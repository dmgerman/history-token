multiline_comment|/* $Id: pgtsrmmu.h,v 1.31 2000/07/16 21:48:52 anton Exp $&n; * pgtsrmmu.h:  SRMMU page table defines and code.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_PGTSRMMU_H
DECL|macro|_SPARC_PGTSRMMU_H
mdefine_line|#define _SPARC_PGTSRMMU_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifdef __ASSEMBLY__
macro_line|#include &lt;asm/thread_info.h&gt;&t;/* TI_UWINMASK for WINDOW_FLUSH */
macro_line|#endif
multiline_comment|/* Number of contexts is implementation-dependent; 64k is the most we support */
DECL|macro|SRMMU_MAX_CONTEXTS
mdefine_line|#define SRMMU_MAX_CONTEXTS&t;65536
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table entry can map */
DECL|macro|SRMMU_REAL_PMD_SHIFT
mdefine_line|#define SRMMU_REAL_PMD_SHIFT&t;&t;18
DECL|macro|SRMMU_REAL_PMD_SIZE
mdefine_line|#define SRMMU_REAL_PMD_SIZE&t;&t;(1UL &lt;&lt; SRMMU_REAL_PMD_SHIFT)
DECL|macro|SRMMU_REAL_PMD_MASK
mdefine_line|#define SRMMU_REAL_PMD_MASK&t;&t;(~(SRMMU_REAL_PMD_SIZE-1))
DECL|macro|SRMMU_REAL_PMD_ALIGN
mdefine_line|#define SRMMU_REAL_PMD_ALIGN(__addr)&t;(((__addr)+SRMMU_REAL_PMD_SIZE-1)&amp;SRMMU_REAL_PMD_MASK)
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|SRMMU_PGDIR_SHIFT
mdefine_line|#define SRMMU_PGDIR_SHIFT       24
DECL|macro|SRMMU_PGDIR_SIZE
mdefine_line|#define SRMMU_PGDIR_SIZE        (1UL &lt;&lt; SRMMU_PGDIR_SHIFT)
DECL|macro|SRMMU_PGDIR_MASK
mdefine_line|#define SRMMU_PGDIR_MASK        (~(SRMMU_PGDIR_SIZE-1))
DECL|macro|SRMMU_PGDIR_ALIGN
mdefine_line|#define SRMMU_PGDIR_ALIGN(addr) (((addr)+SRMMU_PGDIR_SIZE-1)&amp;SRMMU_PGDIR_MASK)
DECL|macro|SRMMU_REAL_PTRS_PER_PTE
mdefine_line|#define SRMMU_REAL_PTRS_PER_PTE&t;64
DECL|macro|SRMMU_REAL_PTRS_PER_PMD
mdefine_line|#define SRMMU_REAL_PTRS_PER_PMD&t;64
DECL|macro|SRMMU_PTRS_PER_PGD
mdefine_line|#define SRMMU_PTRS_PER_PGD&t;256
DECL|macro|SRMMU_REAL_PTE_TABLE_SIZE
mdefine_line|#define SRMMU_REAL_PTE_TABLE_SIZE&t;(SRMMU_REAL_PTRS_PER_PTE*4)
DECL|macro|SRMMU_PMD_TABLE_SIZE
mdefine_line|#define SRMMU_PMD_TABLE_SIZE&t;&t;(SRMMU_REAL_PTRS_PER_PMD*4)
DECL|macro|SRMMU_PGD_TABLE_SIZE
mdefine_line|#define SRMMU_PGD_TABLE_SIZE&t;&t;(SRMMU_PTRS_PER_PGD*4)
multiline_comment|/*&n; * To support pagetables in highmem, Linux introduces APIs which&n; * return struct page* and generally manipulate page tables when&n; * they are not mapped into kernel space. Our hardware page tables&n; * are smaller than pages. We lump hardware tabes into big, page sized&n; * software tables.&n; *&n; * PMD_SHIFT determines the size of the area a second-level page table entry&n; * can map, and our pmd_t is 16 times larger than normal.  The values which&n; * were once defined here are now generic for 4c and srmmu, so they&squot;re&n; * found in pgtable.h.&n; */
DECL|macro|SRMMU_PTRS_PER_PMD
mdefine_line|#define SRMMU_PTRS_PER_PMD&t;4
multiline_comment|/* Definition of the values in the ET field of PTD&squot;s and PTE&squot;s */
DECL|macro|SRMMU_ET_MASK
mdefine_line|#define SRMMU_ET_MASK         0x3
DECL|macro|SRMMU_ET_INVALID
mdefine_line|#define SRMMU_ET_INVALID      0x0
DECL|macro|SRMMU_ET_PTD
mdefine_line|#define SRMMU_ET_PTD          0x1
DECL|macro|SRMMU_ET_PTE
mdefine_line|#define SRMMU_ET_PTE          0x2
DECL|macro|SRMMU_ET_REPTE
mdefine_line|#define SRMMU_ET_REPTE        0x3 /* AIEEE, SuperSparc II reverse endian page! */
multiline_comment|/* Physical page extraction from PTP&squot;s and PTE&squot;s. */
DECL|macro|SRMMU_CTX_PMASK
mdefine_line|#define SRMMU_CTX_PMASK    0xfffffff0
DECL|macro|SRMMU_PTD_PMASK
mdefine_line|#define SRMMU_PTD_PMASK    0xfffffff0
DECL|macro|SRMMU_PTE_PMASK
mdefine_line|#define SRMMU_PTE_PMASK    0xffffff00
multiline_comment|/* The pte non-page bits.  Some notes:&n; * 1) cache, dirty, valid, and ref are frobbable&n; *    for both supervisor and user pages.&n; * 2) exec and write will only give the desired effect&n; *    on user pages&n; * 3) use priv and priv_readonly for changing the&n; *    characteristics of supervisor ptes&n; */
DECL|macro|SRMMU_CACHE
mdefine_line|#define SRMMU_CACHE        0x80
DECL|macro|SRMMU_DIRTY
mdefine_line|#define SRMMU_DIRTY        0x40
DECL|macro|SRMMU_REF
mdefine_line|#define SRMMU_REF          0x20
DECL|macro|SRMMU_NOREAD
mdefine_line|#define SRMMU_NOREAD       0x10
DECL|macro|SRMMU_EXEC
mdefine_line|#define SRMMU_EXEC         0x08
DECL|macro|SRMMU_WRITE
mdefine_line|#define SRMMU_WRITE        0x04
DECL|macro|SRMMU_VALID
mdefine_line|#define SRMMU_VALID        0x02 /* SRMMU_ET_PTE */
DECL|macro|SRMMU_PRIV
mdefine_line|#define SRMMU_PRIV         0x1c
DECL|macro|SRMMU_PRIV_RDONLY
mdefine_line|#define SRMMU_PRIV_RDONLY  0x18
DECL|macro|SRMMU_FILE
mdefine_line|#define SRMMU_FILE         0x40&t;/* Implemented in software */
DECL|macro|SRMMU_PTE_FILE_SHIFT
mdefine_line|#define SRMMU_PTE_FILE_SHIFT     8&t;/* == 32-PTE_FILE_MAX_BITS */
DECL|macro|SRMMU_CHG_MASK
mdefine_line|#define SRMMU_CHG_MASK    (0xffffff00 | SRMMU_REF | SRMMU_DIRTY)
multiline_comment|/* SRMMU swap entry encoding&n; *&n; * We use 5 bits for the type and 19 for the offset.  This gives us&n; * 32 swapfiles of 4GB each.  Encoding looks like:&n; *&n; * oooooooooooooooooootttttRRRRRRRR&n; * fedcba9876543210fedcba9876543210&n; *&n; * The bottom 8 bits are reserved for protection and status bits, especially&n; * FILE and PRESENT.&n; */
DECL|macro|SRMMU_SWP_TYPE_MASK
mdefine_line|#define SRMMU_SWP_TYPE_MASK&t;0x1f
DECL|macro|SRMMU_SWP_TYPE_SHIFT
mdefine_line|#define SRMMU_SWP_TYPE_SHIFT&t;SRMMU_PTE_FILE_SHIFT
DECL|macro|SRMMU_SWP_OFF_MASK
mdefine_line|#define SRMMU_SWP_OFF_MASK&t;0x7ffff
DECL|macro|SRMMU_SWP_OFF_SHIFT
mdefine_line|#define SRMMU_SWP_OFF_SHIFT&t;(SRMMU_PTE_FILE_SHIFT + 5)
multiline_comment|/* Some day I will implement true fine grained access bits for&n; * user pages because the SRMMU gives us the capabilities to&n; * enforce all the protection levels that vma&squot;s can have.&n; * XXX But for now...&n; */
DECL|macro|SRMMU_PAGE_NONE
mdefine_line|#define SRMMU_PAGE_NONE    __pgprot(SRMMU_CACHE | &bslash;&n;&t;&t;&t;&t;    SRMMU_PRIV | SRMMU_REF)
DECL|macro|SRMMU_PAGE_SHARED
mdefine_line|#define SRMMU_PAGE_SHARED  __pgprot(SRMMU_VALID | SRMMU_CACHE | &bslash;&n;&t;&t;&t;&t;    SRMMU_EXEC | SRMMU_WRITE | SRMMU_REF)
DECL|macro|SRMMU_PAGE_COPY
mdefine_line|#define SRMMU_PAGE_COPY    __pgprot(SRMMU_VALID | SRMMU_CACHE | &bslash;&n;&t;&t;&t;&t;    SRMMU_EXEC | SRMMU_REF)
DECL|macro|SRMMU_PAGE_RDONLY
mdefine_line|#define SRMMU_PAGE_RDONLY  __pgprot(SRMMU_VALID | SRMMU_CACHE | &bslash;&n;&t;&t;&t;&t;    SRMMU_EXEC | SRMMU_REF)
DECL|macro|SRMMU_PAGE_KERNEL
mdefine_line|#define SRMMU_PAGE_KERNEL  __pgprot(SRMMU_VALID | SRMMU_CACHE | SRMMU_PRIV | &bslash;&n;&t;&t;&t;&t;    SRMMU_DIRTY | SRMMU_REF)
multiline_comment|/* SRMMU Register addresses in ASI 0x4.  These are valid for all&n; * current SRMMU implementations that exist.&n; */
DECL|macro|SRMMU_CTRL_REG
mdefine_line|#define SRMMU_CTRL_REG           0x00000000
DECL|macro|SRMMU_CTXTBL_PTR
mdefine_line|#define SRMMU_CTXTBL_PTR         0x00000100
DECL|macro|SRMMU_CTX_REG
mdefine_line|#define SRMMU_CTX_REG            0x00000200
DECL|macro|SRMMU_FAULT_STATUS
mdefine_line|#define SRMMU_FAULT_STATUS       0x00000300
DECL|macro|SRMMU_FAULT_ADDR
mdefine_line|#define SRMMU_FAULT_ADDR         0x00000400
DECL|macro|WINDOW_FLUSH
mdefine_line|#define WINDOW_FLUSH(tmp1, tmp2)&t;&t;&t;&t;&t;&bslash;&n;&t;mov&t;0, tmp1;&t;&t;&t;&t;&t;&t;&bslash;&n;98:&t;ld&t;[%g6 + TI_UWINMASK], tmp2;&t;&t;&t;&t;&bslash;&n;&t;orcc&t;%g0, tmp2, %g0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;add&t;tmp1, 1, tmp1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;bne&t;98b;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; save&t;%sp, -64, %sp;&t;&t;&t;&t;&t;&t;&bslash;&n;99:&t;subcc&t;tmp1, 1, tmp1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;bne&t;99b;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; restore %g0, %g0, %g0;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* This makes sense. Honest it does - Anton */
multiline_comment|/* XXX Yes but it&squot;s ugly as sin.  FIXME. -KMW */
r_extern
r_void
op_star
id|srmmu_nocache_pool
suffix:semicolon
DECL|macro|__nocache_pa
mdefine_line|#define __nocache_pa(VADDR) (((unsigned long)VADDR) - SRMMU_NOCACHE_VADDR + __pa((unsigned long)srmmu_nocache_pool))
DECL|macro|__nocache_va
mdefine_line|#define __nocache_va(PADDR) (__va((unsigned long)PADDR) - (unsigned long)srmmu_nocache_pool + SRMMU_NOCACHE_VADDR)
DECL|macro|__nocache_fix
mdefine_line|#define __nocache_fix(VADDR) __va(__nocache_pa(VADDR))
multiline_comment|/* Accessing the MMU control register. */
DECL|function|srmmu_get_mmureg
r_extern
id|__inline__
r_int
r_int
id|srmmu_get_mmureg
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%%g0] %1, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|srmmu_set_mmureg
r_extern
id|__inline__
r_void
id|srmmu_set_mmureg
c_func
(paren
r_int
r_int
id|regval
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %0, [%%g0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|regval
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|srmmu_set_ctable_ptr
r_extern
id|__inline__
r_void
id|srmmu_set_ctable_ptr
c_func
(paren
r_int
r_int
id|paddr
)paren
(brace
id|paddr
op_assign
(paren
(paren
id|paddr
op_rshift
l_int|4
)paren
op_amp
id|SRMMU_CTX_PMASK
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %0, [%1] %2&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|paddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|SRMMU_CTXTBL_PTR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|srmmu_get_ctable_ptr
r_extern
id|__inline__
r_int
r_int
id|srmmu_get_ctable_ptr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SRMMU_CTXTBL_PTR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
(paren
id|retval
op_amp
id|SRMMU_CTX_PMASK
)paren
op_lshift
l_int|4
suffix:semicolon
)brace
DECL|function|srmmu_set_context
r_extern
id|__inline__
r_void
id|srmmu_set_context
c_func
(paren
r_int
id|context
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %0, [%1] %2&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|context
)paren
comma
l_string|&quot;r&quot;
(paren
id|SRMMU_CTX_REG
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|srmmu_get_context
r_extern
id|__inline__
r_int
id|srmmu_get_context
c_func
(paren
r_void
)paren
(brace
r_register
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SRMMU_CTX_REG
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|srmmu_get_fstatus
r_extern
id|__inline__
r_int
r_int
id|srmmu_get_fstatus
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SRMMU_FAULT_STATUS
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|srmmu_get_faddr
r_extern
id|__inline__
r_int
r_int
id|srmmu_get_faddr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|SRMMU_FAULT_ADDR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MMUREGS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* This is guaranteed on all SRMMU&squot;s. */
DECL|function|srmmu_flush_whole_tlb
r_extern
id|__inline__
r_void
id|srmmu_flush_whole_tlb
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0x400
)paren
comma
multiline_comment|/* Flush entire TLB!! */
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_PROBE
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* These flush types are not available on all chips... */
DECL|function|srmmu_flush_tlb_ctx
r_extern
id|__inline__
r_void
id|srmmu_flush_tlb_ctx
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0x300
)paren
comma
multiline_comment|/* Flush TLB ctx.. */
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_PROBE
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|srmmu_flush_tlb_region
r_extern
id|__inline__
r_void
id|srmmu_flush_tlb_region
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|addr
op_and_assign
id|SRMMU_PGDIR_MASK
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
op_or
l_int|0x200
)paren
comma
multiline_comment|/* Flush TLB region.. */
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_PROBE
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|srmmu_flush_tlb_segment
r_extern
id|__inline__
r_void
id|srmmu_flush_tlb_segment
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|addr
op_and_assign
id|SRMMU_REAL_PMD_MASK
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
op_or
l_int|0x100
)paren
comma
multiline_comment|/* Flush TLB segment.. */
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_PROBE
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|srmmu_flush_tlb_page
r_extern
id|__inline__
r_void
id|srmmu_flush_tlb_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
id|page
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|page
)paren
comma
multiline_comment|/* Flush TLB page.. */
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_PROBE
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|srmmu_hwprobe
r_extern
id|__inline__
r_int
r_int
id|srmmu_hwprobe
c_func
(paren
r_int
r_int
id|vaddr
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|vaddr
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|vaddr
op_or
l_int|0x400
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_PROBE
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|srmmu_get_pte
id|srmmu_get_pte
(paren
r_int
r_int
id|addr
)paren
(brace
r_register
r_int
r_int
id|entry
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tlda [%1] %2,%0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|entry
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
id|addr
op_amp
l_int|0xfffff000
)paren
op_or
l_int|0x400
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_PROBE
)paren
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
r_extern
r_int
r_int
(paren
op_star
id|srmmu_read_physical
)paren
(paren
r_int
r_int
id|paddr
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|srmmu_write_physical
)paren
(paren
r_int
r_int
id|paddr
comma
r_int
r_int
id|word
)paren
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(_SPARC_PGTSRMMU_H) */
eof
