multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999, 2000, 03 Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PAGE_32_H
DECL|macro|_ASM_PAGE_32_H
mdefine_line|#define _ASM_PAGE_32_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * This handles the memory map.&n; * We handle pages at KSEG0 for kernels with 32 bit address space.&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;0x80000000UL
DECL|macro|UNCAC_BASE
mdefine_line|#define UNCAC_BASE&t;&t;0xa0000000UL
multiline_comment|/*&n; * Memory above this physical address will be considered highmem.&n; */
DECL|macro|HIGHMEM_START
mdefine_line|#define HIGHMEM_START&t;&t;0x20000000UL
macro_line|#endif /* _ASM_PAGE_32_H */
eof
