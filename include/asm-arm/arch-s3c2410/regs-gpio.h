multiline_comment|/* linux/include/asm/hardware/s3c2410/&n; *&n; * Copyright (c) 2003 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 GPIO register definitions&n; *&n; *  Changelog:&n; *    19-06-2003     BJD     Created file&n; *    23-06-2003     BJD     Updated GSTATUS registers&n; *    12-03-2004     BJD     Updated include protection&n; */
macro_line|#ifndef __ASM_ARCH_REGS_GPIO_H
DECL|macro|__ASM_ARCH_REGS_GPIO_H
mdefine_line|#define __ASM_ARCH_REGS_GPIO_H &quot;$Id: gpio.h,v 1.5 2003/05/19 12:51:08 ben Exp $&quot;
multiline_comment|/* configure GPIO ports A..G */
DECL|macro|S3C2410_GPIOREG
mdefine_line|#define S3C2410_GPIOREG(x) ((x) + S3C2410_VA_GPIO)
multiline_comment|/* port A - 22bits, zero in bit X makes pin X output&n; * 1 makes port special function, this is default&n;*/
DECL|macro|S3C2410_GPACON
mdefine_line|#define S3C2410_GPACON&t;   S3C2410_GPIOREG(0x00)
DECL|macro|S3C2410_GPADAT
mdefine_line|#define S3C2410_GPADAT&t;   S3C2410_GPIOREG(0x04)
multiline_comment|/* 0x08 and 0x0c are reserved */
multiline_comment|/* GPB is 10 IO pins, each configured by 2 bits each in GPBCON.&n; *   00 = input, 01 = output, 10=special function, 11=reserved&n; * bit 0,1 = pin 0, 2,3= pin 1...&n; *&n; * CPBUP = pull up resistor control, 1=disabled, 0=enabled&n;*/
DECL|macro|S3C2410_GPBCON
mdefine_line|#define S3C2410_GPBCON&t;   S3C2410_GPIOREG(0x10)
DECL|macro|S3C2410_GPBDAT
mdefine_line|#define S3C2410_GPBDAT&t;   S3C2410_GPIOREG(0x14)
DECL|macro|S3C2410_GPBUP
mdefine_line|#define S3C2410_GPBUP&t;   S3C2410_GPIOREG(0x18)
multiline_comment|/* no i/o pin in port b can have value 3! */
DECL|macro|S3C2410_GPB0_INP
mdefine_line|#define S3C2410_GPB0_INP     (0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPB0_OUTP
mdefine_line|#define S3C2410_GPB0_OUTP    (0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPB0_TOUT0
mdefine_line|#define S3C2410_GPB0_TOUT0   (0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPB1_INP
mdefine_line|#define S3C2410_GPB1_INP     (0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPB1_OUTP
mdefine_line|#define S3C2410_GPB1_OUTP    (0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPB1_TOUT1
mdefine_line|#define S3C2410_GPB1_TOUT1   (0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPB2_INP
mdefine_line|#define S3C2410_GPB2_INP     (0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPB2_OUTP
mdefine_line|#define S3C2410_GPB2_OUTP    (0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPB2_TOUT2
mdefine_line|#define S3C2410_GPB2_TOUT2   (0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPB3_INP
mdefine_line|#define S3C2410_GPB3_INP     (0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPB3_OUTP
mdefine_line|#define S3C2410_GPB3_OUTP    (0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPB3_TOUT3
mdefine_line|#define S3C2410_GPB3_TOUT3   (0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPB4_INP
mdefine_line|#define S3C2410_GPB4_INP     (0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPB4_OUTP
mdefine_line|#define S3C2410_GPB4_OUTP    (0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPB4_TCLK0
mdefine_line|#define S3C2410_GPB4_TCLK0   (0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPB4_MASK
mdefine_line|#define S3C2410_GPB4_MASK    (0x03 &lt;&lt; 8)
DECL|macro|S3C2410_GPB5_INP
mdefine_line|#define S3C2410_GPB5_INP     (0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPB5_OUTP
mdefine_line|#define S3C2410_GPB5_OUTP    (0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPB5_nXBACK
mdefine_line|#define S3C2410_GPB5_nXBACK  (0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPB6_INP
mdefine_line|#define S3C2410_GPB6_INP     (0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPB6_OUTP
mdefine_line|#define S3C2410_GPB6_OUTP    (0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPB6_nXBREQ
mdefine_line|#define S3C2410_GPB6_nXBREQ  (0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPB7_INP
mdefine_line|#define S3C2410_GPB7_INP     (0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPB7_OUTP
mdefine_line|#define S3C2410_GPB7_OUTP    (0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPB7_nXDACK1
mdefine_line|#define S3C2410_GPB7_nXDACK1 (0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPB8_INP
mdefine_line|#define S3C2410_GPB8_INP     (0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPB8_OUTP
mdefine_line|#define S3C2410_GPB8_OUTP    (0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPB8_nXDREQ1
mdefine_line|#define S3C2410_GPB8_nXDREQ1 (0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPB9_INP
mdefine_line|#define S3C2410_GPB9_INP     (0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPB9_OUTP
mdefine_line|#define S3C2410_GPB9_OUTP    (0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPB9_nXDACK0
mdefine_line|#define S3C2410_GPB9_nXDACK0 (0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPB10_INP
mdefine_line|#define S3C2410_GPB10_INP     (0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPB10_OUTP
mdefine_line|#define S3C2410_GPB10_OUTP    (0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPB10_nXDRE0
mdefine_line|#define S3C2410_GPB10_nXDRE0 (0x02 &lt;&lt; 18)
multiline_comment|/* Port C consits of 16 GPIO/Special function&n; *&n; * almost identical setup to port b, but the special functions are mostly&n; * to do with the video system&squot;s sync/etc.&n;*/
DECL|macro|S3C2410_GPCCON
mdefine_line|#define S3C2410_GPCCON&t;   S3C2410_GPIOREG(0x20)
DECL|macro|S3C2410_GPCDAT
mdefine_line|#define S3C2410_GPCDAT&t;   S3C2410_GPIOREG(0x24)
DECL|macro|S3C2410_GPCUP
mdefine_line|#define S3C2410_GPCUP&t;   S3C2410_GPIOREG(0x28)
DECL|macro|S3C2410_GPC0_INP
mdefine_line|#define S3C2410_GPC0_INP&t;(0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPC0_OUTP
mdefine_line|#define S3C2410_GPC0_OUTP&t;(0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPC0_LEND
mdefine_line|#define S3C2410_GPC0_LEND&t;(0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPC1_INP
mdefine_line|#define S3C2410_GPC1_INP&t;(0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPC1_OUTP
mdefine_line|#define S3C2410_GPC1_OUTP&t;(0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPC1_VCLK
mdefine_line|#define S3C2410_GPC1_VCLK&t;(0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPC2_INP
mdefine_line|#define S3C2410_GPC2_INP&t;(0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPC2_OUTP
mdefine_line|#define S3C2410_GPC2_OUTP&t;(0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPC2_VLINE
mdefine_line|#define S3C2410_GPC2_VLINE&t;(0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPC3_INP
mdefine_line|#define S3C2410_GPC3_INP&t;(0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPC3_OUTP
mdefine_line|#define S3C2410_GPC3_OUTP&t;(0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPC3_VFRAME
mdefine_line|#define S3C2410_GPC3_VFRAME&t;(0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPC4_INP
mdefine_line|#define S3C2410_GPC4_INP&t;(0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPC4_OUTP
mdefine_line|#define S3C2410_GPC4_OUTP&t;(0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPC4_VM
mdefine_line|#define S3C2410_GPC4_VM&t;&t;(0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPC5_INP
mdefine_line|#define S3C2410_GPC5_INP&t;(0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPC5_OUTP
mdefine_line|#define S3C2410_GPC5_OUTP&t;(0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPC5_LCDVF0
mdefine_line|#define S3C2410_GPC5_LCDVF0&t;(0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPC6_INP
mdefine_line|#define S3C2410_GPC6_INP&t;(0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPC6_OUTP
mdefine_line|#define S3C2410_GPC6_OUTP&t;(0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPC6_LCDVF1
mdefine_line|#define S3C2410_GPC6_LCDVF1&t;(0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPC7_INP
mdefine_line|#define S3C2410_GPC7_INP&t;(0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPC7_OUTP
mdefine_line|#define S3C2410_GPC7_OUTP&t;(0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPC7_LCDVF2
mdefine_line|#define S3C2410_GPC7_LCDVF2&t;(0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPC8_INP
mdefine_line|#define S3C2410_GPC8_INP&t;(0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPC8_OUTP
mdefine_line|#define S3C2410_GPC8_OUTP&t;(0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPC8_VD0
mdefine_line|#define S3C2410_GPC8_VD0&t;(0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPC9_INP
mdefine_line|#define S3C2410_GPC9_INP&t;(0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPC9_OUTP
mdefine_line|#define S3C2410_GPC9_OUTP&t;(0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPC9_VD1
mdefine_line|#define S3C2410_GPC9_VD1&t;(0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPC10_INP
mdefine_line|#define S3C2410_GPC10_INP&t;(0x00 &lt;&lt; 20)
DECL|macro|S3C2410_GPC10_OUTP
mdefine_line|#define S3C2410_GPC10_OUTP&t;(0x01 &lt;&lt; 20)
DECL|macro|S3C2410_GPC10_VD2
mdefine_line|#define S3C2410_GPC10_VD2&t;(0x02 &lt;&lt; 20)
DECL|macro|S3C2410_GPC11_INP
mdefine_line|#define S3C2410_GPC11_INP&t;(0x00 &lt;&lt; 22)
DECL|macro|S3C2410_GPC11_OUTP
mdefine_line|#define S3C2410_GPC11_OUTP&t;(0x01 &lt;&lt; 22)
DECL|macro|S3C2410_GPC11_VD3
mdefine_line|#define S3C2410_GPC11_VD3&t;(0x02 &lt;&lt; 22)
DECL|macro|S3C2410_GPC12_INP
mdefine_line|#define S3C2410_GPC12_INP&t;(0x00 &lt;&lt; 24)
DECL|macro|S3C2410_GPC12_OUTP
mdefine_line|#define S3C2410_GPC12_OUTP&t;(0x01 &lt;&lt; 24)
DECL|macro|S3C2410_GPC12_VD4
mdefine_line|#define S3C2410_GPC12_VD4&t;(0x02 &lt;&lt; 24)
DECL|macro|S3C2410_GPC13_INP
mdefine_line|#define S3C2410_GPC13_INP&t;(0x00 &lt;&lt; 26)
DECL|macro|S3C2410_GPC13_OUTP
mdefine_line|#define S3C2410_GPC13_OUTP&t;(0x01 &lt;&lt; 26)
DECL|macro|S3C2410_GPC13_VD5
mdefine_line|#define S3C2410_GPC13_VD5&t;(0x02 &lt;&lt; 26)
DECL|macro|S3C2410_GPC14_INP
mdefine_line|#define S3C2410_GPC14_INP&t;(0x00 &lt;&lt; 28)
DECL|macro|S3C2410_GPC14_OUTP
mdefine_line|#define S3C2410_GPC14_OUTP&t;(0x01 &lt;&lt; 28)
DECL|macro|S3C2410_GPC14_VD6
mdefine_line|#define S3C2410_GPC14_VD6&t;(0x02 &lt;&lt; 28)
DECL|macro|S3C2410_GPC15_INP
mdefine_line|#define S3C2410_GPC15_INP&t;(0x00 &lt;&lt; 30)
DECL|macro|S3C2410_GPC15_OUTP
mdefine_line|#define S3C2410_GPC15_OUTP&t;(0x01 &lt;&lt; 30)
DECL|macro|S3C2410_GPC15_VD7
mdefine_line|#define S3C2410_GPC15_VD7&t;(0x02 &lt;&lt; 30)
multiline_comment|/* Port D consists of 16 GPIO/Special function&n; *&n; * almost identical setup to port b, but the special functions are mostly&n; * to do with the video system&squot;s data.&n;*/
DECL|macro|S3C2410_GPDCON
mdefine_line|#define S3C2410_GPDCON&t;   S3C2410_GPIOREG(0x30)
DECL|macro|S3C2410_GPDDAT
mdefine_line|#define S3C2410_GPDDAT&t;   S3C2410_GPIOREG(0x34)
DECL|macro|S3C2410_GPDUP
mdefine_line|#define S3C2410_GPDUP&t;   S3C2410_GPIOREG(0x38)
DECL|macro|S3C2410_GPD0_INP
mdefine_line|#define S3C2410_GPD0_INP&t;(0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPD0_OUTP
mdefine_line|#define S3C2410_GPD0_OUTP&t;(0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPD0_VD8
mdefine_line|#define S3C2410_GPD0_VD8&t;(0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPD1_INP
mdefine_line|#define S3C2410_GPD1_INP&t;(0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPD1_OUTP
mdefine_line|#define S3C2410_GPD1_OUTP&t;(0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPD1_VD9
mdefine_line|#define S3C2410_GPD1_VD9&t;(0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPD2_INP
mdefine_line|#define S3C2410_GPD2_INP&t;(0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPD2_OUTP
mdefine_line|#define S3C2410_GPD2_OUTP&t;(0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPD2_VD10
mdefine_line|#define S3C2410_GPD2_VD10&t;(0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPD3_INP
mdefine_line|#define S3C2410_GPD3_INP&t;(0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPD3_OUTP
mdefine_line|#define S3C2410_GPD3_OUTP&t;(0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPD3_VD11
mdefine_line|#define S3C2410_GPD3_VD11&t;(0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPD4_INP
mdefine_line|#define S3C2410_GPD4_INP&t;(0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPD4_OUTP
mdefine_line|#define S3C2410_GPD4_OUTP&t;(0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPD4_VD12
mdefine_line|#define S3C2410_GPD4_VD12&t;(0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPD5_INP
mdefine_line|#define S3C2410_GPD5_INP&t;(0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPD5_OUTP
mdefine_line|#define S3C2410_GPD5_OUTP&t;(0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPD5_VD13
mdefine_line|#define S3C2410_GPD5_VD13&t;(0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPD6_INP
mdefine_line|#define S3C2410_GPD6_INP&t;(0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPD6_OUTP
mdefine_line|#define S3C2410_GPD6_OUTP&t;(0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPD6_VD14
mdefine_line|#define S3C2410_GPD6_VD14&t;(0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPD7_INP
mdefine_line|#define S3C2410_GPD7_INP&t;(0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPD7_OUTP
mdefine_line|#define S3C2410_GPD7_OUTP&t;(0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPD7_VD15
mdefine_line|#define S3C2410_GPD7_VD15&t;(0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPD8_INP
mdefine_line|#define S3C2410_GPD8_INP&t;(0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPD8_OUTP
mdefine_line|#define S3C2410_GPD8_OUTP&t;(0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPD8_VD16
mdefine_line|#define S3C2410_GPD8_VD16&t;(0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPD9_INP
mdefine_line|#define S3C2410_GPD9_INP&t;(0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPD9_OUTP
mdefine_line|#define S3C2410_GPD9_OUTP&t;(0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPD9_VD17
mdefine_line|#define S3C2410_GPD9_VD17&t;(0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPD10_INP
mdefine_line|#define S3C2410_GPD10_INP&t;(0x00 &lt;&lt; 20)
DECL|macro|S3C2410_GPD10_OUTP
mdefine_line|#define S3C2410_GPD10_OUTP&t;(0x01 &lt;&lt; 20)
DECL|macro|S3C2410_GPD10_VD18
mdefine_line|#define S3C2410_GPD10_VD18&t;(0x02 &lt;&lt; 20)
DECL|macro|S3C2410_GPD11_INP
mdefine_line|#define S3C2410_GPD11_INP&t;(0x00 &lt;&lt; 22)
DECL|macro|S3C2410_GPD11_OUTP
mdefine_line|#define S3C2410_GPD11_OUTP&t;(0x01 &lt;&lt; 22)
DECL|macro|S3C2410_GPD11_VD19
mdefine_line|#define S3C2410_GPD11_VD19&t;(0x02 &lt;&lt; 22)
DECL|macro|S3C2410_GPD12_INP
mdefine_line|#define S3C2410_GPD12_INP&t;(0x00 &lt;&lt; 24)
DECL|macro|S3C2410_GPD12_OUTP
mdefine_line|#define S3C2410_GPD12_OUTP&t;(0x01 &lt;&lt; 24)
DECL|macro|S3C2410_GPD12_VD20
mdefine_line|#define S3C2410_GPD12_VD20&t;(0x02 &lt;&lt; 24)
DECL|macro|S3C2410_GPD13_INP
mdefine_line|#define S3C2410_GPD13_INP&t;(0x00 &lt;&lt; 26)
DECL|macro|S3C2410_GPD13_OUTP
mdefine_line|#define S3C2410_GPD13_OUTP&t;(0x01 &lt;&lt; 26)
DECL|macro|S3C2410_GPD13_VD21
mdefine_line|#define S3C2410_GPD13_VD21&t;(0x02 &lt;&lt; 26)
DECL|macro|S3C2410_GPD14_INP
mdefine_line|#define S3C2410_GPD14_INP&t;(0x00 &lt;&lt; 28)
DECL|macro|S3C2410_GPD14_OUTP
mdefine_line|#define S3C2410_GPD14_OUTP&t;(0x01 &lt;&lt; 28)
DECL|macro|S3C2410_GPD14_VD22
mdefine_line|#define S3C2410_GPD14_VD22&t;(0x02 &lt;&lt; 28)
DECL|macro|S3C2410_GPD15_INP
mdefine_line|#define S3C2410_GPD15_INP&t;(0x00 &lt;&lt; 30)
DECL|macro|S3C2410_GPD15_OUTP
mdefine_line|#define S3C2410_GPD15_OUTP&t;(0x01 &lt;&lt; 30)
DECL|macro|S3C2410_GPD15_VD23
mdefine_line|#define S3C2410_GPD15_VD23&t;(0x02 &lt;&lt; 30)
multiline_comment|/* Port E consists of 16 GPIO/Special function&n; *&n; * again, the same as port B, but dealing with I2S, SDI, and&n; * more miscellaneous functions&n;*/
DECL|macro|S3C2410_GPECON
mdefine_line|#define S3C2410_GPECON&t;   S3C2410_GPIOREG(0x40)
DECL|macro|S3C2410_GPEDAT
mdefine_line|#define S3C2410_GPEDAT&t;   S3C2410_GPIOREG(0x44)
DECL|macro|S3C2410_GPEUP
mdefine_line|#define S3C2410_GPEUP&t;   S3C2410_GPIOREG(0x48)
DECL|macro|S3C2410_GPE0_INP
mdefine_line|#define S3C2410_GPE0_INP       (0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPE0_OUTP
mdefine_line|#define S3C2410_GPE0_OUTP      (0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPE0_I2SLRCK
mdefine_line|#define S3C2410_GPE0_I2SLRCK   (0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPE0_MASK
mdefine_line|#define S3C2410_GPE0_MASK      (0x03 &lt;&lt; 0)
DECL|macro|S3C2410_GPE1_INP
mdefine_line|#define S3C2410_GPE1_INP       (0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPE1_OUTP
mdefine_line|#define S3C2410_GPE1_OUTP      (0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPE1_I2SSCLK
mdefine_line|#define S3C2410_GPE1_I2SSCLK   (0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPE1_MASK
mdefine_line|#define S3C2410_GPE1_MASK      (0x03 &lt;&lt; 2)
DECL|macro|S3C2410_GPE2_INP
mdefine_line|#define S3C2410_GPE2_INP       (0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPE2_OUTP
mdefine_line|#define S3C2410_GPE2_OUTP      (0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPE2_CDCLK
mdefine_line|#define S3C2410_GPE2_CDCLK     (0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPE3_INP
mdefine_line|#define S3C2410_GPE3_INP       (0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPE3_OUTP
mdefine_line|#define S3C2410_GPE3_OUTP      (0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPE3_I2SSDI
mdefine_line|#define S3C2410_GPE3_I2SSDI    (0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPE3_MASK
mdefine_line|#define S3C2410_GPE3_MASK      (0x03 &lt;&lt; 6)
DECL|macro|S3C2410_GPE4_INP
mdefine_line|#define S3C2410_GPE4_INP       (0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPE4_OUTP
mdefine_line|#define S3C2410_GPE4_OUTP      (0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPE4_I2SSDO
mdefine_line|#define S3C2410_GPE4_I2SSDO    (0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPE4_MASK
mdefine_line|#define S3C2410_GPE4_MASK      (0x03 &lt;&lt; 8)
DECL|macro|S3C2410_GPE5_INP
mdefine_line|#define S3C2410_GPE5_INP       (0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPE5_OUTP
mdefine_line|#define S3C2410_GPE5_OUTP      (0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPE5_SDCLK
mdefine_line|#define S3C2410_GPE5_SDCLK     (0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPE6_INP
mdefine_line|#define S3C2410_GPE6_INP       (0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPE6_OUTP
mdefine_line|#define S3C2410_GPE6_OUTP      (0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPE6_SDCLK
mdefine_line|#define S3C2410_GPE6_SDCLK     (0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPE7_INP
mdefine_line|#define S3C2410_GPE7_INP       (0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPE7_OUTP
mdefine_line|#define S3C2410_GPE7_OUTP      (0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPE7_SDCMD
mdefine_line|#define S3C2410_GPE7_SDCMD     (0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPE8_INP
mdefine_line|#define S3C2410_GPE8_INP       (0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPE8_OUTP
mdefine_line|#define S3C2410_GPE8_OUTP      (0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPE8_SDDAT1
mdefine_line|#define S3C2410_GPE8_SDDAT1    (0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPE9_INP
mdefine_line|#define S3C2410_GPE9_INP       (0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPE9_OUTP
mdefine_line|#define S3C2410_GPE9_OUTP      (0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPE9_SDDAT2
mdefine_line|#define S3C2410_GPE9_SDDAT2    (0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPE10_INP
mdefine_line|#define S3C2410_GPE10_INP      (0x00 &lt;&lt; 20)
DECL|macro|S3C2410_GPE10_OUTP
mdefine_line|#define S3C2410_GPE10_OUTP     (0x01 &lt;&lt; 20)
DECL|macro|S3C2410_GPE10_SDDAT3
mdefine_line|#define S3C2410_GPE10_SDDAT3   (0x02 &lt;&lt; 20)
DECL|macro|S3C2410_GPE11_INP
mdefine_line|#define S3C2410_GPE11_INP      (0x00 &lt;&lt; 22)
DECL|macro|S3C2410_GPE11_OUTP
mdefine_line|#define S3C2410_GPE11_OUTP     (0x01 &lt;&lt; 22)
DECL|macro|S3C2410_GPE11_SPIMISO0
mdefine_line|#define S3C2410_GPE11_SPIMISO0 (0x02 &lt;&lt; 22)
DECL|macro|S3C2410_GPE12_INP
mdefine_line|#define S3C2410_GPE12_INP      (0x00 &lt;&lt; 24)
DECL|macro|S3C2410_GPE12_OUTP
mdefine_line|#define S3C2410_GPE12_OUTP     (0x01 &lt;&lt; 24)
DECL|macro|S3C2410_GPE12_SPIMOSI0
mdefine_line|#define S3C2410_GPE12_SPIMOSI0 (0x02 &lt;&lt; 24)
DECL|macro|S3C2410_GPE13_INP
mdefine_line|#define S3C2410_GPE13_INP      (0x00 &lt;&lt; 26)
DECL|macro|S3C2410_GPE13_OUTP
mdefine_line|#define S3C2410_GPE13_OUTP     (0x01 &lt;&lt; 26)
DECL|macro|S3C2410_GPE13_SPICLK0
mdefine_line|#define S3C2410_GPE13_SPICLK0  (0x02 &lt;&lt; 26)
DECL|macro|S3C2410_GPE14_INP
mdefine_line|#define S3C2410_GPE14_INP      (0x00 &lt;&lt; 28)
DECL|macro|S3C2410_GPE14_OUTP
mdefine_line|#define S3C2410_GPE14_OUTP     (0x01 &lt;&lt; 28)
DECL|macro|S3C2410_GPE14_IICSCL
mdefine_line|#define S3C2410_GPE14_IICSCL   (0x02 &lt;&lt; 28)
DECL|macro|S3C2410_GPE14_MASK
mdefine_line|#define S3C2410_GPE14_MASK     (0x03 &lt;&lt; 28)
DECL|macro|S3C2410_GPE15_INP
mdefine_line|#define S3C2410_GPE15_INP      (0x00 &lt;&lt; 30)
DECL|macro|S3C2410_GPE15_OUTP
mdefine_line|#define S3C2410_GPE15_OUTP     (0x01 &lt;&lt; 30)
DECL|macro|S3C2410_GPE15_IICSDA
mdefine_line|#define S3C2410_GPE15_IICSDA   (0x02 &lt;&lt; 30)
DECL|macro|S3C2410_GPE15_MASK
mdefine_line|#define S3C2410_GPE15_MASK     (0x03 &lt;&lt; 30)
DECL|macro|S3C2410_GPE_PUPDIS
mdefine_line|#define S3C2410_GPE_PUPDIS(x)  (1&lt;&lt;(x))
multiline_comment|/* Port F consists of 8 GPIO/Special function&n; *&n; * GPIO / interrupt inputs&n; *&n; * GPFCON has 2 bits for each of the input pins on port F&n; *   00 = 0 input, 1 output, 2 interrupt (EINT0..7), 3 undefined&n; *&n; * pull up works like all other ports.&n;*/
DECL|macro|S3C2410_GPFCON
mdefine_line|#define S3C2410_GPFCON&t;   S3C2410_GPIOREG(0x50)
DECL|macro|S3C2410_GPFDAT
mdefine_line|#define S3C2410_GPFDAT&t;   S3C2410_GPIOREG(0x54)
DECL|macro|S3C2410_GPFUP
mdefine_line|#define S3C2410_GPFUP&t;   S3C2410_GPIOREG(0x58)
DECL|macro|S3C2410_GPF0_INP
mdefine_line|#define S3C2410_GPF0_INP    (0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPF0_OUTP
mdefine_line|#define S3C2410_GPF0_OUTP   (0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPF0_EINT0
mdefine_line|#define S3C2410_GPF0_EINT0  (0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPF1_INP
mdefine_line|#define S3C2410_GPF1_INP    (0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPF1_OUTP
mdefine_line|#define S3C2410_GPF1_OUTP   (0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPF1_EINT1
mdefine_line|#define S3C2410_GPF1_EINT1  (0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPF2_INP
mdefine_line|#define S3C2410_GPF2_INP    (0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPF2_OUTP
mdefine_line|#define S3C2410_GPF2_OUTP   (0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPF2_EINT2
mdefine_line|#define S3C2410_GPF2_EINT2  (0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPF3_INP
mdefine_line|#define S3C2410_GPF3_INP    (0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPF3_OUTP
mdefine_line|#define S3C2410_GPF3_OUTP   (0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPF3_EINT3
mdefine_line|#define S3C2410_GPF3_EINT3  (0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPF4_INP
mdefine_line|#define S3C2410_GPF4_INP    (0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPF4_OUTP
mdefine_line|#define S3C2410_GPF4_OUTP   (0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPF4_EINT4
mdefine_line|#define S3C2410_GPF4_EINT4  (0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPF5_INP
mdefine_line|#define S3C2410_GPF5_INP    (0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPF5_OUTP
mdefine_line|#define S3C2410_GPF5_OUTP   (0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPF5_EINT5
mdefine_line|#define S3C2410_GPF5_EINT5  (0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPF6_INP
mdefine_line|#define S3C2410_GPF6_INP    (0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPF6_OUTP
mdefine_line|#define S3C2410_GPF6_OUTP   (0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPF6_EINT6
mdefine_line|#define S3C2410_GPF6_EINT6  (0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPF7_INP
mdefine_line|#define S3C2410_GPF7_INP    (0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPF7_OUTP
mdefine_line|#define S3C2410_GPF7_OUTP   (0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPF7_EINT7
mdefine_line|#define S3C2410_GPF7_EINT7  (0x02 &lt;&lt; 14)
multiline_comment|/* Port G consists of 8 GPIO/IRQ/Special function&n; *&n; * GPGCON has 2 bits for each of the input pins on port F&n; *   00 = 0 input, 1 output, 2 interrupt (EINT0..7), 3 special func&n; *&n; * pull up works like all other ports.&n;*/
DECL|macro|S3C2410_GPGCON
mdefine_line|#define S3C2410_GPGCON&t;   S3C2410_GPIOREG(0x60)
DECL|macro|S3C2410_GPGDAT
mdefine_line|#define S3C2410_GPGDAT&t;   S3C2410_GPIOREG(0x64)
DECL|macro|S3C2410_GPGUP
mdefine_line|#define S3C2410_GPGUP&t;   S3C2410_GPIOREG(0x68)
DECL|macro|S3C2410_GPG0_INP
mdefine_line|#define S3C2410_GPG0_INP      (0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPG0_OUTP
mdefine_line|#define S3C2410_GPG0_OUTP     (0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPG0_EINT8
mdefine_line|#define S3C2410_GPG0_EINT8    (0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPG1_INP
mdefine_line|#define S3C2410_GPG1_INP      (0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPG1_OUTP
mdefine_line|#define S3C2410_GPG1_OUTP     (0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPG1_EINT9
mdefine_line|#define S3C2410_GPG1_EINT9    (0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPG2_INP
mdefine_line|#define S3C2410_GPG2_INP      (0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPG2_OUTP
mdefine_line|#define S3C2410_GPG2_OUTP     (0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPG2_EINT10
mdefine_line|#define S3C2410_GPG2_EINT10   (0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPG3_INP
mdefine_line|#define S3C2410_GPG3_INP      (0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPG3_OUTP
mdefine_line|#define S3C2410_GPG3_OUTP     (0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPG3_EINT11
mdefine_line|#define S3C2410_GPG3_EINT11   (0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPG4_INP
mdefine_line|#define S3C2410_GPG4_INP      (0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPG4_OUTP
mdefine_line|#define S3C2410_GPG4_OUTP     (0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPG4_EINT12
mdefine_line|#define S3C2410_GPG4_EINT12   (0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPG4_LCDPWREN
mdefine_line|#define S3C2410_GPG4_LCDPWREN (0x03 &lt;&lt; 8)
DECL|macro|S3C2410_GPG5_INP
mdefine_line|#define S3C2410_GPG5_INP      (0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPG5_OUTP
mdefine_line|#define S3C2410_GPG5_OUTP     (0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPG5_EINT13
mdefine_line|#define S3C2410_GPG5_EINT13   (0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPG5_SPIMISO1
mdefine_line|#define S3C2410_GPG5_SPIMISO1 (0x03 &lt;&lt; 10)
DECL|macro|S3C2410_GPG6_INP
mdefine_line|#define S3C2410_GPG6_INP      (0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPG6_OUTP
mdefine_line|#define S3C2410_GPG6_OUTP     (0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPG6_EINT14
mdefine_line|#define S3C2410_GPG6_EINT14   (0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPG6_SPIMOSI1
mdefine_line|#define S3C2410_GPG6_SPIMOSI1 (0x03 &lt;&lt; 12)
DECL|macro|S3C2410_GPG7_INP
mdefine_line|#define S3C2410_GPG7_INP      (0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPG7_OUTP
mdefine_line|#define S3C2410_GPG7_OUTP     (0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPG7_EINT15
mdefine_line|#define S3C2410_GPG7_EINT15   (0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPG7_SPICLK1
mdefine_line|#define S3C2410_GPG7_SPICLK1  (0x03 &lt;&lt; 14)
DECL|macro|S3C2410_GPG8_INP
mdefine_line|#define S3C2410_GPG8_INP      (0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPG8_OUTP
mdefine_line|#define S3C2410_GPG8_OUTP     (0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPG8_EINT16
mdefine_line|#define S3C2410_GPG8_EINT16   (0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPG9_INP
mdefine_line|#define S3C2410_GPG9_INP      (0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPG9_OUTP
mdefine_line|#define S3C2410_GPG9_OUTP     (0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPG9_EINT17
mdefine_line|#define S3C2410_GPG9_EINT17   (0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPG10_INP
mdefine_line|#define S3C2410_GPG10_INP     (0x00 &lt;&lt; 20)
DECL|macro|S3C2410_GPG10_OUTP
mdefine_line|#define S3C2410_GPG10_OUTP    (0x01 &lt;&lt; 20)
DECL|macro|S3C2410_GPG10_EINT18
mdefine_line|#define S3C2410_GPG10_EINT18  (0x02 &lt;&lt; 20)
DECL|macro|S3C2410_GPG11_INP
mdefine_line|#define S3C2410_GPG11_INP     (0x00 &lt;&lt; 22)
DECL|macro|S3C2410_GPG11_OUTP
mdefine_line|#define S3C2410_GPG11_OUTP    (0x01 &lt;&lt; 22)
DECL|macro|S3C2410_GPG11_EINT19
mdefine_line|#define S3C2410_GPG11_EINT19  (0x02 &lt;&lt; 22)
DECL|macro|S3C2410_GPG11_TCLK1
mdefine_line|#define S3C2410_GPG11_TCLK1   (0x03 &lt;&lt; 22)
DECL|macro|S3C2410_GPG12_INP
mdefine_line|#define S3C2410_GPG12_INP     (0x00 &lt;&lt; 24)
DECL|macro|S3C2410_GPG12_OUTP
mdefine_line|#define S3C2410_GPG12_OUTP    (0x01 &lt;&lt; 24)
DECL|macro|S3C2410_GPG12_EINT18
mdefine_line|#define S3C2410_GPG12_EINT18  (0x02 &lt;&lt; 24)
DECL|macro|S3C2410_GPG12_XMON
mdefine_line|#define S3C2410_GPG12_XMON    (0x03 &lt;&lt; 24)
DECL|macro|S3C2410_GPG13_INP
mdefine_line|#define S3C2410_GPG13_INP     (0x00 &lt;&lt; 26)
DECL|macro|S3C2410_GPG13_OUTP
mdefine_line|#define S3C2410_GPG13_OUTP    (0x01 &lt;&lt; 26)
DECL|macro|S3C2410_GPG13_EINT18
mdefine_line|#define S3C2410_GPG13_EINT18  (0x02 &lt;&lt; 26)
DECL|macro|S3C2410_GPG13_nXPON
mdefine_line|#define S3C2410_GPG13_nXPON   (0x03 &lt;&lt; 26)
DECL|macro|S3C2410_GPG14_INP
mdefine_line|#define S3C2410_GPG14_INP     (0x00 &lt;&lt; 28)
DECL|macro|S3C2410_GPG14_OUTP
mdefine_line|#define S3C2410_GPG14_OUTP    (0x01 &lt;&lt; 28)
DECL|macro|S3C2410_GPG14_EINT18
mdefine_line|#define S3C2410_GPG14_EINT18  (0x02 &lt;&lt; 28)
DECL|macro|S3C2410_GPG14_YMON
mdefine_line|#define S3C2410_GPG14_YMON    (0x03 &lt;&lt; 28)
DECL|macro|S3C2410_GPG15_INP
mdefine_line|#define S3C2410_GPG15_INP     (0x00 &lt;&lt; 30)
DECL|macro|S3C2410_GPG15_OUTP
mdefine_line|#define S3C2410_GPG15_OUTP    (0x01 &lt;&lt; 30)
DECL|macro|S3C2410_GPG15_EINT18
mdefine_line|#define S3C2410_GPG15_EINT18  (0x02 &lt;&lt; 30)
DECL|macro|S3C2410_GPG15_nYPON
mdefine_line|#define S3C2410_GPG15_nYPON   (0x03 &lt;&lt; 30)
DECL|macro|S3C2410_GPG_PUPDIS
mdefine_line|#define S3C2410_GPG_PUPDIS(x)  (1&lt;&lt;(x))
multiline_comment|/* Port H consists of11 GPIO/serial/Misc pins&n; *&n; * GPGCON has 2 bits for each of the input pins on port F&n; *   00 = 0 input, 1 output, 2 interrupt (EINT0..7), 3 special func&n; *&n; * pull up works like all other ports.&n;*/
DECL|macro|S3C2410_GPHCON
mdefine_line|#define S3C2410_GPHCON&t;   S3C2410_GPIOREG(0x70)
DECL|macro|S3C2410_GPHDAT
mdefine_line|#define S3C2410_GPHDAT&t;   S3C2410_GPIOREG(0x74)
DECL|macro|S3C2410_GPHUP
mdefine_line|#define S3C2410_GPHUP&t;   S3C2410_GPIOREG(0x78)
DECL|macro|S3C2410_GPH0_INP
mdefine_line|#define S3C2410_GPH0_INP    (0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPH0_OUTP
mdefine_line|#define S3C2410_GPH0_OUTP   (0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPH0_nCTS0
mdefine_line|#define S3C2410_GPH0_nCTS0  (0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPH1_INP
mdefine_line|#define S3C2410_GPH1_INP    (0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPH1_OUTP
mdefine_line|#define S3C2410_GPH1_OUTP   (0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPH1_nRTS0
mdefine_line|#define S3C2410_GPH1_nRTS0  (0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPH2_INP
mdefine_line|#define S3C2410_GPH2_INP    (0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPH2_OUTP
mdefine_line|#define S3C2410_GPH2_OUTP   (0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPH2_TXD0
mdefine_line|#define S3C2410_GPH2_TXD0   (0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPH3_INP
mdefine_line|#define S3C2410_GPH3_INP    (0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPH3_OUTP
mdefine_line|#define S3C2410_GPH3_OUTP   (0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPH3_RXD0
mdefine_line|#define S3C2410_GPH3_RXD0   (0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPH4_INP
mdefine_line|#define S3C2410_GPH4_INP    (0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPH4_OUTP
mdefine_line|#define S3C2410_GPH4_OUTP   (0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPH4_TXD1
mdefine_line|#define S3C2410_GPH4_TXD1   (0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPH5_INP
mdefine_line|#define S3C2410_GPH5_INP    (0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPH5_OUTP
mdefine_line|#define S3C2410_GPH5_OUTP   (0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPH5_RXD1
mdefine_line|#define S3C2410_GPH5_RXD1   (0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPH6_INP
mdefine_line|#define S3C2410_GPH6_INP    (0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPH6_OUTP
mdefine_line|#define S3C2410_GPH6_OUTP   (0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPH6_TXD2
mdefine_line|#define S3C2410_GPH6_TXD2   (0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPH6_nRTS1
mdefine_line|#define S3C2410_GPH6_nRTS1  (0x03 &lt;&lt; 12)
DECL|macro|S3C2410_GPH7_INP
mdefine_line|#define S3C2410_GPH7_INP    (0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPH7_OUTP
mdefine_line|#define S3C2410_GPH7_OUTP   (0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPH7_RXD2
mdefine_line|#define S3C2410_GPH7_RXD2   (0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPH7_nCTS1
mdefine_line|#define S3C2410_GPH7_nCTS1  (0x03 &lt;&lt; 14)
DECL|macro|S3C2410_GPH8_INP
mdefine_line|#define S3C2410_GPH8_INP    (0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPH8_OUTP
mdefine_line|#define S3C2410_GPH8_OUTP   (0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPH8_UCLK
mdefine_line|#define S3C2410_GPH8_UCLK   (0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPH9_INP
mdefine_line|#define S3C2410_GPH9_INP     (0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPH9_OUTP
mdefine_line|#define S3C2410_GPH9_OUTP    (0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPH9_CLKOUT0
mdefine_line|#define S3C2410_GPH9_CLKOUT0 (0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPH10_INP
mdefine_line|#define S3C2410_GPH10_INP   (0x00 &lt;&lt; 20)
DECL|macro|S3C2410_GPH10_OUTP
mdefine_line|#define S3C2410_GPH10_OUTP  (0x01 &lt;&lt; 20)
DECL|macro|S3C2410_GPH10_CLKOUT1
mdefine_line|#define S3C2410_GPH10_CLKOUT1  (0x02 &lt;&lt; 20)
multiline_comment|/* miscellaneous control */
DECL|macro|S3C2410_MISCCR
mdefine_line|#define S3C2410_MISCCR&t;   S3C2410_GPIOREG(0x80)
DECL|macro|S3C2410_DCLKCON
mdefine_line|#define S3C2410_DCLKCON&t;   S3C2410_GPIOREG(0x84)
multiline_comment|/* see clock.h for dclk definitions */
multiline_comment|/* pullup control on databus */
DECL|macro|S3C2410_MISCCR_SPUCR_HEN
mdefine_line|#define S3C2410_MISCCR_SPUCR_HEN    (0)
DECL|macro|S3C2410_MISCCR_SPUCR_HDIS
mdefine_line|#define S3C2410_MISCCR_SPUCR_HDIS   (1&lt;&lt;0)
DECL|macro|S3C2410_MISCCR_SPUCR_LEN
mdefine_line|#define S3C2410_MISCCR_SPUCR_LEN    (0)
DECL|macro|S3C2410_MISCCR_SPUCR_LDIS
mdefine_line|#define S3C2410_MISCCR_SPUCR_LDIS   (1&lt;&lt;1)
DECL|macro|S3C2410_MISCCR_USBDEV
mdefine_line|#define S3C2410_MISCCR_USBDEV&t;    (0)
DECL|macro|S3C2410_MISCCR_USBHOST
mdefine_line|#define S3C2410_MISCCR_USBHOST&t;    (1&lt;&lt;3)
DECL|macro|S3C2410_MISCCR_CLK0_MPLL
mdefine_line|#define S3C2410_MISCCR_CLK0_MPLL    (0&lt;&lt;4)
DECL|macro|S3C2410_MISCCR_CLK0_UPLL
mdefine_line|#define S3C2410_MISCCR_CLK0_UPLL    (1&lt;&lt;4)
DECL|macro|S3C2410_MISCCR_CLK0_FCLK
mdefine_line|#define S3C2410_MISCCR_CLK0_FCLK    (2&lt;&lt;4)
DECL|macro|S3C2410_MISCCR_CLK0_HCLK
mdefine_line|#define S3C2410_MISCCR_CLK0_HCLK    (3&lt;&lt;4)
DECL|macro|S3C2410_MISCCR_CLK0_PCLK
mdefine_line|#define S3C2410_MISCCR_CLK0_PCLK    (4&lt;&lt;4)
DECL|macro|S3C2410_MISCCR_CLK0_DCLK0
mdefine_line|#define S3C2410_MISCCR_CLK0_DCLK0   (5&lt;&lt;4)
DECL|macro|S3C2410_MISCCR_CLK1_MPLL
mdefine_line|#define S3C2410_MISCCR_CLK1_MPLL    (0&lt;&lt;8)
DECL|macro|S3C2410_MISCCR_CLK1_UPLL
mdefine_line|#define S3C2410_MISCCR_CLK1_UPLL    (1&lt;&lt;8)
DECL|macro|S3C2410_MISCCR_CLK1_FCLK
mdefine_line|#define S3C2410_MISCCR_CLK1_FCLK    (2&lt;&lt;8)
DECL|macro|S3C2410_MISCCR_CLK1_HCLK
mdefine_line|#define S3C2410_MISCCR_CLK1_HCLK    (3&lt;&lt;8)
DECL|macro|S3C2410_MISCCR_CLK1_PCLK
mdefine_line|#define S3C2410_MISCCR_CLK1_PCLK    (4&lt;&lt;8)
DECL|macro|S3C2410_MISCCR_CLK1_DCLK1
mdefine_line|#define S3C2410_MISCCR_CLK1_DCLK1   (5&lt;&lt;8)
DECL|macro|S3C2410_MISCCR_USBSUSPND0
mdefine_line|#define S3C2410_MISCCR_USBSUSPND0   (1&lt;&lt;12)
DECL|macro|S3C2410_MISCCR_USBSUSPND1
mdefine_line|#define S3C2410_MISCCR_USBSUSPND1   (1&lt;&lt;13)
DECL|macro|S3C2410_MISCCR_nRSTCON
mdefine_line|#define S3C2410_MISCCR_nRSTCON&t;    (1&lt;&lt;16)
multiline_comment|/* external interrupt control... */
multiline_comment|/* S3C2410_EXTINT0 -&gt; irq sense control for EINT0..EINT7&n; * S3C2410_EXTINT1 -&gt; irq sense control for EINT8..EINT15&n; * S3C2410_EXTINT2 -&gt; irq sense control for EINT16..EINT23&n; *&n; * note S3C2410_EXTINT2 has filtering options for EINT16..EINT23&n; *&n; * Samsung datasheet p9-25&n;*/
DECL|macro|S3C2410_EXTINT0
mdefine_line|#define S3C2410_EXTINT0&t;   S3C2410_GPIOREG(0x88)
DECL|macro|S3C2410_EXTINT1
mdefine_line|#define S3C2410_EXTINT1&t;   S3C2410_GPIOREG(0x8C)
DECL|macro|S3C2410_EXTINT2
mdefine_line|#define S3C2410_EXTINT2&t;   S3C2410_GPIOREG(0x90)
multiline_comment|/* values for S3C2410_EXTINT0/1/2 */
DECL|macro|S3C2410_EXTINT_LOWLEV
mdefine_line|#define S3C2410_EXTINT_LOWLEV&t; (0x00)
DECL|macro|S3C2410_EXTINT_HILEV
mdefine_line|#define S3C2410_EXTINT_HILEV&t; (0x01)
DECL|macro|S3C2410_EXTINT_FALLEDGE
mdefine_line|#define S3C2410_EXTINT_FALLEDGE&t; (0x02)
DECL|macro|S3C2410_EXTINT_RISEEDGE
mdefine_line|#define S3C2410_EXTINT_RISEEDGE&t; (0x04)
DECL|macro|S3C2410_EXTINT_BOTHEDGE
mdefine_line|#define S3C2410_EXTINT_BOTHEDGE&t; (0x06)
multiline_comment|/* interrupt filtering conrrol for EINT16..EINT23 */
DECL|macro|S3C2410_EINFLT0
mdefine_line|#define S3C2410_EINFLT0&t;   S3C2410_GPIOREG(0x94)
DECL|macro|S3C2410_EINFLT1
mdefine_line|#define S3C2410_EINFLT1&t;   S3C2410_GPIOREG(0x98)
DECL|macro|S3C2410_EINFLT2
mdefine_line|#define S3C2410_EINFLT2&t;   S3C2410_GPIOREG(0x9C)
DECL|macro|S3C2410_EINFLT3
mdefine_line|#define S3C2410_EINFLT3&t;   S3C2410_GPIOREG(0xA0)
multiline_comment|/* removed EINTxxxx defs from here, not meant for this */
multiline_comment|/* GSTATUS have miscellaneous information in them&n; *&n; */
DECL|macro|S3C2410_GSTATUS0
mdefine_line|#define S3C2410_GSTATUS0   S3C2410_GPIOREG(0x0AC)
DECL|macro|S3C2410_GSTATUS1
mdefine_line|#define S3C2410_GSTATUS1   S3C2410_GPIOREG(0x0B0)
DECL|macro|S3C2410_GSTATUS2
mdefine_line|#define S3C2410_GSTATUS2   S3C2410_GPIOREG(0x0B4)
DECL|macro|S3C2410_GSTATUS3
mdefine_line|#define S3C2410_GSTATUS3   S3C2410_GPIOREG(0x0B8)
DECL|macro|S3C2410_GSTATUS4
mdefine_line|#define S3C2410_GSTATUS4   S3C2410_GPIOREG(0x0BC)
DECL|macro|S3C2410_GSTATUS0_nWAIT
mdefine_line|#define S3C2410_GSTATUS0_nWAIT&t;   (1&lt;&lt;3)
DECL|macro|S3C2410_GSTATUS0_NCON
mdefine_line|#define S3C2410_GSTATUS0_NCON&t;   (1&lt;&lt;2)
DECL|macro|S3C2410_GSTATUS0_RnB
mdefine_line|#define S3C2410_GSTATUS0_RnB&t;   (1&lt;&lt;1)
DECL|macro|S3C2410_GSTATUS0_nBATTFLT
mdefine_line|#define S3C2410_GSTATUS0_nBATTFLT  (1&lt;&lt;0)
DECL|macro|S3C2410_GSTATUS2_WTRESET
mdefine_line|#define S3C2410_GSTATUS2_WTRESET   (1&lt;&lt;2)
DECL|macro|S3C2410_GSTATUs2_OFFRESET
mdefine_line|#define S3C2410_GSTATUs2_OFFRESET  (1&lt;&lt;1)
DECL|macro|S3C2410_GSTATUS2_PONRESET
mdefine_line|#define S3C2410_GSTATUS2_PONRESET  (1&lt;&lt;0)
macro_line|#endif&t;/* __ASM_ARCH_REGS_GPIO_H */
eof
