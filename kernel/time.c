multiline_comment|/*&n; *  linux/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  This file contains the interface functions for the various&n; *  time related system calls: time, stime, gettimeofday, settimeofday,&n; *&t;&t;&t;       adjtime&n; */
multiline_comment|/*&n; * Modification history kernel/time.c&n; * &n; * 1993-09-02    Philip Gladstone&n; *      Created file with time related functions from sched.c and adjtimex() &n; * 1993-10-08    Torsten Duwe&n; *      adjtime interface update and CMOS clock write code&n; * 1995-08-13    Torsten Duwe&n; *      kernel PLL updated to 1994-12-13 specs (rfc-1589)&n; * 1999-01-16    Ulrich Windl&n; *&t;Introduced error checking for many cases in adjtimex().&n; *&t;Updated NTP code according to technical memorandum Jan &squot;96&n; *&t;&quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; *&t;Allow time_constant larger than MAXTC(6) for NTP v4 (MAXTC == 10)&n; *&t;(Even though the technical memorandum forbids it)&n; */
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* &n; * The timezone where the local system is located.  Used as a default by some&n; * programs who obtain this value by using gettimeofday.&n; */
DECL|variable|sys_tz
r_struct
id|timezone
id|sys_tz
suffix:semicolon
multiline_comment|/* The xtime_lock is not only serializing the xtime read/writes but it&squot;s also&n;   serializing all accesses to the global NTP variables now. */
r_extern
id|rwlock_t
id|xtime_lock
suffix:semicolon
macro_line|#if !defined(__alpha__) &amp;&amp; !defined(__ia64__)
multiline_comment|/*&n; * sys_time() can be implemented in user-level using&n; * sys_gettimeofday().  Is this for backwards compatibility?  If so,&n; * why not move it into the appropriate arch directory (for those&n; * architectures that need it).&n; *&n; * XXX This function is NOT 64-bit clean!&n; */
DECL|function|sys_time
id|asmlinkage
r_int
id|sys_time
c_func
(paren
r_int
op_star
id|tloc
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* SMP: This is fairly trivial. We grab CURRENT_TIME and &n;&t;   stuff it to user space. No side effects */
id|i
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|tloc
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|i
comma
id|tloc
)paren
)paren
id|i
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_stime() can be implemented in user-level using&n; * sys_settimeofday().  Is this for backwards compatibility?  If so,&n; * why not move it into the appropriate arch directory (for those&n; * architectures that need it).&n; */
DECL|function|sys_stime
id|asmlinkage
r_int
id|sys_stime
c_func
(paren
r_int
op_star
id|tptr
)paren
(brace
r_int
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|value
comma
id|tptr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|write_lock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
id|value
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
id|time_adjust
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* stop active adjtime() */
id|time_status
op_or_assign
id|STA_UNSYNC
suffix:semicolon
id|time_maxerror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
id|time_esterror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sys_gettimeofday
id|asmlinkage
r_int
id|sys_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
comma
r_struct
id|timezone
op_star
id|tz
)paren
(brace
r_if
c_cond
(paren
id|tv
)paren
(brace
r_struct
id|timeval
id|ktv
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|ktv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|tv
comma
op_amp
id|ktv
comma
r_sizeof
(paren
id|ktv
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tz
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|tz
comma
op_amp
id|sys_tz
comma
r_sizeof
(paren
id|sys_tz
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
multiline_comment|/*&n; * Adjust the time obtained from the CMOS to be UTC time instead of&n; * local time.&n; * &n; * This is ugly, but preferable to the alternatives.  Otherwise we&n; * would either need to write a program to do it in /etc/rc (and risk&n; * confusion if the program gets run more than once; it would also be &n; * hard to make the program warp the clock precisely n hours)  or&n; * compile in the timezone information into the kernel.  Bad, bad....&n; *&n; *              &t;&t;&t;&t;- TYT, 1992-01-01&n; *&n; * The best thing to do is to keep the CMOS clock in universal time (UTC)&n; * as real UNIX machines always do it. This avoids all headaches about&n; * daylight saving times and warping kernel clocks.&n; */
DECL|function|warp_clock
r_inline
r_static
r_void
id|warp_clock
c_func
(paren
r_void
)paren
(brace
id|write_lock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|xtime.tv_sec
op_add_assign
id|sys_tz.tz_minuteswest
op_star
l_int|60
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * In case for some reason the CMOS clock has not already been running&n; * in UTC, but in some local time: The first time we set the timezone,&n; * we will warp the clock so that it is ticking UTC time instead of&n; * local time. Presumably, if someone is setting the timezone then we&n; * are running in an environment where the programs understand about&n; * timezones. This should be done at boot time in the /etc/rc script,&n; * as soon as possible, so that the clock can be set right. Otherwise,&n; * various programs will get confused when the clock gets warped.&n; */
DECL|function|do_sys_settimeofday
r_int
id|do_sys_settimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
comma
r_struct
id|timezone
op_star
id|tz
)paren
(brace
r_static
r_int
id|firsttime
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|tz
)paren
(brace
multiline_comment|/* SMP safe, global irq locking makes it work. */
id|sys_tz
op_assign
op_star
id|tz
suffix:semicolon
r_if
c_cond
(paren
id|firsttime
)paren
(brace
id|firsttime
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tv
)paren
id|warp_clock
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|tv
)paren
(brace
multiline_comment|/* SMP safe, again the code in arch/foo/time.c should&n;&t;&t; * globally block out interrupts when it runs.&n;&t;&t; */
id|do_settimeofday
c_func
(paren
id|tv
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_settimeofday
id|asmlinkage
r_int
id|sys_settimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
comma
r_struct
id|timezone
op_star
id|tz
)paren
(brace
r_struct
id|timeval
id|new_tv
suffix:semicolon
r_struct
id|timezone
id|new_tz
suffix:semicolon
r_if
c_cond
(paren
id|tv
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|new_tv
comma
id|tv
comma
r_sizeof
(paren
op_star
id|tv
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tz
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|new_tz
comma
id|tz
comma
r_sizeof
(paren
op_star
id|tz
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|do_sys_settimeofday
c_func
(paren
id|tv
ques
c_cond
op_amp
id|new_tv
suffix:colon
l_int|NULL
comma
id|tz
ques
c_cond
op_amp
id|new_tz
suffix:colon
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|pps_offset
r_int
id|pps_offset
suffix:semicolon
multiline_comment|/* pps time offset (us) */
DECL|variable|pps_jitter
r_int
id|pps_jitter
op_assign
id|MAXTIME
suffix:semicolon
multiline_comment|/* time dispersion (jitter) (us) */
DECL|variable|pps_freq
r_int
id|pps_freq
suffix:semicolon
multiline_comment|/* frequency offset (scaled ppm) */
DECL|variable|pps_stabil
r_int
id|pps_stabil
op_assign
id|MAXFREQ
suffix:semicolon
multiline_comment|/* frequency dispersion (scaled ppm) */
DECL|variable|pps_valid
r_int
id|pps_valid
op_assign
id|PPS_VALID
suffix:semicolon
multiline_comment|/* pps signal watchdog counter */
DECL|variable|pps_shift
r_int
id|pps_shift
op_assign
id|PPS_SHIFT
suffix:semicolon
multiline_comment|/* interval duration (s) (shift) */
DECL|variable|pps_jitcnt
r_int
id|pps_jitcnt
suffix:semicolon
multiline_comment|/* jitter limit exceeded */
DECL|variable|pps_calcnt
r_int
id|pps_calcnt
suffix:semicolon
multiline_comment|/* calibration intervals */
DECL|variable|pps_errcnt
r_int
id|pps_errcnt
suffix:semicolon
multiline_comment|/* calibration errors */
DECL|variable|pps_stbcnt
r_int
id|pps_stbcnt
suffix:semicolon
multiline_comment|/* stability limit exceeded */
multiline_comment|/* hook for a loadable hardpps kernel module */
DECL|variable|hardpps_ptr
r_void
(paren
op_star
id|hardpps_ptr
)paren
(paren
r_struct
id|timeval
op_star
)paren
suffix:semicolon
multiline_comment|/* adjtimex mainly allows reading (and writing, if superuser) of&n; * kernel time-keeping variables. used by xntpd.&n; */
DECL|function|do_adjtimex
r_int
id|do_adjtimex
c_func
(paren
r_struct
id|timex
op_star
id|txc
)paren
(brace
r_int
id|ltemp
comma
id|mtemp
comma
id|save_adjust
suffix:semicolon
r_int
id|result
suffix:semicolon
multiline_comment|/* In order to modify anything, you gotta be super-user! */
r_if
c_cond
(paren
id|txc-&gt;modes
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* Now we validate the data before disabling interrupts */
r_if
c_cond
(paren
id|txc-&gt;modes
op_ne
id|ADJ_OFFSET_SINGLESHOT
op_logical_and
(paren
id|txc-&gt;modes
op_amp
id|ADJ_OFFSET
)paren
)paren
multiline_comment|/* adjustment Offset limited to +- .512 seconds */
r_if
c_cond
(paren
id|txc-&gt;offset
op_le
op_minus
id|MAXPHASE
op_logical_or
id|txc-&gt;offset
op_ge
id|MAXPHASE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* if the quartz is off by more than 10% something is VERY wrong ! */
r_if
c_cond
(paren
id|txc-&gt;modes
op_amp
id|ADJ_TICK
)paren
r_if
c_cond
(paren
id|txc-&gt;tick
template_param
l_int|1100000
op_div
id|HZ
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|write_lock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|result
op_assign
id|time_state
suffix:semicolon
multiline_comment|/* mostly `TIME_OK&squot; */
multiline_comment|/* Save for later - semantics of adjtime is to return old value */
id|save_adjust
op_assign
id|time_adjust
suffix:semicolon
macro_line|#if 0&t;/* STA_CLOCKERR is never set yet */
id|time_status
op_and_assign
op_complement
id|STA_CLOCKERR
suffix:semicolon
multiline_comment|/* reset STA_CLOCKERR */
macro_line|#endif
multiline_comment|/* If there are input parameters, then process them */
r_if
c_cond
(paren
id|txc-&gt;modes
)paren
(brace
r_if
c_cond
(paren
id|txc-&gt;modes
op_amp
id|ADJ_STATUS
)paren
multiline_comment|/* only set allowed bits */
id|time_status
op_assign
(paren
id|txc-&gt;status
op_amp
op_complement
id|STA_RONLY
)paren
op_or
(paren
id|time_status
op_amp
id|STA_RONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|txc-&gt;modes
op_amp
id|ADJ_FREQUENCY
)paren
(brace
multiline_comment|/* p. 22 */
r_if
c_cond
(paren
id|txc-&gt;freq
OG
id|MAXFREQ
op_logical_or
id|txc-&gt;freq
OL
op_minus
id|MAXFREQ
)paren
(brace
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
id|time_freq
op_assign
id|txc-&gt;freq
op_minus
id|pps_freq
suffix:semicolon
)brace
r_if
c_cond
(paren
id|txc-&gt;modes
op_amp
id|ADJ_MAXERROR
)paren
(brace
r_if
c_cond
(paren
id|txc-&gt;maxerror
OL
l_int|0
op_logical_or
id|txc-&gt;maxerror
op_ge
id|NTP_PHASE_LIMIT
)paren
(brace
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
id|time_maxerror
op_assign
id|txc-&gt;maxerror
suffix:semicolon
)brace
r_if
c_cond
(paren
id|txc-&gt;modes
op_amp
id|ADJ_ESTERROR
)paren
(brace
r_if
c_cond
(paren
id|txc-&gt;esterror
OL
l_int|0
op_logical_or
id|txc-&gt;esterror
op_ge
id|NTP_PHASE_LIMIT
)paren
(brace
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
id|time_esterror
op_assign
id|txc-&gt;esterror
suffix:semicolon
)brace
r_if
c_cond
(paren
id|txc-&gt;modes
op_amp
id|ADJ_TIMECONST
)paren
(brace
multiline_comment|/* p. 24 */
r_if
c_cond
(paren
id|txc-&gt;constant
OL
l_int|0
)paren
(brace
multiline_comment|/* NTP v4 uses values &gt; 6 */
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
id|time_constant
op_assign
id|txc-&gt;constant
suffix:semicolon
)brace
r_if
c_cond
(paren
id|txc-&gt;modes
op_amp
id|ADJ_OFFSET
)paren
(brace
multiline_comment|/* values checked earlier */
r_if
c_cond
(paren
id|txc-&gt;modes
op_eq
id|ADJ_OFFSET_SINGLESHOT
)paren
(brace
multiline_comment|/* adjtime() is independent from ntp_adjtime() */
id|time_adjust
op_assign
id|txc-&gt;offset
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|time_status
op_amp
(paren
id|STA_PLL
op_or
id|STA_PPSTIME
)paren
)paren
(brace
id|ltemp
op_assign
(paren
id|time_status
op_amp
(paren
id|STA_PPSTIME
op_or
id|STA_PPSSIGNAL
)paren
)paren
op_eq
(paren
id|STA_PPSTIME
op_or
id|STA_PPSSIGNAL
)paren
ques
c_cond
id|pps_offset
suffix:colon
id|txc-&gt;offset
suffix:semicolon
multiline_comment|/*&n;&t;&t;     * Scale the phase adjustment and&n;&t;&t;     * clamp to the operating range.&n;&t;&t;     */
r_if
c_cond
(paren
id|ltemp
OG
id|MAXPHASE
)paren
id|time_offset
op_assign
id|MAXPHASE
op_lshift
id|SHIFT_UPDATE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ltemp
OL
op_minus
id|MAXPHASE
)paren
id|time_offset
op_assign
op_minus
(paren
id|MAXPHASE
op_lshift
id|SHIFT_UPDATE
)paren
suffix:semicolon
r_else
id|time_offset
op_assign
id|ltemp
op_lshift
id|SHIFT_UPDATE
suffix:semicolon
multiline_comment|/*&n;&t;&t;     * Select whether the frequency is to be controlled&n;&t;&t;     * and in which mode (PLL or FLL). Clamp to the operating&n;&t;&t;     * range. Ugly multiply/divide should be replaced someday.&n;&t;&t;     */
r_if
c_cond
(paren
id|time_status
op_amp
id|STA_FREQHOLD
op_logical_or
id|time_reftime
op_eq
l_int|0
)paren
id|time_reftime
op_assign
id|xtime.tv_sec
suffix:semicolon
id|mtemp
op_assign
id|xtime.tv_sec
op_minus
id|time_reftime
suffix:semicolon
id|time_reftime
op_assign
id|xtime.tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|time_status
op_amp
id|STA_FLL
)paren
(brace
r_if
c_cond
(paren
id|mtemp
op_ge
id|MINSEC
)paren
(brace
id|ltemp
op_assign
(paren
id|time_offset
op_div
id|mtemp
)paren
op_lshift
(paren
id|SHIFT_USEC
op_minus
id|SHIFT_UPDATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ltemp
OL
l_int|0
)paren
id|time_freq
op_sub_assign
op_minus
id|ltemp
op_rshift
id|SHIFT_KH
suffix:semicolon
r_else
id|time_freq
op_add_assign
id|ltemp
op_rshift
id|SHIFT_KH
suffix:semicolon
)brace
r_else
multiline_comment|/* calibration interval too short (p. 12) */
id|result
op_assign
id|TIME_ERROR
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* PLL mode */
r_if
c_cond
(paren
id|mtemp
OL
id|MAXSEC
)paren
(brace
id|ltemp
op_mul_assign
id|mtemp
suffix:semicolon
r_if
c_cond
(paren
id|ltemp
OL
l_int|0
)paren
id|time_freq
op_sub_assign
op_minus
id|ltemp
op_rshift
(paren
id|time_constant
op_plus
id|time_constant
op_plus
id|SHIFT_KF
op_minus
id|SHIFT_USEC
)paren
suffix:semicolon
r_else
id|time_freq
op_add_assign
id|ltemp
op_rshift
(paren
id|time_constant
op_plus
id|time_constant
op_plus
id|SHIFT_KF
op_minus
id|SHIFT_USEC
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* calibration interval too long (p. 12) */
id|result
op_assign
id|TIME_ERROR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|time_freq
OG
id|time_tolerance
)paren
id|time_freq
op_assign
id|time_tolerance
suffix:semicolon
r_else
r_if
c_cond
(paren
id|time_freq
OL
op_minus
id|time_tolerance
)paren
id|time_freq
op_assign
op_minus
id|time_tolerance
suffix:semicolon
)brace
multiline_comment|/* STA_PLL || STA_PPSTIME */
)brace
multiline_comment|/* txc-&gt;modes &amp; ADJ_OFFSET */
r_if
c_cond
(paren
id|txc-&gt;modes
op_amp
id|ADJ_TICK
)paren
(brace
multiline_comment|/* if the quartz is off by more than 10% something is&n;&t;&t;   VERY wrong ! */
r_if
c_cond
(paren
id|txc-&gt;tick
template_param
l_int|1100000
op_div
id|HZ
)paren
(brace
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
id|tick
op_assign
id|txc-&gt;tick
suffix:semicolon
)brace
)brace
multiline_comment|/* txc-&gt;modes */
id|leave
suffix:colon
r_if
c_cond
(paren
(paren
id|time_status
op_amp
(paren
id|STA_UNSYNC
op_or
id|STA_CLOCKERR
)paren
)paren
op_ne
l_int|0
op_logical_or
(paren
(paren
id|time_status
op_amp
(paren
id|STA_PPSFREQ
op_or
id|STA_PPSTIME
)paren
)paren
op_ne
l_int|0
op_logical_and
(paren
id|time_status
op_amp
id|STA_PPSSIGNAL
)paren
op_eq
l_int|0
)paren
multiline_comment|/* p. 24, (b) */
op_logical_or
(paren
(paren
id|time_status
op_amp
(paren
id|STA_PPSTIME
op_or
id|STA_PPSJITTER
)paren
)paren
op_eq
(paren
id|STA_PPSTIME
op_or
id|STA_PPSJITTER
)paren
)paren
multiline_comment|/* p. 24, (c) */
op_logical_or
(paren
(paren
id|time_status
op_amp
id|STA_PPSFREQ
)paren
op_ne
l_int|0
op_logical_and
(paren
id|time_status
op_amp
(paren
id|STA_PPSWANDER
op_or
id|STA_PPSERROR
)paren
)paren
op_ne
l_int|0
)paren
)paren
multiline_comment|/* p. 24, (d) */
id|result
op_assign
id|TIME_ERROR
suffix:semicolon
r_if
c_cond
(paren
(paren
id|txc-&gt;modes
op_amp
id|ADJ_OFFSET_SINGLESHOT
)paren
op_eq
id|ADJ_OFFSET_SINGLESHOT
)paren
id|txc-&gt;offset
op_assign
id|save_adjust
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|time_offset
OL
l_int|0
)paren
id|txc-&gt;offset
op_assign
op_minus
(paren
op_minus
id|time_offset
op_rshift
id|SHIFT_UPDATE
)paren
suffix:semicolon
r_else
id|txc-&gt;offset
op_assign
id|time_offset
op_rshift
id|SHIFT_UPDATE
suffix:semicolon
)brace
id|txc-&gt;freq
op_assign
id|time_freq
op_plus
id|pps_freq
suffix:semicolon
id|txc-&gt;maxerror
op_assign
id|time_maxerror
suffix:semicolon
id|txc-&gt;esterror
op_assign
id|time_esterror
suffix:semicolon
id|txc-&gt;status
op_assign
id|time_status
suffix:semicolon
id|txc-&gt;constant
op_assign
id|time_constant
suffix:semicolon
id|txc-&gt;precision
op_assign
id|time_precision
suffix:semicolon
id|txc-&gt;tolerance
op_assign
id|time_tolerance
suffix:semicolon
id|txc-&gt;tick
op_assign
id|tick
suffix:semicolon
id|txc-&gt;ppsfreq
op_assign
id|pps_freq
suffix:semicolon
id|txc-&gt;jitter
op_assign
id|pps_jitter
op_rshift
id|PPS_AVG
suffix:semicolon
id|txc-&gt;shift
op_assign
id|pps_shift
suffix:semicolon
id|txc-&gt;stabil
op_assign
id|pps_stabil
suffix:semicolon
id|txc-&gt;jitcnt
op_assign
id|pps_jitcnt
suffix:semicolon
id|txc-&gt;calcnt
op_assign
id|pps_calcnt
suffix:semicolon
id|txc-&gt;errcnt
op_assign
id|pps_errcnt
suffix:semicolon
id|txc-&gt;stbcnt
op_assign
id|pps_stbcnt
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|txc-&gt;time
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|sys_adjtimex
id|asmlinkage
r_int
id|sys_adjtimex
c_func
(paren
r_struct
id|timex
op_star
id|txc_p
)paren
(brace
r_struct
id|timex
id|txc
suffix:semicolon
multiline_comment|/* Local copy of parameter */
r_int
id|ret
suffix:semicolon
multiline_comment|/* Copy the user data space into the kernel copy&n;&t; * structure. But bear in mind that the structures&n;&t; * may change&n;&t; */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|txc
comma
id|txc_p
comma
r_sizeof
(paren
r_struct
id|timex
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|ret
op_assign
id|do_adjtimex
c_func
(paren
op_amp
id|txc
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|txc_p
comma
op_amp
id|txc
comma
r_sizeof
(paren
r_struct
id|timex
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|ret
suffix:semicolon
)brace
eof
