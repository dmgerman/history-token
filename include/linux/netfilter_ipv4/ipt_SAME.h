macro_line|#ifndef _IPT_SAME_H
DECL|macro|_IPT_SAME_H
mdefine_line|#define _IPT_SAME_H
DECL|macro|IPT_SAME_MAX_RANGE
mdefine_line|#define IPT_SAME_MAX_RANGE&t;10
DECL|macro|IPT_SAME_NODST
mdefine_line|#define IPT_SAME_NODST&t;&t;0x01
DECL|struct|ipt_same_info
r_struct
id|ipt_same_info
(brace
DECL|member|info
r_int
r_char
id|info
suffix:semicolon
DECL|member|rangesize
id|u_int32_t
id|rangesize
suffix:semicolon
DECL|member|ipnum
id|u_int32_t
id|ipnum
suffix:semicolon
DECL|member|iparray
id|u_int32_t
op_star
id|iparray
suffix:semicolon
multiline_comment|/* hangs off end. */
DECL|member|range
r_struct
id|ip_nat_range
id|range
(braket
id|IPT_SAME_MAX_RANGE
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_SAME_H*/
eof
