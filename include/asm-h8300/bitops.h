macro_line|#ifndef _H8300_BITOPS_H
DECL|macro|_H8300_BITOPS_H
mdefine_line|#define _H8300_BITOPS_H
multiline_comment|/*&n; * Copyright 1992, Linus Torvalds.&n; * Copyright 2002, Yoshinori Sato&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;&t;/* swab32 */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Function prototypes to keep gcc -Wall happy&n; */
multiline_comment|/*&n; * ffz = Find First Zero in word. Undefined if no zero exists,&n; * so code should check against ~0UL first..&n; */
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
r_int
r_int
id|result
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;shlr.l %2&bslash;n&bslash;t&quot;
l_string|&quot;adds #1,%0&bslash;n&bslash;t&quot;
l_string|&quot;bcs 1b&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|result
)paren
comma
l_string|&quot;r&quot;
(paren
id|word
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|macro|H8300_GEN_BITOP_CONST
mdefine_line|#define H8300_GEN_BITOP_CONST(OP,BIT)&t;&t;&t;    &bslash;&n;&t;case BIT:&t;&t;&t;&t;&t;    &bslash;&n;&t;__asm__(OP &quot; #&quot; #BIT &quot;,@%0&quot;::&quot;r&quot;(b_addr):&quot;memory&quot;); &bslash;&n;&t;break;
DECL|macro|H8300_GEN_BITOP
mdefine_line|#define H8300_GEN_BITOP(FNAME,OP)&t;&t;&t;&t;      &bslash;&n;static __inline__ void FNAME(int nr, volatile unsigned long* addr)    &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;volatile unsigned char *b_addr;&t;&t;&t;&t;      &bslash;&n;&t;b_addr = (volatile unsigned char *)addr + ((nr &gt;&gt; 3) ^ 3);    &bslash;&n;&t;if (__builtin_constant_p(nr)) {&t;&t;&t;&t;      &bslash;&n;&t;&t;switch(nr &amp; 7) {&t;&t;&t;&t;      &bslash;&n;&t;&t;&t;H8300_GEN_BITOP_CONST(OP,0)&t;&t;      &bslash;&n;&t;&t;&t;H8300_GEN_BITOP_CONST(OP,1)&t;&t;      &bslash;&n;&t;&t;&t;H8300_GEN_BITOP_CONST(OP,2)&t;&t;      &bslash;&n;&t;&t;&t;H8300_GEN_BITOP_CONST(OP,3)&t;&t;      &bslash;&n;&t;&t;&t;H8300_GEN_BITOP_CONST(OP,4)&t;&t;      &bslash;&n;&t;&t;&t;H8300_GEN_BITOP_CONST(OP,5)&t;&t;      &bslash;&n;&t;&t;&t;H8300_GEN_BITOP_CONST(OP,6)&t;&t;      &bslash;&n;&t;&t;&t;H8300_GEN_BITOP_CONST(OP,7)&t;&t;      &bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;__asm__(OP &quot; %w0,@%1&quot;::&quot;r&quot;(nr),&quot;r&quot;(b_addr):&quot;memory&quot;); &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;}
multiline_comment|/*&n; * clear_bit() doesn&squot;t provide any barrier for the compiler.&n; */
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()&t;barrier()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()&t;barrier()
id|H8300_GEN_BITOP
c_func
(paren
id|set_bit
comma
l_string|&quot;bset&quot;
)paren
id|H8300_GEN_BITOP
c_func
(paren
id|clear_bit
comma
l_string|&quot;bclr&quot;
)paren
id|H8300_GEN_BITOP
c_func
(paren
id|change_bit
comma
l_string|&quot;bnot&quot;
)paren
DECL|macro|__set_bit
mdefine_line|#define __set_bit(nr,addr)    set_bit((nr),(addr))
DECL|macro|__clear_bit
mdefine_line|#define __clear_bit(nr,addr)  clear_bit((nr),(addr))
DECL|macro|__change_bit
mdefine_line|#define __change_bit(nr,addr) change_bit((nr),(addr))
DECL|macro|H8300_GEN_BITOP
macro_line|#undef H8300_GEN_BITOP
DECL|macro|H8300_GEN_BITOP_CONST
macro_line|#undef H8300_GEN_BITOP_CONST
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
r_const
r_int
r_int
op_star
id|addr
)paren
(brace
r_return
(paren
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
op_amp
(paren
l_int|1UL
op_lshift
(paren
id|nr
op_amp
l_int|7
)paren
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|macro|__test_bit
mdefine_line|#define __test_bit(nr, addr) test_bit(nr, addr)
DECL|macro|H8300_GEN_TEST_BITOP_CONST_INT
mdefine_line|#define H8300_GEN_TEST_BITOP_CONST_INT(OP,BIT)&t;&t;&t;     &bslash;&n;&t;case BIT:&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;__asm__(&quot;stc ccr,%w1&bslash;n&bslash;t&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;orc #0x80,ccr&bslash;n&bslash;t&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;bld #&quot; #BIT &quot;,@%4&bslash;n&bslash;t&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;OP &quot; #&quot; #BIT &quot;,@%4&bslash;n&bslash;t&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;rotxl.l %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;ldc %w1,ccr&quot;&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;: &quot;=r&quot;(retval),&quot;=&amp;r&quot;(ccrsave),&quot;=m&quot;(*b_addr)&t;     &bslash;&n;&t;&t;: &quot;0&quot; (retval),&quot;r&quot; (b_addr)&t;&t;&t;     &bslash;&n;&t;&t;: &quot;memory&quot;);                                         &bslash;&n;        break;
DECL|macro|H8300_GEN_TEST_BITOP_CONST
mdefine_line|#define H8300_GEN_TEST_BITOP_CONST(OP,BIT)&t;&t;&t;     &bslash;&n;&t;case BIT:&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;__asm__(&quot;bld #&quot; #BIT &quot;,@%3&bslash;n&bslash;t&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;OP &quot; #&quot; #BIT &quot;,@%3&bslash;n&bslash;t&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&quot;rotxl.l %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;: &quot;=r&quot;(retval),&quot;=m&quot;(*b_addr)&t;&t;&t;     &bslash;&n;&t;&t;: &quot;0&quot; (retval),&quot;r&quot; (b_addr)&t;&t;&t;     &bslash;&n;&t;&t;: &quot;memory&quot;);                                         &bslash;&n;        break;
DECL|macro|H8300_GEN_TEST_BITOP
mdefine_line|#define H8300_GEN_TEST_BITOP(FNNAME,OP)&t;&t;&t;&t;     &bslash;&n;static __inline__ int FNNAME(int nr, volatile void * addr)&t;     &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;int retval = 0;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;char ccrsave;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;volatile unsigned char *b_addr;&t;&t;&t;&t;     &bslash;&n;&t;b_addr = (volatile unsigned char *)addr + ((nr &gt;&gt; 3) ^ 3);   &bslash;&n;&t;if (__builtin_constant_p(nr)) {&t;&t;&t;&t;     &bslash;&n;&t;&t;switch(nr &amp; 7) {&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST_INT(OP,0)&t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST_INT(OP,1)&t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST_INT(OP,2)&t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST_INT(OP,3)&t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST_INT(OP,4)&t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST_INT(OP,5)&t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST_INT(OP,6)&t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST_INT(OP,7)&t;     &bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;__asm__(&quot;stc ccr,%w1&bslash;n&bslash;t&quot;&t;&t;&t;     &bslash;&n;&t;&t;&t;&quot;orc #0x80,ccr&bslash;n&bslash;t&quot;&t;&t;&t;     &bslash;&n;&t;&t;&t;&quot;btst %w5,@%4&bslash;n&bslash;t&quot;&t;&t;&t;     &bslash;&n;&t;&t;&t;OP &quot; %w5,@%4&bslash;n&bslash;t&quot;&t;&t;&t;     &bslash;&n;&t;&t;&t;&quot;beq 1f&bslash;n&bslash;t&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;&quot;inc.l #1,%0&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;&quot;1:&bslash;n&bslash;t&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;&quot;ldc %w1,ccr&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;: &quot;=r&quot;(retval),&quot;=&amp;r&quot;(ccrsave),&quot;=m&quot;(*b_addr)  &bslash;&n;&t;&t;&t;: &quot;0&quot; (retval),&quot;r&quot; (b_addr),&quot;r&quot;(nr)&t;     &bslash;&n;&t;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;     &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;return retval;&t;&t;&t;&t;&t;&t;     &bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;static __inline__ int __ ## FNNAME(int nr, volatile void * addr)     &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;int retval = 0;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;volatile unsigned char *b_addr;&t;&t;&t;&t;     &bslash;&n;&t;b_addr = (volatile unsigned char *)addr + ((nr &gt;&gt; 3) ^ 3);   &bslash;&n;&t;if (__builtin_constant_p(nr)) {&t;&t;&t;&t;     &bslash;&n;&t;&t;switch(nr &amp; 7) {&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST(OP,0) &t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST(OP,1) &t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST(OP,2) &t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST(OP,3) &t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST(OP,4) &t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST(OP,5) &t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST(OP,6) &t;     &bslash;&n;&t;&t;&t;H8300_GEN_TEST_BITOP_CONST(OP,7) &t;     &bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;__asm__(&quot;btst %w4,@%3&bslash;n&bslash;t&quot;&t;&t;&t;     &bslash;&n;&t;&t;&t;OP &quot; %w4,@%3&bslash;n&bslash;t&quot;&t;&t;&t;     &bslash;&n;&t;&t;&t;&quot;beq 1f&bslash;n&bslash;t&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;&quot;inc.l #1,%0&bslash;n&quot;&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;&quot;1:&quot;&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;&t;: &quot;=r&quot;(retval),&quot;=m&quot;(*b_addr)&t;&t;     &bslash;&n;&t;&t;&t;: &quot;0&quot; (retval),&quot;r&quot; (b_addr),&quot;r&quot;(nr)&t;     &bslash;&n;&t;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;     &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;return retval;&t;&t;&t;&t;&t;&t;     &bslash;&n;}
id|H8300_GEN_TEST_BITOP
c_func
(paren
id|test_and_set_bit
comma
l_string|&quot;bset&quot;
)paren
id|H8300_GEN_TEST_BITOP
c_func
(paren
id|test_and_clear_bit
comma
l_string|&quot;bclr&quot;
)paren
id|H8300_GEN_TEST_BITOP
c_func
(paren
id|test_and_change_bit
comma
l_string|&quot;bnot&quot;
)paren
DECL|macro|H8300_GEN_TEST_BITOP_CONST
macro_line|#undef H8300_GEN_TEST_BITOP_CONST
DECL|macro|H8300_GEN_TEST_BITOP_CONST_INT
macro_line|#undef H8300_GEN_TEST_BITOP_CONST_INT
DECL|macro|H8300_GEN_TEST_BITOP
macro_line|#undef H8300_GEN_TEST_BITOP
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;&t;find_next_zero_bit((addr), (size), 0)
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
r_int
r_int
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|addr
op_plus
(paren
id|offset
op_rshift
l_int|3
)paren
)paren
op_amp
op_complement
l_int|3
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
r_int
r_int
id|result
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;shlr.l %2&bslash;n&bslash;t&quot;
l_string|&quot;adds #1,%0&bslash;n&bslash;t&quot;
l_string|&quot;bcc 1b&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|result
)paren
comma
l_string|&quot;r&quot;
(paren
id|word
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|macro|ffs
mdefine_line|#define ffs(x) generic_ffs(x)
DECL|macro|fls
mdefine_line|#define fls(x) generic_fls(x)
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
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
DECL|function|ext2_set_bit
r_static
id|__inline__
r_int
id|ext2_set_bit
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
id|mask
comma
id|retval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_volatile
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
id|local_irq_save
c_func
(paren
id|flags
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
DECL|macro|ext2_set_bit_atomic
mdefine_line|#define ext2_set_bit_atomic(lock, nr, addr) ext2_set_bit(nr, addr)
DECL|function|ext2_clear_bit
r_static
id|__inline__
r_int
id|ext2_clear_bit
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
id|mask
comma
id|retval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_volatile
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
id|local_irq_save
c_func
(paren
id|flags
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
DECL|macro|ext2_clear_bit_atomic
mdefine_line|#define ext2_clear_bit_atomic(lock, nr, addr) ext2_set_bit(nr, addr)
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
r_const
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_int
id|mask
suffix:semicolon
r_const
r_volatile
r_int
r_char
op_star
id|ADDR
op_assign
(paren
r_const
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
r_return
(paren
(paren
id|mask
op_amp
op_star
id|ADDR
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit(addr, size) &bslash;&n;&t;ext2_find_next_zero_bit((addr), (size), 0)
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
multiline_comment|/* We hold the little endian value in tmp, but then the&n;&t;&t; * shift is illegal. So we could keep a big endian value&n;&t;&t; * in tmp, like this:&n;&t;&t; *&n;&t;&t; * tmp = __swab32(*(p++));&n;&t;&t; * tmp |= ~0UL &gt;&gt; (32-offset);&n;&t;&t; *&n;&t;&t; * but this would decrease performance, so we change the&n;&t;&t; * shift:&n;&t;&t; */
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
multiline_comment|/* tmp is little endian, so we would have to swab the shift,&n;&t; * see above. But then we have to swab tmp below for ffz, so&n;&t; * we might as well do this here.&n;&t; */
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
op_or
(paren
op_complement
l_int|0UL
op_lshift
id|size
)paren
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
multiline_comment|/* Bitmap functions for the minix filesystem.  */
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
macro_line|#endif /* _H8300_BITOPS_H */
eof
