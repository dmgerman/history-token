multiline_comment|/*&n; *   ALSA sequencer Queue handling&n; *   Copyright (c) 1998-1999 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SND_SEQ_QUEUE_H
DECL|macro|__SND_SEQ_QUEUE_H
mdefine_line|#define __SND_SEQ_QUEUE_H
macro_line|#include &quot;seq_memory.h&quot;
macro_line|#include &quot;seq_prioq.h&quot;
macro_line|#include &quot;seq_timer.h&quot;
macro_line|#include &quot;seq_lock.h&quot;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/list.h&gt;
DECL|macro|SEQ_QUEUE_NO_OWNER
mdefine_line|#define SEQ_QUEUE_NO_OWNER (-1)
DECL|struct|_snd_seq_queue
r_struct
id|_snd_seq_queue
(brace
DECL|member|queue
r_int
id|queue
suffix:semicolon
multiline_comment|/* queue number */
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* name of this queue */
DECL|member|tickq
id|prioq_t
op_star
id|tickq
suffix:semicolon
multiline_comment|/* midi tick event queue */
DECL|member|timeq
id|prioq_t
op_star
id|timeq
suffix:semicolon
multiline_comment|/* real-time event queue */
DECL|member|timer
id|seq_timer_t
op_star
id|timer
suffix:semicolon
multiline_comment|/* time keeper for this queue */
DECL|member|owner
r_int
id|owner
suffix:semicolon
multiline_comment|/* client that &squot;owns&squot; the timer */
DECL|member|locked
r_int
r_int
id|locked
suffix:colon
l_int|1
comma
multiline_comment|/* timer is only accesibble by owner if set */
DECL|member|klocked
id|klocked
suffix:colon
l_int|1
comma
multiline_comment|/* kernel lock (after START) */
DECL|member|check_again
id|check_again
suffix:colon
l_int|1
comma
DECL|member|check_blocked
id|check_blocked
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* status flags */
DECL|member|info_flags
r_int
r_int
id|info_flags
suffix:semicolon
multiline_comment|/* info for sync */
DECL|member|owner_lock
id|spinlock_t
id|owner_lock
suffix:semicolon
DECL|member|check_lock
id|spinlock_t
id|check_lock
suffix:semicolon
multiline_comment|/* clients which uses this queue (bitmap) */
id|bitmap_member
c_func
(paren
id|clients_bitmap
comma
id|SNDRV_SEQ_MAX_CLIENTS
)paren
suffix:semicolon
DECL|member|clients
r_int
r_int
id|clients
suffix:semicolon
multiline_comment|/* users of this queue */
DECL|member|timer_mutex
r_struct
id|semaphore
id|timer_mutex
suffix:semicolon
DECL|member|use_lock
id|snd_use_lock_t
id|use_lock
suffix:semicolon
DECL|member|taskq
r_struct
id|tasklet_struct
id|taskq
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* get the number of current queues */
r_int
id|snd_seq_queue_get_cur_queues
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* init queues structure */
r_int
id|snd_seq_queues_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* delete queues */
r_void
id|snd_seq_queues_delete
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* create new queue (constructor) */
r_int
id|snd_seq_queue_alloc
c_func
(paren
r_int
id|client
comma
r_int
id|locked
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* delete queue (destructor) */
r_int
id|snd_seq_queue_delete
c_func
(paren
r_int
id|client
comma
r_int
id|queueid
)paren
suffix:semicolon
multiline_comment|/* notification that client has left the system */
r_void
id|snd_seq_queue_client_termination
c_func
(paren
r_int
id|client
)paren
suffix:semicolon
multiline_comment|/* final stage */
r_void
id|snd_seq_queue_client_leave
c_func
(paren
r_int
id|client
)paren
suffix:semicolon
multiline_comment|/* enqueue a event received from one the clients */
r_int
id|snd_seq_enqueue_event
c_func
(paren
id|snd_seq_event_cell_t
op_star
id|cell
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
multiline_comment|/* Remove events */
r_void
id|snd_seq_queue_client_leave_cells
c_func
(paren
r_int
id|client
)paren
suffix:semicolon
r_void
id|snd_seq_queue_remove_cells
c_func
(paren
r_int
id|client
comma
id|snd_seq_remove_events_t
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* return pointer to queue structure for specified id */
id|queue_t
op_star
id|queueptr
c_func
(paren
r_int
id|queueid
)paren
suffix:semicolon
multiline_comment|/* unlock */
DECL|macro|queuefree
mdefine_line|#define queuefree(q) snd_use_lock_free(&amp;(q)-&gt;use_lock)
multiline_comment|/* return the (first) queue matching with the specified name */
id|queue_t
op_star
id|snd_seq_queue_find_name
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* check single queue and dispatch events */
r_void
id|snd_seq_check_queue
c_func
(paren
id|queue_t
op_star
id|q
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
multiline_comment|/* access to queue&squot;s parameters */
r_int
id|snd_seq_queue_check_access
c_func
(paren
r_int
id|queueid
comma
r_int
id|client
)paren
suffix:semicolon
r_int
id|snd_seq_queue_timer_set_tempo
c_func
(paren
r_int
id|queueid
comma
r_int
id|client
comma
id|snd_seq_queue_tempo_t
op_star
id|info
)paren
suffix:semicolon
r_int
id|snd_seq_queue_set_owner
c_func
(paren
r_int
id|queueid
comma
r_int
id|client
comma
r_int
id|locked
)paren
suffix:semicolon
r_int
id|snd_seq_queue_set_locked
c_func
(paren
r_int
id|queueid
comma
r_int
id|client
comma
r_int
id|locked
)paren
suffix:semicolon
r_int
id|snd_seq_queue_timer_open
c_func
(paren
r_int
id|queueid
)paren
suffix:semicolon
r_int
id|snd_seq_queue_timer_close
c_func
(paren
r_int
id|queueid
)paren
suffix:semicolon
r_int
id|snd_seq_queue_use
c_func
(paren
r_int
id|queueid
comma
r_int
id|client
comma
r_int
id|use
)paren
suffix:semicolon
r_int
id|snd_seq_queue_is_used
c_func
(paren
r_int
id|queueid
comma
r_int
id|client
)paren
suffix:semicolon
r_int
id|snd_seq_control_queue
c_func
(paren
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
r_void
id|snd_seq_queue_process_event
c_func
(paren
id|queue_t
op_star
id|q
comma
id|snd_seq_event_t
op_star
id|ev
comma
r_int
id|from_timer_port
comma
r_int
id|atomic
comma
r_int
id|hop
)paren
suffix:semicolon
multiline_comment|/*&n; * 64bit division - for sync stuff..&n; */
macro_line|#if defined(i386) || defined(i486)
DECL|macro|udiv_qrnnd
mdefine_line|#define udiv_qrnnd(q, r, n1, n0, d) &bslash;&n;  __asm__ (&quot;divl %4&quot;&t;&t;&bslash;&n;&t;   : &quot;=a&quot; ((u32)(q)),&t;&bslash;&n;&t;     &quot;=d&quot; ((u32)(r))&t;&bslash;&n;&t;   : &quot;0&quot; ((u32)(n0)),&t;&bslash;&n;&t;     &quot;1&quot; ((u32)(n1)),&t;&bslash;&n;&t;     &quot;rm&quot; ((u32)(d)))
DECL|macro|u64_div
mdefine_line|#define u64_div(x,y,q) do {u32 __tmp; udiv_qrnnd(q, __tmp, (x)&gt;&gt;32, x, y);} while (0)
DECL|macro|u64_mod
mdefine_line|#define u64_mod(x,y,r) do {u32 __tmp; udiv_qrnnd(__tmp, q, (x)&gt;&gt;32, x, y);} while (0)
DECL|macro|u64_divmod
mdefine_line|#define u64_divmod(x,y,q,r) udiv_qrnnd(q, r, (x)&gt;&gt;32, x, y)
macro_line|#else
DECL|macro|u64_div
mdefine_line|#define u64_div(x,y,q)&t;((q) = (u32)((u64)(x) / (u64)(y)))
DECL|macro|u64_mod
mdefine_line|#define u64_mod(x,y,r)&t;((r) = (u32)((u64)(x) % (u64)(y)))
DECL|macro|u64_divmod
mdefine_line|#define u64_divmod(x,y,q,r) (u64_div(x,y,q), u64_mod(x,y,r))
macro_line|#endif
macro_line|#endif
eof
