macro_line|#ifndef _ASM_IA64_BITOPS_H
DECL|macro|_ASM_IA64_BITOPS_H
mdefine_line|#define _ASM_IA64_BITOPS_H
multiline_comment|/*&n; * Copyright (C) 1998-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * 02/06/02 find_next_bit() and find_first_bit() added from Erich Focht&squot;s ia64 O(1)&n; *&t;    scheduler patch&n; */
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/intrinsics.h&gt;
multiline_comment|/**&n; * set_bit - Atomically set a bit in memory&n; * @nr: the bit to set&n; * @addr: the address to start counting from&n; *&n; * This function is atomic and may not be reordered.  See __set_bit()&n; * if you do not require the atomic guarantees.&n; * Note that @nr may be almost arbitrarily large; this function is not&n; * restricted to acting on a single-word quantity.&n; *&n; * The address must be (at least) &quot;long&quot; aligned.&n; * Note that there are driver (e.g., eepro100) which use these operations to operate on&n; * hw-defined data-structures, so we can&squot;t easily change these operations to force a&n; * bigger alignment.&n; *&n; * bit 0 is the LSB of addr; bit 32 is the LSB of (addr+1).&n; */
r_static
id|__inline__
r_void
DECL|function|set_bit
id|set_bit
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
id|__u32
id|bit
comma
id|old
comma
r_new
suffix:semicolon
r_volatile
id|__u32
op_star
id|m
suffix:semicolon
id|CMPXCHG_BUGCHECK_DECL
id|m
op_assign
(paren
r_volatile
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|bit
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
r_do
(brace
id|CMPXCHG_BUGCHECK
c_func
(paren
id|m
)paren
suffix:semicolon
id|old
op_assign
op_star
id|m
suffix:semicolon
r_new
op_assign
id|old
op_or
id|bit
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg_acq
c_func
(paren
id|m
comma
id|old
comma
r_new
)paren
op_ne
id|old
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * __set_bit - Set a bit in memory&n; * @nr: the bit to set&n; * @addr: the address to start counting from&n; *&n; * Unlike set_bit(), this function is non-atomic and may be reordered.&n; * If it&squot;s called on the same region of memory simultaneously, the effect&n; * may be that only one operation succeeds.&n; */
r_static
id|__inline__
r_void
DECL|function|__set_bit
id|__set_bit
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
op_star
(paren
(paren
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
)paren
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * clear_bit() has &quot;acquire&quot; semantics.&n; */
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;smp_mb()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;do { /* skip */; } while (0)
multiline_comment|/**&n; * clear_bit - Clears a bit in memory&n; * @nr: Bit to clear&n; * @addr: Address to start counting from&n; *&n; * clear_bit() is atomic and may not be reordered.  However, it does&n; * not contain a memory barrier, so if it is used for locking purposes,&n; * you should call smp_mb__before_clear_bit() and/or smp_mb__after_clear_bit()&n; * in order to ensure changes are visible on other processors.&n; */
r_static
id|__inline__
r_void
DECL|function|clear_bit
id|clear_bit
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
id|__u32
id|mask
comma
id|old
comma
r_new
suffix:semicolon
r_volatile
id|__u32
op_star
id|m
suffix:semicolon
id|CMPXCHG_BUGCHECK_DECL
id|m
op_assign
(paren
r_volatile
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|mask
op_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
suffix:semicolon
r_do
(brace
id|CMPXCHG_BUGCHECK
c_func
(paren
id|m
)paren
suffix:semicolon
id|old
op_assign
op_star
id|m
suffix:semicolon
r_new
op_assign
id|old
op_amp
id|mask
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg_acq
c_func
(paren
id|m
comma
id|old
comma
r_new
)paren
op_ne
id|old
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * __clear_bit - Clears a bit in memory (non-atomic version)&n; */
r_static
id|__inline__
r_void
DECL|function|__clear_bit
id|__clear_bit
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
r_volatile
id|__u32
op_star
id|p
op_assign
(paren
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__u32
id|m
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
op_star
id|p
op_and_assign
op_complement
id|m
suffix:semicolon
)brace
multiline_comment|/**&n; * change_bit - Toggle a bit in memory&n; * @nr: Bit to clear&n; * @addr: Address to start counting from&n; *&n; * change_bit() is atomic and may not be reordered.&n; * Note that @nr may be almost arbitrarily large; this function is not&n; * restricted to acting on a single-word quantity.&n; */
r_static
id|__inline__
r_void
DECL|function|change_bit
id|change_bit
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
id|__u32
id|bit
comma
id|old
comma
r_new
suffix:semicolon
r_volatile
id|__u32
op_star
id|m
suffix:semicolon
id|CMPXCHG_BUGCHECK_DECL
id|m
op_assign
(paren
r_volatile
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|bit
op_assign
(paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
suffix:semicolon
r_do
(brace
id|CMPXCHG_BUGCHECK
c_func
(paren
id|m
)paren
suffix:semicolon
id|old
op_assign
op_star
id|m
suffix:semicolon
r_new
op_assign
id|old
op_xor
id|bit
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg_acq
c_func
(paren
id|m
comma
id|old
comma
r_new
)paren
op_ne
id|old
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * __change_bit - Toggle a bit in memory&n; * @nr: the bit to set&n; * @addr: the address to start counting from&n; *&n; * Unlike change_bit(), this function is non-atomic and may be reordered.&n; * If it&squot;s called on the same region of memory simultaneously, the effect&n; * may be that only one operation succeeds.&n; */
r_static
id|__inline__
r_void
DECL|function|__change_bit
id|__change_bit
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
op_star
(paren
(paren
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
)paren
op_xor_assign
(paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * test_and_set_bit - Set a bit and return its old value&n; * @nr: Bit to set&n; * @addr: Address to count from&n; *&n; * This operation is atomic and cannot be reordered.  &n; * It also implies a memory barrier.&n; */
r_static
id|__inline__
r_int
DECL|function|test_and_set_bit
id|test_and_set_bit
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
id|__u32
id|bit
comma
id|old
comma
r_new
suffix:semicolon
r_volatile
id|__u32
op_star
id|m
suffix:semicolon
id|CMPXCHG_BUGCHECK_DECL
id|m
op_assign
(paren
r_volatile
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|bit
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
r_do
(brace
id|CMPXCHG_BUGCHECK
c_func
(paren
id|m
)paren
suffix:semicolon
id|old
op_assign
op_star
id|m
suffix:semicolon
r_new
op_assign
id|old
op_or
id|bit
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg_acq
c_func
(paren
id|m
comma
id|old
comma
r_new
)paren
op_ne
id|old
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|bit
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * __test_and_set_bit - Set a bit and return its old value&n; * @nr: Bit to set&n; * @addr: Address to count from&n; *&n; * This operation is non-atomic and can be reordered.  &n; * If two examples of this operation race, one can appear to succeed&n; * but actually fail.  You must protect multiple accesses with a lock.&n; */
r_static
id|__inline__
r_int
DECL|function|__test_and_set_bit
id|__test_and_set_bit
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
id|__u32
op_star
id|p
op_assign
(paren
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__u32
id|m
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
r_int
id|oldbitset
op_assign
(paren
op_star
id|p
op_amp
id|m
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|p
op_or_assign
id|m
suffix:semicolon
r_return
id|oldbitset
suffix:semicolon
)brace
multiline_comment|/**&n; * test_and_clear_bit - Clear a bit and return its old value&n; * @nr: Bit to set&n; * @addr: Address to count from&n; *&n; * This operation is atomic and cannot be reordered.  &n; * It also implies a memory barrier.&n; */
r_static
id|__inline__
r_int
DECL|function|test_and_clear_bit
id|test_and_clear_bit
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
id|__u32
id|mask
comma
id|old
comma
r_new
suffix:semicolon
r_volatile
id|__u32
op_star
id|m
suffix:semicolon
id|CMPXCHG_BUGCHECK_DECL
id|m
op_assign
(paren
r_volatile
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|mask
op_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
suffix:semicolon
r_do
(brace
id|CMPXCHG_BUGCHECK
c_func
(paren
id|m
)paren
suffix:semicolon
id|old
op_assign
op_star
id|m
suffix:semicolon
r_new
op_assign
id|old
op_amp
id|mask
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg_acq
c_func
(paren
id|m
comma
id|old
comma
r_new
)paren
op_ne
id|old
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
op_complement
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * __test_and_clear_bit - Clear a bit and return its old value&n; * @nr: Bit to set&n; * @addr: Address to count from&n; *&n; * This operation is non-atomic and can be reordered.  &n; * If two examples of this operation race, one can appear to succeed&n; * but actually fail.  You must protect multiple accesses with a lock.&n; */
r_static
id|__inline__
r_int
DECL|function|__test_and_clear_bit
id|__test_and_clear_bit
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
id|__u32
op_star
id|p
op_assign
(paren
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|__u32
id|m
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
r_int
id|oldbitset
op_assign
op_star
id|p
op_amp
id|m
suffix:semicolon
op_star
id|p
op_and_assign
op_complement
id|m
suffix:semicolon
r_return
id|oldbitset
suffix:semicolon
)brace
multiline_comment|/**&n; * test_and_change_bit - Change a bit and return its new value&n; * @nr: Bit to set&n; * @addr: Address to count from&n; *&n; * This operation is atomic and cannot be reordered.  &n; * It also implies a memory barrier.&n; */
r_static
id|__inline__
r_int
DECL|function|test_and_change_bit
id|test_and_change_bit
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
id|__u32
id|bit
comma
id|old
comma
r_new
suffix:semicolon
r_volatile
id|__u32
op_star
id|m
suffix:semicolon
id|CMPXCHG_BUGCHECK_DECL
id|m
op_assign
(paren
r_volatile
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|bit
op_assign
(paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
suffix:semicolon
r_do
(brace
id|CMPXCHG_BUGCHECK
c_func
(paren
id|m
)paren
suffix:semicolon
id|old
op_assign
op_star
id|m
suffix:semicolon
r_new
op_assign
id|old
op_xor
id|bit
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg_acq
c_func
(paren
id|m
comma
id|old
comma
r_new
)paren
op_ne
id|old
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|bit
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * WARNING: non atomic version.&n; */
r_static
id|__inline__
r_int
DECL|function|__test_and_change_bit
id|__test_and_change_bit
(paren
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
id|__u32
id|old
comma
id|bit
op_assign
(paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
suffix:semicolon
id|__u32
op_star
id|m
op_assign
(paren
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
suffix:semicolon
id|old
op_assign
op_star
id|m
suffix:semicolon
op_star
id|m
op_assign
id|old
op_xor
id|bit
suffix:semicolon
r_return
(paren
id|old
op_amp
id|bit
)paren
op_ne
l_int|0
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|test_bit
id|test_bit
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
r_return
l_int|1
op_amp
(paren
(paren
(paren
r_const
r_volatile
id|__u32
op_star
)paren
id|addr
)paren
(braket
id|nr
op_rshift
l_int|5
)braket
op_rshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * ffz - find the first zero bit in a long word&n; * @x: The long word to find the bit in&n; *&n; * Returns the bit-number (0..63) of the first (least significant) zero bit.  Undefined if&n; * no zero exists, so code should check against ~0UL first...&n; */
r_static
r_inline
r_int
r_int
DECL|function|ffz
id|ffz
(paren
r_int
r_int
id|x
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
id|__asm__
(paren
l_string|&quot;popcnt %0=%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
op_amp
(paren
op_complement
id|x
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * __ffs - find first bit in word.&n; * @x: The word to search&n; *&n; * Undefined if no bit exists, so code should check against 0 first.&n; */
r_static
id|__inline__
r_int
r_int
DECL|function|__ffs
id|__ffs
(paren
r_int
r_int
id|x
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
id|__asm__
(paren
l_string|&quot;popcnt %0=%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
id|x
op_minus
l_int|1
)paren
op_amp
op_complement
id|x
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * find_last_zero_bit - find the last zero bit in a 64 bit quantity&n; * @x: The value to search&n; */
r_static
r_inline
r_int
r_int
DECL|function|ia64_fls
id|ia64_fls
(paren
r_int
r_int
id|x
)paren
(brace
r_int
r_float
id|d
op_assign
id|x
suffix:semicolon
r_int
id|exp
suffix:semicolon
id|__asm__
(paren
l_string|&quot;getf.exp %0=%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|exp
)paren
suffix:colon
l_string|&quot;f&quot;
(paren
id|d
)paren
)paren
suffix:semicolon
r_return
id|exp
op_minus
l_int|0xffff
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|fls
id|fls
(paren
r_int
id|x
)paren
(brace
r_return
id|ia64_fls
c_func
(paren
(paren
r_int
r_int
)paren
id|x
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ffs: find first bit set. This is defined the same way as the libc and compiler builtin&n; * ffs routines, therefore differs in spirit from the above ffz (man ffs): it operates on&n; * &quot;int&quot; values only and the result value is the bit number + 1.  ffs(0) is defined to&n; * return zero.&n; */
DECL|macro|ffs
mdefine_line|#define ffs(x)&t;__builtin_ffs(x)
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
r_static
id|__inline__
r_int
r_int
DECL|function|hweight64
id|hweight64
(paren
r_int
r_int
id|x
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
id|__asm__
(paren
l_string|&quot;popcnt %0=%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|macro|hweight32
mdefine_line|#define hweight32(x) hweight64 ((x) &amp; 0xfffffffful)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) hweight64 ((x) &amp; 0xfffful)
DECL|macro|hweight8
mdefine_line|#define hweight8(x)  hweight64 ((x) &amp; 0xfful)
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Find next zero bit in a bitmap reasonably efficiently..&n; */
r_static
r_inline
r_int
DECL|function|find_next_zero_bit
id|find_next_zero_bit
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
l_int|6
)paren
suffix:semicolon
r_int
r_int
id|result
op_assign
id|offset
op_amp
op_complement
l_int|63UL
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
l_int|63UL
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
l_int|64
op_minus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|64
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
l_int|64
suffix:semicolon
id|result
op_add_assign
l_int|64
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_amp
op_complement
l_int|63UL
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
l_int|64
suffix:semicolon
id|size
op_sub_assign
l_int|64
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
multiline_comment|/* any bits zero? */
r_return
id|result
op_plus
id|size
suffix:semicolon
multiline_comment|/* nope */
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
multiline_comment|/*&n; * The optimizer actually does good code for this case..&n; */
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) find_next_zero_bit((addr), (size), 0)
multiline_comment|/*&n; * Find next bit in a bitmap reasonably efficiently..&n; */
r_static
r_inline
r_int
DECL|function|find_next_bit
id|find_next_bit
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
l_int|6
)paren
suffix:semicolon
r_int
r_int
id|result
op_assign
id|offset
op_amp
op_complement
l_int|63UL
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
l_int|63UL
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
l_int|64
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
l_int|64
suffix:semicolon
id|result
op_add_assign
l_int|64
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_amp
op_complement
l_int|63UL
)paren
(brace
r_if
c_cond
(paren
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
l_int|64
suffix:semicolon
id|size
op_sub_assign
l_int|64
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
l_int|64
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
DECL|macro|find_first_bit
mdefine_line|#define find_first_bit(addr, size) find_next_bit((addr), (size), 0)
macro_line|#ifdef __KERNEL__
DECL|macro|__clear_bit
mdefine_line|#define __clear_bit(nr, addr)        clear_bit(nr, addr)
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit                 test_and_set_bit
DECL|macro|ext2_set_atomic
mdefine_line|#define ext2_set_atomic(l,n,a)&t;     test_and_set_bit(n,a)
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit               test_and_clear_bit
DECL|macro|ext2_clear_atomic
mdefine_line|#define ext2_clear_atomic(l,n,a)     test_and_clear_bit(n,a)
DECL|macro|ext2_test_bit
mdefine_line|#define ext2_test_bit                test_bit
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit     find_first_zero_bit
DECL|macro|ext2_find_next_zero_bit
mdefine_line|#define ext2_find_next_zero_bit      find_next_zero_bit
multiline_comment|/* Bitmap functions for the minix filesystem.  */
DECL|macro|minix_test_and_set_bit
mdefine_line|#define minix_test_and_set_bit(nr,addr)&t;&t;test_and_set_bit(nr,addr)
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,addr)&t;&t;&t;set_bit(nr,addr)
DECL|macro|minix_test_and_clear_bit
mdefine_line|#define minix_test_and_clear_bit(nr,addr)&t;test_and_clear_bit(nr,addr)
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,addr)&t;&t;&t;test_bit(nr,addr)
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(addr,size)&t;find_first_zero_bit(addr,size)
r_static
r_inline
r_int
DECL|function|sched_find_first_bit
id|sched_find_first_bit
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
l_int|64
op_plus
id|__ffs
c_func
(paren
id|b
(braket
l_int|1
)braket
)paren
suffix:semicolon
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
l_int|128
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_IA64_BITOPS_H */
eof
