macro_line|#ifndef _ASMx8664_SIGNAL_H
DECL|macro|_ASMx8664_SIGNAL_H
mdefine_line|#define _ASMx8664_SIGNAL_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/* Avoid too many header ordering problems.  */
r_struct
id|siginfo
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Most things should be clean enough to redefine this at will, if care&n;   is taken to make libc match.  */
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
r_struct
id|pt_regs
suffix:semicolon
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
DECL|macro|SIGIOT
mdefine_line|#define SIGIOT&t;&t; 6
DECL|macro|SIGBUS
mdefine_line|#define SIGBUS&t;&t; 7
DECL|macro|SIGFPE
mdefine_line|#define SIGFPE&t;&t; 8
DECL|macro|SIGKILL
mdefine_line|#define SIGKILL&t;&t; 9
DECL|macro|SIGUSR1
mdefine_line|#define SIGUSR1&t;&t;10
DECL|macro|SIGSEGV
mdefine_line|#define SIGSEGV&t;&t;11
DECL|macro|SIGUSR2
mdefine_line|#define SIGUSR2&t;&t;12
DECL|macro|SIGPIPE
mdefine_line|#define SIGPIPE&t;&t;13
DECL|macro|SIGALRM
mdefine_line|#define SIGALRM&t;&t;14
DECL|macro|SIGTERM
mdefine_line|#define SIGTERM&t;&t;15
DECL|macro|SIGSTKFLT
mdefine_line|#define SIGSTKFLT&t;16
DECL|macro|SIGCHLD
mdefine_line|#define SIGCHLD&t;&t;17
DECL|macro|SIGCONT
mdefine_line|#define SIGCONT&t;&t;18
DECL|macro|SIGSTOP
mdefine_line|#define SIGSTOP&t;&t;19
DECL|macro|SIGTSTP
mdefine_line|#define SIGTSTP&t;&t;20
DECL|macro|SIGTTIN
mdefine_line|#define SIGTTIN&t;&t;21
DECL|macro|SIGTTOU
mdefine_line|#define SIGTTOU&t;&t;22
DECL|macro|SIGURG
mdefine_line|#define SIGURG&t;&t;23
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
DECL|macro|SIGIO
mdefine_line|#define SIGIO&t;&t;29
DECL|macro|SIGPOLL
mdefine_line|#define SIGPOLL&t;&t;SIGIO
multiline_comment|/*&n;#define SIGLOST&t;&t;29&n;*/
DECL|macro|SIGPWR
mdefine_line|#define SIGPWR&t;&t;30
DECL|macro|SIGSYS
mdefine_line|#define SIGSYS&t;&t;31
DECL|macro|SIGUNUSED
mdefine_line|#define&t;SIGUNUSED&t;31
multiline_comment|/* These should not be considered constants from userland.  */
DECL|macro|SIGRTMIN
mdefine_line|#define SIGRTMIN&t;32
DECL|macro|SIGRTMAX
mdefine_line|#define SIGRTMAX&t;(_NSIG-1)
multiline_comment|/*&n; * SA_FLAGS values:&n; *&n; * SA_ONSTACK indicates that a registered stack_t will be used.&n; * SA_INTERRUPT is a no-op, but left due to historical reasons. Use the&n; * SA_RESTART flag to get restarting signals (which were the default long ago)&n; * SA_NOCLDSTOP flag to turn off SIGCHLD when children stop.&n; * SA_RESETHAND clears the handler when the signal is delivered.&n; * SA_NOCLDWAIT flag on SIGCHLD to inhibit zombies.&n; * SA_NODEFER prevents the current signal from being masked in the handler.&n; *&n; * SA_ONESHOT and SA_NOMASK are the historical Linux names for the Single&n; * Unix names RESETHAND and NODEFER respectively.&n; */
DECL|macro|SA_NOCLDSTOP
mdefine_line|#define SA_NOCLDSTOP&t;0x00000001
DECL|macro|SA_NOCLDWAIT
mdefine_line|#define SA_NOCLDWAIT&t;0x00000002 /* not supported yet */
DECL|macro|SA_SIGINFO
mdefine_line|#define SA_SIGINFO&t;0x00000004
DECL|macro|SA_ONSTACK
mdefine_line|#define SA_ONSTACK&t;0x08000000
DECL|macro|SA_RESTART
mdefine_line|#define SA_RESTART&t;0x10000000
DECL|macro|SA_NODEFER
mdefine_line|#define SA_NODEFER&t;0x40000000
DECL|macro|SA_RESETHAND
mdefine_line|#define SA_RESETHAND&t;0x80000000
DECL|macro|SA_NOMASK
mdefine_line|#define SA_NOMASK&t;SA_NODEFER
DECL|macro|SA_ONESHOT
mdefine_line|#define SA_ONESHOT&t;SA_RESETHAND
DECL|macro|SA_INTERRUPT
mdefine_line|#define SA_INTERRUPT&t;0x20000000 /* dummy -- ignored */
DECL|macro|SA_RESTORER
mdefine_line|#define SA_RESTORER&t;0x04000000
multiline_comment|/*&n; * sigaltstack controls&n; */
DECL|macro|SS_ONSTACK
mdefine_line|#define SS_ONSTACK&t;1
DECL|macro|SS_DISABLE
mdefine_line|#define SS_DISABLE&t;2
DECL|macro|MINSIGSTKSZ
mdefine_line|#define MINSIGSTKSZ&t;2048
DECL|macro|SIGSTKSZ
mdefine_line|#define SIGSTKSZ&t;8192
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * These values of sa_flags are used only by the kernel as part of the&n; * irq handling routines.&n; *&n; * SA_INTERRUPT is also used by the irq handling routines.&n; * SA_SHIRQ is for shared interrupt support on PCI and EISA.&n; */
DECL|macro|SA_PROBE
mdefine_line|#define SA_PROBE&t;&t;SA_ONESHOT
DECL|macro|SA_SAMPLE_RANDOM
mdefine_line|#define SA_SAMPLE_RANDOM&t;SA_RESTART
DECL|macro|SA_SHIRQ
mdefine_line|#define SA_SHIRQ&t;&t;0x04000000
macro_line|#endif
DECL|macro|SIG_BLOCK
mdefine_line|#define SIG_BLOCK          0&t;/* for blocking signals */
DECL|macro|SIG_UNBLOCK
mdefine_line|#define SIG_UNBLOCK        1&t;/* for unblocking signals */
DECL|macro|SIG_SETMASK
mdefine_line|#define SIG_SETMASK        2&t;/* for setting the signal mask */
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
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/sigcontext.h&gt;
DECL|macro|__HAVE_ARCH_SIG_BITOPS
macro_line|#undef __HAVE_ARCH_SIG_BITOPS
macro_line|#if 0
r_extern
id|__inline__
r_void
id|sigaddset
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
id|_sig
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;btsq %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|set
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|_sig
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
id|sigdelset
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
id|_sig
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;btrq %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|set
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|_sig
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
id|__const_sigismember
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
id|_sig
)paren
(brace
r_int
r_int
id|sig
op_assign
id|_sig
op_minus
l_int|1
suffix:semicolon
r_return
l_int|1
op_amp
(paren
id|set-&gt;sig
(braket
id|sig
op_div
id|_NSIG_BPW
)braket
op_rshift
(paren
id|sig
op_amp
op_complement
(paren
id|_NSIG_BPW
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
id|__gen_sigismember
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
id|_sig
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;btq %2,%1&bslash;n&bslash;tsbbq %0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|set
)paren
comma
l_string|&quot;Ir&quot;
(paren
id|_sig
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
mdefine_line|#define sigismember(set,sig)&t;&t;&t;&bslash;&n;&t;(__builtin_constant_p(sig) ?&t;&t;&bslash;&n;&t; __const_sigismember((set),(sig)) :&t;&bslash;&n;&t; __gen_sigismember((set),(sig)))
mdefine_line|#define sigmask(sig)&t;(1UL &lt;&lt; ((sig) - 1))
r_extern
id|__inline__
r_int
id|sigfindinword
c_func
(paren
r_int
r_int
id|word
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;bsfq %1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;rm&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|word
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
