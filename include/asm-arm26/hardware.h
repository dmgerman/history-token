multiline_comment|/*&n; *  linux/include/asm-arm/arch-arc/hardware.h&n; *&n; *  Copyright (C) 1996-1999 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This file contains the hardware definitions of the&n; *  Acorn Archimedes/A5000 machines.&n; *&n; *  Modifications:&n; *   04-04-1998&t;PJB/RMK&t;Merged arc and a5k versions&n; */
macro_line|#ifndef __ASM_HARDWARE_H
DECL|macro|__ASM_HARDWARE_H
mdefine_line|#define __ASM_HARDWARE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * What hardware must be present - these can be tested by the kernel&n; * source.&n; */
DECL|macro|HAS_IOC
mdefine_line|#define HAS_IOC
DECL|macro|HAS_MEMC
mdefine_line|#define HAS_MEMC
DECL|macro|HAS_VIDC
mdefine_line|#define HAS_VIDC
DECL|macro|VDMA_ALIGNMENT
mdefine_line|#define VDMA_ALIGNMENT  PAGE_SIZE
DECL|macro|VDMA_XFERSIZE
mdefine_line|#define VDMA_XFERSIZE   16
DECL|macro|VDMA_INIT
mdefine_line|#define VDMA_INIT       0
DECL|macro|VDMA_START
mdefine_line|#define VDMA_START      1
DECL|macro|VDMA_END
mdefine_line|#define VDMA_END        2
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|memc_write
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|macro|video_set_dma
mdefine_line|#define video_set_dma(start,end,offset)                         &bslash;&n;do {                                                            &bslash;&n;        memc_write (VDMA_START, (start &gt;&gt; 2));                  &bslash;&n;        memc_write (VDMA_END, (end - VDMA_XFERSIZE) &gt;&gt; 2);      &bslash;&n;        memc_write (VDMA_INIT, (offset &gt;&gt; 2));                  &bslash;&n;} while (0)
macro_line|#endif
multiline_comment|/* Hardware addresses of major areas.&n; *  *_START is the physical address&n; *  *_SIZE  is the size of the region&n; *  *_BASE  is the virtual address&n; */
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0x03000000
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x01000000
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0x03000000
multiline_comment|/*&n; * Screen mapping information&n; */
DECL|macro|SCREEN_START
mdefine_line|#define SCREEN_START&t;&t;0x02000000
DECL|macro|SCREEN_END
mdefine_line|#define SCREEN_END&t;&t;0x02078000
DECL|macro|SCREEN_SIZE
mdefine_line|#define SCREEN_SIZE&t;&t;0x00078000
DECL|macro|SCREEN_BASE
mdefine_line|#define SCREEN_BASE&t;&t;0x02000000
DECL|macro|EXPMASK_BASE
mdefine_line|#define EXPMASK_BASE&t;&t;0x03360000
DECL|macro|IOEB_BASE
mdefine_line|#define IOEB_BASE&t;&t;0x03350000
DECL|macro|VIDC_BASE
mdefine_line|#define VIDC_BASE&t;&t;0x03400000
DECL|macro|LATCHA_BASE
mdefine_line|#define LATCHA_BASE&t;&t;0x03250040
DECL|macro|LATCHB_BASE
mdefine_line|#define LATCHB_BASE&t;&t;0x03250018
DECL|macro|IOC_BASE
mdefine_line|#define IOC_BASE&t;&t;0x03200000
DECL|macro|FLOPPYDMA_BASE
mdefine_line|#define FLOPPYDMA_BASE&t;&t;0x0302a000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0x03010000
singleline_comment|// FIXME - are the below correct?
DECL|macro|PODSLOT_IOC0_BASE
mdefine_line|#define PODSLOT_IOC0_BASE       0x03240000
DECL|macro|PODSLOT_IOC_SIZE
mdefine_line|#define PODSLOT_IOC_SIZE        (1 &lt;&lt; 14)
DECL|macro|PODSLOT_MEMC_BASE
mdefine_line|#define PODSLOT_MEMC_BASE       0x03000000
DECL|macro|PODSLOT_MEMC_SIZE
mdefine_line|#define PODSLOT_MEMC_SIZE       (1 &lt;&lt; 14)
DECL|macro|vidc_writel
mdefine_line|#define vidc_writel(val)&t;__raw_writel(val, VIDC_BASE)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * for use with inb/outb&n; */
DECL|macro|IOEB_VID_CTL
mdefine_line|#define IOEB_VID_CTL&t;&t;(IOEB_BASE + 0x48)
DECL|macro|IOEB_PRESENT
mdefine_line|#define IOEB_PRESENT&t;&t;(IOEB_BASE + 0x50)
DECL|macro|IOEB_PSCLR
mdefine_line|#define IOEB_PSCLR&t;&t;(IOEB_BASE + 0x58)
DECL|macro|IOEB_MONTYPE
mdefine_line|#define IOEB_MONTYPE&t;&t;(IOEB_BASE + 0x70)
singleline_comment|//FIXME - These adresses are weird - ISTR some weirdo address shifting stuff was going on here...
DECL|macro|IO_EC_IOC_BASE
mdefine_line|#define IO_EC_IOC_BASE&t;&t;0x80090000
DECL|macro|IO_EC_MEMC_BASE
mdefine_line|#define IO_EC_MEMC_BASE&t;&t;0x80000000
macro_line|#ifdef CONFIG_ARCH_ARC
multiline_comment|/* A680 hardware */
DECL|macro|WD1973_BASE
mdefine_line|#define WD1973_BASE&t;&t;0x03290000
DECL|macro|WD1973_LATCH
mdefine_line|#define WD1973_LATCH&t;&t;0x03350000
DECL|macro|Z8530_BASE
mdefine_line|#define Z8530_BASE&t;&t;0x032b0008
DECL|macro|SCSI_BASE
mdefine_line|#define SCSI_BASE&t;&t;0x03100000
macro_line|#endif
macro_line|#endif
DECL|macro|EXPMASK_STATUS
mdefine_line|#define&t;EXPMASK_STATUS&t;&t;(EXPMASK_BASE + 0x00)
DECL|macro|EXPMASK_ENABLE
mdefine_line|#define EXPMASK_ENABLE&t;&t;(EXPMASK_BASE + 0x04)
macro_line|#endif
eof
