multiline_comment|/*&n; * linux/drivers/char/misc.c&n; *&n; * Generic misc open routine by Johan Myreen&n; *&n; * Based on code from Linus&n; *&n; * Teemu Rantanen&squot;s Microsoft Busmouse support and Derrick Cole&squot;s&n; *   changes incorporated into 0.97pl4&n; *   by Peter Cervasio (pete%q106fm.uucp@wupost.wustl.edu) (08SEP92)&n; *   See busmouse.c for particulars.&n; *&n; * Made things a lot mode modular - easy to compile in just one or two&n; * of the misc drivers, as they are now completely independent. Linus.&n; *&n; * Support for loadable modules. 8-Sep-95 Philip Blundell &lt;pjb27@cam.ac.uk&gt;&n; *&n; * Fixed a failing symbol register to free the device registration&n; *&t;&t;Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt; 21-Jan-96&n; *&n; * Dynamic minors and /proc/mice by Alessandro Rubini. 26-Mar-96&n; *&n; * Renamed to misc and miscdevice to be more accurate. Alan Cox 26-Mar-96&n; *&n; * Handling of mouse minor numbers for kerneld:&n; *  Idea by Jacques Gelinas &lt;jack@solucorp.qc.ca&gt;,&n; *  adapted by Bjorn Ekwall &lt;bj0rn@blox.se&gt;&n; *  corrected by Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;&n; *&n; * Changes for kmod (from kerneld):&n; *&t;Cyrus Durgin &lt;cider@speakeasy.org&gt;&n; *&n; * Added devfs support. Richard Gooch &lt;rgooch@atnf.csiro.au&gt;  10-Jan-1998&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
multiline_comment|/*&n; * Head entry for the doubly linked miscdevice list&n; */
DECL|variable|misc_list
r_static
r_struct
id|miscdevice
id|misc_list
op_assign
(brace
l_int|0
comma
l_string|&quot;head&quot;
comma
l_int|NULL
comma
op_amp
id|misc_list
comma
op_amp
id|misc_list
)brace
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|misc_sem
)paren
suffix:semicolon
multiline_comment|/*&n; * Assigned numbers, used for dynamic minors&n; */
DECL|macro|DYNAMIC_MINORS
mdefine_line|#define DYNAMIC_MINORS 64 /* like dynamic majors */
DECL|variable|misc_minors
r_static
r_int
r_char
id|misc_minors
(braket
id|DYNAMIC_MINORS
op_div
l_int|8
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SGI_NEWPORT_GFX
r_extern
r_void
id|gfx_register
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|streamable_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rtc_DP8570A_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rtc_MK48T08_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ds1286_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pmu_device_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|tosh_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|i8k_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|misc_read_proc
r_static
r_int
id|misc_read_proc
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
comma
r_int
op_star
id|eof
comma
r_void
op_star
r_private
)paren
(brace
r_struct
id|miscdevice
op_star
id|p
suffix:semicolon
r_int
id|written
suffix:semicolon
id|written
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|misc_list.next
suffix:semicolon
id|p
op_ne
op_amp
id|misc_list
op_logical_and
id|written
OL
id|len
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
id|written
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|written
comma
l_string|&quot;%3i %s&bslash;n&quot;
comma
id|p-&gt;minor
comma
id|p-&gt;name
ques
c_cond
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|written
OL
id|offset
)paren
(brace
id|offset
op_sub_assign
id|written
suffix:semicolon
id|written
op_assign
l_int|0
suffix:semicolon
)brace
)brace
op_star
id|start
op_assign
id|buf
op_plus
id|offset
suffix:semicolon
id|written
op_sub_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|written
OG
id|len
)paren
(brace
op_star
id|eof
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
(paren
id|written
OL
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
id|written
suffix:semicolon
)brace
DECL|function|misc_open
r_static
r_int
id|misc_open
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
id|file
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
r_struct
id|miscdevice
op_star
id|c
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
comma
op_star
id|new_fops
op_assign
l_int|NULL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|misc_sem
)paren
suffix:semicolon
id|c
op_assign
id|misc_list.next
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_ne
op_amp
id|misc_list
)paren
op_logical_and
(paren
id|c-&gt;minor
op_ne
id|minor
)paren
)paren
id|c
op_assign
id|c-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
op_amp
id|misc_list
)paren
id|new_fops
op_assign
id|fops_get
c_func
(paren
id|c-&gt;fops
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_fops
)paren
(brace
r_char
id|modname
(braket
l_int|20
)braket
suffix:semicolon
id|up
c_func
(paren
op_amp
id|misc_sem
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|modname
comma
l_string|&quot;char-major-%d-%d&quot;
comma
id|MISC_MAJOR
comma
id|minor
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|modname
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|misc_sem
)paren
suffix:semicolon
id|c
op_assign
id|misc_list.next
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_ne
op_amp
id|misc_list
)paren
op_logical_and
(paren
id|c-&gt;minor
op_ne
id|minor
)paren
)paren
id|c
op_assign
id|c-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
op_amp
id|misc_list
op_logical_or
(paren
id|new_fops
op_assign
id|fops_get
c_func
(paren
id|c-&gt;fops
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|fail
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
id|old_fops
op_assign
id|file-&gt;f_op
suffix:semicolon
id|file-&gt;f_op
op_assign
id|new_fops
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op-&gt;open
)paren
(brace
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|fops_put
c_func
(paren
id|file-&gt;f_op
)paren
suffix:semicolon
id|file-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|old_fops
)paren
suffix:semicolon
)brace
)brace
id|fops_put
c_func
(paren
id|old_fops
)paren
suffix:semicolon
id|fail
suffix:colon
id|up
c_func
(paren
op_amp
id|misc_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|misc_fops
r_static
r_struct
id|file_operations
id|misc_fops
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
id|misc_open
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;misc_register&t;-&t;register a miscellaneous device&n; *&t;@misc: device structure&n; *&t;&n; *&t;Register a miscellaneous device with the kernel. If the minor&n; *&t;number is set to %MISC_DYNAMIC_MINOR a minor number is assigned&n; *&t;and placed in the minor field of the structure. For other cases&n; *&t;the minor number requested is used.&n; *&n; *&t;The structure passed is linked into the kernel and may not be&n; *&t;destroyed until it has been unregistered.&n; *&n; *&t;A zero is returned on success and a negative errno code for&n; *&t;failure.&n; */
DECL|function|misc_register
r_int
id|misc_register
c_func
(paren
r_struct
id|miscdevice
op_star
id|misc
)paren
(brace
r_struct
id|miscdevice
op_star
id|c
suffix:semicolon
r_if
c_cond
(paren
id|misc-&gt;next
op_logical_or
id|misc-&gt;prev
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|down
c_func
(paren
op_amp
id|misc_sem
)paren
suffix:semicolon
id|c
op_assign
id|misc_list.next
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_ne
op_amp
id|misc_list
)paren
op_logical_and
(paren
id|c-&gt;minor
op_ne
id|misc-&gt;minor
)paren
)paren
id|c
op_assign
id|c-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
op_amp
id|misc_list
)paren
(brace
id|up
c_func
(paren
op_amp
id|misc_sem
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|misc-&gt;minor
op_eq
id|MISC_DYNAMIC_MINOR
)paren
(brace
r_int
id|i
op_assign
id|DYNAMIC_MINORS
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
r_if
c_cond
(paren
(paren
id|misc_minors
(braket
id|i
op_rshift
l_int|3
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|i
op_amp
l_int|7
)paren
)paren
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
id|up
c_func
(paren
op_amp
id|misc_sem
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|misc-&gt;minor
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|misc-&gt;minor
OL
id|DYNAMIC_MINORS
)paren
id|misc_minors
(braket
id|misc-&gt;minor
op_rshift
l_int|3
)braket
op_or_assign
l_int|1
op_lshift
(paren
id|misc-&gt;minor
op_amp
l_int|7
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * please use it if you want to do fancy things with your&n;&t; * name...&n;&t; */
r_if
c_cond
(paren
id|misc-&gt;devfs_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
multiline_comment|/* yuck, yet another stupid special-casing.&n;&t;&t;   whos actually using this?  Please switch over&n;&t;&t;   to -&gt;devfs_name ASAP */
id|snprintf
c_func
(paren
id|misc-&gt;devfs_name
comma
r_sizeof
(paren
id|misc-&gt;devfs_name
)paren
comma
id|strchr
c_func
(paren
id|misc-&gt;name
comma
l_char|&squot;/&squot;
)paren
ques
c_cond
l_string|&quot;%s&quot;
suffix:colon
l_string|&quot;misc/%s&quot;
comma
id|misc-&gt;name
)paren
suffix:semicolon
)brace
id|devfs_register
c_func
(paren
l_int|NULL
comma
id|misc-&gt;devfs_name
comma
l_int|0
comma
id|MISC_MAJOR
comma
id|misc-&gt;minor
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
op_or
id|S_IRGRP
comma
id|misc-&gt;fops
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Add it to the front, so that later devices can &quot;override&quot;&n;&t; * earlier defaults&n;&t; */
id|misc-&gt;prev
op_assign
op_amp
id|misc_list
suffix:semicolon
id|misc-&gt;next
op_assign
id|misc_list.next
suffix:semicolon
id|misc-&gt;prev-&gt;next
op_assign
id|misc
suffix:semicolon
id|misc-&gt;next-&gt;prev
op_assign
id|misc
suffix:semicolon
id|up
c_func
(paren
op_amp
id|misc_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;misc_deregister - unregister a miscellaneous device&n; *&t;@misc: device to unregister&n; *&n; *&t;Unregister a miscellaneous device that was previously&n; *&t;successfully registered with misc_register(). Success&n; *&t;is indicated by a zero return, a negative errno code&n; *&t;indicates an error.&n; */
DECL|function|misc_deregister
r_int
id|misc_deregister
c_func
(paren
r_struct
id|miscdevice
op_star
id|misc
)paren
(brace
r_int
id|i
op_assign
id|misc-&gt;minor
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|misc-&gt;next
op_logical_or
op_logical_neg
id|misc-&gt;prev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|misc_sem
)paren
suffix:semicolon
id|misc-&gt;prev-&gt;next
op_assign
id|misc-&gt;next
suffix:semicolon
id|misc-&gt;next-&gt;prev
op_assign
id|misc-&gt;prev
suffix:semicolon
id|misc-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|misc-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|devfs_remove
c_func
(paren
id|misc-&gt;devfs_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
template_param
l_int|0
)paren
(brace
id|misc_minors
(braket
id|i
op_rshift
l_int|3
)braket
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|misc-&gt;minor
op_amp
l_int|7
)paren
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|misc_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|misc_register
id|EXPORT_SYMBOL
c_func
(paren
id|misc_register
)paren
suffix:semicolon
DECL|variable|misc_deregister
id|EXPORT_SYMBOL
c_func
(paren
id|misc_deregister
)paren
suffix:semicolon
DECL|function|misc_init
r_int
id|__init
id|misc_init
c_func
(paren
r_void
)paren
(brace
id|create_proc_read_entry
c_func
(paren
l_string|&quot;misc&quot;
comma
l_int|0
comma
l_int|0
comma
id|misc_read_proc
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MVME16x
id|rtc_MK48T08_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000
id|rtc_DP8570A_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_DS1286
id|ds1286_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PMAC_PBOOK
id|pmu_device_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_NEWPORT_GFX
id|gfx_register
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_IP22
id|streamable_init
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_NEWPORT_GFX
id|gfx_register
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_TOSHIBA
id|tosh_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_I8K
id|i8k_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|MISC_MAJOR
comma
l_string|&quot;misc&quot;
comma
op_amp
id|misc_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unable to get major %d for misc devices&bslash;n&quot;
comma
id|MISC_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
