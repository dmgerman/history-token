multiline_comment|/*&n; *  linux/arch/arm/mm/proc-syms.c&n; *&n; *  Copyright (C) 2000-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/proc-fns.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#ifndef MULTI_CPU
DECL|variable|cpu_dcache_clean_area
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_dcache_clean_area
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
macro_line|#ifndef MULTI_CACHE
DECL|variable|__cpuc_flush_kern_all
id|EXPORT_SYMBOL
c_func
(paren
id|__cpuc_flush_kern_all
)paren
suffix:semicolon
DECL|variable|__cpuc_flush_user_all
id|EXPORT_SYMBOL
c_func
(paren
id|__cpuc_flush_user_all
)paren
suffix:semicolon
DECL|variable|__cpuc_flush_user_range
id|EXPORT_SYMBOL
c_func
(paren
id|__cpuc_flush_user_range
)paren
suffix:semicolon
DECL|variable|__cpuc_coherent_kern_range
id|EXPORT_SYMBOL
c_func
(paren
id|__cpuc_coherent_kern_range
)paren
suffix:semicolon
macro_line|#else
DECL|variable|cpu_cache
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_cache
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
