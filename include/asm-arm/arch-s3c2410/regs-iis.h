multiline_comment|/* linux/include/asm/arch-s3c2410/regs-iis.h&n; *&n; * Copyright (c) 2003 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 IIS register definition&n; *&n; *  Changelog:&n; *    19-06-2003     BJD     Created file&n; *    26-06-2003     BJD     Finished off definitions for register addresses&n; *    12-03-2004     BJD     Updated include protection&n; */
macro_line|#ifndef __ASM_ARCH_REGS_IIS_H
DECL|macro|__ASM_ARCH_REGS_IIS_H
mdefine_line|#define __ASM_ARCH_REGS_IIS_H
DECL|macro|S3C2410_IISCON
mdefine_line|#define S3C2410_IISCON&t; (0x00)
DECL|macro|S3C2410_IISCON_LRINDEX
mdefine_line|#define S3C2410_IISCON_LRINDEX&t;  (1&lt;&lt;8)
DECL|macro|S3C2410_IISCON_TXFIFORDY
mdefine_line|#define S3C2410_IISCON_TXFIFORDY  (1&lt;&lt;7)
DECL|macro|S3C2410_IISCON_RXFIFORDY
mdefine_line|#define S3C2410_IISCON_RXFIFORDY  (1&lt;&lt;6)
DECL|macro|S3C2410_IISCON_TXDMAEN
mdefine_line|#define S3C2410_IISCON_TXDMAEN&t;  (1&lt;&lt;5)
DECL|macro|S3C2410_IISCON_RXDMAEN
mdefine_line|#define S3C2410_IISCON_RXDMAEN&t;  (1&lt;&lt;4)
DECL|macro|S3C2410_IISCON_TXIDLE
mdefine_line|#define S3C2410_IISCON_TXIDLE&t;  (1&lt;&lt;3)
DECL|macro|S3C2410_IISCON_RXIDLE
mdefine_line|#define S3C2410_IISCON_RXIDLE&t;  (1&lt;&lt;2)
DECL|macro|S3C2410_IISCON_IISEN
mdefine_line|#define S3C2410_IISCON_IISEN&t;  (1&lt;&lt;0)
DECL|macro|S3C2410_IISMOD
mdefine_line|#define S3C2410_IISMOD&t; (0x04)
DECL|macro|S3C2410_IISMOD_SLAVE
mdefine_line|#define S3C2410_IISMOD_SLAVE&t;  (1&lt;&lt;8)
DECL|macro|S3C2410_IISMOD_NOXFER
mdefine_line|#define S3C2410_IISMOD_NOXFER&t;  (0&lt;&lt;6)
DECL|macro|S3C2410_IISMOD_RXMODE
mdefine_line|#define S3C2410_IISMOD_RXMODE&t;  (1&lt;&lt;6)
DECL|macro|S3C2410_IISMOD_TXMODE
mdefine_line|#define S3C2410_IISMOD_TXMODE&t;  (2&lt;&lt;6)
DECL|macro|S3C2410_IISMOD_TXRXMODE
mdefine_line|#define S3C2410_IISMOD_TXRXMODE&t;  (3&lt;&lt;6)
DECL|macro|S3C2410_IISMOD_LR_LLOW
mdefine_line|#define S3C2410_IISMOD_LR_LLOW&t;  (0&lt;&lt;5)
DECL|macro|S3C2410_IISMOD_LR_RLOW
mdefine_line|#define S3C2410_IISMOD_LR_RLOW&t;  (1&lt;&lt;5)
DECL|macro|S3C2410_IISMOD_IIS
mdefine_line|#define S3C2410_IISMOD_IIS&t;  (0&lt;&lt;4)
DECL|macro|S3C2410_IISMOD_MSB
mdefine_line|#define S3C2410_IISMOD_MSB&t;  (1&lt;&lt;4)
DECL|macro|S3C2410_IISMOD_8BIT
mdefine_line|#define S3C2410_IISMOD_8BIT&t;  (0&lt;&lt;3)
DECL|macro|S3C2410_IISMOD_16BIT
mdefine_line|#define S3C2410_IISMOD_16BIT&t;  (1&lt;&lt;3)
DECL|macro|S3C2410_IISMOD_256FS
mdefine_line|#define S3C2410_IISMOD_256FS&t;  (0&lt;&lt;1)
DECL|macro|S3C2410_IISMOD_384FS
mdefine_line|#define S3C2410_IISMOD_384FS&t;  (1&lt;&lt;1)
DECL|macro|S3C2410_IISMOD_16FS
mdefine_line|#define S3C2410_IISMOD_16FS&t;  (0&lt;&lt;0)
DECL|macro|S3C2410_IISMOD_32FS
mdefine_line|#define S3C2410_IISMOD_32FS&t;  (1&lt;&lt;0)
DECL|macro|S3C2410_IISMOD_48FS
mdefine_line|#define S3C2410_IISMOD_48FS&t;  (2&lt;&lt;0)
DECL|macro|S3C2410_IISPSR
mdefine_line|#define S3C2410_IISPSR&t;&t;(0x08)
DECL|macro|S3C2410_IISPSR_INTMASK
mdefine_line|#define S3C2410_IISPSR_INTMASK&t;(31&lt;&lt;5)
DECL|macro|S3C2410_IISPSR_INTSHFIT
mdefine_line|#define S3C2410_IISPSR_INTSHFIT&t;(5)
DECL|macro|S3C2410_IISPSR_EXTMASK
mdefine_line|#define S3C2410_IISPSR_EXTMASK&t;(31&lt;&lt;0)
DECL|macro|S3C2410_IISPSR_EXTSHFIT
mdefine_line|#define S3C2410_IISPSR_EXTSHFIT&t;(0)
DECL|macro|S3C2410_IISFCON
mdefine_line|#define S3C2410_IISFCON  (0x0c)
DECL|macro|S3C2410_IISFCON_TXDMA
mdefine_line|#define S3C2410_IISFCON_TXDMA&t;  (1&lt;&lt;15)
DECL|macro|S3C2410_IISFCON_RXDMA
mdefine_line|#define S3C2410_IISFCON_RXDMA&t;  (1&lt;&lt;14)
DECL|macro|S3C2410_IISFCON_TXENABLE
mdefine_line|#define S3C2410_IISFCON_TXENABLE  (1&lt;&lt;13)
DECL|macro|S3C2410_IISFCON_RXENABLE
mdefine_line|#define S3C2410_IISFCON_RXENABLE  (1&lt;&lt;12)
DECL|macro|S3C2410_IISFIFO
mdefine_line|#define S3C2410_IISFIFO  (0x10)
macro_line|#endif /* __ASM_ARCH_REGS_IIS_H */
eof
