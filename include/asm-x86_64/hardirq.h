macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
DECL|macro|__ARCH_IRQ_STAT
mdefine_line|#define __ARCH_IRQ_STAT 1
multiline_comment|/* Generate a lvalue for a pda member. Should fix softirq.c instead to use&n;   special access macros. This would generate better code. */
DECL|macro|__IRQ_STAT
mdefine_line|#define __IRQ_STAT(cpu,member) (read_pda(me)-&gt;member)
r_typedef
r_struct
(brace
multiline_comment|/* Empty. All the fields have moved to the PDA. */
DECL|typedef|irq_cpustat_t
)brace
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt() &bslash;&n;&t;((read_pda(__local_irq_count) +  read_pda(__local_bh_count)) != 0)
DECL|macro|in_irq
mdefine_line|#define in_irq() (read_pda(__local_irq_count) != 0)
macro_line|#ifndef CONFIG_SMP
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;(local_irq_count() == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu, irq)&t;(local_irq_count()++)
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu, irq)&t;(local_irq_count()--)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;barrier()
DECL|macro|release_irqlock
mdefine_line|#define release_irqlock(cpu)&t;do { } while (0)
macro_line|#else
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
r_extern
r_int
r_char
id|global_irq_holder
suffix:semicolon
r_extern
r_int
r_volatile
r_int
id|global_irq_lock
suffix:semicolon
multiline_comment|/* long for set_bit -RR */
DECL|function|irqs_running
r_static
r_inline
r_int
id|irqs_running
(paren
r_void
)paren
(brace
r_int
id|i
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|read_pda
c_func
(paren
id|__local_irq_count
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|release_irqlock
r_static
r_inline
r_void
id|release_irqlock
c_func
(paren
r_int
id|cpu
)paren
(brace
multiline_comment|/* if we didn&squot;t own the irq lock, just ignore.. */
r_if
c_cond
(paren
id|global_irq_holder
op_eq
(paren
r_int
r_char
)paren
id|cpu
)paren
(brace
id|global_irq_holder
op_assign
id|NO_PROC_ID
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|irq_enter
r_static
r_inline
r_void
id|irq_enter
c_func
(paren
r_int
id|cpu
comma
r_int
id|irq
)paren
(brace
id|add_pda
c_func
(paren
id|__local_irq_count
comma
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
)paren
(brace
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|irq_exit
r_static
r_inline
r_void
id|irq_exit
c_func
(paren
r_int
id|cpu
comma
r_int
id|irq
)paren
(brace
id|sub_pda
c_func
(paren
id|__local_irq_count
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|hardirq_trylock
r_static
r_inline
r_int
id|hardirq_trylock
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
op_logical_neg
id|read_pda
c_func
(paren
id|__local_irq_count
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
suffix:semicolon
)brace
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
r_extern
r_void
id|synchronize_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __ASM_HARDIRQ_H */
eof