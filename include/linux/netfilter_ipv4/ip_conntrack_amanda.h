macro_line|#ifndef _IP_CONNTRACK_AMANDA_H
DECL|macro|_IP_CONNTRACK_AMANDA_H
mdefine_line|#define _IP_CONNTRACK_AMANDA_H
multiline_comment|/* AMANDA tracking. */
r_struct
id|ip_conntrack_expect
suffix:semicolon
r_extern
r_int
r_int
(paren
op_star
id|ip_nat_amanda_hook
)paren
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
comma
r_int
r_int
id|matchoff
comma
r_int
r_int
id|matchlen
comma
r_struct
id|ip_conntrack_expect
op_star
id|exp
)paren
suffix:semicolon
macro_line|#endif /* _IP_CONNTRACK_AMANDA_H */
eof
