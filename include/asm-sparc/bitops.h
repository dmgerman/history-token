multiline_comment|/* $Id: bitops.h,v 1.67 2001/11/19 18:36:34 davem Exp $&n; * bitops.h: Bit string operations on the Sparc.&n; *&n; * Copyright 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright 1996 Eddie C. Dost   (ecd@skynet.be)&n; * Copyright 2001 Anton Blanchard (anton@samba.org)&n; */
macro_line|#ifndef _SPARC_BITOPS_H
DECL|macro|_SPARC_BITOPS_H
mdefine_line|#define _SPARC_BITOPS_H
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Set bit &squot;nr&squot; in 32-bit quantity at address &squot;addr&squot; where bit &squot;0&squot;&n; * is in the highest of the four bytes and bit &squot;31&squot; is the high bit&n; * within the first byte. Sparc is BIG-Endian. Unless noted otherwise&n; * all bit-ops return 0 if bit was previously clear and != 0 otherwise.&n; */
DECL|function|test_and_set_bit
r_static
r_inline
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
r_register
r_int
r_int
id|mask
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
op_star
id|ADDR
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp1
id|asm
c_func
(paren
l_string|&quot;g3&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp2
id|asm
c_func
(paren
l_string|&quot;g4&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp3
id|asm
c_func
(paren
l_string|&quot;g5&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp4
id|asm
c_func
(paren
l_string|&quot;g7&quot;
)paren
suffix:semicolon
id|ADDR
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
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___set_bit&bslash;n&bslash;t&quot;
l_string|&quot; add&t;%%o7, 8, %%o7&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp3
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp4
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|mask
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|set_bit
r_static
r_inline
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
r_register
r_int
r_int
id|mask
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
op_star
id|ADDR
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp1
id|asm
c_func
(paren
l_string|&quot;g3&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp2
id|asm
c_func
(paren
l_string|&quot;g4&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp3
id|asm
c_func
(paren
l_string|&quot;g5&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp4
id|asm
c_func
(paren
l_string|&quot;g7&quot;
)paren
suffix:semicolon
id|ADDR
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
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___set_bit&bslash;n&bslash;t&quot;
l_string|&quot; add&t;%%o7, 8, %%o7&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp3
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp4
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|test_and_clear_bit
r_static
r_inline
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
r_register
r_int
r_int
id|mask
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
op_star
id|ADDR
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp1
id|asm
c_func
(paren
l_string|&quot;g3&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp2
id|asm
c_func
(paren
l_string|&quot;g4&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp3
id|asm
c_func
(paren
l_string|&quot;g5&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp4
id|asm
c_func
(paren
l_string|&quot;g7&quot;
)paren
suffix:semicolon
id|ADDR
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
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___clear_bit&bslash;n&bslash;t&quot;
l_string|&quot; add&t;%%o7, 8, %%o7&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp3
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp4
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|mask
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|clear_bit
r_static
r_inline
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
r_register
r_int
r_int
id|mask
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
op_star
id|ADDR
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp1
id|asm
c_func
(paren
l_string|&quot;g3&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp2
id|asm
c_func
(paren
l_string|&quot;g4&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp3
id|asm
c_func
(paren
l_string|&quot;g5&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp4
id|asm
c_func
(paren
l_string|&quot;g7&quot;
)paren
suffix:semicolon
id|ADDR
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
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___clear_bit&bslash;n&bslash;t&quot;
l_string|&quot; add&t;%%o7, 8, %%o7&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp3
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp4
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|test_and_change_bit
r_static
r_inline
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
r_register
r_int
r_int
id|mask
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
op_star
id|ADDR
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp1
id|asm
c_func
(paren
l_string|&quot;g3&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp2
id|asm
c_func
(paren
l_string|&quot;g4&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp3
id|asm
c_func
(paren
l_string|&quot;g5&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp4
id|asm
c_func
(paren
l_string|&quot;g7&quot;
)paren
suffix:semicolon
id|ADDR
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
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___change_bit&bslash;n&bslash;t&quot;
l_string|&quot; add&t;%%o7, 8, %%o7&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp3
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp4
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|mask
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|change_bit
r_static
r_inline
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
r_register
r_int
r_int
id|mask
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
op_star
id|ADDR
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp1
id|asm
c_func
(paren
l_string|&quot;g3&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp2
id|asm
c_func
(paren
l_string|&quot;g4&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp3
id|asm
c_func
(paren
l_string|&quot;g5&quot;
)paren
suffix:semicolon
r_register
r_int
id|tmp4
id|asm
c_func
(paren
l_string|&quot;g7&quot;
)paren
suffix:semicolon
id|ADDR
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
id|mask
op_assign
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___change_bit&bslash;n&bslash;t&quot;
l_string|&quot; add&t;%%o7, 8, %%o7&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp3
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp4
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * non-atomic versions&n; */
DECL|function|__set_bit
r_static
r_inline
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
l_int|1UL
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
DECL|function|__clear_bit
r_static
r_inline
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
l_int|1UL
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
DECL|function|__change_bit
r_static
r_inline
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
l_int|1UL
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
DECL|function|__test_and_set_bit
r_static
r_inline
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
l_int|1UL
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
DECL|function|__test_and_clear_bit
r_static
r_inline
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
l_int|1UL
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
DECL|function|__test_and_change_bit
r_static
r_inline
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
l_int|1UL
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
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;do { } while(0)
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;do { } while(0)
multiline_comment|/* The following routine need not be atomic. */
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
(paren
(paren
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
op_rshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
)paren
op_ne
l_int|0UL
suffix:semicolon
)brace
multiline_comment|/* The easy/cheese version for now. */
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
multiline_comment|/**&n; * __ffs - find first bit in word.&n; * @word: The word to search&n; *&n; * Undefined if no bit exists, so code should check against 0 first.&n; */
DECL|function|__ffs
r_static
r_inline
r_int
id|__ffs
c_func
(paren
r_int
r_int
id|word
)paren
(brace
r_int
id|num
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|word
op_amp
l_int|0xffff
)paren
op_eq
l_int|0
)paren
(brace
id|num
op_add_assign
l_int|16
suffix:semicolon
id|word
op_rshift_assign
l_int|16
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|word
op_amp
l_int|0xff
)paren
op_eq
l_int|0
)paren
(brace
id|num
op_add_assign
l_int|8
suffix:semicolon
id|word
op_rshift_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|word
op_amp
l_int|0xf
)paren
op_eq
l_int|0
)paren
(brace
id|num
op_add_assign
l_int|4
suffix:semicolon
id|word
op_rshift_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|word
op_amp
l_int|0x3
)paren
op_eq
l_int|0
)paren
(brace
id|num
op_add_assign
l_int|2
suffix:semicolon
id|word
op_rshift_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|word
op_amp
l_int|0x1
)paren
op_eq
l_int|0
)paren
id|num
op_add_assign
l_int|1
suffix:semicolon
r_return
id|num
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
r_if
c_cond
(paren
op_logical_neg
id|x
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|__ffs
c_func
(paren
(paren
r_int
r_int
)paren
id|x
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
multiline_comment|/*&n; * find_next_zero_bit() finds the first zero bit in a bit string of length&n; * &squot;size&squot; bits, starting the search at bit &squot;offset&squot;. This is largely based&n; * on Linus&squot;s ALPHA routines, which are pretty portable BTW.&n; */
DECL|function|find_next_zero_bit
r_static
r_inline
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
id|addr
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
multiline_comment|/*&n; * Linus sez that gcc can optimize the following correctly, we&squot;ll see if this&n; * holds on the Sparc as it does for the ALPHA.&n; */
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;        find_next_zero_bit((addr), (size), 0)
multiline_comment|/**&n; * find_next_bit - find the first set bit in a memory region&n; * @addr: The address to base the search on&n; * @offset: The bitnumber to start searching at&n; * @size: The maximum size to search&n; *&n; * Scheduler induced bitop, do not use.&n; */
DECL|function|find_next_bit
r_static
r_inline
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
id|addr
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
id|num
op_assign
id|offset
op_amp
op_complement
l_int|0x1f
suffix:semicolon
r_int
r_int
id|word
suffix:semicolon
id|word
op_assign
op_star
id|p
op_increment
suffix:semicolon
id|word
op_and_assign
op_complement
(paren
(paren
l_int|1
op_lshift
(paren
id|offset
op_amp
l_int|0x1f
)paren
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|num
OL
id|size
)paren
(brace
r_if
c_cond
(paren
id|word
op_ne
l_int|0
)paren
(brace
r_return
id|__ffs
c_func
(paren
id|word
)paren
op_plus
id|num
suffix:semicolon
)brace
id|word
op_assign
op_star
id|p
op_increment
suffix:semicolon
id|num
op_add_assign
l_int|0x20
suffix:semicolon
)brace
r_return
id|num
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|function|test_le_bit
r_static
r_inline
r_int
id|test_le_bit
c_func
(paren
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
r_inline
r_void
id|__set_le_bit
c_func
(paren
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
r_inline
r_void
id|__clear_le_bit
c_func
(paren
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
r_inline
r_int
id|__test_and_set_le_bit
c_func
(paren
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
r_inline
r_int
id|__test_and_clear_le_bit
c_func
(paren
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
DECL|function|find_next_zero_le_bit
r_static
r_inline
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
(brace
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
id|tmp
op_assign
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
r_return
id|result
op_plus
id|ffz
c_func
(paren
id|tmp
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
DECL|macro|find_first_zero_le_bit
mdefine_line|#define find_first_zero_le_bit(addr, size) &bslash;&n;        find_next_zero_le_bit((addr), (size), 0)
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr,addr)&t;&bslash;&n;&t;__test_and_set_le_bit((nr),(unsigned long *)(addr))
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr,addr)&t;&bslash;&n;&t;__test_and_clear_le_bit((nr),(unsigned long *)(addr))
DECL|macro|ext2_set_bit_atomic
mdefine_line|#define ext2_set_bit_atomic(lock, nr, addr)&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int ret;&t;&t;&t;&t;&bslash;&n;&t;&t;spin_lock(lock);&t;&t;&t;&bslash;&n;&t;&t;ret = ext2_set_bit((nr), (unsigned long *)(addr)); &bslash;&n;&t;&t;spin_unlock(lock);&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|ext2_clear_bit_atomic
mdefine_line|#define ext2_clear_bit_atomic(lock, nr, addr)&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int ret;&t;&t;&t;&t;&bslash;&n;&t;&t;spin_lock(lock);&t;&t;&t;&bslash;&n;&t;&t;ret = ext2_clear_bit((nr), (unsigned long *)(addr)); &bslash;&n;&t;&t;spin_unlock(lock);&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|ext2_test_bit
mdefine_line|#define ext2_test_bit(nr,addr)&t;&bslash;&n;&t;test_le_bit((nr),(unsigned long *)(addr))
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit(addr, size) &bslash;&n;&t;find_first_zero_le_bit((unsigned long *)(addr), (size))
DECL|macro|ext2_find_next_zero_bit
mdefine_line|#define ext2_find_next_zero_bit(addr, size, off) &bslash;&n;&t;find_next_zero_le_bit((unsigned long *)(addr), (size), (off))
multiline_comment|/* Bitmap functions for the minix filesystem.  */
DECL|macro|minix_test_and_set_bit
mdefine_line|#define minix_test_and_set_bit(nr,addr)&t;&bslash;&n;&t;test_and_set_bit((nr),(unsigned long *)(addr))
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,addr)&t;&t;&bslash;&n;&t;set_bit((nr),(unsigned long *)(addr))
DECL|macro|minix_test_and_clear_bit
mdefine_line|#define minix_test_and_clear_bit(nr,addr) &bslash;&n;&t;test_and_clear_bit((nr),(unsigned long *)(addr))
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,addr)&t;&t;&bslash;&n;&t;test_bit((nr),(unsigned long *)(addr))
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(addr,size) &bslash;&n;&t;find_first_zero_bit((unsigned long *)(addr),(size))
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* defined(_SPARC_BITOPS_H) */
eof
