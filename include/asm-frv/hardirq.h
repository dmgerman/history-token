multiline_comment|/* hardirq.h: FRV hardware IRQ management&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
r_typedef
r_struct
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
DECL|member|idle_timestamp
r_int
r_int
id|idle_timestamp
suffix:semicolon
DECL|typedef|irq_cpustat_t
)brace
id|____cacheline_aligned
id|irq_cpustat_t
suffix:semicolon
macro_line|#include &lt;linux/irq_cpustat.h&gt;&t;/* Standard mappings for irq_cpustat_t above */
DECL|macro|irq_enter
mdefine_line|#define irq_enter()&t;&t;(preempt_count() += HARDIRQ_OFFSET)
DECL|macro|nmi_enter
mdefine_line|#define nmi_enter()&t;&t;(irq_enter())
DECL|macro|nmi_exit
mdefine_line|#define nmi_exit()&t;&t;(preempt_count() -= HARDIRQ_OFFSET)
DECL|macro|irq_exit
mdefine_line|#define irq_exit()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;preempt_count() -= IRQ_EXIT_OFFSET;&t;&t;&t;&t;&bslash;&n;&t;if (!in_interrupt() &amp;&amp; softirq_pending(smp_processor_id()))&t;&bslash;&n;&t;&t;do_softirq();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;preempt_enable_no_resched();&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#ifdef CONFIG_SMP
macro_line|#error SMP not available on FR-V
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif
eof
