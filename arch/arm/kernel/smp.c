multiline_comment|/*&n; *  linux/arch/arm/kernel/smp.c&n; *&n; *  Copyright (C) 2002 ARM Limited, All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * bitmask of present and online CPUs.&n; * The present bitmask indicates that the CPU is physically present.&n; * The online bitmask indicates that the CPU is up and running.&n; */
DECL|variable|cpu_present_mask
id|cpumask_t
id|cpu_present_mask
suffix:semicolon
DECL|variable|cpu_online_map
id|cpumask_t
id|cpu_online_map
suffix:semicolon
multiline_comment|/*&n; * structures for inter-processor calls&n; * - A collection of single bit ipi messages.&n; */
DECL|struct|ipi_data
r_struct
id|ipi_data
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ipi_count
r_int
r_int
id|ipi_count
suffix:semicolon
DECL|member|bits
r_int
r_int
id|bits
suffix:semicolon
)brace
suffix:semicolon
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|ipi_data
comma
id|ipi_data
)paren
op_assign
(brace
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
comma
)brace
suffix:semicolon
DECL|enum|ipi_msg_type
r_enum
id|ipi_msg_type
(brace
DECL|enumerator|IPI_TIMER
id|IPI_TIMER
comma
DECL|enumerator|IPI_RESCHEDULE
id|IPI_RESCHEDULE
comma
DECL|enumerator|IPI_CALL_FUNC
id|IPI_CALL_FUNC
comma
DECL|enumerator|IPI_CPU_STOP
id|IPI_CPU_STOP
comma
)brace
suffix:semicolon
DECL|struct|smp_call_struct
r_struct
id|smp_call_struct
(brace
DECL|member|func
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
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|wait
r_int
id|wait
suffix:semicolon
DECL|member|pending
id|cpumask_t
id|pending
suffix:semicolon
DECL|member|unfinished
id|cpumask_t
id|unfinished
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|smp_call_function_data
r_static
r_struct
id|smp_call_struct
op_star
r_volatile
id|smp_call_function_data
suffix:semicolon
DECL|variable|smp_call_function_lock
r_static
id|spinlock_t
id|smp_call_function_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|__cpu_up
r_int
id|__init
id|__cpu_up
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_struct
id|task_struct
op_star
id|idle
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * Spawn a new process manually.  Grab a pointer to&n;&t; * its task struct so we can mess with it&n;&t; */
id|idle
op_assign
id|fork_idle
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|idle
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CPU%u: fork() failed&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|idle
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now bring the CPU into our world.&n;&t; */
id|ret
op_assign
id|boot_secondary
c_func
(paren
id|cpu
comma
id|idle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;cpu_up: processor %d failed to boot&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * FIXME: We need to clean up the new idle thread. --rmk&n;&t;&t; */
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Called by both boot and secondaries to move global data into&n; * per-processor storage.&n; */
DECL|function|smp_store_cpu_info
r_void
id|__init
id|smp_store_cpu_info
c_func
(paren
r_int
r_int
id|cpuid
)paren
(brace
r_struct
id|cpuinfo_arm
op_star
id|cpu_info
op_assign
op_amp
id|per_cpu
c_func
(paren
id|cpu_data
comma
id|cpuid
)paren
suffix:semicolon
id|cpu_info-&gt;loops_per_jiffy
op_assign
id|loops_per_jiffy
suffix:semicolon
)brace
DECL|function|smp_cpus_done
r_void
id|__init
id|smp_cpus_done
c_func
(paren
r_int
r_int
id|max_cpus
)paren
(brace
r_int
id|cpu
suffix:semicolon
r_int
r_int
id|bogosum
op_assign
l_int|0
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|cpu
)paren
id|bogosum
op_add_assign
id|per_cpu
c_func
(paren
id|cpu_data
comma
id|cpu
)paren
dot
id|loops_per_jiffy
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SMP: Total of %d processors activated &quot;
l_string|&quot;(%lu.%02lu BogoMIPS).&bslash;n&quot;
comma
id|num_online_cpus
c_func
(paren
)paren
comma
id|bogosum
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|bogosum
op_div
(paren
l_int|5000
op_div
id|HZ
)paren
)paren
op_mod
l_int|100
)paren
suffix:semicolon
)brace
DECL|function|smp_prepare_boot_cpu
r_void
id|__init
id|smp_prepare_boot_cpu
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|cpu_set
c_func
(paren
id|cpu
comma
id|cpu_present_mask
)paren
suffix:semicolon
id|cpu_set
c_func
(paren
id|cpu
comma
id|cpu_online_map
)paren
suffix:semicolon
)brace
DECL|function|send_ipi_message
r_static
r_void
id|send_ipi_message
c_func
(paren
id|cpumask_t
id|callmap
comma
r_enum
id|ipi_msg_type
id|msg
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|cpu
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|for_each_cpu_mask
c_func
(paren
id|cpu
comma
id|callmap
)paren
(brace
r_struct
id|ipi_data
op_star
id|ipi
op_assign
op_amp
id|per_cpu
c_func
(paren
id|ipi_data
comma
id|cpu
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ipi-&gt;lock
)paren
suffix:semicolon
id|ipi-&gt;bits
op_or_assign
l_int|1
op_lshift
id|msg
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ipi-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Call the platform specific cross-CPU call function.&n;&t; */
id|smp_cross_call
c_func
(paren
id|callmap
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * You must not call this function with disabled interrupts, from a&n; * hardware interrupt handler, nor from a bottom half handler.&n; */
DECL|function|smp_call_function_on_cpu
r_int
id|smp_call_function_on_cpu
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
comma
id|cpumask_t
id|callmap
)paren
(brace
r_struct
id|smp_call_struct
id|data
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|data.func
op_assign
id|func
suffix:semicolon
id|data.info
op_assign
id|info
suffix:semicolon
id|data.wait
op_assign
id|wait
suffix:semicolon
id|cpu_clear
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|callmap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_empty
c_func
(paren
id|callmap
)paren
)paren
r_goto
id|out
suffix:semicolon
id|data.pending
op_assign
id|callmap
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|data.unfinished
op_assign
id|callmap
suffix:semicolon
multiline_comment|/*&n;&t; * try to get the mutex on smp_call_function_data&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|smp_call_function_lock
)paren
suffix:semicolon
id|smp_call_function_data
op_assign
op_amp
id|data
suffix:semicolon
id|send_ipi_message
c_func
(paren
id|callmap
comma
id|IPI_CALL_FUNC
)paren
suffix:semicolon
id|timeout
op_assign
id|jiffies
op_plus
id|HZ
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|cpus_empty
c_func
(paren
id|data.pending
)paren
op_logical_and
id|time_before
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * did we time out?&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|cpus_empty
c_func
(paren
id|data.pending
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * this may be causing our panic - report it&n;&t;&t; */
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;CPU%u: smp_call_function timeout for %p(%p)&bslash;n&quot;
l_string|&quot;      callmap %lx pending %lx, %swait&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|func
comma
id|info
comma
id|callmap
comma
id|data.pending
comma
id|wait
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;no &quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * TRACE&n;&t;&t; */
id|timeout
op_assign
id|jiffies
op_plus
(paren
l_int|5
op_star
id|HZ
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|cpus_empty
c_func
(paren
id|data.pending
)paren
op_logical_and
id|time_before
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_empty
c_func
(paren
id|data.pending
)paren
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;     RESOLVED&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;     STILL STUCK&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * whatever happened, we&squot;re done with the data, so release it&n;&t; */
id|smp_call_function_data
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|smp_call_function_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpus_empty
c_func
(paren
id|data.pending
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wait
)paren
r_while
c_loop
(paren
op_logical_neg
id|cpus_empty
c_func
(paren
id|data.unfinished
)paren
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|smp_call_function
r_int
id|smp_call_function
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
r_return
id|smp_call_function_on_cpu
c_func
(paren
id|func
comma
id|info
comma
id|retry
comma
id|wait
comma
id|cpu_online_map
)paren
suffix:semicolon
)brace
DECL|function|show_ipi_list
r_void
id|show_ipi_list
c_func
(paren
r_struct
id|seq_file
op_star
id|p
)paren
(brace
r_int
r_int
id|cpu
suffix:semicolon
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;IPI:&quot;
)paren
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|cpu
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; %10lu&quot;
comma
id|per_cpu
c_func
(paren
id|ipi_data
comma
id|cpu
)paren
dot
id|ipi_count
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|function|ipi_timer
r_static
r_void
id|ipi_timer
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|user
op_assign
id|user_mode
c_func
(paren
id|regs
)paren
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|profile_tick
c_func
(paren
id|CPU_PROFILING
comma
id|regs
)paren
suffix:semicolon
id|update_process_times
c_func
(paren
id|user
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ipi_call_function - handle IPI from smp_call_function()&n; *&n; * Note that we copy data out of the cross-call structure and then&n; * let the caller know that we&squot;re here and have done with their data&n; */
DECL|function|ipi_call_function
r_static
r_void
id|ipi_call_function
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_struct
id|smp_call_struct
op_star
id|data
op_assign
id|smp_call_function_data
suffix:semicolon
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
op_assign
id|data-&gt;func
suffix:semicolon
r_void
op_star
id|info
op_assign
id|data-&gt;info
suffix:semicolon
r_int
id|wait
op_assign
id|data-&gt;wait
suffix:semicolon
id|cpu_clear
c_func
(paren
id|cpu
comma
id|data-&gt;pending
)paren
suffix:semicolon
id|func
c_func
(paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|cpu_clear
c_func
(paren
id|cpu
comma
id|data-&gt;unfinished
)paren
suffix:semicolon
)brace
DECL|variable|stop_lock
r_static
id|spinlock_t
id|stop_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * ipi_cpu_stop - handle IPI from smp_send_stop()&n; */
DECL|function|ipi_cpu_stop
r_static
r_void
id|ipi_cpu_stop
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|stop_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;CPU%u: stopping&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|stop_lock
)paren
suffix:semicolon
id|cpu_clear
c_func
(paren
id|cpu
comma
id|cpu_online_map
)paren
suffix:semicolon
id|local_fiq_disable
c_func
(paren
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Main handler for inter-processor interrupts&n; *&n; * For ARM, the ipimask now only identifies a single&n; * category of IPI (Bit 1 IPIs have been replaced by a&n; * different mechanism):&n; *&n; *  Bit 0 - Inter-processor function call&n; */
DECL|function|do_IPI
r_void
id|do_IPI
c_func
(paren
r_int
r_int
id|ipimask
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|ipi_data
op_star
id|ipi
op_assign
op_amp
id|per_cpu
c_func
(paren
id|ipi_data
comma
id|cpu
)paren
suffix:semicolon
id|ipi-&gt;ipi_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ipimask
op_amp
(paren
l_int|1
op_lshift
l_int|0
)paren
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|msgs
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ipi-&gt;lock
)paren
suffix:semicolon
id|msgs
op_assign
id|ipi-&gt;bits
suffix:semicolon
id|ipi-&gt;bits
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ipi-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|msgs
)paren
r_break
suffix:semicolon
r_do
(brace
r_int
id|nextmsg
suffix:semicolon
id|nextmsg
op_assign
id|msgs
op_amp
op_minus
id|msgs
suffix:semicolon
id|msgs
op_and_assign
op_complement
id|nextmsg
suffix:semicolon
id|nextmsg
op_assign
id|ffz
c_func
(paren
op_complement
id|nextmsg
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|nextmsg
)paren
(brace
r_case
id|IPI_TIMER
suffix:colon
id|ipi_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPI_RESCHEDULE
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * nothing more to do - eveything is&n;&t;&t;&t;&t;&t; * done on the interrupt return path&n;&t;&t;&t;&t;&t; */
r_break
suffix:semicolon
r_case
id|IPI_CALL_FUNC
suffix:colon
id|ipi_call_function
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPI_CPU_STOP
suffix:colon
id|ipi_cpu_stop
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;CPU%u: Unknown IPI message 0x%x&bslash;n&quot;
comma
id|cpu
comma
id|nextmsg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|msgs
)paren
suffix:semicolon
)brace
id|ipimask
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipimask
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;CPU %d: Unknown IPI signal %x!&bslash;n&quot;
comma
id|cpu
comma
id|ipimask
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|smp_send_reschedule
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
(brace
id|send_ipi_message
c_func
(paren
id|cpumask_of_cpu
c_func
(paren
id|cpu
)paren
comma
id|IPI_RESCHEDULE
)paren
suffix:semicolon
)brace
DECL|function|smp_send_timer
r_void
id|smp_send_timer
c_func
(paren
r_void
)paren
(brace
id|cpumask_t
id|mask
op_assign
id|cpu_online_map
suffix:semicolon
id|cpu_clear
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mask
)paren
suffix:semicolon
id|send_ipi_message
c_func
(paren
id|mask
comma
id|IPI_TIMER
)paren
suffix:semicolon
)brace
DECL|function|smp_send_stop
r_void
id|smp_send_stop
c_func
(paren
r_void
)paren
(brace
id|cpumask_t
id|mask
op_assign
id|cpu_online_map
suffix:semicolon
id|cpu_clear
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mask
)paren
suffix:semicolon
id|send_ipi_message
c_func
(paren
id|mask
comma
id|IPI_CPU_STOP
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * not supported here&n; */
DECL|function|setup_profiling_timer
r_int
id|__init
id|setup_profiling_timer
c_func
(paren
r_int
r_int
id|multiplier
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
