macro_line|#ifndef _LINUX_TIMES_H
DECL|macro|_LINUX_TIMES_H
mdefine_line|#define _LINUX_TIMES_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#if (HZ % USER_HZ)==0
DECL|macro|jiffies_to_clock_t
macro_line|# define jiffies_to_clock_t(x) ((x) / (HZ / USER_HZ))
macro_line|#else
DECL|macro|jiffies_to_clock_t
macro_line|# define jiffies_to_clock_t(x) ((clock_t) jiffies_64_to_clock_t((u64) x))
macro_line|#endif
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
macro_line|#if (HZ % USER_HZ)==0
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
id|USER_HZ
suffix:semicolon
id|do_div
c_func
(paren
id|x
comma
id|HZ
)paren
suffix:semicolon
macro_line|#endif
r_return
id|x
suffix:semicolon
)brace
macro_line|#endif
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
