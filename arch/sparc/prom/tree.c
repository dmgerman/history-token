multiline_comment|/* $Id: tree.c,v 1.26 2000/08/26 02:38:03 anton Exp $&n; * tree.c: Basic device tree traversal/scanning for the Linux&n; *         prom library.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
DECL|macro|PROMLIB_INTERNAL
mdefine_line|#define PROMLIB_INTERNAL
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
r_extern
r_void
id|restore_current
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|promlib_buf
r_static
r_char
id|promlib_buf
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* Internal version of prom_getchild that does not alter return values. */
DECL|function|__prom_getchild
r_int
id|__prom_getchild
c_func
(paren
r_int
id|node
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|cnode
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
id|cnode
op_assign
id|prom_nodeops
op_member_access_from_pointer
id|no_child
c_func
(paren
id|node
)paren
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|cnode
suffix:semicolon
)brace
multiline_comment|/* Return the child of node &squot;node&squot; or zero if no this node has no&n; * direct descendent.&n; */
DECL|function|prom_getchild
r_int
id|prom_getchild
c_func
(paren
r_int
id|node
)paren
(brace
r_int
id|cnode
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|cnode
op_assign
id|__prom_getchild
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cnode
op_eq
l_int|0
op_logical_or
id|cnode
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|cnode
suffix:semicolon
)brace
multiline_comment|/* Internal version of prom_getsibling that does not alter return values. */
DECL|function|__prom_getsibling
r_int
id|__prom_getsibling
c_func
(paren
r_int
id|node
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|cnode
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
id|cnode
op_assign
id|prom_nodeops
op_member_access_from_pointer
id|no_nextnode
c_func
(paren
id|node
)paren
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|cnode
suffix:semicolon
)brace
multiline_comment|/* Return the next sibling of node &squot;node&squot; or zero if no more siblings&n; * at this level of depth in the tree.&n; */
DECL|function|prom_getsibling
r_int
id|prom_getsibling
c_func
(paren
r_int
id|node
)paren
(brace
r_int
id|sibnode
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|sibnode
op_assign
id|__prom_getsibling
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sibnode
op_eq
l_int|0
op_logical_or
id|sibnode
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|sibnode
suffix:semicolon
)brace
multiline_comment|/* Return the length in bytes of property &squot;prop&squot; at node &squot;node&squot;.&n; * Return -1 on error.&n; */
DECL|function|prom_getproplen
r_int
id|prom_getproplen
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|prop
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|node
)paren
op_logical_or
(paren
op_logical_neg
id|prop
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|prom_nodeops
op_member_access_from_pointer
id|no_proplen
c_func
(paren
id|node
comma
id|prop
)paren
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Acquire a property &squot;prop&squot; at node &squot;node&squot; and place it in&n; * &squot;buffer&squot; which has a size of &squot;bufsize&squot;.  If the acquisition&n; * was successful the length will be returned, else -1 is returned.&n; */
DECL|function|prom_getproperty
r_int
id|prom_getproperty
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|prop
comma
r_char
op_star
id|buffer
comma
r_int
id|bufsize
)paren
(brace
r_int
id|plen
comma
id|ret
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|plen
op_assign
id|prom_getproplen
c_func
(paren
id|node
comma
id|prop
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|plen
OG
id|bufsize
)paren
op_logical_or
(paren
id|plen
op_eq
l_int|0
)paren
op_logical_or
(paren
id|plen
op_eq
op_minus
l_int|1
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Ok, things seem all right. */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|prom_nodeops
op_member_access_from_pointer
id|no_getprop
c_func
(paren
id|node
comma
id|prop
comma
id|buffer
)paren
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Acquire an integer property and return its value.  Returns -1&n; * on failure.&n; */
DECL|function|prom_getint
r_int
id|prom_getint
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|prop
)paren
(brace
r_static
r_int
id|intprop
suffix:semicolon
r_if
c_cond
(paren
id|prom_getproperty
c_func
(paren
id|node
comma
id|prop
comma
(paren
r_char
op_star
)paren
op_amp
id|intprop
comma
r_sizeof
(paren
r_int
)paren
)paren
op_ne
op_minus
l_int|1
)paren
(brace
r_return
id|intprop
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Acquire an integer property, upon error return the passed default&n; * integer.&n; */
DECL|function|prom_getintdefault
r_int
id|prom_getintdefault
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|property
comma
r_int
id|deflt
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|prom_getint
c_func
(paren
id|node
comma
id|property
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
op_minus
l_int|1
)paren
(brace
r_return
id|deflt
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Acquire a boolean property, 1=TRUE 0=FALSE. */
DECL|function|prom_getbool
r_int
id|prom_getbool
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|prop
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|prom_getproplen
c_func
(paren
id|node
comma
id|prop
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
op_minus
l_int|1
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Acquire a property whose value is a string, returns a null&n; * string on error.  The char pointer is the user supplied string&n; * buffer.&n; */
DECL|function|prom_getstring
r_void
id|prom_getstring
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|prop
comma
r_char
op_star
id|user_buf
comma
r_int
id|ubuf_size
)paren
(brace
r_int
id|len
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
id|prop
comma
id|user_buf
comma
id|ubuf_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
op_minus
l_int|1
)paren
(brace
r_return
suffix:semicolon
)brace
id|user_buf
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Does the device at node &squot;node&squot; have name &squot;name&squot;?&n; * YES = 1   NO = 0&n; */
DECL|function|prom_nodematch
r_int
id|prom_nodematch
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|name
)paren
(brace
r_int
id|error
suffix:semicolon
r_static
r_char
id|namebuf
(braket
l_int|128
)braket
suffix:semicolon
id|error
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;name&quot;
comma
id|namebuf
comma
r_sizeof
(paren
id|namebuf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|namebuf
comma
id|name
)paren
op_eq
l_int|0
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Search siblings at &squot;node_start&squot; for a node with name&n; * &squot;nodename&squot;.  Return node if successful, zero if not.&n; */
DECL|function|prom_searchsiblings
r_int
id|prom_searchsiblings
c_func
(paren
r_int
id|node_start
comma
r_char
op_star
id|nodename
)paren
(brace
r_int
id|thisnode
comma
id|error
suffix:semicolon
r_for
c_loop
(paren
id|thisnode
op_assign
id|node_start
suffix:semicolon
id|thisnode
suffix:semicolon
id|thisnode
op_assign
id|prom_getsibling
c_func
(paren
id|thisnode
)paren
)paren
(brace
id|error
op_assign
id|prom_getproperty
c_func
(paren
id|thisnode
comma
l_string|&quot;name&quot;
comma
id|promlib_buf
comma
r_sizeof
(paren
id|promlib_buf
)paren
)paren
suffix:semicolon
multiline_comment|/* Should this ever happen? */
r_if
c_cond
(paren
id|error
op_eq
op_minus
l_int|1
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|nodename
comma
id|promlib_buf
)paren
op_eq
l_int|0
)paren
(brace
r_return
id|thisnode
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Gets name in the form prom v2+ uses it (name@x,yyyyy or name (if no reg)) */
DECL|function|prom_getname
r_int
id|prom_getname
(paren
r_int
id|node
comma
r_char
op_star
id|buffer
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|linux_prom_registers
id|reg
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
id|i
op_assign
id|prom_getproperty
(paren
id|node
comma
l_string|&quot;name&quot;
comma
id|buffer
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_le
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|buffer
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|len
op_sub_assign
id|i
suffix:semicolon
id|i
op_assign
id|prom_getproperty
(paren
id|node
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
id|reg
comma
r_sizeof
(paren
id|reg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|11
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|buffer
op_assign
id|strchr
(paren
id|buffer
comma
l_int|0
)paren
suffix:semicolon
id|sprintf
(paren
id|buffer
comma
l_string|&quot;@%x,%x&quot;
comma
id|reg
(braket
l_int|0
)braket
dot
id|which_io
comma
(paren
id|uint
)paren
id|reg
(braket
l_int|0
)braket
dot
id|phys_addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Interal version of nextprop that does not alter return values. */
DECL|function|__prom_nextprop
r_char
op_star
id|__prom_nextprop
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|oprop
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_char
op_star
id|prop
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
id|prop
op_assign
id|prom_nodeops
op_member_access_from_pointer
id|no_nextprop
c_func
(paren
id|node
comma
id|oprop
)paren
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|prop
suffix:semicolon
)brace
multiline_comment|/* Return the first property name for node &squot;node&squot;. */
multiline_comment|/* buffer is unused argument, but as v9 uses it, we need to have the same interface */
DECL|function|prom_firstprop
r_char
op_star
id|prom_firstprop
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|bufer
)paren
(brace
r_if
c_cond
(paren
id|node
op_eq
l_int|0
op_logical_or
id|node
op_eq
op_minus
l_int|1
)paren
r_return
l_string|&quot;&quot;
suffix:semicolon
r_return
id|__prom_nextprop
c_func
(paren
id|node
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Return the property type string after property type &squot;oprop&squot;&n; * at node &squot;node&squot; .  Returns empty string if no more&n; * property types for this node.&n; */
DECL|function|prom_nextprop
r_char
op_star
id|prom_nextprop
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|oprop
comma
r_char
op_star
id|buffer
)paren
(brace
r_if
c_cond
(paren
id|node
op_eq
l_int|0
op_logical_or
id|node
op_eq
op_minus
l_int|1
)paren
r_return
l_string|&quot;&quot;
suffix:semicolon
r_return
id|__prom_nextprop
c_func
(paren
id|node
comma
id|oprop
)paren
suffix:semicolon
)brace
DECL|function|prom_finddevice
r_int
id|prom_finddevice
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_char
id|nbuf
(braket
l_int|128
)braket
suffix:semicolon
r_char
op_star
id|s
op_assign
id|name
comma
op_star
id|d
suffix:semicolon
r_int
id|node
op_assign
id|prom_root_node
comma
id|node2
suffix:semicolon
r_int
r_int
id|which_io
comma
id|phys_addr
suffix:semicolon
r_struct
id|linux_prom_registers
id|reg
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
r_while
c_loop
(paren
op_star
id|s
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|s
)paren
r_return
id|node
suffix:semicolon
multiline_comment|/* path &squot;.../&squot; is legal */
id|node
op_assign
id|prom_getchild
c_func
(paren
id|node
)paren
suffix:semicolon
r_for
c_loop
(paren
id|d
op_assign
id|nbuf
suffix:semicolon
op_star
id|s
op_ne
l_int|0
op_logical_and
op_star
id|s
op_ne
l_char|&squot;@&squot;
op_logical_and
op_star
id|s
op_ne
l_char|&squot;/&squot;
suffix:semicolon
)paren
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
op_star
id|d
op_assign
l_int|0
suffix:semicolon
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
id|nbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;@&squot;
)paren
(brace
r_if
c_cond
(paren
id|isxdigit
c_func
(paren
id|s
(braket
l_int|1
)braket
)paren
op_logical_and
id|s
(braket
l_int|2
)braket
op_eq
l_char|&squot;,&squot;
)paren
(brace
id|which_io
op_assign
id|simple_strtoul
c_func
(paren
id|s
op_plus
l_int|1
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
id|phys_addr
op_assign
id|simple_strtoul
c_func
(paren
id|s
op_plus
l_int|3
comma
op_amp
id|d
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d
op_ne
id|s
op_plus
l_int|3
op_logical_and
(paren
op_logical_neg
op_star
id|d
op_logical_or
op_star
id|d
op_eq
l_char|&squot;/&squot;
)paren
op_logical_and
id|d
op_le
id|s
op_plus
l_int|3
op_plus
l_int|8
)paren
(brace
id|node2
op_assign
id|node
suffix:semicolon
r_while
c_loop
(paren
id|node2
op_logical_and
id|node2
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|prom_getproperty
(paren
id|node2
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
id|reg
comma
r_sizeof
(paren
id|reg
)paren
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|which_io
op_eq
id|reg
(braket
l_int|0
)braket
dot
id|which_io
op_logical_and
id|phys_addr
op_eq
id|reg
(braket
l_int|0
)braket
dot
id|phys_addr
)paren
(brace
id|node
op_assign
id|node2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|node2
op_assign
id|prom_getsibling
c_func
(paren
id|node2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node2
op_logical_or
id|node2
op_eq
op_minus
l_int|1
)paren
r_break
suffix:semicolon
id|node2
op_assign
id|prom_searchsiblings
c_func
(paren
id|prom_getsibling
c_func
(paren
id|node2
)paren
comma
id|nbuf
)paren
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
op_star
id|s
op_ne
l_int|0
op_logical_and
op_star
id|s
op_ne
l_char|&squot;/&squot;
)paren
id|s
op_increment
suffix:semicolon
)brace
)brace
r_return
id|node
suffix:semicolon
)brace
DECL|function|prom_node_has_property
r_int
id|prom_node_has_property
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|prop
)paren
(brace
r_char
op_star
id|current_property
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_do
(brace
id|current_property
op_assign
id|prom_nextprop
c_func
(paren
id|node
comma
id|current_property
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|current_property
comma
id|prop
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_star
id|current_property
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set property &squot;pname&squot; at node &squot;node&squot; to value &squot;value&squot; which has a length&n; * of &squot;size&squot; bytes.  Return the number of bytes the prom accepted.&n; */
DECL|function|prom_setprop
r_int
id|prom_setprop
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|pname
comma
r_char
op_star
id|value
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pname
op_eq
l_int|0
)paren
op_logical_or
(paren
id|value
op_eq
l_int|0
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|prom_nodeops
op_member_access_from_pointer
id|no_setprop
c_func
(paren
id|node
comma
id|pname
comma
id|value
comma
id|size
)paren
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|prom_inst2pkg
r_int
id|prom_inst2pkg
c_func
(paren
r_int
id|inst
)paren
(brace
r_int
id|node
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
id|node
op_assign
(paren
op_star
id|romvec-&gt;pv_v2devops.v2_inst2pkg
)paren
(paren
id|inst
)paren
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|node
suffix:semicolon
)brace
multiline_comment|/* Return &squot;node&squot; assigned to a particular prom &squot;path&squot;&n; * FIXME: Should work for v0 as well&n; */
DECL|function|prom_pathtoinode
r_int
id|prom_pathtoinode
c_func
(paren
r_char
op_star
id|path
)paren
(brace
r_int
id|node
comma
id|inst
suffix:semicolon
id|inst
op_assign
id|prom_devopen
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inst
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|node
op_assign
id|prom_inst2pkg
(paren
id|inst
)paren
suffix:semicolon
id|prom_devclose
(paren
id|inst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|node
suffix:semicolon
)brace
eof
