multiline_comment|/* linux/include/asm/arch-s3c2410/regs-clock.h&n; *&n; * Copyright (c) 2003,2004 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 clock register definitions&n; *&n; *  Changelog:&n; *    18-Aug-2004 Ben Dooks      Added 2440 definitions&n; *    08-Aug-2004 Herbert P&#xfffd;tzl  Added CLKCON definitions&n; *    19-06-2003  Ben Dooks      Created file&n; *    12-03-2004  Ben Dooks      Updated include protection&n; *    29-Sep-2004 Ben Dooks&t; Fixed usage for assembly inclusion&n; *    10-Feb-2005 Ben Dooks&t; Fixed CAMDIVN address (Guillaume Gourat)&n; */
macro_line|#ifndef __ASM_ARM_REGS_CLOCK
DECL|macro|__ASM_ARM_REGS_CLOCK
mdefine_line|#define __ASM_ARM_REGS_CLOCK &quot;$Id: clock.h,v 1.4 2003/04/30 14:50:51 ben Exp $&quot;
DECL|macro|S3C2410_CLKREG
mdefine_line|#define S3C2410_CLKREG(x) ((x) + S3C2410_VA_CLKPWR)
DECL|macro|S3C2410_PLLVAL
mdefine_line|#define S3C2410_PLLVAL(_m,_p,_s) ((_m) &lt;&lt; 12 | ((_p) &lt;&lt; 4) | ((_s)))
DECL|macro|S3C2410_LOCKTIME
mdefine_line|#define S3C2410_LOCKTIME    S3C2410_CLKREG(0x00)
DECL|macro|S3C2410_MPLLCON
mdefine_line|#define S3C2410_MPLLCON&t;    S3C2410_CLKREG(0x04)
DECL|macro|S3C2410_UPLLCON
mdefine_line|#define S3C2410_UPLLCON&t;    S3C2410_CLKREG(0x08)
DECL|macro|S3C2410_CLKCON
mdefine_line|#define S3C2410_CLKCON&t;    S3C2410_CLKREG(0x0C)
DECL|macro|S3C2410_CLKSLOW
mdefine_line|#define S3C2410_CLKSLOW&t;    S3C2410_CLKREG(0x10)
DECL|macro|S3C2410_CLKDIVN
mdefine_line|#define S3C2410_CLKDIVN&t;    S3C2410_CLKREG(0x14)
DECL|macro|S3C2410_CLKCON_IDLE
mdefine_line|#define S3C2410_CLKCON_IDLE&t;     (1&lt;&lt;2)
DECL|macro|S3C2410_CLKCON_POWER
mdefine_line|#define S3C2410_CLKCON_POWER&t;     (1&lt;&lt;3)
DECL|macro|S3C2410_CLKCON_NAND
mdefine_line|#define S3C2410_CLKCON_NAND&t;     (1&lt;&lt;4)
DECL|macro|S3C2410_CLKCON_LCDC
mdefine_line|#define S3C2410_CLKCON_LCDC&t;     (1&lt;&lt;5)
DECL|macro|S3C2410_CLKCON_USBH
mdefine_line|#define S3C2410_CLKCON_USBH&t;     (1&lt;&lt;6)
DECL|macro|S3C2410_CLKCON_USBD
mdefine_line|#define S3C2410_CLKCON_USBD&t;     (1&lt;&lt;7)
DECL|macro|S3C2410_CLKCON_PWMT
mdefine_line|#define S3C2410_CLKCON_PWMT&t;     (1&lt;&lt;8)
DECL|macro|S3C2410_CLKCON_SDI
mdefine_line|#define S3C2410_CLKCON_SDI&t;     (1&lt;&lt;9)
DECL|macro|S3C2410_CLKCON_UART0
mdefine_line|#define S3C2410_CLKCON_UART0&t;     (1&lt;&lt;10)
DECL|macro|S3C2410_CLKCON_UART1
mdefine_line|#define S3C2410_CLKCON_UART1&t;     (1&lt;&lt;11)
DECL|macro|S3C2410_CLKCON_UART2
mdefine_line|#define S3C2410_CLKCON_UART2&t;     (1&lt;&lt;12)
DECL|macro|S3C2410_CLKCON_GPIO
mdefine_line|#define S3C2410_CLKCON_GPIO&t;     (1&lt;&lt;13)
DECL|macro|S3C2410_CLKCON_RTC
mdefine_line|#define S3C2410_CLKCON_RTC&t;     (1&lt;&lt;14)
DECL|macro|S3C2410_CLKCON_ADC
mdefine_line|#define S3C2410_CLKCON_ADC&t;     (1&lt;&lt;15)
DECL|macro|S3C2410_CLKCON_IIC
mdefine_line|#define S3C2410_CLKCON_IIC&t;     (1&lt;&lt;16)
DECL|macro|S3C2410_CLKCON_IIS
mdefine_line|#define S3C2410_CLKCON_IIS&t;     (1&lt;&lt;17)
DECL|macro|S3C2410_CLKCON_SPI
mdefine_line|#define S3C2410_CLKCON_SPI&t;     (1&lt;&lt;18)
DECL|macro|S3C2410_PLLCON_MDIVSHIFT
mdefine_line|#define S3C2410_PLLCON_MDIVSHIFT     12
DECL|macro|S3C2410_PLLCON_PDIVSHIFT
mdefine_line|#define S3C2410_PLLCON_PDIVSHIFT     4
DECL|macro|S3C2410_PLLCON_SDIVSHIFT
mdefine_line|#define S3C2410_PLLCON_SDIVSHIFT     0
DECL|macro|S3C2410_PLLCON_MDIVMASK
mdefine_line|#define S3C2410_PLLCON_MDIVMASK&t;     ((1&lt;&lt;(1+(19-12)))-1)
DECL|macro|S3C2410_PLLCON_PDIVMASK
mdefine_line|#define S3C2410_PLLCON_PDIVMASK&t;     ((1&lt;&lt;5)-1)
DECL|macro|S3C2410_PLLCON_SDIVMASK
mdefine_line|#define S3C2410_PLLCON_SDIVMASK&t;     3
multiline_comment|/* DCLKCON register addresses in gpio.h */
DECL|macro|S3C2410_DCLKCON_DCLK0EN
mdefine_line|#define S3C2410_DCLKCON_DCLK0EN&t;     (1&lt;&lt;0)
DECL|macro|S3C2410_DCLKCON_DCLK0_PCLK
mdefine_line|#define S3C2410_DCLKCON_DCLK0_PCLK   (0&lt;&lt;1)
DECL|macro|S3C2410_DCLKCON_DCLK0_UCLK
mdefine_line|#define S3C2410_DCLKCON_DCLK0_UCLK   (1&lt;&lt;1)
DECL|macro|S3C2410_DCLKCON_DCLK0_DIV
mdefine_line|#define S3C2410_DCLKCON_DCLK0_DIV(x) (((x) - 1 )&lt;&lt;4)
DECL|macro|S3C2410_DCLKCON_DCLK0_CMP
mdefine_line|#define S3C2410_DCLKCON_DCLK0_CMP(x) (((x) - 1 )&lt;&lt;8)
DECL|macro|S3C2410_DCLKCON_DCLK1EN
mdefine_line|#define S3C2410_DCLKCON_DCLK1EN&t;     (1&lt;&lt;16)
DECL|macro|S3C2410_DCLKCON_DCLK1_PCLK
mdefine_line|#define S3C2410_DCLKCON_DCLK1_PCLK   (0&lt;&lt;17)
DECL|macro|S3C2410_DCLKCON_DCLK1_UCLK
mdefine_line|#define S3C2410_DCLKCON_DCLK1_UCLK   (1&lt;&lt;17)
DECL|macro|S3C2410_DCLKCON_DCLK1_DIV
mdefine_line|#define S3C2410_DCLKCON_DCLK1_DIV(x) (((x) - 1) &lt;&lt;20)
DECL|macro|S3C2410_CLKDIVN_PDIVN
mdefine_line|#define S3C2410_CLKDIVN_PDIVN&t;     (1&lt;&lt;0)
DECL|macro|S3C2410_CLKDIVN_HDIVN
mdefine_line|#define S3C2410_CLKDIVN_HDIVN&t;     (1&lt;&lt;1)
macro_line|#ifndef __ASSEMBLY__
r_static
r_inline
r_int
r_int
DECL|function|s3c2410_get_pll
id|s3c2410_get_pll
c_func
(paren
r_int
id|pllval
comma
r_int
id|baseclk
)paren
(brace
r_int
id|mdiv
comma
id|pdiv
comma
id|sdiv
suffix:semicolon
id|mdiv
op_assign
id|pllval
op_rshift
id|S3C2410_PLLCON_MDIVSHIFT
suffix:semicolon
id|pdiv
op_assign
id|pllval
op_rshift
id|S3C2410_PLLCON_PDIVSHIFT
suffix:semicolon
id|sdiv
op_assign
id|pllval
op_rshift
id|S3C2410_PLLCON_SDIVSHIFT
suffix:semicolon
id|mdiv
op_and_assign
id|S3C2410_PLLCON_MDIVMASK
suffix:semicolon
id|pdiv
op_and_assign
id|S3C2410_PLLCON_PDIVMASK
suffix:semicolon
id|sdiv
op_and_assign
id|S3C2410_PLLCON_SDIVMASK
suffix:semicolon
r_return
(paren
id|baseclk
op_star
(paren
id|mdiv
op_plus
l_int|8
)paren
)paren
op_div
(paren
(paren
id|pdiv
op_plus
l_int|2
)paren
op_lshift
id|sdiv
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#ifdef CONFIG_CPU_S3C2440
multiline_comment|/* extra registers */
DECL|macro|S3C2440_CAMDIVN
mdefine_line|#define S3C2440_CAMDIVN&t;    S3C2410_CLKREG(0x18)
DECL|macro|S3C2440_CLKCON_CAMERA
mdefine_line|#define S3C2440_CLKCON_CAMERA        (1&lt;&lt;19)
DECL|macro|S3C2440_CLKCON_AC97
mdefine_line|#define S3C2440_CLKCON_AC97          (1&lt;&lt;20)
DECL|macro|S3C2440_CLKDIVN_PDIVN
mdefine_line|#define S3C2440_CLKDIVN_PDIVN&t;     (1&lt;&lt;0)
DECL|macro|S3C2440_CLKDIVN_HDIVN_MASK
mdefine_line|#define S3C2440_CLKDIVN_HDIVN_MASK   (3&lt;&lt;1)
DECL|macro|S3C2440_CLKDIVN_HDIVN_1
mdefine_line|#define S3C2440_CLKDIVN_HDIVN_1      (0&lt;&lt;1)
DECL|macro|S3C2440_CLKDIVN_HDIVN_2
mdefine_line|#define S3C2440_CLKDIVN_HDIVN_2      (1&lt;&lt;1)
DECL|macro|S3C2440_CLKDIVN_HDIVN_4_8
mdefine_line|#define S3C2440_CLKDIVN_HDIVN_4_8    (2&lt;&lt;1)
DECL|macro|S3C2440_CLKDIVN_HDIVN_3_6
mdefine_line|#define S3C2440_CLKDIVN_HDIVN_3_6    (3&lt;&lt;1)
DECL|macro|S3C2440_CLKDIVN_UCLK
mdefine_line|#define S3C2440_CLKDIVN_UCLK         (1&lt;&lt;3)
DECL|macro|S3C2440_CAMDIVN_CAMCLK_MASK
mdefine_line|#define S3C2440_CAMDIVN_CAMCLK_MASK  (0xf&lt;&lt;0)
DECL|macro|S3C2440_CAMDIVN_CAMCLK_SEL
mdefine_line|#define S3C2440_CAMDIVN_CAMCLK_SEL   (1&lt;&lt;4)
DECL|macro|S3C2440_CAMDIVN_HCLK3_HALF
mdefine_line|#define S3C2440_CAMDIVN_HCLK3_HALF   (1&lt;&lt;8)
DECL|macro|S3C2440_CAMDIVN_HCLK4_HALF
mdefine_line|#define S3C2440_CAMDIVN_HCLK4_HALF   (1&lt;&lt;9)
DECL|macro|S3C2440_CAMDIVN_DVSEN
mdefine_line|#define S3C2440_CAMDIVN_DVSEN        (1&lt;&lt;12)
macro_line|#endif /* CONFIG_CPU_S3C2440 */
macro_line|#endif /* __ASM_ARM_REGS_CLOCK */
eof
