multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irqueue.c&n; * Version:       0.3&n; * Description:   General queue implementation&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Jun  9 13:29:31 1998&n; * Modified at:   Sun Dec 12 13:48:22 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Modified at:   Thu Jan  4 14:29:10 CET 2001&n; * Modified by:   Marc Zyngier &lt;mzyngier@freesurf.fr&gt;&n; * &n; *     Copyright (C) 1998-1999, Aage Kvalnes &lt;aage@cs.uit.no&gt;&n; *     Copyright (C) 1998, Dag Brattli, &n; *     All Rights Reserved.&n; *&n; *     This code is taken from the Vortex Operating System written by Aage&n; *     Kvalnes. Aage has agreed that this code can use the GPL licence,&n; *     although he does not use that licence in his own code.&n; *     &n; *     This copyright does however _not_ include the ELF hash() function&n; *     which I currently don&squot;t know which licence or copyright it&n; *     has. Please inform me if you know.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
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
suffix:semicolon
r_static
id|__u32
id|hash
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
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
r_int
id|i
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
multiline_comment|/* Make sure all spinlock&squot;s are unlocked */
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
id|hashbin-&gt;hb_mutex
(braket
id|i
)braket
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_return
id|hashbin
suffix:semicolon
)brace
multiline_comment|/*&n; * Function hashbin_clear (hashbin, free_func)&n; *&n; *    Remove all entries from the hashbin, see also the comments in &n; *    hashbin_delete() below&n; */
DECL|function|hashbin_clear
r_int
id|hashbin_clear
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
multiline_comment|/*&n;&t; * Free the entries in the hashbin&n;&t; */
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
id|hashbin-&gt;hb_size
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
multiline_comment|/*&n;&t; *  Free the hashbin structure&n;&t; */
id|hashbin-&gt;magic
op_assign
op_complement
id|HB_MAGIC
suffix:semicolon
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
id|__u32
id|hashv
comma
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
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
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
id|HB_GLOBAL
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hashbin-&gt;hb_mutex
(braket
id|bin
)braket
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCAL
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
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
id|strncpy
c_func
(paren
id|entry-&gt;q_name
comma
id|name
comma
l_int|32
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Insert new entry first&n;&t; * TODO: Perhaps allow sorted lists?&n;&t; *       -&gt; Merge sort if a sorted list should be created&n;&t; */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_SORTED
)paren
(brace
)brace
r_else
(brace
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
)brace
id|hashbin-&gt;hb_size
op_increment
suffix:semicolon
multiline_comment|/* Release lock */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_GLOBAL
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hashbin-&gt;hb_mutex
(braket
id|bin
)braket
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCAL
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function hashbin_find (hashbin, hashv, name)&n; *&n; *    Find item with the given hashv or name&n; *&n; */
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
id|__u32
id|hashv
comma
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
multiline_comment|/* Synchronize */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_GLOBAL
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hashbin-&gt;hb_mutex
(braket
id|bin
)braket
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCAL
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
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
multiline_comment|/* Release lock */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_GLOBAL
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hashbin-&gt;hb_mutex
(braket
id|bin
)braket
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCAL
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
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
suffix:semicolon
id|irda_queue_t
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
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
id|hashbin_remove
c_func
(paren
id|hashbin
comma
id|entry-&gt;q_hash
comma
l_int|NULL
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
multiline_comment|/* &n; *  Function hashbin_remove (hashbin, hashv, name)&n; *&n; *    Remove entry with the given name&n; *&n; */
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
id|__u32
id|hashv
comma
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
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
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
id|HB_GLOBAL
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hashbin-&gt;hb_mutex
(braket
id|bin
)braket
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCAL
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
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
id|HB_GLOBAL
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hashbin-&gt;hb_mutex
(braket
id|bin
)braket
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCAL
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
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
multiline_comment|/* &n; *  Function hashbin_remove (hashbin, hashv, name)&n; *&n; *    Remove entry with the given name&n; *&n; * In some cases, the user of hashbin can&squot;t guarantee the unicity&n; * of either the hashv or name.&n; * In those cases, using the above function is guaranteed to cause troubles,&n; * so we use this one instead...&n; * And by the way, it&squot;s also faster, because we skip the search phase ;-)&n; */
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
id|__u32
id|hashv
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
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
r_return
l_int|NULL
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
multiline_comment|/* Synchronize */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_GLOBAL
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hashbin-&gt;hb_mutex
(braket
id|bin
)braket
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCAL
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Default is no-lock  */
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
multiline_comment|/* Release lock */
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_GLOBAL
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hashbin-&gt;hb_mutex
(braket
id|bin
)braket
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hashbin-&gt;hb_type
op_amp
id|HB_LOCAL
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_return
id|entry
suffix:semicolon
)brace
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
multiline_comment|/*&n; * Function hashbin_get_next (hashbin)&n; *&n; *    Get next item in hashbin. A series of hashbin_get_next() calls must&n; *    be started by a call to hashbin_get_first(). The function returns&n; *    NULL when all items have been traversed&n; * &n; */
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
multiline_comment|/*&n; * Function enqueue_last (queue, proc)&n; *&n; *    Insert item into end of queue.&n; *&n; */
DECL|function|__enqueue_last
r_static
r_void
id|__enqueue_last
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
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
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
multiline_comment|/*&n;&t;&t; * Queue is not empty.  Insert element into end of queue.&n;&t;&t; */
id|element-&gt;q_prev
op_assign
(paren
op_star
id|queue
)paren
op_member_access_from_pointer
id|q_prev
suffix:semicolon
id|element-&gt;q_prev-&gt;q_next
op_assign
id|element
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
id|element-&gt;q_next
op_assign
op_star
id|queue
suffix:semicolon
)brace
)brace
DECL|function|enqueue_last
r_inline
r_void
id|enqueue_last
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
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|__enqueue_last
c_func
(paren
id|queue
comma
id|element
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function enqueue_first (queue, proc)&n; *&n; *    Insert item first in queue.&n; *&n; */
DECL|function|enqueue_first
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
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
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
multiline_comment|/*&n; * Function enqueue_queue (queue, list)&n; *&n; *    Insert a queue (list) into the start of the first queue&n; *&n; */
DECL|function|enqueue_queue
r_void
id|enqueue_queue
c_func
(paren
id|irda_queue_t
op_star
op_star
id|queue
comma
id|irda_queue_t
op_star
op_star
id|list
)paren
(brace
id|irda_queue_t
op_star
id|tmp
suffix:semicolon
multiline_comment|/*&n;&t; * Check if queue is empty&n;&t; */
r_if
c_cond
(paren
op_star
id|queue
)paren
(brace
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|q_prev-&gt;q_next
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
(paren
op_star
id|list
)paren
suffix:semicolon
id|tmp
op_assign
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|q_prev
suffix:semicolon
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|q_prev
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
id|tmp
suffix:semicolon
)brace
r_else
(brace
op_star
id|queue
op_assign
(paren
op_star
id|list
)paren
suffix:semicolon
)brace
(paren
op_star
id|list
)paren
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function enqueue_second (queue, proc)&n; *&n; *    Insert item behind head of queue.&n; *&n; */
macro_line|#if 0
r_static
r_void
id|enqueue_second
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
l_int|0
comma
l_string|&quot;enqueue_second()&bslash;n&quot;
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
multiline_comment|/*&n;&t;&t; * Queue is not empty.  Insert element into ..&n;&t;&t; */
id|element-&gt;q_prev
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
id|q_next-&gt;q_prev
op_assign
id|element
suffix:semicolon
id|element-&gt;q_next
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
id|q_next
op_assign
id|element
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; * Function dequeue (queue)&n; *&n; *    Remove first entry in queue&n; *&n; */
DECL|function|dequeue_first
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
multiline_comment|/*&n; * Function hash (name)&n; *&n; *    This function hash the input string &squot;name&squot; using the ELF hash&n; *    function for strings.&n; */
DECL|function|hash
r_static
id|__u32
id|hash
c_func
(paren
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
eof
