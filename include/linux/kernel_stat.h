macro_line|#ifndef _LINUX_KERNEL_STAT_H
DECL|macro|_LINUX_KERNEL_STAT_H
mdefine_line|#define _LINUX_KERNEL_STAT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;asm/cputime.h&gt;
multiline_comment|/*&n; * &squot;kernel_stat.h&squot; contains the definitions needed for doing&n; * some kernel statistics (CPU usage, context switches ...),&n; * used by rstatd/perfmeter&n; */
DECL|struct|cpu_usage_stat
r_struct
id|cpu_usage_stat
(brace
DECL|member|user
id|cputime64_t
id|user
suffix:semicolon
DECL|member|nice
id|cputime64_t
id|nice
suffix:semicolon
DECL|member|system
id|cputime64_t
id|system
suffix:semicolon
DECL|member|softirq
id|cputime64_t
id|softirq
suffix:semicolon
DECL|member|irq
id|cputime64_t
id|irq
suffix:semicolon
DECL|member|idle
id|cputime64_t
id|idle
suffix:semicolon
DECL|member|iowait
id|cputime64_t
id|iowait
suffix:semicolon
DECL|member|steal
id|cputime64_t
id|steal
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kernel_stat
r_struct
id|kernel_stat
(brace
DECL|member|cpustat
r_struct
id|cpu_usage_stat
id|cpustat
suffix:semicolon
DECL|member|irqs
r_int
r_int
id|irqs
(braket
id|NR_IRQS
)braket
suffix:semicolon
)brace
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|kernel_stat
comma
id|kstat
)paren
suffix:semicolon
DECL|macro|kstat_cpu
mdefine_line|#define kstat_cpu(cpu)&t;per_cpu(kstat, cpu)
multiline_comment|/* Must have preemption disabled for this to be meaningful. */
DECL|macro|kstat_this_cpu
mdefine_line|#define kstat_this_cpu&t;__get_cpu_var(kstat)
r_extern
r_int
r_int
r_int
id|nr_context_switches
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Number of interrupts per specific IRQ source, since bootup&n; */
DECL|function|kstat_irqs
r_static
r_inline
r_int
id|kstat_irqs
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|i
comma
id|sum
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
id|sum
op_add_assign
id|kstat_cpu
c_func
(paren
id|i
)paren
dot
id|irqs
(braket
id|irq
)braket
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
r_extern
r_void
id|account_user_time
c_func
(paren
r_struct
id|task_struct
op_star
comma
id|cputime_t
)paren
suffix:semicolon
r_extern
r_void
id|account_system_time
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_int
comma
id|cputime_t
)paren
suffix:semicolon
r_extern
r_void
id|account_steal_time
c_func
(paren
r_struct
id|task_struct
op_star
comma
id|cputime_t
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_KERNEL_STAT_H */
eof
