multiline_comment|/*&n; * Initialize MMU support.&n; *&n; * Copyright (C) 1998-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;asm/a.out.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/efi.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
DECL|variable|mmu_gathers
id|mmu_gather_t
id|mmu_gathers
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* References to section boundaries: */
r_extern
r_char
id|_stext
comma
id|_etext
comma
id|_edata
comma
id|__init_begin
comma
id|__init_end
suffix:semicolon
r_extern
r_void
id|ia64_tlb_init
(paren
r_void
)paren
suffix:semicolon
DECL|variable|MAX_DMA_ADDRESS
r_int
r_int
id|MAX_DMA_ADDRESS
op_assign
id|PAGE_OFFSET
op_plus
l_int|0x100000000UL
suffix:semicolon
DECL|variable|totalram_pages
r_static
r_int
r_int
id|totalram_pages
suffix:semicolon
DECL|variable|pgt_cache_water
r_static
r_int
id|pgt_cache_water
(braket
l_int|2
)braket
op_assign
(brace
l_int|25
comma
l_int|50
)brace
suffix:semicolon
r_int
DECL|function|check_pgt_cache
id|check_pgt_cache
(paren
r_void
)paren
(brace
r_int
id|low
comma
id|high
comma
id|freed
op_assign
l_int|0
suffix:semicolon
id|low
op_assign
id|pgt_cache_water
(braket
l_int|0
)braket
suffix:semicolon
id|high
op_assign
id|pgt_cache_water
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pgtable_cache_size
OG
id|high
)paren
(brace
r_do
(brace
r_if
c_cond
(paren
id|pgd_quicklist
)paren
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd_alloc_one_fast
c_func
(paren
l_int|0
)paren
)paren
comma
op_increment
id|freed
suffix:semicolon
r_if
c_cond
(paren
id|pmd_quicklist
)paren
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pmd_alloc_one_fast
c_func
(paren
l_int|0
comma
l_int|0
)paren
)paren
comma
op_increment
id|freed
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pgtable_cache_size
OG
id|low
)paren
suffix:semicolon
)brace
r_return
id|freed
suffix:semicolon
)brace
multiline_comment|/*&n; * This performs some platform-dependent address space initialization.&n; * On IA-64, we want to setup the VM area for the register backing&n; * store (which grows upwards) and install the gateway page which is&n; * used for signal trampolines, etc.&n; */
r_void
DECL|function|ia64_init_addr_space
id|ia64_init_addr_space
(paren
r_void
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re out of memory and kmem_cache_alloc() returns NULL,&n;&t; * we simply ignore the problem.  When the process attempts to&n;&t; * write to the register backing store for the first time, it&n;&t; * will get a SEGFAULT in this case.&n;&t; */
id|vma
op_assign
id|kmem_cache_alloc
c_func
(paren
id|vm_area_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma
)paren
(brace
id|vma-&gt;vm_mm
op_assign
id|current-&gt;mm
suffix:semicolon
id|vma-&gt;vm_start
op_assign
id|IA64_RBS_BOT
suffix:semicolon
id|vma-&gt;vm_end
op_assign
id|vma-&gt;vm_start
op_plus
id|PAGE_SIZE
suffix:semicolon
id|vma-&gt;vm_page_prot
op_assign
id|PAGE_COPY
suffix:semicolon
id|vma-&gt;vm_flags
op_assign
id|VM_READ
op_or
id|VM_WRITE
op_or
id|VM_MAYREAD
op_or
id|VM_MAYWRITE
op_or
id|VM_GROWSUP
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
l_int|NULL
suffix:semicolon
id|vma-&gt;vm_pgoff
op_assign
l_int|0
suffix:semicolon
id|vma-&gt;vm_file
op_assign
l_int|NULL
suffix:semicolon
id|vma-&gt;vm_private_data
op_assign
l_int|NULL
suffix:semicolon
id|insert_vm_struct
c_func
(paren
id|current-&gt;mm
comma
id|vma
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|free_initmem
id|free_initmem
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
op_amp
id|__init_begin
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
op_amp
id|__init_end
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|clear_bit
c_func
(paren
id|PG_reserved
comma
op_amp
id|virt_to_page
c_func
(paren
id|addr
)paren
op_member_access_from_pointer
id|flags
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
op_increment
id|totalram_pages
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Freeing unused kernel memory: %ldkB freed&bslash;n&quot;
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
r_void
DECL|function|free_initrd_mem
id|free_initrd_mem
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
multiline_comment|/*&n;&t; * EFI uses 4KB pages while the kernel can use 4KB  or bigger.&n;&t; * Thus EFI and the kernel may have different page sizes. It is&n;&t; * therefore possible to have the initrd share the same page as&n;&t; * the end of the kernel (given current setup).&n;&t; *&n;&t; * To avoid freeing/using the wrong page (kernel sized) we:&n;&t; *&t;- align up the beginning of initrd&n;&t; *&t;- align down the end of initrd&n;&t; *&n;&t; *  |             |&n;&t; *  |=============| a000&n;&t; *  |             |&n;&t; *  |             |&n;&t; *  |             | 9000&n;&t; *  |/////////////|&n;&t; *  |/////////////|&n;&t; *  |=============| 8000&n;&t; *  |///INITRD////|&n;&t; *  |/////////////|&n;&t; *  |/////////////| 7000&n;&t; *  |             |&n;&t; *  |KKKKKKKKKKKKK|&n;&t; *  |=============| 6000&n;&t; *  |KKKKKKKKKKKKK|&n;&t; *  |KKKKKKKKKKKKK|&n;&t; *  K=kernel using 8KB pages&n;&t; *&n;&t; * In this example, we must free page 8000 ONLY. So we must align up&n;&t; * initrd_start and keep initrd_end as is.&n;&t; */
id|start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start
)paren
suffix:semicolon
id|end
op_assign
id|end
op_amp
id|PAGE_MASK
suffix:semicolon
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
l_string|&quot;Freeing initrd memory: %ldkB freed&bslash;n&quot;
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
r_if
c_cond
(paren
op_logical_neg
id|VALID_PAGE
c_func
(paren
id|virt_to_page
c_func
(paren
id|start
)paren
)paren
)paren
r_continue
suffix:semicolon
id|clear_bit
c_func
(paren
id|PG_reserved
comma
op_amp
id|virt_to_page
c_func
(paren
id|start
)paren
op_member_access_from_pointer
id|flags
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
op_increment
id|totalram_pages
suffix:semicolon
)brace
)brace
r_void
DECL|function|si_meminfo
id|si_meminfo
(paren
r_struct
id|sysinfo
op_star
id|val
)paren
(brace
id|val-&gt;totalram
op_assign
id|totalram_pages
suffix:semicolon
id|val-&gt;sharedram
op_assign
l_int|0
suffix:semicolon
id|val-&gt;freeram
op_assign
id|nr_free_pages
c_func
(paren
)paren
suffix:semicolon
id|val-&gt;bufferram
op_assign
id|atomic_read
c_func
(paren
op_amp
id|buffermem_pages
)paren
suffix:semicolon
id|val-&gt;totalhigh
op_assign
l_int|0
suffix:semicolon
id|val-&gt;freehigh
op_assign
l_int|0
suffix:semicolon
id|val-&gt;mem_unit
op_assign
id|PAGE_SIZE
suffix:semicolon
r_return
suffix:semicolon
)brace
r_void
DECL|function|show_mem
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
macro_line|#ifdef CONFIG_DISCONTIGMEM
(brace
id|pg_data_t
op_star
id|pgdat
op_assign
id|pgdat_list
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
r_do
(brace
id|printk
c_func
(paren
l_string|&quot;Node ID: %d&bslash;n&quot;
comma
id|pgdat-&gt;node_id
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
id|pgdat-&gt;node_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|pgdat-&gt;node_mem_map
op_plus
id|i
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
id|pgdat-&gt;node_mem_map
op_plus
id|i
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
id|pgdat-&gt;node_mem_map
op_plus
id|i
)paren
)paren
id|shared
op_add_assign
id|page_count
c_func
(paren
id|pgdat-&gt;node_mem_map
op_plus
id|i
)paren
op_minus
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;t%d pages of RAM&bslash;n&quot;
comma
id|pgdat-&gt;node_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;t%d reserved pages&bslash;n&quot;
comma
id|reserved
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;t%d pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;t%d pages swap cached&bslash;n&quot;
comma
id|cached
)paren
suffix:semicolon
id|pgdat
op_assign
id|pgdat-&gt;node_next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pgdat
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Total of %ld pages in page table cache&bslash;n&quot;
comma
id|pgtable_cache_size
)paren
suffix:semicolon
id|show_buffers
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d free buffer pages&bslash;n&quot;
comma
id|nr_free_buffer_pages
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#else /* !CONFIG_DISCONTIGMEM */
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
id|i
op_assign
id|max_mapnr
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
id|total
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
id|i
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
id|mem_map
op_plus
id|i
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
id|mem_map
op_plus
id|i
)paren
)paren
id|shared
op_add_assign
id|page_count
c_func
(paren
id|mem_map
op_plus
id|i
)paren
op_minus
l_int|1
suffix:semicolon
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
id|printk
c_func
(paren
l_string|&quot;%ld pages in page table cache&bslash;n&quot;
comma
id|pgtable_cache_size
)paren
suffix:semicolon
id|show_buffers
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
)brace
multiline_comment|/*&n; * This is like put_dirty_page() but installs a clean page with PAGE_GATE protection&n; * (execute-only, typically).&n; */
r_struct
id|page
op_star
DECL|function|put_gate_page
id|put_gate_page
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|address
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
r_if
c_cond
(paren
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;put_gate_page: gate page at 0x%p not in reserved memory&bslash;n&quot;
comma
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|address
)paren
suffix:semicolon
multiline_comment|/* note: this is NOT pgd_offset()! */
id|spin_lock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
(brace
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
op_amp
id|init_mm
comma
id|pgd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
r_goto
id|out
suffix:semicolon
id|pte
op_assign
id|pte_alloc_map
c_func
(paren
op_amp
id|init_mm
comma
id|pmd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
id|pte_unmap
c_func
(paren
id|pte
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|flush_page_to_ram
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|mk_pte
c_func
(paren
id|page
comma
id|PAGE_GATE
)paren
)paren
suffix:semicolon
id|pte_unmap
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
multiline_comment|/* no need for flush_tlb */
r_return
id|page
suffix:semicolon
)brace
r_void
id|__init
DECL|function|ia64_mmu_init
id|ia64_mmu_init
(paren
r_void
op_star
id|my_cpu_data
)paren
(brace
r_int
r_int
id|flags
comma
id|rid
comma
id|pta
comma
id|impl_va_bits
suffix:semicolon
r_extern
r_void
id|__init
id|tlb_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DISABLE_VHPT
DECL|macro|VHPT_ENABLE_BIT
macro_line|#&t;define VHPT_ENABLE_BIT&t;0
macro_line|#else
macro_line|#&t;define VHPT_ENABLE_BIT&t;1
macro_line|#endif
multiline_comment|/*&n;&t; * Set up the kernel identity mapping for regions 6 and 5.  The mapping for region&n;&t; * 7 is setup up in _start().&n;&t; */
id|ia64_clear_ic
c_func
(paren
id|flags
)paren
suffix:semicolon
id|rid
op_assign
id|ia64_rid
c_func
(paren
id|IA64_REGION_ID_KERNEL
comma
id|__IA64_UNCACHED_OFFSET
)paren
suffix:semicolon
id|ia64_set_rr
c_func
(paren
id|__IA64_UNCACHED_OFFSET
comma
(paren
id|rid
op_lshift
l_int|8
)paren
op_or
(paren
id|IA64_GRANULE_SHIFT
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|rid
op_assign
id|ia64_rid
c_func
(paren
id|IA64_REGION_ID_KERNEL
comma
id|VMALLOC_START
)paren
suffix:semicolon
id|ia64_set_rr
c_func
(paren
id|VMALLOC_START
comma
(paren
id|rid
op_lshift
l_int|8
)paren
op_or
(paren
id|PAGE_SHIFT
op_lshift
l_int|2
)paren
op_or
l_int|1
)paren
suffix:semicolon
multiline_comment|/* ensure rr6 is up-to-date before inserting the PERCPU_ADDR translation: */
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
id|ia64_itr
c_func
(paren
l_int|0x2
comma
id|IA64_TR_PERCPU_DATA
comma
id|PERCPU_ADDR
comma
id|pte_val
c_func
(paren
id|mk_pte_phys
c_func
(paren
id|__pa
c_func
(paren
id|my_cpu_data
)paren
comma
id|PAGE_KERNEL
)paren
)paren
comma
id|PAGE_SHIFT
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ia64_srlz_i
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check if the virtually mapped linear page table (VMLPT) overlaps with a mapped&n;&t; * address space.  The IA-64 architecture guarantees that at least 50 bits of&n;&t; * virtual address space are implemented but if we pick a large enough page size&n;&t; * (e.g., 64KB), the mapped address space is big enough that it will overlap with&n;&t; * VMLPT.  I assume that once we run on machines big enough to warrant 64KB pages,&n;&t; * IMPL_VA_MSB will be significantly bigger, so this is unlikely to become a&n;&t; * problem in practice.  Alternatively, we could truncate the top of the mapped&n;&t; * address space to not permit mappings that would overlap with the VMLPT.&n;&t; * --davidm 00/12/06&n;&t; */
DECL|macro|pte_bits
macro_line|#&t;define pte_bits&t;&t;&t;3
DECL|macro|mapped_space_bits
macro_line|#&t;define mapped_space_bits&t;(3*(PAGE_SHIFT - pte_bits) + PAGE_SHIFT)
multiline_comment|/*&n;&t; * The virtual page table has to cover the entire implemented address space within&n;&t; * a region even though not all of this space may be mappable.  The reason for&n;&t; * this is that the Access bit and Dirty bit fault handlers perform&n;&t; * non-speculative accesses to the virtual page table, so the address range of the&n;&t; * virtual page table itself needs to be covered by virtual page table.&n;&t; */
DECL|macro|vmlpt_bits
macro_line|#&t;define vmlpt_bits&t;&t;(impl_va_bits - PAGE_SHIFT + pte_bits)
DECL|macro|POW2
macro_line|#&t;define POW2(n)&t;&t;&t;(1ULL &lt;&lt; (n))
id|impl_va_bits
op_assign
id|ffz
c_func
(paren
op_complement
(paren
id|local_cpu_data-&gt;unimpl_va_mask
op_or
(paren
l_int|7UL
op_lshift
l_int|61
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|impl_va_bits
template_param
l_int|61
)paren
id|panic
c_func
(paren
l_string|&quot;CPU has bogus IMPL_VA_MSB value of %lu!&bslash;n&quot;
comma
id|impl_va_bits
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* place the VMLPT at the end of each page-table mapped region: */
id|pta
op_assign
id|POW2
c_func
(paren
l_int|61
)paren
op_minus
id|POW2
c_func
(paren
id|vmlpt_bits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|POW2
c_func
(paren
id|mapped_space_bits
)paren
op_ge
id|pta
)paren
id|panic
c_func
(paren
l_string|&quot;mm/init: overlap between virtually mapped linear page table and &quot;
l_string|&quot;mapped kernel space!&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the (virtually mapped linear) page table address.  Bit&n;&t; * 8 selects between the short and long format, bits 2-7 the&n;&t; * size of the table, and bit 0 whether the VHPT walker is&n;&t; * enabled.&n;&t; */
id|ia64_set_pta
c_func
(paren
id|pta
op_or
(paren
l_int|0
op_lshift
l_int|8
)paren
op_or
(paren
id|vmlpt_bits
op_lshift
l_int|2
)paren
op_or
id|VHPT_ENABLE_BIT
)paren
suffix:semicolon
id|ia64_tlb_init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up the page tables.&n; */
r_void
DECL|function|paging_init
id|paging_init
(paren
r_void
)paren
(brace
r_int
r_int
id|max_dma
comma
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
id|clear_page
c_func
(paren
(paren
r_void
op_star
)paren
id|ZERO_PAGE_ADDR
)paren
suffix:semicolon
multiline_comment|/* initialize mem_map[] */
id|memset
c_func
(paren
id|zones_size
comma
l_int|0
comma
r_sizeof
(paren
id|zones_size
)paren
)paren
suffix:semicolon
id|max_dma
op_assign
id|virt_to_phys
c_func
(paren
(paren
r_void
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
id|max_low_pfn
OL
id|max_dma
)paren
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|max_low_pfn
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
id|max_low_pfn
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
r_static
r_int
DECL|function|count_pages
id|count_pages
(paren
id|u64
id|start
comma
id|u64
id|end
comma
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
op_star
id|count
op_assign
id|arg
suffix:semicolon
op_star
id|count
op_add_assign
(paren
id|end
op_minus
id|start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|count_reserved_pages
id|count_reserved_pages
(paren
id|u64
id|start
comma
id|u64
id|end
comma
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
id|num_reserved
op_assign
l_int|0
suffix:semicolon
r_int
r_int
op_star
id|count
op_assign
id|arg
suffix:semicolon
r_struct
id|page
op_star
id|pg
suffix:semicolon
r_for
c_loop
(paren
id|pg
op_assign
id|virt_to_page
c_func
(paren
id|start
)paren
suffix:semicolon
id|pg
OL
id|virt_to_page
c_func
(paren
id|end
)paren
suffix:semicolon
op_increment
id|pg
)paren
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|pg
)paren
)paren
op_increment
id|num_reserved
suffix:semicolon
op_star
id|count
op_add_assign
id|num_reserved
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|mem_init
id|mem_init
(paren
r_void
)paren
(brace
r_extern
r_char
id|__start_gate_section
(braket
)braket
suffix:semicolon
r_int
id|reserved_pages
comma
id|codesize
comma
id|datasize
comma
id|initsize
suffix:semicolon
r_int
r_int
id|num_pgt_pages
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
multiline_comment|/*&n;&t; * This needs to be called _after_ the command line has been parsed but _before_&n;&t; * any drivers that may need the PCI DMA interface are initialized or bootmem has&n;&t; * been freed.&n;&t; */
id|platform_pci_dma_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
id|num_physpages
op_assign
l_int|0
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|count_pages
comma
op_amp
id|num_physpages
)paren
suffix:semicolon
id|max_mapnr
op_assign
id|max_low_pfn
suffix:semicolon
id|high_memory
op_assign
id|__va
c_func
(paren
id|max_low_pfn
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
id|totalram_pages
op_add_assign
id|free_all_bootmem
c_func
(paren
)paren
suffix:semicolon
id|reserved_pages
op_assign
l_int|0
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|count_reserved_pages
comma
op_amp
id|reserved_pages
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
id|_stext
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
l_string|&quot;Memory: %luk/%luk available (%luk code, %luk reserved, %luk data, %luk init)&bslash;n&quot;
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
id|reserved_pages
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
multiline_comment|/*&n;&t; * Allow for enough (cached) page table pages so that we can map the entire memory&n;&t; * at least once.  Each task also needs a couple of page tables pages, so add in a&n;&t; * fudge factor for that (don&squot;t use &quot;threads-max&quot; here; that would be wrong!).&n;&t; * Don&squot;t allow the cache to be more than 10% of total memory, though.&n;&t; */
DECL|macro|NUM_TASKS
macro_line|#&t;define NUM_TASKS&t;500&t;/* typical number of tasks */
id|num_pgt_pages
op_assign
id|nr_free_pages
c_func
(paren
)paren
op_div
id|PTRS_PER_PGD
op_plus
id|NUM_TASKS
suffix:semicolon
r_if
c_cond
(paren
id|num_pgt_pages
OG
id|nr_free_pages
c_func
(paren
)paren
op_div
l_int|10
)paren
id|num_pgt_pages
op_assign
id|nr_free_pages
c_func
(paren
)paren
op_div
l_int|10
suffix:semicolon
r_if
c_cond
(paren
id|num_pgt_pages
OG
id|pgt_cache_water
(braket
l_int|1
)braket
)paren
id|pgt_cache_water
(braket
l_int|1
)braket
op_assign
id|num_pgt_pages
suffix:semicolon
multiline_comment|/* install the gate page in the global page table: */
id|put_gate_page
c_func
(paren
id|virt_to_page
c_func
(paren
id|__start_gate_section
)paren
comma
id|GATE_ADDR
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA32_SUPPORT
id|ia32_gdt_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
