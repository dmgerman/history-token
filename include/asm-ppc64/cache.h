multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ARCH_PPC64_CACHE_H
DECL|macro|__ARCH_PPC64_CACHE_H
mdefine_line|#define __ARCH_PPC64_CACHE_H
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_SHIFT
mdefine_line|#define L1_CACHE_SHIFT&t;7
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;(1 &lt;&lt; L1_CACHE_SHIFT)
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES L1_CACHE_BYTES
macro_line|#endif
eof
