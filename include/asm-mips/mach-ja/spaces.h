multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999, 2000, 03, 04 Ralf Baechle&n; * Copyright (C) 2000, 2002  Maciej W. Rozycki&n; * Copyright (C) 1990, 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef __ASM_MACH_JA_SPACES_H
DECL|macro|__ASM_MACH_JA_SPACES_H
mdefine_line|#define __ASM_MACH_JA_SPACES_H
multiline_comment|/*&n; * Memory above this physical address will be considered highmem.&n; */
DECL|macro|HIGHMEM_START
mdefine_line|#define HIGHMEM_START&t;&t;0x08000000UL
macro_line|#include_next &lt;spaces.h&gt;
macro_line|#endif /* __ASM_MACH_JA_SPACES_H */
eof
