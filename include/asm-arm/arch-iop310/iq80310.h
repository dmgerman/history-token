multiline_comment|/*&n; * linux/include/asm/arch-iop80310/iq80310.h&n; *&n; * Intel IQ-80310 evaluation board registers&n; */
macro_line|#ifndef _IQ80310_H_
DECL|macro|_IQ80310_H_
mdefine_line|#define _IQ80310_H_
DECL|macro|IQ80310_RAMBASE
mdefine_line|#define IQ80310_RAMBASE      0xa0000000
DECL|macro|IQ80310_UART1
mdefine_line|#define IQ80310_UART1        0xfe800000    /* UART #1 */
DECL|macro|IQ80310_UART2
mdefine_line|#define IQ80310_UART2        0xfe810000    /* UART #2 */
DECL|macro|IQ80310_INT_STAT
mdefine_line|#define IQ80310_INT_STAT     0xfe820000    /* Interrupt (XINT3#) Status */
DECL|macro|IQ80310_BOARD_REV
mdefine_line|#define IQ80310_BOARD_REV    0xfe830000    /* Board revision register */
DECL|macro|IQ80310_CPLD_REV
mdefine_line|#define IQ80310_CPLD_REV     0xfe840000    /* CPLD revision register */
DECL|macro|IQ80310_7SEG_1
mdefine_line|#define IQ80310_7SEG_1       0xfe840000    /* 7-Segment MSB */
DECL|macro|IQ80310_7SEG_0
mdefine_line|#define IQ80310_7SEG_0       0xfe850000    /* 7-Segment LSB (WO) */
DECL|macro|IQ80310_PCI_INT_STAT
mdefine_line|#define IQ80310_PCI_INT_STAT 0xfe850000    /* PCI Interrupt  Status */
DECL|macro|IQ80310_INT_MASK
mdefine_line|#define IQ80310_INT_MASK     0xfe860000    /* Interrupt (XINT3#) Mask */
DECL|macro|IQ80310_BACKPLANE
mdefine_line|#define IQ80310_BACKPLANE    0xfe870000    /* Backplane Detect */
DECL|macro|IQ80310_TIMER_LA0
mdefine_line|#define IQ80310_TIMER_LA0    0xfe880000    /* Timer LA0 */
DECL|macro|IQ80310_TIMER_LA1
mdefine_line|#define IQ80310_TIMER_LA1    0xfe890000    /* Timer LA1 */
DECL|macro|IQ80310_TIMER_LA2
mdefine_line|#define IQ80310_TIMER_LA2    0xfe8a0000    /* Timer LA2 */
DECL|macro|IQ80310_TIMER_LA3
mdefine_line|#define IQ80310_TIMER_LA3    0xfe8b0000    /* Timer LA3 */
DECL|macro|IQ80310_TIMER_EN
mdefine_line|#define IQ80310_TIMER_EN     0xfe8c0000    /* Timer Enable */
DECL|macro|IQ80310_ROTARY_SW
mdefine_line|#define IQ80310_ROTARY_SW    0xfe8d0000    /* Rotary Switch */
DECL|macro|IQ80310_JTAG
mdefine_line|#define IQ80310_JTAG         0xfe8e0000    /* JTAG Port Access */
DECL|macro|IQ80310_BATT_STAT
mdefine_line|#define IQ80310_BATT_STAT    0xfe8f0000    /* Battery Status */
macro_line|#endif&t;
singleline_comment|// _IQ80310_H_
eof
