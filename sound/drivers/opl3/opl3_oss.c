multiline_comment|/*&n; *  Interface for OSS sequencer emulation&n; *&n; *  Copyright (C) 2000 Uros Bizjak &lt;uros@kss-loka.si&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;opl3_voice.h&quot;
macro_line|#include &lt;linux/slab.h&gt;
r_static
r_int
id|snd_opl3_open_seq_oss
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
id|snd_opl3_close_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
)paren
suffix:semicolon
r_static
r_int
id|snd_opl3_ioctl_seq_oss
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
id|snd_opl3_load_patch_seq_oss
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
id|snd_opl3_reset_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/* */
DECL|function|snd_enter_user
r_static
r_inline
id|mm_segment_t
id|snd_enter_user
c_func
(paren
r_void
)paren
(brace
id|mm_segment_t
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
id|fs
suffix:semicolon
)brace
DECL|function|snd_leave_user
r_static
r_inline
r_void
id|snd_leave_user
c_func
(paren
id|mm_segment_t
id|fs
)paren
(brace
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
)brace
multiline_comment|/* operators */
r_extern
id|snd_midi_op_t
id|opl3_ops
suffix:semicolon
DECL|variable|oss_callback
r_static
id|snd_seq_oss_callback_t
id|oss_callback
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|snd_opl3_open_seq_oss
comma
dot
id|close
op_assign
id|snd_opl3_close_seq_oss
comma
dot
id|ioctl
op_assign
id|snd_opl3_ioctl_seq_oss
comma
dot
id|load_patch
op_assign
id|snd_opl3_load_patch_seq_oss
comma
dot
id|reset
op_assign
id|snd_opl3_reset_seq_oss
comma
)brace
suffix:semicolon
DECL|function|snd_opl3_oss_event_input
r_static
r_int
id|snd_opl3_oss_event_input
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
op_ne
id|SNDRV_SEQ_EVENT_OSS
)paren
id|snd_midi_process_event
c_func
(paren
op_amp
id|opl3_ops
comma
id|ev
comma
id|opl3-&gt;oss_chset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------ */
DECL|function|snd_opl3_oss_free_port
r_static
r_void
id|snd_opl3_oss_free_port
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
id|opl3-&gt;oss_chset
)paren
suffix:semicolon
)brace
DECL|function|snd_opl3_oss_create_port
r_static
r_int
id|snd_opl3_oss_create_port
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
id|voices
comma
id|opl_ver
suffix:semicolon
id|voices
op_assign
(paren
id|opl3-&gt;hardware
OL
id|OPL3_HW_OPL3
)paren
ques
c_cond
id|MAX_OPL2_VOICES
suffix:colon
id|MAX_OPL3_VOICES
suffix:semicolon
id|opl3-&gt;oss_chset
op_assign
id|snd_midi_channel_alloc_set
c_func
(paren
id|voices
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opl3-&gt;oss_chset
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|opl3-&gt;oss_chset-&gt;private_data
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
id|callbacks.event_input
op_assign
id|snd_opl3_oss_event_input
suffix:semicolon
id|callbacks.private_free
op_assign
id|snd_opl3_oss_free_port
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
l_string|&quot;OPL%i OSS Port&quot;
comma
id|opl_ver
)paren
suffix:semicolon
id|opl3-&gt;oss_chset-&gt;client
op_assign
id|opl3-&gt;seq_client
suffix:semicolon
id|opl3-&gt;oss_chset-&gt;port
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
comma
id|SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC
op_or
id|SNDRV_SEQ_PORT_TYPE_MIDI_GM
op_or
id|SNDRV_SEQ_PORT_TYPE_SYNTH
comma
id|voices
comma
id|voices
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opl3-&gt;oss_chset-&gt;port
OL
l_int|0
)paren
(brace
id|snd_midi_channel_free_set
c_func
(paren
id|opl3-&gt;oss_chset
)paren
suffix:semicolon
r_return
id|opl3-&gt;oss_chset-&gt;port
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------ */
multiline_comment|/* register OSS synth */
DECL|function|snd_opl3_init_seq_oss
r_void
id|snd_opl3_init_seq_oss
c_func
(paren
id|opl3_t
op_star
id|opl3
comma
r_char
op_star
id|name
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
id|opl3-&gt;card
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
id|opl3-&gt;oss_seq_dev
op_assign
id|dev
suffix:semicolon
id|strncpy
c_func
(paren
id|dev-&gt;name
comma
id|name
comma
r_sizeof
(paren
id|dev-&gt;name
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|dev-&gt;name
(braket
r_sizeof
(paren
id|dev-&gt;name
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
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
id|SYNTH_TYPE_FM
suffix:semicolon
r_if
c_cond
(paren
id|opl3-&gt;hardware
OL
id|OPL3_HW_OPL3
)paren
(brace
id|arg-&gt;subtype
op_assign
id|FM_TYPE_ADLIB
suffix:semicolon
id|arg-&gt;nvoices
op_assign
id|MAX_OPL2_VOICES
suffix:semicolon
)brace
r_else
(brace
id|arg-&gt;subtype
op_assign
id|FM_TYPE_OPL3
suffix:semicolon
id|arg-&gt;nvoices
op_assign
id|MAX_OPL3_VOICES
suffix:semicolon
)brace
id|arg-&gt;oper
op_assign
id|oss_callback
suffix:semicolon
id|arg-&gt;private_data
op_assign
id|opl3
suffix:semicolon
id|snd_opl3_oss_create_port
c_func
(paren
id|opl3
)paren
suffix:semicolon
multiline_comment|/* register to OSS synth table */
id|snd_device_register
c_func
(paren
id|opl3-&gt;card
comma
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/* unregister */
DECL|function|snd_opl3_free_seq_oss
r_void
id|snd_opl3_free_seq_oss
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
id|opl3-&gt;oss_seq_dev
)paren
(brace
id|snd_device_free
c_func
(paren
id|opl3-&gt;card
comma
id|opl3-&gt;oss_seq_dev
)paren
suffix:semicolon
id|opl3-&gt;oss_seq_dev
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/* ------------------------------ */
multiline_comment|/* open OSS sequencer */
DECL|function|snd_opl3_open_seq_oss
r_static
r_int
id|snd_opl3_open_seq_oss
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
id|opl3_t
op_star
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
comma
id|closure
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_int
id|err
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
multiline_comment|/* fill the argument data */
id|arg-&gt;private_data
op_assign
id|opl3
suffix:semicolon
id|arg-&gt;addr.client
op_assign
id|opl3-&gt;oss_chset-&gt;client
suffix:semicolon
id|arg-&gt;addr.port
op_assign
id|opl3-&gt;oss_chset-&gt;port
suffix:semicolon
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
id|opl3-&gt;synth_mode
op_assign
id|SNDRV_OPL3_MODE_SYNTH
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* close OSS sequencer */
DECL|function|snd_opl3_close_seq_oss
r_static
r_int
id|snd_opl3_close_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
)paren
(brace
id|opl3_t
op_star
id|opl3
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
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
comma
id|arg-&gt;private_data
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|snd_opl3_synth_cleanup
c_func
(paren
id|opl3
)paren
suffix:semicolon
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
multiline_comment|/* load patch */
multiline_comment|/* offsets for SBI params */
DECL|macro|AM_VIB
mdefine_line|#define AM_VIB&t;&t;0
DECL|macro|KSL_LEVEL
mdefine_line|#define KSL_LEVEL&t;2
DECL|macro|ATTACK_DECAY
mdefine_line|#define ATTACK_DECAY&t;4
DECL|macro|SUSTAIN_RELEASE
mdefine_line|#define SUSTAIN_RELEASE&t;6
DECL|macro|WAVE_SELECT
mdefine_line|#define WAVE_SELECT&t;8
multiline_comment|/* offset for SBI instrument */
DECL|macro|CONNECTION
mdefine_line|#define CONNECTION&t;10
DECL|macro|OFFSET_4OP
mdefine_line|#define OFFSET_4OP&t;11
multiline_comment|/* from sound_config.h */
DECL|macro|SBFM_MAXINSTR
mdefine_line|#define SBFM_MAXINSTR&t;256
DECL|function|snd_opl3_load_patch_seq_oss
r_static
r_int
id|snd_opl3_load_patch_seq_oss
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
id|opl3_t
op_star
id|opl3
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EINVAL
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
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
comma
id|arg-&gt;private_data
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|format
op_eq
id|FM_PATCH
)paren
op_logical_or
(paren
id|format
op_eq
id|OPL3_PATCH
)paren
)paren
(brace
r_struct
id|sbi_instrument
id|sbi
suffix:semicolon
r_int
id|size
suffix:semicolon
id|snd_seq_instr_header_t
op_star
id|put
suffix:semicolon
id|snd_seq_instr_data_t
op_star
id|data
suffix:semicolon
id|fm_xinstrument_t
op_star
id|xinstr
suffix:semicolon
id|snd_seq_event_t
id|ev
suffix:semicolon
r_int
id|i
suffix:semicolon
id|mm_segment_t
id|fs
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
(paren
r_int
)paren
r_sizeof
(paren
id|sbi
)paren
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;FM Error: Patch record too short&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sbi
comma
id|buf
comma
r_sizeof
(paren
id|sbi
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|sbi.channel
OL
l_int|0
op_logical_or
id|sbi.channel
op_ge
id|SBFM_MAXINSTR
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;FM Error: Invalid instrument number %d&bslash;n&quot;
comma
id|sbi.channel
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|size
op_assign
r_sizeof
(paren
op_star
id|put
)paren
op_plus
r_sizeof
(paren
id|fm_xinstrument_t
)paren
suffix:semicolon
id|put
op_assign
(paren
id|snd_seq_instr_header_t
op_star
)paren
id|snd_kcalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* build header */
id|data
op_assign
op_amp
id|put-&gt;data
suffix:semicolon
id|data-&gt;type
op_assign
id|SNDRV_SEQ_INSTR_ATYPE_DATA
suffix:semicolon
id|strcpy
c_func
(paren
id|data-&gt;data.format
comma
id|SNDRV_SEQ_INSTR_ID_OPL2_3
)paren
suffix:semicolon
multiline_comment|/* build data section */
id|xinstr
op_assign
(paren
id|fm_xinstrument_t
op_star
)paren
(paren
id|data
op_plus
l_int|1
)paren
suffix:semicolon
id|xinstr-&gt;stype
op_assign
id|FM_STRU_INSTR
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|xinstr-&gt;op
(braket
id|i
)braket
dot
id|am_vib
op_assign
id|sbi.operators
(braket
id|AM_VIB
op_plus
id|i
)braket
suffix:semicolon
id|xinstr-&gt;op
(braket
id|i
)braket
dot
id|ksl_level
op_assign
id|sbi.operators
(braket
id|KSL_LEVEL
op_plus
id|i
)braket
suffix:semicolon
id|xinstr-&gt;op
(braket
id|i
)braket
dot
id|attack_decay
op_assign
id|sbi.operators
(braket
id|ATTACK_DECAY
op_plus
id|i
)braket
suffix:semicolon
id|xinstr-&gt;op
(braket
id|i
)braket
dot
id|sustain_release
op_assign
id|sbi.operators
(braket
id|SUSTAIN_RELEASE
op_plus
id|i
)braket
suffix:semicolon
id|xinstr-&gt;op
(braket
id|i
)braket
dot
id|wave_select
op_assign
id|sbi.operators
(braket
id|WAVE_SELECT
op_plus
id|i
)braket
suffix:semicolon
)brace
id|xinstr-&gt;feedback_connection
(braket
l_int|0
)braket
op_assign
id|sbi.operators
(braket
id|CONNECTION
)braket
suffix:semicolon
r_if
c_cond
(paren
id|format
op_eq
id|OPL3_PATCH
)paren
(brace
id|xinstr-&gt;type
op_assign
id|FM_PATCH_OPL3
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|xinstr-&gt;op
(braket
id|i
op_plus
l_int|2
)braket
dot
id|am_vib
op_assign
id|sbi.operators
(braket
id|OFFSET_4OP
op_plus
id|AM_VIB
op_plus
id|i
)braket
suffix:semicolon
id|xinstr-&gt;op
(braket
id|i
op_plus
l_int|2
)braket
dot
id|ksl_level
op_assign
id|sbi.operators
(braket
id|OFFSET_4OP
op_plus
id|KSL_LEVEL
op_plus
id|i
)braket
suffix:semicolon
id|xinstr-&gt;op
(braket
id|i
op_plus
l_int|2
)braket
dot
id|attack_decay
op_assign
id|sbi.operators
(braket
id|OFFSET_4OP
op_plus
id|ATTACK_DECAY
op_plus
id|i
)braket
suffix:semicolon
id|xinstr-&gt;op
(braket
id|i
op_plus
l_int|2
)braket
dot
id|sustain_release
op_assign
id|sbi.operators
(braket
id|OFFSET_4OP
op_plus
id|SUSTAIN_RELEASE
op_plus
id|i
)braket
suffix:semicolon
id|xinstr-&gt;op
(braket
id|i
op_plus
l_int|2
)braket
dot
id|wave_select
op_assign
id|sbi.operators
(braket
id|OFFSET_4OP
op_plus
id|WAVE_SELECT
op_plus
id|i
)braket
suffix:semicolon
)brace
id|xinstr-&gt;feedback_connection
(braket
l_int|1
)braket
op_assign
id|sbi.operators
(braket
id|OFFSET_4OP
op_plus
id|CONNECTION
)braket
suffix:semicolon
)brace
r_else
(brace
id|xinstr-&gt;type
op_assign
id|FM_PATCH_OPL2
suffix:semicolon
)brace
id|put-&gt;id.instr.std
op_assign
id|SNDRV_SEQ_INSTR_TYPE2_OPL2_3
suffix:semicolon
id|put-&gt;id.instr.bank
op_assign
l_int|127
suffix:semicolon
id|put-&gt;id.instr.prg
op_assign
id|sbi.channel
suffix:semicolon
id|put-&gt;cmd
op_assign
id|SNDRV_SEQ_INSTR_PUT_CMD_CREATE
suffix:semicolon
id|memset
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
id|ev.source.client
op_assign
id|SNDRV_SEQ_CLIENT_OSS
suffix:semicolon
id|ev.dest
op_assign
id|arg-&gt;addr
suffix:semicolon
id|ev.flags
op_assign
id|SNDRV_SEQ_EVENT_LENGTH_VARUSR
suffix:semicolon
id|ev.queue
op_assign
id|SNDRV_SEQ_QUEUE_DIRECT
suffix:semicolon
id|fs
op_assign
id|snd_enter_user
c_func
(paren
)paren
suffix:semicolon
id|__again
suffix:colon
id|ev.type
op_assign
id|SNDRV_SEQ_EVENT_INSTR_PUT
suffix:semicolon
id|ev.data.ext.len
op_assign
id|size
suffix:semicolon
id|ev.data.ext.ptr
op_assign
id|put
suffix:semicolon
id|err
op_assign
id|snd_seq_instr_event
c_func
(paren
op_amp
id|opl3-&gt;fm_ops
comma
id|opl3-&gt;ilist
comma
op_amp
id|ev
comma
id|opl3-&gt;seq_client
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EBUSY
)paren
(brace
id|snd_seq_instr_header_t
id|remove
suffix:semicolon
id|memset
(paren
op_amp
id|remove
comma
l_int|0
comma
r_sizeof
(paren
id|remove
)paren
)paren
suffix:semicolon
id|remove.cmd
op_assign
id|SNDRV_SEQ_INSTR_FREE_CMD_SINGLE
suffix:semicolon
id|remove.id.instr
op_assign
id|put-&gt;id.instr
suffix:semicolon
multiline_comment|/* remove instrument */
id|ev.type
op_assign
id|SNDRV_SEQ_EVENT_INSTR_FREE
suffix:semicolon
id|ev.data.ext.len
op_assign
r_sizeof
(paren
id|remove
)paren
suffix:semicolon
id|ev.data.ext.ptr
op_assign
op_amp
id|remove
suffix:semicolon
id|snd_seq_instr_event
c_func
(paren
op_amp
id|opl3-&gt;fm_ops
comma
id|opl3-&gt;ilist
comma
op_amp
id|ev
comma
id|opl3-&gt;seq_client
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|__again
suffix:semicolon
)brace
id|snd_leave_user
c_func
(paren
id|fs
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|put
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* ioctl */
DECL|function|snd_opl3_ioctl_seq_oss
r_static
r_int
id|snd_opl3_ioctl_seq_oss
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
id|opl3_t
op_star
id|opl3
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
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
comma
id|arg-&gt;private_data
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDCTL_FM_LOAD_INSTR
suffix:colon
id|snd_printk
c_func
(paren
l_string|&quot;OPL3: Obsolete ioctl(SNDCTL_FM_LOAD_INSTR) used. Fix the program.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|SNDCTL_SYNTH_MEMAVL
suffix:colon
r_return
l_int|0x7fffffff
suffix:semicolon
r_case
id|SNDCTL_FM_4OP_ENABLE
suffix:colon
singleline_comment|// handled automatically by OPL instrument type
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* reset device */
DECL|function|snd_opl3_reset_seq_oss
r_static
r_int
id|snd_opl3_reset_seq_oss
c_func
(paren
id|snd_seq_oss_arg_t
op_star
id|arg
)paren
(brace
id|opl3_t
op_star
id|opl3
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
id|opl3
op_assign
id|snd_magic_cast
c_func
(paren
id|opl3_t
comma
id|arg-&gt;private_data
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
