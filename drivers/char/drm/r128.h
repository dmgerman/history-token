multiline_comment|/* r128.h -- ATI Rage 128 DRM template customization -*- linux-c -*-&n; * Created: Wed Feb 14 16:07:10 2001 by gareth@valinux.com&n; *&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#ifndef __R128_H__
DECL|macro|__R128_H__
mdefine_line|#define __R128_H__
multiline_comment|/* This remains constant for all DRM template files.&n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) r128_##x
multiline_comment|/* General customization:&n; */
DECL|macro|__HAVE_AGP
mdefine_line|#define __HAVE_AGP&t;&t;1
DECL|macro|__MUST_HAVE_AGP
mdefine_line|#define __MUST_HAVE_AGP&t;&t;0
DECL|macro|__HAVE_MTRR
mdefine_line|#define __HAVE_MTRR&t;&t;1
DECL|macro|__HAVE_CTX_BITMAP
mdefine_line|#define __HAVE_CTX_BITMAP&t;1
DECL|macro|__HAVE_SG
mdefine_line|#define __HAVE_SG&t;&t;1
DECL|macro|__HAVE_PCI_DMA
mdefine_line|#define __HAVE_PCI_DMA&t;&t;1
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;Gareth Hughes, VA Linux Systems Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;r128&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;ATI Rage 128&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20030526&quot;
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;2
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;4
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;0
multiline_comment|/* Interface history:&n; *&n; * ??  - ??&n; * 2.4 - Add support for ycbcr textures (no new ioctls)&n; */
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_DMA)]             = { r128_cce_buffers,  1, 0 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_INIT)]       = { r128_cce_init,     1, 1 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_CCE_START)]  = { r128_cce_start,    1, 1 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_CCE_STOP)]   = { r128_cce_stop,     1, 1 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_CCE_RESET)]  = { r128_cce_reset,    1, 1 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_CCE_IDLE)]   = { r128_cce_idle,     1, 0 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_RESET)]      = { r128_engine_reset, 1, 0 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_FULLSCREEN)] = { r128_fullscreen,   1, 0 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_SWAP)]       = { r128_cce_swap,     1, 0 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_CLEAR)]      = { r128_cce_clear,    1, 0 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_VERTEX)]     = { r128_cce_vertex,   1, 0 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_INDICES)]    = { r128_cce_indices,  1, 0 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_BLIT)]       = { r128_cce_blit,     1, 0 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_DEPTH)]      = { r128_cce_depth,    1, 0 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_STIPPLE)]    = { r128_cce_stipple,  1, 0 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_INDIRECT)]   = { r128_cce_indirect, 1, 1 }, &bslash;&n;   [DRM_IOCTL_NR(DRM_IOCTL_R128_GETPARAM)]   = { r128_getparam, 1, 0 },
multiline_comment|/* Driver customization:&n; */
DECL|macro|DRIVER_PRERELEASE
mdefine_line|#define DRIVER_PRERELEASE() do {&t;&t;&t;&t;&t;&bslash;&n;&t;if ( dev-&gt;dev_private ) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;drm_r128_private_t *dev_priv = dev-&gt;dev_private;&t;&bslash;&n;&t;&t;if ( dev_priv-&gt;page_flipping ) {&t;&t;&t;&bslash;&n;&t;&t;&t;r128_do_cleanup_pageflip( dev );&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|DRIVER_PRETAKEDOWN
mdefine_line|#define DRIVER_PRETAKEDOWN() do {&t;&t;&t;&t;&t;&bslash;&n;&t;r128_do_cleanup_cce( dev );&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* DMA customization:&n; */
DECL|macro|__HAVE_DMA
mdefine_line|#define __HAVE_DMA&t;&t;1
DECL|macro|__HAVE_DMA_IRQ
mdefine_line|#define __HAVE_DMA_IRQ&t;&t;1
DECL|macro|__HAVE_VBL_IRQ
mdefine_line|#define __HAVE_VBL_IRQ&t;&t;1
DECL|macro|__HAVE_SHARED_IRQ
mdefine_line|#define __HAVE_SHARED_IRQ       1
macro_line|#if 0
multiline_comment|/* GH: Remove this for now... */
mdefine_line|#define __HAVE_DMA_QUIESCENT&t;1
mdefine_line|#define DRIVER_DMA_QUIESCENT() do {&t;&t;&t;&t;&t;&bslash;&n;&t;drm_r128_private_t *dev_priv = dev-&gt;dev_private;&t;&t;&bslash;&n;&t;return r128_do_cce_idle( dev_priv );&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif
multiline_comment|/* Buffer customization:&n; */
DECL|macro|DRIVER_BUF_PRIV_T
mdefine_line|#define DRIVER_BUF_PRIV_T&t;drm_r128_buf_priv_t
DECL|macro|DRIVER_AGP_BUFFERS_MAP
mdefine_line|#define DRIVER_AGP_BUFFERS_MAP( dev )&t;&t;&t;&t;&t;&bslash;&n;&t;((drm_r128_private_t *)((dev)-&gt;dev_private))-&gt;buffers
macro_line|#endif
eof
