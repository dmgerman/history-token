multiline_comment|/*&n; * BK Id: SCCS/s.spd8xx.h 1.8 10/27/01 13:39:41 trini&n; */
multiline_comment|/*&n; * Speech Design SPD8xxTS board specific definitions&n; * &n; * Copyright (c) 2000,2001 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_SPD8XX_H__
DECL|macro|__ASM_SPD8XX_H__
mdefine_line|#define __ASM_SPD8XX_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|SPD_IMMR_BASE
mdefine_line|#define SPD_IMMR_BASE&t;0xFFF00000&t;/* phys. addr of IMMR */
DECL|macro|SPD_IMAP_SIZE
mdefine_line|#define SPD_IMAP_SIZE&t;(64 * 1024)&t;/* size of mapped area */
DECL|macro|IMAP_ADDR
mdefine_line|#define IMAP_ADDR&t;SPD_IMMR_BASE&t;/* physical base address of IMMR area */
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;SPD_IMAP_SIZE&t;/* mapped size of IMMR area */
DECL|macro|PCMCIA_MEM_ADDR
mdefine_line|#define PCMCIA_MEM_ADDR&t;((uint)0xFE100000)
DECL|macro|PCMCIA_MEM_SIZE
mdefine_line|#define PCMCIA_MEM_SIZE&t;((uint)(64 * 1024))
DECL|macro|IDE0_INTERRUPT
mdefine_line|#define IDE0_INTERRUPT&t;10&t;&t;/* = IRQ5 */
DECL|macro|IDE1_INTERRUPT
mdefine_line|#define IDE1_INTERRUPT&t;12&t;&t;/* = IRQ6 */
DECL|macro|CPM_INTERRUPT
mdefine_line|#define CPM_INTERRUPT&t;13&t;&t;/* = SIU_LEVEL6 (was: SIU_LEVEL2) */
multiline_comment|/* override the default number of IDE hardware interfaces */
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;2
multiline_comment|/*&n; * Definitions for IDE0 Interface&n; */
DECL|macro|IDE0_BASE_OFFSET
mdefine_line|#define IDE0_BASE_OFFSET&t;&t;0x0000&t;/* Offset in PCMCIA memory */
DECL|macro|IDE0_DATA_REG_OFFSET
mdefine_line|#define IDE0_DATA_REG_OFFSET&t;&t;0x0000
DECL|macro|IDE0_ERROR_REG_OFFSET
mdefine_line|#define IDE0_ERROR_REG_OFFSET&t;&t;0x0081
DECL|macro|IDE0_NSECTOR_REG_OFFSET
mdefine_line|#define IDE0_NSECTOR_REG_OFFSET&t;&t;0x0082
DECL|macro|IDE0_SECTOR_REG_OFFSET
mdefine_line|#define IDE0_SECTOR_REG_OFFSET&t;&t;0x0083
DECL|macro|IDE0_LCYL_REG_OFFSET
mdefine_line|#define IDE0_LCYL_REG_OFFSET&t;&t;0x0084
DECL|macro|IDE0_HCYL_REG_OFFSET
mdefine_line|#define IDE0_HCYL_REG_OFFSET&t;&t;0x0085
DECL|macro|IDE0_SELECT_REG_OFFSET
mdefine_line|#define IDE0_SELECT_REG_OFFSET&t;&t;0x0086
DECL|macro|IDE0_STATUS_REG_OFFSET
mdefine_line|#define IDE0_STATUS_REG_OFFSET&t;&t;0x0087
DECL|macro|IDE0_CONTROL_REG_OFFSET
mdefine_line|#define IDE0_CONTROL_REG_OFFSET&t;&t;0x0106
DECL|macro|IDE0_IRQ_REG_OFFSET
mdefine_line|#define IDE0_IRQ_REG_OFFSET&t;&t;0x000A&t;/* not used */
multiline_comment|/*&n; * Definitions for IDE1 Interface&n; */
DECL|macro|IDE1_BASE_OFFSET
mdefine_line|#define IDE1_BASE_OFFSET&t;&t;0x0C00&t;/* Offset in PCMCIA memory */
DECL|macro|IDE1_DATA_REG_OFFSET
mdefine_line|#define IDE1_DATA_REG_OFFSET&t;&t;0x0000
DECL|macro|IDE1_ERROR_REG_OFFSET
mdefine_line|#define IDE1_ERROR_REG_OFFSET&t;&t;0x0081
DECL|macro|IDE1_NSECTOR_REG_OFFSET
mdefine_line|#define IDE1_NSECTOR_REG_OFFSET&t;&t;0x0082
DECL|macro|IDE1_SECTOR_REG_OFFSET
mdefine_line|#define IDE1_SECTOR_REG_OFFSET&t;&t;0x0083
DECL|macro|IDE1_LCYL_REG_OFFSET
mdefine_line|#define IDE1_LCYL_REG_OFFSET&t;&t;0x0084
DECL|macro|IDE1_HCYL_REG_OFFSET
mdefine_line|#define IDE1_HCYL_REG_OFFSET&t;&t;0x0085
DECL|macro|IDE1_SELECT_REG_OFFSET
mdefine_line|#define IDE1_SELECT_REG_OFFSET&t;&t;0x0086
DECL|macro|IDE1_STATUS_REG_OFFSET
mdefine_line|#define IDE1_STATUS_REG_OFFSET&t;&t;0x0087
DECL|macro|IDE1_CONTROL_REG_OFFSET
mdefine_line|#define IDE1_CONTROL_REG_OFFSET&t;&t;0x0106
DECL|macro|IDE1_IRQ_REG_OFFSET
mdefine_line|#define IDE1_IRQ_REG_OFFSET&t;&t;0x000A&t;/* not used */
multiline_comment|/* CPM Ethernet through SCCx.&n; *&n; * Bits in parallel I/O port registers that have to be set/cleared&n; * to configure the pins for SCC2 use.&n; */
DECL|macro|PA_ENET_MDC
mdefine_line|#define PA_ENET_MDC&t;((ushort)0x0001)&t;/* PA 15 !!! */
DECL|macro|PA_ENET_MDIO
mdefine_line|#define PA_ENET_MDIO&t;((ushort)0x0002)&t;/* PA 14 !!! */
DECL|macro|PA_ENET_RXD
mdefine_line|#define PA_ENET_RXD&t;((ushort)0x0004)&t;/* PA 13 */
DECL|macro|PA_ENET_TXD
mdefine_line|#define PA_ENET_TXD&t;((ushort)0x0008)&t;/* PA 12 */
DECL|macro|PA_ENET_RCLK
mdefine_line|#define PA_ENET_RCLK&t;((ushort)0x0200)&t;/* PA  6 */
DECL|macro|PA_ENET_TCLK
mdefine_line|#define PA_ENET_TCLK&t;((ushort)0x0400)&t;/* PA  5 */
DECL|macro|PB_ENET_TENA
mdefine_line|#define PB_ENET_TENA&t;((uint)0x00002000)&t;/* PB 18 */
DECL|macro|PC_ENET_CLSN
mdefine_line|#define PC_ENET_CLSN&t;((ushort)0x0040)&t;/* PC  9 */
DECL|macro|PC_ENET_RENA
mdefine_line|#define PC_ENET_RENA&t;((ushort)0x0080)&t;/* PC  8 */
DECL|macro|PC_ENET_RESET
mdefine_line|#define PC_ENET_RESET&t;((ushort)0x0100)&t;/* PC  7 !!! */
multiline_comment|/* Control bits in the SICR to route TCLK (CLK3) and RCLK (CLK2) to&n; * SCC2.  Also, make sure GR2 (bit 16) and SC2 (bit 17) are zero.&n; */
DECL|macro|SICR_ENET_MASK
mdefine_line|#define SICR_ENET_MASK&t;((uint)0x0000ff00)
DECL|macro|SICR_ENET_CLKRT
mdefine_line|#define SICR_ENET_CLKRT&t;((uint)0x00002E00)
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __ASM_SPD8XX_H__ */
macro_line|#endif /* __KERNEL__ */
eof
