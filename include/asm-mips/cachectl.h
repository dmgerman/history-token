multiline_comment|/*&n; * cachectl.h -- defines for MIPS cache control system calls&n; *&n; * Copyright (C) 1994, 1995, 1996 by Ralf Baechle&n; */
macro_line|#ifndef&t;__ASM_MIPS_CACHECTL
DECL|macro|__ASM_MIPS_CACHECTL
mdefine_line|#define&t;__ASM_MIPS_CACHECTL
multiline_comment|/*&n; * Options for cacheflush system call&n; */
DECL|macro|ICACHE
mdefine_line|#define&t;ICACHE&t;(1&lt;&lt;0)&t;&t;/* flush instruction cache        */
DECL|macro|DCACHE
mdefine_line|#define&t;DCACHE&t;(1&lt;&lt;1)&t;&t;/* writeback and flush data cache */
DECL|macro|BCACHE
mdefine_line|#define&t;BCACHE&t;(ICACHE|DCACHE)&t;/* flush both caches              */
multiline_comment|/*&n; * Caching modes for the cachectl(2) call&n; *&n; * cachctl(2) is currently not supported and returns ENOSYS.&n; */
DECL|macro|CACHEABLE
mdefine_line|#define CACHEABLE&t;0&t;/* make pages cacheable */
DECL|macro|UNCACHEABLE
mdefine_line|#define UNCACHEABLE&t;1&t;/* make pages uncacheable */
macro_line|#endif&t;/* __ASM_MIPS_CACHECTL */
eof
