multiline_comment|/*&n; *  linux/include/asm-arm/arch-integrator/keyboard.h&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *  Keyboard driver definitions for the Integrator architecture&n; */
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
r_extern
r_int
r_char
id|kmi_kbd_sysrq_xlate
(braket
id|NR_SCANCODES
)braket
suffix:semicolon
r_extern
r_int
id|kmi_kbd_setkeycode
c_func
(paren
id|u_int
id|scancode
comma
id|u_int
id|keycode
)paren
suffix:semicolon
r_extern
r_int
id|kmi_kbd_getkeycode
c_func
(paren
id|u_int
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|kmi_kbd_translate
c_func
(paren
id|u_char
id|scancode
comma
id|u_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
suffix:semicolon
r_extern
r_char
id|kmi_kbd_unexpected_up
c_func
(paren
id|u_char
id|keycode
)paren
suffix:semicolon
r_extern
r_void
id|kmi_kbd_leds
c_func
(paren
id|u_char
id|leds
)paren
suffix:semicolon
r_extern
r_int
id|kmi_kbd_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|kbd_setkeycode
mdefine_line|#define kbd_setkeycode(sc,kc)&t;&t;kmi_kbd_setkeycode(sc,kc)
DECL|macro|kbd_getkeycode
mdefine_line|#define kbd_getkeycode(sc)&t;&t;kmi_kbd_getkeycode(sc)
DECL|macro|kbd_translate
mdefine_line|#define kbd_translate(sc, kcp, rm)&t;kmi_kbd_translate(sc,kcp,rm)
DECL|macro|kbd_unexpected_up
mdefine_line|#define kbd_unexpected_up(kc)&t;&t;kmi_kbd_unexpected_up(kc)
DECL|macro|kbd_leds
mdefine_line|#define kbd_leds(leds)&t;&t;&t;kmi_kbd_leds(leds)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;&t;&t;kmi_kbd_init()
DECL|macro|kbd_sysrq_xlate
mdefine_line|#define kbd_sysrq_xlate&t;&t;&t;kmi_kbd_sysrq_xlate
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()&t;&t;disable_irq(IRQ_KMIINT0)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()&t;&t;enable_irq(IRQ_KMIINT0)
DECL|macro|SYSRQ_KEY
mdefine_line|#define SYSRQ_KEY&t;&t;&t;0x54
eof
