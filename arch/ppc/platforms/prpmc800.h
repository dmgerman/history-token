multiline_comment|/*&n; * include/asm-ppc/platforms/prpmc800.h&n; * &n; * Definitions for Motorola PrPMC800 board support&n; *&n; * Author: Dale Farnsworth &lt;dale.farnsworth@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
multiline_comment|/*&n; * From Processor to PCI:&n; *   PCI Mem Space: 0x80000000 - 0xa0000000 -&gt; 0x80000000 - 0xa0000000 (512 MB)&n; *   PCI I/O Space: 0xfe400000 - 0xfeef0000 -&gt; 0x00000000 - 0x00b00000 (11 MB)&n; *      Note: Must skip 0xfe000000-0xfe400000 for CONFIG_HIGHMEM/PKMAP area&n; *&n; * From PCI to Processor:&n; *   System Memory: 0x00000000 -&gt; 0x00000000&n; */
macro_line|#ifndef __ASMPPC_PRPMC800_H
DECL|macro|__ASMPPC_PRPMC800_H
mdefine_line|#define __ASMPPC_PRPMC800_H
DECL|macro|PRPMC800_PCI_CONFIG_ADDR
mdefine_line|#define PRPMC800_PCI_CONFIG_ADDR&t;&t;0xfe000cf8
DECL|macro|PRPMC800_PCI_CONFIG_DATA
mdefine_line|#define PRPMC800_PCI_CONFIG_DATA&t;&t;0xfe000cfc
DECL|macro|PRPMC800_PROC_PCI_IO_START
mdefine_line|#define PRPMC800_PROC_PCI_IO_START&t;&t;0xfe400000U
DECL|macro|PRPMC800_PROC_PCI_IO_END
mdefine_line|#define PRPMC800_PROC_PCI_IO_END&t;&t;0xfeefffffU
DECL|macro|PRPMC800_PCI_IO_START
mdefine_line|#define PRPMC800_PCI_IO_START&t;&t;&t;0x00000000U
DECL|macro|PRPMC800_PCI_IO_END
mdefine_line|#define PRPMC800_PCI_IO_END&t;&t;&t;0x00afffffU
DECL|macro|PRPMC800_PROC_PCI_MEM_START
mdefine_line|#define PRPMC800_PROC_PCI_MEM_START&t;&t;0x80000000U
DECL|macro|PRPMC800_PROC_PCI_MEM_END
mdefine_line|#define PRPMC800_PROC_PCI_MEM_END&t;&t;0x9fffffffU
DECL|macro|PRPMC800_PCI_MEM_START
mdefine_line|#define PRPMC800_PCI_MEM_START&t;&t;&t;0x80000000U
DECL|macro|PRPMC800_PCI_MEM_END
mdefine_line|#define PRPMC800_PCI_MEM_END&t;&t;&t;0x9fffffffU
DECL|macro|PRPMC800_PCI_DRAM_OFFSET
mdefine_line|#define PRPMC800_PCI_DRAM_OFFSET&t;&t;0x00000000U
DECL|macro|PRPMC800_PCI_PHY_MEM_OFFSET
mdefine_line|#define PRPMC800_PCI_PHY_MEM_OFFSET&t;&t;0x00000000U
DECL|macro|PRPMC800_ISA_IO_BASE
mdefine_line|#define PRPMC800_ISA_IO_BASE&t;&t;&t;PRPMC800_PROC_PCI_IO_START
DECL|macro|PRPMC800_ISA_MEM_BASE
mdefine_line|#define PRPMC800_ISA_MEM_BASE&t;&t;&t;0x00000000U
DECL|macro|PRPMC800_HARRIER_XCSR_BASE
mdefine_line|#define PRPMC800_HARRIER_XCSR_BASE&t;&t;0xfeff0000
DECL|macro|PRPMC800_HARRIER_MPIC_BASE
mdefine_line|#define PRPMC800_HARRIER_MPIC_BASE&t;&t;0xff000000
DECL|macro|PRPMC800_SERIAL_1
mdefine_line|#define PRPMC800_SERIAL_1&t;&t;&t;0xfeff00c0
DECL|macro|PRPMC800_BASE_BAUD
mdefine_line|#define PRPMC800_BASE_BAUD&t;&t;&t;1843200
macro_line|#endif /* __ASMPPC_PRPMC800_H */
eof
