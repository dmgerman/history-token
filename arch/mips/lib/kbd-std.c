multiline_comment|/* $Id: kbd-std.c,v 1.2 1999/06/11 14:29:45 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Routines for standard PC style keyboards accessible via I/O ports.&n; *&n; * Copyright (C) 1998, 1999 by Ralf Baechle&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pc_keyb.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ 1
DECL|macro|AUX_IRQ
mdefine_line|#define AUX_IRQ 12
DECL|function|std_kbd_request_region
r_static
r_void
id|std_kbd_request_region
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_MIPS_ITE8172
id|printk
c_func
(paren
l_string|&quot;std_kbd_request_region&bslash;n&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x14000060
comma
l_int|16
comma
l_string|&quot;keyboard&quot;
)paren
suffix:semicolon
macro_line|#else
id|request_region
c_func
(paren
l_int|0x60
comma
l_int|16
comma
l_string|&quot;keyboard&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|std_kbd_request_irq
r_static
r_int
id|std_kbd_request_irq
c_func
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
(brace
id|printk
c_func
(paren
l_string|&quot;std_kbd_request_irq&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|request_irq
c_func
(paren
id|KEYBOARD_IRQ
comma
id|handler
comma
l_int|0
comma
l_string|&quot;keyboard&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|std_aux_request_irq
r_static
r_int
id|std_aux_request_irq
c_func
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
(brace
r_return
id|request_irq
c_func
(paren
id|AUX_IRQ
comma
id|handler
comma
l_int|0
comma
l_string|&quot;PS/2 Mouse&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|std_aux_free_irq
r_static
r_void
id|std_aux_free_irq
c_func
(paren
r_void
)paren
(brace
id|free_irq
c_func
(paren
id|AUX_IRQ
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|std_kbd_read_input
r_static
r_int
r_char
id|std_kbd_read_input
c_func
(paren
r_void
)paren
(brace
r_return
id|inb
c_func
(paren
id|KBD_DATA_REG
)paren
suffix:semicolon
)brace
DECL|function|std_kbd_write_output
r_static
r_void
id|std_kbd_write_output
c_func
(paren
r_int
r_char
id|val
)paren
(brace
r_int
id|status
suffix:semicolon
r_do
(brace
id|status
op_assign
id|inb
c_func
(paren
id|KBD_CNTL_REG
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
op_amp
id|KBD_STAT_IBF
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
comma
id|KBD_DATA_REG
)paren
suffix:semicolon
)brace
DECL|function|std_kbd_write_command
r_static
r_void
id|std_kbd_write_command
c_func
(paren
r_int
r_char
id|val
)paren
(brace
r_int
id|status
suffix:semicolon
r_do
(brace
id|status
op_assign
id|inb
c_func
(paren
id|KBD_CNTL_REG
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
op_amp
id|KBD_STAT_IBF
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
comma
id|KBD_CNTL_REG
)paren
suffix:semicolon
)brace
DECL|function|std_kbd_read_status
r_static
r_int
r_char
id|std_kbd_read_status
c_func
(paren
r_void
)paren
(brace
r_return
id|inb
c_func
(paren
id|KBD_STATUS_REG
)paren
suffix:semicolon
)brace
DECL|variable|std_kbd_ops
r_struct
id|kbd_ops
id|std_kbd_ops
op_assign
(brace
id|std_kbd_request_region
comma
id|std_kbd_request_irq
comma
id|std_aux_request_irq
comma
id|std_aux_free_irq
comma
id|std_kbd_read_input
comma
id|std_kbd_write_output
comma
id|std_kbd_write_command
comma
id|std_kbd_read_status
)brace
suffix:semicolon
eof
