multiline_comment|/*&n; * Copyright 1995, Russell King.&n; * Various bits and pieces copyrights include:&n; *  Linus Torvalds (test_bit).&n; * Big endian support: Copyright 2001, Nicolas Pitre&n; *  reworked by rmk.&n; *&n; * bit 0 is the LSB of an &quot;unsigned long&quot; quantity.&n; *&n; * Please note that the code in this file should never be included&n; * from user space.  Many of these are not implemented in assembler&n; * since they would be too costly.  Also, they require privileged&n; * instructions (which are not available from user mode) to ensure&n; * that they are atomic.&n; */
macro_line|#ifndef __ASM_ARM_BITOPS_H
DECL|macro|__ASM_ARM_BITOPS_H
mdefine_line|#define __ASM_ARM_BITOPS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;do { } while (0)
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;do { } while (0)
multiline_comment|/*&n; * These functions are the basis of our bit ops.&n; *&n; * First, the atomic bitops. These use native endian.&n; */
DECL|function|____atomic_set_bit
r_static
r_inline
r_void
id|____atomic_set_bit
c_func
(paren
r_int
r_int
id|bit
comma
r_volatile
r_int
r_int
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
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|bit
op_amp
l_int|31
)paren
suffix:semicolon
id|p
op_add_assign
id|bit
op_rshift
l_int|5
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
DECL|function|____atomic_clear_bit
r_static
r_inline
r_void
id|____atomic_clear_bit
c_func
(paren
r_int
r_int
id|bit
comma
r_volatile
r_int
r_int
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
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|bit
op_amp
l_int|31
)paren
suffix:semicolon
id|p
op_add_assign
id|bit
op_rshift
l_int|5
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
DECL|function|____atomic_change_bit
r_static
r_inline
r_void
id|____atomic_change_bit
c_func
(paren
r_int
r_int
id|bit
comma
r_volatile
r_int
r_int
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
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|bit
op_amp
l_int|31
)paren
suffix:semicolon
id|p
op_add_assign
id|bit
op_rshift
l_int|5
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
DECL|function|____atomic_test_and_set_bit
id|____atomic_test_and_set_bit
c_func
(paren
r_int
r_int
id|bit
comma
r_volatile
r_int
r_int
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
r_int
r_int
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|bit
op_amp
l_int|31
)paren
suffix:semicolon
id|p
op_add_assign
id|bit
op_rshift
l_int|5
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
DECL|function|____atomic_test_and_clear_bit
id|____atomic_test_and_clear_bit
c_func
(paren
r_int
r_int
id|bit
comma
r_volatile
r_int
r_int
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
r_int
r_int
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|bit
op_amp
l_int|31
)paren
suffix:semicolon
id|p
op_add_assign
id|bit
op_rshift
l_int|5
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
DECL|function|____atomic_test_and_change_bit
id|____atomic_test_and_change_bit
c_func
(paren
r_int
r_int
id|bit
comma
r_volatile
r_int
r_int
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
r_int
r_int
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|bit
op_amp
l_int|31
)paren
suffix:semicolon
id|p
op_add_assign
id|bit
op_rshift
l_int|5
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
multiline_comment|/*&n; * Now the non-atomic variants.  We let the compiler handle all&n; * optimisations for these.  These are all _native_ endian.&n; */
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
id|p
)paren
(brace
id|p
(braket
id|nr
op_rshift
l_int|5
)braket
op_or_assign
(paren
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
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
id|p
)paren
(brace
id|p
(braket
id|nr
op_rshift
l_int|5
)braket
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
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
id|p
)paren
(brace
id|p
(braket
id|nr
op_rshift
l_int|5
)braket
op_xor_assign
(paren
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
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
id|p
)paren
(brace
r_int
r_int
id|oldval
comma
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
id|p
op_add_assign
id|nr
op_rshift
l_int|5
suffix:semicolon
id|oldval
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
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
id|p
)paren
(brace
r_int
r_int
id|oldval
comma
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
id|p
op_add_assign
id|nr
op_rshift
l_int|5
suffix:semicolon
id|oldval
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
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
id|p
)paren
(brace
r_int
r_int
id|oldval
comma
id|mask
op_assign
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
suffix:semicolon
id|p
op_add_assign
id|nr
op_rshift
l_int|5
suffix:semicolon
id|oldval
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
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
DECL|function|__test_bit
r_static
r_inline
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
id|p
)paren
(brace
r_return
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
l_int|31
)paren
)paren
op_amp
l_int|1UL
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
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
r_extern
r_int
id|_find_first_bit_le
c_func
(paren
r_const
r_int
r_int
op_star
id|p
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|_find_next_bit_le
c_func
(paren
r_const
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
r_extern
r_int
id|_find_first_bit_be
c_func
(paren
r_const
r_int
r_int
op_star
id|p
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|_find_next_bit_be
c_func
(paren
r_const
r_int
r_int
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
mdefine_line|#define&t;ATOMIC_BITOP_LE(name,nr,p)&t;&t;&bslash;&n;&t;(__builtin_constant_p(nr) ?&t;&t;&bslash;&n;&t; ____atomic_##name(nr, p) :&t;&t;&bslash;&n;&t; _##name##_le(nr,p))
DECL|macro|ATOMIC_BITOP_BE
mdefine_line|#define&t;ATOMIC_BITOP_BE(name,nr,p)&t;&t;&bslash;&n;&t;(__builtin_constant_p(nr) ?&t;&t;&bslash;&n;&t; ____atomic_##name(nr, p) :&t;&t;&bslash;&n;&t; _##name##_be(nr,p))
DECL|macro|NONATOMIC_BITOP
mdefine_line|#define NONATOMIC_BITOP(name,nr,p)&t;&t;&bslash;&n;&t;(____nonatomic_##name(nr, p))
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
mdefine_line|#define test_bit(nr,p)&t;&t;&t;__test_bit(nr,p)
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(p,sz)&t;_find_first_zero_bit_le(p,sz)
DECL|macro|find_next_zero_bit
mdefine_line|#define find_next_zero_bit(p,sz,off)&t;_find_next_zero_bit_le(p,sz,off)
DECL|macro|find_first_bit
mdefine_line|#define find_first_bit(p,sz)&t;&t;_find_first_bit_le(p,sz)
DECL|macro|find_next_bit
mdefine_line|#define find_next_bit(p,sz,off)&t;&t;_find_next_bit_le(p,sz,off)
DECL|macro|WORD_BITOFF_TO_LE
mdefine_line|#define WORD_BITOFF_TO_LE(x)&t;&t;((x))
macro_line|#else
multiline_comment|/*&n; * These are the big endian, atomic definitions.&n; */
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
mdefine_line|#define test_bit(nr,p)&t;&t;&t;__test_bit(nr,p)
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(p,sz)&t;_find_first_zero_bit_be(p,sz)
DECL|macro|find_next_zero_bit
mdefine_line|#define find_next_zero_bit(p,sz,off)&t;_find_next_zero_bit_be(p,sz,off)
DECL|macro|find_first_bit
mdefine_line|#define find_first_bit(p,sz)&t;&t;_find_first_bit_be(p,sz)
DECL|macro|find_next_bit
mdefine_line|#define find_next_bit(p,sz,off)&t;&t;_find_next_bit_be(p,sz,off)
DECL|macro|WORD_BITOFF_TO_LE
mdefine_line|#define WORD_BITOFF_TO_LE(x)&t;&t;((x) ^ 0x18)
macro_line|#endif
macro_line|#if __LINUX_ARM_ARCH__ &lt; 5
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
multiline_comment|/*&n; * ffz = Find First Zero in word. Undefined if no zero exists,&n; * so code should check against ~0UL first..&n; */
DECL|function|__ffs
r_static
r_inline
r_int
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
id|k
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
multiline_comment|/*&n; * fls: find last bit set.&n; */
DECL|macro|fls
mdefine_line|#define fls(x) generic_fls(x)
multiline_comment|/*&n; * ffs: find first bit set. This is defined the same way as&n; * the libc and compiler builtin ffs routines, therefore&n; * differs in spirit from the above ffz (man ffs).&n; */
DECL|macro|ffs
mdefine_line|#define ffs(x) generic_ffs(x)
macro_line|#else
multiline_comment|/*&n; * On ARMv5 and above those functions can be implemented around&n; * the clz instruction for much better code efficiency.&n; */
r_extern
id|__inline__
r_int
id|generic_fls
c_func
(paren
r_int
id|x
)paren
suffix:semicolon
DECL|macro|fls
mdefine_line|#define fls(x) &bslash;&n;&t;( __builtin_constant_p(x) ? generic_fls(x) : &bslash;&n;&t;  ({ int __r; asm(&quot;clz&bslash;t%0, %1&quot; : &quot;=r&quot;(__r) : &quot;r&quot;(x) : &quot;cc&quot;); 32-__r; }) )
DECL|macro|ffs
mdefine_line|#define ffs(x) ({ unsigned long __t = (x); fls(__t &amp; -__t); })
DECL|macro|__ffs
mdefine_line|#define __ffs(x) (ffs(x) - 1)
DECL|macro|ffz
mdefine_line|#define ffz(x) __ffs( ~(x) )
macro_line|#endif
multiline_comment|/*&n; * Find first bit set in a 168-bit bitmap, where the first&n; * 128 bits are unlikely to be set.&n; */
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
r_int
r_int
id|v
suffix:semicolon
r_int
r_int
id|off
suffix:semicolon
r_for
c_loop
(paren
id|off
op_assign
l_int|0
suffix:semicolon
id|v
op_assign
id|b
(braket
id|off
)braket
comma
id|off
OL
l_int|4
suffix:semicolon
id|off
op_increment
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|v
)paren
)paren
r_break
suffix:semicolon
)brace
r_return
id|__ffs
c_func
(paren
id|v
)paren
op_plus
id|off
op_star
l_int|32
suffix:semicolon
)brace
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
multiline_comment|/*&n; * Ext2 is defined to use little-endian byte ordering.&n; * These do not need to be atomic.&n; */
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr,p)&t;&t;&t;&bslash;&n;&t;&t;__test_and_set_bit(WORD_BITOFF_TO_LE(nr), (unsigned long *)(p))
DECL|macro|ext2_set_bit_atomic
mdefine_line|#define ext2_set_bit_atomic(lock,nr,p)          &bslash;&n;                test_and_set_bit(WORD_BITOFF_TO_LE(nr), (unsigned long *)(p))
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr,p)&t;&t;&t;&bslash;&n;&t;&t;__test_and_clear_bit(WORD_BITOFF_TO_LE(nr), (unsigned long *)(p))
DECL|macro|ext2_clear_bit_atomic
mdefine_line|#define ext2_clear_bit_atomic(lock,nr,p)        &bslash;&n;                test_and_clear_bit(WORD_BITOFF_TO_LE(nr), (unsigned long *)(p))
DECL|macro|ext2_test_bit
mdefine_line|#define ext2_test_bit(nr,p)&t;&t;&t;&bslash;&n;&t;&t;__test_bit(WORD_BITOFF_TO_LE(nr), (unsigned long *)(p))
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit(p,sz)&t;&t;&bslash;&n;&t;&t;_find_first_zero_bit_le(p,sz)
DECL|macro|ext2_find_next_zero_bit
mdefine_line|#define ext2_find_next_zero_bit(p,sz,off)&t;&bslash;&n;&t;&t;_find_next_zero_bit_le(p,sz,off)
multiline_comment|/*&n; * Minix is defined to use little-endian byte ordering.&n; * These do not need to be atomic.&n; */
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,p)&t;&t;&t;&bslash;&n;&t;&t;__set_bit(WORD_BITOFF_TO_LE(nr), (unsigned long *)(p))
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,p)&t;&t;&t;&bslash;&n;&t;&t;__test_bit(WORD_BITOFF_TO_LE(nr), (unsigned long *)(p))
DECL|macro|minix_test_and_set_bit
mdefine_line|#define minix_test_and_set_bit(nr,p)&t;&t;&bslash;&n;&t;&t;__test_and_set_bit(WORD_BITOFF_TO_LE(nr), (unsigned long *)(p))
DECL|macro|minix_test_and_clear_bit
mdefine_line|#define minix_test_and_clear_bit(nr,p)&t;&t;&bslash;&n;&t;&t;__test_and_clear_bit(WORD_BITOFF_TO_LE(nr), (unsigned long *)(p))
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(p,sz)&t;&t;&bslash;&n;&t;&t;_find_first_zero_bit_le(p,sz)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ARM_BITOPS_H */
eof
