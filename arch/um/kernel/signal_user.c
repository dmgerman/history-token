multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;signal_kern.h&quot;
macro_line|#include &quot;sysdep/sigcontext.h&quot;
macro_line|#include &quot;sigcontext.h&quot;
DECL|function|set_sigstack
r_void
id|set_sigstack
c_func
(paren
r_void
op_star
id|sig_stack
comma
r_int
id|size
)paren
(brace
id|stack_t
id|stack
op_assign
(paren
(paren
id|stack_t
)paren
(brace
dot
id|ss_flags
op_assign
l_int|0
comma
dot
id|ss_sp
op_assign
(paren
id|__ptr_t
)paren
id|sig_stack
comma
dot
id|ss_size
op_assign
id|size
op_minus
r_sizeof
(paren
r_void
op_star
)paren
)brace
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sigaltstack
c_func
(paren
op_amp
id|stack
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;enabling signal stack failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|set_handler
r_void
id|set_handler
c_func
(paren
r_int
id|sig
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
)paren
comma
r_int
id|flags
comma
dot
dot
dot
)paren
(brace
r_struct
id|sigaction
id|action
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
r_int
id|mask
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|flags
)paren
suffix:semicolon
id|action.sa_handler
op_assign
id|handler
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|action.sa_mask
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|mask
op_assign
id|va_arg
c_func
(paren
id|ap
comma
r_int
)paren
)paren
op_ne
op_minus
l_int|1
)paren
(brace
id|sigaddset
c_func
(paren
op_amp
id|action.sa_mask
comma
id|mask
)paren
suffix:semicolon
)brace
id|action.sa_flags
op_assign
id|flags
suffix:semicolon
id|action.sa_restorer
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|sigaction
c_func
(paren
id|sig
comma
op_amp
id|action
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;sigaction failed&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|change_sig
r_int
id|change_sig
c_func
(paren
r_int
id|signal
comma
r_int
id|on
)paren
(brace
id|sigset_t
id|sigset
comma
id|old
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|sigset
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|sigset
comma
id|signal
)paren
suffix:semicolon
id|sigprocmask
c_func
(paren
id|on
ques
c_cond
id|SIG_UNBLOCK
suffix:colon
id|SIG_BLOCK
comma
op_amp
id|sigset
comma
op_amp
id|old
)paren
suffix:semicolon
r_return
op_logical_neg
id|sigismember
c_func
(paren
op_amp
id|old
comma
id|signal
)paren
suffix:semicolon
)brace
DECL|function|change_signals
r_static
r_void
id|change_signals
c_func
(paren
r_int
id|type
)paren
(brace
id|sigset_t
id|mask
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|mask
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|mask
comma
id|SIGVTALRM
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|mask
comma
id|SIGALRM
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|mask
comma
id|SIGIO
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|mask
comma
id|SIGPROF
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sigprocmask
c_func
(paren
id|type
comma
op_amp
id|mask
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Failed to change signal mask - errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|block_signals
r_void
id|block_signals
c_func
(paren
r_void
)paren
(brace
id|change_signals
c_func
(paren
id|SIG_BLOCK
)paren
suffix:semicolon
)brace
DECL|function|unblock_signals
r_void
id|unblock_signals
c_func
(paren
r_void
)paren
(brace
id|change_signals
c_func
(paren
id|SIG_UNBLOCK
)paren
suffix:semicolon
)brace
DECL|macro|SIGIO_BIT
mdefine_line|#define SIGIO_BIT 0
DECL|macro|SIGVTALRM_BIT
mdefine_line|#define SIGVTALRM_BIT 1
DECL|function|enable_mask
r_static
r_int
id|enable_mask
c_func
(paren
id|sigset_t
op_star
id|mask
)paren
(brace
r_int
id|sigs
suffix:semicolon
id|sigs
op_assign
id|sigismember
c_func
(paren
id|mask
comma
id|SIGIO
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
op_lshift
id|SIGIO_BIT
suffix:semicolon
id|sigs
op_or_assign
id|sigismember
c_func
(paren
id|mask
comma
id|SIGVTALRM
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
op_lshift
id|SIGVTALRM_BIT
suffix:semicolon
id|sigs
op_or_assign
id|sigismember
c_func
(paren
id|mask
comma
id|SIGALRM
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
op_lshift
id|SIGVTALRM_BIT
suffix:semicolon
r_return
id|sigs
suffix:semicolon
)brace
DECL|function|get_signals
r_int
id|get_signals
c_func
(paren
r_void
)paren
(brace
id|sigset_t
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|sigprocmask
c_func
(paren
id|SIG_SETMASK
comma
l_int|NULL
comma
op_amp
id|mask
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Failed to get signal mask&quot;
)paren
suffix:semicolon
)brace
r_return
id|enable_mask
c_func
(paren
op_amp
id|mask
)paren
suffix:semicolon
)brace
DECL|function|set_signals
r_int
id|set_signals
c_func
(paren
r_int
id|enable
)paren
(brace
id|sigset_t
id|mask
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|enable
op_amp
(paren
l_int|1
op_lshift
id|SIGIO_BIT
)paren
)paren
(brace
id|sigaddset
c_func
(paren
op_amp
id|mask
comma
id|SIGIO
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|enable
op_amp
(paren
l_int|1
op_lshift
id|SIGVTALRM_BIT
)paren
)paren
(brace
id|sigaddset
c_func
(paren
op_amp
id|mask
comma
id|SIGVTALRM
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|mask
comma
id|SIGALRM
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sigprocmask
c_func
(paren
id|SIG_UNBLOCK
comma
op_amp
id|mask
comma
op_amp
id|mask
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Failed to enable signals&quot;
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|enable_mask
c_func
(paren
op_amp
id|mask
)paren
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|enable
op_amp
(paren
l_int|1
op_lshift
id|SIGIO_BIT
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|sigaddset
c_func
(paren
op_amp
id|mask
comma
id|SIGIO
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|enable
op_amp
(paren
l_int|1
op_lshift
id|SIGVTALRM_BIT
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|sigaddset
c_func
(paren
op_amp
id|mask
comma
id|SIGVTALRM
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|mask
comma
id|SIGALRM
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sigprocmask
c_func
(paren
id|SIG_BLOCK
comma
op_amp
id|mask
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Failed to block signals&quot;
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
