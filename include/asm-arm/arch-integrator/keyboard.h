multiline_comment|/*&n; *  linux/include/asm-arm/arch-integrator/keyboard.h&n; *&n; *  Copyright (C) 2000-2001 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *  Keyboard driver definitions for the Integrator architecture&n; */
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|NR_SCANCODES
mdefine_line|#define NR_SCANCODES 128
r_extern
r_int
id|kmi_kbd_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|kbd_disable_irq
mdefine_line|#define kbd_disable_irq()&t;disable_irq(IRQ_KMIINT0)
DECL|macro|kbd_enable_irq
mdefine_line|#define kbd_enable_irq()&t;enable_irq(IRQ_KMIINT0)
DECL|macro|kbd_init_hw
mdefine_line|#define kbd_init_hw()&t;&t;kmi_kbd_init()
eof
