multiline_comment|/* $Id: signal.h,v 1.6 1999/08/18 23:37:49 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 1997, 1998, 1999 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SIGNAL_H
DECL|macro|_ASM_SIGNAL_H
mdefine_line|#define _ASM_SIGNAL_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|_NSIG
mdefine_line|#define _NSIG&t;&t;128
DECL|macro|_NSIG_BPW
mdefine_line|#define _NSIG_BPW&t;32
DECL|macro|_NSIG_WORDS
mdefine_line|#define _NSIG_WORDS&t;(_NSIG / _NSIG_BPW)
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
DECL|typedef|old_sigset_t
r_typedef
r_int
r_int
id|old_sigset_t
suffix:semicolon
multiline_comment|/* at least 32 bits */
DECL|macro|SIGHUP
mdefine_line|#define SIGHUP&t;&t; 1&t;/* Hangup (POSIX).  */
DECL|macro|SIGINT
mdefine_line|#define SIGINT&t;&t; 2&t;/* Interrupt (ANSI).  */
DECL|macro|SIGQUIT
mdefine_line|#define SIGQUIT&t;&t; 3&t;/* Quit (POSIX).  */
DECL|macro|SIGILL
mdefine_line|#define SIGILL&t;&t; 4&t;/* Illegal instruction (ANSI).  */
DECL|macro|SIGTRAP
mdefine_line|#define SIGTRAP&t;&t; 5&t;/* Trace trap (POSIX).  */
DECL|macro|SIGIOT
mdefine_line|#define SIGIOT&t;&t; 6&t;/* IOT trap (4.2 BSD).  */
DECL|macro|SIGABRT
mdefine_line|#define SIGABRT&t;&t; SIGIOT&t;/* Abort (ANSI).  */
DECL|macro|SIGEMT
mdefine_line|#define SIGEMT&t;&t; 7
DECL|macro|SIGFPE
mdefine_line|#define SIGFPE&t;&t; 8&t;/* Floating-point exception (ANSI).  */
DECL|macro|SIGKILL
mdefine_line|#define SIGKILL&t;&t; 9&t;/* Kill, unblockable (POSIX).  */
DECL|macro|SIGBUS
mdefine_line|#define SIGBUS&t;&t;10&t;/* BUS error (4.2 BSD).  */
DECL|macro|SIGSEGV
mdefine_line|#define SIGSEGV&t;&t;11&t;/* Segmentation violation (ANSI).  */
DECL|macro|SIGSYS
mdefine_line|#define SIGSYS&t;&t;12
DECL|macro|SIGPIPE
mdefine_line|#define SIGPIPE&t;&t;13&t;/* Broken pipe (POSIX).  */
DECL|macro|SIGALRM
mdefine_line|#define SIGALRM&t;&t;14&t;/* Alarm clock (POSIX).  */
DECL|macro|SIGTERM
mdefine_line|#define SIGTERM&t;&t;15&t;/* Termination (ANSI).  */
DECL|macro|SIGUSR1
mdefine_line|#define SIGUSR1&t;&t;16&t;/* User-defined signal 1 (POSIX).  */
DECL|macro|SIGUSR2
mdefine_line|#define SIGUSR2&t;&t;17&t;/* User-defined signal 2 (POSIX).  */
DECL|macro|SIGCHLD
mdefine_line|#define SIGCHLD&t;&t;18&t;/* Child status has changed (POSIX).  */
DECL|macro|SIGCLD
mdefine_line|#define SIGCLD&t;&t;SIGCHLD&t;/* Same as SIGCHLD (System V).  */
DECL|macro|SIGPWR
mdefine_line|#define SIGPWR&t;&t;19&t;/* Power failure restart (System V).  */
DECL|macro|SIGWINCH
mdefine_line|#define SIGWINCH&t;20&t;/* Window size change (4.3 BSD, Sun).  */
DECL|macro|SIGURG
mdefine_line|#define SIGURG&t;&t;21&t;/* Urgent condition on socket (4.2 BSD).  */
DECL|macro|SIGIO
mdefine_line|#define SIGIO&t;&t;22&t;/* I/O now possible (4.2 BSD).  */
DECL|macro|SIGPOLL
mdefine_line|#define SIGPOLL&t;&t;SIGIO&t;/* Pollable event occurred (System V).  */
DECL|macro|SIGSTOP
mdefine_line|#define SIGSTOP&t;&t;23&t;/* Stop, unblockable (POSIX).  */
DECL|macro|SIGTSTP
mdefine_line|#define SIGTSTP&t;&t;24&t;/* Keyboard stop (POSIX).  */
DECL|macro|SIGCONT
mdefine_line|#define SIGCONT&t;&t;25&t;/* Continue (POSIX).  */
DECL|macro|SIGTTIN
mdefine_line|#define SIGTTIN&t;&t;26&t;/* Background read from tty (POSIX).  */
DECL|macro|SIGTTOU
mdefine_line|#define SIGTTOU&t;&t;27&t;/* Background write to tty (POSIX).  */
DECL|macro|SIGVTALRM
mdefine_line|#define SIGVTALRM&t;28&t;/* Virtual alarm clock (4.2 BSD).  */
DECL|macro|SIGPROF
mdefine_line|#define SIGPROF&t;&t;29&t;/* Profiling alarm clock (4.2 BSD).  */
DECL|macro|SIGXCPU
mdefine_line|#define SIGXCPU&t;&t;30&t;/* CPU limit exceeded (4.2 BSD).  */
DECL|macro|SIGXFSZ
mdefine_line|#define SIGXFSZ&t;&t;31&t;/* File size limit exceeded (4.2 BSD).  */
multiline_comment|/* These should not be considered constants from userland.  */
DECL|macro|SIGRTMIN
mdefine_line|#define SIGRTMIN&t;32
DECL|macro|SIGRTMAX
mdefine_line|#define SIGRTMAX&t;(_NSIG-1)
multiline_comment|/*&n; * SA_FLAGS values:&n; *&n; * SA_ONSTACK indicates that a registered stack_t will be used.&n; * SA_INTERRUPT is a no-op, but left due to historical reasons. Use the&n; * SA_RESTART flag to get restarting signals (which were the default long ago)&n; * SA_NOCLDSTOP flag to turn off SIGCHLD when children stop.&n; * SA_RESETHAND clears the handler when the signal is delivered.&n; * SA_NOCLDWAIT flag on SIGCHLD to inhibit zombies.&n; * SA_NODEFER prevents the current signal from being masked in the handler.&n; *&n; * SA_ONESHOT and SA_NOMASK are the historical Linux names for the Single&n; * Unix names RESETHAND and NODEFER respectively.&n; */
DECL|macro|SA_ONSTACK
mdefine_line|#define SA_ONSTACK&t;0x08000000
DECL|macro|SA_RESETHAND
mdefine_line|#define SA_RESETHAND&t;0x80000000
DECL|macro|SA_RESTART
mdefine_line|#define SA_RESTART&t;0x10000000
DECL|macro|SA_SIGINFO
mdefine_line|#define SA_SIGINFO&t;0x00000008
DECL|macro|SA_NODEFER
mdefine_line|#define SA_NODEFER&t;0x40000000
DECL|macro|SA_NOCLDWAIT
mdefine_line|#define SA_NOCLDWAIT&t;0x00010000&t;/* Not supported yet */
DECL|macro|SA_NOCLDSTOP
mdefine_line|#define SA_NOCLDSTOP&t;0x00000001
DECL|macro|SA_NOMASK
mdefine_line|#define SA_NOMASK&t;SA_NODEFER
DECL|macro|SA_ONESHOT
mdefine_line|#define SA_ONESHOT&t;SA_RESETHAND
DECL|macro|SA_INTERRUPT
mdefine_line|#define SA_INTERRUPT&t;0x20000000&t;/* dummy -- ignored */
DECL|macro|SA_RESTORER
mdefine_line|#define SA_RESTORER&t;0x04000000
multiline_comment|/* &n; * sigaltstack controls&n; */
DECL|macro|SS_ONSTACK
mdefine_line|#define SS_ONSTACK     1
DECL|macro|SS_DISABLE
mdefine_line|#define SS_DISABLE     2
DECL|macro|MINSIGSTKSZ
mdefine_line|#define MINSIGSTKSZ    2048
DECL|macro|SIGSTKSZ
mdefine_line|#define SIGSTKSZ       8192
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * These values of sa_flags are used only by the kernel as part of the&n; * irq handling routines.&n; *&n; * SA_INTERRUPT is also used by the irq handling routines.&n; * SA_SHIRQ flag is for shared interrupt support on PCI and EISA.&n; */
DECL|macro|SA_PROBE
mdefine_line|#define SA_PROBE&t;&t;SA_ONESHOT
DECL|macro|SA_SAMPLE_RANDOM
mdefine_line|#define SA_SAMPLE_RANDOM&t;SA_RESTART
DECL|macro|SA_SHIRQ
mdefine_line|#define SA_SHIRQ&t;&t;0x02000000
macro_line|#endif /* __KERNEL__ */
DECL|macro|SIG_BLOCK
mdefine_line|#define SIG_BLOCK&t;1&t;/* for blocking signals */
DECL|macro|SIG_UNBLOCK
mdefine_line|#define SIG_UNBLOCK&t;2&t;/* for unblocking signals */
DECL|macro|SIG_SETMASK
mdefine_line|#define SIG_SETMASK&t;3&t;/* for setting the signal mask */
DECL|macro|SIG_SETMASK32
mdefine_line|#define SIG_SETMASK32&t;256&t;/* Goodie from SGI for BSD compatibility:&n;&t;&t;&t;&t;   set only the low 32 bit of the sigset.  */
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
multiline_comment|/* Fake signal functions */
DECL|macro|SIG_DFL
mdefine_line|#define SIG_DFL&t;((__sighandler_t)0)&t;/* default signal handling */
DECL|macro|SIG_IGN
mdefine_line|#define SIG_IGN&t;((__sighandler_t)1)&t;/* ignore signal */
DECL|macro|SIG_ERR
mdefine_line|#define SIG_ERR&t;((__sighandler_t)-1)&t;/* error return from signal */
DECL|struct|sigaction
r_struct
id|sigaction
(brace
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_handler
id|__sighandler_t
id|sa_handler
suffix:semicolon
DECL|member|sa_mask
id|sigset_t
id|sa_mask
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
DECL|member|sa_resv
r_int
id|sa_resv
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* reserved */
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
multiline_comment|/* IRIX compatible stack_t  */
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
DECL|member|ss_size
r_int
id|ss_size
suffix:semicolon
DECL|member|ss_flags
r_int
id|ss_flags
suffix:semicolon
DECL|typedef|stack_t
)brace
id|stack_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/sigcontext.h&gt;
multiline_comment|/*&n; * The following break codes are or were in use for specific purposes in&n; * other MIPS operating systems.  Linux/MIPS doesn&squot;t use all of them.  The&n; * unused ones are here as placeholders; we might encounter them in&n; * non-Linux/MIPS object files or make use of them in the future.&n; */
DECL|macro|BRK_USERBP
mdefine_line|#define BRK_USERBP&t;0&t;/* User bp (used by debuggers) */
DECL|macro|BRK_KERNELBP
mdefine_line|#define BRK_KERNELBP&t;1&t;/* Break in the kernel */
DECL|macro|BRK_ABORT
mdefine_line|#define BRK_ABORT&t;2&t;/* Sometimes used by abort(3) to SIGIOT */
DECL|macro|BRK_BD_TAKEN
mdefine_line|#define BRK_BD_TAKEN&t;3&t;/* For bd slot emulation - not implemented */
DECL|macro|BRK_BD_NOTTAKEN
mdefine_line|#define BRK_BD_NOTTAKEN&t;4&t;/* For bd slot emulation - not implemented */
DECL|macro|BRK_SSTEPBP
mdefine_line|#define BRK_SSTEPBP&t;5&t;/* User bp (used by debuggers) */
DECL|macro|BRK_OVERFLOW
mdefine_line|#define BRK_OVERFLOW&t;6&t;/* Overflow check */
DECL|macro|BRK_DIVZERO
mdefine_line|#define BRK_DIVZERO&t;7&t;/* Divide by zero check */
DECL|macro|BRK_RANGE
mdefine_line|#define BRK_RANGE&t;8&t;/* Range error check */
DECL|macro|BRK_STACKOVERFLOW
mdefine_line|#define BRK_STACKOVERFLOW 9&t;/* For Ada stackchecking */
DECL|macro|BRK_NORLD
mdefine_line|#define BRK_NORLD&t;10&t;/* No rld found - not used by Linux/MIPS */
DECL|macro|_BRK_THREADBP
mdefine_line|#define _BRK_THREADBP&t;11&t;/* For threads, user bp (used by debuggers) */
DECL|macro|BRK_MULOVF
mdefine_line|#define BRK_MULOVF&t;1023&t;/* Multiply overflow */
macro_line|#endif /* defined (__KERNEL__) */
macro_line|#endif /* _ASM_SIGNAL_H */
eof
