multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;linux/errno.h&quot;
macro_line|#include &quot;linux/smp_lock.h&quot;
macro_line|#include &quot;linux/security.h&quot;
macro_line|#include &quot;linux/ptrace.h&quot;
macro_line|#ifdef CONFIG_PROC_MM
macro_line|#include &quot;linux/proc_mm.h&quot;
macro_line|#endif
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;ptrace_user.h&quot;
multiline_comment|/*&n; * Called by kernel/ptrace.c when detaching..&n; */
DECL|function|ptrace_disable
r_void
id|ptrace_disable
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
)brace
r_extern
r_int
id|do_mmap2
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|fd
comma
r_int
r_int
id|pgoff
)paren
suffix:semicolon
DECL|function|sys_ptrace
r_int
id|sys_ptrace
c_func
(paren
r_int
id|request
comma
r_int
id|pid
comma
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
r_int
id|i
comma
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_TRACEME
)paren
(brace
multiline_comment|/* are we already being traced? */
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|security_ptrace
c_func
(paren
id|current-&gt;parent
comma
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* set the ptrace bit in the process flags. */
id|current-&gt;ptrace
op_or_assign
id|PT_PTRACED
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|child
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
id|get_task_struct
c_func
(paren
id|child
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_eq
l_int|1
)paren
multiline_comment|/* you may not mess with init */
r_goto
id|out_tsk
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_ATTACH
)paren
(brace
id|ret
op_assign
id|ptrace_attach
c_func
(paren
id|child
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|ret
op_assign
id|ptrace_check_attach
c_func
(paren
id|child
comma
id|request
op_eq
id|PTRACE_KILL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out_tsk
suffix:semicolon
r_switch
c_cond
(paren
id|request
)paren
(brace
multiline_comment|/* when I and D space are separate, these will need to be fixed. */
r_case
id|PTRACE_PEEKTEXT
suffix:colon
multiline_comment|/* read word at location addr. */
r_case
id|PTRACE_PEEKDATA
suffix:colon
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
id|copied
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
id|copied
op_assign
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copied
op_ne
r_sizeof
(paren
id|tmp
)paren
)paren
r_break
suffix:semicolon
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* read the word at location addr in the USER area. */
r_case
id|PTRACE_PEEKUSR
suffix:colon
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|3
)paren
op_logical_or
id|addr
OL
l_int|0
)paren
r_break
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default return condition */
r_if
c_cond
(paren
id|addr
OL
id|FRAME_SIZE_OFFSET
)paren
(brace
id|tmp
op_assign
id|getreg
c_func
(paren
id|child
comma
id|addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|addr
op_ge
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|0
)braket
)paren
)paren
op_logical_and
(paren
id|addr
op_le
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|7
)braket
)paren
)paren
)paren
(brace
id|addr
op_sub_assign
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
id|tmp
op_assign
id|child-&gt;thread.arch.debugregs
(braket
id|addr
)braket
suffix:semicolon
)brace
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* when I and D space are separate, this will have to be fixed. */
r_case
id|PTRACE_POKETEXT
suffix:colon
multiline_comment|/* write the word at location addr. */
r_case
id|PTRACE_POKEDATA
suffix:colon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|data
comma
r_sizeof
(paren
id|data
)paren
comma
l_int|1
)paren
op_ne
r_sizeof
(paren
id|data
)paren
)paren
r_break
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_POKEUSR
suffix:colon
multiline_comment|/* write the word at location addr in the USER area */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|3
)paren
op_logical_or
id|addr
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|FRAME_SIZE_OFFSET
)paren
(brace
id|ret
op_assign
id|putreg
c_func
(paren
id|child
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|addr
op_ge
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|0
)braket
)paren
)paren
op_logical_and
(paren
id|addr
op_le
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|7
)braket
)paren
)paren
)paren
(brace
id|addr
op_sub_assign
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_eq
l_int|4
)paren
op_logical_or
(paren
id|addr
op_eq
l_int|5
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
id|child-&gt;thread.arch.debugregs
(braket
id|addr
)braket
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PTRACE_SYSCALL
suffix:colon
multiline_comment|/* continue and stop at next (return from) syscall */
r_case
id|PTRACE_CONT
suffix:colon
(brace
multiline_comment|/* restart after signal. */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_SYSCALL
)paren
(brace
id|set_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
)brace
r_else
(brace
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
)brace
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; * make the child exit.  Best I can do is send it a sigkill. &n; * perhaps it should be put in the status that it wants to &n; * exit.&n; */
r_case
id|PTRACE_KILL
suffix:colon
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
multiline_comment|/* already dead */
r_break
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|SIGKILL
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_SINGLESTEP
suffix:colon
(brace
multiline_comment|/* set the trap flag. */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
id|child-&gt;ptrace
op_or_assign
id|PT_DTRACE
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
multiline_comment|/* give it a chance to run. */
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_DETACH
suffix:colon
multiline_comment|/* detach a process that was attached. */
id|ret
op_assign
id|ptrace_detach
c_func
(paren
id|child
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef PTRACE_GETREGS
r_case
id|PTRACE_GETREGS
suffix:colon
(brace
multiline_comment|/* Get all gp regs from the child. */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_int
r_int
op_star
)paren
id|data
comma
id|FRAME_SIZE_OFFSET
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|FRAME_SIZE_OFFSET
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|__put_user
c_func
(paren
id|getreg
c_func
(paren
id|child
comma
id|i
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
id|data
op_add_assign
r_sizeof
(paren
r_int
)paren
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef PTRACE_SETREGS
r_case
id|PTRACE_SETREGS
suffix:colon
(brace
multiline_comment|/* Set all gp regs in the child. */
r_int
r_int
id|tmp
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
(paren
r_int
op_star
)paren
id|data
comma
id|FRAME_SIZE_OFFSET
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|FRAME_SIZE_OFFSET
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|__get_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
id|putreg
c_func
(paren
id|child
comma
id|i
comma
id|tmp
)paren
suffix:semicolon
id|data
op_add_assign
r_sizeof
(paren
r_int
)paren
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef PTRACE_GETFPREGS
r_case
id|PTRACE_GETFPREGS
suffix:colon
multiline_comment|/* Get the child FPU state. */
id|ret
op_assign
id|get_fpregs
c_func
(paren
id|data
comma
id|child
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef PTRACE_SETFPREGS
r_case
id|PTRACE_SETFPREGS
suffix:colon
multiline_comment|/* Set the child FPU state. */
id|ret
op_assign
id|set_fpregs
c_func
(paren
id|data
comma
id|child
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef PTRACE_GETFPXREGS
r_case
id|PTRACE_GETFPXREGS
suffix:colon
multiline_comment|/* Get the child FPU state. */
id|ret
op_assign
id|get_fpxregs
c_func
(paren
id|data
comma
id|child
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef PTRACE_SETFPXREGS
r_case
id|PTRACE_SETFPXREGS
suffix:colon
multiline_comment|/* Set the child FPU state. */
id|ret
op_assign
id|set_fpxregs
c_func
(paren
id|data
comma
id|child
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|PTRACE_FAULTINFO
suffix:colon
(brace
r_struct
id|ptrace_faultinfo
id|fault
suffix:semicolon
id|fault
op_assign
(paren
(paren
r_struct
id|ptrace_faultinfo
)paren
(brace
dot
id|is_write
op_assign
id|child-&gt;thread.err
comma
dot
id|addr
op_assign
id|child-&gt;thread.cr2
)brace
)paren
suffix:semicolon
id|ret
op_assign
id|copy_to_user
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|data
comma
op_amp
id|fault
comma
r_sizeof
(paren
id|fault
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_SIGPENDING
suffix:colon
id|ret
op_assign
id|copy_to_user
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|data
comma
op_amp
id|child-&gt;pending.signal
comma
r_sizeof
(paren
id|child-&gt;pending.signal
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_LDT
suffix:colon
(brace
r_struct
id|ptrace_ldt
id|ldt
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ldt
comma
(paren
r_int
r_int
op_star
)paren
id|data
comma
r_sizeof
(paren
id|ldt
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* This one is confusing, so just punt and return -EIO for &n;&t;&t; * now&n;&t;&t; */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_MM
r_case
id|PTRACE_SWITCH_MM
suffix:colon
(brace
r_struct
id|mm_struct
op_star
id|old
op_assign
id|child-&gt;mm
suffix:semicolon
r_struct
id|mm_struct
op_star
r_new
op_assign
id|proc_mm_get_mm
c_func
(paren
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
r_new
)paren
)paren
(brace
id|ret
op_assign
id|PTR_ERR
c_func
(paren
r_new
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|mm_users
)paren
suffix:semicolon
id|child-&gt;mm
op_assign
r_new
suffix:semicolon
id|child-&gt;active_mm
op_assign
r_new
suffix:semicolon
id|mmput
c_func
(paren
id|old
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out_tsk
suffix:colon
id|put_task_struct
c_func
(paren
id|child
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
id|ret
suffix:semicolon
)brace
DECL|function|syscall_trace
r_void
id|syscall_trace
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_SYSCALL_TRACE
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* the 0x80 provides a way for the tracing parent to distinguish&n;&t;   between a syscall stop and SIGTRAP delivery */
id|current-&gt;exit_code
op_assign
id|SIGTRAP
op_or
(paren
(paren
id|current-&gt;ptrace
op_amp
id|PT_TRACESYSGOOD
)paren
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|notify_parent
c_func
(paren
id|current
comma
id|SIGCHLD
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * this isn&squot;t the same as continuing with a signal, but it will do&n;&t; * for normal use.  strace only continues with a signal if the&n;&t; * stopping signal is not SIGTRAP.  -brl&n;&t; */
r_if
c_cond
(paren
id|current-&gt;exit_code
)paren
(brace
id|send_sig
c_func
(paren
id|current-&gt;exit_code
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|current-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
