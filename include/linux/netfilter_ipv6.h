macro_line|#ifndef __LINUX_IP6_NETFILTER_H
DECL|macro|__LINUX_IP6_NETFILTER_H
mdefine_line|#define __LINUX_IP6_NETFILTER_H
multiline_comment|/* IPv6-specific defines for netfilter. &n; * (C)1998 Rusty Russell -- This code is GPL.&n; * (C)1999 David Jeffery&n; *   this header was blatantly ripped from netfilter_ipv4.h &n; *   it&squot;s amazing what adding a bunch of 6s can do =8^)&n; */
macro_line|#include &lt;linux/netfilter.h&gt;
multiline_comment|/* IP Cache bits. */
multiline_comment|/* Src IP address. */
DECL|macro|NFC_IP6_SRC
mdefine_line|#define NFC_IP6_SRC              0x0001
multiline_comment|/* Dest IP address. */
DECL|macro|NFC_IP6_DST
mdefine_line|#define NFC_IP6_DST              0x0002
multiline_comment|/* Input device. */
DECL|macro|NFC_IP6_IF_IN
mdefine_line|#define NFC_IP6_IF_IN            0x0004
multiline_comment|/* Output device. */
DECL|macro|NFC_IP6_IF_OUT
mdefine_line|#define NFC_IP6_IF_OUT           0x0008
multiline_comment|/* TOS. */
DECL|macro|NFC_IP6_TOS
mdefine_line|#define NFC_IP6_TOS              0x0010
multiline_comment|/* Protocol. */
DECL|macro|NFC_IP6_PROTO
mdefine_line|#define NFC_IP6_PROTO            0x0020
multiline_comment|/* IP options. */
DECL|macro|NFC_IP6_OPTIONS
mdefine_line|#define NFC_IP6_OPTIONS          0x0040
multiline_comment|/* Frag &amp; flags. */
DECL|macro|NFC_IP6_FRAG
mdefine_line|#define NFC_IP6_FRAG             0x0080
multiline_comment|/* Per-protocol information: only matters if proto match. */
multiline_comment|/* TCP flags. */
DECL|macro|NFC_IP6_TCPFLAGS
mdefine_line|#define NFC_IP6_TCPFLAGS         0x0100
multiline_comment|/* Source port. */
DECL|macro|NFC_IP6_SRC_PT
mdefine_line|#define NFC_IP6_SRC_PT           0x0200
multiline_comment|/* Dest port. */
DECL|macro|NFC_IP6_DST_PT
mdefine_line|#define NFC_IP6_DST_PT           0x0400
multiline_comment|/* Something else about the proto */
DECL|macro|NFC_IP6_PROTO_UNKNOWN
mdefine_line|#define NFC_IP6_PROTO_UNKNOWN    0x2000
multiline_comment|/* IP6 Hooks */
multiline_comment|/* After promisc drops, checksum checks. */
DECL|macro|NF_IP6_PRE_ROUTING
mdefine_line|#define NF_IP6_PRE_ROUTING&t;0
multiline_comment|/* If the packet is destined for this box. */
DECL|macro|NF_IP6_LOCAL_IN
mdefine_line|#define NF_IP6_LOCAL_IN&t;&t;1
multiline_comment|/* If the packet is destined for another interface. */
DECL|macro|NF_IP6_FORWARD
mdefine_line|#define NF_IP6_FORWARD&t;&t;2
multiline_comment|/* Packets coming from a local process. */
DECL|macro|NF_IP6_LOCAL_OUT
mdefine_line|#define NF_IP6_LOCAL_OUT&t;&t;3
multiline_comment|/* Packets about to hit the wire. */
DECL|macro|NF_IP6_POST_ROUTING
mdefine_line|#define NF_IP6_POST_ROUTING&t;4
DECL|macro|NF_IP6_NUMHOOKS
mdefine_line|#define NF_IP6_NUMHOOKS&t;&t;5
DECL|enum|nf_ip6_hook_priorities
r_enum
id|nf_ip6_hook_priorities
(brace
DECL|enumerator|NF_IP6_PRI_FIRST
id|NF_IP6_PRI_FIRST
op_assign
id|INT_MIN
comma
DECL|enumerator|NF_IP6_PRI_CONNTRACK
id|NF_IP6_PRI_CONNTRACK
op_assign
op_minus
l_int|200
comma
DECL|enumerator|NF_IP6_PRI_MANGLE
id|NF_IP6_PRI_MANGLE
op_assign
op_minus
l_int|150
comma
DECL|enumerator|NF_IP6_PRI_NAT_DST
id|NF_IP6_PRI_NAT_DST
op_assign
op_minus
l_int|100
comma
DECL|enumerator|NF_IP6_PRI_FILTER
id|NF_IP6_PRI_FILTER
op_assign
l_int|0
comma
DECL|enumerator|NF_IP6_PRI_NAT_SRC
id|NF_IP6_PRI_NAT_SRC
op_assign
l_int|100
comma
DECL|enumerator|NF_IP6_PRI_LAST
id|NF_IP6_PRI_LAST
op_assign
id|INT_MAX
comma
)brace
suffix:semicolon
macro_line|#endif /*__LINUX_IP6_NETFILTER_H*/
eof
