multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Routines for control of EMU10K1 MPU-401 in UART mode&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emu10k1.h&gt;
DECL|macro|EMU10K1_MIDI_MODE_INPUT
mdefine_line|#define EMU10K1_MIDI_MODE_INPUT&t;&t;(1&lt;&lt;0)
DECL|macro|EMU10K1_MIDI_MODE_OUTPUT
mdefine_line|#define EMU10K1_MIDI_MODE_OUTPUT&t;(1&lt;&lt;1)
DECL|function|mpu401_read
r_static
r_inline
r_int
r_char
id|mpu401_read
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_midi_t
op_star
id|mpu
comma
r_int
id|idx
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
r_return
(paren
r_int
r_char
)paren
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu
comma
id|mpu-&gt;port
op_plus
id|idx
comma
l_int|0
)paren
suffix:semicolon
r_else
r_return
id|inb
c_func
(paren
id|emu-&gt;port
op_plus
id|mpu-&gt;port
op_plus
id|idx
)paren
suffix:semicolon
)brace
DECL|function|mpu401_write
r_static
r_inline
r_void
id|mpu401_write
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_midi_t
op_star
id|mpu
comma
r_int
id|data
comma
r_int
id|idx
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu
comma
id|mpu-&gt;port
op_plus
id|idx
comma
l_int|0
comma
id|data
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
id|data
comma
id|emu-&gt;port
op_plus
id|mpu-&gt;port
op_plus
id|idx
)paren
suffix:semicolon
)brace
DECL|macro|mpu401_write_data
mdefine_line|#define mpu401_write_data(emu, mpu, data)&t;mpu401_write(emu, mpu, data, 0)
DECL|macro|mpu401_write_cmd
mdefine_line|#define mpu401_write_cmd(emu, mpu, data)&t;mpu401_write(emu, mpu, data, 1)
DECL|macro|mpu401_read_data
mdefine_line|#define mpu401_read_data(emu, mpu)&t;&t;mpu401_read(emu, mpu, 0)
DECL|macro|mpu401_read_stat
mdefine_line|#define mpu401_read_stat(emu, mpu)&t;&t;mpu401_read(emu, mpu, 1)
DECL|macro|mpu401_input_avail
mdefine_line|#define mpu401_input_avail(emu,mpu)&t;(!(mpu401_read_stat(emu,mpu) &amp; 0x80))
DECL|macro|mpu401_output_ready
mdefine_line|#define mpu401_output_ready(emu,mpu)&t;(!(mpu401_read_stat(emu,mpu) &amp; 0x40))
DECL|macro|MPU401_RESET
mdefine_line|#define MPU401_RESET&t;&t;0xff
DECL|macro|MPU401_ENTER_UART
mdefine_line|#define MPU401_ENTER_UART&t;0x3f
DECL|macro|MPU401_ACK
mdefine_line|#define MPU401_ACK&t;&t;0xfe
DECL|function|mpu401_clear_rx
r_static
r_void
id|mpu401_clear_rx
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_midi_t
op_star
id|mpu
)paren
(brace
r_int
id|timeout
op_assign
l_int|100000
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|timeout
OG
l_int|0
op_logical_and
id|mpu401_input_avail
c_func
(paren
id|emu
comma
id|mpu
)paren
suffix:semicolon
id|timeout
op_decrement
)paren
id|mpu401_read_data
c_func
(paren
id|emu
comma
id|mpu
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG
r_if
c_cond
(paren
id|timeout
op_le
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cmd: clear rx timeout (status = 0x%x)&bslash;n&quot;
comma
id|mpu401_read_stat
c_func
(paren
id|emu
comma
id|mpu
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n;&n; */
DECL|function|do_emu10k1_midi_interrupt
r_static
r_void
id|do_emu10k1_midi_interrupt
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_midi_t
op_star
id|midi
comma
r_int
r_int
id|status
)paren
(brace
r_int
r_char
id|byte
suffix:semicolon
r_if
c_cond
(paren
id|midi-&gt;rmidi
op_eq
l_int|NULL
)paren
(brace
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|midi-&gt;tx_enable
op_or
id|midi-&gt;rx_enable
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|midi-&gt;input_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|midi-&gt;ipr_rx
)paren
op_logical_and
id|mpu401_input_avail
c_func
(paren
id|emu
comma
id|midi
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|midi-&gt;midi_mode
op_amp
id|EMU10K1_MIDI_MODE_INPUT
)paren
)paren
(brace
id|mpu401_clear_rx
c_func
(paren
id|emu
comma
id|midi
)paren
suffix:semicolon
)brace
r_else
(brace
id|byte
op_assign
id|mpu401_read_data
c_func
(paren
id|emu
comma
id|midi
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|midi-&gt;input_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|midi-&gt;substream_input
)paren
id|snd_rawmidi_receive
c_func
(paren
id|midi-&gt;substream_input
comma
op_amp
id|byte
comma
l_int|1
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|midi-&gt;input_lock
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|midi-&gt;input_lock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|midi-&gt;output_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|midi-&gt;ipr_tx
)paren
op_logical_and
id|mpu401_output_ready
c_func
(paren
id|emu
comma
id|midi
)paren
)paren
(brace
r_if
c_cond
(paren
id|midi-&gt;substream_output
op_logical_and
id|snd_rawmidi_transmit
c_func
(paren
id|midi-&gt;substream_output
comma
op_amp
id|byte
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
id|mpu401_write_data
c_func
(paren
id|emu
comma
id|midi
comma
id|byte
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|midi-&gt;tx_enable
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|midi-&gt;output_lock
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_midi_interrupt
r_static
r_void
id|snd_emu10k1_midi_interrupt
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|status
)paren
(brace
id|do_emu10k1_midi_interrupt
c_func
(paren
id|emu
comma
op_amp
id|emu-&gt;midi
comma
id|status
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_midi_interrupt2
r_static
r_void
id|snd_emu10k1_midi_interrupt2
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|status
)paren
(brace
id|do_emu10k1_midi_interrupt
c_func
(paren
id|emu
comma
op_amp
id|emu-&gt;midi2
comma
id|status
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_midi_cmd
r_static
r_void
id|snd_emu10k1_midi_cmd
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_midi_t
op_star
id|midi
comma
r_int
r_char
id|cmd
comma
r_int
id|ack
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|timeout
comma
id|ok
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi-&gt;input_lock
comma
id|flags
)paren
suffix:semicolon
id|mpu401_write_data
c_func
(paren
id|emu
comma
id|midi
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* mpu401_clear_rx(emu, midi); */
id|mpu401_write_cmd
c_func
(paren
id|emu
comma
id|midi
comma
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ack
)paren
(brace
id|ok
op_assign
l_int|0
suffix:semicolon
id|timeout
op_assign
l_int|10000
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|ok
op_logical_and
id|timeout
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|mpu401_input_avail
c_func
(paren
id|emu
comma
id|midi
)paren
)paren
(brace
r_if
c_cond
(paren
id|mpu401_read_data
c_func
(paren
id|emu
comma
id|midi
)paren
op_eq
id|MPU401_ACK
)paren
id|ok
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|ok
op_logical_and
id|mpu401_read_data
c_func
(paren
id|emu
comma
id|midi
)paren
op_eq
id|MPU401_ACK
)paren
id|ok
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|ok
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi-&gt;input_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ok
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;midi_cmd: 0x%x failed at 0x%lx (status = 0x%x, data = 0x%x)!!!&bslash;n&quot;
comma
id|cmd
comma
id|emu-&gt;port
comma
id|mpu401_read_stat
c_func
(paren
id|emu
comma
id|midi
)paren
comma
id|mpu401_read_data
c_func
(paren
id|emu
comma
id|midi
)paren
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_midi_input_open
r_static
r_int
id|snd_emu10k1_midi_input_open
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
id|emu10k1_t
op_star
id|emu
suffix:semicolon
id|emu10k1_midi_t
op_star
id|midi
op_assign
(paren
id|emu10k1_midi_t
op_star
)paren
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|emu
op_assign
id|midi-&gt;emu
suffix:semicolon
id|snd_assert
c_func
(paren
id|emu
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
id|midi-&gt;midi_mode
op_or_assign
id|EMU10K1_MIDI_MODE_INPUT
suffix:semicolon
id|midi-&gt;substream_input
op_assign
id|substream
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|midi-&gt;midi_mode
op_amp
id|EMU10K1_MIDI_MODE_OUTPUT
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_emu10k1_midi_cmd
c_func
(paren
id|emu
comma
id|midi
comma
id|MPU401_RESET
comma
l_int|1
)paren
suffix:semicolon
id|snd_emu10k1_midi_cmd
c_func
(paren
id|emu
comma
id|midi
comma
id|MPU401_ENTER_UART
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_midi_output_open
r_static
r_int
id|snd_emu10k1_midi_output_open
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
id|emu10k1_t
op_star
id|emu
suffix:semicolon
id|emu10k1_midi_t
op_star
id|midi
op_assign
(paren
id|emu10k1_midi_t
op_star
)paren
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|emu
op_assign
id|midi-&gt;emu
suffix:semicolon
id|snd_assert
c_func
(paren
id|emu
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
id|midi-&gt;midi_mode
op_or_assign
id|EMU10K1_MIDI_MODE_OUTPUT
suffix:semicolon
id|midi-&gt;substream_output
op_assign
id|substream
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|midi-&gt;midi_mode
op_amp
id|EMU10K1_MIDI_MODE_INPUT
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_emu10k1_midi_cmd
c_func
(paren
id|emu
comma
id|midi
comma
id|MPU401_RESET
comma
l_int|1
)paren
suffix:semicolon
id|snd_emu10k1_midi_cmd
c_func
(paren
id|emu
comma
id|midi
comma
id|MPU401_ENTER_UART
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_midi_input_close
r_static
r_int
id|snd_emu10k1_midi_input_close
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
id|emu10k1_t
op_star
id|emu
suffix:semicolon
id|emu10k1_midi_t
op_star
id|midi
op_assign
(paren
id|emu10k1_midi_t
op_star
)paren
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|emu
op_assign
id|midi-&gt;emu
suffix:semicolon
id|snd_assert
c_func
(paren
id|emu
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|midi-&gt;rx_enable
)paren
suffix:semicolon
id|midi-&gt;midi_mode
op_and_assign
op_complement
id|EMU10K1_MIDI_MODE_INPUT
suffix:semicolon
id|midi-&gt;substream_input
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|midi-&gt;midi_mode
op_amp
id|EMU10K1_MIDI_MODE_OUTPUT
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_emu10k1_midi_cmd
c_func
(paren
id|emu
comma
id|midi
comma
id|MPU401_RESET
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_midi_output_close
r_static
r_int
id|snd_emu10k1_midi_output_close
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
id|emu10k1_t
op_star
id|emu
suffix:semicolon
id|emu10k1_midi_t
op_star
id|midi
op_assign
(paren
id|emu10k1_midi_t
op_star
)paren
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|emu
op_assign
id|midi-&gt;emu
suffix:semicolon
id|snd_assert
c_func
(paren
id|emu
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|midi-&gt;tx_enable
)paren
suffix:semicolon
id|midi-&gt;midi_mode
op_and_assign
op_complement
id|EMU10K1_MIDI_MODE_OUTPUT
suffix:semicolon
id|midi-&gt;substream_output
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|midi-&gt;midi_mode
op_amp
id|EMU10K1_MIDI_MODE_INPUT
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_emu10k1_midi_cmd
c_func
(paren
id|emu
comma
id|midi
comma
id|MPU401_RESET
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi-&gt;open_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_midi_input_trigger
r_static
r_void
id|snd_emu10k1_midi_input_trigger
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
id|emu10k1_t
op_star
id|emu
suffix:semicolon
id|emu10k1_midi_t
op_star
id|midi
op_assign
(paren
id|emu10k1_midi_t
op_star
)paren
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
id|emu
op_assign
id|midi-&gt;emu
suffix:semicolon
id|snd_assert
c_func
(paren
id|emu
comma
r_return
)paren
suffix:semicolon
r_if
c_cond
(paren
id|up
)paren
id|snd_emu10k1_intr_enable
c_func
(paren
id|emu
comma
id|midi-&gt;rx_enable
)paren
suffix:semicolon
r_else
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|midi-&gt;rx_enable
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_midi_output_trigger
r_static
r_void
id|snd_emu10k1_midi_output_trigger
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
id|emu10k1_t
op_star
id|emu
suffix:semicolon
id|emu10k1_midi_t
op_star
id|midi
op_assign
(paren
id|emu10k1_midi_t
op_star
)paren
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|emu
op_assign
id|midi-&gt;emu
suffix:semicolon
id|snd_assert
c_func
(paren
id|emu
comma
r_return
)paren
suffix:semicolon
r_if
c_cond
(paren
id|up
)paren
(brace
r_int
id|max
op_assign
l_int|4
suffix:semicolon
r_int
r_char
id|byte
suffix:semicolon
multiline_comment|/* try to send some amount of bytes here before interrupts */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|midi-&gt;output_lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|max
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|mpu401_output_ready
c_func
(paren
id|emu
comma
id|midi
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|midi-&gt;midi_mode
op_amp
id|EMU10K1_MIDI_MODE_OUTPUT
)paren
op_logical_or
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
multiline_comment|/* no more data */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi-&gt;output_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mpu401_write_data
c_func
(paren
id|emu
comma
id|midi
comma
id|byte
)paren
suffix:semicolon
id|max
op_decrement
suffix:semicolon
)brace
r_else
(brace
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|midi-&gt;output_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_emu10k1_intr_enable
c_func
(paren
id|emu
comma
id|midi-&gt;tx_enable
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|midi-&gt;tx_enable
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&n; */
DECL|variable|snd_emu10k1_midi_output
r_static
id|snd_rawmidi_ops_t
id|snd_emu10k1_midi_output
op_assign
(brace
id|open
suffix:colon
id|snd_emu10k1_midi_output_open
comma
id|close
suffix:colon
id|snd_emu10k1_midi_output_close
comma
id|trigger
suffix:colon
id|snd_emu10k1_midi_output_trigger
comma
)brace
suffix:semicolon
DECL|variable|snd_emu10k1_midi_input
r_static
id|snd_rawmidi_ops_t
id|snd_emu10k1_midi_input
op_assign
(brace
id|open
suffix:colon
id|snd_emu10k1_midi_input_open
comma
id|close
suffix:colon
id|snd_emu10k1_midi_input_close
comma
id|trigger
suffix:colon
id|snd_emu10k1_midi_input_trigger
comma
)brace
suffix:semicolon
DECL|function|snd_emu10k1_midi_free
r_static
r_void
id|snd_emu10k1_midi_free
c_func
(paren
id|snd_rawmidi_t
op_star
id|rmidi
)paren
(brace
id|emu10k1_midi_t
op_star
id|midi
op_assign
(paren
id|emu10k1_midi_t
op_star
)paren
id|rmidi-&gt;private_data
suffix:semicolon
id|midi-&gt;interrupt
op_assign
l_int|NULL
suffix:semicolon
id|midi-&gt;rmidi
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|emu10k1_midi_init
r_static
r_int
id|__devinit
id|emu10k1_midi_init
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_midi_t
op_star
id|midi
comma
r_int
id|device
comma
r_char
op_star
id|name
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
(paren
id|err
op_assign
id|snd_rawmidi_new
c_func
(paren
id|emu-&gt;card
comma
id|name
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
id|midi-&gt;emu
op_assign
id|emu
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|midi-&gt;open_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|midi-&gt;input_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|midi-&gt;output_lock
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|rmidi-&gt;name
comma
id|name
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
id|snd_emu10k1_midi_output
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
id|snd_emu10k1_midi_input
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
id|midi
suffix:semicolon
id|rmidi-&gt;private_free
op_assign
id|snd_emu10k1_midi_free
suffix:semicolon
id|midi-&gt;rmidi
op_assign
id|rmidi
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_midi
r_int
id|__devinit
id|snd_emu10k1_midi
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
(brace
id|emu10k1_midi_t
op_star
id|midi
op_assign
op_amp
id|emu-&gt;midi
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|emu10k1_midi_init
c_func
(paren
id|emu
comma
id|midi
comma
l_int|0
comma
l_string|&quot;EMU10K1 MPU-401 (UART)&quot;
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|midi-&gt;tx_enable
op_assign
id|INTE_MIDITXENABLE
suffix:semicolon
id|midi-&gt;rx_enable
op_assign
id|INTE_MIDIRXENABLE
suffix:semicolon
id|midi-&gt;port
op_assign
id|MUDATA
suffix:semicolon
id|midi-&gt;ipr_tx
op_assign
id|IPR_MIDITRANSBUFEMPTY
suffix:semicolon
id|midi-&gt;ipr_rx
op_assign
id|IPR_MIDIRECVBUFEMPTY
suffix:semicolon
id|midi-&gt;interrupt
op_assign
id|snd_emu10k1_midi_interrupt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_audigy_midi
r_int
id|__devinit
id|snd_emu10k1_audigy_midi
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
(brace
id|emu10k1_midi_t
op_star
id|midi
suffix:semicolon
r_int
id|err
suffix:semicolon
id|midi
op_assign
op_amp
id|emu-&gt;midi
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|emu10k1_midi_init
c_func
(paren
id|emu
comma
id|midi
comma
l_int|0
comma
l_string|&quot;Audigy MPU-401 (UART)&quot;
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|midi-&gt;tx_enable
op_assign
id|INTE_MIDITXENABLE
suffix:semicolon
id|midi-&gt;rx_enable
op_assign
id|INTE_MIDIRXENABLE
suffix:semicolon
id|midi-&gt;port
op_assign
id|A_MUDATA1
suffix:semicolon
id|midi-&gt;ipr_tx
op_assign
id|IPR_MIDITRANSBUFEMPTY
suffix:semicolon
id|midi-&gt;ipr_rx
op_assign
id|IPR_MIDIRECVBUFEMPTY
suffix:semicolon
id|midi-&gt;interrupt
op_assign
id|snd_emu10k1_midi_interrupt
suffix:semicolon
id|midi
op_assign
op_amp
id|emu-&gt;midi2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|emu10k1_midi_init
c_func
(paren
id|emu
comma
id|midi
comma
l_int|1
comma
l_string|&quot;Audigy MPU-401 #2&quot;
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|midi-&gt;tx_enable
op_assign
id|INTE_A_MIDITXENABLE2
suffix:semicolon
id|midi-&gt;rx_enable
op_assign
id|INTE_A_MIDIRXENABLE2
suffix:semicolon
id|midi-&gt;port
op_assign
id|A_MUDATA2
suffix:semicolon
id|midi-&gt;ipr_tx
op_assign
id|IPR_A_MIDITRANSBUFEMPTY2
suffix:semicolon
id|midi-&gt;ipr_rx
op_assign
id|IPR_A_MIDIRECVBUFEMPTY2
suffix:semicolon
id|midi-&gt;interrupt
op_assign
id|snd_emu10k1_midi_interrupt2
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
