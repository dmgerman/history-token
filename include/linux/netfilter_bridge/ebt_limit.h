macro_line|#ifndef __LINUX_BRIDGE_EBT_LIMIT_H
DECL|macro|__LINUX_BRIDGE_EBT_LIMIT_H
mdefine_line|#define __LINUX_BRIDGE_EBT_LIMIT_H
DECL|macro|EBT_LIMIT_MATCH
mdefine_line|#define EBT_LIMIT_MATCH &quot;limit&quot;
multiline_comment|/* timings are in milliseconds. */
DECL|macro|EBT_LIMIT_SCALE
mdefine_line|#define EBT_LIMIT_SCALE 10000
multiline_comment|/* 1/10,000 sec period =&gt; max of 10,000/sec.  Min rate is then 429490&n;   seconds, or one every 59 hours. */
DECL|struct|ebt_limit_info
r_struct
id|ebt_limit_info
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
)brace
suffix:semicolon
macro_line|#endif
eof
