multiline_comment|/* sis_mm.c -- Private header for Direct Rendering Manager -*- linux-c -*-&n; * Created: Mon Jan  4 10:05:05 1999 by sclin@sis.com.tw&n; *&n; * Copyright 2000 Silicon Integrated Systems Corp, Inc., HsinChu, Taiwan.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; * &n; * Authors:&n; *    Sung-Ching Lin &lt;sclin@sis.com.tw&gt;&n; * &n; */
macro_line|#include &quot;sis.h&quot;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;sis_drm.h&quot;
macro_line|#include &quot;sis_drv.h&quot;
macro_line|#include &quot;sis_ds.h&quot;
macro_line|#if defined(__linux__) &amp;&amp; defined(CONFIG_FB_SIS)
macro_line|#include &lt;linux/sisfb.h&gt;
macro_line|#endif
DECL|macro|MAX_CONTEXT
mdefine_line|#define MAX_CONTEXT 100
DECL|macro|VIDEO_TYPE
mdefine_line|#define VIDEO_TYPE 0 
DECL|macro|AGP_TYPE
mdefine_line|#define AGP_TYPE 1
r_typedef
r_struct
(brace
DECL|member|used
r_int
id|used
suffix:semicolon
DECL|member|context
r_int
id|context
suffix:semicolon
DECL|member|sets
id|set_t
op_star
id|sets
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0 for video, 1 for AGP */
DECL|typedef|sis_context_t
)brace
id|sis_context_t
suffix:semicolon
DECL|variable|global_ppriv
r_static
id|sis_context_t
id|global_ppriv
(braket
id|MAX_CONTEXT
)braket
suffix:semicolon
DECL|function|add_alloc_set
r_static
r_int
id|add_alloc_set
c_func
(paren
r_int
id|context
comma
r_int
id|type
comma
r_int
r_int
id|val
)paren
(brace
r_int
id|i
comma
id|retval
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CONTEXT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|global_ppriv
(braket
id|i
)braket
dot
id|used
op_logical_and
id|global_ppriv
(braket
id|i
)braket
dot
id|context
op_eq
id|context
)paren
(brace
id|retval
op_assign
id|setAdd
c_func
(paren
id|global_ppriv
(braket
id|i
)braket
dot
id|sets
(braket
id|type
)braket
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|del_alloc_set
r_static
r_int
id|del_alloc_set
c_func
(paren
r_int
id|context
comma
r_int
id|type
comma
r_int
r_int
id|val
)paren
(brace
r_int
id|i
comma
id|retval
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CONTEXT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|global_ppriv
(braket
id|i
)braket
dot
id|used
op_logical_and
id|global_ppriv
(braket
id|i
)braket
dot
id|context
op_eq
id|context
)paren
(brace
id|retval
op_assign
id|setDel
c_func
(paren
id|global_ppriv
(braket
id|i
)braket
dot
id|sets
(braket
id|type
)braket
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* fb management via fb device */
macro_line|#if defined(__linux__) &amp;&amp; defined(CONFIG_FB_SIS)
DECL|function|sis_fb_init
r_int
id|sis_fb_init
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sis_fb_alloc
r_int
id|sis_fb_alloc
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|drm_sis_mem_t
id|fb
suffix:semicolon
r_struct
id|sis_memreq
id|req
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|fb
comma
(paren
id|drm_sis_mem_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|fb
)paren
)paren
suffix:semicolon
id|req.size
op_assign
id|fb.size
suffix:semicolon
id|sis_malloc
c_func
(paren
op_amp
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req.offset
)paren
(brace
multiline_comment|/* TODO */
id|fb.offset
op_assign
id|req.offset
suffix:semicolon
id|fb.free
op_assign
id|req.offset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|add_alloc_set
c_func
(paren
id|fb.context
comma
id|VIDEO_TYPE
comma
id|fb.free
)paren
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;adding to allocation set fails&bslash;n&quot;
)paren
suffix:semicolon
id|sis_free
c_func
(paren
id|req.offset
)paren
suffix:semicolon
id|retval
op_assign
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|fb.offset
op_assign
l_int|0
suffix:semicolon
id|fb.size
op_assign
l_int|0
suffix:semicolon
id|fb.free
op_assign
l_int|0
suffix:semicolon
)brace
id|DRM_COPY_TO_USER_IOCTL
c_func
(paren
(paren
id|drm_sis_mem_t
op_star
)paren
id|data
comma
id|fb
comma
r_sizeof
(paren
id|fb
)paren
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;alloc fb, size = %d, offset = %ld&bslash;n&quot;
comma
id|fb.size
comma
id|req.offset
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|sis_fb_free
r_int
id|sis_fb_free
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|drm_sis_mem_t
id|fb
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|fb
comma
(paren
id|drm_sis_mem_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|fb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb.free
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|del_alloc_set
c_func
(paren
id|fb.context
comma
id|VIDEO_TYPE
comma
id|fb.free
)paren
)paren
id|retval
op_assign
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|sis_free
c_func
(paren
id|fb.free
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;free fb, offset = %d&bslash;n&quot;
comma
id|fb.free
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* Called by the X Server to initialize the FB heap.  Allocations will fail&n; * unless this is called.  Offset is the beginning of the heap from the&n; * framebuffer offset (MaxXFBMem in XFree86).&n; *&n; * Memory layout according to Thomas Winischofer:&n; * |------------------|DDDDDDDDDDDDDDDDDDDDDDDDDDDDD|HHHH|CCCCCCCCCCC|&n; *&n; *    X driver/sisfb                                  HW-   Command-&n; *  framebuffer memory           DRI heap           Cursor   queue&n; */
DECL|function|sis_fb_init
r_int
id|sis_fb_init
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_sis_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_sis_fb_t
id|fb
suffix:semicolon
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|fb
comma
(paren
id|drm_sis_fb_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|fb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv
op_eq
l_int|NULL
)paren
(brace
id|dev-&gt;dev_private
op_assign
id|DRM
c_func
(paren
id|calloc
)paren
(paren
l_int|1
comma
r_sizeof
(paren
id|drm_sis_private_t
)paren
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv
op_eq
l_int|NULL
)paren
r_return
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev_priv-&gt;FBHeap
op_ne
l_int|NULL
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|dev_priv-&gt;FBHeap
op_assign
id|mmInit
c_func
(paren
id|fb.offset
comma
id|fb.size
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;offset = %u, size = %u&quot;
comma
id|fb.offset
comma
id|fb.size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sis_fb_alloc
r_int
id|sis_fb_alloc
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_sis_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_sis_mem_t
id|fb
suffix:semicolon
id|PMemBlock
id|block
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv
op_eq
l_int|NULL
op_logical_or
id|dev_priv-&gt;FBHeap
op_eq
l_int|NULL
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|fb
comma
(paren
id|drm_sis_mem_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|fb
)paren
)paren
suffix:semicolon
id|block
op_assign
id|mmAllocMem
c_func
(paren
id|dev_priv-&gt;FBHeap
comma
id|fb.size
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
)paren
(brace
multiline_comment|/* TODO */
id|fb.offset
op_assign
id|block-&gt;ofs
suffix:semicolon
id|fb.free
op_assign
(paren
r_int
r_int
)paren
id|block
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|add_alloc_set
c_func
(paren
id|fb.context
comma
id|VIDEO_TYPE
comma
id|fb.free
)paren
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;adding to allocation set fails&bslash;n&quot;
)paren
suffix:semicolon
id|mmFreeMem
c_func
(paren
(paren
id|PMemBlock
)paren
id|fb.free
)paren
suffix:semicolon
id|retval
op_assign
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|fb.offset
op_assign
l_int|0
suffix:semicolon
id|fb.size
op_assign
l_int|0
suffix:semicolon
id|fb.free
op_assign
l_int|0
suffix:semicolon
)brace
id|DRM_COPY_TO_USER_IOCTL
c_func
(paren
(paren
id|drm_sis_mem_t
op_star
)paren
id|data
comma
id|fb
comma
r_sizeof
(paren
id|fb
)paren
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;alloc fb, size = %d, offset = %d&bslash;n&quot;
comma
id|fb.size
comma
id|fb.offset
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|sis_fb_free
r_int
id|sis_fb_free
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_sis_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_sis_mem_t
id|fb
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv
op_eq
l_int|NULL
op_logical_or
id|dev_priv-&gt;FBHeap
op_eq
l_int|NULL
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|fb
comma
(paren
id|drm_sis_mem_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|fb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mmBlockInHeap
c_func
(paren
id|dev_priv-&gt;FBHeap
comma
(paren
id|PMemBlock
)paren
id|fb.free
)paren
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|del_alloc_set
c_func
(paren
id|fb.context
comma
id|VIDEO_TYPE
comma
id|fb.free
)paren
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|mmFreeMem
c_func
(paren
(paren
id|PMemBlock
)paren
id|fb.free
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;free fb, free = 0x%lx&bslash;n&quot;
comma
id|fb.free
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* agp memory management */
DECL|function|sis_ioctl_agp_init
r_int
id|sis_ioctl_agp_init
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_sis_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_sis_agp_t
id|agp
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv
op_eq
l_int|NULL
)paren
(brace
id|dev-&gt;dev_private
op_assign
id|DRM
c_func
(paren
id|calloc
)paren
(paren
l_int|1
comma
r_sizeof
(paren
id|drm_sis_private_t
)paren
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv
op_eq
l_int|NULL
)paren
r_return
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev_priv-&gt;AGPHeap
op_ne
l_int|NULL
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|agp
comma
(paren
id|drm_sis_agp_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|agp
)paren
)paren
suffix:semicolon
id|dev_priv-&gt;AGPHeap
op_assign
id|mmInit
c_func
(paren
id|agp.offset
comma
id|agp.size
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;offset = %u, size = %u&quot;
comma
id|agp.offset
comma
id|agp.size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sis_ioctl_agp_alloc
r_int
id|sis_ioctl_agp_alloc
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_sis_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_sis_mem_t
id|agp
suffix:semicolon
id|PMemBlock
id|block
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv
op_eq
l_int|NULL
op_logical_or
id|dev_priv-&gt;AGPHeap
op_eq
l_int|NULL
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|agp
comma
(paren
id|drm_sis_mem_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|agp
)paren
)paren
suffix:semicolon
id|block
op_assign
id|mmAllocMem
c_func
(paren
id|dev_priv-&gt;AGPHeap
comma
id|agp.size
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
)paren
(brace
multiline_comment|/* TODO */
id|agp.offset
op_assign
id|block-&gt;ofs
suffix:semicolon
id|agp.free
op_assign
(paren
r_int
r_int
)paren
id|block
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|add_alloc_set
c_func
(paren
id|agp.context
comma
id|AGP_TYPE
comma
id|agp.free
)paren
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;adding to allocation set fails&bslash;n&quot;
)paren
suffix:semicolon
id|mmFreeMem
c_func
(paren
(paren
id|PMemBlock
)paren
id|agp.free
)paren
suffix:semicolon
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
id|agp.offset
op_assign
l_int|0
suffix:semicolon
id|agp.size
op_assign
l_int|0
suffix:semicolon
id|agp.free
op_assign
l_int|0
suffix:semicolon
)brace
id|DRM_COPY_TO_USER_IOCTL
c_func
(paren
(paren
id|drm_sis_mem_t
op_star
)paren
id|data
comma
id|agp
comma
r_sizeof
(paren
id|agp
)paren
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;alloc agp, size = %d, offset = %d&bslash;n&quot;
comma
id|agp.size
comma
id|agp.offset
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|sis_ioctl_agp_free
r_int
id|sis_ioctl_agp_free
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_sis_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_sis_mem_t
id|agp
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv
op_eq
l_int|NULL
op_logical_or
id|dev_priv-&gt;AGPHeap
op_eq
l_int|NULL
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|agp
comma
(paren
id|drm_sis_mem_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|agp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mmBlockInHeap
c_func
(paren
id|dev_priv-&gt;AGPHeap
comma
(paren
id|PMemBlock
)paren
id|agp.free
)paren
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|mmFreeMem
c_func
(paren
(paren
id|PMemBlock
)paren
id|agp.free
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|del_alloc_set
c_func
(paren
id|agp.context
comma
id|AGP_TYPE
comma
id|agp.free
)paren
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;free agp, free = 0x%lx&bslash;n&quot;
comma
id|agp.free
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sis_init_context
r_int
id|sis_init_context
c_func
(paren
r_int
id|context
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CONTEXT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|global_ppriv
(braket
id|i
)braket
dot
id|used
op_logical_and
(paren
id|global_ppriv
(braket
id|i
)braket
dot
id|context
op_eq
id|context
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
id|MAX_CONTEXT
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CONTEXT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|global_ppriv
(braket
id|i
)braket
dot
id|used
)paren
(brace
id|global_ppriv
(braket
id|i
)braket
dot
id|context
op_assign
id|context
suffix:semicolon
id|global_ppriv
(braket
id|i
)braket
dot
id|used
op_assign
l_int|1
suffix:semicolon
id|global_ppriv
(braket
id|i
)braket
dot
id|sets
(braket
l_int|0
)braket
op_assign
id|setInit
c_func
(paren
)paren
suffix:semicolon
id|global_ppriv
(braket
id|i
)braket
dot
id|sets
(braket
l_int|1
)braket
op_assign
id|setInit
c_func
(paren
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;init allocation set, socket=%d, &quot;
l_string|&quot;context = %d&bslash;n&quot;
comma
id|i
comma
id|context
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|i
op_ge
id|MAX_CONTEXT
)paren
op_logical_or
(paren
id|global_ppriv
(braket
id|i
)braket
dot
id|sets
(braket
l_int|0
)braket
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|global_ppriv
(braket
id|i
)braket
dot
id|sets
(braket
l_int|1
)braket
op_eq
l_int|NULL
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|sis_final_context
r_int
id|sis_final_context
c_func
(paren
r_int
id|context
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CONTEXT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|global_ppriv
(braket
id|i
)braket
dot
id|used
op_logical_and
(paren
id|global_ppriv
(braket
id|i
)braket
dot
id|context
op_eq
id|context
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|MAX_CONTEXT
)paren
(brace
id|set_t
op_star
id|set
suffix:semicolon
r_int
r_int
id|item
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;find socket %d, context = %d&bslash;n&quot;
comma
id|i
comma
id|context
)paren
suffix:semicolon
multiline_comment|/* Video Memory */
id|set
op_assign
id|global_ppriv
(braket
id|i
)braket
dot
id|sets
(braket
l_int|0
)braket
suffix:semicolon
id|retval
op_assign
id|setFirst
c_func
(paren
id|set
comma
op_amp
id|item
)paren
suffix:semicolon
r_while
c_loop
(paren
id|retval
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;free video memory 0x%x&bslash;n&quot;
comma
id|item
)paren
suffix:semicolon
macro_line|#if defined(__linux__) &amp;&amp; defined(CONFIG_FB_SIS)
id|sis_free
c_func
(paren
id|item
)paren
suffix:semicolon
macro_line|#else
id|mmFreeMem
c_func
(paren
(paren
id|PMemBlock
)paren
id|item
)paren
suffix:semicolon
macro_line|#endif
id|retval
op_assign
id|setNext
c_func
(paren
id|set
comma
op_amp
id|item
)paren
suffix:semicolon
)brace
id|setDestroy
c_func
(paren
id|set
)paren
suffix:semicolon
multiline_comment|/* AGP Memory */
id|set
op_assign
id|global_ppriv
(braket
id|i
)braket
dot
id|sets
(braket
l_int|1
)braket
suffix:semicolon
id|retval
op_assign
id|setFirst
c_func
(paren
id|set
comma
op_amp
id|item
)paren
suffix:semicolon
r_while
c_loop
(paren
id|retval
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;free agp memory 0x%x&bslash;n&quot;
comma
id|item
)paren
suffix:semicolon
id|mmFreeMem
c_func
(paren
(paren
id|PMemBlock
)paren
id|item
)paren
suffix:semicolon
id|retval
op_assign
id|setNext
c_func
(paren
id|set
comma
op_amp
id|item
)paren
suffix:semicolon
)brace
id|setDestroy
c_func
(paren
id|set
)paren
suffix:semicolon
id|global_ppriv
(braket
id|i
)braket
dot
id|used
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
eof
