multiline_comment|/* drm_stub.h -- -*- linux-c -*-&n; * Created: Fri Jan 19 10:48:35 2001 by faith@acm.org&n; *&n; * Copyright 2001 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;drmP.h&quot;
DECL|macro|DRM_STUB_MAXCARDS
mdefine_line|#define DRM_STUB_MAXCARDS 16&t;/* Enough for one machine */
DECL|struct|drm_stub_list
r_static
r_struct
id|drm_stub_list
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|fops
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
DECL|member|dev_root
r_struct
id|proc_dir_entry
op_star
id|dev_root
suffix:semicolon
)brace
op_star
id|DRM
c_func
(paren
id|stub_list
)paren
suffix:semicolon
r_static
r_struct
id|proc_dir_entry
op_star
id|DRM
c_func
(paren
id|stub_root
)paren
suffix:semicolon
DECL|struct|drm_stub_info
r_static
r_struct
id|drm_stub_info
(brace
DECL|member|info_register
r_int
(paren
op_star
id|info_register
)paren
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|file_operations
op_star
id|fops
comma
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
DECL|member|info_unregister
r_int
(paren
op_star
id|info_unregister
)paren
(paren
r_int
id|minor
)paren
suffix:semicolon
)brace
id|DRM
c_func
(paren
id|stub_info
)paren
suffix:semicolon
DECL|function|stub_open
r_static
r_int
id|DRM
c_func
(paren
id|stub_open
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
)paren
(brace
r_int
id|minor
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_struct
id|file_operations
op_star
id|old_fops
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DRM
c_func
(paren
id|stub_list
)paren
op_logical_or
op_logical_neg
id|DRM
c_func
(paren
id|stub_list
)paren
(braket
id|minor
)braket
dot
id|fops
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|old_fops
op_assign
id|filp-&gt;f_op
suffix:semicolon
id|filp-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|DRM
c_func
(paren
id|stub_list
)paren
(braket
id|minor
)braket
dot
id|fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_op-&gt;open
op_logical_and
(paren
id|err
op_assign
id|filp-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|filp
)paren
)paren
)paren
(brace
id|fops_put
c_func
(paren
id|filp-&gt;f_op
)paren
suffix:semicolon
id|filp-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|old_fops
)paren
suffix:semicolon
)brace
id|fops_put
c_func
(paren
id|old_fops
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|stub_fops
r_static
r_struct
id|file_operations
id|DRM
c_func
(paren
id|stub_fops
)paren
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|DRM
c_func
(paren
id|stub_open
)paren
)brace
suffix:semicolon
DECL|function|stub_getminor
r_static
r_int
id|DRM
c_func
(paren
id|stub_getminor
)paren
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|file_operations
op_star
id|fops
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DRM
c_func
(paren
id|stub_list
)paren
)paren
(brace
id|DRM
c_func
(paren
id|stub_list
)paren
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
id|DRM
c_func
(paren
id|stub_list
)paren
)paren
op_star
id|DRM_STUB_MAXCARDS
comma
id|DRM_MEM_STUB
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DRM
c_func
(paren
id|stub_list
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DRM_STUB_MAXCARDS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|DRM
c_func
(paren
id|stub_list
)paren
(braket
id|i
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|DRM
c_func
(paren
id|stub_list
)paren
(braket
id|i
)braket
dot
id|fops
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DRM_STUB_MAXCARDS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|DRM
c_func
(paren
id|stub_list
)paren
(braket
id|i
)braket
dot
id|fops
)paren
(brace
id|DRM
c_func
(paren
id|stub_list
)paren
(braket
id|i
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|DRM
c_func
(paren
id|stub_list
)paren
(braket
id|i
)braket
dot
id|fops
op_assign
id|fops
suffix:semicolon
id|DRM
c_func
(paren
id|stub_root
)paren
op_assign
id|DRM
c_func
(paren
id|proc_init
)paren
(paren
id|dev
comma
id|i
comma
id|DRM
c_func
(paren
id|stub_root
)paren
comma
op_amp
id|DRM
c_func
(paren
id|stub_list
)paren
(braket
id|i
)braket
dot
id|dev_root
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|stub_putminor
r_static
r_int
id|DRM
c_func
(paren
id|stub_putminor
)paren
(paren
r_int
id|minor
)paren
(brace
r_if
c_cond
(paren
id|minor
OL
l_int|0
op_logical_or
id|minor
op_ge
id|DRM_STUB_MAXCARDS
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|DRM
c_func
(paren
id|stub_list
)paren
(braket
id|minor
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|DRM
c_func
(paren
id|stub_list
)paren
(braket
id|minor
)braket
dot
id|fops
op_assign
l_int|NULL
suffix:semicolon
id|DRM
c_func
(paren
id|proc_cleanup
)paren
(paren
id|minor
comma
id|DRM
c_func
(paren
id|stub_root
)paren
comma
id|DRM
c_func
(paren
id|stub_list
)paren
(braket
id|minor
)braket
dot
id|dev_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
)paren
(brace
id|inter_module_put
c_func
(paren
l_string|&quot;drm&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|inter_module_unregister
c_func
(paren
l_string|&quot;drm&quot;
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|free
)paren
(paren
id|DRM
c_func
(paren
id|stub_list
)paren
comma
r_sizeof
(paren
op_star
id|DRM
c_func
(paren
id|stub_list
)paren
)paren
op_star
id|DRM_STUB_MAXCARDS
comma
id|DRM_MEM_STUB
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|DRM_MAJOR
comma
l_string|&quot;drm&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|stub_register
r_int
id|DRM
c_func
(paren
id|stub_register
)paren
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|file_operations
op_star
id|fops
comma
id|drm_device_t
op_star
id|dev
)paren
(brace
r_struct
id|drm_stub_info
op_star
id|i
op_assign
l_int|NULL
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|DRM_MAJOR
comma
l_string|&quot;drm&quot;
comma
op_amp
id|DRM
c_func
(paren
id|stub_fops
)paren
)paren
)paren
id|i
op_assign
(paren
r_struct
id|drm_stub_info
op_star
)paren
id|inter_module_get
c_func
(paren
l_string|&quot;drm&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
multiline_comment|/* Already registered */
id|DRM
c_func
(paren
id|stub_info
)paren
dot
id|info_register
op_assign
id|i-&gt;info_register
suffix:semicolon
id|DRM
c_func
(paren
id|stub_info
)paren
dot
id|info_unregister
op_assign
id|i-&gt;info_unregister
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;already registered&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|DRM
c_func
(paren
id|stub_info
)paren
dot
id|info_register
op_ne
id|DRM
c_func
(paren
id|stub_getminor
)paren
)paren
(brace
id|DRM
c_func
(paren
id|stub_info
)paren
dot
id|info_register
op_assign
id|DRM
c_func
(paren
id|stub_getminor
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|stub_info
)paren
dot
id|info_unregister
op_assign
id|DRM
c_func
(paren
id|stub_putminor
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;calling inter_module_register&bslash;n&quot;
)paren
suffix:semicolon
id|inter_module_register
c_func
(paren
l_string|&quot;drm&quot;
comma
id|THIS_MODULE
comma
op_amp
id|DRM
c_func
(paren
id|stub_info
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DRM
c_func
(paren
id|stub_info
)paren
dot
id|info_register
)paren
r_return
id|DRM
c_func
(paren
id|stub_info
)paren
dot
id|info_register
c_func
(paren
id|name
comma
id|fops
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|stub_unregister
r_int
id|DRM
c_func
(paren
id|stub_unregister
)paren
(paren
r_int
id|minor
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DRM
c_func
(paren
id|stub_info
)paren
dot
id|info_unregister
)paren
r_return
id|DRM
c_func
(paren
id|stub_info
)paren
dot
id|info_unregister
c_func
(paren
id|minor
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
eof
