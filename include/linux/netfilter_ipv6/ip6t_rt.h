macro_line|#ifndef _IP6T_RT_H
DECL|macro|_IP6T_RT_H
mdefine_line|#define _IP6T_RT_H
multiline_comment|/*#include &lt;linux/in6.h&gt;*/
DECL|macro|IP6T_RT_HOPS
mdefine_line|#define IP6T_RT_HOPS 16
DECL|struct|ip6t_rt
r_struct
id|ip6t_rt
(brace
DECL|member|rt_type
id|u_int32_t
id|rt_type
suffix:semicolon
multiline_comment|/* Routing Type */
DECL|member|segsleft
id|u_int32_t
id|segsleft
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Segments Left */
DECL|member|hdrlen
id|u_int32_t
id|hdrlen
suffix:semicolon
multiline_comment|/* Header Length */
DECL|member|flags
id|u_int8_t
id|flags
suffix:semicolon
multiline_comment|/*  */
DECL|member|invflags
id|u_int8_t
id|invflags
suffix:semicolon
multiline_comment|/* Inverse flags */
DECL|member|addrs
r_struct
id|in6_addr
id|addrs
(braket
id|IP6T_RT_HOPS
)braket
suffix:semicolon
multiline_comment|/* Hops */
DECL|member|addrnr
id|u_int8_t
id|addrnr
suffix:semicolon
multiline_comment|/* Nr of Addresses */
)brace
suffix:semicolon
DECL|macro|IP6T_RT_TYP
mdefine_line|#define IP6T_RT_TYP &t;&t;0x01
DECL|macro|IP6T_RT_SGS
mdefine_line|#define IP6T_RT_SGS &t;&t;0x02
DECL|macro|IP6T_RT_LEN
mdefine_line|#define IP6T_RT_LEN &t;&t;0x04
DECL|macro|IP6T_RT_RES
mdefine_line|#define IP6T_RT_RES &t;&t;0x08
DECL|macro|IP6T_RT_FST_MASK
mdefine_line|#define IP6T_RT_FST_MASK&t;0x30
DECL|macro|IP6T_RT_FST
mdefine_line|#define IP6T_RT_FST &t;&t;0x10
DECL|macro|IP6T_RT_FST_NSTRICT
mdefine_line|#define IP6T_RT_FST_NSTRICT&t;0x20
multiline_comment|/* Values for &quot;invflags&quot; field in struct ip6t_rt. */
DECL|macro|IP6T_RT_INV_TYP
mdefine_line|#define IP6T_RT_INV_TYP&t;&t;0x01&t;/* Invert the sense of type. */
DECL|macro|IP6T_RT_INV_SGS
mdefine_line|#define IP6T_RT_INV_SGS&t;&t;0x02&t;/* Invert the sense of Segments. */
DECL|macro|IP6T_RT_INV_LEN
mdefine_line|#define IP6T_RT_INV_LEN&t;&t;0x04&t;/* Invert the sense of length. */
DECL|macro|IP6T_RT_INV_MASK
mdefine_line|#define IP6T_RT_INV_MASK&t;0x07&t;/* All possible flags. */
DECL|macro|MASK_HOPOPTS
mdefine_line|#define MASK_HOPOPTS    128
DECL|macro|MASK_DSTOPTS
mdefine_line|#define MASK_DSTOPTS    64
DECL|macro|MASK_ROUTING
mdefine_line|#define MASK_ROUTING    32
DECL|macro|MASK_FRAGMENT
mdefine_line|#define MASK_FRAGMENT   16
DECL|macro|MASK_AH
mdefine_line|#define MASK_AH         8
DECL|macro|MASK_ESP
mdefine_line|#define MASK_ESP        4
DECL|macro|MASK_NONE
mdefine_line|#define MASK_NONE       2
DECL|macro|MASK_PROTO
mdefine_line|#define MASK_PROTO      1
macro_line|#endif /*_IP6T_RT_H*/
eof
