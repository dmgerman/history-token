multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/ide.h&n; *&n; * Copyright (c) 2000 Steve Hill (sjhill@cotw.com)&n; *&n; * Changelog:&n; *  03-29-2000&t;SJH&t;Created file placeholder&n; */
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * Set up a hw structure for a specified data port, control port and IRQ.&n; * This should follow whatever the default interface uses.&n; */
r_static
id|__inline__
r_void
DECL|function|ide_init_hwif_ports
id|ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
r_int
id|data_port
comma
r_int
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
)brace
multiline_comment|/*&n; * This registers the standard ports for this architecture with the IDE&n; * driver.&n; */
r_static
id|__inline__
r_void
DECL|function|ide_init_default_hwifs
id|ide_init_default_hwifs
c_func
(paren
r_void
)paren
(brace
)brace
eof
