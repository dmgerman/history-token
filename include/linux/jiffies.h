macro_line|#ifndef _LINUX_JIFFIES_H
DECL|macro|_LINUX_JIFFIES_H
mdefine_line|#define _LINUX_JIFFIES_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/param.h&gt;&t;&t;&t;/* for HZ */
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#ifndef div_long_long_rem
DECL|macro|div_long_long_rem
mdefine_line|#define div_long_long_rem(dividend,divisor,remainder) &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u64 result = dividend;&t;&t;&t;&t;&bslash;&n;&t;*remainder = do_div(result,divisor);&t;&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
multiline_comment|/*&n; * The following defines establish the engineering parameters of the PLL&n; * model. The HZ variable establishes the timer interrupt frequency, 100 Hz&n; * for the SunOS kernel, 256 Hz for the Ultrix kernel and 1024 Hz for the&n; * OSF/1 kernel. The SHIFT_HZ define expresses the same value as the&n; * nearest power of two in order to avoid hardware multiply operations.&n; */
macro_line|#if HZ &gt;= 12 &amp;&amp; HZ &lt; 24
DECL|macro|SHIFT_HZ
macro_line|# define SHIFT_HZ&t;4
macro_line|#elif HZ &gt;= 24 &amp;&amp; HZ &lt; 48
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
multiline_comment|/* LATCH is used in the interval timer and ftape setup. */
DECL|macro|LATCH
mdefine_line|#define LATCH  ((CLOCK_TICK_RATE + HZ/2) / HZ)&t;/* For divider */
multiline_comment|/* Suppose we want to devide two numbers NOM and DEN: NOM/DEN, the we can&n; * improve accuracy by shifting LSH bits, hence calculating:&n; *     (NOM &lt;&lt; LSH) / DEN&n; * This however means trouble for large NOM, because (NOM &lt;&lt; LSH) may no&n; * longer fit in 32 bits. The following way of calculating this gives us&n; * some slack, under the following conditions:&n; *   - (NOM / DEN) fits in (32 - LSH) bits.&n; *   - (NOM % DEN) fits in (32 - LSH) bits.&n; */
DECL|macro|SH_DIV
mdefine_line|#define SH_DIV(NOM,DEN,LSH) (   ((NOM / DEN) &lt;&lt; LSH)                    &bslash;&n;                             + (((NOM % DEN) &lt;&lt; LSH) + DEN / 2) / DEN)
multiline_comment|/* HZ is the requested value. ACTHZ is actual HZ (&quot;&lt;&lt; 8&quot; is for accuracy) */
DECL|macro|ACTHZ
mdefine_line|#define ACTHZ (SH_DIV (CLOCK_TICK_RATE, LATCH, 8))
multiline_comment|/* TICK_NSEC is the time between ticks in nsec assuming real ACTHZ */
DECL|macro|TICK_NSEC
mdefine_line|#define TICK_NSEC (SH_DIV (1000000UL * 1000, ACTHZ, 8))
multiline_comment|/* TICK_USEC is the time between ticks in usec assuming fake USER_HZ */
DECL|macro|TICK_USEC
mdefine_line|#define TICK_USEC ((1000000UL + USER_HZ/2) / USER_HZ)
multiline_comment|/* TICK_USEC_TO_NSEC is the time between ticks in nsec assuming real ACTHZ and&t;*/
multiline_comment|/* a value TUSEC for TICK_USEC (can be set bij adjtimex)&t;&t;*/
DECL|macro|TICK_USEC_TO_NSEC
mdefine_line|#define TICK_USEC_TO_NSEC(TUSEC) (SH_DIV (TUSEC * USER_HZ * 1000, ACTHZ, 8))
multiline_comment|/* some arch&squot;s have a small-data section that can be accessed register-relative&n; * but that can only take up to, say, 4-byte variables. jiffies being part of&n; * an 8-byte variable may not be correctly accessed unless we force the issue&n; */
DECL|macro|__jiffy_data
mdefine_line|#define __jiffy_data  __attribute__((section(&quot;.data&quot;)))
multiline_comment|/*&n; * The 64-bit value is not volatile - you MUST NOT read it&n; * without sampling the sequence number in xtime_lock.&n; * get_jiffies_64() will do this for you as appropriate.&n; */
r_extern
id|u64
id|__jiffy_data
id|jiffies_64
suffix:semicolon
r_extern
r_int
r_int
r_volatile
id|__jiffy_data
id|jiffies
suffix:semicolon
macro_line|#if (BITS_PER_LONG &lt; 64)
id|u64
id|get_jiffies_64
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|get_jiffies_64
r_static
r_inline
id|u64
id|get_jiffies_64
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|u64
)paren
id|jiffies
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;These inlines deal with timer wrapping correctly. You are &n; *&t;strongly encouraged to use them&n; *&t;1. Because people otherwise forget&n; *&t;2. Because if the timer wrap changes in future you won&squot;t have to&n; *&t;   alter your driver code.&n; *&n; * time_after(a,b) returns true if the time a is after time b.&n; *&n; * Do this with &quot;&lt;0&quot; and &quot;&gt;=0&quot; to only test the sign of the result. A&n; * good compiler would generate better code (and a really good compiler&n; * wouldn&squot;t care). Gcc is currently neither.&n; */
DECL|macro|time_after
mdefine_line|#define time_after(a,b)&t;&t;&bslash;&n;&t;(typecheck(unsigned long, a) &amp;&amp; &bslash;&n;&t; typecheck(unsigned long, b) &amp;&amp; &bslash;&n;&t; ((long)(b) - (long)(a) &lt; 0))
DECL|macro|time_before
mdefine_line|#define time_before(a,b)&t;time_after(b,a)
DECL|macro|time_after_eq
mdefine_line|#define time_after_eq(a,b)&t;&bslash;&n;&t;(typecheck(unsigned long, a) &amp;&amp; &bslash;&n;&t; typecheck(unsigned long, b) &amp;&amp; &bslash;&n;&t; ((long)(a) - (long)(b) &gt;= 0))
DECL|macro|time_before_eq
mdefine_line|#define time_before_eq(a,b)&t;time_after_eq(b,a)
multiline_comment|/*&n; * Have the 32 bit jiffies value wrap 5 minutes after boot&n; * so jiffies wrap bugs show up earlier.&n; */
DECL|macro|INITIAL_JIFFIES
mdefine_line|#define INITIAL_JIFFIES ((unsigned long)(unsigned int) (-300*HZ))
multiline_comment|/*&n; * Change timeval to jiffies, trying to avoid the&n; * most obvious overflows..&n; *&n; * And some not so obvious.&n; *&n; * Note that we don&squot;t want to return MAX_LONG, because&n; * for various timeout reasons we often end up having&n; * to wait &quot;jiffies+1&quot; in order to guarantee that we wait&n; * at _least_ &quot;jiffies&quot; - so &quot;jiffies+1&quot; had better still&n; * be positive.&n; */
DECL|macro|MAX_JIFFY_OFFSET
mdefine_line|#define MAX_JIFFY_OFFSET ((~0UL &gt;&gt; 1)-1)
multiline_comment|/*&n; * We want to do realistic conversions of time so we need to use the same&n; * values the update wall clock code uses as the jiffies size.  This value&n; * is: TICK_NSEC (which is defined in timex.h).  This&n; * is a constant and is in nanoseconds.  We will used scaled math&n; * with a set of scales defined here as SEC_JIFFIE_SC,  USEC_JIFFIE_SC and&n; * NSEC_JIFFIE_SC.  Note that these defines contain nothing but&n; * constants and so are computed at compile time.  SHIFT_HZ (computed in&n; * timex.h) adjusts the scaling for different HZ values.&n;&n; * Scaled math???  What is that?&n; *&n; * Scaled math is a way to do integer math on values that would,&n; * otherwise, either overflow, underflow, or cause undesired div&n; * instructions to appear in the execution path.  In short, we &quot;scale&quot;&n; * up the operands so they take more bits (more precision, less&n; * underflow), do the desired operation and then &quot;scale&quot; the result back&n; * by the same amount.  If we do the scaling by shifting we avoid the&n; * costly mpy and the dastardly div instructions.&n;&n; * Suppose, for example, we want to convert from seconds to jiffies&n; * where jiffies is defined in nanoseconds as NSEC_PER_JIFFIE.  The&n; * simple math is: jiff = (sec * NSEC_PER_SEC) / NSEC_PER_JIFFIE; We&n; * observe that (NSEC_PER_SEC / NSEC_PER_JIFFIE) is a constant which we&n; * might calculate at compile time, however, the result will only have&n; * about 3-4 bits of precision (less for smaller values of HZ).&n; *&n; * So, we scale as follows:&n; * jiff = (sec) * (NSEC_PER_SEC / NSEC_PER_JIFFIE);&n; * jiff = ((sec) * ((NSEC_PER_SEC * SCALE)/ NSEC_PER_JIFFIE)) / SCALE;&n; * Then we make SCALE a power of two so:&n; * jiff = ((sec) * ((NSEC_PER_SEC &lt;&lt; SCALE)/ NSEC_PER_JIFFIE)) &gt;&gt; SCALE;&n; * Now we define:&n; * #define SEC_CONV = ((NSEC_PER_SEC &lt;&lt; SCALE)/ NSEC_PER_JIFFIE))&n; * jiff = (sec * SEC_CONV) &gt;&gt; SCALE;&n; *&n; * Often the math we use will expand beyond 32-bits so we tell C how to&n; * do this and pass the 64-bit result of the mpy through the &quot;&gt;&gt; SCALE&quot;&n; * which should take the result back to 32-bits.  We want this expansion&n; * to capture as much precision as possible.  At the same time we don&squot;t&n; * want to overflow so we pick the SCALE to avoid this.  In this file,&n; * that means using a different scale for each range of HZ values (as&n; * defined in timex.h).&n; *&n; * For those who want to know, gcc will give a 64-bit result from a &quot;*&quot;&n; * operator if the result is a long long AND at least one of the&n; * operands is cast to long long (usually just prior to the &quot;*&quot; so as&n; * not to confuse it into thinking it really has a 64-bit operand,&n; * which, buy the way, it can do, but it take more code and at least 2&n; * mpys).&n;&n; * We also need to be aware that one second in nanoseconds is only a&n; * couple of bits away from overflowing a 32-bit word, so we MUST use&n; * 64-bits to get the full range time in nanoseconds.&n;&n; */
multiline_comment|/*&n; * Here are the scales we will use.  One for seconds, nanoseconds and&n; * microseconds.&n; *&n; * Within the limits of cpp we do a rough cut at the SEC_JIFFIE_SC and&n; * check if the sign bit is set.  If not, we bump the shift count by 1.&n; * (Gets an extra bit of precision where we can use it.)&n; * We know it is set for HZ = 1024 and HZ = 100 not for 1000.&n; * Haven&squot;t tested others.&n;&n; * Limits of cpp (for #if expressions) only long (no long long), but&n; * then we only need the most signicant bit.&n; */
DECL|macro|SEC_JIFFIE_SC
mdefine_line|#define SEC_JIFFIE_SC (31 - SHIFT_HZ)
macro_line|#if !((((NSEC_PER_SEC &lt;&lt; 2) / TICK_NSEC) &lt;&lt; (SEC_JIFFIE_SC - 2)) &amp; 0x80000000)
DECL|macro|SEC_JIFFIE_SC
macro_line|#undef SEC_JIFFIE_SC
DECL|macro|SEC_JIFFIE_SC
mdefine_line|#define SEC_JIFFIE_SC (32 - SHIFT_HZ)
macro_line|#endif
DECL|macro|NSEC_JIFFIE_SC
mdefine_line|#define NSEC_JIFFIE_SC (SEC_JIFFIE_SC + 29)
DECL|macro|USEC_JIFFIE_SC
mdefine_line|#define USEC_JIFFIE_SC (SEC_JIFFIE_SC + 19)
DECL|macro|SEC_CONVERSION
mdefine_line|#define SEC_CONVERSION ((unsigned long)((((u64)NSEC_PER_SEC &lt;&lt; SEC_JIFFIE_SC) +&bslash;&n;                                TICK_NSEC -1) / (u64)TICK_NSEC))
DECL|macro|NSEC_CONVERSION
mdefine_line|#define NSEC_CONVERSION ((unsigned long)((((u64)1 &lt;&lt; NSEC_JIFFIE_SC) +&bslash;&n;                                        TICK_NSEC -1) / (u64)TICK_NSEC))
DECL|macro|USEC_CONVERSION
mdefine_line|#define USEC_CONVERSION  &bslash;&n;                    ((unsigned long)((((u64)NSEC_PER_USEC &lt;&lt; USEC_JIFFIE_SC) +&bslash;&n;                                        TICK_NSEC -1) / (u64)TICK_NSEC))
multiline_comment|/*&n; * USEC_ROUND is used in the timeval to jiffie conversion.  See there&n; * for more details.  It is the scaled resolution rounding value.  Note&n; * that it is a 64-bit value.  Since, when it is applied, we are already&n; * in jiffies (albit scaled), it is nothing but the bits we will shift&n; * off.&n; */
DECL|macro|USEC_ROUND
mdefine_line|#define USEC_ROUND (u64)(((u64)1 &lt;&lt; USEC_JIFFIE_SC) - 1)
multiline_comment|/*&n; * The maximum jiffie value is (MAX_INT &gt;&gt; 1).  Here we translate that&n; * into seconds.  The 64-bit case will overflow if we are not careful,&n; * so use the messy SH_DIV macro to do it.  Still all constants.&n; */
macro_line|#if BITS_PER_LONG &lt; 64
DECL|macro|MAX_SEC_IN_JIFFIES
macro_line|# define MAX_SEC_IN_JIFFIES &bslash;&n;&t;(long)((u64)((u64)MAX_JIFFY_OFFSET * TICK_NSEC) / NSEC_PER_SEC)
macro_line|#else&t;/* take care of overflow on 64 bits machines */
DECL|macro|MAX_SEC_IN_JIFFIES
macro_line|# define MAX_SEC_IN_JIFFIES &bslash;&n;&t;(SH_DIV((MAX_JIFFY_OFFSET &gt;&gt; SEC_JIFFIE_SC) * TICK_NSEC, NSEC_PER_SEC, 1) - 1)
macro_line|#endif
multiline_comment|/*&n; * Convert jiffies to milliseconds and back.&n; *&n; * Avoid unnecessary multiplications/divisions in the&n; * two most common HZ cases:&n; */
DECL|function|jiffies_to_msecs
r_static
r_inline
r_int
r_int
id|jiffies_to_msecs
c_func
(paren
r_const
r_int
r_int
id|j
)paren
(brace
macro_line|#if HZ &lt;= 1000 &amp;&amp; !(1000 % HZ)
r_return
(paren
l_int|1000
op_div
id|HZ
)paren
op_star
id|j
suffix:semicolon
macro_line|#elif HZ &gt; 1000 &amp;&amp; !(HZ % 1000)
r_return
(paren
id|j
op_plus
(paren
id|HZ
op_div
l_int|1000
)paren
op_minus
l_int|1
)paren
op_div
(paren
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
macro_line|#else
r_return
(paren
id|j
op_star
l_int|1000
)paren
op_div
id|HZ
suffix:semicolon
macro_line|#endif
)brace
DECL|function|jiffies_to_usecs
r_static
r_inline
r_int
r_int
id|jiffies_to_usecs
c_func
(paren
r_const
r_int
r_int
id|j
)paren
(brace
macro_line|#if HZ &lt;= 1000 &amp;&amp; !(1000 % HZ)
r_return
(paren
l_int|1000000
op_div
id|HZ
)paren
op_star
id|j
suffix:semicolon
macro_line|#elif HZ &gt; 1000 &amp;&amp; !(HZ % 1000)
r_return
(paren
id|j
op_star
l_int|1000
op_plus
(paren
id|HZ
op_minus
l_int|1000
)paren
)paren
op_div
(paren
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
macro_line|#else
r_return
(paren
id|j
op_star
l_int|1000000
)paren
op_div
id|HZ
suffix:semicolon
macro_line|#endif
)brace
DECL|function|msecs_to_jiffies
r_static
r_inline
r_int
r_int
id|msecs_to_jiffies
c_func
(paren
r_const
r_int
r_int
id|m
)paren
(brace
r_if
c_cond
(paren
id|m
OG
id|jiffies_to_msecs
c_func
(paren
id|MAX_JIFFY_OFFSET
)paren
)paren
r_return
id|MAX_JIFFY_OFFSET
suffix:semicolon
macro_line|#if HZ &lt;= 1000 &amp;&amp; !(1000 % HZ)
r_return
(paren
id|m
op_plus
(paren
l_int|1000
op_div
id|HZ
)paren
op_minus
l_int|1
)paren
op_div
(paren
l_int|1000
op_div
id|HZ
)paren
suffix:semicolon
macro_line|#elif HZ &gt; 1000 &amp;&amp; !(HZ % 1000)
r_return
id|m
op_star
(paren
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
macro_line|#else
r_return
(paren
id|m
op_star
id|HZ
op_plus
l_int|999
)paren
op_div
l_int|1000
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * The TICK_NSEC - 1 rounds up the value to the next resolution.  Note&n; * that a remainder subtract here would not do the right thing as the&n; * resolution values don&squot;t fall on second boundries.  I.e. the line:&n; * nsec -= nsec % TICK_NSEC; is NOT a correct resolution rounding.&n; *&n; * Rather, we just shift the bits off the right.&n; *&n; * The &gt;&gt; (NSEC_JIFFIE_SC - SEC_JIFFIE_SC) converts the scaled nsec&n; * value to a scaled second value.&n; */
r_static
id|__inline__
r_int
r_int
DECL|function|timespec_to_jiffies
id|timespec_to_jiffies
c_func
(paren
r_const
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
(brace
id|sec
op_assign
id|MAX_SEC_IN_JIFFIES
suffix:semicolon
id|nsec
op_assign
l_int|0
suffix:semicolon
)brace
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
r_const
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
multiline_comment|/*&n;&t; * Convert jiffies to nanoseconds and separate with&n;&t; * one divide.&n;&t; */
id|u64
id|nsec
op_assign
(paren
id|u64
)paren
id|jiffies
op_star
id|TICK_NSEC
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
multiline_comment|/* Same for &quot;timeval&quot;&n; *&n; * Well, almost.  The problem here is that the real system resolution is&n; * in nanoseconds and the value being converted is in micro seconds.&n; * Also for some machines (those that use HZ = 1024, in-particular),&n; * there is a LARGE error in the tick size in microseconds.&n;&n; * The solution we use is to do the rounding AFTER we convert the&n; * microsecond part.  Thus the USEC_ROUND, the bits to be shifted off.&n; * Instruction wise, this should cost only an additional add with carry&n; * instruction above the way it was done above.&n; */
r_static
id|__inline__
r_int
r_int
DECL|function|timeval_to_jiffies
id|timeval_to_jiffies
c_func
(paren
r_const
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
suffix:semicolon
r_if
c_cond
(paren
id|sec
op_ge
id|MAX_SEC_IN_JIFFIES
)paren
(brace
id|sec
op_assign
id|MAX_SEC_IN_JIFFIES
suffix:semicolon
id|usec
op_assign
l_int|0
suffix:semicolon
)brace
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
op_plus
id|USEC_ROUND
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
r_const
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
multiline_comment|/*&n;&t; * Convert jiffies to nanoseconds and separate with&n;&t; * one divide.&n;&t; */
id|u64
id|nsec
op_assign
(paren
id|u64
)paren
id|jiffies
op_star
id|TICK_NSEC
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
multiline_comment|/*&n; * Convert jiffies/jiffies_64 to clock_t and back.&n; */
DECL|function|jiffies_to_clock_t
r_static
r_inline
id|clock_t
id|jiffies_to_clock_t
c_func
(paren
r_int
id|x
)paren
(brace
macro_line|#if (TICK_NSEC % (NSEC_PER_SEC / USER_HZ)) == 0
r_return
id|x
op_div
(paren
id|HZ
op_div
id|USER_HZ
)paren
suffix:semicolon
macro_line|#else
id|u64
id|tmp
op_assign
(paren
id|u64
)paren
id|x
op_star
id|TICK_NSEC
suffix:semicolon
id|do_div
c_func
(paren
id|tmp
comma
(paren
id|NSEC_PER_SEC
op_div
id|USER_HZ
)paren
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
id|tmp
suffix:semicolon
macro_line|#endif
)brace
DECL|function|clock_t_to_jiffies
r_static
r_inline
r_int
r_int
id|clock_t_to_jiffies
c_func
(paren
r_int
r_int
id|x
)paren
(brace
macro_line|#if (HZ % USER_HZ)==0
r_if
c_cond
(paren
id|x
op_ge
op_complement
l_int|0UL
op_div
(paren
id|HZ
op_div
id|USER_HZ
)paren
)paren
r_return
op_complement
l_int|0UL
suffix:semicolon
r_return
id|x
op_star
(paren
id|HZ
op_div
id|USER_HZ
)paren
suffix:semicolon
macro_line|#else
id|u64
id|jif
suffix:semicolon
multiline_comment|/* Don&squot;t worry about loss of precision here .. */
r_if
c_cond
(paren
id|x
op_ge
op_complement
l_int|0UL
op_div
id|HZ
op_star
id|USER_HZ
)paren
r_return
op_complement
l_int|0UL
suffix:semicolon
multiline_comment|/* .. but do try to contain it here */
id|jif
op_assign
id|x
op_star
(paren
id|u64
)paren
id|HZ
suffix:semicolon
id|do_div
c_func
(paren
id|jif
comma
id|USER_HZ
)paren
suffix:semicolon
r_return
id|jif
suffix:semicolon
macro_line|#endif
)brace
DECL|function|jiffies_64_to_clock_t
r_static
r_inline
id|u64
id|jiffies_64_to_clock_t
c_func
(paren
id|u64
id|x
)paren
(brace
macro_line|#if (TICK_NSEC % (NSEC_PER_SEC / USER_HZ)) == 0
id|do_div
c_func
(paren
id|x
comma
id|HZ
op_div
id|USER_HZ
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;&t; * There are better ways that don&squot;t overflow early,&n;&t; * but even this doesn&squot;t overflow in hundreds of years&n;&t; * in 64 bits, so..&n;&t; */
id|x
op_mul_assign
id|TICK_NSEC
suffix:semicolon
id|do_div
c_func
(paren
id|x
comma
(paren
id|NSEC_PER_SEC
op_div
id|USER_HZ
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|x
suffix:semicolon
)brace
DECL|function|nsec_to_clock_t
r_static
r_inline
id|u64
id|nsec_to_clock_t
c_func
(paren
id|u64
id|x
)paren
(brace
macro_line|#if (NSEC_PER_SEC % USER_HZ) == 0
id|do_div
c_func
(paren
id|x
comma
(paren
id|NSEC_PER_SEC
op_div
id|USER_HZ
)paren
)paren
suffix:semicolon
macro_line|#elif (USER_HZ % 512) == 0
id|x
op_mul_assign
id|USER_HZ
op_div
l_int|512
suffix:semicolon
id|do_div
c_func
(paren
id|x
comma
(paren
id|NSEC_PER_SEC
op_div
l_int|512
)paren
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;         * max relative error 5.7e-8 (1.8s per year) for USER_HZ &lt;= 1024,&n;         * overflow after 64.99 years.&n;         * exact for HZ=60, 72, 90, 120, 144, 180, 300, 600, 900, ...&n;         */
id|x
op_mul_assign
l_int|9
suffix:semicolon
id|do_div
c_func
(paren
id|x
comma
(paren
r_int
r_int
)paren
(paren
(paren
l_int|9ull
op_star
id|NSEC_PER_SEC
op_plus
(paren
id|USER_HZ
op_div
l_int|2
)paren
)paren
op_div
id|USER_HZ
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|x
suffix:semicolon
)brace
macro_line|#endif
eof
