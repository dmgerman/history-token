multiline_comment|/*&n; *  include/asm-s390/pgtable.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner&n; *&n; *  Derived from &quot;include/asm-i386/pgtable.h&quot;&n; */
macro_line|#ifndef _ASM_S390_PGTABLE_H
DECL|macro|_ASM_S390_PGTABLE_H
mdefine_line|#define _ASM_S390_PGTABLE_H
multiline_comment|/*&n; * The Linux memory management assumes a three-level page table setup. On&n; * the S390, we use that, but &quot;fold&quot; the mid level into the top-level page&n; * table, so that we physically have the same two-level page table as the&n; * S390 mmu expects.&n; *&n; * This file contains the functions and defines necessary to modify and use&n; * the S390 page table tree.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/tasks.h&gt;
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
multiline_comment|/* Caches aren&squot;t brain-dead on S390. */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()                       do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)                      do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(mm, start, end)       do { } while (0)
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
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* Certain architectures need to do special things when PTEs&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval) ((*(pteptr)) = (pteval))
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT       22
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE        (1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK        (~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT     22
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE      (1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK      (~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: the S390 is two-level, so&n; * we don&squot;t really have any PMD directory physically.&n; * for S390 segment-table entries are combined to one PGD&n; * that leads to 1024 pte per pgd&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE    1024
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD    1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD    512
multiline_comment|/*&n; * pgd entries used up by user/kernel:&n; */
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD  512
DECL|macro|USER_PGD_PTRS
mdefine_line|#define USER_PGD_PTRS      512
DECL|macro|KERNEL_PGD_PTRS
mdefine_line|#define KERNEL_PGD_PTRS    512
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR  0
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %08lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET  (8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START   (((unsigned long) high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1))
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END     (0x7fffffffL)
multiline_comment|/*&n; * A pagetable entry of S390 has following format:&n; *&n; *  |   PFRA          |    |  OS  |&n; * 0                   0IP0&n; * 00000000001111111111222222222233&n; * 01234567890123456789012345678901&n; *&n; * I Page-Invalid Bit:    Page is not available for address-translation&n; * P Page-Protection Bit: Store access not possible for page&n; */
multiline_comment|/*&n; * A segmenttable entry of S390 has following format:&n; *&n; *  |   P-table origin      |  |PTL&n; * 0                         IC&n; * 00000000001111111111222222222233&n; * 01234567890123456789012345678901&n; *&n; * I Segment-Invalid Bit:    Segment is not available for address-translation&n; * C Common-Segment Bit:     Segment is not private (PoP 3-30)&n; * PTL Page-Table-Length:    Length of Page-table (PTL+1*16 entries -&gt; up to 256 entries)&n; */
multiline_comment|/*&n; * The segmenttable origin of S390 has following format:&n; *&n; *  |S-table origin   |     | STL |&n; * X                   **GPS&n; * 00000000001111111111222222222233&n; * 01234567890123456789012345678901&n; *&n; * X Space-Switch event:&n; * G Segment-Invalid Bit:     *&n; * P Private-Space Bit:       Segment is not private (PoP 3-30)&n; * S Storage-Alteration:&n; * STL Segment-Table-Length:  Length of Page-table (STL+1*16 entries -&gt; up to 2048 entries)&n; */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT   0x001          /* Software                         */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED  0x002          /* Software accessed                */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY     0x004          /* Software dirty                   */
DECL|macro|_PAGE_RO
mdefine_line|#define _PAGE_RO        0x200          /* HW read-only                     */
DECL|macro|_PAGE_INVALID
mdefine_line|#define _PAGE_INVALID   0x400          /* HW invalid                       */
DECL|macro|_PAGE_TABLE_LEN
mdefine_line|#define _PAGE_TABLE_LEN 0xf            /* only full page-tables            */
DECL|macro|_PAGE_TABLE_COM
mdefine_line|#define _PAGE_TABLE_COM 0x10           /* common page-table                */
DECL|macro|_PAGE_TABLE_INV
mdefine_line|#define _PAGE_TABLE_INV 0x20           /* invalid page-table               */
DECL|macro|_SEG_PRESENT
mdefine_line|#define _SEG_PRESENT    0x001          /* Software (overlap with PTL)      */
DECL|macro|_USER_SEG_TABLE_LEN
mdefine_line|#define _USER_SEG_TABLE_LEN    0x7f    /* user-segment-table up to 2 GB    */
DECL|macro|_KERNEL_SEG_TABLE_LEN
mdefine_line|#define _KERNEL_SEG_TABLE_LEN  0x7f    /* kernel-segment-table up to 2 GB  */
multiline_comment|/*&n; * User and Kernel pagetables are identical&n; */
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE     (_PAGE_TABLE_LEN )
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE   (_PAGE_TABLE_LEN )
multiline_comment|/*&n; * The Kernel segment-tables includes the User segment-table&n; */
DECL|macro|_SEGMENT_TABLE
mdefine_line|#define _SEGMENT_TABLE  (_USER_SEG_TABLE_LEN|0x80000000)
DECL|macro|_KERNSEG_TABLE
mdefine_line|#define _KERNSEG_TABLE  (_KERNEL_SEG_TABLE_LEN)
multiline_comment|/*&n; * No mapping available&n; */
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE       __pgprot(_PAGE_INVALID )
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_PAGE_PRESENT | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_RO)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_RO)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL     __pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_DIRTY)
multiline_comment|/*&n; * The S390 can&squot;t do page protection for execute, and considers that the same are read.&n; * Also, write permissions imply read permissions. This is the closest we can get..&n; */
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
multiline_comment|/*&n; * Define this if things work differently on an i386 and an i486:&n; * it will (on an i486) warn about kernel memory accesses that are&n; * done without a &squot;verify_area(VERIFY_WRITE,..)&squot;&n; *&n; * Kernel and User memory-access are done equal, so we don&squot;t need verify&n; */
DECL|macro|TEST_VERIFY_AREA
macro_line|#undef TEST_VERIFY_AREA
multiline_comment|/* page table for 0-4MB for everybody */
r_extern
r_int
r_int
id|pg0
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR                    (8*sizeof(unsigned long))
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK                        (~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*)==1&lt;&lt;SIZEOF_PTR_LOG2 */
multiline_comment|/* 64-bit machines, beware!  SRB. */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2                 2
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address) &bslash;&n;((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
multiline_comment|/* &n; * CR 7 (SPST) and cr 13 (HPST) are set to the user pgdir. &n; * Kernel is running in its own, disjunct address space,&n; * running in primary address space.&n; * Copy to/from user is done via access register mode with&n; * access registers set to 0 or 1. For that purpose we need &n; * set up CR 7 with the user pgd.  &n; * &n; */
DECL|macro|SET_PAGE_DIR
mdefine_line|#define SET_PAGE_DIR(tsk,pgdir)                                              &bslash;&n;do {                                                                         &bslash;&n;        unsigned long __pgdir = (__pa(pgdir) &amp; PAGE_MASK ) | _SEGMENT_TABLE; &bslash;&n;        (tsk)-&gt;thread.user_seg = __pgdir;                                    &bslash;&n;        if ((tsk) == current) {                                              &bslash;&n;                __asm__ __volatile__(&quot;lctl  7,7,%0&quot;: :&quot;m&quot; (__pgdir));        &bslash;&n;                __asm__ __volatile__(&quot;lctl  13,13,%0&quot;: :&quot;m&quot; (__pgdir));      &bslash;&n;        }                                                                    &bslash;&n;} while (0)
multiline_comment|/* &n; * CR 7 (SPST) and cr 13 (HPST) are set to the user pgdir. &n; * Kernel is running in its own, disjunct address space,&n; * running in primary address space.&n; * Copy to/from user is done via access register mode with&n; * access registers set to 0 or 1. For that purpose we need &n; * set up CR 7 with the user pgd.  &n; * &n; */
DECL|macro|SET_PAGE_DIR
mdefine_line|#define SET_PAGE_DIR(tsk,pgdir)                                              &bslash;&n;do {                                                                         &bslash;&n;        unsigned long __pgdir = (__pa(pgdir) &amp; PAGE_MASK ) | _SEGMENT_TABLE; &bslash;&n;        (tsk)-&gt;thread.user_seg = __pgdir;                                    &bslash;&n;        if ((tsk) == current) {                                              &bslash;&n;                __asm__ __volatile__(&quot;lctl  7,7,%0&quot;: :&quot;m&quot; (__pgdir));        &bslash;&n;                __asm__ __volatile__(&quot;lctl  13,13,%0&quot;: :&quot;m&quot; (__pgdir));      &bslash;&n;        }                                                                    &bslash;&n;} while (0)
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
)paren
)paren
op_eq
id|_PAGE_INVALID
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
id|_PAGE_PRESENT
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
id|_PAGE_TABLE_INV
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
op_eq
l_int|0
)paren
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
id|_SEG_PRESENT
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
id|pmdp
(braket
l_int|0
)braket
)paren
op_assign
id|_PAGE_TABLE_INV
suffix:semicolon
id|pmd_val
c_func
(paren
id|pmdp
(braket
l_int|1
)braket
)paren
op_assign
id|_PAGE_TABLE_INV
suffix:semicolon
id|pmd_val
c_func
(paren
id|pmdp
(braket
l_int|2
)braket
)paren
op_assign
id|_PAGE_TABLE_INV
suffix:semicolon
id|pmd_val
c_func
(paren
id|pmdp
(braket
l_int|3
)braket
)paren
op_assign
id|_PAGE_TABLE_INV
suffix:semicolon
)brace
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
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
l_int|0
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
l_int|0
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
l_int|1
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
)brace
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
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
id|_PAGE_RO
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
multiline_comment|/* who needs that&n;extern inline int pte_read(pte_t pte)           { return !(pte_val(pte) &amp; _PAGE_INVALID); }&n;extern inline int pte_exec(pte_t pte)           { return !(pte_val(pte) &amp; _PAGE_INVALID); }&n;extern inline pte_t pte_rdprotect(pte_t pte)    { pte_val(pte) |= _PAGE_INVALID; return pte; }&n;extern inline pte_t pte_exprotect(pte_t pte)    { pte_val(pte) |= _PAGE_INVALID; return pte; }&n;extern inline pte_t pte_mkread(pte_t pte)       { pte_val(pte) &amp;= _PAGE_INVALID; return pte; }&n;extern inline pte_t pte_mkexec(pte_t pte)       { pte_val(pte) &amp;= _PAGE_INVALID; return pte; }&n;*/
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
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_DIRTY
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
id|_PAGE_DIRTY
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
id|_PAGE_ACCESSED
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
id|_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot) &bslash;&n;({ pte_t __pte; pte_val(__pte) = __pa(((page)-mem_map)&lt;&lt;PAGE_SHIFT) + pgprot_val(pgprot); __pte; })
multiline_comment|/* This takes a physical page address that is used by the remapping functions */
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage, pgprot) &bslash;&n;({ pte_t __pte; pte_val(__pte) = physpage + pgprot_val(pgprot); __pte; })
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
DECL|macro|page_address
mdefine_line|#define page_address(page)  ((page)-&gt;virtual)
DECL|macro|pte_page
mdefine_line|#define pte_page(x) (mem_map+(unsigned long)((pte_val(pte) &gt;&gt; PAGE_SHIFT)))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) &bslash;&n;((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) ((address &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD-1))
DECL|macro|__pgd_offset
mdefine_line|#define __pgd_offset(address) pgd_index(address)
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) ((mm)-&gt;pgd+pgd_index(address))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
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
id|dir
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|pte_offset
mdefine_line|#define pte_offset(pmd, address) &bslash;&n;((pte_t *) (pmd_page(*pmd) + ((address&gt;&gt;10) &amp; ((PTRS_PER_PTE-1)&lt;&lt;2))))
multiline_comment|/* We don&squot;t use pmd cache, so these are dummy routines */
DECL|function|get_pmd_fast
r_extern
id|__inline__
id|pmd_t
op_star
id|get_pmd_fast
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
l_int|0
suffix:semicolon
)brace
DECL|function|free_pmd_fast
r_extern
id|__inline__
r_void
id|free_pmd_fast
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
)brace
DECL|function|free_pmd_slow
r_extern
id|__inline__
r_void
id|free_pmd_slow
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
)brace
r_extern
r_void
id|__handle_bad_pmd
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
r_extern
r_void
id|__handle_bad_pmd_kernel
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
suffix:semicolon
multiline_comment|/*&n; * The S390 doesn&squot;t have any external MMU info: the kernel page&n; * tables contain all the necessary information.&n; */
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
multiline_comment|/*&n; * a page-table entry has only 19 bit for offset and 7 bit for type&n; * if bits 0, 20 or 23 are set, a translation specification exceptions occures, and it&squot;s&n; * hard to find out the failing address&n; * therefor, we zero out this bits&n; */
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry) (((entry).val &gt;&gt; 1) &amp; 0x3f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry) (((entry).val &gt;&gt; 12) &amp; 0x7FFFF )
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type,offset) ((swp_entry_t) { (((type) &lt;&lt; 1) | &bslash;&n;                                                 ((offset) &lt;&lt; 12) | &bslash;&n;                                                 _PAGE_INVALID | _PAGE_RO) &bslash;&n;                                                 &amp; 0x7ffff6fe })
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)           ((swp_entry_t) { pte_val(pte) })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)             ((pte_t) { (x).val })
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|PageSkip
mdefine_line|#define PageSkip(page)          (0)
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)   (1)
macro_line|#endif /* _S390_PAGE_H */
eof
