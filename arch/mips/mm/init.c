multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 2000 Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|mmu_gather
comma
id|mmu_gathers
)paren
suffix:semicolon
DECL|variable|highstart_pfn
DECL|variable|highend_pfn
r_int
r_int
id|highstart_pfn
comma
id|highend_pfn
suffix:semicolon
multiline_comment|/*&n; * We have up to 8 empty zeroed pages so we can map one of the right colour&n; * when needed.  This is necessary only on R4000 / R4400 SC and MC versions&n; * where we have to avoid VCED / VECI exceptions for good performance at&n; * any price.  Since page is never written to after the initialization we&n; * don&squot;t have to care about aliases on other CPUs.&n; */
DECL|variable|empty_zero_page
DECL|variable|zero_page_mask
r_int
r_int
id|empty_zero_page
comma
id|zero_page_mask
suffix:semicolon
multiline_comment|/*&n; * Not static inline because used by IP27 special magic initialization code&n; */
DECL|function|setup_zero_pages
r_int
r_int
id|setup_zero_pages
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|order
comma
id|size
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_vce
)paren
id|order
op_assign
l_int|3
suffix:semicolon
r_else
id|order
op_assign
l_int|0
suffix:semicolon
id|empty_zero_page
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|empty_zero_page
)paren
id|panic
c_func
(paren
l_string|&quot;Oh boy, that early out of memory?&quot;
)paren
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|empty_zero_page
)paren
suffix:semicolon
r_while
c_loop
(paren
id|page
OL
id|virt_to_page
c_func
(paren
id|empty_zero_page
op_plus
(paren
id|PAGE_SIZE
op_lshift
id|order
)paren
)paren
)paren
(brace
id|set_bit
c_func
(paren
id|PG_reserved
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
l_int|0
)paren
suffix:semicolon
id|page
op_increment
suffix:semicolon
)brace
id|size
op_assign
id|PAGE_SIZE
op_lshift
id|order
suffix:semicolon
id|zero_page_mask
op_assign
(paren
id|size
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|empty_zero_page
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
l_int|1UL
op_lshift
id|order
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HIGHMEM
DECL|variable|kmap_pte
id|pte_t
op_star
id|kmap_pte
suffix:semicolon
DECL|variable|kmap_prot
id|pgprot_t
id|kmap_prot
suffix:semicolon
DECL|variable|kmap_prot
id|EXPORT_SYMBOL
c_func
(paren
id|kmap_prot
)paren
suffix:semicolon
DECL|variable|kmap_pte
id|EXPORT_SYMBOL
c_func
(paren
id|kmap_pte
)paren
suffix:semicolon
DECL|macro|kmap_get_fixmap_pte
mdefine_line|#define kmap_get_fixmap_pte(vaddr)&t;&t;&t;&t;&t;&bslash;&n;&t;pte_offset_kernel(pmd_offset(pgd_offset_k(vaddr), (vaddr)), (vaddr))
DECL|function|kmap_init
r_static
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
macro_line|#ifdef CONFIG_MIPS64
DECL|function|fixrange_init
r_static
r_void
id|__init
id|fixrange_init
c_func
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
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
id|vaddr
op_assign
id|start
suffix:semicolon
id|i
op_assign
id|__pgd_offset
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|j
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
id|i
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|i
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
id|i
op_increment
)paren
(brace
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|pgd
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|j
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
id|j
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
(brace
id|pte
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
id|pte
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
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
)brace
id|vaddr
op_add_assign
id|PMD_SIZE
suffix:semicolon
)brace
id|j
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_MIPS64 */
macro_line|#endif /* CONFIG_HIGHMEM */
macro_line|#ifndef CONFIG_DISCONTIGMEM
r_extern
r_void
id|pagetable_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|paging_init
r_void
id|__init
id|paging_init
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
id|pagetable_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
id|kmap_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef CONFIG_ISA
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
)brace
macro_line|#else
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|low
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HIGHMEM
r_if
c_cond
(paren
id|cpu_has_dc_aliases
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;This processor doesn&squot;t support highmem.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|high
op_minus
id|low
)paren
id|printk
c_func
(paren
l_string|&quot; %ldk highmem ignored&quot;
comma
id|high
op_minus
id|low
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
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
id|free_area_init
c_func
(paren
id|zones_size
)paren
suffix:semicolon
)brace
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)&t;(((x) + PAGE_SIZE - 1) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_DOWN
mdefine_line|#define PFN_DOWN(x)&t;((x) &gt;&gt; PAGE_SHIFT)
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
id|boot_mem_map.nr_map
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
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|type
op_ne
id|BOOT_MEM_RAM
)paren
multiline_comment|/* not usable memory */
r_continue
suffix:semicolon
id|addr
op_assign
id|PFN_UP
c_func
(paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|addr
)paren
suffix:semicolon
id|end
op_assign
id|PFN_DOWN
c_func
(paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pagenr
op_ge
id|addr
op_logical_and
id|pagenr
OL
id|end
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mem_init
r_void
id|__init
id|mem_init
c_func
(paren
r_void
)paren
(brace
r_int
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
r_int
id|tmp
comma
id|ram
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
id|highmem_start_page
op_assign
id|mem_map
op_plus
id|highstart_pfn
suffix:semicolon
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|#error &quot;CONFIG_HIGHMEM and CONFIG_DISCONTIGMEM dont work together yet&quot;
macro_line|#endif
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
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|totalram_pages
op_add_assign
id|free_all_bootmem
c_func
(paren
)paren
suffix:semicolon
id|totalram_pages
op_sub_assign
id|setup_zero_pages
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Setup zeroed pages.  */
id|reservedpages
op_assign
id|ram
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
r_if
c_cond
(paren
id|page_is_ram
c_func
(paren
id|tmp
)paren
)paren
(brace
id|ram
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|mem_map
op_plus
id|tmp
)paren
)paren
id|reservedpages
op_increment
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HIGHMEM
r_for
c_loop
(paren
id|tmp
op_assign
id|highstart_pfn
suffix:semicolon
id|tmp
OL
id|highend_pfn
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|mem_map
op_plus
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page_is_ram
c_func
(paren
id|tmp
)paren
)paren
(brace
id|SetPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_LIMITED_DMA
id|set_page_address
c_func
(paren
id|page
comma
id|lowmem_page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
macro_line|#endif
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
id|totalram_pages
op_add_assign
id|totalhigh_pages
suffix:semicolon
macro_line|#endif
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
l_string|&quot;Memory: %luk/%luk available (%ldk kernel code, &quot;
l_string|&quot;%ldk reserved, %ldk data, %ldk init, %ldk highmem)&bslash;n&quot;
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
id|ram
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
)brace
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
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
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/* Switch from KSEG0 to XKPHYS addresses */
id|start
op_assign
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|CPHYSADDR
c_func
(paren
id|start
)paren
)paren
suffix:semicolon
id|end
op_assign
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|CPHYSADDR
c_func
(paren
id|end
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|start
OL
id|end
)paren
id|printk
c_func
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
r_extern
r_int
r_int
id|prom_free_prom_memory
c_func
(paren
r_void
)paren
suffix:semicolon
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
comma
id|page
comma
id|freed
suffix:semicolon
id|freed
op_assign
id|prom_free_prom_memory
c_func
(paren
)paren
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__init_begin
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
(paren
r_int
r_int
)paren
op_amp
id|__init_end
)paren
(brace
macro_line|#ifdef CONFIG_MIPS64
id|page
op_assign
id|PAGE_OFFSET
op_or
id|CPHYSADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#else
id|page
op_assign
id|addr
suffix:semicolon
macro_line|#endif
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|page
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
id|freed
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Freeing unused kernel memory: %ldk freed&bslash;n&quot;
comma
id|freed
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
eof
