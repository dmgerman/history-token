multiline_comment|/*&n; *  include/asm-s390/pgtable.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com)&n; *               Ulrich Weigand (weigand@de.ibm.com)&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/pgtable.h&quot;&n; */
macro_line|#ifndef _ASM_S390_PGTABLE_H
DECL|macro|_ASM_S390_PGTABLE_H
mdefine_line|#define _ASM_S390_PGTABLE_H
multiline_comment|/*&n; * The Linux memory management assumes a three-level page table setup. On&n; * the S390, we use that, but &quot;fold&quot; the mid level into the top-level page&n; * table, so that we physically have the same two-level page table as the&n; * S390 mmu expects.&n; *&n; * The &quot;pgd_xxx()&quot; functions are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; *&n; * This file contains the functions and defines necessary to modify and use&n; * the S390 page table tree.&n; */
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
multiline_comment|/*&n; * Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET  (8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START   (((unsigned long) high_memory + VMALLOC_OFFSET) &bslash;&n;&t;&t;&t; &amp; ~(VMALLOC_OFFSET-1))
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END     (0x7fffffffL)
multiline_comment|/*&n; * A pagetable entry of S390 has following format:&n; *  |   PFRA          |    |  OS  |&n; * 0                   0IP0&n; * 00000000001111111111222222222233&n; * 01234567890123456789012345678901&n; *&n; * I Page-Invalid Bit:    Page is not available for address-translation&n; * P Page-Protection Bit: Store access not possible for page&n; *&n; * A segmenttable entry of S390 has following format:&n; *  |   P-table origin      |  |PTL&n; * 0                         IC&n; * 00000000001111111111222222222233&n; * 01234567890123456789012345678901&n; *&n; * I Segment-Invalid Bit:    Segment is not available for address-translation&n; * C Common-Segment Bit:     Segment is not private (PoP 3-30)&n; * PTL Page-Table-Length:    Page-table length (PTL+1*16 entries -&gt; up to 256)&n; *&n; * The segmenttable origin of S390 has following format:&n; *&n; *  |S-table origin   |     | STL |&n; * X                   **GPS&n; * 00000000001111111111222222222233&n; * 01234567890123456789012345678901&n; *&n; * X Space-Switch event:&n; * G Segment-Invalid Bit:     *&n; * P Private-Space Bit:       Segment is not private (PoP 3-30)&n; * S Storage-Alteration:&n; * STL Segment-Table-Length:  Segment-table length (STL+1*16 entries -&gt; up to 2048)&n; *&n; * A storage key has the following format:&n; * | ACC |F|R|C|0|&n; *  0   3 4 5 6 7&n; * ACC: access key&n; * F  : fetch protection bit&n; * R  : referenced bit&n; * C  : changed bit&n; */
multiline_comment|/* Bits in the page table entry */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT   0x001          /* Software                         */
DECL|macro|_PAGE_MKCLEAN
mdefine_line|#define _PAGE_MKCLEAN   0x002          /* Software                         */
DECL|macro|_PAGE_ISCLEAN
mdefine_line|#define _PAGE_ISCLEAN   0x004&t;       /* Software&t;&t;&t;   */
DECL|macro|_PAGE_RO
mdefine_line|#define _PAGE_RO        0x200          /* HW read-only                     */
DECL|macro|_PAGE_INVALID
mdefine_line|#define _PAGE_INVALID   0x400          /* HW invalid                       */
multiline_comment|/* Bits in the segment table entry */
DECL|macro|_PAGE_TABLE_LEN
mdefine_line|#define _PAGE_TABLE_LEN 0xf            /* only full page-tables            */
DECL|macro|_PAGE_TABLE_COM
mdefine_line|#define _PAGE_TABLE_COM 0x10           /* common page-table                */
DECL|macro|_PAGE_TABLE_INV
mdefine_line|#define _PAGE_TABLE_INV 0x20           /* invalid page-table               */
DECL|macro|_SEG_PRESENT
mdefine_line|#define _SEG_PRESENT    0x001          /* Software (overlap with PTL)      */
multiline_comment|/* Bits int the storage key */
DECL|macro|_PAGE_CHANGED
mdefine_line|#define _PAGE_CHANGED    0x02          /* HW changed bit                   */
DECL|macro|_PAGE_REFERENCED
mdefine_line|#define _PAGE_REFERENCED 0x04          /* HW referenced bit                */
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
mdefine_line|#define _SEGMENT_TABLE  (_USER_SEG_TABLE_LEN|0x80000000|0x100)
DECL|macro|_KERNSEG_TABLE
mdefine_line|#define _KERNSEG_TABLE  (_KERNEL_SEG_TABLE_LEN)
multiline_comment|/*&n; * No mapping available&n; */
DECL|macro|PAGE_INVALID
mdefine_line|#define PAGE_INVALID&t;  __pgprot(_PAGE_INVALID)
DECL|macro|PAGE_NONE_SHARED
mdefine_line|#define PAGE_NONE_SHARED  __pgprot(_PAGE_PRESENT|_PAGE_INVALID)
DECL|macro|PAGE_NONE_PRIVATE
mdefine_line|#define PAGE_NONE_PRIVATE __pgprot(_PAGE_PRESENT|_PAGE_INVALID|_PAGE_ISCLEAN)
DECL|macro|PAGE_RO_SHARED
mdefine_line|#define PAGE_RO_SHARED&t;  __pgprot(_PAGE_PRESENT|_PAGE_RO)
DECL|macro|PAGE_RO_PRIVATE
mdefine_line|#define PAGE_RO_PRIVATE&t;  __pgprot(_PAGE_PRESENT|_PAGE_RO|_PAGE_ISCLEAN)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;  __pgprot(_PAGE_PRESENT|_PAGE_RO|_PAGE_ISCLEAN)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;  __pgprot(_PAGE_PRESENT)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;  __pgprot(_PAGE_PRESENT)
multiline_comment|/*&n; * The S390 can&squot;t do page protection for execute, and considers that the&n; * same are read. Also, write permissions imply read permissions. This is&n; * the closest we can get..&n; */
multiline_comment|/*xwr*/
DECL|macro|__P000
mdefine_line|#define __P000  PAGE_NONE_PRIVATE
DECL|macro|__P001
mdefine_line|#define __P001  PAGE_RO_PRIVATE
DECL|macro|__P010
mdefine_line|#define __P010  PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011  PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100  PAGE_RO_PRIVATE
DECL|macro|__P101
mdefine_line|#define __P101  PAGE_RO_PRIVATE
DECL|macro|__P110
mdefine_line|#define __P110  PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111  PAGE_COPY
DECL|macro|__S000
mdefine_line|#define __S000  PAGE_NONE_SHARED
DECL|macro|__S001
mdefine_line|#define __S001  PAGE_RO_SHARED
DECL|macro|__S010
mdefine_line|#define __S010  PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011  PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100  PAGE_RO_SHARED
DECL|macro|__S101
mdefine_line|#define __S101  PAGE_RO_SHARED
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
id|_PAGE_MKCLEAN
op_or
id|_PAGE_INVALID
)paren
)paren
op_eq
id|_PAGE_MKCLEAN
)paren
(brace
id|pte_val
c_func
(paren
id|pteval
)paren
op_and_assign
op_complement
id|_PAGE_MKCLEAN
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
l_int|1
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
op_amp
(paren
op_complement
id|PAGE_MASK
op_amp
op_complement
id|_PAGE_TABLE_INV
)paren
)paren
op_ne
id|_PAGE_TABLE
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
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_ISCLEAN
)paren
r_return
l_int|0
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
multiline_comment|/*&n; * The following pte modification functions only work if&n; * pte_present() is true. Undefined behaviour if not..&n; */
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
op_and_assign
id|PAGE_MASK
op_or
id|_PAGE_ISCLEAN
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|pgprot_val
c_func
(paren
id|newprot
)paren
op_amp
op_complement
id|_PAGE_ISCLEAN
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
multiline_comment|/* We do not explicitly set the dirty bit because the&n;&t; * sske instruction is slow. It is faster to let the&n;&t; * next instruction set the dirty bit.&n;&t; */
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
(paren
id|_PAGE_MKCLEAN
op_or
id|_PAGE_ISCLEAN
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
r_if
c_cond
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
id|_PAGE_ISCLEAN
)paren
r_return
l_int|0
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
r_static
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
mdefine_line|#define mk_pte(pg, pgprot)                                                &bslash;&n;({                                                                        &bslash;&n;&t;struct page *__page = (pg);                                       &bslash;&n;&t;pgprot_t __pgprot = (pgprot);&t;&t;&t;&t;&t;  &bslash;&n;&t;unsigned long __physpage = __pa((__page-mem_map) &lt;&lt; PAGE_SHIFT);  &bslash;&n;&t;pte_t __pte = mk_pte_phys(__physpage, __pgprot);                  &bslash;&n;&t;                                                                  &bslash;&n;&t;if (!(pgprot_val(__pgprot) &amp; _PAGE_ISCLEAN)) {&t;&t;&t;  &bslash;&n;&t;&t;int __users = !!PagePrivate(__page) + !!__page-&gt;mapping;  &bslash;&n;&t;&t;if (__users + page_count(__page) == 1)                    &bslash;&n;&t;&t;&t;pte_val(__pte) |= _PAGE_MKCLEAN;                  &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;__pte;                                                            &bslash;&n;})
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, pgprot)                                              &bslash;&n;({                                                                        &bslash;&n;&t;struct page *__page = mem_map+(pfn);                              &bslash;&n;&t;pgprot_t __pgprot = (pgprot);&t;&t;&t;&t;&t;  &bslash;&n;&t;unsigned long __physpage = __pa((pfn) &lt;&lt; PAGE_SHIFT);             &bslash;&n;&t;pte_t __pte = mk_pte_phys(__physpage, __pgprot);                  &bslash;&n;&t;                                                                  &bslash;&n;&t;if (!(pgprot_val(__pgprot) &amp; _PAGE_ISCLEAN)) {&t;&t;&t;  &bslash;&n;&t;&t;int __users = !!PagePrivate(__page) + !!__page-&gt;mapping;  &bslash;&n;&t;&t;if (__users + page_count(__page) == 1)                    &bslash;&n;&t;&t;&t;pte_val(__pte) |= _PAGE_MKCLEAN;                  &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;__pte;                                                            &bslash;&n;})
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x) (pte_val(x) &gt;&gt; PAGE_SHIFT)
DECL|macro|pte_page
mdefine_line|#define pte_page(x) pfn_to_page(pte_pfn(x))
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd) (pmd_val(pmd) &amp; PAGE_MASK)
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) (mem_map+(pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
DECL|macro|pgd_page_kernel
mdefine_line|#define pgd_page_kernel(pgd) (pgd_val(pgd) &amp; PAGE_MASK)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) ((address &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD-1))
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
DECL|macro|__pte_offset
mdefine_line|#define __pte_offset(address) (((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE-1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(pmd, address) &bslash;&n;&t;((pte_t *) pmd_page_kernel(*(pmd)) + __pte_offset(address))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(pmd, address) pte_offset_kernel(pmd, address)
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(pmd, address) pte_offset_kernel(pmd, address)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) do { } while (0)
multiline_comment|/*&n; * A page-table entry has some bits we have to treat in a special way.&n; * Bits 0, 20 and bit 23 have to be zero, otherwise an specification&n; * exception will occur instead of a page translation exception. The&n; * specifiation exception has the bad habit not to store necessary&n; * information in the lowcore.&n; * Bit 21 and bit 22 are the page invalid bit and the page protection&n; * bit. We set both to indicate a swapped page.&n; * Bit 31 is used as the software page present bit. If a page is&n; * swapped this obviously has to be zero.&n; * This leaves the bits 1-19 and bits 24-30 to store type and offset.&n; * We use the 7 bits from 24-30 for the type and the 19 bits from 1-19&n; * for the offset.&n; * 0|     offset      |0110|type |0&n; * 00000000001111111111222222222233&n; * 01234567890123456789012345678901&n; */
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
l_int|0x7ffff6fe
suffix:semicolon
multiline_comment|/* better to be paranoid */
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|__swp_type
mdefine_line|#define __swp_type(entry)&t;(((entry).val &gt;&gt; 1) &amp; 0x3f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(entry)&t;(((entry).val &gt;&gt; 12) &amp; 0x7FFFF )
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type,offset) ((swp_entry_t) { pte_val(mk_swap_pte((type),(offset))) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val })
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)   (1)
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
macro_line|#endif /* _S390_PAGE_H */
eof
