multiline_comment|/*&n; * BK Id: SCCS/s.ivms8.h 1.8 10/26/01 10:14:09 trini&n; */
multiline_comment|/*&n; * Speech Design Integrated Voicemail board specific definitions&n; * - IVMS8  (small,  8 channels)&n; * - IVML24 (large, 24 channels)&n; *&n; * In 2.5 when we force a new bootloader, we can merge these two, and add&n; * in _MACH_&squot;s for them. -- Tom&n; *&n; * Copyright (c) 2000, 2001 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IVMS8_H__
DECL|macro|__ASM_IVMS8_H__
mdefine_line|#define __ASM_IVMS8_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|IVMS_IMMR_BASE
mdefine_line|#define IVMS_IMMR_BASE&t;0xFFF00000&t;/* phys. addr of IMMR */
DECL|macro|IVMS_IMAP_SIZE
mdefine_line|#define IVMS_IMAP_SIZE&t;(64 * 1024)&t;/* size of mapped area */
DECL|macro|IMAP_ADDR
mdefine_line|#define IMAP_ADDR&t;IVMS_IMMR_BASE&t;/* phys. base address of IMMR area */
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;IVMS_IMAP_SIZE&t;/* mapped size of IMMR area */
DECL|macro|PCMCIA_MEM_ADDR
mdefine_line|#define PCMCIA_MEM_ADDR&t;((uint)0xFE100000)
DECL|macro|PCMCIA_MEM_SIZE
mdefine_line|#define PCMCIA_MEM_SIZE&t;((uint)(64 * 1024))
DECL|macro|FEC_INTERRUPT
mdefine_line|#define FEC_INTERRUPT&t; 9&t;&t;/* = SIU_LEVEL4 */
DECL|macro|IDE0_INTERRUPT
mdefine_line|#define IDE0_INTERRUPT&t;10&t;&t;/* = IRQ5 */
DECL|macro|CPM_INTERRUPT
mdefine_line|#define CPM_INTERRUPT&t;11&t;&t;/* = SIU_LEVEL5 (was: SIU_LEVEL2) */
DECL|macro|PHY_INTERRUPT
mdefine_line|#define PHY_INTERRUPT&t;12&t;&t;/* = IRQ6 */
multiline_comment|/* override the default number of IDE hardware interfaces */
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;1
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
multiline_comment|/* We don&squot;t use the 8259. */
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif /* __ASM_IVMS8_H__ */
macro_line|#endif /* __KERNEL__ */
eof
