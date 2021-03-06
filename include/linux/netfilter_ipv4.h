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
DECL|enumerator|NF_IP_PRI_CONNTRACK_DEFRAG
id|NF_IP_PRI_CONNTRACK_DEFRAG
op_assign
op_minus
l_int|400
comma
DECL|enumerator|NF_IP_PRI_RAW
id|NF_IP_PRI_RAW
op_assign
op_minus
l_int|300
comma
DECL|enumerator|NF_IP_PRI_SELINUX_FIRST
id|NF_IP_PRI_SELINUX_FIRST
op_assign
op_minus
l_int|225
comma
DECL|enumerator|NF_IP_PRI_CONNTRACK
id|NF_IP_PRI_CONNTRACK
op_assign
op_minus
l_int|200
comma
DECL|enumerator|NF_IP_PRI_BRIDGE_SABOTAGE_FORWARD
id|NF_IP_PRI_BRIDGE_SABOTAGE_FORWARD
op_assign
op_minus
l_int|175
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
DECL|enumerator|NF_IP_PRI_BRIDGE_SABOTAGE_LOCAL_OUT
id|NF_IP_PRI_BRIDGE_SABOTAGE_LOCAL_OUT
op_assign
op_minus
l_int|50
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
DECL|enumerator|NF_IP_PRI_SELINUX_LAST
id|NF_IP_PRI_SELINUX_LAST
op_assign
l_int|225
comma
DECL|enumerator|NF_IP_PRI_LAST
id|NF_IP_PRI_LAST
op_assign
id|INT_MAX
comma
)brace
suffix:semicolon
multiline_comment|/* Arguments for setsockopt SOL_IP: */
multiline_comment|/* 2.0 firewalling went from 64 through 71 (and +256, +512, etc). */
multiline_comment|/* 2.2 firewalling (+ masq) went from 64 through 76 */
multiline_comment|/* 2.4 firewalling went 64 through 67. */
DECL|macro|SO_ORIGINAL_DST
mdefine_line|#define SO_ORIGINAL_DST 80
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
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
macro_line|#endif /*CONFIG_NETFILTER_DEBUG*/
r_extern
r_int
id|ip_route_me_harder
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
multiline_comment|/* Call this before modifying an existing IP packet: ensures it is&n;   modifiable and linear to the point you care about (writable_len).&n;   Returns true or false. */
r_extern
r_int
id|skb_ip_make_writable
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
id|writable_len
)paren
suffix:semicolon
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /*__LINUX_IP_NETFILTER_H*/
eof
