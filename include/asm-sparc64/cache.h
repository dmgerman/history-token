multiline_comment|/*&n; * include/asm-sparc64/cache.h&n; */
macro_line|#ifndef __ARCH_SPARC64_CACHE_H
DECL|macro|__ARCH_SPARC64_CACHE_H
mdefine_line|#define __ARCH_SPARC64_CACHE_H
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_SHIFT
mdefine_line|#define        L1_CACHE_SHIFT&t;5
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES&t;32 /* Two 16-byte sub-blocks per line. */
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define        L1_CACHE_ALIGN(x)       (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
DECL|macro|SMP_CACHE_BYTES_SHIFT
mdefine_line|#define        SMP_CACHE_BYTES_SHIFT&t;6
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define        SMP_CACHE_BYTES&t;&t;(1 &lt;&lt; SMP_CACHE_BYTES_SHIFT) /* L2 cache line size. */
macro_line|#ifdef MODULE
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__((__aligned__(SMP_CACHE_BYTES)))
macro_line|#else
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned&t;&t;&t;&t;&t;&bslash;&n;  __attribute__((__aligned__(SMP_CACHE_BYTES),&t;&t;&t;&bslash;&n;&t;&t; __section__(&quot;.data.cacheline_aligned&quot;)))
macro_line|#endif
macro_line|#endif
eof
