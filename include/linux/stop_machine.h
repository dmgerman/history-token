macro_line|#ifndef _LINUX_STOP_MACHINE
DECL|macro|_LINUX_STOP_MACHINE
mdefine_line|#define _LINUX_STOP_MACHINE
multiline_comment|/* &quot;Bogolock&quot;: stop the entire machine, disable interrupts.  This is a&n;   very heavy lock, which is equivalent to grabbing every spinlock&n;   (and more).  So the &quot;read&quot; side to such a lock is anything which&n;   diables preeempt. */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef CONFIG_SMP
multiline_comment|/**&n; * stop_machine_run: freeze the machine on all CPUs and run this function&n; * @fn: the function to run&n; * @data: the data ptr for the @fn()&n; * @cpu: the cpu to run @fn() on (or any, if @cpu == NR_CPUS.&n; *&n; * Description: This causes a thread to be scheduled on every other cpu,&n; * each of which disables interrupts, and finally interrupts are disabled&n; * on the current CPU.  The result is that noone is holding a spinlock&n; * or inside any other preempt-disabled region when @fn() runs.&n; *&n; * This can be thought of as a very heavy write lock, equivalent to&n; * grabbing every spinlock in the kernel. */
r_int
id|stop_machine_run
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|data
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/**&n; * __stop_machine_run: freeze the machine on all CPUs and run this function&n; * @fn: the function to run&n; * @data: the data ptr for the @fn&n; * @cpu: the cpu to run @fn on (or any, if @cpu == NR_CPUS.&n; *&n; * Description: This is a special version of the above, which returns the&n; * thread which has run @fn(): kthread_stop will return the return value&n; * of @fn().  Used by hotplug cpu.&n; */
r_struct
id|task_struct
op_star
id|__stop_machine_run
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|data
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#else
DECL|function|stop_machine_run
r_static
r_inline
r_int
id|stop_machine_run
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|data
comma
r_int
r_int
id|cpu
)paren
(brace
r_int
id|ret
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|fn
c_func
(paren
id|data
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* _LINUX_STOP_MACHINE */
eof
