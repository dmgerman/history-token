multiline_comment|/*&n; * include/asm-ppc/platforms/powerpmc250.h&n; * &n; * Definitions for Force PowerPMC-250 board support&n; *&n; * Author: Troy Benjegerdes &lt;tbenjegerdes@mvista.com&gt;&n; * &n; * Borrowed heavily from prpmc750.h by Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __ASMPPC_POWERPMC250_H
DECL|macro|__ASMPPC_POWERPMC250_H
mdefine_line|#define __ASMPPC_POWERPMC250_H
macro_line|#include &lt;linux/serial_reg.h&gt;
DECL|macro|POWERPMC250_PCI_CONFIG_ADDR
mdefine_line|#define POWERPMC250_PCI_CONFIG_ADDR&t;0x80000cf8
DECL|macro|POWERPMC250_PCI_CONFIG_DATA
mdefine_line|#define POWERPMC250_PCI_CONFIG_DATA&t;0x80000cfc
DECL|macro|POWERPMC250_PCI_PHY_MEM_BASE
mdefine_line|#define POWERPMC250_PCI_PHY_MEM_BASE&t;0xc0000000
DECL|macro|POWERPMC250_PCI_MEM_BASE
mdefine_line|#define POWERPMC250_PCI_MEM_BASE&t;&t;0xf0000000
DECL|macro|POWERPMC250_PCI_IO_BASE
mdefine_line|#define POWERPMC250_PCI_IO_BASE&t;&t;0x80000000
DECL|macro|POWERPMC250_ISA_IO_BASE
mdefine_line|#define POWERPMC250_ISA_IO_BASE&t;&t;POWERPMC250_PCI_IO_BASE
DECL|macro|POWERPMC250_ISA_MEM_BASE
mdefine_line|#define POWERPMC250_ISA_MEM_BASE&t;&t;POWERPMC250_PCI_MEM_BASE
DECL|macro|POWERPMC250_PCI_MEM_OFFSET
mdefine_line|#define POWERPMC250_PCI_MEM_OFFSET&t;&t;POWERPMC250_PCI_PHY_MEM_BASE
DECL|macro|POWERPMC250_SYS_MEM_BASE
mdefine_line|#define POWERPMC250_SYS_MEM_BASE&t;&t;0x80000000
DECL|macro|POWERPMC250_HAWK_SMC_BASE
mdefine_line|#define POWERPMC250_HAWK_SMC_BASE&t;&t;0xfef80000
DECL|macro|POWERPMC250_BASE_BAUD
mdefine_line|#define POWERPMC250_BASE_BAUD&t;&t;12288000
DECL|macro|POWERPMC250_SERIAL
mdefine_line|#define POWERPMC250_SERIAL&t;&t;0xff000000
DECL|macro|POWERPMC250_SERIAL_IRQ
mdefine_line|#define POWERPMC250_SERIAL_IRQ&t;&t;20
macro_line|#endif /* __ASMPPC_POWERPMC250_H */
eof
