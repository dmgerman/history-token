multiline_comment|/* gamma.c -- 3dlabs GMX 2000 driver -*- linux-c -*-&n; * Created: Mon Jan  4 08:58:31 1999 by gareth@valinux.com&n; *&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#ifndef __GAMMA_H__
DECL|macro|__GAMMA_H__
mdefine_line|#define __GAMMA_H__
multiline_comment|/* This remains constant for all DRM template files.&n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) gamma_##x
multiline_comment|/* General customization:&n; */
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;VA Linux Systems Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;gamma&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;3DLabs gamma&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20010624&quot;
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;2
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;0
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;0
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_DMA)]&t;     = { gamma_dma,&t;  1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_GAMMA_INIT)] = { gamma_dma_init,  1, 1 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_GAMMA_COPY)] = { gamma_dma_copy,  1, 1 }
DECL|macro|IOCTL_TABLE_NAME
mdefine_line|#define IOCTL_TABLE_NAME&t;DRM(ioctls)
DECL|macro|IOCTL_FUNC_NAME
mdefine_line|#define IOCTL_FUNC_NAME &t;DRM(ioctl)
DECL|macro|__HAVE_COUNTERS
mdefine_line|#define __HAVE_COUNTERS&t;&t;5
DECL|macro|__HAVE_COUNTER6
mdefine_line|#define __HAVE_COUNTER6&t;&t;_DRM_STAT_IRQ
DECL|macro|__HAVE_COUNTER7
mdefine_line|#define __HAVE_COUNTER7&t;&t;_DRM_STAT_DMA
DECL|macro|__HAVE_COUNTER8
mdefine_line|#define __HAVE_COUNTER8&t;&t;_DRM_STAT_PRIMARY
DECL|macro|__HAVE_COUNTER9
mdefine_line|#define __HAVE_COUNTER9&t;&t;_DRM_STAT_SPECIAL
DECL|macro|__HAVE_COUNTER10
mdefine_line|#define __HAVE_COUNTER10&t;_DRM_STAT_MISSED
multiline_comment|/* Driver customization:&n; */
DECL|macro|DRIVER_PRETAKEDOWN
mdefine_line|#define DRIVER_PRETAKEDOWN() do {&t;&t;&t;&t;&t;&bslash;&n;&t;gamma_do_cleanup_dma( dev );&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* DMA customization:&n; */
DECL|macro|__HAVE_DMA
mdefine_line|#define __HAVE_DMA&t;&t;&t;1
DECL|macro|__HAVE_OLD_DMA
mdefine_line|#define __HAVE_OLD_DMA&t;&t;&t;1
DECL|macro|__HAVE_MULTIPLE_DMA_QUEUES
mdefine_line|#define __HAVE_MULTIPLE_DMA_QUEUES&t;1
DECL|macro|__HAVE_DMA_WAITQUEUE
mdefine_line|#define __HAVE_DMA_WAITQUEUE&t;&t;1
multiline_comment|/* removed from DRM HAVE_DMA_FREELIST &amp; HAVE_DMA_SCHEDULE */
DECL|macro|__HAVE_IRQ
mdefine_line|#define __HAVE_IRQ&t;&t;&t;1
DECL|macro|__HAVE_IRQ_BH
mdefine_line|#define __HAVE_IRQ_BH&t;&t;&t;1
macro_line|#endif /* __GAMMA_H__ */
eof
