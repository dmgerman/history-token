multiline_comment|/*&n; * arch/v850/kernel/irq.c -- High-level interrupt handling&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *  Copyright (C) 1994-2000  Ralf Baechle&n; *  Copyright (C) 1992  Linus Torvalds&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * This file was was derived from the mips version, arch/mips/kernel/irq.c&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Controller mappings for all interrupt sources:&n; */
DECL|variable|__cacheline_aligned
id|irq_desc_t
id|irq_desc
(braket
id|NR_IRQS
)braket
id|__cacheline_aligned
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|NR_IRQS
op_minus
l_int|1
)braket
op_assign
(brace
l_int|0
comma
op_amp
id|no_irq_type
comma
l_int|NULL
comma
l_int|0
comma
id|SPIN_LOCK_UNLOCKED
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Special irq handlers.&n; */
DECL|function|no_action
id|irqreturn_t
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
(brace
)brace
multiline_comment|/*&n; * Generic no controller code&n; */
DECL|function|enable_none
r_static
r_void
id|enable_none
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|startup_none
r_static
r_int
r_int
id|startup_none
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|disable_none
r_static
r_void
id|disable_none
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|ack_none
r_static
r_void
id|ack_none
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
multiline_comment|/*&n;&t; * &squot;what should we do if we get a hw irq event on an illegal vector&squot;.&n;&t; * each architecture has to answer this themselves, it doesn&squot;t deserve&n;&t; * a generic callback i think.&n;&t; */
id|printk
c_func
(paren
l_string|&quot;received IRQ %d with unknown interrupt type&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/* startup is the same as &quot;enable&quot;, shutdown is same as &quot;disable&quot; */
DECL|macro|shutdown_none
mdefine_line|#define shutdown_none&t;disable_none
DECL|macro|end_none
mdefine_line|#define end_none&t;enable_none
DECL|variable|no_irq_type
r_struct
id|hw_interrupt_type
id|no_irq_type
op_assign
(brace
l_string|&quot;none&quot;
comma
id|startup_none
comma
id|shutdown_none
comma
id|enable_none
comma
id|disable_none
comma
id|ack_none
comma
id|end_none
)brace
suffix:semicolon
DECL|variable|irq_err_count
DECL|variable|spurious_count
r_volatile
r_int
r_int
id|irq_err_count
comma
id|spurious_count
suffix:semicolon
multiline_comment|/*&n; * Generic, controller-independent functions:&n; */
DECL|function|show_interrupts
r_int
id|show_interrupts
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;           &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|1
multiline_comment|/*smp_num_cpus*/
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;CPU%d       &quot;
comma
id|i
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|j
comma
id|count
comma
id|num
suffix:semicolon
r_const
r_char
op_star
id|type_name
op_assign
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_member_access_from_pointer
r_typename
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_desc
(braket
id|j
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
id|action
op_assign
id|irq_desc
(braket
id|i
)braket
dot
id|action
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_goto
id|skip
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|num
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_IRQS
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|irq_desc
(braket
id|j
)braket
dot
id|handler
op_member_access_from_pointer
r_typename
op_eq
id|type_name
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
id|j
)paren
id|num
op_assign
id|count
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%3d: &quot;
comma
id|i
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%10u &quot;
comma
id|kstat_irqs
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|1
)paren
(brace
r_int
id|prec
op_assign
(paren
id|num
op_ge
l_int|100
ques
c_cond
l_int|3
suffix:colon
id|num
op_ge
l_int|10
ques
c_cond
l_int|2
suffix:colon
l_int|1
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; %*s%d&quot;
comma
l_int|14
op_minus
id|prec
comma
id|type_name
comma
id|num
)paren
suffix:semicolon
)brace
r_else
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; %14s&quot;
comma
id|type_name
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;  %s&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|action
op_assign
id|action-&gt;next
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;, %s&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|skip
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_desc
(braket
id|j
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;ERR: %10lu&bslash;n&quot;
comma
id|irq_err_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This should really return information about whether&n; * we should do bottom half handling etc. Right now we&n; * end up _always_ checking the bottom half, which is a&n; * waste of time and is not what some drivers would&n; * prefer.&n; */
DECL|function|handle_IRQ_event
r_int
id|handle_IRQ_event
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|irqaction
op_star
id|action
)paren
(brace
r_int
id|status
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Force the &quot;do bottom halves&quot; bit */
r_if
c_cond
(paren
op_logical_neg
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|status
op_or_assign
id|action-&gt;flags
suffix:semicolon
id|action
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|action-&gt;dev_id
comma
id|regs
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic enable/disable code: this just calls&n; * down into the PIC-specific version for the actual&n; * hardware disable after having gotten the irq&n; * controller lock. &n; */
multiline_comment|/**&n; *&t;disable_irq_nosync - disable an irq without waiting&n; *&t;@irq: Interrupt to disable&n; *&n; *&t;Disable the selected interrupt line. Disables of an interrupt&n; *&t;stack. Unlike disable_irq(), this function does not ensure existing&n; *&t;instances of the IRQ handler have completed before returning.&n; *&n; *&t;This function may be called from IRQ context.&n; */
DECL|function|disable_irq_nosync
r_void
r_inline
id|disable_irq_nosync
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc-&gt;depth
op_increment
)paren
(brace
id|desc-&gt;status
op_or_assign
id|IRQ_DISABLED
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|disable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;disable_irq - disable an irq and wait for completion&n; *&t;@irq: Interrupt to disable&n; *&n; *&t;Disable the selected interrupt line. Disables of an interrupt&n; *&t;stack. That is for two disables you need two enables. This&n; *&t;function waits for any pending IRQ handlers for this interrupt&n; *&t;to complete before returning. If you use this function while&n; *&t;holding a resource the IRQ handler may need you will deadlock.&n; *&n; *&t;This function may be called - with care - from IRQ context.&n; */
DECL|function|disable_irq
r_void
id|disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_irq_nosync
c_func
(paren
id|irq
)paren
suffix:semicolon
id|synchronize_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;enable_irq - enable interrupt handling on an irq&n; *&t;@irq: Interrupt to enable&n; *&n; *&t;Re-enables the processing of interrupts on this IRQ line&n; *&t;providing no disable_irq calls are now in effect.&n; *&n; *&t;This function may be called from IRQ context.&n; */
DECL|function|enable_irq
r_void
id|enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|desc-&gt;depth
)paren
(brace
r_case
l_int|1
suffix:colon
(brace
r_int
r_int
id|status
op_assign
id|desc-&gt;status
op_amp
op_complement
id|IRQ_DISABLED
suffix:semicolon
id|desc-&gt;status
op_assign
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
(paren
id|IRQ_PENDING
op_or
id|IRQ_REPLAY
)paren
)paren
op_eq
id|IRQ_PENDING
)paren
(brace
id|desc-&gt;status
op_assign
id|status
op_or
id|IRQ_REPLAY
suffix:semicolon
id|hw_resend_irq
c_func
(paren
id|desc-&gt;handler
comma
id|irq
)paren
suffix:semicolon
)brace
id|desc-&gt;handler
op_member_access_from_pointer
id|enable
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* fall-through */
)brace
r_default
suffix:colon
id|desc-&gt;depth
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
l_string|&quot;enable_irq(%u) unbalanced from %p&bslash;n&quot;
comma
id|irq
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Handle interrupt IRQ.  REGS are the registers at the time of ther&n;   interrupt.  */
DECL|function|handle_irq
r_int
r_int
id|handle_irq
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* &n;&t; * We ack quickly, we don&squot;t want the irq controller&n;&t; * thinking we&squot;re snobs just because some other CPU has&n;&t; * disabled global interrupts (we have already done the&n;&t; * INT_ACK cycles, it&squot;s too late to try to pretend to the&n;&t; * controller that we aren&squot;t taking the interrupt).&n;&t; *&n;&t; * 0 return value means that this irq is already being&n;&t; * handled by some other CPU. (or is disabled)&n;&t; */
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|ack
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   REPLAY is when Linux resends an IRQ that was dropped earlier&n;&t;   WAITING is used by probe to mark irqs that are being tested&n;&t;   */
id|status
op_assign
id|desc-&gt;status
op_amp
op_complement
(paren
id|IRQ_REPLAY
op_or
id|IRQ_WAITING
)paren
suffix:semicolon
id|status
op_or_assign
id|IRQ_PENDING
suffix:semicolon
multiline_comment|/* we _want_ to handle it */
multiline_comment|/*&n;&t; * If the IRQ is disabled for whatever reason, we cannot&n;&t; * use the action we have.&n;&t; */
id|action
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
(paren
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
)paren
(brace
id|action
op_assign
id|desc-&gt;action
suffix:semicolon
id|status
op_and_assign
op_complement
id|IRQ_PENDING
suffix:semicolon
multiline_comment|/* we commit to handling */
id|status
op_or_assign
id|IRQ_INPROGRESS
suffix:semicolon
multiline_comment|/* we are handling it */
)brace
id|desc-&gt;status
op_assign
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * If there is no IRQ handler or it was disabled, exit early.&n;&t;   Since we set PENDING, if another processor is handling&n;&t;   a different instance of this same irq, the other processor&n;&t;   will take care of it.&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|action
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Edge triggered interrupts need to remember&n;&t; * pending events.&n;&t; * This applies to any hw interrupts that allow a second&n;&t; * instance of the same irq to arrive while we are in handle_irq&n;&t; * or in the handler. But the code here only handles the _second_&n;&t; * instance of the irq, not the third or fourth. So it is mostly&n;&t; * useful for irq hardware that does not mask cleanly in an&n;&t; * SMP environment.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|handle_IRQ_event
c_func
(paren
id|irq
comma
id|regs
comma
id|action
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
(paren
id|desc-&gt;status
op_amp
id|IRQ_PENDING
)paren
)paren
)paren
r_break
suffix:semicolon
id|desc-&gt;status
op_and_assign
op_complement
id|IRQ_PENDING
suffix:semicolon
)brace
id|desc-&gt;status
op_and_assign
op_complement
id|IRQ_INPROGRESS
suffix:semicolon
id|out
suffix:colon
multiline_comment|/*&n;&t; * The -&gt;end() handler has to deal with interrupts which got&n;&t; * disabled while the handler was running.&n;&t; */
id|desc-&gt;handler
op_member_access_from_pointer
id|end
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;request_irq - allocate an interrupt line&n; *&t;@irq: Interrupt line to allocate&n; *&t;@handler: Function to be called when the IRQ occurs&n; *&t;@irqflags: Interrupt type flags&n; *&t;@devname: An ascii name for the claiming device&n; *&t;@dev_id: A cookie passed back to the handler function&n; *&n; *&t;This call allocates interrupt resources and enables the&n; *&t;interrupt line and IRQ handling. From the point this&n; *&t;call is made your handler function may be invoked. Since&n; *&t;your handler function must clear any interrupt the board &n; *&t;raises, you must take care both to initialise your hardware&n; *&t;and to set up the interrupt handler in the right order.&n; *&n; *&t;Dev_id must be globally unique. Normally the address of the&n; *&t;device data structure is used as the cookie. Since the handler&n; *&t;receives this value it makes sense to use it.&n; *&n; *&t;If your interrupt is shared you must pass a non NULL dev_id&n; *&t;as this is required when freeing the interrupt.&n; *&n; *&t;Flags:&n; *&n; *&t;SA_SHIRQ&t;&t;Interrupt is shared&n; *&n; *&t;SA_INTERRUPT&t;&t;Disable local interrupts while processing&n; *&n; *&t;SA_SAMPLE_RANDOM&t;The interrupt can be used for entropy&n; *&n; */
DECL|function|request_irq
r_int
id|request_irq
c_func
(paren
r_int
r_int
id|irq
comma
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
comma
r_int
r_int
id|irqflags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
(brace
r_int
id|retval
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
macro_line|#if 1
multiline_comment|/*&n;&t; * Sanity-check: shared interrupts should REALLY pass in&n;&t; * a real dev-ID, otherwise we&squot;ll have trouble later trying&n;&t; * to figure out which interrupt is which (messes up the&n;&t; * interrupt freeing logic etc).&n;&t; */
r_if
c_cond
(paren
id|irqflags
op_amp
id|SA_SHIRQ
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev_id
)paren
id|printk
c_func
(paren
l_string|&quot;Bad boy: %s (at 0x%x) called us without a dev_id!&bslash;n&quot;
comma
id|devname
comma
(paren
op_amp
id|irq
)paren
(braket
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|irq
op_ge
id|NR_IRQS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|action
op_assign
(paren
r_struct
id|irqaction
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irqaction
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|action-&gt;handler
op_assign
id|handler
suffix:semicolon
id|action-&gt;flags
op_assign
id|irqflags
suffix:semicolon
id|action-&gt;mask
op_assign
l_int|0
suffix:semicolon
id|action-&gt;name
op_assign
id|devname
suffix:semicolon
id|action-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|action-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
id|retval
op_assign
id|setup_irq
c_func
(paren
id|irq
comma
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;free_irq - free an interrupt&n; *&t;@irq: Interrupt line to free&n; *&t;@dev_id: Device identity to free&n; *&n; *&t;Remove an interrupt handler. The handler is removed and if the&n; *&t;interrupt line is no longer in use by any driver it is disabled.&n; *&t;On a shared IRQ the caller must ensure the interrupt is disabled&n; *&t;on the card it drives before calling this function. The function&n; *&t;does not return until any executing interrupts for this IRQ&n; *&t;have completed.&n; *&n; *&t;This function may be called from interrupt context. &n; *&n; *&t;Bugs: Attempting to free an irq in a handler for the same irq hangs&n; *&t;      the machine.&n; */
DECL|function|free_irq
r_void
id|free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
id|irq_desc_t
op_star
id|desc
suffix:semicolon
r_struct
id|irqaction
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|NR_IRQS
)paren
r_return
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|desc-&gt;action
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|irqaction
op_star
id|action
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
(brace
r_struct
id|irqaction
op_star
op_star
id|pp
op_assign
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|action-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;dev_id
op_ne
id|dev_id
)paren
r_continue
suffix:semicolon
multiline_comment|/* Found it - now remove it from the list of entries */
op_star
id|pp
op_assign
id|action-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc-&gt;action
)paren
(brace
id|desc-&gt;status
op_or_assign
id|IRQ_DISABLED
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|synchronize_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to free free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * IRQ autodetection code..&n; *&n; * This depends on the fact that any interrupt that&n; * comes in on to an unassigned handler will get stuck&n; * with &quot;IRQ_WAITING&quot; cleared and the interrupt&n; * disabled.&n; */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|probe_sem
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;probe_irq_on&t;- begin an interrupt autodetect&n; *&n; *&t;Commence probing for an interrupt. The interrupts are scanned&n; *&t;and a mask of potential interrupt lines is returned.&n; *&n; */
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|irq_desc_t
op_star
id|desc
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_int
r_int
id|delay
suffix:semicolon
id|down
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * something may have generated an irq long ago and we want to&n;&t; * flush such a longstanding irq before considering it as spurious. &n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|NR_IRQS
op_minus
l_int|1
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq_desc
(braket
id|i
)braket
dot
id|action
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_member_access_from_pointer
id|startup
c_func
(paren
id|i
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Wait for longstanding interrupts to trigger. */
r_for
c_loop
(paren
id|delay
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|50
suffix:semicolon
id|time_after
c_func
(paren
id|delay
comma
id|jiffies
)paren
suffix:semicolon
)paren
multiline_comment|/* about 20ms delay */
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * enable any unassigned irqs&n;&t; * (we must startup again here because if a longstanding irq&n;&t; * happened in the previous stage, it may have masked itself)&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|NR_IRQS
op_minus
l_int|1
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc-&gt;action
)paren
(brace
id|desc-&gt;status
op_or_assign
id|IRQ_AUTODETECT
op_or
id|IRQ_WAITING
suffix:semicolon
r_if
c_cond
(paren
id|desc-&gt;handler
op_member_access_from_pointer
id|startup
c_func
(paren
id|i
)paren
)paren
id|desc-&gt;status
op_or_assign
id|IRQ_PENDING
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Wait for spurious interrupts to trigger&n;&t; */
r_for
c_loop
(paren
id|delay
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|10
suffix:semicolon
id|time_after
c_func
(paren
id|delay
comma
id|jiffies
)paren
suffix:semicolon
)paren
multiline_comment|/* about 100ms delay */
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now filter out any obviously spurious interrupts&n;&t; */
id|val
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|status
op_assign
id|desc-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IRQ_AUTODETECT
)paren
(brace
multiline_comment|/* It triggered already - consider it spurious. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|IRQ_WAITING
)paren
)paren
(brace
id|desc-&gt;status
op_assign
id|status
op_amp
op_complement
id|IRQ_AUTODETECT
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
OL
l_int|32
)paren
id|val
op_or_assign
l_int|1
op_lshift
id|i
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * Return a mask of triggered interrupts (this&n; * can handle only legacy ISA interrupts).&n; */
multiline_comment|/**&n; *&t;probe_irq_mask - scan a bitmap of interrupt lines&n; *&t;@val:&t;mask of interrupts to consider&n; *&n; *&t;Scan the ISA bus interrupt lines and return a bitmap of&n; *&t;active interrupts. The interrupt probe logic state is then&n; *&t;returned to its previous value.&n; *&n; *&t;Note: we need to scan all the irq&squot;s even though we will&n; *&t;only return ISA irq numbers - just so that we reset them&n; *&t;all to a known state.&n; */
DECL|function|probe_irq_mask
r_int
r_int
id|probe_irq_mask
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
id|mask
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|status
op_assign
id|desc-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IRQ_AUTODETECT
)paren
(brace
r_if
c_cond
(paren
id|i
OL
l_int|16
op_logical_and
op_logical_neg
(paren
id|status
op_amp
id|IRQ_WAITING
)paren
)paren
id|mask
op_or_assign
l_int|1
op_lshift
id|i
suffix:semicolon
id|desc-&gt;status
op_assign
id|status
op_amp
op_complement
id|IRQ_AUTODETECT
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
r_return
id|mask
op_amp
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the one interrupt that triggered (this can&n; * handle any interrupt source).&n; */
multiline_comment|/**&n; *&t;probe_irq_off&t;- end an interrupt autodetect&n; *&t;@val: mask of potential interrupts (unused)&n; *&n; *&t;Scans the unused interrupt lines and returns the line which&n; *&t;appears to have triggered the interrupt. If no interrupt was&n; *&t;found then zero is returned. If more than one interrupt is&n; *&t;found then minus the first candidate is returned to indicate&n; *&t;their is doubt.&n; *&n; *&t;The interrupt probe logic state is returned to its previous&n; *&t;value.&n; *&n; *&t;BUGS: When used in a module (which arguably shouldnt happen)&n; *&t;nothing prevents two IRQ probe callers from overlapping. The&n; *&t;results of this are non-optimal.&n; */
DECL|function|probe_irq_off
r_int
id|probe_irq_off
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_int
id|i
comma
id|irq_found
comma
id|nr_irqs
suffix:semicolon
id|nr_irqs
op_assign
l_int|0
suffix:semicolon
id|irq_found
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|status
op_assign
id|desc-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IRQ_AUTODETECT
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|IRQ_WAITING
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nr_irqs
)paren
id|irq_found
op_assign
id|i
suffix:semicolon
id|nr_irqs
op_increment
suffix:semicolon
)brace
id|desc-&gt;status
op_assign
id|status
op_amp
op_complement
id|IRQ_AUTODETECT
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_irqs
OG
l_int|1
)paren
id|irq_found
op_assign
op_minus
id|irq_found
suffix:semicolon
r_return
id|irq_found
suffix:semicolon
)brace
multiline_comment|/* this was setup_x86_irq but it seems pretty generic */
DECL|function|setup_irq
r_int
id|setup_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqaction
op_star
r_new
)paren
(brace
r_int
id|shared
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|irqaction
op_star
id|old
comma
op_star
op_star
id|p
suffix:semicolon
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
multiline_comment|/*&n;&t; * Some drivers like serial.c use request_irq() heavily,&n;&t; * so we have to be careful not to interfere with a&n;&t; * running system.&n;&t; */
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
(brace
multiline_comment|/*&n;&t;&t; * This function might sleep, we want to call it first,&n;&t;&t; * outside of the atomic block.&n;&t;&t; * Yes, this might clear the entropy pool if the wrong&n;&t;&t; * driver is attempted to be loaded, without actually&n;&t;&t; * installing a new handler, but is this really a problem,&n;&t;&t; * only the sysadmin is able to do this.&n;&t;&t; */
id|rand_initialize_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The following block of code has to be executed atomically&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|desc-&gt;action
suffix:semicolon
r_if
c_cond
(paren
(paren
id|old
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Can&squot;t share interrupts unless both agree to */
r_if
c_cond
(paren
op_logical_neg
(paren
id|old-&gt;flags
op_amp
r_new
op_member_access_from_pointer
id|flags
op_amp
id|SA_SHIRQ
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* add new interrupt at end of irq queue */
r_do
(brace
id|p
op_assign
op_amp
id|old-&gt;next
suffix:semicolon
id|old
op_assign
op_star
id|p
suffix:semicolon
)brace
r_while
c_loop
(paren
id|old
)paren
suffix:semicolon
id|shared
op_assign
l_int|1
suffix:semicolon
)brace
op_star
id|p
op_assign
r_new
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shared
)paren
(brace
id|desc-&gt;depth
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;status
op_and_assign
op_complement
(paren
id|IRQ_DISABLED
op_or
id|IRQ_AUTODETECT
op_or
id|IRQ_WAITING
op_or
id|IRQ_INPROGRESS
)paren
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|startup
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* register_irq_proc(irq); */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Initialize irq handling for IRQs.&n;   BASE_IRQ, BASE_IRQ+INTERVAL, ..., BASE_IRQ+NUM*INTERVAL&n;   to IRQ_TYPE.  An IRQ_TYPE of 0 means to use a generic interrupt type.  */
r_void
id|__init
DECL|function|init_irq_handlers
id|init_irq_handlers
(paren
r_int
id|base_irq
comma
r_int
id|num
comma
r_int
id|interval
comma
r_struct
id|hw_interrupt_type
op_star
id|irq_type
)paren
(brace
r_while
c_loop
(paren
id|num
op_decrement
OG
l_int|0
)paren
(brace
id|irq_desc
(braket
id|base_irq
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|base_irq
)braket
dot
id|action
op_assign
l_int|NULL
suffix:semicolon
id|irq_desc
(braket
id|base_irq
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|base_irq
)braket
dot
id|handler
op_assign
id|irq_type
suffix:semicolon
id|base_irq
op_add_assign
id|interval
suffix:semicolon
)brace
)brace
macro_line|#if defined(CONFIG_PROC_FS) &amp;&amp; defined(CONFIG_SYSCTL)
DECL|function|init_irq_proc
r_void
id|init_irq_proc
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_PROC_FS &amp;&amp; CONFIG_SYSCTL */
eof
