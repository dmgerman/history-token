multiline_comment|/*&n; *  linux/include/asm-h8300/keyboard.h&n; *  Created 04 Dec 2001 by Khaled Hassounah &lt;khassounah@mediumware.net&gt;&n; *  This file contains the Dragonball architecture specific keyboard definitions&n; */
macro_line|#ifndef _H8300_KEYBOARD_H
DECL|macro|_H8300_KEYBOARD_H
mdefine_line|#define _H8300_KEYBOARD_H
macro_line|#include &lt;linux/config.h&gt;
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
mdefine_line|#define kbd_leds(x...)&t;&t;do {;} while (0)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw(x...)&t;do {;} while (0)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq(x...)&t;do {;} while (0)
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq(x...)&t;do {;} while (0)
multiline_comment|/* needed if MAGIC_SYSRQ is enabled for serial console */
macro_line|#ifndef SYSRQ_KEY
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY&t;&t;((unsigned char)(-1))
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate         ((unsigned char *)NULL)
macro_line|#endif
macro_line|#endif  /* _H8300_KEYBOARD_H */
eof
