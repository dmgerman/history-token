multiline_comment|/* lock.c -- IOCTLs for locking -*- linux-c -*-&n; * Created: Tue Feb  2 08:37:54 1999 by faith@valinux.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/* Gamma-specific code extracted from drm_lock.h:&n; */
DECL|function|flush_queue
r_static
r_int
id|DRM
c_func
(paren
id|flush_queue
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|context
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|entry
comma
id|current
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|drm_queue_t
op_star
id|q
op_assign
id|dev-&gt;queuelist
(braket
id|context
)braket
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
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
OG
l_int|1
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|q-&gt;block_write
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|q-&gt;flush_queue
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
id|DRM_BUFCOUNT
c_func
(paren
op_amp
id|q-&gt;waitlist
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
id|ret
op_assign
op_minus
id|EINTR
suffix:semicolon
multiline_comment|/* Can&squot;t restart */
r_break
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
id|q-&gt;flush_queue
comma
op_amp
id|entry
)paren
suffix:semicolon
)brace
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;use_count
)paren
suffix:semicolon
multiline_comment|/* NOTE: block_write is still incremented!&n;&t;&t;&t;&t;   Use drm_flush_unlock_queue to decrement. */
r_return
id|ret
suffix:semicolon
)brace
DECL|function|flush_unblock_queue
r_static
r_int
id|DRM
c_func
(paren
id|flush_unblock_queue
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|context
)paren
(brace
id|drm_queue_t
op_star
id|q
op_assign
id|dev-&gt;queuelist
(braket
id|context
)braket
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
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
OG
l_int|1
)paren
(brace
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
id|atomic_dec
c_func
(paren
op_amp
id|q-&gt;block_write
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|q-&gt;write_queue
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
)brace
DECL|function|flush_block_and_flush
r_int
id|DRM
c_func
(paren
id|flush_block_and_flush
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|context
comma
id|drm_lock_flags_t
id|flags
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|_DRM_LOCK_FLUSH
)paren
(brace
id|ret
op_assign
id|DRM
c_func
(paren
id|flush_queue
)paren
(paren
id|dev
comma
id|DRM_KERNEL_CONTEXT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
id|DRM
c_func
(paren
id|flush_queue
)paren
(paren
id|dev
comma
id|context
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|_DRM_LOCK_FLUSH_ALL
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|ret
op_logical_and
id|i
OL
id|dev-&gt;queue_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ret
op_assign
id|DRM
c_func
(paren
id|flush_queue
)paren
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|flush_unblock
r_int
id|DRM
c_func
(paren
id|flush_unblock
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|context
comma
id|drm_lock_flags_t
id|flags
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|_DRM_LOCK_FLUSH
)paren
(brace
id|ret
op_assign
id|DRM
c_func
(paren
id|flush_unblock_queue
)paren
(paren
id|dev
comma
id|DRM_KERNEL_CONTEXT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
id|DRM
c_func
(paren
id|flush_unblock_queue
)paren
(paren
id|dev
comma
id|context
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|_DRM_LOCK_FLUSH_ALL
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|ret
op_logical_and
id|i
OL
id|dev-&gt;queue_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ret
op_assign
id|DRM
c_func
(paren
id|flush_unblock_queue
)paren
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|finish
r_int
id|DRM
c_func
(paren
id|finish
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|drm_lock_t
id|lock
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|lock
comma
(paren
id|drm_lock_t
id|__user
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|lock
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ret
op_assign
id|DRM
c_func
(paren
id|flush_block_and_flush
)paren
(paren
id|dev
comma
id|lock.context
comma
id|lock.flags
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|flush_unblock
)paren
(paren
id|dev
comma
id|lock.context
comma
id|lock.flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
