macro_line|#ifndef _IP6T_ESP_H
DECL|macro|_IP6T_ESP_H
mdefine_line|#define _IP6T_ESP_H
DECL|struct|ip6t_esp
r_struct
id|ip6t_esp
(brace
DECL|member|spis
id|u_int32_t
id|spis
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Security Parameter Index */
DECL|member|invflags
id|u_int8_t
id|invflags
suffix:semicolon
multiline_comment|/* Inverse flags */
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
multiline_comment|/* Values for &quot;invflags&quot; field in struct ip6t_esp. */
DECL|macro|IP6T_ESP_INV_SPI
mdefine_line|#define IP6T_ESP_INV_SPI&t;&t;0x01&t;/* Invert the sense of spi. */
DECL|macro|IP6T_ESP_INV_MASK
mdefine_line|#define IP6T_ESP_INV_MASK&t;0x01&t;/* All possible flags. */
macro_line|#endif /*_IP6T_ESP_H*/
eof
