multiline_comment|/*&n; * IBM ASM Service Processor Device Driver&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; *&n; * Copyright (C) IBM Corporation, 2004&n; *&n; * Author: Max Asb&#xfffd;ck &lt;amax@us.ibm.com&gt; &n; *&n; */
multiline_comment|/* Remote mouse and keyboard event handling functions */
macro_line|#include &quot;ibmasm.h&quot;
macro_line|#include &quot;remote.h&quot;
DECL|function|ibmasm_init_remote_queue
r_int
id|ibmasm_init_remote_queue
c_func
(paren
r_struct
id|service_processor
op_star
id|sp
)paren
(brace
r_struct
id|remote_queue
op_star
id|q
op_assign
op_amp
id|sp-&gt;remote_queue
suffix:semicolon
id|disable_mouse_interrupts
c_func
(paren
id|sp
)paren
suffix:semicolon
id|q-&gt;open
op_assign
l_int|0
suffix:semicolon
id|q-&gt;size
op_assign
l_int|0
suffix:semicolon
id|q-&gt;start
op_assign
id|kmalloc
c_func
(paren
id|DRIVER_REMOTE_QUEUE_SIZE
op_star
r_sizeof
(paren
r_struct
id|remote_event
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;start
op_eq
l_int|0
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|q-&gt;end
op_assign
id|q-&gt;start
op_plus
id|DRIVER_REMOTE_QUEUE_SIZE
suffix:semicolon
id|q-&gt;reader
op_assign
id|q-&gt;start
suffix:semicolon
id|q-&gt;writer
op_assign
id|q-&gt;start
suffix:semicolon
id|q-&gt;size
op_assign
id|DRIVER_REMOTE_QUEUE_SIZE
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|q-&gt;wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ibmasm_free_remote_queue
r_void
id|ibmasm_free_remote_queue
c_func
(paren
r_struct
id|service_processor
op_star
id|sp
)paren
(brace
id|kfree
c_func
(paren
id|sp-&gt;remote_queue.start
)paren
suffix:semicolon
)brace
DECL|function|ibmasm_advance_reader
r_void
id|ibmasm_advance_reader
c_func
(paren
r_struct
id|remote_queue
op_star
id|q
comma
r_int
r_int
id|n
)paren
(brace
id|q-&gt;reader
op_add_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;reader
op_ge
id|q-&gt;end
)paren
id|q-&gt;reader
op_sub_assign
id|q-&gt;size
suffix:semicolon
)brace
DECL|function|ibmasm_events_available
r_int
id|ibmasm_events_available
c_func
(paren
r_struct
id|remote_queue
op_star
id|q
)paren
(brace
id|ssize_t
id|diff
op_assign
id|q-&gt;writer
op_minus
id|q-&gt;reader
suffix:semicolon
r_return
(paren
id|diff
op_ge
l_int|0
)paren
ques
c_cond
id|diff
suffix:colon
id|q-&gt;end
op_minus
id|q-&gt;reader
suffix:semicolon
)brace
DECL|function|space_free
r_static
r_int
id|space_free
c_func
(paren
r_struct
id|remote_queue
op_star
id|q
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;reader
op_eq
id|q-&gt;writer
)paren
r_return
id|q-&gt;size
op_minus
l_int|1
suffix:semicolon
r_return
(paren
(paren
id|q-&gt;reader
op_plus
id|q-&gt;size
op_minus
id|q-&gt;writer
)paren
op_mod
id|q-&gt;size
)paren
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|set_mouse_event
r_static
r_void
id|set_mouse_event
c_func
(paren
r_struct
id|remote_input
op_star
id|input
comma
r_struct
id|mouse_event
op_star
id|mouse
)paren
(brace
r_static
r_char
id|last_buttons
op_assign
l_int|0
suffix:semicolon
id|mouse-&gt;x
op_assign
id|input-&gt;data.mouse.x
suffix:semicolon
id|mouse-&gt;y
op_assign
id|input-&gt;data.mouse.y
suffix:semicolon
r_if
c_cond
(paren
id|input-&gt;mouse_buttons
op_eq
id|REMOTE_MOUSE_DOUBLE_CLICK
)paren
(brace
id|mouse-&gt;buttons
op_assign
id|REMOTE_MOUSE_DOUBLE_CLICK
suffix:semicolon
id|last_buttons
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mouse-&gt;transitions
op_assign
id|last_buttons
op_xor
id|input-&gt;mouse_buttons
suffix:semicolon
id|mouse-&gt;buttons
op_assign
id|input-&gt;mouse_buttons
suffix:semicolon
id|last_buttons
op_assign
id|input-&gt;mouse_buttons
suffix:semicolon
)brace
DECL|function|set_keyboard_event
r_static
r_void
id|set_keyboard_event
c_func
(paren
r_struct
id|remote_input
op_star
id|input
comma
r_struct
id|keyboard_event
op_star
id|keyboard
)paren
(brace
id|keyboard-&gt;key_code
op_assign
id|input-&gt;data.keyboard.key_code
suffix:semicolon
id|keyboard-&gt;key_down
op_assign
id|input-&gt;data.keyboard.key_down
suffix:semicolon
)brace
DECL|function|add_to_driver_queue
r_static
r_int
id|add_to_driver_queue
c_func
(paren
r_struct
id|remote_queue
op_star
id|q
comma
r_struct
id|remote_input
op_star
id|input
)paren
(brace
r_struct
id|remote_event
op_star
id|event
op_assign
id|q-&gt;writer
suffix:semicolon
r_if
c_cond
(paren
id|space_free
c_func
(paren
id|q
)paren
OL
l_int|1
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|input-&gt;type
)paren
(brace
r_case
(paren
id|INPUT_TYPE_MOUSE
)paren
suffix:colon
id|event-&gt;type
op_assign
id|INPUT_TYPE_MOUSE
suffix:semicolon
id|set_mouse_event
c_func
(paren
id|input
comma
op_amp
id|event-&gt;data.mouse
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|INPUT_TYPE_KEYBOARD
)paren
suffix:colon
id|event-&gt;type
op_assign
id|INPUT_TYPE_KEYBOARD
suffix:semicolon
id|set_keyboard_event
c_func
(paren
id|input
comma
op_amp
id|event-&gt;data.keyboard
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
id|event-&gt;type
op_assign
id|input-&gt;type
suffix:semicolon
id|q-&gt;writer
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;writer
op_eq
id|q-&gt;end
)paren
id|q-&gt;writer
op_assign
id|q-&gt;start
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ibmasm_handle_mouse_interrupt
r_void
id|ibmasm_handle_mouse_interrupt
c_func
(paren
r_struct
id|service_processor
op_star
id|sp
)paren
(brace
r_int
r_int
id|reader
suffix:semicolon
r_int
r_int
id|writer
suffix:semicolon
r_struct
id|remote_input
id|input
suffix:semicolon
id|reader
op_assign
id|get_queue_reader
c_func
(paren
id|sp
)paren
suffix:semicolon
id|writer
op_assign
id|get_queue_writer
c_func
(paren
id|sp
)paren
suffix:semicolon
r_while
c_loop
(paren
id|reader
op_ne
id|writer
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|input
comma
(paren
r_void
op_star
)paren
id|get_queue_entry
c_func
(paren
id|sp
comma
id|reader
)paren
comma
r_sizeof
(paren
r_struct
id|remote_input
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|add_to_driver_queue
c_func
(paren
op_amp
id|sp-&gt;remote_queue
comma
op_amp
id|input
)paren
)paren
r_break
suffix:semicolon
id|reader
op_assign
id|advance_queue_reader
c_func
(paren
id|sp
comma
id|reader
)paren
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|sp-&gt;remote_queue.wait
)paren
suffix:semicolon
)brace
eof
