multiline_comment|/**&n; * &bslash;file drm_dma.h &n; * DMA IOCTL and function support&n; *&n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/*&n; * Created: Fri Mar 19 14:30:16 1999 by faith@valinux.com&n; *&n; * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &quot;drmP.h&quot;
multiline_comment|/**&n; * Initialize the DMA data.&n; * &n; * &bslash;param dev DRM device.&n; * &bslash;return zero on success or a negative value on failure.&n; *&n; * Allocate and initialize a drm_device_dma structure.&n; */
DECL|function|drm_dma_setup
r_int
id|drm_dma_setup
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
id|dev-&gt;dma
op_assign
id|drm_alloc
c_func
(paren
r_sizeof
(paren
op_star
id|dev-&gt;dma
)paren
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;dma
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;dma
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dev-&gt;dma
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|DRM_MAX_ORDER
suffix:semicolon
id|i
op_increment
)paren
id|memset
c_func
(paren
op_amp
id|dev-&gt;dma-&gt;bufs
(braket
id|i
)braket
comma
l_int|0
comma
r_sizeof
(paren
id|dev-&gt;dma-&gt;bufs
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Cleanup the DMA resources.&n; *&n; * &bslash;param dev DRM device.&n; *&n; * Free all pages associated with DMA buffers, the buffers and pages lists, and&n; * finally the the drm_device::dma structure itself.&n; */
DECL|function|drm_dma_takedown
r_void
id|drm_dma_takedown
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma
)paren
r_return
suffix:semicolon
multiline_comment|/* Clear dma buffers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|DRM_MAX_ORDER
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|seg_count
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;order %d: buf_count = %d,&quot;
l_string|&quot; seg_count = %d&bslash;n&quot;
comma
id|i
comma
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buf_count
comma
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|seg_count
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|seg_count
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|seglist
(braket
id|j
)braket
)paren
(brace
id|drm_free_pages
c_func
(paren
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|seglist
(braket
id|j
)braket
comma
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|page_order
comma
id|DRM_MEM_DMA
)paren
suffix:semicolon
)brace
)brace
id|drm_free
c_func
(paren
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|seglist
comma
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|seg_count
op_star
r_sizeof
(paren
op_star
id|dma-&gt;bufs
(braket
l_int|0
)braket
dot
id|seglist
)paren
comma
id|DRM_MEM_SEGS
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buf_count
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buf_count
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buflist
(braket
id|j
)braket
dot
id|dev_private
)paren
(brace
id|drm_free
c_func
(paren
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buflist
(braket
id|j
)braket
dot
id|dev_private
comma
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buflist
(braket
id|j
)braket
dot
id|dev_priv_size
comma
id|DRM_MEM_BUFS
)paren
suffix:semicolon
)brace
)brace
id|drm_free
c_func
(paren
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buflist
comma
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buf_count
op_star
r_sizeof
(paren
op_star
id|dma-&gt;bufs
(braket
l_int|0
)braket
dot
id|buflist
)paren
comma
id|DRM_MEM_BUFS
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dma-&gt;buflist
)paren
(brace
id|drm_free
c_func
(paren
id|dma-&gt;buflist
comma
id|dma-&gt;buf_count
op_star
r_sizeof
(paren
op_star
id|dma-&gt;buflist
)paren
comma
id|DRM_MEM_BUFS
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dma-&gt;pagelist
)paren
(brace
id|drm_free
c_func
(paren
id|dma-&gt;pagelist
comma
id|dma-&gt;page_count
op_star
r_sizeof
(paren
op_star
id|dma-&gt;pagelist
)paren
comma
id|DRM_MEM_PAGES
)paren
suffix:semicolon
)brace
id|drm_free
c_func
(paren
id|dev-&gt;dma
comma
r_sizeof
(paren
op_star
id|dev-&gt;dma
)paren
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|dev-&gt;dma
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * Free a buffer.&n; *&n; * &bslash;param dev DRM device.&n; * &bslash;param buf buffer to free.&n; * &n; * Resets the fields of &bslash;p buf.&n; */
DECL|function|drm_free_buffer
r_void
id|drm_free_buffer
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|drm_buf_t
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
suffix:semicolon
id|buf-&gt;waiting
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;pending
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;filp
op_assign
l_int|NULL
suffix:semicolon
id|buf-&gt;used
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|drm_core_check_feature
c_func
(paren
id|dev
comma
id|DRIVER_DMA_QUEUE
)paren
op_logical_and
id|waitqueue_active
c_func
(paren
op_amp
id|buf-&gt;dma_wait
)paren
)paren
(brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|buf-&gt;dma_wait
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * Reclaim the buffers.&n; *&n; * &bslash;param filp file pointer.&n; *&n; * Frees each buffer associated with &bslash;p filp not already on the hardware.&n; */
DECL|function|drm_core_reclaim_buffers
r_void
id|drm_core_reclaim_buffers
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma
)paren
r_return
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
id|dma-&gt;buf_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dma-&gt;buflist
(braket
id|i
)braket
op_member_access_from_pointer
id|filp
op_eq
id|filp
)paren
(brace
r_switch
c_cond
(paren
id|dma-&gt;buflist
(braket
id|i
)braket
op_member_access_from_pointer
id|list
)paren
(brace
r_case
id|DRM_LIST_NONE
suffix:colon
id|drm_free_buffer
c_func
(paren
id|dev
comma
id|dma-&gt;buflist
(braket
id|i
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DRM_LIST_WAIT
suffix:colon
id|dma-&gt;buflist
(braket
id|i
)braket
op_member_access_from_pointer
id|list
op_assign
id|DRM_LIST_RECLAIM
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Buffer already on hardware. */
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|variable|drm_core_reclaim_buffers
id|EXPORT_SYMBOL
c_func
(paren
id|drm_core_reclaim_buffers
)paren
suffix:semicolon
eof
