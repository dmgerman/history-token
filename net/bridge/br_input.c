multiline_comment|/*&n; *&t;Handle incoming frames&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_input.c,v 1.10 2001/12/24 04:50:20 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/netfilter_bridge.h&gt;
macro_line|#include &quot;br_private.h&quot;
DECL|variable|bridge_ula
r_const
r_int
r_char
id|bridge_ula
(braket
l_int|6
)braket
op_assign
(brace
l_int|0x01
comma
l_int|0x80
comma
l_int|0xc2
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
DECL|function|br_pass_frame_up_finish
r_static
r_int
id|br_pass_frame_up_finish
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
id|skb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|br_pass_frame_up
r_static
r_void
id|br_pass_frame_up
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|net_device
op_star
id|indev
suffix:semicolon
id|br-&gt;statistics.rx_packets
op_increment
suffix:semicolon
id|br-&gt;statistics.rx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|indev
op_assign
id|skb-&gt;dev
suffix:semicolon
id|skb-&gt;dev
op_assign
id|br-&gt;dev
suffix:semicolon
id|NF_HOOK
c_func
(paren
id|PF_BRIDGE
comma
id|NF_BR_LOCAL_IN
comma
id|skb
comma
id|indev
comma
l_int|NULL
comma
id|br_pass_frame_up_finish
)paren
suffix:semicolon
)brace
DECL|function|br_handle_frame_finish
r_int
id|br_handle_frame_finish
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
r_int
r_char
op_star
id|dest
suffix:semicolon
r_struct
id|net_bridge_fdb_entry
op_star
id|dst
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
r_int
id|passedup
suffix:semicolon
id|dest
op_assign
id|skb-&gt;mac.ethernet-&gt;h_dest
suffix:semicolon
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
id|p
op_assign
id|skb-&gt;dev-&gt;br_port
suffix:semicolon
id|smp_read_barrier_depends
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
op_logical_or
id|p-&gt;state
op_eq
id|BR_STATE_DISABLED
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|br
op_assign
id|p-&gt;br
suffix:semicolon
id|passedup
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|br-&gt;dev-&gt;flags
op_amp
id|IFF_PROMISC
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
id|skb2
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
op_ne
l_int|NULL
)paren
(brace
id|passedup
op_assign
l_int|1
suffix:semicolon
id|br_pass_frame_up
c_func
(paren
id|br
comma
id|skb2
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dest
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
(brace
id|br_flood_forward
c_func
(paren
id|br
comma
id|skb
comma
op_logical_neg
id|passedup
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|passedup
)paren
id|br_pass_frame_up
c_func
(paren
id|br
comma
id|skb
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dst
op_assign
id|br_fdb_get
c_func
(paren
id|br
comma
id|dest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_ne
l_int|NULL
op_logical_and
id|dst-&gt;is_local
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|passedup
)paren
id|br_pass_frame_up
c_func
(paren
id|br
comma
id|skb
)paren
suffix:semicolon
r_else
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|br_fdb_put
c_func
(paren
id|dst
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dst
op_ne
l_int|NULL
)paren
(brace
id|br_forward
c_func
(paren
id|dst-&gt;dst
comma
id|skb
)paren
suffix:semicolon
id|br_fdb_put
c_func
(paren
id|dst
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|br_flood_forward
c_func
(paren
id|br
comma
id|skb
comma
l_int|0
)paren
suffix:semicolon
id|out
suffix:colon
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|br_handle_frame
r_int
id|br_handle_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
r_char
op_star
id|dest
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
id|dest
op_assign
id|skb-&gt;mac.ethernet-&gt;h_dest
suffix:semicolon
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
id|p
op_assign
id|skb-&gt;dev-&gt;br_port
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
op_logical_or
id|p-&gt;state
op_eq
id|BR_STATE_DISABLED
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;mac.ethernet-&gt;h_source
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|BR_STATE_LEARNING
op_logical_or
id|p-&gt;state
op_eq
id|BR_STATE_FORWARDING
)paren
id|br_fdb_insert
c_func
(paren
id|p-&gt;br
comma
id|p
comma
id|skb-&gt;mac.ethernet-&gt;h_source
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;br-&gt;stp_enabled
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|dest
comma
id|bridge_ula
comma
l_int|5
)paren
op_logical_and
op_logical_neg
(paren
id|dest
(braket
l_int|5
)braket
op_amp
l_int|0xF0
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dest
(braket
l_int|5
)braket
)paren
(brace
id|NF_HOOK
c_func
(paren
id|PF_BRIDGE
comma
id|NF_BR_LOCAL_IN
comma
id|skb
comma
id|skb-&gt;dev
comma
l_int|NULL
comma
id|br_stp_handle_bpdu
)paren
suffix:semicolon
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|BR_STATE_FORWARDING
)paren
(brace
r_if
c_cond
(paren
id|br_should_route_hook
op_logical_and
id|br_should_route_hook
c_func
(paren
op_amp
id|skb
)paren
)paren
(brace
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|p-&gt;br-&gt;dev-&gt;dev_addr
comma
id|dest
comma
id|ETH_ALEN
)paren
)paren
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|NF_HOOK
c_func
(paren
id|PF_BRIDGE
comma
id|NF_BR_PRE_ROUTING
comma
id|skb
comma
id|skb-&gt;dev
comma
l_int|NULL
comma
id|br_handle_frame_finish
)paren
suffix:semicolon
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|err
suffix:colon
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
