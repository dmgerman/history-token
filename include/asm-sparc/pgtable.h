multiline_comment|/* $Id: pgtable.h,v 1.110 2001/12/21 04:56:17 davem Exp $ */
macro_line|#ifndef _SPARC_PGTABLE_H
DECL|macro|_SPARC_PGTABLE_H
mdefine_line|#define _SPARC_PGTABLE_H
multiline_comment|/*  asm-sparc/pgtable.h:  Defines and functions used to work&n; *                        with Sparc page tables.&n; *&n; *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *  Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#ifdef CONFIG_SUN4
macro_line|#include &lt;asm/pgtsun4.h&gt;
macro_line|#else
macro_line|#include &lt;asm/pgtsun4c.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/pgtsrmmu.h&gt;
macro_line|#include &lt;asm/vac-ops.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/btfixup.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|load_mmu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|calc_highpages
c_func
(paren
r_void
)paren
suffix:semicolon
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|quick_kernel_fault
comma
r_int
r_int
)paren
DECL|macro|quick_kernel_fault
mdefine_line|#define quick_kernel_fault(addr) BTFIXUP_CALL(quick_kernel_fault)(addr)
multiline_comment|/* Routines for data transfer buffers. */
id|BTFIXUPDEF_CALL
c_func
(paren
r_char
op_star
comma
id|mmu_lockarea
comma
r_char
op_star
comma
r_int
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|mmu_unlockarea
comma
r_char
op_star
comma
r_int
r_int
)paren
DECL|macro|mmu_lockarea
mdefine_line|#define mmu_lockarea(vaddr,len) BTFIXUP_CALL(mmu_lockarea)(vaddr,len)
DECL|macro|mmu_unlockarea
mdefine_line|#define mmu_unlockarea(vaddr,len) BTFIXUP_CALL(mmu_unlockarea)(vaddr,len)
multiline_comment|/* These are implementations for sbus_map_sg/sbus_unmap_sg... collapse later */
id|BTFIXUPDEF_CALL
c_func
(paren
id|__u32
comma
id|mmu_get_scsi_one
comma
r_char
op_star
comma
r_int
r_int
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|mmu_get_scsi_sgl
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|mmu_release_scsi_one
comma
id|__u32
comma
r_int
r_int
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|mmu_release_scsi_sgl
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
DECL|macro|mmu_get_scsi_one
mdefine_line|#define mmu_get_scsi_one(vaddr,len,sbus) BTFIXUP_CALL(mmu_get_scsi_one)(vaddr,len,sbus)
DECL|macro|mmu_get_scsi_sgl
mdefine_line|#define mmu_get_scsi_sgl(sg,sz,sbus) BTFIXUP_CALL(mmu_get_scsi_sgl)(sg,sz,sbus)
DECL|macro|mmu_release_scsi_one
mdefine_line|#define mmu_release_scsi_one(vaddr,len,sbus) BTFIXUP_CALL(mmu_release_scsi_one)(vaddr,len,sbus)
DECL|macro|mmu_release_scsi_sgl
mdefine_line|#define mmu_release_scsi_sgl(sg,sz,sbus) BTFIXUP_CALL(mmu_release_scsi_sgl)(sg,sz,sbus)
multiline_comment|/*&n; * mmu_map/unmap are provided by iommu/iounit; Invalid to call on IIep.&n; */
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|mmu_map_dma_area
comma
r_int
r_int
id|va
comma
id|__u32
id|addr
comma
r_int
id|len
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_int
r_int
multiline_comment|/*phys*/
comma
id|mmu_translate_dvma
comma
r_int
r_int
id|busa
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|mmu_unmap_dma_area
comma
r_int
r_int
id|busa
comma
r_int
id|len
)paren
DECL|macro|mmu_map_dma_area
mdefine_line|#define mmu_map_dma_area(va, ba,len) BTFIXUP_CALL(mmu_map_dma_area)(va,ba,len)
DECL|macro|mmu_unmap_dma_area
mdefine_line|#define mmu_unmap_dma_area(ba,len) BTFIXUP_CALL(mmu_unmap_dma_area)(ba,len)
DECL|macro|mmu_translate_dvma
mdefine_line|#define mmu_translate_dvma(ba)     BTFIXUP_CALL(mmu_translate_dvma)(ba)
id|BTFIXUPDEF_SIMM13
c_func
(paren
id|pmd_shift
)paren
id|BTFIXUPDEF_SETHI
c_func
(paren
id|pmd_size
)paren
id|BTFIXUPDEF_SETHI
c_func
(paren
id|pmd_mask
)paren
r_extern
r_int
r_int
id|pmd_align
c_func
(paren
r_int
r_int
id|addr
)paren
id|__attribute__
c_func
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
DECL|function|pmd_align
r_extern
id|__inline__
r_int
r_int
id|pmd_align
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
(paren
id|addr
op_plus
op_complement
id|BTFIXUP_SETHI
c_func
(paren
id|pmd_mask
)paren
)paren
op_amp
id|BTFIXUP_SETHI
c_func
(paren
id|pmd_mask
)paren
)paren
suffix:semicolon
)brace
id|BTFIXUPDEF_SIMM13
c_func
(paren
id|pgdir_shift
)paren
id|BTFIXUPDEF_SETHI
c_func
(paren
id|pgdir_size
)paren
id|BTFIXUPDEF_SETHI
c_func
(paren
id|pgdir_mask
)paren
r_extern
r_int
r_int
id|pgdir_align
c_func
(paren
r_int
r_int
id|addr
)paren
id|__attribute__
c_func
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
DECL|function|pgdir_align
r_extern
id|__inline__
r_int
r_int
id|pgdir_align
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
(paren
id|addr
op_plus
op_complement
id|BTFIXUP_SETHI
c_func
(paren
id|pgdir_mask
)paren
)paren
op_amp
id|BTFIXUP_SETHI
c_func
(paren
id|pgdir_mask
)paren
)paren
suffix:semicolon
)brace
id|BTFIXUPDEF_SIMM13
c_func
(paren
id|ptrs_per_pte
)paren
id|BTFIXUPDEF_SIMM13
c_func
(paren
id|ptrs_per_pmd
)paren
id|BTFIXUPDEF_SIMM13
c_func
(paren
id|ptrs_per_pgd
)paren
id|BTFIXUPDEF_SIMM13
c_func
(paren
id|user_ptrs_per_pgd
)paren
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e)   __builtin_trap()
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e)   __builtin_trap()
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e)   __builtin_trap()
id|BTFIXUPDEF_INT
c_func
(paren
id|page_none
)paren
id|BTFIXUPDEF_INT
c_func
(paren
id|page_shared
)paren
id|BTFIXUPDEF_INT
c_func
(paren
id|page_copy
)paren
id|BTFIXUPDEF_INT
c_func
(paren
id|page_readonly
)paren
id|BTFIXUPDEF_INT
c_func
(paren
id|page_kernel
)paren
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT       &t;BTFIXUP_SIMM13(pmd_shift)
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE        &t;BTFIXUP_SETHI(pmd_size)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK        &t;BTFIXUP_SETHI(pmd_mask)
DECL|macro|PMD_ALIGN
mdefine_line|#define PMD_ALIGN(addr) &t;pmd_align(addr)
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT     &t;BTFIXUP_SIMM13(pgdir_shift)
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE      &t;BTFIXUP_SETHI(pgdir_size)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK      &t;BTFIXUP_SETHI(pgdir_mask)
DECL|macro|PGDIR_ALIGN
mdefine_line|#define PGDIR_ALIGN     &t;pgdir_align(addr)
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE    &t;BTFIXUP_SIMM13(ptrs_per_pte)
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD    &t;BTFIXUP_SIMM13(ptrs_per_pmd)
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD    &t;BTFIXUP_SIMM13(ptrs_per_pgd)
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;BTFIXUP_SIMM13(user_ptrs_per_pgd)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE      __pgprot(BTFIXUP_INT(page_none))
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED    __pgprot(BTFIXUP_INT(page_shared))
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY      __pgprot(BTFIXUP_INT(page_copy))
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY  __pgprot(BTFIXUP_INT(page_readonly))
r_extern
r_int
r_int
id|page_kernel
suffix:semicolon
macro_line|#ifdef MODULE
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;page_kernel
macro_line|#else
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL    __pgprot(BTFIXUP_INT(page_kernel))
macro_line|#endif
multiline_comment|/* Top-level page directory */
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* Page table for 0-4MB for everybody, on the Sparc this&n; * holds the same as on the i386.&n; */
r_extern
id|pte_t
id|pg0
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
id|pte_t
id|pg1
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
id|pte_t
id|pg2
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
id|pte_t
id|pg3
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
r_int
r_int
id|ptr_in_current_pgd
suffix:semicolon
multiline_comment|/* Here is a trick, since mmap.c need the initializer elements for&n; * protection_map[] to be constant at compile time, I set the following&n; * to all zeros.  I set it to the real values after I link in the&n; * appropriate MMU page table routines at boot time.&n; */
DECL|macro|__P000
mdefine_line|#define __P000  __pgprot(0)
DECL|macro|__P001
mdefine_line|#define __P001  __pgprot(0)
DECL|macro|__P010
mdefine_line|#define __P010  __pgprot(0)
DECL|macro|__P011
mdefine_line|#define __P011  __pgprot(0)
DECL|macro|__P100
mdefine_line|#define __P100  __pgprot(0)
DECL|macro|__P101
mdefine_line|#define __P101  __pgprot(0)
DECL|macro|__P110
mdefine_line|#define __P110  __pgprot(0)
DECL|macro|__P111
mdefine_line|#define __P111  __pgprot(0)
DECL|macro|__S000
mdefine_line|#define __S000&t;__pgprot(0)
DECL|macro|__S001
mdefine_line|#define __S001&t;__pgprot(0)
DECL|macro|__S010
mdefine_line|#define __S010&t;__pgprot(0)
DECL|macro|__S011
mdefine_line|#define __S011&t;__pgprot(0)
DECL|macro|__S100
mdefine_line|#define __S100&t;__pgprot(0)
DECL|macro|__S101
mdefine_line|#define __S101&t;__pgprot(0)
DECL|macro|__S110
mdefine_line|#define __S110&t;__pgprot(0)
DECL|macro|__S111
mdefine_line|#define __S111&t;__pgprot(0)
r_extern
r_int
id|num_contexts
suffix:semicolon
multiline_comment|/* First physical page can be anywhere, the following is needed so that&n; * va--&gt;pa and vice versa conversions work properly without performance&n; * hit for all __pa()/__va() operations.&n; */
r_extern
r_int
r_int
id|phys_base
suffix:semicolon
multiline_comment|/*&n; * BAD_PAGETABLE is used when we need a bogus page-table, while&n; * BAD_PAGE is used for a bogus page.&n; *&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
id|pte_t
op_star
id|__bad_pagetable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|pte_t
id|__bad_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|empty_zero_page
suffix:semicolon
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE __bad_pagetable()
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE __bad_page()
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (mem_map + (((unsigned long)&amp;empty_zero_page - PAGE_OFFSET + phys_base) &gt;&gt; PAGE_SHIFT))
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR      (8*sizeof(unsigned long))
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK          (~(sizeof(void*)-1))
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2   2
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
r_int
r_int
comma
id|pmd_page
comma
id|pmd_t
)paren
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
r_int
r_int
comma
id|pgd_page
comma
id|pgd_t
)paren
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) BTFIXUP_CALL(pmd_page)(pmd)
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd) BTFIXUP_CALL(pgd_page)(pgd)
id|BTFIXUPDEF_SETHI
c_func
(paren
id|none_mask
)paren
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
r_int
comma
id|pte_present
comma
id|pte_t
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|pte_clear
comma
id|pte_t
op_star
)paren
DECL|function|pte_none
r_extern
id|__inline__
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
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|BTFIXUP_SETHI
c_func
(paren
id|none_mask
)paren
)paren
suffix:semicolon
)brace
DECL|macro|pte_present
mdefine_line|#define pte_present(pte) BTFIXUP_CALL(pte_present)(pte)
DECL|macro|pte_clear
mdefine_line|#define pte_clear(pte) BTFIXUP_CALL(pte_clear)(pte)
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
r_int
comma
id|pmd_bad
comma
id|pmd_t
)paren
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
r_int
comma
id|pmd_present
comma
id|pmd_t
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|pmd_clear
comma
id|pmd_t
op_star
)paren
DECL|function|pmd_none
r_extern
id|__inline__
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
(paren
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
op_complement
id|BTFIXUP_SETHI
c_func
(paren
id|none_mask
)paren
)paren
suffix:semicolon
)brace
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd) BTFIXUP_CALL(pmd_bad)(pmd)
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd) BTFIXUP_CALL(pmd_present)(pmd)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmd) BTFIXUP_CALL(pmd_clear)(pmd)
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
r_int
comma
id|pgd_none
comma
id|pgd_t
)paren
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
r_int
comma
id|pgd_bad
comma
id|pgd_t
)paren
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
r_int
comma
id|pgd_present
comma
id|pgd_t
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|pgd_clear
comma
id|pgd_t
op_star
)paren
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd) BTFIXUP_CALL(pgd_none)(pgd)
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd) BTFIXUP_CALL(pgd_bad)(pgd)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd) BTFIXUP_CALL(pgd_present)(pgd)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgd) BTFIXUP_CALL(pgd_clear)(pgd)
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
id|BTFIXUPDEF_HALF
c_func
(paren
id|pte_writei
)paren
id|BTFIXUPDEF_HALF
c_func
(paren
id|pte_dirtyi
)paren
id|BTFIXUPDEF_HALF
c_func
(paren
id|pte_youngi
)paren
r_extern
r_int
id|pte_write
c_func
(paren
id|pte_t
id|pte
)paren
id|__attribute__
c_func
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
DECL|function|pte_write
r_extern
id|__inline__
r_int
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
id|BTFIXUP_HALF
c_func
(paren
id|pte_writei
)paren
suffix:semicolon
)brace
r_extern
r_int
id|pte_dirty
c_func
(paren
id|pte_t
id|pte
)paren
id|__attribute__
c_func
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
DECL|function|pte_dirty
r_extern
id|__inline__
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
id|BTFIXUP_HALF
c_func
(paren
id|pte_dirtyi
)paren
suffix:semicolon
)brace
r_extern
r_int
id|pte_young
c_func
(paren
id|pte_t
id|pte
)paren
id|__attribute__
c_func
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
DECL|function|pte_young
r_extern
id|__inline__
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
id|BTFIXUP_HALF
c_func
(paren
id|pte_youngi
)paren
suffix:semicolon
)brace
id|BTFIXUPDEF_HALF
c_func
(paren
id|pte_wrprotecti
)paren
id|BTFIXUPDEF_HALF
c_func
(paren
id|pte_mkcleani
)paren
id|BTFIXUPDEF_HALF
c_func
(paren
id|pte_mkoldi
)paren
r_extern
id|pte_t
id|pte_wrprotect
c_func
(paren
id|pte_t
id|pte
)paren
id|__attribute__
c_func
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
DECL|function|pte_wrprotect
r_extern
id|__inline__
id|pte_t
id|pte_wrprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
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
id|BTFIXUP_HALF
c_func
(paren
id|pte_wrprotecti
)paren
)paren
suffix:semicolon
)brace
r_extern
id|pte_t
id|pte_mkclean
c_func
(paren
id|pte_t
id|pte
)paren
id|__attribute__
c_func
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
DECL|function|pte_mkclean
r_extern
id|__inline__
id|pte_t
id|pte_mkclean
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
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
id|BTFIXUP_HALF
c_func
(paren
id|pte_mkcleani
)paren
)paren
suffix:semicolon
)brace
r_extern
id|pte_t
id|pte_mkold
c_func
(paren
id|pte_t
id|pte
)paren
id|__attribute__
c_func
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
DECL|function|pte_mkold
r_extern
id|__inline__
id|pte_t
id|pte_mkold
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
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
id|BTFIXUP_HALF
c_func
(paren
id|pte_mkoldi
)paren
)paren
suffix:semicolon
)brace
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
id|pte_t
comma
id|pte_mkwrite
comma
id|pte_t
)paren
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
id|pte_t
comma
id|pte_mkdirty
comma
id|pte_t
)paren
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
id|pte_t
comma
id|pte_mkyoung
comma
id|pte_t
)paren
DECL|macro|pte_mkwrite
mdefine_line|#define pte_mkwrite(pte) BTFIXUP_CALL(pte_mkwrite)(pte)
DECL|macro|pte_mkdirty
mdefine_line|#define pte_mkdirty(pte) BTFIXUP_CALL(pte_mkdirty)(pte)
DECL|macro|pte_mkyoung
mdefine_line|#define pte_mkyoung(pte) BTFIXUP_CALL(pte_mkyoung)(pte)
DECL|macro|page_pte_prot
mdefine_line|#define page_pte_prot(page, prot)&t;mk_pte(page, prot)
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;&t;&t;page_pte_prot(page, __pgprot(0))
id|BTFIXUPDEF_CALL
c_func
(paren
r_struct
id|page
op_star
comma
id|pte_page
comma
id|pte_t
)paren
DECL|macro|pte_page
mdefine_line|#define pte_page(pte) BTFIXUP_CALL(pte_page)(pte)
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
id|pte_t
comma
id|mk_pte
comma
r_struct
id|page
op_star
comma
id|pgprot_t
)paren
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
id|pte_t
comma
id|mk_pte_phys
comma
r_int
r_int
comma
id|pgprot_t
)paren
id|BTFIXUPDEF_CALL_CONST
c_func
(paren
id|pte_t
comma
id|mk_pte_io
comma
r_int
r_int
comma
id|pgprot_t
comma
r_int
)paren
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page,pgprot) BTFIXUP_CALL(mk_pte)(page,pgprot)
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(page,pgprot) BTFIXUP_CALL(mk_pte_phys)(page,pgprot)
DECL|macro|mk_pte_io
mdefine_line|#define mk_pte_io(page,pgprot,space) BTFIXUP_CALL(mk_pte_io)(page,pgprot,space)
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|pgd_set
comma
id|pgd_t
op_star
comma
id|pmd_t
op_star
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|pmd_set
comma
id|pmd_t
op_star
comma
id|pte_t
op_star
)paren
DECL|macro|pgd_set
mdefine_line|#define pgd_set(pgdp,pmdp) BTFIXUP_CALL(pgd_set)(pgdp,pmdp)
DECL|macro|pmd_set
mdefine_line|#define pmd_set(pmdp,ptep) BTFIXUP_CALL(pmd_set)(pmdp,ptep)
id|BTFIXUPDEF_INT
c_func
(paren
id|pte_modify_mask
)paren
r_extern
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
id|__attribute__
c_func
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
DECL|function|pte_modify
r_extern
id|__inline__
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
r_return
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
id|BTFIXUP_INT
c_func
(paren
id|pte_modify_mask
)paren
)paren
op_or
id|pgprot_val
c_func
(paren
id|newprot
)paren
)paren
suffix:semicolon
)brace
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) ((address) &gt;&gt; PGDIR_SHIFT)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) ((mm)-&gt;pgd + pgd_index(address))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
id|BTFIXUPDEF_CALL
c_func
(paren
id|pmd_t
op_star
comma
id|pmd_offset
comma
id|pgd_t
op_star
comma
r_int
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
id|pte_t
op_star
comma
id|pte_offset
comma
id|pmd_t
op_star
comma
r_int
r_int
)paren
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir,addr) BTFIXUP_CALL(pmd_offset)(dir,addr)
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|pte_offset
mdefine_line|#define pte_offset(dir,addr) BTFIXUP_CALL(pte_offset)(dir,addr)
multiline_comment|/* The permissions for pgprot_val to make a page mapped on the obio space */
r_extern
r_int
r_int
id|pg_iobits
suffix:semicolon
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma, pg)      do { } while(0)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,pg,adr,len)&t;do { } while (0)
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|set_pte
comma
id|pte_t
op_star
comma
id|pte_t
)paren
DECL|macro|set_pte
mdefine_line|#define set_pte(ptep,pteval) BTFIXUP_CALL(set_pte)(ptep,pteval)
r_struct
id|seq_file
suffix:semicolon
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|mmu_info
comma
r_struct
id|seq_file
op_star
)paren
DECL|macro|mmu_info
mdefine_line|#define mmu_info(p) BTFIXUP_CALL(mmu_info)(p)
multiline_comment|/* Fault handler stuff... */
DECL|macro|FAULT_CODE_PROT
mdefine_line|#define FAULT_CODE_PROT     0x1
DECL|macro|FAULT_CODE_WRITE
mdefine_line|#define FAULT_CODE_WRITE    0x2
DECL|macro|FAULT_CODE_USER
mdefine_line|#define FAULT_CODE_USER     0x4
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|update_mmu_cache
comma
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
id|pte_t
)paren
DECL|macro|update_mmu_cache
mdefine_line|#define update_mmu_cache(vma,addr,pte) BTFIXUP_CALL(update_mmu_cache)(vma,addr,pte)
r_extern
r_int
id|invalid_segment
suffix:semicolon
multiline_comment|/* Encode and de-code a swap entry */
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(x)&t;&t;&t;(((x).val &gt;&gt; 2) &amp; 0x7f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(x)&t;&t;&t;(((x).val &gt;&gt; 9) &amp; 0x3ffff)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type,offset)&t;&t;((swp_entry_t) { (((type) &amp; 0x7f) &lt;&lt; 2) | (((offset) &amp; 0x3ffff) &lt;&lt; 9) })
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
DECL|struct|ctx_list
r_struct
id|ctx_list
(brace
DECL|member|next
r_struct
id|ctx_list
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|ctx_list
op_star
id|prev
suffix:semicolon
DECL|member|ctx_number
r_int
r_int
id|ctx_number
suffix:semicolon
DECL|member|ctx_mm
r_struct
id|mm_struct
op_star
id|ctx_mm
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ctx_list
op_star
id|ctx_list_pool
suffix:semicolon
multiline_comment|/* Dynamically allocated */
r_extern
r_struct
id|ctx_list
id|ctx_free
suffix:semicolon
multiline_comment|/* Head of free list */
r_extern
r_struct
id|ctx_list
id|ctx_used
suffix:semicolon
multiline_comment|/* Head of used contexts list */
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT     -1
DECL|function|remove_from_ctx_list
r_extern
id|__inline__
r_void
id|remove_from_ctx_list
c_func
(paren
r_struct
id|ctx_list
op_star
id|entry
)paren
(brace
id|entry-&gt;next-&gt;prev
op_assign
id|entry-&gt;prev
suffix:semicolon
id|entry-&gt;prev-&gt;next
op_assign
id|entry-&gt;next
suffix:semicolon
)brace
DECL|function|add_to_ctx_list
r_extern
id|__inline__
r_void
id|add_to_ctx_list
c_func
(paren
r_struct
id|ctx_list
op_star
id|head
comma
r_struct
id|ctx_list
op_star
id|entry
)paren
(brace
id|entry-&gt;next
op_assign
id|head
suffix:semicolon
(paren
id|entry-&gt;prev
op_assign
id|head-&gt;prev
)paren
op_member_access_from_pointer
id|next
op_assign
id|entry
suffix:semicolon
id|head-&gt;prev
op_assign
id|entry
suffix:semicolon
)brace
DECL|macro|add_to_free_ctxlist
mdefine_line|#define add_to_free_ctxlist(entry) add_to_ctx_list(&amp;ctx_free, entry)
DECL|macro|add_to_used_ctxlist
mdefine_line|#define add_to_used_ctxlist(entry) add_to_ctx_list(&amp;ctx_used, entry)
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
r_switch
c_cond
(paren
id|sparc_cpu_model
)paren
(brace
r_case
id|sun4
suffix:colon
r_case
id|sun4c
suffix:colon
r_return
id|sun4c_get_pte
(paren
id|addr
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_case
id|sun4m
suffix:colon
r_case
id|sun4d
suffix:colon
r_return
(paren
(paren
id|srmmu_get_pte
(paren
id|addr
)paren
op_amp
l_int|0xffffff00
)paren
op_lshift
l_int|4
)paren
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
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
r_switch
c_cond
(paren
id|sparc_cpu_model
)paren
(brace
r_case
id|sun4
suffix:colon
r_case
id|sun4c
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Don&squot;t check iospace on sun4c */
r_case
id|sun4m
suffix:colon
r_case
id|sun4d
suffix:colon
r_return
(paren
id|srmmu_get_pte
(paren
id|addr
)paren
op_rshift
l_int|28
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_extern
r_int
r_int
op_star
id|sparc_valid_addr_bitmap
suffix:semicolon
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr) &bslash;&n;&t;(test_bit(__pa((unsigned long)(addr))&gt;&gt;20, sparc_valid_addr_bitmap))
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
id|to
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
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
macro_line|#endif /* !(_SPARC_PGTABLE_H) */
eof
