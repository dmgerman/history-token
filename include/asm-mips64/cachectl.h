multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996, 1999 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef&t;_ASM_CACHECTL
DECL|macro|_ASM_CACHECTL
mdefine_line|#define&t;_ASM_CACHECTL
multiline_comment|/*&n; * Options for cacheflush system call&n; */
DECL|macro|ICACHE
mdefine_line|#define&t;ICACHE&t;(1&lt;&lt;0)&t;&t;/* flush instruction cache        */
DECL|macro|DCACHE
mdefine_line|#define&t;DCACHE&t;(1&lt;&lt;1)&t;&t;/* writeback and flush data cache */
DECL|macro|BCACHE
mdefine_line|#define&t;BCACHE&t;(ICACHE|DCACHE)&t;/* flush both caches              */
multiline_comment|/*&n; * Caching modes for the cachectl(2) call&n; *&n; * cachectl(2) is currently not supported and returns ENOSYS.&n; */
DECL|macro|CACHEABLE
mdefine_line|#define CACHEABLE&t;0&t;/* make pages cacheable */
DECL|macro|UNCACHEABLE
mdefine_line|#define UNCACHEABLE&t;1&t;/* make pages uncacheable */
macro_line|#endif&t;/* _ASM_CACHECTL */
eof
