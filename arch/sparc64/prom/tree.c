multiline_comment|/* $Id: tree.c,v 1.10 1998/01/10 22:39:00 ecd Exp $&n; * tree.c: Basic device tree traversal/scanning for the Linux&n; *         prom library.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
multiline_comment|/* Return the child of node &squot;node&squot; or zero if no this node has no&n; * direct descendent.&n; */
id|__inline__
r_int
DECL|function|__prom_getchild
id|__prom_getchild
c_func
(paren
r_int
id|node
)paren
(brace
r_return
id|p1275_cmd
(paren
l_string|&quot;child&quot;
comma
id|P1275_INOUT
c_func
(paren
l_int|1
comma
l_int|1
)paren
comma
id|node
)paren
suffix:semicolon
)brace
id|__inline__
r_int
DECL|function|prom_getchild
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
(brace
r_return
l_int|0
suffix:semicolon
)brace
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
op_minus
l_int|1
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
(paren
r_int
)paren
id|cnode
suffix:semicolon
)brace
id|__inline__
r_int
DECL|function|prom_getparent
id|prom_getparent
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
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|cnode
op_assign
id|p1275_cmd
(paren
l_string|&quot;parent&quot;
comma
id|P1275_INOUT
c_func
(paren
l_int|1
comma
l_int|1
)paren
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cnode
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
(paren
r_int
)paren
id|cnode
suffix:semicolon
)brace
multiline_comment|/* Return the next sibling of node &squot;node&squot; or zero if no more siblings&n; * at this level of depth in the tree.&n; */
id|__inline__
r_int
DECL|function|__prom_getsibling
id|__prom_getsibling
c_func
(paren
r_int
id|node
)paren
(brace
r_return
id|p1275_cmd
(paren
l_string|&quot;peer&quot;
comma
id|P1275_INOUT
c_func
(paren
l_int|1
comma
l_int|1
)paren
comma
id|node
)paren
suffix:semicolon
)brace
id|__inline__
r_int
DECL|function|prom_getsibling
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
(brace
r_return
l_int|0
suffix:semicolon
)brace
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
op_minus
l_int|1
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|sibnode
suffix:semicolon
)brace
multiline_comment|/* Return the length in bytes of property &squot;prop&squot; at node &squot;node&squot;.&n; * Return -1 on error.&n; */
id|__inline__
r_int
DECL|function|prom_getproplen
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
r_return
id|p1275_cmd
(paren
l_string|&quot;getproplen&quot;
comma
id|P1275_ARG
c_func
(paren
l_int|1
comma
id|P1275_ARG_IN_STRING
)paren
op_or
id|P1275_INOUT
c_func
(paren
l_int|2
comma
l_int|1
)paren
comma
id|node
comma
id|prop
)paren
suffix:semicolon
)brace
multiline_comment|/* Acquire a property &squot;prop&squot; at node &squot;node&squot; and place it in&n; * &squot;buffer&squot; which has a size of &squot;bufsize&squot;.  If the acquisition&n; * was successful the length will be returned, else -1 is returned.&n; */
id|__inline__
r_int
DECL|function|prom_getproperty
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
r_else
(brace
multiline_comment|/* Ok, things seem all right. */
r_return
id|p1275_cmd
(paren
l_string|&quot;getprop&quot;
comma
id|P1275_ARG
c_func
(paren
l_int|1
comma
id|P1275_ARG_IN_STRING
)paren
op_or
id|P1275_ARG
c_func
(paren
l_int|2
comma
id|P1275_ARG_OUT_BUF
)paren
op_or
id|P1275_INOUT
c_func
(paren
l_int|4
comma
l_int|1
)paren
comma
id|node
comma
id|prop
comma
id|buffer
comma
id|P1275_SIZE
c_func
(paren
id|plen
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Acquire an integer property and return its value.  Returns -1&n; * on failure.&n; */
id|__inline__
r_int
DECL|function|prom_getint
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
r_int
DECL|function|prom_getintdefault
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
r_int
DECL|function|prom_getbool
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
r_void
DECL|function|prom_getstring
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
r_int
DECL|function|prom_nodematch
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
r_char
id|namebuf
(braket
l_int|128
)braket
suffix:semicolon
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
r_int
DECL|function|prom_searchsiblings
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
r_char
id|promlib_buf
(braket
l_int|128
)braket
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
multiline_comment|/* Gets name in the {name@x,yyyyy|name (if no reg)} form */
r_int
DECL|function|prom_getname
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
comma
id|sbus
op_assign
l_int|0
suffix:semicolon
r_int
id|pci
op_assign
l_int|0
comma
id|ebus
op_assign
l_int|0
comma
id|ide
op_assign
l_int|0
suffix:semicolon
r_struct
id|linux_prom_registers
op_star
id|reg
suffix:semicolon
r_struct
id|linux_prom64_registers
id|reg64
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
r_for
c_loop
(paren
id|sbus
op_assign
id|prom_getparent
(paren
id|node
)paren
suffix:semicolon
id|sbus
suffix:semicolon
id|sbus
op_assign
id|prom_getparent
(paren
id|sbus
)paren
)paren
(brace
id|i
op_assign
id|prom_getproperty
(paren
id|sbus
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
OG
l_int|0
)paren
(brace
id|buffer
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
(paren
id|buffer
comma
l_string|&quot;sbus&quot;
)paren
)paren
r_goto
id|getit
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|pci
op_assign
id|prom_getparent
(paren
id|node
)paren
)paren
)paren
(brace
id|i
op_assign
id|prom_getproperty
(paren
id|pci
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
OG
l_int|0
)paren
(brace
id|buffer
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
(paren
id|buffer
comma
l_string|&quot;pci&quot;
)paren
)paren
r_goto
id|getit
suffix:semicolon
)brace
id|pci
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ebus
op_assign
id|prom_getparent
(paren
id|node
)paren
)paren
)paren
(brace
id|i
op_assign
id|prom_getproperty
(paren
id|ebus
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
OG
l_int|0
)paren
(brace
id|buffer
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
(paren
id|buffer
comma
l_string|&quot;ebus&quot;
)paren
)paren
r_goto
id|getit
suffix:semicolon
)brace
id|ebus
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ide
op_assign
id|prom_getparent
(paren
id|node
)paren
)paren
)paren
(brace
id|i
op_assign
id|prom_getproperty
(paren
id|ide
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
OG
l_int|0
)paren
(brace
id|buffer
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
(paren
id|buffer
comma
l_string|&quot;ide&quot;
)paren
)paren
r_goto
id|getit
suffix:semicolon
)brace
id|ide
op_assign
l_int|0
suffix:semicolon
)brace
id|getit
suffix:colon
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
(brace
id|buffer
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
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
id|reg64
comma
r_sizeof
(paren
id|reg64
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
l_int|16
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
r_if
c_cond
(paren
id|sbus
)paren
(brace
id|reg
op_assign
(paren
r_struct
id|linux_prom_registers
op_star
)paren
id|reg64
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
)brace
r_else
r_if
c_cond
(paren
id|pci
)paren
(brace
r_int
id|dev
comma
id|fn
suffix:semicolon
id|reg
op_assign
(paren
r_struct
id|linux_prom_registers
op_star
)paren
id|reg64
suffix:semicolon
id|fn
op_assign
(paren
id|reg
(braket
l_int|0
)braket
dot
id|which_io
op_rshift
l_int|8
)paren
op_amp
l_int|0x07
suffix:semicolon
id|dev
op_assign
(paren
id|reg
(braket
l_int|0
)braket
dot
id|which_io
op_rshift
l_int|11
)paren
op_amp
l_int|0x1f
suffix:semicolon
r_if
c_cond
(paren
id|fn
)paren
id|sprintf
(paren
id|buffer
comma
l_string|&quot;@%x,%x&quot;
comma
id|dev
comma
id|fn
)paren
suffix:semicolon
r_else
id|sprintf
(paren
id|buffer
comma
l_string|&quot;@%x&quot;
comma
id|dev
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ebus
)paren
(brace
id|reg
op_assign
(paren
r_struct
id|linux_prom_registers
op_star
)paren
id|reg64
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
id|reg
(braket
l_int|0
)braket
dot
id|phys_addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ide
)paren
(brace
id|reg
op_assign
(paren
r_struct
id|linux_prom_registers
op_star
)paren
id|reg64
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
id|reg
(braket
l_int|0
)braket
dot
id|phys_addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_eq
l_int|4
)paren
(brace
multiline_comment|/* Happens on 8042&squot;s children on Ultra/PCI. */
id|reg
op_assign
(paren
r_struct
id|linux_prom_registers
op_star
)paren
id|reg64
suffix:semicolon
id|sprintf
(paren
id|buffer
comma
l_string|&quot;@%x&quot;
comma
id|reg
(braket
l_int|0
)braket
dot
id|which_io
)paren
suffix:semicolon
)brace
r_else
(brace
id|sprintf
(paren
id|buffer
comma
l_string|&quot;@%x,%x&quot;
comma
(paren
r_int
r_int
)paren
(paren
id|reg64
(braket
l_int|0
)braket
dot
id|phys_addr
op_rshift
l_int|36
)paren
comma
(paren
r_int
r_int
)paren
(paren
id|reg64
(braket
l_int|0
)braket
dot
id|phys_addr
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Return the first property type for node &squot;node&squot;.&n; * buffer should be at least 32B in length&n; */
id|__inline__
r_char
op_star
DECL|function|prom_firstprop
id|prom_firstprop
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|buffer
)paren
(brace
op_star
id|buffer
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
op_minus
l_int|1
)paren
(brace
r_return
id|buffer
suffix:semicolon
)brace
id|p1275_cmd
(paren
l_string|&quot;nextprop&quot;
comma
id|P1275_ARG
c_func
(paren
l_int|2
comma
id|P1275_ARG_OUT_32B
)paren
op_or
id|P1275_INOUT
c_func
(paren
l_int|3
comma
l_int|0
)paren
comma
id|node
comma
(paren
r_char
op_star
)paren
l_int|0x0
comma
id|buffer
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
multiline_comment|/* Return the property type string after property type &squot;oprop&squot;&n; * at node &squot;node&squot; .  Returns NULL string if no more&n; * property types for this node.&n; */
id|__inline__
r_char
op_star
DECL|function|prom_nextprop
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
r_char
id|buf
(braket
l_int|32
)braket
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
op_minus
l_int|1
)paren
(brace
op_star
id|buffer
op_assign
l_int|0
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oprop
op_eq
id|buffer
)paren
(brace
id|strcpy
(paren
id|buf
comma
id|oprop
)paren
suffix:semicolon
id|oprop
op_assign
id|buf
suffix:semicolon
)brace
id|p1275_cmd
(paren
l_string|&quot;nextprop&quot;
comma
id|P1275_ARG
c_func
(paren
l_int|1
comma
id|P1275_ARG_IN_STRING
)paren
op_or
id|P1275_ARG
c_func
(paren
l_int|2
comma
id|P1275_ARG_OUT_32B
)paren
op_or
id|P1275_INOUT
c_func
(paren
l_int|3
comma
l_int|0
)paren
comma
id|node
comma
id|oprop
comma
id|buffer
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
r_int
DECL|function|prom_finddevice
id|prom_finddevice
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|p1275_cmd
(paren
l_string|&quot;finddevice&quot;
comma
id|P1275_ARG
c_func
(paren
l_int|0
comma
id|P1275_ARG_IN_STRING
)paren
op_or
id|P1275_INOUT
c_func
(paren
l_int|1
comma
l_int|1
)paren
comma
id|name
)paren
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
id|buf
(braket
l_int|32
)braket
suffix:semicolon
op_star
id|buf
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|prom_nextprop
c_func
(paren
id|node
comma
id|buf
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|buf
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
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set property &squot;pname&squot; at node &squot;node&squot; to value &squot;value&squot; which has a length&n; * of &squot;size&squot; bytes.  Return the number of bytes the prom accepted.&n; */
r_int
DECL|function|prom_setprop
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
r_return
id|p1275_cmd
(paren
l_string|&quot;setprop&quot;
comma
id|P1275_ARG
c_func
(paren
l_int|1
comma
id|P1275_ARG_IN_STRING
)paren
op_or
id|P1275_ARG
c_func
(paren
l_int|2
comma
id|P1275_ARG_IN_BUF
)paren
op_or
id|P1275_INOUT
c_func
(paren
l_int|4
comma
l_int|1
)paren
comma
id|node
comma
id|pname
comma
id|value
comma
id|P1275_SIZE
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
id|__inline__
r_int
DECL|function|prom_inst2pkg
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
id|node
op_assign
id|p1275_cmd
(paren
l_string|&quot;instance-to-package&quot;
comma
id|P1275_INOUT
c_func
(paren
l_int|1
comma
l_int|1
)paren
comma
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
multiline_comment|/* Return &squot;node&squot; assigned to a particular prom &squot;path&squot;&n; * FIXME: Should work for v0 as well&n; */
r_int
DECL|function|prom_pathtoinode
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
l_int|0
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
