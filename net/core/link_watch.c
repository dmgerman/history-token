multiline_comment|/*&n; * Linux network device link state notification&n; *&n; * Author:&n; *     Stefan Rompf &lt;sux@loplof.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|enum|lw_bits
r_enum
id|lw_bits
(brace
DECL|enumerator|LW_RUNNING
id|LW_RUNNING
op_assign
l_int|0
comma
DECL|enumerator|LW_SE_USED
id|LW_SE_USED
)brace
suffix:semicolon
DECL|variable|linkwatch_flags
r_static
r_int
r_int
id|linkwatch_flags
suffix:semicolon
DECL|variable|linkwatch_nextevent
r_static
r_int
r_int
id|linkwatch_nextevent
suffix:semicolon
r_static
r_void
id|linkwatch_event
c_func
(paren
r_void
op_star
id|dummy
)paren
suffix:semicolon
r_static
id|DECLARE_WORK
c_func
(paren
id|linkwatch_work
comma
id|linkwatch_event
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|lweventlist
)paren
suffix:semicolon
DECL|variable|lweventlist_lock
r_static
id|spinlock_t
id|lweventlist_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|struct|lw_event
r_struct
id|lw_event
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Avoid kmalloc() for most systems */
DECL|variable|singleevent
r_static
r_struct
id|lw_event
id|singleevent
suffix:semicolon
multiline_comment|/* Must be called with the rtnl semaphore held */
DECL|function|linkwatch_run_queue
r_void
id|linkwatch_run_queue
c_func
(paren
r_void
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|head
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|n
comma
op_star
id|next
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|lweventlist_lock
)paren
suffix:semicolon
id|list_splice_init
c_func
(paren
op_amp
id|lweventlist
comma
op_amp
id|head
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|lweventlist_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|n
comma
id|next
comma
op_amp
id|head
)paren
(brace
r_struct
id|lw_event
op_star
id|event
op_assign
id|list_entry
c_func
(paren
id|n
comma
r_struct
id|lw_event
comma
id|list
)paren
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|event-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|event
op_eq
op_amp
id|singleevent
)paren
(brace
id|clear_bit
c_func
(paren
id|LW_SE_USED
comma
op_amp
id|linkwatch_flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|kfree
c_func
(paren
id|event
)paren
suffix:semicolon
)brace
multiline_comment|/* We are about to handle this device,&n;&t;&t; * so new events can be accepted&n;&t;&t; */
id|clear_bit
c_func
(paren
id|__LINK_STATE_LINKWATCH_PENDING
comma
op_amp
id|dev-&gt;state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
id|netdev_state_change
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
DECL|function|linkwatch_event
r_static
r_void
id|linkwatch_event
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
multiline_comment|/* Limit the number of linkwatch events to one&n;&t; * per second so that a runaway driver does not&n;&t; * cause a storm of messages on the netlink&n;&t; * socket&n;&t; */
id|linkwatch_nextevent
op_assign
id|jiffies
op_plus
id|HZ
suffix:semicolon
id|clear_bit
c_func
(paren
id|LW_RUNNING
comma
op_amp
id|linkwatch_flags
)paren
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
id|linkwatch_run_queue
c_func
(paren
)paren
suffix:semicolon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|linkwatch_fire_event
r_void
id|linkwatch_fire_event
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|__LINK_STATE_LINKWATCH_PENDING
comma
op_amp
id|dev-&gt;state
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|lw_event
op_star
id|event
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|LW_SE_USED
comma
op_amp
id|linkwatch_flags
)paren
)paren
(brace
id|event
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|lw_event
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|event
op_eq
l_int|NULL
)paren
)paren
(brace
id|clear_bit
c_func
(paren
id|__LINK_STATE_LINKWATCH_PENDING
comma
op_amp
id|dev-&gt;state
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_else
(brace
id|event
op_assign
op_amp
id|singleevent
suffix:semicolon
)brace
id|dev_hold
c_func
(paren
id|dev
)paren
suffix:semicolon
id|event-&gt;dev
op_assign
id|dev
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lweventlist_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|event-&gt;list
comma
op_amp
id|lweventlist
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lweventlist_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|LW_RUNNING
comma
op_amp
id|linkwatch_flags
)paren
)paren
(brace
r_int
r_int
id|thisevent
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|thisevent
op_ge
id|linkwatch_nextevent
)paren
(brace
id|schedule_work
c_func
(paren
op_amp
id|linkwatch_work
)paren
suffix:semicolon
)brace
r_else
(brace
id|schedule_delayed_work
c_func
(paren
op_amp
id|linkwatch_work
comma
id|linkwatch_nextevent
op_minus
id|thisevent
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|variable|linkwatch_fire_event
id|EXPORT_SYMBOL
c_func
(paren
id|linkwatch_fire_event
)paren
suffix:semicolon
eof
