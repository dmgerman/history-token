multiline_comment|/* drm_fops.h -- File operations for DRM -*- linux-c -*-&n; * Created: Mon Jan  4 08:58:31 1999 by faith@valinux.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *    Daryll Strauss &lt;daryll@valinux.com&gt;&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &lt;linux/poll.h&gt;
multiline_comment|/* drm_open is called whenever a process opens /dev/drm. */
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
id|minor
c_func
(paren
id|inode-&gt;i_rdev
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
id|dev-&gt;device
comma
id|dev-&gt;open_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|dev-&gt;device
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
multiline_comment|/* The drm_read and drm_write_string code (especially that which manages&n;   the circular buffer), is based on Alessandro Rubini&squot;s LINUX DEVICE&n;   DRIVERS (Cambridge: O&squot;Reilly, 1998), pages 111-113. */
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
id|left
suffix:semicolon
r_int
id|avail
suffix:semicolon
r_int
id|send
suffix:semicolon
r_int
id|cur
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%p, %p&bslash;n&quot;
comma
id|dev-&gt;buf_rp
comma
id|dev-&gt;buf_wp
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;buf_rp
op_eq
id|dev-&gt;buf_wp
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;  sleeping&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|dev-&gt;buf_readers
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;  interrupted&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;  awake&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|left
op_assign
(paren
id|dev-&gt;buf_rp
op_plus
id|DRM_BSZ
op_minus
id|dev-&gt;buf_wp
)paren
op_mod
id|DRM_BSZ
suffix:semicolon
id|avail
op_assign
id|DRM_BSZ
op_minus
id|left
suffix:semicolon
id|send
op_assign
id|DRM_MIN
c_func
(paren
id|avail
comma
id|count
)paren
suffix:semicolon
r_while
c_loop
(paren
id|send
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;buf_wp
OG
id|dev-&gt;buf_rp
)paren
(brace
id|cur
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_wp
op_minus
id|dev-&gt;buf_rp
)paren
suffix:semicolon
)brace
r_else
(brace
id|cur
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_end
op_minus
id|dev-&gt;buf_rp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|dev-&gt;buf_rp
comma
id|cur
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dev-&gt;buf_rp
op_add_assign
id|cur
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buf_rp
op_eq
id|dev-&gt;buf_end
)paren
id|dev-&gt;buf_rp
op_assign
id|dev-&gt;buf
suffix:semicolon
id|send
op_sub_assign
id|cur
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;buf_writers
)paren
suffix:semicolon
r_return
id|DRM_MIN
c_func
(paren
id|avail
comma
id|count
)paren
suffix:semicolon
suffix:semicolon
)brace
DECL|function|write_string
r_int
id|DRM
c_func
(paren
id|write_string
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|left
op_assign
(paren
id|dev-&gt;buf_rp
op_plus
id|DRM_BSZ
op_minus
id|dev-&gt;buf_wp
)paren
op_mod
id|DRM_BSZ
suffix:semicolon
r_int
id|send
op_assign
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_int
id|count
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d left, %d to send (%p, %p)&bslash;n&quot;
comma
id|left
comma
id|send
comma
id|dev-&gt;buf_rp
comma
id|dev-&gt;buf_wp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|left
op_eq
l_int|1
op_logical_or
id|dev-&gt;buf_wp
op_ne
id|dev-&gt;buf_rp
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Buffer not empty (%d left, wp = %p, rp = %p)&bslash;n&quot;
comma
id|left
comma
id|dev-&gt;buf_wp
comma
id|dev-&gt;buf_rp
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|send
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;buf_wp
op_ge
id|dev-&gt;buf_rp
)paren
(brace
id|count
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_end
op_minus
id|dev-&gt;buf_wp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
id|left
)paren
op_decrement
id|count
suffix:semicolon
multiline_comment|/* Leave a hole */
)brace
r_else
(brace
id|count
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_rp
op_minus
id|dev-&gt;buf_wp
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|strncpy
c_func
(paren
id|dev-&gt;buf_wp
comma
id|s
comma
id|count
)paren
suffix:semicolon
id|dev-&gt;buf_wp
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buf_wp
op_eq
id|dev-&gt;buf_end
)paren
id|dev-&gt;buf_wp
op_assign
id|dev-&gt;buf
suffix:semicolon
id|send
op_sub_assign
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;buf_async
)paren
id|kill_fasync
c_func
(paren
op_amp
id|dev-&gt;buf_async
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;waking&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;buf_readers
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|poll_wait
c_func
(paren
id|filp
comma
op_amp
id|dev-&gt;buf_readers
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buf_wp
op_ne
id|dev-&gt;buf_rp
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
