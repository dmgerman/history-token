macro_line|#ifndef _M68KNOMMU_BITOPS_H
DECL|macro|_M68KNOMMU_BITOPS_H
mdefine_line|#define _M68KNOMMU_BITOPS_H
multiline_comment|/*&n; * Copyright 1992, Linus Torvalds.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;&t;/* swab32 */
macro_line|#include &lt;asm/system.h&gt;&t;&t;/* save_flags */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; *&t;Generic ffs().&n; */
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
id|r
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xffff
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|16
suffix:semicolon
id|r
op_add_assign
l_int|16
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xff
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|8
suffix:semicolon
id|r
op_add_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xf
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|4
suffix:semicolon
id|r
op_add_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|3
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|2
suffix:semicolon
id|r
op_add_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|1
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|1
suffix:semicolon
id|r
op_add_assign
l_int|1
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Generic __ffs().&n; */
DECL|function|__ffs
r_static
r_inline
r_int
id|__ffs
c_func
(paren
r_int
id|x
)paren
(brace
r_int
id|r
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xffff
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|16
suffix:semicolon
id|r
op_add_assign
l_int|16
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xff
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|8
suffix:semicolon
id|r
op_add_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|0xf
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|4
suffix:semicolon
id|r
op_add_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|3
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|2
suffix:semicolon
id|r
op_add_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|x
op_amp
l_int|1
)paren
)paren
(brace
id|x
op_rshift_assign
l_int|1
suffix:semicolon
id|r
op_add_assign
l_int|1
suffix:semicolon
)brace
r_return
id|r
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
multiline_comment|/*&n; * ffz = Find First Zero in word. Undefined if no zero exists,&n; * so code should check against ~0UL first..&n; */
DECL|function|ffz
r_static
id|__inline__
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
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|word
op_amp
l_int|1
)paren
(brace
id|result
op_increment
suffix:semicolon
id|word
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|set_bit
r_static
id|__inline__
r_void
id|set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|addr
)paren
(brace
macro_line|#ifdef CONFIG_COLDFIRE
id|__asm__
id|__volatile__
(paren
l_string|&quot;lea %0,%%a0; bset %1,(%%a0)&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
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
l_string|&quot;d&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;%a0&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#else
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
id|addr
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
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|__set_bit
mdefine_line|#define __set_bit(nr, addr) set_bit(nr, addr)
multiline_comment|/*&n; * clear_bit() doesn&squot;t provide any barrier for the compiler.&n; */
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;barrier()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;barrier()
DECL|function|clear_bit
r_static
id|__inline__
r_void
id|clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|addr
)paren
(brace
macro_line|#ifdef CONFIG_COLDFIRE
id|__asm__
id|__volatile__
(paren
l_string|&quot;lea %0,%%a0; bclr %1,(%%a0)&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
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
l_string|&quot;d&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;%a0&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#else
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
id|addr
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
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|__clear_bit
mdefine_line|#define __clear_bit(nr, addr) clear_bit(nr, addr)
DECL|function|change_bit
r_static
id|__inline__
r_void
id|change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|addr
)paren
(brace
macro_line|#ifdef CONFIG_COLDFIRE
id|__asm__
id|__volatile__
(paren
l_string|&quot;lea %0,%%a0; bchg %1,(%%a0)&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
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
l_string|&quot;d&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;%a0&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#else
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
id|addr
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
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|__change_bit
mdefine_line|#define __change_bit(nr, addr) change_bit(nr, addr)
DECL|function|test_and_set_bit
r_static
id|__inline__
r_int
id|test_and_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|addr
)paren
(brace
r_char
id|retval
suffix:semicolon
macro_line|#ifdef CONFIG_COLDFIRE
id|__asm__
id|__volatile__
(paren
l_string|&quot;lea %1,%%a0; bset %2,(%%a0); sne %0&quot;
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
id|addr
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
l_string|&quot;d&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;%a0&quot;
)paren
suffix:semicolon
macro_line|#else
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
id|addr
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
)paren
multiline_comment|/* No clobber */
)paren
suffix:semicolon
macro_line|#endif
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|__test_and_set_bit
mdefine_line|#define __test_and_set_bit(nr, addr) test_and_set_bit(nr, addr)
DECL|function|test_and_clear_bit
r_static
id|__inline__
r_int
id|test_and_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|addr
)paren
(brace
r_char
id|retval
suffix:semicolon
macro_line|#ifdef CONFIG_COLDFIRE
id|__asm__
id|__volatile__
(paren
l_string|&quot;lea %1,%%a0; bclr %2,(%%a0); sne %0&quot;
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
id|addr
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
l_string|&quot;d&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;%a0&quot;
)paren
suffix:semicolon
macro_line|#else
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
id|addr
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
)paren
multiline_comment|/* No clobber */
)paren
suffix:semicolon
macro_line|#endif
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|__test_and_clear_bit
mdefine_line|#define __test_and_clear_bit(nr, addr) test_and_clear_bit(nr, addr)
DECL|function|test_and_change_bit
r_static
id|__inline__
r_int
id|test_and_change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|addr
)paren
(brace
r_char
id|retval
suffix:semicolon
macro_line|#ifdef CONFIG_COLDFIRE
id|__asm__
id|__volatile__
(paren
l_string|&quot;lea %1,%%a0&bslash;n&bslash;tbchg %2,(%%a0)&bslash;n&bslash;tsne %0&quot;
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
id|addr
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
l_string|&quot;d&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;%a0&quot;
)paren
suffix:semicolon
macro_line|#else
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
id|addr
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
)paren
multiline_comment|/* No clobber */
)paren
suffix:semicolon
macro_line|#endif
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|__test_and_change_bit
mdefine_line|#define __test_and_change_bit(nr, addr) test_and_change_bit(nr, addr)
multiline_comment|/*&n; * This routine doesn&squot;t need to be atomic.&n; */
DECL|function|__constant_test_bit
r_static
id|__inline__
r_int
id|__constant_test_bit
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
id|addr
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
id|addr
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
DECL|function|__test_bit
r_static
id|__inline__
r_int
id|__test_bit
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
id|addr
)paren
(brace
r_int
op_star
id|a
op_assign
(paren
r_int
op_star
)paren
id|addr
suffix:semicolon
r_int
id|mask
suffix:semicolon
id|a
op_add_assign
id|nr
op_rshift
l_int|5
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_return
(paren
(paren
id|mask
op_amp
op_star
id|a
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
DECL|macro|test_bit
mdefine_line|#define test_bit(nr,addr) &bslash;&n;(__builtin_constant_p(nr) ? &bslash;&n; __constant_test_bit((nr),(addr)) : &bslash;&n; __test_bit((nr),(addr)))
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;        find_next_zero_bit((addr), (size), 0)
DECL|macro|find_first_bit
mdefine_line|#define find_first_bit(addr, size) &bslash;&n;        find_next_bit((addr), (size), 0)
DECL|function|find_next_zero_bit
r_static
id|__inline__
r_int
id|find_next_zero_bit
(paren
r_void
op_star
id|addr
comma
r_int
id|size
comma
r_int
id|offset
)paren
(brace
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
r_int
id|result
op_assign
id|offset
op_amp
op_complement
l_int|31UL
suffix:semicolon
r_int
r_int
id|tmp
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
id|size
op_sub_assign
id|result
suffix:semicolon
id|offset
op_and_assign
l_int|31UL
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|tmp
op_assign
op_star
(paren
id|p
op_increment
)paren
suffix:semicolon
id|tmp
op_or_assign
op_complement
l_int|0UL
op_rshift
(paren
l_int|32
op_minus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|32
)paren
r_goto
id|found_first
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|tmp
)paren
r_goto
id|found_middle
suffix:semicolon
id|size
op_sub_assign
l_int|32
suffix:semicolon
id|result
op_add_assign
l_int|32
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_amp
op_complement
l_int|31UL
)paren
(brace
r_if
c_cond
(paren
op_complement
(paren
id|tmp
op_assign
op_star
(paren
id|p
op_increment
)paren
)paren
)paren
r_goto
id|found_middle
suffix:semicolon
id|result
op_add_assign
l_int|32
suffix:semicolon
id|size
op_sub_assign
l_int|32
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
id|result
suffix:semicolon
id|tmp
op_assign
op_star
id|p
suffix:semicolon
id|found_first
suffix:colon
id|tmp
op_or_assign
op_complement
l_int|0UL
op_rshift
id|size
suffix:semicolon
id|found_middle
suffix:colon
r_return
id|result
op_plus
id|ffz
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Find next one bit in a bitmap reasonably efficiently.&n; */
DECL|function|find_next_bit
r_static
id|__inline__
r_int
r_int
id|find_next_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|offset
)paren
(brace
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
r_int
id|result
op_assign
id|offset
op_amp
op_complement
l_int|31UL
suffix:semicolon
r_int
r_int
id|tmp
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
id|size
op_sub_assign
id|result
suffix:semicolon
id|offset
op_and_assign
l_int|31UL
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|tmp
op_assign
op_star
id|p
op_increment
suffix:semicolon
id|tmp
op_and_assign
op_complement
l_int|0UL
op_lshift
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|32
)paren
r_goto
id|found_first
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
r_goto
id|found_middle
suffix:semicolon
id|size
op_sub_assign
l_int|32
suffix:semicolon
id|result
op_add_assign
l_int|32
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_ge
l_int|32
)paren
(brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
op_star
id|p
op_increment
)paren
op_ne
l_int|0
)paren
r_goto
id|found_middle
suffix:semicolon
id|result
op_add_assign
l_int|32
suffix:semicolon
id|size
op_sub_assign
l_int|32
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
id|result
suffix:semicolon
id|tmp
op_assign
op_star
id|p
suffix:semicolon
id|found_first
suffix:colon
id|tmp
op_and_assign
op_complement
l_int|0UL
op_rshift
(paren
l_int|32
op_minus
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|0UL
)paren
multiline_comment|/* Are any bits set? */
r_return
id|result
op_plus
id|size
suffix:semicolon
multiline_comment|/* Nope. */
id|found_middle
suffix:colon
r_return
id|result
op_plus
id|__ffs
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
DECL|function|ext2_set_bit
r_static
id|__inline__
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
id|addr
)paren
(brace
r_char
id|retval
suffix:semicolon
macro_line|#ifdef CONFIG_COLDFIRE
id|__asm__
id|__volatile__
(paren
l_string|&quot;lea %1,%%a0; bset %2,(%%a0); sne %0&quot;
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
id|addr
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;%a0&quot;
)paren
suffix:semicolon
macro_line|#else
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
id|addr
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
id|nr
)paren
multiline_comment|/* No clobber */
)paren
suffix:semicolon
macro_line|#endif
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ext2_clear_bit
r_static
id|__inline__
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
id|addr
)paren
(brace
r_char
id|retval
suffix:semicolon
macro_line|#ifdef CONFIG_COLDFIRE
id|__asm__
id|__volatile__
(paren
l_string|&quot;lea %1,%%a0; bclr %2,(%%a0); sne %0&quot;
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
id|addr
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;%a0&quot;
)paren
suffix:semicolon
macro_line|#else
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
id|addr
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
)paren
suffix:colon
l_string|&quot;di&quot;
(paren
id|nr
)paren
multiline_comment|/* No clobber */
)paren
suffix:semicolon
macro_line|#endif
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
id|__inline__
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
id|addr
)paren
(brace
r_char
id|retval
suffix:semicolon
macro_line|#ifdef CONFIG_COLDFIRE
id|__asm__
id|__volatile__
(paren
l_string|&quot;lea %1,%%a0; btst %2,(%%a0); sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
(paren
(paren
r_const
r_volatile
r_char
op_star
)paren
id|addr
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
)paren
comma
l_string|&quot;d&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;%a0&quot;
)paren
suffix:semicolon
macro_line|#else
id|__asm__
id|__volatile__
(paren
l_string|&quot;btst %2,%1; sne %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
(paren
(paren
r_const
r_volatile
r_char
op_star
)paren
id|addr
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
)paren
comma
l_string|&quot;di&quot;
(paren
id|nr
)paren
multiline_comment|/* No clobber */
)paren
suffix:semicolon
macro_line|#endif
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit(addr, size) &bslash;&n;        ext2_find_next_zero_bit((addr), (size), 0)
DECL|function|ext2_find_next_zero_bit
r_static
id|__inline__
r_int
r_int
id|ext2_find_next_zero_bit
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|offset
)paren
(brace
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
r_int
id|result
op_assign
id|offset
op_amp
op_complement
l_int|31UL
suffix:semicolon
r_int
r_int
id|tmp
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
id|size
op_sub_assign
id|result
suffix:semicolon
id|offset
op_and_assign
l_int|31UL
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
multiline_comment|/* We hold the little endian value in tmp, but then the&n;&t;&t; * shift is illegal. So we could keep a big endian value&n;&t;&t; * in tmp, like this:&n;&t;&t; *&n;&t;&t; * tmp = __swab32(*(p++));&n;&t;&t; * tmp |= ~0UL &gt;&gt; (32-offset);&n;&t;&t; *&n;&t;&t; * but this would decrease preformance, so we change the&n;&t;&t; * shift:&n;&t;&t; */
id|tmp
op_assign
op_star
(paren
id|p
op_increment
)paren
suffix:semicolon
id|tmp
op_or_assign
id|__swab32
c_func
(paren
op_complement
l_int|0UL
op_rshift
(paren
l_int|32
op_minus
id|offset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|32
)paren
(brace
r_goto
id|found_first
suffix:semicolon
)brace
r_if
c_cond
(paren
op_complement
id|tmp
)paren
(brace
r_goto
id|found_middle
suffix:semicolon
)brace
id|size
op_sub_assign
l_int|32
suffix:semicolon
id|result
op_add_assign
l_int|32
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_amp
op_complement
l_int|31UL
)paren
(brace
r_if
c_cond
(paren
op_complement
(paren
id|tmp
op_assign
op_star
(paren
id|p
op_increment
)paren
)paren
)paren
(brace
r_goto
id|found_middle
suffix:semicolon
)brace
id|result
op_add_assign
l_int|32
suffix:semicolon
id|size
op_sub_assign
l_int|32
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
r_return
id|result
suffix:semicolon
)brace
id|tmp
op_assign
op_star
id|p
suffix:semicolon
id|found_first
suffix:colon
multiline_comment|/* tmp is little endian, so we would have to swab the shift,&n;&t; * see above. But then we have to swab tmp below for ffz, so&n;&t; * we might as well do this here.&n;&t; */
r_return
id|result
op_plus
id|ffz
c_func
(paren
id|__swab32
c_func
(paren
id|tmp
)paren
op_or
(paren
op_complement
l_int|0UL
op_lshift
id|size
)paren
)paren
suffix:semicolon
id|found_middle
suffix:colon
r_return
id|result
op_plus
id|ffz
c_func
(paren
id|__swab32
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Bitmap functions for the minix filesystem.  */
DECL|macro|minix_test_and_set_bit
mdefine_line|#define minix_test_and_set_bit(nr,addr) test_and_set_bit(nr,addr)
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,addr) set_bit(nr,addr)
DECL|macro|minix_test_and_clear_bit
mdefine_line|#define minix_test_and_clear_bit(nr,addr) test_and_clear_bit(nr,addr)
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,addr) test_bit(nr,addr)
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(addr,size) find_first_zero_bit(addr,size)
multiline_comment|/**&n; * hweightN - returns the hamming weight of a N-bit word&n; * @x: the word to weigh&n; *&n; * The Hamming Weight of a number is the total number of bits set in it.&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * fls: find last bit set.&n; */
DECL|macro|fls
mdefine_line|#define fls(x) generic_fls(x)
macro_line|#endif /* _M68KNOMMU_BITOPS_H */
eof
