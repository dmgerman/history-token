multiline_comment|/* mga.h -- Matrox G200/G400 DRM template customization -*- linux-c -*-&n; * Created: Thu Jan 11 21:29:32 2001 by gareth@valinux.com&n; *&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#ifndef __MGA_H__
DECL|macro|__MGA_H__
mdefine_line|#define __MGA_H__
multiline_comment|/* This remains constant for all DRM template files.&n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) mga_##x
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
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;Gareth Hughes, VA Linux Systems Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;mga&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;Matrox G200/G400&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20010321&quot;
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;3
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;0
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;2
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_DMA)]&t;      = { mga_dma_buffers, 1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_MGA_INIT)]    = { mga_dma_init,    1, 1 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_MGA_FLUSH)]   = { mga_dma_flush,   1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_MGA_RESET)]   = { mga_dma_reset,   1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_MGA_SWAP)]    = { mga_dma_swap,    1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_MGA_CLEAR)]   = { mga_dma_clear,   1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_MGA_VERTEX)]  = { mga_dma_vertex,  1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_MGA_INDICES)] = { mga_dma_indices, 1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_MGA_ILOAD)]   = { mga_dma_iload,   1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_MGA_BLIT)]    = { mga_dma_blit,    1, 0 },
DECL|macro|__HAVE_COUNTERS
mdefine_line|#define __HAVE_COUNTERS         3
DECL|macro|__HAVE_COUNTER6
mdefine_line|#define __HAVE_COUNTER6         _DRM_STAT_IRQ
DECL|macro|__HAVE_COUNTER7
mdefine_line|#define __HAVE_COUNTER7         _DRM_STAT_PRIMARY
DECL|macro|__HAVE_COUNTER8
mdefine_line|#define __HAVE_COUNTER8         _DRM_STAT_SECONDARY
multiline_comment|/* Driver customization:&n; */
DECL|macro|DRIVER_PRETAKEDOWN
mdefine_line|#define DRIVER_PRETAKEDOWN() do {&t;&t;&t;&t;&t;&bslash;&n;&t;if ( dev-&gt;dev_private ) mga_do_cleanup_dma( dev );&t;&t;&bslash;&n;} while (0)
multiline_comment|/* DMA customization:&n; */
DECL|macro|__HAVE_DMA
mdefine_line|#define __HAVE_DMA&t;&t;1
DECL|macro|__HAVE_DMA_QUIESCENT
mdefine_line|#define __HAVE_DMA_QUIESCENT&t;1
DECL|macro|DRIVER_DMA_QUIESCENT
mdefine_line|#define DRIVER_DMA_QUIESCENT() do {&t;&t;&t;&t;&t;&bslash;&n;&t;drm_mga_private_t *dev_priv = dev-&gt;dev_private;&t;&t;&t;&bslash;&n;&t;return mga_do_wait_for_idle( dev_priv );&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Buffer customization:&n; */
DECL|macro|DRIVER_BUF_PRIV_T
mdefine_line|#define DRIVER_BUF_PRIV_T&t;drm_mga_buf_priv_t
DECL|macro|DRIVER_AGP_BUFFERS_MAP
mdefine_line|#define DRIVER_AGP_BUFFERS_MAP( dev )&t;&t;&t;&t;&t;&bslash;&n;&t;((drm_mga_private_t *)((dev)-&gt;dev_private))-&gt;buffers
macro_line|#endif
eof
