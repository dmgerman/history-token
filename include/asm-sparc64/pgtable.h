multiline_comment|/* $Id: pgtable.h,v 1.156 2002/02/09 19:49:31 davem Exp $&n; * pgtable.h: SpitFire page table operations.&n; *&n; * Copyright 1996,1997 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef _SPARC64_PGTABLE_H
DECL|macro|_SPARC64_PGTABLE_H
mdefine_line|#define _SPARC64_PGTABLE_H
multiline_comment|/* This file contains the functions and defines necessary to modify and use&n; * the SpitFire page tables.&n; */
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/* The kernel image occupies 0x4000000 to 0x1000000 (4MB --&gt; 16MB).&n; * The page copy blockops use 0x1000000 to 0x18000000 (16MB --&gt; 24MB).&n; * The PROM resides in an area spanning 0xf0000000 to 0x100000000.&n; * The vmalloc area spans 0x140000000 to 0x200000000.&n; * There is a single static kernel PMD which maps from 0x0 to address&n; * 0x400000000.&n; */
DECL|macro|TLBTEMP_BASE
mdefine_line|#define&t;TLBTEMP_BASE&t;&t;0x0000000001000000
DECL|macro|MODULES_VADDR
mdefine_line|#define MODULES_VADDR&t;&t;0x0000000002000000
DECL|macro|MODULES_LEN
mdefine_line|#define MODULES_LEN&t;&t;0x000000007e000000
DECL|macro|MODULES_END
mdefine_line|#define MODULES_END&t;&t;0x0000000080000000
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;0x0000000140000000
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x)&t;((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;&t;0x0000000200000000
DECL|macro|LOW_OBP_ADDRESS
mdefine_line|#define LOW_OBP_ADDRESS&t;&t;0x00000000f0000000
DECL|macro|HI_OBP_ADDRESS
mdefine_line|#define HI_OBP_ADDRESS&t;&t;0x0000000100000000
multiline_comment|/* XXX All of this needs to be rethought so we can take advantage&n; * XXX cheetah&squot;s full 64-bit virtual address space, ie. no more hole&n; * XXX in the middle like on spitfire. -DaveM&n; */
multiline_comment|/*&n; * Given a virtual address, the lowest PAGE_SHIFT bits determine offset&n; * into the page; the next higher PAGE_SHIFT-3 bits determine the pte#&n; * in the proper pagetable (the -3 is from the 8 byte ptes, and each page&n; * table is a single page long). The next higher PMD_BITS determine pmd# &n; * in the proper pmdtable (where we must have PMD_BITS &lt;= (PAGE_SHIFT-2) &n; * since the pmd entries are 4 bytes, and each pmd page is a single page &n; * long). Finally, the higher few bits determine pgde#.&n; */
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;(PAGE_SHIFT + (PAGE_SHIFT-3))
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
DECL|macro|PMD_BITS
mdefine_line|#define PMD_BITS&t;11
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;(PAGE_SHIFT + (PAGE_SHIFT-3) + PMD_BITS)
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval) ((*(pteptr)) = (pteval))
multiline_comment|/* Entries per page directory level. */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;&t;(1UL &lt;&lt; (PAGE_SHIFT-3))
multiline_comment|/* We the first one in this file, what we export to the kernel&n; * is different so we can optimize correctly for 32-bit tasks.&n; */
DECL|macro|REAL_PTRS_PER_PMD
mdefine_line|#define REAL_PTRS_PER_PMD&t;(1UL &lt;&lt; PMD_BITS)
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;&t;((const int)(test_thread_flag(TIF_32BIT) ? &bslash;&n;&t;&t;&t;&t; (1UL &lt;&lt; (32 - (PAGE_SHIFT-3) - PAGE_SHIFT)) : (REAL_PTRS_PER_PMD)))
multiline_comment|/*&n; * We cannot use the top address range because VPTE table lives there. This&n; * formula finds the total legal virtual space in the processor, subtracts the&n; * vpte size, then aligns it to the number of bytes mapped by one pgde, and&n; * thus calculates the number of pgdes needed.&n; */
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;(((1UL &lt;&lt; VA_BITS) - VPTE_SIZE + (1UL &lt;&lt; (PAGE_SHIFT + &bslash;&n;&t;&t;&t;(PAGE_SHIFT-3) + PMD_BITS)) - 1) / (1UL &lt;&lt; (PAGE_SHIFT + &bslash;&n;&t;&t;&t;(PAGE_SHIFT-3) + PMD_BITS)))
multiline_comment|/* Kernel has a separate 44bit address space. */
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;((const int)(test_thread_flag(TIF_32BIT)) ? &bslash;&n;&t;&t;&t;&t; (1) : (PTRS_PER_PGD))
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e)&t;__builtin_trap()
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e)&t;__builtin_trap()
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e)&t;__builtin_trap()
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* Spitfire/Cheetah TTE bits. */
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
DECL|macro|_PAGE_SN
mdefine_line|#define _PAGE_SN&t;0x0000800000000000&t;/* (Cheetah) Snoop                    */
DECL|macro|_PAGE_PADDR_SF
mdefine_line|#define _PAGE_PADDR_SF&t;0x000001FFFFFFE000&t;/* (Spitfire) Phys Address [40:13]    */
DECL|macro|_PAGE_PADDR
mdefine_line|#define _PAGE_PADDR&t;0x000007FFFFFFE000&t;/* (Cheetah) Phys Address [42:13]     */
DECL|macro|_PAGE_SOFT
mdefine_line|#define _PAGE_SOFT&t;0x0000000000001F80&t;/* Software bits                      */
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
macro_line|#if PAGE_SHIFT == 13
DECL|macro|_PAGE_SZBITS
mdefine_line|#define _PAGE_SZBITS&t;_PAGE_SZ8K
macro_line|#elif PAGE_SHIFT == 16
DECL|macro|_PAGE_SZBITS
mdefine_line|#define _PAGE_SZBITS&t;_PAGE_SZ64K
macro_line|#elif PAGE_SHIFT == 19
DECL|macro|_PAGE_SZBITS
mdefine_line|#define _PAGE_SZBITS&t;_PAGE_SZ512K
macro_line|#elif PAGE_SHIFT == 22
DECL|macro|_PAGE_SZBITS
mdefine_line|#define _PAGE_SZBITS&t;_PAGE_SZ4M
macro_line|#else
macro_line|#error Wrong PAGE_SHIFT specified
macro_line|#endif
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
mdefine_line|#define _PAGE_CHG_MASK&t;(_PFN_MASK | _PAGE_MODIFIED | _PAGE_ACCESSED | _PAGE_PRESENT | _PAGE_SZBITS)
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
r_int
r_int
id|phys_base
suffix:semicolon
r_extern
r_int
r_int
id|pfn_base
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|mem_map_zero
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;(mem_map_zero)
multiline_comment|/* PFNs are real physical page numbers.  However, mem_map only begins to record&n; * per-page information starting at pfn_base.  This is to handle systems where&n; * the first physical page in the machine is at some huge physical address, such&n; * as 4GB.   This is common on a partitioned E10000, for example.&n; */
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot)&t;&bslash;&n;&t;__pte(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot) | _PAGE_SZBITS)
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;pfn_pte(page_to_pfn(page), (pgprot))
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)&t;&t;((pte_val(x) &amp; _PAGE_PADDR)&gt;&gt;PAGE_SHIFT)
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;pfn_to_page(pte_pfn(x))
DECL|macro|page_pte_prot
mdefine_line|#define page_pte_prot(page, prot)&t;mk_pte(page, prot)
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;&t;&t;page_pte_prot(page, __pgprot(0))
DECL|function|pte_modify
r_static
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
DECL|macro|__pmd_page
mdefine_line|#define __pmd_page(pmd)&t;&t;&t;((unsigned long) __va((pmd_val(pmd)&lt;&lt;11UL)))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) &t;&t;&t;virt_to_page((void *)__pmd_page(pmd))
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
mdefine_line|#define __page_address(page)&t;page_address(page)
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
DECL|macro|pte_index
mdefine_line|#define pte_index(dir, address)&t;((pte_t *) __pmd_page(*(dir)) + &bslash;&n;&t;&t;&t;&t;&t;((address &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1)))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel&t;&t;pte_index
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map&t;&t;&t;pte_index
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested&t;&t;pte_index
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte)&t;&t;&t;do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte)&t;&t;do { } while (0)
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
r_struct
id|vm_area_struct
suffix:semicolon
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
multiline_comment|/* Make a non-present pseudo-TTE. */
DECL|function|mk_pte_io
r_static
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
DECL|macro|__swp_type
mdefine_line|#define __swp_type(entry)&t;(((entry).val &gt;&gt; PAGE_SHIFT) &amp; 0xffUL)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(entry)&t;((entry).val &gt;&gt; (PAGE_SHIFT + 8UL))
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset)&t;&bslash;&n;&t;( (swp_entry_t) &bslash;&n;&t;  { &bslash;&n;&t;&t;(((long)(type) &lt;&lt; PAGE_SHIFT) | &bslash;&n;                 ((long)(offset) &lt;&lt; (PAGE_SHIFT + 8UL))) &bslash;&n;&t;  } )
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
r_extern
r_int
r_int
id|prom_virt_to_phys
c_func
(paren
r_int
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_static
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
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|LOW_OBP_ADDRESS
)paren
op_logical_and
(paren
id|addr
OL
id|HI_OBP_ADDRESS
)paren
)paren
r_return
id|prom_virt_to_phys
c_func
(paren
id|addr
comma
l_int|0
)paren
suffix:semicolon
id|pgdp
op_assign
id|pgd_offset_k
c_func
(paren
id|addr
)paren
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgdp
comma
id|addr
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmdp
comma
id|addr
)paren
suffix:semicolon
r_return
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
id|_PAGE_PADDR
suffix:semicolon
)brace
r_static
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
r_static
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
r_struct
id|vm_area_struct
op_star
id|vma
comma
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
multiline_comment|/* We provide our own get_unmapped_area to cope with VA holes for userland */
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
multiline_comment|/* We provide a special get_unmapped_area for framebuffer mmaps to try and use&n; * the largest alignment possible such that larget PTEs can be used.&n; */
r_extern
r_int
r_int
id|get_fb_unmapped_area
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|HAVE_ARCH_FB_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_FB_UNMAPPED_AREA
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
r_extern
r_void
id|check_pgt_cache
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|pte_addr_t
r_typedef
id|pte_t
op_star
id|pte_addr_t
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(_SPARC64_PGTABLE_H) */
eof
