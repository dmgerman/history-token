multiline_comment|/*&n; *  linux/arch/ppc64/kernel/ptrace32.c&n; *&n; *  PowerPC version&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Derived from &quot;arch/m68k/kernel/ptrace.c&quot;&n; *  Copyright (C) 1994 by Hamish Macdonald&n; *  Taken from linux/kernel/ptrace.c and modified for M680x0.&n; *  linux/kernel/ptrace.c is by Ross Biro 1/23/92, edited by Linus Torvalds&n; *&n; * Modified by Cort Dougan (cort@hq.fsmlabs.com)&n; * and Paul Mackerras (paulus@linuxcare.com.au).&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file README.legal in the main directory of&n; * this archive for more details.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ptrace-common.h&gt;
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
DECL|function|sys32_ptrace
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
r_int
id|addr
comma
r_int
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
op_assign
op_minus
id|EPERM
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
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
id|u32
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Read 4 bytes of the other process&squot; storage&n;&t; *  data is a pointer specifying where the user wants the&n;&t; *&t;4 bytes copied into&n;&t; *  addr is a pointer in the user&squot;s storage that contains an 8 byte&n;&t; *&t;address in the other process of the 4 bytes that is to be read&n;&t; * (this is run in a 32-bit process looking at a 64-bit process)&n;&t; * when I and D space are separate, these will need to be fixed.&n;&t; */
r_case
id|PPC_PTRACE_PEEKTEXT_3264
suffix:colon
r_case
id|PPC_PTRACE_PEEKDATA_3264
suffix:colon
(brace
id|u32
id|tmp
suffix:semicolon
r_int
id|copied
suffix:semicolon
id|u32
op_star
id|addrOthers
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* Get the addr in the other process that we want to read */
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|addrOthers
comma
(paren
id|u32
op_star
op_star
)paren
id|addr
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|copied
op_assign
id|access_process_vm
c_func
(paren
id|child
comma
(paren
id|u64
)paren
id|addrOthers
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
id|u32
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Read a register (specified by ADDR) out of the &quot;user area&quot; */
r_case
id|PTRACE_PEEKUSR
suffix:colon
(brace
r_int
id|index
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* convert to index and check */
id|index
op_assign
(paren
r_int
r_int
)paren
id|addr
op_rshift
l_int|2
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
(paren
id|index
OG
id|PT_FPSCR32
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
id|PT_FPR0
)paren
(brace
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|index
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|child-&gt;thread.regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|giveup_fpu
c_func
(paren
id|child
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * the user space code considers the floating point&n;&t;&t;&t; * to be an array of unsigned int (32 bits) - the&n;&t;&t;&t; * index passed in is based on this assumption.&n;&t;&t;&t; */
id|tmp
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|child-&gt;thread.fpr
)paren
(braket
id|index
op_minus
id|PT_FPR0
)braket
suffix:semicolon
)brace
id|ret
op_assign
id|put_user
c_func
(paren
(paren
r_int
r_int
)paren
id|tmp
comma
(paren
id|u32
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Read 4 bytes out of the other process&squot; pt_regs area&n;&t; *  data is a pointer specifying where the user wants the&n;&t; *&t;4 bytes copied into&n;&t; *  addr is the offset into the other process&squot; pt_regs structure&n;&t; *&t;that is to be read&n;&t; * (this is run in a 32-bit process looking at a 64-bit process)&n;&t; */
r_case
id|PPC_PTRACE_PEEKUSR_3264
suffix:colon
(brace
id|u32
id|index
suffix:semicolon
id|u32
id|reg32bits
suffix:semicolon
id|u64
id|tmp
suffix:semicolon
id|u32
id|numReg
suffix:semicolon
id|u32
id|part
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* Determine which register the user wants */
id|index
op_assign
(paren
id|u64
)paren
id|addr
op_rshift
l_int|2
suffix:semicolon
id|numReg
op_assign
id|index
op_div
l_int|2
suffix:semicolon
multiline_comment|/* Determine which part of the register the user wants */
r_if
c_cond
(paren
id|index
op_mod
l_int|2
)paren
id|part
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* want the 2nd half of the register (right-most). */
r_else
id|part
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* want the 1st half of the register (left-most). */
multiline_comment|/* Validate the input - check to see if address is on the wrong boundary or beyond the end of the user area */
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|3
)paren
op_logical_or
id|numReg
OG
id|PT_FPSCR
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|numReg
op_ge
id|PT_FPR0
)paren
(brace
r_if
c_cond
(paren
id|child-&gt;thread.regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|giveup_fpu
c_func
(paren
id|child
)paren
suffix:semicolon
id|tmp
op_assign
(paren
(paren
r_int
r_int
r_int
op_star
)paren
id|child-&gt;thread.fpr
)paren
(braket
id|numReg
op_minus
id|PT_FPR0
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* register within PT_REGS struct */
id|tmp
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|numReg
)paren
suffix:semicolon
)brace
id|reg32bits
op_assign
(paren
(paren
id|u32
op_star
)paren
op_amp
id|tmp
)paren
(braket
id|part
)braket
suffix:semicolon
id|ret
op_assign
id|put_user
c_func
(paren
id|reg32bits
comma
(paren
id|u32
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* If I and D space are separate, this will have to be fixed. */
r_case
id|PTRACE_POKETEXT
suffix:colon
multiline_comment|/* write the word at location addr. */
r_case
id|PTRACE_POKEDATA
suffix:colon
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
id|data
suffix:semicolon
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
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
l_int|1
)paren
op_eq
r_sizeof
(paren
id|tmp
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
)brace
multiline_comment|/*&n;&t; * Write 4 bytes into the other process&squot; storage&n;&t; *  data is the 4 bytes that the user wants written&n;&t; *  addr is a pointer in the user&squot;s storage that contains an&n;&t; *&t;8 byte address in the other process where the 4 bytes&n;&t; *&t;that is to be written&n;&t; * (this is run in a 32-bit process looking at a 64-bit process)&n;&t; * when I and D space are separate, these will need to be fixed.&n;&t; */
r_case
id|PPC_PTRACE_POKETEXT_3264
suffix:colon
r_case
id|PPC_PTRACE_POKEDATA_3264
suffix:colon
(brace
id|u32
id|tmp
op_assign
id|data
suffix:semicolon
id|u32
op_star
id|addrOthers
suffix:semicolon
multiline_comment|/* Get the addr in the other process that we want to write into */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|addrOthers
comma
(paren
id|u32
op_star
op_star
)paren
id|addr
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
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
(paren
id|u64
)paren
id|addrOthers
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
l_int|1
)paren
op_eq
r_sizeof
(paren
id|tmp
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
)brace
multiline_comment|/* write the word at location addr in the USER area */
r_case
id|PTRACE_POKEUSR
suffix:colon
(brace
r_int
r_int
id|index
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* convert to index and check */
id|index
op_assign
(paren
r_int
r_int
)paren
id|addr
op_rshift
l_int|2
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
(paren
id|index
OG
id|PT_FPSCR32
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|index
op_eq
id|PT_ORIG_R3
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
id|PT_FPR0
)paren
(brace
id|ret
op_assign
id|put_reg
c_func
(paren
id|child
comma
id|index
comma
id|data
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|child-&gt;thread.regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|giveup_fpu
c_func
(paren
id|child
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * the user space code considers the floating point&n;&t;&t;&t; * to be an array of unsigned int (32 bits) - the&n;&t;&t;&t; * index passed in is based on this assumption.&n;&t;&t;&t; */
(paren
(paren
r_int
r_int
op_star
)paren
id|child-&gt;thread.fpr
)paren
(braket
id|index
op_minus
id|PT_FPR0
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
)brace
multiline_comment|/*&n;&t; * Write 4 bytes into the other process&squot; pt_regs area&n;&t; *  data is the 4 bytes that the user wants written&n;&t; *  addr is the offset into the other process&squot; pt_regs structure&n;&t; *&t;that is to be written into&n;&t; * (this is run in a 32-bit process looking at a 64-bit process)&n;&t; */
r_case
id|PPC_PTRACE_POKEUSR_3264
suffix:colon
(brace
id|u32
id|index
suffix:semicolon
id|u32
id|numReg
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* Determine which register the user wants */
id|index
op_assign
(paren
id|u64
)paren
id|addr
op_rshift
l_int|2
suffix:semicolon
id|numReg
op_assign
id|index
op_div
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Validate the input - check to see if address is on the&n;&t;&t; * wrong boundary or beyond the end of the user area&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|3
)paren
op_logical_or
(paren
id|numReg
OG
id|PT_FPSCR
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* Insure it is a register we let them change */
r_if
c_cond
(paren
(paren
id|numReg
op_eq
id|PT_ORIG_R3
)paren
op_logical_or
(paren
(paren
id|numReg
OG
id|PT_CCR
)paren
op_logical_and
(paren
id|numReg
OL
id|PT_FPR0
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|numReg
op_ge
id|PT_FPR0
)paren
(brace
r_if
c_cond
(paren
id|child-&gt;thread.regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|giveup_fpu
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|numReg
op_eq
id|PT_MSR
)paren
id|data
op_assign
(paren
id|data
op_amp
id|MSR_DEBUGCHANGE
)paren
op_or
(paren
id|child-&gt;thread.regs-&gt;msr
op_amp
op_complement
id|MSR_DEBUGCHANGE
)paren
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|child-&gt;thread.regs
)paren
(braket
id|index
)braket
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
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
multiline_comment|/* make sure the single step bit is not set. */
id|clear_single_step
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
multiline_comment|/*&n;&t; * make the child exit.  Best I can do is send it a sigkill.&n;&t; * perhaps it should be put in the status that it wants to&n;&t; * exit.&n;&t; */
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
multiline_comment|/* make sure the single step bit is not set. */
id|clear_single_step
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
id|set_single_step
c_func
(paren
id|child
)paren
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
id|PPC_PTRACE_GETREGS
suffix:colon
(brace
multiline_comment|/* Get GPRs 0 - 31. */
r_int
id|i
suffix:semicolon
r_int
r_int
op_star
id|reg
op_assign
op_amp
(paren
(paren
r_int
r_int
op_star
)paren
id|child-&gt;thread.regs
)paren
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_int
op_star
id|tmp
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ret
op_assign
id|put_user
c_func
(paren
op_star
id|reg
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_break
suffix:semicolon
id|reg
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|PPC_PTRACE_SETREGS
suffix:colon
(brace
multiline_comment|/* Set GPRs 0 - 31. */
r_int
id|i
suffix:semicolon
r_int
r_int
op_star
id|reg
op_assign
op_amp
(paren
(paren
r_int
r_int
op_star
)paren
id|child-&gt;thread.regs
)paren
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_int
op_star
id|tmp
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ret
op_assign
id|get_user
c_func
(paren
op_star
id|reg
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_break
suffix:semicolon
id|reg
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|PPC_PTRACE_GETFPREGS
suffix:colon
(brace
multiline_comment|/* Get FPRs 0 - 31. */
r_int
id|i
suffix:semicolon
r_int
r_int
op_star
id|reg
op_assign
op_amp
(paren
(paren
r_int
r_int
op_star
)paren
id|child-&gt;thread.fpr
)paren
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_int
op_star
id|tmp
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;thread.regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|giveup_fpu
c_func
(paren
id|child
)paren
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ret
op_assign
id|put_user
c_func
(paren
op_star
id|reg
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_break
suffix:semicolon
id|reg
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|PPC_PTRACE_SETFPREGS
suffix:colon
(brace
multiline_comment|/* Get FPRs 0 - 31. */
r_int
id|i
suffix:semicolon
r_int
r_int
op_star
id|reg
op_assign
op_amp
(paren
(paren
r_int
r_int
op_star
)paren
id|child-&gt;thread.fpr
)paren
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_int
op_star
id|tmp
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;thread.regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|giveup_fpu
c_func
(paren
id|child
)paren
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ret
op_assign
id|get_user
c_func
(paren
op_star
id|reg
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_break
suffix:semicolon
id|reg
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
)brace
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
eof
