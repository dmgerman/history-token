multiline_comment|/* $Id: process.c,v 1.3 2003/07/04 08:27:41 starvik Exp $&n; * &n; *  linux/arch/cris/kernel/process.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Copyright (C) 2000-2002  Axis Communications AB&n; *&n; *  Authors:   Bjorn Wesen (bjornw@axis.com)&n; *             Mikael Starvik (starvik@axis.com)&n; *&n; * This file handles the architecture-dependent parts of process handling..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_ETRAX_GPIO
r_void
id|etrax_gpio_wake_up_check
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* drivers/gpio.c */
macro_line|#endif
multiline_comment|/*&n; * We use this if we don&squot;t have any better&n; * idle routine..&n; */
DECL|function|default_idle
r_void
id|default_idle
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ETRAX_GPIO
id|etrax_gpio_wake_up_check
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#if defined(CONFIG_ETRAX_WATCHDOG) &amp;&amp; !defined(CONFIG_SVINTO_SIM)
r_extern
r_int
id|cause_of_death
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;*** HARD RESET ***&bslash;n&quot;
)paren
suffix:semicolon
id|local_irq_disable
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
id|t
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|user_regs
c_func
(paren
id|t-&gt;thread_info
)paren
op_member_access_from_pointer
id|irp
suffix:semicolon
)brace
DECL|function|kernel_thread_helper
r_static
r_void
id|kernel_thread_helper
c_func
(paren
r_void
op_star
id|dummy
comma
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
)paren
(brace
id|fn
c_func
(paren
id|arg
)paren
suffix:semicolon
id|do_exit
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Should never be called, return bad exit value */
)brace
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
multiline_comment|/* Don&squot;t use r10 since that is set to 0 in copy_thread */
id|regs.r11
op_assign
(paren
r_int
r_int
)paren
id|fn
suffix:semicolon
id|regs.r12
op_assign
(paren
r_int
r_int
)paren
id|arg
suffix:semicolon
id|regs.irp
op_assign
(paren
r_int
r_int
)paren
id|kernel_thread_helper
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
multiline_comment|/* setup the child&squot;s kernel stack with a pt_regs and switch_stack on it.&n; * it will be un-nested during _resume and _ret_from_sys_call when the&n; * new thread is scheduled.&n; *&n; * also setup the thread switching structure which is used to keep&n; * thread-specific data during _resumes.&n; *&n; */
id|asmlinkage
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
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
id|p-&gt;thread_info
)paren
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
multiline_comment|/* struct copy of pt_regs */
id|p-&gt;set_child_tid
op_assign
id|p-&gt;clear_child_tid
op_assign
l_int|NULL
suffix:semicolon
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
id|ret_from_fork
suffix:semicolon
multiline_comment|/* Will call ret_from_sys_call */
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
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* if newusp is 0, we just grab the old usp */
multiline_comment|/* FIXME: Is parent_tid/child_tid really third/fourth argument? Update lib? */
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
op_star
id|parent_tid
comma
r_int
op_star
id|child_tid
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
op_amp
op_complement
id|CLONE_IDLETASK
comma
id|newusp
comma
id|regs
comma
l_int|0
comma
id|parent_tid
comma
id|child_tid
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
