multiline_comment|/* longlong.h -- based on code from gcc-2.95.3&n;&n;   definitions for mixed size 32/64 bit arithmetic.&n;   Copyright (C) 1991, 92, 94, 95, 96, 1997, 1998 Free Software Foundation, Inc.&n;&n;   This definition file is free software; you can redistribute it&n;   and/or modify it under the terms of the GNU General Public&n;   License as published by the Free Software Foundation; either&n;   version 2, or (at your option) any later version.&n;&n;   This definition file is distributed in the hope that it will be&n;   useful, but WITHOUT ANY WARRANTY; without even the implied&n;   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;   See the GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place - Suite 330,&n;   Boston, MA 02111-1307, USA.  */
multiline_comment|/* Borrowed from GCC 2.95.3, I Molton 29/07/01 */
macro_line|#ifndef SI_TYPE_SIZE
DECL|macro|SI_TYPE_SIZE
mdefine_line|#define SI_TYPE_SIZE 32
macro_line|#endif
DECL|macro|__BITS4
mdefine_line|#define __BITS4 (SI_TYPE_SIZE / 4)
DECL|macro|__ll_B
mdefine_line|#define __ll_B (1L &lt;&lt; (SI_TYPE_SIZE / 2))
DECL|macro|__ll_lowpart
mdefine_line|#define __ll_lowpart(t) ((USItype) (t) % __ll_B)
DECL|macro|__ll_highpart
mdefine_line|#define __ll_highpart(t) ((USItype) (t) / __ll_B)
multiline_comment|/* Define auxiliary asm macros.&n;&n;   1) umul_ppmm(high_prod, low_prod, multipler, multiplicand)&n;   multiplies two USItype integers MULTIPLER and MULTIPLICAND,&n;   and generates a two-part USItype product in HIGH_PROD and&n;   LOW_PROD.&n;&n;   2) __umulsidi3(a,b) multiplies two USItype integers A and B,&n;   and returns a UDItype product.  This is just a variant of umul_ppmm.&n;&n;   3) udiv_qrnnd(quotient, remainder, high_numerator, low_numerator,&n;   denominator) divides a two-word unsigned integer, composed by the&n;   integers HIGH_NUMERATOR and LOW_NUMERATOR, by DENOMINATOR and&n;   places the quotient in QUOTIENT and the remainder in REMAINDER.&n;   HIGH_NUMERATOR must be less than DENOMINATOR for correct operation.&n;   If, in addition, the most significant bit of DENOMINATOR must be 1,&n;   then the pre-processor symbol UDIV_NEEDS_NORMALIZATION is defined to 1.&n;&n;   4) sdiv_qrnnd(quotient, remainder, high_numerator, low_numerator,&n;   denominator).  Like udiv_qrnnd but the numbers are signed.  The&n;   quotient is rounded towards 0.&n;&n;   5) count_leading_zeros(count, x) counts the number of zero-bits from&n;   the msb to the first non-zero bit.  This is the number of steps X&n;   needs to be shifted left to set the msb.  Undefined for X == 0.&n;&n;   6) add_ssaaaa(high_sum, low_sum, high_addend_1, low_addend_1,&n;   high_addend_2, low_addend_2) adds two two-word unsigned integers,&n;   composed by HIGH_ADDEND_1 and LOW_ADDEND_1, and HIGH_ADDEND_2 and&n;   LOW_ADDEND_2 respectively.  The result is placed in HIGH_SUM and&n;   LOW_SUM.  Overflow (i.e. carry out) is not stored anywhere, and is&n;   lost.&n;&n;   7) sub_ddmmss(high_difference, low_difference, high_minuend,&n;   low_minuend, high_subtrahend, low_subtrahend) subtracts two&n;   two-word unsigned integers, composed by HIGH_MINUEND_1 and&n;   LOW_MINUEND_1, and HIGH_SUBTRAHEND_2 and LOW_SUBTRAHEND_2&n;   respectively.  The result is placed in HIGH_DIFFERENCE and&n;   LOW_DIFFERENCE.  Overflow (i.e. carry out) is not stored anywhere,&n;   and is lost.&n;&n;   If any of these macros are left undefined for a particular CPU,&n;   C macros are used.  */
macro_line|#if defined (__arm__)
DECL|macro|add_ssaaaa
mdefine_line|#define add_ssaaaa(sh, sl, ah, al, bh, bl) &bslash;&n;  __asm__ (&quot;adds&t;%1, %4, %5
id|adc
op_mod
l_int|0
comma
op_mod
l_int|2
comma
op_mod
l_int|3
l_string|&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
id|r
l_string|&quot; ((USItype) (sh)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype) (sl))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_mod
id|r
l_string|&quot; ((USItype) (ah)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype) (bh)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_mod
id|r
l_string|&quot; ((USItype) (al)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
"&quot;"
(paren
(paren
id|USItype
)paren
(paren
id|bl
)paren
)paren
)paren
DECL|macro|sub_ddmmss
mdefine_line|#define sub_ddmmss(sh, sl, ah, al, bh, bl) &bslash;&n;  __asm__ (&quot;subs&t;%1, %4, %5
id|sbc
op_mod
l_int|0
comma
op_mod
l_int|2
comma
op_mod
l_int|3
l_string|&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
id|r
l_string|&quot; ((USItype) (sh)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((USItype) (sl))&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
id|r
l_string|&quot; ((USItype) (ah)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
l_string|&quot; ((USItype) (bh)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((USItype) (al)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|rI
"&quot;"
(paren
(paren
id|USItype
)paren
(paren
id|bl
)paren
)paren
)paren
DECL|macro|umul_ppmm
mdefine_line|#define umul_ppmm(xh, xl, a, b) &bslash;&n;{register USItype __t0, __t1, __t2;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ (&quot;%@ Inlined umul_ppmm
id|mov
op_mod
l_int|2
comma
op_mod
l_int|5
comma
id|lsr
macro_line|#16
id|mov
op_mod
l_int|0
comma
op_mod
l_int|6
comma
id|lsr
macro_line|#16
id|bic
op_mod
l_int|3
comma
op_mod
l_int|5
comma
op_mod
l_int|2
comma
id|lsl
macro_line|#16
id|bic
op_mod
l_int|4
comma
op_mod
l_int|6
comma
op_mod
l_int|0
comma
id|lsl
macro_line|#16
id|mul
op_mod
l_int|1
comma
op_mod
l_int|3
comma
op_mod
l_int|4
id|mul
op_mod
l_int|4
comma
op_mod
l_int|2
comma
op_mod
l_int|4
id|mul
op_mod
l_int|3
comma
op_mod
l_int|0
comma
op_mod
l_int|3
id|mul
op_mod
l_int|0
comma
op_mod
l_int|2
comma
op_mod
l_int|0
id|adds
op_mod
l_int|3
comma
op_mod
l_int|4
comma
op_mod
l_int|3
id|addcs
op_mod
l_int|0
comma
op_mod
l_int|0
comma
macro_line|#65536
id|adds
op_mod
l_int|1
comma
op_mod
l_int|1
comma
op_mod
l_int|3
comma
id|lsl
macro_line|#16
id|adc
op_mod
l_int|0
comma
op_mod
l_int|0
comma
op_mod
l_int|3
comma
id|lsr
macro_line|#16&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;=&amp;r&quot; ((USItype) (xh)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;=r&quot; ((USItype) (xl)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;=&amp;r&quot; (__t0), &quot;=&amp;r&quot; (__t1), &quot;=r&quot; (__t2)&t;&t;&t;&bslash;&n;&t;   : &quot;r&quot; ((USItype) (a)),&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;r&quot; ((USItype) (b)));}
DECL|macro|UMUL_TIME
mdefine_line|#define UMUL_TIME 20
DECL|macro|UDIV_TIME
mdefine_line|#define UDIV_TIME 100
macro_line|#endif /* __arm__ */
DECL|macro|__umulsidi3
mdefine_line|#define __umulsidi3(u, v) &bslash;&n;  ({DIunion __w;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    umul_ppmm (__w.s.high, __w.s.low, u, v);&t;&t;&t;&t;&bslash;&n;    __w.ll; })
DECL|macro|__udiv_qrnnd_c
mdefine_line|#define __udiv_qrnnd_c(q, r, n1, n0, d) &bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    USItype __d1, __d0, __q1, __q0;&t;&t;&t;&t;&t;&bslash;&n;    USItype __r1, __r0, __m;&t;&t;&t;&t;&t;&t;&bslash;&n;    __d1 = __ll_highpart (d);&t;&t;&t;&t;&t;&t;&bslash;&n;    __d0 = __ll_lowpart (d);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __r1 = (n1) % __d1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __q1 = (n1) / __d1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __m = (USItype) __q1 * __d0;&t;&t;&t;&t;&t;&bslash;&n;    __r1 = __r1 * __ll_B | __ll_highpart (n0);&t;&t;&t;&t;&bslash;&n;    if (__r1 &lt; __m)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__q1--, __r1 += (d);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__r1 &gt;= (d)) /* i.e. we didn&squot;t get carry when adding to __r1 */&bslash;&n;&t;  if (__r1 &lt; __m)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    __q1--, __r1 += (d);&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __r1 -= __m;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __r0 = __r1 % __d1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __q0 = __r1 / __d1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __m = (USItype) __q0 * __d0;&t;&t;&t;&t;&t;&bslash;&n;    __r0 = __r0 * __ll_B | __ll_lowpart (n0);&t;&t;&t;&t;&bslash;&n;    if (__r0 &lt; __m)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__q0--, __r0 += (d);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__r0 &gt;= (d))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  if (__r0 &lt; __m)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    __q0--, __r0 += (d);&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __r0 -= __m;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (q) = (USItype) __q1 * __ll_B | __q0;&t;&t;&t;&t;&bslash;&n;    (r) = __r0;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|UDIV_NEEDS_NORMALIZATION
mdefine_line|#define UDIV_NEEDS_NORMALIZATION 1
DECL|macro|udiv_qrnnd
mdefine_line|#define udiv_qrnnd __udiv_qrnnd_c
r_extern
r_const
id|UQItype
id|__clz_tab
(braket
)braket
suffix:semicolon
DECL|macro|count_leading_zeros
mdefine_line|#define count_leading_zeros(count, x) &bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    USItype __xr = (x);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    USItype __a;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    if (SI_TYPE_SIZE &lt;= 32)&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__a = __xr &lt; ((USItype)1&lt;&lt;2*__BITS4)&t;&t;&t;&t;&bslash;&n;&t;  ? (__xr &lt; ((USItype)1&lt;&lt;__BITS4) ? 0 : __BITS4)&t;&t;&bslash;&n;&t;  : (__xr &lt; ((USItype)1&lt;&lt;3*__BITS4) ?  2*__BITS4 : 3*__BITS4);&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (__a = SI_TYPE_SIZE - 8; __a &gt; 0; __a -= 8)&t;&t;&t;&bslash;&n;&t;  if (((__xr &gt;&gt; __a) &amp; 0xff) != 0)&t;&t;&t;&t;&bslash;&n;&t;    break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    (count) = SI_TYPE_SIZE - (__clz_tab[__xr &gt;&gt; __a] + __a);&t;&t;&bslash;&n;  } while (0)
eof
