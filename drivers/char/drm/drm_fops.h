multiline_comment|/**&n; * &bslash;file drm_fops.h &n; * File operations for DRM&n; * &n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &bslash;author Daryll Strauss &lt;daryll@valinux.com&gt;&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/*&n; * Created: Mon Jan  4 08:58:31 1999 by faith@valinux.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &lt;linux/poll.h&gt;
multiline_comment|/**&n; * Called whenever a process opens /dev/drm. &n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param dev device.&n; * &bslash;return zero on success or a negative number on failure.&n; * &n; * Creates and initializes a drm_file structure for the file private data in &bslash;p&n; * filp and add it into the double linked list in &bslash;p dev.&n; */
DECL|function|open_helper
r_int
id|DRM
c_func
(paren
id|open_helper
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
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
id|drm_file_t
op_star
id|priv
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_EXCL
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* No exclusive opens */
r_if
c_cond
(paren
op_logical_neg
id|DRM
c_func
(paren
id|cpu_valid
)paren
(paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;pid = %d, minor = %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|minor
)paren
suffix:semicolon
id|priv
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
id|priv
)paren
comma
id|DRM_MEM_FILES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|priv
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|priv
)paren
)paren
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|priv
suffix:semicolon
id|priv-&gt;uid
op_assign
id|current-&gt;euid
suffix:semicolon
id|priv-&gt;pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|priv-&gt;minor
op_assign
id|minor
suffix:semicolon
id|priv-&gt;dev
op_assign
id|dev
suffix:semicolon
id|priv-&gt;ioctl_count
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;authenticated
op_assign
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
suffix:semicolon
id|priv-&gt;lock_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;fn_tbl.open_helper
)paren
id|dev-&gt;fn_tbl
dot
id|open_helper
c_func
(paren
id|dev
comma
id|priv
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;file_last
)paren
(brace
id|priv-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|priv-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;file_first
op_assign
id|priv
suffix:semicolon
id|dev-&gt;file_last
op_assign
id|priv
suffix:semicolon
)brace
r_else
(brace
id|priv-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|priv-&gt;prev
op_assign
id|dev-&gt;file_last
suffix:semicolon
id|dev-&gt;file_last-&gt;next
op_assign
id|priv
suffix:semicolon
id|dev-&gt;file_last
op_assign
id|priv
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
macro_line|#ifdef __alpha__
multiline_comment|/*&n;&t; * Default the hose&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;hose
)paren
(brace
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
id|pci_dev
op_assign
id|pci_find_class
c_func
(paren
id|PCI_CLASS_DISPLAY_VGA
op_lshift
l_int|8
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_dev
)paren
id|dev-&gt;hose
op_assign
id|pci_dev-&gt;sysdata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;hose
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
op_assign
id|pci_bus_b
c_func
(paren
id|pci_root_buses.next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
)paren
id|dev-&gt;hose
op_assign
id|b-&gt;sysdata
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/** No-op. */
DECL|function|flush
r_int
id|DRM
c_func
(paren
id|flush
)paren
(paren
r_struct
id|file
op_star
id|filp
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
id|DRM_DEBUG
c_func
(paren
l_string|&quot;pid = %d, device = 0x%lx, open_count = %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
(paren
r_int
)paren
id|old_encode_dev
c_func
(paren
id|dev-&gt;device
)paren
comma
id|dev-&gt;open_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/** No-op. */
DECL|function|fasync
r_int
id|DRM
c_func
(paren
id|fasync
)paren
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
id|on
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
id|DRM_DEBUG
c_func
(paren
l_string|&quot;fd = %d, device = 0x%lx&bslash;n&quot;
comma
id|fd
comma
(paren
r_int
)paren
id|old_encode_dev
c_func
(paren
id|dev-&gt;device
)paren
)paren
suffix:semicolon
id|retcode
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|filp
comma
id|on
comma
op_amp
id|dev-&gt;buf_async
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retcode
OL
l_int|0
)paren
r_return
id|retcode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/** No-op. */
DECL|function|poll
r_int
r_int
id|DRM
c_func
(paren
id|poll
)paren
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|poll_table_struct
op_star
id|wait
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/** No-op. */
DECL|function|read
id|ssize_t
id|DRM
c_func
(paren
id|read
)paren
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
