multiline_comment|/*&n; *  arch/s390/mm/ioremap.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com)&n; *&n; *  Derived from &quot;arch/i386/mm/extable.c&quot;&n; *    (C) Copyright 1995 1996 Linus Torvalds&n; *&n; * Re-map IO memory to kernel address space so that we can access it.&n; * This is needed for high PCI addresses that aren&squot;t mapped in the&n; * 640k-1MB IO memory area on PC&squot;s&n; */
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
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
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
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
r_do
(brace
id|pmd_t
op_star
id|pmd
op_assign
id|pmd_alloc_kernel
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
r_return
op_minus
id|ENOMEM
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|set_pgdir
c_func
(paren
id|address
comma
op_star
id|dir
)paren
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
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic mapping function (not visible outside):&n; */
multiline_comment|/*&n; * Remap an arbitrary physical address space into the kernel virtual&n; * address space. Needed when the kernel wants to access high addresses&n; * directly.&n; */
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
r_return
id|phys_to_virt
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phys_addr
op_amp
op_complement
id|PAGE_MASK
)paren
r_return
l_int|NULL
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|size
OG
id|phys_addr
op_plus
id|size
)paren
r_return
l_int|NULL
suffix:semicolon
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
id|addr
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
id|addr
)paren
suffix:semicolon
)brace
eof
