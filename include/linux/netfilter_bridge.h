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
DECL|macro|NF_BR_NUMHOOKS
mdefine_line|#define NF_BR_NUMHOOKS&t;&t;5
macro_line|#endif
eof
