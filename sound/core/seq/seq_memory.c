multiline_comment|/*&n; *  ALSA sequencer Memory Manager&n; *  Copyright (c) 1998 by Frank van de Pol &lt;fvdpol@coil.demon.nl&gt;&n; *                        Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *                2000 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/seq_kernel.h&gt;
macro_line|#include &quot;seq_memory.h&quot;
macro_line|#include &quot;seq_queue.h&quot;
macro_line|#include &quot;seq_info.h&quot;
macro_line|#include &quot;seq_lock.h&quot;
multiline_comment|/* semaphore in struct file record */
DECL|macro|semaphore_of
mdefine_line|#define semaphore_of(fp)&t;((fp)-&gt;f_dentry-&gt;d_inode-&gt;i_sem)
DECL|function|snd_seq_pool_available
r_inline
r_static
r_int
id|snd_seq_pool_available
c_func
(paren
id|pool_t
op_star
id|pool
)paren
(brace
r_return
id|pool-&gt;total_elements
op_minus
id|atomic_read
c_func
(paren
op_amp
id|pool-&gt;counter
)paren
suffix:semicolon
)brace
DECL|function|snd_seq_output_ok
r_inline
r_static
r_int
id|snd_seq_output_ok
c_func
(paren
id|pool_t
op_star
id|pool
)paren
(brace
r_return
id|snd_seq_pool_available
c_func
(paren
id|pool
)paren
op_ge
id|pool-&gt;room
suffix:semicolon
)brace
multiline_comment|/*&n; * Variable length event:&n; * The event like sysex uses variable length type.&n; * The external data may be stored in three different formats.&n; * 1) kernel space&n; *    This is the normal case.&n; *      ext.data.len = length&n; *      ext.data.ptr = buffer pointer&n; * 2) user space&n; *    When an event is generated via read(), the external data is&n; *    kept in user space until expanded.&n; *      ext.data.len = length | SNDRV_SEQ_EXT_USRPTR&n; *      ext.data.ptr = userspace pointer&n; * 3) chained cells&n; *    When the variable length event is enqueued (in prioq or fifo),&n; *    the external data is decomposed to several cells.&n; *      ext.data.len = length | SNDRV_SEQ_EXT_CHAINED&n; *      ext.data.ptr = the additiona cell head&n; *         -&gt; cell.next -&gt; cell.next -&gt; ..&n; */
multiline_comment|/*&n; * exported:&n; * call dump function to expand external data.&n; */
DECL|function|get_var_len
r_static
r_int
id|get_var_len
c_func
(paren
r_const
id|snd_seq_event_t
op_star
id|event
)paren
(brace
r_if
c_cond
(paren
(paren
id|event-&gt;flags
op_amp
id|SNDRV_SEQ_EVENT_LENGTH_MASK
)paren
op_ne
id|SNDRV_SEQ_EVENT_LENGTH_VARIABLE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|event-&gt;data.ext.len
op_amp
op_complement
id|SNDRV_SEQ_EXT_MASK
suffix:semicolon
)brace
DECL|function|snd_seq_dump_var_event
r_int
id|snd_seq_dump_var_event
c_func
(paren
r_const
id|snd_seq_event_t
op_star
id|event
comma
id|snd_seq_dump_func_t
id|func
comma
r_void
op_star
id|private_data
)paren
(brace
r_int
id|len
comma
id|err
suffix:semicolon
id|snd_seq_event_cell_t
op_star
id|cell
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_assign
id|get_var_len
c_func
(paren
id|event
)paren
)paren
op_le
l_int|0
)paren
r_return
id|len
suffix:semicolon
r_if
c_cond
(paren
id|event-&gt;data.ext.len
op_amp
id|SNDRV_SEQ_EXT_USRPTR
)paren
(brace
r_char
id|buf
(braket
l_int|32
)braket
suffix:semicolon
r_char
id|__user
op_star
id|curptr
op_assign
(paren
r_char
id|__user
op_star
)paren
id|event-&gt;data.ext.ptr
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_int
id|size
op_assign
r_sizeof
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|size
)paren
id|size
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|curptr
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|func
c_func
(paren
id|private_data
comma
id|buf
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|curptr
op_add_assign
id|size
suffix:semicolon
id|len
op_sub_assign
id|size
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|event-&gt;data.ext.len
op_amp
id|SNDRV_SEQ_EXT_CHAINED
)paren
)paren
(brace
r_return
id|func
c_func
(paren
id|private_data
comma
id|event-&gt;data.ext.ptr
comma
id|len
)paren
suffix:semicolon
)brace
id|cell
op_assign
(paren
id|snd_seq_event_cell_t
op_star
)paren
id|event-&gt;data.ext.ptr
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|len
OG
l_int|0
op_logical_and
id|cell
suffix:semicolon
id|cell
op_assign
id|cell-&gt;next
)paren
(brace
r_int
id|size
op_assign
r_sizeof
(paren
id|snd_seq_event_t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|size
)paren
id|size
op_assign
id|len
suffix:semicolon
id|err
op_assign
id|func
c_func
(paren
id|private_data
comma
op_amp
id|cell-&gt;event
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|len
op_sub_assign
id|size
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * exported:&n; * expand the variable length event to linear buffer space.&n; */
DECL|function|seq_copy_in_kernel
r_static
r_int
id|seq_copy_in_kernel
c_func
(paren
r_char
op_star
op_star
id|bufptr
comma
r_const
r_void
op_star
id|src
comma
r_int
id|size
)paren
(brace
id|memcpy
c_func
(paren
op_star
id|bufptr
comma
id|src
comma
id|size
)paren
suffix:semicolon
op_star
id|bufptr
op_add_assign
id|size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|seq_copy_in_user
r_static
r_int
id|seq_copy_in_user
c_func
(paren
r_char
id|__user
op_star
op_star
id|bufptr
comma
r_const
r_void
op_star
id|src
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_star
id|bufptr
comma
id|src
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|bufptr
op_add_assign
id|size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_seq_expand_var_event
r_int
id|snd_seq_expand_var_event
c_func
(paren
r_const
id|snd_seq_event_t
op_star
id|event
comma
r_int
id|count
comma
r_char
op_star
id|buf
comma
r_int
id|in_kernel
comma
r_int
id|size_aligned
)paren
(brace
r_int
id|len
comma
id|newlen
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_assign
id|get_var_len
c_func
(paren
id|event
)paren
)paren
OL
l_int|0
)paren
r_return
id|len
suffix:semicolon
id|newlen
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|size_aligned
OG
l_int|0
)paren
id|newlen
op_assign
(paren
(paren
id|len
op_plus
id|size_aligned
op_minus
l_int|1
)paren
op_div
id|size_aligned
)paren
op_star
id|size_aligned
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|newlen
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|event-&gt;data.ext.len
op_amp
id|SNDRV_SEQ_EXT_USRPTR
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|in_kernel
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
(paren
r_void
id|__user
op_star
)paren
id|event-&gt;data.ext.ptr
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|newlen
suffix:semicolon
)brace
id|err
op_assign
id|snd_seq_dump_var_event
c_func
(paren
id|event
comma
id|in_kernel
ques
c_cond
(paren
id|snd_seq_dump_func_t
)paren
id|seq_copy_in_kernel
suffix:colon
(paren
id|snd_seq_dump_func_t
)paren
id|seq_copy_in_user
comma
op_amp
id|buf
)paren
suffix:semicolon
r_return
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
id|newlen
suffix:semicolon
)brace
multiline_comment|/*&n; * release this cell, free extended data if available&n; */
DECL|function|free_cell
r_static
r_inline
r_void
id|free_cell
c_func
(paren
id|pool_t
op_star
id|pool
comma
id|snd_seq_event_cell_t
op_star
id|cell
)paren
(brace
id|cell-&gt;next
op_assign
id|pool-&gt;free
suffix:semicolon
id|pool-&gt;free
op_assign
id|cell
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|pool-&gt;counter
)paren
suffix:semicolon
)brace
DECL|function|snd_seq_cell_free
r_void
id|snd_seq_cell_free
c_func
(paren
id|snd_seq_event_cell_t
op_star
id|cell
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|pool_t
op_star
id|pool
suffix:semicolon
id|snd_assert
c_func
(paren
id|cell
op_ne
l_int|NULL
comma
r_return
)paren
suffix:semicolon
id|pool
op_assign
id|cell-&gt;pool
suffix:semicolon
id|snd_assert
c_func
(paren
id|pool
op_ne
l_int|NULL
comma
r_return
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|free_cell
c_func
(paren
id|pool
comma
id|cell
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_ev_is_variable
c_func
(paren
op_amp
id|cell-&gt;event
)paren
)paren
(brace
r_if
c_cond
(paren
id|cell-&gt;event.data.ext.len
op_amp
id|SNDRV_SEQ_EXT_CHAINED
)paren
(brace
id|snd_seq_event_cell_t
op_star
id|curp
comma
op_star
id|nextptr
suffix:semicolon
id|curp
op_assign
id|cell-&gt;event.data.ext.ptr
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|curp
suffix:semicolon
id|curp
op_assign
id|nextptr
)paren
(brace
id|nextptr
op_assign
id|curp-&gt;next
suffix:semicolon
id|curp-&gt;next
op_assign
id|pool-&gt;free
suffix:semicolon
id|free_cell
c_func
(paren
id|pool
comma
id|curp
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|pool-&gt;output_sleep
)paren
)paren
(brace
multiline_comment|/* has enough space now? */
r_if
c_cond
(paren
id|snd_seq_output_ok
c_func
(paren
id|pool
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|pool-&gt;output_sleep
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * allocate an event cell.&n; */
DECL|function|snd_seq_cell_alloc
r_static
r_int
id|snd_seq_cell_alloc
c_func
(paren
id|pool_t
op_star
id|pool
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
(brace
id|snd_seq_event_cell_t
op_star
id|cell
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EAGAIN
suffix:semicolon
id|wait_queue_t
id|wait
suffix:semicolon
r_if
c_cond
(paren
id|pool
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|cellp
op_assign
l_int|NULL
suffix:semicolon
id|init_waitqueue_entry
c_func
(paren
op_amp
id|wait
comma
id|current
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pool-&gt;ptr
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* not initialized */
id|snd_printd
c_func
(paren
l_string|&quot;seq: pool is not initialized&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|__error
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pool-&gt;free
op_eq
l_int|NULL
op_logical_and
op_logical_neg
id|nonblock
op_logical_and
op_logical_neg
id|pool-&gt;closing
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|pool-&gt;output_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|pool-&gt;lock
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|pool-&gt;lock
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|pool-&gt;output_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/* interrupted? */
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
id|err
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_goto
id|__error
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|pool-&gt;closing
)paren
(brace
multiline_comment|/* closing.. */
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|__error
suffix:semicolon
)brace
id|cell
op_assign
id|pool-&gt;free
suffix:semicolon
r_if
c_cond
(paren
id|cell
)paren
(brace
r_int
id|used
suffix:semicolon
id|pool-&gt;free
op_assign
id|cell-&gt;next
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|pool-&gt;counter
)paren
suffix:semicolon
id|used
op_assign
id|atomic_read
c_func
(paren
op_amp
id|pool-&gt;counter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pool-&gt;max_used
OL
id|used
)paren
id|pool-&gt;max_used
op_assign
id|used
suffix:semicolon
id|pool-&gt;event_alloc_success
op_increment
suffix:semicolon
multiline_comment|/* clear cell pointers */
id|cell-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|pool-&gt;event_alloc_failures
op_increment
suffix:semicolon
op_star
id|cellp
op_assign
id|cell
suffix:semicolon
id|__error
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * duplicate the event to a cell.&n; * if the event has external data, the data is decomposed to additional&n; * cells.&n; */
DECL|function|snd_seq_event_dup
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
(brace
r_int
id|ncells
comma
id|err
suffix:semicolon
r_int
r_int
id|extlen
suffix:semicolon
id|snd_seq_event_cell_t
op_star
id|cell
suffix:semicolon
op_star
id|cellp
op_assign
l_int|NULL
suffix:semicolon
id|ncells
op_assign
l_int|0
suffix:semicolon
id|extlen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|snd_seq_ev_is_variable
c_func
(paren
id|event
)paren
)paren
(brace
id|extlen
op_assign
id|event-&gt;data.ext.len
op_amp
op_complement
id|SNDRV_SEQ_EXT_MASK
suffix:semicolon
id|ncells
op_assign
(paren
id|extlen
op_plus
r_sizeof
(paren
id|snd_seq_event_t
)paren
op_minus
l_int|1
)paren
op_div
r_sizeof
(paren
id|snd_seq_event_t
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ncells
op_ge
id|pool-&gt;total_elements
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|err
op_assign
id|snd_seq_cell_alloc
c_func
(paren
id|pool
comma
op_amp
id|cell
comma
id|nonblock
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* copy the event */
id|cell-&gt;event
op_assign
op_star
id|event
suffix:semicolon
multiline_comment|/* decompose */
r_if
c_cond
(paren
id|snd_seq_ev_is_variable
c_func
(paren
id|event
)paren
)paren
(brace
r_int
id|len
op_assign
id|extlen
suffix:semicolon
r_int
id|is_chained
op_assign
id|event-&gt;data.ext.len
op_amp
id|SNDRV_SEQ_EXT_CHAINED
suffix:semicolon
r_int
id|is_usrptr
op_assign
id|event-&gt;data.ext.len
op_amp
id|SNDRV_SEQ_EXT_USRPTR
suffix:semicolon
id|snd_seq_event_cell_t
op_star
id|src
comma
op_star
id|tmp
comma
op_star
id|tail
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
id|cell-&gt;event.data.ext.len
op_assign
id|extlen
op_or
id|SNDRV_SEQ_EXT_CHAINED
suffix:semicolon
id|cell-&gt;event.data.ext.ptr
op_assign
l_int|NULL
suffix:semicolon
id|src
op_assign
(paren
id|snd_seq_event_cell_t
op_star
)paren
id|event-&gt;data.ext.ptr
suffix:semicolon
id|buf
op_assign
(paren
r_char
op_star
)paren
id|event-&gt;data.ext.ptr
suffix:semicolon
id|tail
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|ncells
op_decrement
OG
l_int|0
)paren
(brace
r_int
id|size
op_assign
r_sizeof
(paren
id|snd_seq_event_t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|size
)paren
id|size
op_assign
id|len
suffix:semicolon
id|err
op_assign
id|snd_seq_cell_alloc
c_func
(paren
id|pool
comma
op_amp
id|tmp
comma
id|nonblock
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|__error
suffix:semicolon
r_if
c_cond
(paren
id|cell-&gt;event.data.ext.ptr
op_eq
l_int|NULL
)paren
id|cell-&gt;event.data.ext.ptr
op_assign
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|tail
)paren
id|tail-&gt;next
op_assign
id|tmp
suffix:semicolon
id|tail
op_assign
id|tmp
suffix:semicolon
multiline_comment|/* copy chunk */
r_if
c_cond
(paren
id|is_chained
op_logical_and
id|src
)paren
(brace
id|tmp-&gt;event
op_assign
id|src-&gt;event
suffix:semicolon
id|src
op_assign
id|src-&gt;next
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_usrptr
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tmp-&gt;event
comma
(paren
r_char
id|__user
op_star
)paren
id|buf
comma
id|size
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|__error
suffix:semicolon
)brace
)brace
r_else
(brace
id|memcpy
c_func
(paren
op_amp
id|tmp-&gt;event
comma
id|buf
comma
id|size
)paren
suffix:semicolon
)brace
id|buf
op_add_assign
id|size
suffix:semicolon
id|len
op_sub_assign
id|size
suffix:semicolon
)brace
)brace
op_star
id|cellp
op_assign
id|cell
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|__error
suffix:colon
id|snd_seq_cell_free
c_func
(paren
id|cell
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* poll wait */
DECL|function|snd_seq_pool_poll_wait
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
(brace
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|pool-&gt;output_sleep
comma
id|wait
)paren
suffix:semicolon
r_return
id|snd_seq_output_ok
c_func
(paren
id|pool
)paren
suffix:semicolon
)brace
multiline_comment|/* allocate room specified number of events */
DECL|function|snd_seq_pool_init
r_int
id|snd_seq_pool_init
c_func
(paren
id|pool_t
op_star
id|pool
)paren
(brace
r_int
id|cell
suffix:semicolon
id|snd_seq_event_cell_t
op_star
id|cellptr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|snd_assert
c_func
(paren
id|pool
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pool-&gt;ptr
)paren
multiline_comment|/* should be atomic? */
r_return
l_int|0
suffix:semicolon
id|pool-&gt;ptr
op_assign
id|vmalloc
c_func
(paren
r_sizeof
(paren
id|snd_seq_event_cell_t
)paren
op_star
id|pool-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pool-&gt;ptr
op_eq
l_int|NULL
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;seq: malloc for sequencer events failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* add new cells to the free cell list */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|pool-&gt;free
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|cell
op_assign
l_int|0
suffix:semicolon
id|cell
OL
id|pool-&gt;size
suffix:semicolon
id|cell
op_increment
)paren
(brace
id|cellptr
op_assign
id|pool-&gt;ptr
op_plus
id|cell
suffix:semicolon
id|cellptr-&gt;pool
op_assign
id|pool
suffix:semicolon
id|cellptr-&gt;next
op_assign
id|pool-&gt;free
suffix:semicolon
id|pool-&gt;free
op_assign
id|cellptr
suffix:semicolon
)brace
id|pool-&gt;room
op_assign
(paren
id|pool-&gt;size
op_plus
l_int|1
)paren
op_div
l_int|2
suffix:semicolon
multiline_comment|/* init statistics */
id|pool-&gt;max_used
op_assign
l_int|0
suffix:semicolon
id|pool-&gt;total_elements
op_assign
id|pool-&gt;size
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* remove events */
DECL|function|snd_seq_pool_done
r_int
id|snd_seq_pool_done
c_func
(paren
id|pool_t
op_star
id|pool
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|snd_seq_event_cell_t
op_star
id|ptr
suffix:semicolon
r_int
id|max_count
op_assign
l_int|5
op_star
id|HZ
suffix:semicolon
id|snd_assert
c_func
(paren
id|pool
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* wait for closing all threads */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|pool-&gt;closing
op_assign
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|pool-&gt;output_sleep
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|pool-&gt;output_sleep
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|pool-&gt;counter
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|max_count
op_eq
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;snd_seq_pool_done timeout: %d cells remain&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|pool-&gt;counter
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|max_count
op_decrement
suffix:semicolon
)brace
multiline_comment|/* release all resources */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|ptr
op_assign
id|pool-&gt;ptr
suffix:semicolon
id|pool-&gt;ptr
op_assign
l_int|NULL
suffix:semicolon
id|pool-&gt;free
op_assign
l_int|NULL
suffix:semicolon
id|pool-&gt;total_elements
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|pool-&gt;closing
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* init new memory pool */
DECL|function|snd_seq_pool_new
id|pool_t
op_star
id|snd_seq_pool_new
c_func
(paren
r_int
id|poolsize
)paren
(brace
id|pool_t
op_star
id|pool
suffix:semicolon
multiline_comment|/* create pool block */
id|pool
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|pool
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pool
op_eq
l_int|NULL
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;seq: malloc failed for pool&bslash;n&quot;
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
id|pool-&gt;lock
)paren
suffix:semicolon
id|pool-&gt;ptr
op_assign
l_int|NULL
suffix:semicolon
id|pool-&gt;free
op_assign
l_int|NULL
suffix:semicolon
id|pool-&gt;total_elements
op_assign
l_int|0
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|pool-&gt;counter
comma
l_int|0
)paren
suffix:semicolon
id|pool-&gt;closing
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|pool-&gt;output_sleep
)paren
suffix:semicolon
id|pool-&gt;size
op_assign
id|poolsize
suffix:semicolon
multiline_comment|/* init statistics */
id|pool-&gt;max_used
op_assign
l_int|0
suffix:semicolon
r_return
id|pool
suffix:semicolon
)brace
multiline_comment|/* remove memory pool */
DECL|function|snd_seq_pool_delete
r_int
id|snd_seq_pool_delete
c_func
(paren
id|pool_t
op_star
op_star
id|ppool
)paren
(brace
id|pool_t
op_star
id|pool
op_assign
op_star
id|ppool
suffix:semicolon
op_star
id|ppool
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|pool
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|snd_seq_pool_done
c_func
(paren
id|pool
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pool
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* initialize sequencer memory */
DECL|function|snd_sequencer_memory_init
r_int
id|__init
id|snd_sequencer_memory_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* release sequencer memory */
DECL|function|snd_sequencer_memory_done
r_void
id|__exit
id|snd_sequencer_memory_done
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* exported to seq_clientmgr.c */
DECL|function|snd_seq_info_pool
r_void
id|snd_seq_info_pool
c_func
(paren
id|snd_info_buffer_t
op_star
id|buffer
comma
id|pool_t
op_star
id|pool
comma
r_char
op_star
id|space
)paren
(brace
r_if
c_cond
(paren
id|pool
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%sPool size          : %d&bslash;n&quot;
comma
id|space
comma
id|pool-&gt;total_elements
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%sCells in use       : %d&bslash;n&quot;
comma
id|space
comma
id|atomic_read
c_func
(paren
op_amp
id|pool-&gt;counter
)paren
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%sPeak cells in use  : %d&bslash;n&quot;
comma
id|space
comma
id|pool-&gt;max_used
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%sAlloc success      : %d&bslash;n&quot;
comma
id|space
comma
id|pool-&gt;event_alloc_success
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%sAlloc failures     : %d&bslash;n&quot;
comma
id|space
comma
id|pool-&gt;event_alloc_failures
)paren
suffix:semicolon
)brace
eof
