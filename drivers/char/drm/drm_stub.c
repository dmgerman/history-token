multiline_comment|/**&n; * &bslash;file drm_stub.h&n; * Stub support&n; *&n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; */
multiline_comment|/*&n; * Created: Fri Jan 19 10:48:35 2001 by faith@acm.org&n; *&n; * Copyright 2001 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm_core.h&quot;
DECL|variable|drm_cards_limit
r_int
r_int
id|drm_cards_limit
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* Enough for one machine */
DECL|variable|drm_debug
r_int
r_int
id|drm_debug
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 1 to enable debug output */
DECL|variable|drm_debug
id|EXPORT_SYMBOL
c_func
(paren
id|drm_debug
)paren
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|drm_cards_limit
comma
l_string|&quot;Maximum number of graphics cards&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|drm_debug
comma
l_string|&quot;Enable debug output&quot;
)paren
suffix:semicolon
id|module_param_named
c_func
(paren
id|cards_limit
comma
id|drm_cards_limit
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|module_param_named
c_func
(paren
id|debug
comma
id|drm_debug
comma
r_int
comma
l_int|0666
)paren
suffix:semicolon
DECL|variable|drm_heads
id|drm_head_t
op_star
op_star
id|drm_heads
suffix:semicolon
DECL|variable|drm_class
r_struct
id|drm_sysfs_class
op_star
id|drm_class
suffix:semicolon
DECL|variable|drm_proc_root
r_struct
id|proc_dir_entry
op_star
id|drm_proc_root
suffix:semicolon
DECL|function|drm_fill_in_dev
r_static
r_int
id|drm_fill_in_dev
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
comma
r_struct
id|drm_driver
op_star
id|driver
)paren
(brace
r_int
id|retcode
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|dev-&gt;timer
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|dev-&gt;struct_sem
comma
l_int|1
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|dev-&gt;ctxlist_sem
comma
l_int|1
)paren
suffix:semicolon
id|dev-&gt;pdev
op_assign
id|pdev
suffix:semicolon
macro_line|#ifdef __alpha__
id|dev-&gt;hose
op_assign
id|pdev-&gt;sysdata
suffix:semicolon
id|dev-&gt;pci_domain
op_assign
id|dev-&gt;hose-&gt;bus-&gt;number
suffix:semicolon
macro_line|#else
id|dev-&gt;pci_domain
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|dev-&gt;pci_bus
op_assign
id|pdev-&gt;bus-&gt;number
suffix:semicolon
id|dev-&gt;pci_slot
op_assign
id|PCI_SLOT
c_func
(paren
id|pdev-&gt;devfn
)paren
suffix:semicolon
id|dev-&gt;pci_func
op_assign
id|PCI_FUNC
c_func
(paren
id|pdev-&gt;devfn
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
multiline_comment|/* the DRM has 6 basic counters */
id|dev-&gt;counters
op_assign
l_int|6
suffix:semicolon
id|dev-&gt;types
(braket
l_int|0
)braket
op_assign
id|_DRM_STAT_LOCK
suffix:semicolon
id|dev-&gt;types
(braket
l_int|1
)braket
op_assign
id|_DRM_STAT_OPENS
suffix:semicolon
id|dev-&gt;types
(braket
l_int|2
)braket
op_assign
id|_DRM_STAT_CLOSES
suffix:semicolon
id|dev-&gt;types
(braket
l_int|3
)braket
op_assign
id|_DRM_STAT_IOCTLS
suffix:semicolon
id|dev-&gt;types
(braket
l_int|4
)braket
op_assign
id|_DRM_STAT_LOCKS
suffix:semicolon
id|dev-&gt;types
(braket
l_int|5
)braket
op_assign
id|_DRM_STAT_UNLOCKS
suffix:semicolon
id|dev-&gt;driver
op_assign
id|driver
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver-&gt;preinit
)paren
r_if
c_cond
(paren
(paren
id|retcode
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|preinit
c_func
(paren
id|dev
comma
id|ent-&gt;driver_data
)paren
)paren
)paren
r_goto
id|error_out_unreg
suffix:semicolon
r_if
c_cond
(paren
id|drm_core_has_AGP
c_func
(paren
id|dev
)paren
)paren
(brace
id|dev-&gt;agp
op_assign
id|drm_agp_init
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drm_core_check_feature
c_func
(paren
id|dev
comma
id|DRIVER_REQUIRE_AGP
)paren
op_logical_and
(paren
id|dev-&gt;agp
op_eq
l_int|NULL
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Cannot initialize the agpgart module.&bslash;n&quot;
)paren
suffix:semicolon
id|retcode
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|error_out_unreg
suffix:semicolon
)brace
r_if
c_cond
(paren
id|drm_core_has_MTRR
c_func
(paren
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;agp
)paren
id|dev-&gt;agp-&gt;agp_mtrr
op_assign
id|mtrr_add
c_func
(paren
id|dev-&gt;agp-&gt;agp_info.aper_base
comma
id|dev-&gt;agp-&gt;agp_info.aper_size
op_star
l_int|1024
op_star
l_int|1024
comma
id|MTRR_TYPE_WRCOMB
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|retcode
op_assign
id|drm_ctxbitmap_init
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retcode
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Cannot allocate memory for context bitmap.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error_out_unreg
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|error_out_unreg
suffix:colon
id|drm_takedown
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
multiline_comment|/**&n; * File &bslash;c open operation.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; *&n; * Puts the dev-&gt;fops corresponding to the device minor number into&n; * &bslash;p filp, call the &bslash;c open method, and restore the file operations.&n; */
DECL|function|drm_stub_open
r_int
id|drm_stub_open
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
)paren
(brace
id|drm_device_t
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
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
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|minor
op_ge
l_int|0
)paren
op_logical_and
(paren
id|minor
OL
id|drm_cards_limit
)paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drm_heads
(braket
id|minor
)braket
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev
op_assign
id|drm_heads
(braket
id|minor
)braket
op_member_access_from_pointer
id|dev
)paren
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
op_amp
id|dev-&gt;driver-&gt;fops
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
multiline_comment|/**&n; * Register.&n; *&n; * &bslash;param pdev - PCI device structure&n; * &bslash;param ent entry from the PCI ID table with device type flags&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Attempt to gets inter module &quot;drm&quot; information. If we are first&n; * then register the character device and inter module information.&n; * Try and register, if we fail to register, backout previous work.&n; */
DECL|function|drm_get_dev
r_int
id|drm_get_dev
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
comma
r_struct
id|drm_driver
op_star
id|driver
)paren
(brace
id|drm_device_t
op_star
id|dev
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|dev
op_assign
id|drm_calloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|dev
)paren
comma
id|DRM_MEM_STUB
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pci_enable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|drm_fill_in_dev
c_func
(paren
id|dev
comma
id|pdev
comma
id|ent
comma
id|driver
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DRM: Fill_in_dev failed.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_g1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|drm_get_head
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;primary
)paren
)paren
)paren
r_goto
id|err_g1
suffix:semicolon
multiline_comment|/* postinit is a required function to display the signon banner */
multiline_comment|/* drivers add secondary heads here if needed */
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|dev-&gt;driver
op_member_access_from_pointer
id|postinit
c_func
(paren
id|dev
comma
id|ent-&gt;driver_data
)paren
)paren
)paren
r_goto
id|err_g1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_g1
suffix:colon
id|drm_free
c_func
(paren
id|dev
comma
r_sizeof
(paren
op_star
id|dev
)paren
comma
id|DRM_MEM_STUB
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|drm_get_dev
id|EXPORT_SYMBOL
c_func
(paren
id|drm_get_dev
)paren
suffix:semicolon
multiline_comment|/**&n; * Get a secondary minor number.&n; *&n; * &bslash;param dev device data structure&n; * &bslash;param sec-minor structure to hold the assigned minor&n; * &bslash;return negative number on failure.&n; *&n; * Search an empty entry and initialize it to the given parameters, and&n; * create the proc init entry via proc_init(). This routines assigns&n; * minor numbers to secondary heads of multi-headed cards&n; */
DECL|function|drm_get_head
r_int
id|drm_get_head
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|drm_head_t
op_star
id|head
)paren
(brace
id|drm_head_t
op_star
op_star
id|heads
op_assign
id|drm_heads
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|minor
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|minor
op_assign
l_int|0
suffix:semicolon
id|minor
OL
id|drm_cards_limit
suffix:semicolon
id|minor
op_increment
comma
id|heads
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|heads
)paren
(brace
op_star
id|head
op_assign
(paren
id|drm_head_t
)paren
(brace
dot
id|dev
op_assign
id|dev
comma
dot
id|device
op_assign
id|MKDEV
c_func
(paren
id|DRM_MAJOR
comma
id|minor
)paren
comma
dot
id|minor
op_assign
id|minor
comma
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|drm_proc_init
c_func
(paren
id|dev
comma
id|minor
comma
id|drm_proc_root
comma
op_amp
id|head-&gt;dev_root
)paren
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;DRM: Failed to initialize /proc/dri.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_g1
suffix:semicolon
)brace
id|head-&gt;dev_class
op_assign
id|drm_sysfs_device_add
c_func
(paren
id|drm_class
comma
id|MKDEV
c_func
(paren
id|DRM_MAJOR
comma
id|minor
)paren
comma
op_amp
id|dev-&gt;pdev-&gt;dev
comma
l_string|&quot;card%d&quot;
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|head-&gt;dev_class
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DRM: Error sysfs_device_add.&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|head-&gt;dev_class
)paren
suffix:semicolon
r_goto
id|err_g2
suffix:semicolon
)brace
op_star
id|heads
op_assign
id|head
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;new minor assigned %d&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;out of minors&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|err_g2
suffix:colon
id|drm_proc_cleanup
c_func
(paren
id|minor
comma
id|drm_proc_root
comma
id|head-&gt;dev_root
)paren
suffix:semicolon
id|err_g1
suffix:colon
op_star
id|head
op_assign
(paren
id|drm_head_t
)paren
(brace
dot
id|dev
op_assign
l_int|NULL
)brace
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * Put a device minor number.&n; *&n; * &bslash;param dev device data structure&n; * &bslash;return always zero&n; *&n; * Cleans up the proc resources. If it is the last minor then release the foreign&n; * &quot;drm&quot; data, otherwise unregisters the &quot;drm&quot; data, frees the dev list and&n; * unregisters the character device.&n; */
DECL|function|drm_put_dev
r_int
id|drm_put_dev
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;release primary %s&bslash;n&quot;
comma
id|dev-&gt;driver-&gt;pci_driver.name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;unique
)paren
(brace
id|drm_free
c_func
(paren
id|dev-&gt;unique
comma
id|strlen
c_func
(paren
id|dev-&gt;unique
)paren
op_plus
l_int|1
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|dev-&gt;unique
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;unique_len
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;devname
)paren
(brace
id|drm_free
c_func
(paren
id|dev-&gt;devname
comma
id|strlen
c_func
(paren
id|dev-&gt;devname
)paren
op_plus
l_int|1
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|dev-&gt;devname
op_assign
l_int|NULL
suffix:semicolon
)brace
id|drm_free
c_func
(paren
id|dev
comma
r_sizeof
(paren
op_star
id|dev
)paren
comma
id|DRM_MEM_STUB
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Put a secondary minor number.&n; *&n; * &bslash;param sec_minor - structure to be released&n; * &bslash;return always zero&n; *&n; * Cleans up the proc resources. Not legal for this to be the&n; * last minor released.&n; *&n; */
DECL|function|drm_put_head
r_int
id|drm_put_head
c_func
(paren
id|drm_head_t
op_star
id|head
)paren
(brace
r_int
id|minor
op_assign
id|head-&gt;minor
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;release secondary minor %d&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
id|drm_proc_cleanup
c_func
(paren
id|minor
comma
id|drm_proc_root
comma
id|head-&gt;dev_root
)paren
suffix:semicolon
id|drm_sysfs_device_remove
c_func
(paren
id|MKDEV
c_func
(paren
id|DRM_MAJOR
comma
id|head-&gt;minor
)paren
)paren
suffix:semicolon
op_star
id|head
op_assign
(paren
id|drm_head_t
)paren
(brace
dot
id|dev
op_assign
l_int|NULL
)brace
suffix:semicolon
id|drm_heads
(braket
id|minor
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
