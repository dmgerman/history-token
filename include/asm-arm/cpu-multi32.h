multiline_comment|/*&n; *  linux/include/asm-arm/cpu-multi32.h&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* forward-declare task_struct */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/*&n; * Don&squot;t change this structure - ASM code&n; * relies on it.&n; */
DECL|struct|processor
r_extern
r_struct
id|processor
(brace
multiline_comment|/* MISC&n;&t; * get data abort address/flags&n;&t; */
DECL|member|_data_abort
r_void
(paren
op_star
id|_data_abort
)paren
(paren
r_int
r_int
id|pc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * check for any bugs&n;&t; */
DECL|member|_check_bugs
r_void
(paren
op_star
id|_check_bugs
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up any processor specifics&n;&t; */
DECL|member|_proc_init
r_void
(paren
op_star
id|_proc_init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable any processor specifics&n;&t; */
DECL|member|_proc_fin
r_void
(paren
op_star
id|_proc_fin
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Special stuff for a reset&n;&t; */
DECL|member|reset
r_volatile
r_void
(paren
op_star
id|reset
)paren
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Idle the processor&n;&t; */
DECL|member|_do_idle
r_int
(paren
op_star
id|_do_idle
)paren
(paren
r_int
id|mode
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Processor architecture specific&n;&t; */
r_struct
(brace
multiline_comment|/* CACHE */
multiline_comment|/*&n;&t;&t; * flush all caches&n;&t;&t; */
DECL|member|clean_invalidate_all
r_void
(paren
op_star
id|clean_invalidate_all
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * flush a specific page or pages&n;&t;&t; */
DECL|member|clean_invalidate_range
r_void
(paren
op_star
id|clean_invalidate_range
)paren
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|end
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * flush a page to RAM&n;&t;&t; */
DECL|member|_flush_ram_page
r_void
(paren
op_star
id|_flush_ram_page
)paren
(paren
r_void
op_star
id|virt_page
)paren
suffix:semicolon
DECL|member|cache
)brace
id|cache
suffix:semicolon
r_struct
(brace
multiline_comment|/* D-cache */
multiline_comment|/*&n;&t;&t; * invalidate the specified data range&n;&t;&t; */
DECL|member|invalidate_range
r_void
(paren
op_star
id|invalidate_range
)paren
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
multiline_comment|/*&n;&t;&t; * clean specified data range&n;&t;&t; */
DECL|member|clean_range
r_void
(paren
op_star
id|clean_range
)paren
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
multiline_comment|/*&n;&t;&t; * obsolete flush cache entry&n;&t;&t; */
DECL|member|clean_page
r_void
(paren
op_star
id|clean_page
)paren
(paren
r_void
op_star
id|virt_page
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * clean a virtual address range from the&n;&t;&t; * D-cache without flushing the cache.&n;&t;&t; */
DECL|member|clean_entry
r_void
(paren
op_star
id|clean_entry
)paren
(paren
r_int
r_int
id|start
)paren
suffix:semicolon
DECL|member|dcache
)brace
id|dcache
suffix:semicolon
r_struct
(brace
multiline_comment|/* I-cache */
multiline_comment|/*&n;&t;&t; * invalidate the I-cache for the specified range&n;&t;&t; */
DECL|member|invalidate_range
r_void
(paren
op_star
id|invalidate_range
)paren
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
multiline_comment|/*&n;&t;&t; * invalidate the I-cache for the specified virtual page&n;&t;&t; */
DECL|member|invalidate_page
r_void
(paren
op_star
id|invalidate_page
)paren
(paren
r_void
op_star
id|virt_page
)paren
suffix:semicolon
DECL|member|icache
)brace
id|icache
suffix:semicolon
r_struct
(brace
multiline_comment|/* PageTable */
multiline_comment|/*&n;&t;&t; * Set the page table&n;&t;&t; */
DECL|member|set_pgd
r_void
(paren
op_star
id|set_pgd
)paren
(paren
r_int
r_int
id|pgd_phys
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set a PMD (handling IMP bit 4)&n;&t;&t; */
DECL|member|set_pmd
r_void
(paren
op_star
id|set_pmd
)paren
(paren
id|pmd_t
op_star
id|pmdp
comma
id|pmd_t
id|pmd
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set a PTE&n;&t;&t; */
DECL|member|set_pte
r_void
(paren
op_star
id|set_pte
)paren
(paren
id|pte_t
op_star
id|ptep
comma
id|pte_t
id|pte
)paren
suffix:semicolon
DECL|member|pgtable
)brace
id|pgtable
suffix:semicolon
)brace
id|processor
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|arm6_processor_functions
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|arm7_processor_functions
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|sa110_processor_functions
suffix:semicolon
DECL|macro|cpu_check_bugs
mdefine_line|#define cpu_check_bugs()&t;&t;&t;processor._check_bugs()
DECL|macro|cpu_proc_init
mdefine_line|#define cpu_proc_init()&t;&t;&t;&t;processor._proc_init()
DECL|macro|cpu_proc_fin
mdefine_line|#define cpu_proc_fin()&t;&t;&t;&t;processor._proc_fin()
DECL|macro|cpu_reset
mdefine_line|#define cpu_reset(addr)&t;&t;&t;&t;processor.reset(addr)
DECL|macro|cpu_do_idle
mdefine_line|#define cpu_do_idle(mode)&t;&t;&t;processor._do_idle(mode)
DECL|macro|cpu_cache_clean_invalidate_all
mdefine_line|#define cpu_cache_clean_invalidate_all()&t;processor.cache.clean_invalidate_all()
DECL|macro|cpu_cache_clean_invalidate_range
mdefine_line|#define cpu_cache_clean_invalidate_range(s,e,f)&t;processor.cache.clean_invalidate_range(s,e,f)
DECL|macro|cpu_flush_ram_page
mdefine_line|#define cpu_flush_ram_page(vp)&t;&t;&t;processor.cache._flush_ram_page(vp)
DECL|macro|cpu_dcache_clean_page
mdefine_line|#define cpu_dcache_clean_page(vp)&t;&t;processor.dcache.clean_page(vp)
DECL|macro|cpu_dcache_clean_entry
mdefine_line|#define cpu_dcache_clean_entry(addr)&t;&t;processor.dcache.clean_entry(addr)
DECL|macro|cpu_dcache_clean_range
mdefine_line|#define cpu_dcache_clean_range(s,e)&t;&t;processor.dcache.clean_range(s,e)
DECL|macro|cpu_dcache_invalidate_range
mdefine_line|#define cpu_dcache_invalidate_range(s,e)&t;processor.dcache.invalidate_range(s,e)
DECL|macro|cpu_icache_invalidate_range
mdefine_line|#define cpu_icache_invalidate_range(s,e)&t;processor.icache.invalidate_range(s,e)
DECL|macro|cpu_icache_invalidate_page
mdefine_line|#define cpu_icache_invalidate_page(vp)&t;&t;processor.icache.invalidate_page(vp)
DECL|macro|cpu_set_pgd
mdefine_line|#define cpu_set_pgd(pgd)&t;&t;&t;processor.pgtable.set_pgd(pgd)
DECL|macro|cpu_set_pmd
mdefine_line|#define cpu_set_pmd(pmdp, pmd)&t;&t;&t;processor.pgtable.set_pmd(pmdp, pmd)
DECL|macro|cpu_set_pte
mdefine_line|#define cpu_set_pte(ptep, pte)&t;&t;&t;processor.pgtable.set_pte(ptep, pte)
DECL|macro|cpu_switch_mm
mdefine_line|#define cpu_switch_mm(pgd,tsk)&t;&t;&t;cpu_set_pgd(__virt_to_phys((unsigned long)(pgd)))
DECL|macro|cpu_get_pgd
mdefine_line|#define cpu_get_pgd()&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long pg;&t;&t;&t;&bslash;&n;&t;&t;__asm__(&quot;mrc p15, 0, %0, c2, c0, 0&quot;&t;&bslash;&n;&t;&t;&t; : &quot;=r&quot; (pg));&t;&t;&t;&bslash;&n;&t;&t;pg &amp;= ~0x3fff;&t;&t;&t;&t;&bslash;&n;&t;&t;(pgd_t *)phys_to_virt(pg);&t;&t;&bslash;&n;&t;})
macro_line|#endif
eof
