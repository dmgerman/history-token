multiline_comment|/*&n; *  include/asm-s390/hardirq.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; *&n; *  Derived from &quot;include/asm-i386/hardirq.h&quot;&n; */
macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
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
multiline_comment|/* this is always called with cpu == smp_processor_id() at the moment */
r_static
r_inline
id|__u32
DECL|function|softirq_pending
id|softirq_pending
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
id|cpu
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
r_return
id|local_softirq_pending
c_func
(paren
)paren
suffix:semicolon
r_return
id|lowcore_ptr
(braket
id|cpu
)braket
op_member_access_from_pointer
id|softirq_pending
suffix:semicolon
)brace
DECL|macro|__ARCH_IRQ_STAT
mdefine_line|#define __ARCH_IRQ_STAT
multiline_comment|/*&n; * We put the hardirq and softirq counter into the preemption&n; * counter. The bitmask has the following meaning:&n; *&n; * - bits 0-7 are the preemption count (max preemption depth: 256)&n; * - bits 8-15 are the softirq count (max # of softirqs: 256)&n; * - bits 16-23 are the hardirq count (max # of hardirqs: 256)&n; *&n; * - ( bit 26 is the PREEMPT_ACTIVE flag. )&n; *&n; * PREEMPT_MASK: 0x000000ff&n; * SOFTIRQ_MASK: 0x0000ff00&n; * HARDIRQ_MASK: 0x00ff0000&n; */
DECL|macro|PREEMPT_BITS
mdefine_line|#define PREEMPT_BITS&t;8
DECL|macro|SOFTIRQ_BITS
mdefine_line|#define SOFTIRQ_BITS&t;8
DECL|macro|HARDIRQ_BITS
mdefine_line|#define HARDIRQ_BITS&t;8
DECL|macro|PREEMPT_SHIFT
mdefine_line|#define PREEMPT_SHIFT&t;0
DECL|macro|SOFTIRQ_SHIFT
mdefine_line|#define SOFTIRQ_SHIFT&t;(PREEMPT_SHIFT + PREEMPT_BITS)
DECL|macro|HARDIRQ_SHIFT
mdefine_line|#define HARDIRQ_SHIFT&t;(SOFTIRQ_SHIFT + SOFTIRQ_BITS)
r_extern
r_void
id|do_call_softirq
c_func
(paren
r_void
)paren
suffix:semicolon
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
DECL|macro|invoke_softirq
mdefine_line|#define invoke_softirq() do_call_softirq()
DECL|macro|irq_enter
mdefine_line|#define irq_enter()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(preempt_count() += HARDIRQ_OFFSET);&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|irq_exit
mdefine_line|#define irq_exit()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;preempt_count() -= IRQ_EXIT_OFFSET;&t;&t;&t;&t;&bslash;&n;&t;if (!in_interrupt() &amp;&amp; local_softirq_pending())&t;&t;&t;&bslash;&n;&t;&t;/* Use the async. stack for softirq */&t;&t;&t;&bslash;&n;&t;&t;do_call_softirq();&t;&t;&t;&t;&t;&bslash;&n;&t;preempt_enable_no_resched();&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* __ASM_HARDIRQ_H */
eof
