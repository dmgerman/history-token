multiline_comment|/*&n; * linux/arch/x86_64/mm/extable.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* Simple binary search */
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
r_int
id|diff
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
id|diff
op_assign
id|mid-&gt;insn
op_minus
id|value
suffix:semicolon
r_if
c_cond
(paren
id|diff
op_eq
l_int|0
)paren
r_return
id|mid
suffix:semicolon
r_else
r_if
c_cond
(paren
id|diff
OL
l_int|0
)paren
id|first
op_assign
id|mid
op_plus
l_int|1
suffix:semicolon
r_else
id|last
op_assign
id|mid
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* When an exception handler is in an non standard section (like __init)&n;   the fixup table can end up unordered. Fix that here. */
DECL|function|check_extable
r_static
id|__init
r_int
id|check_extable
c_func
(paren
r_void
)paren
(brace
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
r_struct
id|exception_table_entry
op_star
id|e
suffix:semicolon
r_int
id|change
suffix:semicolon
multiline_comment|/* The input is near completely presorted, which makes bubble sort the&n;&t;   best (and simplest) sort algorithm. */
r_do
(brace
id|change
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|e
op_assign
id|__start___ex_table
op_plus
l_int|1
suffix:semicolon
id|e
OL
id|__stop___ex_table
suffix:semicolon
id|e
op_increment
)paren
(brace
r_if
c_cond
(paren
id|e-&gt;insn
OL
id|e
(braket
op_minus
l_int|1
)braket
dot
id|insn
)paren
(brace
r_struct
id|exception_table_entry
id|tmp
op_assign
id|e
(braket
op_minus
l_int|1
)braket
suffix:semicolon
id|e
(braket
op_minus
l_int|1
)braket
op_assign
id|e
(braket
l_int|0
)braket
suffix:semicolon
id|e
(braket
l_int|0
)braket
op_assign
id|tmp
suffix:semicolon
id|change
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
id|change
op_ne
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|check_extable
id|core_initcall
c_func
(paren
id|check_extable
)paren
suffix:semicolon
eof
