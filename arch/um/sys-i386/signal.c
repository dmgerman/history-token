multiline_comment|/*&n; * Copyright (C) 2004 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/signal.h&quot;
macro_line|#include &quot;linux/ptrace.h&quot;
macro_line|#include &quot;asm/current.h&quot;
macro_line|#include &quot;asm/ucontext.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/unistd.h&quot;
macro_line|#include &quot;frame_kern.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;ptrace_user.h&quot;
macro_line|#include &quot;sigcontext.h&quot;
macro_line|#include &quot;mode.h&quot;
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
r_struct
id|sigcontext
id|sc
suffix:semicolon
r_int
r_int
id|fpregs
(braket
id|HOST_FP_SIZE
)braket
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|sc
comma
id|from
comma
r_sizeof
(paren
id|sc
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_from_user
c_func
(paren
id|fpregs
comma
id|sc.fpstate
comma
r_sizeof
(paren
id|fpregs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|REGS_GS
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.gs
suffix:semicolon
id|REGS_FS
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.fs
suffix:semicolon
id|REGS_ES
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.es
suffix:semicolon
id|REGS_DS
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.ds
suffix:semicolon
id|REGS_EDI
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.edi
suffix:semicolon
id|REGS_ESI
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.esi
suffix:semicolon
id|REGS_EBP
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.ebp
suffix:semicolon
id|REGS_SP
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.esp
suffix:semicolon
id|REGS_EBX
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.ebx
suffix:semicolon
id|REGS_EDX
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.edx
suffix:semicolon
id|REGS_ECX
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.ecx
suffix:semicolon
id|REGS_EAX
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.eax
suffix:semicolon
id|REGS_IP
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.eip
suffix:semicolon
id|REGS_CS
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.cs
suffix:semicolon
id|REGS_EFLAGS
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.eflags
suffix:semicolon
id|REGS_SS
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
op_assign
id|sc.ss
suffix:semicolon
id|regs-&gt;regs.skas.fault_addr
op_assign
id|sc.cr2
suffix:semicolon
id|regs-&gt;regs.skas.fault_type
op_assign
id|FAULT_WRITE
c_func
(paren
id|sc.err
)paren
suffix:semicolon
id|regs-&gt;regs.skas.trap_type
op_assign
id|sc.trapno
suffix:semicolon
id|err
op_assign
id|ptrace_setfpregs
c_func
(paren
id|userspace_pid
(braket
l_int|0
)braket
comma
id|fpregs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;copy_sc_from_user_skas - PTRACE_SETFPREGS failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
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
id|fault_addr
comma
r_int
id|fault_type
)paren
(brace
r_struct
id|sigcontext
id|sc
suffix:semicolon
r_int
r_int
id|fpregs
(braket
id|HOST_FP_SIZE
)braket
suffix:semicolon
r_int
id|err
suffix:semicolon
id|sc.gs
op_assign
id|REGS_GS
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.fs
op_assign
id|REGS_FS
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.es
op_assign
id|REGS_ES
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.ds
op_assign
id|REGS_DS
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.edi
op_assign
id|REGS_EDI
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.esi
op_assign
id|REGS_ESI
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.ebp
op_assign
id|REGS_EBP
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.esp
op_assign
id|REGS_SP
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.ebx
op_assign
id|REGS_EBX
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.edx
op_assign
id|REGS_EDX
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.ecx
op_assign
id|REGS_ECX
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.eax
op_assign
id|REGS_EAX
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.eip
op_assign
id|REGS_IP
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.cs
op_assign
id|REGS_CS
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.eflags
op_assign
id|REGS_EFLAGS
c_func
(paren
id|regs-&gt;regs.skas.regs
)paren
suffix:semicolon
id|sc.esp_at_signal
op_assign
id|regs-&gt;regs.skas.regs
(braket
id|UESP
)braket
suffix:semicolon
id|sc.ss
op_assign
id|regs-&gt;regs.skas.regs
(braket
id|SS
)braket
suffix:semicolon
id|sc.cr2
op_assign
id|fault_addr
suffix:semicolon
id|sc.err
op_assign
id|TO_SC_ERR
c_func
(paren
id|fault_type
)paren
suffix:semicolon
id|sc.trapno
op_assign
id|regs-&gt;regs.skas.trap_type
suffix:semicolon
id|err
op_assign
id|ptrace_getfpregs
c_func
(paren
id|userspace_pid
(braket
l_int|0
)braket
comma
id|fpregs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;copy_sc_to_user_skas - PTRACE_GETFPREGS failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|to_fp
op_assign
(paren
id|to_fp
ques
c_cond
id|to_fp
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
id|sc.fpstate
op_assign
id|to_fp
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
r_return
id|copy_to_user
c_func
(paren
id|to
comma
op_amp
id|sc
comma
r_sizeof
(paren
id|sc
)paren
)paren
op_logical_or
id|copy_to_user
c_func
(paren
id|to_fp
comma
id|fpregs
comma
r_sizeof
(paren
id|fpregs
)paren
)paren
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
r_if
c_cond
(paren
id|to_fp
op_ne
l_int|NULL
)paren
(brace
id|err
op_or_assign
id|copy_from_user
c_func
(paren
op_amp
id|to-&gt;fpstate
comma
op_amp
id|to_fp
comma
r_sizeof
(paren
id|to-&gt;fpstate
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_from_user
c_func
(paren
id|to_fp
comma
id|from_fp
comma
id|fpsize
)paren
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|from_fp
op_ne
l_int|NULL
)paren
(brace
id|err
op_or_assign
id|copy_to_user
c_func
(paren
op_amp
id|to-&gt;fpstate
comma
op_amp
id|to_fp
comma
r_sizeof
(paren
id|to-&gt;fpstate
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_to_user
c_func
(paren
id|to_fp
comma
id|from_fp
comma
id|fpsize
)paren
suffix:semicolon
)brace
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
id|current-&gt;thread.cr2
comma
id|current-&gt;thread.err
)paren
)paren
suffix:semicolon
)brace
DECL|function|copy_ucontext_to_user
r_static
r_int
id|copy_ucontext_to_user
c_func
(paren
r_struct
id|ucontext
op_star
id|uc
comma
r_struct
id|_fpstate
op_star
id|fp
comma
id|sigset_t
op_star
id|set
comma
r_int
r_int
id|sp
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|err
op_or_assign
id|put_user
c_func
(paren
id|current-&gt;sas_ss_sp
comma
op_amp
id|uc-&gt;uc_stack.ss_sp
)paren
suffix:semicolon
id|err
op_or_assign
id|put_user
c_func
(paren
id|sas_ss_flags
c_func
(paren
id|sp
)paren
comma
op_amp
id|uc-&gt;uc_stack.ss_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|put_user
c_func
(paren
id|current-&gt;sas_ss_size
comma
op_amp
id|uc-&gt;uc_stack.ss_size
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_sc_to_user
c_func
(paren
op_amp
id|uc-&gt;uc_mcontext
comma
id|fp
comma
op_amp
id|current-&gt;thread.regs
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_to_user
c_func
(paren
op_amp
id|uc-&gt;uc_sigmask
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
r_return
id|err
suffix:semicolon
)brace
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
DECL|function|setup_signal_stack_sc
r_int
id|setup_signal_stack_sc
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
id|sigset_t
op_star
id|mask
)paren
(brace
r_struct
id|sigframe
id|__user
op_star
id|frame
suffix:semicolon
r_void
op_star
id|restorer
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|stack_top
op_and_assign
op_minus
l_int|8UL
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|sigframe
op_star
)paren
id|stack_top
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
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
r_return
l_int|1
suffix:semicolon
)brace
id|restorer
op_assign
(paren
r_void
op_star
)paren
id|frame-&gt;retcode
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
(brace
id|restorer
op_assign
id|ka-&gt;sa.sa_restorer
suffix:semicolon
)brace
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
id|err
op_or_assign
id|__put_user
c_func
(paren
id|sig
comma
op_amp
id|frame-&gt;sig
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_sc_to_user
c_func
(paren
op_amp
id|frame-&gt;sc
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|mask-&gt;sig
(braket
l_int|0
)braket
comma
op_amp
id|frame-&gt;sc.oldmask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_NSIG_WORDS
OG
l_int|1
)paren
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;extramask
comma
op_amp
id|mask-&gt;sig
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
id|__user
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
id|__user
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
id|__user
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
(brace
r_return
id|err
suffix:semicolon
)brace
id|PT_REGS_SP
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
id|PT_REGS_IP
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
id|PT_REGS_EAX
c_func
(paren
id|regs
)paren
op_assign
(paren
r_int
r_int
)paren
id|sig
suffix:semicolon
id|PT_REGS_EDX
c_func
(paren
id|regs
)paren
op_assign
(paren
r_int
r_int
)paren
l_int|0
suffix:semicolon
id|PT_REGS_ECX
c_func
(paren
id|regs
)paren
op_assign
(paren
r_int
r_int
)paren
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;ptrace
op_amp
id|PT_DTRACE
)paren
op_logical_and
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
)paren
id|ptrace_notify
c_func
(paren
id|SIGTRAP
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|mask
)paren
(brace
r_struct
id|rt_sigframe
id|__user
op_star
id|frame
suffix:semicolon
r_void
op_star
id|restorer
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|stack_top
op_and_assign
op_minus
l_int|8UL
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|rt_sigframe
op_star
)paren
id|stack_top
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
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
r_return
l_int|1
suffix:semicolon
)brace
id|restorer
op_assign
(paren
r_void
op_star
)paren
id|frame-&gt;retcode
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
(brace
id|restorer
op_assign
id|ka-&gt;sa.sa_restorer
suffix:semicolon
)brace
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
id|err
op_or_assign
id|__put_user
c_func
(paren
id|sig
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
id|err
op_or_assign
id|copy_ucontext_to_user
c_func
(paren
op_amp
id|frame-&gt;uc
comma
op_amp
id|frame-&gt;fpstate
comma
id|mask
comma
id|PT_REGS_SP
c_func
(paren
id|regs
)paren
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
id|__user
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
id|__user
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
id|__user
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
(brace
r_return
id|err
suffix:semicolon
)brace
id|PT_REGS_SP
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
id|PT_REGS_IP
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
id|PT_REGS_EAX
c_func
(paren
id|regs
)paren
op_assign
(paren
r_int
r_int
)paren
id|sig
suffix:semicolon
id|PT_REGS_EDX
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
id|PT_REGS_ECX
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
r_if
c_cond
(paren
(paren
id|current-&gt;ptrace
op_amp
id|PT_DTRACE
)paren
op_logical_and
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
)paren
id|ptrace_notify
c_func
(paren
id|SIGTRAP
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_sigreturn
r_int
id|sys_sigreturn
c_func
(paren
r_struct
id|pt_regs
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
id|sigframe
id|__user
op_star
id|frame
op_assign
(paren
r_struct
id|sigframe
op_star
)paren
(paren
id|sp
op_minus
l_int|8
)paren
suffix:semicolon
r_struct
id|sigcontext
id|__user
op_star
id|sc
op_assign
op_amp
id|frame-&gt;sc
suffix:semicolon
r_int
r_int
id|__user
op_star
id|mask
op_assign
op_amp
id|sc-&gt;oldmask
suffix:semicolon
r_int
id|sig_size
op_assign
(paren
id|_NSIG_WORDS
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|copy_from_user
c_func
(paren
op_amp
id|current-&gt;blocked.sig
(braket
l_int|0
)braket
comma
id|mask
comma
r_sizeof
(paren
id|current-&gt;blocked.sig
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|copy_from_user
c_func
(paren
op_amp
id|current-&gt;blocked.sig
(braket
l_int|1
)braket
comma
id|mask
comma
id|sig_size
)paren
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_complement
id|_BLOCKABLE
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
id|copy_sc_from_user
c_func
(paren
op_amp
id|current-&gt;thread.regs
comma
id|sc
)paren
suffix:semicolon
r_return
id|PT_REGS_SYSCALL_RET
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
suffix:semicolon
)brace
DECL|function|sys_rt_sigreturn
r_int
id|sys_rt_sigreturn
c_func
(paren
r_struct
id|pt_regs
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
op_star
)paren
(paren
id|sp
op_minus
l_int|4
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
r_int
id|sig_size
op_assign
id|_NSIG_WORDS
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|copy_from_user
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_amp
id|uc-&gt;uc_sigmask
comma
id|sig_size
)paren
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_complement
id|_BLOCKABLE
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
id|copy_sc_from_user
c_func
(paren
op_amp
id|current-&gt;thread.regs
comma
op_amp
id|uc-&gt;uc_mcontext
)paren
suffix:semicolon
r_return
id|PT_REGS_SYSCALL_RET
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
