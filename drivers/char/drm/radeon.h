multiline_comment|/* radeon.h -- ATI Radeon DRM template customization -*- linux-c -*-&n; * Created: Wed Feb 14 17:07:34 2001 by gareth@valinux.com&n; *&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; *    Keith Whitwell &lt;keith@tungstengraphics.com&gt;&n; */
macro_line|#ifndef __RADEON_H__
DECL|macro|__RADEON_H__
mdefine_line|#define __RADEON_H__
multiline_comment|/* This remains constant for all DRM template files.&n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) radeon_##x
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
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;Gareth Hughes, Keith Whitwell, others.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;radeon&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;ATI Radeon&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20020828&quot;
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;10
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;0
multiline_comment|/* Interface history:&n; *&n; * 1.1 - ??&n; * 1.2 - Add vertex2 ioctl (keith)&n; *     - Add stencil capability to clear ioctl (gareth, keith)&n; *     - Increase MAX_TEXTURE_LEVELS (brian)&n; * 1.3 - Add cmdbuf ioctl (keith)&n; *     - Add support for new radeon packets (keith)&n; *     - Add getparam ioctl (keith)&n; *     - Add flip-buffers ioctl, deprecate fullscreen foo (keith).&n; * 1.4 - Add scratch registers to get_param ioctl.&n; * 1.5 - Add r200 packets to cmdbuf ioctl&n; *     - Add r200 function to init ioctl&n; *     - Add &squot;scalar2&squot; instruction to cmdbuf&n; * 1.6 - Add static GART memory manager&n; *       Add irq handler (won&squot;t be turned on unless X server knows to)&n; *       Add irq ioctls and irq_active getparam.&n; *       Add wait command for cmdbuf ioctl&n; *       Add GART offset query for getparam&n; * 1.7 - Add support for cube map registers: R200_PP_CUBIC_FACES_[0..5]&n; *       and R200_PP_CUBIC_OFFSET_F1_[0..5].&n; *       Added packets R200_EMIT_PP_CUBIC_FACES_[0..5] and&n; *       R200_EMIT_PP_CUBIC_OFFSETS_[0..5].  (brian)&n; * 1.8 - Remove need to call cleanup ioctls on last client exit (keith)&n; *       Add &squot;GET&squot; queries for starting additional clients on different VT&squot;s.&n; * 1.9 - Add DRM_IOCTL_RADEON_CP_RESUME ioctl.&n; *       Add texture rectangle support for r100.&n; * 1.10- Add SETPARAM ioctl; first parameter to set is FB_LOCATION, which&n; *       clients use to tell the DRM where they think the framebuffer is &n; *       located in the card&squot;s address space&n; */
DECL|macro|DRIVER_IOCTLS
mdefine_line|#define DRIVER_IOCTLS&t;&t;&t;&t;&t;&t;&t;     &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_DMA)]               = { radeon_cp_buffers,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CP_INIT)]    = { radeon_cp_init,     1, 1 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CP_START)]   = { radeon_cp_start,    1, 1 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CP_STOP)]    = { radeon_cp_stop,     1, 1 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CP_RESET)]   = { radeon_cp_reset,    1, 1 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CP_IDLE)]    = { radeon_cp_idle,     1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CP_RESUME)]  = { radeon_cp_resume,   1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_RESET)]    = { radeon_engine_reset,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_FULLSCREEN)] = { radeon_fullscreen,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_SWAP)]       = { radeon_cp_swap,     1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CLEAR)]      = { radeon_cp_clear,    1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_VERTEX)]     = { radeon_cp_vertex,   1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_INDICES)]    = { radeon_cp_indices,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_TEXTURE)]    = { radeon_cp_texture,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_STIPPLE)]    = { radeon_cp_stipple,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_INDIRECT)]   = { radeon_cp_indirect, 1, 1 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_VERTEX2)]    = { radeon_cp_vertex2,  1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_CMDBUF)]     = { radeon_cp_cmdbuf,   1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_GETPARAM)]   = { radeon_cp_getparam, 1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_FLIP)]       = { radeon_cp_flip,     1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_ALLOC)]      = { radeon_mem_alloc,   1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_FREE)]       = { radeon_mem_free,    1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_INIT_HEAP)]  = { radeon_mem_init_heap, 1, 1 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_IRQ_EMIT)]   = { radeon_irq_emit,    1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_IRQ_WAIT)]   = { radeon_irq_wait,    1, 0 }, &bslash;&n; [DRM_IOCTL_NR(DRM_IOCTL_RADEON_SETPARAM)]   = { radeon_cp_setparam, 1, 0 }, &bslash;&n;
DECL|macro|DRIVER_PCI_IDS
mdefine_line|#define DRIVER_PCI_IDS&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4136, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4137, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4237, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4242, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4242, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4336, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4337, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4437, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4964, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4965, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4966, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4967, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4C57, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4C58, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4C59, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4C5A, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4C64, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4C65, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4C66, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x4C67, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5144, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5145, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5146, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5147, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5148, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5149, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x514A, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x514B, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x514C, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x514D, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x514E, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x514F, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5157, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5158, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5159, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x515A, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5168, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5169, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x516A, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x516B, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x516C, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5834, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5835, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5836, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5837, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5960, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5961, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5962, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5963, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5964, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5968, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5969, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x596A, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x596B, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5c61, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5c62, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5c63, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0x1002, 0x5c64, 0},&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{0, 0, 0}
DECL|macro|DRIVER_FILE_FIELDS
mdefine_line|#define DRIVER_FILE_FIELDS&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int64_t radeon_fb_delta;&t;&t;&t;&t;&t;&bslash;&n;
DECL|macro|DRIVER_OPEN_HELPER
mdefine_line|#define DRIVER_OPEN_HELPER( filp_priv, dev )&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;drm_radeon_private_t *dev_priv = dev-&gt;dev_private;&t;&t;&bslash;&n;&t;if ( dev_priv )&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;filp_priv-&gt;radeon_fb_delta = dev_priv-&gt;fb_location;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;filp_priv-&gt;radeon_fb_delta = 0;&t;&t;&t;&t;&bslash;&n;} while( 0 )
multiline_comment|/* When a client dies:&n; *    - Check for and clean up flipped page state&n; *    - Free any alloced GART memory.&n; *&n; * DRM infrastructure takes care of reclaiming dma buffers.&n; */
DECL|macro|DRIVER_PRERELEASE
mdefine_line|#define DRIVER_PRERELEASE() &t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ( dev-&gt;dev_private ) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;drm_radeon_private_t *dev_priv = dev-&gt;dev_private;&t;&bslash;&n;&t;&t;if ( dev_priv-&gt;page_flipping ) {&t;&t;&t;&bslash;&n;&t;&t;&t;radeon_do_cleanup_pageflip( dev );&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;radeon_mem_release( filp, dev_priv-&gt;gart_heap );&t;&bslash;&n;                radeon_mem_release( filp, dev_priv-&gt;fb_heap );&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* When the last client dies, shut down the CP and free dev-&gt;dev_priv.&n; */
multiline_comment|/* #define __HAVE_RELEASE 1 */
DECL|macro|DRIVER_PRETAKEDOWN
mdefine_line|#define DRIVER_PRETAKEDOWN()&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;    radeon_do_release( dev );&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* DMA customization:&n; */
DECL|macro|__HAVE_DMA
mdefine_line|#define __HAVE_DMA&t;&t;1
DECL|macro|__HAVE_IRQ
mdefine_line|#define __HAVE_IRQ&t;&t;1
DECL|macro|__HAVE_VBL_IRQ
mdefine_line|#define __HAVE_VBL_IRQ&t;&t;1
DECL|macro|__HAVE_SHARED_IRQ
mdefine_line|#define __HAVE_SHARED_IRQ       1
multiline_comment|/* Buffer customization:&n; */
DECL|macro|DRIVER_BUF_PRIV_T
mdefine_line|#define DRIVER_BUF_PRIV_T&t;drm_radeon_buf_priv_t
DECL|macro|DRIVER_AGP_BUFFERS_MAP
mdefine_line|#define DRIVER_AGP_BUFFERS_MAP( dev )&t;&t;&t;&t;&bslash;&n;&t;((drm_radeon_private_t *)((dev)-&gt;dev_private))-&gt;buffers
macro_line|#endif
eof
