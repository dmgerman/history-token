multiline_comment|/*&n; * Copyright 1995, Russell King.&n; * Various bits and pieces copyrights include:&n; *  Linus Torvalds (test_bit).&n; * Big endian support: Copyright 2001, Nicolas Pitre&n; *  reworked by rmk.&n; *&n; * bit 0 is the LSB of addr; bit 32 is the LSB of (addr+1).&n; *&n; * Please note that the code in this file should never be included&n; * from user space.  Many of these are not implemented in assembler&n; * since they would be too costly.  Also, they require priviledged&n; * instructions (which are not available from user mode) to ensure&n; * that they are atomic.&n; */
macro_line|#ifndef __ASM_ARM_BITOPS_H
DECL|macro|__ASM_ARM_BITOPS_H
mdefine_line|#define __ASM_ARM_BITOPS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;do { } while (0)
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;do { } while (0)
multiline_comment|/*&n; * These functions are the basis of our bit ops.&n; * First, the atomic bitops.&n; *&n; * The endian issue for these functions is handled by the macros below.&n; */
r_static
r_inline
r_void
DECL|function|____atomic_set_bit_mask
id|____atomic_set_bit_mask
c_func
(paren
r_int
r_int
id|mask
comma
r_volatile
r_int
r_char
op_star
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|p
op_or_assign
id|mask
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|____atomic_clear_bit_mask
id|____atomic_clear_bit_mask
c_func
(paren
r_int
r_int
id|mask
comma
r_volatile
r_int
r_char
op_star
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|p
op_and_assign
op_complement
id|mask
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|____atomic_change_bit_mask
id|____atomic_change_bit_mask
c_func
(paren
r_int
r_int
id|mask
comma
r_volatile
r_int
r_char
op_star
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|p
op_xor_assign
id|mask
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|____atomic_test_and_set_bit_mask
id|____atomic_test_and_set_bit_mask
c_func
(paren
r_int
r_int
id|mask
comma
r_volatile
r_int
r_char
op_star
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|res
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|res
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|res
op_or
id|mask
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|res
op_amp
id|mask
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|____atomic_test_and_clear_bit_mask
id|____atomic_test_and_clear_bit_mask
c_func
(paren
r_int
r_int
id|mask
comma
r_volatile
r_int
r_char
op_star
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|res
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|res
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|res
op_amp
op_complement
id|mask
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|res
op_amp
id|mask
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|____atomic_test_and_change_bit_mask
id|____atomic_test_and_change_bit_mask
c_func
(paren
r_int
r_int
id|mask
comma
r_volatile
r_int
r_char
op_star
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|res
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|res
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|res
op_xor
id|mask
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|res
op_amp
id|mask
suffix:semicolon
)brace
multiline_comment|/*&n; * Now the non-atomic variants.  We let the compiler handle all optimisations&n; * for these.&n; */
DECL|function|____nonatomic_set_bit
r_static
r_inline
r_void
id|____nonatomic_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
(brace
(paren
(paren
r_int
r_char
op_star
)paren
id|p
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
op_or_assign
(paren
l_int|1U
op_lshift
(paren
id|nr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
)brace
DECL|function|____nonatomic_clear_bit
r_static
r_inline
r_void
id|____nonatomic_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
(brace
(paren
(paren
r_int
r_char
op_star
)paren
id|p
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
op_and_assign
op_complement
(paren
l_int|1U
op_lshift
(paren
id|nr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
)brace
DECL|function|____nonatomic_change_bit
r_static
r_inline
r_void
id|____nonatomic_change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
(brace
(paren
(paren
r_int
r_char
op_star
)paren
id|p
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
op_xor_assign
(paren
l_int|1U
op_lshift
(paren
id|nr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
)brace
DECL|function|____nonatomic_test_and_set_bit
r_static
r_inline
r_int
id|____nonatomic_test_and_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
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
l_int|7
)paren
suffix:semicolon
r_int
r_int
id|oldval
suffix:semicolon
id|oldval
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|p
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
suffix:semicolon
(paren
(paren
r_int
r_char
op_star
)paren
id|p
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
op_assign
id|oldval
op_or
id|mask
suffix:semicolon
r_return
id|oldval
op_amp
id|mask
suffix:semicolon
)brace
DECL|function|____nonatomic_test_and_clear_bit
r_static
r_inline
r_int
id|____nonatomic_test_and_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
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
l_int|7
)paren
suffix:semicolon
r_int
r_int
id|oldval
suffix:semicolon
id|oldval
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|p
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
suffix:semicolon
(paren
(paren
r_int
r_char
op_star
)paren
id|p
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
op_assign
id|oldval
op_amp
op_complement
id|mask
suffix:semicolon
r_return
id|oldval
op_amp
id|mask
suffix:semicolon
)brace
DECL|function|____nonatomic_test_and_change_bit
r_static
r_inline
r_int
id|____nonatomic_test_and_change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
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
l_int|7
)paren
suffix:semicolon
r_int
r_int
id|oldval
suffix:semicolon
id|oldval
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|p
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
suffix:semicolon
(paren
(paren
r_int
r_char
op_star
)paren
id|p
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
op_assign
id|oldval
op_xor
id|mask
suffix:semicolon
r_return
id|oldval
op_amp
id|mask
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine doesn&squot;t need to be atomic.&n; */
DECL|function|____test_bit
r_static
r_inline
r_int
id|____test_bit
c_func
(paren
r_int
id|nr
comma
r_const
r_void
op_star
id|p
)paren
(brace
r_return
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|p
)paren
(braket
id|nr
op_rshift
l_int|3
)braket
op_amp
(paren
l_int|1U
op_lshift
(paren
id|nr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  A note about Endian-ness.&n; *  -------------------------&n; *&n; * When the ARM is put into big endian mode via CR15, the processor&n; * merely swaps the order of bytes within words, thus:&n; *&n; *          ------------ physical data bus bits -----------&n; *          D31 ... D24  D23 ... D16  D15 ... D8  D7 ... D0&n; * little     byte 3       byte 2       byte 1      byte 0&n; * big        byte 0       byte 1       byte 2      byte 3&n; *&n; * This means that reading a 32-bit word at address 0 returns the same&n; * value irrespective of the endian mode bit.&n; *&n; * Peripheral devices should be connected with the data bus reversed in&n; * &quot;Big Endian&quot; mode.  ARM Application Note 61 is applicable, and is&n; * available from http://www.arm.com/.&n; *&n; * The following assumes that the data bus connectivity for big endian&n; * mode has been followed.&n; *&n; * Note that bit 0 is defined to be 32-bit word bit 0, not byte 0 bit 0.&n; */
multiline_comment|/*&n; * Little endian assembly bitops.  nr = 0 -&gt; byte 0 bit 0.&n; */
r_extern
r_void
id|_set_bit_le
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|_clear_bit_le
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|_change_bit_le
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|_test_and_set_bit_le
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|_test_and_clear_bit_le
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|_test_and_change_bit_le
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|_find_first_zero_bit_le
c_func
(paren
r_void
op_star
id|p
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|_find_next_zero_bit_le
c_func
(paren
r_void
op_star
id|p
comma
r_int
id|size
comma
r_int
id|offset
)paren
suffix:semicolon
multiline_comment|/*&n; * Big endian assembly bitops.  nr = 0 -&gt; byte 3 bit 0.&n; */
r_extern
r_void
id|_set_bit_be
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|_clear_bit_be
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|_change_bit_be
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|_test_and_set_bit_be
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|_test_and_clear_bit_be
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|_test_and_change_bit_be
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|_find_first_zero_bit_be
c_func
(paren
r_void
op_star
id|p
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|_find_next_zero_bit_be
c_func
(paren
r_void
op_star
id|p
comma
r_int
id|size
comma
r_int
id|offset
)paren
suffix:semicolon
multiline_comment|/*&n; * The __* form of bitops are non-atomic and may be reordered.&n; */
DECL|macro|ATOMIC_BITOP_LE
mdefine_line|#define&t;ATOMIC_BITOP_LE(name,nr,p)&t;&t;&bslash;&n;&t;(__builtin_constant_p(nr) ?&t;&t;&bslash;&n;&t; ____atomic_##name##_mask(1 &lt;&lt; ((nr) &amp; 7), &bslash;&n;&t;&t;&t;((unsigned char *)(p)) + ((nr) &gt;&gt; 3)) : &bslash;&n;&t; _##name##_le(nr,p))
DECL|macro|ATOMIC_BITOP_BE
mdefine_line|#define&t;ATOMIC_BITOP_BE(name,nr,p)&t;&t;&bslash;&n;&t;(__builtin_constant_p(nr) ?&t;&t;&bslash;&n;&t; ____atomic_##name##_mask(1 &lt;&lt; ((nr) &amp; 7), &bslash;&n;&t;&t;&t;((unsigned char *)(p)) + (((nr) &gt;&gt; 3) ^ 3)) : &bslash;&n;&t; _##name##_be(nr,p))
DECL|macro|NONATOMIC_BITOP_LE
mdefine_line|#define NONATOMIC_BITOP_LE(name,nr,p)&t;&bslash;&n;&t;(____nonatomic_##name(nr, p))
DECL|macro|NONATOMIC_BITOP_BE
mdefine_line|#define NONATOMIC_BITOP_BE(name,nr,p)&t;&bslash;&n;&t;(____nonatomic_##name(nr ^ 0x18, p))
macro_line|#ifndef __ARMEB__
multiline_comment|/*&n; * These are the little endian, atomic definitions.&n; */
DECL|macro|set_bit
mdefine_line|#define set_bit(nr,p)&t;&t;&t;ATOMIC_BITOP_LE(set_bit,nr,p)
DECL|macro|clear_bit
mdefine_line|#define clear_bit(nr,p)&t;&t;&t;ATOMIC_BITOP_LE(clear_bit,nr,p)
DECL|macro|change_bit
mdefine_line|#define change_bit(nr,p)&t;&t;ATOMIC_BITOP_LE(change_bit,nr,p)
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit(nr,p)&t;&t;ATOMIC_BITOP_LE(test_and_set_bit,nr,p)
DECL|macro|test_and_clear_bit
mdefine_line|#define test_and_clear_bit(nr,p)&t;ATOMIC_BITOP_LE(test_and_clear_bit,nr,p)
DECL|macro|test_and_change_bit
mdefine_line|#define test_and_change_bit(nr,p)&t;ATOMIC_BITOP_LE(test_and_change_bit,nr,p)
DECL|macro|test_bit
mdefine_line|#define test_bit(nr,p)&t;&t;&t;____test_bit(nr,p)
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(p,sz)&t;_find_first_zero_bit_le(p,sz)
DECL|macro|find_next_zero_bit
mdefine_line|#define find_next_zero_bit(p,sz,off)&t;_find_next_zero_bit_le(p,sz,off)
multiline_comment|/*&n; * These are the little endian, non-atomic definitions.&n; */
DECL|macro|__set_bit
mdefine_line|#define __set_bit(nr,p)&t;&t;&t;NONATOMIC_BITOP_LE(set_bit,nr,p)
DECL|macro|__clear_bit
mdefine_line|#define __clear_bit(nr,p)&t;&t;NONATOMIC_BITOP_LE(clear_bit,nr,p)
DECL|macro|__change_bit
mdefine_line|#define __change_bit(nr,p)&t;&t;NONATOMIC_BITOP_LE(change_bit,nr,p)
DECL|macro|__test_and_set_bit
mdefine_line|#define __test_and_set_bit(nr,p)&t;NONATOMIC_BITOP_LE(test_and_set_bit,nr,p)
DECL|macro|__test_and_clear_bit
mdefine_line|#define __test_and_clear_bit(nr,p)&t;NONATOMIC_BITOP_LE(test_and_clear_bit,nr,p)
DECL|macro|__test_and_change_bit
mdefine_line|#define __test_and_change_bit(nr,p)&t;NONATOMIC_BITOP_LE(test_and_change_bit,nr,p)
DECL|macro|__test_bit
mdefine_line|#define __test_bit(nr,p)&t;&t;____test_bit(nr,p)
macro_line|#else
multiline_comment|/*&n; * These are the little endian, atomic definitions.&n; */
DECL|macro|set_bit
mdefine_line|#define set_bit(nr,p)&t;&t;&t;ATOMIC_BITOP_BE(set_bit,nr,p)
DECL|macro|clear_bit
mdefine_line|#define clear_bit(nr,p)&t;&t;&t;ATOMIC_BITOP_BE(clear_bit,nr,p)
DECL|macro|change_bit
mdefine_line|#define change_bit(nr,p)&t;&t;ATOMIC_BITOP_BE(change_bit,nr,p)
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit(nr,p)&t;&t;ATOMIC_BITOP_BE(test_and_set_bit,nr,p)
DECL|macro|test_and_clear_bit
mdefine_line|#define test_and_clear_bit(nr,p)&t;ATOMIC_BITOP_BE(test_and_clear_bit,nr,p)
DECL|macro|test_and_change_bit
mdefine_line|#define test_and_change_bit(nr,p)&t;ATOMIC_BITOP_BE(test_and_change_bit,nr,p)
DECL|macro|test_bit
mdefine_line|#define test_bit(nr,p)&t;&t;&t;____test_bit((nr) ^ 0x18, p)
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(p,sz)&t;_find_first_zero_bit_be(p,sz)
DECL|macro|find_next_zero_bit
mdefine_line|#define find_next_zero_bit(p,sz,off)&t;_find_next_zero_bit_be(p,sz,off)
multiline_comment|/*&n; * These are the little endian, non-atomic definitions.&n; */
DECL|macro|__set_bit
mdefine_line|#define __set_bit(nr,p)&t;&t;&t;NONATOMIC_BITOP_BE(set_bit,nr,p)
DECL|macro|__clear_bit
mdefine_line|#define __clear_bit(nr,p)&t;&t;NONATOMIC_BITOP_BE(clear_bit,nr,p)
DECL|macro|__change_bit
mdefine_line|#define __change_bit(nr,p)&t;&t;NONATOMIC_BITOP_BE(change_bit,nr,p)
DECL|macro|__test_and_set_bit
mdefine_line|#define __test_and_set_bit(nr,p)&t;NONATOMIC_BITOP_BE(test_and_set_bit,nr,p)
DECL|macro|__test_and_clear_bit
mdefine_line|#define __test_and_clear_bit(nr,p)&t;NONATOMIC_BITOP_BE(test_and_clear_bit,nr,p)
DECL|macro|__test_and_change_bit
mdefine_line|#define __test_and_change_bit(nr,p)&t;NONATOMIC_BITOP_BE(test_and_change_bit,nr,p)
DECL|macro|__test_bit
mdefine_line|#define __test_bit(nr,p)&t;&t;____test_bit((nr) ^ 0x18, p)
macro_line|#endif
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
id|k
suffix:semicolon
id|word
op_assign
op_complement
id|word
suffix:semicolon
id|k
op_assign
l_int|31
suffix:semicolon
r_if
c_cond
(paren
id|word
op_amp
l_int|0x0000ffff
)paren
(brace
id|k
op_sub_assign
l_int|16
suffix:semicolon
id|word
op_lshift_assign
l_int|16
suffix:semicolon
)brace
r_if
c_cond
(paren
id|word
op_amp
l_int|0x00ff0000
)paren
(brace
id|k
op_sub_assign
l_int|8
suffix:semicolon
id|word
op_lshift_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
id|word
op_amp
l_int|0x0f000000
)paren
(brace
id|k
op_sub_assign
l_int|4
suffix:semicolon
id|word
op_lshift_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|word
op_amp
l_int|0x30000000
)paren
(brace
id|k
op_sub_assign
l_int|2
suffix:semicolon
id|word
op_lshift_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|word
op_amp
l_int|0x40000000
)paren
(brace
id|k
op_sub_assign
l_int|1
suffix:semicolon
)brace
r_return
id|k
suffix:semicolon
)brace
multiline_comment|/*&n; * ffs: find first bit set. This is defined the same way as&n; * the libc and compiler builtin ffs routines, therefore&n; * differs in spirit from the above ffz (man ffs).&n; */
DECL|macro|ffs
mdefine_line|#define ffs(x) generic_ffs(x)
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
multiline_comment|/*&n; * Ext2 is defined to use little-endian byte ordering.&n; * These do not need to be atomic.&n; */
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr,p)&t;&t;&t;NONATOMIC_BITOP_LE(test_and_set_bit,nr,p)
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr,p)&t;&t;&t;NONATOMIC_BITOP_LE(test_and_clear_bit,nr,p)
DECL|macro|ext2_test_bit
mdefine_line|#define ext2_test_bit(nr,p)&t;&t;&t;__test_bit(nr,p)
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit(p,sz)&t;&t;_find_first_zero_bit_le(p,sz)
DECL|macro|ext2_find_next_zero_bit
mdefine_line|#define ext2_find_next_zero_bit(p,sz,off)&t;_find_next_zero_bit_le(p,sz,off)
multiline_comment|/*&n; * Minix is defined to use little-endian byte ordering.&n; * These do not need to be atomic.&n; */
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,p)&t;&t;&t;NONATOMIC_BITOP_LE(set_bit,nr,p)
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,p)&t;&t;&t;__test_bit(nr,p)
DECL|macro|minix_test_and_set_bit
mdefine_line|#define minix_test_and_set_bit(nr,p)&t;&t;NONATOMIC_BITOP_LE(test_and_set_bit,nr,p)
DECL|macro|minix_test_and_clear_bit
mdefine_line|#define minix_test_and_clear_bit(nr,p)&t;&t;NONATOMIC_BITOP_LE(test_and_clear_bit,nr,p)
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(p,sz)&t;&t;_find_first_zero_bit_le(p,sz)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ARM_BITOPS_H */
eof
