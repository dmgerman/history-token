multiline_comment|/* linux/include/asm-arm/arch-s3c2410/vr1000-map.h&n; *&n; * (c) 2003-2005 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Machine VR1000 - Memory map definitions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  06-Jan-2003 BJD  Linux 2.6.0 version, split specifics from arch/map.h&n; *  12-Mar-2004 BJD  Fixed header include protection&n; *  19-Mar-2004 BJD  Copied to VR1000 machine headers.&n; *  19-Jan-2005 BJD  Updated map definitions&n;*/
multiline_comment|/* needs arch/map.h including with this */
multiline_comment|/* ok, we&squot;ve used up to 0x13000000, now we need to find space for the&n; * peripherals that live in the nGCS[x] areas, which are quite numerous&n; * in their space. We also have the board&squot;s CPLD to find register space&n; * for.&n; */
macro_line|#ifndef __ASM_ARCH_VR1000MAP_H
DECL|macro|__ASM_ARCH_VR1000MAP_H
mdefine_line|#define __ASM_ARCH_VR1000MAP_H
macro_line|#include &lt;asm/arch/bast-map.h&gt;
DECL|macro|VR1000_IOADDR
mdefine_line|#define VR1000_IOADDR(x) BAST_IOADDR(x)
multiline_comment|/* we put the CPLD registers next, to get them out of the way */
DECL|macro|VR1000_VA_CTRL1
mdefine_line|#define VR1000_VA_CTRL1&t;    VR1000_IOADDR(0x00000000)&t; /* 0x01300000 */
DECL|macro|VR1000_PA_CTRL1
mdefine_line|#define VR1000_PA_CTRL1&t;    (S3C2410_CS5 | 0x7800000)
DECL|macro|VR1000_VA_CTRL2
mdefine_line|#define VR1000_VA_CTRL2&t;    VR1000_IOADDR(0x00100000)&t; /* 0x01400000 */
DECL|macro|VR1000_PA_CTRL2
mdefine_line|#define VR1000_PA_CTRL2&t;    (S3C2410_CS1 | 0x6000000)
DECL|macro|VR1000_VA_CTRL3
mdefine_line|#define VR1000_VA_CTRL3&t;    VR1000_IOADDR(0x00200000)&t; /* 0x01500000 */
DECL|macro|VR1000_PA_CTRL3
mdefine_line|#define VR1000_PA_CTRL3&t;    (S3C2410_CS1 | 0x6800000)
DECL|macro|VR1000_VA_CTRL4
mdefine_line|#define VR1000_VA_CTRL4&t;    VR1000_IOADDR(0x00300000)&t; /* 0x01600000 */
DECL|macro|VR1000_PA_CTRL4
mdefine_line|#define VR1000_PA_CTRL4&t;    (S3C2410_CS1 | 0x7000000)
multiline_comment|/* next, we have the PC104 ISA interrupt registers */
DECL|macro|VR1000_PA_PC104_IRQREQ
mdefine_line|#define VR1000_PA_PC104_IRQREQ  (S3C2410_CS5 | 0x6000000) /* 0x01700000 */
DECL|macro|VR1000_VA_PC104_IRQREQ
mdefine_line|#define VR1000_VA_PC104_IRQREQ  VR1000_IOADDR(0x00400000)
DECL|macro|VR1000_PA_PC104_IRQRAW
mdefine_line|#define VR1000_PA_PC104_IRQRAW  (S3C2410_CS5 | 0x6800000) /* 0x01800000 */
DECL|macro|VR1000_VA_PC104_IRQRAW
mdefine_line|#define VR1000_VA_PC104_IRQRAW  VR1000_IOADDR(0x00500000)
DECL|macro|VR1000_PA_PC104_IRQMASK
mdefine_line|#define VR1000_PA_PC104_IRQMASK (S3C2410_CS5 | 0x7000000) /* 0x01900000 */
DECL|macro|VR1000_VA_PC104_IRQMASK
mdefine_line|#define VR1000_VA_PC104_IRQMASK VR1000_IOADDR(0x00600000)
multiline_comment|/* 0xE0000000 contains the IO space that is split by speed and&n; * wether the access is for 8 or 16bit IO... this ensures that&n; * the correct access is made&n; *&n; * 0x10000000 of space, partitioned as so:&n; *&n; * 0x00000000 to 0x04000000  8bit,  slow&n; * 0x04000000 to 0x08000000  16bit, slow&n; * 0x08000000 to 0x0C000000  16bit, net&n; * 0x0C000000 to 0x10000000  16bit, fast&n; *&n; * each of these spaces has the following in:&n; *&n; * 0x02000000 to 0x02100000 1MB  IDE primary channel&n; * 0x02100000 to 0x02200000 1MB  IDE primary channel aux&n; * 0x02200000 to 0x02400000 1MB  IDE secondary channel&n; * 0x02300000 to 0x02400000 1MB  IDE secondary channel aux&n; * 0x02500000 to 0x02600000 1MB  Davicom DM9000 ethernet controllers&n; * 0x02600000 to 0x02700000 1MB&n; *&n; * the phyiscal layout of the zones are:&n; *  nGCS2 - 8bit, slow&n; *  nGCS3 - 16bit, slow&n; *  nGCS4 - 16bit, net&n; *  nGCS5 - 16bit, fast&n; */
DECL|macro|VR1000_VA_MULTISPACE
mdefine_line|#define VR1000_VA_MULTISPACE (0xE0000000)
DECL|macro|VR1000_VA_ISAIO
mdefine_line|#define VR1000_VA_ISAIO&t;&t;   (VR1000_VA_MULTISPACE + 0x00000000)
DECL|macro|VR1000_VA_ISAMEM
mdefine_line|#define VR1000_VA_ISAMEM&t;   (VR1000_VA_MULTISPACE + 0x01000000)
DECL|macro|VR1000_VA_IDEPRI
mdefine_line|#define VR1000_VA_IDEPRI&t;   (VR1000_VA_MULTISPACE + 0x02000000)
DECL|macro|VR1000_VA_IDEPRIAUX
mdefine_line|#define VR1000_VA_IDEPRIAUX&t;   (VR1000_VA_MULTISPACE + 0x02100000)
DECL|macro|VR1000_VA_IDESEC
mdefine_line|#define VR1000_VA_IDESEC&t;   (VR1000_VA_MULTISPACE + 0x02200000)
DECL|macro|VR1000_VA_IDESECAUX
mdefine_line|#define VR1000_VA_IDESECAUX&t;   (VR1000_VA_MULTISPACE + 0x02300000)
DECL|macro|VR1000_VA_ASIXNET
mdefine_line|#define VR1000_VA_ASIXNET&t;   (VR1000_VA_MULTISPACE + 0x02400000)
DECL|macro|VR1000_VA_DM9000
mdefine_line|#define VR1000_VA_DM9000&t;   (VR1000_VA_MULTISPACE + 0x02500000)
DECL|macro|VR1000_VA_SUPERIO
mdefine_line|#define VR1000_VA_SUPERIO&t;   (VR1000_VA_MULTISPACE + 0x02600000)
multiline_comment|/* physical offset addresses for the peripherals */
DECL|macro|VR1000_PA_IDEPRI
mdefine_line|#define VR1000_PA_IDEPRI&t;   (0x02000000)
DECL|macro|VR1000_PA_IDEPRIAUX
mdefine_line|#define VR1000_PA_IDEPRIAUX&t;   (0x02800000)
DECL|macro|VR1000_PA_IDESEC
mdefine_line|#define VR1000_PA_IDESEC&t;   (0x03000000)
DECL|macro|VR1000_PA_IDESECAUX
mdefine_line|#define VR1000_PA_IDESECAUX&t;   (0x03800000)
DECL|macro|VR1000_PA_DM9000
mdefine_line|#define VR1000_PA_DM9000&t;   (0x05000000)
DECL|macro|VR1000_PA_SERIAL
mdefine_line|#define VR1000_PA_SERIAL&t;   (0x11800000)
DECL|macro|VR1000_VA_SERIAL
mdefine_line|#define VR1000_VA_SERIAL&t;   (VR1000_IOADDR(0x00700000))
multiline_comment|/* VR1000 ram is in CS1, with A26..A24 = 2_101 */
DECL|macro|VR1000_PA_SRAM
mdefine_line|#define VR1000_PA_SRAM&t;&t;   (S3C2410_CS1 | 0x05000000)
multiline_comment|/* some configurations for the peripherals */
DECL|macro|VR1000_DM9000_CS
mdefine_line|#define VR1000_DM9000_CS&t; VR1000_VAM_CS4
macro_line|#endif /* __ASM_ARCH_VR1000MAP_H */
eof
