macro_line|#ifndef _IPT_MULTIPORT_H
DECL|macro|_IPT_MULTIPORT_H
mdefine_line|#define _IPT_MULTIPORT_H
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
DECL|enum|ipt_multiport_flags
r_enum
id|ipt_multiport_flags
(brace
DECL|enumerator|IPT_MULTIPORT_SOURCE
id|IPT_MULTIPORT_SOURCE
comma
DECL|enumerator|IPT_MULTIPORT_DESTINATION
id|IPT_MULTIPORT_DESTINATION
comma
DECL|enumerator|IPT_MULTIPORT_EITHER
id|IPT_MULTIPORT_EITHER
)brace
suffix:semicolon
DECL|macro|IPT_MULTI_PORTS
mdefine_line|#define IPT_MULTI_PORTS&t;15
multiline_comment|/* Must fit inside union ipt_matchinfo: 16 bytes */
DECL|struct|ipt_multiport
r_struct
id|ipt_multiport
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
id|IPT_MULTI_PORTS
)braket
suffix:semicolon
multiline_comment|/* Ports */
)brace
suffix:semicolon
macro_line|#endif /*_IPT_MULTIPORT_H*/
eof
