macro_line|#ifndef __NET_TC_IPT_H
DECL|macro|__NET_TC_IPT_H
mdefine_line|#define __NET_TC_IPT_H
macro_line|#include &lt;net/act_api.h&gt;
r_struct
id|ipt_entry_target
suffix:semicolon
DECL|struct|tcf_ipt
r_struct
id|tcf_ipt
(brace
id|tca_gen
c_func
(paren
id|ipt
)paren
suffix:semicolon
DECL|member|hook
id|u32
id|hook
suffix:semicolon
DECL|member|tname
r_char
op_star
id|tname
suffix:semicolon
DECL|member|t
r_struct
id|ipt_entry_target
op_star
id|t
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
