multiline_comment|/*&n; * arch/x86_64/mm/ioremap.c&n; *&n; * Re-map IO memory to kernel address space so that we can access it.&n; * This is needed for high PCI addresses that aren&squot;t mapped in the&n; * 640k-1MB IO memory area on PC&squot;s&n; *&n; * (C) Copyright 1995 1996 Linus Torvalds&n; */
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|function|remap_area_pte
r_static
r_inline
r_void
id|remap_area_pte
c_func
(paren
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
id|phys_addr
comma
r_int
r_int
id|flags
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
r_if
c_cond
(paren
id|address
op_ge
id|end
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;remap_area_pte: page already exists&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_pte
c_func
(paren
id|pte
comma
id|mk_pte_phys
c_func
(paren
id|phys_addr
comma
id|__pgprot
c_func
(paren
id|_PAGE_PRESENT
op_or
id|_PAGE_RW
op_or
id|_PAGE_GLOBAL
op_or
id|_PAGE_DIRTY
op_or
id|_PAGE_ACCESSED
op_or
id|flags
)paren
)paren
)paren
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|phys_addr
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
op_logical_and
(paren
id|address
OL
id|end
)paren
)paren
suffix:semicolon
)brace
DECL|function|remap_area_pmd
r_static
r_inline
r_int
id|remap_area_pmd
c_func
(paren
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
id|phys_addr
comma
r_int
r_int
id|flags
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
id|phys_addr
op_sub_assign
id|address
suffix:semicolon
r_if
c_cond
(paren
id|address
op_ge
id|end
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|pte_t
op_star
id|pte
op_assign
id|pte_alloc_kernel
c_func
(paren
op_amp
id|init_mm
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
id|remap_area_pte
c_func
(paren
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
id|phys_addr
comma
id|flags
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
op_logical_and
(paren
id|address
OL
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|remap_area_pages
r_static
r_int
id|remap_area_pages
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
(brace
r_int
id|error
suffix:semicolon
id|pgd_t
op_star
id|dir
suffix:semicolon
r_int
r_int
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
id|phys_addr
op_sub_assign
id|address
suffix:semicolon
id|dir
op_assign
id|pgd_offset_k
c_func
(paren
id|address
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|address
op_ge
id|end
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
r_do
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
op_amp
id|init_mm
comma
id|dir
comma
id|address
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
id|pmd
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|remap_area_pmd
c_func
(paren
id|pmd
comma
id|address
comma
id|end
op_minus
id|address
comma
id|phys_addr
op_plus
id|address
comma
id|flags
)paren
)paren
r_break
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
id|address
op_assign
(paren
id|address
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
r_while
c_loop
(paren
id|address
op_logical_and
(paren
id|address
OL
id|end
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic mapping function (not visible outside):&n; */
multiline_comment|/*&n; * Remap an arbitrary physical address space into the kernel virtual&n; * address space. Needed when the kernel wants to access high addresses&n; * directly.&n; *&n; * NOTE! We need to allow non-page-aligned mappings too: we will obviously&n; * have to convert them into an offset in a page-aligned mapping, but the&n; * caller shouldn&squot;t need to know that small detail.&n; */
DECL|function|__ioremap
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
(brace
r_void
op_star
id|addr
suffix:semicolon
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_int
r_int
id|offset
comma
id|last_addr
suffix:semicolon
multiline_comment|/* Don&squot;t allow wraparound or zero size */
id|last_addr
op_assign
id|phys_addr
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|last_addr
OL
id|phys_addr
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t remap the low PCI/ISA area, it&squot;s always mapped..&n;&t; */
r_if
c_cond
(paren
id|phys_addr
op_ge
l_int|0xA0000
op_logical_and
id|last_addr
OL
l_int|0x100000
)paren
r_return
id|phys_to_virt
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t allow anybody to remap normal RAM that we&squot;re using..&n;&t; */
r_if
c_cond
(paren
id|phys_addr
OL
id|virt_to_phys
c_func
(paren
id|high_memory
)paren
)paren
(brace
r_char
op_star
id|t_addr
comma
op_star
id|t_end
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|t_addr
op_assign
id|__va
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
id|t_end
op_assign
id|t_addr
op_plus
(paren
id|size
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|page
op_assign
id|virt_to_page
c_func
(paren
id|t_addr
)paren
suffix:semicolon
id|page
op_le
id|virt_to_page
c_func
(paren
id|t_end
)paren
suffix:semicolon
id|page
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Mappings have to be page-aligned&n;&t; */
id|offset
op_assign
id|phys_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|phys_addr
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|last_addr
)paren
op_minus
id|phys_addr
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, go for it..&n;&t; */
id|area
op_assign
id|get_vm_area
c_func
(paren
id|size
comma
id|VM_IOREMAP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_return
l_int|NULL
suffix:semicolon
id|addr
op_assign
id|area-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
id|remap_area_pages
c_func
(paren
id|VMALLOC_VMADDR
c_func
(paren
id|addr
)paren
comma
id|phys_addr
comma
id|size
comma
id|flags
)paren
)paren
(brace
id|vfree
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
(paren
id|offset
op_plus
(paren
r_char
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|iounmap
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr
OG
id|high_memory
)paren
r_return
id|vfree
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|PAGE_MASK
op_amp
(paren
r_int
r_int
)paren
id|addr
)paren
)paren
suffix:semicolon
)brace
eof
