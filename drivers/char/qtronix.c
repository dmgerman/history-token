multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Qtronix 990P infrared keyboard driver.&n; *&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *&n; *  The bottom portion of this driver was take from &n; *  pc_keyb.c  Please see that file for copyrights.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* &n; * NOTE:  &n; *&n; *&t;This driver has only been tested with the Consumer IR&n; *&t;port of the ITE 8172 system controller.&n; *&n; *&t;You do not need this driver if you are using the ps/2 or&n; *&t;USB adapter that the keyboard ships with.  You only need &n; *&t;this driver if your board has a IR port and the keyboard&n; *&t;data is being sent directly to the IR.  In that case,&n; *&t;you also need some low-level IR support. See it8172_cir.c.&n; *&t;&n; */
macro_line|#ifdef CONFIG_QTRONIX_KEYBOARD
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/it8172/it8172.h&gt;
macro_line|#include &lt;asm/it8172/it8172_int.h&gt;
macro_line|#include &lt;asm/it8172/it8172_cir.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kbd_ll.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kbd_kern.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/pc_keyb.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|leading1
mdefine_line|#define leading1 0
DECL|macro|leading2
mdefine_line|#define leading2 0xF
DECL|macro|KBD_CIR_PORT
mdefine_line|#define KBD_CIR_PORT 0
DECL|macro|AUX_RECONNECT
mdefine_line|#define AUX_RECONNECT 170 /* scancode when ps2 device is plugged (back) in */
DECL|variable|data_index
r_static
r_int
id|data_index
suffix:semicolon
DECL|variable|cir
r_struct
id|cir_port
op_star
id|cir
suffix:semicolon
DECL|variable|kbdbytes
r_static
r_int
r_char
id|kbdbytes
(braket
l_int|5
)braket
suffix:semicolon
DECL|variable|cir_data
r_static
r_int
r_char
id|cir_data
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* we only need 16 chars */
r_static
r_void
id|kbd_int_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_int
id|handle_data
c_func
(paren
r_int
r_char
op_star
id|p_data
)paren
suffix:semicolon
r_static
r_inline
r_void
id|handle_mouse_event
c_func
(paren
r_int
r_char
id|scancode
)paren
suffix:semicolon
r_static
r_inline
r_void
id|handle_keyboard_event
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
id|down
)paren
suffix:semicolon
r_static
r_int
id|__init
id|psaux_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|queue
r_static
r_struct
id|aux_queue
op_star
id|queue
suffix:semicolon
multiline_comment|/* Mouse data buffer. */
DECL|variable|aux_count
r_static
r_int
id|aux_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Keys accessed through the &squot;Fn&squot; key&n; * The Fn key does not produce a key-up sequence. So, the first&n; * time the user presses it, it will be key-down event. The key&n; * stays down until the user presses it again.&n; */
DECL|macro|NUM_FN_KEYS
mdefine_line|#define NUM_FN_KEYS 56
DECL|variable|fn_keys
r_static
r_int
r_char
id|fn_keys
(braket
id|NUM_FN_KEYS
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0 7   */
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|93
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 8 15  */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|5
comma
multiline_comment|/* 16 23 */
l_int|6
comma
l_int|7
comma
l_int|91
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 24 31 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
multiline_comment|/* 32 39 */
l_int|92
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 40 47 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|11
comma
l_int|0
comma
l_int|94
comma
l_int|95
multiline_comment|/* 48 55 */
)brace
suffix:semicolon
DECL|function|init_qtronix_990P_kbd
r_void
id|__init
id|init_qtronix_990P_kbd
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|cir
op_assign
(paren
r_struct
id|cir_port
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cir_port
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cir
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to initialize Qtronix keyboard&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * revisit&n;&t; * this should be programmable, somehow by the, by the user.&n;&t; */
id|cir-&gt;port
op_assign
id|KBD_CIR_PORT
suffix:semicolon
id|cir-&gt;baud_rate
op_assign
l_int|0x1d
suffix:semicolon
id|cir-&gt;rdwos
op_assign
l_int|0
suffix:semicolon
id|cir-&gt;rxdcr
op_assign
l_int|0x3
suffix:semicolon
id|cir-&gt;hcfs
op_assign
l_int|0
suffix:semicolon
id|cir-&gt;fifo_tl
op_assign
l_int|0
suffix:semicolon
id|cir-&gt;cfq
op_assign
l_int|0x1d
suffix:semicolon
id|cir_port_init
c_func
(paren
id|cir
)paren
suffix:semicolon
id|retval
op_assign
id|request_irq
c_func
(paren
id|IT8172_CIR0_IRQ
comma
id|kbd_int_handler
comma
(paren
r_int
r_int
)paren
(paren
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
)paren
comma
(paren
r_const
r_char
op_star
)paren
l_string|&quot;Qtronix IR Keyboard&quot;
comma
(paren
r_void
op_star
)paren
id|cir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unable to allocate cir %d irq %d&bslash;n&quot;
comma
id|cir-&gt;port
comma
id|IT8172_CIR0_IRQ
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PSMOUSE
id|psaux_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|BitReverse
r_static
r_inline
r_int
r_char
id|BitReverse
c_func
(paren
r_int
r_int
id|key
)paren
(brace
r_int
r_char
id|rkey
op_assign
l_int|0
suffix:semicolon
id|rkey
op_or_assign
(paren
id|key
op_amp
l_int|0x1
)paren
op_lshift
l_int|7
suffix:semicolon
id|rkey
op_or_assign
(paren
id|key
op_amp
l_int|0x2
)paren
op_lshift
l_int|5
suffix:semicolon
id|rkey
op_or_assign
(paren
id|key
op_amp
l_int|0x4
)paren
op_lshift
l_int|3
suffix:semicolon
id|rkey
op_or_assign
(paren
id|key
op_amp
l_int|0x8
)paren
op_lshift
l_int|1
suffix:semicolon
id|rkey
op_or_assign
(paren
id|key
op_amp
l_int|0x10
)paren
op_rshift
l_int|1
suffix:semicolon
id|rkey
op_or_assign
(paren
id|key
op_amp
l_int|0x20
)paren
op_rshift
l_int|3
suffix:semicolon
id|rkey
op_or_assign
(paren
id|key
op_amp
l_int|0x40
)paren
op_rshift
l_int|5
suffix:semicolon
id|rkey
op_or_assign
(paren
id|key
op_amp
l_int|0x80
)paren
op_rshift
l_int|7
suffix:semicolon
r_return
id|rkey
suffix:semicolon
)brace
DECL|function|UpperByte
r_static
r_inline
id|u_int8_t
id|UpperByte
c_func
(paren
id|u_int8_t
id|data
)paren
(brace
r_return
(paren
id|data
op_rshift
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|LowerByte
r_static
r_inline
id|u_int8_t
id|LowerByte
c_func
(paren
id|u_int8_t
id|data
)paren
(brace
r_return
(paren
id|data
op_amp
l_int|0xF
)paren
suffix:semicolon
)brace
DECL|function|CheckSumOk
r_int
id|CheckSumOk
c_func
(paren
id|u_int8_t
id|byte1
comma
id|u_int8_t
id|byte2
comma
id|u_int8_t
id|byte3
comma
id|u_int8_t
id|byte4
comma
id|u_int8_t
id|byte5
)paren
(brace
id|u_int8_t
id|CheckSum
suffix:semicolon
id|CheckSum
op_assign
(paren
id|byte1
op_amp
l_int|0x0F
)paren
op_plus
id|byte2
op_plus
id|byte3
op_plus
id|byte4
op_plus
id|byte5
suffix:semicolon
r_if
c_cond
(paren
id|LowerByte
c_func
(paren
id|UpperByte
c_func
(paren
id|CheckSum
)paren
op_plus
id|LowerByte
c_func
(paren
id|CheckSum
)paren
)paren
op_ne
id|UpperByte
c_func
(paren
id|byte1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kbd_int_handler
r_static
r_void
id|kbd_int_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|cir_port
op_star
id|cir
suffix:semicolon
r_int
id|j
suffix:semicolon
r_int
r_char
id|int_status
suffix:semicolon
id|cir
op_assign
(paren
r_struct
id|cir_port
op_star
)paren
id|dev_id
suffix:semicolon
id|int_status
op_assign
id|get_int_status
c_func
(paren
id|cir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|int_status
op_amp
l_int|0x4
)paren
(brace
id|clear_fifo
c_func
(paren
id|cir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cir_get_rx_count
c_func
(paren
id|cir
)paren
)paren
(brace
id|cir_data
(braket
id|data_index
)braket
op_assign
id|cir_read_data
c_func
(paren
id|cir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data_index
op_eq
l_int|0
)paren
(brace
multiline_comment|/* expecting first byte */
r_if
c_cond
(paren
id|cir_data
(braket
id|data_index
)braket
op_ne
id|leading1
)paren
(brace
singleline_comment|//printk(&quot;!leading byte %x&bslash;n&quot;, cir_data[data_index]);
id|set_rx_active
c_func
(paren
id|cir
)paren
suffix:semicolon
id|clear_fifo
c_func
(paren
id|cir
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|data_index
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|cir_data
(braket
id|data_index
)braket
op_amp
l_int|0xf
)paren
op_ne
id|leading2
)paren
(brace
id|set_rx_active
c_func
(paren
id|cir
)paren
suffix:semicolon
id|data_index
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* start over */
id|clear_fifo
c_func
(paren
id|cir
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|cir_data
(braket
id|data_index
)braket
op_eq
l_int|0xff
)paren
)paren
(brace
multiline_comment|/* last byte */
singleline_comment|//printk(&quot;data_index %d&bslash;n&quot;, data_index);
id|set_rx_active
c_func
(paren
id|cir
)paren
suffix:semicolon
macro_line|#if 0
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
op_le
id|data_index
suffix:semicolon
id|j
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;rx_data %d:  %x&bslash;n&quot;
comma
id|j
comma
id|cir_data
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
id|data_index
op_assign
l_int|0
suffix:semicolon
id|handle_data
c_func
(paren
id|cir_data
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|data_index
OG
l_int|16
)paren
(brace
id|set_rx_active
c_func
(paren
id|cir
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;warning: data_index %d&bslash;n&quot;
comma
id|data_index
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
op_le
id|data_index
suffix:semicolon
id|j
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;rx_data %d:  %x&bslash;n&quot;
comma
id|j
comma
id|cir_data
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
id|data_index
op_assign
l_int|0
suffix:semicolon
id|clear_fifo
c_func
(paren
id|cir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|data_index
op_increment
suffix:semicolon
)brace
)brace
DECL|macro|NUM_KBD_BYTES
mdefine_line|#define NUM_KBD_BYTES 5
DECL|function|handle_data
r_static
r_int
id|handle_data
c_func
(paren
r_int
r_char
op_star
id|p_data
)paren
(brace
id|u_int32_t
id|bit_bucket
suffix:semicolon
id|u_int32_t
id|i
comma
id|j
suffix:semicolon
id|u_int32_t
id|got_bits
comma
id|next_byte
suffix:semicolon
r_int
id|down
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Reorganize the bit stream */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|p_data
(braket
id|i
)braket
op_assign
id|BitReverse
c_func
(paren
op_complement
id|p_data
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * We&squot;ve already previously checked that p_data[0]&n;&t; * is equal to leading1 and that (p_data[1] &amp; 0xf)&n;&t; * is equal to leading2. These twelve bits are the&n;&t; * leader code.  We can now throw them away (the 12&n;&t; * bits) and continue parsing the stream.&n;&t; */
id|bit_bucket
op_assign
id|p_data
(braket
l_int|1
)braket
op_lshift
l_int|12
suffix:semicolon
id|got_bits
op_assign
l_int|4
suffix:semicolon
id|next_byte
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* &n;&t; * Process four bits at a time&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_KBD_BYTES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|kbdbytes
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
multiline_comment|/* 8 bits per byte */
(brace
r_if
c_cond
(paren
id|got_bits
OL
l_int|4
)paren
(brace
id|bit_bucket
op_or_assign
(paren
id|p_data
(braket
id|next_byte
op_increment
)braket
op_lshift
(paren
l_int|8
op_minus
id|got_bits
)paren
)paren
suffix:semicolon
id|got_bits
op_add_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|bit_bucket
op_amp
l_int|0xF000
)paren
op_eq
l_int|0x8000
)paren
(brace
multiline_comment|/* Convert 1000b to 1 */
id|kbdbytes
(braket
id|i
)braket
op_assign
l_int|0x80
op_or
(paren
id|kbdbytes
(braket
id|i
)braket
op_rshift
l_int|1
)paren
suffix:semicolon
id|got_bits
op_sub_assign
l_int|4
suffix:semicolon
id|bit_bucket
op_assign
id|bit_bucket
op_lshift
l_int|4
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|bit_bucket
op_amp
l_int|0xC000
)paren
op_eq
l_int|0x8000
)paren
(brace
multiline_comment|/* Convert 10b to 0 */
id|kbdbytes
(braket
id|i
)braket
op_assign
id|kbdbytes
(braket
id|i
)braket
op_rshift
l_int|1
suffix:semicolon
id|got_bits
op_sub_assign
l_int|2
suffix:semicolon
id|bit_bucket
op_assign
id|bit_bucket
op_lshift
l_int|2
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* bad serial stream */
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|next_byte
OG
l_int|16
)paren
(brace
singleline_comment|//printk(&quot;error: too many bytes&bslash;n&quot;);
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|CheckSumOk
c_func
(paren
id|kbdbytes
(braket
l_int|0
)braket
comma
id|kbdbytes
(braket
l_int|1
)braket
comma
id|kbdbytes
(braket
l_int|2
)braket
comma
id|kbdbytes
(braket
l_int|3
)braket
comma
id|kbdbytes
(braket
l_int|4
)braket
)paren
)paren
(brace
singleline_comment|//printk(&quot;checksum failed&bslash;n&quot;);
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kbdbytes
(braket
l_int|1
)braket
op_amp
l_int|0x08
)paren
(brace
singleline_comment|//printk(&quot;m: %x %x %x&bslash;n&quot;, kbdbytes[1], kbdbytes[2], kbdbytes[3]);
id|handle_mouse_event
c_func
(paren
id|kbdbytes
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|handle_mouse_event
c_func
(paren
id|kbdbytes
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|handle_mouse_event
c_func
(paren
id|kbdbytes
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|kbdbytes
(braket
l_int|2
)braket
op_eq
l_int|0
)paren
id|down
op_assign
l_int|1
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|down
)paren
id|printk
c_func
(paren
l_string|&quot;down %d&bslash;n&quot;
comma
id|kbdbytes
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;up %d&bslash;n&quot;
comma
id|kbdbytes
(braket
l_int|3
)braket
)paren
suffix:semicolon
macro_line|#endif
id|handle_keyboard_event
c_func
(paren
id|kbdbytes
(braket
l_int|3
)braket
comma
id|down
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|kbd_controller_lock
id|DEFINE_SPINLOCK
c_func
(paren
id|kbd_controller_lock
)paren
suffix:semicolon
r_static
r_int
r_char
id|handle_kbd_event
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|kbd_setkeycode
r_int
id|kbd_setkeycode
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
(brace
id|printk
c_func
(paren
l_string|&quot;kbd_setkeycode scancode %x keycode %x&bslash;n&quot;
comma
id|scancode
comma
id|keycode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kbd_getkeycode
r_int
id|kbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
(brace
r_return
id|scancode
suffix:semicolon
)brace
DECL|function|kbd_translate
r_int
id|kbd_translate
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
(brace
r_static
r_int
id|prev_scancode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|scancode
op_eq
l_int|0x00
op_logical_or
id|scancode
op_eq
l_int|0xff
)paren
(brace
id|prev_scancode
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* todo */
r_if
c_cond
(paren
op_logical_neg
id|prev_scancode
op_logical_and
id|scancode
op_eq
l_int|160
)paren
(brace
multiline_comment|/* Fn key down */
singleline_comment|//printk(&quot;Fn key down&bslash;n&quot;);
id|prev_scancode
op_assign
l_int|160
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|prev_scancode
op_logical_and
id|scancode
op_eq
l_int|160
)paren
(brace
multiline_comment|/* Fn key up */
singleline_comment|//printk(&quot;Fn key up&bslash;n&quot;);
id|prev_scancode
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* todo */
r_if
c_cond
(paren
id|prev_scancode
op_eq
l_int|160
)paren
(brace
r_if
c_cond
(paren
id|scancode
op_le
id|NUM_FN_KEYS
)paren
(brace
op_star
id|keycode
op_assign
id|fn_keys
(braket
id|scancode
)braket
suffix:semicolon
singleline_comment|//printk(&quot;fn keycode %d&bslash;n&quot;, *keycode);
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|scancode
op_le
l_int|127
)paren
(brace
op_star
id|keycode
op_assign
id|scancode
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kbd_unexpected_up
r_char
id|kbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
(brace
singleline_comment|//printk(&quot;kbd_unexpected_up&bslash;n&quot;);
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|kbd_exists
r_static
r_int
r_char
id|kbd_exists
op_assign
l_int|1
suffix:semicolon
DECL|function|handle_keyboard_event
r_static
r_inline
r_void
id|handle_keyboard_event
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
id|down
)paren
(brace
id|kbd_exists
op_assign
l_int|1
suffix:semicolon
id|handle_scancode
c_func
(paren
id|scancode
comma
id|down
)paren
suffix:semicolon
id|tasklet_schedule
c_func
(paren
op_amp
id|keyboard_tasklet
)paren
suffix:semicolon
)brace
DECL|function|kbd_leds
r_void
id|kbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
(brace
)brace
multiline_comment|/* dummy */
DECL|function|kbd_init_hw
r_void
id|kbd_init_hw
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|handle_mouse_event
r_static
r_inline
r_void
id|handle_mouse_event
c_func
(paren
r_int
r_char
id|scancode
)paren
(brace
r_if
c_cond
(paren
id|scancode
op_eq
id|AUX_RECONNECT
)paren
(brace
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Flush input queue */
singleline_comment|//&t;__aux_write_ack(AUX_ENABLE_DEV);  /* ping the mouse :) */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aux_count
)paren
(brace
r_int
id|head
op_assign
id|queue-&gt;head
suffix:semicolon
id|queue-&gt;buf
(braket
id|head
)braket
op_assign
id|scancode
suffix:semicolon
id|head
op_assign
(paren
id|head
op_plus
l_int|1
)paren
op_amp
(paren
id|AUX_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head
op_ne
id|queue-&gt;tail
)paren
(brace
id|queue-&gt;head
op_assign
id|head
suffix:semicolon
id|kill_fasync
c_func
(paren
op_amp
id|queue-&gt;fasync
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|queue-&gt;proc_list
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|get_from_queue
r_static
r_int
r_char
id|get_from_queue
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|result
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|kbd_controller_lock
comma
id|flags
)paren
suffix:semicolon
id|result
op_assign
id|queue-&gt;buf
(braket
id|queue-&gt;tail
)braket
suffix:semicolon
id|queue-&gt;tail
op_assign
(paren
id|queue-&gt;tail
op_plus
l_int|1
)paren
op_amp
(paren
id|AUX_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|kbd_controller_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|queue_empty
r_static
r_inline
r_int
id|queue_empty
c_func
(paren
r_void
)paren
(brace
r_return
id|queue-&gt;head
op_eq
id|queue-&gt;tail
suffix:semicolon
)brace
DECL|function|fasync_aux
r_static
r_int
id|fasync_aux
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
id|on
)paren
(brace
r_int
id|retval
suffix:semicolon
singleline_comment|//printk(&quot;fasync_aux&bslash;n&quot;);
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|filp
comma
id|on
comma
op_amp
id|queue-&gt;fasync
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Random magic cookie for the aux device&n; */
DECL|macro|AUX_DEV
mdefine_line|#define AUX_DEV ((void *)queue)
DECL|function|release_aux
r_static
r_int
id|release_aux
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
id|fasync_aux
c_func
(paren
op_minus
l_int|1
comma
id|file
comma
l_int|0
)paren
suffix:semicolon
id|aux_count
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|open_aux
r_static
r_int
id|open_aux
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
id|aux_count
op_increment
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Flush input queue */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Put bytes from input queue to buffer.&n; */
DECL|function|read_aux
r_static
id|ssize_t
id|read_aux
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|ssize_t
id|i
op_assign
id|count
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|queue_empty
c_func
(paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|queue-&gt;proc_list
comma
op_amp
id|wait
)paren
suffix:semicolon
id|repeat
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|queue_empty
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|queue-&gt;proc_list
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OG
l_int|0
op_logical_and
op_logical_neg
id|queue_empty
c_func
(paren
)paren
)paren
(brace
id|c
op_assign
id|get_from_queue
c_func
(paren
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|c
comma
id|buffer
op_increment
)paren
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_minus
id|i
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|current_fs_time
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_return
id|count
op_minus
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write to the aux device.&n; */
DECL|function|write_aux
r_static
id|ssize_t
id|write_aux
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
multiline_comment|/*&n;&t; * The ITE boards this was tested on did not have the&n;&t; * transmit wires connected.&n;&t; */
r_return
id|count
suffix:semicolon
)brace
DECL|function|aux_poll
r_static
r_int
r_int
id|aux_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|queue-&gt;proc_list
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|queue_empty
c_func
(paren
)paren
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|psaux_fops
r_struct
id|file_operations
id|psaux_fops
op_assign
(brace
dot
id|read
op_assign
id|read_aux
comma
dot
id|write
op_assign
id|write_aux
comma
dot
id|poll
op_assign
id|aux_poll
comma
dot
id|open
op_assign
id|open_aux
comma
dot
id|release
op_assign
id|release_aux
comma
dot
id|fasync
op_assign
id|fasync_aux
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialize driver.&n; */
DECL|variable|psaux_mouse
r_static
r_struct
id|miscdevice
id|psaux_mouse
op_assign
(brace
id|PSMOUSE_MINOR
comma
l_string|&quot;psaux&quot;
comma
op_amp
id|psaux_fops
)brace
suffix:semicolon
DECL|function|psaux_init
r_static
r_int
id|__init
id|psaux_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|misc_register
c_func
(paren
op_amp
id|psaux_mouse
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
r_return
id|retval
suffix:semicolon
)brace
id|queue
op_assign
(paren
r_struct
id|aux_queue
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|queue
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|queue
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|queue
)paren
)paren
suffix:semicolon
id|queue-&gt;head
op_assign
id|queue-&gt;tail
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|queue-&gt;proc_list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_qtronix_990P_kbd
id|module_init
c_func
(paren
id|init_qtronix_990P_kbd
)paren
suffix:semicolon
macro_line|#endif
eof
