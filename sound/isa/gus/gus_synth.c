multiline_comment|/*&n; *  Routines for Gravis UltraSound soundcards - Synthesizer&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/gus.h&gt;
macro_line|#include &lt;sound/seq_device.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Routines for Gravis UltraSound soundcards - Synthesizer&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; *&n; */
DECL|function|snd_gus_synth_free_voices
r_static
r_void
id|snd_gus_synth_free_voices
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
r_int
id|client
comma
r_int
id|port
)paren
(brace
r_int
id|idx
suffix:semicolon
id|snd_gus_voice_t
op_star
id|voice
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|32
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|voice
op_assign
op_amp
id|gus-&gt;gf1.voices
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|voice-&gt;use
op_logical_and
id|voice-&gt;client
op_eq
id|client
op_logical_and
id|voice-&gt;port
op_eq
id|port
)paren
id|snd_gf1_free_voice
c_func
(paren
id|gus
comma
id|voice
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_gus_synth_use
r_static
r_int
id|snd_gus_synth_use
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
id|snd_gus_port_t
op_star
id|port
op_assign
(paren
id|snd_gus_port_t
op_star
)paren
id|private_data
suffix:semicolon
id|snd_gus_card_t
op_star
id|gus
op_assign
id|port-&gt;gus
suffix:semicolon
id|snd_gus_voice_t
op_star
id|voice
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;voices
OG
l_int|32
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|gus-&gt;register_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|snd_gus_use_inc
c_func
(paren
id|gus
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|gus-&gt;register_mutex
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|info-&gt;voices
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|voice
op_assign
id|snd_gf1_alloc_voice
c_func
(paren
id|gus
comma
id|SNDRV_GF1_VOICE_TYPE_SYNTH
comma
id|info-&gt;sender.client
comma
id|info-&gt;sender.port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|voice
op_eq
l_int|NULL
)paren
(brace
id|snd_gus_synth_free_voices
c_func
(paren
id|gus
comma
id|info-&gt;sender.client
comma
id|info-&gt;sender.port
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|gus-&gt;register_mutex
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|voice-&gt;index
op_assign
id|idx
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|gus-&gt;register_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gus_synth_unuse
r_static
r_int
id|snd_gus_synth_unuse
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
id|snd_gus_port_t
op_star
id|port
op_assign
(paren
id|snd_gus_port_t
op_star
)paren
id|private_data
suffix:semicolon
id|snd_gus_card_t
op_star
id|gus
op_assign
id|port-&gt;gus
suffix:semicolon
id|down
c_func
(paren
op_amp
id|gus-&gt;register_mutex
)paren
suffix:semicolon
id|snd_gus_synth_free_voices
c_func
(paren
id|gus
comma
id|info-&gt;sender.client
comma
id|info-&gt;sender.port
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|gus-&gt;register_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&n; */
DECL|function|snd_gus_synth_free_private_instruments
r_static
r_void
id|snd_gus_synth_free_private_instruments
c_func
(paren
id|snd_gus_port_t
op_star
id|p
comma
r_int
id|client
)paren
(brace
id|snd_seq_instr_header_t
id|ifree
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ifree
comma
l_int|0
comma
r_sizeof
(paren
id|ifree
)paren
)paren
suffix:semicolon
id|ifree.cmd
op_assign
id|SNDRV_SEQ_INSTR_FREE_CMD_PRIVATE
suffix:semicolon
id|snd_seq_instr_list_free_cond
c_func
(paren
id|p-&gt;gus-&gt;gf1.ilist
comma
op_amp
id|ifree
comma
id|client
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|snd_gus_synth_event_input
r_int
id|snd_gus_synth_event_input
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
id|snd_gus_port_t
op_star
id|p
op_assign
(paren
id|snd_gus_port_t
op_star
)paren
id|private_data
suffix:semicolon
id|snd_assert
c_func
(paren
id|p
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ev-&gt;type
op_ge
id|SNDRV_SEQ_EVENT_SAMPLE
op_logical_and
id|ev-&gt;type
op_le
id|SNDRV_SEQ_EVENT_SAMPLE_PRIVATE1
)paren
(brace
id|snd_gus_sample_event
c_func
(paren
id|ev
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ev-&gt;source.client
op_eq
id|SNDRV_SEQ_CLIENT_SYSTEM
op_logical_and
id|ev-&gt;source.port
op_eq
id|SNDRV_SEQ_PORT_SYSTEM_ANNOUNCE
)paren
(brace
r_if
c_cond
(paren
id|ev-&gt;type
op_eq
id|SNDRV_SEQ_EVENT_CLIENT_EXIT
)paren
(brace
id|snd_gus_synth_free_private_instruments
c_func
(paren
id|p
comma
id|ev-&gt;data.addr.client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|direct
)paren
(brace
r_if
c_cond
(paren
id|ev-&gt;type
op_ge
id|SNDRV_SEQ_EVENT_INSTR_BEGIN
)paren
(brace
id|snd_seq_instr_event
c_func
(paren
op_amp
id|p-&gt;gus-&gt;gf1.iwffff_ops.kops
comma
id|p-&gt;gus-&gt;gf1.ilist
comma
id|ev
comma
id|p-&gt;gus-&gt;gf1.seq_client
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gus_synth_instr_notify
r_static
r_void
id|snd_gus_synth_instr_notify
c_func
(paren
r_void
op_star
id|private_data
comma
id|snd_seq_kinstr_t
op_star
id|instr
comma
r_int
id|what
)paren
(brace
r_int
id|idx
suffix:semicolon
id|snd_gus_card_t
op_star
id|gus
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_gus_card_t
comma
id|private_data
comma
r_return
)paren
suffix:semicolon
id|snd_gus_voice_t
op_star
id|pvoice
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;event_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|32
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|pvoice
op_assign
op_amp
id|gus-&gt;gf1.voices
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pvoice-&gt;use
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
op_amp
id|pvoice-&gt;instr
comma
op_amp
id|instr-&gt;instr
comma
r_sizeof
(paren
id|pvoice-&gt;instr
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|pvoice-&gt;sample_ops
op_logical_and
id|pvoice-&gt;sample_ops-&gt;sample_stop
)paren
(brace
id|pvoice-&gt;sample_ops
op_member_access_from_pointer
id|sample_stop
c_func
(paren
id|gus
comma
id|pvoice
comma
id|SAMPLE_STOP_IMMEDIATELY
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_gf1_stop_voice
c_func
(paren
id|gus
comma
id|pvoice-&gt;number
)paren
suffix:semicolon
id|pvoice-&gt;flags
op_and_assign
op_complement
id|SNDRV_GF1_VFLG_RUNNING
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;event_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&n; */
DECL|function|snd_gus_synth_free_port
r_static
r_void
id|snd_gus_synth_free_port
c_func
(paren
r_void
op_star
id|private_data
)paren
(brace
id|snd_gus_port_t
op_star
id|p
op_assign
(paren
id|snd_gus_port_t
op_star
)paren
id|private_data
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|snd_midi_channel_free_set
c_func
(paren
id|p-&gt;chset
)paren
suffix:semicolon
)brace
DECL|function|snd_gus_synth_create_port
r_static
r_int
id|snd_gus_synth_create_port
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
r_int
id|idx
)paren
(brace
id|snd_gus_port_t
op_star
id|p
suffix:semicolon
id|snd_seq_port_callback_t
id|callbacks
suffix:semicolon
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|result
suffix:semicolon
id|p
op_assign
op_amp
id|gus-&gt;gf1.seq_ports
(braket
id|idx
)braket
suffix:semicolon
id|p-&gt;chset
op_assign
id|snd_midi_channel_alloc_set
c_func
(paren
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;chset
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|p-&gt;chset-&gt;private_data
op_assign
id|p
suffix:semicolon
id|p-&gt;gus
op_assign
id|gus
suffix:semicolon
id|p-&gt;client
op_assign
id|gus-&gt;gf1.seq_client
suffix:semicolon
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
id|callbacks.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|callbacks.use
op_assign
id|snd_gus_synth_use
suffix:semicolon
id|callbacks.unuse
op_assign
id|snd_gus_synth_unuse
suffix:semicolon
id|callbacks.event_input
op_assign
id|snd_gus_synth_event_input
suffix:semicolon
id|callbacks.private_free
op_assign
id|snd_gus_synth_free_port
suffix:semicolon
id|callbacks.private_data
op_assign
id|p
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%s port %i&quot;
comma
id|gus-&gt;interwave
ques
c_cond
l_string|&quot;AMD InterWave&quot;
suffix:colon
l_string|&quot;GF1&quot;
comma
id|idx
)paren
suffix:semicolon
id|p-&gt;chset-&gt;port
op_assign
id|snd_seq_event_port_attach
c_func
(paren
id|gus-&gt;gf1.seq_client
comma
op_amp
id|callbacks
comma
id|SNDRV_SEQ_PORT_CAP_WRITE
op_or
id|SNDRV_SEQ_PORT_CAP_SUBS_WRITE
comma
id|SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC
op_or
id|SNDRV_SEQ_PORT_TYPE_MIDI_GM
op_or
id|SNDRV_SEQ_PORT_TYPE_MIDI_GS
op_or
id|SNDRV_SEQ_PORT_TYPE_DIRECT_SAMPLE
op_or
id|SNDRV_SEQ_PORT_TYPE_SYNTH
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;chset-&gt;port
OL
l_int|0
)paren
(brace
id|result
op_assign
id|p-&gt;chset-&gt;port
suffix:semicolon
id|snd_gus_synth_free_port
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|p-&gt;port
op_assign
id|p-&gt;chset-&gt;port
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&n; */
DECL|function|snd_gus_synth_new_device
r_static
r_int
id|snd_gus_synth_new_device
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
(brace
id|snd_gus_card_t
op_star
id|gus
suffix:semicolon
r_int
id|client
comma
id|i
suffix:semicolon
id|snd_seq_client_callback_t
id|callbacks
suffix:semicolon
id|snd_seq_client_info_t
id|cinfo
suffix:semicolon
id|snd_seq_port_subscribe_t
id|sub
suffix:semicolon
id|snd_iwffff_ops_t
op_star
id|iwops
suffix:semicolon
id|snd_gf1_ops_t
op_star
id|gf1ops
suffix:semicolon
id|snd_simple_ops_t
op_star
id|simpleops
suffix:semicolon
id|gus
op_assign
op_star
(paren
id|snd_gus_card_t
op_star
op_star
)paren
id|SNDRV_SEQ_DEVICE_ARGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|gus-&gt;register_mutex
)paren
suffix:semicolon
id|gus-&gt;gf1.seq_client
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* allocate new client */
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
id|gus
suffix:semicolon
id|callbacks.allow_output
op_assign
id|callbacks.allow_input
op_assign
l_int|1
suffix:semicolon
id|client
op_assign
id|gus-&gt;gf1.seq_client
op_assign
id|snd_seq_create_kernel_client
c_func
(paren
id|gus-&gt;card
comma
l_int|1
comma
op_amp
id|callbacks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|client
OL
l_int|0
)paren
r_return
id|client
suffix:semicolon
multiline_comment|/* change name of client */
id|memset
c_func
(paren
op_amp
id|cinfo
comma
l_int|0
comma
r_sizeof
(paren
id|cinfo
)paren
)paren
suffix:semicolon
id|cinfo.client
op_assign
id|client
suffix:semicolon
id|cinfo.type
op_assign
id|KERNEL_CLIENT
suffix:semicolon
id|sprintf
c_func
(paren
id|cinfo.name
comma
id|gus-&gt;interwave
ques
c_cond
l_string|&quot;AMD InterWave&quot;
suffix:colon
l_string|&quot;GF1&quot;
)paren
suffix:semicolon
id|snd_seq_kernel_client_ctl
c_func
(paren
id|client
comma
id|SNDRV_SEQ_IOCTL_SET_CLIENT_INFO
comma
op_amp
id|cinfo
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|snd_gus_synth_create_port
c_func
(paren
id|gus
comma
id|i
)paren
suffix:semicolon
id|gus-&gt;gf1.ilist
op_assign
id|snd_seq_instr_list_new
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.ilist
op_eq
l_int|NULL
)paren
(brace
id|snd_seq_delete_kernel_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|gus-&gt;gf1.seq_client
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|gus-&gt;gf1.ilist-&gt;flags
op_assign
id|SNDRV_SEQ_INSTR_FLG_DIRECT
suffix:semicolon
id|simpleops
op_assign
op_amp
id|gus-&gt;gf1.simple_ops
suffix:semicolon
id|snd_seq_simple_init
c_func
(paren
id|simpleops
comma
id|gus
comma
l_int|NULL
)paren
suffix:semicolon
id|simpleops-&gt;put_sample
op_assign
id|snd_gus_simple_put_sample
suffix:semicolon
id|simpleops-&gt;get_sample
op_assign
id|snd_gus_simple_get_sample
suffix:semicolon
id|simpleops-&gt;remove_sample
op_assign
id|snd_gus_simple_remove_sample
suffix:semicolon
id|simpleops-&gt;notify
op_assign
id|snd_gus_synth_instr_notify
suffix:semicolon
id|gf1ops
op_assign
op_amp
id|gus-&gt;gf1.gf1_ops
suffix:semicolon
id|snd_seq_gf1_init
c_func
(paren
id|gf1ops
comma
id|gus
comma
op_amp
id|simpleops-&gt;kops
)paren
suffix:semicolon
id|gf1ops-&gt;put_sample
op_assign
id|snd_gus_gf1_put_sample
suffix:semicolon
id|gf1ops-&gt;get_sample
op_assign
id|snd_gus_gf1_get_sample
suffix:semicolon
id|gf1ops-&gt;remove_sample
op_assign
id|snd_gus_gf1_remove_sample
suffix:semicolon
id|gf1ops-&gt;notify
op_assign
id|snd_gus_synth_instr_notify
suffix:semicolon
id|iwops
op_assign
op_amp
id|gus-&gt;gf1.iwffff_ops
suffix:semicolon
id|snd_seq_iwffff_init
c_func
(paren
id|iwops
comma
id|gus
comma
op_amp
id|gf1ops-&gt;kops
)paren
suffix:semicolon
id|iwops-&gt;put_sample
op_assign
id|snd_gus_iwffff_put_sample
suffix:semicolon
id|iwops-&gt;get_sample
op_assign
id|snd_gus_iwffff_get_sample
suffix:semicolon
id|iwops-&gt;remove_sample
op_assign
id|snd_gus_iwffff_remove_sample
suffix:semicolon
id|iwops-&gt;notify
op_assign
id|snd_gus_synth_instr_notify
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|sub
comma
l_int|0
comma
r_sizeof
(paren
id|sub
)paren
)paren
suffix:semicolon
id|sub.sender.client
op_assign
id|SNDRV_SEQ_CLIENT_SYSTEM
suffix:semicolon
id|sub.sender.port
op_assign
id|SNDRV_SEQ_PORT_SYSTEM_ANNOUNCE
suffix:semicolon
id|sub.dest.client
op_assign
id|client
suffix:semicolon
id|sub.dest.port
op_assign
l_int|0
suffix:semicolon
id|snd_seq_kernel_client_ctl
c_func
(paren
id|client
comma
id|SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT
comma
op_amp
id|sub
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gus_synth_delete_device
r_static
r_int
id|snd_gus_synth_delete_device
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
(brace
id|snd_gus_card_t
op_star
id|gus
suffix:semicolon
id|gus
op_assign
op_star
(paren
id|snd_gus_card_t
op_star
op_star
)paren
id|SNDRV_SEQ_DEVICE_ARGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.seq_client
op_ge
l_int|0
)paren
(brace
id|snd_seq_delete_kernel_client
c_func
(paren
id|gus-&gt;gf1.seq_client
)paren
suffix:semicolon
id|gus-&gt;gf1.seq_client
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gus-&gt;gf1.ilist
)paren
id|snd_seq_instr_list_free
c_func
(paren
op_amp
id|gus-&gt;gf1.ilist
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_gus_synth_init
r_static
r_int
id|__init
id|alsa_gus_synth_init
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
id|snd_gus_synth_new_device
comma
id|snd_gus_synth_delete_device
)brace
suffix:semicolon
r_return
id|snd_seq_device_register_driver
c_func
(paren
id|SNDRV_SEQ_DEV_ID_GUS
comma
op_amp
id|ops
comma
r_sizeof
(paren
id|snd_gus_card_t
op_star
)paren
)paren
suffix:semicolon
)brace
DECL|function|alsa_gus_synth_exit
r_static
r_void
id|__exit
id|alsa_gus_synth_exit
c_func
(paren
r_void
)paren
(brace
id|snd_seq_device_unregister_driver
c_func
(paren
id|SNDRV_SEQ_DEV_ID_GUS
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_gus_synth_init
)paren
id|module_exit
c_func
(paren
id|alsa_gus_synth_exit
)paren
eof
