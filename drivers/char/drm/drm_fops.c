multiline_comment|/**&n; * &bslash;file drm_fops.h &n; * File operations for DRM&n; * &n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &bslash;author Daryll Strauss &lt;daryll@valinux.com&gt;&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/*&n; * Created: Mon Jan  4 08:58:31 1999 by faith@valinux.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &lt;linux/poll.h&gt;
DECL|function|drm_setup
r_static
r_int
id|drm_setup
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;presetup
)paren
(brace
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|presetup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
r_return
id|ret
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;ioctl_count
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;vma_count
comma
l_int|0
)paren
suffix:semicolon
id|dev-&gt;buf_use
op_assign
l_int|0
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;buf_alloc
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drm_core_check_feature
c_func
(paren
id|dev
comma
id|DRIVER_HAVE_DMA
)paren
)paren
(brace
id|i
op_assign
id|drm_dma_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
r_return
id|i
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DRM_ARRAY_SIZE
c_func
(paren
id|dev-&gt;counts
)paren
suffix:semicolon
id|i
op_increment
)paren
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;counts
(braket
id|i
)braket
comma
l_int|0
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
id|DRM_HASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev-&gt;magiclist
(braket
id|i
)braket
dot
id|head
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;magiclist
(braket
id|i
)braket
dot
id|tail
op_assign
l_int|NULL
suffix:semicolon
)brace
id|dev-&gt;maplist
op_assign
id|drm_alloc
c_func
(paren
r_sizeof
(paren
op_star
id|dev-&gt;maplist
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;maplist
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev-&gt;maplist
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dev-&gt;maplist
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;maplist-&gt;head
)paren
suffix:semicolon
id|dev-&gt;ctxlist
op_assign
id|drm_alloc
c_func
(paren
r_sizeof
(paren
op_star
id|dev-&gt;ctxlist
)paren
comma
id|DRM_MEM_CTXLIST
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;ctxlist
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev-&gt;ctxlist
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dev-&gt;ctxlist
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;ctxlist-&gt;head
)paren
suffix:semicolon
id|dev-&gt;vmalist
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;sigdata.lock
op_assign
id|dev-&gt;lock.hw_lock
op_assign
l_int|NULL
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;lock.lock_queue
)paren
suffix:semicolon
id|dev-&gt;queue_count
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;queue_reserved
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;queue_slots
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;queuelist
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;irq_enabled
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;context_flag
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;interrupt_flag
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;dma_flag
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;last_context
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;last_switch
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;last_checked
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;context_wait
)paren
suffix:semicolon
id|dev-&gt;if_version
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;ctx_start
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;lck_start
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;buf_rp
op_assign
id|dev-&gt;buf
suffix:semicolon
id|dev-&gt;buf_wp
op_assign
id|dev-&gt;buf
suffix:semicolon
id|dev-&gt;buf_end
op_assign
id|dev-&gt;buf
op_plus
id|DRM_BSZ
suffix:semicolon
id|dev-&gt;buf_async
op_assign
l_int|NULL
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;buf_readers
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;buf_writers
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The kernel&squot;s context could be created here, but is now created&n;&t; * in drm_dma_enqueue.&t;This is more resource-efficient for&n;&t; * hardware that does not do DMA, but may mean that&n;&t; * drm_select_queue fails between the time the interrupt is&n;&t; * initialized and the time the queues are initialized.&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;postsetup
)paren
id|dev-&gt;driver
op_member_access_from_pointer
id|postsetup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Open file.&n; * &n; * &bslash;param inode device inode&n; * &bslash;param filp file pointer.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Searches the DRM device with the same minor number, calls open_helper(), and&n; * increments the device open count. If the open count was previous at zero,&n; * i.e., it&squot;s the first that the device is open, then calls setup().&n; */
DECL|function|drm_open
r_int
id|drm_open
c_func
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
)paren
(brace
id|drm_device_t
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|retcode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|minor
op_ge
l_int|0
)paren
op_logical_and
(paren
id|minor
OL
id|drm_cards_limit
)paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dev
op_assign
id|drm_minors
(braket
id|minor
)braket
dot
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|retcode
op_assign
id|drm_open_helper
c_func
(paren
id|inode
comma
id|filp
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retcode
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;counts
(braket
id|_DRM_STAT_OPENS
)braket
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;open_count
op_increment
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
r_return
id|drm_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
)brace
r_return
id|retcode
suffix:semicolon
)brace
DECL|variable|drm_open
id|EXPORT_SYMBOL
c_func
(paren
id|drm_open
)paren
suffix:semicolon
multiline_comment|/**&n; * Release file.&n; *&n; * &bslash;param inode device inode&n; * &bslash;param filp file pointer.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * If the hardware lock is held then free it, and take it again for the kernel&n; * context since it&squot;s necessary to reclaim buffers. Unlink the file private&n; * data from its list and free it. Decreases the open count and if it reaches&n; * zero calls takedown().&n; */
DECL|function|drm_release
r_int
id|drm_release
c_func
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
suffix:semicolon
r_int
id|retcode
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;open_count = %d&bslash;n&quot;
comma
id|dev-&gt;open_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;prerelease
)paren
id|dev-&gt;driver
op_member_access_from_pointer
id|prerelease
c_func
(paren
id|dev
comma
id|filp
)paren
suffix:semicolon
multiline_comment|/* ========================================================&n;&t; * Begin inline drm_release&n;&t; */
id|DRM_DEBUG
c_func
(paren
l_string|&quot;pid = %d, device = 0x%lx, open_count = %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
(paren
r_int
)paren
id|old_encode_dev
c_func
(paren
id|dev-&gt;device
)paren
comma
id|dev-&gt;open_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;lock_count
op_logical_and
id|dev-&gt;lock.hw_lock
op_logical_and
id|_DRM_LOCK_IS_HELD
c_func
(paren
id|dev-&gt;lock.hw_lock-&gt;lock
)paren
op_logical_and
id|dev-&gt;lock.filp
op_eq
id|filp
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;File %p released, freeing lock for context %d&bslash;n&quot;
comma
id|filp
comma
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|dev-&gt;lock.hw_lock-&gt;lock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;release
)paren
id|dev-&gt;driver
op_member_access_from_pointer
id|release
c_func
(paren
id|dev
comma
id|filp
)paren
suffix:semicolon
id|drm_lock_free
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;lock.hw_lock-&gt;lock
comma
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|dev-&gt;lock.hw_lock-&gt;lock
)paren
)paren
suffix:semicolon
multiline_comment|/* FIXME: may require heavy-handed reset of&n;                                   hardware at this point, possibly&n;                                   processed via a callback to the X&n;                                   server. */
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;release
op_logical_and
id|priv-&gt;lock_count
op_logical_and
id|dev-&gt;lock.hw_lock
)paren
(brace
multiline_comment|/* The lock is required to reclaim buffers */
id|DECLARE_WAITQUEUE
c_func
(paren
id|entry
comma
id|current
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|dev-&gt;lock.lock_queue
comma
op_amp
id|entry
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|__set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;lock.hw_lock
)paren
(brace
multiline_comment|/* Device has been unregistered */
id|retcode
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|drm_lock_take
c_func
(paren
op_amp
id|dev-&gt;lock.hw_lock-&gt;lock
comma
id|DRM_KERNEL_CONTEXT
)paren
)paren
(brace
id|dev-&gt;lock.filp
op_assign
id|filp
suffix:semicolon
id|dev-&gt;lock.lock_time
op_assign
id|jiffies
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;counts
(braket
id|_DRM_STAT_LOCKS
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Got lock */
)brace
multiline_comment|/* Contention */
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
id|retcode
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|__set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|dev-&gt;lock.lock_queue
comma
op_amp
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retcode
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;release
)paren
id|dev-&gt;driver
op_member_access_from_pointer
id|release
c_func
(paren
id|dev
comma
id|filp
)paren
suffix:semicolon
id|drm_lock_free
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;lock.hw_lock-&gt;lock
comma
id|DRM_KERNEL_CONTEXT
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|drm_core_check_feature
c_func
(paren
id|dev
comma
id|DRIVER_HAVE_DMA
)paren
)paren
(brace
id|dev-&gt;driver
op_member_access_from_pointer
id|reclaim_buffers
c_func
(paren
id|filp
)paren
suffix:semicolon
)brace
id|drm_fasync
c_func
(paren
op_minus
l_int|1
comma
id|filp
comma
l_int|0
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;ctxlist_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dev-&gt;ctxlist-&gt;head
)paren
)paren
(brace
id|drm_ctx_list_t
op_star
id|pos
comma
op_star
id|n
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|pos
comma
id|n
comma
op_amp
id|dev-&gt;ctxlist-&gt;head
comma
id|head
)paren
(brace
r_if
c_cond
(paren
id|pos-&gt;tag
op_eq
id|priv
op_logical_and
id|pos-&gt;handle
op_ne
id|DRM_KERNEL_CONTEXT
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;context_dtor
)paren
id|dev-&gt;driver
op_member_access_from_pointer
id|context_dtor
c_func
(paren
id|dev
comma
id|pos-&gt;handle
)paren
suffix:semicolon
id|drm_ctxbitmap_free
c_func
(paren
id|dev
comma
id|pos-&gt;handle
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|pos-&gt;head
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|pos
comma
r_sizeof
(paren
op_star
id|pos
)paren
comma
id|DRM_MEM_CTXLIST
)paren
suffix:semicolon
op_decrement
id|dev-&gt;ctx_count
suffix:semicolon
)brace
)brace
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;ctxlist_sem
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;remove_auth_on_close
op_eq
l_int|1
)paren
(brace
id|drm_file_t
op_star
id|temp
op_assign
id|dev-&gt;file_first
suffix:semicolon
r_while
c_loop
(paren
id|temp
)paren
(brace
id|temp-&gt;authenticated
op_assign
l_int|0
suffix:semicolon
id|temp
op_assign
id|temp-&gt;next
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|priv-&gt;prev
)paren
(brace
id|priv-&gt;prev-&gt;next
op_assign
id|priv-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;file_first
op_assign
id|priv-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|priv-&gt;next
)paren
(brace
id|priv-&gt;next-&gt;prev
op_assign
id|priv-&gt;prev
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;file_last
op_assign
id|priv-&gt;prev
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;free_filp_priv
)paren
id|dev-&gt;driver
op_member_access_from_pointer
id|free_filp_priv
c_func
(paren
id|dev
comma
id|priv
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|priv
comma
r_sizeof
(paren
op_star
id|priv
)paren
comma
id|DRM_MEM_FILES
)paren
suffix:semicolon
multiline_comment|/* ========================================================&n;&t; * End inline drm_release&n;&t; */
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;counts
(braket
id|_DRM_STAT_CLOSES
)braket
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|dev-&gt;open_count
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;ioctl_count
)paren
op_logical_or
id|dev-&gt;blocked
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Device busy: %d %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;ioctl_count
)paren
comma
id|dev-&gt;blocked
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|drm_takedown
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
DECL|variable|drm_release
id|EXPORT_SYMBOL
c_func
(paren
id|drm_release
)paren
suffix:semicolon
multiline_comment|/**&n; * Called whenever a process opens /dev/drm. &n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param dev device.&n; * &bslash;return zero on success or a negative number on failure.&n; * &n; * Creates and initializes a drm_file structure for the file private data in &bslash;p&n; * filp and add it into the double linked list in &bslash;p dev.&n; */
DECL|function|drm_open_helper
r_int
id|drm_open_helper
c_func
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
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
id|drm_file_t
op_star
id|priv
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_EXCL
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* No exclusive opens */
r_if
c_cond
(paren
op_logical_neg
id|drm_cpu_valid
c_func
(paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;pid = %d, minor = %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|minor
)paren
suffix:semicolon
id|priv
op_assign
id|drm_alloc
c_func
(paren
r_sizeof
(paren
op_star
id|priv
)paren
comma
id|DRM_MEM_FILES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|priv
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|priv
)paren
)paren
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|priv
suffix:semicolon
id|priv-&gt;uid
op_assign
id|current-&gt;euid
suffix:semicolon
id|priv-&gt;pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|priv-&gt;minor
op_assign
id|minor
suffix:semicolon
id|priv-&gt;dev
op_assign
id|dev
suffix:semicolon
id|priv-&gt;ioctl_count
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;authenticated
op_assign
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
suffix:semicolon
id|priv-&gt;lock_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;open_helper
)paren
(brace
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|open_helper
c_func
(paren
id|dev
comma
id|priv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out_free
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;file_last
)paren
(brace
id|priv-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|priv-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;file_first
op_assign
id|priv
suffix:semicolon
id|dev-&gt;file_last
op_assign
id|priv
suffix:semicolon
)brace
r_else
(brace
id|priv-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|priv-&gt;prev
op_assign
id|dev-&gt;file_last
suffix:semicolon
id|dev-&gt;file_last-&gt;next
op_assign
id|priv
suffix:semicolon
id|dev-&gt;file_last
op_assign
id|priv
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
macro_line|#ifdef __alpha__
multiline_comment|/*&n;&t; * Default the hose&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;hose
)paren
(brace
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
id|pci_dev
op_assign
id|pci_get_class
c_func
(paren
id|PCI_CLASS_DISPLAY_VGA
op_lshift
l_int|8
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_dev
)paren
(brace
id|dev-&gt;hose
op_assign
id|pci_dev-&gt;sysdata
suffix:semicolon
id|pci_dev_put
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;hose
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
op_assign
id|pci_bus_b
c_func
(paren
id|pci_root_buses.next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
)paren
id|dev-&gt;hose
op_assign
id|b-&gt;sysdata
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
id|out_free
suffix:colon
id|drm_free
c_func
(paren
id|priv
comma
r_sizeof
(paren
op_star
id|priv
)paren
comma
id|DRM_MEM_FILES
)paren
suffix:semicolon
id|filp-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/** No-op. */
DECL|function|drm_flush
r_int
id|drm_flush
c_func
(paren
r_struct
id|file
op_star
id|filp
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
id|DRM_DEBUG
c_func
(paren
l_string|&quot;pid = %d, device = 0x%lx, open_count = %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
(paren
r_int
)paren
id|old_encode_dev
c_func
(paren
id|dev-&gt;device
)paren
comma
id|dev-&gt;open_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|drm_flush
id|EXPORT_SYMBOL
c_func
(paren
id|drm_flush
)paren
suffix:semicolon
multiline_comment|/** No-op. */
DECL|function|drm_fasync
r_int
id|drm_fasync
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
id|on
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
id|retcode
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;fd = %d, device = 0x%lx&bslash;n&quot;
comma
id|fd
comma
(paren
r_int
)paren
id|old_encode_dev
c_func
(paren
id|dev-&gt;device
)paren
)paren
suffix:semicolon
id|retcode
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|filp
comma
id|on
comma
op_amp
id|dev-&gt;buf_async
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retcode
OL
l_int|0
)paren
r_return
id|retcode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|drm_fasync
id|EXPORT_SYMBOL
c_func
(paren
id|drm_fasync
)paren
suffix:semicolon
multiline_comment|/** No-op. */
DECL|function|drm_poll
r_int
r_int
id|drm_poll
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|drm_poll
id|EXPORT_SYMBOL
c_func
(paren
id|drm_poll
)paren
suffix:semicolon
multiline_comment|/** No-op. */
DECL|function|drm_read
id|ssize_t
id|drm_read
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
r_return
l_int|0
suffix:semicolon
)brace
eof
