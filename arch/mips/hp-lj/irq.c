multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Code to handle x86 style IRQs plus some generic interrupt stuff.&n; *&n; * Copyright (C) 1992 Linus Torvalds&n; * Copyright (C) 1994 - 2000 Ralf Baechle&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/gdb-stub.h&gt;
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|hpIRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mips_cpu_irq_init
c_func
(paren
id|u32
id|base
)paren
suffix:semicolon
id|mips_cpu_irq_init
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|0
comma
id|hpIRQ
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KGDB
(brace
r_extern
r_void
id|breakpoint
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|remote_debug
suffix:semicolon
r_if
c_cond
(paren
id|remote_debug
)paren
(brace
id|set_debug_traps
c_func
(paren
)paren
suffix:semicolon
id|breakpoint
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
eof
