macro_line|#ifndef _IP_NAT_CORE_H
DECL|macro|_IP_NAT_CORE_H
mdefine_line|#define _IP_NAT_CORE_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
multiline_comment|/* This header used to share core functionality between the standalone&n;   NAT module, and the compatibility layer&squot;s use of NAT for masquerading. */
r_extern
r_int
id|ip_nat_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ip_nat_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|do_bindings
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|conntrackinfo
comma
r_struct
id|ip_nat_info
op_star
id|info
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
r_extern
r_struct
id|list_head
id|protos
suffix:semicolon
r_extern
r_int
id|icmp_reply_translation
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
id|conntrack
comma
r_int
r_int
id|hooknum
comma
r_int
id|dir
)paren
suffix:semicolon
r_extern
r_void
id|replace_in_hashes
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_struct
id|ip_nat_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|place_in_hashes
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_struct
id|ip_nat_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* Built-in protocols. */
r_extern
r_struct
id|ip_nat_protocol
id|ip_nat_protocol_tcp
suffix:semicolon
r_extern
r_struct
id|ip_nat_protocol
id|ip_nat_protocol_udp
suffix:semicolon
r_extern
r_struct
id|ip_nat_protocol
id|ip_nat_protocol_icmp
suffix:semicolon
multiline_comment|/* Call this before modifying an existing IP packet: ensures it is&n;   modifiable and linear to the point you care about (writable_len).&n;   Returns true or false. */
r_extern
r_int
id|skb_ip_make_writable
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
id|writable_len
)paren
suffix:semicolon
macro_line|#endif /* _IP_NAT_CORE_H */
eof
