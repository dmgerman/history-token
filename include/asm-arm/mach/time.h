multiline_comment|/*&n; * linux/include/asm-arm/mach/time.h&n; *&n; * Copyright (C) 2004 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_MACH_TIME_H
DECL|macro|__ASM_ARM_MACH_TIME_H
mdefine_line|#define __ASM_ARM_MACH_TIME_H
macro_line|#include &lt;linux/sysdev.h&gt;
multiline_comment|/*&n; * This is our kernel timer structure.&n; *&n; * - init&n; *   Initialise the kernels jiffy timer source, claim interrupt&n; *   using setup_irq.  This is called early on during initialisation&n; *   while interrupts are still disabled on the local CPU.&n; * - suspend&n; *   Suspend the kernel jiffy timer source, if necessary.  This&n; *   is called with interrupts disabled, after all normal devices&n; *   have been suspended.  If no action is required, set this to&n; *   NULL.&n; * - resume&n; *   Resume the kernel jiffy timer source, if necessary.  This&n; *   is called with interrupts disabled before any normal devices&n; *   are resumed.  If no action is required, set this to NULL.&n; * - offset&n; *   Return the timer offset in microseconds since the last timer&n; *   interrupt.  Note: this must take account of any unprocessed&n; *   timer interrupt which may be pending.&n; */
DECL|struct|sys_timer
r_struct
id|sys_timer
(brace
DECL|member|dev
r_struct
id|sys_device
id|dev
suffix:semicolon
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|suspend
r_void
(paren
op_star
id|suspend
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|resume
r_void
(paren
op_star
id|resume
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|offset
r_int
r_int
(paren
op_star
id|offset
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sys_timer
op_star
id|system_timer
suffix:semicolon
r_extern
r_void
id|timer_tick
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Kernel time keeping support.&n; */
r_extern
r_int
(paren
op_star
id|set_rtc
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|save_time_delta
c_func
(paren
r_struct
id|timespec
op_star
id|delta
comma
r_struct
id|timespec
op_star
id|rtc
)paren
suffix:semicolon
r_extern
r_void
id|restore_time_delta
c_func
(paren
r_struct
id|timespec
op_star
id|delta
comma
r_struct
id|timespec
op_star
id|rtc
)paren
suffix:semicolon
macro_line|#endif
eof
