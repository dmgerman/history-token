macro_line|#ifndef _IP6T_OPTS_H
DECL|macro|_IP6T_OPTS_H
mdefine_line|#define _IP6T_OPTS_H
DECL|macro|IP6T_OPTS_OPTSNR
mdefine_line|#define IP6T_OPTS_OPTSNR 16
DECL|struct|ip6t_opts
r_struct
id|ip6t_opts
(brace
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
DECL|member|opts
id|u_int16_t
id|opts
(braket
id|IP6T_OPTS_OPTSNR
)braket
suffix:semicolon
multiline_comment|/* opts */
DECL|member|optsnr
id|u_int8_t
id|optsnr
suffix:semicolon
multiline_comment|/* Nr of OPts */
)brace
suffix:semicolon
DECL|macro|IP6T_OPTS_LEN
mdefine_line|#define IP6T_OPTS_LEN &t;&t;0x01
DECL|macro|IP6T_OPTS_OPTS
mdefine_line|#define IP6T_OPTS_OPTS &t;&t;0x02
DECL|macro|IP6T_OPTS_NSTRICT
mdefine_line|#define IP6T_OPTS_NSTRICT&t;0x04
multiline_comment|/* Values for &quot;invflags&quot; field in struct ip6t_rt. */
DECL|macro|IP6T_OPTS_INV_LEN
mdefine_line|#define IP6T_OPTS_INV_LEN&t;0x01&t;/* Invert the sense of length. */
DECL|macro|IP6T_OPTS_INV_MASK
mdefine_line|#define IP6T_OPTS_INV_MASK&t;0x01&t;/* All possible flags. */
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
macro_line|#endif /*_IP6T_OPTS_H*/
eof
