multiline_comment|/*&n; *  linux/include/asm-arm26/cache.h&n; */
macro_line|#ifndef __ASMARM_CACHE_H
DECL|macro|__ASMARM_CACHE_H
mdefine_line|#define __ASMARM_CACHE_H
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  32
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define        L1_CACHE_ALIGN(x)       (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define        SMP_CACHE_BYTES L1_CACHE_BYTES
macro_line|#endif
eof
