macro_line|#ifndef __NET_TC_PED_H
DECL|macro|__NET_TC_PED_H
mdefine_line|#define __NET_TC_PED_H
macro_line|#include &lt;net/act_api.h&gt;
DECL|struct|tcf_pedit
r_struct
id|tcf_pedit
(brace
id|tca_gen
c_func
(paren
id|pedit
)paren
suffix:semicolon
DECL|member|nkeys
r_int
r_char
id|nkeys
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|keys
r_struct
id|tc_pedit_key
op_star
id|keys
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
