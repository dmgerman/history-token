macro_line|#ifndef _IPT_MARK_H_target
DECL|macro|_IPT_MARK_H_target
mdefine_line|#define _IPT_MARK_H_target
multiline_comment|/* Version 0 */
DECL|struct|ipt_mark_target_info
r_struct
id|ipt_mark_target_info
(brace
DECL|member|mark
r_int
r_int
id|mark
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Version 1 */
r_enum
(brace
DECL|enumerator|IPT_MARK_SET
id|IPT_MARK_SET
op_assign
l_int|0
comma
DECL|enumerator|IPT_MARK_AND
id|IPT_MARK_AND
comma
DECL|enumerator|IPT_MARK_OR
id|IPT_MARK_OR
)brace
suffix:semicolon
DECL|struct|ipt_mark_target_info_v1
r_struct
id|ipt_mark_target_info_v1
(brace
DECL|member|mark
r_int
r_int
id|mark
suffix:semicolon
DECL|member|mode
id|u_int8_t
id|mode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_MARK_H_target*/
eof
