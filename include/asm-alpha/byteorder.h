macro_line|#ifndef _ALPHA_BYTEORDER_H
DECL|macro|_ALPHA_BYTEORDER_H
mdefine_line|#define _ALPHA_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
macro_line|#ifdef __GNUC__
DECL|function|__arch__swab32
r_static
id|__inline
id|__u32
id|__attribute_const__
id|__arch__swab32
c_func
(paren
id|__u32
id|x
)paren
(brace
multiline_comment|/*&n;&t; * Unfortunately, we can&squot;t use the 6 instruction sequence&n;&t; * on ev6 since the latency of the UNPKBW is 3, which is&n;&t; * pretty hard to hide.  Just in case a future implementation&n;&t; * has a lower latency, here&squot;s the sequence (also by Mike Burrows)&n;&t; *&n;&t; * UNPKBW a0, v0       v0: 00AA00BB00CC00DD&n;&t; * SLL v0, 24, a0      a0: BB00CC00DD000000&n;&t; * BIS v0, a0, a0      a0: BBAACCBBDDCC00DD&n;&t; * EXTWL a0, 6, v0     v0: 000000000000BBAA&n;&t; * ZAP a0, 0xf3, a0    a0: 00000000DDCC0000&n;&t; * ADDL a0, v0, v0     v0: ssssssssDDCCBBAA&n;&t; */
id|__u64
id|t0
comma
id|t1
comma
id|t2
comma
id|t3
suffix:semicolon
id|t0
op_assign
id|__kernel_inslh
c_func
(paren
id|x
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/* t0 : 0000000000AABBCC */
id|t1
op_assign
id|__kernel_inswl
c_func
(paren
id|x
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* t1 : 000000CCDD000000 */
id|t1
op_or_assign
id|t0
suffix:semicolon
multiline_comment|/* t1 : 000000CCDDAABBCC */
id|t2
op_assign
id|t1
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* t2 : 0000000000CCDDAA */
id|t0
op_assign
id|t1
op_amp
l_int|0xFF00FF00
suffix:semicolon
multiline_comment|/* t0 : 00000000DD00BB00 */
id|t3
op_assign
id|t2
op_amp
l_int|0x00FF00FF
suffix:semicolon
multiline_comment|/* t3 : 0000000000CC00AA */
id|t1
op_assign
id|t0
op_plus
id|t3
suffix:semicolon
multiline_comment|/* t1 : ssssssssDDCCBBAA */
r_return
id|t1
suffix:semicolon
)brace
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32 __arch__swab32
macro_line|#endif /* __GNUC__ */
DECL|macro|__BYTEORDER_HAS_U64__
mdefine_line|#define __BYTEORDER_HAS_U64__
macro_line|#include &lt;linux/byteorder/little_endian.h&gt;
macro_line|#endif /* _ALPHA_BYTEORDER_H */
eof
