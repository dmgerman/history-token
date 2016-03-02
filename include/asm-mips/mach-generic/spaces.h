multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 99 Ralf Baechle&n; * Copyright (C) 2000, 2002  Maciej W. Rozycki&n; * Copyright (C) 1990, 1999 by Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_MACH_SPACES_H
DECL|macro|_ASM_MACH_SPACES_H
mdefine_line|#define _ASM_MACH_SPACES_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_MIPS32
DECL|macro|CAC_BASE
mdefine_line|#define CAC_BASE&t;&t;0x80000000
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xa0000000
DECL|macro|UNCAC_BASE
mdefine_line|#define UNCAC_BASE&t;&t;0xa0000000
DECL|macro|MAP_BASE
mdefine_line|#define MAP_BASE&t;&t;0xc0000000
macro_line|#endif /* CONFIG_MIPS32 */
macro_line|#ifdef CONFIG_MIPS64
macro_line|#ifdef CONFIG_DMA_NONCOHERENT
DECL|macro|CAC_BASE
mdefine_line|#define CAC_BASE&t;&t;0x9800000000000000
macro_line|#else
DECL|macro|CAC_BASE
mdefine_line|#define CAC_BASE&t;&t;0xa800000000000000
macro_line|#endif
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0x9000000000000000
DECL|macro|UNCAC_BASE
mdefine_line|#define UNCAC_BASE&t;&t;0x9000000000000000
DECL|macro|MAP_BASE
mdefine_line|#define MAP_BASE&t;&t;0xc000000000000000
DECL|macro|TO_PHYS
mdefine_line|#define TO_PHYS(x)&t;&t;(             ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_CAC
mdefine_line|#define TO_CAC(x)&t;&t;(CAC_BASE   | ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_UNCAC
mdefine_line|#define TO_UNCAC(x)&t;&t;(UNCAC_BASE | ((x) &amp; TO_PHYS_MASK))
macro_line|#endif /* CONFIG_MIPS64 */
macro_line|#endif /* _ASM_MACH_SPACES_H */
eof
