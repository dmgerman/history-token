multiline_comment|/*&n; *  linux/arch/alpha/mm/init.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
multiline_comment|/* 2.3.x zone allocator, 1999 Andrea Arcangeli &lt;andrea@suse.de&gt; */
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
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt; /* max_low_pfn */
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/console.h&gt;
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
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|original_pcb
r_static
r_struct
id|pcb_struct
id|original_pcb
suffix:semicolon
id|pgd_t
op_star
DECL|function|pgd_alloc
id|pgd_alloc
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|pgd_t
op_star
id|ret
comma
op_star
id|init
suffix:semicolon
id|ret
op_assign
(paren
id|pgd_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
id|init
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
l_int|0UL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|clear_page
c_func
(paren
id|ret
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ALPHA_LARGE_VMALLOC
id|memcpy
(paren
id|ret
op_plus
id|USER_PTRS_PER_PGD
comma
id|init
op_plus
id|USER_PTRS_PER_PGD
comma
(paren
id|PTRS_PER_PGD
op_minus
id|USER_PTRS_PER_PGD
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
macro_line|#else
id|pgd_val
c_func
(paren
id|ret
(braket
id|PTRS_PER_PGD
op_minus
l_int|2
)braket
)paren
op_assign
id|pgd_val
c_func
(paren
id|init
(braket
id|PTRS_PER_PGD
op_minus
l_int|2
)braket
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* The last PGD entry is the VPTB self-map.  */
id|pgd_val
c_func
(paren
id|ret
(braket
id|PTRS_PER_PGD
op_minus
l_int|1
)braket
)paren
op_assign
id|pte_val
c_func
(paren
id|mk_pte
c_func
(paren
id|virt_to_page
c_func
(paren
id|ret
)paren
comma
id|PAGE_KERNEL
)paren
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
id|pte_t
op_star
DECL|function|pte_alloc_one_kernel
id|pte_alloc_one_kernel
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
id|pte_t
op_star
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_REPEAT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
id|clear_page
c_func
(paren
id|pte
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/*&n; * BAD_PAGE is the page that is used for page faults when linux&n; * is out-of-memory. Older versions of linux just did a&n; * do_exit(), but using this instead means there is less risk&n; * for a process dying in kernel mode, possibly leaving an inode&n; * unused etc..&n; *&n; * BAD_PAGETABLE is the accompanying page-table: it is initialized&n; * to point to BAD_PAGE entries.&n; *&n; * ZERO_PAGE is a special page that is used for zero-initialized&n; * data and COW.&n; */
id|pmd_t
op_star
DECL|function|__bad_pagetable
id|__bad_pagetable
c_func
(paren
r_void
)paren
(brace
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|EMPTY_PGT
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
(paren
id|pmd_t
op_star
)paren
id|EMPTY_PGT
suffix:semicolon
)brace
id|pte_t
DECL|function|__bad_page
id|__bad_page
c_func
(paren
r_void
)paren
(brace
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|EMPTY_PGE
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
id|pte_mkdirty
c_func
(paren
id|mk_pte
c_func
(paren
id|virt_to_page
c_func
(paren
id|EMPTY_PGE
)paren
comma
id|PAGE_SHARED
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_DISCONTIGMEM
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
id|free
op_assign
l_int|0
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
l_string|&quot;&bslash;nMem-info:&bslash;n&quot;
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
op_logical_neg
id|page_count
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
id|free
op_increment
suffix:semicolon
r_else
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
l_string|&quot;%ld pages of RAM&bslash;n&quot;
comma
id|total
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%ld free pages&bslash;n&quot;
comma
id|free
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%ld reserved pages&bslash;n&quot;
comma
id|reserved
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%ld pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%ld pages swap cached&bslash;n&quot;
comma
id|cached
)paren
suffix:semicolon
)brace
macro_line|#endif
r_static
r_inline
r_int
r_int
DECL|function|load_PCB
id|load_PCB
c_func
(paren
r_struct
id|pcb_struct
op_star
id|pcb
)paren
(brace
r_register
r_int
r_int
id|sp
id|__asm__
c_func
(paren
l_string|&quot;$30&quot;
)paren
suffix:semicolon
id|pcb-&gt;ksp
op_assign
id|sp
suffix:semicolon
r_return
id|__reload_thread
c_func
(paren
id|pcb
)paren
suffix:semicolon
)brace
multiline_comment|/* Set up initial PCB, VPTB, and other such nicities.  */
r_static
r_inline
r_void
DECL|function|switch_to_system_map
id|switch_to_system_map
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|newptbr
suffix:semicolon
r_int
r_int
id|original_pcb_ptr
suffix:semicolon
multiline_comment|/* Initialize the kernel&squot;s page tables.  Linux puts the vptb in&n;&t;   the last slot of the L1 page table.  */
id|memset
c_func
(paren
id|swapper_pg_dir
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|newptbr
op_assign
(paren
(paren
r_int
r_int
)paren
id|swapper_pg_dir
op_minus
id|PAGE_OFFSET
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|pgd_val
c_func
(paren
id|swapper_pg_dir
(braket
l_int|1023
)braket
)paren
op_assign
(paren
id|newptbr
op_lshift
l_int|32
)paren
op_or
id|pgprot_val
c_func
(paren
id|PAGE_KERNEL
)paren
suffix:semicolon
multiline_comment|/* Set the vptb.  This is often done by the bootloader, but &n;&t;   shouldn&squot;t be required.  */
r_if
c_cond
(paren
id|hwrpb-&gt;vptb
op_ne
l_int|0xfffffffe00000000
)paren
(brace
id|wrvptptr
c_func
(paren
l_int|0xfffffffe00000000
)paren
suffix:semicolon
id|hwrpb-&gt;vptb
op_assign
l_int|0xfffffffe00000000
suffix:semicolon
id|hwrpb_update_checksum
c_func
(paren
id|hwrpb
)paren
suffix:semicolon
)brace
multiline_comment|/* Also set up the real kernel PCB while we&squot;re at it.  */
id|init_thread_info.pcb.ptbr
op_assign
id|newptbr
suffix:semicolon
id|init_thread_info.pcb.flags
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* set FEN, clear everything else */
id|original_pcb_ptr
op_assign
id|load_PCB
c_func
(paren
op_amp
id|init_thread_info.pcb
)paren
suffix:semicolon
id|tbia
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Save off the contents of the original PCB so that we can&n;&t;   restore the original console&squot;s page tables for a clean reboot.&n;&n;&t;   Note that the PCB is supposed to be a physical address, but&n;&t;   since KSEG values also happen to work, folks get confused.&n;&t;   Check this here.  */
r_if
c_cond
(paren
id|original_pcb_ptr
OL
id|PAGE_OFFSET
)paren
(brace
id|original_pcb_ptr
op_assign
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|original_pcb_ptr
)paren
suffix:semicolon
)brace
id|original_pcb
op_assign
op_star
(paren
r_struct
id|pcb_struct
op_star
)paren
id|original_pcb_ptr
suffix:semicolon
)brace
DECL|variable|callback_init_done
r_int
id|callback_init_done
suffix:semicolon
r_void
op_star
id|__init
DECL|function|callback_init
id|callback_init
c_func
(paren
r_void
op_star
id|kernel_end
)paren
(brace
r_struct
id|crb_struct
op_star
id|crb
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_void
op_star
id|two_pages
suffix:semicolon
multiline_comment|/* Starting at the HWRPB, locate the CRB. */
id|crb
op_assign
(paren
r_struct
id|crb_struct
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|hwrpb
op_plus
id|hwrpb-&gt;crb_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alpha_using_srm
)paren
(brace
multiline_comment|/* Tell the console whither it is to be remapped. */
r_if
c_cond
(paren
id|srm_fixup
c_func
(paren
id|VMALLOC_START
comma
(paren
r_int
r_int
)paren
id|hwrpb
)paren
)paren
id|__halt
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* &quot;We&squot;re boned.&quot;  --Bender */
multiline_comment|/* Edit the procedure descriptors for DISPATCH and FIXUP. */
id|crb-&gt;dispatch_va
op_assign
(paren
r_struct
id|procdesc_struct
op_star
)paren
(paren
id|VMALLOC_START
op_plus
(paren
r_int
r_int
)paren
id|crb-&gt;dispatch_va
op_minus
id|crb-&gt;map
(braket
l_int|0
)braket
dot
id|va
)paren
suffix:semicolon
id|crb-&gt;fixup_va
op_assign
(paren
r_struct
id|procdesc_struct
op_star
)paren
(paren
id|VMALLOC_START
op_plus
(paren
r_int
r_int
)paren
id|crb-&gt;fixup_va
op_minus
id|crb-&gt;map
(braket
l_int|0
)braket
dot
id|va
)paren
suffix:semicolon
)brace
id|switch_to_system_map
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Allocate one PGD and one PMD.  In the case of SRM, we&squot;ll need&n;&t;   these to actually remap the console.  There is an assumption&n;&t;   here that only one of each is needed, and this allows for 8MB.&n;&t;   On systems with larger consoles, additional pages will be&n;&t;   allocated as needed during the mapping process.&n;&n;&t;   In the case of not SRM, but not CONFIG_ALPHA_LARGE_VMALLOC,&n;&t;   we need to allocate the PGD we use for vmalloc before we start&n;&t;   forking other tasks.  */
id|two_pages
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|kernel_end
op_plus
op_complement
id|PAGE_MASK
)paren
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|kernel_end
op_assign
id|two_pages
op_plus
l_int|2
op_star
id|PAGE_SIZE
suffix:semicolon
id|memset
c_func
(paren
id|two_pages
comma
l_int|0
comma
l_int|2
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|VMALLOC_START
)paren
suffix:semicolon
id|pgd_set
c_func
(paren
id|pgd
comma
(paren
id|pmd_t
op_star
)paren
id|two_pages
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|VMALLOC_START
)paren
suffix:semicolon
id|pmd_set
c_func
(paren
id|pmd
comma
(paren
id|pte_t
op_star
)paren
(paren
id|two_pages
op_plus
id|PAGE_SIZE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alpha_using_srm
)paren
(brace
r_static
r_struct
id|vm_struct
id|console_remap_vm
suffix:semicolon
r_int
r_int
id|vaddr
op_assign
id|VMALLOC_START
suffix:semicolon
r_int
r_int
id|i
comma
id|j
suffix:semicolon
multiline_comment|/* Set up the third level PTEs and update the virtual&n;&t;&t;   addresses of the CRB entries.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|crb-&gt;map_entries
suffix:semicolon
op_increment
id|i
)paren
(brace
r_int
r_int
id|pfn
op_assign
id|crb-&gt;map
(braket
id|i
)braket
dot
id|pa
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|crb-&gt;map
(braket
id|i
)braket
dot
id|va
op_assign
id|vaddr
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
id|crb-&gt;map
(braket
id|i
)braket
dot
id|count
suffix:semicolon
op_increment
id|j
)paren
(brace
multiline_comment|/* Newer console&squot;s (especially on larger&n;&t;&t;&t;&t;   systems) may require more pages of&n;&t;&t;&t;&t;   PTEs. Grab additional pages as needed. */
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
id|vaddr
)paren
)paren
(brace
id|memset
c_func
(paren
id|kernel_end
comma
l_int|0
comma
id|PAGE_SIZE
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
id|pmd_set
c_func
(paren
id|pmd
comma
(paren
id|pte_t
op_star
)paren
id|kernel_end
)paren
suffix:semicolon
id|kernel_end
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|set_pte
c_func
(paren
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|vaddr
)paren
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
id|pfn
op_increment
suffix:semicolon
id|vaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
multiline_comment|/* Let vmalloc know that we&squot;ve allocated some space.  */
id|console_remap_vm.flags
op_assign
id|VM_ALLOC
suffix:semicolon
id|console_remap_vm.addr
op_assign
(paren
r_void
op_star
)paren
id|VMALLOC_START
suffix:semicolon
id|console_remap_vm.size
op_assign
id|vaddr
op_minus
id|VMALLOC_START
suffix:semicolon
id|vmlist
op_assign
op_amp
id|console_remap_vm
suffix:semicolon
)brace
id|callback_init_done
op_assign
l_int|1
suffix:semicolon
r_return
id|kernel_end
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * paging_init() sets up the memory map.&n; */
r_void
DECL|function|paging_init
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
id|dma_pfn
comma
id|high_pfn
suffix:semicolon
id|dma_pfn
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
id|high_pfn
op_assign
id|max_pfn
op_assign
id|max_low_pfn
suffix:semicolon
r_if
c_cond
(paren
id|dma_pfn
op_ge
id|high_pfn
)paren
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|high_pfn
suffix:semicolon
r_else
(brace
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|dma_pfn
suffix:semicolon
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
id|high_pfn
op_minus
id|dma_pfn
suffix:semicolon
)brace
multiline_comment|/* Initialize mem_map[].  */
id|free_area_init
c_func
(paren
id|zones_size
)paren
suffix:semicolon
multiline_comment|/* Initialize the kernel&squot;s ZERO_PGE. */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|ZERO_PGE
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_SRM)
r_void
DECL|function|srm_paging_stop
id|srm_paging_stop
(paren
r_void
)paren
(brace
multiline_comment|/* Move the vptb back to where the SRM console expects it.  */
id|swapper_pg_dir
(braket
l_int|1
)braket
op_assign
id|swapper_pg_dir
(braket
l_int|1023
)braket
suffix:semicolon
id|tbia
c_func
(paren
)paren
suffix:semicolon
id|wrvptptr
c_func
(paren
l_int|0x200000000
)paren
suffix:semicolon
id|hwrpb-&gt;vptb
op_assign
l_int|0x200000000
suffix:semicolon
id|hwrpb_update_checksum
c_func
(paren
id|hwrpb
)paren
suffix:semicolon
multiline_comment|/* Reload the page tables that the console had in use.  */
id|load_PCB
c_func
(paren
op_amp
id|original_pcb
)paren
suffix:semicolon
id|tbia
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef CONFIG_DISCONTIGMEM
r_static
r_void
id|__init
DECL|function|printk_memory_info
id|printk_memory_info
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
comma
id|tmp
suffix:semicolon
r_extern
r_int
id|page_is_ram
c_func
(paren
r_int
r_int
)paren
id|__init
suffix:semicolon
r_extern
r_char
id|_text
comma
id|_etext
comma
id|_data
comma
id|_edata
suffix:semicolon
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
multiline_comment|/* printk all informations */
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
id|_data
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
l_string|&quot;Memory: %luk/%luk available (%luk kernel code, %luk reserved, %luk data, %luk init)&bslash;n&quot;
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
)brace
r_void
id|__init
DECL|function|mem_init
id|mem_init
c_func
(paren
r_void
)paren
(brace
id|max_mapnr
op_assign
id|num_physpages
op_assign
id|max_low_pfn
suffix:semicolon
id|totalram_pages
op_add_assign
id|free_all_bootmem
c_func
(paren
)paren
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
id|max_low_pfn
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
id|printk_memory_info
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_DISCONTIGMEM */
r_void
DECL|function|free_reserved_mem
id|free_reserved_mem
c_func
(paren
r_void
op_star
id|start
comma
r_void
op_star
id|end
)paren
(brace
r_void
op_star
id|__start
op_assign
id|start
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|__start
OL
id|end
suffix:semicolon
id|__start
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
id|__start
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|__start
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|__start
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
)brace
)brace
r_void
DECL|function|free_initmem
id|free_initmem
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
id|free_reserved_mem
c_func
(paren
op_amp
id|__init_begin
comma
op_amp
id|__init_end
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;Freeing unused kernel memory: %ldk freed&bslash;n&quot;
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
r_void
DECL|function|free_initrd_mem
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
id|free_reserved_mem
c_func
(paren
(paren
r_void
op_star
)paren
id|start
comma
(paren
r_void
op_star
)paren
id|end
)paren
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
)brace
macro_line|#endif
eof
