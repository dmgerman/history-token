multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999, 2000, 03, 04, 05 Ralf Baechle (ralf@linux-mips.org)&n; * Copyright (C) 2000, 2002  Maciej W. Rozycki&n; * Copyright (C) 1990, 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_MACH_IP32_SPACES_H
DECL|macro|_ASM_MACH_IP32_SPACES_H
mdefine_line|#define _ASM_MACH_IP32_SPACES_H
multiline_comment|/*&n; * Memory above this physical address will be considered highmem.&n; * Fixme: 59 bits is a fictive number and makes assumptions about processors&n; * in the distant future.  Nobody will care for a few years :-)&n; */
macro_line|#ifndef HIGHMEM_START
DECL|macro|HIGHMEM_START
mdefine_line|#define HIGHMEM_START&t;&t;(1UL &lt;&lt; 59UL)
macro_line|#endif
DECL|macro|CAC_BASE
mdefine_line|#define CAC_BASE&t;&t;0x9800000000000000
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
multiline_comment|/*&n; * This handles the memory map.&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;CAC_BASE
macro_line|#endif /* __ASM_MACH_IP32_SPACES_H */
eof
