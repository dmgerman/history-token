multiline_comment|/*&n; * linux/arch/m68k/mm/sun3mmu.c&n; *&n; * Implementations of mm routines specific to the sun3 MMU.&n; *&n; * Moved here 8/20/1999 Sam Creasey&n; *&n; */
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
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
r_void
id|mmu_emu_init
(paren
r_int
r_int
id|bootmem_end
)paren
suffix:semicolon
DECL|variable|bad_pmd_string
r_const
r_char
id|bad_pmd_string
(braket
)braket
op_assign
l_string|&quot;Bad pmd in pte_alloc: %08lx&bslash;n&quot;
suffix:semicolon
r_extern
r_int
r_int
id|num_pages
suffix:semicolon
DECL|function|free_initmem
r_void
id|free_initmem
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* For the sun3 we try to follow the i386 paging_init() more closely */
multiline_comment|/* start_mem and end_mem have PAGE_OFFSET added already */
multiline_comment|/* now sets up tables using sun3 PTEs rather than i386 as before. --m */
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
r_int
id|i
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
r_int
r_int
id|next_pgtable
suffix:semicolon
r_int
r_int
id|bootmem_end
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
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
macro_line|#ifdef TEST_VERIFY_AREA
id|wp_works_ok
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|empty_zero_page
op_assign
id|alloc_bootmem_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
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
id|address
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|pg_dir
op_assign
id|swapper_pg_dir
suffix:semicolon
id|memset
(paren
id|swapper_pg_dir
comma
l_int|0
comma
r_sizeof
(paren
id|swapper_pg_dir
)paren
)paren
suffix:semicolon
id|memset
(paren
id|kernel_pg_dir
comma
l_int|0
comma
r_sizeof
(paren
id|kernel_pg_dir
)paren
)paren
suffix:semicolon
id|size
op_assign
id|num_pages
op_star
r_sizeof
(paren
id|pte_t
)paren
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
id|PAGE_SIZE
)paren
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|next_pgtable
op_assign
(paren
r_int
r_int
)paren
id|alloc_bootmem_pages
c_func
(paren
id|size
)paren
suffix:semicolon
id|bootmem_end
op_assign
(paren
id|next_pgtable
op_plus
id|size
op_plus
id|PAGE_SIZE
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
multiline_comment|/* Map whole memory from PAGE_OFFSET (0x0E000000) */
id|pg_dir
op_add_assign
id|PAGE_OFFSET
op_rshift
id|PGDIR_SHIFT
suffix:semicolon
r_while
c_loop
(paren
id|address
OL
(paren
r_int
r_int
)paren
id|high_memory
)paren
(brace
id|pg_table
op_assign
(paren
id|pte_t
op_star
)paren
id|__pa
(paren
id|next_pgtable
)paren
suffix:semicolon
id|next_pgtable
op_add_assign
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
id|pte_t
)paren
suffix:semicolon
id|pgd_val
c_func
(paren
op_star
id|pg_dir
)paren
op_assign
(paren
r_int
r_int
)paren
id|pg_table
suffix:semicolon
id|pg_dir
op_increment
suffix:semicolon
multiline_comment|/* now change pg_table to kernel virtual addresses */
id|pg_table
op_assign
(paren
id|pte_t
op_star
)paren
id|__va
(paren
(paren
r_int
r_int
)paren
id|pg_table
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
id|PTRS_PER_PTE
suffix:semicolon
op_increment
id|i
comma
op_increment
id|pg_table
)paren
(brace
id|pte_t
id|pte
op_assign
id|pfn_pte
c_func
(paren
id|virt_to_pfn
c_func
(paren
id|address
)paren
comma
id|PAGE_INIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|address
op_ge
(paren
r_int
r_int
)paren
id|high_memory
)paren
id|pte_val
(paren
id|pte
)paren
op_assign
l_int|0
suffix:semicolon
id|set_pte
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
id|mmu_emu_init
c_func
(paren
id|bootmem_end
)paren
suffix:semicolon
id|current-&gt;mm
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* memory sizing is a hack stolen from motorola.c..  hope it works for us */
id|zones_size
(braket
l_int|0
)braket
op_assign
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
suffix:semicolon
id|zones_size
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|free_area_init
c_func
(paren
id|zones_size
)paren
suffix:semicolon
)brace
eof
