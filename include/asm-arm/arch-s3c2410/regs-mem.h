multiline_comment|/* linux/include/asm-arm/arch-s3c2410/regs-mem.h&n; *&n; * Copyright (c) 2004 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 Memory Control register definitions&n; *&n; *  Changelog:&n; *&t;29-Sep-2004  BJD  Initial include for Linux&n; *&n;*/
macro_line|#ifndef __ASM_ARM_MEMREGS_H
DECL|macro|__ASM_ARM_MEMREGS_H
mdefine_line|#define __ASM_ARM_MEMREGS_H &quot;$Id: regs.h,v 1.8 2003/05/01 15:55:41 ben Exp $&quot;
macro_line|#ifndef S3C2410_MEMREG
DECL|macro|S3C2410_MEMREG
mdefine_line|#define S3C2410_MEMREG(x) (S3C2410_VA_MEMCTRL + (x))
macro_line|#endif
multiline_comment|/* bus width, and wait state control */
DECL|macro|S3C2410_BWSCON
mdefine_line|#define S3C2410_BWSCON&t;&t;&t;S3C2410_MEMREG(0x0000)
multiline_comment|/* bank zero config - note, pinstrapped from OM pins! */
DECL|macro|S3C2410_BWSCON_DW0_16
mdefine_line|#define S3C2410_BWSCON_DW0_16&t;&t;(1&lt;&lt;1)
DECL|macro|S3C2410_BWSCON_DW0_32
mdefine_line|#define S3C2410_BWSCON_DW0_32&t;&t;(2&lt;&lt;1)
multiline_comment|/* bank one configs */
DECL|macro|S3C2410_BWSCON_DW1_8
mdefine_line|#define S3C2410_BWSCON_DW1_8&t;&t;(0&lt;&lt;4)
DECL|macro|S3C2410_BWSCON_DW1_16
mdefine_line|#define S3C2410_BWSCON_DW1_16&t;&t;(1&lt;&lt;4)
DECL|macro|S3C2410_BWSCON_DW1_32
mdefine_line|#define S3C2410_BWSCON_DW1_32&t;&t;(2&lt;&lt;4)
DECL|macro|S3C2410_BWSCON_WS1
mdefine_line|#define S3C2410_BWSCON_WS1&t;&t;(1&lt;&lt;6)
DECL|macro|S3C2410_BWSCON_ST1
mdefine_line|#define S3C2410_BWSCON_ST1&t;&t;(1&lt;&lt;7)
multiline_comment|/* bank 2 configurations */
DECL|macro|S3C2410_BWSCON_DW2_8
mdefine_line|#define S3C2410_BWSCON_DW2_8&t;&t;(0&lt;&lt;8)
DECL|macro|S3C2410_BWSCON_DW2_16
mdefine_line|#define S3C2410_BWSCON_DW2_16&t;&t;(1&lt;&lt;8)
DECL|macro|S3C2410_BWSCON_DW2_32
mdefine_line|#define S3C2410_BWSCON_DW2_32&t;&t;(2&lt;&lt;8)
DECL|macro|S3C2410_BWSCON_WS2
mdefine_line|#define S3C2410_BWSCON_WS2&t;&t;(1&lt;&lt;10)
DECL|macro|S3C2410_BWSCON_ST2
mdefine_line|#define S3C2410_BWSCON_ST2&t;&t;(1&lt;&lt;11)
multiline_comment|/* bank 3 configurations */
DECL|macro|S3C2410_BWSCON_DW3_8
mdefine_line|#define S3C2410_BWSCON_DW3_8&t;&t;(0&lt;&lt;12)
DECL|macro|S3C2410_BWSCON_DW3_16
mdefine_line|#define S3C2410_BWSCON_DW3_16&t;&t;(1&lt;&lt;12)
DECL|macro|S3C2410_BWSCON_DW3_32
mdefine_line|#define S3C2410_BWSCON_DW3_32&t;&t;(2&lt;&lt;12)
DECL|macro|S3C2410_BWSCON_WS3
mdefine_line|#define S3C2410_BWSCON_WS3&t;&t;(1&lt;&lt;14)
DECL|macro|S3C2410_BWSCON_ST3
mdefine_line|#define S3C2410_BWSCON_ST3&t;&t;(1&lt;&lt;15)
multiline_comment|/* bank 4 configurations */
DECL|macro|S3C2410_BWSCON_DW4_8
mdefine_line|#define S3C2410_BWSCON_DW4_8&t;&t;(0&lt;&lt;16)
DECL|macro|S3C2410_BWSCON_DW4_16
mdefine_line|#define S3C2410_BWSCON_DW4_16&t;&t;(1&lt;&lt;16)
DECL|macro|S3C2410_BWSCON_DW4_32
mdefine_line|#define S3C2410_BWSCON_DW4_32&t;&t;(2&lt;&lt;16)
DECL|macro|S3C2410_BWSCON_WS4
mdefine_line|#define S3C2410_BWSCON_WS4&t;&t;(1&lt;&lt;18)
DECL|macro|S3C2410_BWSCON_ST4
mdefine_line|#define S3C2410_BWSCON_ST4&t;&t;(1&lt;&lt;19)
multiline_comment|/* bank 5 configurations */
DECL|macro|S3C2410_BWSCON_DW5_8
mdefine_line|#define S3C2410_BWSCON_DW5_8&t;&t;(0&lt;&lt;20)
DECL|macro|S3C2410_BWSCON_DW5_16
mdefine_line|#define S3C2410_BWSCON_DW5_16&t;&t;(1&lt;&lt;20)
DECL|macro|S3C2410_BWSCON_DW5_32
mdefine_line|#define S3C2410_BWSCON_DW5_32&t;&t;(2&lt;&lt;20)
DECL|macro|S3C2410_BWSCON_WS5
mdefine_line|#define S3C2410_BWSCON_WS5&t;&t;(1&lt;&lt;22)
DECL|macro|S3C2410_BWSCON_ST5
mdefine_line|#define S3C2410_BWSCON_ST5&t;&t;(1&lt;&lt;23)
multiline_comment|/* bank 6 configurations */
DECL|macro|S3C2410_BWSCON_DW6_8
mdefine_line|#define S3C2410_BWSCON_DW6_8&t;&t;(0&lt;&lt;24)
DECL|macro|S3C2410_BWSCON_DW6_16
mdefine_line|#define S3C2410_BWSCON_DW6_16&t;&t;(1&lt;&lt;24)
DECL|macro|S3C2410_BWSCON_DW6_32
mdefine_line|#define S3C2410_BWSCON_DW6_32&t;&t;(2&lt;&lt;24)
DECL|macro|S3C2410_BWSCON_WS6
mdefine_line|#define S3C2410_BWSCON_WS6&t;&t;(1&lt;&lt;26)
DECL|macro|S3C2410_BWSCON_ST6
mdefine_line|#define S3C2410_BWSCON_ST6&t;&t;(1&lt;&lt;27)
multiline_comment|/* bank 7 configurations */
DECL|macro|S3C2410_BWSCON_DW7_8
mdefine_line|#define S3C2410_BWSCON_DW7_8&t;&t;(0&lt;&lt;28)
DECL|macro|S3C2410_BWSCON_DW7_16
mdefine_line|#define S3C2410_BWSCON_DW7_16&t;&t;(1&lt;&lt;28)
DECL|macro|S3C2410_BWSCON_DW7_32
mdefine_line|#define S3C2410_BWSCON_DW7_32&t;&t;(2&lt;&lt;28)
DECL|macro|S3C2410_BWSCON_WS7
mdefine_line|#define S3C2410_BWSCON_WS7&t;&t;(1&lt;&lt;30)
DECL|macro|S3C2410_BWSCON_ST7
mdefine_line|#define S3C2410_BWSCON_ST7&t;&t;(1&lt;&lt;31)
multiline_comment|/* memory set (rom, ram) */
DECL|macro|S3C2410_BANKCON0
mdefine_line|#define S3C2410_BANKCON0&t;&t;S3C2410_MEMREG(0x0004)
DECL|macro|S3C2410_BANKCON1
mdefine_line|#define S3C2410_BANKCON1&t;&t;S3C2410_MEMREG(0x0008)
DECL|macro|S3C2410_BANKCON2
mdefine_line|#define S3C2410_BANKCON2&t;&t;S3C2410_MEMREG(0x000C)
DECL|macro|S3C2410_BANKCON3
mdefine_line|#define S3C2410_BANKCON3&t;&t;S3C2410_MEMREG(0x0010)
DECL|macro|S3C2410_BANKCON4
mdefine_line|#define S3C2410_BANKCON4&t;&t;S3C2410_MEMREG(0x0014)
DECL|macro|S3C2410_BANKCON5
mdefine_line|#define S3C2410_BANKCON5&t;&t;S3C2410_MEMREG(0x0018)
DECL|macro|S3C2410_BANKCON6
mdefine_line|#define S3C2410_BANKCON6&t;&t;S3C2410_MEMREG(0x001C)
DECL|macro|S3C2410_BANKCON7
mdefine_line|#define S3C2410_BANKCON7&t;&t;S3C2410_MEMREG(0x0020)
multiline_comment|/* bank configuration registers */
DECL|macro|S3C2410_BANKCON_PMCnorm
mdefine_line|#define S3C2410_BANKCON_PMCnorm&t;&t;(0x00)
DECL|macro|S3C2410_BANKCON_PMC4
mdefine_line|#define S3C2410_BANKCON_PMC4&t;&t;(0x01)
DECL|macro|S3C2410_BANKCON_PMC8
mdefine_line|#define S3C2410_BANKCON_PMC8&t;&t;(0x02)
DECL|macro|S3C2410_BANKCON_PMC16
mdefine_line|#define S3C2410_BANKCON_PMC16&t;&t;(0x03)
multiline_comment|/* bank configurations for banks 0..7, note banks&n; * 6 and 7 have differnt configurations depending on&n; * the memory type bits */
DECL|macro|S3C2410_BANKCON_Tacp2
mdefine_line|#define S3C2410_BANKCON_Tacp2&t;&t;(0x0 &lt;&lt; 2)
DECL|macro|S3C2410_BANKCON_Tacp3
mdefine_line|#define S3C2410_BANKCON_Tacp3&t;&t;(0x1 &lt;&lt; 2)
DECL|macro|S3C2410_BANKCON_Tacp4
mdefine_line|#define S3C2410_BANKCON_Tacp4&t;&t;(0x2 &lt;&lt; 2)
DECL|macro|S3C2410_BANKCON_Tacp6
mdefine_line|#define S3C2410_BANKCON_Tacp6&t;&t;(0x3 &lt;&lt; 2)
DECL|macro|S3C2410_BANKCON_Tcah0
mdefine_line|#define S3C2410_BANKCON_Tcah0&t;&t;(0x0 &lt;&lt; 4)
DECL|macro|S3C2410_BANKCON_Tcah1
mdefine_line|#define S3C2410_BANKCON_Tcah1&t;&t;(0x1 &lt;&lt; 4)
DECL|macro|S3C2410_BANKCON_Tcah2
mdefine_line|#define S3C2410_BANKCON_Tcah2&t;&t;(0x2 &lt;&lt; 4)
DECL|macro|S3C2410_BANKCON_Tcah4
mdefine_line|#define S3C2410_BANKCON_Tcah4&t;&t;(0x3 &lt;&lt; 4)
DECL|macro|S3C2410_BANKCON_Tcoh0
mdefine_line|#define S3C2410_BANKCON_Tcoh0&t;&t;(0x0 &lt;&lt; 6)
DECL|macro|S3C2410_BANKCON_Tcoh1
mdefine_line|#define S3C2410_BANKCON_Tcoh1&t;&t;(0x1 &lt;&lt; 6)
DECL|macro|S3C2410_BANKCON_Tcoh2
mdefine_line|#define S3C2410_BANKCON_Tcoh2&t;&t;(0x2 &lt;&lt; 6)
DECL|macro|S3C2410_BANKCON_Tcoh4
mdefine_line|#define S3C2410_BANKCON_Tcoh4&t;&t;(0x3 &lt;&lt; 6)
DECL|macro|S3C2410_BANKCON_Tacc1
mdefine_line|#define S3C2410_BANKCON_Tacc1&t;&t;(0x0 &lt;&lt; 8)
DECL|macro|S3C2410_BANKCON_Tacc2
mdefine_line|#define S3C2410_BANKCON_Tacc2&t;&t;(0x1 &lt;&lt; 8)
DECL|macro|S3C2410_BANKCON_Tacc3
mdefine_line|#define S3C2410_BANKCON_Tacc3&t;&t;(0x2 &lt;&lt; 8)
DECL|macro|S3C2410_BANKCON_Tacc4
mdefine_line|#define S3C2410_BANKCON_Tacc4&t;&t;(0x3 &lt;&lt; 8)
DECL|macro|S3C2410_BANKCON_Tacc6
mdefine_line|#define S3C2410_BANKCON_Tacc6&t;&t;(0x4 &lt;&lt; 8)
DECL|macro|S3C2410_BANKCON_Tacc8
mdefine_line|#define S3C2410_BANKCON_Tacc8&t;&t;(0x5 &lt;&lt; 8)
DECL|macro|S3C2410_BANKCON_Tacc10
mdefine_line|#define S3C2410_BANKCON_Tacc10&t;&t;(0x6 &lt;&lt; 8)
DECL|macro|S3C2410_BANKCON_Tacc14
mdefine_line|#define S3C2410_BANKCON_Tacc14&t;&t;(0x7 &lt;&lt; 8)
DECL|macro|S3C2410_BANKCON_Tcos0
mdefine_line|#define S3C2410_BANKCON_Tcos0&t;&t;(0x0 &lt;&lt; 11)
DECL|macro|S3C2410_BANKCON_Tcos1
mdefine_line|#define S3C2410_BANKCON_Tcos1&t;&t;(0x1 &lt;&lt; 11)
DECL|macro|S3C2410_BANKCON_Tcos2
mdefine_line|#define S3C2410_BANKCON_Tcos2&t;&t;(0x2 &lt;&lt; 11)
DECL|macro|S3C2410_BANKCON_Tcos4
mdefine_line|#define S3C2410_BANKCON_Tcos4&t;&t;(0x3 &lt;&lt; 11)
DECL|macro|S3C2410_BANKCON_Tacs0
mdefine_line|#define S3C2410_BANKCON_Tacs0&t;&t;(0x0 &lt;&lt; 13)
DECL|macro|S3C2410_BANKCON_Tacs1
mdefine_line|#define S3C2410_BANKCON_Tacs1&t;&t;(0x1 &lt;&lt; 13)
DECL|macro|S3C2410_BANKCON_Tacs2
mdefine_line|#define S3C2410_BANKCON_Tacs2&t;&t;(0x2 &lt;&lt; 13)
DECL|macro|S3C2410_BANKCON_Tacs4
mdefine_line|#define S3C2410_BANKCON_Tacs4&t;&t;(0x3 &lt;&lt; 13)
DECL|macro|S3C2410_BANKCON_SRAM
mdefine_line|#define S3C2410_BANKCON_SRAM&t;&t;(0x0 &lt;&lt; 15)
DECL|macro|S3C2410_BANKCON_SDRAM
mdefine_line|#define S3C2410_BANKCON_SDRAM&t;&t;(0x3 &lt;&lt; 15)
multiline_comment|/* next bits only for SDRAM in 6,7 */
DECL|macro|S3C2410_BANKCON_Trdc2
mdefine_line|#define S3C2410_BANKCON_Trdc2&t;&t;(0x00 &lt;&lt; 2)
DECL|macro|S3C2410_BANKCON_Trdc3
mdefine_line|#define S3C2410_BANKCON_Trdc3&t;&t;(0x01 &lt;&lt; 2)
DECL|macro|S3C2410_BANKCON_Trdc4
mdefine_line|#define S3C2410_BANKCON_Trdc4&t;&t;(0x02 &lt;&lt; 2)
multiline_comment|/* control column address select */
DECL|macro|S3C2410_BANKCON_SCANb8
mdefine_line|#define S3C2410_BANKCON_SCANb8&t;&t;(0x00 &lt;&lt; 0)
DECL|macro|S3C2410_BANKCON_SCANb9
mdefine_line|#define S3C2410_BANKCON_SCANb9&t;&t;(0x01 &lt;&lt; 0)
DECL|macro|S3C2410_BANKCON_SCANb10
mdefine_line|#define S3C2410_BANKCON_SCANb10&t;&t;(0x02 &lt;&lt; 0)
DECL|macro|S3C2410_REFRESH
mdefine_line|#define S3C2410_REFRESH&t;&t;&t;S3C2410_MEMREG(0x0024)
DECL|macro|S3C2410_BANKSIZE
mdefine_line|#define S3C2410_BANKSIZE&t;&t;S3C2410_MEMREG(0x0028)
DECL|macro|S3C2410_MRSRB6
mdefine_line|#define S3C2410_MRSRB6&t;&t;&t;S3C2410_MEMREG(0x002C)
DECL|macro|S3C2410_MRSRB7
mdefine_line|#define S3C2410_MRSRB7&t;&t;&t;S3C2410_MEMREG(0x0030)
multiline_comment|/* refresh control */
DECL|macro|S3C2410_REFRESH_REFEN
mdefine_line|#define S3C2410_REFRESH_REFEN&t;&t;(1&lt;&lt;23)
DECL|macro|S3C2410_REFRESH_SELF
mdefine_line|#define S3C2410_REFRESH_SELF&t;&t;(1&lt;&lt;22)
DECL|macro|S3C2410_REFRESH_REFCOUNTER
mdefine_line|#define S3C2410_REFRESH_REFCOUNTER&t;((1&lt;&lt;11)-1)
DECL|macro|S3C2410_REFRESH_TRP_MASK
mdefine_line|#define S3C2410_REFRESH_TRP_MASK&t;(3&lt;&lt;20)
DECL|macro|S3C2410_REFRESH_TRP_2clk
mdefine_line|#define S3C2410_REFRESH_TRP_2clk&t;(0&lt;&lt;20)
DECL|macro|S3C2410_REFRESH_TRP_3clk
mdefine_line|#define S3C2410_REFRESH_TRP_3clk&t;(1&lt;&lt;20)
DECL|macro|S3C2410_REFRESH_TRP_4clk
mdefine_line|#define S3C2410_REFRESH_TRP_4clk&t;(2&lt;&lt;20)
DECL|macro|S3C2410_REFRESH_TSRC_MASK
mdefine_line|#define S3C2410_REFRESH_TSRC_MASK&t;(3&lt;&lt;18)
DECL|macro|S3C2410_REFRESH_TSRC_4clk
mdefine_line|#define S3C2410_REFRESH_TSRC_4clk&t;(0&lt;&lt;18)
DECL|macro|S3C2410_REFRESH_TSRC_5clk
mdefine_line|#define S3C2410_REFRESH_TSRC_5clk&t;(1&lt;&lt;18)
DECL|macro|S3C2410_REFRESH_TSRC_6clk
mdefine_line|#define S3C2410_REFRESH_TSRC_6clk&t;(2&lt;&lt;18)
DECL|macro|S3C2410_REFRESH_TSRC_7clk
mdefine_line|#define S3C2410_REFRESH_TSRC_7clk&t;(3&lt;&lt;18)
multiline_comment|/* mode select register(s) */
DECL|macro|S3C2410_MRSRB_CL1
mdefine_line|#define  S3C2410_MRSRB_CL1&t;&t;(0x00 &lt;&lt; 4)
DECL|macro|S3C2410_MRSRB_CL2
mdefine_line|#define  S3C2410_MRSRB_CL2&t;&t;(0x02 &lt;&lt; 4)
DECL|macro|S3C2410_MRSRB_CL3
mdefine_line|#define  S3C2410_MRSRB_CL3&t;&t;(0x03 &lt;&lt; 4)
multiline_comment|/* bank size register */
DECL|macro|S3C2410_BANKSIZE_128M
mdefine_line|#define S3C2410_BANKSIZE_128M&t;&t;(0x2 &lt;&lt; 0)
DECL|macro|S3C2410_BANKSIZE_64M
mdefine_line|#define S3C2410_BANKSIZE_64M&t;&t;(0x1 &lt;&lt; 0)
DECL|macro|S3C2410_BANKSIZE_32M
mdefine_line|#define S3C2410_BANKSIZE_32M&t;&t;(0x0 &lt;&lt; 0)
DECL|macro|S3C2410_BANKSIZE_16M
mdefine_line|#define S3C2410_BANKSIZE_16M&t;&t;(0x7 &lt;&lt; 0)
DECL|macro|S3C2410_BANKSIZE_8M
mdefine_line|#define S3C2410_BANKSIZE_8M&t;&t;(0x6 &lt;&lt; 0)
DECL|macro|S3C2410_BANKSIZE_4M
mdefine_line|#define S3C2410_BANKSIZE_4M&t;&t;(0x5 &lt;&lt; 0)
DECL|macro|S3C2410_BANKSIZE_2M
mdefine_line|#define S3C2410_BANKSIZE_2M&t;&t;(0x4 &lt;&lt; 0)
DECL|macro|S3C2410_BANKSIZE_MASK
mdefine_line|#define S3C2410_BANKSIZE_MASK&t;&t;(0x7 &lt;&lt; 0)
DECL|macro|S3C2410_BANKSIZE_SCLK_EN
mdefine_line|#define S3C2410_BANKSIZE_SCLK_EN&t;(1&lt;&lt;4)
DECL|macro|S3C2410_BANKSIZE_SCKE_EN
mdefine_line|#define S3C2410_BANKSIZE_SCKE_EN&t;(1&lt;&lt;5)
DECL|macro|S3C2410_BANKSIZE_BURST
mdefine_line|#define S3C2410_BANKSIZE_BURST&t;&t;(1&lt;&lt;7)
macro_line|#endif /* __ASM_ARM_MEMREGS_H */
eof
