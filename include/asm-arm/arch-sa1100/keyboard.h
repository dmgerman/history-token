multiline_comment|/*&n; *  linux/include/asm-arm/arch-sa1100/keyboard.h&n; *  Created 16 Dec 1999 by Nicolas Pitre &lt;nico@cam.org&gt;&n; *  This file contains the SA1100 architecture specific keyboard definitions&n; */
macro_line|#ifndef _SA1100_KEYBOARD_H
DECL|macro|_SA1100_KEYBOARD_H
mdefine_line|#define _SA1100_KEYBOARD_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
r_extern
r_struct
id|kbd_ops_struct
op_star
id|kbd_ops
suffix:semicolon
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()&t;do { } while(0);
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()&t;do { } while(0);
multiline_comment|/*&n; * SA1111 keyboard driver&n; */
r_extern
r_void
id|sa1111_kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * GraphicsClient keyboard driver&n; */
r_extern
r_void
id|gc_kbd_init_hw
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
id|machine_is_assabet
c_func
(paren
)paren
op_logical_and
id|machine_has_neponset
c_func
(paren
)paren
)paren
id|sa1111_kbd_init_hw
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_graphicsclient
c_func
(paren
)paren
)paren
id|gc_kbd_init_hw
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if 0&t; /* Brutus needs fixing */
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
mdefine_line|#define kbd_setkeycode(x...)&t;(-ENOSYS)
mdefine_line|#define kbd_getkeycode(x...)&t;(-ENOSYS)
mdefine_line|#define kbd_translate&t;&t;Brutus_kbd_translate
mdefine_line|#define kbd_unexpected_up(x...)&t;(1)
mdefine_line|#define kbd_leds&t;&t;Brutus_kbd_leds
mdefine_line|#define kbd_init_hw&t;&t;Brutus_kbd_init_hw
mdefine_line|#define kbd_enable_irq&t;&t;Brutus_kbd_enable_irq
mdefine_line|#define kbd_disable_irq&t;&t;Brutus_kbd_disable_irq
mdefine_line|#define kbd_sysrq_xlate&t;&t;Brutus_kbd_sysrq_xlate
mdefine_line|#define SYSRQ_KEY 0x54
macro_line|#elif 0 
singleline_comment|// CONFIG_SA1100_GRAPHICSCLIENT
r_extern
r_int
id|gc_kbd_setkeycode
c_func
(paren
r_int
r_int
id|scancode
comma
r_int
r_int
id|keycode
)paren
suffix:semicolon
r_extern
r_int
id|gc_kbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|gc_kbd_translate
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
id|gc_kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|gc_kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gc_kbd_enable_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gc_kbd_disable_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|gc_kbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(x...)    gc_kbd_setkeycode&t;
singleline_comment|//(-ENOSYS)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(x...)    gc_kbd_getkeycode&t;
singleline_comment|//(-ENOSYS)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate           gc_kbd_translate
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(x...) (1)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds                gc_kbd_leds
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw             gc_kbd_init_hw
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq          gc_kbd_enable_irq
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq         gc_kbd_disable_irq
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate         (1)
macro_line|#endif
macro_line|#endif  /* _SA1100_KEYBOARD_H */
eof
