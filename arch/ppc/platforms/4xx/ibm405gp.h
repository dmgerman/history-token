multiline_comment|/*&n; * ibm405gp.h&n; *&n; *&t;This was derived from the ppc4xx.h and all 405GP specific&n; *&t;definition and board inclusions were moved here.&n; *&n; *      Armin Kuster akuster@mvista.com&n; *      Oct, 2001&n; *&n; *&n; * Copyright 2001 MontaVista Softare Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *&t;Version 1.0 (01/10/10) - A. Kuster&n; *&t;Initial version&t; - moved 40GP  specific out of ppc4xx.h&n; *&t;&t;&t;- moved emac reg from ppc405_enet.h&n; *&n; *&t;Version 1.1 02/01/17 - A. Kuster&n; *&t;Moved offsets to ibm405.h&n; *&n; *&t;Version 1.2 05/01/02 - Armin&n; *&t; added IIC_PORT_DFNS&n; *&n; *&t;Version 1.3 - armin&n; *&t;  removed iic &amp; uart num defines&n; *&t;  and IIC_PORT_DFNS&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBM405GP_H__
DECL|macro|__ASM_IBM405GP_H__
mdefine_line|#define __ASM_IBM405GP_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/ibm_ocp.h&gt;
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
DECL|macro|IIC0_BASE
mdefine_line|#define IIC0_BASE&t;0xEF600500
DECL|macro|OPB0_BASE
mdefine_line|#define OPB0_BASE&t;0xEF600600
DECL|macro|GPIO0_BASE
mdefine_line|#define GPIO0_BASE&t;0xEF600700
DECL|macro|EMAC0_BASE
mdefine_line|#define EMAC0_BASE&t;0xEF600800
DECL|macro|EMAC_NUMS
mdefine_line|#define EMAC_NUMS&t;1
DECL|macro|IIC0_IRQ
mdefine_line|#define IIC0_IRQ&t;2
DECL|macro|IIC1_IRQ
mdefine_line|#define IIC1_IRQ&t;0
DECL|macro|IIC_OWN
mdefine_line|#define IIC_OWN&t;&t;0x55
DECL|macro|IIC_CLOCK
mdefine_line|#define IIC_CLOCK&t;50
DECL|macro|BD_EMAC_ADDR
mdefine_line|#define BD_EMAC_ADDR(e,i) bi_enetaddr[i]
DECL|macro|STD_UART_OP
mdefine_line|#define STD_UART_OP(num)&t;&t;&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0, UART##num##_INT,&t;&t;&t;&bslash;&n;&t;&t;(ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST),&t;&bslash;&n;&t;&t;iomem_base: (u8 *)UART##num##_IO_BASE,&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM},
macro_line|#if defined(CONFIG_UART0_TTYS0)
DECL|macro|SERIAL_DEBUG_IO_BASE
mdefine_line|#define SERIAL_DEBUG_IO_BASE&t;UART0_IO_BASE
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;STD_UART_OP(0)&t;&t;&bslash;&n;&t;STD_UART_OP(1)
macro_line|#endif
macro_line|#if defined(CONFIG_UART0_TTYS1)
DECL|macro|SERIAL_DEBUG_IO_BASE
mdefine_line|#define SERIAL_DEBUG_IO_BASE&t;UART1_IO_BASE
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;STD_UART_OP(1)&t;&t;&bslash;&n;&t;STD_UART_OP(0)
macro_line|#endif
multiline_comment|/* DCR defines */
DECL|macro|DCRN_CHCR_BASE
mdefine_line|#define DCRN_CHCR_BASE&t;&t;0x0B1
DECL|macro|DCRN_CHPSR_BASE
mdefine_line|#define DCRN_CHPSR_BASE&t;&t;0x0B4
DECL|macro|DCRN_CPMSR_BASE
mdefine_line|#define DCRN_CPMSR_BASE&t;&t;0x0B8
DECL|macro|DCRN_CPMFR_BASE
mdefine_line|#define DCRN_CPMFR_BASE&t;&t;0x0BA
DECL|macro|CHR0_U0EC
mdefine_line|#define CHR0_U0EC&t;0x00000080&t;/* Select external clock for UART0 */
DECL|macro|CHR0_U1EC
mdefine_line|#define CHR0_U1EC&t;0x00000040&t;/* Select external clock for UART1 */
DECL|macro|CHR0_UDIV
mdefine_line|#define CHR0_UDIV&t;0x0000003E&t;/* UART internal clock divisor */
DECL|macro|CHR1_CETE
mdefine_line|#define CHR1_CETE&t;0x00800000&t;/* CPU external timer enable */
DECL|macro|DCRN_CHPSR_BASE
mdefine_line|#define DCRN_CHPSR_BASE         0x0B4
DECL|macro|PSR_PLL_FWD_MASK
mdefine_line|#define  PSR_PLL_FWD_MASK        0xC0000000
DECL|macro|PSR_PLL_FDBACK_MASK
mdefine_line|#define  PSR_PLL_FDBACK_MASK     0x30000000
DECL|macro|PSR_PLL_TUNING_MASK
mdefine_line|#define  PSR_PLL_TUNING_MASK     0x0E000000
DECL|macro|PSR_PLB_CPU_MASK
mdefine_line|#define  PSR_PLB_CPU_MASK        0x01800000
DECL|macro|PSR_OPB_PLB_MASK
mdefine_line|#define  PSR_OPB_PLB_MASK        0x00600000
DECL|macro|PSR_PCI_PLB_MASK
mdefine_line|#define  PSR_PCI_PLB_MASK        0x00180000
DECL|macro|PSR_EB_PLB_MASK
mdefine_line|#define  PSR_EB_PLB_MASK         0x00060000
DECL|macro|PSR_ROM_WIDTH_MASK
mdefine_line|#define  PSR_ROM_WIDTH_MASK      0x00018000
DECL|macro|PSR_ROM_LOC
mdefine_line|#define  PSR_ROM_LOC             0x00004000
DECL|macro|PSR_PCI_ASYNC_EN
mdefine_line|#define  PSR_PCI_ASYNC_EN        0x00001000
DECL|macro|PSR_PCI_ARBIT_EN
mdefine_line|#define  PSR_PCI_ARBIT_EN        0x00000400
DECL|macro|CPM_IIC0
mdefine_line|#define CPM_IIC0&t;&t;0x80000000&t;/* IIC interface */
DECL|macro|CPM_PCI
mdefine_line|#define CPM_PCI&t;&t;&t;0x40000000&t;/* PCI bridge */
DECL|macro|CPM_CPU
mdefine_line|#define CPM_CPU&t;&t;&t;0x20000000&t;/* processor core */
DECL|macro|CPM_DMA
mdefine_line|#define CPM_DMA&t;&t;&t;0x10000000&t;/* DMA controller */
DECL|macro|CPM_BRG
mdefine_line|#define CPM_BRG&t;&t;&t;0x08000000&t;/* PLB to OPB bridge */
DECL|macro|CPM_DCP
mdefine_line|#define CPM_DCP&t;&t;&t;0x04000000&t;/* CodePack */
DECL|macro|CPM_EBC
mdefine_line|#define CPM_EBC&t;&t;&t;0x02000000&t;/* ROM/SRAM peripheral controller */
DECL|macro|CPM_SDRAM0
mdefine_line|#define CPM_SDRAM0&t;&t;0x01000000&t;/* SDRAM memory controller */
DECL|macro|CPM_PLB
mdefine_line|#define CPM_PLB&t;&t;&t;0x00800000&t;/* PLB bus arbiter */
DECL|macro|CPM_GPIO0
mdefine_line|#define CPM_GPIO0&t;&t;0x00400000&t;/* General Purpose IO (??) */
DECL|macro|CPM_UART0
mdefine_line|#define CPM_UART0&t;&t;0x00200000&t;/* serial port 0 */
DECL|macro|CPM_UART1
mdefine_line|#define CPM_UART1&t;&t;0x00100000&t;/* serial port 1 */
DECL|macro|CPM_UIC
mdefine_line|#define CPM_UIC&t;&t;&t;0x00080000&t;/* Universal Interrupt Controller */
DECL|macro|CPM_TMRCLK
mdefine_line|#define CPM_TMRCLK&t;&t;0x00040000&t;/* CPU timers */
DECL|macro|CPM_EMAC_MM
mdefine_line|#define CPM_EMAC_MM&t;&t;0x00020000&t;/* on-chip ethernet MM unit */
DECL|macro|CPM_EMAC_RM
mdefine_line|#define CPM_EMAC_RM&t;&t;0x00010000&t;/* on-chip ethernet RM unit */
DECL|macro|CPM_EMAC_TM
mdefine_line|#define CPM_EMAC_TM&t;&t;0x00008000&t;/* on-chip ethernet TM unit */
DECL|macro|DCRN_DMA0_BASE
mdefine_line|#define DCRN_DMA0_BASE&t;&t;0x100
DECL|macro|DCRN_DMA1_BASE
mdefine_line|#define DCRN_DMA1_BASE&t;&t;0x108
DECL|macro|DCRN_DMA2_BASE
mdefine_line|#define DCRN_DMA2_BASE&t;&t;0x110
DECL|macro|DCRN_DMA3_BASE
mdefine_line|#define DCRN_DMA3_BASE&t;&t;0x118
DECL|macro|DCRNCAP_DMA_SG
mdefine_line|#define DCRNCAP_DMA_SG&t;&t;1&t;/* have DMA scatter/gather capability */
DECL|macro|DCRN_DMASR_BASE
mdefine_line|#define DCRN_DMASR_BASE&t;&t;0x120
DECL|macro|DCRN_EBC_BASE
mdefine_line|#define DCRN_EBC_BASE&t;&t;0x012
DECL|macro|DCRN_DCP0_BASE
mdefine_line|#define DCRN_DCP0_BASE&t;&t;0x014
DECL|macro|DCRN_MAL_BASE
mdefine_line|#define DCRN_MAL_BASE&t;&t;0x180
DECL|macro|DCRN_OCM0_BASE
mdefine_line|#define DCRN_OCM0_BASE&t;&t;0x018
DECL|macro|DCRN_PLB0_BASE
mdefine_line|#define DCRN_PLB0_BASE&t;&t;0x084
DECL|macro|DCRN_PLLMR_BASE
mdefine_line|#define DCRN_PLLMR_BASE&t;&t;0x0B0
DECL|macro|DCRN_POB0_BASE
mdefine_line|#define DCRN_POB0_BASE&t;&t;0x0A0
DECL|macro|DCRN_SDRAM0_BASE
mdefine_line|#define DCRN_SDRAM0_BASE&t;0x010
DECL|macro|DCRN_UIC0_BASE
mdefine_line|#define DCRN_UIC0_BASE&t;&t;0x0C0
DECL|macro|UIC0
mdefine_line|#define UIC0 DCRN_UIC0_BASE
macro_line|#include &lt;platforms/ibm405.h&gt;
macro_line|#endif&t;&t;&t;&t;/* __ASM_IBM405GP_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
