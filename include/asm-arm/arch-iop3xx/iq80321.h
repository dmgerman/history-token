multiline_comment|/*&n; * linux/include/asm/arch-iop3xx/iq80321.h&n; *&n; * Intel IQ80321 evaluation board registers&n; */
macro_line|#ifndef _IQ80321_H_
DECL|macro|_IQ80321_H_
mdefine_line|#define _IQ80321_H_
DECL|macro|IQ80321_FLASHBASE
mdefine_line|#define&t;IQ80321_FLASHBASE&t;0xf0000000&t;/* Flash */
DECL|macro|IQ80321_FLASHSIZE
mdefine_line|#define&t;IQ80321_FLASHSIZE&t;0x00800000
DECL|macro|IQ80321_FLASHWIDTH
mdefine_line|#define&t;IQ80321_FLASHWIDTH&t;1
DECL|macro|IQ80321_UART
mdefine_line|#define IQ80321_UART&t;&t;0xfe800000&t;/* UART #1 */
DECL|macro|IQ80321_7SEG_1
mdefine_line|#define IQ80321_7SEG_1&t;&t;0xfe840000&t;/* 7-Segment MSB */
DECL|macro|IQ80321_7SEG_0
mdefine_line|#define IQ80321_7SEG_0&t;&t;0xfe850000&t;/* 7-Segment LSB (WO) */
DECL|macro|IQ80321_ROTARY_SW
mdefine_line|#define IQ80321_ROTARY_SW&t;0xfe8d0000&t;/* Rotary Switch */
DECL|macro|IQ80321_BATT_STAT
mdefine_line|#define IQ80321_BATT_STAT&t;0xfe8f0000&t;/* Battery Status */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|iq80321_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;
singleline_comment|// _IQ80321_H_
eof
