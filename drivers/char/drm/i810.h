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
multiline_comment|/* Driver customization:&n; */
DECL|macro|__HAVE_RELEASE
mdefine_line|#define __HAVE_RELEASE&t;&t;1
DECL|macro|DRIVER_RELEASE
mdefine_line|#define DRIVER_RELEASE() do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;i810_reclaim_buffers( dev, priv-&gt;pid );&t;&t;&t;&t;&bslash;&n;} while (0)
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
mdefine_line|#define DRIVER_DMA_QUIESCENT() do {&t;&t;&t;&t;&t;&bslash;&n;&t;i810_dma_quiescent( dev );&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Don&squot;t need an irq any more.  The template code will make sure that&n; * a noop stub is generated for compatibility.&n; */
DECL|macro|__HAVE_DMA_IRQ
mdefine_line|#define __HAVE_DMA_IRQ&t;&t;0
multiline_comment|/* Buffer customization:&n; */
DECL|macro|DRIVER_BUF_PRIV_T
mdefine_line|#define DRIVER_BUF_PRIV_T&t;drm_i810_buf_priv_t
DECL|macro|DRIVER_AGP_BUFFERS_MAP
mdefine_line|#define DRIVER_AGP_BUFFERS_MAP( dev )&t;&t;&t;&t;&t;&bslash;&n;&t;((drm_i810_private_t *)((dev)-&gt;dev_private))-&gt;buffer_map
macro_line|#endif
eof
