multiline_comment|/* $Id: visasm.h,v 1.5 2001/04/24 01:09:12 davem Exp $ */
macro_line|#ifndef _SPARC64_VISASM_H
DECL|macro|_SPARC64_VISASM_H
mdefine_line|#define _SPARC64_VISASM_H
multiline_comment|/* visasm.h:  FPU saving macros for VIS routines&n; *&n; * Copyright (C) 1998 Jakub Jelinek (jj@ultra.linux.cz)&n; */
macro_line|#include &lt;asm/pstate.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/* Clobbers %o5, %g1, %g2, %g3, %g7, %icc, %xcc */
DECL|macro|VISEntry
mdefine_line|#define VISEntry&t;&t;&t;&t;&t;&bslash;&n;&t;rd&t;&t;%fprs, %o5;&t;&t;&t;&bslash;&n;&t;andcc&t;&t;%o5, (FPRS_FEF|FPRS_DU), %g0;&t;&bslash;&n;&t;be,pt&t;&t;%icc, 297f;&t;&t;&t;&bslash;&n;&t; sethi&t;&t;%hi(297f), %g7;&t;&t;&t;&bslash;&n;&t;sethi&t;&t;%hi(VISenter), %g1;&t;&t;&bslash;&n;&t;jmpl&t;&t;%g1 + %lo(VISenter), %g0;&t;&bslash;&n;&t; or&t;&t;%g7, %lo(297f), %g7;&t;&t;&bslash;&n;297:&t;wr&t;&t;%g0, FPRS_FEF, %fprs;&t;&t;&bslash;&n;
DECL|macro|VISExit
mdefine_line|#define VISExit&t;&t;&t;&t;&t;&t;&bslash;&n;&t;wr&t;&t;%g0, 0, %fprs;
multiline_comment|/* Clobbers %o5, %g1, %g2, %g3, %g7, %icc, %xcc.&n; * Must preserve %o5 between VISEntryHalf and VISExitHalf */
DECL|macro|VISEntryHalf
mdefine_line|#define VISEntryHalf&t;&t;&t;&t;&t;&bslash;&n;&t;rd&t;&t;%fprs, %o5;&t;&t;&t;&bslash;&n;&t;andcc&t;&t;%o5, FPRS_FEF, %g0;&t;&t;&bslash;&n;&t;be,pt&t;&t;%icc, 297f;&t;&t;&t;&bslash;&n;&t; sethi&t;&t;%hi(298f), %g7;&t;&t;&t;&bslash;&n;&t;sethi&t;&t;%hi(VISenterhalf), %g1;&t;&t;&bslash;&n;&t;jmpl&t;&t;%g1 + %lo(VISenterhalf), %g0;&t;&bslash;&n;&t; or&t;&t;%g7, %lo(298f), %g7;&t;&t;&bslash;&n;&t;clr&t;&t;%o5;&t;&t;&t;&t;&bslash;&n;297:&t;wr&t;&t;%o5, FPRS_FEF, %fprs;&t;&t;&bslash;&n;298:
DECL|macro|VISExitHalf
mdefine_line|#define VISExitHalf&t;&t;&t;&t;&t;&bslash;&n;&t;wr&t;&t;%o5, 0, %fprs;
macro_line|#ifndef __ASSEMBLY__&t;
DECL|function|save_and_clear_fpu
r_static
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
l_string|&quot;&t;&t;rd %%fprs, %%o5&bslash;n&quot;
l_string|&quot;&t;&t;andcc %%o5, %0, %%g0&bslash;n&quot;
l_string|&quot;&t;&t;be,pt %%icc, 299f&bslash;n&quot;
l_string|&quot;&t;&t; sethi %%hi(298f), %%g7&bslash;n&quot;
l_string|&quot;&t;&t;sethi %%hi(VISenter), %%g1&bslash;n&quot;
l_string|&quot;&t;&t;jmpl %%g1 + %%lo(VISenter), %%g0&bslash;n&quot;
l_string|&quot;&t;&t; or %%g7, %%lo(298f), %%g7&bslash;n&quot;
l_string|&quot;&t;298:&t;wr %%g0, 0, %%fprs&bslash;n&quot;
l_string|&quot;&t;299:&bslash;n&quot;
l_string|&quot;&t;&t;&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
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
