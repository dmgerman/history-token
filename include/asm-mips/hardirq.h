multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 1998, 1999, 2000, 2001 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2001 MIPS Technologies, Inc.&n; */
macro_line|#ifndef _ASM_HARDIRQ_H
DECL|macro|_ASM_HARDIRQ_H
mdefine_line|#define _ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
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
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;8
multiline_comment|/*&n; * The hardirq mask has to be large enough to have&n; * space for potentially all IRQ sources in the system&n; * nesting on a single CPU:&n; */
macro_line|#if (1 &lt;&lt; HARDIRQ_BITS) &lt; NR_IRQS
macro_line|# error HARDIRQ_BITS is too low!
macro_line|#endif
DECL|macro|irq_enter
mdefine_line|#define irq_enter()&t;&t;(preempt_count() += HARDIRQ_OFFSET)
DECL|macro|irq_exit
mdefine_line|#define irq_exit()                                                     &bslash;&n;do {                                                                   &bslash;&n;&t;preempt_count() -= IRQ_EXIT_OFFSET;                     &bslash;&n;&t;if (!in_interrupt() &amp;&amp; softirq_pending(smp_processor_id())) &bslash;&n;&t;&t;do_softirq();                                   &bslash;&n;&t;preempt_enable_no_resched();                            &bslash;&n;} while (0)
macro_line|#endif /* _ASM_HARDIRQ_H */
eof
