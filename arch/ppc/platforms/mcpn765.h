multiline_comment|/*&n; * arch/ppc/platforms/mcpn765.h&n; *&n; * Definitions for Motorola MCG MCPN765 cPCI Board.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * 2001-2004 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * From Processor to PCI:&n; *   PCI Mem Space: 0x80000000 - 0xc0000000 -&gt; 0x80000000 - 0xc0000000 (1 GB)&n; *   PCI I/O Space: 0xfd800000 - 0xfe000000 -&gt; 0x00000000 - 0x00800000 (8 MB)&n; *&t;Note: Must skip 0xfe000000-0xfe400000 for CONFIG_HIGHMEM/PKMAP area&n; *   MPIC in PCI Mem Space: 0xfe800000 - 0xfe830000 (not all used by MPIC)&n; *&n; * From PCI to Processor:&n; *   System Memory: 0x00000000 -&gt; 0x00000000&n; */
macro_line|#ifndef __PPC_PLATFORMS_MCPN765_H
DECL|macro|__PPC_PLATFORMS_MCPN765_H
mdefine_line|#define __PPC_PLATFORMS_MCPN765_H
macro_line|#include &lt;linux/config.h&gt;
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
multiline_comment|/* Defines for UART */
multiline_comment|/* Define the UART base addresses */
DECL|macro|MCPN765_SERIAL_1
mdefine_line|#define&t;MCPN765_SERIAL_1&t;&t;0xfef88000
DECL|macro|MCPN765_SERIAL_2
mdefine_line|#define&t;MCPN765_SERIAL_2&t;&t;0xfef88200
DECL|macro|MCPN765_SERIAL_3
mdefine_line|#define&t;MCPN765_SERIAL_3&t;&t;0xfef88400
DECL|macro|MCPN765_SERIAL_4
mdefine_line|#define&t;MCPN765_SERIAL_4&t;&t;0xfef88600
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
macro_line|#endif
multiline_comment|/* Rate for the 1.8432 Mhz clock for the onboard serial chip */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;( 1843200 / 16 )
DECL|macro|UART_CLK
mdefine_line|#define UART_CLK&t;1843200
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
multiline_comment|/* All UART IRQ&squot;s are wire-OR&squot;d to IRQ 17 */
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, MCPN765_SERIAL_1, 17, STD_COM_FLAGS, /* ttyS0 */&bslash;&n;&t;&t;iomem_base: (u8 *)MCPN765_SERIAL_1,&t;&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 4,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },&t;&t;&t;&t;&bslash;&n;        { 0, BASE_BAUD, MCPN765_SERIAL_2, 17, STD_COM_FLAGS, /* ttyS1 */&bslash;&n;&t;&t;iomem_base: (u8 *)MCPN765_SERIAL_2,&t;&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 4,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },&t;&t;&t;&t;&bslash;&n;        { 0, BASE_BAUD, MCPN765_SERIAL_3, 17, STD_COM_FLAGS, /* ttyS2 */&bslash;&n;&t;&t;iomem_base: (u8 *)MCPN765_SERIAL_3,&t;&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 4,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },&t;&t;&t;&t;&bslash;&n;        { 0, BASE_BAUD, MCPN765_SERIAL_4, 17, STD_COM_FLAGS, /* ttyS3 */&bslash;&n;&t;&t;iomem_base: (u8 *)MCPN765_SERIAL_4,&t;&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 4,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
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
