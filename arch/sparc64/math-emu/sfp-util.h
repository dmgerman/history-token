multiline_comment|/* $Id: sfp-util.h,v 1.4 1999/09/20 12:14:19 jj Exp $&n; * arch/sparc64/math-emu/sfp-util.h&n; *&n; * Copyright (C) 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1999 David S. Miller (davem@redhat.com)&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|add_ssaaaa
mdefine_line|#define add_ssaaaa(sh, sl, ah, al, bh, bl) &t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ (&quot;addcc %4,%5,%1
id|add
op_mod
l_int|2
comma
op_mod
l_int|3
comma
op_mod
l_int|0
id|bcs
comma
id|a
comma
id|pn
op_mod
op_mod
id|xcc
comma
l_float|1f
id|add
op_mod
l_int|0
comma
l_int|1
comma
op_mod
l_int|0
l_int|1
suffix:colon
l_string|&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
id|r
l_string|&quot; ((UDItype)(sh)),&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((UDItype)(sl))&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;   : &quot;
id|r
l_string|&quot; ((UDItype)(ah)),&t;&t;&t;&t;     &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(bh)),&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(al)),&t;&t;&t;&t;     &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(bl))&t;&t;&t;&t;       &t;&t;&t;&bslash;&n;&t;   : &quot;
id|cc
"&quot;"
)paren
DECL|macro|sub_ddmmss
mdefine_line|#define sub_ddmmss(sh, sl, ah, al, bh, bl) &t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ (&quot;subcc %4,%5,%1
id|sub
op_mod
l_int|2
comma
op_mod
l_int|3
comma
op_mod
l_int|0
id|bcs
comma
id|a
comma
id|pn
op_mod
op_mod
id|xcc
comma
l_float|1f
id|sub
op_mod
l_int|0
comma
l_int|1
comma
op_mod
l_int|0
l_int|1
suffix:colon
l_string|&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
id|r
l_string|&quot; ((UDItype)(sh)),&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((UDItype)(sl))&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;   : &quot;
id|r
l_string|&quot; ((UDItype)(ah)),&t;&t;&t;&t;     &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(bh)),&t;&t;&t;&t;      &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(al)),&t;&t;&t;&t;     &t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(bl))&t;&t;&t;&t;       &t;&t;&t;&bslash;&n;&t;   : &quot;
id|cc
"&quot;"
)paren
DECL|macro|umul_ppmm
mdefine_line|#define umul_ppmm(wh, wl, u, v)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  UDItype tmp1, tmp2, tmp3, tmp4;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  __asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;   &quot;srl %7,0,%3
id|mulx
op_mod
l_int|3
comma
op_mod
l_int|6
comma
op_mod
l_int|1
id|srlx
op_mod
l_int|6
comma
l_int|32
comma
op_mod
l_int|2
id|mulx
op_mod
l_int|2
comma
op_mod
l_int|3
comma
op_mod
l_int|4
id|sllx
op_mod
l_int|4
comma
l_int|32
comma
op_mod
l_int|5
id|srl
op_mod
l_int|6
comma
l_int|0
comma
op_mod
l_int|3
id|sub
op_mod
l_int|1
comma
op_mod
l_int|5
comma
op_mod
l_int|5
id|srlx
op_mod
l_int|5
comma
l_int|32
comma
op_mod
l_int|5
id|addcc
op_mod
l_int|4
comma
op_mod
l_int|5
comma
op_mod
l_int|4
id|srlx
op_mod
l_int|7
comma
l_int|32
comma
op_mod
l_int|5
id|mulx
op_mod
l_int|3
comma
op_mod
l_int|5
comma
op_mod
l_int|3
id|mulx
op_mod
l_int|2
comma
op_mod
l_int|5
comma
op_mod
l_int|5
id|sethi
op_mod
op_mod
id|hi
c_func
(paren
l_int|0x80000000
)paren
comma
op_mod
l_int|2
id|addcc
op_mod
l_int|4
comma
op_mod
l_int|3
comma
op_mod
l_int|4
id|srlx
op_mod
l_int|4
comma
l_int|32
comma
op_mod
l_int|4
id|add
op_mod
l_int|2
comma
op_mod
l_int|2
comma
op_mod
l_int|2
id|movcc
op_mod
op_mod
id|xcc
comma
op_mod
op_mod
id|g0
comma
op_mod
l_int|2
id|addcc
op_mod
l_int|5
comma
op_mod
l_int|4
comma
op_mod
l_int|5
id|sllx
op_mod
l_int|3
comma
l_int|32
comma
op_mod
l_int|3
id|add
op_mod
l_int|1
comma
op_mod
l_int|3
comma
op_mod
l_int|1
id|add
op_mod
l_int|5
comma
op_mod
l_int|2
comma
op_mod
l_int|0
l_string|&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
op_assign
id|r
l_string|&quot; ((UDItype)(wh)),&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; ((UDItype)(wl)),&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
op_assign
op_amp
id|r
l_string|&quot; (tmp1), &quot;
op_assign
op_amp
id|r
l_string|&quot; (tmp2), &quot;
op_assign
op_amp
id|r
l_string|&quot; (tmp3), &quot;
op_assign
op_amp
id|r
l_string|&quot; (tmp4)&t;&t;&t;&bslash;&n;&t;   : &quot;
id|r
l_string|&quot; ((UDItype)(u)),&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;     &quot;
id|r
l_string|&quot; ((UDItype)(v))&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;   : &quot;
id|cc
"&quot;"
)paren
suffix:semicolon
"&bslash;"
)brace
r_while
c_loop
(paren
l_int|0
)paren
DECL|macro|udiv_qrnnd
mdefine_line|#define udiv_qrnnd(q, r, n1, n0, d) &t;&t;&t;&t;&t;&t;&t;&bslash;&n;  do {                                                                  &t;&t;&bslash;&n;    UWtype __d1, __d0, __q1, __q0, __r1, __r0, __m;                     &t;&t;&bslash;&n;    __d1 = (d &gt;&gt; 32);                                           &t;&t;&t;&bslash;&n;    __d0 = (USItype)d;                                            &t;&t;&t;&bslash;&n;                                                                        &t;&t;&bslash;&n;    __r1 = (n1) % __d1;                                                 &t;&t;&bslash;&n;    __q1 = (n1) / __d1;                                                 &t;&t;&bslash;&n;    __m = (UWtype) __q1 * __d0;                                         &t;&t;&bslash;&n;    __r1 = (__r1 &lt;&lt; 32) | (n0 &gt;&gt; 32);                          &t;&t;&t;&t;&bslash;&n;    if (__r1 &lt; __m)                                                     &t;&t;&bslash;&n;      {                                                                 &t;&t;&bslash;&n;        __q1--, __r1 += (d);                                            &t;&t;&bslash;&n;        if (__r1 &gt;= (d)) /* i.e. we didn&squot;t get carry when adding to __r1 */&t;&t;&bslash;&n;          if (__r1 &lt; __m)                                               &t;&t;&bslash;&n;            __q1--, __r1 += (d);                                        &t;&t;&bslash;&n;      }                                                                 &t;&t;&bslash;&n;    __r1 -= __m;                                                        &t;&t;&bslash;&n;                                                                        &t;&t;&bslash;&n;    __r0 = __r1 % __d1;                                                 &t;&t;&bslash;&n;    __q0 = __r1 / __d1;                                                 &t;&t;&bslash;&n;    __m = (UWtype) __q0 * __d0;                                         &t;&t;&bslash;&n;    __r0 = (__r0 &lt;&lt; 32) | ((USItype)n0);                           &t;&t;&t;&bslash;&n;    if (__r0 &lt; __m)                                                     &t;&t;&bslash;&n;      {                                                                 &t;&t;&bslash;&n;        __q0--, __r0 += (d);                                            &t;&t;&bslash;&n;        if (__r0 &gt;= (d))                                                &t;&t;&bslash;&n;          if (__r0 &lt; __m)                                               &t;&t;&bslash;&n;            __q0--, __r0 += (d);                                        &t;&t;&bslash;&n;      }                                                                 &t;&t;&bslash;&n;    __r0 -= __m;                                                        &t;&t;&bslash;&n;                                                                        &t;&t;&bslash;&n;    (q) = (UWtype) (__q1 &lt;&lt; 32)  | __q0;                                &t;&t;&bslash;&n;    (r) = __r0;                                                         &t;&t;&bslash;&n;  } while (0)
DECL|macro|UDIV_NEEDS_NORMALIZATION
mdefine_line|#define UDIV_NEEDS_NORMALIZATION 1  
DECL|macro|abort
mdefine_line|#define abort()&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return 0
macro_line|#ifdef __BIG_ENDIAN
DECL|macro|__BYTE_ORDER
mdefine_line|#define __BYTE_ORDER __BIG_ENDIAN
macro_line|#else
DECL|macro|__BYTE_ORDER
mdefine_line|#define __BYTE_ORDER __LITTLE_ENDIAN
macro_line|#endif
eof
