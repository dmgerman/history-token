multiline_comment|/*&n; * Copyright (C) 2004 2N Telekomunikace, Ladislav Michl &lt;michl@2n.cz&gt;&n; *&n; * Hardware definitions for OMAP5910 based NetStar board.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARCH_NETSTAR_H
DECL|macro|__ASM_ARCH_NETSTAR_H
mdefine_line|#define __ASM_ARCH_NETSTAR_H
macro_line|#include &lt;asm/arch/tc.h&gt;
DECL|macro|OMAP_NAND_FLASH_START1
mdefine_line|#define OMAP_NAND_FLASH_START1&t;&t;OMAP_CS1_PHYS + (1 &lt;&lt; 23)
DECL|macro|OMAP_NAND_FLASH_START2
mdefine_line|#define OMAP_NAND_FLASH_START2&t;&t;OMAP_CS1_PHYS + (2 &lt;&lt; 23)
macro_line|#endif /*  __ASM_ARCH_NETSTAR_H */
eof
