multiline_comment|/*&n; * arch/ppc/platforms/hdpu.h&n; *&n; * Definitions for Sky Computers HDPU board.&n; *&n; * Brian Waite &lt;waite@skycomputers.com&gt;&n; *&n; * Based on code done by Rabeeh Khoury - rabeeh@galileo.co.il&n; * Based on code done by Mark A. Greer &lt;mgreer@mvista.com&gt;&n; * Based on code done by  Tim Montgomery &lt;timm@artesyncp.com&gt;&n; *&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
multiline_comment|/*&n; * The MV64360 has 2 PCI buses each with 1 window from the CPU bus to&n; * PCI I/O space and 4 windows from the CPU bus to PCI MEM space.&n; * We&squot;ll only use one PCI MEM window on each PCI bus.&n; *&n; * This is the CPU physical memory map (windows must be at least 64K and start&n; * on a boundary that is a multiple of the window size):&n; *&n; *    0x80000000-0x8fffffff&t; - PCI 0 MEM&n; *    0xa0000000-0xafffffff&t; - PCI 1 MEM&n; *    0xc0000000-0xc0ffffff&t; - PCI 0 I/O&n; *    0xc1000000-0xc1ffffff&t; - PCI 1 I/O&n;&n; *    0xf1000000-0xf100ffff      - MV64360 Registers&n; *    0xf1010000-0xfb9fffff      - HOLE&n; *    0xfbfa0000-0xfbfaffff      - TBEN&n; *    0xfbf00000-0xfbfbffff      - NEXUS&n; *    0xfbfc0000-0xfbffffff      - Internal SRAM&n; *    0xfc000000-0xffffffff      - Boot window&n; */
macro_line|#ifndef __PPC_PLATFORMS_HDPU_H
DECL|macro|__PPC_PLATFORMS_HDPU_H
mdefine_line|#define __PPC_PLATFORMS_HDPU_H
multiline_comment|/* CPU Physical Memory Map setup. */
DECL|macro|HDPU_BRIDGE_REG_BASE
mdefine_line|#define&t;HDPU_BRIDGE_REG_BASE&t;&t;     0xf1000000
DECL|macro|HDPU_TBEN_BASE
mdefine_line|#define HDPU_TBEN_BASE                        0xfbfa0000
DECL|macro|HDPU_TBEN_SIZE
mdefine_line|#define HDPU_TBEN_SIZE                        0x00010000
DECL|macro|HDPU_NEXUS_ID_BASE
mdefine_line|#define HDPU_NEXUS_ID_BASE                    0xfbfb0000
DECL|macro|HDPU_NEXUS_ID_SIZE
mdefine_line|#define HDPU_NEXUS_ID_SIZE                    0x00010000
DECL|macro|HDPU_INTERNAL_SRAM_BASE
mdefine_line|#define HDPU_INTERNAL_SRAM_BASE               0xfbfc0000
DECL|macro|HDPU_INTERNAL_SRAM_SIZE
mdefine_line|#define HDPU_INTERNAL_SRAM_SIZE               0x00040000
DECL|macro|HDPU_EMB_FLASH_BASE
mdefine_line|#define&t;HDPU_EMB_FLASH_BASE&t;&t;      0xfc000000
DECL|macro|HDPU_EMB_FLASH_SIZE
mdefine_line|#define&t;HDPU_EMB_FLASH_SIZE      &t;      0x04000000
multiline_comment|/* PCI Mappings */
DECL|macro|HDPU_PCI0_MEM_START_PROC_ADDR
mdefine_line|#define HDPU_PCI0_MEM_START_PROC_ADDR         0x80000000
DECL|macro|HDPU_PCI0_MEM_START_PCI_HI_ADDR
mdefine_line|#define HDPU_PCI0_MEM_START_PCI_HI_ADDR       0x00000000
DECL|macro|HDPU_PCI0_MEM_START_PCI_LO_ADDR
mdefine_line|#define HDPU_PCI0_MEM_START_PCI_LO_ADDR       HDPU_PCI0_MEM_START_PROC_ADDR
DECL|macro|HDPU_PCI0_MEM_SIZE
mdefine_line|#define HDPU_PCI0_MEM_SIZE                    0x10000000
DECL|macro|HDPU_PCI1_MEM_START_PROC_ADDR
mdefine_line|#define HDPU_PCI1_MEM_START_PROC_ADDR         0xc0000000
DECL|macro|HDPU_PCI1_MEM_START_PCI_HI_ADDR
mdefine_line|#define HDPU_PCI1_MEM_START_PCI_HI_ADDR       0x00000000
DECL|macro|HDPU_PCI1_MEM_START_PCI_LO_ADDR
mdefine_line|#define HDPU_PCI1_MEM_START_PCI_LO_ADDR       HDPU_PCI1_MEM_START_PROC_ADDR
DECL|macro|HDPU_PCI1_MEM_SIZE
mdefine_line|#define HDPU_PCI1_MEM_SIZE                    0x20000000
DECL|macro|HDPU_PCI0_IO_START_PROC_ADDR
mdefine_line|#define HDPU_PCI0_IO_START_PROC_ADDR          0xc0000000
DECL|macro|HDPU_PCI0_IO_START_PCI_ADDR
mdefine_line|#define HDPU_PCI0_IO_START_PCI_ADDR           0x00000000
DECL|macro|HDPU_PCI0_IO_SIZE
mdefine_line|#define HDPU_PCI0_IO_SIZE                     0x01000000
DECL|macro|HDPU_PCI1_IO_START_PROC_ADDR
mdefine_line|#define HDPU_PCI1_IO_START_PROC_ADDR          0xc1000000
DECL|macro|HDPU_PCI1_IO_START_PCI_ADDR
mdefine_line|#define HDPU_PCI1_IO_START_PCI_ADDR           0x01000000
DECL|macro|HDPU_PCI1_IO_SIZE
mdefine_line|#define HDPU_PCI1_IO_SIZE                     0x01000000
DECL|macro|HDPU_DEFAULT_BAUD
mdefine_line|#define HDPU_DEFAULT_BAUD 115200
DECL|macro|HDPU_MPSC_CLK_SRC
mdefine_line|#define HDPU_MPSC_CLK_SRC 8&t;/* TCLK */
DECL|macro|HDPU_MPSC_CLK_FREQ
mdefine_line|#define HDPU_MPSC_CLK_FREQ 133000000&t;/* 133 Mhz */
DECL|macro|HDPU_PCI_0_IRQ
mdefine_line|#define&t;HDPU_PCI_0_IRQ&t;&t;(8+64)
DECL|macro|HDPU_PCI_1_IRQ
mdefine_line|#define&t;HDPU_PCI_1_IRQ&t;&t;(13+64)
macro_line|#endif&t;&t;&t;&t;/* __PPC_PLATFORMS_HDPU_H */
eof
