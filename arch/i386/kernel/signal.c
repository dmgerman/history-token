multiline_comment|/*&n; *  linux/arch/i386/kernel/signal.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  1997-11-28  Modified for POSIX.1b signals by Richard Henderson&n; *  2000-06-20  Pentium III FXSR, SSE support by Gareth Hughes&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
DECL|macro|DEBUG_SIG
mdefine_line|#define DEBUG_SIG 0
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
multiline_comment|/*&n; * Atomically swap in the new signal mask, and wait for a signal.&n; */
id|asmlinkage
r_int
DECL|function|sys_sigsuspend
id|sys_sigsuspend
c_func
(paren
r_int
id|history0
comma
r_int
id|history1
comma
id|old_sigset_t
id|mask
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|history0
suffix:semicolon
id|sigset_t
id|saveset
suffix:semicolon
id|mask
op_and_assign
id|_BLOCKABLE
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sig-&gt;siglock
)paren
suffix:semicolon
id|saveset
op_assign
id|current-&gt;blocked
suffix:semicolon
id|siginitset
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|mask
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
id|current-&gt;sig-&gt;siglock
)paren
suffix:semicolon
id|regs-&gt;eax
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
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|unewset
suffix:semicolon
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
id|current-&gt;sig-&gt;siglock
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
id|current-&gt;sig-&gt;siglock
)paren
suffix:semicolon
id|regs-&gt;eax
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
DECL|function|sys_sigaction
id|sys_sigaction
c_func
(paren
r_int
id|sig
comma
r_const
r_struct
id|old_sigaction
op_star
id|act
comma
r_struct
id|old_sigaction
op_star
id|oact
)paren
(brace
r_struct
id|k_sigaction
id|new_ka
comma
id|old_ka
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|act
)paren
(brace
id|old_sigset_t
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|act
comma
r_sizeof
(paren
op_star
id|act
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|new_ka.sa.sa_handler
comma
op_amp
id|act-&gt;sa_handler
)paren
op_logical_or
id|__get_user
c_func
(paren
id|new_ka.sa.sa_restorer
comma
op_amp
id|act-&gt;sa_restorer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__get_user
c_func
(paren
id|new_ka.sa.sa_flags
comma
op_amp
id|act-&gt;sa_flags
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|mask
comma
op_amp
id|act-&gt;sa_mask
)paren
suffix:semicolon
id|siginitset
c_func
(paren
op_amp
id|new_ka.sa.sa_mask
comma
id|mask
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|do_sigaction
c_func
(paren
id|sig
comma
id|act
ques
c_cond
op_amp
id|new_ka
suffix:colon
l_int|NULL
comma
id|oact
ques
c_cond
op_amp
id|old_ka
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|oact
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|oact
comma
r_sizeof
(paren
op_star
id|oact
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|old_ka.sa.sa_handler
comma
op_amp
id|oact-&gt;sa_handler
)paren
op_logical_or
id|__put_user
c_func
(paren
id|old_ka.sa.sa_restorer
comma
op_amp
id|oact-&gt;sa_restorer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__put_user
c_func
(paren
id|old_ka.sa.sa_flags
comma
op_amp
id|oact-&gt;sa_flags
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|old_ka.sa.sa_mask.sig
(braket
l_int|0
)braket
comma
op_amp
id|oact-&gt;sa_mask
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
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
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|uss
suffix:semicolon
r_return
id|do_sigaltstack
c_func
(paren
id|uss
comma
id|uoss
comma
id|regs-&gt;esp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do a signal return; undo the signal stack.&n; */
DECL|struct|sigframe
r_struct
id|sigframe
(brace
DECL|member|pretcode
r_char
op_star
id|pretcode
suffix:semicolon
DECL|member|sig
r_int
id|sig
suffix:semicolon
DECL|member|sc
r_struct
id|sigcontext
id|sc
suffix:semicolon
DECL|member|fpstate
r_struct
id|_fpstate
id|fpstate
suffix:semicolon
DECL|member|extramask
r_int
r_int
id|extramask
(braket
id|_NSIG_WORDS
op_minus
l_int|1
)braket
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
DECL|struct|rt_sigframe
r_struct
id|rt_sigframe
(brace
DECL|member|pretcode
r_char
op_star
id|pretcode
suffix:semicolon
DECL|member|sig
r_int
id|sig
suffix:semicolon
DECL|member|pinfo
r_struct
id|siginfo
op_star
id|pinfo
suffix:semicolon
DECL|member|puc
r_void
op_star
id|puc
suffix:semicolon
DECL|member|info
r_struct
id|siginfo
id|info
suffix:semicolon
DECL|member|uc
r_struct
id|ucontext
id|uc
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
op_star
id|peax
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
id|COPY_SEG
c_func
(paren
id|es
)paren
suffix:semicolon
id|COPY_SEG
c_func
(paren
id|ds
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|edi
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|esi
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ebp
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|esp
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ebx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|edx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ecx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|eip
)paren
suffix:semicolon
id|COPY_SEG_STRICT
c_func
(paren
id|cs
)paren
suffix:semicolon
id|COPY_SEG_STRICT
c_func
(paren
id|ss
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
id|regs-&gt;orig_eax
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
id|peax
comma
op_amp
id|sc-&gt;eax
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
DECL|function|sys_sigreturn
id|asmlinkage
r_int
id|sys_sigreturn
c_func
(paren
r_int
r_int
id|__unused
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|__unused
suffix:semicolon
r_struct
id|sigframe
op_star
id|frame
op_assign
(paren
r_struct
id|sigframe
op_star
)paren
(paren
id|regs-&gt;esp
op_minus
l_int|8
)paren
suffix:semicolon
id|sigset_t
id|set
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
id|__get_user
c_func
(paren
id|set.sig
(braket
l_int|0
)braket
comma
op_amp
id|frame-&gt;sc.oldmask
)paren
op_logical_or
(paren
id|_NSIG_WORDS
OG
l_int|1
op_logical_and
id|__copy_from_user
c_func
(paren
op_amp
id|set.sig
(braket
l_int|1
)braket
comma
op_amp
id|frame-&gt;extramask
comma
r_sizeof
(paren
id|frame-&gt;extramask
)paren
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
id|current-&gt;sig-&gt;siglock
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
id|current-&gt;sig-&gt;siglock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|restore_sigcontext
c_func
(paren
id|regs
comma
op_amp
id|frame-&gt;sc
comma
op_amp
id|eax
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_return
id|eax
suffix:semicolon
id|badframe
suffix:colon
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
DECL|function|sys_rt_sigreturn
id|asmlinkage
r_int
id|sys_rt_sigreturn
c_func
(paren
r_int
r_int
id|__unused
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|__unused
suffix:semicolon
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
id|regs-&gt;esp
op_minus
l_int|4
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
id|current-&gt;sig-&gt;siglock
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
id|current-&gt;sig-&gt;siglock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|restore_sigcontext
c_func
(paren
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
id|regs-&gt;esp
)paren
suffix:semicolon
r_return
id|eax
suffix:semicolon
id|badframe
suffix:colon
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
id|regs-&gt;xes
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|sc-&gt;es
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;xds
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|sc-&gt;ds
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;edi
comma
op_amp
id|sc-&gt;edi
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;esi
comma
op_amp
id|sc-&gt;esi
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;ebp
comma
op_amp
id|sc-&gt;ebp
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;esp
comma
op_amp
id|sc-&gt;esp
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;ebx
comma
op_amp
id|sc-&gt;ebx
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;edx
comma
op_amp
id|sc-&gt;edx
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;ecx
comma
op_amp
id|sc-&gt;ecx
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;eax
comma
op_amp
id|sc-&gt;eax
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
id|regs-&gt;eip
comma
op_amp
id|sc-&gt;eip
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;xcs
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|sc-&gt;cs
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
id|regs-&gt;esp
comma
op_amp
id|sc-&gt;esp_at_signal
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;xss
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|sc-&gt;ss
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
id|esp
suffix:semicolon
multiline_comment|/* Default to using normal stack */
id|esp
op_assign
id|regs-&gt;esp
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
id|sas_ss_flags
c_func
(paren
id|esp
)paren
op_eq
l_int|0
)paren
id|esp
op_assign
id|current-&gt;sas_ss_sp
op_plus
id|current-&gt;sas_ss_size
suffix:semicolon
)brace
multiline_comment|/* This is the legacy signal stack switching. */
r_else
r_if
c_cond
(paren
(paren
id|regs-&gt;xss
op_amp
l_int|0xffff
)paren
op_ne
id|__USER_DS
op_logical_and
op_logical_neg
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
op_logical_and
id|ka-&gt;sa.sa_restorer
)paren
(brace
id|esp
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_restorer
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
(paren
(paren
id|esp
op_minus
id|frame_size
)paren
op_amp
op_minus
l_int|8ul
)paren
suffix:semicolon
)brace
DECL|function|setup_frame
r_static
r_void
id|setup_frame
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
(brace
r_void
op_star
id|restorer
suffix:semicolon
r_struct
id|sigframe
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
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain
op_logical_and
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain-&gt;signal_invmap
op_logical_and
id|sig
OL
l_int|32
ques
c_cond
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain-&gt;signal_invmap
(braket
id|sig
)braket
suffix:colon
id|sig
)paren
comma
op_amp
id|frame-&gt;sig
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
id|err
op_or_assign
id|setup_sigcontext
c_func
(paren
op_amp
id|frame-&gt;sc
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
r_if
c_cond
(paren
id|err
)paren
r_goto
id|give_sigsegv
suffix:semicolon
r_if
c_cond
(paren
id|_NSIG_WORDS
OG
l_int|1
)paren
(brace
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
id|frame-&gt;extramask
comma
op_amp
id|set-&gt;sig
(braket
l_int|1
)braket
comma
r_sizeof
(paren
id|frame-&gt;extramask
)paren
)paren
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
id|restorer
op_assign
(paren
r_void
op_star
)paren
(paren
id|fix_to_virt
c_func
(paren
id|FIX_VSYSCALL
)paren
op_plus
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
id|restorer
op_assign
id|ka-&gt;sa.sa_restorer
suffix:semicolon
multiline_comment|/* Set up to return from userspace.  */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|restorer
comma
op_amp
id|frame-&gt;pretcode
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is popl %eax ; movl $,%eax ; int $0x80&n;&t; *&n;&t; * WE DO NOT USE IT ANY MORE! It&squot;s only left here for historical&n;&t; * reasons and because gdb uses it as a signature to notice&n;&t; * signal handler stack frames.&n;&t; */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0xb858
comma
(paren
r_int
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|0
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|__NR_sigreturn
comma
(paren
r_int
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|2
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x80cd
comma
(paren
r_int
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|6
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
multiline_comment|/* Set up registers for signal handler */
id|regs-&gt;esp
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|regs-&gt;eip
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
id|regs-&gt;xds
op_assign
id|__USER_DS
suffix:semicolon
id|regs-&gt;xes
op_assign
id|__USER_DS
suffix:semicolon
id|regs-&gt;xss
op_assign
id|__USER_DS
suffix:semicolon
id|regs-&gt;xcs
op_assign
id|__USER_CS
suffix:semicolon
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
id|regs-&gt;eip
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
r_void
op_star
id|restorer
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
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain
op_logical_and
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain-&gt;signal_invmap
op_logical_and
id|sig
OL
l_int|32
ques
c_cond
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain-&gt;signal_invmap
(braket
id|sig
)braket
suffix:colon
id|sig
)paren
comma
op_amp
id|frame-&gt;sig
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
op_amp
id|frame-&gt;info
comma
op_amp
id|frame-&gt;pinfo
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
op_amp
id|frame-&gt;uc
comma
op_amp
id|frame-&gt;puc
)paren
suffix:semicolon
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
id|regs-&gt;esp
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
multiline_comment|/* Set up to return from userspace.  */
id|restorer
op_assign
(paren
r_void
op_star
)paren
(paren
id|fix_to_virt
c_func
(paren
id|FIX_VSYSCALL
)paren
op_plus
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
id|restorer
op_assign
id|ka-&gt;sa.sa_restorer
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|restorer
comma
op_amp
id|frame-&gt;pretcode
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is movl $,%eax ; int $0x80&n;&t; *&n;&t; * WE DO NOT USE IT ANY MORE! It&squot;s only left here for historical&n;&t; * reasons and because gdb uses it as a signature to notice&n;&t; * signal handler stack frames.&n;&t; */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0xb8
comma
(paren
r_char
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|0
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|__NR_rt_sigreturn
comma
(paren
r_int
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x80cd
comma
(paren
r_int
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|5
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
multiline_comment|/* Set up registers for signal handler */
id|regs-&gt;esp
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|regs-&gt;eip
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
id|regs-&gt;xds
op_assign
id|__USER_DS
suffix:semicolon
id|regs-&gt;xes
op_assign
id|__USER_DS
suffix:semicolon
id|regs-&gt;xss
op_assign
id|__USER_DS
suffix:semicolon
id|regs-&gt;xcs
op_assign
id|__USER_CS
suffix:semicolon
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
id|regs-&gt;eip
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
r_struct
id|k_sigaction
op_star
id|ka
op_assign
op_amp
id|current-&gt;sig-&gt;action
(braket
id|sig
op_minus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Are we from a system call? */
r_if
c_cond
(paren
id|regs-&gt;orig_eax
op_ge
l_int|0
)paren
(brace
multiline_comment|/* If so, check system call restarting.. */
r_switch
c_cond
(paren
id|regs-&gt;eax
)paren
(brace
r_case
op_minus
id|ERESTART_RESTARTBLOCK
suffix:colon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|restart_block.fn
op_assign
id|do_no_restart_syscall
suffix:semicolon
r_case
op_minus
id|ERESTARTNOHAND
suffix:colon
id|regs-&gt;eax
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
id|regs-&gt;eax
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
id|regs-&gt;eax
op_assign
id|regs-&gt;orig_eax
suffix:semicolon
id|regs-&gt;eip
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
multiline_comment|/* Set up the stack frame */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_SIGINFO
)paren
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
r_else
id|setup_frame
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
id|current-&gt;sig-&gt;siglock
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
id|current-&gt;sig-&gt;siglock
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
r_int
id|signr
suffix:semicolon
multiline_comment|/*&n;&t; * We want the common case to go fast, which&n;&t; * is why we may in certain cases get here from&n;&t; * kernel mode. Just return without doing anything&n;&t; * if so.&n;&t; */
r_if
c_cond
(paren
(paren
id|regs-&gt;xcs
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_FREEZE
)paren
(brace
id|refrigerator
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_goto
id|no_signal
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
id|signr
op_assign
id|get_signal_to_deliver
c_func
(paren
op_amp
id|info
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signr
OG
l_int|0
)paren
(brace
multiline_comment|/* Reenable any watchpoints before delivering the&n;&t;&t; * signal to user space. The processor register will&n;&t;&t; * have been cleared if the watchpoint triggered&n;&t;&t; * inside the kernel.&n;&t;&t; */
id|__asm__
c_func
(paren
l_string|&quot;movl %0,%%db7&quot;
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
id|no_signal
suffix:colon
multiline_comment|/* Did we come from a system call? */
r_if
c_cond
(paren
id|regs-&gt;orig_eax
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Restart the system call - no handlers present */
r_if
c_cond
(paren
id|regs-&gt;eax
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;eax
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|regs-&gt;eax
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|regs-&gt;eax
op_assign
id|regs-&gt;orig_eax
suffix:semicolon
id|regs-&gt;eip
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regs-&gt;eax
op_eq
op_minus
id|ERESTART_RESTARTBLOCK
)paren
(brace
id|regs-&gt;eax
op_assign
id|__NR_restart_syscall
suffix:semicolon
id|regs-&gt;eip
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * notification of userspace execution resumption&n; * - triggered by current-&gt;work.notify_resume&n; */
id|__attribute__
c_func
(paren
(paren
id|regparm
c_func
(paren
l_int|3
)paren
)paren
)paren
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
multiline_comment|/* Pending single-step? */
r_if
c_cond
(paren
id|thread_info_flags
op_amp
id|_TIF_SINGLESTEP
)paren
(brace
id|regs-&gt;eflags
op_or_assign
id|TF_MASK
suffix:semicolon
id|clear_thread_flag
c_func
(paren
id|TIF_SINGLESTEP
)paren
suffix:semicolon
)brace
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
id|clear_thread_flag
c_func
(paren
id|TIF_IRET
)paren
suffix:semicolon
)brace
eof
