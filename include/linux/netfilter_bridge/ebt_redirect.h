macro_line|#ifndef __LINUX_BRIDGE_EBT_REDIRECT_H
DECL|macro|__LINUX_BRIDGE_EBT_REDIRECT_H
mdefine_line|#define __LINUX_BRIDGE_EBT_REDIRECT_H
DECL|struct|ebt_redirect_info
r_struct
id|ebt_redirect_info
(brace
multiline_comment|/* EBT_ACCEPT, EBT_DROP, EBT_CONTINUE or EBT_RETURN */
DECL|member|target
r_int
id|target
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EBT_REDIRECT_TARGET
mdefine_line|#define EBT_REDIRECT_TARGET &quot;redirect&quot;
macro_line|#endif
eof
