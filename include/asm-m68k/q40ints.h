multiline_comment|/*&n; * contains some Q40 related interrupt definitions&n; */
DECL|macro|Q40_IRQ_MAX
mdefine_line|#define Q40_IRQ_MAX      (34)
DECL|macro|Q40_IRQ_SAMPLE
mdefine_line|#define Q40_IRQ_SAMPLE    (34)
DECL|macro|Q40_IRQ_KEYBOARD
mdefine_line|#define Q40_IRQ_KEYBOARD (32)
DECL|macro|Q40_IRQ_FRAME
mdefine_line|#define Q40_IRQ_FRAME    (33)
multiline_comment|/* masks for interrupt regiosters*/
multiline_comment|/* internal, IIRQ_REG */
DECL|macro|IRQ_KEYB_MASK
mdefine_line|#define IRQ_KEYB_MASK    (2)
DECL|macro|IRQ_SER_MASK
mdefine_line|#define IRQ_SER_MASK     (1&lt;&lt;2)
DECL|macro|IRQ_FRAME_MASK
mdefine_line|#define IRQ_FRAME_MASK   (1&lt;&lt;3)
DECL|macro|IRQ_EXT_MASK
mdefine_line|#define IRQ_EXT_MASK     (1&lt;&lt;4)    /* is a EIRQ */
multiline_comment|/* eirq, EIRQ_REG */
DECL|macro|IRQ3_MASK
mdefine_line|#define IRQ3_MASK        (1)
DECL|macro|IRQ4_MASK
mdefine_line|#define IRQ4_MASK        (1&lt;&lt;1)
DECL|macro|IRQ5_MASK
mdefine_line|#define IRQ5_MASK        (1&lt;&lt;2)
DECL|macro|IRQ6_MASK
mdefine_line|#define IRQ6_MASK        (1&lt;&lt;3)
DECL|macro|IRQ7_MASK
mdefine_line|#define IRQ7_MASK        (1&lt;&lt;4)
DECL|macro|IRQ10_MASK
mdefine_line|#define IRQ10_MASK       (1&lt;&lt;5)
DECL|macro|IRQ14_MASK
mdefine_line|#define IRQ14_MASK       (1&lt;&lt;6)
DECL|macro|IRQ15_MASK
mdefine_line|#define IRQ15_MASK       (1&lt;&lt;7)
r_extern
r_int
r_int
id|q40_probe_irq_on
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|q40_probe_irq_off
(paren
r_int
r_int
id|irqs
)paren
suffix:semicolon
eof
