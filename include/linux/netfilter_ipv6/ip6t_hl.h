multiline_comment|/* ip6tables module for matching the Hop Limit value&n; * Maciej Soltysiak &lt;solt@dns.toxicfilms.tv&gt;&n; * Based on HW&squot;s ttl module */
macro_line|#ifndef _IP6T_HL_H
DECL|macro|_IP6T_HL_H
mdefine_line|#define _IP6T_HL_H
r_enum
(brace
DECL|enumerator|IP6T_HL_EQ
id|IP6T_HL_EQ
op_assign
l_int|0
comma
multiline_comment|/* equals */
DECL|enumerator|IP6T_HL_NE
id|IP6T_HL_NE
comma
multiline_comment|/* not equals */
DECL|enumerator|IP6T_HL_LT
id|IP6T_HL_LT
comma
multiline_comment|/* less than */
DECL|enumerator|IP6T_HL_GT
id|IP6T_HL_GT
comma
multiline_comment|/* greater than */
)brace
suffix:semicolon
DECL|struct|ip6t_hl_info
r_struct
id|ip6t_hl_info
(brace
DECL|member|mode
id|u_int8_t
id|mode
suffix:semicolon
DECL|member|hop_limit
id|u_int8_t
id|hop_limit
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
