multiline_comment|/*&n; * BK Id: SCCS/s.hardirq.h 1.10 06/09/01 22:16:38 paulus&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
multiline_comment|/* entry.S is sensitive to the offsets of these fields */
multiline_comment|/* The __last_jiffy_stamp field is needed to ensure that no decrementer &n; * interrupt is lost on SMP machines. Since on most CPUs it is in the same &n; * cache line as local_irq_count, it is cheap to access and is also used on UP &n; * for uniformity.&n; */
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
multiline_comment|/* set_bit is used on this */
DECL|member|__local_irq_count
r_int
r_int
id|__local_irq_count
suffix:semicolon
DECL|member|__local_bh_count
r_int
r_int
id|__local_bh_count
suffix:semicolon
DECL|member|__syscall_count
r_int
r_int
id|__syscall_count
suffix:semicolon
DECL|member|__last_jiffy_stamp
r_int
r_int
id|__last_jiffy_stamp
suffix:semicolon
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
DECL|macro|last_jiffy_stamp
mdefine_line|#define last_jiffy_stamp(cpu) __IRQ_STAT((cpu), __last_jiffy_stamp)
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt() ({ int __cpu = smp_processor_id(); &bslash;&n;&t;(local_irq_count(__cpu) + local_bh_count(__cpu) != 0); })
DECL|macro|in_irq
mdefine_line|#define in_irq() (local_irq_count(smp_processor_id()) != 0)
macro_line|#ifndef CONFIG_SMP
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;(local_irq_count(cpu) == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|hardirq_enter
mdefine_line|#define hardirq_enter(cpu)&t;(local_irq_count(cpu)++)
DECL|macro|hardirq_exit
mdefine_line|#define hardirq_exit(cpu)&t;(local_irq_count(cpu)--)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;do { } while (0)
macro_line|#else /* CONFIG_SMP */
macro_line|#include &lt;asm/atomic.h&gt;
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
r_extern
id|atomic_t
id|global_irq_count
suffix:semicolon
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
DECL|function|hardirq_enter
r_static
r_inline
r_void
id|hardirq_enter
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
r_int
id|loops
op_assign
l_int|10000000
suffix:semicolon
op_increment
id|local_irq_count
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|global_irq_count
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
r_if
c_cond
(paren
id|cpu
op_eq
id|global_irq_holder
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;uh oh, interrupt while we hold global irq lock! (CPU %d)&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
id|xmon
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loops
op_decrement
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;do_IRQ waiting for irq lock (holder=%d)&bslash;n&quot;
comma
id|global_irq_holder
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
id|xmon
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
)brace
DECL|function|hardirq_exit
r_static
r_inline
r_void
id|hardirq_exit
c_func
(paren
r_int
id|cpu
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|global_irq_count
)paren
suffix:semicolon
op_decrement
id|local_irq_count
c_func
(paren
id|cpu
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
id|atomic_read
c_func
(paren
op_amp
id|global_irq_count
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
macro_line|#endif /* __KERNEL__ */
eof
