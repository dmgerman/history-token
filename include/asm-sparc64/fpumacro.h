multiline_comment|/* fpumacro.h: FPU related macros.&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_FPUMACRO_H
DECL|macro|_SPARC64_FPUMACRO_H
mdefine_line|#define _SPARC64_FPUMACRO_H
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/visasm.h&gt;
DECL|struct|fpustate
r_struct
id|fpustate
(brace
DECL|member|regs
id|u32
id|regs
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FPUSTATE
mdefine_line|#define FPUSTATE (struct fpustate *)(((unsigned long)current) + AOFF_task_fpregs)
DECL|function|fprs_read
r_extern
id|__inline__
r_int
r_int
id|fprs_read
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%fprs, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|fprs_write
r_extern
id|__inline__
r_void
id|fprs_write
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wr %0, 0x0, %%fprs&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC64_FPUMACRO_H) */
eof
