macro_line|#ifndef _LINUX_TIME_H
DECL|macro|_LINUX_TIME_H
mdefine_line|#define _LINUX_TIME_H
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifndef _STRUCT_TIMESPEC
DECL|macro|_STRUCT_TIMESPEC
mdefine_line|#define _STRUCT_TIMESPEC
DECL|struct|timespec
r_struct
id|timespec
(brace
DECL|member|tv_sec
id|time_t
id|tv_sec
suffix:semicolon
multiline_comment|/* seconds */
DECL|member|tv_nsec
r_int
id|tv_nsec
suffix:semicolon
multiline_comment|/* nanoseconds */
)brace
suffix:semicolon
macro_line|#endif /* _STRUCT_TIMESPEC */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Change timeval to jiffies, trying to avoid the&n; * most obvious overflows..&n; *&n; * And some not so obvious.&n; *&n; * Note that we don&squot;t want to return MAX_LONG, because&n; * for various timeout reasons we often end up having&n; * to wait &quot;jiffies+1&quot; in order to guarantee that we wait&n; * at _least_ &quot;jiffies&quot; - so &quot;jiffies+1&quot; had better still&n; * be positive.&n; */
DECL|macro|MAX_JIFFY_OFFSET
mdefine_line|#define MAX_JIFFY_OFFSET ((~0UL &gt;&gt; 1)-1)
r_static
id|__inline__
r_int
r_int
DECL|function|timespec_to_jiffies
id|timespec_to_jiffies
c_func
(paren
r_struct
id|timespec
op_star
id|value
)paren
(brace
r_int
r_int
id|sec
op_assign
id|value-&gt;tv_sec
suffix:semicolon
r_int
id|nsec
op_assign
id|value-&gt;tv_nsec
suffix:semicolon
r_if
c_cond
(paren
id|sec
op_ge
(paren
id|MAX_JIFFY_OFFSET
op_div
id|HZ
)paren
)paren
r_return
id|MAX_JIFFY_OFFSET
suffix:semicolon
id|nsec
op_add_assign
l_int|1000000000L
op_div
id|HZ
op_minus
l_int|1
suffix:semicolon
id|nsec
op_div_assign
l_int|1000000000L
op_div
id|HZ
suffix:semicolon
r_return
id|HZ
op_star
id|sec
op_plus
id|nsec
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|jiffies_to_timespec
id|jiffies_to_timespec
c_func
(paren
r_int
r_int
id|jiffies
comma
r_struct
id|timespec
op_star
id|value
)paren
(brace
id|value-&gt;tv_nsec
op_assign
(paren
id|jiffies
op_mod
id|HZ
)paren
op_star
(paren
l_int|1000000000L
op_div
id|HZ
)paren
suffix:semicolon
id|value-&gt;tv_sec
op_assign
id|jiffies
op_div
id|HZ
suffix:semicolon
)brace
multiline_comment|/* Converts Gregorian date to seconds since 1970-01-01 00:00:00.&n; * Assumes input in normal date format, i.e. 1980-12-31 23:59:59&n; * =&gt; year=1980, mon=12, day=31, hour=23, min=59, sec=59.&n; *&n; * [For the Julian calendar (which was used in Russia before 1917,&n; * Britain &amp; colonies before 1752, anywhere else before 1582,&n; * and is still in use by some communities) leave out the&n; * -year/100+year/400 terms, and add 10.]&n; *&n; * This algorithm was first published by Gauss (I think).&n; *&n; * WARNING: this function will overflow on 2106-02-07 06:28:16 on&n; * machines were long is 32-bit! (However, as time_t is signed, we&n; * will already get problems at other places on 2038-01-19 03:14:08)&n; */
r_static
r_inline
r_int
r_int
DECL|function|mktime
id|mktime
(paren
r_int
r_int
id|year
comma
r_int
r_int
id|mon
comma
r_int
r_int
id|day
comma
r_int
r_int
id|hour
comma
r_int
r_int
id|min
comma
r_int
r_int
id|sec
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ge
(paren
r_int
)paren
(paren
id|mon
op_sub_assign
l_int|2
)paren
)paren
(brace
multiline_comment|/* 1..12 -&gt; 11,12,1..10 */
id|mon
op_add_assign
l_int|12
suffix:semicolon
multiline_comment|/* Puts Feb last since it has leap day */
id|year
op_sub_assign
l_int|1
suffix:semicolon
)brace
r_return
(paren
(paren
(paren
(paren
r_int
r_int
)paren
(paren
id|year
op_div
l_int|4
op_minus
id|year
op_div
l_int|100
op_plus
id|year
op_div
l_int|400
op_plus
l_int|367
op_star
id|mon
op_div
l_int|12
op_plus
id|day
)paren
op_plus
id|year
op_star
l_int|365
op_minus
l_int|719499
)paren
op_star
l_int|24
op_plus
id|hour
multiline_comment|/* now have hours */
)paren
op_star
l_int|60
op_plus
id|min
multiline_comment|/* now have minutes */
)paren
op_star
l_int|60
op_plus
id|sec
suffix:semicolon
multiline_comment|/* finally seconds */
)brace
r_extern
r_struct
id|timeval
id|xtime
suffix:semicolon
DECL|macro|CURRENT_TIME
mdefine_line|#define CURRENT_TIME (xtime.tv_sec)
macro_line|#endif /* __KERNEL__ */
DECL|struct|timeval
r_struct
id|timeval
(brace
DECL|member|tv_sec
id|time_t
id|tv_sec
suffix:semicolon
multiline_comment|/* seconds */
DECL|member|tv_usec
id|suseconds_t
id|tv_usec
suffix:semicolon
multiline_comment|/* microseconds */
)brace
suffix:semicolon
DECL|struct|timezone
r_struct
id|timezone
(brace
DECL|member|tz_minuteswest
r_int
id|tz_minuteswest
suffix:semicolon
multiline_comment|/* minutes west of Greenwich */
DECL|member|tz_dsttime
r_int
id|tz_dsttime
suffix:semicolon
multiline_comment|/* type of dst correction */
)brace
suffix:semicolon
DECL|macro|NFDBITS
mdefine_line|#define NFDBITS&t;&t;&t;__NFDBITS
macro_line|#ifdef __KERNEL__
r_extern
r_void
id|do_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
r_extern
r_void
id|do_settimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|FD_SETSIZE
mdefine_line|#define FD_SETSIZE&t;&t;__FD_SETSIZE
DECL|macro|FD_SET
mdefine_line|#define FD_SET(fd,fdsetp)&t;__FD_SET(fd,fdsetp)
DECL|macro|FD_CLR
mdefine_line|#define FD_CLR(fd,fdsetp)&t;__FD_CLR(fd,fdsetp)
DECL|macro|FD_ISSET
mdefine_line|#define FD_ISSET(fd,fdsetp)&t;__FD_ISSET(fd,fdsetp)
DECL|macro|FD_ZERO
mdefine_line|#define FD_ZERO(fdsetp)&t;&t;__FD_ZERO(fdsetp)
multiline_comment|/*&n; * Names of the interval timers, and structure&n; * defining a timer setting.&n; */
DECL|macro|ITIMER_REAL
mdefine_line|#define&t;ITIMER_REAL&t;0
DECL|macro|ITIMER_VIRTUAL
mdefine_line|#define&t;ITIMER_VIRTUAL&t;1
DECL|macro|ITIMER_PROF
mdefine_line|#define&t;ITIMER_PROF&t;2
DECL|struct|itimerspec
r_struct
id|itimerspec
(brace
DECL|member|it_interval
r_struct
id|timespec
id|it_interval
suffix:semicolon
multiline_comment|/* timer period */
DECL|member|it_value
r_struct
id|timespec
id|it_value
suffix:semicolon
multiline_comment|/* timer expiration */
)brace
suffix:semicolon
DECL|struct|itimerval
r_struct
id|itimerval
(brace
DECL|member|it_interval
r_struct
id|timeval
id|it_interval
suffix:semicolon
multiline_comment|/* timer interval */
DECL|member|it_value
r_struct
id|timeval
id|it_value
suffix:semicolon
multiline_comment|/* current value */
)brace
suffix:semicolon
macro_line|#endif
eof
