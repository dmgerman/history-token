multiline_comment|/* sis_drv.h -- Private header for sis driver -*- linux-c -*-&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; * &n; */
multiline_comment|/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/linux/drm/kernel/sis.h,v 1.2 2001/12/19 21:25:59 dawes Exp $ */
macro_line|#ifndef __SIS_H__
DECL|macro|__SIS_H__
mdefine_line|#define __SIS_H__
multiline_comment|/* This remains constant for all DRM template files.&n; * Name it sisdrv_##x as there&squot;s a conflict with sis_free/malloc in the kernel&n; * that&squot;s used for fb devices &n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) sisdrv_##x
multiline_comment|/* General customization:&n; */
DECL|macro|__HAVE_AGP
mdefine_line|#define __HAVE_AGP&t;&t;1
DECL|macro|__MUST_HAVE_AGP
mdefine_line|#define __MUST_HAVE_AGP&t;&t;0
DECL|macro|__HAVE_MTRR
mdefine_line|#define __HAVE_MTRR&t;&t;1
DECL|macro|__HAVE_CTX_BITMAP
mdefine_line|#define __HAVE_CTX_BITMAP&t;1
multiline_comment|/* Buffer customization:&n; */
DECL|macro|DRIVER_AGP_BUFFERS_MAP
mdefine_line|#define DRIVER_AGP_BUFFERS_MAP( dev )&t;&t;&t;&t;&t;&bslash;&n;&t;((drm_sis_private_t *)((dev)-&gt;dev_private))-&gt;buffers
r_extern
r_int
id|sis_init_context
c_func
(paren
r_int
id|context
)paren
suffix:semicolon
r_extern
r_int
id|sis_final_context
c_func
(paren
r_int
id|context
)paren
suffix:semicolon
DECL|macro|DRIVER_CTX_CTOR
mdefine_line|#define DRIVER_CTX_CTOR sis_init_context
DECL|macro|DRIVER_CTX_DTOR
mdefine_line|#define DRIVER_CTX_DTOR sis_final_context
macro_line|#endif
eof
