multiline_comment|/**&n; * @file oprofile_files.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &quot;event_buffer.h&quot;
macro_line|#include &quot;oprofile_stats.h&quot;
macro_line|#include &quot;oprof.h&quot;
DECL|variable|fs_buffer_size
r_int
r_int
id|fs_buffer_size
op_assign
l_int|131072
suffix:semicolon
DECL|variable|fs_cpu_buffer_size
r_int
r_int
id|fs_cpu_buffer_size
op_assign
l_int|8192
suffix:semicolon
DECL|variable|fs_buffer_watershed
r_int
r_int
id|fs_buffer_watershed
op_assign
l_int|32768
suffix:semicolon
multiline_comment|/* FIXME: tune */
DECL|function|depth_read
r_static
id|ssize_t
id|depth_read
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
r_return
id|oprofilefs_ulong_to_user
c_func
(paren
id|backtrace_depth
comma
id|buf
comma
id|count
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|function|depth_write
r_static
id|ssize_t
id|depth_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
r_const
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
r_int
r_int
id|val
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_star
id|offset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|retval
op_assign
id|oprofilefs_ulong_from_user
c_func
(paren
op_amp
id|val
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|retval
op_assign
id|oprofile_set_backtrace
c_func
(paren
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|depth_fops
r_static
r_struct
id|file_operations
id|depth_fops
op_assign
(brace
dot
id|read
op_assign
id|depth_read
comma
dot
id|write
op_assign
id|depth_write
)brace
suffix:semicolon
DECL|function|pointer_size_read
r_static
id|ssize_t
id|pointer_size_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
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
r_return
id|oprofilefs_ulong_to_user
c_func
(paren
r_sizeof
(paren
r_void
op_star
)paren
comma
id|buf
comma
id|count
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|variable|pointer_size_fops
r_static
r_struct
id|file_operations
id|pointer_size_fops
op_assign
(brace
dot
id|read
op_assign
id|pointer_size_read
comma
)brace
suffix:semicolon
DECL|function|cpu_type_read
r_static
id|ssize_t
id|cpu_type_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
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
r_return
id|oprofilefs_str_to_user
c_func
(paren
id|oprofile_ops.cpu_type
comma
id|buf
comma
id|count
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|variable|cpu_type_fops
r_static
r_struct
id|file_operations
id|cpu_type_fops
op_assign
(brace
dot
id|read
op_assign
id|cpu_type_read
comma
)brace
suffix:semicolon
DECL|function|enable_read
r_static
id|ssize_t
id|enable_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
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
r_return
id|oprofilefs_ulong_to_user
c_func
(paren
id|oprofile_started
comma
id|buf
comma
id|count
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|function|enable_write
r_static
id|ssize_t
id|enable_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
r_const
id|__user
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
r_int
r_int
id|val
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_star
id|offset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|retval
op_assign
id|oprofilefs_ulong_from_user
c_func
(paren
op_amp
id|val
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
id|retval
op_assign
id|oprofile_start
c_func
(paren
)paren
suffix:semicolon
r_else
id|oprofile_stop
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|enable_fops
r_static
r_struct
id|file_operations
id|enable_fops
op_assign
(brace
dot
id|read
op_assign
id|enable_read
comma
dot
id|write
op_assign
id|enable_write
comma
)brace
suffix:semicolon
DECL|function|dump_write
r_static
id|ssize_t
id|dump_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
r_const
id|__user
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
id|wake_up_buffer_waiter
c_func
(paren
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|dump_fops
r_static
r_struct
id|file_operations
id|dump_fops
op_assign
(brace
dot
id|write
op_assign
id|dump_write
comma
)brace
suffix:semicolon
DECL|function|oprofile_create_files
r_void
id|oprofile_create_files
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
)paren
(brace
id|oprofilefs_create_file
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;enable&quot;
comma
op_amp
id|enable_fops
)paren
suffix:semicolon
id|oprofilefs_create_file_perm
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;dump&quot;
comma
op_amp
id|dump_fops
comma
l_int|0666
)paren
suffix:semicolon
id|oprofilefs_create_file
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;buffer&quot;
comma
op_amp
id|event_buffer_fops
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;buffer_size&quot;
comma
op_amp
id|fs_buffer_size
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;buffer_watershed&quot;
comma
op_amp
id|fs_buffer_watershed
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;cpu_buffer_size&quot;
comma
op_amp
id|fs_cpu_buffer_size
)paren
suffix:semicolon
id|oprofilefs_create_file
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;cpu_type&quot;
comma
op_amp
id|cpu_type_fops
)paren
suffix:semicolon
id|oprofilefs_create_file
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;backtrace_depth&quot;
comma
op_amp
id|depth_fops
)paren
suffix:semicolon
id|oprofilefs_create_file
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;pointer_size&quot;
comma
op_amp
id|pointer_size_fops
)paren
suffix:semicolon
id|oprofile_create_stats_files
c_func
(paren
id|sb
comma
id|root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oprofile_ops.create_files
)paren
id|oprofile_ops
dot
id|create_files
c_func
(paren
id|sb
comma
id|root
)paren
suffix:semicolon
)brace
eof
