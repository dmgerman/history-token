macro_line|#ifndef __ARCH_H8300_ATOMIC__
DECL|macro|__ARCH_H8300_ATOMIC__
mdefine_line|#define __ARCH_H8300_ATOMIC__
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; */
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
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v, i)&t;(((v)-&gt;counter) = i)
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
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
id|ret
comma
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ret
op_assign
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
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|atomic_add
mdefine_line|#define atomic_add(i, v) atomic_add_return(i, v)
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
id|ret
comma
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ret
op_assign
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
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|atomic_sub
mdefine_line|#define atomic_sub(i, v) atomic_sub_return(i, v)
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
id|ret
comma
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|v-&gt;counter
op_increment
suffix:semicolon
id|ret
op_assign
id|v-&gt;counter
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) atomic_inc_return(v)
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
id|ret
comma
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
op_decrement
id|v-&gt;counter
suffix:semicolon
id|ret
op_assign
id|v-&gt;counter
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) atomic_dec_return(v)
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
id|ret
comma
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
op_decrement
id|v-&gt;counter
suffix:semicolon
id|ret
op_assign
id|v-&gt;counter
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ret
op_eq
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(__H8300H__)
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
r_int
r_int
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc ccr,r2l&bslash;n&bslash;t&quot;
l_string|&quot;orc #0x80,ccr&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %0,er0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %1,er1&bslash;n&bslash;t&quot;
l_string|&quot;and.l er1,er0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l er0,%0&bslash;n&bslash;t&quot;
l_string|&quot;ldc r2l,ccr&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
op_complement
(paren
id|mask
)paren
)paren
suffix:colon
l_string|&quot;er0&quot;
comma
l_string|&quot;er1&quot;
comma
l_string|&quot;er2&quot;
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
r_int
r_int
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc ccr,r2l&bslash;n&bslash;t&quot;
l_string|&quot;orc #0x80,ccr&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %0,er0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %1,er1&bslash;n&bslash;t&quot;
l_string|&quot;or.l er1,er0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l er0,%0&bslash;n&bslash;t&quot;
l_string|&quot;ldc r2l,ccr&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;er0&quot;
comma
l_string|&quot;er1&quot;
comma
l_string|&quot;er2&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(__H8300S__)
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
r_int
r_int
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc exr,r2l&bslash;n&bslash;t&quot;
l_string|&quot;orc #0x07,exr&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %0,er0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %1,er1&bslash;n&bslash;t&quot;
l_string|&quot;and.l er1,er0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l er0,%0&bslash;n&bslash;t&quot;
l_string|&quot;ldc r2l,exr&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
op_complement
(paren
id|mask
)paren
)paren
suffix:colon
l_string|&quot;er0&quot;
comma
l_string|&quot;er1&quot;
comma
l_string|&quot;er2&quot;
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
r_int
r_int
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc exr,r2l&bslash;n&bslash;t&quot;
l_string|&quot;orc #0x07,exr&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %0,er0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %1,er1&bslash;n&bslash;t&quot;
l_string|&quot;or.l er1,er0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l er0,%0&bslash;n&bslash;t&quot;
l_string|&quot;ldc r2l,exr&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;ir&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;er0&quot;
comma
l_string|&quot;er1&quot;
comma
l_string|&quot;er2&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Atomic operations are already serializing */
DECL|macro|smp_mb__before_atomic_dec
mdefine_line|#define smp_mb__before_atomic_dec()    barrier()
DECL|macro|smp_mb__after_atomic_dec
mdefine_line|#define smp_mb__after_atomic_dec() barrier()
DECL|macro|smp_mb__before_atomic_inc
mdefine_line|#define smp_mb__before_atomic_inc()    barrier()
DECL|macro|smp_mb__after_atomic_inc
mdefine_line|#define smp_mb__after_atomic_inc() barrier()
macro_line|#endif /* __ARCH_H8300_ATOMIC __ */
eof
