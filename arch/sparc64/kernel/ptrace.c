multiline_comment|/* ptrace.c: Sparc process tracing support.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caipfs.rutgers.edu)&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; * Based upon code written by Ross Biro, Linus Torvalds, Bob Manson,&n; * and David Mosberger.&n; *&n; * Added Linux support -miguel (weird, eh?, the orignal code was meant&n; * to emulate SunOS).&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/psrcompat.h&gt;
macro_line|#include &lt;asm/visasm.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
multiline_comment|/* Returning from ptrace is a bit tricky because the syscall return&n; * low level code assumes any value returned which is negative and&n; * is a valid errno will mean setting the condition codes to indicate&n; * an error return.  This doesn&squot;t work, so we have this hook.&n; */
DECL|function|pt_error_return
r_static
r_inline
r_void
id|pt_error_return
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|error
)paren
(brace
id|regs-&gt;u_regs
(braket
id|UREG_I0
)braket
op_assign
id|error
suffix:semicolon
id|regs-&gt;tstate
op_or_assign
(paren
id|TSTATE_ICARRY
op_or
id|TSTATE_XCARRY
)paren
suffix:semicolon
id|regs-&gt;tpc
op_assign
id|regs-&gt;tnpc
suffix:semicolon
id|regs-&gt;tnpc
op_add_assign
l_int|4
suffix:semicolon
)brace
DECL|function|pt_succ_return
r_static
r_inline
r_void
id|pt_succ_return
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|value
)paren
(brace
id|regs-&gt;u_regs
(braket
id|UREG_I0
)braket
op_assign
id|value
suffix:semicolon
id|regs-&gt;tstate
op_and_assign
op_complement
(paren
id|TSTATE_ICARRY
op_or
id|TSTATE_XCARRY
)paren
suffix:semicolon
id|regs-&gt;tpc
op_assign
id|regs-&gt;tnpc
suffix:semicolon
id|regs-&gt;tnpc
op_add_assign
l_int|4
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pt_succ_return_linux
id|pt_succ_return_linux
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|value
comma
r_int
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|value
comma
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
)paren
r_return
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|value
comma
id|addr
)paren
)paren
r_return
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
)brace
id|regs-&gt;u_regs
(braket
id|UREG_I0
)braket
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;tstate
op_and_assign
op_complement
(paren
id|TSTATE_ICARRY
op_or
id|TSTATE_XCARRY
)paren
suffix:semicolon
id|regs-&gt;tpc
op_assign
id|regs-&gt;tnpc
suffix:semicolon
id|regs-&gt;tnpc
op_add_assign
l_int|4
suffix:semicolon
)brace
r_static
r_void
DECL|function|pt_os_succ_return
id|pt_os_succ_return
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|val
comma
r_int
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;personality
op_eq
id|PER_SUNOS
)paren
id|pt_succ_return
(paren
id|regs
comma
id|val
)paren
suffix:semicolon
r_else
id|pt_succ_return_linux
(paren
id|regs
comma
id|val
comma
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* #define ALLOW_INIT_TRACING */
multiline_comment|/* #define DEBUG_PTRACE */
macro_line|#ifdef DEBUG_PTRACE
DECL|variable|pt_rq
r_char
op_star
id|pt_rq
(braket
)braket
op_assign
(brace
multiline_comment|/* 0  */
l_string|&quot;TRACEME&quot;
comma
l_string|&quot;PEEKTEXT&quot;
comma
l_string|&quot;PEEKDATA&quot;
comma
l_string|&quot;PEEKUSR&quot;
comma
multiline_comment|/* 4  */
l_string|&quot;POKETEXT&quot;
comma
l_string|&quot;POKEDATA&quot;
comma
l_string|&quot;POKEUSR&quot;
comma
l_string|&quot;CONT&quot;
comma
multiline_comment|/* 8  */
l_string|&quot;KILL&quot;
comma
l_string|&quot;SINGLESTEP&quot;
comma
l_string|&quot;SUNATTACH&quot;
comma
l_string|&quot;SUNDETACH&quot;
comma
multiline_comment|/* 12 */
l_string|&quot;GETREGS&quot;
comma
l_string|&quot;SETREGS&quot;
comma
l_string|&quot;GETFPREGS&quot;
comma
l_string|&quot;SETFPREGS&quot;
comma
multiline_comment|/* 16 */
l_string|&quot;READDATA&quot;
comma
l_string|&quot;WRITEDATA&quot;
comma
l_string|&quot;READTEXT&quot;
comma
l_string|&quot;WRITETEXT&quot;
comma
multiline_comment|/* 20 */
l_string|&quot;GETFPAREGS&quot;
comma
l_string|&quot;SETFPAREGS&quot;
comma
l_string|&quot;unknown&quot;
comma
l_string|&quot;unknown&quot;
comma
multiline_comment|/* 24 */
l_string|&quot;SYSCALL&quot;
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* nothing to do */
)brace
DECL|function|do_ptrace
id|asmlinkage
r_void
id|do_ptrace
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|request
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_I0
)braket
suffix:semicolon
id|pid_t
id|pid
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_I1
)braket
suffix:semicolon
r_int
r_int
id|addr
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_I2
)braket
suffix:semicolon
r_int
r_int
id|data
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_I3
)braket
suffix:semicolon
r_int
r_int
id|addr2
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_I4
)braket
suffix:semicolon
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
(brace
id|addr
op_and_assign
l_int|0xffffffffUL
suffix:semicolon
id|data
op_and_assign
l_int|0xffffffffUL
suffix:semicolon
id|addr2
op_and_assign
l_int|0xffffffffUL
suffix:semicolon
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_PTRACE
(brace
r_char
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
(paren
id|request
op_ge
l_int|0
)paren
op_logical_and
(paren
id|request
op_le
l_int|24
)paren
)paren
id|s
op_assign
id|pt_rq
(braket
id|request
)braket
suffix:semicolon
r_else
id|s
op_assign
l_string|&quot;unknown&quot;
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_POKEDATA
op_logical_and
id|data
op_eq
l_int|0x91d02001
)paren
(brace
id|printk
(paren
l_string|&quot;do_ptrace: breakpoint pid=%d, addr=%016lx addr2=%016lx&bslash;n&quot;
comma
id|pid
comma
id|addr
comma
id|addr2
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;do_ptrace: rq=%s(%d) pid=%d addr=%016lx data=%016lx addr2=%016lx&bslash;n&quot;
comma
id|s
comma
id|request
comma
id|pid
comma
id|addr
comma
id|data
comma
id|addr2
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_TRACEME
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* are we already being traced? */
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EPERM
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|security_ops
op_member_access_from_pointer
id|ptrace
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
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
op_minus
id|ret
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* set the ptrace bit in the process flags. */
id|current-&gt;ptrace
op_or_assign
id|PT_PTRACED
suffix:semicolon
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#ifndef ALLOW_INIT_TRACING
r_if
c_cond
(paren
id|pid
op_eq
l_int|1
)paren
(brace
multiline_comment|/* Can&squot;t dork with init. */
id|pt_error_return
c_func
(paren
id|regs
comma
id|EPERM
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#endif
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
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|ESRCH
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|current-&gt;personality
op_eq
id|PER_SUNOS
op_logical_and
id|request
op_eq
id|PTRACE_SUNATTACH
)paren
op_logical_or
(paren
id|current-&gt;personality
op_ne
id|PER_SUNOS
op_logical_and
id|request
op_eq
id|PTRACE_ATTACH
)paren
)paren
(brace
r_if
c_cond
(paren
id|ptrace_attach
c_func
(paren
id|child
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EPERM
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
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
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
op_minus
id|ret
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
op_logical_and
(paren
(paren
id|request
op_eq
id|PTRACE_READDATA64
)paren
op_logical_or
(paren
id|request
op_eq
id|PTRACE_WRITEDATA64
)paren
op_logical_or
(paren
id|request
op_eq
id|PTRACE_READTEXT64
)paren
op_logical_or
(paren
id|request
op_eq
id|PTRACE_WRITETEXT64
)paren
op_logical_or
(paren
id|request
op_eq
id|PTRACE_PEEKTEXT64
)paren
op_logical_or
(paren
id|request
op_eq
id|PTRACE_POKETEXT64
)paren
op_logical_or
(paren
id|request
op_eq
id|PTRACE_PEEKDATA64
)paren
op_logical_or
(paren
id|request
op_eq
id|PTRACE_POKEDATA64
)paren
)paren
)paren
(brace
id|addr
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_G2
)braket
suffix:semicolon
id|addr2
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_G3
)braket
suffix:semicolon
id|request
op_sub_assign
l_int|30
suffix:semicolon
multiline_comment|/* wheee... */
)brace
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
id|tmp64
suffix:semicolon
r_int
r_int
id|tmp32
suffix:semicolon
r_int
id|res
comma
id|copied
suffix:semicolon
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
(brace
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
id|tmp32
comma
r_sizeof
(paren
id|tmp32
)paren
comma
l_int|0
)paren
suffix:semicolon
id|tmp64
op_assign
(paren
r_int
r_int
)paren
id|tmp32
suffix:semicolon
r_if
c_cond
(paren
id|copied
op_eq
r_sizeof
(paren
id|tmp32
)paren
)paren
id|res
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
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
id|tmp64
comma
r_sizeof
(paren
id|tmp64
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copied
op_eq
r_sizeof
(paren
id|tmp64
)paren
)paren
id|res
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
id|pt_error_return
c_func
(paren
id|regs
comma
op_minus
id|res
)paren
suffix:semicolon
r_else
id|pt_os_succ_return
c_func
(paren
id|regs
comma
id|tmp64
comma
(paren
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
r_goto
id|flush_and_out
suffix:semicolon
)brace
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
id|tmp64
suffix:semicolon
r_int
r_int
id|tmp32
suffix:semicolon
r_int
id|copied
comma
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
(brace
id|tmp32
op_assign
id|data
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
id|tmp32
comma
r_sizeof
(paren
id|tmp32
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copied
op_eq
r_sizeof
(paren
id|tmp32
)paren
)paren
id|res
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|tmp64
op_assign
id|data
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
id|tmp64
comma
r_sizeof
(paren
id|tmp64
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copied
op_eq
r_sizeof
(paren
id|tmp64
)paren
)paren
id|res
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
id|pt_error_return
c_func
(paren
id|regs
comma
op_minus
id|res
)paren
suffix:semicolon
r_else
id|pt_succ_return
c_func
(paren
id|regs
comma
id|res
)paren
suffix:semicolon
r_goto
id|flush_and_out
suffix:semicolon
)brace
r_case
id|PTRACE_GETREGS
suffix:colon
(brace
r_struct
id|pt_regs32
op_star
id|pregs
op_assign
(paren
r_struct
id|pt_regs32
op_star
)paren
id|addr
suffix:semicolon
r_struct
id|pt_regs
op_star
id|cregs
op_assign
id|child-&gt;thread_info-&gt;kregs
suffix:semicolon
r_int
id|rval
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|tstate_to_psr
c_func
(paren
id|cregs-&gt;tstate
)paren
comma
(paren
op_amp
id|pregs-&gt;psr
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|cregs-&gt;tpc
comma
(paren
op_amp
id|pregs-&gt;pc
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|cregs-&gt;tnpc
comma
(paren
op_amp
id|pregs-&gt;npc
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|cregs-&gt;y
comma
(paren
op_amp
id|pregs-&gt;y
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_for
c_loop
(paren
id|rval
op_assign
l_int|1
suffix:semicolon
id|rval
OL
l_int|16
suffix:semicolon
id|rval
op_increment
)paren
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|cregs-&gt;u_regs
(braket
id|rval
)braket
comma
(paren
op_amp
id|pregs-&gt;u_regs
(braket
id|rval
op_minus
l_int|1
)braket
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_PTRACE
id|printk
(paren
l_string|&quot;PC=%lx nPC=%lx o7=%lx&bslash;n&quot;
comma
id|cregs-&gt;tpc
comma
id|cregs-&gt;tnpc
comma
id|cregs-&gt;u_regs
(braket
l_int|15
)braket
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|out_tsk
suffix:semicolon
)brace
r_case
id|PTRACE_GETREGS64
suffix:colon
(brace
r_struct
id|pt_regs
op_star
id|pregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|addr
suffix:semicolon
r_struct
id|pt_regs
op_star
id|cregs
op_assign
id|child-&gt;thread_info-&gt;kregs
suffix:semicolon
r_int
r_int
id|tpc
op_assign
id|cregs-&gt;tpc
suffix:semicolon
r_int
id|rval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|child-&gt;thread_info-&gt;flags
op_amp
id|_TIF_32BIT
)paren
op_ne
l_int|0
)paren
id|tpc
op_and_assign
l_int|0xffffffff
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|cregs-&gt;tstate
comma
(paren
op_amp
id|pregs-&gt;tstate
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|tpc
comma
(paren
op_amp
id|pregs-&gt;tpc
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|cregs-&gt;tnpc
comma
(paren
op_amp
id|pregs-&gt;tnpc
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|cregs-&gt;y
comma
(paren
op_amp
id|pregs-&gt;y
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_for
c_loop
(paren
id|rval
op_assign
l_int|1
suffix:semicolon
id|rval
OL
l_int|16
suffix:semicolon
id|rval
op_increment
)paren
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|cregs-&gt;u_regs
(braket
id|rval
)braket
comma
(paren
op_amp
id|pregs-&gt;u_regs
(braket
id|rval
op_minus
l_int|1
)braket
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_PTRACE
id|printk
(paren
l_string|&quot;PC=%lx nPC=%lx o7=%lx&bslash;n&quot;
comma
id|cregs-&gt;tpc
comma
id|cregs-&gt;tnpc
comma
id|cregs-&gt;u_regs
(braket
l_int|15
)braket
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|out_tsk
suffix:semicolon
)brace
r_case
id|PTRACE_SETREGS
suffix:colon
(brace
r_struct
id|pt_regs32
op_star
id|pregs
op_assign
(paren
r_struct
id|pt_regs32
op_star
)paren
id|addr
suffix:semicolon
r_struct
id|pt_regs
op_star
id|cregs
op_assign
id|child-&gt;thread_info-&gt;kregs
suffix:semicolon
r_int
r_int
id|psr
comma
id|pc
comma
id|npc
comma
id|y
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Must be careful, tracing process can only set certain&n;&t;&t; * bits in the psr.&n;&t;&t; */
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|psr
comma
(paren
op_amp
id|pregs-&gt;psr
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|pc
comma
(paren
op_amp
id|pregs-&gt;pc
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|npc
comma
(paren
op_amp
id|pregs-&gt;npc
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|y
comma
(paren
op_amp
id|pregs-&gt;y
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|cregs-&gt;tstate
op_and_assign
op_complement
(paren
id|TSTATE_ICC
)paren
suffix:semicolon
id|cregs-&gt;tstate
op_or_assign
id|psr_to_tstate_icc
c_func
(paren
id|psr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|pc
op_or
id|npc
)paren
op_amp
l_int|3
)paren
)paren
(brace
id|cregs-&gt;tpc
op_assign
id|pc
suffix:semicolon
id|cregs-&gt;tnpc
op_assign
id|npc
suffix:semicolon
)brace
id|cregs-&gt;y
op_assign
id|y
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|cregs-&gt;u_regs
(braket
id|i
)braket
comma
(paren
op_amp
id|pregs-&gt;u_regs
(braket
id|i
op_minus
l_int|1
)braket
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
)brace
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_case
id|PTRACE_SETREGS64
suffix:colon
(brace
r_struct
id|pt_regs
op_star
id|pregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|addr
suffix:semicolon
r_struct
id|pt_regs
op_star
id|cregs
op_assign
id|child-&gt;thread_info-&gt;kregs
suffix:semicolon
r_int
r_int
id|tstate
comma
id|tpc
comma
id|tnpc
comma
id|y
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Must be careful, tracing process can only set certain&n;&t;&t; * bits in the psr.&n;&t;&t; */
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|tstate
comma
(paren
op_amp
id|pregs-&gt;tstate
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|tpc
comma
(paren
op_amp
id|pregs-&gt;tpc
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|tnpc
comma
(paren
op_amp
id|pregs-&gt;tnpc
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|y
comma
(paren
op_amp
id|pregs-&gt;y
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|child-&gt;thread_info-&gt;flags
op_amp
id|_TIF_32BIT
)paren
op_ne
l_int|0
)paren
(brace
id|tpc
op_and_assign
l_int|0xffffffff
suffix:semicolon
id|tnpc
op_and_assign
l_int|0xffffffff
suffix:semicolon
)brace
id|tstate
op_and_assign
(paren
id|TSTATE_ICC
op_or
id|TSTATE_XCC
)paren
suffix:semicolon
id|cregs-&gt;tstate
op_and_assign
op_complement
(paren
id|TSTATE_ICC
op_or
id|TSTATE_XCC
)paren
suffix:semicolon
id|cregs-&gt;tstate
op_or_assign
id|tstate
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|tpc
op_or
id|tnpc
)paren
op_amp
l_int|3
)paren
)paren
(brace
id|cregs-&gt;tpc
op_assign
id|tpc
suffix:semicolon
id|cregs-&gt;tnpc
op_assign
id|tnpc
suffix:semicolon
)brace
id|cregs-&gt;y
op_assign
id|y
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|cregs-&gt;u_regs
(braket
id|i
)braket
comma
(paren
op_amp
id|pregs-&gt;u_regs
(braket
id|i
op_minus
l_int|1
)braket
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
)brace
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_case
id|PTRACE_GETFPREGS
suffix:colon
(brace
r_struct
id|fps
(brace
r_int
r_int
id|regs
(braket
l_int|32
)braket
suffix:semicolon
r_int
r_int
id|fsr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|extra
suffix:semicolon
r_int
r_int
id|fpqd
suffix:semicolon
r_struct
id|fq
(brace
r_int
r_int
id|insnaddr
suffix:semicolon
r_int
r_int
id|insn
suffix:semicolon
)brace
id|fpq
(braket
l_int|16
)braket
suffix:semicolon
)brace
op_star
id|fps
op_assign
(paren
r_struct
id|fps
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|fpregs
op_assign
id|child-&gt;thread_info-&gt;fpregs
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
id|fps-&gt;regs
(braket
l_int|0
)braket
comma
id|fpregs
comma
(paren
l_int|32
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|child-&gt;thread_info-&gt;xfsr
(braket
l_int|0
)braket
comma
(paren
op_amp
id|fps-&gt;fsr
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0
comma
(paren
op_amp
id|fps-&gt;fpqd
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0
comma
(paren
op_amp
id|fps-&gt;flags
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0
comma
(paren
op_amp
id|fps-&gt;extra
)paren
)paren
op_logical_or
id|clear_user
c_func
(paren
op_amp
id|fps-&gt;fpq
(braket
l_int|0
)braket
comma
l_int|32
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_case
id|PTRACE_GETFPREGS64
suffix:colon
(brace
r_struct
id|fps
(brace
r_int
r_int
id|regs
(braket
l_int|64
)braket
suffix:semicolon
r_int
r_int
id|fsr
suffix:semicolon
)brace
op_star
id|fps
op_assign
(paren
r_struct
id|fps
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|fpregs
op_assign
id|child-&gt;thread_info-&gt;fpregs
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
id|fps-&gt;regs
(braket
l_int|0
)braket
comma
id|fpregs
comma
(paren
l_int|64
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|child-&gt;thread_info-&gt;xfsr
(braket
l_int|0
)braket
comma
(paren
op_amp
id|fps-&gt;fsr
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_case
id|PTRACE_SETFPREGS
suffix:colon
(brace
r_struct
id|fps
(brace
r_int
r_int
id|regs
(braket
l_int|32
)braket
suffix:semicolon
r_int
r_int
id|fsr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|extra
suffix:semicolon
r_int
r_int
id|fpqd
suffix:semicolon
r_struct
id|fq
(brace
r_int
r_int
id|insnaddr
suffix:semicolon
r_int
r_int
id|insn
suffix:semicolon
)brace
id|fpq
(braket
l_int|16
)braket
suffix:semicolon
)brace
op_star
id|fps
op_assign
(paren
r_struct
id|fps
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|fpregs
op_assign
id|child-&gt;thread_info-&gt;fpregs
suffix:semicolon
r_int
id|fsr
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|fpregs
comma
op_amp
id|fps-&gt;regs
(braket
l_int|0
)braket
comma
(paren
l_int|32
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|fsr
comma
(paren
op_amp
id|fps-&gt;fsr
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|child-&gt;thread_info-&gt;xfsr
(braket
l_int|0
)braket
op_and_assign
l_int|0xffffffff00000000UL
suffix:semicolon
id|child-&gt;thread_info-&gt;xfsr
(braket
l_int|0
)braket
op_or_assign
id|fsr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|child-&gt;thread_info-&gt;fpsaved
(braket
l_int|0
)braket
op_amp
id|FPRS_FEF
)paren
)paren
id|child-&gt;thread_info-&gt;gsr
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|child-&gt;thread_info-&gt;fpsaved
(braket
l_int|0
)braket
op_or_assign
(paren
id|FPRS_FEF
op_or
id|FPRS_DL
)paren
suffix:semicolon
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_case
id|PTRACE_SETFPREGS64
suffix:colon
(brace
r_struct
id|fps
(brace
r_int
r_int
id|regs
(braket
l_int|64
)braket
suffix:semicolon
r_int
r_int
id|fsr
suffix:semicolon
)brace
op_star
id|fps
op_assign
(paren
r_struct
id|fps
op_star
)paren
id|addr
suffix:semicolon
r_int
r_int
op_star
id|fpregs
op_assign
id|child-&gt;thread_info-&gt;fpregs
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|fpregs
comma
op_amp
id|fps-&gt;regs
(braket
l_int|0
)braket
comma
(paren
l_int|64
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|child-&gt;thread_info-&gt;xfsr
(braket
l_int|0
)braket
comma
(paren
op_amp
id|fps-&gt;fsr
)paren
)paren
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EFAULT
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|child-&gt;thread_info-&gt;fpsaved
(braket
l_int|0
)braket
op_amp
id|FPRS_FEF
)paren
)paren
id|child-&gt;thread_info-&gt;gsr
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|child-&gt;thread_info-&gt;fpsaved
(braket
l_int|0
)braket
op_or_assign
(paren
id|FPRS_FEF
op_or
id|FPRS_DL
op_or
id|FPRS_DU
)paren
suffix:semicolon
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_case
id|PTRACE_READTEXT
suffix:colon
r_case
id|PTRACE_READDATA
suffix:colon
(brace
r_int
id|res
op_assign
id|ptrace_readdata
c_func
(paren
id|child
comma
id|addr
comma
(paren
r_void
op_star
)paren
id|addr2
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
id|data
)paren
(brace
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|flush_and_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res
op_ge
l_int|0
)paren
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
id|pt_error_return
c_func
(paren
id|regs
comma
op_minus
id|res
)paren
suffix:semicolon
r_goto
id|flush_and_out
suffix:semicolon
)brace
r_case
id|PTRACE_WRITETEXT
suffix:colon
r_case
id|PTRACE_WRITEDATA
suffix:colon
(brace
r_int
id|res
op_assign
id|ptrace_writedata
c_func
(paren
id|child
comma
(paren
r_void
op_star
)paren
id|addr2
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
id|data
)paren
(brace
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|flush_and_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res
op_ge
l_int|0
)paren
id|res
op_assign
op_minus
id|EIO
suffix:semicolon
id|pt_error_return
c_func
(paren
id|regs
comma
op_minus
id|res
)paren
suffix:semicolon
r_goto
id|flush_and_out
suffix:semicolon
)brace
r_case
id|PTRACE_SYSCALL
suffix:colon
multiline_comment|/* continue and stop at (return from) syscall */
id|addr
op_assign
l_int|1
suffix:semicolon
r_case
id|PTRACE_CONT
suffix:colon
(brace
multiline_comment|/* restart after signal. */
r_if
c_cond
(paren
id|data
OG
id|_NSIG
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EIO
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
op_ne
l_int|1
)paren
(brace
r_int
r_int
id|pc_mask
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|child-&gt;thread_info-&gt;flags
op_amp
id|_TIF_32BIT
)paren
op_ne
l_int|0
)paren
id|pc_mask
op_assign
l_int|0xffffffff
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_amp
l_int|3
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EINVAL
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_PTRACE
id|printk
(paren
l_string|&quot;Original: %016lx %016lx&bslash;n&quot;
comma
id|child-&gt;thread_info-&gt;kregs-&gt;tpc
comma
id|child-&gt;thread_info-&gt;kregs-&gt;tnpc
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;Continuing with %016lx %016lx&bslash;n&quot;
comma
id|addr
comma
id|addr
op_plus
l_int|4
)paren
suffix:semicolon
macro_line|#endif
id|child-&gt;thread_info-&gt;kregs-&gt;tpc
op_assign
(paren
id|addr
op_amp
id|pc_mask
)paren
suffix:semicolon
id|child-&gt;thread_info-&gt;kregs-&gt;tnpc
op_assign
(paren
(paren
id|addr
op_plus
l_int|4
)paren
op_amp
id|pc_mask
)paren
suffix:semicolon
)brace
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
macro_line|#ifdef DEBUG_PTRACE
id|printk
c_func
(paren
l_string|&quot;CONT: %s [%d]: set exit_code = %x %lx %lx&bslash;n&quot;
comma
id|child-&gt;comm
comma
id|child-&gt;pid
comma
id|child-&gt;exit_code
comma
id|child-&gt;thread_info-&gt;kregs-&gt;tpc
comma
id|child-&gt;thread_info-&gt;kregs-&gt;tnpc
)paren
suffix:semicolon
macro_line|#endif
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_tsk
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
(brace
multiline_comment|/* already dead */
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
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
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
r_case
id|PTRACE_SUNDETACH
suffix:colon
(brace
multiline_comment|/* detach a process that was attached. */
r_int
id|error
op_assign
id|ptrace_detach
c_func
(paren
id|child
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|pt_error_return
c_func
(paren
id|regs
comma
id|EIO
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|pt_succ_return
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
multiline_comment|/* PTRACE_DUMPCORE unsupported... */
r_default
suffix:colon
id|pt_error_return
c_func
(paren
id|regs
comma
id|EIO
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|flush_and_out
suffix:colon
(brace
r_int
r_int
id|va
suffix:semicolon
r_if
c_cond
(paren
id|tlb_type
op_eq
id|cheetah
op_logical_or
id|tlb_type
op_eq
id|cheetah_plus
)paren
(brace
r_for
c_loop
(paren
id|va
op_assign
l_int|0
suffix:semicolon
id|va
OL
(paren
l_int|1
op_lshift
l_int|16
)paren
suffix:semicolon
id|va
op_add_assign
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
id|spitfire_put_dcache_tag
c_func
(paren
id|va
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* No need to mess with I-cache on Cheetah. */
)brace
r_else
(brace
r_for
c_loop
(paren
id|va
op_assign
l_int|0
suffix:semicolon
id|va
OL
id|L1DCACHE_SIZE
suffix:semicolon
id|va
op_add_assign
l_int|32
)paren
id|spitfire_put_dcache_tag
c_func
(paren
id|va
comma
l_int|0x0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_PEEKTEXT
op_logical_or
id|request
op_eq
id|PTRACE_POKETEXT
op_logical_or
id|request
op_eq
id|PTRACE_READTEXT
op_logical_or
id|request
op_eq
id|PTRACE_WRITETEXT
)paren
(brace
r_for
c_loop
(paren
id|va
op_assign
l_int|0
suffix:semicolon
id|va
OL
(paren
id|PAGE_SIZE
op_lshift
l_int|1
)paren
suffix:semicolon
id|va
op_add_assign
l_int|32
)paren
id|spitfire_put_icache_tag
c_func
(paren
id|va
comma
l_int|0x0
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;flush %g6&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
id|out_tsk
suffix:colon
r_if
c_cond
(paren
id|child
)paren
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
macro_line|#ifdef DEBUG_PTRACE
id|printk
c_func
(paren
l_string|&quot;%s [%d]: syscall_trace&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
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
macro_line|#ifdef DEBUG_PTRACE
id|printk
c_func
(paren
l_string|&quot;%s [%d]: syscall_trace exit= %x&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|current-&gt;exit_code
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|current-&gt;exit_code
)paren
(brace
id|send_sig
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
