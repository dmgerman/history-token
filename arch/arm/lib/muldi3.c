multiline_comment|/* More subroutines needed by GCC output code on some machines.  */
multiline_comment|/* Compile this one with gcc.  */
multiline_comment|/* Copyright (C) 1989, 92-98, 1999 Free Software Foundation, Inc.&n;&n;This file is part of GNU CC.&n;&n;GNU CC is free software; you can redistribute it and/or modify&n;it under the terms of the GNU General Public License as published by&n;the Free Software Foundation; either version 2, or (at your option)&n;any later version.&n;&n;GNU CC is distributed in the hope that it will be useful,&n;but WITHOUT ANY WARRANTY; without even the implied warranty of&n;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;GNU General Public License for more details.&n;&n;You should have received a copy of the GNU General Public License&n;along with GNU CC; see the file COPYING.  If not, write to&n;the Free Software Foundation, 59 Temple Place - Suite 330,&n;Boston, MA 02111-1307, USA.  */
multiline_comment|/* As a special exception, if you link this library with other files,&n;   some of which are compiled with GCC, to produce an executable,&n;   this library does not by itself cause the resulting executable&n;   to be covered by the GNU General Public License.&n;   This exception does not however invalidate any other reasons why&n;   the executable file might be covered by the GNU General Public License.&n; */
multiline_comment|/* support functions required by the kernel. based on code from gcc-2.95.3 */
multiline_comment|/* I Molton     29/07/01 */
macro_line|#include &quot;gcclib.h&quot;
DECL|macro|umul_ppmm
mdefine_line|#define umul_ppmm(xh, xl, a, b) &bslash;&n;{register USItype __t0, __t1, __t2;                                     &bslash;&n;  __asm__ (&quot;%@ Inlined umul_ppmm&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        mov     %2, %5, lsr #16&t;&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        mov     %0, %6, lsr #16&t;&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        bic     %3, %5, %2, lsl #16&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        bic     %4, %6, %0, lsl #16&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        mul     %1, %3, %4&t;&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        mul     %4, %2, %4&t;&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        mul     %3, %0, %3&t;&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        mul     %0, %2, %0&t;&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        adds    %3, %4, %3&t;&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        addcs   %0, %0, #65536&t;&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        adds    %1, %1, %3, lsl #16&t;&t;&t;&t;&t;&bslash;n&bslash;&n;        adc     %0, %0, %3, lsr #16&quot;                                    &bslash;&n;           : &quot;=&amp;r&quot; ((USItype) (xh)),                                    &bslash;&n;             &quot;=r&quot; ((USItype) (xl)),                                     &bslash;&n;             &quot;=&amp;r&quot; (__t0), &quot;=&amp;r&quot; (__t1), &quot;=r&quot; (__t2)                    &bslash;&n;           : &quot;r&quot; ((USItype) (a)),                                       &bslash;&n;             &quot;r&quot; ((USItype) (b)));}
DECL|macro|__umulsidi3
mdefine_line|#define __umulsidi3(u, v) &bslash;&n;  ({DIunion __w;                                                        &bslash;&n;    umul_ppmm (__w.s.high, __w.s.low, u, v);                            &bslash;&n;    __w.ll; })
id|DItype
DECL|function|__muldi3
id|__muldi3
(paren
id|DItype
id|u
comma
id|DItype
id|v
)paren
(brace
id|DIunion
id|w
suffix:semicolon
id|DIunion
id|uu
comma
id|vv
suffix:semicolon
id|uu.ll
op_assign
id|u
comma
id|vv.ll
op_assign
id|v
suffix:semicolon
id|w.ll
op_assign
id|__umulsidi3
(paren
id|uu.s.low
comma
id|vv.s.low
)paren
suffix:semicolon
id|w.s.high
op_add_assign
(paren
(paren
id|USItype
)paren
id|uu.s.low
op_star
(paren
id|USItype
)paren
id|vv.s.high
op_plus
(paren
id|USItype
)paren
id|uu.s.high
op_star
(paren
id|USItype
)paren
id|vv.s.low
)paren
suffix:semicolon
r_return
id|w.ll
suffix:semicolon
)brace
eof
