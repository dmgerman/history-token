multiline_comment|/* asm/bitops.h for Linux/CRIS&n; *&n; * TODO: asm versions if speed is needed&n; *&n; * All bit operations return 0 if the bit was cleared before the&n; * operation and != 0 if it was not.&n; *&n; * bit 0 is the LSB of addr; bit 32 is the LSB of (addr+1).&n; */
macro_line|#ifndef _CRIS_BITOPS_H
DECL|macro|_CRIS_BITOPS_H
mdefine_line|#define _CRIS_BITOPS_H
multiline_comment|/* Currently this is unsuitable for consumption outside the kernel.  */
macro_line|#ifdef __KERNEL__ 
macro_line|#include &lt;asm/arch/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/*&n; * Some hacks to defeat gcc over-optimizations..&n; */
DECL|struct|__dummy
DECL|member|a
r_struct
id|__dummy
(brace
r_int
r_int
id|a
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ADDR
mdefine_line|#define ADDR (*(struct __dummy *) addr)
DECL|macro|CONST_ADDR
mdefine_line|#define CONST_ADDR (*(const struct __dummy *) addr)
multiline_comment|/*&n; * set_bit - Atomically set a bit in memory&n; * @nr: the bit to set&n; * @addr: the address to start counting from&n; *&n; * This function is atomic and may not be reordered.  See __set_bit()&n; * if you do not require the atomic guarantees.&n; * Note that @nr may be almost arbitrarily large; this function is not&n; * restricted to acting on a single-word quantity.&n; */
DECL|macro|set_bit
mdefine_line|#define set_bit(nr, addr)    (void)test_and_set_bit(nr, addr)
DECL|macro|__set_bit
mdefine_line|#define __set_bit(nr, addr)    (void)__test_and_set_bit(nr, addr)
multiline_comment|/*&n; * clear_bit - Clears a bit in memory&n; * @nr: Bit to clear&n; * @addr: Address to start counting from&n; *&n; * clear_bit() is atomic and may not be reordered.  However, it does&n; * not contain a memory barrier, so if it is used for locking purposes,&n; * you should call smp_mb__before_clear_bit() and/or smp_mb__after_clear_bit()&n; * in order to ensure changes are visible on other processors.&n; */
DECL|macro|clear_bit
mdefine_line|#define clear_bit(nr, addr)  (void)test_and_clear_bit(nr, addr)
DECL|macro|__clear_bit
mdefine_line|#define __clear_bit(nr, addr)  (void)__test_and_clear_bit(nr, addr)
multiline_comment|/*&n; * change_bit - Toggle a bit in memory&n; * @nr: Bit to change&n; * @addr: Address to start counting from&n; *&n; * change_bit() is atomic and may not be reordered.&n; * Note that @nr may be almost arbitrarily large; this function is not&n; * restricted to acting on a single-word quantity.&n; */
DECL|macro|change_bit
mdefine_line|#define change_bit(nr, addr) (void)test_and_change_bit(nr, addr)
multiline_comment|/*&n; * __change_bit - Toggle a bit in memory&n; * @nr: the bit to change&n; * @addr: the address to start counting from&n; *&n; * Unlike change_bit(), this function is non-atomic and may be reordered.&n; * If it&squot;s called on the same region of memory simultaneously, the effect&n; * may be that only one operation succeeds.&n; */
DECL|macro|__change_bit
mdefine_line|#define __change_bit(nr, addr) (void)__test_and_change_bit(nr, addr)
multiline_comment|/**&n; * test_and_set_bit - Set a bit and return its old value&n; * @nr: Bit to set&n; * @addr: Address to count from&n; *&n; * This operation is atomic and cannot be reordered.  &n; * It also implies a memory barrier.&n; */
DECL|function|test_and_set_bit
r_extern
r_inline
r_int
id|test_and_set_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|mask
comma
id|retval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
op_star
id|adr
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
id|adr
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
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|adr
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|adr
op_or_assign
id|mask
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|__test_and_set_bit
r_extern
r_inline
r_int
id|__test_and_set_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|mask
comma
id|retval
suffix:semicolon
r_int
r_int
op_star
id|adr
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
id|adr
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
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|adr
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|adr
op_or_assign
id|mask
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * clear_bit() doesn&squot;t provide any barrier for the compiler.&n; */
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()      barrier()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()       barrier()
multiline_comment|/**&n; * test_and_clear_bit - Clear a bit and return its old value&n; * @nr: Bit to clear&n; * @addr: Address to count from&n; *&n; * This operation is atomic and cannot be reordered.  &n; * It also implies a memory barrier.&n; */
DECL|function|test_and_clear_bit
r_extern
r_inline
r_int
id|test_and_clear_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|mask
comma
id|retval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
op_star
id|adr
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
id|adr
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
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|adr
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|adr
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
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; * __test_and_clear_bit - Clear a bit and return its old value&n; * @nr: Bit to clear&n; * @addr: Address to count from&n; *&n; * This operation is non-atomic and can be reordered.  &n; * If two examples of this operation race, one can appear to succeed&n; * but actually fail.  You must protect multiple accesses with a lock.&n; */
DECL|function|__test_and_clear_bit
r_extern
r_inline
r_int
id|__test_and_clear_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|mask
comma
id|retval
suffix:semicolon
r_int
r_int
op_star
id|adr
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
id|adr
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
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|adr
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|adr
op_and_assign
op_complement
id|mask
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; * test_and_change_bit - Change a bit and return its old value&n; * @nr: Bit to change&n; * @addr: Address to count from&n; *&n; * This operation is atomic and cannot be reordered.  &n; * It also implies a memory barrier.&n; */
DECL|function|test_and_change_bit
r_extern
r_inline
r_int
id|test_and_change_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|mask
comma
id|retval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
op_star
id|adr
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
id|adr
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
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|adr
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|adr
op_xor_assign
id|mask
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* WARNING: non atomic and it can be reordered! */
DECL|function|__test_and_change_bit
r_extern
r_inline
r_int
id|__test_and_change_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|mask
comma
id|retval
suffix:semicolon
r_int
r_int
op_star
id|adr
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
id|adr
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
id|retval
op_assign
(paren
id|mask
op_amp
op_star
id|adr
)paren
op_ne
l_int|0
suffix:semicolon
op_star
id|adr
op_xor_assign
id|mask
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; * test_bit - Determine whether a bit is set&n; * @nr: bit number to test&n; * @addr: Address to start counting from&n; *&n; * This routine doesn&squot;t need to be atomic.&n; */
DECL|function|test_bit
r_extern
r_inline
r_int
id|test_bit
c_func
(paren
r_int
id|nr
comma
r_const
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|adr
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
id|adr
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
id|adr
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Find-bit routines..&n; */
multiline_comment|/*&n; * Since we define it &quot;external&quot;, it collides with the built-in&n; * definition, which doesn&squot;t have the same semantics.  We don&squot;t want to&n; * use -fno-builtin, so just hide the name ffs.&n; */
DECL|macro|ffs
mdefine_line|#define ffs kernel_ffs
multiline_comment|/*&n; * fls: find last bit set.&n; */
DECL|macro|fls
mdefine_line|#define fls(x) generic_fls(x)
multiline_comment|/*&n; * hweightN - returns the hamming weight of a N-bit word&n; * @x: the word to weigh&n; *&n; * The Hamming Weight of a number is the total number of bits set in it.&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
multiline_comment|/**&n; * find_next_zero_bit - find the first zero bit in a memory region&n; * @addr: The address to base the search on&n; * @offset: The bitnumber to start searching at&n; * @size: The maximum size to search&n; */
DECL|function|find_next_zero_bit
r_extern
r_inline
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
multiline_comment|/**&n; * find_next_bit - find the first set bit in a memory region&n; * @addr: The address to base the search on&n; * @offset: The bitnumber to start searching at&n; * @size: The maximum size to search&n; */
DECL|function|find_next_bit
r_static
id|__inline__
r_int
id|find_next_bit
c_func
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
op_and_assign
(paren
op_complement
l_int|0UL
op_lshift
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
op_and_assign
(paren
op_complement
l_int|0UL
op_rshift
(paren
l_int|32
op_minus
id|size
)paren
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
multiline_comment|/**&n; * find_first_zero_bit - find the first zero bit in a memory region&n; * @addr: The address to start the search at&n; * @size: The maximum size to search&n; *&n; * Returns the bit-number of the first zero bit, not the number of the byte&n; * containing a bit.&n; */
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;        find_next_zero_bit((addr), (size), 0)
DECL|macro|find_first_bit
mdefine_line|#define find_first_bit(addr, size) &bslash;&n;        find_next_bit((addr), (size), 0)
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit                 test_and_set_bit
DECL|macro|ext2_set_bit_atomic
mdefine_line|#define ext2_set_bit_atomic(l,n,a)   test_and_set_bit(n,a)
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit               test_and_clear_bit
DECL|macro|ext2_clear_bit_atomic
mdefine_line|#define ext2_clear_bit_atomic(l,n,a) test_and_clear_bit(n,a)
DECL|macro|ext2_test_bit
mdefine_line|#define ext2_test_bit                test_bit
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit     find_first_zero_bit
DECL|macro|ext2_find_next_zero_bit
mdefine_line|#define ext2_find_next_zero_bit      find_next_zero_bit
multiline_comment|/* Bitmap functions for the minix filesystem.  */
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,addr) test_and_set_bit(nr,addr)
DECL|macro|minix_clear_bit
mdefine_line|#define minix_clear_bit(nr,addr) test_and_clear_bit(nr,addr)
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,addr) test_bit(nr,addr)
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(addr,size) find_first_zero_bit(addr,size)
DECL|function|sched_find_first_bit
r_extern
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
id|unlikely
c_func
(paren
id|b
(braket
l_int|3
)braket
)paren
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
r_if
c_cond
(paren
id|b
(braket
l_int|4
)braket
)paren
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
r_return
id|__ffs
c_func
(paren
id|b
(braket
l_int|5
)braket
)paren
op_plus
l_int|32
op_plus
l_int|128
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _CRIS_BITOPS_H */
eof
