macro_line|#ifndef __LINUX_BRIDGE_EBT_MARK_T_H
DECL|macro|__LINUX_BRIDGE_EBT_MARK_T_H
mdefine_line|#define __LINUX_BRIDGE_EBT_MARK_T_H
DECL|struct|ebt_mark_t_info
r_struct
id|ebt_mark_t_info
(brace
DECL|member|mark
r_int
r_int
id|mark
suffix:semicolon
multiline_comment|/* EBT_ACCEPT, EBT_DROP, EBT_CONTINUE or EBT_RETURN */
DECL|member|target
r_int
id|target
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EBT_MARK_TARGET
mdefine_line|#define EBT_MARK_TARGET &quot;mark&quot;
macro_line|#endif
eof
