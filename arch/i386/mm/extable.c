multiline_comment|/*&n; * linux/arch/i386/mm/extable.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
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
macro_line|#ifdef CONFIG_PNPBIOS
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|regs-&gt;xcs
op_or
l_int|8
)paren
op_eq
l_int|0x88
)paren
)paren
multiline_comment|/* 0x80 or 0x88 */
(brace
r_extern
id|u32
id|pnp_bios_fault_eip
comma
id|pnp_bios_fault_esp
suffix:semicolon
r_extern
id|u32
id|pnp_bios_is_utter_crap
suffix:semicolon
id|pnp_bios_is_utter_crap
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;PNPBIOS fault.. attempting recovery.&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
r_volatile
(paren
l_string|&quot;movl %0, %%esp&bslash;n&bslash;t&quot;
l_string|&quot;jmp *%1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|pnp_bios_fault_esp
)paren
comma
l_string|&quot;=b&quot;
(paren
id|pnp_bios_fault_eip
)paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;do_trap: can&squot;t hit this&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|fixup
op_assign
id|search_exception_tables
c_func
(paren
id|regs-&gt;eip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fixup
)paren
(brace
id|regs-&gt;eip
op_assign
id|fixup-&gt;fixup
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
