multiline_comment|/*&n; * Initialize MMU support.&n; *&n; * Copyright (C) 1998-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/mempolicy.h&gt;
macro_line|#include &lt;asm/a.out.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
macro_line|#include &lt;asm/patch.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &lt;asm/mca.h&gt;
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
macro_line|#ifdef CONFIG_VIRTUAL_MEM_MAP
DECL|variable|vmalloc_end
r_int
r_int
id|vmalloc_end
op_assign
id|VMALLOC_END_INIT
suffix:semicolon
DECL|variable|vmalloc_end
id|EXPORT_SYMBOL
c_func
(paren
id|vmalloc_end
)paren
suffix:semicolon
DECL|variable|vmem_map
r_struct
id|page
op_star
id|vmem_map
suffix:semicolon
DECL|variable|vmem_map
id|EXPORT_SYMBOL
c_func
(paren
id|vmem_map
)paren
suffix:semicolon
macro_line|#endif
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
DECL|variable|zero_page_memmap_ptr
r_struct
id|page
op_star
id|zero_page_memmap_ptr
suffix:semicolon
multiline_comment|/* map entry for zero page */
DECL|variable|zero_page_memmap_ptr
id|EXPORT_SYMBOL
c_func
(paren
id|zero_page_memmap_ptr
)paren
suffix:semicolon
r_void
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
(paren
id|u64
)paren
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
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pgtable_cache_size
OG
(paren
id|u64
)paren
id|low
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|update_mmu_cache
id|update_mmu_cache
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vaddr
comma
id|pte_t
id|pte
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_exec
c_func
(paren
id|pte
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* not an executable page... */
id|page
op_assign
id|pte_page
c_func
(paren
id|pte
)paren
suffix:semicolon
multiline_comment|/* don&squot;t use VADDR: it may not be mapped on this CPU (or may have just been flushed): */
id|addr
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* i-cache is already coherent with d-cache */
id|flush_icache_range
c_func
(paren
id|addr
comma
id|addr
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
multiline_comment|/* mark page as clean */
)brace
r_inline
r_void
DECL|function|ia64_set_rbs_bot
id|ia64_set_rbs_bot
(paren
r_void
)paren
(brace
r_int
r_int
id|stack_size
op_assign
id|current-&gt;rlim
(braket
id|RLIMIT_STACK
)braket
dot
id|rlim_max
op_amp
op_minus
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|stack_size
OG
id|MAX_USER_STACK_SIZE
)paren
id|stack_size
op_assign
id|MAX_USER_STACK_SIZE
suffix:semicolon
id|current-&gt;thread.rbs_bot
op_assign
id|STACK_TOP
op_minus
id|stack_size
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
id|ia64_set_rbs_bot
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re out of memory and kmem_cache_alloc() returns NULL, we simply ignore&n;&t; * the problem.  When the process attempts to write to the register backing store&n;&t; * for the first time, it will get a SEGFAULT in this case.&n;&t; */
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
id|memset
c_func
(paren
id|vma
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|vma
)paren
)paren
suffix:semicolon
id|vma-&gt;vm_mm
op_assign
id|current-&gt;mm
suffix:semicolon
id|vma-&gt;vm_start
op_assign
id|current-&gt;thread.rbs_bot
op_amp
id|PAGE_MASK
suffix:semicolon
id|vma-&gt;vm_end
op_assign
id|vma-&gt;vm_start
op_plus
id|PAGE_SIZE
suffix:semicolon
id|vma-&gt;vm_page_prot
op_assign
id|protection_map
(braket
id|VM_DATA_DEFAULT_FLAGS
op_amp
l_int|0x7
)braket
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
id|insert_vm_struct
c_func
(paren
id|current-&gt;mm
comma
id|vma
)paren
suffix:semicolon
)brace
multiline_comment|/* map NaT-page at address zero to speed up speculative dereferencing of NULL: */
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;personality
op_amp
id|MMAP_PAGE_ZERO
)paren
)paren
(brace
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
id|memset
c_func
(paren
id|vma
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|vma
)paren
)paren
suffix:semicolon
id|vma-&gt;vm_mm
op_assign
id|current-&gt;mm
suffix:semicolon
id|vma-&gt;vm_end
op_assign
id|PAGE_SIZE
suffix:semicolon
id|vma-&gt;vm_page_prot
op_assign
id|__pgprot
c_func
(paren
id|pgprot_val
c_func
(paren
id|PAGE_READONLY
)paren
op_or
id|_PAGE_MA_NAT
)paren
suffix:semicolon
id|vma-&gt;vm_flags
op_assign
id|VM_READ
op_or
id|VM_MAYREAD
op_or
id|VM_IO
op_or
id|VM_RESERVED
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
comma
id|eaddr
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ia64_imva
c_func
(paren
id|__init_begin
)paren
suffix:semicolon
id|eaddr
op_assign
(paren
r_int
r_int
)paren
id|ia64_imva
c_func
(paren
id|__init_end
)paren
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
id|eaddr
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
op_increment
id|totalram_pages
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
l_string|&quot;Freeing unused kernel memory: %ldkB freed&bslash;n&quot;
comma
(paren
id|__init_end
op_minus
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
r_struct
id|page
op_star
id|page
suffix:semicolon
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
id|virt_addr_valid
c_func
(paren
id|start
)paren
)paren
r_continue
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|start
)paren
suffix:semicolon
id|ClearPageReserved
c_func
(paren
id|page
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
multiline_comment|/*&n; * This is like put_dirty_page() but installs a clean page in the kernel&squot;s page table.&n; */
r_struct
id|page
op_star
DECL|function|put_kernel_page
id|put_kernel_page
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|address
comma
id|pgprot_t
id|pgprot
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
id|KERN_ERR
l_string|&quot;put_kernel_page: page at 0x%p not in reserved memory&bslash;n&quot;
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
id|pgprot
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
r_static
r_void
DECL|function|setup_gate
id|setup_gate
(paren
r_void
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
multiline_comment|/*&n;&t; * Map the gate page twice: once read-only to export the ELF headers etc. and once&n;&t; * execute-only page to enable privilege-promotion via &quot;epc&quot;:&n;&t; */
id|page
op_assign
id|virt_to_page
c_func
(paren
id|ia64_imva
c_func
(paren
id|__start_gate_section
)paren
)paren
suffix:semicolon
id|put_kernel_page
c_func
(paren
id|page
comma
id|GATE_ADDR
comma
id|PAGE_READONLY
)paren
suffix:semicolon
macro_line|#ifdef HAVE_BUGGY_SEGREL
id|page
op_assign
id|virt_to_page
c_func
(paren
id|ia64_imva
c_func
(paren
id|__start_gate_section
op_plus
id|PAGE_SIZE
)paren
)paren
suffix:semicolon
id|put_kernel_page
c_func
(paren
id|page
comma
id|GATE_ADDR
op_plus
id|PAGE_SIZE
comma
id|PAGE_GATE
)paren
suffix:semicolon
macro_line|#else
id|put_kernel_page
c_func
(paren
id|page
comma
id|GATE_ADDR
op_plus
id|PERCPU_PAGE_SIZE
comma
id|PAGE_GATE
)paren
suffix:semicolon
macro_line|#endif
id|ia64_patch_gate
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
id|__devinit
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
id|psr
comma
id|pta
comma
id|impl_va_bits
suffix:semicolon
r_extern
r_void
id|__devinit
id|tlb_init
(paren
r_void
)paren
suffix:semicolon
r_int
id|cpu
suffix:semicolon
macro_line|#ifdef CONFIG_DISABLE_VHPT
DECL|macro|VHPT_ENABLE_BIT
macro_line|#&t;define VHPT_ENABLE_BIT&t;0
macro_line|#else
macro_line|#&t;define VHPT_ENABLE_BIT&t;1
macro_line|#endif
multiline_comment|/* Pin mapping for percpu area into TLB */
id|psr
op_assign
id|ia64_clear_ic
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
id|pfn_pte
c_func
(paren
id|__pa
c_func
(paren
id|my_cpu_data
)paren
op_rshift
id|PAGE_SHIFT
comma
id|PAGE_KERNEL
)paren
)paren
comma
id|PERCPU_PAGE_SHIFT
)paren
suffix:semicolon
id|ia64_set_psr
c_func
(paren
id|psr
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
macro_line|#ifdef&t;CONFIG_HUGETLB_PAGE
id|ia64_set_rr
c_func
(paren
id|HPAGE_REGION_BASE
comma
id|HPAGE_SHIFT
op_lshift
l_int|2
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* mca handler uses cr.lid as key to pick the right entry */
id|ia64_mca_tlb_list
(braket
id|cpu
)braket
dot
id|cr_lid
op_assign
id|ia64_getreg
c_func
(paren
id|_IA64_REG_CR_LID
)paren
suffix:semicolon
multiline_comment|/* insert this percpu data information into our list for MCA recovery purposes */
id|ia64_mca_tlb_list
(braket
id|cpu
)braket
dot
id|percpu_paddr
op_assign
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
suffix:semicolon
multiline_comment|/* Also save per-cpu tlb flush recipe for use in physical mode mca handler */
id|ia64_mca_tlb_list
(braket
id|cpu
)braket
dot
id|ptce_base
op_assign
id|local_cpu_data-&gt;ptce_base
suffix:semicolon
id|ia64_mca_tlb_list
(braket
id|cpu
)braket
dot
id|ptce_count
(braket
l_int|0
)braket
op_assign
id|local_cpu_data-&gt;ptce_count
(braket
l_int|0
)braket
suffix:semicolon
id|ia64_mca_tlb_list
(braket
id|cpu
)braket
dot
id|ptce_count
(braket
l_int|1
)braket
op_assign
id|local_cpu_data-&gt;ptce_count
(braket
l_int|1
)braket
suffix:semicolon
id|ia64_mca_tlb_list
(braket
id|cpu
)braket
dot
id|ptce_stride
(braket
l_int|0
)braket
op_assign
id|local_cpu_data-&gt;ptce_stride
(braket
l_int|0
)braket
suffix:semicolon
id|ia64_mca_tlb_list
(braket
id|cpu
)braket
dot
id|ptce_stride
(braket
l_int|1
)braket
op_assign
id|local_cpu_data-&gt;ptce_stride
(braket
l_int|1
)braket
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_VIRTUAL_MEM_MAP
r_int
DECL|function|create_mem_map_page_table
id|create_mem_map_page_table
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
id|address
comma
id|start_page
comma
id|end_page
suffix:semicolon
r_struct
id|page
op_star
id|map_start
comma
op_star
id|map_end
suffix:semicolon
r_int
id|node
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
id|map_start
op_assign
id|vmem_map
op_plus
(paren
id|__pa
c_func
(paren
id|start
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|map_end
op_assign
id|vmem_map
op_plus
(paren
id|__pa
c_func
(paren
id|end
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|start_page
op_assign
(paren
r_int
r_int
)paren
id|map_start
op_amp
id|PAGE_MASK
suffix:semicolon
id|end_page
op_assign
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|map_end
)paren
suffix:semicolon
id|node
op_assign
id|paddr_to_nid
c_func
(paren
id|__pa
c_func
(paren
id|start
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|address
op_assign
id|start_page
suffix:semicolon
id|address
OL
id|end_page
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|address
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
id|pgd_populate
c_func
(paren
op_amp
id|init_mm
comma
id|pgd
comma
id|alloc_bootmem_pages_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|node
)paren
comma
id|PAGE_SIZE
)paren
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
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
)paren
id|pmd_populate_kernel
c_func
(paren
op_amp
id|init_mm
comma
id|pmd
comma
id|alloc_bootmem_pages_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|node
)paren
comma
id|PAGE_SIZE
)paren
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
id|set_pte
c_func
(paren
id|pte
comma
id|pfn_pte
c_func
(paren
id|__pa
c_func
(paren
id|alloc_bootmem_pages_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|node
)paren
comma
id|PAGE_SIZE
)paren
)paren
op_rshift
id|PAGE_SHIFT
comma
id|PAGE_KERNEL
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|memmap_init_callback_data
r_struct
id|memmap_init_callback_data
(brace
DECL|member|start
r_struct
id|page
op_star
id|start
suffix:semicolon
DECL|member|end
r_struct
id|page
op_star
id|end
suffix:semicolon
DECL|member|nid
r_int
id|nid
suffix:semicolon
DECL|member|zone
r_int
r_int
id|zone
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
DECL|function|virtual_memmap_init
id|virtual_memmap_init
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
r_struct
id|memmap_init_callback_data
op_star
id|args
suffix:semicolon
r_struct
id|page
op_star
id|map_start
comma
op_star
id|map_end
suffix:semicolon
id|args
op_assign
(paren
r_struct
id|memmap_init_callback_data
op_star
)paren
id|arg
suffix:semicolon
id|map_start
op_assign
id|vmem_map
op_plus
(paren
id|__pa
c_func
(paren
id|start
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|map_end
op_assign
id|vmem_map
op_plus
(paren
id|__pa
c_func
(paren
id|end
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map_start
OL
id|args-&gt;start
)paren
id|map_start
op_assign
id|args-&gt;start
suffix:semicolon
r_if
c_cond
(paren
id|map_end
OG
id|args-&gt;end
)paren
id|map_end
op_assign
id|args-&gt;end
suffix:semicolon
multiline_comment|/*&n;&t; * We have to initialize &quot;out of bounds&quot; struct page elements that fit completely&n;&t; * on the same pages that were allocated for the &quot;in bounds&quot; elements because they&n;&t; * may be referenced later (and found to be &quot;reserved&quot;).&n;&t; */
id|map_start
op_sub_assign
(paren
(paren
r_int
r_int
)paren
id|map_start
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_div
r_sizeof
(paren
r_struct
id|page
)paren
suffix:semicolon
id|map_end
op_add_assign
(paren
(paren
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|map_end
)paren
op_minus
(paren
r_int
r_int
)paren
id|map_end
)paren
op_div
r_sizeof
(paren
r_struct
id|page
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map_start
OL
id|map_end
)paren
id|memmap_init_zone
c_func
(paren
id|map_start
comma
(paren
r_int
r_int
)paren
(paren
id|map_end
op_minus
id|map_start
)paren
comma
id|args-&gt;nid
comma
id|args-&gt;zone
comma
id|page_to_pfn
c_func
(paren
id|map_start
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|memmap_init
id|memmap_init
(paren
r_struct
id|page
op_star
id|start
comma
r_int
r_int
id|size
comma
r_int
id|nid
comma
r_int
r_int
id|zone
comma
r_int
r_int
id|start_pfn
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|vmem_map
)paren
id|memmap_init_zone
c_func
(paren
id|start
comma
id|size
comma
id|nid
comma
id|zone
comma
id|start_pfn
)paren
suffix:semicolon
r_else
(brace
r_struct
id|memmap_init_callback_data
id|args
suffix:semicolon
id|args.start
op_assign
id|start
suffix:semicolon
id|args.end
op_assign
id|start
op_plus
id|size
suffix:semicolon
id|args.nid
op_assign
id|nid
suffix:semicolon
id|args.zone
op_assign
id|zone
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|virtual_memmap_init
comma
op_amp
id|args
)paren
suffix:semicolon
)brace
)brace
r_int
DECL|function|ia64_pfn_valid
id|ia64_pfn_valid
(paren
r_int
r_int
id|pfn
)paren
(brace
r_char
id|byte
suffix:semicolon
r_struct
id|page
op_star
id|pg
op_assign
id|pfn_to_page
c_func
(paren
id|pfn
)paren
suffix:semicolon
r_return
(paren
id|__get_user
c_func
(paren
id|byte
comma
(paren
r_char
op_star
)paren
id|pg
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
(paren
(paren
id|u64
)paren
id|pg
op_amp
id|PAGE_MASK
)paren
op_eq
(paren
(paren
(paren
id|u64
)paren
(paren
id|pg
op_plus
l_int|1
)paren
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
)paren
)paren
op_logical_or
(paren
id|__get_user
c_func
(paren
id|byte
comma
(paren
r_char
op_star
)paren
(paren
id|pg
op_plus
l_int|1
)paren
op_minus
l_int|1
)paren
op_eq
l_int|0
)paren
)paren
suffix:semicolon
)brace
DECL|variable|ia64_pfn_valid
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_pfn_valid
)paren
suffix:semicolon
r_int
DECL|function|find_largest_hole
id|find_largest_hole
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
id|u64
op_star
id|max_gap
op_assign
id|arg
suffix:semicolon
r_static
id|u64
id|last_end
op_assign
id|PAGE_OFFSET
suffix:semicolon
multiline_comment|/* NOTE: this algorithm assumes efi memmap table is ordered */
r_if
c_cond
(paren
op_star
id|max_gap
OL
(paren
id|start
op_minus
id|last_end
)paren
)paren
op_star
id|max_gap
op_assign
id|start
op_minus
id|last_end
suffix:semicolon
id|last_end
op_assign
id|end
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_VIRTUAL_MEM_MAP */
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
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|start
)paren
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
multiline_comment|/*&n; * Boot command-line option &quot;nolwsys&quot; can be used to disable the use of any light-weight&n; * system call handler.  When this option is in effect, all fsyscalls will end up bubbling&n; * down into the kernel and calling the normal (heavy-weight) syscall handler.  This is&n; * useful for performance testing, but conceivably could also come in handy for debugging&n; * purposes.&n; */
DECL|variable|nolwsys
r_static
r_int
id|nolwsys
suffix:semicolon
r_static
r_int
id|__init
DECL|function|nolwsys_setup
id|nolwsys_setup
(paren
r_char
op_star
id|s
)paren
(brace
id|nolwsys
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nolwsys&quot;
comma
id|nolwsys_setup
)paren
suffix:semicolon
r_void
DECL|function|mem_init
id|mem_init
(paren
r_void
)paren
(brace
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
id|pg_data_t
op_star
id|pgdat
suffix:semicolon
r_int
id|i
suffix:semicolon
r_static
r_struct
id|kcore_list
id|kcore_mem
comma
id|kcore_vmem
comma
id|kcore_kernel
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
multiline_comment|/*&n;&t; * This needs to be called _after_ the command line has been parsed but _before_&n;&t; * any drivers that may need the PCI DMA interface are initialized or bootmem has&n;&t; * been freed.&n;&t; */
id|platform_dma_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
id|max_mapnr
op_assign
id|max_low_pfn
suffix:semicolon
macro_line|#endif
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
id|kclist_add
c_func
(paren
op_amp
id|kcore_mem
comma
id|__va
c_func
(paren
l_int|0
)paren
comma
id|max_low_pfn
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
id|kclist_add
c_func
(paren
op_amp
id|kcore_vmem
comma
(paren
r_void
op_star
)paren
id|VMALLOC_START
comma
id|VMALLOC_END
op_minus
id|VMALLOC_START
)paren
suffix:semicolon
id|kclist_add
c_func
(paren
op_amp
id|kcore_kernel
comma
id|_stext
comma
id|_end
op_minus
id|_stext
)paren
suffix:semicolon
id|for_each_pgdat
c_func
(paren
id|pgdat
)paren
id|totalram_pages
op_add_assign
id|free_all_bootmem_node
c_func
(paren
id|pgdat
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
id|_etext
op_minus
(paren
r_int
r_int
)paren
id|_stext
suffix:semicolon
id|datasize
op_assign
(paren
r_int
r_int
)paren
id|_edata
op_minus
(paren
r_int
r_int
)paren
id|_etext
suffix:semicolon
id|initsize
op_assign
(paren
r_int
r_int
)paren
id|__init_end
op_minus
(paren
r_int
r_int
)paren
id|__init_begin
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Memory: %luk/%luk available (%luk code, %luk reserved, &quot;
l_string|&quot;%luk data, %luk init)&bslash;n&quot;
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
(paren
id|u64
)paren
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
multiline_comment|/*&n;&t; * For fsyscall entrpoints with no light-weight handler, use the ordinary&n;&t; * (heavy-weight) handler, but mark it by setting bit 0, so the fsyscall entry&n;&t; * code can tell them apart.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_syscalls
suffix:semicolon
op_increment
id|i
)paren
(brace
r_extern
r_int
r_int
id|fsyscall_table
(braket
id|NR_syscalls
)braket
suffix:semicolon
r_extern
r_int
r_int
id|sys_call_table
(braket
id|NR_syscalls
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fsyscall_table
(braket
id|i
)braket
op_logical_or
id|nolwsys
)paren
id|fsyscall_table
(braket
id|i
)braket
op_assign
id|sys_call_table
(braket
id|i
)braket
op_or
l_int|1
suffix:semicolon
)brace
id|setup_gate
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* setup gate pages before we free up boot memory... */
macro_line|#ifdef CONFIG_IA32_SUPPORT
id|ia32_boot_gdt_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
