multiline_comment|/* sis.c -- sis driver -*- linux-c -*-&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;sis.h&quot;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;sis_drm.h&quot;
macro_line|#include &quot;sis_drv.h&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t; &quot;SIS&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t; &quot;sis&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t; &quot;SIS 300/630/540&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t; &quot;20010503&quot;
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t; 1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t; 0
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL  0
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS &bslash;&n;        [DRM_IOCTL_NR(SIS_IOCTL_FB_ALLOC)]   = { sis_fb_alloc,&t;  1, 0 }, &bslash;&n;        [DRM_IOCTL_NR(SIS_IOCTL_FB_FREE)]    = { sis_fb_free,&t;  1, 0 }, &bslash;&n;        /* AGP Memory Management */&t;&t;&t;&t;&t;  &bslash;&n;        [DRM_IOCTL_NR(SIS_IOCTL_AGP_INIT)]   = { sisp_agp_init,&t;  1, 0 }, &bslash;&n;        [DRM_IOCTL_NR(SIS_IOCTL_AGP_ALLOC)]  = { sisp_agp_alloc,  1, 0 }, &bslash;&n;        [DRM_IOCTL_NR(SIS_IOCTL_AGP_FREE)]   = { sisp_agp_free,&t;  1, 0 }
macro_line|#if 0 /* these don&squot;t appear to be defined */
multiline_comment|/* SIS Stereo */
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_CONTROL
)paren
)braket
op_assign
(brace
id|sis_control
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
id|SIS_IOCTL_FLIP
)paren
)braket
op_assign
(brace
id|sis_flip
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
id|SIS_IOCTL_FLIP_INIT
)paren
)braket
op_assign
(brace
id|sis_flip_init
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
id|SIS_IOCTL_FLIP_FINAL
)paren
)braket
op_assign
(brace
id|sis_flip_final
comma
l_int|1
comma
l_int|1
)brace
macro_line|#endif
DECL|macro|__HAVE_COUNTERS
mdefine_line|#define __HAVE_COUNTERS&t;&t;5
macro_line|#include &quot;drm_auth.h&quot;
macro_line|#include &quot;drm_agpsupport.h&quot;
macro_line|#include &quot;drm_bufs.h&quot;
macro_line|#include &quot;drm_context.h&quot;
macro_line|#include &quot;drm_dma.h&quot;
macro_line|#include &quot;drm_drawable.h&quot;
macro_line|#include &quot;drm_drv.h&quot;
macro_line|#include &quot;drm_fops.h&quot;
macro_line|#include &quot;drm_init.h&quot;
macro_line|#include &quot;drm_ioctl.h&quot;
macro_line|#include &quot;drm_lists.h&quot;
macro_line|#include &quot;drm_lock.h&quot;
macro_line|#include &quot;drm_memory.h&quot;
macro_line|#include &quot;drm_proc.h&quot;
macro_line|#include &quot;drm_vm.h&quot;
macro_line|#include &quot;drm_stub.h&quot;
eof
