multiline_comment|/*---------------------------------------------------------------------------+&n; |  control_w.h                                                              |&n; |                                                                           |&n; | Copyright (C) 1992,1993                                                   |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail   billm@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _CONTROLW_H_
DECL|macro|_CONTROLW_H_
mdefine_line|#define _CONTROLW_H_
macro_line|#ifdef __ASSEMBLY__
DECL|macro|_Const_
mdefine_line|#define&t;_Const_(x)&t;$##x
macro_line|#else
DECL|macro|_Const_
mdefine_line|#define&t;_Const_(x)&t;x
macro_line|#endif
DECL|macro|CW_RC
mdefine_line|#define CW_RC&t;&t;_Const_(0x0C00)&t;/* rounding control */
DECL|macro|CW_PC
mdefine_line|#define CW_PC&t;&t;_Const_(0x0300)&t;/* precision control */
DECL|macro|CW_Precision
mdefine_line|#define CW_Precision&t;Const_(0x0020)&t;/* loss of precision mask */
DECL|macro|CW_Underflow
mdefine_line|#define CW_Underflow&t;Const_(0x0010)&t;/* underflow mask */
DECL|macro|CW_Overflow
mdefine_line|#define CW_Overflow&t;Const_(0x0008)&t;/* overflow mask */
DECL|macro|CW_ZeroDiv
mdefine_line|#define CW_ZeroDiv&t;Const_(0x0004)&t;/* divide by zero mask */
DECL|macro|CW_Denormal
mdefine_line|#define CW_Denormal&t;Const_(0x0002)&t;/* denormalized operand mask */
DECL|macro|CW_Invalid
mdefine_line|#define CW_Invalid&t;Const_(0x0001)&t;/* invalid operation mask */
DECL|macro|CW_Exceptions
mdefine_line|#define CW_Exceptions  &t;_Const_(0x003f)&t;/* all masks */
DECL|macro|RC_RND
mdefine_line|#define RC_RND&t;&t;_Const_(0x0000)
DECL|macro|RC_DOWN
mdefine_line|#define RC_DOWN&t;&t;_Const_(0x0400)
DECL|macro|RC_UP
mdefine_line|#define RC_UP&t;&t;_Const_(0x0800)
DECL|macro|RC_CHOP
mdefine_line|#define RC_CHOP&t;&t;_Const_(0x0C00)
multiline_comment|/* p 15-5: Precision control bits affect only the following:&n;   ADD, SUB(R), MUL, DIV(R), and SQRT */
DECL|macro|PR_24_BITS
mdefine_line|#define PR_24_BITS        _Const_(0x000)
DECL|macro|PR_53_BITS
mdefine_line|#define PR_53_BITS        _Const_(0x200)
DECL|macro|PR_64_BITS
mdefine_line|#define PR_64_BITS        _Const_(0x300)
DECL|macro|PR_RESERVED_BITS
mdefine_line|#define PR_RESERVED_BITS  _Const_(0x100)
multiline_comment|/* FULL_PRECISION simulates all exceptions masked */
DECL|macro|FULL_PRECISION
mdefine_line|#define FULL_PRECISION  (PR_64_BITS | RC_RND | 0x3f)
macro_line|#endif _CONTROLW_H_
eof
