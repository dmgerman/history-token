multiline_comment|/*&n; * include/asm-ppc/platforms/prpmc800.h&n; *&n; * Definitions for Motorola PrPMC800 board support&n; *&n; * Author: Dale Farnsworth &lt;dale.farnsworth@mvista.com&gt;&n; *&n; * 2001-2004 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n;  * From Processor to PCI:&n;  *   PCI Mem Space: 0x80000000 - 0xa0000000 -&gt; 0x80000000 - 0xa0000000 (512 MB)&n;  *   PCI I/O Space: 0xfe400000 - 0xfeef0000 -&gt; 0x00000000 - 0x00b00000 (11 MB)&n;  *      Note: Must skip 0xfe000000-0xfe400000 for CONFIG_HIGHMEM/PKMAP area&n;  *&n;  * From PCI to Processor:&n;  *   System Memory: 0x00000000 -&gt; 0x00000000&n;  */
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
DECL|macro|PRPMC800_NM_PROC_PCI_MEM_START
mdefine_line|#define PRPMC800_NM_PROC_PCI_MEM_START&t;&t;0x40000000U
DECL|macro|PRPMC800_NM_PROC_PCI_MEM_END
mdefine_line|#define PRPMC800_NM_PROC_PCI_MEM_END&t;&t;0xdfffffffU
DECL|macro|PRPMC800_NM_PCI_MEM_START
mdefine_line|#define PRPMC800_NM_PCI_MEM_START&t;&t;0x40000000U
DECL|macro|PRPMC800_NM_PCI_MEM_END
mdefine_line|#define PRPMC800_NM_PCI_MEM_END&t;&t;&t;0xdfffffffU
DECL|macro|PRPMC800_PCI_DRAM_OFFSET
mdefine_line|#define PRPMC800_PCI_DRAM_OFFSET&t;&t;0x00000000U
DECL|macro|PRPMC800_PCI_PHY_MEM_OFFSET
mdefine_line|#define PRPMC800_PCI_PHY_MEM_OFFSET&t;&t;0x00000000U
DECL|macro|PRPMC800_ISA_IO_BASE
mdefine_line|#define PRPMC800_ISA_IO_BASE&t;&t;&t;PRPMC800_PROC_PCI_IO_START
DECL|macro|PRPMC800_ISA_MEM_BASE
mdefine_line|#define PRPMC800_ISA_MEM_BASE&t;&t;&t;0x00000000U
DECL|macro|PRPMC800_HARRIER_XCSR_BASE
mdefine_line|#define PRPMC800_HARRIER_XCSR_BASE&t;&t;HARRIER_DEFAULT_XCSR_BASE
DECL|macro|PRPMC800_HARRIER_MPIC_BASE
mdefine_line|#define PRPMC800_HARRIER_MPIC_BASE&t;&t;0xff000000
DECL|macro|PRPMC800_SERIAL_1
mdefine_line|#define PRPMC800_SERIAL_1&t;&t;&t;0xfeff00c0
DECL|macro|PRPMC800_BASE_BAUD
mdefine_line|#define PRPMC800_BASE_BAUD&t;&t;&t;1843200
multiline_comment|/*&n; * interrupt vector number and priority for harrier internal interrupt&n; * sources&n; */
DECL|macro|PRPMC800_INT_IRQ
mdefine_line|#define PRPMC800_INT_IRQ&t;&t;&t;16
DECL|macro|PRPMC800_INT_PRI
mdefine_line|#define PRPMC800_INT_PRI&t;&t;&t;15
multiline_comment|/* UART Defines. */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
multiline_comment|/* Rate for the 1.8432 Mhz clock for the onboard serial chip */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (PRPMC800_BASE_BAUD / 16)
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS ASYNC_BOOT_AUTOCONF
multiline_comment|/* UARTS are at IRQ 16 */
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, PRPMC800_SERIAL_1, 16, STD_COM_FLAGS, /* ttyS0 */&bslash;&n;&t;&t;iomem_base: (unsigned char *)PRPMC800_SERIAL_1,&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 0,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
macro_line|#endif&t;&t;&t;&t;/* __ASMPPC_PRPMC800_H */
eof
