multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;time.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;process.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;time_user.h&quot;
macro_line|#include &quot;kern_constants.h&quot;
multiline_comment|/* XXX This really needs to be declared and initialized in a kernel file since&n; * it&squot;s in &lt;linux/time.h&gt;&n; */
r_extern
r_struct
id|timespec
id|wall_to_monotonic
suffix:semicolon
r_extern
r_struct
id|timeval
id|xtime
suffix:semicolon
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
id|timeradd
c_func
(paren
op_amp
id|xtime
comma
op_amp
id|local_offset
comma
op_amp
id|xtime
)paren
suffix:semicolon
)brace
DECL|function|set_interval
r_void
id|set_interval
c_func
(paren
r_int
id|timer_type
)paren
(brace
r_int
id|usec
op_assign
l_int|1000000
op_div
id|hz
c_func
(paren
)paren
suffix:semicolon
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
id|usec
)brace
comma
(brace
l_int|0
comma
id|usec
)brace
)brace
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
DECL|function|enable_timer
r_void
id|enable_timer
c_func
(paren
r_void
)paren
(brace
r_int
id|usec
op_assign
l_int|1000000
op_div
id|hz
c_func
(paren
)paren
suffix:semicolon
r_struct
id|itimerval
id|enable
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
id|usec
)brace
comma
(brace
l_int|0
comma
id|usec
)brace
)brace
)paren
suffix:semicolon
r_if
c_cond
(paren
id|setitimer
c_func
(paren
id|ITIMER_VIRTUAL
comma
op_amp
id|enable
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;enable_timer - setitimer failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|switch_timers
r_void
id|switch_timers
c_func
(paren
r_int
id|to_real
)paren
(brace
r_struct
id|itimerval
id|disable
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
r_struct
id|itimerval
id|enable
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
l_int|1000000
op_div
id|hz
c_func
(paren
)paren
)brace
comma
(brace
l_int|0
comma
l_int|1000000
op_div
id|hz
c_func
(paren
)paren
)brace
)brace
)paren
suffix:semicolon
r_int
id|old
comma
r_new
suffix:semicolon
r_if
c_cond
(paren
id|to_real
)paren
(brace
id|old
op_assign
id|ITIMER_VIRTUAL
suffix:semicolon
r_new
op_assign
id|ITIMER_REAL
suffix:semicolon
)brace
r_else
(brace
id|old
op_assign
id|ITIMER_REAL
suffix:semicolon
r_new
op_assign
id|ITIMER_VIRTUAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|setitimer
c_func
(paren
id|old
comma
op_amp
id|disable
comma
l_int|NULL
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|setitimer
c_func
(paren
r_new
comma
op_amp
id|enable
comma
l_int|NULL
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;switch_timers - setitimer failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|uml_idle_timer
r_void
id|uml_idle_timer
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
id|SA_RESTART
comma
id|SIGUSR1
comma
id|SIGIO
comma
id|SIGWINCH
comma
id|SIGVTALRM
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
DECL|function|get_host_hz
r_static
r_int
r_int
r_int
id|get_host_hz
c_func
(paren
r_void
)paren
(brace
r_char
id|mhzline
(braket
l_int|16
)braket
comma
op_star
id|end
suffix:semicolon
r_int
r_int
r_int
id|mhz
suffix:semicolon
r_int
id|ret
comma
id|mult
comma
id|rest
comma
id|len
suffix:semicolon
id|ret
op_assign
id|cpu_feature
c_func
(paren
l_string|&quot;cpu MHz&quot;
comma
id|mhzline
comma
r_sizeof
(paren
id|mhzline
)paren
op_div
r_sizeof
(paren
id|mhzline
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|panic
(paren
l_string|&quot;Could not get host MHZ&quot;
)paren
suffix:semicolon
)brace
id|mhz
op_assign
id|strtoul
c_func
(paren
id|mhzline
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
multiline_comment|/* This business is to parse a floating point number without using&n;&t; * floating types.&n;&t; */
id|rest
op_assign
l_int|0
suffix:semicolon
id|mult
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|end
op_eq
l_char|&squot;.&squot;
)paren
(brace
id|end
op_increment
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|6
)paren
(brace
id|mult
op_assign
l_int|6
op_minus
id|len
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|len
OG
l_int|6
)paren
(brace
id|end
(braket
l_int|6
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
id|rest
op_assign
id|strtoul
c_func
(paren
id|end
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_while
c_loop
(paren
id|mult
op_decrement
OG
l_int|0
)paren
(brace
id|rest
op_mul_assign
l_int|10
suffix:semicolon
)brace
)brace
r_return
l_int|1000000
op_star
id|mhz
op_plus
id|rest
suffix:semicolon
)brace
DECL|variable|host_hz
r_int
r_int
r_int
id|host_hz
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
id|do_posix_clock_monotonic_gettime
c_func
(paren
r_struct
id|timespec
op_star
id|tp
)paren
suffix:semicolon
DECL|function|time_init
r_void
id|time_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|timespec
id|now
suffix:semicolon
id|host_hz
op_assign
id|get_host_hz
c_func
(paren
)paren
suffix:semicolon
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
id|do_posix_clock_monotonic_gettime
c_func
(paren
op_amp
id|now
)paren
suffix:semicolon
id|wall_to_monotonic.tv_sec
op_assign
op_minus
id|now.tv_sec
suffix:semicolon
id|wall_to_monotonic.tv_nsec
op_assign
op_minus
id|now.tv_nsec
suffix:semicolon
)brace
multiline_comment|/* Declared in linux/time.h, which can&squot;t be included here */
r_extern
r_void
id|clock_was_set
c_func
(paren
r_void
)paren
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
r_int
r_int
id|flags
suffix:semicolon
id|flags
op_assign
id|time_lock
c_func
(paren
)paren
suffix:semicolon
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
id|time_unlock
c_func
(paren
id|flags
)paren
suffix:semicolon
id|clock_was_set
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_settimeofday
r_int
id|do_settimeofday
c_func
(paren
r_struct
id|timespec
op_star
id|tv
)paren
(brace
r_struct
id|timeval
id|now
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|timeval
id|tv_in
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|tv-&gt;tv_nsec
op_ge
id|UM_NSEC_PER_SEC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tv_in.tv_sec
op_assign
id|tv-&gt;tv_sec
suffix:semicolon
id|tv_in.tv_usec
op_assign
id|tv-&gt;tv_nsec
op_div
l_int|1000
suffix:semicolon
id|flags
op_assign
id|time_lock
c_func
(paren
)paren
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
op_amp
id|tv_in
comma
op_amp
id|now
comma
op_amp
id|local_offset
)paren
suffix:semicolon
id|time_unlock
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
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
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
