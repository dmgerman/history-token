multiline_comment|/*****************************************************************************&n; *                                                                           *&n; * Copyright (c) David L. Mills 1993                                         *&n; *                                                                           *&n; * Permission to use, copy, modify, and distribute this software and its     *&n; * documentation for any purpose and without fee is hereby granted, provided *&n; * that the above copyright notice appears in all copies and that both the   *&n; * copyright notice and this permission notice appear in supporting          *&n; * documentation, and that the name University of Delaware not be used in    *&n; * advertising or publicity pertaining to distribution of the software       *&n; * without specific, written prior permission.  The University of Delaware   *&n; * makes no representations about the suitability this software for any      *&n; * purpose.  It is provided &quot;as is&quot; without express or implied warranty.     *&n; *                                                                           *&n; *****************************************************************************/
multiline_comment|/*&n; * Modification history timex.h&n; *&n; * 29 Dec 97&t;Russell King&n; *&t;Moved CLOCK_TICK_RATE, CLOCK_TICK_FACTOR and FINETUNE to asm/timex.h&n; *&t;for ARM machines&n; *&n; *  9 Jan 97    Adrian Sun&n; *      Shifted LATCH define to allow access to alpha machines.&n; *&n; * 26 Sep 94&t;David L. Mills&n; *&t;Added defines for hybrid phase/frequency-lock loop.&n; *&n; * 19 Mar 94&t;David L. Mills&n; *&t;Moved defines from kernel routines to header file and added new&n; *&t;defines for PPS phase-lock loop.&n; *&n; * 20 Feb 94&t;David L. Mills&n; *&t;Revised status codes and structures for external clock and PPS&n; *&t;signal discipline.&n; *&n; * 28 Nov 93&t;David L. Mills&n; *&t;Adjusted parameters to improve stability and increase poll&n; *&t;interval.&n; *&n; * 17 Sep 93    David L. Mills&n; *      Created file $NTP/include/sys/timex.h&n; * 07 Oct 93    Torsten Duwe&n; *      Derived linux/timex.h&n; * 1995-08-13    Torsten Duwe&n; *      kernel PLL updated to 1994-12-13 specs (rfc-1589)&n; * 1997-08-30    Ulrich Windl&n; *      Added new constant NTP_PHASE_LIMIT&n; */
macro_line|#ifndef _LINUX_TIMEX_H
DECL|macro|_LINUX_TIMEX_H
mdefine_line|#define _LINUX_TIMEX_H
macro_line|#include &lt;asm/param.h&gt;
multiline_comment|/*&n; * The following defines establish the engineering parameters of the PLL&n; * model. The HZ variable establishes the timer interrupt frequency, 100 Hz&n; * for the SunOS kernel, 256 Hz for the Ultrix kernel and 1024 Hz for the&n; * OSF/1 kernel. The SHIFT_HZ define expresses the same value as the&n; * nearest power of two in order to avoid hardware multiply operations.&n; */
macro_line|#if HZ &gt;= 24 &amp;&amp; HZ &lt; 48
DECL|macro|SHIFT_HZ
macro_line|# define SHIFT_HZ&t;5
macro_line|#elif HZ &gt;= 48 &amp;&amp; HZ &lt; 96
DECL|macro|SHIFT_HZ
macro_line|# define SHIFT_HZ&t;6
macro_line|#elif HZ &gt;= 96 &amp;&amp; HZ &lt; 192
DECL|macro|SHIFT_HZ
macro_line|# define SHIFT_HZ&t;7
macro_line|#elif HZ &gt;= 192 &amp;&amp; HZ &lt; 384
DECL|macro|SHIFT_HZ
macro_line|# define SHIFT_HZ&t;8
macro_line|#elif HZ &gt;= 384 &amp;&amp; HZ &lt; 768
DECL|macro|SHIFT_HZ
macro_line|# define SHIFT_HZ&t;9
macro_line|#elif HZ &gt;= 768 &amp;&amp; HZ &lt; 1536
DECL|macro|SHIFT_HZ
macro_line|# define SHIFT_HZ&t;10
macro_line|#else
macro_line|# error You lose.
macro_line|#endif
multiline_comment|/*&n; * SHIFT_KG and SHIFT_KF establish the damping of the PLL and are chosen&n; * for a slightly underdamped convergence characteristic. SHIFT_KH&n; * establishes the damping of the FLL and is chosen by wisdom and black&n; * art.&n; *&n; * MAXTC establishes the maximum time constant of the PLL. With the&n; * SHIFT_KG and SHIFT_KF values given and a time constant range from&n; * zero to MAXTC, the PLL will converge in 15 minutes to 16 hours,&n; * respectively.&n; */
DECL|macro|SHIFT_KG
mdefine_line|#define SHIFT_KG 6&t;&t;/* phase factor (shift) */
DECL|macro|SHIFT_KF
mdefine_line|#define SHIFT_KF 16&t;&t;/* PLL frequency factor (shift) */
DECL|macro|SHIFT_KH
mdefine_line|#define SHIFT_KH 2&t;&t;/* FLL frequency factor (shift) */
DECL|macro|MAXTC
mdefine_line|#define MAXTC 6&t;&t;&t;/* maximum time constant (shift) */
multiline_comment|/*&n; * The SHIFT_SCALE define establishes the decimal point of the time_phase&n; * variable which serves as an extension to the low-order bits of the&n; * system clock variable. The SHIFT_UPDATE define establishes the decimal&n; * point of the time_offset variable which represents the current offset&n; * with respect to standard time. The FINEUSEC define represents 1 usec in&n; * scaled units.&n; *&n; * SHIFT_USEC defines the scaling (shift) of the time_freq and&n; * time_tolerance variables, which represent the current frequency&n; * offset and maximum frequency tolerance.&n; *&n; * FINEUSEC is 1 us in SHIFT_UPDATE units of the time_phase variable.&n; */
DECL|macro|SHIFT_SCALE
mdefine_line|#define SHIFT_SCALE 22&t;&t;/* phase scale (shift) */
DECL|macro|SHIFT_UPDATE
mdefine_line|#define SHIFT_UPDATE (SHIFT_KG + MAXTC) /* time offset scale (shift) */
DECL|macro|SHIFT_USEC
mdefine_line|#define SHIFT_USEC 16&t;&t;/* frequency offset scale (shift) */
DECL|macro|FINEUSEC
mdefine_line|#define FINEUSEC (1L &lt;&lt; SHIFT_SCALE) /* 1 us in phase units */
DECL|macro|MAXPHASE
mdefine_line|#define MAXPHASE 512000L        /* max phase error (us) */
DECL|macro|MAXFREQ
mdefine_line|#define MAXFREQ (512L &lt;&lt; SHIFT_USEC)  /* max frequency error (ppm) */
DECL|macro|MAXTIME
mdefine_line|#define MAXTIME (200L &lt;&lt; PPS_AVG) /* max PPS error (jitter) (200 us) */
DECL|macro|MINSEC
mdefine_line|#define MINSEC 16L              /* min interval between updates (s) */
DECL|macro|MAXSEC
mdefine_line|#define MAXSEC 1200L            /* max interval between updates (s) */
DECL|macro|NTP_PHASE_LIMIT
mdefine_line|#define&t;NTP_PHASE_LIMIT&t;(MAXPHASE &lt;&lt; 5)&t;/* beyond max. dispersion */
multiline_comment|/*&n; * The following defines are used only if a pulse-per-second (PPS)&n; * signal is available and connected via a modem control lead, such as&n; * produced by the optional ppsclock feature incorporated in the Sun&n; * asynch driver. They establish the design parameters of the frequency-&n; * lock loop used to discipline the CPU clock oscillator to the PPS&n; * signal.&n; *&n; * PPS_AVG is the averaging factor for the frequency loop, as well as&n; * the time and frequency dispersion.&n; *&n; * PPS_SHIFT and PPS_SHIFTMAX specify the minimum and maximum&n; * calibration intervals, respectively, in seconds as a power of two.&n; *&n; * PPS_VALID is the maximum interval before the PPS signal is considered&n; * invalid and protocol updates used directly instead.&n; *&n; * MAXGLITCH is the maximum interval before a time offset of more than&n; * MAXTIME is believed.&n; */
DECL|macro|PPS_AVG
mdefine_line|#define PPS_AVG 2&t;&t;/* pps averaging constant (shift) */
DECL|macro|PPS_SHIFT
mdefine_line|#define PPS_SHIFT 2&t;&t;/* min interval duration (s) (shift) */
DECL|macro|PPS_SHIFTMAX
mdefine_line|#define PPS_SHIFTMAX 8&t;&t;/* max interval duration (s) (shift) */
DECL|macro|PPS_VALID
mdefine_line|#define PPS_VALID 120&t;&t;/* pps signal watchdog max (s) */
DECL|macro|MAXGLITCH
mdefine_line|#define MAXGLITCH 30&t;&t;/* pps signal glitch max (s) */
multiline_comment|/*&n; * Pick up the architecture specific timex specifications&n; */
macro_line|#include &lt;asm/timex.h&gt;
multiline_comment|/* LATCH is used in the interval timer and ftape setup. */
DECL|macro|LATCH
mdefine_line|#define LATCH  ((CLOCK_TICK_RATE + HZ/2) / HZ)&t;/* For divider */
multiline_comment|/*&n; * syscall interface - used (mainly by NTP daemon)&n; * to discipline kernel clock oscillator&n; */
DECL|struct|timex
r_struct
id|timex
(brace
DECL|member|modes
r_int
r_int
id|modes
suffix:semicolon
multiline_comment|/* mode selector */
DECL|member|offset
r_int
id|offset
suffix:semicolon
multiline_comment|/* time offset (usec) */
DECL|member|freq
r_int
id|freq
suffix:semicolon
multiline_comment|/* frequency offset (scaled ppm) */
DECL|member|maxerror
r_int
id|maxerror
suffix:semicolon
multiline_comment|/* maximum error (usec) */
DECL|member|esterror
r_int
id|esterror
suffix:semicolon
multiline_comment|/* estimated error (usec) */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* clock command/status */
DECL|member|constant
r_int
id|constant
suffix:semicolon
multiline_comment|/* pll time constant */
DECL|member|precision
r_int
id|precision
suffix:semicolon
multiline_comment|/* clock precision (usec) (read only) */
DECL|member|tolerance
r_int
id|tolerance
suffix:semicolon
multiline_comment|/* clock frequency tolerance (ppm)&n;&t;&t;&t;&t; * (read only)&n;&t;&t;&t;&t; */
DECL|member|time
r_struct
id|timeval
id|time
suffix:semicolon
multiline_comment|/* (read only) */
DECL|member|tick
r_int
id|tick
suffix:semicolon
multiline_comment|/* (modified) usecs between clock ticks */
DECL|member|ppsfreq
r_int
id|ppsfreq
suffix:semicolon
multiline_comment|/* pps frequency (scaled ppm) (ro) */
DECL|member|jitter
r_int
id|jitter
suffix:semicolon
multiline_comment|/* pps jitter (us) (ro) */
DECL|member|shift
r_int
id|shift
suffix:semicolon
multiline_comment|/* interval duration (s) (shift) (ro) */
DECL|member|stabil
r_int
id|stabil
suffix:semicolon
multiline_comment|/* pps stability (scaled ppm) (ro) */
DECL|member|jitcnt
r_int
id|jitcnt
suffix:semicolon
multiline_comment|/* jitter limit exceeded (ro) */
DECL|member|calcnt
r_int
id|calcnt
suffix:semicolon
multiline_comment|/* calibration intervals (ro) */
DECL|member|errcnt
r_int
id|errcnt
suffix:semicolon
multiline_comment|/* calibration errors (ro) */
DECL|member|stbcnt
r_int
id|stbcnt
suffix:semicolon
multiline_comment|/* stability limit exceeded (ro) */
r_int
suffix:colon
l_int|32
suffix:semicolon
r_int
suffix:colon
l_int|32
suffix:semicolon
r_int
suffix:colon
l_int|32
suffix:semicolon
r_int
suffix:colon
l_int|32
suffix:semicolon
r_int
suffix:colon
l_int|32
suffix:semicolon
r_int
suffix:colon
l_int|32
suffix:semicolon
r_int
suffix:colon
l_int|32
suffix:semicolon
r_int
suffix:colon
l_int|32
suffix:semicolon
r_int
suffix:colon
l_int|32
suffix:semicolon
r_int
suffix:colon
l_int|32
suffix:semicolon
r_int
suffix:colon
l_int|32
suffix:semicolon
r_int
suffix:colon
l_int|32
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Mode codes (timex.mode)&n; */
DECL|macro|ADJ_OFFSET
mdefine_line|#define ADJ_OFFSET&t;&t;0x0001&t;/* time offset */
DECL|macro|ADJ_FREQUENCY
mdefine_line|#define ADJ_FREQUENCY&t;&t;0x0002&t;/* frequency offset */
DECL|macro|ADJ_MAXERROR
mdefine_line|#define ADJ_MAXERROR&t;&t;0x0004&t;/* maximum time error */
DECL|macro|ADJ_ESTERROR
mdefine_line|#define ADJ_ESTERROR&t;&t;0x0008&t;/* estimated time error */
DECL|macro|ADJ_STATUS
mdefine_line|#define ADJ_STATUS&t;&t;0x0010&t;/* clock status */
DECL|macro|ADJ_TIMECONST
mdefine_line|#define ADJ_TIMECONST&t;&t;0x0020&t;/* pll time constant */
DECL|macro|ADJ_TICK
mdefine_line|#define ADJ_TICK&t;&t;0x4000&t;/* tick value */
DECL|macro|ADJ_OFFSET_SINGLESHOT
mdefine_line|#define ADJ_OFFSET_SINGLESHOT&t;0x8001&t;/* old-fashioned adjtime */
multiline_comment|/* xntp 3.4 compatibility names */
DECL|macro|MOD_OFFSET
mdefine_line|#define MOD_OFFSET&t;ADJ_OFFSET
DECL|macro|MOD_FREQUENCY
mdefine_line|#define MOD_FREQUENCY&t;ADJ_FREQUENCY
DECL|macro|MOD_MAXERROR
mdefine_line|#define MOD_MAXERROR&t;ADJ_MAXERROR
DECL|macro|MOD_ESTERROR
mdefine_line|#define MOD_ESTERROR&t;ADJ_ESTERROR
DECL|macro|MOD_STATUS
mdefine_line|#define MOD_STATUS&t;ADJ_STATUS
DECL|macro|MOD_TIMECONST
mdefine_line|#define MOD_TIMECONST&t;ADJ_TIMECONST
DECL|macro|MOD_CLKB
mdefine_line|#define MOD_CLKB&t;ADJ_TICK
DECL|macro|MOD_CLKA
mdefine_line|#define MOD_CLKA&t;ADJ_OFFSET_SINGLESHOT /* 0x8000 in original */
multiline_comment|/*&n; * Status codes (timex.status)&n; */
DECL|macro|STA_PLL
mdefine_line|#define STA_PLL&t;&t;0x0001&t;/* enable PLL updates (rw) */
DECL|macro|STA_PPSFREQ
mdefine_line|#define STA_PPSFREQ&t;0x0002&t;/* enable PPS freq discipline (rw) */
DECL|macro|STA_PPSTIME
mdefine_line|#define STA_PPSTIME&t;0x0004&t;/* enable PPS time discipline (rw) */
DECL|macro|STA_FLL
mdefine_line|#define STA_FLL&t;&t;0x0008&t;/* select frequency-lock mode (rw) */
DECL|macro|STA_INS
mdefine_line|#define STA_INS&t;&t;0x0010&t;/* insert leap (rw) */
DECL|macro|STA_DEL
mdefine_line|#define STA_DEL&t;&t;0x0020&t;/* delete leap (rw) */
DECL|macro|STA_UNSYNC
mdefine_line|#define STA_UNSYNC&t;0x0040&t;/* clock unsynchronized (rw) */
DECL|macro|STA_FREQHOLD
mdefine_line|#define STA_FREQHOLD&t;0x0080&t;/* hold frequency (rw) */
DECL|macro|STA_PPSSIGNAL
mdefine_line|#define STA_PPSSIGNAL&t;0x0100&t;/* PPS signal present (ro) */
DECL|macro|STA_PPSJITTER
mdefine_line|#define STA_PPSJITTER&t;0x0200&t;/* PPS signal jitter exceeded (ro) */
DECL|macro|STA_PPSWANDER
mdefine_line|#define STA_PPSWANDER&t;0x0400&t;/* PPS signal wander exceeded (ro) */
DECL|macro|STA_PPSERROR
mdefine_line|#define STA_PPSERROR&t;0x0800&t;/* PPS signal calibration error (ro) */
DECL|macro|STA_CLOCKERR
mdefine_line|#define STA_CLOCKERR&t;0x1000&t;/* clock hardware fault (ro) */
DECL|macro|STA_RONLY
mdefine_line|#define STA_RONLY (STA_PPSSIGNAL | STA_PPSJITTER | STA_PPSWANDER | &bslash;&n;    STA_PPSERROR | STA_CLOCKERR) /* read-only bits */
multiline_comment|/*&n; * Clock states (time_state)&n; */
DECL|macro|TIME_OK
mdefine_line|#define TIME_OK&t;&t;0&t;/* clock synchronized, no leap second */
DECL|macro|TIME_INS
mdefine_line|#define TIME_INS&t;1&t;/* insert leap second */
DECL|macro|TIME_DEL
mdefine_line|#define TIME_DEL&t;2&t;/* delete leap second */
DECL|macro|TIME_OOP
mdefine_line|#define TIME_OOP&t;3&t;/* leap second in progress */
DECL|macro|TIME_WAIT
mdefine_line|#define TIME_WAIT&t;4&t;/* leap second has occurred */
DECL|macro|TIME_ERROR
mdefine_line|#define TIME_ERROR&t;5&t;/* clock not synchronized */
DECL|macro|TIME_BAD
mdefine_line|#define TIME_BAD&t;TIME_ERROR /* bw compat */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * kernel variables&n; * Note: maximum error = NTP synch distance = dispersion + delay / 2;&n; * estimated error = NTP dispersion.&n; */
r_extern
r_int
id|tick
suffix:semicolon
multiline_comment|/* timer interrupt period */
r_extern
r_int
id|tickadj
suffix:semicolon
multiline_comment|/* amount of adjustment per tick */
multiline_comment|/*&n; * phase-lock loop variables&n; */
r_extern
r_int
id|time_state
suffix:semicolon
multiline_comment|/* clock status */
r_extern
r_int
id|time_status
suffix:semicolon
multiline_comment|/* clock synchronization status bits */
r_extern
r_int
id|time_offset
suffix:semicolon
multiline_comment|/* time adjustment (us) */
r_extern
r_int
id|time_constant
suffix:semicolon
multiline_comment|/* pll time constant */
r_extern
r_int
id|time_tolerance
suffix:semicolon
multiline_comment|/* frequency tolerance (ppm) */
r_extern
r_int
id|time_precision
suffix:semicolon
multiline_comment|/* clock precision (us) */
r_extern
r_int
id|time_maxerror
suffix:semicolon
multiline_comment|/* maximum error */
r_extern
r_int
id|time_esterror
suffix:semicolon
multiline_comment|/* estimated error */
r_extern
r_int
id|time_phase
suffix:semicolon
multiline_comment|/* phase offset (scaled us) */
r_extern
r_int
id|time_freq
suffix:semicolon
multiline_comment|/* frequency offset (scaled ppm) */
r_extern
r_int
id|time_adj
suffix:semicolon
multiline_comment|/* tick adjust (scaled 1 / HZ) */
r_extern
r_int
id|time_reftime
suffix:semicolon
multiline_comment|/* time at last adjustment (s) */
r_extern
r_int
id|time_adjust
suffix:semicolon
multiline_comment|/* The amount of adjtime left */
multiline_comment|/* interface variables pps-&gt;timer interrupt */
r_extern
r_int
id|pps_offset
suffix:semicolon
multiline_comment|/* pps time offset (us) */
r_extern
r_int
id|pps_jitter
suffix:semicolon
multiline_comment|/* time dispersion (jitter) (us) */
r_extern
r_int
id|pps_freq
suffix:semicolon
multiline_comment|/* frequency offset (scaled ppm) */
r_extern
r_int
id|pps_stabil
suffix:semicolon
multiline_comment|/* frequency dispersion (scaled ppm) */
r_extern
r_int
id|pps_valid
suffix:semicolon
multiline_comment|/* pps signal watchdog counter */
multiline_comment|/* interface variables pps-&gt;adjtimex */
r_extern
r_int
id|pps_shift
suffix:semicolon
multiline_comment|/* interval duration (s) (shift) */
r_extern
r_int
id|pps_jitcnt
suffix:semicolon
multiline_comment|/* jitter limit exceeded */
r_extern
r_int
id|pps_calcnt
suffix:semicolon
multiline_comment|/* calibration intervals */
r_extern
r_int
id|pps_errcnt
suffix:semicolon
multiline_comment|/* calibration errors */
r_extern
r_int
id|pps_stbcnt
suffix:semicolon
multiline_comment|/* stability limit exceeded */
macro_line|#endif /* KERNEL */
macro_line|#endif /* LINUX_TIMEX_H */
eof
