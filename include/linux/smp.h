macro_line|#ifndef __LINUX_SMP_H
DECL|macro|__LINUX_SMP_H
mdefine_line|#define __LINUX_SMP_H
multiline_comment|/*&n; *&t;Generic SMP support&n; *&t;&t;Alan Cox. &lt;alan@redhat.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
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
id|FASTCALL
c_func
(paren
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
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
multiline_comment|/*&n; * True once the per process idle is forked&n; */
r_extern
r_int
id|smp_threads_ready
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|smp_msg_data
suffix:semicolon
r_extern
r_volatile
r_int
id|smp_src_cpu
suffix:semicolon
r_extern
r_volatile
r_int
id|smp_msg_id
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
r_struct
id|notifier_block
suffix:semicolon
multiline_comment|/* Need to know about CPUs going up/down? */
r_extern
r_int
id|register_cpu_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_extern
r_void
id|unregister_cpu_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_int
id|cpu_up
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#else /* !SMP */
multiline_comment|/*&n; *&t;These macros fold the SMP functionality into a single CPU system&n; */
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;&t;&t;0
DECL|macro|hard_smp_processor_id
mdefine_line|#define hard_smp_processor_id()&t;&t;&t;0
DECL|macro|smp_threads_ready
mdefine_line|#define smp_threads_ready&t;&t;&t;1
macro_line|#ifndef CONFIG_PREEMPT
DECL|macro|kernel_lock
mdefine_line|#define kernel_lock()
macro_line|#endif
DECL|macro|smp_call_function
mdefine_line|#define smp_call_function(func,info,retry,wait)&t;({ 0; })
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
DECL|function|smp_send_reschedule_all
r_static
r_inline
r_void
id|smp_send_reschedule_all
c_func
(paren
r_void
)paren
(brace
)brace
DECL|macro|cpu_online_map
mdefine_line|#define cpu_online_map&t;&t;&t;&t;1
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;&t;&t;({ cpu; 1; })
DECL|macro|num_online_cpus
mdefine_line|#define num_online_cpus()&t;&t;&t;1
DECL|macro|__per_cpu_data
mdefine_line|#define __per_cpu_data
DECL|macro|per_cpu
mdefine_line|#define per_cpu(var, cpu)&t;&t;&t;var
DECL|macro|this_cpu
mdefine_line|#define this_cpu(var)&t;&t;&t;&t;var
multiline_comment|/* Need to know about CPUs going up/down? */
DECL|macro|register_cpu_notifier
mdefine_line|#define register_cpu_notifier(nb) 0
DECL|macro|unregister_cpu_notifier
mdefine_line|#define unregister_cpu_notifier(nb) do { } while(0)
macro_line|#endif /* !SMP */
DECL|macro|get_cpu
mdefine_line|#define get_cpu()&t;&t;({ preempt_disable(); smp_processor_id(); })
DECL|macro|put_cpu
mdefine_line|#define put_cpu()&t;&t;preempt_enable()
DECL|macro|put_cpu_no_resched
mdefine_line|#define put_cpu_no_resched()&t;preempt_enable_no_resched()
macro_line|#endif /* __LINUX_SMP_H */
eof
