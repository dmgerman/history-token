multiline_comment|/* linux/include/asm-arm/arch-s3c2410/bast-map.h&n; *&n; * (c) 2003,2004 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Machine BAST - Memory map definitions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  06-Jan-2003 BJD  Linux 2.6.0 version, moved bast specifics from arch/map.h&n; *  12-Mar-2004 BJD  Fixed header include protection&n;*/
multiline_comment|/* needs arch/map.h including with this */
multiline_comment|/* ok, we&squot;ve used up to 0x13000000, now we need to find space for the&n; * peripherals that live in the nGCS[x] areas, which are quite numerous&n; * in their space. We also have the board&squot;s CPLD to find register space&n; * for.&n; */
macro_line|#ifndef __ASM_ARCH_BASTMAP_H
DECL|macro|__ASM_ARCH_BASTMAP_H
mdefine_line|#define __ASM_ARCH_BASTMAP_H
DECL|macro|BAST_IOADDR
mdefine_line|#define BAST_IOADDR(x)&t;   (S3C2410_ADDR((x) + 0x01300000))
multiline_comment|/* we put the CPLD registers next, to get them out of the way */
DECL|macro|BAST_VA_CTRL1
mdefine_line|#define BAST_VA_CTRL1&t;    BAST_IOADDR(0x00000000)&t; /* 0x01300000 */
DECL|macro|BAST_PA_CTRL1
mdefine_line|#define BAST_PA_CTRL1&t;    (S3C2410_CS5 | 0x7800000)
DECL|macro|BAST_VA_CTRL2
mdefine_line|#define BAST_VA_CTRL2&t;    BAST_IOADDR(0x00100000)&t; /* 0x01400000 */
DECL|macro|BAST_PA_CTRL2
mdefine_line|#define BAST_PA_CTRL2&t;    (S3C2410_CS1 | 0x6000000)
DECL|macro|BAST_VA_CTRL3
mdefine_line|#define BAST_VA_CTRL3&t;    BAST_IOADDR(0x00200000)&t; /* 0x01500000 */
DECL|macro|BAST_PA_CTRL3
mdefine_line|#define BAST_PA_CTRL3&t;    (S3C2410_CS1 | 0x6800000)
DECL|macro|BAST_VA_CTRL4
mdefine_line|#define BAST_VA_CTRL4&t;    BAST_IOADDR(0x00300000)&t; /* 0x01600000 */
DECL|macro|BAST_PA_CTRL4
mdefine_line|#define BAST_PA_CTRL4&t;    (S3C2410_CS1 | 0x7000000)
multiline_comment|/* next, we have the PC104 ISA interrupt registers */
DECL|macro|BAST_PA_PC104_IRQREQ
mdefine_line|#define BAST_PA_PC104_IRQREQ  (S3C2410_CS5 | 0x6000000) /* 0x01700000 */
DECL|macro|BAST_VA_PC104_IRQREQ
mdefine_line|#define BAST_VA_PC104_IRQREQ  BAST_IOADDR(0x00400000)
DECL|macro|BAST_PA_PC104_IRQRAW
mdefine_line|#define BAST_PA_PC104_IRQRAW  (S3C2410_CS5 | 0x6800000) /* 0x01800000 */
DECL|macro|BAST_VA_PC104_IRQRAW
mdefine_line|#define BAST_VA_PC104_IRQRAW  BAST_IOADDR(0x00500000)
DECL|macro|BAST_PA_PC104_IRQMASK
mdefine_line|#define BAST_PA_PC104_IRQMASK (S3C2410_CS5 | 0x7000000) /* 0x01900000 */
DECL|macro|BAST_VA_PC104_IRQMASK
mdefine_line|#define BAST_VA_PC104_IRQMASK BAST_IOADDR(0x00600000)
DECL|macro|BAST_PA_LCD_RCMD1
mdefine_line|#define BAST_PA_LCD_RCMD1     (0x8800000)
DECL|macro|BAST_VA_LCD_RCMD1
mdefine_line|#define BAST_VA_LCD_RCMD1     BAST_IOADDR(0x00700000)
DECL|macro|BAST_PA_LCD_WCMD1
mdefine_line|#define BAST_PA_LCD_WCMD1     (0x8000000)
DECL|macro|BAST_VA_LCD_WCMD1
mdefine_line|#define BAST_VA_LCD_WCMD1     BAST_IOADDR(0x00800000)
DECL|macro|BAST_PA_LCD_RDATA1
mdefine_line|#define BAST_PA_LCD_RDATA1    (0x9800000)
DECL|macro|BAST_VA_LCD_RDATA1
mdefine_line|#define BAST_VA_LCD_RDATA1    BAST_IOADDR(0x00900000)
DECL|macro|BAST_PA_LCD_WDATA1
mdefine_line|#define BAST_PA_LCD_WDATA1    (0x9000000)
DECL|macro|BAST_VA_LCD_WDATA1
mdefine_line|#define BAST_VA_LCD_WDATA1    BAST_IOADDR(0x00A00000)
DECL|macro|BAST_PA_LCD_RCMD2
mdefine_line|#define BAST_PA_LCD_RCMD2     (0xA800000)
DECL|macro|BAST_VA_LCD_RCMD2
mdefine_line|#define BAST_VA_LCD_RCMD2     BAST_IOADDR(0x00B00000)
DECL|macro|BAST_PA_LCD_WCMD2
mdefine_line|#define BAST_PA_LCD_WCMD2     (0xA000000)
DECL|macro|BAST_VA_LCD_WCMD2
mdefine_line|#define BAST_VA_LCD_WCMD2     BAST_IOADDR(0x00C00000)
DECL|macro|BAST_PA_LCD_RDATA2
mdefine_line|#define BAST_PA_LCD_RDATA2    (0xB800000)
DECL|macro|BAST_VA_LCD_RDATA2
mdefine_line|#define BAST_VA_LCD_RDATA2    BAST_IOADDR(0x00D00000)
DECL|macro|BAST_PA_LCD_WDATA2
mdefine_line|#define BAST_PA_LCD_WDATA2    (0xB000000)
DECL|macro|BAST_VA_LCD_WDATA2
mdefine_line|#define BAST_VA_LCD_WDATA2    BAST_IOADDR(0x00E00000)
multiline_comment|/* 0xE0000000 contains the IO space that is split by speed and&n; * wether the access is for 8 or 16bit IO... this ensures that&n; * the correct access is made&n; *&n; * 0x10000000 of space, partitioned as so:&n; *&n; * 0x00000000 to 0x04000000  8bit,  slow&n; * 0x04000000 to 0x08000000  16bit, slow&n; * 0x08000000 to 0x0C000000  16bit, net&n; * 0x0C000000 to 0x10000000  16bit, fast&n; *&n; * each of these spaces has the following in:&n; *&n; * 0x00000000 to 0x01000000 16MB ISA IO space&n; * 0x01000000 to 0x02000000 16MB ISA memory space&n; * 0x02000000 to 0x02100000 1MB  IDE primary channel&n; * 0x02100000 to 0x02200000 1MB  IDE primary channel aux&n; * 0x02200000 to 0x02400000 1MB  IDE secondary channel&n; * 0x02300000 to 0x02400000 1MB  IDE secondary channel aux&n; * 0x02400000 to 0x02500000 1MB  ASIX ethernet controller&n; * 0x02500000 to 0x02600000 1MB  Davicom DM9000 ethernet controller&n; * 0x02600000 to 0x02700000 1MB  PC SuperIO controller&n; *&n; * the phyiscal layout of the zones are:&n; *  nGCS2 - 8bit, slow&n; *  nGCS3 - 16bit, slow&n; *  nGCS4 - 16bit, net&n; *  nGCS5 - 16bit, fast&n; */
DECL|macro|BAST_VA_MULTISPACE
mdefine_line|#define BAST_VA_MULTISPACE (0xE0000000)
DECL|macro|BAST_VA_ISAIO
mdefine_line|#define BAST_VA_ISAIO&t;   (BAST_VA_MULTISPACE + 0x00000000)
DECL|macro|BAST_VA_ISAMEM
mdefine_line|#define BAST_VA_ISAMEM&t;   (BAST_VA_MULTISPACE + 0x01000000)
DECL|macro|BAST_VA_IDEPRI
mdefine_line|#define BAST_VA_IDEPRI&t;   (BAST_VA_MULTISPACE + 0x02000000)
DECL|macro|BAST_VA_IDEPRIAUX
mdefine_line|#define BAST_VA_IDEPRIAUX  (BAST_VA_MULTISPACE + 0x02100000)
DECL|macro|BAST_VA_IDESEC
mdefine_line|#define BAST_VA_IDESEC&t;   (BAST_VA_MULTISPACE + 0x02200000)
DECL|macro|BAST_VA_IDESECAUX
mdefine_line|#define BAST_VA_IDESECAUX  (BAST_VA_MULTISPACE + 0x02300000)
DECL|macro|BAST_VA_ASIXNET
mdefine_line|#define BAST_VA_ASIXNET&t;   (BAST_VA_MULTISPACE + 0x02400000)
DECL|macro|BAST_VA_DM9000
mdefine_line|#define BAST_VA_DM9000&t;   (BAST_VA_MULTISPACE + 0x02500000)
DECL|macro|BAST_VA_SUPERIO
mdefine_line|#define BAST_VA_SUPERIO&t;   (BAST_VA_MULTISPACE + 0x02600000)
DECL|macro|BAST_VA_MULTISPACE
mdefine_line|#define BAST_VA_MULTISPACE (0xE0000000)
DECL|macro|BAST_VAM_CS2
mdefine_line|#define BAST_VAM_CS2 (0x00000000)
DECL|macro|BAST_VAM_CS3
mdefine_line|#define BAST_VAM_CS3 (0x04000000)
DECL|macro|BAST_VAM_CS4
mdefine_line|#define BAST_VAM_CS4 (0x08000000)
DECL|macro|BAST_VAM_CS5
mdefine_line|#define BAST_VAM_CS5 (0x0C000000)
multiline_comment|/* physical offset addresses for the peripherals */
DECL|macro|BAST_PA_ISAIO
mdefine_line|#define BAST_PA_ISAIO&t;  (0x00000000)
DECL|macro|BAST_PA_ASIXNET
mdefine_line|#define BAST_PA_ASIXNET&t;  (0x01000000)
DECL|macro|BAST_PA_SUPERIO
mdefine_line|#define BAST_PA_SUPERIO&t;  (0x01800000)
DECL|macro|BAST_PA_IDEPRI
mdefine_line|#define BAST_PA_IDEPRI&t;  (0x02000000)
DECL|macro|BAST_PA_IDEPRIAUX
mdefine_line|#define BAST_PA_IDEPRIAUX (0x02800000)
DECL|macro|BAST_PA_IDESEC
mdefine_line|#define BAST_PA_IDESEC&t;  (0x03000000)
DECL|macro|BAST_PA_IDESECAUX
mdefine_line|#define BAST_PA_IDESECAUX (0x03800000)
DECL|macro|BAST_PA_ISAMEM
mdefine_line|#define BAST_PA_ISAMEM&t;  (0x04000000)
DECL|macro|BAST_PA_DM9000
mdefine_line|#define BAST_PA_DM9000&t;  (0x05000000)
multiline_comment|/* some configurations for the peripherals */
DECL|macro|BAST_PCSIO
mdefine_line|#define BAST_PCSIO (BAST_VA_SUPERIO + BAST_VAM_CS2)
multiline_comment|/*  */
DECL|macro|BAST_ASIXNET_CS
mdefine_line|#define BAST_ASIXNET_CS  BAST_VAM_CS5
DECL|macro|BAST_IDE_CS
mdefine_line|#define BAST_IDE_CS&t; BAST_VAM_CS5
DECL|macro|BAST_DM9000_CS
mdefine_line|#define BAST_DM9000_CS&t; BAST_VAM_CS4
macro_line|#endif /* __ASM_ARCH_BASTMAP_H */
eof
