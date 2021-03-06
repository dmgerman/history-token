multiline_comment|/*&n; *  include/asm-s390/hardirq.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; *&n; *  Derived from &quot;include/asm-i386/hardirq.h&quot;&n; */
macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
multiline_comment|/* irq_cpustat_t is unused currently, but could be converted&n; * into a percpu variable instead of storing softirq_pending&n; * on the lowcore */
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
DECL|typedef|irq_cpustat_t
)brace
id|irq_cpustat_t
suffix:semicolon
DECL|macro|local_softirq_pending
mdefine_line|#define local_softirq_pending() (S390_lowcore.softirq_pending)
DECL|macro|__ARCH_IRQ_STAT
mdefine_line|#define __ARCH_IRQ_STAT
DECL|macro|__ARCH_HAS_DO_SOFTIRQ
mdefine_line|#define __ARCH_HAS_DO_SOFTIRQ
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;8
r_extern
r_void
id|account_ticks
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif /* __ASM_HARDIRQ_H */
eof
