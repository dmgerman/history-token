multiline_comment|/*&n; * net/nonet.c&n; *&n; * Dummy functions to allow us to configure network support entirely&n; * out of the kernel.&n; *&n; * Distributed under the terms of the GNU GPL version 2.&n; * Copyright (c) Matthew Wilcox 2003&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|function|sock_init
r_void
id|__init
id|sock_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Linux NoNET1.0 for Linux 2.6&bslash;n&quot;
)paren
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
r_struct
id|file_operations
id|bad_sock_fops
op_assign
(brace
dot
id|open
op_assign
id|sock_no_open
comma
)brace
suffix:semicolon
eof
