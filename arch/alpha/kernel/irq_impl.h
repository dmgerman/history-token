multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/irq_impl.h&n; *&n; *&t;Copyright (C) 1995 Linus Torvalds&n; *&t;Copyright (C) 1998, 2000 Richard Henderson&n; *&n; * This file contains declarations and inline functions for interfacing&n; * with the IRQ handling routines in irq.c.&n; */
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ    8
r_extern
r_void
id|isa_device_interrupt
c_func
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isa_no_iack_sc_device_interrupt
c_func
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|srm_device_interrupt
c_func
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pyxis_device_interrupt
c_func
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|irqaction
id|timer_irqaction
suffix:semicolon
r_extern
r_struct
id|irqaction
id|isa_cascade_irqaction
suffix:semicolon
r_extern
r_struct
id|irqaction
id|timer_cascade_irqaction
suffix:semicolon
r_extern
r_struct
id|irqaction
id|halt_switch_irqaction
suffix:semicolon
r_extern
r_void
id|init_srm_irqs
c_func
(paren
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|init_pyxis_irqs
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|init_rtc_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|common_init_isa_dma
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|i8259a_enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|i8259a_disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|i8259a_mask_and_ack_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|i8259a_startup_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|i8259a_end_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|hw_interrupt_type
id|i8259a_irq_type
suffix:semicolon
r_extern
r_void
id|init_i8259a_irqs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|handle_irq
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
suffix:semicolon
r_extern
r_int
r_int
id|prof_cpu_mask
suffix:semicolon
r_static
r_inline
r_void
DECL|function|alpha_do_profile
id|alpha_do_profile
c_func
(paren
r_int
r_int
id|pc
)paren
(brace
r_extern
r_char
id|_stext
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prof_buffer
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Only measure the CPUs specified by /proc/irq/prof_cpu_mask.&n;&t; * (default is all CPUs.)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
op_amp
id|prof_cpu_mask
)paren
)paren
r_return
suffix:semicolon
id|pc
op_sub_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|pc
op_rshift_assign
id|prof_shift
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t ignore out-of-bounds PC values silently,&n;&t; * put them into the last histogram slot, so if&n;&t; * present, they will show up as a sharp peak.&n;&t; */
r_if
c_cond
(paren
id|pc
OG
id|prof_len
op_minus
l_int|1
)paren
id|pc
op_assign
id|prof_len
op_minus
l_int|1
suffix:semicolon
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|prof_buffer
(braket
id|pc
)braket
)paren
suffix:semicolon
)brace
eof
