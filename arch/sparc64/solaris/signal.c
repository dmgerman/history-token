multiline_comment|/* $Id: signal.c,v 1.7 2000/09/05 21:44:54 davem Exp $&n; * signal.c: Signal emulation for Solaris&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/svr4.h&gt;
macro_line|#include &lt;asm/string.h&gt;
macro_line|#include &quot;conv.h&quot;
macro_line|#include &quot;signal.h&quot;
DECL|macro|_S
mdefine_line|#define _S(nr) (1L&lt;&lt;((nr)-1))
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(_S(SIGKILL) | _S(SIGSTOP)))
DECL|variable|linux_to_solaris_signals
r_int
id|linux_to_solaris_signals
(braket
)braket
op_assign
(brace
l_int|0
comma
id|SOLARIS_SIGHUP
comma
id|SOLARIS_SIGINT
comma
id|SOLARIS_SIGQUIT
comma
id|SOLARIS_SIGILL
comma
id|SOLARIS_SIGTRAP
comma
id|SOLARIS_SIGIOT
comma
id|SOLARIS_SIGEMT
comma
id|SOLARIS_SIGFPE
comma
id|SOLARIS_SIGKILL
comma
id|SOLARIS_SIGBUS
comma
id|SOLARIS_SIGSEGV
comma
id|SOLARIS_SIGSYS
comma
id|SOLARIS_SIGPIPE
comma
id|SOLARIS_SIGALRM
comma
id|SOLARIS_SIGTERM
comma
id|SOLARIS_SIGURG
comma
id|SOLARIS_SIGSTOP
comma
id|SOLARIS_SIGTSTP
comma
id|SOLARIS_SIGCONT
comma
id|SOLARIS_SIGCLD
comma
id|SOLARIS_SIGTTIN
comma
id|SOLARIS_SIGTTOU
comma
id|SOLARIS_SIGPOLL
comma
id|SOLARIS_SIGXCPU
comma
id|SOLARIS_SIGXFSZ
comma
id|SOLARIS_SIGVTALRM
comma
id|SOLARIS_SIGPROF
comma
id|SOLARIS_SIGWINCH
comma
id|SOLARIS_SIGUSR1
comma
id|SOLARIS_SIGUSR1
comma
id|SOLARIS_SIGUSR2
comma
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|solaris_to_linux_signals
r_int
id|solaris_to_linux_signals
(braket
)braket
op_assign
(brace
l_int|0
comma
id|SIGHUP
comma
id|SIGINT
comma
id|SIGQUIT
comma
id|SIGILL
comma
id|SIGTRAP
comma
id|SIGIOT
comma
id|SIGEMT
comma
id|SIGFPE
comma
id|SIGKILL
comma
id|SIGBUS
comma
id|SIGSEGV
comma
id|SIGSYS
comma
id|SIGPIPE
comma
id|SIGALRM
comma
id|SIGTERM
comma
id|SIGUSR1
comma
id|SIGUSR2
comma
id|SIGCHLD
comma
op_minus
l_int|1
comma
id|SIGWINCH
comma
id|SIGURG
comma
id|SIGPOLL
comma
id|SIGSTOP
comma
id|SIGTSTP
comma
id|SIGCONT
comma
id|SIGTTIN
comma
id|SIGTTOU
comma
id|SIGVTALRM
comma
id|SIGPROF
comma
id|SIGXCPU
comma
id|SIGXFSZ
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|function|mapsig
r_static
r_inline
r_int
id|mapsig
c_func
(paren
r_int
id|sig
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|sig
OG
id|SOLARIS_NSIGNALS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|solaris_to_linux_signals
(braket
id|sig
)braket
suffix:semicolon
)brace
DECL|function|solaris_kill
id|asmlinkage
r_int
id|solaris_kill
c_func
(paren
r_int
id|pid
comma
r_int
id|sig
)paren
(brace
r_int
(paren
op_star
id|sys_kill
)paren
(paren
r_int
comma
r_int
)paren
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
r_int
comma
r_int
)paren
)paren
id|SYS
c_func
(paren
id|kill
)paren
suffix:semicolon
r_int
id|s
op_assign
id|mapsig
c_func
(paren
id|sig
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
OL
l_int|0
)paren
r_return
id|s
suffix:semicolon
r_return
id|sys_kill
c_func
(paren
id|pid
comma
id|s
)paren
suffix:semicolon
)brace
DECL|function|sig_handler
r_static
r_int
id|sig_handler
c_func
(paren
r_int
id|sig
comma
id|u32
id|arg
comma
r_int
id|one_shot
)paren
(brace
r_struct
id|sigaction
id|sa
comma
id|old
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_int
(paren
op_star
id|sys_sigaction
)paren
(paren
r_int
comma
r_struct
id|sigaction
op_star
comma
r_struct
id|sigaction
op_star
)paren
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
r_int
comma
r_struct
id|sigaction
op_star
comma
r_struct
id|sigaction
op_star
)paren
)paren
id|SYS
c_func
(paren
id|sigaction
)paren
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|sa.sa_mask
)paren
suffix:semicolon
id|sa.sa_restorer
op_assign
l_int|NULL
suffix:semicolon
id|sa.sa_handler
op_assign
(paren
id|__sighandler_t
)paren
id|A
c_func
(paren
id|arg
)paren
suffix:semicolon
id|sa.sa_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|one_shot
)paren
id|sa.sa_flags
op_assign
id|SA_ONESHOT
op_or
id|SA_NOMASK
suffix:semicolon
id|set_fs
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|ret
op_assign
id|sys_sigaction
c_func
(paren
id|sig
comma
op_amp
id|sa
comma
op_amp
id|old
)paren
suffix:semicolon
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
(paren
id|u32
)paren
(paren
r_int
)paren
id|old.sa_handler
suffix:semicolon
)brace
DECL|function|solaris_signal
r_static
r_inline
r_int
id|solaris_signal
c_func
(paren
r_int
id|sig
comma
id|u32
id|arg
)paren
(brace
r_return
id|sig_handler
(paren
id|sig
comma
id|arg
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|solaris_sigset
r_static
r_int
id|solaris_sigset
c_func
(paren
r_int
id|sig
comma
id|u32
id|arg
)paren
(brace
r_if
c_cond
(paren
id|arg
op_ne
l_int|2
)paren
multiline_comment|/* HOLD */
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|_S
c_func
(paren
id|sig
)paren
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
r_return
id|sig_handler
(paren
id|sig
comma
id|arg
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|sigaddsetmask
c_func
(paren
op_amp
id|current-&gt;blocked
comma
(paren
id|_S
c_func
(paren
id|sig
)paren
op_amp
op_complement
id|_BLOCKABLE
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|solaris_sighold
r_static
r_inline
r_int
id|solaris_sighold
c_func
(paren
r_int
id|sig
)paren
(brace
r_return
id|solaris_sigset
c_func
(paren
id|sig
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|solaris_sigrelse
r_static
r_inline
r_int
id|solaris_sigrelse
c_func
(paren
r_int
id|sig
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|_S
c_func
(paren
id|sig
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|solaris_sigignore
r_static
r_inline
r_int
id|solaris_sigignore
c_func
(paren
r_int
id|sig
)paren
(brace
r_return
id|sig_handler
(paren
id|sig
comma
(paren
id|u32
)paren
id|SIG_IGN
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|solaris_sigpause
r_static
r_inline
r_int
id|solaris_sigpause
c_func
(paren
r_int
id|sig
)paren
(brace
id|printk
(paren
l_string|&quot;Need to support solaris sigpause&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|solaris_sigfunc
id|asmlinkage
r_int
id|solaris_sigfunc
c_func
(paren
r_int
id|sig
comma
id|u32
id|arg
)paren
(brace
r_int
id|func
op_assign
id|sig
op_amp
op_complement
l_int|0xff
suffix:semicolon
id|sig
op_assign
id|mapsig
c_func
(paren
id|sig
op_amp
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
OL
l_int|0
)paren
r_return
id|sig
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
id|solaris_signal
c_func
(paren
id|sig
comma
id|arg
)paren
suffix:semicolon
r_case
l_int|0x100
suffix:colon
r_return
id|solaris_sigset
c_func
(paren
id|sig
comma
id|arg
)paren
suffix:semicolon
r_case
l_int|0x200
suffix:colon
r_return
id|solaris_sighold
c_func
(paren
id|sig
)paren
suffix:semicolon
r_case
l_int|0x400
suffix:colon
r_return
id|solaris_sigrelse
c_func
(paren
id|sig
)paren
suffix:semicolon
r_case
l_int|0x800
suffix:colon
r_return
id|solaris_sigignore
c_func
(paren
id|sig
)paren
suffix:semicolon
r_case
l_int|0x1000
suffix:colon
r_return
id|solaris_sigpause
c_func
(paren
id|sig
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_typedef
r_struct
(brace
DECL|member|__sigbits
id|u32
id|__sigbits
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|sol_sigset_t
)brace
id|sol_sigset_t
suffix:semicolon
DECL|function|mapin
r_static
r_inline
r_int
id|mapin
c_func
(paren
id|u32
op_star
id|p
comma
id|sigset_t
op_star
id|q
)paren
(brace
r_int
id|i
suffix:semicolon
id|u32
id|x
suffix:semicolon
r_int
id|sig
suffix:semicolon
id|sigemptyset
c_func
(paren
id|q
)paren
suffix:semicolon
id|x
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|SOLARIS_NSIGNALS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|x
op_amp
l_int|1
)paren
(brace
id|sig
op_assign
id|solaris_to_linux_signals
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sigaddsetmask
c_func
(paren
id|q
comma
(paren
l_int|1L
op_lshift
(paren
id|sig
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
)brace
id|x
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|32
)paren
id|x
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mapout
r_static
r_inline
r_int
id|mapout
c_func
(paren
id|sigset_t
op_star
id|q
comma
id|u32
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|sig
suffix:semicolon
id|p
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sigismember
c_func
(paren
id|q
comma
id|sigmask
c_func
(paren
id|i
)paren
)paren
)paren
(brace
id|sig
op_assign
id|linux_to_solaris_signals
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|sig
OG
l_int|32
)paren
id|p
(braket
l_int|1
)braket
op_or_assign
l_int|1L
op_lshift
(paren
id|sig
op_minus
l_int|33
)paren
suffix:semicolon
r_else
id|p
(braket
l_int|0
)braket
op_or_assign
l_int|1L
op_lshift
(paren
id|sig
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|solaris_sigprocmask
id|asmlinkage
r_int
id|solaris_sigprocmask
c_func
(paren
r_int
id|how
comma
id|u32
id|in
comma
id|u32
id|out
)paren
(brace
id|sigset_t
id|in_s
comma
op_star
id|ins
comma
id|out_s
comma
op_star
id|outs
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
(paren
op_star
id|sys_sigprocmask
)paren
(paren
r_int
comma
id|sigset_t
op_star
comma
id|sigset_t
op_star
)paren
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
r_int
comma
id|sigset_t
op_star
comma
id|sigset_t
op_star
)paren
)paren
id|SYS
c_func
(paren
id|sigprocmask
)paren
suffix:semicolon
id|ins
op_assign
l_int|NULL
suffix:semicolon
id|outs
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|in
)paren
(brace
id|u32
id|tmp
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
(paren
id|tmp
comma
(paren
id|sol_sigset_t
op_star
)paren
id|A
c_func
(paren
id|in
)paren
comma
l_int|2
op_star
r_sizeof
(paren
id|u32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ins
op_assign
op_amp
id|in_s
suffix:semicolon
r_if
c_cond
(paren
id|mapin
(paren
id|tmp
comma
id|ins
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|out
)paren
id|outs
op_assign
op_amp
id|out_s
suffix:semicolon
id|set_fs
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|ret
op_assign
id|sys_sigprocmask
c_func
(paren
(paren
id|how
op_eq
l_int|3
)paren
ques
c_cond
id|SIG_SETMASK
suffix:colon
id|how
comma
id|ins
comma
id|outs
)paren
suffix:semicolon
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|out
)paren
(brace
id|u32
id|tmp
(braket
l_int|4
)braket
suffix:semicolon
id|tmp
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|tmp
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mapout
(paren
id|outs
comma
id|tmp
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|sol_sigset_t
op_star
)paren
id|A
c_func
(paren
id|out
)paren
comma
id|tmp
comma
l_int|4
op_star
r_sizeof
(paren
id|u32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_sol_sigsuspend
id|asmlinkage
r_int
id|do_sol_sigsuspend
c_func
(paren
id|u32
id|mask
)paren
(brace
id|sigset_t
id|s
suffix:semicolon
id|u32
id|tmp
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
(paren
id|tmp
comma
(paren
id|sol_sigset_t
op_star
)paren
id|A
c_func
(paren
id|mask
)paren
comma
l_int|2
op_star
r_sizeof
(paren
id|u32
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
id|mapin
(paren
id|tmp
comma
op_amp
id|s
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
(paren
r_int
)paren
id|s.sig
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|struct|sol_sigaction
r_struct
id|sol_sigaction
(brace
DECL|member|sa_flags
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_handler
id|u32
id|sa_handler
suffix:semicolon
DECL|member|sa_mask
id|u32
id|sa_mask
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|sa_resv
r_int
id|sa_resv
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|solaris_sigaction
id|asmlinkage
r_int
id|solaris_sigaction
c_func
(paren
r_int
id|sig
comma
id|u32
id|act
comma
id|u32
id|old
)paren
(brace
id|u32
id|tmp
comma
id|tmp2
(braket
l_int|4
)braket
suffix:semicolon
r_struct
id|sigaction
id|s
comma
id|s2
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_int
(paren
op_star
id|sys_sigaction
)paren
(paren
r_int
comma
r_struct
id|sigaction
op_star
comma
r_struct
id|sigaction
op_star
)paren
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
r_int
comma
r_struct
id|sigaction
op_star
comma
r_struct
id|sigaction
op_star
)paren
)paren
id|SYS
c_func
(paren
id|sigaction
)paren
suffix:semicolon
id|sig
op_assign
id|mapsig
c_func
(paren
id|sig
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
OL
l_int|0
)paren
(brace
multiline_comment|/* We cheat a little bit for Solaris only signals */
r_if
c_cond
(paren
id|old
op_logical_and
id|clear_user
c_func
(paren
(paren
r_struct
id|sol_sigaction
op_star
)paren
id|A
c_func
(paren
id|old
)paren
comma
r_sizeof
(paren
r_struct
id|sol_sigaction
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|act
)paren
(brace
r_if
c_cond
(paren
id|get_user
(paren
id|tmp
comma
op_amp
(paren
(paren
r_struct
id|sol_sigaction
op_star
)paren
id|A
c_func
(paren
id|act
)paren
)paren
op_member_access_from_pointer
id|sa_flags
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|s.sa_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|SOLARIS_SA_ONSTACK
)paren
id|s.sa_flags
op_or_assign
id|SA_STACK
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|SOLARIS_SA_RESTART
)paren
id|s.sa_flags
op_or_assign
id|SA_RESTART
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|SOLARIS_SA_NODEFER
)paren
id|s.sa_flags
op_or_assign
id|SA_NOMASK
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|SOLARIS_SA_RESETHAND
)paren
id|s.sa_flags
op_or_assign
id|SA_ONESHOT
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|SOLARIS_SA_NOCLDSTOP
)paren
id|s.sa_flags
op_or_assign
id|SA_NOCLDSTOP
suffix:semicolon
r_if
c_cond
(paren
id|get_user
(paren
id|tmp
comma
op_amp
(paren
(paren
r_struct
id|sol_sigaction
op_star
)paren
id|A
c_func
(paren
id|act
)paren
)paren
op_member_access_from_pointer
id|sa_handler
)paren
op_logical_or
id|copy_from_user
(paren
id|tmp2
comma
op_amp
(paren
(paren
r_struct
id|sol_sigaction
op_star
)paren
id|A
c_func
(paren
id|act
)paren
)paren
op_member_access_from_pointer
id|sa_mask
comma
l_int|2
op_star
r_sizeof
(paren
id|u32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|s.sa_handler
op_assign
(paren
id|__sighandler_t
)paren
id|A
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapin
(paren
id|tmp2
comma
op_amp
id|s.sa_mask
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|s.sa_restorer
op_assign
l_int|0
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|ret
op_assign
id|sys_sigaction
c_func
(paren
id|sig
comma
id|act
ques
c_cond
op_amp
id|s
suffix:colon
l_int|NULL
comma
id|old
ques
c_cond
op_amp
id|s2
suffix:colon
l_int|NULL
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|old
)paren
(brace
r_if
c_cond
(paren
id|mapout
(paren
op_amp
id|s2.sa_mask
comma
id|tmp2
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp2
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|tmp2
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|s2.sa_flags
op_amp
id|SA_STACK
)paren
id|tmp
op_or_assign
id|SOLARIS_SA_ONSTACK
suffix:semicolon
r_if
c_cond
(paren
id|s2.sa_flags
op_amp
id|SA_RESTART
)paren
id|tmp
op_or_assign
id|SOLARIS_SA_RESTART
suffix:semicolon
r_if
c_cond
(paren
id|s2.sa_flags
op_amp
id|SA_NOMASK
)paren
id|tmp
op_or_assign
id|SOLARIS_SA_NODEFER
suffix:semicolon
r_if
c_cond
(paren
id|s2.sa_flags
op_amp
id|SA_ONESHOT
)paren
id|tmp
op_or_assign
id|SOLARIS_SA_RESETHAND
suffix:semicolon
r_if
c_cond
(paren
id|s2.sa_flags
op_amp
id|SA_NOCLDSTOP
)paren
id|tmp
op_or_assign
id|SOLARIS_SA_NOCLDSTOP
suffix:semicolon
r_if
c_cond
(paren
id|put_user
(paren
id|tmp
comma
op_amp
(paren
(paren
r_struct
id|sol_sigaction
op_star
)paren
id|A
c_func
(paren
id|old
)paren
)paren
op_member_access_from_pointer
id|sa_flags
)paren
op_logical_or
id|__put_user
(paren
(paren
id|u32
)paren
(paren
r_int
)paren
id|s2.sa_handler
comma
op_amp
(paren
(paren
r_struct
id|sol_sigaction
op_star
)paren
id|A
c_func
(paren
id|old
)paren
)paren
op_member_access_from_pointer
id|sa_handler
)paren
op_logical_or
id|copy_to_user
(paren
op_amp
(paren
(paren
r_struct
id|sol_sigaction
op_star
)paren
id|A
c_func
(paren
id|old
)paren
)paren
op_member_access_from_pointer
id|sa_mask
comma
id|tmp2
comma
l_int|4
op_star
r_sizeof
(paren
id|u32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|solaris_sigpending
id|asmlinkage
r_int
id|solaris_sigpending
c_func
(paren
r_int
id|which
comma
id|u32
id|set
)paren
(brace
id|sigset_t
id|s
suffix:semicolon
id|u32
id|tmp
(braket
l_int|4
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|which
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* sigpending */
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|sigandsets
c_func
(paren
op_amp
id|s
comma
op_amp
id|current-&gt;blocked
comma
op_amp
id|current-&gt;pending.signal
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
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* sigfillset - I just set signals which have linux equivalents */
id|sigfillset
c_func
(paren
op_amp
id|s
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mapout
(paren
op_amp
id|s
comma
id|tmp
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tmp
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|tmp
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
(paren
id|u32
op_star
)paren
id|A
c_func
(paren
id|set
)paren
comma
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|solaris_wait
id|asmlinkage
r_int
id|solaris_wait
c_func
(paren
id|u32
id|stat_loc
)paren
(brace
r_int
(paren
op_star
id|sys_wait4
)paren
(paren
id|pid_t
comma
r_int
r_int
op_star
comma
r_int
comma
r_struct
id|rusage
op_star
)paren
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
id|pid_t
comma
r_int
r_int
op_star
comma
r_int
comma
r_struct
id|rusage
op_star
)paren
)paren
id|SYS
c_func
(paren
id|wait4
)paren
suffix:semicolon
r_int
id|ret
comma
id|status
suffix:semicolon
id|ret
op_assign
id|sys_wait4
c_func
(paren
op_minus
l_int|1
comma
(paren
r_int
r_int
op_star
)paren
id|A
c_func
(paren
id|stat_loc
)paren
comma
id|WUNTRACED
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
op_logical_and
id|stat_loc
)paren
(brace
r_if
c_cond
(paren
id|get_user
(paren
id|status
comma
(paren
r_int
r_int
op_star
)paren
id|A
c_func
(paren
id|stat_loc
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
(paren
(paren
id|status
op_minus
l_int|1
)paren
op_amp
l_int|0xffff
)paren
OL
l_int|0xff
)paren
id|status
op_assign
id|linux_to_solaris_signals
(braket
id|status
op_amp
l_int|0x7f
)braket
op_amp
l_int|0x7f
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0xff
)paren
op_eq
l_int|0x7f
)paren
id|status
op_assign
(paren
id|linux_to_solaris_signals
(braket
(paren
id|status
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)braket
op_lshift
l_int|8
)paren
op_or
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
(paren
id|status
comma
(paren
r_int
r_int
op_star
)paren
id|A
c_func
(paren
id|stat_loc
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|solaris_waitid
id|asmlinkage
r_int
id|solaris_waitid
c_func
(paren
r_int
id|idtype
comma
id|s32
id|pid
comma
id|u32
id|info
comma
r_int
id|options
)paren
(brace
r_int
(paren
op_star
id|sys_wait4
)paren
(paren
id|pid_t
comma
r_int
r_int
op_star
comma
r_int
comma
r_struct
id|rusage
op_star
)paren
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
id|pid_t
comma
r_int
r_int
op_star
comma
r_int
comma
r_struct
id|rusage
op_star
)paren
)paren
id|SYS
c_func
(paren
id|wait4
)paren
suffix:semicolon
r_int
id|opts
comma
id|status
comma
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|idtype
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* P_PID */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* P_PGID */
id|pid
op_assign
op_minus
id|pid
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* P_ALL */
id|pid
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|opts
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|options
op_amp
id|SOLARIS_WUNTRACED
)paren
id|opts
op_or_assign
id|WUNTRACED
suffix:semicolon
r_if
c_cond
(paren
id|options
op_amp
id|SOLARIS_WNOHANG
)paren
id|opts
op_or_assign
id|WNOHANG
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|ret
op_assign
id|sys_wait4
c_func
(paren
id|pid
comma
(paren
r_int
r_int
op_star
)paren
id|A
c_func
(paren
id|info
)paren
comma
id|opts
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|info
)paren
(brace
r_struct
id|sol_siginfo
op_star
id|s
op_assign
(paren
r_struct
id|sol_siginfo
op_star
)paren
id|A
c_func
(paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_user
(paren
id|status
comma
(paren
r_int
r_int
op_star
)paren
id|A
c_func
(paren
id|info
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
id|__put_user
(paren
id|SOLARIS_SIGCLD
comma
op_amp
id|s-&gt;si_signo
)paren
op_logical_or
id|__put_user
(paren
id|ret
comma
op_amp
id|s-&gt;_data._proc._pid
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|status
op_amp
l_int|0xff
)paren
(brace
r_case
l_int|0
suffix:colon
id|ret
op_assign
id|SOLARIS_CLD_EXITED
suffix:semicolon
id|status
op_assign
(paren
id|status
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x7f
suffix:colon
id|status
op_assign
(paren
id|status
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|SIGSTOP
suffix:colon
r_case
id|SIGTSTP
suffix:colon
id|ret
op_assign
id|SOLARIS_CLD_STOPPED
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
id|SOLARIS_CLD_EXITED
suffix:semicolon
)brace
id|status
op_assign
id|linux_to_solaris_signals
(braket
id|status
)braket
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|status
op_amp
l_int|0x80
)paren
id|ret
op_assign
id|SOLARIS_CLD_DUMPED
suffix:semicolon
r_else
id|ret
op_assign
id|SOLARIS_CLD_KILLED
suffix:semicolon
id|status
op_assign
id|linux_to_solaris_signals
(braket
id|status
op_amp
l_int|0x7f
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|__put_user
(paren
id|ret
comma
op_amp
id|s-&gt;si_code
)paren
op_logical_or
id|__put_user
(paren
id|status
comma
op_amp
id|s-&gt;_data._proc._pdata._cld._status
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|svr4_setcontext
c_func
(paren
id|svr4_ucontext_t
op_star
id|c
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|svr4_getcontext
c_func
(paren
id|svr4_ucontext_t
op_star
id|c
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|function|solaris_context
id|asmlinkage
r_int
id|solaris_context
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_switch
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;u_regs
(braket
id|UREG_I0
)braket
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* getcontext */
r_return
id|svr4_getcontext
c_func
(paren
(paren
id|svr4_ucontext_t
op_star
)paren
(paren
r_int
)paren
(paren
id|u32
)paren
id|regs-&gt;u_regs
(braket
id|UREG_I1
)braket
comma
id|regs
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* setcontext */
r_return
id|svr4_setcontext
c_func
(paren
(paren
id|svr4_ucontext_t
op_star
)paren
(paren
r_int
)paren
(paren
id|u32
)paren
id|regs-&gt;u_regs
(braket
id|UREG_I1
)braket
comma
id|regs
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|solaris_sigaltstack
id|asmlinkage
r_int
id|solaris_sigaltstack
c_func
(paren
id|u32
id|ss
comma
id|u32
id|oss
)paren
(brace
multiline_comment|/* XXX Implement this soon */
r_return
l_int|0
suffix:semicolon
)brace
eof
