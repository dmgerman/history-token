macro_line|#ifndef __LINUX_SMP_H
DECL|macro|__LINUX_SMP_H
mdefine_line|#define __LINUX_SMP_H
multiline_comment|/*&n; *&t;Generic SMP support&n; *&t;&t;Alan Cox. &lt;alan@redhat.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
r_extern
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/bug.h&gt;
multiline_comment|/*&n; * main cross-CPU interfaces, handles INIT, TLB flush, STOP, etc.&n; * (defined in asm header):&n; */
multiline_comment|/*&n; * stops all CPUs but the current one:&n; */
r_extern
r_void
id|smp_send_stop
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * sends a &squot;reschedule&squot; event to another CPU:&n; */
r_extern
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/*&n; * Prepare machine for booting other CPUs.&n; */
r_extern
r_void
id|smp_prepare_cpus
c_func
(paren
r_int
r_int
id|max_cpus
)paren
suffix:semicolon
multiline_comment|/*&n; * Bring a CPU up&n; */
r_extern
r_int
id|__cpu_up
c_func
(paren
r_int
r_int
id|cpunum
)paren
suffix:semicolon
multiline_comment|/*&n; * Final polishing of CPUs&n; */
r_extern
r_void
id|smp_cpus_done
c_func
(paren
r_int
r_int
id|max_cpus
)paren
suffix:semicolon
multiline_comment|/*&n; * Call a function on all other processors&n; */
r_extern
r_int
id|smp_call_function
(paren
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
comma
r_void
op_star
id|info
comma
r_int
id|retry
comma
r_int
id|wait
)paren
suffix:semicolon
multiline_comment|/*&n; * Call a function on all processors&n; */
DECL|function|on_each_cpu
r_static
r_inline
r_int
id|on_each_cpu
c_func
(paren
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
comma
r_void
op_star
id|info
comma
r_int
id|retry
comma
r_int
id|wait
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|smp_call_function
c_func
(paren
id|func
comma
id|info
comma
id|retry
comma
id|wait
)paren
suffix:semicolon
id|func
c_func
(paren
id|info
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * True once the per process idle is forked&n; */
r_extern
r_int
id|smp_threads_ready
suffix:semicolon
DECL|macro|MSG_ALL_BUT_SELF
mdefine_line|#define MSG_ALL_BUT_SELF&t;0x8000&t;/* Assume &lt;32768 CPU&squot;s */
DECL|macro|MSG_ALL
mdefine_line|#define MSG_ALL&t;&t;&t;0x8001
DECL|macro|MSG_INVALIDATE_TLB
mdefine_line|#define MSG_INVALIDATE_TLB&t;0x0001&t;/* Remote processor TLB invalidate */
DECL|macro|MSG_STOP_CPU
mdefine_line|#define MSG_STOP_CPU&t;&t;0x0002&t;/* Sent to shut down slave CPU&squot;s&n;&t;&t;&t;&t;&t; * when rebooting&n;&t;&t;&t;&t;&t; */
DECL|macro|MSG_RESCHEDULE
mdefine_line|#define MSG_RESCHEDULE&t;&t;0x0003&t;/* Reschedule request from master CPU*/
DECL|macro|MSG_CALL_FUNCTION
mdefine_line|#define MSG_CALL_FUNCTION       0x0004  /* Call function on all other CPUs */
multiline_comment|/*&n; * Mark the boot cpu &quot;online&quot; so that it can call console drivers in&n; * printk() and can access its per-cpu storage.&n; */
r_void
id|smp_prepare_boot_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else /* !SMP */
multiline_comment|/*&n; *&t;These macros fold the SMP functionality into a single CPU system&n; */
macro_line|#if !defined(__smp_processor_id) || !defined(CONFIG_PREEMPT)
DECL|macro|smp_processor_id
macro_line|# define smp_processor_id()&t;&t;&t;0
macro_line|#endif
DECL|macro|hard_smp_processor_id
mdefine_line|#define hard_smp_processor_id()&t;&t;&t;0
DECL|macro|smp_threads_ready
mdefine_line|#define smp_threads_ready&t;&t;&t;1
DECL|macro|smp_call_function
mdefine_line|#define smp_call_function(func,info,retry,wait)&t;({ 0; })
DECL|macro|on_each_cpu
mdefine_line|#define on_each_cpu(func,info,retry,wait)&t;({ func(info); 0; })
DECL|function|smp_send_reschedule
r_static
r_inline
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
(brace
)brace
DECL|macro|num_booting_cpus
mdefine_line|#define num_booting_cpus()&t;&t;&t;1
DECL|macro|smp_prepare_boot_cpu
mdefine_line|#define smp_prepare_boot_cpu()&t;&t;&t;do {} while (0)
macro_line|#endif /* !SMP */
multiline_comment|/*&n; * DEBUG_PREEMPT support: check whether smp_processor_id() is being&n; * used in a preemption-safe way.&n; *&n; * An architecture has to enable this debugging code explicitly.&n; * It can do so by renaming the smp_processor_id() macro to&n; * __smp_processor_id().  This should only be done after some minimal&n; * testing, because usually there are a number of false positives&n; * that an architecture will trigger.&n; *&n; * To fix a false positive (i.e. smp_processor_id() use that the&n; * debugging code reports but which use for some reason is legal),&n; * change the smp_processor_id() reference to _smp_processor_id(),&n; * which is the nondebug variant.  NOTE: don&squot;t use this to hack around&n; * real bugs.&n; */
macro_line|#ifdef __smp_processor_id
macro_line|# if defined(CONFIG_PREEMPT) &amp;&amp; defined(CONFIG_DEBUG_PREEMPT)
r_extern
r_int
r_int
id|smp_processor_id
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|# else
DECL|macro|smp_processor_id
macro_line|#  define smp_processor_id() __smp_processor_id()
macro_line|# endif
DECL|macro|_smp_processor_id
macro_line|# define _smp_processor_id() __smp_processor_id()
macro_line|#else
DECL|macro|_smp_processor_id
macro_line|# define _smp_processor_id() smp_processor_id()
macro_line|#endif
DECL|macro|get_cpu
mdefine_line|#define get_cpu()&t;&t;({ preempt_disable(); smp_processor_id(); })
DECL|macro|put_cpu
mdefine_line|#define put_cpu()&t;&t;preempt_enable()
DECL|macro|put_cpu_no_resched
mdefine_line|#define put_cpu_no_resched()&t;preempt_enable_no_resched()
macro_line|#endif /* __LINUX_SMP_H */
eof
