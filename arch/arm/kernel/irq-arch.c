multiline_comment|/*&n; *  linux/arch/arm/kernel/irq-arch.c&n; *&n; *  Copyright (C) 1995-2000 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  We contain the architecture-specific parts of interrupt handling&n; *  in this file.  In 2.5, it will move into the various arch/arm/mach-*&n; *  directories.&n; */
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
multiline_comment|/*&n; * Get architecture specific interrupt handlers&n; * and interrupt initialisation.&n; */
macro_line|#include &lt;asm/arch/irq.h&gt;
DECL|function|genarch_init_irq
r_void
id|__init
id|genarch_init_irq
c_func
(paren
r_void
)paren
(brace
id|irq_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
eof
