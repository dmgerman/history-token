multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999, 2000, 03 Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PAGE_64_H
DECL|macro|_ASM_PAGE_64_H
mdefine_line|#define _ASM_PAGE_64_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * This handles the memory map.&n; */
macro_line|#ifdef CONFIG_NONCOHERENT_IO
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;0x9800000000000000UL
macro_line|#else
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;0xa800000000000000UL
macro_line|#endif
multiline_comment|/*&n; * Memory above this physical address will be considered highmem.&n; * Fixme: 59 bits is a fictive number and makes assumptions about processors&n; * in the distant future.  Nobody will care for a few years :-)&n; */
DECL|macro|HIGHMEM_START
mdefine_line|#define HIGHMEM_START&t;&t;(1UL &lt;&lt; 59UL)
macro_line|#endif /* _ASM_PAGE_64_H */
eof
