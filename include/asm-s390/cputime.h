multiline_comment|/*&n; *  include/asm-s390/cputime.h&n; *&n; *  (C) Copyright IBM Corp. 2004&n; *&n; *  Author: Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; */
macro_line|#ifndef _S390_CPUTIME_H
DECL|macro|_S390_CPUTIME_H
mdefine_line|#define _S390_CPUTIME_H
multiline_comment|/* We want to use micro-second resolution. */
DECL|typedef|cputime_t
r_typedef
r_int
r_int
r_int
id|cputime_t
suffix:semicolon
DECL|typedef|cputime64_t
r_typedef
r_int
r_int
r_int
id|cputime64_t
suffix:semicolon
macro_line|#ifndef __s390x__
r_static
r_inline
r_int
r_int
DECL|function|__div
id|__div
c_func
(paren
r_int
r_int
r_int
id|n
comma
r_int
r_int
id|base
)paren
(brace
id|register_pair
id|rp
suffix:semicolon
id|rp.pair
op_assign
id|n
op_rshift
l_int|1
suffix:semicolon
id|asm
(paren
l_string|&quot;dr %0,%1&quot;
suffix:colon
l_string|&quot;+d&quot;
(paren
id|rp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|base
op_rshift
l_int|1
)paren
)paren
suffix:semicolon
r_return
id|rp.subreg.odd
suffix:semicolon
)brace
macro_line|#else /* __s390x__ */
r_static
r_inline
r_int
r_int
DECL|function|__div
id|__div
c_func
(paren
r_int
r_int
r_int
id|n
comma
r_int
r_int
id|base
)paren
(brace
r_return
id|n
op_div
id|base
suffix:semicolon
)brace
macro_line|#endif /* __s390x__ */
DECL|macro|cputime_zero
mdefine_line|#define cputime_zero&t;&t;&t;(0ULL)
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
mdefine_line|#define cputime_to_jiffies(__ct)&t;(__div((__ct), 1000000 / HZ))
DECL|macro|jiffies_to_cputime
mdefine_line|#define jiffies_to_cputime(__hz)&t;((cputime_t)(__hz) * (1000000 / HZ))
DECL|macro|cputime64_zero
mdefine_line|#define cputime64_zero&t;&t;&t;(0ULL)
DECL|macro|cputime64_add
mdefine_line|#define cputime64_add(__a, __b)&t;&t;((__a) + (__b))
DECL|macro|cputime_to_cputime64
mdefine_line|#define cputime_to_cputime64(__ct)&t;(__ct)
r_static
r_inline
id|u64
DECL|function|cputime64_to_jiffies64
id|cputime64_to_jiffies64
c_func
(paren
id|cputime64_t
id|cputime
)paren
(brace
id|do_div
c_func
(paren
id|cputime
comma
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
r_return
id|cputime
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert cputime to milliseconds and back.&n; */
r_static
r_inline
r_int
r_int
DECL|function|cputime_to_msecs
id|cputime_to_msecs
c_func
(paren
r_const
id|cputime_t
id|cputime
)paren
(brace
r_return
id|__div
c_func
(paren
id|cputime
comma
l_int|1000
)paren
suffix:semicolon
)brace
r_static
r_inline
id|cputime_t
DECL|function|msecs_to_cputime
id|msecs_to_cputime
c_func
(paren
r_const
r_int
r_int
id|m
)paren
(brace
r_return
(paren
id|cputime_t
)paren
id|m
op_star
l_int|1000
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert cputime to milliseconds and back.&n; */
r_static
r_inline
r_int
r_int
DECL|function|cputime_to_secs
id|cputime_to_secs
c_func
(paren
r_const
id|cputime_t
id|cputime
)paren
(brace
r_return
id|__div
c_func
(paren
id|cputime
comma
l_int|1000000
)paren
suffix:semicolon
)brace
r_static
r_inline
id|cputime_t
DECL|function|secs_to_cputime
id|secs_to_cputime
c_func
(paren
r_const
r_int
r_int
id|s
)paren
(brace
r_return
(paren
id|cputime_t
)paren
id|s
op_star
l_int|1000000
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert cputime to timespec and back.&n; */
r_static
r_inline
id|cputime_t
DECL|function|timespec_to_cputime
id|timespec_to_cputime
c_func
(paren
r_const
r_struct
id|timespec
op_star
id|value
)paren
(brace
r_return
id|value-&gt;tv_nsec
op_div
l_int|1000
op_plus
(paren
id|u64
)paren
id|value-&gt;tv_sec
op_star
l_int|1000000
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|cputime_to_timespec
id|cputime_to_timespec
c_func
(paren
r_const
id|cputime_t
id|cputime
comma
r_struct
id|timespec
op_star
id|value
)paren
(brace
macro_line|#ifndef __s390x__
id|register_pair
id|rp
suffix:semicolon
id|rp.pair
op_assign
id|cputime
op_rshift
l_int|1
suffix:semicolon
id|asm
(paren
l_string|&quot;dr %0,%1&quot;
suffix:colon
l_string|&quot;+d&quot;
(paren
id|rp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|1000000
op_rshift
l_int|1
)paren
)paren
suffix:semicolon
id|value-&gt;tv_nsec
op_assign
id|rp.subreg.even
op_star
l_int|1000
suffix:semicolon
id|value-&gt;tv_sec
op_assign
id|rp.subreg.odd
suffix:semicolon
macro_line|#else
id|value-&gt;tv_nsec
op_assign
(paren
id|cputime
op_mod
l_int|1000000
)paren
op_star
l_int|1000
suffix:semicolon
id|value-&gt;tv_sec
op_assign
id|cputime
op_div
l_int|1000000
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Convert cputime to timeval and back.&n; * Since cputime and timeval have the same resolution (microseconds)&n; * this is easy.&n; */
r_static
r_inline
id|cputime_t
DECL|function|timeval_to_cputime
id|timeval_to_cputime
c_func
(paren
r_const
r_struct
id|timeval
op_star
id|value
)paren
(brace
r_return
id|value-&gt;tv_usec
op_plus
(paren
id|u64
)paren
id|value-&gt;tv_sec
op_star
l_int|1000000
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|cputime_to_timeval
id|cputime_to_timeval
c_func
(paren
r_const
id|cputime_t
id|cputime
comma
r_struct
id|timeval
op_star
id|value
)paren
(brace
macro_line|#ifndef __s390x__
id|register_pair
id|rp
suffix:semicolon
id|rp.pair
op_assign
id|cputime
op_rshift
l_int|1
suffix:semicolon
id|asm
(paren
l_string|&quot;dr %0,%1&quot;
suffix:colon
l_string|&quot;+d&quot;
(paren
id|rp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|1000000
op_rshift
l_int|1
)paren
)paren
suffix:semicolon
id|value-&gt;tv_usec
op_assign
id|rp.subreg.even
suffix:semicolon
id|value-&gt;tv_sec
op_assign
id|rp.subreg.odd
suffix:semicolon
macro_line|#else
id|value-&gt;tv_usec
op_assign
id|cputime
op_mod
l_int|1000000
suffix:semicolon
id|value-&gt;tv_sec
op_assign
id|cputime
op_div
l_int|1000000
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Convert cputime to clock and back.&n; */
r_static
r_inline
id|clock_t
DECL|function|cputime_to_clock_t
id|cputime_to_clock_t
c_func
(paren
id|cputime_t
id|cputime
)paren
(brace
r_return
id|__div
c_func
(paren
id|cputime
comma
l_int|1000000
op_div
id|USER_HZ
)paren
suffix:semicolon
)brace
r_static
r_inline
id|cputime_t
DECL|function|clock_t_to_cputime
id|clock_t_to_cputime
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_return
(paren
id|cputime_t
)paren
id|x
op_star
(paren
l_int|1000000
op_div
id|USER_HZ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert cputime64 to clock.&n; */
r_static
r_inline
id|clock_t
DECL|function|cputime64_to_clock_t
id|cputime64_to_clock_t
c_func
(paren
id|cputime64_t
id|cputime
)paren
(brace
r_return
id|__div
c_func
(paren
id|cputime
comma
l_int|1000000
op_div
id|USER_HZ
)paren
suffix:semicolon
)brace
macro_line|#endif /* _S390_CPUTIME_H */
eof
