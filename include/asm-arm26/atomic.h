multiline_comment|/*&n; *  linux/include/asm-arm26/atomic.h&n; *&n; *  Copyright (c) 1996 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   27-06-1996&t;RMK&t;Created&n; *   13-04-1997&t;RMK&t;Made functions atomic!&n; *   07-12-1997&t;RMK&t;Upgraded for v2.1.&n; *   26-08-1998&t;PJB&t;Added #ifdef __KERNEL__&n; *&n; *  FIXME - its probably worth seeing what these compile into...&n; */
macro_line|#ifndef __ASM_ARM_ATOMIC_H
DECL|macro|__ASM_ARM_ATOMIC_H
mdefine_line|#define __ASM_ARM_ATOMIC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#error SMP is NOT supported
macro_line|#endif
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
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;(((v)-&gt;counter) = (i))
DECL|function|atomic_add
r_static
r_inline
r_void
id|atomic_add
c_func
(paren
r_int
id|i
comma
r_volatile
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
id|v-&gt;counter
op_add_assign
id|i
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|atomic_sub
r_static
r_inline
r_void
id|atomic_sub
c_func
(paren
r_int
id|i
comma
r_volatile
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
id|v-&gt;counter
op_sub_assign
id|i
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|atomic_inc
r_static
r_inline
r_void
id|atomic_inc
c_func
(paren
r_volatile
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
id|v-&gt;counter
op_add_assign
l_int|1
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|atomic_dec
r_static
r_inline
r_void
id|atomic_dec
c_func
(paren
r_volatile
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
id|v-&gt;counter
op_sub_assign
l_int|1
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|atomic_dec_and_test
r_static
r_inline
r_int
id|atomic_dec_and_test
c_func
(paren
r_volatile
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
l_int|1
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|val
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|atomic_add_negative
r_static
r_inline
r_int
id|atomic_add_negative
c_func
(paren
r_int
id|i
comma
r_volatile
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
OL
l_int|0
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
r_volatile
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
op_plus
id|i
suffix:semicolon
id|v-&gt;counter
op_assign
id|val
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
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_return
id|atomic_add_return
c_func
(paren
op_minus
id|i
comma
id|v
)paren
suffix:semicolon
)brace
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v)  (atomic_add_return(1,v))
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v)  (atomic_sub_return(1,v))
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
