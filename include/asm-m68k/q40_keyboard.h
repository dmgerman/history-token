multiline_comment|/*&n; *  linux/include/asm-m68k/q40_keyboard.h&n; *&n; *  Created &n; */
multiline_comment|/*&n; *  This file contains the Q40 specific keyboard definitions&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/machdep.h&gt;
r_extern
r_int
id|q40kbd_setkeycode
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
id|q40kbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|q40kbd_pretranslate
c_func
(paren
r_int
r_char
id|scancode
comma
r_char
id|raw_mode
)paren
suffix:semicolon
r_extern
r_int
id|q40kbd_translate
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
r_char
id|q40kbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
suffix:semicolon
r_extern
r_void
id|q40kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|q40kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|q40kbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
macro_line|#if 0
mdefine_line|#define kbd_setkeycode&t;&t;q40kbd_setkeycode
mdefine_line|#define kbd_getkeycode&t;&t;q40kbd_getkeycode
mdefine_line|#define kbd_pretranslate&t;q40kbd_pretranslate
mdefine_line|#define kbd_translate&t;&t;q40kbd_translate
mdefine_line|#define kbd_unexpected_up&t;q40kbd_unexpected_up
mdefine_line|#define kbd_leds&t;&t;q40kbd_leds
mdefine_line|#define kbd_init_hw&t;&t;q40kbd_init_hw
mdefine_line|#define kbd_sysrq_xlate&t;&t;q40kbd_sysrq_xlate
mdefine_line|#define SYSRQ_KEY 0x54
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
