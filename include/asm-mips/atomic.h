multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; *&n; * But use these as seldom as possible since they are much more slower&n; * than regular operations.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 97, 99, 2000, 03 by Ralf Baechle&n; */
multiline_comment|/*&n; * As workaround for the ATOMIC_DEC_AND_LOCK / atomic_dec_and_lock mess in&n; * &lt;linux/spinlock.h&gt; we have to include &lt;linux/spinlock.h&gt; outside the&n; * main big wrapper ...&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#ifndef _ASM_ATOMIC_H
DECL|macro|_ASM_ATOMIC_H
mdefine_line|#define _ASM_ATOMIC_H
r_extern
id|spinlock_t
id|atomic_lock
suffix:semicolon
DECL|member|counter
DECL|typedef|atomic_t
r_typedef
r_struct
(brace
r_volatile
r_int
id|counter
suffix:semicolon
)brace
id|atomic_t
suffix:semicolon
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)    { (i) }
multiline_comment|/*&n; * atomic_read - read atomic variable&n; * @v: pointer of type atomic_t&n; *&n; * Atomically reads the value of @v.&n; */
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter)
multiline_comment|/*&n; * atomic_set - set atomic variable&n; * @v: pointer of type atomic_t&n; * @i: required value&n; *&n; * Atomically sets the value of @v to @i.&n; */
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;&t;((v)-&gt;counter = (i))
macro_line|#ifdef CONFIG_CPU_HAS_LLSC
multiline_comment|/*&n; * atomic_add - add integer to atomic variable&n; * @i: integer value to add&n; * @v: pointer of type atomic_t&n; *&n; * Atomically adds @i to @v.&n; */
DECL|function|atomic_add
r_static
id|__inline__
r_void
id|atomic_add
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ll&t;%0, %1&t;&t;# atomic_add&t;&t;&bslash;n&quot;
l_string|&quot;&t;addu&t;%0, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%0, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * atomic_sub - subtract the atomic variable&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; *&n; * Atomically subtracts @i from @v.&n; */
DECL|function|atomic_sub
r_static
id|__inline__
r_void
id|atomic_sub
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ll&t;%0, %1&t;&t;# atomic_sub&t;&t;&bslash;n&quot;
l_string|&quot;&t;subu&t;%0, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%0, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Same as above, but return the result value&n; */
DECL|function|atomic_add_return
r_static
id|__inline__
r_int
id|atomic_add_return
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
comma
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ll&t;%1, %2&t;&t;# atomic_add_return&t;&bslash;n&quot;
l_string|&quot;&t;addu&t;%0, %1, %3&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%0, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;addu&t;%0, %1, %3&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|atomic_sub_return
r_static
id|__inline__
r_int
id|atomic_sub_return
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
comma
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ll&t;%1, %2&t;&t;# atomic_sub_return&t;&bslash;n&quot;
l_string|&quot;&t;subu&t;%0, %1, %3&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%0, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;subu&t;%0, %1, %3&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * The MIPS I implementation is only atomic with respect to&n; * interrupts.  R3000 based multiprocessor machines are rare anyway ...&n; *&n; * atomic_add - add integer to atomic variable&n; * @i: integer value to add&n; * @v: pointer of type atomic_t&n; *&n; * Atomically adds @i to @v.&n; */
DECL|function|atomic_add
r_static
id|__inline__
r_void
id|atomic_add
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
id|v-&gt;counter
op_add_assign
id|i
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * atomic_sub - subtract the atomic variable&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; *&n; * Atomically subtracts @i from @v.&n; */
DECL|function|atomic_sub
r_static
id|__inline__
r_void
id|atomic_sub
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
id|v-&gt;counter
op_sub_assign
id|i
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|atomic_add_return
r_static
id|__inline__
r_int
id|atomic_add_return
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|temp
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
id|temp
op_assign
id|v-&gt;counter
suffix:semicolon
id|temp
op_add_assign
id|i
suffix:semicolon
id|v-&gt;counter
op_assign
id|temp
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|temp
suffix:semicolon
)brace
DECL|function|atomic_sub_return
r_static
id|__inline__
r_int
id|atomic_sub_return
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|temp
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
id|temp
op_assign
id|v-&gt;counter
suffix:semicolon
id|temp
op_sub_assign
id|i
suffix:semicolon
id|v-&gt;counter
op_assign
id|temp
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|temp
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_CPU_HAS_LLSC */
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v) atomic_sub_return(1,(v))
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v) atomic_add_return(1,(v))
multiline_comment|/*&n; * atomic_sub_and_test - subtract value from variable and test result&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; *&n; * Atomically subtracts @i from @v and returns&n; * true if the result is zero, or false for all&n; * other cases.&n; */
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(i,v) (atomic_sub_return((i), (v)) == 0)
multiline_comment|/*&n; * atomic_inc_and_test - increment and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically increments @v by 1&n; * and returns true if the result is zero, or false for all&n; * other cases.&n; */
DECL|macro|atomic_inc_and_test
mdefine_line|#define atomic_inc_and_test(v) (atomic_inc_return(v) == 0)
multiline_comment|/*&n; * atomic_dec_and_test - decrement by 1 and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically decrements @v by 1 and&n; * returns true if the result is 0, or false for all other&n; * cases.&n; */
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v) (atomic_sub_return(1, (v)) == 0)
multiline_comment|/*&n; * atomic_inc - increment atomic variable&n; * @v: pointer of type atomic_t&n; *&n; * Atomically increments @v by 1.&n; */
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) atomic_add(1,(v))
multiline_comment|/*&n; * atomic_dec - decrement and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically decrements @v by 1.&n; */
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) atomic_sub(1,(v))
multiline_comment|/*&n; * atomic_add_negative - add and test if negative&n; * @v: pointer of type atomic_t&n; * @i: integer value to add&n; *&n; * Atomically adds @i to @v and returns true&n; * if the result is negative, or false when&n; * result is greater than or equal to zero.&n; */
DECL|macro|atomic_add_negative
mdefine_line|#define atomic_add_negative(i,v) (atomic_add_return(i, (v)) &lt; 0)
macro_line|#ifdef CONFIG_MIPS64
DECL|member|counter
DECL|typedef|atomic64_t
r_typedef
r_struct
(brace
r_volatile
id|__s64
id|counter
suffix:semicolon
)brace
id|atomic64_t
suffix:semicolon
DECL|macro|ATOMIC64_INIT
mdefine_line|#define ATOMIC64_INIT(i)    { (i) }
multiline_comment|/*&n; * atomic64_read - read atomic variable&n; * @v: pointer of type atomic64_t&n; *&n; */
DECL|macro|atomic64_read
mdefine_line|#define atomic64_read(v)&t;((v)-&gt;counter)
multiline_comment|/*&n; * atomic64_set - set atomic variable&n; * @v: pointer of type atomic64_t&n; * @i: required value&n; */
DECL|macro|atomic64_set
mdefine_line|#define atomic64_set(v,i)&t;((v)-&gt;counter = (i))
macro_line|#ifdef CONFIG_CPU_HAS_LLDSCD
multiline_comment|/*&n; * atomic64_add - add integer to atomic variable&n; * @i: integer value to add&n; * @v: pointer of type atomic64_t&n; *&n; * Atomically adds @i to @v.&n; */
DECL|function|atomic64_add
r_static
id|__inline__
r_void
id|atomic64_add
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lld&t;%0, %1&t;&t;# atomic64_add&t;&t;&bslash;n&quot;
l_string|&quot;&t;addu&t;%0, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;scd&t;%0, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * atomic64_sub - subtract the atomic variable&n; * @i: integer value to subtract&n; * @v: pointer of type atomic64_t&n; *&n; * Atomically subtracts @i from @v.&n; */
DECL|function|atomic64_sub
r_static
id|__inline__
r_void
id|atomic64_sub
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lld&t;%0, %1&t;&t;# atomic64_sub&t;&t;&bslash;n&quot;
l_string|&quot;&t;subu&t;%0, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;scd&t;%0, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Same as above, but return the result value&n; */
DECL|function|atomic64_add_return
r_static
id|__inline__
r_int
id|atomic64_add_return
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
comma
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lld&t;%1, %2&t;&t;# atomic64_add_return&t;&bslash;n&quot;
l_string|&quot;&t;addu&t;%0, %1, %3&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;scd&t;%0, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;addu&t;%0, %1, %3&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|atomic64_sub_return
r_static
id|__inline__
r_int
id|atomic64_sub_return
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
comma
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;lld&t;%1, %2&t;&t;# atomic64_sub_return&t;&bslash;n&quot;
l_string|&quot;&t;subu&t;%0, %1, %3&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;scd&t;%0, %2&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%0, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;subu&t;%0, %1, %3&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * This implementation is only atomic with respect to interrupts.  It can&squot;t&n; * be used on SMP&n; *&n; * atomic64_add - add integer to atomic variable&n; * @i: integer value to add&n; * @v: pointer of type atomic64_t&n; *&n; * Atomically adds @i to @v.&n; */
DECL|function|atomic64_add
r_static
id|__inline__
r_void
id|atomic64_add
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
id|v-&gt;counter
op_add_assign
id|i
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * atomic64_sub - subtract the atomic variable&n; * @i: integer value to subtract&n; * @v: pointer of type atomic64_t&n; *&n; * Atomically subtracts @i from @v.&n; */
DECL|function|atomic64_sub
r_static
id|__inline__
r_void
id|atomic64_sub
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
id|v-&gt;counter
op_sub_assign
id|i
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|atomic64_add_return
r_static
id|__inline__
r_int
id|atomic64_add_return
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|temp
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
id|temp
op_assign
id|v-&gt;counter
suffix:semicolon
id|temp
op_add_assign
id|i
suffix:semicolon
id|v-&gt;counter
op_assign
id|temp
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|temp
suffix:semicolon
)brace
DECL|function|atomic64_sub_return
r_static
id|__inline__
r_int
id|atomic64_sub_return
c_func
(paren
r_int
id|i
comma
id|atomic64_t
op_star
id|v
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|temp
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
id|temp
op_assign
id|v-&gt;counter
suffix:semicolon
id|temp
op_sub_assign
id|i
suffix:semicolon
id|v-&gt;counter
op_assign
id|temp
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|atomic_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|temp
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_CPU_HAS_LLDSCD */
DECL|macro|atomic64_dec_return
mdefine_line|#define atomic64_dec_return(v) atomic64_sub_return(1,(v))
DECL|macro|atomic64_inc_return
mdefine_line|#define atomic64_inc_return(v) atomic64_add_return(1,(v))
multiline_comment|/*&n; * atomic64_sub_and_test - subtract value from variable and test result&n; * @i: integer value to subtract&n; * @v: pointer of type atomic64_t&n; *&n; * Atomically subtracts @i from @v and returns&n; * true if the result is zero, or false for all&n; * other cases.&n; */
DECL|macro|atomic64_sub_and_test
mdefine_line|#define atomic64_sub_and_test(i,v) (atomic64_sub_return((i), (v)) == 0)
multiline_comment|/*&n; * atomic64_inc_and_test - increment and test&n; * @v: pointer of type atomic64_t&n; *&n; * Atomically increments @v by 1&n; * and returns true if the result is zero, or false for all&n; * other cases.&n; */
DECL|macro|atomic64_inc_and_test
mdefine_line|#define atomic64_inc_and_test(v) (atomic64_inc_return(v) == 0)
multiline_comment|/*&n; * atomic64_dec_and_test - decrement by 1 and test&n; * @v: pointer of type atomic64_t&n; *&n; * Atomically decrements @v by 1 and&n; * returns true if the result is 0, or false for all other&n; * cases.&n; */
DECL|macro|atomic64_dec_and_test
mdefine_line|#define atomic64_dec_and_test(v) (atomic64_sub_return(1, (v)) == 0)
multiline_comment|/*&n; * atomic64_inc - increment atomic variable&n; * @v: pointer of type atomic64_t&n; *&n; * Atomically increments @v by 1.&n; */
DECL|macro|atomic64_inc
mdefine_line|#define atomic64_inc(v) atomic64_add(1,(v))
multiline_comment|/*&n; * atomic64_dec - decrement and test&n; * @v: pointer of type atomic64_t&n; *&n; * Atomically decrements @v by 1.&n; */
DECL|macro|atomic64_dec
mdefine_line|#define atomic64_dec(v) atomic64_sub(1,(v))
multiline_comment|/*&n; * atomic64_add_negative - add and test if negative&n; * @v: pointer of type atomic64_t&n; * @i: integer value to add&n; *&n; * Atomically adds @i to @v and returns true&n; * if the result is negative, or false when&n; * result is greater than or equal to zero.&n; */
DECL|macro|atomic64_add_negative
mdefine_line|#define atomic64_add_negative(i,v) (atomic64_add_return(i, (v)) &lt; 0)
macro_line|#endif /* CONFIG_MIPS64 */
multiline_comment|/*&n; * atomic*_return operations are serializing but not the non-*_return&n; * versions.&n; */
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;smp_mb()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;smp_mb()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;smp_mb()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;smp_mb()
macro_line|#endif /* _ASM_ATOMIC_H */
eof
