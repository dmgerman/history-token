multiline_comment|/*&n; * OSS compatible sequencer driver&n; *&n; * synth device handlers&n; *&n; * Copyright (C) 1998,99 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;seq_oss_synth.h&quot;
macro_line|#include &quot;seq_oss_midi.h&quot;
macro_line|#include &quot;../seq_lock.h&quot;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * constants&n; */
DECL|macro|SNDRV_SEQ_OSS_MAX_SYNTH_NAME
mdefine_line|#define SNDRV_SEQ_OSS_MAX_SYNTH_NAME&t;30
DECL|macro|MAX_SYSEX_BUFLEN
mdefine_line|#define MAX_SYSEX_BUFLEN&t;&t;128
multiline_comment|/*&n; * definition of synth info records&n; */
multiline_comment|/* sysex buffer */
DECL|struct|seq_oss_synth_sysex_t
r_struct
id|seq_oss_synth_sysex_t
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|skip
r_int
id|skip
suffix:semicolon
DECL|member|buf
r_int
r_char
id|buf
(braket
id|MAX_SYSEX_BUFLEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* synth info */
DECL|struct|seq_oss_synth_t
r_struct
id|seq_oss_synth_t
(brace
DECL|member|seq_device
r_int
id|seq_device
suffix:semicolon
multiline_comment|/* for synth_info */
DECL|member|synth_type
r_int
id|synth_type
suffix:semicolon
DECL|member|synth_subtype
r_int
id|synth_subtype
suffix:semicolon
DECL|member|nr_voices
r_int
id|nr_voices
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|SNDRV_SEQ_OSS_MAX_SYNTH_NAME
)braket
suffix:semicolon
DECL|member|oper
id|snd_seq_oss_callback_t
id|oper
suffix:semicolon
DECL|member|opened
r_int
id|opened
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|use_lock
id|snd_use_lock_t
id|use_lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * device table&n; */
DECL|variable|max_synth_devs
r_static
r_int
id|max_synth_devs
suffix:semicolon
DECL|variable|synth_devs
r_static
id|seq_oss_synth_t
op_star
id|synth_devs
(braket
id|SNDRV_SEQ_OSS_MAX_SYNTH_DEVS
)braket
suffix:semicolon
DECL|variable|midi_synth_dev
r_static
id|seq_oss_synth_t
id|midi_synth_dev
op_assign
(brace
op_minus
l_int|1
comma
multiline_comment|/* seq_device */
id|SYNTH_TYPE_MIDI
comma
multiline_comment|/* synth_type */
l_int|0
comma
multiline_comment|/* synth_subtype */
l_int|16
comma
multiline_comment|/* nr_voices */
l_string|&quot;MIDI&quot;
comma
multiline_comment|/* name */
)brace
suffix:semicolon
DECL|variable|register_lock
r_static
id|spinlock_t
id|register_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
r_static
id|seq_oss_synth_t
op_star
id|get_synthdev
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
)paren
suffix:semicolon
r_static
r_void
id|reset_channels
c_func
(paren
id|seq_oss_synthinfo_t
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n; * global initialization&n; */
r_void
id|__init
DECL|function|snd_seq_oss_synth_init
id|snd_seq_oss_synth_init
c_func
(paren
r_void
)paren
(brace
id|snd_use_lock_init
c_func
(paren
op_amp
id|midi_synth_dev.use_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * registration of the synth device&n; */
r_int
DECL|function|snd_seq_oss_synth_register
id|snd_seq_oss_synth_register
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_oss_synth_t
op_star
id|rec
suffix:semicolon
id|snd_seq_oss_reg_t
op_star
id|reg
op_assign
id|SNDRV_SEQ_DEVICE_ARGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rec
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|rec
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;can&squot;t malloc synth info&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|rec-&gt;seq_device
op_assign
op_minus
l_int|1
suffix:semicolon
id|rec-&gt;synth_type
op_assign
id|reg-&gt;type
suffix:semicolon
id|rec-&gt;synth_subtype
op_assign
id|reg-&gt;subtype
suffix:semicolon
id|rec-&gt;nr_voices
op_assign
id|reg-&gt;nvoices
suffix:semicolon
id|rec-&gt;oper
op_assign
id|reg-&gt;oper
suffix:semicolon
id|rec-&gt;private_data
op_assign
id|reg-&gt;private_data
suffix:semicolon
id|rec-&gt;opened
op_assign
l_int|0
suffix:semicolon
id|snd_use_lock_init
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
multiline_comment|/* copy and truncate the name of synth device */
id|strncpy
c_func
(paren
id|rec-&gt;name
comma
id|dev-&gt;name
comma
r_sizeof
(paren
id|rec-&gt;name
)paren
)paren
suffix:semicolon
id|rec-&gt;name
(braket
r_sizeof
(paren
id|rec-&gt;name
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* registration */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|register_lock
comma
id|flags
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
id|max_synth_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|synth_devs
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
id|max_synth_devs
)paren
(brace
r_if
c_cond
(paren
id|max_synth_devs
op_ge
id|SNDRV_SEQ_OSS_MAX_SYNTH_DEVS
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;no more synth slot&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rec
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|max_synth_devs
op_increment
suffix:semicolon
)brace
id|rec-&gt;seq_device
op_assign
id|i
suffix:semicolon
id|synth_devs
(braket
id|i
)braket
op_assign
id|rec
suffix:semicolon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;synth %s registered %d&bslash;n&quot;
comma
id|rec-&gt;name
comma
id|i
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
id|dev-&gt;driver_data
op_assign
id|rec
suffix:semicolon
macro_line|#ifdef SNDRV_OSS_INFO_DEV_SYNTH
r_if
c_cond
(paren
id|i
OL
id|SNDRV_CARDS
)paren
id|snd_oss_info_register
c_func
(paren
id|SNDRV_OSS_INFO_DEV_SYNTH
comma
id|i
comma
id|rec-&gt;name
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|snd_seq_oss_synth_unregister
id|snd_seq_oss_synth_unregister
c_func
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
(brace
r_int
id|index
suffix:semicolon
id|seq_oss_synth_t
op_star
id|rec
op_assign
id|dev-&gt;driver_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|max_synth_devs
suffix:semicolon
id|index
op_increment
)paren
(brace
r_if
c_cond
(paren
id|synth_devs
(braket
id|index
)braket
op_eq
id|rec
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|index
op_ge
id|max_synth_devs
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;can&squot;t unregister synth&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|synth_devs
(braket
id|index
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|index
op_eq
id|max_synth_devs
op_minus
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|index
op_decrement
suffix:semicolon
id|index
op_ge
l_int|0
suffix:semicolon
id|index
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|synth_devs
(braket
id|index
)braket
)paren
r_break
suffix:semicolon
)brace
id|max_synth_devs
op_assign
id|index
op_plus
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#ifdef SNDRV_OSS_INFO_DEV_SYNTH
r_if
c_cond
(paren
id|rec-&gt;seq_device
OL
id|SNDRV_CARDS
)paren
id|snd_oss_info_unregister
c_func
(paren
id|SNDRV_OSS_INFO_DEV_SYNTH
comma
id|rec-&gt;seq_device
)paren
suffix:semicolon
macro_line|#endif
id|snd_use_lock_sync
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rec
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; */
r_static
id|seq_oss_synth_t
op_star
DECL|function|get_sdev
id|get_sdev
c_func
(paren
r_int
id|dev
)paren
(brace
id|seq_oss_synth_t
op_star
id|rec
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
id|rec
op_assign
id|synth_devs
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|rec
)paren
id|snd_use_lock_use
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|register_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|rec
suffix:semicolon
)brace
multiline_comment|/*&n; * set up synth tables&n; */
r_void
DECL|function|snd_seq_oss_synth_setup
id|snd_seq_oss_synth_setup
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_oss_synth_t
op_star
id|rec
suffix:semicolon
id|seq_oss_synthinfo_t
op_star
id|info
suffix:semicolon
id|dp-&gt;max_synthdev
op_assign
id|max_synth_devs
suffix:semicolon
id|dp-&gt;synth_opened
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|dp-&gt;synths
comma
l_int|0
comma
r_sizeof
(paren
id|dp-&gt;synths
)paren
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
id|dp-&gt;max_synthdev
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rec
op_assign
id|get_sdev
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;oper.open
op_eq
l_int|NULL
op_logical_or
id|rec-&gt;oper.close
op_eq
l_int|NULL
)paren
(brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|info
op_assign
op_amp
id|dp-&gt;synths
(braket
id|i
)braket
suffix:semicolon
id|info-&gt;arg.app_index
op_assign
id|dp-&gt;port
suffix:semicolon
id|info-&gt;arg.file_mode
op_assign
id|dp-&gt;file_mode
suffix:semicolon
id|info-&gt;arg.seq_mode
op_assign
id|dp-&gt;seq_mode
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;seq_mode
op_eq
id|SNDRV_SEQ_OSS_MODE_SYNTH
)paren
id|info-&gt;arg.event_passing
op_assign
id|SNDRV_SEQ_OSS_PROCESS_EVENTS
suffix:semicolon
r_else
id|info-&gt;arg.event_passing
op_assign
id|SNDRV_SEQ_OSS_PASS_EVENTS
suffix:semicolon
id|info-&gt;opened
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|rec-&gt;oper.owner
)paren
)paren
(brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rec-&gt;oper
dot
id|open
c_func
(paren
op_amp
id|info-&gt;arg
comma
id|rec-&gt;private_data
)paren
OL
l_int|0
)paren
(brace
id|module_put
c_func
(paren
id|rec-&gt;oper.owner
)paren
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|info-&gt;nr_voices
op_assign
id|rec-&gt;nr_voices
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;nr_voices
OG
l_int|0
)paren
(brace
id|info-&gt;ch
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
id|seq_oss_chinfo_t
)paren
op_star
id|info-&gt;nr_voices
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|reset_channels
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
id|debug_printk
c_func
(paren
(paren
l_string|&quot;synth %d assigned&bslash;n&quot;
comma
id|i
)paren
)paren
suffix:semicolon
id|info-&gt;opened
op_increment
suffix:semicolon
id|rec-&gt;opened
op_increment
suffix:semicolon
id|dp-&gt;synth_opened
op_increment
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * set up synth tables for MIDI emulation - /dev/music mode only&n; */
r_void
DECL|function|snd_seq_oss_synth_setup_midi
id|snd_seq_oss_synth_setup_midi
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;max_synthdev
op_ge
id|SNDRV_SEQ_OSS_MAX_SYNTH_DEVS
)paren
r_return
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
id|dp-&gt;max_mididev
suffix:semicolon
id|i
op_increment
)paren
(brace
id|seq_oss_synthinfo_t
op_star
id|info
suffix:semicolon
id|info
op_assign
op_amp
id|dp-&gt;synths
(braket
id|dp-&gt;max_synthdev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_oss_midi_open
c_func
(paren
id|dp
comma
id|i
comma
id|dp-&gt;file_mode
)paren
OL
l_int|0
)paren
r_continue
suffix:semicolon
id|info-&gt;arg.app_index
op_assign
id|dp-&gt;port
suffix:semicolon
id|info-&gt;arg.file_mode
op_assign
id|dp-&gt;file_mode
suffix:semicolon
id|info-&gt;arg.seq_mode
op_assign
id|dp-&gt;seq_mode
suffix:semicolon
id|info-&gt;arg.private_data
op_assign
id|info
suffix:semicolon
id|info-&gt;is_midi
op_assign
l_int|1
suffix:semicolon
id|info-&gt;midi_mapped
op_assign
id|i
suffix:semicolon
id|info-&gt;arg.event_passing
op_assign
id|SNDRV_SEQ_OSS_PASS_EVENTS
suffix:semicolon
id|snd_seq_oss_midi_get_addr
c_func
(paren
id|dp
comma
id|i
comma
op_amp
id|info-&gt;arg.addr
)paren
suffix:semicolon
id|info-&gt;opened
op_assign
l_int|1
suffix:semicolon
id|midi_synth_dev.opened
op_increment
suffix:semicolon
id|dp-&gt;max_synthdev
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;max_synthdev
op_ge
id|SNDRV_SEQ_OSS_MAX_SYNTH_DEVS
)paren
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * clean up synth tables&n; */
r_void
DECL|function|snd_seq_oss_synth_cleanup
id|snd_seq_oss_synth_cleanup
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_oss_synth_t
op_star
id|rec
suffix:semicolon
id|seq_oss_synthinfo_t
op_star
id|info
suffix:semicolon
id|snd_assert
c_func
(paren
id|dp-&gt;max_synthdev
op_le
id|SNDRV_SEQ_OSS_MAX_SYNTH_DEVS
comma
r_return
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
id|dp-&gt;max_synthdev
suffix:semicolon
id|i
op_increment
)paren
(brace
id|info
op_assign
op_amp
id|dp-&gt;synths
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;opened
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;is_midi
)paren
(brace
r_if
c_cond
(paren
id|midi_synth_dev.opened
OG
l_int|0
)paren
(brace
id|snd_seq_oss_midi_close
c_func
(paren
id|dp
comma
id|info-&gt;midi_mapped
)paren
suffix:semicolon
id|midi_synth_dev.opened
op_decrement
suffix:semicolon
)brace
)brace
r_else
(brace
id|rec
op_assign
id|get_sdev
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;opened
OG
l_int|0
)paren
(brace
id|debug_printk
c_func
(paren
(paren
l_string|&quot;synth %d closed&bslash;n&quot;
comma
id|i
)paren
)paren
suffix:semicolon
id|rec-&gt;oper
dot
id|close
c_func
(paren
op_amp
id|info-&gt;arg
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|rec-&gt;oper.owner
)paren
suffix:semicolon
id|rec-&gt;opened
op_assign
l_int|0
suffix:semicolon
)brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;sysex
)paren
(brace
id|kfree
c_func
(paren
id|info-&gt;sysex
)paren
suffix:semicolon
id|info-&gt;sysex
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;ch
)paren
(brace
id|kfree
c_func
(paren
id|info-&gt;ch
)paren
suffix:semicolon
id|info-&gt;ch
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|dp-&gt;synth_opened
op_assign
l_int|0
suffix:semicolon
id|dp-&gt;max_synthdev
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * check if the specified device is MIDI mapped device&n; */
r_static
r_int
DECL|function|is_midi_dev
id|is_midi_dev
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev
OL
l_int|0
op_logical_or
id|dev
op_ge
id|dp-&gt;max_synthdev
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;synths
(braket
id|dev
)braket
dot
id|is_midi
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * return synth device information pointer&n; */
r_static
id|seq_oss_synth_t
op_star
DECL|function|get_synthdev
id|get_synthdev
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
)paren
(brace
id|seq_oss_synth_t
op_star
id|rec
suffix:semicolon
r_if
c_cond
(paren
id|dev
OL
l_int|0
op_logical_or
id|dev
op_ge
id|dp-&gt;max_synthdev
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dp-&gt;synths
(braket
id|dev
)braket
dot
id|opened
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;synths
(braket
id|dev
)braket
dot
id|is_midi
)paren
r_return
op_amp
id|midi_synth_dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rec
op_assign
id|get_sdev
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rec-&gt;opened
)paren
(brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|rec
suffix:semicolon
)brace
multiline_comment|/*&n; * reset note and velocity on each channel.&n; */
r_static
r_void
DECL|function|reset_channels
id|reset_channels
c_func
(paren
id|seq_oss_synthinfo_t
op_star
id|info
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;ch
op_eq
l_int|NULL
op_logical_or
op_logical_neg
id|info-&gt;nr_voices
)paren
r_return
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
id|info-&gt;nr_voices
suffix:semicolon
id|i
op_increment
)paren
(brace
id|info-&gt;ch
(braket
id|i
)braket
dot
id|note
op_assign
op_minus
l_int|1
suffix:semicolon
id|info-&gt;ch
(braket
id|i
)braket
dot
id|vel
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * reset synth device:&n; * call reset callback.  if no callback is defined, send a heartbeat&n; * event to the corresponding port.&n; */
r_void
DECL|function|snd_seq_oss_synth_reset
id|snd_seq_oss_synth_reset
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
)paren
(brace
id|seq_oss_synth_t
op_star
id|rec
suffix:semicolon
id|seq_oss_synthinfo_t
op_star
id|info
suffix:semicolon
id|snd_assert
c_func
(paren
id|dev
op_ge
l_int|0
op_logical_and
id|dev
OL
id|dp-&gt;max_synthdev
comma
r_return
)paren
suffix:semicolon
id|info
op_assign
op_amp
id|dp-&gt;synths
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;opened
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;sysex
)paren
id|info-&gt;sysex-&gt;len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* reset sysex */
id|reset_channels
c_func
(paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;is_midi
)paren
(brace
r_if
c_cond
(paren
id|midi_synth_dev.opened
op_le
l_int|0
)paren
r_return
suffix:semicolon
id|snd_seq_oss_midi_reset
c_func
(paren
id|dp
comma
id|info-&gt;midi_mapped
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_oss_midi_open
c_func
(paren
id|dp
comma
id|info-&gt;midi_mapped
comma
id|dp-&gt;file_mode
)paren
OL
l_int|0
)paren
(brace
id|midi_synth_dev.opened
op_decrement
suffix:semicolon
id|info-&gt;opened
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;sysex
)paren
(brace
id|kfree
c_func
(paren
id|info-&gt;sysex
)paren
suffix:semicolon
id|info-&gt;sysex
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;ch
)paren
(brace
id|kfree
c_func
(paren
id|info-&gt;ch
)paren
suffix:semicolon
id|info-&gt;ch
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
id|rec
op_assign
id|get_sdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;oper.reset
)paren
(brace
id|rec-&gt;oper
dot
id|reset
c_func
(paren
op_amp
id|info-&gt;arg
)paren
suffix:semicolon
)brace
r_else
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
id|snd_seq_oss_fill_addr
c_func
(paren
id|dp
comma
op_amp
id|ev
comma
id|info-&gt;arg.addr.client
comma
id|info-&gt;arg.addr.port
)paren
suffix:semicolon
id|ev.type
op_assign
id|SNDRV_SEQ_EVENT_RESET
suffix:semicolon
id|snd_seq_oss_dispatch
c_func
(paren
id|dp
comma
op_amp
id|ev
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * load a patch record:&n; * call load_patch callback function&n; */
r_int
DECL|function|snd_seq_oss_synth_load_patch
id|snd_seq_oss_synth_load_patch
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
comma
r_int
id|fmt
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|p
comma
r_int
id|c
)paren
(brace
id|seq_oss_synth_t
op_star
id|rec
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|dev
OL
l_int|0
op_logical_or
id|dev
op_ge
id|dp-&gt;max_synthdev
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|is_midi_dev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rec
op_assign
id|get_synthdev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;oper.load_patch
op_eq
l_int|NULL
)paren
id|rc
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_else
id|rc
op_assign
id|rec-&gt;oper
dot
id|load_patch
c_func
(paren
op_amp
id|dp-&gt;synths
(braket
id|dev
)braket
dot
id|arg
comma
id|fmt
comma
id|buf
comma
id|p
comma
id|c
)paren
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * check if the device is valid synth device&n; */
r_int
DECL|function|snd_seq_oss_synth_is_valid
id|snd_seq_oss_synth_is_valid
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
)paren
(brace
id|seq_oss_synth_t
op_star
id|rec
suffix:semicolon
id|rec
op_assign
id|get_synthdev
c_func
(paren
id|dp
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec
)paren
(brace
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * receive OSS 6 byte sysex packet:&n; * the full sysex message will be sent if it reaches to the end of data&n; * (0xff).&n; */
r_int
DECL|function|snd_seq_oss_synth_sysex
id|snd_seq_oss_synth_sysex
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
comma
r_int
r_char
op_star
id|buf
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
r_int
id|i
comma
id|send
suffix:semicolon
r_int
r_char
op_star
id|dest
suffix:semicolon
id|seq_oss_synth_sysex_t
op_star
id|sysex
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|snd_seq_oss_synth_is_valid
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|sysex
op_assign
id|dp-&gt;synths
(braket
id|dev
)braket
dot
id|sysex
suffix:semicolon
r_if
c_cond
(paren
id|sysex
op_eq
l_int|NULL
)paren
(brace
id|sysex
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sysex
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sysex
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dp-&gt;synths
(braket
id|dev
)braket
dot
id|sysex
op_assign
id|sysex
suffix:semicolon
)brace
id|send
op_assign
l_int|0
suffix:semicolon
id|dest
op_assign
id|sysex-&gt;buf
op_plus
id|sysex-&gt;len
suffix:semicolon
multiline_comment|/* copy 6 byte packet to the buffer */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_eq
l_int|0xff
)paren
(brace
id|send
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dest
(braket
id|i
)braket
op_assign
id|buf
(braket
id|i
)braket
suffix:semicolon
id|sysex-&gt;len
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|sysex-&gt;len
op_ge
id|MAX_SYSEX_BUFLEN
)paren
(brace
id|sysex-&gt;len
op_assign
l_int|0
suffix:semicolon
id|sysex-&gt;skip
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sysex-&gt;len
op_logical_and
id|send
)paren
(brace
r_if
c_cond
(paren
id|sysex-&gt;skip
)paren
(brace
id|sysex-&gt;skip
op_assign
l_int|0
suffix:semicolon
id|sysex-&gt;len
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* skip */
)brace
multiline_comment|/* copy the data to event record and send it */
id|ev-&gt;flags
op_assign
id|SNDRV_SEQ_EVENT_LENGTH_VARIABLE
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_oss_synth_addr
c_func
(paren
id|dp
comma
id|dev
comma
id|ev
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ev-&gt;data.ext.len
op_assign
id|sysex-&gt;len
suffix:semicolon
id|ev-&gt;data.ext.ptr
op_assign
id|sysex-&gt;buf
suffix:semicolon
id|sysex-&gt;len
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* skip */
)brace
multiline_comment|/*&n; * fill the event source/destination addresses&n; */
r_int
DECL|function|snd_seq_oss_synth_addr
id|snd_seq_oss_synth_addr
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|snd_seq_oss_synth_is_valid
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|snd_seq_oss_fill_addr
c_func
(paren
id|dp
comma
id|ev
comma
id|dp-&gt;synths
(braket
id|dev
)braket
dot
id|arg.addr.client
comma
id|dp-&gt;synths
(braket
id|dev
)braket
dot
id|arg.addr.port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * OSS compatible ioctl&n; */
r_int
DECL|function|snd_seq_oss_synth_ioctl
id|snd_seq_oss_synth_ioctl
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|addr
)paren
(brace
id|seq_oss_synth_t
op_star
id|rec
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|is_midi_dev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rec
op_assign
id|get_synthdev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;oper.ioctl
op_eq
l_int|NULL
)paren
id|rc
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_else
id|rc
op_assign
id|rec-&gt;oper
dot
id|ioctl
c_func
(paren
op_amp
id|dp-&gt;synths
(braket
id|dev
)braket
dot
id|arg
comma
id|cmd
comma
id|addr
)paren
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * send OSS raw events - SEQ_PRIVATE and SEQ_VOLUME&n; */
r_int
DECL|function|snd_seq_oss_synth_raw_event
id|snd_seq_oss_synth_raw_event
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
comma
r_int
r_char
op_star
id|data
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|snd_seq_oss_synth_is_valid
c_func
(paren
id|dp
comma
id|dev
)paren
op_logical_or
id|is_midi_dev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|ev-&gt;type
op_assign
id|SNDRV_SEQ_EVENT_OSS
suffix:semicolon
id|memcpy
c_func
(paren
id|ev-&gt;data.raw8.d
comma
id|data
comma
l_int|8
)paren
suffix:semicolon
r_return
id|snd_seq_oss_synth_addr
c_func
(paren
id|dp
comma
id|dev
comma
id|ev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * create OSS compatible synth_info record&n; */
r_int
DECL|function|snd_seq_oss_synth_make_info
id|snd_seq_oss_synth_make_info
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|dev
comma
r_struct
id|synth_info
op_star
id|inf
)paren
(brace
id|seq_oss_synth_t
op_star
id|rec
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;synths
(braket
id|dev
)braket
dot
id|is_midi
)paren
(brace
r_struct
id|midi_info
id|minf
suffix:semicolon
id|snd_seq_oss_midi_make_info
c_func
(paren
id|dp
comma
id|dp-&gt;synths
(braket
id|dev
)braket
dot
id|midi_mapped
comma
op_amp
id|minf
)paren
suffix:semicolon
id|inf-&gt;synth_type
op_assign
id|SYNTH_TYPE_MIDI
suffix:semicolon
id|inf-&gt;synth_subtype
op_assign
l_int|0
suffix:semicolon
id|inf-&gt;nr_voices
op_assign
l_int|16
suffix:semicolon
id|inf-&gt;device
op_assign
id|dev
suffix:semicolon
id|strncpy
c_func
(paren
id|inf-&gt;name
comma
id|minf.name
comma
r_sizeof
(paren
id|inf-&gt;name
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|rec
op_assign
id|get_synthdev
c_func
(paren
id|dp
comma
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|inf-&gt;synth_type
op_assign
id|rec-&gt;synth_type
suffix:semicolon
id|inf-&gt;synth_subtype
op_assign
id|rec-&gt;synth_subtype
suffix:semicolon
id|inf-&gt;nr_voices
op_assign
id|rec-&gt;nr_voices
suffix:semicolon
id|inf-&gt;device
op_assign
id|dev
suffix:semicolon
id|strncpy
c_func
(paren
id|inf-&gt;name
comma
id|rec-&gt;name
comma
r_sizeof
(paren
id|inf-&gt;name
)paren
)paren
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * proc interface&n; */
r_void
DECL|function|snd_seq_oss_synth_info_read
id|snd_seq_oss_synth_info_read
c_func
(paren
id|snd_info_buffer_t
op_star
id|buf
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_oss_synth_t
op_star
id|rec
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;nNumber of synth devices: %d&bslash;n&quot;
comma
id|max_synth_devs
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
id|max_synth_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;nsynth %d: &quot;
comma
id|i
)paren
suffix:semicolon
id|rec
op_assign
id|get_sdev
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec
op_eq
l_int|NULL
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;*empty*&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;[%s]&bslash;n&quot;
comma
id|rec-&gt;name
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;  type 0x%x : subtype 0x%x : voices %d&bslash;n&quot;
comma
id|rec-&gt;synth_type
comma
id|rec-&gt;synth_subtype
comma
id|rec-&gt;nr_voices
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;  capabilities : ioctl %s / load_patch %s&bslash;n&quot;
comma
id|enabled_str
c_func
(paren
(paren
r_int
)paren
id|rec-&gt;oper.ioctl
)paren
comma
id|enabled_str
c_func
(paren
(paren
r_int
)paren
id|rec-&gt;oper.load_patch
)paren
)paren
suffix:semicolon
id|snd_use_lock_free
c_func
(paren
op_amp
id|rec-&gt;use_lock
)paren
suffix:semicolon
)brace
)brace
eof
