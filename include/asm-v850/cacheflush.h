multiline_comment|/*&n; * include/asm-v850/cacheflush.h&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_CACHEFLUSH_H__
DECL|macro|__V850_CACHEFLUSH_H__
mdefine_line|#define __V850_CACHEFLUSH_H__
multiline_comment|/* Somebody depends on this; sigh...  */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#ifndef flush_cache_all
multiline_comment|/* If there&squot;s no flush_cache_all macro defined by &lt;asm/machdep.h&gt;, then&n;   this processor has no cache, so just define these as nops.  */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;((void)0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;((void)0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma, start, end)&t;((void)0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr)&t;&t;((void)0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;((void)0)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;((void)0)
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
macro_line|#endif /* !flush_cache_all */
macro_line|#endif /* __V850_CACHEFLUSH_H__ */
eof
