multiline_comment|/* MiroSOUND PCM20 radio rds interface driver&n; * (c) 2001 Robert Siemer &lt;Robert.Siemer@gmx.de&gt;&n; * Thanks to Fred Seidel. See miropcm20-rds-core.c for further information.&n; */
multiline_comment|/* Revision history:&n; *&n; *   2001-04-18  Robert Siemer &lt;Robert.Siemer@gmx.de&gt;&n; *        separate file for user interface driver&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &quot;miropcm20-rds-core.h&quot;
DECL|variable|text_buffer
r_static
r_char
op_star
id|text_buffer
suffix:semicolon
DECL|variable|rds_users
r_static
r_int
id|rds_users
op_assign
l_int|0
suffix:semicolon
DECL|function|rds_f_open
r_static
r_int
id|rds_f_open
c_func
(paren
r_struct
id|inode
op_star
id|in
comma
r_struct
id|file
op_star
id|fi
)paren
(brace
r_if
c_cond
(paren
id|rds_users
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|rds_users
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|text_buffer
op_assign
id|kmalloc
c_func
(paren
l_int|66
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|rds_users
op_decrement
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;aci-rds: Out of memory by open()...&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rds_f_release
r_static
r_int
id|rds_f_release
c_func
(paren
r_struct
id|inode
op_star
id|in
comma
r_struct
id|file
op_star
id|fi
)paren
(brace
id|kfree
c_func
(paren
id|text_buffer
)paren
suffix:semicolon
id|rds_users
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|print_matrix
r_static
r_void
id|print_matrix
c_func
(paren
r_char
op_star
id|ch
comma
r_char
id|out
(braket
)braket
)paren
(brace
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|7
suffix:semicolon
id|j
op_ge
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|out
(braket
l_int|7
op_minus
id|j
)braket
op_assign
(paren
(paren
op_star
id|ch
op_rshift
id|j
)paren
op_amp
l_int|0x1
)paren
op_plus
l_char|&squot;0&squot;
suffix:semicolon
)brace
)brace
DECL|function|rds_f_read
r_static
id|ssize_t
id|rds_f_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
comma
r_int
id|length
comma
id|loff_t
op_star
id|offset
)paren
(brace
singleline_comment|//&t;i = sprintf(text_buffer, &quot;length: %d, offset: %d&bslash;n&quot;, length, *offset);
r_char
id|c
suffix:semicolon
r_char
id|bits
(braket
l_int|8
)braket
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|2
op_star
id|HZ
)paren
suffix:semicolon
id|aci_rds_cmd
c_func
(paren
id|RDS_STATUS
comma
op_amp
id|c
comma
l_int|1
)paren
suffix:semicolon
id|print_matrix
c_func
(paren
op_amp
id|c
comma
id|bits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|bits
comma
l_int|8
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/*&t;if ((c &gt;&gt; 3) &amp; 1) {&n;&t;&t;aci_rds_cmd(RDS_STATIONNAME, text_buffer+1, 8);&n;&t;&t;text_buffer[0]  = &squot; &squot; ;&n;&t;&t;text_buffer[9]  = &squot;&bslash;n&squot;;&n;&t;&t;return copy_to_user(buffer+8, text_buffer, 10) ? -EFAULT: 18;&n;&t;}&n;*/
multiline_comment|/*&t;if ((c &gt;&gt; 6) &amp; 1) {&n;&t;&t;aci_rds_cmd(RDS_PTYTATP, &amp;c, 1);&n;&t;&t;if ( c &amp; 1)&n;&t;&t;&t;sprintf(text_buffer, &quot; M&quot;);&n;&t;&t;else&n;&t;&t;&t;sprintf(text_buffer, &quot; S&quot;);&n;&t;&t;if ((c &gt;&gt; 1) &amp; 1)&n;&t;&t;&t;sprintf(text_buffer+2, &quot; TA&quot;);&n;&t;&t;else&n;&t;&t;&t;sprintf(text_buffer+2, &quot; --&quot;);&n;&t;&t;if ((c &gt;&gt; 7) &amp; 1)&n;&t;&t;&t;sprintf(text_buffer+5, &quot; TP&quot;);&n;&t;&t;else&n;&t;&t;&t;sprintf(text_buffer+5, &quot; --&quot;);&n;&t;&t;sprintf(text_buffer+8, &quot; %2d&bslash;n&quot;, (c &gt;&gt; 2) &amp; 0x1f);&n;&t;&t;return copy_to_user(buffer+8, text_buffer, 12) ? -EFAULT: 20;&n;&t;}&n;*/
r_if
c_cond
(paren
(paren
id|c
op_rshift
l_int|4
)paren
op_amp
l_int|1
)paren
(brace
id|aci_rds_cmd
c_func
(paren
id|RDS_TEXT
comma
id|text_buffer
comma
l_int|65
)paren
suffix:semicolon
id|text_buffer
(braket
l_int|0
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|text_buffer
(braket
l_int|65
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|buffer
op_plus
l_int|8
comma
id|text_buffer
comma
l_int|66
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|66
op_plus
l_int|8
suffix:semicolon
)brace
r_else
(brace
id|put_user
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|buffer
op_plus
l_int|8
)paren
suffix:semicolon
r_return
l_int|9
suffix:semicolon
)brace
)brace
DECL|variable|rds_f_ops
r_static
r_struct
id|file_operations
id|rds_f_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|rds_f_read
comma
dot
id|open
op_assign
id|rds_f_open
comma
dot
id|release
op_assign
id|rds_f_release
)brace
suffix:semicolon
DECL|function|miropcm20_rds_init
r_static
r_int
id|__init
id|miropcm20_rds_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|devfs_register
c_func
(paren
l_int|NULL
comma
l_string|&quot;v4l/rds/radiotext&quot;
comma
id|DEVFS_FL_DEFAULT
op_or
id|DEVFS_FL_AUTO_DEVNUM
comma
l_int|0
comma
l_int|0
comma
id|S_IRUGO
op_or
id|S_IFCHR
comma
op_amp
id|rds_f_ops
comma
l_int|NULL
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;miropcm20-rds: userinterface driver loaded.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|miropcm20_rds_cleanup
r_static
r_void
id|__exit
id|miropcm20_rds_cleanup
c_func
(paren
r_void
)paren
(brace
id|devfs_remove
c_func
(paren
l_string|&quot;v4l/rds/radiotext&quot;
)paren
suffix:semicolon
)brace
DECL|variable|miropcm20_rds_init
id|module_init
c_func
(paren
id|miropcm20_rds_init
)paren
suffix:semicolon
DECL|variable|miropcm20_rds_cleanup
id|module_exit
c_func
(paren
id|miropcm20_rds_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
