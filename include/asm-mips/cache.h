multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 98, 99, 2000 Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_CACHE_H
DECL|macro|_ASM_CACHE_H
mdefine_line|#define _ASM_CACHE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef _LANGUAGE_ASSEMBLY
multiline_comment|/*&n; * Descriptor for a cache&n; */
DECL|struct|cache_desc
r_struct
id|cache_desc
(brace
DECL|member|linesz
r_int
id|linesz
suffix:semicolon
DECL|member|sets
r_int
id|sets
suffix:semicolon
DECL|member|ways
r_int
id|ways
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* Details like write thru/back, coherent, etc. */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Flag definitions&n; */
DECL|macro|MIPS_CACHE_NOT_PRESENT
mdefine_line|#define MIPS_CACHE_NOT_PRESENT 0x00000001
macro_line|#if defined(CONFIG_CPU_R3000) || defined(CONFIG_CPU_R6000)
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;16
macro_line|#else
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES &t;&t;32&t;/* A guess */
macro_line|#endif
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES&t;&t;L1_CACHE_BYTES
macro_line|#endif /* _ASM_CACHE_H */
eof
