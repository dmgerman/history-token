multiline_comment|/*&n; *  arch/s390/kernel/process.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Hartmut Penner (hp@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),&n; *&n; *  Derived from &quot;arch/i386/kernel/process.c&quot;&n; *    Copyright (C) 1995, Linus Torvalds&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
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
multiline_comment|/*&n; * Return saved PC of a blocked thread. used in kernel/sched.&n; * resume in entry.S does not create a new stack frame, it&n; * just stores the registers %r6-%r15 to the frame given by&n; * schedule. We want to return the address of the caller of&n; * schedule, so we have to walk the backchain one time to&n; * find the frame schedule() store its return address.&n; */
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
r_struct
id|stack_frame
op_star
id|sf
suffix:semicolon
id|sf
op_assign
(paren
r_struct
id|stack_frame
op_star
)paren
id|tsk-&gt;thread.ksp
suffix:semicolon
id|sf
op_assign
(paren
r_struct
id|stack_frame
op_star
)paren
id|sf-&gt;back_chain
suffix:semicolon
r_return
id|sf-&gt;gprs
(braket
l_int|8
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Need to know about CPUs going idle?&n; */
DECL|variable|idle_chain
r_static
r_struct
id|notifier_block
op_star
id|idle_chain
suffix:semicolon
DECL|function|register_idle_notifier
r_int
id|register_idle_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
(brace
r_return
id|notifier_chain_register
c_func
(paren
op_amp
id|idle_chain
comma
id|nb
)paren
suffix:semicolon
)brace
DECL|variable|register_idle_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|register_idle_notifier
)paren
suffix:semicolon
DECL|function|unregister_idle_notifier
r_int
id|unregister_idle_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
(brace
r_return
id|notifier_chain_unregister
c_func
(paren
op_amp
id|idle_chain
comma
id|nb
)paren
suffix:semicolon
)brace
DECL|variable|unregister_idle_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_idle_notifier
)paren
suffix:semicolon
DECL|function|do_monitor_call
r_void
id|do_monitor_call
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|interruption_code
)paren
(brace
multiline_comment|/* disable monitor call class 0 */
id|__ctl_clear_bit
c_func
(paren
l_int|8
comma
l_int|15
)paren
suffix:semicolon
id|notifier_call_chain
c_func
(paren
op_amp
id|idle_chain
comma
id|CPU_NOT_IDLE
comma
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The idle loop on a S390...&n; */
DECL|function|default_idle
r_void
id|default_idle
c_func
(paren
r_void
)paren
(brace
id|psw_t
id|wait_psw
suffix:semicolon
r_int
r_int
id|reg
suffix:semicolon
r_int
id|cpu
comma
id|rc
suffix:semicolon
id|local_irq_disable
c_func
(paren
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
(brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* CPU is going idle. */
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|rc
op_assign
id|notifier_call_chain
c_func
(paren
op_amp
id|idle_chain
comma
id|CPU_IDLE
comma
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|NOTIFY_OK
op_logical_and
id|rc
op_ne
id|NOTIFY_DONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|NOTIFY_OK
)paren
(brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* enable monitor call class 0 */
id|__ctl_set_bit
c_func
(paren
l_int|8
comma
l_int|15
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HOTPLUG_CPU
r_if
c_cond
(paren
id|cpu_is_offline
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
id|cpu_die
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* &n;&t; * Wait for external, I/O or machine check interrupt and&n;&t; * switch off machine check bit after the wait has ended.&n;&t; */
id|wait_psw.mask
op_assign
id|PSW_KERNEL_BITS
op_or
id|PSW_MASK_MCHECK
op_or
id|PSW_MASK_WAIT
op_or
id|PSW_MASK_IO
op_or
id|PSW_MASK_EXT
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
id|asm
r_volatile
(paren
l_string|&quot;    basr %0,0&bslash;n&quot;
l_string|&quot;0:  la   %0,1f-0b(%0)&bslash;n&quot;
l_string|&quot;    st   %0,4(%1)&bslash;n&quot;
l_string|&quot;    oi   4(%1),0x80&bslash;n&quot;
l_string|&quot;    lpsw 0(%1)&bslash;n&quot;
l_string|&quot;1:  la   %0,2f-1b(%0)&bslash;n&quot;
l_string|&quot;    st   %0,4(%1)&bslash;n&quot;
l_string|&quot;    oi   4(%1),0x80&bslash;n&quot;
l_string|&quot;    ni   1(%1),0xf9&bslash;n&quot;
l_string|&quot;    lpsw 0(%1)&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|wait_psw
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|asm
r_volatile
(paren
l_string|&quot;    larl  %0,0f&bslash;n&quot;
l_string|&quot;    stg   %0,8(%1)&bslash;n&quot;
l_string|&quot;    lpswe 0(%1)&bslash;n&quot;
l_string|&quot;0:  larl  %0,1f&bslash;n&quot;
l_string|&quot;    stg   %0,8(%1)&bslash;n&quot;
l_string|&quot;    ni    1(%1),0xf9&bslash;n&quot;
l_string|&quot;    lpswe 0(%1)&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|reg
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|wait_psw
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
)brace
DECL|function|cpu_idle
r_int
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|default_idle
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU:    %d    %s&bslash;n&quot;
comma
id|tsk-&gt;thread_info-&gt;cpu
comma
id|print_tainted
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Process %s (pid: %d, task: %p, ksp: %p)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
(paren
r_void
op_star
)paren
id|tsk
comma
(paren
r_void
op_star
)paren
id|tsk-&gt;thread.ksp
)paren
suffix:semicolon
id|show_registers
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* Show stack backtrace if pt_regs is from kernel mode */
r_if
c_cond
(paren
op_logical_neg
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
)paren
id|show_trace
c_func
(paren
l_int|0
comma
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;gprs
(braket
l_int|15
)braket
)paren
suffix:semicolon
)brace
r_extern
r_void
id|kernel_thread_starter
c_func
(paren
r_void
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;kernel_thread_starter:&bslash;n&quot;
l_string|&quot;    la    2,0(10)&bslash;n&quot;
l_string|&quot;    basr  14,9&bslash;n&quot;
l_string|&quot;    la    2,0&bslash;n&quot;
l_string|&quot;    br    11&bslash;n&quot;
)paren
suffix:semicolon
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
id|regs.psw.mask
op_assign
id|PSW_KERNEL_BITS
op_or
id|PSW_MASK_IO
op_or
id|PSW_MASK_EXT
suffix:semicolon
id|regs.psw.addr
op_assign
(paren
r_int
r_int
)paren
id|kernel_thread_starter
op_or
id|PSW_ADDR_AMODE
suffix:semicolon
id|regs.gprs
(braket
l_int|9
)braket
op_assign
(paren
r_int
r_int
)paren
id|fn
suffix:semicolon
id|regs.gprs
(braket
l_int|10
)braket
op_assign
(paren
r_int
r_int
)paren
id|arg
suffix:semicolon
id|regs.gprs
(braket
l_int|11
)braket
op_assign
(paren
r_int
r_int
)paren
id|do_exit
suffix:semicolon
id|regs.orig_gpr2
op_assign
op_minus
l_int|1
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
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
id|current-&gt;used_math
op_assign
l_int|0
suffix:semicolon
id|clear_tsk_thread_flag
c_func
(paren
id|current
comma
id|TIF_USEDFPU
)paren
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
id|new_stackp
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
id|fake_frame
(brace
r_struct
id|stack_frame
id|sf
suffix:semicolon
r_struct
id|pt_regs
id|childregs
suffix:semicolon
)brace
op_star
id|frame
suffix:semicolon
id|frame
op_assign
(paren
(paren
r_struct
id|fake_frame
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
id|p-&gt;thread.ksp
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|p-&gt;set_child_tid
op_assign
id|p-&gt;clear_child_tid
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Store access registers to kernel stack of new process. */
id|frame-&gt;childregs
op_assign
op_star
id|regs
suffix:semicolon
id|frame-&gt;childregs.gprs
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* child returns 0 on fork. */
id|frame-&gt;childregs.gprs
(braket
l_int|15
)braket
op_assign
id|new_stackp
suffix:semicolon
id|frame-&gt;sf.back_chain
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* new return point is ret_from_fork */
id|frame-&gt;sf.gprs
(braket
l_int|8
)braket
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
multiline_comment|/* fake return stack for resume(), don&squot;t go back to schedule */
id|frame-&gt;sf.gprs
(braket
l_int|9
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
multiline_comment|/* Save access registers to new thread structure. */
id|save_access_regs
c_func
(paren
op_amp
id|p-&gt;thread.acrs
(braket
l_int|0
)braket
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
multiline_comment|/*&n;&t; * save fprs to current-&gt;thread.fp_regs to merge them with&n;&t; * the emulated registers and then copy the result to the child.&n;&t; */
id|save_fp_regs
c_func
(paren
op_amp
id|current-&gt;thread.fp_regs
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|p-&gt;thread.fp_regs
comma
op_amp
id|current-&gt;thread.fp_regs
comma
r_sizeof
(paren
id|s390_fp_regs
)paren
)paren
suffix:semicolon
id|p-&gt;thread.user_seg
op_assign
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|p-&gt;mm-&gt;pgd
)paren
op_or
id|_SEGMENT_TABLE
suffix:semicolon
multiline_comment|/* Set a new TLS ?  */
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_SETTLS
)paren
id|p-&gt;thread.acrs
(braket
l_int|0
)braket
op_assign
id|regs-&gt;gprs
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
multiline_comment|/* Save the fpu registers to new thread structure. */
id|save_fp_regs
c_func
(paren
op_amp
id|p-&gt;thread.fp_regs
)paren
suffix:semicolon
id|p-&gt;thread.user_seg
op_assign
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|p-&gt;mm-&gt;pgd
)paren
op_or
id|_REGION_TABLE
suffix:semicolon
multiline_comment|/* Set a new TLS ?  */
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_SETTLS
)paren
(brace
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_31BIT
)paren
)paren
(brace
id|p-&gt;thread.acrs
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|regs-&gt;gprs
(braket
l_int|6
)braket
suffix:semicolon
)brace
r_else
(brace
id|p-&gt;thread.acrs
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
(paren
id|regs-&gt;gprs
(braket
l_int|6
)braket
op_rshift
l_int|32
)paren
suffix:semicolon
id|p-&gt;thread.acrs
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_int
)paren
id|regs-&gt;gprs
(braket
l_int|6
)braket
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_ARCH_S390X */
multiline_comment|/* start new process with ar4 pointing to the correct address space */
id|p-&gt;thread.mm_segment
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t copy debug registers */
id|memset
c_func
(paren
op_amp
id|p-&gt;thread.per_info
comma
l_int|0
comma
r_sizeof
(paren
id|p-&gt;thread.per_info
)paren
)paren
suffix:semicolon
r_return
l_int|0
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
id|regs.gprs
(braket
l_int|15
)braket
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
id|regs.gprs
(braket
l_int|3
)braket
suffix:semicolon
id|newsp
op_assign
id|regs.orig_gpr2
suffix:semicolon
id|parent_tidptr
op_assign
(paren
r_int
id|__user
op_star
)paren
id|regs.gprs
(braket
l_int|4
)braket
suffix:semicolon
id|child_tidptr
op_assign
(paren
r_int
id|__user
op_star
)paren
id|regs.gprs
(braket
l_int|5
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newsp
)paren
id|newsp
op_assign
id|regs.gprs
(braket
l_int|15
)braket
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|clone_flags
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
id|regs.gprs
(braket
l_int|15
)braket
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
id|regs.orig_gpr2
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
id|regs.gprs
(braket
l_int|3
)braket
comma
(paren
r_char
id|__user
op_star
id|__user
op_star
)paren
id|regs.gprs
(braket
l_int|4
)braket
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
id|task_lock
c_func
(paren
id|current
)paren
suffix:semicolon
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
id|task_unlock
c_func
(paren
id|current
)paren
suffix:semicolon
id|current-&gt;thread.fp_regs.fpc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|MACHINE_HAS_IEEE
)paren
id|asm
r_volatile
(paren
l_string|&quot;sfpc %0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|0
)paren
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
multiline_comment|/*&n; * fill in the FPU structure for a core dump.&n; */
DECL|function|dump_fpu
r_int
id|dump_fpu
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|s390_fp_regs
op_star
id|fpregs
)paren
(brace
macro_line|#ifndef CONFIG_ARCH_S390X
multiline_comment|/*&n;&t; * save fprs to current-&gt;thread.fp_regs to merge them with&n;&t; * the emulated registers and then copy the result to the dump.&n;&t; */
id|save_fp_regs
c_func
(paren
op_amp
id|current-&gt;thread.fp_regs
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fpregs
comma
op_amp
id|current-&gt;thread.fp_regs
comma
r_sizeof
(paren
id|s390_fp_regs
)paren
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|save_fp_regs
c_func
(paren
id|fpregs
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
r_return
l_int|1
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
id|regs-&gt;gprs
(braket
l_int|15
)braket
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
id|current-&gt;mm-&gt;end_code
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
id|current-&gt;mm-&gt;brk
op_plus
id|PAGE_SIZE
op_minus
l_int|1
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
id|TASK_SIZE
op_minus
id|dump-&gt;start_stack
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|dump-&gt;regs
comma
id|regs
comma
r_sizeof
(paren
id|s390_regs
)paren
)paren
suffix:semicolon
id|dump_fpu
(paren
id|regs
comma
op_amp
id|dump-&gt;regs.fp_regs
)paren
suffix:semicolon
id|dump-&gt;regs.per_info
op_assign
id|current-&gt;thread.per_info
suffix:semicolon
)brace
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
r_struct
id|stack_frame
op_star
id|sf
comma
op_star
id|low
comma
op_star
id|high
suffix:semicolon
r_int
r_int
id|return_address
suffix:semicolon
r_int
id|count
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
op_logical_or
op_logical_neg
id|p-&gt;thread_info
)paren
r_return
l_int|0
suffix:semicolon
id|low
op_assign
(paren
r_struct
id|stack_frame
op_star
)paren
id|p-&gt;thread_info
suffix:semicolon
id|high
op_assign
(paren
r_struct
id|stack_frame
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
op_plus
id|THREAD_SIZE
)paren
op_minus
l_int|1
suffix:semicolon
id|sf
op_assign
(paren
r_struct
id|stack_frame
op_star
)paren
(paren
id|p-&gt;thread.ksp
op_amp
id|PSW_ADDR_INSN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sf
op_le
id|low
op_logical_or
id|sf
OG
id|high
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
l_int|16
suffix:semicolon
id|count
op_increment
)paren
(brace
id|sf
op_assign
(paren
r_struct
id|stack_frame
op_star
)paren
(paren
id|sf-&gt;back_chain
op_amp
id|PSW_ADDR_INSN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sf
op_le
id|low
op_logical_or
id|sf
OG
id|high
)paren
r_return
l_int|0
suffix:semicolon
id|return_address
op_assign
id|sf-&gt;gprs
(braket
l_int|8
)braket
op_amp
id|PSW_ADDR_INSN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_sched_functions
c_func
(paren
id|return_address
)paren
)paren
r_return
id|return_address
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
