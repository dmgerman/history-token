multiline_comment|/*&n; *  linux/include/asm-m68k/keyboard.h&n; *&n; *  Created 3 Nov 1996 by Geert Uytterhoeven&n; */
multiline_comment|/*&n; *  This file contains the m68k architecture specific keyboard definitions&n; */
macro_line|#ifndef __M68K_KEYBOARD_H
DECL|macro|__M68K_KEYBOARD_H
mdefine_line|#define __M68K_KEYBOARD_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#ifdef CONFIG_Q40
macro_line|#include &lt;asm/q40_keyboard.h&gt;
macro_line|#endif
DECL|function|kbd_setkeycode
r_static
id|__inline__
r_int
id|kbd_setkeycode
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
(brace
macro_line|#ifdef CONFIG_Q40
r_if
c_cond
(paren
id|MACH_IS_Q40
)paren
r_return
id|q40kbd_setkeycode
c_func
(paren
id|scancode
comma
id|keycode
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
DECL|function|kbd_getkeycode
r_static
id|__inline__
r_int
id|kbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
(brace
macro_line|#ifdef CONFIG_Q40
r_if
c_cond
(paren
id|MACH_IS_Q40
)paren
r_return
id|q40kbd_getkeycode
c_func
(paren
id|scancode
)paren
suffix:semicolon
macro_line|#endif
r_return
id|scancode
OG
l_int|127
ques
c_cond
op_minus
id|EINVAL
suffix:colon
id|scancode
suffix:semicolon
)brace
DECL|function|kbd_unexpected_up
r_static
id|__inline__
r_char
id|kbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
(brace
macro_line|#ifdef CONFIG_Q40
r_if
c_cond
(paren
id|MACH_IS_Q40
)paren
r_return
id|q40kbd_unexpected_up
c_func
(paren
id|keycode
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0200
suffix:semicolon
)brace
DECL|function|kbd_leds
r_static
id|__inline__
r_void
id|kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
(brace
r_if
c_cond
(paren
id|mach_kbd_leds
)paren
id|mach_kbd_leds
c_func
(paren
id|leds
)paren
suffix:semicolon
)brace
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw&t;&t;mach_keyb_init
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate&t;&t;mach_kbd_translate
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;mach_sysrq_xlate
multiline_comment|/* resource allocation */
DECL|macro|kbd_request_region
mdefine_line|#define kbd_request_region()
DECL|macro|kbd_request_irq
mdefine_line|#define kbd_request_irq(handler)
r_extern
r_int
r_int
id|SYSRQ_KEY
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __M68K_KEYBOARD_H */
eof
