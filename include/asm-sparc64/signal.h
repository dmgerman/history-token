multiline_comment|/* $Id: signal.h,v 1.9 1999/09/06 08:22:11 jj Exp $ */
macro_line|#ifndef _ASMSPARC64_SIGNAL_H
DECL|macro|_ASMSPARC64_SIGNAL_H
mdefine_line|#define _ASMSPARC64_SIGNAL_H
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#endif
macro_line|#endif
multiline_comment|/* On the Sparc the signal handlers get passed a &squot;sub-signal&squot; code&n; * for certain signal types, which we document here.&n; */
DECL|macro|SIGHUP
mdefine_line|#define SIGHUP&t;&t; 1
DECL|macro|SIGINT
mdefine_line|#define SIGINT&t;&t; 2
DECL|macro|SIGQUIT
mdefine_line|#define SIGQUIT&t;&t; 3
DECL|macro|SIGILL
mdefine_line|#define SIGILL&t;&t; 4
DECL|macro|SUBSIG_STACK
mdefine_line|#define    SUBSIG_STACK       0
DECL|macro|SUBSIG_ILLINST
mdefine_line|#define    SUBSIG_ILLINST     2
DECL|macro|SUBSIG_PRIVINST
mdefine_line|#define    SUBSIG_PRIVINST    3
DECL|macro|SUBSIG_BADTRAP
mdefine_line|#define    SUBSIG_BADTRAP(t)  (0x80 + (t))
DECL|macro|SIGTRAP
mdefine_line|#define SIGTRAP&t;&t; 5
DECL|macro|SIGABRT
mdefine_line|#define SIGABRT&t;&t; 6
DECL|macro|SIGIOT
mdefine_line|#define SIGIOT&t;&t; 6
DECL|macro|SIGEMT
mdefine_line|#define SIGEMT           7
DECL|macro|SUBSIG_TAG
mdefine_line|#define    SUBSIG_TAG    10
DECL|macro|SIGFPE
mdefine_line|#define SIGFPE&t;&t; 8
DECL|macro|SUBSIG_FPDISABLED
mdefine_line|#define    SUBSIG_FPDISABLED     0x400
DECL|macro|SUBSIG_FPERROR
mdefine_line|#define    SUBSIG_FPERROR        0x404
DECL|macro|SUBSIG_FPINTOVFL
mdefine_line|#define    SUBSIG_FPINTOVFL      0x001
DECL|macro|SUBSIG_FPSTSIG
mdefine_line|#define    SUBSIG_FPSTSIG        0x002
DECL|macro|SUBSIG_IDIVZERO
mdefine_line|#define    SUBSIG_IDIVZERO       0x014
DECL|macro|SUBSIG_FPINEXACT
mdefine_line|#define    SUBSIG_FPINEXACT      0x0c4
DECL|macro|SUBSIG_FPDIVZERO
mdefine_line|#define    SUBSIG_FPDIVZERO      0x0c8
DECL|macro|SUBSIG_FPUNFLOW
mdefine_line|#define    SUBSIG_FPUNFLOW       0x0cc
DECL|macro|SUBSIG_FPOPERROR
mdefine_line|#define    SUBSIG_FPOPERROR      0x0d0
DECL|macro|SUBSIG_FPOVFLOW
mdefine_line|#define    SUBSIG_FPOVFLOW       0x0d4
DECL|macro|SIGKILL
mdefine_line|#define SIGKILL&t;&t; 9
DECL|macro|SIGBUS
mdefine_line|#define SIGBUS          10
DECL|macro|SUBSIG_BUSTIMEOUT
mdefine_line|#define    SUBSIG_BUSTIMEOUT    1
DECL|macro|SUBSIG_ALIGNMENT
mdefine_line|#define    SUBSIG_ALIGNMENT     2
DECL|macro|SUBSIG_MISCERROR
mdefine_line|#define    SUBSIG_MISCERROR     5
DECL|macro|SIGSEGV
mdefine_line|#define SIGSEGV&t;&t;11
DECL|macro|SUBSIG_NOMAPPING
mdefine_line|#define    SUBSIG_NOMAPPING     3
DECL|macro|SUBSIG_PROTECTION
mdefine_line|#define    SUBSIG_PROTECTION    4
DECL|macro|SUBSIG_SEGERROR
mdefine_line|#define    SUBSIG_SEGERROR      5
DECL|macro|SIGSYS
mdefine_line|#define SIGSYS&t;&t;12
DECL|macro|SIGPIPE
mdefine_line|#define SIGPIPE&t;&t;13
DECL|macro|SIGALRM
mdefine_line|#define SIGALRM&t;&t;14
DECL|macro|SIGTERM
mdefine_line|#define SIGTERM&t;&t;15
DECL|macro|SIGURG
mdefine_line|#define SIGURG          16
multiline_comment|/* SunOS values which deviate from the Linux/i386 ones */
DECL|macro|SIGSTOP
mdefine_line|#define SIGSTOP&t;&t;17
DECL|macro|SIGTSTP
mdefine_line|#define SIGTSTP&t;&t;18
DECL|macro|SIGCONT
mdefine_line|#define SIGCONT&t;&t;19
DECL|macro|SIGCHLD
mdefine_line|#define SIGCHLD&t;&t;20
DECL|macro|SIGTTIN
mdefine_line|#define SIGTTIN&t;&t;21
DECL|macro|SIGTTOU
mdefine_line|#define SIGTTOU&t;&t;22
DECL|macro|SIGIO
mdefine_line|#define SIGIO&t;&t;23
DECL|macro|SIGPOLL
mdefine_line|#define SIGPOLL&t;&t;SIGIO   /* SysV name for SIGIO */
DECL|macro|SIGXCPU
mdefine_line|#define SIGXCPU&t;&t;24
DECL|macro|SIGXFSZ
mdefine_line|#define SIGXFSZ&t;&t;25
DECL|macro|SIGVTALRM
mdefine_line|#define SIGVTALRM&t;26
DECL|macro|SIGPROF
mdefine_line|#define SIGPROF&t;&t;27
DECL|macro|SIGWINCH
mdefine_line|#define SIGWINCH&t;28
DECL|macro|SIGLOST
mdefine_line|#define SIGLOST&t;&t;29
DECL|macro|SIGPWR
mdefine_line|#define SIGPWR&t;&t;SIGLOST
DECL|macro|SIGUSR1
mdefine_line|#define SIGUSR1&t;&t;30
DECL|macro|SIGUSR2
mdefine_line|#define SIGUSR2&t;&t;31
multiline_comment|/* Most things should be clean enough to redefine this at will, if care&n;   is taken to make libc match.  */
DECL|macro|__OLD_NSIG
mdefine_line|#define __OLD_NSIG&t;32
DECL|macro|__NEW_NSIG
mdefine_line|#define __NEW_NSIG      64
DECL|macro|_NSIG_BPW
mdefine_line|#define _NSIG_BPW     &t;64
DECL|macro|_NSIG_WORDS
mdefine_line|#define _NSIG_WORDS   &t;(__NEW_NSIG / _NSIG_BPW)
DECL|macro|SIGRTMIN
mdefine_line|#define SIGRTMIN       32
DECL|macro|SIGRTMAX
mdefine_line|#define SIGRTMAX       __NEW_NSIG
macro_line|#if defined(__KERNEL__) || defined(__WANT_POSIX1B_SIGNALS__)
DECL|macro|_NSIG
mdefine_line|#define _NSIG&t;&t;&t;__NEW_NSIG
DECL|macro|__new_sigset_t
mdefine_line|#define __new_sigset_t&t;&t;sigset_t
DECL|macro|__new_sigaction
mdefine_line|#define __new_sigaction&t;&t;sigaction
DECL|macro|__new_sigaction32
mdefine_line|#define __new_sigaction32&t;sigaction32
DECL|macro|__old_sigset_t
mdefine_line|#define __old_sigset_t&t;&t;old_sigset_t
DECL|macro|__old_sigaction
mdefine_line|#define __old_sigaction&t;&t;old_sigaction
DECL|macro|__old_sigaction32
mdefine_line|#define __old_sigaction32&t;old_sigaction32
macro_line|#else
DECL|macro|_NSIG
mdefine_line|#define _NSIG&t;&t;&t;__OLD_NSIG
DECL|macro|NSIG
mdefine_line|#define NSIG&t;&t;&t;_NSIG
DECL|macro|__old_sigset_t
mdefine_line|#define __old_sigset_t&t;&t;sigset_t
DECL|macro|__old_sigaction
mdefine_line|#define __old_sigaction&t;&t;sigaction
DECL|macro|__old_sigaction32
mdefine_line|#define __old_sigaction32&t;sigaction32
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|typedef|__old_sigset_t
r_typedef
r_int
r_int
id|__old_sigset_t
suffix:semicolon
multiline_comment|/* at least 32 bits */
r_typedef
r_struct
(brace
DECL|member|sig
r_int
r_int
id|sig
(braket
id|_NSIG_WORDS
)braket
suffix:semicolon
DECL|typedef|__new_sigset_t
)brace
id|__new_sigset_t
suffix:semicolon
multiline_comment|/* A SunOS sigstack */
DECL|struct|sigstack
r_struct
id|sigstack
(brace
multiline_comment|/* XXX 32-bit pointers pinhead XXX */
DECL|member|the_stack
r_char
op_star
id|the_stack
suffix:semicolon
DECL|member|cur_status
r_int
id|cur_status
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Sigvec flags */
DECL|macro|_SV_SSTACK
mdefine_line|#define _SV_SSTACK    1u    /* This signal handler should use sig-stack */
DECL|macro|_SV_INTR
mdefine_line|#define _SV_INTR      2u    /* Sig return should not restart system call */
DECL|macro|_SV_RESET
mdefine_line|#define _SV_RESET     4u    /* Set handler to SIG_DFL upon taken signal */
DECL|macro|_SV_IGNCHILD
mdefine_line|#define _SV_IGNCHILD  8u    /* Do not send SIGCHLD */
multiline_comment|/*&n; * sa_flags values: SA_STACK is not currently supported, but will allow the&n; * usage of signal stacks by using the (now obsolete) sa_restorer field in&n; * the sigaction structure as a stack pointer. This is now possible due to&n; * the changes in signal handling. LBT 010493.&n; * SA_INTERRUPT is a no-op, but left due to historical reasons. Use the&n; * SA_RESTART flag to get restarting signals (which were the default long ago)&n; * SA_SHIRQ flag is for shared interrupt support on PCI and EISA.&n; */
DECL|macro|SA_NOCLDSTOP
mdefine_line|#define SA_NOCLDSTOP&t;_SV_IGNCHILD
DECL|macro|SA_STACK
mdefine_line|#define SA_STACK&t;_SV_SSTACK
DECL|macro|SA_ONSTACK
mdefine_line|#define SA_ONSTACK&t;_SV_SSTACK
DECL|macro|SA_RESTART
mdefine_line|#define SA_RESTART&t;_SV_INTR
DECL|macro|SA_ONESHOT
mdefine_line|#define SA_ONESHOT&t;_SV_RESET
DECL|macro|SA_INTERRUPT
mdefine_line|#define SA_INTERRUPT&t;0x10u
DECL|macro|SA_NOMASK
mdefine_line|#define SA_NOMASK&t;0x20u
DECL|macro|SA_SHIRQ
mdefine_line|#define SA_SHIRQ&t;0x40u
DECL|macro|SA_NOCLDWAIT
mdefine_line|#define SA_NOCLDWAIT    0x100u
DECL|macro|SA_SIGINFO
mdefine_line|#define SA_SIGINFO      0x200u
DECL|macro|SIG_BLOCK
mdefine_line|#define SIG_BLOCK          0x01&t;/* for blocking signals */
DECL|macro|SIG_UNBLOCK
mdefine_line|#define SIG_UNBLOCK        0x02&t;/* for unblocking signals */
DECL|macro|SIG_SETMASK
mdefine_line|#define SIG_SETMASK        0x04&t;/* for setting the signal mask */
multiline_comment|/* &n; * sigaltstack controls&n; */
DECL|macro|SS_ONSTACK
mdefine_line|#define SS_ONSTACK&t;1
DECL|macro|SS_DISABLE
mdefine_line|#define SS_DISABLE&t;2
DECL|macro|MINSIGSTKSZ
mdefine_line|#define MINSIGSTKSZ&t;4096
DECL|macro|SIGSTKSZ
mdefine_line|#define SIGSTKSZ&t;16384
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * These values of sa_flags are used only by the kernel as part of the&n; * irq handling routines.&n; *&n; * SA_INTERRUPT is also used by the irq handling routines.&n; *&n; * DJHR&n; * SA_STATIC_ALLOC is used for the SPARC system to indicate that this&n; * interrupt handler&squot;s irq structure should be statically allocated&n; * by the request_irq routine.&n; * The alternative is that arch/sparc/kernel/irq.c has carnal knowledge&n; * of interrupt usage and that sucks. Also without a flag like this&n; * it may be possible for the free_irq routine to attempt to free&n; * statically allocated data.. which is NOT GOOD.&n; *&n; */
DECL|macro|SA_PROBE
mdefine_line|#define SA_PROBE SA_ONESHOT
DECL|macro|SA_SAMPLE_RANDOM
mdefine_line|#define SA_SAMPLE_RANDOM SA_RESTART
DECL|macro|SA_STATIC_ALLOC
mdefine_line|#define SA_STATIC_ALLOC&t;&t;0x80
macro_line|#endif
multiline_comment|/* Type of a signal handler.  */
macro_line|#ifdef __KERNEL__
DECL|typedef|__signalfn_t
r_typedef
r_void
id|__signalfn_t
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|typedef|__sighandler_t
r_typedef
id|__signalfn_t
id|__user
op_star
id|__sighandler_t
suffix:semicolon
DECL|typedef|__restorefn_t
r_typedef
r_void
id|__restorefn_t
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|__sigrestore_t
r_typedef
id|__restorefn_t
id|__user
op_star
id|__sigrestore_t
suffix:semicolon
macro_line|#else
DECL|typedef|__sighandler_t
r_typedef
r_void
(paren
op_star
id|__sighandler_t
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|typedef|__sigrestore_t
r_typedef
r_void
(paren
op_star
id|__sigrestore_t
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|SIG_DFL
mdefine_line|#define SIG_DFL&t;((__sighandler_t)0)&t;/* default signal handling */
DECL|macro|SIG_IGN
mdefine_line|#define SIG_IGN&t;((__sighandler_t)1)&t;/* ignore signal */
DECL|macro|SIG_ERR
mdefine_line|#define SIG_ERR&t;((__sighandler_t)-1)&t;/* error return from signal */
DECL|struct|__new_sigaction
r_struct
id|__new_sigaction
(brace
DECL|member|sa_handler
id|__sighandler_t
id|sa_handler
suffix:semicolon
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
id|__sigrestore_t
id|sa_restorer
suffix:semicolon
multiline_comment|/* not used by Linux/SPARC yet */
DECL|member|sa_mask
id|__new_sigset_t
id|sa_mask
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_COMPAT
DECL|struct|__new_sigaction32
r_struct
id|__new_sigaction32
(brace
DECL|member|sa_handler
r_int
id|sa_handler
suffix:semicolon
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_int
id|sa_restorer
suffix:semicolon
multiline_comment|/* not used by Linux/SPARC yet */
DECL|member|sa_mask
id|compat_sigset_t
id|sa_mask
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|struct|k_sigaction
r_struct
id|k_sigaction
(brace
DECL|member|sa
r_struct
id|__new_sigaction
id|sa
suffix:semicolon
DECL|member|ka_restorer
r_void
id|__user
op_star
id|ka_restorer
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|struct|__old_sigaction
r_struct
id|__old_sigaction
(brace
DECL|member|sa_handler
id|__sighandler_t
id|sa_handler
suffix:semicolon
DECL|member|sa_mask
id|__old_sigset_t
id|sa_mask
suffix:semicolon
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_void
(paren
op_star
id|sa_restorer
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* not used by Linux/SPARC yet */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_COMPAT
DECL|struct|__old_sigaction32
r_struct
id|__old_sigaction32
(brace
DECL|member|sa_handler
r_int
id|sa_handler
suffix:semicolon
DECL|member|sa_mask
id|compat_old_sigset_t
id|sa_mask
suffix:semicolon
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_int
id|sa_restorer
suffix:semicolon
multiline_comment|/* not used by Linux/SPARC yet */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|struct|sigaltstack
r_typedef
r_struct
id|sigaltstack
(brace
DECL|member|ss_sp
r_void
id|__user
op_star
id|ss_sp
suffix:semicolon
DECL|member|ss_flags
r_int
id|ss_flags
suffix:semicolon
DECL|member|ss_size
r_int
id|ss_size
suffix:semicolon
DECL|typedef|stack_t
)brace
id|stack_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_COMPAT
DECL|struct|sigaltstack32
r_typedef
r_struct
id|sigaltstack32
(brace
DECL|member|ss_sp
id|u32
id|ss_sp
suffix:semicolon
DECL|member|ss_flags
r_int
id|ss_flags
suffix:semicolon
DECL|member|ss_size
id|compat_size_t
id|ss_size
suffix:semicolon
DECL|typedef|stack_t32
)brace
id|stack_t32
suffix:semicolon
macro_line|#endif
DECL|struct|signal_deliver_cookie
r_struct
id|signal_deliver_cookie
(brace
DECL|member|restart_syscall
r_int
id|restart_syscall
suffix:semicolon
DECL|member|orig_i0
r_int
r_int
id|orig_i0
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_extern
r_void
id|ptrace_signal_deliver
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_void
op_star
id|cookie
)paren
suffix:semicolon
macro_line|#endif /* !(__KERNEL__) */
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(_ASMSPARC64_SIGNAL_H) */
eof
