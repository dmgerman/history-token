multiline_comment|/*&n; *  Interface for OSS sequencer emulation&n; *&n; *  Copyright (C) 1999 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; * Changes&n; * 19990227   Steve Ratcliffe   Made separate file and merged in latest&n; * &t;&t;&t;&t;midi emulation.&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#ifdef CONFIG_SND_SEQUENCER_OSS
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;emux_voice.h&quot;
macro_line|#include &lt;sound/asoundef.h&gt;
r_static
r_int
id|snd_emux_open_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
comma
r_void
op_star
id|closure
)paren
suffix:semicolon
r_static
r_int
id|snd_emux_close_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
)paren
suffix:semicolon
r_static
r_int
id|snd_emux_ioctl_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|ioarg
)paren
suffix:semicolon
r_static
r_int
id|snd_emux_load_patch_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
comma
r_int
id|format
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|offs
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_int
id|snd_emux_reset_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
)paren
suffix:semicolon
r_static
r_int
id|snd_emux_event_oss_input
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
r_private
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
r_static
r_void
id|reset_port_mode
c_func
(paren
id|snd_emux_port_t
op_star
id|port
comma
r_int
id|midi_mode
)paren
suffix:semicolon
r_static
r_void
id|emuspec_control
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
id|snd_emux_port_t
op_star
id|port
comma
r_int
id|cmd
comma
r_int
r_char
op_star
id|event
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
r_static
r_void
id|gusspec_control
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
id|snd_emux_port_t
op_star
id|port
comma
r_int
id|cmd
comma
r_int
r_char
op_star
id|event
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
r_static
r_void
id|fake_event
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
id|snd_emux_port_t
op_star
id|port
comma
r_int
id|ch
comma
r_int
id|param
comma
r_int
id|val
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
multiline_comment|/* operators */
DECL|variable|oss_callback
r_static
id|snd_seq_oss_callback_t
id|oss_callback
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|open
suffix:colon
id|snd_emux_open_seq_oss
comma
id|close
suffix:colon
id|snd_emux_close_seq_oss
comma
id|ioctl
suffix:colon
id|snd_emux_ioctl_seq_oss
comma
id|load_patch
suffix:colon
id|snd_emux_load_patch_seq_oss
comma
id|reset
suffix:colon
id|snd_emux_reset_seq_oss
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * register OSS synth&n; */
r_void
DECL|function|snd_emux_init_seq_oss
id|snd_emux_init_seq_oss
c_func
(paren
id|snd_emux_t
op_star
id|emu
)paren
(brace
id|snd_seq_oss_reg_t
op_star
id|arg
suffix:semicolon
id|snd_seq_device_t
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_device_new
c_func
(paren
id|emu-&gt;card
comma
l_int|0
comma
id|SNDRV_SEQ_DEV_ID_OSS
comma
r_sizeof
(paren
id|snd_seq_oss_reg_t
)paren
comma
op_amp
id|dev
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|emu-&gt;oss_synth
op_assign
id|dev
suffix:semicolon
id|strcpy
c_func
(paren
id|dev-&gt;name
comma
id|emu-&gt;name
)paren
suffix:semicolon
id|arg
op_assign
id|SNDRV_SEQ_DEVICE_ARGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|arg-&gt;type
op_assign
id|SYNTH_TYPE_SAMPLE
suffix:semicolon
id|arg-&gt;subtype
op_assign
id|SAMPLE_TYPE_AWE32
suffix:semicolon
id|arg-&gt;nvoices
op_assign
id|emu-&gt;max_voices
suffix:semicolon
id|arg-&gt;oper
op_assign
id|oss_callback
suffix:semicolon
id|arg-&gt;private_data
op_assign
id|emu
suffix:semicolon
multiline_comment|/* register to OSS synth table */
id|snd_device_register
c_func
(paren
id|emu-&gt;card
comma
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * unregister&n; */
r_void
DECL|function|snd_emux_detach_seq_oss
id|snd_emux_detach_seq_oss
c_func
(paren
id|snd_emux_t
op_star
id|emu
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;oss_synth
)paren
(brace
id|snd_device_free
c_func
(paren
id|emu-&gt;card
comma
id|emu-&gt;oss_synth
)paren
suffix:semicolon
id|emu-&gt;oss_synth
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/* use port number as a unique soundfont client number */
DECL|macro|SF_CLIENT_NO
mdefine_line|#define SF_CLIENT_NO(p)&t;((p) + 0x1000)
multiline_comment|/*&n; * open port for OSS sequencer&n; */
r_static
r_int
DECL|function|snd_emux_open_seq_oss
id|snd_emux_open_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
comma
r_void
op_star
id|closure
)paren
(brace
id|snd_emux_t
op_star
id|emu
suffix:semicolon
id|snd_emux_port_t
op_star
id|p
suffix:semicolon
id|snd_seq_port_callback_t
id|callback
suffix:semicolon
r_char
id|tmpname
(braket
l_int|64
)braket
suffix:semicolon
id|emu
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_emux_t
comma
id|closure
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|arg
op_ne
l_int|NULL
op_logical_and
id|emu
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|emu-&gt;register_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|snd_emux_inc_count
c_func
(paren
id|emu
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|emu-&gt;register_mutex
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|callback
comma
l_int|0
comma
r_sizeof
(paren
id|callback
)paren
)paren
suffix:semicolon
id|callback.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|callback.event_input
op_assign
id|snd_emux_event_oss_input
suffix:semicolon
id|sprintf
c_func
(paren
id|tmpname
comma
l_string|&quot;%s OSS Port&quot;
comma
id|emu-&gt;name
)paren
suffix:semicolon
id|p
op_assign
id|snd_emux_create_port
c_func
(paren
id|emu
comma
id|tmpname
comma
l_int|32
comma
l_int|1
comma
op_amp
id|callback
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;can&squot;t create port&bslash;n&quot;
)paren
suffix:semicolon
id|snd_emux_dec_count
c_func
(paren
id|emu
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|emu-&gt;register_mutex
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* fill the argument data */
id|arg-&gt;private_data
op_assign
id|p
suffix:semicolon
id|arg-&gt;addr.client
op_assign
id|p-&gt;chset.client
suffix:semicolon
id|arg-&gt;addr.port
op_assign
id|p-&gt;chset.port
suffix:semicolon
id|p-&gt;oss_arg
op_assign
id|arg
suffix:semicolon
id|reset_port_mode
c_func
(paren
id|p
comma
id|arg-&gt;seq_mode
)paren
suffix:semicolon
id|snd_emux_reset_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|emu-&gt;register_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|DEFAULT_DRUM_FLAGS
mdefine_line|#define DEFAULT_DRUM_FLAGS&t;((1&lt;&lt;9) | (1&lt;&lt;25))
multiline_comment|/*&n; * reset port mode&n; */
r_static
r_void
DECL|function|reset_port_mode
id|reset_port_mode
c_func
(paren
id|snd_emux_port_t
op_star
id|port
comma
r_int
id|midi_mode
)paren
(brace
r_if
c_cond
(paren
id|midi_mode
)paren
(brace
id|port-&gt;port_mode
op_assign
id|SNDRV_EMUX_PORT_MODE_OSS_MIDI
suffix:semicolon
id|port-&gt;drum_flags
op_assign
id|DEFAULT_DRUM_FLAGS
suffix:semicolon
id|port-&gt;volume_atten
op_assign
l_int|0
suffix:semicolon
id|port-&gt;oss_arg-&gt;event_passing
op_assign
id|SNDRV_SEQ_OSS_PROCESS_KEYPRESS
suffix:semicolon
)brace
r_else
(brace
id|port-&gt;port_mode
op_assign
id|SNDRV_EMUX_PORT_MODE_OSS_SYNTH
suffix:semicolon
id|port-&gt;drum_flags
op_assign
l_int|0
suffix:semicolon
id|port-&gt;volume_atten
op_assign
l_int|32
suffix:semicolon
id|port-&gt;oss_arg-&gt;event_passing
op_assign
id|SNDRV_SEQ_OSS_PROCESS_EVENTS
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * close port&n; */
r_static
r_int
DECL|function|snd_emux_close_seq_oss
id|snd_emux_close_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
)paren
(brace
id|snd_emux_t
op_star
id|emu
suffix:semicolon
id|snd_emux_port_t
op_star
id|p
suffix:semicolon
id|snd_assert
c_func
(paren
id|arg
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|p
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_emux_port_t
comma
id|arg-&gt;private_data
comma
r_return
op_minus
id|EINVAL
)paren
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
id|ENXIO
)paren
suffix:semicolon
id|emu
op_assign
id|p-&gt;emu
suffix:semicolon
id|snd_assert
c_func
(paren
id|emu
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|emu-&gt;register_mutex
)paren
suffix:semicolon
id|snd_emux_sounds_off_all
c_func
(paren
id|p
)paren
suffix:semicolon
id|snd_soundfont_close_check
c_func
(paren
id|emu-&gt;sflist
comma
id|SF_CLIENT_NO
c_func
(paren
id|p-&gt;chset.port
)paren
)paren
suffix:semicolon
id|snd_seq_event_port_detach
c_func
(paren
id|p-&gt;chset.client
comma
id|p-&gt;chset.port
)paren
suffix:semicolon
id|snd_emux_dec_count
c_func
(paren
id|emu
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|emu-&gt;register_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * load patch&n; */
r_static
r_int
DECL|function|snd_emux_load_patch_seq_oss
id|snd_emux_load_patch_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
comma
r_int
id|format
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|offs
comma
r_int
id|count
)paren
(brace
id|snd_emux_t
op_star
id|emu
suffix:semicolon
id|snd_emux_port_t
op_star
id|p
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|snd_assert
c_func
(paren
id|arg
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|p
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_emux_port_t
comma
id|arg-&gt;private_data
comma
r_return
op_minus
id|EINVAL
)paren
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
id|ENXIO
)paren
suffix:semicolon
id|emu
op_assign
id|p-&gt;emu
suffix:semicolon
id|snd_assert
c_func
(paren
id|emu
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|format
op_eq
id|GUS_PATCH
)paren
id|rc
op_assign
id|snd_soundfont_load_guspatch
c_func
(paren
id|emu-&gt;sflist
comma
id|buf
comma
id|count
comma
id|SF_CLIENT_NO
c_func
(paren
id|p-&gt;chset.port
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|format
op_eq
id|SNDRV_OSS_SOUNDFONT_PATCH
)paren
(brace
id|soundfont_patch_info_t
id|patch
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
r_sizeof
(paren
id|patch
)paren
)paren
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|patch
comma
id|buf
comma
r_sizeof
(paren
id|patch
)paren
)paren
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|patch.type
op_ge
id|SNDRV_SFNT_LOAD_INFO
op_logical_and
id|patch.type
op_le
id|SNDRV_SFNT_PROBE_DATA
)paren
id|rc
op_assign
id|snd_soundfont_load
c_func
(paren
id|emu-&gt;sflist
comma
id|buf
comma
id|count
comma
id|SF_CLIENT_NO
c_func
(paren
id|p-&gt;chset.port
)paren
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|emu-&gt;ops.load_fx
)paren
id|rc
op_assign
id|emu-&gt;ops
dot
id|load_fx
c_func
(paren
id|emu
comma
id|patch.type
comma
id|patch.optarg
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_else
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_else
id|rc
op_assign
l_int|0
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * ioctl&n; */
r_static
r_int
DECL|function|snd_emux_ioctl_seq_oss
id|snd_emux_ioctl_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|ioarg
)paren
(brace
id|snd_emux_port_t
op_star
id|p
suffix:semicolon
id|snd_emux_t
op_star
id|emu
suffix:semicolon
id|snd_assert
c_func
(paren
id|arg
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|p
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_emux_port_t
comma
id|arg-&gt;private_data
comma
r_return
op_minus
id|EINVAL
)paren
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
id|ENXIO
)paren
suffix:semicolon
id|emu
op_assign
id|p-&gt;emu
suffix:semicolon
id|snd_assert
c_func
(paren
id|emu
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDCTL_SEQ_RESETSAMPLES
suffix:colon
id|snd_soundfont_remove_samples
c_func
(paren
id|emu-&gt;sflist
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SNDCTL_SYNTH_MEMAVL
suffix:colon
r_if
c_cond
(paren
id|emu-&gt;memhdr
)paren
r_return
id|snd_util_mem_avail
c_func
(paren
id|emu-&gt;memhdr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * reset device&n; */
r_static
r_int
DECL|function|snd_emux_reset_seq_oss
id|snd_emux_reset_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
)paren
(brace
id|snd_emux_port_t
op_star
id|p
suffix:semicolon
id|snd_assert
c_func
(paren
id|arg
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|p
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_emux_port_t
comma
id|arg-&gt;private_data
comma
r_return
op_minus
id|EINVAL
)paren
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
id|ENXIO
)paren
suffix:semicolon
id|snd_emux_reset_port
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * receive raw events: only SEQ_PRIVATE is accepted.&n; */
r_static
r_int
DECL|function|snd_emux_event_oss_input
id|snd_emux_event_oss_input
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
id|snd_emux_t
op_star
id|emu
suffix:semicolon
id|snd_emux_port_t
op_star
id|p
suffix:semicolon
r_int
r_char
id|cmd
comma
op_star
id|data
suffix:semicolon
id|p
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_emux_port_t
comma
id|private_data
comma
r_return
op_minus
id|EINVAL
)paren
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
id|emu
op_assign
id|p-&gt;emu
suffix:semicolon
id|snd_assert
c_func
(paren
id|emu
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
op_ne
id|SNDRV_SEQ_EVENT_OSS
)paren
r_return
id|snd_emux_event_input
c_func
(paren
id|ev
comma
id|direct
comma
id|private_data
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
id|data
op_assign
id|ev-&gt;data.raw8.d
suffix:semicolon
multiline_comment|/* only SEQ_PRIVATE is accepted */
r_if
c_cond
(paren
id|data
(braket
l_int|0
)braket
op_ne
l_int|0xfe
)paren
r_return
l_int|0
suffix:semicolon
id|cmd
op_assign
id|data
(braket
l_int|2
)braket
op_amp
id|_EMUX_OSS_MODE_VALUE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
l_int|2
)braket
op_amp
id|_EMUX_OSS_MODE_FLAG
)paren
id|emuspec_control
c_func
(paren
id|emu
comma
id|p
comma
id|cmd
comma
id|data
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_else
id|gusspec_control
c_func
(paren
id|emu
comma
id|p
comma
id|cmd
comma
id|data
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
multiline_comment|/*&n; * OSS/AWE driver specific h/w controls&n; */
r_static
r_void
DECL|function|emuspec_control
id|emuspec_control
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
id|snd_emux_port_t
op_star
id|port
comma
r_int
id|cmd
comma
r_int
r_char
op_star
id|event
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_int
id|voice
suffix:semicolon
r_int
r_int
id|p1
suffix:semicolon
r_int
id|p2
suffix:semicolon
r_int
id|i
suffix:semicolon
id|snd_midi_channel_t
op_star
id|chan
suffix:semicolon
id|voice
op_assign
id|event
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|voice
OL
l_int|0
op_logical_or
id|voice
op_ge
id|port-&gt;chset.max_channels
)paren
id|chan
op_assign
l_int|NULL
suffix:semicolon
r_else
id|chan
op_assign
op_amp
id|port-&gt;chset.channels
(braket
id|voice
)braket
suffix:semicolon
id|p1
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
op_amp
id|event
(braket
l_int|4
)braket
suffix:semicolon
id|p2
op_assign
op_star
(paren
r_int
op_star
)paren
op_amp
id|event
(braket
l_int|6
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|_EMUX_OSS_REMOVE_LAST_SAMPLES
suffix:colon
id|snd_soundfont_remove_unlocked
c_func
(paren
id|emu-&gt;sflist
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_SEND_EFFECT
suffix:colon
r_if
c_cond
(paren
id|chan
)paren
id|snd_emux_send_effect_oss
c_func
(paren
id|port
comma
id|chan
comma
id|p1
comma
id|p2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_TERMINATE_ALL
suffix:colon
id|snd_emux_terminate_all
c_func
(paren
id|emu
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_TERMINATE_CHANNEL
suffix:colon
multiline_comment|/*snd_emux_mute_channel(emu, chan);*/
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_RESET_CHANNEL
suffix:colon
multiline_comment|/*snd_emux_channel_init(chset, chan);*/
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_RELEASE_ALL
suffix:colon
id|fake_event
c_func
(paren
id|emu
comma
id|port
comma
id|voice
comma
id|MIDI_CTL_ALL_NOTES_OFF
comma
l_int|0
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_NOTEOFF_ALL
suffix:colon
id|fake_event
c_func
(paren
id|emu
comma
id|port
comma
id|voice
comma
id|MIDI_CTL_ALL_SOUNDS_OFF
comma
l_int|0
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_INITIAL_VOLUME
suffix:colon
r_if
c_cond
(paren
id|p2
)paren
(brace
id|port-&gt;volume_atten
op_assign
(paren
r_int
)paren
id|p1
suffix:semicolon
id|snd_emux_update_port
c_func
(paren
id|port
comma
id|SNDRV_EMUX_UPDATE_VOLUME
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_CHN_PRESSURE
suffix:colon
r_if
c_cond
(paren
id|chan
)paren
(brace
id|chan-&gt;midi_pressure
op_assign
id|p1
suffix:semicolon
id|snd_emux_update_channel
c_func
(paren
id|port
comma
id|chan
comma
id|SNDRV_EMUX_UPDATE_FMMOD
op_or
id|SNDRV_EMUX_UPDATE_FM2FRQ2
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_CHANNEL_MODE
suffix:colon
id|reset_port_mode
c_func
(paren
id|port
comma
id|p1
)paren
suffix:semicolon
id|snd_emux_reset_port
c_func
(paren
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_DRUM_CHANNELS
suffix:colon
id|port-&gt;drum_flags
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
op_amp
id|event
(braket
l_int|4
)braket
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
id|port-&gt;chset.max_channels
suffix:semicolon
id|i
op_increment
)paren
(brace
id|chan
op_assign
op_amp
id|port-&gt;chset.channels
(braket
id|i
)braket
suffix:semicolon
id|chan-&gt;drum_channel
op_assign
(paren
(paren
id|port-&gt;drum_flags
op_rshift
id|i
)paren
op_amp
l_int|1
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_MISC_MODE
suffix:colon
r_if
c_cond
(paren
id|p1
OL
id|EMUX_MD_END
)paren
id|port-&gt;ctrls
(braket
id|p1
)braket
op_assign
id|p2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_EMUX_OSS_DEBUG_MODE
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|emu-&gt;ops.oss_ioctl
)paren
id|emu-&gt;ops
dot
id|oss_ioctl
c_func
(paren
id|emu
comma
id|cmd
comma
id|p1
comma
id|p2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * GUS specific h/w controls&n; */
macro_line|#include &lt;linux/ultrasound.h&gt;
r_static
r_void
DECL|function|gusspec_control
id|gusspec_control
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
id|snd_emux_port_t
op_star
id|port
comma
r_int
id|cmd
comma
r_int
r_char
op_star
id|event
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
r_int
id|voice
suffix:semicolon
r_int
r_int
id|p1
suffix:semicolon
r_int
id|p2
suffix:semicolon
r_int
id|plong
suffix:semicolon
id|snd_midi_channel_t
op_star
id|chan
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;port_mode
op_ne
id|SNDRV_EMUX_PORT_MODE_OSS_SYNTH
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|_GUS_NUMVOICES
)paren
r_return
suffix:semicolon
id|voice
op_assign
id|event
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|voice
OL
l_int|0
op_logical_or
id|voice
op_ge
id|port-&gt;chset.max_channels
)paren
r_return
suffix:semicolon
id|chan
op_assign
op_amp
id|port-&gt;chset.channels
(braket
id|voice
)braket
suffix:semicolon
id|p1
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
op_amp
id|event
(braket
l_int|4
)braket
suffix:semicolon
id|p2
op_assign
op_star
(paren
r_int
op_star
)paren
op_amp
id|event
(braket
l_int|6
)braket
suffix:semicolon
id|plong
op_assign
op_star
(paren
r_int
op_star
)paren
op_amp
id|event
(braket
l_int|4
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|_GUS_VOICESAMPLE
suffix:colon
id|chan-&gt;midi_program
op_assign
id|p1
suffix:semicolon
r_return
suffix:semicolon
r_case
id|_GUS_VOICEBALA
suffix:colon
multiline_comment|/* 0 to 15 --&gt; 0 to 127 */
id|chan-&gt;control
(braket
id|MIDI_CTL_MSB_PAN
)braket
op_assign
(paren
r_int
)paren
id|p1
op_lshift
l_int|3
suffix:semicolon
id|snd_emux_update_channel
c_func
(paren
id|port
comma
id|chan
comma
id|SNDRV_EMUX_UPDATE_PAN
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|_GUS_VOICEVOL
suffix:colon
r_case
id|_GUS_VOICEVOL2
suffix:colon
multiline_comment|/* not supported yet */
r_return
suffix:semicolon
r_case
id|_GUS_RAMPRANGE
suffix:colon
r_case
id|_GUS_RAMPRATE
suffix:colon
r_case
id|_GUS_RAMPMODE
suffix:colon
r_case
id|_GUS_RAMPON
suffix:colon
r_case
id|_GUS_RAMPOFF
suffix:colon
multiline_comment|/* volume ramping not supported */
r_return
suffix:semicolon
r_case
id|_GUS_VOLUME_SCALE
suffix:colon
r_return
suffix:semicolon
r_case
id|_GUS_VOICE_POS
suffix:colon
macro_line|#ifdef SNDRV_EMUX_USE_RAW_EFFECT
id|snd_emux_send_effect
c_func
(paren
id|port
comma
id|chan
comma
id|EMUX_FX_SAMPLE_START
comma
(paren
r_int
)paren
(paren
id|plong
op_amp
l_int|0x7fff
)paren
comma
id|EMUX_FX_FLAG_SET
)paren
suffix:semicolon
id|snd_emux_send_effect
c_func
(paren
id|port
comma
id|chan
comma
id|EMUX_FX_COARSE_SAMPLE_START
comma
(paren
id|plong
op_rshift
l_int|15
)paren
op_amp
l_int|0xffff
comma
id|EMUX_FX_FLAG_SET
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * send an event to midi emulation&n; */
r_static
r_void
DECL|function|fake_event
id|fake_event
c_func
(paren
id|snd_emux_t
op_star
id|emu
comma
id|snd_emux_port_t
op_star
id|port
comma
r_int
id|ch
comma
r_int
id|param
comma
r_int
id|val
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
(brace
id|snd_seq_event_t
id|ev
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
id|ev.type
op_assign
id|SNDRV_SEQ_EVENT_CONTROLLER
suffix:semicolon
id|ev.data.control.channel
op_assign
id|ch
suffix:semicolon
id|ev.data.control.param
op_assign
id|param
suffix:semicolon
id|ev.data.control.value
op_assign
id|val
suffix:semicolon
id|snd_emux_event_input
c_func
(paren
op_amp
id|ev
comma
l_int|0
comma
id|port
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SND_SEQUENCER_OSS */
eof
