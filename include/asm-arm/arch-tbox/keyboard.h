multiline_comment|/*&n; * linux/include/asm-arm/arch-tbox/keyboard.h&n; *&n; * Driver definitions for Tbox dummy keyboard.&n; *&n; * Copyright (C) 1998 Russell King&n; * Copyright (C) 1998 Philip Blundell&n; */
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(sc,kc)&t;&t;(-EINVAL)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(sc)&t;&t;(-EINVAL)
multiline_comment|/* Prototype: int kbd_pretranslate(scancode, raw_mode)&n; * Returns  : 0 to ignore scancode&n; */
DECL|macro|kbd_pretranslate
mdefine_line|#define kbd_pretranslate(sc,rm)&t;(1)
multiline_comment|/* Prototype: int kbd_translate(scancode, *keycode, *up_flag, raw_mode)&n; * Returns  : 0 to ignore scancode, *keycode set to keycode, *up_flag&n; *            set to 0200 if scancode indicates release&n; */
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, rm) 0
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(kc)&t;&t;(0200)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(leds)&t;&t;&t;do { } while (0)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;&t;&t;do { } while (0)
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()&t;&t;do { } while (0)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()&t;&t;do { } while (0)
eof
