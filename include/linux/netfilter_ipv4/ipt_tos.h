macro_line|#ifndef _IPT_TOS_H
DECL|macro|_IPT_TOS_H
mdefine_line|#define _IPT_TOS_H
DECL|struct|ipt_tos_info
r_struct
id|ipt_tos_info
(brace
DECL|member|tos
id|u_int8_t
id|tos
suffix:semicolon
DECL|member|invert
id|u_int8_t
id|invert
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifndef IPTOS_NORMALSVC
DECL|macro|IPTOS_NORMALSVC
mdefine_line|#define IPTOS_NORMALSVC 0
macro_line|#endif
macro_line|#endif /*_IPT_TOS_H*/
eof
