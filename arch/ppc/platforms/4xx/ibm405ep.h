multiline_comment|/*&n; * arch/ppc/platforms/4xx/ibm405ep.h&n; *&n; * IBM PPC 405EP processor defines.&n; *&n; * Author: SAW (IBM), derived from ibm405gp.h.&n; *         Maintained by MontaVista Software &lt;source@mvista.com&gt;&n; *&n; * 2003 (c) MontaVista Softare Inc.  This file is licensed under the&n; * terms of the GNU General Public License version 2. This program is&n; * licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBM405EP_H__
DECL|macro|__ASM_IBM405EP_H__
mdefine_line|#define __ASM_IBM405EP_H__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* ibm405.h at bottom of this file */
multiline_comment|/* PCI&n; * PCI Bridge config reg definitions&n; * see 17-19 of manual&n; */
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
mdefine_line|#define PPC405_PCI_LOWER_MEM&t;0x80000000&t;/* hose_a-&gt;mem_space.start */
DECL|macro|PPC405_PCI_UPPER_MEM
mdefine_line|#define PPC405_PCI_UPPER_MEM&t;0xBfffffff&t;/* hose_a-&gt;mem_space.end */
DECL|macro|PPC405_PCI_LOWER_IO
mdefine_line|#define PPC405_PCI_LOWER_IO&t;0x00000000&t;/* hose_a-&gt;io_space.start */
DECL|macro|PPC405_PCI_UPPER_IO
mdefine_line|#define PPC405_PCI_UPPER_IO&t;0x0000ffff&t;/* hose_a-&gt;io_space.end */
DECL|macro|PPC405_ISA_IO_BASE
mdefine_line|#define PPC405_ISA_IO_BASE&t;PPC405_PCI_IO_BASE
DECL|macro|PPC4xx_PCI_IO_PADDR
mdefine_line|#define PPC4xx_PCI_IO_PADDR&t;((uint)PPC405_PCI_PHY_IO_BASE)
DECL|macro|PPC4xx_PCI_IO_VADDR
mdefine_line|#define PPC4xx_PCI_IO_VADDR&t;PPC4xx_PCI_IO_PADDR
DECL|macro|PPC4xx_PCI_IO_SIZE
mdefine_line|#define PPC4xx_PCI_IO_SIZE&t;((uint)64*1024)
DECL|macro|PPC4xx_PCI_CFG_PADDR
mdefine_line|#define PPC4xx_PCI_CFG_PADDR&t;((uint)PPC405_PCI_CONFIG_ADDR)
DECL|macro|PPC4xx_PCI_CFG_VADDR
mdefine_line|#define PPC4xx_PCI_CFG_VADDR&t;PPC4xx_PCI_CFG_PADDR
DECL|macro|PPC4xx_PCI_CFG_SIZE
mdefine_line|#define PPC4xx_PCI_CFG_SIZE&t;((uint)4*1024)
DECL|macro|PPC4xx_PCI_LCFG_PADDR
mdefine_line|#define PPC4xx_PCI_LCFG_PADDR&t;((uint)0xef400000)
DECL|macro|PPC4xx_PCI_LCFG_VADDR
mdefine_line|#define PPC4xx_PCI_LCFG_VADDR&t;PPC4xx_PCI_LCFG_PADDR
DECL|macro|PPC4xx_PCI_LCFG_SIZE
mdefine_line|#define PPC4xx_PCI_LCFG_SIZE&t;((uint)4*1024)
DECL|macro|PPC4xx_ONB_IO_PADDR
mdefine_line|#define PPC4xx_ONB_IO_PADDR&t;((uint)0xef600000)
DECL|macro|PPC4xx_ONB_IO_VADDR
mdefine_line|#define PPC4xx_ONB_IO_VADDR&t;PPC4xx_ONB_IO_PADDR
DECL|macro|PPC4xx_ONB_IO_SIZE
mdefine_line|#define PPC4xx_ONB_IO_SIZE&t;((uint)4*1024)
multiline_comment|/* serial port defines */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;2
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
DECL|macro|EMAC0_BASE
mdefine_line|#define EMAC0_BASE&t;0xEF600800
DECL|macro|BD_EMAC_ADDR
mdefine_line|#define BD_EMAC_ADDR(e,i) bi_enetaddr[e][i]
macro_line|#if defined(CONFIG_UART0_TTYS0)
DECL|macro|ACTING_UART0_IO_BASE
mdefine_line|#define ACTING_UART0_IO_BASE&t;UART0_IO_BASE
DECL|macro|ACTING_UART1_IO_BASE
mdefine_line|#define ACTING_UART1_IO_BASE&t;UART1_IO_BASE
DECL|macro|ACTING_UART0_INT
mdefine_line|#define ACTING_UART0_INT&t;UART0_INT
DECL|macro|ACTING_UART1_INT
mdefine_line|#define ACTING_UART1_INT&t;UART1_INT
macro_line|#else
DECL|macro|ACTING_UART0_IO_BASE
mdefine_line|#define ACTING_UART0_IO_BASE&t;UART1_IO_BASE
DECL|macro|ACTING_UART1_IO_BASE
mdefine_line|#define ACTING_UART1_IO_BASE&t;UART0_IO_BASE
DECL|macro|ACTING_UART0_INT
mdefine_line|#define ACTING_UART0_INT&t;UART1_INT
DECL|macro|ACTING_UART1_INT
mdefine_line|#define ACTING_UART1_INT&t;UART0_INT
macro_line|#endif
DECL|macro|STD_UART_OP
mdefine_line|#define STD_UART_OP(num)&t;&t;&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0, ACTING_UART##num##_INT,&t;&t;&t;&bslash;&n;&t;&t;(ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST),&t;&bslash;&n;&t;&t;iomem_base: (u8 *)ACTING_UART##num##_IO_BASE,&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM},
DECL|macro|SERIAL_DEBUG_IO_BASE
mdefine_line|#define SERIAL_DEBUG_IO_BASE&t;ACTING_UART0_IO_BASE
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;STD_UART_OP(0)&t;&t;&bslash;&n;&t;STD_UART_OP(1)
multiline_comment|/* DCR defines */
DECL|macro|DCRN_CPMSR_BASE
mdefine_line|#define DCRN_CPMSR_BASE         0x0BA
DECL|macro|DCRN_CPMFR_BASE
mdefine_line|#define DCRN_CPMFR_BASE         0x0B9
DECL|macro|DCRN_CPC0_PLLMR0_BASE
mdefine_line|#define DCRN_CPC0_PLLMR0_BASE   0x0F0
DECL|macro|DCRN_CPC0_BOOT_BASE
mdefine_line|#define DCRN_CPC0_BOOT_BASE     0x0F1
DECL|macro|DCRN_CPC0_CR1_BASE
mdefine_line|#define DCRN_CPC0_CR1_BASE      0x0F2
DECL|macro|DCRN_CPC0_EPRCSR_BASE
mdefine_line|#define DCRN_CPC0_EPRCSR_BASE   0x0F3
DECL|macro|DCRN_CPC0_PLLMR1_BASE
mdefine_line|#define DCRN_CPC0_PLLMR1_BASE   0x0F4
DECL|macro|DCRN_CPC0_UCR_BASE
mdefine_line|#define DCRN_CPC0_UCR_BASE      0x0F5
DECL|macro|DCRN_CPC0_UCR_U0DIV
mdefine_line|#define DCRN_CPC0_UCR_U0DIV     0x07F
DECL|macro|DCRN_CPC0_SRR_BASE
mdefine_line|#define DCRN_CPC0_SRR_BASE      0x0F6
DECL|macro|DCRN_CPC0_JTAGID_BASE
mdefine_line|#define DCRN_CPC0_JTAGID_BASE   0x0F7
DECL|macro|DCRN_CPC0_SPARE_BASE
mdefine_line|#define DCRN_CPC0_SPARE_BASE    0x0F8
DECL|macro|DCRN_CPC0_PCI_BASE
mdefine_line|#define DCRN_CPC0_PCI_BASE      0x0F9
DECL|macro|IBM_CPM_GPT
mdefine_line|#define IBM_CPM_GPT             0x80000000      /* GPT interface */
DECL|macro|IBM_CPM_PCI
mdefine_line|#define IBM_CPM_PCI             0x40000000      /* PCI bridge */
DECL|macro|IBM_CPM_UIC
mdefine_line|#define IBM_CPM_UIC             0x00010000      /* Universal Int Controller */
DECL|macro|IBM_CPM_CPU
mdefine_line|#define IBM_CPM_CPU             0x00008000      /* processor core */
DECL|macro|IBM_CPM_EBC
mdefine_line|#define IBM_CPM_EBC             0x00002000      /* EBC controller */
DECL|macro|IBM_CPM_SDRAM0
mdefine_line|#define IBM_CPM_SDRAM0          0x00004000      /* SDRAM memory controller */
DECL|macro|IBM_CPM_GPIO0
mdefine_line|#define IBM_CPM_GPIO0           0x00001000      /* General Purpose IO */
DECL|macro|IBM_CPM_TMRCLK
mdefine_line|#define IBM_CPM_TMRCLK          0x00000400      /* CPU timers */
DECL|macro|IBM_CPM_PLB
mdefine_line|#define IBM_CPM_PLB             0x00000100      /* PLB bus arbiter */
DECL|macro|IBM_CPM_OPB
mdefine_line|#define IBM_CPM_OPB             0x00000080      /* PLB to OPB bridge */
DECL|macro|IBM_CPM_DMA
mdefine_line|#define IBM_CPM_DMA             0x00000040      /* DMA controller */
DECL|macro|IBM_CPM_IIC0
mdefine_line|#define IBM_CPM_IIC0            0x00000010      /* IIC interface */
DECL|macro|IBM_CPM_UART1
mdefine_line|#define IBM_CPM_UART1           0x00000002      /* serial port 0 */
DECL|macro|IBM_CPM_UART0
mdefine_line|#define IBM_CPM_UART0           0x00000001      /* serial port 1 */
DECL|macro|DFLT_IBM4xx_PM
mdefine_line|#define DFLT_IBM4xx_PM          ~(IBM_CPM_PCI | IBM_CPM_CPU | IBM_CPM_DMA &bslash;&n;                                        | IBM_CPM_OPB | IBM_CPM_EBC &bslash;&n;                                        | IBM_CPM_SDRAM0 | IBM_CPM_PLB &bslash;&n;                                        | IBM_CPM_UIC | IBM_CPM_TMRCLK)
DECL|macro|DCRN_DMA0_BASE
mdefine_line|#define DCRN_DMA0_BASE          0x100
DECL|macro|DCRN_DMA1_BASE
mdefine_line|#define DCRN_DMA1_BASE          0x108
DECL|macro|DCRN_DMA2_BASE
mdefine_line|#define DCRN_DMA2_BASE          0x110
DECL|macro|DCRN_DMA3_BASE
mdefine_line|#define DCRN_DMA3_BASE          0x118
DECL|macro|DCRNCAP_DMA_SG
mdefine_line|#define DCRNCAP_DMA_SG          1       /* have DMA scatter/gather capability */
DECL|macro|DCRN_DMASR_BASE
mdefine_line|#define DCRN_DMASR_BASE         0x120
DECL|macro|DCRN_EBC_BASE
mdefine_line|#define DCRN_EBC_BASE           0x012
DECL|macro|DCRN_DCP0_BASE
mdefine_line|#define DCRN_DCP0_BASE          0x014
DECL|macro|DCRN_MAL_BASE
mdefine_line|#define DCRN_MAL_BASE           0x180
DECL|macro|DCRN_OCM0_BASE
mdefine_line|#define DCRN_OCM0_BASE          0x018
DECL|macro|DCRN_PLB0_BASE
mdefine_line|#define DCRN_PLB0_BASE          0x084
DECL|macro|DCRN_PLLMR_BASE
mdefine_line|#define DCRN_PLLMR_BASE         0x0B0
DECL|macro|DCRN_POB0_BASE
mdefine_line|#define DCRN_POB0_BASE          0x0A0
DECL|macro|DCRN_SDRAM0_BASE
mdefine_line|#define DCRN_SDRAM0_BASE        0x010
DECL|macro|DCRN_UIC0_BASE
mdefine_line|#define DCRN_UIC0_BASE          0x0C0
DECL|macro|UIC0
mdefine_line|#define UIC0 DCRN_UIC0_BASE
macro_line|#include &lt;asm/ibm405.h&gt;
macro_line|#endif&t;&t;&t;&t;/* __ASM_IBM405EP_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
