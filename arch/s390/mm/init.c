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
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
DECL|variable|totalram_pages
r_static
r_int
r_int
id|totalram_pages
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
DECL|function|test_access
r_static
r_int
id|test_access
c_func
(paren
r_int
r_int
id|loc
)paren
(brace
r_static
r_const
r_int
id|ssm_mask
op_assign
l_int|0x07000000L
suffix:semicolon
r_int
id|rc
comma
id|i
suffix:semicolon
id|rc
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
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;    slr   %0,%0&bslash;n&quot;
l_string|&quot;    ssm   %1&bslash;n&quot;
l_string|&quot;    tprot 0(%2),0&bslash;n&quot;
l_string|&quot;0:  jne   1f&bslash;n&quot;
l_string|&quot;    lhi   %0,1&bslash;n&quot;
l_string|&quot;1:  ssm   %3&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long  0b,1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;+&amp;d&quot;
(paren
id|rc
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;a&quot;
(paren
id|loc
)paren
comma
l_string|&quot;m&quot;
(paren
id|ssm_mask
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|loc
op_add_assign
l_int|0x100000
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
DECL|function|do_check_pgt_cache
r_int
id|do_check_pgt_cache
c_func
(paren
r_int
id|low
comma
r_int
id|high
)paren
(brace
r_int
id|freed
op_assign
l_int|0
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
(brace
id|free_pgd_slow
c_func
(paren
id|get_pgd_fast
c_func
(paren
)paren
)paren
comma
id|freed
op_add_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmd_quicklist
)paren
(brace
id|pmd_free_slow
c_func
(paren
id|pmd_alloc_one_fast
c_func
(paren
l_int|NULL
comma
l_int|0
)paren
)paren
comma
id|freed
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pte_quicklist
)paren
(brace
id|pte_free_slow
c_func
(paren
id|pte_alloc_one_fast
c_func
(paren
l_int|NULL
comma
l_int|0
)paren
)paren
comma
id|freed
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|pgtable_cache_size
OG
id|low
)paren
(brace
suffix:semicolon
)brace
)brace
r_return
id|freed
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
id|atomic_read
c_func
(paren
op_amp
id|mem_map
(braket
id|i
)braket
dot
id|count
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
multiline_comment|/*&n; * paging_init() sets up the page tables - note that the first 4MB are&n; * already mapped by head.S.&n; * paging_init will erase this initial mapping&n; */
DECL|variable|last_valid_pfn
r_int
r_int
id|last_valid_pfn
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
id|address
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
r_int
r_int
id|end_mem
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|max_low_pfn
op_star
id|PAGE_SIZE
)paren
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
id|address
OL
id|end_mem
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
id|mk_pte_phys
c_func
(paren
id|address
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|address
op_ge
id|end_mem
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
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
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
multiline_comment|/* mark usable pages in the mem_map[] and count reserved pages */
id|reservedpages
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|tmp
op_logical_and
(paren
id|tmp
op_amp
l_int|0x3ff
)paren
op_eq
l_int|0
op_logical_and
id|test_access
c_func
(paren
id|tmp
op_star
id|PAGE_SIZE
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;4M Segment %lX not available&bslash;n&quot;
comma
id|tmp
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
r_do
(brace
id|set_bit
c_func
(paren
id|PG_reserved
comma
op_amp
id|mem_map
(braket
id|tmp
)braket
dot
id|flags
)paren
suffix:semicolon
id|reservedpages
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tmp
OL
id|max_low_pfn
op_logical_and
(paren
id|tmp
op_amp
l_int|0x3ff
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
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
id|tmp
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|tmp
OL
id|max_low_pfn
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
DECL|function|si_meminfo
r_void
id|si_meminfo
c_func
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
)brace
eof
