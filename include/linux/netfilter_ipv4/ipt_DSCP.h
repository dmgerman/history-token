multiline_comment|/* iptables module for setting the IPv4 DSCP field&n; *&n; * (C) 2002 Harald Welte &lt;laforge@gnumonks.org&gt;&n; * based on ipt_FTOS.c (C) 2000 by Matthew G. Marsh &lt;mgm@paktronix.com&gt;&n; * This software is distributed under GNU GPL v2, 1991&n; * &n; * See RFC2474 for a description of the DSCP field within the IP Header.&n; *&n; * ipt_DSCP.h,v 1.7 2002/03/14 12:03:13 laforge Exp&n;*/
macro_line|#ifndef _IPT_DSCP_TARGET_H
DECL|macro|_IPT_DSCP_TARGET_H
mdefine_line|#define _IPT_DSCP_TARGET_H
macro_line|#include &lt;linux/netfilter_ipv4/ipt_dscp.h&gt;
multiline_comment|/* target info */
DECL|struct|ipt_DSCP_info
r_struct
id|ipt_DSCP_info
(brace
DECL|member|dscp
id|u_int8_t
id|dscp
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _IPT_DSCP_TARGET_H */
eof
