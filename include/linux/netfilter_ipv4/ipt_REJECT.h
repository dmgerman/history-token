macro_line|#ifndef _IPT_REJECT_H
DECL|macro|_IPT_REJECT_H
mdefine_line|#define _IPT_REJECT_H
DECL|enum|ipt_reject_with
r_enum
id|ipt_reject_with
(brace
DECL|enumerator|IPT_ICMP_NET_UNREACHABLE
id|IPT_ICMP_NET_UNREACHABLE
comma
DECL|enumerator|IPT_ICMP_HOST_UNREACHABLE
id|IPT_ICMP_HOST_UNREACHABLE
comma
DECL|enumerator|IPT_ICMP_PROT_UNREACHABLE
id|IPT_ICMP_PROT_UNREACHABLE
comma
DECL|enumerator|IPT_ICMP_PORT_UNREACHABLE
id|IPT_ICMP_PORT_UNREACHABLE
comma
DECL|enumerator|IPT_ICMP_ECHOREPLY
id|IPT_ICMP_ECHOREPLY
comma
DECL|enumerator|IPT_ICMP_NET_PROHIBITED
id|IPT_ICMP_NET_PROHIBITED
comma
DECL|enumerator|IPT_ICMP_HOST_PROHIBITED
id|IPT_ICMP_HOST_PROHIBITED
comma
DECL|enumerator|IPT_TCP_RESET
id|IPT_TCP_RESET
)brace
suffix:semicolon
DECL|struct|ipt_reject_info
r_struct
id|ipt_reject_info
(brace
DECL|member|with
r_enum
id|ipt_reject_with
id|with
suffix:semicolon
multiline_comment|/* reject type */
)brace
suffix:semicolon
macro_line|#endif /*_IPT_REJECT_H*/
eof
