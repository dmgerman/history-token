macro_line|#ifndef _S390_BITOPS_H
DECL|macro|_S390_BITOPS_H
mdefine_line|#define _S390_BITOPS_H
multiline_comment|/*&n; *  include/asm-s390/bitops.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/bitops.h&quot;&n; *    Copyright (C) 1992, Linus Torvalds&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * 32 bit bitops format:&n; * bit 0 is the LSB of *addr; bit 31 is the MSB of *addr;&n; * bit 32 is the LSB of *(addr+4). That combined with the&n; * big endian byte order on S390 give the following bit&n; * order in memory:&n; *    1f 1e 1d 1c 1b 1a 19 18 17 16 15 14 13 12 11 10 &bslash;&n; *    0f 0e 0d 0c 0b 0a 09 08 07 06 05 04 03 02 01 00&n; * after that follows the next long with bit numbers&n; *    3f 3e 3d 3c 3b 3a 39 38 37 36 35 34 33 32 31 30&n; *    2f 2e 2d 2c 2b 2a 29 28 27 26 25 24 23 22 21 20&n; * The reason for this bit ordering is the fact that&n; * in the architecture independent code bits operations&n; * of the form &quot;flags |= (1 &lt;&lt; bitnr)&quot; are used INTERMIXED&n; * with operation of the form &quot;set_bit(bitnr, flags)&quot;.&n; *&n; * 64 bit bitops format:&n; * bit 0 is the LSB of *addr; bit 63 is the MSB of *addr;&n; * bit 64 is the LSB of *(addr+8). That combined with the&n; * big endian byte order on S390 give the following bit&n; * order in memory:&n; *    3f 3e 3d 3c 3b 3a 39 38 37 36 35 34 33 32 31 30&n; *    2f 2e 2d 2c 2b 2a 29 28 27 26 25 24 23 22 21 20&n; *    1f 1e 1d 1c 1b 1a 19 18 17 16 15 14 13 12 11 10&n; *    0f 0e 0d 0c 0b 0a 09 08 07 06 05 04 03 02 01 00&n; * after that follows the next long with bit numbers&n; *    7f 7e 7d 7c 7b 7a 79 78 77 76 75 74 73 72 71 70&n; *    6f 6e 6d 6c 6b 6a 69 68 67 66 65 64 63 62 61 60&n; *    5f 5e 5d 5c 5b 5a 59 58 57 56 55 54 53 52 51 50&n; *    4f 4e 4d 4c 4b 4a 49 48 47 46 45 44 43 42 41 40&n; * The reason for this bit ordering is the fact that&n; * in the architecture independent code bits operations&n; * of the form &quot;flags |= (1 &lt;&lt; bitnr)&quot; are used INTERMIXED&n; * with operation of the form &quot;set_bit(bitnr, flags)&quot;.&n; */
multiline_comment|/* set ALIGN_CS to 1 if the SMP safe bit operations should&n; * align the address to 4 byte boundary. It seems to work&n; * without the alignment. &n; */
macro_line|#ifdef __KERNEL__
DECL|macro|ALIGN_CS
mdefine_line|#define ALIGN_CS 0
macro_line|#else
DECL|macro|ALIGN_CS
mdefine_line|#define ALIGN_CS 1
macro_line|#ifndef CONFIG_SMP
macro_line|#error &quot;bitops won&squot;t work without CONFIG_SMP&quot;
macro_line|#endif
macro_line|#endif
multiline_comment|/* bitmap tables from arch/S390/kernel/bitmap.S */
r_extern
r_const
r_char
id|_oi_bitmap
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
id|_ni_bitmap
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
id|_zb_findmap
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
id|_sb_findmap
(braket
)braket
suffix:semicolon
macro_line|#ifndef __s390x__
DECL|macro|__BITOPS_ALIGN
mdefine_line|#define __BITOPS_ALIGN&t;&t;3
DECL|macro|__BITOPS_WORDSIZE
mdefine_line|#define __BITOPS_WORDSIZE&t;32
DECL|macro|__BITOPS_OR
mdefine_line|#define __BITOPS_OR&t;&t;&quot;or&quot;
DECL|macro|__BITOPS_AND
mdefine_line|#define __BITOPS_AND&t;&t;&quot;nr&quot;
DECL|macro|__BITOPS_XOR
mdefine_line|#define __BITOPS_XOR&t;&t;&quot;xr&quot;
DECL|macro|__BITOPS_LOOP
mdefine_line|#define __BITOPS_LOOP(__old, __new, __addr, __val, __op_string)&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;   l   %0,0(%4)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;     &quot;0: lr  %1,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;     __op_string &quot;  %1,%3&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;     &quot;   cs  %0,%1,0(%4)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;     &quot;   jl  0b&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;     : &quot;=&amp;d&quot; (__old), &quot;=&amp;d&quot; (__new),&t;       &t;&bslash;&n;&t;&t;&t;       &quot;=m&quot; (*(unsigned long *) __addr)&t;&t;&bslash;&n;&t;&t;&t;     : &quot;d&quot; (__val), &quot;a&quot; (__addr),&t;&t;&bslash;&n;&t;&t;&t;       &quot;m&quot; (*(unsigned long *) __addr) : &quot;cc&quot; );
macro_line|#else /* __s390x__ */
DECL|macro|__BITOPS_ALIGN
mdefine_line|#define __BITOPS_ALIGN&t;&t;7
DECL|macro|__BITOPS_WORDSIZE
mdefine_line|#define __BITOPS_WORDSIZE&t;64
DECL|macro|__BITOPS_OR
mdefine_line|#define __BITOPS_OR&t;&t;&quot;ogr&quot;
DECL|macro|__BITOPS_AND
mdefine_line|#define __BITOPS_AND&t;&t;&quot;ngr&quot;
DECL|macro|__BITOPS_XOR
mdefine_line|#define __BITOPS_XOR&t;&t;&quot;xgr&quot;
DECL|macro|__BITOPS_LOOP
mdefine_line|#define __BITOPS_LOOP(__old, __new, __addr, __val, __op_string)&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;   lg  %0,0(%4)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;     &quot;0: lgr %1,%0&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;     __op_string &quot;  %1,%3&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;     &quot;   csg %0,%1,0(%4)&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;     &quot;   jl  0b&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;     : &quot;=&amp;d&quot; (__old), &quot;=&amp;d&quot; (__new),&t;       &t;&bslash;&n;&t;&t;&t;       &quot;=m&quot; (*(unsigned long *) __addr)&t;&t;&bslash;&n;&t;&t;&t;     : &quot;d&quot; (__val), &quot;a&quot; (__addr),&t;&t;&bslash;&n;&t;&t;&t;       &quot;m&quot; (*(unsigned long *) __addr) : &quot;cc&quot; );
macro_line|#endif /* __s390x__ */
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n; * SMP safe set_bit routine based on compare and swap (CS)&n; */
DECL|function|set_bit_cs
r_static
r_inline
r_void
id|set_bit_cs
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
comma
id|old
comma
r_new
comma
id|mask
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
macro_line|#if ALIGN_CS == 1
id|nr
op_add_assign
(paren
id|addr
op_amp
id|__BITOPS_ALIGN
)paren
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* add alignment to bit number */
id|addr
op_xor_assign
id|addr
op_amp
id|__BITOPS_ALIGN
suffix:semicolon
multiline_comment|/* align address to 8 */
macro_line|#endif
multiline_comment|/* calculate address for CS */
id|addr
op_add_assign
(paren
id|nr
op_xor
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
)paren
op_rshift
l_int|3
suffix:semicolon
multiline_comment|/* make OR mask */
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* Do the atomic update. */
id|__BITOPS_LOOP
c_func
(paren
id|old
comma
r_new
comma
id|addr
comma
id|mask
comma
id|__BITOPS_OR
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP safe clear_bit routine based on compare and swap (CS)&n; */
DECL|function|clear_bit_cs
r_static
r_inline
r_void
id|clear_bit_cs
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
comma
id|old
comma
r_new
comma
id|mask
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
macro_line|#if ALIGN_CS == 1
id|nr
op_add_assign
(paren
id|addr
op_amp
id|__BITOPS_ALIGN
)paren
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* add alignment to bit number */
id|addr
op_xor_assign
id|addr
op_amp
id|__BITOPS_ALIGN
suffix:semicolon
multiline_comment|/* align address to 8 */
macro_line|#endif
multiline_comment|/* calculate address for CS */
id|addr
op_add_assign
(paren
id|nr
op_xor
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
)paren
op_rshift
l_int|3
suffix:semicolon
multiline_comment|/* make AND mask */
id|mask
op_assign
op_complement
(paren
l_int|1UL
op_lshift
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Do the atomic update. */
id|__BITOPS_LOOP
c_func
(paren
id|old
comma
r_new
comma
id|addr
comma
id|mask
comma
id|__BITOPS_AND
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP safe change_bit routine based on compare and swap (CS)&n; */
DECL|function|change_bit_cs
r_static
r_inline
r_void
id|change_bit_cs
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
comma
id|old
comma
r_new
comma
id|mask
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
macro_line|#if ALIGN_CS == 1
id|nr
op_add_assign
(paren
id|addr
op_amp
id|__BITOPS_ALIGN
)paren
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* add alignment to bit number */
id|addr
op_xor_assign
id|addr
op_amp
id|__BITOPS_ALIGN
suffix:semicolon
multiline_comment|/* align address to 8 */
macro_line|#endif
multiline_comment|/* calculate address for CS */
id|addr
op_add_assign
(paren
id|nr
op_xor
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
)paren
op_rshift
l_int|3
suffix:semicolon
multiline_comment|/* make XOR mask */
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* Do the atomic update. */
id|__BITOPS_LOOP
c_func
(paren
id|old
comma
r_new
comma
id|addr
comma
id|mask
comma
id|__BITOPS_XOR
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP safe test_and_set_bit routine based on compare and swap (CS)&n; */
r_static
r_inline
r_int
DECL|function|test_and_set_bit_cs
id|test_and_set_bit_cs
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
comma
id|old
comma
r_new
comma
id|mask
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
macro_line|#if ALIGN_CS == 1
id|nr
op_add_assign
(paren
id|addr
op_amp
id|__BITOPS_ALIGN
)paren
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* add alignment to bit number */
id|addr
op_xor_assign
id|addr
op_amp
id|__BITOPS_ALIGN
suffix:semicolon
multiline_comment|/* align address to 8 */
macro_line|#endif
multiline_comment|/* calculate address for CS */
id|addr
op_add_assign
(paren
id|nr
op_xor
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
)paren
op_rshift
l_int|3
suffix:semicolon
multiline_comment|/* make OR/test mask */
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* Do the atomic update. */
id|__BITOPS_LOOP
c_func
(paren
id|old
comma
r_new
comma
id|addr
comma
id|mask
comma
id|__BITOPS_OR
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
multiline_comment|/*&n; * SMP safe test_and_clear_bit routine based on compare and swap (CS)&n; */
r_static
r_inline
r_int
DECL|function|test_and_clear_bit_cs
id|test_and_clear_bit_cs
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
comma
id|old
comma
r_new
comma
id|mask
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
macro_line|#if ALIGN_CS == 1
id|nr
op_add_assign
(paren
id|addr
op_amp
id|__BITOPS_ALIGN
)paren
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* add alignment to bit number */
id|addr
op_xor_assign
id|addr
op_amp
id|__BITOPS_ALIGN
suffix:semicolon
multiline_comment|/* align address to 8 */
macro_line|#endif
multiline_comment|/* calculate address for CS */
id|addr
op_add_assign
(paren
id|nr
op_xor
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
)paren
op_rshift
l_int|3
suffix:semicolon
multiline_comment|/* make AND/test mask */
id|mask
op_assign
op_complement
(paren
l_int|1UL
op_lshift
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Do the atomic update. */
id|__BITOPS_LOOP
c_func
(paren
id|old
comma
r_new
comma
id|addr
comma
id|mask
comma
id|__BITOPS_AND
)paren
suffix:semicolon
r_return
(paren
id|old
op_xor
r_new
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP safe test_and_change_bit routine based on compare and swap (CS) &n; */
r_static
r_inline
r_int
DECL|function|test_and_change_bit_cs
id|test_and_change_bit_cs
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
comma
id|old
comma
r_new
comma
id|mask
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
macro_line|#if ALIGN_CS == 1
id|nr
op_add_assign
(paren
id|addr
op_amp
id|__BITOPS_ALIGN
)paren
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* add alignment to bit number */
id|addr
op_xor_assign
id|addr
op_amp
id|__BITOPS_ALIGN
suffix:semicolon
multiline_comment|/* align address to 8 */
macro_line|#endif
multiline_comment|/* calculate address for CS */
id|addr
op_add_assign
(paren
id|nr
op_xor
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
)paren
op_rshift
l_int|3
suffix:semicolon
multiline_comment|/* make XOR/test mask */
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|nr
op_amp
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* Do the atomic update. */
id|__BITOPS_LOOP
c_func
(paren
id|old
comma
r_new
comma
id|addr
comma
id|mask
comma
id|__BITOPS_XOR
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
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/*&n; * fast, non-SMP set_bit routine&n; */
DECL|function|__set_bit
r_static
r_inline
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
op_plus
(paren
(paren
id|nr
op_xor
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|8
)paren
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;oc 0(1,%1),0(%2)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
id|_oi_bitmap
op_plus
(paren
id|nr
op_amp
l_int|7
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__constant_set_bit
id|__constant_set_bit
c_func
(paren
r_const
r_int
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|ptr
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
(paren
(paren
r_int
r_int
)paren
id|ptr
)paren
op_plus
(paren
(paren
id|nr
op_xor
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|8
)paren
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|nr
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;oi 0(%1),0x01&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;oi 0(%1),0x02&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;oi 0(%1),0x04&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;oi 0(%1),0x08&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;oi 0(%1),0x10&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;oi 0(%1),0x20&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;oi 0(%1),0x40&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;oi 0(%1),0x80&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|macro|set_bit_simple
mdefine_line|#define set_bit_simple(nr,addr) &bslash;&n;(__builtin_constant_p((nr)) ? &bslash;&n; __constant_set_bit((nr),(addr)) : &bslash;&n; __set_bit((nr),(addr)) )
multiline_comment|/*&n; * fast, non-SMP clear_bit routine&n; */
r_static
r_inline
r_void
DECL|function|__clear_bit
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
op_plus
(paren
(paren
id|nr
op_xor
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|8
)paren
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;nc 0(1,%1),0(%2)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
id|_ni_bitmap
op_plus
(paren
id|nr
op_amp
l_int|7
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__constant_clear_bit
id|__constant_clear_bit
c_func
(paren
r_const
r_int
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|ptr
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
(paren
(paren
r_int
r_int
)paren
id|ptr
)paren
op_plus
(paren
(paren
id|nr
op_xor
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|8
)paren
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|nr
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;ni 0(%1),0xFE&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;ni 0(%1),0xFD&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;ni 0(%1),0xFB&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;ni 0(%1),0xF7&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;ni 0(%1),0xEF&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;ni 0(%1),0xDF&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;ni 0(%1),0xBF&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;ni 0(%1),0x7F&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|macro|clear_bit_simple
mdefine_line|#define clear_bit_simple(nr,addr) &bslash;&n;(__builtin_constant_p((nr)) ? &bslash;&n; __constant_clear_bit((nr),(addr)) : &bslash;&n; __clear_bit((nr),(addr)) )
multiline_comment|/* &n; * fast, non-SMP change_bit routine &n; */
DECL|function|__change_bit
r_static
r_inline
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
op_plus
(paren
(paren
id|nr
op_xor
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|8
)paren
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;xc 0(1,%1),0(%2)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
id|_oi_bitmap
op_plus
(paren
id|nr
op_amp
l_int|7
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__constant_change_bit
id|__constant_change_bit
c_func
(paren
r_const
r_int
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|ptr
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
(paren
(paren
r_int
r_int
)paren
id|ptr
)paren
op_plus
(paren
(paren
id|nr
op_xor
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|8
)paren
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|nr
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;xi 0(%1),0x01&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;xi 0(%1),0x02&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;xi 0(%1),0x04&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;xi 0(%1),0x08&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;xi 0(%1),0x10&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;xi 0(%1),0x20&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;xi 0(%1),0x40&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;xi 0(%1),0x80&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|macro|change_bit_simple
mdefine_line|#define change_bit_simple(nr,addr) &bslash;&n;(__builtin_constant_p((nr)) ? &bslash;&n; __constant_change_bit((nr),(addr)) : &bslash;&n; __change_bit((nr),(addr)) )
multiline_comment|/*&n; * fast, non-SMP test_and_set_bit routine&n; */
r_static
r_inline
r_int
DECL|function|test_and_set_bit_simple
id|test_and_set_bit_simple
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_char
id|ch
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
op_plus
(paren
(paren
id|nr
op_xor
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|8
)paren
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|ch
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;oc 0(1,%1),0(%2)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
id|_oi_bitmap
op_plus
(paren
id|nr
op_amp
l_int|7
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|ch
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
DECL|macro|__test_and_set_bit
mdefine_line|#define __test_and_set_bit(X,Y)&t;&t;test_and_set_bit_simple(X,Y)
multiline_comment|/*&n; * fast, non-SMP test_and_clear_bit routine&n; */
r_static
r_inline
r_int
DECL|function|test_and_clear_bit_simple
id|test_and_clear_bit_simple
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_char
id|ch
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
op_plus
(paren
(paren
id|nr
op_xor
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|8
)paren
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|ch
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;nc 0(1,%1),0(%2)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
id|_ni_bitmap
op_plus
(paren
id|nr
op_amp
l_int|7
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|ch
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
DECL|macro|__test_and_clear_bit
mdefine_line|#define __test_and_clear_bit(X,Y)&t;test_and_clear_bit_simple(X,Y)
multiline_comment|/*&n; * fast, non-SMP test_and_change_bit routine&n; */
r_static
r_inline
r_int
DECL|function|test_and_change_bit_simple
id|test_and_change_bit_simple
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
id|ptr
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_char
id|ch
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
op_plus
(paren
(paren
id|nr
op_xor
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|8
)paren
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|ch
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;xc 0(1,%1),0(%2)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
id|_oi_bitmap
op_plus
(paren
id|nr
op_amp
l_int|7
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|ch
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
DECL|macro|__test_and_change_bit
mdefine_line|#define __test_and_change_bit(X,Y)&t;test_and_change_bit_simple(X,Y)
macro_line|#ifdef CONFIG_SMP
DECL|macro|set_bit
mdefine_line|#define set_bit             set_bit_cs
DECL|macro|clear_bit
mdefine_line|#define clear_bit           clear_bit_cs
DECL|macro|change_bit
mdefine_line|#define change_bit          change_bit_cs
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit    test_and_set_bit_cs
DECL|macro|test_and_clear_bit
mdefine_line|#define test_and_clear_bit  test_and_clear_bit_cs
DECL|macro|test_and_change_bit
mdefine_line|#define test_and_change_bit test_and_change_bit_cs
macro_line|#else
DECL|macro|set_bit
mdefine_line|#define set_bit             set_bit_simple
DECL|macro|clear_bit
mdefine_line|#define clear_bit           clear_bit_simple
DECL|macro|change_bit
mdefine_line|#define change_bit          change_bit_simple
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit    test_and_set_bit_simple
DECL|macro|test_and_clear_bit
mdefine_line|#define test_and_clear_bit  test_and_clear_bit_simple
DECL|macro|test_and_change_bit
mdefine_line|#define test_and_change_bit test_and_change_bit_simple
macro_line|#endif
multiline_comment|/*&n; * This routine doesn&squot;t need to be atomic.&n; */
DECL|function|__test_bit
r_static
r_inline
r_int
id|__test_bit
c_func
(paren
r_int
r_int
id|nr
comma
r_const
r_volatile
r_int
r_int
op_star
id|ptr
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_char
id|ch
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
op_plus
(paren
(paren
id|nr
op_xor
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|8
)paren
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|ch
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
r_return
(paren
id|ch
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
r_static
r_inline
r_int
DECL|function|__constant_test_bit
id|__constant_test_bit
c_func
(paren
r_int
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
(paren
id|__BITOPS_WORDSIZE
op_minus
l_int|8
)paren
)paren
op_rshift
l_int|3
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|7
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|macro|test_bit
mdefine_line|#define test_bit(nr,addr) &bslash;&n;(__builtin_constant_p((nr)) ? &bslash;&n; __constant_test_bit((nr),(addr)) : &bslash;&n; __test_bit((nr),(addr)) )
macro_line|#ifndef __s390x__
multiline_comment|/*&n; * Find-bit routines..&n; */
r_static
r_inline
r_int
DECL|function|find_first_zero_bit
id|find_first_zero_bit
c_func
(paren
r_int
r_int
op_star
id|addr
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|cmp
comma
id|count
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
id|__asm__
c_func
(paren
l_string|&quot;   lhi  %1,-1&bslash;n&quot;
l_string|&quot;   lr   %2,%3&bslash;n&quot;
l_string|&quot;   slr  %0,%0&bslash;n&quot;
l_string|&quot;   ahi  %2,31&bslash;n&quot;
l_string|&quot;   srl  %2,5&bslash;n&quot;
l_string|&quot;0: c    %1,0(%0,%4)&bslash;n&quot;
l_string|&quot;   jne  1f&bslash;n&quot;
l_string|&quot;   ahi  %0,4&bslash;n&quot;
l_string|&quot;   brct %2,0b&bslash;n&quot;
l_string|&quot;   lr   %0,%3&bslash;n&quot;
l_string|&quot;   j    4f&bslash;n&quot;
l_string|&quot;1: l    %2,0(%0,%4)&bslash;n&quot;
l_string|&quot;   sll  %0,3&bslash;n&quot;
l_string|&quot;   lhi  %1,0xff&bslash;n&quot;
l_string|&quot;   tml  %2,0xffff&bslash;n&quot;
l_string|&quot;   jno  2f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srl  %2,16&bslash;n&quot;
l_string|&quot;2: tml  %2,0x00ff&bslash;n&quot;
l_string|&quot;   jno  3f&bslash;n&quot;
l_string|&quot;   ahi  %0,8&bslash;n&quot;
l_string|&quot;   srl  %2,8&bslash;n&quot;
l_string|&quot;3: nr   %2,%1&bslash;n&quot;
l_string|&quot;   ic   %2,0(%2,%5)&bslash;n&quot;
l_string|&quot;   alr  %0,%2&bslash;n&quot;
l_string|&quot;4:&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|cmp
)paren
comma
l_string|&quot;=&amp;a&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|size
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|res
OL
id|size
)paren
ques
c_cond
id|res
suffix:colon
id|size
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|find_first_bit
id|find_first_bit
c_func
(paren
r_int
r_int
op_star
id|addr
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|cmp
comma
id|count
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
id|__asm__
c_func
(paren
l_string|&quot;   slr  %1,%1&bslash;n&quot;
l_string|&quot;   lr   %2,%3&bslash;n&quot;
l_string|&quot;   slr  %0,%0&bslash;n&quot;
l_string|&quot;   ahi  %2,31&bslash;n&quot;
l_string|&quot;   srl  %2,5&bslash;n&quot;
l_string|&quot;0: c    %1,0(%0,%4)&bslash;n&quot;
l_string|&quot;   jne  1f&bslash;n&quot;
l_string|&quot;   ahi  %0,4&bslash;n&quot;
l_string|&quot;   brct %2,0b&bslash;n&quot;
l_string|&quot;   lr   %0,%3&bslash;n&quot;
l_string|&quot;   j    4f&bslash;n&quot;
l_string|&quot;1: l    %2,0(%0,%4)&bslash;n&quot;
l_string|&quot;   sll  %0,3&bslash;n&quot;
l_string|&quot;   lhi  %1,0xff&bslash;n&quot;
l_string|&quot;   tml  %2,0xffff&bslash;n&quot;
l_string|&quot;   jnz  2f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srl  %2,16&bslash;n&quot;
l_string|&quot;2: tml  %2,0x00ff&bslash;n&quot;
l_string|&quot;   jnz  3f&bslash;n&quot;
l_string|&quot;   ahi  %0,8&bslash;n&quot;
l_string|&quot;   srl  %2,8&bslash;n&quot;
l_string|&quot;3: nr   %2,%1&bslash;n&quot;
l_string|&quot;   ic   %2,0(%2,%5)&bslash;n&quot;
l_string|&quot;   alr  %0,%2&bslash;n&quot;
l_string|&quot;4:&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|cmp
)paren
comma
l_string|&quot;=&amp;a&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|size
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_sb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|res
OL
id|size
)paren
ques
c_cond
id|res
suffix:colon
id|size
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|find_next_zero_bit
id|find_next_zero_bit
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
id|bitvec
comma
id|reg
suffix:semicolon
r_int
id|set
comma
id|bit
op_assign
id|offset
op_amp
l_int|31
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/*&n;                 * Look for zero in first word&n;                 */
id|bitvec
op_assign
(paren
op_star
id|p
)paren
op_rshift
id|bit
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   slr  %0,%0&bslash;n&quot;
l_string|&quot;   lhi  %2,0xff&bslash;n&quot;
l_string|&quot;   tml  %1,0xffff&bslash;n&quot;
l_string|&quot;   jno  0f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srl  %1,16&bslash;n&quot;
l_string|&quot;0: tml  %1,0x00ff&bslash;n&quot;
l_string|&quot;   jno  1f&bslash;n&quot;
l_string|&quot;   ahi  %0,8&bslash;n&quot;
l_string|&quot;   srl  %1,8&bslash;n&quot;
l_string|&quot;1: nr   %1,%2&bslash;n&quot;
l_string|&quot;   ic   %1,0(%1,%3)&bslash;n&quot;
l_string|&quot;   alr  %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|set
)paren
comma
l_string|&quot;+a&quot;
(paren
id|bitvec
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
OL
(paren
l_int|32
op_minus
id|bit
)paren
)paren
r_return
id|set
op_plus
id|offset
suffix:semicolon
id|offset
op_add_assign
l_int|32
op_minus
id|bit
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;         * No zero yet, search remaining full words for a zero&n;         */
id|res
op_assign
id|find_first_zero_bit
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
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
)paren
suffix:semicolon
r_return
(paren
id|offset
op_plus
id|res
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|find_next_bit
id|find_next_bit
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
id|bitvec
comma
id|reg
suffix:semicolon
r_int
id|set
comma
id|bit
op_assign
id|offset
op_amp
l_int|31
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/*&n;                 * Look for set bit in first word&n;                 */
id|bitvec
op_assign
(paren
op_star
id|p
)paren
op_rshift
id|bit
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   slr  %0,%0&bslash;n&quot;
l_string|&quot;   lhi  %2,0xff&bslash;n&quot;
l_string|&quot;   tml  %1,0xffff&bslash;n&quot;
l_string|&quot;   jnz  0f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srl  %1,16&bslash;n&quot;
l_string|&quot;0: tml  %1,0x00ff&bslash;n&quot;
l_string|&quot;   jnz  1f&bslash;n&quot;
l_string|&quot;   ahi  %0,8&bslash;n&quot;
l_string|&quot;   srl  %1,8&bslash;n&quot;
l_string|&quot;1: nr   %1,%2&bslash;n&quot;
l_string|&quot;   ic   %1,0(%1,%3)&bslash;n&quot;
l_string|&quot;   alr  %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|set
)paren
comma
l_string|&quot;+a&quot;
(paren
id|bitvec
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|_sb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
OL
(paren
l_int|32
op_minus
id|bit
)paren
)paren
r_return
id|set
op_plus
id|offset
suffix:semicolon
id|offset
op_add_assign
l_int|32
op_minus
id|bit
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;         * No set bit yet, search remaining full words for a bit&n;         */
id|res
op_assign
id|find_first_bit
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
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
)paren
suffix:semicolon
r_return
(paren
id|offset
op_plus
id|res
)paren
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
r_int
id|reg
suffix:semicolon
r_int
id|result
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   slr  %0,%0&bslash;n&quot;
l_string|&quot;   lhi  %2,0xff&bslash;n&quot;
l_string|&quot;   tml  %1,0xffff&bslash;n&quot;
l_string|&quot;   jno  0f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srl  %1,16&bslash;n&quot;
l_string|&quot;0: tml  %1,0x00ff&bslash;n&quot;
l_string|&quot;   jno  1f&bslash;n&quot;
l_string|&quot;   ahi  %0,8&bslash;n&quot;
l_string|&quot;   srl  %1,8&bslash;n&quot;
l_string|&quot;1: nr   %1,%2&bslash;n&quot;
l_string|&quot;   ic   %1,0(%1,%3)&bslash;n&quot;
l_string|&quot;   alr  %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|result
)paren
comma
l_string|&quot;+a&quot;
(paren
id|word
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * __ffs = find first bit in word. Undefined if no bit exists,&n; * so code should check against 0UL first..&n; */
DECL|function|__ffs
r_static
r_inline
r_int
r_int
id|__ffs
(paren
r_int
r_int
id|word
)paren
(brace
r_int
r_int
id|reg
comma
id|result
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   slr  %0,%0&bslash;n&quot;
l_string|&quot;   lhi  %2,0xff&bslash;n&quot;
l_string|&quot;   tml  %1,0xffff&bslash;n&quot;
l_string|&quot;   jnz  0f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srl  %1,16&bslash;n&quot;
l_string|&quot;0: tml  %1,0x00ff&bslash;n&quot;
l_string|&quot;   jnz  1f&bslash;n&quot;
l_string|&quot;   ahi  %0,8&bslash;n&quot;
l_string|&quot;   srl  %1,8&bslash;n&quot;
l_string|&quot;1: nr   %1,%2&bslash;n&quot;
l_string|&quot;   ic   %1,0(%1,%3)&bslash;n&quot;
l_string|&quot;   alr  %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|result
)paren
comma
l_string|&quot;+a&quot;
(paren
id|word
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|_sb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#else /* __s390x__ */
multiline_comment|/*&n; * Find-bit routines..&n; */
r_static
r_inline
r_int
r_int
DECL|function|find_first_zero_bit
id|find_first_zero_bit
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
)paren
(brace
r_int
r_int
id|res
comma
id|cmp
comma
id|count
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
id|__asm__
c_func
(paren
l_string|&quot;   lghi  %1,-1&bslash;n&quot;
l_string|&quot;   lgr   %2,%3&bslash;n&quot;
l_string|&quot;   slgr  %0,%0&bslash;n&quot;
l_string|&quot;   aghi  %2,63&bslash;n&quot;
l_string|&quot;   srlg  %2,%2,6&bslash;n&quot;
l_string|&quot;0: cg    %1,0(%0,%4)&bslash;n&quot;
l_string|&quot;   jne   1f&bslash;n&quot;
l_string|&quot;   aghi  %0,8&bslash;n&quot;
l_string|&quot;   brct  %2,0b&bslash;n&quot;
l_string|&quot;   lgr   %0,%3&bslash;n&quot;
l_string|&quot;   j     5f&bslash;n&quot;
l_string|&quot;1: lg    %2,0(%0,%4)&bslash;n&quot;
l_string|&quot;   sllg  %0,%0,3&bslash;n&quot;
l_string|&quot;   clr   %2,%1&bslash;n&quot;
l_string|&quot;   jne   2f&bslash;n&quot;
l_string|&quot;   aghi  %0,32&bslash;n&quot;
l_string|&quot;   srlg  %2,%2,32&bslash;n&quot;
l_string|&quot;2: lghi  %1,0xff&bslash;n&quot;
l_string|&quot;   tmll  %2,0xffff&bslash;n&quot;
l_string|&quot;   jno   3f&bslash;n&quot;
l_string|&quot;   aghi  %0,16&bslash;n&quot;
l_string|&quot;   srl   %2,16&bslash;n&quot;
l_string|&quot;3: tmll  %2,0x00ff&bslash;n&quot;
l_string|&quot;   jno   4f&bslash;n&quot;
l_string|&quot;   aghi  %0,8&bslash;n&quot;
l_string|&quot;   srl   %2,8&bslash;n&quot;
l_string|&quot;4: ngr   %2,%1&bslash;n&quot;
l_string|&quot;   ic    %2,0(%2,%5)&bslash;n&quot;
l_string|&quot;   algr  %0,%2&bslash;n&quot;
l_string|&quot;5:&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|cmp
)paren
comma
l_string|&quot;=&amp;a&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|size
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|res
OL
id|size
)paren
ques
c_cond
id|res
suffix:colon
id|size
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|find_first_bit
id|find_first_bit
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
)paren
(brace
r_int
r_int
id|res
comma
id|cmp
comma
id|count
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
id|__asm__
c_func
(paren
l_string|&quot;   slgr  %1,%1&bslash;n&quot;
l_string|&quot;   lgr   %2,%3&bslash;n&quot;
l_string|&quot;   slgr  %0,%0&bslash;n&quot;
l_string|&quot;   aghi  %2,63&bslash;n&quot;
l_string|&quot;   srlg  %2,%2,6&bslash;n&quot;
l_string|&quot;0: cg    %1,0(%0,%4)&bslash;n&quot;
l_string|&quot;   jne   1f&bslash;n&quot;
l_string|&quot;   aghi  %0,8&bslash;n&quot;
l_string|&quot;   brct  %2,0b&bslash;n&quot;
l_string|&quot;   lgr   %0,%3&bslash;n&quot;
l_string|&quot;   j     5f&bslash;n&quot;
l_string|&quot;1: lg    %2,0(%0,%4)&bslash;n&quot;
l_string|&quot;   sllg  %0,%0,3&bslash;n&quot;
l_string|&quot;   clr   %2,%1&bslash;n&quot;
l_string|&quot;   jne   2f&bslash;n&quot;
l_string|&quot;   aghi  %0,32&bslash;n&quot;
l_string|&quot;   srlg  %2,%2,32&bslash;n&quot;
l_string|&quot;2: lghi  %1,0xff&bslash;n&quot;
l_string|&quot;   tmll  %2,0xffff&bslash;n&quot;
l_string|&quot;   jnz   3f&bslash;n&quot;
l_string|&quot;   aghi  %0,16&bslash;n&quot;
l_string|&quot;   srl   %2,16&bslash;n&quot;
l_string|&quot;3: tmll  %2,0x00ff&bslash;n&quot;
l_string|&quot;   jnz   4f&bslash;n&quot;
l_string|&quot;   aghi  %0,8&bslash;n&quot;
l_string|&quot;   srl   %2,8&bslash;n&quot;
l_string|&quot;4: ngr   %2,%1&bslash;n&quot;
l_string|&quot;   ic    %2,0(%2,%5)&bslash;n&quot;
l_string|&quot;   algr  %0,%2&bslash;n&quot;
l_string|&quot;5:&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|cmp
)paren
comma
l_string|&quot;=&amp;a&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|size
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_sb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|res
OL
id|size
)paren
ques
c_cond
id|res
suffix:colon
id|size
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|find_next_zero_bit
id|find_next_zero_bit
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
l_int|6
)paren
suffix:semicolon
r_int
r_int
id|bitvec
comma
id|reg
suffix:semicolon
r_int
r_int
id|set
comma
id|bit
op_assign
id|offset
op_amp
l_int|63
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/*&n;                 * Look for zero in first word&n;                 */
id|bitvec
op_assign
(paren
op_star
id|p
)paren
op_rshift
id|bit
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   lhi  %2,-1&bslash;n&quot;
l_string|&quot;   slgr %0,%0&bslash;n&quot;
l_string|&quot;   clr  %1,%2&bslash;n&quot;
l_string|&quot;   jne  0f&bslash;n&quot;
l_string|&quot;   aghi %0,32&bslash;n&quot;
l_string|&quot;   srlg %1,%1,32&bslash;n&quot;
l_string|&quot;0: lghi %2,0xff&bslash;n&quot;
l_string|&quot;   tmll %1,0xffff&bslash;n&quot;
l_string|&quot;   jno  1f&bslash;n&quot;
l_string|&quot;   aghi %0,16&bslash;n&quot;
l_string|&quot;   srlg %1,%1,16&bslash;n&quot;
l_string|&quot;1: tmll %1,0x00ff&bslash;n&quot;
l_string|&quot;   jno  2f&bslash;n&quot;
l_string|&quot;   aghi %0,8&bslash;n&quot;
l_string|&quot;   srlg %1,%1,8&bslash;n&quot;
l_string|&quot;2: ngr  %1,%2&bslash;n&quot;
l_string|&quot;   ic   %1,0(%1,%3)&bslash;n&quot;
l_string|&quot;   algr %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|set
)paren
comma
l_string|&quot;+a&quot;
(paren
id|bitvec
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
OL
(paren
l_int|64
op_minus
id|bit
)paren
)paren
r_return
id|set
op_plus
id|offset
suffix:semicolon
id|offset
op_add_assign
l_int|64
op_minus
id|bit
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;         * No zero yet, search remaining full words for a zero&n;         */
id|res
op_assign
id|find_first_zero_bit
(paren
id|p
comma
id|size
op_minus
l_int|64
op_star
(paren
id|p
op_minus
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
)paren
suffix:semicolon
r_return
(paren
id|offset
op_plus
id|res
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|find_next_bit
id|find_next_bit
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
l_int|6
)paren
suffix:semicolon
r_int
r_int
id|bitvec
comma
id|reg
suffix:semicolon
r_int
r_int
id|set
comma
id|bit
op_assign
id|offset
op_amp
l_int|63
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/*&n;                 * Look for zero in first word&n;                 */
id|bitvec
op_assign
(paren
op_star
id|p
)paren
op_rshift
id|bit
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   slgr %0,%0&bslash;n&quot;
l_string|&quot;   ltr  %1,%1&bslash;n&quot;
l_string|&quot;   jnz  0f&bslash;n&quot;
l_string|&quot;   aghi %0,32&bslash;n&quot;
l_string|&quot;   srlg %1,%1,32&bslash;n&quot;
l_string|&quot;0: lghi %2,0xff&bslash;n&quot;
l_string|&quot;   tmll %1,0xffff&bslash;n&quot;
l_string|&quot;   jnz  1f&bslash;n&quot;
l_string|&quot;   aghi %0,16&bslash;n&quot;
l_string|&quot;   srlg %1,%1,16&bslash;n&quot;
l_string|&quot;1: tmll %1,0x00ff&bslash;n&quot;
l_string|&quot;   jnz  2f&bslash;n&quot;
l_string|&quot;   aghi %0,8&bslash;n&quot;
l_string|&quot;   srlg %1,%1,8&bslash;n&quot;
l_string|&quot;2: ngr  %1,%2&bslash;n&quot;
l_string|&quot;   ic   %1,0(%1,%3)&bslash;n&quot;
l_string|&quot;   algr %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|set
)paren
comma
l_string|&quot;+a&quot;
(paren
id|bitvec
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|_sb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
OL
(paren
l_int|64
op_minus
id|bit
)paren
)paren
r_return
id|set
op_plus
id|offset
suffix:semicolon
id|offset
op_add_assign
l_int|64
op_minus
id|bit
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;         * No set bit yet, search remaining full words for a bit&n;         */
id|res
op_assign
id|find_first_bit
(paren
id|p
comma
id|size
op_minus
l_int|64
op_star
(paren
id|p
op_minus
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
)paren
suffix:semicolon
r_return
(paren
id|offset
op_plus
id|res
)paren
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
r_int
id|reg
comma
id|result
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   lhi  %2,-1&bslash;n&quot;
l_string|&quot;   slgr %0,%0&bslash;n&quot;
l_string|&quot;   clr  %1,%2&bslash;n&quot;
l_string|&quot;   jne  0f&bslash;n&quot;
l_string|&quot;   aghi %0,32&bslash;n&quot;
l_string|&quot;   srlg %1,%1,32&bslash;n&quot;
l_string|&quot;0: lghi %2,0xff&bslash;n&quot;
l_string|&quot;   tmll %1,0xffff&bslash;n&quot;
l_string|&quot;   jno  1f&bslash;n&quot;
l_string|&quot;   aghi %0,16&bslash;n&quot;
l_string|&quot;   srlg %1,%1,16&bslash;n&quot;
l_string|&quot;1: tmll %1,0x00ff&bslash;n&quot;
l_string|&quot;   jno  2f&bslash;n&quot;
l_string|&quot;   aghi %0,8&bslash;n&quot;
l_string|&quot;   srlg %1,%1,8&bslash;n&quot;
l_string|&quot;2: ngr  %1,%2&bslash;n&quot;
l_string|&quot;   ic   %1,0(%1,%3)&bslash;n&quot;
l_string|&quot;   algr %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|result
)paren
comma
l_string|&quot;+a&quot;
(paren
id|word
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * __ffs = find first bit in word. Undefined if no bit exists,&n; * so code should check against 0UL first..&n; */
DECL|function|__ffs
r_static
r_inline
r_int
r_int
id|__ffs
(paren
r_int
r_int
id|word
)paren
(brace
r_int
r_int
id|reg
comma
id|result
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   slgr %0,%0&bslash;n&quot;
l_string|&quot;   ltr  %1,%1&bslash;n&quot;
l_string|&quot;   jnz  0f&bslash;n&quot;
l_string|&quot;   aghi %0,32&bslash;n&quot;
l_string|&quot;   srlg %1,%1,32&bslash;n&quot;
l_string|&quot;0: lghi %2,0xff&bslash;n&quot;
l_string|&quot;   tmll %1,0xffff&bslash;n&quot;
l_string|&quot;   jnz  1f&bslash;n&quot;
l_string|&quot;   aghi %0,16&bslash;n&quot;
l_string|&quot;   srlg %1,%1,16&bslash;n&quot;
l_string|&quot;1: tmll %1,0x00ff&bslash;n&quot;
l_string|&quot;   jnz  2f&bslash;n&quot;
l_string|&quot;   aghi %0,8&bslash;n&quot;
l_string|&quot;   srlg %1,%1,8&bslash;n&quot;
l_string|&quot;2: ngr  %1,%2&bslash;n&quot;
l_string|&quot;   ic   %1,0(%1,%3)&bslash;n&quot;
l_string|&quot;   algr %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|result
)paren
comma
l_string|&quot;+a&quot;
(paren
id|word
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|_sb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#endif /* __s390x__ */
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
r_return
id|find_first_bit
c_func
(paren
id|b
comma
l_int|140
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ffs: find first bit set. This is defined the same way as&n; * the libc and compiler builtin ffs routines, therefore&n; * differs in spirit from the above ffz (man ffs).&n; */
DECL|function|ffs
r_extern
r_inline
r_int
id|ffs
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
id|x
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;    tml  %1,0xffff&bslash;n&quot;
l_string|&quot;    jnz  0f&bslash;n&quot;
l_string|&quot;    srl  %1,16&bslash;n&quot;
l_string|&quot;    ahi  %0,16&bslash;n&quot;
l_string|&quot;0:  tml  %1,0x00ff&bslash;n&quot;
l_string|&quot;    jnz  1f&bslash;n&quot;
l_string|&quot;    srl  %1,8&bslash;n&quot;
l_string|&quot;    ahi  %0,8&bslash;n&quot;
l_string|&quot;1:  tml  %1,0x000f&bslash;n&quot;
l_string|&quot;    jnz  2f&bslash;n&quot;
l_string|&quot;    srl  %1,4&bslash;n&quot;
l_string|&quot;    ahi  %0,4&bslash;n&quot;
l_string|&quot;2:  tml  %1,0x0003&bslash;n&quot;
l_string|&quot;    jnz  3f&bslash;n&quot;
l_string|&quot;    srl  %1,2&bslash;n&quot;
l_string|&quot;    ahi  %0,2&bslash;n&quot;
l_string|&quot;3:  tml  %1,0x0001&bslash;n&quot;
l_string|&quot;    jnz  4f&bslash;n&quot;
l_string|&quot;    ahi  %0,1&bslash;n&quot;
l_string|&quot;4:&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|r
)paren
comma
l_string|&quot;+d&quot;
(paren
id|x
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; * fls: find last bit set.&n; */
DECL|function|fls
r_extern
id|__inline__
r_int
id|fls
c_func
(paren
r_int
id|x
)paren
(brace
r_int
id|r
op_assign
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;    tmh  %1,0xffff&bslash;n&quot;
l_string|&quot;    jz   0f&bslash;n&quot;
l_string|&quot;    sll  %1,16&bslash;n&quot;
l_string|&quot;    ahi  %0,-16&bslash;n&quot;
l_string|&quot;0:  tmh  %1,0xff00&bslash;n&quot;
l_string|&quot;    jz   1f&bslash;n&quot;
l_string|&quot;    sll  %1,8&bslash;n&quot;
l_string|&quot;    ahi  %0,-8&bslash;n&quot;
l_string|&quot;1:  tmh  %1,0xf000&bslash;n&quot;
l_string|&quot;    jz   2f&bslash;n&quot;
l_string|&quot;    sll  %1,4&bslash;n&quot;
l_string|&quot;    ahi  %0,-4&bslash;n&quot;
l_string|&quot;2:  tmh  %1,0xc000&bslash;n&quot;
l_string|&quot;    jz   3f&bslash;n&quot;
l_string|&quot;    sll  %1,2&bslash;n&quot;
l_string|&quot;    ahi  %0,-2&bslash;n&quot;
l_string|&quot;3:  tmh  %1,0x8000&bslash;n&quot;
l_string|&quot;    jz   4f&bslash;n&quot;
l_string|&quot;    ahi  %0,-1&bslash;n&quot;
l_string|&quot;4:&quot;
suffix:colon
l_string|&quot;+d&quot;
(paren
id|r
)paren
comma
l_string|&quot;+d&quot;
(paren
id|x
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|macro|hweight64
mdefine_line|#define hweight64(x)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __x = (x);&t;&t;&t;&t;&bslash;&n;&t;unsigned int __w;&t;&t;&t;&t;&t;&bslash;&n;&t;__w = generic_hweight32((unsigned int) __x);&t;&t;&bslash;&n;&t;__w += generic_hweight32((unsigned int) (__x&gt;&gt;32));&t;&bslash;&n;&t;__w;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * ATTENTION: intel byte ordering convention for ext2 and minix !!&n; * bit 0 is the LSB of addr; bit 31 is the MSB of addr;&n; * bit 32 is the LSB of (addr+4).&n; * That combined with the little endian byte order of Intel gives the&n; * following bit order in memory:&n; *    07 06 05 04 03 02 01 00 15 14 13 12 11 10 09 08 &bslash;&n; *    23 22 21 20 19 18 17 16 31 30 29 28 27 26 25 24&n; */
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr, addr)       &bslash;&n;&t;test_and_set_bit((nr)^(__BITOPS_WORDSIZE - 8), (unsigned long *)addr)
DECL|macro|ext2_set_bit_atomic
mdefine_line|#define ext2_set_bit_atomic(lock, nr, addr)       &bslash;&n;&t;test_and_set_bit((nr)^(__BITOPS_WORDSIZE - 8), (unsigned long *)addr)
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr, addr)     &bslash;&n;&t;test_and_clear_bit((nr)^(__BITOPS_WORDSIZE - 8), (unsigned long *)addr)
DECL|macro|ext2_clear_bit_atomic
mdefine_line|#define ext2_clear_bit_atomic(lock, nr, addr)     &bslash;&n;&t;test_and_clear_bit((nr)^(__BITOPS_WORDSIZE - 8), (unsigned long *)addr)
DECL|macro|ext2_test_bit
mdefine_line|#define ext2_test_bit(nr, addr)      &bslash;&n;&t;test_bit((nr)^(__BITOPS_WORDSIZE - 8), (unsigned long *)addr)
macro_line|#ifndef __s390x__
r_static
r_inline
r_int
DECL|function|ext2_find_first_zero_bit
id|ext2_find_first_zero_bit
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|cmp
comma
id|count
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
id|__asm__
c_func
(paren
l_string|&quot;   lhi  %1,-1&bslash;n&quot;
l_string|&quot;   lr   %2,%3&bslash;n&quot;
l_string|&quot;   ahi  %2,31&bslash;n&quot;
l_string|&quot;   srl  %2,5&bslash;n&quot;
l_string|&quot;   slr  %0,%0&bslash;n&quot;
l_string|&quot;0: cl   %1,0(%0,%4)&bslash;n&quot;
l_string|&quot;   jne  1f&bslash;n&quot;
l_string|&quot;   ahi  %0,4&bslash;n&quot;
l_string|&quot;   brct %2,0b&bslash;n&quot;
l_string|&quot;   lr   %0,%3&bslash;n&quot;
l_string|&quot;   j    4f&bslash;n&quot;
l_string|&quot;1: l    %2,0(%0,%4)&bslash;n&quot;
l_string|&quot;   sll  %0,3&bslash;n&quot;
l_string|&quot;   ahi  %0,24&bslash;n&quot;
l_string|&quot;   lhi  %1,0xff&bslash;n&quot;
l_string|&quot;   tmh  %2,0xffff&bslash;n&quot;
l_string|&quot;   jo   2f&bslash;n&quot;
l_string|&quot;   ahi  %0,-16&bslash;n&quot;
l_string|&quot;   srl  %2,16&bslash;n&quot;
l_string|&quot;2: tml  %2,0xff00&bslash;n&quot;
l_string|&quot;   jo   3f&bslash;n&quot;
l_string|&quot;   ahi  %0,-8&bslash;n&quot;
l_string|&quot;   srl  %2,8&bslash;n&quot;
l_string|&quot;3: nr   %2,%1&bslash;n&quot;
l_string|&quot;   ic   %2,0(%2,%5)&bslash;n&quot;
l_string|&quot;   alr  %0,%2&bslash;n&quot;
l_string|&quot;4:&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|cmp
)paren
comma
l_string|&quot;=&amp;a&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|size
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|res
OL
id|size
)paren
ques
c_cond
id|res
suffix:colon
id|size
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|ext2_find_next_zero_bit
id|ext2_find_next_zero_bit
c_func
(paren
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
r_int
r_int
op_star
id|addr
op_assign
id|vaddr
suffix:semicolon
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
id|word
comma
id|reg
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
id|__asm__
c_func
(paren
l_string|&quot;   ic   %0,0(%1)&bslash;n&quot;
l_string|&quot;   icm  %0,2,1(%1)&bslash;n&quot;
l_string|&quot;   icm  %0,4,2(%1)&bslash;n&quot;
l_string|&quot;   icm  %0,8,3(%1)&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
id|word
op_rshift_assign
id|bit
suffix:semicolon
id|res
op_assign
id|bit
suffix:semicolon
multiline_comment|/* Look for zero in first longword */
id|__asm__
c_func
(paren
l_string|&quot;   lhi  %2,0xff&bslash;n&quot;
l_string|&quot;   tml  %1,0xffff&bslash;n&quot;
l_string|&quot;   jno  0f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srl  %1,16&bslash;n&quot;
l_string|&quot;0: tml  %1,0x00ff&bslash;n&quot;
l_string|&quot;   jno  1f&bslash;n&quot;
l_string|&quot;   ahi  %0,8&bslash;n&quot;
l_string|&quot;   srl  %1,8&bslash;n&quot;
l_string|&quot;1: nr   %1,%2&bslash;n&quot;
l_string|&quot;   ic   %1,0(%1,%3)&bslash;n&quot;
l_string|&quot;   alr  %0,%1&quot;
suffix:colon
l_string|&quot;+&amp;d&quot;
(paren
id|res
)paren
comma
l_string|&quot;+&amp;a&quot;
(paren
id|word
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
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
macro_line|#else /* __s390x__ */
r_static
r_inline
r_int
r_int
DECL|function|ext2_find_first_zero_bit
id|ext2_find_first_zero_bit
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|res
comma
id|cmp
comma
id|count
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
id|__asm__
c_func
(paren
l_string|&quot;   lghi  %1,-1&bslash;n&quot;
l_string|&quot;   lgr   %2,%3&bslash;n&quot;
l_string|&quot;   aghi  %2,63&bslash;n&quot;
l_string|&quot;   srlg  %2,%2,6&bslash;n&quot;
l_string|&quot;   slgr  %0,%0&bslash;n&quot;
l_string|&quot;0: clg   %1,0(%0,%4)&bslash;n&quot;
l_string|&quot;   jne   1f&bslash;n&quot;
l_string|&quot;   aghi  %0,8&bslash;n&quot;
l_string|&quot;   brct  %2,0b&bslash;n&quot;
l_string|&quot;   lgr   %0,%3&bslash;n&quot;
l_string|&quot;   j     5f&bslash;n&quot;
l_string|&quot;1: cl    %1,0(%0,%4)&bslash;n&quot;
l_string|&quot;   jne   2f&bslash;n&quot;
l_string|&quot;   aghi  %0,4&bslash;n&quot;
l_string|&quot;2: l     %2,0(%0,%4)&bslash;n&quot;
l_string|&quot;   sllg  %0,%0,3&bslash;n&quot;
l_string|&quot;   aghi  %0,24&bslash;n&quot;
l_string|&quot;   lghi  %1,0xff&bslash;n&quot;
l_string|&quot;   tmlh  %2,0xffff&bslash;n&quot;
l_string|&quot;   jo    3f&bslash;n&quot;
l_string|&quot;   aghi  %0,-16&bslash;n&quot;
l_string|&quot;   srl   %2,16&bslash;n&quot;
l_string|&quot;3: tmll  %2,0xff00&bslash;n&quot;
l_string|&quot;   jo    4f&bslash;n&quot;
l_string|&quot;   aghi  %0,-8&bslash;n&quot;
l_string|&quot;   srl   %2,8&bslash;n&quot;
l_string|&quot;4: ngr   %2,%1&bslash;n&quot;
l_string|&quot;   ic    %2,0(%2,%5)&bslash;n&quot;
l_string|&quot;   algr  %0,%2&bslash;n&quot;
l_string|&quot;5:&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|cmp
)paren
comma
l_string|&quot;=&amp;a&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|size
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|res
OL
id|size
)paren
ques
c_cond
id|res
suffix:colon
id|size
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|ext2_find_next_zero_bit
id|ext2_find_next_zero_bit
c_func
(paren
r_void
op_star
id|vaddr
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
id|addr
op_assign
id|vaddr
suffix:semicolon
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
l_int|6
)paren
suffix:semicolon
r_int
r_int
id|word
comma
id|reg
suffix:semicolon
r_int
r_int
id|bit
op_assign
id|offset
op_amp
l_int|63UL
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
id|__asm__
c_func
(paren
l_string|&quot;   lrvg %0,%1&quot;
multiline_comment|/* load reversed, neat instruction */
suffix:colon
l_string|&quot;=a&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|word
op_rshift_assign
id|bit
suffix:semicolon
id|res
op_assign
id|bit
suffix:semicolon
multiline_comment|/* Look for zero in first 8 byte word */
id|__asm__
c_func
(paren
l_string|&quot;   lghi %2,0xff&bslash;n&quot;
l_string|&quot;   tmll %1,0xffff&bslash;n&quot;
l_string|&quot;   jno  2f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srlg %1,%1,16&bslash;n&quot;
l_string|&quot;0: tmll %1,0xffff&bslash;n&quot;
l_string|&quot;   jno  2f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srlg %1,%1,16&bslash;n&quot;
l_string|&quot;1: tmll %1,0xffff&bslash;n&quot;
l_string|&quot;   jno  2f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srl  %1,16&bslash;n&quot;
l_string|&quot;2: tmll %1,0x00ff&bslash;n&quot;
l_string|&quot;   jno  3f&bslash;n&quot;
l_string|&quot;   ahi  %0,8&bslash;n&quot;
l_string|&quot;   srl  %1,8&bslash;n&quot;
l_string|&quot;3: ngr  %1,%2&bslash;n&quot;
l_string|&quot;   ic   %1,0(%1,%3)&bslash;n&quot;
l_string|&quot;   alr  %0,%1&quot;
suffix:colon
l_string|&quot;+&amp;d&quot;
(paren
id|res
)paren
comma
l_string|&quot;+a&quot;
(paren
id|word
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|64
)paren
r_return
(paren
id|p
op_minus
id|addr
)paren
op_star
l_int|64
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
l_int|64
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
l_int|64
op_plus
id|res
suffix:semicolon
)brace
macro_line|#endif /* __s390x__ */
multiline_comment|/* Bitmap functions for the minix filesystem.  */
multiline_comment|/* FIXME !!! */
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _S390_BITOPS_H */
eof
