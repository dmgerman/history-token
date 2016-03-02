multiline_comment|/* i830.h -- Intel I830 DRM template customization -*- linux-c -*-&n; * Created: Thu Feb 15 00:01:12 2001 by gareth@valinux.com&n; *&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#ifndef __I830_H__
DECL|macro|__I830_H__
mdefine_line|#define __I830_H__
multiline_comment|/* This remains constant for all DRM template files.&n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) i830_##x
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
mdefine_line|#define DRIVER_NAME&t;&t;&quot;i830&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;Intel 830M&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20011004&quot;
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;2
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;0
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_INIT)]   = { i830_dma_init,    1, 1 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I830_VERTEX)] = { i830_dma_vertex,  1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I830_CLEAR)]  = { i830_clear_bufs,  1, 0 }, &bslash;&n;      &t;[DRM_IOCTL_NR(DRM_IOCTL_I830_FLUSH)]  = { i830_flush_ioctl, 1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I830_GETAGE)] = { i830_getage,      1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_GETBUF)] = { i830_getbuf,      1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I830_SWAP)]   = { i830_swap_bufs,   1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I830_COPY)]   = { i830_copybuf,     1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I830_DOCOPY)] = { i830_docopy,      1, 0 },
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
mdefine_line|#define DRIVER_RELEASE() do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;i830_reclaim_buffers( dev, priv-&gt;pid );&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* DMA customization:&n; */
DECL|macro|__HAVE_DMA
mdefine_line|#define __HAVE_DMA&t;&t;1
DECL|macro|__HAVE_DMA_QUEUE
mdefine_line|#define __HAVE_DMA_QUEUE&t;1
DECL|macro|__HAVE_DMA_WAITLIST
mdefine_line|#define __HAVE_DMA_WAITLIST&t;1
DECL|macro|__HAVE_DMA_RECLAIM
mdefine_line|#define __HAVE_DMA_RECLAIM&t;1
DECL|macro|__HAVE_DMA_QUIESCENT
mdefine_line|#define __HAVE_DMA_QUIESCENT&t;1
DECL|macro|DRIVER_DMA_QUIESCENT
mdefine_line|#define DRIVER_DMA_QUIESCENT() do {&t;&t;&t;&t;&t;&bslash;&n;&t;i830_dma_quiescent( dev );&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__HAVE_DMA_IRQ
mdefine_line|#define __HAVE_DMA_IRQ&t;&t;1
DECL|macro|__HAVE_DMA_IRQ_BH
mdefine_line|#define __HAVE_DMA_IRQ_BH&t;1
DECL|macro|__HAVE_SHARED_IRQ
mdefine_line|#define __HAVE_SHARED_IRQ       1
DECL|macro|DRIVER_PREINSTALL
mdefine_line|#define DRIVER_PREINSTALL() do {&t;&t;&t;&t;&t;&bslash;&n;&t;drm_i830_private_t *dev_priv =&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(drm_i830_private_t *)dev-&gt;dev_private;&t;&t;&t;&bslash;&n;&t;u16 tmp;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;   &t;tmp = I830_READ16( I830REG_HWSTAM );&t;&t;&t;&t;&bslash;&n;   &t;tmp = tmp &amp; 0x6000;&t;&t;&t;&t;&t;&t;&bslash;&n;   &t;I830_WRITE16( I830REG_HWSTAM, tmp );&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;      &t;tmp = I830_READ16( I830REG_INT_MASK_R );&t;&t;&t;&bslash;&n;   &t;tmp = tmp &amp; 0x6000;&t;&t;/* Unmask interrupts */&t;&t;&bslash;&n;   &t;I830_WRITE16( I830REG_INT_MASK_R, tmp );&t;&t;&t;&bslash;&n;   &t;tmp = I830_READ16( I830REG_INT_ENABLE_R );&t;&t;&t;&bslash;&n;   &t;tmp = tmp &amp; 0x6000;&t;&t;/* Disable all interrupts */&t;&bslash;&n;      &t;I830_WRITE16( I830REG_INT_ENABLE_R, tmp );&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|DRIVER_POSTINSTALL
mdefine_line|#define DRIVER_POSTINSTALL() do {&t;&t;&t;&t;&t;&bslash;&n;&t;drm_i830_private_t *dev_priv =&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(drm_i830_private_t *)dev-&gt;dev_private;&t;&bslash;&n;&t;u16 tmp;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;   &t;tmp = I830_READ16( I830REG_INT_ENABLE_R );&t;&t;&t;&bslash;&n;   &t;tmp = tmp &amp; 0x6000;&t;&t;&t;&t;&t;&t;&bslash;&n;   &t;tmp = tmp | 0x0003;&t;/* Enable bp &amp; user interrupts */&t;&bslash;&n;   &t;I830_WRITE16( I830REG_INT_ENABLE_R, tmp );&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|DRIVER_UNINSTALL
mdefine_line|#define DRIVER_UNINSTALL() do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;drm_i830_private_t *dev_priv =&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(drm_i830_private_t *)dev-&gt;dev_private;&t;&t;&t;&bslash;&n;&t;u16 tmp;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( dev_priv ) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;tmp = I830_READ16( I830REG_INT_IDENTITY_R );&t;&t;&bslash;&n;&t;&t;tmp = tmp &amp; ~(0x6000);&t;/* Clear all interrupts */&t;&bslash;&n;&t;&t;if ( tmp != 0 )&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;I830_WRITE16( I830REG_INT_IDENTITY_R, tmp );&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;tmp = I830_READ16( I830REG_INT_ENABLE_R );&t;&t;&bslash;&n;&t;&t;tmp = tmp &amp; 0x6000;&t;/* Disable all interrupts */&t;&bslash;&n;&t;&t;I830_WRITE16( I830REG_INT_ENABLE_R, tmp );&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Buffer customization:&n; */
DECL|macro|DRIVER_BUF_PRIV_T
mdefine_line|#define DRIVER_BUF_PRIV_T&t;drm_i830_buf_priv_t
DECL|macro|DRIVER_AGP_BUFFERS_MAP
mdefine_line|#define DRIVER_AGP_BUFFERS_MAP( dev )&t;&t;&t;&t;&t;&bslash;&n;&t;((drm_i830_private_t *)((dev)-&gt;dev_private))-&gt;buffer_map
macro_line|#endif
eof
