multiline_comment|/*&n; *  include/asm-s390/signal.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/signal.h&quot;&n; */
macro_line|#ifndef _ASMS390_SIGNAL_H
DECL|macro|_ASMS390_SIGNAL_H
mdefine_line|#define _ASMS390_SIGNAL_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* Avoid too many header ordering problems.  */
r_struct
id|siginfo
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Most things should be clean enough to redefine this at will, if care&n;   is taken to make libc match.  */
macro_line|#include &lt;asm/sigcontext.h&gt;
DECL|macro|_NSIG
mdefine_line|#define _NSIG           _SIGCONTEXT_NSIG
DECL|macro|_NSIG_BPW
mdefine_line|#define _NSIG_BPW       _SIGCONTEXT_NSIG_BPW
DECL|macro|_NSIG_WORDS
mdefine_line|#define _NSIG_WORDS     _SIGCONTEXT_NSIG_WORDS
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
mdefine_line|#define NSIG            32
DECL|typedef|sigset_t
r_typedef
r_int
r_int
id|sigset_t
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
DECL|macro|SIGHUP
mdefine_line|#define SIGHUP           1
DECL|macro|SIGINT
mdefine_line|#define SIGINT           2
DECL|macro|SIGQUIT
mdefine_line|#define SIGQUIT          3
DECL|macro|SIGILL
mdefine_line|#define SIGILL           4
DECL|macro|SIGTRAP
mdefine_line|#define SIGTRAP          5
DECL|macro|SIGABRT
mdefine_line|#define SIGABRT          6
DECL|macro|SIGIOT
mdefine_line|#define SIGIOT           6
DECL|macro|SIGBUS
mdefine_line|#define SIGBUS           7
DECL|macro|SIGFPE
mdefine_line|#define SIGFPE           8
DECL|macro|SIGKILL
mdefine_line|#define SIGKILL          9
DECL|macro|SIGUSR1
mdefine_line|#define SIGUSR1         10
DECL|macro|SIGSEGV
mdefine_line|#define SIGSEGV         11
DECL|macro|SIGUSR2
mdefine_line|#define SIGUSR2         12
DECL|macro|SIGPIPE
mdefine_line|#define SIGPIPE         13
DECL|macro|SIGALRM
mdefine_line|#define SIGALRM         14
DECL|macro|SIGTERM
mdefine_line|#define SIGTERM         15
DECL|macro|SIGSTKFLT
mdefine_line|#define SIGSTKFLT       16
DECL|macro|SIGCHLD
mdefine_line|#define SIGCHLD         17
DECL|macro|SIGCONT
mdefine_line|#define SIGCONT         18
DECL|macro|SIGSTOP
mdefine_line|#define SIGSTOP         19
DECL|macro|SIGTSTP
mdefine_line|#define SIGTSTP         20
DECL|macro|SIGTTIN
mdefine_line|#define SIGTTIN         21
DECL|macro|SIGTTOU
mdefine_line|#define SIGTTOU         22
DECL|macro|SIGURG
mdefine_line|#define SIGURG          23
DECL|macro|SIGXCPU
mdefine_line|#define SIGXCPU         24
DECL|macro|SIGXFSZ
mdefine_line|#define SIGXFSZ         25
DECL|macro|SIGVTALRM
mdefine_line|#define SIGVTALRM       26
DECL|macro|SIGPROF
mdefine_line|#define SIGPROF         27
DECL|macro|SIGWINCH
mdefine_line|#define SIGWINCH        28
DECL|macro|SIGIO
mdefine_line|#define SIGIO           29
DECL|macro|SIGPOLL
mdefine_line|#define SIGPOLL         SIGIO
multiline_comment|/*&n;#define SIGLOST         29&n;*/
DECL|macro|SIGPWR
mdefine_line|#define SIGPWR          30
DECL|macro|SIGSYS
mdefine_line|#define SIGSYS&t;&t;31
DECL|macro|SIGUNUSED
mdefine_line|#define SIGUNUSED       31
multiline_comment|/* These should not be considered constants from userland.  */
DECL|macro|SIGRTMIN
mdefine_line|#define SIGRTMIN        32
DECL|macro|SIGRTMAX
mdefine_line|#define SIGRTMAX        (_NSIG-1)
multiline_comment|/*&n; * SA_FLAGS values:&n; *&n; * SA_ONSTACK indicates that a registered stack_t will be used.&n; * SA_INTERRUPT is a no-op, but left due to historical reasons. Use the&n; * SA_RESTART flag to get restarting signals (which were the default long ago)&n; * SA_NOCLDSTOP flag to turn off SIGCHLD when children stop.&n; * SA_RESETHAND clears the handler when the signal is delivered.&n; * SA_NOCLDWAIT flag on SIGCHLD to inhibit zombies.&n; * SA_NODEFER prevents the current signal from being masked in the handler.&n; *&n; * SA_ONESHOT and SA_NOMASK are the historical Linux names for the Single&n; * Unix names RESETHAND and NODEFER respectively.&n; */
DECL|macro|SA_NOCLDSTOP
mdefine_line|#define SA_NOCLDSTOP    0x00000001
DECL|macro|SA_NOCLDWAIT
mdefine_line|#define SA_NOCLDWAIT    0x00000002 /* not supported yet */
DECL|macro|SA_SIGINFO
mdefine_line|#define SA_SIGINFO      0x00000004
DECL|macro|SA_ONSTACK
mdefine_line|#define SA_ONSTACK      0x08000000
DECL|macro|SA_RESTART
mdefine_line|#define SA_RESTART      0x10000000
DECL|macro|SA_NODEFER
mdefine_line|#define SA_NODEFER      0x40000000
DECL|macro|SA_RESETHAND
mdefine_line|#define SA_RESETHAND    0x80000000
DECL|macro|SA_NOMASK
mdefine_line|#define SA_NOMASK       SA_NODEFER
DECL|macro|SA_ONESHOT
mdefine_line|#define SA_ONESHOT      SA_RESETHAND
DECL|macro|SA_INTERRUPT
mdefine_line|#define SA_INTERRUPT    0x20000000 /* dummy -- ignored */
DECL|macro|SA_RESTORER
mdefine_line|#define SA_RESTORER     0x04000000
multiline_comment|/*&n; * sigaltstack controls&n; */
DECL|macro|SS_ONSTACK
mdefine_line|#define SS_ONSTACK      1
DECL|macro|SS_DISABLE
mdefine_line|#define SS_DISABLE      2
DECL|macro|MINSIGSTKSZ
mdefine_line|#define MINSIGSTKSZ     2048
DECL|macro|SIGSTKSZ
mdefine_line|#define SIGSTKSZ        8192
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * These values of sa_flags are used only by the kernel as part of the&n; * irq handling routines.&n; *&n; * SA_INTERRUPT is also used by the irq handling routines.&n; * SA_SHIRQ is for shared interrupt support on PCI and EISA.&n; */
DECL|macro|SA_PROBE
mdefine_line|#define SA_PROBE                SA_ONESHOT
DECL|macro|SA_SAMPLE_RANDOM
mdefine_line|#define SA_SAMPLE_RANDOM        SA_RESTART
DECL|macro|SA_SHIRQ
mdefine_line|#define SA_SHIRQ                0x04000000
macro_line|#endif
DECL|macro|SIG_BLOCK
mdefine_line|#define SIG_BLOCK          0    /* for blocking signals */
DECL|macro|SIG_UNBLOCK
mdefine_line|#define SIG_UNBLOCK        1    /* for unblocking signals */
DECL|macro|SIG_SETMASK
mdefine_line|#define SIG_SETMASK        2    /* for setting the signal mask */
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
mdefine_line|#define SIG_DFL ((__sighandler_t)0)     /* default signal handling */
DECL|macro|SIG_IGN
mdefine_line|#define SIG_IGN ((__sighandler_t)1)     /* ignore signal */
DECL|macro|SIG_ERR
mdefine_line|#define SIG_ERR ((__sighandler_t)-1)    /* error return from signal */
macro_line|#ifdef __KERNEL__
DECL|struct|old_sigaction
r_struct
id|old_sigaction
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
)brace
suffix:semicolon
DECL|macro|sa_handler
mdefine_line|#define sa_handler      _u._sa_handler
DECL|macro|sa_sigaction
mdefine_line|#define sa_sigaction    _u._sa_sigaction
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
macro_line|#endif
eof
