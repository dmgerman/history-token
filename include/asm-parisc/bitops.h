macro_line|#ifndef _PARISC_BITOPS_H
DECL|macro|_PARISC_BITOPS_H
mdefine_line|#define _PARISC_BITOPS_H
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * HP-PARISC specific bit operations&n; * for a detailed description of the functions please refer&n; * to include/asm-i386/bitops.h or kerneldoc&n; */
macro_line|#ifdef __LP64__
DECL|macro|SHIFT_PER_LONG
macro_line|#   define SHIFT_PER_LONG 6
macro_line|#ifndef BITS_PER_LONG
DECL|macro|BITS_PER_LONG
macro_line|#   define BITS_PER_LONG 64
macro_line|#endif
macro_line|#else
DECL|macro|SHIFT_PER_LONG
macro_line|#   define SHIFT_PER_LONG 5
macro_line|#ifndef BITS_PER_LONG
DECL|macro|BITS_PER_LONG
macro_line|#   define BITS_PER_LONG 32
macro_line|#endif
macro_line|#endif
DECL|macro|CHOP_SHIFTCOUNT
mdefine_line|#define CHOP_SHIFTCOUNT(x) ((x) &amp; (BITS_PER_LONG - 1))
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()      smp_mb()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()       smp_mb()
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
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
id|_atomic_spin_lock_irqsave
c_func
(paren
id|addr
comma
id|flags
)paren
suffix:semicolon
op_star
id|addr
op_or_assign
id|mask
suffix:semicolon
id|_atomic_spin_unlock_irqrestore
c_func
(paren
id|addr
comma
id|flags
)paren
suffix:semicolon
)brace
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
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
op_star
id|addr
op_or_assign
id|mask
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
id|nr
comma
r_volatile
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
id|_atomic_spin_lock_irqsave
c_func
(paren
id|addr
comma
id|flags
)paren
suffix:semicolon
op_star
id|addr
op_and_assign
op_complement
id|mask
suffix:semicolon
id|_atomic_spin_unlock_irqrestore
c_func
(paren
id|addr
comma
id|flags
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
r_int
id|nr
comma
r_volatile
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
op_star
id|addr
op_and_assign
op_complement
id|mask
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
id|nr
comma
r_volatile
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
id|_atomic_spin_lock_irqsave
c_func
(paren
id|addr
comma
id|flags
)paren
suffix:semicolon
op_star
id|addr
op_xor_assign
id|mask
suffix:semicolon
id|_atomic_spin_unlock_irqrestore
c_func
(paren
id|addr
comma
id|flags
)paren
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
id|nr
comma
r_volatile
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
op_star
id|addr
op_xor_assign
id|mask
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
id|nr
comma
r_volatile
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
id|_atomic_spin_lock_irqsave
c_func
(paren
id|addr
comma
id|flags
)paren
suffix:semicolon
id|oldbit
op_assign
(paren
op_star
id|addr
op_amp
id|mask
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
op_star
id|addr
op_or_assign
id|mask
suffix:semicolon
id|_atomic_spin_unlock_irqrestore
c_func
(paren
id|addr
comma
id|flags
)paren
suffix:semicolon
r_return
id|oldbit
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
id|nr
comma
r_volatile
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
id|oldbit
op_assign
(paren
op_star
id|addr
op_amp
id|mask
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
op_star
id|addr
op_or_assign
id|mask
suffix:semicolon
r_return
id|oldbit
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
id|nr
comma
r_volatile
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
id|_atomic_spin_lock_irqsave
c_func
(paren
id|addr
comma
id|flags
)paren
suffix:semicolon
id|oldbit
op_assign
(paren
op_star
id|addr
op_amp
id|mask
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
op_star
id|addr
op_and_assign
op_complement
id|mask
suffix:semicolon
id|_atomic_spin_unlock_irqrestore
c_func
(paren
id|addr
comma
id|flags
)paren
suffix:semicolon
r_return
id|oldbit
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
id|nr
comma
r_volatile
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
id|oldbit
op_assign
(paren
op_star
id|addr
op_amp
id|mask
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
op_star
id|addr
op_and_assign
op_complement
id|mask
suffix:semicolon
r_return
id|oldbit
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
id|nr
comma
r_volatile
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
id|_atomic_spin_lock_irqsave
c_func
(paren
id|addr
comma
id|flags
)paren
suffix:semicolon
id|oldbit
op_assign
(paren
op_star
id|addr
op_amp
id|mask
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
op_star
id|addr
op_xor_assign
id|mask
suffix:semicolon
id|_atomic_spin_unlock_irqrestore
c_func
(paren
id|addr
comma
id|flags
)paren
suffix:semicolon
r_return
id|oldbit
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
id|nr
comma
r_volatile
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
id|oldbit
op_assign
(paren
op_star
id|addr
op_amp
id|mask
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
op_star
id|addr
op_xor_assign
id|mask
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
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
r_volatile
r_int
r_int
op_star
id|address
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_const
r_int
r_int
op_star
id|addr
op_assign
(paren
r_const
r_int
r_int
op_star
)paren
id|address
suffix:semicolon
id|addr
op_add_assign
(paren
id|nr
op_rshift
id|SHIFT_PER_LONG
)paren
suffix:semicolon
id|mask
op_assign
l_int|1L
op_lshift
id|CHOP_SHIFTCOUNT
c_func
(paren
id|nr
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
(paren
op_star
id|addr
op_amp
id|mask
)paren
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
multiline_comment|/**&n; * __ffs - find first bit in word. returns 0 to &quot;BITS_PER_LONG-1&quot;.&n; * @word: The word to search&n; *&n; * __ffs() return is undefined if no bit is set.&n; *&n; * 32-bit fast __ffs by LaMont Jones &quot;lamont At hp com&quot;.&n; * 64-bit enhancement by Grant Grundler &quot;grundler At parisc-linux org&quot;.&n; * (with help from willy/jejb to get the semantics right)&n; *&n; * This algorithm avoids branches by making use of nullification.&n; * One side effect of &quot;extr&quot; instructions is it sets PSW[N] bit.&n; * How PSW[N] (nullify next insn) gets set is determined by the &n; * &quot;condition&quot; field (eg &quot;&lt;&gt;&quot; or &quot;TR&quot; below) in the extr* insn.&n; * Only the 1st and one of either the 2cd or 3rd insn will get executed.&n; * Each set of 3 insn will get executed in 2 cycles on PA8x00 vs 16 or so&n; * cycles for each mispredicted branch.&n; */
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
id|x
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
id|__asm__
c_func
(paren
macro_line|#if BITS_PER_LONG &gt; 32
l_string|&quot; ldi       63,%1&bslash;n&quot;
l_string|&quot; extrd,u,*&lt;&gt;  %0,63,32,%%r0&bslash;n&quot;
l_string|&quot; extrd,u,*TR  %0,31,32,%0&bslash;n&quot;
multiline_comment|/* move top 32-bits down */
l_string|&quot; addi    -32,%1,%1&bslash;n&quot;
macro_line|#else
l_string|&quot; ldi       31,%1&bslash;n&quot;
macro_line|#endif
l_string|&quot; extru,&lt;&gt;  %0,31,16,%%r0&bslash;n&quot;
l_string|&quot; extru,TR  %0,15,16,%0&bslash;n&quot;
multiline_comment|/* xxxx0000 -&gt; 0000xxxx */
l_string|&quot; addi    -16,%1,%1&bslash;n&quot;
l_string|&quot; extru,&lt;&gt;  %0,31,8,%%r0&bslash;n&quot;
l_string|&quot; extru,TR  %0,23,8,%0&bslash;n&quot;
multiline_comment|/* 0000xx00 -&gt; 000000xx */
l_string|&quot; addi    -8,%1,%1&bslash;n&quot;
l_string|&quot; extru,&lt;&gt;  %0,31,4,%%r0&bslash;n&quot;
l_string|&quot; extru,TR  %0,27,4,%0&bslash;n&quot;
multiline_comment|/* 000000x0 -&gt; 0000000x */
l_string|&quot; addi    -4,%1,%1&bslash;n&quot;
l_string|&quot; extru,&lt;&gt;  %0,31,2,%%r0&bslash;n&quot;
l_string|&quot; extru,TR  %0,29,2,%0&bslash;n&quot;
multiline_comment|/* 0000000y, 1100b -&gt; 0011b */
l_string|&quot; addi    -2,%1,%1&bslash;n&quot;
l_string|&quot; extru,=  %0,31,1,%%r0&bslash;n&quot;
multiline_comment|/* check last bit */
l_string|&quot; addi    -1,%1,%1&bslash;n&quot;
suffix:colon
l_string|&quot;+r&quot;
(paren
id|x
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ret
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Undefined if no bit is zero. */
DECL|macro|ffz
mdefine_line|#define ffz(x)&t;__ffs(~x)
multiline_comment|/*&n; * ffs: find first bit set. returns 1 to BITS_PER_LONG or 0 (if none set)&n; * This is defined the same way as the libc and compiler builtin&n; * ffs routines, therefore differs in spirit from the above ffz (man ffs).&n; */
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
r_return
id|x
ques
c_cond
(paren
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
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fls: find last (most significant) bit set.&n; * fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.&n; */
DECL|function|fls
r_static
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
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;&t;ldi&t;&t;1,%1&bslash;n&quot;
l_string|&quot;&t;extru,&lt;&gt;&t;%0,15,16,%%r0&bslash;n&quot;
l_string|&quot;&t;zdep,TR&t;&t;%0,15,16,%0&bslash;n&quot;
multiline_comment|/* xxxx0000 */
l_string|&quot;&t;addi&t;&t;16,%1,%1&bslash;n&quot;
l_string|&quot;&t;extru,&lt;&gt;&t;%0,7,8,%%r0&bslash;n&quot;
l_string|&quot;&t;zdep,TR&t;&t;%0,23,24,%0&bslash;n&quot;
multiline_comment|/* xx000000 */
l_string|&quot;&t;addi&t;&t;8,%1,%1&bslash;n&quot;
l_string|&quot;&t;extru,&lt;&gt;&t;%0,3,4,%%r0&bslash;n&quot;
l_string|&quot;&t;zdep,TR&t;&t;%0,27,28,%0&bslash;n&quot;
multiline_comment|/* x0000000 */
l_string|&quot;&t;addi&t;&t;4,%1,%1&bslash;n&quot;
l_string|&quot;&t;extru,&lt;&gt;&t;%0,1,2,%%r0&bslash;n&quot;
l_string|&quot;&t;zdep,TR&t;&t;%0,29,30,%0&bslash;n&quot;
multiline_comment|/* y0000000 (y&amp;3 = 0) */
l_string|&quot;&t;addi&t;&t;2,%1,%1&bslash;n&quot;
l_string|&quot;&t;extru,=&t;&t;%0,0,1,%%r0&bslash;n&quot;
l_string|&quot;&t;addi&t;&t;1,%1,%1&bslash;n&quot;
multiline_comment|/* if y &amp; 8, add 1 */
suffix:colon
l_string|&quot;+r&quot;
(paren
id|x
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ret
)paren
)paren
suffix:semicolon
r_return
id|ret
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
multiline_comment|/*&n; * Every architecture must define this function. It&squot;s the fastest&n; * way of searching a 140-bit bitmap where the first 100 bits are&n; * unlikely to be set. It&squot;s guaranteed that at least one of the 140&n; * bits is cleared.&n; */
DECL|function|sched_find_first_bit
r_static
r_inline
r_int
id|sched_find_first_bit
c_func
(paren
r_const
r_int
r_int
op_star
id|b
)paren
(brace
macro_line|#ifndef __LP64__
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
macro_line|#else
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
(paren
(paren
r_int
r_int
)paren
id|b
(braket
l_int|1
)braket
)paren
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
l_int|64
suffix:semicolon
r_if
c_cond
(paren
id|b
(braket
l_int|1
)braket
op_rshift
l_int|32
)paren
r_return
id|__ffs
c_func
(paren
id|b
(braket
l_int|1
)braket
op_rshift
l_int|32
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
l_int|2
)braket
)paren
op_plus
l_int|128
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * This implementation of find_{first,next}_zero_bit was stolen from&n; * Linus&squot; asm-alpha/bitops.h.&n; */
DECL|macro|find_first_zero_bit
mdefine_line|#define find_first_zero_bit(addr, size) &bslash;&n;&t;find_next_zero_bit((addr), (size), 0)
DECL|function|find_next_zero_bit
r_static
id|__inline__
r_int
r_int
id|find_next_zero_bit
c_func
(paren
r_const
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
r_const
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
id|SHIFT_PER_LONG
)paren
suffix:semicolon
r_int
r_int
id|result
op_assign
id|offset
op_amp
op_complement
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
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
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
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
id|BITS_PER_LONG
op_minus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|BITS_PER_LONG
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
id|BITS_PER_LONG
suffix:semicolon
id|result
op_add_assign
id|BITS_PER_LONG
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_amp
op_complement
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
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
id|BITS_PER_LONG
suffix:semicolon
id|size
op_sub_assign
id|BITS_PER_LONG
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
DECL|function|find_next_bit
r_static
id|__inline__
r_int
r_int
id|find_next_bit
c_func
(paren
r_const
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
r_const
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
id|result
op_assign
id|offset
op_amp
op_complement
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
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
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
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
id|BITS_PER_LONG
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
id|BITS_PER_LONG
suffix:semicolon
id|result
op_add_assign
id|BITS_PER_LONG
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_amp
op_complement
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
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
id|BITS_PER_LONG
suffix:semicolon
id|size
op_sub_assign
id|BITS_PER_LONG
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
id|BITS_PER_LONG
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
multiline_comment|/**&n; * find_first_bit - find the first set bit in a memory region&n; * @addr: The address to start the search at&n; * @size: The maximum size to search&n; *&n; * Returns the bit-number of the first set bit, not the number of the byte&n; * containing a bit.&n; */
DECL|macro|find_first_bit
mdefine_line|#define find_first_bit(addr, size) &bslash;&n;        find_next_bit((addr), (size), 0)
DECL|macro|_EXT2_HAVE_ASM_BITOPS_
mdefine_line|#define _EXT2_HAVE_ASM_BITOPS_
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * test_and_{set,clear}_bit guarantee atomicity without&n; * disabling interrupts.&n; */
macro_line|#ifdef __LP64__
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr, addr)&t;&t;__test_and_set_bit((nr) ^ 0x38, (unsigned long *)addr)
DECL|macro|ext2_set_bit_atomic
mdefine_line|#define ext2_set_bit_atomic(l,nr,addr)  test_and_set_bit((nr) ^ 0x38, (unsigned long *)addr)
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr, addr)&t;__test_and_clear_bit((nr) ^ 0x38, (unsigned long *)addr)
DECL|macro|ext2_clear_bit_atomic
mdefine_line|#define ext2_clear_bit_atomic(l,nr,addr) test_and_clear_bit((nr) ^ 0x38, (unsigned long *)addr)
macro_line|#else
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr, addr)&t;&t;__test_and_set_bit((nr) ^ 0x18, (unsigned long *)addr)
DECL|macro|ext2_set_bit_atomic
mdefine_line|#define ext2_set_bit_atomic(l,nr,addr)  test_and_set_bit((nr) ^ 0x18, (unsigned long *)addr)
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr, addr)&t;__test_and_clear_bit((nr) ^ 0x18, (unsigned long *)addr)
DECL|macro|ext2_clear_bit_atomic
mdefine_line|#define ext2_clear_bit_atomic(l,nr,addr) test_and_clear_bit((nr) ^ 0x18, (unsigned long *)addr)
macro_line|#endif
macro_line|#endif&t;/* __KERNEL__ */
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
id|__const__
r_void
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
multiline_comment|/*&n; * This implementation of ext2_find_{first,next}_zero_bit was stolen from&n; * Linus&squot; asm-alpha/bitops.h and modified for a big-endian machine.&n; */
DECL|macro|ext2_find_first_zero_bit
mdefine_line|#define ext2_find_first_zero_bit(addr, size) &bslash;&n;        ext2_find_next_zero_bit((addr), (size), 0)
DECL|function|ext2_find_next_zero_bit
r_extern
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
id|tmp
op_assign
id|cpu_to_le32p
c_func
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
id|tmp
op_ne
op_complement
l_int|0U
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
op_ge
l_int|32
)paren
(brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|cpu_to_le32p
c_func
(paren
id|p
op_increment
)paren
)paren
op_ne
op_complement
l_int|0U
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
id|cpu_to_le32p
c_func
(paren
id|p
)paren
suffix:semicolon
id|found_first
suffix:colon
id|tmp
op_or_assign
op_complement
l_int|0U
op_lshift
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
multiline_comment|/* Bitmap functions for the minix filesystem.  */
DECL|macro|minix_test_and_set_bit
mdefine_line|#define minix_test_and_set_bit(nr,addr) ext2_set_bit(nr,addr)
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,addr) ((void)ext2_set_bit(nr,addr))
DECL|macro|minix_test_and_clear_bit
mdefine_line|#define minix_test_and_clear_bit(nr,addr) ext2_clear_bit(nr,addr)
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,addr) ext2_test_bit(nr,addr)
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(addr,size) ext2_find_first_zero_bit(addr,size)
macro_line|#endif /* _PARISC_BITOPS_H */
eof
