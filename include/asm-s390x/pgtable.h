multiline_comment|/*&n; *  include/asm-s390/pgtable.h&n; *&n; *  S390 64bit version&n; *    Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com)&n; *               Ulrich Weigand (weigand@de.ibm.com)&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/pgtable.h&quot;&n; */
macro_line|#ifndef _ASM_S390_PGTABLE_H
DECL|macro|_ASM_S390_PGTABLE_H
mdefine_line|#define _ASM_S390_PGTABLE_H
multiline_comment|/*&n; * The Linux memory management assumes a three-level page table setup. On&n; * the S390, we use that, but &quot;fold&quot; the mid level into the top-level page&n; * table, so that we physically have the same two-level page table as the&n; * S390 mmu expects.&n; *&n; * This file contains the functions and defines necessary to modify and use&n; * the S390 page table tree.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4096
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Caches aren&squot;t brain-dead on S390. */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()                       do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)                      do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma, start, end)      do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr)           do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)                 do { } while (0)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;do { } while (0)
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)          do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)               do { } while (0)
multiline_comment|/*&n; * The S390 doesn&squot;t have any external MMU info: the kernel page&n; * tables contain all the necessary information.&n; */
DECL|macro|update_mmu_cache
mdefine_line|#define update_mmu_cache(vma, address, pte)     do { } while (0)
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_char
id|empty_zero_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * PMD_SHIFT determines the size of the area a second-level page&n; * table can map&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT       21
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE        (1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK        (~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT     31
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE      (1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK      (~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: the S390 is two to five-level,&n; * currently we use a 3 level lookup&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE    512
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD    1024
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD    2048
multiline_comment|/*&n; * pgd entries used up by user/kernel:&n; */
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD  2048
DECL|macro|USER_PGD_PTRS
mdefine_line|#define USER_PGD_PTRS      2048
DECL|macro|KERNEL_PGD_PTRS
mdefine_line|#define KERNEL_PGD_PTRS    2048
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR  0
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %016lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET  (8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START   (((unsigned long) high_memory + VMALLOC_OFFSET) &bslash;&n;                         &amp; ~(VMALLOC_OFFSET-1))
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END     (0x40000000000L)
multiline_comment|/*&n; * A pagetable entry of S390 has following format:&n; * |                     PFRA                         |0IP0|  OS  |&n; * 0000000000111111111122222222223333333333444444444455555555556666&n; * 0123456789012345678901234567890123456789012345678901234567890123&n; *&n; * I Page-Invalid Bit:    Page is not available for address-translation&n; * P Page-Protection Bit: Store access not possible for page&n; *&n; * A segmenttable entry of S390 has following format:&n; * |        P-table origin                              |      TT&n; * 0000000000111111111122222222223333333333444444444455555555556666&n; * 0123456789012345678901234567890123456789012345678901234567890123&n; *&n; * I Segment-Invalid Bit:    Segment is not available for address-translation&n; * C Common-Segment Bit:     Segment is not private (PoP 3-30)&n; * P Page-Protection Bit: Store access not possible for page&n; * TT Type 00&n; *&n; * A region table entry of S390 has following format:&n; * |        S-table origin                             |   TF  TTTL&n; * 0000000000111111111122222222223333333333444444444455555555556666&n; * 0123456789012345678901234567890123456789012345678901234567890123&n; *&n; * I Segment-Invalid Bit:    Segment is not available for address-translation&n; * TT Type 01&n; * TF&n; * TL Table lenght&n; *&n; * The regiontable origin of S390 has following format:&n; * |      region table origon                          |       DTTL&n; * 0000000000111111111122222222223333333333444444444455555555556666&n; * 0123456789012345678901234567890123456789012345678901234567890123&n; *&n; * X Space-Switch event:&n; * G Segment-Invalid Bit:  &n; * P Private-Space Bit:    &n; * S Storage-Alteration:&n; * R Real space&n; * TL Table-Length:&n; *&n; * A storage key has the following format:&n; * | ACC |F|R|C|0|&n; *  0   3 4 5 6 7&n; * ACC: access key&n; * F  : fetch protection bit&n; * R  : referenced bit&n; * C  : changed bit&n; */
multiline_comment|/* Bits in the page table entry */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT   0x001          /* Software                         */
DECL|macro|_PAGE_MKCLEAR
mdefine_line|#define _PAGE_MKCLEAR   0x002          /* Software                         */
DECL|macro|_PAGE_RO
mdefine_line|#define _PAGE_RO        0x200          /* HW read-only                     */
DECL|macro|_PAGE_INVALID
mdefine_line|#define _PAGE_INVALID   0x400          /* HW invalid                       */
multiline_comment|/* Bits in the segment table entry */
DECL|macro|_PMD_ENTRY_INV
mdefine_line|#define _PMD_ENTRY_INV   0x20          /* invalid segment table entry      */
DECL|macro|_PMD_ENTRY
mdefine_line|#define _PMD_ENTRY       0x00        
multiline_comment|/* Bits in the region third table entry */
DECL|macro|_PGD_ENTRY_INV
mdefine_line|#define _PGD_ENTRY_INV   0x20          /* invalid region table entry       */
DECL|macro|_PGD_ENTRY
mdefine_line|#define _PGD_ENTRY       0x07
multiline_comment|/*&n; * User and kernel page directory&n; */
DECL|macro|_REGION_THIRD
mdefine_line|#define _REGION_THIRD       0x4
DECL|macro|_REGION_THIRD_LEN
mdefine_line|#define _REGION_THIRD_LEN   0x3 
DECL|macro|_REGION_TABLE
mdefine_line|#define _REGION_TABLE       (_REGION_THIRD|_REGION_THIRD_LEN|0x40|0x100)
DECL|macro|_KERN_REGION_TABLE
mdefine_line|#define _KERN_REGION_TABLE  (_REGION_THIRD|_REGION_THIRD_LEN)
multiline_comment|/* Bits in the storage key */
DECL|macro|_PAGE_CHANGED
mdefine_line|#define _PAGE_CHANGED    0x02          /* HW changed bit                   */
DECL|macro|_PAGE_REFERENCED
mdefine_line|#define _PAGE_REFERENCED 0x04          /* HW referenced bit                */
multiline_comment|/*&n; * No mapping available&n; */
DECL|macro|PAGE_INVALID
mdefine_line|#define PAGE_INVALID    __pgprot(_PAGE_INVALID)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE       __pgprot(_PAGE_PRESENT | _PAGE_INVALID)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_PAGE_PRESENT | _PAGE_RO)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_PAGE_PRESENT | _PAGE_RO)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_PAGE_PRESENT )
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL     __pgprot(_PAGE_PRESENT )
multiline_comment|/*&n; * The S390 can&squot;t do page protection for execute, and considers that the&n; * same are read. Also, write permissions imply read permissions. This is&n; * the closest we can get..&n; */
DECL|macro|__P000
mdefine_line|#define __P000  PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001  PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010  PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011  PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100  PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101  PAGE_READONLY
DECL|macro|__P110
mdefine_line|#define __P110  PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111  PAGE_COPY
DECL|macro|__S000
mdefine_line|#define __S000  PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001  PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010  PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011  PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100  PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101  PAGE_READONLY
DECL|macro|__S110
mdefine_line|#define __S110  PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111  PAGE_SHARED
multiline_comment|/*&n; * Certain architectures need to do special things when PTEs&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|function|set_pte
r_extern
r_inline
r_void
id|set_pte
c_func
(paren
id|pte_t
op_star
id|pteptr
comma
id|pte_t
id|pteval
)paren
(brace
r_if
c_cond
(paren
(paren
id|pte_val
c_func
(paren
id|pteval
)paren
op_amp
(paren
id|_PAGE_MKCLEAR
op_or
id|_PAGE_INVALID
)paren
)paren
op_eq
id|_PAGE_MKCLEAR
)paren
(brace
id|pte_val
c_func
(paren
id|pteval
)paren
op_and_assign
op_complement
id|_PAGE_MKCLEAR
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sske %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;a&quot;
(paren
id|pte_val
c_func
(paren
id|pteval
)paren
)paren
)paren
suffix:semicolon
)brace
op_star
id|pteptr
op_assign
id|pteval
suffix:semicolon
)brace
multiline_comment|/*&n; * Permanent address of a page.&n; */
DECL|macro|page_address
mdefine_line|#define page_address(page) ((page)-&gt;virtual)
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x) ((x) &gt;&gt; (20-PAGE_SHIFT))
multiline_comment|/*&n; * pgd/pmd/pte query functions&n; */
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
(paren
id|pgd_val
c_func
(paren
id|pgd
)paren
op_amp
op_complement
id|PAGE_MASK
)paren
op_eq
id|_PGD_ENTRY
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
id|pgd_val
c_func
(paren
id|pgd
)paren
op_amp
id|_PGD_ENTRY_INV
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
(paren
op_complement
id|PAGE_MASK
op_amp
op_complement
id|_PGD_ENTRY_INV
)paren
)paren
op_ne
id|_PGD_ENTRY
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
(paren
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
op_complement
id|PAGE_MASK
)paren
op_eq
id|_PMD_ENTRY
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
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
id|_PMD_ENTRY_INV
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
(paren
op_complement
id|PAGE_MASK
op_amp
op_complement
id|_PMD_ENTRY_INV
)paren
)paren
op_ne
id|_PMD_ENTRY
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
id|_PAGE_PRESENT
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
(paren
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
(paren
id|_PAGE_INVALID
op_or
id|_PAGE_RO
op_or
id|_PAGE_PRESENT
)paren
)paren
op_eq
id|_PAGE_INVALID
)paren
suffix:semicolon
)brace
DECL|macro|pte_same
mdefine_line|#define pte_same(a,b)&t;(pte_val(a) == pte_val(b))
multiline_comment|/*&n; * query functions pte_write/pte_dirty/pte_young only work if&n; * pte_present() is true. Undefined behaviour if not..&n; */
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
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_RO
)paren
op_eq
l_int|0
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
r_int
id|skey
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;iske %0,%1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|skey
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|pte_val
c_func
(paren
id|pte
)paren
)paren
)paren
suffix:semicolon
r_return
id|skey
op_amp
id|_PAGE_CHANGED
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
r_int
id|skey
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;iske %0,%1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|skey
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|pte_val
c_func
(paren
id|pte
)paren
)paren
)paren
suffix:semicolon
r_return
id|skey
op_amp
id|_PAGE_REFERENCED
suffix:semicolon
)brace
multiline_comment|/*&n; * pgd/pmd/pte modification functions&n; */
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
id|_PGD_ENTRY_INV
op_or
id|_PGD_ENTRY
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
id|_PMD_ENTRY_INV
op_or
id|_PMD_ENTRY
suffix:semicolon
id|pmd_val1
c_func
(paren
op_star
id|pmdp
)paren
op_assign
id|_PMD_ENTRY_INV
op_or
id|_PMD_ENTRY
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
id|_PAGE_INVALID
suffix:semicolon
)brace
DECL|macro|PTE_INIT
mdefine_line|#define PTE_INIT(x) pte_clear(x)
multiline_comment|/*&n; * The following pte_modification functions only work if &n; * pte_present() is true. Undefined behaviour if not..&n; */
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
id|PAGE_MASK
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
id|_PAGE_RO
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
id|_PAGE_RO
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
multiline_comment|/* The only user of pte_mkclean is the fork() code.&n;&t;   We must *not* clear the *physical* page dirty bit&n;&t;   just because fork() wants to clear the dirty bit in&n;&t;   *one* of the page&squot;s mappings.  So we just do nothing. */
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
multiline_comment|/* We can&squot;t set the changed bit atomically either. For now we&n;         * set (!) the page referenced bit. */
id|asm
r_volatile
(paren
l_string|&quot;sske %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
id|_PAGE_CHANGED
op_or
id|_PAGE_REFERENCED
)paren
comma
l_string|&quot;a&quot;
(paren
id|pte_val
c_func
(paren
id|pte
)paren
)paren
)paren
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_MKCLEAR
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
id|asm
r_volatile
(paren
l_string|&quot;rrbe 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|pte_val
c_func
(paren
id|pte
)paren
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
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
multiline_comment|/* To set the referenced bit we read the first word from the real&n;&t; * page with a special instruction: load using real address (lura).&n;&t; * Isn&squot;t S/390 a nice architecture ?! */
id|asm
r_volatile
(paren
l_string|&quot;lura 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|PAGE_MASK
)paren
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_return
id|pte
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
id|ccode
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;rrbe 0,%1&bslash;n&bslash;t&quot;
l_string|&quot;ipm  %0&bslash;n&bslash;t&quot;
l_string|&quot;srl  %0,28&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|ccode
op_amp
l_int|2
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
id|skey
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;iske %0,%1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|skey
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skey
op_amp
id|_PAGE_CHANGED
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* We can&squot;t clear the changed bit atomically. For now we&n;         * clear (!) the page referenced bit. */
id|asm
r_volatile
(paren
l_string|&quot;sske %0,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;a&quot;
(paren
op_star
id|ptep
)paren
)paren
suffix:semicolon
r_return
l_int|1
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
id|pte_t
id|pte
op_assign
op_star
id|ptep
suffix:semicolon
id|pte_clear
c_func
(paren
id|ptep
)paren
suffix:semicolon
r_return
id|pte
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
id|pte_t
id|old_pte
op_assign
op_star
id|ptep
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|pte_wrprotect
c_func
(paren
id|old_pte
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
id|pte_mkdirty
c_func
(paren
op_star
id|ptep
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
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
id|__pte
suffix:semicolon
id|pte_val
c_func
(paren
id|__pte
)paren
op_assign
id|physpage
op_plus
id|pgprot_val
c_func
(paren
id|pgprot
)paren
suffix:semicolon
r_return
id|__pte
suffix:semicolon
)brace
DECL|macro|mk_pte
mdefine_line|#define mk_pte(pg, pgprot)                                                &bslash;&n;({                                                                        &bslash;&n;&t;struct page *__page = (pg);                                       &bslash;&n;&t;unsigned long __physpage = __pa((__page-mem_map) &lt;&lt; PAGE_SHIFT);  &bslash;&n;&t;pte_t __pte = mk_pte_phys(__physpage, (pgprot));                  &bslash;&n;&t;                                                                  &bslash;&n;&t;if (__page != ZERO_PAGE(__physpage)) {                            &bslash;&n;&t;&t;int __users = page_count(__page);                         &bslash;&n;&t;&t;__users -= !!__page-&gt;buffers + !!__page-&gt;mapping;         &bslash;&n;&t;                                                                  &bslash;&n;&t;&t;if (__users == 1)                                         &bslash;&n;&t;&t;&t;pte_val(__pte) |= _PAGE_MKCLEAR;                  &bslash;&n;        }                                                                 &bslash;&n;&t;                                                                  &bslash;&n;&t;__pte;                                                            &bslash;&n;})
DECL|macro|pte_page
mdefine_line|#define pte_page(x) (mem_map+(unsigned long)((pte_val(x) &gt;&gt; PAGE_SHIFT)))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) &bslash;&n;        ((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) ((address &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD-1))
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) ((mm)-&gt;pgd+pgd_index(address))
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pmd) &bslash;&n;        ((unsigned long) __va(pgd_val(pmd) &amp; PAGE_MASK))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir,addr) &bslash;&n;&t;((pmd_t *) pgd_page(*(dir)) + (((addr) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD - 1)))
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|pte_offset
mdefine_line|#define pte_offset(dir,addr) &bslash;&n;&t;((pte_t *) pmd_page(*(dir)) + (((addr) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1)))
multiline_comment|/*&n; * A page-table entry has some bits we have to treat in a special way.&n; * Bits 52 and bit 55 have to be zero, otherwise an specification&n; * exception will occur instead of a page translation exception. The&n; * specifiation exception has the bad habit not to store necessary&n; * information in the lowcore.&n; * Bit 53 and bit 54 are the page invalid bit and the page protection&n; * bit. We set both to indicate a swapped page.&n; * Bit 63 is used as the software page present bit. If a page is&n; * swapped this obviously has to be zero.&n; * This leaves the bits 0-51 and bits 56-62 to store type and offset.&n; * We use the 7 bits from 56-62 for the type and the 52 bits from 0-51&n; * for the offset.&n; * |                     offset                       |0110|type |0&n; * 0000000000111111111122222222223333333333444444444455555555556666&n; * 0123456789012345678901234567890123456789012345678901234567890123&n; */
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
l_int|1
)paren
op_or
(paren
id|offset
op_lshift
l_int|12
)paren
op_or
id|_PAGE_INVALID
op_or
id|_PAGE_RO
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
l_int|0xfffffffffffff6fe
suffix:semicolon
multiline_comment|/* better to be paranoid */
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry)&t;&t;(((entry).val &gt;&gt; 1) &amp; 0x3f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry)&t;((entry).val &gt;&gt; 12)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type,offset)&t;((swp_entry_t) { pte_val(mk_swap_pte((type),(offset))) })
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)&t;((pte_t) { (x).val })
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|PageSkip
mdefine_line|#define PageSkip(page)          (0)
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)   (1)
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
macro_line|#endif /* _S390_PAGE_H */
eof
