multiline_comment|/*&n; *  linux/arch/arm/mm/proc-syms.c&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/proc-fns.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#ifndef MULTI_CPU
DECL|variable|cpu_cache_clean_invalidate_all
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_cache_clean_invalidate_all
)paren
suffix:semicolon
DECL|variable|cpu_cache_clean_invalidate_range
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_cache_clean_invalidate_range
)paren
suffix:semicolon
DECL|variable|cpu_dcache_clean_page
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_dcache_clean_page
)paren
suffix:semicolon
DECL|variable|cpu_dcache_clean_entry
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_dcache_clean_entry
)paren
suffix:semicolon
DECL|variable|cpu_dcache_clean_range
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_dcache_clean_range
)paren
suffix:semicolon
DECL|variable|cpu_dcache_invalidate_range
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_dcache_invalidate_range
)paren
suffix:semicolon
DECL|variable|cpu_icache_invalidate_range
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_icache_invalidate_range
)paren
suffix:semicolon
DECL|variable|cpu_icache_invalidate_page
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_icache_invalidate_page
)paren
suffix:semicolon
DECL|variable|cpu_set_pgd
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_set_pgd
)paren
suffix:semicolon
DECL|variable|cpu_set_pmd
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_set_pmd
)paren
suffix:semicolon
DECL|variable|cpu_set_pte
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_set_pte
)paren
suffix:semicolon
macro_line|#else
DECL|variable|processor
id|EXPORT_SYMBOL
c_func
(paren
id|processor
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * No module should need to touch the TLB (and currently&n; * no modules do.  We export this for &quot;loadkernel&quot; support&n; * (booting a new kernel from within a running kernel.)&n; */
macro_line|#ifdef MULTI_TLB
DECL|variable|cpu_tlb
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_tlb
)paren
suffix:semicolon
macro_line|#endif
eof
