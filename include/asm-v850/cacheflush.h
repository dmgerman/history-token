multiline_comment|/*&n; * include/asm-v850/cacheflush.h&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_CACHEFLUSH_H__
DECL|macro|__V850_CACHEFLUSH_H__
mdefine_line|#define __V850_CACHEFLUSH_H__
multiline_comment|/* Somebody depends on this; sigh...  */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
multiline_comment|/* The following are all used by the kernel in ways that only affect&n;   systems with MMUs, so we don&squot;t need them.  */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;((void)0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;((void)0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma, start, end)&t;((void)0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr)&t;&t;((void)0)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;((void)0)
macro_line|#ifdef CONFIG_NO_CACHE
multiline_comment|/* Some systems have no cache at all, in which case we don&squot;t need these&n;   either.  */
DECL|macro|flush_icache
mdefine_line|#define flush_icache()&t;&t;&t;&t;((void)0)
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;((void)0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)&t;&t;((void)0)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,pg,adr,len)&t;((void)0)
DECL|macro|flush_cache_sigtramp
mdefine_line|#define flush_cache_sigtramp(vaddr)&t;&t;((void)0)
macro_line|#else /* !CONFIG_NO_CACHE */
r_struct
id|page
suffix:semicolon
r_struct
id|mm_struct
suffix:semicolon
r_struct
id|vm_area_struct
suffix:semicolon
multiline_comment|/* Otherwise, somebody had better define them.  */
r_extern
r_void
id|flush_icache
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|flush_icache_range
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|flush_icache_page
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
id|flush_icache_user_range
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|adr
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|flush_cache_sigtramp
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NO_CACHE */
macro_line|#endif /* __V850_CACHEFLUSH_H__ */
eof
