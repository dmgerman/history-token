multiline_comment|/* $Id: cache.h,v 1.4 2003/05/06 23:28:50 lethal Exp $&n; *&n; * include/asm-sh/cache.h&n; *&n; * Copyright 1999 (C) Niibe Yutaka&n; * Copyright 2002, 2003 (C) Paul Mundt&n; */
macro_line|#ifndef __ASM_SH_CACHE_H
DECL|macro|__ASM_SH_CACHE_H
mdefine_line|#define __ASM_SH_CACHE_H
macro_line|#include &lt;asm/cpu/cache.h&gt;
macro_line|#include &lt;asm/cpu/cacheflush.h&gt;
DECL|macro|SH_CACHE_VALID
mdefine_line|#define SH_CACHE_VALID&t;&t;1
DECL|macro|SH_CACHE_UPDATED
mdefine_line|#define SH_CACHE_UPDATED&t;2
DECL|macro|SH_CACHE_COMBINED
mdefine_line|#define SH_CACHE_COMBINED&t;4
DECL|macro|SH_CACHE_ASSOC
mdefine_line|#define SH_CACHE_ASSOC&t;&t;8
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES L1_CACHE_BYTES
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define L1_CACHE_ALIGN(x)&t;(((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
macro_line|#ifdef MODULE
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__((__aligned__(L1_CACHE_BYTES)))
macro_line|#else
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned&t;&t;&t;&t;&t;&bslash;&n;  __attribute__((__aligned__(L1_CACHE_BYTES),&t;&t;&t;&bslash;&n;&t;&t; __section__(&quot;.data.cacheline_aligned&quot;)))
macro_line|#endif
DECL|macro|L1_CACHE_SHIFT_MAX
mdefine_line|#define L1_CACHE_SHIFT_MAX 5&t;/* largest L1 which this arch supports */
DECL|struct|cache_info
r_struct
id|cache_info
(brace
DECL|member|ways
r_int
r_int
id|ways
suffix:semicolon
DECL|member|sets
r_int
r_int
id|sets
suffix:semicolon
DECL|member|linesz
r_int
r_int
id|linesz
suffix:semicolon
DECL|member|way_shift
r_int
r_int
id|way_shift
suffix:semicolon
DECL|member|entry_shift
r_int
r_int
id|entry_shift
suffix:semicolon
DECL|member|entry_mask
r_int
r_int
id|entry_mask
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flush (write-back only) a region (smaller than a page) */
r_extern
r_void
id|__flush_wback_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Flush (write-back &amp; invalidate) a region (smaller than a page) */
r_extern
r_void
id|__flush_purge_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Flush (invalidate only) a region (smaller than a page) */
r_extern
r_void
id|__flush_invalidate_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
suffix:semicolon
macro_line|#endif /* __ASM_SH_CACHE_H */
eof
