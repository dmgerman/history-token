multiline_comment|/*&n; * $Id: mtdcore.c,v 1.44 2004/11/16 18:28:59 dwmw2 Exp $&n; *&n; * Core registration and callback routines for MTD&n; * drivers and users.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mtd/compatmac.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/mtd/mtd.h&gt;
multiline_comment|/* These are exported solely for the purpose of mtd_blkdevs.c. You &n;   should not use them for _anything_ else */
DECL|variable|mtd_table_mutex
id|DECLARE_MUTEX
c_func
(paren
id|mtd_table_mutex
)paren
suffix:semicolon
DECL|variable|mtd_table
r_struct
id|mtd_info
op_star
id|mtd_table
(braket
id|MAX_MTD_DEVICES
)braket
suffix:semicolon
DECL|variable|mtd_table_mutex
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|mtd_table_mutex
)paren
suffix:semicolon
DECL|variable|mtd_table
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|mtd_table
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|mtd_notifiers
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;add_mtd_device - register an MTD device&n; *&t;@mtd: pointer to new MTD device info structure&n; *&n; *&t;Add a device to the list of MTD devices present in the system, and&n; *&t;notify each currently active MTD &squot;user&squot; of its arrival. Returns&n; *&t;zero on success or 1 on failure, which currently will only happen&n; *&t;if the number of present devices exceeds MAX_MTD_DEVICES (i.e. 16)&n; */
DECL|function|add_mtd_device
r_int
id|add_mtd_device
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_int
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mtd_table_mutex
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
OL
id|MAX_MTD_DEVICES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|mtd_table
(braket
id|i
)braket
)paren
(brace
r_struct
id|list_head
op_star
id|this
suffix:semicolon
id|mtd_table
(braket
id|i
)braket
op_assign
id|mtd
suffix:semicolon
id|mtd-&gt;index
op_assign
id|i
suffix:semicolon
id|mtd-&gt;usecount
op_assign
l_int|0
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;mtd: Giving out device %d to %s&bslash;n&quot;
comma
id|i
comma
id|mtd-&gt;name
)paren
suffix:semicolon
multiline_comment|/* No need to get a refcount on the module containing&n;&t;&t;&t;   the notifier, since we hold the mtd_table_mutex */
id|list_for_each
c_func
(paren
id|this
comma
op_amp
id|mtd_notifiers
)paren
(brace
r_struct
id|mtd_notifier
op_star
op_logical_neg
op_assign
id|list_entry
c_func
(paren
id|this
comma
r_struct
id|mtd_notifier
comma
id|list
)paren
suffix:semicolon
op_logical_neg
op_member_access_from_pointer
id|add
c_func
(paren
id|mtd
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
multiline_comment|/* We _know_ we aren&squot;t being removed, because&n;&t;&t;&t;   our caller is still holding us here. So none&n;&t;&t;&t;   of this try_ nonsense, and no bitching about it&n;&t;&t;&t;   either. :) */
id|__module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;del_mtd_device - unregister an MTD device&n; *&t;@mtd: pointer to MTD device info structure&n; *&n; *&t;Remove a device from the list of MTD devices present in the system,&n; *&t;and notify each currently active MTD &squot;user&squot; of its departure.&n; *&t;Returns zero on success or 1 on failure, which currently will happen&n; *&t;if the requested device does not appear to be present in the list.&n; */
DECL|function|del_mtd_device
r_int
id|del_mtd_device
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_int
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtd_table
(braket
id|mtd-&gt;index
)braket
op_ne
id|mtd
)paren
(brace
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mtd-&gt;usecount
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Removing MTD device #%d (%s) with use count %d&bslash;n&quot;
comma
id|mtd-&gt;index
comma
id|mtd-&gt;name
comma
id|mtd-&gt;usecount
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
(brace
r_struct
id|list_head
op_star
id|this
suffix:semicolon
multiline_comment|/* No need to get a refcount on the module containing&n;&t;&t;   the notifier, since we hold the mtd_table_mutex */
id|list_for_each
c_func
(paren
id|this
comma
op_amp
id|mtd_notifiers
)paren
(brace
r_struct
id|mtd_notifier
op_star
op_logical_neg
op_assign
id|list_entry
c_func
(paren
id|this
comma
r_struct
id|mtd_notifier
comma
id|list
)paren
suffix:semicolon
op_logical_neg
op_member_access_from_pointer
id|remove
c_func
(paren
id|mtd
)paren
suffix:semicolon
)brace
id|mtd_table
(braket
id|mtd-&gt;index
)braket
op_assign
l_int|NULL
suffix:semicolon
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;register_mtd_user - register a &squot;user&squot; of MTD devices.&n; *&t;@new: pointer to notifier info structure&n; *&n; *&t;Registers a pair of callbacks function to be called upon addition&n; *&t;or removal of MTD devices. Causes the &squot;add&squot; callback to be immediately&n; *&t;invoked for each MTD device currently present in the system.&n; */
DECL|function|register_mtd_user
r_void
id|register_mtd_user
(paren
r_struct
id|mtd_notifier
op_star
r_new
)paren
(brace
r_int
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|list
comma
op_amp
id|mtd_notifiers
)paren
suffix:semicolon
id|__module_get
c_func
(paren
id|THIS_MODULE
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
OL
id|MAX_MTD_DEVICES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|mtd_table
(braket
id|i
)braket
)paren
r_new
op_member_access_from_pointer
id|add
c_func
(paren
id|mtd_table
(braket
id|i
)braket
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;register_mtd_user - unregister a &squot;user&squot; of MTD devices.&n; *&t;@new: pointer to notifier info structure&n; *&n; *&t;Removes a callback function pair from the list of &squot;users&squot; to be&n; *&t;notified upon addition or removal of MTD devices. Causes the&n; *&t;&squot;remove&squot; callback to be immediately invoked for each MTD device&n; *&t;currently present in the system.&n; */
DECL|function|unregister_mtd_user
r_int
id|unregister_mtd_user
(paren
r_struct
id|mtd_notifier
op_star
id|old
)paren
(brace
r_int
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|THIS_MODULE
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
OL
id|MAX_MTD_DEVICES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|mtd_table
(braket
id|i
)braket
)paren
id|old
op_member_access_from_pointer
id|remove
c_func
(paren
id|mtd_table
(braket
id|i
)braket
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|old-&gt;list
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;get_mtd_device - obtain a validated handle for an MTD device&n; *&t;@mtd: last known address of the required MTD device&n; *&t;@num: internal device number of the required MTD device&n; *&n; *&t;Given a number and NULL address, return the num&squot;th entry in the device&n; *&t;table, if any.&t;Given an address and num == -1, search the device table&n; *&t;for a device with that address and return if it&squot;s still present. Given&n; *&t;both, return the num&squot;th driver only if its address matches. Return NULL&n; *&t;if not.&n; */
DECL|function|get_mtd_device
r_struct
id|mtd_info
op_star
id|get_mtd_device
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_int
id|num
)paren
(brace
r_struct
id|mtd_info
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num
op_eq
op_minus
l_int|1
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
id|MAX_MTD_DEVICES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|mtd_table
(braket
id|i
)braket
op_eq
id|mtd
)paren
id|ret
op_assign
id|mtd_table
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|num
OL
id|MAX_MTD_DEVICES
)paren
(brace
id|ret
op_assign
id|mtd_table
(braket
id|num
)braket
suffix:semicolon
r_if
c_cond
(paren
id|mtd
op_logical_and
id|mtd
op_ne
id|ret
)paren
id|ret
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_logical_and
op_logical_neg
id|try_module_get
c_func
(paren
id|ret-&gt;owner
)paren
)paren
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|ret-&gt;usecount
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|put_mtd_device
r_void
id|put_mtd_device
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_int
id|c
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
id|c
op_assign
op_decrement
id|mtd-&gt;usecount
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|c
OL
l_int|0
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|mtd-&gt;owner
)paren
suffix:semicolon
)brace
multiline_comment|/* default_mtd_writev - default mtd writev method for MTD devices that&n; *&t;&t;&t;dont implement their own&n; */
DECL|function|default_mtd_writev
r_int
id|default_mtd_writev
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|to
comma
r_int
op_star
id|retlen
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
id|totlen
op_assign
l_int|0
comma
id|thislen
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd-&gt;write
)paren
(brace
id|ret
op_assign
op_minus
id|EROFS
suffix:semicolon
)brace
r_else
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|vecs
(braket
id|i
)braket
dot
id|iov_len
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|mtd
op_member_access_from_pointer
id|write
c_func
(paren
id|mtd
comma
id|to
comma
id|vecs
(braket
id|i
)braket
dot
id|iov_len
comma
op_amp
id|thislen
comma
id|vecs
(braket
id|i
)braket
dot
id|iov_base
)paren
suffix:semicolon
id|totlen
op_add_assign
id|thislen
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_or
id|thislen
op_ne
id|vecs
(braket
id|i
)braket
dot
id|iov_len
)paren
r_break
suffix:semicolon
id|to
op_add_assign
id|vecs
(braket
id|i
)braket
dot
id|iov_len
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|retlen
)paren
op_star
id|retlen
op_assign
id|totlen
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* default_mtd_readv - default mtd readv method for MTD devices that dont&n; *&t;&t;       implement their own&n; */
DECL|function|default_mtd_readv
r_int
id|default_mtd_readv
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|from
comma
r_int
op_star
id|retlen
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
id|totlen
op_assign
l_int|0
comma
id|thislen
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd-&gt;read
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_else
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|vecs
(braket
id|i
)braket
dot
id|iov_len
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|mtd
op_member_access_from_pointer
id|read
c_func
(paren
id|mtd
comma
id|from
comma
id|vecs
(braket
id|i
)braket
dot
id|iov_len
comma
op_amp
id|thislen
comma
id|vecs
(braket
id|i
)braket
dot
id|iov_base
)paren
suffix:semicolon
id|totlen
op_add_assign
id|thislen
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_or
id|thislen
op_ne
id|vecs
(braket
id|i
)braket
dot
id|iov_len
)paren
r_break
suffix:semicolon
id|from
op_add_assign
id|vecs
(braket
id|i
)braket
dot
id|iov_len
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|retlen
)paren
op_star
id|retlen
op_assign
id|totlen
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|add_mtd_device
id|EXPORT_SYMBOL
c_func
(paren
id|add_mtd_device
)paren
suffix:semicolon
DECL|variable|del_mtd_device
id|EXPORT_SYMBOL
c_func
(paren
id|del_mtd_device
)paren
suffix:semicolon
DECL|variable|get_mtd_device
id|EXPORT_SYMBOL
c_func
(paren
id|get_mtd_device
)paren
suffix:semicolon
DECL|variable|put_mtd_device
id|EXPORT_SYMBOL
c_func
(paren
id|put_mtd_device
)paren
suffix:semicolon
DECL|variable|register_mtd_user
id|EXPORT_SYMBOL
c_func
(paren
id|register_mtd_user
)paren
suffix:semicolon
DECL|variable|unregister_mtd_user
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_mtd_user
)paren
suffix:semicolon
DECL|variable|default_mtd_writev
id|EXPORT_SYMBOL
c_func
(paren
id|default_mtd_writev
)paren
suffix:semicolon
DECL|variable|default_mtd_readv
id|EXPORT_SYMBOL
c_func
(paren
id|default_mtd_readv
)paren
suffix:semicolon
multiline_comment|/*====================================================================*/
multiline_comment|/* Power management code */
macro_line|#ifdef CONFIG_PM
macro_line|#include &lt;linux/pm.h&gt;
DECL|variable|mtd_pm_dev
r_static
r_struct
id|pm_dev
op_star
id|mtd_pm_dev
op_assign
l_int|NULL
suffix:semicolon
DECL|function|mtd_pm_callback
r_static
r_int
id|mtd_pm_callback
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
comma
id|pm_request_t
id|rqst
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|ret
op_assign
l_int|0
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|rqst
op_eq
id|PM_SUSPEND
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|ret
op_eq
l_int|0
op_logical_and
id|i
OL
id|MAX_MTD_DEVICES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mtd_table
(braket
id|i
)braket
op_logical_and
id|mtd_table
(braket
id|i
)braket
op_member_access_from_pointer
id|suspend
)paren
id|ret
op_assign
id|mtd_table
(braket
id|i
)braket
op_member_access_from_pointer
id|suspend
c_func
(paren
id|mtd_table
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_else
id|i
op_assign
id|MAX_MTD_DEVICES
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|rqst
op_eq
id|PM_RESUME
op_logical_or
id|ret
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|mtd_table
(braket
id|i
)braket
op_logical_and
id|mtd_table
(braket
id|i
)braket
op_member_access_from_pointer
id|resume
)paren
id|mtd_table
(braket
id|i
)braket
op_member_access_from_pointer
id|resume
c_func
(paren
id|mtd_table
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*====================================================================*/
multiline_comment|/* Support for /proc/mtd */
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|proc_mtd
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_mtd
suffix:semicolon
DECL|function|mtd_proc_info
r_static
r_inline
r_int
id|mtd_proc_info
(paren
r_char
op_star
id|buf
comma
r_int
id|i
)paren
(brace
r_struct
id|mtd_info
op_star
id|this
op_assign
id|mtd_table
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;mtd%d: %8.8x %8.8x &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|i
comma
id|this-&gt;size
comma
id|this-&gt;erasesize
comma
id|this-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|mtd_read_proc
r_static
r_int
id|mtd_read_proc
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data_unused
)paren
(brace
r_int
id|len
comma
id|l
comma
id|i
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;dev:    size   erasesize  name&bslash;n&quot;
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
OL
id|MAX_MTD_DEVICES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|l
op_assign
id|mtd_proc_info
c_func
(paren
id|page
op_plus
id|len
comma
id|i
)paren
suffix:semicolon
id|len
op_add_assign
id|l
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
id|begin
OG
id|off
op_plus
id|count
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
id|begin
OL
id|off
)paren
(brace
id|begin
op_add_assign
id|len
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
)brace
)brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
id|done
suffix:colon
id|up
c_func
(paren
op_amp
id|mtd_table_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ge
id|len
op_plus
id|begin
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
(paren
id|off
op_minus
id|begin
)paren
suffix:semicolon
r_return
(paren
(paren
id|count
OL
id|begin
op_plus
id|len
op_minus
id|off
)paren
ques
c_cond
id|count
suffix:colon
id|begin
op_plus
id|len
op_minus
id|off
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
multiline_comment|/*====================================================================*/
multiline_comment|/* Init code */
DECL|function|init_mtd
r_static
r_int
id|__init
id|init_mtd
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
r_if
c_cond
(paren
(paren
id|proc_mtd
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;mtd&quot;
comma
l_int|0
comma
l_int|NULL
)paren
)paren
)paren
id|proc_mtd-&gt;read_proc
op_assign
id|mtd_read_proc
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PM
id|mtd_pm_dev
op_assign
id|pm_register
c_func
(paren
id|PM_UNKNOWN_DEV
comma
l_int|0
comma
id|mtd_pm_callback
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_mtd
r_static
r_void
id|__exit
id|cleanup_mtd
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PM
r_if
c_cond
(paren
id|mtd_pm_dev
)paren
(brace
id|pm_unregister
c_func
(paren
id|mtd_pm_dev
)paren
suffix:semicolon
id|mtd_pm_dev
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
r_if
c_cond
(paren
id|proc_mtd
)paren
id|remove_proc_entry
c_func
(paren
l_string|&quot;mtd&quot;
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|init_mtd
id|module_init
c_func
(paren
id|init_mtd
)paren
suffix:semicolon
DECL|variable|cleanup_mtd
id|module_exit
c_func
(paren
id|cleanup_mtd
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Woodhouse &lt;dwmw2@infradead.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Core MTD registration and access routines&quot;
)paren
suffix:semicolon
eof
