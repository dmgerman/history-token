macro_line|#ifndef _ASM_IA64_PGTABLE_H
DECL|macro|_ASM_IA64_PGTABLE_H
mdefine_line|#define _ASM_IA64_PGTABLE_H
multiline_comment|/*&n; * This file contains the functions and defines necessary to modify and use&n; * the IA-64 page table tree.&n; *&n; * This hopefully works with any (fixed) IA-64 page-size, as defined&n; * in &lt;asm/page.h&gt;.&n; *&n; * Copyright (C) 1998-2004 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mman.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|IA64_MAX_PHYS_BITS
mdefine_line|#define IA64_MAX_PHYS_BITS&t;50&t;/* max. number of physical address bits (architected) */
multiline_comment|/*&n; * First, define the various bits in a PTE.  Note that the PTE format&n; * matches the VHPT short format, the firt doubleword of the VHPD long&n; * format, and the first doubleword of the TLB insertion format.&n; */
DECL|macro|_PAGE_P_BIT
mdefine_line|#define _PAGE_P_BIT&t;&t;0
DECL|macro|_PAGE_A_BIT
mdefine_line|#define _PAGE_A_BIT&t;&t;5
DECL|macro|_PAGE_D_BIT
mdefine_line|#define _PAGE_D_BIT&t;&t;6
DECL|macro|_PAGE_P
mdefine_line|#define _PAGE_P&t;&t;&t;(1 &lt;&lt; _PAGE_P_BIT)&t;/* page present bit */
DECL|macro|_PAGE_MA_WB
mdefine_line|#define _PAGE_MA_WB&t;&t;(0x0 &lt;&lt;  2)&t;/* write back memory attribute */
DECL|macro|_PAGE_MA_UC
mdefine_line|#define _PAGE_MA_UC&t;&t;(0x4 &lt;&lt;  2)&t;/* uncacheable memory attribute */
DECL|macro|_PAGE_MA_UCE
mdefine_line|#define _PAGE_MA_UCE&t;&t;(0x5 &lt;&lt;  2)&t;/* UC exported attribute */
DECL|macro|_PAGE_MA_WC
mdefine_line|#define _PAGE_MA_WC&t;&t;(0x6 &lt;&lt;  2)&t;/* write coalescing memory attribute */
DECL|macro|_PAGE_MA_NAT
mdefine_line|#define _PAGE_MA_NAT&t;&t;(0x7 &lt;&lt;  2)&t;/* not-a-thing attribute */
DECL|macro|_PAGE_MA_MASK
mdefine_line|#define _PAGE_MA_MASK&t;&t;(0x7 &lt;&lt;  2)
DECL|macro|_PAGE_PL_0
mdefine_line|#define _PAGE_PL_0&t;&t;(0 &lt;&lt;  7)&t;/* privilege level 0 (kernel) */
DECL|macro|_PAGE_PL_1
mdefine_line|#define _PAGE_PL_1&t;&t;(1 &lt;&lt;  7)&t;/* privilege level 1 (unused) */
DECL|macro|_PAGE_PL_2
mdefine_line|#define _PAGE_PL_2&t;&t;(2 &lt;&lt;  7)&t;/* privilege level 2 (unused) */
DECL|macro|_PAGE_PL_3
mdefine_line|#define _PAGE_PL_3&t;&t;(3 &lt;&lt;  7)&t;/* privilege level 3 (user) */
DECL|macro|_PAGE_PL_MASK
mdefine_line|#define _PAGE_PL_MASK&t;&t;(3 &lt;&lt;  7)
DECL|macro|_PAGE_AR_R
mdefine_line|#define _PAGE_AR_R&t;&t;(0 &lt;&lt;  9)&t;/* read only */
DECL|macro|_PAGE_AR_RX
mdefine_line|#define _PAGE_AR_RX&t;&t;(1 &lt;&lt;  9)&t;/* read &amp; execute */
DECL|macro|_PAGE_AR_RW
mdefine_line|#define _PAGE_AR_RW&t;&t;(2 &lt;&lt;  9)&t;/* read &amp; write */
DECL|macro|_PAGE_AR_RWX
mdefine_line|#define _PAGE_AR_RWX&t;&t;(3 &lt;&lt;  9)&t;/* read, write &amp; execute */
DECL|macro|_PAGE_AR_R_RW
mdefine_line|#define _PAGE_AR_R_RW&t;&t;(4 &lt;&lt;  9)&t;/* read / read &amp; write */
DECL|macro|_PAGE_AR_RX_RWX
mdefine_line|#define _PAGE_AR_RX_RWX&t;&t;(5 &lt;&lt;  9)&t;/* read &amp; exec / read, write &amp; exec */
DECL|macro|_PAGE_AR_RWX_RW
mdefine_line|#define _PAGE_AR_RWX_RW&t;&t;(6 &lt;&lt;  9)&t;/* read, write &amp; exec / read &amp; write */
DECL|macro|_PAGE_AR_X_RX
mdefine_line|#define _PAGE_AR_X_RX&t;&t;(7 &lt;&lt;  9)&t;/* exec &amp; promote / read &amp; exec */
DECL|macro|_PAGE_AR_MASK
mdefine_line|#define _PAGE_AR_MASK&t;&t;(7 &lt;&lt;  9)
DECL|macro|_PAGE_AR_SHIFT
mdefine_line|#define _PAGE_AR_SHIFT&t;&t;9
DECL|macro|_PAGE_A
mdefine_line|#define _PAGE_A&t;&t;&t;(1 &lt;&lt; _PAGE_A_BIT)&t;/* page accessed bit */
DECL|macro|_PAGE_D
mdefine_line|#define _PAGE_D&t;&t;&t;(1 &lt;&lt; _PAGE_D_BIT)&t;/* page dirty bit */
DECL|macro|_PAGE_PPN_MASK
mdefine_line|#define _PAGE_PPN_MASK&t;&t;(((__IA64_UL(1) &lt;&lt; IA64_MAX_PHYS_BITS) - 1) &amp; ~0xfffUL)
DECL|macro|_PAGE_ED
mdefine_line|#define _PAGE_ED&t;&t;(__IA64_UL(1) &lt;&lt; 52)&t;/* exception deferral */
DECL|macro|_PAGE_PROTNONE
mdefine_line|#define _PAGE_PROTNONE&t;&t;(__IA64_UL(1) &lt;&lt; 63)
multiline_comment|/* Valid only for a PTE with the present bit cleared: */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;&t;(1 &lt;&lt; 1)&t;&t;/* see swap &amp; file pte remarks below */
DECL|macro|_PFN_MASK
mdefine_line|#define _PFN_MASK&t;&t;_PAGE_PPN_MASK
multiline_comment|/* Mask of bits which may be changed by pte_modify(); the odd bits are there for _PAGE_PROTNONE */
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(_PAGE_P | _PAGE_PROTNONE | _PAGE_PL_MASK | _PAGE_AR_MASK | _PAGE_ED)
DECL|macro|_PAGE_SIZE_4K
mdefine_line|#define _PAGE_SIZE_4K&t;12
DECL|macro|_PAGE_SIZE_8K
mdefine_line|#define _PAGE_SIZE_8K&t;13
DECL|macro|_PAGE_SIZE_16K
mdefine_line|#define _PAGE_SIZE_16K&t;14
DECL|macro|_PAGE_SIZE_64K
mdefine_line|#define _PAGE_SIZE_64K&t;16
DECL|macro|_PAGE_SIZE_256K
mdefine_line|#define _PAGE_SIZE_256K&t;18
DECL|macro|_PAGE_SIZE_1M
mdefine_line|#define _PAGE_SIZE_1M&t;20
DECL|macro|_PAGE_SIZE_4M
mdefine_line|#define _PAGE_SIZE_4M&t;22
DECL|macro|_PAGE_SIZE_16M
mdefine_line|#define _PAGE_SIZE_16M&t;24
DECL|macro|_PAGE_SIZE_64M
mdefine_line|#define _PAGE_SIZE_64M&t;26
DECL|macro|_PAGE_SIZE_256M
mdefine_line|#define _PAGE_SIZE_256M&t;28
DECL|macro|_PAGE_SIZE_1G
mdefine_line|#define _PAGE_SIZE_1G&t;30
DECL|macro|_PAGE_SIZE_4G
mdefine_line|#define _PAGE_SIZE_4G&t;32
DECL|macro|__ACCESS_BITS
mdefine_line|#define __ACCESS_BITS&t;&t;_PAGE_ED | _PAGE_A | _PAGE_P | _PAGE_MA_WB
DECL|macro|__DIRTY_BITS_NO_ED
mdefine_line|#define __DIRTY_BITS_NO_ED&t;_PAGE_A | _PAGE_P | _PAGE_D | _PAGE_MA_WB
DECL|macro|__DIRTY_BITS
mdefine_line|#define __DIRTY_BITS&t;&t;_PAGE_ED | __DIRTY_BITS_NO_ED
multiline_comment|/*&n; * Definitions for first level:&n; *&n; * PGDIR_SHIFT determines what a first-level page table entry can map.&n; */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;&t;(PAGE_SHIFT + 2*(PAGE_SHIFT-3))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;&t;(__IA64_UL(1) &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;&t;(~(PGDIR_SIZE-1))
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;&t;(1UL &lt;&lt; (PAGE_SHIFT-3))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(5*PTRS_PER_PGD/8)&t;/* regions 0-4 are user regions */
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
multiline_comment|/*&n; * Definitions for second level:&n; *&n; * PMD_SHIFT determines the size of the area a second-level page table&n; * can map.&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;(PAGE_SHIFT + (PAGE_SHIFT-3))
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;(1UL &lt;&lt; (PAGE_SHIFT-3))
multiline_comment|/*&n; * Definitions for third level:&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;(__IA64_UL(1) &lt;&lt; (PAGE_SHIFT-3))
multiline_comment|/*&n; * All the normal masks have the &quot;page accessed&quot; bits on, as any time&n; * they are used, the page is accessed. They are cleared only by the&n; * page-out routines.&n; */
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PROTNONE | _PAGE_A)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RW)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_R)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_R)
DECL|macro|PAGE_COPY_EXEC
mdefine_line|#define PAGE_COPY_EXEC&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RX)
DECL|macro|PAGE_GATE
mdefine_line|#define PAGE_GATE&t;__pgprot(__ACCESS_BITS | _PAGE_PL_0 | _PAGE_AR_X_RX)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(__DIRTY_BITS  | _PAGE_PL_0 | _PAGE_AR_RWX)
DECL|macro|PAGE_KERNELRX
mdefine_line|#define PAGE_KERNELRX&t;__pgprot(__ACCESS_BITS | _PAGE_PL_0 | _PAGE_AR_RX)
macro_line|# ifndef __ASSEMBLY__
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * Next come the mappings that determine how mmap() protection bits&n; * (PROT_EXEC, PROT_READ, PROT_WRITE, PROT_NONE) get implemented.  The&n; * _P version gets used for a private shared memory segment, the _S&n; * version gets used for a shared memory segment with MAP_SHARED on.&n; * In a private shared memory segment, we do a copy-on-write if a task&n; * attempts to write to the page.&n; */
multiline_comment|/* xwr */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_READONLY&t;/* write to priv pg -&gt; copy &amp; make writable */
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_READONLY&t;/* ditto */
DECL|macro|__P100
mdefine_line|#define __P100&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_X_RX)
DECL|macro|__P101
mdefine_line|#define __P101&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RX)
DECL|macro|__P110
mdefine_line|#define __P110&t;PAGE_COPY_EXEC
DECL|macro|__P111
mdefine_line|#define __P111&t;PAGE_COPY_EXEC
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED&t;/* we don&squot;t have (and don&squot;t need) write-only */
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_X_RX)
DECL|macro|__S101
mdefine_line|#define __S101&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RX)
DECL|macro|__S110
mdefine_line|#define __S110&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RWX)
DECL|macro|__S111
mdefine_line|#define __S111&t;__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RWX)
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e)&t;printk(&quot;%s:%d: bad pgd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e)&t;printk(&quot;%s:%d: bad pmd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e)&t;printk(&quot;%s:%d: bad pte %016lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
multiline_comment|/*&n; * Some definitions to translate between mem_map, PTEs, and page addresses:&n; */
multiline_comment|/* Quick test to see if ADDR is a (potentially) valid physical address. */
r_static
r_inline
r_int
DECL|function|ia64_phys_addr_valid
id|ia64_phys_addr_valid
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
id|addr
op_amp
(paren
id|local_cpu_data-&gt;unimpl_pa_mask
)paren
)paren
op_eq
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * kern_addr_valid(ADDR) tests if ADDR is pointing to valid kernel&n; * memory.  For the return value to be meaningful, ADDR must be &gt;=&n; * PAGE_OFFSET.  This operation can be relatively expensive (e.g.,&n; * require a hash-, or multi-level tree-lookup or something of that&n; * sort) but it guarantees to return TRUE only if accessing the page&n; * at that address does not cause an error.  Note that there may be&n; * addresses for which kern_addr_valid() returns FALSE even though an&n; * access would not cause an error (e.g., this is typically true for&n; * memory mapped I/O regions.&n; *&n; * XXX Need to implement this for IA-64.&n; */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
multiline_comment|/*&n; * Now come the defines and routines to manage and access the three-level&n; * page table.&n; */
multiline_comment|/*&n; * On some architectures, special things need to be done when setting&n; * the PTE in a page table.  Nothing special needs to be on IA-64.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(ptep, pteval)&t;(*(ptep) = (pteval))
DECL|macro|set_pte_at
mdefine_line|#define set_pte_at(mm,addr,ptep,pteval) set_pte(ptep,pteval)
DECL|macro|RGN_SIZE
mdefine_line|#define RGN_SIZE&t;(1UL &lt;&lt; 61)
DECL|macro|RGN_KERNEL
mdefine_line|#define RGN_KERNEL&t;7
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;0xa000000200000000UL
macro_line|#ifdef CONFIG_VIRTUAL_MEM_MAP
DECL|macro|VMALLOC_END_INIT
macro_line|# define VMALLOC_END_INIT&t;(0xa000000000000000UL + (1UL &lt;&lt; (4*PAGE_SHIFT - 9)))
DECL|macro|VMALLOC_END
macro_line|# define VMALLOC_END&t;&t;vmalloc_end
r_extern
r_int
r_int
id|vmalloc_end
suffix:semicolon
macro_line|#else
DECL|macro|VMALLOC_END
macro_line|# define VMALLOC_END&t;&t;(0xa000000000000000UL + (1UL &lt;&lt; (4*PAGE_SHIFT - 9)))
macro_line|#endif
multiline_comment|/* fs/proc/kcore.c */
DECL|macro|kc_vaddr_to_offset
mdefine_line|#define&t;kc_vaddr_to_offset(v) ((v) - 0xa000000000000000UL)
DECL|macro|kc_offset_to_vaddr
mdefine_line|#define&t;kc_offset_to_vaddr(o) ((o) + 0xa000000000000000UL)
multiline_comment|/*&n; * Conversion functions: convert page frame number (pfn) and a protection value to a page&n; * table entry (pte).&n; */
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, pgprot) &bslash;&n;({ pte_t __pte; pte_val(__pte) = ((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(pgprot); __pte; })
multiline_comment|/* Extract pfn from pte.  */
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(_pte)&t;&t;((pte_val(_pte) &amp; _PFN_MASK) &gt;&gt; PAGE_SHIFT)
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;pfn_pte(page_to_pfn(page), (pgprot))
multiline_comment|/* This takes a physical page address that is used by the remapping functions */
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage, pgprot) &bslash;&n;({ pte_t __pte; pte_val(__pte) = physpage + pgprot_val(pgprot); __pte; })
DECL|macro|pte_modify
mdefine_line|#define pte_modify(_pte, newprot) &bslash;&n;&t;(__pte((pte_val(_pte) &amp; ~_PAGE_CHG_MASK) | (pgprot_val(newprot) &amp; _PAGE_CHG_MASK)))
DECL|macro|page_pte_prot
mdefine_line|#define page_pte_prot(page,prot)&t;mk_pte(page, prot)
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;&t;&t;page_pte_prot(page, __pgprot(0))
DECL|macro|pte_none
mdefine_line|#define pte_none(pte) &t;&t;&t;(!pte_val(pte))
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;&t;(pte_val(pte) &amp; (_PAGE_P | _PAGE_PROTNONE))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(mm,addr,pte)&t;&t;(pte_val(*(pte)) = 0UL)
multiline_comment|/* pte_page() returns the &quot;struct page *&quot; corresponding to the PTE: */
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)&t;&t;&t;virt_to_page(((pte_val(pte) &amp; _PFN_MASK) + PAGE_OFFSET))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;&t;(!ia64_phys_addr_valid(pmd_val(pmd)))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd)&t;&t;(pmd_val(pmd) != 0UL)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmdp)&t;&t;&t;(pmd_val(*(pmdp)) = 0UL)
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd)&t;&t;((unsigned long) __va(pmd_val(pmd) &amp; _PFN_MASK))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;&t;virt_to_page((pmd_val(pmd) + PAGE_OFFSET))
DECL|macro|pud_none
mdefine_line|#define pud_none(pud)&t;&t;&t;(!pud_val(pud))
DECL|macro|pud_bad
mdefine_line|#define pud_bad(pud)&t;&t;&t;(!ia64_phys_addr_valid(pud_val(pud)))
DECL|macro|pud_present
mdefine_line|#define pud_present(pud)&t;&t;(pud_val(pud) != 0UL)
DECL|macro|pud_clear
mdefine_line|#define pud_clear(pudp)&t;&t;&t;(pud_val(*(pudp)) = 0UL)
DECL|macro|pud_page
mdefine_line|#define pud_page(pud)&t;&t;&t;((unsigned long) __va(pud_val(pud) &amp; _PFN_MASK))
multiline_comment|/*&n; * The following have defined behavior only work if pte_present() is true.&n; */
DECL|macro|pte_user
mdefine_line|#define pte_user(pte)&t;&t;((pte_val(pte) &amp; _PAGE_PL_MASK) == _PAGE_PL_3)
DECL|macro|pte_read
mdefine_line|#define pte_read(pte)&t;&t;(((pte_val(pte) &amp; _PAGE_AR_MASK) &gt;&gt; _PAGE_AR_SHIFT) &lt; 6)
DECL|macro|pte_write
mdefine_line|#define pte_write(pte)&t;((unsigned) (((pte_val(pte) &amp; _PAGE_AR_MASK) &gt;&gt; _PAGE_AR_SHIFT) - 2) &lt;= 4)
DECL|macro|pte_exec
mdefine_line|#define pte_exec(pte)&t;&t;((pte_val(pte) &amp; _PAGE_AR_RX) != 0)
DECL|macro|pte_dirty
mdefine_line|#define pte_dirty(pte)&t;&t;((pte_val(pte) &amp; _PAGE_D) != 0)
DECL|macro|pte_young
mdefine_line|#define pte_young(pte)&t;&t;((pte_val(pte) &amp; _PAGE_A) != 0)
DECL|macro|pte_file
mdefine_line|#define pte_file(pte)&t;&t;((pte_val(pte) &amp; _PAGE_FILE) != 0)
multiline_comment|/*&n; * Note: we convert AR_RWX to AR_RX and AR_RW to AR_R by clearing the 2nd bit in the&n; * access rights:&n; */
DECL|macro|pte_wrprotect
mdefine_line|#define pte_wrprotect(pte)&t;(__pte(pte_val(pte) &amp; ~_PAGE_AR_RW))
DECL|macro|pte_mkwrite
mdefine_line|#define pte_mkwrite(pte)&t;(__pte(pte_val(pte) | _PAGE_AR_RW))
DECL|macro|pte_mkexec
mdefine_line|#define pte_mkexec(pte)&t;&t;(__pte(pte_val(pte) | _PAGE_AR_RX))
DECL|macro|pte_mkold
mdefine_line|#define pte_mkold(pte)&t;&t;(__pte(pte_val(pte) &amp; ~_PAGE_A))
DECL|macro|pte_mkyoung
mdefine_line|#define pte_mkyoung(pte)&t;(__pte(pte_val(pte) | _PAGE_A))
DECL|macro|pte_mkclean
mdefine_line|#define pte_mkclean(pte)&t;(__pte(pte_val(pte) &amp; ~_PAGE_D))
DECL|macro|pte_mkdirty
mdefine_line|#define pte_mkdirty(pte)&t;(__pte(pte_val(pte) | _PAGE_D))
multiline_comment|/*&n; * Macro to a page protection value as &quot;uncacheable&quot;.  Note that &quot;protection&quot; is really a&n; * misnomer here as the protection value contains the memory attribute bits, dirty bits,&n; * and various other bits as well.&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached(prot)&t;&t;__pgprot((pgprot_val(prot) &amp; ~_PAGE_MA_MASK) | _PAGE_MA_UC)
multiline_comment|/*&n; * Macro to make mark a page protection value as &quot;write-combining&quot;.&n; * Note that &quot;protection&quot; is really a misnomer here as the protection&n; * value contains the memory attribute bits, dirty bits, and various&n; * other bits as well.  Accesses through a write-combining translation&n; * works bypasses the caches, but does allow for consecutive writes to&n; * be combined into single (but larger) write transactions.&n; */
DECL|macro|pgprot_writecombine
mdefine_line|#define pgprot_writecombine(prot)&t;__pgprot((pgprot_val(prot) &amp; ~_PAGE_MA_MASK) | _PAGE_MA_WC)
r_static
r_inline
r_int
r_int
DECL|function|pgd_index
id|pgd_index
(paren
r_int
r_int
id|address
)paren
(brace
r_int
r_int
id|region
op_assign
id|address
op_rshift
l_int|61
suffix:semicolon
r_int
r_int
id|l1index
op_assign
(paren
id|address
op_rshift
id|PGDIR_SHIFT
)paren
op_amp
(paren
(paren
id|PTRS_PER_PGD
op_rshift
l_int|3
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_return
(paren
id|region
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|6
)paren
)paren
op_or
id|l1index
suffix:semicolon
)brace
multiline_comment|/* The offset in the 1-level directory is given by the 3 region bits&n;   (61..63) and the level-1 bits.  */
r_static
r_inline
id|pgd_t
op_star
DECL|function|pgd_offset
id|pgd_offset
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|mm-&gt;pgd
op_plus
id|pgd_index
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/* In the kernel&squot;s mapped region we completely ignore the region number&n;   (since we know it&squot;s in region number 5). */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(addr) &bslash;&n;&t;(init_mm.pgd + (((addr) &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD - 1)))
multiline_comment|/* Look up a pgd entry in the gate area.  On IA-64, the gate-area&n;   resides in the kernel-mapped segment, hence we use pgd_offset_k()&n;   here.  */
DECL|macro|pgd_offset_gate
mdefine_line|#define pgd_offset_gate(mm, addr)&t;pgd_offset_k(addr)
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir,addr) &bslash;&n;&t;((pmd_t *) pud_page(*(dir)) + (((addr) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD - 1)))
multiline_comment|/*&n; * Find an entry in the third-level page table.  This looks more complicated than it&n; * should be because some platforms place page tables in high memory.&n; */
DECL|macro|pte_index
mdefine_line|#define pte_index(addr)&t; &t;(((addr) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir,addr)&t;((pte_t *) pmd_page_kernel(*(dir)) + pte_index(addr))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir,addr)&t;pte_offset_kernel(dir, addr)
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir,addr)&t;pte_offset_map(dir, addr)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte)&t;&t;&t;do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte)&t;&t;do { } while (0)
multiline_comment|/* atomic versions of the some PTE manipulations: */
r_static
r_inline
r_int
DECL|function|ptep_test_and_clear_young
id|ptep_test_and_clear_young
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
comma
id|pte_t
op_star
id|ptep
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|pte_young
c_func
(paren
op_star
id|ptep
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|test_and_clear_bit
c_func
(paren
id|_PAGE_A_BIT
comma
id|ptep
)paren
suffix:semicolon
macro_line|#else
id|pte_t
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_young
c_func
(paren
id|pte
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|set_pte_at
c_func
(paren
id|vma-&gt;vm_mm
comma
id|addr
comma
id|ptep
comma
id|pte_mkold
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
macro_line|#endif
)brace
r_static
r_inline
r_int
DECL|function|ptep_test_and_clear_dirty
id|ptep_test_and_clear_dirty
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
comma
id|pte_t
op_star
id|ptep
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|pte_dirty
c_func
(paren
op_star
id|ptep
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|test_and_clear_bit
c_func
(paren
id|_PAGE_D_BIT
comma
id|ptep
)paren
suffix:semicolon
macro_line|#else
id|pte_t
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_dirty
c_func
(paren
id|pte
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|set_pte_at
c_func
(paren
id|vma-&gt;vm_mm
comma
id|addr
comma
id|ptep
comma
id|pte_mkclean
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
macro_line|#endif
)brace
r_static
r_inline
id|pte_t
DECL|function|ptep_get_and_clear
id|ptep_get_and_clear
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
comma
id|pte_t
op_star
id|ptep
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_return
id|__pte
c_func
(paren
id|xchg
c_func
(paren
(paren
r_int
op_star
)paren
id|ptep
comma
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#else
id|pte_t
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
id|pte_clear
c_func
(paren
id|mm
comma
id|addr
comma
id|ptep
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
macro_line|#endif
)brace
r_static
r_inline
r_void
DECL|function|ptep_set_wrprotect
id|ptep_set_wrprotect
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
comma
id|pte_t
op_star
id|ptep
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_int
r_int
r_new
comma
id|old
suffix:semicolon
r_do
(brace
id|old
op_assign
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
suffix:semicolon
r_new
op_assign
id|pte_val
c_func
(paren
id|pte_wrprotect
c_func
(paren
id|__pte
(paren
id|old
)paren
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|ptep
comma
id|old
comma
r_new
)paren
op_ne
id|old
)paren
suffix:semicolon
macro_line|#else
id|pte_t
id|old_pte
op_assign
op_star
id|ptep
suffix:semicolon
id|set_pte_at
c_func
(paren
id|mm
comma
id|addr
comma
id|ptep
comma
id|pte_wrprotect
c_func
(paren
id|old_pte
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_inline
r_int
DECL|function|pte_same
id|pte_same
(paren
id|pte_t
id|a
comma
id|pte_t
id|b
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|a
)paren
op_eq
id|pte_val
c_func
(paren
id|b
)paren
suffix:semicolon
)brace
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
r_extern
r_void
id|paging_init
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Note: The macros below rely on the fact that MAX_SWAPFILES_SHIFT &lt;= number of&n; *&t; bits in the swap-type field of the swap pte.  It would be nice to&n; *&t; enforce that, but we can&squot;t easily include &lt;linux/swap.h&gt; here.&n; *&t; (Of course, better still would be to define MAX_SWAPFILES_SHIFT here...).&n; *&n; * Format of swap pte:&n; *&t;bit   0   : present bit (must be zero)&n; *&t;bit   1   : _PAGE_FILE (must be zero)&n; *&t;bits  2- 8: swap-type&n; *&t;bits  9-62: swap offset&n; *&t;bit  63   : _PAGE_PROTNONE bit&n; *&n; * Format of file pte:&n; *&t;bit   0   : present bit (must be zero)&n; *&t;bit   1   : _PAGE_FILE (must be one)&n; *&t;bits  2-62: file_offset/PAGE_SIZE&n; *&t;bit  63   : _PAGE_PROTNONE bit&n; */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(entry)&t;&t;(((entry).val &gt;&gt; 2) &amp; 0x7f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(entry)&t;&t;(((entry).val &lt;&lt; 1) &gt;&gt; 10)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type,offset)&t;((swp_entry_t) { ((type) &lt;&lt; 2) | ((long) (offset) &lt;&lt; 9) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;&t;61
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(pte)&t;&t;((pte_val(pte) &lt;&lt; 1) &gt;&gt; 3)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off)&t;&t;((pte_t) { ((off) &lt;&lt; 2) | _PAGE_FILE })
multiline_comment|/* XXX is this right? */
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma, vaddr, paddr, size, prot)&t;&t;&bslash;&n;&t;&t;remap_pfn_range(vma, vaddr, (paddr) &gt;&gt; PAGE_SHIFT, size, prot)
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_int
r_int
id|empty_zero_page
(braket
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_int
r_int
)paren
)braket
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|zero_page_memmap_ptr
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (zero_page_memmap_ptr)
multiline_comment|/* We provide our own get_unmapped_area to cope with VA holes for userland */
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
macro_line|#ifdef CONFIG_HUGETLB_PAGE
DECL|macro|HUGETLB_PGDIR_SHIFT
mdefine_line|#define HUGETLB_PGDIR_SHIFT&t;(HPAGE_SHIFT + 2*(PAGE_SHIFT-3))
DECL|macro|HUGETLB_PGDIR_SIZE
mdefine_line|#define HUGETLB_PGDIR_SIZE&t;(__IA64_UL(1) &lt;&lt; HUGETLB_PGDIR_SHIFT)
DECL|macro|HUGETLB_PGDIR_MASK
mdefine_line|#define HUGETLB_PGDIR_MASK&t;(~(HUGETLB_PGDIR_SIZE-1))
r_struct
id|mmu_gather
suffix:semicolon
r_extern
r_void
id|hugetlb_free_pgtables
c_func
(paren
r_struct
id|mmu_gather
op_star
id|tlb
comma
r_struct
id|vm_area_struct
op_star
id|prev
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * IA-64 doesn&squot;t have any external MMU info: the page tables contain all the necessary&n; * information.  However, we use this routine to take care of any (delayed) i-cache&n; * flushing that may be necessary.&n; */
r_extern
r_void
id|update_mmu_cache
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vaddr
comma
id|pte_t
id|pte
)paren
suffix:semicolon
DECL|macro|__HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
mdefine_line|#define __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
multiline_comment|/*&n; * Update PTEP with ENTRY, which is guaranteed to be a less&n; * restrictive PTE.  That is, ENTRY may have the ACCESSED, DIRTY, and&n; * WRITABLE bits turned on, when the value at PTEP did not.  The&n; * WRITABLE bit may only be turned if SAFELY_WRITABLE is TRUE.&n; *&n; * SAFELY_WRITABLE is TRUE if we can update the value at PTEP without&n; * having to worry about races.  On SMP machines, there are only two&n; * cases where this is true:&n; *&n; *&t;(1) *PTEP has the PRESENT bit turned OFF&n; *&t;(2) ENTRY has the DIRTY bit turned ON&n; *&n; * On ia64, we could implement this routine with a cmpxchg()-loop&n; * which ORs in the _PAGE_A/_PAGE_D bit if they&squot;re set in ENTRY.&n; * However, like on x86, we can get a more streamlined version by&n; * observing that it is OK to drop ACCESSED bit updates when&n; * SAFELY_WRITABLE is FALSE.  Besides being rare, all that would do is&n; * result in an extra Access-bit fault, which would then turn on the&n; * ACCESSED bit in the low-level fault handler (iaccess_bit or&n; * daccess_bit in ivt.S).&n; */
macro_line|#ifdef CONFIG_SMP
DECL|macro|ptep_set_access_flags
macro_line|# define ptep_set_access_flags(__vma, __addr, __ptep, __entry, __safely_writable)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (__safely_writable) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_pte(__ptep, __entry);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;flush_tlb_page(__vma, __addr);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else
DECL|macro|ptep_set_access_flags
macro_line|# define ptep_set_access_flags(__vma, __addr, __ptep, __entry, __safely_writable)&t;&bslash;&n;&t;ptep_establish(__vma, __addr, __ptep, __entry)
macro_line|#endif
macro_line|#  ifdef CONFIG_VIRTUAL_MEM_MAP
multiline_comment|/* arch mem_map init routine is needed due to holes in a virtual mem_map */
DECL|macro|__HAVE_ARCH_MEMMAP_INIT
macro_line|#   define __HAVE_ARCH_MEMMAP_INIT
r_extern
r_void
id|memmap_init
(paren
r_int
r_int
id|size
comma
r_int
id|nid
comma
r_int
r_int
id|zone
comma
r_int
r_int
id|start_pfn
)paren
suffix:semicolon
macro_line|#  endif /* CONFIG_VIRTUAL_MEM_MAP */
macro_line|# endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * Identity-mapped regions use a large page size.  We&squot;ll call such large pages&n; * &quot;granules&quot;.  If you can think of a better name that&squot;s unambiguous, let me&n; * know...&n; */
macro_line|#if defined(CONFIG_IA64_GRANULE_64MB)
DECL|macro|IA64_GRANULE_SHIFT
macro_line|# define IA64_GRANULE_SHIFT&t;_PAGE_SIZE_64M
macro_line|#elif defined(CONFIG_IA64_GRANULE_16MB)
DECL|macro|IA64_GRANULE_SHIFT
macro_line|# define IA64_GRANULE_SHIFT&t;_PAGE_SIZE_16M
macro_line|#endif
DECL|macro|IA64_GRANULE_SIZE
mdefine_line|#define IA64_GRANULE_SIZE&t;(1 &lt;&lt; IA64_GRANULE_SHIFT)
multiline_comment|/*&n; * log2() of the page size we use to map the kernel image (IA64_TR_KERNEL):&n; */
DECL|macro|KERNEL_TR_PAGE_SHIFT
mdefine_line|#define KERNEL_TR_PAGE_SHIFT&t;_PAGE_SIZE_64M
DECL|macro|KERNEL_TR_PAGE_SIZE
mdefine_line|#define KERNEL_TR_PAGE_SIZE&t;(1 &lt;&lt; KERNEL_TR_PAGE_SHIFT)
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
multiline_comment|/* These tell get_user_pages() that the first gate page is accessible from user-level.  */
DECL|macro|FIXADDR_USER_START
mdefine_line|#define FIXADDR_USER_START&t;GATE_ADDR
DECL|macro|FIXADDR_USER_END
mdefine_line|#define FIXADDR_USER_END&t;(GATE_ADDR + 2*PERCPU_PAGE_SIZE)
DECL|macro|__HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
mdefine_line|#define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
DECL|macro|__HAVE_ARCH_PTEP_TEST_AND_CLEAR_DIRTY
mdefine_line|#define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_DIRTY
DECL|macro|__HAVE_ARCH_PTEP_GET_AND_CLEAR
mdefine_line|#define __HAVE_ARCH_PTEP_GET_AND_CLEAR
DECL|macro|__HAVE_ARCH_PTEP_SET_WRPROTECT
mdefine_line|#define __HAVE_ARCH_PTEP_SET_WRPROTECT
DECL|macro|__HAVE_ARCH_PTE_SAME
mdefine_line|#define __HAVE_ARCH_PTE_SAME
DECL|macro|__HAVE_ARCH_PGD_OFFSET_GATE
mdefine_line|#define __HAVE_ARCH_PGD_OFFSET_GATE
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#include &lt;asm-generic/pgtable-nopud.h&gt;
macro_line|#endif /* _ASM_IA64_PGTABLE_H */
eof
