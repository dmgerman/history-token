multiline_comment|/*  $Id: init.c,v 1.103 2001/11/19 19:03:08 davem Exp $&n; *  linux/arch/sparc/mm/init.c&n; *&n; *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *  Copyright (C) 1995 Eddie C. Dost (ecd@skynet.be)&n; *  Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *  Copyright (C) 2000 Anton Blanchard (anton@samba.org)&n; */
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
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/vac-ops.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;&t;/* bug in asm-generic/tlb.h: check_pgt_cache */
macro_line|#include &lt;asm/tlb.h&gt;
DECL|variable|mmu_gathers
id|mmu_gather_t
id|mmu_gathers
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|sparc_valid_addr_bitmap
r_int
r_int
op_star
id|sparc_valid_addr_bitmap
suffix:semicolon
DECL|variable|phys_base
r_int
r_int
id|phys_base
suffix:semicolon
DECL|variable|page_kernel
r_int
r_int
id|page_kernel
suffix:semicolon
DECL|variable|sp_banks
r_struct
id|sparc_phys_banks
id|sp_banks
(braket
id|SPARC_PHYS_BANKS
)braket
suffix:semicolon
DECL|variable|sparc_unmapped_base
r_int
r_int
id|sparc_unmapped_base
suffix:semicolon
DECL|variable|pgt_quicklists
r_struct
id|pgtable_cache_struct
id|pgt_quicklists
suffix:semicolon
multiline_comment|/* References to section boundaries */
r_extern
r_char
id|__init_begin
comma
id|__init_end
comma
id|_start
comma
id|_end
comma
id|etext
comma
id|edata
suffix:semicolon
multiline_comment|/* Initial ramdisk setup */
r_extern
r_int
r_int
id|sparc_ramdisk_image
suffix:semicolon
r_extern
r_int
r_int
id|sparc_ramdisk_size
suffix:semicolon
DECL|variable|highstart_pfn
DECL|variable|highend_pfn
r_int
r_int
id|highstart_pfn
comma
id|highend_pfn
suffix:semicolon
DECL|variable|kmap_pte
id|pte_t
op_star
id|kmap_pte
suffix:semicolon
DECL|variable|kmap_prot
id|pgprot_t
id|kmap_prot
suffix:semicolon
DECL|macro|kmap_get_fixed_pte
mdefine_line|#define kmap_get_fixed_pte(vaddr) &bslash;&n;&t;pte_offset_kernel(pmd_offset(pgd_offset_k(vaddr), (vaddr)), (vaddr))
DECL|function|kmap_init
r_void
id|__init
id|kmap_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* cache the first kmap pte */
id|kmap_pte
op_assign
id|kmap_get_fixed_pte
c_func
(paren
id|FIX_KMAP_BEGIN
)paren
suffix:semicolon
id|kmap_prot
op_assign
id|__pgprot
c_func
(paren
id|SRMMU_ET_PTE
op_or
id|SRMMU_PRIV
op_or
id|SRMMU_CACHE
)paren
suffix:semicolon
)brace
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
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
id|printk
c_func
(paren
l_string|&quot;%ld pages of RAM&bslash;n&quot;
comma
id|totalram_pages
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d free pages&bslash;n&quot;
comma
id|nr_free_pages
c_func
(paren
)paren
)paren
suffix:semicolon
macro_line|#if 0 /* undefined pgtable_cache_size, pgd_cache_size */
id|printk
c_func
(paren
l_string|&quot;%ld pages in page table cache&bslash;n&quot;
comma
id|pgtable_cache_size
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4m
op_logical_or
id|sparc_cpu_model
op_eq
id|sun4d
)paren
id|printk
c_func
(paren
l_string|&quot;%ld entries in page dir cache&bslash;n&quot;
comma
id|pgd_cache_size
)paren
suffix:semicolon
macro_line|#endif&t;
macro_line|#endif
)brace
r_extern
id|pgprot_t
id|protection_map
(braket
l_int|16
)braket
suffix:semicolon
DECL|function|sparc_context_init
r_void
id|__init
id|sparc_context_init
c_func
(paren
r_int
id|numctx
)paren
(brace
r_int
id|ctx
suffix:semicolon
id|ctx_list_pool
op_assign
id|__alloc_bootmem
c_func
(paren
id|numctx
op_star
r_sizeof
(paren
r_struct
id|ctx_list
)paren
comma
id|SMP_CACHE_BYTES
comma
l_int|0UL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ctx
op_assign
l_int|0
suffix:semicolon
id|ctx
OL
id|numctx
suffix:semicolon
id|ctx
op_increment
)paren
(brace
r_struct
id|ctx_list
op_star
id|clist
suffix:semicolon
id|clist
op_assign
(paren
id|ctx_list_pool
op_plus
id|ctx
)paren
suffix:semicolon
id|clist-&gt;ctx_number
op_assign
id|ctx
suffix:semicolon
id|clist-&gt;ctx_mm
op_assign
l_int|0
suffix:semicolon
)brace
id|ctx_free.next
op_assign
id|ctx_free.prev
op_assign
op_amp
id|ctx_free
suffix:semicolon
id|ctx_used.next
op_assign
id|ctx_used.prev
op_assign
op_amp
id|ctx_used
suffix:semicolon
r_for
c_loop
(paren
id|ctx
op_assign
l_int|0
suffix:semicolon
id|ctx
OL
id|numctx
suffix:semicolon
id|ctx
op_increment
)paren
(brace
id|add_to_free_ctxlist
c_func
(paren
id|ctx_list_pool
op_plus
id|ctx
)paren
suffix:semicolon
)brace
)brace
DECL|macro|DEBUG_BOOTMEM
mdefine_line|#define DEBUG_BOOTMEM
r_extern
r_int
r_int
id|cmdline_memory_size
suffix:semicolon
DECL|variable|last_valid_pfn
r_int
r_int
id|last_valid_pfn
suffix:semicolon
DECL|function|calc_highpages
r_int
r_int
id|calc_highpages
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|nr
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|start_pfn
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_int
r_int
id|end_pfn
op_assign
(paren
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_plus
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|end_pfn
op_le
id|max_low_pfn
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|start_pfn
OL
id|max_low_pfn
)paren
id|start_pfn
op_assign
id|max_low_pfn
suffix:semicolon
id|nr
op_add_assign
id|end_pfn
op_minus
id|start_pfn
suffix:semicolon
)brace
r_return
id|nr
suffix:semicolon
)brace
DECL|function|calc_max_low_pfn
r_int
r_int
id|calc_max_low_pfn
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|tmp
op_assign
(paren
id|SRMMU_MAXMEM
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_int
r_int
id|curr_pfn
comma
id|last_pfn
suffix:semicolon
id|last_pfn
op_assign
(paren
id|sp_banks
(braket
l_int|0
)braket
dot
id|base_addr
op_plus
id|sp_banks
(braket
l_int|0
)braket
dot
id|num_bytes
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
id|curr_pfn
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|curr_pfn
op_ge
id|tmp
)paren
(brace
r_if
c_cond
(paren
id|last_pfn
OL
id|tmp
)paren
id|tmp
op_assign
id|last_pfn
suffix:semicolon
r_break
suffix:semicolon
)brace
id|last_pfn
op_assign
(paren
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_plus
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|bootmem_init
r_int
r_int
id|__init
id|bootmem_init
c_func
(paren
r_int
r_int
op_star
id|pages_avail
)paren
(brace
r_int
r_int
id|bootmap_size
comma
id|start_pfn
comma
id|max_pfn
suffix:semicolon
r_int
r_int
id|end_of_phys_memory
op_assign
l_int|0UL
suffix:semicolon
r_int
r_int
id|bootmap_pfn
comma
id|bytes_avail
comma
id|size
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifdef DEBUG_BOOTMEM
id|prom_printf
c_func
(paren
l_string|&quot;bootmem_init: Scan sp_banks,  &quot;
)paren
suffix:semicolon
macro_line|#endif
id|bytes_avail
op_assign
l_int|0UL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
id|end_of_phys_memory
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_plus
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
suffix:semicolon
id|bytes_avail
op_add_assign
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
suffix:semicolon
r_if
c_cond
(paren
id|cmdline_memory_size
)paren
(brace
r_if
c_cond
(paren
id|bytes_avail
OG
id|cmdline_memory_size
)paren
(brace
r_int
r_int
id|slack
op_assign
id|bytes_avail
op_minus
id|cmdline_memory_size
suffix:semicolon
id|bytes_avail
op_sub_assign
id|slack
suffix:semicolon
id|end_of_phys_memory
op_sub_assign
id|slack
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_sub_assign
id|slack
suffix:semicolon
r_if
c_cond
(paren
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_eq
l_int|0
)paren
(brace
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_assign
l_int|0xdeadbeef
suffix:semicolon
)brace
r_else
(brace
id|sp_banks
(braket
id|i
op_plus
l_int|1
)braket
dot
id|num_bytes
op_assign
l_int|0
suffix:semicolon
id|sp_banks
(braket
id|i
op_plus
l_int|1
)braket
dot
id|base_addr
op_assign
l_int|0xdeadbeef
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Start with page aligned address of last symbol in kernel&n;&t; * image.  &n;&t; */
id|start_pfn
op_assign
(paren
r_int
r_int
)paren
id|__pa
c_func
(paren
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|_end
)paren
)paren
suffix:semicolon
multiline_comment|/* Adjust up to the physical address where the kernel begins. */
id|start_pfn
op_add_assign
id|phys_base
suffix:semicolon
multiline_comment|/* Now shift down to get the real physical page frame number. */
id|start_pfn
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|bootmap_pfn
op_assign
id|start_pfn
suffix:semicolon
id|max_pfn
op_assign
id|end_of_phys_memory
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|max_low_pfn
op_assign
id|max_pfn
suffix:semicolon
id|highstart_pfn
op_assign
id|highend_pfn
op_assign
id|max_pfn
suffix:semicolon
r_if
c_cond
(paren
id|max_low_pfn
OG
(paren
id|SRMMU_MAXMEM
op_rshift
id|PAGE_SHIFT
)paren
)paren
(brace
id|highstart_pfn
op_assign
(paren
id|SRMMU_MAXMEM
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|max_low_pfn
op_assign
id|calc_max_low_pfn
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%ldMB HIGHMEM available.&bslash;n&quot;
comma
id|calc_highpages
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* Now have to check initial ramdisk, so that bootmap does not overwrite it */
r_if
c_cond
(paren
id|sparc_ramdisk_image
)paren
(brace
r_if
c_cond
(paren
id|sparc_ramdisk_image
op_ge
(paren
r_int
r_int
)paren
op_amp
id|_end
op_minus
l_int|2
op_star
id|PAGE_SIZE
)paren
id|sparc_ramdisk_image
op_sub_assign
id|KERNBASE
suffix:semicolon
id|initrd_start
op_assign
id|sparc_ramdisk_image
op_plus
id|phys_base
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|sparc_ramdisk_size
suffix:semicolon
r_if
c_cond
(paren
id|initrd_end
OG
id|end_of_phys_memory
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%016lx &gt; 0x%016lx)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|initrd_end
comma
id|end_of_phys_memory
)paren
suffix:semicolon
id|initrd_start
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|initrd_start
)paren
(brace
r_if
c_cond
(paren
id|initrd_start
op_ge
(paren
id|start_pfn
op_lshift
id|PAGE_SHIFT
)paren
op_logical_and
id|initrd_start
OL
(paren
id|start_pfn
op_lshift
id|PAGE_SHIFT
)paren
op_plus
l_int|2
op_star
id|PAGE_SIZE
)paren
id|bootmap_pfn
op_assign
id|PAGE_ALIGN
(paren
id|initrd_end
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
)brace
macro_line|#endif&t;
multiline_comment|/* Initialize the boot-time allocator. */
macro_line|#ifdef DEBUG_BOOTMEM
id|prom_printf
c_func
(paren
l_string|&quot;init_bootmem(spfn[%lx],bpfn[%lx],mlpfn[%lx])&bslash;n&quot;
comma
id|start_pfn
comma
id|bootmap_pfn
comma
id|max_low_pfn
)paren
suffix:semicolon
macro_line|#endif
id|bootmap_size
op_assign
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|bootmap_pfn
comma
id|phys_base
op_rshift
id|PAGE_SHIFT
comma
id|max_low_pfn
)paren
suffix:semicolon
multiline_comment|/* Now register the available physical memory with the&n;&t; * allocator.&n;&t; */
op_star
id|pages_avail
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|curr_pfn
comma
id|last_pfn
suffix:semicolon
id|curr_pfn
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|curr_pfn
op_ge
id|max_low_pfn
)paren
r_break
suffix:semicolon
id|last_pfn
op_assign
(paren
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_plus
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|last_pfn
OG
id|max_low_pfn
)paren
id|last_pfn
op_assign
id|max_low_pfn
suffix:semicolon
multiline_comment|/*&n;&t;&t; * .. finally, did all the rounding and playing&n;&t;&t; * around just make the area go away?&n;&t;&t; */
r_if
c_cond
(paren
id|last_pfn
op_le
id|curr_pfn
)paren
r_continue
suffix:semicolon
id|size
op_assign
(paren
id|last_pfn
op_minus
id|curr_pfn
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
op_star
id|pages_avail
op_add_assign
id|last_pfn
op_minus
id|curr_pfn
suffix:semicolon
macro_line|#ifdef DEBUG_BOOTMEM
id|prom_printf
c_func
(paren
l_string|&quot;free_bootmem: base[%lx] size[%lx]&bslash;n&quot;
comma
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
id|free_bootmem
c_func
(paren
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
comma
id|size
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_start
)paren
(brace
id|size
op_assign
id|initrd_end
op_minus
id|initrd_start
suffix:semicolon
macro_line|#ifdef DEBUG_BOOTMEM
id|prom_printf
c_func
(paren
l_string|&quot;reserve_bootmem: base[%lx] size[%lx]&bslash;n&quot;
comma
id|initrd_start
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Reserve the initrd image area. */
id|reserve_bootmem
c_func
(paren
id|initrd_start
comma
id|size
)paren
suffix:semicolon
op_star
id|pages_avail
op_sub_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|initrd_start
op_add_assign
id|PAGE_OFFSET
suffix:semicolon
id|initrd_end
op_add_assign
id|PAGE_OFFSET
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Reserve the kernel text/data/bss. */
id|size
op_assign
(paren
id|start_pfn
op_lshift
id|PAGE_SHIFT
)paren
op_minus
id|phys_base
suffix:semicolon
macro_line|#ifdef DEBUG_BOOTMEM
id|prom_printf
c_func
(paren
l_string|&quot;reserve_bootmem: base[%lx] size[%lx]&bslash;n&quot;
comma
id|phys_base
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
id|reserve_bootmem
c_func
(paren
id|phys_base
comma
id|size
)paren
suffix:semicolon
op_star
id|pages_avail
op_sub_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* Reserve the bootmem map.   We do not account for it&n;&t; * in pages_avail because we will release that memory&n;&t; * in free_all_bootmem.&n;&t; */
id|size
op_assign
id|bootmap_size
suffix:semicolon
macro_line|#ifdef DEBUG_BOOTMEM
id|prom_printf
c_func
(paren
l_string|&quot;reserve_bootmem: base[%lx] size[%lx]&bslash;n&quot;
comma
(paren
id|bootmap_pfn
op_lshift
id|PAGE_SHIFT
)paren
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
id|reserve_bootmem
c_func
(paren
(paren
id|bootmap_pfn
op_lshift
id|PAGE_SHIFT
)paren
comma
id|size
)paren
suffix:semicolon
op_star
id|pages_avail
op_sub_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_return
id|max_pfn
suffix:semicolon
)brace
multiline_comment|/*&n; * check_pgt_cache&n; *&n; * This is called at the end of unmapping of VMA (zap_page_range),&n; * to rescan the page cache for architecture specific things,&n; * presumably something like sun4/sun4c PMEGs. Most architectures&n; * define check_pgt_cache empty.&n; *&n; * We simply copy the 2.4 implementation for now.&n; */
DECL|variable|pgt_cache_water
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
DECL|function|check_pgt_cache
r_void
id|check_pgt_cache
c_func
(paren
r_void
)paren
(brace
id|do_check_pgt_cache
c_func
(paren
id|pgt_cache_water
(braket
l_int|0
)braket
comma
id|pgt_cache_water
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * paging_init() sets up the page tables: We call the MMU specific&n; * init routine based upon the Sun model type on the Sparc.&n; *&n; */
r_extern
r_void
id|sun4c_paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|srmmu_paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|device_scan
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
r_switch
c_cond
(paren
id|sparc_cpu_model
)paren
(brace
r_case
id|sun4c
suffix:colon
r_case
id|sun4e
suffix:colon
r_case
id|sun4
suffix:colon
id|sun4c_paging_init
c_func
(paren
)paren
suffix:semicolon
id|sparc_unmapped_base
op_assign
l_int|0xe0000000
suffix:semicolon
id|BTFIXUPSET_SETHI
c_func
(paren
id|sparc_unmapped_base
comma
l_int|0xe0000000
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4m
suffix:colon
r_case
id|sun4d
suffix:colon
id|srmmu_paging_init
c_func
(paren
)paren
suffix:semicolon
id|sparc_unmapped_base
op_assign
l_int|0x50000000
suffix:semicolon
id|BTFIXUPSET_SETHI
c_func
(paren
id|sparc_unmapped_base
comma
l_int|0x50000000
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot;paging_init: Cannot init paging on this Sparc&bslash;n&quot;
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;paging_init: sparc_cpu_model = %d&bslash;n&quot;
comma
id|sparc_cpu_model
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;paging_init: Halting...&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Initialize the protection map with non-constant, MMU dependent values. */
id|protection_map
(braket
l_int|0
)braket
op_assign
id|PAGE_NONE
suffix:semicolon
id|protection_map
(braket
l_int|1
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|2
)braket
op_assign
id|PAGE_COPY
suffix:semicolon
id|protection_map
(braket
l_int|3
)braket
op_assign
id|PAGE_COPY
suffix:semicolon
id|protection_map
(braket
l_int|4
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|5
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|6
)braket
op_assign
id|PAGE_COPY
suffix:semicolon
id|protection_map
(braket
l_int|7
)braket
op_assign
id|PAGE_COPY
suffix:semicolon
id|protection_map
(braket
l_int|8
)braket
op_assign
id|PAGE_NONE
suffix:semicolon
id|protection_map
(braket
l_int|9
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|10
)braket
op_assign
id|PAGE_SHARED
suffix:semicolon
id|protection_map
(braket
l_int|11
)braket
op_assign
id|PAGE_SHARED
suffix:semicolon
id|protection_map
(braket
l_int|12
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|13
)braket
op_assign
id|PAGE_READONLY
suffix:semicolon
id|protection_map
(braket
l_int|14
)braket
op_assign
id|PAGE_SHARED
suffix:semicolon
id|protection_map
(braket
l_int|15
)braket
op_assign
id|PAGE_SHARED
suffix:semicolon
id|btfixup
c_func
(paren
)paren
suffix:semicolon
id|device_scan
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|sparc_aliases
r_struct
id|cache_palias
op_star
id|sparc_aliases
suffix:semicolon
DECL|function|taint_real_pages
r_static
r_void
id|__init
id|taint_real_pages
c_func
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
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|start
comma
id|end
suffix:semicolon
id|start
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|set_bit
(paren
id|start
op_rshift
l_int|20
comma
id|sparc_valid_addr_bitmap
)paren
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
)brace
DECL|function|map_high_region
r_void
id|map_high_region
c_func
(paren
r_int
r_int
id|start_pfn
comma
r_int
r_int
id|end_pfn
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
macro_line|#ifdef DEBUG_HIGHMEM
id|printk
c_func
(paren
l_string|&quot;mapping high region %08lx - %08lx&bslash;n&quot;
comma
id|start_pfn
comma
id|end_pfn
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|tmp
op_assign
id|start_pfn
suffix:semicolon
id|tmp
OL
id|end_pfn
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
id|atomic_set
c_func
(paren
op_amp
id|page-&gt;count
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
id|codepages
op_assign
l_int|0
suffix:semicolon
r_int
id|datapages
op_assign
l_int|0
suffix:semicolon
r_int
id|initpages
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|highmem_start_page
op_assign
id|mem_map
op_plus
id|highstart_pfn
suffix:semicolon
multiline_comment|/* Saves us work later. */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|empty_zero_page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|i
op_assign
id|last_valid_pfn
op_rshift
(paren
(paren
l_int|20
op_minus
id|PAGE_SHIFT
)paren
op_plus
l_int|5
)paren
suffix:semicolon
id|i
op_add_assign
l_int|1
suffix:semicolon
id|sparc_valid_addr_bitmap
op_assign
(paren
r_int
r_int
op_star
)paren
id|__alloc_bootmem
c_func
(paren
id|i
op_lshift
l_int|2
comma
id|SMP_CACHE_BYTES
comma
l_int|0UL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sparc_valid_addr_bitmap
op_eq
l_int|NULL
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;mem_init: Cannot alloc valid_addr_bitmap.&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sparc_valid_addr_bitmap
comma
l_int|0
comma
id|i
op_lshift
l_int|2
)paren
suffix:semicolon
id|taint_real_pages
c_func
(paren
)paren
suffix:semicolon
id|max_mapnr
op_assign
id|last_valid_pfn
op_minus
(paren
id|phys_base
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|high_memory
op_assign
id|__va
c_func
(paren
id|max_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_BOOTMEM
id|prom_printf
c_func
(paren
l_string|&quot;mem_init: Calling free_all_bootmem().&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|num_physpages
op_assign
id|totalram_pages
op_assign
id|free_all_bootmem
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|start_pfn
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_int
r_int
id|end_pfn
op_assign
(paren
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_plus
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|end_pfn
op_le
id|highstart_pfn
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|start_pfn
OL
id|highstart_pfn
)paren
id|start_pfn
op_assign
id|highstart_pfn
suffix:semicolon
id|map_high_region
c_func
(paren
id|start_pfn
comma
id|end_pfn
)paren
suffix:semicolon
)brace
id|totalram_pages
op_add_assign
id|totalhigh_pages
suffix:semicolon
id|codepages
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
op_amp
id|etext
)paren
op_minus
(paren
(paren
r_int
r_int
)paren
op_amp
id|_start
)paren
)paren
suffix:semicolon
id|codepages
op_assign
id|PAGE_ALIGN
c_func
(paren
id|codepages
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|datapages
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
op_amp
id|edata
)paren
op_minus
(paren
(paren
r_int
r_int
)paren
op_amp
id|etext
)paren
)paren
suffix:semicolon
id|datapages
op_assign
id|PAGE_ALIGN
c_func
(paren
id|datapages
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|initpages
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
op_amp
id|__init_end
)paren
op_minus
(paren
(paren
r_int
r_int
)paren
op_amp
id|__init_begin
)paren
)paren
suffix:semicolon
id|initpages
op_assign
id|PAGE_ALIGN
c_func
(paren
id|initpages
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Memory: %dk available (%dk kernel code, %dk data, %dk init, %ldk highmem) [%08lx,%08lx]&bslash;n&quot;
comma
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
id|codepages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|datapages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|initpages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|totalhigh_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
(paren
r_int
r_int
)paren
id|PAGE_OFFSET
comma
(paren
id|last_valid_pfn
op_lshift
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
)brace
DECL|function|free_initmem
r_void
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
r_int
r_int
id|page
suffix:semicolon
r_struct
id|page
op_star
id|p
suffix:semicolon
id|page
op_assign
id|addr
op_plus
id|phys_base
suffix:semicolon
id|p
op_assign
id|virt_to_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|ClearPageReserved
c_func
(paren
id|p
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|p
comma
l_int|1
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|p
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
id|num_physpages
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
r_struct
id|page
op_star
id|p
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
id|p
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|p
comma
l_int|1
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|p
)paren
suffix:semicolon
id|num_physpages
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|flush_page_to_ram
r_void
id|flush_page_to_ram
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
r_int
id|vaddr
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
id|vaddr
)paren
id|__flush_page_to_ram
c_func
(paren
id|vaddr
)paren
suffix:semicolon
)brace
eof
