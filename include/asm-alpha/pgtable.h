macro_line|#ifndef _ALPHA_PGTABLE_H
DECL|macro|_ALPHA_PGTABLE_H
mdefine_line|#define _ALPHA_PGTABLE_H
multiline_comment|/*&n; * This file contains the functions and defines necessary to modify and use&n; * the Alpha page table tree.&n; *&n; * This hopefully works with any standard Alpha page-size, as defined&n; * in &lt;asm/page.h&gt; (currently 8192).&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/processor.h&gt;&t;/* For TASK_SIZE */
macro_line|#include &lt;asm/machvec.h&gt;
multiline_comment|/* Certain architectures need to do special things when PTEs&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval) ((*(pteptr)) = (pteval))
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;(PAGE_SHIFT + (PAGE_SHIFT-3))
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;(PAGE_SHIFT + 2*(PAGE_SHIFT-3))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * Entries per page directory level:  the Alpha is three-level, with&n; * all levels having a one-page page table.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;(1UL &lt;&lt; (PAGE_SHIFT-3))
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;(1UL &lt;&lt; (PAGE_SHIFT-3))
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;(1UL &lt;&lt; (PAGE_SHIFT-3))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE / PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
multiline_comment|/* Number of pointers that fit on a page:  this will go away. */
DECL|macro|PTRS_PER_PAGE
mdefine_line|#define PTRS_PER_PAGE&t;(1UL &lt;&lt; (PAGE_SHIFT-3))
macro_line|#ifdef CONFIG_ALPHA_LARGE_VMALLOC
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;0xfffffe0000000000
macro_line|#else
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;(-2*PGDIR_SIZE)
macro_line|#endif
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x)&t;((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;&t;(-PGDIR_SIZE)
multiline_comment|/*&n; * OSF/1 PAL-code-imposed page table bits&n; */
DECL|macro|_PAGE_VALID
mdefine_line|#define _PAGE_VALID&t;0x0001
DECL|macro|_PAGE_FOR
mdefine_line|#define _PAGE_FOR&t;0x0002&t;/* used for page protection (fault on read) */
DECL|macro|_PAGE_FOW
mdefine_line|#define _PAGE_FOW&t;0x0004&t;/* used for page protection (fault on write) */
DECL|macro|_PAGE_FOE
mdefine_line|#define _PAGE_FOE&t;0x0008&t;/* used for page protection (fault on exec) */
DECL|macro|_PAGE_ASM
mdefine_line|#define _PAGE_ASM&t;0x0010
DECL|macro|_PAGE_KRE
mdefine_line|#define _PAGE_KRE&t;0x0100&t;/* xxx - see below on the &quot;accessed&quot; bit */
DECL|macro|_PAGE_URE
mdefine_line|#define _PAGE_URE&t;0x0200&t;/* xxx */
DECL|macro|_PAGE_KWE
mdefine_line|#define _PAGE_KWE&t;0x1000&t;/* used to do the dirty bit in software */
DECL|macro|_PAGE_UWE
mdefine_line|#define _PAGE_UWE&t;0x2000&t;/* used to do the dirty bit in software */
multiline_comment|/* .. and these are ours ... */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x20000
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x40000
multiline_comment|/*&n; * NOTE! The &quot;accessed&quot; bit isn&squot;t necessarily exact:  it can be kept exactly&n; * by software (use the KRE/URE/KWE/UWE bits appropriately), but I&squot;ll fake it.&n; * Under Linux/AXP, the &quot;accessed&quot; bit just means &quot;read&quot;, and I&squot;ll just use&n; * the KRE/URE bits to watch for it. That way we don&squot;t need to overload the&n; * KWE/UWE bits with both handling dirty and accessed.&n; *&n; * Note that the kernel uses the accessed bit just to check whether to page&n; * out a page or not, so it doesn&squot;t have to be exact anyway.&n; */
DECL|macro|__DIRTY_BITS
mdefine_line|#define __DIRTY_BITS&t;(_PAGE_DIRTY | _PAGE_KWE | _PAGE_UWE)
DECL|macro|__ACCESS_BITS
mdefine_line|#define __ACCESS_BITS&t;(_PAGE_ACCESSED | _PAGE_KRE | _PAGE_URE)
DECL|macro|_PFN_MASK
mdefine_line|#define _PFN_MASK&t;0xFFFFFFFF00000000
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_VALID | __DIRTY_BITS | __ACCESS_BITS)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(_PFN_MASK | __DIRTY_BITS | __ACCESS_BITS)
multiline_comment|/*&n; * All the normal masks have the &quot;page accessed&quot; bits on, as any time they are used,&n; * the page is accessed. They are cleared only by the page-out routines&n; */
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_VALID | __ACCESS_BITS | _PAGE_FOR | _PAGE_FOW | _PAGE_FOE)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_VALID | __ACCESS_BITS)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_VALID | __ACCESS_BITS | _PAGE_FOW)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_VALID | __ACCESS_BITS | _PAGE_FOW)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_VALID | _PAGE_ASM | _PAGE_KRE | _PAGE_KWE)
DECL|macro|_PAGE_NORMAL
mdefine_line|#define _PAGE_NORMAL(x) __pgprot(_PAGE_VALID | __ACCESS_BITS | (x))
DECL|macro|_PAGE_P
mdefine_line|#define _PAGE_P(x) _PAGE_NORMAL((x) | (((x) &amp; _PAGE_FOW)?0:_PAGE_FOW))
DECL|macro|_PAGE_S
mdefine_line|#define _PAGE_S(x) _PAGE_NORMAL(x)
multiline_comment|/*&n; * The hardware can handle write-only mappings, but as the Alpha&n; * architecture does byte-wide writes with a read-modify-write&n; * sequence, it&squot;s not practical to have write-without-read privs.&n; * Thus the &quot;-w- -&gt; rw-&quot; and &quot;-wx -&gt; rwx&quot; mapping here (and in&n; * arch/alpha/mm/fault.c)&n; */
multiline_comment|/* xwr */
DECL|macro|__P000
mdefine_line|#define __P000&t;_PAGE_P(_PAGE_FOE | _PAGE_FOW | _PAGE_FOR)
DECL|macro|__P001
mdefine_line|#define __P001&t;_PAGE_P(_PAGE_FOE | _PAGE_FOW)
DECL|macro|__P010
mdefine_line|#define __P010&t;_PAGE_P(_PAGE_FOE)
DECL|macro|__P011
mdefine_line|#define __P011&t;_PAGE_P(_PAGE_FOE)
DECL|macro|__P100
mdefine_line|#define __P100&t;_PAGE_P(_PAGE_FOW | _PAGE_FOR)
DECL|macro|__P101
mdefine_line|#define __P101&t;_PAGE_P(_PAGE_FOW)
DECL|macro|__P110
mdefine_line|#define __P110&t;_PAGE_P(0)
DECL|macro|__P111
mdefine_line|#define __P111&t;_PAGE_P(0)
DECL|macro|__S000
mdefine_line|#define __S000&t;_PAGE_S(_PAGE_FOE | _PAGE_FOW | _PAGE_FOR)
DECL|macro|__S001
mdefine_line|#define __S001&t;_PAGE_S(_PAGE_FOE | _PAGE_FOW)
DECL|macro|__S010
mdefine_line|#define __S010&t;_PAGE_S(_PAGE_FOE)
DECL|macro|__S011
mdefine_line|#define __S011&t;_PAGE_S(_PAGE_FOE)
DECL|macro|__S100
mdefine_line|#define __S100&t;_PAGE_S(_PAGE_FOW | _PAGE_FOR)
DECL|macro|__S101
mdefine_line|#define __S101&t;_PAGE_S(_PAGE_FOW)
DECL|macro|__S110
mdefine_line|#define __S110&t;_PAGE_S(0)
DECL|macro|__S111
mdefine_line|#define __S111&t;_PAGE_S(0)
multiline_comment|/*&n; * BAD_PAGETABLE is used when we need a bogus page-table, while&n; * BAD_PAGE is used for a bogus page.&n; *&n; * ZERO_PAGE is a global shared page that is always zero:  used&n; * for zero-mapped memory areas etc..&n; */
r_extern
id|pte_t
id|__bad_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|pmd_t
op_star
id|__bad_pagetable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__zero_page
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE&t;__bad_pagetable()
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE&t;__bad_page()
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;(virt_to_page(ZERO_PGE))
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR&t;&t;&t;(8*sizeof(unsigned long))
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK&t;&t;&t;(~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*)==1&lt;&lt;SIZEOF_PTR_LOG2 */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2&t;&t;&t;3
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address)&t;&t;&bslash;&n;  ((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
multiline_comment|/*&n; * On certain platforms whose physical address space can overlap KSEG,&n; * namely EV6 and above, we must re-twiddle the physaddr to restore the&n; * correct high-order bits.&n; *&n; * This is extremely confusing until you realize that this is actually&n; * just working around a userspace bug.  The X server was intending to&n; * provide the physical address but instead provided the KSEG address.&n; * Or tried to, except it&squot;s not representable.&n; * &n; * On Tsunami there&squot;s nothing meaningful at 0x40000000000, so this is&n; * a safe thing to do.  Come the first core logic that does put something&n; * in this area -- memory or whathaveyou -- then this hack will have&n; * to go away.  So be prepared!&n; */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) &amp;&amp; defined(USE_48_BIT_KSEG)
macro_line|#error &quot;EV6-only feature in a generic kernel&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || &bslash;&n;    (defined(CONFIG_ALPHA_EV6) &amp;&amp; !defined(USE_48_BIT_KSEG))
DECL|macro|PHYS_TWIDDLE
mdefine_line|#define PHYS_TWIDDLE(phys) &bslash;&n;  ((((phys) &amp; 0xc0000000000UL) == 0x40000000000UL) &bslash;&n;  ? ((phys) ^= 0xc0000000000UL) : (phys))
macro_line|#else
DECL|macro|PHYS_TWIDDLE
mdefine_line|#define PHYS_TWIDDLE(phys) (phys)
macro_line|#endif
multiline_comment|/*&n; * Conversion functions:  convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|PAGE_TO_PA
mdefine_line|#define PAGE_TO_PA(page)&t;((page - mem_map) &lt;&lt; PAGE_SHIFT)
macro_line|#else
DECL|macro|PAGE_TO_PA
mdefine_line|#define PAGE_TO_PA(page) &bslash;&n;&t;&t;((((page)-(page)-&gt;zone-&gt;zone_mem_map) &lt;&lt; PAGE_SHIFT) &bslash;&n;&t;&t;+ (page)-&gt;zone-&gt;zone_start_paddr)
macro_line|#endif
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t pte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_val(pte) = ((unsigned long)(page - mem_map) &lt;&lt; 32) |&t;&bslash;&n;&t;&t;       pgprot_val(pgprot);&t;&t;&t;&t;&bslash;&n;&t;pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#else
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long pfn;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pfn = ((unsigned long)((page)-(page)-&gt;zone-&gt;zone_mem_map)) &lt;&lt; 32;&t;&bslash;&n;&t;pfn += (page)-&gt;zone-&gt;zone_start_paddr &lt;&lt; (32-PAGE_SHIFT);&t;&t;&bslash;&n;&t;pte_val(pte) = pfn | pgprot_val(pgprot);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
DECL|function|mk_pte_phys
r_extern
r_inline
id|pte_t
id|mk_pte_phys
c_func
(paren
r_int
r_int
id|physpage
comma
id|pgprot_t
id|pgprot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|PHYS_TWIDDLE
c_func
(paren
id|physpage
)paren
op_lshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
op_or
id|pgprot_val
c_func
(paren
id|pgprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_modify
r_extern
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
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_CHG_MASK
)paren
op_or
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
DECL|function|pmd_set
r_extern
r_inline
r_void
id|pmd_set
c_func
(paren
id|pmd_t
op_star
id|pmdp
comma
id|pte_t
op_star
id|ptep
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmdp
)paren
op_assign
id|_PAGE_TABLE
op_or
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|ptep
)paren
op_minus
id|PAGE_OFFSET
)paren
op_lshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
)brace
DECL|function|pgd_set
r_extern
r_inline
r_void
id|pgd_set
c_func
(paren
id|pgd_t
op_star
id|pgdp
comma
id|pmd_t
op_star
id|pmdp
)paren
(brace
id|pgd_val
c_func
(paren
op_star
id|pgdp
)paren
op_assign
id|_PAGE_TABLE
op_or
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|pmdp
)paren
op_minus
id|PAGE_OFFSET
)paren
op_lshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;(mem_map+(unsigned long)((pte_val(x) &gt;&gt; 32)))
macro_line|#else
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long kvirt;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct page * __xx;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;kvirt = (unsigned long)__va(pte_val(x) &gt;&gt; (32-PAGE_SHIFT));&t;&bslash;&n;&t;__xx = virt_to_page(kvirt);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__xx;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
DECL|function|pmd_page
r_extern
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
r_return
id|PAGE_OFFSET
op_plus
(paren
(paren
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
id|_PFN_MASK
)paren
op_rshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
)brace
DECL|function|pgd_page
r_extern
r_inline
r_int
r_int
id|pgd_page
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
id|PAGE_OFFSET
op_plus
(paren
(paren
id|pgd_val
c_func
(paren
id|pgd
)paren
op_amp
id|_PFN_MASK
)paren
op_rshift
(paren
l_int|32
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
)brace
DECL|function|pte_none
r_extern
r_inline
r_int
id|pte_none
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
id|pte_val
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
DECL|function|pte_present
r_extern
r_inline
r_int
id|pte_present
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_VALID
suffix:semicolon
)brace
DECL|function|pte_clear
r_extern
r_inline
r_void
id|pte_clear
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|pmd_none
r_extern
r_inline
r_int
id|pmd_none
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
op_logical_neg
id|pmd_val
c_func
(paren
id|pmd
)paren
suffix:semicolon
)brace
DECL|function|pmd_bad
r_extern
r_inline
r_int
id|pmd_bad
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
(paren
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
op_complement
id|_PFN_MASK
)paren
op_ne
id|_PAGE_TABLE
suffix:semicolon
)brace
DECL|function|pmd_present
r_extern
r_inline
r_int
id|pmd_present
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
id|_PAGE_VALID
suffix:semicolon
)brace
DECL|function|pmd_clear
r_extern
r_inline
r_void
id|pmd_clear
c_func
(paren
id|pmd_t
op_star
id|pmdp
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmdp
)paren
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_none
r_extern
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
op_logical_neg
id|pgd_val
c_func
(paren
id|pgd
)paren
suffix:semicolon
)brace
DECL|function|pgd_bad
r_extern
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
(paren
id|pgd_val
c_func
(paren
id|pgd
)paren
op_amp
op_complement
id|_PFN_MASK
)paren
op_ne
id|_PAGE_TABLE
suffix:semicolon
)brace
DECL|function|pgd_present
r_extern
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
id|pgd_val
c_func
(paren
id|pgd
)paren
op_amp
id|_PAGE_VALID
suffix:semicolon
)brace
DECL|function|pgd_clear
r_extern
r_inline
r_void
id|pgd_clear
c_func
(paren
id|pgd_t
op_star
id|pgdp
)paren
(brace
id|pgd_val
c_func
(paren
op_star
id|pgdp
)paren
op_assign
l_int|0
suffix:semicolon
)brace
DECL|macro|page_address
mdefine_line|#define page_address(page)&t;((page)-&gt;virtual)
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|function|pte_read
r_extern
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_FOR
)paren
suffix:semicolon
)brace
DECL|function|pte_write
r_extern
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_FOW
)paren
suffix:semicolon
)brace
DECL|function|pte_exec
r_extern
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_FOE
)paren
suffix:semicolon
)brace
DECL|function|pte_dirty
r_extern
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_DIRTY
suffix:semicolon
)brace
DECL|function|pte_young
r_extern
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_ACCESSED
suffix:semicolon
)brace
DECL|function|pte_wrprotect
r_extern
r_inline
id|pte_t
id|pte_wrprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_FOW
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_rdprotect
r_extern
r_inline
id|pte_t
id|pte_rdprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_FOR
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_exprotect
r_extern
r_inline
id|pte_t
id|pte_exprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_FOE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkclean
r_extern
r_inline
id|pte_t
id|pte_mkclean
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
(paren
id|__DIRTY_BITS
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkold
r_extern
r_inline
id|pte_t
id|pte_mkold
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
(paren
id|__ACCESS_BITS
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkwrite
r_extern
r_inline
id|pte_t
id|pte_mkwrite
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_FOW
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkread
r_extern
r_inline
id|pte_t
id|pte_mkread
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_FOR
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkexec
r_extern
r_inline
id|pte_t
id|pte_mkexec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_FOE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkdirty
r_extern
r_inline
id|pte_t
id|pte_mkdirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|__DIRTY_BITS
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkyoung
r_extern
r_inline
id|pte_t
id|pte_mkyoung
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|__ACCESS_BITS
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|PAGE_DIR_OFFSET
mdefine_line|#define PAGE_DIR_OFFSET(tsk,address) pgd_offset((tsk),(address))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* to find an entry in a page-table-directory. */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address)&t;((address &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD - 1))
DECL|macro|__pgd_offset
mdefine_line|#define __pgd_offset(address)&t;pgd_index(address)
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address)&t;((mm)-&gt;pgd+pgd_index(address))
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|function|pmd_offset
r_extern
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
id|pgd_page
c_func
(paren
op_star
id|dir
)paren
op_plus
(paren
(paren
id|address
op_rshift
id|PMD_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PAGE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|function|pte_offset
r_extern
r_inline
id|pte_t
op_star
id|pte_offset
c_func
(paren
id|pmd_t
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
id|pte_t
op_star
)paren
id|pmd_page
c_func
(paren
op_star
id|dir
)paren
op_plus
(paren
(paren
id|address
op_rshift
id|PAGE_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PAGE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/*&n; * The Alpha doesn&squot;t have any external MMU info:  the kernel page&n; * tables contain all the necessary information.&n; */
DECL|function|update_mmu_cache
r_extern
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
)brace
multiline_comment|/*&n; * Non-present pages:  high 24 bits are offset, next 8 bits type,&n; * low 32 bits zero.&n; */
DECL|function|mk_swap_pte
r_extern
r_inline
id|pte_t
id|mk_swap_pte
c_func
(paren
r_int
r_int
id|type
comma
r_int
r_int
id|offset
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|type
op_lshift
l_int|32
)paren
op_or
(paren
id|offset
op_lshift
l_int|40
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(x)&t;&t;&t;(((x).val &gt;&gt; 32) &amp; 0xff)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(x)&t;&t;&t;((x).val &gt;&gt; 40)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type, offset)&t;&t;((swp_entry_t) { pte_val(mk_swap_pte((type),(offset))) })
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|PageSkip
mdefine_line|#define PageSkip(page)&t;&t;(0)
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
macro_line|#endif
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(start, busaddr, size, prot) &bslash;&n;&t;remap_page_range(start, virt_to_phys(__ioremap(busaddr)), size, prot)
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %016lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#endif /* _ALPHA_PGTABLE_H */
eof
