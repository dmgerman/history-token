multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irqueue.c&n; * Version:       0.3&n; * Description:   General queue implementation&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Jun  9 13:29:31 1998&n; * Modified at:   Sun Dec 12 13:48:22 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Modified at:   Thu Jan  4 14:29:10 CET 2001&n; * Modified by:   Marc Zyngier &lt;mzyngier@freesurf.fr&gt;&n; * &n; *     Copyright (C) 1998-1999, Aage Kvalnes &lt;aage@cs.uit.no&gt;&n; *     Copyright (C) 1998, Dag Brattli, &n; *     All Rights Reserved.&n; *&n; *     This code is taken from the Vortex Operating System written by Aage&n; *     Kvalnes. Aage has agreed that this code can use the GPL licence,&n; *     although he does not use that licence in his own code.&n; *     &n; *     This copyright does however _not_ include the ELF hash() function&n; *     which I currently don&squot;t know which licence or copyright it&n; *     has. Please inform me if you know.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
multiline_comment|/*&n; * NOTE :&n; * There are various problems with this package :&n; *&t;o the hash function for ints is pathetic (but could be changed)&n; *&t;o locking is sometime suspicious (especially during enumeration)&n; *&t;o most users have only a few elements (== overhead)&n; *&t;o most users never use seach, so don&squot;t benefit from hashing&n; * Problem already fixed :&n; *&t;o not 64 bit compliant (most users do hashv = (int) self)&n; *&t;o hashbin_remove() is broken =&gt; use hashbin_remove_this()&n; * I think most users would be better served by a simple linked list&n; * (like include/linux/list.h) with a global spinlock per list.&n; * Jean II&n; */
multiline_comment|/*&n; * Notes on the concurrent access to hashbin and other SMP issues&n; * -------------------------------------------------------------&n; *&t;Hashbins are very often in the IrDA stack a global repository of&n; * information, and therefore used in a very asynchronous manner following&n; * various events (driver calls, timers, user calls...).&n; *&t;Therefore, very often it is highly important to consider the&n; * management of concurrent access to the hashbin and how to guarantee the&n; * consistency of the operations on it.&n; *&n; *&t;First, we need to define the objective of locking :&n; *&t;&t;1) Protect user data (content pointed by the hashbin)&n; *&t;&t;2) Protect hashbin structure itself (linked list in each bin)&n; *&n; *&t;&t;&t;     OLD LOCKING&n; *&t;&t;&t;     -----------&n; *&n; *&t;The previous locking strategy, either HB_LOCAL or HB_GLOBAL were&n; * both inadequate in *both* aspect.&n; *&t;&t;o HB_GLOBAL was using a spinlock for each bin (local locking).&n; *&t;&t;o HB_LOCAL was disabling irq on *all* CPUs, so use a single&n; *&t;&t;  global semaphore.&n; *&t;The problems were :&n; *&t;&t;A) Global irq disabling is no longer supported by the kernel&n; *&t;&t;B) No protection for the hashbin struct global data&n; *&t;&t;&t;o hashbin_delete()&n; *&t;&t;&t;o hb_current&n; *&t;&t;C) No protection for user data in some cases&n; *&n; *&t;A) HB_LOCAL use global irq disabling, so doesn&squot;t work on kernel&n; * 2.5.X. Even when it is supported (kernel 2.4.X and earlier), its&n; * performance is not satisfactory on SMP setups. Most hashbins were&n; * HB_LOCAL, so (A) definitely need fixing.&n; *&t;B) HB_LOCAL could be modified to fix (B). However, because HB_GLOBAL&n; * lock only the individual bins, it will never be able to lock the&n; * global data, so can&squot;t do (B).&n; *&t;C) Some functions return pointer to data that is still in the&n; * hashbin :&n; *&t;&t;o hashbin_find()&n; *&t;&t;o hashbin_get_first()&n; *&t;&t;o hashbin_get_next()&n; *&t;As the data is still in the hashbin, it may be changed or free&squot;d&n; * while the caller is examinimg the data. In those case, locking can&squot;t&n; * be done within the hashbin, but must include use of the data within&n; * the caller.&n; *&t;The caller can easily do this with HB_LOCAL (just disable irqs).&n; * However, this is impossible with HB_GLOBAL because the caller has no&n; * way to know the proper bin, so don&squot;t know which spinlock to use.&n; *&n; *&t;Quick summary : can no longer use HB_LOCAL, and HB_GLOBAL is&n; * fundamentally broken and will never work.&n; *&n; *&t;&t;&t;     NEW LOCKING&n; *&t;&t;&t;     -----------&n; *&n; *&t;To fix those problems, I&squot;ve introduce a few changes in the&n; * hashbin locking :&n; *&t;&t;1) New HB_LOCK scheme&n; *&t;&t;2) hashbin-&gt;hb_spinlock&n; *&t;&t;3) New hashbin usage policy&n; *&n; * HB_LOCK :&n; * -------&n; *&t;HB_LOCK is a locking scheme intermediate between the old HB_LOCAL&n; * and HB_GLOBAL. It uses a single spinlock to protect the whole content&n; * of the hashbin. As it is a single spinlock, it can protect the global&n; * data of the hashbin and not only the bins themselves.&n; *&t;HB_LOCK can only protect some of the hashbin calls, so it only lock&n; * call that can be made 100% safe and leave other call unprotected.&n; *&t;HB_LOCK in theory is slower than HB_GLOBAL, but as the hashbin&n; * content is always small contention is not high, so it doesn&squot;t matter&n; * much. HB_LOCK is probably faster than HB_LOCAL.&n; *&n; * hashbin-&gt;hb_spinlock :&n; * --------------------&n; *&t;The spinlock that HB_LOCK uses is available for caller, so that&n; * the caller can protect unprotected calls (see below).&n; *&t;If the caller want to do entirely its own locking (HB_NOLOCK), he&n; * can do so and may use safely this spinlock.&n; *&t;Locking is done like this :&n; *&t;&t;spin_lock_irqsave(&amp;hashbin-&gt;hb_spinlock, flags);&n; *&t;Releasing the lock :&n; *&t;&t;spin_unlock_irqrestore(&amp;hashbin-&gt;hb_spinlock, flags);&n; *&n; * Safe &amp; Protected calls :&n; * ----------------------&n; *&t;The following calls are safe or protected via HB_LOCK :&n; *&t;&t;o hashbin_new()&t;&t;-&gt; safe&n; *&t;&t;o hashbin_delete()&n; *&t;&t;o hashbin_insert()&n; *&t;&t;o hashbin_remove_first()&n; *&t;&t;o hashbin_remove()&n; *&t;&t;o hashbin_remove_this()&n; *&t;&t;o HASHBIN_GET_SIZE()&t;-&gt; atomic&n; *&n; *&t;The following calls only protect the hashbin itself :&n; *&t;&t;o hashbin_lock_find()&n; *&t;&t;o hashbin_find_next()&n; *&n; * Unprotected calls :&n; * -----------------&n; *&t;The following calls need to be protected by the caller :&n; *&t;&t;o hashbin_find()&n; *&t;&t;o hashbin_get_first()&n; *&t;&t;o hashbin_get_next()&n; *&n; * Locking Policy :&n; * --------------&n; *&t;If the hashbin is used only in a single thread of execution&n; * (explicitly or implicitely), you can use HB_NOLOCK&n; *&t;If the calling module already provide concurrent access protection,&n; * you may use HB_NOLOCK.&n; *&n; *&t;In all other cases, you need to use HB_LOCK and lock the hashbin&n; * every time before calling one of the unprotected calls. You also must&n; * use the pointer returned by the unprotected call within the locked&n; * region.&n; *&n; * Extra care for enumeration :&n; * --------------------------&n; *&t;hashbin_get_first() and hashbin_get_next() use the hashbin to&n; * store the current position, in hb_current.&n; *&t;As long as the hashbin remains locked, this is safe. If you unlock&n; * the hashbin, the current position may change if anybody else modify&n; * or enumerate the hashbin.&n; *&t;Summary : do the full enumeration while locked.&n; *&n; *&t;Alternatively, you may use hashbin_find_next(). But, this will&n; * be slower, is more complex to use and doesn&squot;t protect the hashbin&n; * content. So, care is needed here as well.&n; *&n; * Other issues :&n; * ------------&n; *&t;I believe that we are overdoing it by using spin_lock_irqsave()&n; * and we should use only spin_lock_bh() or similar. But, I don&squot;t have&n; * the balls to try it out.&n; *&t;Don&squot;t believe that because hashbin are now (somewhat) SMP safe&n; * that the rest of the code is. Higher layers tend to be safest,&n; * but LAP and LMP would need some serious dedicated love.&n; *&n; * Jean II&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
multiline_comment|/************************ QUEUE SUBROUTINES ************************/
multiline_comment|/*&n; * Hashbin&n; */
DECL|macro|GET_HASHBIN
mdefine_line|#define GET_HASHBIN(x) ( x &amp; HASHBIN_MASK )
multiline_comment|/*&n; * Function hash (name)&n; *&n; *    This function hash the input string &squot;name&squot; using the ELF hash&n; *    function for strings.&n; */
DECL|function|hash
r_static
id|__u32
id|hash
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
id|__u32
id|h
op_assign
l_int|0
suffix:semicolon
id|__u32
id|g
suffix:semicolon
r_while
c_loop
(paren
op_star
id|name
)paren
(brace
id|h
op_assign
(paren
id|h
op_lshift
l_int|4
)paren
op_plus
op_star
id|name
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|g
op_assign
(paren
id|h
op_amp
l_int|0xf0000000
)paren
)paren
)paren
id|h
op_xor_assign
id|g
op_rshift
l_int|24
suffix:semicolon
id|h
op_and_assign
op_complement
id|g
suffix:semicolon
)brace
r_return
id|h
suffix:semicolon
)brace
multiline_comment|/*&n; * Function enqueue_first (queue, proc)&n; *&n; *    Insert item first in queue.&n; *&n; */
DECL|function|enqueue_first
r_static
r_void
id|enqueue_first
c_func
(paren
id|irda_queue_t
op_star
op_star
id|queue
comma
id|irda_queue_t
op_star
id|element
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check if queue is empty.&n;&t; */
r_if
c_cond
(paren
op_star
id|queue
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * Queue is empty.  Insert one element into the queue.&n;&t;&t; */
id|element-&gt;q_next
op_assign
id|element-&gt;q_prev
op_assign
op_star
id|queue
op_assign
id|element
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Queue is not empty.  Insert element into front of queue.&n;&t;&t; */
id|element-&gt;q_next
op_assign
(paren
op_star
id|queue
)paren
suffix:semicolon
(paren
op_star
id|queue
)paren
op_member_access_from_pointer
id|q_prev-&gt;q_next
op_assign
id|element
suffix:semicolon
id|element-&gt;q_prev
op_assign
(paren
op_star
id|queue
)paren
op_member_access_from_pointer
id|q_prev
suffix:semicolon
(paren
op_star
id|queue
)paren
op_member_access_from_pointer
id|q_prev
op_assign
id|element
suffix:semicolon
(paren
op_star
id|queue
)paren
op_assign
id|element
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function dequeue (queue)&n; *&n; *    Remove first entry in queue&n; *&n; */
DECL|function|dequeue_first
r_static
id|irda_queue_t
op_star
id|dequeue_first
c_func
(paren
id|irda_queue_t
op_star
op_star
id|queue
)paren
(brace
id|irda_queue_t
op_star
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;dequeue_first()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set return value&n;&t; */
id|ret
op_assign
op_star
id|queue
suffix:semicolon
r_if
c_cond
(paren
op_star
id|queue
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * Queue was empty.&n;&t;&t; */
)brace
r_else
r_if
c_cond
(paren
(paren
op_star
id|queue
)paren
op_member_access_from_pointer
id|q_next
op_eq
op_star
id|queue
)paren
(brace
multiline_comment|/* &n;&t;&t; *  Queue only contained a single element. It will now be&n;&t;&t; *  empty.  &n;&t;&t; */
op_star
id|queue
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Queue contained several element.  Remove the first one.&n;&t;&t; */
(paren
op_star
id|queue
)paren
op_member_access_from_pointer
id|q_prev-&gt;q_next
op_assign
(paren
op_star
id|queue
)paren
op_member_access_from_pointer
id|q_next
suffix:semicolon
(paren
op_star
id|queue
)paren
op_member_access_from_pointer
id|q_next-&gt;q_prev
op_assign
(paren
op_star
id|queue
)paren
op_member_access_from_pointer
id|q_prev
suffix:semicolon
op_star
id|queue
op_assign
(paren
op_star
id|queue
)paren
op_member_access_from_pointer
id|q_next
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Return the removed entry (or NULL of queue was empty).&n;&t; */
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function dequeue_general (queue, element)&n; *&n; *&n; */
DECL|function|dequeue_general
r_static
id|irda_queue_t
op_star
id|dequeue_general
c_func
(paren
id|irda_queue_t
op_star
op_star
id|queue
comma
id|irda_queue_t
op_star
id|element
)paren
(brace
id|irda_queue_t
op_star
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;dequeue_general()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set return value&n;&t; */
id|ret
op_assign
op_star
id|queue
suffix:semicolon
r_if
c_cond
(paren
op_star
id|queue
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * Queue was empty.&n;&t;&t; */
)brace
r_else
r_if
c_cond
(paren
(paren
op_star
id|queue
)paren
op_member_access_from_pointer
id|q_next
op_eq
op_star
id|queue
)paren
(brace
multiline_comment|/* &n;&t;&t; *  Queue only contained a single element. It will now be&n;&t;&t; *  empty.  &n;&t;&t; */
op_star
id|queue
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; *  Remove specific element.&n;&t;&t; */
id|element-&gt;q_prev-&gt;q_next
op_assign
id|element-&gt;q_next
suffix:semicolon
id|element-&gt;q_next-&gt;q_prev
op_assign
id|element-&gt;q_prev
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|queue
)paren
op_eq
id|element
)paren
(paren
op_star
id|queue
)paren
op_assign
id|element-&gt;q_next
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Return the removed entry (or NULL of queue was empty).&n;&t; */
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/************************ HASHBIN MANAGEMENT ************************/
multiline_comment|/*&n; * Function hashbin_create ( type, name )&n; *&n; *    Create hashbin!&n; *&n; */
DECL|function|hashbin_new
id|hashbin_t
op_star
id|hashbin_new
c_func
(paren
r_int
id|type
)paren
(brace
id|hashbin_t
op_star
id|hashbin
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate new hashbin&n;&t; */
id|hashbin
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|hashbin_t
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hashbin
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize structure&n;&t; */
id|memset
c_func
(paren
id|hashbin
comma
l_int|0
comma
r_sizeof
(paren
id|hashbin_t
)paren
)paren
suffix:semicolon
id|hashbin-&gt;hb_type
op_assign
id|type
suffix:semicolon
id|hashbin-&gt;magic
op_assign
id|HB_MAGIC
suffix:semicolon
singleline_comment|//hashbin-&gt;hb_current = NULL;
multiline_comment|/* Make sure all spinlock&squot;s are unlocked */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCK
)paren
(brace
id|spin_lock_init
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
)paren
suffix:semicolon
)brace
r_return
id|hashbin
suffix:semicolon
)brace
DECL|variable|hashbin_new
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_new
)paren
suffix:semicolon
multiline_comment|/*&n; * Function hashbin_delete (hashbin, free_func)&n; *&n; *    Destroy hashbin, the free_func can be a user supplied special routine &n; *    for deallocating this structure if it&squot;s complex. If not the user can &n; *    just supply kfree, which should take care of the job.&n; */
DECL|function|hashbin_delete
r_int
id|hashbin_delete
c_func
(paren
id|hashbin_t
op_star
id|hashbin
comma
id|FREE_FUNC
id|free_func
)paren
(brace
id|irda_queue_t
op_star
id|queue
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin-&gt;magic
op_eq
id|HB_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Synchronize */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCK
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Free the entries in the hashbin, TODO: use hashbin_clear when&n;&t; *  it has been shown to work&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|HASHBIN_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|queue
op_assign
id|dequeue_first
c_func
(paren
(paren
id|irda_queue_t
op_star
op_star
)paren
op_amp
id|hashbin-&gt;hb_queue
(braket
id|i
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|queue
)paren
(brace
r_if
c_cond
(paren
id|free_func
)paren
(paren
op_star
id|free_func
)paren
(paren
id|queue
)paren
suffix:semicolon
id|queue
op_assign
id|dequeue_first
c_func
(paren
(paren
id|irda_queue_t
op_star
op_star
)paren
op_amp
id|hashbin-&gt;hb_queue
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Cleanup local data */
id|hashbin-&gt;hb_current
op_assign
l_int|NULL
suffix:semicolon
id|hashbin-&gt;magic
op_assign
op_complement
id|HB_MAGIC
suffix:semicolon
multiline_comment|/* Release lock */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCK
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Free the hashbin structure&n;&t; */
id|kfree
c_func
(paren
id|hashbin
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hashbin_delete
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_delete
)paren
suffix:semicolon
multiline_comment|/********************* HASHBIN LIST OPERATIONS *********************/
multiline_comment|/*&n; * Function hashbin_insert (hashbin, entry, name)&n; *&n; *    Insert an entry into the hashbin&n; *&n; */
DECL|function|hashbin_insert
r_void
id|hashbin_insert
c_func
(paren
id|hashbin_t
op_star
id|hashbin
comma
id|irda_queue_t
op_star
id|entry
comma
r_int
id|hashv
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
id|bin
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin-&gt;magic
op_eq
id|HB_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Locate hashbin&n;&t; */
r_if
c_cond
(paren
id|name
)paren
id|hashv
op_assign
id|hash
c_func
(paren
id|name
)paren
suffix:semicolon
id|bin
op_assign
id|GET_HASHBIN
c_func
(paren
id|hashv
)paren
suffix:semicolon
multiline_comment|/* Synchronize */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCK
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Default is no-lock  */
multiline_comment|/*&n;&t; * Store name and key&n;&t; */
id|entry-&gt;q_hash
op_assign
id|hashv
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
id|strlcpy
c_func
(paren
id|entry-&gt;q_name
comma
id|name
comma
r_sizeof
(paren
id|entry-&gt;q_name
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Insert new entry first&n;&t; */
id|enqueue_first
c_func
(paren
(paren
id|irda_queue_t
op_star
op_star
)paren
op_amp
id|hashbin-&gt;hb_queue
(braket
id|bin
)braket
comma
id|entry
)paren
suffix:semicolon
id|hashbin-&gt;hb_size
op_increment
suffix:semicolon
multiline_comment|/* Release lock */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCK
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Default is no-lock  */
)brace
DECL|variable|hashbin_insert
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_insert
)paren
suffix:semicolon
multiline_comment|/* &n; *  Function hashbin_remove_first (hashbin)&n; *&n; *    Remove first entry of the hashbin&n; *&n; * Note : this function no longer use hashbin_remove(), but does things&n; * similar to hashbin_remove_this(), so can be considered safe.&n; * Jean II&n; */
DECL|function|hashbin_remove_first
r_void
op_star
id|hashbin_remove_first
c_func
(paren
id|hashbin_t
op_star
id|hashbin
)paren
(brace
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|irda_queue_t
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Synchronize */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCK
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Default is no-lock  */
id|entry
op_assign
id|hashbin_get_first
c_func
(paren
id|hashbin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_ne
l_int|NULL
)paren
(brace
r_int
id|bin
suffix:semicolon
r_int
id|hashv
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Locate hashbin&n;&t;&t; */
id|hashv
op_assign
id|entry-&gt;q_hash
suffix:semicolon
id|bin
op_assign
id|GET_HASHBIN
c_func
(paren
id|hashv
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Dequeue the entry...&n;&t;&t; */
id|dequeue_general
c_func
(paren
(paren
id|irda_queue_t
op_star
op_star
)paren
op_amp
id|hashbin-&gt;hb_queue
(braket
id|bin
)braket
comma
(paren
id|irda_queue_t
op_star
)paren
id|entry
)paren
suffix:semicolon
id|hashbin-&gt;hb_size
op_decrement
suffix:semicolon
id|entry-&gt;q_next
op_assign
l_int|NULL
suffix:semicolon
id|entry-&gt;q_prev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  Check if this item is the currently selected item, and in&n;&t;&t; *  that case we must reset hb_current&n;&t;&t; */
r_if
c_cond
(paren
id|entry
op_eq
id|hashbin-&gt;hb_current
)paren
id|hashbin-&gt;hb_current
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Release lock */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCK
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Default is no-lock  */
r_return
id|entry
suffix:semicolon
)brace
multiline_comment|/* &n; *  Function hashbin_remove (hashbin, hashv, name)&n; *&n; *    Remove entry with the given name&n; *&n; *  The use of this function is highly discouraged, because the whole&n; *  concept behind hashbin_remove() is broken. In many cases, it&squot;s not&n; *  possible to guarantee the unicity of the index (either hashv or name),&n; *  leading to removing the WRONG entry.&n; *  The only simple safe use is :&n; *&t;&t;hashbin_remove(hasbin, (int) self, NULL);&n; *  In other case, you must think hard to guarantee unicity of the index.&n; *  Jean II&n; */
DECL|function|hashbin_remove
r_void
op_star
id|hashbin_remove
c_func
(paren
id|hashbin_t
op_star
id|hashbin
comma
r_int
id|hashv
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|bin
comma
id|found
op_assign
id|FALSE
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|irda_queue_t
op_star
id|entry
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin-&gt;magic
op_eq
id|HB_MAGIC
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Locate hashbin&n;&t; */
r_if
c_cond
(paren
id|name
)paren
id|hashv
op_assign
id|hash
c_func
(paren
id|name
)paren
suffix:semicolon
id|bin
op_assign
id|GET_HASHBIN
c_func
(paren
id|hashv
)paren
suffix:semicolon
multiline_comment|/* Synchronize */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCK
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Default is no-lock  */
multiline_comment|/*&n;&t; * Search for entry&n;&t; */
id|entry
op_assign
id|hashbin-&gt;hb_queue
(braket
id|bin
)braket
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
r_do
(brace
multiline_comment|/*&n;&t;&t;&t; * Check for key&n;&t;&t;&t; */
r_if
c_cond
(paren
id|entry-&gt;q_hash
op_eq
id|hashv
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Name compare too?&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|name
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|entry-&gt;q_name
comma
id|name
)paren
op_eq
l_int|0
)paren
(brace
id|found
op_assign
id|TRUE
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|found
op_assign
id|TRUE
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|entry
op_assign
id|entry-&gt;q_next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|entry
op_ne
id|hashbin-&gt;hb_queue
(braket
id|bin
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If entry was found, dequeue it&n;&t; */
r_if
c_cond
(paren
id|found
)paren
(brace
id|dequeue_general
c_func
(paren
(paren
id|irda_queue_t
op_star
op_star
)paren
op_amp
id|hashbin-&gt;hb_queue
(braket
id|bin
)braket
comma
(paren
id|irda_queue_t
op_star
)paren
id|entry
)paren
suffix:semicolon
id|hashbin-&gt;hb_size
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  Check if this item is the currently selected item, and in&n;&t;&t; *  that case we must reset hb_current&n;&t;&t; */
r_if
c_cond
(paren
id|entry
op_eq
id|hashbin-&gt;hb_current
)paren
id|hashbin-&gt;hb_current
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Release lock */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCK
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Default is no-lock  */
multiline_comment|/* Return */
r_if
c_cond
(paren
id|found
)paren
r_return
id|entry
suffix:semicolon
r_else
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|hashbin_remove
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_remove
)paren
suffix:semicolon
multiline_comment|/* &n; *  Function hashbin_remove_this (hashbin, entry)&n; *&n; *    Remove entry with the given name&n; *&n; * In some cases, the user of hashbin can&squot;t guarantee the unicity&n; * of either the hashv or name.&n; * In those cases, using the above function is guaranteed to cause troubles,&n; * so we use this one instead...&n; * And by the way, it&squot;s also faster, because we skip the search phase ;-)&n; */
DECL|function|hashbin_remove_this
r_void
op_star
id|hashbin_remove_this
c_func
(paren
id|hashbin_t
op_star
id|hashbin
comma
id|irda_queue_t
op_star
id|entry
)paren
(brace
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
id|bin
suffix:semicolon
r_int
id|hashv
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin-&gt;magic
op_eq
id|HB_MAGIC
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|entry
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Synchronize */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCK
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Default is no-lock  */
multiline_comment|/* Check if valid and not already removed... */
r_if
c_cond
(paren
(paren
id|entry-&gt;q_next
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|entry-&gt;q_prev
op_eq
l_int|NULL
)paren
)paren
(brace
id|entry
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Locate hashbin&n;&t; */
id|hashv
op_assign
id|entry-&gt;q_hash
suffix:semicolon
id|bin
op_assign
id|GET_HASHBIN
c_func
(paren
id|hashv
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Dequeue the entry...&n;&t; */
id|dequeue_general
c_func
(paren
(paren
id|irda_queue_t
op_star
op_star
)paren
op_amp
id|hashbin-&gt;hb_queue
(braket
id|bin
)braket
comma
(paren
id|irda_queue_t
op_star
)paren
id|entry
)paren
suffix:semicolon
id|hashbin-&gt;hb_size
op_decrement
suffix:semicolon
id|entry-&gt;q_next
op_assign
l_int|NULL
suffix:semicolon
id|entry-&gt;q_prev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *  Check if this item is the currently selected item, and in&n;&t; *  that case we must reset hb_current&n;&t; */
r_if
c_cond
(paren
id|entry
op_eq
id|hashbin-&gt;hb_current
)paren
id|hashbin-&gt;hb_current
op_assign
l_int|NULL
suffix:semicolon
id|out
suffix:colon
multiline_comment|/* Release lock */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCK
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Default is no-lock  */
r_return
id|entry
suffix:semicolon
)brace
DECL|variable|hashbin_remove_this
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_remove_this
)paren
suffix:semicolon
multiline_comment|/*********************** HASHBIN ENUMERATION ***********************/
multiline_comment|/*&n; * Function hashbin_common_find (hashbin, hashv, name)&n; *&n; *    Find item with the given hashv or name&n; *&n; */
DECL|function|hashbin_find
r_void
op_star
id|hashbin_find
c_func
(paren
id|hashbin_t
op_star
id|hashbin
comma
r_int
id|hashv
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|bin
suffix:semicolon
id|irda_queue_t
op_star
id|entry
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;hashbin_find()&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin-&gt;magic
op_eq
id|HB_MAGIC
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Locate hashbin&n;&t; */
r_if
c_cond
(paren
id|name
)paren
id|hashv
op_assign
id|hash
c_func
(paren
id|name
)paren
suffix:semicolon
id|bin
op_assign
id|GET_HASHBIN
c_func
(paren
id|hashv
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Search for entry&n;&t; */
id|entry
op_assign
id|hashbin-&gt;hb_queue
(braket
id|bin
)braket
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
r_do
(brace
multiline_comment|/*&n;&t;&t;&t; * Check for key&n;&t;&t;&t; */
r_if
c_cond
(paren
id|entry-&gt;q_hash
op_eq
id|hashv
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Name compare too?&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|name
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|entry-&gt;q_name
comma
id|name
)paren
op_eq
l_int|0
)paren
(brace
r_return
id|entry
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
id|entry
suffix:semicolon
)brace
)brace
id|entry
op_assign
id|entry-&gt;q_next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|entry
op_ne
id|hashbin-&gt;hb_queue
(braket
id|bin
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|hashbin_find
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_find
)paren
suffix:semicolon
multiline_comment|/*&n; * Function hashbin_lock_find (hashbin, hashv, name)&n; *&n; *    Find item with the given hashv or name&n; *&n; * Same, but with spinlock protection...&n; * I call it safe, but it&squot;s only safe with respect to the hashbin, not its&n; * content. - Jean II&n; */
DECL|function|hashbin_lock_find
r_void
op_star
id|hashbin_lock_find
c_func
(paren
id|hashbin_t
op_star
id|hashbin
comma
r_int
id|hashv
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|irda_queue_t
op_star
id|entry
suffix:semicolon
multiline_comment|/* Synchronize */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Search for entry&n;&t; */
id|entry
op_assign
(paren
id|irda_queue_t
op_star
)paren
id|hashbin_find
c_func
(paren
id|hashbin
comma
id|hashv
comma
id|name
)paren
suffix:semicolon
multiline_comment|/* Release lock */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|variable|hashbin_lock_find
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_lock_find
)paren
suffix:semicolon
multiline_comment|/*&n; * Function hashbin_find (hashbin, hashv, name, pnext)&n; *&n; *    Find an item with the given hashv or name, and its successor&n; *&n; * This function allow to do concurrent enumerations without the&n; * need to lock over the whole session, because the caller keep the&n; * context of the search. On the other hand, it might fail and return&n; * NULL if the entry is removed. - Jean II&n; */
DECL|function|hashbin_find_next
r_void
op_star
id|hashbin_find_next
c_func
(paren
id|hashbin_t
op_star
id|hashbin
comma
r_int
id|hashv
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
op_star
id|pnext
)paren
(brace
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|irda_queue_t
op_star
id|entry
suffix:semicolon
multiline_comment|/* Synchronize */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Search for current entry&n;&t; * This allow to check if the current item is still in the&n;&t; * hashbin or has been removed.&n;&t; */
id|entry
op_assign
(paren
id|irda_queue_t
op_star
)paren
id|hashbin_find
c_func
(paren
id|hashbin
comma
id|hashv
comma
id|name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Trick hashbin_get_next() to return what we want&n;&t; */
r_if
c_cond
(paren
id|entry
)paren
(brace
id|hashbin-&gt;hb_current
op_assign
id|entry
suffix:semicolon
op_star
id|pnext
op_assign
id|hashbin_get_next
c_func
(paren
id|hashbin
)paren
suffix:semicolon
)brace
r_else
op_star
id|pnext
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Release lock */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hashbin-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|variable|hashbin_find_next
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_find_next
)paren
suffix:semicolon
multiline_comment|/*&n; * Function hashbin_get_first (hashbin)&n; *&n; *    Get a pointer to first element in hashbin, this function must be&n; *    called before any calls to hashbin_get_next()!&n; *&n; */
DECL|function|hashbin_get_first
id|irda_queue_t
op_star
id|hashbin_get_first
c_func
(paren
id|hashbin_t
op_star
id|hashbin
)paren
(brace
id|irda_queue_t
op_star
id|entry
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin-&gt;magic
op_eq
id|HB_MAGIC
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hashbin
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|HASHBIN_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|entry
op_assign
id|hashbin-&gt;hb_queue
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
id|hashbin-&gt;hb_current
op_assign
id|entry
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *  Did not find any item in hashbin&n;&t; */
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|hashbin_get_first
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_get_first
)paren
suffix:semicolon
multiline_comment|/*&n; * Function hashbin_get_next (hashbin)&n; *&n; *    Get next item in hashbin. A series of hashbin_get_next() calls must&n; *    be started by a call to hashbin_get_first(). The function returns&n; *    NULL when all items have been traversed&n; * &n; * The context of the search is stored within the hashbin, so you must&n; * protect yourself from concurrent enumerations. - Jean II&n; */
DECL|function|hashbin_get_next
id|irda_queue_t
op_star
id|hashbin_get_next
c_func
(paren
id|hashbin_t
op_star
id|hashbin
)paren
(brace
id|irda_queue_t
op_star
id|entry
suffix:semicolon
r_int
id|bin
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hashbin-&gt;magic
op_eq
id|HB_MAGIC
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hashbin-&gt;hb_current
op_eq
l_int|NULL
)paren
(brace
id|ASSERT
c_func
(paren
id|hashbin-&gt;hb_current
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|entry
op_assign
id|hashbin-&gt;hb_current-&gt;q_next
suffix:semicolon
id|bin
op_assign
id|GET_HASHBIN
c_func
(paren
id|entry-&gt;q_hash
)paren
suffix:semicolon
multiline_comment|/*  &n;&t; *  Make sure that we are not back at the beginning of the queue&n;&t; *  again &n;&t; */
r_if
c_cond
(paren
id|entry
op_ne
id|hashbin-&gt;hb_queue
(braket
id|bin
)braket
)paren
(brace
id|hashbin-&gt;hb_current
op_assign
id|entry
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Check that this is not the last queue in hashbin&n;&t; */
r_if
c_cond
(paren
id|bin
op_ge
id|HASHBIN_SIZE
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *  Move to next queue in hashbin&n;&t; */
id|bin
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|bin
suffix:semicolon
id|i
OL
id|HASHBIN_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|entry
op_assign
id|hashbin-&gt;hb_queue
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
id|hashbin-&gt;hb_current
op_assign
id|entry
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|hashbin_get_next
id|EXPORT_SYMBOL
c_func
(paren
id|hashbin_get_next
)paren
suffix:semicolon
eof
