multiline_comment|/*&n; * NETLINK&t;An implementation of a loadable kernel mode driver providing&n; *&t;&t;multiple kernel/user space bidirectional communications links.&n; *&n; * &t;&t;Author: &t;Alan Cox &lt;alan@redhat.com&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; * &n; *&t;Now netlink devices are emulated on the top of netlink sockets&n; *&t;by compatibility reasons. Remove this file after a period. --ANK&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|open_map
r_static
r_int
id|open_map
suffix:semicolon
DECL|variable|netlink_user
r_static
r_struct
id|socket
op_star
id|netlink_user
(braket
id|MAX_LINKS
)braket
suffix:semicolon
multiline_comment|/*&n; *&t;Device operations&n; */
DECL|function|netlink_poll
r_static
r_int
r_int
id|netlink_poll
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
r_struct
id|socket
op_star
id|sock
op_assign
id|netlink_user
(braket
id|minor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;ops-&gt;poll
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|sock-&gt;ops
op_member_access_from_pointer
id|poll
c_func
(paren
id|file
comma
id|sock
comma
id|wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Write a message to the kernel side of a communication link&n; */
DECL|function|netlink_write
r_static
id|ssize_t
id|netlink_write
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
id|pos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|socket
op_star
id|sock
op_assign
id|netlink_user
(braket
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_struct
id|msghdr
id|msg
suffix:semicolon
r_struct
id|iovec
id|iov
suffix:semicolon
id|iov.iov_base
op_assign
(paren
r_void
op_star
)paren
id|buf
suffix:semicolon
id|iov.iov_len
op_assign
id|count
suffix:semicolon
id|msg.msg_name
op_assign
l_int|NULL
suffix:semicolon
id|msg.msg_namelen
op_assign
l_int|0
suffix:semicolon
id|msg.msg_controllen
op_assign
l_int|0
suffix:semicolon
id|msg.msg_flags
op_assign
l_int|0
suffix:semicolon
id|msg.msg_iov
op_assign
op_amp
id|iov
suffix:semicolon
id|msg.msg_iovlen
op_assign
l_int|1
suffix:semicolon
r_return
id|sock_sendmsg
c_func
(paren
id|sock
comma
op_amp
id|msg
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Read a message from the kernel side of the communication link&n; */
DECL|function|netlink_read
r_static
id|ssize_t
id|netlink_read
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
id|pos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|socket
op_star
id|sock
op_assign
id|netlink_user
(braket
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_struct
id|msghdr
id|msg
suffix:semicolon
r_struct
id|iovec
id|iov
suffix:semicolon
id|iov.iov_base
op_assign
id|buf
suffix:semicolon
id|iov.iov_len
op_assign
id|count
suffix:semicolon
id|msg.msg_name
op_assign
l_int|NULL
suffix:semicolon
id|msg.msg_namelen
op_assign
l_int|0
suffix:semicolon
id|msg.msg_controllen
op_assign
l_int|0
suffix:semicolon
id|msg.msg_flags
op_assign
l_int|0
suffix:semicolon
id|msg.msg_iov
op_assign
op_amp
id|iov
suffix:semicolon
id|msg.msg_iovlen
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
id|msg.msg_flags
op_assign
id|MSG_DONTWAIT
suffix:semicolon
r_return
id|sock_recvmsg
c_func
(paren
id|sock
comma
op_amp
id|msg
comma
id|count
comma
id|msg.msg_flags
)paren
suffix:semicolon
)brace
DECL|function|netlink_open
r_static
r_int
id|netlink_open
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
id|minor
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|socket
op_star
id|sock
suffix:semicolon
r_struct
id|sockaddr_nl
id|nladdr
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ge
id|MAX_LINKS
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|minor
comma
op_amp
id|open_map
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|err
op_assign
id|sock_create
c_func
(paren
id|PF_NETLINK
comma
id|SOCK_RAW
comma
id|minor
comma
op_amp
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|nladdr
comma
l_int|0
comma
r_sizeof
(paren
id|nladdr
)paren
)paren
suffix:semicolon
id|nladdr.nl_family
op_assign
id|AF_NETLINK
suffix:semicolon
id|nladdr.nl_groups
op_assign
op_complement
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|sock-&gt;ops
op_member_access_from_pointer
id|bind
c_func
(paren
id|sock
comma
(paren
r_struct
id|sockaddr
op_star
)paren
op_amp
id|nladdr
comma
r_sizeof
(paren
id|nladdr
)paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|sock_release
c_func
(paren
id|sock
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|netlink_user
(braket
id|minor
)braket
op_assign
id|sock
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|clear_bit
c_func
(paren
id|minor
comma
op_amp
id|open_map
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|netlink_release
r_static
r_int
id|netlink_release
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
id|minor
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|socket
op_star
id|sock
suffix:semicolon
id|sock
op_assign
id|netlink_user
(braket
id|minor
)braket
suffix:semicolon
id|netlink_user
(braket
id|minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|clear_bit
c_func
(paren
id|minor
comma
op_amp
id|open_map
)paren
suffix:semicolon
id|sock_release
c_func
(paren
id|sock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|netlink_ioctl
r_static
r_int
id|netlink_ioctl
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
r_int
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
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ge
id|MAX_LINKS
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_default
suffix:colon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|netlink_fops
r_static
r_struct
id|file_operations
id|netlink_fops
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
id|netlink_read
comma
dot
id|write
op_assign
id|netlink_write
comma
dot
id|poll
op_assign
id|netlink_poll
comma
dot
id|ioctl
op_assign
id|netlink_ioctl
comma
dot
id|open
op_assign
id|netlink_open
comma
dot
id|release
op_assign
id|netlink_release
comma
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|variable|entries
)brace
id|entries
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;route&quot;
comma
dot
id|minor
op_assign
id|NETLINK_ROUTE
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;skip&quot;
comma
dot
id|minor
op_assign
id|NETLINK_SKIP
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;usersock&quot;
comma
dot
id|minor
op_assign
id|NETLINK_USERSOCK
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;fwmonitor&quot;
comma
dot
id|minor
op_assign
id|NETLINK_FIREWALL
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;tcpdiag&quot;
comma
dot
id|minor
op_assign
id|NETLINK_TCPDIAG
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;nflog&quot;
comma
dot
id|minor
op_assign
id|NETLINK_NFLOG
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;xfrm&quot;
comma
dot
id|minor
op_assign
id|NETLINK_XFRM
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;arpd&quot;
comma
dot
id|minor
op_assign
id|NETLINK_ARPD
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;route6&quot;
comma
dot
id|minor
op_assign
id|NETLINK_ROUTE6
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;ip6_fw&quot;
comma
dot
id|minor
op_assign
id|NETLINK_IP6_FW
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;dnrtmsg&quot;
comma
dot
id|minor
op_assign
id|NETLINK_DNRTMSG
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|init_netlink
r_static
r_int
id|__init
id|init_netlink
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|NETLINK_MAJOR
comma
l_string|&quot;netlink&quot;
comma
op_amp
id|netlink_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;netlink: unable to get major %d&bslash;n&quot;
comma
id|NETLINK_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|devfs_mk_dir
c_func
(paren
l_string|&quot;netlink&quot;
)paren
suffix:semicolon
multiline_comment|/*  Someone tell me the official names for the uppercase ones  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|entries
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|NETLINK_MAJOR
comma
id|entries
(braket
id|i
)braket
dot
id|minor
)paren
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_string|&quot;netlink/%s&quot;
comma
id|entries
(braket
id|i
)braket
dot
id|name
)paren
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|NETLINK_MAJOR
comma
id|i
op_plus
l_int|16
)paren
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_string|&quot;netlink/tap%d&quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_netlink
r_static
r_void
id|__exit
id|cleanup_netlink
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|ARRAY_SIZE
c_func
(paren
id|entries
)paren
suffix:semicolon
id|i
op_increment
)paren
id|devfs_remove
c_func
(paren
l_string|&quot;netlink/%s&quot;
comma
id|entries
(braket
id|i
)braket
dot
id|name
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|devfs_remove
c_func
(paren
l_string|&quot;netlink/tap%d&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;netlink&quot;
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|NETLINK_MAJOR
comma
l_string|&quot;netlink&quot;
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|init_netlink
id|module_init
c_func
(paren
id|init_netlink
)paren
suffix:semicolon
DECL|variable|cleanup_netlink
id|module_exit
c_func
(paren
id|cleanup_netlink
)paren
suffix:semicolon
eof
