multiline_comment|/*---------------------------------------------------------------------------+&n; |  status_w.h                                                               |&n; |                                                                           |&n; | Copyright (C) 1992,1993                                                   |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail   billm@vaxc.cc.monash.edu.au    |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
macro_line|#ifndef _STATUS_H_
DECL|macro|_STATUS_H_
mdefine_line|#define _STATUS_H_
macro_line|#include &quot;fpu_emu.h&quot;    /* for definition of PECULIAR_486 */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|Const__
mdefine_line|#define&t;Const__(x)&t;$##x
macro_line|#else
DECL|macro|Const__
mdefine_line|#define&t;Const__(x)&t;x
macro_line|#endif
DECL|macro|SW_Backward
mdefine_line|#define SW_Backward    &t;Const__(0x8000)&t;/* backward compatibility */
DECL|macro|SW_C3
mdefine_line|#define SW_C3&t;&t;Const__(0x4000)&t;/* condition bit 3 */
DECL|macro|SW_Top
mdefine_line|#define SW_Top&t;&t;Const__(0x3800)&t;/* top of stack */
DECL|macro|SW_Top_Shift
mdefine_line|#define SW_Top_Shift &t;Const__(11)&t;/* shift for top of stack bits */
DECL|macro|SW_C2
mdefine_line|#define SW_C2&t;&t;Const__(0x0400)&t;/* condition bit 2 */
DECL|macro|SW_C1
mdefine_line|#define SW_C1&t;&t;Const__(0x0200)&t;/* condition bit 1 */
DECL|macro|SW_C0
mdefine_line|#define SW_C0&t;&t;Const__(0x0100)&t;/* condition bit 0 */
DECL|macro|SW_Summary
mdefine_line|#define SW_Summary     &t;Const__(0x0080)&t;/* exception summary */
DECL|macro|SW_Stack_Fault
mdefine_line|#define SW_Stack_Fault&t;Const__(0x0040)&t;/* stack fault */
DECL|macro|SW_Precision
mdefine_line|#define SW_Precision   &t;Const__(0x0020)&t;/* loss of precision */
DECL|macro|SW_Underflow
mdefine_line|#define SW_Underflow   &t;Const__(0x0010)&t;/* underflow */
DECL|macro|SW_Overflow
mdefine_line|#define SW_Overflow    &t;Const__(0x0008)&t;/* overflow */
DECL|macro|SW_Zero_Div
mdefine_line|#define SW_Zero_Div    &t;Const__(0x0004)&t;/* divide by zero */
DECL|macro|SW_Denorm_Op
mdefine_line|#define SW_Denorm_Op   &t;Const__(0x0002)&t;/* denormalized operand */
DECL|macro|SW_Invalid
mdefine_line|#define SW_Invalid     &t;Const__(0x0001)&t;/* invalid operation */
DECL|macro|SW_Exc_Mask
mdefine_line|#define SW_Exc_Mask     Const__(0x27f)  /* Status word exception bit mask */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|COMP_A_gt_B
mdefine_line|#define COMP_A_gt_B&t;1
DECL|macro|COMP_A_eq_B
mdefine_line|#define COMP_A_eq_B&t;2
DECL|macro|COMP_A_lt_B
mdefine_line|#define COMP_A_lt_B&t;3
DECL|macro|COMP_No_Comp
mdefine_line|#define COMP_No_Comp&t;4
DECL|macro|COMP_Denormal
mdefine_line|#define COMP_Denormal   0x20
DECL|macro|COMP_NaN
mdefine_line|#define COMP_NaN&t;0x40
DECL|macro|COMP_SNaN
mdefine_line|#define COMP_SNaN&t;0x80
DECL|macro|status_word
mdefine_line|#define status_word() &bslash;&n;  ((partial_status &amp; ~SW_Top &amp; 0xffff) | ((top &lt;&lt; SW_Top_Shift) &amp; SW_Top))
DECL|macro|setcc
mdefine_line|#define setcc(cc) ({ &bslash;&n;  partial_status &amp;= ~(SW_C0|SW_C1|SW_C2|SW_C3); &bslash;&n;  partial_status |= (cc) &amp; (SW_C0|SW_C1|SW_C2|SW_C3); })
macro_line|#ifdef PECULIAR_486
multiline_comment|/* Default, this conveys no information, but an 80486 does it. */
multiline_comment|/* Clear the SW_C1 bit, &quot;other bits undefined&quot;. */
DECL|macro|clear_C1
macro_line|#  define clear_C1()  { partial_status &amp;= ~SW_C1; }
macro_line|# else
DECL|macro|clear_C1
macro_line|#  define clear_C1()
macro_line|#endif PECULIAR_486
macro_line|#endif __ASSEMBLY__
macro_line|#endif _STATUS_H_
eof
