multiline_comment|/*&n; * include/asm-m68k/cache.h&n; */
macro_line|#ifndef __ARCH_M68K_CACHE_H
DECL|macro|__ARCH_M68K_CACHE_H
mdefine_line|#define __ARCH_M68K_CACHE_H
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_SHIFT
mdefine_line|#define        L1_CACHE_SHIFT  4
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  (1&lt;&lt; L1_CACHE_SHIFT)
DECL|macro|L1_CACHE_SHIFT_MAX
mdefine_line|#define L1_CACHE_SHIFT_MAX 4&t;/* largest L1 which this arch supports */
macro_line|#endif
eof
