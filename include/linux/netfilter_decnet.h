macro_line|#ifndef __LINUX_DECNET_NETFILTER_H
DECL|macro|__LINUX_DECNET_NETFILTER_H
mdefine_line|#define __LINUX_DECNET_NETFILTER_H
multiline_comment|/* DECnet-specific defines for netfilter. &n; * This file (C) Steve Whitehouse 1999 derived from the&n; * ipv4 netfilter header file which is&n; * (C)1998 Rusty Russell -- This code is GPL.&n; */
macro_line|#include &lt;linux/netfilter.h&gt;
multiline_comment|/* IP Cache bits. */
multiline_comment|/* Src IP address. */
DECL|macro|NFC_DN_SRC
mdefine_line|#define NFC_DN_SRC&t;&t;0x0001
multiline_comment|/* Dest IP address. */
DECL|macro|NFC_DN_DST
mdefine_line|#define NFC_DN_DST&t;&t;0x0002
multiline_comment|/* Input device. */
DECL|macro|NFC_DN_IF_IN
mdefine_line|#define NFC_DN_IF_IN&t;&t;0x0004
multiline_comment|/* Output device. */
DECL|macro|NFC_DN_IF_OUT
mdefine_line|#define NFC_DN_IF_OUT&t;&t;0x0008
multiline_comment|/* DECnet Hooks */
multiline_comment|/* After promisc drops, checksum checks. */
DECL|macro|NF_DN_PRE_ROUTING
mdefine_line|#define NF_DN_PRE_ROUTING&t;0
multiline_comment|/* If the packet is destined for this box. */
DECL|macro|NF_DN_LOCAL_IN
mdefine_line|#define NF_DN_LOCAL_IN&t;&t;1
multiline_comment|/* If the packet is destined for another interface. */
DECL|macro|NF_DN_FORWARD
mdefine_line|#define NF_DN_FORWARD&t;&t;2
multiline_comment|/* Packets coming from a local process. */
DECL|macro|NF_DN_LOCAL_OUT
mdefine_line|#define NF_DN_LOCAL_OUT&t;&t;3
multiline_comment|/* Packets about to hit the wire. */
DECL|macro|NF_DN_POST_ROUTING
mdefine_line|#define NF_DN_POST_ROUTING&t;4
multiline_comment|/* Input Hello Packets */
DECL|macro|NF_DN_HELLO
mdefine_line|#define NF_DN_HELLO&t;&t;5
multiline_comment|/* Input Routing Packets */
DECL|macro|NF_DN_ROUTE
mdefine_line|#define NF_DN_ROUTE&t;&t;6
DECL|macro|NF_DN_NUMHOOKS
mdefine_line|#define NF_DN_NUMHOOKS&t;&t;7
DECL|enum|nf_dn_hook_priorities
r_enum
id|nf_dn_hook_priorities
(brace
DECL|enumerator|NF_DN_PRI_FIRST
id|NF_DN_PRI_FIRST
op_assign
id|INT_MIN
comma
DECL|enumerator|NF_DN_PRI_CONNTRACK
id|NF_DN_PRI_CONNTRACK
op_assign
op_minus
l_int|200
comma
DECL|enumerator|NF_DN_PRI_MANGLE
id|NF_DN_PRI_MANGLE
op_assign
op_minus
l_int|150
comma
DECL|enumerator|NF_DN_PRI_NAT_DST
id|NF_DN_PRI_NAT_DST
op_assign
op_minus
l_int|100
comma
DECL|enumerator|NF_DN_PRI_FILTER
id|NF_DN_PRI_FILTER
op_assign
l_int|0
comma
DECL|enumerator|NF_DN_PRI_NAT_SRC
id|NF_DN_PRI_NAT_SRC
op_assign
l_int|100
comma
DECL|enumerator|NF_DN_PRI_DNRTMSG
id|NF_DN_PRI_DNRTMSG
op_assign
l_int|200
comma
DECL|enumerator|NF_DN_PRI_LAST
id|NF_DN_PRI_LAST
op_assign
id|INT_MAX
comma
)brace
suffix:semicolon
DECL|struct|nf_dn_rtmsg
r_struct
id|nf_dn_rtmsg
(brace
DECL|member|nfdn_ifindex
r_int
id|nfdn_ifindex
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NFDN_RTMSG
mdefine_line|#define NFDN_RTMSG(r) ((unsigned char *)(r) + NLMSG_ALIGN(sizeof(struct nf_dn_rtmsg)))
DECL|macro|DNRMG_L1_GROUP
mdefine_line|#define DNRMG_L1_GROUP 0x01
DECL|macro|DNRMG_L2_GROUP
mdefine_line|#define DNRMG_L2_GROUP 0x02
macro_line|#endif /*__LINUX_DECNET_NETFILTER_H*/
eof
