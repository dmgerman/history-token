multiline_comment|/*&n; * OPL4 sequencer functions&n; *&n; * Copyright (c) 2003 by Clemens Ladisch &lt;clemens@ladisch.de&gt;&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed and/or modified under the&n; * terms of the GNU General Public License as published by the Free Software&n; * Foundation; either version 2 of the License, or (at your option) any later&n; * version.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#include &quot;opl4_local.h&quot;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Clemens Ladisch &lt;clemens@ladisch.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;OPL4 wavetable synth driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual BSD/GPL&quot;
)paren
suffix:semicolon
id|MODULE_CLASSES
c_func
(paren
l_string|&quot;{sound}&quot;
)paren
suffix:semicolon
DECL|variable|volume_boost
r_int
id|volume_boost
op_assign
l_int|8
suffix:semicolon
id|module_param
c_func
(paren
id|volume_boost
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|volume_boost
comma
l_string|&quot;Additional volume for OPL4 wavetable sounds.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|volume_boost
comma
l_string|&quot;default:8&quot;
)paren
suffix:semicolon
DECL|function|snd_opl4_seq_use_inc
r_static
r_int
id|snd_opl4_seq_use_inc
c_func
(paren
id|opl4_t
op_star
id|opl4
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|opl4-&gt;card-&gt;module
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl4_seq_use_dec
r_static
r_void
id|snd_opl4_seq_use_dec
c_func
(paren
id|opl4_t
op_star
id|opl4
)paren
(brace
id|module_put
c_func
(paren
id|opl4-&gt;card-&gt;module
)paren
suffix:semicolon
)brace
DECL|function|snd_opl4_seq_use
r_static
r_int
id|snd_opl4_seq_use
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
id|opl4_t
op_star
id|opl4
op_assign
id|snd_magic_cast
c_func
(paren
id|opl4_t
comma
id|private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
id|down
c_func
(paren
op_amp
id|opl4-&gt;access_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opl4-&gt;used
)paren
(brace
id|up
c_func
(paren
op_amp
id|opl4-&gt;access_mutex
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|opl4-&gt;used
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;sender.client
op_ne
id|SNDRV_SEQ_CLIENT_SYSTEM
)paren
(brace
id|err
op_assign
id|snd_opl4_seq_use_inc
c_func
(paren
id|opl4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|up
c_func
(paren
op_amp
id|opl4-&gt;access_mutex
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|opl4-&gt;access_mutex
)paren
suffix:semicolon
id|snd_opl4_synth_reset
c_func
(paren
id|opl4
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl4_seq_unuse
r_static
r_int
id|snd_opl4_seq_unuse
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
id|opl4_t
op_star
id|opl4
op_assign
id|snd_magic_cast
c_func
(paren
id|opl4_t
comma
id|private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_opl4_synth_shutdown
c_func
(paren
id|opl4
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|opl4-&gt;access_mutex
)paren
suffix:semicolon
id|opl4-&gt;used
op_decrement
suffix:semicolon
id|up
c_func
(paren
op_amp
id|opl4-&gt;access_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;sender.client
op_ne
id|SNDRV_SEQ_CLIENT_SYSTEM
)paren
id|snd_opl4_seq_use_dec
c_func
(paren
id|opl4
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|opl4_ops
r_static
id|snd_midi_op_t
id|opl4_ops
op_assign
(brace
dot
id|note_on
op_assign
id|snd_opl4_note_on
comma
dot
id|note_off
op_assign
id|snd_opl4_note_off
comma
dot
id|note_terminate
op_assign
id|snd_opl4_terminate_note
comma
dot
id|control
op_assign
id|snd_opl4_control
comma
dot
id|sysex
op_assign
id|snd_opl4_sysex
comma
)brace
suffix:semicolon
DECL|function|snd_opl4_seq_event_input
r_static
r_int
id|snd_opl4_seq_event_input
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
id|opl4_t
op_star
id|opl4
op_assign
id|snd_magic_cast
c_func
(paren
id|opl4_t
comma
id|private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_midi_process_event
c_func
(paren
op_amp
id|opl4_ops
comma
id|ev
comma
id|opl4-&gt;chset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl4_seq_free_port
r_static
r_void
id|snd_opl4_seq_free_port
c_func
(paren
r_void
op_star
id|private_data
)paren
(brace
id|opl4_t
op_star
id|opl4
op_assign
id|snd_magic_cast
c_func
(paren
id|opl4_t
comma
id|private_data
comma
r_return
)paren
suffix:semicolon
id|snd_midi_channel_free_set
c_func
(paren
id|opl4-&gt;chset
)paren
suffix:semicolon
)brace
DECL|function|snd_opl4_seq_new_device
r_static
r_int
id|snd_opl4_seq_new_device
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
(brace
id|opl4_t
op_star
id|opl4
suffix:semicolon
r_int
id|client
suffix:semicolon
id|snd_seq_client_callback_t
id|callbacks
suffix:semicolon
id|snd_seq_client_info_t
id|cinfo
suffix:semicolon
id|snd_seq_port_callback_t
id|pcallbacks
suffix:semicolon
id|opl4
op_assign
op_star
(paren
id|opl4_t
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
op_logical_neg
id|opl4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|snd_yrw801_detect
c_func
(paren
id|opl4
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|opl4-&gt;chset
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
op_logical_neg
id|opl4-&gt;chset
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|opl4-&gt;chset-&gt;private_data
op_assign
id|opl4
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
id|opl4
suffix:semicolon
id|callbacks.allow_output
op_assign
id|callbacks.allow_input
op_assign
l_int|1
suffix:semicolon
id|client
op_assign
id|snd_seq_create_kernel_client
c_func
(paren
id|opl4-&gt;card
comma
id|opl4-&gt;seq_dev_num
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
(brace
id|snd_midi_channel_free_set
c_func
(paren
id|opl4-&gt;chset
)paren
suffix:semicolon
r_return
id|client
suffix:semicolon
)brace
id|opl4-&gt;seq_client
op_assign
id|client
suffix:semicolon
id|opl4-&gt;chset-&gt;client
op_assign
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
id|strcpy
c_func
(paren
id|cinfo.name
comma
l_string|&quot;OPL4 Wavetable&quot;
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
multiline_comment|/* create new port */
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
id|pcallbacks.use
op_assign
id|snd_opl4_seq_use
suffix:semicolon
id|pcallbacks.unuse
op_assign
id|snd_opl4_seq_unuse
suffix:semicolon
id|pcallbacks.event_input
op_assign
id|snd_opl4_seq_event_input
suffix:semicolon
id|pcallbacks.private_free
op_assign
id|snd_opl4_seq_free_port
suffix:semicolon
id|pcallbacks.private_data
op_assign
id|opl4
suffix:semicolon
id|opl4-&gt;chset-&gt;port
op_assign
id|snd_seq_event_port_attach
c_func
(paren
id|client
comma
op_amp
id|pcallbacks
comma
id|SNDRV_SEQ_PORT_CAP_WRITE
op_or
id|SNDRV_SEQ_PORT_CAP_SUBS_WRITE
comma
id|SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC
op_or
id|SNDRV_SEQ_PORT_TYPE_MIDI_GM
comma
l_int|16
comma
l_int|24
comma
l_string|&quot;OPL4 Wavetable Port&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opl4-&gt;chset-&gt;port
OL
l_int|0
)paren
(brace
r_int
id|err
op_assign
id|opl4-&gt;chset-&gt;port
suffix:semicolon
id|snd_midi_channel_free_set
c_func
(paren
id|opl4-&gt;chset
)paren
suffix:semicolon
id|snd_seq_delete_kernel_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|opl4-&gt;seq_client
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl4_seq_delete_device
r_static
r_int
id|snd_opl4_seq_delete_device
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
(brace
id|opl4_t
op_star
id|opl4
suffix:semicolon
id|opl4
op_assign
op_star
(paren
id|opl4_t
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
op_logical_neg
id|opl4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|opl4-&gt;seq_client
op_ge
l_int|0
)paren
(brace
id|snd_seq_delete_kernel_client
c_func
(paren
id|opl4-&gt;seq_client
)paren
suffix:semicolon
id|opl4-&gt;seq_client
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_opl4_synth_init
r_static
r_int
id|__init
id|alsa_opl4_synth_init
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
id|snd_opl4_seq_new_device
comma
id|snd_opl4_seq_delete_device
)brace
suffix:semicolon
r_return
id|snd_seq_device_register_driver
c_func
(paren
id|SNDRV_SEQ_DEV_ID_OPL4
comma
op_amp
id|ops
comma
r_sizeof
(paren
id|opl4_t
op_star
)paren
)paren
suffix:semicolon
)brace
DECL|function|alsa_opl4_synth_exit
r_static
r_void
id|__exit
id|alsa_opl4_synth_exit
c_func
(paren
r_void
)paren
(brace
id|snd_seq_device_unregister_driver
c_func
(paren
id|SNDRV_SEQ_DEV_ID_OPL4
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_opl4_synth_init
)paren
id|module_exit
c_func
(paren
id|alsa_opl4_synth_exit
)paren
eof
