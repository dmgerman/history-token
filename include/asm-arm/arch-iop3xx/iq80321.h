multiline_comment|/*&n; * linux/include/asm/arch-iop3xx/iq80321.h&n; *&n; * Intel IQ-80321 evaluation board registers&n; */
macro_line|#ifndef _IQ80321_H_
DECL|macro|_IQ80321_H_
mdefine_line|#define _IQ80321_H_
DECL|macro|IQ80321_RAMBASE
mdefine_line|#define IQ80321_RAMBASE      0xa0000000
DECL|macro|IQ80321_UART1
mdefine_line|#define IQ80321_UART1        0xfe800000    /* UART #1 */
DECL|macro|IQ80321_7SEG_1
mdefine_line|#define IQ80321_7SEG_1       0xfe840000    /* 7-Segment MSB */
DECL|macro|IQ80321_7SEG_0
mdefine_line|#define IQ80321_7SEG_0       0xfe850000    /* 7-Segment LSB (WO) */
DECL|macro|IQ80321_ROTARY_SW
mdefine_line|#define IQ80321_ROTARY_SW    0xfe8d0000    /* Rotary Switch */
DECL|macro|IQ80321_BATT_STAT
mdefine_line|#define IQ80321_BATT_STAT    0xfe8f0000    /* Battery Status */
macro_line|#endif&t;
singleline_comment|// _IQ80321_H_
eof
