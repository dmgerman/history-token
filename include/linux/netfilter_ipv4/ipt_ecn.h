multiline_comment|/* iptables module for matching the ECN header in IPv4 and TCP header&n; *&n; * (C) 2002 Harald Welte &lt;laforge@gnumonks.org&gt;&n; *&n; * This software is distributed under GNU GPL v2, 1991&n; * &n; * ipt_ecn.h,v 1.4 2002/08/05 19:39:00 laforge Exp&n;*/
macro_line|#ifndef _IPT_ECN_H
DECL|macro|_IPT_ECN_H
mdefine_line|#define _IPT_ECN_H
macro_line|#include &lt;linux/netfilter_ipv4/ipt_dscp.h&gt;
DECL|macro|IPT_ECN_IP_MASK
mdefine_line|#define IPT_ECN_IP_MASK&t;(~IPT_DSCP_MASK)
DECL|macro|IPT_ECN_OP_MATCH_IP
mdefine_line|#define IPT_ECN_OP_MATCH_IP&t;0x01
DECL|macro|IPT_ECN_OP_MATCH_ECE
mdefine_line|#define IPT_ECN_OP_MATCH_ECE&t;0x10
DECL|macro|IPT_ECN_OP_MATCH_CWR
mdefine_line|#define IPT_ECN_OP_MATCH_CWR&t;0x20
DECL|macro|IPT_ECN_OP_MATCH_MASK
mdefine_line|#define IPT_ECN_OP_MATCH_MASK&t;0xce
multiline_comment|/* match info */
DECL|struct|ipt_ecn_info
r_struct
id|ipt_ecn_info
(brace
DECL|member|operation
id|u_int8_t
id|operation
suffix:semicolon
DECL|member|invert
id|u_int8_t
id|invert
suffix:semicolon
DECL|member|ip_ect
id|u_int8_t
id|ip_ect
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|ect
id|u_int8_t
id|ect
suffix:semicolon
DECL|member|tcp
)brace
id|tcp
suffix:semicolon
DECL|member|proto
)brace
id|proto
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _IPT_ECN_H */
eof
