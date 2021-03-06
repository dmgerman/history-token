multiline_comment|/*&n; * Implementation of the extensible bitmap type.&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &quot;ebitmap.h&quot;
macro_line|#include &quot;policydb.h&quot;
DECL|function|ebitmap_cmp
r_int
id|ebitmap_cmp
c_func
(paren
r_struct
id|ebitmap
op_star
id|e1
comma
r_struct
id|ebitmap
op_star
id|e2
)paren
(brace
r_struct
id|ebitmap_node
op_star
id|n1
comma
op_star
id|n2
suffix:semicolon
r_if
c_cond
(paren
id|e1-&gt;highbit
op_ne
id|e2-&gt;highbit
)paren
r_return
l_int|0
suffix:semicolon
id|n1
op_assign
id|e1-&gt;node
suffix:semicolon
id|n2
op_assign
id|e2-&gt;node
suffix:semicolon
r_while
c_loop
(paren
id|n1
op_logical_and
id|n2
op_logical_and
(paren
id|n1-&gt;startbit
op_eq
id|n2-&gt;startbit
)paren
op_logical_and
(paren
id|n1-&gt;map
op_eq
id|n2-&gt;map
)paren
)paren
(brace
id|n1
op_assign
id|n1-&gt;next
suffix:semicolon
id|n2
op_assign
id|n2-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n1
op_logical_or
id|n2
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ebitmap_cpy
r_int
id|ebitmap_cpy
c_func
(paren
r_struct
id|ebitmap
op_star
id|dst
comma
r_struct
id|ebitmap
op_star
id|src
)paren
(brace
r_struct
id|ebitmap_node
op_star
id|n
comma
op_star
r_new
comma
op_star
id|prev
suffix:semicolon
id|ebitmap_init
c_func
(paren
id|dst
)paren
suffix:semicolon
id|n
op_assign
id|src-&gt;node
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|n
)paren
(brace
r_new
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
r_new
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
(brace
id|ebitmap_destroy
c_func
(paren
id|dst
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
op_star
r_new
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|startbit
op_assign
id|n-&gt;startbit
suffix:semicolon
r_new
op_member_access_from_pointer
id|map
op_assign
id|n-&gt;map
suffix:semicolon
r_new
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;next
op_assign
r_new
suffix:semicolon
r_else
id|dst-&gt;node
op_assign
r_new
suffix:semicolon
id|prev
op_assign
r_new
suffix:semicolon
id|n
op_assign
id|n-&gt;next
suffix:semicolon
)brace
id|dst-&gt;highbit
op_assign
id|src-&gt;highbit
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ebitmap_contains
r_int
id|ebitmap_contains
c_func
(paren
r_struct
id|ebitmap
op_star
id|e1
comma
r_struct
id|ebitmap
op_star
id|e2
)paren
(brace
r_struct
id|ebitmap_node
op_star
id|n1
comma
op_star
id|n2
suffix:semicolon
r_if
c_cond
(paren
id|e1-&gt;highbit
OL
id|e2-&gt;highbit
)paren
r_return
l_int|0
suffix:semicolon
id|n1
op_assign
id|e1-&gt;node
suffix:semicolon
id|n2
op_assign
id|e2-&gt;node
suffix:semicolon
r_while
c_loop
(paren
id|n1
op_logical_and
id|n2
op_logical_and
(paren
id|n1-&gt;startbit
op_le
id|n2-&gt;startbit
)paren
)paren
(brace
r_if
c_cond
(paren
id|n1-&gt;startbit
OL
id|n2-&gt;startbit
)paren
(brace
id|n1
op_assign
id|n1-&gt;next
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|n1-&gt;map
op_amp
id|n2-&gt;map
)paren
op_ne
id|n2-&gt;map
)paren
r_return
l_int|0
suffix:semicolon
id|n1
op_assign
id|n1-&gt;next
suffix:semicolon
id|n2
op_assign
id|n2-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n2
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ebitmap_get_bit
r_int
id|ebitmap_get_bit
c_func
(paren
r_struct
id|ebitmap
op_star
id|e
comma
r_int
r_int
id|bit
)paren
(brace
r_struct
id|ebitmap_node
op_star
id|n
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;highbit
OL
id|bit
)paren
r_return
l_int|0
suffix:semicolon
id|n
op_assign
id|e-&gt;node
suffix:semicolon
r_while
c_loop
(paren
id|n
op_logical_and
(paren
id|n-&gt;startbit
op_le
id|bit
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|n-&gt;startbit
op_plus
id|MAPSIZE
)paren
OG
id|bit
)paren
(brace
r_if
c_cond
(paren
id|n-&gt;map
op_amp
(paren
id|MAPBIT
op_lshift
(paren
id|bit
op_minus
id|n-&gt;startbit
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
id|n
op_assign
id|n-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ebitmap_set_bit
r_int
id|ebitmap_set_bit
c_func
(paren
r_struct
id|ebitmap
op_star
id|e
comma
r_int
r_int
id|bit
comma
r_int
id|value
)paren
(brace
r_struct
id|ebitmap_node
op_star
id|n
comma
op_star
id|prev
comma
op_star
r_new
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|n
op_assign
id|e-&gt;node
suffix:semicolon
r_while
c_loop
(paren
id|n
op_logical_and
id|n-&gt;startbit
op_le
id|bit
)paren
(brace
r_if
c_cond
(paren
(paren
id|n-&gt;startbit
op_plus
id|MAPSIZE
)paren
OG
id|bit
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
(brace
id|n-&gt;map
op_or_assign
(paren
id|MAPBIT
op_lshift
(paren
id|bit
op_minus
id|n-&gt;startbit
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|n-&gt;map
op_and_assign
op_complement
(paren
id|MAPBIT
op_lshift
(paren
id|bit
op_minus
id|n-&gt;startbit
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n-&gt;map
)paren
(brace
multiline_comment|/* drop this node from the bitmap */
r_if
c_cond
(paren
op_logical_neg
id|n-&gt;next
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t; * this was the highest map&n;&t;&t;&t;&t;&t;&t; * within the bitmap&n;&t;&t;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|prev
)paren
id|e-&gt;highbit
op_assign
id|prev-&gt;startbit
op_plus
id|MAPSIZE
suffix:semicolon
r_else
id|e-&gt;highbit
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;next
op_assign
id|n-&gt;next
suffix:semicolon
r_else
id|e-&gt;node
op_assign
id|n-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|prev
op_assign
id|n
suffix:semicolon
id|n
op_assign
id|n-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
l_int|0
suffix:semicolon
r_new
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
r_new
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
op_star
r_new
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|startbit
op_assign
id|bit
op_amp
op_complement
(paren
id|MAPSIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|map
op_assign
(paren
id|MAPBIT
op_lshift
(paren
id|bit
op_minus
r_new
op_member_access_from_pointer
id|startbit
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
multiline_comment|/* this node will be the highest map within the bitmap */
id|e-&gt;highbit
op_assign
r_new
op_member_access_from_pointer
id|startbit
op_plus
id|MAPSIZE
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
(brace
r_new
op_member_access_from_pointer
id|next
op_assign
id|prev-&gt;next
suffix:semicolon
id|prev-&gt;next
op_assign
r_new
suffix:semicolon
)brace
r_else
(brace
r_new
op_member_access_from_pointer
id|next
op_assign
id|e-&gt;node
suffix:semicolon
id|e-&gt;node
op_assign
r_new
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ebitmap_destroy
r_void
id|ebitmap_destroy
c_func
(paren
r_struct
id|ebitmap
op_star
id|e
)paren
(brace
r_struct
id|ebitmap_node
op_star
id|n
comma
op_star
id|temp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e
)paren
r_return
suffix:semicolon
id|n
op_assign
id|e-&gt;node
suffix:semicolon
r_while
c_loop
(paren
id|n
)paren
(brace
id|temp
op_assign
id|n
suffix:semicolon
id|n
op_assign
id|n-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|temp
)paren
suffix:semicolon
)brace
id|e-&gt;highbit
op_assign
l_int|0
suffix:semicolon
id|e-&gt;node
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|ebitmap_read
r_int
id|ebitmap_read
c_func
(paren
r_struct
id|ebitmap
op_star
id|e
comma
r_void
op_star
id|fp
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|ebitmap_node
op_star
id|n
comma
op_star
id|l
suffix:semicolon
id|u32
id|buf
(braket
l_int|3
)braket
comma
id|mapsize
comma
id|count
comma
id|i
suffix:semicolon
id|u64
id|map
suffix:semicolon
id|ebitmap_init
c_func
(paren
id|e
)paren
suffix:semicolon
id|rc
op_assign
id|next_entry
c_func
(paren
id|buf
comma
id|fp
comma
r_sizeof
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|mapsize
op_assign
id|le32_to_cpu
c_func
(paren
id|buf
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|e-&gt;highbit
op_assign
id|le32_to_cpu
c_func
(paren
id|buf
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|count
op_assign
id|le32_to_cpu
c_func
(paren
id|buf
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapsize
op_ne
id|MAPSIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;security: ebitmap: map size %u does not &quot;
l_string|&quot;match my size %Zd (high bit was %d)&bslash;n&quot;
comma
id|mapsize
comma
id|MAPSIZE
comma
id|e-&gt;highbit
)paren
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|e-&gt;highbit
)paren
(brace
id|e-&gt;node
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|ok
suffix:semicolon
)brace
r_if
c_cond
(paren
id|e-&gt;highbit
op_amp
(paren
id|MAPSIZE
op_minus
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;security: ebitmap: high bit (%d) is not a &quot;
l_string|&quot;multiple of the map size (%Zd)&bslash;n&quot;
comma
id|e-&gt;highbit
comma
id|MAPSIZE
)paren
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|l
op_assign
l_int|NULL
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rc
op_assign
id|next_entry
c_func
(paren
id|buf
comma
id|fp
comma
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;security: ebitmap: truncated map&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|n
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|n
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;security: ebitmap: out of memory&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|bad
suffix:semicolon
)brace
id|memset
c_func
(paren
id|n
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|n
)paren
)paren
suffix:semicolon
id|n-&gt;startbit
op_assign
id|le32_to_cpu
c_func
(paren
id|buf
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n-&gt;startbit
op_amp
(paren
id|MAPSIZE
op_minus
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;security: ebitmap start bit (%d) is &quot;
l_string|&quot;not a multiple of the map size (%Zd)&bslash;n&quot;
comma
id|n-&gt;startbit
comma
id|MAPSIZE
)paren
suffix:semicolon
r_goto
id|bad_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n-&gt;startbit
OG
(paren
id|e-&gt;highbit
op_minus
id|MAPSIZE
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;security: ebitmap start bit (%d) is &quot;
l_string|&quot;beyond the end of the bitmap (%Zd)&bslash;n&quot;
comma
id|n-&gt;startbit
comma
(paren
id|e-&gt;highbit
op_minus
id|MAPSIZE
)paren
)paren
suffix:semicolon
r_goto
id|bad_free
suffix:semicolon
)brace
id|rc
op_assign
id|next_entry
c_func
(paren
op_amp
id|map
comma
id|fp
comma
r_sizeof
(paren
id|u64
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;security: ebitmap: truncated map&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bad_free
suffix:semicolon
)brace
id|n-&gt;map
op_assign
id|le64_to_cpu
c_func
(paren
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n-&gt;map
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;security: ebitmap: null map in &quot;
l_string|&quot;ebitmap (startbit %d)&bslash;n&quot;
comma
id|n-&gt;startbit
)paren
suffix:semicolon
r_goto
id|bad_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|l
)paren
(brace
r_if
c_cond
(paren
id|n-&gt;startbit
op_le
id|l-&gt;startbit
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;security: ebitmap: start &quot;
l_string|&quot;bit %d comes after start bit %d&bslash;n&quot;
comma
id|n-&gt;startbit
comma
id|l-&gt;startbit
)paren
suffix:semicolon
r_goto
id|bad_free
suffix:semicolon
)brace
id|l-&gt;next
op_assign
id|n
suffix:semicolon
)brace
r_else
id|e-&gt;node
op_assign
id|n
suffix:semicolon
id|l
op_assign
id|n
suffix:semicolon
)brace
id|ok
suffix:colon
id|rc
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|bad_free
suffix:colon
id|kfree
c_func
(paren
id|n
)paren
suffix:semicolon
id|bad
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|ebitmap_destroy
c_func
(paren
id|e
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
eof
