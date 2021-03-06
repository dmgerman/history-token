multiline_comment|/*&n; * OSS compatible sequencer driver&n; *&n; * seq_oss_readq.c - MIDI input queue&n; *&n; * Copyright (C) 1998,99 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;seq_oss_readq.h&quot;
macro_line|#include &quot;seq_oss_event.h&quot;
macro_line|#include &lt;sound/seq_oss_legacy.h&gt;
macro_line|#include &quot;../seq_lock.h&quot;
macro_line|#include &lt;linux/wait.h&gt;
multiline_comment|/*&n; * constants&n; */
singleline_comment|//#define SNDRV_SEQ_OSS_MAX_TIMEOUT&t;(unsigned long)(-1)
DECL|macro|SNDRV_SEQ_OSS_MAX_TIMEOUT
mdefine_line|#define SNDRV_SEQ_OSS_MAX_TIMEOUT&t;(HZ * 3600)
multiline_comment|/*&n; * prototypes&n; */
multiline_comment|/*&n; * create a read queue&n; */
id|seq_oss_readq_t
op_star
DECL|function|snd_seq_oss_readq_new
id|snd_seq_oss_readq_new
c_func
(paren
id|seq_oss_devinfo_t
op_star
id|dp
comma
r_int
id|maxlen
)paren
(brace
id|seq_oss_readq_t
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
(paren
id|q
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|q
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
l_string|&quot;can&squot;t malloc read queue&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|q-&gt;q
op_assign
id|kcalloc
c_func
(paren
id|maxlen
comma
r_sizeof
(paren
id|evrec_t
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
l_string|&quot;can&squot;t malloc read queue buffer&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|q
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|q-&gt;maxlen
op_assign
id|maxlen
suffix:semicolon
id|q-&gt;qlen
op_assign
l_int|0
suffix:semicolon
id|q-&gt;head
op_assign
id|q-&gt;tail
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|q-&gt;midi_sleep
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|q-&gt;lock
)paren
suffix:semicolon
id|q-&gt;pre_event_timeout
op_assign
id|SNDRV_SEQ_OSS_MAX_TIMEOUT
suffix:semicolon
id|q-&gt;input_time
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
r_return
id|q
suffix:semicolon
)brace
multiline_comment|/*&n; * delete the read queue&n; */
r_void
DECL|function|snd_seq_oss_readq_delete
id|snd_seq_oss_readq_delete
c_func
(paren
id|seq_oss_readq_t
op_star
id|q
)paren
(brace
r_if
c_cond
(paren
id|q
)paren
(brace
id|kfree
c_func
(paren
id|q-&gt;q
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|q
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * reset the read queue&n; */
r_void
DECL|function|snd_seq_oss_readq_clear
id|snd_seq_oss_readq_clear
c_func
(paren
id|seq_oss_readq_t
op_star
id|q
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;qlen
)paren
(brace
id|q-&gt;qlen
op_assign
l_int|0
suffix:semicolon
id|q-&gt;head
op_assign
id|q-&gt;tail
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* if someone sleeping, wake&squot;em up */
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|q-&gt;midi_sleep
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|q-&gt;midi_sleep
)paren
suffix:semicolon
id|q-&gt;input_time
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * put a midi byte&n; */
r_int
DECL|function|snd_seq_oss_readq_puts
id|snd_seq_oss_readq_puts
c_func
(paren
id|seq_oss_readq_t
op_star
id|q
comma
r_int
id|dev
comma
r_int
r_char
op_star
id|data
comma
r_int
id|len
)paren
(brace
id|evrec_t
id|rec
suffix:semicolon
r_int
id|result
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|rec
comma
l_int|0
comma
r_sizeof
(paren
id|rec
)paren
)paren
suffix:semicolon
id|rec.c
(braket
l_int|0
)braket
op_assign
id|SEQ_MIDIPUTC
suffix:semicolon
id|rec.c
(braket
l_int|2
)braket
op_assign
id|dev
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
OG
l_int|0
)paren
(brace
id|rec.c
(braket
l_int|1
)braket
op_assign
op_star
id|data
op_increment
suffix:semicolon
id|result
op_assign
id|snd_seq_oss_readq_put_event
c_func
(paren
id|q
comma
op_amp
id|rec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * copy an event to input queue:&n; * return zero if enqueued&n; */
r_int
DECL|function|snd_seq_oss_readq_put_event
id|snd_seq_oss_readq_put_event
c_func
(paren
id|seq_oss_readq_t
op_star
id|q
comma
id|evrec_t
op_star
id|ev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;qlen
op_ge
id|q-&gt;maxlen
op_minus
l_int|1
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|q-&gt;q
(braket
id|q-&gt;tail
)braket
comma
id|ev
comma
r_sizeof
(paren
op_star
id|ev
)paren
)paren
suffix:semicolon
id|q-&gt;tail
op_assign
(paren
id|q-&gt;tail
op_plus
l_int|1
)paren
op_mod
id|q-&gt;maxlen
suffix:semicolon
id|q-&gt;qlen
op_increment
suffix:semicolon
multiline_comment|/* wake up sleeper */
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|q-&gt;midi_sleep
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|q-&gt;midi_sleep
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * pop queue&n; * caller must hold lock&n; */
r_int
DECL|function|snd_seq_oss_readq_pick
id|snd_seq_oss_readq_pick
c_func
(paren
id|seq_oss_readq_t
op_star
id|q
comma
id|evrec_t
op_star
id|rec
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;qlen
op_eq
l_int|0
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|memcpy
c_func
(paren
id|rec
comma
op_amp
id|q-&gt;q
(braket
id|q-&gt;head
)braket
comma
r_sizeof
(paren
op_star
id|rec
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * sleep until ready&n; */
r_void
DECL|function|snd_seq_oss_readq_wait
id|snd_seq_oss_readq_wait
c_func
(paren
id|seq_oss_readq_t
op_star
id|q
)paren
(brace
id|wait_event_interruptible_timeout
c_func
(paren
id|q-&gt;midi_sleep
comma
(paren
id|q-&gt;qlen
OG
l_int|0
op_logical_or
id|q-&gt;head
op_eq
id|q-&gt;tail
)paren
comma
id|q-&gt;pre_event_timeout
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * drain one record&n; * caller must hold lock&n; */
r_void
DECL|function|snd_seq_oss_readq_free
id|snd_seq_oss_readq_free
c_func
(paren
id|seq_oss_readq_t
op_star
id|q
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;qlen
OG
l_int|0
)paren
(brace
id|q-&gt;head
op_assign
(paren
id|q-&gt;head
op_plus
l_int|1
)paren
op_mod
id|q-&gt;maxlen
suffix:semicolon
id|q-&gt;qlen
op_decrement
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * polling/select:&n; * return non-zero if readq is not empty.&n; */
r_int
r_int
DECL|function|snd_seq_oss_readq_poll
id|snd_seq_oss_readq_poll
c_func
(paren
id|seq_oss_readq_t
op_star
id|q
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
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|q-&gt;midi_sleep
comma
id|wait
)paren
suffix:semicolon
r_return
id|q-&gt;qlen
suffix:semicolon
)brace
multiline_comment|/*&n; * put a timestamp&n; */
r_int
DECL|function|snd_seq_oss_readq_put_timestamp
id|snd_seq_oss_readq_put_timestamp
c_func
(paren
id|seq_oss_readq_t
op_star
id|q
comma
r_int
r_int
id|curt
comma
r_int
id|seq_mode
)paren
(brace
r_if
c_cond
(paren
id|curt
op_ne
id|q-&gt;input_time
)paren
(brace
id|evrec_t
id|rec
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|rec
comma
l_int|0
comma
r_sizeof
(paren
id|rec
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|seq_mode
)paren
(brace
r_case
id|SNDRV_SEQ_OSS_MODE_SYNTH
suffix:colon
id|rec.echo
op_assign
(paren
id|curt
op_lshift
l_int|8
)paren
op_or
id|SEQ_WAIT
suffix:semicolon
id|snd_seq_oss_readq_put_event
c_func
(paren
id|q
comma
op_amp
id|rec
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SEQ_OSS_MODE_MUSIC
suffix:colon
id|rec.t.code
op_assign
id|EV_TIMING
suffix:semicolon
id|rec.t.cmd
op_assign
id|TMR_WAIT_ABS
suffix:semicolon
id|rec.t.time
op_assign
id|curt
suffix:semicolon
id|snd_seq_oss_readq_put_event
c_func
(paren
id|q
comma
op_amp
id|rec
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|q-&gt;input_time
op_assign
id|curt
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * proc interface&n; */
r_void
DECL|function|snd_seq_oss_readq_info_read
id|snd_seq_oss_readq_info_read
c_func
(paren
id|seq_oss_readq_t
op_star
id|q
comma
id|snd_info_buffer_t
op_star
id|buf
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;  read queue [%s] length = %d : tick = %ld&bslash;n&quot;
comma
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|q-&gt;midi_sleep
)paren
ques
c_cond
l_string|&quot;sleeping&quot;
suffix:colon
l_string|&quot;running&quot;
)paren
comma
id|q-&gt;qlen
comma
id|q-&gt;input_time
)paren
suffix:semicolon
)brace
eof
