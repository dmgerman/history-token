multiline_comment|/*&n; * linux/arch/alpha/mm/extable.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_const
r_struct
id|exception_table_entry
id|__start___ex_table
(braket
)braket
suffix:semicolon
r_extern
r_const
r_struct
id|exception_table_entry
id|__stop___ex_table
(braket
)braket
suffix:semicolon
r_static
r_inline
r_int
DECL|function|search_one_table
id|search_one_table
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
r_int
id|mid_value
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
id|mid_value
op_assign
(paren
r_int
r_int
)paren
op_amp
id|mid-&gt;insn
op_plus
id|mid-&gt;insn
suffix:semicolon
r_if
c_cond
(paren
id|mid_value
op_eq
id|value
)paren
r_return
id|mid-&gt;fixup.unit
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mid_value
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
id|last
op_assign
id|mid
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|search_exception_table
id|search_exception_table
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
macro_line|#ifndef CONFIG_MODULES
id|ret
op_assign
id|search_one_table
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
macro_line|#else
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|i
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|modlist_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|i
comma
op_amp
id|extables
)paren
(brace
r_struct
id|exception_table
op_star
id|ex
op_assign
id|list_entry
c_func
(paren
id|i
comma
r_struct
id|exception_table
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ex-&gt;num_entries
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|search_one_table
c_func
(paren
id|ex-&gt;entry
comma
id|ex-&gt;entry
op_plus
id|ex-&gt;num_entries
op_minus
l_int|1
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|modlist_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
eof
