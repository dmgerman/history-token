macro_line|#ifndef _FIB_LOOKUP_H
DECL|macro|_FIB_LOOKUP_H
mdefine_line|#define _FIB_LOOKUP_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;net/ip_fib.h&gt;
DECL|struct|fib_alias
r_struct
id|fib_alias
(brace
DECL|member|fa_list
r_struct
id|list_head
id|fa_list
suffix:semicolon
DECL|member|fa_info
r_struct
id|fib_info
op_star
id|fa_info
suffix:semicolon
DECL|member|fa_tos
id|u8
id|fa_tos
suffix:semicolon
DECL|member|fa_type
id|u8
id|fa_type
suffix:semicolon
DECL|member|fa_scope
id|u8
id|fa_scope
suffix:semicolon
DECL|member|fa_state
id|u8
id|fa_state
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FA_S_ACCESSED
mdefine_line|#define FA_S_ACCESSED&t;0x01
macro_line|#endif /* _FIB_LOOKUP_H */
eof
