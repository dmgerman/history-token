macro_line|#ifndef _IPT_IPRANGE_H
DECL|macro|_IPT_IPRANGE_H
mdefine_line|#define _IPT_IPRANGE_H
DECL|macro|IPRANGE_SRC
mdefine_line|#define IPRANGE_SRC&t;&t;0x01&t;/* Match source IP address */
DECL|macro|IPRANGE_DST
mdefine_line|#define IPRANGE_DST&t;&t;0x02&t;/* Match destination IP address */
DECL|macro|IPRANGE_SRC_INV
mdefine_line|#define IPRANGE_SRC_INV&t;&t;0x10&t;/* Negate the condition */
DECL|macro|IPRANGE_DST_INV
mdefine_line|#define IPRANGE_DST_INV&t;&t;0x20&t;/* Negate the condition */
DECL|struct|ipt_iprange
r_struct
id|ipt_iprange
(brace
multiline_comment|/* Inclusive: network order. */
DECL|member|min_ip
DECL|member|max_ip
id|u_int32_t
id|min_ip
comma
id|max_ip
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipt_iprange_info
r_struct
id|ipt_iprange_info
(brace
DECL|member|src
r_struct
id|ipt_iprange
id|src
suffix:semicolon
DECL|member|dst
r_struct
id|ipt_iprange
id|dst
suffix:semicolon
multiline_comment|/* Flags from above */
DECL|member|flags
id|u_int8_t
id|flags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _IPT_IPRANGE_H */
eof
