multiline_comment|/*&n; * arch/ppc/platforms/4xx/ibmnp405h.h&n; *&n; * Author: Armin Kuster &lt;akuster@mvista.com&gt;&n; *&n; * 2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBMNP405H_H__
DECL|macro|__ASM_IBMNP405H_H__
mdefine_line|#define __ASM_IBMNP405H_H__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* ibm405.h at bottom of this file */
DECL|macro|PPC405_PCI_CONFIG_ADDR
mdefine_line|#define PPC405_PCI_CONFIG_ADDR&t;0xeec00000
DECL|macro|PPC405_PCI_CONFIG_DATA
mdefine_line|#define PPC405_PCI_CONFIG_DATA&t;0xeec00004
DECL|macro|PPC405_PCI_PHY_MEM_BASE
mdefine_line|#define PPC405_PCI_PHY_MEM_BASE&t;0x80000000&t;/* hose_a-&gt;pci_mem_offset */
multiline_comment|/* setbat */
DECL|macro|PPC405_PCI_MEM_BASE
mdefine_line|#define PPC405_PCI_MEM_BASE&t;PPC405_PCI_PHY_MEM_BASE&t;/* setbat */
DECL|macro|PPC405_PCI_PHY_IO_BASE
mdefine_line|#define PPC405_PCI_PHY_IO_BASE&t;0xe8000000&t;/* setbat */
DECL|macro|PPC405_PCI_IO_BASE
mdefine_line|#define PPC405_PCI_IO_BASE&t;PPC405_PCI_PHY_IO_BASE&t;/* setbat */
DECL|macro|PPC405_PCI_LOWER_MEM
mdefine_line|#define PPC405_PCI_LOWER_MEM&t;0x00000000&t;/* hose_a-&gt;mem_space.start */
DECL|macro|PPC405_PCI_UPPER_MEM
mdefine_line|#define PPC405_PCI_UPPER_MEM&t;0xBfffffff&t;/* hose_a-&gt;mem_space.end */
DECL|macro|PPC405_PCI_LOWER_IO
mdefine_line|#define PPC405_PCI_LOWER_IO&t;0x00000000&t;/* hose_a-&gt;io_space.start */
DECL|macro|PPC405_PCI_UPPER_IO
mdefine_line|#define PPC405_PCI_UPPER_IO&t;0x0000ffff&t;/* hose_a-&gt;io_space.end */
DECL|macro|PPC405_ISA_IO_BASE
mdefine_line|#define PPC405_ISA_IO_BASE&t;PPC405_PCI_IO_BASE
DECL|macro|PPC4xx_PCI_IO_ADDR
mdefine_line|#define PPC4xx_PCI_IO_ADDR&t;((uint)PPC405_PCI_PHY_IO_BASE)
DECL|macro|PPC4xx_PCI_IO_SIZE
mdefine_line|#define PPC4xx_PCI_IO_SIZE&t;((uint)64*1024)
DECL|macro|PPC4xx_PCI_CFG_ADDR
mdefine_line|#define PPC4xx_PCI_CFG_ADDR&t;((uint)PPC405_PCI_CONFIG_ADDR)
DECL|macro|PPC4xx_PCI_CFG_SIZE
mdefine_line|#define PPC4xx_PCI_CFG_SIZE&t;((uint)4*1024)
DECL|macro|PPC4xx_PCI_LCFG_ADDR
mdefine_line|#define PPC4xx_PCI_LCFG_ADDR&t;((uint)0xef400000)
DECL|macro|PPC4xx_PCI_LCFG_SIZE
mdefine_line|#define PPC4xx_PCI_LCFG_SIZE&t;((uint)4*1024)
DECL|macro|PPC4xx_ONB_IO_ADDR
mdefine_line|#define PPC4xx_ONB_IO_ADDR&t;((uint)0xef600000)
DECL|macro|PPC4xx_ONB_IO_SIZE
mdefine_line|#define PPC4xx_ONB_IO_SIZE&t;((uint)4*1024)
multiline_comment|/* serial port defines */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;4
DECL|macro|UART0_INT
mdefine_line|#define UART0_INT&t;0
DECL|macro|UART1_INT
mdefine_line|#define UART1_INT&t;1
DECL|macro|PCIL0_BASE
mdefine_line|#define PCIL0_BASE&t;0xEF400000
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE&t;0xEF600300
DECL|macro|UART1_IO_BASE
mdefine_line|#define UART1_IO_BASE&t;0xEF600400
DECL|macro|OPB0_BASE
mdefine_line|#define OPB0_BASE&t;0xEF600600
DECL|macro|EMAC0_BASE
mdefine_line|#define EMAC0_BASE&t;0xEF600800
DECL|macro|BD_EMAC_ADDR
mdefine_line|#define BD_EMAC_ADDR(e,i) bi_enetaddr[e][i]
DECL|macro|STD_UART_OP
mdefine_line|#define STD_UART_OP(num)&t;&t;&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0, UART##num##_INT,&t;&t;&t;&bslash;&n;&t;&t;(ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST),&t;&bslash;&n;&t;&t;iomem_base:(u8 *) UART##num##_IO_BASE,&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM},
macro_line|#if defined(CONFIG_UART0_TTYS0)
DECL|macro|SERIAL_DEBUG_IO_BASE
mdefine_line|#define SERIAL_DEBUG_IO_BASE&t;UART0_IO_BASE
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS        &bslash;&n;        STD_UART_OP(0)          &bslash;&n;        STD_UART_OP(1)
macro_line|#endif
macro_line|#if defined(CONFIG_UART0_TTYS1)
DECL|macro|SERIAL_DEBUG_IO_BASE
mdefine_line|#define SERIAL_DEBUG_IO_BASE&t;UART0_IO_BASE
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS        &bslash;&n;        STD_UART_OP(1)          &bslash;&n;        STD_UART_OP(0)
macro_line|#endif
multiline_comment|/* DCR defines */
multiline_comment|/* ------------------------------------------------------------------------- */
DECL|macro|DCRN_CHCR_BASE
mdefine_line|#define DCRN_CHCR_BASE&t;0x0F1
DECL|macro|DCRN_CHPSR_BASE
mdefine_line|#define DCRN_CHPSR_BASE&t;0x0B4
DECL|macro|DCRN_CPMSR_BASE
mdefine_line|#define DCRN_CPMSR_BASE&t;0x0BA
DECL|macro|DCRN_CPMFR_BASE
mdefine_line|#define DCRN_CPMFR_BASE&t;0x0B9
DECL|macro|DCRN_CPMER_BASE
mdefine_line|#define DCRN_CPMER_BASE&t;0x0B8
multiline_comment|/* CPM Clocking &amp; Power Mangement defines */
DECL|macro|IBM_CPM_PCI
mdefine_line|#define IBM_CPM_PCI&t;&t;0x40000000&t;/* PCI */
DECL|macro|IBM_CPM_EMAC2
mdefine_line|#define IBM_CPM_EMAC2&t;0x20000000&t;/* EMAC 2 MII */
DECL|macro|IBM_CPM_EMAC3
mdefine_line|#define IBM_CPM_EMAC3&t;0x04000000&t;/* EMAC 3 MII */
DECL|macro|IBM_CPM_EMAC0
mdefine_line|#define IBM_CPM_EMAC0&t;0x00800000&t;/* EMAC 0 MII */
DECL|macro|IBM_CPM_EMAC1
mdefine_line|#define IBM_CPM_EMAC1&t;0x00100000&t;/* EMAC 1 MII */
DECL|macro|IBM_CPM_EMMII
mdefine_line|#define IBM_CPM_EMMII&t;0&t;/* Shift value for MII */
DECL|macro|IBM_CPM_EMRX
mdefine_line|#define IBM_CPM_EMRX&t;1&t;/* Shift value for recv */
DECL|macro|IBM_CPM_EMTX
mdefine_line|#define IBM_CPM_EMTX&t;2&t;/* Shift value for MAC */
DECL|macro|IBM_CPM_UIC1
mdefine_line|#define IBM_CPM_UIC1&t;0x00020000&t;/* Universal Interrupt Controller */
DECL|macro|IBM_CPM_UIC0
mdefine_line|#define IBM_CPM_UIC0&t;0x00010000&t;/* Universal Interrupt Controller */
DECL|macro|IBM_CPM_CPU
mdefine_line|#define IBM_CPM_CPU&t;0x00008000&t;/* processor core */
DECL|macro|IBM_CPM_EBC
mdefine_line|#define IBM_CPM_EBC&t;0x00004000&t;/* ROM/SRAM peripheral controller */
DECL|macro|IBM_CPM_SDRAM0
mdefine_line|#define IBM_CPM_SDRAM0&t;0x00002000&t;/* SDRAM memory controller */
DECL|macro|IBM_CPM_GPIO0
mdefine_line|#define IBM_CPM_GPIO0&t;0x00001000&t;/* General Purpose IO (??) */
DECL|macro|IBM_CPM_HDLC
mdefine_line|#define IBM_CPM_HDLC&t;0x00000800&t;/* HDCL */
DECL|macro|IBM_CPM_TMRCLK
mdefine_line|#define IBM_CPM_TMRCLK&t;0x00000400&t;/* CPU timers */
DECL|macro|IBM_CPM_PLB
mdefine_line|#define IBM_CPM_PLB&t;0x00000100&t;/* PLB bus arbiter */
DECL|macro|IBM_CPM_OPB
mdefine_line|#define IBM_CPM_OPB&t;0x00000080&t;/* PLB to OPB bridge */
DECL|macro|IBM_CPM_DMA
mdefine_line|#define IBM_CPM_DMA&t;0x00000040&t;/* DMA controller */
DECL|macro|IBM_CPM_IIC0
mdefine_line|#define IBM_CPM_IIC0&t;0x00000010&t;/* IIC interface */
DECL|macro|IBM_CPM_UART0
mdefine_line|#define IBM_CPM_UART0&t;0x00000002&t;/* serial port 0 */
DECL|macro|IBM_CPM_UART1
mdefine_line|#define IBM_CPM_UART1&t;0x00000001&t;/* serial port 1 */
multiline_comment|/* this is the default setting for devices put to sleep when booting */
DECL|macro|DFLT_IBM4xx_PM
mdefine_line|#define DFLT_IBM4xx_PM&t;~(IBM_CPM_UIC0 | IBM_CPM_UIC1 | IBM_CPM_CPU &t;&bslash;&n;&t;&t;&t;| IBM_CPM_EBC | IBM_CPM_SDRAM0 | IBM_CPM_PLB &t;&bslash;&n;&t;&t;&t;| IBM_CPM_OPB | IBM_CPM_TMRCLK | IBM_CPM_DMA&t;&bslash;&n;&t;&t;&t;| IBM_CPM_EMAC0 | IBM_CPM_EMAC1 | IBM_CPM_EMAC2&t;&bslash;&n;&t;&t;&t;| IBM_CPM_EMAC3 | IBM_CPM_PCI)
DECL|macro|DCRN_DMA0_BASE
mdefine_line|#define DCRN_DMA0_BASE&t;0x100
DECL|macro|DCRN_DMA1_BASE
mdefine_line|#define DCRN_DMA1_BASE&t;0x108
DECL|macro|DCRN_DMA2_BASE
mdefine_line|#define DCRN_DMA2_BASE&t;0x110
DECL|macro|DCRN_DMA3_BASE
mdefine_line|#define DCRN_DMA3_BASE&t;0x118
DECL|macro|DCRNCAP_DMA_SG
mdefine_line|#define DCRNCAP_DMA_SG&t;1&t;/* have DMA scatter/gather capability */
DECL|macro|DCRN_DMASR_BASE
mdefine_line|#define DCRN_DMASR_BASE&t;0x120
DECL|macro|DCRN_EBC_BASE
mdefine_line|#define DCRN_EBC_BASE&t;0x012
DECL|macro|DCRN_DCP0_BASE
mdefine_line|#define DCRN_DCP0_BASE&t;0x014
DECL|macro|DCRN_MAL_BASE
mdefine_line|#define DCRN_MAL_BASE&t;0x180
DECL|macro|DCRN_OCM0_BASE
mdefine_line|#define DCRN_OCM0_BASE&t;0x018
DECL|macro|DCRN_PLB0_BASE
mdefine_line|#define DCRN_PLB0_BASE&t;0x084
DECL|macro|DCRN_PLLMR_BASE
mdefine_line|#define DCRN_PLLMR_BASE&t;0x0B0
DECL|macro|DCRN_POB0_BASE
mdefine_line|#define DCRN_POB0_BASE&t;0x0A0
DECL|macro|DCRN_SDRAM0_BASE
mdefine_line|#define DCRN_SDRAM0_BASE 0x010
DECL|macro|DCRN_UIC0_BASE
mdefine_line|#define DCRN_UIC0_BASE&t;0x0C0
DECL|macro|DCRN_UIC1_BASE
mdefine_line|#define DCRN_UIC1_BASE&t;0x0D0
DECL|macro|DCRN_CPC0_EPRCSR
mdefine_line|#define DCRN_CPC0_EPRCSR 0x0F3
DECL|macro|UIC0_UIC1NC
mdefine_line|#define UIC0_UIC1NC&t;0x00000002
DECL|macro|CHR1_CETE
mdefine_line|#define CHR1_CETE&t;0x00000004&t;/* CPU external timer enable */
DECL|macro|UIC0
mdefine_line|#define UIC0&t;DCRN_UIC0_BASE
DECL|macro|UIC1
mdefine_line|#define UIC1&t;DCRN_UIC1_BASE
DECL|macro|NR_UICS
macro_line|#undef NR_UICS
DECL|macro|NR_UICS
mdefine_line|#define NR_UICS&t;2
multiline_comment|/* EMAC DCRN&squot;s FIXME: armin */
DECL|macro|DCRN_MALRXCTP2R
mdefine_line|#define DCRN_MALRXCTP2R(base)&t;((base) + 0x42)&t;/* Channel Rx 2 Channel Table Pointer */
DECL|macro|DCRN_MALRXCTP3R
mdefine_line|#define DCRN_MALRXCTP3R(base)&t;((base) + 0x43)&t;/* Channel Rx 3 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP4R
mdefine_line|#define DCRN_MALTXCTP4R(base)&t;((base) + 0x24)&t;/* Channel Tx 4 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP5R
mdefine_line|#define DCRN_MALTXCTP5R(base)&t;((base) + 0x25)&t;/* Channel Tx 5 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP6R
mdefine_line|#define DCRN_MALTXCTP6R(base)&t;((base) + 0x26)&t;/* Channel Tx 6 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP7R
mdefine_line|#define DCRN_MALTXCTP7R(base)&t;((base) + 0x27)&t;/* Channel Tx 7 Channel Table Pointer */
DECL|macro|DCRN_MALRCBS2
mdefine_line|#define DCRN_MALRCBS2(base)&t;((base) + 0x62)&t;/* Channel Rx 2 Channel Buffer Size */
DECL|macro|DCRN_MALRCBS3
mdefine_line|#define DCRN_MALRCBS3(base)&t;((base) + 0x63)&t;/* Channel Rx 3 Channel Buffer Size */
macro_line|#include &lt;asm/ibm405.h&gt;
macro_line|#endif&t;&t;&t;&t;/* __ASM_IBMNP405H_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
