multiline_comment|/* sis_drv.h -- Private header for sis driver -*- linux-c -*-&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; * &n; */
multiline_comment|/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/linux/drm/kernel/sis.h,v 1.3 2002/10/30 12:52:38 alanh Exp $ */
macro_line|#ifndef __SIS_H__
DECL|macro|__SIS_H__
mdefine_line|#define __SIS_H__
multiline_comment|/* This remains constant for all DRM template files.&n; * Name it sisdrv_##x as there&squot;s a conflict with sis_free/malloc in the kernel&n; * that&squot;s used for fb devices &n; */
macro_line|#ifdef __linux__
DECL|macro|DRM
mdefine_line|#define DRM(x) sisdrv_##x
macro_line|#else
DECL|macro|DRM
mdefine_line|#define DRM(x) sis_##x
macro_line|#endif
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
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_SIS_FB_ALLOC)]  = { sis_fb_alloc,&t;1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_SIS_FB_FREE)]   = { sis_fb_free,&t;1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_SIS_AGP_INIT)]  = { sis_ioctl_agp_init,&t;1, 1 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_SIS_AGP_ALLOC)] = { sis_ioctl_agp_alloc, 1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_SIS_AGP_FREE)]&t;= { sis_ioctl_agp_free,&t;1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_SIS_FB_INIT)]&t;= { sis_fb_init,&t;1, 1 }
macro_line|#endif
eof
