macro_line|#ifndef _ASM_IA64_PAGE_H
DECL|macro|_ASM_IA64_PAGE_H
mdefine_line|#define _ASM_IA64_PAGE_H
multiline_comment|/*&n; * Pagetable related stuff.&n; *&n; * Copyright (C) 1998, 1999, 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/intrinsics.h&gt;
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; * PAGE_SHIFT determines the actual kernel page size.&n; */
macro_line|#if defined(CONFIG_IA64_PAGE_SIZE_4KB)
DECL|macro|PAGE_SHIFT
macro_line|# define PAGE_SHIFT&t;12
macro_line|#elif defined(CONFIG_IA64_PAGE_SIZE_8KB)
DECL|macro|PAGE_SHIFT
macro_line|# define PAGE_SHIFT&t;13
macro_line|#elif defined(CONFIG_IA64_PAGE_SIZE_16KB)
DECL|macro|PAGE_SHIFT
macro_line|# define PAGE_SHIFT&t;14
macro_line|#elif defined(CONFIG_IA64_PAGE_SIZE_64KB)
DECL|macro|PAGE_SHIFT
macro_line|# define PAGE_SHIFT&t;16
macro_line|#else
macro_line|# error Unsupported page size!
macro_line|#endif
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;&t;(__IA64_UL_CONST(1) &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;&t;(~(PAGE_SIZE - 1))
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr) + PAGE_SIZE - 1) &amp; PAGE_MASK)
DECL|macro|PERCPU_PAGE_SHIFT
mdefine_line|#define PERCPU_PAGE_SHIFT&t;16&t;/* log2() of max. size of per-CPU area */
DECL|macro|PERCPU_PAGE_SIZE
mdefine_line|#define PERCPU_PAGE_SIZE&t;(__IA64_UL_CONST(1) &lt;&lt; PERCPU_PAGE_SHIFT)
DECL|macro|RGN_MAP_LIMIT
mdefine_line|#define RGN_MAP_LIMIT&t;((1UL &lt;&lt; (4*PAGE_SHIFT - 12)) - PAGE_SIZE)&t;/* per region addr limit */
macro_line|#ifdef CONFIG_HUGETLB_PAGE
DECL|macro|REGION_HPAGE
macro_line|# define REGION_HPAGE&t;&t;(4UL)&t;/* note: this is hardcoded in reload_context()!*/
DECL|macro|REGION_SHIFT
macro_line|# define REGION_SHIFT&t;&t;61
DECL|macro|HPAGE_REGION_BASE
macro_line|# define HPAGE_REGION_BASE&t;(REGION_HPAGE &lt;&lt; REGION_SHIFT)
DECL|macro|HPAGE_SHIFT
macro_line|# define HPAGE_SHIFT&t;&t;hpage_shift
DECL|macro|HPAGE_SHIFT_DEFAULT
macro_line|# define HPAGE_SHIFT_DEFAULT&t;28&t;/* check ia64 SDM for architecture supported size */
DECL|macro|HPAGE_SIZE
macro_line|# define HPAGE_SIZE&t;&t;(__IA64_UL_CONST(1) &lt;&lt; HPAGE_SHIFT)
DECL|macro|HPAGE_MASK
macro_line|# define HPAGE_MASK&t;&t;(~(HPAGE_SIZE - 1))
DECL|macro|HAVE_ARCH_HUGETLB_UNMAPPED_AREA
macro_line|# define HAVE_ARCH_HUGETLB_UNMAPPED_AREA
DECL|macro|ARCH_HAS_HUGEPAGE_ONLY_RANGE
macro_line|# define ARCH_HAS_HUGEPAGE_ONLY_RANGE
macro_line|#endif /* CONFIG_HUGETLB_PAGE */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|__pa
macro_line|# define __pa(x)&t;&t;((x) - PAGE_OFFSET)
DECL|macro|__va
macro_line|# define __va(x)&t;&t;((x) + PAGE_OFFSET)
macro_line|#else /* !__ASSEMBLY */
macro_line|# ifdef __KERNEL__
DECL|macro|STRICT_MM_TYPECHECKS
macro_line|#  define STRICT_MM_TYPECHECKS
r_extern
r_void
id|clear_page
(paren
r_void
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
id|copy_page
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
)paren
suffix:semicolon
multiline_comment|/*&n; * clear_user_page() and copy_user_page() can&squot;t be inline functions because&n; * flush_dcache_page() can&squot;t be defined until later...&n; */
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(addr, vaddr, page)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;clear_page(addr);&t;&t;&t;&bslash;&n;&t;flush_dcache_page(page);&t;&t;&bslash;&n;} while (0)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr, page)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;copy_page((to), (from));&t;&t;&bslash;&n;&t;flush_dcache_page(page);&t;&t;&bslash;&n;} while (0)
DECL|macro|alloc_zeroed_user_highpage
mdefine_line|#define alloc_zeroed_user_highpage(vma, vaddr) &bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct page *page = alloc_page_vma(GFP_HIGHUSER | __GFP_ZERO, vma, vaddr); &bslash;&n;&t;if (page)&t;&t;&t;&t;&bslash;&n; &t;&t;flush_dcache_page(page);&t;&bslash;&n;&t;page;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE
mdefine_line|#define __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;pfn_valid(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
macro_line|#ifdef CONFIG_VIRTUAL_MEM_MAP
r_extern
r_int
id|ia64_pfn_valid
(paren
r_int
r_int
id|pfn
)paren
suffix:semicolon
macro_line|#else
DECL|macro|ia64_pfn_valid
macro_line|# define ia64_pfn_valid(pfn) 1
macro_line|#endif
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|pfn_valid
macro_line|# define pfn_valid(pfn)&t;&t;(((pfn) &lt; max_mapnr) &amp;&amp; ia64_pfn_valid(pfn))
DECL|macro|page_to_pfn
macro_line|# define page_to_pfn(page)&t;((unsigned long) (page - mem_map))
DECL|macro|pfn_to_page
macro_line|# define pfn_to_page(pfn)&t;(mem_map + (pfn))
macro_line|#else
r_extern
r_struct
id|page
op_star
id|vmem_map
suffix:semicolon
r_extern
r_int
r_int
id|max_low_pfn
suffix:semicolon
DECL|macro|pfn_valid
macro_line|# define pfn_valid(pfn)&t;&t;(((pfn) &lt; max_low_pfn) &amp;&amp; ia64_pfn_valid(pfn))
DECL|macro|page_to_pfn
macro_line|# define page_to_pfn(page)&t;((unsigned long) (page - vmem_map))
DECL|macro|pfn_to_page
macro_line|# define pfn_to_page(pfn)&t;(vmem_map + (pfn))
macro_line|#endif
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;(page_to_pfn(page) &lt;&lt; PAGE_SHIFT)
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;pfn_to_page(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|union|ia64_va
r_typedef
r_union
id|ia64_va
(brace
r_struct
(brace
DECL|member|off
r_int
r_int
id|off
suffix:colon
l_int|61
suffix:semicolon
multiline_comment|/* intra-region offset */
DECL|member|reg
r_int
r_int
id|reg
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* region number */
DECL|member|f
)brace
id|f
suffix:semicolon
DECL|member|l
r_int
r_int
id|l
suffix:semicolon
DECL|member|p
r_void
op_star
id|p
suffix:semicolon
DECL|typedef|ia64_va
)brace
id|ia64_va
suffix:semicolon
multiline_comment|/*&n; * Note: These macros depend on the fact that PAGE_OFFSET has all&n; * region bits set to 1 and all other bits set to zero.  They are&n; * expressed in this way to ensure they result in a single &quot;dep&quot;&n; * instruction.&n; */
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;({ia64_va _v; _v.l = (long) (x); _v.f.reg = 0; _v.l;})
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;({ia64_va _v; _v.l = (long) (x); _v.f.reg = -1; _v.p;})
DECL|macro|REGION_NUMBER
mdefine_line|#define REGION_NUMBER(x)&t;({ia64_va _v; _v.l = (long) (x); _v.f.reg;})
DECL|macro|REGION_OFFSET
mdefine_line|#define REGION_OFFSET(x)&t;({ia64_va _v; _v.l = (long) (x); _v.f.off;})
DECL|macro|REGION_SIZE
mdefine_line|#define REGION_SIZE&t;&t;REGION_NUMBER(1)
DECL|macro|REGION_KERNEL
mdefine_line|#define REGION_KERNEL&t;&t;7
macro_line|#ifdef CONFIG_HUGETLB_PAGE
DECL|macro|htlbpage_to_page
macro_line|# define htlbpage_to_page(x)&t;(((unsigned long) REGION_NUMBER(x) &lt;&lt; 61)&t;&t;&t;&bslash;&n;&t;&t;&t;&t; | (REGION_OFFSET(x) &gt;&gt; (HPAGE_SHIFT-PAGE_SHIFT)))
DECL|macro|HUGETLB_PAGE_ORDER
macro_line|# define HUGETLB_PAGE_ORDER&t;(HPAGE_SHIFT - PAGE_SHIFT)
DECL|macro|is_hugepage_only_range
macro_line|# define is_hugepage_only_range(addr, len)&t;&t;&bslash;&n;&t; (REGION_NUMBER(addr) == REGION_HPAGE &amp;&amp;&t;&bslash;&n;&t;  REGION_NUMBER((addr)+(len)) == REGION_HPAGE)
r_extern
r_int
r_int
id|hpage_shift
suffix:semicolon
macro_line|#endif
r_static
id|__inline__
r_int
DECL|function|get_order
id|get_order
(paren
r_int
r_int
id|size
)paren
(brace
r_int
r_float
id|d
op_assign
id|size
op_minus
l_int|1
suffix:semicolon
r_int
id|order
suffix:semicolon
id|order
op_assign
id|ia64_getf_exp
c_func
(paren
id|d
)paren
suffix:semicolon
id|order
op_assign
id|order
op_minus
id|PAGE_SHIFT
op_minus
l_int|0xffff
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|order
OL
l_int|0
)paren
id|order
op_assign
l_int|0
suffix:semicolon
r_return
id|order
suffix:semicolon
)brace
macro_line|# endif /* __KERNEL__ */
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#ifdef STRICT_MM_TYPECHECKS
multiline_comment|/*&n;   * These are used to make use of C type-checking..&n;   */
DECL|member|pte
DECL|typedef|pte_t
r_typedef
r_struct
(brace
r_int
r_int
id|pte
suffix:semicolon
)brace
id|pte_t
suffix:semicolon
DECL|member|pmd
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pmd
suffix:semicolon
)brace
id|pmd_t
suffix:semicolon
DECL|member|pgd
DECL|typedef|pgd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgd
suffix:semicolon
)brace
id|pgd_t
suffix:semicolon
DECL|member|pgprot
DECL|typedef|pgprot_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgprot
suffix:semicolon
)brace
id|pgprot_t
suffix:semicolon
DECL|macro|pte_val
macro_line|# define pte_val(x)&t;((x).pte)
DECL|macro|pmd_val
macro_line|# define pmd_val(x)&t;((x).pmd)
DECL|macro|pgd_val
macro_line|# define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
macro_line|# define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
macro_line|# define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__pgprot
macro_line|# define __pgprot(x)&t;((pgprot_t) { (x) } )
macro_line|#else /* !STRICT_MM_TYPECHECKS */
multiline_comment|/*&n;   * .. while these make it easier on the compiler&n;   */
macro_line|# ifndef __ASSEMBLY__
DECL|typedef|pte_t
r_typedef
r_int
r_int
id|pte_t
suffix:semicolon
DECL|typedef|pmd_t
r_typedef
r_int
r_int
id|pmd_t
suffix:semicolon
DECL|typedef|pgd_t
r_typedef
r_int
r_int
id|pgd_t
suffix:semicolon
DECL|typedef|pgprot_t
r_typedef
r_int
r_int
id|pgprot_t
suffix:semicolon
macro_line|# endif
DECL|macro|pte_val
macro_line|# define pte_val(x)&t;(x)
DECL|macro|pmd_val
macro_line|# define pmd_val(x)&t;(x)
DECL|macro|pgd_val
macro_line|# define pgd_val(x)&t;(x)
DECL|macro|pgprot_val
macro_line|# define pgprot_val(x)&t;(x)
DECL|macro|__pte
macro_line|# define __pte(x)&t;(x)
DECL|macro|__pgd
macro_line|# define __pgd(x)&t;(x)
DECL|macro|__pgprot
macro_line|# define __pgprot(x)&t;(x)
macro_line|#endif /* !STRICT_MM_TYPECHECKS */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;&t;__IA64_UL_CONST(0xe000000000000000)
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;&t;(VM_READ | VM_WRITE |&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC |&t;&t;&bslash;&n;&t;&t;&t;&t;&t; (((current-&gt;personality &amp; READ_IMPLIES_EXEC) != 0)&t;&bslash;&n;&t;&t;&t;&t;&t;  ? VM_EXEC : 0))
macro_line|#endif /* _ASM_IA64_PAGE_H */
eof
