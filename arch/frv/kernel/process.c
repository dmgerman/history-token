multiline_comment|/*&n; *  linux/arch/m68k/kernel/process.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; *&n; *  68060 fixes by Jesper Skov&n; *&n; *  uClinux changes Copyright (C) 2000-2002, David McCullough &lt;davidm@snapgear.com&gt;&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/gdb-stub.h&gt;
macro_line|#include &lt;asm/mb-regs.h&gt;
macro_line|#include &quot;local.h&quot;
id|asmlinkage
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#include &lt;asm/pgalloc.h&gt;
DECL|function|alloc_task_struct
r_struct
id|task_struct
op_star
id|alloc_task_struct
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|p
op_assign
id|kmalloc
c_func
(paren
id|THREAD_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|atomic_set
c_func
(paren
(paren
id|atomic_t
op_star
)paren
(paren
id|p
op_plus
l_int|1
)paren
comma
l_int|1
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|free_task_struct
r_void
id|free_task_struct
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
(paren
id|atomic_t
op_star
)paren
(paren
id|p
op_plus
l_int|1
)paren
)paren
)paren
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|core_sleep_idle
r_static
r_void
id|core_sleep_idle
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef LED_DEBUG_SLEEP
multiline_comment|/* Show that we&squot;re sleeping... */
id|__set_LEDS
c_func
(paren
l_int|0x55aa
)paren
suffix:semicolon
macro_line|#endif
id|frv_cpu_core_sleep
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef LED_DEBUG_SLEEP
multiline_comment|/* ... and that we woke up */
id|__set_LEDS
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|idle
r_void
(paren
op_star
id|idle
)paren
(paren
r_void
)paren
op_assign
id|core_sleep_idle
suffix:semicolon
multiline_comment|/*&n; * The idle thread. There&squot;s no useful work to be&n; * done, so just try to conserve power and have a&n; * low exit latency (ie sit in a loop waiting for&n; * somebody to say that they&squot;d like to reschedule)&n; */
DECL|function|cpu_idle
r_void
id|cpu_idle
c_func
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
r_if
c_cond
(paren
op_logical_neg
id|frv_dma_inprogress
op_logical_and
id|idle
)paren
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
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
r_int
r_int
id|reset_addr
suffix:semicolon
macro_line|#ifdef CONFIG_GDBSTUB
id|gdbstub_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|PSR_IMPLE
c_func
(paren
id|__get_PSR
c_func
(paren
)paren
)paren
op_eq
id|PSR_IMPLE_FR551
)paren
id|reset_addr
op_assign
l_int|0xfefff500
suffix:semicolon
r_else
id|reset_addr
op_assign
l_int|0xfeff0500
suffix:semicolon
multiline_comment|/* Software reset. */
id|asm
r_volatile
(paren
l_string|&quot;      dcef @(gr0,gr0),1 ! membar !&quot;
l_string|&quot;      sti     %1,@(%0,0) !&quot;
l_string|&quot;      nop ! nop ! nop ! nop ! nop ! &quot;
l_string|&quot;      nop ! nop ! nop ! nop ! nop ! &quot;
l_string|&quot;      nop ! nop ! nop ! nop ! nop ! &quot;
l_string|&quot;      nop ! nop ! nop ! nop ! nop ! &quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|reset_addr
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_GDBSTUB
id|gdbstub_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_GDBSTUB
id|gdbstub_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0 
singleline_comment|//ndef NO_FPU
r_int
r_int
id|zero
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
)brace
DECL|function|user_stack
r_inline
r_int
r_int
id|user_stack
c_func
(paren
r_const
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_while
c_loop
(paren
id|regs-&gt;next_frame
)paren
id|regs
op_assign
id|regs-&gt;next_frame
suffix:semicolon
r_return
id|user_mode
c_func
(paren
id|regs
)paren
ques
c_cond
id|regs-&gt;sp
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|sys_fork
id|asmlinkage
r_int
id|sys_fork
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_MMU
multiline_comment|/* fork almost works, enough to trick you into looking elsewhere:-( */
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#else
r_return
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|user_stack
c_func
(paren
id|__frame
)paren
comma
id|__frame
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|sys_vfork
id|asmlinkage
r_int
id|sys_vfork
c_func
(paren
r_void
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
id|user_stack
c_func
(paren
id|__frame
)paren
comma
id|__frame
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clone a process&n; * - tlsptr is retrieved by copy_thread()&n; */
DECL|function|sys_clone
id|asmlinkage
r_int
id|sys_clone
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|newsp
comma
r_int
id|__user
op_star
id|parent_tidptr
comma
r_int
id|__user
op_star
id|child_tidptr
comma
r_int
id|__user
op_star
id|tlsptr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|newsp
)paren
id|newsp
op_assign
id|user_stack
c_func
(paren
id|__frame
)paren
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|clone_flags
comma
id|newsp
comma
id|__frame
comma
l_int|0
comma
id|parent_tidptr
comma
id|child_tidptr
)paren
suffix:semicolon
)brace
multiline_comment|/* end sys_clone() */
multiline_comment|/*****************************************************************************/
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
singleline_comment|//unlazy_fpu(tsk);
)brace
multiline_comment|/* end prepare_to_copy() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * set up the kernel stack and exception frames for a new process&n; */
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
id|usp
comma
r_int
r_int
id|topstk
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
id|childregs0
comma
op_star
id|childregs
comma
op_star
id|regs0
suffix:semicolon
id|regs0
op_assign
id|__kernel_frame0_ptr
suffix:semicolon
id|childregs0
op_assign
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
id|p-&gt;thread_info
op_plus
id|THREAD_SIZE
op_minus
id|USER_CONTEXT_SIZE
)paren
suffix:semicolon
id|childregs
op_assign
id|childregs0
suffix:semicolon
multiline_comment|/* set up the userspace frame (the only place that the USP is stored) */
op_star
id|childregs0
op_assign
op_star
id|regs0
suffix:semicolon
id|childregs0-&gt;gr8
op_assign
l_int|0
suffix:semicolon
id|childregs0-&gt;sp
op_assign
id|usp
suffix:semicolon
id|childregs0-&gt;next_frame
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* set up the return kernel frame if called from kernel_thread() */
r_if
c_cond
(paren
id|regs
op_ne
id|regs0
)paren
(brace
id|childregs
op_decrement
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
id|childregs-&gt;sp
op_assign
(paren
r_int
r_int
)paren
id|childregs0
suffix:semicolon
id|childregs-&gt;next_frame
op_assign
id|childregs0
suffix:semicolon
id|childregs-&gt;gr15
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
suffix:semicolon
id|childregs-&gt;gr29
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
)brace
id|p-&gt;set_child_tid
op_assign
id|p-&gt;clear_child_tid
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;thread.frame
op_assign
id|childregs
suffix:semicolon
id|p-&gt;thread.curr
op_assign
id|p
suffix:semicolon
id|p-&gt;thread.sp
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
id|p-&gt;thread.fp
op_assign
l_int|0
suffix:semicolon
id|p-&gt;thread.lr
op_assign
l_int|0
suffix:semicolon
id|p-&gt;thread.pc
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
id|p-&gt;thread.frame0
op_assign
id|childregs0
suffix:semicolon
multiline_comment|/* the new TLS pointer is passed in as arg #5 to sys_clone() */
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_SETTLS
)paren
id|childregs-&gt;gr29
op_assign
id|childregs-&gt;gr12
suffix:semicolon
id|save_user_regs
c_func
(paren
id|p-&gt;thread.user
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end copy_thread() */
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
macro_line|#if 0
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
id|user_stack
c_func
(paren
id|regs
)paren
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
id|dump-&gt;regs
op_assign
op_star
(paren
r_struct
id|user_context
op_star
)paren
id|regs
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
DECL|function|sys_execve
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
(brace
r_int
id|error
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
id|name
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
id|argv
comma
id|envp
comma
id|__frame
)paren
suffix:semicolon
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
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
id|pt_regs
op_star
id|regs0
suffix:semicolon
r_int
r_int
id|fp
comma
id|pc
suffix:semicolon
r_int
r_int
id|stack_limit
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
id|stack_limit
op_assign
(paren
r_int
r_int
)paren
(paren
id|p
op_plus
l_int|1
)paren
suffix:semicolon
id|fp
op_assign
id|p-&gt;thread.fp
suffix:semicolon
id|regs0
op_assign
id|p-&gt;thread.frame0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|fp
OL
id|stack_limit
op_logical_or
id|fp
op_ge
(paren
r_int
r_int
)paren
id|regs0
op_logical_or
id|fp
op_amp
l_int|3
)paren
r_return
l_int|0
suffix:semicolon
id|pc
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|fp
)paren
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* FIXME: This depends on the order of these functions. */
r_if
c_cond
(paren
op_logical_neg
id|in_sched_functions
c_func
(paren
id|pc
)paren
)paren
r_return
id|pc
suffix:semicolon
id|fp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|fp
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
multiline_comment|/* Check whether the thread is blocked in resume() */
r_if
c_cond
(paren
id|in_sched_functions
c_func
(paren
id|tsk-&gt;thread.pc
)paren
)paren
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|tsk-&gt;thread.fp
)paren
(braket
l_int|2
)braket
suffix:semicolon
r_else
r_return
id|tsk-&gt;thread.pc
suffix:semicolon
)brace
DECL|function|elf_check_arch
r_int
id|elf_check_arch
c_func
(paren
r_const
r_struct
id|elf32_hdr
op_star
id|hdr
)paren
(brace
r_int
r_int
id|hsr0
op_assign
id|__get_HSR
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_int
r_int
id|psr
op_assign
id|__get_PSR
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;e_machine
op_ne
id|EM_FRV
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|hdr-&gt;e_flags
op_amp
id|EF_FRV_GPR_MASK
)paren
(brace
r_case
id|EF_FRV_GPR64
suffix:colon
r_if
c_cond
(paren
(paren
id|hsr0
op_amp
id|HSR0_GRN
)paren
op_eq
id|HSR0_GRN_32
)paren
r_return
l_int|0
suffix:semicolon
r_case
id|EF_FRV_GPR32
suffix:colon
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|hdr-&gt;e_flags
op_amp
id|EF_FRV_FPR_MASK
)paren
(brace
r_case
id|EF_FRV_FPR64
suffix:colon
r_if
c_cond
(paren
(paren
id|hsr0
op_amp
id|HSR0_FRN
)paren
op_eq
id|HSR0_FRN_32
)paren
r_return
l_int|0
suffix:semicolon
r_case
id|EF_FRV_FPR32
suffix:colon
r_case
id|EF_FRV_FPR_NONE
suffix:colon
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|hdr-&gt;e_flags
op_amp
id|EF_FRV_MULADD
)paren
op_eq
id|EF_FRV_MULADD
)paren
r_if
c_cond
(paren
id|PSR_IMPLE
c_func
(paren
id|psr
)paren
op_ne
id|PSR_IMPLE_FR405
op_logical_and
id|PSR_IMPLE
c_func
(paren
id|psr
)paren
op_ne
id|PSR_IMPLE_FR451
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|hdr-&gt;e_flags
op_amp
id|EF_FRV_CPU_MASK
)paren
(brace
r_case
id|EF_FRV_CPU_GENERIC
suffix:colon
r_break
suffix:semicolon
r_case
id|EF_FRV_CPU_FR300
suffix:colon
r_case
id|EF_FRV_CPU_SIMPLE
suffix:colon
r_case
id|EF_FRV_CPU_TOMCAT
suffix:colon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|EF_FRV_CPU_FR400
suffix:colon
r_if
c_cond
(paren
id|PSR_IMPLE
c_func
(paren
id|psr
)paren
op_ne
id|PSR_IMPLE_FR401
op_logical_and
id|PSR_IMPLE
c_func
(paren
id|psr
)paren
op_ne
id|PSR_IMPLE_FR405
op_logical_and
id|PSR_IMPLE
c_func
(paren
id|psr
)paren
op_ne
id|PSR_IMPLE_FR451
op_logical_and
id|PSR_IMPLE
c_func
(paren
id|psr
)paren
op_ne
id|PSR_IMPLE_FR551
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EF_FRV_CPU_FR450
suffix:colon
r_if
c_cond
(paren
id|PSR_IMPLE
c_func
(paren
id|psr
)paren
op_ne
id|PSR_IMPLE_FR451
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EF_FRV_CPU_FR500
suffix:colon
r_if
c_cond
(paren
id|PSR_IMPLE
c_func
(paren
id|psr
)paren
op_ne
id|PSR_IMPLE_FR501
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EF_FRV_CPU_FR550
suffix:colon
r_if
c_cond
(paren
id|PSR_IMPLE
c_func
(paren
id|psr
)paren
op_ne
id|PSR_IMPLE_FR551
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
eof
