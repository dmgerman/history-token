multiline_comment|/*&n; *  linux/arch/x86_64/kernel/signal.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *  Copyright (C) 2000, 2001, 2002 Andi Kleen SuSE Labs&n; *&n; *  1997-11-28  Modified for POSIX.1b signals by Richard Henderson&n; *  2000-06-20  Pentium III FXSR, SSE support by Gareth Hughes&n; *  2000-2002   x86-64 support by Andi Kleen&n; * &n; *  $Id: signal.c,v 1.18 2001/10/17 22:30:37 ak Exp $&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
DECL|macro|DEBUG_SIG
mdefine_line|#define DEBUG_SIG 0
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
r_void
id|ia32_setup_rt_frame
c_func
(paren
r_int
id|sig
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
id|siginfo_t
op_star
id|info
comma
id|sigset_t
op_star
id|set
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|ia32_setup_frame
c_func
(paren
r_int
id|sig
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
id|sigset_t
op_star
id|set
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|function|copy_siginfo_to_user
r_int
id|copy_siginfo_to_user
c_func
(paren
id|siginfo_t
op_star
id|to
comma
id|siginfo_t
op_star
id|from
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
(paren
id|VERIFY_WRITE
comma
id|to
comma
r_sizeof
(paren
id|siginfo_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|from-&gt;si_code
OL
l_int|0
)paren
r_return
id|__copy_to_user
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
id|siginfo_t
)paren
)paren
suffix:semicolon
r_else
(brace
r_int
id|err
suffix:semicolon
multiline_comment|/* If you change siginfo_t structure, please be sure&n;&t;&t;   this code is fixed accordingly.&n;&t;&t;   It should never copy any pad contained in the structure&n;&t;&t;   to avoid security leaks, but must copy the generic&n;&t;&t;   3 ints plus the relevant union member.  */
id|err
op_assign
id|__put_user
c_func
(paren
id|from-&gt;si_signo
comma
op_amp
id|to-&gt;si_signo
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_errno
comma
op_amp
id|to-&gt;si_errno
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
r_int
)paren
id|from-&gt;si_code
comma
op_amp
id|to-&gt;si_code
)paren
suffix:semicolon
multiline_comment|/* First 32bits of unions are always present.  */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_pid
comma
op_amp
id|to-&gt;si_pid
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|from-&gt;si_code
op_rshift
l_int|16
)paren
(brace
r_case
id|__SI_FAULT
op_rshift
l_int|16
suffix:colon
r_break
suffix:semicolon
r_case
id|__SI_CHLD
op_rshift
l_int|16
suffix:colon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_utime
comma
op_amp
id|to-&gt;si_utime
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_stime
comma
op_amp
id|to-&gt;si_stime
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_status
comma
op_amp
id|to-&gt;si_status
)paren
suffix:semicolon
r_default
suffix:colon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_uid
comma
op_amp
id|to-&gt;si_uid
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* case __SI_RT: This is not generated by the kernel as of now.  */
)brace
r_return
id|err
suffix:semicolon
)brace
)brace
id|asmlinkage
r_int
DECL|function|sys_rt_sigsuspend
id|sys_rt_sigsuspend
c_func
(paren
id|sigset_t
op_star
id|unewset
comma
r_int
id|sigsetsize
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
id|sigset_t
id|saveset
comma
id|newset
suffix:semicolon
multiline_comment|/* XXX: Don&squot;t preclude handling different sized sigset_t&squot;s.  */
r_if
c_cond
(paren
id|sigsetsize
op_ne
r_sizeof
(paren
id|sigset_t
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|newset
comma
id|unewset
comma
r_sizeof
(paren
id|newset
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|newset
comma
op_complement
id|_BLOCKABLE
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|saveset
op_assign
id|current-&gt;blocked
suffix:semicolon
id|current-&gt;blocked
op_assign
id|newset
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;rt_sigsuspend savset(%lx) newset(%lx) regs(%p) rip(%lx)&bslash;n&quot;
comma
id|saveset
comma
id|newset
comma
op_amp
id|regs
comma
id|regs.rip
)paren
suffix:semicolon
macro_line|#endif 
id|regs.rax
op_assign
op_minus
id|EINTR
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_signal
c_func
(paren
op_amp
id|regs
comma
op_amp
id|saveset
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
id|asmlinkage
r_int
DECL|function|sys_sigaltstack
id|sys_sigaltstack
c_func
(paren
r_const
id|stack_t
op_star
id|uss
comma
id|stack_t
op_star
id|uoss
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_return
id|do_sigaltstack
c_func
(paren
id|uss
comma
id|uoss
comma
id|regs.rsp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do a signal return; undo the signal stack.&n; */
DECL|struct|rt_sigframe
r_struct
id|rt_sigframe
(brace
DECL|member|pretcode
r_char
op_star
id|pretcode
suffix:semicolon
DECL|member|uc
r_struct
id|ucontext
id|uc
suffix:semicolon
DECL|member|info
r_struct
id|siginfo
id|info
suffix:semicolon
DECL|member|fpstate
r_struct
id|_fpstate
id|fpstate
suffix:semicolon
DECL|member|retcode
r_char
id|retcode
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
DECL|function|restore_sigcontext
id|restore_sigcontext
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|sigcontext
op_star
id|sc
comma
r_int
r_int
op_star
id|prax
)paren
(brace
r_int
r_int
id|err
op_assign
l_int|0
suffix:semicolon
DECL|macro|COPY
mdefine_line|#define COPY(x)&t;&t;err |= __get_user(regs-&gt;x, &amp;sc-&gt;x)
DECL|macro|COPY_SEG
mdefine_line|#define COPY_SEG(seg)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{ unsigned short tmp;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  err |= __get_user(tmp, &amp;sc-&gt;seg);&t;&t;&t;&t;&bslash;&n;&t;  regs-&gt;x##seg = tmp; }
DECL|macro|COPY_SEG_STRICT
mdefine_line|#define COPY_SEG_STRICT(seg)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{ unsigned short tmp;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  err |= __get_user(tmp, &amp;sc-&gt;seg);&t;&t;&t;&t;&bslash;&n;&t;  regs-&gt;x##seg = tmp|3; }
DECL|macro|GET_SEG
mdefine_line|#define GET_SEG(seg)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{ unsigned short tmp;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  err |= __get_user(tmp, &amp;sc-&gt;seg);&t;&t;&t;&t;&bslash;&n;&t;  loadsegment(seg,tmp); }
multiline_comment|/* XXX: rdmsr for 64bits */
id|GET_SEG
c_func
(paren
id|gs
)paren
suffix:semicolon
id|GET_SEG
c_func
(paren
id|fs
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|rdi
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|rsi
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|rbp
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|rsp
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|rbx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|rdx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|rcx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|rip
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|r8
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|r9
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|r10
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|r11
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|r12
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|r13
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|r14
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|r15
)paren
suffix:semicolon
(brace
r_int
r_int
id|tmpflags
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|tmpflags
comma
op_amp
id|sc-&gt;eflags
)paren
suffix:semicolon
id|regs-&gt;eflags
op_assign
(paren
id|regs-&gt;eflags
op_amp
op_complement
l_int|0x40DD5
)paren
op_or
(paren
id|tmpflags
op_amp
l_int|0x40DD5
)paren
suffix:semicolon
id|regs-&gt;orig_rax
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* disable syscall checks */
)brace
(brace
r_struct
id|_fpstate
op_star
id|buf
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|buf
comma
op_amp
id|sc-&gt;fpstate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
r_sizeof
(paren
op_star
id|buf
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|err
op_or_assign
id|restore_i387
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
)brace
id|err
op_or_assign
id|__get_user
c_func
(paren
op_star
id|prax
comma
op_amp
id|sc-&gt;rax
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
id|badframe
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|sys_rt_sigreturn
id|asmlinkage
r_int
id|sys_rt_sigreturn
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_struct
id|rt_sigframe
op_star
id|frame
op_assign
(paren
r_struct
id|rt_sigframe
op_star
)paren
(paren
id|regs.rsp
op_minus
l_int|8
)paren
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
id|stack_t
id|st
suffix:semicolon
r_int
id|eax
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|frame
comma
r_sizeof
(paren
op_star
id|frame
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
op_amp
id|set
comma
op_amp
id|frame-&gt;uc.uc_sigmask
comma
r_sizeof
(paren
id|set
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|set
comma
op_complement
id|_BLOCKABLE
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|set
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|restore_sigcontext
c_func
(paren
op_amp
id|regs
comma
op_amp
id|frame-&gt;uc.uc_mcontext
comma
op_amp
id|eax
)paren
)paren
r_goto
id|badframe
suffix:semicolon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;%d sigreturn rip:%lx rsp:%lx frame:%p rax:%lx&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|regs.rip
comma
id|regs.rsp
comma
id|frame
comma
id|eax
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
op_amp
id|st
comma
op_amp
id|frame-&gt;uc.uc_stack
comma
r_sizeof
(paren
id|st
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/* It is more difficult to avoid calling this function than to&n;&t;   call it and ignore errors.  */
id|do_sigaltstack
c_func
(paren
op_amp
id|st
comma
l_int|NULL
comma
id|regs.rsp
)paren
suffix:semicolon
r_return
id|eax
suffix:semicolon
id|badframe
suffix:colon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;%d bad frame %p&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|frame
)paren
suffix:semicolon
macro_line|#endif
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up a signal frame.&n; */
r_static
r_int
DECL|function|setup_sigcontext
id|setup_sigcontext
c_func
(paren
r_struct
id|sigcontext
op_star
id|sc
comma
r_struct
id|_fpstate
op_star
id|fpstate
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|mask
)paren
(brace
r_int
id|tmp
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%gs,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|sc-&gt;gs
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%fs,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|sc-&gt;fs
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;rdi
comma
op_amp
id|sc-&gt;rdi
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;rsi
comma
op_amp
id|sc-&gt;rsi
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;rbp
comma
op_amp
id|sc-&gt;rbp
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;rsp
comma
op_amp
id|sc-&gt;rsp
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;rbx
comma
op_amp
id|sc-&gt;rbx
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;rdx
comma
op_amp
id|sc-&gt;rdx
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;rcx
comma
op_amp
id|sc-&gt;rcx
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;rax
comma
op_amp
id|sc-&gt;rax
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;r8
comma
op_amp
id|sc-&gt;r8
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;r9
comma
op_amp
id|sc-&gt;r9
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;r10
comma
op_amp
id|sc-&gt;r10
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;r11
comma
op_amp
id|sc-&gt;r11
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;r12
comma
op_amp
id|sc-&gt;r12
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;r13
comma
op_amp
id|sc-&gt;r13
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;r14
comma
op_amp
id|sc-&gt;r14
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;r15
comma
op_amp
id|sc-&gt;r15
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;thread.trap_no
comma
op_amp
id|sc-&gt;trapno
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;thread.error_code
comma
op_amp
id|sc-&gt;err
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;rip
comma
op_amp
id|sc-&gt;rip
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;eflags
comma
op_amp
id|sc-&gt;eflags
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;rsp
comma
op_amp
id|sc-&gt;rsp_at_signal
)paren
suffix:semicolon
id|tmp
op_assign
id|save_i387
c_func
(paren
id|fpstate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OL
l_int|0
)paren
id|err
op_assign
l_int|1
suffix:semicolon
r_else
id|err
op_or_assign
id|__put_user
c_func
(paren
id|tmp
ques
c_cond
id|fpstate
suffix:colon
l_int|NULL
comma
op_amp
id|sc-&gt;fpstate
)paren
suffix:semicolon
multiline_comment|/* non-iBCS2 extensions.. */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|mask
comma
op_amp
id|sc-&gt;oldmask
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;thread.cr2
comma
op_amp
id|sc-&gt;cr2
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Determine which stack to use..&n; */
r_static
r_inline
r_void
op_star
DECL|function|get_sigframe
id|get_sigframe
c_func
(paren
r_struct
id|k_sigaction
op_star
id|ka
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|frame_size
)paren
(brace
r_int
r_int
id|rsp
suffix:semicolon
multiline_comment|/* Default to using normal stack - redzone*/
id|rsp
op_assign
id|regs-&gt;rsp
op_minus
l_int|128
suffix:semicolon
multiline_comment|/* This is the X/Open sanctioned signal stack switching.  */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_ONSTACK
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sas_ss_flags
c_func
(paren
id|rsp
)paren
op_eq
l_int|0
)paren
id|rsp
op_assign
id|current-&gt;sas_ss_sp
op_plus
id|current-&gt;sas_ss_size
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
(paren
(paren
id|rsp
op_minus
id|frame_size
)paren
op_amp
op_minus
l_int|16UL
)paren
suffix:semicolon
)brace
DECL|function|setup_rt_frame
r_static
r_void
id|setup_rt_frame
c_func
(paren
r_int
id|sig
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
id|siginfo_t
op_star
id|info
comma
id|sigset_t
op_star
id|set
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|thread_info
op_star
id|ti
suffix:semicolon
r_struct
id|rt_sigframe
op_star
id|frame
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|frame
op_assign
id|get_sigframe
c_func
(paren
id|ka
comma
id|regs
comma
r_sizeof
(paren
op_star
id|frame
)paren
)paren
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
id|frame
comma
r_sizeof
(paren
op_star
id|frame
)paren
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_SIGINFO
)paren
(brace
id|err
op_or_assign
id|copy_siginfo_to_user
c_func
(paren
op_amp
id|frame-&gt;info
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|give_sigsegv
suffix:semicolon
)brace
multiline_comment|/* Create the ucontext.  */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|frame-&gt;uc.uc_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|frame-&gt;uc.uc_link
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;sas_ss_sp
comma
op_amp
id|frame-&gt;uc.uc_stack.ss_sp
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|sas_ss_flags
c_func
(paren
id|regs-&gt;rsp
)paren
comma
op_amp
id|frame-&gt;uc.uc_stack.ss_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;sas_ss_size
comma
op_amp
id|frame-&gt;uc.uc_stack.ss_size
)paren
suffix:semicolon
id|err
op_or_assign
id|setup_sigcontext
c_func
(paren
op_amp
id|frame-&gt;uc.uc_mcontext
comma
op_amp
id|frame-&gt;fpstate
comma
id|regs
comma
id|set-&gt;sig
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;uc.uc_sigmask
comma
id|set
comma
r_sizeof
(paren
op_star
id|set
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|give_sigsegv
suffix:semicolon
multiline_comment|/* Set up to return from userspace.  If provided, use a stub&n;&t;   already in userspace.  */
multiline_comment|/* x86-64 should always use SA_RESTORER. */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
(brace
id|err
op_or_assign
id|__put_user
c_func
(paren
id|ka-&gt;sa.sa_restorer
comma
op_amp
id|frame-&gt;pretcode
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;%s forgot to set SA_RESTORER for signal %d.&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|sig
)paren
suffix:semicolon
r_goto
id|give_sigsegv
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
r_goto
id|give_sigsegv
suffix:semicolon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;%d old rip %lx old rsp %lx old rax %lx&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|regs-&gt;rip
comma
id|regs-&gt;rsp
comma
id|regs-&gt;rax
)paren
suffix:semicolon
macro_line|#endif
id|ti
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Set up registers for signal handler */
id|regs-&gt;rdi
op_assign
(paren
id|ti-&gt;exec_domain
op_logical_and
id|ti-&gt;exec_domain-&gt;signal_invmap
op_logical_and
id|sig
OL
l_int|32
ques
c_cond
id|ti-&gt;exec_domain-&gt;signal_invmap
(braket
id|sig
)braket
suffix:colon
id|sig
)paren
suffix:semicolon
id|regs-&gt;rax
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* In case the signal handler was declared without prototypes */
multiline_comment|/* This also works for non SA_SIGINFO handlers because they expect the&n;&t;   next argument after the signal number on the stack. */
id|regs-&gt;rsi
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;info
suffix:semicolon
id|regs-&gt;rdx
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;uc
suffix:semicolon
id|regs-&gt;rsp
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|regs-&gt;rip
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
singleline_comment|// XXX: cs
id|regs-&gt;eflags
op_and_assign
op_complement
id|TF_MASK
suffix:semicolon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;SIG deliver (%s:%d): sp=%p pc=%p ra=%p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|frame
comma
id|regs-&gt;rip
comma
id|frame-&gt;pretcode
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
id|give_sigsegv
suffix:colon
r_if
c_cond
(paren
id|sig
op_eq
id|SIGSEGV
)paren
id|ka-&gt;sa.sa_handler
op_assign
id|SIG_DFL
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * OK, we&squot;re invoking a handler&n; */
r_static
r_void
DECL|function|handle_signal
id|handle_signal
c_func
(paren
r_int
r_int
id|sig
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
id|siginfo_t
op_star
id|info
comma
id|sigset_t
op_star
id|oldset
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;handle_signal pid:%d sig:%lu rip:%lx rsp:%lx regs=%p&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|sig
comma
id|regs-&gt;rip
comma
id|regs-&gt;rsp
comma
id|regs
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Are we from a system call? */
r_if
c_cond
(paren
id|regs-&gt;orig_rax
op_ge
l_int|0
)paren
(brace
multiline_comment|/* If so, check system call restarting.. */
r_switch
c_cond
(paren
id|regs-&gt;rax
)paren
(brace
r_case
op_minus
id|ERESTARTNOHAND
suffix:colon
id|regs-&gt;rax
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ERESTARTSYS
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTART
)paren
)paren
(brace
id|regs-&gt;rax
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* fallthrough */
r_case
op_minus
id|ERESTARTNOINTR
suffix:colon
id|regs-&gt;rax
op_assign
id|regs-&gt;orig_rax
suffix:semicolon
id|regs-&gt;rip
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_IA32_EMULATION
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_IA32
)paren
)paren
(brace
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_SIGINFO
)paren
id|ia32_setup_rt_frame
c_func
(paren
id|sig
comma
id|ka
comma
id|info
comma
id|oldset
comma
id|regs
)paren
suffix:semicolon
r_else
id|ia32_setup_frame
c_func
(paren
id|sig
comma
id|ka
comma
id|oldset
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
id|setup_rt_frame
c_func
(paren
id|sig
comma
id|ka
comma
id|info
comma
id|oldset
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_ONESHOT
)paren
id|ka-&gt;sa.sa_handler
op_assign
id|SIG_DFL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_NODEFER
)paren
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|sigorsets
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_amp
id|current-&gt;blocked
comma
op_amp
id|ka-&gt;sa.sa_mask
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|sig
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Note that &squot;init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t&n; * want to handle. Thus you cannot kill init even with a SIGKILL even by&n; * mistake.&n; */
DECL|function|do_signal
r_int
id|do_signal
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|sigset_t
op_star
id|oldset
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_struct
id|k_sigaction
op_star
id|ka
suffix:semicolon
multiline_comment|/*&n;&t; * We want the common case to go fast, which&n;&t; * is why we may in certain cases get here from&n;&t; * kernel mode. Just return without doing anything&n;&t; * if so.&n;&t; */
r_if
c_cond
(paren
(paren
id|regs-&gt;cs
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|oldset
)paren
id|oldset
op_assign
op_amp
id|current-&gt;blocked
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|signr
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|signr
op_assign
id|dequeue_signal
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_amp
id|info
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|signr
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
op_logical_and
id|signr
op_ne
id|SIGKILL
)paren
(brace
multiline_comment|/* Let the debugger run.  */
id|current-&gt;exit_code
op_assign
id|signr
suffix:semicolon
id|preempt_disable
c_func
(paren
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
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We&squot;re back.  Did the debugger cancel the sig?  */
r_if
c_cond
(paren
op_logical_neg
(paren
id|signr
op_assign
id|current-&gt;exit_code
)paren
)paren
r_continue
suffix:semicolon
id|current-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The debugger continued.  Ignore SIGSTOP.  */
r_if
c_cond
(paren
id|signr
op_eq
id|SIGSTOP
)paren
r_continue
suffix:semicolon
multiline_comment|/* Update the siginfo structure.  Is this good?  */
r_if
c_cond
(paren
id|signr
op_ne
id|info.si_signo
)paren
(brace
id|info.si_signo
op_assign
id|signr
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|SI_USER
suffix:semicolon
id|info.si_pid
op_assign
id|current-&gt;p_pptr-&gt;pid
suffix:semicolon
id|info.si_uid
op_assign
id|current-&gt;p_pptr-&gt;uid
suffix:semicolon
)brace
multiline_comment|/* If the (new) signal is now blocked, requeue it.  */
r_if
c_cond
(paren
id|sigismember
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|signr
)paren
)paren
(brace
id|send_sig_info
c_func
(paren
id|signr
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|ka
op_assign
op_amp
id|current-&gt;sig-&gt;action
(braket
id|signr
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_handler
op_eq
id|SIG_IGN
)paren
(brace
r_if
c_cond
(paren
id|signr
op_ne
id|SIGCHLD
)paren
r_continue
suffix:semicolon
multiline_comment|/* Check for SIGCHLD: it&squot;s special.  */
r_while
c_loop
(paren
id|sys_wait4
c_func
(paren
op_minus
l_int|1
comma
l_int|NULL
comma
id|WNOHANG
comma
l_int|NULL
)paren
OG
l_int|0
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ka-&gt;sa.sa_handler
op_eq
id|SIG_DFL
)paren
(brace
r_int
id|exit_code
op_assign
id|signr
suffix:semicolon
multiline_comment|/* Init gets no signals it doesn&squot;t want.  */
r_if
c_cond
(paren
id|current-&gt;pid
op_eq
l_int|1
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|signr
)paren
(brace
r_case
id|SIGCONT
suffix:colon
r_case
id|SIGCHLD
suffix:colon
r_case
id|SIGWINCH
suffix:colon
r_continue
suffix:semicolon
r_case
id|SIGTSTP
suffix:colon
r_case
id|SIGTTIN
suffix:colon
r_case
id|SIGTTOU
suffix:colon
r_if
c_cond
(paren
id|is_orphaned_pgrp
c_func
(paren
id|current-&gt;pgrp
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* FALLTHRU */
r_case
id|SIGSTOP
suffix:colon
(brace
r_struct
id|signal_struct
op_star
id|sig
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|current-&gt;exit_code
op_assign
id|signr
suffix:semicolon
id|sig
op_assign
id|current-&gt;p_pptr-&gt;sig
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_logical_and
op_logical_neg
(paren
id|sig-&gt;action
(braket
id|SIGCHLD
op_minus
l_int|1
)braket
dot
id|sa.sa_flags
op_amp
id|SA_NOCLDSTOP
)paren
)paren
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
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_case
id|SIGQUIT
suffix:colon
r_case
id|SIGILL
suffix:colon
r_case
id|SIGTRAP
suffix:colon
r_case
id|SIGABRT
suffix:colon
r_case
id|SIGFPE
suffix:colon
r_case
id|SIGSEGV
suffix:colon
r_case
id|SIGBUS
suffix:colon
r_case
id|SIGSYS
suffix:colon
r_case
id|SIGXCPU
suffix:colon
r_case
id|SIGXFSZ
suffix:colon
r_if
c_cond
(paren
id|do_coredump
c_func
(paren
id|signr
comma
id|regs
)paren
)paren
id|exit_code
op_or_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* FALLTHRU */
r_default
suffix:colon
id|sig_exit
c_func
(paren
id|signr
comma
id|exit_code
comma
op_amp
id|info
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
)brace
multiline_comment|/* Reenable any watchpoints before delivering the&n;&t;&t; * signal to user space. The processor register will&n;&t;&t; * have been cleared if the watchpoint triggered&n;&t;&t; * inside the kernel.&n;&t;&t; */
id|__asm__
c_func
(paren
l_string|&quot;movq %0,%%db7&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|current-&gt;thread.debugreg
(braket
l_int|7
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* Whee!  Actually deliver the signal.  */
id|handle_signal
c_func
(paren
id|signr
comma
id|ka
comma
op_amp
id|info
comma
id|oldset
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Did we come from a system call? */
r_if
c_cond
(paren
id|regs-&gt;orig_rax
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Restart the system call - no handlers present */
r_if
c_cond
(paren
id|regs-&gt;rax
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;rax
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|regs-&gt;rax
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|regs-&gt;rax
op_assign
id|regs-&gt;orig_rax
suffix:semicolon
id|regs-&gt;rcx
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_notify_resume
r_void
id|do_notify_resume
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|sigset_t
op_star
id|oldset
comma
id|__u32
id|thread_info_flags
)paren
(brace
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;do_notify_resume flags:%x rip:%lx rsp:%lx caller:%lx pending:%lx&bslash;n&quot;
comma
id|thread_info_flags
comma
id|regs-&gt;rip
comma
id|regs-&gt;rsp
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
comma
id|signal_pending
c_func
(paren
id|current
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* deal with pending signal delivery */
r_if
c_cond
(paren
id|thread_info_flags
op_amp
id|_TIF_SIGPENDING
)paren
id|do_signal
c_func
(paren
id|regs
comma
id|oldset
)paren
suffix:semicolon
)brace
eof
