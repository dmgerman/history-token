multiline_comment|/* linux/include/asm/hardware/s3c2410/regs-gpio.h&n; *&n; * Copyright (c) 2003,2004 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;           http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 GPIO register definitions&n; *&n; *  Changelog:&n; *    19-06-2003     BJD     Created file&n; *    23-06-2003     BJD     Updated GSTATUS registers&n; *    12-03-2004     BJD     Updated include protection&n; *    20-07-2004     BJD     Added GPIO pin numbers, added Port A definitions&n; *    04-10-2004     BJD     Fixed number of bugs, added EXT IRQ filter defs&n; *    17-10-2004     BJD     Added GSTATUS1 register definitions&n;*/
macro_line|#ifndef __ASM_ARCH_REGS_GPIO_H
DECL|macro|__ASM_ARCH_REGS_GPIO_H
mdefine_line|#define __ASM_ARCH_REGS_GPIO_H &quot;$Id: gpio.h,v 1.5 2003/05/19 12:51:08 ben Exp $&quot;
DECL|macro|S3C2410_GPIONO
mdefine_line|#define S3C2410_GPIONO(bank,offset) ((bank) + (offset))
DECL|macro|S3C2410_GPIO_BANKA
mdefine_line|#define S3C2410_GPIO_BANKA   (32*0)
DECL|macro|S3C2410_GPIO_BANKB
mdefine_line|#define S3C2410_GPIO_BANKB   (32*1)
DECL|macro|S3C2410_GPIO_BANKC
mdefine_line|#define S3C2410_GPIO_BANKC   (32*2)
DECL|macro|S3C2410_GPIO_BANKD
mdefine_line|#define S3C2410_GPIO_BANKD   (32*3)
DECL|macro|S3C2410_GPIO_BANKE
mdefine_line|#define S3C2410_GPIO_BANKE   (32*4)
DECL|macro|S3C2410_GPIO_BANKF
mdefine_line|#define S3C2410_GPIO_BANKF   (32*5)
DECL|macro|S3C2410_GPIO_BANKG
mdefine_line|#define S3C2410_GPIO_BANKG   (32*6)
DECL|macro|S3C2410_GPIO_BANKH
mdefine_line|#define S3C2410_GPIO_BANKH   (32*7)
DECL|macro|S3C2410_GPIO_BASE
mdefine_line|#define S3C2410_GPIO_BASE(pin)   ((((pin) &amp; ~31) &gt;&gt; 1) + S3C2410_VA_GPIO)
DECL|macro|S3C2410_GPIO_OFFSET
mdefine_line|#define S3C2410_GPIO_OFFSET(pin) ((pin) &amp; 31)
multiline_comment|/* general configuration options */
DECL|macro|S3C2410_GPIO_LEAVE
mdefine_line|#define S3C2410_GPIO_LEAVE   (0xFFFFFFFF)
multiline_comment|/* configure GPIO ports A..G */
DECL|macro|S3C2410_GPIOREG
mdefine_line|#define S3C2410_GPIOREG(x) ((x) + S3C2410_VA_GPIO)
multiline_comment|/* port A - 22bits, zero in bit X makes pin X output&n; * 1 makes port special function, this is default&n;*/
DECL|macro|S3C2410_GPACON
mdefine_line|#define S3C2410_GPACON&t;   S3C2410_GPIOREG(0x00)
DECL|macro|S3C2410_GPADAT
mdefine_line|#define S3C2410_GPADAT&t;   S3C2410_GPIOREG(0x04)
DECL|macro|S3C2410_GPA0
mdefine_line|#define S3C2410_GPA0         S3C2410_GPIONO(S3C2410_GPIO_BANKA, 0)
DECL|macro|S3C2410_GPA0_OUT
mdefine_line|#define S3C2410_GPA0_OUT     (0&lt;&lt;0)
DECL|macro|S3C2410_GPA0_ADDR0
mdefine_line|#define S3C2410_GPA0_ADDR0   (1&lt;&lt;0)
DECL|macro|S3C2410_GPA1
mdefine_line|#define S3C2410_GPA1         S3C2410_GPIONO(S3C2410_GPIO_BANKA, 1)
DECL|macro|S3C2410_GPA1_OUT
mdefine_line|#define S3C2410_GPA1_OUT     (0&lt;&lt;1)
DECL|macro|S3C2410_GPA1_ADDR16
mdefine_line|#define S3C2410_GPA1_ADDR16  (1&lt;&lt;1)
DECL|macro|S3C2410_GPA2
mdefine_line|#define S3C2410_GPA2         S3C2410_GPIONO(S3C2410_GPIO_BANKA, 2)
DECL|macro|S3C2410_GPA2_OUT
mdefine_line|#define S3C2410_GPA2_OUT     (0&lt;&lt;2)
DECL|macro|S3C2410_GPA2_ADDR17
mdefine_line|#define S3C2410_GPA2_ADDR17  (1&lt;&lt;2)
DECL|macro|S3C2410_GPA3
mdefine_line|#define S3C2410_GPA3         S3C2410_GPIONO(S3C2410_GPIO_BANKA, 3)
DECL|macro|S3C2410_GPA3_OUT
mdefine_line|#define S3C2410_GPA3_OUT     (0&lt;&lt;3)
DECL|macro|S3C2410_GPA3_ADDR18
mdefine_line|#define S3C2410_GPA3_ADDR18  (1&lt;&lt;3)
DECL|macro|S3C2410_GPA4
mdefine_line|#define S3C2410_GPA4         S3C2410_GPIONO(S3C2410_GPIO_BANKA, 4)
DECL|macro|S3C2410_GPA4_OUT
mdefine_line|#define S3C2410_GPA4_OUT     (0&lt;&lt;4)
DECL|macro|S3C2410_GPA4_ADDR19
mdefine_line|#define S3C2410_GPA4_ADDR19  (1&lt;&lt;4)
DECL|macro|S3C2410_GPA5
mdefine_line|#define S3C2410_GPA5         S3C2410_GPIONO(S3C2410_GPIO_BANKA, 5)
DECL|macro|S3C2410_GPA5_OUT
mdefine_line|#define S3C2410_GPA5_OUT     (0&lt;&lt;5)
DECL|macro|S3C2410_GPA5_ADDR20
mdefine_line|#define S3C2410_GPA5_ADDR20  (1&lt;&lt;5)
DECL|macro|S3C2410_GPA6
mdefine_line|#define S3C2410_GPA6         S3C2410_GPIONO(S3C2410_GPIO_BANKA, 6)
DECL|macro|S3C2410_GPA6_OUT
mdefine_line|#define S3C2410_GPA6_OUT     (0&lt;&lt;6)
DECL|macro|S3C2410_GPA6_ADDR21
mdefine_line|#define S3C2410_GPA6_ADDR21  (1&lt;&lt;6)
DECL|macro|S3C2410_GPA7
mdefine_line|#define S3C2410_GPA7         S3C2410_GPIONO(S3C2410_GPIO_BANKA, 7)
DECL|macro|S3C2410_GPA7_OUT
mdefine_line|#define S3C2410_GPA7_OUT     (0&lt;&lt;7)
DECL|macro|S3C2410_GPA7_ADDR22
mdefine_line|#define S3C2410_GPA7_ADDR22  (1&lt;&lt;7)
DECL|macro|S3C2410_GPA8
mdefine_line|#define S3C2410_GPA8         S3C2410_GPIONO(S3C2410_GPIO_BANKA, 8)
DECL|macro|S3C2410_GPA8_OUT
mdefine_line|#define S3C2410_GPA8_OUT     (0&lt;&lt;8)
DECL|macro|S3C2410_GPA8_ADDR23
mdefine_line|#define S3C2410_GPA8_ADDR23  (1&lt;&lt;8)
DECL|macro|S3C2410_GPA9
mdefine_line|#define S3C2410_GPA9         S3C2410_GPIONO(S3C2410_GPIO_BANKA, 9)
DECL|macro|S3C2410_GPA9_OUT
mdefine_line|#define S3C2410_GPA9_OUT     (0&lt;&lt;9)
DECL|macro|S3C2410_GPA9_ADDR24
mdefine_line|#define S3C2410_GPA9_ADDR24  (1&lt;&lt;9)
DECL|macro|S3C2410_GPA10
mdefine_line|#define S3C2410_GPA10        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 10)
DECL|macro|S3C2410_GPA10_OUT
mdefine_line|#define S3C2410_GPA10_OUT    (0&lt;&lt;10)
DECL|macro|S3C2410_GPA10_ADDR25
mdefine_line|#define S3C2410_GPA10_ADDR25 (1&lt;&lt;10)
DECL|macro|S3C2410_GPA11
mdefine_line|#define S3C2410_GPA11        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 11)
DECL|macro|S3C2410_GPA11_OUT
mdefine_line|#define S3C2410_GPA11_OUT    (0&lt;&lt;11)
DECL|macro|S3C2410_GPA11_ADDR26
mdefine_line|#define S3C2410_GPA11_ADDR26 (1&lt;&lt;11)
DECL|macro|S3C2410_GPA12
mdefine_line|#define S3C2410_GPA12        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 12)
DECL|macro|S3C2410_GPA12_OUT
mdefine_line|#define S3C2410_GPA12_OUT    (0&lt;&lt;12)
DECL|macro|S3C2410_GPA12_nGCS1
mdefine_line|#define S3C2410_GPA12_nGCS1  (1&lt;&lt;12)
DECL|macro|S3C2410_GPA13
mdefine_line|#define S3C2410_GPA13        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 13)
DECL|macro|S3C2410_GPA13_OUT
mdefine_line|#define S3C2410_GPA13_OUT    (0&lt;&lt;13)
DECL|macro|S3C2410_GPA13_nGCS2
mdefine_line|#define S3C2410_GPA13_nGCS2  (1&lt;&lt;13)
DECL|macro|S3C2410_GPA14
mdefine_line|#define S3C2410_GPA14        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 14)
DECL|macro|S3C2410_GPA14_OUT
mdefine_line|#define S3C2410_GPA14_OUT    (0&lt;&lt;14)
DECL|macro|S3C2410_GPA14_nGCS3
mdefine_line|#define S3C2410_GPA14_nGCS3  (1&lt;&lt;14)
DECL|macro|S3C2410_GPA15
mdefine_line|#define S3C2410_GPA15        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 15)
DECL|macro|S3C2410_GPA15_OUT
mdefine_line|#define S3C2410_GPA15_OUT    (0&lt;&lt;15)
DECL|macro|S3C2410_GPA15_nGCS4
mdefine_line|#define S3C2410_GPA15_nGCS4  (1&lt;&lt;15)
DECL|macro|S3C2410_GPA16
mdefine_line|#define S3C2410_GPA16        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 16)
DECL|macro|S3C2410_GPA16_OUT
mdefine_line|#define S3C2410_GPA16_OUT    (0&lt;&lt;16)
DECL|macro|S3C2410_GPA16_nGCS5
mdefine_line|#define S3C2410_GPA16_nGCS5  (1&lt;&lt;16)
DECL|macro|S3C2410_GPA17
mdefine_line|#define S3C2410_GPA17        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 17)
DECL|macro|S3C2410_GPA17_OUT
mdefine_line|#define S3C2410_GPA17_OUT    (0&lt;&lt;17)
DECL|macro|S3C2410_GPA17_CLE
mdefine_line|#define S3C2410_GPA17_CLE    (1&lt;&lt;17)
DECL|macro|S3C2410_GPA18
mdefine_line|#define S3C2410_GPA18        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 18)
DECL|macro|S3C2410_GPA18_OUT
mdefine_line|#define S3C2410_GPA18_OUT    (0&lt;&lt;18)
DECL|macro|S3C2410_GPA18_ALE
mdefine_line|#define S3C2410_GPA18_ALE    (1&lt;&lt;18)
DECL|macro|S3C2410_GPA19
mdefine_line|#define S3C2410_GPA19        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 19)
DECL|macro|S3C2410_GPA19_OUT
mdefine_line|#define S3C2410_GPA19_OUT    (0&lt;&lt;19)
DECL|macro|S3C2410_GPA19_nFWE
mdefine_line|#define S3C2410_GPA19_nFWE   (1&lt;&lt;19)
DECL|macro|S3C2410_GPA20
mdefine_line|#define S3C2410_GPA20        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 20)
DECL|macro|S3C2410_GPA20_OUT
mdefine_line|#define S3C2410_GPA20_OUT    (0&lt;&lt;20)
DECL|macro|S3C2410_GPA20_nFRE
mdefine_line|#define S3C2410_GPA20_nFRE   (1&lt;&lt;20)
DECL|macro|S3C2410_GPA21
mdefine_line|#define S3C2410_GPA21        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 21)
DECL|macro|S3C2410_GPA21_OUT
mdefine_line|#define S3C2410_GPA21_OUT    (0&lt;&lt;21)
DECL|macro|S3C2410_GPA21_nRSTOUT
mdefine_line|#define S3C2410_GPA21_nRSTOUT (1&lt;&lt;21)
DECL|macro|S3C2410_GPA22
mdefine_line|#define S3C2410_GPA22        S3C2410_GPIONO(S3C2410_GPIO_BANKA, 22)
DECL|macro|S3C2410_GPA22_OUT
mdefine_line|#define S3C2410_GPA22_OUT    (0&lt;&lt;22)
DECL|macro|S3C2410_GPA22_nFCE
mdefine_line|#define S3C2410_GPA22_nFCE   (1&lt;&lt;22)
multiline_comment|/* 0x08 and 0x0c are reserved */
multiline_comment|/* GPB is 10 IO pins, each configured by 2 bits each in GPBCON.&n; *   00 = input, 01 = output, 10=special function, 11=reserved&n; * bit 0,1 = pin 0, 2,3= pin 1...&n; *&n; * CPBUP = pull up resistor control, 1=disabled, 0=enabled&n;*/
DECL|macro|S3C2410_GPBCON
mdefine_line|#define S3C2410_GPBCON&t;   S3C2410_GPIOREG(0x10)
DECL|macro|S3C2410_GPBDAT
mdefine_line|#define S3C2410_GPBDAT&t;   S3C2410_GPIOREG(0x14)
DECL|macro|S3C2410_GPBUP
mdefine_line|#define S3C2410_GPBUP&t;   S3C2410_GPIOREG(0x18)
multiline_comment|/* no i/o pin in port b can have value 3! */
DECL|macro|S3C2410_GPB0
mdefine_line|#define S3C2410_GPB0         S3C2410_GPIONO(S3C2410_GPIO_BANKB, 0)
DECL|macro|S3C2410_GPB0_INP
mdefine_line|#define S3C2410_GPB0_INP     (0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPB0_OUTP
mdefine_line|#define S3C2410_GPB0_OUTP    (0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPB0_TOUT0
mdefine_line|#define S3C2410_GPB0_TOUT0   (0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPB1
mdefine_line|#define S3C2410_GPB1         S3C2410_GPIONO(S3C2410_GPIO_BANKB, 1)
DECL|macro|S3C2410_GPB1_INP
mdefine_line|#define S3C2410_GPB1_INP     (0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPB1_OUTP
mdefine_line|#define S3C2410_GPB1_OUTP    (0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPB1_TOUT1
mdefine_line|#define S3C2410_GPB1_TOUT1   (0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPB2
mdefine_line|#define S3C2410_GPB2         S3C2410_GPIONO(S3C2410_GPIO_BANKB, 2)
DECL|macro|S3C2410_GPB2_INP
mdefine_line|#define S3C2410_GPB2_INP     (0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPB2_OUTP
mdefine_line|#define S3C2410_GPB2_OUTP    (0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPB2_TOUT2
mdefine_line|#define S3C2410_GPB2_TOUT2   (0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPB3
mdefine_line|#define S3C2410_GPB3         S3C2410_GPIONO(S3C2410_GPIO_BANKB, 3)
DECL|macro|S3C2410_GPB3_INP
mdefine_line|#define S3C2410_GPB3_INP     (0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPB3_OUTP
mdefine_line|#define S3C2410_GPB3_OUTP    (0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPB3_TOUT3
mdefine_line|#define S3C2410_GPB3_TOUT3   (0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPB4
mdefine_line|#define S3C2410_GPB4         S3C2410_GPIONO(S3C2410_GPIO_BANKB, 4)
DECL|macro|S3C2410_GPB4_INP
mdefine_line|#define S3C2410_GPB4_INP     (0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPB4_OUTP
mdefine_line|#define S3C2410_GPB4_OUTP    (0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPB4_TCLK0
mdefine_line|#define S3C2410_GPB4_TCLK0   (0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPB4_MASK
mdefine_line|#define S3C2410_GPB4_MASK    (0x03 &lt;&lt; 8)
DECL|macro|S3C2410_GPB5
mdefine_line|#define S3C2410_GPB5         S3C2410_GPIONO(S3C2410_GPIO_BANKB, 5)
DECL|macro|S3C2410_GPB5_INP
mdefine_line|#define S3C2410_GPB5_INP     (0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPB5_OUTP
mdefine_line|#define S3C2410_GPB5_OUTP    (0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPB5_nXBACK
mdefine_line|#define S3C2410_GPB5_nXBACK  (0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPB6
mdefine_line|#define S3C2410_GPB6         S3C2410_GPIONO(S3C2410_GPIO_BANKB, 6)
DECL|macro|S3C2410_GPB6_INP
mdefine_line|#define S3C2410_GPB6_INP     (0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPB6_OUTP
mdefine_line|#define S3C2410_GPB6_OUTP    (0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPB6_nXBREQ
mdefine_line|#define S3C2410_GPB6_nXBREQ  (0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPB7
mdefine_line|#define S3C2410_GPB7         S3C2410_GPIONO(S3C2410_GPIO_BANKB, 7)
DECL|macro|S3C2410_GPB7_INP
mdefine_line|#define S3C2410_GPB7_INP     (0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPB7_OUTP
mdefine_line|#define S3C2410_GPB7_OUTP    (0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPB7_nXDACK1
mdefine_line|#define S3C2410_GPB7_nXDACK1 (0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPB8
mdefine_line|#define S3C2410_GPB8         S3C2410_GPIONO(S3C2410_GPIO_BANKB, 8)
DECL|macro|S3C2410_GPB8_INP
mdefine_line|#define S3C2410_GPB8_INP     (0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPB8_OUTP
mdefine_line|#define S3C2410_GPB8_OUTP    (0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPB8_nXDREQ1
mdefine_line|#define S3C2410_GPB8_nXDREQ1 (0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPB9
mdefine_line|#define S3C2410_GPB9         S3C2410_GPIONO(S3C2410_GPIO_BANKB, 9)
DECL|macro|S3C2410_GPB9_INP
mdefine_line|#define S3C2410_GPB9_INP     (0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPB9_OUTP
mdefine_line|#define S3C2410_GPB9_OUTP    (0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPB9_nXDACK0
mdefine_line|#define S3C2410_GPB9_nXDACK0 (0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPB10
mdefine_line|#define S3C2410_GPB10        S3C2410_GPIONO(S3C2410_GPIO_BANKB, 10)
DECL|macro|S3C2410_GPB10_INP
mdefine_line|#define S3C2410_GPB10_INP    (0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPB10_OUTP
mdefine_line|#define S3C2410_GPB10_OUTP   (0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPB10_nXDRE0
mdefine_line|#define S3C2410_GPB10_nXDRE0 (0x02 &lt;&lt; 18)
multiline_comment|/* Port C consits of 16 GPIO/Special function&n; *&n; * almost identical setup to port b, but the special functions are mostly&n; * to do with the video system&squot;s sync/etc.&n;*/
DECL|macro|S3C2410_GPCCON
mdefine_line|#define S3C2410_GPCCON&t;   S3C2410_GPIOREG(0x20)
DECL|macro|S3C2410_GPCDAT
mdefine_line|#define S3C2410_GPCDAT&t;   S3C2410_GPIOREG(0x24)
DECL|macro|S3C2410_GPCUP
mdefine_line|#define S3C2410_GPCUP&t;   S3C2410_GPIOREG(0x28)
DECL|macro|S3C2410_GPC0
mdefine_line|#define S3C2410_GPC0            S3C2410_GPIONO(S3C2410_GPIO_BANKC, 0)
DECL|macro|S3C2410_GPC0_INP
mdefine_line|#define S3C2410_GPC0_INP&t;(0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPC0_OUTP
mdefine_line|#define S3C2410_GPC0_OUTP&t;(0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPC0_LEND
mdefine_line|#define S3C2410_GPC0_LEND&t;(0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPC1
mdefine_line|#define S3C2410_GPC1            S3C2410_GPIONO(S3C2410_GPIO_BANKC, 1)
DECL|macro|S3C2410_GPC1_INP
mdefine_line|#define S3C2410_GPC1_INP&t;(0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPC1_OUTP
mdefine_line|#define S3C2410_GPC1_OUTP&t;(0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPC1_VCLK
mdefine_line|#define S3C2410_GPC1_VCLK&t;(0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPC2
mdefine_line|#define S3C2410_GPC2            S3C2410_GPIONO(S3C2410_GPIO_BANKC, 2)
DECL|macro|S3C2410_GPC2_INP
mdefine_line|#define S3C2410_GPC2_INP&t;(0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPC2_OUTP
mdefine_line|#define S3C2410_GPC2_OUTP&t;(0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPC2_VLINE
mdefine_line|#define S3C2410_GPC2_VLINE&t;(0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPC3
mdefine_line|#define S3C2410_GPC3            S3C2410_GPIONO(S3C2410_GPIO_BANKC, 3)
DECL|macro|S3C2410_GPC3_INP
mdefine_line|#define S3C2410_GPC3_INP&t;(0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPC3_OUTP
mdefine_line|#define S3C2410_GPC3_OUTP&t;(0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPC3_VFRAME
mdefine_line|#define S3C2410_GPC3_VFRAME&t;(0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPC4
mdefine_line|#define S3C2410_GPC4            S3C2410_GPIONO(S3C2410_GPIO_BANKC, 4)
DECL|macro|S3C2410_GPC4_INP
mdefine_line|#define S3C2410_GPC4_INP&t;(0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPC4_OUTP
mdefine_line|#define S3C2410_GPC4_OUTP&t;(0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPC4_VM
mdefine_line|#define S3C2410_GPC4_VM&t;&t;(0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPC5
mdefine_line|#define S3C2410_GPC5            S3C2410_GPIONO(S3C2410_GPIO_BANKC, 5)
DECL|macro|S3C2410_GPC5_INP
mdefine_line|#define S3C2410_GPC5_INP&t;(0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPC5_OUTP
mdefine_line|#define S3C2410_GPC5_OUTP&t;(0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPC5_LCDVF0
mdefine_line|#define S3C2410_GPC5_LCDVF0&t;(0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPC6
mdefine_line|#define S3C2410_GPC6            S3C2410_GPIONO(S3C2410_GPIO_BANKC, 6)
DECL|macro|S3C2410_GPC6_INP
mdefine_line|#define S3C2410_GPC6_INP&t;(0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPC6_OUTP
mdefine_line|#define S3C2410_GPC6_OUTP&t;(0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPC6_LCDVF1
mdefine_line|#define S3C2410_GPC6_LCDVF1&t;(0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPC7
mdefine_line|#define S3C2410_GPC7            S3C2410_GPIONO(S3C2410_GPIO_BANKC, 7)
DECL|macro|S3C2410_GPC7_INP
mdefine_line|#define S3C2410_GPC7_INP&t;(0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPC7_OUTP
mdefine_line|#define S3C2410_GPC7_OUTP&t;(0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPC7_LCDVF2
mdefine_line|#define S3C2410_GPC7_LCDVF2&t;(0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPC8
mdefine_line|#define S3C2410_GPC8            S3C2410_GPIONO(S3C2410_GPIO_BANKC, 8)
DECL|macro|S3C2410_GPC8_INP
mdefine_line|#define S3C2410_GPC8_INP&t;(0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPC8_OUTP
mdefine_line|#define S3C2410_GPC8_OUTP&t;(0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPC8_VD0
mdefine_line|#define S3C2410_GPC8_VD0&t;(0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPC9
mdefine_line|#define S3C2410_GPC9            S3C2410_GPIONO(S3C2410_GPIO_BANKC, 9)
DECL|macro|S3C2410_GPC9_INP
mdefine_line|#define S3C2410_GPC9_INP&t;(0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPC9_OUTP
mdefine_line|#define S3C2410_GPC9_OUTP&t;(0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPC9_VD1
mdefine_line|#define S3C2410_GPC9_VD1&t;(0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPC10
mdefine_line|#define S3C2410_GPC10           S3C2410_GPIONO(S3C2410_GPIO_BANKC, 10)
DECL|macro|S3C2410_GPC10_INP
mdefine_line|#define S3C2410_GPC10_INP&t;(0x00 &lt;&lt; 20)
DECL|macro|S3C2410_GPC10_OUTP
mdefine_line|#define S3C2410_GPC10_OUTP&t;(0x01 &lt;&lt; 20)
DECL|macro|S3C2410_GPC10_VD2
mdefine_line|#define S3C2410_GPC10_VD2&t;(0x02 &lt;&lt; 20)
DECL|macro|S3C2410_GPC11
mdefine_line|#define S3C2410_GPC11           S3C2410_GPIONO(S3C2410_GPIO_BANKC, 11)
DECL|macro|S3C2410_GPC11_INP
mdefine_line|#define S3C2410_GPC11_INP&t;(0x00 &lt;&lt; 22)
DECL|macro|S3C2410_GPC11_OUTP
mdefine_line|#define S3C2410_GPC11_OUTP&t;(0x01 &lt;&lt; 22)
DECL|macro|S3C2410_GPC11_VD3
mdefine_line|#define S3C2410_GPC11_VD3&t;(0x02 &lt;&lt; 22)
DECL|macro|S3C2410_GPC12
mdefine_line|#define S3C2410_GPC12           S3C2410_GPIONO(S3C2410_GPIO_BANKC, 12)
DECL|macro|S3C2410_GPC12_INP
mdefine_line|#define S3C2410_GPC12_INP&t;(0x00 &lt;&lt; 24)
DECL|macro|S3C2410_GPC12_OUTP
mdefine_line|#define S3C2410_GPC12_OUTP&t;(0x01 &lt;&lt; 24)
DECL|macro|S3C2410_GPC12_VD4
mdefine_line|#define S3C2410_GPC12_VD4&t;(0x02 &lt;&lt; 24)
DECL|macro|S3C2410_GPC13
mdefine_line|#define S3C2410_GPC13           S3C2410_GPIONO(S3C2410_GPIO_BANKC, 13)
DECL|macro|S3C2410_GPC13_INP
mdefine_line|#define S3C2410_GPC13_INP&t;(0x00 &lt;&lt; 26)
DECL|macro|S3C2410_GPC13_OUTP
mdefine_line|#define S3C2410_GPC13_OUTP&t;(0x01 &lt;&lt; 26)
DECL|macro|S3C2410_GPC13_VD5
mdefine_line|#define S3C2410_GPC13_VD5&t;(0x02 &lt;&lt; 26)
DECL|macro|S3C2410_GPC14
mdefine_line|#define S3C2410_GPC14           S3C2410_GPIONO(S3C2410_GPIO_BANKC, 14)
DECL|macro|S3C2410_GPC14_INP
mdefine_line|#define S3C2410_GPC14_INP&t;(0x00 &lt;&lt; 28)
DECL|macro|S3C2410_GPC14_OUTP
mdefine_line|#define S3C2410_GPC14_OUTP&t;(0x01 &lt;&lt; 28)
DECL|macro|S3C2410_GPC14_VD6
mdefine_line|#define S3C2410_GPC14_VD6&t;(0x02 &lt;&lt; 28)
DECL|macro|S3C2410_GPC15
mdefine_line|#define S3C2410_GPC15           S3C2410_GPIONO(S3C2410_GPIO_BANKC, 15)
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
DECL|macro|S3C2410_GPD0
mdefine_line|#define S3C2410_GPD0            S3C2410_GPIONO(S3C2410_GPIO_BANKD, 0)
DECL|macro|S3C2410_GPD0_INP
mdefine_line|#define S3C2410_GPD0_INP&t;(0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPD0_OUTP
mdefine_line|#define S3C2410_GPD0_OUTP&t;(0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPD0_VD8
mdefine_line|#define S3C2410_GPD0_VD8&t;(0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPD1
mdefine_line|#define S3C2410_GPD1            S3C2410_GPIONO(S3C2410_GPIO_BANKD, 1)
DECL|macro|S3C2410_GPD1_INP
mdefine_line|#define S3C2410_GPD1_INP&t;(0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPD1_OUTP
mdefine_line|#define S3C2410_GPD1_OUTP&t;(0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPD1_VD9
mdefine_line|#define S3C2410_GPD1_VD9&t;(0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPD2
mdefine_line|#define S3C2410_GPD2            S3C2410_GPIONO(S3C2410_GPIO_BANKD, 2)
DECL|macro|S3C2410_GPD2_INP
mdefine_line|#define S3C2410_GPD2_INP&t;(0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPD2_OUTP
mdefine_line|#define S3C2410_GPD2_OUTP&t;(0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPD2_VD10
mdefine_line|#define S3C2410_GPD2_VD10&t;(0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPD3
mdefine_line|#define S3C2410_GPD3            S3C2410_GPIONO(S3C2410_GPIO_BANKD, 3)
DECL|macro|S3C2410_GPD3_INP
mdefine_line|#define S3C2410_GPD3_INP&t;(0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPD3_OUTP
mdefine_line|#define S3C2410_GPD3_OUTP&t;(0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPD3_VD11
mdefine_line|#define S3C2410_GPD3_VD11&t;(0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPD4
mdefine_line|#define S3C2410_GPD4            S3C2410_GPIONO(S3C2410_GPIO_BANKD, 4)
DECL|macro|S3C2410_GPD4_INP
mdefine_line|#define S3C2410_GPD4_INP&t;(0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPD4_OUTP
mdefine_line|#define S3C2410_GPD4_OUTP&t;(0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPD4_VD12
mdefine_line|#define S3C2410_GPD4_VD12&t;(0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPD5
mdefine_line|#define S3C2410_GPD5            S3C2410_GPIONO(S3C2410_GPIO_BANKD, 5)
DECL|macro|S3C2410_GPD5_INP
mdefine_line|#define S3C2410_GPD5_INP&t;(0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPD5_OUTP
mdefine_line|#define S3C2410_GPD5_OUTP&t;(0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPD5_VD13
mdefine_line|#define S3C2410_GPD5_VD13&t;(0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPD6
mdefine_line|#define S3C2410_GPD6            S3C2410_GPIONO(S3C2410_GPIO_BANKD, 6)
DECL|macro|S3C2410_GPD6_INP
mdefine_line|#define S3C2410_GPD6_INP&t;(0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPD6_OUTP
mdefine_line|#define S3C2410_GPD6_OUTP&t;(0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPD6_VD14
mdefine_line|#define S3C2410_GPD6_VD14&t;(0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPD7
mdefine_line|#define S3C2410_GPD7            S3C2410_GPIONO(S3C2410_GPIO_BANKD, 7)
DECL|macro|S3C2410_GPD7_INP
mdefine_line|#define S3C2410_GPD7_INP&t;(0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPD7_OUTP
mdefine_line|#define S3C2410_GPD7_OUTP&t;(0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPD7_VD15
mdefine_line|#define S3C2410_GPD7_VD15&t;(0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPD8
mdefine_line|#define S3C2410_GPD8            S3C2410_GPIONO(S3C2410_GPIO_BANKD, 8)
DECL|macro|S3C2410_GPD8_INP
mdefine_line|#define S3C2410_GPD8_INP&t;(0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPD8_OUTP
mdefine_line|#define S3C2410_GPD8_OUTP&t;(0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPD8_VD16
mdefine_line|#define S3C2410_GPD8_VD16&t;(0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPD9
mdefine_line|#define S3C2410_GPD9            S3C2410_GPIONO(S3C2410_GPIO_BANKD, 9)
DECL|macro|S3C2410_GPD9_INP
mdefine_line|#define S3C2410_GPD9_INP&t;(0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPD9_OUTP
mdefine_line|#define S3C2410_GPD9_OUTP&t;(0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPD9_VD17
mdefine_line|#define S3C2410_GPD9_VD17&t;(0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPD10
mdefine_line|#define S3C2410_GPD10           S3C2410_GPIONO(S3C2410_GPIO_BANKD, 10)
DECL|macro|S3C2410_GPD10_INP
mdefine_line|#define S3C2410_GPD10_INP&t;(0x00 &lt;&lt; 20)
DECL|macro|S3C2410_GPD10_OUTP
mdefine_line|#define S3C2410_GPD10_OUTP&t;(0x01 &lt;&lt; 20)
DECL|macro|S3C2410_GPD10_VD18
mdefine_line|#define S3C2410_GPD10_VD18&t;(0x02 &lt;&lt; 20)
DECL|macro|S3C2410_GPD11
mdefine_line|#define S3C2410_GPD11           S3C2410_GPIONO(S3C2410_GPIO_BANKD, 11)
DECL|macro|S3C2410_GPD11_INP
mdefine_line|#define S3C2410_GPD11_INP&t;(0x00 &lt;&lt; 22)
DECL|macro|S3C2410_GPD11_OUTP
mdefine_line|#define S3C2410_GPD11_OUTP&t;(0x01 &lt;&lt; 22)
DECL|macro|S3C2410_GPD11_VD19
mdefine_line|#define S3C2410_GPD11_VD19&t;(0x02 &lt;&lt; 22)
DECL|macro|S3C2410_GPD12
mdefine_line|#define S3C2410_GPD12           S3C2410_GPIONO(S3C2410_GPIO_BANKD, 12)
DECL|macro|S3C2410_GPD12_INP
mdefine_line|#define S3C2410_GPD12_INP&t;(0x00 &lt;&lt; 24)
DECL|macro|S3C2410_GPD12_OUTP
mdefine_line|#define S3C2410_GPD12_OUTP&t;(0x01 &lt;&lt; 24)
DECL|macro|S3C2410_GPD12_VD20
mdefine_line|#define S3C2410_GPD12_VD20&t;(0x02 &lt;&lt; 24)
DECL|macro|S3C2410_GPD13
mdefine_line|#define S3C2410_GPD13           S3C2410_GPIONO(S3C2410_GPIO_BANKD, 13)
DECL|macro|S3C2410_GPD13_INP
mdefine_line|#define S3C2410_GPD13_INP&t;(0x00 &lt;&lt; 26)
DECL|macro|S3C2410_GPD13_OUTP
mdefine_line|#define S3C2410_GPD13_OUTP&t;(0x01 &lt;&lt; 26)
DECL|macro|S3C2410_GPD13_VD21
mdefine_line|#define S3C2410_GPD13_VD21&t;(0x02 &lt;&lt; 26)
DECL|macro|S3C2410_GPD14
mdefine_line|#define S3C2410_GPD14           S3C2410_GPIONO(S3C2410_GPIO_BANKD, 14)
DECL|macro|S3C2410_GPD14_INP
mdefine_line|#define S3C2410_GPD14_INP&t;(0x00 &lt;&lt; 28)
DECL|macro|S3C2410_GPD14_OUTP
mdefine_line|#define S3C2410_GPD14_OUTP&t;(0x01 &lt;&lt; 28)
DECL|macro|S3C2410_GPD14_VD22
mdefine_line|#define S3C2410_GPD14_VD22&t;(0x02 &lt;&lt; 28)
DECL|macro|S3C2410_GPD15
mdefine_line|#define S3C2410_GPD15           S3C2410_GPIONO(S3C2410_GPIO_BANKD, 15)
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
DECL|macro|S3C2410_GPE0
mdefine_line|#define S3C2410_GPE0           S3C2410_GPIONO(S3C2410_GPIO_BANKE, 0)
DECL|macro|S3C2410_GPE0_INP
mdefine_line|#define S3C2410_GPE0_INP       (0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPE0_OUTP
mdefine_line|#define S3C2410_GPE0_OUTP      (0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPE0_I2SLRCK
mdefine_line|#define S3C2410_GPE0_I2SLRCK   (0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPE0_MASK
mdefine_line|#define S3C2410_GPE0_MASK      (0x03 &lt;&lt; 0)
DECL|macro|S3C2410_GPE1
mdefine_line|#define S3C2410_GPE1           S3C2410_GPIONO(S3C2410_GPIO_BANKE, 1)
DECL|macro|S3C2410_GPE1_INP
mdefine_line|#define S3C2410_GPE1_INP       (0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPE1_OUTP
mdefine_line|#define S3C2410_GPE1_OUTP      (0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPE1_I2SSCLK
mdefine_line|#define S3C2410_GPE1_I2SSCLK   (0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPE1_MASK
mdefine_line|#define S3C2410_GPE1_MASK      (0x03 &lt;&lt; 2)
DECL|macro|S3C2410_GPE2
mdefine_line|#define S3C2410_GPE2           S3C2410_GPIONO(S3C2410_GPIO_BANKE, 2)
DECL|macro|S3C2410_GPE2_INP
mdefine_line|#define S3C2410_GPE2_INP       (0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPE2_OUTP
mdefine_line|#define S3C2410_GPE2_OUTP      (0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPE2_CDCLK
mdefine_line|#define S3C2410_GPE2_CDCLK     (0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPE3
mdefine_line|#define S3C2410_GPE3           S3C2410_GPIONO(S3C2410_GPIO_BANKE, 3)
DECL|macro|S3C2410_GPE3_INP
mdefine_line|#define S3C2410_GPE3_INP       (0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPE3_OUTP
mdefine_line|#define S3C2410_GPE3_OUTP      (0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPE3_I2SSDI
mdefine_line|#define S3C2410_GPE3_I2SSDI    (0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPE3_MASK
mdefine_line|#define S3C2410_GPE3_MASK      (0x03 &lt;&lt; 6)
DECL|macro|S3C2410_GPE4
mdefine_line|#define S3C2410_GPE4           S3C2410_GPIONO(S3C2410_GPIO_BANKE, 4)
DECL|macro|S3C2410_GPE4_INP
mdefine_line|#define S3C2410_GPE4_INP       (0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPE4_OUTP
mdefine_line|#define S3C2410_GPE4_OUTP      (0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPE4_I2SSDO
mdefine_line|#define S3C2410_GPE4_I2SSDO    (0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPE4_MASK
mdefine_line|#define S3C2410_GPE4_MASK      (0x03 &lt;&lt; 8)
DECL|macro|S3C2410_GPE5
mdefine_line|#define S3C2410_GPE5           S3C2410_GPIONO(S3C2410_GPIO_BANKE, 5)
DECL|macro|S3C2410_GPE5_INP
mdefine_line|#define S3C2410_GPE5_INP       (0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPE5_OUTP
mdefine_line|#define S3C2410_GPE5_OUTP      (0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPE5_SDCLK
mdefine_line|#define S3C2410_GPE5_SDCLK     (0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPE6
mdefine_line|#define S3C2410_GPE6           S3C2410_GPIONO(S3C2410_GPIO_BANKE, 6)
DECL|macro|S3C2410_GPE6_INP
mdefine_line|#define S3C2410_GPE6_INP       (0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPE6_OUTP
mdefine_line|#define S3C2410_GPE6_OUTP      (0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPE6_SDCLK
mdefine_line|#define S3C2410_GPE6_SDCLK     (0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPE7
mdefine_line|#define S3C2410_GPE7           S3C2410_GPIONO(S3C2410_GPIO_BANKE, 7)
DECL|macro|S3C2410_GPE7_INP
mdefine_line|#define S3C2410_GPE7_INP       (0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPE7_OUTP
mdefine_line|#define S3C2410_GPE7_OUTP      (0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPE7_SDCMD
mdefine_line|#define S3C2410_GPE7_SDCMD     (0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPE8
mdefine_line|#define S3C2410_GPE8           S3C2410_GPIONO(S3C2410_GPIO_BANKE, 8)
DECL|macro|S3C2410_GPE8_INP
mdefine_line|#define S3C2410_GPE8_INP       (0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPE8_OUTP
mdefine_line|#define S3C2410_GPE8_OUTP      (0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPE8_SDDAT1
mdefine_line|#define S3C2410_GPE8_SDDAT1    (0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPE9
mdefine_line|#define S3C2410_GPE9           S3C2410_GPIONO(S3C2410_GPIO_BANKE, 9)
DECL|macro|S3C2410_GPE9_INP
mdefine_line|#define S3C2410_GPE9_INP       (0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPE9_OUTP
mdefine_line|#define S3C2410_GPE9_OUTP      (0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPE9_SDDAT2
mdefine_line|#define S3C2410_GPE9_SDDAT2    (0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPE10
mdefine_line|#define S3C2410_GPE10          S3C2410_GPIONO(S3C2410_GPIO_BANKE, 10)
DECL|macro|S3C2410_GPE10_INP
mdefine_line|#define S3C2410_GPE10_INP      (0x00 &lt;&lt; 20)
DECL|macro|S3C2410_GPE10_OUTP
mdefine_line|#define S3C2410_GPE10_OUTP     (0x01 &lt;&lt; 20)
DECL|macro|S3C2410_GPE10_SDDAT3
mdefine_line|#define S3C2410_GPE10_SDDAT3   (0x02 &lt;&lt; 20)
DECL|macro|S3C2410_GPE11
mdefine_line|#define S3C2410_GPE11          S3C2410_GPIONO(S3C2410_GPIO_BANKE, 11)
DECL|macro|S3C2410_GPE11_INP
mdefine_line|#define S3C2410_GPE11_INP      (0x00 &lt;&lt; 22)
DECL|macro|S3C2410_GPE11_OUTP
mdefine_line|#define S3C2410_GPE11_OUTP     (0x01 &lt;&lt; 22)
DECL|macro|S3C2410_GPE11_SPIMISO0
mdefine_line|#define S3C2410_GPE11_SPIMISO0 (0x02 &lt;&lt; 22)
DECL|macro|S3C2410_GPE12
mdefine_line|#define S3C2410_GPE12          S3C2410_GPIONO(S3C2410_GPIO_BANKE, 12)
DECL|macro|S3C2410_GPE12_INP
mdefine_line|#define S3C2410_GPE12_INP      (0x00 &lt;&lt; 24)
DECL|macro|S3C2410_GPE12_OUTP
mdefine_line|#define S3C2410_GPE12_OUTP     (0x01 &lt;&lt; 24)
DECL|macro|S3C2410_GPE12_SPIMOSI0
mdefine_line|#define S3C2410_GPE12_SPIMOSI0 (0x02 &lt;&lt; 24)
DECL|macro|S3C2410_GPE13
mdefine_line|#define S3C2410_GPE13          S3C2410_GPIONO(S3C2410_GPIO_BANKE, 13)
DECL|macro|S3C2410_GPE13_INP
mdefine_line|#define S3C2410_GPE13_INP      (0x00 &lt;&lt; 26)
DECL|macro|S3C2410_GPE13_OUTP
mdefine_line|#define S3C2410_GPE13_OUTP     (0x01 &lt;&lt; 26)
DECL|macro|S3C2410_GPE13_SPICLK0
mdefine_line|#define S3C2410_GPE13_SPICLK0  (0x02 &lt;&lt; 26)
DECL|macro|S3C2410_GPE14
mdefine_line|#define S3C2410_GPE14          S3C2410_GPIONO(S3C2410_GPIO_BANKE, 14)
DECL|macro|S3C2410_GPE14_INP
mdefine_line|#define S3C2410_GPE14_INP      (0x00 &lt;&lt; 28)
DECL|macro|S3C2410_GPE14_OUTP
mdefine_line|#define S3C2410_GPE14_OUTP     (0x01 &lt;&lt; 28)
DECL|macro|S3C2410_GPE14_IICSCL
mdefine_line|#define S3C2410_GPE14_IICSCL   (0x02 &lt;&lt; 28)
DECL|macro|S3C2410_GPE14_MASK
mdefine_line|#define S3C2410_GPE14_MASK     (0x03 &lt;&lt; 28)
DECL|macro|S3C2410_GPE15
mdefine_line|#define S3C2410_GPE15          S3C2410_GPIONO(S3C2410_GPIO_BANKE, 15)
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
DECL|macro|S3C2410_GPF0
mdefine_line|#define S3C2410_GPF0        S3C2410_GPIONO(S3C2410_GPIO_BANKF, 0)
DECL|macro|S3C2410_GPF0_INP
mdefine_line|#define S3C2410_GPF0_INP    (0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPF0_OUTP
mdefine_line|#define S3C2410_GPF0_OUTP   (0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPF0_EINT0
mdefine_line|#define S3C2410_GPF0_EINT0  (0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPF1
mdefine_line|#define S3C2410_GPF1        S3C2410_GPIONO(S3C2410_GPIO_BANKF, 1)
DECL|macro|S3C2410_GPF1_INP
mdefine_line|#define S3C2410_GPF1_INP    (0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPF1_OUTP
mdefine_line|#define S3C2410_GPF1_OUTP   (0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPF1_EINT1
mdefine_line|#define S3C2410_GPF1_EINT1  (0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPF2
mdefine_line|#define S3C2410_GPF2        S3C2410_GPIONO(S3C2410_GPIO_BANKF, 2)
DECL|macro|S3C2410_GPF2_INP
mdefine_line|#define S3C2410_GPF2_INP    (0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPF2_OUTP
mdefine_line|#define S3C2410_GPF2_OUTP   (0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPF2_EINT2
mdefine_line|#define S3C2410_GPF2_EINT2  (0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPF3
mdefine_line|#define S3C2410_GPF3        S3C2410_GPIONO(S3C2410_GPIO_BANKF, 3)
DECL|macro|S3C2410_GPF3_INP
mdefine_line|#define S3C2410_GPF3_INP    (0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPF3_OUTP
mdefine_line|#define S3C2410_GPF3_OUTP   (0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPF3_EINT3
mdefine_line|#define S3C2410_GPF3_EINT3  (0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPF4
mdefine_line|#define S3C2410_GPF4        S3C2410_GPIONO(S3C2410_GPIO_BANKF, 4)
DECL|macro|S3C2410_GPF4_INP
mdefine_line|#define S3C2410_GPF4_INP    (0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPF4_OUTP
mdefine_line|#define S3C2410_GPF4_OUTP   (0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPF4_EINT4
mdefine_line|#define S3C2410_GPF4_EINT4  (0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPF5
mdefine_line|#define S3C2410_GPF5        S3C2410_GPIONO(S3C2410_GPIO_BANKF, 5)
DECL|macro|S3C2410_GPF5_INP
mdefine_line|#define S3C2410_GPF5_INP    (0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPF5_OUTP
mdefine_line|#define S3C2410_GPF5_OUTP   (0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPF5_EINT5
mdefine_line|#define S3C2410_GPF5_EINT5  (0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPF6
mdefine_line|#define S3C2410_GPF6        S3C2410_GPIONO(S3C2410_GPIO_BANKF, 6)
DECL|macro|S3C2410_GPF6_INP
mdefine_line|#define S3C2410_GPF6_INP    (0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPF6_OUTP
mdefine_line|#define S3C2410_GPF6_OUTP   (0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPF6_EINT6
mdefine_line|#define S3C2410_GPF6_EINT6  (0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPF7
mdefine_line|#define S3C2410_GPF7        S3C2410_GPIONO(S3C2410_GPIO_BANKF, 7)
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
DECL|macro|S3C2410_GPG0
mdefine_line|#define S3C2410_GPG0          S3C2410_GPIONO(S3C2410_GPIO_BANKG, 0)
DECL|macro|S3C2410_GPG0_INP
mdefine_line|#define S3C2410_GPG0_INP      (0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPG0_OUTP
mdefine_line|#define S3C2410_GPG0_OUTP     (0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPG0_EINT8
mdefine_line|#define S3C2410_GPG0_EINT8    (0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPG1
mdefine_line|#define S3C2410_GPG1          S3C2410_GPIONO(S3C2410_GPIO_BANKG, 1)
DECL|macro|S3C2410_GPG1_INP
mdefine_line|#define S3C2410_GPG1_INP      (0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPG1_OUTP
mdefine_line|#define S3C2410_GPG1_OUTP     (0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPG1_EINT9
mdefine_line|#define S3C2410_GPG1_EINT9    (0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPG2
mdefine_line|#define S3C2410_GPG2          S3C2410_GPIONO(S3C2410_GPIO_BANKG, 2)
DECL|macro|S3C2410_GPG2_INP
mdefine_line|#define S3C2410_GPG2_INP      (0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPG2_OUTP
mdefine_line|#define S3C2410_GPG2_OUTP     (0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPG2_EINT10
mdefine_line|#define S3C2410_GPG2_EINT10   (0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPG3
mdefine_line|#define S3C2410_GPG3          S3C2410_GPIONO(S3C2410_GPIO_BANKG, 3)
DECL|macro|S3C2410_GPG3_INP
mdefine_line|#define S3C2410_GPG3_INP      (0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPG3_OUTP
mdefine_line|#define S3C2410_GPG3_OUTP     (0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPG3_EINT11
mdefine_line|#define S3C2410_GPG3_EINT11   (0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPG4
mdefine_line|#define S3C2410_GPG4          S3C2410_GPIONO(S3C2410_GPIO_BANKG, 4)
DECL|macro|S3C2410_GPG4_INP
mdefine_line|#define S3C2410_GPG4_INP      (0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPG4_OUTP
mdefine_line|#define S3C2410_GPG4_OUTP     (0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPG4_EINT12
mdefine_line|#define S3C2410_GPG4_EINT12   (0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPG4_LCDPWREN
mdefine_line|#define S3C2410_GPG4_LCDPWREN (0x03 &lt;&lt; 8)
DECL|macro|S3C2410_GPG5
mdefine_line|#define S3C2410_GPG5          S3C2410_GPIONO(S3C2410_GPIO_BANKG, 5)
DECL|macro|S3C2410_GPG5_INP
mdefine_line|#define S3C2410_GPG5_INP      (0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPG5_OUTP
mdefine_line|#define S3C2410_GPG5_OUTP     (0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPG5_EINT13
mdefine_line|#define S3C2410_GPG5_EINT13   (0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPG5_SPIMISO1
mdefine_line|#define S3C2410_GPG5_SPIMISO1 (0x03 &lt;&lt; 10)
DECL|macro|S3C2410_GPG6
mdefine_line|#define S3C2410_GPG6          S3C2410_GPIONO(S3C2410_GPIO_BANKG, 6)
DECL|macro|S3C2410_GPG6_INP
mdefine_line|#define S3C2410_GPG6_INP      (0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPG6_OUTP
mdefine_line|#define S3C2410_GPG6_OUTP     (0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPG6_EINT14
mdefine_line|#define S3C2410_GPG6_EINT14   (0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPG6_SPIMOSI1
mdefine_line|#define S3C2410_GPG6_SPIMOSI1 (0x03 &lt;&lt; 12)
DECL|macro|S3C2410_GPG7
mdefine_line|#define S3C2410_GPG7          S3C2410_GPIONO(S3C2410_GPIO_BANKG, 7)
DECL|macro|S3C2410_GPG7_INP
mdefine_line|#define S3C2410_GPG7_INP      (0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPG7_OUTP
mdefine_line|#define S3C2410_GPG7_OUTP     (0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPG7_EINT15
mdefine_line|#define S3C2410_GPG7_EINT15   (0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPG7_SPICLK1
mdefine_line|#define S3C2410_GPG7_SPICLK1  (0x03 &lt;&lt; 14)
DECL|macro|S3C2410_GPG8
mdefine_line|#define S3C2410_GPG8          S3C2410_GPIONO(S3C2410_GPIO_BANKG, 8)
DECL|macro|S3C2410_GPG8_INP
mdefine_line|#define S3C2410_GPG8_INP      (0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPG8_OUTP
mdefine_line|#define S3C2410_GPG8_OUTP     (0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPG8_EINT16
mdefine_line|#define S3C2410_GPG8_EINT16   (0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPG9
mdefine_line|#define S3C2410_GPG9          S3C2410_GPIONO(S3C2410_GPIO_BANKG, 9)
DECL|macro|S3C2410_GPG9_INP
mdefine_line|#define S3C2410_GPG9_INP      (0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPG9_OUTP
mdefine_line|#define S3C2410_GPG9_OUTP     (0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPG9_EINT17
mdefine_line|#define S3C2410_GPG9_EINT17   (0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPG10
mdefine_line|#define S3C2410_GPG10         S3C2410_GPIONO(S3C2410_GPIO_BANKG, 10)
DECL|macro|S3C2410_GPG10_INP
mdefine_line|#define S3C2410_GPG10_INP     (0x00 &lt;&lt; 20)
DECL|macro|S3C2410_GPG10_OUTP
mdefine_line|#define S3C2410_GPG10_OUTP    (0x01 &lt;&lt; 20)
DECL|macro|S3C2410_GPG10_EINT18
mdefine_line|#define S3C2410_GPG10_EINT18  (0x02 &lt;&lt; 20)
DECL|macro|S3C2410_GPG11
mdefine_line|#define S3C2410_GPG11         S3C2410_GPIONO(S3C2410_GPIO_BANKG, 11)
DECL|macro|S3C2410_GPG11_INP
mdefine_line|#define S3C2410_GPG11_INP     (0x00 &lt;&lt; 22)
DECL|macro|S3C2410_GPG11_OUTP
mdefine_line|#define S3C2410_GPG11_OUTP    (0x01 &lt;&lt; 22)
DECL|macro|S3C2410_GPG11_EINT19
mdefine_line|#define S3C2410_GPG11_EINT19  (0x02 &lt;&lt; 22)
DECL|macro|S3C2410_GPG11_TCLK1
mdefine_line|#define S3C2410_GPG11_TCLK1   (0x03 &lt;&lt; 22)
DECL|macro|S3C2410_GPG12
mdefine_line|#define S3C2410_GPG12         S3C2410_GPIONO(S3C2410_GPIO_BANKG, 12)
DECL|macro|S3C2410_GPG12_INP
mdefine_line|#define S3C2410_GPG12_INP     (0x00 &lt;&lt; 24)
DECL|macro|S3C2410_GPG12_OUTP
mdefine_line|#define S3C2410_GPG12_OUTP    (0x01 &lt;&lt; 24)
DECL|macro|S3C2410_GPG12_EINT20
mdefine_line|#define S3C2410_GPG12_EINT20  (0x02 &lt;&lt; 24)
DECL|macro|S3C2410_GPG12_XMON
mdefine_line|#define S3C2410_GPG12_XMON    (0x03 &lt;&lt; 24)
DECL|macro|S3C2410_GPG13
mdefine_line|#define S3C2410_GPG13         S3C2410_GPIONO(S3C2410_GPIO_BANKG, 13)
DECL|macro|S3C2410_GPG13_INP
mdefine_line|#define S3C2410_GPG13_INP     (0x00 &lt;&lt; 26)
DECL|macro|S3C2410_GPG13_OUTP
mdefine_line|#define S3C2410_GPG13_OUTP    (0x01 &lt;&lt; 26)
DECL|macro|S3C2410_GPG13_EINT21
mdefine_line|#define S3C2410_GPG13_EINT21  (0x02 &lt;&lt; 26)
DECL|macro|S3C2410_GPG13_nXPON
mdefine_line|#define S3C2410_GPG13_nXPON   (0x03 &lt;&lt; 26)
DECL|macro|S3C2410_GPG14
mdefine_line|#define S3C2410_GPG14         S3C2410_GPIONO(S3C2410_GPIO_BANKG, 14)
DECL|macro|S3C2410_GPG14_INP
mdefine_line|#define S3C2410_GPG14_INP     (0x00 &lt;&lt; 28)
DECL|macro|S3C2410_GPG14_OUTP
mdefine_line|#define S3C2410_GPG14_OUTP    (0x01 &lt;&lt; 28)
DECL|macro|S3C2410_GPG14_EINT22
mdefine_line|#define S3C2410_GPG14_EINT22  (0x02 &lt;&lt; 28)
DECL|macro|S3C2410_GPG14_YMON
mdefine_line|#define S3C2410_GPG14_YMON    (0x03 &lt;&lt; 28)
DECL|macro|S3C2410_GPG15
mdefine_line|#define S3C2410_GPG15         S3C2410_GPIONO(S3C2410_GPIO_BANKG, 15)
DECL|macro|S3C2410_GPG15_INP
mdefine_line|#define S3C2410_GPG15_INP     (0x00 &lt;&lt; 30)
DECL|macro|S3C2410_GPG15_OUTP
mdefine_line|#define S3C2410_GPG15_OUTP    (0x01 &lt;&lt; 30)
DECL|macro|S3C2410_GPG15_EINT23
mdefine_line|#define S3C2410_GPG15_EINT23  (0x02 &lt;&lt; 30)
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
DECL|macro|S3C2410_GPH0
mdefine_line|#define S3C2410_GPH0        S3C2410_GPIONO(S3C2410_GPIO_BANKH, 0)
DECL|macro|S3C2410_GPH0_INP
mdefine_line|#define S3C2410_GPH0_INP    (0x00 &lt;&lt; 0)
DECL|macro|S3C2410_GPH0_OUTP
mdefine_line|#define S3C2410_GPH0_OUTP   (0x01 &lt;&lt; 0)
DECL|macro|S3C2410_GPH0_nCTS0
mdefine_line|#define S3C2410_GPH0_nCTS0  (0x02 &lt;&lt; 0)
DECL|macro|S3C2410_GPH1
mdefine_line|#define S3C2410_GPH1        S3C2410_GPIONO(S3C2410_GPIO_BANKH, 1)
DECL|macro|S3C2410_GPH1_INP
mdefine_line|#define S3C2410_GPH1_INP    (0x00 &lt;&lt; 2)
DECL|macro|S3C2410_GPH1_OUTP
mdefine_line|#define S3C2410_GPH1_OUTP   (0x01 &lt;&lt; 2)
DECL|macro|S3C2410_GPH1_nRTS0
mdefine_line|#define S3C2410_GPH1_nRTS0  (0x02 &lt;&lt; 2)
DECL|macro|S3C2410_GPH2
mdefine_line|#define S3C2410_GPH2        S3C2410_GPIONO(S3C2410_GPIO_BANKH, 2)
DECL|macro|S3C2410_GPH2_INP
mdefine_line|#define S3C2410_GPH2_INP    (0x00 &lt;&lt; 4)
DECL|macro|S3C2410_GPH2_OUTP
mdefine_line|#define S3C2410_GPH2_OUTP   (0x01 &lt;&lt; 4)
DECL|macro|S3C2410_GPH2_TXD0
mdefine_line|#define S3C2410_GPH2_TXD0   (0x02 &lt;&lt; 4)
DECL|macro|S3C2410_GPH3
mdefine_line|#define S3C2410_GPH3        S3C2410_GPIONO(S3C2410_GPIO_BANKH, 3)
DECL|macro|S3C2410_GPH3_INP
mdefine_line|#define S3C2410_GPH3_INP    (0x00 &lt;&lt; 6)
DECL|macro|S3C2410_GPH3_OUTP
mdefine_line|#define S3C2410_GPH3_OUTP   (0x01 &lt;&lt; 6)
DECL|macro|S3C2410_GPH3_RXD0
mdefine_line|#define S3C2410_GPH3_RXD0   (0x02 &lt;&lt; 6)
DECL|macro|S3C2410_GPH4
mdefine_line|#define S3C2410_GPH4        S3C2410_GPIONO(S3C2410_GPIO_BANKH, 4)
DECL|macro|S3C2410_GPH4_INP
mdefine_line|#define S3C2410_GPH4_INP    (0x00 &lt;&lt; 8)
DECL|macro|S3C2410_GPH4_OUTP
mdefine_line|#define S3C2410_GPH4_OUTP   (0x01 &lt;&lt; 8)
DECL|macro|S3C2410_GPH4_TXD1
mdefine_line|#define S3C2410_GPH4_TXD1   (0x02 &lt;&lt; 8)
DECL|macro|S3C2410_GPH5
mdefine_line|#define S3C2410_GPH5        S3C2410_GPIONO(S3C2410_GPIO_BANKH, 5)
DECL|macro|S3C2410_GPH5_INP
mdefine_line|#define S3C2410_GPH5_INP    (0x00 &lt;&lt; 10)
DECL|macro|S3C2410_GPH5_OUTP
mdefine_line|#define S3C2410_GPH5_OUTP   (0x01 &lt;&lt; 10)
DECL|macro|S3C2410_GPH5_RXD1
mdefine_line|#define S3C2410_GPH5_RXD1   (0x02 &lt;&lt; 10)
DECL|macro|S3C2410_GPH6
mdefine_line|#define S3C2410_GPH6        S3C2410_GPIONO(S3C2410_GPIO_BANKH, 6)
DECL|macro|S3C2410_GPH6_INP
mdefine_line|#define S3C2410_GPH6_INP    (0x00 &lt;&lt; 12)
DECL|macro|S3C2410_GPH6_OUTP
mdefine_line|#define S3C2410_GPH6_OUTP   (0x01 &lt;&lt; 12)
DECL|macro|S3C2410_GPH6_TXD2
mdefine_line|#define S3C2410_GPH6_TXD2   (0x02 &lt;&lt; 12)
DECL|macro|S3C2410_GPH6_nRTS1
mdefine_line|#define S3C2410_GPH6_nRTS1  (0x03 &lt;&lt; 12)
DECL|macro|S3C2410_GPH7
mdefine_line|#define S3C2410_GPH7        S3C2410_GPIONO(S3C2410_GPIO_BANKH, 7)
DECL|macro|S3C2410_GPH7_INP
mdefine_line|#define S3C2410_GPH7_INP    (0x00 &lt;&lt; 14)
DECL|macro|S3C2410_GPH7_OUTP
mdefine_line|#define S3C2410_GPH7_OUTP   (0x01 &lt;&lt; 14)
DECL|macro|S3C2410_GPH7_RXD2
mdefine_line|#define S3C2410_GPH7_RXD2   (0x02 &lt;&lt; 14)
DECL|macro|S3C2410_GPH7_nCTS1
mdefine_line|#define S3C2410_GPH7_nCTS1  (0x03 &lt;&lt; 14)
DECL|macro|S3C2410_GPH8
mdefine_line|#define S3C2410_GPH8        S3C2410_GPIONO(S3C2410_GPIO_BANKH, 8)
DECL|macro|S3C2410_GPH8_INP
mdefine_line|#define S3C2410_GPH8_INP    (0x00 &lt;&lt; 16)
DECL|macro|S3C2410_GPH8_OUTP
mdefine_line|#define S3C2410_GPH8_OUTP   (0x01 &lt;&lt; 16)
DECL|macro|S3C2410_GPH8_UCLK
mdefine_line|#define S3C2410_GPH8_UCLK   (0x02 &lt;&lt; 16)
DECL|macro|S3C2410_GPH9
mdefine_line|#define S3C2410_GPH9          S3C2410_GPIONO(S3C2410_GPIO_BANKH, 9)
DECL|macro|S3C2410_GPH9_INP
mdefine_line|#define S3C2410_GPH9_INP      (0x00 &lt;&lt; 18)
DECL|macro|S3C2410_GPH9_OUTP
mdefine_line|#define S3C2410_GPH9_OUTP     (0x01 &lt;&lt; 18)
DECL|macro|S3C2410_GPH9_CLKOUT0
mdefine_line|#define S3C2410_GPH9_CLKOUT0  (0x02 &lt;&lt; 18)
DECL|macro|S3C2410_GPH10
mdefine_line|#define S3C2410_GPH10         S3C2410_GPIONO(S3C2410_GPIO_BANKH, 10)
DECL|macro|S3C2410_GPH10_INP
mdefine_line|#define S3C2410_GPH10_INP     (0x00 &lt;&lt; 20)
DECL|macro|S3C2410_GPH10_OUTP
mdefine_line|#define S3C2410_GPH10_OUTP    (0x01 &lt;&lt; 20)
DECL|macro|S3C2410_GPH10_CLKOUT1
mdefine_line|#define S3C2410_GPH10_CLKOUT1 (0x02 &lt;&lt; 20)
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
DECL|macro|S3C2410_MISCCR_nEN_SCLK0
mdefine_line|#define S3C2410_MISCCR_nEN_SCLK0    (1&lt;&lt;17)
DECL|macro|S3C2410_MISCCR_nEN_SCLK1
mdefine_line|#define S3C2410_MISCCR_nEN_SCLK1    (1&lt;&lt;18)
DECL|macro|S3C2410_MISCCR_nEN_SCLKE
mdefine_line|#define S3C2410_MISCCR_nEN_SCLKE    (1&lt;&lt;19)
DECL|macro|S3C2410_MISCCR_SDSLEEP
mdefine_line|#define S3C2410_MISCCR_SDSLEEP&t;    (7&lt;&lt;17)
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
multiline_comment|/* values for interrupt filtering */
DECL|macro|S3C2410_EINTFLT_PCLK
mdefine_line|#define S3C2410_EINTFLT_PCLK&t;&t;(0x00)
DECL|macro|S3C2410_EINTFLT_EXTCLK
mdefine_line|#define S3C2410_EINTFLT_EXTCLK&t;&t;(1&lt;&lt;7)
DECL|macro|S3C2410_EINTFLT_WIDTHMSK
mdefine_line|#define S3C2410_EINTFLT_WIDTHMSK(x)&t;((x) &amp; 0x3f)
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
DECL|macro|S3C2410_GSTATUS1_IDMASK
mdefine_line|#define S3C2410_GSTATUS1_IDMASK&t;   (0xffff0000)
DECL|macro|S3C2410_GSTATUS1_2410
mdefine_line|#define S3C2410_GSTATUS1_2410&t;   (0x32410000)
DECL|macro|S3C2410_GSTATUS1_2440
mdefine_line|#define S3C2410_GSTATUS1_2440&t;   (0x32440000)
DECL|macro|S3C2410_GSTATUS2_WTRESET
mdefine_line|#define S3C2410_GSTATUS2_WTRESET   (1&lt;&lt;2)
DECL|macro|S3C2410_GSTATUS2_OFFRESET
mdefine_line|#define S3C2410_GSTATUS2_OFFRESET  (1&lt;&lt;1)
DECL|macro|S3C2410_GSTATUS2_PONRESET
mdefine_line|#define S3C2410_GSTATUS2_PONRESET  (1&lt;&lt;0)
macro_line|#endif&t;/* __ASM_ARCH_REGS_GPIO_H */
eof
