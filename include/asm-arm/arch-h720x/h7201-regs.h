multiline_comment|/*&n; * linux/include/asm-arm/arch-h720x/h7201-regs.h&n; *&n; * Copyright (C) 2000 Jungjun Kim, Hynix Semiconductor Inc.&n; *           (C) 2003 Thomas Gleixner &lt;tglx@linutronix.de&gt;&n; *           (C) 2003 Robert Schwebel &lt;r.schwebel@pengutronix.de&gt;&n; *           (C) 2004 Sascha Hauer    &lt;s.hauer@pengutronix.de&gt;&n; *&n; * This file contains the hardware definitions of the h720x processors&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Do not add implementations specific defines here. This files contains&n; * only defines of the onchip peripherals. Add those defines to boards.h,&n; * which is included by this file.&n; */
DECL|macro|SERIAL2_VIRT
mdefine_line|#define SERIAL2_VIRT &t;&t;(IO_VIRT + 0x50100)
DECL|macro|SERIAL3_VIRT
mdefine_line|#define SERIAL3_VIRT &t;&t;(IO_VIRT + 0x50200)
multiline_comment|/*&n; * PCMCIA&n; */
DECL|macro|PCMCIA0_ATT_BASE
mdefine_line|#define PCMCIA0_ATT_BASE        0xe5000000
DECL|macro|PCMCIA0_ATT_SIZE
mdefine_line|#define PCMCIA0_ATT_SIZE        0x00200000
DECL|macro|PCMCIA0_ATT_START
mdefine_line|#define PCMCIA0_ATT_START       0x20000000
DECL|macro|PCMCIA0_MEM_BASE
mdefine_line|#define PCMCIA0_MEM_BASE        0xe5200000
DECL|macro|PCMCIA0_MEM_SIZE
mdefine_line|#define PCMCIA0_MEM_SIZE        0x00200000
DECL|macro|PCMCIA0_MEM_START
mdefine_line|#define PCMCIA0_MEM_START       0x24000000
DECL|macro|PCMCIA0_IO_BASE
mdefine_line|#define PCMCIA0_IO_BASE         0xe5400000
DECL|macro|PCMCIA0_IO_SIZE
mdefine_line|#define PCMCIA0_IO_SIZE         0x00200000
DECL|macro|PCMCIA0_IO_START
mdefine_line|#define PCMCIA0_IO_START        0x28000000
DECL|macro|PCMCIA1_ATT_BASE
mdefine_line|#define PCMCIA1_ATT_BASE        0xe5600000
DECL|macro|PCMCIA1_ATT_SIZE
mdefine_line|#define PCMCIA1_ATT_SIZE        0x00200000
DECL|macro|PCMCIA1_ATT_START
mdefine_line|#define PCMCIA1_ATT_START       0x30000000
DECL|macro|PCMCIA1_MEM_BASE
mdefine_line|#define PCMCIA1_MEM_BASE        0xe5800000
DECL|macro|PCMCIA1_MEM_SIZE
mdefine_line|#define PCMCIA1_MEM_SIZE        0x00200000
DECL|macro|PCMCIA1_MEM_START
mdefine_line|#define PCMCIA1_MEM_START       0x34000000
DECL|macro|PCMCIA1_IO_BASE
mdefine_line|#define PCMCIA1_IO_BASE         0xe5a00000
DECL|macro|PCMCIA1_IO_SIZE
mdefine_line|#define PCMCIA1_IO_SIZE         0x00200000
DECL|macro|PCMCIA1_IO_START
mdefine_line|#define PCMCIA1_IO_START        0x38000000
DECL|macro|PRIME3C_BASE
mdefine_line|#define PRIME3C_BASE            0xf0050000
DECL|macro|PRIME3C_SIZE
mdefine_line|#define PRIME3C_SIZE            0x00001000
DECL|macro|PRIME3C_START
mdefine_line|#define PRIME3C_START           0x10000000
multiline_comment|/* VGA Controller */
DECL|macro|VGA_RAMBASE
mdefine_line|#define VGA_RAMBASE &t;&t;0x50
DECL|macro|VGA_TIMING0
mdefine_line|#define VGA_TIMING0 &t;&t;0x60
DECL|macro|VGA_TIMING1
mdefine_line|#define VGA_TIMING1 &t;&t;0x64
DECL|macro|VGA_TIMING2
mdefine_line|#define VGA_TIMING2 &t;&t;0x68
DECL|macro|VGA_TIMING3
mdefine_line|#define VGA_TIMING3 &t;&t;0x6c
DECL|macro|LCD_CTRL_VGA_ENABLE
mdefine_line|#define LCD_CTRL_VGA_ENABLE   &t;0x00000100
DECL|macro|LCD_CTRL_VGA_BPP_MASK
mdefine_line|#define LCD_CTRL_VGA_BPP_MASK &t;0x00000600
DECL|macro|LCD_CTRL_VGA_4BPP
mdefine_line|#define LCD_CTRL_VGA_4BPP    &t;0x00000000
DECL|macro|LCD_CTRL_VGA_8BPP
mdefine_line|#define LCD_CTRL_VGA_8BPP    &t;0x00000200
DECL|macro|LCD_CTRL_VGA_16BPP
mdefine_line|#define LCD_CTRL_VGA_16BPP   &t;0x00000300
DECL|macro|LCD_CTRL_SHARE_DMA
mdefine_line|#define LCD_CTRL_SHARE_DMA    &t;0x00000800
DECL|macro|LCD_CTRL_VDE
mdefine_line|#define LCD_CTRL_VDE          &t;0x00100000
DECL|macro|LCD_CTRL_LPE
mdefine_line|#define LCD_CTRL_LPE          &t;0x00400000&t;/* LCD Power enable */
DECL|macro|LCD_CTRL_BLE
mdefine_line|#define LCD_CTRL_BLE          &t;0x00800000&t;/* LCD backlight enable */
DECL|macro|VGA_PALETTE_BASE
mdefine_line|#define VGA_PALETTE_BASE&t;(IO_VIRT + 0x10800)
eof
