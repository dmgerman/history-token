macro_line|#ifndef _M68K_IRQ_H_
DECL|macro|_M68K_IRQ_H_
mdefine_line|#define _M68K_IRQ_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#ifdef CONFIG_COLDFIRE
multiline_comment|/*&n; * On the ColdFire we keep track of all vectors. That way drivers&n; * can register whatever vector number they wish, and we can deal&n; * with it.&n; */
DECL|macro|SYS_IRQS
mdefine_line|#define&t;SYS_IRQS&t;256
DECL|macro|NR_IRQS
mdefine_line|#define&t;NR_IRQS&t;&t;SYS_IRQS
macro_line|#else
multiline_comment|/*&n; * # of m68k interrupts&n; */
DECL|macro|SYS_IRQS
mdefine_line|#define SYS_IRQS 8
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS (24+SYS_IRQS)
macro_line|#endif /* CONFIG_COLDFIRE */
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
multiline_comment|/*&n; * Machine specific interrupt sources.&n; *&n; * Adding an interrupt service routine for a source with this bit&n; * set indicates a special machine specific interrupt source.&n; * The machine specific files define these sources.&n; *&n; * The IRQ_MACHSPEC bit is now gone - the only thing it did was to&n; * introduce unnecessary overhead.&n; *&n; * All interrupt handling is actually machine specific so it is better&n; * to use function pointers, as used by the Sparc port, and select the&n; * interrupt handling functions when initializing the kernel. This way&n; * we save some unnecessary overhead at run-time. &n; *                                                      01/11/97 - Jes&n; */
r_extern
r_void
(paren
op_star
id|mach_enable_irq
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
id|mach_disable_irq
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sys_request_irq
c_func
(paren
r_int
r_int
comma
id|irqreturn_t
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
macro_line|#ifdef CONFIG_M68360
DECL|macro|CPM_INTERRUPT
mdefine_line|#define CPM_INTERRUPT    IRQ4
multiline_comment|/* see MC68360 User&squot;s Manual, p. 7-377  */
DECL|macro|CPM_VECTOR_BASE
mdefine_line|#define CPM_VECTOR_BASE  0x04           /* 3 MSbits of CPM vector */
macro_line|#endif /* CONFIG_M68360 */
multiline_comment|/*&n; * This structure is used to chain together the ISRs for a particular&n; * interrupt source (if it supports chaining).&n; */
DECL|struct|irq_node
r_typedef
r_struct
id|irq_node
(brace
DECL|member|handler
id|irqreturn_t
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
id|irqreturn_t
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
multiline_comment|/*&n; * Some drivers want these entry points&n; */
DECL|macro|enable_irq
mdefine_line|#define enable_irq(x)&t;(mach_enable_irq  ? (*mach_enable_irq)(x)  : 0)
DECL|macro|disable_irq
mdefine_line|#define disable_irq(x)&t;(mach_disable_irq ? (*mach_disable_irq)(x) : 0)
DECL|macro|enable_irq_nosync
mdefine_line|#define enable_irq_nosync(x)&t;enable_irq(x)
DECL|macro|disable_irq_nosync
mdefine_line|#define disable_irq_nosync(x)&t;disable_irq(x)
macro_line|#endif /* _M68K_IRQ_H_ */
eof
