multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * highmem.h: virtual kernel memory mappings for high memory&n; *&n; * PowerPC version, stolen from the i386 version.&n; *&n; * Used in CONFIG_HIGHMEM systems for memory pages which&n; * are not addressable by direct kernel virtual addresses.&n; *&n; * Copyright (C) 1999 Gerhard Wichert, Siemens AG&n; *&t;&t;      Gerhard.Wichert@pdb.siemens.de&n; *&n; *&n; * Redesigned the x86 32-bit VM architecture to deal with &n; * up to 16 Terrabyte physical memory. With current x86 CPUs&n; * we now support up to 64 Gigabytes physical RAM.&n; *&n; * Copyright (C) 1999 Ingo Molnar &lt;mingo@redhat.com&gt;&n; */
macro_line|#ifndef _ASM_HIGHMEM_H
DECL|macro|_ASM_HIGHMEM_H
mdefine_line|#define _ASM_HIGHMEM_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/kmap_types.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/* undef for production */
DECL|macro|HIGHMEM_DEBUG
mdefine_line|#define HIGHMEM_DEBUG 1
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
multiline_comment|/*&n; * Right now we initialize only a single pte table. It can be extended&n; * easily, subsequent pte tables have to be allocated in one physical&n; * chunk of RAM.&n; */
macro_line|#ifdef CONFIG_HIGHMEM_START_BOOL
DECL|macro|PKMAP_BASE
mdefine_line|#define PKMAP_BASE CONFIG_HIGHMEM_START
macro_line|#else
DECL|macro|PKMAP_BASE
mdefine_line|#define PKMAP_BASE (0xfe000000UL)
macro_line|#endif /* CONFIG_HIGHMEM_START_BOOL */
DECL|macro|LAST_PKMAP
mdefine_line|#define LAST_PKMAP 1024
DECL|macro|LAST_PKMAP_MASK
mdefine_line|#define LAST_PKMAP_MASK (LAST_PKMAP-1)
DECL|macro|PKMAP_NR
mdefine_line|#define PKMAP_NR(virt)  ((virt-PKMAP_BASE) &gt;&gt; PAGE_SHIFT)
DECL|macro|PKMAP_ADDR
mdefine_line|#define PKMAP_ADDR(nr)  (PKMAP_BASE + ((nr) &lt;&lt; PAGE_SHIFT))
DECL|macro|KMAP_FIX_BEGIN
mdefine_line|#define KMAP_FIX_BEGIN&t;(PKMAP_BASE + 0x00400000UL)
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
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
OL
id|highmem_start_page
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
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
OL
id|highmem_start_page
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
multiline_comment|/*&n; * The use of kmap_atomic/kunmap_atomic is discouraged - kmap/kunmap&n; * gives a more generic (and caching) interface. But kmap_atomic can&n; * be used in IRQ contexts, so in some (very limited) cases we need&n; * it.&n; */
DECL|function|kmap_atomic
r_static
r_inline
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
(brace
r_int
r_int
id|idx
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
id|inc_preempt_count
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
OL
id|highmem_start_page
)paren
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|idx
op_assign
id|type
op_plus
id|KM_TYPE_NR
op_star
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|vaddr
op_assign
id|KMAP_FIX_BEGIN
op_plus
id|idx
op_star
id|PAGE_SIZE
suffix:semicolon
macro_line|#if HIGHMEM_DEBUG
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
(paren
id|kmap_pte
op_plus
id|idx
)paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|set_pte
c_func
(paren
id|kmap_pte
op_plus
id|idx
comma
id|mk_pte
c_func
(paren
id|page
comma
id|kmap_prot
)paren
)paren
suffix:semicolon
id|flush_tlb_page
c_func
(paren
l_int|0
comma
id|vaddr
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|vaddr
suffix:semicolon
)brace
DECL|function|kunmap_atomic
r_static
r_inline
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
(brace
macro_line|#if HIGHMEM_DEBUG
r_int
r_int
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|kvaddr
op_amp
id|PAGE_MASK
suffix:semicolon
r_int
r_int
id|idx
op_assign
id|type
op_plus
id|KM_TYPE_NR
op_star
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vaddr
OL
id|KMAP_FIX_BEGIN
)paren
(brace
singleline_comment|// FIXME
id|dec_preempt_count
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vaddr
op_ne
id|KMAP_FIX_BEGIN
op_plus
id|idx
op_star
id|PAGE_SIZE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * force other mappings to Oops if they&squot;ll try to access&n;&t; * this pte without first remap it&n;&t; */
id|pte_clear
c_func
(paren
id|kmap_pte
op_plus
id|idx
)paren
suffix:semicolon
id|flush_tlb_page
c_func
(paren
l_int|0
comma
id|vaddr
)paren
suffix:semicolon
macro_line|#endif
id|dec_preempt_count
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_HIGHMEM_H */
eof
