multiline_comment|/*&n; *  linux/arch/m68k/kernel/ptrace.c&n; *&n; *  Copyright (C) 1994 by Hamish Macdonald&n; *  Taken from linux/kernel/ptrace.c and modified for M680x0.&n; *  linux/kernel/ptrace.c is by Ross Biro 1/23/92, edited by Linus Torvalds&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of&n; * this archive for more details.&n; */
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
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
multiline_comment|/* determines which bits in the SR the user has access to. */
multiline_comment|/* 1 = access 0 = no access */
DECL|macro|SR_MASK
mdefine_line|#define SR_MASK 0x001f
multiline_comment|/* sets the trace bits. */
DECL|macro|TRACE_BITS
mdefine_line|#define TRACE_BITS 0x8000
multiline_comment|/* Find the stack offset for a register, relative to thread.esp0. */
DECL|macro|PT_REG
mdefine_line|#define PT_REG(reg)&t;((long)&amp;((struct pt_regs *)0)-&gt;reg)
DECL|macro|SW_REG
mdefine_line|#define SW_REG(reg)&t;((long)&amp;((struct switch_stack *)0)-&gt;reg &bslash;&n;&t;&t;&t; - sizeof(struct switch_stack))
multiline_comment|/* Mapping from PT_xxx to the stack offset at which the register is&n;   saved.  Notice that usp has no stack-slot and needs to be treated&n;   specially (see get_reg/put_reg below). */
DECL|variable|regoff
r_static
r_int
id|regoff
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
id|PT_REG
c_func
(paren
id|d1
)paren
comma
(braket
l_int|1
)braket
op_assign
id|PT_REG
c_func
(paren
id|d2
)paren
comma
(braket
l_int|2
)braket
op_assign
id|PT_REG
c_func
(paren
id|d3
)paren
comma
(braket
l_int|3
)braket
op_assign
id|PT_REG
c_func
(paren
id|d4
)paren
comma
(braket
l_int|4
)braket
op_assign
id|PT_REG
c_func
(paren
id|d5
)paren
comma
(braket
l_int|5
)braket
op_assign
id|SW_REG
c_func
(paren
id|d6
)paren
comma
(braket
l_int|6
)braket
op_assign
id|SW_REG
c_func
(paren
id|d7
)paren
comma
(braket
l_int|7
)braket
op_assign
id|PT_REG
c_func
(paren
id|a0
)paren
comma
(braket
l_int|8
)braket
op_assign
id|PT_REG
c_func
(paren
id|a1
)paren
comma
(braket
l_int|9
)braket
op_assign
id|PT_REG
c_func
(paren
id|a2
)paren
comma
(braket
l_int|10
)braket
op_assign
id|SW_REG
c_func
(paren
id|a3
)paren
comma
(braket
l_int|11
)braket
op_assign
id|SW_REG
c_func
(paren
id|a4
)paren
comma
(braket
l_int|12
)braket
op_assign
id|SW_REG
c_func
(paren
id|a5
)paren
comma
(braket
l_int|13
)braket
op_assign
id|SW_REG
c_func
(paren
id|a6
)paren
comma
(braket
l_int|14
)braket
op_assign
id|PT_REG
c_func
(paren
id|d0
)paren
comma
(braket
l_int|15
)braket
op_assign
op_minus
l_int|1
comma
(braket
l_int|16
)braket
op_assign
id|PT_REG
c_func
(paren
id|orig_d0
)paren
comma
(braket
l_int|17
)braket
op_assign
id|PT_REG
c_func
(paren
id|sr
)paren
comma
(braket
l_int|18
)braket
op_assign
id|PT_REG
c_func
(paren
id|pc
)paren
comma
)brace
suffix:semicolon
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
id|regno
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
id|addr
op_assign
op_amp
id|task-&gt;thread.usp
suffix:semicolon
r_else
r_if
c_cond
(paren
id|regno
OL
r_sizeof
(paren
id|regoff
)paren
op_div
r_sizeof
(paren
id|regoff
(braket
l_int|0
)braket
)paren
)paren
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|task-&gt;thread.esp0
op_plus
id|regoff
(braket
id|regno
)braket
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
r_return
op_star
id|addr
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
id|addr
op_assign
op_amp
id|task-&gt;thread.usp
suffix:semicolon
r_else
r_if
c_cond
(paren
id|regno
OL
r_sizeof
(paren
id|regoff
)paren
op_div
r_sizeof
(paren
id|regoff
(braket
l_int|0
)braket
)paren
)paren
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|task-&gt;thread.esp0
op_plus
id|regoff
(braket
id|regno
)braket
)paren
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
op_star
id|addr
op_assign
id|data
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
r_int
r_int
id|tmp
suffix:semicolon
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_SR
)paren
op_amp
op_complement
(paren
id|TRACE_BITS
op_lshift
l_int|16
)paren
suffix:semicolon
id|put_reg
c_func
(paren
id|child
comma
id|PT_SR
comma
id|tmp
)paren
suffix:semicolon
id|child-&gt;thread.work.delayed_trace
op_assign
l_int|0
suffix:semicolon
id|child-&gt;thread.work.syscall_trace
op_assign
l_int|0
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
template_param
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
l_int|3
)paren
r_break
suffix:semicolon
id|tmp
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
l_int|19
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
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
id|PT_SR
)paren
id|tmp
op_rshift_assign
l_int|16
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addr
op_ge
l_int|21
op_logical_and
id|addr
OL
l_int|49
)paren
(brace
id|tmp
op_assign
id|child-&gt;thread.fp
(braket
id|addr
op_minus
l_int|21
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_M68KFPU_EMU
multiline_comment|/* Convert internal fpu reg representation&n;&t;&t;&t;&t; * into long double format&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|FPU_IS_EMU
op_logical_and
(paren
id|addr
OL
l_int|45
)paren
op_logical_and
op_logical_neg
(paren
id|addr
op_mod
l_int|3
)paren
)paren
id|tmp
op_assign
(paren
(paren
id|tmp
op_amp
l_int|0xffff0000
)paren
op_lshift
l_int|15
)paren
op_or
(paren
(paren
id|tmp
op_amp
l_int|0x0000ffff
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
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
template_param
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
l_int|3
)paren
r_break
suffix:semicolon
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
id|PT_SR
)paren
(brace
id|data
op_and_assign
id|SR_MASK
suffix:semicolon
id|data
op_lshift_assign
l_int|16
suffix:semicolon
id|data
op_or_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_SR
)paren
op_amp
op_complement
(paren
id|SR_MASK
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
OL
l_int|19
)paren
(brace
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
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
op_ge
l_int|21
op_logical_and
id|addr
OL
l_int|48
)paren
(brace
macro_line|#ifdef CONFIG_M68KFPU_EMU
multiline_comment|/* Convert long double format&n;&t;&t;&t;&t; * into internal fpu reg representation&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|FPU_IS_EMU
op_logical_and
(paren
id|addr
OL
l_int|45
)paren
op_logical_and
op_logical_neg
(paren
id|addr
op_mod
l_int|3
)paren
)paren
(brace
id|data
op_assign
(paren
r_int
r_int
)paren
id|data
op_lshift
l_int|15
suffix:semicolon
id|data
op_assign
(paren
id|data
op_amp
l_int|0xffff0000
)paren
op_or
(paren
(paren
id|data
op_amp
l_int|0x0000ffff
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
id|child-&gt;thread.fp
(braket
id|addr
op_minus
l_int|21
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
(brace
id|child-&gt;thread.work.syscall_trace
op_assign
op_complement
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|child-&gt;thread.work.syscall_trace
op_assign
l_int|0
suffix:semicolon
)brace
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_SR
)paren
op_amp
op_complement
(paren
id|TRACE_BITS
op_lshift
l_int|16
)paren
suffix:semicolon
id|put_reg
c_func
(paren
id|child
comma
id|PT_SR
comma
id|tmp
)paren
suffix:semicolon
id|child-&gt;thread.work.delayed_trace
op_assign
l_int|0
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
multiline_comment|/*&n; * make the child exit.  Best I can do is send it a sigkill.&n; * perhaps it should be put in the status that it wants to&n; * exit.&n; */
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
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_SR
)paren
op_amp
op_complement
(paren
id|TRACE_BITS
op_lshift
l_int|16
)paren
suffix:semicolon
id|put_reg
c_func
(paren
id|child
comma
id|PT_SR
comma
id|tmp
)paren
suffix:semicolon
id|child-&gt;thread.work.delayed_trace
op_assign
l_int|0
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
id|child-&gt;thread.work.syscall_trace
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_SR
)paren
op_or
(paren
id|TRACE_BITS
op_lshift
l_int|16
)paren
suffix:semicolon
id|put_reg
c_func
(paren
id|child
comma
id|PT_SR
comma
id|tmp
)paren
suffix:semicolon
id|child-&gt;thread.work.delayed_trace
op_assign
l_int|1
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
l_int|19
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
id|i
op_eq
id|PT_SR
)paren
id|tmp
op_rshift_assign
l_int|16
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
l_int|19
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
id|PT_SR
)paren
(brace
id|tmp
op_and_assign
id|SR_MASK
suffix:semicolon
id|tmp
op_lshift_assign
l_int|16
suffix:semicolon
id|tmp
op_or_assign
id|get_reg
c_func
(paren
id|child
comma
id|PT_SR
)paren
op_amp
op_complement
(paren
id|SR_MASK
op_lshift
l_int|16
)paren
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
r_case
id|PTRACE_GETFPREGS
suffix:colon
(brace
multiline_comment|/* Get the child FPU state. */
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|data
comma
op_amp
id|child-&gt;thread.fp
comma
r_sizeof
(paren
r_struct
id|user_m68kfp_struct
)paren
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_SETFPREGS
suffix:colon
(brace
multiline_comment|/* Set the child FPU state. */
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|child-&gt;thread.fp
comma
(paren
r_void
op_star
)paren
id|data
comma
r_sizeof
(paren
r_struct
id|user_m68kfp_struct
)paren
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|ret
op_assign
id|ptrace_request
c_func
(paren
id|child
comma
id|request
comma
id|addr
comma
id|data
)paren
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
id|current-&gt;thread.work.delayed_trace
op_logical_and
op_logical_neg
id|current-&gt;thread.work.syscall_trace
)paren
r_return
suffix:semicolon
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
eof
