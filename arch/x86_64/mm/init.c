multiline_comment|/*&n; *  linux/arch/x86_64/mm/init.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Copyright (C) 2000  Pavel Machek &lt;pavel@suse.cz&gt;&n; *  Copyright (C) 2002  Andi Kleen &lt;ak@suse.de&gt;&n; */
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
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
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
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
DECL|variable|start_pfn
DECL|variable|end_pfn
r_int
r_int
id|start_pfn
comma
id|end_pfn
suffix:semicolon
DECL|variable|mmu_gathers
r_struct
id|mmu_gather
id|mmu_gathers
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n; * NOTE: pagetable_init alloc all the fixmap pagetables contiguous on the&n; * physical space so we can cache the place of the first one and move&n; * around without checking the pgd every time.&n; */
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|total
op_assign
l_int|0
comma
id|reserved
op_assign
l_int|0
suffix:semicolon
r_int
id|shared
op_assign
l_int|0
comma
id|cached
op_assign
l_int|0
suffix:semicolon
id|pg_data_t
op_star
id|pgdat
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Mem-info:&bslash;n&quot;
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Free swap:       %6dkB&bslash;n&quot;
comma
id|nr_swap_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|for_each_pgdat
c_func
(paren
id|pgdat
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pgdat-&gt;node_size
suffix:semicolon
op_increment
id|i
)paren
(brace
id|page
op_assign
id|pgdat-&gt;node_mem_map
op_plus
id|i
suffix:semicolon
id|total
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|page
)paren
)paren
id|reserved
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
id|cached
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|page_count
c_func
(paren
id|page
)paren
)paren
id|shared
op_add_assign
id|page_count
c_func
(paren
id|page
)paren
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;%d pages of RAM&bslash;n&quot;
comma
id|total
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d reserved pages&bslash;n&quot;
comma
id|reserved
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages swap cached&bslash;n&quot;
comma
id|cached
)paren
suffix:semicolon
)brace
multiline_comment|/* References to section boundaries */
r_extern
r_char
id|_text
comma
id|_etext
comma
id|_edata
comma
id|__bss_start
comma
id|_end
suffix:semicolon
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
DECL|variable|after_bootmem
r_int
id|after_bootmem
suffix:semicolon
DECL|function|spp_getpage
r_static
r_void
op_star
id|spp_getpage
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|after_bootmem
)paren
id|ptr
op_assign
(paren
r_void
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_ATOMIC
)paren
suffix:semicolon
r_else
id|ptr
op_assign
id|alloc_bootmem_low
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
id|panic
c_func
(paren
l_string|&quot;set_pte_phys: cannot allocate page data %s&bslash;n&quot;
comma
id|after_bootmem
ques
c_cond
l_string|&quot;after bootmem&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
DECL|function|set_pte_phys
r_static
r_void
id|set_pte_phys
c_func
(paren
r_int
r_int
id|vaddr
comma
r_int
r_int
id|phys
comma
id|pgprot_t
id|prot
)paren
(brace
id|pml4_t
op_star
id|level4
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
id|level4
op_assign
id|pml4_offset_k
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pml4_none
c_func
(paren
op_star
id|level4
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PML4 FIXMAP MISSING, it should be setup in head.S!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pgd
op_assign
id|level3_offset_k
c_func
(paren
id|level4
comma
id|vaddr
)paren
suffix:semicolon
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
(brace
id|pmd
op_assign
(paren
id|pmd_t
op_star
)paren
id|spp_getpage
c_func
(paren
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
id|pmd
)paren
op_or
id|_KERNPG_TABLE
op_or
id|_PAGE_USER
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
op_ne
id|pmd_offset
c_func
(paren
id|pgd
comma
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PAGETABLE BUG #01!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
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
id|spp_getpage
c_func
(paren
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
id|pte
)paren
op_or
id|_KERNPG_TABLE
op_or
id|_PAGE_USER
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
(brace
id|printk
c_func
(paren
l_string|&quot;PAGETABLE BUG #02!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
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
r_if
c_cond
(paren
id|pte_val
c_func
(paren
op_star
id|pte
)paren
)paren
id|pte_ERROR
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|pfn_pte
c_func
(paren
id|phys
op_rshift
id|PAGE_SHIFT
comma
id|prot
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * It&squot;s enough to flush this one mapping.&n;&t; * (PGE mappings get flushed as well)&n;&t; */
id|__flush_tlb_one
c_func
(paren
id|vaddr
)paren
suffix:semicolon
)brace
multiline_comment|/* NOTE: this is meant to be run only at boot */
DECL|function|__set_fixmap
r_void
id|__set_fixmap
(paren
r_enum
id|fixed_addresses
id|idx
comma
r_int
r_int
id|phys
comma
id|pgprot_t
id|prot
)paren
(brace
r_int
r_int
id|address
op_assign
id|__fix_to_virt
c_func
(paren
id|idx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|__end_of_fixed_addresses
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Invalid __set_fixmap&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|set_pte_phys
c_func
(paren
id|address
comma
id|phys
comma
id|prot
)paren
suffix:semicolon
)brace
r_extern
r_int
r_int
id|start_pfn
comma
id|end_pfn
suffix:semicolon
r_extern
id|pmd_t
id|temp_boot_pmds
(braket
)braket
suffix:semicolon
DECL|struct|temp_map
r_static
r_struct
id|temp_map
(brace
DECL|member|pmd
id|pmd_t
op_star
id|pmd
suffix:semicolon
DECL|member|address
r_void
op_star
id|address
suffix:semicolon
DECL|member|allocated
r_int
id|allocated
suffix:semicolon
DECL|variable|__initdata
)brace
id|temp_mappings
(braket
)braket
id|__initdata
op_assign
(brace
(brace
op_amp
id|temp_boot_pmds
(braket
l_int|0
)braket
comma
(paren
r_void
op_star
)paren
(paren
l_int|40UL
op_star
l_int|1024
op_star
l_int|1024
)paren
)brace
comma
(brace
op_amp
id|temp_boot_pmds
(braket
l_int|1
)braket
comma
(paren
r_void
op_star
)paren
(paren
l_int|42UL
op_star
l_int|1024
op_star
l_int|1024
)paren
)brace
comma
(brace
op_amp
id|temp_boot_pmds
(braket
l_int|2
)braket
comma
(paren
r_void
op_star
)paren
(paren
l_int|44UL
op_star
l_int|1024
op_star
l_int|1024
)paren
)brace
comma
(brace
)brace
)brace
suffix:semicolon
DECL|function|alloc_low_page
r_static
id|__init
r_void
op_star
id|alloc_low_page
c_func
(paren
r_int
op_star
id|index
comma
r_int
r_int
op_star
id|phys
)paren
(brace
r_struct
id|temp_map
op_star
id|ti
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|pfn
op_assign
id|start_pfn
op_increment
comma
id|paddr
suffix:semicolon
r_void
op_star
id|adr
suffix:semicolon
r_if
c_cond
(paren
id|pfn
op_ge
id|end_pfn_map
)paren
id|panic
c_func
(paren
l_string|&quot;alloc_low_page: ran out of memory&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|temp_mappings
(braket
id|i
)braket
dot
id|allocated
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|temp_mappings
(braket
id|i
)braket
dot
id|pmd
)paren
id|panic
c_func
(paren
l_string|&quot;alloc_low_page: ran out of temp mappings&quot;
)paren
suffix:semicolon
)brace
id|ti
op_assign
op_amp
id|temp_mappings
(braket
id|i
)braket
suffix:semicolon
id|paddr
op_assign
(paren
id|pfn
op_amp
(paren
op_complement
l_int|511
)paren
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|set_pmd
c_func
(paren
id|ti-&gt;pmd
comma
id|__pmd
c_func
(paren
id|paddr
op_or
id|_KERNPG_TABLE
op_or
id|_PAGE_PSE
)paren
)paren
suffix:semicolon
id|ti-&gt;allocated
op_assign
l_int|1
suffix:semicolon
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
id|adr
op_assign
id|ti-&gt;address
op_plus
(paren
id|pfn
op_amp
l_int|511
)paren
op_star
id|PAGE_SIZE
suffix:semicolon
op_star
id|index
op_assign
id|i
suffix:semicolon
op_star
id|phys
op_assign
id|pfn
op_star
id|PAGE_SIZE
suffix:semicolon
r_return
id|adr
suffix:semicolon
)brace
DECL|function|unmap_low_page
r_static
id|__init
r_void
id|unmap_low_page
c_func
(paren
r_int
id|i
)paren
(brace
r_struct
id|temp_map
op_star
id|ti
op_assign
op_amp
id|temp_mappings
(braket
id|i
)braket
suffix:semicolon
id|set_pmd
c_func
(paren
id|ti-&gt;pmd
comma
id|__pmd
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|ti-&gt;allocated
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|phys_pgd_init
r_static
r_void
id|__init
id|phys_pgd_init
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|end
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
id|i
op_assign
id|pgd_index
c_func
(paren
id|address
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd
op_plus
id|i
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|PTRS_PER_PGD
suffix:semicolon
id|pgd
op_increment
comma
id|i
op_increment
)paren
(brace
r_int
id|map
suffix:semicolon
r_int
r_int
id|paddr
op_assign
id|i
op_star
id|PGDIR_SIZE
comma
id|pmd_phys
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_if
c_cond
(paren
id|paddr
op_ge
id|end
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|PTRS_PER_PGD
suffix:semicolon
id|i
op_increment
comma
id|pgd
op_increment
)paren
id|set_pgd
c_func
(paren
id|pgd
comma
id|__pgd
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pmd
op_assign
id|alloc_low_page
c_func
(paren
op_amp
id|map
comma
op_amp
id|pmd_phys
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
id|pmd_phys
op_or
id|_KERNPG_TABLE
)paren
)paren
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
id|PTRS_PER_PMD
suffix:semicolon
id|pmd
op_increment
comma
id|j
op_increment
)paren
(brace
r_int
r_int
id|pe
suffix:semicolon
id|paddr
op_assign
id|i
op_star
id|PGDIR_SIZE
op_plus
id|j
op_star
id|PMD_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|paddr
op_ge
id|end
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
id|PTRS_PER_PMD
suffix:semicolon
id|j
op_increment
comma
id|pmd
op_increment
)paren
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pe
op_assign
id|_PAGE_NX
op_or
id|_PAGE_PSE
op_or
id|_KERNPG_TABLE
op_or
id|_PAGE_GLOBAL
op_or
id|paddr
suffix:semicolon
id|pe
op_and_assign
id|__supported_pte_mask
suffix:semicolon
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|pe
)paren
)paren
suffix:semicolon
)brace
id|unmap_low_page
c_func
(paren
id|map
)paren
suffix:semicolon
)brace
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Setup the direct mapping of the physical memory at PAGE_OFFSET.&n;   This runs before bootmem is initialized and gets pages directly from the &n;   physical memory. To access them they are temporarily mapped. */
DECL|function|init_memory_mapping
r_void
id|__init
id|init_memory_mapping
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|adr
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
id|end
op_assign
id|PAGE_OFFSET
op_plus
(paren
id|end_pfn_map
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|adr
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|adr
OL
id|end
suffix:semicolon
id|adr
op_assign
id|next
)paren
(brace
r_int
id|map
suffix:semicolon
r_int
r_int
id|pgd_phys
suffix:semicolon
id|pgd_t
op_star
id|pgd
op_assign
id|alloc_low_page
c_func
(paren
op_amp
id|map
comma
op_amp
id|pgd_phys
)paren
suffix:semicolon
id|next
op_assign
id|adr
op_plus
(paren
l_int|512UL
op_star
l_int|1024
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
OG
id|end
)paren
id|next
op_assign
id|end
suffix:semicolon
id|phys_pgd_init
c_func
(paren
id|pgd
comma
id|adr
op_minus
id|PAGE_OFFSET
comma
id|next
op_minus
id|PAGE_OFFSET
)paren
suffix:semicolon
id|set_pml4
c_func
(paren
id|init_level4_pgt
op_plus
id|pml4_index
c_func
(paren
id|adr
)paren
comma
id|mk_kernel_pml4
c_func
(paren
id|pgd_phys
)paren
)paren
suffix:semicolon
id|unmap_low_page
c_func
(paren
id|map
)paren
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;movq %%cr4,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|mmu_cr4_features
)paren
)paren
suffix:semicolon
id|__flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|x8664_pda
id|cpu_pda
(braket
id|NR_CPUS
)braket
suffix:semicolon
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_pda
(braket
id|i
)braket
dot
id|level4_pgt
)paren
id|cpu_pda
(braket
id|i
)braket
dot
id|level4_pgt
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
(brace
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
r_if
c_cond
(paren
id|end_pfn
OL
id|max_dma
)paren
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|end_pfn
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
id|end_pfn
op_minus
id|max_dma
suffix:semicolon
)brace
id|free_area_init
c_func
(paren
id|zones_size
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|page_is_ram
r_static
r_inline
r_int
id|page_is_ram
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
id|printk
c_func
(paren
l_string|&quot;mem_init&bslash;n&quot;
)paren
suffix:semicolon
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
id|max_low_pfn
op_assign
id|end_pfn
suffix:semicolon
id|max_pfn
op_assign
id|end_pfn
suffix:semicolon
id|max_mapnr
op_assign
id|num_physpages
op_assign
id|end_pfn
suffix:semicolon
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|end_pfn
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
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
id|free_all_bootmem
c_func
(paren
)paren
suffix:semicolon
id|after_bootmem
op_assign
l_int|1
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
id|end_pfn
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
id|mem_map
op_plus
id|tmp
)paren
)paren
id|reservedpages
op_increment
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
l_string|&quot;Memory: %luk/%luk available (%dk kernel code, %dk reserved, %dk data, %dk init)&bslash;n&quot;
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
id|max_mapnr
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
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Subtle. SMP is doing its boot stuff late (because it has to&n;&t; * fork idle threads) - but it also needs low mappings for the&n;&t; * protected-mode entry to work. We zap these entries only after&n;&t; * the WP-bit has been tested.&n;&t; */
macro_line|#ifndef CONFIG_SMP
id|zap_low_mappings
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef CONFIG_INIT_DEBUG
id|memset
c_func
(paren
id|addr
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
comma
l_int|0xcc
comma
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#endif
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
l_string|&quot;Freeing unused kernel memory: %luk freed&bslash;n&quot;
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
(paren
r_int
r_int
)paren
op_amp
id|_end
)paren
r_return
suffix:semicolon
id|printk
(paren
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
