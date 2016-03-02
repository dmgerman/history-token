multiline_comment|/*&n; *  ALSA sequencer Memory Manager&n; *  Copyright (c) 1998 by Frank van de Pol &lt;fvdpol@coil.demon.nl&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SND_SEQ_MEMORYMGR_H
DECL|macro|__SND_SEQ_MEMORYMGR_H
mdefine_line|#define __SND_SEQ_MEMORYMGR_H
macro_line|#include &lt;sound/seq_kernel.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
DECL|typedef|pool_t
r_typedef
r_struct
id|pool
id|pool_t
suffix:semicolon
multiline_comment|/* container for sequencer event (internal use) */
DECL|struct|snd_seq_event_cell_t
r_typedef
r_struct
id|snd_seq_event_cell_t
(brace
DECL|member|event
id|snd_seq_event_t
id|event
suffix:semicolon
DECL|member|pool
id|pool_t
op_star
id|pool
suffix:semicolon
multiline_comment|/* used pool */
DECL|member|next
r_struct
id|snd_seq_event_cell_t
op_star
id|next
suffix:semicolon
multiline_comment|/* next cell */
DECL|typedef|snd_seq_event_cell_t
)brace
id|snd_seq_event_cell_t
suffix:semicolon
multiline_comment|/* design note: the pool is a contigious block of memory, if we dynamicly&n;   want to add additional cells to the pool be better store this in another&n;   pool as we need to know the base address of the pool when releasing&n;   memory. */
DECL|struct|pool
r_struct
id|pool
(brace
DECL|member|ptr
id|snd_seq_event_cell_t
op_star
id|ptr
suffix:semicolon
multiline_comment|/* pointer to first event chunk */
DECL|member|free
id|snd_seq_event_cell_t
op_star
id|free
suffix:semicolon
multiline_comment|/* pointer to the head of the free list */
DECL|member|total_elements
r_int
id|total_elements
suffix:semicolon
multiline_comment|/* pool size actually allocated */
DECL|member|counter
id|atomic_t
id|counter
suffix:semicolon
multiline_comment|/* cells free */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* pool size to be allocated */
DECL|member|room
r_int
id|room
suffix:semicolon
multiline_comment|/* watermark for sleep/wakeup */
DECL|member|closing
r_int
id|closing
suffix:semicolon
multiline_comment|/* statistics */
DECL|member|max_used
r_int
id|max_used
suffix:semicolon
DECL|member|event_alloc_nopool
r_int
id|event_alloc_nopool
suffix:semicolon
DECL|member|event_alloc_failures
r_int
id|event_alloc_failures
suffix:semicolon
DECL|member|event_alloc_success
r_int
id|event_alloc_success
suffix:semicolon
multiline_comment|/* Write locking */
DECL|member|output_sleep
id|wait_queue_head_t
id|output_sleep
suffix:semicolon
multiline_comment|/* Pool lock */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|snd_seq_cell_free
c_func
(paren
id|snd_seq_event_cell_t
op_star
id|cell
)paren
suffix:semicolon
r_int
id|snd_seq_event_dup
c_func
(paren
id|pool_t
op_star
id|pool
comma
id|snd_seq_event_t
op_star
id|event
comma
id|snd_seq_event_cell_t
op_star
op_star
id|cellp
comma
r_int
id|nonblock
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
multiline_comment|/* return number of unused (free) cells */
DECL|function|snd_seq_unused_cells
r_static
r_inline
r_int
id|snd_seq_unused_cells
c_func
(paren
id|pool_t
op_star
id|pool
)paren
(brace
r_return
id|pool
ques
c_cond
id|pool-&gt;total_elements
op_minus
id|atomic_read
c_func
(paren
op_amp
id|pool-&gt;counter
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/* return total number of allocated cells */
DECL|function|snd_seq_total_cells
r_static
r_inline
r_int
id|snd_seq_total_cells
c_func
(paren
id|pool_t
op_star
id|pool
)paren
(brace
r_return
id|pool
ques
c_cond
id|pool-&gt;total_elements
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/* init pool - allocate events */
r_int
id|snd_seq_pool_init
c_func
(paren
id|pool_t
op_star
id|pool
)paren
suffix:semicolon
multiline_comment|/* done pool - free events */
r_int
id|snd_seq_pool_done
c_func
(paren
id|pool_t
op_star
id|pool
)paren
suffix:semicolon
multiline_comment|/* create pool */
id|pool_t
op_star
id|snd_seq_pool_new
c_func
(paren
r_int
id|poolsize
)paren
suffix:semicolon
multiline_comment|/* remove pool */
r_int
id|snd_seq_pool_delete
c_func
(paren
id|pool_t
op_star
op_star
id|pool
)paren
suffix:semicolon
multiline_comment|/* init memory */
r_int
id|snd_sequencer_memory_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* release event memory */
r_void
id|snd_sequencer_memory_done
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* polling */
r_int
id|snd_seq_pool_poll_wait
c_func
(paren
id|pool_t
op_star
id|pool
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
macro_line|#endif
eof
