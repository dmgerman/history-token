multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999, 2000 by Silicon Graphics&n; * Copyright (C) 2003 by Ralf Baechle&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
DECL|function|pgd_init
r_void
id|pgd_init
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
op_star
id|p
comma
op_star
id|end
suffix:semicolon
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
id|end
op_assign
id|p
op_plus
id|PTRS_PER_PGD
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
id|end
)paren
(brace
id|p
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pmd_table
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pmd_table
suffix:semicolon
id|p
(braket
l_int|2
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pmd_table
suffix:semicolon
id|p
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pmd_table
suffix:semicolon
id|p
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pmd_table
suffix:semicolon
id|p
(braket
l_int|5
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pmd_table
suffix:semicolon
id|p
(braket
l_int|6
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pmd_table
suffix:semicolon
id|p
(braket
l_int|7
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pmd_table
suffix:semicolon
id|p
op_add_assign
l_int|8
suffix:semicolon
)brace
)brace
DECL|function|pmd_init
r_void
id|pmd_init
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|pagetable
)paren
(brace
r_int
r_int
op_star
id|p
comma
op_star
id|end
suffix:semicolon
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
id|end
op_assign
id|p
op_plus
id|PTRS_PER_PMD
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
id|end
)paren
(brace
id|p
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|pagetable
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_int
)paren
id|pagetable
suffix:semicolon
id|p
(braket
l_int|2
)braket
op_assign
(paren
r_int
r_int
)paren
id|pagetable
suffix:semicolon
id|p
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|pagetable
suffix:semicolon
id|p
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
id|pagetable
suffix:semicolon
id|p
(braket
l_int|5
)braket
op_assign
(paren
r_int
r_int
)paren
id|pagetable
suffix:semicolon
id|p
(braket
l_int|6
)braket
op_assign
(paren
r_int
r_int
)paren
id|pagetable
suffix:semicolon
id|p
(braket
l_int|7
)braket
op_assign
(paren
r_int
r_int
)paren
id|pagetable
suffix:semicolon
id|p
op_add_assign
l_int|8
suffix:semicolon
)brace
)brace
DECL|function|pagetable_init
r_void
id|__init
id|pagetable_init
c_func
(paren
r_void
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Initialize the entire pgd.  */
id|pgd_init
c_func
(paren
(paren
r_int
r_int
)paren
id|swapper_pg_dir
)paren
suffix:semicolon
id|pmd_init
c_func
(paren
(paren
r_int
r_int
)paren
id|invalid_pmd_table
comma
(paren
r_int
r_int
)paren
id|invalid_pte_table
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|invalid_pte_table
comma
l_int|0
comma
r_sizeof
(paren
id|pte_t
)paren
op_star
id|PTRS_PER_PTE
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|kptbl
comma
l_int|0
comma
id|PAGE_SIZE
op_lshift
id|PGD_ORDER
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|kpmdtbl
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|set_pgd
c_func
(paren
id|swapper_pg_dir
comma
id|__pgd
c_func
(paren
(paren
r_int
r_int
)paren
id|kpmdtbl
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The 64-bit kernel uses a flat pagetable for it&squot;s kernel mappings ...&n;&t; */
id|pmd
op_assign
id|kpmdtbl
suffix:semicolon
id|pte
op_assign
id|kptbl
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
(paren
l_int|1
op_lshift
id|PGD_ORDER
)paren
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
(paren
r_int
r_int
)paren
id|pte
suffix:semicolon
id|pte
op_add_assign
id|PTRS_PER_PTE
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
)brace
eof
