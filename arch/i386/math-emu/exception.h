multiline_comment|/*---------------------------------------------------------------------------+&n; |  exception.h                                                              |&n; |                                                                           |&n; | Copyright (C) 1992    W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail   billm@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _EXCEPTION_H_
DECL|macro|_EXCEPTION_H_
mdefine_line|#define _EXCEPTION_H_
macro_line|#ifdef __ASSEMBLY__
DECL|macro|Const_
mdefine_line|#define&t;Const_(x)&t;$##x
macro_line|#else
DECL|macro|Const_
mdefine_line|#define&t;Const_(x)&t;x
macro_line|#endif
macro_line|#ifndef SW_C1
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#endif SW_C1
DECL|macro|FPU_BUSY
mdefine_line|#define FPU_BUSY        Const_(0x8000)   /* FPU busy bit (8087 compatibility) */
DECL|macro|EX_ErrorSummary
mdefine_line|#define EX_ErrorSummary Const_(0x0080)   /* Error summary status */
multiline_comment|/* Special exceptions: */
DECL|macro|EX_INTERNAL
mdefine_line|#define&t;EX_INTERNAL&t;Const_(0x8000)&t;/* Internal error in wm-FPU-emu */
DECL|macro|EX_StackOver
mdefine_line|#define EX_StackOver&t;Const_(0x0041|SW_C1)&t;/* stack overflow */
DECL|macro|EX_StackUnder
mdefine_line|#define EX_StackUnder&t;Const_(0x0041)&t;/* stack underflow */
multiline_comment|/* Exception flags: */
DECL|macro|EX_Precision
mdefine_line|#define EX_Precision&t;Const_(0x0020)&t;/* loss of precision */
DECL|macro|EX_Underflow
mdefine_line|#define EX_Underflow&t;Const_(0x0010)&t;/* underflow */
DECL|macro|EX_Overflow
mdefine_line|#define EX_Overflow&t;Const_(0x0008)&t;/* overflow */
DECL|macro|EX_ZeroDiv
mdefine_line|#define EX_ZeroDiv&t;Const_(0x0004)&t;/* divide by zero */
DECL|macro|EX_Denormal
mdefine_line|#define EX_Denormal&t;Const_(0x0002)&t;/* denormalized operand */
DECL|macro|EX_Invalid
mdefine_line|#define EX_Invalid&t;Const_(0x0001)&t;/* invalid operation */
DECL|macro|PRECISION_LOST_UP
mdefine_line|#define PRECISION_LOST_UP    Const_((EX_Precision | SW_C1))
DECL|macro|PRECISION_LOST_DOWN
mdefine_line|#define PRECISION_LOST_DOWN  Const_(EX_Precision)
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef DEBUG
DECL|macro|EXCEPTION
mdefine_line|#define&t;EXCEPTION(x)&t;{ printk(&quot;exception in %s at line %d&bslash;n&quot;, &bslash;&n;&t;__FILE__, __LINE__); FPU_exception(x); }
macro_line|#else
DECL|macro|EXCEPTION
mdefine_line|#define&t;EXCEPTION(x)&t;FPU_exception(x)
macro_line|#endif
macro_line|#endif __ASSEMBLY__
macro_line|#endif _EXCEPTION_H_
eof
