multiline_comment|/*&n; *  linux/arch/m68k/mm/init.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; *&n; *  Contains common initialization routines, specific init code moved&n; *  to motorola.c and sun3mmu.c&n; */
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
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_ATARI
macro_line|#include &lt;asm/atari_stram.h&gt;
macro_line|#endif
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
multiline_comment|/*&n; * ZERO_PAGE is a special page that is used for zero-initialized&n; * data and COW.&n; */
DECL|variable|empty_zero_page
r_void
op_star
id|empty_zero_page
suffix:semicolon
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
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
comma
id|shared
op_assign
l_int|0
suffix:semicolon
r_int
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
l_string|&quot;%d pages of RAM&bslash;n&quot;
comma
id|total
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d free pages&bslash;n&quot;
comma
id|free
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
r_extern
r_void
id|init_pointer_table
c_func
(paren
r_int
r_int
id|ptable
)paren
suffix:semicolon
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
r_extern
id|pmd_t
op_star
id|zero_pgtable
suffix:semicolon
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
r_int
id|tmp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|max_mapnr
op_assign
id|num_physpages
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|PAGE_OFFSET
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ATARI
r_if
c_cond
(paren
id|MACH_IS_ATARI
)paren
id|atari_stram_mem_init_hook
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* this will put all memory onto the freelists */
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
id|tmp
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|tmp
OL
(paren
r_int
r_int
)paren
id|high_memory
suffix:semicolon
id|tmp
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|tmp
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|tmp
op_ge
(paren
r_int
r_int
)paren
op_amp
id|_text
op_logical_and
id|tmp
OL
(paren
r_int
r_int
)paren
op_amp
id|_etext
)paren
id|codepages
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tmp
op_ge
(paren
r_int
r_int
)paren
op_amp
id|__init_begin
op_logical_and
id|tmp
OL
(paren
r_int
r_int
)paren
op_amp
id|__init_end
)paren
id|initpages
op_increment
suffix:semicolon
r_else
id|datapages
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
macro_line|#ifndef CONFIG_SUN3
multiline_comment|/* insert pointer tables allocated so far into the tablelist */
id|init_pointer_table
c_func
(paren
(paren
r_int
r_int
)paren
id|kernel_pg_dir
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
id|PTRS_PER_PGD
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pgd_present
c_func
(paren
id|kernel_pg_dir
(braket
id|i
)braket
)paren
)paren
id|init_pointer_table
c_func
(paren
id|__pgd_page
c_func
(paren
id|kernel_pg_dir
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* insert also pointer table that we used to unmap the zero page */
r_if
c_cond
(paren
id|zero_pgtable
)paren
id|init_pointer_table
c_func
(paren
(paren
r_int
r_int
)paren
id|zero_pgtable
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;Memory: %luk/%luk available (%dk kernel code, %dk data, %dk init)&bslash;n&quot;
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
r_int
id|pages
op_assign
l_int|0
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
id|pages
op_increment
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;Freeing initrd memory: %dk freed&bslash;n&quot;
comma
id|pages
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
