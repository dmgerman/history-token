multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * bitops.h: Bit string operations on the ppc&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_BITOPS_H
DECL|macro|_PPC_BITOPS_H
mdefine_line|#define _PPC_BITOPS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * The test_and_*_bit operations are taken to imply a memory barrier&n; * on SMP systems.&n; */
macro_line|#ifdef CONFIG_SMP
DECL|macro|SMP_WMB
mdefine_line|#define SMP_WMB&t;&t;&quot;eieio&bslash;n&quot;
DECL|macro|SMP_MB
mdefine_line|#define SMP_MB&t;&t;&quot;&bslash;nsync&quot;
macro_line|#else
DECL|macro|SMP_WMB
mdefine_line|#define SMP_WMB
DECL|macro|SMP_MB
mdefine_line|#define SMP_MB
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/*&n; * These used to be if&squot;d out here because using : &quot;cc&quot; as a constraint&n; * resulted in errors from egcs.  Things appear to be OK with gcc-2.95.&n; */
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
r_int
r_int
id|old
suffix:semicolon
r_int
r_int
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%3 &bslash;n&bslash;&n;&t;or&t;%0,%0,%2 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|3
)paren
l_string|&quot;&t;stwcx.&t;%0,0,%3 &bslash;n&bslash;&n;&t;bne-&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * non-atomic version&n; */
DECL|function|__set_bit
r_static
id|__inline__
r_void
id|__set_bit
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
r_int
r_int
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
op_star
id|p
op_or_assign
id|mask
suffix:semicolon
)brace
multiline_comment|/*&n; * clear_bit doesn&squot;t imply a memory barrier&n; */
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;smp_mb()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;smp_mb()
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
r_int
r_int
id|old
suffix:semicolon
r_int
r_int
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%3 &bslash;n&bslash;&n;&t;andc&t;%0,%0,%2 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|3
)paren
l_string|&quot;&t;stwcx.&t;%0,0,%3 &bslash;n&bslash;&n;&t;bne-&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * non-atomic version&n; */
DECL|function|__clear_bit
r_static
id|__inline__
r_void
id|__clear_bit
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
r_int
r_int
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
op_star
id|p
op_and_assign
op_complement
id|mask
suffix:semicolon
)brace
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
r_int
r_int
id|old
suffix:semicolon
r_int
r_int
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%3 &bslash;n&bslash;&n;&t;xor&t;%0,%0,%2 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|3
)paren
l_string|&quot;&t;stwcx.&t;%0,0,%3 &bslash;n&bslash;&n;&t;bne-&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * non-atomic version&n; */
DECL|function|__change_bit
r_static
id|__inline__
r_void
id|__change_bit
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
r_int
r_int
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
op_star
id|p
op_xor_assign
id|mask
suffix:semicolon
)brace
multiline_comment|/*&n; * test_and_*_bit do imply a memory barrier (?)&n; */
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
r_int
r_int
id|old
comma
id|t
suffix:semicolon
r_int
r_int
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
r_volatile
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|SMP_WMB
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%4 &bslash;n&bslash;&n;&t;or&t;%1,%0,%3 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|4
)paren
l_string|&quot;&t;stwcx.&t;%1,0,%4 &bslash;n&bslash;&n;&t;bne&t;1b&quot;
id|SMP_MB
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * non-atomic version&n; */
DECL|function|__test_and_set_bit
r_static
id|__inline__
r_int
id|__test_and_set_bit
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
r_int
r_int
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
r_int
id|old
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|old
op_or
id|mask
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
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
r_int
r_int
id|old
comma
id|t
suffix:semicolon
r_int
r_int
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
r_volatile
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|SMP_WMB
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%4 &bslash;n&bslash;&n;&t;andc&t;%1,%0,%3 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|4
)paren
l_string|&quot;&t;stwcx.&t;%1,0,%4 &bslash;n&bslash;&n;&t;bne&t;1b&quot;
id|SMP_MB
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * non-atomic version&n; */
DECL|function|__test_and_clear_bit
r_static
id|__inline__
r_int
id|__test_and_clear_bit
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
r_int
r_int
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
r_int
id|old
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|old
op_amp
op_complement
id|mask
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
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
r_int
r_int
id|old
comma
id|t
suffix:semicolon
r_int
r_int
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
r_volatile
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|SMP_WMB
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%4 &bslash;n&bslash;&n;&t;xor&t;%1,%0,%3 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|4
)paren
l_string|&quot;&t;stwcx.&t;%1,0,%4 &bslash;n&bslash;&n;&t;bne&t;1b&quot;
id|SMP_MB
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * non-atomic version&n; */
DECL|function|__test_and_change_bit
r_static
id|__inline__
r_int
id|__test_and_change_bit
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
r_int
r_int
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
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
r_int
id|old
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|old
op_xor
id|mask
suffix:semicolon
r_return
(paren
id|old
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|test_bit
r_static
id|__inline__
r_int
id|test_bit
c_func
(paren
r_int
id|nr
comma
id|__const__
r_volatile
r_int
r_int
op_star
id|addr
)paren
(brace
id|__const__
r_int
r_int
op_star
id|p
op_assign
(paren
id|__const__
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_return
(paren
(paren
id|p
(braket
id|nr
op_rshift
l_int|5
)braket
op_rshift
(paren
id|nr
op_amp
l_int|0x1f
)paren
)paren
op_amp
l_int|1
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Return the bit position of the most significant 1 bit in a word */
DECL|function|__ilog2
r_static
id|__inline__
r_int
id|__ilog2
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
id|lz
suffix:semicolon
id|asm
(paren
l_string|&quot;cntlzw %0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|lz
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
l_int|31
op_minus
id|lz
suffix:semicolon
)brace
DECL|function|ffz
r_static
id|__inline__
r_int
id|ffz
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_if
c_cond
(paren
(paren
id|x
op_assign
op_complement
id|x
)paren
op_eq
l_int|0
)paren
r_return
l_int|32
suffix:semicolon
r_return
id|__ilog2
c_func
(paren
id|x
op_amp
op_minus
id|x
)paren
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
DECL|function|__ffs
r_static
r_inline
r_int
id|__ffs
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_return
id|__ilog2
c_func
(paren
id|x
op_amp
op_minus
id|x
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ffs: find first bit set. This is defined the same way as&n; * the libc and compiler builtin ffs routines, therefore&n; * differs in spirit from the above ffz (man ffs).&n; */
DECL|function|ffs
r_static
id|__inline__
r_int
id|ffs
c_func
(paren
r_int
id|x
)paren
(brace
r_return
id|__ilog2
c_func
(paren
id|x
op_amp
op_minus
id|x
)paren
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * fls: find last (most-significant) bit set.&n; * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.&n; */
DECL|function|fls
r_static
id|__inline__
r_int
id|fls
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
id|lz
suffix:semicolon
id|asm
(paren
l_string|&quot;cntlzw %0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|lz
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
l_int|32
op_minus
id|lz
suffix:semicolon
)brace
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Find the first bit set in a 140-bit bitmap.&n; * The first 100 bits are unlikely to be set.&n; */
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
multiline_comment|/**&n; * find_next_bit - find the next set bit in a memory region&n; * @addr: The address to base the search on&n; * @offset: The bitnumber to start searching at&n; * @size: The maximum size to search&n; */
DECL|function|find_next_bit
r_static
id|__inline__
r_int
r_int
id|find_next_bit
c_func
(paren
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
multiline_comment|/**&n; * find_first_bit - find the first set bit in a memory region&n; * @addr: The address to start the search at&n; * @size: The maximum size to search&n; *&n; * Returns the bit-number of the first set bit, not the number of the byte&n; * containing a bit.&n; */
DECL|macro|find_first_bit
mdefine_line|#define find_first_bit(addr, size) &bslash;&n;&t;find_next_bit((addr), (size), 0)
multiline_comment|/*&n; * This implementation of find_{first,next}_zero_bit was stolen from&n; * Linus&squot; asm-alpha/bitops.h.&n; */
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;&t;find_next_zero_bit((addr), (size), 0)
DECL|function|find_next_zero_bit
r_static
id|__inline__
r_int
r_int
id|find_next_zero_bit
c_func
(paren
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
id|tmp
op_ne
op_complement
l_int|0U
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
op_complement
l_int|0U
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
op_lshift
id|size
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
op_complement
l_int|0UL
)paren
multiline_comment|/* Are any bits zero? */
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
id|ffz
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr, addr)&t;__test_and_set_bit((nr) ^ 0x18, (unsigned long *)(addr))
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr, addr) __test_and_clear_bit((nr) ^ 0x18, (unsigned long *)(addr))
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
id|__const__
r_void
op_star
id|addr
)paren
(brace
id|__const__
r_int
r_char
op_star
id|ADDR
op_assign
(paren
id|__const__
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
r_return
(paren
id|ADDR
(braket
id|nr
op_rshift
l_int|3
)braket
op_rshift
(paren
id|nr
op_amp
l_int|7
)paren
)paren
op_amp
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * This implementation of ext2_find_{first,next}_zero_bit was stolen from&n; * Linus&squot; asm-alpha/bitops.h and modified for a big-endian machine.&n; */
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
id|tmp
op_assign
id|cpu_to_le32p
c_func
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
id|tmp
op_ne
op_complement
l_int|0U
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
id|cpu_to_le32p
c_func
(paren
id|p
op_increment
)paren
)paren
op_ne
op_complement
l_int|0U
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
id|cpu_to_le32p
c_func
(paren
id|p
)paren
suffix:semicolon
id|found_first
suffix:colon
id|tmp
op_or_assign
op_complement
l_int|0U
op_lshift
id|size
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
op_complement
l_int|0UL
)paren
multiline_comment|/* Are any bits zero? */
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
id|ffz
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
multiline_comment|/* Bitmap functions for the minix filesystem.  */
DECL|macro|minix_test_and_set_bit
mdefine_line|#define minix_test_and_set_bit(nr,addr) ext2_set_bit(nr,addr)
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,addr) ((void)ext2_set_bit(nr,addr))
DECL|macro|minix_test_and_clear_bit
mdefine_line|#define minix_test_and_clear_bit(nr,addr) ext2_clear_bit(nr,addr)
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,addr) ext2_test_bit(nr,addr)
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(addr,size) ext2_find_first_zero_bit(addr,size)
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif /* _PPC_BITOPS_H */
macro_line|#endif /* __KERNEL__ */
eof
