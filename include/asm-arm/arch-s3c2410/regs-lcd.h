multiline_comment|/* linux/include/asm/arch-s3c2410/regs-lcd.h&n; *&n; * Copyright (c) 2003 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *&n; *&n; *  Changelog:&n; *    12-06-2003     BJD     Created file&n; *    26-06-2003     BJD     Updated LCDCON register definitions&n; *    12-03-2004     BJD     Updated include protection&n;*/
macro_line|#ifndef ___ASM_ARCH_REGS_LCD_H
DECL|macro|___ASM_ARCH_REGS_LCD_H
mdefine_line|#define ___ASM_ARCH_REGS_LCD_H &quot;$Id: lcd.h,v 1.3 2003/06/26 13:25:06 ben Exp $&quot;
DECL|macro|S3C2410_LCDREG
mdefine_line|#define S3C2410_LCDREG(x) ((x) + S3C2410_VA_LCD)
multiline_comment|/* LCD control registers */
DECL|macro|S3C2410_LCDCON1
mdefine_line|#define S3C2410_LCDCON1&t;    S3C2410_LCDREG(0x00)
DECL|macro|S3C2410_LCDCON2
mdefine_line|#define S3C2410_LCDCON2&t;    S3C2410_LCDREG(0x04)
DECL|macro|S3C2410_LCDCON3
mdefine_line|#define S3C2410_LCDCON3&t;    S3C2410_LCDREG(0x08)
DECL|macro|S3C2410_LCDCON4
mdefine_line|#define S3C2410_LCDCON4&t;    S3C2410_LCDREG(0x0C)
DECL|macro|S3C2410_LCDCON5
mdefine_line|#define S3C2410_LCDCON5&t;    S3C2410_LCDREG(0x10)
DECL|macro|S3C2410_LCDCON1_CLKVAL
mdefine_line|#define S3C2410_LCDCON1_CLKVAL(x)  ((x) &lt;&lt; 8)
DECL|macro|S3C2410_LCDCON1_MMODE
mdefine_line|#define S3C2410_LCDCON1_MMODE&t;   (1&lt;&lt;7)
DECL|macro|S3C2410_LCDCON1_DSCAN4
mdefine_line|#define S3C2410_LCDCON1_DSCAN4&t;   (0&lt;&lt;5)
DECL|macro|S3C2410_LCDCON1_STN4
mdefine_line|#define S3C2410_LCDCON1_STN4&t;   (1&lt;&lt;5)
DECL|macro|S3C2410_LCDCON1_STN8
mdefine_line|#define S3C2410_LCDCON1_STN8&t;   (2&lt;&lt;5)
DECL|macro|S3C2410_LCDCON1_TFT
mdefine_line|#define S3C2410_LCDCON1_TFT&t;   (3&lt;&lt;5)
DECL|macro|S3C2410_LCDCON1_STN1BPP
mdefine_line|#define S3C2410_LCDCON1_STN1BPP&t;   (0&lt;&lt;1)
DECL|macro|S3C2410_LCDCON1_STN2GREY
mdefine_line|#define S3C2410_LCDCON1_STN2GREY   (1&lt;&lt;1)
DECL|macro|S3C2410_LCDCON1_STN4GREY
mdefine_line|#define S3C2410_LCDCON1_STN4GREY   (2&lt;&lt;1)
DECL|macro|S3C2410_LCDCON1_STN8BPP
mdefine_line|#define S3C2410_LCDCON1_STN8BPP&t;   (3&lt;&lt;1)
DECL|macro|S3C2410_LCDCON1_STN12BPP
mdefine_line|#define S3C2410_LCDCON1_STN12BPP   (4&lt;&lt;1)
DECL|macro|S3C2410_LCDCON1_TFT1BPP
mdefine_line|#define S3C2410_LCDCON1_TFT1BPP&t;   (8&lt;&lt;1)
DECL|macro|S3C2410_LCDCON1_TFT2BPP
mdefine_line|#define S3C2410_LCDCON1_TFT2BPP&t;   (9&lt;&lt;1)
DECL|macro|S3C2410_LCDCON1_TFT4BPP
mdefine_line|#define S3C2410_LCDCON1_TFT4BPP&t;   (10&lt;&lt;1)
DECL|macro|S3C2410_LCDCON1_TFT8BPP
mdefine_line|#define S3C2410_LCDCON1_TFT8BPP&t;   (11&lt;&lt;1)
DECL|macro|S3C2410_LCDCON1_TFT16BPP
mdefine_line|#define S3C2410_LCDCON1_TFT16BPP   (12&lt;&lt;1)
DECL|macro|S3C2410_LCDCON1_TFT24BPP
mdefine_line|#define S3C2410_LCDCON1_TFT24BPP   (13&lt;&lt;1)
DECL|macro|S3C2410_LCDCON1_ENVID
mdefine_line|#define S3C2410_LCDCON1_ENVID&t;   (1)
DECL|macro|S3C2410_LCDCON2_VBPD
mdefine_line|#define S3C2410_LCDCON2_VBPD(x)&t;    ((x) &lt;&lt; 24)
DECL|macro|S3C2410_LCDCON2_LINEVAL
mdefine_line|#define S3C2410_LCDCON2_LINEVAL(x)  ((x) &lt;&lt; 14)
DECL|macro|S3C2410_LCDCON2_VFPD
mdefine_line|#define S3C2410_LCDCON2_VFPD(x)&t;    ((x) &lt;&lt; 6)
DECL|macro|S3C2410_LCDCON2_VSPW
mdefine_line|#define S3C2410_LCDCON2_VSPW(x)&t;    ((x) &lt;&lt; 0)
DECL|macro|S3C2410_LCDCON3_HBPD
mdefine_line|#define S3C2410_LCDCON3_HBPD(x)&t;    ((x) &lt;&lt; 19)
DECL|macro|S3C2410_LCDCON3_WDLY
mdefine_line|#define S3C2410_LCDCON3_WDLY(x)&t;    ((x) &lt;&lt; 19)
DECL|macro|S3C2410_LCDCON3_HOZVAL
mdefine_line|#define S3C2410_LCDCON3_HOZVAL(x)   ((x) &lt;&lt; 8)
DECL|macro|S3C2410_LCDCON3_HFPD
mdefine_line|#define S3C2410_LCDCON3_HFPD(x)&t;    ((x) &lt;&lt; 0)
DECL|macro|S3C2410_LCDCON3_LINEBLANK
mdefine_line|#define S3C2410_LCDCON3_LINEBLANK(x)((x) &lt;&lt; 0)
DECL|macro|S3C2410_LCDCON4_MVAL
mdefine_line|#define S3C2410_LCDCON4_MVAL(x)&t;    ((x) &lt;&lt; 8)
DECL|macro|S3C2410_LCDCON4_HSPW
mdefine_line|#define S3C2410_LCDCON4_HSPW(x)&t;    ((x) &lt;&lt; 0)
DECL|macro|S3C2410_LCDCON4_WLH
mdefine_line|#define S3C2410_LCDCON4_WLH(x)&t;    ((x) &lt;&lt; 0)
DECL|macro|S3C2410_LCDCON5_BPP24BL
mdefine_line|#define S3C2410_LCDCON5_BPP24BL&t;    (1&lt;&lt;12)
DECL|macro|S3C2410_LCDCON5_FRM565
mdefine_line|#define S3C2410_LCDCON5_FRM565&t;    (1&lt;&lt;11)
DECL|macro|S3C2410_LCDCON5_INVVCLK
mdefine_line|#define S3C2410_LCDCON5_INVVCLK&t;    (1&lt;&lt;10)
DECL|macro|S3C2410_LCDCON5_INVVLINE
mdefine_line|#define S3C2410_LCDCON5_INVVLINE    (1&lt;&lt;9)
DECL|macro|S3C2410_LCDCON5_INVVFRAME
mdefine_line|#define S3C2410_LCDCON5_INVVFRAME   (1&lt;&lt;8)
DECL|macro|S3C2410_LCDCON5_INVVD
mdefine_line|#define S3C2410_LCDCON5_INVVD&t;    (1&lt;&lt;7)
DECL|macro|S3C2410_LCDCON5_INVVDEN
mdefine_line|#define S3C2410_LCDCON5_INVVDEN&t;    (1&lt;&lt;6)
DECL|macro|S3C2410_LCDCON5_INVPWREN
mdefine_line|#define S3C2410_LCDCON5_INVPWREN    (1&lt;&lt;5)
DECL|macro|S3C2410_LCDCON5_INVLEND
mdefine_line|#define S3C2410_LCDCON5_INVLEND&t;    (1&lt;&lt;4)
DECL|macro|S3C2410_LCDCON5_PWREN
mdefine_line|#define S3C2410_LCDCON5_PWREN&t;    (1&lt;&lt;3)
DECL|macro|S3C2410_LCDCON5_ENLEND
mdefine_line|#define S3C2410_LCDCON5_ENLEND&t;    (1&lt;&lt;2)
DECL|macro|S3C2410_LCDCON5_BSWP
mdefine_line|#define S3C2410_LCDCON5_BSWP&t;    (1&lt;&lt;1)
DECL|macro|S3C2410_LCDCON5_HWSWP
mdefine_line|#define S3C2410_LCDCON5_HWSWP&t;    (1&lt;&lt;0)
multiline_comment|/* framebuffer start addressed */
DECL|macro|S3C2410_LCDSADDR1
mdefine_line|#define S3C2410_LCDSADDR1   S3C2410_LCDREG(0x14)
DECL|macro|S3C2410_LCDSADDR2
mdefine_line|#define S3C2410_LCDSADDR2   S3C2410_LCDREG(0x18)
DECL|macro|S3C2410_LCDSADDR3
mdefine_line|#define S3C2410_LCDSADDR3   S3C2410_LCDREG(0x1C)
DECL|macro|S3C2410_LCDBANK
mdefine_line|#define S3C2410_LCDBANK(x)&t;((x) &lt;&lt; 21)
DECL|macro|S3C2410_LCDBASEU
mdefine_line|#define S3C2410_LCDBASEU(x)&t;(x)
DECL|macro|S3C2410_OFFSIZE
mdefine_line|#define S3C2410_OFFSIZE(x)&t;((x) &lt;&lt; 11)
DECL|macro|S3C2410_PAGEWIDTH
mdefine_line|#define S3C2410_PAGEWIDTH(x)&t;(x)
multiline_comment|/* colour lookup and miscellaneous controls */
DECL|macro|S3C2410_REDLUT
mdefine_line|#define S3C2410_REDLUT&t;   S3C2410_LCDREG(0x20)
DECL|macro|S3C2410_GREENLUT
mdefine_line|#define S3C2410_GREENLUT   S3C2410_LCDREG(0x24)
DECL|macro|S3C2410_BLUELUT
mdefine_line|#define S3C2410_BLUELUT&t;   S3C2410_LCDREG(0x28)
DECL|macro|S3C2410_DITHMODE
mdefine_line|#define S3C2410_DITHMODE   S3C2410_LCDREG(0x4C)
DECL|macro|S3C2410_TPAL
mdefine_line|#define S3C2410_TPAL&t;   S3C2410_LCDREG(0x50)
multiline_comment|/* interrupt info */
DECL|macro|S3C2410_LCDINTPND
mdefine_line|#define S3C2410_LCDINTPND  S3C2410_LCDREG(0x54)
DECL|macro|S3C2410_LCDSRCPND
mdefine_line|#define S3C2410_LCDSRCPND  S3C2410_LCDREG(0x58)
DECL|macro|S3C2410_LCDINTMSK
mdefine_line|#define S3C2410_LCDINTMSK  S3C2410_LCDREG(0x5C)
DECL|macro|S3C2410_LPCSEL
mdefine_line|#define S3C2410_LPCSEL&t;   S3C2410_LCDREG(0x60)
DECL|macro|S3C2410_TFTPAL
mdefine_line|#define S3C2410_TFTPAL(x)  S3C2410_LCDREG((0x400 + (x)*4))
macro_line|#endif /* ___ASM_ARCH_REGS_LCD_H */
eof
