multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/fpga.h&n; *&n; * Interrupt handler for OMAP-1510 FPGA&n; *&n; * Copyright (C) 2001 RidgeRun, Inc.&n; * Author: Greg Lonnon &lt;glonnon@ridgerun.com&gt;&n; *&n; * Copyright (C) 2002 MontaVista Software, Inc.&n; *&n; * Separated FPGA interrupts from innovator1510.c and cleaned up for 2.6&n; * Copyright (C) 2004 Nokia Corporation by Tony Lindrgen &lt;tony@atomide.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_FPGA_H
DECL|macro|__ASM_ARCH_OMAP_FPGA_H
mdefine_line|#define __ASM_ARCH_OMAP_FPGA_H
r_extern
r_void
id|fpga_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|fpga_read
c_func
(paren
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_void
id|fpga_write
c_func
(paren
r_int
r_char
id|val
comma
r_int
id|reg
)paren
suffix:semicolon
macro_line|#endif
eof
