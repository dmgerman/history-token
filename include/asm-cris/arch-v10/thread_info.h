macro_line|#ifndef _ASM_ARCH_THREAD_INFO_H
DECL|macro|_ASM_ARCH_THREAD_INFO_H
mdefine_line|#define _ASM_ARCH_THREAD_INFO_H
multiline_comment|/* how to get the thread information struct from C */
DECL|function|current_thread_info
r_extern
r_inline
r_struct
id|thread_info
op_star
id|current_thread_info
c_func
(paren
r_void
)paren
(brace
r_struct
id|thread_info
op_star
id|ti
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;and.d $sp,%0; &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ti
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
op_complement
l_int|8191UL
)paren
)paren
suffix:semicolon
r_return
id|ti
suffix:semicolon
)brace
macro_line|#endif
eof
