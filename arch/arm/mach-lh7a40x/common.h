multiline_comment|/* arch/arm/mach-lh7a40x/common.h&n; *&n; *  Copyright (C) 2004 Marc Singer&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
r_extern
r_struct
id|sys_timer
id|lh7a40x_timer
suffix:semicolon
r_extern
r_void
id|lh7a400_init_irq
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|lh7a404_init_irq
(paren
r_void
)paren
suffix:semicolon
DECL|macro|IRQ_DISPATCH
mdefine_line|#define IRQ_DISPATCH(irq) irq_desc[irq].handle ((irq), &amp;irq_desc[irq], regs)
eof
