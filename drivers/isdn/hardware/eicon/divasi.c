multiline_comment|/* $Id: divasi.c,v 1.1.2.7 2001/05/01 15:48:05 armin Exp $&n; *&n; * Driver for Eicon DIVA Server ISDN cards.&n; * User Mode IDI Interface &n; *&n; * Copyright 2000-2002 by Armin Schindler (mac@melware.de)&n; * Copyright 2000-2002 Cytronics &amp; Melware (info@melware.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &quot;platform.h&quot;
macro_line|#include &quot;di_defs.h&quot;
macro_line|#include &quot;divasync.h&quot;
macro_line|#include &quot;um_xdi.h&quot;
macro_line|#include &quot;um_idi.h&quot;
DECL|variable|main_revision
r_static
r_char
op_star
id|main_revision
op_assign
l_string|&quot;$Revision: 1.1.2.7 $&quot;
suffix:semicolon
DECL|variable|major
r_static
r_int
id|major
op_assign
l_int|242
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;User IDI Interface for Eicon ISDN cards&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Cytronics &amp; Melware, Eicon Networks&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;DIVA card driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|major
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|major
comma
l_string|&quot;Major number for /dev/DivasIDI&quot;
)paren
suffix:semicolon
DECL|struct|_diva_um_idi_os_context
r_typedef
r_struct
id|_diva_um_idi_os_context
(brace
DECL|member|read_wait
id|wait_queue_head_t
id|read_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
DECL|member|diva_timer_id
r_struct
id|timer_list
id|diva_timer_id
suffix:semicolon
DECL|member|aborted
r_int
id|aborted
suffix:semicolon
DECL|typedef|diva_um_idi_os_context_t
)brace
id|diva_um_idi_os_context_t
suffix:semicolon
DECL|variable|DRIVERNAME
r_static
r_char
op_star
id|DRIVERNAME
op_assign
l_string|&quot;Eicon DIVA - User IDI (http://www.melware.net)&quot;
suffix:semicolon
DECL|variable|DRIVERLNAME
r_static
r_char
op_star
id|DRIVERLNAME
op_assign
l_string|&quot;diva_idi&quot;
suffix:semicolon
DECL|variable|DRIVERRELEASE
r_char
op_star
id|DRIVERRELEASE
op_assign
l_string|&quot;2.0&quot;
suffix:semicolon
r_extern
r_int
id|idifunc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|idifunc_finit
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; *  helper functions&n; */
DECL|function|getrev
r_static
r_char
op_star
id|getrev
c_func
(paren
r_const
r_char
op_star
id|revision
)paren
(brace
r_char
op_star
id|rev
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|revision
comma
l_char|&squot;:&squot;
)paren
)paren
)paren
(brace
id|rev
op_assign
id|p
op_plus
l_int|2
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|rev
comma
l_char|&squot;$&squot;
)paren
suffix:semicolon
op_star
op_decrement
id|p
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|rev
op_assign
l_string|&quot;1.0&quot;
suffix:semicolon
r_return
id|rev
suffix:semicolon
)brace
multiline_comment|/*&n; *  LOCALS&n; */
r_static
id|ssize_t
id|um_idi_read
c_func
(paren
r_struct
id|file
op_star
id|file
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
id|offset
)paren
suffix:semicolon
r_static
id|ssize_t
id|um_idi_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
suffix:semicolon
r_static
r_int
r_int
id|um_idi_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
suffix:semicolon
r_static
r_int
id|um_idi_open
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
suffix:semicolon
r_static
r_int
id|um_idi_release
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
suffix:semicolon
r_static
r_int
id|remove_entity
c_func
(paren
r_void
op_star
id|entity
)paren
suffix:semicolon
r_static
r_void
id|diva_um_timer_function
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * malloc&n; */
DECL|function|diva_os_malloc
r_void
op_star
id|diva_os_malloc
c_func
(paren
r_int
r_int
id|flags
comma
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
id|ret
op_assign
(paren
r_void
op_star
)paren
id|vmalloc
c_func
(paren
(paren
r_int
r_int
)paren
id|size
)paren
suffix:semicolon
)brace
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * free&n; */
DECL|function|diva_os_free
r_void
id|diva_os_free
c_func
(paren
r_int
r_int
id|unused
comma
r_void
op_star
id|ptr
)paren
(brace
r_if
c_cond
(paren
id|ptr
)paren
(brace
id|vfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * proc entry&n; */
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_net_isdn_eicon
suffix:semicolon
DECL|variable|um_idi_proc_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|um_idi_proc_entry
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
DECL|function|um_idi_proc_read
id|um_idi_proc_read
c_func
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
id|data
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_char
id|tmprev
(braket
l_int|32
)braket
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|DRIVERNAME
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;name     : %s&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;release  : %s&bslash;n&quot;
comma
id|DRIVERRELEASE
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|tmprev
comma
id|main_revision
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;revision : %s&bslash;n&quot;
comma
id|getrev
c_func
(paren
id|tmprev
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;build    : %s&bslash;n&quot;
comma
id|DIVA_BUILD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|off
op_plus
id|count
op_ge
id|len
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|off
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
(paren
(paren
id|count
OL
id|len
op_minus
id|off
)paren
ques
c_cond
id|count
suffix:colon
id|len
op_minus
id|off
)paren
suffix:semicolon
)brace
DECL|function|create_um_idi_proc
r_static
r_int
id|DIVA_INIT_FUNCTION
id|create_um_idi_proc
c_func
(paren
r_void
)paren
(brace
id|um_idi_proc_entry
op_assign
id|create_proc_entry
c_func
(paren
id|DRIVERLNAME
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|proc_net_isdn_eicon
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|um_idi_proc_entry
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|um_idi_proc_entry-&gt;read_proc
op_assign
id|um_idi_proc_read
suffix:semicolon
id|um_idi_proc_entry-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|remove_um_idi_proc
r_static
r_void
id|remove_um_idi_proc
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|um_idi_proc_entry
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|DRIVERLNAME
comma
id|proc_net_isdn_eicon
)paren
suffix:semicolon
id|um_idi_proc_entry
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|variable|divas_idi_fops
r_static
r_struct
id|file_operations
id|divas_idi_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|um_idi_read
comma
dot
id|write
op_assign
id|um_idi_write
comma
dot
id|poll
op_assign
id|um_idi_poll
comma
dot
id|open
op_assign
id|um_idi_open
comma
dot
id|release
op_assign
id|um_idi_release
)brace
suffix:semicolon
DECL|function|divas_idi_unregister_chrdev
r_static
r_void
id|divas_idi_unregister_chrdev
c_func
(paren
r_void
)paren
(brace
id|devfs_remove
c_func
(paren
l_string|&quot;DivasIDI&quot;
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|major
comma
l_string|&quot;DivasIDI&quot;
)paren
suffix:semicolon
)brace
DECL|function|divas_idi_register_chrdev
r_static
r_int
id|DIVA_INIT_FUNCTION
id|divas_idi_register_chrdev
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|major
comma
l_string|&quot;DivasIDI&quot;
comma
op_amp
id|divas_idi_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to create /dev entry.&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|major
comma
l_int|0
)paren
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_string|&quot;DivasIDI&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;** Driver Load&n;*/
DECL|function|divasi_init
r_static
r_int
id|DIVA_INIT_FUNCTION
id|divasi_init
c_func
(paren
r_void
)paren
(brace
r_char
id|tmprev
(braket
l_int|50
)braket
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&bslash;n&quot;
comma
id|DRIVERNAME
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Rel:%s  Rev:&quot;
comma
id|DRIVERLNAME
comma
id|DRIVERRELEASE
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|tmprev
comma
id|main_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s  Build: %s Major: %d&bslash;n&quot;
comma
id|getrev
c_func
(paren
id|tmprev
)paren
comma
id|DIVA_BUILD
comma
id|major
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|divas_idi_register_chrdev
c_func
(paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create_um_idi_proc
c_func
(paren
)paren
)paren
(brace
id|divas_idi_unregister_chrdev
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to create proc entry.&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|idifunc_init
c_func
(paren
)paren
)paren
)paren
(brace
id|remove_um_idi_proc
c_func
(paren
)paren
suffix:semicolon
id|divas_idi_unregister_chrdev
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to connect to DIDD.&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;** Driver Unload&n;*/
DECL|function|divasi_exit
r_static
r_void
id|DIVA_EXIT_FUNCTION
id|divasi_exit
c_func
(paren
r_void
)paren
(brace
id|idifunc_finit
c_func
(paren
)paren
suffix:semicolon
id|remove_um_idi_proc
c_func
(paren
)paren
suffix:semicolon
id|divas_idi_unregister_chrdev
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: module unloaded.&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
)brace
DECL|variable|divasi_init
id|module_init
c_func
(paren
id|divasi_init
)paren
suffix:semicolon
DECL|variable|divasi_exit
id|module_exit
c_func
(paren
id|divasi_exit
)paren
suffix:semicolon
multiline_comment|/*&n; *  FILE OPERATIONS&n; */
r_static
r_int
DECL|function|divas_um_idi_copy_to_user
id|divas_um_idi_copy_to_user
c_func
(paren
r_void
op_star
id|os_handle
comma
r_void
op_star
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|length
)paren
(brace
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|length
)paren
suffix:semicolon
r_return
(paren
id|length
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|um_idi_read
id|um_idi_read
c_func
(paren
r_struct
id|file
op_star
id|file
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
id|offset
)paren
(brace
id|diva_um_idi_os_context_t
op_star
id|p_os
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;private_data
)paren
(brace
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p_os
op_assign
(paren
id|diva_um_idi_os_context_t
op_star
)paren
id|diva_um_id_get_os_context
c_func
(paren
id|file
op_member_access_from_pointer
id|private_data
)paren
)paren
)paren
(brace
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p_os-&gt;aborted
)paren
(brace
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
op_assign
id|diva_os_malloc
c_func
(paren
l_int|0
comma
id|count
)paren
)paren
)paren
(brace
r_return
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|diva_um_idi_read
c_func
(paren
id|file-&gt;private_data
comma
id|file
comma
id|data
comma
id|count
comma
id|divas_um_idi_copy_to_user
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ret
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* no message available */
id|ret
op_assign
(paren
op_minus
id|EAGAIN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
op_minus
l_int|1
)paren
suffix:colon
multiline_comment|/* adapter was removed */
id|ret
op_assign
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
op_minus
l_int|2
)paren
suffix:colon
multiline_comment|/* message_length &gt; length of user buffer */
id|ret
op_assign
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|data
comma
id|ret
)paren
)paren
(brace
id|ret
op_assign
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
)brace
)brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|data
)paren
suffix:semicolon
id|DBG_TRC
c_func
(paren
(paren
l_string|&quot;read: ret %d&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|divas_um_idi_copy_from_user
id|divas_um_idi_copy_from_user
c_func
(paren
r_void
op_star
id|os_handle
comma
r_void
op_star
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|length
)paren
(brace
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|length
)paren
suffix:semicolon
r_return
(paren
id|length
)paren
suffix:semicolon
)brace
DECL|function|um_idi_open_adapter
r_static
r_int
id|um_idi_open_adapter
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
id|adapter_nr
)paren
(brace
id|diva_um_idi_os_context_t
op_star
id|p_os
suffix:semicolon
r_void
op_star
id|e
op_assign
id|divas_um_idi_create_entity
c_func
(paren
(paren
id|dword
)paren
id|adapter_nr
comma
(paren
r_void
op_star
)paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|file-&gt;private_data
op_assign
id|e
)paren
)paren
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|p_os
op_assign
(paren
id|diva_um_idi_os_context_t
op_star
)paren
id|diva_um_id_get_os_context
c_func
(paren
id|e
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|p_os-&gt;read_wait
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|p_os-&gt;close_wait
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|p_os-&gt;diva_timer_id
)paren
suffix:semicolon
id|p_os-&gt;diva_timer_id.function
op_assign
(paren
r_void
op_star
)paren
id|diva_um_timer_function
suffix:semicolon
id|p_os-&gt;diva_timer_id.data
op_assign
(paren
r_int
r_int
)paren
id|p_os
suffix:semicolon
id|p_os-&gt;aborted
op_assign
l_int|0
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|um_idi_write
id|um_idi_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
(brace
id|diva_um_idi_os_context_t
op_star
id|p_os
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_int
id|adapter_nr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;private_data
)paren
(brace
multiline_comment|/* the first write() selects the adapter_nr */
r_if
c_cond
(paren
id|count
op_eq
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
(paren
(paren
r_void
op_star
)paren
op_amp
id|adapter_nr
comma
id|buf
comma
id|count
)paren
)paren
r_return
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|um_idi_open_adapter
c_func
(paren
id|file
comma
id|adapter_nr
)paren
)paren
)paren
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_return
(paren
id|count
)paren
suffix:semicolon
)brace
r_else
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p_os
op_assign
(paren
id|diva_um_idi_os_context_t
op_star
)paren
id|diva_um_id_get_os_context
c_func
(paren
id|file
op_member_access_from_pointer
id|private_data
)paren
)paren
)paren
(brace
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p_os-&gt;aborted
)paren
(brace
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
op_assign
id|diva_os_malloc
c_func
(paren
l_int|0
comma
id|count
)paren
)paren
)paren
(brace
r_return
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|data
comma
id|buf
comma
id|count
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|diva_um_idi_write
c_func
(paren
id|file-&gt;private_data
comma
id|file
comma
id|data
comma
id|count
comma
id|divas_um_idi_copy_from_user
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ret
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* no space available */
id|ret
op_assign
(paren
op_minus
id|EAGAIN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
op_minus
l_int|1
)paren
suffix:colon
multiline_comment|/* adapter was removed */
id|ret
op_assign
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
op_minus
l_int|2
)paren
suffix:colon
multiline_comment|/* length of user buffer &gt; max message_length */
id|ret
op_assign
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|data
)paren
suffix:semicolon
id|DBG_TRC
c_func
(paren
(paren
l_string|&quot;write: ret %d&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
DECL|function|um_idi_poll
r_static
r_int
r_int
id|um_idi_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
id|diva_um_idi_os_context_t
op_star
id|p_os
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;private_data
)paren
(brace
r_return
(paren
id|POLLERR
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|p_os
op_assign
(paren
id|diva_um_idi_os_context_t
op_star
)paren
id|diva_um_id_get_os_context
c_func
(paren
id|file-&gt;private_data
)paren
)paren
)paren
op_logical_or
id|p_os-&gt;aborted
)paren
(brace
r_return
(paren
id|POLLERR
)paren
suffix:semicolon
)brace
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|p_os-&gt;read_wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p_os-&gt;aborted
)paren
(brace
r_return
(paren
id|POLLERR
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|diva_user_mode_idi_ind_ready
c_func
(paren
id|file-&gt;private_data
comma
id|file
)paren
)paren
(brace
r_case
(paren
op_minus
l_int|1
)paren
suffix:colon
r_return
(paren
id|POLLERR
)paren
suffix:semicolon
r_case
l_int|0
suffix:colon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
id|POLLIN
op_or
id|POLLRDNORM
)paren
suffix:semicolon
)brace
DECL|function|um_idi_open
r_static
r_int
id|um_idi_open
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
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|um_idi_release
r_static
r_int
id|um_idi_release
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
r_int
id|adapter_nr
op_assign
id|iminor
c_func
(paren
id|inode
)paren
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
(paren
id|file-&gt;private_data
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|remove_entity
c_func
(paren
id|file-&gt;private_data
)paren
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|divas_um_idi_delete_entity
(paren
(paren
r_int
)paren
id|adapter_nr
comma
id|file-&gt;private_data
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
DECL|function|diva_os_get_context_size
r_int
id|diva_os_get_context_size
c_func
(paren
r_void
)paren
(brace
r_return
(paren
r_sizeof
(paren
id|diva_um_idi_os_context_t
)paren
)paren
suffix:semicolon
)brace
DECL|function|diva_os_wakeup_read
r_void
id|diva_os_wakeup_read
c_func
(paren
r_void
op_star
id|os_context
)paren
(brace
id|diva_um_idi_os_context_t
op_star
id|p_os
op_assign
(paren
id|diva_um_idi_os_context_t
op_star
)paren
id|os_context
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|p_os-&gt;read_wait
)paren
suffix:semicolon
)brace
DECL|function|diva_os_wakeup_close
r_void
id|diva_os_wakeup_close
c_func
(paren
r_void
op_star
id|os_context
)paren
(brace
id|diva_um_idi_os_context_t
op_star
id|p_os
op_assign
(paren
id|diva_um_idi_os_context_t
op_star
)paren
id|os_context
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|p_os-&gt;close_wait
)paren
suffix:semicolon
)brace
r_static
DECL|function|diva_um_timer_function
r_void
id|diva_um_timer_function
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|diva_um_idi_os_context_t
op_star
id|p_os
op_assign
(paren
id|diva_um_idi_os_context_t
op_star
)paren
id|data
suffix:semicolon
id|p_os-&gt;aborted
op_assign
l_int|1
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|p_os-&gt;read_wait
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|p_os-&gt;close_wait
)paren
suffix:semicolon
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;entity removal watchdog&quot;
)paren
)paren
)brace
multiline_comment|/*&n;**  If application exits without entity removal this function will remove&n;**  entity and block until removal is complete&n;*/
DECL|function|remove_entity
r_static
r_int
id|remove_entity
c_func
(paren
r_void
op_star
id|entity
)paren
(brace
r_struct
id|task_struct
op_star
id|curtask
op_assign
id|current
suffix:semicolon
id|diva_um_idi_os_context_t
op_star
id|p_os
suffix:semicolon
id|diva_um_idi_stop_wdog
c_func
(paren
id|entity
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entity
)paren
(brace
id|DBG_FTL
c_func
(paren
(paren
l_string|&quot;Zero entity on remove&quot;
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p_os
op_assign
(paren
id|diva_um_idi_os_context_t
op_star
)paren
id|diva_um_id_get_os_context
c_func
(paren
id|entity
)paren
)paren
)paren
(brace
id|DBG_FTL
c_func
(paren
(paren
l_string|&quot;Zero entity os context on remove&quot;
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|divas_um_idi_entity_assigned
c_func
(paren
id|entity
)paren
op_logical_or
id|p_os-&gt;aborted
)paren
(brace
multiline_comment|/*&n;&t;&t;   Entity is not assigned, also can be removed&n;&t;&t; */
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|DBG_TRC
c_func
(paren
(paren
l_string|&quot;E(%08x) check remove&quot;
comma
id|entity
)paren
)paren
multiline_comment|/*&n;&t;   If adapter not answers on remove request inside of&n;&t;   10 Sec, then adapter is dead&n;&t; */
id|diva_um_idi_start_wdog
c_func
(paren
id|entity
)paren
suffix:semicolon
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|curtask
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|p_os-&gt;close_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|divas_um_idi_entity_start_remove
c_func
(paren
id|entity
)paren
op_logical_or
id|p_os-&gt;aborted
)paren
(brace
r_break
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|p_os-&gt;close_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
id|DBG_TRC
c_func
(paren
(paren
l_string|&quot;E(%08x) start remove&quot;
comma
id|entity
)paren
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|curtask
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|p_os-&gt;close_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|divas_um_idi_entity_assigned
c_func
(paren
id|entity
)paren
op_logical_or
id|p_os-&gt;aborted
)paren
(brace
r_break
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|p_os-&gt;close_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
id|DBG_TRC
c_func
(paren
(paren
l_string|&quot;E(%08x) remove complete, aborted:%d&quot;
comma
id|entity
comma
id|p_os-&gt;aborted
)paren
)paren
id|diva_um_idi_stop_wdog
c_func
(paren
id|entity
)paren
suffix:semicolon
id|p_os-&gt;aborted
op_assign
l_int|0
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * timer watchdog&n; */
DECL|function|diva_um_idi_start_wdog
r_void
id|diva_um_idi_start_wdog
c_func
(paren
r_void
op_star
id|entity
)paren
(brace
id|diva_um_idi_os_context_t
op_star
id|p_os
suffix:semicolon
r_if
c_cond
(paren
id|entity
op_logical_and
(paren
(paren
id|p_os
op_assign
(paren
id|diva_um_idi_os_context_t
op_star
)paren
id|diva_um_id_get_os_context
c_func
(paren
id|entity
)paren
)paren
)paren
)paren
(brace
id|mod_timer
c_func
(paren
op_amp
id|p_os-&gt;diva_timer_id
comma
id|jiffies
op_plus
l_int|10
op_star
id|HZ
)paren
suffix:semicolon
)brace
)brace
DECL|function|diva_um_idi_stop_wdog
r_void
id|diva_um_idi_stop_wdog
c_func
(paren
r_void
op_star
id|entity
)paren
(brace
id|diva_um_idi_os_context_t
op_star
id|p_os
suffix:semicolon
r_if
c_cond
(paren
id|entity
op_logical_and
(paren
(paren
id|p_os
op_assign
(paren
id|diva_um_idi_os_context_t
op_star
)paren
id|diva_um_id_get_os_context
c_func
(paren
id|entity
)paren
)paren
)paren
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|p_os-&gt;diva_timer_id
)paren
suffix:semicolon
)brace
)brace
eof
