multiline_comment|/*&n; *   Generic MIDI synth driver for ALSA sequencer&n; *   Copyright (c) 1998 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *                         Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
multiline_comment|/* &n;Possible options for midisynth module:&n;&t;- automatic opening of midi ports on first received event or subscription&n;&t;  (close will be performed when client leaves)&n;*/
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/rawmidi.h&gt;
macro_line|#include &lt;sound/seq_kernel.h&gt;
macro_line|#include &lt;sound/seq_device.h&gt;
macro_line|#include &lt;sound/seq_midi_event.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Frank van de Pol &lt;fvdpol@home.nl&gt;, Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Advanced Linux Sound Architecture sequencer MIDI synth.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_CLASSES
c_func
(paren
l_string|&quot;{sound}&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;sound&quot;
)paren
suffix:semicolon
DECL|variable|output_buffer_size
r_int
id|output_buffer_size
op_assign
id|PAGE_SIZE
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|output_buffer_size
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|output_buffer_size
comma
l_string|&quot;Output buffer size in bytes.&quot;
)paren
suffix:semicolon
DECL|variable|input_buffer_size
r_int
id|input_buffer_size
op_assign
id|PAGE_SIZE
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|input_buffer_size
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|input_buffer_size
comma
l_string|&quot;Input buffer size in bytes.&quot;
)paren
suffix:semicolon
multiline_comment|/* data for this midi synth driver */
r_typedef
r_struct
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|device
r_int
id|device
suffix:semicolon
DECL|member|subdevice
r_int
id|subdevice
suffix:semicolon
DECL|member|input_rfile
id|snd_rawmidi_file_t
id|input_rfile
suffix:semicolon
DECL|member|output_rfile
id|snd_rawmidi_file_t
id|output_rfile
suffix:semicolon
DECL|member|seq_client
r_int
id|seq_client
suffix:semicolon
DECL|member|seq_port
r_int
id|seq_port
suffix:semicolon
DECL|member|parser
id|snd_midi_event_t
op_star
id|parser
suffix:semicolon
DECL|typedef|seq_midisynth_t
)brace
id|seq_midisynth_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|seq_client
r_int
id|seq_client
suffix:semicolon
DECL|member|num_ports
r_int
id|num_ports
suffix:semicolon
DECL|member|ports_per_device
r_int
id|ports_per_device
(braket
id|SNDRV_RAWMIDI_DEVICES
)braket
suffix:semicolon
DECL|member|ports
id|seq_midisynth_t
op_star
id|ports
(braket
id|SNDRV_RAWMIDI_DEVICES
)braket
suffix:semicolon
DECL|typedef|seq_midisynth_client_t
)brace
id|seq_midisynth_client_t
suffix:semicolon
DECL|variable|synths
r_static
id|seq_midisynth_client_t
op_star
id|synths
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|register_mutex
)paren
suffix:semicolon
multiline_comment|/* handle rawmidi input event (MIDI v1.0 stream) */
DECL|function|snd_midi_input_event
r_static
r_void
id|snd_midi_input_event
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
id|snd_rawmidi_runtime_t
op_star
id|runtime
suffix:semicolon
id|seq_midisynth_t
op_star
id|msynth
suffix:semicolon
id|snd_seq_event_t
id|ev
suffix:semicolon
r_char
id|buf
(braket
l_int|16
)braket
comma
op_star
id|pbuf
suffix:semicolon
r_int
id|res
comma
id|count
suffix:semicolon
r_if
c_cond
(paren
id|substream
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|msynth
op_assign
(paren
id|seq_midisynth_t
op_star
)paren
id|runtime-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|msynth
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ev
comma
l_int|0
comma
r_sizeof
(paren
id|ev
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|runtime-&gt;avail
OG
l_int|0
)paren
(brace
id|res
op_assign
id|snd_rawmidi_kernel_read
c_func
(paren
id|substream
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_le
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|msynth-&gt;parser
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|pbuf
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|res
OG
l_int|0
)paren
(brace
id|count
op_assign
id|snd_midi_event_encode
c_func
(paren
id|msynth-&gt;parser
comma
id|pbuf
comma
id|res
comma
op_amp
id|ev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_break
suffix:semicolon
id|pbuf
op_add_assign
id|count
suffix:semicolon
id|res
op_sub_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|ev.type
op_ne
id|SNDRV_SEQ_EVENT_NONE
)paren
(brace
id|ev.source.port
op_assign
id|msynth-&gt;seq_port
suffix:semicolon
id|ev.dest.client
op_assign
id|SNDRV_SEQ_ADDRESS_SUBSCRIBERS
suffix:semicolon
id|snd_seq_kernel_client_dispatch
c_func
(paren
id|msynth-&gt;seq_client
comma
op_amp
id|ev
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* clear event and reset header */
id|memset
c_func
(paren
op_amp
id|ev
comma
l_int|0
comma
r_sizeof
(paren
id|ev
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|dump_midi
r_static
r_int
id|dump_midi
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|snd_rawmidi_runtime_t
op_star
id|runtime
suffix:semicolon
r_int
id|tmp
suffix:semicolon
id|snd_assert
c_func
(paren
id|substream
op_ne
l_int|NULL
op_logical_or
id|buf
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|runtime-&gt;avail
)paren
OL
id|count
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;warning, output event was lost (count = %i, available = %i)&bslash;n&quot;
comma
id|count
comma
id|tmp
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|snd_rawmidi_kernel_write
c_func
(paren
id|substream
comma
id|buf
comma
id|count
)paren
OL
id|count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|event_process_midi
r_static
r_int
id|event_process_midi
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|direct
comma
r_void
op_star
id|private_data
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
id|seq_midisynth_t
op_star
id|msynth
op_assign
(paren
id|seq_midisynth_t
op_star
)paren
id|private_data
suffix:semicolon
r_int
r_char
id|msg
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* buffer for constructing midi messages */
id|snd_rawmidi_substream_t
op_star
id|substream
suffix:semicolon
r_int
id|res
suffix:semicolon
id|snd_assert
c_func
(paren
id|msynth
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|substream
op_assign
id|msynth-&gt;output_rfile.output
suffix:semicolon
r_if
c_cond
(paren
id|substream
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|ev-&gt;type
op_eq
id|SNDRV_SEQ_EVENT_SYSEX
)paren
(brace
multiline_comment|/* special case, to save space */
r_if
c_cond
(paren
(paren
id|ev-&gt;flags
op_amp
id|SNDRV_SEQ_EVENT_LENGTH_MASK
)paren
op_ne
id|SNDRV_SEQ_EVENT_LENGTH_VARIABLE
)paren
(brace
multiline_comment|/* invalid event */
id|snd_printd
c_func
(paren
l_string|&quot;seq_midi: invalid sysex event flags = 0x%x&bslash;n&quot;
comma
id|ev-&gt;flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|res
op_assign
id|snd_seq_dump_var_event
c_func
(paren
id|ev
comma
(paren
id|snd_seq_dump_func_t
)paren
id|dump_midi
comma
id|substream
)paren
suffix:semicolon
id|snd_midi_event_reset_decode
c_func
(paren
id|msynth-&gt;parser
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|msynth-&gt;parser
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|res
op_assign
id|snd_midi_event_decode
c_func
(paren
id|msynth-&gt;parser
comma
id|msg
comma
r_sizeof
(paren
id|msg
)paren
comma
id|ev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|dump_midi
c_func
(paren
id|substream
comma
id|msg
comma
id|res
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_midi_event_reset_decode
c_func
(paren
id|msynth-&gt;parser
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_midisynth_new
r_static
r_int
id|snd_seq_midisynth_new
c_func
(paren
id|seq_midisynth_t
op_star
id|msynth
comma
id|snd_card_t
op_star
id|card
comma
r_int
id|device
comma
r_int
id|subdevice
)paren
(brace
r_if
c_cond
(paren
id|snd_midi_event_new
c_func
(paren
id|MAX_MIDI_EVENT_BUF
comma
op_amp
id|msynth-&gt;parser
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|msynth-&gt;card
op_assign
id|card
suffix:semicolon
id|msynth-&gt;device
op_assign
id|device
suffix:semicolon
id|msynth-&gt;subdevice
op_assign
id|subdevice
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* open associated midi device for input */
DECL|function|midisynth_subscribe
r_static
r_int
id|midisynth_subscribe
c_func
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
(brace
r_int
id|err
suffix:semicolon
id|seq_midisynth_t
op_star
id|msynth
op_assign
(paren
id|seq_midisynth_t
op_star
)paren
id|private_data
suffix:semicolon
id|snd_rawmidi_runtime_t
op_star
id|runtime
suffix:semicolon
id|snd_rawmidi_params_t
id|params
suffix:semicolon
multiline_comment|/* open midi port */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_rawmidi_kernel_open
c_func
(paren
id|msynth-&gt;card-&gt;number
comma
id|msynth-&gt;device
comma
id|msynth-&gt;subdevice
comma
id|SNDRV_RAWMIDI_LFLG_INPUT
comma
op_amp
id|msynth-&gt;input_rfile
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;midi input open failed!!!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|runtime
op_assign
id|msynth-&gt;input_rfile.input-&gt;runtime
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|params
comma
l_int|0
comma
r_sizeof
(paren
id|params
)paren
)paren
suffix:semicolon
id|params.avail_min
op_assign
l_int|1
suffix:semicolon
id|params.buffer_size
op_assign
id|input_buffer_size
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_rawmidi_input_params
c_func
(paren
id|msynth-&gt;input_rfile.input
comma
op_amp
id|params
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_rawmidi_kernel_release
c_func
(paren
op_amp
id|msynth-&gt;input_rfile
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|runtime-&gt;event
op_assign
id|snd_midi_input_event
suffix:semicolon
id|runtime-&gt;private_data
op_assign
id|msynth
suffix:semicolon
id|snd_rawmidi_kernel_read
c_func
(paren
id|msynth-&gt;input_rfile.input
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* close associated midi device for input */
DECL|function|midisynth_unsubscribe
r_static
r_int
id|midisynth_unsubscribe
c_func
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
(brace
r_int
id|err
suffix:semicolon
id|seq_midisynth_t
op_star
id|msynth
op_assign
(paren
id|seq_midisynth_t
op_star
)paren
id|private_data
suffix:semicolon
id|snd_assert
c_func
(paren
id|msynth-&gt;input_rfile.input
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|err
op_assign
id|snd_rawmidi_kernel_release
c_func
(paren
op_amp
id|msynth-&gt;input_rfile
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* open associated midi device for output */
DECL|function|midisynth_use
r_static
r_int
id|midisynth_use
c_func
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
(brace
r_int
id|err
suffix:semicolon
id|seq_midisynth_t
op_star
id|msynth
op_assign
(paren
id|seq_midisynth_t
op_star
)paren
id|private_data
suffix:semicolon
id|snd_rawmidi_params_t
id|params
suffix:semicolon
multiline_comment|/* open midi port */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_rawmidi_kernel_open
c_func
(paren
id|msynth-&gt;card-&gt;number
comma
id|msynth-&gt;device
comma
id|msynth-&gt;subdevice
comma
id|SNDRV_RAWMIDI_LFLG_OUTPUT
comma
op_amp
id|msynth-&gt;output_rfile
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;midi output open failed!!!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|params
comma
l_int|0
comma
r_sizeof
(paren
id|params
)paren
)paren
suffix:semicolon
id|params.avail_min
op_assign
l_int|1
suffix:semicolon
id|params.buffer_size
op_assign
id|output_buffer_size
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_rawmidi_output_params
c_func
(paren
id|msynth-&gt;output_rfile.output
comma
op_amp
id|params
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_rawmidi_kernel_release
c_func
(paren
op_amp
id|msynth-&gt;output_rfile
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* close associated midi device for output */
DECL|function|midisynth_unuse
r_static
r_int
id|midisynth_unuse
c_func
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
(brace
id|seq_midisynth_t
op_star
id|msynth
op_assign
(paren
id|seq_midisynth_t
op_star
)paren
id|private_data
suffix:semicolon
r_int
r_char
id|buf
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* MIDI reset */
id|snd_assert
c_func
(paren
id|msynth-&gt;output_rfile.output
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* sending single MIDI reset message to shut the device up */
id|snd_rawmidi_kernel_write
c_func
(paren
id|msynth-&gt;output_rfile.output
comma
op_amp
id|buf
comma
l_int|1
)paren
suffix:semicolon
id|snd_rawmidi_drain_output
c_func
(paren
id|msynth-&gt;output_rfile.output
)paren
suffix:semicolon
r_return
id|snd_rawmidi_kernel_release
c_func
(paren
op_amp
id|msynth-&gt;output_rfile
)paren
suffix:semicolon
)brace
multiline_comment|/* delete given midi synth port */
DECL|function|snd_seq_midisynth_delete
r_static
r_void
id|snd_seq_midisynth_delete
c_func
(paren
id|seq_midisynth_t
op_star
id|msynth
)paren
(brace
id|snd_seq_port_info_t
id|port
suffix:semicolon
r_if
c_cond
(paren
id|msynth
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|msynth-&gt;seq_client
OG
l_int|0
)paren
(brace
multiline_comment|/* delete port */
id|memset
c_func
(paren
op_amp
id|port
comma
l_int|0
comma
r_sizeof
(paren
id|port
)paren
)paren
suffix:semicolon
id|port.addr.client
op_assign
id|msynth-&gt;seq_client
suffix:semicolon
id|port.addr.port
op_assign
id|msynth-&gt;seq_port
suffix:semicolon
id|snd_seq_kernel_client_ctl
c_func
(paren
id|port.addr.client
comma
id|SNDRV_SEQ_IOCTL_DELETE_PORT
comma
op_amp
id|port
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|msynth-&gt;parser
)paren
id|snd_midi_event_free
c_func
(paren
id|msynth-&gt;parser
)paren
suffix:semicolon
)brace
multiline_comment|/* register new midi synth port */
r_int
DECL|function|snd_seq_midisynth_register_port
id|snd_seq_midisynth_register_port
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
(brace
id|seq_midisynth_client_t
op_star
id|client
suffix:semicolon
id|seq_midisynth_t
op_star
id|msynth
comma
op_star
id|ms
suffix:semicolon
id|snd_seq_port_info_t
id|port
suffix:semicolon
id|snd_rawmidi_info_t
id|info
suffix:semicolon
r_int
id|newclient
op_assign
l_int|0
comma
id|p
comma
id|ports
suffix:semicolon
id|snd_seq_client_callback_t
id|callbacks
suffix:semicolon
id|snd_seq_port_callback_t
id|pcallbacks
suffix:semicolon
id|snd_seq_client_info_t
id|inf
suffix:semicolon
id|snd_card_t
op_star
id|card
op_assign
id|dev-&gt;card
suffix:semicolon
r_int
id|device
op_assign
id|dev-&gt;device
suffix:semicolon
r_int
r_int
id|input_count
op_assign
l_int|0
comma
id|output_count
op_assign
l_int|0
suffix:semicolon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
op_logical_and
id|device
op_ge
l_int|0
op_logical_and
id|device
OL
id|SNDRV_RAWMIDI_DEVICES
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|info.device
op_assign
id|device
suffix:semicolon
id|info.stream
op_assign
id|SNDRV_RAWMIDI_STREAM_OUTPUT
suffix:semicolon
id|info.subdevice
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|snd_rawmidi_info_select
c_func
(paren
id|card
comma
op_amp
id|info
)paren
op_ge
l_int|0
)paren
id|output_count
op_assign
id|info.subdevices_count
suffix:semicolon
id|info.stream
op_assign
id|SNDRV_RAWMIDI_STREAM_INPUT
suffix:semicolon
r_if
c_cond
(paren
id|snd_rawmidi_info_select
c_func
(paren
id|card
comma
op_amp
id|info
)paren
op_ge
l_int|0
)paren
(brace
id|input_count
op_assign
id|info.subdevices_count
suffix:semicolon
)brace
id|ports
op_assign
id|output_count
suffix:semicolon
r_if
c_cond
(paren
id|ports
OL
id|input_count
)paren
id|ports
op_assign
id|input_count
suffix:semicolon
r_if
c_cond
(paren
id|ports
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|ports
OG
(paren
l_int|256
op_div
id|SNDRV_RAWMIDI_DEVICES
)paren
)paren
id|ports
op_assign
l_int|256
op_div
id|SNDRV_RAWMIDI_DEVICES
suffix:semicolon
id|down
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
id|client
op_assign
id|synths
(braket
id|card-&gt;number
)braket
suffix:semicolon
r_if
c_cond
(paren
id|client
op_eq
l_int|NULL
)paren
(brace
id|newclient
op_assign
l_int|1
suffix:semicolon
id|client
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
id|seq_midisynth_client_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|client
op_eq
l_int|NULL
)paren
(brace
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|callbacks
comma
l_int|0
comma
r_sizeof
(paren
id|callbacks
)paren
)paren
suffix:semicolon
id|callbacks.private_data
op_assign
id|client
suffix:semicolon
id|callbacks.allow_input
op_assign
id|callbacks.allow_output
op_assign
l_int|1
suffix:semicolon
id|client-&gt;seq_client
op_assign
id|snd_seq_create_kernel_client
c_func
(paren
id|card
comma
l_int|0
comma
op_amp
id|callbacks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|client-&gt;seq_client
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* set our client name */
id|memset
c_func
(paren
op_amp
id|inf
comma
l_int|0
comma
r_sizeof
(paren
id|snd_seq_client_info_t
)paren
)paren
suffix:semicolon
id|inf.client
op_assign
id|client-&gt;seq_client
suffix:semicolon
id|inf.type
op_assign
id|KERNEL_CLIENT
suffix:semicolon
id|sprintf
c_func
(paren
id|inf.name
comma
l_string|&quot;External MIDI %i&quot;
comma
id|card-&gt;number
)paren
suffix:semicolon
id|snd_seq_kernel_client_ctl
c_func
(paren
id|client-&gt;seq_client
comma
id|SNDRV_SEQ_IOCTL_SET_CLIENT_INFO
comma
op_amp
id|inf
)paren
suffix:semicolon
)brace
id|msynth
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
id|seq_midisynth_t
)paren
op_star
id|ports
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msynth
op_eq
l_int|NULL
)paren
r_goto
id|__nomem
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
l_int|0
suffix:semicolon
id|p
OL
id|ports
suffix:semicolon
id|p
op_increment
)paren
(brace
id|ms
op_assign
op_amp
id|msynth
(braket
id|p
)braket
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_midisynth_new
c_func
(paren
id|ms
comma
id|card
comma
id|device
comma
id|p
)paren
OL
l_int|0
)paren
r_goto
id|__nomem
suffix:semicolon
multiline_comment|/* declare port */
id|memset
c_func
(paren
op_amp
id|port
comma
l_int|0
comma
r_sizeof
(paren
id|port
)paren
)paren
suffix:semicolon
id|port.addr.client
op_assign
id|client-&gt;seq_client
suffix:semicolon
id|port.addr.port
op_assign
id|device
op_star
(paren
l_int|256
op_div
id|SNDRV_RAWMIDI_DEVICES
)paren
op_plus
id|p
suffix:semicolon
id|port.flags
op_assign
id|SNDRV_SEQ_PORT_FLG_GIVEN_PORT
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
id|info.device
op_assign
id|device
suffix:semicolon
r_if
c_cond
(paren
id|p
OL
id|output_count
)paren
id|info.stream
op_assign
id|SNDRV_RAWMIDI_STREAM_OUTPUT
suffix:semicolon
r_else
id|info.stream
op_assign
id|SNDRV_RAWMIDI_STREAM_INPUT
suffix:semicolon
id|info.subdevice
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|snd_rawmidi_info_select
c_func
(paren
id|card
comma
op_amp
id|info
)paren
op_ge
l_int|0
)paren
id|strcpy
c_func
(paren
id|port.name
comma
id|info.subname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port.name
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|ports
OG
l_int|1
)paren
id|sprintf
c_func
(paren
id|port.name
comma
l_string|&quot;MIDI %d-%d-%d&quot;
comma
id|card-&gt;number
comma
id|device
comma
id|p
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|port.name
comma
l_string|&quot;MIDI %d-%d&quot;
comma
id|card-&gt;number
comma
id|device
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|info.flags
op_amp
id|SNDRV_RAWMIDI_INFO_OUTPUT
)paren
op_logical_and
id|p
OL
id|output_count
)paren
id|port.capability
op_or_assign
id|SNDRV_SEQ_PORT_CAP_WRITE
op_or
id|SNDRV_SEQ_PORT_CAP_SYNC_WRITE
op_or
id|SNDRV_SEQ_PORT_CAP_SUBS_WRITE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|info.flags
op_amp
id|SNDRV_RAWMIDI_INFO_INPUT
)paren
op_logical_and
id|p
OL
id|input_count
)paren
id|port.capability
op_or_assign
id|SNDRV_SEQ_PORT_CAP_READ
op_or
id|SNDRV_SEQ_PORT_CAP_SYNC_READ
op_or
id|SNDRV_SEQ_PORT_CAP_SUBS_READ
suffix:semicolon
r_if
c_cond
(paren
(paren
id|port.capability
op_amp
(paren
id|SNDRV_SEQ_PORT_CAP_WRITE
op_or
id|SNDRV_SEQ_PORT_CAP_READ
)paren
)paren
op_eq
(paren
id|SNDRV_SEQ_PORT_CAP_WRITE
op_or
id|SNDRV_SEQ_PORT_CAP_READ
)paren
op_logical_and
id|info.flags
op_amp
id|SNDRV_RAWMIDI_INFO_DUPLEX
)paren
id|port.capability
op_or_assign
id|SNDRV_SEQ_PORT_CAP_DUPLEX
suffix:semicolon
id|port.type
op_assign
id|SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC
suffix:semicolon
id|port.midi_channels
op_assign
l_int|16
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pcallbacks
comma
l_int|0
comma
r_sizeof
(paren
id|pcallbacks
)paren
)paren
suffix:semicolon
id|pcallbacks.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|pcallbacks.private_data
op_assign
id|ms
suffix:semicolon
id|pcallbacks.subscribe
op_assign
id|midisynth_subscribe
suffix:semicolon
id|pcallbacks.unsubscribe
op_assign
id|midisynth_unsubscribe
suffix:semicolon
id|pcallbacks.use
op_assign
id|midisynth_use
suffix:semicolon
id|pcallbacks.unuse
op_assign
id|midisynth_unuse
suffix:semicolon
id|pcallbacks.event_input
op_assign
id|event_process_midi
suffix:semicolon
id|port.kernel
op_assign
op_amp
id|pcallbacks
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_kernel_client_ctl
c_func
(paren
id|client-&gt;seq_client
comma
id|SNDRV_SEQ_IOCTL_CREATE_PORT
comma
op_amp
id|port
)paren
OL
l_int|0
)paren
r_goto
id|__nomem
suffix:semicolon
id|ms-&gt;seq_client
op_assign
id|client-&gt;seq_client
suffix:semicolon
id|ms-&gt;seq_port
op_assign
id|port.addr.port
suffix:semicolon
)brace
id|client-&gt;ports_per_device
(braket
id|device
)braket
op_assign
id|ports
suffix:semicolon
id|client-&gt;ports
(braket
id|device
)braket
op_assign
id|msynth
suffix:semicolon
id|client-&gt;num_ports
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|newclient
)paren
id|synths
(braket
id|card-&gt;number
)braket
op_assign
id|client
suffix:semicolon
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* success */
id|__nomem
suffix:colon
r_if
c_cond
(paren
id|msynth
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|p
op_assign
l_int|0
suffix:semicolon
id|p
OL
id|ports
suffix:semicolon
id|p
op_increment
)paren
id|snd_seq_midisynth_delete
c_func
(paren
op_amp
id|msynth
(braket
id|p
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|msynth
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|newclient
)paren
(brace
id|snd_seq_delete_kernel_client
c_func
(paren
id|client-&gt;seq_client
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* release midi synth port */
r_int
DECL|function|snd_seq_midisynth_unregister_port
id|snd_seq_midisynth_unregister_port
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
(brace
id|seq_midisynth_client_t
op_star
id|client
suffix:semicolon
id|seq_midisynth_t
op_star
id|msynth
suffix:semicolon
id|snd_card_t
op_star
id|card
op_assign
id|dev-&gt;card
suffix:semicolon
r_int
id|device
op_assign
id|dev-&gt;device
comma
id|p
comma
id|ports
suffix:semicolon
id|down
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
id|client
op_assign
id|synths
(braket
id|card-&gt;number
)braket
suffix:semicolon
r_if
c_cond
(paren
id|client
op_eq
l_int|NULL
op_logical_or
id|client-&gt;ports
(braket
id|device
)braket
op_eq
l_int|NULL
)paren
(brace
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|snd_seq_event_port_detach
c_func
(paren
id|client-&gt;seq_client
comma
id|client-&gt;ports
(braket
id|device
)braket
op_member_access_from_pointer
id|seq_port
)paren
suffix:semicolon
id|ports
op_assign
id|client-&gt;ports_per_device
(braket
id|device
)braket
suffix:semicolon
id|client-&gt;ports_per_device
(braket
id|device
)braket
op_assign
l_int|0
suffix:semicolon
id|msynth
op_assign
id|client-&gt;ports
(braket
id|device
)braket
suffix:semicolon
id|client-&gt;ports
(braket
id|device
)braket
op_assign
l_int|NULL
suffix:semicolon
id|snd_runtime_check
c_func
(paren
id|msynth
op_ne
l_int|NULL
op_logical_or
id|ports
op_le
l_int|0
comma
r_goto
id|__skip
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
l_int|0
suffix:semicolon
id|p
OL
id|ports
suffix:semicolon
id|p
op_increment
)paren
id|snd_seq_midisynth_delete
c_func
(paren
op_amp
id|msynth
(braket
id|p
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|msynth
)paren
suffix:semicolon
id|__skip
suffix:colon
id|client-&gt;num_ports
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|client-&gt;num_ports
op_le
l_int|0
)paren
(brace
id|snd_seq_delete_kernel_client
c_func
(paren
id|client-&gt;seq_client
)paren
suffix:semicolon
id|synths
(braket
id|card-&gt;number
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_seq_midi_init
r_static
r_int
id|__init
id|alsa_seq_midi_init
c_func
(paren
r_void
)paren
(brace
r_static
id|snd_seq_dev_ops_t
id|ops
op_assign
(brace
id|snd_seq_midisynth_register_port
comma
id|snd_seq_midisynth_unregister_port
comma
)brace
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|synths
comma
l_int|0
comma
r_sizeof
(paren
id|synths
)paren
)paren
suffix:semicolon
id|snd_seq_device_register_driver
c_func
(paren
id|SNDRV_SEQ_DEV_ID_MIDISYNTH
comma
op_amp
id|ops
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_seq_midi_exit
r_static
r_void
id|__exit
id|alsa_seq_midi_exit
c_func
(paren
r_void
)paren
(brace
id|snd_seq_device_unregister_driver
c_func
(paren
id|SNDRV_SEQ_DEV_ID_MIDISYNTH
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_seq_midi_init
)paren
id|module_exit
c_func
(paren
id|alsa_seq_midi_exit
)paren
eof
