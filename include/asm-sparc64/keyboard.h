multiline_comment|/* $Id: keyboard.h,v 1.6 2002/01/08 16:00:20 davem Exp $&n; * linux/include/asm-sparc64/keyboard.h&n; *&n; * Created Aug 29 1997 by Eddie C. Dost (ecd@skynet.be)&n; */
multiline_comment|/*&n; *  This file contains the Ultra/PCI architecture specific keyboard definitions&n; */
macro_line|#ifndef _SPARC64_KEYBOARD_H
DECL|macro|_SPARC64_KEYBOARD_H
mdefine_line|#define _SPARC64_KEYBOARD_H 1
macro_line|#ifdef __KERNEL__
multiline_comment|/* We use the generic input layer for keyboard handling, thus&n; * some of this stuff should never be invoked.&n; */
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(scancode, keycode)&t;(BUG(), 0)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(scancode)&t;&t;(BUG(), 0)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(keycode, keycodep, raw_mode) &bslash;&n;&t;({ *(keycodep) = scancode; 1; })
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(keycode)&t;&t;(0200)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(leds)&t;&t;&t;&t;do { } while (0)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;&t;&t;&t;do { } while (0)
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY 0x54
r_extern
r_int
r_char
id|kbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(_SPARC64_KEYBOARD_H) */
eof
