multiline_comment|/* linux/include/asm/arch-s3c2410/regs-timer.h&n; *&n; * Copyright (c) 2003 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 Timer configuration&n; *&n; *  Changelog:&n; *    05-06-2003     BJD     Created file&n; *    26-06-2003     BJD     Added more timer definitions to mux / control&n; *    12-03-2004     BJD     Updated include protection&n; *    10-02-2005     BJD     Added S3C2410_TCFG1_MUX4_SHIFT (Guillaume Gourat)&n;*/
macro_line|#ifndef __ASM_ARCH_REGS_TIMER_H
DECL|macro|__ASM_ARCH_REGS_TIMER_H
mdefine_line|#define __ASM_ARCH_REGS_TIMER_H &quot;$Id: timer.h,v 1.4 2003/05/06 19:30:50 ben Exp $&quot;
DECL|macro|S3C2410_TIMERREG
mdefine_line|#define S3C2410_TIMERREG(x) (S3C2410_VA_TIMER + (x))
DECL|macro|S3C2410_TIMERREG2
mdefine_line|#define S3C2410_TIMERREG2(tmr,reg) S3C2410_TIMERREG((reg)+0x0c+((tmr)*0x0c))
DECL|macro|S3C2410_TCFG0
mdefine_line|#define S3C2410_TCFG0&t;      S3C2410_TIMERREG(0x00)
DECL|macro|S3C2410_TCFG1
mdefine_line|#define S3C2410_TCFG1&t;      S3C2410_TIMERREG(0x04)
DECL|macro|S3C2410_TCON
mdefine_line|#define S3C2410_TCON&t;      S3C2410_TIMERREG(0x08)
DECL|macro|S3C2410_TCFG_PRESCALER0_MASK
mdefine_line|#define S3C2410_TCFG_PRESCALER0_MASK (255&lt;&lt;0)
DECL|macro|S3C2410_TCFG_PRESCALER1_MASK
mdefine_line|#define S3C2410_TCFG_PRESCALER1_MASK (255&lt;&lt;8)
DECL|macro|S3C2410_TCFG_PRESCALER1_SHIFT
mdefine_line|#define S3C2410_TCFG_PRESCALER1_SHIFT (8)
DECL|macro|S3C2410_TCFG_DEADZONE_MASK
mdefine_line|#define S3C2410_TCFG_DEADZONE_MASK   (255&lt;&lt;16)
DECL|macro|S3C2410_TCFG_DEADZONE_SHIFT
mdefine_line|#define S3C2410_TCFG_DEADZONE_SHIFT  (16)
DECL|macro|S3C2410_TCFG1_MUX4_DIV2
mdefine_line|#define S3C2410_TCFG1_MUX4_DIV2&t;  (0&lt;&lt;16)
DECL|macro|S3C2410_TCFG1_MUX4_DIV4
mdefine_line|#define S3C2410_TCFG1_MUX4_DIV4&t;  (1&lt;&lt;16)
DECL|macro|S3C2410_TCFG1_MUX4_DIV8
mdefine_line|#define S3C2410_TCFG1_MUX4_DIV8&t;  (2&lt;&lt;16)
DECL|macro|S3C2410_TCFG1_MUX4_DIV16
mdefine_line|#define S3C2410_TCFG1_MUX4_DIV16  (3&lt;&lt;16)
DECL|macro|S3C2410_TCFG1_MUX4_TCLK1
mdefine_line|#define S3C2410_TCFG1_MUX4_TCLK1  (4&lt;&lt;16)
DECL|macro|S3C2410_TCFG1_MUX4_MASK
mdefine_line|#define S3C2410_TCFG1_MUX4_MASK&t;  (15&lt;&lt;16)
DECL|macro|S3C2410_TCFG1_MUX4_SHIFT
mdefine_line|#define S3C2410_TCFG1_MUX4_SHIFT  (16)
DECL|macro|S3C2410_TCFG1_MUX3_DIV2
mdefine_line|#define S3C2410_TCFG1_MUX3_DIV2&t;  (0&lt;&lt;12)
DECL|macro|S3C2410_TCFG1_MUX3_DIV4
mdefine_line|#define S3C2410_TCFG1_MUX3_DIV4&t;  (1&lt;&lt;12)
DECL|macro|S3C2410_TCFG1_MUX3_DIV8
mdefine_line|#define S3C2410_TCFG1_MUX3_DIV8&t;  (2&lt;&lt;12)
DECL|macro|S3C2410_TCFG1_MUX3_DIV16
mdefine_line|#define S3C2410_TCFG1_MUX3_DIV16  (3&lt;&lt;12)
DECL|macro|S3C2410_TCFG1_MUX3_TCLK1
mdefine_line|#define S3C2410_TCFG1_MUX3_TCLK1  (4&lt;&lt;12)
DECL|macro|S3C2410_TCFG1_MUX3_MASK
mdefine_line|#define S3C2410_TCFG1_MUX3_MASK&t;  (15&lt;&lt;12)
DECL|macro|S3C2410_TCFG1_MUX2_DIV2
mdefine_line|#define S3C2410_TCFG1_MUX2_DIV2&t;  (0&lt;&lt;8)
DECL|macro|S3C2410_TCFG1_MUX2_DIV4
mdefine_line|#define S3C2410_TCFG1_MUX2_DIV4&t;  (1&lt;&lt;8)
DECL|macro|S3C2410_TCFG1_MUX2_DIV8
mdefine_line|#define S3C2410_TCFG1_MUX2_DIV8&t;  (2&lt;&lt;8)
DECL|macro|S3C2410_TCFG1_MUX2_DIV16
mdefine_line|#define S3C2410_TCFG1_MUX2_DIV16  (3&lt;&lt;8)
DECL|macro|S3C2410_TCFG1_MUX2_TCLK1
mdefine_line|#define S3C2410_TCFG1_MUX2_TCLK1  (4&lt;&lt;8)
DECL|macro|S3C2410_TCFG1_MUX2_MASK
mdefine_line|#define S3C2410_TCFG1_MUX2_MASK&t;  (15&lt;&lt;8)
DECL|macro|S3C2410_TCFG1_MUX1_DIV2
mdefine_line|#define S3C2410_TCFG1_MUX1_DIV2&t;  (0&lt;&lt;4)
DECL|macro|S3C2410_TCFG1_MUX1_DIV4
mdefine_line|#define S3C2410_TCFG1_MUX1_DIV4&t;  (1&lt;&lt;4)
DECL|macro|S3C2410_TCFG1_MUX1_DIV8
mdefine_line|#define S3C2410_TCFG1_MUX1_DIV8&t;  (2&lt;&lt;4)
DECL|macro|S3C2410_TCFG1_MUX1_DIV16
mdefine_line|#define S3C2410_TCFG1_MUX1_DIV16  (3&lt;&lt;4)
DECL|macro|S3C2410_TCFG1_MUX1_TCLK0
mdefine_line|#define S3C2410_TCFG1_MUX1_TCLK0  (4&lt;&lt;4)
DECL|macro|S3C2410_TCFG1_MUX1_MASK
mdefine_line|#define S3C2410_TCFG1_MUX1_MASK&t;  (15&lt;&lt;4)
DECL|macro|S3C2410_TCFG1_MUX0_DIV2
mdefine_line|#define S3C2410_TCFG1_MUX0_DIV2&t;  (0&lt;&lt;0)
DECL|macro|S3C2410_TCFG1_MUX0_DIV4
mdefine_line|#define S3C2410_TCFG1_MUX0_DIV4&t;  (1&lt;&lt;0)
DECL|macro|S3C2410_TCFG1_MUX0_DIV8
mdefine_line|#define S3C2410_TCFG1_MUX0_DIV8&t;  (2&lt;&lt;0)
DECL|macro|S3C2410_TCFG1_MUX0_DIV16
mdefine_line|#define S3C2410_TCFG1_MUX0_DIV16  (3&lt;&lt;0)
DECL|macro|S3C2410_TCFG1_MUX0_TCLK0
mdefine_line|#define S3C2410_TCFG1_MUX0_TCLK0  (4&lt;&lt;0)
DECL|macro|S3C2410_TCFG1_MUX0_MASK
mdefine_line|#define S3C2410_TCFG1_MUX0_MASK&t;  (15&lt;&lt;0)
multiline_comment|/* for each timer, we have an count buffer, an compare buffer and&n; * an observation buffer&n;*/
multiline_comment|/* WARNING - timer 4 has no buffer reg, and it&squot;s observation is at +4 */
DECL|macro|S3C2410_TCNTB
mdefine_line|#define S3C2410_TCNTB(tmr)    S3C2410_TIMERREG2(tmr, 0x00)
DECL|macro|S3C2410_TCMPB
mdefine_line|#define S3C2410_TCMPB(tmr)    S3C2410_TIMERREG2(tmr, 0x04)
DECL|macro|S3C2410_TCNTO
mdefine_line|#define S3C2410_TCNTO(tmr)    S3C2410_TIMERREG2(tmr, (((tmr) == 4) ? 0x04 : 0x08))
DECL|macro|S3C2410_TCON_T4RELOAD
mdefine_line|#define S3C2410_TCON_T4RELOAD&t;  (1&lt;&lt;22)
DECL|macro|S3C2410_TCON_T4MANUALUPD
mdefine_line|#define S3C2410_TCON_T4MANUALUPD  (1&lt;&lt;21)
DECL|macro|S3C2410_TCON_T4START
mdefine_line|#define S3C2410_TCON_T4START&t;  (1&lt;&lt;20)
DECL|macro|S3C2410_TCON_T3RELOAD
mdefine_line|#define S3C2410_TCON_T3RELOAD&t;  (1&lt;&lt;19)
DECL|macro|S3C2410_TCON_T3INVERT
mdefine_line|#define S3C2410_TCON_T3INVERT&t;  (1&lt;&lt;18)
DECL|macro|S3C2410_TCON_T3MANUALUPD
mdefine_line|#define S3C2410_TCON_T3MANUALUPD  (1&lt;&lt;17)
DECL|macro|S3C2410_TCON_T3START
mdefine_line|#define S3C2410_TCON_T3START&t;  (1&lt;&lt;16)
DECL|macro|S3C2410_TCON_T2RELOAD
mdefine_line|#define S3C2410_TCON_T2RELOAD&t;  (1&lt;&lt;15)
DECL|macro|S3C2410_TCON_T2INVERT
mdefine_line|#define S3C2410_TCON_T2INVERT&t;  (1&lt;&lt;14)
DECL|macro|S3C2410_TCON_T2MANUALUPD
mdefine_line|#define S3C2410_TCON_T2MANUALUPD  (1&lt;&lt;13)
DECL|macro|S3C2410_TCON_T2START
mdefine_line|#define S3C2410_TCON_T2START&t;  (1&lt;&lt;12)
DECL|macro|S3C2410_TCON_T1RELOAD
mdefine_line|#define S3C2410_TCON_T1RELOAD&t;  (1&lt;&lt;11)
DECL|macro|S3C2410_TCON_T1INVERT
mdefine_line|#define S3C2410_TCON_T1INVERT&t;  (1&lt;&lt;10)
DECL|macro|S3C2410_TCON_T1MANUALUPD
mdefine_line|#define S3C2410_TCON_T1MANUALUPD  (1&lt;&lt;9)
DECL|macro|S3C2410_TCON_T1START
mdefine_line|#define S3C2410_TCON_T1START&t;  (1&lt;&lt;8)
DECL|macro|S3C2410_TCON_T0DEADZONE
mdefine_line|#define S3C2410_TCON_T0DEADZONE&t;  (1&lt;&lt;4)
DECL|macro|S3C2410_TCON_T0RELOAD
mdefine_line|#define S3C2410_TCON_T0RELOAD&t;  (1&lt;&lt;3)
DECL|macro|S3C2410_TCON_T0INVERT
mdefine_line|#define S3C2410_TCON_T0INVERT&t;  (1&lt;&lt;2)
DECL|macro|S3C2410_TCON_T0MANUALUPD
mdefine_line|#define S3C2410_TCON_T0MANUALUPD  (1&lt;&lt;1)
DECL|macro|S3C2410_TCON_T0START
mdefine_line|#define S3C2410_TCON_T0START&t;  (1&lt;&lt;0)
macro_line|#endif /*  __ASM_ARCH_REGS_TIMER_H */
eof
