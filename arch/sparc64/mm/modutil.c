multiline_comment|/*  $Id: modutil.c,v 1.9 2001/08/14 22:10:56 davem Exp $&n; *  arch/sparc64/mm/modutil.c&n; *&n; *  Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *  Based upon code written by Linus Torvalds and others.&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|MODULES_VADDR
mdefine_line|#define  MODULES_VADDR&t;0x0000000001000000ULL  /* Where to map modules */
DECL|macro|MODULES_LEN
mdefine_line|#define  MODULES_LEN&t;0x000000007f000000ULL
DECL|macro|MODULES_END
mdefine_line|#define  MODULES_END&t;0x0000000080000000ULL
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
id|vmfree_area_pages
c_func
(paren
id|VMALLOC_VMADDR
c_func
(paren
id|tmp-&gt;addr
)paren
comma
id|tmp-&gt;size
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
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
r_void
op_star
id|addr
suffix:semicolon
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
op_star
id|p
op_assign
id|area
suffix:semicolon
r_if
c_cond
(paren
id|vmalloc_area_pages
c_func
(paren
id|VMALLOC_VMADDR
c_func
(paren
id|addr
)paren
comma
id|size
comma
id|GFP_KERNEL
comma
id|PAGE_KERNEL
)paren
)paren
(brace
id|module_unmap
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
eof
