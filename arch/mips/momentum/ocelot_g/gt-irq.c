multiline_comment|/*&n; *&n; * Copyright 2002 Momentum Computer&n; * Author: mdharm@momenco.com&n; *&n; * arch/mips/momentum/ocelot_g/gt_irq.c&n; *     Interrupt routines for gt64240.  Currently it only handles timer irq.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;gt64240.h&quot;
DECL|variable|bus_clock
r_int
r_int
id|bus_clock
suffix:semicolon
multiline_comment|/*&n; * These are interrupt handlers for the GT on-chip interrupts.  They&n; * all come in to the MIPS on a single interrupt line, and have to&n; * be handled and ack&squot;ed differently than other MIPS interrupts.&n; */
macro_line|#if CURRENTLY_UNUSED
DECL|variable|irq_handlers
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
r_void
id|hook_irq_handler
c_func
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
multiline_comment|/*&n; * Hooks IRQ handler to the system. When the system is interrupted&n; * the interrupt service routine is called.&n; *&n; * Inputs :&n; * int_cause - The interrupt cause number. In EVB64120 two parameters&n; *             are declared, INT_CAUSE_MAIN and INT_CAUSE_HIGH.&n; * bit_num   - Indicates which bit number in the cause register&n; * isr_ptr   - Pointer to the interrupt service routine&n; */
DECL|function|hook_irq_handler
r_void
id|hook_irq_handler
c_func
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
(brace
id|irq_handlers
(braket
id|int_cause
)braket
(braket
id|bit_num
)braket
dot
id|routine
op_assign
id|isr_ptr
suffix:semicolon
)brace
multiline_comment|/*&n; * Enables the IRQ on Galileo Chip&n; *&n; * Inputs :&n; * int_cause - The interrupt cause number. In EVB64120 two parameters&n; *             are declared, INT_CAUSE_MAIN and INT_CAUSE_HIGH.&n; * bit_num   - Indicates which bit number in the cause register&n; *&n; * Outputs :&n; * 1 if succesful, 0 if failure&n; */
DECL|function|enable_galileo_irq
r_int
id|enable_galileo_irq
c_func
(paren
r_int
id|int_cause
comma
r_int
id|bit_num
)paren
(brace
r_if
c_cond
(paren
id|int_cause
op_eq
id|INT_CAUSE_MAIN
)paren
id|SET_REG_BITS
c_func
(paren
id|CPU_INTERRUPT_MASK_REGISTER
comma
(paren
l_int|1
op_lshift
id|bit_num
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|int_cause
op_eq
id|INT_CAUSE_HIGH
)paren
id|SET_REG_BITS
c_func
(paren
id|CPU_HIGH_INTERRUPT_MASK_REGISTER
comma
(paren
l_int|1
op_lshift
id|bit_num
)paren
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Disables the IRQ on Galileo Chip&n; *&n; * Inputs :&n; * int_cause - The interrupt cause number. In EVB64120 two parameters&n; *             are declared, INT_CAUSE_MAIN and INT_CAUSE_HIGH.&n; * bit_num   - Indicates which bit number in the cause register&n; *&n; * Outputs :&n; * 1 if succesful, 0 if failure&n; */
DECL|function|disable_galileo_irq
r_int
id|disable_galileo_irq
c_func
(paren
r_int
id|int_cause
comma
r_int
id|bit_num
)paren
(brace
r_if
c_cond
(paren
id|int_cause
op_eq
id|INT_CAUSE_MAIN
)paren
id|RESET_REG_BITS
c_func
(paren
id|CPU_INTERRUPT_MASK_REGISTER
comma
(paren
l_int|1
op_lshift
id|bit_num
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|int_cause
op_eq
id|INT_CAUSE_HIGH
)paren
id|RESET_REG_BITS
c_func
(paren
id|CPU_HIGH_INTERRUPT_MASK_REGISTER
comma
(paren
l_int|1
op_lshift
id|bit_num
)paren
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/*  UNUSED  */
multiline_comment|/*&n; * Interrupt handler for interrupts coming from the Galileo chip via P0_INT#.&n; *&n; * We route the timer interrupt to P0_INT# (IRQ 6), and that&squot;s all this&n; * routine can handle, for now.&n; *&n; * In the future, we&squot;ll route more interrupts to this pin, and that&squot;s why&n; * we keep this particular structure in the function.&n; */
DECL|function|gt64240_p0int_irq
r_static
r_void
id|gt64240_p0int_irq
c_func
(paren
r_int
id|irq
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
r_uint32
id|irq_src
comma
id|irq_src_mask
suffix:semicolon
r_int
id|handled
suffix:semicolon
multiline_comment|/* get the low interrupt cause register */
id|GT_READ
c_func
(paren
id|LOW_INTERRUPT_CAUSE_REGISTER
comma
op_amp
id|irq_src
)paren
suffix:semicolon
multiline_comment|/* get the mask register for this pin */
id|GT_READ
c_func
(paren
id|PCI_0INTERRUPT_CAUSE_MASK_REGISTER_LOW
comma
op_amp
id|irq_src_mask
)paren
suffix:semicolon
multiline_comment|/* mask off only the interrupts we&squot;re interested in */
id|irq_src
op_assign
id|irq_src
op_amp
id|irq_src_mask
suffix:semicolon
id|handled
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Check for timer interrupt */
r_if
c_cond
(paren
id|irq_src
op_amp
l_int|0x00000100
)paren
(brace
id|handled
op_assign
l_int|1
suffix:semicolon
id|irq_src
op_and_assign
op_complement
l_int|0x00000100
suffix:semicolon
multiline_comment|/* Clear any pending cause bits */
id|GT_WRITE
c_func
(paren
id|TIMER_COUNTER_0_3_INTERRUPT_CAUSE
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* handle the timer call */
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq_src
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;UNKNOWN P0_INT# interrupt received, irq_src=0x%x&bslash;n&quot;
comma
id|irq_src
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Interrupt handler for interrupts coming from the Galileo chip.&n; * It could be built in ethernet ports etc...&n; */
DECL|function|gt64240_irq
r_static
r_void
id|gt64240_irq
c_func
(paren
r_int
id|irq
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
r_int
r_int
id|irq_src
comma
id|int_high_src
comma
id|irq_src_mask
comma
id|int_high_src_mask
suffix:semicolon
r_int
id|handled
suffix:semicolon
macro_line|#if 0
id|GT_READ
c_func
(paren
id|GT_INTRCAUSE_OFS
comma
op_amp
id|irq_src
)paren
suffix:semicolon
id|GT_READ
c_func
(paren
id|GT_INTRMASK_OFS
comma
op_amp
id|irq_src_mask
)paren
suffix:semicolon
id|GT_READ
c_func
(paren
id|GT_HINTRCAUSE_OFS
comma
op_amp
id|int_high_src
)paren
suffix:semicolon
id|GT_READ
c_func
(paren
id|GT_HINTRMASK_OFS
comma
op_amp
id|int_high_src_mask
)paren
suffix:semicolon
macro_line|#endif
id|irq_src
op_assign
id|irq_src
op_amp
id|irq_src_mask
suffix:semicolon
id|int_high_src
op_assign
id|int_high_src
op_amp
id|int_high_src_mask
suffix:semicolon
id|handled
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Execute all interrupt handlers */
multiline_comment|/* Check for timer interrupt */
r_if
c_cond
(paren
id|irq_src
op_amp
l_int|0x00000800
)paren
(brace
id|handled
op_assign
l_int|1
suffix:semicolon
id|irq_src
op_and_assign
op_complement
l_int|0x00000800
suffix:semicolon
singleline_comment|//    RESET_REG_BITS (INTERRUPT_CAUSE_REGISTER,BIT8);
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq_src
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Other Galileo interrupt received irq_src %x&bslash;n&quot;
comma
id|irq_src
)paren
suffix:semicolon
macro_line|#if CURRENTLY_UNUSED
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|MAX_CAUSE_REG_WIDTH
suffix:semicolon
id|count
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irq_src
op_amp
(paren
l_int|1
op_lshift
id|count
)paren
)paren
(brace
r_if
c_cond
(paren
id|irq_handlers
(braket
id|INT_CAUSE_MAIN
)braket
(braket
id|count
)braket
dot
id|routine
)paren
(brace
id|queue_task
c_func
(paren
op_amp
id|irq_handlers
(braket
id|INT_CAUSE_MAIN
)braket
(braket
id|count
)braket
comma
op_amp
id|tq_immediate
)paren
suffix:semicolon
id|mark_bh
c_func
(paren
id|IMMEDIATE_BH
)paren
suffix:semicolon
id|handled
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif&t;&t;&t;&t;/*  UNUSED  */
)brace
macro_line|#if 0
id|GT_WRITE
c_func
(paren
id|GT_INTRCAUSE_OFS
comma
l_int|0
)paren
suffix:semicolon
id|GT_WRITE
c_func
(paren
id|GT_HINTRCAUSE_OFS
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|GALILEO_I2O
macro_line|#undef GALILEO_I2O
macro_line|#ifdef GALILEO_I2O
multiline_comment|/*&n;&t; * Future I2O support.  We currently attach I2O interrupt handlers to&n;&t; * the Galileo interrupt (int 4) and handle them in do_IRQ.&n;&t; */
r_if
c_cond
(paren
id|isInBoundDoorBellInterruptSet
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;I2O doorbell interrupt received.&bslash;n&quot;
)paren
suffix:semicolon
id|handled
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|isInBoundPostQueueInterruptSet
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;I2O Queue interrupt received.&bslash;n&quot;
)paren
suffix:semicolon
id|handled
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This normally would be outside of the ifdef, but since we&squot;re&n;&t; * handling I2O outside of this handler, this printk shows up every&n;&t; * time we get a valid I2O interrupt.  So turn this off for now.&n;&t; */
r_if
c_cond
(paren
id|handled
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|counter
OL
l_int|50
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Spurious Galileo interrupt...&bslash;n&quot;
)paren
suffix:semicolon
id|counter
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; * Initializes timer using galileo&squot;s built in timer.&n; */
multiline_comment|/*&n; * This will ignore the standard MIPS timer interrupt handler&n; * that is passed in as *irq (=irq0 in ../kernel/time.c).&n; * We will do our own timer interrupt handling.&n; */
DECL|function|gt64240_time_init
r_void
id|gt64240_time_init
c_func
(paren
r_void
)paren
(brace
r_extern
id|irq_desc_t
id|irq_desc
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_static
r_struct
id|irqaction
id|timer
suffix:semicolon
multiline_comment|/* Stop the timer -- we&squot;ll use timer #0 */
id|GT_WRITE
c_func
(paren
id|TIMER_COUNTER_0_3_CONTROL
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* Load timer value for 100 Hz */
id|GT_WRITE
c_func
(paren
id|TIMER_COUNTER0
comma
id|bus_clock
op_div
l_int|100
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create the IRQ structure entry for the timer.  Since we&squot;re too early&n;&t; * in the boot process to use the &quot;request_irq()&quot; call, we&squot;ll hard-code&n;&t; * the values to the correct interrupt line.&n;&t; */
id|timer.handler
op_assign
op_amp
id|gt64240_p0int_irq
suffix:semicolon
id|timer.flags
op_assign
id|SA_SHIRQ
op_or
id|SA_INTERRUPT
suffix:semicolon
id|timer.name
op_assign
l_string|&quot;timer&quot;
suffix:semicolon
id|timer.dev_id
op_assign
l_int|NULL
suffix:semicolon
id|timer.next
op_assign
l_int|NULL
suffix:semicolon
id|timer.mask
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
l_int|6
)braket
dot
id|action
op_assign
op_amp
id|timer
suffix:semicolon
id|enable_irq
c_func
(paren
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Clear any pending cause bits */
id|GT_WRITE
c_func
(paren
id|TIMER_COUNTER_0_3_INTERRUPT_CAUSE
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* Enable the interrupt for timer 0 */
id|GT_WRITE
c_func
(paren
id|TIMER_COUNTER_0_3_INTERRUPT_MASK
comma
l_int|0x1
)paren
suffix:semicolon
multiline_comment|/* Enable the timer interrupt for GT-64240 pin P0_INT# */
id|GT_WRITE
(paren
id|PCI_0INTERRUPT_CAUSE_MASK_REGISTER_LOW
comma
l_int|0x100
)paren
suffix:semicolon
multiline_comment|/* Configure and start the timer */
id|GT_WRITE
c_func
(paren
id|TIMER_COUNTER_0_3_CONTROL
comma
l_int|0x3
)paren
suffix:semicolon
)brace
DECL|function|gt64240_irq_init
r_void
id|gt64240_irq_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if CURRENTLY_UNUSED
r_int
id|i
comma
id|j
suffix:semicolon
multiline_comment|/* Reset irq handlers pointers to NULL */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CAUSE_REGS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|MAX_CAUSE_REG_WIDTH
suffix:semicolon
id|j
op_increment
)paren
(brace
id|irq_handlers
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|next
op_assign
l_int|NULL
suffix:semicolon
id|irq_handlers
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|sync
op_assign
l_int|0
suffix:semicolon
id|irq_handlers
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|routine
op_assign
l_int|NULL
suffix:semicolon
id|irq_handlers
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|data
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
eof
