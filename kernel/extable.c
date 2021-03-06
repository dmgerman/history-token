multiline_comment|/* Rewritten by Rusty Russell, on the backs of many others...&n;   Copyright (C) 2001 Rusty Russell, 2002 Rusty Russell IBM.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
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
multiline_comment|/* Sort the kernel&squot;s built-in exception table */
DECL|function|sort_main_extable
r_void
id|__init
id|sort_main_extable
c_func
(paren
r_void
)paren
(brace
id|sort_extable
c_func
(paren
id|__start___ex_table
comma
id|__stop___ex_table
)paren
suffix:semicolon
)brace
multiline_comment|/* Given an address, look for it in the exception tables. */
DECL|function|search_exception_tables
r_const
r_struct
id|exception_table_entry
op_star
id|search_exception_tables
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_const
r_struct
id|exception_table_entry
op_star
id|e
suffix:semicolon
id|e
op_assign
id|search_extable
c_func
(paren
id|__start___ex_table
comma
id|__stop___ex_table
op_minus
l_int|1
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e
)paren
id|e
op_assign
id|search_module_extables
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
id|e
suffix:semicolon
)brace
DECL|function|core_kernel_text
r_static
r_int
id|core_kernel_text
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
r_int
)paren
id|_stext
op_logical_and
id|addr
op_le
(paren
r_int
r_int
)paren
id|_etext
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
r_int
)paren
id|_sinittext
op_logical_and
id|addr
op_le
(paren
r_int
r_int
)paren
id|_einittext
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__kernel_text_address
r_int
id|__kernel_text_address
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|core_kernel_text
c_func
(paren
id|addr
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|__module_text_address
c_func
(paren
id|addr
)paren
op_ne
l_int|NULL
suffix:semicolon
)brace
DECL|function|kernel_text_address
r_int
id|kernel_text_address
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|core_kernel_text
c_func
(paren
id|addr
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|module_text_address
c_func
(paren
id|addr
)paren
op_ne
l_int|NULL
suffix:semicolon
)brace
eof
