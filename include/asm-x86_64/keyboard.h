multiline_comment|/*&n; *  linux/include/asm-x8664/keyboard.h&n; *&n; *  Created 3 Nov 1996 by Geert Uytterhoeven&n; */
multiline_comment|/*&n; *  This file contains the x8664 architecture specific keyboard definitions&n; */
macro_line|#ifndef _X8664_KEYBOARD_H
DECL|macro|_X8664_KEYBOARD_H
mdefine_line|#define _X8664_KEYBOARD_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ&t;&t;&t;1
DECL|macro|DISABLE_KBD_DURING_INTERRUPTS
mdefine_line|#define DISABLE_KBD_DURING_INTERRUPTS&t;0
r_extern
r_int
id|pckbd_setkeycode
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
id|pckbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_translate
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
id|pckbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
suffix:semicolon
r_extern
r_void
id|pckbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|pckbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_pm_resume
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
comma
id|pm_request_t
id|rqst
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
r_char
id|pckbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode&t;&t;pckbd_setkeycode
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode&t;&t;pckbd_getkeycode
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate&t;&t;pckbd_translate
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up&t;pckbd_unexpected_up
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds&t;&t;pckbd_leds
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw&t;&t;pckbd_init_hw
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;pckbd_sysrq_xlate
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY 0x54
multiline_comment|/* resource allocation */
DECL|macro|kbd_request_region
mdefine_line|#define kbd_request_region()
DECL|macro|kbd_request_irq
mdefine_line|#define kbd_request_irq(handler) request_irq(KEYBOARD_IRQ, handler, 0, &bslash;&n;                                             &quot;keyboard&quot;, NULL)
multiline_comment|/* How to access the keyboard macros on this platform.  */
DECL|macro|kbd_read_input
mdefine_line|#define kbd_read_input() inb(KBD_DATA_REG)
DECL|macro|kbd_read_status
mdefine_line|#define kbd_read_status() inb(KBD_STATUS_REG)
DECL|macro|kbd_write_output
mdefine_line|#define kbd_write_output(val) outb(val, KBD_DATA_REG)
DECL|macro|kbd_write_command
mdefine_line|#define kbd_write_command(val) outb(val, KBD_CNTL_REG)
multiline_comment|/* Some stoneage hardware needs delays after some operations.  */
DECL|macro|kbd_pause
mdefine_line|#define kbd_pause() do { } while(0)
multiline_comment|/*&n; * Machine specific bits for the PS/2 driver&n; */
DECL|macro|AUX_IRQ
mdefine_line|#define AUX_IRQ 12
DECL|macro|aux_request_irq
mdefine_line|#define aux_request_irq(hand, dev_id)&t;&t;&t;&t;&t;&bslash;&n;&t;request_irq(AUX_IRQ, hand, SA_SHIRQ, &quot;PS/2 Mouse&quot;, dev_id)
DECL|macro|aux_free_irq
mdefine_line|#define aux_free_irq(dev_id) free_irq(AUX_IRQ, dev_id)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _X8664_KEYBOARD_H */
eof
