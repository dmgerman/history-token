macro_line|#ifndef __irq_h
DECL|macro|__irq_h
mdefine_line|#define __irq_h
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/*&n; * IRQ line status.&n; */
DECL|macro|IRQ_INPROGRESS
mdefine_line|#define IRQ_INPROGRESS&t;1&t;/* IRQ handler active - do not enter! */
DECL|macro|IRQ_DISABLED
mdefine_line|#define IRQ_DISABLED&t;2&t;/* IRQ disabled - do not enter! */
DECL|macro|IRQ_PENDING
mdefine_line|#define IRQ_PENDING&t;4&t;/* IRQ pending - replay on enable */
DECL|macro|IRQ_REPLAY
mdefine_line|#define IRQ_REPLAY&t;8&t;/* IRQ has been replayed but not acked yet */
DECL|macro|IRQ_AUTODETECT
mdefine_line|#define IRQ_AUTODETECT&t;16&t;/* IRQ is being autodetected */
DECL|macro|IRQ_WAITING
mdefine_line|#define IRQ_WAITING&t;32&t;/* IRQ not yet seen - for autodetection */
DECL|macro|IRQ_LEVEL
mdefine_line|#define IRQ_LEVEL&t;64&t;/* IRQ level triggered */
DECL|macro|IRQ_MASKED
mdefine_line|#define IRQ_MASKED&t;128&t;/* IRQ masked - shouldn&squot;t be seen again */
DECL|macro|IRQ_PER_CPU
mdefine_line|#define IRQ_PER_CPU&t;256&t;/* IRQ is per CPU */
multiline_comment|/*&n; * Interrupt controller descriptor. This is all we need&n; * to describe about the low-level hardware. &n; */
DECL|struct|hw_interrupt_type
r_struct
id|hw_interrupt_type
(brace
DECL|member|typename
r_const
r_char
op_star
r_typename
suffix:semicolon
DECL|member|startup
r_int
r_int
(paren
op_star
id|startup
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|member|shutdown
r_void
(paren
op_star
id|shutdown
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|member|enable
r_void
(paren
op_star
id|enable
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|member|disable
r_void
(paren
op_star
id|disable
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|member|ack
r_void
(paren
op_star
id|ack
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|member|end
r_void
(paren
op_star
id|end
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|member|set_affinity
r_void
(paren
op_star
id|set_affinity
)paren
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|mask
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|hw_irq_controller
r_typedef
r_struct
id|hw_interrupt_type
id|hw_irq_controller
suffix:semicolon
multiline_comment|/*&n; * This is the &quot;IRQ descriptor&quot;, which contains various information&n; * about the irq, including what kind of hardware handling it has,&n; * whether it is disabled etc etc.&n; *&n; * Pad this out to 32 bytes for cache and indexing reasons.&n; */
r_typedef
r_struct
(brace
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* IRQ status */
DECL|member|handler
id|hw_irq_controller
op_star
id|handler
suffix:semicolon
DECL|member|action
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
multiline_comment|/* IRQ action list */
DECL|member|depth
r_int
r_int
id|depth
suffix:semicolon
multiline_comment|/* nested irq disables */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|typedef|irq_desc_t
)brace
id|____cacheline_aligned
id|irq_desc_t
suffix:semicolon
r_extern
id|irq_desc_t
id|irq_desc
(braket
id|NR_IRQS
)braket
suffix:semicolon
macro_line|#include &lt;asm/hw_irq.h&gt; /* the arch dependent stuff */
r_extern
r_int
id|handle_IRQ_event
c_func
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
comma
r_struct
id|irqaction
op_star
)paren
suffix:semicolon
r_extern
r_int
id|setup_irq
c_func
(paren
r_int
r_int
comma
r_struct
id|irqaction
op_star
)paren
suffix:semicolon
r_extern
id|hw_irq_controller
id|no_irq_type
suffix:semicolon
multiline_comment|/* needed in every arch ? */
r_extern
r_void
id|no_action
c_func
(paren
r_int
id|cpl
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* __asm_h */
eof
