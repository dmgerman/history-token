multiline_comment|/*&n; * arch/ppc/platforms/pal4.h&n; * &n; * Definitions for SBS Palomar IV board&n; *&n; * Author: Dan Cox&n; *&n; * 2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef __PPC_PLATFORMS_PAL4_H
DECL|macro|__PPC_PLATFORMS_PAL4_H
mdefine_line|#define __PPC_PLATFORMS_PAL4_H
DECL|macro|PAL4_NVRAM
mdefine_line|#define PAL4_NVRAM             0xfffc0000
DECL|macro|PAL4_NVRAM_SIZE
mdefine_line|#define PAL4_NVRAM_SIZE        0x8000
DECL|macro|PAL4_DRAM
mdefine_line|#define PAL4_DRAM              0xfff80000
DECL|macro|PAL4_DRAM_BR_MASK
mdefine_line|#define  PAL4_DRAM_BR_MASK     0xc0
DECL|macro|PAL4_DRAM_BR_SHIFT
mdefine_line|#define  PAL4_DRAM_BR_SHIFT    6
DECL|macro|PAL4_DRAM_RESET
mdefine_line|#define  PAL4_DRAM_RESET       0x10
DECL|macro|PAL4_DRAM_EREADY
mdefine_line|#define  PAL4_DRAM_EREADY      0x40
DECL|macro|PAL4_MISC
mdefine_line|#define PAL4_MISC              0xfff80004
DECL|macro|PAL4_MISC_FB_MASK
mdefine_line|#define  PAL4_MISC_FB_MASK     0xc0
DECL|macro|PAL4_MISC_FLASH
mdefine_line|#define  PAL4_MISC_FLASH       0x20  /* StratFlash mapping: 1-&gt;0xff80, 0-&gt;0xfff0 */
DECL|macro|PAL4_MISC_MISC
mdefine_line|#define  PAL4_MISC_MISC        0x08
DECL|macro|PAL4_MISC_BITF
mdefine_line|#define  PAL4_MISC_BITF        0x02
DECL|macro|PAL4_MISC_NVKS
mdefine_line|#define  PAL4_MISC_NVKS        0x01
DECL|macro|PAL4_L2
mdefine_line|#define PAL4_L2                0xfff80008
DECL|macro|PAL4_L2_MASK
mdefine_line|#define  PAL4_L2_MASK          0x07
DECL|macro|PAL4_PLDR
mdefine_line|#define PAL4_PLDR              0xfff8000c
multiline_comment|/* Only two Ethernet devices on the board... */
DECL|macro|PAL4_ETH
mdefine_line|#define PAL4_ETH               31
DECL|macro|PAL4_INTA
mdefine_line|#define PAL4_INTA              20
macro_line|#endif /* __PPC_PLATFORMS_PAL4_H */
eof
