multiline_comment|/*&n; *  linux/include/asm-arm/arch-sa1100/keyboard.h&n; *  Created 16 Dec 1999 by Nicolas Pitre &lt;nico@cam.org&gt;&n; *  This file contains the SA1100 architecture specific keyboard definitions&n; */
macro_line|#ifndef _SA1100_KEYBOARD_H
DECL|macro|_SA1100_KEYBOARD_H
mdefine_line|#define _SA1100_KEYBOARD_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SA1100_BRUTUS
r_extern
r_int
id|Brutus_kbd_translate
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
suffix:semicolon
r_extern
r_void
id|Brutus_kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|Brutus_kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|Brutus_kbd_enable_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|Brutus_kbd_disable_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|Brutus_kbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(x...)&t;(-ENOSYS)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(x...)&t;(-ENOSYS)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate&t;&t;Brutus_kbd_translate
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(x...)&t;(1)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds&t;&t;Brutus_kbd_leds
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw&t;&t;Brutus_kbd_init_hw
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq&t;&t;Brutus_kbd_enable_irq
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq&t;&t;Brutus_kbd_disable_irq
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;Brutus_kbd_sysrq_xlate
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY 0x54
macro_line|#else
multiline_comment|/* dummy i.e. no real keyboard */
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(x...)&t;(-ENOSYS)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(x...)&t;(-ENOSYS)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(x...)&t;(0)
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(x...)&t;(1)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(x...)&t;&t;do { } while (0)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw(x...)&t;do { } while (0)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq(x...)&t;do { } while (0)
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq(x...)&t;do { } while (0)
macro_line|#endif
macro_line|#endif  /* _SA1100_KEYBOARD_H */
eof
