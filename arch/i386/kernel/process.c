multiline_comment|/*&n; *  linux/arch/i386/kernel/process.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *&n; *  Pentium III FXSR, SSE support&n; *&t;Gareth Hughes &lt;gareth@valinux.com&gt;, May 2000&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ldt.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#ifdef CONFIG_MATH_EMULATION
macro_line|#include &lt;asm/math_emu.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/err.h&gt;
id|asmlinkage
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
id|__asm__
c_func
(paren
l_string|&quot;ret_from_fork&quot;
)paren
suffix:semicolon
DECL|variable|hlt_counter
r_int
id|hlt_counter
suffix:semicolon
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
DECL|function|thread_saved_pc
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|tsk-&gt;thread.esp
)paren
(braket
l_int|3
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Powermanagement idle function, if any..&n; */
DECL|variable|pm_idle
r_void
(paren
op_star
id|pm_idle
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|disable_hlt
r_void
id|disable_hlt
c_func
(paren
r_void
)paren
(brace
id|hlt_counter
op_increment
suffix:semicolon
)brace
DECL|variable|disable_hlt
id|EXPORT_SYMBOL
c_func
(paren
id|disable_hlt
)paren
suffix:semicolon
DECL|function|enable_hlt
r_void
id|enable_hlt
c_func
(paren
r_void
)paren
(brace
id|hlt_counter
op_decrement
suffix:semicolon
)brace
DECL|variable|enable_hlt
id|EXPORT_SYMBOL
c_func
(paren
id|enable_hlt
)paren
suffix:semicolon
multiline_comment|/*&n; * We use this if we don&squot;t have any better&n; * idle routine..&n; */
DECL|function|default_idle
r_void
id|default_idle
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hlt_counter
op_logical_and
id|current_cpu_data.hlt_works_ok
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|safe_halt
c_func
(paren
)paren
suffix:semicolon
r_else
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * On SMP it&squot;s slightly faster (but much more power-consuming!)&n; * to poll the -&gt;work.need_resched flag instead of waiting for the&n; * cross-CPU IPI to arrive. Use this option with caution.&n; */
DECL|function|poll_idle
r_static
r_void
id|poll_idle
(paren
r_void
)paren
(brace
r_int
id|oldval
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Deal with another CPU just having chosen a thread to&n;&t; * run here:&n;&t; */
id|oldval
op_assign
id|test_and_clear_thread_flag
c_func
(paren
id|TIF_NEED_RESCHED
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldval
)paren
(brace
id|set_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;2:&quot;
l_string|&quot;testl %0, %1;&quot;
l_string|&quot;rep; nop;&quot;
l_string|&quot;je 2b;&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|_TIF_NEED_RESCHED
)paren
comma
l_string|&quot;m&quot;
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
)paren
)paren
suffix:semicolon
id|clear_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
)brace
r_else
(brace
id|set_need_resched
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The idle thread. There&squot;s no useful work to be&n; * done, so just try to conserve power and have a&n; * low exit latency (ie sit in a loop waiting for&n; * somebody to say that they&squot;d like to reschedule)&n; */
DECL|function|cpu_idle
r_void
id|cpu_idle
(paren
r_void
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
(brace
r_void
(paren
op_star
id|idle
)paren
(paren
r_void
)paren
op_assign
id|pm_idle
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idle
)paren
id|idle
op_assign
id|default_idle
suffix:semicolon
id|irq_stat
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
dot
id|idle_timestamp
op_assign
id|jiffies
suffix:semicolon
id|idle
c_func
(paren
)paren
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This uses new MONITOR/MWAIT instructions on P4 processors with PNI,&n; * which can obviate IPI to trigger checking of need_resched.&n; * We execute MONITOR against need_resched and enter optimized wait state&n; * through MWAIT. Whenever someone changes need_resched, we would be woken&n; * up from MWAIT (without an IPI).&n; */
DECL|function|mwait_idle
r_static
r_void
id|mwait_idle
c_func
(paren
r_void
)paren
(brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
(brace
id|set_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
r_do
(brace
id|__monitor
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
r_break
suffix:semicolon
id|__mwait
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
suffix:semicolon
id|clear_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
)brace
)brace
DECL|function|select_idle_routine
r_void
id|__init
id|select_idle_routine
c_func
(paren
r_const
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_if
c_cond
(paren
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_MWAIT
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;monitor/mwait feature present.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Skip, if setup has overridden idle.&n;&t;&t; * Also, take care of system with asymmetric CPUs.&n;&t;&t; * Use, mwait_idle only if all cpus support it.&n;&t;&t; * If not, we fallback to default_idle()&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|pm_idle
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;using mwait in idle threads.&bslash;n&quot;
)paren
suffix:semicolon
id|pm_idle
op_assign
id|mwait_idle
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|pm_idle
op_assign
id|default_idle
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|idle_setup
r_static
r_int
id|__init
id|idle_setup
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;poll&quot;
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;using polling idle threads.&bslash;n&quot;
)paren
suffix:semicolon
id|pm_idle
op_assign
id|poll_idle
suffix:semicolon
macro_line|#ifdef CONFIG_X86_SMP
r_if
c_cond
(paren
id|smp_num_siblings
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;WARNING: polling idle and HT enabled, performance may degrade.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;halt&quot;
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;using halt in idle threads.&bslash;n&quot;
)paren
suffix:semicolon
id|pm_idle
op_assign
id|default_idle
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;idle=&quot;
comma
id|idle_setup
)paren
suffix:semicolon
DECL|function|show_regs
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|cr0
op_assign
l_int|0L
comma
id|cr2
op_assign
l_int|0L
comma
id|cr3
op_assign
l_int|0L
comma
id|cr4
op_assign
l_int|0L
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Pid: %d, comm: %20s&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EIP: %04x:[&lt;%08lx&gt;] CPU: %d&bslash;n&quot;
comma
l_int|0xffff
op_amp
id|regs-&gt;xcs
comma
id|regs-&gt;eip
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot;EIP is at %s&bslash;n&quot;
comma
id|regs-&gt;eip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;xcs
op_amp
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot; ESP: %04x:%08lx&quot;
comma
l_int|0xffff
op_amp
id|regs-&gt;xss
comma
id|regs-&gt;esp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; EFLAGS: %08lx    %s  (%s)&bslash;n&quot;
comma
id|regs-&gt;eflags
comma
id|print_tainted
c_func
(paren
)paren
comma
id|UTS_RELEASE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EAX: %08lx EBX: %08lx ECX: %08lx EDX: %08lx&bslash;n&quot;
comma
id|regs-&gt;eax
comma
id|regs-&gt;ebx
comma
id|regs-&gt;ecx
comma
id|regs-&gt;edx
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ESI: %08lx EDI: %08lx EBP: %08lx&quot;
comma
id|regs-&gt;esi
comma
id|regs-&gt;edi
comma
id|regs-&gt;ebp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; DS: %04x ES: %04x&bslash;n&quot;
comma
l_int|0xffff
op_amp
id|regs-&gt;xds
comma
l_int|0xffff
op_amp
id|regs-&gt;xes
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr0, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr0
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr2
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr3, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr3
)paren
)paren
suffix:semicolon
multiline_comment|/* This could fault if %cr4 does not exist */
id|__asm__
c_func
(paren
l_string|&quot;1: movl %%cr4, %0&t;&t;&bslash;n&quot;
l_string|&quot;2:&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&t;&bslash;n&quot;
l_string|&quot;.long 1b,2b&t;&t;&t;&bslash;n&quot;
l_string|&quot;.previous&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr4
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CR0: %08lx CR2: %08lx CR3: %08lx CR4: %08lx&bslash;n&quot;
comma
id|cr0
comma
id|cr2
comma
id|cr3
comma
id|cr4
)paren
suffix:semicolon
id|show_trace
c_func
(paren
l_int|NULL
comma
op_amp
id|regs-&gt;esp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This gets run with %ebx containing the&n; * function to call, and %edx containing&n; * the &quot;args&quot;.&n; */
r_extern
r_void
id|kernel_thread_helper
c_func
(paren
r_void
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;.section .text&bslash;n&quot;
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;kernel_thread_helper:&bslash;n&bslash;t&quot;
l_string|&quot;movl %edx,%eax&bslash;n&bslash;t&quot;
l_string|&quot;pushl %edx&bslash;n&bslash;t&quot;
l_string|&quot;call *%ebx&bslash;n&bslash;t&quot;
l_string|&quot;pushl %eax&bslash;n&bslash;t&quot;
l_string|&quot;call do_exit&bslash;n&quot;
l_string|&quot;.previous&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Create a kernel thread&n; */
DECL|function|kernel_thread
r_int
id|kernel_thread
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
id|arg
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|pt_regs
id|regs
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|regs
comma
l_int|0
comma
r_sizeof
(paren
id|regs
)paren
)paren
suffix:semicolon
id|regs.ebx
op_assign
(paren
r_int
r_int
)paren
id|fn
suffix:semicolon
id|regs.edx
op_assign
(paren
r_int
r_int
)paren
id|arg
suffix:semicolon
id|regs.xds
op_assign
id|__USER_DS
suffix:semicolon
id|regs.xes
op_assign
id|__USER_DS
suffix:semicolon
id|regs.orig_eax
op_assign
op_minus
l_int|1
suffix:semicolon
id|regs.eip
op_assign
(paren
r_int
r_int
)paren
id|kernel_thread_helper
suffix:semicolon
id|regs.xcs
op_assign
id|__KERNEL_CS
suffix:semicolon
id|regs.eflags
op_assign
id|X86_EFLAGS_IF
op_or
id|X86_EFLAGS_SF
op_or
id|X86_EFLAGS_PF
op_or
l_int|0x2
suffix:semicolon
multiline_comment|/* Ok, create the new process.. */
r_return
id|do_fork
c_func
(paren
id|flags
op_or
id|CLONE_VM
op_or
id|CLONE_UNTRACED
comma
l_int|0
comma
op_amp
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Free current thread data structures etc..&n; */
DECL|function|exit_thread
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|thread_struct
op_star
id|t
op_assign
op_amp
id|tsk-&gt;thread
suffix:semicolon
multiline_comment|/* The process may have allocated an io port bitmap... nuke it. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
l_int|NULL
op_ne
id|t-&gt;io_bitmap_ptr
)paren
)paren
(brace
r_int
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
r_struct
id|tss_struct
op_star
id|tss
op_assign
op_amp
id|per_cpu
c_func
(paren
id|init_tss
comma
id|cpu
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|t-&gt;io_bitmap_ptr
)paren
suffix:semicolon
id|t-&gt;io_bitmap_ptr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Careful, clear this in the TSS too:&n;&t;&t; */
id|memset
c_func
(paren
id|tss-&gt;io_bitmap
comma
l_int|0xff
comma
id|t-&gt;io_bitmap_max
)paren
suffix:semicolon
id|t-&gt;io_bitmap_max
op_assign
l_int|0
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|memset
c_func
(paren
id|tsk-&gt;thread.debugreg
comma
l_int|0
comma
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|8
)paren
suffix:semicolon
id|memset
c_func
(paren
id|tsk-&gt;thread.tls_array
comma
l_int|0
comma
r_sizeof
(paren
id|tsk-&gt;thread.tls_array
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Forget coprocessor state..&n;&t; */
id|clear_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;used_math
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|release_thread
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
id|dead_task
)paren
(brace
r_if
c_cond
(paren
id|dead_task-&gt;mm
)paren
(brace
singleline_comment|// temporary debugging check
r_if
c_cond
(paren
id|dead_task-&gt;mm-&gt;context.size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WARNING: dead process %8s still has LDT? &lt;%p/%d&gt;&bslash;n&quot;
comma
id|dead_task-&gt;comm
comma
id|dead_task-&gt;mm-&gt;context.ldt
comma
id|dead_task-&gt;mm-&gt;context.size
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|release_x86_irqs
c_func
(paren
id|dead_task
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This gets called before we allocate a new thread and copy&n; * the current task into it.&n; */
DECL|function|prepare_to_copy
r_void
id|prepare_to_copy
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|unlazy_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
DECL|function|copy_thread
r_int
id|copy_thread
c_func
(paren
r_int
id|nr
comma
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|esp
comma
r_int
r_int
id|unused
comma
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_int
id|err
suffix:semicolon
id|childregs
op_assign
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|THREAD_SIZE
op_plus
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
)paren
)paren
op_minus
l_int|1
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
id|childregs-&gt;eax
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;esp
op_assign
id|esp
suffix:semicolon
id|p-&gt;set_child_tid
op_assign
id|p-&gt;clear_child_tid
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;thread.esp
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
id|p-&gt;thread.esp0
op_assign
(paren
r_int
r_int
)paren
(paren
id|childregs
op_plus
l_int|1
)paren
suffix:semicolon
id|p-&gt;thread.eip
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
id|savesegment
c_func
(paren
id|fs
comma
id|p-&gt;thread.fs
)paren
suffix:semicolon
id|savesegment
c_func
(paren
id|gs
comma
id|p-&gt;thread.gs
)paren
suffix:semicolon
id|tsk
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
l_int|NULL
op_ne
id|tsk-&gt;thread.io_bitmap_ptr
)paren
)paren
(brace
id|p-&gt;thread.io_bitmap_ptr
op_assign
id|kmalloc
c_func
(paren
id|IO_BITMAP_BYTES
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;thread.io_bitmap_ptr
)paren
(brace
id|p-&gt;thread.io_bitmap_max
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|p-&gt;thread.io_bitmap_ptr
comma
id|tsk-&gt;thread.io_bitmap_ptr
comma
id|IO_BITMAP_BYTES
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set a new TLS for the child thread?&n;&t; */
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_SETTLS
)paren
(brace
r_struct
id|desc_struct
op_star
id|desc
suffix:semicolon
r_struct
id|user_desc
id|info
suffix:semicolon
r_int
id|idx
suffix:semicolon
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|info
comma
(paren
r_void
id|__user
op_star
)paren
id|childregs-&gt;esi
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|LDT_empty
c_func
(paren
op_amp
id|info
)paren
)paren
r_goto
id|out
suffix:semicolon
id|idx
op_assign
id|info.entry_number
suffix:semicolon
r_if
c_cond
(paren
id|idx
template_param
id|GDT_ENTRY_TLS_MAX
)paren
r_goto
id|out
suffix:semicolon
id|desc
op_assign
id|p-&gt;thread.tls_array
op_plus
id|idx
op_minus
id|GDT_ENTRY_TLS_MIN
suffix:semicolon
id|desc-&gt;a
op_assign
id|LDT_entry_a
c_func
(paren
op_amp
id|info
)paren
suffix:semicolon
id|desc-&gt;b
op_assign
id|LDT_entry_b
c_func
(paren
op_amp
id|info
)paren
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|err
op_logical_and
id|p-&gt;thread.io_bitmap_ptr
)paren
(brace
id|kfree
c_func
(paren
id|p-&gt;thread.io_bitmap_ptr
)paren
suffix:semicolon
id|p-&gt;thread.io_bitmap_max
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * fill in the user structure for a core dump..&n; */
DECL|function|dump_thread
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|user
op_star
id|dump
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* changed the size calculations - should hopefully work better. lbt */
id|dump-&gt;magic
op_assign
id|CMAGIC
suffix:semicolon
id|dump-&gt;start_code
op_assign
l_int|0
suffix:semicolon
id|dump-&gt;start_stack
op_assign
id|regs-&gt;esp
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|dump-&gt;u_tsize
op_assign
(paren
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;end_code
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|current-&gt;mm-&gt;brk
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_sub_assign
id|dump-&gt;u_tsize
suffix:semicolon
id|dump-&gt;u_ssize
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|dump-&gt;u_debugreg
(braket
id|i
)braket
op_assign
id|current-&gt;thread.debugreg
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dump-&gt;start_stack
OL
id|TASK_SIZE
)paren
id|dump-&gt;u_ssize
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|TASK_SIZE
op_minus
id|dump-&gt;start_stack
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;regs.ebx
op_assign
id|regs-&gt;ebx
suffix:semicolon
id|dump-&gt;regs.ecx
op_assign
id|regs-&gt;ecx
suffix:semicolon
id|dump-&gt;regs.edx
op_assign
id|regs-&gt;edx
suffix:semicolon
id|dump-&gt;regs.esi
op_assign
id|regs-&gt;esi
suffix:semicolon
id|dump-&gt;regs.edi
op_assign
id|regs-&gt;edi
suffix:semicolon
id|dump-&gt;regs.ebp
op_assign
id|regs-&gt;ebp
suffix:semicolon
id|dump-&gt;regs.eax
op_assign
id|regs-&gt;eax
suffix:semicolon
id|dump-&gt;regs.ds
op_assign
id|regs-&gt;xds
suffix:semicolon
id|dump-&gt;regs.es
op_assign
id|regs-&gt;xes
suffix:semicolon
id|savesegment
c_func
(paren
id|fs
comma
id|dump-&gt;regs.fs
)paren
suffix:semicolon
id|savesegment
c_func
(paren
id|gs
comma
id|dump-&gt;regs.gs
)paren
suffix:semicolon
id|dump-&gt;regs.orig_eax
op_assign
id|regs-&gt;orig_eax
suffix:semicolon
id|dump-&gt;regs.eip
op_assign
id|regs-&gt;eip
suffix:semicolon
id|dump-&gt;regs.cs
op_assign
id|regs-&gt;xcs
suffix:semicolon
id|dump-&gt;regs.eflags
op_assign
id|regs-&gt;eflags
suffix:semicolon
id|dump-&gt;regs.esp
op_assign
id|regs-&gt;esp
suffix:semicolon
id|dump-&gt;regs.ss
op_assign
id|regs-&gt;xss
suffix:semicolon
id|dump-&gt;u_fpvalid
op_assign
id|dump_fpu
(paren
id|regs
comma
op_amp
id|dump-&gt;i387
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Capture the user space registers if the task is not running (in user space)&n; */
DECL|function|dump_task_regs
r_int
id|dump_task_regs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
id|elf_gregset_t
op_star
id|regs
)paren
(brace
r_struct
id|pt_regs
id|ptregs
suffix:semicolon
id|ptregs
op_assign
op_star
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|tsk-&gt;thread_info
op_plus
id|THREAD_SIZE
op_minus
r_sizeof
(paren
id|ptregs
)paren
)paren
suffix:semicolon
id|ptregs.xcs
op_and_assign
l_int|0xffff
suffix:semicolon
id|ptregs.xds
op_and_assign
l_int|0xffff
suffix:semicolon
id|ptregs.xes
op_and_assign
l_int|0xffff
suffix:semicolon
id|ptregs.xss
op_and_assign
l_int|0xffff
suffix:semicolon
id|elf_core_copy_regs
c_func
(paren
id|regs
comma
op_amp
id|ptregs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * This special macro can be used to load a debugging register&n; */
DECL|macro|loaddebug
mdefine_line|#define loaddebug(thread,register) &bslash;&n;&t;&t;__asm__(&quot;movl %0,%%db&quot; #register  &bslash;&n;&t;&t;&t;: /* no output */ &bslash;&n;&t;&t;&t;:&quot;r&quot; (thread-&gt;debugreg[register]))
multiline_comment|/*&n; *&t;switch_to(x,yn) should switch tasks from x to y.&n; *&n; * We fsave/fwait so that an exception goes off at the right time&n; * (as a call from the fsave or fwait in effect) rather than to&n; * the wrong process. Lazy FP saving no longer makes any sense&n; * with modern CPU&squot;s, and this simplifies a lot of things (SMP&n; * and UP become the same).&n; *&n; * NOTE! We used to use the x86 hardware context switching. The&n; * reason for not using it any more becomes apparent when you&n; * try to recover gracefully from saved state that is no longer&n; * valid (stale segment register values in particular). With the&n; * hardware task-switch, there is no way to fix up bad state in&n; * a reasonable manner.&n; *&n; * The fact that Intel documents the hardware task-switching to&n; * be slow is a fairly red herring - this code is not noticeably&n; * faster. However, there _is_ some room for improvement here,&n; * so the performance issues may eventually be a valid point.&n; * More important, however, is the fact that this allows us much&n; * more flexibility.&n; *&n; * The return value (in %eax) will be the &quot;prev&quot; task after&n; * the task-switch, and shows up in ret_from_fork in entry.S,&n; * for example.&n; */
DECL|function|__switch_to
r_struct
id|task_struct
id|fastcall
op_star
id|__switch_to
c_func
(paren
r_struct
id|task_struct
op_star
id|prev_p
comma
r_struct
id|task_struct
op_star
id|next_p
)paren
(brace
r_struct
id|thread_struct
op_star
id|prev
op_assign
op_amp
id|prev_p-&gt;thread
comma
op_star
id|next
op_assign
op_amp
id|next_p-&gt;thread
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|tss_struct
op_star
id|tss
op_assign
op_amp
id|per_cpu
c_func
(paren
id|init_tss
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/* never put a printk in __switch_to... printk() calls wake_up*() indirectly */
id|__unlazy_fpu
c_func
(paren
id|prev_p
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reload esp0, LDT and the page table pointer:&n;&t; */
id|load_esp0
c_func
(paren
id|tss
comma
id|next
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Load the per-thread Thread-Local Storage descriptor.&n;&t; */
id|load_TLS
c_func
(paren
id|next
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Save away %fs and %gs. No need to save %es and %ds, as&n;&t; * those are always kernel segments while inside the kernel.&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movl %%fs,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
op_amp
id|prev-&gt;fs
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%gs,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
op_amp
id|prev-&gt;gs
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Restore %fs and %gs if needed.&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|prev-&gt;fs
op_or
id|prev-&gt;gs
op_or
id|next-&gt;fs
op_or
id|next-&gt;gs
)paren
)paren
(brace
id|loadsegment
c_func
(paren
id|fs
comma
id|next-&gt;fs
)paren
suffix:semicolon
id|loadsegment
c_func
(paren
id|gs
comma
id|next-&gt;gs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now maybe reload the debug registers&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|next-&gt;debugreg
(braket
l_int|7
)braket
)paren
)paren
(brace
id|loaddebug
c_func
(paren
id|next
comma
l_int|0
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|1
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|2
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* no 4 and 5 */
id|loaddebug
c_func
(paren
id|next
comma
l_int|6
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|7
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|prev-&gt;io_bitmap_ptr
op_logical_or
id|next-&gt;io_bitmap_ptr
)paren
)paren
(brace
r_if
c_cond
(paren
id|next-&gt;io_bitmap_ptr
)paren
multiline_comment|/*&n;&t;&t;&t; * Copy the relevant range of the IO bitmap.&n;&t;&t;&t; * Normally this is 128 bytes or less:&n;&t;&t;&t; */
id|memcpy
c_func
(paren
id|tss-&gt;io_bitmap
comma
id|next-&gt;io_bitmap_ptr
comma
id|max
c_func
(paren
id|prev-&gt;io_bitmap_max
comma
id|next-&gt;io_bitmap_max
)paren
)paren
suffix:semicolon
r_else
multiline_comment|/*&n;&t;&t;&t; * Clear any possible leftover bits:&n;&t;&t;&t; */
id|memset
c_func
(paren
id|tss-&gt;io_bitmap
comma
l_int|0xff
comma
id|prev-&gt;io_bitmap_max
)paren
suffix:semicolon
)brace
r_return
id|prev_p
suffix:semicolon
)brace
DECL|function|sys_fork
id|asmlinkage
r_int
id|sys_fork
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_return
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|regs.esp
comma
op_amp
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|sys_clone
id|asmlinkage
r_int
id|sys_clone
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
r_int
id|clone_flags
suffix:semicolon
r_int
r_int
id|newsp
suffix:semicolon
r_int
id|__user
op_star
id|parent_tidptr
comma
op_star
id|child_tidptr
suffix:semicolon
id|clone_flags
op_assign
id|regs.ebx
suffix:semicolon
id|newsp
op_assign
id|regs.ecx
suffix:semicolon
id|parent_tidptr
op_assign
(paren
r_int
id|__user
op_star
)paren
id|regs.edx
suffix:semicolon
id|child_tidptr
op_assign
(paren
r_int
id|__user
op_star
)paren
id|regs.edi
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newsp
)paren
id|newsp
op_assign
id|regs.esp
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|clone_flags
op_amp
op_complement
id|CLONE_IDLETASK
comma
id|newsp
comma
op_amp
id|regs
comma
l_int|0
comma
id|parent_tidptr
comma
id|child_tidptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is trivial, and on the face of it looks like it&n; * could equally well be done in user mode.&n; *&n; * Not so, for quite unobvious reasons - register pressure.&n; * In user mode vfork() cannot have a stack frame, and if&n; * done by calling the &quot;clone()&quot; system call directly, you&n; * do not have enough call-clobbered registers to hold all&n; * the information you need.&n; */
DECL|function|sys_vfork
id|asmlinkage
r_int
id|sys_vfork
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_return
id|do_fork
c_func
(paren
id|CLONE_VFORK
op_or
id|CLONE_VM
op_or
id|SIGCHLD
comma
id|regs.esp
comma
op_amp
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
DECL|function|sys_execve
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
id|error
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
(paren
r_char
id|__user
op_star
)paren
id|regs.ebx
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|filename
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|do_execve
c_func
(paren
id|filename
comma
(paren
r_char
id|__user
op_star
id|__user
op_star
)paren
id|regs.ecx
comma
(paren
r_char
id|__user
op_star
id|__user
op_star
)paren
id|regs.edx
comma
op_amp
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
(brace
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
multiline_comment|/* Make sure we don&squot;t return using sysenter.. */
id|set_thread_flag
c_func
(paren
id|TIF_IRET
)paren
suffix:semicolon
)brace
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|macro|top_esp
mdefine_line|#define top_esp                (THREAD_SIZE - sizeof(unsigned long))
DECL|macro|top_ebp
mdefine_line|#define top_ebp                (THREAD_SIZE - 2*sizeof(unsigned long))
DECL|function|get_wchan
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
r_int
id|ebp
comma
id|esp
comma
id|eip
suffix:semicolon
r_int
r_int
id|stack_page
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|p
op_eq
id|current
op_logical_or
id|p-&gt;state
op_eq
id|TASK_RUNNING
)paren
r_return
l_int|0
suffix:semicolon
id|stack_page
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
suffix:semicolon
id|esp
op_assign
id|p-&gt;thread.esp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stack_page
op_logical_or
id|esp
template_param
id|top_esp
op_plus
id|stack_page
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* include/asm-i386/system.h:switch_to() pushes ebp last. */
id|ebp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|esp
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|ebp
template_param
id|top_ebp
op_plus
id|stack_page
)paren
r_return
l_int|0
suffix:semicolon
id|eip
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|ebp
op_plus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_sched_functions
c_func
(paren
id|eip
)paren
)paren
r_return
id|eip
suffix:semicolon
id|ebp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|ebp
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
op_increment
OL
l_int|16
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_alloc_thread_area: get a yet unused TLS descriptor index.&n; */
DECL|function|get_free_idx
r_static
r_int
id|get_free_idx
c_func
(paren
r_void
)paren
(brace
r_struct
id|thread_struct
op_star
id|t
op_assign
op_amp
id|current-&gt;thread
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|GDT_ENTRY_TLS_ENTRIES
suffix:semicolon
id|idx
op_increment
)paren
r_if
c_cond
(paren
id|desc_empty
c_func
(paren
id|t-&gt;tls_array
op_plus
id|idx
)paren
)paren
r_return
id|idx
op_plus
id|GDT_ENTRY_TLS_MIN
suffix:semicolon
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
multiline_comment|/*&n; * Set a given TLS descriptor:&n; */
DECL|function|sys_set_thread_area
id|asmlinkage
r_int
id|sys_set_thread_area
c_func
(paren
r_struct
id|user_desc
id|__user
op_star
id|u_info
)paren
(brace
r_struct
id|thread_struct
op_star
id|t
op_assign
op_amp
id|current-&gt;thread
suffix:semicolon
r_struct
id|user_desc
id|info
suffix:semicolon
r_struct
id|desc_struct
op_star
id|desc
suffix:semicolon
r_int
id|cpu
comma
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|info
comma
id|u_info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|idx
op_assign
id|info.entry_number
suffix:semicolon
multiline_comment|/*&n;&t; * index -1 means the kernel should try to find and&n;&t; * allocate an empty descriptor:&n;&t; */
r_if
c_cond
(paren
id|idx
op_eq
op_minus
l_int|1
)paren
(brace
id|idx
op_assign
id|get_free_idx
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
r_return
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|idx
comma
op_amp
id|u_info-&gt;entry_number
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|idx
template_param
id|GDT_ENTRY_TLS_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|desc
op_assign
id|t-&gt;tls_array
op_plus
id|idx
op_minus
id|GDT_ENTRY_TLS_MIN
suffix:semicolon
multiline_comment|/*&n;&t; * We must not get preempted while modifying the TLS.&n;&t; */
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LDT_empty
c_func
(paren
op_amp
id|info
)paren
)paren
(brace
id|desc-&gt;a
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;b
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|desc-&gt;a
op_assign
id|LDT_entry_a
c_func
(paren
op_amp
id|info
)paren
suffix:semicolon
id|desc-&gt;b
op_assign
id|LDT_entry_b
c_func
(paren
op_amp
id|info
)paren
suffix:semicolon
)brace
id|load_TLS
c_func
(paren
id|t
comma
id|cpu
)paren
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the current Thread-Local Storage area:&n; */
DECL|macro|GET_BASE
mdefine_line|#define GET_BASE(desc) ( &bslash;&n;&t;(((desc)-&gt;a &gt;&gt; 16) &amp; 0x0000ffff) | &bslash;&n;&t;(((desc)-&gt;b &lt;&lt; 16) &amp; 0x00ff0000) | &bslash;&n;&t;( (desc)-&gt;b        &amp; 0xff000000)   )
DECL|macro|GET_LIMIT
mdefine_line|#define GET_LIMIT(desc) ( &bslash;&n;&t;((desc)-&gt;a &amp; 0x0ffff) | &bslash;&n;&t; ((desc)-&gt;b &amp; 0xf0000) )
DECL|macro|GET_32BIT
mdefine_line|#define GET_32BIT(desc)&t;&t;(((desc)-&gt;b &gt;&gt; 22) &amp; 1)
DECL|macro|GET_CONTENTS
mdefine_line|#define GET_CONTENTS(desc)&t;(((desc)-&gt;b &gt;&gt; 10) &amp; 3)
DECL|macro|GET_WRITABLE
mdefine_line|#define GET_WRITABLE(desc)&t;(((desc)-&gt;b &gt;&gt;  9) &amp; 1)
DECL|macro|GET_LIMIT_PAGES
mdefine_line|#define GET_LIMIT_PAGES(desc)&t;(((desc)-&gt;b &gt;&gt; 23) &amp; 1)
DECL|macro|GET_PRESENT
mdefine_line|#define GET_PRESENT(desc)&t;(((desc)-&gt;b &gt;&gt; 15) &amp; 1)
DECL|macro|GET_USEABLE
mdefine_line|#define GET_USEABLE(desc)&t;(((desc)-&gt;b &gt;&gt; 20) &amp; 1)
DECL|function|sys_get_thread_area
id|asmlinkage
r_int
id|sys_get_thread_area
c_func
(paren
r_struct
id|user_desc
id|__user
op_star
id|u_info
)paren
(brace
r_struct
id|user_desc
id|info
suffix:semicolon
r_struct
id|desc_struct
op_star
id|desc
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|idx
comma
op_amp
id|u_info-&gt;entry_number
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|idx
template_param
id|GDT_ENTRY_TLS_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|desc
op_assign
id|current-&gt;thread.tls_array
op_plus
id|idx
op_minus
id|GDT_ENTRY_TLS_MIN
suffix:semicolon
id|info.entry_number
op_assign
id|idx
suffix:semicolon
id|info.base_addr
op_assign
id|GET_BASE
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.limit
op_assign
id|GET_LIMIT
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.seg_32bit
op_assign
id|GET_32BIT
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.contents
op_assign
id|GET_CONTENTS
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.read_exec_only
op_assign
op_logical_neg
id|GET_WRITABLE
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.limit_in_pages
op_assign
id|GET_LIMIT_PAGES
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.seg_not_present
op_assign
op_logical_neg
id|GET_PRESENT
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.useable
op_assign
id|GET_USEABLE
c_func
(paren
id|desc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|u_info
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
