multiline_comment|/* &n; * 32bit ptrace for x86-64.&n; *&n; * Copyright 2001,2002 Andi Kleen, SuSE Labs.&n; * Some parts copied from arch/i386/kernel/ptrace.c. See that file for earlier &n; * copyright.&n; * &n; * This allows to access 64bit processes too; but there is no way to see the extended &n; * register contents.&n; *&n; * $Id: ptrace32.c,v 1.16 2003/03/14 16:06:35 ak Exp $&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/compat.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/user32.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/debugreg.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/fpu32.h&gt;
multiline_comment|/* determines which flags the user has access to. */
multiline_comment|/* 1 = access 0 = no access */
DECL|macro|FLAG_MASK
mdefine_line|#define FLAG_MASK 0x44dd5UL
DECL|macro|R32
mdefine_line|#define R32(l,q) &bslash;&n;&t;case offsetof(struct user32, regs.l): stack[offsetof(struct pt_regs, q)/8] = val; break
DECL|function|putreg32
r_static
r_int
id|putreg32
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
id|regno
comma
id|u32
id|val
)paren
(brace
r_int
id|i
suffix:semicolon
id|__u64
op_star
id|stack
op_assign
(paren
id|__u64
op_star
)paren
(paren
id|child-&gt;thread.rsp0
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
id|regno
)paren
(brace
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|regs.fs
)paren
suffix:colon
r_if
c_cond
(paren
id|val
op_logical_and
(paren
id|val
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
id|child-&gt;thread.fs
op_assign
id|val
op_amp
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|regs.gs
)paren
suffix:colon
r_if
c_cond
(paren
id|val
op_logical_and
(paren
id|val
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
id|child-&gt;thread.gs
op_assign
id|val
op_amp
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|regs.ds
)paren
suffix:colon
r_if
c_cond
(paren
id|val
op_logical_and
(paren
id|val
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
id|val
op_amp
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|regs.es
)paren
suffix:colon
id|child-&gt;thread.es
op_assign
id|val
op_amp
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|regs.ss
)paren
suffix:colon
r_if
c_cond
(paren
(paren
id|val
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
id|stack
(braket
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|ss
)paren
op_div
l_int|8
)braket
op_assign
id|val
op_amp
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|regs.cs
)paren
suffix:colon
r_if
c_cond
(paren
(paren
id|val
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
id|stack
(braket
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|cs
)paren
op_div
l_int|8
)braket
op_assign
id|val
op_amp
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
id|R32
c_func
(paren
id|ebx
comma
id|rbx
)paren
suffix:semicolon
id|R32
c_func
(paren
id|ecx
comma
id|rcx
)paren
suffix:semicolon
id|R32
c_func
(paren
id|edx
comma
id|rdx
)paren
suffix:semicolon
id|R32
c_func
(paren
id|edi
comma
id|rdi
)paren
suffix:semicolon
id|R32
c_func
(paren
id|esi
comma
id|rsi
)paren
suffix:semicolon
id|R32
c_func
(paren
id|ebp
comma
id|rbp
)paren
suffix:semicolon
id|R32
c_func
(paren
id|eax
comma
id|rax
)paren
suffix:semicolon
id|R32
c_func
(paren
id|orig_eax
comma
id|orig_rax
)paren
suffix:semicolon
id|R32
c_func
(paren
id|eip
comma
id|rip
)paren
suffix:semicolon
id|R32
c_func
(paren
id|esp
comma
id|rsp
)paren
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|regs.eflags
)paren
suffix:colon
(brace
id|__u64
op_star
id|flags
op_assign
op_amp
id|stack
(braket
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|eflags
)paren
op_div
l_int|8
)braket
suffix:semicolon
id|val
op_and_assign
id|FLAG_MASK
suffix:semicolon
op_star
id|flags
op_assign
id|val
op_or
(paren
op_star
id|flags
op_amp
op_complement
id|FLAG_MASK
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|4
)braket
)paren
suffix:colon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|5
)braket
)paren
suffix:colon
r_return
op_minus
id|EIO
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|0
)braket
)paren
suffix:colon
id|child-&gt;thread.debugreg0
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|1
)braket
)paren
suffix:colon
id|child-&gt;thread.debugreg1
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|2
)braket
)paren
suffix:colon
id|child-&gt;thread.debugreg2
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|3
)braket
)paren
suffix:colon
id|child-&gt;thread.debugreg3
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|6
)braket
)paren
suffix:colon
id|child-&gt;thread.debugreg6
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|7
)braket
)paren
suffix:colon
id|val
op_and_assign
op_complement
id|DR_CONTROL_RESERVED
suffix:semicolon
multiline_comment|/* See arch/i386/kernel/ptrace.c for an explanation of&n;&t;&t; * this awkward check.*/
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
id|val
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
r_return
op_minus
id|EIO
suffix:semicolon
id|child-&gt;thread.debugreg7
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|regno
OG
r_sizeof
(paren
r_struct
id|user32
)paren
op_logical_or
(paren
id|regno
op_amp
l_int|3
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* Other dummy fields in the virtual user structure are ignored */
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|R32
macro_line|#undef R32
DECL|macro|R32
mdefine_line|#define R32(l,q) &bslash;&n;&t;case offsetof(struct user32, regs.l): *val = stack[offsetof(struct pt_regs, q)/8]; break
DECL|function|getreg32
r_static
r_int
id|getreg32
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
id|regno
comma
id|u32
op_star
id|val
)paren
(brace
id|__u64
op_star
id|stack
op_assign
(paren
id|__u64
op_star
)paren
(paren
id|child-&gt;thread.rsp0
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
id|regno
)paren
(brace
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|regs.fs
)paren
suffix:colon
op_star
id|val
op_assign
id|child-&gt;thread.fs
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|regs.gs
)paren
suffix:colon
op_star
id|val
op_assign
id|child-&gt;thread.gs
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|regs.ds
)paren
suffix:colon
op_star
id|val
op_assign
id|child-&gt;thread.ds
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|regs.es
)paren
suffix:colon
op_star
id|val
op_assign
id|child-&gt;thread.es
suffix:semicolon
r_break
suffix:semicolon
id|R32
c_func
(paren
id|cs
comma
id|cs
)paren
suffix:semicolon
id|R32
c_func
(paren
id|ss
comma
id|ss
)paren
suffix:semicolon
id|R32
c_func
(paren
id|ebx
comma
id|rbx
)paren
suffix:semicolon
id|R32
c_func
(paren
id|ecx
comma
id|rcx
)paren
suffix:semicolon
id|R32
c_func
(paren
id|edx
comma
id|rdx
)paren
suffix:semicolon
id|R32
c_func
(paren
id|edi
comma
id|rdi
)paren
suffix:semicolon
id|R32
c_func
(paren
id|esi
comma
id|rsi
)paren
suffix:semicolon
id|R32
c_func
(paren
id|ebp
comma
id|rbp
)paren
suffix:semicolon
id|R32
c_func
(paren
id|eax
comma
id|rax
)paren
suffix:semicolon
id|R32
c_func
(paren
id|orig_eax
comma
id|orig_rax
)paren
suffix:semicolon
id|R32
c_func
(paren
id|eip
comma
id|rip
)paren
suffix:semicolon
id|R32
c_func
(paren
id|eflags
comma
id|eflags
)paren
suffix:semicolon
id|R32
c_func
(paren
id|esp
comma
id|rsp
)paren
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|0
)braket
)paren
suffix:colon
op_star
id|val
op_assign
id|child-&gt;thread.debugreg0
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|1
)braket
)paren
suffix:colon
op_star
id|val
op_assign
id|child-&gt;thread.debugreg1
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|2
)braket
)paren
suffix:colon
op_star
id|val
op_assign
id|child-&gt;thread.debugreg2
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|3
)braket
)paren
suffix:colon
op_star
id|val
op_assign
id|child-&gt;thread.debugreg3
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|6
)braket
)paren
suffix:colon
op_star
id|val
op_assign
id|child-&gt;thread.debugreg6
suffix:semicolon
r_break
suffix:semicolon
r_case
m_offsetof
(paren
r_struct
id|user32
comma
id|u_debugreg
(braket
l_int|7
)braket
)paren
suffix:colon
op_star
id|val
op_assign
id|child-&gt;thread.debugreg7
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|regno
OG
r_sizeof
(paren
r_struct
id|user32
)paren
op_logical_or
(paren
id|regno
op_amp
l_int|3
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* Other dummy fields in the virtual user structure are ignored */
op_star
id|val
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|R32
macro_line|#undef R32
DECL|function|find_target
r_static
r_struct
id|task_struct
op_star
id|find_target
c_func
(paren
r_int
id|request
comma
r_int
id|pid
comma
r_int
op_star
id|err
)paren
(brace
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
op_star
id|err
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
r_return
l_int|NULL
suffix:semicolon
op_star
id|err
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
id|child
)paren
(brace
op_star
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;pid
op_eq
l_int|1
)paren
r_goto
id|out
suffix:semicolon
op_star
id|err
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
op_star
id|err
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_return
id|child
suffix:semicolon
)brace
id|out
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
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|sys32_ptrace
id|asmlinkage
r_int
id|sys32_ptrace
c_func
(paren
r_int
id|request
comma
id|u32
id|pid
comma
id|u32
id|addr
comma
id|u32
id|data
)paren
(brace
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
r_void
id|__user
op_star
id|datap
op_assign
id|compat_ptr
c_func
(paren
id|data
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|__u32
id|val
suffix:semicolon
r_switch
c_cond
(paren
id|request
)paren
(brace
r_default
suffix:colon
r_return
id|sys_ptrace
c_func
(paren
id|request
comma
id|pid
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_case
id|PTRACE_PEEKTEXT
suffix:colon
r_case
id|PTRACE_PEEKDATA
suffix:colon
r_case
id|PTRACE_POKEDATA
suffix:colon
r_case
id|PTRACE_POKETEXT
suffix:colon
r_case
id|PTRACE_POKEUSR
suffix:colon
r_case
id|PTRACE_PEEKUSR
suffix:colon
r_case
id|PTRACE_GETREGS
suffix:colon
r_case
id|PTRACE_SETREGS
suffix:colon
r_case
id|PTRACE_SETFPREGS
suffix:colon
r_case
id|PTRACE_GETFPREGS
suffix:colon
r_case
id|PTRACE_SETFPXREGS
suffix:colon
r_case
id|PTRACE_GETFPXREGS
suffix:colon
r_case
id|PTRACE_GETEVENTMSG
suffix:colon
r_break
suffix:semicolon
)brace
id|child
op_assign
id|find_target
c_func
(paren
id|request
comma
id|pid
comma
op_amp
id|ret
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child
)paren
r_return
id|ret
suffix:semicolon
id|childregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|child-&gt;thread.rsp0
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
id|request
)paren
(brace
r_case
id|PTRACE_PEEKDATA
suffix:colon
r_case
id|PTRACE_PEEKTEXT
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
id|val
comma
r_sizeof
(paren
id|u32
)paren
comma
l_int|0
)paren
op_ne
r_sizeof
(paren
id|u32
)paren
)paren
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_else
id|ret
op_assign
id|put_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|datap
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_POKEDATA
suffix:colon
r_case
id|PTRACE_POKETEXT
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
id|u32
)paren
comma
l_int|1
)paren
op_ne
r_sizeof
(paren
id|u32
)paren
)paren
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_PEEKUSR
suffix:colon
id|ret
op_assign
id|getreg32
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|put_user
c_func
(paren
id|val
comma
(paren
id|__u32
id|__user
op_star
)paren
id|datap
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_POKEUSR
suffix:colon
id|ret
op_assign
id|putreg32
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
r_case
id|PTRACE_GETREGS
suffix:colon
(brace
multiline_comment|/* Get all gp regs from the child. */
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|datap
comma
l_int|16
op_star
l_int|4
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|16
op_star
l_int|4
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
id|__u32
)paren
)paren
(brace
id|getreg32
c_func
(paren
id|child
comma
id|i
comma
op_amp
id|val
)paren
suffix:semicolon
id|ret
op_or_assign
id|__put_user
c_func
(paren
id|val
comma
(paren
id|u32
id|__user
op_star
)paren
id|datap
)paren
suffix:semicolon
id|datap
op_add_assign
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
)brace
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
r_int
id|i
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
id|datap
comma
l_int|16
op_star
l_int|4
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|16
op_star
l_int|4
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
id|u32
)paren
)paren
(brace
id|ret
op_or_assign
id|__get_user
c_func
(paren
id|tmp
comma
(paren
id|u32
id|__user
op_star
)paren
id|datap
)paren
suffix:semicolon
id|putreg32
c_func
(paren
id|child
comma
id|i
comma
id|tmp
)paren
suffix:semicolon
id|datap
op_add_assign
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_GETFPREGS
suffix:colon
id|ret
op_assign
op_minus
id|EIO
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
id|compat_ptr
c_func
(paren
id|data
)paren
comma
r_sizeof
(paren
r_struct
id|user_i387_struct
)paren
)paren
)paren
r_break
suffix:semicolon
id|save_i387_ia32
c_func
(paren
id|child
comma
id|datap
comma
id|childregs
comma
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_SETFPREGS
suffix:colon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|datap
comma
r_sizeof
(paren
r_struct
id|user_i387_struct
)paren
)paren
)paren
r_break
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* don&squot;t check EFAULT to be bug-to-bug compatible to i386 */
id|restore_i387_ia32
c_func
(paren
id|child
comma
id|datap
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_GETFPXREGS
suffix:colon
(brace
r_struct
id|user32_fxsr_struct
id|__user
op_star
id|u
op_assign
id|datap
suffix:semicolon
id|init_fpu
c_func
(paren
id|child
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
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|u
comma
r_sizeof
(paren
op_star
id|u
)paren
)paren
)paren
r_break
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
id|u
comma
op_amp
id|child-&gt;thread.i387.fxsave
comma
r_sizeof
(paren
op_star
id|u
)paren
)paren
)paren
r_break
suffix:semicolon
id|ret
op_assign
id|__put_user
c_func
(paren
id|childregs-&gt;cs
comma
op_amp
id|u-&gt;fcs
)paren
suffix:semicolon
id|ret
op_or_assign
id|__put_user
c_func
(paren
id|child-&gt;thread.ds
comma
op_amp
id|u-&gt;fos
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_SETFPXREGS
suffix:colon
(brace
r_struct
id|user32_fxsr_struct
id|__user
op_star
id|u
op_assign
id|datap
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|child
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
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|u
comma
r_sizeof
(paren
op_star
id|u
)paren
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* no checking to be bug-to-bug compatible with i386 */
id|__copy_from_user
c_func
(paren
op_amp
id|child-&gt;thread.i387.fxsave
comma
id|u
comma
r_sizeof
(paren
op_star
id|u
)paren
)paren
suffix:semicolon
id|set_stopped_child_used_math
c_func
(paren
id|child
)paren
suffix:semicolon
id|child-&gt;thread.i387.fxsave.mxcsr
op_and_assign
id|mxcsr_feature_mask
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_GETEVENTMSG
suffix:colon
id|ret
op_assign
id|put_user
c_func
(paren
id|child-&gt;ptrace_message
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|compat_ptr
c_func
(paren
id|data
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|put_task_struct
c_func
(paren
id|child
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
