multiline_comment|/*&n; *  linux/include/asm-arm/arch-anakin/time.h&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   10-Apr-2001 TTC&t;Created&n; */
macro_line|#ifndef __ASM_ARCH_TIME_H
DECL|macro|__ASM_ARCH_TIME_H
mdefine_line|#define __ASM_ARCH_TIME_H
r_static
id|irqreturn_t
DECL|function|anakin_timer_interrupt
id|anakin_timer_interrupt
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
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
id|timer_irq.handler
op_assign
id|anakin_timer_interrupt
suffix:semicolon
id|setup_irq
c_func
(paren
id|IRQ_TICK
comma
op_amp
id|timer_irq
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
