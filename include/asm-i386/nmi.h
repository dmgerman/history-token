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
macro_line|#endif /* ASM_NMI_H */
eof
