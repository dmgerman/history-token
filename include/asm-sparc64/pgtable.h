multiline_comment|/* $Id: pgtable.h,v 1.135 2000/11/08 04:49:24 davem Exp $&n; * pgtable.h: SpitFire page table operations.&n; *&n; * Copyright 1996,1997 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef _SPARC64_PGTABLE_H
DECL|macro|_SPARC64_PGTABLE_H
mdefine_line|#define _SPARC64_PGTABLE_H
multiline_comment|/* This file contains the functions and defines necessary to modify and use&n; * the SpitFire page tables.&n; */
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PG_dcache_dirty
mdefine_line|#define PG_dcache_dirty&t;&t;PG_arch_1
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
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
mdefine_line|#define PGDIR_SHIFT&t;(PAGE_SHIFT + (PAGE_SHIFT-3) + (PAGE_SHIFT-2))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/* Entries per page directory level. */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;&t;(1UL &lt;&lt; (PAGE_SHIFT-3))
multiline_comment|/* We the first one in this file, what we export to the kernel&n; * is different so we can optimize correctly for 32-bit tasks.&n; */
DECL|macro|REAL_PTRS_PER_PMD
mdefine_line|#define REAL_PTRS_PER_PMD&t;(1UL &lt;&lt; (PAGE_SHIFT-2))
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;&t;((const int)((current-&gt;thread.flags &amp; SPARC_FLAG_32BIT) ? &bslash;&n;&t;&t;&t;&t; (REAL_PTRS_PER_PMD &gt;&gt; 2) : (REAL_PTRS_PER_PMD)))
multiline_comment|/* We cannot use the top 16G because VPTE table lives there. */
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;&t;((1UL &lt;&lt; (PAGE_SHIFT-3))-1)
multiline_comment|/* Kernel has a separate 44bit address space. */
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;((const int)((current-&gt;thread.flags &amp; SPARC_FLAG_32BIT) ? &bslash;&n;&t;&t;&t;&t; (1) : (PTRS_PER_PGD)))
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|PTE_TABLE_SIZE
mdefine_line|#define PTE_TABLE_SIZE&t;0x2000&t;/* 1024 entries 8 bytes each */
DECL|macro|PMD_TABLE_SIZE
mdefine_line|#define PMD_TABLE_SIZE&t;0x2000&t;/* 2048 entries 4 bytes each */
DECL|macro|PGD_TABLE_SIZE
mdefine_line|#define PGD_TABLE_SIZE&t;0x1000&t;/* 1024 entries 4 bytes each */
multiline_comment|/* NOTE: TLB miss handlers depend heavily upon where this is. */
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;0x0000000140000000UL
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x)&t;((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;&t;0x0000000200000000UL
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e)&t;__builtin_trap()
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e)&t;__builtin_trap()
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e)&t;__builtin_trap()
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* SpitFire TTE bits. */
DECL|macro|_PAGE_VALID
mdefine_line|#define _PAGE_VALID&t;0x8000000000000000&t;/* Valid TTE                          */
DECL|macro|_PAGE_R
mdefine_line|#define _PAGE_R&t;&t;0x8000000000000000&t;/* Used to keep ref bit up to date    */
DECL|macro|_PAGE_SZ4MB
mdefine_line|#define _PAGE_SZ4MB&t;0x6000000000000000&t;/* 4MB Page                           */
DECL|macro|_PAGE_SZ512K
mdefine_line|#define _PAGE_SZ512K&t;0x4000000000000000&t;/* 512K Page                          */
DECL|macro|_PAGE_SZ64K
mdefine_line|#define _PAGE_SZ64K&t;0x2000000000000000&t;/* 64K Page                           */
DECL|macro|_PAGE_SZ8K
mdefine_line|#define _PAGE_SZ8K&t;0x0000000000000000&t;/* 8K Page                            */
DECL|macro|_PAGE_NFO
mdefine_line|#define _PAGE_NFO&t;0x1000000000000000&t;/* No Fault Only                      */
DECL|macro|_PAGE_IE
mdefine_line|#define _PAGE_IE&t;0x0800000000000000&t;/* Invert Endianness                  */
DECL|macro|_PAGE_SOFT2
mdefine_line|#define _PAGE_SOFT2&t;0x07FC000000000000&t;/* Second set of software bits        */
DECL|macro|_PAGE_DIAG
mdefine_line|#define _PAGE_DIAG&t;0x0003FE0000000000&t;/* Diagnostic TTE bits                */
DECL|macro|_PAGE_PADDR
mdefine_line|#define _PAGE_PADDR&t;0x000001FFFFFFE000&t;/* Physical Address bits [40:13]      */
DECL|macro|_PAGE_SOFT
mdefine_line|#define _PAGE_SOFT&t;0x0000000000001F80&t;/* First set of software bits         */
DECL|macro|_PAGE_L
mdefine_line|#define _PAGE_L&t;&t;0x0000000000000040&t;/* Locked TTE                         */
DECL|macro|_PAGE_CP
mdefine_line|#define _PAGE_CP&t;0x0000000000000020&t;/* Cacheable in Physical Cache        */
DECL|macro|_PAGE_CV
mdefine_line|#define _PAGE_CV&t;0x0000000000000010&t;/* Cacheable in Virtual Cache         */
DECL|macro|_PAGE_E
mdefine_line|#define _PAGE_E&t;&t;0x0000000000000008&t;/* side-Effect                        */
DECL|macro|_PAGE_P
mdefine_line|#define _PAGE_P&t;&t;0x0000000000000004&t;/* Privileged Page                    */
DECL|macro|_PAGE_W
mdefine_line|#define _PAGE_W&t;&t;0x0000000000000002&t;/* Writable                           */
DECL|macro|_PAGE_G
mdefine_line|#define _PAGE_G&t;&t;0x0000000000000001&t;/* Global                             */
multiline_comment|/* Here are the SpitFire software bits we use in the TTE&squot;s. */
DECL|macro|_PAGE_MODIFIED
mdefine_line|#define _PAGE_MODIFIED&t;0x0000000000000800&t;/* Modified Page (ie. dirty)          */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x0000000000000400&t;/* Accessed Page (ie. referenced)     */
DECL|macro|_PAGE_READ
mdefine_line|#define _PAGE_READ&t;0x0000000000000200&t;/* Readable SW Bit                    */
DECL|macro|_PAGE_WRITE
mdefine_line|#define _PAGE_WRITE&t;0x0000000000000100&t;/* Writable SW Bit                    */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x0000000000000080&t;/* Present Page (ie. not swapped out) */
DECL|macro|_PAGE_CACHE
mdefine_line|#define _PAGE_CACHE&t;(_PAGE_CP | _PAGE_CV)
DECL|macro|__DIRTY_BITS
mdefine_line|#define __DIRTY_BITS&t;(_PAGE_MODIFIED | _PAGE_WRITE | _PAGE_W)
DECL|macro|__ACCESS_BITS
mdefine_line|#define __ACCESS_BITS&t;(_PAGE_ACCESSED | _PAGE_READ | _PAGE_R)
DECL|macro|__PRIV_BITS
mdefine_line|#define __PRIV_BITS&t;_PAGE_P
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot (_PAGE_PRESENT | _PAGE_ACCESSED)
multiline_comment|/* Don&squot;t set the TTE _PAGE_W bit here, else the dirty bit never gets set. */
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot (_PAGE_PRESENT | _PAGE_VALID | _PAGE_CACHE | &bslash;&n;&t;&t;&t;&t;  __ACCESS_BITS | _PAGE_WRITE)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot (_PAGE_PRESENT | _PAGE_VALID | _PAGE_CACHE | &bslash;&n;&t;&t;&t;&t;  __ACCESS_BITS)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot (_PAGE_PRESENT | _PAGE_VALID | _PAGE_CACHE | &bslash;&n;&t;&t;&t;&t;  __ACCESS_BITS)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot (_PAGE_PRESENT | _PAGE_VALID | _PAGE_CACHE | &bslash;&n;&t;&t;&t;&t;  __PRIV_BITS | __ACCESS_BITS | __DIRTY_BITS)
DECL|macro|PAGE_INVALID
mdefine_line|#define PAGE_INVALID&t;__pgprot (0)
DECL|macro|_PFN_MASK
mdefine_line|#define _PFN_MASK&t;_PAGE_PADDR
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(_PFN_MASK | _PAGE_MODIFIED | _PAGE_ACCESSED | _PAGE_PRESENT)
DECL|macro|pg_iobits
mdefine_line|#define pg_iobits (_PAGE_VALID | _PAGE_PRESENT | __DIRTY_BITS | __ACCESS_BITS | _PAGE_E)
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
macro_line|#ifndef __ASSEMBLY__
r_extern
id|pte_t
id|__bad_page
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE&t;__bad_page()
r_extern
r_int
r_int
id|phys_base
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;(mem_map)
multiline_comment|/* Warning: These take pointers to page structs now... */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;&t;&bslash;&n;&t;__pte((((page - mem_map) &lt;&lt; PAGE_SHIFT)+phys_base) | pgprot_val(pgprot))
DECL|macro|page_pte_prot
mdefine_line|#define page_pte_prot(page, prot)&t;mk_pte(page, prot)
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;&t;&t;page_pte_prot(page, __pgprot(0))
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage, pgprot)&t;(__pte((physpage) | pgprot_val(pgprot)))
DECL|function|pte_modify
r_extern
r_inline
id|pte_t
id|pte_modify
c_func
(paren
id|pte_t
id|orig_pte
comma
id|pgprot_t
id|new_prot
)paren
(brace
id|pte_t
id|__pte
suffix:semicolon
id|pte_val
c_func
(paren
id|__pte
)paren
op_assign
(paren
id|pte_val
c_func
(paren
id|orig_pte
)paren
op_amp
id|_PAGE_CHG_MASK
)paren
op_or
id|pgprot_val
c_func
(paren
id|new_prot
)paren
suffix:semicolon
r_return
id|__pte
suffix:semicolon
)brace
DECL|macro|pmd_set
mdefine_line|#define pmd_set(pmdp, ptep)&t;&bslash;&n;&t;(pmd_val(*(pmdp)) = (__pa((unsigned long) (ptep)) &gt;&gt; 11UL))
DECL|macro|pgd_set
mdefine_line|#define pgd_set(pgdp, pmdp)&t;&bslash;&n;&t;(pgd_val(*(pgdp)) = (__pa((unsigned long) (pmdp)) &gt;&gt; 11UL))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;&t;((unsigned long) __va((pmd_val(pmd)&lt;&lt;11UL)))
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd)&t;&t;&t;((unsigned long) __va((pgd_val(pgd)&lt;&lt;11UL)))
DECL|macro|pte_none
mdefine_line|#define pte_none(pte) &t;&t;&t;(!pte_val(pte))
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;&t;(pte_val(pte) &amp; _PAGE_PRESENT)
DECL|macro|pte_clear
mdefine_line|#define pte_clear(pte)&t;&t;&t;(pte_val(*(pte)) = 0UL)
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;&t;(0)
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd)&t;&t;(pmd_val(pmd) != 0UL)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmdp)&t;&t;&t;(pmd_val(*(pmdp)) = 0UL)
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;&t;(!pgd_val(pgd))
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;&t;(0)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;&t;(pgd_val(pgd) != 0UL)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)&t;&t;&t;(pgd_val(*(pgdp)) = 0UL)
multiline_comment|/* The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|macro|pte_read
mdefine_line|#define pte_read(pte)&t;&t;(pte_val(pte) &amp; _PAGE_READ)
DECL|macro|pte_exec
mdefine_line|#define pte_exec(pte)&t;&t;pte_read(pte)
DECL|macro|pte_write
mdefine_line|#define pte_write(pte)&t;&t;(pte_val(pte) &amp; _PAGE_WRITE)
DECL|macro|pte_dirty
mdefine_line|#define pte_dirty(pte)&t;&t;(pte_val(pte) &amp; _PAGE_MODIFIED)
DECL|macro|pte_young
mdefine_line|#define pte_young(pte)&t;&t;(pte_val(pte) &amp; _PAGE_ACCESSED)
DECL|macro|pte_wrprotect
mdefine_line|#define pte_wrprotect(pte)&t;(__pte(pte_val(pte) &amp; ~(_PAGE_WRITE|_PAGE_W)))
DECL|macro|pte_rdprotect
mdefine_line|#define pte_rdprotect(pte)&t;(__pte(((pte_val(pte)&lt;&lt;1UL)&gt;&gt;1UL) &amp; ~_PAGE_READ))
DECL|macro|pte_mkclean
mdefine_line|#define pte_mkclean(pte)&t;(__pte(pte_val(pte) &amp; ~(_PAGE_MODIFIED|_PAGE_W)))
DECL|macro|pte_mkold
mdefine_line|#define pte_mkold(pte)&t;&t;(__pte(((pte_val(pte)&lt;&lt;1UL)&gt;&gt;1UL) &amp; ~_PAGE_ACCESSED))
multiline_comment|/* Permanent address of a page. */
DECL|macro|__page_address
mdefine_line|#define __page_address(page)&t;((page)-&gt;virtual)
DECL|macro|page_address
mdefine_line|#define page_address(page)&t;({ __page_address(page); })
DECL|macro|pte_page
mdefine_line|#define pte_page(x) (mem_map+(((pte_val(x)&amp;_PAGE_PADDR)-phys_base)&gt;&gt;PAGE_SHIFT))
multiline_comment|/* Be very careful when you change these three, they are delicate. */
DECL|macro|pte_mkyoung
mdefine_line|#define pte_mkyoung(pte)&t;(__pte(pte_val(pte) | _PAGE_ACCESSED | _PAGE_R))
DECL|macro|pte_mkwrite
mdefine_line|#define pte_mkwrite(pte)&t;(__pte(pte_val(pte) | _PAGE_WRITE))
DECL|macro|pte_mkdirty
mdefine_line|#define pte_mkdirty(pte)&t;(__pte(pte_val(pte) | _PAGE_MODIFIED | _PAGE_W))
multiline_comment|/* to find an entry in a page-table-directory. */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address)&t;(((address) &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD))
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address)&t;((mm)-&gt;pgd + pgd_index(address))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir, address)&t;((pmd_t *) pgd_page(*(dir)) + &bslash;&n;&t;&t;&t;&t;&t;((address &gt;&gt; PMD_SHIFT) &amp; (REAL_PTRS_PER_PMD-1)))
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|pte_offset
mdefine_line|#define pte_offset(dir, address)&t;((pte_t *) pmd_page(*(dir)) + &bslash;&n;&t;&t;&t;&t;&t;((address &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1)))
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* These do nothing with the way I have things setup. */
DECL|macro|mmu_lockarea
mdefine_line|#define mmu_lockarea(vaddr, len)&t;&t;(vaddr)
DECL|macro|mmu_unlockarea
mdefine_line|#define mmu_unlockarea(vaddr, len)&t;&t;do { } while(0)
r_extern
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
id|pte_t
)paren
suffix:semicolon
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma, pg)&t;do { } while(0)
multiline_comment|/* Make a non-present pseudo-TTE. */
DECL|function|mk_pte_io
r_extern
r_inline
id|pte_t
id|mk_pte_io
c_func
(paren
r_int
r_int
id|page
comma
id|pgprot_t
id|prot
comma
r_int
id|space
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
(paren
id|page
)paren
op_or
id|pgprot_val
c_func
(paren
id|prot
)paren
op_or
id|_PAGE_E
)paren
op_amp
op_complement
(paren
r_int
r_int
)paren
id|_PAGE_CACHE
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|space
)paren
op_lshift
l_int|32
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/* Encode and de-code a swap entry */
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry)&t;&t;(((entry).val &gt;&gt; PAGE_SHIFT) &amp; 0xff)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry)&t;((entry).val &gt;&gt; (PAGE_SHIFT + 8))
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type, offset)&t;&bslash;&n;&t;( (swp_entry_t) &bslash;&n;&t;  { &bslash;&n;&t;&t;((type &lt;&lt; PAGE_SHIFT) | (offset &lt;&lt; (PAGE_SHIFT + 8))) &bslash;&n;&t;  } )
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
r_extern
id|__inline__
r_int
r_int
DECL|function|sun4u_get_pte
id|sun4u_get_pte
(paren
r_int
r_int
id|addr
)paren
(brace
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|PAGE_OFFSET
)paren
r_return
id|addr
op_amp
id|_PAGE_PADDR
suffix:semicolon
id|pgdp
op_assign
id|pgd_offset_k
(paren
id|addr
)paren
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
(paren
id|pgdp
comma
id|addr
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset
(paren
id|pmdp
comma
id|addr
)paren
suffix:semicolon
r_return
id|pte_val
(paren
op_star
id|ptep
)paren
op_amp
id|_PAGE_PADDR
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
r_int
DECL|function|__get_phys
id|__get_phys
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|sun4u_get_pte
(paren
id|addr
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|__get_iospace
id|__get_iospace
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
(paren
id|sun4u_get_pte
(paren
id|addr
)paren
op_amp
l_int|0xf0000000
)paren
op_rshift
l_int|28
)paren
suffix:semicolon
)brace
r_extern
r_int
r_int
op_star
id|sparc64_valid_addr_bitmap
suffix:semicolon
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;&bslash;&n;&t;(test_bit(__pa((unsigned long)(addr))&gt;&gt;22, sparc64_valid_addr_bitmap))
r_extern
r_int
id|io_remap_page_range
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
comma
r_int
id|space
)paren
suffix:semicolon
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* We provide our own get_unmapped_area to cope with VA holes for userland */
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
macro_line|#endif /* !(_SPARC64_PGTABLE_H) */
eof
