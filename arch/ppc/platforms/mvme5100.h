multiline_comment|/*&n; * include/asm-ppc/platforms/mvme5100.h&n; * &n; * Definitions for Motorola MVME5100.&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_MVME5100_H__
DECL|macro|__ASM_MVME5100_H__
mdefine_line|#define __ASM_MVME5100_H__
DECL|macro|MVME5100_HAWK_SMC_BASE
mdefine_line|#define MVME5100_HAWK_SMC_BASE&t;&t;0xfef80000
DECL|macro|MVME5100_PCI_CONFIG_ADDR
mdefine_line|#define&t;MVME5100_PCI_CONFIG_ADDR&t;0xfe000cf8
DECL|macro|MVME5100_PCI_CONFIG_DATA
mdefine_line|#define&t;MVME5100_PCI_CONFIG_DATA&t;0xfe000cfc
DECL|macro|MVME5100_PCI_IO_BASE
mdefine_line|#define MVME5100_PCI_IO_BASE&t;&t;0xfe000000
DECL|macro|MVME5100_PCI_MEM_BASE
mdefine_line|#define MVME5100_PCI_MEM_BASE&t;&t;0x80000000
DECL|macro|MVME5100_PCI_MEM_OFFSET
mdefine_line|#define MVME5100_PCI_MEM_OFFSET&t;&t;0x00000000
DECL|macro|MVME5100_PCI_DRAM_OFFSET
mdefine_line|#define MVME5100_PCI_DRAM_OFFSET&t;0x00000000
DECL|macro|MVME5100_ISA_MEM_BASE
mdefine_line|#define MVME5100_ISA_MEM_BASE&t;&t;0x00000000
DECL|macro|MVME5100_ISA_IO_BASE
mdefine_line|#define MVME5100_ISA_IO_BASE&t;&t;MVME5100_PCI_IO_BASE
DECL|macro|MVME5100_PCI_LOWER_MEM
mdefine_line|#define MVME5100_PCI_LOWER_MEM&t;&t;0x80000000
DECL|macro|MVME5100_PCI_UPPER_MEM
mdefine_line|#define MVME5100_PCI_UPPER_MEM&t;&t;0xf3f7ffff
DECL|macro|MVME5100_PCI_LOWER_IO
mdefine_line|#define MVME5100_PCI_LOWER_IO&t;&t;0x00000000
DECL|macro|MVME5100_PCI_UPPER_IO
mdefine_line|#define MVME5100_PCI_UPPER_IO&t;&t;0x0077ffff
multiline_comment|/* MVME5100 board register addresses. */
DECL|macro|MVME5100_BOARD_STATUS_REG
mdefine_line|#define&t;MVME5100_BOARD_STATUS_REG&t;0xfef88080
DECL|macro|MVME5100_BOARD_MODFAIL_REG
mdefine_line|#define&t;MVME5100_BOARD_MODFAIL_REG&t;0xfef88090
DECL|macro|MVME5100_BOARD_MODRST_REG
mdefine_line|#define&t;MVME5100_BOARD_MODRST_REG&t;0xfef880a0
DECL|macro|MVME5100_BOARD_TBEN_REG
mdefine_line|#define&t;MVME5100_BOARD_TBEN_REG&t;&t;0xfef880c0
DECL|macro|MVME5100_BOARD_SW_READ_REG
mdefine_line|#define MVME5100_BOARD_SW_READ_REG&t;0xfef880e0
DECL|macro|MVME5100_BOARD_GEO_ADDR_REG
mdefine_line|#define&t;MVME5100_BOARD_GEO_ADDR_REG&t;0xfef880e8
DECL|macro|MVME5100_BOARD_EXT_FEATURE1_REG
mdefine_line|#define&t;MVME5100_BOARD_EXT_FEATURE1_REG&t;0xfef880f0
DECL|macro|MVME5100_BOARD_EXT_FEATURE2_REG
mdefine_line|#define&t;MVME5100_BOARD_EXT_FEATURE2_REG&t;0xfef88100
multiline_comment|/* Define the NVRAM/RTC address strobe &amp; data registers */
DECL|macro|MVME5100_PHYS_NVRAM_AS0
mdefine_line|#define MVME5100_PHYS_NVRAM_AS0&t;&t;0xfef880c8
DECL|macro|MVME5100_PHYS_NVRAM_AS1
mdefine_line|#define MVME5100_PHYS_NVRAM_AS1&t;&t;0xfef880d0
DECL|macro|MVME5100_PHYS_NVRAM_DATA
mdefine_line|#define MVME5100_PHYS_NVRAM_DATA&t;0xfef880d8
DECL|macro|MVME5100_NVRAM_AS0
mdefine_line|#define MVME5100_NVRAM_AS0&t;(MVME5100_PHYS_NVRAM_AS0 - MVME5100_ISA_IO_BASE)
DECL|macro|MVME5100_NVRAM_AS1
mdefine_line|#define MVME5100_NVRAM_AS1&t;(MVME5100_PHYS_NVRAM_AS1 - MVME5100_ISA_IO_BASE)
DECL|macro|MVME5100_NVRAM_DATA
mdefine_line|#define MVME5100_NVRAM_DATA&t;(MVME5100_PHYS_NVRAM_DATA - MVME5100_ISA_IO_BASE)
multiline_comment|/* UART clock, addresses, and irq */
DECL|macro|MVME5100_BASE_BAUD
mdefine_line|#define MVME5100_BASE_BAUD&t;&t;1843200
DECL|macro|MVME5100_SERIAL_1
mdefine_line|#define&t;MVME5100_SERIAL_1&t;&t;0xfef88000
DECL|macro|MVME5100_SERIAL_2
mdefine_line|#define&t;MVME5100_SERIAL_2&t;&t;0xfef88200
macro_line|#ifdef CONFIG_MVME5100_IPMC761_PRESENT
DECL|macro|MVME5100_SERIAL_IRQ
mdefine_line|#define MVME5100_SERIAL_IRQ&t;&t;17
macro_line|#else
DECL|macro|MVME5100_SERIAL_IRQ
mdefine_line|#define MVME5100_SERIAL_IRQ&t;&t;1
macro_line|#endif
DECL|macro|MVME5100_WINBOND_DEVFN
mdefine_line|#define MVME5100_WINBOND_DEVFN&t;&t;0x58
DECL|macro|MVME5100_WINBOND_VIDDID
mdefine_line|#define MVME5100_WINBOND_VIDDID&t;&t;0x056510ad
r_extern
r_void
id|mvme5100_setup_bridge
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASM_MVME5100_H__ */
macro_line|#endif /* __KERNEL__ */
eof
