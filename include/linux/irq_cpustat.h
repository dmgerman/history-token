macro_line|#ifndef __irq_cpustat_h
DECL|macro|__irq_cpustat_h
mdefine_line|#define __irq_cpustat_h
multiline_comment|/*&n; * Contains default mappings for irq_cpustat_t, used by almost every&n; * architecture.  Some arch (like s390) have per cpu hardware pages and&n; * they define their own mappings for irq_stat.&n; *&n; * Keith Owens &lt;kaos@ocs.com.au&gt; July 2000.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Simple wrappers reducing source bloat.  Define all irq_stat fields&n; * here, even ones that are arch dependent.  That way we get common&n; * definitions instead of differing sets for each arch.&n; */
macro_line|#ifndef __ARCH_IRQ_STAT
r_extern
id|irq_cpustat_t
id|irq_stat
(braket
)braket
suffix:semicolon
multiline_comment|/* defined in asm/hardirq.h */
macro_line|#ifdef CONFIG_SMP
DECL|macro|__IRQ_STAT
mdefine_line|#define __IRQ_STAT(cpu, member)&t;(irq_stat[cpu].member)
macro_line|#else
DECL|macro|__IRQ_STAT
mdefine_line|#define __IRQ_STAT(cpu, member)&t;((void)(cpu), irq_stat[0].member)
macro_line|#endif&t;
macro_line|#endif
multiline_comment|/* arch independent irq_stat fields */
DECL|macro|softirq_pending
mdefine_line|#define softirq_pending(cpu)&t;__IRQ_STAT((cpu), __softirq_pending)
DECL|macro|local_softirq_pending
mdefine_line|#define local_softirq_pending()&t;softirq_pending(smp_processor_id())
multiline_comment|/* arch dependent irq_stat fields */
DECL|macro|nmi_count
mdefine_line|#define nmi_count(cpu)&t;&t;__IRQ_STAT((cpu), __nmi_count)&t;/* i386 */
macro_line|#endif&t;/* __irq_cpustat_h */
eof
