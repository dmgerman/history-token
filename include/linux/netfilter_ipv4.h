macro_line|#ifndef __LINUX_IP_NETFILTER_H
DECL|macro|__LINUX_IP_NETFILTER_H
mdefine_line|#define __LINUX_IP_NETFILTER_H
multiline_comment|/* IPv4-specific defines for netfilter. &n; * (C)1998 Rusty Russell -- This code is GPL.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
multiline_comment|/* IP Cache bits. */
multiline_comment|/* Src IP address. */
DECL|macro|NFC_IP_SRC
mdefine_line|#define NFC_IP_SRC&t;&t;0x0001
multiline_comment|/* Dest IP address. */
DECL|macro|NFC_IP_DST
mdefine_line|#define NFC_IP_DST&t;&t;0x0002
multiline_comment|/* Input device. */
DECL|macro|NFC_IP_IF_IN
mdefine_line|#define NFC_IP_IF_IN&t;&t;0x0004
multiline_comment|/* Output device. */
DECL|macro|NFC_IP_IF_OUT
mdefine_line|#define NFC_IP_IF_OUT&t;&t;0x0008
multiline_comment|/* TOS. */
DECL|macro|NFC_IP_TOS
mdefine_line|#define NFC_IP_TOS&t;&t;0x0010
multiline_comment|/* Protocol. */
DECL|macro|NFC_IP_PROTO
mdefine_line|#define NFC_IP_PROTO&t;&t;0x0020
multiline_comment|/* IP options. */
DECL|macro|NFC_IP_OPTIONS
mdefine_line|#define NFC_IP_OPTIONS&t;&t;0x0040
multiline_comment|/* Frag &amp; flags. */
DECL|macro|NFC_IP_FRAG
mdefine_line|#define NFC_IP_FRAG&t;&t;0x0080
multiline_comment|/* Per-protocol information: only matters if proto match. */
multiline_comment|/* TCP flags. */
DECL|macro|NFC_IP_TCPFLAGS
mdefine_line|#define NFC_IP_TCPFLAGS&t;&t;0x0100
multiline_comment|/* Source port. */
DECL|macro|NFC_IP_SRC_PT
mdefine_line|#define NFC_IP_SRC_PT&t;&t;0x0200
multiline_comment|/* Dest port. */
DECL|macro|NFC_IP_DST_PT
mdefine_line|#define NFC_IP_DST_PT&t;&t;0x0400
multiline_comment|/* Something else about the proto */
DECL|macro|NFC_IP_PROTO_UNKNOWN
mdefine_line|#define NFC_IP_PROTO_UNKNOWN&t;0x2000
multiline_comment|/* IP Hooks */
multiline_comment|/* After promisc drops, checksum checks. */
DECL|macro|NF_IP_PRE_ROUTING
mdefine_line|#define NF_IP_PRE_ROUTING&t;0
multiline_comment|/* If the packet is destined for this box. */
DECL|macro|NF_IP_LOCAL_IN
mdefine_line|#define NF_IP_LOCAL_IN&t;&t;1
multiline_comment|/* If the packet is destined for another interface. */
DECL|macro|NF_IP_FORWARD
mdefine_line|#define NF_IP_FORWARD&t;&t;2
multiline_comment|/* Packets coming from a local process. */
DECL|macro|NF_IP_LOCAL_OUT
mdefine_line|#define NF_IP_LOCAL_OUT&t;&t;3
multiline_comment|/* Packets about to hit the wire. */
DECL|macro|NF_IP_POST_ROUTING
mdefine_line|#define NF_IP_POST_ROUTING&t;4
DECL|macro|NF_IP_NUMHOOKS
mdefine_line|#define NF_IP_NUMHOOKS&t;&t;5
DECL|enum|nf_ip_hook_priorities
r_enum
id|nf_ip_hook_priorities
(brace
DECL|enumerator|NF_IP_PRI_FIRST
id|NF_IP_PRI_FIRST
op_assign
id|INT_MIN
comma
DECL|enumerator|NF_IP_PRI_CONNTRACK
id|NF_IP_PRI_CONNTRACK
op_assign
op_minus
l_int|200
comma
DECL|enumerator|NF_IP_PRI_MANGLE
id|NF_IP_PRI_MANGLE
op_assign
op_minus
l_int|150
comma
DECL|enumerator|NF_IP_PRI_NAT_DST
id|NF_IP_PRI_NAT_DST
op_assign
op_minus
l_int|100
comma
DECL|enumerator|NF_IP_PRI_FILTER
id|NF_IP_PRI_FILTER
op_assign
l_int|0
comma
DECL|enumerator|NF_IP_PRI_NAT_SRC
id|NF_IP_PRI_NAT_SRC
op_assign
l_int|100
comma
DECL|enumerator|NF_IP_PRI_LAST
id|NF_IP_PRI_LAST
op_assign
id|INT_MAX
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
macro_line|#ifdef __KERNEL__
r_void
id|nf_debug_ip_local_deliver
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|nf_debug_ip_loopback_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|newskb
)paren
suffix:semicolon
r_void
id|nf_debug_ip_finish_output2
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /*CONFIG_NETFILTER_DEBUG*/
multiline_comment|/* Arguments for setsockopt SOL_IP: */
multiline_comment|/* 2.0 firewalling went from 64 through 71 (and +256, +512, etc). */
multiline_comment|/* 2.2 firewalling (+ masq) went from 64 through 76 */
multiline_comment|/* 2.4 firewalling went 64 through 67. */
DECL|macro|SO_ORIGINAL_DST
mdefine_line|#define SO_ORIGINAL_DST 80
multiline_comment|/* route_me_harder function, used by iptable_nat, iptable_mangle + ip_queue &n; *&n; * Ideally this would be ins some netfilter_utility module, but creating this&n; * module for just one function doesn&squot;t make sense. -HW */
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
DECL|function|route_me_harder
r_static
r_inline
r_int
id|route_me_harder
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
r_struct
id|rt_key
id|key
op_assign
(brace
id|dst
suffix:colon
id|iph-&gt;daddr
comma
id|src
suffix:colon
id|iph-&gt;saddr
comma
id|oif
suffix:colon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk
ques
c_cond
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk-&gt;bound_dev_if
suffix:colon
l_int|0
comma
id|tos
suffix:colon
id|RT_TOS
c_func
(paren
id|iph-&gt;tos
)paren
op_or
id|RTO_CONN
comma
macro_line|#ifdef CONFIG_IP_ROUTE_FWMARK
id|fwmark
suffix:colon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfmark
macro_line|#endif
)brace
suffix:semicolon
r_struct
id|net_device
op_star
id|dev_src
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* accomodate ip_route_output_slow(), which expects the key src to be&n;&t;   0 or a local address; however some non-standard hacks like&n;&t;   ipt_REJECT.c:send_reset() can cause packets with foreign&n;           saddr to be appear on the NF_IP_LOCAL_OUT hook -MB */
r_if
c_cond
(paren
id|key.src
op_logical_and
op_logical_neg
(paren
id|dev_src
op_assign
id|ip_dev_find
c_func
(paren
id|key.src
)paren
)paren
)paren
(brace
id|key.src
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|ip_route_output_key
c_func
(paren
op_amp
id|rt
comma
op_amp
id|key
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;route_me_harder: ip_route_output_key(dst=%u.%u.%u.%u, src=%u.%u.%u.%u, oif=%d, tos=0x%x, fwmark=0x%lx) error %d&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;daddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;saddr
)paren
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk
ques
c_cond
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk-&gt;bound_dev_if
suffix:colon
l_int|0
comma
id|RT_TOS
c_func
(paren
id|iph-&gt;tos
)paren
op_or
id|RTO_CONN
comma
macro_line|#ifdef CONFIG_IP_ROUTE_FWMARK
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfmark
comma
macro_line|#else
l_int|0UL
comma
macro_line|#endif
id|err
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Drop old route. */
id|dst_release
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst
)paren
suffix:semicolon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
multiline_comment|/* Change in oif may mean change in hh_len. */
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
op_star
id|pskb
)paren
OL
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst-&gt;dev-&gt;hard_header_len
)paren
(brace
r_struct
id|sk_buff
op_star
id|nskb
suffix:semicolon
id|nskb
op_assign
id|skb_realloc_headroom
c_func
(paren
op_star
id|pskb
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst-&gt;dev-&gt;hard_header_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nskb
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk
)paren
id|skb_set_owner_w
c_func
(paren
id|nskb
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|sk
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
op_star
id|pskb
op_assign
id|nskb
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|dev_src
)paren
id|dev_put
c_func
(paren
id|dev_src
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif /*__LINUX_IP_NETFILTER_H*/
eof
