multiline_comment|/*&n; *  linux/include/asm-arm/arch-anakin/keyboard.h&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   11-Apr-2001 TTC&t;Created&n; */
macro_line|#ifndef __ASM_ARCH_KEYBOARD_H
DECL|macro|__ASM_ARCH_KEYBOARD_H
mdefine_line|#define __ASM_ARCH_KEYBOARD_H
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(s, k)&t;(-EINVAL)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(s)&t;(-EINVAL)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(s, k, r)&t;0
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(k)&t;0
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(l)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;((int *) 0)
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY&t;&t;0x54
macro_line|#endif
eof
