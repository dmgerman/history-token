multiline_comment|/*&n; *  linux/arch/h8300/kernel/ptrace.c&n; *&n; *  Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; *&n; *  Based on:&n; *  linux/arch/m68k/kernel/ptrace.c&n; *&n; *  Copyright (C) 1994 by Hamish Macdonald&n; *  Taken from linux/kernel/ptrace.c and modified for M680x0.&n; *  linux/kernel/ptrace.c is by Ross Biro 1/23/92, edited by Linus Torvalds&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of&n; * this archive for more details.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
multiline_comment|/* cpu depend functions */
r_extern
r_int
id|h8300_get_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|regno
)paren
suffix:semicolon
r_extern
r_int
id|h8300_put_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|regno
comma
r_int
r_int
id|data
)paren
suffix:semicolon
r_extern
r_void
id|h8300_disable_trace
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
suffix:semicolon
r_extern
r_void
id|h8300_enable_trace
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
suffix:semicolon
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
r_inline
DECL|function|read_long
r_static
r_int
id|read_long
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|addr
comma
r_int
r_int
op_star
id|result
)paren
(brace
op_star
id|result
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|h8300_disable_trace
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
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
id|ret
op_assign
id|read_long
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
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
op_assign
l_int|0
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
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default return condition */
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
multiline_comment|/* temporary hack. */
r_if
c_cond
(paren
id|addr
OL
id|H8300_REGS_NO
)paren
id|tmp
op_assign
id|h8300_get_reg
c_func
(paren
id|child
comma
id|addr
)paren
suffix:semicolon
r_else
(brace
r_switch
c_cond
(paren
id|addr
)paren
(brace
r_case
l_int|49
suffix:colon
id|tmp
op_assign
id|child-&gt;mm-&gt;start_code
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|tmp
op_assign
id|child-&gt;mm-&gt;start_data
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|51
suffix:colon
id|tmp
op_assign
id|child-&gt;mm-&gt;end_code
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|52
suffix:colon
id|tmp
op_assign
id|child-&gt;mm-&gt;end_data
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
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
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
multiline_comment|/* temporary hack. */
r_if
c_cond
(paren
id|addr
op_eq
id|PT_ORIG_ER0
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
r_if
c_cond
(paren
id|addr
OL
id|H8300_REGS_NO
)paren
(brace
id|ret
op_assign
id|h8300_put_reg
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
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
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
op_ge
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
id|set_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
r_else
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
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
multiline_comment|/* make sure the single step bit is not set. */
id|h8300_disable_trace
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
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
id|child-&gt;exit_state
op_eq
id|EXIT_ZOMBIE
)paren
multiline_comment|/* already dead */
r_break
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|SIGKILL
suffix:semicolon
id|h8300_disable_trace
c_func
(paren
id|child
)paren
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
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
id|h8300_enable_trace
c_func
(paren
id|child
)paren
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
OL
id|H8300_REGS_NO
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp
op_assign
id|h8300_get_reg
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
OL
id|H8300_REGS_NO
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
id|h8300_put_reg
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
id|ptrace_notify
c_func
(paren
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
