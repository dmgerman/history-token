macro_line|#ifndef __LINUX_PERCPU_H
DECL|macro|__LINUX_PERCPU_H
mdefine_line|#define __LINUX_PERCPU_H
macro_line|#include &lt;linux/spinlock.h&gt; /* For preempt_disable() */
macro_line|#include &lt;linux/slab.h&gt; /* For kmalloc_percpu() */
macro_line|#include &lt;asm/percpu.h&gt;
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
multiline_comment|/* &n; * Use this to get to a cpu&squot;s version of the per-cpu object allocated using&n; * kmalloc_percpu.  If you want to get &quot;this cpu&squot;s version&quot;, maybe you want&n; * to use get_cpu_ptr... &n; */
DECL|macro|per_cpu_ptr
mdefine_line|#define per_cpu_ptr(ptr, cpu)                   &bslash;&n;({                                              &bslash;&n;        struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(ptr); &bslash;&n;        (__typeof__(ptr))__p-&gt;ptrs[(cpu)];&t;&bslash;&n;})
r_extern
r_void
op_star
id|kmalloc_percpu
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|kfree_percpu
c_func
(paren
r_const
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|kmalloc_percpu_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else /* CONFIG_SMP */
DECL|macro|per_cpu_ptr
mdefine_line|#define per_cpu_ptr(ptr, cpu) (ptr)
DECL|function|kmalloc_percpu
r_static
r_inline
r_void
op_star
id|kmalloc_percpu
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|kfree_percpu
r_static
r_inline
r_void
id|kfree_percpu
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
DECL|function|kmalloc_percpu_init
r_static
r_inline
r_void
id|kmalloc_percpu_init
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/* &n; * Use these with kmalloc_percpu. If&n; * 1. You want to operate on memory allocated by kmalloc_percpu (dereference&n; *    and read/modify/write)  AND &n; * 2. You want &quot;this cpu&squot;s version&quot; of the object AND &n; * 3. You want to do this safely since:&n; *    a. On multiprocessors, you don&squot;t want to switch between cpus after &n; *    you&squot;ve read the current processor id due to preemption -- this would &n; *    take away the implicit  advantage to not have any kind of traditional &n; *    serialization for per-cpu data&n; *    b. On uniprocessors, you don&squot;t want another kernel thread messing&n; *    up with the same per-cpu data due to preemption&n; *    &n; * So, Use get_cpu_ptr to disable preemption and get pointer to the &n; * local cpu version of the per-cpu object. Use put_cpu_ptr to enable&n; * preemption.  Operations on per-cpu data between get_ and put_ is&n; * then considered to be safe. And ofcourse, &quot;Thou shalt not sleep between &n; * get_cpu_ptr and put_cpu_ptr&quot;&n; */
DECL|macro|get_cpu_ptr
mdefine_line|#define get_cpu_ptr(ptr) per_cpu_ptr(ptr, get_cpu())
DECL|macro|put_cpu_ptr
mdefine_line|#define put_cpu_ptr(ptr) put_cpu()
macro_line|#endif /* __LINUX_PERCPU_H */
eof
