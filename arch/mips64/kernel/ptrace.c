multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 Ross Biro&n; * Copyright (C) Linus Torvalds&n; * Copyright (C) 1994, 95, 96, 97, 98, 2000 Ralf Baechle&n; * Copyright (C) 1996 David S. Miller&n; * Copyright (C) 2000 Ulf Carlsson&n; *&n; * At this time Linux/MIPS64 only supports syscall tracing, even for 32-bit&n; * binaries.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * Called by kernel/ptrace.c when detaching..&n; *&n; * Make sure single step bits etc are not set.&n; */
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
multiline_comment|/* Nothing to do.. */
)brace
multiline_comment|/*&n; * Tracing a 32-bit process with a 64-bit strace and vice versa will not&n; * work.  I don&squot;t know how to fix this.&n; */
DECL|function|sys32_ptrace
id|asmlinkage
r_int
id|sys32_ptrace
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
(paren
r_int
r_int
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
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|regs
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
id|child
op_plus
id|KERNEL_STACK_SIZE
op_minus
l_int|32
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|addr
)paren
(brace
r_case
l_int|0
dot
dot
dot
l_int|31
suffix:colon
id|tmp
op_assign
id|regs-&gt;regs
(braket
id|addr
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FPR_BASE
dot
dot
dot
id|FPR_BASE
op_plus
l_int|31
suffix:colon
r_if
c_cond
(paren
id|child-&gt;used_math
)paren
(brace
r_int
r_int
op_star
id|fregs
op_assign
(paren
r_void
op_star
)paren
id|child-&gt;thread.fpu.hard.fp_regs
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|child
)paren
(brace
id|set_cp0_status
c_func
(paren
id|ST0_CU1
comma
id|ST0_CU1
)paren
suffix:semicolon
id|save_fp
c_func
(paren
id|child
)paren
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|ST0_CU1
comma
l_int|0
)paren
suffix:semicolon
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t;&t;&t;&t; * The odd registers are actually the high&n;&t;&t;&t;&t; * order bits of the values stored in the even&n;&t;&t;&t;&t; * registers.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|addr
op_amp
l_int|1
)paren
id|tmp
op_assign
(paren
r_int
r_int
)paren
(paren
id|fregs
(braket
(paren
(paren
id|addr
op_amp
op_complement
l_int|1
)paren
op_minus
l_int|32
)paren
)braket
op_rshift
l_int|32
)paren
suffix:semicolon
r_else
id|tmp
op_assign
(paren
r_int
r_int
)paren
(paren
id|fregs
(braket
(paren
id|addr
op_minus
l_int|32
)paren
)braket
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PC
suffix:colon
id|tmp
op_assign
id|regs-&gt;cp0_epc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CAUSE
suffix:colon
id|tmp
op_assign
id|regs-&gt;cp0_cause
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BADVADDR
suffix:colon
id|tmp
op_assign
id|regs-&gt;cp0_badvaddr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMHI
suffix:colon
id|tmp
op_assign
id|regs-&gt;hi
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMLO
suffix:colon
id|tmp
op_assign
id|regs-&gt;lo
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FPC_CSR
suffix:colon
id|tmp
op_assign
id|child-&gt;thread.fpu.hard.control
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FPC_EIR
suffix:colon
(brace
multiline_comment|/* implementation / version register */
r_int
r_int
id|flags
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|ST0_CU1
comma
id|ST0_CU1
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cfc1&bslash;t%0,$0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|tmp
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_tsk
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
op_star
)paren
(paren
r_int
r_int
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
(brace
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|regs
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
id|child
op_plus
id|KERNEL_STACK_SIZE
op_minus
l_int|32
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|addr
)paren
(brace
r_case
l_int|0
dot
dot
dot
l_int|31
suffix:colon
id|regs-&gt;regs
(braket
id|addr
)braket
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FPR_BASE
dot
dot
dot
id|FPR_BASE
op_plus
l_int|31
suffix:colon
(brace
r_int
r_int
op_star
id|fregs
op_assign
(paren
r_void
op_star
)paren
id|child-&gt;thread.fpu.hard.fp_regs
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;used_math
)paren
(brace
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|child
)paren
(brace
id|set_cp0_status
c_func
(paren
id|ST0_CU1
comma
id|ST0_CU1
)paren
suffix:semicolon
id|save_fp
c_func
(paren
id|child
)paren
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|ST0_CU1
comma
l_int|0
)paren
suffix:semicolon
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
id|regs-&gt;cp0_status
op_and_assign
op_complement
id|ST0_CU1
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
multiline_comment|/* FP not yet used  */
id|memset
c_func
(paren
op_amp
id|child-&gt;thread.fpu.hard
comma
op_complement
l_int|0
comma
r_sizeof
(paren
id|child-&gt;thread.fpu.hard
)paren
)paren
suffix:semicolon
id|child-&gt;thread.fpu.hard.control
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * The odd registers are actually the high order bits&n;&t;&t;&t; * of the values stored in the even registers - unless&n;&t;&t;&t; * we&squot;re using r2k_switch.S.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|addr
op_amp
l_int|1
)paren
(brace
id|fregs
(braket
(paren
id|addr
op_amp
op_complement
l_int|1
)paren
op_minus
id|FPR_BASE
)braket
op_and_assign
l_int|0xffffffff
suffix:semicolon
id|fregs
(braket
(paren
id|addr
op_amp
op_complement
l_int|1
)paren
op_minus
id|FPR_BASE
)braket
op_or_assign
(paren
(paren
r_int
r_int
)paren
id|data
)paren
op_lshift
l_int|32
suffix:semicolon
)brace
r_else
(brace
id|fregs
(braket
id|addr
op_minus
id|FPR_BASE
)braket
op_and_assign
op_complement
l_int|0xffffffffLL
suffix:semicolon
id|fregs
(braket
id|addr
op_minus
id|FPR_BASE
)braket
op_or_assign
id|data
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|PC
suffix:colon
id|regs-&gt;cp0_epc
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMHI
suffix:colon
id|regs-&gt;hi
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMLO
suffix:colon
id|regs-&gt;lo
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FPC_CSR
suffix:colon
id|child-&gt;thread.fpu.hard.control
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* The rest are not allowed. */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
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
id|PTRACE_SETOPTIONS
suffix:colon
(brace
r_if
c_cond
(paren
id|data
op_amp
id|PTRACE_O_TRACESYSGOOD
)paren
id|child-&gt;ptrace
op_or_assign
id|PT_TRACESYSGOOD
suffix:semicolon
r_else
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_TRACESYSGOOD
suffix:semicolon
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
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;ptrace(r=%d,pid=%d,addr=%08lx,data=%08lx)&bslash;n&quot;
comma
(paren
r_int
)paren
id|request
comma
(paren
r_int
)paren
id|pid
comma
(paren
r_int
r_int
)paren
id|addr
comma
(paren
r_int
r_int
)paren
id|data
)paren
suffix:semicolon
macro_line|#endif
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
id|out
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
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|regs
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
id|child
op_plus
id|KERNEL_STACK_SIZE
op_minus
l_int|32
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|addr
)paren
(brace
r_case
l_int|0
dot
dot
dot
l_int|31
suffix:colon
id|tmp
op_assign
id|regs-&gt;regs
(braket
id|addr
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FPR_BASE
dot
dot
dot
id|FPR_BASE
op_plus
l_int|31
suffix:colon
r_if
c_cond
(paren
id|child-&gt;used_math
)paren
(brace
r_int
r_int
r_int
op_star
id|fregs
op_assign
(paren
r_int
r_int
r_int
op_star
)paren
op_amp
id|child-&gt;thread.fpu.hard.fp_regs
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|child
)paren
(brace
id|set_cp0_status
c_func
(paren
id|ST0_CU1
comma
id|ST0_CU1
)paren
suffix:semicolon
id|save_fp
c_func
(paren
id|child
)paren
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|ST0_CU1
comma
l_int|0
)paren
suffix:semicolon
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t;&t;&t;&t; * The odd registers are actually the high&n;&t;&t;&t;&t; * order bits of the values stored in the even&n;&t;&t;&t;&t; * registers.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|addr
op_amp
l_int|1
)paren
id|tmp
op_assign
(paren
r_int
r_int
)paren
(paren
id|fregs
(braket
(paren
(paren
id|addr
op_amp
op_complement
l_int|1
)paren
op_minus
l_int|32
)paren
)braket
op_rshift
l_int|32
)paren
suffix:semicolon
r_else
id|tmp
op_assign
(paren
r_int
r_int
)paren
(paren
id|fregs
(braket
(paren
id|addr
op_minus
l_int|32
)paren
)braket
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PC
suffix:colon
id|tmp
op_assign
id|regs-&gt;cp0_epc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CAUSE
suffix:colon
id|tmp
op_assign
id|regs-&gt;cp0_cause
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BADVADDR
suffix:colon
id|tmp
op_assign
id|regs-&gt;cp0_badvaddr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMHI
suffix:colon
id|tmp
op_assign
id|regs-&gt;hi
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMLO
suffix:colon
id|tmp
op_assign
id|regs-&gt;lo
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FPC_CSR
suffix:colon
id|tmp
op_assign
id|child-&gt;thread.fpu.hard.control
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FPC_EIR
suffix:colon
(brace
multiline_comment|/* implementation / version register */
r_int
r_int
id|flags
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|ST0_CU1
comma
id|ST0_CU1
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cfc1&bslash;t%0,$0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|tmp
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_tsk
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
(brace
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|regs
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
id|child
op_plus
id|KERNEL_STACK_SIZE
op_minus
l_int|32
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|addr
)paren
(brace
r_case
l_int|0
dot
dot
dot
l_int|31
suffix:colon
id|regs-&gt;regs
(braket
id|addr
)braket
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FPR_BASE
dot
dot
dot
id|FPR_BASE
op_plus
l_int|31
suffix:colon
(brace
r_int
r_int
op_star
id|fregs
op_assign
(paren
r_void
op_star
)paren
id|child-&gt;thread.fpu.hard.fp_regs
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;used_math
)paren
(brace
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|child
)paren
(brace
id|set_cp0_status
c_func
(paren
id|ST0_CU1
comma
id|ST0_CU1
)paren
suffix:semicolon
id|save_fp
c_func
(paren
id|child
)paren
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|ST0_CU1
comma
l_int|0
)paren
suffix:semicolon
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
id|regs-&gt;cp0_status
op_and_assign
op_complement
id|ST0_CU1
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
multiline_comment|/* FP not yet used  */
id|memset
c_func
(paren
op_amp
id|child-&gt;thread.fpu.hard
comma
op_complement
l_int|0
comma
r_sizeof
(paren
id|child-&gt;thread.fpu.hard
)paren
)paren
suffix:semicolon
id|child-&gt;thread.fpu.hard.control
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * The odd registers are actually the high order bits&n;&t;&t;&t; * of the values stored in the even registers - unless&n;&t;&t;&t; * we&squot;re using r2k_switch.S.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|addr
op_amp
l_int|1
)paren
(brace
id|fregs
(braket
(paren
id|addr
op_amp
op_complement
l_int|1
)paren
op_minus
id|FPR_BASE
)braket
op_and_assign
l_int|0xffffffff
suffix:semicolon
id|fregs
(braket
(paren
id|addr
op_amp
op_complement
l_int|1
)paren
op_minus
id|FPR_BASE
)braket
op_or_assign
(paren
(paren
r_int
r_int
)paren
id|data
)paren
op_lshift
l_int|32
suffix:semicolon
)brace
r_else
(brace
id|fregs
(braket
id|addr
op_minus
id|FPR_BASE
)braket
op_and_assign
op_complement
l_int|0xffffffffLL
suffix:semicolon
id|fregs
(braket
id|addr
op_minus
id|FPR_BASE
)braket
op_or_assign
id|data
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|PC
suffix:colon
id|regs-&gt;cp0_epc
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMHI
suffix:colon
id|regs-&gt;hi
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMLO
suffix:colon
id|regs-&gt;lo
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FPC_CSR
suffix:colon
id|child-&gt;thread.fpu.hard.control
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* The rest are not allowed. */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
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
id|PTRACE_SETOPTIONS
suffix:colon
(brace
r_if
c_cond
(paren
id|data
op_amp
id|PTRACE_O_TRACESYSGOOD
)paren
id|child-&gt;ptrace
op_or_assign
id|PT_TRACESYSGOOD
suffix:semicolon
r_else
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_TRACESYSGOOD
suffix:semicolon
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
multiline_comment|/* The 0x80 provides a way for the tracing parent to distinguish&n;&t;   between a syscall stop and SIGTRAP delivery */
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
