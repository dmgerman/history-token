multiline_comment|/*---------------------------------------------------------------------------+&n; |  fpu_asm.h                                                                |&n; |                                                                           |&n; | Copyright (C) 1992,1995,1997                                              |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail billm@suburbia.net               |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _FPU_ASM_H_
DECL|macro|_FPU_ASM_H_
mdefine_line|#define _FPU_ASM_H_
macro_line|#include &lt;linux/linkage.h&gt;
DECL|macro|EXCEPTION
mdefine_line|#define&t;EXCEPTION&t;SYMBOL_NAME(FPU_exception)
DECL|macro|PARAM1
mdefine_line|#define PARAM1&t;8(%ebp)
DECL|macro|PARAM2
mdefine_line|#define&t;PARAM2&t;12(%ebp)
DECL|macro|PARAM3
mdefine_line|#define&t;PARAM3&t;16(%ebp)
DECL|macro|PARAM4
mdefine_line|#define&t;PARAM4&t;20(%ebp)
DECL|macro|PARAM5
mdefine_line|#define&t;PARAM5&t;24(%ebp)
DECL|macro|PARAM6
mdefine_line|#define&t;PARAM6&t;28(%ebp)
DECL|macro|PARAM7
mdefine_line|#define&t;PARAM7&t;32(%ebp)
DECL|macro|SIGL_OFFSET
mdefine_line|#define SIGL_OFFSET 0
DECL|macro|EXP
mdefine_line|#define&t;EXP(x)&t;8(x)
DECL|macro|SIG
mdefine_line|#define SIG(x)&t;SIGL_OFFSET##(x)
DECL|macro|SIGL
mdefine_line|#define&t;SIGL(x)&t;SIGL_OFFSET##(x)
DECL|macro|SIGH
mdefine_line|#define&t;SIGH(x)&t;4(x)
macro_line|#endif _FPU_ASM_H_
eof
