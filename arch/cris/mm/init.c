multiline_comment|/*&n; *  linux/arch/cris/mm/init.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Copyright (C) 2000,2001  Axis Communications AB&n; *&n; *  Authors:  Bjorn Wesen (bjornw@axis.com)&n; *&n; *  $Log: init.c,v $&n; *  Revision 1.11  2004/05/28 09:28:56  starvik&n; *  Calculation of loops_per_usec moved because initalization order has changed&n; *  in Linux 2.6.&n; *&n; *  Revision 1.10  2004/05/14 07:58:05  starvik&n; *  Merge of changes from 2.4&n; *&n; *  Revision 1.9  2003/07/04 08:27:54  starvik&n; *  Merge of Linux 2.5.74&n; *&n; *  Revision 1.8  2003/04/09 05:20:48  starvik&n; *  Merge of Linux 2.5.67&n; *&n; *  Revision 1.7  2003/01/22 06:48:38  starvik&n; *  Fixed warnings issued by GCC 3.2.1&n; *&n; *  Revision 1.6  2002/12/11 14:44:48  starvik&n; *  Extracted v10 (ETRAX 100LX) specific stuff to arch/cris/arch-v10/mm&n; *&n; *  Revision 1.5  2002/11/18 07:37:37  starvik&n; *  Added cache bug workaround (from Linux 2.4)&n; *&n; *  Revision 1.4  2002/11/13 15:40:24  starvik&n; *  Removed the page table cache stuff (as done in other archs)&n; *&n; *  Revision 1.3  2002/11/05 06:45:13  starvik&n; *  Merge of Linux 2.5.45&n; *&n; *  Revision 1.2  2001/12/18 13:35:22  bjornw&n; *  Applied the 2.4.13-&gt;2.4.16 CRIS patch to 2.5.1 (is a copy of 2.4.15).&n; *&n; *  Revision 1.31  2001/11/13 16:22:00  bjornw&n; *  Skip calculating totalram and sharedram in si_meminfo&n; *&n; *  Revision 1.30  2001/11/12 19:02:10  pkj&n; *  Fixed compiler warnings.&n; *&n; *  Revision 1.29  2001/07/25 16:09:50  bjornw&n; *  val-&gt;sharedram will stay 0&n; *&n; *  Revision 1.28  2001/06/28 16:30:17  bjornw&n; *  Oops. This needs to wait until 2.4.6 is merged&n; *&n; *  Revision 1.27  2001/06/28 14:04:07  bjornw&n; *  Fill in sharedram&n; *&n; *  Revision 1.26  2001/06/18 06:36:02  hp&n; *  Enable free_initmem of __init-type pages&n; *&n; *  Revision 1.25  2001/06/13 00:02:23  bjornw&n; *  Use a separate variable to store the current pgd to avoid races in schedule&n; *&n; *  Revision 1.24  2001/05/15 00:52:20  hp&n; *  Only map segment 0xa as seg if CONFIG_JULIETTE&n; *&n; *  Revision 1.23  2001/04/04 14:35:40  bjornw&n; *  * Removed get_pte_slow and friends (2.4.3 change)&n; *  * Removed bad_pmd handling (2.4.3 change)&n; *&n; *  Revision 1.22  2001/04/04 13:38:04  matsfg&n; *  Moved ioremap to a separate function instead&n; *&n; *  Revision 1.21  2001/03/27 09:28:33  bjornw&n; *  ioremap used too early - lets try it in mem_init instead&n; *&n; *  Revision 1.20  2001/03/23 07:39:21  starvik&n; *  Corrected according to review remarks&n; *&n; *  Revision 1.19  2001/03/15 14:25:17  bjornw&n; *  More general shadow registers and ioremaped addresses for external I/O&n; *&n; *  Revision 1.18  2001/02/23 12:46:44  bjornw&n; *  * 0xc was not CSE1; 0x8 is, same as uncached flash, so we move the uncached&n; *    flash during CRIS_LOW_MAP from 0xe to 0x8 so both the flash and the I/O&n; *    is mapped straight over (for !CRIS_LOW_MAP the uncached flash is still 0xe)&n; *&n; *  Revision 1.17  2001/02/22 15:05:21  bjornw&n; *  Map 0x9 straight over during LOW_MAP to allow for memory mapped LEDs&n; *&n; *  Revision 1.16  2001/02/22 15:02:35  bjornw&n; *  Map 0xc straight over during LOW_MAP to allow for memory mapped I/O&n; *&n; *  Revision 1.15  2001/01/10 21:12:10  bjornw&n; *  loops_per_sec -&gt; loops_per_jiffy&n; *&n; *  Revision 1.14  2000/11/22 16:23:20  bjornw&n; *  Initialize totalhigh counters to 0 to make /proc/meminfo look nice.&n; *&n; *  Revision 1.13  2000/11/21 16:37:51  bjornw&n; *  Temporarily disable initmem freeing&n; *&n; *  Revision 1.12  2000/11/21 13:55:07  bjornw&n; *  Use CONFIG_CRIS_LOW_MAP for the low VM map instead of explicit CPU type&n; *&n; *  Revision 1.11  2000/10/06 12:38:22  bjornw&n; *  Cast empty_bad_page correctly (should really be of * type from the start..&n; *&n; *  Revision 1.10  2000/10/04 16:53:57  bjornw&n; *  Fix memory-map due to LX features&n; *&n; *  Revision 1.9  2000/09/13 15:47:49  bjornw&n; *  Wrong count in reserved-pages loop&n; *&n; *  Revision 1.8  2000/09/13 14:35:10  bjornw&n; *  2.4.0-test8 added a new arg to free_area_init_node&n; *&n; *  Revision 1.7  2000/08/17 15:35:55  bjornw&n; *  2.4.0-test6 removed MAP_NR and inserted virt_to_page&n; *&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
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
DECL|variable|empty_zero_page
r_int
r_int
id|empty_zero_page
suffix:semicolon
r_extern
r_char
id|_stext
comma
id|_edata
comma
id|_etext
suffix:semicolon
multiline_comment|/* From linkerscript */
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
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
id|cached
op_assign
l_int|0
comma
id|reserved
op_assign
l_int|0
comma
id|nonshared
op_assign
l_int|0
suffix:semicolon
r_int
id|shared
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
op_eq
l_int|1
)paren
id|nonshared
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
l_string|&quot;%d pages nonshared&bslash;n&quot;
comma
id|nonshared
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
r_void
id|__init
DECL|function|mem_init
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
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem_map
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* max/min_low_pfn was set by setup.c&n;&t; * now we just copy it to some other necessary places...&n;&t; *&n;&t; * high_memory was also set in setup.c&n;&t; */
id|max_mapnr
op_assign
id|num_physpages
op_assign
id|max_low_pfn
op_minus
id|min_low_pfn
suffix:semicolon
multiline_comment|/* this will put all memory onto the freelists */
id|totalram_pages
op_assign
id|free_all_bootmem
c_func
(paren
)paren
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
id|max_mapnr
suffix:semicolon
id|tmp
op_increment
)paren
(brace
multiline_comment|/*&n;                 * Only count reserved RAM pages&n;                 */
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
id|KERN_INFO
l_string|&quot;Memory: %luk/%luk available (%dk kernel code, %dk reserved, %dk data, &quot;
l_string|&quot;%dk init)&bslash;n&quot;
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
multiline_comment|/* free the pages occupied by initialization code */
r_void
DECL|function|free_initmem
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
id|KERN_INFO
l_string|&quot;Freeing unused kernel memory: %luk freed&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
(paren
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
)paren
suffix:semicolon
)brace
eof
