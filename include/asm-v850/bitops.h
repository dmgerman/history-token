multiline_comment|/*&n; * include/asm-v850/bitops.h -- Bit operations&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *  Copyright (C) 1992  Linus Torvalds.&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; */
macro_line|#ifndef __V850_BITOPS_H__
DECL|macro|__V850_BITOPS_H__
mdefine_line|#define __V850_BITOPS_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;&t;/* unlikely  */
macro_line|#include &lt;asm/byteorder.h&gt;&t;/* swab32 */
macro_line|#include &lt;asm/system.h&gt;&t;&t;/* interrupt enable/disable */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * The __ functions are not atomic&n; */
multiline_comment|/*&n; * ffz = Find First Zero in word. Undefined if no zero exists,&n; * so code should check against ~0UL first..&n; */
DECL|function|ffz
r_extern
id|__inline__
r_int
r_int
id|ffz
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
multiline_comment|/* In the following constant-bit-op macros, a &quot;g&quot; constraint is used when&n;   we really need an integer (&quot;i&quot; constraint).  This is to avoid&n;   warnings/errors from the compiler in the case where the associated&n;   operand _isn&squot;t_ an integer, and shouldn&squot;t produce bogus assembly because&n;   use of that form is protected by a guard statement that checks for&n;   constants, and should otherwise be removed by the optimizer.  This&n;   _usually_ works -- however, __builtin_constant_p returns true for a&n;   variable with a known constant value too, and unfortunately gcc will&n;   happily put the variable in a register and use the register for the &quot;g&quot;&n;   constraint&squot;d asm operand.  To avoid the latter problem, we add a&n;   constant offset to the operand and subtract it back in the asm code;&n;   forcing gcc to do arithmetic on the value is usually enough to get it&n;   to use a real constant value.  This is horrible, and ultimately&n;   unreliable too, but it seems to work for now (hopefully gcc will offer&n;   us more control in the future, so we can do a better job).  */
DECL|macro|__const_bit_op
mdefine_line|#define __const_bit_op(op, nr, addr)&t;&t;&t;&t;&t;&bslash;&n;  ({ __asm__ (op &quot; (%0 - 0x123), %1&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;      :: &quot;g&quot; (((nr) &amp; 0x7) + 0x123),&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;m&quot; (*((char *)(addr) + ((nr) &gt;&gt; 3)))&t;&t;&t;&bslash;&n;&t;      : &quot;memory&quot;); })
DECL|macro|__var_bit_op
mdefine_line|#define __var_bit_op(op, nr, addr)&t;&t;&t;&t;&t;&bslash;&n;  ({ int __nr = (nr);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__ (op &quot; %0, [%1]&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      :: &quot;r&quot; (__nr &amp; 0x7),&t;&t;&t;&t;&t;&bslash;&n;&t;&t; &quot;r&quot; ((char *)(addr) + (__nr &gt;&gt; 3))&t;&t;&t;&bslash;&n;&t;      : &quot;memory&quot;); })
DECL|macro|__bit_op
mdefine_line|#define __bit_op(op, nr, addr)&t;&t;&t;&t;&t;&t;&bslash;&n;  ((__builtin_constant_p (nr) &amp;&amp; (unsigned)(nr) &lt;= 0x7FFFF)&t;&t;&bslash;&n;   ? __const_bit_op (op, nr, addr)&t;&t;&t;&t;&t;&bslash;&n;   : __var_bit_op (op, nr, addr))
DECL|macro|__set_bit
mdefine_line|#define __set_bit(nr, addr)&t;&t;__bit_op (&quot;set1&quot;, nr, addr)
DECL|macro|__clear_bit
mdefine_line|#define __clear_bit(nr, addr)&t;&t;__bit_op (&quot;clr1&quot;, nr, addr)
DECL|macro|__change_bit
mdefine_line|#define __change_bit(nr, addr)&t;&t;__bit_op (&quot;not1&quot;, nr, addr)
multiline_comment|/* The bit instructions used by `non-atomic&squot; variants are actually atomic.  */
DECL|macro|set_bit
mdefine_line|#define set_bit __set_bit
DECL|macro|clear_bit
mdefine_line|#define clear_bit __clear_bit
DECL|macro|change_bit
mdefine_line|#define change_bit __change_bit
DECL|macro|__const_tns_bit_op
mdefine_line|#define __const_tns_bit_op(op, nr, addr)&t;&t;&t;&t;&bslash;&n;  ({ int __tns_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__ (&quot;tst1 (%1 - 0x123), %2; setf nz, %0; &quot; op &quot; (%1 - 0x123), %2&quot; &bslash;&n;&t;      : &quot;=&amp;r&quot; (__tns_res)&t;&t;&t;&t;&t;&bslash;&n;&t;      : &quot;g&quot; (((nr) &amp; 0x7) + 0x123),&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;m&quot; (*((char *)(addr) + ((nr) &gt;&gt; 3)))&t;&t;&t;&bslash;&n;&t;      : &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;     __tns_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  })
DECL|macro|__var_tns_bit_op
mdefine_line|#define __var_tns_bit_op(op, nr, addr)&t;&t;&t;&t;&t;&bslash;&n;  ({ int __nr = (nr);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     int __tns_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__ (&quot;tst1 %1, [%2]; setf nz, %0; &quot; op &quot; %1, [%2]&quot;&t;&t;&bslash;&n;&t;      : &quot;=&amp;r&quot; (__tns_res)&t;&t;&t;&t;&t;&bslash;&n;&t;      : &quot;r&quot; (__nr &amp; 0x7),&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;r&quot; ((char *)(addr) + (__nr &gt;&gt; 3))&t;&t;&t;&bslash;&n;&t;      : &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;     __tns_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  })
DECL|macro|__tns_bit_op
mdefine_line|#define __tns_bit_op(op, nr, addr)&t;&t;&t;&t;&t;&bslash;&n;  ((__builtin_constant_p (nr) &amp;&amp; (unsigned)(nr) &lt;= 0x7FFFF)&t;&t;&bslash;&n;   ? __const_tns_bit_op (op, nr, addr)&t;&t;&t;&t;&t;&bslash;&n;   : __var_tns_bit_op (op, nr, addr))
DECL|macro|__tns_atomic_bit_op
mdefine_line|#define __tns_atomic_bit_op(op, nr, addr)&t;&t;&t;&t;&bslash;&n;  ({ int __tns_atomic_res, __tns_atomic_flags;&t;&t;&t;&t;&bslash;&n;     local_irq_save (__tns_atomic_flags);&t;&t;&t;&t;&bslash;&n;     __tns_atomic_res = __tns_bit_op (op, nr, addr);&t;&t;&t;&bslash;&n;     local_irq_restore (__tns_atomic_flags);&t;&t;&t;&t;&bslash;&n;     __tns_atomic_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  })
DECL|macro|__test_and_set_bit
mdefine_line|#define __test_and_set_bit(nr, addr)&t;__tns_bit_op (&quot;set1&quot;, nr, addr)
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit(nr, addr)&t;__tns_atomic_bit_op (&quot;set1&quot;, nr, addr)
DECL|macro|__test_and_clear_bit
mdefine_line|#define __test_and_clear_bit(nr, addr)&t;__tns_bit_op (&quot;clr1&quot;, nr, addr)
DECL|macro|test_and_clear_bit
mdefine_line|#define test_and_clear_bit(nr, addr)&t;__tns_atomic_bit_op (&quot;clr1&quot;, nr, addr)
DECL|macro|__test_and_change_bit
mdefine_line|#define __test_and_change_bit(nr, addr)&t;__tns_bit_op (&quot;not1&quot;, nr, addr)
DECL|macro|test_and_change_bit
mdefine_line|#define test_and_change_bit(nr, addr)&t;__tns_atomic_bit_op (&quot;not1&quot;, nr, addr)
DECL|macro|__const_test_bit
mdefine_line|#define __const_test_bit(nr, addr)&t;&t;&t;&t;&t;&bslash;&n;  ({ int __test_bit_res;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__ (&quot;tst1 (%1 - 0x123), %2; setf nz, %0&quot;&t;&t;&t;&bslash;&n;&t;      : &quot;=r&quot; (__test_bit_res)&t;&t;&t;&t;&t;&bslash;&n;&t;      : &quot;g&quot; (((nr) &amp; 0x7) + 0x123),&t;&t;&t;&t;&bslash;&n;                &quot;m&quot; (*((const char *)(addr) + ((nr) &gt;&gt; 3))));&t;&t;&bslash;&n;     __test_bit_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  })
DECL|function|__test_bit
r_extern
id|__inline__
r_int
id|__test_bit
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
id|res
suffix:semicolon
id|__asm__
(paren
l_string|&quot;tst1 %1, [%2]; setf nz, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
op_amp
l_int|0x7
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|3
)paren
)paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|macro|test_bit
mdefine_line|#define test_bit(nr,addr)&t;&t;&t;&t;&t;&t;&bslash;&n;  ((__builtin_constant_p (nr) &amp;&amp; (unsigned)(nr) &lt;= 0x7FFFF)&t;&t;&bslash;&n;   ? __const_test_bit ((nr), (addr))&t;&t;&t;&t;&t;&bslash;&n;   : __test_bit ((nr), (addr)))
multiline_comment|/* clear_bit doesn&squot;t provide any barrier for the compiler.  */
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;barrier ()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;barrier ()
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;  find_next_zero_bit ((addr), (size), 0)
DECL|function|find_next_zero_bit
r_extern
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
(paren
id|tmp
)paren
suffix:semicolon
)brace
DECL|macro|ffs
mdefine_line|#define ffs(x) generic_ffs (x)
DECL|macro|fls
mdefine_line|#define fls(x) generic_fls (x)
DECL|macro|__ffs
mdefine_line|#define __ffs(x) ffs(x)
multiline_comment|/*&n; * This is just `generic_ffs&squot; from &lt;linux/bitops.h&gt;, except that it assumes&n; * that at least one bit is set, and returns the real index of the bit&n; * (rather than the bit index + 1, like ffs does).&n; */
DECL|function|sched_ffs
r_static
r_inline
r_int
id|sched_ffs
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
multiline_comment|/*&n; * Every architecture must define this function. It&squot;s the fastest&n; * way of searching a 140-bit bitmap where the first 100 bits are&n; * unlikely to be set. It&squot;s guaranteed that at least one of the 140&n; * bits is set.&n; */
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
id|offs
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
op_star
id|b
)paren
(brace
id|b
op_increment
suffix:semicolon
id|offs
op_add_assign
l_int|32
suffix:semicolon
)brace
r_return
id|sched_ffs
(paren
op_star
id|b
)paren
op_plus
id|offs
suffix:semicolon
)brace
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) &t;&t;&t;generic_hweight32 (x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) &t;&t;&t;generic_hweight16 (x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) &t;&t;&t;generic_hweight8 (x)
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit&t;&t;&t;test_and_set_bit
DECL|macro|ext2_set_bit_atomic
mdefine_line|#define ext2_set_bit_atomic(l,n,a)      test_and_set_bit(n,a)
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit&t;&t;&t;test_and_clear_bit
DECL|macro|ext2_clear_bit_atomic
mdefine_line|#define ext2_clear_bit_atomic(l,n,a)    test_and_clear_bit(n,a)
DECL|macro|ext2_test_bit
mdefine_line|#define ext2_test_bit&t;&t;&t;test_bit
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit&t;find_first_zero_bit
DECL|macro|ext2_find_next_zero_bit
mdefine_line|#define ext2_find_next_zero_bit&t;&t;find_next_zero_bit
multiline_comment|/* Bitmap functions for the minix filesystem.  */
DECL|macro|minix_test_and_set_bit
mdefine_line|#define minix_test_and_set_bit&t;&t;test_and_set_bit
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit&t;&t;&t;set_bit
DECL|macro|minix_test_and_clear_bit
mdefine_line|#define minix_test_and_clear_bit&t;test_and_clear_bit
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit &t;&t;&t;test_bit
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit &t;find_first_zero_bit
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __V850_BITOPS_H__ */
eof
