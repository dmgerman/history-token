multiline_comment|/*&n; *   ALSA sequencer Priority Queue&n; *   Copyright (c) 1998 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SND_SEQ_PRIOQ_H
DECL|macro|__SND_SEQ_PRIOQ_H
mdefine_line|#define __SND_SEQ_PRIOQ_H
macro_line|#include &quot;seq_memory.h&quot;
multiline_comment|/* === PRIOQ === */
r_typedef
r_struct
(brace
DECL|member|head
id|snd_seq_event_cell_t
op_star
id|head
suffix:semicolon
multiline_comment|/* pointer to head of prioq */
DECL|member|tail
id|snd_seq_event_cell_t
op_star
id|tail
suffix:semicolon
multiline_comment|/* pointer to tail of prioq */
DECL|member|cells
r_int
id|cells
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|typedef|prioq_t
)brace
id|prioq_t
suffix:semicolon
multiline_comment|/* create new prioq (constructor) */
r_extern
id|prioq_t
op_star
id|snd_seq_prioq_new
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* delete prioq (destructor) */
r_extern
r_void
id|snd_seq_prioq_delete
c_func
(paren
id|prioq_t
op_star
op_star
id|fifo
)paren
suffix:semicolon
multiline_comment|/* enqueue cell to prioq */
r_extern
r_void
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
suffix:semicolon
multiline_comment|/* dequeue cell from prioq */
r_extern
id|snd_seq_event_cell_t
op_star
id|snd_seq_prioq_cell_out
c_func
(paren
id|prioq_t
op_star
id|f
)paren
suffix:semicolon
multiline_comment|/* return number of events available in prioq */
r_extern
r_int
id|snd_seq_prioq_avail
c_func
(paren
id|prioq_t
op_star
id|f
)paren
suffix:semicolon
multiline_comment|/* peek at cell at the head of the prioq */
r_extern
id|snd_seq_event_cell_t
op_star
id|snd_seq_prioq_cell_peek
c_func
(paren
id|prioq_t
op_star
id|f
)paren
suffix:semicolon
multiline_comment|/* client left queue */
r_extern
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
suffix:semicolon
multiline_comment|/* Remove events */
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
suffix:semicolon
macro_line|#endif
eof
