multiline_comment|/*&n; * OSS compatible sequencer driver&n; *&n; * seq_oss_writeq.c - write queue and sync&n; *&n; * Copyright (C) 1998,99 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;seq_oss_writeq.h&quot;
macro_line|#include &quot;seq_oss_event.h&quot;
macro_line|#include &quot;seq_oss_timer.h&quot;
macro_line|#include &lt;sound/seq_oss_legacy.h&gt;
macro_line|#include &quot;../seq_lock.h&quot;
macro_line|#include &quot;../seq_clientmgr.h&quot;
multiline_comment|/*&n; * create a write queue record&n; */
id|seq_oss_writeq_t
op_star
DECL|function|snd_seq_oss_writeq_new
id|snd_seq_oss_writeq_new
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
id|seq_oss_writeq_t
op_star
id|q
suffix:semicolon
id|snd_seq_client_pool_t
id|pool
suffix:semicolon
r_if
c_cond
(paren
(paren
id|q
op_assign
id|snd_kcalloc
c_func
(paren
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
r_return
l_int|NULL
suffix:semicolon
id|q-&gt;dp
op_assign
id|dp
suffix:semicolon
id|q-&gt;maxlen
op_assign
id|maxlen
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|q-&gt;sync_lock
)paren
suffix:semicolon
id|q-&gt;sync_event_put
op_assign
l_int|0
suffix:semicolon
id|q-&gt;sync_time
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|q-&gt;sync_sleep
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pool
comma
l_int|0
comma
r_sizeof
(paren
id|pool
)paren
)paren
suffix:semicolon
id|pool.client
op_assign
id|dp-&gt;cseq
suffix:semicolon
id|pool.output_pool
op_assign
id|maxlen
suffix:semicolon
id|pool.output_room
op_assign
id|maxlen
op_div
l_int|2
suffix:semicolon
id|snd_seq_oss_control
c_func
(paren
id|dp
comma
id|SNDRV_SEQ_IOCTL_SET_CLIENT_POOL
comma
op_amp
id|pool
)paren
suffix:semicolon
r_return
id|q
suffix:semicolon
)brace
multiline_comment|/*&n; * delete the write queue&n; */
r_void
DECL|function|snd_seq_oss_writeq_delete
id|snd_seq_oss_writeq_delete
c_func
(paren
id|seq_oss_writeq_t
op_star
id|q
)paren
(brace
id|snd_seq_oss_writeq_clear
c_func
(paren
id|q
)paren
suffix:semicolon
multiline_comment|/* to be sure */
id|kfree
c_func
(paren
id|q
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * reset the write queue&n; */
r_void
DECL|function|snd_seq_oss_writeq_clear
id|snd_seq_oss_writeq_clear
c_func
(paren
id|seq_oss_writeq_t
op_star
id|q
)paren
(brace
id|snd_seq_remove_events_t
id|reset
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|reset
comma
l_int|0
comma
r_sizeof
(paren
id|reset
)paren
)paren
suffix:semicolon
id|reset.remove_mode
op_assign
id|SNDRV_SEQ_REMOVE_OUTPUT
suffix:semicolon
multiline_comment|/* remove all */
id|snd_seq_oss_control
c_func
(paren
id|q-&gt;dp
comma
id|SNDRV_SEQ_IOCTL_REMOVE_EVENTS
comma
op_amp
id|reset
)paren
suffix:semicolon
multiline_comment|/* wake up sleepers if any */
id|snd_seq_oss_writeq_wakeup
c_func
(paren
id|q
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * wait until the write buffer has enough room&n; */
r_int
DECL|function|snd_seq_oss_writeq_sync
id|snd_seq_oss_writeq_sync
c_func
(paren
id|seq_oss_writeq_t
op_star
id|q
)paren
(brace
id|seq_oss_devinfo_t
op_star
id|dp
op_assign
id|q-&gt;dp
suffix:semicolon
id|abstime_t
id|time
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|time
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
id|q-&gt;sync_time
op_ge
id|time
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* already finished */
r_if
c_cond
(paren
op_logical_neg
id|q-&gt;sync_event_put
)paren
(brace
id|snd_seq_event_t
id|ev
suffix:semicolon
id|evrec_t
op_star
id|rec
suffix:semicolon
multiline_comment|/* put echoback event */
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
id|ev.flags
op_assign
l_int|0
suffix:semicolon
id|ev.type
op_assign
id|SNDRV_SEQ_EVENT_ECHO
suffix:semicolon
id|ev.time.tick
op_assign
id|time
suffix:semicolon
multiline_comment|/* echo back to itself */
id|snd_seq_oss_fill_addr
c_func
(paren
id|dp
comma
op_amp
id|ev
comma
id|dp-&gt;addr.client
comma
id|dp-&gt;addr.port
)paren
suffix:semicolon
id|rec
op_assign
(paren
id|evrec_t
op_star
)paren
op_amp
id|ev.data
suffix:semicolon
id|rec-&gt;t.code
op_assign
id|SEQ_SYNCTIMER
suffix:semicolon
id|rec-&gt;t.time
op_assign
id|time
suffix:semicolon
id|q-&gt;sync_event_put
op_assign
l_int|1
suffix:semicolon
id|snd_seq_kernel_client_enqueue_blocking
c_func
(paren
id|dp-&gt;cseq
comma
op_amp
id|ev
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|q-&gt;sync_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q-&gt;sync_event_put
)paren
(brace
multiline_comment|/* echoback event has been received */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;sync_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* wait for echo event */
id|snd_seq_sleep_timeout_in_lock
c_func
(paren
op_amp
id|q-&gt;sync_sleep
comma
op_amp
id|q-&gt;sync_lock
comma
id|HZ
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
(brace
multiline_comment|/* interrupted - return 0 to finish sync */
id|q-&gt;sync_event_put
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;sync_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;sync_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;sync_time
op_ge
id|time
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * wake up sync - echo event was catched&n; */
r_void
DECL|function|snd_seq_oss_writeq_wakeup
id|snd_seq_oss_writeq_wakeup
c_func
(paren
id|seq_oss_writeq_t
op_star
id|q
comma
id|abstime_t
id|time
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
id|q-&gt;sync_lock
comma
id|flags
)paren
suffix:semicolon
id|q-&gt;sync_time
op_assign
id|time
suffix:semicolon
id|q-&gt;sync_event_put
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|q-&gt;sync_sleep
)paren
)paren
(brace
id|wake_up
c_func
(paren
op_amp
id|q-&gt;sync_sleep
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|q-&gt;sync_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * return the unused pool size&n; */
r_int
DECL|function|snd_seq_oss_writeq_get_free_size
id|snd_seq_oss_writeq_get_free_size
c_func
(paren
id|seq_oss_writeq_t
op_star
id|q
)paren
(brace
id|snd_seq_client_pool_t
id|pool
suffix:semicolon
id|pool.client
op_assign
id|q-&gt;dp-&gt;cseq
suffix:semicolon
id|snd_seq_oss_control
c_func
(paren
id|q-&gt;dp
comma
id|SNDRV_SEQ_IOCTL_GET_CLIENT_POOL
comma
op_amp
id|pool
)paren
suffix:semicolon
r_return
id|pool.output_free
suffix:semicolon
)brace
multiline_comment|/*&n; * set output threshold size from ioctl&n; */
r_void
DECL|function|snd_seq_oss_writeq_set_output
id|snd_seq_oss_writeq_set_output
c_func
(paren
id|seq_oss_writeq_t
op_star
id|q
comma
r_int
id|val
)paren
(brace
id|snd_seq_client_pool_t
id|pool
suffix:semicolon
id|pool.client
op_assign
id|q-&gt;dp-&gt;cseq
suffix:semicolon
id|snd_seq_oss_control
c_func
(paren
id|q-&gt;dp
comma
id|SNDRV_SEQ_IOCTL_GET_CLIENT_POOL
comma
op_amp
id|pool
)paren
suffix:semicolon
id|pool.output_room
op_assign
id|val
suffix:semicolon
id|snd_seq_oss_control
c_func
(paren
id|q-&gt;dp
comma
id|SNDRV_SEQ_IOCTL_SET_CLIENT_POOL
comma
op_amp
id|pool
)paren
suffix:semicolon
)brace
eof
