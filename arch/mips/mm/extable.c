multiline_comment|/*&n; * linux/arch/mips/mm/extable.c&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/branch.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|fixup_exception
r_int
id|fixup_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_const
r_struct
id|exception_table_entry
op_star
id|fixup
suffix:semicolon
id|fixup
op_assign
id|search_exception_tables
c_func
(paren
id|exception_epc
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fixup
)paren
(brace
id|regs-&gt;cp0_epc
op_assign
id|fixup-&gt;nextinsn
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
