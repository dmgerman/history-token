multiline_comment|/*&n; *  linux/arch/m68k/mm/memory.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#ifdef CONFIG_AMIGA
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#endif
multiline_comment|/* ++andreas: {get,free}_pointer_table rewritten to use unused fields from&n;   struct page instead of separately kmalloced struct.  Stolen from&n;   arch/sparc/mm/srmmu.c ... */
DECL|typedef|ptable_desc
r_typedef
r_struct
id|list_head
id|ptable_desc
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|ptable_list
)paren
suffix:semicolon
DECL|macro|PD_PTABLE
mdefine_line|#define PD_PTABLE(page) ((ptable_desc *)virt_to_page(page))
DECL|macro|PD_PAGE
mdefine_line|#define PD_PAGE(ptable) (list_entry(ptable, struct page, list))
DECL|macro|PD_MARKBITS
mdefine_line|#define PD_MARKBITS(dp) (*(unsigned char *)&amp;PD_PAGE(dp)-&gt;index)
DECL|macro|PTABLE_SIZE
mdefine_line|#define PTABLE_SIZE (PTRS_PER_PMD * sizeof(pmd_t))
DECL|function|init_pointer_table
r_void
id|__init
id|init_pointer_table
c_func
(paren
r_int
r_int
id|ptable
)paren
(brace
id|ptable_desc
op_star
id|dp
suffix:semicolon
r_int
r_int
id|page
op_assign
id|ptable
op_amp
id|PAGE_MASK
suffix:semicolon
r_int
r_char
id|mask
op_assign
l_int|1
op_lshift
(paren
(paren
id|ptable
op_minus
id|page
)paren
op_div
id|PTABLE_SIZE
)paren
suffix:semicolon
id|dp
op_assign
id|PD_PTABLE
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|PD_MARKBITS
c_func
(paren
id|dp
)paren
op_amp
id|mask
)paren
)paren
(brace
id|PD_MARKBITS
c_func
(paren
id|dp
)paren
op_assign
l_int|0xff
suffix:semicolon
id|list_add
c_func
(paren
id|dp
comma
op_amp
id|ptable_list
)paren
suffix:semicolon
)brace
id|PD_MARKBITS
c_func
(paren
id|dp
)paren
op_and_assign
op_complement
id|mask
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;init_pointer_table: %lx, %x&bslash;n&quot;
comma
id|ptable
comma
id|PD_MARKBITS
c_func
(paren
id|dp
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* unreserve the page so it&squot;s possible to free that page */
id|PD_PAGE
c_func
(paren
id|dp
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
id|atomic_set
c_func
(paren
op_amp
id|PD_PAGE
c_func
(paren
id|dp
)paren
op_member_access_from_pointer
id|count
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|get_pointer_table
id|pmd_t
op_star
id|get_pointer_table
(paren
r_void
)paren
(brace
id|ptable_desc
op_star
id|dp
op_assign
id|ptable_list.next
suffix:semicolon
r_int
r_char
id|mask
op_assign
id|PD_MARKBITS
(paren
id|dp
)paren
suffix:semicolon
r_int
r_char
id|tmp
suffix:semicolon
r_int
r_int
id|off
suffix:semicolon
multiline_comment|/*&n;&t; * For a pointer table for a user process address space, a&n;&t; * table is taken from a page allocated for the purpose.  Each&n;&t; * page can hold 8 pointer tables.  The page is remapped in&n;&t; * virtual address space to be noncacheable.&n;&t; */
r_if
c_cond
(paren
id|mask
op_eq
l_int|0
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
id|ptable_desc
op_star
r_new
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
id|get_free_page
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|flush_tlb_kernel_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|nocache_page
(paren
id|page
)paren
suffix:semicolon
r_new
op_assign
id|PD_PTABLE
c_func
(paren
id|page
)paren
suffix:semicolon
id|PD_MARKBITS
c_func
(paren
r_new
)paren
op_assign
l_int|0xfe
suffix:semicolon
id|list_add_tail
c_func
(paren
r_new
comma
id|dp
)paren
suffix:semicolon
r_return
(paren
id|pmd_t
op_star
)paren
id|page
suffix:semicolon
)brace
r_for
c_loop
(paren
id|tmp
op_assign
l_int|1
comma
id|off
op_assign
l_int|0
suffix:semicolon
(paren
id|mask
op_amp
id|tmp
)paren
op_eq
l_int|0
suffix:semicolon
id|tmp
op_lshift_assign
l_int|1
comma
id|off
op_add_assign
id|PTABLE_SIZE
)paren
suffix:semicolon
id|PD_MARKBITS
c_func
(paren
id|dp
)paren
op_assign
id|mask
op_amp
op_complement
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PD_MARKBITS
c_func
(paren
id|dp
)paren
)paren
(brace
multiline_comment|/* move to end of list */
id|list_del
c_func
(paren
id|dp
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
id|dp
comma
op_amp
id|ptable_list
)paren
suffix:semicolon
)brace
r_return
(paren
id|pmd_t
op_star
)paren
(paren
id|page_address
c_func
(paren
id|PD_PAGE
c_func
(paren
id|dp
)paren
)paren
op_plus
id|off
)paren
suffix:semicolon
)brace
DECL|function|free_pointer_table
r_int
id|free_pointer_table
(paren
id|pmd_t
op_star
id|ptable
)paren
(brace
id|ptable_desc
op_star
id|dp
suffix:semicolon
r_int
r_int
id|page
op_assign
(paren
r_int
r_int
)paren
id|ptable
op_amp
id|PAGE_MASK
suffix:semicolon
r_int
r_char
id|mask
op_assign
l_int|1
op_lshift
(paren
(paren
(paren
r_int
r_int
)paren
id|ptable
op_minus
id|page
)paren
op_div
id|PTABLE_SIZE
)paren
suffix:semicolon
id|dp
op_assign
id|PD_PTABLE
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PD_MARKBITS
(paren
id|dp
)paren
op_amp
id|mask
)paren
id|panic
(paren
l_string|&quot;table already free!&quot;
)paren
suffix:semicolon
id|PD_MARKBITS
(paren
id|dp
)paren
op_or_assign
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|PD_MARKBITS
c_func
(paren
id|dp
)paren
op_eq
l_int|0xff
)paren
(brace
multiline_comment|/* all tables in page are free, free page */
id|list_del
c_func
(paren
id|dp
)paren
suffix:semicolon
id|cache_page
(paren
id|page
)paren
suffix:semicolon
id|free_page
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ptable_list.next
op_ne
id|dp
)paren
(brace
multiline_comment|/*&n;&t;&t; * move this descriptor to the front of the list, since&n;&t;&t; * it has one or more free tables.&n;&t;&t; */
id|list_del
c_func
(paren
id|dp
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|dp
comma
op_amp
id|ptable_list
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|transp_transl_matches
r_static
r_int
r_int
id|transp_transl_matches
c_func
(paren
r_int
r_int
id|regval
comma
r_int
r_int
id|vaddr
)paren
(brace
r_int
r_int
id|base
comma
id|mask
suffix:semicolon
multiline_comment|/* enabled? */
r_if
c_cond
(paren
op_logical_neg
(paren
id|regval
op_amp
l_int|0x8000
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|CPU_IS_030
)paren
(brace
multiline_comment|/* function code match? */
id|base
op_assign
(paren
id|regval
op_rshift
l_int|4
)paren
op_amp
l_int|7
suffix:semicolon
id|mask
op_assign
op_complement
(paren
id|regval
op_amp
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|SUPER_DATA
op_xor
id|base
)paren
op_amp
id|mask
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* must not be user-only */
r_if
c_cond
(paren
(paren
id|regval
op_amp
l_int|0x6000
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* address match? */
id|base
op_assign
id|regval
op_amp
l_int|0xff000000
suffix:semicolon
id|mask
op_assign
op_complement
(paren
id|regval
op_lshift
l_int|8
)paren
op_amp
l_int|0xff000000
suffix:semicolon
r_return
(paren
(paren
(paren
r_int
r_int
)paren
id|vaddr
op_xor
id|base
)paren
op_amp
id|mask
)paren
op_eq
l_int|0
suffix:semicolon
)brace
macro_line|#if DEBUG_INVALID_PTOV
DECL|variable|mm_inv_cnt
r_int
id|mm_inv_cnt
op_assign
l_int|5
suffix:semicolon
macro_line|#endif
macro_line|#ifndef CONFIG_SINGLE_MEMORY_CHUNK
multiline_comment|/*&n; * The following two routines map from a physical address to a kernel&n; * virtual address and vice versa.&n; */
DECL|function|mm_vtop
r_int
r_int
id|mm_vtop
c_func
(paren
r_int
r_int
id|vaddr
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|voff
op_assign
(paren
r_int
r_int
)paren
id|vaddr
op_minus
id|PAGE_OFFSET
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|voff
OL
id|m68k_memory
(braket
id|i
)braket
dot
id|size
)paren
(brace
macro_line|#ifdef DEBUGPV
id|printk
(paren
l_string|&quot;VTOP(%p)=%lx&bslash;n&quot;
comma
id|vaddr
comma
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
op_plus
id|voff
)paren
suffix:semicolon
macro_line|#endif
r_return
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
op_plus
id|voff
suffix:semicolon
)brace
id|voff
op_sub_assign
id|m68k_memory
(braket
id|i
)braket
dot
id|size
suffix:semicolon
)brace
r_while
c_loop
(paren
op_increment
id|i
OL
id|m68k_num_memory
)paren
suffix:semicolon
multiline_comment|/* As a special case allow `__pa(high_memory)&squot;.  */
r_if
c_cond
(paren
id|voff
op_eq
l_int|0
)paren
r_return
id|m68k_memory
(braket
id|i
op_minus
l_int|1
)braket
dot
id|addr
op_plus
id|m68k_memory
(braket
id|i
op_minus
l_int|1
)braket
dot
id|size
suffix:semicolon
multiline_comment|/* As a special case allow `__pa(high_memory)&squot;.  */
r_if
c_cond
(paren
id|voff
op_eq
l_int|0
)paren
r_return
id|m68k_memory
(braket
id|i
op_minus
l_int|1
)braket
dot
id|addr
op_plus
id|m68k_memory
(braket
id|i
op_minus
l_int|1
)braket
dot
id|size
suffix:semicolon
r_return
id|mm_vtop_fallback
c_func
(paren
id|vaddr
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Separate function to make the common case faster (needs to save less&n;   registers) */
DECL|function|mm_vtop_fallback
r_int
r_int
id|mm_vtop_fallback
c_func
(paren
r_int
r_int
id|vaddr
)paren
(brace
multiline_comment|/* not in one of the memory chunks; test for applying transparent&n;&t; * translation */
r_if
c_cond
(paren
id|CPU_IS_030
)paren
(brace
r_int
r_int
id|ttreg
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;.chip 68030&bslash;n&bslash;t&quot;
l_string|&quot;pmove %/tt0,%0@&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|ttreg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transp_transl_matches
c_func
(paren
id|ttreg
comma
id|vaddr
)paren
)paren
r_return
(paren
r_int
r_int
)paren
id|vaddr
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;.chip 68030&bslash;n&bslash;t&quot;
l_string|&quot;pmove %/tt1,%0@&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|ttreg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transp_transl_matches
c_func
(paren
id|ttreg
comma
id|vaddr
)paren
)paren
r_return
(paren
r_int
r_int
)paren
id|vaddr
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
r_int
r_int
id|ttreg
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;movec %%dtt0,%0&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ttreg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transp_transl_matches
c_func
(paren
id|ttreg
comma
id|vaddr
)paren
)paren
r_return
(paren
r_int
r_int
)paren
id|vaddr
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;movec %%dtt1,%0&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ttreg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transp_transl_matches
c_func
(paren
id|ttreg
comma
id|vaddr
)paren
)paren
r_return
(paren
r_int
r_int
)paren
id|vaddr
suffix:semicolon
)brace
multiline_comment|/* no match, too, so get the actual physical address from the MMU. */
r_if
c_cond
(paren
id|CPU_IS_060
)paren
(brace
id|mm_segment_t
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|paddr
suffix:semicolon
id|set_fs
(paren
id|MAKE_MM_SEG
c_func
(paren
id|SUPER_DATA
)paren
)paren
suffix:semicolon
multiline_comment|/* The PLPAR instruction causes an access error if the translation&n;&t;   * is not possible. To catch this we use the same exception mechanism&n;&t;   * as for user space accesses in &lt;asm/uaccess.h&gt;. */
id|asm
r_volatile
(paren
l_string|&quot;.chip 68060&bslash;n&quot;
l_string|&quot;1: plpar (%0)&bslash;n&quot;
l_string|&quot;.chip 68k&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .even&bslash;n&quot;
l_string|&quot;3: lea -1,%0&bslash;n&quot;
l_string|&quot;   jra 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long 1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|paddr
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|vaddr
)paren
)paren
suffix:semicolon
id|set_fs
(paren
id|fs
)paren
suffix:semicolon
r_return
id|paddr
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CPU_IS_040
)paren
(brace
r_int
r_int
id|mmusr
suffix:semicolon
id|mm_segment_t
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
(paren
id|MAKE_MM_SEG
c_func
(paren
id|SUPER_DATA
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;.chip 68040&bslash;n&bslash;t&quot;
l_string|&quot;ptestr (%1)&bslash;n&bslash;t&quot;
l_string|&quot;movec %%mmusr, %0&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|mmusr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
)paren
suffix:semicolon
id|set_fs
(paren
id|fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mmusr
op_amp
id|MMU_T_040
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|vaddr
suffix:semicolon
multiline_comment|/* Transparent translation */
)brace
r_if
c_cond
(paren
id|mmusr
op_amp
id|MMU_R_040
)paren
r_return
(paren
id|mmusr
op_amp
id|PAGE_MASK
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|vaddr
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;VTOP040: bad virtual address %lx (%lx)&quot;
comma
id|vaddr
comma
id|mmusr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_volatile
r_int
r_int
id|temp
suffix:semicolon
r_int
r_int
id|mmusr
suffix:semicolon
r_int
r_int
op_star
id|descaddr
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;ptestr #5,%2@,#7,%0&bslash;n&bslash;t&quot;
l_string|&quot;pmove %/psr,%1@&quot;
suffix:colon
l_string|&quot;=a&amp;&quot;
(paren
id|descaddr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|temp
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
)paren
suffix:semicolon
id|mmusr
op_assign
id|temp
suffix:semicolon
r_if
c_cond
(paren
id|mmusr
op_amp
(paren
id|MMU_I
op_or
id|MMU_B
op_or
id|MMU_L
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;VTOP030: bad virtual address %lx (%x)&bslash;n&quot;
comma
id|vaddr
comma
id|mmusr
)paren
suffix:semicolon
id|descaddr
op_assign
id|phys_to_virt
c_func
(paren
(paren
r_int
r_int
)paren
id|descaddr
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mmusr
op_amp
id|MMU_NUM
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
(paren
op_star
id|descaddr
op_amp
l_int|0xfe000000
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|vaddr
op_amp
l_int|0x01ffffff
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
(paren
op_star
id|descaddr
op_amp
l_int|0xfffc0000
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|vaddr
op_amp
l_int|0x0003ffff
)paren
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
(paren
op_star
id|descaddr
op_amp
id|PAGE_MASK
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|vaddr
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;VTOP: bad levels (%u) for virtual address %lx&bslash;n&quot;
comma
id|mmusr
op_amp
id|MMU_NUM
comma
id|vaddr
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;VTOP: bad virtual address %lx&bslash;n&quot;
comma
id|vaddr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_SINGLE_MEMORY_CHUNK
DECL|function|mm_ptov
r_int
r_int
id|mm_ptov
(paren
r_int
r_int
id|paddr
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|poff
comma
id|voff
op_assign
id|PAGE_OFFSET
suffix:semicolon
r_do
(brace
id|poff
op_assign
id|paddr
op_minus
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|poff
OL
id|m68k_memory
(braket
id|i
)braket
dot
id|size
)paren
(brace
macro_line|#ifdef DEBUGPV
id|printk
(paren
l_string|&quot;PTOV(%lx)=%lx&bslash;n&quot;
comma
id|paddr
comma
id|poff
op_plus
id|voff
)paren
suffix:semicolon
macro_line|#endif
r_return
id|poff
op_plus
id|voff
suffix:semicolon
)brace
id|voff
op_add_assign
id|m68k_memory
(braket
id|i
)braket
dot
id|size
suffix:semicolon
)brace
r_while
c_loop
(paren
op_increment
id|i
OL
id|m68k_num_memory
)paren
suffix:semicolon
macro_line|#if DEBUG_INVALID_PTOV
r_if
c_cond
(paren
id|mm_inv_cnt
OG
l_int|0
)paren
(brace
id|mm_inv_cnt
op_decrement
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Invalid use of phys_to_virt(0x%lx) at 0x%p!&bslash;n&quot;
comma
id|paddr
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * assume that the kernel virtual address is the same as the&n;&t; * physical address.&n;&t; *&n;&t; * This should be reasonable in most situations:&n;&t; *  1) They shouldn&squot;t be dereferencing the virtual address&n;&t; *     unless they are sure that it is valid from kernel space.&n;&t; *  2) The only usage I see so far is converting a page table&n;&t; *     reference to some non-FASTMEM address space when freeing&n;         *     mmaped &quot;/dev/mem&quot; pages.  These addresses are just passed&n;&t; *     to &quot;free_page&quot;, which ignores addresses that aren&squot;t in&n;&t; *     the memory list anyway.&n;&t; *&n;&t; */
macro_line|#ifdef CONFIG_AMIGA
multiline_comment|/*&n;&t; * if on an amiga and address is in first 16M, move it &n;&t; * to the ZTWO_VADDR range&n;&t; */
r_if
c_cond
(paren
id|MACH_IS_AMIGA
op_logical_and
id|paddr
OL
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
r_return
id|ZTWO_VADDR
c_func
(paren
id|paddr
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* invalidate page in both caches */
DECL|macro|clear040
mdefine_line|#define&t;clear040(paddr)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;.chip 68040&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;      &quot;cinvp %%bc,(%0)&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;      &quot;.chip 68k&quot;&t;&t;&bslash;&n;&t;&t;&t;      : : &quot;a&quot; (paddr))
multiline_comment|/* invalidate page in i-cache */
DECL|macro|cleari040
mdefine_line|#define&t;cleari040(paddr)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;.chip 68040&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;      &quot;cinvp %%ic,(%0)&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;      &quot;.chip 68k&quot;&t;&t;&bslash;&n;&t;&t;&t;      : : &quot;a&quot; (paddr))
multiline_comment|/* push page in both caches */
DECL|macro|push040
mdefine_line|#define&t;push040(paddr)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;.chip 68040&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;      &quot;cpushp %%bc,(%0)&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;      &quot;.chip 68k&quot;&t;&t;&bslash;&n;&t;&t;&t;      : : &quot;a&quot; (paddr))
multiline_comment|/* push and invalidate page in both caches, must disable ints&n; * to avoid invalidating valid data */
DECL|macro|pushcl040
mdefine_line|#define&t;pushcl040(paddr)&t;&t;&t;&bslash;&n;&t;do { unsigned long flags;               &bslash;&n;             save_flags(flags);                 &bslash;&n;&t;     cli();                             &bslash;&n;             push040(paddr);&t;&t;&t;&bslash;&n;&t;     if (CPU_IS_060) clear040(paddr);&t;&bslash;&n;&t;     restore_flags(flags);              &bslash;&n;&t;} while(0)
multiline_comment|/* push page in both caches, invalidate in i-cache */
multiline_comment|/* RZ: cpush %bc DOES invalidate %ic, regardless of DPI */
DECL|macro|pushcli040
mdefine_line|#define&t;pushcli040(paddr)&t;&t;&t;&bslash;&n;&t;do { push040(paddr);&t;&t;&t;&bslash;&n;&t;} while(0)
multiline_comment|/*&n; * 040: Hit every page containing an address in the range paddr..paddr+len-1.&n; * (Low order bits of the ea of a CINVP/CPUSHP are &quot;don&squot;t care&quot;s).&n; * Hit every page until there is a page or less to go. Hit the next page,&n; * and the one after that if the range hits it.&n; */
multiline_comment|/* ++roman: A little bit more care is required here: The CINVP instruction&n; * invalidates cache entries WITHOUT WRITING DIRTY DATA BACK! So the beginning&n; * and the end of the region must be treated differently if they are not&n; * exactly at the beginning or end of a page boundary. Else, maybe too much&n; * data becomes invalidated and thus lost forever. CPUSHP does what we need:&n; * it invalidates the page after pushing dirty data to memory. (Thanks to Jes&n; * for discovering the problem!)&n; */
multiline_comment|/* ... but on the &squot;060, CPUSH doesn&squot;t invalidate (for us, since we have set&n; * the DPI bit in the CACR; would it cause problems with temporarily changing&n; * this?). So we have to push first and then additionally to invalidate.&n; */
multiline_comment|/*&n; * cache_clear() semantics: Clear any cache entries for the area in question,&n; * without writing back dirty entries first. This is useful if the data will&n; * be overwritten anyway, e.g. by DMA to memory. The range is defined by a&n; * _physical_ address.&n; */
DECL|function|cache_clear
r_void
id|cache_clear
(paren
r_int
r_int
id|paddr
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
r_int
id|tmp
suffix:semicolon
multiline_comment|/*&n;&t; * We need special treatment for the first page, in case it&n;&t; * is not page-aligned. Page align the addresses to work&n;&t; * around bug I17 in the 68060.&n;&t; */
r_if
c_cond
(paren
(paren
id|tmp
op_assign
op_minus
id|paddr
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|pushcl040
c_func
(paren
id|paddr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|tmp
)paren
op_le
l_int|0
)paren
r_return
suffix:semicolon
id|paddr
op_add_assign
id|tmp
suffix:semicolon
)brace
id|tmp
op_assign
id|PAGE_SIZE
suffix:semicolon
id|paddr
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_while
c_loop
(paren
(paren
id|len
op_sub_assign
id|tmp
)paren
op_ge
l_int|0
)paren
(brace
id|clear040
c_func
(paren
id|paddr
)paren
suffix:semicolon
id|paddr
op_add_assign
id|tmp
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|len
op_add_assign
id|tmp
)paren
)paren
multiline_comment|/* a page boundary gets crossed at the end */
id|pushcl040
c_func
(paren
id|paddr
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* 68030 or 68020 */
id|asm
r_volatile
(paren
l_string|&quot;movec %/cacr,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;oriw %0,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movec %/d0,%/cacr&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|FLUSH_I_AND_D
)paren
suffix:colon
l_string|&quot;d0&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_M68K_L2_CACHE
r_if
c_cond
(paren
id|mach_l2_flush
)paren
(brace
id|mach_l2_flush
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; * cache_push() semantics: Write back any dirty cache data in the given area,&n; * and invalidate the range in the instruction cache. It needs not (but may)&n; * invalidate those entries also in the data cache. The range is defined by a&n; * _physical_ address.&n; */
DECL|function|cache_push
r_void
id|cache_push
(paren
r_int
r_int
id|paddr
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
r_int
id|tmp
op_assign
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/*&n;         * on 68040 or 68060, push cache lines for pages in the range;&n;&t; * on the &squot;040 this also invalidates the pushed lines, but not on&n;&t; * the &squot;060!&n;&t; */
id|len
op_add_assign
id|paddr
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Work around bug I17 in the 68060 affecting some instruction&n;&t; * lines not being invalidated properly.&n;&t; */
id|paddr
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_do
(brace
id|pushcli040
c_func
(paren
id|paddr
)paren
suffix:semicolon
id|paddr
op_add_assign
id|tmp
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|len
op_sub_assign
id|tmp
)paren
OG
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     * 68030/68020 have no writeback cache. On the other hand,&n;     * cache_push is actually a superset of cache_clear (the lines&n;     * get written back and invalidated), so we should make sure&n;     * to perform the corresponding actions. After all, this is getting&n;     * called in places where we&squot;ve just loaded code, or whatever, so&n;     * flushing the icache is appropriate; flushing the dcache shouldn&squot;t&n;     * be required.&n;     */
r_else
multiline_comment|/* 68030 or 68020 */
id|asm
r_volatile
(paren
l_string|&quot;movec %/cacr,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;oriw %0,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;movec %/d0,%/cacr&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|FLUSH_I
)paren
suffix:colon
l_string|&quot;d0&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_M68K_L2_CACHE
r_if
c_cond
(paren
id|mach_l2_flush
)paren
(brace
id|mach_l2_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|macro|clear040
macro_line|#undef clear040
DECL|macro|cleari040
macro_line|#undef cleari040
DECL|macro|push040
macro_line|#undef push040
DECL|macro|pushcl040
macro_line|#undef pushcl040
DECL|macro|pushcli040
macro_line|#undef pushcli040
macro_line|#ifndef CONFIG_SINGLE_MEMORY_CHUNK
DECL|function|mm_end_of_chunk
r_int
id|mm_end_of_chunk
(paren
r_int
r_int
id|addr
comma
r_int
id|len
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
id|m68k_num_memory
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
op_plus
id|m68k_memory
(braket
id|i
)braket
dot
id|size
op_eq
id|addr
op_plus
id|len
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
