multiline_comment|/* drm_agpsupport.h -- DRM support for AGP/GART backend -*- linux-c -*-&n; * Created: Mon Dec 13 09:56:45 1999 by faith@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Author:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#if __REALLY_HAVE_AGP
DECL|macro|DRM_AGP_GET
mdefine_line|#define DRM_AGP_GET (drm_agp_t *)inter_module_get(&quot;drm_agp&quot;)
DECL|macro|DRM_AGP_PUT
mdefine_line|#define DRM_AGP_PUT inter_module_put(&quot;drm_agp&quot;)
DECL|variable|drm_agp
r_static
r_const
id|drm_agp_t
op_star
id|drm_agp
op_assign
l_int|NULL
suffix:semicolon
DECL|function|agp_info
r_int
id|DRM
c_func
(paren
id|agp_info
)paren
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
id|priv-&gt;dev
suffix:semicolon
id|agp_kern_info
op_star
id|kern
suffix:semicolon
id|drm_agp_info_t
id|info
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;agp
op_logical_or
op_logical_neg
id|dev-&gt;agp-&gt;acquired
op_logical_or
op_logical_neg
id|drm_agp-&gt;copy_info
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|kern
op_assign
op_amp
id|dev-&gt;agp-&gt;agp_info
suffix:semicolon
id|info.agp_version_major
op_assign
id|kern-&gt;version.major
suffix:semicolon
id|info.agp_version_minor
op_assign
id|kern-&gt;version.minor
suffix:semicolon
id|info.mode
op_assign
id|kern-&gt;mode
suffix:semicolon
id|info.aperture_base
op_assign
id|kern-&gt;aper_base
suffix:semicolon
id|info.aperture_size
op_assign
id|kern-&gt;aper_size
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
id|info.memory_allowed
op_assign
id|kern-&gt;max_memory
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|info.memory_used
op_assign
id|kern-&gt;current_memory
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|info.id_vendor
op_assign
id|kern-&gt;device-&gt;vendor
suffix:semicolon
id|info.id_device
op_assign
id|kern-&gt;device-&gt;device
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_agp_info_t
op_star
)paren
id|arg
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_acquire
r_int
id|DRM
c_func
(paren
id|agp_acquire
)paren
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
id|priv-&gt;dev
suffix:semicolon
r_int
id|retcode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;agp
op_logical_or
id|dev-&gt;agp-&gt;acquired
op_logical_or
op_logical_neg
id|drm_agp-&gt;acquire
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retcode
op_assign
id|drm_agp
op_member_access_from_pointer
id|acquire
c_func
(paren
)paren
)paren
)paren
r_return
id|retcode
suffix:semicolon
id|dev-&gt;agp-&gt;acquired
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_release
r_int
id|DRM
c_func
(paren
id|agp_release
)paren
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
id|priv-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;agp
op_logical_or
op_logical_neg
id|dev-&gt;agp-&gt;acquired
op_logical_or
op_logical_neg
id|drm_agp-&gt;release
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|drm_agp
op_member_access_from_pointer
id|release
c_func
(paren
)paren
suffix:semicolon
id|dev-&gt;agp-&gt;acquired
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_do_release
r_void
id|DRM
c_func
(paren
id|agp_do_release
)paren
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|drm_agp-&gt;release
)paren
id|drm_agp
op_member_access_from_pointer
id|release
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|agp_enable
r_int
id|DRM
c_func
(paren
id|agp_enable
)paren
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
id|priv-&gt;dev
suffix:semicolon
id|drm_agp_mode_t
id|mode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;agp
op_logical_or
op_logical_neg
id|dev-&gt;agp-&gt;acquired
op_logical_or
op_logical_neg
id|drm_agp-&gt;enable
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
id|mode
comma
(paren
id|drm_agp_mode_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|mode
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dev-&gt;agp-&gt;mode
op_assign
id|mode.mode
suffix:semicolon
id|drm_agp
op_member_access_from_pointer
id|enable
c_func
(paren
id|mode.mode
)paren
suffix:semicolon
id|dev-&gt;agp-&gt;base
op_assign
id|dev-&gt;agp-&gt;agp_info.aper_base
suffix:semicolon
id|dev-&gt;agp-&gt;enabled
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_alloc
r_int
id|DRM
c_func
(paren
id|agp_alloc
)paren
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
id|priv-&gt;dev
suffix:semicolon
id|drm_agp_buffer_t
id|request
suffix:semicolon
id|drm_agp_mem_t
op_star
id|entry
suffix:semicolon
id|agp_memory
op_star
id|memory
suffix:semicolon
r_int
r_int
id|pages
suffix:semicolon
id|u32
id|type
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;agp
op_logical_or
op_logical_neg
id|dev-&gt;agp-&gt;acquired
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
id|drm_agp_buffer_t
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|entry
op_assign
id|DRM
c_func
(paren
id|alloc
)paren
(paren
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|DRM_MEM_AGPLISTS
)paren
)paren
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
id|type
op_assign
(paren
id|u32
)paren
id|request.type
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|memory
op_assign
id|DRM
c_func
(paren
id|alloc_agp
)paren
(paren
id|pages
comma
id|type
)paren
)paren
)paren
(brace
id|DRM
c_func
(paren
id|free
)paren
(paren
id|entry
comma
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|DRM_MEM_AGPLISTS
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|entry-&gt;handle
op_assign
(paren
r_int
r_int
)paren
id|memory-&gt;memory
suffix:semicolon
id|entry-&gt;memory
op_assign
id|memory
suffix:semicolon
id|entry-&gt;bound
op_assign
l_int|0
suffix:semicolon
id|entry-&gt;pages
op_assign
id|pages
suffix:semicolon
id|entry-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|entry-&gt;next
op_assign
id|dev-&gt;agp-&gt;memory
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;agp-&gt;memory
)paren
id|dev-&gt;agp-&gt;memory-&gt;prev
op_assign
id|entry
suffix:semicolon
id|dev-&gt;agp-&gt;memory
op_assign
id|entry
suffix:semicolon
id|request.handle
op_assign
id|entry-&gt;handle
suffix:semicolon
id|request.physical
op_assign
id|memory-&gt;physical
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_agp_buffer_t
op_star
)paren
id|arg
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
id|dev-&gt;agp-&gt;memory
op_assign
id|entry-&gt;next
suffix:semicolon
id|dev-&gt;agp-&gt;memory-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|DRM
c_func
(paren
id|free_agp
)paren
(paren
id|memory
comma
id|pages
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|free
)paren
(paren
id|entry
comma
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|DRM_MEM_AGPLISTS
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_lookup_entry
r_static
id|drm_agp_mem_t
op_star
id|DRM
c_func
(paren
id|agp_lookup_entry
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
r_int
id|handle
)paren
(brace
id|drm_agp_mem_t
op_star
id|entry
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|dev-&gt;agp-&gt;memory
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;handle
op_eq
id|handle
)paren
r_return
id|entry
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|agp_unbind
r_int
id|DRM
c_func
(paren
id|agp_unbind
)paren
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
id|priv-&gt;dev
suffix:semicolon
id|drm_agp_binding_t
id|request
suffix:semicolon
id|drm_agp_mem_t
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;agp
op_logical_or
op_logical_neg
id|dev-&gt;agp-&gt;acquired
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
id|drm_agp_binding_t
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|entry
op_assign
id|DRM
c_func
(paren
id|agp_lookup_entry
)paren
(paren
id|dev
comma
id|request.handle
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;bound
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|DRM
c_func
(paren
id|unbind_agp
)paren
(paren
id|entry-&gt;memory
)paren
suffix:semicolon
)brace
DECL|function|agp_bind
r_int
id|DRM
c_func
(paren
id|agp_bind
)paren
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
id|priv-&gt;dev
suffix:semicolon
id|drm_agp_binding_t
id|request
suffix:semicolon
id|drm_agp_mem_t
op_star
id|entry
suffix:semicolon
r_int
id|retcode
suffix:semicolon
r_int
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;agp
op_logical_or
op_logical_neg
id|dev-&gt;agp-&gt;acquired
op_logical_or
op_logical_neg
id|drm_agp-&gt;bind_memory
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
id|drm_agp_binding_t
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|entry
op_assign
id|DRM
c_func
(paren
id|agp_lookup_entry
)paren
(paren
id|dev
comma
id|request.handle
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;bound
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|page
op_assign
(paren
id|request.offset
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retcode
op_assign
id|DRM
c_func
(paren
id|bind_agp
)paren
(paren
id|entry-&gt;memory
comma
id|page
)paren
)paren
)paren
r_return
id|retcode
suffix:semicolon
id|entry-&gt;bound
op_assign
id|dev-&gt;agp-&gt;base
op_plus
(paren
id|page
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;base = 0x%lx entry-&gt;bound = 0x%lx&bslash;n&quot;
comma
id|dev-&gt;agp-&gt;base
comma
id|entry-&gt;bound
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_free
r_int
id|DRM
c_func
(paren
id|agp_free
)paren
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
id|priv-&gt;dev
suffix:semicolon
id|drm_agp_buffer_t
id|request
suffix:semicolon
id|drm_agp_mem_t
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;agp
op_logical_or
op_logical_neg
id|dev-&gt;agp-&gt;acquired
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
id|drm_agp_buffer_t
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|entry
op_assign
id|DRM
c_func
(paren
id|agp_lookup_entry
)paren
(paren
id|dev
comma
id|request.handle
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;bound
)paren
id|DRM
c_func
(paren
id|unbind_agp
)paren
(paren
id|entry-&gt;memory
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;prev
)paren
id|entry-&gt;prev-&gt;next
op_assign
id|entry-&gt;next
suffix:semicolon
r_else
id|dev-&gt;agp-&gt;memory
op_assign
id|entry-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;next
)paren
id|entry-&gt;next-&gt;prev
op_assign
id|entry-&gt;prev
suffix:semicolon
id|DRM
c_func
(paren
id|free_agp
)paren
(paren
id|entry-&gt;memory
comma
id|entry-&gt;pages
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|free
)paren
(paren
id|entry
comma
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|DRM_MEM_AGPLISTS
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|agp_init
id|drm_agp_head_t
op_star
id|DRM
c_func
(paren
id|agp_init
)paren
(paren
r_void
)paren
(brace
id|drm_agp_head_t
op_star
id|head
op_assign
l_int|NULL
suffix:semicolon
id|drm_agp
op_assign
id|DRM_AGP_GET
suffix:semicolon
r_if
c_cond
(paren
id|drm_agp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|head
op_assign
id|DRM
c_func
(paren
id|alloc
)paren
(paren
r_sizeof
(paren
op_star
id|head
)paren
comma
id|DRM_MEM_AGPLISTS
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|head
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|head
)paren
)paren
suffix:semicolon
id|drm_agp
op_member_access_from_pointer
id|copy_info
c_func
(paren
op_amp
id|head-&gt;agp_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head-&gt;agp_info.chipset
op_eq
id|NOT_SUPPORTED
)paren
(brace
id|DRM
c_func
(paren
id|free
)paren
(paren
id|head
comma
r_sizeof
(paren
op_star
id|head
)paren
comma
id|DRM_MEM_AGPLISTS
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|head-&gt;memory
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|head-&gt;agp_info.chipset
)paren
(brace
r_case
id|INTEL_GENERIC
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Intel&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTEL_LX
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Intel 440LX&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTEL_BX
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Intel 440BX&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTEL_GX
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Intel 440GX&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTEL_I810
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Intel i810&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTEL_I815
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Intel i815&quot;
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x02040f /* KERNEL_VERSION(2,4,15) */
r_case
id|INTEL_I820
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Intel i820&quot;
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|INTEL_I840
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Intel i840&quot;
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x02040f /* KERNEL_VERSION(2,4,15) */
r_case
id|INTEL_I845
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Intel i845&quot;
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|INTEL_I850
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Intel i850&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTEL_460GX
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Intel 460GX&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_GENERIC
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;VIA&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_VP3
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;VIA VP3&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_MVP3
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;VIA MVP3&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_MVP4
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;VIA MVP4&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_APOLLO_KX133
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;VIA Apollo KX133&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_APOLLO_KT133
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;VIA Apollo KT133&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIA_APOLLO_PRO
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;VIA Apollo Pro&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIS_GENERIC
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;SiS&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AMD_GENERIC
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;AMD&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AMD_IRONGATE
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;AMD Irongate&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALI_GENERIC
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;ALi&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALI_M1541
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;ALi M1541&quot;
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020402
r_case
id|ALI_M1621
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;ALi M1621&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALI_M1631
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;ALi M1631&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALI_M1632
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;ALi M1632&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALI_M1641
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;ALi M1641&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALI_M1644
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;ALi M1644&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALI_M1647
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;ALi M1647&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALI_M1651
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;ALi M1651&quot;
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020406
r_case
id|SVWRKS_HE
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Serverworks HE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SVWRKS_LE
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Serverworks LE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SVWRKS_GENERIC
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Serverworks Generic&quot;
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|HP_ZX1
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;HP ZX1&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|head-&gt;chipset
op_assign
l_string|&quot;Unknown&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#if LINUX_VERSION_CODE &lt;= 0x020408
id|head-&gt;cant_use_aperture
op_assign
l_int|0
suffix:semicolon
id|head-&gt;page_mask
op_assign
op_complement
(paren
l_int|0xfff
)paren
suffix:semicolon
macro_line|#else
id|head-&gt;cant_use_aperture
op_assign
id|head-&gt;agp_info.cant_use_aperture
suffix:semicolon
id|head-&gt;page_mask
op_assign
id|head-&gt;agp_info.page_mask
suffix:semicolon
macro_line|#endif
id|DRM_INFO
c_func
(paren
l_string|&quot;AGP %d.%d on %s @ 0x%08lx %ZuMB&bslash;n&quot;
comma
id|head-&gt;agp_info.version.major
comma
id|head-&gt;agp_info.version.minor
comma
id|head-&gt;chipset
comma
id|head-&gt;agp_info.aper_base
comma
id|head-&gt;agp_info.aper_size
)paren
suffix:semicolon
)brace
r_return
id|head
suffix:semicolon
)brace
DECL|function|agp_uninit
r_void
id|DRM
c_func
(paren
id|agp_uninit
)paren
(paren
r_void
)paren
(brace
id|DRM_AGP_PUT
suffix:semicolon
id|drm_agp
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|agp_allocate_memory
id|agp_memory
op_star
id|DRM
c_func
(paren
id|agp_allocate_memory
)paren
(paren
r_int
id|pages
comma
id|u32
id|type
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|drm_agp-&gt;allocate_memory
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|drm_agp
op_member_access_from_pointer
id|allocate_memory
c_func
(paren
id|pages
comma
id|type
)paren
suffix:semicolon
)brace
DECL|function|agp_free_memory
r_int
id|DRM
c_func
(paren
id|agp_free_memory
)paren
(paren
id|agp_memory
op_star
id|handle
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|handle
op_logical_or
op_logical_neg
id|drm_agp-&gt;free_memory
)paren
r_return
l_int|0
suffix:semicolon
id|drm_agp
op_member_access_from_pointer
id|free_memory
c_func
(paren
id|handle
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|agp_bind_memory
r_int
id|DRM
c_func
(paren
id|agp_bind_memory
)paren
(paren
id|agp_memory
op_star
id|handle
comma
id|off_t
id|start
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|handle
op_logical_or
op_logical_neg
id|drm_agp-&gt;bind_memory
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|drm_agp
op_member_access_from_pointer
id|bind_memory
c_func
(paren
id|handle
comma
id|start
)paren
suffix:semicolon
)brace
DECL|function|agp_unbind_memory
r_int
id|DRM
c_func
(paren
id|agp_unbind_memory
)paren
(paren
id|agp_memory
op_star
id|handle
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|handle
op_logical_or
op_logical_neg
id|drm_agp-&gt;unbind_memory
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|drm_agp
op_member_access_from_pointer
id|unbind_memory
c_func
(paren
id|handle
)paren
suffix:semicolon
)brace
macro_line|#endif /* __REALLY_HAVE_AGP */
eof
