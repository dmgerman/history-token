multiline_comment|/* iptables module for matching the IPv4 DSCP field&n; *&n; * (C) 2002 Harald Welte &lt;laforge@gnumonks.org&gt;&n; * This software is distributed under GNU GPL v2, 1991&n; * &n; * See RFC2474 for a description of the DSCP field within the IP Header.&n; *&n; * ipt_dscp.h,v 1.3 2002/08/05 19:00:21 laforge Exp&n;*/
macro_line|#ifndef _IPT_DSCP_H
DECL|macro|_IPT_DSCP_H
mdefine_line|#define _IPT_DSCP_H
DECL|macro|IPT_DSCP_MASK
mdefine_line|#define IPT_DSCP_MASK&t;0xfc&t;/* 11111100 */
DECL|macro|IPT_DSCP_SHIFT
mdefine_line|#define IPT_DSCP_SHIFT&t;2
DECL|macro|IPT_DSCP_MAX
mdefine_line|#define IPT_DSCP_MAX&t;0x3f&t;/* 00111111 */
multiline_comment|/* match info */
DECL|struct|ipt_dscp_info
r_struct
id|ipt_dscp_info
(brace
DECL|member|dscp
id|u_int8_t
id|dscp
suffix:semicolon
DECL|member|invert
id|u_int8_t
id|invert
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _IPT_DSCP_H */
eof
