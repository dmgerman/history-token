multiline_comment|/* net/sched/sch_teql.c&t;&quot;True&quot; (or &quot;trivial&quot;) link equalizer.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
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
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
multiline_comment|/*&n;   How to setup it.&n;   ----------------&n;&n;   After loading this module you will find a new device teqlN&n;   and new qdisc with the same name. To join a slave to the equalizer&n;   you should just set this qdisc on a device f.e.&n;&n;   # tc qdisc add dev eth0 root teql0&n;   # tc qdisc add dev eth1 root teql0&n;&n;   That&squot;s all. Full PnP 8)&n;&n;   Applicability.&n;   --------------&n;&n;   1. Slave devices MUST be active devices, i.e., they must raise the tbusy&n;      signal and generate EOI events. If you want to equalize virtual devices&n;      like tunnels, use a normal eql device.&n;   2. This device puts no limitations on physical slave characteristics&n;      f.e. it will equalize 9600baud line and 100Mb ethernet perfectly :-)&n;      Certainly, large difference in link speeds will make the resulting&n;      eqalized link unusable, because of huge packet reordering.&n;      I estimate an upper useful difference as ~10 times.&n;   3. If the slave requires address resolution, only protocols using&n;      neighbour cache (IPv4/IPv6) will work over the equalized link.&n;      Other protocols are still allowed to use the slave device directly,&n;      which will not break load balancing, though native slave&n;      traffic will have the highest priority.  */
DECL|struct|teql_master
r_struct
id|teql_master
(brace
DECL|member|qops
r_struct
id|Qdisc_ops
id|qops
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|slaves
r_struct
id|Qdisc
op_star
id|slaves
suffix:semicolon
DECL|member|master_list
r_struct
id|list_head
id|master_list
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|teql_sched_data
r_struct
id|teql_sched_data
(brace
DECL|member|next
r_struct
id|Qdisc
op_star
id|next
suffix:semicolon
DECL|member|m
r_struct
id|teql_master
op_star
id|m
suffix:semicolon
DECL|member|ncache
r_struct
id|neighbour
op_star
id|ncache
suffix:semicolon
DECL|member|q
r_struct
id|sk_buff_head
id|q
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NEXT_SLAVE
mdefine_line|#define NEXT_SLAVE(q) (((struct teql_sched_data*)qdisc_priv(q))-&gt;next)
DECL|macro|FMASK
mdefine_line|#define FMASK (IFF_BROADCAST|IFF_POINTOPOINT|IFF_BROADCAST)
multiline_comment|/* &quot;teql*&quot; qdisc routines */
r_static
r_int
DECL|function|teql_enqueue
id|teql_enqueue
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
id|sch
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|sch-&gt;dev
suffix:semicolon
r_struct
id|teql_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
id|__skb_queue_tail
c_func
(paren
op_amp
id|q-&gt;q
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;q.qlen
op_le
id|dev-&gt;tx_queue_len
)paren
(brace
id|sch-&gt;stats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;stats.packets
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__skb_unlink
c_func
(paren
id|skb
comma
op_amp
id|q-&gt;q
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|sch-&gt;stats.drops
op_increment
suffix:semicolon
r_return
id|NET_XMIT_DROP
suffix:semicolon
)brace
r_static
r_int
DECL|function|teql_requeue
id|teql_requeue
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
id|sch
)paren
(brace
r_struct
id|teql_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
id|__skb_queue_head
c_func
(paren
op_amp
id|q-&gt;q
comma
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|teql_dequeue
id|teql_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|teql_sched_data
op_star
id|dat
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|skb
op_assign
id|__skb_dequeue
c_func
(paren
op_amp
id|dat-&gt;q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
r_struct
id|net_device
op_star
id|m
op_assign
id|dat-&gt;m-&gt;dev-&gt;qdisc-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|m
)paren
(brace
id|dat-&gt;m-&gt;slaves
op_assign
id|sch
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|m
)paren
suffix:semicolon
)brace
)brace
id|sch-&gt;q.qlen
op_assign
id|dat-&gt;q.qlen
op_plus
id|dat-&gt;m-&gt;dev-&gt;qdisc-&gt;q.qlen
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|teql_neigh_release
id|teql_neigh_release
c_func
(paren
r_struct
id|neighbour
op_star
id|n
)paren
(brace
r_if
c_cond
(paren
id|n
)paren
id|neigh_release
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|teql_reset
id|teql_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|teql_sched_data
op_star
id|dat
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
id|skb_queue_purge
c_func
(paren
op_amp
id|dat-&gt;q
)paren
suffix:semicolon
id|sch-&gt;q.qlen
op_assign
l_int|0
suffix:semicolon
id|teql_neigh_release
c_func
(paren
id|xchg
c_func
(paren
op_amp
id|dat-&gt;ncache
comma
l_int|NULL
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|teql_destroy
id|teql_destroy
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|Qdisc
op_star
id|q
comma
op_star
id|prev
suffix:semicolon
r_struct
id|teql_sched_data
op_star
id|dat
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_struct
id|teql_master
op_star
id|master
op_assign
id|dat-&gt;m
suffix:semicolon
r_if
c_cond
(paren
(paren
id|prev
op_assign
id|master-&gt;slaves
)paren
op_ne
l_int|NULL
)paren
(brace
r_do
(brace
id|q
op_assign
id|NEXT_SLAVE
c_func
(paren
id|prev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q
op_eq
id|sch
)paren
(brace
id|NEXT_SLAVE
c_func
(paren
id|prev
)paren
op_assign
id|NEXT_SLAVE
c_func
(paren
id|q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q
op_eq
id|master-&gt;slaves
)paren
(brace
id|master-&gt;slaves
op_assign
id|NEXT_SLAVE
c_func
(paren
id|q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q
op_eq
id|master-&gt;slaves
)paren
(brace
id|master-&gt;slaves
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|master-&gt;dev-&gt;queue_lock
)paren
suffix:semicolon
id|qdisc_reset
c_func
(paren
id|master-&gt;dev-&gt;qdisc
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|master-&gt;dev-&gt;queue_lock
)paren
suffix:semicolon
)brace
)brace
id|skb_queue_purge
c_func
(paren
op_amp
id|dat-&gt;q
)paren
suffix:semicolon
id|teql_neigh_release
c_func
(paren
id|xchg
c_func
(paren
op_amp
id|dat-&gt;ncache
comma
l_int|NULL
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
id|prev
op_assign
id|q
)paren
op_ne
id|master-&gt;slaves
)paren
suffix:semicolon
)brace
)brace
DECL|function|teql_qdisc_init
r_static
r_int
id|teql_qdisc_init
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_struct
id|rtattr
op_star
id|opt
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|sch-&gt;dev
suffix:semicolon
r_struct
id|teql_master
op_star
id|m
op_assign
(paren
r_struct
id|teql_master
op_star
)paren
id|sch-&gt;ops
suffix:semicolon
r_struct
id|teql_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;hard_header_len
OG
id|m-&gt;dev-&gt;hard_header_len
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;dev
op_eq
id|dev
)paren
r_return
op_minus
id|ELOOP
suffix:semicolon
id|q-&gt;m
op_assign
id|m
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|q-&gt;q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;slaves
)paren
(brace
r_if
c_cond
(paren
id|m-&gt;dev-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
r_if
c_cond
(paren
(paren
id|m-&gt;dev-&gt;flags
op_amp
id|IFF_POINTOPOINT
op_logical_and
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|IFF_POINTOPOINT
)paren
)paren
op_logical_or
(paren
id|m-&gt;dev-&gt;flags
op_amp
id|IFF_BROADCAST
op_logical_and
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|IFF_BROADCAST
)paren
)paren
op_logical_or
(paren
id|m-&gt;dev-&gt;flags
op_amp
id|IFF_MULTICAST
op_logical_and
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|IFF_MULTICAST
)paren
)paren
op_logical_or
id|dev-&gt;mtu
OL
id|m-&gt;dev-&gt;mtu
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|IFF_POINTOPOINT
)paren
)paren
id|m-&gt;dev-&gt;flags
op_and_assign
op_complement
id|IFF_POINTOPOINT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|IFF_BROADCAST
)paren
)paren
id|m-&gt;dev-&gt;flags
op_and_assign
op_complement
id|IFF_BROADCAST
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|IFF_MULTICAST
)paren
)paren
id|m-&gt;dev-&gt;flags
op_and_assign
op_complement
id|IFF_MULTICAST
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mtu
OL
id|m-&gt;dev-&gt;mtu
)paren
id|m-&gt;dev-&gt;mtu
op_assign
id|dev-&gt;mtu
suffix:semicolon
)brace
id|q-&gt;next
op_assign
id|NEXT_SLAVE
c_func
(paren
id|m-&gt;slaves
)paren
suffix:semicolon
id|NEXT_SLAVE
c_func
(paren
id|m-&gt;slaves
)paren
op_assign
id|sch
suffix:semicolon
)brace
r_else
(brace
id|q-&gt;next
op_assign
id|sch
suffix:semicolon
id|m-&gt;slaves
op_assign
id|sch
suffix:semicolon
id|m-&gt;dev-&gt;mtu
op_assign
id|dev-&gt;mtu
suffix:semicolon
id|m-&gt;dev-&gt;flags
op_assign
(paren
id|m-&gt;dev-&gt;flags
op_amp
op_complement
id|FMASK
)paren
op_or
(paren
id|dev-&gt;flags
op_amp
id|FMASK
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &quot;teql*&quot; netdevice routines */
r_static
r_int
DECL|function|__teql_resolve
id|__teql_resolve
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|sk_buff
op_star
id|skb_res
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|teql_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|dev-&gt;qdisc
)paren
suffix:semicolon
r_struct
id|neighbour
op_star
id|mn
op_assign
id|skb-&gt;dst-&gt;neighbour
suffix:semicolon
r_struct
id|neighbour
op_star
id|n
op_assign
id|q-&gt;ncache
suffix:semicolon
r_if
c_cond
(paren
id|mn-&gt;tbl
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|n
op_logical_and
id|n-&gt;tbl
op_eq
id|mn-&gt;tbl
op_logical_and
id|memcmp
c_func
(paren
id|n-&gt;primary_key
comma
id|mn-&gt;primary_key
comma
id|mn-&gt;tbl-&gt;key_len
)paren
op_eq
l_int|0
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|n-&gt;refcnt
)paren
suffix:semicolon
)brace
r_else
(brace
id|n
op_assign
id|__neigh_lookup_errno
c_func
(paren
id|mn-&gt;tbl
comma
id|mn-&gt;primary_key
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|n
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|neigh_event_send
c_func
(paren
id|n
comma
id|skb_res
)paren
op_eq
l_int|0
)paren
(brace
r_int
id|err
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|n-&gt;lock
)paren
suffix:semicolon
id|err
op_assign
id|dev
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|skb
comma
id|dev
comma
id|ntohs
c_func
(paren
id|skb-&gt;protocol
)paren
comma
id|n-&gt;ha
comma
l_int|NULL
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|n-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|neigh_release
c_func
(paren
id|n
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|teql_neigh_release
c_func
(paren
id|xchg
c_func
(paren
op_amp
id|q-&gt;ncache
comma
id|n
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|neigh_release
c_func
(paren
id|n
)paren
suffix:semicolon
r_return
(paren
id|skb_res
op_eq
l_int|NULL
)paren
ques
c_cond
op_minus
id|EAGAIN
suffix:colon
l_int|1
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|teql_resolve
id|teql_resolve
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|sk_buff
op_star
id|skb_res
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;hard_header
op_eq
l_int|NULL
op_logical_or
id|skb-&gt;dst
op_eq
l_int|NULL
op_logical_or
id|skb-&gt;dst-&gt;neighbour
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|__teql_resolve
c_func
(paren
id|skb
comma
id|skb_res
comma
id|dev
)paren
suffix:semicolon
)brace
DECL|function|teql_master_xmit
r_static
r_int
id|teql_master_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|teql_master
op_star
id|master
op_assign
(paren
r_void
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|Qdisc
op_star
id|start
comma
op_star
id|q
suffix:semicolon
r_int
id|busy
suffix:semicolon
r_int
id|nores
suffix:semicolon
r_int
id|len
op_assign
id|skb-&gt;len
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb_res
op_assign
l_int|NULL
suffix:semicolon
id|start
op_assign
id|master-&gt;slaves
suffix:semicolon
id|restart
suffix:colon
id|nores
op_assign
l_int|0
suffix:semicolon
id|busy
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|q
op_assign
id|start
)paren
op_eq
l_int|NULL
)paren
r_goto
id|drop
suffix:semicolon
r_do
(brace
r_struct
id|net_device
op_star
id|slave
op_assign
id|q-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|slave-&gt;qdisc_sleeping
op_ne
id|q
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|netif_queue_stopped
c_func
(paren
id|slave
)paren
op_logical_or
op_logical_neg
id|netif_running
c_func
(paren
id|slave
)paren
)paren
(brace
id|busy
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|teql_resolve
c_func
(paren
id|skb
comma
id|skb_res
comma
id|slave
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|spin_trylock
c_func
(paren
op_amp
id|slave-&gt;xmit_lock
)paren
)paren
(brace
id|slave-&gt;xmit_lock_owner
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|netif_queue_stopped
c_func
(paren
id|slave
)paren
op_logical_and
id|slave
op_member_access_from_pointer
id|hard_start_xmit
c_func
(paren
id|skb
comma
id|slave
)paren
op_eq
l_int|0
)paren
(brace
id|slave-&gt;xmit_lock_owner
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|slave-&gt;xmit_lock
)paren
suffix:semicolon
id|master-&gt;slaves
op_assign
id|NEXT_SLAVE
c_func
(paren
id|q
)paren
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|master-&gt;stats.tx_packets
op_increment
suffix:semicolon
id|master-&gt;stats.tx_bytes
op_add_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|slave-&gt;xmit_lock_owner
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|slave-&gt;xmit_lock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|netif_queue_stopped
c_func
(paren
id|dev
)paren
)paren
id|busy
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|master-&gt;slaves
op_assign
id|NEXT_SLAVE
c_func
(paren
id|q
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|nores
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|__skb_pull
c_func
(paren
id|skb
comma
id|skb-&gt;nh.raw
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|q
op_assign
id|NEXT_SLAVE
c_func
(paren
id|q
)paren
)paren
op_ne
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nores
op_logical_and
id|skb_res
op_eq
l_int|NULL
)paren
(brace
id|skb_res
op_assign
id|skb
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
r_if
c_cond
(paren
id|busy
)paren
(brace
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|master-&gt;stats.tx_errors
op_increment
suffix:semicolon
id|drop
suffix:colon
id|master-&gt;stats.tx_dropped
op_increment
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|teql_master_open
r_static
r_int
id|teql_master_open
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
suffix:semicolon
r_struct
id|teql_master
op_star
id|m
op_assign
(paren
r_void
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|mtu
op_assign
l_int|0xFFFE
suffix:semicolon
r_int
id|flags
op_assign
id|IFF_NOARP
op_or
id|IFF_MULTICAST
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;slaves
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EUNATCH
suffix:semicolon
id|flags
op_assign
id|FMASK
suffix:semicolon
id|q
op_assign
id|m-&gt;slaves
suffix:semicolon
r_do
(brace
r_struct
id|net_device
op_star
id|slave
op_assign
id|q-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|slave
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EUNATCH
suffix:semicolon
r_if
c_cond
(paren
id|slave-&gt;mtu
OL
id|mtu
)paren
id|mtu
op_assign
id|slave-&gt;mtu
suffix:semicolon
r_if
c_cond
(paren
id|slave-&gt;hard_header_len
OG
id|LL_MAX_HEADER
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* If all the slaves are BROADCAST, master is BROADCAST&n;&t;&t;   If all the slaves are PtP, master is PtP&n;&t;&t;   Otherwise, master is NBMA.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|slave-&gt;flags
op_amp
id|IFF_POINTOPOINT
)paren
)paren
id|flags
op_and_assign
op_complement
id|IFF_POINTOPOINT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|slave-&gt;flags
op_amp
id|IFF_BROADCAST
)paren
)paren
id|flags
op_and_assign
op_complement
id|IFF_BROADCAST
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|slave-&gt;flags
op_amp
id|IFF_MULTICAST
)paren
)paren
id|flags
op_and_assign
op_complement
id|IFF_MULTICAST
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|q
op_assign
id|NEXT_SLAVE
c_func
(paren
id|q
)paren
)paren
op_ne
id|m-&gt;slaves
)paren
suffix:semicolon
id|m-&gt;dev-&gt;mtu
op_assign
id|mtu
suffix:semicolon
id|m-&gt;dev-&gt;flags
op_assign
(paren
id|m-&gt;dev-&gt;flags
op_amp
op_complement
id|FMASK
)paren
op_or
id|flags
suffix:semicolon
id|netif_start_queue
c_func
(paren
id|m-&gt;dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|teql_master_close
r_static
r_int
id|teql_master_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|teql_master_stats
r_static
r_struct
id|net_device_stats
op_star
id|teql_master_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|teql_master
op_star
id|m
op_assign
(paren
r_void
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|m-&gt;stats
suffix:semicolon
)brace
DECL|function|teql_master_mtu
r_static
r_int
id|teql_master_mtu
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|new_mtu
)paren
(brace
r_struct
id|teql_master
op_star
id|m
op_assign
(paren
r_void
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|Qdisc
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
id|new_mtu
OL
l_int|68
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|q
op_assign
id|m-&gt;slaves
suffix:semicolon
r_if
c_cond
(paren
id|q
)paren
(brace
r_do
(brace
r_if
c_cond
(paren
id|new_mtu
OG
id|q-&gt;dev-&gt;mtu
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|q
op_assign
id|NEXT_SLAVE
c_func
(paren
id|q
)paren
)paren
op_ne
id|m-&gt;slaves
)paren
suffix:semicolon
)brace
id|dev-&gt;mtu
op_assign
id|new_mtu
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|teql_master_setup
r_static
id|__init
r_void
id|teql_master_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|teql_master
op_star
id|master
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|Qdisc_ops
op_star
id|ops
op_assign
op_amp
id|master-&gt;qops
suffix:semicolon
id|master-&gt;dev
op_assign
id|dev
suffix:semicolon
id|ops-&gt;priv_size
op_assign
r_sizeof
(paren
r_struct
id|teql_sched_data
)paren
suffix:semicolon
id|ops-&gt;enqueue
op_assign
id|teql_enqueue
suffix:semicolon
id|ops-&gt;dequeue
op_assign
id|teql_dequeue
suffix:semicolon
id|ops-&gt;requeue
op_assign
id|teql_requeue
suffix:semicolon
id|ops-&gt;init
op_assign
id|teql_qdisc_init
suffix:semicolon
id|ops-&gt;reset
op_assign
id|teql_reset
suffix:semicolon
id|ops-&gt;destroy
op_assign
id|teql_destroy
suffix:semicolon
id|ops-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|dev-&gt;open
op_assign
id|teql_master_open
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|teql_master_xmit
suffix:semicolon
id|dev-&gt;stop
op_assign
id|teql_master_close
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|teql_master_stats
suffix:semicolon
id|dev-&gt;change_mtu
op_assign
id|teql_master_mtu
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_VOID
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|1500
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|100
suffix:semicolon
id|dev-&gt;flags
op_assign
id|IFF_NOARP
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|LL_MAX_HEADER
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_static
id|LIST_HEAD
c_func
(paren
id|master_dev_list
)paren
suffix:semicolon
DECL|variable|max_equalizers
r_static
r_int
id|max_equalizers
op_assign
l_int|1
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|max_equalizers
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|max_equalizers
comma
l_string|&quot;Max number of link equalizers&quot;
)paren
suffix:semicolon
DECL|function|teql_init
r_static
r_int
id|__init
id|teql_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENODEV
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
id|max_equalizers
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|teql_master
op_star
id|master
suffix:semicolon
id|dev
op_assign
id|alloc_netdev
c_func
(paren
r_sizeof
(paren
r_struct
id|teql_master
)paren
comma
l_string|&quot;teql%d&quot;
comma
id|teql_master_setup
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
)paren
)paren
(brace
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|master
op_assign
id|dev-&gt;priv
suffix:semicolon
id|strlcpy
c_func
(paren
id|master-&gt;qops.id
comma
id|dev-&gt;name
comma
id|IFNAMSIZ
)paren
suffix:semicolon
id|err
op_assign
id|register_qdisc
c_func
(paren
op_amp
id|master-&gt;qops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|list_add_tail
c_func
(paren
op_amp
id|master-&gt;master_list
comma
op_amp
id|master_dev_list
)paren
suffix:semicolon
)brace
r_return
id|i
ques
c_cond
l_int|0
suffix:colon
id|err
suffix:semicolon
)brace
DECL|function|teql_exit
r_static
r_void
id|__exit
id|teql_exit
c_func
(paren
r_void
)paren
(brace
r_struct
id|teql_master
op_star
id|master
comma
op_star
id|nxt
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|master
comma
id|nxt
comma
op_amp
id|master_dev_list
comma
id|master_list
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|master-&gt;master_list
)paren
suffix:semicolon
id|unregister_qdisc
c_func
(paren
op_amp
id|master-&gt;qops
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|master-&gt;dev
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|master-&gt;dev
)paren
suffix:semicolon
)brace
)brace
DECL|variable|teql_init
id|module_init
c_func
(paren
id|teql_init
)paren
suffix:semicolon
DECL|variable|teql_exit
id|module_exit
c_func
(paren
id|teql_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
