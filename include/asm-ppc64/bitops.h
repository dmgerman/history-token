multiline_comment|/*&n; * PowerPC64 atomic bit operations.&n; * Dave Engebretsen, Todd Inglett, Don Reed, Pat McCarthy, Peter Bergner,&n; * Anton Blanchard&n; *&n; * Originally taken from the 32b PPC code.  Modified to use 64b values for&n; * the various counters &amp; memory references.&n; *&n; * Bitops are odd when viewed on big-endian systems.  They were designed&n; * on little endian so the size of the bitset doesn&squot;t matter (low order bytes&n; * come first) as long as the bit in question is valid.&n; *&n; * Bits are &quot;tested&quot; often using the C expression (val &amp; (1&lt;&lt;nr)) so we do&n; * our best to stay compatible with that.  The assumption is that val will&n; * be unsigned long for such tests.  As such, we assume the bits are stored&n; * as an array of unsigned long (the usual case is a single unsigned long,&n; * of course).  Here&squot;s an example bitset with bit numbering:&n; *&n; *   |63..........0|127........64|195.......128|255.......196|&n; *&n; * This leads to a problem. If an int, short or char is passed as a bitset&n; * it will be a bad memory reference since we want to store in chunks&n; * of unsigned long (64 bits here) size.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _PPC64_BITOPS_H
DECL|macro|_PPC64_BITOPS_H
mdefine_line|#define _PPC64_BITOPS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/memory.h&gt;
multiline_comment|/*&n; * clear_bit doesn&squot;t imply a memory barrier&n; */
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;smp_mb()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;smp_mb()
DECL|function|test_bit
r_static
id|__inline__
r_int
id|test_bit
c_func
(paren
r_int
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
r_return
(paren
l_int|1UL
op_amp
(paren
id|addr
(braket
id|nr
op_rshift
l_int|6
)braket
op_rshift
(paren
id|nr
op_amp
l_int|63
)paren
)paren
)paren
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldarx&t;%0,0,%3&t;&t;# set_bit&bslash;n&bslash;&n;&t;or&t;%0,%0,%2&bslash;n&bslash;&n;&t;stdcx.&t;%0,0,%3&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
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
DECL|function|clear_bit
r_static
id|__inline__
r_void
id|clear_bit
c_func
(paren
r_int
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldarx&t;%0,0,%3&t;&t;# clear_bit&bslash;n&bslash;&n;&t;andc&t;%0,%0,%2&bslash;n&bslash;&n;&t;stdcx.&t;%0,0,%3&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
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
DECL|function|change_bit
r_static
id|__inline__
r_void
id|change_bit
c_func
(paren
r_int
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldarx&t;%0,0,%3&t;&t;# change_bit&bslash;n&bslash;&n;&t;xor&t;%0,%0,%2&bslash;n&bslash;&n;&t;stdcx.&t;%0,0,%3&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
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
DECL|function|test_and_set_bit
r_static
id|__inline__
r_int
id|test_and_set_bit
c_func
(paren
r_int
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;ldarx&t;%0,0,%3&t;&t;# test_and_set_bit&bslash;n&bslash;&n;&t;or&t;%1,%0,%2 &bslash;n&bslash;&n;&t;stdcx.&t;%1,0,%3 &bslash;n&bslash;&n;&t;bne-&t;1b&quot;
id|ISYNC_ON_SMP
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
DECL|function|test_and_clear_bit
r_static
id|__inline__
r_int
id|test_and_clear_bit
c_func
(paren
r_int
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;ldarx&t;%0,0,%3&t;&t;# test_and_clear_bit&bslash;n&bslash;&n;&t;andc&t;%1,%0,%2&bslash;n&bslash;&n;&t;stdcx.&t;%1,0,%3&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
id|ISYNC_ON_SMP
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
DECL|function|test_and_change_bit
r_static
id|__inline__
r_int
id|test_and_change_bit
c_func
(paren
r_int
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;ldarx&t;%0,0,%3&t;&t;# test_and_change_bit&bslash;n&bslash;&n;&t;xor&t;%1,%0,%2&bslash;n&bslash;&n;&t;stdcx.&t;%1,0,%3&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
id|ISYNC_ON_SMP
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
multiline_comment|/*&n; * non-atomic versions&n; */
DECL|function|__set_bit
r_static
id|__inline__
r_void
id|__set_bit
c_func
(paren
r_int
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
)paren
suffix:semicolon
op_star
id|p
op_or_assign
id|mask
suffix:semicolon
)brace
DECL|function|__clear_bit
r_static
id|__inline__
r_void
id|__clear_bit
c_func
(paren
r_int
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
)paren
suffix:semicolon
op_star
id|p
op_and_assign
op_complement
id|mask
suffix:semicolon
)brace
DECL|function|__change_bit
r_static
id|__inline__
r_void
id|__change_bit
c_func
(paren
r_int
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
)paren
suffix:semicolon
op_star
id|p
op_xor_assign
id|mask
suffix:semicolon
)brace
DECL|function|__test_and_set_bit
r_static
id|__inline__
r_int
id|__test_and_set_bit
c_func
(paren
r_int
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
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
DECL|function|__test_and_clear_bit
r_static
id|__inline__
r_int
id|__test_and_clear_bit
c_func
(paren
r_int
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
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
DECL|function|__test_and_change_bit
r_static
id|__inline__
r_int
id|__test_and_change_bit
c_func
(paren
r_int
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
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|0x3f
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
l_int|6
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
multiline_comment|/*&n; * Return the zero-based bit position (from RIGHT TO LEFT, 63 -&gt; 0) of the&n; * most significant (left-most) 1-bit in a double word.&n; */
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
l_string|&quot;cntlzd %0,%1&quot;
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
l_int|63
op_minus
id|lz
suffix:semicolon
)brace
multiline_comment|/*&n; * Determines the bit position of the least significant (rightmost) 0 bit&n; * in the specified double word. The returned bit position will be zero-based,&n; * starting from the right side (63 - 0).&n; */
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
id|x
)paren
(brace
multiline_comment|/* no zero exists anywhere in the 8 byte area. */
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
l_int|64
suffix:semicolon
multiline_comment|/*&n;&t; * Calculate the bit position of the least signficant &squot;1&squot; bit in x&n;&t; * (since x has been changed this will actually be the least signficant&n;&t; * &squot;0&squot; bit in * the original x).  Note: (x &amp; -x) gives us a mask that&n;&t; * is the least significant * (RIGHT-most) 1-bit of the value in x.&n;&t; */
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
DECL|function|__ffs
r_static
id|__inline__
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
r_int
r_int
id|i
op_assign
(paren
r_int
r_int
)paren
id|x
suffix:semicolon
r_return
id|__ilog2
c_func
(paren
id|i
op_amp
op_minus
id|i
)paren
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * fls: find last (most-significant) bit set.&n; * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.&n; */
DECL|macro|fls
mdefine_line|#define fls(x) generic_fls(x)
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
r_extern
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
suffix:semicolon
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;&t;find_next_zero_bit((addr), (size), 0)
r_extern
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
suffix:semicolon
DECL|macro|find_first_bit
mdefine_line|#define find_first_bit(addr, size) &bslash;&n;&t;find_next_bit((addr), (size), 0)
r_extern
r_int
r_int
id|find_next_zero_le_bit
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
suffix:semicolon
DECL|macro|find_first_zero_le_bit
mdefine_line|#define find_first_zero_le_bit(addr, size) &bslash;&n;&t;find_next_zero_le_bit((addr), (size), 0)
DECL|function|test_le_bit
r_static
id|__inline__
r_int
id|test_le_bit
c_func
(paren
r_int
r_int
id|nr
comma
id|__const__
r_int
r_int
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
multiline_comment|/*&n; * non-atomic versions&n; */
DECL|function|__set_le_bit
r_static
id|__inline__
r_void
id|__set_le_bit
c_func
(paren
r_int
r_int
id|nr
comma
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
r_char
op_star
id|ADDR
op_assign
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
id|ADDR
op_add_assign
id|nr
op_rshift
l_int|3
suffix:semicolon
op_star
id|ADDR
op_or_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x07
)paren
suffix:semicolon
)brace
DECL|function|__clear_le_bit
r_static
id|__inline__
r_void
id|__clear_le_bit
c_func
(paren
r_int
r_int
id|nr
comma
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
r_char
op_star
id|ADDR
op_assign
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
id|ADDR
op_add_assign
id|nr
op_rshift
l_int|3
suffix:semicolon
op_star
id|ADDR
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x07
)paren
)paren
suffix:semicolon
)brace
DECL|function|__test_and_set_le_bit
r_static
id|__inline__
r_int
id|__test_and_set_le_bit
c_func
(paren
r_int
r_int
id|nr
comma
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
id|mask
comma
id|retval
suffix:semicolon
r_int
r_char
op_star
id|ADDR
op_assign
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
id|ADDR
op_add_assign
id|nr
op_rshift
l_int|3
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x07
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|ADDR
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|ADDR
op_or_assign
id|mask
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|__test_and_clear_le_bit
r_static
id|__inline__
r_int
id|__test_and_clear_le_bit
c_func
(paren
r_int
r_int
id|nr
comma
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
id|mask
comma
id|retval
suffix:semicolon
r_int
r_char
op_star
id|ADDR
op_assign
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
id|ADDR
op_add_assign
id|nr
op_rshift
l_int|3
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|0x07
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|ADDR
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|ADDR
op_and_assign
op_complement
id|mask
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr,addr) &bslash;&n;&t;__test_and_set_le_bit((nr),(unsigned long*)addr)
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr, addr) &bslash;&n;&t;__test_and_clear_le_bit((nr),(unsigned long*)addr)
DECL|macro|ext2_test_bit
mdefine_line|#define ext2_test_bit(nr, addr)      test_le_bit((nr),(unsigned long*)addr)
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit(addr, size) &bslash;&n;&t;find_first_zero_le_bit((unsigned long*)addr, size)
DECL|macro|ext2_find_next_zero_bit
mdefine_line|#define ext2_find_next_zero_bit(addr, size, off) &bslash;&n;&t;find_next_zero_le_bit((unsigned long*)addr, size, off)
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _PPC64_BITOPS_H */
eof
