multiline_comment|/* linux/include/asm-arm/arch-s3c2410/regs-spi.h&n; *&n; * Copyright (c) 2004 Fetron GmbH&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 SPI register definition&n; *&n; *  Changelog:&n; *    20-04-2004     KF      Created file&n; *    04-10-2004     BJD     Removed VA address (no longer mapped)&n; *&t;&t;&t;     tidied file for submission&n; */
macro_line|#ifndef __ASM_ARCH_REGS_SPI_H
DECL|macro|__ASM_ARCH_REGS_SPI_H
mdefine_line|#define __ASM_ARCH_REGS_SPI_H
DECL|macro|S3C2410_SPCON
mdefine_line|#define S3C2410_SPCON&t;(0x00)
DECL|macro|S3C2410_SPCON_SMOD_DMA
mdefine_line|#define S3C2410_SPCON_SMOD_DMA&t;  (2&lt;&lt;5)&t;/* DMA mode */
DECL|macro|S3C2410_SPCON_SMOD_INT
mdefine_line|#define S3C2410_SPCON_SMOD_INT&t;  (1&lt;&lt;5)&t;/* interrupt mode */
DECL|macro|S3C2410_SPCON_SMOD_POLL
mdefine_line|#define S3C2410_SPCON_SMOD_POLL   (0&lt;&lt;5)&t;/* polling mode */
DECL|macro|S3C2410_SPCON_ENSCK
mdefine_line|#define S3C2410_SPCON_ENSCK&t;  (1&lt;&lt;4)&t;/* Enable SCK */
DECL|macro|S3C2410_SPCON_MSTR
mdefine_line|#define S3C2410_SPCON_MSTR&t;  (1&lt;&lt;3)&t;/* Master/Slave select&n;&t;&t;&t;&t;&t;&t;   0: slave, 1: master */
DECL|macro|S3C2410_SPCON_CPOL_HIGH
mdefine_line|#define S3C2410_SPCON_CPOL_HIGH&t;  (1&lt;&lt;2)&t;/* Clock polarity select */
DECL|macro|S3C2410_SPCON_CPOL_LOW
mdefine_line|#define S3C2410_SPCON_CPOL_LOW&t;  (0&lt;&lt;2)&t;/* Clock polarity select */
DECL|macro|S3C2410_SPCON_CPHA_FMTB
mdefine_line|#define S3C2410_SPCON_CPHA_FMTB&t;  (1&lt;&lt;1)&t;/* Clock Phase Select */
DECL|macro|S3C2410_SPCON_CPHA_FMTA
mdefine_line|#define S3C2410_SPCON_CPHA_FMTA&t;  (0&lt;&lt;1)&t;/* Clock Phase Select */
DECL|macro|S3C2410_SPCON_TAGD
mdefine_line|#define S3C2410_SPCON_TAGD&t;  (1&lt;&lt;0)&t;/* Tx auto garbage data mode */
DECL|macro|S3C2410_SPSTA
mdefine_line|#define S3C2410_SPSTA&t; (0x04)
DECL|macro|S3C2410_SPSTA_DCOL
mdefine_line|#define S3C2410_SPSTA_DCOL&t;  (1&lt;&lt;2)&t;/* Data Collision Error */
DECL|macro|S3C2410_SPSTA_MULD
mdefine_line|#define S3C2410_SPSTA_MULD&t;  (1&lt;&lt;1)&t;/* Multi Master Error */
DECL|macro|S3C2410_SPSTA_READY
mdefine_line|#define S3C2410_SPSTA_READY&t;  (1&lt;&lt;0)&t;/* Data Tx/Rx ready */
DECL|macro|S3C2410_SPPIN
mdefine_line|#define S3C2410_SPPIN&t; (0x08)
DECL|macro|S3C2410_SPPIN_ENMUL
mdefine_line|#define S3C2410_SPPIN_ENMUL&t;  (1&lt;&lt;2)&t;/* Multi Master Error detect */
DECL|macro|S3C2410_SPPIN_RESERVED
mdefine_line|#define S3C2410_SPPIN_RESERVED&t;  (1&lt;&lt;1)
DECL|macro|S3C2410_SPPIN_KEEP
mdefine_line|#define S3C2410_SPPIN_KEEP&t;  (1&lt;&lt;0)&t;/* Master Out keep */
DECL|macro|S3C2410_SPPRE
mdefine_line|#define S3C2410_SPPRE&t; (0x0C)
DECL|macro|S3C2410_SPTDAT
mdefine_line|#define S3C2410_SPTDAT&t; (0x10)
DECL|macro|S3C2410_SPRDAT
mdefine_line|#define S3C2410_SPRDAT&t; (0x14)
macro_line|#endif /* __ASM_ARCH_REGS_SPI_H */
eof
