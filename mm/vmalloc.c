multiline_comment|/*&n; *  linux/mm/vmalloc.c&n; *&n; *  Copyright (C) 1993  Linus Torvalds&n; *  Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999&n; *  SMP-safe vmalloc/vfree/ioremap, Tigran Aivazian &lt;tigran@veritas.com&gt;, May 2000&n; *  Major rework to support vmap/vunmap, Christoph Hellwig, SGI, August 2002&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|variable|vmlist_lock
id|DEFINE_RWLOCK
c_func
(paren
id|vmlist_lock
)paren
suffix:semicolon
DECL|variable|vmlist
r_struct
id|vm_struct
op_star
id|vmlist
suffix:semicolon
DECL|function|vunmap_pte_range
r_static
r_void
id|vunmap_pte_range
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|addr
)paren
suffix:semicolon
r_do
(brace
id|pte_t
id|ptent
op_assign
id|ptep_get_and_clear
c_func
(paren
op_amp
id|init_mm
comma
id|addr
comma
id|pte
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
op_logical_neg
id|pte_none
c_func
(paren
id|ptent
)paren
op_logical_and
op_logical_neg
id|pte_present
c_func
(paren
id|ptent
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pte
op_increment
comma
id|addr
op_add_assign
id|PAGE_SIZE
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
)brace
DECL|function|vunmap_pmd_range
r_static
r_void
id|vunmap_pmd_range
c_func
(paren
id|pud_t
op_star
id|pud
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pud
comma
id|addr
)paren
suffix:semicolon
r_do
(brace
id|next
op_assign
id|pmd_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none_or_clear_bad
c_func
(paren
id|pmd
)paren
)paren
r_continue
suffix:semicolon
id|vunmap_pte_range
c_func
(paren
id|pmd
comma
id|addr
comma
id|next
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pmd
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
)brace
DECL|function|vunmap_pud_range
r_static
r_void
id|vunmap_pud_range
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
)paren
(brace
id|pud_t
op_star
id|pud
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
id|pud
op_assign
id|pud_offset
c_func
(paren
id|pgd
comma
id|addr
)paren
suffix:semicolon
r_do
(brace
id|next
op_assign
id|pud_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pud_none_or_clear_bad
c_func
(paren
id|pud
)paren
)paren
r_continue
suffix:semicolon
id|vunmap_pmd_range
c_func
(paren
id|pud
comma
id|addr
comma
id|next
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pud
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
)brace
DECL|function|unmap_vm_area
r_void
id|unmap_vm_area
c_func
(paren
r_struct
id|vm_struct
op_star
id|area
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|area-&gt;addr
suffix:semicolon
r_int
r_int
id|end
op_assign
id|addr
op_plus
id|area-&gt;size
suffix:semicolon
id|BUG_ON
c_func
(paren
id|addr
op_ge
id|end
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|addr
)paren
suffix:semicolon
id|flush_cache_vunmap
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
r_do
(brace
id|next
op_assign
id|pgd_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none_or_clear_bad
c_func
(paren
id|pgd
)paren
)paren
r_continue
suffix:semicolon
id|vunmap_pud_range
c_func
(paren
id|pgd
comma
id|addr
comma
id|next
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pgd
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
id|flush_tlb_kernel_range
c_func
(paren
(paren
r_int
r_int
)paren
id|area-&gt;addr
comma
id|end
)paren
suffix:semicolon
)brace
DECL|function|vmap_pte_range
r_static
r_int
id|vmap_pte_range
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
comma
id|pgprot_t
id|prot
comma
r_struct
id|page
op_star
op_star
op_star
id|pages
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
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
id|addr
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
r_do
(brace
r_struct
id|page
op_star
id|page
op_assign
op_star
op_star
id|pages
suffix:semicolon
id|WARN_ON
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
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|set_pte_at
c_func
(paren
op_amp
id|init_mm
comma
id|addr
comma
id|pte
comma
id|mk_pte
c_func
(paren
id|page
comma
id|prot
)paren
)paren
suffix:semicolon
(paren
op_star
id|pages
)paren
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pte
op_increment
comma
id|addr
op_add_assign
id|PAGE_SIZE
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vmap_pmd_range
r_static
r_int
id|vmap_pmd_range
c_func
(paren
id|pud_t
op_star
id|pud
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
comma
id|pgprot_t
id|prot
comma
r_struct
id|page
op_star
op_star
op_star
id|pages
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
op_amp
id|init_mm
comma
id|pud
comma
id|addr
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
r_do
(brace
id|next
op_assign
id|pmd_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vmap_pte_range
c_func
(paren
id|pmd
comma
id|addr
comma
id|next
comma
id|prot
comma
id|pages
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pmd
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vmap_pud_range
r_static
r_int
id|vmap_pud_range
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|end
comma
id|pgprot_t
id|prot
comma
r_struct
id|page
op_star
op_star
op_star
id|pages
)paren
(brace
id|pud_t
op_star
id|pud
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
id|pud
op_assign
id|pud_alloc
c_func
(paren
op_amp
id|init_mm
comma
id|pgd
comma
id|addr
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
r_do
(brace
id|next
op_assign
id|pud_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vmap_pmd_range
c_func
(paren
id|pud
comma
id|addr
comma
id|next
comma
id|prot
comma
id|pages
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pud
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|map_vm_area
r_int
id|map_vm_area
c_func
(paren
r_struct
id|vm_struct
op_star
id|area
comma
id|pgprot_t
id|prot
comma
r_struct
id|page
op_star
op_star
op_star
id|pages
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|area-&gt;addr
suffix:semicolon
r_int
r_int
id|end
op_assign
id|addr
op_plus
id|area-&gt;size
op_minus
id|PAGE_SIZE
suffix:semicolon
r_int
id|err
suffix:semicolon
id|BUG_ON
c_func
(paren
id|addr
op_ge
id|end
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|addr
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
id|next
op_assign
id|pgd_addr_end
c_func
(paren
id|addr
comma
id|end
)paren
suffix:semicolon
id|err
op_assign
id|vmap_pud_range
c_func
(paren
id|pgd
comma
id|addr
comma
id|next
comma
id|prot
comma
id|pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pgd
op_increment
comma
id|addr
op_assign
id|next
comma
id|addr
op_ne
id|end
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|init_mm.page_table_lock
)paren
suffix:semicolon
id|flush_cache_vmap
c_func
(paren
(paren
r_int
r_int
)paren
id|area-&gt;addr
comma
id|end
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|macro|IOREMAP_MAX_ORDER
mdefine_line|#define IOREMAP_MAX_ORDER&t;(7 + PAGE_SHIFT)&t;/* 128 pages */
DECL|function|__get_vm_area
r_struct
id|vm_struct
op_star
id|__get_vm_area
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_struct
id|vm_struct
op_star
op_star
id|p
comma
op_star
id|tmp
comma
op_star
id|area
suffix:semicolon
r_int
r_int
id|align
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|VM_IOREMAP
)paren
(brace
r_int
id|bit
op_assign
id|fls
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bit
OG
id|IOREMAP_MAX_ORDER
)paren
id|bit
op_assign
id|IOREMAP_MAX_ORDER
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bit
OL
id|PAGE_SHIFT
)paren
id|bit
op_assign
id|PAGE_SHIFT
suffix:semicolon
id|align
op_assign
l_int|1ul
op_lshift
id|bit
suffix:semicolon
)brace
id|addr
op_assign
id|ALIGN
c_func
(paren
id|start
comma
id|align
)paren
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
id|area
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|area
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|area
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|size
)paren
)paren
(brace
id|kfree
(paren
id|area
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We always allocate a guard page.&n;&t; */
id|size
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|vmlist
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
op_amp
id|tmp-&gt;next
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
OL
id|addr
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
op_plus
id|tmp-&gt;size
op_ge
id|addr
)paren
(brace
id|addr
op_assign
id|ALIGN
c_func
(paren
id|tmp-&gt;size
op_plus
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
comma
id|align
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|size
op_plus
id|addr
)paren
OL
id|addr
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|size
op_plus
id|addr
op_le
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
)paren
r_goto
id|found
suffix:semicolon
id|addr
op_assign
id|ALIGN
c_func
(paren
id|tmp-&gt;size
op_plus
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
comma
id|align
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
OG
id|end
op_minus
id|size
)paren
r_goto
id|out
suffix:semicolon
)brace
id|found
suffix:colon
id|area-&gt;next
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|area
suffix:semicolon
id|area-&gt;flags
op_assign
id|flags
suffix:semicolon
id|area-&gt;addr
op_assign
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
id|area-&gt;size
op_assign
id|size
suffix:semicolon
id|area-&gt;pages
op_assign
l_int|NULL
suffix:semicolon
id|area-&gt;nr_pages
op_assign
l_int|0
suffix:semicolon
id|area-&gt;phys_addr
op_assign
l_int|0
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_return
id|area
suffix:semicolon
id|out
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|area
)paren
suffix:semicolon
r_if
c_cond
(paren
id|printk_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;allocation failed: out of vmalloc space - use vmalloc=&lt;size&gt; to increase size.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;get_vm_area  -  reserve a contingous kernel virtual area&n; *&n; *&t;@size:&t;&t;size of the area&n; *&t;@flags:&t;&t;%VM_IOREMAP for I/O mappings or VM_ALLOC&n; *&n; *&t;Search an area of @size in the kernel virtual mapping area,&n; *&t;and reserved it for out purposes.  Returns the area descriptor&n; *&t;on success or %NULL on failure.&n; */
DECL|function|get_vm_area
r_struct
id|vm_struct
op_star
id|get_vm_area
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
(brace
r_return
id|__get_vm_area
c_func
(paren
id|size
comma
id|flags
comma
id|VMALLOC_START
comma
id|VMALLOC_END
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;remove_vm_area  -  find and remove a contingous kernel virtual area&n; *&n; *&t;@addr:&t;&t;base address&n; *&n; *&t;Search for the kernel VM area starting at @addr, and remove it.&n; *&t;This function returns the found VM area, but using it is NOT safe&n; *&t;on SMP machines.&n; */
DECL|function|remove_vm_area
r_struct
id|vm_struct
op_star
id|remove_vm_area
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_struct
id|vm_struct
op_star
op_star
id|p
comma
op_star
id|tmp
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|vmlist
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
op_amp
id|tmp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;addr
op_eq
id|addr
)paren
r_goto
id|found
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
id|found
suffix:colon
id|unmap_vm_area
c_func
(paren
id|tmp
)paren
suffix:semicolon
op_star
id|p
op_assign
id|tmp-&gt;next
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Remove the guard page.&n;&t; */
id|tmp-&gt;size
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|__vunmap
r_void
id|__vunmap
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|deallocate_pages
)paren
(brace
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
(paren
r_int
r_int
)paren
id|addr
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Trying to vfree() bad address (%p)&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|area
op_assign
id|remove_vm_area
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|area
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Trying to vfree() nonexistent vm area (%p)&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|deallocate_pages
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
id|area-&gt;nr_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|area-&gt;pages
(braket
id|i
)braket
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|area-&gt;pages
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|area-&gt;nr_pages
OG
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_struct
id|page
op_star
)paren
)paren
id|vfree
c_func
(paren
id|area-&gt;pages
)paren
suffix:semicolon
r_else
id|kfree
c_func
(paren
id|area-&gt;pages
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|area
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;vfree  -  release memory allocated by vmalloc()&n; *&n; *&t;@addr:&t;&t;memory base address&n; *&n; *&t;Free the virtually contiguous memory area starting at @addr, as&n; *&t;obtained from vmalloc(), vmalloc_32() or __vmalloc().&n; *&n; *&t;May not be called in interrupt context.&n; */
DECL|function|vfree
r_void
id|vfree
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
id|BUG_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
id|__vunmap
c_func
(paren
id|addr
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|vfree
id|EXPORT_SYMBOL
c_func
(paren
id|vfree
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;vunmap  -  release virtual mapping obtained by vmap()&n; *&n; *&t;@addr:&t;&t;memory base address&n; *&n; *&t;Free the virtually contiguous memory area starting at @addr,&n; *&t;which was created from the page array passed to vmap().&n; *&n; *&t;May not be called in interrupt context.&n; */
DECL|function|vunmap
r_void
id|vunmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
id|BUG_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
id|__vunmap
c_func
(paren
id|addr
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|vunmap
id|EXPORT_SYMBOL
c_func
(paren
id|vunmap
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;vmap  -  map an array of pages into virtually contiguous space&n; *&n; *&t;@pages:&t;&t;array of page pointers&n; *&t;@count:&t;&t;number of pages to map&n; *&t;@flags:&t;&t;vm_area-&gt;flags&n; *&t;@prot:&t;&t;page protection for the mapping&n; *&n; *&t;Maps @count pages from @pages into contiguous kernel virtual&n; *&t;space.&n; */
DECL|function|vmap
r_void
op_star
id|vmap
c_func
(paren
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
r_int
id|count
comma
r_int
r_int
id|flags
comma
id|pgprot_t
id|prot
)paren
(brace
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|num_physpages
)paren
r_return
l_int|NULL
suffix:semicolon
id|area
op_assign
id|get_vm_area
c_func
(paren
(paren
id|count
op_lshift
id|PAGE_SHIFT
)paren
comma
id|flags
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
r_if
c_cond
(paren
id|map_vm_area
c_func
(paren
id|area
comma
id|prot
comma
op_amp
id|pages
)paren
)paren
(brace
id|vunmap
c_func
(paren
id|area-&gt;addr
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|area-&gt;addr
suffix:semicolon
)brace
DECL|variable|vmap
id|EXPORT_SYMBOL
c_func
(paren
id|vmap
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;__vmalloc  -  allocate virtually contiguous memory&n; *&n; *&t;@size:&t;&t;allocation size&n; *&t;@gfp_mask:&t;flags for the page level allocator&n; *&t;@prot:&t;&t;protection mask for the allocated pages&n; *&n; *&t;Allocate enough pages to cover @size from the page level&n; *&t;allocator with @gfp_mask flags.  Map them into contiguous&n; *&t;kernel virtual space, using a pagetable protection of @prot.&n; */
DECL|function|__vmalloc
r_void
op_star
id|__vmalloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|gfp_mask
comma
id|pgprot_t
id|prot
)paren
(brace
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
r_int
r_int
id|nr_pages
comma
id|array_size
comma
id|i
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
(paren
id|size
op_rshift
id|PAGE_SHIFT
)paren
OG
id|num_physpages
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
id|VM_ALLOC
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
id|nr_pages
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|array_size
op_assign
(paren
id|nr_pages
op_star
r_sizeof
(paren
r_struct
id|page
op_star
)paren
)paren
suffix:semicolon
id|area-&gt;nr_pages
op_assign
id|nr_pages
suffix:semicolon
multiline_comment|/* Please note that the recursion is strictly bounded. */
r_if
c_cond
(paren
id|array_size
OG
id|PAGE_SIZE
)paren
id|pages
op_assign
id|__vmalloc
c_func
(paren
id|array_size
comma
id|gfp_mask
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
r_else
id|pages
op_assign
id|kmalloc
c_func
(paren
id|array_size
comma
(paren
id|gfp_mask
op_amp
op_complement
id|__GFP_HIGHMEM
)paren
)paren
suffix:semicolon
id|area-&gt;pages
op_assign
id|pages
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area-&gt;pages
)paren
(brace
id|remove_vm_area
c_func
(paren
id|area-&gt;addr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|area
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|area-&gt;pages
comma
l_int|0
comma
id|array_size
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
id|area-&gt;nr_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
id|area-&gt;pages
(braket
id|i
)braket
op_assign
id|alloc_page
c_func
(paren
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|area-&gt;pages
(braket
id|i
)braket
)paren
)paren
(brace
multiline_comment|/* Successfully allocated i pages, free them in __vunmap() */
id|area-&gt;nr_pages
op_assign
id|i
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|map_vm_area
c_func
(paren
id|area
comma
id|prot
comma
op_amp
id|pages
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_return
id|area-&gt;addr
suffix:semicolon
id|fail
suffix:colon
id|vfree
c_func
(paren
id|area-&gt;addr
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|__vmalloc
id|EXPORT_SYMBOL
c_func
(paren
id|__vmalloc
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;vmalloc  -  allocate virtually contiguous memory&n; *&n; *&t;@size:&t;&t;allocation size&n; *&n; *&t;Allocate enough pages to cover @size from the page level&n; *&t;allocator and map them into contiguous kernel virtual space.&n; *&n; *&t;For tight cotrol over page level allocator and protection flags&n; *&t;use __vmalloc() instead.&n; */
DECL|function|vmalloc
r_void
op_star
id|vmalloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_return
id|__vmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
op_or
id|__GFP_HIGHMEM
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
)brace
DECL|variable|vmalloc
id|EXPORT_SYMBOL
c_func
(paren
id|vmalloc
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;vmalloc_exec  -  allocate virtually contiguous, executable memory&n; *&n; *&t;@size:&t;&t;allocation size&n; *&n; *&t;Kernel-internal function to allocate enough pages to cover @size&n; *&t;the page level allocator and map them into contiguous and&n; *&t;executable kernel virtual space.&n; *&n; *&t;For tight cotrol over page level allocator and protection flags&n; *&t;use __vmalloc() instead.&n; */
macro_line|#ifndef PAGE_KERNEL_EXEC
DECL|macro|PAGE_KERNEL_EXEC
macro_line|# define PAGE_KERNEL_EXEC PAGE_KERNEL
macro_line|#endif
DECL|function|vmalloc_exec
r_void
op_star
id|vmalloc_exec
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_return
id|__vmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
op_or
id|__GFP_HIGHMEM
comma
id|PAGE_KERNEL_EXEC
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;vmalloc_32  -  allocate virtually contiguous memory (32bit addressable)&n; *&n; *&t;@size:&t;&t;allocation size&n; *&n; *&t;Allocate enough 32bit PA addressable pages to cover @size from the&n; *&t;page level allocator and map them into contiguous kernel virtual space.&n; */
DECL|function|vmalloc_32
r_void
op_star
id|vmalloc_32
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_return
id|__vmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
comma
id|PAGE_KERNEL
)paren
suffix:semicolon
)brace
DECL|variable|vmalloc_32
id|EXPORT_SYMBOL
c_func
(paren
id|vmalloc_32
)paren
suffix:semicolon
DECL|function|vread
r_int
id|vread
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|vm_struct
op_star
id|tmp
suffix:semicolon
r_char
op_star
id|vaddr
comma
op_star
id|buf_start
op_assign
id|buf
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
multiline_comment|/* Don&squot;t allow overflow */
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|addr
op_plus
id|count
OL
id|count
)paren
id|count
op_assign
op_minus
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|vmlist
suffix:semicolon
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
(brace
id|vaddr
op_assign
(paren
r_char
op_star
)paren
id|tmp-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|vaddr
op_plus
id|tmp-&gt;size
op_minus
id|PAGE_SIZE
)paren
r_continue
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
id|vaddr
)paren
(brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
id|finished
suffix:semicolon
op_star
id|buf
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|addr
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|n
op_assign
id|vaddr
op_plus
id|tmp-&gt;size
op_minus
id|PAGE_SIZE
op_minus
id|addr
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
id|finished
suffix:semicolon
op_star
id|buf
op_assign
op_star
id|addr
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|addr
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|n
OG
l_int|0
)paren
suffix:semicolon
)brace
id|finished
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_return
id|buf
op_minus
id|buf_start
suffix:semicolon
)brace
DECL|function|vwrite
r_int
id|vwrite
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|vm_struct
op_star
id|tmp
suffix:semicolon
r_char
op_star
id|vaddr
comma
op_star
id|buf_start
op_assign
id|buf
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
multiline_comment|/* Don&squot;t allow overflow */
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|addr
op_plus
id|count
OL
id|count
)paren
id|count
op_assign
op_minus
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|vmlist
suffix:semicolon
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
(brace
id|vaddr
op_assign
(paren
r_char
op_star
)paren
id|tmp-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|vaddr
op_plus
id|tmp-&gt;size
op_minus
id|PAGE_SIZE
)paren
r_continue
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
id|vaddr
)paren
(brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
id|finished
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|addr
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|n
op_assign
id|vaddr
op_plus
id|tmp-&gt;size
op_minus
id|PAGE_SIZE
op_minus
id|addr
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
id|finished
suffix:semicolon
op_star
id|addr
op_assign
op_star
id|buf
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|addr
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|n
OG
l_int|0
)paren
suffix:semicolon
)brace
id|finished
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_return
id|buf
op_minus
id|buf_start
suffix:semicolon
)brace
eof
