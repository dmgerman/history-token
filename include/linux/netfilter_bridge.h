macro_line|#ifndef __LINUX_BRIDGE_NETFILTER_H
DECL|macro|__LINUX_BRIDGE_NETFILTER_H
mdefine_line|#define __LINUX_BRIDGE_NETFILTER_H
multiline_comment|/* bridge-specific defines for netfilter. &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#if defined(__KERNEL__) &amp;&amp; defined(CONFIG_BRIDGE_NETFILTER)
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#if defined(CONFIG_VLAN_8021Q) || defined(CONFIG_VLAN_8021Q_MODULE)
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#endif
macro_line|#endif
multiline_comment|/* Bridge Hooks */
multiline_comment|/* After promisc drops, checksum checks. */
DECL|macro|NF_BR_PRE_ROUTING
mdefine_line|#define NF_BR_PRE_ROUTING&t;0
multiline_comment|/* If the packet is destined for this box. */
DECL|macro|NF_BR_LOCAL_IN
mdefine_line|#define NF_BR_LOCAL_IN&t;&t;1
multiline_comment|/* If the packet is destined for another interface. */
DECL|macro|NF_BR_FORWARD
mdefine_line|#define NF_BR_FORWARD&t;&t;2
multiline_comment|/* Packets coming from a local process. */
DECL|macro|NF_BR_LOCAL_OUT
mdefine_line|#define NF_BR_LOCAL_OUT&t;&t;3
multiline_comment|/* Packets about to hit the wire. */
DECL|macro|NF_BR_POST_ROUTING
mdefine_line|#define NF_BR_POST_ROUTING&t;4
multiline_comment|/* Not really a hook, but used for the ebtables broute table */
DECL|macro|NF_BR_BROUTING
mdefine_line|#define NF_BR_BROUTING&t;&t;5
DECL|macro|NF_BR_NUMHOOKS
mdefine_line|#define NF_BR_NUMHOOKS&t;&t;6
macro_line|#ifdef __KERNEL__
DECL|enum|nf_br_hook_priorities
r_enum
id|nf_br_hook_priorities
(brace
DECL|enumerator|NF_BR_PRI_FIRST
id|NF_BR_PRI_FIRST
op_assign
id|INT_MIN
comma
DECL|enumerator|NF_BR_PRI_NAT_DST_BRIDGED
id|NF_BR_PRI_NAT_DST_BRIDGED
op_assign
op_minus
l_int|300
comma
DECL|enumerator|NF_BR_PRI_FILTER_BRIDGED
id|NF_BR_PRI_FILTER_BRIDGED
op_assign
op_minus
l_int|200
comma
DECL|enumerator|NF_BR_PRI_BRNF
id|NF_BR_PRI_BRNF
op_assign
l_int|0
comma
DECL|enumerator|NF_BR_PRI_NAT_DST_OTHER
id|NF_BR_PRI_NAT_DST_OTHER
op_assign
l_int|100
comma
DECL|enumerator|NF_BR_PRI_FILTER_OTHER
id|NF_BR_PRI_FILTER_OTHER
op_assign
l_int|200
comma
DECL|enumerator|NF_BR_PRI_NAT_SRC
id|NF_BR_PRI_NAT_SRC
op_assign
l_int|300
comma
DECL|enumerator|NF_BR_PRI_LAST
id|NF_BR_PRI_LAST
op_assign
id|INT_MAX
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_BRIDGE_NETFILTER
DECL|macro|BRNF_PKT_TYPE
mdefine_line|#define BRNF_PKT_TYPE&t;&t;&t;0x01
DECL|macro|BRNF_BRIDGED_DNAT
mdefine_line|#define BRNF_BRIDGED_DNAT&t;&t;0x02
DECL|macro|BRNF_DONT_TAKE_PARENT
mdefine_line|#define BRNF_DONT_TAKE_PARENT&t;&t;0x04
DECL|macro|BRNF_BRIDGED
mdefine_line|#define BRNF_BRIDGED&t;&t;&t;0x08
DECL|macro|BRNF_NF_BRIDGE_PREROUTING
mdefine_line|#define BRNF_NF_BRIDGE_PREROUTING&t;0x10
r_static
r_inline
DECL|function|nf_bridge_alloc
r_struct
id|nf_bridge_info
op_star
id|nf_bridge_alloc
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|nf_bridge_info
op_star
op_star
id|nf_bridge
op_assign
op_amp
(paren
id|skb-&gt;nf_bridge
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|nf_bridge
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
op_star
id|nf_bridge
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
(paren
op_star
id|nf_bridge
)paren
op_member_access_from_pointer
id|use
comma
l_int|1
)paren
suffix:semicolon
(paren
op_star
id|nf_bridge
)paren
op_member_access_from_pointer
id|mask
op_assign
l_int|0
suffix:semicolon
(paren
op_star
id|nf_bridge
)paren
op_member_access_from_pointer
id|physindev
op_assign
(paren
op_star
id|nf_bridge
)paren
op_member_access_from_pointer
id|physoutdev
op_assign
l_int|NULL
suffix:semicolon
macro_line|#if defined(CONFIG_VLAN_8021Q) || defined(CONFIG_VLAN_8021Q_MODULE)
(paren
op_star
id|nf_bridge
)paren
op_member_access_from_pointer
id|netoutdev
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
)brace
r_return
op_star
id|nf_bridge
suffix:semicolon
)brace
multiline_comment|/* Only used in br_forward.c */
r_static
r_inline
DECL|function|nf_bridge_maybe_copy_header
r_void
id|nf_bridge_maybe_copy_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nf_bridge
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;protocol
op_eq
id|__constant_htons
c_func
(paren
id|ETH_P_8021Q
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|skb-&gt;data
op_minus
l_int|18
comma
id|skb-&gt;nf_bridge-&gt;data
comma
l_int|18
)paren
suffix:semicolon
id|skb_push
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
id|skb-&gt;data
op_minus
l_int|16
comma
id|skb-&gt;nf_bridge-&gt;data
comma
l_int|16
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
DECL|function|nf_bridge_save_header
r_void
id|nf_bridge_save_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|header_size
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;protocol
op_eq
id|__constant_htons
c_func
(paren
id|ETH_P_8021Q
)paren
)paren
id|header_size
op_assign
l_int|18
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;nf_bridge-&gt;data
comma
id|skb-&gt;data
op_minus
id|header_size
comma
id|header_size
)paren
suffix:semicolon
)brace
DECL|struct|bridge_skb_cb
r_struct
id|bridge_skb_cb
(brace
r_union
(brace
DECL|member|ipv4
id|__u32
id|ipv4
suffix:semicolon
DECL|member|daddr
)brace
id|daddr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_BRIDGE_NETFILTER */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
