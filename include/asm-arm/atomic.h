multiline_comment|/*&n; *  linux/include/asm-arm/atomic.h&n; *&n; *  Copyright (C) 1996 Russell King.&n; *  Copyright (C) 2002 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_ATOMIC_H
DECL|macro|__ASM_ARM_ATOMIC_H
mdefine_line|#define __ASM_ARM_ATOMIC_H
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#ifdef __KERNEL__
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;((v)-&gt;counter)
macro_line|#if __LINUX_ARM_ARCH__ &gt;= 6
multiline_comment|/*&n; * ARMv6 UP and SMP safe atomic ops.  We use load exclusive and&n; * store exclusive to ensure that these are atomic.  We may loop&n; * to ensure that the update happens.  Writing to &squot;v-&gt;counter&squot;&n; * without using the following operations WILL break the atomic&n; * nature of these ops.&n; */
DECL|function|atomic_set
r_static
r_inline
r_void
id|atomic_set
c_func
(paren
id|atomic_t
op_star
id|v
comma
r_int
id|i
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;@ atomic_set&bslash;n&quot;
l_string|&quot;1:&t;ldrex&t;%0, [%1]&bslash;n&quot;
l_string|&quot;&t;strex&t;%0, %2, [%1]&bslash;n&quot;
l_string|&quot;&t;teq&t;%0, #0&bslash;n&quot;
l_string|&quot;&t;bne&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
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
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_add_return
r_static
r_inline
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
id|tmp
suffix:semicolon
r_int
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;@ atomic_add_return&bslash;n&quot;
l_string|&quot;1:&t;ldrex&t;%0, [%2]&bslash;n&quot;
l_string|&quot;&t;add&t;%0, %0, %3&bslash;n&quot;
l_string|&quot;&t;strex&t;%1, %0, [%2]&bslash;n&quot;
l_string|&quot;&t;teq&t;%1, #0&bslash;n&quot;
l_string|&quot;&t;bne&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
comma
l_string|&quot;Ir&quot;
(paren
id|i
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|atomic_sub_return
r_static
r_inline
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
id|tmp
suffix:semicolon
r_int
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;@ atomic_sub_return&bslash;n&quot;
l_string|&quot;1:&t;ldrex&t;%0, [%2]&bslash;n&quot;
l_string|&quot;&t;sub&t;%0, %0, %3&bslash;n&quot;
l_string|&quot;&t;strex&t;%1, %0, [%2]&bslash;n&quot;
l_string|&quot;&t;teq&t;%1, #0&bslash;n&quot;
l_string|&quot;&t;bne&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|v-&gt;counter
)paren
comma
l_string|&quot;Ir&quot;
(paren
id|i
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|atomic_clear_mask
r_static
r_inline
r_void
id|atomic_clear_mask
c_func
(paren
r_int
r_int
id|mask
comma
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
r_int
id|tmp
comma
id|tmp2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;@ atomic_clear_mask&bslash;n&quot;
l_string|&quot;1:&t;ldrex&t;%0, %2&bslash;n&quot;
l_string|&quot;&t;bic&t;%0, %0, %3&bslash;n&quot;
l_string|&quot;&t;strex&t;%1, %0, %2&bslash;n&quot;
l_string|&quot;&t;teq&t;%1, #0&bslash;n&quot;
l_string|&quot;&t;bne&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;Ir&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
macro_line|#else /* ARM_ARCH_6 */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#error SMP not supported on pre-ARMv6 CPUs
macro_line|#endif
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;(((v)-&gt;counter) = (i))
DECL|function|atomic_add_return
r_static
r_inline
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
id|val
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|v-&gt;counter
suffix:semicolon
id|v-&gt;counter
op_assign
id|val
op_add_assign
id|i
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|atomic_sub_return
r_static
r_inline
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
id|val
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|v-&gt;counter
suffix:semicolon
id|v-&gt;counter
op_assign
id|val
op_sub_assign
id|i
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|atomic_clear_mask
r_static
r_inline
r_void
id|atomic_clear_mask
c_func
(paren
r_int
r_int
id|mask
comma
r_int
r_int
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
op_star
id|addr
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
macro_line|#endif /* __LINUX_ARM_ARCH__ */
DECL|macro|atomic_add
mdefine_line|#define atomic_add(i, v)&t;(void) atomic_add_return(i, v)
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v)&t;&t;(void) atomic_add_return(1, v)
DECL|macro|atomic_sub
mdefine_line|#define atomic_sub(i, v)&t;(void) atomic_sub_return(i, v)
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v)&t;&t;(void) atomic_sub_return(1, v)
DECL|macro|atomic_inc_and_test
mdefine_line|#define atomic_inc_and_test(v)&t;(atomic_add_return(1, v) == 0)
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v)&t;(atomic_sub_return(1, v) == 0)
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v)    (atomic_add_return(1, v))
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v)    (atomic_sub_return(1, v))
DECL|macro|atomic_add_negative
mdefine_line|#define atomic_add_negative(i,v) (atomic_add_return(i, v) &lt; 0)
multiline_comment|/* Atomic operations are already serializing on ARM */
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;barrier()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;barrier()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;barrier()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;barrier()
macro_line|#endif
macro_line|#endif
eof
