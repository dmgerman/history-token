multiline_comment|/*&n; *  linux/include/asm-arm/arch-arc/hardware.h&n; *&n; *  Copyright (C) 1996-1999 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This file contains the hardware definitions of the&n; *  Acorn Archimedes/A5000 machines.&n; *&n; *  Modifications:&n; *   04-04-1998&t;PJB/RMK&t;Merged arc and a5k versions&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch/memory.h&gt;
multiline_comment|/*&n; * What hardware must be present - these can be tested by the kernel&n; * source.&n; */
DECL|macro|HAS_IOC
mdefine_line|#define HAS_IOC
DECL|macro|HAS_MEMC
mdefine_line|#define HAS_MEMC
macro_line|#include &lt;asm/hardware/memc.h&gt;
DECL|macro|HAS_VIDC
mdefine_line|#define HAS_VIDC
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
DECL|macro|vidc_writel
mdefine_line|#define vidc_writel(val)&t;__raw_writel(val, VIDC_BASE)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * for use with inb/outb&n; */
macro_line|#ifdef CONFIG_ARCH_A5K
DECL|macro|IOEB_VID_CTL
mdefine_line|#define IOEB_VID_CTL&t;&t;(IOEB_BASE + 0x48)
DECL|macro|IOEB_PRESENT
mdefine_line|#define IOEB_PRESENT&t;&t;(IOEB_BASE + 0x50)
DECL|macro|IOEB_PSCLR
mdefine_line|#define IOEB_PSCLR&t;&t;(IOEB_BASE + 0x58)
DECL|macro|IOEB_MONTYPE
mdefine_line|#define IOEB_MONTYPE&t;&t;(IOEB_BASE + 0x70)
macro_line|#endif
DECL|macro|IO_EC_IOC4_BASE
mdefine_line|#define IO_EC_IOC4_BASE&t;&t;0x8009c000
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
