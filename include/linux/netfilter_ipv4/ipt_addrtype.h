macro_line|#ifndef _IPT_ADDRTYPE_H
DECL|macro|_IPT_ADDRTYPE_H
mdefine_line|#define _IPT_ADDRTYPE_H
DECL|struct|ipt_addrtype_info
r_struct
id|ipt_addrtype_info
(brace
DECL|member|source
id|u_int16_t
id|source
suffix:semicolon
multiline_comment|/* source-type mask */
DECL|member|dest
id|u_int16_t
id|dest
suffix:semicolon
multiline_comment|/* dest-type mask */
DECL|member|invert_source
id|u_int32_t
id|invert_source
suffix:semicolon
DECL|member|invert_dest
id|u_int32_t
id|invert_dest
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
