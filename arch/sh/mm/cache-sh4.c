multiline_comment|/* $Id: cache-sh4.c,v 1.16 2001/09/10 11:06:35 dwmw2 Exp $&n; *&n; *  linux/arch/sh/mm/cache.c&n; *&n; * Copyright (C) 1999, 2000  Niibe Yutaka&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
DECL|macro|CCR
mdefine_line|#define CCR&t;&t; 0xff00001c&t;/* Address of Cache Control Register */
DECL|macro|CCR_CACHE_OCE
mdefine_line|#define CCR_CACHE_OCE&t;0x0001&t;/* Operand Cache Enable */
DECL|macro|CCR_CACHE_WT
mdefine_line|#define CCR_CACHE_WT&t;0x0002&t;/* Write-Through (for P0,U0,P3) (else writeback)*/
DECL|macro|CCR_CACHE_CB
mdefine_line|#define CCR_CACHE_CB&t;0x0004&t;/* Copy-Back (for P1) (else writethrough) */
DECL|macro|CCR_CACHE_OCI
mdefine_line|#define CCR_CACHE_OCI&t;0x0008&t;/* OC Invalidate */
DECL|macro|CCR_CACHE_ORA
mdefine_line|#define CCR_CACHE_ORA&t;0x0020&t;/* OC RAM Mode */
DECL|macro|CCR_CACHE_OIX
mdefine_line|#define CCR_CACHE_OIX&t;0x0080&t;/* OC Index Enable */
DECL|macro|CCR_CACHE_ICE
mdefine_line|#define CCR_CACHE_ICE&t;0x0100&t;/* Instruction Cache Enable */
DECL|macro|CCR_CACHE_ICI
mdefine_line|#define CCR_CACHE_ICI&t;0x0800&t;/* IC Invalidate */
DECL|macro|CCR_CACHE_IIX
mdefine_line|#define CCR_CACHE_IIX&t;0x8000&t;/* IC Index Enable */
multiline_comment|/* Default CCR setup: 8k+16k-byte cache,P1-wb,enable */
DECL|macro|CCR_CACHE_VAL
mdefine_line|#define CCR_CACHE_VAL&t;(CCR_CACHE_ICE|CCR_CACHE_CB|CCR_CACHE_OCE)
DECL|macro|CCR_CACHE_INIT
mdefine_line|#define CCR_CACHE_INIT&t;(CCR_CACHE_VAL|CCR_CACHE_OCI|CCR_CACHE_ICI)
DECL|macro|CCR_CACHE_ENABLE
mdefine_line|#define CCR_CACHE_ENABLE (CCR_CACHE_OCE|CCR_CACHE_ICE)
DECL|macro|CACHE_IC_ADDRESS_ARRAY
mdefine_line|#define CACHE_IC_ADDRESS_ARRAY 0xf0000000
DECL|macro|CACHE_OC_ADDRESS_ARRAY
mdefine_line|#define CACHE_OC_ADDRESS_ARRAY 0xf4000000
DECL|macro|CACHE_VALID
mdefine_line|#define CACHE_VALID&t;  1
DECL|macro|CACHE_UPDATED
mdefine_line|#define CACHE_UPDATED&t;  2
DECL|macro|CACHE_OC_WAY_SHIFT
mdefine_line|#define CACHE_OC_WAY_SHIFT       13
DECL|macro|CACHE_IC_WAY_SHIFT
mdefine_line|#define CACHE_IC_WAY_SHIFT       13
DECL|macro|CACHE_OC_ENTRY_SHIFT
mdefine_line|#define CACHE_OC_ENTRY_SHIFT      5
DECL|macro|CACHE_IC_ENTRY_SHIFT
mdefine_line|#define CACHE_IC_ENTRY_SHIFT      5
DECL|macro|CACHE_OC_ENTRY_MASK
mdefine_line|#define CACHE_OC_ENTRY_MASK&t;&t;0x3fe0
DECL|macro|CACHE_OC_ENTRY_PHYS_MASK
mdefine_line|#define CACHE_OC_ENTRY_PHYS_MASK&t;0x0fe0
DECL|macro|CACHE_IC_ENTRY_MASK
mdefine_line|#define CACHE_IC_ENTRY_MASK&t;&t;0x1fe0
DECL|macro|CACHE_IC_NUM_ENTRIES
mdefine_line|#define CACHE_IC_NUM_ENTRIES&t;256
DECL|macro|CACHE_OC_NUM_ENTRIES
mdefine_line|#define CACHE_OC_NUM_ENTRIES&t;512
r_static
r_void
id|__init
DECL|function|detect_cpu_and_cache_system
id|detect_cpu_and_cache_system
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_CPU_SUBTYPE_ST40STB1
id|cpu_data-&gt;type
op_assign
id|CPU_ST40STB1
suffix:semicolon
macro_line|#elif defined(CONFIG_CPU_SUBTYPE_SH7750) || defined(CONFIG_CPU_SUBTYPE_SH7751)
id|cpu_data-&gt;type
op_assign
id|CPU_SH7750
suffix:semicolon
macro_line|#else
macro_line|#error Unknown SH4 CPU type
macro_line|#endif
)brace
DECL|function|cache_init
r_void
id|__init
id|cache_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ccr
suffix:semicolon
id|detect_cpu_and_cache_system
c_func
(paren
)paren
suffix:semicolon
id|jump_to_P2
c_func
(paren
)paren
suffix:semicolon
id|ccr
op_assign
id|ctrl_inl
c_func
(paren
id|CCR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccr
op_amp
id|CCR_CACHE_ENABLE
)paren
(brace
multiline_comment|/*&n;&t;&t; * XXX: Should check RA here. &n;&t;&t; * If RA was 1, we only need to flush the half of the caches.&n;&t;&t; */
r_int
r_int
id|addr
comma
id|data
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|CACHE_OC_ADDRESS_ARRAY
suffix:semicolon
id|addr
OL
(paren
id|CACHE_OC_ADDRESS_ARRAY
op_plus
(paren
id|CACHE_OC_NUM_ENTRIES
op_lshift
id|CACHE_OC_ENTRY_SHIFT
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
(paren
l_int|1
op_lshift
id|CACHE_OC_ENTRY_SHIFT
)paren
)paren
(brace
id|data
op_assign
id|ctrl_inl
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|data
op_amp
(paren
id|CACHE_UPDATED
op_or
id|CACHE_VALID
)paren
)paren
op_eq
(paren
id|CACHE_UPDATED
op_or
id|CACHE_VALID
)paren
)paren
id|ctrl_outl
c_func
(paren
id|data
op_amp
op_complement
id|CACHE_UPDATED
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
id|ctrl_outl
c_func
(paren
id|CCR_CACHE_INIT
comma
id|CCR
)paren
suffix:semicolon
id|back_to_P1
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * SH-4 has virtually indexed and physically tagged cache.&n; */
DECL|variable|p3map_sem
r_static
r_struct
id|semaphore
id|p3map_sem
(braket
l_int|4
)braket
suffix:semicolon
DECL|function|p3_cache_init
r_void
id|__init
id|p3_cache_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* In ioremap.c */
r_extern
r_int
id|remap_area_pages
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remap_area_pages
c_func
(paren
id|P3SEG
comma
l_int|0
comma
id|PAGE_SIZE
op_star
l_int|4
comma
id|_PAGE_CACHABLE
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;p3_cachie_init failed.&quot;
)paren
suffix:semicolon
id|sema_init
(paren
op_amp
id|p3map_sem
(braket
l_int|0
)braket
comma
l_int|1
)paren
suffix:semicolon
id|sema_init
(paren
op_amp
id|p3map_sem
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
id|sema_init
(paren
op_amp
id|p3map_sem
(braket
l_int|2
)braket
comma
l_int|1
)paren
suffix:semicolon
id|sema_init
(paren
op_amp
id|p3map_sem
(braket
l_int|3
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back the dirty D-caches, but not invalidate them.&n; *&n; * START: Virtual Address (U0, P1, or P3)&n; * SIZE: Size of the region.&n; */
DECL|function|__flush_wback_region
r_void
id|__flush_wback_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|v
suffix:semicolon
r_int
r_int
id|begin
comma
id|end
suffix:semicolon
id|begin
op_assign
(paren
r_int
r_int
)paren
id|start
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
(paren
r_int
r_int
)paren
id|start
op_plus
id|size
op_plus
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|v
op_assign
id|begin
suffix:semicolon
id|v
OL
id|end
suffix:semicolon
id|v
op_add_assign
id|L1_CACHE_BYTES
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;ocbwb&t;%0&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|v
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Write back the dirty D-caches and invalidate them.&n; *&n; * START: Virtual Address (U0, P1, or P3)&n; * SIZE: Size of the region.&n; */
DECL|function|__flush_purge_region
r_void
id|__flush_purge_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|v
suffix:semicolon
r_int
r_int
id|begin
comma
id|end
suffix:semicolon
id|begin
op_assign
(paren
r_int
r_int
)paren
id|start
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
(paren
r_int
r_int
)paren
id|start
op_plus
id|size
op_plus
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|v
op_assign
id|begin
suffix:semicolon
id|v
OL
id|end
suffix:semicolon
id|v
op_add_assign
id|L1_CACHE_BYTES
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;ocbp&t;%0&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|v
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * No write back please&n; */
DECL|function|__flush_invalidate_region
r_void
id|__flush_invalidate_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|v
suffix:semicolon
r_int
r_int
id|begin
comma
id|end
suffix:semicolon
id|begin
op_assign
(paren
r_int
r_int
)paren
id|start
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
(paren
r_int
r_int
)paren
id|start
op_plus
id|size
op_plus
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|v
op_assign
id|begin
suffix:semicolon
id|v
OL
id|end
suffix:semicolon
id|v
op_add_assign
id|L1_CACHE_BYTES
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;ocbi&t;%0&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|v
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Write back the range of D-cache, and purge the I-cache.&n; *&n; * Called from kernel/module.c:sys_init_module and routine for a.out format.&n; */
DECL|function|flush_icache_range
r_void
id|flush_icache_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back the D-cache and purge the I-cache for signal trampoline. &n; */
DECL|function|flush_cache_sigtramp
r_void
id|flush_cache_sigtramp
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|v
comma
id|index
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|v
op_assign
id|addr
op_amp
op_complement
(paren
id|L1_CACHE_BYTES
op_minus
l_int|1
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;ocbwb&t;%0&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;m&quot;
(paren
id|__m
c_func
(paren
id|v
)paren
)paren
)paren
suffix:semicolon
id|index
op_assign
id|CACHE_IC_ADDRESS_ARRAY
op_or
(paren
id|v
op_amp
id|CACHE_IC_ENTRY_MASK
)paren
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|jump_to_P2
c_func
(paren
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|index
)paren
suffix:semicolon
multiline_comment|/* Clear out Valid-bit */
id|back_to_P1
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Writeback&amp;Invalidate the D-cache of the page&n; */
DECL|function|__flush_dcache_page
r_static
r_void
id|__flush_dcache_page
c_func
(paren
r_int
r_int
id|phys
)paren
(brace
r_int
r_int
id|addr
comma
id|data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|phys
op_or_assign
id|CACHE_VALID
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|jump_to_P2
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Loop all the D-cache */
r_for
c_loop
(paren
id|addr
op_assign
id|CACHE_OC_ADDRESS_ARRAY
suffix:semicolon
id|addr
OL
(paren
id|CACHE_OC_ADDRESS_ARRAY
op_plus
(paren
id|CACHE_OC_NUM_ENTRIES
op_lshift
id|CACHE_OC_ENTRY_SHIFT
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
(paren
l_int|1
op_lshift
id|CACHE_OC_ENTRY_SHIFT
)paren
)paren
(brace
id|data
op_assign
id|ctrl_inl
c_func
(paren
id|addr
)paren
op_amp
(paren
l_int|0x1ffff000
op_or
id|CACHE_VALID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
id|phys
)paren
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|addr
)paren
suffix:semicolon
)brace
macro_line|#if 0 /* DEBUG DEBUG */
multiline_comment|/* Loop all the I-cache */
r_for
c_loop
(paren
id|addr
op_assign
id|CACHE_IC_ADDRESS_ARRAY
suffix:semicolon
id|addr
OL
(paren
id|CACHE_IC_ADDRESS_ARRAY
op_plus
(paren
id|CACHE_IC_NUM_ENTRIES
op_lshift
id|CACHE_IC_ENTRY_SHIFT
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
(paren
l_int|1
op_lshift
id|CACHE_IC_ENTRY_SHIFT
)paren
)paren
(brace
id|data
op_assign
id|ctrl_inl
c_func
(paren
id|addr
)paren
op_amp
(paren
l_int|0x1ffff000
op_or
id|CACHE_VALID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
id|phys
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;__flush_cache_page: I-cache entry found&bslash;n&quot;
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|back_to_P1
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back &amp; invalidate the D-cache of the page.&n; * (To avoid &quot;alias&quot; issues)&n; */
DECL|function|flush_dcache_page
r_void
id|flush_dcache_page
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
id|test_bit
c_func
(paren
id|PG_mapped
comma
op_amp
id|page-&gt;flags
)paren
)paren
id|__flush_dcache_page
c_func
(paren
id|PHYSADDR
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|flush_cache_all
r_void
id|flush_cache_all
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Prefetch the data to write back D-cache */
r_for
c_loop
(paren
id|addr
op_assign
(paren
r_int
r_int
)paren
id|empty_zero_page
suffix:semicolon
id|addr
OL
(paren
r_int
r_int
)paren
id|empty_zero_page
op_plus
l_int|1024
op_star
l_int|16
suffix:semicolon
id|addr
op_add_assign
id|L1_CACHE_BYTES
)paren
id|asm
r_volatile
(paren
l_string|&quot;pref @%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
id|jump_to_P2
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush D-cache/I-cache */
id|ctrl_outl
c_func
(paren
id|CCR_CACHE_INIT
comma
id|CCR
)paren
suffix:semicolon
id|back_to_P1
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|flush_cache_mm
r_void
id|flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/* Is there any good way? */
multiline_comment|/* XXX: possibly call flush_cache_range for each vm area */
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back and invalidate D-caches.&n; *&n; * START, END: Virtual Address (U0 address)&n; *&n; * NOTE: We need to flush the _physical_ page entry.&n; * Flushing the cache lines for U0 only isn&squot;t enough.&n; * We need to flush for P1 too, which may contain aliases.&n; */
DECL|function|flush_cache_range
r_void
id|flush_cache_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
multiline_comment|/*&n;&t; * We could call flush_cache_page for the pages of these range,&n;&t; * but it&squot;s not efficient (scan the caches all the time...).&n;&t; *&n;&t; * We can&squot;t use A-bit magic, as there&squot;s the case we don&squot;t have&n;&t; * valid entry on TLB.&n;&t; */
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back and invalidate I/D-caches for the page.&n; *&n; * ADDR: Virtual Address (U0 address)&n; */
DECL|function|flush_cache_page
r_void
id|flush_cache_page
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
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte_t
id|entry
suffix:semicolon
r_int
r_int
id|phys
comma
id|addr
comma
id|data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
comma
id|address
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
op_logical_or
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
r_return
suffix:semicolon
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|entry
op_assign
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
id|pte_none
c_func
(paren
id|entry
)paren
op_logical_or
op_logical_neg
id|pte_present
c_func
(paren
id|entry
)paren
)paren
r_return
suffix:semicolon
id|phys
op_assign
id|pte_val
c_func
(paren
id|entry
)paren
op_amp
id|PTE_PHYS_MASK
suffix:semicolon
id|phys
op_or_assign
id|CACHE_VALID
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|jump_to_P2
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We only need to flush D-cache when we have alias */
r_if
c_cond
(paren
(paren
id|address
op_xor
id|phys
)paren
op_amp
id|CACHE_ALIAS
)paren
(brace
multiline_comment|/* Loop 4K of the D-cache */
r_for
c_loop
(paren
id|addr
op_assign
id|CACHE_OC_ADDRESS_ARRAY
op_or
(paren
id|address
op_amp
id|CACHE_ALIAS
)paren
suffix:semicolon
id|addr
OL
(paren
id|CACHE_OC_ADDRESS_ARRAY
op_plus
(paren
id|address
op_amp
id|CACHE_ALIAS
)paren
op_plus
(paren
id|CACHE_OC_NUM_ENTRIES
op_div
l_int|4
op_lshift
id|CACHE_OC_ENTRY_SHIFT
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
(paren
l_int|1
op_lshift
id|CACHE_OC_ENTRY_SHIFT
)paren
)paren
(brace
id|data
op_assign
id|ctrl_inl
c_func
(paren
id|addr
)paren
op_amp
(paren
l_int|0x1ffff000
op_or
id|CACHE_VALID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
id|phys
)paren
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Loop another 4K of the D-cache */
r_for
c_loop
(paren
id|addr
op_assign
id|CACHE_OC_ADDRESS_ARRAY
op_or
(paren
id|phys
op_amp
id|CACHE_ALIAS
)paren
suffix:semicolon
id|addr
OL
(paren
id|CACHE_OC_ADDRESS_ARRAY
op_plus
(paren
id|phys
op_amp
id|CACHE_ALIAS
)paren
op_plus
(paren
id|CACHE_OC_NUM_ENTRIES
op_div
l_int|4
op_lshift
id|CACHE_OC_ENTRY_SHIFT
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
(paren
l_int|1
op_lshift
id|CACHE_OC_ENTRY_SHIFT
)paren
)paren
(brace
id|data
op_assign
id|ctrl_inl
c_func
(paren
id|addr
)paren
op_amp
(paren
l_int|0x1ffff000
op_or
id|CACHE_VALID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
id|phys
)paren
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
multiline_comment|/* Loop 4K of the I-cache */
r_for
c_loop
(paren
id|addr
op_assign
id|CACHE_IC_ADDRESS_ARRAY
op_or
(paren
id|address
op_amp
l_int|0x1000
)paren
suffix:semicolon
id|addr
OL
(paren
(paren
id|CACHE_IC_ADDRESS_ARRAY
op_or
(paren
id|address
op_amp
l_int|0x1000
)paren
)paren
op_plus
(paren
id|CACHE_IC_NUM_ENTRIES
op_div
l_int|2
op_lshift
id|CACHE_IC_ENTRY_SHIFT
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
(paren
l_int|1
op_lshift
id|CACHE_IC_ENTRY_SHIFT
)paren
)paren
(brace
id|data
op_assign
id|ctrl_inl
c_func
(paren
id|addr
)paren
op_amp
(paren
l_int|0x1ffff000
op_or
id|CACHE_VALID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
id|phys
)paren
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|addr
)paren
suffix:semicolon
)brace
id|back_to_P1
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * clear_user_page&n; * @to: P1 address&n; * @address: U0 address to be mapped&n; */
DECL|function|clear_user_page
r_void
id|clear_user_page
c_func
(paren
r_void
op_star
id|to
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|to
)paren
suffix:semicolon
id|__set_bit
c_func
(paren
id|PG_mapped
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|address
op_xor
(paren
r_int
r_int
)paren
id|to
)paren
op_amp
id|CACHE_ALIAS
)paren
op_eq
l_int|0
)paren
id|clear_page
c_func
(paren
id|to
)paren
suffix:semicolon
r_else
(brace
id|pgprot_t
id|pgprot
op_assign
id|__pgprot
c_func
(paren
id|_PAGE_PRESENT
op_or
id|_PAGE_RW
op_or
id|_PAGE_CACHABLE
op_or
id|_PAGE_DIRTY
op_or
id|_PAGE_ACCESSED
op_or
id|_PAGE_HW_SHARED
op_or
id|_PAGE_FLAGS_HARD
)paren
suffix:semicolon
r_int
r_int
id|phys_addr
op_assign
id|PHYSADDR
c_func
(paren
id|to
)paren
suffix:semicolon
r_int
r_int
id|p3_addr
op_assign
id|P3SEG
op_plus
(paren
id|address
op_amp
id|CACHE_ALIAS
)paren
suffix:semicolon
id|pgd_t
op_star
id|dir
op_assign
id|pgd_offset_k
c_func
(paren
id|p3_addr
)paren
suffix:semicolon
id|pmd_t
op_star
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|p3_addr
)paren
suffix:semicolon
id|pte_t
op_star
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
id|p3_addr
)paren
suffix:semicolon
id|pte_t
id|entry
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|entry
op_assign
id|pfn_pte
c_func
(paren
id|phys_addr
op_rshift
id|PAGE_SHIFT
comma
id|pgprot
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|p3map_sem
(braket
(paren
id|address
op_amp
id|CACHE_ALIAS
)paren
op_rshift
l_int|12
)braket
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|entry
)paren
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__flush_tlb_page
c_func
(paren
id|get_asid
c_func
(paren
)paren
comma
id|p3_addr
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|update_mmu_cache
c_func
(paren
l_int|NULL
comma
id|p3_addr
comma
id|entry
)paren
suffix:semicolon
id|__clear_user_page
c_func
(paren
(paren
r_void
op_star
)paren
id|p3_addr
comma
id|to
)paren
suffix:semicolon
id|pte_clear
c_func
(paren
id|pte
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|p3map_sem
(braket
(paren
id|address
op_amp
id|CACHE_ALIAS
)paren
op_rshift
l_int|12
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * copy_user_page&n; * @to: P1 address&n; * @from: P1 address&n; * @address: U0 address to be mapped&n; */
DECL|function|copy_user_page
r_void
id|copy_user_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|to
)paren
suffix:semicolon
id|__set_bit
c_func
(paren
id|PG_mapped
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|address
op_xor
(paren
r_int
r_int
)paren
id|to
)paren
op_amp
id|CACHE_ALIAS
)paren
op_eq
l_int|0
)paren
id|copy_page
c_func
(paren
id|to
comma
id|from
)paren
suffix:semicolon
r_else
(brace
id|pgprot_t
id|pgprot
op_assign
id|__pgprot
c_func
(paren
id|_PAGE_PRESENT
op_or
id|_PAGE_RW
op_or
id|_PAGE_CACHABLE
op_or
id|_PAGE_DIRTY
op_or
id|_PAGE_ACCESSED
op_or
id|_PAGE_HW_SHARED
op_or
id|_PAGE_FLAGS_HARD
)paren
suffix:semicolon
r_int
r_int
id|phys_addr
op_assign
id|PHYSADDR
c_func
(paren
id|to
)paren
suffix:semicolon
r_int
r_int
id|p3_addr
op_assign
id|P3SEG
op_plus
(paren
id|address
op_amp
id|CACHE_ALIAS
)paren
suffix:semicolon
id|pgd_t
op_star
id|dir
op_assign
id|pgd_offset_k
c_func
(paren
id|p3_addr
)paren
suffix:semicolon
id|pmd_t
op_star
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|p3_addr
)paren
suffix:semicolon
id|pte_t
op_star
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
id|p3_addr
)paren
suffix:semicolon
id|pte_t
id|entry
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|entry
op_assign
id|pfn_pte
c_func
(paren
id|phys_addr
op_rshift
id|PAGE_SHIFT
comma
id|pgprot
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|p3map_sem
(braket
(paren
id|address
op_amp
id|CACHE_ALIAS
)paren
op_rshift
l_int|12
)braket
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|entry
)paren
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__flush_tlb_page
c_func
(paren
id|get_asid
c_func
(paren
)paren
comma
id|p3_addr
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|update_mmu_cache
c_func
(paren
l_int|NULL
comma
id|p3_addr
comma
id|entry
)paren
suffix:semicolon
id|__copy_user_page
c_func
(paren
(paren
r_void
op_star
)paren
id|p3_addr
comma
id|from
comma
id|to
)paren
suffix:semicolon
id|pte_clear
c_func
(paren
id|pte
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|p3map_sem
(braket
(paren
id|address
op_amp
id|CACHE_ALIAS
)paren
op_rshift
l_int|12
)braket
)paren
suffix:semicolon
)brace
)brace
eof
