macro_line|#ifndef _M68K_BITOPS_H
DECL|macro|_M68K_BITOPS_H
mdefine_line|#define _M68K_BITOPS_H
multiline_comment|/*&n; * Copyright 1992, Linus Torvalds.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/*&n; * Require 68020 or better.&n; *&n; * They use the standard big-endian m680x0 bit ordering.&n; */
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit(nr,vaddr) &bslash;&n;  (__builtin_constant_p(nr) ? &bslash;&n;   __constant_test_and_set_bit(nr, vaddr) : &bslash;&n;   __generic_test_and_set_bit(nr, vaddr))
DECL|macro|__test_and_set_bit
mdefine_line|#define __test_and_set_bit(nr,vaddr) test_and_set_bit(nr,vaddr)
DECL|function|__constant_test_and_set_bit
r_static
r_inline
r_int
id|__constant_test_and_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bset %2,%1; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
comma
l_string|&quot;+m&quot;
(paren
(paren
(paren
r_volatile
r_char
op_star
)paren
id|vaddr
)paren
(braket
(paren
id|nr
op_xor
l_int|31
)paren
op_rshift
l_int|3
)braket
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
id|nr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|__generic_test_and_set_bit
r_static
r_inline
r_int
id|__generic_test_and_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfset %2@{%1:#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|31
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|set_bit
mdefine_line|#define set_bit(nr,vaddr) &bslash;&n;  (__builtin_constant_p(nr) ? &bslash;&n;   __constant_set_bit(nr, vaddr) : &bslash;&n;   __generic_set_bit(nr, vaddr))
DECL|macro|__set_bit
mdefine_line|#define __set_bit(nr,vaddr) set_bit(nr,vaddr)
DECL|function|__constant_set_bit
r_static
r_inline
r_void
id|__constant_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;bset %1,%0&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
(paren
(paren
r_volatile
r_char
op_star
)paren
id|vaddr
)paren
(braket
(paren
id|nr
op_xor
l_int|31
)paren
op_rshift
l_int|3
)braket
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
id|nr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
)brace
DECL|function|__generic_set_bit
r_static
r_inline
r_void
id|__generic_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfset %1@{%0:#1}&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|31
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|test_and_clear_bit
mdefine_line|#define test_and_clear_bit(nr,vaddr) &bslash;&n;  (__builtin_constant_p(nr) ? &bslash;&n;   __constant_test_and_clear_bit(nr, vaddr) : &bslash;&n;   __generic_test_and_clear_bit(nr, vaddr))
DECL|macro|__test_and_clear_bit
mdefine_line|#define __test_and_clear_bit(nr,vaddr) test_and_clear_bit(nr,vaddr)
DECL|function|__constant_test_and_clear_bit
r_static
r_inline
r_int
id|__constant_test_and_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bclr %2,%1; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
comma
l_string|&quot;+m&quot;
(paren
(paren
(paren
r_volatile
r_char
op_star
)paren
id|vaddr
)paren
(braket
(paren
id|nr
op_xor
l_int|31
)paren
op_rshift
l_int|3
)braket
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
id|nr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|__generic_test_and_clear_bit
r_static
r_inline
r_int
id|__generic_test_and_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfclr %2@{%1:#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|31
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * clear_bit() doesn&squot;t provide any barrier for the compiler.&n; */
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;barrier()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;barrier()
DECL|macro|clear_bit
mdefine_line|#define clear_bit(nr,vaddr) &bslash;&n;  (__builtin_constant_p(nr) ? &bslash;&n;   __constant_clear_bit(nr, vaddr) : &bslash;&n;   __generic_clear_bit(nr, vaddr))
DECL|macro|__clear_bit
mdefine_line|#define __clear_bit(nr,vaddr) clear_bit(nr,vaddr)
DECL|function|__constant_clear_bit
r_static
r_inline
r_void
id|__constant_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;bclr %1,%0&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
(paren
(paren
r_volatile
r_char
op_star
)paren
id|vaddr
)paren
(braket
(paren
id|nr
op_xor
l_int|31
)paren
op_rshift
l_int|3
)braket
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
id|nr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
)brace
DECL|function|__generic_clear_bit
r_static
r_inline
r_void
id|__generic_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfclr %1@{%0:#1}&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|31
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|test_and_change_bit
mdefine_line|#define test_and_change_bit(nr,vaddr) &bslash;&n;  (__builtin_constant_p(nr) ? &bslash;&n;   __constant_test_and_change_bit(nr, vaddr) : &bslash;&n;   __generic_test_and_change_bit(nr, vaddr))
DECL|macro|__test_and_change_bit
mdefine_line|#define __test_and_change_bit(nr,vaddr) test_and_change_bit(nr,vaddr)
DECL|macro|__change_bit
mdefine_line|#define __change_bit(nr,vaddr) change_bit(nr,vaddr)
DECL|function|__constant_test_and_change_bit
r_static
r_inline
r_int
id|__constant_test_and_change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bchg %2,%1; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
comma
l_string|&quot;+m&quot;
(paren
(paren
(paren
r_volatile
r_char
op_star
)paren
id|vaddr
)paren
(braket
(paren
id|nr
op_xor
l_int|31
)paren
op_rshift
l_int|3
)braket
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
id|nr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|__generic_test_and_change_bit
r_static
r_inline
r_int
id|__generic_test_and_change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfchg %2@{%1:#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|31
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|change_bit
mdefine_line|#define change_bit(nr,vaddr) &bslash;&n;  (__builtin_constant_p(nr) ? &bslash;&n;   __constant_change_bit(nr, vaddr) : &bslash;&n;   __generic_change_bit(nr, vaddr))
DECL|function|__constant_change_bit
r_static
r_inline
r_void
id|__constant_change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;bchg %1,%0&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
(paren
(paren
r_volatile
r_char
op_star
)paren
id|vaddr
)paren
(braket
(paren
id|nr
op_xor
l_int|31
)paren
op_rshift
l_int|3
)braket
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
id|nr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
)brace
DECL|function|__generic_change_bit
r_static
r_inline
r_void
id|__generic_change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfchg %1@{%0:#1}&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|31
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|test_bit
r_static
r_inline
r_int
id|test_bit
c_func
(paren
r_int
id|nr
comma
r_const
r_volatile
r_int
r_int
op_star
id|vaddr
)paren
(brace
r_return
(paren
(paren
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
op_amp
(paren
(paren
(paren
r_const
r_volatile
r_int
r_int
op_star
)paren
id|vaddr
)paren
(braket
id|nr
op_rshift
l_int|5
)braket
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|find_first_zero_bit
r_static
r_inline
r_int
id|find_first_zero_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|vaddr
comma
r_int
id|size
)paren
(brace
r_const
r_int
r_int
op_star
id|p
op_assign
id|vaddr
suffix:semicolon
r_int
id|res
op_assign
l_int|32
suffix:semicolon
r_int
r_int
id|num
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|0
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
l_int|31
)paren
op_rshift
l_int|5
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|num
op_assign
op_complement
op_star
id|p
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|size
)paren
r_goto
id|out
suffix:semicolon
)brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfffo %1{#0,#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|num
op_amp
op_minus
id|num
)paren
)paren
suffix:semicolon
id|res
op_xor_assign
l_int|31
suffix:semicolon
id|out
suffix:colon
r_return
(paren
(paren
r_int
)paren
id|p
op_minus
(paren
r_int
)paren
id|vaddr
op_minus
l_int|4
)paren
op_star
l_int|8
op_plus
id|res
suffix:semicolon
)brace
DECL|function|find_next_zero_bit
r_static
r_inline
r_int
id|find_next_zero_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|vaddr
comma
r_int
id|size
comma
r_int
id|offset
)paren
(brace
r_const
r_int
r_int
op_star
id|p
op_assign
id|vaddr
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
id|bit
op_assign
id|offset
op_amp
l_int|31UL
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|size
)paren
r_return
id|size
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
r_int
r_int
id|num
op_assign
op_complement
op_star
id|p
op_increment
op_amp
(paren
op_complement
l_int|0UL
op_lshift
id|bit
)paren
suffix:semicolon
id|offset
op_sub_assign
id|bit
suffix:semicolon
multiline_comment|/* Look for zero in first longword */
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfffo %1{#0,#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|num
op_amp
op_minus
id|num
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|32
)paren
r_return
id|offset
op_plus
(paren
id|res
op_xor
l_int|31
)paren
suffix:semicolon
id|offset
op_add_assign
l_int|32
suffix:semicolon
)brace
multiline_comment|/* No zero yet, search remaining full bytes for a zero */
id|res
op_assign
id|find_first_zero_bit
c_func
(paren
id|p
comma
id|size
op_minus
(paren
(paren
r_int
)paren
id|p
op_minus
(paren
r_int
)paren
id|vaddr
)paren
op_star
l_int|8
)paren
suffix:semicolon
r_return
id|offset
op_plus
id|res
suffix:semicolon
)brace
DECL|function|find_first_bit
r_static
r_inline
r_int
id|find_first_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|vaddr
comma
r_int
id|size
)paren
(brace
r_const
r_int
r_int
op_star
id|p
op_assign
id|vaddr
suffix:semicolon
r_int
id|res
op_assign
l_int|32
suffix:semicolon
r_int
r_int
id|num
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|0
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
l_int|31
)paren
op_rshift
l_int|5
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|num
op_assign
op_star
id|p
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|size
)paren
r_goto
id|out
suffix:semicolon
)brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfffo %1{#0,#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|num
op_amp
op_minus
id|num
)paren
)paren
suffix:semicolon
id|res
op_xor_assign
l_int|31
suffix:semicolon
id|out
suffix:colon
r_return
(paren
(paren
r_int
)paren
id|p
op_minus
(paren
r_int
)paren
id|vaddr
op_minus
l_int|4
)paren
op_star
l_int|8
op_plus
id|res
suffix:semicolon
)brace
DECL|function|find_next_bit
r_static
r_inline
r_int
id|find_next_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|vaddr
comma
r_int
id|size
comma
r_int
id|offset
)paren
(brace
r_const
r_int
r_int
op_star
id|p
op_assign
id|vaddr
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
id|bit
op_assign
id|offset
op_amp
l_int|31UL
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|size
)paren
r_return
id|size
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
r_int
r_int
id|num
op_assign
op_star
id|p
op_increment
op_amp
(paren
op_complement
l_int|0UL
op_lshift
id|bit
)paren
suffix:semicolon
id|offset
op_sub_assign
id|bit
suffix:semicolon
multiline_comment|/* Look for one in first longword */
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfffo %1{#0,#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|num
op_amp
op_minus
id|num
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|32
)paren
r_return
id|offset
op_plus
(paren
id|res
op_xor
l_int|31
)paren
suffix:semicolon
id|offset
op_add_assign
l_int|32
suffix:semicolon
)brace
multiline_comment|/* No one yet, search remaining full bytes for a one */
id|res
op_assign
id|find_first_bit
c_func
(paren
id|p
comma
id|size
op_minus
(paren
(paren
r_int
)paren
id|p
op_minus
(paren
r_int
)paren
id|vaddr
)paren
op_star
l_int|8
)paren
suffix:semicolon
r_return
id|offset
op_plus
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * ffz = Find First Zero in word. Undefined if no zero exists,&n; * so code should check against ~0UL first..&n; */
DECL|function|ffz
r_static
r_inline
r_int
r_int
id|ffz
c_func
(paren
r_int
r_int
id|word
)paren
(brace
r_int
id|res
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfffo %1{#0,#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
op_complement
id|word
op_amp
op_minus
op_complement
id|word
)paren
)paren
suffix:semicolon
r_return
id|res
op_xor
l_int|31
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * ffs: find first bit set. This is defined the same way as&n; * the libc and compiler builtin ffs routines, therefore&n; * differs in spirit from the above ffz (man ffs).&n; */
DECL|function|ffs
r_static
r_inline
r_int
id|ffs
c_func
(paren
r_int
id|x
)paren
(brace
r_int
id|cnt
suffix:semicolon
id|asm
(paren
l_string|&quot;bfffo %1{#0:#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cnt
)paren
suffix:colon
l_string|&quot;dm&quot;
(paren
id|x
op_amp
op_minus
id|x
)paren
)paren
suffix:semicolon
r_return
l_int|32
op_minus
id|cnt
suffix:semicolon
)brace
DECL|macro|__ffs
mdefine_line|#define __ffs(x) (ffs(x) - 1)
multiline_comment|/*&n; * fls: find last bit set.&n; */
DECL|function|fls
r_static
r_inline
r_int
id|fls
c_func
(paren
r_int
id|x
)paren
(brace
r_int
id|cnt
suffix:semicolon
id|asm
(paren
l_string|&quot;bfffo %1{#0,#0},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cnt
)paren
suffix:colon
l_string|&quot;dm&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
l_int|32
op_minus
id|cnt
suffix:semicolon
)brace
multiline_comment|/*&n; * Every architecture must define this function. It&squot;s the fastest&n; * way of searching a 140-bit bitmap where the first 100 bits are&n; * unlikely to be set. It&squot;s guaranteed that at least one of the 140&n; * bits is cleared.&n; */
DECL|function|sched_find_first_bit
r_static
r_inline
r_int
id|sched_find_first_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|b
(braket
l_int|0
)braket
)paren
)paren
r_return
id|__ffs
c_func
(paren
id|b
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|b
(braket
l_int|1
)braket
)paren
)paren
r_return
id|__ffs
c_func
(paren
id|b
(braket
l_int|1
)braket
)paren
op_plus
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|b
(braket
l_int|2
)braket
)paren
)paren
r_return
id|__ffs
c_func
(paren
id|b
(braket
l_int|2
)braket
)paren
op_plus
l_int|64
suffix:semicolon
r_if
c_cond
(paren
id|b
(braket
l_int|3
)braket
)paren
r_return
id|__ffs
c_func
(paren
id|b
(braket
l_int|3
)braket
)paren
op_plus
l_int|96
suffix:semicolon
r_return
id|__ffs
c_func
(paren
id|b
(braket
l_int|4
)braket
)paren
op_plus
l_int|128
suffix:semicolon
)brace
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
multiline_comment|/* Bitmap functions for the minix filesystem */
DECL|function|minix_find_first_zero_bit
r_static
r_inline
r_int
id|minix_find_first_zero_bit
c_func
(paren
r_const
r_void
op_star
id|vaddr
comma
r_int
id|size
)paren
(brace
r_const
r_int
r_int
op_star
id|p
op_assign
id|vaddr
comma
op_star
id|addr
op_assign
id|vaddr
suffix:semicolon
r_int
id|res
suffix:semicolon
r_int
r_int
id|num
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|0
suffix:semicolon
id|size
op_assign
(paren
id|size
op_rshift
l_int|4
)paren
op_plus
(paren
(paren
id|size
op_amp
l_int|15
)paren
OG
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_increment
op_eq
l_int|0xffff
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|size
op_eq
l_int|0
)paren
r_return
(paren
id|p
op_minus
id|addr
)paren
op_lshift
l_int|4
suffix:semicolon
)brace
id|num
op_assign
op_complement
op_star
op_decrement
id|p
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfffo %1{#16,#16},%0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|num
op_amp
op_minus
id|num
)paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|p
op_minus
id|addr
)paren
op_lshift
l_int|4
)paren
op_plus
(paren
id|res
op_xor
l_int|31
)paren
suffix:semicolon
)brace
DECL|function|minix_test_and_set_bit
r_static
r_inline
r_int
id|minix_test_and_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfset %2{%1:#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|15
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_volatile
r_char
op_star
)paren
id|vaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,addr)&t;((void)minix_test_and_set_bit(nr,addr))
DECL|function|minix_test_and_clear_bit
r_static
r_inline
r_int
id|minix_test_and_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfclr %2{%1:#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|15
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_volatile
r_char
op_star
)paren
id|vaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|minix_test_bit
r_static
r_inline
r_int
id|minix_test_bit
c_func
(paren
r_int
id|nr
comma
r_const
r_volatile
r_void
op_star
id|vaddr
)paren
(brace
r_return
(paren
(paren
l_int|1U
op_lshift
(paren
id|nr
op_amp
l_int|15
)paren
)paren
op_amp
(paren
(paren
(paren
r_const
r_volatile
r_int
r_int
op_star
)paren
id|vaddr
)paren
(braket
id|nr
op_rshift
l_int|4
)braket
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Bitmap functions for the ext2 filesystem. */
DECL|function|ext2_set_bit
r_static
r_inline
r_int
id|ext2_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfset %2{%1,#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|7
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_volatile
r_char
op_star
)paren
id|vaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ext2_clear_bit
r_static
r_inline
r_int
id|ext2_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|vaddr
)paren
(brace
r_char
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;bfclr %2{%1,#1}; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
op_xor
l_int|7
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_volatile
r_char
op_star
)paren
id|vaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|ext2_set_bit_atomic
mdefine_line|#define ext2_set_bit_atomic(lock, nr, addr)&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int ret;&t;&t;&t;&t;&bslash;&n;&t;&t;spin_lock(lock);&t;&t;&t;&bslash;&n;&t;&t;ret = ext2_set_bit((nr), (addr));&t;&bslash;&n;&t;&t;spin_unlock(lock);&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|ext2_clear_bit_atomic
mdefine_line|#define ext2_clear_bit_atomic(lock, nr, addr)&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int ret;&t;&t;&t;&t;&bslash;&n;&t;&t;spin_lock(lock);&t;&t;&t;&bslash;&n;&t;&t;ret = ext2_clear_bit((nr), (addr));&t;&bslash;&n;&t;&t;spin_unlock(lock);&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|function|ext2_test_bit
r_static
r_inline
r_int
id|ext2_test_bit
c_func
(paren
r_int
id|nr
comma
r_const
r_volatile
r_void
op_star
id|vaddr
)paren
(brace
r_return
(paren
(paren
l_int|1U
op_lshift
(paren
id|nr
op_amp
l_int|7
)paren
)paren
op_amp
(paren
(paren
(paren
r_const
r_volatile
r_int
r_char
op_star
)paren
id|vaddr
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|ext2_find_first_zero_bit
r_static
r_inline
r_int
id|ext2_find_first_zero_bit
c_func
(paren
r_const
r_void
op_star
id|vaddr
comma
r_int
id|size
)paren
(brace
r_const
r_int
r_int
op_star
id|p
op_assign
id|vaddr
comma
op_star
id|addr
op_assign
id|vaddr
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|0
suffix:semicolon
id|size
op_assign
(paren
id|size
op_rshift
l_int|5
)paren
op_plus
(paren
(paren
id|size
op_amp
l_int|31
)paren
OG
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_increment
op_eq
op_complement
l_int|0UL
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|size
op_eq
l_int|0
)paren
r_return
(paren
id|p
op_minus
id|addr
)paren
op_lshift
l_int|5
suffix:semicolon
)brace
op_decrement
id|p
suffix:semicolon
r_for
c_loop
(paren
id|res
op_assign
l_int|0
suffix:semicolon
id|res
OL
l_int|32
suffix:semicolon
id|res
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|ext2_test_bit
(paren
id|res
comma
id|p
)paren
)paren
r_break
suffix:semicolon
r_return
(paren
id|p
op_minus
id|addr
)paren
op_star
l_int|32
op_plus
id|res
suffix:semicolon
)brace
DECL|function|ext2_find_next_zero_bit
r_static
r_inline
r_int
id|ext2_find_next_zero_bit
c_func
(paren
r_const
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
r_int
id|offset
)paren
(brace
r_const
r_int
r_int
op_star
id|addr
op_assign
id|vaddr
suffix:semicolon
r_const
r_int
r_int
op_star
id|p
op_assign
id|addr
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
id|bit
op_assign
id|offset
op_amp
l_int|31UL
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|size
)paren
r_return
id|size
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/* Look for zero in first longword */
r_for
c_loop
(paren
id|res
op_assign
id|bit
suffix:semicolon
id|res
OL
l_int|32
suffix:semicolon
id|res
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|ext2_test_bit
(paren
id|res
comma
id|p
)paren
)paren
r_return
(paren
id|p
op_minus
id|addr
)paren
op_star
l_int|32
op_plus
id|res
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/* No zero yet, search remaining full bytes for a zero */
id|res
op_assign
id|ext2_find_first_zero_bit
(paren
id|p
comma
id|size
op_minus
l_int|32
op_star
(paren
id|p
op_minus
id|addr
)paren
)paren
suffix:semicolon
r_return
(paren
id|p
op_minus
id|addr
)paren
op_star
l_int|32
op_plus
id|res
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _M68K_BITOPS_H */
eof
