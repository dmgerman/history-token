multiline_comment|/*&n; *  arch/s390/mm/extable.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com)&n; *&n; *  Derived from &quot;arch/i386/mm/extable.c&quot;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
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
id|mid-&gt;fixup
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
r_extern
id|spinlock_t
id|modlist_lock
suffix:semicolon
r_int
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifndef CONFIG_MODULES
id|addr
op_and_assign
l_int|0x7fffffff
suffix:semicolon
multiline_comment|/* remove amode bit from address */
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
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|ret
op_assign
id|FIX_PSW
c_func
(paren
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
macro_line|#else
multiline_comment|/* The kernel is the last &quot;module&quot; -- no need to treat it special.  */
r_struct
id|module
op_star
id|mp
suffix:semicolon
id|addr
op_and_assign
l_int|0x7fffffff
suffix:semicolon
multiline_comment|/* remove amode bit from address */
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
op_ne
l_int|NULL
suffix:semicolon
id|mp
op_assign
id|mp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|mp-&gt;ex_table_start
op_eq
l_int|NULL
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
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|ret
op_assign
id|FIX_PSW
c_func
(paren
id|ret
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_return
id|ret
suffix:semicolon
macro_line|#endif
)brace
eof
