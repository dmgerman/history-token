multiline_comment|/* softirq.h: 64-bit Sparc soft IRQ support.&n; *&n; * Copyright (C) 1997, 1998 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_SOFTIRQ_H
DECL|macro|__SPARC64_SOFTIRQ_H
mdefine_line|#define __SPARC64_SOFTIRQ_H
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/system.h&gt;&t;&t;/* for membar() */
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;&bslash;&n;&t;do { preempt_count() += SOFTIRQ_OFFSET; barrier(); } while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()&t;&bslash;&n;&t;do { barrier(); preempt_count() -= SOFTIRQ_OFFSET; } while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&bslash;&n;do {&t;__local_bh_enable();&t;&t;&t;&t;&bslash;&n;&t;if (unlikely(!in_interrupt() &amp;&amp;&t;&t;&t;&bslash;&n;&t;    softirq_pending(smp_processor_id())))&t;&bslash;&n;&t;&t;do_softirq();&t;&t;&t;&t;&bslash;&n;&t;preempt_check_resched();&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* !(__SPARC64_SOFTIRQ_H) */
eof
