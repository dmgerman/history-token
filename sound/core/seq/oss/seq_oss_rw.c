multiline_comment|/*&n; * OSS compatible sequencer driver&n; *&n; * read/write/select interface to device file&n; *&n; * Copyright (C) 1998,99 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;seq_oss_device.h&quot;
macro_line|#include &quot;seq_oss_readq.h&quot;
macro_line|#include &quot;seq_oss_writeq.h&quot;
macro_line|#include &quot;seq_oss_synth.h&quot;
macro_line|#include &lt;sound/seq_oss_legacy.h&gt;
macro_line|#include &quot;seq_oss_event.h&quot;
macro_line|#include &quot;seq_oss_timer.h&quot;
macro_line|#include &quot;../seq_clientmgr.h&quot;
multiline_comment|/*&n; * protoypes&n; */
r_static
r_int
id|insert_queue
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
id|evrec_t
op_star
id|rec
comma
r_struct
id|file
op_star
id|opt
)paren
suffix:semicolon
multiline_comment|/*&n; * read interface&n; */
r_int
DECL|function|snd_seq_oss_read
id|snd_seq_oss_read
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|seq_oss_readq_t
op_star
id|readq
op_assign
id|dp-&gt;readq
suffix:semicolon
r_int
id|result
op_assign
l_int|0
comma
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|ev_len
suffix:semicolon
id|evrec_t
id|rec
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|readq
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
op_minus
id|ENXIO
suffix:semicolon
r_while
c_loop
(paren
id|count
op_ge
id|SHORT_EVENT_SIZE
)paren
(brace
id|snd_seq_oss_readq_lock
c_func
(paren
id|readq
comma
id|flags
)paren
suffix:semicolon
id|err
op_assign
id|snd_seq_oss_readq_pick
c_func
(paren
id|readq
comma
op_amp
id|rec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EAGAIN
op_logical_and
op_logical_neg
id|is_nonblock_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
op_logical_and
id|result
op_eq
l_int|0
)paren
(brace
id|snd_seq_oss_readq_unlock
c_func
(paren
id|readq
comma
id|flags
)paren
suffix:semicolon
id|snd_seq_oss_readq_wait
c_func
(paren
id|readq
)paren
suffix:semicolon
id|snd_seq_oss_readq_lock
c_func
(paren
id|readq
comma
id|flags
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
id|err
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_else
id|err
op_assign
id|snd_seq_oss_readq_pick
c_func
(paren
id|readq
comma
op_amp
id|rec
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|snd_seq_oss_readq_unlock
c_func
(paren
id|readq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ev_len
op_assign
id|ev_length
c_func
(paren
op_amp
id|rec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ev_len
OL
id|count
)paren
(brace
id|snd_seq_oss_readq_unlock
c_func
(paren
id|readq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|snd_seq_oss_readq_free
c_func
(paren
id|readq
)paren
suffix:semicolon
id|snd_seq_oss_readq_unlock
c_func
(paren
id|readq
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|rec
comma
id|ev_len
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|result
op_add_assign
id|ev_len
suffix:semicolon
id|buf
op_add_assign
id|ev_len
suffix:semicolon
id|count
op_sub_assign
id|ev_len
suffix:semicolon
)brace
r_return
id|result
OG
l_int|0
ques
c_cond
id|result
suffix:colon
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * write interface&n; */
r_int
DECL|function|snd_seq_oss_write
id|snd_seq_oss_write
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
r_struct
id|file
op_star
id|opt
)paren
(brace
r_int
id|result
op_assign
l_int|0
comma
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|ev_size
comma
id|fmt
suffix:semicolon
id|evrec_t
id|rec
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
op_minus
id|ENXIO
suffix:semicolon
r_while
c_loop
(paren
id|count
op_ge
id|SHORT_EVENT_SIZE
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rec
comma
id|buf
comma
id|SHORT_EVENT_SIZE
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rec.s.code
op_eq
id|SEQ_FULLSIZE
)paren
(brace
multiline_comment|/* load patch */
r_if
c_cond
(paren
id|result
OG
l_int|0
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|fmt
op_assign
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|rec.c
)paren
op_amp
l_int|0xffff
suffix:semicolon
multiline_comment|/* FIXME the return value isn&squot;t correct */
r_return
id|snd_seq_oss_synth_load_patch
c_func
(paren
id|dp
comma
id|rec.s.dev
comma
id|fmt
comma
id|buf
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ev_is_long
c_func
(paren
op_amp
id|rec
)paren
)paren
(brace
multiline_comment|/* extended code */
r_if
c_cond
(paren
id|rec.s.code
op_eq
id|SEQ_EXTENDED
op_logical_and
id|dp-&gt;seq_mode
op_eq
id|SNDRV_SEQ_OSS_MODE_MUSIC
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ev_size
op_assign
id|LONG_EVENT_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|ev_size
)paren
r_break
suffix:semicolon
multiline_comment|/* copy the reset 4 bytes */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|rec.c
op_plus
id|SHORT_EVENT_SIZE
comma
id|buf
op_plus
id|SHORT_EVENT_SIZE
comma
id|LONG_EVENT_SIZE
op_minus
id|SHORT_EVENT_SIZE
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* old-type code */
r_if
c_cond
(paren
id|dp-&gt;seq_mode
op_eq
id|SNDRV_SEQ_OSS_MODE_MUSIC
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ev_size
op_assign
id|SHORT_EVENT_SIZE
suffix:semicolon
)brace
multiline_comment|/* insert queue */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|insert_queue
c_func
(paren
id|dp
comma
op_amp
id|rec
comma
id|opt
)paren
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|result
op_add_assign
id|ev_size
suffix:semicolon
id|buf
op_add_assign
id|ev_size
suffix:semicolon
id|count
op_sub_assign
id|ev_size
suffix:semicolon
)brace
r_return
id|result
OG
l_int|0
ques
c_cond
id|result
suffix:colon
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * insert event record to write queue&n; * return: 0 = OK, non-zero = NG&n; */
r_static
r_int
DECL|function|insert_queue
id|insert_queue
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
id|evrec_t
op_star
id|rec
comma
r_struct
id|file
op_star
id|opt
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|snd_seq_event_t
id|event
suffix:semicolon
multiline_comment|/* if this is a timing event, process the current time */
r_if
c_cond
(paren
id|snd_seq_oss_process_timer_event
c_func
(paren
id|dp-&gt;timer
comma
id|rec
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* no need to insert queue */
multiline_comment|/* parse this event */
id|memset
c_func
(paren
op_amp
id|event
comma
l_int|0
comma
r_sizeof
(paren
id|event
)paren
)paren
suffix:semicolon
multiline_comment|/* set dummy -- to be sure */
id|event.type
op_assign
id|SNDRV_SEQ_EVENT_NOTEOFF
suffix:semicolon
id|snd_seq_oss_fill_addr
c_func
(paren
id|dp
comma
op_amp
id|event
comma
id|dp-&gt;addr.port
comma
id|dp-&gt;addr.client
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_oss_process_event
c_func
(paren
id|dp
comma
id|rec
comma
op_amp
id|event
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* invalid event - no need to insert queue */
id|event.time.tick
op_assign
id|snd_seq_oss_timer_cur_tick
c_func
(paren
id|dp-&gt;timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;timer-&gt;realtime
op_logical_or
op_logical_neg
id|dp-&gt;timer-&gt;running
)paren
(brace
id|snd_seq_oss_dispatch
c_func
(paren
id|dp
comma
op_amp
id|event
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|is_nonblock_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
)paren
id|rc
op_assign
id|snd_seq_kernel_client_enqueue
c_func
(paren
id|dp-&gt;cseq
comma
op_amp
id|event
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_else
id|rc
op_assign
id|snd_seq_kernel_client_enqueue_blocking
c_func
(paren
id|dp-&gt;cseq
comma
op_amp
id|event
comma
id|opt
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * select / poll&n; */
r_int
r_int
DECL|function|snd_seq_oss_poll
id|snd_seq_oss_poll
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* input */
r_if
c_cond
(paren
id|dp-&gt;readq
op_logical_and
id|is_read_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|snd_seq_oss_readq_poll
c_func
(paren
id|dp-&gt;readq
comma
id|file
comma
id|wait
)paren
)paren
id|mask
op_or_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
)brace
multiline_comment|/* output */
r_if
c_cond
(paren
id|dp-&gt;writeq
op_logical_and
id|is_write_mode
c_func
(paren
id|dp-&gt;file_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|snd_seq_kernel_client_write_poll
c_func
(paren
id|dp-&gt;cseq
comma
id|file
comma
id|wait
)paren
)paren
id|mask
op_or_assign
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
)brace
r_return
id|mask
suffix:semicolon
)brace
eof
