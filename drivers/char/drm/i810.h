multiline_comment|/* i810.h -- Intel i810/i815 DRM template customization -*- linux-c -*-&n; * Created: Thu Feb 15 00:01:12 2001 by gareth@valinux.com&n; *&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#ifndef __I810_H__
DECL|macro|__I810_H__
mdefine_line|#define __I810_H__
multiline_comment|/* This remains constant for all DRM template files.&n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) i810_##x
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
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;VA Linux Systems Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;i810&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;Intel i810&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20030605&quot;
multiline_comment|/* Interface history&n; *&n; * 1.1   - XFree86 4.1&n; * 1.2   - XvMC interfaces&n; *       - XFree86 4.2&n; * 1.2.1 - Disable copying code (leave stub ioctls for backwards compatibility)&n; *       - Remove requirement for interrupt (leave stubs again)&n; * 1.3   - Add page flipping.&n; * 1.4   - fix DRM interface&n; */
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;4
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;0
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_INIT)]   = { i810_dma_init,    1, 1 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_VERTEX)] = { i810_dma_vertex,  1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_CLEAR)]  = { i810_clear_bufs,  1, 0 }, &bslash;&n;      &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_FLUSH)]  = { i810_flush_ioctl, 1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_GETAGE)] = { i810_getage,      1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_GETBUF)] = { i810_getbuf,      1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_SWAP)]   = { i810_swap_bufs,   1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_COPY)]   = { i810_copybuf,     1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_DOCOPY)] = { i810_docopy,      1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_OV0INFO)] = { i810_ov0_info,   1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_FSTATUS)] = { i810_fstatus,    1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_OV0FLIP)] = { i810_ov0_flip,   1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_MC)]      = { i810_dma_mc,     1, 1 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_RSTATUS)] = { i810_rstatus,    1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_FLIP)] =    { i810_flip_bufs,  1, 0 }
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
DECL|macro|__HAVE_RELEASE
mdefine_line|#define __HAVE_RELEASE&t;&t;1
DECL|macro|DRIVER_RELEASE
mdefine_line|#define DRIVER_RELEASE() do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;i810_reclaim_buffers( filp );&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|DRIVER_PRETAKEDOWN
mdefine_line|#define DRIVER_PRETAKEDOWN() do {&t;&t;&t;&t;&t;&bslash;&n;&t;i810_dma_cleanup( dev );&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* DMA customization:&n; */
DECL|macro|__HAVE_DMA
mdefine_line|#define __HAVE_DMA&t;&t;1
DECL|macro|__HAVE_DMA_QUEUE
mdefine_line|#define __HAVE_DMA_QUEUE&t;1
DECL|macro|__HAVE_DMA_WAITLIST
mdefine_line|#define __HAVE_DMA_WAITLIST&t;0
DECL|macro|__HAVE_DMA_RECLAIM
mdefine_line|#define __HAVE_DMA_RECLAIM&t;1
DECL|macro|__HAVE_DMA_QUIESCENT
mdefine_line|#define __HAVE_DMA_QUIESCENT&t;1
DECL|macro|DRIVER_DMA_QUIESCENT
mdefine_line|#define DRIVER_DMA_QUIESCENT() do {&t;&t;&t;&t;&t;&bslash;&n;&t;i810_dma_quiescent( dev );&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Don&squot;t need an irq any more.  The template code will make sure that&n; * a noop stub is generated for compatibility.&n; */
multiline_comment|/* XXX: Add vblank support? */
DECL|macro|__HAVE_DMA_IRQ
mdefine_line|#define __HAVE_DMA_IRQ&t;&t;0
multiline_comment|/* Buffer customization:&n; */
DECL|macro|DRIVER_BUF_PRIV_T
mdefine_line|#define DRIVER_BUF_PRIV_T&t;drm_i810_buf_priv_t
DECL|macro|DRIVER_AGP_BUFFERS_MAP
mdefine_line|#define DRIVER_AGP_BUFFERS_MAP( dev )&t;&t;&t;&t;&t;&bslash;&n;&t;((drm_i810_private_t *)((dev)-&gt;dev_private))-&gt;buffer_map
macro_line|#endif
eof
