multiline_comment|/*&n; *&t;Forwarding decision&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_forward.c,v 1.4 2001/08/14 22:05:57 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;linux/netfilter_bridge.h&gt;
macro_line|#include &quot;br_private.h&quot;
DECL|function|should_deliver
r_static
r_inline
r_int
id|should_deliver
c_func
(paren
r_const
r_struct
id|net_bridge_port
op_star
id|p
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;dev
op_eq
id|p-&gt;dev
op_logical_or
id|p-&gt;state
op_ne
id|BR_STATE_FORWARDING
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|br_dev_queue_push_xmit
r_int
id|br_dev_queue_push_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
macro_line|#ifdef CONFIG_NETFILTER
multiline_comment|/* FIXME: skb bas not been linearized: is this valid?? --RR */
r_if
c_cond
(paren
id|skb-&gt;nf_bridge
)paren
id|memcpy
c_func
(paren
id|skb-&gt;data
op_minus
l_int|16
comma
id|skb-&gt;nf_bridge-&gt;hh
comma
l_int|16
)paren
suffix:semicolon
macro_line|#endif
id|skb_push
c_func
(paren
id|skb
comma
id|ETH_HLEN
)paren
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|br_forward_finish
r_int
id|br_forward_finish
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|NF_HOOK
c_func
(paren
id|PF_BRIDGE
comma
id|NF_BR_POST_ROUTING
comma
id|skb
comma
l_int|NULL
comma
id|skb-&gt;dev
comma
id|br_dev_queue_push_xmit
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__br_deliver
r_static
r_void
id|__br_deliver
c_func
(paren
r_const
r_struct
id|net_bridge_port
op_star
id|to
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|skb-&gt;dev
op_assign
id|to-&gt;dev
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
id|skb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|NF_HOOK
c_func
(paren
id|PF_BRIDGE
comma
id|NF_BR_LOCAL_OUT
comma
id|skb
comma
l_int|NULL
comma
id|skb-&gt;dev
comma
id|br_forward_finish
)paren
suffix:semicolon
)brace
DECL|function|__br_forward
r_static
r_void
id|__br_forward
c_func
(paren
r_const
r_struct
id|net_bridge_port
op_star
id|to
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
id|indev
op_assign
id|skb-&gt;dev
suffix:semicolon
id|skb-&gt;dev
op_assign
id|to-&gt;dev
suffix:semicolon
id|NF_HOOK
c_func
(paren
id|PF_BRIDGE
comma
id|NF_BR_FORWARD
comma
id|skb
comma
id|indev
comma
id|skb-&gt;dev
comma
id|br_forward_finish
)paren
suffix:semicolon
)brace
multiline_comment|/* called with rcu_read_lock */
DECL|function|br_deliver
r_void
id|br_deliver
c_func
(paren
r_const
r_struct
id|net_bridge_port
op_star
id|to
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|should_deliver
c_func
(paren
id|to
comma
id|skb
)paren
)paren
(brace
id|__br_deliver
c_func
(paren
id|to
comma
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/* called with rcu_read_lock */
DECL|function|br_forward
r_void
id|br_forward
c_func
(paren
r_const
r_struct
id|net_bridge_port
op_star
id|to
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|should_deliver
c_func
(paren
id|to
comma
id|skb
)paren
)paren
(brace
id|__br_forward
c_func
(paren
id|to
comma
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_flood
r_static
r_void
id|br_flood
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
comma
r_int
id|clone
comma
r_void
(paren
op_star
id|__packet_hook
)paren
(paren
r_const
r_struct
id|net_bridge_port
op_star
id|p
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
)paren
(brace
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|prev
suffix:semicolon
r_if
c_cond
(paren
id|clone
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb2
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|br-&gt;statistics.tx_dropped
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb
op_assign
id|skb2
suffix:semicolon
)brace
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|list_for_each_entry_rcu
c_func
(paren
id|p
comma
op_amp
id|br-&gt;port_list
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|should_deliver
c_func
(paren
id|p
comma
id|skb
)paren
)paren
(brace
r_if
c_cond
(paren
id|prev
op_ne
l_int|NULL
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb2
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|br-&gt;statistics.tx_dropped
op_increment
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|__packet_hook
c_func
(paren
id|prev
comma
id|skb2
)paren
suffix:semicolon
)brace
id|prev
op_assign
id|p
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|prev
op_ne
l_int|NULL
)paren
(brace
id|__packet_hook
c_func
(paren
id|prev
comma
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/* called with rcu_read_lock */
DECL|function|br_flood_deliver
r_void
id|br_flood_deliver
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
comma
r_int
id|clone
)paren
(brace
id|br_flood
c_func
(paren
id|br
comma
id|skb
comma
id|clone
comma
id|__br_deliver
)paren
suffix:semicolon
)brace
multiline_comment|/* called under bridge lock */
DECL|function|br_flood_forward
r_void
id|br_flood_forward
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
comma
r_int
id|clone
)paren
(brace
id|br_flood
c_func
(paren
id|br
comma
id|skb
comma
id|clone
comma
id|__br_forward
)paren
suffix:semicolon
)brace
eof
