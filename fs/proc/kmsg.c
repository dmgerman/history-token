multiline_comment|/*&n; *  linux/fs/proc/kmsg.c&n; *&n; *  Copyright (C) 1992  by Linus Torvalds&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
id|wait_queue_head_t
id|log_wait
suffix:semicolon
r_extern
r_int
id|do_syslog
c_func
(paren
r_int
id|type
comma
r_char
op_star
id|bug
comma
r_int
id|count
)paren
suffix:semicolon
DECL|function|kmsg_open
r_static
r_int
id|kmsg_open
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
id|do_syslog
c_func
(paren
l_int|1
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|kmsg_release
r_static
r_int
id|kmsg_release
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
(paren
r_void
)paren
id|do_syslog
c_func
(paren
l_int|0
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kmsg_read
r_static
id|ssize_t
id|kmsg_read
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
id|ppos
)paren
(brace
r_return
id|do_syslog
c_func
(paren
l_int|2
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|kmsg_poll
r_static
r_int
r_int
id|kmsg_poll
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
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|log_wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_syslog
c_func
(paren
l_int|9
comma
l_int|0
comma
l_int|0
)paren
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
DECL|variable|proc_kmsg_operations
r_struct
id|file_operations
id|proc_kmsg_operations
op_assign
(brace
dot
id|read
op_assign
id|kmsg_read
comma
dot
id|poll
op_assign
id|kmsg_poll
comma
dot
id|open
op_assign
id|kmsg_open
comma
dot
id|release
op_assign
id|kmsg_release
comma
)brace
suffix:semicolon
eof
