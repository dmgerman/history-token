multiline_comment|/*&n; * include/asm-ppc/platforms/prpmc750.h&n; *&n; * Definitions for Motorola PrPMC750 board support&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PRPMC750_H__
DECL|macro|__ASM_PRPMC750_H__
mdefine_line|#define __ASM_PRPMC750_H__
macro_line|#include &lt;linux/serial_reg.h&gt;
multiline_comment|/*&n; * Due to limiations imposed by legacy hardware (primaryily IDE controllers),&n; * the PrPMC750 carrier board operates using a PReP address map.&n; *&n; * From Processor (physical) -&gt; PCI:&n; *   PCI Mem Space: 0xc0000000 - 0xfe000000 -&gt; 0x00000000 - 0x3e000000 (768 MB)&n; *   PCI I/O Space: 0x80000000 - 0x90000000 -&gt; 0x00000000 - 0x10000000 (256 MB)&n; *&t;Note: Must skip 0xfe000000-0xfe400000 for CONFIG_HIGHMEM/PKMAP area&n; *&n; * From PCI -&gt; Processor (physical):&n; *   System Memory: 0x80000000 -&gt; 0x00000000&n; */
DECL|macro|PRPMC750_ISA_IO_BASE
mdefine_line|#define PRPMC750_ISA_IO_BASE&t;&t;PREP_ISA_IO_BASE
DECL|macro|PRPMC750_ISA_MEM_BASE
mdefine_line|#define PRPMC750_ISA_MEM_BASE&t;&t;PREP_ISA_MEM_BASE
multiline_comment|/* PCI Memory space mapping info */
DECL|macro|PRPMC750_PCI_MEM_SIZE
mdefine_line|#define PRPMC750_PCI_MEM_SIZE&t;&t;0x30000000U
DECL|macro|PRPMC750_PROC_PCI_MEM_START
mdefine_line|#define PRPMC750_PROC_PCI_MEM_START&t;PRPMC750_ISA_MEM_BASE
DECL|macro|PRPMC750_PROC_PCI_MEM_END
mdefine_line|#define PRPMC750_PROC_PCI_MEM_END&t;(PRPMC750_PROC_PCI_MEM_START +&t;&bslash;&n;&t;&t;&t;&t;&t; PRPMC750_PCI_MEM_SIZE - 1)
DECL|macro|PRPMC750_PCI_MEM_START
mdefine_line|#define PRPMC750_PCI_MEM_START&t;&t;0x00000000U
DECL|macro|PRPMC750_PCI_MEM_END
mdefine_line|#define PRPMC750_PCI_MEM_END&t;&t;(PRPMC750_PCI_MEM_START +&t;&bslash;&n;&t;&t;&t;&t;&t; PRPMC750_PCI_MEM_SIZE - 1)
multiline_comment|/* PCI I/O space mapping info */
DECL|macro|PRPMC750_PCI_IO_SIZE
mdefine_line|#define PRPMC750_PCI_IO_SIZE&t;&t;0x10000000U
DECL|macro|PRPMC750_PROC_PCI_IO_START
mdefine_line|#define PRPMC750_PROC_PCI_IO_START&t;PRPMC750_ISA_IO_BASE
DECL|macro|PRPMC750_PROC_PCI_IO_END
mdefine_line|#define PRPMC750_PROC_PCI_IO_END&t;(PRPMC750_PROC_PCI_IO_START +&t;&bslash;&n;&t;&t;&t;&t;&t; PRPMC750_PCI_IO_SIZE - 1)
DECL|macro|PRPMC750_PCI_IO_START
mdefine_line|#define PRPMC750_PCI_IO_START&t;&t;0x00000000U
DECL|macro|PRPMC750_PCI_IO_END
mdefine_line|#define PRPMC750_PCI_IO_END&t;&t;(PRPMC750_PCI_IO_START + &t;&bslash;&n;&t;&t;&t;&t;&t; PRPMC750_PCI_IO_SIZE - 1)
multiline_comment|/* System memory mapping info */
DECL|macro|PRPMC750_PCI_DRAM_OFFSET
mdefine_line|#define PRPMC750_PCI_DRAM_OFFSET&t;PREP_PCI_DRAM_OFFSET
DECL|macro|PRPMC750_PCI_PHY_MEM_OFFSET
mdefine_line|#define PRPMC750_PCI_PHY_MEM_OFFSET&t;(PRPMC750_ISA_MEM_BASE-PRPMC750_PCI_MEM_START)
multiline_comment|/* Register address definitions */
DECL|macro|PRPMC750_HAWK_SMC_BASE
mdefine_line|#define PRPMC750_HAWK_SMC_BASE&t;&t;0xfef80000U
DECL|macro|PRPMC750_HAWK_PPC_REG_BASE
mdefine_line|#define PRPMC750_HAWK_PPC_REG_BASE&t;0xfeff0000U
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
macro_line|#endif&t;&t;&t;&t;/* __ASM_PRPMC750_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
