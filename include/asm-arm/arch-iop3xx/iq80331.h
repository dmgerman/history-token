multiline_comment|/*&n; * linux/include/asm/arch-iop3xx/iq80331.h&n; *&n; * Intel IQ80331 evaluation board registers&n; */
macro_line|#ifndef _IQ80331_H_
DECL|macro|_IQ80331_H_
mdefine_line|#define _IQ80331_H_
DECL|macro|IQ80331_FLASHBASE
mdefine_line|#define&t;IQ80331_FLASHBASE&t;0xc0000000&t;/* Flash */
DECL|macro|IQ80331_FLASHSIZE
mdefine_line|#define&t;IQ80331_FLASHSIZE&t;0x00800000
DECL|macro|IQ80331_FLASHWIDTH
mdefine_line|#define&t;IQ80331_FLASHWIDTH&t;1
DECL|macro|IQ80331_7SEG_1
mdefine_line|#define IQ80331_7SEG_1&t;&t;0xce840000&t;/* 7-Segment MSB */
DECL|macro|IQ80331_7SEG_0
mdefine_line|#define IQ80331_7SEG_0&t;&t;0xce850000&t;/* 7-Segment LSB (WO) */
DECL|macro|IQ80331_ROTARY_SW
mdefine_line|#define IQ80331_ROTARY_SW&t;0xce8d0000&t;/* Rotary Switch */
DECL|macro|IQ80331_BATT_STAT
mdefine_line|#define IQ80331_BATT_STAT&t;0xce8f0000&t;/* Battery Status */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|iq80331_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;
singleline_comment|// _IQ80331_H_
eof
