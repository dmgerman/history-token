multiline_comment|/*&n; * ibmstbx.h&n; *&n; *&t;This was dirived from the ppc4xx.h and all stbx specific definitions&n; *&t;are located here.&n; *&n; *      Armin Kuster &lt;akuster@mvista.com&gt;&n; *      Tom Rini &lt;trini@mvista.com&gt;&n; *      Oct, 2001&n; *&n; *&n; *&n; * Copyright 2001 MontaVista Softare Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *&t;Version 1.0 Oct 10, 2001 - A. Kuster&n; *&t;Initial version&t; - moved stbx  specific out of ibm4xx.h&n; *&n; *&t;Version 1.1 Oct 25, 2001 - T. Rini&n; *&t;Lots of cleanups, and we get included by the board-specific file.&n; *&n; *&t;Version 1.2 Jan 16, 2002 - A. Kuster&n; *&t;Removed common dcr offests that are now in ibm405.h &n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBMSTBX_H__
DECL|macro|__ASM_IBMSTBX_H__
mdefine_line|#define __ASM_IBMSTBX_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/ibm_ocp.h&gt;
multiline_comment|/* ibm405.h at bottom of this file */
multiline_comment|/*&n; * Memory map for the IBM &quot;Redwood-4&quot; STB03xxx evaluation board.&n; *&n; * The  STB03xxx internal i/o addresses don&squot;t work for us 1:1,&n; * so we need to map them at a well know virtual address.&n; *&n; * 4000 000x   uart1           -&gt; 0xe000 000x&n; * 4001 00xx   ppu&n; * 4002 00xx   smart card&n; * 4003 000x   iic&n; * 4004 000x   uart0&n; * 4005 0xxx   timer&n; * 4006 00xx   gpio&n; * 4007 00xx   smart card&n; * 400b 000x   iic&n; * 400c 000x   scp&n; * 400d 000x   modem&n; */
DECL|macro|STB03xxx_IO_BASE
mdefine_line|#define STB03xxx_IO_BASE&t;((uint)0xe0000000)
DECL|macro|PPC4xx_ONB_IO_PADDR
mdefine_line|#define PPC4xx_ONB_IO_PADDR&t;((uint)0x40000000)
DECL|macro|PPC4xx_ONB_IO_VADDR
mdefine_line|#define PPC4xx_ONB_IO_VADDR&t;STB03xxx_IO_BASE
DECL|macro|PPC4xx_ONB_IO_SIZE
mdefine_line|#define PPC4xx_ONB_IO_SIZE&t;((uint)14*64*1024)
multiline_comment|/* Since we&squot;re into address mapping hacks, at least try to hide&n; * it under a macro.....&n; */
DECL|macro|STB03xxx_MAP_IO_ADDR
mdefine_line|#define STB03xxx_MAP_IO_ADDR(a)&t;(((uint)(a) &amp; 0x000fffff) + PPC4xx_ONB_IO_VADDR)
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;&t;1
DECL|macro|UART0_INT
mdefine_line|#define UART0_INT&t;&t;20
macro_line|#ifdef __BOOTER__
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE&t;&t;(u8 *)0x40040000
macro_line|#else
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE&t;&t;(u8 *)STB03xxx_MAP_IO_ADDR(0x40040000)
macro_line|#endif
multiline_comment|/* UART 0 is duped here so when the SICC is the default console&n;  * then ttys1 is configured properly - armin &n;  */
DECL|macro|UART1_INT
mdefine_line|#define UART1_INT&t;&t;20
macro_line|#ifdef __BOOTER__
DECL|macro|UART1_IO_BASE
mdefine_line|#define UART1_IO_BASE&t;&t;(u8 *)0x40040000
macro_line|#else
DECL|macro|UART1_IO_BASE
mdefine_line|#define UART1_IO_BASE&t;&t;(u8 *)STB03xxx_MAP_IO_ADDR(0x40040000)
macro_line|#endif
multiline_comment|/* need to make this work in scheme - armin */
DECL|macro|SICC0_INTRX
mdefine_line|#define SICC0_INTRX&t;&t;21
DECL|macro|SICC0_INTTX
mdefine_line|#define SICC0_INTTX&t;&t;22
DECL|macro|SICC0_IO_BASE
mdefine_line|#define SICC0_IO_BASE&t;&t;((uint* )0x40000000)
DECL|macro|IIC0_BASE
mdefine_line|#define IIC0_BASE&t;0x40030000
DECL|macro|IIC1_BASE
mdefine_line|#define IIC1_BASE&t;0x400b0000
DECL|macro|OPB0_BASE
mdefine_line|#define OPB0_BASE&t;0x40010000
DECL|macro|GPIO0_BASE
mdefine_line|#define GPIO0_BASE&t;0x40060000
DECL|macro|BD_EMAC_ADDR
mdefine_line|#define BD_EMAC_ADDR(e,i) bi_enetaddr[i]
DECL|macro|STD_UART_OP
mdefine_line|#define STD_UART_OP(num)&t;&t;&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0, UART##num##_INT,&t;&t;&t;&bslash;&n;&t;&t;(ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST),&t;&bslash;&n;&t;&t;iomem_base: UART##num##_IO_BASE,&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM},
macro_line|#if defined(CONFIG_UART0_TTYS0)
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;STD_UART_OP(0)
macro_line|#endif
macro_line|#if defined(CONFIG_UART0_TTYS1)
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;STD_UART_OP(1)
macro_line|#endif
multiline_comment|/* ------------------------------------------------------------------------- */
DECL|macro|DCRN_DCRX_BASE
mdefine_line|#define DCRN_DCRX_BASE&t;&t;0x020
DECL|macro|DCRN_CIC_BASE
mdefine_line|#define DCRN_CIC_BASE &t;&t;0x030
DECL|macro|DCRN_UIC0_BASE
mdefine_line|#define DCRN_UIC0_BASE&t;&t;0x040
DECL|macro|DCRN_PLB0_BASE
mdefine_line|#define DCRN_PLB0_BASE&t;&t;0x054
DECL|macro|DCRN_PLB1_BASE
mdefine_line|#define DCRN_PLB1_BASE&t;&t;0x064
DECL|macro|DCRN_EBIMC_BASE
mdefine_line|#define DCRN_EBIMC_BASE&t;&t;0x070
DECL|macro|DCRN_POB0_BASE
mdefine_line|#define DCRN_POB0_BASE&t;&t;0x0B0
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
DECL|macro|DCRN_CPMFR_BASE
mdefine_line|#define DCRN_CPMFR_BASE&t;&t;0x102
DECL|macro|DCRN_SCCR_BASE
mdefine_line|#define DCRN_SCCR_BASE&t;&t;0x120
DECL|macro|CPM_IIC0
mdefine_line|#define CPM_IIC0&t;0x80000000&t;/* IIC 0 interface */
DECL|macro|CPM_I1284
mdefine_line|#define CPM_I1284&t;0x40000000&t;/* IEEE-1284 */
DECL|macro|CPM_IIC1
mdefine_line|#define CPM_IIC1&t;0x20000000&t;/* IIC 1 interface */
DECL|macro|CPM_CPU
mdefine_line|#define CPM_CPU&t;&t;0x10000000&t;/* PPC405B3 clock control */
DECL|macro|CPM_AUD
mdefine_line|#define CPM_AUD&t;&t;0x08000000&t;/* Audio Decoder */
DECL|macro|CPM_EBIU
mdefine_line|#define CPM_EBIU&t;0x04000000&t;/* External Bus Interface Unit */
DECL|macro|CPM_SDRAM1
mdefine_line|#define CPM_SDRAM1&t;0x02000000&t;/* SDRAM 1 memory controller */
DECL|macro|CPM_DMA
mdefine_line|#define CPM_DMA&t;&t;0x01000000&t;/* DMA controller */
DECL|macro|CPM_RES_1
mdefine_line|#define CPM_RES_1&t;0x00800000&t;/* reserved */
DECL|macro|CPM_RES_2
mdefine_line|#define CPM_RES_2&t;0x00400000&t;/* reserved */
DECL|macro|CPM_RES_3
mdefine_line|#define CPM_RES_3&t;0x00200000&t;/* reserved */
DECL|macro|CPM_UART1
mdefine_line|#define CPM_UART1&t;0x00100000&t;/* Serial 1 / Infrared */
DECL|macro|CPM_UART0
mdefine_line|#define CPM_UART0&t;0x00080000&t;/* Serial 0 / 16550 */
DECL|macro|CPM_DCRX
mdefine_line|#define CPM_DCRX&t;0x00040000&t;/* DCR Extension */
DECL|macro|CPM_SC0
mdefine_line|#define CPM_SC0&t;&t;0x00020000&t;/* Smart Card 0 */
DECL|macro|CPM_RES_4
mdefine_line|#define CPM_RES_4&t;0x00010000&t;/* reserved */
DECL|macro|CPM_SC1
mdefine_line|#define CPM_SC1&t;&t;0x00008000&t;/* Smart Card 1 */
DECL|macro|CPM_SDRAM0
mdefine_line|#define CPM_SDRAM0&t;0x00004000&t;/* SDRAM 0 memory controller */
DECL|macro|CPM_XPT54
mdefine_line|#define CPM_XPT54&t;0x00002000&t;/* Transport - 54 Mhz */
DECL|macro|CPM_CBS
mdefine_line|#define CPM_CBS&t;&t;0x00001000&t;/* Cross Bar Switch */
DECL|macro|CPM_GPT
mdefine_line|#define CPM_GPT&t;&t;0x00000800&t;/* GPTPWM */
DECL|macro|CPM_GPIO0
mdefine_line|#define CPM_GPIO0&t;0x00000400&t;/* General Purpose IO 0 */
DECL|macro|CPM_DENC
mdefine_line|#define CPM_DENC&t;0x00000200&t;/* Digital video Encoder */
DECL|macro|CPM_TMRCLK
mdefine_line|#define CPM_TMRCLK&t;0x00000100&t;/* CPU timers */
DECL|macro|CPM_XPT27
mdefine_line|#define CPM_XPT27&t;0x00000080&t;/* Transport - 27 Mhz */
DECL|macro|CPM_UIC
mdefine_line|#define CPM_UIC&t;&t;0x00000040&t;/* Universal Interrupt Controller */
DECL|macro|CPM_RES_5
mdefine_line|#define CPM_RES_5&t;0x00000020&t;/* reserved */
DECL|macro|CPM_MSI
mdefine_line|#define CPM_MSI&t;&t;0x00000010&t;/* Modem Serial Interface (SSP) */
DECL|macro|CPM_UART2
mdefine_line|#define CPM_UART2&t;0x00000008&t;/* Serial Control Port */
DECL|macro|CPM_DSCR
mdefine_line|#define CPM_DSCR&t;0x00000004&t;/* Descrambler */
DECL|macro|CPM_VID2
mdefine_line|#define CPM_VID2&t;0x00000002&t;/* Video Decoder clock domain 2 */
DECL|macro|CPM_RES_6
mdefine_line|#define CPM_RES_6&t;0x00000001&t;/* reserved */
multiline_comment|/*&t;&t;&t;0x80000000 */
DECL|macro|UIC_XPORT
mdefine_line|#define UIC_XPORT&t;0x40000000&t;/* 1 Transport */
DECL|macro|UIC_AUDIO
mdefine_line|#define UIC_AUDIO&t;0x20000000&t;/* 2 Audio Decoder */
DECL|macro|UIC_VIDEO
mdefine_line|#define UIC_VIDEO&t;0x10000000&t;/* 3 Video Decoder */
DECL|macro|UIC_D0
mdefine_line|#define UIC_D0&t;&t;0x08000000&t;/* 4 DMA Channel 0 */
DECL|macro|UIC_D1
mdefine_line|#define UIC_D1&t;&t;0x04000000&t;/* 5 DMA Channel 1 */
DECL|macro|UIC_D2
mdefine_line|#define UIC_D2&t;&t;0x02000000&t;/* 6 DMA Channel 2 */
DECL|macro|UIC_D3
mdefine_line|#define UIC_D3&t;&t;0x01000000&t;/* 7 DMA Channel 3 */
DECL|macro|UIC_SC0
mdefine_line|#define UIC_SC0&t;&t;0x00800000&t;/* 8 SmartCard 0 Controller */
DECL|macro|UIC_IIC0
mdefine_line|#define UIC_IIC0&t;0x00400000&t;/* 9 IIC 0 */
DECL|macro|UIC_IIC1
mdefine_line|#define UIC_IIC1&t;0x00200000&t;/* 10 IIC 1 */
DECL|macro|UIC_PWM0
mdefine_line|#define UIC_PWM0&t;0x00100000&t;/* 11 GPT_PWM 0: Capture Timers */
DECL|macro|UIC_PWM1
mdefine_line|#define UIC_PWM1&t;0x00080000&t;/* 12 GPT_PWM 1: Compare Timers */
DECL|macro|UIC_SCP
mdefine_line|#define UIC_SCP&t;&t;0x00040000&t;/* 13 Serial Control Port */
DECL|macro|UIC_SSP
mdefine_line|#define UIC_SSP&t;&t;0x00020000&t;/* 14 Soft Modem/Synchronous Serial Port */
DECL|macro|UIC_PWM2
mdefine_line|#define UIC_PWM2&t;0x00010000&t;/* 15 GPT_PWM 2: Down Counters */
DECL|macro|UIC_SC1
mdefine_line|#define UIC_SC1&t;&t;0x00008000&t;/* 16 SmartCard 1 Controller */
DECL|macro|UIC_EIR7
mdefine_line|#define UIC_EIR7&t;0x00004000&t;/* 17 External IRQ 7 */
DECL|macro|UIC_EIR8
mdefine_line|#define UIC_EIR8&t;0x00002000&t;/* 18 External IRQ 8 */
DECL|macro|UIC_EIR9
mdefine_line|#define UIC_EIR9&t;0x00001000&t;/* 19 External IRQ 9 */
DECL|macro|UIC_U0
mdefine_line|#define UIC_U0&t;&t;0x00000800&t;/* 20 UART0 */
DECL|macro|UIC_IR_RCV
mdefine_line|#define UIC_IR_RCV&t;0x00000400&t;/* 21 Serial 1 / Infrared UART Receive */
DECL|macro|UIC_IR_XMIT
mdefine_line|#define UIC_IR_XMIT&t;0x00000200&t;/* 22 Serial 1 / Infrared UART Transmit */
DECL|macro|UIC_IEEE1284
mdefine_line|#define UIC_IEEE1284&t;0x00000100&t;/* 23 IEEE-1284 / PPU */
DECL|macro|UIC_DCRX
mdefine_line|#define UIC_DCRX&t;0x00000080&t;/* 24 DCRX */
DECL|macro|UIC_EIR0
mdefine_line|#define UIC_EIR0&t;0x00000040&t;/* 25 External IRQ 0 */
DECL|macro|UIC_EIR1
mdefine_line|#define UIC_EIR1&t;0x00000020&t;/* 26 External IRQ 1 */
DECL|macro|UIC_EIR2
mdefine_line|#define UIC_EIR2&t;0x00000010&t;/* 27 External IRQ 2 */
DECL|macro|UIC_EIR3
mdefine_line|#define UIC_EIR3&t;0x00000008&t;/* 28 External IRQ 3 */
DECL|macro|UIC_EIR4
mdefine_line|#define UIC_EIR4&t;0x00000004&t;/* 29 External IRQ 4 */
DECL|macro|UIC_EIR5
mdefine_line|#define UIC_EIR5&t;0x00000002&t;/* 30 External IRQ 5 */
DECL|macro|UIC_EIR6
mdefine_line|#define UIC_EIR6&t;0x00000001&t;/* 31 External IRQ 6 */
macro_line|#ifdef DCRN_CIC_BASE
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
macro_line|#endif
macro_line|#ifdef DCRN_DCRX_BASE
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
macro_line|#endif
macro_line|#ifdef DCRN_EBC_BASE
DECL|macro|DCRN_EBCCFGADR
mdefine_line|#define DCRN_EBCCFGADR&t;(DCRN_EBC_BASE + 0x0)&t;/* Peripheral Controller Address */
DECL|macro|DCRN_EBCCFGDATA
mdefine_line|#define DCRN_EBCCFGDATA&t;(DCRN_EBC_BASE + 0x1)&t;/* Peripheral Controller Data */
macro_line|#endif
macro_line|#ifdef DCRN_EBIMC_BASE
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
macro_line|#endif
macro_line|#ifdef DCRN_SCCR_BASE
DECL|macro|DCRN_SCCR
mdefine_line|#define DCRN_SCCR&t;(DCRN_SCCR_BASE + 0x0)
macro_line|#endif
macro_line|#ifdef DCRN_SDRAM0_BASE
DECL|macro|DCRN_SDRAM0_CFGADDR
mdefine_line|#define DCRN_SDRAM0_CFGADDR&t;(DCRN_SDRAM0_BASE + 0x0)&t;/* Memory Controller Address */
DECL|macro|DCRN_SDRAM0_CFGDATA
mdefine_line|#define DCRN_SDRAM0_CFGDATA&t;(DCRN_SDRAM0_BASE + 0x1)&t;/* Memory Controller Data */
macro_line|#endif
macro_line|#ifdef DCRN_OCM0_BASE
DECL|macro|DCRN_OCMISARC
mdefine_line|#define DCRN_OCMISARC&t;(DCRN_OCM0_BASE + 0x0)&t;/* OCM Instr Side Addr Range Compare */
DECL|macro|DCRN_OCMISCR
mdefine_line|#define DCRN_OCMISCR&t;(DCRN_OCM0_BASE + 0x1)&t;/* OCM Instr Side Control */
DECL|macro|DCRN_OCMDSARC
mdefine_line|#define DCRN_OCMDSARC&t;(DCRN_OCM0_BASE + 0x2)&t;/* OCM Data Side Addr Range Compare */
DECL|macro|DCRN_OCMDSCR
mdefine_line|#define DCRN_OCMDSCR&t;(DCRN_OCM0_BASE + 0x3)&t;/* OCM Data Side Control */
macro_line|#endif
macro_line|#include &lt;platforms/ibm405.h&gt;
macro_line|#endif&t;&t;&t;&t;/* __ASM_IBMSTBX_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
