multiline_comment|/*&n; * TQM8xx(L) board specific definitions&n; *&n; * Copyright (c) 1999-2002 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __MACH_TQM8xx_H
DECL|macro|__MACH_TQM8xx_H
mdefine_line|#define __MACH_TQM8xx_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|TQM_IMMR_BASE
mdefine_line|#define&t;TQM_IMMR_BASE&t;0xFFF00000&t;/* phys. addr of IMMR */
DECL|macro|TQM_IMAP_SIZE
mdefine_line|#define&t;TQM_IMAP_SIZE&t;(64 * 1024)&t;/* size of mapped area */
DECL|macro|IMAP_ADDR
mdefine_line|#define&t;IMAP_ADDR&t;TQM_IMMR_BASE&t;/* physical base address of IMMR area */
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;TQM_IMAP_SIZE&t;/* mapped size of IMMR area */
multiline_comment|/*-----------------------------------------------------------------------&n; * PCMCIA stuff&n; *-----------------------------------------------------------------------&n; *&n; */
DECL|macro|PCMCIA_MEM_SIZE
mdefine_line|#define PCMCIA_MEM_SIZE&t;&t;( 64 &lt;&lt; 20 )
macro_line|#ifndef CONFIG_KUP4K
DECL|macro|MAX_HWIFS
macro_line|# define&t;MAX_HWIFS&t;1&t;/* overwrite default in include/asm-ppc/ide.h&t;*/
macro_line|#else&t;/* CONFIG_KUP4K */
DECL|macro|MAX_HWIFS
macro_line|# define&t;MAX_HWIFS&t;2&t;/* overwrite default in include/asm-ppc/ide.h&t;*/
macro_line|# ifndef __ASSEMBLY__
macro_line|# include &lt;asm/8xx_immap.h&gt;
DECL|function|ide_led
r_static
id|__inline__
r_void
id|ide_led
c_func
(paren
r_int
id|on
)paren
(brace
r_volatile
id|immap_t
op_star
id|immap
op_assign
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
(brace
id|immap-&gt;im_ioport.iop_padat
op_and_assign
op_complement
l_int|0x80
suffix:semicolon
)brace
r_else
(brace
id|immap-&gt;im_ioport.iop_padat
op_or_assign
l_int|0x80
suffix:semicolon
)brace
)brace
macro_line|# endif&t;/* __ASSEMBLY__ */
DECL|macro|IDE_LED
macro_line|# define IDE_LED(x) ide_led((x))
macro_line|#endif&t;/* CONFIG_KUP4K */
multiline_comment|/*&n; * Definitions for IDE0 Interface&n; */
DECL|macro|IDE0_BASE_OFFSET
mdefine_line|#define IDE0_BASE_OFFSET&t;&t;0
DECL|macro|IDE0_DATA_REG_OFFSET
mdefine_line|#define IDE0_DATA_REG_OFFSET&t;&t;(PCMCIA_MEM_SIZE + 0x320)
DECL|macro|IDE0_ERROR_REG_OFFSET
mdefine_line|#define IDE0_ERROR_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 1)
DECL|macro|IDE0_NSECTOR_REG_OFFSET
mdefine_line|#define IDE0_NSECTOR_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 2)
DECL|macro|IDE0_SECTOR_REG_OFFSET
mdefine_line|#define IDE0_SECTOR_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 3)
DECL|macro|IDE0_LCYL_REG_OFFSET
mdefine_line|#define IDE0_LCYL_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 4)
DECL|macro|IDE0_HCYL_REG_OFFSET
mdefine_line|#define IDE0_HCYL_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 5)
DECL|macro|IDE0_SELECT_REG_OFFSET
mdefine_line|#define IDE0_SELECT_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 6)
DECL|macro|IDE0_STATUS_REG_OFFSET
mdefine_line|#define IDE0_STATUS_REG_OFFSET&t;&t;(2 * PCMCIA_MEM_SIZE + 0x320 + 7)
DECL|macro|IDE0_CONTROL_REG_OFFSET
mdefine_line|#define IDE0_CONTROL_REG_OFFSET&t;&t;0x0106
DECL|macro|IDE0_IRQ_REG_OFFSET
mdefine_line|#define IDE0_IRQ_REG_OFFSET&t;&t;0x000A&t;/* not used */
multiline_comment|/* define IO_BASE for PCMCIA */
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE 0x80000000
DECL|macro|_IO_BASE_SIZE
mdefine_line|#define _IO_BASE_SIZE  (64&lt;&lt;10)
DECL|macro|FEC_INTERRUPT
mdefine_line|#define&t;FEC_INTERRUPT&t;&t; 9&t;/* = SIU_LEVEL4&t;&t;&t;*/
DECL|macro|PHY_INTERRUPT
mdefine_line|#define PHY_INTERRUPT&t;&t;12&t;/* = IRQ6&t;&t;&t;*/
DECL|macro|IDE0_INTERRUPT
mdefine_line|#define&t;IDE0_INTERRUPT&t;&t;13
macro_line|#ifdef CONFIG_IDE
macro_line|#endif
multiline_comment|/*-----------------------------------------------------------------------&n; * CPM Ethernet through SCCx.&n; *-----------------------------------------------------------------------&n; *&n; */
multiline_comment|/***  TQM823L, TQM850L  ***********************************************/
macro_line|#if defined(CONFIG_TQM823L) || defined(CONFIG_TQM850L)
multiline_comment|/* Bits in parallel I/O port registers that have to be set/cleared&n; * to configure the pins for SCC1 use.&n; */
DECL|macro|PA_ENET_RXD
mdefine_line|#define PA_ENET_RXD&t;((ushort)0x0004)&t;/* PA 13 */
DECL|macro|PA_ENET_TXD
mdefine_line|#define PA_ENET_TXD&t;((ushort)0x0008)&t;/* PA 12 */
DECL|macro|PA_ENET_RCLK
mdefine_line|#define PA_ENET_RCLK&t;((ushort)0x0100)&t;/* PA  7 */
DECL|macro|PA_ENET_TCLK
mdefine_line|#define PA_ENET_TCLK&t;((ushort)0x0400)&t;/* PA  5 */
DECL|macro|PB_ENET_TENA
mdefine_line|#define PB_ENET_TENA&t;((uint)0x00002000)&t;/* PB 18 */
DECL|macro|PC_ENET_CLSN
mdefine_line|#define PC_ENET_CLSN&t;((ushort)0x0040)&t;/* PC  9 */
DECL|macro|PC_ENET_RENA
mdefine_line|#define PC_ENET_RENA&t;((ushort)0x0080)&t;/* PC  8 */
multiline_comment|/* Control bits in the SICR to route TCLK (CLK3) and RCLK (CLK1) to&n; * SCC2.  Also, make sure GR2 (bit 16) and SC2 (bit 17) are zero.&n; */
DECL|macro|SICR_ENET_MASK
mdefine_line|#define SICR_ENET_MASK&t;((uint)0x0000ff00)
DECL|macro|SICR_ENET_CLKRT
mdefine_line|#define SICR_ENET_CLKRT&t;((uint)0x00002600)
macro_line|#endif&t;/* CONFIG_TQM823L, CONFIG_TQM850L */
multiline_comment|/***  TQM860L  ********************************************************/
macro_line|#ifdef CONFIG_TQM860L
multiline_comment|/* Bits in parallel I/O port registers that have to be set/cleared&n; * to configure the pins for SCC1 use.&n; */
DECL|macro|PA_ENET_RXD
mdefine_line|#define PA_ENET_RXD&t;((ushort)0x0001)&t;/* PA 15 */
DECL|macro|PA_ENET_TXD
mdefine_line|#define PA_ENET_TXD&t;((ushort)0x0002)&t;/* PA 14 */
DECL|macro|PA_ENET_RCLK
mdefine_line|#define PA_ENET_RCLK&t;((ushort)0x0100)&t;/* PA  7 */
DECL|macro|PA_ENET_TCLK
mdefine_line|#define PA_ENET_TCLK&t;((ushort)0x0400)&t;/* PA  5 */
DECL|macro|PC_ENET_TENA
mdefine_line|#define PC_ENET_TENA&t;((ushort)0x0001)&t;/* PC 15 */
DECL|macro|PC_ENET_CLSN
mdefine_line|#define PC_ENET_CLSN&t;((ushort)0x0010)&t;/* PC 11 */
DECL|macro|PC_ENET_RENA
mdefine_line|#define PC_ENET_RENA&t;((ushort)0x0020)&t;/* PC 10 */
multiline_comment|/* Control bits in the SICR to route TCLK (CLK3) and RCLK (CLK1) to&n; * SCC1.  Also, make sure GR1 (bit 24) and SC1 (bit 25) are zero.&n; */
DECL|macro|SICR_ENET_MASK
mdefine_line|#define SICR_ENET_MASK&t;((uint)0x000000ff)
DECL|macro|SICR_ENET_CLKRT
mdefine_line|#define SICR_ENET_CLKRT&t;((uint)0x00000026)
macro_line|#endif&t;/* CONFIG_TQM860L */
multiline_comment|/***  FPS850L  *********************************************************/
macro_line|#ifdef CONFIG_FPS850L
multiline_comment|/* Bits in parallel I/O port registers that have to be set/cleared&n; * to configure the pins for SCC1 use.&n; */
DECL|macro|PA_ENET_RXD
mdefine_line|#define PA_ENET_RXD&t;((ushort)0x0004)&t;/* PA 13 */
DECL|macro|PA_ENET_TXD
mdefine_line|#define PA_ENET_TXD&t;((ushort)0x0008)&t;/* PA 12 */
DECL|macro|PA_ENET_RCLK
mdefine_line|#define PA_ENET_RCLK&t;((ushort)0x0100)&t;/* PA  7 */
DECL|macro|PA_ENET_TCLK
mdefine_line|#define PA_ENET_TCLK&t;((ushort)0x0400)&t;/* PA  5 */
DECL|macro|PC_ENET_TENA
mdefine_line|#define PC_ENET_TENA&t;((ushort)0x0002)&t;/* PC 14 */
DECL|macro|PC_ENET_CLSN
mdefine_line|#define PC_ENET_CLSN&t;((ushort)0x0040)&t;/* PC  9 */
DECL|macro|PC_ENET_RENA
mdefine_line|#define PC_ENET_RENA&t;((ushort)0x0080)&t;/* PC  8 */
multiline_comment|/* Control bits in the SICR to route TCLK (CLK2) and RCLK (CLK4) to&n; * SCC2.  Also, make sure GR2 (bit 16) and SC2 (bit 17) are zero.&n; */
DECL|macro|SICR_ENET_MASK
mdefine_line|#define SICR_ENET_MASK&t;((uint)0x0000ff00)
DECL|macro|SICR_ENET_CLKRT
mdefine_line|#define SICR_ENET_CLKRT&t;((uint)0x00002600)
macro_line|#endif&t;/* CONFIG_FPS850L */
multiline_comment|/***  SM850  *********************************************************/
multiline_comment|/* The SM850 Service Module uses SCC2 for IrDA and SCC3 for Ethernet */
macro_line|#ifdef CONFIG_SM850
DECL|macro|PB_ENET_RXD
mdefine_line|#define PB_ENET_RXD&t;((uint)0x00000004)&t;/* PB 29 */
DECL|macro|PB_ENET_TXD
mdefine_line|#define PB_ENET_TXD&t;((uint)0x00000002)&t;/* PB 30 */
DECL|macro|PA_ENET_RCLK
mdefine_line|#define PA_ENET_RCLK&t;((ushort)0x0100)&t;/* PA  7 */
DECL|macro|PA_ENET_TCLK
mdefine_line|#define PA_ENET_TCLK&t;((ushort)0x0400)&t;/* PA  5 */
DECL|macro|PC_ENET_LBK
mdefine_line|#define PC_ENET_LBK&t;((ushort)0x0008)&t;/* PC 12 */
DECL|macro|PC_ENET_TENA
mdefine_line|#define PC_ENET_TENA&t;((ushort)0x0004)&t;/* PC 13 */
DECL|macro|PC_ENET_RENA
mdefine_line|#define PC_ENET_RENA&t;((ushort)0x0800)&t;/* PC  4 */
DECL|macro|PC_ENET_CLSN
mdefine_line|#define PC_ENET_CLSN&t;((ushort)0x0400)&t;/* PC  5 */
multiline_comment|/* Control bits in the SICR to route TCLK (CLK3) and RCLK (CLK1) to&n; * SCC3.  Also, make sure GR3 (bit 8) and SC3 (bit 9) are zero.&n; */
DECL|macro|SICR_ENET_MASK
mdefine_line|#define SICR_ENET_MASK&t;((uint)0x00FF0000)
DECL|macro|SICR_ENET_CLKRT
mdefine_line|#define SICR_ENET_CLKRT&t;((uint)0x00260000)
macro_line|#endif&t;/* CONFIG_SM850 */
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif&t;/* __MACH_TQM8xx_H */
macro_line|#endif /* __KERNEL__ */
eof
