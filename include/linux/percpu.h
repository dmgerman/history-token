macro_line|#ifndef __LINUX_PERCPU_H
DECL|macro|__LINUX_PERCPU_H
mdefine_line|#define __LINUX_PERCPU_H
macro_line|#include &lt;linux/spinlock.h&gt; /* For preempt_disable() */
macro_line|#include &lt;linux/slab.h&gt; /* For kmalloc() */
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/string.h&gt; /* For memset() */
macro_line|#include &lt;asm/percpu.h&gt;
multiline_comment|/* Enough to cover all DEFINE_PER_CPUs in kernel, including modules. */
macro_line|#ifndef PERCPU_ENOUGH_ROOM
DECL|macro|PERCPU_ENOUGH_ROOM
mdefine_line|#define PERCPU_ENOUGH_ROOM 32768
macro_line|#endif
multiline_comment|/* Must be an lvalue. */
DECL|macro|get_cpu_var
mdefine_line|#define get_cpu_var(var) (*({ preempt_disable(); &amp;__get_cpu_var(var); }))
DECL|macro|put_cpu_var
mdefine_line|#define put_cpu_var(var) preempt_enable()
macro_line|#ifdef CONFIG_SMP
DECL|struct|percpu_data
r_struct
id|percpu_data
(brace
DECL|member|ptrs
r_void
op_star
id|ptrs
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|member|blkp
r_void
op_star
id|blkp
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Use this to get to a cpu&squot;s version of the per-cpu object allocated using&n; * alloc_percpu.  Non-atomic access to the current CPU&squot;s version should&n; * probably be combined with get_cpu()/put_cpu().&n; */
DECL|macro|per_cpu_ptr
mdefine_line|#define per_cpu_ptr(ptr, cpu)                   &bslash;&n;({                                              &bslash;&n;        struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(ptr); &bslash;&n;        (__typeof__(ptr))__p-&gt;ptrs[(cpu)];&t;&bslash;&n;})
r_extern
r_void
op_star
id|__alloc_percpu
c_func
(paren
r_int
id|size
comma
r_int
id|align
)paren
suffix:semicolon
r_extern
r_void
id|free_percpu
c_func
(paren
r_const
r_void
op_star
)paren
suffix:semicolon
macro_line|#else /* CONFIG_SMP */
DECL|macro|per_cpu_ptr
mdefine_line|#define per_cpu_ptr(ptr, cpu) (ptr)
DECL|function|__alloc_percpu
r_static
r_inline
r_void
op_star
id|__alloc_percpu
c_func
(paren
r_int
id|size
comma
r_int
id|align
)paren
(brace
r_void
op_star
id|ret
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|free_percpu
r_static
r_inline
r_void
id|free_percpu
c_func
(paren
r_const
r_void
op_star
id|ptr
)paren
(brace
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/* Simple wrapper for the common case: zeros memory. */
DECL|macro|alloc_percpu
mdefine_line|#define alloc_percpu(type) &bslash;&n;&t;((type *)(__alloc_percpu(sizeof(type), __alignof__(type))))
macro_line|#endif /* __LINUX_PERCPU_H */
eof
