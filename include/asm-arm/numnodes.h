multiline_comment|/*&n; *  linux/include/asm-arm/numnodes.h&n; *&n; *  Copyright (C) 2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
multiline_comment|/* This declaration for the size of the NUMA (CONFIG_DISCONTIGMEM)&n; * memory node table is the default.&n; *&n; * A good place to override this value is include/asm/arch/memory.h.&n; */
macro_line|#ifndef __ASM_ARM_NUMNODES_H
DECL|macro|__ASM_ARM_NUMNODES_H
mdefine_line|#define __ASM_ARM_NUMNODES_H
macro_line|#ifndef NODES_SHIFT
DECL|macro|NODES_SHIFT
macro_line|# define NODES_SHIFT&t;2&t;/* Normally, Max 4 Nodes */
macro_line|#endif
macro_line|#endif
eof
