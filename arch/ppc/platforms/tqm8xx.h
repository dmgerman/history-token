multiline_comment|/*&n; * BK Id: SCCS/s.tqm8xx.h 1.8 08/30/01 09:01:04 trini&n; */
multiline_comment|/*&n; * TQM8xx(L) board specific definitions&n; * &n; * Copyright (c) 1999,2000,2001 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifndef __MACH_TQM8xx_H
DECL|macro|__MACH_TQM8xx_H
mdefine_line|#define __MACH_TQM8xx_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
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
DECL|macro|MAX_HWIFS
mdefine_line|#define&t;MAX_HWIFS&t;1&t;/* overwrite default in include/asm-ppc/ide.h */
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
DECL|macro|IDE0_INTERRUPT
mdefine_line|#define&t;IDE0_INTERRUPT&t;&t;&t;13
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif&t;/* __MACH_TQM8xx_H */
eof
