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
multiline_comment|/* Abort early if the search value is out of range.  */
r_if
c_cond
(paren
id|value
op_ne
(paren
r_int
r_int
)paren
id|value
)paren
r_return
l_int|0
suffix:semicolon
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
id|mid-&gt;fixup.unit
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
l_int|0
suffix:semicolon
)brace
r_register
r_int
r_int
id|gp
id|__asm__
c_func
(paren
l_string|&quot;$29&quot;
)paren
suffix:semicolon
r_static
r_int
DECL|function|search_exception_table_without_gp
id|search_exception_table_without_gp
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
multiline_comment|/* There is only the kernel to search.  */
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
op_minus
id|gp
)paren
suffix:semicolon
macro_line|#else
r_extern
id|spinlock_t
id|modlist_lock
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* The kernel is the last &quot;module&quot; -- no need to treat it special. */
r_struct
id|module
op_star
id|mp
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
r_for
c_loop
(paren
id|mp
op_assign
id|module_list
suffix:semicolon
id|mp
suffix:semicolon
id|mp
op_assign
id|mp-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mp-&gt;ex_table_start
op_logical_or
op_logical_neg
(paren
id|mp-&gt;flags
op_amp
(paren
id|MOD_RUNNING
op_or
id|MOD_INITIALIZING
)paren
)paren
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|search_one_table
c_func
(paren
id|mp-&gt;ex_table_start
comma
id|mp-&gt;ex_table_end
op_minus
l_int|1
comma
id|addr
op_minus
id|mp-&gt;gp
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
r_int
DECL|function|search_exception_table
id|search_exception_table
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|exc_gp
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
op_minus
id|exc_gp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
macro_line|#else
r_extern
id|spinlock_t
id|modlist_lock
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* The kernel is the last &quot;module&quot; -- no need to treat it special. */
r_struct
id|module
op_star
id|mp
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
r_for
c_loop
(paren
id|mp
op_assign
id|module_list
suffix:semicolon
id|mp
suffix:semicolon
id|mp
op_assign
id|mp-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mp-&gt;ex_table_start
op_logical_or
op_logical_neg
(paren
id|mp-&gt;flags
op_amp
(paren
id|MOD_RUNNING
op_or
id|MOD_INITIALIZING
)paren
)paren
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|search_one_table
c_func
(paren
id|mp-&gt;ex_table_start
comma
id|mp-&gt;ex_table_end
op_minus
l_int|1
comma
id|addr
op_minus
id|exc_gp
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
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * The search failed with the exception gp. To be safe, try the&n;&t; * old method before giving up.&n;&t; */
id|ret
op_assign
id|search_exception_table_without_gp
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;%s: [%lx] EX_TABLE search fail with&quot;
l_string|&quot;exc frame GP, success with raw GP&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|addr
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
