multiline_comment|/*&n; * $Id: time.h,v 1.12 1999/08/27 04:21:23 cort Exp $&n; * Common time prototypes and such for all ppc machines.&n; *&n; * Written by Cort Dougan (cort@fsmlabs.com) to merge&n; * Paul Mackerras&squot; version and mine for PReP and Pmac.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/* time.c */
r_extern
r_int
id|tb_ticks_per_jiffy
suffix:semicolon
r_extern
r_int
id|tb_to_us
suffix:semicolon
r_extern
r_int
id|tb_last_stamp
suffix:semicolon
r_extern
r_int
r_int
id|disarm_decr
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_void
id|to_tm
c_func
(paren
r_int
id|tim
comma
r_struct
id|rtc_time
op_star
id|tm
)paren
suffix:semicolon
r_extern
id|time_t
id|last_rtc_update
suffix:semicolon
r_int
id|via_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Accessor functions for the decrementer register. */
DECL|function|get_dec
r_static
id|__inline__
r_int
r_int
id|get_dec
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_4xx)
r_return
(paren
id|mfspr
c_func
(paren
id|SPRN_PIT
)paren
)paren
suffix:semicolon
macro_line|#else
r_return
(paren
id|mfspr
c_func
(paren
id|SPRN_DEC
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|set_dec
r_static
id|__inline__
r_void
id|set_dec
c_func
(paren
r_int
r_int
id|val
)paren
(brace
macro_line|#if defined(CONFIG_4xx)
id|mtspr
c_func
(paren
id|SPRN_PIT
comma
id|val
)paren
suffix:semicolon
macro_line|#else
macro_line|#ifdef CONFIG_8xx_CPU6
id|set_dec_cpu6
c_func
(paren
id|val
)paren
suffix:semicolon
macro_line|#else
id|mtspr
c_func
(paren
id|SPRN_DEC
comma
id|val
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
)brace
multiline_comment|/* Accessor functions for the timebase (RTC on 601) registers. */
multiline_comment|/* If one day CONFIG_POWER is added just define __USE_RTC as 1 */
macro_line|#ifdef CONFIG_6xx
DECL|function|__USE_RTC
r_extern
id|__inline__
r_int
r_const
id|__USE_RTC
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|mfspr
c_func
(paren
id|SPRN_PVR
)paren
op_rshift
l_int|16
)paren
op_eq
l_int|1
suffix:semicolon
)brace
macro_line|#else
DECL|macro|__USE_RTC
mdefine_line|#define __USE_RTC() 0
macro_line|#endif
DECL|function|get_tbl
r_extern
id|__inline__
r_int
r_int
id|get_tbl
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tbl
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mftb %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tbl
)paren
)paren
suffix:semicolon
r_return
id|tbl
suffix:semicolon
)brace
DECL|function|get_rtcl
r_extern
id|__inline__
r_int
r_int
id|get_rtcl
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|rtcl
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mfrtcl %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|rtcl
)paren
)paren
suffix:semicolon
r_return
id|rtcl
suffix:semicolon
)brace
DECL|function|get_native_tbl
r_extern
id|__inline__
r_int
id|get_native_tbl
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|__USE_RTC
c_func
(paren
)paren
)paren
r_return
id|get_rtcl
c_func
(paren
)paren
suffix:semicolon
r_else
r_return
id|get_tbl
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* On machines with RTC, this function can only be used safely&n; * after the timestamp and for 1 second. It is only used by gettimeofday&n; * however so it should not matter.&n; */
DECL|function|tb_ticks_since
r_extern
id|__inline__
r_int
id|tb_ticks_since
c_func
(paren
r_int
id|tstamp
)paren
(brace
r_if
c_cond
(paren
id|__USE_RTC
c_func
(paren
)paren
)paren
(brace
r_int
id|delta
op_assign
id|get_rtcl
c_func
(paren
)paren
op_minus
id|tstamp
suffix:semicolon
r_return
id|delta
OL
l_int|0
ques
c_cond
id|delta
op_plus
l_int|1000000000
suffix:colon
id|delta
suffix:semicolon
)brace
r_else
(brace
r_return
id|get_tbl
c_func
(paren
)paren
op_minus
id|tstamp
suffix:semicolon
)brace
)brace
macro_line|#if 0
r_extern
id|__inline__
r_int
r_int
id|get_bin_rtcl
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|rtcl
comma
id|rtcu1
comma
id|rtcu2
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;&bslash;&n;1:    mfrtcu  %0&bslash;n&bslash;&n;      mfrtcl  %1&bslash;n&bslash;&n;      mfrtcu  %2&bslash;n&bslash;&n;      cmpw    %0,%2&bslash;n&bslash;&n;      bne-    1b&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|rtcu1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|rtcl
)paren
comma
l_string|&quot;=r&quot;
(paren
id|rtcu2
)paren
suffix:colon
suffix:colon
l_string|&quot;cr0&quot;
)paren
suffix:semicolon
r_return
id|rtcu2
op_star
l_int|1000000000
op_plus
id|rtcl
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
id|binary_tbl
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|__USE_RTC
c_func
(paren
)paren
)paren
r_return
id|get_bin_rtcl
c_func
(paren
)paren
suffix:semicolon
r_else
r_return
id|get_tbl
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Use mulhwu to scale processor timebase to timeval */
DECL|macro|mulhwu
mdefine_line|#define mulhwu(x,y) &bslash;&n;({unsigned z; asm (&quot;mulhwu %0,%1,%2&quot; : &quot;=r&quot; (z) : &quot;r&quot; (x), &quot;r&quot; (y)); z;})
r_int
id|mulhwu_scale_factor
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
eof
