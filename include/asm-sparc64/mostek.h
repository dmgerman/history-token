multiline_comment|/* $Id: mostek.h,v 1.4 2001/01/11 15:07:09 davem Exp $&n; * mostek.h:  Describes the various Mostek time of day clock registers.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@eden.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_MOSTEK_H
DECL|macro|_SPARC64_MOSTEK_H
mdefine_line|#define _SPARC64_MOSTEK_H
macro_line|#include &lt;asm/idprom.h&gt;
multiline_comment|/*       M48T02 Register Map (adapted from Sun NVRAM/Hostid FAQ)&n; *&n; *                             Data&n; * Address                                                 Function&n; *        Bit 7 Bit 6 Bit 5 Bit 4Bit 3 Bit 2 Bit 1 Bit 0&n; *   7ff  -     -     -     -    -     -     -     -       Year 00-99&n; *   7fe  0     0     0     -    -     -     -     -      Month 01-12&n; *   7fd  0     0     -     -    -     -     -     -       Date 01-31&n; *   7fc  0     FT    0     0    0     -     -     -        Day 01-07&n; *   7fb  KS    0     -     -    -     -     -     -      Hours 00-23&n; *   7fa  0     -     -     -    -     -     -     -    Minutes 00-59&n; *   7f9  ST    -     -     -    -     -     -     -    Seconds 00-59&n; *   7f8  W     R     S     -    -     -     -     -    Control&n; *&n; *   * ST is STOP BIT&n; *   * W is WRITE BIT&n; *   * R is READ BIT&n; *   * S is SIGN BIT&n; *   * FT is FREQ TEST BIT&n; *   * KS is KICK START BIT&n; */
multiline_comment|/* The Mostek 48t02 real time clock and NVRAM chip. The registers&n; * other than the control register are in binary coded decimal. Some&n; * control bits also live outside the control register.&n; *&n; * We now deal with physical addresses for I/O to the chip. -DaveM&n; */
DECL|function|mostek_read
r_static
id|__inline__
id|u8
id|mostek_read
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u8
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduba&t;[%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|mostek_write
r_static
id|__inline__
r_void
id|mostek_write
c_func
(paren
r_int
r_int
id|addr
comma
id|u8
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stba&t;%0, [%1] %2&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|macro|MOSTEK_EEPROM
mdefine_line|#define MOSTEK_EEPROM&t;&t;0x0000UL
DECL|macro|MOSTEK_IDPROM
mdefine_line|#define MOSTEK_IDPROM&t;&t;0x07d8UL
DECL|macro|MOSTEK_CREG
mdefine_line|#define MOSTEK_CREG&t;&t;0x07f8UL
DECL|macro|MOSTEK_SEC
mdefine_line|#define MOSTEK_SEC&t;&t;0x07f9UL
DECL|macro|MOSTEK_MIN
mdefine_line|#define MOSTEK_MIN&t;&t;0x07faUL
DECL|macro|MOSTEK_HOUR
mdefine_line|#define MOSTEK_HOUR&t;&t;0x07fbUL
DECL|macro|MOSTEK_DOW
mdefine_line|#define MOSTEK_DOW&t;&t;0x07fcUL
DECL|macro|MOSTEK_DOM
mdefine_line|#define MOSTEK_DOM&t;&t;0x07fdUL
DECL|macro|MOSTEK_MONTH
mdefine_line|#define MOSTEK_MONTH&t;&t;0x07feUL
DECL|macro|MOSTEK_YEAR
mdefine_line|#define MOSTEK_YEAR&t;&t;0x07ffUL
r_extern
id|spinlock_t
id|mostek_lock
suffix:semicolon
r_extern
r_int
r_int
id|mstk48t02_regs
suffix:semicolon
multiline_comment|/* Control register values. */
DECL|macro|MSTK_CREG_WRITE
mdefine_line|#define&t;MSTK_CREG_WRITE&t;0x80&t;/* Must set this before placing values. */
DECL|macro|MSTK_CREG_READ
mdefine_line|#define&t;MSTK_CREG_READ&t;0x40&t;/* Stop updates to allow a clean read. */
DECL|macro|MSTK_CREG_SIGN
mdefine_line|#define&t;MSTK_CREG_SIGN&t;0x20&t;/* Slow/speed clock in calibration mode. */
multiline_comment|/* Control bits that live in the other registers. */
DECL|macro|MSTK_STOP
mdefine_line|#define&t;MSTK_STOP&t;0x80&t;/* Stop the clock oscillator. (sec) */
DECL|macro|MSTK_KICK_START
mdefine_line|#define&t;MSTK_KICK_START&t;0x80&t;/* Kick start the clock chip. (hour) */
DECL|macro|MSTK_FREQ_TEST
mdefine_line|#define MSTK_FREQ_TEST&t;0x40&t;/* Frequency test mode. (day) */
DECL|macro|MSTK_YEAR_ZERO
mdefine_line|#define MSTK_YEAR_ZERO       1968   /* If year reg has zero, it is 1968. */
DECL|macro|MSTK_CVT_YEAR
mdefine_line|#define MSTK_CVT_YEAR(yr)  ((yr) + MSTK_YEAR_ZERO)
multiline_comment|/* Masks that define how much space each value takes up. */
DECL|macro|MSTK_SEC_MASK
mdefine_line|#define&t;MSTK_SEC_MASK&t;0x7f
DECL|macro|MSTK_MIN_MASK
mdefine_line|#define&t;MSTK_MIN_MASK&t;0x7f
DECL|macro|MSTK_HOUR_MASK
mdefine_line|#define&t;MSTK_HOUR_MASK&t;0x3f
DECL|macro|MSTK_DOW_MASK
mdefine_line|#define&t;MSTK_DOW_MASK&t;0x07
DECL|macro|MSTK_DOM_MASK
mdefine_line|#define&t;MSTK_DOM_MASK&t;0x3f
DECL|macro|MSTK_MONTH_MASK
mdefine_line|#define&t;MSTK_MONTH_MASK&t;0x1f
DECL|macro|MSTK_YEAR_MASK
mdefine_line|#define&t;MSTK_YEAR_MASK&t;0xff
multiline_comment|/* Binary coded decimal conversion macros. */
DECL|macro|MSTK_REGVAL_TO_DECIMAL
mdefine_line|#define MSTK_REGVAL_TO_DECIMAL(x)  (((x) &amp; 0x0F) + 0x0A * ((x) &gt;&gt; 0x04))
DECL|macro|MSTK_DECIMAL_TO_REGVAL
mdefine_line|#define MSTK_DECIMAL_TO_REGVAL(x)  ((((x) / 0x0A) &lt;&lt; 0x04) + ((x) % 0x0A))
multiline_comment|/* Generic register set and get macros for internal use. */
DECL|macro|MSTK_GET
mdefine_line|#define MSTK_GET(regs,name)&t;&bslash;&n;&t;(MSTK_REGVAL_TO_DECIMAL(mostek_read(regs + MOSTEK_ ## name) &amp; MSTK_ ## name ## _MASK))
DECL|macro|MSTK_SET
mdefine_line|#define MSTK_SET(regs,name,value) &bslash;&n;do {&t;u8 __val = mostek_read(regs + MOSTEK_ ## name); &bslash;&n;&t;__val &amp;= ~(MSTK_ ## name ## _MASK); &bslash;&n;&t;__val |= (MSTK_DECIMAL_TO_REGVAL(value) &amp; &bslash;&n;&t;&t;  (MSTK_ ## name ## _MASK)); &bslash;&n;&t;mostek_write(regs + MOSTEK_ ## name, __val); &bslash;&n;} while(0)
multiline_comment|/* Macros to make register access easier on our fingers. These give you&n; * the decimal value of the register requested if applicable. You pass&n; * the a pointer to a &squot;struct mostek48t02&squot;.&n; */
DECL|macro|MSTK_REG_CREG
mdefine_line|#define&t;MSTK_REG_CREG(regs)&t;(mostek_read((regs) + MOSTEK_CREG))
DECL|macro|MSTK_REG_SEC
mdefine_line|#define&t;MSTK_REG_SEC(regs)&t;MSTK_GET(regs,SEC)
DECL|macro|MSTK_REG_MIN
mdefine_line|#define&t;MSTK_REG_MIN(regs)&t;MSTK_GET(regs,MIN)
DECL|macro|MSTK_REG_HOUR
mdefine_line|#define&t;MSTK_REG_HOUR(regs)&t;MSTK_GET(regs,HOUR)
DECL|macro|MSTK_REG_DOW
mdefine_line|#define&t;MSTK_REG_DOW(regs)&t;MSTK_GET(regs,DOW)
DECL|macro|MSTK_REG_DOM
mdefine_line|#define&t;MSTK_REG_DOM(regs)&t;MSTK_GET(regs,DOM)
DECL|macro|MSTK_REG_MONTH
mdefine_line|#define&t;MSTK_REG_MONTH(regs)&t;MSTK_GET(regs,MONTH)
DECL|macro|MSTK_REG_YEAR
mdefine_line|#define&t;MSTK_REG_YEAR(regs)&t;MSTK_GET(regs,YEAR)
DECL|macro|MSTK_SET_REG_SEC
mdefine_line|#define&t;MSTK_SET_REG_SEC(regs,value)&t;MSTK_SET(regs,SEC,value)
DECL|macro|MSTK_SET_REG_MIN
mdefine_line|#define&t;MSTK_SET_REG_MIN(regs,value)&t;MSTK_SET(regs,MIN,value)
DECL|macro|MSTK_SET_REG_HOUR
mdefine_line|#define&t;MSTK_SET_REG_HOUR(regs,value)&t;MSTK_SET(regs,HOUR,value)
DECL|macro|MSTK_SET_REG_DOW
mdefine_line|#define&t;MSTK_SET_REG_DOW(regs,value)&t;MSTK_SET(regs,DOW,value)
DECL|macro|MSTK_SET_REG_DOM
mdefine_line|#define&t;MSTK_SET_REG_DOM(regs,value)&t;MSTK_SET(regs,DOM,value)
DECL|macro|MSTK_SET_REG_MONTH
mdefine_line|#define&t;MSTK_SET_REG_MONTH(regs,value)&t;MSTK_SET(regs,MONTH,value)
DECL|macro|MSTK_SET_REG_YEAR
mdefine_line|#define&t;MSTK_SET_REG_YEAR(regs,value)&t;MSTK_SET(regs,YEAR,value)
multiline_comment|/* The Mostek 48t08 clock chip. Found on Sun4m&squot;s I think. It has the&n; * same (basically) layout of the 48t02 chip except for the extra&n; * NVRAM on board (8 KB against the 48t02&squot;s 2 KB).&n; */
DECL|macro|MOSTEK_48T08_OFFSET
mdefine_line|#define MOSTEK_48T08_OFFSET&t;0x0000UL&t;/* Lower NVRAM portions */
DECL|macro|MOSTEK_48T08_48T02
mdefine_line|#define MOSTEK_48T08_48T02&t;0x1800UL&t;/* Offset to 48T02 chip */
r_extern
r_int
r_int
id|mstk48t08_regs
suffix:semicolon
multiline_comment|/* SUN5 systems usually have 48t59 model clock chipsets.  But we keep the older&n; * clock chip definitions around just in case.&n; */
DECL|macro|MOSTEK_48T59_OFFSET
mdefine_line|#define MOSTEK_48T59_OFFSET&t;0x0000UL&t;/* Lower NVRAM portions */
DECL|macro|MOSTEK_48T59_48T02
mdefine_line|#define MOSTEK_48T59_48T02&t;0x1800UL&t;/* Offset to 48T02 chip */
r_extern
r_int
r_int
id|mstk48t59_regs
suffix:semicolon
macro_line|#endif /* !(_SPARC64_MOSTEK_H) */
eof
