macro_line|#ifndef _IP6T_FRAG_H
DECL|macro|_IP6T_FRAG_H
mdefine_line|#define _IP6T_FRAG_H
DECL|struct|ip6t_frag
r_struct
id|ip6t_frag
(brace
DECL|member|ids
id|u_int32_t
id|ids
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Security Parameter Index */
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
)brace
suffix:semicolon
DECL|macro|IP6T_FRAG_IDS
mdefine_line|#define IP6T_FRAG_IDS &t;&t;0x01
DECL|macro|IP6T_FRAG_LEN
mdefine_line|#define IP6T_FRAG_LEN &t;&t;0x02
DECL|macro|IP6T_FRAG_RES
mdefine_line|#define IP6T_FRAG_RES &t;&t;0x04
DECL|macro|IP6T_FRAG_FST
mdefine_line|#define IP6T_FRAG_FST &t;&t;0x08
DECL|macro|IP6T_FRAG_MF
mdefine_line|#define IP6T_FRAG_MF  &t;&t;0x10
DECL|macro|IP6T_FRAG_NMF
mdefine_line|#define IP6T_FRAG_NMF  &t;&t;0x20
multiline_comment|/* Values for &quot;invflags&quot; field in struct ip6t_frag. */
DECL|macro|IP6T_FRAG_INV_IDS
mdefine_line|#define IP6T_FRAG_INV_IDS&t;0x01&t;/* Invert the sense of ids. */
DECL|macro|IP6T_FRAG_INV_LEN
mdefine_line|#define IP6T_FRAG_INV_LEN&t;0x02&t;/* Invert the sense of length. */
DECL|macro|IP6T_FRAG_INV_MASK
mdefine_line|#define IP6T_FRAG_INV_MASK&t;0x03&t;/* All possible flags. */
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
macro_line|#endif /*_IP6T_FRAG_H*/
eof
