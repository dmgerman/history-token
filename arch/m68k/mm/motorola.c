multiline_comment|/*&n; * linux/arch/m68k/motorola.c&n; *&n; * Routines specific to the Motorola MMU, originally from:&n; * linux/arch/m68k/init.c &n; * which are Copyright (C) 1995 Hamish Macdonald&n; * &n; * Moved 8/20/1999 Sam Creasey&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#ifdef CONFIG_ATARI
macro_line|#include &lt;asm/atari_stram.h&gt;
macro_line|#endif
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifndef mm_cachebits
multiline_comment|/*&n; * Bits to add to page descriptors for &quot;normal&quot; caching mode.&n; * For 68020/030 this is 0.&n; * For 68040, this is _PAGE_CACHE040 (cachable, copyback)&n; */
DECL|variable|mm_cachebits
r_int
r_int
id|mm_cachebits
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
DECL|function|kernel_page_table
r_static
id|pte_t
op_star
id|__init
id|kernel_page_table
c_func
(paren
r_void
)paren
(brace
id|pte_t
op_star
id|ptablep
suffix:semicolon
id|ptablep
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
id|clear_page
c_func
(paren
id|ptablep
)paren
suffix:semicolon
id|__flush_page_to_ram
c_func
(paren
(paren
r_int
r_int
)paren
id|ptablep
)paren
suffix:semicolon
id|flush_tlb_kernel_page
c_func
(paren
(paren
r_int
r_int
)paren
id|ptablep
)paren
suffix:semicolon
id|nocache_page
(paren
(paren
r_int
r_int
)paren
id|ptablep
)paren
suffix:semicolon
r_return
id|ptablep
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
id|pmd_t
op_star
id|last_pgtable
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|__initdata
id|pmd_t
op_star
id|zero_pgtable
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
DECL|function|kernel_ptr_table
r_static
id|pmd_t
op_star
id|__init
id|kernel_ptr_table
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|last_pgtable
)paren
(brace
r_int
r_int
id|pmd
comma
id|last
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Find the last ptr table that was used in head.S and&n;&t;&t; * reuse the remaining space in that page for further&n;&t;&t; * ptr tables.&n;&t;&t; */
id|last
op_assign
(paren
r_int
r_int
)paren
id|kernel_pg_dir
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
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pgd_present
c_func
(paren
id|kernel_pg_dir
(braket
id|i
)braket
)paren
)paren
r_continue
suffix:semicolon
id|pmd
op_assign
id|__pgd_page
c_func
(paren
id|kernel_pg_dir
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
OG
id|last
)paren
id|last
op_assign
id|pmd
suffix:semicolon
)brace
id|last_pgtable
op_assign
(paren
id|pmd_t
op_star
)paren
id|last
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;kernel_ptr_init: %p&bslash;n&quot;
comma
id|last_pgtable
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
(paren
id|last_pgtable
op_plus
id|PTRS_PER_PMD
)paren
op_amp
op_complement
id|PAGE_MASK
)paren
op_eq
l_int|0
)paren
(brace
id|last_pgtable
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
id|clear_page
c_func
(paren
id|last_pgtable
)paren
suffix:semicolon
id|__flush_page_to_ram
c_func
(paren
(paren
r_int
r_int
)paren
id|last_pgtable
)paren
suffix:semicolon
id|flush_tlb_kernel_page
c_func
(paren
(paren
r_int
r_int
)paren
id|last_pgtable
)paren
suffix:semicolon
id|nocache_page
c_func
(paren
(paren
r_int
r_int
)paren
id|last_pgtable
)paren
suffix:semicolon
)brace
r_else
id|last_pgtable
op_add_assign
id|PTRS_PER_PMD
suffix:semicolon
r_return
id|last_pgtable
suffix:semicolon
)brace
r_static
r_int
r_int
id|__init
DECL|function|map_chunk
id|map_chunk
(paren
r_int
r_int
id|addr
comma
r_int
id|size
)paren
(brace
DECL|macro|PTRTREESIZE
mdefine_line|#define PTRTREESIZE (256*1024)
DECL|macro|ROOTTREESIZE
mdefine_line|#define ROOTTREESIZE (32*1024*1024)
r_static
r_int
r_int
id|virtaddr
op_assign
id|PAGE_OFFSET
suffix:semicolon
r_int
r_int
id|physaddr
suffix:semicolon
id|pgd_t
op_star
id|pgd_dir
suffix:semicolon
id|pmd_t
op_star
id|pmd_dir
suffix:semicolon
id|pte_t
op_star
id|pte_dir
suffix:semicolon
id|physaddr
op_assign
(paren
id|addr
op_or
id|m68k_supervisor_cachemode
op_or
id|_PAGE_PRESENT
op_or
id|_PAGE_ACCESSED
op_or
id|_PAGE_DIRTY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
id|physaddr
op_or_assign
id|_PAGE_GLOBAL040
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
op_logical_neg
(paren
id|virtaddr
op_amp
(paren
id|PTRTREESIZE
op_minus
l_int|1
)paren
)paren
)paren
id|printk
(paren
l_string|&quot;&bslash;npa=%#lx va=%#lx &quot;
comma
id|physaddr
op_amp
id|PAGE_MASK
comma
id|virtaddr
)paren
suffix:semicolon
macro_line|#endif
id|pgd_dir
op_assign
id|pgd_offset_k
c_func
(paren
id|virtaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|virtaddr
op_logical_and
id|CPU_IS_020_OR_030
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|virtaddr
op_amp
(paren
id|ROOTTREESIZE
op_minus
l_int|1
)paren
)paren
op_logical_and
id|size
op_ge
id|ROOTTREESIZE
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;[very early term]&quot;
)paren
suffix:semicolon
macro_line|#endif
id|pgd_val
c_func
(paren
op_star
id|pgd_dir
)paren
op_assign
id|physaddr
suffix:semicolon
id|size
op_sub_assign
id|ROOTTREESIZE
suffix:semicolon
id|virtaddr
op_add_assign
id|ROOTTREESIZE
suffix:semicolon
id|physaddr
op_add_assign
id|ROOTTREESIZE
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|pgd_present
c_func
(paren
op_star
id|pgd_dir
)paren
)paren
(brace
id|pmd_dir
op_assign
id|kernel_ptr_table
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;[new pointer %p]&quot;
comma
id|pmd_dir
)paren
suffix:semicolon
macro_line|#endif
id|pgd_set
c_func
(paren
id|pgd_dir
comma
id|pmd_dir
)paren
suffix:semicolon
)brace
r_else
id|pmd_dir
op_assign
id|pmd_offset
c_func
(paren
id|pgd_dir
comma
id|virtaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CPU_IS_020_OR_030
)paren
(brace
r_if
c_cond
(paren
id|virtaddr
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;[early term]&quot;
)paren
suffix:semicolon
macro_line|#endif
id|pmd_dir-&gt;pmd
(braket
(paren
id|virtaddr
op_div
id|PTRTREESIZE
)paren
op_amp
l_int|15
)braket
op_assign
id|physaddr
suffix:semicolon
id|physaddr
op_add_assign
id|PTRTREESIZE
suffix:semicolon
)brace
r_else
(brace
r_int
id|i
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;[zero map]&quot;
)paren
suffix:semicolon
macro_line|#endif
id|zero_pgtable
op_assign
id|kernel_ptr_table
c_func
(paren
)paren
suffix:semicolon
id|pte_dir
op_assign
(paren
id|pte_t
op_star
)paren
id|zero_pgtable
suffix:semicolon
id|pmd_dir-&gt;pmd
(braket
l_int|0
)braket
op_assign
id|virt_to_phys
c_func
(paren
id|pte_dir
)paren
op_or
id|_PAGE_TABLE
op_or
id|_PAGE_ACCESSED
suffix:semicolon
id|pte_val
c_func
(paren
op_star
id|pte_dir
op_increment
)paren
op_assign
l_int|0
suffix:semicolon
id|physaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|64
suffix:semicolon
id|physaddr
op_add_assign
id|PAGE_SIZE
comma
id|i
op_increment
)paren
id|pte_val
c_func
(paren
op_star
id|pte_dir
op_increment
)paren
op_assign
id|physaddr
suffix:semicolon
)brace
id|size
op_sub_assign
id|PTRTREESIZE
suffix:semicolon
id|virtaddr
op_add_assign
id|PTRTREESIZE
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|pmd_present
c_func
(paren
op_star
id|pmd_dir
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;[new table]&quot;
)paren
suffix:semicolon
macro_line|#endif
id|pte_dir
op_assign
id|kernel_page_table
c_func
(paren
)paren
suffix:semicolon
id|pmd_set
c_func
(paren
id|pmd_dir
comma
id|pte_dir
)paren
suffix:semicolon
)brace
id|pte_dir
op_assign
id|pte_offset
c_func
(paren
id|pmd_dir
comma
id|virtaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|virtaddr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|pte_dir
)paren
)paren
id|pte_val
c_func
(paren
op_star
id|pte_dir
)paren
op_assign
id|physaddr
suffix:semicolon
)brace
r_else
id|pte_val
c_func
(paren
op_star
id|pte_dir
)paren
op_assign
l_int|0
suffix:semicolon
id|size
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
id|virtaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|physaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|virtaddr
suffix:semicolon
)brace
r_extern
r_int
r_int
id|empty_bad_page_table
suffix:semicolon
r_extern
r_int
r_int
id|empty_bad_page
suffix:semicolon
multiline_comment|/*&n; * paging_init() continues the virtual memory environment setup which&n; * was begun by the code in arch/head.S.&n; */
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
id|chunk
suffix:semicolon
r_int
r_int
id|mem_avail
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|zones_size
(braket
l_int|3
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
macro_line|#ifdef DEBUG
(brace
r_extern
r_int
r_int
id|availmem
suffix:semicolon
id|printk
(paren
l_string|&quot;start of paging_init (%p, %lx, %lx, %lx)&bslash;n&quot;
comma
id|kernel_pg_dir
comma
id|availmem
comma
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Fix the cache mode in the page descriptors for the 680[46]0.  */
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
r_int
id|i
suffix:semicolon
macro_line|#ifndef mm_cachebits
id|mm_cachebits
op_assign
id|_PAGE_CACHE040
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|pgprot_val
c_func
(paren
id|protection_map
(braket
id|i
)braket
)paren
op_or_assign
id|_PAGE_CACHE040
suffix:semicolon
)brace
multiline_comment|/* Fix the PAGE_NONE value. */
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
multiline_comment|/* On the 680[46]0 we can use the _PAGE_SUPER bit.  */
id|pgprot_val
c_func
(paren
id|protection_map
(braket
l_int|0
)braket
)paren
op_or_assign
id|_PAGE_SUPER
suffix:semicolon
id|pgprot_val
c_func
(paren
id|protection_map
(braket
id|VM_SHARED
)braket
)paren
op_or_assign
id|_PAGE_SUPER
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Otherwise we must fake it. */
id|pgprot_val
c_func
(paren
id|protection_map
(braket
l_int|0
)braket
)paren
op_and_assign
op_complement
id|_PAGE_PRESENT
suffix:semicolon
id|pgprot_val
c_func
(paren
id|protection_map
(braket
l_int|0
)braket
)paren
op_or_assign
id|_PAGE_FAKE_SUPER
suffix:semicolon
id|pgprot_val
c_func
(paren
id|protection_map
(braket
id|VM_SHARED
)braket
)paren
op_and_assign
op_complement
id|_PAGE_PRESENT
suffix:semicolon
id|pgprot_val
c_func
(paren
id|protection_map
(braket
id|VM_SHARED
)braket
)paren
op_or_assign
id|_PAGE_FAKE_SUPER
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Map the physical memory available into the kernel virtual&n;&t; * address space.  It may allocate some memory for page&n;&t; * tables and thus modify availmem.&n;&t; */
r_for
c_loop
(paren
id|chunk
op_assign
l_int|0
suffix:semicolon
id|chunk
OL
id|m68k_num_memory
suffix:semicolon
id|chunk
op_increment
)paren
(brace
id|mem_avail
op_assign
id|map_chunk
(paren
id|m68k_memory
(braket
id|chunk
)braket
dot
id|addr
comma
id|m68k_memory
(braket
id|chunk
)braket
dot
id|size
)paren
suffix:semicolon
)brace
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;memory available is %ldKB&bslash;n&quot;
comma
id|mem_avail
op_rshift
l_int|10
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;start_mem is %#lx&bslash;nvirtual_end is %#lx&bslash;n&quot;
comma
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * initialize the bad page table and bad page to point&n;&t; * to a couple of allocated pages&n;&t; */
id|empty_bad_page_table
op_assign
(paren
r_int
r_int
)paren
id|alloc_bootmem_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|empty_bad_page
op_assign
(paren
r_int
r_int
)paren
id|alloc_bootmem_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|empty_zero_page
op_assign
(paren
r_int
r_int
)paren
id|alloc_bootmem_pages
c_func
(paren
id|PAGE_SIZE
)paren
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
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up SFC/DFC registers (user data space)&n;&t; */
id|set_fs
(paren
id|USER_DS
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;before free_area_init&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|zones_size
(braket
l_int|0
)braket
op_assign
(paren
id|mach_max_dma_address
OL
(paren
r_int
r_int
)paren
id|high_memory
ques
c_cond
id|mach_max_dma_address
suffix:colon
(paren
r_int
r_int
)paren
id|high_memory
)paren
suffix:semicolon
id|zones_size
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|zones_size
(braket
l_int|0
)braket
suffix:semicolon
id|zones_size
(braket
l_int|0
)braket
op_assign
(paren
id|zones_size
(braket
l_int|0
)braket
op_minus
id|PAGE_OFFSET
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|zones_size
(braket
l_int|1
)braket
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|free_area_init
c_func
(paren
id|zones_size
)paren
suffix:semicolon
)brace
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
r_extern
r_int
r_int
id|totalram_pages
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
id|virt_to_page
c_func
(paren
id|addr
)paren
op_member_access_from_pointer
id|flags
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|PG_reserved
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
)brace
eof
