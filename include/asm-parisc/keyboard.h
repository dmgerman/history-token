multiline_comment|/*&n; *  linux/include/asm-parisc/keyboard.h&n; *&n; *  Original by Geert Uytterhoeven&n; *  updates by Alex deVries &lt;adevries@thepuffingroup.com&gt;&n; *  portions copyright (1999) The Puffin Group&n; *  mostly rewritten by Philipp Rumpf &lt;prumpf@tux.org&gt;,&n; *   Copyright 2000 Philipp Rumpf&n; */
multiline_comment|/*&n; *  We try to keep the amount of generic code as low as possible -&n; *  we want to support all HIL, PS/2, and untranslated USB keyboards&n; */
macro_line|#ifndef _PARISC_KEYBOARD_H
DECL|macro|_PARISC_KEYBOARD_H
mdefine_line|#define _PARISC_KEYBOARD_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_VT
multiline_comment|/*  These are basically the generic functions / variables.  The only&n; *  unexpected detail is the initialization sequence for the keyboard&n; *  driver is something like this:&n; *&n; *  detect keyboard port&n; *  detect keyboard&n; *  call register_kbd_ops &n; *  wait for init_hw&n; *&n; *  only after init_hw has been called you&squot;re allowed to call&n; *  handle_scancode.  This means you either have to be extremely&n; *  careful or use a global flag or something - I strongly suggest&n; *  the latter.    prumpf */
DECL|struct|kbd_ops
r_extern
r_struct
id|kbd_ops
(brace
DECL|member|setkeycode
r_int
(paren
op_star
id|setkeycode
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|getkeycode
r_int
(paren
op_star
id|getkeycode
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|translate
r_int
(paren
op_star
id|translate
)paren
(paren
r_int
r_char
comma
r_int
r_char
op_star
comma
r_char
)paren
suffix:semicolon
DECL|member|unexpected_up
r_char
(paren
op_star
id|unexpected_up
)paren
(paren
r_int
r_char
)paren
suffix:semicolon
DECL|member|leds
r_void
(paren
op_star
id|leds
)paren
(paren
r_int
r_char
)paren
suffix:semicolon
DECL|member|init_hw
r_void
(paren
op_star
id|init_hw
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|sysrq_key
r_int
r_char
id|sysrq_key
suffix:semicolon
DECL|member|sysrq_xlate
r_int
r_char
op_star
id|sysrq_xlate
suffix:semicolon
)brace
op_star
id|kbd_ops
suffix:semicolon
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode&t;&t;(*kbd_ops-&gt;setkeycode)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode&t;&t;(*kbd_ops-&gt;getkeycode)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate&t;&t;(*kbd_ops-&gt;translate)
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up&t;(*kbd_ops-&gt;unexpected_up)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds&t;&t;(*kbd_ops-&gt;leds)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw&t;&t;(*kbd_ops-&gt;init_hw)
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY&t;&t;(kbd_ops-&gt;sysrq_key)
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define&t;kbd_sysrq_xlate&t;&t;(kbd_ops-&gt;sysrq_xlate)
r_extern
r_int
r_char
id|hp_ps2kbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* from drivers/char/hp_keyb.c */
r_extern
r_void
id|register_kbd_ops
c_func
(paren
r_struct
id|kbd_ops
op_star
id|ops
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_VT */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMPARISC_KEYBOARD_H */
eof
