macro_line|#ifndef _IPT_STATE_H
DECL|macro|_IPT_STATE_H
mdefine_line|#define _IPT_STATE_H
DECL|macro|IPT_STATE_BIT
mdefine_line|#define IPT_STATE_BIT(ctinfo) (1 &lt;&lt; ((ctinfo)%IP_CT_IS_REPLY+1))
DECL|macro|IPT_STATE_INVALID
mdefine_line|#define IPT_STATE_INVALID (1 &lt;&lt; 0)
DECL|struct|ipt_state_info
r_struct
id|ipt_state_info
(brace
DECL|member|statemask
r_int
r_int
id|statemask
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_STATE_H*/
eof
