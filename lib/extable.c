multiline_comment|/*&n; * lib/extable.c&n; * Derived from arch/ppc/mm/extable.c and arch/i386/mm/extable.c.&n; *&n; * Copyright (C) 2004 Paul Mackerras, IBM Corp.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sort.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_struct
id|exception_table_entry
id|__start___ex_table
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|exception_table_entry
id|__stop___ex_table
(braket
)braket
suffix:semicolon
macro_line|#ifndef ARCH_HAS_SORT_EXTABLE
multiline_comment|/*&n; * The exception table needs to be sorted so that the binary&n; * search that we use to find entries in it works properly.&n; * This is used both for the kernel exception table and for&n; * the exception tables of modules that get loaded.&n; */
DECL|function|cmp_ex
r_static
r_int
id|cmp_ex
c_func
(paren
r_const
r_void
op_star
id|a
comma
r_const
r_void
op_star
id|b
)paren
(brace
r_const
r_struct
id|exception_table_entry
op_star
id|x
op_assign
id|a
comma
op_star
id|y
op_assign
id|b
suffix:semicolon
r_return
id|x-&gt;insn
op_minus
id|y-&gt;insn
suffix:semicolon
)brace
DECL|function|sort_extable
r_void
id|sort_extable
c_func
(paren
r_struct
id|exception_table_entry
op_star
id|start
comma
r_struct
id|exception_table_entry
op_star
id|finish
)paren
(brace
id|sort
c_func
(paren
id|start
comma
id|finish
op_minus
id|start
comma
r_sizeof
(paren
r_struct
id|exception_table_entry
)paren
comma
id|cmp_ex
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef ARCH_HAS_SEARCH_EXTABLE
multiline_comment|/*&n; * Search one exception table for an entry corresponding to the&n; * given instruction address, and return the address of the entry,&n; * or NULL if none is found.&n; * We use a binary search, and thus we assume that the table is&n; * already sorted.&n; */
r_const
r_struct
id|exception_table_entry
op_star
DECL|function|search_extable
id|search_extable
c_func
(paren
r_const
r_struct
id|exception_table_entry
op_star
id|first
comma
r_const
r_struct
id|exception_table_entry
op_star
id|last
comma
r_int
r_int
id|value
)paren
(brace
r_while
c_loop
(paren
id|first
op_le
id|last
)paren
(brace
r_const
r_struct
id|exception_table_entry
op_star
id|mid
suffix:semicolon
id|mid
op_assign
(paren
id|last
op_minus
id|first
)paren
op_div
l_int|2
op_plus
id|first
suffix:semicolon
multiline_comment|/*&n;&t;&t; * careful, the distance between entries can be&n;&t;&t; * larger than 2GB:&n;&t;&t; */
r_if
c_cond
(paren
id|mid-&gt;insn
OL
id|value
)paren
id|first
op_assign
id|mid
op_plus
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mid-&gt;insn
OG
id|value
)paren
id|last
op_assign
id|mid
op_minus
l_int|1
suffix:semicolon
r_else
r_return
id|mid
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
eof
