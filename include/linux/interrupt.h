multiline_comment|/* interrupt.h */
macro_line|#ifndef _LINUX_INTERRUPT_H
DECL|macro|_LINUX_INTERRUPT_H
mdefine_line|#define _LINUX_INTERRUPT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/hardirq.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * For 2.4.x compatibility, 2.4.x can use&n; *&n; *&t;typedef void irqreturn_t;&n; *&t;#define IRQ_NONE&n; *&t;#define IRQ_HANDLED&n; *&t;#define IRQ_RETVAL(x)&n; *&n; * To mix old-style and new-style irq handler returns.&n; *&n; * IRQ_NONE means we didn&squot;t handle it.&n; * IRQ_HANDLED means that we did have a valid interrupt and handled it.&n; * IRQ_RETVAL(x) selects on the two depending on x being non-zero (for handled)&n; */
DECL|typedef|irqreturn_t
r_typedef
r_int
id|irqreturn_t
suffix:semicolon
DECL|macro|IRQ_NONE
mdefine_line|#define IRQ_NONE&t;(0)
DECL|macro|IRQ_HANDLED
mdefine_line|#define IRQ_HANDLED&t;(1)
DECL|macro|IRQ_RETVAL
mdefine_line|#define IRQ_RETVAL(x)&t;((x) != 0)
DECL|struct|irqaction
r_struct
id|irqaction
(brace
DECL|member|handler
id|irqreturn_t
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|mask
id|cpumask_t
id|mask
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
DECL|member|next
r_struct
id|irqaction
op_star
id|next
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|dir
r_struct
id|proc_dir_entry
op_star
id|dir
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|irqreturn_t
id|no_action
c_func
(paren
r_int
id|cpl
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|request_irq
c_func
(paren
r_int
r_int
comma
id|irqreturn_t
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
comma
r_const
r_char
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|free_irq
c_func
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_GENERIC_HARDIRQS
r_extern
r_void
id|disable_irq_nosync
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Temporary defines for UP kernels, until all code gets fixed.&n; */
macro_line|#ifndef CONFIG_SMP
DECL|macro|cli
macro_line|# define cli()&t;&t;&t;local_irq_disable()
DECL|macro|sti
macro_line|# define sti()&t;&t;&t;local_irq_enable()
DECL|macro|save_flags
macro_line|# define save_flags(x)&t;&t;local_save_flags(x)
DECL|macro|restore_flags
macro_line|# define restore_flags(x)&t;local_irq_restore(x)
DECL|macro|save_and_cli
macro_line|# define save_and_cli(x)&t;local_irq_save(x)
macro_line|#endif
multiline_comment|/* SoftIRQ primitives.  */
DECL|macro|local_bh_disable
mdefine_line|#define local_bh_disable() &bslash;&n;&t;&t;do { preempt_count() += SOFTIRQ_OFFSET; barrier(); } while (0)
DECL|macro|__local_bh_enable
mdefine_line|#define __local_bh_enable() &bslash;&n;&t;&t;do { barrier(); preempt_count() -= SOFTIRQ_OFFSET; } while (0)
r_extern
r_void
id|local_bh_enable
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* PLEASE, avoid to allocate new softirqs, if you need not _really_ high&n;   frequency threaded job scheduling. For almost all the purposes&n;   tasklets are more than enough. F.e. all serial device BHs et&n;   al. should be converted to tasklets, not to softirqs.&n; */
r_enum
(brace
DECL|enumerator|HI_SOFTIRQ
id|HI_SOFTIRQ
op_assign
l_int|0
comma
DECL|enumerator|TIMER_SOFTIRQ
id|TIMER_SOFTIRQ
comma
DECL|enumerator|NET_TX_SOFTIRQ
id|NET_TX_SOFTIRQ
comma
DECL|enumerator|NET_RX_SOFTIRQ
id|NET_RX_SOFTIRQ
comma
DECL|enumerator|SCSI_SOFTIRQ
id|SCSI_SOFTIRQ
comma
DECL|enumerator|TASKLET_SOFTIRQ
id|TASKLET_SOFTIRQ
)brace
suffix:semicolon
multiline_comment|/* softirq mask and active fields moved to irq_cpustat_t in&n; * asm/hardirq.h to get better cache usage.  KAO&n; */
DECL|struct|softirq_action
r_struct
id|softirq_action
(brace
DECL|member|action
r_void
(paren
op_star
id|action
)paren
(paren
r_struct
id|softirq_action
op_star
)paren
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
id|asmlinkage
r_void
id|do_softirq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|open_softirq
c_func
(paren
r_int
id|nr
comma
r_void
(paren
op_star
id|action
)paren
(paren
r_struct
id|softirq_action
op_star
)paren
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|softirq_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__raise_softirq_irqoff
mdefine_line|#define __raise_softirq_irqoff(nr) do { local_softirq_pending() |= 1UL &lt;&lt; (nr); } while (0)
r_extern
r_void
id|FASTCALL
c_func
(paren
id|raise_softirq_irqoff
c_func
(paren
r_int
r_int
id|nr
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|raise_softirq
c_func
(paren
r_int
r_int
id|nr
)paren
)paren
suffix:semicolon
multiline_comment|/* Tasklets --- multithreaded analogue of BHs.&n;&n;   Main feature differing them of generic softirqs: tasklet&n;   is running only on one CPU simultaneously.&n;&n;   Main feature differing them of BHs: different tasklets&n;   may be run simultaneously on different CPUs.&n;&n;   Properties:&n;   * If tasklet_schedule() is called, then tasklet is guaranteed&n;     to be executed on some cpu at least once after this.&n;   * If the tasklet is already scheduled, but its excecution is still not&n;     started, it will be executed only once.&n;   * If this tasklet is already running on another CPU (or schedule is called&n;     from tasklet itself), it is rescheduled for later.&n;   * Tasklet is strictly serialized wrt itself, but not&n;     wrt another tasklets. If client needs some intertask synchronization,&n;     he makes it with spinlocks.&n; */
DECL|struct|tasklet_struct
r_struct
id|tasklet_struct
(brace
DECL|member|next
r_struct
id|tasklet_struct
op_star
id|next
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|func
r_void
(paren
op_star
id|func
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|data
r_int
r_int
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DECLARE_TASKLET
mdefine_line|#define DECLARE_TASKLET(name, func, data) &bslash;&n;struct tasklet_struct name = { NULL, 0, ATOMIC_INIT(0), func, data }
DECL|macro|DECLARE_TASKLET_DISABLED
mdefine_line|#define DECLARE_TASKLET_DISABLED(name, func, data) &bslash;&n;struct tasklet_struct name = { NULL, 0, ATOMIC_INIT(1), func, data }
r_enum
(brace
DECL|enumerator|TASKLET_STATE_SCHED
id|TASKLET_STATE_SCHED
comma
multiline_comment|/* Tasklet is scheduled for execution */
DECL|enumerator|TASKLET_STATE_RUN
id|TASKLET_STATE_RUN
multiline_comment|/* Tasklet is running (SMP only) */
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|function|tasklet_trylock
r_static
r_inline
r_int
id|tasklet_trylock
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
r_return
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|TASKLET_STATE_RUN
comma
op_amp
(paren
id|t
)paren
op_member_access_from_pointer
id|state
)paren
suffix:semicolon
)brace
DECL|function|tasklet_unlock
r_static
r_inline
r_void
id|tasklet_unlock
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
id|smp_mb__before_clear_bit
c_func
(paren
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|TASKLET_STATE_RUN
comma
op_amp
(paren
id|t
)paren
op_member_access_from_pointer
id|state
)paren
suffix:semicolon
)brace
DECL|function|tasklet_unlock_wait
r_static
r_inline
r_void
id|tasklet_unlock_wait
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|TASKLET_STATE_RUN
comma
op_amp
(paren
id|t
)paren
op_member_access_from_pointer
id|state
)paren
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
DECL|macro|tasklet_trylock
mdefine_line|#define tasklet_trylock(t) 1
DECL|macro|tasklet_unlock_wait
mdefine_line|#define tasklet_unlock_wait(t) do { } while (0)
DECL|macro|tasklet_unlock
mdefine_line|#define tasklet_unlock(t) do { } while (0)
macro_line|#endif
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__tasklet_schedule
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
)paren
suffix:semicolon
DECL|function|tasklet_schedule
r_static
r_inline
r_void
id|tasklet_schedule
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|TASKLET_STATE_SCHED
comma
op_amp
id|t-&gt;state
)paren
)paren
id|__tasklet_schedule
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__tasklet_hi_schedule
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
)paren
suffix:semicolon
DECL|function|tasklet_hi_schedule
r_static
r_inline
r_void
id|tasklet_hi_schedule
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|TASKLET_STATE_SCHED
comma
op_amp
id|t-&gt;state
)paren
)paren
id|__tasklet_hi_schedule
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
DECL|function|tasklet_disable_nosync
r_static
r_inline
r_void
id|tasklet_disable_nosync
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|t-&gt;count
)paren
suffix:semicolon
id|smp_mb__after_atomic_inc
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|tasklet_disable
r_static
r_inline
r_void
id|tasklet_disable
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
id|tasklet_disable_nosync
c_func
(paren
id|t
)paren
suffix:semicolon
id|tasklet_unlock_wait
c_func
(paren
id|t
)paren
suffix:semicolon
id|smp_mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|tasklet_enable
r_static
r_inline
r_void
id|tasklet_enable
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
id|smp_mb__before_atomic_dec
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|t-&gt;count
)paren
suffix:semicolon
)brace
DECL|function|tasklet_hi_enable
r_static
r_inline
r_void
id|tasklet_hi_enable
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
id|smp_mb__before_atomic_dec
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|t-&gt;count
)paren
suffix:semicolon
)brace
r_extern
r_void
id|tasklet_kill
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
suffix:semicolon
r_extern
r_void
id|tasklet_kill_immediate
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_void
id|tasklet_init
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
comma
r_void
(paren
op_star
id|func
)paren
(paren
r_int
r_int
)paren
comma
r_int
r_int
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * Autoprobing for irqs:&n; *&n; * probe_irq_on() and probe_irq_off() provide robust primitives&n; * for accurate IRQ probing during kernel initialization.  They are&n; * reasonably simple to use, are not &quot;fooled&quot; by spurious interrupts,&n; * and, unlike other attempts at IRQ probing, they do not get hung on&n; * stuck interrupts (such as unused PS2 mouse interfaces on ASUS boards).&n; *&n; * For reasonably foolproof probing, use them as follows:&n; *&n; * 1. clear and/or mask the device&squot;s internal interrupt.&n; * 2. sti();&n; * 3. irqs = probe_irq_on();      // &quot;take over&quot; all unassigned idle IRQs&n; * 4. enable the device and cause it to trigger an interrupt.&n; * 5. wait for the device to interrupt, using non-intrusive polling or a delay.&n; * 6. irq = probe_irq_off(irqs);  // get IRQ number, 0=none, negative=multiple&n; * 7. service the device to clear its pending interrupt.&n; * 8. loop again if paranoia is required.&n; *&n; * probe_irq_on() returns a mask of allocated irq&squot;s.&n; *&n; * probe_irq_off() takes the mask as a parameter,&n; * and returns the irq number which occurred,&n; * or zero if none occurred, or a negative irq number&n; * if more than one irq occurred.&n; */
macro_line|#if defined(CONFIG_GENERIC_HARDIRQS) &amp;&amp; !defined(CONFIG_GENERIC_IRQ_PROBE) 
DECL|function|probe_irq_on
r_static
r_inline
r_int
r_int
id|probe_irq_on
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|probe_irq_off
r_static
r_inline
r_int
id|probe_irq_off
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|probe_irq_mask
r_static
r_inline
r_int
r_int
id|probe_irq_mask
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
r_extern
r_int
r_int
id|probe_irq_on
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* returns 0 on failure */
r_extern
r_int
id|probe_irq_off
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* returns 0 or negative on failure */
r_extern
r_int
r_int
id|probe_irq_mask
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* returns mask of ISA interrupts */
macro_line|#endif
macro_line|#endif
eof
