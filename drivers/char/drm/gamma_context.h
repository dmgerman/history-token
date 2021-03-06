multiline_comment|/* drm_context.h -- IOCTLs for generic contexts -*- linux-c -*-&n; * Created: Fri Nov 24 18:31:37 2000 by gareth@valinux.com&n; *&n; * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; * ChangeLog:&n; *  2001-11-16&t;Torsten Duwe &lt;duwe@caldera.de&gt;&n; *&t;&t;added context constructor/destructor hooks,&n; *&t;&t;needed by SiS driver&squot;s memory management.&n; */
multiline_comment|/* ================================================================&n; * Old-style context support -- only used by gamma.  &n; */
multiline_comment|/* The drm_read and drm_write_string code (especially that which manages&n;   the circular buffer), is based on Alessandro Rubini&squot;s LINUX DEVICE&n;   DRIVERS (Cambridge: O&squot;Reilly, 1998), pages 111-113. */
DECL|function|gamma_fops_read
id|ssize_t
id|gamma_fops_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
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
id|left
suffix:semicolon
r_int
id|avail
suffix:semicolon
r_int
id|send
suffix:semicolon
r_int
id|cur
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%p, %p&bslash;n&quot;
comma
id|dev-&gt;buf_rp
comma
id|dev-&gt;buf_wp
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;buf_rp
op_eq
id|dev-&gt;buf_wp
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;  sleeping&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|dev-&gt;buf_readers
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
id|DRM_DEBUG
c_func
(paren
l_string|&quot;  interrupted&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;  awake&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|left
op_assign
(paren
id|dev-&gt;buf_rp
op_plus
id|DRM_BSZ
op_minus
id|dev-&gt;buf_wp
)paren
op_mod
id|DRM_BSZ
suffix:semicolon
id|avail
op_assign
id|DRM_BSZ
op_minus
id|left
suffix:semicolon
id|send
op_assign
id|DRM_MIN
c_func
(paren
id|avail
comma
id|count
)paren
suffix:semicolon
r_while
c_loop
(paren
id|send
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;buf_wp
OG
id|dev-&gt;buf_rp
)paren
(brace
id|cur
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_wp
op_minus
id|dev-&gt;buf_rp
)paren
suffix:semicolon
)brace
r_else
(brace
id|cur
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_end
op_minus
id|dev-&gt;buf_rp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|dev-&gt;buf_rp
comma
id|cur
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dev-&gt;buf_rp
op_add_assign
id|cur
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buf_rp
op_eq
id|dev-&gt;buf_end
)paren
id|dev-&gt;buf_rp
op_assign
id|dev-&gt;buf
suffix:semicolon
id|send
op_sub_assign
id|cur
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;buf_writers
)paren
suffix:semicolon
r_return
id|DRM_MIN
c_func
(paren
id|avail
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* In an incredibly convoluted setup, the kernel module actually calls&n; * back into the X server to perform context switches on behalf of the&n; * 3d clients.&n; */
DECL|function|write_string
r_int
id|DRM
c_func
(paren
id|write_string
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|left
op_assign
(paren
id|dev-&gt;buf_rp
op_plus
id|DRM_BSZ
op_minus
id|dev-&gt;buf_wp
)paren
op_mod
id|DRM_BSZ
suffix:semicolon
r_int
id|send
op_assign
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_int
id|count
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d left, %d to send (%p, %p)&bslash;n&quot;
comma
id|left
comma
id|send
comma
id|dev-&gt;buf_rp
comma
id|dev-&gt;buf_wp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|left
op_eq
l_int|1
op_logical_or
id|dev-&gt;buf_wp
op_ne
id|dev-&gt;buf_rp
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Buffer not empty (%d left, wp = %p, rp = %p)&bslash;n&quot;
comma
id|left
comma
id|dev-&gt;buf_wp
comma
id|dev-&gt;buf_rp
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|send
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;buf_wp
op_ge
id|dev-&gt;buf_rp
)paren
(brace
id|count
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_end
op_minus
id|dev-&gt;buf_wp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
id|left
)paren
op_decrement
id|count
suffix:semicolon
multiline_comment|/* Leave a hole */
)brace
r_else
(brace
id|count
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_rp
op_minus
id|dev-&gt;buf_wp
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|strncpy
c_func
(paren
id|dev-&gt;buf_wp
comma
id|s
comma
id|count
)paren
suffix:semicolon
id|dev-&gt;buf_wp
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buf_wp
op_eq
id|dev-&gt;buf_end
)paren
id|dev-&gt;buf_wp
op_assign
id|dev-&gt;buf
suffix:semicolon
id|send
op_sub_assign
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;buf_async
)paren
id|kill_fasync
c_func
(paren
op_amp
id|dev-&gt;buf_async
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;waking&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;buf_readers
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gamma_fops_poll
r_int
r_int
id|gamma_fops_poll
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|poll_table_struct
op_star
id|wait
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
id|poll_wait
c_func
(paren
id|filp
comma
op_amp
id|dev-&gt;buf_readers
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buf_wp
op_ne
id|dev-&gt;buf_rp
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|context_switch
r_int
id|DRM
c_func
(paren
id|context_switch
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|old
comma
r_int
r_new
)paren
(brace
r_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
id|drm_queue_t
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;context_flag
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Reentering -- FIXME&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;Context switch from %d to %d&bslash;n&quot;
comma
id|old
comma
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_ge
id|dev-&gt;queue_count
)paren
(brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;context_flag
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
r_new
op_eq
id|dev-&gt;last_context
)paren
(brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;context_flag
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|q
op_assign
id|dev-&gt;queuelist
(braket
r_new
)braket
suffix:semicolon
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
id|q-&gt;use_count
)paren
op_eq
l_int|1
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;use_count
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;context_flag
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* This causes the X server to wake up &amp; do a bunch of hardware&n;&t; * interaction to actually effect the context switch.&n;&t; */
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;C %d %d&bslash;n&quot;
comma
id|old
comma
r_new
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|write_string
)paren
(paren
id|dev
comma
id|buf
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
l_int|0
suffix:semicolon
)brace
DECL|function|context_switch_complete
r_int
id|DRM
c_func
(paren
id|context_switch_complete
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
r_new
)paren
(brace
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
id|dev-&gt;last_context
op_assign
r_new
suffix:semicolon
multiline_comment|/* PRE/POST: This is the _only_ writer. */
id|dev-&gt;last_switch
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|_DRM_LOCK_IS_HELD
c_func
(paren
id|dev-&gt;lock.hw_lock-&gt;lock
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Lock isn&squot;t held after context switch&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dma
op_logical_or
op_logical_neg
(paren
id|dma-&gt;next_buffer
op_logical_and
id|dma-&gt;next_buffer-&gt;while_locked
)paren
)paren
(brace
r_if
c_cond
(paren
id|DRM
c_func
(paren
id|lock_free
)paren
(paren
id|dev
comma
op_amp
id|dev-&gt;lock.hw_lock-&gt;lock
comma
id|DRM_KERNEL_CONTEXT
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Cannot free lock&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;context_flag
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;context_wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_queue
r_static
r_int
id|DRM
c_func
(paren
id|init_queue
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
id|drm_queue_t
op_star
id|q
comma
id|drm_ctx_t
op_star
id|ctx
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
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
op_ne
l_int|1
op_logical_or
id|atomic_read
c_func
(paren
op_amp
id|q-&gt;finalization
)paren
op_logical_or
id|atomic_read
c_func
(paren
op_amp
id|q-&gt;block_count
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;New queue is already in use: u%d f%d b%d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|q-&gt;use_count
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|q-&gt;finalization
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|q-&gt;block_count
)paren
)paren
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|q-&gt;finalization
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|q-&gt;block_count
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|q-&gt;block_read
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|q-&gt;block_write
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|q-&gt;total_queued
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|q-&gt;total_flushed
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|q-&gt;total_locks
comma
l_int|0
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|q-&gt;write_queue
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|q-&gt;read_queue
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|q-&gt;flush_queue
)paren
suffix:semicolon
id|q-&gt;flags
op_assign
id|ctx-&gt;flags
suffix:semicolon
id|DRM
c_func
(paren
id|waitlist_create
)paren
(paren
op_amp
id|q-&gt;waitlist
comma
id|dev-&gt;dma-&gt;buf_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* drm_alloc_queue:&n;PRE: 1) dev-&gt;queuelist[0..dev-&gt;queue_count] is allocated and will not&n;&t;disappear (so all deallocation must be done after IOCTLs are off)&n;     2) dev-&gt;queue_count &lt; dev-&gt;queue_slots&n;     3) dev-&gt;queuelist[i].use_count == 0 and&n;&t;dev-&gt;queuelist[i].finalization == 0 if i not in use&n;POST: 1) dev-&gt;queuelist[i].use_count == 1&n;      2) dev-&gt;queue_count &lt; dev-&gt;queue_slots */
DECL|function|alloc_queue
r_static
r_int
id|DRM
c_func
(paren
id|alloc_queue
)paren
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
id|drm_queue_t
op_star
id|queue
suffix:semicolon
r_int
id|oldslots
suffix:semicolon
r_int
id|newslots
suffix:semicolon
multiline_comment|/* Check for a free queue */
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
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;queuelist
(braket
id|i
)braket
op_member_access_from_pointer
id|use_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;queuelist
(braket
id|i
)braket
op_member_access_from_pointer
id|use_count
)paren
op_eq
l_int|1
op_logical_and
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;queuelist
(braket
id|i
)braket
op_member_access_from_pointer
id|finalization
)paren
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d (free)&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
id|atomic_dec
c_func
(paren
op_amp
id|dev-&gt;queuelist
(braket
id|i
)braket
op_member_access_from_pointer
id|use_count
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate a new queue */
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|queue
op_assign
id|DRM
c_func
(paren
id|alloc
)paren
(paren
r_sizeof
(paren
op_star
id|queue
)paren
comma
id|DRM_MEM_QUEUES
)paren
suffix:semicolon
id|memset
c_func
(paren
id|queue
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|queue
)paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|queue-&gt;use_count
comma
l_int|1
)paren
suffix:semicolon
op_increment
id|dev-&gt;queue_count
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;queue_count
op_ge
id|dev-&gt;queue_slots
)paren
(brace
id|oldslots
op_assign
id|dev-&gt;queue_slots
op_star
r_sizeof
(paren
op_star
id|dev-&gt;queuelist
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;queue_slots
)paren
id|dev-&gt;queue_slots
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;queue_slots
op_mul_assign
l_int|2
suffix:semicolon
id|newslots
op_assign
id|dev-&gt;queue_slots
op_star
r_sizeof
(paren
op_star
id|dev-&gt;queuelist
)paren
suffix:semicolon
id|dev-&gt;queuelist
op_assign
id|DRM
c_func
(paren
id|realloc
)paren
(paren
id|dev-&gt;queuelist
comma
id|oldslots
comma
id|newslots
comma
id|DRM_MEM_QUEUES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;queuelist
)paren
(brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
id|dev-&gt;queuelist
(braket
id|dev-&gt;queue_count
op_minus
l_int|1
)braket
op_assign
id|queue
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d (new)&bslash;n&quot;
comma
id|dev-&gt;queue_count
op_minus
l_int|1
)paren
suffix:semicolon
r_return
id|dev-&gt;queue_count
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|resctx
r_int
id|DRM
c_func
(paren
id|resctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|drm_ctx_res_t
id|__user
op_star
id|argp
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
id|drm_ctx_res_t
id|res
suffix:semicolon
id|drm_ctx_t
id|ctx
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|DRM_RESERVED_CONTEXTS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|res
comma
id|argp
comma
r_sizeof
(paren
id|res
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
id|res.count
op_ge
id|DRM_RESERVED_CONTEXTS
)paren
(brace
id|memset
c_func
(paren
op_amp
id|ctx
comma
l_int|0
comma
r_sizeof
(paren
id|ctx
)paren
)paren
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
id|DRM_RESERVED_CONTEXTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ctx.handle
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
id|res.contexts
(braket
id|i
)braket
comma
op_amp
id|i
comma
r_sizeof
(paren
id|i
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
id|res.count
op_assign
id|DRM_RESERVED_CONTEXTS
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|res
comma
r_sizeof
(paren
id|res
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|addctx
r_int
id|DRM
c_func
(paren
id|addctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
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
id|drm_ctx_t
id|ctx
suffix:semicolon
id|drm_ctx_t
id|__user
op_star
id|argp
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ctx
comma
id|argp
comma
r_sizeof
(paren
id|ctx
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
(paren
id|ctx.handle
op_assign
id|DRM
c_func
(paren
id|alloc_queue
)paren
(paren
id|dev
)paren
)paren
op_eq
id|DRM_KERNEL_CONTEXT
)paren
(brace
multiline_comment|/* Init kernel&squot;s context and get a new one. */
id|DRM
c_func
(paren
id|init_queue
)paren
(paren
id|dev
comma
id|dev-&gt;queuelist
(braket
id|ctx.handle
)braket
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|ctx.handle
op_assign
id|DRM
c_func
(paren
id|alloc_queue
)paren
(paren
id|dev
)paren
suffix:semicolon
)brace
id|DRM
c_func
(paren
id|init_queue
)paren
(paren
id|dev
comma
id|dev-&gt;queuelist
(braket
id|ctx.handle
)braket
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|ctx.handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|ctx
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|modctx
r_int
id|DRM
c_func
(paren
id|modctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
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
id|drm_ctx_t
id|ctx
suffix:semicolon
id|drm_queue_t
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ctx
comma
(paren
id|drm_ctx_t
id|__user
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|ctx.handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx.handle
OL
l_int|0
op_logical_or
id|ctx.handle
op_ge
id|dev-&gt;queue_count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|q
op_assign
id|dev-&gt;queuelist
(braket
id|ctx.handle
)braket
suffix:semicolon
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
id|q-&gt;use_count
)paren
op_eq
l_int|1
)paren
(brace
multiline_comment|/* No longer in use */
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;use_count
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
id|DRM_BUFCOUNT
c_func
(paren
op_amp
id|q-&gt;waitlist
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
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|q-&gt;flags
op_assign
id|ctx.flags
suffix:semicolon
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
)brace
DECL|function|getctx
r_int
id|DRM
c_func
(paren
id|getctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
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
id|drm_ctx_t
id|__user
op_star
id|argp
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
id|drm_ctx_t
id|ctx
suffix:semicolon
id|drm_queue_t
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ctx
comma
id|argp
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|ctx.handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx.handle
op_ge
id|dev-&gt;queue_count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|q
op_assign
id|dev-&gt;queuelist
(braket
id|ctx.handle
)braket
suffix:semicolon
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
id|q-&gt;use_count
)paren
op_eq
l_int|1
)paren
(brace
multiline_comment|/* No longer in use */
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;use_count
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ctx.flags
op_assign
id|q-&gt;flags
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;use_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|ctx
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|switchctx
r_int
id|DRM
c_func
(paren
id|switchctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
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
id|drm_ctx_t
id|ctx
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ctx
comma
(paren
id|drm_ctx_t
id|__user
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|ctx.handle
)paren
suffix:semicolon
r_return
id|DRM
c_func
(paren
id|context_switch
)paren
(paren
id|dev
comma
id|dev-&gt;last_context
comma
id|ctx.handle
)paren
suffix:semicolon
)brace
DECL|function|newctx
r_int
id|DRM
c_func
(paren
id|newctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
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
id|drm_ctx_t
id|ctx
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ctx
comma
(paren
id|drm_ctx_t
id|__user
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|ctx.handle
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|context_switch_complete
)paren
(paren
id|dev
comma
id|ctx.handle
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rmctx
r_int
id|DRM
c_func
(paren
id|rmctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
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
id|drm_ctx_t
id|ctx
suffix:semicolon
id|drm_queue_t
op_star
id|q
suffix:semicolon
id|drm_buf_t
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ctx
comma
(paren
id|drm_ctx_t
id|__user
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|ctx.handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx.handle
op_ge
id|dev-&gt;queue_count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|q
op_assign
id|dev-&gt;queuelist
(braket
id|ctx.handle
)braket
suffix:semicolon
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
id|q-&gt;use_count
)paren
op_eq
l_int|1
)paren
(brace
multiline_comment|/* No longer in use */
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;use_count
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|q-&gt;finalization
)paren
suffix:semicolon
multiline_comment|/* Mark queue in finalization state */
id|atomic_sub
c_func
(paren
l_int|2
comma
op_amp
id|q-&gt;use_count
)paren
suffix:semicolon
multiline_comment|/* Mark queue as unused (pending&n;&t;&t;&t;&t;&t; finalization) */
r_while
c_loop
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;interrupt_flag
)paren
)paren
(brace
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
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;interrupt_flag
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
multiline_comment|/* Remove queued buffers */
r_while
c_loop
(paren
(paren
id|buf
op_assign
id|DRM
c_func
(paren
id|waitlist_get
)paren
(paren
op_amp
id|q-&gt;waitlist
)paren
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
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;interrupt_flag
)paren
suffix:semicolon
multiline_comment|/* Wakeup blocked processes */
id|wake_up_interruptible
c_func
(paren
op_amp
id|q-&gt;read_queue
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|q-&gt;write_queue
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|q-&gt;flush_queue
)paren
suffix:semicolon
multiline_comment|/* Finalization over.  Queue is made&n;&t;&t;&t;&t;   available when both use_count and&n;&t;&t;&t;&t;   finalization become 0, which won&squot;t&n;&t;&t;&t;&t;   happen until all the waiting processes&n;&t;&t;&t;&t;   stop waiting. */
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;finalization
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
