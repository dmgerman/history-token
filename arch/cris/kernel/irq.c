multiline_comment|/*&n; *&n; *&t;linux/arch/cris/kernel/irq.c&n; *&n; *      Copyright (c) 2000,2001 Axis Communications AB&n; *&n; *      Authors: Bjorn Wesen (bjornw@axis.com)&n; *&n; * This file contains the code used by various IRQ handling routines:&n; * asking for different IRQ&squot;s should be done through these routines&n; * instead of just grabbing them. Thus setups with different IRQ numbers&n; * shouldn&squot;t result in any weird surprises, and installing new handlers&n; * should be easier.&n; *&n; * Notice Linux/CRIS: these routines do not care about SMP&n; *&n; */
multiline_comment|/*&n; * IRQ&squot;s are in fact implemented a bit like signal handlers for the kernel.&n; * Naturally it&squot;s not a 1:1 relation, but there are similarities.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* Defined in arch specific irq.c */
r_extern
r_void
id|arch_setup_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|arch_free_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_void
DECL|function|disable_irq
id|disable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|mask_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_void
DECL|function|enable_irq
id|enable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|probe_irq_on
id|probe_irq_on
c_func
(paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|probe_irq_on
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_on
)paren
suffix:semicolon
r_int
DECL|function|probe_irq_off
id|probe_irq_off
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|probe_irq_off
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_off
)paren
suffix:semicolon
multiline_comment|/*&n; * Initial irq handlers.&n; */
DECL|variable|irq_action
r_static
r_struct
id|irqaction
op_star
id|irq_action
(braket
id|NR_IRQS
)braket
suffix:semicolon
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
op_assign
op_star
(paren
id|loff_t
op_star
)paren
id|v
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
r_if
c_cond
(paren
id|i
OL
id|NR_IRQS
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|action
op_assign
id|irq_action
(braket
id|i
)braket
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
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%2d: %10u %c %s&quot;
comma
id|i
comma
id|kstat_this_cpu.irqs
(braket
id|i
)braket
comma
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot; &squot;
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
(brace
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;,%s %s&quot;
comma
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
ques
c_cond
l_string|&quot; +&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
)brace
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
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* called by the assembler IRQ entry functions defined in irq.h&n; * to dispatch the interrupts to registred handlers&n; * interrupts are disabled upon entry - depending on if the&n; * interrupt was registred with SA_INTERRUPT or not, interrupts&n; * are re-enabled or not.&n; */
DECL|function|do_IRQ
id|asmlinkage
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
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
id|do_random
comma
id|cpu
suffix:semicolon
r_int
id|ret
comma
id|retval
op_assign
l_int|0
suffix:semicolon
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
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
op_minus
id|FIRST_IRQ
)braket
op_increment
suffix:semicolon
id|action
op_assign
id|irq_action
(braket
id|irq
op_minus
id|FIRST_IRQ
)braket
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
(brace
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
id|do_random
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|ret
op_assign
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
r_if
c_cond
(paren
id|ret
op_eq
id|IRQ_HANDLED
)paren
id|do_random
op_or_assign
id|action-&gt;flags
suffix:semicolon
id|retval
op_or_assign
id|ret
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
id|retval
op_ne
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;irq event %d: bogus retval mask %x&bslash;n&quot;
comma
id|irq
comma
id|retval
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;irq %d: nobody cared&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|do_random
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
)brace
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* this function links in a handler into the chain of handlers for the&n;   given irq, and if the irq has never been registred, the appropriate&n;   handler is entered into the interrupt vector&n;*/
DECL|function|setup_irq
r_int
id|setup_irq
c_func
(paren
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
r_struct
id|irqaction
op_star
id|old
comma
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|p
op_assign
id|irq_action
op_plus
id|irq
op_minus
id|FIRST_IRQ
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
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Can&squot;t share interrupts unless both are same type */
r_if
c_cond
(paren
(paren
id|old-&gt;flags
op_xor
r_new
op_member_access_from_pointer
id|flags
)paren
op_amp
id|SA_INTERRUPT
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
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
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|rand_initialize_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
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
multiline_comment|/* if the irq wasn&squot;t registred before, enter it into the vector table&n;&t;&t;   and unmask it physically &n;&t;&t;*/
id|arch_setup_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* this function is called by a driver to register an irq handler&n;   Valid flags:&n;   SA_INTERRUPT -&gt; it&squot;s a fast interrupt, handler called with irq disabled and&n;                   no signal checking etc is performed upon exit&n;   SA_SHIRQ -&gt; the interrupt can be shared between different handlers, the handler&n;                is required to check if the irq was &quot;aimed&quot; at it explicitely&n;   SA_RANDOM -&gt; the interrupt will add to the random generators entropy&n;*/
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
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* allocate and fill in a handler structure and setup the irq */
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
id|cpus_clear
c_func
(paren
id|action-&gt;mask
)paren
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
DECL|variable|request_irq
id|EXPORT_SYMBOL
c_func
(paren
id|request_irq
)paren
suffix:semicolon
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
r_struct
id|irqaction
op_star
id|action
comma
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
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
id|irq
op_minus
id|FIRST_IRQ
op_plus
id|irq_action
suffix:semicolon
(paren
id|action
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
op_amp
id|action-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;dev_id
op_ne
id|dev_id
)paren
r_continue
suffix:semicolon
multiline_comment|/* Found it - now free it */
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
op_star
id|p
op_assign
id|action-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq_action
(braket
id|irq
op_minus
id|FIRST_IRQ
)braket
)paren
(brace
id|mask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|arch_free_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
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
)brace
DECL|variable|free_irq
id|EXPORT_SYMBOL
c_func
(paren
id|free_irq
)paren
suffix:semicolon
DECL|function|weird_irq
r_void
id|weird_irq
c_func
(paren
r_void
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;weird irq&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
macro_line|#if defined(CONFIG_PROC_FS) &amp;&amp; defined(CONFIG_SYSCTL)
multiline_comment|/* Used by other archs to show/control IRQ steering during SMP */
r_void
id|__init
DECL|function|init_irq_proc
id|init_irq_proc
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
eof
