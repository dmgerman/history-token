multiline_comment|/*&n; * linux/include/asm/arch-iop3xx/iq80332.h&n; *&n; * Intel IQ80332 evaluation board registers&n; */
macro_line|#ifndef _IQ80332_H_
DECL|macro|_IQ80332_H_
mdefine_line|#define _IQ80332_H_
DECL|macro|IQ80332_FLASHBASE
mdefine_line|#define&t;IQ80332_FLASHBASE&t;0xc0000000&t;/* Flash */
DECL|macro|IQ80332_FLASHSIZE
mdefine_line|#define&t;IQ80332_FLASHSIZE&t;0x00800000
DECL|macro|IQ80332_FLASHWIDTH
mdefine_line|#define&t;IQ80332_FLASHWIDTH&t;1
DECL|macro|IQ80332_7SEG_1
mdefine_line|#define IQ80332_7SEG_1&t;&t;0xce840000&t;/* 7-Segment MSB */
DECL|macro|IQ80332_7SEG_0
mdefine_line|#define IQ80332_7SEG_0&t;&t;0xce850000&t;/* 7-Segment LSB (WO) */
DECL|macro|IQ80332_ROTARY_SW
mdefine_line|#define IQ80332_ROTARY_SW&t;0xce8d0000&t;/* Rotary Switch */
DECL|macro|IQ80332_BATT_STAT
mdefine_line|#define IQ80332_BATT_STAT&t;0xce8f0000&t;/* Battery Status */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|iq80332_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;
singleline_comment|// _IQ80332_H_
eof
