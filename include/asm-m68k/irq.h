macro_line|#ifndef _M68K_IRQ_H_
DECL|macro|_M68K_IRQ_H_
mdefine_line|#define _M68K_IRQ_H_
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * # of m68k interrupts&n; */
DECL|macro|SYS_IRQS
mdefine_line|#define SYS_IRQS 8
multiline_comment|/*&n; * This should be the same as the max(NUM_X_SOURCES) for all the&n; * different m68k hosts compiled into the kernel.&n; * Currently the Atari has 72 and the Amiga 24, but if both are&n; * supported in the kernel it is better to make room for 72.&n; */
macro_line|#if defined(CONFIG_ATARI) || defined(CONFIG_MAC)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS (72+SYS_IRQS)
macro_line|#else
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS (24+SYS_IRQS)
macro_line|#endif
multiline_comment|/*&n; * Interrupt source definitions&n; * General interrupt sources are the level 1-7.&n; * Adding an interrupt service routine for one of these sources&n; * results in the addition of that routine to a chain of routines.&n; * Each one is called in succession.  Each individual interrupt&n; * service routine should determine if the device associated with&n; * that routine requires service.&n; */
DECL|macro|IRQ1
mdefine_line|#define IRQ1&t;&t;(1)&t;/* level 1 interrupt */
DECL|macro|IRQ2
mdefine_line|#define IRQ2&t;&t;(2)&t;/* level 2 interrupt */
DECL|macro|IRQ3
mdefine_line|#define IRQ3&t;&t;(3)&t;/* level 3 interrupt */
DECL|macro|IRQ4
mdefine_line|#define IRQ4&t;&t;(4)&t;/* level 4 interrupt */
DECL|macro|IRQ5
mdefine_line|#define IRQ5&t;&t;(5)&t;/* level 5 interrupt */
DECL|macro|IRQ6
mdefine_line|#define IRQ6&t;&t;(6)&t;/* level 6 interrupt */
DECL|macro|IRQ7
mdefine_line|#define IRQ7&t;&t;(7)&t;/* level 7 interrupt (non-maskable) */
multiline_comment|/*&n; * &quot;Generic&quot; interrupt sources&n; */
DECL|macro|IRQ_SCHED_TIMER
mdefine_line|#define IRQ_SCHED_TIMER&t;(8)    /* interrupt source for scheduling timer */
DECL|function|irq_cannonicalize
r_static
id|__inline__
r_int
id|irq_cannonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
multiline_comment|/*&n; * Machine specific interrupt sources.&n; *&n; * Adding an interrupt service routine for a source with this bit&n; * set indicates a special machine specific interrupt source.&n; * The machine specific files define these sources.&n; *&n; * The IRQ_MACHSPEC bit is now gone - the only thing it did was to&n; * introduce unnecessary overhead.&n; *&n; * All interrupt handling is actually machine specific so it is better&n; * to use function pointers, as used by the Sparc port, and select the&n; * interrupt handling functions when initializing the kernel. This way&n; * we save some unnecessary overhead at run-time. &n; *                                                      01/11/97 - Jes&n; */
r_extern
r_void
(paren
op_star
id|enable_irq
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|disable_irq
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|disable_irq_nosync
mdefine_line|#define disable_irq_nosync&t;disable_irq
DECL|macro|enable_irq_nosync
mdefine_line|#define enable_irq_nosync&t;enable_irq
r_extern
r_int
id|sys_request_irq
c_func
(paren
r_int
r_int
comma
r_void
(paren
op_star
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
comma
r_const
r_char
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sys_free_irq
c_func
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * various flags for request_irq() - the Amiga now uses the standard&n; * mechanism like all other architectures - SA_INTERRUPT and SA_SHIRQ&n; * are your friends.&n; */
macro_line|#ifndef CONFIG_AMIGA
DECL|macro|IRQ_FLG_LOCK
mdefine_line|#define IRQ_FLG_LOCK&t;(0x0001)&t;/* handler is not replaceable&t;*/
DECL|macro|IRQ_FLG_REPLACE
mdefine_line|#define IRQ_FLG_REPLACE&t;(0x0002)&t;/* replace existing handler&t;*/
DECL|macro|IRQ_FLG_FAST
mdefine_line|#define IRQ_FLG_FAST&t;(0x0004)
DECL|macro|IRQ_FLG_SLOW
mdefine_line|#define IRQ_FLG_SLOW&t;(0x0008)
DECL|macro|IRQ_FLG_STD
mdefine_line|#define IRQ_FLG_STD&t;(0x8000)&t;/* internally used&t;&t;*/
macro_line|#endif
multiline_comment|/*&n; * This structure is used to chain together the ISRs for a particular&n; * interrupt source (if it supports chaining).&n; */
DECL|struct|irq_node
r_typedef
r_struct
id|irq_node
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
DECL|member|devname
r_const
r_char
op_star
id|devname
suffix:semicolon
DECL|member|next
r_struct
id|irq_node
op_star
id|next
suffix:semicolon
DECL|typedef|irq_node_t
)brace
id|irq_node_t
suffix:semicolon
multiline_comment|/*&n; * This structure has only 4 elements for speed reasons&n; */
DECL|struct|irq_handler
r_typedef
r_struct
id|irq_handler
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
DECL|member|devname
r_const
r_char
op_star
id|devname
suffix:semicolon
DECL|typedef|irq_handler_t
)brace
id|irq_handler_t
suffix:semicolon
multiline_comment|/* count of spurious interrupts */
r_extern
r_volatile
r_int
r_int
id|num_spurious
suffix:semicolon
multiline_comment|/*&n; * This function returns a new irq_node_t&n; */
r_extern
id|irq_node_t
op_star
id|new_irq_node
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _M68K_IRQ_H_ */
eof
