multiline_comment|/*&n; * include/asm-ppc/platforms/powerpmc250.h&n; *&n; * Definitions for Force PowerPMC-250 board support&n; *&n; * Author: Troy Benjegerdes &lt;tbenjegerdes@mvista.com&gt;&n; *&n; * Borrowed heavily from prpmc750.h by Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2001-2004 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef __ASMPPC_POWERPMC250_H
DECL|macro|__ASMPPC_POWERPMC250_H
mdefine_line|#define __ASMPPC_POWERPMC250_H
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
multiline_comment|/* UART Defines. */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  1
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD  (POWERPMC250_BASE_BAUD / 16)
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS ASYNC_BOOT_AUTOCONF
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;&t;{ 0, BASE_BAUD, POWERPMC250_SERIAL, POWERPMC250_SERIAL_IRQ,&t;&bslash;&n;&t;&t;STD_COM_FLAGS, &t;&t;&t;&t;/* ttyS0 */&t;&bslash;&n;&t;&t;iomem_base: (u8 *)POWERPMC250_SERIAL,&t;&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 0,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM }
macro_line|#endif /* __ASMPPC_POWERPMC250_H */
eof
