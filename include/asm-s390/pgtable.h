multiline_comment|/*&n; *  include/asm-s390/pgtable.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com)&n; *               Ulrich Weigand (weigand@de.ibm.com)&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/pgtable.h&quot;&n; */
macro_line|#ifndef _ASM_S390_PGTABLE_H
DECL|macro|_ASM_S390_PGTABLE_H
mdefine_line|#define _ASM_S390_PGTABLE_H
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
multiline_comment|/*&n; * The Linux memory management assumes a three-level page table setup. For&n; * s390 31 bit we &quot;fold&quot; the mid level into the top-level page table, so&n; * that we physically have the same two-level page table as the s390 mmu&n; * expects in 31 bit mode. For s390 64 bit we use three of the five levels&n; * the hardware provides (region first and region second tables are not&n; * used).&n; *&n; * The &quot;pgd_xxx()&quot; functions are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; *&n; * This file contains the functions and defines necessary to modify and use&n; * the S390 page table tree.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/bug.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
r_struct
id|vm_area_struct
suffix:semicolon
multiline_comment|/* forward declaration (include/linux/mm.h) */
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
multiline_comment|/*&n; * PMD_SHIFT determines the size of the area a second-level page&n; * table can map&n; * PGDIR_SHIFT determines what a third-level page table entry can map&n; */
macro_line|#ifndef __s390x__
DECL|macro|PMD_SHIFT
macro_line|# define PMD_SHIFT&t;22
DECL|macro|PGDIR_SHIFT
macro_line|# define PGDIR_SHIFT&t;22
macro_line|#else /* __s390x__ */
DECL|macro|PMD_SHIFT
macro_line|# define PMD_SHIFT&t;21
DECL|macro|PGDIR_SHIFT
macro_line|# define PGDIR_SHIFT&t;31
macro_line|#endif /* __s390x__ */
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE        (1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK        (~(PMD_SIZE-1))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE      (1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK      (~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: the S390 is two-level, so&n; * we don&squot;t really have any PMD directory physically.&n; * for S390 segment-table entries are combined to one PGD&n; * that leads to 1024 pte per pgd&n; */
macro_line|#ifndef __s390x__
DECL|macro|PTRS_PER_PTE
macro_line|# define PTRS_PER_PTE    1024
DECL|macro|PTRS_PER_PMD
macro_line|# define PTRS_PER_PMD    1
DECL|macro|PTRS_PER_PGD
macro_line|# define PTRS_PER_PGD    512
macro_line|#else /* __s390x__ */
DECL|macro|PTRS_PER_PTE
macro_line|# define PTRS_PER_PTE    512
DECL|macro|PTRS_PER_PMD
macro_line|# define PTRS_PER_PMD    1024
DECL|macro|PTRS_PER_PGD
macro_line|# define PTRS_PER_PGD    2048
macro_line|#endif /* __s390x__ */
multiline_comment|/*&n; * pgd entries used up by user/kernel:&n; */
macro_line|#ifndef __s390x__
DECL|macro|USER_PTRS_PER_PGD
macro_line|# define USER_PTRS_PER_PGD  512
DECL|macro|USER_PGD_PTRS
macro_line|# define USER_PGD_PTRS      512
DECL|macro|KERNEL_PGD_PTRS
macro_line|# define KERNEL_PGD_PTRS    512
DECL|macro|FIRST_USER_PGD_NR
macro_line|# define FIRST_USER_PGD_NR  0
macro_line|#else /* __s390x__ */
DECL|macro|USER_PTRS_PER_PGD
macro_line|# define USER_PTRS_PER_PGD  2048
DECL|macro|USER_PGD_PTRS
macro_line|# define USER_PGD_PTRS      2048
DECL|macro|KERNEL_PGD_PTRS
macro_line|# define KERNEL_PGD_PTRS    2048
DECL|macro|FIRST_USER_PGD_NR
macro_line|# define FIRST_USER_PGD_NR  0
macro_line|#endif /* __s390x__ */
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %p.&bslash;n&quot;, __FILE__, __LINE__, (void *) pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %p.&bslash;n&quot;, __FILE__, __LINE__, (void *) pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %p.&bslash;n&quot;, __FILE__, __LINE__, (void *) pgd_val(e))
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET  (8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START   (((unsigned long) high_memory + VMALLOC_OFFSET) &bslash;&n;&t;&t;&t; &amp; ~(VMALLOC_OFFSET-1))
macro_line|#ifndef __s390x__
DECL|macro|VMALLOC_END
macro_line|# define VMALLOC_END     (0x7fffffffL)
macro_line|#else /* __s390x__ */
DECL|macro|VMALLOC_END
macro_line|# define VMALLOC_END     (0x40000000000L)
macro_line|#endif /* __s390x__ */
multiline_comment|/*&n; * A 31 bit pagetable entry of S390 has following format:&n; *  |   PFRA          |    |  OS  |&n; * 0                   0IP0&n; * 00000000001111111111222222222233&n; * 01234567890123456789012345678901&n; *&n; * I Page-Invalid Bit:    Page is not available for address-translation&n; * P Page-Protection Bit: Store access not possible for page&n; *&n; * A 31 bit segmenttable entry of S390 has following format:&n; *  |   P-table origin      |  |PTL&n; * 0                         IC&n; * 00000000001111111111222222222233&n; * 01234567890123456789012345678901&n; *&n; * I Segment-Invalid Bit:    Segment is not available for address-translation&n; * C Common-Segment Bit:     Segment is not private (PoP 3-30)&n; * PTL Page-Table-Length:    Page-table length (PTL+1*16 entries -&gt; up to 256)&n; *&n; * The 31 bit segmenttable origin of S390 has following format:&n; *&n; *  |S-table origin   |     | STL |&n; * X                   **GPS&n; * 00000000001111111111222222222233&n; * 01234567890123456789012345678901&n; *&n; * X Space-Switch event:&n; * G Segment-Invalid Bit:     *&n; * P Private-Space Bit:       Segment is not private (PoP 3-30)&n; * S Storage-Alteration:&n; * STL Segment-Table-Length:  Segment-table length (STL+1*16 entries -&gt; up to 2048)&n; *&n; * A 64 bit pagetable entry of S390 has following format:&n; * |                     PFRA                         |0IP0|  OS  |&n; * 0000000000111111111122222222223333333333444444444455555555556666&n; * 0123456789012345678901234567890123456789012345678901234567890123&n; *&n; * I Page-Invalid Bit:    Page is not available for address-translation&n; * P Page-Protection Bit: Store access not possible for page&n; *&n; * A 64 bit segmenttable entry of S390 has following format:&n; * |        P-table origin                              |      TT&n; * 0000000000111111111122222222223333333333444444444455555555556666&n; * 0123456789012345678901234567890123456789012345678901234567890123&n; *&n; * I Segment-Invalid Bit:    Segment is not available for address-translation&n; * C Common-Segment Bit:     Segment is not private (PoP 3-30)&n; * P Page-Protection Bit: Store access not possible for page&n; * TT Type 00&n; *&n; * A 64 bit region table entry of S390 has following format:&n; * |        S-table origin                             |   TF  TTTL&n; * 0000000000111111111122222222223333333333444444444455555555556666&n; * 0123456789012345678901234567890123456789012345678901234567890123&n; *&n; * I Segment-Invalid Bit:    Segment is not available for address-translation&n; * TT Type 01&n; * TF&n; * TL Table lenght&n; *&n; * The 64 bit regiontable origin of S390 has following format:&n; * |      region table origon                          |       DTTL&n; * 0000000000111111111122222222223333333333444444444455555555556666&n; * 0123456789012345678901234567890123456789012345678901234567890123&n; *&n; * X Space-Switch event:&n; * G Segment-Invalid Bit:  &n; * P Private-Space Bit:    &n; * S Storage-Alteration:&n; * R Real space&n; * TL Table-Length:&n; *&n; * A storage key has the following format:&n; * | ACC |F|R|C|0|&n; *  0   3 4 5 6 7&n; * ACC: access key&n; * F  : fetch protection bit&n; * R  : referenced bit&n; * C  : changed bit&n; */
multiline_comment|/* Hardware bits in the page table entry */
DECL|macro|_PAGE_RO
mdefine_line|#define _PAGE_RO        0x200          /* HW read-only                     */
DECL|macro|_PAGE_INVALID
mdefine_line|#define _PAGE_INVALID   0x400          /* HW invalid                       */
multiline_comment|/* Mask and four different kinds of invalid pages. */
DECL|macro|_PAGE_INVALID_MASK
mdefine_line|#define _PAGE_INVALID_MASK&t;0x601
DECL|macro|_PAGE_INVALID_EMPTY
mdefine_line|#define _PAGE_INVALID_EMPTY&t;0x400
DECL|macro|_PAGE_INVALID_NONE
mdefine_line|#define _PAGE_INVALID_NONE&t;0x401
DECL|macro|_PAGE_INVALID_SWAP
mdefine_line|#define _PAGE_INVALID_SWAP&t;0x600
DECL|macro|_PAGE_INVALID_FILE
mdefine_line|#define _PAGE_INVALID_FILE&t;0x601
macro_line|#ifndef __s390x__
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
mdefine_line|#define _PAGE_TABLE&t;_PAGE_TABLE_LEN
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE&t;_PAGE_TABLE_LEN
multiline_comment|/*&n; * The Kernel segment-tables includes the User segment-table&n; */
DECL|macro|_SEGMENT_TABLE
mdefine_line|#define _SEGMENT_TABLE&t;(_USER_SEG_TABLE_LEN|0x80000000|0x100)
DECL|macro|_KERNSEG_TABLE
mdefine_line|#define _KERNSEG_TABLE&t;_KERNEL_SEG_TABLE_LEN
DECL|macro|USER_STD_MASK
mdefine_line|#define USER_STD_MASK&t;0x00000080UL
macro_line|#else /* __s390x__ */
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
DECL|macro|USER_STD_MASK
mdefine_line|#define USER_STD_MASK           0x0000000000000080UL
multiline_comment|/* Bits in the storage key */
DECL|macro|_PAGE_CHANGED
mdefine_line|#define _PAGE_CHANGED    0x02          /* HW changed bit                   */
DECL|macro|_PAGE_REFERENCED
mdefine_line|#define _PAGE_REFERENCED 0x04          /* HW referenced bit                */
macro_line|#endif /* __s390x__ */
multiline_comment|/*&n; * No mapping available&n; */
DECL|macro|PAGE_NONE_SHARED
mdefine_line|#define PAGE_NONE_SHARED  __pgprot(_PAGE_INVALID_NONE)
DECL|macro|PAGE_NONE_PRIVATE
mdefine_line|#define PAGE_NONE_PRIVATE __pgprot(_PAGE_INVALID_NONE)
DECL|macro|PAGE_RO_SHARED
mdefine_line|#define PAGE_RO_SHARED&t;  __pgprot(_PAGE_RO)
DECL|macro|PAGE_RO_PRIVATE
mdefine_line|#define PAGE_RO_PRIVATE&t;  __pgprot(_PAGE_RO)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;  __pgprot(_PAGE_RO)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;  __pgprot(0)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;  __pgprot(0)
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
op_star
id|pteptr
op_assign
id|pteval
suffix:semicolon
)brace
multiline_comment|/*&n; * pgd/pmd/pte query functions&n; */
macro_line|#ifndef __s390x__
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
macro_line|#else /* __s390x__ */
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
macro_line|#endif /* __s390x__ */
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_INVALID_MASK
)paren
op_eq
id|_PAGE_INVALID_EMPTY
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
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_INVALID
)paren
op_logical_or
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_INVALID_MASK
)paren
op_eq
id|_PAGE_INVALID_NONE
suffix:semicolon
)brace
DECL|function|pte_file
r_extern
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
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_INVALID_MASK
)paren
op_eq
id|_PAGE_INVALID_FILE
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
multiline_comment|/* A pte is neither clean nor dirty on s/390. The dirty bit&n;&t; * is in the storage key. See page_test_and_clear_dirty for&n;&t; * details.&n;&t; */
r_return
l_int|0
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
multiline_comment|/* A pte is neither young nor old on s/390. The young bit&n;&t; * is in the storage key. See page_test_and_clear_young for&n;&t; * details.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * pgd/pmd/pte modification functions&n; */
macro_line|#ifndef __s390x__
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
macro_line|#else /* __s390x__ */
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
macro_line|#endif /* __s390x__ */
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
id|_PAGE_INVALID_EMPTY
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
multiline_comment|/* Do not clobber _PAGE_INVALID_NONE pages!  */
r_if
c_cond
(paren
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_INVALID
)paren
)paren
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
multiline_comment|/* S/390 doesn&squot;t keep its dirty/referenced bit in the pte.&n;&t; * There is no point in clearing the real referenced bit.&n;&t; */
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
multiline_comment|/* S/390 doesn&squot;t keep its dirty/referenced bit in the pte.&n;&t; * There is no point in setting the real referenced bit.&n;&t; */
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
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|ptep_clear_flush_young
id|ptep_clear_flush_young
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
op_star
id|ptep
)paren
(brace
multiline_comment|/* No need to flush TLB; bits are in storage key */
r_return
id|ptep_test_and_clear_young
c_func
(paren
id|ptep
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|ptep_clear_flush_dirty
id|ptep_clear_flush_dirty
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
op_star
id|ptep
)paren
(brace
multiline_comment|/* No need to flush TLB; bits are in storage key */
r_return
id|ptep_test_and_clear_dirty
c_func
(paren
id|ptep
)paren
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
r_static
r_inline
id|pte_t
DECL|function|ptep_clear_flush
id|ptep_clear_flush
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
macro_line|#ifndef __s390x__
r_if
c_cond
(paren
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_INVALID
)paren
)paren
(brace
multiline_comment|/* S390 has 1mb segments, we are emulating 4MB segments */
id|pte_t
op_star
id|pto
op_assign
(paren
id|pte_t
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|ptep
)paren
op_amp
l_int|0x7ffffc00
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;ipte %2,%3&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|ptep
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|ptep
)paren
comma
l_string|&quot;a&quot;
(paren
id|pto
)paren
comma
l_string|&quot;a&quot;
(paren
id|address
)paren
)paren
suffix:semicolon
)brace
macro_line|#else /* __s390x__ */
r_if
c_cond
(paren
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_INVALID
)paren
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;ipte %2,%3&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|ptep
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|ptep
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptep
)paren
comma
l_string|&quot;a&quot;
(paren
id|address
)paren
)paren
suffix:semicolon
macro_line|#endif /* __s390x__ */
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
r_static
r_inline
r_void
DECL|function|ptep_establish
id|ptep_establish
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
op_star
id|ptep
comma
id|pte_t
id|entry
)paren
(brace
id|ptep_clear_flush
c_func
(paren
id|vma
comma
id|address
comma
id|ptep
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|entry
)paren
suffix:semicolon
)brace
DECL|macro|ptep_set_access_flags
mdefine_line|#define ptep_set_access_flags(__vma, __address, __ptep, __entry, __dirty) &bslash;&n;&t;ptep_establish(__vma, __address, __ptep, __entry)
multiline_comment|/*&n; * Test and clear dirty bit in storage key.&n; * We can&squot;t clear the changed bit atomically. This is a potential&n; * race against modification of the referenced bit. This function&n; * should therefore only be called if it is not mapped in any&n; * address space.&n; */
DECL|macro|page_test_and_clear_dirty
mdefine_line|#define page_test_and_clear_dirty(_page)&t;&t;&t;&t;  &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;struct page *__page = (_page);&t;&t;&t;&t;&t;  &bslash;&n;&t;unsigned long __physpage = __pa((__page-mem_map) &lt;&lt; PAGE_SHIFT);  &bslash;&n;&t;int __skey = page_get_storage_key(__physpage);&t;&t;&t;  &bslash;&n;&t;if (__skey &amp; _PAGE_CHANGED)&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;page_set_storage_key(__physpage, __skey &amp; ~_PAGE_CHANGED);&bslash;&n;&t;(__skey &amp; _PAGE_CHANGED);&t;&t;&t;&t;&t;  &bslash;&n;})
multiline_comment|/*&n; * Test and clear referenced bit in storage key.&n; */
DECL|macro|page_test_and_clear_young
mdefine_line|#define page_test_and_clear_young(page)&t;&t;&t;&t;&t;  &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;struct page *__page = (page);&t;&t;&t;&t;&t;  &bslash;&n;&t;unsigned long __physpage = __pa((__page-mem_map) &lt;&lt; PAGE_SHIFT);  &bslash;&n;&t;int __ccode;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;asm volatile (&quot;rrbe 0,%1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;      &quot;ipm  %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;      &quot;srl  %0,28&bslash;n&bslash;t&quot; &t;&t;&t;&t;&t;  &bslash;&n;                      : &quot;=d&quot; (__ccode) : &quot;a&quot; (__physpage) : &quot;cc&quot; );&t;  &bslash;&n;&t;(__ccode &amp; 2);&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;})
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
mdefine_line|#define mk_pte(pg, pgprot)                                                &bslash;&n;({                                                                        &bslash;&n;&t;struct page *__page = (pg);                                       &bslash;&n;&t;pgprot_t __pgprot = (pgprot);&t;&t;&t;&t;&t;  &bslash;&n;&t;unsigned long __physpage = __pa((__page-mem_map) &lt;&lt; PAGE_SHIFT);  &bslash;&n;&t;pte_t __pte = mk_pte_phys(__physpage, __pgprot);                  &bslash;&n;&t;__pte;                                                            &bslash;&n;})
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, pgprot)                                              &bslash;&n;({                                                                        &bslash;&n;&t;pgprot_t __pgprot = (pgprot);&t;&t;&t;&t;&t;  &bslash;&n;&t;unsigned long __physpage = __pa((pfn) &lt;&lt; PAGE_SHIFT);             &bslash;&n;&t;pte_t __pte = mk_pte_phys(__physpage, __pgprot);                  &bslash;&n;&t;__pte;                                                            &bslash;&n;})
DECL|macro|SetPageUptodate
mdefine_line|#define SetPageUptodate(_page) &bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;struct page *__page = (_page);&t;&t;&t;&t;      &bslash;&n;&t;&t;if (!test_and_set_bit(PG_uptodate, &amp;__page-&gt;flags))&t;      &bslash;&n;&t;&t;&t;page_test_and_clear_dirty(_page);&t;&t;      &bslash;&n;&t;} while (0)
macro_line|#ifdef __s390x__
DECL|macro|pfn_pmd
mdefine_line|#define pfn_pmd(pfn, pgprot)                                              &bslash;&n;({                                                                        &bslash;&n;&t;pgprot_t __pgprot = (pgprot);                                     &bslash;&n;&t;unsigned long __physpage = __pa((pfn) &lt;&lt; PAGE_SHIFT);             &bslash;&n;&t;pmd_t __pmd = __pmd(__physpage + pgprot_val(__pgprot));           &bslash;&n;&t;__pmd;                                                            &bslash;&n;})
macro_line|#endif /* __s390x__ */
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
macro_line|#ifndef __s390x__
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
macro_line|#else /* __s390x__ */
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_index
mdefine_line|#define pmd_index(address) (((address) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD-1))
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir,addr) &bslash;&n;&t;((pmd_t *) pgd_page_kernel(*(dir)) + pmd_index(addr))
macro_line|#endif /* __s390x__ */
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|pte_index
mdefine_line|#define pte_index(address) (((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE-1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(pmd, address) &bslash;&n;&t;((pte_t *) pmd_page_kernel(*(pmd)) + pte_index(address))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(pmd, address) pte_offset_kernel(pmd, address)
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(pmd, address) pte_offset_kernel(pmd, address)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) do { } while (0)
multiline_comment|/*&n; * 31 bit swap entry format:&n; * A page-table entry has some bits we have to treat in a special way.&n; * Bits 0, 20 and bit 23 have to be zero, otherwise an specification&n; * exception will occur instead of a page translation exception. The&n; * specifiation exception has the bad habit not to store necessary&n; * information in the lowcore.&n; * Bit 21 and bit 22 are the page invalid bit and the page protection&n; * bit. We set both to indicate a swapped page.&n; * Bit 30 and 31 are used to distinguish the different page types. For&n; * a swapped page these bits need to be zero.&n; * This leaves the bits 1-19 and bits 24-29 to store type and offset.&n; * We use the 5 bits from 25-29 for the type and the 20 bits from 1-19&n; * plus 24 for the offset.&n; * 0|     offset        |0110|o|type |00|&n; * 0 0000000001111111111 2222 2 22222 33&n; * 0 1234567890123456789 0123 4 56789 01&n; *&n; * 64 bit swap entry format:&n; * A page-table entry has some bits we have to treat in a special way.&n; * Bits 52 and bit 55 have to be zero, otherwise an specification&n; * exception will occur instead of a page translation exception. The&n; * specifiation exception has the bad habit not to store necessary&n; * information in the lowcore.&n; * Bit 53 and bit 54 are the page invalid bit and the page protection&n; * bit. We set both to indicate a swapped page.&n; * Bit 62 and 63 are used to distinguish the different page types. For&n; * a swapped page these bits need to be zero.&n; * This leaves the bits 0-51 and bits 56-61 to store type and offset.&n; * We use the 5 bits from 57-61 for the type and the 53 bits from 0-51&n; * plus 56 for the offset.&n; * |                      offset                        |0110|o|type |00|&n; *  0000000000111111111122222222223333333333444444444455 5555 5 55566 66&n; *  0123456789012345678901234567890123456789012345678901 2345 6 78901 23&n; */
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
id|_PAGE_INVALID_SWAP
op_or
(paren
(paren
id|type
op_amp
l_int|0x1f
)paren
op_lshift
l_int|2
)paren
op_or
(paren
(paren
id|offset
op_amp
l_int|1
)paren
op_lshift
l_int|7
)paren
op_or
(paren
(paren
id|offset
op_amp
l_int|0xffffe
)paren
op_lshift
l_int|11
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|__swp_type
mdefine_line|#define __swp_type(entry)&t;(((entry).val &gt;&gt; 2) &amp; 0x1f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(entry)&t;(((entry).val &gt;&gt; 11) | (((entry).val &gt;&gt; 7) &amp; 1))
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type,offset) ((swp_entry_t) { pte_val(mk_swap_pte((type),(offset))) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val })
macro_line|#ifndef __s390x__
DECL|macro|PTE_FILE_MAX_BITS
macro_line|# define PTE_FILE_MAX_BITS&t;26
macro_line|#else /* __s390x__ */
DECL|macro|PTE_FILE_MAX_BITS
macro_line|# define PTE_FILE_MAX_BITS&t;59
macro_line|#endif /* __s390x__ */
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(__pte) &bslash;&n;&t;((((__pte).pte &gt;&gt; 12) &lt;&lt; 7) + (((__pte).pte &gt;&gt; 1) &amp; 0x7f))
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(__off) &bslash;&n;&t;((pte_t) { ((((__off) &amp; 0x7f) &lt;&lt; 1) + (((__off) &gt;&gt; 7) &lt;&lt; 12)) &bslash;&n;&t;&t;   | _PAGE_INVALID_FILE })
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)   (1)
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
DECL|macro|__HAVE_ARCH_PTEP_ESTABLISH
mdefine_line|#define __HAVE_ARCH_PTEP_ESTABLISH
DECL|macro|__HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
mdefine_line|#define __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
DECL|macro|__HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
mdefine_line|#define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
DECL|macro|__HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
mdefine_line|#define __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
DECL|macro|__HAVE_ARCH_PTEP_TEST_AND_CLEAR_DIRTY
mdefine_line|#define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_DIRTY
DECL|macro|__HAVE_ARCH_PTEP_CLEAR_DIRTY_FLUSH
mdefine_line|#define __HAVE_ARCH_PTEP_CLEAR_DIRTY_FLUSH
DECL|macro|__HAVE_ARCH_PTEP_GET_AND_CLEAR
mdefine_line|#define __HAVE_ARCH_PTEP_GET_AND_CLEAR
DECL|macro|__HAVE_ARCH_PTEP_CLEAR_FLUSH
mdefine_line|#define __HAVE_ARCH_PTEP_CLEAR_FLUSH
DECL|macro|__HAVE_ARCH_PTEP_SET_WRPROTECT
mdefine_line|#define __HAVE_ARCH_PTEP_SET_WRPROTECT
DECL|macro|__HAVE_ARCH_PTEP_MKDIRTY
mdefine_line|#define __HAVE_ARCH_PTEP_MKDIRTY
DECL|macro|__HAVE_ARCH_PTE_SAME
mdefine_line|#define __HAVE_ARCH_PTE_SAME
DECL|macro|__HAVE_ARCH_PAGE_TEST_AND_CLEAR_DIRTY
mdefine_line|#define __HAVE_ARCH_PAGE_TEST_AND_CLEAR_DIRTY
DECL|macro|__HAVE_ARCH_PAGE_TEST_AND_CLEAR_YOUNG
mdefine_line|#define __HAVE_ARCH_PAGE_TEST_AND_CLEAR_YOUNG
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#endif /* _S390_PAGE_H */
eof
