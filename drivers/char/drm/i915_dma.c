multiline_comment|/* i915_dma.c -- DMA support for the I915 -*- linux-c -*-&n; */
multiline_comment|/**************************************************************************&n; * &n; * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.&n; * All Rights Reserved.&n; * &n; **************************************************************************/
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm.h&quot;
macro_line|#include &quot;i915_drm.h&quot;
macro_line|#include &quot;i915_drv.h&quot;
DECL|variable|i915_ioctls
id|drm_ioctl_desc_t
id|i915_ioctls
(braket
)braket
op_assign
(brace
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_INIT
)paren
)braket
op_assign
(brace
id|i915_dma_init
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_FLUSH
)paren
)braket
op_assign
(brace
id|i915_flush_ioctl
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_FLIP
)paren
)braket
op_assign
(brace
id|i915_flip_bufs
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_BATCHBUFFER
)paren
)braket
op_assign
(brace
id|i915_batchbuffer
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_IRQ_EMIT
)paren
)braket
op_assign
(brace
id|i915_irq_emit
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_IRQ_WAIT
)paren
)braket
op_assign
(brace
id|i915_irq_wait
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_GETPARAM
)paren
)braket
op_assign
(brace
id|i915_getparam
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_SETPARAM
)paren
)braket
op_assign
(brace
id|i915_setparam
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_ALLOC
)paren
)braket
op_assign
(brace
id|i915_mem_alloc
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_FREE
)paren
)braket
op_assign
(brace
id|i915_mem_free
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_INIT_HEAP
)paren
)braket
op_assign
(brace
id|i915_mem_init_heap
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_I915_CMDBUFFER
)paren
)braket
op_assign
(brace
id|i915_cmdbuffer
comma
l_int|1
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|i915_max_ioctl
r_int
id|i915_max_ioctl
op_assign
id|DRM_ARRAY_SIZE
c_func
(paren
id|i915_ioctls
)paren
suffix:semicolon
multiline_comment|/* Really want an OS-independent resettable timer.  Would like to have&n; * this loop run for (eg) 3 sec, but have the timer reset every time&n; * the head pointer changes, so that EBUSY only happens if the ring&n; * actually stalls for (eg) 3 seconds.&n; */
DECL|function|i915_wait_ring
r_int
id|i915_wait_ring
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|n
comma
r_const
r_char
op_star
id|caller
)paren
(brace
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_i915_ring_buffer_t
op_star
id|ring
op_assign
op_amp
(paren
id|dev_priv-&gt;ring
)paren
suffix:semicolon
id|u32
id|last_head
op_assign
id|I915_READ
c_func
(paren
id|LP_RING
op_plus
id|RING_HEAD
)paren
op_amp
id|HEAD_ADDR
suffix:semicolon
r_int
id|i
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
l_int|10000
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ring-&gt;head
op_assign
id|I915_READ
c_func
(paren
id|LP_RING
op_plus
id|RING_HEAD
)paren
op_amp
id|HEAD_ADDR
suffix:semicolon
id|ring-&gt;space
op_assign
id|ring-&gt;head
op_minus
(paren
id|ring-&gt;tail
op_plus
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ring-&gt;space
OL
l_int|0
)paren
id|ring-&gt;space
op_add_assign
id|ring-&gt;Size
suffix:semicolon
r_if
c_cond
(paren
id|ring-&gt;space
op_ge
id|n
)paren
r_return
l_int|0
suffix:semicolon
id|dev_priv-&gt;sarea_priv-&gt;perf_boxes
op_or_assign
id|I915_BOX_WAIT
suffix:semicolon
r_if
c_cond
(paren
id|ring-&gt;head
op_ne
id|last_head
)paren
id|i
op_assign
l_int|0
suffix:semicolon
id|last_head
op_assign
id|ring-&gt;head
suffix:semicolon
)brace
r_return
id|DRM_ERR
c_func
(paren
id|EBUSY
)paren
suffix:semicolon
)brace
DECL|function|i915_kernel_lost_context
r_void
id|i915_kernel_lost_context
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
id|drm_i915_ring_buffer_t
op_star
id|ring
op_assign
op_amp
(paren
id|dev_priv-&gt;ring
)paren
suffix:semicolon
id|ring-&gt;head
op_assign
id|I915_READ
c_func
(paren
id|LP_RING
op_plus
id|RING_HEAD
)paren
op_amp
id|HEAD_ADDR
suffix:semicolon
id|ring-&gt;tail
op_assign
id|I915_READ
c_func
(paren
id|LP_RING
op_plus
id|RING_TAIL
)paren
op_amp
id|TAIL_ADDR
suffix:semicolon
id|ring-&gt;space
op_assign
id|ring-&gt;head
op_minus
(paren
id|ring-&gt;tail
op_plus
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ring-&gt;space
OL
l_int|0
)paren
id|ring-&gt;space
op_add_assign
id|ring-&gt;Size
suffix:semicolon
r_if
c_cond
(paren
id|ring-&gt;head
op_eq
id|ring-&gt;tail
)paren
id|dev_priv-&gt;sarea_priv-&gt;perf_boxes
op_or_assign
id|I915_BOX_RING_EMPTY
suffix:semicolon
)brace
DECL|function|i915_dma_cleanup
r_int
id|i915_dma_cleanup
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
multiline_comment|/* Make sure interrupts are disabled here because the uninstall ioctl&n;&t; * may not have been called from userspace and after dev_private&n;&t; * is freed, it&squot;s too late.&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;irq
)paren
id|drm_irq_uninstall
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;dev_private
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
id|dev_priv-&gt;ring.virtual_start
)paren
(brace
id|drm_core_ioremapfree
c_func
(paren
op_amp
id|dev_priv-&gt;ring.map
comma
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev_priv-&gt;hw_status_page
)paren
(brace
id|drm_pci_free
c_func
(paren
id|dev
comma
id|PAGE_SIZE
comma
id|dev_priv-&gt;hw_status_page
comma
id|dev_priv-&gt;dma_status_page
)paren
suffix:semicolon
multiline_comment|/* Need to rewrite hardware status page */
id|I915_WRITE
c_func
(paren
l_int|0x02080
comma
l_int|0x1ffff000
)paren
suffix:semicolon
)brace
id|drm_free
(paren
id|dev-&gt;dev_private
comma
r_sizeof
(paren
id|drm_i915_private_t
)paren
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|dev-&gt;dev_private
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i915_initialize
r_static
r_int
id|i915_initialize
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|drm_i915_private_t
op_star
id|dev_priv
comma
id|drm_i915_init_t
op_star
id|init
)paren
(brace
id|memset
c_func
(paren
id|dev_priv
comma
l_int|0
comma
r_sizeof
(paren
id|drm_i915_private_t
)paren
)paren
suffix:semicolon
id|DRM_GETSAREA
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_priv-&gt;sarea
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;can not find sarea!&bslash;n&quot;
)paren
suffix:semicolon
id|dev-&gt;dev_private
op_assign
(paren
r_void
op_star
)paren
id|dev_priv
suffix:semicolon
id|i915_dma_cleanup
c_func
(paren
id|dev
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
id|dev_priv-&gt;mmio_map
op_assign
id|drm_core_findmap
c_func
(paren
id|dev
comma
id|init-&gt;mmio_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_priv-&gt;mmio_map
)paren
(brace
id|dev-&gt;dev_private
op_assign
(paren
r_void
op_star
)paren
id|dev_priv
suffix:semicolon
id|i915_dma_cleanup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|DRM_ERROR
c_func
(paren
l_string|&quot;can not find mmio map!&bslash;n&quot;
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
id|dev_priv-&gt;sarea_priv
op_assign
(paren
id|drm_i915_sarea_t
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|dev_priv-&gt;sarea-&gt;handle
op_plus
id|init-&gt;sarea_priv_offset
)paren
suffix:semicolon
id|dev_priv-&gt;ring.Start
op_assign
id|init-&gt;ring_start
suffix:semicolon
id|dev_priv-&gt;ring.End
op_assign
id|init-&gt;ring_end
suffix:semicolon
id|dev_priv-&gt;ring.Size
op_assign
id|init-&gt;ring_size
suffix:semicolon
id|dev_priv-&gt;ring.tail_mask
op_assign
id|dev_priv-&gt;ring.Size
op_minus
l_int|1
suffix:semicolon
id|dev_priv-&gt;ring.map.offset
op_assign
id|init-&gt;ring_start
suffix:semicolon
id|dev_priv-&gt;ring.map.size
op_assign
id|init-&gt;ring_size
suffix:semicolon
id|dev_priv-&gt;ring.map.type
op_assign
l_int|0
suffix:semicolon
id|dev_priv-&gt;ring.map.flags
op_assign
l_int|0
suffix:semicolon
id|dev_priv-&gt;ring.map.mtrr
op_assign
l_int|0
suffix:semicolon
id|drm_core_ioremap
c_func
(paren
op_amp
id|dev_priv-&gt;ring.map
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv-&gt;ring.map.handle
op_eq
l_int|NULL
)paren
(brace
id|dev-&gt;dev_private
op_assign
(paren
r_void
op_star
)paren
id|dev_priv
suffix:semicolon
id|i915_dma_cleanup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|DRM_ERROR
c_func
(paren
l_string|&quot;can not ioremap virtual address for&quot;
l_string|&quot; ring buffer&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|ENOMEM
)paren
suffix:semicolon
)brace
id|dev_priv-&gt;ring.virtual_start
op_assign
id|dev_priv-&gt;ring.map.handle
suffix:semicolon
id|dev_priv-&gt;back_offset
op_assign
id|init-&gt;back_offset
suffix:semicolon
id|dev_priv-&gt;front_offset
op_assign
id|init-&gt;front_offset
suffix:semicolon
id|dev_priv-&gt;current_page
op_assign
l_int|0
suffix:semicolon
id|dev_priv-&gt;sarea_priv-&gt;pf_current_page
op_assign
id|dev_priv-&gt;current_page
suffix:semicolon
multiline_comment|/* We are using separate values as placeholders for mechanisms for&n;&t; * private backbuffer/depthbuffer usage.&n;&t; */
id|dev_priv-&gt;use_mi_batchbuffer_start
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Allow hardware batchbuffers unless told otherwise.&n;&t; */
id|dev_priv-&gt;allow_batchbuffer
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Program Hardware Status Page */
id|dev_priv-&gt;hw_status_page
op_assign
id|drm_pci_alloc
c_func
(paren
id|dev
comma
id|PAGE_SIZE
comma
id|PAGE_SIZE
comma
l_int|0xffffffff
comma
op_amp
id|dev_priv-&gt;dma_status_page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_priv-&gt;hw_status_page
)paren
(brace
id|dev-&gt;dev_private
op_assign
(paren
r_void
op_star
)paren
id|dev_priv
suffix:semicolon
id|i915_dma_cleanup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|DRM_ERROR
c_func
(paren
l_string|&quot;Can not allocate hardware status page&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|ENOMEM
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev_priv-&gt;hw_status_page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;hw status page @ %p&bslash;n&quot;
comma
id|dev_priv-&gt;hw_status_page
)paren
suffix:semicolon
id|I915_WRITE
c_func
(paren
l_int|0x02080
comma
id|dev_priv-&gt;dma_status_page
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;Enabled hardware status page&bslash;n&quot;
)paren
suffix:semicolon
id|dev-&gt;dev_private
op_assign
(paren
r_void
op_star
)paren
id|dev_priv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i915_resume
r_static
r_int
id|i915_resume
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
op_logical_neg
id|dev_priv-&gt;sarea
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;can not find sarea!&bslash;n&quot;
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
r_if
c_cond
(paren
op_logical_neg
id|dev_priv-&gt;mmio_map
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;can not find mmio map!&bslash;n&quot;
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
r_if
c_cond
(paren
id|dev_priv-&gt;ring.map.handle
op_eq
l_int|NULL
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;can not ioremap virtual address for&quot;
l_string|&quot; ring buffer&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|ENOMEM
)paren
suffix:semicolon
)brace
multiline_comment|/* Program Hardware Status Page */
r_if
c_cond
(paren
op_logical_neg
id|dev_priv-&gt;hw_status_page
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Can not find hardware status page&bslash;n&quot;
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
id|DRM_DEBUG
c_func
(paren
l_string|&quot;hw status page @ %p&bslash;n&quot;
comma
id|dev_priv-&gt;hw_status_page
)paren
suffix:semicolon
id|I915_WRITE
c_func
(paren
l_int|0x02080
comma
id|dev_priv-&gt;dma_status_page
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;Enabled hardware status page&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i915_dma_init
r_int
id|i915_dma_init
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
suffix:semicolon
id|drm_i915_init_t
id|init
suffix:semicolon
r_int
id|retcode
op_assign
l_int|0
suffix:semicolon
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|init
comma
(paren
id|drm_i915_init_t
id|__user
op_star
)paren
id|data
comma
r_sizeof
(paren
id|init
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|init.func
)paren
(brace
r_case
id|I915_INIT_DMA
suffix:colon
id|dev_priv
op_assign
id|drm_alloc
(paren
r_sizeof
(paren
id|drm_i915_private_t
)paren
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv
op_eq
l_int|NULL
)paren
r_return
id|DRM_ERR
c_func
(paren
id|ENOMEM
)paren
suffix:semicolon
id|retcode
op_assign
id|i915_initialize
c_func
(paren
id|dev
comma
id|dev_priv
comma
op_amp
id|init
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I915_CLEANUP_DMA
suffix:colon
id|retcode
op_assign
id|i915_dma_cleanup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I915_RESUME_DMA
suffix:colon
id|retcode
op_assign
id|i915_resume
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retcode
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|retcode
suffix:semicolon
)brace
multiline_comment|/* Implement basically the same security restrictions as hardware does&n; * for MI_BATCH_NON_SECURE.  These can be made stricter at any time.&n; *&n; * Most of the calculations below involve calculating the size of a&n; * particular instruction.  It&squot;s important to get the size right as&n; * that tells us where the next instruction to check is.  Any illegal&n; * instruction detected will be given a size of zero, which is a&n; * signal to abort the rest of the buffer.&n; */
DECL|function|do_validate_cmd
r_static
r_int
id|do_validate_cmd
c_func
(paren
r_int
id|cmd
)paren
(brace
r_switch
c_cond
(paren
(paren
(paren
id|cmd
op_rshift
l_int|29
)paren
op_amp
l_int|0x7
)paren
)paren
(brace
r_case
l_int|0x0
suffix:colon
r_switch
c_cond
(paren
(paren
id|cmd
op_rshift
l_int|23
)paren
op_amp
l_int|0x3f
)paren
(brace
r_case
l_int|0x0
suffix:colon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* MI_NOOP */
r_case
l_int|0x4
suffix:colon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* MI_FLUSH */
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* disallow everything else */
)brace
r_break
suffix:semicolon
r_case
l_int|0x1
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* reserved */
r_case
l_int|0x2
suffix:colon
r_return
(paren
id|cmd
op_amp
l_int|0xff
)paren
op_plus
l_int|2
suffix:semicolon
multiline_comment|/* 2d commands */
r_case
l_int|0x3
suffix:colon
r_if
c_cond
(paren
(paren
(paren
id|cmd
op_rshift
l_int|24
)paren
op_amp
l_int|0x1f
)paren
op_le
l_int|0x18
)paren
r_return
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|cmd
op_rshift
l_int|24
)paren
op_amp
l_int|0x1f
)paren
(brace
r_case
l_int|0x1c
suffix:colon
r_return
l_int|1
suffix:semicolon
r_case
l_int|0x1d
suffix:colon
r_switch
c_cond
(paren
(paren
id|cmd
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
(brace
r_case
l_int|0x3
suffix:colon
r_return
(paren
id|cmd
op_amp
l_int|0x1f
)paren
op_plus
l_int|2
suffix:semicolon
r_case
l_int|0x4
suffix:colon
r_return
(paren
id|cmd
op_amp
l_int|0xf
)paren
op_plus
l_int|2
suffix:semicolon
r_default
suffix:colon
r_return
(paren
id|cmd
op_amp
l_int|0xffff
)paren
op_plus
l_int|2
suffix:semicolon
)brace
r_case
l_int|0x1e
suffix:colon
r_if
c_cond
(paren
id|cmd
op_amp
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
r_return
(paren
id|cmd
op_amp
l_int|0xffff
)paren
op_plus
l_int|1
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
r_case
l_int|0x1f
suffix:colon
r_if
c_cond
(paren
(paren
id|cmd
op_amp
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
op_eq
l_int|0
)paren
multiline_comment|/* inline vertices */
r_return
(paren
id|cmd
op_amp
l_int|0x1ffff
)paren
op_plus
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmd
op_amp
(paren
l_int|1
op_lshift
l_int|17
)paren
)paren
multiline_comment|/* indirect random */
r_if
c_cond
(paren
(paren
id|cmd
op_amp
l_int|0xffff
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* unknown length, too hard */
r_else
r_return
(paren
(paren
(paren
id|cmd
op_amp
l_int|0xffff
)paren
op_plus
l_int|1
)paren
op_div
l_int|2
)paren
op_plus
l_int|1
suffix:semicolon
r_else
r_return
l_int|2
suffix:semicolon
multiline_comment|/* indirect sequential */
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|validate_cmd
r_static
r_int
id|validate_cmd
c_func
(paren
r_int
id|cmd
)paren
(brace
r_int
id|ret
op_assign
id|do_validate_cmd
c_func
(paren
id|cmd
)paren
suffix:semicolon
multiline_comment|/* &t;printk(&quot;validate_cmd( %x ): %d&bslash;n&quot;, cmd, ret); */
r_return
id|ret
suffix:semicolon
)brace
DECL|function|i915_emit_cmds
r_static
r_int
id|i915_emit_cmds
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|__user
op_star
id|buffer
comma
r_int
id|dwords
)paren
(brace
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
r_int
id|i
suffix:semicolon
id|RING_LOCALS
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
id|dwords
suffix:semicolon
)paren
(brace
r_int
id|cmd
comma
id|sz
suffix:semicolon
r_if
c_cond
(paren
id|DRM_COPY_FROM_USER_UNCHECKED
c_func
(paren
op_amp
id|cmd
comma
op_amp
id|buffer
(braket
id|i
)braket
comma
r_sizeof
(paren
id|cmd
)paren
)paren
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* &t;&t;printk(&quot;%d/%d &quot;, i, dwords); */
r_if
c_cond
(paren
(paren
id|sz
op_assign
id|validate_cmd
c_func
(paren
id|cmd
)paren
)paren
op_eq
l_int|0
op_logical_or
id|i
op_plus
id|sz
OG
id|dwords
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|BEGIN_LP_RING
c_func
(paren
id|sz
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_while
c_loop
(paren
op_increment
id|i
comma
op_decrement
id|sz
)paren
(brace
r_if
c_cond
(paren
id|DRM_COPY_FROM_USER_UNCHECKED
c_func
(paren
op_amp
id|cmd
comma
op_amp
id|buffer
(braket
id|i
)braket
comma
r_sizeof
(paren
id|cmd
)paren
)paren
)paren
(brace
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
id|OUT_RING
c_func
(paren
id|cmd
)paren
suffix:semicolon
)brace
id|ADVANCE_LP_RING
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i915_emit_box
r_static
r_int
id|i915_emit_box
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|drm_clip_rect_t
id|__user
op_star
id|boxes
comma
r_int
id|i
comma
r_int
id|DR1
comma
r_int
id|DR4
)paren
(brace
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_clip_rect_t
id|box
suffix:semicolon
id|RING_LOCALS
suffix:semicolon
r_if
c_cond
(paren
id|DRM_COPY_FROM_USER_UNCHECKED
c_func
(paren
op_amp
id|box
comma
op_amp
id|boxes
(braket
id|i
)braket
comma
r_sizeof
(paren
id|box
)paren
)paren
)paren
(brace
r_return
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|box.y2
op_le
id|box.y1
op_logical_or
id|box.x2
op_le
id|box.x1
op_logical_or
id|box.y2
op_le
l_int|0
op_logical_or
id|box.x2
op_le
l_int|0
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Bad box %d,%d..%d,%d&bslash;n&quot;
comma
id|box.x1
comma
id|box.y1
comma
id|box.x2
comma
id|box.y2
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
id|BEGIN_LP_RING
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|GFX_OP_DRAWRECT_INFO
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|DR1
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
(paren
id|box.x1
op_amp
l_int|0xffff
)paren
op_or
(paren
id|box.y1
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
(paren
(paren
id|box.x2
op_minus
l_int|1
)paren
op_amp
l_int|0xffff
)paren
op_or
(paren
(paren
id|box.y2
op_minus
l_int|1
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|DR4
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ADVANCE_LP_RING
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i915_dispatch_cmdbuffer
r_static
r_int
id|i915_dispatch_cmdbuffer
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|drm_i915_cmdbuffer_t
op_star
id|cmd
)paren
(brace
r_int
id|nbox
op_assign
id|cmd-&gt;num_cliprects
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|count
comma
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;sz
op_amp
l_int|0x3
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;alignment&quot;
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
id|i915_kernel_lost_context
c_func
(paren
id|dev
)paren
suffix:semicolon
id|count
op_assign
id|nbox
ques
c_cond
id|nbox
suffix:colon
l_int|1
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
id|nbox
)paren
(brace
id|ret
op_assign
id|i915_emit_box
c_func
(paren
id|dev
comma
id|cmd-&gt;cliprects
comma
id|i
comma
id|cmd-&gt;DR1
comma
id|cmd-&gt;DR4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|i915_emit_cmds
c_func
(paren
id|dev
comma
(paren
r_int
id|__user
op_star
)paren
id|cmd-&gt;buf
comma
id|cmd-&gt;sz
op_div
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i915_dispatch_batchbuffer
r_static
r_int
id|i915_dispatch_batchbuffer
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|drm_i915_batchbuffer_t
op_star
id|batch
)paren
(brace
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_clip_rect_t
id|__user
op_star
id|boxes
op_assign
id|batch-&gt;cliprects
suffix:semicolon
r_int
id|nbox
op_assign
id|batch-&gt;num_cliprects
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|count
suffix:semicolon
id|RING_LOCALS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|batch-&gt;start
op_or
id|batch-&gt;used
)paren
op_amp
l_int|0x7
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;alignment&quot;
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
id|i915_kernel_lost_context
c_func
(paren
id|dev
)paren
suffix:semicolon
id|count
op_assign
id|nbox
ques
c_cond
id|nbox
suffix:colon
l_int|1
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
id|nbox
)paren
(brace
r_int
id|ret
op_assign
id|i915_emit_box
c_func
(paren
id|dev
comma
id|boxes
comma
id|i
comma
id|batch-&gt;DR1
comma
id|batch-&gt;DR4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev_priv-&gt;use_mi_batchbuffer_start
)paren
(brace
id|BEGIN_LP_RING
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|MI_BATCH_BUFFER_START
op_or
(paren
l_int|2
op_lshift
l_int|6
)paren
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|batch-&gt;start
op_or
id|MI_BATCH_NON_SECURE
)paren
suffix:semicolon
id|ADVANCE_LP_RING
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|BEGIN_LP_RING
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|MI_BATCH_BUFFER
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|batch-&gt;start
op_or
id|MI_BATCH_NON_SECURE
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|batch-&gt;start
op_plus
id|batch-&gt;used
op_minus
l_int|4
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ADVANCE_LP_RING
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|dev_priv-&gt;sarea_priv-&gt;last_enqueue
op_assign
id|dev_priv-&gt;counter
op_increment
suffix:semicolon
id|BEGIN_LP_RING
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|CMD_STORE_DWORD_IDX
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|dev_priv-&gt;counter
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ADVANCE_LP_RING
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i915_dispatch_flip
r_static
r_int
id|i915_dispatch_flip
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
id|RING_LOCALS
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%s: page=%d pfCurrentPage=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dev_priv-&gt;current_page
comma
id|dev_priv-&gt;sarea_priv-&gt;pf_current_page
)paren
suffix:semicolon
id|i915_kernel_lost_context
c_func
(paren
id|dev
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
id|INST_PARSER_CLIENT
op_or
id|INST_OP_FLUSH
op_or
id|INST_FLUSH_MAP_CACHE
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ADVANCE_LP_RING
c_func
(paren
)paren
suffix:semicolon
id|BEGIN_LP_RING
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|CMD_OP_DISPLAYBUFFER_INFO
op_or
id|ASYNC_FLIP
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv-&gt;current_page
op_eq
l_int|0
)paren
(brace
id|OUT_RING
c_func
(paren
id|dev_priv-&gt;back_offset
)paren
suffix:semicolon
id|dev_priv-&gt;current_page
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|OUT_RING
c_func
(paren
id|dev_priv-&gt;front_offset
)paren
suffix:semicolon
id|dev_priv-&gt;current_page
op_assign
l_int|0
suffix:semicolon
)brace
id|OUT_RING
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ADVANCE_LP_RING
c_func
(paren
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
id|MI_WAIT_FOR_EVENT
op_or
id|MI_WAIT_FOR_PLANE_A_FLIP
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ADVANCE_LP_RING
c_func
(paren
)paren
suffix:semicolon
id|dev_priv-&gt;sarea_priv-&gt;last_enqueue
op_assign
id|dev_priv-&gt;counter
op_increment
suffix:semicolon
id|BEGIN_LP_RING
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|CMD_STORE_DWORD_IDX
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
id|dev_priv-&gt;counter
)paren
suffix:semicolon
id|OUT_RING
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ADVANCE_LP_RING
c_func
(paren
)paren
suffix:semicolon
id|dev_priv-&gt;sarea_priv-&gt;pf_current_page
op_assign
id|dev_priv-&gt;current_page
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i915_quiescent
r_static
r_int
id|i915_quiescent
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
id|i915_kernel_lost_context
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|i915_wait_ring
c_func
(paren
id|dev
comma
id|dev_priv-&gt;ring.Size
op_minus
l_int|8
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
DECL|function|i915_flush_ioctl
r_int
id|i915_flush_ioctl
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|LOCK_TEST_WITH_RETURN
c_func
(paren
id|dev
comma
id|filp
)paren
suffix:semicolon
r_return
id|i915_quiescent
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|i915_batchbuffer
r_int
id|i915_batchbuffer
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
(paren
id|drm_i915_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
id|u32
op_star
id|hw_status
op_assign
id|dev_priv-&gt;hw_status_page
suffix:semicolon
id|drm_i915_sarea_t
op_star
id|sarea_priv
op_assign
(paren
id|drm_i915_sarea_t
op_star
)paren
id|dev_priv-&gt;sarea_priv
suffix:semicolon
id|drm_i915_batchbuffer_t
id|batch
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_priv-&gt;allow_batchbuffer
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Batchbuffer ioctl disabled&bslash;n&quot;
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
id|batch
comma
(paren
id|drm_i915_batchbuffer_t
id|__user
op_star
)paren
id|data
comma
r_sizeof
(paren
id|batch
)paren
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;i915 batchbuffer, start %x used %d cliprects %d&bslash;n&quot;
comma
id|batch.start
comma
id|batch.used
comma
id|batch.num_cliprects
)paren
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
id|batch.num_cliprects
op_logical_and
id|DRM_VERIFYAREA_READ
c_func
(paren
id|batch.cliprects
comma
id|batch.num_cliprects
op_star
r_sizeof
(paren
id|drm_clip_rect_t
)paren
)paren
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EFAULT
)paren
suffix:semicolon
id|ret
op_assign
id|i915_dispatch_batchbuffer
c_func
(paren
id|dev
comma
op_amp
id|batch
)paren
suffix:semicolon
id|sarea_priv-&gt;last_dispatch
op_assign
(paren
r_int
)paren
id|hw_status
(braket
l_int|5
)braket
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|i915_cmdbuffer
r_int
id|i915_cmdbuffer
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
(paren
id|drm_i915_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
id|u32
op_star
id|hw_status
op_assign
id|dev_priv-&gt;hw_status_page
suffix:semicolon
id|drm_i915_sarea_t
op_star
id|sarea_priv
op_assign
(paren
id|drm_i915_sarea_t
op_star
)paren
id|dev_priv-&gt;sarea_priv
suffix:semicolon
id|drm_i915_cmdbuffer_t
id|cmdbuf
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|cmdbuf
comma
(paren
id|drm_i915_cmdbuffer_t
id|__user
op_star
)paren
id|data
comma
r_sizeof
(paren
id|cmdbuf
)paren
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;i915 cmdbuffer, buf %p sz %d cliprects %d&bslash;n&quot;
comma
id|cmdbuf.buf
comma
id|cmdbuf.sz
comma
id|cmdbuf.num_cliprects
)paren
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
id|cmdbuf.num_cliprects
op_logical_and
id|DRM_VERIFYAREA_READ
c_func
(paren
id|cmdbuf.cliprects
comma
id|cmdbuf.num_cliprects
op_star
r_sizeof
(paren
id|drm_clip_rect_t
)paren
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Fault accessing cliprects&bslash;n&quot;
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
id|ret
op_assign
id|i915_dispatch_cmdbuffer
c_func
(paren
id|dev
comma
op_amp
id|cmdbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;i915_dispatch_cmdbuffer failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|sarea_priv-&gt;last_dispatch
op_assign
(paren
r_int
)paren
id|hw_status
(braket
l_int|5
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i915_do_cleanup_pageflip
r_int
id|i915_do_cleanup_pageflip
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
id|dev_priv-&gt;current_page
op_ne
l_int|0
)paren
id|i915_dispatch_flip
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i915_flip_bufs
r_int
id|i915_flip_bufs
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|LOCK_TEST_WITH_RETURN
c_func
(paren
id|dev
comma
id|filp
)paren
suffix:semicolon
r_return
id|i915_dispatch_flip
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|i915_getparam
r_int
id|i915_getparam
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
id|drm_i915_getparam_t
id|param
suffix:semicolon
r_int
id|value
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
id|param
comma
(paren
id|drm_i915_getparam_t
id|__user
op_star
)paren
id|data
comma
r_sizeof
(paren
id|param
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|param.param
)paren
(brace
r_case
id|I915_PARAM_IRQ_ACTIVE
suffix:colon
id|value
op_assign
id|dev-&gt;irq
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I915_PARAM_ALLOW_BATCHBUFFER
suffix:colon
id|value
op_assign
id|dev_priv-&gt;allow_batchbuffer
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|DRM_ERROR
c_func
(paren
l_string|&quot;Unkown parameter %d&bslash;n&quot;
comma
id|param.param
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
r_if
c_cond
(paren
id|DRM_COPY_TO_USER
c_func
(paren
id|param.value
comma
op_amp
id|value
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
l_string|&quot;DRM_COPY_TO_USER failed&bslash;n&quot;
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
DECL|function|i915_setparam
r_int
id|i915_setparam
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
id|drm_i915_setparam_t
id|param
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
id|param
comma
(paren
id|drm_i915_setparam_t
id|__user
op_star
)paren
id|data
comma
r_sizeof
(paren
id|param
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|param.param
)paren
(brace
r_case
id|I915_SETPARAM_USE_MI_BATCHBUFFER_START
suffix:colon
id|dev_priv-&gt;use_mi_batchbuffer_start
op_assign
id|param.value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I915_SETPARAM_TEX_LRU_LOG_GRANULARITY
suffix:colon
id|dev_priv-&gt;tex_lru_log_granularity
op_assign
id|param.value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I915_SETPARAM_ALLOW_BATCHBUFFER
suffix:colon
id|dev_priv-&gt;allow_batchbuffer
op_assign
id|param.value
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|DRM_ERROR
c_func
(paren
l_string|&quot;unknown parameter %d&bslash;n&quot;
comma
id|param.param
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i915_driver_pretakedown
r_void
id|i915_driver_pretakedown
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;dev_private
)paren
(brace
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|i915_mem_takedown
c_func
(paren
op_amp
(paren
id|dev_priv-&gt;agp_heap
)paren
)paren
suffix:semicolon
)brace
id|i915_dma_cleanup
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|i915_driver_prerelease
r_void
id|i915_driver_prerelease
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|DRMFILE
id|filp
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;dev_private
)paren
(brace
id|drm_i915_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|i915_mem_release
c_func
(paren
id|dev
comma
id|filp
comma
id|dev_priv-&gt;agp_heap
)paren
suffix:semicolon
)brace
)brace
eof
