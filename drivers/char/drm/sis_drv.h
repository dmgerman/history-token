multiline_comment|/* sis_drv.h -- Private header for sis driver -*- linux-c -*-&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; * &n; */
macro_line|#ifndef _SIS_DRV_H_
DECL|macro|_SIS_DRV_H_
mdefine_line|#define _SIS_DRV_H_
multiline_comment|/* General customization:&n; */
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;SIS&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;sis&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;SIS 300/630/540&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20030826&quot;
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;1
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;0
macro_line|#include &quot;sis_ds.h&quot;
DECL|struct|drm_sis_private
r_typedef
r_struct
id|drm_sis_private
(brace
DECL|member|AGPHeap
id|memHeap_t
op_star
id|AGPHeap
suffix:semicolon
DECL|member|FBHeap
id|memHeap_t
op_star
id|FBHeap
suffix:semicolon
DECL|typedef|drm_sis_private_t
)brace
id|drm_sis_private_t
suffix:semicolon
r_extern
r_int
id|sis_fb_alloc
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|sis_fb_free
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|sis_ioctl_agp_init
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|sis_ioctl_agp_alloc
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|sis_ioctl_agp_free
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|sis_fb_init
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|sis_init_context
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|context
)paren
suffix:semicolon
r_extern
r_int
id|sis_final_context
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|context
)paren
suffix:semicolon
macro_line|#endif
eof
