multiline_comment|/* softirq.h: 64-bit Sparc soft IRQ support.&n; *&n; * Copyright (C) 1997, 1998 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_SOFTIRQ_H
DECL|macro|__SPARC64_SOFTIRQ_H
mdefine_line|#define __SPARC64_SOFTIRQ_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/system.h&gt;&t;&t;/* for membar() */
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable()&t;do { barrier(); preempt_disable(); local_bh_count(smp_processor_id())++; } while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable()&t;do { local_bh_count(smp_processor_id())--; preempt_enable(); barrier(); } while (0)
DECL|macro|local_bh_enable
mdefine_line|#define local_bh_enable()&t;&t;&t;  &bslash;&n;do { if (!--local_bh_count(smp_processor_id()) &amp;&amp; &bslash;&n;&t; softirq_pending(smp_processor_id())) {   &bslash;&n;&t;&t;do_softirq();&t;&t;&t;  &bslash;&n;&t;&t;__sti();&t;&t;&t;  &bslash;&n;     }&t;&t;&t;&t;&t;&t;  &bslash;&n;     preempt_enable();&t;&t;&t;&t;  &bslash;&n;} while (0)
DECL|macro|in_softirq
mdefine_line|#define in_softirq() (local_bh_count(smp_processor_id()) != 0)
macro_line|#endif /* !(__SPARC64_SOFTIRQ_H) */
eof
