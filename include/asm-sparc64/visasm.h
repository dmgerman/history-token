multiline_comment|/* $Id: visasm.h,v 1.4 1999/04/19 01:25:55 davem Exp $ */
macro_line|#ifndef _SPARC64_VISASM_H
DECL|macro|_SPARC64_VISASM_H
mdefine_line|#define _SPARC64_VISASM_H
multiline_comment|/* visasm.h:  FPU saving macros for VIS routines&n; *&n; * Copyright (C) 1998 Jakub Jelinek (jj@ultra.linux.cz)&n; */
macro_line|#include &lt;asm/pstate.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|AOFF_task_fpregs
mdefine_line|#define AOFF_task_fpregs&t;(((ASIZ_task) + (64 - 1)) &amp; ~(64 - 1))
multiline_comment|/* Clobbers %o5, %g1, %g2, %g3, %g7, %icc, %xcc */
DECL|macro|VISEntry
mdefine_line|#define VISEntry&t;&t;&t;&t;&t;&bslash;&n;&t;rd&t;&t;%fprs, %o5;&t;&t;&t;&bslash;&n;&t;andcc&t;&t;%o5, (FPRS_FEF|FPRS_DU), %g0;&t;&bslash;&n;&t;be,pt&t;&t;%icc, 297f;&t;&t;&t;&bslash;&n;&t; sethi&t;&t;%hi(297f), %g7;&t;&t;&t;&bslash;&n;&t;ba,pt&t;&t;%xcc, VISenter;&t;&t;&t;&bslash;&n;&t; or&t;&t;%g7, %lo(297f), %g7;&t;&t;&bslash;&n;297:&t;wr&t;&t;%g0, FPRS_FEF, %fprs;&t;&t;&bslash;&n;
DECL|macro|VISExit
mdefine_line|#define VISExit&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wr&t;&t;%g0, 0, %fprs;
multiline_comment|/* Clobbers %o5, %g1, %g2, %g3, %g7, %icc, %xcc.&n; * Must preserve %o5 between VISEntryHalf and VISExitHalf */
DECL|macro|VISEntryHalf
mdefine_line|#define VISEntryHalf&t;&t;&t;&t;&t;&bslash;&n;&t;rd&t;&t;%fprs, %o5;&t;&t;&t;&bslash;&n;&t;andcc&t;&t;%o5, FPRS_FEF, %g0;&t;&t;&bslash;&n;&t;be,pt&t;&t;%icc, 297f;&t;&t;&t;&bslash;&n;&t; sethi&t;&t;%hi(298f), %g7;&t;&t;&t;&bslash;&n;&t;ba,pt&t;&t;%xcc, VISenterhalf;&t;&t;&bslash;&n;&t; or&t;&t;%g7, %lo(298f), %g7;&t;&t;&bslash;&n;&t;clr&t;&t;%o5;&t;&t;&t;&t;&bslash;&n;297:&t;wr&t;&t;%o5, FPRS_FEF, %fprs;&t;&t;&bslash;&n;298:
DECL|macro|VISExitHalf
mdefine_line|#define VISExitHalf&t;&t;&t;&t;&t;&bslash;&n;&t;wr&t;&t;%o5, 0, %fprs;
macro_line|#ifndef __ASSEMBLY__&t;
DECL|function|save_and_clear_fpu
r_extern
id|__inline__
r_void
id|save_and_clear_fpu
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
"&quot;"
id|rd
op_mod
op_mod
id|fprs
comma
op_mod
op_mod
id|o5
id|andcc
op_mod
op_mod
id|o5
comma
op_mod
l_int|0
comma
op_mod
op_mod
id|g0
id|be
comma
id|pt
op_mod
op_mod
id|icc
comma
l_float|299f
id|sethi
op_mod
op_mod
id|hi
c_func
(paren
l_float|298f
)paren
comma
op_mod
op_mod
id|g7
id|ba
id|VISenter
op_logical_neg
id|Note
dot
id|This
id|cannot
id|be
id|bp
comma
id|as
id|it
id|may
id|be
id|too
id|far
id|from
id|VISenter
dot
op_logical_or
op_mod
op_mod
id|g7
comma
op_mod
op_mod
id|lo
c_func
(paren
l_float|298f
)paren
comma
op_mod
op_mod
id|g7
l_int|298
suffix:colon
id|wr
op_mod
op_mod
id|g0
comma
l_int|0
comma
op_mod
op_mod
id|fprs
l_int|299
suffix:colon
l_string|&quot; : : &quot;
id|i
"&quot;"
(paren
id|FPRS_FEF
op_or
id|FPRS_DU
)paren
suffix:colon
l_string|&quot;o5&quot;
comma
l_string|&quot;g1&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* _SPARC64_ASI_H */
eof
