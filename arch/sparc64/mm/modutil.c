multiline_comment|/*  $Id: modutil.c,v 1.11 2001/12/05 06:05:35 davem Exp $&n; *  arch/sparc64/mm/modutil.c&n; *&n; *  Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *  Based upon code written by Linus Torvalds and others.&n; */
macro_line|#warning &quot;major untested changes to this file  --hch (2002/08/05)&quot;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|variable|modvmlist
r_static
r_struct
id|vm_struct
op_star
id|modvmlist
op_assign
l_int|NULL
suffix:semicolon
DECL|function|module_unmap
r_void
id|module_unmap
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
r_int
id|i
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
l_string|&quot;Trying to unmap module with bad address (%p)&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|modvmlist
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|p
)paren
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
(brace
op_star
id|p
op_assign
id|tmp-&gt;next
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to unmap nonexistent module vm area (%p)&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
id|found
suffix:colon
id|unmap_vm_area
c_func
(paren
id|tmp
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
id|tmp-&gt;nr_pages
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
id|tmp-&gt;pages
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
id|tmp-&gt;pages
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|tmp-&gt;pages
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
DECL|function|module_map
r_void
op_star
id|module_map
(paren
r_int
r_int
id|size
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
r_void
op_star
id|addr
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
id|size
OG
id|MODULES_LEN
)paren
r_return
l_int|NULL
suffix:semicolon
id|addr
op_assign
(paren
r_void
op_star
)paren
id|MODULES_VADDR
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|modvmlist
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|p
)paren
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
id|size
op_plus
(paren
r_int
r_int
)paren
id|addr
OL
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
)paren
r_break
suffix:semicolon
id|addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|tmp-&gt;size
op_plus
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|addr
op_plus
id|size
op_ge
id|MODULES_END
)paren
r_return
l_int|NULL
suffix:semicolon
id|area
op_assign
(paren
r_struct
id|vm_struct
op_star
)paren
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
op_logical_neg
id|area
)paren
r_return
l_int|NULL
suffix:semicolon
id|area-&gt;size
op_assign
id|size
op_plus
id|PAGE_SIZE
suffix:semicolon
id|area-&gt;addr
op_assign
id|addr
suffix:semicolon
id|area-&gt;next
op_assign
op_star
id|p
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
op_star
id|p
op_assign
id|area
suffix:semicolon
id|nr_pages
op_assign
(paren
id|size
op_plus
id|PAGE_SIZE
)paren
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
id|area-&gt;pages
op_assign
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
r_if
c_cond
(paren
op_logical_neg
id|area-&gt;pages
)paren
r_return
l_int|NULL
suffix:semicolon
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
r_goto
id|fail
suffix:semicolon
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
)brace
eof
