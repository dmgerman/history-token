multiline_comment|/*&n; *  Copyright (c) by Uros Bizjak &lt;uros@kss-loka.si&gt;&n; *&n; *  Midi Sequencer interface routines for OPL2/OPL3/OPL4 FM&n; *&n; *  OPL2/3 FM instrument loader:&n; *   alsa-tools/seq/sbiload/&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;opl3_voice.h&quot;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Uros Bizjak &lt;uros@kss-loka.si&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ALSA driver for OPL3 FM synth&quot;
)paren
suffix:semicolon
id|MODULE_CLASSES
c_func
(paren
l_string|&quot;{sound}&quot;
)paren
suffix:semicolon
DECL|variable|use_internal_drums
r_int
id|use_internal_drums
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|use_internal_drums
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|use_internal_drums
comma
l_string|&quot;Enable internal OPL2/3 drums.&quot;
)paren
suffix:semicolon
DECL|function|dec_mod_count
r_static
r_inline
r_void
id|dec_mod_count
c_func
(paren
r_struct
id|module
op_star
id|module
)paren
(brace
r_if
c_cond
(paren
id|module
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|module
)paren
suffix:semicolon
)brace
DECL|function|snd_opl3_synth_use_inc
r_int
id|snd_opl3_synth_use_inc
c_func
(paren
id|opl3_t
op_star
id|opl3
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|try_inc_mod_count
c_func
(paren
id|opl3-&gt;card-&gt;module
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
DECL|function|snd_opl3_synth_use_dec
r_void
id|snd_opl3_synth_use_dec
c_func
(paren
id|opl3_t
op_star
id|opl3
)paren
(brace
id|dec_mod_count
c_func
(paren
id|opl3-&gt;card-&gt;module
)paren
suffix:semicolon
)brace
DECL|function|snd_opl3_synth_setup
r_int
id|snd_opl3_synth_setup
c_func
(paren
id|opl3_t
op_star
id|opl3
)paren
(brace
r_int
id|idx
suffix:semicolon
id|down
c_func
(paren
op_amp
id|opl3-&gt;access_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opl3-&gt;used
)paren
(brace
id|up
c_func
(paren
op_amp
id|opl3-&gt;access_mutex
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|opl3-&gt;used
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|opl3-&gt;access_mutex
)paren
suffix:semicolon
id|snd_opl3_reset
c_func
(paren
id|opl3
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
id|MAX_OPL3_VOICES
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|opl3-&gt;voices
(braket
id|idx
)braket
dot
id|state
op_assign
id|SNDRV_OPL3_ST_OFF
suffix:semicolon
id|opl3-&gt;voices
(braket
id|idx
)braket
dot
id|time
op_assign
l_int|0
suffix:semicolon
id|opl3-&gt;voices
(braket
id|idx
)braket
dot
id|keyon_reg
op_assign
l_int|0x00
suffix:semicolon
)brace
id|opl3-&gt;use_time
op_assign
l_int|0
suffix:semicolon
id|opl3-&gt;connection_reg
op_assign
l_int|0x00
suffix:semicolon
r_if
c_cond
(paren
id|opl3-&gt;hardware
op_ge
id|OPL3_HW_OPL3
)paren
(brace
multiline_comment|/* Enter OPL3 mode */
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_RIGHT
op_or
id|OPL3_REG_MODE
comma
id|OPL3_OPL3_ENABLE
)paren
suffix:semicolon
multiline_comment|/* Clear 4-op connections */
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_RIGHT
op_or
id|OPL3_REG_CONNECTION_SELECT
comma
id|opl3-&gt;connection_reg
)paren
suffix:semicolon
id|opl3-&gt;max_voices
op_assign
id|MAX_OPL3_VOICES
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl3_synth_cleanup
r_void
id|snd_opl3_synth_cleanup
c_func
(paren
id|opl3_t
op_star
id|opl3
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Stop system timer */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|opl3-&gt;sys_timer_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opl3-&gt;sys_timer_status
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|opl3-&gt;tlist
)paren
suffix:semicolon
id|opl3-&gt;sys_timer_status
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|opl3-&gt;sys_timer_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_opl3_reset
c_func
(paren
id|opl3
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|opl3-&gt;access_mutex
)paren
suffix:semicolon
id|opl3-&gt;used
op_decrement
suffix:semicolon
id|up
c_func
(paren
op_amp
id|opl3-&gt;access_mutex
)paren
suffix:semicolon
)brace
DECL|function|snd_opl3_synth_use
r_int
id|snd_opl3_synth_use
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
id|opl3_t
op_star
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
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
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_opl3_synth_setup
c_func
(paren
id|opl3
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|use_internal_drums
)paren
(brace
multiline_comment|/* Percussion mode */
id|opl3-&gt;voices
(braket
l_int|6
)braket
dot
id|state
op_assign
id|opl3-&gt;voices
(braket
l_int|7
)braket
dot
id|state
op_assign
id|opl3-&gt;voices
(braket
l_int|8
)braket
dot
id|state
op_assign
id|SNDRV_OPL3_ST_NOT_AVAIL
suffix:semicolon
id|snd_opl3_load_drums
c_func
(paren
id|opl3
)paren
suffix:semicolon
id|opl3-&gt;drum_reg
op_assign
id|OPL3_PERCUSSION_ENABLE
suffix:semicolon
id|opl3
op_member_access_from_pointer
id|command
c_func
(paren
id|opl3
comma
id|OPL3_LEFT
op_or
id|OPL3_REG_PERCUSSION
comma
id|opl3-&gt;drum_reg
)paren
suffix:semicolon
)brace
r_else
(brace
id|opl3-&gt;drum_reg
op_assign
l_int|0x00
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;sender.client
op_ne
id|SNDRV_SEQ_CLIENT_SYSTEM
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_opl3_synth_use_inc
c_func
(paren
id|opl3
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
id|opl3-&gt;synth_mode
op_assign
id|SNDRV_OPL3_MODE_SEQ
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl3_synth_unuse
r_int
id|snd_opl3_synth_unuse
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
id|opl3_t
op_star
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
comma
id|private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_opl3_synth_cleanup
c_func
(paren
id|opl3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;sender.client
op_ne
id|SNDRV_SEQ_CLIENT_SYSTEM
)paren
id|snd_opl3_synth_use_dec
c_func
(paren
id|opl3
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * MIDI emulation operators&n; */
DECL|variable|opl3_ops
id|snd_midi_op_t
id|opl3_ops
op_assign
(brace
id|snd_opl3_note_on
comma
id|snd_opl3_note_off
comma
id|snd_opl3_key_press
comma
id|snd_opl3_terminate_note
comma
id|snd_opl3_control
comma
id|snd_opl3_nrpn
comma
id|snd_opl3_sysex
comma
)brace
suffix:semicolon
DECL|function|snd_opl3_synth_event_input
r_static
r_int
id|snd_opl3_synth_event_input
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
id|opl3_t
op_star
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
comma
id|private_data
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
id|SNDRV_SEQ_EVENT_INSTR_BEGIN
op_logical_and
id|ev-&gt;type
op_le
id|SNDRV_SEQ_EVENT_INSTR_CHANGE
)paren
(brace
r_if
c_cond
(paren
id|direct
)paren
(brace
id|snd_seq_instr_event
c_func
(paren
op_amp
id|opl3-&gt;fm_ops
comma
id|opl3-&gt;ilist
comma
id|ev
comma
id|opl3-&gt;seq_client
comma
id|atomic
comma
id|hop
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|snd_midi_process_event
c_func
(paren
op_amp
id|opl3_ops
comma
id|ev
comma
id|opl3-&gt;chset
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------ */
DECL|function|snd_opl3_synth_free_port
r_static
r_void
id|snd_opl3_synth_free_port
c_func
(paren
r_void
op_star
id|private_data
)paren
(brace
id|opl3_t
op_star
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
comma
id|private_data
comma
r_return
)paren
suffix:semicolon
id|snd_midi_channel_free_set
c_func
(paren
id|opl3-&gt;chset
)paren
suffix:semicolon
)brace
DECL|function|snd_opl3_synth_create_port
r_static
r_int
id|snd_opl3_synth_create_port
c_func
(paren
id|opl3_t
op_star
id|opl3
)paren
(brace
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
id|opl_ver
suffix:semicolon
id|opl3-&gt;chset
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
id|opl3-&gt;chset
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|opl3-&gt;chset-&gt;private_data
op_assign
id|opl3
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
id|snd_opl3_synth_use
suffix:semicolon
id|callbacks.unuse
op_assign
id|snd_opl3_synth_unuse
suffix:semicolon
id|callbacks.event_input
op_assign
id|snd_opl3_synth_event_input
suffix:semicolon
id|callbacks.private_free
op_assign
id|snd_opl3_synth_free_port
suffix:semicolon
id|callbacks.private_data
op_assign
id|opl3
suffix:semicolon
id|opl_ver
op_assign
(paren
id|opl3-&gt;hardware
op_amp
id|OPL3_HW_MASK
)paren
op_rshift
l_int|8
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;OPL%i Port&quot;
comma
id|opl_ver
)paren
suffix:semicolon
id|opl3-&gt;chset-&gt;client
op_assign
id|opl3-&gt;seq_client
suffix:semicolon
id|opl3-&gt;chset-&gt;port
op_assign
id|snd_seq_event_port_attach
c_func
(paren
id|opl3-&gt;seq_client
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
id|SNDRV_SEQ_PORT_TYPE_SYNTH
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opl3-&gt;chset-&gt;port
OL
l_int|0
)paren
(brace
id|snd_midi_channel_free_set
c_func
(paren
id|opl3-&gt;chset
)paren
suffix:semicolon
r_return
id|opl3-&gt;chset-&gt;port
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------ */
DECL|function|snd_opl3_seq_new_device
r_static
r_int
id|snd_opl3_seq_new_device
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
(brace
id|opl3_t
op_star
id|opl3
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
r_int
id|opl_ver
suffix:semicolon
id|opl3
op_assign
op_star
(paren
id|opl3_t
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
id|opl3
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|opl3-&gt;voice_lock
)paren
suffix:semicolon
id|opl3-&gt;seq_client
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
id|opl3
suffix:semicolon
id|callbacks.allow_output
op_assign
id|callbacks.allow_input
op_assign
l_int|1
suffix:semicolon
id|client
op_assign
id|opl3-&gt;seq_client
op_assign
id|snd_seq_create_kernel_client
c_func
(paren
id|opl3-&gt;card
comma
id|opl3-&gt;seq_dev_num
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
id|opl_ver
op_assign
(paren
id|opl3-&gt;hardware
op_amp
id|OPL3_HW_MASK
)paren
op_rshift
l_int|8
suffix:semicolon
id|sprintf
c_func
(paren
id|cinfo.name
comma
l_string|&quot;OPL%i FM synth&quot;
comma
id|opl_ver
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
id|snd_opl3_synth_create_port
c_func
(paren
id|opl3
)paren
suffix:semicolon
multiline_comment|/* initialize instrument list */
id|opl3-&gt;ilist
op_assign
id|snd_seq_instr_list_new
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opl3-&gt;ilist
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
id|opl3-&gt;seq_client
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|opl3-&gt;ilist-&gt;flags
op_assign
id|SNDRV_SEQ_INSTR_FLG_DIRECT
suffix:semicolon
id|snd_seq_fm_init
c_func
(paren
op_amp
id|opl3-&gt;fm_ops
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* setup system timer */
id|memset
c_func
(paren
op_amp
id|opl3-&gt;tlist
comma
l_int|0
comma
r_sizeof
(paren
id|opl3-&gt;tlist
)paren
)paren
suffix:semicolon
id|opl3-&gt;tlist.function
op_assign
id|snd_opl3_timer_func
suffix:semicolon
id|opl3-&gt;tlist.data
op_assign
(paren
r_int
r_int
)paren
id|opl3
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|opl3-&gt;sys_timer_lock
)paren
suffix:semicolon
id|opl3-&gt;sys_timer_status
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
id|snd_opl3_init_seq_oss
c_func
(paren
id|opl3
comma
id|cinfo.name
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl3_seq_delete_device
r_static
r_int
id|snd_opl3_seq_delete_device
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
(brace
id|opl3_t
op_star
id|opl3
suffix:semicolon
id|opl3
op_assign
op_star
(paren
id|opl3_t
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
id|opl3
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
id|snd_opl3_free_seq_oss
c_func
(paren
id|opl3
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|opl3-&gt;seq_client
op_ge
l_int|0
)paren
(brace
id|snd_seq_delete_kernel_client
c_func
(paren
id|opl3-&gt;seq_client
)paren
suffix:semicolon
id|opl3-&gt;seq_client
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opl3-&gt;ilist
)paren
id|snd_seq_instr_list_free
c_func
(paren
op_amp
id|opl3-&gt;ilist
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_opl3_seq_init
r_static
r_int
id|__init
id|alsa_opl3_seq_init
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
id|snd_opl3_seq_new_device
comma
id|snd_opl3_seq_delete_device
)brace
suffix:semicolon
r_return
id|snd_seq_device_register_driver
c_func
(paren
id|SNDRV_SEQ_DEV_ID_OPL3
comma
op_amp
id|ops
comma
r_sizeof
(paren
id|opl3_t
op_star
)paren
)paren
suffix:semicolon
)brace
DECL|function|alsa_opl3_seq_exit
r_static
r_void
id|__exit
id|alsa_opl3_seq_exit
c_func
(paren
r_void
)paren
(brace
id|snd_seq_device_unregister_driver
c_func
(paren
id|SNDRV_SEQ_DEV_ID_OPL3
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_opl3_seq_init
)paren
id|module_exit
c_func
(paren
id|alsa_opl3_seq_exit
)paren
eof
