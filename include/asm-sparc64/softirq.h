multiline_comment|/* softirq.h: 64-bit Sparc soft IRQ support.&n; *&n; * Copyright (C) 1997, 1998 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_SOFTIRQ_H
DECL|macro|__SPARC64_SOFTIRQ_H
mdefine_line|#define __SPARC64_SOFTIRQ_H
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/system.h&gt;&t;&t;/* for membar() */
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;do { preempt_count() += IRQ_OFFSET; barrier(); } while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()&t;do { barrier(); preempt_count() -= IRQ_OFFSET; } while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;&t;&bslash;&n;do { if (unlikely((preempt_count() == IRQ_OFFSET) &amp;&amp;&t;&bslash;&n;&t; softirq_pending(smp_processor_id()))) {   &t;&bslash;&n;&t;&t;__local_bh_enable();&t;&t;&t;&bslash;&n;&t;&t;do_softirq();&t;&t;&t;  &t;&bslash;&n;&t;&t;preempt_check_resched();&t;&t;&bslash;&n;     } else {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__local_bh_enable();&t;&t;&t;&bslash;&n;&t;&t;preempt_check_resched();&t;&t;&bslash;&n;     }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() in_interrupt()
macro_line|#endif /* !(__SPARC64_SOFTIRQ_H) */
eof
