multiline_comment|/*&n; * linux/include/asm-arm/arch-clps711x/keyboard.h&n; *&n; * Copyright (C) 1998-2001 Russell King&n; */
macro_line|#include &lt;asm/mach-types.h&gt;
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()&t;do { } while (0)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()&t;do { } while (0)
multiline_comment|/*&n; * EDB7211 keyboard driver&n; */
r_extern
r_void
id|edb7211_kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|clps711x_kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|kbd_init_hw
r_static
r_inline
r_void
id|kbd_init_hw
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_edb7211
c_func
(paren
)paren
)paren
id|edb7211_kbd_init_hw
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_autcpu12
c_func
(paren
)paren
)paren
id|clps711x_kbd_init_hw
c_func
(paren
)paren
suffix:semicolon
)brace
eof
