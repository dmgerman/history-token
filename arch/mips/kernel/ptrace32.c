multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 Ross Biro&n; * Copyright (C) Linus Torvalds&n; * Copyright (C) 1994, 95, 96, 97, 98, 2000 Ralf Baechle&n; * Copyright (C) 1996 David S. Miller&n; * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999 MIPS Technologies, Inc.&n; * Copyright (C) 2000 Ulf Carlsson&n; *&n; * At this time Linux/MIPS64 only supports syscall tracing, even for 32-bit&n; * binaries.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
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
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|security_ptrace
c_func
(paren
id|current-&gt;parent
comma
id|current
)paren
)paren
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
multiline_comment|/* Read the word at location addr in the USER area. */
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
id|child-&gt;thread_info
op_plus
id|THREAD_SIZE
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
multiline_comment|/* Default return value. */
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
id|fpureg_t
op_star
id|fregs
op_assign
id|get_fpu_regs
c_func
(paren
id|child
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * The odd registers are actually the high&n;&t;&t;&t;&t; * order bits of the values stored in the even&n;&t;&t;&t;&t; * registers - unless we&squot;re using r2k_switch.S.&n;&t;&t;&t;&t; */
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
l_int|1
suffix:semicolon
multiline_comment|/* FP not yet used  */
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
r_if
c_cond
(paren
id|cpu_has_fpu
)paren
id|tmp
op_assign
id|child-&gt;thread.fpu.hard.fcr31
suffix:semicolon
r_else
id|tmp
op_assign
id|child-&gt;thread.fpu.soft.fcr31
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
r_if
c_cond
(paren
op_logical_neg
id|cpu_has_fpu
)paren
r_break
suffix:semicolon
id|flags
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
id|__enable_fpu
c_func
(paren
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
id|write_c0_status
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
id|child-&gt;thread_info
op_plus
id|THREAD_SIZE
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
id|fpureg_t
op_star
id|fregs
op_assign
id|get_fpu_regs
c_func
(paren
id|child
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child-&gt;used_math
)paren
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
id|child-&gt;thread.fpu.hard.fcr31
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
multiline_comment|/* Must cast, lest sign extension fill upper&n;&t;&t;&t;&t;   bits!  */
id|fregs
(braket
id|addr
op_minus
id|FPR_BASE
)braket
op_or_assign
(paren
r_int
r_int
)paren
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
r_if
c_cond
(paren
id|cpu_has_fpu
)paren
id|child-&gt;thread.fpu.hard.fcr31
op_assign
id|data
suffix:semicolon
r_else
id|child-&gt;thread.fpu.soft.fcr31
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
r_break
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
multiline_comment|/*&n;&t; * make the child exit.  Best I can do is send it a sigkill.&n;&t; * perhaps it should be put in the status that it wants to&n;&t; * exit.&n;&t; */
r_case
id|PTRACE_KILL
suffix:colon
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
eof
