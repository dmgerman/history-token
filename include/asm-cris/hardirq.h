macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
multiline_comment|/* only non-SMP supported */
macro_line|#include &lt;linux/threads.h&gt;
multiline_comment|/* entry.S is sensitive to the offsets of these fields */
r_typedef
r_struct
(brace
DECL|member|__softirq_active
r_int
r_int
id|__softirq_active
suffix:semicolon
DECL|member|__softirq_mask
r_int
r_int
id|__softirq_mask
suffix:semicolon
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
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt; /* Standard mappings for irq_cpustat_t above */
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt()  ((local_irq_count(smp_processor_id()) + &bslash;&n;&t;&t;&t;  local_bh_count(smp_processor_id())) != 0)
DECL|macro|in_irq
mdefine_line|#define in_irq()        (local_irq_count(smp_processor_id()) != 0)
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)    (local_irq_count(cpu) == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)    do { (void)(cpu); } while (0)
DECL|macro|irq_enter
mdefine_line|#define irq_enter(cpu)      (local_irq_count(cpu)++)
DECL|macro|irq_exit
mdefine_line|#define irq_exit(cpu)       (local_irq_count(cpu)--)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()       barrier()
macro_line|#endif /* __ASM_HARDIRQ_H */
eof
