multiline_comment|/*&n; *  linux/include/asm-arm/cpu-single.h&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
multiline_comment|/*&n; * Single CPU&n; */
macro_line|#ifdef __STDC__
DECL|macro|__catify_fn
mdefine_line|#define __catify_fn(name,x)&t;name##x
macro_line|#else
DECL|macro|__catify_fn
mdefine_line|#define __catify_fn(name,x)&t;name/**/x
macro_line|#endif
DECL|macro|__cpu_fn
mdefine_line|#define __cpu_fn(name,x)&t;__catify_fn(name,x)
multiline_comment|/*&n; * If we are supporting multiple CPUs, then we must use a table of&n; * function pointers for this lot.  Otherwise, we can optimise the&n; * table away.&n; */
DECL|macro|cpu_data_abort
mdefine_line|#define cpu_data_abort&t;&t;&t;__cpu_fn(CPU_ABRT,_abort)
DECL|macro|cpu_check_bugs
mdefine_line|#define cpu_check_bugs&t;&t;&t;__cpu_fn(CPU_NAME,_check_bugs)
DECL|macro|cpu_proc_init
mdefine_line|#define cpu_proc_init&t;&t;&t;__cpu_fn(CPU_NAME,_proc_init)
DECL|macro|cpu_proc_fin
mdefine_line|#define cpu_proc_fin&t;&t;&t;__cpu_fn(CPU_NAME,_proc_fin)
DECL|macro|cpu_reset
mdefine_line|#define cpu_reset&t;&t;&t;__cpu_fn(CPU_NAME,_reset)
DECL|macro|cpu_do_idle
mdefine_line|#define cpu_do_idle&t;&t;&t;__cpu_fn(CPU_NAME,_do_idle)
DECL|macro|cpu_cache_clean_invalidate_all
mdefine_line|#define cpu_cache_clean_invalidate_all&t;__cpu_fn(CPU_NAME,_cache_clean_invalidate_all)
DECL|macro|cpu_cache_clean_invalidate_range
mdefine_line|#define cpu_cache_clean_invalidate_range __cpu_fn(CPU_NAME,_cache_clean_invalidate_range)
DECL|macro|cpu_flush_ram_page
mdefine_line|#define cpu_flush_ram_page&t;&t;__cpu_fn(CPU_NAME,_flush_ram_page)
DECL|macro|cpu_dcache_invalidate_range
mdefine_line|#define cpu_dcache_invalidate_range&t;__cpu_fn(CPU_NAME,_dcache_invalidate_range)
DECL|macro|cpu_dcache_clean_range
mdefine_line|#define cpu_dcache_clean_range&t;&t;__cpu_fn(CPU_NAME,_dcache_clean_range)
DECL|macro|cpu_dcache_clean_page
mdefine_line|#define cpu_dcache_clean_page&t;&t;__cpu_fn(CPU_NAME,_dcache_clean_page)
DECL|macro|cpu_dcache_clean_entry
mdefine_line|#define cpu_dcache_clean_entry&t;&t;__cpu_fn(CPU_NAME,_dcache_clean_entry)
DECL|macro|cpu_icache_invalidate_range
mdefine_line|#define cpu_icache_invalidate_range&t;__cpu_fn(CPU_NAME,_icache_invalidate_range)
DECL|macro|cpu_icache_invalidate_page
mdefine_line|#define cpu_icache_invalidate_page&t;__cpu_fn(CPU_NAME,_icache_invalidate_page)
DECL|macro|cpu_set_pgd
mdefine_line|#define cpu_set_pgd&t;&t;&t;__cpu_fn(CPU_NAME,_set_pgd)
DECL|macro|cpu_set_pmd
mdefine_line|#define cpu_set_pmd&t;&t;&t;__cpu_fn(CPU_NAME,_set_pmd)
DECL|macro|cpu_set_pte
mdefine_line|#define cpu_set_pte&t;&t;&t;__cpu_fn(CPU_NAME,_set_pte)
DECL|macro|cpu_copy_user_page
mdefine_line|#define cpu_copy_user_page&t;&t;__cpu_fn(MMU_ARCH,_copy_user_page)
DECL|macro|cpu_clear_user_page
mdefine_line|#define cpu_clear_user_page&t;&t;__cpu_fn(MMU_ARCH,_clear_user_page)
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* forward declare task_struct */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* declare all the functions as extern */
r_extern
r_void
id|cpu_data_abort
c_func
(paren
r_int
r_int
id|pc
)paren
suffix:semicolon
r_extern
r_void
id|cpu_check_bugs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_proc_fin
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cpu_do_idle
c_func
(paren
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_void
id|cpu_cache_clean_invalidate_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_cache_clean_invalidate_range
c_func
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
r_extern
r_void
id|cpu_flush_ram_page
c_func
(paren
r_void
op_star
id|virt_page
)paren
suffix:semicolon
r_extern
r_void
id|cpu_dcache_invalidate_range
c_func
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
id|cpu_dcache_clean_range
c_func
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
id|cpu_dcache_clean_page
c_func
(paren
r_void
op_star
id|virt_page
)paren
suffix:semicolon
r_extern
r_void
id|cpu_dcache_clean_entry
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_void
id|cpu_icache_invalidate_range
c_func
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
id|cpu_icache_invalidate_page
c_func
(paren
r_void
op_star
id|virt_page
)paren
suffix:semicolon
r_extern
r_void
id|cpu_set_pgd
c_func
(paren
r_int
r_int
id|pgd_phys
)paren
suffix:semicolon
r_extern
r_void
id|cpu_set_pmd
c_func
(paren
id|pmd_t
op_star
id|pmdp
comma
id|pmd_t
id|pmd
)paren
suffix:semicolon
r_extern
r_void
id|cpu_set_pte
c_func
(paren
id|pte_t
op_star
id|ptep
comma
id|pte_t
id|pte
)paren
suffix:semicolon
r_extern
r_void
id|cpu_copy_user_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
comma
r_int
r_int
id|u_addr
)paren
suffix:semicolon
r_extern
r_void
id|cpu_clear_user_page
c_func
(paren
r_void
op_star
id|page
comma
r_int
r_int
id|u_addr
)paren
suffix:semicolon
r_extern
r_volatile
r_void
id|cpu_reset
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|macro|cpu_switch_mm
mdefine_line|#define cpu_switch_mm(pgd,tsk) cpu_set_pgd(__virt_to_phys((unsigned long)(pgd)))
DECL|macro|cpu_get_pgd
mdefine_line|#define cpu_get_pgd()&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long pg;&t;&t;&t;&bslash;&n;&t;&t;__asm__(&quot;mrc p15, 0, %0, c2, c0, 0&quot;&t;&bslash;&n;&t;&t;&t; : &quot;=r&quot; (pg));&t;&t;&t;&bslash;&n;&t;&t;pg &amp;= ~0x3fff;&t;&t;&t;&t;&bslash;&n;&t;&t;(pgd_t *)phys_to_virt(pg);&t;&t;&bslash;&n;&t;})
macro_line|#endif
eof
