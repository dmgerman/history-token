multiline_comment|/* radeon_mem.c -- Simple agp/fb memory manager for radeon -*- linux-c -*-&n; *&n; * Copyright (C) The Weather Channel, Inc.  2002.  All Rights Reserved.&n; * &n; * The Weather Channel (TM) funded Tungsten Graphics to develop the&n; * initial release of the Radeon 8500 driver under the XFree86 license.&n; * This notice must be preserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Keith Whitwell &lt;keith@tungstengraphics.com&gt;&n; */
macro_line|#include &quot;radeon.h&quot;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm.h&quot;
macro_line|#include &quot;radeon_drm.h&quot;
macro_line|#include &quot;radeon_drv.h&quot;
multiline_comment|/* Interrupts - Used for device synchronization and flushing in the&n; * following circumstances:&n; *&n; * - Exclusive FB access with hw idle:&n; *    - Wait for GUI Idle (?) interrupt, then do normal flush.&n; *&n; * - Frame throttling, NV_fence:&n; *    - Drop marker irq&squot;s into command stream ahead of time.&n; *    - Wait on irq&squot;s with lock *not held*&n; *    - Check each for termination condition&n; *&n; * - Internally in cp_getbuffer, etc:&n; *    - as above, but wait with lock held???&n; *&n; * NOTE: These functions are misleadingly named -- the irq&squot;s aren&squot;t&n; * tied to dma at all, this is just a hangover from dri prehistory.&n; */
DECL|function|dma_service
r_void
id|DRM
c_func
(paren
id|dma_service
)paren
(paren
id|DRM_IRQ_ARGS
)paren
(brace
id|drm_device_t
op_star
id|dev
op_assign
(paren
id|drm_device_t
op_star
)paren
id|arg
suffix:semicolon
id|drm_radeon_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_radeon_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
id|u32
id|temp
suffix:semicolon
multiline_comment|/* Need to wait for fifo to drain?&n;&t; */
id|temp
op_assign
id|RADEON_READ
c_func
(paren
id|RADEON_GEN_INT_STATUS
)paren
suffix:semicolon
id|temp
op_assign
id|temp
op_amp
id|RADEON_SW_INT_TEST_ACK
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|RADEON_WRITE
c_func
(paren
id|RADEON_GEN_INT_STATUS
comma
id|temp
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev_priv-&gt;irq_received
)paren
suffix:semicolon
macro_line|#ifdef __linux__
id|schedule_task
c_func
(paren
op_amp
id|dev-&gt;tq
)paren
suffix:semicolon
macro_line|#endif /* __linux__ */
macro_line|#ifdef __FreeBSD__
id|taskqueue_enqueue
c_func
(paren
id|taskqueue_swi
comma
op_amp
id|dev-&gt;task
)paren
suffix:semicolon
macro_line|#endif /* __FreeBSD__ */
)brace
DECL|function|dma_immediate_bh
r_void
id|DRM
c_func
(paren
id|dma_immediate_bh
)paren
(paren
id|DRM_TASKQUEUE_ARGS
)paren
(brace
id|drm_device_t
op_star
id|dev
op_assign
(paren
id|drm_device_t
op_star
)paren
id|arg
suffix:semicolon
id|drm_radeon_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_radeon_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
macro_line|#ifdef __linux__
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev_priv-&gt;irq_queue
)paren
suffix:semicolon
macro_line|#endif /* __linux__ */
macro_line|#ifdef __FreeBSD__
id|wakeup
c_func
(paren
op_amp
id|dev_priv-&gt;irq_queue
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|radeon_emit_irq
r_int
id|radeon_emit_irq
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_radeon_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|RING_LOCALS
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev_priv-&gt;irq_emitted
)paren
suffix:semicolon
id|BEGIN_RING
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|CP_PACKET0
c_func
(paren
id|RADEON_GEN_INT_STATUS
comma
l_int|0
)paren
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|RADEON_SW_INT_FIRE
)paren
suffix:semicolon
id|ADVANCE_RING
c_func
(paren
)paren
suffix:semicolon
id|COMMIT_RING
c_func
(paren
)paren
suffix:semicolon
r_return
id|atomic_read
c_func
(paren
op_amp
id|dev_priv-&gt;irq_emitted
)paren
suffix:semicolon
)brace
DECL|function|radeon_wait_irq
r_int
id|radeon_wait_irq
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|irq_nr
)paren
(brace
id|drm_radeon_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_radeon_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
macro_line|#ifdef __linux__
id|DECLARE_WAITQUEUE
c_func
(paren
id|entry
comma
id|current
)paren
suffix:semicolon
r_int
r_int
id|end
op_assign
id|jiffies
op_plus
id|HZ
op_star
l_int|3
suffix:semicolon
macro_line|#endif /* __linux__ */
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dev_priv-&gt;irq_received
)paren
op_ge
id|irq_nr
)paren
r_return
l_int|0
suffix:semicolon
id|dev_priv-&gt;stats.boxes
op_or_assign
id|RADEON_BOX_WAIT_IDLE
suffix:semicolon
macro_line|#ifdef __linux__
id|add_wait_queue
c_func
(paren
op_amp
id|dev_priv-&gt;irq_queue
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
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dev_priv-&gt;irq_received
)paren
op_ge
id|irq_nr
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|end
op_minus
id|jiffies
)paren
op_le
l_int|0
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Lockup?  Missed irq? */
r_break
suffix:semicolon
)brace
id|schedule_timeout
c_func
(paren
id|HZ
op_star
l_int|3
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
r_break
suffix:semicolon
)brace
)brace
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|dev_priv-&gt;irq_queue
comma
op_amp
id|entry
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
macro_line|#endif /* __linux__ */
macro_line|#ifdef __FreeBSD__
id|ret
op_assign
id|tsleep
c_func
(paren
op_amp
id|dev_priv-&gt;irq_queue
comma
id|PZERO
op_or
id|PCATCH
comma
"&bslash;"
l_string|&quot;rdnirq&quot;
comma
l_int|3
op_star
id|hz
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_eq
id|EWOULDBLOCK
)paren
op_logical_or
(paren
id|ret
op_eq
id|EINTR
)paren
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EBUSY
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
macro_line|#endif /* __FreeBSD__ */
)brace
DECL|function|radeon_emit_and_wait_irq
r_int
id|radeon_emit_and_wait_irq
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
r_return
id|radeon_wait_irq
c_func
(paren
id|dev
comma
id|radeon_emit_irq
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Needs the lock as it touches the ring.&n; */
DECL|function|radeon_irq_emit
r_int
id|radeon_irq_emit
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_radeon_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_radeon_irq_emit_t
id|emit
suffix:semicolon
r_int
id|result
suffix:semicolon
id|LOCK_TEST_WITH_RETURN
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_priv
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;%s called with no initialization&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|emit
comma
(paren
id|drm_radeon_irq_emit_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|emit
)paren
)paren
suffix:semicolon
id|result
op_assign
id|radeon_emit_irq
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DRM_COPY_TO_USER
c_func
(paren
id|emit.irq_seq
comma
op_amp
id|result
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;copy_to_user&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|EFAULT
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Doesn&squot;t need the hardware lock.&n; */
DECL|function|radeon_irq_wait
r_int
id|radeon_irq_wait
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_radeon_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_radeon_irq_wait_t
id|irqwait
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_priv
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;%s called with no initialization&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|irqwait
comma
(paren
id|drm_radeon_irq_wait_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|irqwait
)paren
)paren
suffix:semicolon
r_return
id|radeon_wait_irq
c_func
(paren
id|dev
comma
id|irqwait.irq_seq
)paren
suffix:semicolon
)brace
eof
