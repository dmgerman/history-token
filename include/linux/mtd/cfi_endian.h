multiline_comment|/*&n; * $Id: cfi_endian.h,v 1.9 2001/04/23 21:19:11 nico Exp $&n; *&n; * It seems that some helpful people decided to make life easier&n; * for software engineers who aren&squot;t capable of dealing with the &n; * concept of byteswapping, and advise engineers to swap the bytes&n; * by wiring the data lines up to flash chips from BE hosts backwards.&n; *&n; * So we have ugly stuff here to disable the byteswapping where necessary.&n; * I&squot;m not going to try to do this dynamically.&n; *&n; * At first I thought these guys were on crack, but then I discovered the&n; * LART. &n; *&n; */
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifndef CONFIG_MTD_CFI_ADV_OPTIONS
DECL|macro|CFI_HOST_ENDIAN
mdefine_line|#define CFI_HOST_ENDIAN
macro_line|#else
macro_line|#ifdef CONFIG_MTD_CFI_NOSWAP
DECL|macro|CFI_HOST_ENDIAN
mdefine_line|#define CFI_HOST_ENDIAN
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_LE_BYTE_SWAP
DECL|macro|CFI_LITTLE_ENDIAN
mdefine_line|#define CFI_LITTLE_ENDIAN
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_BE_BYTE_SWAP
DECL|macro|CFI_BIG_ENDIAN
mdefine_line|#define CFI_BIG_ENDIAN
macro_line|#endif
macro_line|#ifdef CONFIG_MTD_CFI_LART_BIT_SWAP
DECL|macro|CFI_LART_ENDIAN
mdefine_line|#define CFI_LART_ENDIAN
macro_line|#endif
macro_line|#endif
macro_line|#if defined(CFI_LITTLE_ENDIAN)
DECL|macro|cpu_to_cfi8
mdefine_line|#define cpu_to_cfi8(x) (x)
DECL|macro|cfi8_to_cpu
mdefine_line|#define cfi8_to_cpu(x) (x)
DECL|macro|cpu_to_cfi16
mdefine_line|#define cpu_to_cfi16(x) cpu_to_le16(x)
DECL|macro|cpu_to_cfi32
mdefine_line|#define cpu_to_cfi32(x) cpu_to_le32(x)
DECL|macro|cfi16_to_cpu
mdefine_line|#define cfi16_to_cpu(x) le16_to_cpu(x)
DECL|macro|cfi32_to_cpu
mdefine_line|#define cfi32_to_cpu(x) le32_to_cpu(x)
macro_line|#elif defined (CFI_BIG_ENDIAN)
DECL|macro|cpu_to_cfi8
mdefine_line|#define cpu_to_cfi8(x) (x)
DECL|macro|cfi8_to_cpu
mdefine_line|#define cfi8_to_cpu(x) (x)
DECL|macro|cpu_to_cfi16
mdefine_line|#define cpu_to_cfi16(x) cpu_to_be16(x)
DECL|macro|cpu_to_cfi32
mdefine_line|#define cpu_to_cfi32(x) cpu_to_be32(x)
DECL|macro|cfi16_to_cpu
mdefine_line|#define cfi16_to_cpu(x) be16_to_cpu(x)
DECL|macro|cfi32_to_cpu
mdefine_line|#define cfi32_to_cpu(x) be32_to_cpu(x)
macro_line|#elif defined (CFI_HOST_ENDIAN)
DECL|macro|cpu_to_cfi8
mdefine_line|#define cpu_to_cfi8(x) (x)
DECL|macro|cfi8_to_cpu
mdefine_line|#define cfi8_to_cpu(x) (x)
DECL|macro|cpu_to_cfi16
mdefine_line|#define cpu_to_cfi16(x) (x)
DECL|macro|cpu_to_cfi32
mdefine_line|#define cpu_to_cfi32(x) (x)
DECL|macro|cfi16_to_cpu
mdefine_line|#define cfi16_to_cpu(x) (x)
DECL|macro|cfi32_to_cpu
mdefine_line|#define cfi32_to_cpu(x) (x)
macro_line|#elif defined (CFI_LART_ENDIAN)
multiline_comment|/* &n;   Fuck me backwards. The data line mapping on LART is as follows:&n;&n;&t;U2&t;CPU&t;|&t;U3&t;CPU&n;&t; 0&t;20&t;|&t;0&t;12&n;&t; 1&t;22&t;|&t;1&t;14&n;&t; 2&t;19&t;|&t;2&t;11&n;&t; 3&t;17&t;|&t;3&t;9&n;&t; 4&t;24&t;|&t;4&t;0&n;&t; 5&t;26&t;|&t;5&t;2&n;&t; 6&t;31&t;|&t;6&t;7&n;&t; 7&t;29&t;|&t;7&t;5&n;&t; 8&t;21&t;|&t;8&t;13&n;&t; 9&t;23&t;|&t;9&t;15&n;&t; 10&t;18&t;|&t;10&t;10&n;&t; 11&t;16&t;|&t;11&t;8&n;&t; 12&t;25&t;|&t;12&t;1&n;&t; 13&t;27&t;|&t;13&t;3&n;&t; 14&t;30&t;|&t;14&t;6&n;&t; 15&t;28&t;|&t;15&t;4&n;&n;   For historical reference: the reason why the LART has this strange&n;   mapping is that the designer of the board wanted address lines to&n;   be as short as possible. Why? Because in that way you don&squot;t need&n;   drivers in the address lines so the memory access time can be held&n;   short. -- Erik Mouw &lt;J.A.K.Mouw@its.tudelft.nl&gt;&n;*/
multiline_comment|/* cpu_to_cfi16() and cfi16_to_cpu() are not needed because the LART&n; * only has 32 bit wide Flash memory. -- Erik&n; */
DECL|macro|cpu_to_cfi16
mdefine_line|#define cpu_to_cfi16(x) (x)
DECL|macro|cfi16_to_cpu
mdefine_line|#define cfi16_to_cpu(x) (x)
DECL|function|cfi32_to_cpu
r_static
r_inline
id|__u32
id|cfi32_to_cpu
c_func
(paren
id|__u32
id|x
)paren
(brace
id|__u32
id|ret
suffix:semicolon
id|ret
op_assign
(paren
id|x
op_amp
l_int|0x08009000
)paren
op_rshift
l_int|11
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00002000
)paren
op_rshift
l_int|10
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x04004000
)paren
op_rshift
l_int|8
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00000010
)paren
op_rshift
l_int|4
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x91000820
)paren
op_rshift
l_int|3
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x22080080
)paren
op_rshift
l_int|2
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x40000400
)paren
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00040040
)paren
op_lshift
l_int|1
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00110000
)paren
op_lshift
l_int|4
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00220100
)paren
op_lshift
l_int|5
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00800208
)paren
op_lshift
l_int|6
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00400004
)paren
op_lshift
l_int|9
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00000001
)paren
op_lshift
l_int|12
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00000002
)paren
op_lshift
l_int|13
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cpu_to_cfi32
r_static
r_inline
id|__u32
id|cpu_to_cfi32
c_func
(paren
id|__u32
id|x
)paren
(brace
id|__u32
id|ret
suffix:semicolon
id|ret
op_assign
(paren
id|x
op_amp
l_int|0x00010012
)paren
op_lshift
l_int|11
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00000008
)paren
op_lshift
l_int|10
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00040040
)paren
op_lshift
l_int|8
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00000001
)paren
op_lshift
l_int|4
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x12200104
)paren
op_lshift
l_int|3
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x08820020
)paren
op_lshift
l_int|2
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x40000400
)paren
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00080080
)paren
op_rshift
l_int|1
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x01100000
)paren
op_rshift
l_int|4
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x04402000
)paren
op_rshift
l_int|5
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x20008200
)paren
op_rshift
l_int|6
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x80000800
)paren
op_rshift
l_int|9
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00001000
)paren
op_rshift
l_int|12
suffix:semicolon
id|ret
op_or_assign
(paren
id|x
op_amp
l_int|0x00004000
)paren
op_rshift
l_int|13
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#else
macro_line|#error No CFI endianness defined
macro_line|#endif
eof
