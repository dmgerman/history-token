multiline_comment|/* IP tables module for matching the value of the TTL&n; * (C) 2000 by Harald Welte &lt;laforge@gnumonks.org&gt; */
macro_line|#ifndef _IPT_TTL_H
DECL|macro|_IPT_TTL_H
mdefine_line|#define _IPT_TTL_H
r_enum
(brace
DECL|enumerator|IPT_TTL_EQ
id|IPT_TTL_EQ
op_assign
l_int|0
comma
multiline_comment|/* equals */
DECL|enumerator|IPT_TTL_NE
id|IPT_TTL_NE
comma
multiline_comment|/* not equals */
DECL|enumerator|IPT_TTL_LT
id|IPT_TTL_LT
comma
multiline_comment|/* less than */
DECL|enumerator|IPT_TTL_GT
id|IPT_TTL_GT
comma
multiline_comment|/* greater than */
)brace
suffix:semicolon
DECL|struct|ipt_ttl_info
r_struct
id|ipt_ttl_info
(brace
DECL|member|mode
id|u_int8_t
id|mode
suffix:semicolon
DECL|member|ttl
id|u_int8_t
id|ttl
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
