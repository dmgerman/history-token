multiline_comment|/* softirq.h: 32-bit Sparc soft IRQ support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998-99 Anton Blanchard (anton@progsoc.uts.edu.au)&n; */
macro_line|#ifndef __SPARC_SOFTIRQ_H
DECL|macro|__SPARC_SOFTIRQ_H
mdefine_line|#define __SPARC_SOFTIRQ_H
singleline_comment|// #include &lt;linux/threads.h&gt;&t;/* For NR_CPUS */
singleline_comment|// #include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable() &bslash;&n;&t;&t;do { preempt_count() += SOFTIRQ_OFFSET; barrier(); } while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable() &bslash;&n;&t;&t;do { barrier(); preempt_count() -= SOFTIRQ_OFFSET; } while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;  &bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__local_bh_enable();&t;&t;&t;&bslash;&n;&t;if (!in_interrupt() &amp;&amp;&t;&t;&t;&bslash;&n;&t; softirq_pending(smp_processor_id())) {   &bslash;&n;&t;&t;do_softirq();&t;&t;&t;  &bslash;&n;     }&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;preempt_check_resched();&t;&t;  &bslash;&n;} while (0)
macro_line|#endif&t;/* __SPARC_SOFTIRQ_H */
eof
