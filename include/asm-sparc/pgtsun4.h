multiline_comment|/* $Id: pgtsun4.h,v 1.5 2000/06/05 06:08:46 anton Exp $&n; * pgtsun4.h:  Sun4 specific pgtable.h defines and code.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef _SPARC_PGTSUN4C_H
DECL|macro|_SPARC_PGTSUN4C_H
mdefine_line|#define _SPARC_PGTSUN4C_H
macro_line|#include &lt;asm/contregs.h&gt;
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|SUN4C_PMD_SHIFT
mdefine_line|#define SUN4C_PMD_SHIFT       23
DECL|macro|SUN4C_PMD_SIZE
mdefine_line|#define SUN4C_PMD_SIZE        (1UL &lt;&lt; SUN4C_PMD_SHIFT)
DECL|macro|SUN4C_PMD_MASK
mdefine_line|#define SUN4C_PMD_MASK        (~(SUN4C_PMD_SIZE-1))
DECL|macro|SUN4C_PMD_ALIGN
mdefine_line|#define SUN4C_PMD_ALIGN(addr) (((addr)+SUN4C_PMD_SIZE-1)&amp;SUN4C_PMD_MASK)
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|SUN4C_PGDIR_SHIFT
mdefine_line|#define SUN4C_PGDIR_SHIFT       23
DECL|macro|SUN4C_PGDIR_SIZE
mdefine_line|#define SUN4C_PGDIR_SIZE        (1UL &lt;&lt; SUN4C_PGDIR_SHIFT)
DECL|macro|SUN4C_PGDIR_MASK
mdefine_line|#define SUN4C_PGDIR_MASK        (~(SUN4C_PGDIR_SIZE-1))
DECL|macro|SUN4C_PGDIR_ALIGN
mdefine_line|#define SUN4C_PGDIR_ALIGN(addr) (((addr)+SUN4C_PGDIR_SIZE-1)&amp;SUN4C_PGDIR_MASK)
multiline_comment|/* To represent how the sun4c mmu really lays things out. */
DECL|macro|SUN4C_REAL_PGDIR_SHIFT
mdefine_line|#define SUN4C_REAL_PGDIR_SHIFT       18
DECL|macro|SUN4C_REAL_PGDIR_SIZE
mdefine_line|#define SUN4C_REAL_PGDIR_SIZE        (1UL &lt;&lt; SUN4C_REAL_PGDIR_SHIFT)
DECL|macro|SUN4C_REAL_PGDIR_MASK
mdefine_line|#define SUN4C_REAL_PGDIR_MASK        (~(SUN4C_REAL_PGDIR_SIZE-1))
DECL|macro|SUN4C_REAL_PGDIR_ALIGN
mdefine_line|#define SUN4C_REAL_PGDIR_ALIGN(addr) (((addr)+SUN4C_REAL_PGDIR_SIZE-1)&amp;SUN4C_REAL_PGDIR_MASK)
multiline_comment|/* 19 bit PFN on sun4 */
DECL|macro|SUN4C_PFN_MASK
mdefine_line|#define SUN4C_PFN_MASK 0x7ffff
multiline_comment|/* Don&squot;t increase these unless the structures in sun4c.c are fixed */
DECL|macro|SUN4C_MAX_SEGMAPS
mdefine_line|#define SUN4C_MAX_SEGMAPS 256
DECL|macro|SUN4C_MAX_CONTEXTS
mdefine_line|#define SUN4C_MAX_CONTEXTS 16
multiline_comment|/*&n; * To be efficient, and not have to worry about allocating such&n; * a huge pgd, we make the kernel sun4c tables each hold 1024&n; * entries and the pgd similarly just like the i386 tables.&n; */
DECL|macro|SUN4C_PTRS_PER_PTE
mdefine_line|#define SUN4C_PTRS_PER_PTE    1024
DECL|macro|SUN4C_PTRS_PER_PMD
mdefine_line|#define SUN4C_PTRS_PER_PMD    1
DECL|macro|SUN4C_PTRS_PER_PGD
mdefine_line|#define SUN4C_PTRS_PER_PGD    1024
multiline_comment|/*&n; * Sparc SUN4C pte fields.&n; */
DECL|macro|_SUN4C_PAGE_VALID
mdefine_line|#define _SUN4C_PAGE_VALID        0x80000000
DECL|macro|_SUN4C_PAGE_SILENT_READ
mdefine_line|#define _SUN4C_PAGE_SILENT_READ  0x80000000   /* synonym */
DECL|macro|_SUN4C_PAGE_DIRTY
mdefine_line|#define _SUN4C_PAGE_DIRTY        0x40000000
DECL|macro|_SUN4C_PAGE_SILENT_WRITE
mdefine_line|#define _SUN4C_PAGE_SILENT_WRITE 0x40000000   /* synonym */
DECL|macro|_SUN4C_PAGE_PRIV
mdefine_line|#define _SUN4C_PAGE_PRIV         0x20000000   /* privileged page */
DECL|macro|_SUN4C_PAGE_NOCACHE
mdefine_line|#define _SUN4C_PAGE_NOCACHE      0x10000000   /* non-cacheable page */
DECL|macro|_SUN4C_PAGE_PRESENT
mdefine_line|#define _SUN4C_PAGE_PRESENT      0x08000000   /* implemented in software */
DECL|macro|_SUN4C_PAGE_IO
mdefine_line|#define _SUN4C_PAGE_IO           0x04000000   /* I/O page */
DECL|macro|_SUN4C_PAGE_READ
mdefine_line|#define _SUN4C_PAGE_READ         0x00800000   /* implemented in software */
DECL|macro|_SUN4C_PAGE_WRITE
mdefine_line|#define _SUN4C_PAGE_WRITE        0x00400000   /* implemented in software */
DECL|macro|_SUN4C_PAGE_ACCESSED
mdefine_line|#define _SUN4C_PAGE_ACCESSED     0x00200000   /* implemented in software */
DECL|macro|_SUN4C_PAGE_MODIFIED
mdefine_line|#define _SUN4C_PAGE_MODIFIED     0x00100000   /* implemented in software */
DECL|macro|_SUN4C_READABLE
mdefine_line|#define _SUN4C_READABLE&t;&t;(_SUN4C_PAGE_READ|_SUN4C_PAGE_SILENT_READ|&bslash;&n;&t;&t;&t;&t; _SUN4C_PAGE_ACCESSED)
DECL|macro|_SUN4C_WRITEABLE
mdefine_line|#define _SUN4C_WRITEABLE&t;(_SUN4C_PAGE_WRITE|_SUN4C_PAGE_SILENT_WRITE|&bslash;&n;&t;&t;&t;&t; _SUN4C_PAGE_MODIFIED)
DECL|macro|_SUN4C_PAGE_CHG_MASK
mdefine_line|#define _SUN4C_PAGE_CHG_MASK&t;(0xffff|_SUN4C_PAGE_ACCESSED|_SUN4C_PAGE_MODIFIED)
DECL|macro|SUN4C_PAGE_NONE
mdefine_line|#define SUN4C_PAGE_NONE&t;&t;__pgprot(_SUN4C_PAGE_PRESENT)
DECL|macro|SUN4C_PAGE_SHARED
mdefine_line|#define SUN4C_PAGE_SHARED&t;__pgprot(_SUN4C_PAGE_PRESENT|_SUN4C_READABLE|&bslash;&n;&t;&t;&t;&t;&t; _SUN4C_PAGE_WRITE)
DECL|macro|SUN4C_PAGE_COPY
mdefine_line|#define SUN4C_PAGE_COPY&t;&t;__pgprot(_SUN4C_PAGE_PRESENT|_SUN4C_READABLE)
DECL|macro|SUN4C_PAGE_READONLY
mdefine_line|#define SUN4C_PAGE_READONLY&t;__pgprot(_SUN4C_PAGE_PRESENT|_SUN4C_READABLE)
DECL|macro|SUN4C_PAGE_KERNEL
mdefine_line|#define SUN4C_PAGE_KERNEL&t;__pgprot(_SUN4C_READABLE|_SUN4C_WRITEABLE|&bslash;&n;&t;&t;&t;&t;&t; _SUN4C_PAGE_DIRTY|_SUN4C_PAGE_PRIV)
macro_line|#ifndef __ASSEMBLY__
DECL|function|sun4c_get_synchronous_error
r_extern
id|__inline__
r_int
r_int
id|sun4c_get_synchronous_error
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sync_err
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sync_err
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|AC_SYNC_ERR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
)paren
suffix:semicolon
r_return
id|sync_err
suffix:semicolon
)brace
DECL|function|sun4c_get_synchronous_address
r_extern
id|__inline__
r_int
r_int
id|sun4c_get_synchronous_address
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sync_addr
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sync_addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|AC_SYNC_VA
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
)paren
suffix:semicolon
r_return
id|sync_addr
suffix:semicolon
)brace
multiline_comment|/* SUN4 pte, segmap, and context manipulation */
DECL|function|sun4c_get_segmap
r_extern
id|__inline__
r_int
r_int
id|sun4c_get_segmap
c_func
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
l_string|&quot;&bslash;n&bslash;tlduha [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|entry
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_SEGMAP
)paren
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|function|sun4c_put_segmap
r_extern
id|__inline__
r_void
id|sun4c_put_segmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|entry
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tstha %1, [%0] %2; nop; nop; nop;&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|entry
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_SEGMAP
)paren
)paren
suffix:semicolon
)brace
DECL|function|sun4c_get_pte
r_extern
id|__inline__
r_int
r_int
id|sun4c_get_pte
c_func
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
l_string|&quot;&bslash;n&bslash;tlda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|entry
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PTE
)paren
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|function|sun4c_put_pte
r_extern
id|__inline__
r_void
id|sun4c_put_pte
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|entry
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tsta %1, [%0] %2; nop; nop; nop;&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
(paren
id|entry
op_amp
op_complement
(paren
id|_SUN4C_PAGE_PRESENT
)paren
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PTE
)paren
)paren
suffix:semicolon
)brace
DECL|function|sun4c_get_context
r_extern
id|__inline__
r_int
id|sun4c_get_context
c_func
(paren
r_void
)paren
(brace
r_register
r_int
id|ctx
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tlduba [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ctx
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|AC_CONTEXT
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
)paren
suffix:semicolon
r_return
id|ctx
suffix:semicolon
)brace
DECL|function|sun4c_set_context
r_extern
id|__inline__
r_int
id|sun4c_set_context
c_func
(paren
r_int
id|ctx
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;tstba %0, [%1] %2; nop; nop; nop;&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|ctx
)paren
comma
l_string|&quot;r&quot;
(paren
id|AC_CONTEXT
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
)paren
suffix:semicolon
r_return
id|ctx
suffix:semicolon
)brace
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(_SPARC_PGTSUN4_H) */
eof
