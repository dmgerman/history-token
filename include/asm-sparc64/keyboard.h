multiline_comment|/* $Id: keyboard.h,v 1.4 2001/08/13 14:40:07 davem Exp $&n; * linux/include/asm-sparc64/keyboard.h&n; *&n; * Created Aug 29 1997 by Eddie C. Dost (ecd@skynet.be)&n; */
multiline_comment|/*&n; *  This file contains the Ultra/PCI architecture specific keyboard definitions&n; */
macro_line|#ifndef _SPARC64_KEYBOARD_H
DECL|macro|_SPARC64_KEYBOARD_H
mdefine_line|#define _SPARC64_KEYBOARD_H 1
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ&t;&t;&t;1
DECL|macro|DISABLE_KBD_DURING_INTERRUPTS
mdefine_line|#define DISABLE_KBD_DURING_INTERRUPTS&t;0
r_extern
r_int
id|pcikbd_setkeycode
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
id|pcikbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|pcikbd_translate
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
id|pcikbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
suffix:semicolon
r_extern
r_void
id|pcikbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_int
id|pcikbd_rate
c_func
(paren
r_struct
id|kbd_repeat
op_star
id|rep
)paren
suffix:semicolon
r_extern
r_void
id|pcikbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|pcikbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode&t;&t;&t;pcikbd_setkeycode
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode&t;&t;&t;pcikbd_getkeycode
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate&t;&t;&t;pcikbd_translate
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up&t;&t;pcikbd_unexpected_up
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds&t;&t;&t;pcikbd_leds
DECL|macro|kbd_rate
mdefine_line|#define kbd_rate&t;&t;&t;pcikbd_rate
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw&t;&t;&t;pcikbd_init_hw
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;&t;pcikbd_sysrq_xlate
DECL|macro|kbd_init
mdefine_line|#define kbd_init&t;&t;&t;pcikbd_init
DECL|macro|compute_shiftstate
mdefine_line|#define compute_shiftstate&t;&t;pci_compute_shiftstate
DECL|macro|keyboard_wait_for_keypress
mdefine_line|#define keyboard_wait_for_keypress&t;pci_wait_for_keypress
DECL|macro|getkeycode
mdefine_line|#define getkeycode&t;&t;&t;pci_getkeycode
DECL|macro|setkeycode
mdefine_line|#define setkeycode&t;&t;&t;pci_setkeycode
DECL|macro|getledstate
mdefine_line|#define getledstate&t;&t;&t;pci_getledstate
DECL|macro|setledstate
mdefine_line|#define setledstate&t;&t;&t;pci_setledstate
DECL|macro|register_leds
mdefine_line|#define register_leds&t;&t;&t;pci_register_leds
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY 0x54
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(_SPARC64_KEYBOARD_H) */
eof
