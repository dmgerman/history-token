multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;time.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;process.h&quot;
macro_line|#include &quot;signal_user.h&quot;
r_extern
r_struct
id|timeval
id|xtime
suffix:semicolon
DECL|function|timer_handler
r_void
id|timer_handler
c_func
(paren
r_int
id|sig
comma
r_struct
id|uml_pt_regs
op_star
id|regs
)paren
(brace
id|timer_irq
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
DECL|function|timer
r_void
id|timer
c_func
(paren
r_void
)paren
(brace
id|gettimeofday
c_func
(paren
op_amp
id|xtime
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|profile_interval
r_static
r_struct
id|itimerval
id|profile_interval
suffix:semicolon
DECL|function|get_profile_timer
r_void
id|get_profile_timer
c_func
(paren
r_void
)paren
(brace
id|getitimer
c_func
(paren
id|ITIMER_PROF
comma
op_amp
id|profile_interval
)paren
suffix:semicolon
id|profile_interval.it_value
op_assign
id|profile_interval.it_interval
suffix:semicolon
)brace
DECL|function|disable_profile_timer
r_void
id|disable_profile_timer
c_func
(paren
r_void
)paren
(brace
r_struct
id|itimerval
id|interval
op_assign
(paren
(paren
r_struct
id|itimerval
)paren
(brace
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
)paren
suffix:semicolon
id|setitimer
c_func
(paren
id|ITIMER_PROF
comma
op_amp
id|interval
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|set_interval
r_static
r_void
id|set_interval
c_func
(paren
r_int
id|timer_type
)paren
(brace
r_struct
id|itimerval
id|interval
suffix:semicolon
id|interval.it_interval.tv_sec
op_assign
l_int|0
suffix:semicolon
id|interval.it_interval.tv_usec
op_assign
l_int|1000000
op_div
id|hz
c_func
(paren
)paren
suffix:semicolon
id|interval.it_value.tv_sec
op_assign
l_int|0
suffix:semicolon
id|interval.it_value.tv_usec
op_assign
l_int|1000000
op_div
id|hz
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|setitimer
c_func
(paren
id|timer_type
comma
op_amp
id|interval
comma
l_int|NULL
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;setitimer failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|idle_timer
r_void
id|idle_timer
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|signal
c_func
(paren
id|SIGVTALRM
comma
id|SIG_IGN
)paren
op_eq
id|SIG_ERR
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t unset SIGVTALRM handler&quot;
)paren
suffix:semicolon
)brace
id|set_handler
c_func
(paren
id|SIGALRM
comma
(paren
id|__sighandler_t
)paren
id|alarm_handler
comma
id|SA_NODEFER
op_or
id|SA_RESTART
comma
id|SIGUSR1
comma
id|SIGIO
comma
id|SIGWINCH
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|set_interval
c_func
(paren
id|ITIMER_REAL
)paren
suffix:semicolon
)brace
DECL|function|user_time_init
r_void
id|user_time_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|signal
c_func
(paren
id|SIGVTALRM
comma
(paren
id|__sighandler_t
)paren
id|alarm_handler
)paren
op_eq
id|SIG_ERR
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t set SIGVTALRM handler&quot;
)paren
suffix:semicolon
)brace
id|set_interval
c_func
(paren
id|ITIMER_VIRTUAL
)paren
suffix:semicolon
)brace
DECL|function|time_init
r_void
id|time_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|signal
c_func
(paren
id|SIGVTALRM
comma
id|boot_timer_handler
)paren
op_eq
id|SIG_ERR
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t set SIGVTALRM handler&quot;
)paren
suffix:semicolon
)brace
id|set_interval
c_func
(paren
id|ITIMER_VIRTUAL
)paren
suffix:semicolon
)brace
DECL|function|set_timers
r_void
id|set_timers
c_func
(paren
r_int
id|set_signal
)paren
(brace
r_if
c_cond
(paren
id|set_signal
)paren
(brace
id|set_interval
c_func
(paren
id|ITIMER_VIRTUAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|setitimer
c_func
(paren
id|ITIMER_PROF
comma
op_amp
id|profile_interval
comma
l_int|NULL
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;setitimer ITIMER_PROF failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|variable|local_offset
r_struct
id|timeval
id|local_offset
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|function|do_gettimeofday
r_void
id|do_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
id|gettimeofday
c_func
(paren
id|tv
comma
l_int|NULL
)paren
suffix:semicolon
id|timeradd
c_func
(paren
id|tv
comma
op_amp
id|local_offset
comma
id|tv
)paren
suffix:semicolon
)brace
DECL|function|do_settimeofday
r_void
id|do_settimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
r_struct
id|timeval
id|now
suffix:semicolon
id|gettimeofday
c_func
(paren
op_amp
id|now
comma
l_int|NULL
)paren
suffix:semicolon
id|timersub
c_func
(paren
id|tv
comma
op_amp
id|now
comma
op_amp
id|local_offset
)paren
suffix:semicolon
)brace
DECL|function|idle_sleep
r_void
id|idle_sleep
c_func
(paren
r_int
id|secs
)paren
(brace
r_struct
id|timespec
id|ts
suffix:semicolon
id|ts.tv_sec
op_assign
id|secs
suffix:semicolon
id|ts.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|nanosleep
c_func
(paren
op_amp
id|ts
comma
op_amp
id|ts
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
