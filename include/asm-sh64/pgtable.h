macro_line|#ifndef __ASM_SH64_PGTABLE_H
DECL|macro|__ASM_SH64_PGTABLE_H
mdefine_line|#define __ASM_SH64_PGTABLE_H
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/pgtable.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003, 2004  Paul Mundt&n; * Copyright (C) 2003, 2004  Richard Curnow&n; *&n; * This file contains the functions and defines necessary to modify and use&n; * the SuperH page table tree.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/config.h&gt;
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* We provide our own get_unmapped_area to avoid cache synonym issue */
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
multiline_comment|/*&n; * Basically we have the same two-level (which is the logical three level&n; * Linux page table layout folded) page tables as the i386.&n; */
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_int
r_char
id|empty_zero_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (mem_map + MAP_NR(empty_zero_page))
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * NEFF and NPHYS related defines.&n; * FIXME : These need to be model-dependent.  For now this is OK, SH5-101 and SH5-103&n; * implement 32 bits effective and 32 bits physical.  But future implementations may&n; * extend beyond this.&n; */
DECL|macro|NEFF
mdefine_line|#define NEFF&t;&t;32
DECL|macro|NEFF_SIGN
mdefine_line|#define&t;NEFF_SIGN&t;(1LL &lt;&lt; (NEFF - 1))
DECL|macro|NEFF_MASK
mdefine_line|#define&t;NEFF_MASK&t;(-1LL &lt;&lt; NEFF)
DECL|macro|NPHYS
mdefine_line|#define NPHYS&t;&t;32
DECL|macro|NPHYS_SIGN
mdefine_line|#define&t;NPHYS_SIGN&t;(1LL &lt;&lt; (NPHYS - 1))
DECL|macro|NPHYS_MASK
mdefine_line|#define&t;NPHYS_MASK&t;(-1LL &lt;&lt; NPHYS)
multiline_comment|/* Typically 2-level is sufficient up to 32 bits of virtual address space, beyond&n;   that 3-level would be appropriate. */
macro_line|#if defined(CONFIG_SH64_PGTABLE_2_LEVEL)
multiline_comment|/* For 4k pages, this contains 512 entries, i.e. 9 bits worth of address. */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;((1&lt;&lt;PAGE_SHIFT)/sizeof(unsigned long long))
DECL|macro|PTE_MAGNITUDE
mdefine_line|#define PTE_MAGNITUDE&t;3&t;      /* sizeof(unsigned long long) magnit. */
DECL|macro|PTE_SHIFT
mdefine_line|#define PTE_SHIFT&t;PAGE_SHIFT
DECL|macro|PTE_BITS
mdefine_line|#define PTE_BITS&t;(PAGE_SHIFT - PTE_MAGNITUDE)
multiline_comment|/* top level: PMD. */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;(PTE_SHIFT + PTE_BITS)
DECL|macro|PGD_BITS
mdefine_line|#define PGD_BITS&t;(NEFF - PGDIR_SHIFT)
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;(1&lt;&lt;PGD_BITS)
multiline_comment|/* middle level: PMD. This doesn&squot;t do anything for the 2-level case. */
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;(1)
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;PGDIR_SHIFT
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;PGDIR_SIZE
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;PGDIR_MASK
macro_line|#elif defined(CONFIG_SH64_PGTABLE_3_LEVEL)
multiline_comment|/*&n; * three-level asymmetric paging structure: PGD is top level.&n; * The asymmetry comes from 32-bit pointers and 64-bit PTEs.&n; */
multiline_comment|/* bottom level: PTE. It&squot;s 9 bits = 512 pointers */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;((1&lt;&lt;PAGE_SHIFT)/sizeof(unsigned long long))
DECL|macro|PTE_MAGNITUDE
mdefine_line|#define PTE_MAGNITUDE&t;3&t;      /* sizeof(unsigned long long) magnit. */
DECL|macro|PTE_SHIFT
mdefine_line|#define PTE_SHIFT&t;PAGE_SHIFT
DECL|macro|PTE_BITS
mdefine_line|#define PTE_BITS&t;(PAGE_SHIFT - PTE_MAGNITUDE)
multiline_comment|/* middle level: PMD. It&squot;s 10 bits = 1024 pointers */
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;((1&lt;&lt;PAGE_SHIFT)/sizeof(unsigned long long *))
DECL|macro|PMD_MAGNITUDE
mdefine_line|#define PMD_MAGNITUDE&t;2&t;      /* sizeof(unsigned long long *) magnit. */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;(PTE_SHIFT + PTE_BITS)
DECL|macro|PMD_BITS
mdefine_line|#define PMD_BITS&t;(PAGE_SHIFT - PMD_MAGNITUDE)
multiline_comment|/* top level: PMD. It&squot;s 1 bit = 2 pointers */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;(PMD_SHIFT + PMD_BITS)
DECL|macro|PGD_BITS
mdefine_line|#define PGD_BITS&t;(NEFF - PGDIR_SHIFT)
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;(1&lt;&lt;PGD_BITS)
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
macro_line|#else
macro_line|#error &quot;No defined number of page table levels&quot;
macro_line|#endif
multiline_comment|/*&n; * Error outputs.&n; */
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %016Lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
multiline_comment|/*&n; * Table setting routines. Used within arch/mm only.&n; */
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgdptr, pgdval) (*(pgdptr) = pgdval)
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdptr, pmdval) (*(pmdptr) = pmdval)
DECL|function|set_pte
r_static
id|__inline__
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
r_int
r_int
r_int
id|x
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|pteval.pte
)paren
suffix:semicolon
r_int
r_int
r_int
op_star
id|xp
op_assign
(paren
r_int
r_int
r_int
op_star
)paren
id|pteptr
suffix:semicolon
multiline_comment|/*&n;&t; * Sign-extend based on NPHYS.&n;&t; */
op_star
(paren
id|xp
)paren
op_assign
(paren
id|x
op_amp
id|NPHYS_SIGN
)paren
ques
c_cond
(paren
id|x
op_or
id|NPHYS_MASK
)paren
suffix:colon
id|x
suffix:semicolon
)brace
DECL|function|pmd_set
r_static
id|__inline__
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
(paren
r_int
r_int
)paren
id|ptep
suffix:semicolon
)brace
multiline_comment|/*&n; * PGD defines. Top level.&n; */
multiline_comment|/* To find an entry in a generic PGD. */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) (((address) &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD-1))
DECL|macro|__pgd_offset
mdefine_line|#define __pgd_offset(address) pgd_index(address)
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) ((mm)-&gt;pgd+pgd_index(address))
multiline_comment|/* To find an entry in a kernel PGD. */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/*&n; * PGD level access routines.&n; *&n; * Note1:&n; * There&squot;s no need to use physical addresses since the tree walk is all&n; * in performed in software, until the PTE translation.&n; *&n; * Note 2:&n; * A PGD entry can be uninitialized (_PGD_UNUSED), generically bad,&n; * clear (_PGD_EMPTY), present. When present, lower 3 nibbles contain&n; * _KERNPG_TABLE. Being a kernel virtual pointer also bit 31 must&n; * be 1. Assuming an arbitrary clear value of bit 31 set to 0 and&n; * lower 3 nibbles set to 0xFFF (_PGD_EMPTY) any other value is a&n; * bad pgd that must be notified via printk().&n; *&n; */
DECL|macro|_PGD_EMPTY
mdefine_line|#define _PGD_EMPTY&t;&t;0x0
macro_line|#if defined(CONFIG_SH64_PGTABLE_2_LEVEL)
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
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd) ((pgd_val(pgd) &amp; _PAGE_PRESENT) ? 1 : 0)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(xx)&t;&t;&t;&t;do { } while(0)
macro_line|#elif defined(CONFIG_SH64_PGTABLE_3_LEVEL)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd_entry)&t;(1)
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd_entry)&t;(pgd_val((pgd_entry)) == _PGD_EMPTY)
multiline_comment|/* TODO: Think later about what a useful definition of &squot;bad&squot; would be now. */
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd_entry)&t;(0)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgd_entry_p)&t;(set_pgd((pgd_entry_p), __pgd(_PGD_EMPTY)))
macro_line|#endif
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd_entry)&t;((unsigned long) (pgd_val(pgd_entry) &amp; PAGE_MASK))
multiline_comment|/*&n; * PMD defines. Middle level.&n; */
multiline_comment|/* PGD to PMD dereferencing */
macro_line|#if defined(CONFIG_SH64_PGTABLE_2_LEVEL)
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
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_SH64_PGTABLE_3_LEVEL)
DECL|macro|__pmd_offset
mdefine_line|#define __pmd_offset(address) &bslash;&n;&t;&t;(((address) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD-1))
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir, addr) &bslash;&n;&t;&t;((pmd_t *) ((pgd_val(*(dir))) &amp; PAGE_MASK) + __pmd_offset((addr)))
macro_line|#endif
multiline_comment|/*&n; * PMD level access routines. Same notes as above.&n; */
DECL|macro|_PMD_EMPTY
mdefine_line|#define _PMD_EMPTY&t;&t;0x0
multiline_comment|/* Either the PMD is empty or present, it&squot;s not paged out */
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd_entry)&t;(pmd_val(pmd_entry) &amp; _PAGE_PRESENT)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmd_entry_p)&t;(set_pmd((pmd_entry_p), __pmd(_PMD_EMPTY)))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd_entry)&t;(pmd_val((pmd_entry)) == _PMD_EMPTY)
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd_entry)&t;((pmd_val(pmd_entry) &amp; (~PAGE_MASK &amp; ~_PAGE_USER)) != _KERNPG_TABLE)
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd_entry) &bslash;&n;&t;((unsigned long) __va(pmd_val(pmd_entry) &amp; PAGE_MASK))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) &bslash;&n;&t;(virt_to_page(pmd_val(pmd)))
multiline_comment|/* PMD to PTE dereferencing */
DECL|macro|pte_index
mdefine_line|#define pte_index(address) &bslash;&n;&t;&t;((address &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, addr) &bslash;&n;&t;&t;((pte_t *) ((pmd_val(*(dir))) &amp; PAGE_MASK) + pte_index((addr)))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir,addr)&t;pte_offset_kernel(dir, addr)
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir,addr)&t;pte_offset_kernel(dir, addr)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte)&t;&t;do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte)&t;do { } while (0)
multiline_comment|/* Round it up ! */
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;((TASK_SIZE+PGDIR_SIZE-1)/PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
macro_line|#ifndef __ASSEMBLY__
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;0xff000000
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;0xf0000000
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|IOBASE_VADDR
mdefine_line|#define IOBASE_VADDR&t;0xff000000
DECL|macro|IOBASE_END
mdefine_line|#define IOBASE_END&t;0xffffffff
multiline_comment|/*&n; * PTEL coherent flags.&n; * See Chapter 17 ST50 CPU Core Volume 1, Architecture.&n; */
multiline_comment|/* The bits that are required in the SH-5 TLB are placed in the h/w-defined&n;   positions, to avoid expensive bit shuffling on every refill.  The remaining&n;   bits are used for s/w purposes and masked out on each refill.&n;&n;   Note, the PTE slots are used to hold data of type swp_entry_t when a page is&n;   swapped out.  Only the _PAGE_PRESENT flag is significant when the page is&n;   swapped out, and it must be placed so that it doesn&squot;t overlap either the&n;   type or offset fields of swp_entry_t.  For x86, offset is at [31:8] and type&n;   at [6:1], with _PAGE_PRESENT at bit 0 for both pte_t and swp_entry_t.  This&n;   scheme doesn&squot;t map to SH-5 because bit [0] controls cacheability.  So bit&n;   [2] is used for _PAGE_PRESENT and the type field of swp_entry_t is split&n;   into 2 pieces.  That is handled by SWP_ENTRY and SWP_TYPE below. */
DECL|macro|_PAGE_WT
mdefine_line|#define _PAGE_WT&t;0x001  /* CB0: if cacheable, 1-&gt;write-thru, 0-&gt;write-back */
DECL|macro|_PAGE_DEVICE
mdefine_line|#define _PAGE_DEVICE&t;0x001  /* CB0: if uncacheable, 1-&gt;device (i.e. no write-combining or reordering at bus level) */
DECL|macro|_PAGE_CACHABLE
mdefine_line|#define _PAGE_CACHABLE&t;0x002  /* CB1: uncachable/cachable */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x004  /* software: page referenced */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;0x004  /* software: only when !present */
DECL|macro|_PAGE_SIZE0
mdefine_line|#define _PAGE_SIZE0&t;0x008  /* SZ0-bit : size of page */
DECL|macro|_PAGE_SIZE1
mdefine_line|#define _PAGE_SIZE1&t;0x010  /* SZ1-bit : size of page */
DECL|macro|_PAGE_SHARED
mdefine_line|#define _PAGE_SHARED&t;0x020  /* software: reflects PTEH&squot;s SH */
DECL|macro|_PAGE_READ
mdefine_line|#define _PAGE_READ&t;0x040  /* PR0-bit : read access allowed */
DECL|macro|_PAGE_EXECUTE
mdefine_line|#define _PAGE_EXECUTE&t;0x080  /* PR1-bit : execute access allowed */
DECL|macro|_PAGE_WRITE
mdefine_line|#define _PAGE_WRITE&t;0x100  /* PR2-bit : write access allowed */
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x200  /* PR3-bit : user space access allowed */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x400  /* software: page accessed in write */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x800  /* software: page referenced */
multiline_comment|/* Mask which drops software flags */
DECL|macro|_PAGE_FLAGS_HARDWARE_MASK
mdefine_line|#define _PAGE_FLAGS_HARDWARE_MASK&t;0xfffffffffffff3dbLL
multiline_comment|/* Flags default: 4KB, Read, Not write, Not execute, Not user */
DECL|macro|_PAGE_FLAGS_HARDWARE_DEFAULT
mdefine_line|#define _PAGE_FLAGS_HARDWARE_DEFAULT&t;0x0000000000000040LL
multiline_comment|/*&n; * HugeTLB support&n; */
macro_line|#if defined(CONFIG_HUGETLB_PAGE_SIZE_64K)
DECL|macro|_PAGE_SZHUGE
mdefine_line|#define _PAGE_SZHUGE&t;(_PAGE_SIZE0)
macro_line|#elif defined(CONFIG_HUGETLB_PAGE_SIZE_1MB)
DECL|macro|_PAGE_SZHUGE
mdefine_line|#define _PAGE_SZHUGE&t;(_PAGE_SIZE1)
macro_line|#elif defined(CONFIG_HUGETLB_PAGE_SIZE_512MB)
DECL|macro|_PAGE_SZHUGE
mdefine_line|#define _PAGE_SZHUGE&t;(_PAGE_SIZE0 | _PAGE_SIZE1)
macro_line|#endif
multiline_comment|/*&n; * Default flags for a Kernel page.&n; * This is fundametally also SHARED because the main use of this define&n; * (other than for PGD/PMD entries) is for the VMALLOC pool which is&n; * contextless.&n; *&n; * _PAGE_EXECUTE is required for modules&n; *&n; */
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE&t;(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | &bslash;&n;&t;&t;&t; _PAGE_EXECUTE | &bslash;&n;&t;&t;&t; _PAGE_CACHABLE | _PAGE_ACCESSED | _PAGE_DIRTY | &bslash;&n;&t;&t;&t; _PAGE_SHARED)
multiline_comment|/* Default flags for a User page */
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_KERNPG_TABLE | _PAGE_USER)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PTE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_CACHABLE | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | &bslash;&n;&t;&t;&t;&t; _PAGE_CACHABLE | _PAGE_ACCESSED | _PAGE_USER | &bslash;&n;&t;&t;&t;&t; _PAGE_SHARED)
multiline_comment|/* We need to include PAGE_EXECUTE in PAGE_COPY because it is the default&n; * protection mode for the stack. */
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_CACHABLE | &bslash;&n;&t;&t;&t;&t; _PAGE_ACCESSED | _PAGE_USER | _PAGE_EXECUTE)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_CACHABLE | &bslash;&n;&t;&t;&t;&t; _PAGE_ACCESSED | _PAGE_USER)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_KERNPG_TABLE)
multiline_comment|/*&n; * In ST50 we have full permissions (Read/Write/Execute/Shared).&n; * Just match&squot;em all. These are for mmap(), therefore all at least&n; * User/Cachable/Present/Accessed. No point in making Fault on Write.&n; */
DECL|macro|__MMAP_COMMON
mdefine_line|#define __MMAP_COMMON&t;(_PAGE_PRESENT | _PAGE_USER | _PAGE_CACHABLE | _PAGE_ACCESSED)
multiline_comment|/* sxwr */
DECL|macro|__P000
mdefine_line|#define __P000&t;__pgprot(__MMAP_COMMON)
DECL|macro|__P001
mdefine_line|#define __P001&t;__pgprot(__MMAP_COMMON | _PAGE_READ)
DECL|macro|__P010
mdefine_line|#define __P010&t;__pgprot(__MMAP_COMMON)
DECL|macro|__P011
mdefine_line|#define __P011&t;__pgprot(__MMAP_COMMON | _PAGE_READ)
DECL|macro|__P100
mdefine_line|#define __P100&t;__pgprot(__MMAP_COMMON | _PAGE_EXECUTE)
DECL|macro|__P101
mdefine_line|#define __P101&t;__pgprot(__MMAP_COMMON | _PAGE_EXECUTE | _PAGE_READ)
DECL|macro|__P110
mdefine_line|#define __P110&t;__pgprot(__MMAP_COMMON | _PAGE_EXECUTE)
DECL|macro|__P111
mdefine_line|#define __P111&t;__pgprot(__MMAP_COMMON | _PAGE_EXECUTE | _PAGE_READ)
DECL|macro|__S000
mdefine_line|#define __S000&t;__pgprot(__MMAP_COMMON | _PAGE_SHARED)
DECL|macro|__S001
mdefine_line|#define __S001&t;__pgprot(__MMAP_COMMON | _PAGE_SHARED | _PAGE_READ)
DECL|macro|__S010
mdefine_line|#define __S010&t;__pgprot(__MMAP_COMMON | _PAGE_SHARED | _PAGE_WRITE)
DECL|macro|__S011
mdefine_line|#define __S011&t;__pgprot(__MMAP_COMMON | _PAGE_SHARED | _PAGE_READ | _PAGE_WRITE)
DECL|macro|__S100
mdefine_line|#define __S100&t;__pgprot(__MMAP_COMMON | _PAGE_SHARED | _PAGE_EXECUTE)
DECL|macro|__S101
mdefine_line|#define __S101&t;__pgprot(__MMAP_COMMON | _PAGE_SHARED | _PAGE_EXECUTE | _PAGE_READ)
DECL|macro|__S110
mdefine_line|#define __S110&t;__pgprot(__MMAP_COMMON | _PAGE_SHARED | _PAGE_EXECUTE | _PAGE_WRITE)
DECL|macro|__S111
mdefine_line|#define __S111&t;__pgprot(__MMAP_COMMON | _PAGE_SHARED | _PAGE_EXECUTE | _PAGE_READ | _PAGE_WRITE)
multiline_comment|/* Make it a device mapping for maximum safety (e.g. for mapping device&n;   registers into user-space via /dev/map).  */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached(x) __pgprot(((x).pgprot &amp; ~(_PAGE_CACHABLE)) | _PAGE_DEVICE)
DECL|macro|pgprot_writecombine
mdefine_line|#define pgprot_writecombine(prot) __pgprot(pgprot_val(prot) &amp; ~_PAGE_CACHABLE)
multiline_comment|/*&n; * Handling allocation failures during page table setup.&n; */
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
DECL|macro|__handle_bad_pmd
mdefine_line|#define __handle_bad_pmd(x)&t;__handle_bad_pmd_kernel(x)
multiline_comment|/*&n; * PTE level access routines.&n; *&n; * Note1:&n; * It&squot;s the tree walk leaf. This is physical address to be stored.&n; *&n; * Note 2:&n; * Regarding the choice of _PTE_EMPTY:&n;&n;   We must choose a bit pattern that cannot be valid, whether or not the page&n;   is present.  bit[2]==1 =&gt; present, bit[2]==0 =&gt; swapped out.  If swapped&n;   out, bits [31:8], [6:3], [1:0] are under swapper control, so only bit[7] is&n;   left for us to select.  If we force bit[7]==0 when swapped out, we could use&n;   the combination bit[7,2]=2&squot;b10 to indicate an empty PTE.  Alternatively, if&n;   we force bit[7]==1 when swapped out, we can use all zeroes to indicate&n;   empty.  This is convenient, because the page tables get cleared to zero&n;   when they are allocated.&n;&n; */
DECL|macro|_PTE_EMPTY
mdefine_line|#define _PTE_EMPTY&t;0x0
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;(pte_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pte_clear
mdefine_line|#define pte_clear(xp)&t;(set_pte(xp, __pte(_PTE_EMPTY)))
DECL|macro|pte_none
mdefine_line|#define pte_none(x)&t;(pte_val(x) == _PTE_EMPTY)
multiline_comment|/*&n; * Some definitions to translate between mem_map, PTEs, and page&n; * addresses:&n; */
multiline_comment|/*&n; * Given a PTE, return the index of the mem_map[] entry corresponding&n; * to the page frame the PTE. Get the absolute physical address, make&n; * a relative physical address and translate it to an index.&n; */
DECL|macro|pte_pagenr
mdefine_line|#define pte_pagenr(x)&t;&t;(((unsigned long) (pte_val(x)) - &bslash;&n;&t;&t;&t;&t; __MEMORY_START) &gt;&gt; PAGE_SHIFT)
multiline_comment|/*&n; * Given a PTE, return the &quot;struct page *&quot;.&n; */
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;(mem_map + pte_pagenr(x))
multiline_comment|/*&n; * Return number of (down rounded) MB corresponding to x pages.&n; */
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x) ((x) &gt;&gt; (20-PAGE_SHIFT))
multiline_comment|/*&n; * The following have defined behavior only work if pte_present() is true.&n; */
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_READ
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_EXECUTE
suffix:semicolon
)brace
DECL|function|pte_dirty
r_static
r_inline
r_int
(def_block
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
)def_block
DECL|function|pte_young
r_static
r_inline
r_int
(def_block
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
)def_block
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_FILE
suffix:semicolon
)brace
DECL|function|pte_write
r_static
r_inline
r_int
(def_block
id|pte_write
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
id|_PAGE_WRITE
suffix:semicolon
)brace
)def_block
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_READ
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_WRITE
)paren
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_EXECUTE
)paren
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_DIRTY
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_ACCESSED
)paren
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or
id|_PAGE_READ
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or
id|_PAGE_WRITE
)paren
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or
id|_PAGE_EXECUTE
)paren
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or
id|_PAGE_DIRTY
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or
id|_PAGE_ACCESSED
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry.&n; *&n; * extern pte_t mk_pte(struct page *page, pgprot_t pgprot)&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page,pgprot)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t __pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_pte(&amp;__pte, __pte((((page)-mem_map) &lt;&lt; PAGE_SHIFT) | &t;&t;&bslash;&n;&t;&t;__MEMORY_START | pgprot_val((pgprot))));&t;&t;&t;&bslash;&n;&t;__pte;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * This takes a (absolute) physical page address that is used&n; * by the remapping functions&n; */
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage, pgprot) &bslash;&n;({ pte_t __pte; set_pte(&amp;__pte, __pte(physpage | pgprot_val(pgprot))); __pte; })
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
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
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|page_pte_prot
mdefine_line|#define page_pte_prot(page, prot) mk_pte(page, prot)
DECL|macro|page_pte
mdefine_line|#define page_pte(page) page_pte_prot(page, __pgprot(0))
DECL|typedef|pte_addr_t
r_typedef
id|pte_t
op_star
id|pte_addr_t
suffix:semicolon
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
r_extern
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
suffix:semicolon
multiline_comment|/* Encode and decode a swap entry */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;&t;(((x).val &amp; 3) + (((x).val &gt;&gt; 1) &amp; 0x3c))
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;&t;((x).val &gt;&gt; 8)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset)&t;((swp_entry_t) { ((offset &lt;&lt; 8) + ((type &amp; 0x3c) &lt;&lt; 1) + (type &amp; 3)) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
multiline_comment|/* Encode and decode a nonlinear file mapping entry */
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;&t;29
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(pte)&t;&t;(pte_val(pte))
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off)&t;&t;((pte_t) { (off) | _PAGE_FILE })
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|PageSkip
mdefine_line|#define PageSkip(page)&t;&t;(0)
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma, vaddr, paddr, size, prot)&t;&t;&bslash;&n;&t;&t;remap_pfn_range(vma, vaddr, (paddr) &gt;&gt; PAGE_SHIFT, size, prot)
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()    do { } while (0)
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)&t;&t;(((unsigned long)((x).pte)) &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot)&t;__pte(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot))
DECL|macro|pfn_pmd
mdefine_line|#define pfn_pmd(pfn, prot)&t;__pmd(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot))
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#endif /* __ASM_SH64_PGTABLE_H */
eof
