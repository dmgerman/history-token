macro_line|#ifndef _ASMAXP_SIGNAL_H
DECL|macro|_ASMAXP_SIGNAL_H
mdefine_line|#define _ASMAXP_SIGNAL_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* Avoid too many header ordering problems.  */
r_struct
id|siginfo
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Digital Unix defines 64 signals.  Most things should be clean enough&n;   to redefine this at will, if care is taken to make libc match.  */
DECL|macro|_NSIG
mdefine_line|#define _NSIG&t;&t;64
DECL|macro|_NSIG_BPW
mdefine_line|#define _NSIG_BPW&t;64
DECL|macro|_NSIG_WORDS
mdefine_line|#define _NSIG_WORDS&t;(_NSIG / _NSIG_BPW)
DECL|typedef|old_sigset_t
r_typedef
r_int
r_int
id|old_sigset_t
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
DECL|typedef|sigset_t
)brace
id|sigset_t
suffix:semicolon
macro_line|#else
multiline_comment|/* Here we must cater to libcs that poke about in kernel headers.  */
DECL|macro|NSIG
mdefine_line|#define NSIG&t;&t;32
DECL|typedef|sigset_t
r_typedef
r_int
r_int
id|sigset_t
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Linux/AXP has different signal numbers that Linux/i386: I&squot;m trying&n; * to make it OSF/1 binary compatible, at least for normal binaries.&n; */
DECL|macro|SIGHUP
mdefine_line|#define SIGHUP&t;&t; 1
DECL|macro|SIGINT
mdefine_line|#define SIGINT&t;&t; 2
DECL|macro|SIGQUIT
mdefine_line|#define SIGQUIT&t;&t; 3
DECL|macro|SIGILL
mdefine_line|#define SIGILL&t;&t; 4
DECL|macro|SIGTRAP
mdefine_line|#define SIGTRAP&t;&t; 5
DECL|macro|SIGABRT
mdefine_line|#define SIGABRT&t;&t; 6
DECL|macro|SIGEMT
mdefine_line|#define SIGEMT&t;&t; 7
DECL|macro|SIGFPE
mdefine_line|#define SIGFPE&t;&t; 8
DECL|macro|SIGKILL
mdefine_line|#define SIGKILL&t;&t; 9
DECL|macro|SIGBUS
mdefine_line|#define SIGBUS&t;&t;10
DECL|macro|SIGSEGV
mdefine_line|#define SIGSEGV&t;&t;11
DECL|macro|SIGSYS
mdefine_line|#define SIGSYS&t;&t;12
DECL|macro|SIGPIPE
mdefine_line|#define SIGPIPE&t;&t;13
DECL|macro|SIGALRM
mdefine_line|#define SIGALRM&t;&t;14
DECL|macro|SIGTERM
mdefine_line|#define SIGTERM&t;&t;15
DECL|macro|SIGURG
mdefine_line|#define SIGURG&t;&t;16
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
DECL|macro|SIGINFO
mdefine_line|#define SIGINFO&t;&t;29
DECL|macro|SIGUSR1
mdefine_line|#define SIGUSR1&t;&t;30
DECL|macro|SIGUSR2
mdefine_line|#define SIGUSR2&t;&t;31
DECL|macro|SIGPOLL
mdefine_line|#define SIGPOLL&t;SIGIO
DECL|macro|SIGPWR
mdefine_line|#define SIGPWR&t;SIGINFO
DECL|macro|SIGIOT
mdefine_line|#define SIGIOT&t;SIGABRT
multiline_comment|/* These should not be considered constants from userland.  */
DECL|macro|SIGRTMIN
mdefine_line|#define SIGRTMIN&t;32
DECL|macro|SIGRTMAX
mdefine_line|#define SIGRTMAX&t;(_NSIG-1)
multiline_comment|/*&n; * SA_FLAGS values:&n; *&n; * SA_ONSTACK indicates that a registered stack_t will be used.&n; * SA_INTERRUPT is a no-op, but left due to historical reasons. Use the&n; * SA_RESTART flag to get restarting signals (which were the default long ago)&n; * SA_NOCLDSTOP flag to turn off SIGCHLD when children stop.&n; * SA_RESETHAND clears the handler when the signal is delivered.&n; * SA_NOCLDWAIT flag on SIGCHLD to inhibit zombies.&n; * SA_NODEFER prevents the current signal from being masked in the handler.&n; *&n; * SA_ONESHOT and SA_NOMASK are the historical Linux names for the Single&n; * Unix names RESETHAND and NODEFER respectively.&n; */
DECL|macro|SA_ONSTACK
mdefine_line|#define SA_ONSTACK&t;0x00000001
DECL|macro|SA_RESTART
mdefine_line|#define SA_RESTART&t;0x00000002
DECL|macro|SA_NOCLDSTOP
mdefine_line|#define SA_NOCLDSTOP&t;0x00000004
DECL|macro|SA_NODEFER
mdefine_line|#define SA_NODEFER&t;0x00000008
DECL|macro|SA_RESETHAND
mdefine_line|#define SA_RESETHAND&t;0x00000010
DECL|macro|SA_NOCLDWAIT
mdefine_line|#define SA_NOCLDWAIT&t;0x00000020 /* not supported yet */
DECL|macro|SA_SIGINFO
mdefine_line|#define SA_SIGINFO&t;0x00000040
DECL|macro|SA_ONESHOT
mdefine_line|#define SA_ONESHOT&t;SA_RESETHAND
DECL|macro|SA_NOMASK
mdefine_line|#define SA_NOMASK&t;SA_NODEFER
DECL|macro|SA_INTERRUPT
mdefine_line|#define SA_INTERRUPT&t;0x20000000 /* dummy -- ignored */
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
multiline_comment|/*&n; * These values of sa_flags are used only by the kernel as part of the&n; * irq handling routines.&n; *&n; * SA_INTERRUPT is also used by the irq handling routines.&n; * SA_SHIRQ is for shared interrupt support on PCI and EISA.&n; */
DECL|macro|SA_PROBE
mdefine_line|#define SA_PROBE&t;&t;SA_ONESHOT
DECL|macro|SA_SAMPLE_RANDOM
mdefine_line|#define SA_SAMPLE_RANDOM&t;SA_RESTART
DECL|macro|SA_SHIRQ
mdefine_line|#define SA_SHIRQ&t;&t;0x40000000
macro_line|#endif
DECL|macro|SIG_BLOCK
mdefine_line|#define SIG_BLOCK          1&t;/* for blocking signals */
DECL|macro|SIG_UNBLOCK
mdefine_line|#define SIG_UNBLOCK        2&t;/* for unblocking signals */
DECL|macro|SIG_SETMASK
mdefine_line|#define SIG_SETMASK        3&t;/* for setting the signal mask */
multiline_comment|/* Type of a signal handler.  */
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
DECL|macro|SIG_DFL
mdefine_line|#define SIG_DFL&t;((__sighandler_t)0)&t;/* default signal handling */
DECL|macro|SIG_IGN
mdefine_line|#define SIG_IGN&t;((__sighandler_t)1)&t;/* ignore signal */
DECL|macro|SIG_ERR
mdefine_line|#define SIG_ERR&t;((__sighandler_t)-1)&t;/* error return from signal */
macro_line|#ifdef __KERNEL__
DECL|struct|osf_sigaction
r_struct
id|osf_sigaction
(brace
DECL|member|sa_handler
id|__sighandler_t
id|sa_handler
suffix:semicolon
DECL|member|sa_mask
id|old_sigset_t
id|sa_mask
suffix:semicolon
DECL|member|sa_flags
r_int
id|sa_flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sigaction
r_struct
id|sigaction
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
DECL|member|sa_mask
id|sigset_t
id|sa_mask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
DECL|struct|k_sigaction
r_struct
id|k_sigaction
(brace
DECL|member|sa
r_struct
id|sigaction
id|sa
suffix:semicolon
DECL|member|ka_restorer
r_void
(paren
op_star
id|ka_restorer
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else
multiline_comment|/* Here we must cater to libcs that poke about in kernel headers.  */
DECL|struct|sigaction
r_struct
id|sigaction
(brace
r_union
(brace
DECL|member|_sa_handler
id|__sighandler_t
id|_sa_handler
suffix:semicolon
DECL|member|_sa_sigaction
r_void
(paren
op_star
id|_sa_sigaction
)paren
(paren
r_int
comma
r_struct
id|siginfo
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|_u
)brace
id|_u
suffix:semicolon
DECL|member|sa_mask
id|sigset_t
id|sa_mask
suffix:semicolon
DECL|member|sa_flags
r_int
id|sa_flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|sa_handler
mdefine_line|#define sa_handler&t;_u._sa_handler
DECL|macro|sa_sigaction
mdefine_line|#define sa_sigaction&t;_u._sa_sigaction
macro_line|#endif /* __KERNEL__ */
DECL|struct|sigaltstack
r_typedef
r_struct
id|sigaltstack
(brace
DECL|member|ss_sp
r_void
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
multiline_comment|/* sigstack(2) is deprecated, and will be withdrawn in a future version&n;   of the X/Open CAE Specification.  Use sigaltstack instead.  It is only&n;   implemented here for OSF/1 compatibility.  */
DECL|struct|sigstack
r_struct
id|sigstack
(brace
DECL|member|ss_sp
r_void
op_star
id|ss_sp
suffix:semicolon
DECL|member|ss_onstack
r_int
id|ss_onstack
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/sigcontext.h&gt;
DECL|macro|HAVE_ARCH_GET_SIGNAL_TO_DELIVER
mdefine_line|#define HAVE_ARCH_GET_SIGNAL_TO_DELIVER
macro_line|#endif
macro_line|#endif
eof
