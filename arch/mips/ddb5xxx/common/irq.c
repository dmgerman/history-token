multiline_comment|/*&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * arch/mips/ddb5xxx/common/irq.c&n; *     Common irq code for DDB boards.  This really should belong&n; *&t;arch/mips/kernel/irq.c.  Need to talk to Ralf.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|variable|irq_setup
r_void
(paren
op_star
id|irq_setup
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_REMOTE_DEBUG
r_extern
r_void
id|breakpoint
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_debug_traps
c_func
(paren
r_void
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Wait for gdb client connection ...&bslash;n&quot;
)paren
suffix:semicolon
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
macro_line|#endif
multiline_comment|/* invoke board-specific irq setup */
id|irq_setup
c_func
(paren
)paren
suffix:semicolon
)brace
eof
