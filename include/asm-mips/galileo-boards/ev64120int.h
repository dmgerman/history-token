macro_line|#ifndef IRQ_HANDLER_
DECL|macro|IRQ_HANDLER_
mdefine_line|#define IRQ_HANDLER_
DECL|macro|INT_CAUSE_MAIN
mdefine_line|#define INT_CAUSE_MAIN 0
DECL|macro|INT_CAUSE_HIGH
mdefine_line|#define INT_CAUSE_HIGH 1
DECL|macro|MAX_CAUSE_REGS
mdefine_line|#define MAX_CAUSE_REGS 4
DECL|macro|MAX_CAUSE_REG_WIDTH
mdefine_line|#define MAX_CAUSE_REG_WIDTH 32
r_void
id|hook_irq_handler
(paren
r_int
id|int_cause
comma
r_int
id|bit_num
comma
r_void
op_star
id|isr_ptr
)paren
suffix:semicolon
r_int
id|disable_galileo_irq
(paren
r_int
id|int_cause
comma
r_int
id|bit_num
)paren
suffix:semicolon
r_int
id|enable_galileo_irq
(paren
r_int
id|int_cause
comma
r_int
id|bit_num
)paren
suffix:semicolon
r_extern
r_struct
id|tq_struct
id|irq_handlers
(braket
id|MAX_CAUSE_REGS
)braket
(braket
id|MAX_CAUSE_REG_WIDTH
)braket
suffix:semicolon
multiline_comment|/*&n;  PCI interrupts will come in on either the INTA or&n;  INTD interrups lines, which are mapped to the #2 and&n;  #5 interrupt pins of the MIPS.  On our boards, they&n;  all either come in on IntD or they all come in on&n;  IntA, they aren&squot;t mixed. There can be numerous PCI&n;  interrupts, so we keep a list of the &quot;requested&quot;&n;  interrupt numbers and go through the list whenever&n;  we get an IntA/D.&n;&n;  All PCI interrupts have numbers &gt;= 20 by arbitrary convention.  Any&n;  interrupt &lt; 8 is an interrupt that is maskable on the&n;  MIPS.&n;*/
DECL|macro|TIMER
mdefine_line|#define TIMER 4
DECL|macro|INTA
mdefine_line|#define INTA 2
DECL|macro|INTD
mdefine_line|#define INTD 5
macro_line|#endif /* IRQ_HANDLER_ */
eof
