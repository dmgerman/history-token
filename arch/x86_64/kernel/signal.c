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
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
multiline_comment|/* #define DEBUG_SIG 1 */
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
id|asmlinkage
r_int
DECL|function|sys_rt_sigsuspend
id|sys_rt_sigsuspend
c_func
(paren
id|sigset_t
id|__user
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
id|current-&gt;sighand-&gt;siglock
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
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_SIG
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
id|__user
op_star
id|uss
comma
id|stack_t
id|__user
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
id|__user
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
multiline_comment|/* Always make any pending restarted system calls return -EINTR */
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|restart_block.fn
op_assign
id|do_no_restart_syscall
suffix:semicolon
DECL|macro|COPY
mdefine_line|#define COPY(x)&t;&t;err |= __get_user(regs-&gt;x, &amp;sc-&gt;x)
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
id|__user
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
id|__user
op_star
id|frame
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
r_int
id|eax
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|rt_sigframe
id|__user
op_star
)paren
(paren
id|regs.rsp
op_minus
l_int|8
)paren
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
(brace
r_goto
id|badframe
suffix:semicolon
)brace
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
(brace
r_goto
id|badframe
suffix:semicolon
)brace
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
id|current-&gt;sighand-&gt;siglock
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
id|current-&gt;sighand-&gt;siglock
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
(brace
r_goto
id|badframe
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_SIG
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
id|do_sigaltstack
c_func
(paren
op_amp
id|frame-&gt;uc.uc_stack
comma
l_int|NULL
comma
id|regs.rsp
)paren
op_eq
op_minus
id|EFAULT
)paren
r_goto
id|badframe
suffix:semicolon
r_return
id|eax
suffix:semicolon
id|badframe
suffix:colon
id|signal_fault
c_func
(paren
op_amp
id|regs
comma
id|frame
comma
l_string|&quot;sigreturn&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up a signal frame.&n; */
r_static
r_inline
r_int
DECL|function|setup_sigcontext
id|setup_sigcontext
c_func
(paren
r_struct
id|sigcontext
id|__user
op_star
id|sc
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|mask
comma
r_struct
id|task_struct
op_star
id|me
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|sc-&gt;gs
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
id|me-&gt;thread.trap_no
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
id|me-&gt;thread.error_code
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
id|me-&gt;thread.cr2
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
r_void
id|__user
op_star
DECL|function|get_stack
id|get_stack
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
r_int
id|size
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
multiline_comment|/* RED-PEN: redzone on that stack? */
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
id|__user
op_star
)paren
id|round_down
c_func
(paren
id|rsp
op_minus
id|size
comma
l_int|16
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
id|rt_sigframe
id|__user
op_star
id|frame
suffix:semicolon
r_struct
id|_fpstate
id|__user
op_star
id|fp
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
id|me
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|me-&gt;used_math
)paren
(brace
id|fp
op_assign
id|get_stack
c_func
(paren
id|ka
comma
id|regs
comma
r_sizeof
(paren
r_struct
id|_fpstate
)paren
)paren
suffix:semicolon
id|frame
op_assign
(paren
r_void
id|__user
op_star
)paren
id|round_down
c_func
(paren
(paren
id|u64
)paren
id|fp
op_minus
r_sizeof
(paren
r_struct
id|rt_sigframe
)paren
comma
l_int|16
)paren
op_minus
l_int|8
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
id|fp
comma
r_sizeof
(paren
r_struct
id|_fpstate
)paren
)paren
)paren
(brace
r_goto
id|give_sigsegv
suffix:semicolon
)brace
r_if
c_cond
(paren
id|save_i387
c_func
(paren
id|fp
)paren
OL
l_int|0
)paren
id|err
op_or_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|frame
op_assign
id|get_stack
c_func
(paren
id|ka
comma
id|regs
comma
r_sizeof
(paren
r_struct
id|rt_sigframe
)paren
)paren
op_minus
l_int|8
suffix:semicolon
)brace
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
(brace
r_goto
id|give_sigsegv
suffix:semicolon
)brace
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
(brace
r_goto
id|give_sigsegv
suffix:semicolon
)brace
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
id|me-&gt;sas_ss_sp
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
id|me-&gt;sas_ss_size
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
id|regs
comma
id|set-&gt;sig
(braket
l_int|0
)braket
comma
id|me
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|fp
comma
op_amp
id|frame-&gt;uc.uc_mcontext.fpstate
)paren
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
op_star
id|set
)paren
op_eq
l_int|16
)paren
(brace
id|__put_user
c_func
(paren
id|set-&gt;sig
(braket
l_int|0
)braket
comma
op_amp
id|frame-&gt;uc.uc_sigmask.sig
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|set-&gt;sig
(braket
l_int|1
)braket
comma
op_amp
id|frame-&gt;uc.uc_sigmask.sig
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
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
)brace
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
id|me-&gt;comm
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
(brace
r_goto
id|give_sigsegv
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_SIG
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
multiline_comment|/* Set up registers for signal handler */
(brace
r_struct
id|exec_domain
op_star
id|ed
op_assign
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|ed
op_logical_and
id|ed-&gt;signal_invmap
op_logical_and
id|sig
OL
l_int|32
)paren
)paren
id|sig
op_assign
id|ed-&gt;signal_invmap
(braket
id|sig
)braket
suffix:semicolon
)brace
id|regs-&gt;rdi
op_assign
id|sig
suffix:semicolon
multiline_comment|/* In case the signal handler was declared without prototypes */
id|regs-&gt;rax
op_assign
l_int|0
suffix:semicolon
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
id|regs-&gt;rip
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|regs-&gt;rsp
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
id|regs-&gt;eflags
op_and_assign
op_complement
id|TF_MASK
suffix:semicolon
macro_line|#ifdef DEBUG_SIG
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
id|signal_fault
c_func
(paren
id|regs
comma
id|frame
comma
l_string|&quot;signal deliver&quot;
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
id|current-&gt;sighand-&gt;action
(braket
id|sig
op_minus
l_int|1
)braket
suffix:semicolon
macro_line|#ifdef DEBUG_SIG
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
id|ERESTART_RESTARTBLOCK
suffix:colon
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
id|current-&gt;sighand-&gt;siglock
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
id|current-&gt;sighand-&gt;siglock
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
comma
l_int|NULL
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
r_if
c_cond
(paren
id|current-&gt;thread.debugreg7
)paren
id|asm
r_volatile
(paren
l_string|&quot;movq %0,%%db7&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|current-&gt;thread.debugreg7
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
id|regs-&gt;orig_rax
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Restart the system call - no handlers present */
r_int
id|res
op_assign
id|regs-&gt;rax
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|res
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|res
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|regs-&gt;rax
op_assign
id|regs-&gt;orig_rax
suffix:semicolon
id|regs-&gt;rip
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regs-&gt;rax
op_eq
(paren
r_int
r_int
)paren
op_minus
id|ERESTART_RESTARTBLOCK
)paren
(brace
id|regs-&gt;rax
op_assign
id|__NR_restart_syscall
suffix:semicolon
id|regs-&gt;rip
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
macro_line|#ifdef DEBUG_SIG
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
)brace
DECL|function|signal_fault
r_void
id|signal_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_void
id|__user
op_star
id|frame
comma
r_char
op_star
id|where
)paren
(brace
r_struct
id|task_struct
op_star
id|me
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|exception_trace
)paren
id|printk
c_func
(paren
l_string|&quot;%s[%d] bad frame in %s frame:%p rip:%lx rsp:%lx orax:%lx&bslash;n&quot;
comma
id|me-&gt;comm
comma
id|me-&gt;pid
comma
id|where
comma
id|frame
comma
id|regs-&gt;rip
comma
id|regs-&gt;rsp
comma
id|regs-&gt;orig_rax
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|me
)paren
suffix:semicolon
)brace
eof
