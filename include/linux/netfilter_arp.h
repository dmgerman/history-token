macro_line|#ifndef __LINUX_ARP_NETFILTER_H
DECL|macro|__LINUX_ARP_NETFILTER_H
mdefine_line|#define __LINUX_ARP_NETFILTER_H
multiline_comment|/* ARP-specific defines for netfilter.&n; * (C)2002 Rusty Russell IBM -- This code is GPL.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
multiline_comment|/* There is no PF_ARP. */
DECL|macro|NF_ARP
mdefine_line|#define NF_ARP&t;&t;0
multiline_comment|/* ARP Hooks */
DECL|macro|NF_ARP_IN
mdefine_line|#define NF_ARP_IN&t;0
DECL|macro|NF_ARP_OUT
mdefine_line|#define NF_ARP_OUT&t;1
DECL|macro|NF_ARP_NUMHOOKS
mdefine_line|#define NF_ARP_NUMHOOKS&t;2
macro_line|#endif /* __LINUX_ARP_NETFILTER_H */
eof
