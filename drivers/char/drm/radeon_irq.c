multiline_comment|/* radeon_irq.c -- IRQ handling for radeon -*- linux-c -*-&n; *&n; * Copyright (C) The Weather Channel, Inc.  2002.  All Rights Reserved.&n; * &n; * The Weather Channel (TM) funded Tungsten Graphics to develop the&n; * initial release of the Radeon 8500 driver under the XFree86 license.&n; * This notice must be preserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Keith Whitwell &lt;keith@tungstengraphics.com&gt;&n; *    Michel D&#xfffd;nzer &lt;michel@daenzer.net&gt;&n; */
macro_line|#include &quot;radeon.h&quot;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm.h&quot;
macro_line|#include &quot;radeon_drm.h&quot;
macro_line|#include &quot;radeon_drv.h&quot;
multiline_comment|/* Interrupts - Used for device synchronization and flushing in the&n; * following circumstances:&n; *&n; * - Exclusive FB access with hw idle:&n; *    - Wait for GUI Idle (?) interrupt, then do normal flush.&n; *&n; * - Frame throttling, NV_fence:&n; *    - Drop marker irq&squot;s into command stream ahead of time.&n; *    - Wait on irq&squot;s with lock *not held*&n; *    - Check each for termination condition&n; *&n; * - Internally in cp_getbuffer, etc:&n; *    - as above, but wait with lock held???&n; *&n; * NOTE: These functions are misleadingly named -- the irq&squot;s aren&squot;t&n; * tied to dma at all, this is just a hangover from dri prehistory.&n; */
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
id|stat
suffix:semicolon
multiline_comment|/* Only consider the bits we&squot;re interested in - others could be used&n;&t; * outside the DRM&n;&t; */
id|stat
op_assign
id|RADEON_READ
c_func
(paren
id|RADEON_GEN_INT_STATUS
)paren
op_amp
(paren
id|RADEON_SW_INT_TEST
op_or
id|RADEON_CRTC_VBLANK_STAT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stat
)paren
r_return
id|IRQ_NONE
suffix:semicolon
multiline_comment|/* SW interrupt */
r_if
c_cond
(paren
id|stat
op_amp
id|RADEON_SW_INT_TEST
)paren
(brace
id|DRM_WAKEUP
c_func
(paren
op_amp
id|dev_priv-&gt;swi_queue
)paren
suffix:semicolon
)brace
multiline_comment|/* VBLANK interrupt */
r_if
c_cond
(paren
id|stat
op_amp
id|RADEON_CRTC_VBLANK_STAT
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;vbl_received
)paren
suffix:semicolon
id|DRM_WAKEUP
c_func
(paren
op_amp
id|dev-&gt;vbl_queue
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|vbl_send_signals
)paren
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/* Acknowledge interrupts we handle */
id|RADEON_WRITE
c_func
(paren
id|RADEON_GEN_INT_STATUS
comma
id|stat
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|radeon_acknowledge_irqs
r_static
id|__inline__
r_void
id|radeon_acknowledge_irqs
c_func
(paren
id|drm_radeon_private_t
op_star
id|dev_priv
)paren
(brace
id|u32
id|tmp
op_assign
id|RADEON_READ
c_func
(paren
id|RADEON_GEN_INT_STATUS
)paren
op_amp
(paren
id|RADEON_SW_INT_TEST_ACK
op_or
id|RADEON_CRTC_VBLANK_STAT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
id|RADEON_WRITE
c_func
(paren
id|RADEON_GEN_INT_STATUS
comma
id|tmp
)paren
suffix:semicolon
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
r_int
r_int
id|ret
suffix:semicolon
id|RING_LOCALS
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev_priv-&gt;swi_emitted
)paren
suffix:semicolon
id|ret
op_assign
id|atomic_read
c_func
(paren
op_amp
id|dev_priv-&gt;swi_emitted
)paren
suffix:semicolon
id|BEGIN_RING
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|OUT_RING_REG
c_func
(paren
id|RADEON_LAST_SWI_REG
comma
id|ret
)paren
suffix:semicolon
id|OUT_RING_REG
c_func
(paren
id|RADEON_GEN_INT_STATUS
comma
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
id|ret
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
id|swi_nr
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|RADEON_READ
c_func
(paren
id|RADEON_LAST_SWI_REG
)paren
op_ge
id|swi_nr
)paren
r_return
l_int|0
suffix:semicolon
id|dev_priv-&gt;stats.boxes
op_or_assign
id|RADEON_BOX_WAIT_IDLE
suffix:semicolon
multiline_comment|/* This is a hack to work around mysterious freezes on certain&n;&t; * systems:&n;&t; */
id|radeon_acknowledge_irqs
c_func
(paren
id|dev_priv
)paren
suffix:semicolon
id|DRM_WAIT_ON
c_func
(paren
id|ret
comma
id|dev_priv-&gt;swi_queue
comma
l_int|3
op_star
id|DRM_HZ
comma
id|RADEON_READ
c_func
(paren
id|RADEON_LAST_SWI_REG
)paren
op_ge
id|swi_nr
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
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
DECL|function|vblank_wait
r_int
id|DRM
c_func
(paren
id|vblank_wait
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
r_int
op_star
id|sequence
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
r_int
r_int
id|cur_vblank
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
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
id|radeon_acknowledge_irqs
c_func
(paren
id|dev_priv
)paren
suffix:semicolon
id|dev_priv-&gt;stats.boxes
op_or_assign
id|RADEON_BOX_WAIT_IDLE
suffix:semicolon
multiline_comment|/* Assume that the user has missed the current sequence number&n;&t; * by about a day rather than she wants to wait for years&n;&t; * using vertical blanks... &n;&t; */
id|DRM_WAIT_ON
c_func
(paren
id|ret
comma
id|dev-&gt;vbl_queue
comma
l_int|3
op_star
id|DRM_HZ
comma
(paren
(paren
(paren
id|cur_vblank
op_assign
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;vbl_received
)paren
)paren
op_minus
op_star
id|sequence
)paren
op_le
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
)paren
suffix:semicolon
op_star
id|sequence
op_assign
id|cur_vblank
suffix:semicolon
r_return
id|ret
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
comma
id|filp
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
id|__user
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
id|__user
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
multiline_comment|/* Disable *all* interrupts */
id|RADEON_WRITE
c_func
(paren
id|RADEON_GEN_INT_CNTL
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Clear bits if they&squot;re already high */
id|radeon_acknowledge_irqs
c_func
(paren
id|dev_priv
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
id|atomic_set
c_func
(paren
op_amp
id|dev_priv-&gt;swi_emitted
comma
l_int|0
)paren
suffix:semicolon
id|DRM_INIT_WAITQUEUE
c_func
(paren
op_amp
id|dev_priv-&gt;swi_queue
)paren
suffix:semicolon
multiline_comment|/* Turn on SW and VBL ints */
id|RADEON_WRITE
c_func
(paren
id|RADEON_GEN_INT_CNTL
comma
id|RADEON_CRTC_VBLANK_MASK
op_or
id|RADEON_SW_INT_ENABLE
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
r_if
c_cond
(paren
op_logical_neg
id|dev_priv
)paren
r_return
suffix:semicolon
multiline_comment|/* Disable *all* interrupts */
id|RADEON_WRITE
c_func
(paren
id|RADEON_GEN_INT_CNTL
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
