multiline_comment|/* $Id: irq.c,v 1.2 2001/12/18 13:35:20 bjornw Exp $&n; *&n; *&t;linux/arch/cris/kernel/irq.c&n; *&n; *      Copyright (c) 2000,2001 Axis Communications AB&n; *&n; *      Authors: Bjorn Wesen (bjornw@axis.com)&n; *&n; * This file contains the code used by various IRQ handling routines:&n; * asking for different IRQ&squot;s should be done through these routines&n; * instead of just grabbing them. Thus setups with different IRQ numbers&n; * shouldn&squot;t result in any weird surprises, and installing new handlers&n; * should be easier.&n; *&n; * Notice Linux/CRIS: these routines do not care about SMP&n; *&n; */
multiline_comment|/*&n; * IRQ&squot;s are in fact implemented a bit like signal handlers for the kernel.&n; * Naturally it&squot;s not a 1:1 relation, but there are similarities.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
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
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/svinto.h&gt;
DECL|variable|hw_bp_msg
r_char
op_star
id|hw_bp_msg
op_assign
l_string|&quot;BP 0x%x&bslash;n&quot;
suffix:semicolon
r_static
r_inline
r_void
DECL|function|mask_irq
id|mask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
op_star
id|R_VECT_MASK_CLR
op_assign
l_int|1
op_lshift
id|irq_nr
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|unmask_irq
id|unmask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
op_star
id|R_VECT_MASK_SET
op_assign
l_int|1
op_lshift
id|irq_nr
suffix:semicolon
)brace
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
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
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
id|restore_flags
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
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
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
id|restore_flags
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
DECL|variable|irq_shortcuts
id|irqvectptr
id|irq_shortcuts
(braket
id|NR_IRQS
)braket
suffix:semicolon
multiline_comment|/* vector of shortcut jumps after the irq prologue */
multiline_comment|/* don&squot;t use set_int_vector, it bypasses the linux interrupt handlers. it is&n; * global just so that the kernel gdb can use it.&n; */
r_void
DECL|function|set_int_vector
id|set_int_vector
c_func
(paren
r_int
id|n
comma
id|irqvectptr
id|addr
comma
id|irqvectptr
id|saddr
)paren
(brace
multiline_comment|/* remember the shortcut entry point, after the prologue */
id|irq_shortcuts
(braket
id|n
)braket
op_assign
id|saddr
suffix:semicolon
id|etrax_irv-&gt;v
(braket
id|n
op_plus
l_int|0x20
)braket
op_assign
(paren
id|irqvectptr
)paren
id|addr
suffix:semicolon
)brace
multiline_comment|/* the breakpoint vector is obviously not made just like the normal irq handlers&n; * but needs to contain _code_ to jump to addr.&n; *&n; * the BREAK n instruction jumps to IBR + n * 8&n; */
r_void
DECL|function|set_break_vector
id|set_break_vector
c_func
(paren
r_int
id|n
comma
id|irqvectptr
id|addr
)paren
(brace
r_int
r_int
op_star
id|jinstr
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|etrax_irv-&gt;v
(braket
id|n
op_star
l_int|2
)braket
suffix:semicolon
r_int
r_int
op_star
id|jaddr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|jinstr
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* if you don&squot;t know what this does, do not touch it! */
op_star
id|jinstr
op_assign
l_int|0x0d3f
suffix:semicolon
op_star
id|jaddr
op_assign
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
multiline_comment|/* 00000026 &lt;clrlop+1a&gt; 3f0d82000000     jump  0x82 */
)brace
multiline_comment|/*&n; * This builds up the IRQ handler stubs using some ugly macros in irq.h&n; *&n; * These macros create the low-level assembly IRQ routines that do all&n; * the operations that are needed. They are also written to be fast - and to&n; * disable interrupts as little as humanly possible.&n; *&n; */
multiline_comment|/* IRQ0 and 1 are special traps */
r_void
id|hwbreakpoint
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|IRQ1_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
id|BUILD_TIMER_IRQ
c_func
(paren
l_int|2
comma
l_int|0x04
)paren
multiline_comment|/* the timer interrupt is somewhat special */
id|BUILD_IRQ
c_func
(paren
l_int|3
comma
l_int|0x08
)paren
id|BUILD_IRQ
c_func
(paren
l_int|4
comma
l_int|0x10
)paren
id|BUILD_IRQ
c_func
(paren
l_int|5
comma
l_int|0x20
)paren
id|BUILD_IRQ
c_func
(paren
l_int|6
comma
l_int|0x40
)paren
id|BUILD_IRQ
c_func
(paren
l_int|7
comma
l_int|0x80
)paren
id|BUILD_IRQ
c_func
(paren
l_int|8
comma
l_int|0x100
)paren
id|BUILD_IRQ
c_func
(paren
l_int|9
comma
l_int|0x200
)paren
id|BUILD_IRQ
c_func
(paren
l_int|10
comma
l_int|0x400
)paren
id|BUILD_IRQ
c_func
(paren
l_int|11
comma
l_int|0x800
)paren
id|BUILD_IRQ
c_func
(paren
l_int|12
comma
l_int|0x1000
)paren
id|BUILD_IRQ
c_func
(paren
l_int|13
comma
l_int|0x2000
)paren
r_void
id|mmu_bus_fault
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* IRQ 14 is the bus fault interrupt */
r_void
id|multiple_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* IRQ 15 is the multiple IRQ interrupt */
id|BUILD_IRQ
c_func
(paren
l_int|16
comma
l_int|0x10000
)paren
id|BUILD_IRQ
c_func
(paren
l_int|17
comma
l_int|0x20000
)paren
id|BUILD_IRQ
c_func
(paren
l_int|18
comma
l_int|0x40000
)paren
id|BUILD_IRQ
c_func
(paren
l_int|19
comma
l_int|0x80000
)paren
id|BUILD_IRQ
c_func
(paren
l_int|20
comma
l_int|0x100000
)paren
id|BUILD_IRQ
c_func
(paren
l_int|21
comma
l_int|0x200000
)paren
id|BUILD_IRQ
c_func
(paren
l_int|22
comma
l_int|0x400000
)paren
id|BUILD_IRQ
c_func
(paren
l_int|23
comma
l_int|0x800000
)paren
id|BUILD_IRQ
c_func
(paren
l_int|24
comma
l_int|0x1000000
)paren
id|BUILD_IRQ
c_func
(paren
l_int|25
comma
l_int|0x2000000
)paren
multiline_comment|/* IRQ 26-30 are reserved */
id|BUILD_IRQ
c_func
(paren
l_int|31
comma
l_int|0x80000000
)paren
multiline_comment|/*&n; * Pointers to the low-level handlers &n; */
DECL|variable|interrupt
r_static
r_void
(paren
op_star
id|interrupt
(braket
id|NR_IRQS
)braket
)paren
(paren
r_void
)paren
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
id|IRQ2_interrupt
comma
id|IRQ3_interrupt
comma
id|IRQ4_interrupt
comma
id|IRQ5_interrupt
comma
id|IRQ6_interrupt
comma
id|IRQ7_interrupt
comma
id|IRQ8_interrupt
comma
id|IRQ9_interrupt
comma
id|IRQ10_interrupt
comma
id|IRQ11_interrupt
comma
id|IRQ12_interrupt
comma
id|IRQ13_interrupt
comma
l_int|NULL
comma
l_int|NULL
comma
id|IRQ16_interrupt
comma
id|IRQ17_interrupt
comma
id|IRQ18_interrupt
comma
id|IRQ19_interrupt
comma
id|IRQ20_interrupt
comma
id|IRQ21_interrupt
comma
id|IRQ22_interrupt
comma
id|IRQ23_interrupt
comma
id|IRQ24_interrupt
comma
id|IRQ25_interrupt
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|IRQ31_interrupt
)brace
suffix:semicolon
DECL|variable|sinterrupt
r_static
r_void
(paren
op_star
id|sinterrupt
(braket
id|NR_IRQS
)braket
)paren
(paren
r_void
)paren
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
id|sIRQ2_interrupt
comma
id|sIRQ3_interrupt
comma
id|sIRQ4_interrupt
comma
id|sIRQ5_interrupt
comma
id|sIRQ6_interrupt
comma
id|sIRQ7_interrupt
comma
id|sIRQ8_interrupt
comma
id|sIRQ9_interrupt
comma
id|sIRQ10_interrupt
comma
id|sIRQ11_interrupt
comma
id|sIRQ12_interrupt
comma
id|sIRQ13_interrupt
comma
l_int|NULL
comma
l_int|NULL
comma
id|sIRQ16_interrupt
comma
id|sIRQ17_interrupt
comma
id|sIRQ18_interrupt
comma
id|sIRQ19_interrupt
comma
id|sIRQ20_interrupt
comma
id|sIRQ21_interrupt
comma
id|sIRQ22_interrupt
comma
id|sIRQ23_interrupt
comma
id|sIRQ24_interrupt
comma
id|sIRQ25_interrupt
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|sIRQ31_interrupt
)brace
suffix:semicolon
DECL|variable|bad_interrupt
r_static
r_void
(paren
op_star
id|bad_interrupt
(braket
id|NR_IRQS
)braket
)paren
(paren
r_void
)paren
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|bad_IRQ3_interrupt
comma
id|bad_IRQ4_interrupt
comma
id|bad_IRQ5_interrupt
comma
id|bad_IRQ6_interrupt
comma
id|bad_IRQ7_interrupt
comma
id|bad_IRQ8_interrupt
comma
id|bad_IRQ9_interrupt
comma
id|bad_IRQ10_interrupt
comma
id|bad_IRQ11_interrupt
comma
id|bad_IRQ12_interrupt
comma
id|bad_IRQ13_interrupt
comma
l_int|NULL
comma
l_int|NULL
comma
id|bad_IRQ16_interrupt
comma
id|bad_IRQ17_interrupt
comma
id|bad_IRQ18_interrupt
comma
id|bad_IRQ19_interrupt
comma
id|bad_IRQ20_interrupt
comma
id|bad_IRQ21_interrupt
comma
id|bad_IRQ22_interrupt
comma
id|bad_IRQ23_interrupt
comma
id|bad_IRQ24_interrupt
comma
id|bad_IRQ25_interrupt
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|bad_IRQ31_interrupt
)brace
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
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
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
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
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
r_continue
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
id|kstat.irqs
(braket
l_int|0
)braket
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
id|cpu
)paren
suffix:semicolon
id|kstat.irqs
(braket
id|cpu
)braket
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|action
op_assign
id|irq_action
(braket
id|irq
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
id|__sti
c_func
(paren
)paren
suffix:semicolon
id|action
op_assign
id|irq_action
(braket
id|irq
)braket
suffix:semicolon
id|do_random
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|do_random
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
id|__cli
c_func
(paren
)paren
suffix:semicolon
)brace
id|irq_exit
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|softirq_pending
c_func
(paren
id|cpu
)paren
)paren
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* unmasking and bottom half handling is done magically for us. */
)brace
multiline_comment|/* this function links in a handler into the chain of handlers for the&n;   given irq, and if the irq has never been registred, the appropriate&n;   handler is entered into the interrupt vector&n;*/
DECL|function|setup_etrax_irq
r_int
id|setup_etrax_irq
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
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
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
id|set_int_vector
c_func
(paren
id|irq
comma
id|interrupt
(braket
id|irq
)braket
comma
id|sinterrupt
(braket
id|irq
)braket
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|restore_flags
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
multiline_comment|/* interrupts 0 and 1 are hardware breakpoint and NMI and we can&squot;t support&n;&t;   these yet. interrupt 15 is the multiple irq, it&squot;s special. */
r_if
c_cond
(paren
id|irq
OL
l_int|2
op_logical_or
id|irq
op_eq
l_int|15
op_logical_or
id|irq
op_ge
id|NR_IRQS
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
id|setup_etrax_irq
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
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
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
)braket
)paren
(brace
id|mask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|set_int_vector
c_func
(paren
id|irq
comma
id|bad_interrupt
(braket
id|irq
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
id|restore_flags
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
DECL|function|weird_irq
r_void
id|weird_irq
c_func
(paren
r_void
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;di&quot;
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
multiline_comment|/* init_IRQ() is called by start_kernel and is responsible for fixing IRQ masks and&n;   setting the irq vector table to point to bad_interrupt ptrs.&n;*/
r_void
id|system_call
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* from entry.S */
r_void
id|do_sigtrap
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* from entry.S */
r_void
id|gdb_handle_breakpoint
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* from entry.S */
r_void
id|__init
DECL|function|init_IRQ
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* clear all interrupt masks */
macro_line|#ifndef CONFIG_SVINTO_SIM
op_star
id|R_IRQ_MASK0_CLR
op_assign
l_int|0xffffffff
suffix:semicolon
op_star
id|R_IRQ_MASK1_CLR
op_assign
l_int|0xffffffff
suffix:semicolon
op_star
id|R_IRQ_MASK2_CLR
op_assign
l_int|0xffffffff
suffix:semicolon
macro_line|#endif
op_star
id|R_VECT_MASK_CLR
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* clear the shortcut entry points */
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
id|irq_shortcuts
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
id|etrax_irv-&gt;v
(braket
id|i
)braket
op_assign
id|weird_irq
suffix:semicolon
multiline_comment|/* the entries in the break vector contain actual code to be&n;           executed by the associated break handler, rather than just a jump&n;           address. therefore we need to setup a default breakpoint handler&n;           for all breakpoints */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|set_break_vector
c_func
(paren
id|i
comma
id|do_sigtrap
)paren
suffix:semicolon
multiline_comment|/* set all etrax irq&squot;s to the bad handlers */
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
id|set_int_vector
c_func
(paren
id|i
comma
id|bad_interrupt
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* except IRQ 15 which is the multiple-IRQ handler on Etrax100 */
id|set_int_vector
c_func
(paren
l_int|15
comma
id|multiple_interrupt
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 0 and 1 which are special breakpoint/NMI traps */
id|set_int_vector
c_func
(paren
l_int|0
comma
id|hwbreakpoint
comma
l_int|0
)paren
suffix:semicolon
id|set_int_vector
c_func
(paren
l_int|1
comma
id|IRQ1_interrupt
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* and irq 14 which is the mmu bus fault handler */
id|set_int_vector
c_func
(paren
l_int|14
comma
id|mmu_bus_fault
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* setup the system-call trap, which is reached by BREAK 13 */
id|set_break_vector
c_func
(paren
l_int|13
comma
id|system_call
)paren
suffix:semicolon
multiline_comment|/* setup a breakpoint handler for debugging used for both user and&n;           kernel mode debugging  (which is why it is not inside an ifdef&n;           CONFIG_ETRAX_KGDB) */
id|set_break_vector
c_func
(paren
l_int|8
comma
id|gdb_handle_breakpoint
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ETRAX_KGDB
multiline_comment|/* setup kgdb if its enabled, and break into the debugger */
id|kgdb_init
c_func
(paren
)paren
suffix:semicolon
id|breakpoint
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
