multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/irq.h&n; * &n; * Author: Nicolas Pitre&n; */
DECL|macro|fixup_irq
mdefine_line|#define fixup_irq(x)&t;(x)
multiline_comment|/*&n; * This prototype is required for cascading of multiplexed interrupts.&n; * Since it doesn&squot;t exist elsewhere, we&squot;ll put it here for now.&n; */
r_extern
r_void
id|do_IRQ
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
eof
