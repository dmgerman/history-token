multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Routines for the GF1 MIDI interface - like UART 6850&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/gus.h&gt;
DECL|function|snd_gf1_interrupt_midi_in
r_static
r_void
id|snd_gf1_interrupt_midi_in
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
r_int
id|count
suffix:semicolon
r_int
r_char
id|stat
comma
id|data
comma
id|byte
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|count
op_assign
l_int|10
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
id|stat
op_assign
id|snd_gf1_uart_stat
c_func
(paren
id|gus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|stat
op_amp
l_int|0x01
)paren
)paren
(brace
multiline_comment|/* data in Rx FIFO? */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|count
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* arm counter to new value */
id|data
op_assign
id|snd_gf1_uart_get
c_func
(paren
id|gus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|gus-&gt;gf1.uart_cmd
op_amp
l_int|0x80
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stat
op_amp
l_int|0x10
)paren
(brace
multiline_comment|/* framing error */
id|gus-&gt;gf1.uart_framing
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|byte
op_assign
id|snd_gf1_uart_get
c_func
(paren
id|gus
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_rawmidi_receive
c_func
(paren
id|gus-&gt;midi_substream_input
comma
op_amp
id|byte
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
l_int|0x20
)paren
(brace
id|gus-&gt;gf1.uart_overrun
op_increment
suffix:semicolon
)brace
)brace
)brace
DECL|function|snd_gf1_interrupt_midi_out
r_static
r_void
id|snd_gf1_interrupt_midi_out
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
r_char
id|byte
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* try unlock output */
r_if
c_cond
(paren
id|snd_gf1_uart_stat
c_func
(paren
id|gus
)paren
op_amp
l_int|0x01
)paren
id|snd_gf1_interrupt_midi_in
c_func
(paren
id|gus
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_gf1_uart_stat
c_func
(paren
id|gus
)paren
op_amp
l_int|0x02
)paren
(brace
multiline_comment|/* Tx FIFO free? */
r_if
c_cond
(paren
id|snd_rawmidi_transmit
c_func
(paren
id|gus-&gt;midi_substream_output
comma
op_amp
id|byte
comma
l_int|1
)paren
op_ne
l_int|1
)paren
(brace
multiline_comment|/* no other bytes or error */
id|snd_gf1_uart_cmd
c_func
(paren
id|gus
comma
id|gus-&gt;gf1.uart_cmd
op_amp
op_complement
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* disable Tx interrupt */
)brace
r_else
(brace
id|snd_gf1_uart_put
c_func
(paren
id|gus
comma
id|byte
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_uart_reset
r_static
r_void
id|snd_gf1_uart_reset
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
r_int
id|close
)paren
(brace
id|snd_gf1_uart_cmd
c_func
(paren
id|gus
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* reset */
r_if
c_cond
(paren
op_logical_neg
id|close
op_logical_and
id|gus-&gt;uart_enable
)paren
(brace
id|udelay
c_func
(paren
l_int|160
)paren
suffix:semicolon
id|snd_gf1_uart_cmd
c_func
(paren
id|gus
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* normal operations */
)brace
)brace
DECL|function|snd_gf1_uart_output_open
r_static
r_int
id|snd_gf1_uart_output_open
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|snd_gus_card_t
op_star
id|gus
suffix:semicolon
id|gus
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|gus-&gt;gf1.uart_cmd
op_amp
l_int|0x80
)paren
)paren
(brace
multiline_comment|/* input active? */
id|snd_gf1_uart_reset
c_func
(paren
id|gus
comma
l_int|0
)paren
suffix:semicolon
)brace
id|gus-&gt;gf1.interrupt_handler_midi_out
op_assign
id|snd_gf1_interrupt_midi_out
suffix:semicolon
id|gus-&gt;midi_substream_output
op_assign
id|substream
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#if 0
id|snd_printk
c_func
(paren
l_string|&quot;write init - cmd = 0x%x, stat = 0x%x&bslash;n&quot;
comma
id|gus-&gt;gf1.uart_cmd
comma
id|snd_gf1_uart_stat
c_func
(paren
id|gus
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gf1_uart_input_open
r_static
r_int
id|snd_gf1_uart_input_open
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|snd_gus_card_t
op_star
id|gus
suffix:semicolon
r_int
id|i
suffix:semicolon
id|gus
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.interrupt_handler_midi_out
op_ne
id|snd_gf1_interrupt_midi_out
)paren
(brace
id|snd_gf1_uart_reset
c_func
(paren
id|gus
comma
l_int|0
)paren
suffix:semicolon
)brace
id|gus-&gt;gf1.interrupt_handler_midi_in
op_assign
id|snd_gf1_interrupt_midi_in
suffix:semicolon
id|gus-&gt;midi_substream_input
op_assign
id|substream
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;uart_enable
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|1000
op_logical_and
(paren
id|snd_gf1_uart_stat
c_func
(paren
id|gus
)paren
op_amp
l_int|0x01
)paren
suffix:semicolon
id|i
op_increment
)paren
id|snd_gf1_uart_get
c_func
(paren
id|gus
)paren
suffix:semicolon
multiline_comment|/* clean Rx */
r_if
c_cond
(paren
id|i
op_ge
l_int|1000
)paren
id|snd_printk
c_func
(paren
l_string|&quot;gus midi uart init read - cleanup error&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#if 0
id|snd_printk
c_func
(paren
l_string|&quot;read init - enable = %i, cmd = 0x%x, stat = 0x%x&bslash;n&quot;
comma
id|gus-&gt;uart_enable
comma
id|gus-&gt;gf1.uart_cmd
comma
id|snd_gf1_uart_stat
c_func
(paren
id|gus
)paren
)paren
suffix:semicolon
id|snd_printk
c_func
(paren
l_string|&quot;[0x%x] reg (ctrl/status) = 0x%x, reg (data) = 0x%x (page = 0x%x)&bslash;n&quot;
comma
id|gus-&gt;gf1.port
op_plus
l_int|0x100
comma
id|inb
c_func
(paren
id|gus-&gt;gf1.port
op_plus
l_int|0x100
)paren
comma
id|inb
c_func
(paren
id|gus-&gt;gf1.port
op_plus
l_int|0x101
)paren
comma
id|inb
c_func
(paren
id|gus-&gt;gf1.port
op_plus
l_int|0x102
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gf1_uart_output_close
r_static
r_int
id|snd_gf1_uart_output_close
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|snd_gus_card_t
op_star
id|gus
suffix:semicolon
id|gus
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.interrupt_handler_midi_in
op_ne
id|snd_gf1_interrupt_midi_in
)paren
id|snd_gf1_uart_reset
c_func
(paren
id|gus
comma
l_int|1
)paren
suffix:semicolon
id|snd_gf1_set_default_handlers
c_func
(paren
id|gus
comma
id|SNDRV_GF1_HANDLER_MIDI_OUT
)paren
suffix:semicolon
id|gus-&gt;midi_substream_output
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gf1_uart_input_close
r_static
r_int
id|snd_gf1_uart_input_close
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|snd_gus_card_t
op_star
id|gus
suffix:semicolon
id|gus
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.interrupt_handler_midi_out
op_ne
id|snd_gf1_interrupt_midi_out
)paren
id|snd_gf1_uart_reset
c_func
(paren
id|gus
comma
l_int|1
)paren
suffix:semicolon
id|snd_gf1_set_default_handlers
c_func
(paren
id|gus
comma
id|SNDRV_GF1_HANDLER_MIDI_IN
)paren
suffix:semicolon
id|gus-&gt;midi_substream_input
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gf1_uart_input_trigger
r_static
r_void
id|snd_gf1_uart_input_trigger
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_int
id|up
)paren
(brace
id|snd_gus_card_t
op_star
id|gus
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|gus
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|up
)paren
(brace
r_if
c_cond
(paren
(paren
id|gus-&gt;gf1.uart_cmd
op_amp
l_int|0x80
)paren
op_eq
l_int|0
)paren
id|snd_gf1_uart_cmd
c_func
(paren
id|gus
comma
id|gus-&gt;gf1.uart_cmd
op_or
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* enable Rx interrupts */
)brace
r_else
(brace
r_if
c_cond
(paren
id|gus-&gt;gf1.uart_cmd
op_amp
l_int|0x80
)paren
id|snd_gf1_uart_cmd
c_func
(paren
id|gus
comma
id|gus-&gt;gf1.uart_cmd
op_amp
op_complement
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* disable Rx interrupts */
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_uart_output_trigger
r_static
r_void
id|snd_gf1_uart_output_trigger
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_int
id|up
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|snd_gus_card_t
op_star
id|gus
suffix:semicolon
r_char
id|byte
suffix:semicolon
r_int
id|timeout
suffix:semicolon
id|gus
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|up
)paren
(brace
r_if
c_cond
(paren
(paren
id|gus-&gt;gf1.uart_cmd
op_amp
l_int|0x20
)paren
op_eq
l_int|0
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* wait for empty Rx - Tx is probably unlocked */
id|timeout
op_assign
l_int|10000
suffix:semicolon
r_while
c_loop
(paren
id|timeout
op_decrement
OG
l_int|0
op_logical_and
id|snd_gf1_uart_stat
c_func
(paren
id|gus
)paren
op_amp
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* Tx FIFO free? */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.uart_cmd
op_amp
l_int|0x20
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|snd_gf1_uart_stat
c_func
(paren
id|gus
)paren
op_amp
l_int|0x02
)paren
(brace
r_if
c_cond
(paren
id|snd_rawmidi_transmit
c_func
(paren
id|substream
comma
op_amp
id|byte
comma
l_int|1
)paren
op_ne
l_int|1
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|snd_gf1_uart_put
c_func
(paren
id|gus
comma
id|byte
)paren
suffix:semicolon
)brace
id|snd_gf1_uart_cmd
c_func
(paren
id|gus
comma
id|gus-&gt;gf1.uart_cmd
op_or
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* enable Tx interrupt */
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|gus-&gt;gf1.uart_cmd
op_amp
l_int|0x20
)paren
id|snd_gf1_uart_cmd
c_func
(paren
id|gus
comma
id|gus-&gt;gf1.uart_cmd
op_amp
op_complement
l_int|0x20
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;uart_cmd_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|snd_gf1_uart_output
r_static
id|snd_rawmidi_ops_t
id|snd_gf1_uart_output
op_assign
(brace
dot
id|open
op_assign
id|snd_gf1_uart_output_open
comma
dot
id|close
op_assign
id|snd_gf1_uart_output_close
comma
dot
id|trigger
op_assign
id|snd_gf1_uart_output_trigger
comma
)brace
suffix:semicolon
DECL|variable|snd_gf1_uart_input
r_static
id|snd_rawmidi_ops_t
id|snd_gf1_uart_input
op_assign
(brace
dot
id|open
op_assign
id|snd_gf1_uart_input_open
comma
dot
id|close
op_assign
id|snd_gf1_uart_input_close
comma
dot
id|trigger
op_assign
id|snd_gf1_uart_input_trigger
comma
)brace
suffix:semicolon
DECL|function|snd_gf1_rawmidi_new
r_int
id|snd_gf1_rawmidi_new
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
r_int
id|device
comma
id|snd_rawmidi_t
op_star
op_star
id|rrawmidi
)paren
(brace
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|rrawmidi
)paren
op_star
id|rrawmidi
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_rawmidi_new
c_func
(paren
id|gus-&gt;card
comma
l_string|&quot;GF1&quot;
comma
id|device
comma
l_int|1
comma
l_int|1
comma
op_amp
id|rmidi
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|strcpy
c_func
(paren
id|rmidi-&gt;name
comma
id|gus-&gt;interwave
ques
c_cond
l_string|&quot;AMD InterWave&quot;
suffix:colon
l_string|&quot;GF1&quot;
)paren
suffix:semicolon
id|snd_rawmidi_set_ops
c_func
(paren
id|rmidi
comma
id|SNDRV_RAWMIDI_STREAM_OUTPUT
comma
op_amp
id|snd_gf1_uart_output
)paren
suffix:semicolon
id|snd_rawmidi_set_ops
c_func
(paren
id|rmidi
comma
id|SNDRV_RAWMIDI_STREAM_INPUT
comma
op_amp
id|snd_gf1_uart_input
)paren
suffix:semicolon
id|rmidi-&gt;info_flags
op_or_assign
id|SNDRV_RAWMIDI_INFO_OUTPUT
op_or
id|SNDRV_RAWMIDI_INFO_INPUT
op_or
id|SNDRV_RAWMIDI_INFO_DUPLEX
suffix:semicolon
id|rmidi-&gt;private_data
op_assign
id|gus
suffix:semicolon
id|gus-&gt;midi_uart
op_assign
id|rmidi
suffix:semicolon
r_if
c_cond
(paren
id|rrawmidi
)paren
op_star
id|rrawmidi
op_assign
id|rmidi
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
