multiline_comment|/*&n; *  linux/include/asm-arm/cpu-multi32.h&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/page.h&gt;
r_struct
id|mm_struct
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
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Processor architecture specific&n;&t; */
multiline_comment|/*&n;&t; * clean a virtual address range from the&n;&t; * D-cache without flushing the cache.&n;&t; */
DECL|member|dcache_clean_area
r_void
(paren
op_star
id|dcache_clean_area
)paren
(paren
r_void
op_star
id|addr
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the page table&n;&t; */
DECL|member|switch_mm
r_void
(paren
op_star
id|switch_mm
)paren
(paren
r_int
r_int
id|pgd_phys
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set a PTE&n;&t; */
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
)brace
id|processor
suffix:semicolon
DECL|macro|cpu_check_bugs
mdefine_line|#define cpu_check_bugs()&t;&t;processor._check_bugs()
DECL|macro|cpu_proc_init
mdefine_line|#define cpu_proc_init()&t;&t;&t;processor._proc_init()
DECL|macro|cpu_proc_fin
mdefine_line|#define cpu_proc_fin()&t;&t;&t;processor._proc_fin()
DECL|macro|cpu_reset
mdefine_line|#define cpu_reset(addr)&t;&t;&t;processor.reset(addr)
DECL|macro|cpu_do_idle
mdefine_line|#define cpu_do_idle()&t;&t;&t;processor._do_idle()
DECL|macro|cpu_dcache_clean_area
mdefine_line|#define cpu_dcache_clean_area(addr,sz)&t;processor.dcache_clean_area(addr,sz)
DECL|macro|cpu_set_pte
mdefine_line|#define cpu_set_pte(ptep, pte)&t;&t;processor.set_pte(ptep, pte)
DECL|macro|cpu_switch_mm
mdefine_line|#define cpu_switch_mm(pgd,mm)&t;processor.switch_mm(__virt_to_phys((unsigned long)(pgd)),mm)
DECL|macro|cpu_get_pgd
mdefine_line|#define cpu_get_pgd()&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long pg;&t;&t;&t;&bslash;&n;&t;&t;__asm__(&quot;mrc&t;p15, 0, %0, c2, c0, 0&quot;&t;&bslash;&n;&t;&t;&t; : &quot;=r&quot; (pg) : : &quot;cc&quot;);&t;&t;&bslash;&n;&t;&t;pg &amp;= ~0x3fff;&t;&t;&t;&t;&bslash;&n;&t;&t;(pgd_t *)phys_to_virt(pg);&t;&t;&bslash;&n;&t;})
macro_line|#endif
eof
