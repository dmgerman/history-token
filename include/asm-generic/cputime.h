macro_line|#ifndef _ASM_GENERIC_CPUTIME_H
DECL|macro|_ASM_GENERIC_CPUTIME_H
mdefine_line|#define _ASM_GENERIC_CPUTIME_H
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
DECL|typedef|cputime_t
r_typedef
r_int
r_int
id|cputime_t
suffix:semicolon
DECL|macro|cputime_zero
mdefine_line|#define cputime_zero&t;&t;&t;(0UL)
DECL|macro|cputime_max
mdefine_line|#define cputime_max&t;&t;&t;((~0UL &gt;&gt; 1) - 1)
DECL|macro|cputime_add
mdefine_line|#define cputime_add(__a, __b)&t;&t;((__a) +  (__b))
DECL|macro|cputime_sub
mdefine_line|#define cputime_sub(__a, __b)&t;&t;((__a) -  (__b))
DECL|macro|cputime_eq
mdefine_line|#define cputime_eq(__a, __b)&t;&t;((__a) == (__b))
DECL|macro|cputime_gt
mdefine_line|#define cputime_gt(__a, __b)&t;&t;((__a) &gt;  (__b))
DECL|macro|cputime_ge
mdefine_line|#define cputime_ge(__a, __b)&t;&t;((__a) &gt;= (__b))
DECL|macro|cputime_lt
mdefine_line|#define cputime_lt(__a, __b)&t;&t;((__a) &lt;  (__b))
DECL|macro|cputime_le
mdefine_line|#define cputime_le(__a, __b)&t;&t;((__a) &lt;= (__b))
DECL|macro|cputime_to_jiffies
mdefine_line|#define cputime_to_jiffies(__ct)&t;(__ct)
DECL|macro|jiffies_to_cputime
mdefine_line|#define jiffies_to_cputime(__hz)&t;(__hz)
DECL|typedef|cputime64_t
r_typedef
id|u64
id|cputime64_t
suffix:semicolon
DECL|macro|cputime64_zero
mdefine_line|#define cputime64_zero (0ULL)
DECL|macro|cputime64_add
mdefine_line|#define cputime64_add(__a, __b)&t;&t;((__a) + (__b))
DECL|macro|cputime64_to_jiffies64
mdefine_line|#define cputime64_to_jiffies64(__ct)&t;(__ct)
DECL|macro|cputime_to_cputime64
mdefine_line|#define cputime_to_cputime64(__ct)&t;((u64) __ct)
multiline_comment|/*&n; * Convert cputime to milliseconds and back.&n; */
DECL|macro|cputime_to_msecs
mdefine_line|#define cputime_to_msecs(__ct)&t;&t;jiffies_to_msecs(__ct)
DECL|macro|msecs_to_cputime
mdefine_line|#define msecs_to_cputime(__msecs)&t;msecs_to_jiffies(__msecs)
multiline_comment|/*&n; * Convert cputime to seconds and back.&n; */
DECL|macro|cputime_to_secs
mdefine_line|#define cputime_to_secs(jif)&t;&t;((jif) / HZ)
DECL|macro|secs_to_cputime
mdefine_line|#define secs_to_cputime(sec)&t;&t;((sec) * HZ)
multiline_comment|/*&n; * Convert cputime to timespec and back.&n; */
DECL|macro|timespec_to_cputime
mdefine_line|#define timespec_to_cputime(__val)&t;timespec_to_jiffies(__val)
DECL|macro|cputime_to_timespec
mdefine_line|#define cputime_to_timespec(__ct,__val)&t;jiffies_to_timespec(__ct,__val)
multiline_comment|/*&n; * Convert cputime to timeval and back.&n; */
DECL|macro|timeval_to_cputime
mdefine_line|#define timeval_to_cputime(__val)&t;timeval_to_jiffies(__val)
DECL|macro|cputime_to_timeval
mdefine_line|#define cputime_to_timeval(__ct,__val)&t;jiffies_to_timeval(__ct,__val)
multiline_comment|/*&n; * Convert cputime to clock and back.&n; */
DECL|macro|cputime_to_clock_t
mdefine_line|#define cputime_to_clock_t(__ct)&t;jiffies_to_clock_t(__ct)
DECL|macro|clock_t_to_cputime
mdefine_line|#define clock_t_to_cputime(__x)&t;&t;clock_t_to_jiffies(__x)
multiline_comment|/*&n; * Convert cputime64 to clock.&n; */
DECL|macro|cputime64_to_clock_t
mdefine_line|#define cputime64_to_clock_t(__ct)&t;jiffies_64_to_clock_t(__ct)
macro_line|#endif
eof
