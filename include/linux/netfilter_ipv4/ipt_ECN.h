multiline_comment|/* Header file for iptables ipt_ECN target&n; *&n; * (C) 2002 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; *&n; * This software is distributed under GNU GPL v2, 1991&n; * &n; * ipt_ECN.h,v 1.3 2002/05/29 12:17:40 laforge Exp&n;*/
macro_line|#ifndef _IPT_ECN_TARGET_H
DECL|macro|_IPT_ECN_TARGET_H
mdefine_line|#define _IPT_ECN_TARGET_H
macro_line|#include &lt;linux/netfilter_ipv4/ipt_DSCP.h&gt;
DECL|macro|IPT_ECN_IP_MASK
mdefine_line|#define IPT_ECN_IP_MASK&t;(~IPT_DSCP_MASK)
DECL|macro|IPT_ECN_OP_SET_IP
mdefine_line|#define IPT_ECN_OP_SET_IP&t;0x01&t;/* set ECN bits of IPv4 header */
DECL|macro|IPT_ECN_OP_SET_ECE
mdefine_line|#define IPT_ECN_OP_SET_ECE&t;0x10&t;/* set ECE bit of TCP header */
DECL|macro|IPT_ECN_OP_SET_CWR
mdefine_line|#define IPT_ECN_OP_SET_CWR&t;0x20&t;/* set CWR bit of TCP header */
DECL|macro|IPT_ECN_OP_MASK
mdefine_line|#define IPT_ECN_OP_MASK&t;&t;0xce
DECL|struct|ipt_ECN_info
r_struct
id|ipt_ECN_info
(brace
DECL|member|operation
id|u_int8_t
id|operation
suffix:semicolon
multiline_comment|/* bitset of operations */
DECL|member|ip_ect
id|u_int8_t
id|ip_ect
suffix:semicolon
multiline_comment|/* ECT codepoint of IPv4 header, pre-shifted */
r_union
(brace
r_struct
(brace
DECL|member|ece
DECL|member|cwr
id|u_int8_t
id|ece
suffix:colon
l_int|1
comma
id|cwr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* TCP ECT bits */
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
macro_line|#endif /* _IPT_ECN_TARGET_H */
eof
