multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa110/system.h&n; *&n; *  Copyright (C) 1996-2000 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
multiline_comment|/*&n; * EBSA110 idling methodology:&n; *&n; * We can not execute the &quot;wait for interrupt&quot; instruction since that&n; * will stop our MCLK signal (which provides the clock for the glue&n; * logic, and therefore the timer interrupt).&n; *&n; * Instead, we spin, polling the IRQ_STAT register for the occurrence&n; * of any interrupt with core clock down to the memory clock.&n; */
DECL|function|arch_idle
r_static
r_void
id|arch_idle
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|irq_stat
op_assign
(paren
r_char
op_star
)paren
l_int|0xff000000
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hlt_counter
)paren
r_return
suffix:semicolon
r_do
(brace
multiline_comment|/* disable interrupts */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* check need_resched here to avoid races */
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* disable clock switching */
id|asm
r_volatile
(paren
l_string|&quot;mcr%? p15, 0, ip, c15, c2, 2&quot;
)paren
suffix:semicolon
multiline_comment|/* wait for an interrupt to occur */
r_while
c_loop
(paren
op_logical_neg
op_star
id|irq_stat
)paren
suffix:semicolon
multiline_comment|/* enable clock switching */
id|asm
r_volatile
(paren
l_string|&quot;mcr%? p15, 0, ip, c15, c1, 2&quot;
)paren
suffix:semicolon
multiline_comment|/* allow the interrupt to happen */
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|macro|arch_reset
mdefine_line|#define arch_reset(mode)&t;cpu_reset(0x80000000)
macro_line|#endif
eof
