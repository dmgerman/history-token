multiline_comment|/* i915.h -- Intel I915 DRM template customization -*- linux-c -*-&n; */
multiline_comment|/**************************************************************************&n; * &n; * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.&n; * All Rights Reserved.&n; * &n; **************************************************************************/
macro_line|#ifndef __I915_H__
DECL|macro|__I915_H__
mdefine_line|#define __I915_H__
multiline_comment|/* This remains constant for all DRM template files.&n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) i915_##x
multiline_comment|/* General customization:&n; */
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
multiline_comment|/* We use our own dma mechanisms, not the drm template code.  However,&n; * the shared IRQ code is useful to us:&n; */
DECL|macro|__HAVE_PM
mdefine_line|#define __HAVE_PM&t;&t;1
macro_line|#endif
eof
