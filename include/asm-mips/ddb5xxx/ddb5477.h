multiline_comment|/***********************************************************************&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * include/asm-mips/ddb5xxx/ddb5477.h&n; *     DDB 5477 specific definitions and macros.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; ***********************************************************************&n; */
macro_line|#ifndef __ASM_DDB5XXX_DDB5477_H
DECL|macro|__ASM_DDB5XXX_DDB5477_H
mdefine_line|#define __ASM_DDB5XXX_DDB5477_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ddb5xxx/ddb5xxx.h&gt;
multiline_comment|/*&n; * This contains macros that are specific to DDB5477 or renamed from&n; * DDB5476.&n; */
multiline_comment|/*&n; * renamed PADRs&n; */
DECL|macro|DDB_LCS0
mdefine_line|#define&t;DDB_LCS0&t;DDB_LDCS0
DECL|macro|DDB_LCS1
mdefine_line|#define&t;DDB_LCS1&t;DDB_LDCS1
DECL|macro|DDB_LCS2
mdefine_line|#define&t;DDB_LCS2&t;DDB_LDCS2
DECL|macro|DDB_VRC5477
mdefine_line|#define&t;DDB_VRC5477&t;DDB_INTCS
multiline_comment|/*&n; * New CPU interface registers&n; */
DECL|macro|DDB_INTCTRL0
mdefine_line|#define&t;DDB_INTCTRL0&t;0x0400&t;/* Interrupt Control 0 */
DECL|macro|DDB_INTCTRL1
mdefine_line|#define&t;DDB_INTCTRL1&t;0x0404&t;/* Interrupt Control 1 */
DECL|macro|DDB_INTCTRL2
mdefine_line|#define&t;DDB_INTCTRL2&t;0x0408&t;/* Interrupt Control 2 */
DECL|macro|DDB_INTCTRL3
mdefine_line|#define&t;DDB_INTCTRL3&t;0x040c&t;/* Interrupt Control 3 */
DECL|macro|DDB_INT0STAT
mdefine_line|#define&t;DDB_INT0STAT&t;0x0420 &t;/* INT0 Status [R] */
DECL|macro|DDB_INT1STAT
mdefine_line|#define&t;DDB_INT1STAT&t;0x0428 &t;/* INT1 Status [R] */
DECL|macro|DDB_INT2STAT
mdefine_line|#define&t;DDB_INT2STAT&t;0x0430 &t;/* INT2 Status [R] */
DECL|macro|DDB_INT3STAT
mdefine_line|#define&t;DDB_INT3STAT&t;0x0438 &t;/* INT3 Status [R] */
DECL|macro|DDB_INT4STAT
mdefine_line|#define&t;DDB_INT4STAT&t;0x0440 &t;/* INT4 Status [R] */
DECL|macro|DDB_NMISTAT
mdefine_line|#define&t;DDB_NMISTAT&t;0x0450&t;/* NMI Status [R] */
DECL|macro|DDB_INTCLR32
mdefine_line|#define&t;DDB_INTCLR32&t;0x0468&t;/* Interrupt Clear */
DECL|macro|DDB_INTPPES0
mdefine_line|#define&t;DDB_INTPPES0&t;0x0470&t;/* PCI0 Interrupt Control */
DECL|macro|DDB_INTPPES1
mdefine_line|#define&t;DDB_INTPPES1&t;0x0478&t;/* PCI1 Interrupt Control */
DECL|macro|DDB_CPUSTAT
macro_line|#undef  DDB_CPUSTAT&t;&t;/* duplicate in Vrc-5477 */
DECL|macro|DDB_CPUSTAT
mdefine_line|#define&t;DDB_CPUSTAT&t;0x0480&t;/* CPU Status [R] */
DECL|macro|DDB_BUSCTRL
mdefine_line|#define&t;DDB_BUSCTRL&t;0x0488&t;/* Internal Bus Control */
multiline_comment|/*&n; * Timer registers&n; */
DECL|macro|DDB_REFCTRL_L
mdefine_line|#define&t;DDB_REFCTRL_L&t;DDB_T0CTRL
DECL|macro|DDB_REFCTRL_H
mdefine_line|#define&t;DDB_REFCTRL_H&t;(DDB_T0CTRL+4)
DECL|macro|DDB_REFCNTR
mdefine_line|#define&t;DDB_REFCNTR&t;DDB_T0CNTR
DECL|macro|DDB_SPT0CTRL_L
mdefine_line|#define&t;DDB_SPT0CTRL_L&t;DDB_T1CTRL
DECL|macro|DDB_SPT0CTRL_H
mdefine_line|#define&t;DDB_SPT0CTRL_H&t;(DDB_T1CTRL+4)
DECL|macro|DDB_SPT1CTRL_L
mdefine_line|#define&t;DDB_SPT1CTRL_L&t;DDB_T2CTRL
DECL|macro|DDB_SPT1CTRL_H
mdefine_line|#define&t;DDB_SPT1CTRL_H&t;(DDB_T2CTRL+4)
DECL|macro|DDB_SPT1CNTR
mdefine_line|#define DDB_SPT1CNTR&t;DDB_T1CTRL
DECL|macro|DDB_WDTCTRL_L
mdefine_line|#define&t;DDB_WDTCTRL_L&t;DDB_T3CTRL
DECL|macro|DDB_WDTCTRL_H
mdefine_line|#define&t;DDB_WDTCTRL_H&t;(DDB_T3CTRL+4)
DECL|macro|DDB_WDTCNTR
mdefine_line|#define&t;DDB_WDTCNTR&t;DDB_T3CNTR
multiline_comment|/*&n; * DMA registers are moved.  We don&squot;t care about it for now. TODO.&n; */
multiline_comment|/*&n; * BARs for ext PCI (PCI0)&n; */
DECL|macro|DDB_BARC
macro_line|#undef&t;DDB_BARC
DECL|macro|DDB_BARB
macro_line|#undef&t;DDB_BARB
DECL|macro|DDB_BARC0
mdefine_line|#define DDB_BARC0&t;0x0210&t;/* PCI0 Control */
DECL|macro|DDB_BARM010
mdefine_line|#define DDB_BARM010&t;0x0218&t;/* PCI0 SDRAM bank01 */
DECL|macro|DDB_BARM230
mdefine_line|#define&t;DDB_BARM230&t;0x0220&t;/* PCI0 SDRAM bank23 */
DECL|macro|DDB_BAR00
mdefine_line|#define&t;DDB_BAR00&t;0x0240&t;/* PCI0 LDCS0 */
DECL|macro|DDB_BAR10
mdefine_line|#define&t;DDB_BAR10&t;0x0248&t;/* PCI0 LDCS1 */
DECL|macro|DDB_BAR20
mdefine_line|#define&t;DDB_BAR20&t;0x0250&t;/* PCI0 LDCS2 */
DECL|macro|DDB_BAR30
mdefine_line|#define&t;DDB_BAR30&t;0x0258&t;/* PCI0 LDCS3 */
DECL|macro|DDB_BAR40
mdefine_line|#define&t;DDB_BAR40&t;0x0260&t;/* PCI0 LDCS4 */
DECL|macro|DDB_BAR50
mdefine_line|#define&t;DDB_BAR50&t;0x0268&t;/* PCI0 LDCS5 */
DECL|macro|DDB_BARB0
mdefine_line|#define&t;DDB_BARB0&t;0x0280&t;/* PCI0 BOOT */
DECL|macro|DDB_BARP00
mdefine_line|#define&t;DDB_BARP00&t;0x0290&t;/* PCI0 for IOPCI Window0 */
DECL|macro|DDB_BARP10
mdefine_line|#define&t;DDB_BARP10&t;0x0298&t;/* PCI0 for IOPCI Window1 */
multiline_comment|/*&n; * BARs for IOPIC (PCI1)&n; */
DECL|macro|DDB_BARC1
mdefine_line|#define DDB_BARC1&t;0x0610&t;/* PCI1 Control */
DECL|macro|DDB_BARM011
mdefine_line|#define DDB_BARM011&t;0x0618&t;/* PCI1 SDRAM bank01 */
DECL|macro|DDB_BARM231
mdefine_line|#define&t;DDB_BARM231&t;0x0620&t;/* PCI1 SDRAM bank23 */
DECL|macro|DDB_BAR01
mdefine_line|#define&t;DDB_BAR01&t;0x0640&t;/* PCI1 LDCS0 */
DECL|macro|DDB_BAR11
mdefine_line|#define&t;DDB_BAR11&t;0x0648&t;/* PCI1 LDCS1 */
DECL|macro|DDB_BAR21
mdefine_line|#define&t;DDB_BAR21&t;0x0650&t;/* PCI1 LDCS2 */
DECL|macro|DDB_BAR31
mdefine_line|#define&t;DDB_BAR31&t;0x0658&t;/* PCI1 LDCS3 */
DECL|macro|DDB_BAR41
mdefine_line|#define&t;DDB_BAR41&t;0x0660&t;/* PCI1 LDCS4 */
DECL|macro|DDB_BAR51
mdefine_line|#define&t;DDB_BAR51&t;0x0668&t;/* PCI1 LDCS5 */
DECL|macro|DDB_BARB1
mdefine_line|#define&t;DDB_BARB1&t;0x0680&t;/* PCI1 BOOT */
DECL|macro|DDB_BARP01
mdefine_line|#define&t;DDB_BARP01&t;0x0690&t;/* PCI1 for ext PCI Window0 */
DECL|macro|DDB_BARP11
mdefine_line|#define&t;DDB_BARP11&t;0x0698&t;/* PCI1 for ext PCI Window1 */
multiline_comment|/*&n; * Other registers for ext PCI (PCI0)&n; */
DECL|macro|DDB_PCIINIT00
mdefine_line|#define&t;DDB_PCIINIT00&t;0x02f0&t;/* PCI0 Initiator 0 */
DECL|macro|DDB_PCIINIT10
mdefine_line|#define&t;DDB_PCIINIT10&t;0x02f8&t;/* PCI0 Initiator 1 */
DECL|macro|DDB_PCISWP0
mdefine_line|#define&t;DDB_PCISWP0&t;0x02b0&t;/* PCI0 Swap */
DECL|macro|DDB_PCIERR0
mdefine_line|#define&t;DDB_PCIERR0&t;0x02b8&t;/* PCI0 Error */
DECL|macro|DDB_PCICTL0_L
mdefine_line|#define&t;DDB_PCICTL0_L&t;0x02e0&t;/* PCI0 Control-L */
DECL|macro|DDB_PCICTL0_H
mdefine_line|#define&t;DDB_PCICTL0_H&t;0x02e4&t;/* PCI0 Control-H */
DECL|macro|DDB_PCIARB0_L
mdefine_line|#define&t;DDB_PCIARB0_L&t;0x02e8&t;/* PCI0 Arbitration-L */
DECL|macro|DDB_PCIARB0_H
mdefine_line|#define&t;DDB_PCIARB0_H&t;0x02ec&t;/* PCI0 Arbitration-H */
multiline_comment|/*&n; * Other registers for IOPCI (PCI1)&n; */
DECL|macro|DDB_IOPCIW0
mdefine_line|#define DDB_IOPCIW0&t;0x00d0&t;/* PCI Address Window 0 [R/W] */
DECL|macro|DDB_IOPCIW1
mdefine_line|#define DDB_IOPCIW1&t;0x00d8&t;/* PCI Address Window 1 [R/W] */
DECL|macro|DDB_PCIINIT01
mdefine_line|#define&t;DDB_PCIINIT01&t;0x06f0&t;/* PCI1 Initiator 0 */
DECL|macro|DDB_PCIINIT11
mdefine_line|#define&t;DDB_PCIINIT11&t;0x06f8&t;/* PCI1 Initiator 1 */
DECL|macro|DDB_PCISWP1
mdefine_line|#define&t;DDB_PCISWP1&t;0x06b0&t;/* PCI1 Swap */
DECL|macro|DDB_PCIERR1
mdefine_line|#define&t;DDB_PCIERR1&t;0x06b8&t;/* PCI1 Error */
DECL|macro|DDB_PCICTL1_L
mdefine_line|#define&t;DDB_PCICTL1_L&t;0x06e0&t;/* PCI1 Control-L */
DECL|macro|DDB_PCICTL1_H
mdefine_line|#define&t;DDB_PCICTL1_H&t;0x06e4&t;/* PCI1 Control-H */
DECL|macro|DDB_PCIARB1_L
mdefine_line|#define&t;DDB_PCIARB1_L&t;0x06e8&t;/* PCI1 Arbitration-L */
DECL|macro|DDB_PCIARB1_H
mdefine_line|#define&t;DDB_PCIARB1_H&t;0x06ec&t;/* PCI1 Arbitration-H */
multiline_comment|/*&n; * Local Bus&n; */
DECL|macro|DDB_LCST0
mdefine_line|#define DDB_LCST0&t;0x0110  /* LB Chip Select Timing 0 */
DECL|macro|DDB_LCST1
mdefine_line|#define DDB_LCST1&t;0x0118  /* LB Chip Select Timing 1 */
DECL|macro|DDB_LCST2
macro_line|#undef DDB_LCST2
DECL|macro|DDB_LCST2
mdefine_line|#define DDB_LCST2&t;0x0120  /* LB Chip Select Timing 2 */
DECL|macro|DDB_LCST3
macro_line|#undef DDB_LCST3
DECL|macro|DDB_LCST4
macro_line|#undef DDB_LCST4
DECL|macro|DDB_LCST5
macro_line|#undef DDB_LCST5
DECL|macro|DDB_LCST6
macro_line|#undef DDB_LCST6
DECL|macro|DDB_LCST7
macro_line|#undef DDB_LCST7
DECL|macro|DDB_LCST8
macro_line|#undef DDB_LCST8
DECL|macro|DDB_ERRADR
mdefine_line|#define DDB_ERRADR&t;0x0150  /* Error Address Register */
DECL|macro|DDB_ERRCS
mdefine_line|#define DDB_ERRCS       0x0160
DECL|macro|DDB_BTM
mdefine_line|#define DDB_BTM&t;&t;0x0170  /* Boot Time Mode value */
multiline_comment|/*&n; * MISC registers&n; */
DECL|macro|DDB_GIUFUNSEL
mdefine_line|#define DDB_GIUFUNSEL&t;0x4040  /* select dual-func pins */
DECL|macro|DDB_PIBMISC
mdefine_line|#define DDB_PIBMISC&t;0x0750&t;/* USB buffer enable / power saving */
multiline_comment|/*&n; *  Memory map (physical address)&n; *&n; *  Note most of the following address must be properly aligned by the&n; *  corresponding size.  For example, if PCI_IO_SIZE is 16MB, then&n; *  PCI_IO_BASE must be aligned along 16MB boundary.&n; */
DECL|macro|DDB_SDRAM_BASE
mdefine_line|#define&t;DDB_SDRAM_BASE&t;&t;0x00000000
DECL|macro|DDB_SDRAM_SIZE
mdefine_line|#define&t;DDB_SDRAM_SIZE&t;&t;0x08000000&t;/* 128MB, for sure? */
DECL|macro|DDB_PCI0_MEM_BASE
mdefine_line|#define&t;DDB_PCI0_MEM_BASE&t;0x08000000
DECL|macro|DDB_PCI0_MEM_SIZE
mdefine_line|#define&t;DDB_PCI0_MEM_SIZE&t;0x08000000&t;/* 128 MB */
DECL|macro|DDB_PCI1_MEM_BASE
mdefine_line|#define&t;DDB_PCI1_MEM_BASE&t;0x10000000
DECL|macro|DDB_PCI1_MEM_SIZE
mdefine_line|#define&t;DDB_PCI1_MEM_SIZE&t;0x08000000&t;/* 128 MB */
DECL|macro|DDB_PCI0_CONFIG_BASE
mdefine_line|#define&t;DDB_PCI0_CONFIG_BASE&t;0x18000000
DECL|macro|DDB_PCI0_CONFIG_SIZE
mdefine_line|#define&t;DDB_PCI0_CONFIG_SIZE&t;0x01000000&t;/* 16 MB */
DECL|macro|DDB_PCI1_CONFIG_BASE
mdefine_line|#define&t;DDB_PCI1_CONFIG_BASE&t;0x19000000
DECL|macro|DDB_PCI1_CONFIG_SIZE
mdefine_line|#define&t;DDB_PCI1_CONFIG_SIZE&t;0x01000000&t;/* 16 MB */
DECL|macro|DDB_PCI_IO_BASE
mdefine_line|#define&t;DDB_PCI_IO_BASE&t;&t;0x1a000000&t;/* we concatenate two IOs */
DECL|macro|DDB_PCI0_IO_BASE
mdefine_line|#define&t;DDB_PCI0_IO_BASE&t;0x1a000000
DECL|macro|DDB_PCI0_IO_SIZE
mdefine_line|#define&t;DDB_PCI0_IO_SIZE&t;0x01000000&t;/* 16 MB */
DECL|macro|DDB_PCI1_IO_BASE
mdefine_line|#define&t;DDB_PCI1_IO_BASE&t;0x1b000000
DECL|macro|DDB_PCI1_IO_SIZE
mdefine_line|#define&t;DDB_PCI1_IO_SIZE&t;0x01000000&t;/* 16 MB */
DECL|macro|DDB_LCS0_BASE
mdefine_line|#define&t;DDB_LCS0_BASE&t;&t;0x1c000000&t;/* flash memory */
DECL|macro|DDB_LCS0_SIZE
mdefine_line|#define&t;DDB_LCS0_SIZE&t;&t;0x01000000&t;/* 16 MB */
DECL|macro|DDB_LCS1_BASE
mdefine_line|#define&t;DDB_LCS1_BASE&t;&t;0x1d000000&t;/* misc */
DECL|macro|DDB_LCS1_SIZE
mdefine_line|#define&t;DDB_LCS1_SIZE&t;&t;0x01000000&t;/* 16 MB */
DECL|macro|DDB_LCS2_BASE
mdefine_line|#define&t;DDB_LCS2_BASE&t;&t;0x1e000000&t;/* Mezzanine */
DECL|macro|DDB_LCS2_SIZE
mdefine_line|#define&t;DDB_LCS2_SIZE&t;&t;0x01000000&t;/* 16 MB */
DECL|macro|DDB_VRC5477_BASE
mdefine_line|#define&t;DDB_VRC5477_BASE&t;0x1fa00000&t;/* VRC5477 control regs */
DECL|macro|DDB_VRC5477_SIZE
mdefine_line|#define&t;DDB_VRC5477_SIZE&t;0x00200000&t;/* 2MB */
DECL|macro|DDB_BOOTCS_BASE
mdefine_line|#define&t;DDB_BOOTCS_BASE&t;&t;0x1fc00000&t;/* Boot ROM / EPROM /Flash */
DECL|macro|DDB_BOOTCS_SIZE
mdefine_line|#define&t;DDB_BOOTCS_SIZE&t;&t;0x00200000&t;/* 2 MB - doc says 4MB */
DECL|macro|DDB_LED
mdefine_line|#define&t;DDB_LED&t;&t;&t;DDB_LCS1_BASE + 0x10000
multiline_comment|/*&n; * DDB5477 specific functions&n; */
r_extern
r_void
id|ddb5477_irq_setup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* route irq to cpu int pin */
r_extern
r_void
id|ll_vrc5477_irq_route
c_func
(paren
r_int
id|vrc5477_irq
comma
r_int
id|ip
)paren
suffix:semicolon
multiline_comment|/* low-level routine for enabling vrc5477 irq, bypassing high-level */
r_extern
r_void
id|ll_vrc5477_irq_enable
c_func
(paren
r_int
id|vrc5477_irq
)paren
suffix:semicolon
r_extern
r_void
id|ll_vrc5477_irq_disable
c_func
(paren
r_int
id|vrc5477_irq
)paren
suffix:semicolon
multiline_comment|/* &n; * debug routines&n; */
macro_line|#if defined(CONFIG_LL_DEBUG)
r_extern
r_void
id|vrc5477_show_pdar_regs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vrc5477_show_pci_regs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vrc5477_show_bar_regs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vrc5477_show_int_regs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vrc5477_show_all_regs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASM_DDB5XXX_DDB5477_H */
eof
