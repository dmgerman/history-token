multiline_comment|/* i810_drv.c -- I810 driver -*- linux-c -*-&n; * Created: Mon Dec 13 01:56:22 1999 by jhartmann@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *    Jeff Hartmann &lt;jhartmann@valinux.com&gt;&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;i810.h&quot;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;i810_drv.h&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;VA Linux Systems Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;i810&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;Intel i810&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20020211&quot;
multiline_comment|/* Interface history&n; *&n; * 1.1   - XFree86 4.1&n; * 1.2   - XvMC interfaces&n; *       - XFree86 4.2&n; * 1.2.1 - Disable copying code (leave stub ioctls for backwards compatibility)&n; *       - Remove requirement for interrupt (leave stubs again)&n; */
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;2
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;1
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS&t;&t;&t;&t;&t;&t;&t;    &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_INIT)]   = { i810_dma_init,    1, 1 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_VERTEX)] = { i810_dma_vertex,  1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_CLEAR)]  = { i810_clear_bufs,  1, 0 }, &bslash;&n;      &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_FLUSH)]  = { i810_flush_ioctl, 1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_GETAGE)] = { i810_getage,      1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_GETBUF)] = { i810_getbuf,      1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_SWAP)]   = { i810_swap_bufs,   1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_COPY)]   = { i810_copybuf,     1, 0 }, &bslash;&n;   &t;[DRM_IOCTL_NR(DRM_IOCTL_I810_DOCOPY)] = { i810_docopy,      1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_OV0INFO)] = { i810_ov0_info,   1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_FSTATUS)] = { i810_fstatus,    1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_OV0FLIP)] = { i810_ov0_flip,   1, 0 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_MC)]      = { i810_dma_mc,     1, 1 }, &bslash;&n;&t;[DRM_IOCTL_NR(DRM_IOCTL_I810_RSTATUS)] = { i810_rstatus,    1, 0 }
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
macro_line|#include &quot;drm_agpsupport.h&quot;
macro_line|#include &quot;drm_auth.h&quot;
macro_line|#include &quot;drm_bufs.h&quot;
macro_line|#include &quot;drm_context.h&quot;
macro_line|#include &quot;drm_dma.h&quot;
macro_line|#include &quot;drm_drawable.h&quot;
macro_line|#include &quot;drm_drv.h&quot;
macro_line|#ifndef MODULE
multiline_comment|/* DRM(options) is called by the kernel to parse command-line options&n; * passed via the boot-loader (e.g., LILO).  It calls the insmod option&n; * routine, drm_parse_drm.&n; */
multiline_comment|/* JH- We have to hand expand the string ourselves because of the cpp.  If&n; * anyone can think of a way that we can fit into the __setup macro without&n; * changing it, then please send the solution my way.&n; */
DECL|function|i810_options
r_static
r_int
id|__init
id|i810_options
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|DRM
c_func
(paren
id|parse_options
)paren
(paren
id|str
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
id|DRIVER_NAME
l_string|&quot;=&quot;
comma
id|i810_options
)paren
suffix:semicolon
macro_line|#endif
macro_line|#include &quot;drm_fops.h&quot;
macro_line|#include &quot;drm_init.h&quot;
macro_line|#include &quot;drm_ioctl.h&quot;
macro_line|#include &quot;drm_lock.h&quot;
macro_line|#include &quot;drm_lists.h&quot;
macro_line|#include &quot;drm_memory.h&quot;
macro_line|#include &quot;drm_proc.h&quot;
macro_line|#include &quot;drm_vm.h&quot;
macro_line|#include &quot;drm_stub.h&quot;
eof
