macro_line|#ifndef _PARISC_CURRENT_H
DECL|macro|_PARISC_CURRENT_H
mdefine_line|#define _PARISC_CURRENT_H
macro_line|#include &lt;asm/processor.h&gt;
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
id|asm
c_func
(paren
l_string|&quot;copy 30,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|current
)paren
)paren
suffix:semicolon
r_return
(paren
r_struct
id|task_struct
op_star
)paren
(paren
(paren
r_int
)paren
id|current
op_amp
op_complement
(paren
id|THREAD_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|macro|current
mdefine_line|#define current get_current()
macro_line|#endif /* !(_PARISC_CURRENT_H) */
eof
