multiline_comment|/*&n; * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org)&n; * Copyright (C) 2001 - 2003 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/notifier.h&quot;
macro_line|#include &quot;linux/reboot.h&quot;
macro_line|#include &quot;linux/utsname.h&quot;
macro_line|#include &quot;linux/ctype.h&quot;
macro_line|#include &quot;linux/interrupt.h&quot;
macro_line|#include &quot;linux/sysrq.h&quot;
macro_line|#include &quot;linux/workqueue.h&quot;
macro_line|#include &quot;linux/module.h&quot;
macro_line|#include &quot;linux/file.h&quot;
macro_line|#include &quot;linux/fs.h&quot;
macro_line|#include &quot;linux/namei.h&quot;
macro_line|#include &quot;linux/proc_fs.h&quot;
macro_line|#include &quot;asm/irq.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;mconsole.h&quot;
macro_line|#include &quot;mconsole_kern.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;umid.h&quot;
macro_line|#include &quot;irq_kern.h&quot;
DECL|function|do_unlink_socket
r_static
r_int
id|do_unlink_socket
c_func
(paren
r_struct
id|notifier_block
op_star
id|notifier
comma
r_int
r_int
id|what
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|mconsole_unlink_socket
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|reboot_notifier
r_static
r_struct
id|notifier_block
id|reboot_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|do_unlink_socket
comma
dot
id|priority
op_assign
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/* Safe without explicit locking for now.  Tasklets provide their own &n; * locking, and the interrupt handler is safe because it can&squot;t interrupt&n; * itself and it can only happen on CPU 0.&n; */
DECL|variable|mc_requests
id|LIST_HEAD
c_func
(paren
id|mc_requests
)paren
suffix:semicolon
DECL|function|mc_work_proc
r_static
r_void
id|mc_work_proc
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_struct
id|mconsole_entry
op_star
id|req
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|mc_requests
)paren
)paren
(brace
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|req
op_assign
id|list_entry
c_func
(paren
id|mc_requests.next
comma
r_struct
id|mconsole_entry
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|req-&gt;list
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|req-&gt;request.cmd
op_member_access_from_pointer
id|handler
c_func
(paren
op_amp
id|req-&gt;request
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
)brace
id|DECLARE_WORK
c_func
(paren
id|mconsole_work
comma
id|mc_work_proc
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|mconsole_interrupt
r_static
id|irqreturn_t
id|mconsole_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|fd
suffix:semicolon
r_struct
id|mconsole_entry
op_star
r_new
suffix:semicolon
r_struct
id|mc_request
id|req
suffix:semicolon
id|fd
op_assign
(paren
r_int
)paren
id|dev_id
suffix:semicolon
r_while
c_loop
(paren
id|mconsole_get_request
c_func
(paren
id|fd
comma
op_amp
id|req
)paren
)paren
(brace
r_if
c_cond
(paren
id|req.cmd-&gt;context
op_eq
id|MCONSOLE_INTR
)paren
(brace
(paren
op_star
id|req.cmd-&gt;handler
)paren
(paren
op_amp
id|req
)paren
suffix:semicolon
)brace
r_else
(brace
r_new
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
r_new
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
(brace
id|mconsole_reply
c_func
(paren
op_amp
id|req
comma
l_string|&quot;Out of memory&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_new
op_member_access_from_pointer
id|request
op_assign
id|req
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
id|mc_requests
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|mc_requests
)paren
)paren
(brace
id|schedule_work
c_func
(paren
op_amp
id|mconsole_work
)paren
suffix:semicolon
)brace
id|reactivate_fd
c_func
(paren
id|fd
comma
id|MCONSOLE_IRQ
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|mconsole_version
r_void
id|mconsole_version
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
r_char
id|version
(braket
l_int|256
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|version
comma
l_string|&quot;%s %s %s %s %s&quot;
comma
id|system_utsname.sysname
comma
id|system_utsname.nodename
comma
id|system_utsname.release
comma
id|system_utsname.version
comma
id|system_utsname.machine
)paren
suffix:semicolon
id|mconsole_reply
c_func
(paren
id|req
comma
id|version
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|mconsole_log
r_void
id|mconsole_log
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
r_int
id|len
suffix:semicolon
r_char
op_star
id|ptr
op_assign
id|req-&gt;request.data
suffix:semicolon
id|ptr
op_add_assign
id|strlen
c_func
(paren
l_string|&quot;log &quot;
)paren
suffix:semicolon
id|len
op_assign
id|req-&gt;len
op_minus
(paren
id|ptr
op_minus
id|req-&gt;request.data
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%.*s&quot;
comma
id|len
comma
id|ptr
)paren
suffix:semicolon
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|mconsole_proc
r_void
id|mconsole_proc
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
r_struct
id|nameidata
id|nd
suffix:semicolon
r_struct
id|file_system_type
op_star
id|proc
suffix:semicolon
r_struct
id|super_block
op_star
id|super
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|n
comma
id|err
suffix:semicolon
r_char
op_star
id|ptr
op_assign
id|req-&gt;request.data
comma
op_star
id|buf
suffix:semicolon
id|ptr
op_add_assign
id|strlen
c_func
(paren
l_string|&quot;proc&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|ptr
)paren
)paren
(brace
id|ptr
op_increment
suffix:semicolon
)brace
id|proc
op_assign
id|get_fs_type
c_func
(paren
l_string|&quot;proc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc
op_eq
l_int|NULL
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;procfs not registered&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|super
op_assign
(paren
op_star
id|proc-&gt;get_sb
)paren
(paren
id|proc
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|put_filesystem
c_func
(paren
id|proc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|super
op_eq
l_int|NULL
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Failed to get procfs superblock&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|super-&gt;s_umount
)paren
suffix:semicolon
id|nd.dentry
op_assign
id|super-&gt;s_root
suffix:semicolon
id|nd.mnt
op_assign
l_int|NULL
suffix:semicolon
id|nd.flags
op_assign
id|O_RDONLY
op_plus
l_int|1
suffix:semicolon
id|nd.last_type
op_assign
id|LAST_ROOT
suffix:semicolon
id|err
op_assign
id|link_path_walk
c_func
(paren
id|ptr
comma
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Failed to look up file&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_kill
suffix:semicolon
)brace
id|file
op_assign
id|dentry_open
c_func
(paren
id|nd.dentry
comma
id|nd.mnt
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|file
)paren
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Failed to open file&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_kill
suffix:semicolon
)brace
id|buf
op_assign
id|kmalloc
c_func
(paren
id|PAGE_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|NULL
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Failed to allocate buffer&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_fput
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|file-&gt;f_op
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|file-&gt;f_op-&gt;read
op_ne
l_int|NULL
)paren
)paren
(brace
r_do
(brace
id|n
op_assign
(paren
op_star
id|file-&gt;f_op-&gt;read
)paren
(paren
id|file
comma
id|buf
comma
id|PAGE_SIZE
op_minus
l_int|1
comma
op_amp
id|file-&gt;f_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
l_int|0
)paren
(brace
id|buf
(braket
id|n
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|mconsole_reply
c_func
(paren
id|req
comma
id|buf
comma
l_int|0
comma
(paren
id|n
OG
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Read of file failed&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|n
OG
l_int|0
)paren
(brace
suffix:semicolon
)brace
)brace
r_else
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|out_free
suffix:colon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|out_fput
suffix:colon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
id|out_kill
suffix:colon
id|deactivate_super
c_func
(paren
id|super
)paren
suffix:semicolon
id|out
suffix:colon
suffix:semicolon
)brace
DECL|macro|UML_MCONSOLE_HELPTEXT
mdefine_line|#define UML_MCONSOLE_HELPTEXT &bslash;&n;&quot;Commands: &bslash;n&bslash;&n;    version - Get kernel version &bslash;n&bslash;&n;    help - Print this message &bslash;n&bslash;&n;    halt - Halt UML &bslash;n&bslash;&n;    reboot - Reboot UML &bslash;n&bslash;&n;    config &lt;dev&gt;=&lt;config&gt; - Add a new device to UML;  &bslash;n&bslash;&n;&t;same syntax as command line &bslash;n&bslash;&n;    config &lt;dev&gt; - Query the configuration of a device &bslash;n&bslash;&n;    remove &lt;dev&gt; - Remove a device from UML &bslash;n&bslash;&n;    sysrq &lt;letter&gt; - Performs the SysRq action controlled by the letter &bslash;n&bslash;&n;    cad - invoke the Ctl-Alt-Del handler &bslash;n&bslash;&n;    stop - pause the UML; it will do nothing until it receives a &squot;go&squot; &bslash;n&bslash;&n;    go - continue the UML after a &squot;stop&squot; &bslash;n&bslash;&n;    log &lt;string&gt; - make UML enter &lt;string&gt; into the kernel log&bslash;n&bslash;&n;    proc &lt;file&gt; - returns the contents of the UML&squot;s /proc/&lt;file&gt;&bslash;n&bslash;&n;&quot;
DECL|function|mconsole_help
r_void
id|mconsole_help
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
id|UML_MCONSOLE_HELPTEXT
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|mconsole_halt
r_void
id|mconsole_halt
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|machine_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|mconsole_reboot
r_void
id|mconsole_reboot
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|machine_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_extern
r_void
id|ctrl_alt_del
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|mconsole_cad
r_void
id|mconsole_cad
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|ctrl_alt_del
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|mconsole_go
r_void
id|mconsole_go
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Not stopped&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|mconsole_stop
r_void
id|mconsole_stop
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
id|deactivate_fd
c_func
(paren
id|req-&gt;originating_fd
comma
id|MCONSOLE_IRQ
)paren
suffix:semicolon
id|os_set_fd_block
c_func
(paren
id|req-&gt;originating_fd
comma
l_int|1
)paren
suffix:semicolon
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|mconsole_get_request
c_func
(paren
id|req-&gt;originating_fd
comma
id|req
)paren
)paren
(brace
r_if
c_cond
(paren
id|req-&gt;cmd-&gt;handler
op_eq
id|mconsole_go
)paren
(brace
r_break
suffix:semicolon
)brace
(paren
op_star
id|req-&gt;cmd-&gt;handler
)paren
(paren
id|req
)paren
suffix:semicolon
)brace
id|os_set_fd_block
c_func
(paren
id|req-&gt;originating_fd
comma
l_int|0
)paren
suffix:semicolon
id|reactivate_fd
c_func
(paren
id|req-&gt;originating_fd
comma
id|MCONSOLE_IRQ
)paren
suffix:semicolon
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* This list is populated by __initcall routines. */
DECL|variable|mconsole_devices
id|LIST_HEAD
c_func
(paren
id|mconsole_devices
)paren
suffix:semicolon
DECL|function|mconsole_register_dev
r_void
id|mconsole_register_dev
c_func
(paren
r_struct
id|mc_device
op_star
r_new
)paren
(brace
id|list_add
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|list
comma
op_amp
id|mconsole_devices
)paren
suffix:semicolon
)brace
DECL|function|mconsole_find_dev
r_static
r_struct
id|mc_device
op_star
id|mconsole_find_dev
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|mc_device
op_star
id|dev
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
op_amp
id|mconsole_devices
)paren
(brace
id|dev
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|mc_device
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|name
comma
id|dev-&gt;name
comma
id|strlen
c_func
(paren
id|dev-&gt;name
)paren
)paren
)paren
(brace
r_return
id|dev
suffix:semicolon
)brace
)brace
)def_block
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|macro|CONFIG_BUF_SIZE
mdefine_line|#define CONFIG_BUF_SIZE 64
DECL|function|mconsole_get_config
r_static
r_void
id|mconsole_get_config
c_func
(paren
r_int
(paren
op_star
id|get_config
)paren
(paren
r_char
op_star
comma
r_char
op_star
comma
r_int
comma
r_char
op_star
op_star
)paren
comma
r_struct
id|mc_request
op_star
id|req
comma
r_char
op_star
id|name
)paren
(brace
r_char
id|default_buf
(braket
id|CONFIG_BUF_SIZE
)braket
comma
op_star
id|error
comma
op_star
id|buf
suffix:semicolon
r_int
id|n
comma
id|size
suffix:semicolon
r_if
c_cond
(paren
id|get_config
op_eq
l_int|NULL
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;No get_config routine defined&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|error
op_assign
l_int|NULL
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
id|default_buf
)paren
op_div
r_sizeof
(paren
id|default_buf
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|buf
op_assign
id|default_buf
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|n
op_assign
(paren
op_star
id|get_config
)paren
(paren
id|name
comma
id|buf
comma
id|size
comma
op_amp
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
l_int|NULL
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
id|error
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_le
id|size
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
id|buf
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buf
op_ne
id|default_buf
)paren
(brace
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
id|size
op_assign
id|n
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|NULL
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Failed to allocate buffer&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|buf
op_ne
id|default_buf
)paren
(brace
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
)brace
DECL|function|mconsole_config
r_void
id|mconsole_config
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
r_struct
id|mc_device
op_star
id|dev
suffix:semicolon
r_char
op_star
id|ptr
op_assign
id|req-&gt;request.data
comma
op_star
id|name
suffix:semicolon
r_int
id|err
suffix:semicolon
id|ptr
op_add_assign
id|strlen
c_func
(paren
l_string|&quot;config&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|ptr
)paren
)paren
(brace
id|ptr
op_increment
suffix:semicolon
)brace
id|dev
op_assign
id|mconsole_find_dev
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Bad configuration option&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|name
op_assign
op_amp
id|ptr
(braket
id|strlen
c_func
(paren
id|dev-&gt;name
)paren
)braket
suffix:semicolon
id|ptr
op_assign
id|name
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|ptr
op_ne
l_char|&squot;=&squot;
)paren
op_logical_and
(paren
op_star
id|ptr
op_ne
l_char|&squot;&bslash;0&squot;
)paren
)paren
(brace
id|ptr
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|ptr
op_eq
l_char|&squot;=&squot;
)paren
(brace
id|err
op_assign
(paren
op_star
id|dev-&gt;config
)paren
(paren
id|name
)paren
suffix:semicolon
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;&quot;
comma
id|err
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|mconsole_get_config
c_func
(paren
id|dev-&gt;get_config
comma
id|req
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|mconsole_remove
r_void
id|mconsole_remove
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
r_struct
id|mc_device
op_star
id|dev
suffix:semicolon
r_char
op_star
id|ptr
op_assign
id|req-&gt;request.data
suffix:semicolon
r_int
id|err
suffix:semicolon
id|ptr
op_add_assign
id|strlen
c_func
(paren
l_string|&quot;remove&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|ptr
)paren
)paren
(brace
id|ptr
op_increment
suffix:semicolon
)brace
id|dev
op_assign
id|mconsole_find_dev
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Bad remove option&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|err
op_assign
(paren
op_star
id|dev-&gt;remove
)paren
(paren
op_amp
id|ptr
(braket
id|strlen
c_func
(paren
id|dev-&gt;name
)paren
)braket
)paren
suffix:semicolon
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;&quot;
comma
id|err
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|function|mconsole_sysrq
r_void
id|mconsole_sysrq
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
r_char
op_star
id|ptr
op_assign
id|req-&gt;request.data
suffix:semicolon
id|ptr
op_add_assign
id|strlen
c_func
(paren
l_string|&quot;sysrq&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|ptr
)paren
)paren
(brace
id|ptr
op_increment
suffix:semicolon
)brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|handle_sysrq
c_func
(paren
op_star
id|ptr
comma
op_amp
id|current-&gt;thread.regs
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|mconsole_sysrq
r_void
id|mconsole_sysrq
c_func
(paren
r_struct
id|mc_request
op_star
id|req
)paren
(brace
id|mconsole_reply
c_func
(paren
id|req
comma
l_string|&quot;Sysrq not compiled in&quot;
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Changed by mconsole_setup, which is __setup, and called before SMP is&n; * active.&n; */
DECL|variable|notify_socket
r_static
r_char
op_star
id|notify_socket
op_assign
l_int|NULL
suffix:semicolon
DECL|function|mconsole_init
r_int
id|mconsole_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
comma
id|sock
suffix:semicolon
r_char
id|file
(braket
l_int|256
)braket
suffix:semicolon
r_if
c_cond
(paren
id|umid_file_name
c_func
(paren
l_string|&quot;mconsole&quot;
comma
id|file
comma
r_sizeof
(paren
id|file
)paren
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|snprintf
c_func
(paren
id|mconsole_socket_name
comma
r_sizeof
(paren
id|file
)paren
comma
l_string|&quot;%s&quot;
comma
id|file
)paren
suffix:semicolon
id|sock
op_assign
id|os_create_unix_socket
c_func
(paren
id|file
comma
r_sizeof
(paren
id|file
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to initialize management console&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|register_reboot_notifier
c_func
(paren
op_amp
id|reboot_notifier
)paren
suffix:semicolon
id|err
op_assign
id|um_request_irq
c_func
(paren
id|MCONSOLE_IRQ
comma
id|sock
comma
id|IRQ_READ
comma
id|mconsole_interrupt
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
op_or
id|SA_SAMPLE_RANDOM
comma
l_string|&quot;mconsole&quot;
comma
(paren
r_void
op_star
)paren
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to get IRQ for management console&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|notify_socket
op_ne
l_int|NULL
)paren
(brace
id|notify_socket
op_assign
id|uml_strdup
c_func
(paren
id|notify_socket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|notify_socket
op_ne
l_int|NULL
)paren
(brace
id|mconsole_notify
c_func
(paren
id|notify_socket
comma
id|MCONSOLE_SOCKET
comma
id|mconsole_socket_name
comma
id|strlen
c_func
(paren
id|mconsole_socket_name
)paren
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mconsole_setup failed to strdup &quot;
l_string|&quot;string&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;mconsole (version %d) initialized on %s&bslash;n&quot;
comma
id|MCONSOLE_VERSION
comma
id|mconsole_socket_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mconsole_init
id|__initcall
c_func
(paren
id|mconsole_init
)paren
suffix:semicolon
DECL|function|write_proc_mconsole
r_static
r_int
id|write_proc_mconsole
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
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|buf
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
id|count
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|buffer
comma
id|count
)paren
)paren
(brace
id|count
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|buf
(braket
id|count
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|mconsole_notify
c_func
(paren
id|notify_socket
comma
id|MCONSOLE_USER_NOTIFY
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|create_proc_mconsole
r_static
r_int
id|create_proc_mconsole
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
r_if
c_cond
(paren
id|notify_socket
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;mconsole&quot;
comma
id|S_IFREG
op_or
l_int|0200
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;create_proc_mconsole : create_proc_entry failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ent-&gt;read_proc
op_assign
l_int|NULL
suffix:semicolon
id|ent-&gt;write_proc
op_assign
id|write_proc_mconsole
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|notify_spinlock
r_static
id|spinlock_t
id|notify_spinlock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|lock_notify
r_void
id|lock_notify
c_func
(paren
r_void
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|notify_spinlock
)paren
suffix:semicolon
)brace
DECL|function|unlock_notify
r_void
id|unlock_notify
c_func
(paren
r_void
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|notify_spinlock
)paren
suffix:semicolon
)brace
DECL|variable|create_proc_mconsole
id|__initcall
c_func
(paren
id|create_proc_mconsole
)paren
suffix:semicolon
DECL|macro|NOTIFY
mdefine_line|#define NOTIFY &quot;=notify:&quot;
DECL|function|mconsole_setup
r_static
r_int
id|mconsole_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
id|NOTIFY
comma
id|strlen
c_func
(paren
id|NOTIFY
)paren
)paren
)paren
(brace
id|str
op_add_assign
id|strlen
c_func
(paren
id|NOTIFY
)paren
suffix:semicolon
id|notify_socket
op_assign
id|str
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mconsole_setup : Unknown option - &squot;%s&squot;&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;mconsole&quot;
comma
id|mconsole_setup
)paren
suffix:semicolon
id|__uml_help
c_func
(paren
id|mconsole_setup
comma
l_string|&quot;mconsole=notify:&lt;socket&gt;&bslash;n&quot;
l_string|&quot;    Requests that the mconsole driver send a message to the named Unix&bslash;n&quot;
l_string|&quot;    socket containing the name of the mconsole socket.  This also serves&bslash;n&quot;
l_string|&quot;    to notify outside processes when UML has booted far enough to respond&bslash;n&quot;
l_string|&quot;    to mconsole requests.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
DECL|function|notify_panic
r_static
r_int
id|notify_panic
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|unused1
comma
r_void
op_star
id|ptr
)paren
(brace
r_char
op_star
id|message
op_assign
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|notify_socket
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|mconsole_notify
c_func
(paren
id|notify_socket
comma
id|MCONSOLE_PANIC
comma
id|message
comma
id|strlen
c_func
(paren
id|message
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|panic_exit_notifier
r_static
r_struct
id|notifier_block
id|panic_exit_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|notify_panic
comma
dot
id|next
op_assign
l_int|NULL
comma
dot
id|priority
op_assign
l_int|1
)brace
suffix:semicolon
DECL|function|add_notifier
r_static
r_int
id|add_notifier
c_func
(paren
r_void
)paren
(brace
id|notifier_chain_register
c_func
(paren
op_amp
id|panic_notifier_list
comma
op_amp
id|panic_exit_notifier
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|add_notifier
id|__initcall
c_func
(paren
id|add_notifier
)paren
suffix:semicolon
DECL|function|mconsole_notify_socket
r_char
op_star
id|mconsole_notify_socket
c_func
(paren
r_void
)paren
(brace
r_return
id|notify_socket
suffix:semicolon
)brace
DECL|variable|mconsole_notify_socket
id|EXPORT_SYMBOL
c_func
(paren
id|mconsole_notify_socket
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
