multiline_comment|/*&n; *  linux/arch/arm/kernel/signal.c&n; *&n; *  Copyright (C) 1995-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;ptrace.h&quot;
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
multiline_comment|/*&n; * For ARM syscalls, we encode the syscall number into the instruction.&n; */
DECL|macro|SWI_SYS_SIGRETURN
mdefine_line|#define SWI_SYS_SIGRETURN&t;(0xef000000|(__NR_sigreturn))
DECL|macro|SWI_SYS_RT_SIGRETURN
mdefine_line|#define SWI_SYS_RT_SIGRETURN&t;(0xef000000|(__NR_rt_sigreturn))
multiline_comment|/*&n; * For Thumb syscalls, we pass the syscall number via r7.  We therefore&n; * need two 16-bit instructions.&n; */
DECL|macro|SWI_THUMB_SIGRETURN
mdefine_line|#define SWI_THUMB_SIGRETURN&t;(0xdf00 &lt;&lt; 16 | 0x2700 | (__NR_sigreturn - __NR_SYSCALL_BASE))
DECL|macro|SWI_THUMB_RT_SIGRETURN
mdefine_line|#define SWI_THUMB_RT_SIGRETURN&t;(0xdf00 &lt;&lt; 16 | 0x2700 | (__NR_rt_sigreturn - __NR_SYSCALL_BASE))
DECL|variable|retcodes
r_static
r_const
r_int
r_int
id|retcodes
(braket
l_int|4
)braket
op_assign
(brace
id|SWI_SYS_SIGRETURN
comma
id|SWI_THUMB_SIGRETURN
comma
id|SWI_SYS_RT_SIGRETURN
comma
id|SWI_THUMB_RT_SIGRETURN
)brace
suffix:semicolon
id|asmlinkage
r_int
id|do_signal
c_func
(paren
id|sigset_t
op_star
id|oldset
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|syscall
)paren
suffix:semicolon
multiline_comment|/*&n; * atomically swap in the new signal mask, and wait for a signal.&n; */
DECL|function|sys_sigsuspend
id|asmlinkage
r_int
id|sys_sigsuspend
c_func
(paren
r_int
id|restart
comma
r_int
r_int
id|oldmask
comma
id|old_sigset_t
id|mask
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
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
id|current-&gt;sigmask_lock
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
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|regs-&gt;ARM_r0
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
id|saveset
comma
id|regs
comma
l_int|0
)paren
)paren
r_return
id|regs-&gt;ARM_r0
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
op_star
id|regs
)paren
(brace
id|sigset_t
id|saveset
comma
id|newset
suffix:semicolon
multiline_comment|/* XXX: Don&squot;t preclude handling different sized sigset_t&squot;s. */
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
id|regs-&gt;ARM_r0
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
id|saveset
comma
id|regs
comma
l_int|0
)paren
)paren
r_return
id|regs-&gt;ARM_r0
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
multiline_comment|/*&n; * Do a signal return; undo the signal stack.&n; */
DECL|struct|sigframe
r_struct
id|sigframe
(brace
DECL|member|sc
r_struct
id|sigcontext
id|sc
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
r_int
r_int
id|retcode
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rt_sigframe
r_struct
id|rt_sigframe
(brace
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
DECL|member|retcode
r_int
r_int
id|retcode
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
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_r0
comma
op_amp
id|sc-&gt;arm_r0
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_r1
comma
op_amp
id|sc-&gt;arm_r1
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_r2
comma
op_amp
id|sc-&gt;arm_r2
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_r3
comma
op_amp
id|sc-&gt;arm_r3
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_r4
comma
op_amp
id|sc-&gt;arm_r4
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_r5
comma
op_amp
id|sc-&gt;arm_r5
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_r6
comma
op_amp
id|sc-&gt;arm_r6
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_r7
comma
op_amp
id|sc-&gt;arm_r7
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_r8
comma
op_amp
id|sc-&gt;arm_r8
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_r9
comma
op_amp
id|sc-&gt;arm_r9
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_r10
comma
op_amp
id|sc-&gt;arm_r10
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_fp
comma
op_amp
id|sc-&gt;arm_fp
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_ip
comma
op_amp
id|sc-&gt;arm_ip
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_sp
comma
op_amp
id|sc-&gt;arm_sp
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_lr
comma
op_amp
id|sc-&gt;arm_lr
comma
id|err
)paren
suffix:semicolon
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_pc
comma
op_amp
id|sc-&gt;arm_pc
comma
id|err
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
id|__get_user_error
c_func
(paren
id|regs-&gt;ARM_cpsr
comma
op_amp
id|sc-&gt;arm_cpsr
comma
id|err
)paren
suffix:semicolon
macro_line|#endif
id|err
op_or_assign
op_logical_neg
id|valid_user_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|sys_sigreturn
id|asmlinkage
r_int
id|sys_sigreturn
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|sigframe
op_star
id|frame
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
multiline_comment|/*&n;&t; * Since we stacked the signal on a 64-bit boundary,&n;&t; * then &squot;sp&squot; should be word aligned here.  If it&squot;s&n;&t; * not, then the user is trying to mess with us.&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;ARM_sp
op_amp
l_int|7
)paren
r_goto
id|badframe
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|sigframe
op_star
)paren
id|regs-&gt;ARM_sp
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
id|regs
comma
op_amp
id|frame-&gt;sc
)paren
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/* Send SIGTRAP if we&squot;re single-stepping */
r_if
c_cond
(paren
id|ptrace_cancel_bpt
c_func
(paren
id|current
)paren
)paren
id|send_sig
c_func
(paren
id|SIGTRAP
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
id|regs-&gt;ARM_r0
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
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|rt_sigframe
op_star
id|frame
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
multiline_comment|/*&n;&t; * Since we stacked the signal on a 64-bit boundary,&n;&t; * then &squot;sp&squot; should be word aligned here.  If it&squot;s&n;&t; * not, then the user is trying to mess with us.&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;ARM_sp
op_amp
l_int|7
)paren
r_goto
id|badframe
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|rt_sigframe
op_star
)paren
id|regs-&gt;ARM_sp
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
id|regs
comma
op_amp
id|frame-&gt;uc.uc_mcontext
)paren
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/* Send SIGTRAP if we&squot;re single-stepping */
r_if
c_cond
(paren
id|ptrace_cancel_bpt
c_func
(paren
id|current
)paren
)paren
id|send_sig
c_func
(paren
id|SIGTRAP
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
id|regs-&gt;ARM_r0
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
multiline_comment|/*struct _fpstate *fpstate,*/
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
id|err
op_assign
l_int|0
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_r0
comma
op_amp
id|sc-&gt;arm_r0
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_r1
comma
op_amp
id|sc-&gt;arm_r1
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_r2
comma
op_amp
id|sc-&gt;arm_r2
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_r3
comma
op_amp
id|sc-&gt;arm_r3
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_r4
comma
op_amp
id|sc-&gt;arm_r4
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_r5
comma
op_amp
id|sc-&gt;arm_r5
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_r6
comma
op_amp
id|sc-&gt;arm_r6
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_r7
comma
op_amp
id|sc-&gt;arm_r7
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_r8
comma
op_amp
id|sc-&gt;arm_r8
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_r9
comma
op_amp
id|sc-&gt;arm_r9
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_r10
comma
op_amp
id|sc-&gt;arm_r10
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_fp
comma
op_amp
id|sc-&gt;arm_fp
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_ip
comma
op_amp
id|sc-&gt;arm_ip
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_sp
comma
op_amp
id|sc-&gt;arm_sp
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_lr
comma
op_amp
id|sc-&gt;arm_lr
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_pc
comma
op_amp
id|sc-&gt;arm_pc
comma
id|err
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
id|__put_user_error
c_func
(paren
id|regs-&gt;ARM_cpsr
comma
op_amp
id|sc-&gt;arm_cpsr
comma
id|err
)paren
suffix:semicolon
macro_line|#endif
id|__put_user_error
c_func
(paren
id|current-&gt;thread.trap_no
comma
op_amp
id|sc-&gt;trap_no
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|current-&gt;thread.error_code
comma
op_amp
id|sc-&gt;error_code
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|current-&gt;thread.address
comma
op_amp
id|sc-&gt;fault_address
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
id|mask
comma
op_amp
id|sc-&gt;oldmask
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
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
id|framesize
)paren
(brace
r_int
r_int
id|sp
op_assign
id|regs-&gt;ARM_sp
suffix:semicolon
multiline_comment|/*&n;&t; * This is the X/Open sanctioned signal stack switching.&n;&t; */
r_if
c_cond
(paren
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_ONSTACK
)paren
op_logical_and
op_logical_neg
id|sas_ss_flags
c_func
(paren
id|sp
)paren
)paren
id|sp
op_assign
id|current-&gt;sas_ss_sp
op_plus
id|current-&gt;sas_ss_size
suffix:semicolon
multiline_comment|/*&n;&t; * ATPCS B01 mandates 8-byte alignment&n;&t; */
r_return
(paren
r_void
op_star
)paren
(paren
(paren
id|sp
op_minus
id|framesize
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|setup_return
id|setup_return
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
r_int
r_int
op_star
id|rc
comma
r_void
op_star
id|frame
comma
r_int
id|usig
)paren
(brace
r_int
r_int
id|handler
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
r_int
r_int
id|retcode
suffix:semicolon
r_int
id|thumb
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
r_int
r_int
id|cpsr
op_assign
id|regs-&gt;ARM_cpsr
suffix:semicolon
multiline_comment|/*&n;&t; * Maybe we need to deliver a 32-bit signal to a 26-bit task.&n;&t; */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_THIRTYTWO
)paren
id|cpsr
op_assign
(paren
id|cpsr
op_amp
op_complement
id|MODE_MASK
)paren
op_or
id|USR_MODE
suffix:semicolon
macro_line|#ifdef CONFIG_ARM_THUMB
r_if
c_cond
(paren
id|elf_hwcap
op_amp
id|HWCAP_THUMB
)paren
(brace
multiline_comment|/*&n;&t;&t; * The LSB of the handler determines if we&squot;re going to&n;&t;&t; * be using THUMB or ARM mode for this signal handler.&n;&t;&t; */
id|thumb
op_assign
id|handler
op_amp
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|thumb
)paren
id|cpsr
op_or_assign
id|PSR_T_BIT
suffix:semicolon
r_else
id|cpsr
op_and_assign
op_complement
id|PSR_T_BIT
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
(brace
id|retcode
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_restorer
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|idx
op_assign
id|thumb
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_SIGINFO
)paren
id|idx
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|retcodes
(braket
id|idx
)braket
comma
id|rc
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Ensure that the instruction cache sees&n;&t;&t; * the return code written onto the stack.&n;&t;&t; */
id|cpu_icache_invalidate_range
c_func
(paren
(paren
r_int
r_int
)paren
id|rc
comma
(paren
r_int
r_int
)paren
(paren
id|rc
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|retcode
op_assign
(paren
(paren
r_int
r_int
)paren
id|rc
)paren
op_plus
id|thumb
suffix:semicolon
)brace
id|regs-&gt;ARM_r0
op_assign
id|usig
suffix:semicolon
id|regs-&gt;ARM_sp
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|regs-&gt;ARM_lr
op_assign
id|retcode
suffix:semicolon
id|regs-&gt;ARM_pc
op_assign
id|handler
op_amp
(paren
id|thumb
ques
c_cond
op_complement
l_int|1
suffix:colon
op_complement
l_int|3
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
id|regs-&gt;ARM_cpsr
op_assign
id|cpsr
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|setup_frame
id|setup_frame
c_func
(paren
r_int
id|usig
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
r_struct
id|sigframe
op_star
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
r_int
id|err
op_assign
l_int|0
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
r_return
l_int|1
suffix:semicolon
id|err
op_or_assign
id|setup_sigcontext
c_func
(paren
op_amp
id|frame-&gt;sc
comma
multiline_comment|/*&amp;frame-&gt;fpstate,*/
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
op_eq
l_int|0
)paren
id|err
op_assign
id|setup_return
c_func
(paren
id|regs
comma
id|ka
comma
op_amp
id|frame-&gt;retcode
comma
id|frame
comma
id|usig
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_int
DECL|function|setup_rt_frame
id|setup_rt_frame
c_func
(paren
r_int
id|usig
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
op_star
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
r_int
id|err
op_assign
l_int|0
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
r_return
l_int|1
suffix:semicolon
id|__put_user_error
c_func
(paren
op_amp
id|frame-&gt;info
comma
op_amp
id|frame-&gt;pinfo
comma
id|err
)paren
suffix:semicolon
id|__put_user_error
c_func
(paren
op_amp
id|frame-&gt;uc
comma
op_amp
id|frame-&gt;puc
comma
id|err
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
multiline_comment|/* Clear all the bits of the ucontext we don&squot;t use.  */
id|err
op_or_assign
id|__clear_user
c_func
(paren
op_amp
id|frame-&gt;uc
comma
m_offsetof
(paren
r_struct
id|ucontext
comma
id|uc_mcontext
)paren
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
multiline_comment|/*&amp;frame-&gt;fpstate,*/
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
op_eq
l_int|0
)paren
id|err
op_assign
id|setup_return
c_func
(paren
id|regs
comma
id|ka
comma
op_amp
id|frame-&gt;retcode
comma
id|frame
comma
id|usig
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * For realtime signals we must also set the second and third&n;&t;&t; * arguments for the signal handler.&n;&t;&t; *   -- Peter Maydell &lt;pmaydell@chiark.greenend.org.uk&gt; 2000-12-06&n;&t;&t; */
id|regs-&gt;ARM_r1
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;pinfo
suffix:semicolon
id|regs-&gt;ARM_r2
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;puc
suffix:semicolon
)brace
r_return
id|err
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
r_struct
id|thread_info
op_star
id|thread
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_int
id|usig
op_assign
id|sig
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * translate the signal&n;&t; */
r_if
c_cond
(paren
id|usig
OL
l_int|32
op_logical_and
id|thread-&gt;exec_domain
op_logical_and
id|thread-&gt;exec_domain-&gt;signal_invmap
)paren
id|usig
op_assign
id|thread-&gt;exec_domain-&gt;signal_invmap
(braket
id|usig
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the stack frame&n;&t; */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_SIGINFO
)paren
id|ret
op_assign
id|setup_rt_frame
c_func
(paren
id|usig
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
id|ret
op_assign
id|setup_frame
c_func
(paren
id|usig
comma
id|ka
comma
id|oldset
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check that the resulting registers are actually sane.&n;&t; */
id|ret
op_or_assign
op_logical_neg
id|valid_user_regs
c_func
(paren
id|regs
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
id|tsk-&gt;sigmask_lock
)paren
suffix:semicolon
id|sigorsets
c_func
(paren
op_amp
id|tsk-&gt;blocked
comma
op_amp
id|tsk-&gt;blocked
comma
op_amp
id|ka-&gt;sa.sa_mask
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|tsk-&gt;blocked
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
id|tsk-&gt;sigmask_lock
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
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
id|tsk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that &squot;init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t&n; * want to handle. Thus you cannot kill init even with a SIGKILL even by&n; * mistake.&n; *&n; * Note that we go through the signals twice: once to check the signals that&n; * the kernel can handle, and then we build all the user-level signal handling&n; * stack-frames in one go after that.&n; */
DECL|function|do_signal
r_int
id|do_signal
c_func
(paren
id|sigset_t
op_star
id|oldset
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|syscall
)paren
(brace
r_struct
id|k_sigaction
op_star
id|ka
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
r_int
id|single_stepping
suffix:semicolon
multiline_comment|/*&n;&t; * We want the common case to go fast, which&n;&t; * is why we may in certain cases get here from&n;&t; * kernel mode. Just return without doing anything&n;&t; * if so.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_return
l_int|0
suffix:semicolon
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
id|single_stepping
op_assign
id|ptrace_cancel_bpt
c_func
(paren
id|current
)paren
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
r_break
suffix:semicolon
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
id|single_stepping
op_or_assign
id|ptrace_cancel_bpt
c_func
(paren
id|current
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
multiline_comment|/* Update the siginfo structure.  Is this good? */
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
id|current-&gt;parent-&gt;pid
suffix:semicolon
id|info.si_uid
op_assign
id|current-&gt;parent-&gt;uid
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
r_case
id|SIGURG
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
id|current-&gt;parent-&gt;sig
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
multiline_comment|/* Are we from a system call? */
r_if
c_cond
(paren
id|syscall
)paren
(brace
r_switch
c_cond
(paren
id|regs-&gt;ARM_r0
)paren
(brace
r_case
op_minus
id|ERESTARTNOHAND
suffix:colon
id|regs-&gt;ARM_r0
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
id|regs-&gt;ARM_r0
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
id|regs-&gt;ARM_r0
op_assign
id|regs-&gt;ARM_ORIG_r0
suffix:semicolon
id|regs-&gt;ARM_pc
op_sub_assign
l_int|4
suffix:semicolon
)brace
)brace
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
r_if
c_cond
(paren
id|single_stepping
)paren
id|ptrace_set_bpt
c_func
(paren
id|current
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|syscall
op_logical_and
(paren
id|regs-&gt;ARM_r0
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;ARM_r0
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|regs-&gt;ARM_r0
op_eq
op_minus
id|ERESTARTNOINTR
)paren
)paren
(brace
id|regs-&gt;ARM_r0
op_assign
id|regs-&gt;ARM_ORIG_r0
suffix:semicolon
id|regs-&gt;ARM_pc
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|single_stepping
)paren
id|ptrace_set_bpt
c_func
(paren
id|current
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|asmlinkage
r_void
DECL|function|do_notify_resume
id|do_notify_resume
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|thread_flags
comma
r_int
id|syscall
)paren
(brace
r_if
c_cond
(paren
id|thread_flags
op_amp
id|_TIF_SIGPENDING
)paren
id|do_signal
c_func
(paren
l_int|NULL
comma
id|regs
comma
id|syscall
)paren
suffix:semicolon
)brace
eof
