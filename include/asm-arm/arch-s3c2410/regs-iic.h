multiline_comment|/* linux/include/asm-arm/arch-s3c2410/regs-iic.h&n; *&n; * Copyright (c) 2004 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 I2C Controller&n; *&n; *  Changelog:&n; *&t;03-Oct-2004  BJD  Initial include for Linux&n;*/
macro_line|#ifndef __ASM_ARCH_REGS_IIC_H
DECL|macro|__ASM_ARCH_REGS_IIC_H
mdefine_line|#define __ASM_ARCH_REGS_IIC_H __FILE__
multiline_comment|/* see s3c2410x user guide, v1.1, section 9 (p447) for more info */
DECL|macro|S3C2410_IICREG
mdefine_line|#define S3C2410_IICREG(x) (x)
DECL|macro|S3C2410_IICCON
mdefine_line|#define S3C2410_IICCON    S3C2410_IICREG(0x00)
DECL|macro|S3C2410_IICSTAT
mdefine_line|#define S3C2410_IICSTAT   S3C2410_IICREG(0x04)
DECL|macro|S3C2410_IICADD
mdefine_line|#define S3C2410_IICADD    S3C2410_IICREG(0x08)
DECL|macro|S3C2410_IICDS
mdefine_line|#define S3C2410_IICDS     S3C2410_IICREG(0x0C)
DECL|macro|S3C2410_IICCON_ACKEN
mdefine_line|#define S3C2410_IICCON_ACKEN&t;&t;(1&lt;&lt;7)
DECL|macro|S3C2410_IICCON_TXDIV_16
mdefine_line|#define S3C2410_IICCON_TXDIV_16&t;&t;(0&lt;&lt;6)
DECL|macro|S3C2410_IICCON_TXDIV_512
mdefine_line|#define S3C2410_IICCON_TXDIV_512&t;(1&lt;&lt;6)
DECL|macro|S3C2410_IICCON_IRQEN
mdefine_line|#define S3C2410_IICCON_IRQEN&t;&t;(1&lt;&lt;5)
DECL|macro|S3C2410_IICCON_IRQPEND
mdefine_line|#define S3C2410_IICCON_IRQPEND&t;&t;(1&lt;&lt;4)
DECL|macro|S3C2410_IICCON_SCALE
mdefine_line|#define S3C2410_IICCON_SCALE(x)&t;&t;((x)&amp;15)
DECL|macro|S3C2410_IICCON_SCALEMASK
mdefine_line|#define S3C2410_IICCON_SCALEMASK&t;(0xf)
DECL|macro|S3C2410_IICSTAT_MASTER_RX
mdefine_line|#define S3C2410_IICSTAT_MASTER_RX&t;(2&lt;&lt;6)
DECL|macro|S3C2410_IICSTAT_MASTER_TX
mdefine_line|#define S3C2410_IICSTAT_MASTER_TX&t;(3&lt;&lt;6)
DECL|macro|S3C2410_IICSTAT_SLAVE_RX
mdefine_line|#define S3C2410_IICSTAT_SLAVE_RX&t;(0&lt;&lt;6)
DECL|macro|S3C2410_IICSTAT_SLAVE_TX
mdefine_line|#define S3C2410_IICSTAT_SLAVE_TX&t;(1&lt;&lt;6)
DECL|macro|S3C2410_IICSTAT_MODEMASK
mdefine_line|#define S3C2410_IICSTAT_MODEMASK&t;(3&lt;&lt;6)
DECL|macro|S3C2410_IICSTAT_START
mdefine_line|#define S3C2410_IICSTAT_START&t;&t;(1&lt;&lt;5)
DECL|macro|S3C2410_IICSTAT_BUSBUSY
mdefine_line|#define S3C2410_IICSTAT_BUSBUSY&t;&t;(1&lt;&lt;5)
DECL|macro|S3C2410_IICSTAT_TXRXEN
mdefine_line|#define S3C2410_IICSTAT_TXRXEN&t;&t;(1&lt;&lt;4)
DECL|macro|S3C2410_IICSTAT_ARBITR
mdefine_line|#define S3C2410_IICSTAT_ARBITR&t;&t;(1&lt;&lt;3)
DECL|macro|S3C2410_IICSTAT_ASSLAVE
mdefine_line|#define S3C2410_IICSTAT_ASSLAVE&t;&t;(1&lt;&lt;2)
DECL|macro|S3C2410_IICSTAT_ADDR0
mdefine_line|#define S3C2410_IICSTAT_ADDR0&t;&t;(1&lt;&lt;1)
DECL|macro|S3C2410_IICSTAT_LASTBIT
mdefine_line|#define S3C2410_IICSTAT_LASTBIT&t;&t;(1&lt;&lt;0)
macro_line|#endif /* __ASM_ARCH_REGS_IIC_H */
eof
