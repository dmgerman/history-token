macro_line|#ifndef _ASM_M32R_ATOMIC_H
DECL|macro|_ASM_M32R_ATOMIC_H
mdefine_line|#define _ASM_M32R_ATOMIC_H
multiline_comment|/*&n; *  linux/include/asm-m32r/atomic.h&n; *&n; *  M32R version:&n; *    Copyright (C) 2001, 2002  Hitoshi Yamamoto&n; *    Copyright (C) 2004  Hirokazu Takata &lt;takata at linux-m32r.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/assembler.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; */
multiline_comment|/*&n; * Make sure gcc doesn&squot;t try to be clever and move things around&n; * on us. We need to use _exactly_ the address the user gave us,&n; * not some alias that contains the same information.&n; */
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
mdefine_line|#define ATOMIC_INIT(i)&t;{ (i) }
multiline_comment|/**&n; * atomic_read - read atomic variable&n; * @v: pointer of type atomic_t&n; *&n; * Atomically reads the value of @v.&n; */
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;((v)-&gt;counter)
multiline_comment|/**&n; * atomic_set - set atomic variable&n; * @v: pointer of type atomic_t&n; * @i: required value&n; *&n; * Atomically sets the value of @v to @i.&n; */
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;(((v)-&gt;counter) = (i))
multiline_comment|/**&n; * atomic_add_return - add integer to atomic variable and return it&n; * @i: integer value to add&n; * @v: pointer of type atomic_t&n; *&n; * Atomically adds @i to @v and return (@i + @v).&n; */
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
id|result
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# atomic_add_return&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|M32R_LOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;add&t;%0, %2;&t;&t;&t;&bslash;n&bslash;t&quot;
id|M32R_UNLOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
comma
l_string|&quot;r&quot;
(paren
id|i
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r4&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_sub_return - subtract integer from atomic variable and return it&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; *&n; * Atomically subtracts @i from @v and return (@v - @i).&n; */
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
id|result
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# atomic_sub_return&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|M32R_LOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;sub&t;%0, %2;&t;&t;&t;&bslash;n&bslash;t&quot;
id|M32R_UNLOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
comma
l_string|&quot;r&quot;
(paren
id|i
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r4&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_add - add integer to atomic variable&n; * @i: integer value to add&n; * @v: pointer of type atomic_t&n; *&n; * Atomically adds @i to @v.&n; */
DECL|macro|atomic_add
mdefine_line|#define atomic_add(i,v) ((void) atomic_add_return((i), (v)))
multiline_comment|/**&n; * atomic_sub - subtract the atomic variable&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; *&n; * Atomically subtracts @i from @v.&n; */
DECL|macro|atomic_sub
mdefine_line|#define atomic_sub(i,v) ((void) atomic_sub_return((i), (v)))
multiline_comment|/**&n; * atomic_sub_and_test - subtract value from variable and test result&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; *&n; * Atomically subtracts @i from @v and returns&n; * true if the result is zero, or false for all&n; * other cases.&n; */
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(i,v) (atomic_sub_return((i), (v)) == 0)
multiline_comment|/**&n; * atomic_inc_return - increment atomic variable and return it&n; * @v: pointer of type atomic_t&n; *&n; * Atomically increments @v by 1 and returns the result.&n; */
DECL|function|atomic_inc_return
r_static
id|__inline__
r_int
id|atomic_inc_return
c_func
(paren
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
id|result
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# atomic_inc_return&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|M32R_LOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #1;&t;&t;&t;&bslash;n&bslash;t&quot;
id|M32R_UNLOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r4&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_dec_return - decrement atomic variable and return it&n; * @v: pointer of type atomic_t&n; *&n; * Atomically decrements @v by 1 and returns the result.&n; */
DECL|function|atomic_dec_return
r_static
id|__inline__
r_int
id|atomic_dec_return
c_func
(paren
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
id|result
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# atomic_dec_return&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|M32R_LOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1;&t;&t;&bslash;n&bslash;t&quot;
id|M32R_UNLOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r4&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_inc - increment atomic variable&n; * @v: pointer of type atomic_t&n; *&n; * Atomically increments @v by 1.&n; */
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) ((void)atomic_inc_return(v))
multiline_comment|/**&n; * atomic_dec - decrement atomic variable&n; * @v: pointer of type atomic_t&n; *&n; * Atomically decrements @v by 1.&n; */
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) ((void)atomic_dec_return(v))
multiline_comment|/**&n; * atomic_inc_and_test - increment and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically increments @v by 1&n; * and returns true if the result is zero, or false for all&n; * other cases.&n; */
DECL|macro|atomic_inc_and_test
mdefine_line|#define atomic_inc_and_test(v) (atomic_inc_return(v) == 0)
multiline_comment|/**&n; * atomic_dec_and_test - decrement and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically decrements @v by 1 and&n; * returns true if the result is 0, or false for all&n; * other cases.&n; */
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v) (atomic_dec_return(v) == 0)
multiline_comment|/**&n; * atomic_add_negative - add and test if negative&n; * @v: pointer of type atomic_t&n; * @i: integer value to add&n; *&n; * Atomically adds @i to @v and returns true&n; * if the result is negative, or false when&n; * result is greater than or equal to zero.&n; */
DECL|macro|atomic_add_negative
mdefine_line|#define atomic_add_negative(i,v) (atomic_add_return((i), (v)) &lt; 0)
DECL|function|atomic_clear_mask
r_static
id|__inline__
r_void
id|atomic_clear_mask
c_func
(paren
r_int
r_int
id|mask
comma
id|atomic_t
op_star
id|addr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# atomic_clear_mask&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r5&quot;
comma
l_string|&quot;%1&quot;
)paren
id|M32R_LOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;and&t;%0, %2;&t;&t;&t;&bslash;n&bslash;t&quot;
id|M32R_UNLOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
op_complement
id|mask
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r5&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|atomic_set_mask
r_static
id|__inline__
r_void
id|atomic_set_mask
c_func
(paren
r_int
r_int
id|mask
comma
id|atomic_t
op_star
id|addr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# atomic_set_mask&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r5&quot;
comma
l_string|&quot;%1&quot;
)paren
id|M32R_LOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%0, %2;&t;&t;&t;&bslash;n&bslash;t&quot;
id|M32R_UNLOCK
l_string|&quot; %0, @%1;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r5&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Atomic operations are already serializing on m32r */
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;barrier()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;barrier()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;barrier()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;barrier()
macro_line|#endif&t;/* _ASM_M32R_ATOMIC_H */
eof
