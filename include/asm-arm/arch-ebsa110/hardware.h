multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa110/hardware.h&n; *&n; *  Copyright (C) 1996-2000 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This file contains the hardware definitions of the EBSA-110.&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
multiline_comment|/*&n; * The EBSA110 has a weird &quot;ISA IO&quot; region:&n; *&n; * Region 0 (addr = 0xf0000000 + io &lt;&lt; 2)&n; * --------------------------------------------------------&n; * Physical region&t;IO region&n; * f0000fe0 - f0000ffc&t;3f8 - 3ff  ttyS0&n; * f0000e60 - f0000e64&t;398 - 399&n; * f0000de0 - f0000dfc&t;378 - 37f  lp0&n; * f0000be0 - f0000bfc&t;2f8 - 2ff  ttyS1&n; *&n; * Region 1 (addr = 0xf0000000 + (io &amp; ~1) &lt;&lt; 1 + (io &amp; 1))&n; * --------------------------------------------------------&n; * Physical region&t;IO region&n; * f00014f1             a79        pnp write data&n; * f00007c0 - f00007c1&t;3e0 - 3e1  pcmcia&n; * f00004f1&t;&t;279        pnp address&n; * f0000440 - f000046c  220 - 236  eth0&n; * f0000405&t;&t;203        pnp read data&n; */
DECL|macro|ISAMEM_PHYS
mdefine_line|#define ISAMEM_PHYS&t;&t;0xe0000000
DECL|macro|ISAMEM_SIZE
mdefine_line|#define ISAMEM_SIZE&t;&t;0x10000000
DECL|macro|ISAIO_PHYS
mdefine_line|#define ISAIO_PHYS&t;&t;0xf0000000
DECL|macro|ISAIO_SIZE
mdefine_line|#define ISAIO_SIZE&t;&t;PGDIR_SIZE
DECL|macro|TRICK0_PHYS
mdefine_line|#define TRICK0_PHYS&t;&t;0xf2000000
DECL|macro|TRICK1_PHYS
mdefine_line|#define TRICK1_PHYS&t;&t;0xf2400000
DECL|macro|TRICK2_PHYS
mdefine_line|#define TRICK2_PHYS&t;&t;0xf2800000
DECL|macro|TRICK3_PHYS
mdefine_line|#define TRICK3_PHYS&t;&t;0xf2c00000
DECL|macro|TRICK4_PHYS
mdefine_line|#define TRICK4_PHYS&t;&t;0xf3000000
DECL|macro|TRICK5_PHYS
mdefine_line|#define TRICK5_PHYS&t;&t;0xf3400000
DECL|macro|TRICK6_PHYS
mdefine_line|#define TRICK6_PHYS&t;&t;0xf3800000
DECL|macro|TRICK7_PHYS
mdefine_line|#define TRICK7_PHYS&t;&t;0xf3c00000
DECL|macro|ISAMEM_BASE
mdefine_line|#define ISAMEM_BASE&t;&t;0xe0000000
DECL|macro|ISAIO_BASE
mdefine_line|#define ISAIO_BASE&t;&t;0xf0000000
DECL|macro|PIT_BASE
mdefine_line|#define PIT_BASE&t;&t;0xfc000000
DECL|macro|SOFT_BASE
mdefine_line|#define SOFT_BASE&t;&t;0xfd000000
multiline_comment|/*&n; * RAM definitions&n; */
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x40000000
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xdf000000
DECL|macro|UNCACHEABLE_ADDR
mdefine_line|#define UNCACHEABLE_ADDR&t;0xff000000&t;/* IRQ_STAT */
macro_line|#endif
eof
