macro_line|#ifndef _X86_64_BITOPS_H
DECL|macro|_X86_64_BITOPS_H
mdefine_line|#define _X86_64_BITOPS_H
multiline_comment|/*&n; * Copyright 1992, Linus Torvalds.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * These have to be done with inline assembly: that way the bit-setting&n; * is guaranteed to be atomic. All bit operations return 0 if the bit&n; * was cleared before the operation and != 0 if it was not.&n; *&n; * bit 0 is the LSB of addr; bit 32 is the LSB of (addr+1).&n; */
macro_line|#ifdef CONFIG_SMP
DECL|macro|LOCK_PREFIX
mdefine_line|#define LOCK_PREFIX &quot;lock ; &quot;
macro_line|#else
DECL|macro|LOCK_PREFIX
mdefine_line|#define LOCK_PREFIX &quot;&quot;
macro_line|#endif
DECL|macro|ADDR
mdefine_line|#define ADDR (*(volatile long *) addr)
multiline_comment|/**&n; * set_bit - Atomically set a bit in memory&n; * @nr: the bit to set&n; * @addr: the address to start counting from&n; *&n; * This function is atomic and may not be reordered.  See __set_bit()&n; * if you do not require the atomic guarantees.&n; * Note that @nr may be almost arbitrarily large; this function is not&n; * restricted to acting on a single-word quantity.&n; */
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
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK_PREFIX
l_string|&quot;btsq %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * __set_bit - Set a bit in memory&n; * @nr: the bit to set&n; * @addr: the address to start counting from&n; *&n; * Unlike set_bit(), this function is non-atomic and may be reordered.&n; * If it&squot;s called on the same region of memory simultaneously, the effect&n; * may be that only one operation succeeds.&n; */
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
r_void
op_star
id|addr
)paren
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;btsl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * clear_bit - Clears a bit in memory&n; * @nr: Bit to clear&n; * @addr: Address to start counting from&n; *&n; * clear_bit() is atomic and may not be reordered.  However, it does&n; * not contain a memory barrier, so if it is used for locking purposes,&n; * you should call smp_mb__before_clear_bit() and/or smp_mb__after_clear_bit()&n; * in order to ensure changes are visible on other processors.&n; */
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
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK_PREFIX
l_string|&quot;btrl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
)paren
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
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;btrl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
)paren
suffix:semicolon
)brace
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;barrier()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;barrier()
multiline_comment|/**&n; * __change_bit - Toggle a bit in memory&n; * @nr: the bit to set&n; * @addr: the address to start counting from&n; *&n; * Unlike change_bit(), this function is non-atomic and may be reordered.&n; * If it&squot;s called on the same region of memory simultaneously, the effect&n; * may be that only one operation succeeds.&n; */
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
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;btcl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * change_bit - Toggle a bit in memory&n; * @nr: Bit to clear&n; * @addr: Address to start counting from&n; *&n; * change_bit() is atomic and may not be reordered.&n; * Note that @nr may be almost arbitrarily large; this function is not&n; * restricted to acting on a single-word quantity.&n; */
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
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK_PREFIX
l_string|&quot;btcl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * test_and_set_bit - Set a bit and return its old value&n; * @nr: Bit to set&n; * @addr: Address to count from&n; *&n; * This operation is atomic and cannot be reordered.  &n; * It also implies a memory barrier.&n; */
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
r_void
op_star
id|addr
)paren
(brace
r_int
id|oldbit
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK_PREFIX
l_string|&quot;btsl %2,%1&bslash;n&bslash;tsbbl %0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|oldbit
)paren
comma
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
multiline_comment|/**&n; * __test_and_set_bit - Set a bit and return its old value&n; * @nr: Bit to set&n; * @addr: Address to count from&n; *&n; * This operation is non-atomic and can be reordered.  &n; * If two examples of this operation race, one can appear to succeed&n; * but actually fail.  You must protect multiple accesses with a lock.&n; */
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
r_void
op_star
id|addr
)paren
(brace
r_int
id|oldbit
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;btsl %2,%1&bslash;n&bslash;tsbbl %0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|oldbit
)paren
comma
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
)paren
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
multiline_comment|/**&n; * test_and_clear_bit - Clear a bit and return its old value&n; * @nr: Bit to set&n; * @addr: Address to count from&n; *&n; * This operation is atomic and cannot be reordered.  &n; * It also implies a memory barrier.&n; */
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
r_void
op_star
id|addr
)paren
(brace
r_int
id|oldbit
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK_PREFIX
l_string|&quot;btrl %2,%1&bslash;n&bslash;tsbbl %0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|oldbit
)paren
comma
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
multiline_comment|/**&n; * __test_and_clear_bit - Clear a bit and return its old value&n; * @nr: Bit to set&n; * @addr: Address to count from&n; *&n; * This operation is non-atomic and can be reordered.  &n; * If two examples of this operation race, one can appear to succeed&n; * but actually fail.  You must protect multiple accesses with a lock.&n; */
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
r_void
op_star
id|addr
)paren
(brace
r_int
id|oldbit
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;btrl %2,%1&bslash;n&bslash;tsbbl %0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|oldbit
)paren
comma
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
)paren
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
multiline_comment|/* WARNING: non atomic and it can be reordered! */
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
r_void
op_star
id|addr
)paren
(brace
r_int
id|oldbit
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;btcl %2,%1&bslash;n&bslash;tsbbl %0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|oldbit
)paren
comma
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
multiline_comment|/**&n; * test_and_change_bit - Change a bit and return its new value&n; * @nr: Bit to set&n; * @addr: Address to count from&n; *&n; * This operation is atomic and cannot be reordered.  &n; * It also implies a memory barrier.&n; */
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
r_void
op_star
id|addr
)paren
(brace
r_int
id|oldbit
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK_PREFIX
l_string|&quot;btcl %2,%1&bslash;n&bslash;tsbbl %0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|oldbit
)paren
comma
l_string|&quot;=m&quot;
(paren
id|ADDR
)paren
suffix:colon
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
macro_line|#if 0 /* Fool kernel-doc since it doesn&squot;t do macros yet */
multiline_comment|/**&n; * test_bit - Determine whether a bit is set&n; * @nr: bit number to test&n; * @addr: Address to start counting from&n; */
r_static
r_int
id|test_bit
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
suffix:semicolon
macro_line|#endif
DECL|function|constant_test_bit
r_static
id|__inline__
r_int
id|constant_test_bit
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
DECL|function|variable_test_bit
r_static
id|__inline__
r_int
id|variable_test_bit
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
r_int
id|oldbit
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;btl %2,%1&bslash;n&bslash;tsbbl %0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|oldbit
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|ADDR
)paren
comma
l_string|&quot;dIr&quot;
(paren
id|nr
)paren
)paren
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
DECL|macro|test_bit
mdefine_line|#define test_bit(nr,addr) &bslash;&n;(__builtin_constant_p(nr) ? &bslash;&n; constant_test_bit((nr),(addr)) : &bslash;&n; variable_test_bit((nr),(addr)))
multiline_comment|/**&n; * find_first_zero_bit - find the first zero bit in a memory region&n; * @addr: The address to start the search at&n; * @size: The maximum size to search&n; *&n; * Returns the bit-number of the first zero bit, not the number of the byte&n; * containing a bit.&n; */
DECL|function|find_first_zero_bit
r_static
id|__inline__
r_int
id|find_first_zero_bit
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|size
)paren
(brace
r_int
id|d0
comma
id|d1
comma
id|d2
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
id|__volatile__
c_func
(paren
l_string|&quot;movl $-1,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;xorl %%edx,%%edx&bslash;n&bslash;t&quot;
l_string|&quot;repe; scasl&bslash;n&bslash;t&quot;
l_string|&quot;je 1f&bslash;n&bslash;t&quot;
l_string|&quot;xorl -4(%%rdi),%%eax&bslash;n&bslash;t&quot;
l_string|&quot;subq $4,%%rdi&bslash;n&bslash;t&quot;
l_string|&quot;bsfl %%eax,%%edx&bslash;n&quot;
l_string|&quot;1:&bslash;tsubq %%rbx,%%rdi&bslash;n&bslash;t&quot;
l_string|&quot;shlq $3,%%rdi&bslash;n&bslash;t&quot;
l_string|&quot;addq %%rdi,%%rdx&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;c&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d1
)paren
comma
l_string|&quot;=&amp;a&quot;
(paren
id|d2
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
(paren
id|size
op_plus
l_int|31
)paren
op_rshift
l_int|5
)paren
comma
l_string|&quot;2&quot;
(paren
id|addr
)paren
comma
l_string|&quot;b&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/**&n; * find_next_zero_bit - find the first zero bit in a memory region&n; * @addr: The address to base the search on&n; * @offset: The bitnumber to start searching at&n; * @size: The maximum size to search&n; */
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
l_int|6
)paren
suffix:semicolon
r_int
r_int
id|set
op_assign
l_int|0
suffix:semicolon
r_int
id|res
comma
id|bit
op_assign
id|offset
op_amp
l_int|63
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/*&n;&t;&t; * Look for zero in first word&n;&t;&t; */
id|__asm__
c_func
(paren
l_string|&quot;bsfq %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;cmoveq %2,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|set
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_complement
(paren
op_star
id|p
op_rshift
id|bit
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|64L
)paren
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
id|set
op_assign
l_int|64
op_minus
id|bit
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * No zero yet, search remaining full words for a zero&n;&t; */
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
id|set
op_plus
id|res
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * find_first_bit - find the first set bit in a memory region&n; * @addr: The address to start the search at&n; * @size: The maximum size to search&n; *&n; * Returns the bit-number of the first set bit, not the number of the byte&n; * containing a bit.&n; */
DECL|function|find_first_bit
r_static
id|__inline__
r_int
id|find_first_bit
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|size
)paren
(brace
r_int
id|d0
comma
id|d1
suffix:semicolon
r_int
id|res
suffix:semicolon
multiline_comment|/* This looks at memory. Mark it volatile to tell gcc not to move it around */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;xorl %%eax,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;repe; scasl&bslash;n&bslash;t&quot;
l_string|&quot;jz 1f&bslash;n&bslash;t&quot;
l_string|&quot;leaq -4(%%rdi),%%rdi&bslash;n&bslash;t&quot;
l_string|&quot;bsfq (%%rdi),%%rax&bslash;n&quot;
l_string|&quot;1:&bslash;tsubl %%ebx,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;shll $3,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;addl %%edi,%%eax&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|res
)paren
comma
l_string|&quot;=&amp;c&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d1
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
(paren
id|size
op_plus
l_int|31
)paren
op_rshift
l_int|5
)paren
comma
l_string|&quot;2&quot;
(paren
id|addr
)paren
comma
l_string|&quot;b&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
r_return
id|res
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
id|set
op_assign
l_int|0
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
multiline_comment|/*&n;&t;&t; * Look for nonzero in the first 32 bits:&n;&t;&t; */
id|__asm__
c_func
(paren
l_string|&quot;bsfl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;cmovel %2,%0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|set
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_star
id|p
op_rshift
id|bit
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|32
)paren
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
id|set
op_assign
l_int|32
op_minus
id|bit
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * No set bit yet, search remaining full words for a bit&n;&t; */
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
id|set
op_plus
id|res
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * ffz - find first zero in word.&n; * @word: The word to search&n; *&n; * Undefined if no zero exists, so code should check against ~0UL first.&n; */
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
id|__asm__
c_func
(paren
l_string|&quot;bsfq %1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_complement
id|word
)paren
)paren
suffix:semicolon
r_return
id|word
suffix:semicolon
)brace
multiline_comment|/**&n; * __ffs - find first bit in word.&n; * @word: The word to search&n; *&n; * Undefined if no bit exists, so code should check against 0 first.&n; */
DECL|function|__ffs
r_static
id|__inline__
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
id|__asm__
c_func
(paren
l_string|&quot;bsfq %1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;rm&quot;
(paren
id|word
)paren
)paren
suffix:semicolon
r_return
id|word
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
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
id|b
(braket
l_int|0
)braket
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
id|b
(braket
l_int|1
)braket
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
l_int|64
suffix:semicolon
r_if
c_cond
(paren
id|b
(braket
l_int|2
)braket
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
l_int|128
suffix:semicolon
)brace
multiline_comment|/**&n; * ffs - find first bit set&n; * @x: the word to search&n; *&n; * This is defined the same way as&n; * the libc and compiler builtin ffs routines, therefore&n; * differs in spirit from the above ffz (man ffs).&n; */
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
id|r
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;bsfl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;cmovzl %2,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r
)paren
suffix:colon
l_string|&quot;g&quot;
(paren
id|x
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|32
)paren
)paren
suffix:semicolon
r_return
id|r
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * hweightN - returns the hamming weight of a N-bit word&n; * @x: the word to weigh&n; *&n; * The Hamming Weight of a number is the total number of bits set in it.&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
macro_line|#endif /* __KERNEL__ */
macro_line|#ifdef __KERNEL__
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr,addr) &bslash;&n;&t;__test_and_set_bit((nr),(unsigned long*)addr)
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr, addr) &bslash;&n;&t;__test_and_clear_bit((nr),(unsigned long*)addr)
DECL|macro|ext2_test_bit
mdefine_line|#define ext2_test_bit(nr, addr)      test_bit((nr),(unsigned long*)addr)
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit(addr, size) &bslash;&n;&t;find_first_zero_bit((unsigned long*)addr, size)
DECL|macro|ext2_find_next_zero_bit
mdefine_line|#define ext2_find_next_zero_bit(addr, size, off) &bslash;&n;&t;find_next_zero_bit((unsigned long*)addr, size, off)
multiline_comment|/* Bitmap functions for the minix filesystem.  */
DECL|macro|minix_test_and_set_bit
mdefine_line|#define minix_test_and_set_bit(nr,addr) __test_and_set_bit(nr,(void*)addr)
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,addr) __set_bit(nr,(void*)addr)
DECL|macro|minix_test_and_clear_bit
mdefine_line|#define minix_test_and_clear_bit(nr,addr) __test_and_clear_bit(nr,(void*)addr)
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,addr) test_bit(nr,(void*)addr)
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(addr,size) &bslash;&n;&t;find_first_zero_bit((void*)addr,size)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _X86_64_BITOPS_H */
eof
