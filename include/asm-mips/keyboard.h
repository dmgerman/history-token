multiline_comment|/* $Id: keyboard.h,v 1.14 1999/08/19 22:56:33 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999 Ralf Baechle&n; */
macro_line|#ifndef _ASM_KEYBOARD_H
DECL|macro|_ASM_KEYBOARD_H
mdefine_line|#define _ASM_KEYBOARD_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
DECL|macro|DISABLE_KBD_DURING_INTERRUPTS
mdefine_line|#define DISABLE_KBD_DURING_INTERRUPTS 0
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
r_char
id|pckbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
r_extern
r_void
id|kbd_forward_char
(paren
r_int
id|ch
)paren
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
mdefine_line|#define kbd_sysrq_xlate         pckbd_sysrq_xlate
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY 0x54
multiline_comment|/* Some stoneage hardware needs delays after some operations.  */
DECL|macro|kbd_pause
mdefine_line|#define kbd_pause() do { } while(0)
DECL|struct|kbd_ops
r_struct
id|kbd_ops
(brace
multiline_comment|/* Keyboard driver resource allocation  */
DECL|member|kbd_request_region
r_void
(paren
op_star
id|kbd_request_region
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|kbd_request_irq
r_int
(paren
op_star
id|kbd_request_irq
)paren
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/* PSaux driver resource managment  */
DECL|member|aux_request_irq
r_int
(paren
op_star
id|aux_request_irq
)paren
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
suffix:semicolon
DECL|member|aux_free_irq
r_void
(paren
op_star
id|aux_free_irq
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Methods to access the keyboard processor&squot;s I/O registers  */
DECL|member|kbd_read_input
r_int
r_char
(paren
op_star
id|kbd_read_input
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|kbd_write_output
r_void
(paren
op_star
id|kbd_write_output
)paren
(paren
r_int
r_char
id|val
)paren
suffix:semicolon
DECL|member|kbd_write_command
r_void
(paren
op_star
id|kbd_write_command
)paren
(paren
r_int
r_char
id|val
)paren
suffix:semicolon
DECL|member|kbd_read_status
r_int
r_char
(paren
op_star
id|kbd_read_status
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|kbd_ops
op_star
id|kbd_ops
suffix:semicolon
multiline_comment|/* Do the actual calls via kbd_ops vector  */
DECL|macro|kbd_request_region
mdefine_line|#define kbd_request_region() kbd_ops-&gt;kbd_request_region()
DECL|macro|kbd_request_irq
mdefine_line|#define kbd_request_irq(handler) kbd_ops-&gt;kbd_request_irq(handler)
DECL|macro|aux_request_irq
mdefine_line|#define aux_request_irq(hand, dev_id) kbd_ops-&gt;aux_request_irq(hand)
DECL|macro|aux_free_irq
mdefine_line|#define aux_free_irq(dev_id) kbd_ops-&gt;aux_free_irq()
DECL|macro|kbd_read_input
mdefine_line|#define kbd_read_input() kbd_ops-&gt;kbd_read_input()
DECL|macro|kbd_write_output
mdefine_line|#define kbd_write_output(val) kbd_ops-&gt;kbd_write_output(val)
DECL|macro|kbd_write_command
mdefine_line|#define kbd_write_command(val) kbd_ops-&gt;kbd_write_command(val)
DECL|macro|kbd_read_status
mdefine_line|#define kbd_read_status() kbd_ops-&gt;kbd_read_status()
macro_line|#endif /* __KERNEL */
macro_line|#endif /* _ASM_KEYBOARD_H */
eof
