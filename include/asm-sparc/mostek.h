multiline_comment|/* $Id: mostek.h,v 1.12 1999/08/31 18:51:41 davem Exp $&n; * mostek.h:  Describes the various Mostek time of day clock registers.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@eden.rutgers.edu)&n; * Added intersil code 05/25/98 Chris Davis (cdavis@cois.on.ca)&n; */
macro_line|#ifndef _SPARC_MOSTEK_H
DECL|macro|_SPARC_MOSTEK_H
mdefine_line|#define _SPARC_MOSTEK_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/idprom.h&gt;
multiline_comment|/*       M48T02 Register Map (adapted from Sun NVRAM/Hostid FAQ)&n; *&n; *                             Data&n; * Address                                                 Function&n; *        Bit 7 Bit 6 Bit 5 Bit 4Bit 3 Bit 2 Bit 1 Bit 0&n; *   7ff  -     -     -     -    -     -     -     -       Year 00-99&n; *   7fe  0     0     0     -    -     -     -     -      Month 01-12&n; *   7fd  0     0     -     -    -     -     -     -       Date 01-31&n; *   7fc  0     FT    0     0    0     -     -     -        Day 01-07&n; *   7fb  KS    0     -     -    -     -     -     -      Hours 00-23&n; *   7fa  0     -     -     -    -     -     -     -    Minutes 00-59&n; *   7f9  ST    -     -     -    -     -     -     -    Seconds 00-59&n; *   7f8  W     R     S     -    -     -     -     -    Control&n; *&n; *   * ST is STOP BIT&n; *   * W is WRITE BIT&n; *   * R is READ BIT&n; *   * S is SIGN BIT&n; *   * FT is FREQ TEST BIT&n; *   * KS is KICK START BIT&n; */
multiline_comment|/* The Mostek 48t02 real time clock and NVRAM chip. The registers&n; * other than the control register are in binary coded decimal. Some&n; * control bits also live outside the control register.&n; */
DECL|macro|mostek_read
mdefine_line|#define mostek_read(_addr)&t;&t;(*((volatile u8 *)(_addr)))
DECL|macro|mostek_write
mdefine_line|#define mostek_write(_addr,_val)&t;((*((volatile u8 *)(_addr))) = (_val))
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
DECL|struct|mostek48t02
r_struct
id|mostek48t02
(brace
DECL|member|eeprom
r_volatile
r_char
id|eeprom
(braket
l_int|2008
)braket
suffix:semicolon
multiline_comment|/* This is the eeprom, don&squot;t touch! */
DECL|member|idprom
r_struct
id|idprom
id|idprom
suffix:semicolon
multiline_comment|/* The idprom lives here. */
DECL|member|creg
r_volatile
r_int
r_char
id|creg
suffix:semicolon
multiline_comment|/* Control register */
DECL|member|sec
r_volatile
r_int
r_char
id|sec
suffix:semicolon
multiline_comment|/* Seconds (0-59) */
DECL|member|min
r_volatile
r_int
r_char
id|min
suffix:semicolon
multiline_comment|/* Minutes (0-59) */
DECL|member|hour
r_volatile
r_int
r_char
id|hour
suffix:semicolon
multiline_comment|/* Hour (0-23) */
DECL|member|dow
r_volatile
r_int
r_char
id|dow
suffix:semicolon
multiline_comment|/* Day of the week (1-7) */
DECL|member|dom
r_volatile
r_int
r_char
id|dom
suffix:semicolon
multiline_comment|/* Day of the month (1-31) */
DECL|member|month
r_volatile
r_int
r_char
id|month
suffix:semicolon
multiline_comment|/* Month of year (1-12) */
DECL|member|year
r_volatile
r_int
r_char
id|year
suffix:semicolon
multiline_comment|/* Year (0-99) */
)brace
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
mdefine_line|#define MSTK_GET(regs,var,mask) (MSTK_REGVAL_TO_DECIMAL(((struct mostek48t02 *)regs)-&gt;var &amp; MSTK_ ## mask ## _MASK))
DECL|macro|MSTK_SET
mdefine_line|#define MSTK_SET(regs,var,value,mask) do { ((struct mostek48t02 *)regs)-&gt;var &amp;= ~(MSTK_ ## mask ## _MASK); ((struct mostek48t02 *)regs)-&gt;var |= MSTK_DECIMAL_TO_REGVAL(value) &amp; (MSTK_ ## mask ## _MASK); } while (0)
multiline_comment|/* Macros to make register access easier on our fingers. These give you&n; * the decimal value of the register requested if applicable. You pass&n; * the a pointer to a &squot;struct mostek48t02&squot;.&n; */
DECL|macro|MSTK_REG_CREG
mdefine_line|#define&t;MSTK_REG_CREG(regs)&t;(((struct mostek48t02 *)regs)-&gt;creg)
DECL|macro|MSTK_REG_SEC
mdefine_line|#define&t;MSTK_REG_SEC(regs)&t;MSTK_GET(regs,sec,SEC)
DECL|macro|MSTK_REG_MIN
mdefine_line|#define&t;MSTK_REG_MIN(regs)&t;MSTK_GET(regs,min,MIN)
DECL|macro|MSTK_REG_HOUR
mdefine_line|#define&t;MSTK_REG_HOUR(regs)&t;MSTK_GET(regs,hour,HOUR)
DECL|macro|MSTK_REG_DOW
mdefine_line|#define&t;MSTK_REG_DOW(regs)&t;MSTK_GET(regs,dow,DOW)
DECL|macro|MSTK_REG_DOM
mdefine_line|#define&t;MSTK_REG_DOM(regs)&t;MSTK_GET(regs,dom,DOM)
DECL|macro|MSTK_REG_MONTH
mdefine_line|#define&t;MSTK_REG_MONTH(regs)&t;MSTK_GET(regs,month,MONTH)
DECL|macro|MSTK_REG_YEAR
mdefine_line|#define&t;MSTK_REG_YEAR(regs)&t;MSTK_GET(regs,year,YEAR)
DECL|macro|MSTK_SET_REG_SEC
mdefine_line|#define&t;MSTK_SET_REG_SEC(regs,value)&t;MSTK_SET(regs,sec,value,SEC)
DECL|macro|MSTK_SET_REG_MIN
mdefine_line|#define&t;MSTK_SET_REG_MIN(regs,value)&t;MSTK_SET(regs,min,value,MIN)
DECL|macro|MSTK_SET_REG_HOUR
mdefine_line|#define&t;MSTK_SET_REG_HOUR(regs,value)&t;MSTK_SET(regs,hour,value,HOUR)
DECL|macro|MSTK_SET_REG_DOW
mdefine_line|#define&t;MSTK_SET_REG_DOW(regs,value)&t;MSTK_SET(regs,dow,value,DOW)
DECL|macro|MSTK_SET_REG_DOM
mdefine_line|#define&t;MSTK_SET_REG_DOM(regs,value)&t;MSTK_SET(regs,dom,value,DOM)
DECL|macro|MSTK_SET_REG_MONTH
mdefine_line|#define&t;MSTK_SET_REG_MONTH(regs,value)&t;MSTK_SET(regs,month,value,MONTH)
DECL|macro|MSTK_SET_REG_YEAR
mdefine_line|#define&t;MSTK_SET_REG_YEAR(regs,value)&t;MSTK_SET(regs,year,value,YEAR)
multiline_comment|/* The Mostek 48t08 clock chip. Found on Sun4m&squot;s I think. It has the&n; * same (basically) layout of the 48t02 chip except for the extra&n; * NVRAM on board (8 KB against the 48t02&squot;s 2 KB).&n; */
DECL|struct|mostek48t08
r_struct
id|mostek48t08
(brace
DECL|member|offset
r_char
id|offset
(braket
l_int|6
op_star
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* Magic things may be here, who knows? */
DECL|member|regs
r_struct
id|mostek48t02
id|regs
suffix:semicolon
multiline_comment|/* Here is what we are interested in.   */
)brace
suffix:semicolon
r_extern
r_struct
id|mostek48t08
op_star
id|mstk48t08_regs
suffix:semicolon
r_extern
r_enum
id|sparc_clock_type
id|sp_clock_typ
suffix:semicolon
macro_line|#ifdef CONFIG_SUN4
DECL|enum|sparc_clock_type
DECL|enumerator|MSTK48T02
DECL|enumerator|MSTK48T08
r_enum
id|sparc_clock_type
(brace
id|MSTK48T02
comma
id|MSTK48T08
comma
"&bslash;"
DECL|enumerator|INTERSIL
DECL|enumerator|MSTK_INVALID
id|INTERSIL
comma
id|MSTK_INVALID
)brace
suffix:semicolon
macro_line|#else
DECL|enum|sparc_clock_type
DECL|enumerator|MSTK48T02
DECL|enumerator|MSTK48T08
r_enum
id|sparc_clock_type
(brace
id|MSTK48T02
comma
id|MSTK48T08
comma
"&bslash;"
DECL|enumerator|MSTK_INVALID
id|MSTK_INVALID
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SUN4
multiline_comment|/* intersil on a sun 4/260 code  data from harris doc */
DECL|struct|intersil_dt
r_struct
id|intersil_dt
(brace
DECL|member|int_csec
r_volatile
r_int
r_char
id|int_csec
suffix:semicolon
DECL|member|int_hour
r_volatile
r_int
r_char
id|int_hour
suffix:semicolon
DECL|member|int_min
r_volatile
r_int
r_char
id|int_min
suffix:semicolon
DECL|member|int_sec
r_volatile
r_int
r_char
id|int_sec
suffix:semicolon
DECL|member|int_month
r_volatile
r_int
r_char
id|int_month
suffix:semicolon
DECL|member|int_day
r_volatile
r_int
r_char
id|int_day
suffix:semicolon
DECL|member|int_year
r_volatile
r_int
r_char
id|int_year
suffix:semicolon
DECL|member|int_dow
r_volatile
r_int
r_char
id|int_dow
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|intersil
r_struct
id|intersil
(brace
DECL|member|clk
r_struct
id|intersil_dt
id|clk
suffix:semicolon
DECL|member|cmp
r_struct
id|intersil_dt
id|cmp
suffix:semicolon
DECL|member|int_intr_reg
r_volatile
r_int
r_char
id|int_intr_reg
suffix:semicolon
DECL|member|int_cmd_reg
r_volatile
r_int
r_char
id|int_cmd_reg
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INTERSIL_STOP
mdefine_line|#define INTERSIL_STOP        0x0
DECL|macro|INTERSIL_START
mdefine_line|#define INTERSIL_START       0x8
DECL|macro|INTERSIL_INTR_DISABLE
mdefine_line|#define INTERSIL_INTR_DISABLE   0x0
DECL|macro|INTERSIL_INTR_ENABLE
mdefine_line|#define INTERSIL_INTR_ENABLE   0x10
DECL|macro|INTERSIL_32K
mdefine_line|#define INTERSIL_32K&t;&t;0x0
DECL|macro|INTERSIL_NORMAL
mdefine_line|#define INTERSIL_NORMAL&t;&t;0x0
DECL|macro|INTERSIL_24H
mdefine_line|#define INTERSIL_24H&t;&t;0x4 
DECL|macro|INTERSIL_INT_100HZ
mdefine_line|#define INTERSIL_INT_100HZ&t;0x2
multiline_comment|/* end of intersil info */
macro_line|#endif
macro_line|#endif /* !(_SPARC_MOSTEK_H) */
eof
