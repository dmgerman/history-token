macro_line|#ifndef _IP_NAT_HELPER_H
DECL|macro|_IP_NAT_HELPER_H
mdefine_line|#define _IP_NAT_HELPER_H
multiline_comment|/* NAT protocol helper routines. */
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
macro_line|#include &lt;linux/module.h&gt;
r_struct
id|sk_buff
suffix:semicolon
multiline_comment|/* These return true or false. */
r_extern
r_int
id|ip_nat_mangle_tcp_packet
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_int
r_int
id|match_offset
comma
r_int
r_int
id|match_len
comma
r_const
r_char
op_star
id|rep_buffer
comma
r_int
r_int
id|rep_len
)paren
suffix:semicolon
r_extern
r_int
id|ip_nat_mangle_udp_packet
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_int
r_int
id|match_offset
comma
r_int
r_int
id|match_len
comma
r_const
r_char
op_star
id|rep_buffer
comma
r_int
r_int
id|rep_len
)paren
suffix:semicolon
r_extern
r_int
id|ip_nat_seq_adjust
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
)paren
suffix:semicolon
multiline_comment|/* Setup NAT on this expected conntrack so it follows master, but goes&n; * to port ct-&gt;master-&gt;saved_proto. */
r_extern
r_void
id|ip_nat_follow_master
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|ct
)paren
suffix:semicolon
macro_line|#endif
eof
