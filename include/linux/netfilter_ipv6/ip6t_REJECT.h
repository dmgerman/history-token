macro_line|#ifndef _IP6T_REJECT_H
DECL|macro|_IP6T_REJECT_H
mdefine_line|#define _IP6T_REJECT_H
DECL|enum|ip6t_reject_with
r_enum
id|ip6t_reject_with
(brace
DECL|enumerator|IP6T_ICMP_NET_UNREACHABLE
id|IP6T_ICMP_NET_UNREACHABLE
comma
DECL|enumerator|IP6T_ICMP_HOST_UNREACHABLE
id|IP6T_ICMP_HOST_UNREACHABLE
comma
DECL|enumerator|IP6T_ICMP_PROT_UNREACHABLE
id|IP6T_ICMP_PROT_UNREACHABLE
comma
DECL|enumerator|IP6T_ICMP_PORT_UNREACHABLE
id|IP6T_ICMP_PORT_UNREACHABLE
comma
DECL|enumerator|IP6T_ICMP_ECHOREPLY
id|IP6T_ICMP_ECHOREPLY
)brace
suffix:semicolon
DECL|struct|ip6t_reject_info
r_struct
id|ip6t_reject_info
(brace
DECL|member|with
r_enum
id|ip6t_reject_with
id|with
suffix:semicolon
multiline_comment|/* reject type */
)brace
suffix:semicolon
macro_line|#endif /*_IPT_REJECT_H*/
eof
