multiline_comment|/*&n; * ibmstbx25.h&n; *&n; *      Current maintainer&n; *      Armin Kuster akuster@mvista.com&n; *      July, 2002&n; *&n; *&n; * Copyright 2002 MontaVista Softare Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBMSTBX25_H__
DECL|macro|__ASM_IBMSTBX25_H__
mdefine_line|#define __ASM_IBMSTBX25_H__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* serial port defines */
DECL|macro|STBx25xx_IO_BASE
mdefine_line|#define STBx25xx_IO_BASE&t;((uint)0xe0000000)
DECL|macro|PPC4xx_ONB_IO_PADDR
mdefine_line|#define PPC4xx_ONB_IO_PADDR&t;STBx25xx_IO_BASE
DECL|macro|PPC4xx_ONB_IO_VADDR
mdefine_line|#define PPC4xx_ONB_IO_VADDR&t;((uint)0xe0000000)
DECL|macro|PPC4xx_ONB_IO_SIZE
mdefine_line|#define PPC4xx_ONB_IO_SIZE&t;((uint)14*64*1024)
multiline_comment|/*&n; * map STBxxxx internal i/o address (0x400x00xx) to an address&n; * which is below the 2GB limit...&n; *&n; * 4000 000x&t;uart1&t;&t;-&gt; 0xe000 000x&n; * 4001 00xx&t;uart2&n; * 4002 00xx&t;smart card&n; * 4003 000x&t;iic&n; * 4004 000x&t;uart0&n; * 4005 0xxx&t;timer&n; * 4006 00xx&t;gpio&n; * 4007 00xx&t;smart card&n; * 400b 000x&t;iic&n; * 400c 000x&t;scp&n; * 400d 000x&t;modem&n; * 400e 000x&t;uart2&n;*/
DECL|macro|STBx25xx_MAP_IO_ADDR
mdefine_line|#define STBx25xx_MAP_IO_ADDR(a)&t;(((uint)(a)) + (STBx25xx_IO_BASE - 0x40000000))
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;3
DECL|macro|OPB_BASE_START
mdefine_line|#define OPB_BASE_START&t;0x40000000
DECL|macro|EBIU_BASE_START
mdefine_line|#define EBIU_BASE_START&t;0xF0100000
DECL|macro|DCR_BASE_START
mdefine_line|#define DCR_BASE_START  0x0000
macro_line|#ifdef __BOOTER__
DECL|macro|UART1_IO_BASE
mdefine_line|#define UART1_IO_BASE&t;0x40000000
DECL|macro|UART2_IO_BASE
mdefine_line|#define UART2_IO_BASE&t;0x40010000
macro_line|#else
DECL|macro|UART1_IO_BASE
mdefine_line|#define UART1_IO_BASE&t;0xe0000000
DECL|macro|UART2_IO_BASE
mdefine_line|#define UART2_IO_BASE&t;0xe0010000
macro_line|#endif
DECL|macro|SC0_BASE
mdefine_line|#define SC0_BASE&t;0x40020000&t;/* smart card #0 */
DECL|macro|IIC0_BASE
mdefine_line|#define IIC0_BASE&t;0x40030000
macro_line|#ifdef __BOOTER__
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE&t;0x40040000
macro_line|#else
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE&t;0xe0040000
macro_line|#endif
DECL|macro|SCC0_BASE
mdefine_line|#define SCC0_BASE&t;0x40040000&t;/* Serial 0 controller IrdA */
DECL|macro|GPT0_BASE
mdefine_line|#define GPT0_BASE&t;0x40050000&t;/* General purpose timers */
DECL|macro|GPIO0_BASE
mdefine_line|#define GPIO0_BASE&t;0x40060000
DECL|macro|SC1_BASE
mdefine_line|#define SC1_BASE&t;0x40070000&t;/* smart card #1 */
DECL|macro|SCP0_BASE
mdefine_line|#define SCP0_BASE&t;0x400C0000&t;/* Serial Controller Port */
DECL|macro|SSP0_BASE
mdefine_line|#define SSP0_BASE&t;0x400D0000&t;/* Sync serial port */
DECL|macro|IDE0_BASE
mdefine_line|#define IDE0_BASE&t;&t;0xf0100000
DECL|macro|REDWOOD_IDE_CTRL
mdefine_line|#define REDWOOD_IDE_CTRL&t;0xf1100000
DECL|macro|RTCFPC_IRQ
mdefine_line|#define RTCFPC_IRQ&t;0
DECL|macro|XPORT_IRQ
mdefine_line|#define XPORT_IRQ&t;1
DECL|macro|AUD_IRQ
mdefine_line|#define AUD_IRQ&t;&t;2
DECL|macro|AID_IRQ
mdefine_line|#define AID_IRQ&t;&t;3
DECL|macro|DMA0
mdefine_line|#define DMA0&t;&t;4
DECL|macro|DMA1_IRQ
mdefine_line|#define DMA1_IRQ&t;5
DECL|macro|DMA2_IRQ
mdefine_line|#define DMA2_IRQ&t;6
DECL|macro|DMA3_IRQ
mdefine_line|#define DMA3_IRQ&t;7
DECL|macro|SC0_IRQ
mdefine_line|#define SC0_IRQ&t;&t;8
DECL|macro|IIC0_IRQ
mdefine_line|#define IIC0_IRQ&t;9
DECL|macro|IIR0_IRQ
mdefine_line|#define IIR0_IRQ&t;10
DECL|macro|GPT0_IRQ
mdefine_line|#define GPT0_IRQ&t;11
DECL|macro|GPT1_IRQ
mdefine_line|#define GPT1_IRQ&t;12
DECL|macro|SCP0_IRQ
mdefine_line|#define SCP0_IRQ&t;13
DECL|macro|SSP0_IRQ
mdefine_line|#define SSP0_IRQ&t;14
DECL|macro|GPT2_IRQ
mdefine_line|#define GPT2_IRQ&t;15&t;/* count down timer */
DECL|macro|SC1_IRQ
mdefine_line|#define SC1_IRQ&t;&t;16
multiline_comment|/* IRQ 17 - 19  external */
DECL|macro|UART0_INT
mdefine_line|#define UART0_INT&t;20
DECL|macro|UART1_INT
mdefine_line|#define UART1_INT&t;21
DECL|macro|UART2_INT
mdefine_line|#define UART2_INT&t;22
DECL|macro|XPTDMA_IRQ
mdefine_line|#define XPTDMA_IRQ&t;23
DECL|macro|DCRIDE_IRQ
mdefine_line|#define DCRIDE_IRQ&t;24
multiline_comment|/* IRQ 25 - 30 external */
DECL|macro|IDE0_IRQ
mdefine_line|#define IDE0_IRQ&t;26
DECL|macro|IIC_NUMS
mdefine_line|#define IIC_NUMS&t;1
DECL|macro|UART_NUMS
mdefine_line|#define UART_NUMS&t;3
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
DECL|macro|DCRN_RTCFP_BASE
mdefine_line|#define DCRN_RTCFP_BASE&t;&t;0x310
DECL|macro|UIC0
mdefine_line|#define UIC0 DCRN_UIC0_BASE
DECL|macro|IBM_CPM_IIC0
mdefine_line|#define IBM_CPM_IIC0&t;0x80000000&t;/* IIC 0 interface */
DECL|macro|IBM_CPM_CPU
mdefine_line|#define IBM_CPM_CPU&t;0x10000000&t;/* PPC405B3 clock control */
DECL|macro|IBM_CPM_AUD
mdefine_line|#define IBM_CPM_AUD&t;0x08000000&t;/* Audio Decoder */
DECL|macro|IBM_CPM_EBIU
mdefine_line|#define IBM_CPM_EBIU&t;0x04000000&t;/* External Bus Interface Unit */
DECL|macro|IBM_CPM_IRR
mdefine_line|#define IBM_CPM_IRR&t;0x02000000&t;/* Infrared reciever */
DECL|macro|IBM_CPM_DMA
mdefine_line|#define IBM_CPM_DMA&t;0x01000000&t;/* DMA controller */
DECL|macro|IBM_CPM_UART2
mdefine_line|#define IBM_CPM_UART2&t;0x00200000&t;/* Serial Control Port */
DECL|macro|IBM_CPM_UART1
mdefine_line|#define IBM_CPM_UART1&t;0x00100000&t;/* Serial 1 / Infrared */
DECL|macro|IBM_CPM_UART0
mdefine_line|#define IBM_CPM_UART0&t;0x00080000&t;/* Serial 0 / 16550 */
DECL|macro|IBM_PM_DCRIDE
mdefine_line|#define IBM_PM_DCRIDE&t;0x00040000&t;/* DCR timeout &amp; IDE line Mode clock */
DECL|macro|IBM_CPM_SC0
mdefine_line|#define IBM_CPM_SC0&t;0x00020000&t;/* Smart Card 0 */
DECL|macro|IBM_CPM_VID
mdefine_line|#define IBM_CPM_VID&t;0x00010000&t;/* reserved */
DECL|macro|IBM_CPM_SC1
mdefine_line|#define IBM_CPM_SC1&t;0x00008000&t;/* Smart Card 0 */
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
DECL|macro|IBM_CPM_C405T
mdefine_line|#define IBM_CPM_C405T&t;0x00000100&t;/* CPU timers */
DECL|macro|IBM_CPM_XPT27
mdefine_line|#define IBM_CPM_XPT27&t;0x00000080&t;/* Transport - 27 Mhz */
DECL|macro|IBM_CPM_UIC
mdefine_line|#define IBM_CPM_UIC&t;0x00000040&t;/* Universal Interrupt Controller */
DECL|macro|IBM_CPM_RTCFPC
mdefine_line|#define IBM_CPM_RTCFPC&t;0x00000020&t;/* Realtime clock and front panel */
DECL|macro|IBM_CPM_SSP
mdefine_line|#define IBM_CPM_SSP&t;0x00000010&t;/* Modem Serial Interface (SSP) */
DECL|macro|IBM_CPM_VID2
mdefine_line|#define IBM_CPM_VID2&t;0x00000002&t;/* Video Decoder clock domain 2 */
DECL|macro|DFLT_IBM4xx_PM
mdefine_line|#define DFLT_IBM4xx_PM&t;~(IBM_CPM_CPU | IBM_CPM_EBIU | IBM_CPM_DMA&t;&bslash;&n;&t;&t;&t;| IBM_CPM_CBS | IBM_CPM_XPT0 | IBM_CPM_C405T &t;&bslash;&n;&t;&t;&t;| IBM_CPM_XPT27 | IBM_CPM_UIC)
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
DECL|macro|DCRN_RTC_FPC0_CNTL
mdefine_line|#define DCRN_RTC_FPC0_CNTL &t;(DCRN_RTCFP_BASE + 0x00)&t;/* RTC cntl */
DECL|macro|DCRN_RTC_FPC0_INT
mdefine_line|#define DCRN_RTC_FPC0_INT &t;(DCRN_RTCFP_BASE + 0x01)&t;/* RTC Interrupt */
DECL|macro|DCRN_RTC_FPC0_TIME
mdefine_line|#define DCRN_RTC_FPC0_TIME &t;(DCRN_RTCFP_BASE + 0x02)&t;/* RTC time reg */
DECL|macro|DCRN_RTC_FPC0_ALRM
mdefine_line|#define DCRN_RTC_FPC0_ALRM &t;(DCRN_RTCFP_BASE + 0x03)&t;/* RTC Alarm reg */
DECL|macro|DCRN_RTC_FPC0_D1
mdefine_line|#define DCRN_RTC_FPC0_D1 &t;(DCRN_RTCFP_BASE + 0x04)&t;/* LED Data 1 */
DECL|macro|DCRN_RTC_FPC0_D2
mdefine_line|#define DCRN_RTC_FPC0_D2 &t;(DCRN_RTCFP_BASE + 0x05)&t;/* LED Data 2 */
DECL|macro|DCRN_RTC_FPC0_D3
mdefine_line|#define DCRN_RTC_FPC0_D3 &t;(DCRN_RTCFP_BASE + 0x06)&t;/* LED Data 3 */
DECL|macro|DCRN_RTC_FPC0_D4
mdefine_line|#define DCRN_RTC_FPC0_D4 &t;(DCRN_RTCFP_BASE + 0x07)&t;/* LED Data 4 */
DECL|macro|DCRN_RTC_FPC0_D5
mdefine_line|#define DCRN_RTC_FPC0_D5 &t;(DCRN_RTCFP_BASE + 0x08)&t;/* LED Data 5 */
DECL|macro|DCRN_RTC_FPC0_FCNTL
mdefine_line|#define DCRN_RTC_FPC0_FCNTL &t;(DCRN_RTCFP_BASE + 0x09)&t;/* LED control */
DECL|macro|DCRN_RTC_FPC0_BRT
mdefine_line|#define DCRN_RTC_FPC0_BRT &t;(DCRN_RTCFP_BASE + 0x0A)&t;/* Brightness cntl */
macro_line|#include &lt;asm/ibm405.h&gt;
macro_line|#endif&t;&t;&t;&t;/* __ASM_IBMSTBX25_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
