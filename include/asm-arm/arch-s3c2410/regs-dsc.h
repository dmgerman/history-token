multiline_comment|/* linux/include/asm/hardware/s3c2410/regs-dsc.h&n; *&n; * Copyright (c) 2004 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2440 Signal Drive Strength Control&n; *&n; *  Changelog:&n; *    11-Aug-2004     BJD     Created file&n; *    25-Aug-2004     BJD     Added the _SELECT_* defs for using with functions&n;*/
macro_line|#ifndef __ASM_ARCH_REGS_DSC_H
DECL|macro|__ASM_ARCH_REGS_DSC_H
mdefine_line|#define __ASM_ARCH_REGS_DSC_H &quot;2440-dsc&quot;
macro_line|#ifdef CONFIG_CPU_S3C2440
DECL|macro|S3C2440_DSC0
mdefine_line|#define S3C2440_DSC0&t;   S3C2410_GPIOREG(0xc4)
DECL|macro|S3C2440_DSC1
mdefine_line|#define S3C2440_DSC1&t;   S3C2410_GPIOREG(0xc8)
DECL|macro|S3C2440_SELECT_DSC0
mdefine_line|#define S3C2440_SELECT_DSC0 (0)
DECL|macro|S3C2440_SELECT_DSC1
mdefine_line|#define S3C2440_SELECT_DSC1 (1&lt;&lt;31)
DECL|macro|S3C2440_DSC_GETSHIFT
mdefine_line|#define S3C2440_DSC_GETSHIFT(x) ((x) &amp; 31)
DECL|macro|S3C2440_DSC0_DISABLE
mdefine_line|#define S3C2440_DSC0_DISABLE&t;(1&lt;&lt;31)
DECL|macro|S3C2440_DSC0_ADDR
mdefine_line|#define S3C2440_DSC0_ADDR       (S3C2440_SELECT_DSC0 | 8)
DECL|macro|S3C2440_DSC0_ADDR_12mA
mdefine_line|#define S3C2440_DSC0_ADDR_12mA  (0&lt;&lt;8)
DECL|macro|S3C2440_DSC0_ADDR_10mA
mdefine_line|#define S3C2440_DSC0_ADDR_10mA  (1&lt;&lt;8)
DECL|macro|S3C2440_DSC0_ADDR_8mA
mdefine_line|#define S3C2440_DSC0_ADDR_8mA   (2&lt;&lt;8)
DECL|macro|S3C2440_DSC0_ADDR_6mA
mdefine_line|#define S3C2440_DSC0_ADDR_6mA   (3&lt;&lt;8)
DECL|macro|S3C2440_DSC0_ADDR_MASK
mdefine_line|#define S3C2440_DSC0_ADDR_MASK  (3&lt;&lt;8)
multiline_comment|/* D24..D31 */
DECL|macro|S3C2440_DSC0_DATA3
mdefine_line|#define S3C2440_DSC0_DATA3      (S3C2440_SELECT_DSC0 | 6)
DECL|macro|S3C2440_DSC0_DATA3_12mA
mdefine_line|#define S3C2440_DSC0_DATA3_12mA (0&lt;&lt;6)
DECL|macro|S3C2440_DSC0_DATA3_10mA
mdefine_line|#define S3C2440_DSC0_DATA3_10mA (1&lt;&lt;6)
DECL|macro|S3C2440_DSC0_DATA3_8mA
mdefine_line|#define S3C2440_DSC0_DATA3_8mA  (2&lt;&lt;6)
DECL|macro|S3C2440_DSC0_DATA3_6mA
mdefine_line|#define S3C2440_DSC0_DATA3_6mA  (3&lt;&lt;6)
DECL|macro|S3C2440_DSC0_DATA3_MASK
mdefine_line|#define S3C2440_DSC0_DATA3_MASK (3&lt;&lt;6)
multiline_comment|/* D16..D23 */
DECL|macro|S3C2440_DSC0_DATA2
mdefine_line|#define S3C2440_DSC0_DATA2      (S3C2440_SELECT_DSC0 | 4)
DECL|macro|S3C2440_DSC0_DATA2_12mA
mdefine_line|#define S3C2440_DSC0_DATA2_12mA (0&lt;&lt;4)
DECL|macro|S3C2440_DSC0_DATA2_10mA
mdefine_line|#define S3C2440_DSC0_DATA2_10mA (1&lt;&lt;4)
DECL|macro|S3C2440_DSC0_DATA2_8mA
mdefine_line|#define S3C2440_DSC0_DATA2_8mA  (2&lt;&lt;4)
DECL|macro|S3C2440_DSC0_DATA2_6mA
mdefine_line|#define S3C2440_DSC0_DATA2_6mA  (3&lt;&lt;4)
DECL|macro|S3C2440_DSC0_DATA2_MASK
mdefine_line|#define S3C2440_DSC0_DATA2_MASK (3&lt;&lt;4)
multiline_comment|/* D8..D15 */
DECL|macro|S3C2440_DSC0_DATA1
mdefine_line|#define S3C2440_DSC0_DATA1      (S3C2440_SELECT_DSC0 | 2)
DECL|macro|S3C2440_DSC0_DATA1_12mA
mdefine_line|#define S3C2440_DSC0_DATA1_12mA (0&lt;&lt;2)
DECL|macro|S3C2440_DSC0_DATA1_10mA
mdefine_line|#define S3C2440_DSC0_DATA1_10mA (1&lt;&lt;2)
DECL|macro|S3C2440_DSC0_DATA1_8mA
mdefine_line|#define S3C2440_DSC0_DATA1_8mA  (2&lt;&lt;2)
DECL|macro|S3C2440_DSC0_DATA1_6mA
mdefine_line|#define S3C2440_DSC0_DATA1_6mA  (3&lt;&lt;2)
DECL|macro|S3C2440_DSC0_DATA1_MASK
mdefine_line|#define S3C2440_DSC0_DATA1_MASK (3&lt;&lt;2)
multiline_comment|/* D0..D7 */
DECL|macro|S3C2440_DSC0_DATA0
mdefine_line|#define S3C2440_DSC0_DATA0      (S3C2440_SELECT_DSC0 | 0)
DECL|macro|S3C2440_DSC0_DATA0_12mA
mdefine_line|#define S3C2440_DSC0_DATA0_12mA (0&lt;&lt;0)
DECL|macro|S3C2440_DSC0_DATA0_10mA
mdefine_line|#define S3C2440_DSC0_DATA0_10mA (1&lt;&lt;0)
DECL|macro|S3C2440_DSC0_DATA0_8mA
mdefine_line|#define S3C2440_DSC0_DATA0_8mA  (2&lt;&lt;0)
DECL|macro|S3C2440_DSC0_DATA0_6mA
mdefine_line|#define S3C2440_DSC0_DATA0_6mA  (3&lt;&lt;0)
DECL|macro|S3C2440_DSC0_DATA0_MASK
mdefine_line|#define S3C2440_DSC0_DATA0_MASK (3&lt;&lt;0)
DECL|macro|S3C2440_DSC1_SCK1
mdefine_line|#define S3C2440_DSC1_SCK1       (S3C2440_SELECT_DSC1 | 28)
DECL|macro|S3C2440_DSC1_SCK1_12mA
mdefine_line|#define S3C2440_DSC1_SCK1_12mA  (0&lt;&lt;28)
DECL|macro|S3C2440_DSC1_SCK1_10mA
mdefine_line|#define S3C2440_DSC1_SCK1_10mA  (1&lt;&lt;28)
DECL|macro|S3C2440_DSC1_SCK1_8mA
mdefine_line|#define S3C2440_DSC1_SCK1_8mA   (2&lt;&lt;28)
DECL|macro|S3C2440_DSC1_SCK1_6mA
mdefine_line|#define S3C2440_DSC1_SCK1_6mA   (3&lt;&lt;28)
DECL|macro|S3C2440_DSC1_SCK1_MASK
mdefine_line|#define S3C2440_DSC1_SCK1_MASK  (3&lt;&lt;28)
DECL|macro|S3C2440_DSC1_SCK0
mdefine_line|#define S3C2440_DSC1_SCK0       (S3C2440_SELECT_DSC1 | 26)
DECL|macro|S3C2440_DSC1_SCK0_12mA
mdefine_line|#define S3C2440_DSC1_SCK0_12mA  (0&lt;&lt;26)
DECL|macro|S3C2440_DSC1_SCK0_10mA
mdefine_line|#define S3C2440_DSC1_SCK0_10mA  (1&lt;&lt;26)
DECL|macro|S3C2440_DSC1_SCK0_8mA
mdefine_line|#define S3C2440_DSC1_SCK0_8mA   (2&lt;&lt;26)
DECL|macro|S3C2440_DSC1_SCK0_6mA
mdefine_line|#define S3C2440_DSC1_SCK0_6mA   (3&lt;&lt;26)
DECL|macro|S3C2440_DSC1_SCK0_MASK
mdefine_line|#define S3C2440_DSC1_SCK0_MASK  (3&lt;&lt;26)
DECL|macro|S3C2440_DSC1_SCKE
mdefine_line|#define S3C2440_DSC1_SCKE       (S3C2440_SELECT_DSC1 | 24)
DECL|macro|S3C2440_DSC1_SCKE_10mA
mdefine_line|#define S3C2440_DSC1_SCKE_10mA  (0&lt;&lt;24)
DECL|macro|S3C2440_DSC1_SCKE_8mA
mdefine_line|#define S3C2440_DSC1_SCKE_8mA   (1&lt;&lt;24)
DECL|macro|S3C2440_DSC1_SCKE_6mA
mdefine_line|#define S3C2440_DSC1_SCKE_6mA   (2&lt;&lt;24)
DECL|macro|S3C2440_DSC1_SCKE_4mA
mdefine_line|#define S3C2440_DSC1_SCKE_4mA   (3&lt;&lt;24)
DECL|macro|S3C2440_DSC1_SCKE_MASK
mdefine_line|#define S3C2440_DSC1_SCKE_MASK  (3&lt;&lt;24)
multiline_comment|/* SDRAM nRAS/nCAS */
DECL|macro|S3C2440_DSC1_SDR
mdefine_line|#define S3C2440_DSC1_SDR        (S3C2440_SELECT_DSC1 | 22)
DECL|macro|S3C2440_DSC1_SDR_10mA
mdefine_line|#define S3C2440_DSC1_SDR_10mA   (0&lt;&lt;22)
DECL|macro|S3C2440_DSC1_SDR_8mA
mdefine_line|#define S3C2440_DSC1_SDR_8mA    (1&lt;&lt;22)
DECL|macro|S3C2440_DSC1_SDR_6mA
mdefine_line|#define S3C2440_DSC1_SDR_6mA    (2&lt;&lt;22)
DECL|macro|S3C2440_DSC1_SDR_4mA
mdefine_line|#define S3C2440_DSC1_SDR_4mA    (3&lt;&lt;22)
DECL|macro|S3C2440_DSC1_SDR_MASK
mdefine_line|#define S3C2440_DSC1_SDR_MASK   (3&lt;&lt;22)
multiline_comment|/* NAND Flash Controller */
DECL|macro|S3C2440_DSC1_NFC
mdefine_line|#define S3C2440_DSC1_NFC        (S3C2440_SELECT_DSC1 | 20)
DECL|macro|S3C2440_DSC1_NFC_10mA
mdefine_line|#define S3C2440_DSC1_NFC_10mA   (0&lt;&lt;20)
DECL|macro|S3C2440_DSC1_NFC_8mA
mdefine_line|#define S3C2440_DSC1_NFC_8mA    (1&lt;&lt;20)
DECL|macro|S3C2440_DSC1_NFC_6mA
mdefine_line|#define S3C2440_DSC1_NFC_6mA    (2&lt;&lt;20)
DECL|macro|S3C2440_DSC1_NFC_4mA
mdefine_line|#define S3C2440_DSC1_NFC_4mA    (3&lt;&lt;20)
DECL|macro|S3C2440_DSC1_NFC_MASK
mdefine_line|#define S3C2440_DSC1_NFC_MASK   (3&lt;&lt;20)
multiline_comment|/* nBE[0..3] */
DECL|macro|S3C2440_DSC1_nBE
mdefine_line|#define S3C2440_DSC1_nBE        (S3C2440_SELECT_DSC1 | 18)
DECL|macro|S3C2440_DSC1_nBE_10mA
mdefine_line|#define S3C2440_DSC1_nBE_10mA   (0&lt;&lt;18)
DECL|macro|S3C2440_DSC1_nBE_8mA
mdefine_line|#define S3C2440_DSC1_nBE_8mA    (1&lt;&lt;18)
DECL|macro|S3C2440_DSC1_nBE_6mA
mdefine_line|#define S3C2440_DSC1_nBE_6mA    (2&lt;&lt;18)
DECL|macro|S3C2440_DSC1_nBE_4mA
mdefine_line|#define S3C2440_DSC1_nBE_4mA    (3&lt;&lt;18)
DECL|macro|S3C2440_DSC1_nBE_MASK
mdefine_line|#define S3C2440_DSC1_nBE_MASK   (3&lt;&lt;18)
DECL|macro|S3C2440_DSC1_WOE
mdefine_line|#define S3C2440_DSC1_WOE        (S3C2440_SELECT_DSC1 | 16)
DECL|macro|S3C2440_DSC1_WOE_10mA
mdefine_line|#define S3C2440_DSC1_WOE_10mA   (0&lt;&lt;16)
DECL|macro|S3C2440_DSC1_WOE_8mA
mdefine_line|#define S3C2440_DSC1_WOE_8mA    (1&lt;&lt;16)
DECL|macro|S3C2440_DSC1_WOE_6mA
mdefine_line|#define S3C2440_DSC1_WOE_6mA    (2&lt;&lt;16)
DECL|macro|S3C2440_DSC1_WOE_4mA
mdefine_line|#define S3C2440_DSC1_WOE_4mA    (3&lt;&lt;16)
DECL|macro|S3C2440_DSC1_WOE_MASK
mdefine_line|#define S3C2440_DSC1_WOE_MASK   (3&lt;&lt;16)
DECL|macro|S3C2440_DSC1_CS7
mdefine_line|#define S3C2440_DSC1_CS7        (S3C2440_SELECT_DSC1 | 14)
DECL|macro|S3C2440_DSC1_CS7_10mA
mdefine_line|#define S3C2440_DSC1_CS7_10mA   (0&lt;&lt;14)
DECL|macro|S3C2440_DSC1_CS7_8mA
mdefine_line|#define S3C2440_DSC1_CS7_8mA    (1&lt;&lt;14)
DECL|macro|S3C2440_DSC1_CS7_6mA
mdefine_line|#define S3C2440_DSC1_CS7_6mA    (2&lt;&lt;14)
DECL|macro|S3C2440_DSC1_CS7_4mA
mdefine_line|#define S3C2440_DSC1_CS7_4mA    (3&lt;&lt;14)
DECL|macro|S3C2440_DSC1_CS7_MASK
mdefine_line|#define S3C2440_DSC1_CS7_MASK   (3&lt;&lt;14)
DECL|macro|S3C2440_DSC1_CS6
mdefine_line|#define S3C2440_DSC1_CS6        (S3C2440_SELECT_DSC1 | 12)
DECL|macro|S3C2440_DSC1_CS6_10mA
mdefine_line|#define S3C2440_DSC1_CS6_10mA   (0&lt;&lt;12)
DECL|macro|S3C2440_DSC1_CS6_8mA
mdefine_line|#define S3C2440_DSC1_CS6_8mA    (1&lt;&lt;12)
DECL|macro|S3C2440_DSC1_CS6_6mA
mdefine_line|#define S3C2440_DSC1_CS6_6mA    (2&lt;&lt;12)
DECL|macro|S3C2440_DSC1_CS6_4mA
mdefine_line|#define S3C2440_DSC1_CS6_4mA    (3&lt;&lt;12)
DECL|macro|S3C2440_DSC1_CS6_MASK
mdefine_line|#define S3C2440_DSC1_CS6_MASK   (3&lt;&lt;12)
DECL|macro|S3C2440_DSC1_CS5
mdefine_line|#define S3C2440_DSC1_CS5        (S3C2440_SELECT_DSC1 | 10)
DECL|macro|S3C2440_DSC1_CS5_10mA
mdefine_line|#define S3C2440_DSC1_CS5_10mA   (0&lt;&lt;10)
DECL|macro|S3C2440_DSC1_CS5_8mA
mdefine_line|#define S3C2440_DSC1_CS5_8mA    (1&lt;&lt;10)
DECL|macro|S3C2440_DSC1_CS5_6mA
mdefine_line|#define S3C2440_DSC1_CS5_6mA    (2&lt;&lt;10)
DECL|macro|S3C2440_DSC1_CS5_4mA
mdefine_line|#define S3C2440_DSC1_CS5_4mA    (3&lt;&lt;10)
DECL|macro|S3C2440_DSC1_CS5_MASK
mdefine_line|#define S3C2440_DSC1_CS5_MASK   (3&lt;&lt;10)
DECL|macro|S3C2440_DSC1_CS4
mdefine_line|#define S3C2440_DSC1_CS4        (S3C2440_SELECT_DSC1 | 8)
DECL|macro|S3C2440_DSC1_CS4_10mA
mdefine_line|#define S3C2440_DSC1_CS4_10mA   (0&lt;&lt;8)
DECL|macro|S3C2440_DSC1_CS4_8mA
mdefine_line|#define S3C2440_DSC1_CS4_8mA    (1&lt;&lt;8)
DECL|macro|S3C2440_DSC1_CS4_6mA
mdefine_line|#define S3C2440_DSC1_CS4_6mA    (2&lt;&lt;8)
DECL|macro|S3C2440_DSC1_CS4_4mA
mdefine_line|#define S3C2440_DSC1_CS4_4mA    (3&lt;&lt;8)
DECL|macro|S3C2440_DSC1_CS4_MASK
mdefine_line|#define S3C2440_DSC1_CS4_MASK   (3&lt;&lt;8)
DECL|macro|S3C2440_DSC1_CS3
mdefine_line|#define S3C2440_DSC1_CS3        (S3C2440_SELECT_DSC1 | 6)
DECL|macro|S3C2440_DSC1_CS3_10mA
mdefine_line|#define S3C2440_DSC1_CS3_10mA   (0&lt;&lt;6)
DECL|macro|S3C2440_DSC1_CS3_8mA
mdefine_line|#define S3C2440_DSC1_CS3_8mA    (1&lt;&lt;6)
DECL|macro|S3C2440_DSC1_CS3_6mA
mdefine_line|#define S3C2440_DSC1_CS3_6mA    (2&lt;&lt;6)
DECL|macro|S3C2440_DSC1_CS3_4mA
mdefine_line|#define S3C2440_DSC1_CS3_4mA    (3&lt;&lt;6)
DECL|macro|S3C2440_DSC1_CS3_MASK
mdefine_line|#define S3C2440_DSC1_CS3_MASK   (3&lt;&lt;6)
DECL|macro|S3C2440_DSC1_CS2
mdefine_line|#define S3C2440_DSC1_CS2        (S3C2440_SELECT_DSC1 | 4)
DECL|macro|S3C2440_DSC1_CS2_10mA
mdefine_line|#define S3C2440_DSC1_CS2_10mA   (0&lt;&lt;4)
DECL|macro|S3C2440_DSC1_CS2_8mA
mdefine_line|#define S3C2440_DSC1_CS2_8mA    (1&lt;&lt;4)
DECL|macro|S3C2440_DSC1_CS2_6mA
mdefine_line|#define S3C2440_DSC1_CS2_6mA    (2&lt;&lt;4)
DECL|macro|S3C2440_DSC1_CS2_4mA
mdefine_line|#define S3C2440_DSC1_CS2_4mA    (3&lt;&lt;4)
DECL|macro|S3C2440_DSC1_CS2_MASK
mdefine_line|#define S3C2440_DSC1_CS2_MASK   (3&lt;&lt;4)
DECL|macro|S3C2440_DSC1_CS1
mdefine_line|#define S3C2440_DSC1_CS1        (S3C2440_SELECT_DSC1 | 2)
DECL|macro|S3C2440_DSC1_CS1_10mA
mdefine_line|#define S3C2440_DSC1_CS1_10mA   (0&lt;&lt;2)
DECL|macro|S3C2440_DSC1_CS1_8mA
mdefine_line|#define S3C2440_DSC1_CS1_8mA    (1&lt;&lt;2)
DECL|macro|S3C2440_DSC1_CS1_6mA
mdefine_line|#define S3C2440_DSC1_CS1_6mA    (2&lt;&lt;2)
DECL|macro|S3C2440_DSC1_CS1_4mA
mdefine_line|#define S3C2440_DSC1_CS1_4mA    (3&lt;&lt;2)
DECL|macro|S3C2440_DSC1_CS1_MASK
mdefine_line|#define S3C2440_DSC1_CS1_MASK   (3&lt;&lt;2)
DECL|macro|S3C2440_DSC1_CS0
mdefine_line|#define S3C2440_DSC1_CS0        (S3C2440_SELECT_DSC1 | 0
DECL|macro|S3C2440_DSC1_CS0_10mA
mdefine_line|#define S3C2440_DSC1_CS0_10mA   (0&lt;&lt;0)
DECL|macro|S3C2440_DSC1_CS0_8mA
mdefine_line|#define S3C2440_DSC1_CS0_8mA    (1&lt;&lt;0)
DECL|macro|S3C2440_DSC1_CS0_6mA
mdefine_line|#define S3C2440_DSC1_CS0_6mA    (2&lt;&lt;0)
DECL|macro|S3C2440_DSC1_CS0_4mA
mdefine_line|#define S3C2440_DSC1_CS0_4mA    (3&lt;&lt;0)
DECL|macro|S3C2440_DSC1_CS0_MASK
mdefine_line|#define S3C2440_DSC1_CS0_MASK   (3&lt;&lt;0)
macro_line|#endif /* CONFIG_CPU_S3C2440 */
macro_line|#endif&t;/* __ASM_ARCH_REGS_DSC_H */
eof
