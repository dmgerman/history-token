multiline_comment|/* softirq.h: 32-bit Sparc soft IRQ support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998-99 Anton Blanchard (anton@progsoc.uts.edu.au)&n; */
macro_line|#ifndef __SPARC_SOFTIRQ_H
DECL|macro|__SPARC_SOFTIRQ_H
mdefine_line|#define __SPARC_SOFTIRQ_H
macro_line|#include &lt;linux/threads.h&gt;&t;/* For NR_CPUS */
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;(local_bh_count(smp_processor_id())++)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()&t;(local_bh_count(smp_processor_id())--)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;  &bslash;&n;do { if (!--local_bh_count(smp_processor_id()) &amp;&amp; &bslash;&n;&t; softirq_pending(smp_processor_id())) {   &bslash;&n;&t;&t;do_softirq();&t;&t;&t;  &bslash;&n;&t;&t;__sti();&t;&t;&t;  &bslash;&n;     }&t;&t;&t;&t;&t;&t;  &bslash;&n;} while (0)
DECL|macro|__cpu_raise_softirq
mdefine_line|#define __cpu_raise_softirq(cpu, nr)&t;(softirq_pending(cpu) |= (1&lt;&lt;nr))
DECL|macro|raise_softirq
mdefine_line|#define raise_softirq(nr)&t;&t;&t;&t;&bslash;&n;do {&t;unsigned long flags;&t;&t;&t;&t;&bslash;&n;&t;local_irq_save(flags);&t;&t;&t;&t;&bslash;&n;&t;__cpu_raise_softirq(smp_processor_id(), nr);&t;&bslash;&n;&t;local_irq_restore(flags);&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
macro_line|#endif&t;/* __SPARC_SOFTIRQ_H */
eof
