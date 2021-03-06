multiline_comment|/* i915_dma.c -- DMA support for the I915 -*- linux-c -*-&n; */
multiline_comment|/**************************************************************************&n; * &n; * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.&n; * All Rights Reserved.&n; * &n; **************************************************************************/
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm.h&quot;
macro_line|#include &quot;i915_drm.h&quot;
macro_line|#include &quot;i915_drv.h&quot;
DECL|macro|USER_INT_FLAG
mdefine_line|#define USER_INT_FLAG 0x2
DECL|macro|MAX_NOPID
mdefine_line|#define MAX_NOPID ((u32)~0)
DECL|macro|READ_BREADCRUMB
mdefine_line|#define READ_BREADCRUMB(dev_priv)  (((u32*)(dev_priv-&gt;hw_status_page))[5])
DECL|function|i915_driver_irq_handler
id|irqreturn_t
id|i915_driver_irq_handler
c_func
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
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_i915_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
id|u16
id|temp
suffix:semicolon
id|temp
op_assign
id|I915_READ16
c_func
(paren
id|I915REG_INT_IDENTITY_R
)paren
suffix:semicolon
id|temp
op_and_assign
id|USER_INT_FLAG
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%s flag=%08x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_eq
l_int|0
)paren
r_return
id|IRQ_NONE
suffix:semicolon
id|I915_WRITE16
c_func
(paren
id|I915REG_INT_IDENTITY_R
comma
id|temp
)paren
suffix:semicolon
id|DRM_WAKEUP
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
DECL|function|i915_emit_irq
r_int
id|i915_emit_irq
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|u32
id|ret
suffix:semicolon
id|RING_LOCALS
suffix:semicolon
id|i915_kernel_lost_context
c_func
(paren
id|dev
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ret
op_assign
id|dev_priv-&gt;counter
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
id|ret
suffix:semicolon
)brace
DECL|function|i915_wait_irq
r_int
id|i915_wait_irq
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
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_i915_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%s irq_nr=%d breadcrumb=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq_nr
comma
id|READ_BREADCRUMB
c_func
(paren
id|dev_priv
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|READ_BREADCRUMB
c_func
(paren
id|dev_priv
)paren
op_ge
id|irq_nr
)paren
r_return
l_int|0
suffix:semicolon
id|dev_priv-&gt;sarea_priv-&gt;perf_boxes
op_or_assign
id|I915_BOX_WAIT
suffix:semicolon
id|DRM_WAIT_ON
c_func
(paren
id|ret
comma
id|dev_priv-&gt;irq_queue
comma
l_int|3
op_star
id|DRM_HZ
comma
id|READ_BREADCRUMB
c_func
(paren
id|dev_priv
)paren
op_ge
id|irq_nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|DRM_ERR
c_func
(paren
id|EBUSY
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;%s: EBUSY -- rec: %d emitted: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|READ_BREADCRUMB
c_func
(paren
id|dev_priv
)paren
comma
(paren
r_int
)paren
id|dev_priv-&gt;counter
)paren
suffix:semicolon
)brace
id|dev_priv-&gt;sarea_priv-&gt;last_dispatch
op_assign
id|READ_BREADCRUMB
c_func
(paren
id|dev_priv
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Needs the lock as it touches the ring.&n; */
DECL|function|i915_irq_emit
r_int
id|i915_irq_emit
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_i915_irq_emit_t
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
id|drm_i915_irq_emit_t
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
id|i915_emit_irq
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
DECL|function|i915_irq_wait
r_int
id|i915_irq_wait
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_i915_irq_wait_t
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
id|drm_i915_irq_wait_t
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
id|i915_wait_irq
c_func
(paren
id|dev
comma
id|irqwait.irq_seq
)paren
suffix:semicolon
)brace
multiline_comment|/* drm_dma.h hooks&n;*/
DECL|function|i915_driver_irq_preinstall
r_void
id|i915_driver_irq_preinstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_i915_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
id|I915_WRITE16
c_func
(paren
id|I915REG_HWSTAM
comma
l_int|0xfffe
)paren
suffix:semicolon
id|I915_WRITE16
c_func
(paren
id|I915REG_INT_MASK_R
comma
l_int|0x0
)paren
suffix:semicolon
id|I915_WRITE16
c_func
(paren
id|I915REG_INT_ENABLE_R
comma
l_int|0x0
)paren
suffix:semicolon
)brace
DECL|function|i915_driver_irq_postinstall
r_void
id|i915_driver_irq_postinstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_i915_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
id|I915_WRITE16
c_func
(paren
id|I915REG_INT_ENABLE_R
comma
id|USER_INT_FLAG
)paren
suffix:semicolon
id|DRM_INIT_WAITQUEUE
c_func
(paren
op_amp
id|dev_priv-&gt;irq_queue
)paren
suffix:semicolon
)brace
DECL|function|i915_driver_irq_uninstall
r_void
id|i915_driver_irq_uninstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_i915_private_t
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
id|I915_WRITE16
c_func
(paren
id|I915REG_HWSTAM
comma
l_int|0xffff
)paren
suffix:semicolon
id|I915_WRITE16
c_func
(paren
id|I915REG_INT_MASK_R
comma
l_int|0xffff
)paren
suffix:semicolon
id|I915_WRITE16
c_func
(paren
id|I915REG_INT_ENABLE_R
comma
l_int|0x0
)paren
suffix:semicolon
)brace
eof
