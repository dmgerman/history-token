multiline_comment|/**&n; * &bslash;file drm_lock.h &n; * IOCTLs for locking&n; * &n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/*&n; * Created: Tue Feb  2 08:37:54 1999 by faith@valinux.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &quot;drmP.h&quot;
multiline_comment|/** &n; * Lock ioctl.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument, pointing to a drm_lock structure.&n; * &bslash;return zero on success or negative number on failure.&n; *&n; * Add the current task to the lock wait queue, and attempt to take to lock.&n; */
DECL|function|drm_lock
r_int
id|drm_lock
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
id|DECLARE_WAITQUEUE
c_func
(paren
id|entry
comma
id|current
)paren
suffix:semicolon
id|drm_lock_t
id|lock
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
op_increment
id|priv-&gt;lock_count
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
r_if
c_cond
(paren
id|lock.context
op_eq
id|DRM_KERNEL_CONTEXT
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Process %d using kernel context %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|lock.context
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d (pid %d) requests lock (0x%08x), flags = 0x%08x&bslash;n&quot;
comma
id|lock.context
comma
id|current-&gt;pid
comma
id|dev-&gt;lock.hw_lock-&gt;lock
comma
id|lock.flags
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
id|DRIVER_DMA_QUEUE
)paren
)paren
r_if
c_cond
(paren
id|lock.context
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
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
id|ret
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
id|lock.context
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
id|ret
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
id|sigemptyset
c_func
(paren
op_amp
id|dev-&gt;sigmask
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|dev-&gt;sigmask
comma
id|SIGSTOP
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|dev-&gt;sigmask
comma
id|SIGTSTP
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|dev-&gt;sigmask
comma
id|SIGTTIN
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|dev-&gt;sigmask
comma
id|SIGTTOU
)paren
suffix:semicolon
id|dev-&gt;sigdata.context
op_assign
id|lock.context
suffix:semicolon
id|dev-&gt;sigdata.lock
op_assign
id|dev-&gt;lock.hw_lock
suffix:semicolon
id|block_all_signals
c_func
(paren
id|drm_notifier
comma
op_amp
id|dev-&gt;sigdata
comma
op_amp
id|dev-&gt;sigmask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;dma_ready
op_logical_and
(paren
id|lock.flags
op_amp
id|_DRM_LOCK_READY
)paren
)paren
id|dev-&gt;driver
op_member_access_from_pointer
id|dma_ready
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;dma_quiescent
op_logical_and
(paren
id|lock.flags
op_amp
id|_DRM_LOCK_QUIESCENT
)paren
)paren
r_return
id|dev-&gt;driver
op_member_access_from_pointer
id|dma_quiescent
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* dev-&gt;driver-&gt;kernel_context_switch isn&squot;t used by any of the x86 &n;&t; *  drivers but is used by the Sparc driver.&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;kernel_context_switch
op_logical_and
id|dev-&gt;last_context
op_ne
id|lock.context
)paren
(brace
id|dev-&gt;driver
op_member_access_from_pointer
id|kernel_context_switch
c_func
(paren
id|dev
comma
id|dev-&gt;last_context
comma
id|lock.context
)paren
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d %s&bslash;n&quot;
comma
id|lock.context
comma
id|ret
ques
c_cond
l_string|&quot;interrupted&quot;
suffix:colon
l_string|&quot;has lock&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/** &n; * Unlock ioctl.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument, pointing to a drm_lock structure.&n; * &bslash;return zero on success or negative number on failure.&n; *&n; * Transfer and free the lock.&n; */
DECL|function|drm_unlock
r_int
id|drm_unlock
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
id|drm_lock_t
id|lock
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
r_if
c_cond
(paren
id|lock.context
op_eq
id|DRM_KERNEL_CONTEXT
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Process %d using kernel context %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|lock.context
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
id|dev-&gt;counts
(braket
id|_DRM_STAT_UNLOCKS
)braket
)paren
suffix:semicolon
multiline_comment|/* kernel_context_switch isn&squot;t used by any of the x86 drm&n;&t; * modules but is required by the Sparc driver.&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;kernel_context_switch_unlock
)paren
id|dev-&gt;driver
op_member_access_from_pointer
id|kernel_context_switch_unlock
c_func
(paren
id|dev
comma
op_amp
id|lock
)paren
suffix:semicolon
r_else
(brace
id|drm_lock_transfer
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
r_if
c_cond
(paren
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
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|unblock_all_signals
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Take the heavyweight lock.&n; *&n; * &bslash;param lock lock pointer.&n; * &bslash;param context locking context.&n; * &bslash;return one if the lock is held, or zero otherwise.&n; *&n; * Attempt to mark the lock as held by the given context, via the &bslash;p cmpxchg instruction.&n; */
DECL|function|drm_lock_take
r_int
id|drm_lock_take
c_func
(paren
id|__volatile__
r_int
r_int
op_star
id|lock
comma
r_int
r_int
id|context
)paren
(brace
r_int
r_int
id|old
comma
r_new
comma
id|prev
suffix:semicolon
r_do
(brace
id|old
op_assign
op_star
id|lock
suffix:semicolon
r_if
c_cond
(paren
id|old
op_amp
id|_DRM_LOCK_HELD
)paren
r_new
op_assign
id|old
op_or
id|_DRM_LOCK_CONT
suffix:semicolon
r_else
r_new
op_assign
id|context
op_or
id|_DRM_LOCK_HELD
suffix:semicolon
id|prev
op_assign
id|cmpxchg
c_func
(paren
id|lock
comma
id|old
comma
r_new
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|prev
op_ne
id|old
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|old
)paren
op_eq
id|context
)paren
(brace
r_if
c_cond
(paren
id|old
op_amp
id|_DRM_LOCK_HELD
)paren
(brace
r_if
c_cond
(paren
id|context
op_ne
id|DRM_KERNEL_CONTEXT
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;%d holds heavyweight lock&bslash;n&quot;
comma
id|context
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
r_new
op_eq
(paren
id|context
op_or
id|_DRM_LOCK_HELD
)paren
)paren
(brace
multiline_comment|/* Have lock */
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * This takes a lock forcibly and hands it to context.&t;Should ONLY be used&n; * inside *_unlock to give lock to kernel before calling *_dma_schedule. &n; * &n; * &bslash;param dev DRM device.&n; * &bslash;param lock lock pointer.&n; * &bslash;param context locking context.&n; * &bslash;return always one.&n; *&n; * Resets the lock file pointer.&n; * Marks the lock as held by the given context, via the &bslash;p cmpxchg instruction.&n; */
DECL|function|drm_lock_transfer
r_int
id|drm_lock_transfer
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|__volatile__
r_int
r_int
op_star
id|lock
comma
r_int
r_int
id|context
)paren
(brace
r_int
r_int
id|old
comma
r_new
comma
id|prev
suffix:semicolon
id|dev-&gt;lock.filp
op_assign
l_int|NULL
suffix:semicolon
r_do
(brace
id|old
op_assign
op_star
id|lock
suffix:semicolon
r_new
op_assign
id|context
op_or
id|_DRM_LOCK_HELD
suffix:semicolon
id|prev
op_assign
id|cmpxchg
c_func
(paren
id|lock
comma
id|old
comma
r_new
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|prev
op_ne
id|old
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * Free lock.&n; * &n; * &bslash;param dev DRM device.&n; * &bslash;param lock lock.&n; * &bslash;param context context.&n; * &n; * Resets the lock file pointer.&n; * Marks the lock as not held, via the &bslash;p cmpxchg instruction. Wakes any task&n; * waiting on the lock queue.&n; */
DECL|function|drm_lock_free
r_int
id|drm_lock_free
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|__volatile__
r_int
r_int
op_star
id|lock
comma
r_int
r_int
id|context
)paren
(brace
r_int
r_int
id|old
comma
r_new
comma
id|prev
suffix:semicolon
id|dev-&gt;lock.filp
op_assign
l_int|NULL
suffix:semicolon
r_do
(brace
id|old
op_assign
op_star
id|lock
suffix:semicolon
r_new
op_assign
l_int|0
suffix:semicolon
id|prev
op_assign
id|cmpxchg
c_func
(paren
id|lock
comma
id|old
comma
r_new
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|prev
op_ne
id|old
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_DRM_LOCK_IS_HELD
c_func
(paren
id|old
)paren
op_logical_and
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|old
)paren
op_ne
id|context
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;%d freed heavyweight lock held by %d&bslash;n&quot;
comma
id|context
comma
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|old
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;lock.lock_queue
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * If we get here, it means that the process has called DRM_IOCTL_LOCK&n; * without calling DRM_IOCTL_UNLOCK.&n; *&n; * If the lock is not held, then let the signal proceed as usual.  If the lock&n; * is held, then set the contended flag and keep the signal blocked.&n; *&n; * &bslash;param priv pointer to a drm_sigdata structure.&n; * &bslash;return one if the signal should be delivered normally, or zero if the&n; * signal should be blocked.&n; */
DECL|function|drm_notifier
r_int
id|drm_notifier
c_func
(paren
r_void
op_star
id|priv
)paren
(brace
id|drm_sigdata_t
op_star
id|s
op_assign
(paren
id|drm_sigdata_t
op_star
)paren
id|priv
suffix:semicolon
r_int
r_int
id|old
comma
r_new
comma
id|prev
suffix:semicolon
multiline_comment|/* Allow signal delivery if lock isn&squot;t held */
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;lock
op_logical_or
op_logical_neg
id|_DRM_LOCK_IS_HELD
c_func
(paren
id|s-&gt;lock-&gt;lock
)paren
op_logical_or
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|s-&gt;lock-&gt;lock
)paren
op_ne
id|s-&gt;context
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Otherwise, set flag to force call to&n;                                   drmUnlock */
r_do
(brace
id|old
op_assign
id|s-&gt;lock-&gt;lock
suffix:semicolon
r_new
op_assign
id|old
op_or
id|_DRM_LOCK_CONT
suffix:semicolon
id|prev
op_assign
id|cmpxchg
c_func
(paren
op_amp
id|s-&gt;lock-&gt;lock
comma
id|old
comma
r_new
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|prev
op_ne
id|old
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
