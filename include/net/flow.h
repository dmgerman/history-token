multiline_comment|/*&n; *&n; *&t;Generic internet FLOW.&n; *&n; */
macro_line|#ifndef _NET_FLOW_H
DECL|macro|_NET_FLOW_H
mdefine_line|#define _NET_FLOW_H
DECL|struct|flowi
r_struct
id|flowi
(brace
DECL|member|oif
r_int
id|oif
suffix:semicolon
DECL|member|iif
r_int
id|iif
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
DECL|member|fwmark
id|__u32
id|fwmark
suffix:semicolon
DECL|member|tos
id|__u8
id|tos
suffix:semicolon
DECL|member|scope
id|__u8
id|scope
suffix:semicolon
DECL|member|ip4_u
)brace
id|ip4_u
suffix:semicolon
r_struct
(brace
DECL|member|daddr
r_struct
id|in6_addr
op_star
id|daddr
suffix:semicolon
DECL|member|saddr
r_struct
id|in6_addr
op_star
id|saddr
suffix:semicolon
DECL|member|flowlabel
id|__u32
id|flowlabel
suffix:semicolon
DECL|member|ip6_u
)brace
id|ip6_u
suffix:semicolon
DECL|member|nl_u
)brace
id|nl_u
suffix:semicolon
DECL|macro|fl6_dst
mdefine_line|#define fl6_dst&t;&t;nl_u.ip6_u.daddr
DECL|macro|fl6_src
mdefine_line|#define fl6_src&t;&t;nl_u.ip6_u.saddr
DECL|macro|fl6_flowlabel
mdefine_line|#define fl6_flowlabel&t;nl_u.ip6_u.flowlabel
DECL|macro|fl4_dst
mdefine_line|#define fl4_dst&t;&t;nl_u.ip4_u.daddr
DECL|macro|fl4_src
mdefine_line|#define fl4_src&t;&t;nl_u.ip4_u.saddr
DECL|macro|fl4_fwmark
mdefine_line|#define fl4_fwmark&t;nl_u.ip4_u.fwmark
DECL|macro|fl4_tos
mdefine_line|#define fl4_tos&t;&t;nl_u.ip4_u.tos
DECL|macro|fl4_scope
mdefine_line|#define fl4_scope&t;nl_u.ip4_u.scope
DECL|member|proto
id|__u8
id|proto
suffix:semicolon
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|sport
id|__u16
id|sport
suffix:semicolon
DECL|member|dport
id|__u16
id|dport
suffix:semicolon
DECL|member|ports
)brace
id|ports
suffix:semicolon
r_struct
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|code
id|__u8
id|code
suffix:semicolon
DECL|member|icmpt
)brace
id|icmpt
suffix:semicolon
DECL|member|spi
id|__u32
id|spi
suffix:semicolon
DECL|member|uli_u
)brace
id|uli_u
suffix:semicolon
DECL|macro|fl_ip_sport
mdefine_line|#define fl_ip_sport&t;uli_u.ports.sport
DECL|macro|fl_ip_dport
mdefine_line|#define fl_ip_dport&t;uli_u.ports.dport
DECL|macro|fl_icmp_type
mdefine_line|#define fl_icmp_type&t;uli_u.icmpt.type
DECL|macro|fl_icmp_code
mdefine_line|#define fl_icmp_code&t;uli_u.icmpt.code
DECL|macro|fl_ipsec_spi
mdefine_line|#define fl_ipsec_spi&t;uli_u.spi
)brace
suffix:semicolon
macro_line|#endif
eof
