multiline_comment|/* $Id: process.c,v 1.20 2001/10/03 08:21:39 jonashg Exp $&n; * &n; *  linux/arch/cris/kernel/process.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Copyright (C) 2000, 2001  Axis Communications AB&n; *&n; *  Authors:   Bjorn Wesen (bjornw@axis.com)&n; *&n; *  $Log: process.c,v $&n; *  Revision 1.20  2001/10/03 08:21:39  jonashg&n; *  cause_of_death does not exist if CONFIG_SVINTO_SIM is defined.&n; *&n; *  Revision 1.19  2001/09/26 11:52:54  bjornw&n; *  INIT_MMAP is gone in 2.4.10&n; *&n; *  Revision 1.18  2001/08/21 21:43:51  hp&n; *  Move last watchdog fix inside #ifdef CONFIG_ETRAX_WATCHDOG&n; *&n; *  Revision 1.17  2001/08/21 13:48:01  jonashg&n; *  Added fix by HP to avoid oops when doing a hard_reset_now.&n; *&n; *  Revision 1.16  2001/06/21 02:00:40  hp&n; *  &t;* entry.S: Include asm/unistd.h.&n; *  &t;(_sys_call_table): Use section .rodata, not .data.&n; *  &t;(_kernel_thread): Move from...&n; *  &t;* process.c: ... here.&n; *  &t;* entryoffsets.c (VAL): Break out from...&n; *  &t;(OF): Use VAL.&n; *  &t;(LCLONE_VM): New asmified value from CLONE_VM.&n; *&n; *  Revision 1.15  2001/06/20 16:31:57  hp&n; *  Add comments to describe empty functions according to review.&n; *&n; *  Revision 1.14  2001/05/29 11:27:59  markusl&n; *  Fixed so that hard_reset_now will do reset even if watchdog wasn&squot;t enabled&n; *&n; *  Revision 1.13  2001/03/20 19:44:06  bjornw&n; *  Use the 7th syscall argument for regs instead of current_regs&n; *&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
singleline_comment|//#define DEBUG
multiline_comment|/*&n; * Initial task structure. Make this a per-architecture thing,&n; * because different architectures tend to have different&n; * alignment requirements and potentially different initial&n; * setup.&n; */
DECL|variable|init_fs
r_static
r_struct
id|fs_struct
id|init_fs
op_assign
id|INIT_FS
suffix:semicolon
DECL|variable|init_files
r_static
r_struct
id|files_struct
id|init_files
op_assign
id|INIT_FILES
suffix:semicolon
DECL|variable|init_signals
r_static
r_struct
id|signal_struct
id|init_signals
op_assign
id|INIT_SIGNALS
suffix:semicolon
DECL|variable|init_mm
r_struct
id|mm_struct
id|init_mm
op_assign
id|INIT_MM
c_func
(paren
id|init_mm
)paren
suffix:semicolon
multiline_comment|/*&n; * Initial task structure.&n; *&n; * We need to make sure that this is 8192-byte aligned due to the&n; * way process stacks are handled. This is done by having a special&n; * &quot;init_task&quot; linker map entry..&n; */
DECL|variable|init_task_union
r_union
id|task_union
id|init_task_union
id|__attribute__
c_func
(paren
(paren
id|__section__
c_func
(paren
l_string|&quot;.data.init_task&quot;
)paren
)paren
)paren
op_assign
(brace
id|INIT_TASK
c_func
(paren
id|init_task_union.task
)paren
)brace
suffix:semicolon
multiline_comment|/*&n; * The hlt_counter, disable_hlt and enable_hlt is just here as a hook if&n; * there would ever be a halt sequence (for power save when idle) with&n; * some largish delay when halting or resuming *and* a driver that can&squot;t&n; * afford that delay.  The hlt_counter would then be checked before&n; * executing the halt sequence, and the driver marks the unhaltable&n; * region by enable_hlt/disable_hlt.&n; */
DECL|variable|hlt_counter
r_static
r_int
id|hlt_counter
op_assign
l_int|0
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
DECL|function|cpu_idle
r_int
id|cpu_idle
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|current-&gt;counter
op_assign
op_minus
l_int|100
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* if the watchdog is enabled, we can simply disable interrupts and go&n; * into an eternal loop, and the watchdog will reset the CPU after 0.1s&n; * if on the other hand the watchdog wasn&squot;t enabled, we just enable it and wait&n; */
DECL|function|hard_reset_now
r_void
id|hard_reset_now
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Don&squot;t declare this variable elsewhere.  We don&squot;t want any other&n;&t; * code to know about it than the watchdog handler in entry.S and&n;&t; * this code, implementing hard reset through the watchdog.&n;&t; */
r_extern
r_int
id|cause_of_death
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;*** HARD RESET ***&bslash;n&quot;
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ETRAX_WATCHDOG) &amp;&amp; !defined(CONFIG_SVINTO_SIM)
id|cause_of_death
op_assign
l_int|0xbedead
suffix:semicolon
macro_line|#else
multiline_comment|/* Since we dont plan to keep on reseting the watchdog,&n;&t;   the key can be arbitrary hence three */
op_star
id|R_WATCHDOG
op_assign
id|IO_FIELD
c_func
(paren
id|R_WATCHDOG
comma
id|key
comma
l_int|3
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_WATCHDOG
comma
id|enable
comma
id|start
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/* waiting for RETRIBUTION! */
suffix:semicolon
)brace
)brace
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_void
)paren
(brace
id|hard_reset_now
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Similar to machine_power_off, but don&squot;t shut off power.  Add code&n; * here to freeze the system for e.g. post-mortem debug purpose when&n; * possible.  This halt has nothing to do with the idle halt.&n; */
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* If or when software power-off is implemented, add code here.  */
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/*&n; * When a process does an &quot;exec&quot;, machine state like FPU and debug&n; * registers need to be reset.  This is a hook function for that.&n; * Currently we don&squot;t have any such state to reset, so this is empty.&n; */
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
)brace
id|asmlinkage
r_void
id|ret_from_sys_call
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* setup the child&squot;s kernel stack with a pt_regs and switch_stack on it.&n; * it will be un-nested during _resume and _ret_from_sys_call when the&n; * new thread is scheduled.&n; *&n; * also setup the thread switching structure which is used to keep&n; * thread-specific data during _resumes.&n; *&n; */
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
id|switch_stack
op_star
id|swstack
suffix:semicolon
multiline_comment|/* put the pt_regs structure at the end of the new kernel stack page and fix it up&n;&t; * remember that the task_struct doubles as the kernel stack for the task&n;&t; */
id|childregs
op_assign
id|user_regs
c_func
(paren
id|p
)paren
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
multiline_comment|/* struct copy of pt_regs */
id|childregs-&gt;r10
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* child returns 0 after a fork/clone */
multiline_comment|/* put the switch stack right below the pt_regs */
id|swstack
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|childregs
)paren
op_minus
l_int|1
suffix:semicolon
id|swstack-&gt;r9
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* parameter to ret_from_sys_call, 0 == dont restart the syscall */
multiline_comment|/* we want to return into ret_from_sys_call after the _resume */
id|swstack-&gt;return_ip
op_assign
(paren
r_int
r_int
)paren
id|ret_from_sys_call
suffix:semicolon
multiline_comment|/* fix the user-mode stackpointer */
id|p-&gt;thread.usp
op_assign
id|usp
suffix:semicolon
multiline_comment|/* and the kernel-mode one */
id|p-&gt;thread.ksp
op_assign
(paren
r_int
r_int
)paren
id|swstack
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;copy_thread: new regs at 0x%p, as shown below:&bslash;n&quot;
comma
id|childregs
)paren
suffix:semicolon
id|show_registers
c_func
(paren
id|childregs
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
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
id|current-&gt;debugreg
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
id|dump-&gt;regs
op_assign
op_star
id|regs
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
macro_line|#endif 
)brace
multiline_comment|/* &n; * Be aware of the &quot;magic&quot; 7th argument in the four system-calls below.&n; * They need the latest stackframe, which is put as the 7th argument by&n; * entry.S. The previous arguments are dummies or actually used, but need&n; * to be defined to reach the 7th argument.&n; *&n; * N.B.: Another method to get the stackframe is to use current_regs(). But&n; * it returns the latest stack-frame stacked when going from _user mode_ and&n; * some of these (at least sys_clone) are called from kernel-mode sometimes&n; * (for example during kernel_thread, above) and thus cannot use it. Thus,&n; * to be sure not to get any surprises, we use the method for the other calls&n; * as well.&n; */
DECL|function|sys_fork
id|asmlinkage
r_int
id|sys_fork
c_func
(paren
r_int
id|r10
comma
r_int
id|r11
comma
r_int
id|r12
comma
r_int
id|r13
comma
r_int
id|mof
comma
r_int
id|srp
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|rdusp
c_func
(paren
)paren
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* if newusp is 0, we just grab the old usp */
DECL|function|sys_clone
id|asmlinkage
r_int
id|sys_clone
c_func
(paren
r_int
r_int
id|newusp
comma
r_int
r_int
id|flags
comma
r_int
id|r12
comma
r_int
id|r13
comma
r_int
id|mof
comma
r_int
id|srp
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|newusp
)paren
id|newusp
op_assign
id|rdusp
c_func
(paren
)paren
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|flags
comma
id|newusp
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* vfork is a system call in i386 because of register-pressure - maybe&n; * we can remove it and handle it in libc but we put it here until then.&n; */
DECL|function|sys_vfork
id|asmlinkage
r_int
id|sys_vfork
c_func
(paren
r_int
id|r10
comma
r_int
id|r11
comma
r_int
id|r12
comma
r_int
id|r13
comma
r_int
id|mof
comma
r_int
id|srp
comma
r_struct
id|pt_regs
op_star
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
id|rdusp
c_func
(paren
)paren
comma
id|regs
comma
l_int|0
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
r_const
r_char
op_star
id|fname
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
comma
r_int
id|r13
comma
r_int
id|mof
comma
r_int
id|srp
comma
r_struct
id|pt_regs
op_star
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
id|fname
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
id|regs
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
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * These bracket the sleeping functions..&n; */
r_extern
r_void
id|scheduling_functions_start_here
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scheduling_functions_end_here
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|first_sched
mdefine_line|#define first_sched     ((unsigned long) scheduling_functions_start_here)
DECL|macro|last_sched
mdefine_line|#define last_sched      ((unsigned long) scheduling_functions_end_here)
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
macro_line|#if 0
multiline_comment|/* YURGH. TODO. */
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
id|p
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
l_int|8188
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
l_int|8184
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
id|eip
OL
id|first_sched
op_logical_or
id|eip
op_ge
id|last_sched
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
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|last_sched
macro_line|#undef last_sched
DECL|macro|first_sched
macro_line|#undef first_sched
eof
