multiline_comment|/*&n; * IBM ASM Service Processor Device Driver&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; *&n; * Copyright (C) IBM Corporation, 2004&n; *&n; * Author: Max Asb&#xfffd;ck &lt;amax@us.ibm.com&gt; &n; *&n; * Orignally written by Pete Reynolds&n; */
macro_line|#ifndef _IBMASM_REMOTE_H_
DECL|macro|_IBMASM_REMOTE_H_
mdefine_line|#define _IBMASM_REMOTE_H_
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* pci offsets */
DECL|macro|CONDOR_MOUSE_DATA
mdefine_line|#define CONDOR_MOUSE_DATA&t;&t;0x000AC000
DECL|macro|CONDOR_MOUSE_ISR_CONTROL
mdefine_line|#define CONDOR_MOUSE_ISR_CONTROL&t;0x00
DECL|macro|CONDOR_MOUSE_ISR_STATUS
mdefine_line|#define CONDOR_MOUSE_ISR_STATUS&t;&t;0x04
DECL|macro|CONDOR_MOUSE_Q_READER
mdefine_line|#define CONDOR_MOUSE_Q_READER&t;&t;0x08
DECL|macro|CONDOR_MOUSE_Q_WRITER
mdefine_line|#define CONDOR_MOUSE_Q_WRITER&t;&t;0x0C
DECL|macro|CONDOR_MOUSE_Q_BEGIN
mdefine_line|#define CONDOR_MOUSE_Q_BEGIN&t;&t;0x10
DECL|macro|CONDOR_MOUSE_MAX_X
mdefine_line|#define CONDOR_MOUSE_MAX_X&t;&t;0x14
DECL|macro|CONDOR_MOUSE_MAX_Y
mdefine_line|#define CONDOR_MOUSE_MAX_Y&t;&t;0x18
DECL|macro|CONDOR_INPUT_DESKTOP_INFO
mdefine_line|#define CONDOR_INPUT_DESKTOP_INFO&t;0x1F0
DECL|macro|CONDOR_INPUT_DISPLAY_RESX
mdefine_line|#define CONDOR_INPUT_DISPLAY_RESX&t;0x1F4
DECL|macro|CONDOR_INPUT_DISPLAY_RESY
mdefine_line|#define CONDOR_INPUT_DISPLAY_RESY&t;0x1F8
DECL|macro|CONDOR_INPUT_DISPLAY_BITS
mdefine_line|#define CONDOR_INPUT_DISPLAY_BITS&t;0x1FC
DECL|macro|CONDOR_OUTPUT_VNC_STATUS
mdefine_line|#define CONDOR_OUTPUT_VNC_STATUS&t;0x200
DECL|macro|CONDOR_MOUSE_INTR_STATUS_MASK
mdefine_line|#define CONDOR_MOUSE_INTR_STATUS_MASK&t;0x00000001
DECL|macro|INPUT_TYPE_MOUSE
mdefine_line|#define INPUT_TYPE_MOUSE&t;0x1
DECL|macro|INPUT_TYPE_KEYBOARD
mdefine_line|#define INPUT_TYPE_KEYBOARD&t;0x2
multiline_comment|/* mouse button states received from SP */
DECL|macro|REMOTE_MOUSE_DOUBLE_CLICK
mdefine_line|#define REMOTE_MOUSE_DOUBLE_CLICK&t;0xF0
DECL|macro|REMOTE_MOUSE_BUTTON_LEFT
mdefine_line|#define REMOTE_MOUSE_BUTTON_LEFT&t;0x01
DECL|macro|REMOTE_MOUSE_BUTTON_MIDDLE
mdefine_line|#define REMOTE_MOUSE_BUTTON_MIDDLE&t;0x02
DECL|macro|REMOTE_MOUSE_BUTTON_RIGHT
mdefine_line|#define REMOTE_MOUSE_BUTTON_RIGHT&t;0x04
DECL|struct|mouse_input
r_struct
id|mouse_input
(brace
DECL|member|y
r_int
r_int
id|y
suffix:semicolon
DECL|member|x
r_int
r_int
id|x
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|keyboard_input
r_struct
id|keyboard_input
(brace
DECL|member|key_code
r_int
r_int
id|key_code
suffix:semicolon
DECL|member|key_flag
r_int
r_char
id|key_flag
suffix:semicolon
DECL|member|key_down
r_int
r_char
id|key_down
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|remote_input
r_struct
id|remote_input
(brace
r_union
(brace
DECL|member|mouse
r_struct
id|mouse_input
id|mouse
suffix:semicolon
DECL|member|keyboard
r_struct
id|keyboard_input
id|keyboard
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|pad1
r_int
r_char
id|pad1
suffix:semicolon
DECL|member|mouse_buttons
r_int
r_char
id|mouse_buttons
suffix:semicolon
DECL|member|pad3
r_int
r_char
id|pad3
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|mouse_addr
mdefine_line|#define mouse_addr(sp) &t;&t;sp-&gt;base_address + CONDOR_MOUSE_DATA
DECL|macro|display_width
mdefine_line|#define display_width(sp)&t;mouse_addr(sp) + CONDOR_INPUT_DISPLAY_RESX
DECL|macro|display_height
mdefine_line|#define display_height(sp)&t;mouse_addr(sp) + CONDOR_INPUT_DISPLAY_RESY
DECL|macro|display_depth
mdefine_line|#define display_depth(sp)&t;mouse_addr(sp) + CONDOR_INPUT_DISPLAY_BITS
DECL|macro|vnc_status
mdefine_line|#define vnc_status(sp)&t;&t;mouse_addr(sp) + CONDOR_OUTPUT_VNC_STATUS
DECL|macro|mouse_interrupt_pending
mdefine_line|#define mouse_interrupt_pending(sp) &t;readl(mouse_addr(sp) + CONDOR_MOUSE_ISR_STATUS)
DECL|macro|clear_mouse_interrupt
mdefine_line|#define clear_mouse_interrupt(sp)&t;writel(0, mouse_addr(sp) + CONDOR_MOUSE_ISR_STATUS)
DECL|macro|enable_mouse_interrupts
mdefine_line|#define enable_mouse_interrupts(sp)&t;writel(1, mouse_addr(sp) + CONDOR_MOUSE_ISR_CONTROL)
DECL|macro|disable_mouse_interrupts
mdefine_line|#define disable_mouse_interrupts(sp)&t;writel(0, mouse_addr(sp) + CONDOR_MOUSE_ISR_CONTROL)
multiline_comment|/* remote input queue operations */
DECL|macro|REMOTE_QUEUE_SIZE
mdefine_line|#define REMOTE_QUEUE_SIZE&t;60
DECL|macro|get_queue_writer
mdefine_line|#define get_queue_writer(sp)&t;readl(mouse_addr(sp) + CONDOR_MOUSE_Q_WRITER)
DECL|macro|get_queue_reader
mdefine_line|#define get_queue_reader(sp)&t;readl(mouse_addr(sp) + CONDOR_MOUSE_Q_READER)
DECL|macro|set_queue_reader
mdefine_line|#define set_queue_reader(sp, reader)&t;writel(reader, mouse_addr(sp) + CONDOR_MOUSE_Q_READER)
DECL|macro|queue_begin
mdefine_line|#define queue_begin&t;mouse_addr(sp) + CONDOR_MOUSE_Q_BEGIN
DECL|macro|get_queue_entry
mdefine_line|#define get_queue_entry(sp, read_index) &bslash;&n;&t;queue_begin + read_index * sizeof(struct remote_input)
DECL|function|advance_queue_reader
r_static
r_inline
r_int
id|advance_queue_reader
c_func
(paren
r_struct
id|service_processor
op_star
id|sp
comma
r_int
r_int
id|reader
)paren
(brace
id|reader
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|reader
op_eq
id|REMOTE_QUEUE_SIZE
)paren
id|reader
op_assign
l_int|0
suffix:semicolon
id|set_queue_reader
c_func
(paren
id|sp
comma
id|reader
)paren
suffix:semicolon
r_return
id|reader
suffix:semicolon
)brace
macro_line|#endif /* _IBMASM_REMOTE_H_ */
eof
