multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/pgtable.h&n; *&n; *  Copyright (C) 1995-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  12-Jan-1997&t;RMK&t;Altered flushing routines to use function pointers&n; *&t;&t;&t;now possible to combine ARM6, ARM7 and StrongARM versions.&n; *  17-Apr-1999&t;RMK&t;Now pass an area size to clean_cache_area and&n; *&t;&t;&t;flush_icache_area.&n; */
macro_line|#ifndef __ASM_PROC_PGTABLE_H
DECL|macro|__ASM_PROC_PGTABLE_H
mdefine_line|#define __ASM_PROC_PGTABLE_H
macro_line|#include &lt;asm/proc/domain.h&gt;
macro_line|#include &lt;asm/arch/vmalloc.h&gt;
multiline_comment|/*&n; * entries per page directory level: they are two-level, so&n; * we don&squot;t really have any PMD directory.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;&t;256
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;&t;1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;&t;4096
multiline_comment|/****************&n;* PMD functions *&n;****************/
multiline_comment|/* PMD types (actually level 1 descriptor) */
DECL|macro|PMD_TYPE_MASK
mdefine_line|#define PMD_TYPE_MASK&t;&t;0x0003
DECL|macro|PMD_TYPE_FAULT
mdefine_line|#define PMD_TYPE_FAULT&t;&t;0x0000
DECL|macro|PMD_TYPE_TABLE
mdefine_line|#define PMD_TYPE_TABLE&t;&t;0x0001
DECL|macro|PMD_TYPE_SECT
mdefine_line|#define PMD_TYPE_SECT&t;&t;0x0002
DECL|macro|PMD_UPDATABLE
mdefine_line|#define PMD_UPDATABLE&t;&t;0x0010
DECL|macro|PMD_SECT_CACHEABLE
mdefine_line|#define PMD_SECT_CACHEABLE&t;0x0008
DECL|macro|PMD_SECT_BUFFERABLE
mdefine_line|#define PMD_SECT_BUFFERABLE&t;0x0004
DECL|macro|PMD_SECT_AP_WRITE
mdefine_line|#define PMD_SECT_AP_WRITE&t;0x0400
DECL|macro|PMD_SECT_AP_READ
mdefine_line|#define PMD_SECT_AP_READ&t;0x0800
DECL|macro|PMD_DOMAIN
mdefine_line|#define PMD_DOMAIN(x)&t;&t;((x) &lt;&lt; 5)
DECL|macro|_PAGE_USER_TABLE
mdefine_line|#define _PAGE_USER_TABLE&t;(PMD_TYPE_TABLE | PMD_DOMAIN(DOMAIN_USER))
DECL|macro|_PAGE_KERNEL_TABLE
mdefine_line|#define _PAGE_KERNEL_TABLE&t;(PMD_TYPE_TABLE | PMD_DOMAIN(DOMAIN_KERNEL))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;(pmd_val(pmd) &amp; 2)
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdp,pmd)&t;cpu_set_pmd(pmdp,pmd)
DECL|function|__mk_pmd
r_static
r_inline
id|pmd_t
id|__mk_pmd
c_func
(paren
id|pte_t
op_star
id|ptep
comma
r_int
r_int
id|prot
)paren
(brace
r_int
r_int
id|pte_ptr
op_assign
(paren
r_int
r_int
)paren
id|ptep
suffix:semicolon
id|pmd_t
id|pmd
suffix:semicolon
id|pte_ptr
op_sub_assign
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The pmd must be loaded with the physical&n;&t; * address of the PTE table&n;&t; */
id|pmd_val
c_func
(paren
id|pmd
)paren
op_assign
id|__virt_to_phys
c_func
(paren
id|pte_ptr
)paren
op_or
id|prot
suffix:semicolon
r_return
id|pmd
suffix:semicolon
)brace
DECL|function|pmd_page
r_static
r_inline
r_int
r_int
id|pmd_page
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_int
r_int
id|ptr
suffix:semicolon
id|ptr
op_assign
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
op_complement
(paren
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
r_void
op_star
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|ptr
op_add_assign
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
r_return
id|__phys_to_virt
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
multiline_comment|/****************&n;* PTE functions *&n;****************/
multiline_comment|/* PTE types (actually level 2 descriptor) */
DECL|macro|PTE_TYPE_MASK
mdefine_line|#define PTE_TYPE_MASK&t;&t;0x0003
DECL|macro|PTE_TYPE_FAULT
mdefine_line|#define PTE_TYPE_FAULT&t;&t;0x0000
DECL|macro|PTE_TYPE_LARGE
mdefine_line|#define PTE_TYPE_LARGE&t;&t;0x0001
DECL|macro|PTE_TYPE_SMALL
mdefine_line|#define PTE_TYPE_SMALL&t;&t;0x0002
DECL|macro|PTE_AP_READ
mdefine_line|#define PTE_AP_READ&t;&t;0x0aa0
DECL|macro|PTE_AP_WRITE
mdefine_line|#define PTE_AP_WRITE&t;&t;0x0550
DECL|macro|PTE_CACHEABLE
mdefine_line|#define PTE_CACHEABLE&t;&t;0x0008
DECL|macro|PTE_BUFFERABLE
mdefine_line|#define PTE_BUFFERABLE&t;&t;0x0004
DECL|macro|set_pte
mdefine_line|#define set_pte(ptep, pte)&t;cpu_set_pte(ptep,pte)
multiline_comment|/* We now keep two sets of ptes - the physical and the linux version.&n; * This gives us many advantages, and allows us greater flexibility.&n; *&n; * The Linux pte&squot;s contain:&n; *  bit   meaning&n; *   0    page present&n; *   1    young&n; *   2    bufferable&t;- matches physical pte&n; *   3    cacheable&t;- matches physical pte&n; *   4    user&n; *   5    write&n; *   6    execute&n; *   7    dirty&n; *  8-11  unused&n; *  12-31 virtual page address&n; *&n; * These are stored at the pte pointer; the physical PTE is at -1024bytes&n; */
DECL|macro|L_PTE_PRESENT
mdefine_line|#define L_PTE_PRESENT&t;&t;(1 &lt;&lt; 0)
DECL|macro|L_PTE_YOUNG
mdefine_line|#define L_PTE_YOUNG&t;&t;(1 &lt;&lt; 1)
DECL|macro|L_PTE_BUFFERABLE
mdefine_line|#define L_PTE_BUFFERABLE&t;(1 &lt;&lt; 2)
DECL|macro|L_PTE_CACHEABLE
mdefine_line|#define L_PTE_CACHEABLE&t;&t;(1 &lt;&lt; 3)
DECL|macro|L_PTE_USER
mdefine_line|#define L_PTE_USER&t;&t;(1 &lt;&lt; 4)
DECL|macro|L_PTE_WRITE
mdefine_line|#define L_PTE_WRITE&t;&t;(1 &lt;&lt; 5)
DECL|macro|L_PTE_EXEC
mdefine_line|#define L_PTE_EXEC&t;&t;(1 &lt;&lt; 6)
DECL|macro|L_PTE_DIRTY
mdefine_line|#define L_PTE_DIRTY&t;&t;(1 &lt;&lt; 7)
multiline_comment|/*&n; * The following macros handle the cache and bufferable bits...&n; */
DECL|macro|_L_PTE_DEFAULT
mdefine_line|#define _L_PTE_DEFAULT&t;L_PTE_PRESENT | L_PTE_YOUNG
DECL|macro|_L_PTE_READ
mdefine_line|#define _L_PTE_READ&t;L_PTE_USER | L_PTE_CACHEABLE | L_PTE_BUFFERABLE
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE       __pgprot(_L_PTE_DEFAULT)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_L_PTE_DEFAULT | _L_PTE_READ)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_L_PTE_DEFAULT | _L_PTE_READ | L_PTE_WRITE)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_L_PTE_DEFAULT | _L_PTE_READ)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL     __pgprot(_L_PTE_DEFAULT | L_PTE_CACHEABLE | L_PTE_BUFFERABLE | L_PTE_DIRTY | L_PTE_WRITE)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | L_PTE_DIRTY | L_PTE_YOUNG)
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;&t;(pte_val(pte) &amp; L_PTE_PRESENT)
DECL|macro|pte_read
mdefine_line|#define pte_read(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_USER)
DECL|macro|pte_write
mdefine_line|#define pte_write(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_WRITE)
DECL|macro|pte_exec
mdefine_line|#define pte_exec(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_EXEC)
DECL|macro|pte_dirty
mdefine_line|#define pte_dirty(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_DIRTY)
DECL|macro|pte_young
mdefine_line|#define pte_young(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_YOUNG)
DECL|macro|PTE_BIT_FUNC
mdefine_line|#define PTE_BIT_FUNC(fn,op)&t;&t;&t;&bslash;&n;extern inline pte_t pte_##fn(pte_t pte) { pte_val(pte) op; return pte; }
multiline_comment|/*PTE_BIT_FUNC(rdprotect, &amp;= ~L_PTE_USER);*/
multiline_comment|/*PTE_BIT_FUNC(mkread,    |= L_PTE_USER);*/
id|PTE_BIT_FUNC
c_func
(paren
id|wrprotect
comma
op_and_assign
op_complement
id|L_PTE_WRITE
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkwrite
comma
op_or_assign
id|L_PTE_WRITE
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|exprotect
comma
op_and_assign
op_complement
id|L_PTE_EXEC
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkexec
comma
op_or_assign
id|L_PTE_EXEC
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkclean
comma
op_and_assign
op_complement
id|L_PTE_DIRTY
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkdirty
comma
op_or_assign
id|L_PTE_DIRTY
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkold
comma
op_and_assign
op_complement
id|L_PTE_YOUNG
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkyoung
comma
op_or_assign
id|L_PTE_YOUNG
)paren
suffix:semicolon
multiline_comment|/*&n; * Mark the prot value as uncacheable and unbufferable.&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached(prot)&t;__pgprot(pgprot_val(prot) &amp; ~(L_PTE_CACHEABLE | L_PTE_BUFFERABLE))
macro_line|#endif /* __ASM_PROC_PGTABLE_H */
eof
