multiline_comment|/* i830_dma.c -- DMA support for the I830 -*- linux-c -*-&n; *&n; * Copyright 2002 Tungsten Graphics, Inc.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors: Keith Whitwell &lt;keith@tungstengraphics.com&gt;&n; *&n; */
macro_line|#include &quot;i830.h&quot;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm.h&quot;
macro_line|#include &quot;i830_drm.h&quot;
macro_line|#include &quot;i830_drv.h&quot;
macro_line|#include &lt;linux/interrupt.h&gt;&t;/* For task queue support */
macro_line|#include &lt;linux/delay.h&gt;
DECL|function|irq_handler
id|irqreturn_t
id|DRM
c_func
(paren
id|irq_handler
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
id|drm_i830_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_i830_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
id|u16
id|temp
suffix:semicolon
id|temp
op_assign
id|I830_READ16
c_func
(paren
id|I830REG_INT_IDENTITY_R
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%x&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|temp
op_amp
l_int|2
)paren
)paren
r_return
id|IRQ_NONE
suffix:semicolon
id|I830_WRITE16
c_func
(paren
id|I830REG_INT_IDENTITY_R
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
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev_priv-&gt;irq_queue
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|i830_emit_irq
r_int
id|i830_emit_irq
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_i830_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|RING_LOCALS
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev_priv-&gt;irq_emitted
)paren
suffix:semicolon
id|BEGIN_LP_RING
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|GFX_OP_USER_INTERRUPT
)paren
suffix:semicolon
id|ADVANCE_LP_RING
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
DECL|function|i830_wait_irq
r_int
id|i830_wait_irq
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
id|drm_i830_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_i830_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
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
id|dev_priv-&gt;sarea_priv-&gt;perf_boxes
op_or_assign
id|I830_BOX_WAIT
suffix:semicolon
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
id|DRM_ERROR
c_func
(paren
l_string|&quot;timeout iir %x imr %x ier %x hwstam %x&bslash;n&quot;
comma
id|I830_READ16
c_func
(paren
id|I830REG_INT_IDENTITY_R
)paren
comma
id|I830_READ16
c_func
(paren
id|I830REG_INT_MASK_R
)paren
comma
id|I830_READ16
c_func
(paren
id|I830REG_INT_ENABLE_R
)paren
comma
id|I830_READ16
c_func
(paren
id|I830REG_HWSTAM
)paren
)paren
suffix:semicolon
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
)brace
multiline_comment|/* Needs the lock as it touches the ring.&n; */
DECL|function|i830_irq_emit
r_int
id|i830_irq_emit
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
id|drm_i830_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_i830_irq_emit_t
id|emit
suffix:semicolon
r_int
id|result
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
l_string|&quot;i830_irq_emit called without lock held&bslash;n&quot;
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
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|emit
comma
(paren
id|drm_i830_irq_emit_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|emit
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|result
op_assign
id|i830_emit_irq
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
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
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Doesn&squot;t need the hardware lock.&n; */
DECL|function|i830_irq_wait
r_int
id|i830_irq_wait
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
id|drm_i830_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_i830_irq_wait_t
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
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|irqwait
comma
(paren
id|drm_i830_irq_wait_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|irqwait
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|i830_wait_irq
c_func
(paren
id|dev
comma
id|irqwait.irq_seq
)paren
suffix:semicolon
)brace
multiline_comment|/* drm_dma.h hooks&n;*/
DECL|function|driver_irq_preinstall
r_void
id|DRM
c_func
(paren
id|driver_irq_preinstall
)paren
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_i830_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_i830_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
id|I830_WRITE16
c_func
(paren
id|I830REG_HWSTAM
comma
l_int|0xffff
)paren
suffix:semicolon
id|I830_WRITE16
c_func
(paren
id|I830REG_INT_MASK_R
comma
l_int|0x0
)paren
suffix:semicolon
id|I830_WRITE16
c_func
(paren
id|I830REG_INT_ENABLE_R
comma
l_int|0x0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev_priv-&gt;irq_received
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev_priv-&gt;irq_emitted
comma
l_int|0
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev_priv-&gt;irq_queue
)paren
suffix:semicolon
)brace
DECL|function|driver_irq_postinstall
r_void
id|DRM
c_func
(paren
id|driver_irq_postinstall
)paren
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_i830_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_i830_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
id|I830_WRITE16
c_func
(paren
id|I830REG_INT_ENABLE_R
comma
l_int|0x2
)paren
suffix:semicolon
)brace
DECL|function|driver_irq_uninstall
r_void
id|DRM
c_func
(paren
id|driver_irq_uninstall
)paren
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_i830_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_i830_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_priv
)paren
r_return
suffix:semicolon
id|I830_WRITE16
c_func
(paren
id|I830REG_INT_MASK_R
comma
l_int|0xffff
)paren
suffix:semicolon
id|I830_WRITE16
c_func
(paren
id|I830REG_INT_ENABLE_R
comma
l_int|0x0
)paren
suffix:semicolon
)brace
eof
