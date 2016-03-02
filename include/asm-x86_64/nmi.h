multiline_comment|/*&n; *  linux/include/asm-i386/nmi.h&n; */
macro_line|#ifndef ASM_NMI_H
DECL|macro|ASM_NMI_H
mdefine_line|#define ASM_NMI_H
macro_line|#include &lt;linux/pm.h&gt;
r_struct
id|pt_regs
suffix:semicolon
DECL|typedef|nmi_callback_t
r_typedef
r_int
(paren
op_star
id|nmi_callback_t
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/** &n; * set_nmi_callback&n; *&n; * Set a handler for an NMI. Only one handler may be&n; * set. Return 1 if the NMI was handled.&n; */
r_void
id|set_nmi_callback
c_func
(paren
id|nmi_callback_t
id|callback
)paren
suffix:semicolon
multiline_comment|/** &n; * unset_nmi_callback&n; *&n; * Remove the handler previously set.&n; */
r_void
id|unset_nmi_callback
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
multiline_comment|/** Replace the PM callback routine for NMI. */
r_struct
id|pm_dev
op_star
id|set_nmi_pm_callback
c_func
(paren
id|pm_callback
id|callback
)paren
suffix:semicolon
multiline_comment|/** Unset the PM callback routine back to the default. */
r_void
id|unset_nmi_pm_callback
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#else
DECL|function|set_nmi_pm_callback
r_static
r_inline
r_struct
id|pm_dev
op_star
id|set_nmi_pm_callback
c_func
(paren
id|pm_callback
id|callback
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unset_nmi_pm_callback
r_static
r_inline
r_void
id|unset_nmi_pm_callback
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
)paren
(brace
)brace
macro_line|#endif /* CONFIG_PM */
r_extern
r_void
id|default_do_nmi
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif /* ASM_NMI_H */
eof
