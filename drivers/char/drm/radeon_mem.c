multiline_comment|/* radeon_mem.c -- Simple agp/fb memory manager for radeon -*- linux-c -*-&n; *&n; * Copyright (C) The Weather Channel, Inc.  2002.  All Rights Reserved.&n; * &n; * The Weather Channel (TM) funded Tungsten Graphics to develop the&n; * initial release of the Radeon 8500 driver under the XFree86 license.&n; * This notice must be preserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Keith Whitwell &lt;keith@tungstengraphics.com&gt;&n; */
macro_line|#include &quot;radeon.h&quot;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm.h&quot;
macro_line|#include &quot;radeon_drm.h&quot;
macro_line|#include &quot;radeon_drv.h&quot;
multiline_comment|/* Very simple allocator for agp memory, working on a static range&n; * already mapped into each client&squot;s address space.  &n; */
DECL|function|split_block
r_static
r_struct
id|mem_block
op_star
id|split_block
c_func
(paren
r_struct
id|mem_block
op_star
id|p
comma
r_int
id|start
comma
r_int
id|size
comma
r_int
id|pid
)paren
(brace
multiline_comment|/* Maybe cut off the start of an existing block */
r_if
c_cond
(paren
id|start
OG
id|p-&gt;start
)paren
(brace
r_struct
id|mem_block
op_star
id|newblock
op_assign
id|DRM_MALLOC
c_func
(paren
r_sizeof
(paren
op_star
id|newblock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newblock
)paren
r_goto
id|out
suffix:semicolon
id|newblock-&gt;start
op_assign
id|start
suffix:semicolon
id|newblock-&gt;size
op_assign
id|p-&gt;size
op_minus
(paren
id|start
op_minus
id|p-&gt;start
)paren
suffix:semicolon
id|newblock-&gt;pid
op_assign
l_int|0
suffix:semicolon
id|newblock-&gt;next
op_assign
id|p-&gt;next
suffix:semicolon
id|newblock-&gt;prev
op_assign
id|p
suffix:semicolon
id|p-&gt;next-&gt;prev
op_assign
id|newblock
suffix:semicolon
id|p-&gt;next
op_assign
id|newblock
suffix:semicolon
id|p-&gt;size
op_sub_assign
id|newblock-&gt;size
suffix:semicolon
id|p
op_assign
id|newblock
suffix:semicolon
)brace
multiline_comment|/* Maybe cut off the end of an existing block */
r_if
c_cond
(paren
id|size
OL
id|p-&gt;size
)paren
(brace
r_struct
id|mem_block
op_star
id|newblock
op_assign
id|DRM_MALLOC
c_func
(paren
r_sizeof
(paren
op_star
id|newblock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newblock
)paren
r_goto
id|out
suffix:semicolon
id|newblock-&gt;start
op_assign
id|start
op_plus
id|size
suffix:semicolon
id|newblock-&gt;size
op_assign
id|p-&gt;size
op_minus
id|size
suffix:semicolon
id|newblock-&gt;pid
op_assign
l_int|0
suffix:semicolon
id|newblock-&gt;next
op_assign
id|p-&gt;next
suffix:semicolon
id|newblock-&gt;prev
op_assign
id|p
suffix:semicolon
id|p-&gt;next-&gt;prev
op_assign
id|newblock
suffix:semicolon
id|p-&gt;next
op_assign
id|newblock
suffix:semicolon
id|p-&gt;size
op_assign
id|size
suffix:semicolon
)brace
id|out
suffix:colon
multiline_comment|/* Our block is in the middle */
id|p-&gt;pid
op_assign
id|pid
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|alloc_block
r_static
r_struct
id|mem_block
op_star
id|alloc_block
c_func
(paren
r_struct
id|mem_block
op_star
id|heap
comma
r_int
id|size
comma
r_int
id|align2
comma
r_int
id|pid
)paren
(brace
r_struct
id|mem_block
op_star
id|p
suffix:semicolon
r_int
id|mask
op_assign
(paren
l_int|1
op_lshift
id|align2
)paren
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|heap-&gt;next
suffix:semicolon
id|p
op_ne
id|heap
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_int
id|start
op_assign
(paren
id|p-&gt;start
op_plus
id|mask
)paren
op_amp
op_complement
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pid
op_eq
l_int|0
op_logical_and
id|start
op_plus
id|size
op_le
id|p-&gt;start
op_plus
id|p-&gt;size
)paren
r_return
id|split_block
c_func
(paren
id|p
comma
id|start
comma
id|size
comma
id|pid
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|find_block
r_static
r_struct
id|mem_block
op_star
id|find_block
c_func
(paren
r_struct
id|mem_block
op_star
id|heap
comma
r_int
id|start
)paren
(brace
r_struct
id|mem_block
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|heap-&gt;next
suffix:semicolon
id|p
op_ne
id|heap
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
r_if
c_cond
(paren
id|p-&gt;start
op_eq
id|start
)paren
r_return
id|p
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|free_block
r_static
r_void
id|free_block
c_func
(paren
r_struct
id|mem_block
op_star
id|p
)paren
(brace
id|p-&gt;pid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Assumes a single contiguous range.  Needs a special pid in&n;&t; * &squot;heap&squot; to stop it being subsumed.&n;&t; */
r_if
c_cond
(paren
id|p-&gt;next-&gt;pid
op_eq
l_int|0
)paren
(brace
r_struct
id|mem_block
op_star
id|q
op_assign
id|p-&gt;next
suffix:semicolon
id|p-&gt;size
op_add_assign
id|q-&gt;size
suffix:semicolon
id|p-&gt;next
op_assign
id|q-&gt;next
suffix:semicolon
id|p-&gt;next-&gt;prev
op_assign
id|p
suffix:semicolon
id|DRM_FREE
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;prev-&gt;pid
op_eq
l_int|0
)paren
(brace
r_struct
id|mem_block
op_star
id|q
op_assign
id|p-&gt;prev
suffix:semicolon
id|q-&gt;size
op_add_assign
id|p-&gt;size
suffix:semicolon
id|q-&gt;next
op_assign
id|p-&gt;next
suffix:semicolon
id|q-&gt;next-&gt;prev
op_assign
id|q
suffix:semicolon
id|DRM_FREE
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
DECL|function|print_heap
r_static
r_void
id|print_heap
c_func
(paren
r_struct
id|mem_block
op_star
id|heap
)paren
(brace
r_struct
id|mem_block
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|heap-&gt;next
suffix:semicolon
id|p
op_ne
id|heap
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
id|DRM_DEBUG
c_func
(paren
l_string|&quot;0x%x..0x%x (0x%x) -- owner %d&bslash;n&quot;
comma
id|p-&gt;start
comma
id|p-&gt;start
op_plus
id|p-&gt;size
comma
id|p-&gt;size
comma
id|p-&gt;pid
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize.  How to check for an uninitialized heap?&n; */
DECL|function|init_heap
r_static
r_int
id|init_heap
c_func
(paren
r_struct
id|mem_block
op_star
op_star
id|heap
comma
r_int
id|start
comma
r_int
id|size
)paren
(brace
r_struct
id|mem_block
op_star
id|blocks
op_assign
id|DRM_MALLOC
c_func
(paren
r_sizeof
(paren
op_star
id|blocks
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blocks
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_star
id|heap
op_assign
id|DRM_MALLOC
c_func
(paren
r_sizeof
(paren
op_star
op_star
id|heap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|heap
)paren
(brace
id|DRM_FREE
c_func
(paren
id|blocks
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|blocks-&gt;start
op_assign
id|start
suffix:semicolon
id|blocks-&gt;size
op_assign
id|size
suffix:semicolon
id|blocks-&gt;pid
op_assign
l_int|0
suffix:semicolon
id|blocks-&gt;next
op_assign
id|blocks-&gt;prev
op_assign
op_star
id|heap
suffix:semicolon
id|memset
c_func
(paren
op_star
id|heap
comma
l_int|0
comma
r_sizeof
(paren
op_star
op_star
id|heap
)paren
)paren
suffix:semicolon
(paren
op_star
id|heap
)paren
op_member_access_from_pointer
id|pid
op_assign
op_minus
l_int|1
suffix:semicolon
(paren
op_star
id|heap
)paren
op_member_access_from_pointer
id|next
op_assign
(paren
op_star
id|heap
)paren
op_member_access_from_pointer
id|prev
op_assign
id|blocks
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Free all blocks associated with the releasing pid.&n; */
DECL|function|radeon_mem_release
r_void
id|radeon_mem_release
c_func
(paren
r_struct
id|mem_block
op_star
id|heap
)paren
(brace
r_int
id|pid
op_assign
id|DRM_CURRENTPID
suffix:semicolon
r_struct
id|mem_block
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|heap
op_logical_or
op_logical_neg
id|heap-&gt;next
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|heap-&gt;next
suffix:semicolon
id|p
op_ne
id|heap
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pid
op_eq
id|pid
)paren
id|p-&gt;pid
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Assumes a single contiguous range.  Needs a special pid in&n;&t; * &squot;heap&squot; to stop it being subsumed.&n;&t; */
r_for
c_loop
(paren
id|p
op_assign
id|heap-&gt;next
suffix:semicolon
id|p
op_ne
id|heap
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_while
c_loop
(paren
id|p-&gt;pid
op_eq
l_int|0
op_logical_and
id|p-&gt;next-&gt;pid
op_eq
l_int|0
)paren
(brace
r_struct
id|mem_block
op_star
id|q
op_assign
id|p-&gt;next
suffix:semicolon
id|p-&gt;size
op_add_assign
id|q-&gt;size
suffix:semicolon
id|p-&gt;next
op_assign
id|q-&gt;next
suffix:semicolon
id|p-&gt;next-&gt;prev
op_assign
id|p
suffix:semicolon
id|DRM_FREE
c_func
(paren
id|q
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Shutdown.&n; */
DECL|function|radeon_mem_takedown
r_void
id|radeon_mem_takedown
c_func
(paren
r_struct
id|mem_block
op_star
op_star
id|heap
)paren
(brace
r_struct
id|mem_block
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|heap
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
(paren
op_star
id|heap
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|p
op_ne
op_star
id|heap
suffix:semicolon
)paren
(brace
r_struct
id|mem_block
op_star
id|q
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
id|DRM_FREE
c_func
(paren
id|q
)paren
suffix:semicolon
)brace
id|DRM_FREE
c_func
(paren
op_star
id|heap
)paren
suffix:semicolon
op_star
id|heap
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* IOCTL HANDLERS */
DECL|function|get_heap
r_static
r_struct
id|mem_block
op_star
op_star
id|get_heap
c_func
(paren
id|drm_radeon_private_t
op_star
id|dev_priv
comma
r_int
id|region
)paren
(brace
r_switch
c_cond
(paren
id|region
)paren
(brace
r_case
id|RADEON_MEM_REGION_AGP
suffix:colon
r_return
op_amp
id|dev_priv-&gt;agp_heap
suffix:semicolon
r_case
id|RADEON_MEM_REGION_FB
suffix:colon
r_return
op_amp
id|dev_priv-&gt;fb_heap
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|radeon_mem_alloc
r_int
id|radeon_mem_alloc
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_radeon_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_radeon_mem_alloc_t
id|alloc
suffix:semicolon
r_struct
id|mem_block
op_star
id|block
comma
op_star
op_star
id|heap
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_priv
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;%s called with no initialization&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|alloc
comma
(paren
id|drm_radeon_mem_alloc_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|alloc
)paren
)paren
suffix:semicolon
id|heap
op_assign
id|get_heap
c_func
(paren
id|dev_priv
comma
id|alloc.region
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|heap
op_logical_or
op_logical_neg
op_star
id|heap
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EFAULT
)paren
suffix:semicolon
multiline_comment|/* Make things easier on ourselves: all allocations at least&n;&t; * 4k aligned.&n;&t; */
r_if
c_cond
(paren
id|alloc.alignment
OL
l_int|12
)paren
id|alloc.alignment
op_assign
l_int|12
suffix:semicolon
id|block
op_assign
id|alloc_block
c_func
(paren
op_star
id|heap
comma
id|alloc.size
comma
id|alloc.alignment
comma
id|DRM_CURRENTPID
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
)paren
r_return
id|DRM_ERR
c_func
(paren
id|ENOMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DRM_COPY_TO_USER
c_func
(paren
id|alloc.region_offset
comma
op_amp
id|block-&gt;start
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;copy_to_user&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|EFAULT
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|radeon_mem_free
r_int
id|radeon_mem_free
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_radeon_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_radeon_mem_free_t
id|memfree
suffix:semicolon
r_struct
id|mem_block
op_star
id|block
comma
op_star
op_star
id|heap
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_priv
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;%s called with no initialization&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|memfree
comma
(paren
id|drm_radeon_mem_free_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|memfree
)paren
)paren
suffix:semicolon
id|heap
op_assign
id|get_heap
c_func
(paren
id|dev_priv
comma
id|memfree.region
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|heap
op_logical_or
op_logical_neg
op_star
id|heap
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EFAULT
)paren
suffix:semicolon
id|block
op_assign
id|find_block
c_func
(paren
op_star
id|heap
comma
id|memfree.region_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EFAULT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block-&gt;pid
op_ne
id|DRM_CURRENTPID
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EPERM
)paren
suffix:semicolon
id|free_block
c_func
(paren
id|block
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|radeon_mem_init_heap
r_int
id|radeon_mem_init_heap
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
(brace
id|DRM_DEVICE
suffix:semicolon
id|drm_radeon_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_radeon_mem_init_heap_t
id|initheap
suffix:semicolon
r_struct
id|mem_block
op_star
op_star
id|heap
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_priv
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;%s called with no initialization&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
id|DRM_COPY_FROM_USER_IOCTL
c_func
(paren
id|initheap
comma
(paren
id|drm_radeon_mem_init_heap_t
op_star
)paren
id|data
comma
r_sizeof
(paren
id|initheap
)paren
)paren
suffix:semicolon
id|heap
op_assign
id|get_heap
c_func
(paren
id|dev_priv
comma
id|initheap.region
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|heap
)paren
r_return
id|DRM_ERR
c_func
(paren
id|EFAULT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|heap
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;heap already initialized?&quot;
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|EFAULT
)paren
suffix:semicolon
)brace
r_return
id|init_heap
c_func
(paren
id|heap
comma
id|initheap.start
comma
id|initheap.size
)paren
suffix:semicolon
)brace
eof
