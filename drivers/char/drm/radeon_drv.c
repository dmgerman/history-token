multiline_comment|/* radeon_drv.c -- ATI Radeon driver -*- linux-c -*-&n; * Created: Wed Feb 14 17:10:04 2001 by gareth@valinux.com&n; *&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;radeon.h&quot;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;radeon_drv.h&quot;
macro_line|#include &quot;ati_pcigart.h&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;Gareth Hughes, VA Linux Systems Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;radeon&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;ATI Radeon&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20010405&quot;
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;1
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;1
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS&t;&t;&t;&t;&t;&t;&t;     &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_DMA)]               = { radeon_cp_buffers,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CP_INIT)]    = { radeon_cp_init,     1, 1 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CP_START)]   = { radeon_cp_start,    1, 1 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CP_STOP)]    = { radeon_cp_stop,     1, 1 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CP_RESET)]   = { radeon_cp_reset,    1, 1 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CP_IDLE)]    = { radeon_cp_idle,     1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_RESET)]    = { radeon_engine_reset,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_FULLSCREEN)] = { radeon_fullscreen,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_SWAP)]       = { radeon_cp_swap,     1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CLEAR)]      = { radeon_cp_clear,    1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_VERTEX)]     = { radeon_cp_vertex,   1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_INDICES)]    = { radeon_cp_indices,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_TEXTURE)]    = { radeon_cp_texture,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_STIPPLE)]    = { radeon_cp_stipple,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_INDIRECT)]   = { radeon_cp_indirect, 1, 1 },
macro_line|#if 0
multiline_comment|/* GH: Count data sent to card via ring or vertex/indirect buffers.&n; */
mdefine_line|#define __HAVE_COUNTERS         3
mdefine_line|#define __HAVE_COUNTER6         _DRM_STAT_IRQ
mdefine_line|#define __HAVE_COUNTER7         _DRM_STAT_PRIMARY
mdefine_line|#define __HAVE_COUNTER8         _DRM_STAT_SECONDARY
macro_line|#endif
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
DECL|function|radeon_options
r_static
r_int
id|__init
id|radeon_options
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
id|radeon_options
)paren
suffix:semicolon
macro_line|#endif
macro_line|#include &quot;drm_fops.h&quot;
macro_line|#include &quot;drm_init.h&quot;
macro_line|#include &quot;drm_ioctl.h&quot;
macro_line|#include &quot;drm_lock.h&quot;
macro_line|#include &quot;drm_memory.h&quot;
macro_line|#include &quot;drm_proc.h&quot;
macro_line|#include &quot;drm_vm.h&quot;
macro_line|#include &quot;drm_stub.h&quot;
macro_line|#include &quot;drm_scatter.h&quot;
eof
