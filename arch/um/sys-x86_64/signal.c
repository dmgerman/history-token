multiline_comment|/*&n; * Copyright (C) 2003 PathScale, Inc.&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/stddef.h&quot;
macro_line|#include &quot;linux/errno.h&quot;
macro_line|#include &quot;linux/personality.h&quot;
macro_line|#include &quot;linux/ptrace.h&quot;
macro_line|#include &quot;asm/current.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/sigcontext.h&quot;
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;asm/arch/ucontext.h&quot;
macro_line|#include &quot;choose-mode.h&quot;
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;frame_kern.h&quot;
macro_line|#ifdef CONFIG_MODE_SKAS
macro_line|#include &quot;skas.h&quot;
DECL|function|copy_sc_from_user_skas
r_static
r_int
id|copy_sc_from_user_skas
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
id|from
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
DECL|macro|GETREG
mdefine_line|#define GETREG(regs, regno, sc, regname) &bslash;&n;       __get_user((regs)-&gt;regs.skas.regs[(regno) / sizeof(unsigned long)], &bslash;&n;                  &amp;(sc)-&gt;regname)
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|R8
comma
id|from
comma
id|r8
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|R9
comma
id|from
comma
id|r9
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|R10
comma
id|from
comma
id|r10
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|R11
comma
id|from
comma
id|r11
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|R12
comma
id|from
comma
id|r12
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|R13
comma
id|from
comma
id|r13
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|R14
comma
id|from
comma
id|r14
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|R15
comma
id|from
comma
id|r15
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|RDI
comma
id|from
comma
id|rdi
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|RSI
comma
id|from
comma
id|rsi
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|RBP
comma
id|from
comma
id|rbp
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|RBX
comma
id|from
comma
id|rbx
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|RDX
comma
id|from
comma
id|rdx
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|RAX
comma
id|from
comma
id|rax
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|RCX
comma
id|from
comma
id|rcx
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|RSP
comma
id|from
comma
id|rsp
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|RIP
comma
id|from
comma
id|rip
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|EFLAGS
comma
id|from
comma
id|eflags
)paren
suffix:semicolon
id|err
op_or_assign
id|GETREG
c_func
(paren
id|regs
comma
id|CS
comma
id|from
comma
id|cs
)paren
suffix:semicolon
DECL|macro|GETREG
macro_line|#undef GETREG
r_return
id|err
suffix:semicolon
)brace
DECL|function|copy_sc_to_user_skas
r_int
id|copy_sc_to_user_skas
c_func
(paren
r_struct
id|sigcontext
op_star
id|to
comma
r_struct
id|_fpstate
op_star
id|to_fp
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
r_int
id|eflags
suffix:semicolon
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
id|to-&gt;gs
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
id|to-&gt;fs
)paren
suffix:semicolon
DECL|macro|PUTREG
mdefine_line|#define PUTREG(regs, regno, sc, regname) &bslash;&n;       __put_user((regs)-&gt;regs.skas.regs[(regno) / sizeof(unsigned long)], &bslash;&n;                  &amp;(sc)-&gt;regname)
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|RDI
comma
id|to
comma
id|rdi
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|RSI
comma
id|to
comma
id|rsi
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|RBP
comma
id|to
comma
id|rbp
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|RSP
comma
id|to
comma
id|rsp
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|RBX
comma
id|to
comma
id|rbx
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|RDX
comma
id|to
comma
id|rdx
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|RCX
comma
id|to
comma
id|rcx
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|RAX
comma
id|to
comma
id|rax
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|R8
comma
id|to
comma
id|r8
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|R9
comma
id|to
comma
id|r9
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|R10
comma
id|to
comma
id|r10
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|R11
comma
id|to
comma
id|r11
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|R12
comma
id|to
comma
id|r12
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|R13
comma
id|to
comma
id|r13
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|R14
comma
id|to
comma
id|r14
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|R15
comma
id|to
comma
id|r15
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|CS
comma
id|to
comma
id|cs
)paren
suffix:semicolon
multiline_comment|/* XXX x86_64 doesn&squot;t do this */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;thread.err
comma
op_amp
id|to-&gt;err
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
id|to-&gt;trapno
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|RIP
comma
id|to
comma
id|rip
)paren
suffix:semicolon
id|err
op_or_assign
id|PUTREG
c_func
(paren
id|regs
comma
id|EFLAGS
comma
id|to
comma
id|eflags
)paren
suffix:semicolon
DECL|macro|PUTREG
macro_line|#undef PUTREG
id|err
op_or_assign
id|__put_user
c_func
(paren
id|mask
comma
op_amp
id|to-&gt;oldmask
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
id|to-&gt;cr2
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_MODE_TT
DECL|function|copy_sc_from_user_tt
r_int
id|copy_sc_from_user_tt
c_func
(paren
r_struct
id|sigcontext
op_star
id|to
comma
r_struct
id|sigcontext
op_star
id|from
comma
r_int
id|fpsize
)paren
(brace
r_struct
id|_fpstate
op_star
id|to_fp
comma
op_star
id|from_fp
suffix:semicolon
r_int
r_int
id|sigs
suffix:semicolon
r_int
id|err
suffix:semicolon
id|to_fp
op_assign
id|to-&gt;fpstate
suffix:semicolon
id|from_fp
op_assign
id|from-&gt;fpstate
suffix:semicolon
id|sigs
op_assign
id|to-&gt;oldmask
suffix:semicolon
id|err
op_assign
id|copy_from_user
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
op_star
id|to
)paren
)paren
suffix:semicolon
id|to-&gt;oldmask
op_assign
id|sigs
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|copy_sc_to_user_tt
r_int
id|copy_sc_to_user_tt
c_func
(paren
r_struct
id|sigcontext
op_star
id|to
comma
r_struct
id|_fpstate
op_star
id|fp
comma
r_struct
id|sigcontext
op_star
id|from
comma
r_int
id|fpsize
)paren
(brace
r_struct
id|_fpstate
op_star
id|to_fp
comma
op_star
id|from_fp
suffix:semicolon
r_int
id|err
suffix:semicolon
id|to_fp
op_assign
(paren
id|fp
ques
c_cond
id|fp
suffix:colon
(paren
r_struct
id|_fpstate
op_star
)paren
(paren
id|to
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|from_fp
op_assign
id|from-&gt;fpstate
suffix:semicolon
id|err
op_assign
id|copy_to_user
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
op_star
id|to
)paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif
DECL|function|copy_sc_from_user
r_static
r_int
id|copy_sc_from_user
c_func
(paren
r_struct
id|pt_regs
op_star
id|to
comma
r_void
id|__user
op_star
id|from
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|CHOOSE_MODE
c_func
(paren
id|copy_sc_from_user_tt
c_func
(paren
id|UPT_SC
c_func
(paren
op_amp
id|to-&gt;regs
)paren
comma
id|from
comma
r_sizeof
(paren
r_struct
id|_fpstate
)paren
)paren
comma
id|copy_sc_from_user_skas
c_func
(paren
id|to
comma
id|from
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|copy_sc_to_user
r_static
r_int
id|copy_sc_to_user
c_func
(paren
r_struct
id|sigcontext
op_star
id|to
comma
r_struct
id|_fpstate
op_star
id|fp
comma
r_struct
id|pt_regs
op_star
id|from
comma
r_int
r_int
id|mask
)paren
(brace
r_return
id|CHOOSE_MODE
c_func
(paren
id|copy_sc_to_user_tt
c_func
(paren
id|to
comma
id|fp
comma
id|UPT_SC
c_func
(paren
op_amp
id|from-&gt;regs
)paren
comma
r_sizeof
(paren
op_star
id|fp
)paren
)paren
comma
id|copy_sc_to_user_skas
c_func
(paren
id|to
comma
id|fp
comma
id|from
comma
id|mask
)paren
)paren
suffix:semicolon
)brace
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
DECL|macro|round_down
mdefine_line|#define round_down(m, n) (((m) / (n)) * (n))
DECL|function|setup_signal_stack_si
r_int
id|setup_signal_stack_si
c_func
(paren
r_int
r_int
id|stack_top
comma
r_int
id|sig
comma
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
id|siginfo_t
op_star
id|info
comma
id|sigset_t
op_star
id|set
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
id|frame
op_assign
(paren
r_struct
id|rt_sigframe
id|__user
op_star
)paren
id|round_down
c_func
(paren
id|stack_top
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
id|frame
op_sub_assign
l_int|128
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
r_goto
id|out
suffix:semicolon
macro_line|#if 0 /* XXX */
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
macro_line|#endif
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
id|out
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
id|out
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
id|PT_REGS_SP
c_func
(paren
id|regs
)paren
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
id|copy_sc_to_user
c_func
(paren
op_amp
id|frame-&gt;uc.uc_mcontext
comma
id|fp
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
multiline_comment|/* Set up to return from userspace.  If provided, use a stub&n;&t;   already in userspace.  */
multiline_comment|/* x86-64 should always use SA_RESTORER. */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
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
r_else
multiline_comment|/* could use a vstub here */
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
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
id|PT_REGS_RDI
c_func
(paren
id|regs
)paren
op_assign
id|sig
suffix:semicolon
multiline_comment|/* In case the signal handler was declared without prototypes */
id|PT_REGS_RAX
c_func
(paren
id|regs
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This also works for non SA_SIGINFO handlers because they expect the&n;&t;   next argument after the signal number on the stack. */
id|PT_REGS_RSI
c_func
(paren
id|regs
)paren
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;info
suffix:semicolon
id|PT_REGS_RDX
c_func
(paren
id|regs
)paren
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;uc
suffix:semicolon
id|PT_REGS_RIP
c_func
(paren
id|regs
)paren
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|PT_REGS_RSP
c_func
(paren
id|regs
)paren
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|sys_rt_sigreturn
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
r_int
r_int
id|__user
id|sp
op_assign
id|PT_REGS_SP
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
suffix:semicolon
r_struct
id|rt_sigframe
id|__user
op_star
id|frame
op_assign
(paren
r_struct
id|rt_sigframe
id|__user
op_star
)paren
(paren
id|sp
op_minus
l_int|8
)paren
suffix:semicolon
r_struct
id|ucontext
id|__user
op_star
id|uc
op_assign
op_amp
id|frame-&gt;uc
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|set
comma
op_amp
id|uc-&gt;uc_sigmask
comma
r_sizeof
(paren
id|set
)paren
)paren
)paren
(brace
r_goto
id|segfault
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
id|copy_sc_from_user
c_func
(paren
op_amp
id|current-&gt;thread.regs
comma
op_amp
id|uc-&gt;uc_mcontext
)paren
)paren
(brace
r_goto
id|segfault
suffix:semicolon
)brace
multiline_comment|/* Avoid ERESTART handling */
id|PT_REGS_SYSCALL_NR
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|PT_REGS_SYSCALL_RET
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
suffix:semicolon
id|segfault
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
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
