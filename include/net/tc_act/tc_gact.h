macro_line|#ifndef __NET_TC_GACT_H
DECL|macro|__NET_TC_GACT_H
mdefine_line|#define __NET_TC_GACT_H
macro_line|#include &lt;net/act_api.h&gt;
DECL|struct|tcf_gact
r_struct
id|tcf_gact
(brace
id|tca_gen
c_func
(paren
id|gact
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_GACT_PROB
DECL|member|ptype
id|u16
id|ptype
suffix:semicolon
DECL|member|pval
id|u16
id|pval
suffix:semicolon
DECL|member|paction
r_int
id|paction
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif
eof
