multiline_comment|/*&n; * highmem.h: virtual kernel memory mappings for high memory&n; *&n; * Used in CONFIG_HIGHMEM systems for memory pages which&n; * are not addressable by direct kernel virtual addresses.&n; *&n; * Copyright (C) 1999 Gerhard Wichert, Siemens AG&n; *&t;&t;      Gerhard.Wichert@pdb.siemens.de&n; *&n; *&n; * Redesigned the x86 32-bit VM architecture to deal with &n; * up to 16 Terrabyte physical memory. With current x86 CPUs&n; * we now support up to 64 Gigabytes physical RAM.&n; *&n; * Copyright (C) 1999 Ingo Molnar &lt;mingo@redhat.com&gt;&n; */
macro_line|#ifndef _ASM_HIGHMEM_H
DECL|macro|_ASM_HIGHMEM_H
mdefine_line|#define _ASM_HIGHMEM_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
macro_line|#include &lt;asm/kmap_types.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/* declarations for highmem.c */
r_extern
r_int
r_int
id|highstart_pfn
comma
id|highend_pfn
suffix:semicolon
r_extern
id|pte_t
op_star
id|kmap_pte
suffix:semicolon
r_extern
id|pgprot_t
id|kmap_prot
suffix:semicolon
r_extern
id|pte_t
op_star
id|pkmap_page_table
suffix:semicolon
r_extern
r_void
id|kmap_init
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
multiline_comment|/*&n; * Right now we initialize only a single pte table. It can be extended&n; * easily, subsequent pte tables have to be allocated in one physical&n; * chunk of RAM.  Currently the simplest way to do this is to align the&n; * pkmap region on a pagetable boundary (4MB).&n; */
DECL|macro|LAST_PKMAP
mdefine_line|#define LAST_PKMAP 1024
DECL|macro|PKMAP_SIZE
mdefine_line|#define PKMAP_SIZE (LAST_PKMAP &lt;&lt; PAGE_SHIFT)
DECL|macro|PKMAP_BASE
mdefine_line|#define PKMAP_BASE PMD_ALIGN(SRMMU_NOCACHE_VADDR + (SRMMU_MAX_NOCACHE_PAGES &lt;&lt; PAGE_SHIFT))
DECL|macro|LAST_PKMAP_MASK
mdefine_line|#define LAST_PKMAP_MASK (LAST_PKMAP - 1)
DECL|macro|PKMAP_NR
mdefine_line|#define PKMAP_NR(virt)  ((virt - PKMAP_BASE) &gt;&gt; PAGE_SHIFT)
DECL|macro|PKMAP_ADDR
mdefine_line|#define PKMAP_ADDR(nr)  (PKMAP_BASE + ((nr) &lt;&lt; PAGE_SHIFT))
DECL|macro|PKMAP_END
mdefine_line|#define PKMAP_END (PKMAP_ADDR(LAST_PKMAP))
r_extern
r_void
op_star
id|kmap_high
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
id|kunmap_high
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
DECL|function|kmap
r_static
r_inline
r_void
op_star
id|kmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|BUG_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|kmap_high
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|kunmap
r_static
r_inline
r_void
id|kunmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|BUG_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
r_return
suffix:semicolon
id|kunmap_high
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_extern
r_void
op_star
id|kmap_atomic
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_enum
id|km_type
id|type
)paren
suffix:semicolon
r_extern
r_void
id|kunmap_atomic
c_func
(paren
r_void
op_star
id|kvaddr
comma
r_enum
id|km_type
id|type
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|kmap_atomic_to_page
c_func
(paren
r_void
op_star
id|vaddr
)paren
suffix:semicolon
DECL|macro|flush_cache_kmaps
mdefine_line|#define flush_cache_kmaps()&t;flush_cache_all()
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_HIGHMEM_H */
eof
