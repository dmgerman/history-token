multiline_comment|/* i915.h -- Intel I915 DRM template customization -*- linux-c -*-&n; */
multiline_comment|/**************************************************************************&n; * &n; * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.&n; * All Rights Reserved.&n; * &n; **************************************************************************/
macro_line|#ifndef __I915_H__
DECL|macro|__I915_H__
mdefine_line|#define __I915_H__
multiline_comment|/* This remains constant for all DRM template files.&n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) i915_##x
multiline_comment|/* General customization:&n; */
DECL|macro|__HAVE_AGP
mdefine_line|#define __HAVE_AGP&t;&t;1
DECL|macro|__MUST_HAVE_AGP
mdefine_line|#define __MUST_HAVE_AGP&t;&t;1
DECL|macro|__HAVE_MTRR
mdefine_line|#define __HAVE_MTRR&t;&t;1
DECL|macro|__HAVE_CTX_BITMAP
mdefine_line|#define __HAVE_CTX_BITMAP&t;1
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;Tungsten Graphics, Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;i915&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;Intel Graphics&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20040405&quot;
multiline_comment|/* Interface history:&n; *&n; * 1.1: Original.&n; */
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;1
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;0
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I915_INIT)]   = { i915_dma_init,    1, 1 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I915_FLUSH)]  = { i915_flush_ioctl, 1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I915_FLIP)]   = { i915_flip_bufs,   1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I915_BATCHBUFFER)] = { i915_batchbuffer, 1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I915_IRQ_EMIT)] = { i915_irq_emit,  1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I915_IRQ_WAIT)] = { i915_irq_wait,  1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I915_GETPARAM)] = { i915_getparam,  1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I915_SETPARAM)] = { i915_setparam,  1, 1 }, &bslash;&n;        [DRM_IOCTL_NR(DRM_IOCTL_I915_ALLOC)]   = { i915_mem_alloc,  1, 0 }, &bslash;&n;        [DRM_IOCTL_NR(DRM_IOCTL_I915_FREE)]    = { i915_mem_free,    1, 0 }, &bslash;&n;        [DRM_IOCTL_NR(DRM_IOCTL_I915_INIT_HEAP)] = { i915_mem_init_heap, 1, 1 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I915_CMDBUFFER)] = { i915_cmdbuffer, 1, 0 }
DECL|macro|__HAVE_COUNTERS
mdefine_line|#define __HAVE_COUNTERS         4
DECL|macro|__HAVE_COUNTER6
mdefine_line|#define __HAVE_COUNTER6         _DRM_STAT_IRQ
DECL|macro|__HAVE_COUNTER7
mdefine_line|#define __HAVE_COUNTER7         _DRM_STAT_PRIMARY
DECL|macro|__HAVE_COUNTER8
mdefine_line|#define __HAVE_COUNTER8         _DRM_STAT_SECONDARY
DECL|macro|__HAVE_COUNTER9
mdefine_line|#define __HAVE_COUNTER9         _DRM_STAT_DMA
multiline_comment|/* Driver customization:&n; */
DECL|macro|DRIVER_PRETAKEDOWN
mdefine_line|#define DRIVER_PRETAKEDOWN() do {&t;&t;&t;&t;&t;&bslash;&n;&t;if ( dev-&gt;dev_private ) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;drm_i915_private_t *dev_priv = dev-&gt;dev_private;&t;&bslash;&n;&t;        i915_mem_takedown( &amp;(dev_priv-&gt;agp_heap) );             &bslash;&n; &t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;i915_dma_cleanup( dev );&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* When a client dies:&n; *    - Free any alloced agp memory.&n; */
DECL|macro|DRIVER_PRERELEASE
mdefine_line|#define DRIVER_PRERELEASE() &t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( dev-&gt;dev_private ) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;drm_i915_private_t *dev_priv = dev-&gt;dev_private;&t;&bslash;&n;                i915_mem_release( dev, filp, dev_priv-&gt;agp_heap );&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* We use our own dma mechanisms, not the drm template code.  However,&n; * the shared IRQ code is useful to us:&n; */
DECL|macro|__HAVE_DMA
mdefine_line|#define __HAVE_DMA&t;&t;0
DECL|macro|__HAVE_IRQ
mdefine_line|#define __HAVE_IRQ&t;&t;1
DECL|macro|__HAVE_SHARED_IRQ
mdefine_line|#define __HAVE_SHARED_IRQ&t;1
DECL|macro|__HAVE_PM
mdefine_line|#define __HAVE_PM&t;&t;1
macro_line|#endif
eof
