macro_line|#ifndef _IP6T_MULTIPORT_H
DECL|macro|_IP6T_MULTIPORT_H
mdefine_line|#define _IP6T_MULTIPORT_H
macro_line|#include &lt;linux/netfilter_ipv6/ip6_tables.h&gt;
DECL|enum|ip6t_multiport_flags
r_enum
id|ip6t_multiport_flags
(brace
DECL|enumerator|IP6T_MULTIPORT_SOURCE
id|IP6T_MULTIPORT_SOURCE
comma
DECL|enumerator|IP6T_MULTIPORT_DESTINATION
id|IP6T_MULTIPORT_DESTINATION
comma
DECL|enumerator|IP6T_MULTIPORT_EITHER
id|IP6T_MULTIPORT_EITHER
)brace
suffix:semicolon
DECL|macro|IP6T_MULTI_PORTS
mdefine_line|#define IP6T_MULTI_PORTS&t;15
multiline_comment|/* Must fit inside union ip6t_matchinfo: 16 bytes */
DECL|struct|ip6t_multiport
r_struct
id|ip6t_multiport
(brace
DECL|member|flags
id|u_int8_t
id|flags
suffix:semicolon
multiline_comment|/* Type of comparison */
DECL|member|count
id|u_int8_t
id|count
suffix:semicolon
multiline_comment|/* Number of ports */
DECL|member|ports
id|u_int16_t
id|ports
(braket
id|IP6T_MULTI_PORTS
)braket
suffix:semicolon
multiline_comment|/* Ports */
)brace
suffix:semicolon
macro_line|#endif /*_IPT_MULTIPORT_H*/
eof
