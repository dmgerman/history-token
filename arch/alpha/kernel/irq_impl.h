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
eof
