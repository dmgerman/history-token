multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 99 Ralf Baechle&n; * Copyright (C) 2000, 2002  Maciej W. Rozycki&n; * Copyright (C) 1990, 1999 by Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_MACH_IP27_SPACES_H
DECL|macro|_ASM_MACH_IP27_SPACES_H
mdefine_line|#define _ASM_MACH_IP27_SPACES_H
multiline_comment|/*&n; * IP27 uses the R10000&squot;s uncached attribute feature.  Attribute 3 selects&n; * uncached memory addressing.&n; */
DECL|macro|CAC_BASE
mdefine_line|#define CAC_BASE&t;&t;0xa800000000000000
DECL|macro|HSPEC_BASE
mdefine_line|#define HSPEC_BASE&t;&t;0x9000000000000000
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0x9200000000000000
DECL|macro|MSPEC_BASE
mdefine_line|#define MSPEC_BASE&t;&t;0x9400000000000000
DECL|macro|UNCAC_BASE
mdefine_line|#define UNCAC_BASE&t;&t;0x9600000000000000
DECL|macro|TO_PHYS
mdefine_line|#define TO_PHYS(x)&t;&t;(             ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_CAC
mdefine_line|#define TO_CAC(x)&t;&t;(CAC_BASE   | ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_UNCAC
mdefine_line|#define TO_UNCAC(x)&t;&t;(UNCAC_BASE | ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_MSPEC
mdefine_line|#define TO_MSPEC(x)&t;&t;(MSPEC_BASE | ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_HSPEC
mdefine_line|#define TO_HSPEC(x)&t;&t;(HSPEC_BASE | ((x) &amp; TO_PHYS_MASK))
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;CAC_BASE
DECL|macro|HIGHMEM_START
mdefine_line|#define HIGHMEM_START&t;&t;(~0UL)
macro_line|#endif /* _ASM_MACH_IP27_SPACES_H */
eof
