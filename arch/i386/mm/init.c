multiline_comment|/*&n; *  linux/arch/i386/mm/init.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *&n; *  Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/hugetlb.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/e820.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
DECL|variable|mmu_gathers
id|mmu_gather_t
id|mmu_gathers
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|highstart_pfn
DECL|variable|highend_pfn
r_int
r_int
id|highstart_pfn
comma
id|highend_pfn
suffix:semicolon
multiline_comment|/*&n; * Creates a middle page table and puts a pointer to it in the&n; * given global directory entry. This only returns the gd entry&n; * in non-PAE compilation mode, since the middle layer is folded.&n; */
DECL|function|one_md_table_init
r_static
id|pmd_t
op_star
id|__init
id|one_md_table_init
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|pmd_t
op_star
id|pmd_table
suffix:semicolon
macro_line|#if CONFIG_X86_PAE
id|pmd_table
op_assign
(paren
id|pmd_t
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_pgd
c_func
(paren
id|pgd
comma
id|__pgd
c_func
(paren
id|__pa
c_func
(paren
id|pmd_table
)paren
op_or
id|_PAGE_PRESENT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_table
op_ne
id|pmd_offset
c_func
(paren
id|pgd
comma
l_int|0
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
id|pmd_table
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_return
id|pmd_table
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a page table and place a pointer to it in a middle page&n; * directory entry.&n; */
DECL|function|one_page_table_init
r_static
id|pte_t
op_star
id|__init
id|one_page_table_init
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
id|pte_t
op_star
id|page_table
op_assign
(paren
id|pte_t
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|__pa
c_func
(paren
id|page_table
)paren
op_or
id|_KERNPG_TABLE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page_table
op_ne
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
l_int|0
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
id|page_table
suffix:semicolon
)brace
multiline_comment|/*&n; * This function initializes a certain range of kernel virtual memory &n; * with new bootmem page tables, everywhere page tables are missing in&n; * the given range.&n; */
multiline_comment|/*&n; * NOTE: The pagetables are allocated contiguous on the physical space &n; * so we can cache the place of the first one and move around without &n; * checking the pgd every time.&n; */
DECL|function|page_table_range_init
r_static
r_void
id|__init
id|page_table_range_init
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
id|pgd_t
op_star
id|pgd_base
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
id|pgd_ofs
comma
id|pmd_ofs
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
id|vaddr
op_assign
id|start
suffix:semicolon
id|pgd_ofs
op_assign
id|__pgd_offset
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pmd_ofs
op_assign
id|__pmd_offset
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_base
op_plus
id|pgd_ofs
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|pgd_ofs
OL
id|PTRS_PER_PGD
)paren
op_logical_and
(paren
id|vaddr
op_ne
id|end
)paren
suffix:semicolon
id|pgd
op_increment
comma
id|pgd_ofs
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
id|one_md_table_init
c_func
(paren
id|pgd
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|vaddr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|pmd_ofs
OL
id|PTRS_PER_PMD
)paren
op_logical_and
(paren
id|vaddr
op_ne
id|end
)paren
suffix:semicolon
id|pmd
op_increment
comma
id|pmd_ofs
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
id|one_page_table_init
c_func
(paren
id|pmd
)paren
suffix:semicolon
id|vaddr
op_add_assign
id|PMD_SIZE
suffix:semicolon
)brace
id|pmd_ofs
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This maps the physical memory to kernel virtual address space, a total &n; * of max_low_pfn pages, by creating page tables starting from address &n; * PAGE_OFFSET.&n; */
DECL|function|kernel_physical_mapping_init
r_static
r_void
id|__init
id|kernel_physical_mapping_init
c_func
(paren
id|pgd_t
op_star
id|pgd_base
)paren
(brace
r_int
r_int
id|pfn
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|pgd_ofs
comma
id|pmd_ofs
comma
id|pte_ofs
suffix:semicolon
id|pgd_ofs
op_assign
id|__pgd_offset
c_func
(paren
id|PAGE_OFFSET
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_base
op_plus
id|pgd_ofs
suffix:semicolon
id|pfn
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|pgd_ofs
OL
id|PTRS_PER_PGD
op_logical_and
id|pfn
OL
id|max_low_pfn
suffix:semicolon
id|pgd
op_increment
comma
id|pgd_ofs
op_increment
)paren
(brace
id|pmd
op_assign
id|one_md_table_init
c_func
(paren
id|pgd
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pmd_ofs
op_assign
l_int|0
suffix:semicolon
id|pmd_ofs
OL
id|PTRS_PER_PMD
op_logical_and
id|pfn
OL
id|max_low_pfn
suffix:semicolon
id|pmd
op_increment
comma
id|pmd_ofs
op_increment
)paren
(brace
multiline_comment|/* Map with big pages if possible, otherwise create normal page tables. */
r_if
c_cond
(paren
id|cpu_has_pse
)paren
(brace
id|set_pmd
c_func
(paren
id|pmd
comma
id|pfn_pmd
c_func
(paren
id|pfn
comma
id|PAGE_KERNEL_LARGE
)paren
)paren
suffix:semicolon
id|pfn
op_add_assign
id|PTRS_PER_PTE
suffix:semicolon
)brace
r_else
(brace
id|pte
op_assign
id|one_page_table_init
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pte_ofs
op_assign
l_int|0
suffix:semicolon
id|pte_ofs
OL
id|PTRS_PER_PTE
op_logical_and
id|pfn
OL
id|max_low_pfn
suffix:semicolon
id|pte
op_increment
comma
id|pfn
op_increment
comma
id|pte_ofs
op_increment
)paren
id|set_pte
c_func
(paren
id|pte
comma
id|pfn_pte
c_func
(paren
id|pfn
comma
id|PAGE_KERNEL
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|page_kills_ppro
r_static
r_inline
r_int
id|page_kills_ppro
c_func
(paren
r_int
r_int
id|pagenr
)paren
(brace
r_if
c_cond
(paren
id|pagenr
op_ge
l_int|0x70000
op_logical_and
id|pagenr
op_le
l_int|0x7003F
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|page_is_ram
r_static
r_inline
r_int
id|page_is_ram
c_func
(paren
r_int
r_int
id|pagenr
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|e820.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|addr
comma
id|end
suffix:semicolon
r_if
c_cond
(paren
id|e820.map
(braket
id|i
)braket
dot
id|type
op_ne
id|E820_RAM
)paren
multiline_comment|/* not usable memory */
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;!!!FIXME!!! Some BIOSen report areas as RAM that&n;&t;&t; *&t;are not. Notably the 640-&gt;1Mb area. We need a sanity&n;&t;&t; *&t;check here.&n;&t;&t; */
id|addr
op_assign
(paren
id|e820.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|end
op_assign
(paren
id|e820.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|e820.map
(braket
id|i
)braket
dot
id|size
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pagenr
op_ge
id|addr
)paren
op_logical_and
(paren
id|pagenr
OL
id|end
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if CONFIG_HIGHMEM
DECL|variable|kmap_pte
id|pte_t
op_star
id|kmap_pte
suffix:semicolon
DECL|variable|kmap_prot
id|pgprot_t
id|kmap_prot
suffix:semicolon
DECL|macro|kmap_get_fixmap_pte
mdefine_line|#define kmap_get_fixmap_pte(vaddr)&t;&t;&t;&t;&t;&bslash;&n;&t;pte_offset_kernel(pmd_offset(pgd_offset_k(vaddr), (vaddr)), (vaddr))
DECL|function|kmap_init
r_void
id|__init
id|kmap_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|kmap_vstart
suffix:semicolon
multiline_comment|/* cache the first kmap pte */
id|kmap_vstart
op_assign
id|__fix_to_virt
c_func
(paren
id|FIX_KMAP_BEGIN
)paren
suffix:semicolon
id|kmap_pte
op_assign
id|kmap_get_fixmap_pte
c_func
(paren
id|kmap_vstart
)paren
suffix:semicolon
id|kmap_prot
op_assign
id|PAGE_KERNEL
suffix:semicolon
)brace
DECL|function|permanent_kmaps_init
r_void
id|__init
id|permanent_kmaps_init
c_func
(paren
id|pgd_t
op_star
id|pgd_base
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
id|vaddr
op_assign
id|PKMAP_BASE
suffix:semicolon
id|page_table_range_init
c_func
(paren
id|vaddr
comma
id|vaddr
op_plus
id|PAGE_SIZE
op_star
id|LAST_PKMAP
comma
id|pgd_base
)paren
suffix:semicolon
id|pgd
op_assign
id|swapper_pg_dir
op_plus
id|__pgd_offset
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|vaddr
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|vaddr
)paren
suffix:semicolon
id|pkmap_page_table
op_assign
id|pte
suffix:semicolon
)brace
DECL|function|one_highpage_init
r_void
id|__init
id|one_highpage_init
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|pfn
comma
r_int
id|bad_ppro
)paren
(brace
r_if
c_cond
(paren
id|page_is_ram
c_func
(paren
id|pfn
)paren
op_logical_and
op_logical_neg
(paren
id|bad_ppro
op_logical_and
id|page_kills_ppro
c_func
(paren
id|pfn
)paren
)paren
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_highmem
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|totalhigh_pages
op_increment
suffix:semicolon
)brace
r_else
id|SetPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|function|set_highmem_pages_init
r_void
id|__init
id|set_highmem_pages_init
c_func
(paren
r_int
id|bad_ppro
)paren
(brace
r_int
id|pfn
suffix:semicolon
r_for
c_loop
(paren
id|pfn
op_assign
id|highstart_pfn
suffix:semicolon
id|pfn
OL
id|highend_pfn
suffix:semicolon
id|pfn
op_increment
)paren
id|one_highpage_init
c_func
(paren
id|pfn_to_page
c_func
(paren
id|pfn
)paren
comma
id|pfn
comma
id|bad_ppro
)paren
suffix:semicolon
id|totalram_pages
op_add_assign
id|totalhigh_pages
suffix:semicolon
)brace
macro_line|#else
r_extern
r_void
id|set_highmem_pages_init
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
macro_line|#else
DECL|macro|kmap_init
mdefine_line|#define kmap_init() do { } while (0)
DECL|macro|permanent_kmaps_init
mdefine_line|#define permanent_kmaps_init(pgd_base) do { } while (0)
DECL|macro|set_highmem_pages_init
mdefine_line|#define set_highmem_pages_init(bad_ppro) do { } while (0)
macro_line|#endif /* CONFIG_HIGHMEM */
DECL|variable|__PAGE_KERNEL
r_int
r_int
id|__PAGE_KERNEL
op_assign
id|_PAGE_KERNEL
suffix:semicolon
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|remap_numa_kva
mdefine_line|#define remap_numa_kva() do {} while (0)
macro_line|#else
r_extern
r_void
id|__init
id|remap_numa_kva
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|pagetable_init
r_static
r_void
id|__init
id|pagetable_init
(paren
r_void
)paren
(brace
r_int
r_int
id|vaddr
suffix:semicolon
id|pgd_t
op_star
id|pgd_base
op_assign
id|swapper_pg_dir
suffix:semicolon
macro_line|#if CONFIG_X86_PAE
r_int
id|i
suffix:semicolon
multiline_comment|/* Init entries of the first-level page table to the zero page */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PTRS_PER_PGD
suffix:semicolon
id|i
op_increment
)paren
id|set_pgd
c_func
(paren
id|pgd_base
op_plus
id|i
comma
id|__pgd
c_func
(paren
id|__pa
c_func
(paren
id|empty_zero_page
)paren
op_or
id|_PAGE_PRESENT
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Enable PSE if available */
r_if
c_cond
(paren
id|cpu_has_pse
)paren
(brace
id|set_in_cr4
c_func
(paren
id|X86_CR4_PSE
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable PGE if available */
r_if
c_cond
(paren
id|cpu_has_pge
)paren
(brace
id|set_in_cr4
c_func
(paren
id|X86_CR4_PGE
)paren
suffix:semicolon
id|__PAGE_KERNEL
op_or_assign
id|_PAGE_GLOBAL
suffix:semicolon
)brace
id|kernel_physical_mapping_init
c_func
(paren
id|pgd_base
)paren
suffix:semicolon
id|remap_numa_kva
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Fixed mappings, only the page table structure has to be&n;&t; * created - mappings will be set by set_fixmap():&n;&t; */
id|vaddr
op_assign
id|__fix_to_virt
c_func
(paren
id|__end_of_fixed_addresses
op_minus
l_int|1
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|page_table_range_init
c_func
(paren
id|vaddr
comma
l_int|0
comma
id|pgd_base
)paren
suffix:semicolon
id|permanent_kmaps_init
c_func
(paren
id|pgd_base
)paren
suffix:semicolon
macro_line|#if CONFIG_X86_PAE
multiline_comment|/*&n;&t; * Add low memory identity-mappings - SMP needs it when&n;&t; * starting up on an AP from real-mode. In the non-PAE&n;&t; * case we already have these mappings through head.S.&n;&t; * All user-space mappings are explicitly cleared after&n;&t; * SMP startup.&n;&t; */
id|pgd_base
(braket
l_int|0
)braket
op_assign
id|pgd_base
(braket
id|USER_PTRS_PER_PGD
)braket
suffix:semicolon
macro_line|#endif
)brace
DECL|function|zap_low_mappings
r_void
id|__init
id|zap_low_mappings
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Zap initial low-memory mappings.&n;&t; *&n;&t; * Note that &quot;pgd_clear()&quot; doesn&squot;t do it for&n;&t; * us, because pgd_clear() is a no-op on i386.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|USER_PTRS_PER_PGD
suffix:semicolon
id|i
op_increment
)paren
macro_line|#if CONFIG_X86_PAE
id|set_pgd
c_func
(paren
id|swapper_pg_dir
op_plus
id|i
comma
id|__pgd
c_func
(paren
l_int|1
op_plus
id|__pa
c_func
(paren
id|empty_zero_page
)paren
)paren
)paren
suffix:semicolon
macro_line|#else
id|set_pgd
c_func
(paren
id|swapper_pg_dir
op_plus
id|i
comma
id|__pgd
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
macro_line|#endif
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|function|zone_sizes_init
r_void
id|__init
id|zone_sizes_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
r_int
id|max_dma
comma
id|high
comma
id|low
suffix:semicolon
id|max_dma
op_assign
id|virt_to_phys
c_func
(paren
(paren
r_char
op_star
)paren
id|MAX_DMA_ADDRESS
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|low
op_assign
id|max_low_pfn
suffix:semicolon
id|high
op_assign
id|highend_pfn
suffix:semicolon
r_if
c_cond
(paren
id|low
OL
id|max_dma
)paren
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|low
suffix:semicolon
r_else
(brace
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|max_dma
suffix:semicolon
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
id|low
op_minus
id|max_dma
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
id|zones_size
(braket
id|ZONE_HIGHMEM
)braket
op_assign
id|high
op_minus
id|low
suffix:semicolon
macro_line|#endif
)brace
id|free_area_init
c_func
(paren
id|zones_size
)paren
suffix:semicolon
)brace
macro_line|#else
r_extern
r_void
id|zone_sizes_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
multiline_comment|/*&n; * paging_init() sets up the page tables - note that the first 8MB are&n; * already mapped by head.S.&n; *&n; * This routines also unmaps the page at virtual kernel address 0, so&n; * that we can trap those pesky NULL-reference errors in the kernel.&n; */
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
(brace
id|pagetable_init
c_func
(paren
)paren
suffix:semicolon
id|load_cr3
c_func
(paren
id|swapper_pg_dir
)paren
suffix:semicolon
macro_line|#if CONFIG_X86_PAE
multiline_comment|/*&n;&t; * We will bail out later - printk doesn&squot;t work right now so&n;&t; * the user would just see a hanging kernel.&n;&t; */
r_if
c_cond
(paren
id|cpu_has_pae
)paren
id|set_in_cr4
c_func
(paren
id|X86_CR4_PAE
)paren
suffix:semicolon
macro_line|#endif
id|__flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|kmap_init
c_func
(paren
)paren
suffix:semicolon
id|zone_sizes_init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Test if the WP bit works in supervisor mode. It isn&squot;t supported on 386&squot;s&n; * and also on some strange 486&squot;s (NexGen etc.). All 586+&squot;s are OK. The jumps&n; * before and after the test are here to work-around some nasty CPU bugs.&n; */
multiline_comment|/*&n; * This function cannot be __init, since exceptions don&squot;t work in that&n; * section.&n; */
r_static
r_int
id|do_test_wp_bit
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|test_wp_bit
r_void
id|__init
id|test_wp_bit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|cpu_has_pse
)paren
(brace
multiline_comment|/* Ok, all PSE-capable CPUs are definitely handling the WP bit right. */
id|boot_cpu_data.wp_works_ok
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Checking if this processor honours the WP bit even in supervisor mode... &quot;
)paren
suffix:semicolon
multiline_comment|/* Any page-aligned address will do, the test is non-destructive */
id|__set_fixmap
c_func
(paren
id|FIX_WP_TEST
comma
id|__pa
c_func
(paren
op_amp
id|swapper_pg_dir
)paren
comma
id|PAGE_READONLY
)paren
suffix:semicolon
id|boot_cpu_data.wp_works_ok
op_assign
id|do_test_wp_bit
c_func
(paren
)paren
suffix:semicolon
id|clear_fixmap
c_func
(paren
id|FIX_WP_TEST
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|boot_cpu_data.wp_works_ok
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_WP_WORKS_OK
id|panic
c_func
(paren
l_string|&quot;This kernel doesn&squot;t support CPU&squot;s with broken WP. Recompile it for a 386!&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Ok.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|function|set_max_mapnr_init
r_static
r_void
id|__init
id|set_max_mapnr_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_HIGHMEM
id|highmem_start_page
op_assign
id|pfn_to_page
c_func
(paren
id|highstart_pfn
)paren
suffix:semicolon
id|max_mapnr
op_assign
id|num_physpages
op_assign
id|highend_pfn
suffix:semicolon
macro_line|#else
id|max_mapnr
op_assign
id|num_physpages
op_assign
id|max_low_pfn
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|__free_all_bootmem
mdefine_line|#define __free_all_bootmem() free_all_bootmem()
macro_line|#else
DECL|macro|__free_all_bootmem
mdefine_line|#define __free_all_bootmem() free_all_bootmem_node(NODE_DATA(0))
r_extern
r_void
id|set_max_mapnr_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
macro_line|#ifdef CONFIG_HUGETLB_PAGE
DECL|variable|htlbpagemem
r_int
id|htlbpagemem
op_assign
l_int|0
suffix:semicolon
DECL|variable|htlbpage_max
r_int
id|htlbpage_max
suffix:semicolon
DECL|variable|htlbzone_pages
r_int
id|htlbzone_pages
suffix:semicolon
r_extern
r_struct
id|list_head
id|htlbpage_freelist
suffix:semicolon
macro_line|#endif
DECL|function|mem_init
r_void
id|__init
id|mem_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|ppro_with_ram_bug
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|codesize
comma
id|reservedpages
comma
id|datasize
comma
id|initsize
suffix:semicolon
r_int
id|tmp
suffix:semicolon
r_int
id|bad_ppro
suffix:semicolon
macro_line|#ifndef CONFIG_DISCONTIGMEM
r_if
c_cond
(paren
op_logical_neg
id|mem_map
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|bad_ppro
op_assign
id|ppro_with_ram_bug
c_func
(paren
)paren
suffix:semicolon
id|set_max_mapnr_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|highstart_pfn
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#else
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|max_low_pfn
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* clear the zero-page */
id|memset
c_func
(paren
id|empty_zero_page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* this will put all low memory onto the freelists */
id|totalram_pages
op_add_assign
id|__free_all_bootmem
c_func
(paren
)paren
suffix:semicolon
id|reservedpages
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|max_low_pfn
suffix:semicolon
id|tmp
op_increment
)paren
multiline_comment|/*&n;&t;&t; * Only count reserved RAM pages&n;&t;&t; */
r_if
c_cond
(paren
id|page_is_ram
c_func
(paren
id|tmp
)paren
op_logical_and
id|PageReserved
c_func
(paren
id|pfn_to_page
c_func
(paren
id|tmp
)paren
)paren
)paren
id|reservedpages
op_increment
suffix:semicolon
id|set_highmem_pages_init
c_func
(paren
id|bad_ppro
)paren
suffix:semicolon
id|codesize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_text
suffix:semicolon
id|datasize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_edata
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_etext
suffix:semicolon
id|initsize
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__init_end
op_minus
(paren
r_int
r_int
)paren
op_amp
id|__init_begin
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Memory: %luk/%luk available (%dk kernel code, %dk reserved, %dk data, %dk init, %ldk highmem)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|nr_free_pages
c_func
(paren
)paren
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|num_physpages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|codesize
op_rshift
l_int|10
comma
id|reservedpages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|datasize
op_rshift
l_int|10
comma
id|initsize
op_rshift
l_int|10
comma
(paren
r_int
r_int
)paren
(paren
id|totalhigh_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
)paren
suffix:semicolon
macro_line|#if CONFIG_X86_PAE
r_if
c_cond
(paren
op_logical_neg
id|cpu_has_pae
)paren
id|panic
c_func
(paren
l_string|&quot;cannot execute a PAE-enabled kernel on a PAE-less CPU!&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|boot_cpu_data.wp_works_ok
OL
l_int|0
)paren
id|test_wp_bit
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Subtle. SMP is doing it&squot;s boot stuff late (because it has to&n;&t; * fork idle threads) - but it also needs low mappings for the&n;&t; * protected-mode entry to work. We zap these entries only after&n;&t; * the WP-bit has been tested.&n;&t; */
macro_line|#ifndef CONFIG_SMP
id|zap_low_mappings
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HUGETLB_PAGE
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_struct
id|page
op_star
id|page
comma
op_star
id|map
suffix:semicolon
multiline_comment|/*For now reserve quarter for hugetlb_pages.*/
id|htlbzone_pages
op_assign
(paren
id|max_low_pfn
op_rshift
(paren
(paren
id|HPAGE_SHIFT
op_minus
id|PAGE_SHIFT
)paren
op_plus
l_int|2
)paren
)paren
suffix:semicolon
multiline_comment|/*Will make this kernel command line. */
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|htlbpage_freelist
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|htlbzone_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
id|page
op_assign
id|alloc_pages
c_func
(paren
id|__GFP_HIGHMEM
comma
id|HUGETLB_PAGE_ORDER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|map
op_assign
id|page
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
(paren
id|HPAGE_SIZE
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
id|SetPageReserved
c_func
(paren
id|map
)paren
suffix:semicolon
id|map
op_increment
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|page-&gt;list
comma
op_amp
id|htlbpage_freelist
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Total Huge_TLB_Page memory pages allocated %ld&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|htlbzone_pages
op_assign
id|htlbpagemem
op_assign
id|i
suffix:semicolon
id|htlbpage_max
op_assign
id|i
suffix:semicolon
)brace
macro_line|#endif
)brace
macro_line|#if CONFIG_X86_PAE
DECL|variable|pae_pgd_cachep
r_struct
id|kmem_cache_s
op_star
id|pae_pgd_cachep
suffix:semicolon
DECL|function|pgtable_cache_init
r_void
id|__init
id|pgtable_cache_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;         * PAE pgds must be 16-byte aligned:&n;         */
id|pae_pgd_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;pae_pgd&quot;
comma
l_int|32
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
op_or
id|SLAB_MUST_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pae_pgd_cachep
)paren
id|panic
c_func
(paren
l_string|&quot;init_pae(): Cannot alloc pae_pgd SLAB cache&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Put this after the callers, so that it cannot be inlined */
DECL|function|do_test_wp_bit
r_static
r_int
id|do_test_wp_bit
c_func
(paren
r_void
)paren
(brace
r_char
id|tmp_reg
suffix:semicolon
r_int
id|flag
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;movb %0,%1&t;&bslash;n&quot;
l_string|&quot;1:&t;movb %1,%0&t;&bslash;n&quot;
l_string|&quot;&t;xorl %2,%2&t;&bslash;n&quot;
l_string|&quot;2:&t;&t;&t;&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&t;&bslash;n&quot;
l_string|&quot;&t;.long 1b,2b&t;&bslash;n&quot;
l_string|&quot;.previous&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_char
op_star
)paren
id|fix_to_virt
c_func
(paren
id|FIX_WP_TEST
)paren
)paren
comma
l_string|&quot;=q&quot;
(paren
id|tmp_reg
)paren
comma
l_string|&quot;=r&quot;
(paren
id|flag
)paren
suffix:colon
l_string|&quot;2&quot;
(paren
l_int|1
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|flag
suffix:semicolon
)brace
DECL|function|free_initmem
r_void
id|free_initmem
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__init_begin
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|addr
OL
(paren
r_int
r_int
)paren
(paren
op_amp
id|__init_end
)paren
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|addr
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|addr
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Freeing unused kernel memory: %dk freed&bslash;n&quot;
comma
(paren
op_amp
id|__init_end
op_minus
op_amp
id|__init_begin
)paren
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|function|free_initrd_mem
r_void
id|free_initrd_mem
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
r_if
c_cond
(paren
id|start
OL
id|end
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;Freeing initrd memory: %ldk freed&bslash;n&quot;
comma
(paren
id|end
op_minus
id|start
)paren
op_rshift
l_int|10
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|start
OL
id|end
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|start
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|start
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|start
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
