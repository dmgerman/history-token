multiline_comment|/*&n; * include/asm-ppc/platforms/prpmc750.h&n; * &n; * Definitions for Motorola PrPMC750 board support&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PRPMC750_H__
DECL|macro|__ASM_PRPMC750_H__
mdefine_line|#define __ASM_PRPMC750_H__
macro_line|#include &lt;linux/serial_reg.h&gt;
DECL|macro|PRPMC750_PCI_CONFIG_ADDR
mdefine_line|#define PRPMC750_PCI_CONFIG_ADDR&t;0x80000cf8
DECL|macro|PRPMC750_PCI_CONFIG_DATA
mdefine_line|#define PRPMC750_PCI_CONFIG_DATA&t;0x80000cfc
DECL|macro|PRPMC750_PCI_PHY_MEM_BASE
mdefine_line|#define PRPMC750_PCI_PHY_MEM_BASE&t;0xc0000000
DECL|macro|PRPMC750_PCI_MEM_BASE
mdefine_line|#define PRPMC750_PCI_MEM_BASE&t;&t;0xf0000000
DECL|macro|PRPMC750_PCI_IO_BASE
mdefine_line|#define PRPMC750_PCI_IO_BASE&t;&t;0x80000000
DECL|macro|PRPMC750_ISA_IO_BASE
mdefine_line|#define PRPMC750_ISA_IO_BASE&t;&t;PRPMC750_PCI_IO_BASE
DECL|macro|PRPMC750_ISA_MEM_BASE
mdefine_line|#define PRPMC750_ISA_MEM_BASE&t;&t;PRPMC750_PCI_MEM_BASE
DECL|macro|PRPMC750_PCI_MEM_OFFSET
mdefine_line|#define PRPMC750_PCI_MEM_OFFSET&t;&t;PRPMC750_PCI_PHY_MEM_BASE
DECL|macro|PRPMC750_SYS_MEM_BASE
mdefine_line|#define PRPMC750_SYS_MEM_BASE&t;&t;0x80000000
DECL|macro|PRPMC750_PCI_LOWER_MEM
mdefine_line|#define PRPMC750_PCI_LOWER_MEM&t;&t;0x00000000
DECL|macro|PRPMC750_PCI_UPPER_MEM_AUTO
mdefine_line|#define PRPMC750_PCI_UPPER_MEM_AUTO&t;0x3bf7ffff
DECL|macro|PRPMC750_PCI_UPPER_MEM
mdefine_line|#define PRPMC750_PCI_UPPER_MEM&t;&t;0x3bffffff
DECL|macro|PRPMC750_PCI_LOWER_IO
mdefine_line|#define PRPMC750_PCI_LOWER_IO&t;&t;0x00000000
DECL|macro|PRPMC750_PCI_UPPER_IO
mdefine_line|#define PRPMC750_PCI_UPPER_IO&t;&t;0x0ff7ffff
DECL|macro|PRPMC750_HAWK_MPIC_BASE
mdefine_line|#define PRPMC750_HAWK_MPIC_BASE&t;&t;0xfbf80000
DECL|macro|PRPMC750_HAWK_SMC_BASE
mdefine_line|#define PRPMC750_HAWK_SMC_BASE&t;&t;0xfef80000
DECL|macro|PRPMC750_BASE_BAUD
mdefine_line|#define PRPMC750_BASE_BAUD&t;&t;1843200
DECL|macro|PRPMC750_SERIAL_0
mdefine_line|#define PRPMC750_SERIAL_0&t;&t;0xfef88000
DECL|macro|PRPMC750_SERIAL_0_DLL
mdefine_line|#define PRPMC750_SERIAL_0_DLL&t;&t;(PRPMC750_SERIAL_0 + (UART_DLL &lt;&lt; 4))
DECL|macro|PRPMC750_SERIAL_0_DLM
mdefine_line|#define PRPMC750_SERIAL_0_DLM&t;&t;(PRPMC750_SERIAL_0 + (UART_DLM &lt;&lt; 4))
DECL|macro|PRPMC750_SERIAL_0_LCR
mdefine_line|#define PRPMC750_SERIAL_0_LCR&t;&t;(PRPMC750_SERIAL_0 + (UART_LCR &lt;&lt; 4))
DECL|macro|PRPMC750_STATUS_REG
mdefine_line|#define PRPMC750_STATUS_REG&t;&t;0xfef88080
DECL|macro|PRPMC750_BAUDOUT_MASK
mdefine_line|#define PRPMC750_BAUDOUT_MASK&t;&t;0x02
DECL|macro|PRPMC750_MONARCH_MASK
mdefine_line|#define PRPMC750_MONARCH_MASK&t;&t;0x01
DECL|macro|PRPMC750_MODRST_REG
mdefine_line|#define PRPMC750_MODRST_REG&t;&t;0xfef880a0
DECL|macro|PRPMC750_MODRST_MASK
mdefine_line|#define PRPMC750_MODRST_MASK&t;&t;0x01
DECL|macro|PRPMC750_PIRQ_REG
mdefine_line|#define PRPMC750_PIRQ_REG&t;&t;0xfef880b0
DECL|macro|PRPMC750_SEL1_MASK
mdefine_line|#define PRPMC750_SEL1_MASK&t;&t;0x02
DECL|macro|PRPMC750_SEL0_MASK
mdefine_line|#define PRPMC750_SEL0_MASK&t;&t;0x01
DECL|macro|PRPMC750_TBEN_REG
mdefine_line|#define PRPMC750_TBEN_REG&t;&t;0xfef880c0
DECL|macro|PRPMC750_TBEN_MASK
mdefine_line|#define PRPMC750_TBEN_MASK&t;&t;0x01
macro_line|#endif /* __ASM_PRPMC750_H__ */
macro_line|#endif /* __KERNEL__ */
eof
