macro_line|#ifndef __LINUX_BRIDGE_NETFILTER_H
DECL|macro|__LINUX_BRIDGE_NETFILTER_H
mdefine_line|#define __LINUX_BRIDGE_NETFILTER_H
multiline_comment|/* bridge-specific defines for netfilter. &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
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
DECL|enum|nf_br_hook_priorities
r_enum
id|nf_br_hook_priorities
(brace
DECL|enumerator|NF_BR_PRI_FIRST
id|NF_BR_PRI_FIRST
op_assign
id|INT_MIN
comma
DECL|enumerator|NF_BR_PRI_FILTER_BRIDGED
id|NF_BR_PRI_FILTER_BRIDGED
op_assign
op_minus
l_int|200
comma
DECL|enumerator|NF_BR_PRI_FILTER_OTHER
id|NF_BR_PRI_FILTER_OTHER
op_assign
l_int|200
comma
DECL|enumerator|NF_BR_PRI_NAT_DST_BRIDGED
id|NF_BR_PRI_NAT_DST_BRIDGED
op_assign
op_minus
l_int|300
comma
DECL|enumerator|NF_BR_PRI_NAT_DST_OTHER
id|NF_BR_PRI_NAT_DST_OTHER
op_assign
l_int|100
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
macro_line|#endif
eof
