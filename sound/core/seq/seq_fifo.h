multiline_comment|/*&n; *   ALSA sequencer FIFO&n; *   Copyright (c) 1998 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SND_SEQ_FIFO_H
DECL|macro|__SND_SEQ_FIFO_H
mdefine_line|#define __SND_SEQ_FIFO_H
macro_line|#include &quot;seq_memory.h&quot;
macro_line|#include &quot;seq_lock.h&quot;
multiline_comment|/* === FIFO === */
r_typedef
r_struct
(brace
DECL|member|pool
id|pool_t
op_star
id|pool
suffix:semicolon
multiline_comment|/* FIFO pool */
DECL|member|head
id|snd_seq_event_cell_t
op_star
id|head
suffix:semicolon
multiline_comment|/* pointer to head of fifo */
DECL|member|tail
id|snd_seq_event_cell_t
op_star
id|tail
suffix:semicolon
multiline_comment|/* pointer to tail of fifo */
DECL|member|cells
r_int
id|cells
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|use_lock
id|snd_use_lock_t
id|use_lock
suffix:semicolon
DECL|member|input_sleep
id|wait_queue_head_t
id|input_sleep
suffix:semicolon
DECL|member|overflow
id|atomic_t
id|overflow
suffix:semicolon
DECL|typedef|fifo_t
)brace
id|fifo_t
suffix:semicolon
multiline_comment|/* create new fifo (constructor) */
r_extern
id|fifo_t
op_star
id|snd_seq_fifo_new
c_func
(paren
r_int
id|poolsize
)paren
suffix:semicolon
multiline_comment|/* delete fifo (destructor) */
r_extern
r_void
id|snd_seq_fifo_delete
c_func
(paren
id|fifo_t
op_star
op_star
id|f
)paren
suffix:semicolon
multiline_comment|/* enqueue event to fifo */
r_extern
r_int
id|snd_seq_fifo_event_in
c_func
(paren
id|fifo_t
op_star
id|f
comma
id|snd_seq_event_t
op_star
id|event
)paren
suffix:semicolon
multiline_comment|/* lock fifo from release */
DECL|macro|snd_seq_fifo_lock
mdefine_line|#define snd_seq_fifo_lock(fifo)&t;&t;snd_use_lock_use(&amp;(fifo)-&gt;use_lock)
DECL|macro|snd_seq_fifo_unlock
mdefine_line|#define snd_seq_fifo_unlock(fifo)&t;snd_use_lock_free(&amp;(fifo)-&gt;use_lock)
multiline_comment|/* get a cell from fifo - fifo should be locked */
r_int
id|snd_seq_fifo_cell_out
c_func
(paren
id|fifo_t
op_star
id|f
comma
id|snd_seq_event_cell_t
op_star
op_star
id|cellp
comma
r_int
id|nonblock
)paren
suffix:semicolon
multiline_comment|/* free dequeued cell - fifo should be locked */
r_extern
r_void
id|snd_seq_fifo_cell_putback
c_func
(paren
id|fifo_t
op_star
id|f
comma
id|snd_seq_event_cell_t
op_star
id|cell
)paren
suffix:semicolon
multiline_comment|/* clean up queue */
r_extern
r_void
id|snd_seq_fifo_clear
c_func
(paren
id|fifo_t
op_star
id|f
)paren
suffix:semicolon
multiline_comment|/* polling */
r_extern
r_int
id|snd_seq_fifo_poll_wait
c_func
(paren
id|fifo_t
op_star
id|f
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
suffix:semicolon
multiline_comment|/* resize pool in fifo */
r_int
id|snd_seq_fifo_resize
c_func
(paren
id|fifo_t
op_star
id|f
comma
r_int
id|poolsize
)paren
suffix:semicolon
macro_line|#endif
eof
