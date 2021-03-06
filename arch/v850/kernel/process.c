multiline_comment|/*&n; * arch/v850/kernel/process.c -- Arch-dependent process handling&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
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
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
r_extern
r_void
id|ret_from_fork
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* The idle loop.  */
DECL|function|default_idle
r_void
id|default_idle
(paren
r_void
)paren
(brace
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
(paren
)paren
)paren
id|asm
(paren
l_string|&quot;halt; nop; nop; nop; nop; nop&quot;
op_scope_resolution
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
id|schedule
(paren
)paren
suffix:semicolon
)brace
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
id|default_idle
suffix:semicolon
multiline_comment|/*&n; * The idle thread. There&squot;s no useful work to be&n; * done, so just try to conserve power and have a&n; * low exit latency (ie sit in a loop waiting for&n; * somebody to say that they&squot;d like to reschedule)&n; */
DECL|function|cpu_idle
r_void
id|cpu_idle
(paren
r_void
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
(paren
op_star
id|idle
)paren
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the mechanism for creating a new kernel thread.&n; *&n; * NOTE! Only a kernel-only process (ie the swapper or direct descendants who&n; * haven&squot;t done an &quot;execve()&quot;) should use this: it will work within a system&n; * call from a &quot;real&quot; process, but the process memory space will not be free&squot;d&n; * until both the parent and the child have exited.&n; */
DECL|function|kernel_thread
r_int
id|kernel_thread
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
r_register
id|mm_segment_t
id|fs
op_assign
id|get_fs
(paren
)paren
suffix:semicolon
r_register
r_int
r_int
id|syscall
id|asm
(paren
id|SYSCALL_NUM
)paren
suffix:semicolon
r_register
r_int
r_int
id|arg0
id|asm
(paren
id|SYSCALL_ARG0
)paren
suffix:semicolon
r_register
r_int
r_int
id|ret
id|asm
(paren
id|SYSCALL_RET
)paren
suffix:semicolon
id|set_fs
(paren
id|KERNEL_DS
)paren
suffix:semicolon
multiline_comment|/* Clone this thread.  Note that we don&squot;t pass the clone syscall&squot;s&n;&t;   second argument -- it&squot;s ignored for calls from kernel mode (the&n;&t;   child&squot;s SP is always set to the top of the kernel stack).  */
id|arg0
op_assign
id|flags
op_or
id|CLONE_VM
suffix:semicolon
id|syscall
op_assign
id|__NR_clone
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;trap &quot;
id|SYSCALL_SHORT_TRAP
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=r&quot;
(paren
id|syscall
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|syscall
)paren
comma
l_string|&quot;r&quot;
(paren
id|arg0
)paren
suffix:colon
id|SYSCALL_SHORT_CLOBBERS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
multiline_comment|/* In child thread, call FN and exit.  */
id|arg0
op_assign
(paren
op_star
id|fn
)paren
(paren
id|arg
)paren
suffix:semicolon
id|syscall
op_assign
id|__NR_exit
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;trap &quot;
id|SYSCALL_SHORT_TRAP
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=r&quot;
(paren
id|syscall
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|syscall
)paren
comma
l_string|&quot;r&quot;
(paren
id|arg0
)paren
suffix:colon
id|SYSCALL_SHORT_CLOBBERS
)paren
suffix:semicolon
)brace
multiline_comment|/* In parent.  */
id|set_fs
(paren
id|fs
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|flush_thread
r_void
id|flush_thread
(paren
r_void
)paren
(brace
id|set_fs
(paren
id|USER_DS
)paren
suffix:semicolon
)brace
DECL|function|copy_thread
r_int
id|copy_thread
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
id|stack_start
comma
r_int
r_int
id|stack_size
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
multiline_comment|/* Start pushing stuff from the top of the child&squot;s kernel stack.  */
r_int
r_int
id|orig_ksp
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
op_plus
id|THREAD_SIZE
suffix:semicolon
r_int
r_int
id|ksp
op_assign
id|orig_ksp
suffix:semicolon
multiline_comment|/* We push two `state save&squot; stack fames (see entry.S) on the new&n;&t;   kernel stack:&n;&t;     1) The innermost one is what switch_thread would have&n;&t;        pushed, and is used when we context switch to the child&n;&t;&t;thread for the first time.  It&squot;s set up to return to&n;&t;&t;ret_from_fork in entry.S.&n;&t;     2) The outermost one (nearest the top) is what a syscall&n;&t;        trap would have pushed, and is set up to return to the&n;&t;&t;same location as the parent thread, but with a return&n;&t;&t;value of 0. */
r_struct
id|pt_regs
op_star
id|child_switch_regs
comma
op_star
id|child_trap_regs
suffix:semicolon
multiline_comment|/* Trap frame.  */
id|ksp
op_sub_assign
id|STATE_SAVE_SIZE
suffix:semicolon
id|child_trap_regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|ksp
op_plus
id|STATE_SAVE_PT_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Switch frame.  */
id|ksp
op_sub_assign
id|STATE_SAVE_SIZE
suffix:semicolon
id|child_switch_regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|ksp
op_plus
id|STATE_SAVE_PT_OFFSET
)paren
suffix:semicolon
multiline_comment|/* First copy parent&squot;s register state to child.  */
op_star
id|child_switch_regs
op_assign
op_star
id|regs
suffix:semicolon
op_star
id|child_trap_regs
op_assign
op_star
id|regs
suffix:semicolon
multiline_comment|/* switch_thread returns to the restored value of the lp&n;&t;   register (r31), so we make that the place where we want to&n;&t;   jump when the child thread begins running.  */
id|child_switch_regs-&gt;gpr
(braket
id|GPR_LP
)braket
op_assign
(paren
id|v850_reg_t
)paren
id|ret_from_fork
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;kernel_mode
)paren
multiline_comment|/* Since we&squot;re returning to kernel-mode, make sure the child&squot;s&n;&t;&t;   stored kernel stack pointer agrees with what the actual&n;&t;&t;   stack pointer will be at that point (the trap return code&n;&t;&t;   always restores the SP, even when returning to&n;&t;&t;   kernel-mode).  */
id|child_trap_regs-&gt;gpr
(braket
id|GPR_SP
)braket
op_assign
id|orig_ksp
suffix:semicolon
r_else
multiline_comment|/* Set the child&squot;s user-mode stack-pointer (the name&n;&t;&t;   `stack_start&squot; is a misnomer, it&squot;s just the initial SP&n;&t;&t;   value).  */
id|child_trap_regs-&gt;gpr
(braket
id|GPR_SP
)braket
op_assign
id|stack_start
suffix:semicolon
multiline_comment|/* Thread state for the child (everything else is on the stack).  */
id|p-&gt;thread.ksp
op_assign
id|ksp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fill in the user structure for a core dump..&n; */
DECL|function|dump_thread
r_void
id|dump_thread
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
macro_line|#if 0  /* Later.  XXX */
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
id|regs-&gt;gpr
(braket
id|GPR_SP
)braket
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
id|dump-&gt;u_ar0
op_assign
(paren
r_struct
id|user_regs_struct
op_star
)paren
(paren
(paren
r_int
)paren
op_amp
id|dump-&gt;regs
op_minus
(paren
r_int
)paren
id|dump
)paren
suffix:semicolon
id|dump-&gt;regs
op_assign
op_star
id|regs
suffix:semicolon
id|dump-&gt;u_fpvalid
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
DECL|function|sys_execve
r_int
id|sys_execve
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
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_char
op_star
id|filename
op_assign
id|getname
(paren
id|name
)paren
suffix:semicolon
r_int
id|error
op_assign
id|PTR_ERR
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
(paren
id|filename
)paren
)paren
(brace
id|error
op_assign
id|do_execve
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
(paren
id|filename
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * These bracket the sleeping functions..&n; */
DECL|macro|first_sched
mdefine_line|#define first_sched&t;((unsigned long)__sched_text_start)
DECL|macro|last_sched
mdefine_line|#define last_sched&t;((unsigned long)__sched_text_end)
DECL|function|get_wchan
r_int
r_int
id|get_wchan
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
macro_line|#if 0  /* Barf.  Figure out the stack-layout later.  XXX  */
r_int
r_int
id|fp
comma
id|pc
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
id|pc
op_assign
id|thread_saved_pc
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* This quite disgusting function walks up the stack, following&n;&t;   saved return address, until it something that&squot;s out of bounds&n;&t;   (as defined by `first_sched&squot; and `last_sched&squot;).  It then&n;&t;   returns the last PC that was in-bounds.  */
r_do
(brace
r_if
c_cond
(paren
id|fp
OL
id|stack_page
op_plus
r_sizeof
(paren
r_struct
id|task_struct
)paren
op_logical_or
id|fp
op_ge
l_int|8184
op_plus
id|stack_page
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
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pc
OL
id|first_sched
op_logical_or
id|pc
op_ge
id|last_sched
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
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
