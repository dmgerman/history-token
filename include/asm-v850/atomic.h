multiline_comment|/*&n; * include/asm-v850/atomic.h -- Atomic operations&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_ATOMIC_H__
DECL|macro|__V850_ATOMIC_H__
mdefine_line|#define __V850_ATOMIC_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#error SMP not supported
macro_line|#endif
DECL|member|counter
DECL|typedef|atomic_t
r_typedef
r_struct
(brace
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
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;&t;(((v)-&gt;counter) = (i))
DECL|function|atomic_add_return
r_extern
id|__inline__
r_int
id|atomic_add_return
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
id|res
suffix:semicolon
id|local_irq_save
(paren
id|flags
)paren
suffix:semicolon
id|res
op_assign
id|v-&gt;counter
op_plus
id|i
suffix:semicolon
id|v-&gt;counter
op_assign
id|res
suffix:semicolon
id|local_irq_restore
(paren
id|flags
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|atomic_sub_return
r_static
id|__inline__
r_int
id|atomic_sub_return
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
id|res
suffix:semicolon
id|local_irq_save
(paren
id|flags
)paren
suffix:semicolon
id|res
op_assign
id|v-&gt;counter
op_minus
id|i
suffix:semicolon
id|v-&gt;counter
op_assign
id|res
suffix:semicolon
id|local_irq_restore
(paren
id|flags
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|atomic_clear_mask
r_static
id|__inline__
r_void
id|atomic_clear_mask
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
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|atomic_add
mdefine_line|#define atomic_add(i, v)&t;atomic_add_return ((i), (v))
DECL|macro|atomic_sub
mdefine_line|#define atomic_sub(i, v)&t;atomic_sub_return ((i), (v))
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v)&t;atomic_sub_return (1, (v))
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v)&t;atomic_add_return (1, (v))
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) &t;&t;atomic_inc_return (v)
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) &t;&t;atomic_dec_return (v)
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(i,v)&t;(atomic_sub_return ((i), (v)) == 0)
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v)&t;&t;(atomic_sub_return (1, (v)) == 0)
DECL|macro|atomic_add_negative
mdefine_line|#define atomic_add_negative(i,v)&t;(atomic_add_return ((i), (v)) &lt; 0)
multiline_comment|/* Atomic operations are already serializing on ARM */
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()&t;barrier()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec()&t;barrier()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()&t;barrier()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc()&t;barrier()
macro_line|#endif /* __V850_ATOMIC_H__ */
eof
