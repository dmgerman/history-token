multiline_comment|/*&n; * linux/include/asm-arm/arch-cl7500/keyboard.h&n; *  from linux/include/asm-arm/arch-rpc/keyboard.h&n; *&n; * Keyboard driver definitions for CL7500 architecture&n; *&n; * Copyright (C) 1998-2001 Russell King&n; */
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
r_extern
r_int
id|ps2kbd_init_hw
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
mdefine_line|#define kbd_init_hw()&t;&t;ps2kbd_init_hw()
eof
