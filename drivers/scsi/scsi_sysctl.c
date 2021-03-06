multiline_comment|/*&n; * Copyright (C) 2003 Christoph Hellwig.&n; *&t;Released under GPL v2.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &quot;scsi_logging.h&quot;
DECL|variable|scsi_table
r_static
id|ctl_table
id|scsi_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|DEV_SCSI_LOGGING_LEVEL
comma
dot
id|procname
op_assign
l_string|&quot;logging_level&quot;
comma
dot
id|data
op_assign
op_amp
id|scsi_logging_level
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
id|scsi_logging_level
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
)brace
)brace
suffix:semicolon
DECL|variable|scsi_dir_table
r_static
id|ctl_table
id|scsi_dir_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|DEV_SCSI
comma
dot
id|procname
op_assign
l_string|&quot;scsi&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|scsi_table
)brace
comma
(brace
)brace
)brace
suffix:semicolon
DECL|variable|scsi_root_table
r_static
id|ctl_table
id|scsi_root_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|CTL_DEV
comma
dot
id|procname
op_assign
l_string|&quot;dev&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|scsi_dir_table
)brace
comma
(brace
)brace
)brace
suffix:semicolon
DECL|variable|scsi_table_header
r_static
r_struct
id|ctl_table_header
op_star
id|scsi_table_header
suffix:semicolon
DECL|function|scsi_init_sysctl
r_int
id|__init
id|scsi_init_sysctl
c_func
(paren
r_void
)paren
(brace
id|scsi_table_header
op_assign
id|register_sysctl_table
c_func
(paren
id|scsi_root_table
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scsi_table_header
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scsi_exit_sysctl
r_void
id|scsi_exit_sysctl
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|scsi_table_header
)paren
suffix:semicolon
)brace
eof
