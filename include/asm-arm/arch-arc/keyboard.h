multiline_comment|/*&n; *  linux/include/asm-arm/arch-arc/keyboard.h&n; *&n; *  Copyright (C) 1998-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Keyboard driver definitions for Acorn Archimedes/A5000&n; *  architecture&n; */
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
r_extern
r_void
id|a5kkbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()&t;disable_irq(IRQ_KEYBOARDRX)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()&t;enable_irq(IRQ_KEYBOARDRX)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;&t;a5kkbd_init_hw()
eof
