macro_line|#ifndef _ASM_M32R_ATOMIC_H
DECL|macro|_ASM_M32R_ATOMIC_H
mdefine_line|#define _ASM_M32R_ATOMIC_H
multiline_comment|/* $Id$ */
multiline_comment|/*&n; *  linux/include/asm-m32r/atomic.h&n; *    orig : i386 2.4.10&n; *&n; *  M32R version:&n; *    Copyright (C) 2001, 2002  Hitoshi Yamamoto&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; */
DECL|macro|LOAD
macro_line|#undef LOAD
DECL|macro|STORE
macro_line|#undef STORE
macro_line|#ifdef CONFIG_SMP
DECL|macro|LOAD
mdefine_line|#define LOAD&t;&quot;lock&quot;
DECL|macro|STORE
mdefine_line|#define STORE&t;&quot;unlock&quot;
macro_line|#else
DECL|macro|LOAD
mdefine_line|#define LOAD&t;&quot;ld&quot;
DECL|macro|STORE
mdefine_line|#define STORE&t;&quot;st&quot;
macro_line|#endif
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
multiline_comment|/**&n; * atomic_read - read atomic variable&n; * @v: pointer of type atomic_t&n; *&n; * Atomically reads the value of @v.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;((v)-&gt;counter)
multiline_comment|/**&n; * atomic_set - set atomic variable&n; * @v: pointer of type atomic_t&n; * @i: required value&n; *&n; * Atomically sets the value of @v to @i.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;(((v)-&gt;counter) = (i))
multiline_comment|/**&n; * atomic_add - add integer to atomic variable&n; * @i: integer value to add&n; * @v: pointer of type atomic_t&n; *&n; * Atomically adds @i to @v.  Note that the guaranteed useful range&n; * of an atomic_t is only 24 bits.&n; */
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
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# atomic_add&t;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;r4&quot;
comma
l_string|&quot;r5&quot;
comma
l_string|&quot;%0&quot;
)paren
id|LOAD
l_string|&quot;&t;r4, @%0;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;add&t;r4, %1;&t;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;r4, @%0;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* no outputs */
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
comma
l_string|&quot;r4&quot;
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
multiline_comment|/**&n; * atomic_sub - subtract the atomic variable&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; *&n; * Atomically subtracts @i from @v.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
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
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# atomic_sub&t;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;r4&quot;
comma
l_string|&quot;r5&quot;
comma
l_string|&quot;%0&quot;
)paren
id|LOAD
l_string|&quot;&t;r4, @%0;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;sub&t;r4, %1;&t;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;r4, @%0;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* no outputs */
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
comma
l_string|&quot;r4&quot;
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
multiline_comment|/**&n; * atomic_sub_and_test - subtract value from variable and test result&n; * @i: integer value to subtract&n; * @v: pointer of type atomic_t&n; *&n; * Atomically subtracts @i from @v and returns&n; * true if the result is zero, or false for all&n; * other cases.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|function|atomic_sub_and_test
r_static
id|__inline__
r_int
id|atomic_sub_and_test
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
l_string|&quot;# atomic_sub_and_test&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|LOAD
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;sub&t;%0, %2;&t;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
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
(paren
id|result
op_eq
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_inc - increment atomic variable&n; * @v: pointer of type atomic_t&n; *&n; * Atomically increments @v by 1.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|function|atomic_inc
r_static
id|__inline__
r_void
id|atomic_inc
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
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# atomic_inc&t;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;r4&quot;
comma
l_string|&quot;r5&quot;
comma
l_string|&quot;%0&quot;
)paren
id|LOAD
l_string|&quot;&t;r4, @%0; &t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;r4, #1;&t;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;r4, @%0;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;r4&quot;
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
multiline_comment|/**&n; * atomic_dec - decrement atomic variable&n; * @v: pointer of type atomic_t&n; *&n; * Atomically decrements @v by 1.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|function|atomic_dec
r_static
id|__inline__
r_void
id|atomic_dec
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
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;# atomic_dec&t;&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;r4&quot;
comma
l_string|&quot;r5&quot;
comma
l_string|&quot;%0&quot;
)paren
id|LOAD
l_string|&quot;&t;r4, @%0;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;r4, #-1;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;r4, @%0;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;r4&quot;
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
multiline_comment|/**&n; * atomic_dec_and_test - decrement and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically decrements @v by 1 and&n; * returns true if the result is 0, or false for all other&n; * cases.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|function|atomic_dec_and_test
r_static
id|__inline__
r_int
id|atomic_dec_and_test
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
l_string|&quot;# atomic_dec_and_test&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|LOAD
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #-1;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
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
(paren
id|result
op_eq
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_inc_and_test - increment and test&n; * @v: pointer of type atomic_t&n; *&n; * Atomically increments @v by 1&n; * and returns true if the result is zero, or false for all&n; * other cases.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|function|atomic_inc_and_test
r_static
id|__inline__
r_int
id|atomic_inc_and_test
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
l_string|&quot;# atomic_dec_and_test&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|LOAD
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;addi&t;%0, #1;&t;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
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
(paren
id|result
op_eq
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * atomic_add_negative - add and test if negative&n; * @v: pointer of type atomic_t&n; * @i: integer value to add&n; *&n; * Atomically adds @i to @v and returns true&n; * if the result is negative, or false when&n; * result is greater than or equal to zero.  Note that the guaranteed&n; * useful range of an atomic_t is only 24 bits.&n; */
DECL|function|atomic_add_negative
r_static
id|__inline__
r_int
id|atomic_add_negative
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
l_string|&quot;# atomic_add_negative&t;&t;&bslash;n&bslash;t&quot;
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%1&quot;
)paren
id|LOAD
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;add&t;%0, %2;&t;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;%0, @%1;&t;&t;&bslash;n&bslash;t&quot;
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
(paren
id|result
OL
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* These are x86-specific, used by some header files */
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
l_string|&quot;r4&quot;
comma
l_string|&quot;r5&quot;
comma
l_string|&quot;%0&quot;
)paren
id|LOAD
l_string|&quot;&t;r4, @%0;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;or&t;r4, %1;&t;&t;&t;&bslash;n&bslash;t&quot;
id|STORE
l_string|&quot;&t;r4, @%0;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* no outputs */
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
comma
l_string|&quot;r4&quot;
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
multiline_comment|/* Atomic operations are already serializing on x86 */
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
