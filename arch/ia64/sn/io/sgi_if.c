multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997,2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/pci/bridge.h&gt;
macro_line|#include &lt;asm/sn/ioerror_handling.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/slotnum.h&gt;
r_void
op_star
DECL|function|snia_kmem_zalloc
id|snia_kmem_zalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flag
)paren
(brace
r_void
op_star
id|ptr
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
id|BZERO
c_func
(paren
id|ptr
comma
id|size
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
r_void
DECL|function|snia_kmem_free
id|snia_kmem_free
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * the alloc/free_node routines do a simple kmalloc for now ..&n; */
r_void
op_star
DECL|function|snia_kmem_alloc_node
id|snia_kmem_alloc_node
c_func
(paren
r_register
r_int
id|size
comma
r_register
r_int
id|flags
comma
id|cnodeid_t
id|node
)paren
(brace
multiline_comment|/* someday will Allocate on node &squot;node&squot; */
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_void
op_star
DECL|function|snia_kmem_zalloc_node
id|snia_kmem_zalloc_node
c_func
(paren
r_register
r_int
id|size
comma
r_register
r_int
id|flags
comma
id|cnodeid_t
id|node
)paren
(brace
r_void
op_star
id|ptr
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
id|BZERO
c_func
(paren
id|ptr
comma
id|size
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
multiline_comment|/*&n; * print_register() allows formatted printing of bit fields.  individual&n; * bit fields are described by a struct reg_desc, multiple bit fields within&n; * a single word can be described by multiple reg_desc structures.&n; * %r outputs a string of the format &quot;&lt;bit field descriptions&gt;&quot;&n; * %R outputs a string of the format &quot;0x%x&lt;bit field descriptions&gt;&quot;&n; *&n; * The fields in a reg_desc are:&n; *&t;unsigned long long rd_mask; An appropriate mask to isolate the bit field&n; *&t;&t;&t;&t;within a word, and&squot;ed with val&n; *&n; *&t;int rd_shift;&t;&t;A shift amount to be done to the isolated&n; *&t;&t;&t;&t;bit field.  done before printing the isolate&n; *&t;&t;&t;&t;bit field with rd_format and before searching&n; *&t;&t;&t;&t;for symbolic value names in rd_values&n; *&n; *&t;char *rd_name;&t;&t;If non-null, a bit field name to label any&n; *&t;&t;&t;&t;out from rd_format or searching rd_values.&n; *&t;&t;&t;&t;if neither rd_format or rd_values is non-null&n; *&t;&t;&t;&t;rd_name is printed only if the isolated&n; *&t;&t;&t;&t;bit field is non-null.&n; *&n; *&t;char *rd_format;&t;If non-null, the shifted bit field value&n; *&t;&t;&t;&t;is printed using this format.&n; *&n; *&t;struct reg_values *rd_values;&t;If non-null, a pointer to a table&n; *&t;&t;&t;&t;matching numeric values with symbolic names.&n; *&t;&t;&t;&t;rd_values are searched and the symbolic&n; *&t;&t;&t;&t;value is printed if a match is found, if no&n; *&t;&t;&t;&t;match is found &quot;???&quot; is printed.&n; *&t;&t;&t;&t;&n; */
r_void
DECL|function|print_register
id|print_register
c_func
(paren
r_int
r_int
r_int
id|reg
comma
r_struct
id|reg_desc
op_star
id|addr
)paren
(brace
r_register
r_struct
id|reg_desc
op_star
id|rd
suffix:semicolon
r_register
r_struct
id|reg_values
op_star
id|rv
suffix:semicolon
r_int
r_int
r_int
id|field
suffix:semicolon
r_int
id|any
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&lt;&quot;
)paren
suffix:semicolon
id|any
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|rd
op_assign
id|addr
suffix:semicolon
id|rd-&gt;rd_mask
suffix:semicolon
id|rd
op_increment
)paren
(brace
id|field
op_assign
id|reg
op_amp
id|rd-&gt;rd_mask
suffix:semicolon
id|field
op_assign
(paren
id|rd-&gt;rd_shift
OG
l_int|0
)paren
ques
c_cond
id|field
op_lshift
id|rd-&gt;rd_shift
suffix:colon
id|field
op_rshift
op_minus
id|rd-&gt;rd_shift
suffix:semicolon
r_if
c_cond
(paren
id|any
op_logical_and
(paren
id|rd-&gt;rd_format
op_logical_or
id|rd-&gt;rd_values
op_logical_or
(paren
id|rd-&gt;rd_name
op_logical_and
id|field
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;,&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rd-&gt;rd_name
)paren
(brace
r_if
c_cond
(paren
id|rd-&gt;rd_format
op_logical_or
id|rd-&gt;rd_values
op_logical_or
id|field
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|rd-&gt;rd_name
)paren
suffix:semicolon
id|any
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rd-&gt;rd_format
op_logical_or
id|rd-&gt;rd_values
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;=&quot;
)paren
suffix:semicolon
id|any
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* You can have any format so long as it is %x */
r_if
c_cond
(paren
id|rd-&gt;rd_format
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%llx&quot;
comma
id|field
)paren
suffix:semicolon
id|any
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|rd-&gt;rd_values
)paren
id|printk
c_func
(paren
l_string|&quot;:&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rd-&gt;rd_values
)paren
(brace
id|any
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|rv
op_assign
id|rd-&gt;rd_values
suffix:semicolon
id|rv-&gt;rv_name
suffix:semicolon
id|rv
op_increment
)paren
(brace
r_if
c_cond
(paren
id|field
op_eq
id|rv-&gt;rv_value
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|rv-&gt;rv_name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|rv-&gt;rv_name
op_eq
l_int|NULL
)paren
id|printk
c_func
(paren
l_string|&quot;???&quot;
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
