macro_line|#ifndef _ASM_PMC_CP7000INT_H
DECL|macro|_ASM_PMC_CP7000INT_H
mdefine_line|#define _ASM_PMC_CP7000INT_H
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
multiline_comment|/*&n; * PCI interrupts will come in on either the INTA or INTD interrups lines,&n; * which are mapped to the #2 and #5 interrupt pins of the MIPS.  On our&n; * boards, they all either come in on IntD or they all come in on IntA, they&n; * aren&squot;t mixed. There can be numerous PCI interrupts, so we keep a list of the&n; * &quot;requested&quot; interrupt numbers and go through the list whenever we get an&n; * IntA/D.&n; *&n; * All PCI interrupts have numbers &gt;= 20 by arbitrary convention.  Any&n; * interrupt &lt; 8 is an interrupt that is maskable on MIPS.&n; */
DECL|macro|TIMER
mdefine_line|#define TIMER&t;4
DECL|macro|INTA
mdefine_line|#define INTA&t;2
DECL|macro|INTD
mdefine_line|#define INTD&t;5
macro_line|#endif /* _ASM_PMC_CP7000INT_H */
eof
