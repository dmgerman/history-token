macro_line|#ifndef _IP_NAT_HELPER_H
DECL|macro|_IP_NAT_HELPER_H
mdefine_line|#define _IP_NAT_HELPER_H
multiline_comment|/* NAT protocol helper routines. */
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
macro_line|#include &lt;linux/module.h&gt;
r_struct
id|sk_buff
suffix:semicolon
multiline_comment|/* Flags */
multiline_comment|/* NAT helper must be called on every packet (for TCP) */
DECL|macro|IP_NAT_HELPER_F_ALWAYS
mdefine_line|#define IP_NAT_HELPER_F_ALWAYS&t;&t;0x01
DECL|struct|ip_nat_helper
r_struct
id|ip_nat_helper
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* Internal use */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name of the module */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* Flags (see above) */
DECL|member|me
r_struct
id|module
op_star
id|me
suffix:semicolon
multiline_comment|/* pointer to self */
multiline_comment|/* Mask of things we will help: vs. tuple from server */
DECL|member|tuple
r_struct
id|ip_conntrack_tuple
id|tuple
suffix:semicolon
DECL|member|mask
r_struct
id|ip_conntrack_tuple
id|mask
suffix:semicolon
multiline_comment|/* Helper function: returns verdict */
DECL|member|help
r_int
r_int
(paren
op_star
id|help
)paren
(paren
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_struct
id|ip_conntrack_expect
op_star
id|exp
comma
r_struct
id|ip_nat_info
op_star
id|info
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_int
r_int
id|hooknum
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|ip_nat_helper_register
c_func
(paren
r_struct
id|ip_nat_helper
op_star
id|me
)paren
suffix:semicolon
r_extern
r_void
id|ip_nat_helper_unregister
c_func
(paren
r_struct
id|ip_nat_helper
op_star
id|me
)paren
suffix:semicolon
r_extern
r_struct
id|ip_nat_helper
op_star
id|ip_nat_find_helper
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
suffix:semicolon
r_extern
r_struct
id|ip_nat_helper
op_star
id|__ip_nat_find_helper
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
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
