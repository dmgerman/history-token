multiline_comment|/*&n; *   ALSA sequencer Priority Queue&n; *   Copyright (c) 1998-1999 by Frank van de Pol &lt;fvdpol@coil.demon.nl&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;seq_timer.h&quot;
macro_line|#include &quot;seq_prioq.h&quot;
multiline_comment|/* Implementation is a simple linked list for now...&n;&n;   This priority queue orders the events on timestamp. For events with an&n;   equeal timestamp the queue behaves as a FIFO. &n;&n;   *&n;   *           +-------+&n;   *  Head --&gt; | first |&n;   *           +-------+&n;   *                 |next&n;   *           +-----v-+&n;   *           |       |&n;   *           +-------+&n;   *                 |&n;   *           +-----v-+&n;   *           |       |&n;   *           +-------+&n;   *                 |&n;   *           +-----v-+&n;   *  Tail --&gt; | last  |&n;   *           +-------+&n;   *&n;&n; */
multiline_comment|/* create new prioq (constructor) */
DECL|function|snd_seq_prioq_new
id|prioq_t
op_star
id|snd_seq_prioq_new
c_func
(paren
r_void
)paren
(brace
id|prioq_t
op_star
id|f
suffix:semicolon
id|f
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
id|prioq_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f
op_eq
l_int|NULL
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;oops: malloc failed for snd_seq_prioq_new()&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|spin_lock_init
c_func
(paren
op_amp
id|f-&gt;lock
)paren
suffix:semicolon
id|f-&gt;head
op_assign
l_int|NULL
suffix:semicolon
id|f-&gt;tail
op_assign
l_int|NULL
suffix:semicolon
id|f-&gt;cells
op_assign
l_int|0
suffix:semicolon
r_return
id|f
suffix:semicolon
)brace
multiline_comment|/* delete prioq (destructor) */
DECL|function|snd_seq_prioq_delete
r_void
id|snd_seq_prioq_delete
c_func
(paren
id|prioq_t
op_star
op_star
id|fifo
)paren
(brace
id|prioq_t
op_star
id|f
op_assign
op_star
id|fifo
suffix:semicolon
op_star
id|fifo
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|f
op_eq
l_int|NULL
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;oops: snd_seq_prioq_delete() called with NULL prioq&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* release resources...*/
multiline_comment|/*....................*/
r_if
c_cond
(paren
id|f-&gt;cells
OG
l_int|0
)paren
(brace
multiline_comment|/* drain prioQ */
r_while
c_loop
(paren
id|f-&gt;cells
OG
l_int|0
)paren
id|snd_seq_cell_free
c_func
(paren
id|snd_seq_prioq_cell_out
c_func
(paren
id|f
)paren
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
multiline_comment|/* compare timestamp between events */
multiline_comment|/* return 1 if a &gt;= b; 0 */
DECL|function|compare_timestamp
r_static
r_inline
r_int
id|compare_timestamp
c_func
(paren
id|snd_seq_event_t
op_star
id|a
comma
id|snd_seq_event_t
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
(paren
id|a-&gt;flags
op_amp
id|SNDRV_SEQ_TIME_STAMP_MASK
)paren
op_eq
id|SNDRV_SEQ_TIME_STAMP_TICK
)paren
(brace
multiline_comment|/* compare ticks */
r_return
(paren
id|snd_seq_compare_tick_time
c_func
(paren
op_amp
id|a-&gt;time.tick
comma
op_amp
id|b-&gt;time.tick
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* compare real time */
r_return
(paren
id|snd_seq_compare_real_time
c_func
(paren
op_amp
id|a-&gt;time.time
comma
op_amp
id|b-&gt;time.time
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* compare timestamp between events */
multiline_comment|/* return negative if a &lt; b;&n; *        zero     if a = b;&n; *        positive if a &gt; b;&n; */
DECL|function|compare_timestamp_rel
r_static
r_inline
r_int
id|compare_timestamp_rel
c_func
(paren
id|snd_seq_event_t
op_star
id|a
comma
id|snd_seq_event_t
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
(paren
id|a-&gt;flags
op_amp
id|SNDRV_SEQ_TIME_STAMP_MASK
)paren
op_eq
id|SNDRV_SEQ_TIME_STAMP_TICK
)paren
(brace
multiline_comment|/* compare ticks */
r_if
c_cond
(paren
id|a-&gt;time.tick
OG
id|b-&gt;time.tick
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|a-&gt;time.tick
op_eq
id|b-&gt;time.tick
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* compare real time */
r_if
c_cond
(paren
id|a-&gt;time.time.tv_sec
OG
id|b-&gt;time.time.tv_sec
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|a-&gt;time.time.tv_sec
op_eq
id|b-&gt;time.time.tv_sec
)paren
(brace
r_if
c_cond
(paren
id|a-&gt;time.time.tv_nsec
OG
id|b-&gt;time.time.tv_nsec
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|a-&gt;time.time.tv_nsec
op_eq
id|b-&gt;time.time.tv_nsec
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* enqueue cell to prioq */
DECL|function|snd_seq_prioq_cell_in
r_int
id|snd_seq_prioq_cell_in
c_func
(paren
id|prioq_t
op_star
id|f
comma
id|snd_seq_event_cell_t
op_star
id|cell
)paren
(brace
id|snd_seq_event_cell_t
op_star
id|cur
comma
op_star
id|prev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
id|prior
suffix:semicolon
id|snd_assert
c_func
(paren
id|f
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|cell
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* check flags */
id|prior
op_assign
(paren
id|cell-&gt;event.flags
op_amp
id|SNDRV_SEQ_PRIORITY_MASK
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|f-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* check if this element needs to inserted at the end (ie. ordered &n;&t;   data is inserted) This will be very likeley if a sequencer &n;&t;   application or midi file player is feeding us (sequential) data */
r_if
c_cond
(paren
id|f-&gt;tail
op_logical_and
op_logical_neg
id|prior
)paren
(brace
r_if
c_cond
(paren
id|compare_timestamp
c_func
(paren
op_amp
id|cell-&gt;event
comma
op_amp
id|f-&gt;tail-&gt;event
)paren
)paren
(brace
multiline_comment|/* add new cell to tail of the fifo */
id|f-&gt;tail-&gt;next
op_assign
id|cell
suffix:semicolon
id|f-&gt;tail
op_assign
id|cell
suffix:semicolon
id|cell-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|f-&gt;cells
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|f-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* traverse list of elements to find the place where the new cell is&n;&t;   to be inserted... Note that this is a order n process ! */
id|prev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* previous cell */
id|cur
op_assign
id|f-&gt;head
suffix:semicolon
multiline_comment|/* cursor */
id|count
op_assign
l_int|10000
suffix:semicolon
multiline_comment|/* FIXME: enough big, isn&squot;t it? */
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* compare timestamps */
r_int
id|rel
op_assign
id|compare_timestamp_rel
c_func
(paren
op_amp
id|cell-&gt;event
comma
op_amp
id|cur-&gt;event
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rel
OL
l_int|0
)paren
multiline_comment|/* new cell has earlier schedule time, */
r_break
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rel
op_eq
l_int|0
op_logical_and
id|prior
)paren
multiline_comment|/* equal schedule time and prior to others */
r_break
suffix:semicolon
multiline_comment|/* new cell has equal or larger schedule time, */
multiline_comment|/* move cursor to next cell */
id|prev
op_assign
id|cur
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|count
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|f-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cannot find a pointer.. infinite loop?&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/* insert it before cursor */
r_if
c_cond
(paren
id|prev
op_ne
l_int|NULL
)paren
id|prev-&gt;next
op_assign
id|cell
suffix:semicolon
id|cell-&gt;next
op_assign
id|cur
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;head
op_eq
id|cur
)paren
multiline_comment|/* this is the first cell, set head to it */
id|f-&gt;head
op_assign
id|cell
suffix:semicolon
r_if
c_cond
(paren
id|cur
op_eq
l_int|NULL
)paren
multiline_comment|/* reached end of the list */
id|f-&gt;tail
op_assign
id|cell
suffix:semicolon
id|f-&gt;cells
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|f-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* dequeue cell from prioq */
DECL|function|snd_seq_prioq_cell_out
id|snd_seq_event_cell_t
op_star
id|snd_seq_prioq_cell_out
c_func
(paren
id|prioq_t
op_star
id|f
)paren
(brace
id|snd_seq_event_cell_t
op_star
id|cell
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|f
op_eq
l_int|NULL
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;oops: snd_seq_prioq_cell_in() called with NULL prioq&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|f-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|cell
op_assign
id|f-&gt;head
suffix:semicolon
r_if
c_cond
(paren
id|cell
)paren
(brace
id|f-&gt;head
op_assign
id|cell-&gt;next
suffix:semicolon
multiline_comment|/* reset tail if this was the last element */
r_if
c_cond
(paren
id|f-&gt;tail
op_eq
id|cell
)paren
id|f-&gt;tail
op_assign
l_int|NULL
suffix:semicolon
id|cell-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|f-&gt;cells
op_decrement
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|f-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|cell
suffix:semicolon
)brace
multiline_comment|/* return number of events available in prioq */
DECL|function|snd_seq_prioq_avail
r_int
id|snd_seq_prioq_avail
c_func
(paren
id|prioq_t
op_star
id|f
)paren
(brace
r_if
c_cond
(paren
id|f
op_eq
l_int|NULL
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;oops: snd_seq_prioq_cell_in() called with NULL prioq&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|f-&gt;cells
suffix:semicolon
)brace
multiline_comment|/* peek at cell at the head of the prioq */
DECL|function|snd_seq_prioq_cell_peek
id|snd_seq_event_cell_t
op_star
id|snd_seq_prioq_cell_peek
c_func
(paren
id|prioq_t
op_star
id|f
)paren
(brace
r_if
c_cond
(paren
id|f
op_eq
l_int|NULL
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;oops: snd_seq_prioq_cell_in() called with NULL prioq&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|f-&gt;head
suffix:semicolon
)brace
DECL|function|prioq_match
r_static
r_inline
r_int
id|prioq_match
c_func
(paren
id|snd_seq_event_cell_t
op_star
id|cell
comma
r_int
id|client
comma
r_int
id|timestamp
)paren
(brace
r_if
c_cond
(paren
id|cell-&gt;event.source.client
op_eq
id|client
op_logical_or
id|cell-&gt;event.dest.client
op_eq
id|client
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timestamp
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cell-&gt;event.flags
op_amp
id|SNDRV_SEQ_TIME_STAMP_MASK
)paren
(brace
r_case
id|SNDRV_SEQ_TIME_STAMP_TICK
suffix:colon
r_if
c_cond
(paren
id|cell-&gt;event.time.tick
)paren
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SEQ_TIME_STAMP_REAL
suffix:colon
r_if
c_cond
(paren
id|cell-&gt;event.time.time.tv_sec
op_logical_or
id|cell-&gt;event.time.time.tv_nsec
)paren
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* remove cells for left client */
DECL|function|snd_seq_prioq_leave
r_void
id|snd_seq_prioq_leave
c_func
(paren
id|prioq_t
op_star
id|f
comma
r_int
id|client
comma
r_int
id|timestamp
)paren
(brace
r_register
id|snd_seq_event_cell_t
op_star
id|cell
comma
op_star
id|next
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|snd_seq_event_cell_t
op_star
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|snd_seq_event_cell_t
op_star
id|freefirst
op_assign
l_int|NULL
comma
op_star
id|freeprev
op_assign
l_int|NULL
comma
op_star
id|freenext
suffix:semicolon
multiline_comment|/* collect all removed cells */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|f-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|cell
op_assign
id|f-&gt;head
suffix:semicolon
r_while
c_loop
(paren
id|cell
)paren
(brace
id|next
op_assign
id|cell-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|prioq_match
c_func
(paren
id|cell
comma
id|client
comma
id|timestamp
)paren
)paren
(brace
multiline_comment|/* remove cell from prioq */
r_if
c_cond
(paren
id|cell
op_eq
id|f-&gt;head
)paren
(brace
id|f-&gt;head
op_assign
id|cell-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|prev-&gt;next
op_assign
id|cell-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cell
op_eq
id|f-&gt;tail
)paren
id|f-&gt;tail
op_assign
id|cell-&gt;next
suffix:semicolon
id|f-&gt;cells
op_decrement
suffix:semicolon
multiline_comment|/* add cell to free list */
id|cell-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|freefirst
op_eq
l_int|NULL
)paren
(brace
id|freefirst
op_assign
id|cell
suffix:semicolon
)brace
r_else
(brace
id|freeprev-&gt;next
op_assign
id|cell
suffix:semicolon
)brace
id|freeprev
op_assign
id|cell
suffix:semicolon
)brace
r_else
(brace
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;type = %i, source = %i, dest = %i, client = %i&bslash;n&quot;
comma
id|cell-&gt;event.type
comma
id|cell-&gt;event.source.client
comma
id|cell-&gt;event.dest.client
comma
id|client
)paren
suffix:semicolon
macro_line|#endif
id|prev
op_assign
id|cell
suffix:semicolon
)brace
id|cell
op_assign
id|next
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|f-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* remove selected cells */
r_while
c_loop
(paren
id|freefirst
)paren
(brace
id|freenext
op_assign
id|freefirst-&gt;next
suffix:semicolon
id|snd_seq_cell_free
c_func
(paren
id|freefirst
)paren
suffix:semicolon
id|freefirst
op_assign
id|freenext
suffix:semicolon
)brace
)brace
DECL|function|prioq_remove_match
r_static
r_int
id|prioq_remove_match
c_func
(paren
id|snd_seq_remove_events_t
op_star
id|info
comma
id|snd_seq_event_t
op_star
id|ev
)paren
(brace
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;remove_mode
op_amp
id|SNDRV_SEQ_REMOVE_DEST
)paren
(brace
r_if
c_cond
(paren
id|ev-&gt;dest.client
op_ne
id|info-&gt;dest.client
op_logical_or
id|ev-&gt;dest.port
op_ne
id|info-&gt;dest.port
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;remove_mode
op_amp
id|SNDRV_SEQ_REMOVE_DEST_CHANNEL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|snd_seq_ev_is_channel_type
c_func
(paren
id|ev
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* data.note.channel and data.control.channel are identical */
r_if
c_cond
(paren
id|ev-&gt;data.note.channel
op_ne
id|info-&gt;channel
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;remove_mode
op_amp
id|SNDRV_SEQ_REMOVE_TIME_AFTER
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;remove_mode
op_amp
id|SNDRV_SEQ_REMOVE_TIME_TICK
)paren
id|res
op_assign
id|snd_seq_compare_tick_time
c_func
(paren
op_amp
id|ev-&gt;time.tick
comma
op_amp
id|info-&gt;time.tick
)paren
suffix:semicolon
r_else
id|res
op_assign
id|snd_seq_compare_real_time
c_func
(paren
op_amp
id|ev-&gt;time.time
comma
op_amp
id|info-&gt;time.time
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;remove_mode
op_amp
id|SNDRV_SEQ_REMOVE_TIME_BEFORE
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;remove_mode
op_amp
id|SNDRV_SEQ_REMOVE_TIME_TICK
)paren
id|res
op_assign
id|snd_seq_compare_tick_time
c_func
(paren
op_amp
id|ev-&gt;time.tick
comma
op_amp
id|info-&gt;time.tick
)paren
suffix:semicolon
r_else
id|res
op_assign
id|snd_seq_compare_real_time
c_func
(paren
op_amp
id|ev-&gt;time.time
comma
op_amp
id|info-&gt;time.time
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;remove_mode
op_amp
id|SNDRV_SEQ_REMOVE_EVENT_TYPE
)paren
(brace
r_if
c_cond
(paren
id|ev-&gt;type
op_ne
id|info-&gt;type
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;remove_mode
op_amp
id|SNDRV_SEQ_REMOVE_IGNORE_OFF
)paren
(brace
multiline_comment|/* Do not remove off events */
r_switch
c_cond
(paren
id|ev-&gt;type
)paren
(brace
r_case
id|SNDRV_SEQ_EVENT_NOTEOFF
suffix:colon
multiline_comment|/* case SNDRV_SEQ_EVENT_SAMPLE_STOP: */
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|info-&gt;remove_mode
op_amp
id|SNDRV_SEQ_REMOVE_TAG_MATCH
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;tag
op_ne
id|ev-&gt;tag
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* remove cells matching remove criteria */
DECL|function|snd_seq_prioq_remove_events
r_void
id|snd_seq_prioq_remove_events
c_func
(paren
id|prioq_t
op_star
id|f
comma
r_int
id|client
comma
id|snd_seq_remove_events_t
op_star
id|info
)paren
(brace
r_register
id|snd_seq_event_cell_t
op_star
id|cell
comma
op_star
id|next
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|snd_seq_event_cell_t
op_star
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|snd_seq_event_cell_t
op_star
id|freefirst
op_assign
l_int|NULL
comma
op_star
id|freeprev
op_assign
l_int|NULL
comma
op_star
id|freenext
suffix:semicolon
multiline_comment|/* collect all removed cells */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|f-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|cell
op_assign
id|f-&gt;head
suffix:semicolon
r_while
c_loop
(paren
id|cell
)paren
(brace
id|next
op_assign
id|cell-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|cell-&gt;event.source.client
op_eq
id|client
op_logical_and
id|prioq_remove_match
c_func
(paren
id|info
comma
op_amp
id|cell-&gt;event
)paren
)paren
(brace
multiline_comment|/* remove cell from prioq */
r_if
c_cond
(paren
id|cell
op_eq
id|f-&gt;head
)paren
(brace
id|f-&gt;head
op_assign
id|cell-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|prev-&gt;next
op_assign
id|cell-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cell
op_eq
id|f-&gt;tail
)paren
id|f-&gt;tail
op_assign
id|cell-&gt;next
suffix:semicolon
id|f-&gt;cells
op_decrement
suffix:semicolon
multiline_comment|/* add cell to free list */
id|cell-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|freefirst
op_eq
l_int|NULL
)paren
(brace
id|freefirst
op_assign
id|cell
suffix:semicolon
)brace
r_else
(brace
id|freeprev-&gt;next
op_assign
id|cell
suffix:semicolon
)brace
id|freeprev
op_assign
id|cell
suffix:semicolon
)brace
r_else
(brace
id|prev
op_assign
id|cell
suffix:semicolon
)brace
id|cell
op_assign
id|next
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|f-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* remove selected cells */
r_while
c_loop
(paren
id|freefirst
)paren
(brace
id|freenext
op_assign
id|freefirst-&gt;next
suffix:semicolon
id|snd_seq_cell_free
c_func
(paren
id|freefirst
)paren
suffix:semicolon
id|freefirst
op_assign
id|freenext
suffix:semicolon
)brace
)brace
eof
