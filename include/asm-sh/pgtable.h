macro_line|#ifndef __ASM_SH_PGTABLE_H
DECL|macro|__ASM_SH_PGTABLE_H
mdefine_line|#define __ASM_SH_PGTABLE_H
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
multiline_comment|/*&n; * Copyright (C) 1999 Niibe Yutaka&n; * Copyright (C) 2002, 2003, 2004 Paul Mundt&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pgtable-2level.h&gt;
multiline_comment|/*&n; * This file contains the functions and defines necessary to modify and use&n; * the SuperH page table tree.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
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
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Basically we have the same two-level (which is the logical three level&n; * Linux page table layout folded) page tables as the i386.&n; */
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
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE/PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|PTE_PHYS_MASK
mdefine_line|#define PTE_PHYS_MASK&t;0x1ffff000
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * First 1MB map is used by fixed purpose.&n; * Currently only 4-enty (16kB) is used (see arch/sh/mm/cache.c)&n; */
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;(P3SEG+0x00100000)
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;(FIXADDR_START-2*PAGE_SIZE)
DECL|macro|_PAGE_WT
mdefine_line|#define&t;_PAGE_WT&t;0x001  /* WT-bit on SH-4, 0 on SH-3 */
DECL|macro|_PAGE_HW_SHARED
mdefine_line|#define _PAGE_HW_SHARED&t;0x002  /* SH-bit  : page is shared among processes */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x004  /* D-bit   : page changed */
DECL|macro|_PAGE_CACHABLE
mdefine_line|#define _PAGE_CACHABLE&t;0x008  /* C-bit   : cachable */
DECL|macro|_PAGE_SZ0
mdefine_line|#define _PAGE_SZ0&t;0x010  /* SZ0-bit : Size of page */
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW&t;0x020  /* PR0-bit : write access allowed */
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x040  /* PR1-bit : user space access allowed */
DECL|macro|_PAGE_SZ1
mdefine_line|#define _PAGE_SZ1&t;0x080  /* SZ1-bit : Size of page (on SH-4) */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x100  /* V-bit   : page is valid */
DECL|macro|_PAGE_PROTNONE
mdefine_line|#define _PAGE_PROTNONE&t;0x200  /* software: if not present  */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED &t;0x400  /* software: page referenced */
DECL|macro|_PAGE_U0_SHARED
mdefine_line|#define _PAGE_U0_SHARED 0x800  /* software: page is shared in user space */
DECL|macro|_PAGE_FILE
mdefine_line|#define&t;_PAGE_FILE&t;_PAGE_WT  /* software: pagecache or swap? */
multiline_comment|/* software: moves to PTEA.TC (Timing Control) */
DECL|macro|_PAGE_PCC_AREA5
mdefine_line|#define _PAGE_PCC_AREA5&t;0x00000000&t;/* use BSC registers for area5 */
DECL|macro|_PAGE_PCC_AREA6
mdefine_line|#define _PAGE_PCC_AREA6&t;0x80000000&t;/* use BSC registers for area6 */
multiline_comment|/* software: moves to PTEA.SA[2:0] (Space Attributes) */
DECL|macro|_PAGE_PCC_IODYN
mdefine_line|#define _PAGE_PCC_IODYN 0x00000001&t;/* IO space, dynamically sized bus */
DECL|macro|_PAGE_PCC_IO8
mdefine_line|#define _PAGE_PCC_IO8&t;0x20000000&t;/* IO space, 8 bit bus */
DECL|macro|_PAGE_PCC_IO16
mdefine_line|#define _PAGE_PCC_IO16&t;0x20000001&t;/* IO space, 16 bit bus */
DECL|macro|_PAGE_PCC_COM8
mdefine_line|#define _PAGE_PCC_COM8&t;0x40000000&t;/* Common Memory space, 8 bit bus */
DECL|macro|_PAGE_PCC_COM16
mdefine_line|#define _PAGE_PCC_COM16&t;0x40000001&t;/* Common Memory space, 16 bit bus */
DECL|macro|_PAGE_PCC_ATR8
mdefine_line|#define _PAGE_PCC_ATR8&t;0x60000000&t;/* Attribute Memory space, 8 bit bus */
DECL|macro|_PAGE_PCC_ATR16
mdefine_line|#define _PAGE_PCC_ATR16&t;0x60000001&t;/* Attribute Memory space, 6 bit bus */
multiline_comment|/* Mask which drop software flags&n; * We also drop WT bit since it is used for _PAGE_FILE&n; * bit in this implementation.&n; */
DECL|macro|_PAGE_CLEAR_FLAGS
mdefine_line|#define _PAGE_CLEAR_FLAGS&t;(_PAGE_WT | _PAGE_PROTNONE | _PAGE_ACCESSED | _PAGE_U0_SHARED)
macro_line|#if defined(CONFIG_CPU_SH3)
multiline_comment|/*&n; * MMU on SH-3 has bug on SH-bit: We can&squot;t use it if MMUCR.IX=1.&n; * Work around: Just drop SH-bit.&n; */
DECL|macro|_PAGE_FLAGS_HARDWARE_MASK
mdefine_line|#define _PAGE_FLAGS_HARDWARE_MASK&t;(0x1fffffff &amp; ~(_PAGE_CLEAR_FLAGS | _PAGE_HW_SHARED))
macro_line|#else
DECL|macro|_PAGE_FLAGS_HARDWARE_MASK
mdefine_line|#define _PAGE_FLAGS_HARDWARE_MASK&t;(0x1fffffff &amp; ~(_PAGE_CLEAR_FLAGS))
macro_line|#endif
multiline_comment|/* Hardware flags: SZ0=1 (4k-byte) */
DECL|macro|_PAGE_FLAGS_HARD
mdefine_line|#define _PAGE_FLAGS_HARD&t;_PAGE_SZ0
macro_line|#if defined(CONFIG_HUGETLB_PAGE_SIZE_64K)
DECL|macro|_PAGE_SZHUGE
mdefine_line|#define _PAGE_SZHUGE&t;(_PAGE_SZ1)
macro_line|#elif defined(CONFIG_HUGETLB_PAGE_SIZE_1MB)
DECL|macro|_PAGE_SZHUGE
mdefine_line|#define _PAGE_SZHUGE&t;(_PAGE_SZ0 | _PAGE_SZ1)
macro_line|#endif
DECL|macro|_PAGE_SHARED
mdefine_line|#define _PAGE_SHARED&t;_PAGE_U0_SHARED
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PTE_MASK | _PAGE_ACCESSED | _PAGE_CACHABLE | _PAGE_DIRTY | _PAGE_SHARED)
macro_line|#ifdef CONFIG_MMU
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PROTNONE | _PAGE_CACHABLE |_PAGE_ACCESSED | _PAGE_FLAGS_HARD)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_CACHABLE |_PAGE_ACCESSED | _PAGE_SHARED | _PAGE_FLAGS_HARD)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_CACHABLE | _PAGE_ACCESSED | _PAGE_FLAGS_HARD)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_CACHABLE | _PAGE_ACCESSED | _PAGE_FLAGS_HARD)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_CACHABLE | _PAGE_DIRTY | _PAGE_ACCESSED | _PAGE_HW_SHARED | _PAGE_FLAGS_HARD)
DECL|macro|PAGE_KERNEL_NOCACHE
mdefine_line|#define PAGE_KERNEL_NOCACHE &bslash;&n;&t;&t;&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_ACCESSED | _PAGE_HW_SHARED | _PAGE_FLAGS_HARD)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO&t;__pgprot(_PAGE_PRESENT | _PAGE_CACHABLE | _PAGE_DIRTY | _PAGE_ACCESSED | _PAGE_HW_SHARED | _PAGE_FLAGS_HARD)
DECL|macro|PAGE_KERNEL_PCC
mdefine_line|#define PAGE_KERNEL_PCC(slot, type) &bslash;&n;&t;&t;&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_ACCESSED | _PAGE_FLAGS_HARD | (slot ? _PAGE_PCC_AREA5 : _PAGE_PCC_AREA6) | (type))
macro_line|#else /* no mmu */
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;&t;__pgprot(0)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;&t;__pgprot(0)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;&t;__pgprot(0)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;&t;__pgprot(0)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;&t;__pgprot(0)
DECL|macro|PAGE_KERNEL_NOCACHE
mdefine_line|#define PAGE_KERNEL_NOCACHE&t;__pgprot(0)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO&t;&t;__pgprot(0)
DECL|macro|PAGE_KERNEL_PCC
mdefine_line|#define PAGE_KERNEL_PCC&t;&t;__pgprot(0)
macro_line|#endif
multiline_comment|/*&n; * As i386 and MIPS, SuperH can&squot;t do page protection for execute, and&n; * considers that the same as a read.  Also, write permissions imply&n; * read permissions. This is the closest we can get..  &n; */
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
DECL|macro|pte_none
mdefine_line|#define pte_none(x)&t;(!pte_val(x))
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;(pte_val(x) &amp; (_PAGE_PRESENT | _PAGE_PROTNONE))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(xp)&t;do { set_pte(xp, __pte(0)); } while (0)
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!pmd_val(x))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(x)&t;(pmd_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(xp)&t;do { set_pmd(xp, __pmd(0)); } while (0)
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(x)&t;((pmd_val(x) &amp; (~PAGE_MASK &amp; ~_PAGE_USER)) != _KERNPG_TABLE)
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x)&t;((x) &gt;&gt; (20-PAGE_SHIFT))
DECL|macro|pte_page
mdefine_line|#define pte_page(x) &t;phys_to_page(pte_val(x)&amp;PTE_PHYS_MASK)
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
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
id|_PAGE_USER
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
id|_PAGE_USER
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
id|_PAGE_RW
suffix:semicolon
)brace
)def_block
DECL|function|pte_not_present
r_static
r_inline
r_int
(def_block
id|pte_not_present
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
id|_PAGE_PRESENT
)paren
suffix:semicolon
)brace
)def_block
DECL|function|pte_rdprotect
r_static
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
id|_PAGE_USER
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_exprotect
r_static
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
id|_PAGE_USER
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkclean
r_static
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
r_static
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
DECL|function|pte_wrprotect
r_static
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
id|_PAGE_RW
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkread
r_static
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
id|_PAGE_USER
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkexec
r_static
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
id|_PAGE_USER
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkdirty
r_static
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
r_static
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
DECL|function|pte_mkwrite
r_static
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
id|_PAGE_RW
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/*&n; * Macro and implementation to make a page protection as uncachable.&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached pgprot_noncached
DECL|function|pgprot_noncached
r_static
r_inline
id|pgprot_t
id|pgprot_noncached
c_func
(paren
id|pgprot_t
id|_prot
)paren
(brace
r_int
r_int
id|prot
op_assign
id|pgprot_val
c_func
(paren
id|_prot
)paren
suffix:semicolon
id|prot
op_and_assign
op_complement
id|_PAGE_CACHABLE
suffix:semicolon
r_return
id|__pgprot
c_func
(paren
id|prot
)paren
suffix:semicolon
)brace
DECL|macro|pgprot_writecombine
mdefine_line|#define pgprot_writecombine(prot) __pgprot(pgprot_val(prot) &amp; ~_PAGE_CACHABLE)
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; *&n; * extern pte_t mk_pte(struct page *page, pgprot_t pgprot)&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;pfn_pte(page_to_pfn(page), (pgprot))
DECL|function|pte_modify
r_static
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
DECL|macro|page_pte
mdefine_line|#define page_pte(page) page_pte_prot(page, __pgprot(0))
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd) &bslash;&n;((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) &bslash;&n;&t;(phys_to_page(pmd_val(pmd)))
multiline_comment|/* to find an entry in a page-table-directory. */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) (((address) &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD-1))
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) ((mm)-&gt;pgd+pgd_index(address))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|pte_index
mdefine_line|#define pte_index(address) &bslash;&n;&t;&t;((address &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address) &bslash;&n;&t;((pte_t *) pmd_page_kernel(*(dir)) + pte_index(address))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address) pte_offset_kernel(dir, address)
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address) pte_offset_kernel(dir, address)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte)&t;&t;do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte)&t;do { } while (0)
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
multiline_comment|/* Encode and de-code a swap entry */
multiline_comment|/*&n; * NOTE: We should set ZEROs at the position of _PAGE_PRESENT&n; *       and _PAGE_PROTNONE bits&n; */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;((x).val &amp; 0xff)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;((x).val &gt;&gt; 10)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset) ((swp_entry_t) { (type) | ((offset) &lt;&lt; 10) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) &gt;&gt; 1 })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val &lt;&lt; 1 })
multiline_comment|/*&n; * Encode and decode a nonlinear file mapping entry&n; */
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;29
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(pte)&t;(pte_val(pte) &gt;&gt; 1)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off)&t;((pte_t) { ((off) &lt;&lt; 1) | _PAGE_FILE })
DECL|typedef|pte_addr_t
r_typedef
id|pte_t
op_star
id|pte_addr_t
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma, vaddr, paddr, size, prot)&t;&t;&bslash;&n;&t;&t;remap_pfn_range(vma, vaddr, (paddr) &gt;&gt; PAGE_SHIFT, size, prot)
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
macro_line|#ifndef CONFIG_MMU
r_extern
r_int
r_int
id|kobjsize
c_func
(paren
r_const
r_void
op_star
id|objp
)paren
suffix:semicolon
macro_line|#endif /* !CONFIG_MMU */
macro_line|#if defined(CONFIG_CPU_SH4) || defined(CONFIG_SH7705_CACHE_32KB)
DECL|macro|__HAVE_ARCH_PTEP_GET_AND_CLEAR
mdefine_line|#define __HAVE_ARCH_PTEP_GET_AND_CLEAR
r_extern
id|pte_t
id|ptep_get_and_clear
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
suffix:semicolon
macro_line|#endif
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#endif /* __ASM_SH_PAGE_H */
eof
