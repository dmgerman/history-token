multiline_comment|/* pgtable.h: FR-V page table mangling&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Derived from:&n; *&t;include/asm-m68knommu/pgtable.h&n; *&t;include/asm-i386/pgtable.h&n; */
macro_line|#ifndef _ASM_PGTABLE_H
DECL|macro|_ASM_PGTABLE_H
mdefine_line|#define _ASM_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mem-layout.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
macro_line|#if defined(CONFIG_HIGHPTE)
DECL|typedef|pte_addr_t
r_typedef
r_int
r_int
id|pte_addr_t
suffix:semicolon
macro_line|#else
DECL|typedef|pte_addr_t
r_typedef
id|pte_t
op_star
id|pte_addr_t
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * MMU-less operation case first&n; */
macro_line|#ifndef CONFIG_MMU
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(1)&t;&t;/* pages are always present on NO_MM */
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(0)
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;(0)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|pmd_offset
mdefine_line|#define&t;pmd_offset(a, b)&t;((void *) 0)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;&t;__pgprot(0)&t;/* these mean nothing to NO_MM */
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;&t;__pgprot(0)&t;/* these mean nothing to NO_MM */
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;&t;__pgprot(0)&t;/* these mean nothing to NO_MM */
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;&t;__pgprot(0)&t;/* these mean nothing to NO_MM */
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;&t;__pgprot(0)&t;/* these mean nothing to NO_MM */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;(0)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;(0)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(typ,off)&t;((swp_entry_t) { ((typ) | ((off) &lt;&lt; 7)) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val })
macro_line|#ifndef __ASSEMBLY__
DECL|function|pte_file
r_static
r_inline
r_int
id|pte_file
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;({ BUG(); NULL; })
DECL|macro|swapper_pg_dir
mdefine_line|#define swapper_pg_dir&t;&t;((pgd_t *) NULL)
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do {} while(0)
macro_line|#else /* !CONFIG_MMU */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * then MMU operation&n; */
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|empty_zero_page
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;virt_to_page(empty_zero_page)
macro_line|#endif
multiline_comment|/*&n; * we use 2-level page tables, folding the PMD (mid-level table) into the PGE (top-level entry)&n; * [see Documentation/fujitsu/frv/mmu-layout.txt]&n; *&n; * 4th-Level Page Directory:&n; *  - Size: 16KB&n; *  - 1 PML4Es per PML4&n; *  - Each PML4E holds 1 PGD and covers 4GB&n; *&n; * Page Directory:&n; *  - Size: 16KB&n; *  - 64 PGEs per PGD&n; *  - Each PGE holds 1 PMD and covers 64MB&n; *&n; * Page Mid-Level Directory&n; *  - 1 PME per PMD&n; *  - Each PME holds 64 STEs, all of which point to separate chunks of the same Page Table&n; *  - All STEs are instantiated at the same time&n; *  - Size: 256B&n; *&n; * Page Table&n; *  - Size: 16KB&n; *  - 4096 PTEs per PT&n; *  - Each Linux PT is subdivided into 64 FR451 PT&squot;s, each of which holds 64 entries&n; *&n; * Pages&n; *  - Size: 4KB&n; *&n; * total PTEs&n; *&t;= 1 PML4E * 64 PGEs * 1 PMEs * 4096 PTEs&n; *&t;= 1 PML4E * 64 PGEs * 64 STEs * 64 PTEs/FR451-PT&n; *&t;= 262144 (or 256 * 1024)&n; */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;&t;26
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;&t;(~(PGDIR_SIZE - 1))
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;&t;64
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;&t;26
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;&t;(~(PMD_SIZE - 1))
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;&t;1
DECL|macro|PME_SIZE
mdefine_line|#define PME_SIZE&t;&t;256
DECL|macro|__frv_PT_SIZE
mdefine_line|#define __frv_PT_SIZE&t;&t;256
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;&t;4096
DECL|macro|USER_PGDS_IN_LAST_PML4
mdefine_line|#define USER_PGDS_IN_LAST_PML4&t;(TASK_SIZE / PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|USER_PGD_PTRS
mdefine_line|#define USER_PGD_PTRS&t;&t;(PAGE_OFFSET &gt;&gt; PGDIR_SHIFT)
DECL|macro|KERNEL_PGD_PTRS
mdefine_line|#define KERNEL_PGD_PTRS&t;&t;(PTRS_PER_PGD - USER_PGD_PTRS)
DECL|macro|TWOLEVEL_PGDIR_SHIFT
mdefine_line|#define TWOLEVEL_PGDIR_SHIFT&t;26
DECL|macro|BOOT_USER_PGD_PTRS
mdefine_line|#define BOOT_USER_PGD_PTRS&t;(__PAGE_OFFSET &gt;&gt; TWOLEVEL_PGDIR_SHIFT)
DECL|macro|BOOT_KERNEL_PGD_PTRS
mdefine_line|#define BOOT_KERNEL_PGD_PTRS&t;(PTRS_PER_PGD - BOOT_USER_PGD_PTRS)
macro_line|#ifndef __ASSEMBLY__
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %08lx.&bslash;n&quot;, __FILE__, __LINE__, (e).pte)
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(pgd_val(e)))
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|function|pgd_none
r_static
r_inline
r_int
id|pgd_none
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_bad
r_static
r_inline
r_int
id|pgd_bad
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_present
r_static
r_inline
r_int
id|pgd_present
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(xp)&t;&t;&t;&t;do { } while (0)
multiline_comment|/*&n; * Certain architectures need to do special things when PTEs&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(pteptr) = (pteval);&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;dcf %M0&quot; :: &quot;U&quot;(*pteptr));&t;&bslash;&n;} while(0)
DECL|macro|set_pte_atomic
mdefine_line|#define set_pte_atomic(pteptr, pteval)&t;&t;set_pte((pteptr), (pteval))
multiline_comment|/*&n; * (pmds are folded into pgds so this doesn&squot;t get actually called,&n; * but the define is needed for a generic inline function.)&n; */
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgdptr, pgdval)&t;&t;&t;(*(pgdptr) = pgdval)
r_extern
r_void
id|__set_pmd
c_func
(paren
id|pmd_t
op_star
id|pmdptr
comma
r_int
r_int
id|__pmd
)paren
suffix:semicolon
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdptr, pmdval)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__set_pmd((pmdptr), (pmdval).ste[0]);&t;&bslash;&n;} while(0)
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd)&t;&t;&t;&t;((unsigned long) __va(pgd_val(pgd) &amp; PAGE_MASK))
DECL|macro|__pmd_index
mdefine_line|#define __pmd_index(address)&t;&t;&t;0
DECL|function|pmd_offset
r_static
r_inline
id|pmd_t
op_star
id|pmd_offset
c_func
(paren
id|pgd_t
op_star
id|dir
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
id|dir
op_plus
id|__pmd_index
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
DECL|macro|pte_same
mdefine_line|#define pte_same(a, b)&t;&t;((a).pte == (b).pte)
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;(mem_map + ((unsigned long)(((x).pte &gt;&gt; PAGE_SHIFT))))
DECL|macro|pte_none
mdefine_line|#define pte_none(x)&t;&t;(!(x).pte)
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)&t;&t;((unsigned long)(((x).pte &gt;&gt; PAGE_SHIFT)))
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot)&t;__pte(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot))
DECL|macro|pfn_pmd
mdefine_line|#define pfn_pmd(pfn, prot)&t;__pmd(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot))
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x)&t;((unsigned long) (x))
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * control flags in AMPR registers and TLB entries&n; */
DECL|macro|_PAGE_BIT_PRESENT
mdefine_line|#define _PAGE_BIT_PRESENT&t;xAMPRx_V_BIT
DECL|macro|_PAGE_BIT_WP
mdefine_line|#define _PAGE_BIT_WP&t;&t;DAMPRx_WP_BIT
DECL|macro|_PAGE_BIT_NOCACHE
mdefine_line|#define _PAGE_BIT_NOCACHE&t;xAMPRx_C_BIT
DECL|macro|_PAGE_BIT_SUPER
mdefine_line|#define _PAGE_BIT_SUPER&t;&t;xAMPRx_S_BIT
DECL|macro|_PAGE_BIT_ACCESSED
mdefine_line|#define _PAGE_BIT_ACCESSED&t;xAMPRx_RESERVED8_BIT
DECL|macro|_PAGE_BIT_DIRTY
mdefine_line|#define _PAGE_BIT_DIRTY&t;&t;xAMPRx_M_BIT
DECL|macro|_PAGE_BIT_NOTGLOBAL
mdefine_line|#define _PAGE_BIT_NOTGLOBAL&t;xAMPRx_NG_BIT
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;&t;xAMPRx_V
DECL|macro|_PAGE_WP
mdefine_line|#define _PAGE_WP&t;&t;DAMPRx_WP
DECL|macro|_PAGE_NOCACHE
mdefine_line|#define _PAGE_NOCACHE&t;&t;xAMPRx_C
DECL|macro|_PAGE_SUPER
mdefine_line|#define _PAGE_SUPER&t;&t;xAMPRx_S
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;&t;xAMPRx_RESERVED8&t;/* accessed if set */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;&t;xAMPRx_M
DECL|macro|_PAGE_NOTGLOBAL
mdefine_line|#define _PAGE_NOTGLOBAL&t;&t;xAMPRx_NG
DECL|macro|_PAGE_RESERVED_MASK
mdefine_line|#define _PAGE_RESERVED_MASK&t;(xAMPRx_RESERVED8 | xAMPRx_RESERVED13)
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;&t;0x002&t;/* set:pagecache unset:swap */
DECL|macro|_PAGE_PROTNONE
mdefine_line|#define _PAGE_PROTNONE&t;&t;0x000&t;/* If not present */
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;&t;(PTE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|__PGPROT_BASE
mdefine_line|#define __PGPROT_BASE &bslash;&n;&t;(_PAGE_PRESENT | xAMPRx_SS_16Kb | xAMPRx_D | _PAGE_NOTGLOBAL | _PAGE_ACCESSED)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PROTNONE | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(__PGPROT_BASE)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(__PGPROT_BASE | _PAGE_WP)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(__PGPROT_BASE | _PAGE_WP)
DECL|macro|__PAGE_KERNEL
mdefine_line|#define __PAGE_KERNEL&t;&t;(__PGPROT_BASE | _PAGE_SUPER | _PAGE_DIRTY)
DECL|macro|__PAGE_KERNEL_NOCACHE
mdefine_line|#define __PAGE_KERNEL_NOCACHE&t;(__PGPROT_BASE | _PAGE_SUPER | _PAGE_DIRTY | _PAGE_NOCACHE)
DECL|macro|__PAGE_KERNEL_RO
mdefine_line|#define __PAGE_KERNEL_RO&t;(__PGPROT_BASE | _PAGE_SUPER | _PAGE_DIRTY | _PAGE_WP)
DECL|macro|MAKE_GLOBAL
mdefine_line|#define MAKE_GLOBAL(x) __pgprot((x) &amp; ~_PAGE_NOTGLOBAL)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;&t;MAKE_GLOBAL(__PAGE_KERNEL)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO&t;&t;MAKE_GLOBAL(__PAGE_KERNEL_RO)
DECL|macro|PAGE_KERNEL_NOCACHE
mdefine_line|#define PAGE_KERNEL_NOCACHE&t;MAKE_GLOBAL(__PAGE_KERNEL_NOCACHE)
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;&t;(_PAGE_PRESENT | xAMPRx_SS_16Kb | xAMPRx_D | _PAGE_ACCESSED)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * The FR451 can do execute protection by virtue of having separate TLB miss handlers for&n; * instruction access and for data access. However, we don&squot;t have enough reserved bits to say&n; * &quot;execute only&quot;, so we don&squot;t bother. If you can read it, you can execute it and vice versa.&n; */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100&t;PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101&t;PAGE_READONLY
DECL|macro|__P110
mdefine_line|#define __P110&t;PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111&t;PAGE_COPY
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100&t;PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101&t;PAGE_READONLY
DECL|macro|__S110
mdefine_line|#define __S110&t;PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111&t;PAGE_SHARED
multiline_comment|/*&n; * Define this to warn about kernel memory accesses that are&n; * done without a &squot;verify_area(VERIFY_WRITE,..)&squot;&n; */
DECL|macro|TEST_VERIFY_AREA
macro_line|#undef TEST_VERIFY_AREA
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;(pte_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pte_clear
mdefine_line|#define pte_clear(xp)&t;do { set_pte(xp, __pte(0)); } while (0)
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!pmd_val(x))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(x)&t;(pmd_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(x)&t;(pmd_val(x) &amp; xAMPRx_SS)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(xp)&t;do { __set_pmd(xp, 0); } while(0)
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd) &bslash;&n;&t;((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;(pfn_to_page(pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
macro_line|#endif
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x) ((x) &gt;&gt; (20-PAGE_SHIFT))
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|function|pte_read
r_static
r_inline
r_int
id|pte_read
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
(paren
(paren
id|pte
)paren
dot
id|pte
op_amp
id|_PAGE_SUPER
)paren
suffix:semicolon
)brace
DECL|function|pte_exec
r_static
r_inline
r_int
id|pte_exec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
(paren
(paren
id|pte
)paren
dot
id|pte
op_amp
id|_PAGE_SUPER
)paren
suffix:semicolon
)brace
DECL|function|pte_dirty
r_static
r_inline
r_int
id|pte_dirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
(paren
id|pte
)paren
dot
id|pte
op_amp
id|_PAGE_DIRTY
suffix:semicolon
)brace
DECL|function|pte_young
r_static
r_inline
r_int
id|pte_young
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
(paren
id|pte
)paren
dot
id|pte
op_amp
id|_PAGE_ACCESSED
suffix:semicolon
)brace
DECL|function|pte_write
r_static
r_inline
r_int
id|pte_write
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
(paren
(paren
id|pte
)paren
dot
id|pte
op_amp
id|_PAGE_WP
)paren
suffix:semicolon
)brace
DECL|function|pte_rdprotect
r_static
r_inline
id|pte_t
id|pte_rdprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte
op_or_assign
id|_PAGE_SUPER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_exprotect
r_static
r_inline
id|pte_t
id|pte_exprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte
op_or_assign
id|_PAGE_SUPER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkclean
r_static
r_inline
id|pte_t
id|pte_mkclean
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte
op_and_assign
op_complement
id|_PAGE_DIRTY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkold
r_static
r_inline
id|pte_t
id|pte_mkold
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte
op_and_assign
op_complement
id|_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_wrprotect
r_static
r_inline
id|pte_t
id|pte_wrprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte
op_or_assign
id|_PAGE_WP
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkread
r_static
r_inline
id|pte_t
id|pte_mkread
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte
op_and_assign
op_complement
id|_PAGE_SUPER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkexec
r_static
r_inline
id|pte_t
id|pte_mkexec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte
op_and_assign
op_complement
id|_PAGE_SUPER
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkdirty
r_static
r_inline
id|pte_t
id|pte_mkdirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte
op_or_assign
id|_PAGE_DIRTY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkyoung
r_static
r_inline
id|pte_t
id|pte_mkyoung
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte
op_or_assign
id|_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkwrite
r_static
r_inline
id|pte_t
id|pte_mkwrite
c_func
(paren
id|pte_t
id|pte
)paren
(brace
(paren
id|pte
)paren
dot
id|pte
op_and_assign
op_complement
id|_PAGE_WP
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|ptep_test_and_clear_dirty
r_static
r_inline
r_int
id|ptep_test_and_clear_dirty
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_int
id|i
op_assign
id|test_and_clear_bit
c_func
(paren
id|_PAGE_BIT_DIRTY
comma
id|ptep
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;dcf %M0&quot;
op_scope_resolution
l_string|&quot;U&quot;
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|ptep_test_and_clear_young
r_static
r_inline
r_int
id|ptep_test_and_clear_young
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_int
id|i
op_assign
id|test_and_clear_bit
c_func
(paren
id|_PAGE_BIT_ACCESSED
comma
id|ptep
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;dcf %M0&quot;
op_scope_resolution
l_string|&quot;U&quot;
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|ptep_get_and_clear
r_static
r_inline
id|pte_t
id|ptep_get_and_clear
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_int
r_int
id|x
op_assign
id|xchg
c_func
(paren
op_amp
id|ptep-&gt;pte
comma
l_int|0
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;dcf %M0&quot;
op_scope_resolution
l_string|&quot;U&quot;
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
r_return
id|__pte
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|ptep_set_wrprotect
r_static
r_inline
r_void
id|ptep_set_wrprotect
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
id|set_bit
c_func
(paren
id|_PAGE_BIT_WP
comma
id|ptep
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;dcf %M0&quot;
op_scope_resolution
l_string|&quot;U&quot;
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
)brace
DECL|function|ptep_mkdirty
r_static
r_inline
r_void
id|ptep_mkdirty
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
id|set_bit
c_func
(paren
id|_PAGE_BIT_DIRTY
comma
id|ptep
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;dcf %M0&quot;
op_scope_resolution
l_string|&quot;U&quot;
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;pfn_pte(page_to_pfn(page), (pgprot))
DECL|macro|mk_pte_huge
mdefine_line|#define mk_pte_huge(entry)&t;((entry).pte_low |= _PAGE_PRESENT | _PAGE_PSE)
multiline_comment|/* This takes a physical page address that is used by the remapping functions */
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage, pgprot)&t;pfn_pte((physpage) &gt;&gt; PAGE_SHIFT, pgprot)
DECL|function|pte_modify
r_static
r_inline
id|pte_t
id|pte_modify
c_func
(paren
id|pte_t
id|pte
comma
id|pgprot_t
id|newprot
)paren
(brace
id|pte.pte
op_and_assign
id|_PAGE_CHG_MASK
suffix:semicolon
id|pte.pte
op_or_assign
id|pgprot_val
c_func
(paren
id|newprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;page_pte_prot(page, __pgprot(0))
multiline_comment|/* to find an entry in a page-table-directory. */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) ((address &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD - 1))
DECL|macro|pgd_index_k
mdefine_line|#define pgd_index_k(addr) pgd_index(addr)
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|__pte_index
mdefine_line|#define __pte_index(address) ((address &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset
mdefine_line|#define pte_offset(dir, address) ((pte_t *) pmd_page(*(dir)) + __pte_index(address))
multiline_comment|/*&n; * the pte page can be thought of an array like this: pte_t[PTRS_PER_PTE]&n; *&n; * this macro returns the index of the entry in the pte page which would&n; * control the given virtual address&n; */
DECL|macro|pte_index
mdefine_line|#define pte_index(address) &bslash;&n;&t;&t;(((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address) &bslash;&n;&t;((pte_t *) pmd_page_kernel(*(dir)) +  pte_index(address))
macro_line|#if defined(CONFIG_HIGHPTE)
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address) &bslash;&n;&t;((pte_t *)kmap_atomic(pmd_page(*(dir)),KM_PTE0) + pte_index(address))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address) &bslash;&n;&t;((pte_t *)kmap_atomic(pmd_page(*(dir)),KM_PTE1) + pte_index(address))
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) kunmap_atomic(pte, KM_PTE0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) kunmap_atomic(pte, KM_PTE1)
macro_line|#else
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address) &bslash;&n;&t;((pte_t *)page_address(pmd_page(*(dir))) + pte_index(address))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address) pte_offset_map(dir, address)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) do { } while (0)
macro_line|#endif
multiline_comment|/*&n; * Handle swap and file entries&n; * - the PTE is encoded in the following format:&n; *&t;bit 0:&t;&t;Must be 0 (!_PAGE_PRESENT)&n; *&t;bit 1:&t;&t;Type: 0 for swap, 1 for file (_PAGE_FILE)&n; *&t;bits 2-7:&t;Swap type&n; *&t;bits 8-31:&t;Swap offset&n; *&t;bits 2-31:&t;File pgoff&n; */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;&t;(((x).val &gt;&gt; 2) &amp; 0x1f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;&t;((x).val &gt;&gt; 8)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset)&t;((swp_entry_t) { ((type) &lt;&lt; 2) | ((offset) &lt;&lt; 8) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { (pte).pte })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
DECL|function|pte_file
r_static
r_inline
r_int
id|pte_file
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte.pte
op_amp
id|_PAGE_FILE
suffix:semicolon
)brace
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;29
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(PTE)&t;((PTE).pte &gt;&gt; 2)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off)&t;__pte((off) &lt;&lt; 2 | _PAGE_FILE)
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|PageSkip
mdefine_line|#define PageSkip(page)&t;&t;(0)
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range&t;remap_page_range
DECL|macro|__HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
mdefine_line|#define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
DECL|macro|__HAVE_ARCH_PTEP_TEST_AND_CLEAR_DIRTY
mdefine_line|#define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_DIRTY
DECL|macro|__HAVE_ARCH_PTEP_GET_AND_CLEAR
mdefine_line|#define __HAVE_ARCH_PTEP_GET_AND_CLEAR
DECL|macro|__HAVE_ARCH_PTEP_SET_WRPROTECT
mdefine_line|#define __HAVE_ARCH_PTEP_SET_WRPROTECT
DECL|macro|__HAVE_ARCH_PTEP_MKDIRTY
mdefine_line|#define __HAVE_ARCH_PTEP_MKDIRTY
DECL|macro|__HAVE_ARCH_PTE_SAME
mdefine_line|#define __HAVE_ARCH_PTE_SAME
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#include &lt;asm-generic/nopml4-pgtable.h&gt;
multiline_comment|/*&n; * preload information about a newly instantiated PTE into the SCR0/SCR1 PGE cache&n; */
DECL|function|update_mmu_cache
r_static
r_inline
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
(brace
r_int
r_int
id|ampr
suffix:semicolon
id|pml4_t
op_star
id|pml4e
op_assign
id|pml4_offset
c_func
(paren
id|current-&gt;mm
comma
id|address
)paren
suffix:semicolon
id|pgd_t
op_star
id|pge
op_assign
id|pml4_pgd_offset
c_func
(paren
id|pml4e
comma
id|address
)paren
suffix:semicolon
id|pmd_t
op_star
id|pme
op_assign
id|pmd_offset
c_func
(paren
id|pge
comma
id|address
)paren
suffix:semicolon
id|ampr
op_assign
id|pme-&gt;ste
(braket
l_int|0
)braket
op_amp
l_int|0xffffff00
suffix:semicolon
id|ampr
op_or_assign
id|xAMPRx_L
op_or
id|xAMPRx_SS_16Kb
op_or
id|xAMPRx_S
op_or
id|xAMPRx_C
op_or
id|xAMPRx_V
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movgs %0,scr0&bslash;n&quot;
l_string|&quot;movgs %0,scr1&bslash;n&quot;
l_string|&quot;movgs %1,dampr4&bslash;n&quot;
l_string|&quot;movgs %1,dampr5&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|address
)paren
comma
l_string|&quot;r&quot;
(paren
id|ampr
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_char
op_star
id|proc_pid_status_frv_cxnr
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_char
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|__init
id|pgtable_cache_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* !CONFIG_MMU */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_PGTABLE_H */
eof
