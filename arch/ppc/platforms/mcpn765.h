multiline_comment|/*&n; * arch/ppc/platforms/mcpn765.h&n; * &n; * Definitions for Motorola MCG MCPN765 cPCI Board.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
multiline_comment|/*&n; * From Processor to PCI:&n; *   PCI Mem Space: 0x80000000 - 0xc0000000 -&gt; 0x80000000 - 0xc0000000 (1 GB)&n; *   PCI I/O Space: 0xfd800000 - 0xfe000000 -&gt; 0x00000000 - 0x00800000 (8 MB)&n; *&t;Note: Must skip 0xfe000000-0xfe400000 for CONFIG_HIGHMEM/PKMAP area&n; *   MPIC in PCI Mem Space: 0xfe800000 - 0xfe830000 (not all used by MPIC)&n; *&n; * From PCI to Processor:&n; *   System Memory: 0x00000000 -&gt; 0x00000000&n; */
macro_line|#ifndef __PPC_PLATFORMS_MCPN765_H
DECL|macro|__PPC_PLATFORMS_MCPN765_H
mdefine_line|#define __PPC_PLATFORMS_MCPN765_H
multiline_comment|/* PCI Memory space mapping info */
DECL|macro|MCPN765_PCI_MEM_SIZE
mdefine_line|#define&t;MCPN765_PCI_MEM_SIZE&t;&t;0x40000000U
DECL|macro|MCPN765_PROC_PCI_MEM_START
mdefine_line|#define MCPN765_PROC_PCI_MEM_START&t;0x80000000U
DECL|macro|MCPN765_PROC_PCI_MEM_END
mdefine_line|#define MCPN765_PROC_PCI_MEM_END&t;(MCPN765_PROC_PCI_MEM_START +&t;&bslash;&n;&t;&t;&t;&t;&t; MCPN765_PCI_MEM_SIZE - 1)
DECL|macro|MCPN765_PCI_MEM_START
mdefine_line|#define MCPN765_PCI_MEM_START&t;&t;0x80000000U
DECL|macro|MCPN765_PCI_MEM_END
mdefine_line|#define MCPN765_PCI_MEM_END&t;&t;(MCPN765_PCI_MEM_START +&t;&bslash;&n;&t;&t;&t;&t;&t; MCPN765_PCI_MEM_SIZE - 1)
multiline_comment|/* PCI I/O space mapping info */
DECL|macro|MCPN765_PCI_IO_SIZE
mdefine_line|#define&t;MCPN765_PCI_IO_SIZE&t;&t;0x00800000U
DECL|macro|MCPN765_PROC_PCI_IO_START
mdefine_line|#define MCPN765_PROC_PCI_IO_START&t;0xfd800000U
DECL|macro|MCPN765_PROC_PCI_IO_END
mdefine_line|#define MCPN765_PROC_PCI_IO_END&t;&t;(MCPN765_PROC_PCI_IO_START +&t;&bslash;&n;&t;&t;&t;&t;&t; MCPN765_PCI_IO_SIZE - 1)
DECL|macro|MCPN765_PCI_IO_START
mdefine_line|#define MCPN765_PCI_IO_START&t;&t;0x00000000U
DECL|macro|MCPN765_PCI_IO_END
mdefine_line|#define MCPN765_PCI_IO_END&t;&t;(MCPN765_PCI_IO_START + &t;&bslash;&n;&t;&t;&t;&t;&t; MCPN765_PCI_IO_SIZE - 1)
multiline_comment|/* System memory mapping info */
DECL|macro|MCPN765_PCI_DRAM_OFFSET
mdefine_line|#define MCPN765_PCI_DRAM_OFFSET&t;&t;0x00000000U
DECL|macro|MCPN765_PCI_PHY_MEM_OFFSET
mdefine_line|#define MCPN765_PCI_PHY_MEM_OFFSET&t;0x00000000U
DECL|macro|MCPN765_ISA_MEM_BASE
mdefine_line|#define MCPN765_ISA_MEM_BASE&t;&t;0x00000000U
DECL|macro|MCPN765_ISA_IO_BASE
mdefine_line|#define MCPN765_ISA_IO_BASE&t;&t;MCPN765_PROC_PCI_IO_START
multiline_comment|/* Define base addresses for important sets of registers */
DECL|macro|MCPN765_HAWK_MPIC_BASE
mdefine_line|#define MCPN765_HAWK_MPIC_BASE&t;&t;0xfe800000U
DECL|macro|MCPN765_HAWK_SMC_BASE
mdefine_line|#define MCPN765_HAWK_SMC_BASE&t;&t;0xfef80000U
DECL|macro|MCPN765_HAWK_PPC_REG_BASE
mdefine_line|#define&t;MCPN765_HAWK_PPC_REG_BASE&t;0xfeff0000U
multiline_comment|/* Define MCPN765 board register addresses. */
DECL|macro|MCPN765_BOARD_STATUS_REG
mdefine_line|#define&t;MCPN765_BOARD_STATUS_REG&t;0xfef88080U
DECL|macro|MCPN765_BOARD_MODFAIL_REG
mdefine_line|#define&t;MCPN765_BOARD_MODFAIL_REG&t;0xfef88090U
DECL|macro|MCPN765_BOARD_MODRST_REG
mdefine_line|#define&t;MCPN765_BOARD_MODRST_REG&t;0xfef880a0U
DECL|macro|MCPN765_BOARD_TBEN_REG
mdefine_line|#define&t;MCPN765_BOARD_TBEN_REG&t;&t;0xfef880c0U
DECL|macro|MCPN765_BOARD_GEOGRAPHICAL_REG
mdefine_line|#define&t;MCPN765_BOARD_GEOGRAPHICAL_REG&t;0xfef880e8U
DECL|macro|MCPN765_BOARD_EXT_FEATURE_REG
mdefine_line|#define&t;MCPN765_BOARD_EXT_FEATURE_REG&t;0xfef880f0U
DECL|macro|MCPN765_BOARD_LAST_RESET_REG
mdefine_line|#define&t;MCPN765_BOARD_LAST_RESET_REG&t;0xfef880f8U
multiline_comment|/* UART base addresses are defined in &lt;asm-ppc/platforms/mcpn765_serial.h&gt; */
multiline_comment|/* Define the NVRAM/RTC address strobe &amp; data registers */
DECL|macro|MCPN765_PHYS_NVRAM_AS0
mdefine_line|#define MCPN765_PHYS_NVRAM_AS0          0xfef880c8U
DECL|macro|MCPN765_PHYS_NVRAM_AS1
mdefine_line|#define MCPN765_PHYS_NVRAM_AS1          0xfef880d0U
DECL|macro|MCPN765_PHYS_NVRAM_DATA
mdefine_line|#define MCPN765_PHYS_NVRAM_DATA         0xfef880d8U
r_extern
r_void
id|mcpn765_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __PPC_PLATFORMS_MCPN765_H */
eof
