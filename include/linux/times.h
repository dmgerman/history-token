macro_line|#ifndef _LINUX_TIMES_H
DECL|macro|_LINUX_TIMES_H
mdefine_line|#define _LINUX_TIMES_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/param.h&gt;
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
macro_line|#endif
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
DECL|struct|tms
r_struct
id|tms
(brace
DECL|member|tms_utime
id|clock_t
id|tms_utime
suffix:semicolon
DECL|member|tms_stime
id|clock_t
id|tms_stime
suffix:semicolon
DECL|member|tms_cutime
id|clock_t
id|tms_cutime
suffix:semicolon
DECL|member|tms_cstime
id|clock_t
id|tms_cstime
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
