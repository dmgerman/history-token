macro_line|#ifndef _ASM_GENERIC_LOCAL_H
DECL|macro|_ASM_GENERIC_LOCAL_H
mdefine_line|#define _ASM_GENERIC_LOCAL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
multiline_comment|/* An unsigned long type for operations which are atomic for a single&n; * CPU.  Usually used in combination with per-cpu variables. */
macro_line|#if BITS_PER_LONG == 32 &amp;&amp; !defined(CONFIG_SPARC32)
multiline_comment|/* Implement in terms of atomics. */
multiline_comment|/* Don&squot;t use typedef: don&squot;t want them to be mixed with atomic_t&squot;s. */
r_typedef
r_struct
(brace
DECL|member|a
id|atomic_t
id|a
suffix:semicolon
DECL|typedef|local_t
)brace
id|local_t
suffix:semicolon
DECL|macro|LOCAL_INIT
mdefine_line|#define LOCAL_INIT(i)&t;{ ATOMIC_INIT(i) }
DECL|macro|local_read
mdefine_line|#define local_read(l)&t;((unsigned long)atomic_read(&amp;(l)-&gt;a))
DECL|macro|local_set
mdefine_line|#define local_set(l,i)&t;atomic_set((&amp;(l)-&gt;a),(i))
DECL|macro|local_inc
mdefine_line|#define local_inc(l)&t;atomic_inc(&amp;(l)-&gt;a)
DECL|macro|local_dec
mdefine_line|#define local_dec(l)&t;atomic_dec(&amp;(l)-&gt;a)
DECL|macro|local_add
mdefine_line|#define local_add(i,l)&t;atomic_add((i),(&amp;(l)-&gt;a))
DECL|macro|local_sub
mdefine_line|#define local_sub(i,l)&t;atomic_sub((i),(&amp;(l)-&gt;a))
multiline_comment|/* Non-atomic variants, ie. preemption disabled and won&squot;t be touched&n; * in interrupt, etc.  Some archs can optimize this case well. */
DECL|macro|__local_inc
mdefine_line|#define __local_inc(l)&t;&t;local_set((l), local_read(l) + 1)
DECL|macro|__local_dec
mdefine_line|#define __local_dec(l)&t;&t;local_set((l), local_read(l) - 1)
DECL|macro|__local_add
mdefine_line|#define __local_add(i,l)&t;local_set((l), local_read(l) + (i))
DECL|macro|__local_sub
mdefine_line|#define __local_sub(i,l)&t;local_set((l), local_read(l) - (i))
macro_line|#else /* ... can&squot;t use atomics. */
multiline_comment|/* Implement in terms of three variables.&n;   Another option would be to use local_irq_save/restore. */
r_typedef
r_struct
(brace
multiline_comment|/* 0 = in hardirq, 1 = in softirq, 2 = usermode. */
DECL|member|v
r_int
r_int
id|v
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|local_t
)brace
id|local_t
suffix:semicolon
DECL|macro|_LOCAL_VAR
mdefine_line|#define _LOCAL_VAR(l)&t;((l)-&gt;v[!in_interrupt() + !in_irq()])
DECL|macro|LOCAL_INIT
mdefine_line|#define LOCAL_INIT(i)&t;{ { (i), 0, 0 } }
DECL|function|local_read
r_static
r_inline
r_int
r_int
id|local_read
c_func
(paren
id|local_t
op_star
id|l
)paren
(brace
r_return
id|l-&gt;v
(braket
l_int|0
)braket
op_plus
id|l-&gt;v
(braket
l_int|1
)braket
op_plus
id|l-&gt;v
(braket
l_int|2
)braket
suffix:semicolon
)brace
DECL|function|local_set
r_static
r_inline
r_void
id|local_set
c_func
(paren
id|local_t
op_star
id|l
comma
r_int
r_int
id|v
)paren
(brace
id|l-&gt;v
(braket
l_int|0
)braket
op_assign
id|v
suffix:semicolon
id|l-&gt;v
(braket
l_int|1
)braket
op_assign
id|l-&gt;v
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|local_inc
r_static
r_inline
r_void
id|local_inc
c_func
(paren
id|local_t
op_star
id|l
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_LOCAL_VAR
c_func
(paren
id|l
)paren
op_increment
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|local_dec
r_static
r_inline
r_void
id|local_dec
c_func
(paren
id|local_t
op_star
id|l
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_LOCAL_VAR
c_func
(paren
id|l
)paren
op_decrement
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|local_add
r_static
r_inline
r_void
id|local_add
c_func
(paren
r_int
r_int
id|v
comma
id|local_t
op_star
id|l
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_LOCAL_VAR
c_func
(paren
id|l
)paren
op_add_assign
id|v
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|local_sub
r_static
r_inline
r_void
id|local_sub
c_func
(paren
r_int
r_int
id|v
comma
id|local_t
op_star
id|l
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_LOCAL_VAR
c_func
(paren
id|l
)paren
op_sub_assign
id|v
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Non-atomic variants, ie. preemption disabled and won&squot;t be touched&n; * in interrupt, etc.  Some archs can optimize this case well. */
DECL|macro|__local_inc
mdefine_line|#define __local_inc(l)&t;&t;((l)-&gt;v[0]++)
DECL|macro|__local_dec
mdefine_line|#define __local_dec(l)&t;&t;((l)-&gt;v[0]--)
DECL|macro|__local_add
mdefine_line|#define __local_add(i,l)&t;((l)-&gt;v[0] += (i))
DECL|macro|__local_sub
mdefine_line|#define __local_sub(i,l)&t;((l)-&gt;v[0] -= (i))
macro_line|#endif /* Non-atomic implementation */
multiline_comment|/* Use these for per-cpu local_t variables: on some archs they are&n; * much more efficient than these naive implementations.  Note they take&n; * a variable (eg. mystruct.foo), not an address.&n; */
DECL|macro|cpu_local_read
mdefine_line|#define cpu_local_read(v)&t;local_read(&amp;__get_cpu_var(v))
DECL|macro|cpu_local_set
mdefine_line|#define cpu_local_set(v, i)&t;local_set(&amp;__get_cpu_var(v), (i))
DECL|macro|cpu_local_inc
mdefine_line|#define cpu_local_inc(v)&t;local_inc(&amp;__get_cpu_var(v))
DECL|macro|cpu_local_dec
mdefine_line|#define cpu_local_dec(v)&t;local_dec(&amp;__get_cpu_var(v))
DECL|macro|cpu_local_add
mdefine_line|#define cpu_local_add(i, v)&t;local_add((i), &amp;__get_cpu_var(v))
DECL|macro|cpu_local_sub
mdefine_line|#define cpu_local_sub(i, v)&t;local_sub((i), &amp;__get_cpu_var(v))
multiline_comment|/* Non-atomic increments, ie. preemption disabled and won&squot;t be touched&n; * in interrupt, etc.  Some archs can optimize this case well.&n; */
DECL|macro|__cpu_local_inc
mdefine_line|#define __cpu_local_inc(v)&t;__local_inc(&amp;__get_cpu_var(v))
DECL|macro|__cpu_local_dec
mdefine_line|#define __cpu_local_dec(v)&t;__local_dec(&amp;__get_cpu_var(v))
DECL|macro|__cpu_local_add
mdefine_line|#define __cpu_local_add(i, v)&t;__local_add((i), &amp;__get_cpu_var(v))
DECL|macro|__cpu_local_sub
mdefine_line|#define __cpu_local_sub(i, v)&t;__local_sub((i), &amp;__get_cpu_var(v))
macro_line|#endif /* _ASM_GENERIC_LOCAL_H */
eof
