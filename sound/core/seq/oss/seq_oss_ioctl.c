multiline_comment|/*&n; * OSS compatible sequencer driver&n; *&n; * OSS compatible i/o control&n; *&n; * Copyright (C) 1998,99 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;seq_oss_device.h&quot;
macro_line|#include &quot;seq_oss_readq.h&quot;
macro_line|#include &quot;seq_oss_writeq.h&quot;
macro_line|#include &quot;seq_oss_timer.h&quot;
macro_line|#include &quot;seq_oss_synth.h&quot;
macro_line|#include &quot;seq_oss_midi.h&quot;
macro_line|#include &quot;seq_oss_event.h&quot;
DECL|function|snd_seq_oss_synth_info_user
r_static
r_int
id|snd_seq_oss_synth_info_user
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_struct
id|synth_info
id|info
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|info
comma
id|arg
comma
r_sizeof
(paren
id|info
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
id|snd_seq_oss_synth_make_info
c_func
(paren
id|dp
comma
id|info.device
comma
op_amp
id|info
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
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
DECL|function|snd_seq_oss_midi_info_user
r_static
r_int
id|snd_seq_oss_midi_info_user
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_struct
id|midi_info
id|info
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|info
comma
id|arg
comma
r_sizeof
(paren
id|info
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
id|snd_seq_oss_midi_make_info
c_func
(paren
id|dp
comma
id|info.device
comma
op_amp
id|info
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
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
DECL|function|snd_seq_oss_oob_user
r_static
r_int
id|snd_seq_oss_oob_user
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_int
r_char
id|ev
(braket
l_int|8
)braket
suffix:semicolon
id|snd_seq_event_t
id|tmpev
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|ev
comma
id|arg
comma
l_int|8
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tmpev
comma
l_int|0
comma
r_sizeof
(paren
id|tmpev
)paren
)paren
suffix:semicolon
id|snd_seq_oss_fill_addr
c_func
(paren
id|dp
comma
op_amp
id|tmpev
comma
id|dp-&gt;addr.port
comma
id|dp-&gt;addr.client
)paren
suffix:semicolon
id|tmpev.time.tick
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|snd_seq_oss_process_event
c_func
(paren
id|dp
comma
(paren
id|evrec_t
op_star
)paren
id|ev
comma
op_amp
id|tmpev
)paren
)paren
(brace
id|snd_seq_oss_dispatch
c_func
(paren
id|dp
comma
op_amp
id|tmpev
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|snd_seq_oss_ioctl
id|snd_seq_oss_ioctl
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|carg
)paren
(brace
r_int
id|dev
comma
id|val
suffix:semicolon
r_void
id|__user
op_star
id|arg
op_assign
(paren
r_void
id|__user
op_star
)paren
id|carg
suffix:semicolon
r_int
id|__user
op_star
id|p
op_assign
id|arg
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDCTL_TMR_TIMEBASE
suffix:colon
r_case
id|SNDCTL_TMR_TEMPO
suffix:colon
r_case
id|SNDCTL_TMR_START
suffix:colon
r_case
id|SNDCTL_TMR_STOP
suffix:colon
r_case
id|SNDCTL_TMR_CONTINUE
suffix:colon
r_case
id|SNDCTL_TMR_METRONOME
suffix:colon
r_case
id|SNDCTL_TMR_SOURCE
suffix:colon
r_case
id|SNDCTL_TMR_SELECT
suffix:colon
r_case
id|SNDCTL_SEQ_CTRLRATE
suffix:colon
r_return
id|snd_seq_oss_timer_ioctl
c_func
(paren
id|dp-&gt;timer
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_case
id|SNDCTL_SEQ_PANIC
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;panic&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|snd_seq_oss_reset
c_func
(paren
id|dp
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|SNDCTL_SEQ_SYNC
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;sync&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_write_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
op_logical_or
id|dp-&gt;writeq
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|snd_seq_oss_writeq_sync
c_func
(paren
id|dp-&gt;writeq
)paren
)paren
suffix:semicolon
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
r_case
id|SNDCTL_SEQ_RESET
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;reset&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|snd_seq_oss_reset
c_func
(paren
id|dp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SNDCTL_SEQ_TESTMIDI
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;test midi&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|dev
comma
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|snd_seq_oss_midi_open
c_func
(paren
id|dp
comma
id|dev
comma
id|dp-&gt;file_mode
)paren
suffix:semicolon
r_case
id|SNDCTL_SEQ_GETINCOUNT
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;get in count&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;readq
op_eq
l_int|NULL
op_logical_or
op_logical_neg
id|is_read_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|dp-&gt;readq-&gt;qlen
comma
id|p
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|SNDCTL_SEQ_GETOUTCOUNT
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;get out count&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_write_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
op_logical_or
id|dp-&gt;writeq
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|snd_seq_oss_writeq_get_free_size
c_func
(paren
id|dp-&gt;writeq
)paren
comma
id|p
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|SNDCTL_SEQ_GETTIME
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;get time&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|snd_seq_oss_timer_cur_tick
c_func
(paren
id|dp-&gt;timer
)paren
comma
id|p
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|SNDCTL_SEQ_RESETSAMPLES
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;reset samples&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|dev
comma
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|snd_seq_oss_synth_ioctl
c_func
(paren
id|dp
comma
id|dev
comma
id|cmd
comma
id|carg
)paren
suffix:semicolon
r_case
id|SNDCTL_SEQ_NRSYNTHS
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;nr synths&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|dp-&gt;max_synthdev
comma
id|p
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|SNDCTL_SEQ_NRMIDIS
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;nr midis&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|dp-&gt;max_mididev
comma
id|p
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|SNDCTL_SYNTH_MEMAVL
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;mem avail&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|dev
comma
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|val
op_assign
id|snd_seq_oss_synth_ioctl
c_func
(paren
id|dp
comma
id|dev
comma
id|cmd
comma
id|carg
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|val
comma
id|p
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|SNDCTL_FM_4OP_ENABLE
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;4op&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|dev
comma
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|snd_seq_oss_synth_ioctl
c_func
(paren
id|dp
comma
id|dev
comma
id|cmd
comma
id|carg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SNDCTL_SYNTH_INFO
suffix:colon
r_case
id|SNDCTL_SYNTH_ID
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;synth info&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|snd_seq_oss_synth_info_user
c_func
(paren
id|dp
comma
id|arg
)paren
suffix:semicolon
r_case
id|SNDCTL_SEQ_OUTOFBAND
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;out of band&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|snd_seq_oss_oob_user
c_func
(paren
id|dp
comma
id|arg
)paren
suffix:semicolon
r_case
id|SNDCTL_MIDI_INFO
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;midi info&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|snd_seq_oss_midi_info_user
c_func
(paren
id|dp
comma
id|arg
)paren
suffix:semicolon
r_case
id|SNDCTL_SEQ_THRESHOLD
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;threshold&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_write_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|val
OL
l_int|1
)paren
id|val
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|val
op_ge
id|dp-&gt;writeq-&gt;maxlen
)paren
id|val
op_assign
id|dp-&gt;writeq-&gt;maxlen
op_minus
l_int|1
suffix:semicolon
id|snd_seq_oss_writeq_set_output
c_func
(paren
id|dp-&gt;writeq
comma
id|val
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SNDCTL_MIDI_PRETIME
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;pretime&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;readq
op_eq
l_int|NULL
op_logical_or
op_logical_neg
id|is_read_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
id|p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|val
op_le
l_int|0
)paren
id|val
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
id|val
op_assign
(paren
id|HZ
op_star
id|val
)paren
op_div
l_int|10
suffix:semicolon
id|dp-&gt;readq-&gt;pre_event_timeout
op_assign
id|val
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|val
comma
id|p
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_default
suffix:colon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;others&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_write_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
id|snd_seq_oss_synth_ioctl
c_func
(paren
id|dp
comma
l_int|0
comma
id|cmd
comma
id|carg
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
