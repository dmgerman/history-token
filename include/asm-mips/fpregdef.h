multiline_comment|/*&n; * Definitions for the FPU register names&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_FPREGDEF_H
DECL|macro|__ASM_MIPS_FPREGDEF_H
mdefine_line|#define __ASM_MIPS_FPREGDEF_H
multiline_comment|/*&n; * These definitions only cover the R3000-ish 16/32 register model.&n; * But we&squot;re trying to be R3000 friendly anyway ...&n; */
DECL|macro|fv0
mdefine_line|#define fv0&t;$f0      /* return value */
DECL|macro|fv0f
mdefine_line|#define fv0f&t;$f1
DECL|macro|fv1
mdefine_line|#define fv1&t;$f2
DECL|macro|fv1f
mdefine_line|#define fv1f&t;$f3
DECL|macro|fa0
mdefine_line|#define fa0&t;$f12     /* argument registers */
DECL|macro|fa0f
mdefine_line|#define fa0f&t;$f13
DECL|macro|fa1
mdefine_line|#define fa1&t;$f14
DECL|macro|fa1f
mdefine_line|#define fa1f&t;$f15
DECL|macro|ft0
mdefine_line|#define ft0&t;$f4      /* caller saved */
DECL|macro|ft0f
mdefine_line|#define ft0f&t;$f5
DECL|macro|ft1
mdefine_line|#define ft1&t;$f6
DECL|macro|ft1f
mdefine_line|#define ft1f&t;$f7
DECL|macro|ft2
mdefine_line|#define ft2&t;$f8
DECL|macro|ft2f
mdefine_line|#define ft2f&t;$f9
DECL|macro|ft3
mdefine_line|#define ft3&t;$f10
DECL|macro|ft3f
mdefine_line|#define ft3f&t;$f11
DECL|macro|ft4
mdefine_line|#define ft4&t;$f16
DECL|macro|ft4f
mdefine_line|#define ft4f&t;$f17
DECL|macro|ft5
mdefine_line|#define ft5&t;$f18
DECL|macro|ft5f
mdefine_line|#define ft5f&t;$f19
DECL|macro|fs0
mdefine_line|#define fs0&t;$f20     /* callee saved */
DECL|macro|fs0f
mdefine_line|#define fs0f&t;$f21
DECL|macro|fs1
mdefine_line|#define fs1&t;$f22
DECL|macro|fs1f
mdefine_line|#define fs1f&t;$f23
DECL|macro|fs2
mdefine_line|#define fs2&t;$f24
DECL|macro|fs2f
mdefine_line|#define fs2f&t;$f25
DECL|macro|fs3
mdefine_line|#define fs3&t;$f26
DECL|macro|fs3f
mdefine_line|#define fs3f&t;$f27
DECL|macro|fs4
mdefine_line|#define fs4&t;$f28
DECL|macro|fs4f
mdefine_line|#define fs4f&t;$f29
DECL|macro|fs5
mdefine_line|#define fs5&t;$f30
DECL|macro|fs5f
mdefine_line|#define fs5f&t;$f31
DECL|macro|fcr31
mdefine_line|#define fcr31&t;$31      /* FPU status register */
macro_line|#endif /* !defined (__ASM_MIPS_FPREGDEF_H) */
eof
