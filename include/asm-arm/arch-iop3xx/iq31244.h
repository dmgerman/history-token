multiline_comment|/*&n; * linux/include/asm/arch-iop3xx/iq31244.h&n; *&n; * Intel IQ31244 evaluation board registers&n; */
macro_line|#ifndef _IQ31244_H_
DECL|macro|_IQ31244_H_
mdefine_line|#define _IQ31244_H_
DECL|macro|IQ31244_FLASHBASE
mdefine_line|#define&t;IQ31244_FLASHBASE&t;0xf0000000&t;/* Flash */
DECL|macro|IQ31244_FLASHSIZE
mdefine_line|#define&t;IQ31244_FLASHSIZE&t;0x00800000
DECL|macro|IQ31244_FLASHWIDTH
mdefine_line|#define&t;IQ31244_FLASHWIDTH&t;2
DECL|macro|IQ31244_UART
mdefine_line|#define IQ31244_UART&t;&t;0xfe800000&t;/* UART #1 */
DECL|macro|IQ31244_7SEG_1
mdefine_line|#define IQ31244_7SEG_1&t;&t;0xfe840000&t;/* 7-Segment MSB */
DECL|macro|IQ31244_7SEG_0
mdefine_line|#define IQ31244_7SEG_0&t;&t;0xfe850000&t;/* 7-Segment LSB (WO) */
DECL|macro|IQ31244_ROTARY_SW
mdefine_line|#define IQ31244_ROTARY_SW&t;0xfe8d0000&t;/* Rotary Switch */
DECL|macro|IQ31244_BATT_STAT
mdefine_line|#define IQ31244_BATT_STAT&t;0xfe8f0000&t;/* Battery Status */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|iq31244_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;
singleline_comment|// _IQ31244_H_
eof
