multiline_comment|/**&n; * &bslash;file drm_agpsupport.h &n; * DRM support for AGP/GART backend&n; *    &n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/*&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#if __OS_HAS_AGP
multiline_comment|/**&n; * AGP information ioctl.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg pointer to a (output) drm_agp_info structure.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Verifies the AGP device has been initialized and acquired and fills in the&n; * drm_agp_info structure with the information in drm_agp_head::agp_info.&n; */
DECL|function|drm_agp_info
r_int
id|drm_agp_info
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
id|DRM_AGP_KERN
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
id|__user
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
multiline_comment|/**&n; * Acquire the AGP device (ioctl).&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument.&n; * &bslash;return zero on success or a negative number on failure. &n; *&n; * Verifies the AGP device hasn&squot;t been acquired before and calls&n; * agp_acquire().&n; */
DECL|function|drm_agp_acquire
r_int
id|drm_agp_acquire
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
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;agp
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;agp-&gt;acquired
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;agp-&gt;bridge
op_assign
id|agp_backend_acquire
c_func
(paren
id|dev-&gt;pdev
)paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dev-&gt;agp-&gt;acquired
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Release the AGP device (ioctl).&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Verifies the AGP device has been acquired and calls agp_backend_release().&n; */
DECL|function|drm_agp_release
r_int
id|drm_agp_release
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
id|agp_backend_release
c_func
(paren
id|dev-&gt;agp-&gt;bridge
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
multiline_comment|/**&n; * Release the AGP device.&n; *&n; * Calls agp_backend_release().&n; */
DECL|function|drm_agp_do_release
r_void
id|drm_agp_do_release
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|agp_backend_release
c_func
(paren
id|dev-&gt;agp-&gt;bridge
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * Enable the AGP bus.&n; * &n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg pointer to a drm_agp_mode structure.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Verifies the AGP device has been acquired but not enabled, and calls&n; * agp_enable().&n; */
DECL|function|drm_agp_enable
r_int
id|drm_agp_enable
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
id|__user
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
id|agp_enable
c_func
(paren
id|dev-&gt;agp-&gt;bridge
comma
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
multiline_comment|/**&n; * Allocate AGP memory.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg pointer to a drm_agp_buffer structure.&n; * &bslash;return zero on success or a negative number on failure.&n; * &n; * Verifies the AGP device is present and has been acquired, allocates the&n; * memory via alloc_agp() and creates a drm_agp_mem entry for it.&n; */
DECL|function|drm_agp_alloc
r_int
id|drm_agp_alloc
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
id|drm_agp_buffer_t
id|request
suffix:semicolon
id|drm_agp_mem_t
op_star
id|entry
suffix:semicolon
id|DRM_AGP_MEM
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
id|drm_agp_buffer_t
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
r_if
c_cond
(paren
op_logical_neg
(paren
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
id|drm_alloc_agp
c_func
(paren
id|dev-&gt;agp-&gt;bridge
comma
id|pages
comma
id|type
)paren
)paren
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
id|memory-&gt;key
op_plus
l_int|1
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
id|dev-&gt;agp-&gt;memory
op_assign
id|entry-&gt;next
suffix:semicolon
id|dev-&gt;agp-&gt;memory-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|drm_free_agp
c_func
(paren
id|memory
comma
id|pages
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
multiline_comment|/**&n; * Search for the AGP memory entry associated with a handle.&n; *&n; * &bslash;param dev DRM device structure.&n; * &bslash;param handle AGP memory handle.&n; * &bslash;return pointer to the drm_agp_mem structure associated with &bslash;p handle.&n; * &n; * Walks through drm_agp_head::memory until finding a matching handle.&n; */
DECL|function|drm_agp_lookup_entry
r_static
id|drm_agp_mem_t
op_star
id|drm_agp_lookup_entry
c_func
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
multiline_comment|/**&n; * Unbind AGP memory from the GATT (ioctl).&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg pointer to a drm_agp_binding structure.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Verifies the AGP device is present and acquired, looks-up the AGP memory&n; * entry and passes it to the unbind_agp() function.&n; */
DECL|function|drm_agp_unbind
r_int
id|drm_agp_unbind
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
id|drm_agp_binding_t
id|request
suffix:semicolon
id|drm_agp_mem_t
op_star
id|entry
suffix:semicolon
r_int
id|ret
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|entry
op_assign
id|drm_agp_lookup_entry
c_func
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
id|ret
op_assign
id|drm_unbind_agp
c_func
(paren
id|entry-&gt;memory
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|entry-&gt;bound
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * Bind AGP memory into the GATT (ioctl)&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg pointer to a drm_agp_binding structure.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Verifies the AGP device is present and has been acquired and that no memory&n; * is currently bound into the GATT. Looks-up the AGP memory entry and passes&n; * it to bind_agp() function.&n; */
DECL|function|drm_agp_bind
r_int
id|drm_agp_bind
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|entry
op_assign
id|drm_agp_lookup_entry
c_func
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
id|drm_bind_agp
c_func
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
multiline_comment|/**&n; * Free AGP memory (ioctl).&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg pointer to a drm_agp_buffer structure.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Verifies the AGP device is present and has been acquired and looks up the&n; * AGP memory entry. If the memory it&squot;s currently bound, unbind it via&n; * unbind_agp(). Frees it via free_agp() as well as the entry itself&n; * and unlinks from the doubly linked list it&squot;s inserted in.&n; */
DECL|function|drm_agp_free
r_int
id|drm_agp_free
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|entry
op_assign
id|drm_agp_lookup_entry
c_func
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
id|drm_unbind_agp
c_func
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
id|drm_free_agp
c_func
(paren
id|entry-&gt;memory
comma
id|entry-&gt;pages
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
id|DRM_MEM_AGPLISTS
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Initialize the AGP resources.&n; *&n; * &bslash;return pointer to a drm_agp_head structure.&n; *&n; */
DECL|function|drm_agp_init
id|drm_agp_head_t
op_star
id|drm_agp_init
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_agp_head_t
op_star
id|head
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|head
op_assign
id|drm_alloc
c_func
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
id|head-&gt;bridge
op_assign
id|agp_find_bridge
c_func
(paren
id|dev-&gt;pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head-&gt;bridge
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|head-&gt;bridge
op_assign
id|agp_backend_acquire
c_func
(paren
id|dev-&gt;pdev
)paren
)paren
)paren
(brace
id|drm_free
c_func
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
id|agp_copy_info
c_func
(paren
id|head-&gt;bridge
comma
op_amp
id|head-&gt;agp_info
)paren
suffix:semicolon
id|agp_backend_release
c_func
(paren
id|head-&gt;bridge
)paren
suffix:semicolon
)brace
r_else
(brace
id|agp_copy_info
c_func
(paren
id|head-&gt;bridge
comma
op_amp
id|head-&gt;agp_info
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|head-&gt;agp_info.chipset
op_eq
id|NOT_SUPPORTED
)paren
(brace
id|drm_free
c_func
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
r_return
id|head
suffix:semicolon
)brace
multiline_comment|/** Calls agp_allocate_memory() */
DECL|function|drm_agp_allocate_memory
id|DRM_AGP_MEM
op_star
id|drm_agp_allocate_memory
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
comma
r_int
id|pages
comma
id|u32
id|type
)paren
(brace
r_return
id|agp_allocate_memory
c_func
(paren
id|bridge
comma
id|pages
comma
id|type
)paren
suffix:semicolon
)brace
multiline_comment|/** Calls agp_free_memory() */
DECL|function|drm_agp_free_memory
r_int
id|drm_agp_free_memory
c_func
(paren
id|DRM_AGP_MEM
op_star
id|handle
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
r_return
l_int|0
suffix:semicolon
id|agp_free_memory
c_func
(paren
id|handle
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/** Calls agp_bind_memory() */
DECL|function|drm_agp_bind_memory
r_int
id|drm_agp_bind_memory
c_func
(paren
id|DRM_AGP_MEM
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
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|agp_bind_memory
c_func
(paren
id|handle
comma
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/** Calls agp_unbind_memory() */
DECL|function|drm_agp_unbind_memory
r_int
id|drm_agp_unbind_memory
c_func
(paren
id|DRM_AGP_MEM
op_star
id|handle
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|agp_unbind_memory
c_func
(paren
id|handle
)paren
suffix:semicolon
)brace
macro_line|#endif /* __OS_HAS_AGP */
eof
