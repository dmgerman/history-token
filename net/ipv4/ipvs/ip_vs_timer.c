multiline_comment|/*&n; * IPVS         An implementation of the IP virtual server support for the&n; *              LINUX operating system.  IPVS is now implemented as a module&n; *              over the Netfilter framework. IPVS can be used to build a&n; *              high-performance and highly available server based on a&n; *              cluster of servers.&n; *&n; * Version:     $Id: ip_vs_timer.c,v 1.11 2003/06/08 09:31:19 wensong Exp $&n; *&n; * Authors:     Wensong Zhang &lt;wensong@linuxvirtualserver.org&gt;&n; *              Julian Anastasov &lt;ja@ssi.bg&gt;&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; * Changes:&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
multiline_comment|/*&n; * The following block implements slow timers for IPVS, most code is stolen&n; * from linux/kernel/timer.c.&n; * Slow timer is used to avoid the overhead of cascading timers, when lots&n; * of connection entries (&gt;50,000) are cluttered in the system.&n; */
DECL|macro|SHIFT_BITS
mdefine_line|#define SHIFT_BITS 6
DECL|macro|TVN_BITS
mdefine_line|#define TVN_BITS 8
DECL|macro|TVR_BITS
mdefine_line|#define TVR_BITS 10
DECL|macro|TVN_SIZE
mdefine_line|#define TVN_SIZE (1 &lt;&lt; TVN_BITS)
DECL|macro|TVR_SIZE
mdefine_line|#define TVR_SIZE (1 &lt;&lt; TVR_BITS)
DECL|macro|TVN_MASK
mdefine_line|#define TVN_MASK (TVN_SIZE - 1)
DECL|macro|TVR_MASK
mdefine_line|#define TVR_MASK (TVR_SIZE - 1)
DECL|struct|sltimer_vec
r_struct
id|sltimer_vec
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|vec
r_struct
id|list_head
id|vec
(braket
id|TVN_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sltimer_vec_root
r_struct
id|sltimer_vec_root
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|vec
r_struct
id|list_head
id|vec
(braket
id|TVR_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|sltv3
r_static
r_struct
id|sltimer_vec
id|sltv3
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|sltv2
r_static
r_struct
id|sltimer_vec
id|sltv2
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|sltv1
r_static
r_struct
id|sltimer_vec_root
id|sltv1
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|sltvecs
r_static
r_struct
id|sltimer_vec
op_star
r_const
id|sltvecs
(braket
)braket
op_assign
(brace
(paren
r_struct
id|sltimer_vec
op_star
)paren
op_amp
id|sltv1
comma
op_amp
id|sltv2
comma
op_amp
id|sltv3
)brace
suffix:semicolon
DECL|macro|NOOF_SLTVECS
mdefine_line|#define NOOF_SLTVECS (sizeof(sltvecs) / sizeof(sltvecs[0]))
DECL|function|init_sltimervecs
r_static
r_void
id|init_sltimervecs
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|TVN_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
id|sltv3.vec
op_plus
id|i
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
id|sltv2.vec
op_plus
id|i
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TVR_SIZE
suffix:semicolon
id|i
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
id|sltv1.vec
op_plus
id|i
)paren
suffix:semicolon
)brace
DECL|variable|sltimer_jiffies
r_static
r_int
r_int
id|sltimer_jiffies
op_assign
l_int|0
suffix:semicolon
DECL|function|internal_add_sltimer
r_static
r_inline
r_void
id|internal_add_sltimer
c_func
(paren
r_struct
id|sltimer_list
op_star
id|timer
)paren
(brace
multiline_comment|/*&n;&t; * must hold the sltimer lock when calling this&n;&t; */
r_int
r_int
id|expires
op_assign
id|timer-&gt;expires
suffix:semicolon
r_int
r_int
id|idx
op_assign
id|expires
op_minus
id|sltimer_jiffies
suffix:semicolon
r_struct
id|list_head
op_star
id|vec
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|1
op_lshift
(paren
id|SHIFT_BITS
op_plus
id|TVR_BITS
)paren
)paren
(brace
r_int
id|i
op_assign
(paren
id|expires
op_rshift
id|SHIFT_BITS
)paren
op_amp
id|TVR_MASK
suffix:semicolon
id|vec
op_assign
id|sltv1.vec
op_plus
id|i
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|idx
OL
l_int|1
op_lshift
(paren
id|SHIFT_BITS
op_plus
id|TVR_BITS
op_plus
id|TVN_BITS
)paren
)paren
(brace
r_int
id|i
op_assign
(paren
id|expires
op_rshift
(paren
id|SHIFT_BITS
op_plus
id|TVR_BITS
)paren
)paren
op_amp
id|TVN_MASK
suffix:semicolon
id|vec
op_assign
id|sltv2.vec
op_plus
id|i
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|idx
OL
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * can happen if you add a timer with expires == jiffies,&n;&t;&t; * or you set a timer to go off in the past&n;&t;&t; */
id|vec
op_assign
id|sltv1.vec
op_plus
id|sltv1.index
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|idx
op_le
l_int|0xffffffffUL
)paren
(brace
r_int
id|i
op_assign
(paren
id|expires
op_rshift
(paren
id|SHIFT_BITS
op_plus
id|TVR_BITS
op_plus
id|TVN_BITS
)paren
)paren
op_amp
id|TVN_MASK
suffix:semicolon
id|vec
op_assign
id|sltv3.vec
op_plus
id|i
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Can only get here on architectures with 64-bit jiffies */
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|timer-&gt;list
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Timers are FIFO!&n;&t; */
id|list_add
c_func
(paren
op_amp
id|timer-&gt;list
comma
id|vec-&gt;prev
)paren
suffix:semicolon
)brace
DECL|variable|__ip_vs_sltimerlist_lock
r_static
id|spinlock_t
id|__ip_vs_sltimerlist_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|add_sltimer
r_void
id|add_sltimer
c_func
(paren
r_struct
id|sltimer_list
op_star
id|timer
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|__ip_vs_sltimerlist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timer-&gt;list.next
)paren
r_goto
id|bug
suffix:semicolon
id|internal_add_sltimer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|__ip_vs_sltimerlist_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
id|bug
suffix:colon
id|printk
c_func
(paren
l_string|&quot;bug: kernel sltimer added twice at %p.&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|detach_sltimer
r_static
r_inline
r_int
id|detach_sltimer
c_func
(paren
r_struct
id|sltimer_list
op_star
id|timer
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sltimer_pending
c_func
(paren
id|timer
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|timer-&gt;list
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|mod_sltimer
r_void
id|mod_sltimer
c_func
(paren
r_struct
id|sltimer_list
op_star
id|timer
comma
r_int
r_int
id|expires
)paren
(brace
r_int
id|ret
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|__ip_vs_sltimerlist_lock
)paren
suffix:semicolon
id|timer-&gt;expires
op_assign
id|expires
suffix:semicolon
id|ret
op_assign
id|detach_sltimer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|internal_add_sltimer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|__ip_vs_sltimerlist_lock
)paren
suffix:semicolon
)brace
DECL|function|del_sltimer
r_int
id|del_sltimer
c_func
(paren
r_struct
id|sltimer_list
op_star
id|timer
)paren
(brace
r_int
id|ret
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|__ip_vs_sltimerlist_lock
)paren
suffix:semicolon
id|ret
op_assign
id|detach_sltimer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|timer-&gt;list.next
op_assign
id|timer-&gt;list.prev
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|__ip_vs_sltimerlist_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cascade_sltimers
r_static
r_inline
r_void
id|cascade_sltimers
c_func
(paren
r_struct
id|sltimer_vec
op_star
id|tv
)paren
(brace
multiline_comment|/*&n;&t; * cascade all the timers from tv up one level&n;&t; */
r_struct
id|list_head
op_star
id|head
comma
op_star
id|curr
comma
op_star
id|next
suffix:semicolon
id|head
op_assign
id|tv-&gt;vec
op_plus
id|tv-&gt;index
suffix:semicolon
id|curr
op_assign
id|head-&gt;next
suffix:semicolon
multiline_comment|/*&n;&t; * We are removing _all_ timers from the list, so we don&squot;t  have to&n;&t; * detach them individually, just clear the list afterwards.&n;&t; */
r_while
c_loop
(paren
id|curr
op_ne
id|head
)paren
(brace
r_struct
id|sltimer_list
op_star
id|tmp
suffix:semicolon
id|tmp
op_assign
id|list_entry
c_func
(paren
id|curr
comma
r_struct
id|sltimer_list
comma
id|list
)paren
suffix:semicolon
id|next
op_assign
id|curr-&gt;next
suffix:semicolon
id|list_del
c_func
(paren
id|curr
)paren
suffix:semicolon
singleline_comment|// not needed
id|internal_add_sltimer
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|curr
op_assign
id|next
suffix:semicolon
)brace
id|INIT_LIST_HEAD
c_func
(paren
id|head
)paren
suffix:semicolon
id|tv-&gt;index
op_assign
(paren
id|tv-&gt;index
op_plus
l_int|1
)paren
op_amp
id|TVN_MASK
suffix:semicolon
)brace
DECL|function|run_sltimer_list
r_static
r_inline
r_void
id|run_sltimer_list
c_func
(paren
r_void
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|__ip_vs_sltimerlist_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
r_int
)paren
(paren
id|jiffies
op_minus
id|sltimer_jiffies
)paren
op_ge
l_int|0
)paren
(brace
r_struct
id|list_head
op_star
id|head
comma
op_star
id|curr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sltv1.index
)paren
(brace
r_int
id|n
op_assign
l_int|1
suffix:semicolon
r_do
(brace
id|cascade_sltimers
c_func
(paren
id|sltvecs
(braket
id|n
)braket
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sltvecs
(braket
id|n
)braket
op_member_access_from_pointer
id|index
op_eq
l_int|1
op_logical_and
op_increment
id|n
OL
id|NOOF_SLTVECS
)paren
suffix:semicolon
)brace
id|repeat
suffix:colon
id|head
op_assign
id|sltv1.vec
op_plus
id|sltv1.index
suffix:semicolon
id|curr
op_assign
id|head-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|curr
op_ne
id|head
)paren
(brace
r_struct
id|sltimer_list
op_star
id|timer
suffix:semicolon
r_void
(paren
op_star
id|fn
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
r_int
id|data
suffix:semicolon
id|timer
op_assign
id|list_entry
c_func
(paren
id|curr
comma
r_struct
id|sltimer_list
comma
id|list
)paren
suffix:semicolon
id|fn
op_assign
id|timer-&gt;function
suffix:semicolon
id|data
op_assign
id|timer-&gt;data
suffix:semicolon
id|detach_sltimer
c_func
(paren
id|timer
)paren
suffix:semicolon
id|timer-&gt;list.next
op_assign
id|timer-&gt;list.prev
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|__ip_vs_sltimerlist_lock
)paren
suffix:semicolon
id|fn
c_func
(paren
id|data
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|__ip_vs_sltimerlist_lock
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|sltimer_jiffies
op_add_assign
l_int|1
op_lshift
id|SHIFT_BITS
suffix:semicolon
id|sltv1.index
op_assign
(paren
id|sltv1.index
op_plus
l_int|1
)paren
op_amp
id|TVR_MASK
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|__ip_vs_sltimerlist_lock
)paren
suffix:semicolon
)brace
DECL|variable|slow_timer
r_static
r_struct
id|timer_list
id|slow_timer
suffix:semicolon
multiline_comment|/*&n; *  Slow timer handler is activated every second&n; */
DECL|macro|SLTIMER_PERIOD
mdefine_line|#define SLTIMER_PERIOD&t;     1*HZ
DECL|function|sltimer_handler
r_static
r_void
id|sltimer_handler
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|run_sltimer_list
c_func
(paren
)paren
suffix:semicolon
id|update_defense_level
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ip_vs_dropentry
)paren
)paren
id|ip_vs_random_dropentry
c_func
(paren
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|slow_timer
comma
(paren
id|jiffies
op_plus
id|SLTIMER_PERIOD
)paren
)paren
suffix:semicolon
)brace
DECL|function|ip_vs_sltimer_init
r_void
id|ip_vs_sltimer_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* initialize the slow timer vectors */
id|init_sltimervecs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* initialize the slow timer jiffies and the vector indexes */
id|sltimer_jiffies
op_assign
id|jiffies
suffix:semicolon
id|sltv1.index
op_assign
(paren
id|sltimer_jiffies
op_rshift
id|SHIFT_BITS
)paren
op_amp
id|TVR_MASK
suffix:semicolon
id|sltv2.index
op_assign
(paren
id|sltimer_jiffies
op_rshift
(paren
id|SHIFT_BITS
op_plus
id|TVR_BITS
)paren
)paren
op_amp
id|TVN_MASK
suffix:semicolon
id|sltv3.index
op_assign
(paren
id|sltimer_jiffies
op_rshift
(paren
id|SHIFT_BITS
op_plus
id|TVR_BITS
op_plus
id|TVN_BITS
)paren
)paren
op_amp
id|TVN_MASK
suffix:semicolon
multiline_comment|/* Hook the slow_timer handler in the system timer */
id|init_timer
c_func
(paren
op_amp
id|slow_timer
)paren
suffix:semicolon
id|slow_timer.function
op_assign
id|sltimer_handler
suffix:semicolon
id|slow_timer.expires
op_assign
id|jiffies
op_plus
id|SLTIMER_PERIOD
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|slow_timer
)paren
suffix:semicolon
)brace
DECL|function|ip_vs_sltimer_cleanup
r_void
id|ip_vs_sltimer_cleanup
c_func
(paren
r_void
)paren
(brace
id|del_timer_sync
c_func
(paren
op_amp
id|slow_timer
)paren
suffix:semicolon
)brace
eof
