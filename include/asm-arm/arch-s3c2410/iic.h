multiline_comment|/* linux/include/asm-arm/arch-s3c2410/iic.h&n; *&n; * (c) 2004 Simtec Electronics&n; *&t;Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 - I2C Controller platfrom_device info&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *&t;05-Oct-2004 BJD  Created file&n; *&t;19-Oct-2004 BJD&t; Updated for s3c2440&n;*/
macro_line|#ifndef __ASM_ARCH_IIC_H
DECL|macro|__ASM_ARCH_IIC_H
mdefine_line|#define __ASM_ARCH_IIC_H __FILE__
DECL|macro|S3C_IICFLG_FILTER
mdefine_line|#define S3C_IICFLG_FILTER&t;(1&lt;&lt;0)&t;/* enable s3c2440 filter */
multiline_comment|/* Notes:&n; *&t;1) All frequencies are expressed in Hz&n; *&t;2) A value of zero is `do not care`&n;*/
DECL|struct|s3c2410_platform_i2c
r_struct
id|s3c2410_platform_i2c
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|slave_addr
r_int
r_int
id|slave_addr
suffix:semicolon
multiline_comment|/* slave address for controller */
DECL|member|bus_freq
r_int
r_int
id|bus_freq
suffix:semicolon
multiline_comment|/* standard bus frequency */
DECL|member|max_freq
r_int
r_int
id|max_freq
suffix:semicolon
multiline_comment|/* max frequency for the bus */
DECL|member|min_freq
r_int
r_int
id|min_freq
suffix:semicolon
multiline_comment|/* min frequency for the bus */
DECL|member|sda_delay
r_int
r_int
id|sda_delay
suffix:semicolon
multiline_comment|/* pclks (s3c2440 only) */
)brace
suffix:semicolon
macro_line|#endif /* __ASM_ARCH_IIC_H */
eof
