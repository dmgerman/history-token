multiline_comment|/* ipv6header match - matches IPv6 packets based&n;on whether they contain certain headers */
multiline_comment|/* Original idea: Brad Chapman &n; * Rewritten by: Andras Kis-Szabo &lt;kisza@sch.bme.hu&gt; */
macro_line|#ifndef __IPV6HEADER_H
DECL|macro|__IPV6HEADER_H
mdefine_line|#define __IPV6HEADER_H
DECL|struct|ip6t_ipv6header_info
r_struct
id|ip6t_ipv6header_info
(brace
DECL|member|matchflags
id|u_int8_t
id|matchflags
suffix:semicolon
DECL|member|invflags
id|u_int8_t
id|invflags
suffix:semicolon
DECL|member|modeflag
id|u_int8_t
id|modeflag
suffix:semicolon
)brace
suffix:semicolon
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
macro_line|#endif /* __IPV6HEADER_H */
eof
