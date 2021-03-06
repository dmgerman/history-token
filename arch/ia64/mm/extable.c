multiline_comment|/*&n; * Kernel exception handling table support.  Derived from arch/alpha/mm/extable.c.&n; *&n; * Copyright (C) 1998, 1999, 2001-2002, 2004 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sort.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/module.h&gt;
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
id|l
op_assign
id|a
comma
op_star
id|r
op_assign
id|b
suffix:semicolon
id|u64
id|lip
op_assign
(paren
id|u64
)paren
op_amp
id|l-&gt;addr
op_plus
id|l-&gt;addr
suffix:semicolon
id|u64
id|rip
op_assign
(paren
id|u64
)paren
op_amp
id|r-&gt;addr
op_plus
id|r-&gt;addr
suffix:semicolon
multiline_comment|/* avoid overflow */
r_if
c_cond
(paren
id|lip
OG
id|rip
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|lip
OL
id|rip
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|swap_ex
r_static
r_void
id|swap_ex
c_func
(paren
r_void
op_star
id|a
comma
r_void
op_star
id|b
comma
r_int
id|size
)paren
(brace
r_struct
id|exception_table_entry
op_star
id|l
op_assign
id|a
comma
op_star
id|r
op_assign
id|b
comma
id|tmp
suffix:semicolon
id|u64
id|delta
op_assign
(paren
id|u64
)paren
id|r
op_minus
(paren
id|u64
)paren
id|l
suffix:semicolon
id|tmp
op_assign
op_star
id|l
suffix:semicolon
id|l-&gt;addr
op_assign
id|r-&gt;addr
op_plus
id|delta
suffix:semicolon
id|l-&gt;cont
op_assign
id|r-&gt;cont
op_plus
id|delta
suffix:semicolon
id|r-&gt;addr
op_assign
id|tmp.addr
op_minus
id|delta
suffix:semicolon
id|r-&gt;cont
op_assign
id|tmp.cont
op_minus
id|delta
suffix:semicolon
)brace
multiline_comment|/*&n; * Sort the exception table. It&squot;s usually already sorted, but there&n; * may be unordered entries due to multiple text sections (such as the&n; * .init text section). Note that the exception-table-entries contain&n; * location-relative addresses, which requires a bit of care during&n; * sorting to avoid overflows in the offset members (e.g., it would&n; * not be safe to make a temporary copy of an exception-table entry on&n; * the stack, because the stack may be more than 2GB away from the&n; * exception-table).&n; */
DECL|function|sort_extable
r_void
id|sort_extable
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
id|swap_ex
)paren
suffix:semicolon
)brace
r_const
r_struct
id|exception_table_entry
op_star
DECL|function|search_extable
id|search_extable
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
id|ip
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
id|mid_ip
suffix:semicolon
r_int
id|diff
suffix:semicolon
r_while
c_loop
(paren
id|first
op_le
id|last
)paren
(brace
id|mid
op_assign
op_amp
id|first
(braket
(paren
id|last
op_minus
id|first
)paren
op_div
l_int|2
)braket
suffix:semicolon
id|mid_ip
op_assign
(paren
id|u64
)paren
op_amp
id|mid-&gt;addr
op_plus
id|mid-&gt;addr
suffix:semicolon
id|diff
op_assign
id|mid_ip
op_minus
id|ip
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
r_void
DECL|function|ia64_handle_exception
id|ia64_handle_exception
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_const
r_struct
id|exception_table_entry
op_star
id|e
)paren
(brace
r_int
id|fix
op_assign
(paren
id|u64
)paren
op_amp
id|e-&gt;cont
op_plus
id|e-&gt;cont
suffix:semicolon
id|regs-&gt;r8
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|fix
op_amp
l_int|4
)paren
id|regs-&gt;r9
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;cr_iip
op_assign
id|fix
op_amp
op_complement
l_int|0xf
suffix:semicolon
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
op_assign
id|fix
op_amp
l_int|0x3
suffix:semicolon
multiline_comment|/* set continuation slot number */
)brace
eof
