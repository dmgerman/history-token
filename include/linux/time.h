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
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/seqlock.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#ifndef div_long_long_rem
DECL|macro|div_long_long_rem
mdefine_line|#define div_long_long_rem(dividend,divisor,remainder) ({ &bslash;&n;&t;&t;       u64 result = dividend;&t;&t;&bslash;&n;&t;&t;       *remainder = do_div(result,divisor); &bslash;&n;&t;&t;       result; })
macro_line|#endif
multiline_comment|/*&n; * Have the 32 bit jiffies value wrap 5 minutes after boot&n; * so jiffies wrap bugs show up earlier.&n; */
DECL|macro|INITIAL_JIFFIES
mdefine_line|#define INITIAL_JIFFIES ((unsigned long)(unsigned int) (-300*HZ))
multiline_comment|/*&n; * Change timeval to jiffies, trying to avoid the&n; * most obvious overflows..&n; *&n; * And some not so obvious.&n; *&n; * Note that we don&squot;t want to return MAX_LONG, because&n; * for various timeout reasons we often end up having&n; * to wait &quot;jiffies+1&quot; in order to guarantee that we wait&n; * at _least_ &quot;jiffies&quot; - so &quot;jiffies+1&quot; had better still&n; * be positive.&n; */
DECL|macro|MAX_JIFFY_OFFSET
mdefine_line|#define MAX_JIFFY_OFFSET ((~0UL &gt;&gt; 1)-1)
multiline_comment|/* Parameters used to convert the timespec values */
macro_line|#ifndef USEC_PER_SEC
DECL|macro|USEC_PER_SEC
mdefine_line|#define USEC_PER_SEC (1000000L)
macro_line|#endif
macro_line|#ifndef NSEC_PER_SEC
DECL|macro|NSEC_PER_SEC
mdefine_line|#define NSEC_PER_SEC (1000000000L)
macro_line|#endif
macro_line|#ifndef NSEC_PER_USEC
DECL|macro|NSEC_PER_USEC
mdefine_line|#define NSEC_PER_USEC (1000L)
macro_line|#endif
multiline_comment|/*&n; * We want to do realistic conversions of time so we need to use the same&n; * values the update wall clock code uses as the jiffie size.  This value&n; * is: TICK_NSEC(TICK_USEC) (both of which are defined in timex.h).  This &n; * is a constant and is in nanoseconds.  We will used scaled math and&n; * with a scales defined here as SEC_JIFFIE_SC,  USEC_JIFFIE_SC and &n; * NSEC_JIFFIE_SC.  Note that these defines contain nothing but&n; * constants and so are computed at compile time.  SHIFT_HZ (computed in&n; * timex.h) adjusts the scaling for different HZ values.&n; */
DECL|macro|SEC_JIFFIE_SC
mdefine_line|#define SEC_JIFFIE_SC (30 - SHIFT_HZ)
DECL|macro|NSEC_JIFFIE_SC
mdefine_line|#define NSEC_JIFFIE_SC (SEC_JIFFIE_SC + 30)
DECL|macro|USEC_JIFFIE_SC
mdefine_line|#define USEC_JIFFIE_SC (SEC_JIFFIE_SC + 20)
DECL|macro|SEC_CONVERSION
mdefine_line|#define SEC_CONVERSION ((unsigned long)(((u64)NSEC_PER_SEC &lt;&lt; SEC_JIFFIE_SC) /&bslash;&n;                            (u64)TICK_NSEC(TICK_USEC))) 
DECL|macro|NSEC_CONVERSION
mdefine_line|#define NSEC_CONVERSION ((unsigned long)(((u64)1 &lt;&lt; NSEC_JIFFIE_SC) / &bslash;&n;                            (u64)TICK_NSEC(TICK_USEC))) 
DECL|macro|USEC_CONVERSION
mdefine_line|#define USEC_CONVERSION &bslash;&n;               ((unsigned long)(((u64)NSEC_PER_USEC &lt;&lt; USEC_JIFFIE_SC)/ &bslash;&n;                                 (u64)TICK_NSEC(TICK_USEC))) 
DECL|macro|MAX_SEC_IN_JIFFIES
mdefine_line|#define MAX_SEC_IN_JIFFIES &bslash;&n;    (u32)((u64)((u64)MAX_JIFFY_OFFSET * TICK_NSEC(TICK_USEC)) / NSEC_PER_SEC)
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
op_plus
id|TICK_NSEC
c_func
(paren
id|TICK_USEC
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sec
op_ge
id|MAX_SEC_IN_JIFFIES
)paren
r_return
id|MAX_JIFFY_OFFSET
suffix:semicolon
r_return
(paren
(paren
(paren
id|u64
)paren
id|sec
op_star
id|SEC_CONVERSION
)paren
op_plus
(paren
(paren
(paren
id|u64
)paren
id|nsec
op_star
id|NSEC_CONVERSION
)paren
op_rshift
(paren
id|NSEC_JIFFIE_SC
op_minus
id|SEC_JIFFIE_SC
)paren
)paren
)paren
op_rshift
id|SEC_JIFFIE_SC
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
multiline_comment|/*&n;&t; * Convert jiffies to nanoseconds and seperate with&n;&t; * one divide.&n;&t; */
id|u64
id|nsec
op_assign
(paren
id|u64
)paren
id|jiffies
op_star
id|TICK_NSEC
c_func
(paren
id|TICK_USEC
)paren
suffix:semicolon
id|value-&gt;tv_sec
op_assign
id|div_long_long_rem
c_func
(paren
id|nsec
comma
id|NSEC_PER_SEC
comma
op_amp
id|value-&gt;tv_nsec
)paren
suffix:semicolon
)brace
multiline_comment|/* Same for &quot;timeval&quot; */
r_static
id|__inline__
r_int
r_int
DECL|function|timeval_to_jiffies
id|timeval_to_jiffies
c_func
(paren
r_struct
id|timeval
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
id|usec
op_assign
id|value-&gt;tv_usec
op_plus
id|USEC_PER_SEC
op_div
id|HZ
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sec
op_ge
id|MAX_SEC_IN_JIFFIES
)paren
r_return
id|MAX_JIFFY_OFFSET
suffix:semicolon
r_return
(paren
(paren
(paren
id|u64
)paren
id|sec
op_star
id|SEC_CONVERSION
)paren
op_plus
(paren
(paren
(paren
id|u64
)paren
id|usec
op_star
id|USEC_CONVERSION
)paren
op_rshift
(paren
id|USEC_JIFFIE_SC
op_minus
id|SEC_JIFFIE_SC
)paren
)paren
)paren
op_rshift
id|SEC_JIFFIE_SC
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|jiffies_to_timeval
id|jiffies_to_timeval
c_func
(paren
r_int
r_int
id|jiffies
comma
r_struct
id|timeval
op_star
id|value
)paren
(brace
multiline_comment|/*&n;&t; * Convert jiffies to nanoseconds and seperate with&n;&t; * one divide.&n;&t; */
id|u64
id|nsec
op_assign
(paren
id|u64
)paren
id|jiffies
op_star
id|TICK_NSEC
c_func
(paren
id|TICK_USEC
)paren
suffix:semicolon
id|value-&gt;tv_sec
op_assign
id|div_long_long_rem
c_func
(paren
id|nsec
comma
id|NSEC_PER_SEC
comma
op_amp
id|value-&gt;tv_usec
)paren
suffix:semicolon
id|value-&gt;tv_usec
op_div_assign
id|NSEC_PER_USEC
suffix:semicolon
)brace
DECL|function|timespec_equal
r_static
id|__inline__
r_int
id|timespec_equal
c_func
(paren
r_struct
id|timespec
op_star
id|a
comma
r_struct
id|timespec
op_star
id|b
)paren
(brace
r_return
(paren
id|a-&gt;tv_sec
op_eq
id|b-&gt;tv_sec
)paren
op_logical_and
(paren
id|a-&gt;tv_nsec
op_eq
id|b-&gt;tv_nsec
)paren
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
id|timespec
id|xtime
suffix:semicolon
r_extern
r_struct
id|timespec
id|wall_to_monotonic
suffix:semicolon
r_extern
id|seqlock_t
id|xtime_lock
suffix:semicolon
DECL|function|get_seconds
r_static
r_inline
r_int
r_int
id|get_seconds
c_func
(paren
r_void
)paren
(brace
r_return
id|xtime.tv_sec
suffix:semicolon
)brace
r_struct
id|timespec
id|current_kernel_time
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|CURRENT_TIME
mdefine_line|#define CURRENT_TIME (current_kernel_time())
macro_line|#endif /* __KERNEL__ */
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
r_int
id|do_settimeofday
c_func
(paren
r_struct
id|timespec
op_star
id|tv
)paren
suffix:semicolon
r_extern
r_int
id|do_sys_settimeofday
c_func
(paren
r_struct
id|timespec
op_star
id|tv
comma
r_struct
id|timezone
op_star
id|tz
)paren
suffix:semicolon
r_extern
r_void
id|clock_was_set
c_func
(paren
r_void
)paren
suffix:semicolon
singleline_comment|// call when ever the clock is set
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
r_extern
r_int
id|do_nanosleep
c_func
(paren
r_struct
id|timespec
op_star
id|t
)paren
suffix:semicolon
r_extern
r_int
id|do_utimes
c_func
(paren
r_char
id|__user
op_star
id|filename
comma
r_struct
id|timeval
op_star
id|times
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
multiline_comment|/*&n; * The IDs of the various system clocks (for POSIX.1b interval timers).&n; */
DECL|macro|CLOCK_REALTIME
mdefine_line|#define CLOCK_REALTIME&t;&t;  0
DECL|macro|CLOCK_MONOTONIC
mdefine_line|#define CLOCK_MONOTONIC&t;  1
DECL|macro|CLOCK_PROCESS_CPUTIME_ID
mdefine_line|#define CLOCK_PROCESS_CPUTIME_ID 2
DECL|macro|CLOCK_THREAD_CPUTIME_ID
mdefine_line|#define CLOCK_THREAD_CPUTIME_ID&t; 3
DECL|macro|CLOCK_REALTIME_HR
mdefine_line|#define CLOCK_REALTIME_HR&t; 4
DECL|macro|CLOCK_MONOTONIC_HR
mdefine_line|#define CLOCK_MONOTONIC_HR&t;  5
DECL|macro|MAX_CLOCKS
mdefine_line|#define MAX_CLOCKS 6
DECL|macro|CLOCKS_MASK
mdefine_line|#define CLOCKS_MASK  (CLOCK_REALTIME | CLOCK_MONOTONIC | &bslash;&n;                     CLOCK_REALTIME_HR | CLOCK_MONOTONIC_HR)
DECL|macro|CLOCKS_MONO
mdefine_line|#define CLOCKS_MONO (CLOCK_MONOTONIC &amp; CLOCK_MONOTONIC_HR)
multiline_comment|/*&n; * The various flags for setting POSIX.1b interval timers.&n; */
DECL|macro|TIMER_ABSTIME
mdefine_line|#define TIMER_ABSTIME 0x01
macro_line|#endif
eof
