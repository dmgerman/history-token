multiline_comment|/*&n; * arch/ppc/platforms/4xx/ibmstb4.h&n; *&n; * Author: Armin Kuster &lt;akuster@mvista.com&gt;&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBMSTB4_H__
DECL|macro|__ASM_IBMSTB4_H__
mdefine_line|#define __ASM_IBMSTB4_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/4xx/ibm_ocp.h&gt;
multiline_comment|/* serial port defines */
DECL|macro|STB04xxx_IO_BASE
mdefine_line|#define STB04xxx_IO_BASE&t;((uint)0xe0000000)
DECL|macro|PPC4xx_PCI_IO_ADDR
mdefine_line|#define PPC4xx_PCI_IO_ADDR&t;STB04xxx_IO_BASE
DECL|macro|PPC4xx_ONB_IO_PADDR
mdefine_line|#define PPC4xx_ONB_IO_PADDR&t;STB04xxx_IO_BASE
DECL|macro|PPC4xx_ONB_IO_VADDR
mdefine_line|#define PPC4xx_ONB_IO_VADDR&t;((uint)0xe0000000)
DECL|macro|PPC4xx_ONB_IO_SIZE
mdefine_line|#define PPC4xx_ONB_IO_SIZE&t;((uint)14*64*1024)
multiline_comment|/*&n; * map STB04xxx internal i/o address (0x400x00xx) to an address&n; * which is below the 2GB limit...&n; *&n; * 4000 000x&t;uart1&t;&t;-&gt; 0xe000 000x&n; * 4001 00xx&t;ppu&n; * 4002 00xx&t;smart card&n; * 4003 000x&t;iic&n; * 4004 000x&t;uart0&n; * 4005 0xxx&t;timer&n; * 4006 00xx&t;gpio&n; * 4007 00xx&t;smart card&n; * 400b 000x&t;iic&n; * 400c 000x&t;scp&n; * 400d 000x&t;modem&n; * 400e 000x&t;uart2&n;*/
DECL|macro|STB04xxx_MAP_IO_ADDR
mdefine_line|#define STB04xxx_MAP_IO_ADDR(a)&t;(((uint)(a)) + (STB04xxx_IO_BASE - 0x40000000))
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;&t;3
DECL|macro|UART0_INT
mdefine_line|#define UART0_INT&t;&t;20
macro_line|#ifdef __BOOTER__
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE&t;&t;0x40040000
macro_line|#else
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE&t;&t;0xe0040000
macro_line|#endif
DECL|macro|UART1_INT
mdefine_line|#define UART1_INT&t;&t;21
macro_line|#ifdef __BOOTER__
DECL|macro|UART1_IO_BASE
mdefine_line|#define UART1_IO_BASE&t;&t;0x40000000
macro_line|#else
DECL|macro|UART1_IO_BASE
mdefine_line|#define UART1_IO_BASE&t;&t;0xe0000000
macro_line|#endif
DECL|macro|UART2_INT
mdefine_line|#define UART2_INT&t;&t;31
macro_line|#ifdef __BOOTER__
DECL|macro|UART2_IO_BASE
mdefine_line|#define UART2_IO_BASE&t;&t;0x400e0000
macro_line|#else
DECL|macro|UART2_IO_BASE
mdefine_line|#define UART2_IO_BASE&t;&t;0xe00e0000
macro_line|#endif
DECL|macro|IDE0_BASE
mdefine_line|#define IDE0_BASE&t;0x400F0000
DECL|macro|IDE0_SIZE
mdefine_line|#define IDE0_SIZE&t;0x200
DECL|macro|IDE0_IRQ
mdefine_line|#define IDE0_IRQ&t;25
DECL|macro|IIC0_BASE
mdefine_line|#define IIC0_BASE&t;0x40030000
DECL|macro|IIC1_BASE
mdefine_line|#define IIC1_BASE&t;0x400b0000
DECL|macro|OPB0_BASE
mdefine_line|#define OPB0_BASE&t;0x40000000
DECL|macro|GPIO0_BASE
mdefine_line|#define GPIO0_BASE&t;0x40060000
DECL|macro|USB0_IRQ
mdefine_line|#define USB0_IRQ&t;18
DECL|macro|USB0_BASE
mdefine_line|#define USB0_BASE&t;STB04xxx_MAP_IO_ADDR(0x40010000)
DECL|macro|USB0_EXTENT
mdefine_line|#define USB0_EXTENT 4096
DECL|macro|IIC_NUMS
mdefine_line|#define IIC_NUMS 2
DECL|macro|UART_NUMS
mdefine_line|#define UART_NUMS&t;3
DECL|macro|IIC0_IRQ
mdefine_line|#define IIC0_IRQ&t;9
DECL|macro|IIC1_IRQ
mdefine_line|#define IIC1_IRQ&t;10
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
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;STD_UART_OP(0)&t;&t;&bslash;&n;&t;STD_UART_OP(1)&t;&t;&bslash;&n;&t;STD_UART_OP(2)
macro_line|#endif
macro_line|#if defined(CONFIG_UART0_TTYS1)
DECL|macro|SERIAL_DEBUG_IO_BASE
mdefine_line|#define SERIAL_DEBUG_IO_BASE&t;UART2_IO_BASE
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;STD_UART_OP(1)&t;&t;&bslash;&n;&t;STD_UART_OP(0)&t;&t;&bslash;&n;&t;STD_UART_OP(2)
macro_line|#endif
macro_line|#if defined(CONFIG_UART0_TTYS2)
DECL|macro|SERIAL_DEBUG_IO_BASE
mdefine_line|#define SERIAL_DEBUG_IO_BASE&t;UART2_IO_BASE
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;STD_UART_OP(2)&t;&t;&bslash;&n;&t;STD_UART_OP(0)&t;&t;&bslash;&n;&t;STD_UART_OP(1)
macro_line|#endif
DECL|macro|DCRN_BE_BASE
mdefine_line|#define DCRN_BE_BASE&t;&t;0x090
DECL|macro|DCRN_DMA0_BASE
mdefine_line|#define DCRN_DMA0_BASE&t;&t;0x0C0
DECL|macro|DCRN_DMA1_BASE
mdefine_line|#define DCRN_DMA1_BASE&t;&t;0x0C8
DECL|macro|DCRN_DMA2_BASE
mdefine_line|#define DCRN_DMA2_BASE&t;&t;0x0D0
DECL|macro|DCRN_DMA3_BASE
mdefine_line|#define DCRN_DMA3_BASE&t;&t;0x0D8
DECL|macro|DCRNCAP_DMA_CC
mdefine_line|#define DCRNCAP_DMA_CC&t;&t;1&t;/* have DMA chained count capability */
DECL|macro|DCRN_DMASR_BASE
mdefine_line|#define DCRN_DMASR_BASE&t;&t;0x0E0
DECL|macro|DCRN_PLB0_BASE
mdefine_line|#define DCRN_PLB0_BASE&t;&t;0x054
DECL|macro|DCRN_PLB1_BASE
mdefine_line|#define DCRN_PLB1_BASE&t;&t;0x064
DECL|macro|DCRN_POB0_BASE
mdefine_line|#define DCRN_POB0_BASE&t;&t;0x0B0
DECL|macro|DCRN_SCCR_BASE
mdefine_line|#define DCRN_SCCR_BASE&t;&t;0x120
DECL|macro|DCRN_UIC0_BASE
mdefine_line|#define DCRN_UIC0_BASE&t;&t;0x040
DECL|macro|DCRN_BE_BASE
mdefine_line|#define DCRN_BE_BASE&t;&t;0x090
DECL|macro|DCRN_DMA0_BASE
mdefine_line|#define DCRN_DMA0_BASE&t;&t;0x0C0
DECL|macro|DCRN_DMA1_BASE
mdefine_line|#define DCRN_DMA1_BASE&t;&t;0x0C8
DECL|macro|DCRN_DMA2_BASE
mdefine_line|#define DCRN_DMA2_BASE&t;&t;0x0D0
DECL|macro|DCRN_DMA3_BASE
mdefine_line|#define DCRN_DMA3_BASE&t;&t;0x0D8
DECL|macro|DCRN_CIC_BASE
mdefine_line|#define DCRN_CIC_BASE &t;&t;0x030
DECL|macro|DCRN_DMASR_BASE
mdefine_line|#define DCRN_DMASR_BASE&t;&t;0x0E0
DECL|macro|DCRN_EBIMC_BASE
mdefine_line|#define DCRN_EBIMC_BASE&t;&t;0x070
DECL|macro|DCRN_DCRX_BASE
mdefine_line|#define DCRN_DCRX_BASE&t;&t;0x020
DECL|macro|DCRN_CPMFR_BASE
mdefine_line|#define DCRN_CPMFR_BASE&t;&t;0x102
DECL|macro|DCRN_SCCR_BASE
mdefine_line|#define DCRN_SCCR_BASE&t;&t;0x120
DECL|macro|UIC0
mdefine_line|#define UIC0 DCRN_UIC0_BASE
DECL|macro|IBM_CPM_IIC0
mdefine_line|#define IBM_CPM_IIC0&t;0x80000000&t;/* IIC 0 interface */
DECL|macro|IBM_CPM_USB0
mdefine_line|#define IBM_CPM_USB0&t;0x40000000&t;/* IEEE-1284 */
DECL|macro|IBM_CPM_IIC1
mdefine_line|#define IBM_CPM_IIC1&t;0x20000000&t;/* IIC 1 interface */
DECL|macro|IBM_CPM_CPU
mdefine_line|#define IBM_CPM_CPU&t;0x10000000&t;/* PPC405B3 clock control */
DECL|macro|IBM_CPM_AUD
mdefine_line|#define IBM_CPM_AUD&t;0x08000000&t;/* Audio Decoder */
DECL|macro|IBM_CPM_EBIU
mdefine_line|#define IBM_CPM_EBIU&t;0x04000000&t;/* External Bus Interface Unit */
DECL|macro|IBM_CPM_SDRAM1
mdefine_line|#define IBM_CPM_SDRAM1&t;0x02000000&t;/* SDRAM 1 memory controller */
DECL|macro|IBM_CPM_DMA
mdefine_line|#define IBM_CPM_DMA&t;0x01000000&t;/* DMA controller */
DECL|macro|IBM_CPM_DMA1
mdefine_line|#define IBM_CPM_DMA1&t;0x00800000&t;/* reserved */
DECL|macro|IBM_CPM_XPT1
mdefine_line|#define IBM_CPM_XPT1&t;0x00400000&t;/* reserved */
DECL|macro|IBM_CPM_XPT2
mdefine_line|#define IBM_CPM_XPT2&t;0x00200000&t;/* reserved */
DECL|macro|IBM_CPM_UART1
mdefine_line|#define IBM_CPM_UART1&t;0x00100000&t;/* Serial 1 / Infrared */
DECL|macro|IBM_CPM_UART0
mdefine_line|#define IBM_CPM_UART0&t;0x00080000&t;/* Serial 0 / 16550 */
DECL|macro|IBM_CPM_EPI
mdefine_line|#define IBM_CPM_EPI&t;0x00040000&t;/* DCR Extension */
DECL|macro|IBM_CPM_SC0
mdefine_line|#define IBM_CPM_SC0&t;0x00020000&t;/* Smart Card 0 */
DECL|macro|IBM_CPM_VID
mdefine_line|#define IBM_CPM_VID&t;0x00010000&t;/* reserved */
DECL|macro|IBM_CPM_SC1
mdefine_line|#define IBM_CPM_SC1&t;0x00008000&t;/* Smart Card 1 */
DECL|macro|IBM_CPM_USBSDRA
mdefine_line|#define IBM_CPM_USBSDRA&t;0x00004000&t;/* SDRAM 0 memory controller */
DECL|macro|IBM_CPM_XPT0
mdefine_line|#define IBM_CPM_XPT0&t;0x00002000&t;/* Transport - 54 Mhz */
DECL|macro|IBM_CPM_CBS
mdefine_line|#define IBM_CPM_CBS&t;0x00001000&t;/* Cross Bar Switch */
DECL|macro|IBM_CPM_GPT
mdefine_line|#define IBM_CPM_GPT&t;0x00000800&t;/* GPTPWM */
DECL|macro|IBM_CPM_GPIO0
mdefine_line|#define IBM_CPM_GPIO0&t;0x00000400&t;/* General Purpose IO 0 */
DECL|macro|IBM_CPM_DENC
mdefine_line|#define IBM_CPM_DENC&t;0x00000200&t;/* Digital video Encoder */
DECL|macro|IBM_CPM_TMRCLK
mdefine_line|#define IBM_CPM_TMRCLK&t;0x00000100&t;/* CPU timers */
DECL|macro|IBM_CPM_XPT27
mdefine_line|#define IBM_CPM_XPT27&t;0x00000080&t;/* Transport - 27 Mhz */
DECL|macro|IBM_CPM_UIC
mdefine_line|#define IBM_CPM_UIC&t;0x00000040&t;/* Universal Interrupt Controller */
DECL|macro|IBM_CPM_SSP
mdefine_line|#define IBM_CPM_SSP&t;0x00000010&t;/* Modem Serial Interface (SSP) */
DECL|macro|IBM_CPM_UART2
mdefine_line|#define IBM_CPM_UART2&t;0x00000008&t;/* Serial Control Port */
DECL|macro|IBM_CPM_DDIO
mdefine_line|#define IBM_CPM_DDIO&t;0x00000004&t;/* Descrambler */
DECL|macro|IBM_CPM_VID2
mdefine_line|#define IBM_CPM_VID2&t;0x00000002&t;/* Video Decoder clock domain 2 */
DECL|macro|DFLT_IBM4xx_PM
mdefine_line|#define DFLT_IBM4xx_PM&t;~(IBM_CPM_CPU | IBM_CPM_EBIU | IBM_CPM_SDRAM1 &bslash;&n;&t;&t;&t;| IBM_CPM_DMA | IBM_CPM_DMA1 | IBM_CPM_CBS &bslash;&n;&t;&t;&t;| IBM_CPM_USBSDRA | IBM_CPM_XPT0 | IBM_CPM_TMRCLK &bslash;&n;&t;&t;&t;| IBM_CPM_XPT27 | IBM_CPM_UIC )
DECL|macro|DCRN_BEAR
mdefine_line|#define DCRN_BEAR&t;(DCRN_BE_BASE + 0x0)&t;/* Bus Error Address Register */
DECL|macro|DCRN_BESR
mdefine_line|#define DCRN_BESR&t;(DCRN_BE_BASE + 0x1)&t;/* Bus Error Syndrome Register */
multiline_comment|/* DCRN_BESR */
DECL|macro|BESR_DSES
mdefine_line|#define BESR_DSES&t;0x80000000&t;/* Data-Side Error Status */
DECL|macro|BESR_DMES
mdefine_line|#define BESR_DMES&t;0x40000000&t;/* DMA Error Status */
DECL|macro|BESR_RWS
mdefine_line|#define BESR_RWS&t;0x20000000&t;/* Read/Write Status */
DECL|macro|BESR_ETMASK
mdefine_line|#define BESR_ETMASK&t;0x1C000000&t;/* Error Type */
DECL|macro|ET_PROT
mdefine_line|#define ET_PROT&t;&t;0
DECL|macro|ET_PARITY
mdefine_line|#define ET_PARITY&t;1
DECL|macro|ET_NCFG
mdefine_line|#define ET_NCFG&t;&t;2
DECL|macro|ET_BUSERR
mdefine_line|#define ET_BUSERR&t;4
DECL|macro|ET_BUSTO
mdefine_line|#define ET_BUSTO&t;6
DECL|macro|CHR1_CETE
mdefine_line|#define CHR1_CETE&t;0x00800000&t;/* CPU external timer enable */
DECL|macro|CHR1_PCIPW
mdefine_line|#define CHR1_PCIPW&t;0x00008000&t;/* PCI Int enable/Peripheral Write enable */
DECL|macro|DCRN_CICCR
mdefine_line|#define DCRN_CICCR&t;(DCRN_CIC_BASE + 0x0)&t;/* CIC Control Register */
DECL|macro|DCRN_DMAS1
mdefine_line|#define DCRN_DMAS1&t;(DCRN_CIC_BASE + 0x1)&t;/* DMA Select1 Register */
DECL|macro|DCRN_DMAS2
mdefine_line|#define DCRN_DMAS2&t;(DCRN_CIC_BASE + 0x2)&t;/* DMA Select2 Register */
DECL|macro|DCRN_CICVCR
mdefine_line|#define DCRN_CICVCR&t;(DCRN_CIC_BASE + 0x3)&t;/* CIC Video COntro Register */
DECL|macro|DCRN_CICSEL3
mdefine_line|#define DCRN_CICSEL3&t;(DCRN_CIC_BASE + 0x5)&t;/* CIC Select 3 Register */
DECL|macro|DCRN_SGPO
mdefine_line|#define DCRN_SGPO&t;(DCRN_CIC_BASE + 0x6)&t;/* CIC GPIO Output Register */
DECL|macro|DCRN_SGPOD
mdefine_line|#define DCRN_SGPOD&t;(DCRN_CIC_BASE + 0x7)&t;/* CIC GPIO OD Register */
DECL|macro|DCRN_SGPTC
mdefine_line|#define DCRN_SGPTC&t;(DCRN_CIC_BASE + 0x8)&t;/* CIC GPIO Tristate Ctrl Reg */
DECL|macro|DCRN_SGPI
mdefine_line|#define DCRN_SGPI&t;(DCRN_CIC_BASE + 0x9)&t;/* CIC GPIO Input Reg */
DECL|macro|DCRN_DCRXICR
mdefine_line|#define DCRN_DCRXICR&t;(DCRN_DCRX_BASE + 0x0)&t;/* Internal Control Register */
DECL|macro|DCRN_DCRXISR
mdefine_line|#define DCRN_DCRXISR&t;(DCRN_DCRX_BASE + 0x1)&t;/* Internal Status Register */
DECL|macro|DCRN_DCRXECR
mdefine_line|#define DCRN_DCRXECR&t;(DCRN_DCRX_BASE + 0x2)&t;/* External Control Register */
DECL|macro|DCRN_DCRXESR
mdefine_line|#define DCRN_DCRXESR&t;(DCRN_DCRX_BASE + 0x3)&t;/* External Status Register */
DECL|macro|DCRN_DCRXTAR
mdefine_line|#define DCRN_DCRXTAR&t;(DCRN_DCRX_BASE + 0x4)&t;/* Target Address Register */
DECL|macro|DCRN_DCRXTDR
mdefine_line|#define DCRN_DCRXTDR&t;(DCRN_DCRX_BASE + 0x5)&t;/* Target Data Register */
DECL|macro|DCRN_DCRXIGR
mdefine_line|#define DCRN_DCRXIGR&t;(DCRN_DCRX_BASE + 0x6)&t;/* Interrupt Generation Register */
DECL|macro|DCRN_DCRXBCR
mdefine_line|#define DCRN_DCRXBCR&t;(DCRN_DCRX_BASE + 0x7)&t;/* Line Buffer Control Register */
DECL|macro|DCRN_BRCRH0
mdefine_line|#define DCRN_BRCRH0&t;(DCRN_EBIMC_BASE + 0x0)&t;/* Bus Region Config High 0 */
DECL|macro|DCRN_BRCRH1
mdefine_line|#define DCRN_BRCRH1&t;(DCRN_EBIMC_BASE + 0x1)&t;/* Bus Region Config High 1 */
DECL|macro|DCRN_BRCRH2
mdefine_line|#define DCRN_BRCRH2&t;(DCRN_EBIMC_BASE + 0x2)&t;/* Bus Region Config High 2 */
DECL|macro|DCRN_BRCRH3
mdefine_line|#define DCRN_BRCRH3&t;(DCRN_EBIMC_BASE + 0x3)&t;/* Bus Region Config High 3 */
DECL|macro|DCRN_BRCRH4
mdefine_line|#define DCRN_BRCRH4&t;(DCRN_EBIMC_BASE + 0x4)&t;/* Bus Region Config High 4 */
DECL|macro|DCRN_BRCRH5
mdefine_line|#define DCRN_BRCRH5&t;(DCRN_EBIMC_BASE + 0x5)&t;/* Bus Region Config High 5 */
DECL|macro|DCRN_BRCRH6
mdefine_line|#define DCRN_BRCRH6&t;(DCRN_EBIMC_BASE + 0x6)&t;/* Bus Region Config High 6 */
DECL|macro|DCRN_BRCRH7
mdefine_line|#define DCRN_BRCRH7&t;(DCRN_EBIMC_BASE + 0x7)&t;/* Bus Region Config High 7 */
DECL|macro|DCRN_BRCR0
mdefine_line|#define DCRN_BRCR0&t;(DCRN_EBIMC_BASE + 0x10)&t;/* BRC 0 */
DECL|macro|DCRN_BRCR1
mdefine_line|#define DCRN_BRCR1&t;(DCRN_EBIMC_BASE + 0x11)&t;/* BRC 1 */
DECL|macro|DCRN_BRCR2
mdefine_line|#define DCRN_BRCR2&t;(DCRN_EBIMC_BASE + 0x12)&t;/* BRC 2 */
DECL|macro|DCRN_BRCR3
mdefine_line|#define DCRN_BRCR3&t;(DCRN_EBIMC_BASE + 0x13)&t;/* BRC 3 */
DECL|macro|DCRN_BRCR4
mdefine_line|#define DCRN_BRCR4&t;(DCRN_EBIMC_BASE + 0x14)&t;/* BRC 4 */
DECL|macro|DCRN_BRCR5
mdefine_line|#define DCRN_BRCR5&t;(DCRN_EBIMC_BASE + 0x15)&t;/* BRC 5 */
DECL|macro|DCRN_BRCR6
mdefine_line|#define DCRN_BRCR6&t;(DCRN_EBIMC_BASE + 0x16)&t;/* BRC 6 */
DECL|macro|DCRN_BRCR7
mdefine_line|#define DCRN_BRCR7&t;(DCRN_EBIMC_BASE + 0x17)&t;/* BRC 7 */
DECL|macro|DCRN_BEAR0
mdefine_line|#define DCRN_BEAR0&t;(DCRN_EBIMC_BASE + 0x20)&t;/* Bus Error Address Register */
DECL|macro|DCRN_BESR0
mdefine_line|#define DCRN_BESR0&t;(DCRN_EBIMC_BASE + 0x21)&t;/* Bus Error Status Register */
DECL|macro|DCRN_BIUCR
mdefine_line|#define DCRN_BIUCR&t;(DCRN_EBIMC_BASE + 0x2A)&t;/* Bus Interfac Unit Ctrl Reg */
macro_line|#include &lt;asm/ibm405.h&gt;
macro_line|#endif&t;&t;&t;&t;/* __ASM_IBMSTB4_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
