multiline_comment|/* $Id: generic.c,v 1.18 2001/12/21 04:56:15 davem Exp $&n; * generic.c: Generic Sparc mm routines that are not dependent upon&n; *            MMU type but are Sparc specific.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/* Remap IO memory, the same way as remap_pfn_range(), but use&n; * the obio memory space.&n; *&n; * They use a pgprot that sets PAGE_IO and does not check the&n; * mem_map table as this is independent of normal memory.&n; *&n; * As a special hack if the lowest bit of offset is set the&n; * side-effect bit will be turned off.  This is used as a&n; * performance improvement on FFB/AFB. -DaveM&n; */
DECL|function|io_remap_pte_range
r_static
r_inline
r_void
id|io_remap_pte_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pte_t
op_star
id|pte
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|offset
comma
id|pgprot_t
id|prot
comma
r_int
id|space
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
id|address
op_and_assign
op_complement
id|PMD_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PMD_SIZE
)paren
id|end
op_assign
id|PMD_SIZE
suffix:semicolon
r_do
(brace
id|pte_t
id|entry
suffix:semicolon
r_int
r_int
id|curend
op_assign
id|address
op_plus
id|PAGE_SIZE
suffix:semicolon
id|entry
op_assign
id|mk_pte_io
c_func
(paren
(paren
id|offset
op_amp
op_complement
(paren
l_int|0x1UL
)paren
)paren
comma
id|prot
comma
id|space
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|address
op_amp
l_int|0xffff
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|address
op_amp
l_int|0x3fffff
)paren
op_logical_and
op_logical_neg
(paren
id|offset
op_amp
l_int|0x3ffffe
)paren
op_logical_and
id|end
op_ge
id|address
op_plus
l_int|0x400000
)paren
(brace
id|entry
op_assign
id|mk_pte_io
c_func
(paren
(paren
id|offset
op_amp
op_complement
(paren
l_int|0x1UL
)paren
)paren
comma
id|__pgprot
c_func
(paren
id|pgprot_val
(paren
id|prot
)paren
op_or
id|_PAGE_SZ4MB
)paren
comma
id|space
)paren
suffix:semicolon
id|curend
op_assign
id|address
op_plus
l_int|0x400000
suffix:semicolon
id|offset
op_add_assign
l_int|0x400000
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|address
op_amp
l_int|0x7ffff
)paren
op_logical_and
op_logical_neg
(paren
id|offset
op_amp
l_int|0x7fffe
)paren
op_logical_and
id|end
op_ge
id|address
op_plus
l_int|0x80000
)paren
(brace
id|entry
op_assign
id|mk_pte_io
c_func
(paren
(paren
id|offset
op_amp
op_complement
(paren
l_int|0x1UL
)paren
)paren
comma
id|__pgprot
c_func
(paren
id|pgprot_val
(paren
id|prot
)paren
op_or
id|_PAGE_SZ512K
)paren
comma
id|space
)paren
suffix:semicolon
id|curend
op_assign
id|address
op_plus
l_int|0x80000
suffix:semicolon
id|offset
op_add_assign
l_int|0x80000
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|offset
op_amp
l_int|0xfffe
)paren
op_logical_and
id|end
op_ge
id|address
op_plus
l_int|0x10000
)paren
(brace
id|entry
op_assign
id|mk_pte_io
c_func
(paren
(paren
id|offset
op_amp
op_complement
(paren
l_int|0x1UL
)paren
)paren
comma
id|__pgprot
c_func
(paren
id|pgprot_val
(paren
id|prot
)paren
op_or
id|_PAGE_SZ64K
)paren
comma
id|space
)paren
suffix:semicolon
id|curend
op_assign
id|address
op_plus
l_int|0x10000
suffix:semicolon
id|offset
op_add_assign
l_int|0x10000
suffix:semicolon
)brace
r_else
id|offset
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_else
id|offset
op_add_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_amp
l_int|0x1UL
)paren
id|pte_val
c_func
(paren
id|entry
)paren
op_and_assign
op_complement
(paren
id|_PAGE_E
)paren
suffix:semicolon
r_do
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
suffix:semicolon
id|set_pte_at
c_func
(paren
id|mm
comma
id|address
comma
id|pte
comma
id|entry
)paren
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pte
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|curend
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|io_remap_pmd_range
r_static
r_inline
r_int
id|io_remap_pmd_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|offset
comma
id|pgprot_t
id|prot
comma
r_int
id|space
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
id|address
op_and_assign
op_complement
id|PGDIR_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PGDIR_SIZE
)paren
id|end
op_assign
id|PGDIR_SIZE
suffix:semicolon
id|offset
op_sub_assign
id|address
suffix:semicolon
r_do
(brace
id|pte_t
op_star
id|pte
op_assign
id|pte_alloc_map
c_func
(paren
id|mm
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|io_remap_pte_range
c_func
(paren
id|mm
comma
id|pte
comma
id|address
comma
id|end
op_minus
id|address
comma
id|address
op_plus
id|offset
comma
id|prot
comma
id|space
)paren
suffix:semicolon
id|pte_unmap
c_func
(paren
id|pte
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|io_remap_pud_range
r_static
r_inline
r_int
id|io_remap_pud_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pud_t
op_star
id|pud
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|offset
comma
id|pgprot_t
id|prot
comma
r_int
id|space
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
id|address
op_and_assign
op_complement
id|PUD_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PUD_SIZE
)paren
id|end
op_assign
id|PUD_SIZE
suffix:semicolon
id|offset
op_sub_assign
id|address
suffix:semicolon
r_do
(brace
id|pmd_t
op_star
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
id|mm
comma
id|pud
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pud
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|io_remap_pmd_range
c_func
(paren
id|mm
comma
id|pmd
comma
id|address
comma
id|end
op_minus
id|address
comma
id|address
op_plus
id|offset
comma
id|prot
comma
id|space
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PUD_SIZE
)paren
op_amp
id|PUD_MASK
suffix:semicolon
id|pud
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|io_remap_page_range
r_int
id|io_remap_page_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|from
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
comma
r_int
id|space
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|pgd_t
op_star
id|dir
suffix:semicolon
r_int
r_int
id|beg
op_assign
id|from
suffix:semicolon
r_int
r_int
id|end
op_assign
id|from
op_plus
id|size
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
id|prot
op_assign
id|__pgprot
c_func
(paren
id|pg_iobits
)paren
suffix:semicolon
id|offset
op_sub_assign
id|from
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|from
)paren
suffix:semicolon
id|flush_cache_range
c_func
(paren
id|vma
comma
id|beg
comma
id|end
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|from
OL
id|end
)paren
(brace
id|pud_t
op_star
id|pud
op_assign
id|pud_alloc
c_func
(paren
id|mm
comma
id|dir
comma
id|from
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pud
)paren
r_break
suffix:semicolon
id|error
op_assign
id|io_remap_pud_range
c_func
(paren
id|mm
comma
id|pud
comma
id|from
comma
id|end
op_minus
id|from
comma
id|offset
op_plus
id|from
comma
id|prot
comma
id|space
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_break
suffix:semicolon
id|from
op_assign
(paren
id|from
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|dir
op_increment
suffix:semicolon
)brace
id|flush_tlb_range
c_func
(paren
id|vma
comma
id|beg
comma
id|end
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
