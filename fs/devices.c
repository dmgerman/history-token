multiline_comment|/*&n; *  linux/fs/devices.c&n; *&n; * (C) 1993 Matthias Urlichs -- collected common code and tables.&n; * &n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  Added kerneld support: Jacques Gelinas and Bjorn Ekwall&n; *  (changed to kmod)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
multiline_comment|/* serial module kmod load support */
r_struct
id|tty_driver
op_star
id|get_tty_driver
c_func
(paren
id|kdev_t
id|device
)paren
suffix:semicolon
DECL|macro|isa_tty_dev
mdefine_line|#define isa_tty_dev(ma)&t;(ma == TTY_MAJOR || ma == TTYAUX_MAJOR)
DECL|macro|need_serial
mdefine_line|#define need_serial(ma,mi) (get_tty_driver(mk_kdev(ma,mi)) == NULL)
macro_line|#endif
DECL|struct|device_struct
r_struct
id|device_struct
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
)brace
suffix:semicolon
DECL|variable|chrdevs_lock
r_static
id|rwlock_t
id|chrdevs_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|chrdevs
r_static
r_struct
id|device_struct
id|chrdevs
(braket
id|MAX_CHRDEV
)braket
suffix:semicolon
r_extern
r_int
id|get_blkdev_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|function|get_device_list
r_int
id|get_device_list
c_func
(paren
r_char
op_star
id|page
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;Character devices:&bslash;n&quot;
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|chrdevs_lock
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
id|MAX_CHRDEV
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|chrdevs
(braket
id|i
)braket
dot
id|fops
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%3d %s&bslash;n&quot;
comma
id|i
comma
id|chrdevs
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
id|len
op_add_assign
id|get_blkdev_list
c_func
(paren
id|page
op_plus
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n;&t;Return the function table of a device.&n;&t;Load the driver if needed.&n;&t;Increment the reference count of module in question.&n;*/
DECL|function|get_chrfops
r_static
r_struct
id|file_operations
op_star
id|get_chrfops
c_func
(paren
r_int
r_int
id|major
comma
r_int
r_int
id|minor
)paren
(brace
r_struct
id|file_operations
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|major
op_logical_or
id|major
op_ge
id|MAX_CHRDEV
)paren
r_return
l_int|NULL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
id|ret
op_assign
id|fops_get
c_func
(paren
id|chrdevs
(braket
id|major
)braket
dot
id|fops
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
id|ret
op_logical_and
id|isa_tty_dev
c_func
(paren
id|major
)paren
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_serial
c_func
(paren
id|major
comma
id|minor
)paren
)paren
(brace
multiline_comment|/* Force request_module anyway, but what for? */
id|fops_put
c_func
(paren
id|ret
)paren
suffix:semicolon
id|ret
op_assign
l_int|NULL
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;char-major-%d&quot;
comma
id|major
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|name
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
id|ret
op_assign
id|fops_get
c_func
(paren
id|chrdevs
(braket
id|major
)braket
dot
id|fops
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
DECL|function|register_chrdev
r_int
id|register_chrdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|file_operations
op_star
id|fops
)paren
(brace
r_if
c_cond
(paren
id|devfs_only
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|major
op_eq
l_int|0
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|major
op_assign
id|MAX_CHRDEV
op_minus
l_int|1
suffix:semicolon
id|major
OG
l_int|0
suffix:semicolon
id|major
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_eq
l_int|NULL
)paren
(brace
id|chrdevs
(braket
id|major
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_assign
id|fops
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
id|major
suffix:semicolon
)brace
)brace
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
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
id|major
op_ge
id|MAX_CHRDEV
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_logical_and
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_ne
id|fops
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|chrdevs
(braket
id|major
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_assign
id|fops
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_chrdev
r_int
id|unregister_chrdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
id|devfs_only
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|major
op_ge
id|MAX_CHRDEV
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_logical_or
id|strcmp
c_func
(paren
id|chrdevs
(braket
id|major
)braket
dot
id|name
comma
id|name
)paren
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|chrdevs
(braket
id|major
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|chrdevs
(braket
id|major
)braket
dot
id|fops
op_assign
l_int|NULL
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Called every time a character special file is opened&n; */
DECL|function|chrdev_open
r_int
id|chrdev_open
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
r_int
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|filp-&gt;f_op
op_assign
id|get_chrfops
c_func
(paren
id|major
c_func
(paren
id|inode-&gt;i_rdev
)paren
comma
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_op
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_op-&gt;open
op_ne
l_int|NULL
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
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
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Dummy default file-operations: the only thing this does&n; * is contain the open that then fills in the correct operations&n; * depending on the special file...&n; */
DECL|variable|def_chr_fops
r_static
r_struct
id|file_operations
id|def_chr_fops
op_assign
(brace
dot
id|open
op_assign
id|chrdev_open
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Print device name (in decimal, hexadecimal or symbolic)&n; * Note: returns pointer to static data!&n; */
DECL|function|kdevname
r_const
r_char
op_star
id|kdevname
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|32
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%02x:%02x&quot;
comma
id|major
c_func
(paren
id|dev
)paren
comma
id|minor
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|cdevname
r_const
r_char
op_star
id|cdevname
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|32
)braket
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|chrdevs
(braket
id|major
c_func
(paren
id|dev
)paren
)braket
dot
id|name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|name
op_assign
l_string|&quot;unknown-char&quot;
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s(%d,%d)&quot;
comma
id|name
comma
id|major
c_func
(paren
id|dev
)paren
comma
id|minor
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|sock_no_open
r_static
r_int
id|sock_no_open
c_func
(paren
r_struct
id|inode
op_star
id|irrelevant
comma
r_struct
id|file
op_star
id|dontcare
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|variable|bad_sock_fops
r_static
r_struct
id|file_operations
id|bad_sock_fops
op_assign
(brace
dot
id|open
op_assign
id|sock_no_open
)brace
suffix:semicolon
DECL|function|init_special_inode
r_void
id|init_special_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|umode_t
id|mode
comma
id|dev_t
id|rdev
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|mode
)paren
)paren
(brace
id|inode-&gt;i_fop
op_assign
op_amp
id|def_chr_fops
suffix:semicolon
id|inode-&gt;i_rdev
op_assign
id|to_kdev_t
c_func
(paren
id|rdev
)paren
suffix:semicolon
id|inode-&gt;i_cdev
op_assign
id|cdget
c_func
(paren
id|rdev
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|mode
)paren
)paren
(brace
id|inode-&gt;i_fop
op_assign
op_amp
id|def_blk_fops
suffix:semicolon
id|inode-&gt;i_rdev
op_assign
id|to_kdev_t
c_func
(paren
id|rdev
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISFIFO
c_func
(paren
id|mode
)paren
)paren
id|inode-&gt;i_fop
op_assign
op_amp
id|def_fifo_fops
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISSOCK
c_func
(paren
id|mode
)paren
)paren
id|inode-&gt;i_fop
op_assign
op_amp
id|bad_sock_fops
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;init_special_inode: bogus imode (%o)&bslash;n&quot;
comma
id|mode
)paren
suffix:semicolon
)brace
eof
