multiline_comment|/* cache.h: FRV cache definitions&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_CACHE_H
DECL|macro|__ASM_CACHE_H
mdefine_line|#define __ASM_CACHE_H
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_SHIFT
mdefine_line|#define L1_CACHE_SHIFT&t;&t;5
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;(1 &lt;&lt; L1_CACHE_SHIFT)
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned&t;__attribute__((aligned(L1_CACHE_BYTES)))
DECL|macro|____cacheline_aligned
mdefine_line|#define ____cacheline_aligned&t;__attribute__((aligned(L1_CACHE_BYTES)))
macro_line|#endif
eof
