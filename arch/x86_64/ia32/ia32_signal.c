multiline_comment|/*&n; *  linux/arch/x86_64/ia32/ia32_signal.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  1997-11-28  Modified for POSIX.1b signals by Richard Henderson&n; *  2000-06-20  Pentium III FXSR, SSE support by Gareth Hughes&n; *  2000-12-*   x86-64 compatibility mode signal handling by Andi Kleen&n; * &n; *  $Id: ia32_signal.c,v 1.17 2002/03/21 14:16:32 ak Exp $&n; */
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
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/ia32_unistd.h&gt;
macro_line|#include &lt;asm/user32.h&gt;
macro_line|#include &lt;asm/sigcontext32.h&gt;
macro_line|#include &lt;asm/fpu32.h&gt;
DECL|macro|ptr_to_u32
mdefine_line|#define ptr_to_u32(x) ((u32)(u64)(x))&t;/* avoid gcc warning */ 
DECL|macro|DEBUG_SIG
mdefine_line|#define DEBUG_SIG 0
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
id|asmlinkage
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
suffix:semicolon
DECL|function|ia32_copy_siginfo_to_user
r_static
r_int
id|ia32_copy_siginfo_to_user
c_func
(paren
id|siginfo_t32
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
DECL|function|sys32_sigsuspend
id|sys32_sigsuspend
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
comma
r_struct
id|pt_regs
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
DECL|function|sys32_sigaltstack
id|sys32_sigaltstack
c_func
(paren
r_const
id|stack_ia32_t
op_star
id|uss_ptr
comma
id|stack_ia32_t
op_star
id|uoss_ptr
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
id|stack_t
id|uss
comma
id|uoss
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|mm_segment_t
id|seg
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
id|uss_ptr
comma
r_sizeof
(paren
id|stack_ia32_t
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|ptr_to_u32
c_func
(paren
id|uss.ss_sp
)paren
comma
op_amp
id|uss_ptr-&gt;ss_sp
)paren
op_logical_or
id|__get_user
c_func
(paren
(paren
id|u32
)paren
id|uss.ss_flags
comma
op_amp
id|uss_ptr-&gt;ss_flags
)paren
op_logical_or
id|__get_user
c_func
(paren
(paren
id|u32
)paren
id|uss.ss_size
comma
op_amp
id|uss_ptr-&gt;ss_size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|seg
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|ret
op_assign
id|do_sigaltstack
c_func
(paren
op_amp
id|uss
comma
op_amp
id|uoss
comma
id|regs.rsp
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|seg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
op_logical_and
id|uoss_ptr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|uss_ptr
comma
r_sizeof
(paren
id|stack_ia32_t
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|ptr_to_u32
c_func
(paren
id|uss.ss_sp
)paren
comma
op_amp
id|uss_ptr-&gt;ss_sp
)paren
op_logical_or
id|__put_user
c_func
(paren
(paren
id|u32
)paren
id|uss.ss_flags
comma
op_amp
id|uss_ptr-&gt;ss_flags
)paren
op_logical_or
id|__put_user
c_func
(paren
(paren
id|u32
)paren
id|uss.ss_size
comma
op_amp
id|uss_ptr-&gt;ss_size
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
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
DECL|member|pretcode
id|u32
id|pretcode
suffix:semicolon
DECL|member|sig
r_int
id|sig
suffix:semicolon
DECL|member|sc
r_struct
id|sigcontext_ia32
id|sc
suffix:semicolon
DECL|member|fpstate
r_struct
id|_fpstate_ia32
id|fpstate
suffix:semicolon
DECL|member|extramask
r_int
r_int
id|extramask
(braket
id|_IA32_NSIG_WORDS
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
id|u32
id|pretcode
suffix:semicolon
DECL|member|sig
r_int
id|sig
suffix:semicolon
DECL|member|pinfo
id|u32
id|pinfo
suffix:semicolon
DECL|member|puc
id|u32
id|puc
suffix:semicolon
DECL|member|info
r_struct
id|siginfo32
id|info
suffix:semicolon
DECL|member|uc
r_struct
id|ucontext_ia32
id|uc
suffix:semicolon
DECL|member|fpstate
r_struct
id|_fpstate_ia32
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
DECL|function|ia32_restore_sigcontext
id|ia32_restore_sigcontext
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|sigcontext_ia32
op_star
id|sc
comma
r_int
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
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;SIG restore_sigcontext: sc=%p err(%x) eip(%x) cs(%x) flg(%x)&bslash;n&quot;
comma
id|sc
comma
id|sc-&gt;err
comma
id|sc-&gt;eip
comma
id|sc-&gt;cs
comma
id|sc-&gt;eflags
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|COPY
mdefine_line|#define COPY(x)&t;&t;{ &bslash;&n;&t;unsigned int reg;&t;&bslash;&n;&t;err |= __get_user(reg, &amp;sc-&gt;e ##x);&t;&bslash;&n;&t;regs-&gt;r ## x = reg;&t;&t;&t;&bslash;&n;}
DECL|macro|RELOAD_SEG
mdefine_line|#define RELOAD_SEG(seg)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{ unsigned int cur; &t;&t;&t;&t;&bslash;&n;&t;  unsigned short pre;&t;&t;&t;&t;&bslash;&n;&t;  err |= __get_user(pre, &amp;sc-&gt;seg);&t;&t;&t;&t;&bslash;&n;    &t;  asm volatile(&quot;movl %%&quot; #seg &quot;,%0&quot; : &quot;=r&quot; (cur));&t;&t;&bslash;&n;&t;  if (pre != cur) loadsegment(seg,pre); }
multiline_comment|/* Reload fs and gs if they have changed in the signal handler. */
(brace
r_int
r_int
id|gs
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|gs
comma
op_amp
id|sc-&gt;gs
)paren
suffix:semicolon
id|load_gs_index
c_func
(paren
id|gs
)paren
suffix:semicolon
)brace
id|RELOAD_SEG
c_func
(paren
id|fs
)paren
suffix:semicolon
id|RELOAD_SEG
c_func
(paren
id|ds
)paren
suffix:semicolon
id|RELOAD_SEG
c_func
(paren
id|es
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|di
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|si
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|bp
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|sp
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|bx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|dx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|cx
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ip
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t touch extended registers */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|regs-&gt;cs
comma
op_amp
id|sc-&gt;cs
)paren
suffix:semicolon
id|regs-&gt;cs
op_or_assign
l_int|2
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|regs-&gt;ss
comma
op_amp
id|sc-&gt;ss
)paren
suffix:semicolon
id|regs-&gt;ss
op_or_assign
l_int|2
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
id|u32
id|tmp
suffix:semicolon
r_struct
id|_fpstate_ia32
op_star
id|buf
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|tmp
comma
op_amp
id|sc-&gt;fpstate
)paren
suffix:semicolon
id|buf
op_assign
(paren
r_struct
id|_fpstate_ia32
op_star
)paren
(paren
id|u64
)paren
id|tmp
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
id|restore_i387_ia32
c_func
(paren
id|current
comma
id|buf
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
(brace
id|u32
id|tmp
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|tmp
comma
op_amp
id|sc-&gt;eax
)paren
suffix:semicolon
op_star
id|peax
op_assign
id|tmp
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
id|badframe
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|sys32_sigreturn
id|asmlinkage
r_int
id|sys32_sigreturn
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
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
id|regs.rsp
op_minus
l_int|8
)paren
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
r_int
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
id|_IA32_NSIG_WORDS
OG
l_int|1
op_logical_and
id|__copy_from_user
c_func
(paren
(paren
(paren
(paren
r_char
op_star
)paren
op_amp
id|set.sig
)paren
op_plus
l_int|4
)paren
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
id|ia32_restore_sigcontext
c_func
(paren
op_amp
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
id|signal_fault
c_func
(paren
op_amp
id|regs
comma
id|frame
comma
l_string|&quot;32bit sigreturn&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys32_rt_sigreturn
id|asmlinkage
r_int
id|sys32_rt_sigreturn
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
id|ia32_restore_sigcontext
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
(brace
id|mm_segment_t
id|oldds
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
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
id|set_fs
c_func
(paren
id|oldds
)paren
suffix:semicolon
)brace
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
l_string|&quot;32bit rt sigreturn&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up a signal frame.&n; */
r_static
r_int
DECL|function|ia32_setup_sigcontext
id|ia32_setup_sigcontext
c_func
(paren
r_struct
id|sigcontext_ia32
op_star
id|sc
comma
r_struct
id|_fpstate_ia32
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
id|__asm__
c_func
(paren
l_string|&quot;movl %%ds,%0&quot;
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
id|sc-&gt;ds
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%es,%0&quot;
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
id|sc-&gt;es
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|u32
)paren
id|regs-&gt;rdi
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
(paren
id|u32
)paren
id|regs-&gt;rsi
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
(paren
id|u32
)paren
id|regs-&gt;rbp
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
(paren
id|u32
)paren
id|regs-&gt;rsp
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
(paren
id|u32
)paren
id|regs-&gt;rbx
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
(paren
id|u32
)paren
id|regs-&gt;rdx
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
(paren
id|u32
)paren
id|regs-&gt;rcx
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
(paren
id|u32
)paren
id|regs-&gt;rax
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
(paren
id|u32
)paren
id|regs-&gt;cs
comma
op_amp
id|sc-&gt;cs
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|u32
)paren
id|regs-&gt;ss
comma
op_amp
id|sc-&gt;ss
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
(paren
id|u32
)paren
id|regs-&gt;rip
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
(paren
id|u32
)paren
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
(paren
id|u32
)paren
id|regs-&gt;rsp
comma
op_amp
id|sc-&gt;esp_at_signal
)paren
suffix:semicolon
id|tmp
op_assign
id|save_i387_ia32
c_func
(paren
id|current
comma
id|fpstate
comma
id|regs
comma
l_int|0
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
op_minus
id|EFAULT
suffix:semicolon
r_else
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|u32
)paren
(paren
id|u64
)paren
(paren
id|tmp
ques
c_cond
id|fpstate
suffix:colon
l_int|NULL
)paren
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
multiline_comment|/* Default to using normal stack */
id|rsp
op_assign
id|regs-&gt;rsp
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
id|on_sig_stack
c_func
(paren
id|rsp
)paren
)paren
id|rsp
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
id|regs-&gt;ss
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
id|rsp
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
id|rsp
op_minus
id|frame_size
)paren
op_amp
op_minus
l_int|8UL
)paren
suffix:semicolon
)brace
DECL|function|ia32_setup_frame
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
id|sigset32_t
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
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|ed
op_logical_and
id|ed-&gt;signal_invmap
op_logical_and
id|sig
OL
l_int|32
ques
c_cond
id|ed-&gt;signal_invmap
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
)brace
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
id|ia32_setup_sigcontext
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
id|_IA32_NSIG_WORDS
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
multiline_comment|/* Set up to return from userspace.  If provided, use a stub&n;&t;   already in userspace.  */
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
(paren
id|u32
)paren
(paren
id|u64
)paren
id|ka-&gt;sa.sa_restorer
comma
op_amp
id|frame-&gt;pretcode
)paren
suffix:semicolon
)brace
r_else
(brace
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|u32
)paren
(paren
id|u64
)paren
id|frame-&gt;retcode
comma
op_amp
id|frame-&gt;pretcode
)paren
suffix:semicolon
multiline_comment|/* This is popl %eax ; movl $,%eax ; int $0x80 */
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|u16
)paren
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
(paren
id|u32
)paren
id|__NR_ia32_sigreturn
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
(paren
id|u16
)paren
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
)brace
r_if
c_cond
(paren
id|err
)paren
r_goto
id|give_sigsegv
suffix:semicolon
multiline_comment|/* Set up registers for signal handler */
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
id|asm
r_volatile
(paren
l_string|&quot;movl %0,%%ds&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|__USER32_DS
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0,%%es&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|__USER32_DS
)paren
)paren
suffix:semicolon
id|regs-&gt;cs
op_assign
id|__USER32_CS
suffix:semicolon
id|regs-&gt;ss
op_assign
id|__USER32_DS
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
id|signal_fault
c_func
(paren
id|regs
comma
id|frame
comma
l_string|&quot;32bit signal setup&quot;
)paren
suffix:semicolon
)brace
DECL|function|ia32_setup_rt_frame
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
id|sigset32_t
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
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|ed
op_logical_and
id|ed-&gt;signal_invmap
op_logical_and
id|sig
OL
l_int|32
ques
c_cond
id|ed-&gt;signal_invmap
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
)brace
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|u32
)paren
(paren
id|u64
)paren
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
(paren
id|u32
)paren
(paren
id|u64
)paren
op_amp
id|frame-&gt;uc
comma
op_amp
id|frame-&gt;puc
)paren
suffix:semicolon
id|err
op_or_assign
id|ia32_copy_siginfo_to_user
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
id|ia32_setup_sigcontext
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
(paren
id|u32
)paren
(paren
id|u64
)paren
id|ka-&gt;sa.sa_restorer
comma
op_amp
id|frame-&gt;pretcode
)paren
suffix:semicolon
)brace
r_else
(brace
id|err
op_or_assign
id|__put_user
c_func
(paren
id|ptr_to_u32
c_func
(paren
id|frame-&gt;retcode
)paren
comma
op_amp
id|frame-&gt;pretcode
)paren
suffix:semicolon
multiline_comment|/* This is movl $,%eax ; int $0x80 */
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
(paren
id|u32
)paren
id|__NR_ia32_rt_sigreturn
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
)brace
r_if
c_cond
(paren
id|err
)paren
r_goto
id|give_sigsegv
suffix:semicolon
multiline_comment|/* Set up registers for signal handler */
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
id|asm
r_volatile
(paren
l_string|&quot;movl %0,%%ds&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|__USER32_DS
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0,%%es&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|__USER32_DS
)paren
)paren
suffix:semicolon
id|regs-&gt;cs
op_assign
id|__USER32_CS
suffix:semicolon
id|regs-&gt;ss
op_assign
id|__USER32_DS
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
id|signal_fault
c_func
(paren
id|regs
comma
id|frame
comma
l_string|&quot;32bit rt signal setup&quot;
)paren
suffix:semicolon
)brace
eof
