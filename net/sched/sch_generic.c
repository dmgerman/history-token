multiline_comment|/*&n; * net/sched/sch_generic.c&t;Generic packet scheduler routines.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *              Jamal Hadi Salim, &lt;hadi@cyberus.ca&gt; 990601&n; *              - Ingress support&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
multiline_comment|/* Main transmission queue. */
multiline_comment|/* Main qdisc structure lock. &n;&n;   However, modifications&n;   to data, participating in scheduling must be additionally&n;   protected with dev-&gt;queue_lock spinlock.&n;&n;   The idea is the following:&n;   - enqueue, dequeue are serialized via top level device&n;     spinlock dev-&gt;queue_lock.&n;   - tree walking is protected by read_lock(qdisc_tree_lock)&n;     and this lock is used only in process context.&n;   - updates to tree are made only under rtnl semaphore,&n;     hence this lock may be made without local bh disabling.&n;&n;   qdisc_tree_lock must be grabbed BEFORE dev-&gt;queue_lock!&n; */
DECL|variable|qdisc_tree_lock
id|rwlock_t
id|qdisc_tree_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* &n;   dev-&gt;queue_lock serializes queue accesses for this device&n;   AND dev-&gt;qdisc pointer itself.&n;&n;   dev-&gt;xmit_lock serializes accesses to device driver.&n;&n;   dev-&gt;queue_lock and dev-&gt;xmit_lock are mutually exclusive,&n;   if one is grabbed, another must be free.&n; */
multiline_comment|/* Kick device.&n;   Note, that this procedure can be called by a watchdog timer, so that&n;   we do not check dev-&gt;tbusy flag here.&n;&n;   Returns:  0  - queue is empty.&n;            &gt;0  - queue is not empty, but throttled.&n;&t;    &lt;0  - queue is not empty. Device is throttled, if dev-&gt;tbusy != 0.&n;&n;   NOTE: Called under dev-&gt;queue_lock with locally disabled BH.&n;*/
DECL|function|qdisc_restart
r_int
id|qdisc_restart
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|Qdisc
op_star
id|q
op_assign
id|dev-&gt;qdisc
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* Dequeue packet */
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|q
op_member_access_from_pointer
id|dequeue
c_func
(paren
id|q
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|spin_trylock
c_func
(paren
op_amp
id|dev-&gt;xmit_lock
)paren
)paren
(brace
multiline_comment|/* Remember that the driver is grabbed by us. */
id|dev-&gt;xmit_lock_owner
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* And release queue */
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|netif_queue_stopped
c_func
(paren
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|netdev_nit
)paren
id|dev_queue_xmit_nit
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
id|hard_start_xmit
c_func
(paren
id|skb
comma
id|dev
)paren
op_eq
l_int|0
)paren
(brace
id|dev-&gt;xmit_lock_owner
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;xmit_lock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* Release the driver */
id|dev-&gt;xmit_lock_owner
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;xmit_lock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|q
op_assign
id|dev-&gt;qdisc
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* So, someone grabbed the driver. */
multiline_comment|/* It may be transient configuration error,&n;&t;&t;&t;   when hard_start_xmit() recurses. We detect&n;&t;&t;&t;   it by checking xmit owner and drop the&n;&t;&t;&t;   packet when deadloop is detected.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;xmit_lock_owner
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Dead loop on netdevice %s, fix it urgently!&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|__get_cpu_var
c_func
(paren
id|netdev_rx_stat
)paren
dot
id|cpu_collision
op_increment
suffix:semicolon
)brace
multiline_comment|/* Device kicked us out :(&n;&t;&t;   This is possible in three cases:&n;&n;&t;&t;   0. driver is locked&n;&t;&t;   1. fastroute is enabled&n;&t;&t;   2. device cannot determine busy state&n;&t;&t;      before start of transmission (f.e. dialout)&n;&t;&t;   3. device is buggy (ppp)&n;&t;&t; */
id|q-&gt;ops
op_member_access_from_pointer
id|requeue
c_func
(paren
id|skb
comma
id|q
)paren
suffix:semicolon
id|netif_schedule
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|q-&gt;q.qlen
suffix:semicolon
)brace
DECL|function|dev_watchdog
r_static
r_void
id|dev_watchdog
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|arg
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;xmit_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;qdisc
op_ne
op_amp
id|noop_qdisc
)paren
(brace
r_if
c_cond
(paren
id|netif_device_present
c_func
(paren
id|dev
)paren
op_logical_and
id|netif_running
c_func
(paren
id|dev
)paren
op_logical_and
id|netif_carrier_ok
c_func
(paren
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|netif_queue_stopped
c_func
(paren
id|dev
)paren
op_logical_and
(paren
id|jiffies
op_minus
id|dev-&gt;trans_start
)paren
OG
id|dev-&gt;watchdog_timeo
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NETDEV WATCHDOG: %s: transmit timed out&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev
op_member_access_from_pointer
id|tx_timeout
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|dev-&gt;watchdog_timer
comma
id|jiffies
op_plus
id|dev-&gt;watchdog_timeo
)paren
)paren
id|dev_hold
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;xmit_lock
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|dev_watchdog_init
r_static
r_void
id|dev_watchdog_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|dev-&gt;watchdog_timer
)paren
suffix:semicolon
id|dev-&gt;watchdog_timer.data
op_assign
(paren
r_int
r_int
)paren
id|dev
suffix:semicolon
id|dev-&gt;watchdog_timer.function
op_assign
id|dev_watchdog
suffix:semicolon
)brace
DECL|function|__netdev_watchdog_up
r_void
id|__netdev_watchdog_up
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
id|dev-&gt;tx_timeout
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;watchdog_timeo
op_le
l_int|0
)paren
id|dev-&gt;watchdog_timeo
op_assign
l_int|5
op_star
id|HZ
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|dev-&gt;watchdog_timer
comma
id|jiffies
op_plus
id|dev-&gt;watchdog_timeo
)paren
)paren
id|dev_hold
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
DECL|function|dev_watchdog_up
r_static
r_void
id|dev_watchdog_up
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;xmit_lock
)paren
suffix:semicolon
id|__netdev_watchdog_up
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;xmit_lock
)paren
suffix:semicolon
)brace
DECL|function|dev_watchdog_down
r_static
r_void
id|dev_watchdog_down
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;xmit_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|del_timer
c_func
(paren
op_amp
id|dev-&gt;watchdog_timer
)paren
)paren
id|__dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;xmit_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* &quot;NOOP&quot; scheduler: the best scheduler, recommended for all interfaces&n;   under all circumstances. It is difficult to invent anything faster or&n;   cheaper.&n; */
r_static
r_int
DECL|function|noop_enqueue
id|noop_enqueue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|Qdisc
op_star
id|qdisc
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_XMIT_CN
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|noop_dequeue
id|noop_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|qdisc
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_int
DECL|function|noop_requeue
id|noop_requeue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|Qdisc
op_star
id|qdisc
)paren
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s deferred output. It is buggy.&bslash;n&quot;
comma
id|skb-&gt;dev-&gt;name
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_XMIT_CN
suffix:semicolon
)brace
DECL|variable|noop_qdisc_ops
r_struct
id|Qdisc_ops
id|noop_qdisc_ops
op_assign
(brace
dot
id|next
op_assign
l_int|NULL
comma
dot
id|cl_ops
op_assign
l_int|NULL
comma
dot
id|id
op_assign
l_string|&quot;noop&quot;
comma
dot
id|priv_size
op_assign
l_int|0
comma
dot
id|enqueue
op_assign
id|noop_enqueue
comma
dot
id|dequeue
op_assign
id|noop_dequeue
comma
dot
id|requeue
op_assign
id|noop_requeue
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|variable|noop_qdisc
r_struct
id|Qdisc
id|noop_qdisc
op_assign
(brace
dot
id|enqueue
op_assign
id|noop_enqueue
comma
dot
id|dequeue
op_assign
id|noop_dequeue
comma
dot
id|flags
op_assign
id|TCQ_F_BUILTIN
comma
dot
id|ops
op_assign
op_amp
id|noop_qdisc_ops
comma
)brace
suffix:semicolon
DECL|variable|noqueue_qdisc_ops
r_struct
id|Qdisc_ops
id|noqueue_qdisc_ops
op_assign
(brace
dot
id|next
op_assign
l_int|NULL
comma
dot
id|cl_ops
op_assign
l_int|NULL
comma
dot
id|id
op_assign
l_string|&quot;noqueue&quot;
comma
dot
id|priv_size
op_assign
l_int|0
comma
dot
id|enqueue
op_assign
id|noop_enqueue
comma
dot
id|dequeue
op_assign
id|noop_dequeue
comma
dot
id|requeue
op_assign
id|noop_requeue
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|variable|noqueue_qdisc
r_struct
id|Qdisc
id|noqueue_qdisc
op_assign
(brace
dot
id|enqueue
op_assign
l_int|NULL
comma
dot
id|dequeue
op_assign
id|noop_dequeue
comma
dot
id|flags
op_assign
id|TCQ_F_BUILTIN
comma
dot
id|ops
op_assign
op_amp
id|noqueue_qdisc_ops
comma
)brace
suffix:semicolon
DECL|variable|prio2band
r_static
r_const
id|u8
id|prio2band
(braket
id|TC_PRIO_MAX
op_plus
l_int|1
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|1
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
multiline_comment|/* 3-band FIFO queue: old style, but should be a bit faster than&n;   generic prio+fifo combination.&n; */
r_static
r_int
DECL|function|pfifo_fast_enqueue
id|pfifo_fast_enqueue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|Qdisc
op_star
id|qdisc
)paren
(brace
r_struct
id|sk_buff_head
op_star
id|list
suffix:semicolon
id|list
op_assign
(paren
(paren
r_struct
id|sk_buff_head
op_star
)paren
id|qdisc-&gt;data
)paren
op_plus
id|prio2band
(braket
id|skb-&gt;priority
op_amp
id|TC_PRIO_MAX
)braket
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;qlen
op_le
id|qdisc-&gt;dev-&gt;tx_queue_len
)paren
(brace
id|__skb_queue_tail
c_func
(paren
id|list
comma
id|skb
)paren
suffix:semicolon
id|qdisc-&gt;q.qlen
op_increment
suffix:semicolon
id|qdisc-&gt;stats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|qdisc-&gt;stats.packets
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|qdisc-&gt;stats.drops
op_increment
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_XMIT_DROP
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|pfifo_fast_dequeue
id|pfifo_fast_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|qdisc
)paren
(brace
r_int
id|prio
suffix:semicolon
r_struct
id|sk_buff_head
op_star
id|list
op_assign
(paren
(paren
r_struct
id|sk_buff_head
op_star
)paren
id|qdisc-&gt;data
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_for
c_loop
(paren
id|prio
op_assign
l_int|0
suffix:semicolon
id|prio
OL
l_int|3
suffix:semicolon
id|prio
op_increment
comma
id|list
op_increment
)paren
(brace
id|skb
op_assign
id|__skb_dequeue
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|qdisc-&gt;q.qlen
op_decrement
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_int
DECL|function|pfifo_fast_requeue
id|pfifo_fast_requeue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|Qdisc
op_star
id|qdisc
)paren
(brace
r_struct
id|sk_buff_head
op_star
id|list
suffix:semicolon
id|list
op_assign
(paren
(paren
r_struct
id|sk_buff_head
op_star
)paren
id|qdisc-&gt;data
)paren
op_plus
id|prio2band
(braket
id|skb-&gt;priority
op_amp
id|TC_PRIO_MAX
)braket
suffix:semicolon
id|__skb_queue_head
c_func
(paren
id|list
comma
id|skb
)paren
suffix:semicolon
id|qdisc-&gt;q.qlen
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|pfifo_fast_reset
id|pfifo_fast_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|qdisc
)paren
(brace
r_int
id|prio
suffix:semicolon
r_struct
id|sk_buff_head
op_star
id|list
op_assign
(paren
(paren
r_struct
id|sk_buff_head
op_star
)paren
id|qdisc-&gt;data
)paren
suffix:semicolon
r_for
c_loop
(paren
id|prio
op_assign
l_int|0
suffix:semicolon
id|prio
OL
l_int|3
suffix:semicolon
id|prio
op_increment
)paren
id|skb_queue_purge
c_func
(paren
id|list
op_plus
id|prio
)paren
suffix:semicolon
id|qdisc-&gt;q.qlen
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|pfifo_fast_dump
r_static
r_int
id|pfifo_fast_dump
c_func
(paren
r_struct
id|Qdisc
op_star
id|qdisc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
suffix:semicolon
r_struct
id|tc_prio_qopt
id|opt
suffix:semicolon
id|opt.bands
op_assign
l_int|3
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|opt.priomap
comma
id|prio2band
comma
id|TC_PRIO_MAX
op_plus
l_int|1
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_OPTIONS
comma
r_sizeof
(paren
id|opt
)paren
comma
op_amp
id|opt
)paren
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
id|rtattr_failure
suffix:colon
id|skb_trim
c_func
(paren
id|skb
comma
id|b
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|pfifo_fast_init
r_static
r_int
id|pfifo_fast_init
c_func
(paren
r_struct
id|Qdisc
op_star
id|qdisc
comma
r_struct
id|rtattr
op_star
id|opt
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|sk_buff_head
op_star
id|list
suffix:semicolon
id|list
op_assign
(paren
(paren
r_struct
id|sk_buff_head
op_star
)paren
id|qdisc-&gt;data
)paren
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
id|skb_queue_head_init
c_func
(paren
id|list
op_plus
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pfifo_fast_ops
r_static
r_struct
id|Qdisc_ops
id|pfifo_fast_ops
op_assign
(brace
dot
id|next
op_assign
l_int|NULL
comma
dot
id|cl_ops
op_assign
l_int|NULL
comma
dot
id|id
op_assign
l_string|&quot;pfifo_fast&quot;
comma
dot
id|priv_size
op_assign
l_int|3
op_star
r_sizeof
(paren
r_struct
id|sk_buff_head
)paren
comma
dot
id|enqueue
op_assign
id|pfifo_fast_enqueue
comma
dot
id|dequeue
op_assign
id|pfifo_fast_dequeue
comma
dot
id|requeue
op_assign
id|pfifo_fast_requeue
comma
dot
id|init
op_assign
id|pfifo_fast_init
comma
dot
id|reset
op_assign
id|pfifo_fast_reset
comma
dot
id|dump
op_assign
id|pfifo_fast_dump
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|qdisc_create_dflt
r_struct
id|Qdisc
op_star
id|qdisc_create_dflt
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|Qdisc_ops
op_star
id|ops
)paren
(brace
r_struct
id|Qdisc
op_star
id|sch
suffix:semicolon
r_int
id|size
op_assign
r_sizeof
(paren
op_star
id|sch
)paren
op_plus
id|ops-&gt;priv_size
suffix:semicolon
id|sch
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sch
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|sch
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|sch-&gt;q
)paren
suffix:semicolon
id|sch-&gt;ops
op_assign
id|ops
suffix:semicolon
id|sch-&gt;enqueue
op_assign
id|ops-&gt;enqueue
suffix:semicolon
id|sch-&gt;dequeue
op_assign
id|ops-&gt;dequeue
suffix:semicolon
id|sch-&gt;dev
op_assign
id|dev
suffix:semicolon
id|sch-&gt;stats.lock
op_assign
op_amp
id|dev-&gt;queue_lock
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|sch-&gt;refcnt
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ops-&gt;init
op_logical_or
id|ops
op_member_access_from_pointer
id|init
c_func
(paren
id|sch
comma
l_int|NULL
)paren
op_eq
l_int|0
)paren
r_return
id|sch
suffix:semicolon
id|kfree
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Under dev-&gt;queue_lock and BH! */
DECL|function|qdisc_reset
r_void
id|qdisc_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|qdisc
)paren
(brace
r_struct
id|Qdisc_ops
op_star
id|ops
op_assign
id|qdisc-&gt;ops
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;reset
)paren
id|ops
op_member_access_from_pointer
id|reset
c_func
(paren
id|qdisc
)paren
suffix:semicolon
)brace
multiline_comment|/* Under dev-&gt;queue_lock and BH! */
DECL|function|qdisc_destroy
r_void
id|qdisc_destroy
c_func
(paren
r_struct
id|Qdisc
op_star
id|qdisc
)paren
(brace
r_struct
id|Qdisc_ops
op_star
id|ops
op_assign
id|qdisc-&gt;ops
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_dec_and_test
c_func
(paren
op_amp
id|qdisc-&gt;refcnt
)paren
)paren
r_return
suffix:semicolon
id|dev
op_assign
id|qdisc-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
r_struct
id|Qdisc
op_star
id|q
comma
op_star
op_star
id|qp
suffix:semicolon
r_for
c_loop
(paren
id|qp
op_assign
op_amp
id|qdisc-&gt;dev-&gt;qdisc_list
suffix:semicolon
(paren
id|q
op_assign
op_star
id|qp
)paren
op_ne
l_int|NULL
suffix:semicolon
id|qp
op_assign
op_amp
id|q-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|q
op_eq
id|qdisc
)paren
(brace
op_star
id|qp
op_assign
id|q-&gt;next
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
macro_line|#ifdef CONFIG_NET_ESTIMATOR
id|qdisc_kill_estimator
c_func
(paren
op_amp
id|qdisc-&gt;stats
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ops-&gt;reset
)paren
id|ops
op_member_access_from_pointer
id|reset
c_func
(paren
id|qdisc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops-&gt;destroy
)paren
id|ops
op_member_access_from_pointer
id|destroy
c_func
(paren
id|qdisc
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|ops-&gt;owner
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|qdisc-&gt;flags
op_amp
id|TCQ_F_BUILTIN
)paren
)paren
id|kfree
c_func
(paren
id|qdisc
)paren
suffix:semicolon
)brace
DECL|function|dev_activate
r_void
id|dev_activate
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* No queueing discipline is attached to device;&n;&t;   create default one i.e. pfifo_fast for devices,&n;&t;   which need queueing and noqueue_qdisc for&n;&t;   virtual interfaces&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;qdisc_sleeping
op_eq
op_amp
id|noop_qdisc
)paren
(brace
r_struct
id|Qdisc
op_star
id|qdisc
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;tx_queue_len
)paren
(brace
id|qdisc
op_assign
id|qdisc_create_dflt
c_func
(paren
id|dev
comma
op_amp
id|pfifo_fast_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qdisc
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: activation failed&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|write_lock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
id|qdisc-&gt;next
op_assign
id|dev-&gt;qdisc_list
suffix:semicolon
id|dev-&gt;qdisc_list
op_assign
id|qdisc
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
)brace
r_else
(brace
id|qdisc
op_assign
op_amp
id|noqueue_qdisc
suffix:semicolon
)brace
id|write_lock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
id|dev-&gt;qdisc_sleeping
op_assign
id|qdisc
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
)brace
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;qdisc
op_assign
id|dev-&gt;qdisc_sleeping
)paren
op_ne
op_amp
id|noqueue_qdisc
)paren
(brace
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|dev_watchdog_up
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
)brace
DECL|function|dev_deactivate
r_void
id|dev_deactivate
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|Qdisc
op_star
id|qdisc
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|qdisc
op_assign
id|dev-&gt;qdisc
suffix:semicolon
id|dev-&gt;qdisc
op_assign
op_amp
id|noop_qdisc
suffix:semicolon
id|qdisc_reset
c_func
(paren
id|qdisc
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|dev_watchdog_down
c_func
(paren
id|dev
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|__LINK_STATE_SCHED
comma
op_amp
id|dev-&gt;state
)paren
)paren
id|yield
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_wait
c_func
(paren
op_amp
id|dev-&gt;xmit_lock
)paren
suffix:semicolon
)brace
DECL|function|dev_init_scheduler
r_void
id|dev_init_scheduler
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|dev-&gt;qdisc
op_assign
op_amp
id|noop_qdisc
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|dev-&gt;qdisc_sleeping
op_assign
op_amp
id|noop_qdisc
suffix:semicolon
id|dev-&gt;qdisc_list
op_assign
l_int|NULL
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
id|dev_watchdog_init
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|dev_shutdown
r_void
id|dev_shutdown
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|Qdisc
op_star
id|qdisc
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|qdisc
op_assign
id|dev-&gt;qdisc_sleeping
suffix:semicolon
id|dev-&gt;qdisc
op_assign
op_amp
id|noop_qdisc
suffix:semicolon
id|dev-&gt;qdisc_sleeping
op_assign
op_amp
id|noop_qdisc
suffix:semicolon
id|qdisc_destroy
c_func
(paren
id|qdisc
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_NET_SCH_INGRESS) || defined(CONFIG_NET_SCH_INGRESS_MODULE)
r_if
c_cond
(paren
(paren
id|qdisc
op_assign
id|dev-&gt;qdisc_ingress
)paren
op_ne
l_int|NULL
)paren
(brace
id|dev-&gt;qdisc_ingress
op_assign
l_int|NULL
suffix:semicolon
id|qdisc_destroy
c_func
(paren
id|qdisc
)paren
suffix:semicolon
)brace
macro_line|#endif
id|BUG_TRAP
c_func
(paren
id|dev-&gt;qdisc_list
op_eq
l_int|NULL
)paren
suffix:semicolon
id|BUG_TRAP
c_func
(paren
op_logical_neg
id|timer_pending
c_func
(paren
op_amp
id|dev-&gt;watchdog_timer
)paren
)paren
suffix:semicolon
id|dev-&gt;qdisc_list
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
)brace
eof
