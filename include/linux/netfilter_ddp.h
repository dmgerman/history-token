macro_line|#ifndef __LINUX_DDP_NETFILTER_H
DECL|macro|__LINUX_DDP_NETFILTER_H
mdefine_line|#define __LINUX_DDP_NETFILTER_H
multiline_comment|/* DDP-specific defines for netfilter.  Complete me sometime.&n; * (C)1998 Rusty Russell -- This code is GPL.&n; */
macro_line|#include &lt;linux/netfilter.h&gt;
multiline_comment|/* Appletalk hooks */
DECL|macro|NF_DDP_INPUT
mdefine_line|#define NF_DDP_INPUT&t;0
DECL|macro|NF_DDP_FORWARD
mdefine_line|#define NF_DDP_FORWARD&t;1
DECL|macro|NF_DDP_OUTPUT
mdefine_line|#define NF_DDP_OUTPUT&t;2
macro_line|#endif /*__LINUX_DDP_NETFILTER_H*/
eof
