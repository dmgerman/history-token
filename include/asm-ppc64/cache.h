multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ARCH_PPC64_CACHE_H
DECL|macro|__ARCH_PPC64_CACHE_H
mdefine_line|#define __ARCH_PPC64_CACHE_H
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_SHIFT
mdefine_line|#define L1_CACHE_SHIFT&t;7
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;(1 &lt;&lt; L1_CACHE_SHIFT)
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES L1_CACHE_BYTES
DECL|macro|L1_CACHE_SHIFT_MAX
mdefine_line|#define L1_CACHE_SHIFT_MAX 7&t;/* largest L1 which this arch supports */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|ppc64_caches
r_struct
id|ppc64_caches
(brace
DECL|member|dsize
id|u32
id|dsize
suffix:semicolon
multiline_comment|/* L1 d-cache size */
DECL|member|dline_size
id|u32
id|dline_size
suffix:semicolon
multiline_comment|/* L1 d-cache line size&t;*/
DECL|member|log_dline_size
id|u32
id|log_dline_size
suffix:semicolon
DECL|member|dlines_per_page
id|u32
id|dlines_per_page
suffix:semicolon
DECL|member|isize
id|u32
id|isize
suffix:semicolon
multiline_comment|/* L1 i-cache size */
DECL|member|iline_size
id|u32
id|iline_size
suffix:semicolon
multiline_comment|/* L1 i-cache line size&t;*/
DECL|member|log_iline_size
id|u32
id|log_iline_size
suffix:semicolon
DECL|member|ilines_per_page
id|u32
id|ilines_per_page
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ppc64_caches
id|ppc64_caches
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
