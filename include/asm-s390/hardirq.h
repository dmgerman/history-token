multiline_comment|/*&n; *  include/asm-s390/hardirq.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; *&n; *  Derived from &quot;include/asm-i386/hardirq.h&quot;&n; */
macro_line|#ifndef __ASM_HARDIRQ_H
DECL|macro|__ASM_HARDIRQ_H
mdefine_line|#define __ASM_HARDIRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/* No irq_cpustat_t for s390, the data is held directly in S390_lowcore */
multiline_comment|/*&n; * Simple wrappers reducing source bloat.  S390 specific because each&n; * cpu stores its data in S390_lowcore (PSA) instead of using a cache&n; * aligned array element like most architectures.&n; */
macro_line|#ifdef CONFIG_SMP
DECL|macro|softirq_active
mdefine_line|#define softirq_active(cpu)&t;(safe_get_cpu_lowcore(cpu).__softirq_active)
DECL|macro|softirq_mask
mdefine_line|#define softirq_mask(cpu)&t;(safe_get_cpu_lowcore(cpu).__softirq_mask)
DECL|macro|local_irq_count
mdefine_line|#define local_irq_count(cpu)&t;(safe_get_cpu_lowcore(cpu).__local_irq_count)
DECL|macro|local_bh_count
mdefine_line|#define local_bh_count(cpu)&t;(safe_get_cpu_lowcore(cpu).__local_bh_count)
DECL|macro|syscall_count
mdefine_line|#define syscall_count(cpu)&t;(safe_get_cpu_lowcore(cpu).__syscall_count)
macro_line|#else&t;/* CONFIG_SMP */
multiline_comment|/* Optimize away the cpu calculation, it is always current PSA */
DECL|macro|softirq_active
mdefine_line|#define softirq_active(cpu)&t;((void)(cpu), S390_lowcore.__softirq_active)
DECL|macro|softirq_mask
mdefine_line|#define softirq_mask(cpu)&t;((void)(cpu), S390_lowcore.__softirq_mask)
DECL|macro|local_irq_count
mdefine_line|#define local_irq_count(cpu)&t;((void)(cpu), S390_lowcore.__local_irq_count)
DECL|macro|local_bh_count
mdefine_line|#define local_bh_count(cpu)&t;((void)(cpu), S390_lowcore.__local_bh_count)
DECL|macro|syscall_count
mdefine_line|#define syscall_count(cpu)&t;((void)(cpu), S390_lowcore.__syscall_count)
macro_line|#endif&t;/* CONFIG_SMP */
multiline_comment|/*&n; * Are we in an interrupt context? Either doing bottom half&n; * or hardware interrupt processing?&n; * Special definitions for s390, always access current PSA.&n; */
DECL|macro|in_interrupt
mdefine_line|#define in_interrupt() ((S390_lowcore.__local_irq_count + S390_lowcore.__local_bh_count) != 0)
DECL|macro|in_irq
mdefine_line|#define in_irq() (S390_lowcore.__local_irq_count != 0)
macro_line|#ifndef CONFIG_SMP
DECL|macro|hardirq_trylock
mdefine_line|#define hardirq_trylock(cpu)&t;(local_irq_count(cpu) == 0)
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
DECL|macro|hardirq_enter
mdefine_line|#define hardirq_enter(cpu)&t;(local_irq_count(cpu)++)
DECL|macro|hardirq_exit
mdefine_line|#define hardirq_exit(cpu)&t;(local_irq_count(cpu)--)
DECL|macro|synchronize_irq
mdefine_line|#define synchronize_irq()&t;do { } while (0)
macro_line|#else
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
r_extern
id|atomic_t
id|global_irq_holder
suffix:semicolon
r_extern
id|atomic_t
id|global_irq_lock
suffix:semicolon
r_extern
id|atomic_t
id|global_irq_count
suffix:semicolon
DECL|function|release_irqlock
r_static
r_inline
r_void
id|release_irqlock
c_func
(paren
r_int
id|cpu
)paren
(brace
multiline_comment|/* if we didn&squot;t own the irq lock, just ignore.. */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|global_irq_holder
)paren
op_eq
id|cpu
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|global_irq_holder
comma
id|NO_PROC_ID
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|hardirq_enter
r_static
r_inline
r_void
id|hardirq_enter
c_func
(paren
r_int
id|cpu
)paren
(brace
op_increment
id|local_irq_count
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|global_irq_count
)paren
suffix:semicolon
)brace
DECL|function|hardirq_exit
r_static
r_inline
r_void
id|hardirq_exit
c_func
(paren
r_int
id|cpu
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|global_irq_count
)paren
suffix:semicolon
op_decrement
id|local_irq_count
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
DECL|function|hardirq_trylock
r_static
r_inline
r_int
id|hardirq_trylock
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|global_irq_count
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
suffix:semicolon
)brace
DECL|macro|hardirq_endlock
mdefine_line|#define hardirq_endlock(cpu)&t;do { } while (0)
r_extern
r_void
id|synchronize_irq
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __ASM_HARDIRQ_H */
eof
