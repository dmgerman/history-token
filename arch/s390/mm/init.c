multiline_comment|/*&n; *  arch/s390/mm/init.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com)&n; *&n; *  Derived from &quot;arch/i386/mm/init.c&quot;&n; *    Copyright (C) 1995  Linus Torvalds&n; */
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
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|mmu_gather
comma
id|mmu_gathers
)paren
suffix:semicolon
DECL|variable|swapper_pg_dir
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
id|__attribute__
c_func
(paren
(paren
id|__aligned__
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
suffix:semicolon
DECL|variable|empty_zero_page
r_char
id|empty_zero_page
(braket
id|PAGE_SIZE
)braket
id|__attribute__
c_func
(paren
(paren
id|__aligned__
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
suffix:semicolon
DECL|function|diag10
r_void
id|diag10
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr
op_ge
l_int|0x7ff00000
)paren
r_return
suffix:semicolon
macro_line|#ifdef __s390x__
id|asm
r_volatile
(paren
l_string|&quot;   sam31&bslash;n&quot;
l_string|&quot;   diag %0,%0,0x10&bslash;n&quot;
l_string|&quot;0: sam64&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad 0b, 0b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
macro_line|#else
id|asm
r_volatile
(paren
l_string|&quot;   diag %0,%0,0x10&bslash;n&quot;
l_string|&quot;0:&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 0b, 0b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
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
l_string|&quot;Free swap:       %6ldkB&bslash;n&quot;
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
)brace
multiline_comment|/* References to section boundaries */
r_extern
r_int
r_int
id|_text
suffix:semicolon
r_extern
r_int
r_int
id|_etext
suffix:semicolon
r_extern
r_int
r_int
id|_edata
suffix:semicolon
r_extern
r_int
r_int
id|__bss_start
suffix:semicolon
r_extern
r_int
r_int
id|_end
suffix:semicolon
r_extern
r_int
r_int
id|__init_begin
suffix:semicolon
r_extern
r_int
r_int
id|__init_end
suffix:semicolon
multiline_comment|/*&n; * paging_init() sets up the page tables&n; */
macro_line|#ifndef CONFIG_ARCH_S390X
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
(brace
id|pgd_t
op_star
id|pg_dir
suffix:semicolon
id|pte_t
op_star
id|pg_table
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
id|pfn
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pgdir_k
op_assign
(paren
id|__pa
c_func
(paren
id|swapper_pg_dir
)paren
op_amp
id|PAGE_MASK
)paren
op_or
id|_KERNSEG_TABLE
suffix:semicolon
r_static
r_const
r_int
id|ssm_mask
op_assign
l_int|0x04000000L
suffix:semicolon
multiline_comment|/* unmap whole virtual address space */
id|pg_dir
op_assign
id|swapper_pg_dir
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
id|KERNEL_PGD_PTRS
suffix:semicolon
id|i
op_increment
)paren
id|pmd_clear
c_func
(paren
(paren
id|pmd_t
op_star
)paren
id|pg_dir
op_increment
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * map whole physical memory to virtual memory (identity mapping) &n;&t; */
id|pg_dir
op_assign
id|swapper_pg_dir
suffix:semicolon
r_while
c_loop
(paren
id|pfn
OL
id|max_low_pfn
)paren
(brace
multiline_comment|/*&n;                 * pg_table is physical at this point&n;                 */
id|pg_table
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
id|pg_dir-&gt;pgd0
op_assign
(paren
id|_PAGE_TABLE
op_or
id|__pa
c_func
(paren
id|pg_table
)paren
)paren
suffix:semicolon
id|pg_dir-&gt;pgd1
op_assign
(paren
id|_PAGE_TABLE
op_or
(paren
id|__pa
c_func
(paren
id|pg_table
)paren
op_plus
l_int|1024
)paren
)paren
suffix:semicolon
id|pg_dir-&gt;pgd2
op_assign
(paren
id|_PAGE_TABLE
op_or
(paren
id|__pa
c_func
(paren
id|pg_table
)paren
op_plus
l_int|2048
)paren
)paren
suffix:semicolon
id|pg_dir-&gt;pgd3
op_assign
(paren
id|_PAGE_TABLE
op_or
(paren
id|__pa
c_func
(paren
id|pg_table
)paren
op_plus
l_int|3072
)paren
)paren
suffix:semicolon
id|pg_dir
op_increment
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
id|PTRS_PER_PTE
suffix:semicolon
id|tmp
op_increment
comma
id|pg_table
op_increment
)paren
(brace
id|pte
op_assign
id|pfn_pte
c_func
(paren
id|pfn
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pfn
op_ge
id|max_low_pfn
)paren
id|pte_clear
c_func
(paren
op_amp
id|pte
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pg_table
comma
id|pte
)paren
suffix:semicolon
id|pfn
op_increment
suffix:semicolon
)brace
)brace
id|S390_lowcore.kernel_asce
op_assign
id|pgdir_k
suffix:semicolon
multiline_comment|/* enable virtual mapping in kernel mode */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;    LCTL  1,1,%0&bslash;n&quot;
l_string|&quot;    LCTL  7,7,%0&bslash;n&quot;
l_string|&quot;    LCTL  13,13,%0&bslash;n&quot;
l_string|&quot;    SSM   %1&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|pgdir_k
)paren
comma
l_string|&quot;m&quot;
(paren
id|ssm_mask
)paren
)paren
suffix:semicolon
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
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
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|max_low_pfn
suffix:semicolon
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
macro_line|#else /* CONFIG_ARCH_S390X */
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
(brace
id|pgd_t
op_star
id|pg_dir
suffix:semicolon
id|pmd_t
op_star
id|pm_dir
suffix:semicolon
id|pte_t
op_star
id|pt_dir
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
suffix:semicolon
r_int
r_int
id|pfn
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pgdir_k
op_assign
(paren
id|__pa
c_func
(paren
id|swapper_pg_dir
)paren
op_amp
id|PAGE_MASK
)paren
op_or
id|_KERN_REGION_TABLE
suffix:semicolon
r_static
r_const
r_int
id|ssm_mask
op_assign
l_int|0x04000000L
suffix:semicolon
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
id|MAX_DMA_ADDRESS
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|high_pfn
op_assign
id|max_low_pfn
suffix:semicolon
r_if
c_cond
(paren
id|dma_pfn
OG
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
multiline_comment|/*&n;&t; * map whole physical memory to virtual memory (identity mapping) &n;&t; */
id|pg_dir
op_assign
id|swapper_pg_dir
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
id|PTRS_PER_PGD
suffix:semicolon
id|i
op_increment
comma
id|pg_dir
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pfn
op_ge
id|max_low_pfn
)paren
(brace
id|pgd_clear
c_func
(paren
id|pg_dir
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pm_dir
op_assign
(paren
id|pmd_t
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
op_star
l_int|4
)paren
suffix:semicolon
id|pgd_populate
c_func
(paren
op_amp
id|init_mm
comma
id|pg_dir
comma
id|pm_dir
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
id|j
op_increment
comma
id|pm_dir
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pfn
op_ge
id|max_low_pfn
)paren
(brace
id|pmd_clear
c_func
(paren
id|pm_dir
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pt_dir
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
id|pmd_populate_kernel
c_func
(paren
op_amp
id|init_mm
comma
id|pm_dir
comma
id|pt_dir
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|PTRS_PER_PTE
suffix:semicolon
id|k
op_increment
comma
id|pt_dir
op_increment
)paren
(brace
id|pte
op_assign
id|pfn_pte
c_func
(paren
id|pfn
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pfn
op_ge
id|max_low_pfn
)paren
(brace
id|pte_clear
c_func
(paren
op_amp
id|pte
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|set_pte
c_func
(paren
id|pt_dir
comma
id|pte
)paren
suffix:semicolon
id|pfn
op_increment
suffix:semicolon
)brace
)brace
)brace
id|S390_lowcore.kernel_asce
op_assign
id|pgdir_k
suffix:semicolon
multiline_comment|/* enable virtual mapping in kernel mode */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lctlg 1,1,%0&bslash;n&bslash;t&quot;
l_string|&quot;lctlg 7,7,%0&bslash;n&bslash;t&quot;
l_string|&quot;lctlg 13,13,%0&bslash;n&bslash;t&quot;
l_string|&quot;ssm   %1&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|pgdir_k
)paren
comma
l_string|&quot;m&quot;
(paren
id|ssm_mask
)paren
)paren
suffix:semicolon
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ARCH_S390X */
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
id|max_mapnr
op_assign
id|num_physpages
op_assign
id|max_low_pfn
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
id|reservedpages
op_assign
l_int|0
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
l_string|&quot;Memory: %luk/%luk available (%ldk kernel code, %ldk reserved, %ldk data, %ldk init)&bslash;n&quot;
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
l_string|&quot;Freeing unused kernel memory: %ldk freed&bslash;n&quot;
comma
(paren
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
