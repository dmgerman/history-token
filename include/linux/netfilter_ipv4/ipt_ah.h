macro_line|#ifndef _IPT_AH_H
DECL|macro|_IPT_AH_H
mdefine_line|#define _IPT_AH_H
DECL|struct|ipt_ah
r_struct
id|ipt_ah
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
multiline_comment|/* Values for &quot;invflags&quot; field in struct ipt_ah. */
DECL|macro|IPT_AH_INV_SPI
mdefine_line|#define IPT_AH_INV_SPI&t;&t;0x01&t;/* Invert the sense of spi. */
DECL|macro|IPT_AH_INV_MASK
mdefine_line|#define IPT_AH_INV_MASK&t;0x01&t;/* All possible flags. */
macro_line|#endif /*_IPT_AH_H*/
eof
