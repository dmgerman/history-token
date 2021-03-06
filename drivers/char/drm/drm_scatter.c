multiline_comment|/**&n; * &bslash;file drm_scatter.h &n; * IOCTLs to manage scatter/gather memory&n; *&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/*&n; * Created: Mon Dec 18 23:20:54 2000 by gareth@valinux.com&n; *&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &quot;drmP.h&quot;
DECL|macro|DEBUG_SCATTER
mdefine_line|#define DEBUG_SCATTER 0
DECL|function|drm_sg_cleanup
r_void
id|drm_sg_cleanup
c_func
(paren
id|drm_sg_mem_t
op_star
id|entry
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
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
id|entry-&gt;pages
suffix:semicolon
id|i
op_increment
)paren
(brace
id|page
op_assign
id|entry-&gt;pagelist
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|vfree
c_func
(paren
id|entry
op_member_access_from_pointer
r_virtual
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|entry-&gt;busaddr
comma
id|entry-&gt;pages
op_star
r_sizeof
(paren
op_star
id|entry-&gt;busaddr
)paren
comma
id|DRM_MEM_PAGES
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|entry-&gt;pagelist
comma
id|entry-&gt;pages
op_star
r_sizeof
(paren
op_star
id|entry-&gt;pagelist
)paren
comma
id|DRM_MEM_PAGES
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|entry
comma
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|DRM_MEM_SGLISTS
)paren
suffix:semicolon
)brace
DECL|function|drm_sg_alloc
r_int
id|drm_sg_alloc
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;head-&gt;dev
suffix:semicolon
id|drm_scatter_gather_t
id|__user
op_star
id|argp
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
id|drm_scatter_gather_t
id|request
suffix:semicolon
id|drm_sg_mem_t
op_star
id|entry
suffix:semicolon
r_int
r_int
id|pages
comma
id|i
comma
id|j
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drm_core_check_feature
c_func
(paren
id|dev
comma
id|DRIVER_SG
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;sg
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|request
comma
id|argp
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|entry
op_assign
id|drm_alloc
c_func
(paren
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|DRM_MEM_SGLISTS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|entry
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|entry
)paren
)paren
suffix:semicolon
id|pages
op_assign
(paren
id|request.size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;sg size=%ld pages=%ld&bslash;n&quot;
comma
id|request.size
comma
id|pages
)paren
suffix:semicolon
id|entry-&gt;pages
op_assign
id|pages
suffix:semicolon
id|entry-&gt;pagelist
op_assign
id|drm_alloc
c_func
(paren
id|pages
op_star
r_sizeof
(paren
op_star
id|entry-&gt;pagelist
)paren
comma
id|DRM_MEM_PAGES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;pagelist
)paren
(brace
id|drm_free
c_func
(paren
id|entry
comma
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|DRM_MEM_SGLISTS
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|entry-&gt;pagelist
comma
l_int|0
comma
id|pages
op_star
r_sizeof
(paren
op_star
id|entry-&gt;pagelist
)paren
)paren
suffix:semicolon
id|entry-&gt;busaddr
op_assign
id|drm_alloc
c_func
(paren
id|pages
op_star
r_sizeof
(paren
op_star
id|entry-&gt;busaddr
)paren
comma
id|DRM_MEM_PAGES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;busaddr
)paren
(brace
id|drm_free
c_func
(paren
id|entry-&gt;pagelist
comma
id|entry-&gt;pages
op_star
r_sizeof
(paren
op_star
id|entry-&gt;pagelist
)paren
comma
id|DRM_MEM_PAGES
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|entry
comma
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|DRM_MEM_SGLISTS
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|entry-&gt;busaddr
comma
l_int|0
comma
id|pages
op_star
r_sizeof
(paren
op_star
id|entry-&gt;busaddr
)paren
)paren
suffix:semicolon
id|entry
op_member_access_from_pointer
r_virtual
op_assign
id|vmalloc_32
c_func
(paren
id|pages
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
op_member_access_from_pointer
r_virtual
)paren
(brace
id|drm_free
c_func
(paren
id|entry-&gt;busaddr
comma
id|entry-&gt;pages
op_star
r_sizeof
(paren
op_star
id|entry-&gt;busaddr
)paren
comma
id|DRM_MEM_PAGES
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|entry-&gt;pagelist
comma
id|entry-&gt;pages
op_star
r_sizeof
(paren
op_star
id|entry-&gt;pagelist
)paren
comma
id|DRM_MEM_PAGES
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|entry
comma
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|DRM_MEM_SGLISTS
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* This also forces the mapping of COW pages, so our page list&n;&t; * will be valid.  Please don&squot;t remove it...&n;&t; */
id|memset
c_func
(paren
id|entry
op_member_access_from_pointer
r_virtual
comma
l_int|0
comma
id|pages
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|entry-&gt;handle
op_assign
(paren
r_int
r_int
)paren
id|entry
op_member_access_from_pointer
r_virtual
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;sg alloc handle  = %08lx&bslash;n&quot;
comma
id|entry-&gt;handle
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;sg alloc virtual = %p&bslash;n&quot;
comma
id|entry
op_member_access_from_pointer
r_virtual
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|entry-&gt;handle
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|pages
suffix:semicolon
id|i
op_add_assign
id|PAGE_SIZE
comma
id|j
op_increment
)paren
(brace
id|entry-&gt;pagelist
(braket
id|j
)braket
op_assign
id|vmalloc_to_page
c_func
(paren
(paren
r_void
op_star
)paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;pagelist
(braket
id|j
)braket
)paren
r_goto
id|failed
suffix:semicolon
id|SetPageReserved
c_func
(paren
id|entry-&gt;pagelist
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
id|request.handle
op_assign
id|entry-&gt;handle
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|request
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
(brace
id|drm_sg_cleanup
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|dev-&gt;sg
op_assign
id|entry
suffix:semicolon
macro_line|#if DEBUG_SCATTER
multiline_comment|/* Verify that each page points to its virtual address, and vice&n;&t; * versa.&n;&t; */
(brace
r_int
id|error
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
id|pages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
op_star
id|tmp
suffix:semicolon
id|tmp
op_assign
id|page_address
c_func
(paren
id|entry-&gt;pagelist
(braket
id|i
)braket
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
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|j
op_increment
comma
id|tmp
op_increment
)paren
(brace
op_star
id|tmp
op_assign
l_int|0xcafebabe
suffix:semicolon
)brace
id|tmp
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|entry
op_member_access_from_pointer
r_virtual
op_plus
(paren
id|PAGE_SIZE
op_star
id|i
)paren
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
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|j
op_increment
comma
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|tmp
op_ne
l_int|0xcafebabe
op_logical_and
id|error
op_eq
l_int|0
)paren
(brace
id|error
op_assign
l_int|1
suffix:semicolon
id|DRM_ERROR
c_func
(paren
l_string|&quot;Scatter allocation error, &quot;
l_string|&quot;pagelist does not match &quot;
l_string|&quot;virtual mapping&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|tmp
op_assign
id|page_address
c_func
(paren
id|entry-&gt;pagelist
(braket
id|i
)braket
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
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|j
op_increment
comma
id|tmp
op_increment
)paren
(brace
op_star
id|tmp
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
id|DRM_ERROR
c_func
(paren
l_string|&quot;Scatter allocation matches pagelist&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
id|failed
suffix:colon
id|drm_sg_cleanup
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|drm_sg_free
r_int
id|drm_sg_free
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;head-&gt;dev
suffix:semicolon
id|drm_scatter_gather_t
id|request
suffix:semicolon
id|drm_sg_mem_t
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drm_core_check_feature
c_func
(paren
id|dev
comma
id|DRIVER_SG
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|request
comma
(paren
id|drm_scatter_gather_t
id|__user
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|entry
op_assign
id|dev-&gt;sg
suffix:semicolon
id|dev-&gt;sg
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
op_logical_or
id|entry-&gt;handle
op_ne
id|request.handle
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;sg free virtual  = %p&bslash;n&quot;
comma
id|entry
op_member_access_from_pointer
r_virtual
)paren
suffix:semicolon
id|drm_sg_cleanup
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
