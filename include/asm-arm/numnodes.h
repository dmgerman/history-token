multiline_comment|/*&n; *  linux/include/asm-arm/numnodes.h&n; *&n; *  Copyright (C) 2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_NUMNODES_H
DECL|macro|__ASM_ARM_NUMNODES_H
mdefine_line|#define __ASM_ARM_NUMNODES_H
macro_line|#ifdef CONFIG_ARCH_LH7A40X
DECL|macro|NODES_SHIFT
macro_line|# define NODES_SHIFT&t;4&t;/* Max 16 nodes for the Sharp CPUs */
macro_line|#else
DECL|macro|NODES_SHIFT
macro_line|# define NODES_SHIFT&t;2&t;/* Normally, Max 4 Nodes */
macro_line|#endif
macro_line|#endif
eof
