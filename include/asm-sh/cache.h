multiline_comment|/* $Id: cache.h,v 1.3 2000/07/04 06:24:49 gniibe Exp $&n; *&n; * include/asm-sh/cache.h&n; *&n; * Copyright 1999 (C) Niibe Yutaka&n; */
macro_line|#ifndef __ASM_SH_CACHE_H
DECL|macro|__ASM_SH_CACHE_H
mdefine_line|#define __ASM_SH_CACHE_H
multiline_comment|/* bytes per L1 cache line */
macro_line|#if defined(__sh3__)
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  16
macro_line|#elif defined(__SH4__)
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  32
macro_line|#endif
macro_line|#endif /* __ASM_SH_CACHE_H */
eof
