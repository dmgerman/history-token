macro_line|#ifndef _I386_CURRENT_H
DECL|macro|_I386_CURRENT_H
mdefine_line|#define _I386_CURRENT_H
r_struct
id|task_struct
suffix:semicolon
DECL|function|get_current
r_static
r_inline
r_struct
id|task_struct
op_star
id|get_current
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|current
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;andl %%esp,%0; &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|current
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
id|current
suffix:semicolon
)brace
DECL|macro|current
mdefine_line|#define current get_current()
macro_line|#endif /* !(_I386_CURRENT_H) */
eof
