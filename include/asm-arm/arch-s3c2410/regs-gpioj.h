multiline_comment|/* linux/include/asm/hardware/s3c2410/regs-gpioj.h&n; *&n; * Copyright (c) 2004 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2440 GPIO J register definitions&n; *&n; *  Changelog:&n; *    11-Aug-2004     BJD     Created file&n; *    10-Feb-2005     BJD     Fix GPJ12 definition (Guillaume Gourat)&n;*/
macro_line|#ifndef __ASM_ARCH_REGS_GPIOJ_H
DECL|macro|__ASM_ARCH_REGS_GPIOJ_H
mdefine_line|#define __ASM_ARCH_REGS_GPIOJ_H &quot;gpioj&quot;
multiline_comment|/* Port J consists of 13 GPIO/Camera pins&n; *&n; * GPJCON has 2 bits for each of the input pins on port F&n; *   00 = 0 input, 1 output, 2 Camera&n; *&n; * pull up works like all other ports.&n;*/
DECL|macro|S3C2440_GPIO_BANKJ
mdefine_line|#define S3C2440_GPIO_BANKJ  (416)
DECL|macro|S3C2440_GPJCON
mdefine_line|#define S3C2440_GPJCON&t;    S3C2410_GPIOREG(0xd0)
DECL|macro|S3C2440_GPJDAT
mdefine_line|#define S3C2440_GPJDAT&t;    S3C2410_GPIOREG(0xd4)
DECL|macro|S3C2440_GPJUP
mdefine_line|#define S3C2440_GPJUP&t;    S3C2410_GPIOREG(0xd8)
DECL|macro|S3C2440_GPJ0
mdefine_line|#define S3C2440_GPJ0            S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 0)
DECL|macro|S3C2440_GPJ0_INP
mdefine_line|#define S3C2440_GPJ0_INP        (0x00 &lt;&lt; 0)
DECL|macro|S3C2440_GPJ0_OUTP
mdefine_line|#define S3C2440_GPJ0_OUTP       (0x01 &lt;&lt; 0)
DECL|macro|S3C2440_GPJ0_CAMDATA0
mdefine_line|#define S3C2440_GPJ0_CAMDATA0   (0x02 &lt;&lt; 0)
DECL|macro|S3C2440_GPJ1
mdefine_line|#define S3C2440_GPJ1            S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 1)
DECL|macro|S3C2440_GPJ1_INP
mdefine_line|#define S3C2440_GPJ1_INP        (0x00 &lt;&lt; 2)
DECL|macro|S3C2440_GPJ1_OUTP
mdefine_line|#define S3C2440_GPJ1_OUTP       (0x01 &lt;&lt; 2)
DECL|macro|S3C2440_GPJ1_CAMDATA1
mdefine_line|#define S3C2440_GPJ1_CAMDATA1   (0x02 &lt;&lt; 2)
DECL|macro|S3C2440_GPJ2
mdefine_line|#define S3C2440_GPJ2            S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 2)
DECL|macro|S3C2440_GPJ2_INP
mdefine_line|#define S3C2440_GPJ2_INP        (0x00 &lt;&lt; 4)
DECL|macro|S3C2440_GPJ2_OUTP
mdefine_line|#define S3C2440_GPJ2_OUTP       (0x01 &lt;&lt; 4)
DECL|macro|S3C2440_GPJ2_CAMDATA2
mdefine_line|#define S3C2440_GPJ2_CAMDATA2   (0x02 &lt;&lt; 4)
DECL|macro|S3C2440_GPJ3
mdefine_line|#define S3C2440_GPJ3            S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 3)
DECL|macro|S3C2440_GPJ3_INP
mdefine_line|#define S3C2440_GPJ3_INP        (0x00 &lt;&lt; 6)
DECL|macro|S3C2440_GPJ3_OUTP
mdefine_line|#define S3C2440_GPJ3_OUTP       (0x01 &lt;&lt; 6)
DECL|macro|S3C2440_GPJ3_CAMDATA3
mdefine_line|#define S3C2440_GPJ3_CAMDATA3   (0x02 &lt;&lt; 6)
DECL|macro|S3C2440_GPJ4
mdefine_line|#define S3C2440_GPJ4            S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 4)
DECL|macro|S3C2440_GPJ4_INP
mdefine_line|#define S3C2440_GPJ4_INP        (0x00 &lt;&lt; 8)
DECL|macro|S3C2440_GPJ4_OUTP
mdefine_line|#define S3C2440_GPJ4_OUTP       (0x01 &lt;&lt; 8)
DECL|macro|S3C2440_GPJ4_CAMDATA4
mdefine_line|#define S3C2440_GPJ4_CAMDATA4   (0x02 &lt;&lt; 8)
DECL|macro|S3C2440_GPJ5
mdefine_line|#define S3C2440_GPJ5            S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 5)
DECL|macro|S3C2440_GPJ5_INP
mdefine_line|#define S3C2440_GPJ5_INP        (0x00 &lt;&lt; 10)
DECL|macro|S3C2440_GPJ5_OUTP
mdefine_line|#define S3C2440_GPJ5_OUTP       (0x01 &lt;&lt; 10)
DECL|macro|S3C2440_GPJ5_CAMDATA5
mdefine_line|#define S3C2440_GPJ5_CAMDATA5   (0x02 &lt;&lt; 10)
DECL|macro|S3C2440_GPJ6
mdefine_line|#define S3C2440_GPJ6            S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 6)
DECL|macro|S3C2440_GPJ6_INP
mdefine_line|#define S3C2440_GPJ6_INP        (0x00 &lt;&lt; 12)
DECL|macro|S3C2440_GPJ6_OUTP
mdefine_line|#define S3C2440_GPJ6_OUTP       (0x01 &lt;&lt; 12)
DECL|macro|S3C2440_GPJ6_CAMDATA6
mdefine_line|#define S3C2440_GPJ6_CAMDATA6   (0x02 &lt;&lt; 12)
DECL|macro|S3C2440_GPJ7
mdefine_line|#define S3C2440_GPJ7            S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 7)
DECL|macro|S3C2440_GPJ7_INP
mdefine_line|#define S3C2440_GPJ7_INP        (0x00 &lt;&lt; 14)
DECL|macro|S3C2440_GPJ7_OUTP
mdefine_line|#define S3C2440_GPJ7_OUTP       (0x01 &lt;&lt; 14)
DECL|macro|S3C2440_GPJ7_CAMDATA7
mdefine_line|#define S3C2440_GPJ7_CAMDATA7   (0x02 &lt;&lt; 14)
DECL|macro|S3C2440_GPJ8
mdefine_line|#define S3C2440_GPJ8            S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 8)
DECL|macro|S3C2440_GPJ8_INP
mdefine_line|#define S3C2440_GPJ8_INP        (0x00 &lt;&lt; 16)
DECL|macro|S3C2440_GPJ8_OUTP
mdefine_line|#define S3C2440_GPJ8_OUTP       (0x01 &lt;&lt; 16)
DECL|macro|S3C2440_GPJ8_CAMPCLK
mdefine_line|#define S3C2440_GPJ8_CAMPCLK    (0x02 &lt;&lt; 16)
DECL|macro|S3C2440_GPJ9
mdefine_line|#define S3C2440_GPJ9            S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 9)
DECL|macro|S3C2440_GPJ9_INP
mdefine_line|#define S3C2440_GPJ9_INP        (0x00 &lt;&lt; 18)
DECL|macro|S3C2440_GPJ9_OUTP
mdefine_line|#define S3C2440_GPJ9_OUTP       (0x01 &lt;&lt; 18)
DECL|macro|S3C2440_GPJ9_CAMVSYNC
mdefine_line|#define S3C2440_GPJ9_CAMVSYNC   (0x02 &lt;&lt; 18)
DECL|macro|S3C2440_GPJ10
mdefine_line|#define S3C2440_GPJ10           S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 10)
DECL|macro|S3C2440_GPJ10_INP
mdefine_line|#define S3C2440_GPJ10_INP       (0x00 &lt;&lt; 20)
DECL|macro|S3C2440_GPJ10_OUTP
mdefine_line|#define S3C2440_GPJ10_OUTP      (0x01 &lt;&lt; 20)
DECL|macro|S3C2440_GPJ10_CAMHREF
mdefine_line|#define S3C2440_GPJ10_CAMHREF   (0x02 &lt;&lt; 20)
DECL|macro|S3C2440_GPJ11
mdefine_line|#define S3C2440_GPJ11           S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 11)
DECL|macro|S3C2440_GPJ11_INP
mdefine_line|#define S3C2440_GPJ11_INP       (0x00 &lt;&lt; 22)
DECL|macro|S3C2440_GPJ11_OUTP
mdefine_line|#define S3C2440_GPJ11_OUTP      (0x01 &lt;&lt; 22)
DECL|macro|S3C2440_GPJ11_CAMCLKOUT
mdefine_line|#define S3C2440_GPJ11_CAMCLKOUT (0x02 &lt;&lt; 22)
DECL|macro|S3C2440_GPJ12
mdefine_line|#define S3C2440_GPJ12           S3C2410_GPIONO(S3C2440_GPIO_BANKJ, 12)
DECL|macro|S3C2440_GPJ12_INP
mdefine_line|#define S3C2440_GPJ12_INP       (0x00 &lt;&lt; 24)
DECL|macro|S3C2440_GPJ12_OUTP
mdefine_line|#define S3C2440_GPJ12_OUTP      (0x01 &lt;&lt; 24)
DECL|macro|S3C2440_GPJ12_CAMRESET
mdefine_line|#define S3C2440_GPJ12_CAMRESET  (0x02 &lt;&lt; 24)
macro_line|#endif&t;/* __ASM_ARCH_REGS_GPIOJ_H */
eof
