macro_line|#ifndef _IP6T_RATE_H
DECL|macro|_IP6T_RATE_H
mdefine_line|#define _IP6T_RATE_H
multiline_comment|/* timings are in milliseconds. */
DECL|macro|IP6T_LIMIT_SCALE
mdefine_line|#define IP6T_LIMIT_SCALE 10000
multiline_comment|/* 1/10,000 sec period =&gt; max of 10,000/sec.  Min rate is then 429490&n;   seconds, or one every 59 hours. */
DECL|struct|ip6t_rateinfo
r_struct
id|ip6t_rateinfo
(brace
DECL|member|avg
id|u_int32_t
id|avg
suffix:semicolon
multiline_comment|/* Average secs between packets * scale */
DECL|member|burst
id|u_int32_t
id|burst
suffix:semicolon
multiline_comment|/* Period multiplier for upper limit. */
multiline_comment|/* Used internally by the kernel */
DECL|member|prev
r_int
r_int
id|prev
suffix:semicolon
DECL|member|credit
id|u_int32_t
id|credit
suffix:semicolon
DECL|member|credit_cap
DECL|member|cost
id|u_int32_t
id|credit_cap
comma
id|cost
suffix:semicolon
multiline_comment|/* Ugly, ugly fucker. */
DECL|member|master
r_struct
id|ip6t_rateinfo
op_star
id|master
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_RATE_H*/
eof
