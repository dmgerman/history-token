multiline_comment|/* drm_dma.c -- DMA IOCTL and function support -*- linux-c -*-&n; * Created: Fri Mar 19 14:30:16 1999 by faith@valinux.com&n; *&n; * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/* Gamma-specific code pulled from drm_dma.h:&n; */
DECL|function|clear_next_buffer
r_void
id|DRM
c_func
(paren
id|clear_next_buffer
)paren
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
id|dma-&gt;next_buffer
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;next_queue
op_logical_and
op_logical_neg
id|DRM_BUFCOUNT
c_func
(paren
op_amp
id|dma-&gt;next_queue-&gt;waitlist
)paren
)paren
(brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|dma-&gt;next_queue-&gt;flush_queue
)paren
suffix:semicolon
)brace
id|dma-&gt;next_queue
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|select_queue
r_int
id|DRM
c_func
(paren
id|select_queue
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_void
(paren
op_star
id|wrapper
)paren
(paren
r_int
r_int
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|candidate
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|j
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;No device&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;queuelist
op_logical_or
op_logical_neg
id|dev-&gt;queuelist
(braket
id|DRM_KERNEL_CONTEXT
)braket
)paren
(brace
multiline_comment|/* This only happens between the time the&n;&t;&t;&t;&t;   interrupt is initialized and the time&n;&t;&t;&t;&t;   the queues are initialized. */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Doing &quot;while locked&quot; DMA? */
r_if
c_cond
(paren
id|DRM_WAITCOUNT
c_func
(paren
id|dev
comma
id|DRM_KERNEL_CONTEXT
)paren
)paren
(brace
r_return
id|DRM_KERNEL_CONTEXT
suffix:semicolon
)brace
multiline_comment|/* If there are buffers on the last_context&n;&t;&t;&t;&t;   queue, and we have not been executing&n;&t;&t;&t;&t;   this context very long, continue to&n;&t;&t;&t;&t;   execute this context. */
r_if
c_cond
(paren
id|dev-&gt;last_switch
op_le
id|j
op_logical_and
id|dev-&gt;last_switch
op_plus
id|DRM_TIME_SLICE
OG
id|j
op_logical_and
id|DRM_WAITCOUNT
c_func
(paren
id|dev
comma
id|dev-&gt;last_context
)paren
)paren
(brace
r_return
id|dev-&gt;last_context
suffix:semicolon
)brace
multiline_comment|/* Otherwise, find a candidate */
r_for
c_loop
(paren
id|i
op_assign
id|dev-&gt;last_checked
op_plus
l_int|1
suffix:semicolon
id|i
OL
id|dev-&gt;queue_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|DRM_WAITCOUNT
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
id|candidate
op_assign
id|dev-&gt;last_checked
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|candidate
OL
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dev-&gt;queue_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|DRM_WAITCOUNT
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
id|candidate
op_assign
id|dev-&gt;last_checked
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|wrapper
op_logical_and
id|candidate
op_ge
l_int|0
op_logical_and
id|candidate
op_ne
id|dev-&gt;last_context
op_logical_and
id|dev-&gt;last_switch
op_le
id|j
op_logical_and
id|dev-&gt;last_switch
op_plus
id|DRM_TIME_SLICE
OG
id|j
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;timer.expires
op_ne
id|dev-&gt;last_switch
op_plus
id|DRM_TIME_SLICE
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|dev-&gt;timer
)paren
suffix:semicolon
id|dev-&gt;timer.function
op_assign
id|wrapper
suffix:semicolon
id|dev-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|dev
suffix:semicolon
id|dev-&gt;timer.expires
op_assign
id|dev-&gt;last_switch
op_plus
id|DRM_TIME_SLICE
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|dev-&gt;timer
)paren
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|candidate
suffix:semicolon
)brace
DECL|function|dma_enqueue
r_int
id|DRM
c_func
(paren
id|dma_enqueue
)paren
(paren
r_struct
id|file
op_star
id|filp
comma
id|drm_dma_t
op_star
id|d
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
r_int
id|i
suffix:semicolon
id|drm_queue_t
op_star
id|q
suffix:semicolon
id|drm_buf_t
op_star
id|buf
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_int
id|while_locked
op_assign
l_int|0
suffix:semicolon
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
r_int
op_star
id|ind
suffix:semicolon
r_int
id|err
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|entry
comma
id|current
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|d-&gt;send_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;flags
op_amp
id|_DRM_DMA_WHILE_LOCKED
)paren
(brace
r_int
id|context
op_assign
id|dev-&gt;lock.hw_lock-&gt;lock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|_DRM_LOCK_IS_HELD
c_func
(paren
id|context
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;No lock held during &bslash;&quot;while locked&bslash;&quot;&quot;
l_string|&quot; request&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d-&gt;context
op_ne
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|context
)paren
op_logical_and
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|context
)paren
op_ne
id|DRM_KERNEL_CONTEXT
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Lock held by %d while %d makes&quot;
l_string|&quot; &bslash;&quot;while locked&bslash;&quot; request&bslash;n&quot;
comma
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|context
)paren
comma
id|d-&gt;context
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|q
op_assign
id|dev-&gt;queuelist
(braket
id|DRM_KERNEL_CONTEXT
)braket
suffix:semicolon
id|while_locked
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|q
op_assign
id|dev-&gt;queuelist
(braket
id|d-&gt;context
)braket
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|q-&gt;use_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|q-&gt;block_write
)paren
)paren
(brace
id|add_wait_queue
c_func
(paren
op_amp
id|q-&gt;write_queue
comma
op_amp
id|entry
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|q-&gt;block_count
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|q-&gt;block_write
)paren
)paren
r_break
suffix:semicolon
id|schedule
c_func
(paren
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
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;use_count
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|q-&gt;write_queue
comma
op_amp
id|entry
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;block_count
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|q-&gt;write_queue
comma
op_amp
id|entry
)paren
suffix:semicolon
)brace
id|ind
op_assign
id|DRM
c_func
(paren
id|alloc
)paren
(paren
id|d-&gt;send_count
op_star
r_sizeof
(paren
r_int
)paren
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ind
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|ind
comma
id|d-&gt;send_indices
comma
id|d-&gt;send_count
op_star
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|d-&gt;send_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|idx
op_assign
id|ind
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
op_logical_or
id|idx
op_ge
id|dma-&gt;buf_count
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Index %d (of %d max)&bslash;n&quot;
comma
id|ind
(braket
id|i
)braket
comma
id|dma-&gt;buf_count
op_minus
l_int|1
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|buf
op_assign
id|dma-&gt;buflist
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;filp
op_ne
id|filp
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Process %d using buffer not owned&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buf-&gt;list
op_ne
id|DRM_LIST_NONE
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Process %d using buffer %d on list %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|buf-&gt;idx
comma
id|buf-&gt;list
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|buf-&gt;used
op_assign
id|ind
(braket
id|i
)braket
suffix:semicolon
id|buf-&gt;while_locked
op_assign
id|while_locked
suffix:semicolon
id|buf-&gt;context
op_assign
id|d-&gt;context
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf-&gt;used
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Queueing 0 length buffer&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buf-&gt;pending
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Queueing pending buffer:&quot;
l_string|&quot; buffer %d, offset %d&bslash;n&quot;
comma
id|ind
(braket
id|i
)braket
comma
id|i
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buf-&gt;waiting
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Queueing waiting buffer:&quot;
l_string|&quot; buffer %d, offset %d&bslash;n&quot;
comma
id|ind
(braket
id|i
)braket
comma
id|i
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|buf-&gt;waiting
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|q-&gt;use_count
)paren
op_eq
l_int|1
op_logical_or
id|atomic_read
c_func
(paren
op_amp
id|q-&gt;finalization
)paren
)paren
(brace
id|DRM
c_func
(paren
id|free_buffer
)paren
(paren
id|dev
comma
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
id|DRM
c_func
(paren
id|waitlist_put
)paren
(paren
op_amp
id|q-&gt;waitlist
comma
id|buf
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|q-&gt;total_queued
)paren
suffix:semicolon
)brace
)brace
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;use_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|DRM
c_func
(paren
id|free
)paren
(paren
id|ind
comma
id|d-&gt;send_count
op_star
r_sizeof
(paren
r_int
)paren
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;use_count
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|dma_get_buffers_of_order
r_static
r_int
id|DRM
c_func
(paren
id|dma_get_buffers_of_order
)paren
(paren
r_struct
id|file
op_star
id|filp
comma
id|drm_dma_t
op_star
id|d
comma
r_int
id|order
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
r_int
id|i
suffix:semicolon
id|drm_buf_t
op_star
id|buf
suffix:semicolon
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|d-&gt;granted_count
suffix:semicolon
id|i
OL
id|d-&gt;request_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|buf
op_assign
id|DRM
c_func
(paren
id|freelist_get
)paren
(paren
op_amp
id|dma-&gt;bufs
(braket
id|order
)braket
dot
id|freelist
comma
id|d-&gt;flags
op_amp
id|_DRM_DMA_WAIT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;pending
op_logical_or
id|buf-&gt;waiting
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Free buffer %d in use: filp %p (w%d, p%d)&bslash;n&quot;
comma
id|buf-&gt;idx
comma
id|buf-&gt;filp
comma
id|buf-&gt;waiting
comma
id|buf-&gt;pending
)paren
suffix:semicolon
)brace
id|buf-&gt;filp
op_assign
id|filp
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
id|d-&gt;request_indices
(braket
id|i
)braket
comma
op_amp
id|buf-&gt;idx
comma
r_sizeof
(paren
id|buf-&gt;idx
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
id|copy_to_user
c_func
(paren
op_amp
id|d-&gt;request_sizes
(braket
id|i
)braket
comma
op_amp
id|buf-&gt;total
comma
r_sizeof
(paren
id|buf-&gt;total
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_increment
id|d-&gt;granted_count
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dma_get_buffers
r_int
id|DRM
c_func
(paren
id|dma_get_buffers
)paren
(paren
r_struct
id|file
op_star
id|filp
comma
id|drm_dma_t
op_star
id|dma
)paren
(brace
r_int
id|order
suffix:semicolon
r_int
id|retcode
op_assign
l_int|0
suffix:semicolon
r_int
id|tmp_order
suffix:semicolon
id|order
op_assign
id|DRM
c_func
(paren
id|order
)paren
(paren
id|dma-&gt;request_size
)paren
suffix:semicolon
id|dma-&gt;granted_count
op_assign
l_int|0
suffix:semicolon
id|retcode
op_assign
id|DRM
c_func
(paren
id|dma_get_buffers_of_order
)paren
(paren
id|filp
comma
id|dma
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;granted_count
OL
id|dma-&gt;request_count
op_logical_and
(paren
id|dma-&gt;flags
op_amp
id|_DRM_DMA_SMALLER_OK
)paren
)paren
(brace
r_for
c_loop
(paren
id|tmp_order
op_assign
id|order
op_minus
l_int|1
suffix:semicolon
op_logical_neg
id|retcode
op_logical_and
id|dma-&gt;granted_count
OL
id|dma-&gt;request_count
op_logical_and
id|tmp_order
op_ge
id|DRM_MIN_ORDER
suffix:semicolon
op_decrement
id|tmp_order
)paren
(brace
id|retcode
op_assign
id|DRM
c_func
(paren
id|dma_get_buffers_of_order
)paren
(paren
id|filp
comma
id|dma
comma
id|tmp_order
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dma-&gt;granted_count
OL
id|dma-&gt;request_count
op_logical_and
(paren
id|dma-&gt;flags
op_amp
id|_DRM_DMA_LARGER_OK
)paren
)paren
(brace
r_for
c_loop
(paren
id|tmp_order
op_assign
id|order
op_plus
l_int|1
suffix:semicolon
op_logical_neg
id|retcode
op_logical_and
id|dma-&gt;granted_count
OL
id|dma-&gt;request_count
op_logical_and
id|tmp_order
op_le
id|DRM_MAX_ORDER
suffix:semicolon
op_increment
id|tmp_order
)paren
(brace
id|retcode
op_assign
id|DRM
c_func
(paren
id|dma_get_buffers_of_order
)paren
(paren
id|filp
comma
id|dma
comma
id|tmp_order
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
