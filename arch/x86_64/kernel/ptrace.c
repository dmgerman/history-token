multiline_comment|/* ptrace.c */
multiline_comment|/* By Ross Biro 1/23/92 */
multiline_comment|/*&n; * Pentium III FXSR, SSE support&n; *&t;Gareth Hughes &lt;gareth@valinux.com&gt;, May 2000&n; * &n; * x86-64 port 2000-2002 Andi Kleen&n; */
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
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/debugreg.h&gt;
macro_line|#include &lt;asm/ldt.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
multiline_comment|/* determines which flags the user has access to. */
multiline_comment|/* 1 = access 0 = no access */
DECL|macro|FLAG_MASK
mdefine_line|#define FLAG_MASK 0x44dd5UL
multiline_comment|/* set&squot;s the trap flag. */
DECL|macro|TRAP_FLAG
mdefine_line|#define TRAP_FLAG 0x100UL
multiline_comment|/*&n; * eflags and offset of eflags on child stack..&n; */
DECL|macro|EFLAGS
mdefine_line|#define EFLAGS offsetof(struct pt_regs, eflags)
DECL|macro|EFL_OFFSET
mdefine_line|#define EFL_OFFSET ((int)(EFLAGS-sizeof(struct pt_regs)))
multiline_comment|/*&n; * this routine will get a word off of the processes privileged stack. &n; * the offset is how far from the base addr as stored in the TSS.  &n; * this routine assumes that all the privileged stacks are in our&n; * data space.&n; */
DECL|function|get_stack_long
r_static
r_inline
r_int
r_int
id|get_stack_long
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|offset
)paren
(brace
r_int
r_char
op_star
id|stack
suffix:semicolon
id|stack
op_assign
(paren
r_int
r_char
op_star
)paren
id|task-&gt;thread.rsp0
suffix:semicolon
id|stack
op_add_assign
id|offset
suffix:semicolon
r_return
(paren
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|stack
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * this routine will put a word on the processes privileged stack. &n; * the offset is how far from the base addr as stored in the TSS.  &n; * this routine assumes that all the privileged stacks are in our&n; * data space.&n; */
DECL|function|put_stack_long
r_static
r_inline
r_int
id|put_stack_long
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|offset
comma
r_int
r_int
id|data
)paren
(brace
r_int
r_char
op_star
id|stack
suffix:semicolon
id|stack
op_assign
(paren
r_int
r_char
op_star
)paren
id|task-&gt;thread.rsp0
suffix:semicolon
id|stack
op_add_assign
id|offset
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|stack
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
id|tmp
suffix:semicolon
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
)paren
op_amp
op_complement
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
comma
id|tmp
)paren
suffix:semicolon
)brace
DECL|function|putreg
r_static
r_int
id|putreg
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
r_int
id|regno
comma
r_int
r_int
id|value
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
multiline_comment|/* Some code in the 64bit emulation may not be 64bit clean.&n;&t;   Don&squot;t take any chances. */
r_if
c_cond
(paren
id|test_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_IA32
)paren
)paren
id|value
op_and_assign
l_int|0xffffffff
suffix:semicolon
r_switch
c_cond
(paren
id|regno
)paren
(brace
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|fs
)paren
suffix:colon
r_if
c_cond
(paren
id|value
op_logical_and
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|child-&gt;thread.fsindex
op_assign
id|value
op_amp
l_int|0xffff
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|gs
)paren
suffix:colon
r_if
c_cond
(paren
id|value
op_logical_and
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|child-&gt;thread.gsindex
op_assign
id|value
op_amp
l_int|0xffff
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|ds
)paren
suffix:colon
r_if
c_cond
(paren
id|value
op_logical_and
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|child-&gt;thread.ds
op_assign
id|value
op_amp
l_int|0xffff
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|es
)paren
suffix:colon
r_if
c_cond
(paren
id|value
op_logical_and
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|child-&gt;thread.es
op_assign
id|value
op_amp
l_int|0xffff
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|ss
)paren
suffix:colon
r_if
c_cond
(paren
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|value
op_and_assign
l_int|0xffff
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|fs_base
)paren
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|value
op_rshift
l_int|48
)paren
op_eq
l_int|0
op_logical_or
(paren
id|value
op_rshift
l_int|48
)paren
op_eq
l_int|0xffff
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|child-&gt;thread.fs
op_assign
id|value
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|gs_base
)paren
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|value
op_rshift
l_int|48
)paren
op_eq
l_int|0
op_logical_or
(paren
id|value
op_rshift
l_int|48
)paren
op_eq
l_int|0xffff
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|child-&gt;thread.gs
op_assign
id|value
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|eflags
)paren
suffix:colon
id|value
op_and_assign
id|FLAG_MASK
suffix:semicolon
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
id|FLAG_MASK
suffix:semicolon
id|value
op_or_assign
id|tmp
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|cs
)paren
suffix:colon
r_if
c_cond
(paren
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|value
op_and_assign
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
)brace
id|put_stack_long
c_func
(paren
id|child
comma
id|regno
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|getreg
r_static
r_int
r_int
id|getreg
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
r_int
id|regno
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
r_switch
c_cond
(paren
id|regno
)paren
(brace
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|fs
)paren
suffix:colon
r_return
id|child-&gt;thread.fsindex
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|gs
)paren
suffix:colon
r_return
id|child-&gt;thread.gsindex
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|ds
)paren
suffix:colon
r_return
id|child-&gt;thread.ds
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|es
)paren
suffix:colon
r_return
id|child-&gt;thread.es
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|fs_base
)paren
suffix:colon
r_return
id|child-&gt;thread.fs
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user_regs_struct
comma
id|gs_base
)paren
suffix:colon
r_return
id|child-&gt;thread.gs
suffix:semicolon
r_default
suffix:colon
id|regno
op_assign
id|regno
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
id|val
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|regno
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_IA32
)paren
)paren
id|val
op_and_assign
l_int|0xffffffff
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
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
r_int
id|ui
suffix:semicolon
multiline_comment|/* This lock_kernel fixes a subtle race with suid exec */
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
l_int|7
)paren
op_logical_or
id|addr
OG
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
l_int|7
)paren
r_break
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
r_sizeof
(paren
r_struct
id|user_regs_struct
)paren
suffix:colon
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
r_break
suffix:semicolon
r_case
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
suffix:colon
id|tmp
op_assign
id|child-&gt;thread.debugreg0
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|1
)braket
)paren
suffix:colon
id|tmp
op_assign
id|child-&gt;thread.debugreg1
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|2
)braket
)paren
suffix:colon
id|tmp
op_assign
id|child-&gt;thread.debugreg2
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|3
)braket
)paren
suffix:colon
id|tmp
op_assign
id|child-&gt;thread.debugreg3
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|6
)braket
)paren
suffix:colon
id|tmp
op_assign
id|child-&gt;thread.debugreg6
suffix:semicolon
r_break
suffix:semicolon
r_case
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
suffix:colon
id|tmp
op_assign
id|child-&gt;thread.debugreg7
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|tmp
op_assign
l_int|0
suffix:semicolon
r_break
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
l_int|7
)paren
op_logical_or
id|addr
OG
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
l_int|7
)paren
r_break
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
r_sizeof
(paren
r_struct
id|user_regs_struct
)paren
suffix:colon
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
multiline_comment|/* Disallows to set a breakpoint into the vsyscall */
r_case
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
suffix:colon
r_if
c_cond
(paren
id|data
op_ge
id|TASK_SIZE
op_minus
l_int|7
)paren
r_break
suffix:semicolon
id|child-&gt;thread.debugreg0
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|1
)braket
)paren
suffix:colon
r_if
c_cond
(paren
id|data
op_ge
id|TASK_SIZE
op_minus
l_int|7
)paren
r_break
suffix:semicolon
id|child-&gt;thread.debugreg1
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|2
)braket
)paren
suffix:colon
r_if
c_cond
(paren
id|data
op_ge
id|TASK_SIZE
op_minus
l_int|7
)paren
r_break
suffix:semicolon
id|child-&gt;thread.debugreg2
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|3
)braket
)paren
suffix:colon
r_if
c_cond
(paren
id|data
op_ge
id|TASK_SIZE
op_minus
l_int|7
)paren
r_break
suffix:semicolon
id|child-&gt;thread.debugreg3
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|6
)braket
)paren
suffix:colon
r_if
c_cond
(paren
id|data
op_rshift
l_int|32
)paren
r_break
suffix:semicolon
id|child-&gt;thread.debugreg6
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
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
suffix:colon
id|data
op_and_assign
op_complement
id|DR_CONTROL_RESERVED
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
l_int|0x5454
op_rshift
(paren
(paren
id|data
op_rshift
(paren
l_int|16
op_plus
l_int|4
op_star
id|i
)paren
)paren
op_amp
l_int|0xf
)paren
)paren
op_amp
l_int|1
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|4
)paren
(brace
id|child-&gt;thread.debugreg7
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
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
comma
id|tmp
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
macro_line|#ifdef CONFIG_IA32_EMULATION
multiline_comment|/* This makes only sense with 32bit programs. Allow a&n;&t;&t;   64bit debugger to fully examine them too. Better&n;&t;&t;   don&squot;t use it against 64bit processes, use&n;&t;&t;   PTRACE_ARCH_PRCTL instead. */
r_case
id|PTRACE_SET_THREAD_AREA
suffix:colon
(brace
r_int
id|old
suffix:semicolon
id|get_user
c_func
(paren
id|old
comma
op_amp
(paren
(paren
r_struct
id|user_desc
op_star
)paren
id|data
)paren
op_member_access_from_pointer
id|entry_number
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|addr
comma
op_amp
(paren
(paren
r_struct
id|user_desc
op_star
)paren
id|data
)paren
op_member_access_from_pointer
id|entry_number
)paren
suffix:semicolon
id|ret
op_assign
id|do_set_thread_area
c_func
(paren
op_amp
id|child-&gt;thread
comma
(paren
r_struct
id|user_desc
op_star
)paren
id|data
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|old
comma
op_amp
(paren
(paren
r_struct
id|user_desc
op_star
)paren
id|data
)paren
op_member_access_from_pointer
id|entry_number
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_GET_THREAD_AREA
suffix:colon
id|get_user
c_func
(paren
id|old
comma
op_amp
(paren
(paren
r_struct
id|user_desc
op_star
)paren
id|data
)paren
op_member_access_from_pointer
id|entry_number
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|addr
comma
op_amp
(paren
(paren
r_struct
id|user_desc
op_star
)paren
id|data
)paren
op_member_access_from_pointer
id|entry_number
)paren
suffix:semicolon
id|ret
op_assign
id|do_get_thread_area
c_func
(paren
op_amp
id|child-&gt;thread
comma
(paren
r_struct
id|user_desc
op_star
)paren
id|data
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|old
comma
op_amp
(paren
(paren
r_struct
id|user_desc
op_star
)paren
id|data
)paren
op_member_access_from_pointer
id|entry_number
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* normal 64bit interface to access TLS data. &n;&t;&t;   Works just like arch_prctl, except that the arguments&n;&t;&t;   are reversed. */
r_case
id|PTRACE_ARCH_PRCTL
suffix:colon
id|ret
op_assign
id|do_arch_prctl
c_func
(paren
id|child
comma
id|data
comma
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
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
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
)paren
op_amp
op_complement
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
comma
id|tmp
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
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|child-&gt;ptrace
op_amp
id|PT_DTRACE
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Spurious delayed TF traps may occur */
id|child-&gt;ptrace
op_or_assign
id|PT_DTRACE
suffix:semicolon
)brace
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
)paren
op_or
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
comma
id|tmp
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
op_star
)paren
id|data
comma
id|FRAME_SIZE
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
id|ui
op_assign
l_int|0
suffix:semicolon
id|ui
OL
r_sizeof
(paren
r_struct
id|user_regs_struct
)paren
suffix:semicolon
id|ui
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
id|ui
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
r_case
id|PTRACE_SETREGS
suffix:colon
(brace
multiline_comment|/* Set all gp regs in the child. */
r_int
r_int
id|tmp
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
id|FRAME_SIZE
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
id|ui
op_assign
l_int|0
suffix:semicolon
id|ui
OL
r_sizeof
(paren
r_struct
id|user_regs_struct
)paren
suffix:semicolon
id|ui
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
id|ui
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
multiline_comment|/* Get the child extended FPU state. */
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
op_star
)paren
id|data
comma
r_sizeof
(paren
r_struct
id|user_i387_struct
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
id|ret
op_assign
id|get_fpregs
c_func
(paren
(paren
r_struct
id|user_i387_struct
op_star
)paren
id|data
comma
id|child
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_SETFPREGS
suffix:colon
(brace
multiline_comment|/* Set the child extended FPU state. */
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
r_sizeof
(paren
r_struct
id|user_i387_struct
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
id|child-&gt;used_math
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|set_fpregs
c_func
(paren
id|child
comma
(paren
r_struct
id|user_i387_struct
op_star
)paren
id|data
)paren
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
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;trace %s rip %lx rsp %lx rax %d origrax %d caller %lx tiflags %x ptrace %x&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|regs-&gt;rip
comma
id|regs-&gt;rsp
comma
id|regs-&gt;rax
comma
id|regs-&gt;orig_rax
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
comma
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
comma
id|current-&gt;ptrace
)paren
suffix:semicolon
macro_line|#endif
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
