multiline_comment|/* i830.h -- Intel I830 DRM template customization -*- linux-c -*-&n; * Created: Thu Feb 15 00:01:12 2001 by gareth@valinux.com&n; *&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#ifndef __I830_H__
DECL|macro|__I830_H__
mdefine_line|#define __I830_H__
multiline_comment|/* This remains constant for all DRM template files.&n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) i830_##x
multiline_comment|/* General customization:&n; */
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;VA Linux Systems Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;i830&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;Intel 830M&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20021108&quot;
multiline_comment|/* Interface history:&n; *&n; * 1.1: Original.&n; * 1.2: ?&n; * 1.3: New irq emit/wait ioctls.&n; *      New pageflip ioctl.&n; *      New getparam ioctl.&n; *      State for texunits 3&amp;4 in sarea.&n; *      New (alternative) layout for texture state.&n; */
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;3
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;2
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_INIT)]   = { i830_dma_init,    1, 1 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_VERTEX)] = { i830_dma_vertex,  1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_CLEAR)]  = { i830_clear_bufs,  1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_FLUSH)]  = { i830_flush_ioctl, 1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_GETAGE)] = { i830_getage,      1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_GETBUF)] = { i830_getbuf,      1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_SWAP)]   = { i830_swap_bufs,   1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_COPY)]   = { i830_copybuf,     1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_DOCOPY)] = { i830_docopy,      1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_FLIP)]   = { i830_flip_bufs,   1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_IRQ_EMIT)] = { i830_irq_emit,  1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_IRQ_WAIT)] = { i830_irq_wait,  1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_GETPARAM)] = { i830_getparam,  1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I830_SETPARAM)] = { i830_setparam,  1, 0 } 
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
multiline_comment|/* DMA customization:&n; */
DECL|macro|__HAVE_DMA
mdefine_line|#define __HAVE_DMA&t;&t;1
DECL|macro|__HAVE_DMA_QUEUE
mdefine_line|#define __HAVE_DMA_QUEUE&t;1
DECL|macro|__HAVE_DMA_RECLAIM
mdefine_line|#define __HAVE_DMA_RECLAIM&t;1
multiline_comment|/* Driver will work either way: IRQ&squot;s save cpu time when waiting for&n; * the card, but are subject to subtle interactions between bios,&n; * hardware and the driver.&n; */
multiline_comment|/* XXX: Add vblank support? */
DECL|macro|USE_IRQS
mdefine_line|#define USE_IRQS 0
macro_line|#if USE_IRQS
DECL|macro|__HAVE_IRQ
mdefine_line|#define __HAVE_IRQ&t;&t;1
DECL|macro|__HAVE_SHARED_IRQ
mdefine_line|#define __HAVE_SHARED_IRQ&t;1
macro_line|#else
DECL|macro|__HAVE_IRQ
mdefine_line|#define __HAVE_IRQ          0
macro_line|#endif
macro_line|#endif
eof
