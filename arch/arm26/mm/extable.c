multiline_comment|/*&n; *  linux/arch/arm26/mm/extable.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
id|instruction_pointer
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The kernel runs in SVC mode - make sure we keep running in SVC mode&n;&t; * by frobbing the PSR appropriately (PSR and PC are in the same reg.&n;&t; * on ARM26)&n;&t; */
r_if
c_cond
(paren
id|fixup
)paren
id|regs-&gt;ARM_pc
op_assign
id|fixup-&gt;fixup
op_or
id|PSR_I_BIT
op_or
id|MODE_SVC26
suffix:semicolon
r_return
id|fixup
op_ne
l_int|NULL
suffix:semicolon
)brace
eof
