multiline_comment|/*&n; *  linux/arch/cris/kernel/ptrace.c&n; *&n; * Parts taken from the m68k port.&n; * &n; * Copyright (c) 2000, 2001 Axis Communications AB&n; *&n; * Authors:   Bjorn Wesen&n; *&n; * $Log: ptrace.c,v $&n; * Revision 1.7  2001/09/26 11:53:49  bjornw&n; * PTRACE_DETACH works more simple in 2.4.10&n; *&n; * Revision 1.6  2001/07/25 16:08:47  bjornw&n; * PTRACE_ATTACH bulk moved into arch-independant code in 2.4.7&n; *&n; * Revision 1.5  2001/03/26 14:24:28  orjanf&n; * * Changed loop condition.&n; * * Added comment documenting non-standard ptrace behaviour.&n; *&n; * Revision 1.4  2001/03/20 19:44:41  bjornw&n; * Use the user_regs macro instead of thread.esp0&n; *&n; * Revision 1.3  2000/12/18 23:45:25  bjornw&n; * Linux/CRIS first version&n; *&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
multiline_comment|/* determines which bits in DCCR the user has access to. */
multiline_comment|/* 1 = access 0 = no access */
DECL|macro|DCCR_MASK
mdefine_line|#define DCCR_MASK 0x0000001f     /* XNZVC */
multiline_comment|/*&n; * Get contents of register REGNO in task TASK.&n; */
DECL|function|get_reg
r_static
r_inline
r_int
id|get_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|regno
)paren
(brace
multiline_comment|/* USP is a special case, it&squot;s not in the pt_regs struct but&n;&t; * in the tasks thread struct&n;&t; */
r_if
c_cond
(paren
id|regno
op_eq
id|PT_USP
)paren
r_return
id|task-&gt;thread.usp
suffix:semicolon
r_else
r_if
c_cond
(paren
id|regno
OL
id|PT_MAX
)paren
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|user_regs
c_func
(paren
id|task
)paren
)paren
(braket
id|regno
)braket
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write contents of register REGNO in task TASK.&n; */
DECL|function|put_reg
r_static
r_inline
r_int
id|put_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|regno
comma
r_int
r_int
id|data
)paren
(brace
r_int
r_int
op_star
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_eq
id|PT_USP
)paren
id|task-&gt;thread.usp
op_assign
id|data
suffix:semicolon
r_else
r_if
c_cond
(paren
id|regno
OL
id|PT_MAX
)paren
(paren
(paren
r_int
r_int
op_star
)paren
id|user_regs
c_func
(paren
id|task
)paren
)paren
(braket
id|regno
)braket
op_assign
id|data
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Called by kernel/ptrace.c when detaching..&n; *&n; * Make sure the single step bit is not set.&n; */
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
multiline_comment|/* Todo - pending singlesteps? */
)brace
multiline_comment|/* Note that this implementation of ptrace behaves differently from vanilla&n; * ptrace.  Contrary to what the man page says, in the PTRACE_PEEKTEXT,&n; * PTRACE_PEEKDATA, and PTRACE_PEEKUSER requests the data variable is not&n; * ignored.  Instead, the data variable is expected to point at a location&n; * (in user space) where the result of the ptrace call is written (instead of&n; * being returned).&n; */
DECL|function|sys_ptrace
id|asmlinkage
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
op_minus
id|ESRCH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|child-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
)paren
r_goto
id|out_tsk
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_ne
id|TASK_STOPPED
)paren
(brace
r_if
c_cond
(paren
id|request
op_ne
id|PTRACE_KILL
)paren
r_goto
id|out_tsk
suffix:semicolon
)brace
r_if
c_cond
(paren
id|child-&gt;p_pptr
op_ne
id|current
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
id|ret
op_assign
op_minus
id|EIO
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
op_logical_or
id|addr
op_ge
r_sizeof
(paren
r_struct
id|user
)paren
)paren
r_break
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default return condition */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
(brace
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|addr
op_rshift
l_int|2
)paren
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
)brace
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
l_int|0
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
op_eq
r_sizeof
(paren
id|data
)paren
)paren
r_break
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
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
op_logical_or
id|addr
op_ge
r_sizeof
(paren
r_struct
id|user
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
(brace
id|addr
op_rshift_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
id|PT_DCCR
)paren
(brace
multiline_comment|/* don&squot;t allow the tracing process to change stuff like&n;&t;&t;&t;&t; * interrupt enable, kernel/user bit, dma enables etc.&n;&t;&t;&t;&t; */
id|data
op_and_assign
id|DCCR_MASK
suffix:semicolon
id|data
op_or_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_DCCR
)paren
op_amp
op_complement
id|DCCR_MASK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|put_reg
c_func
(paren
id|child
comma
id|addr
comma
id|data
)paren
)paren
r_break
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
id|child-&gt;ptrace
op_or_assign
id|PT_TRACESYS
suffix:semicolon
r_else
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_TRACESYS
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
multiline_comment|/* TODO: make sure any pending breakpoint is killed */
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
r_int
id|tmp
suffix:semicolon
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
multiline_comment|/* TODO: make sure any pending breakpoint is killed */
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
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_TRACESYS
suffix:semicolon
multiline_comment|/* TODO: set some clever breakpoint mechanism... */
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
r_case
id|PTRACE_GETREGS
suffix:colon
(brace
multiline_comment|/* Get all gp regs from the child. */
r_int
id|i
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|PT_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
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
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_case
id|PTRACE_SETREGS
suffix:colon
(brace
multiline_comment|/* Set all gp regs in the child. */
r_int
id|i
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|PT_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|get_user
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
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|PT_DCCR
)paren
(brace
id|tmp
op_and_assign
id|DCCR_MASK
suffix:semicolon
id|tmp
op_or_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_DCCR
)paren
op_amp
op_complement
id|DCCR_MASK
suffix:semicolon
)brace
id|put_reg
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
id|free_task_struct
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
id|asmlinkage
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
(paren
id|current-&gt;ptrace
op_amp
(paren
id|PT_PTRACED
op_or
id|PT_TRACESYS
)paren
)paren
op_ne
(paren
id|PT_PTRACED
op_or
id|PT_TRACESYS
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* TODO: make a way to distinguish between a syscall stop and SIGTRAP&n;&t; * delivery like in the i386 port ? &n;&t; */
id|current-&gt;exit_code
op_assign
id|SIGTRAP
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
eof
