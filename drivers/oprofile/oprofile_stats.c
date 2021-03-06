multiline_comment|/**&n; * @file oprofile_stats.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &quot;oprofile_stats.h&quot;
macro_line|#include &quot;cpu_buffer.h&quot;
DECL|variable|oprofile_stats
r_struct
id|oprofile_stat_struct
id|oprofile_stats
suffix:semicolon
DECL|function|oprofile_reset_stats
r_void
id|oprofile_reset_stats
c_func
(paren
r_void
)paren
(brace
r_struct
id|oprofile_cpu_buffer
op_star
id|cpu_buf
suffix:semicolon
r_int
id|i
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|i
)paren
(brace
id|cpu_buf
op_assign
op_amp
id|cpu_buffer
(braket
id|i
)braket
suffix:semicolon
id|cpu_buf-&gt;sample_received
op_assign
l_int|0
suffix:semicolon
id|cpu_buf-&gt;sample_lost_overflow
op_assign
l_int|0
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|oprofile_stats.sample_lost_no_mm
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|oprofile_stats.sample_lost_no_mapping
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|oprofile_stats.event_lost_overflow
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|oprofile_create_stats_files
r_void
id|oprofile_create_stats_files
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
r_struct
id|oprofile_cpu_buffer
op_star
id|cpu_buf
suffix:semicolon
r_struct
id|dentry
op_star
id|cpudir
suffix:semicolon
r_struct
id|dentry
op_star
id|dir
suffix:semicolon
r_char
id|buf
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dir
op_assign
id|oprofilefs_mkdir
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;stats&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|i
)paren
(brace
id|cpu_buf
op_assign
op_amp
id|cpu_buffer
(braket
id|i
)braket
suffix:semicolon
id|snprintf
c_func
(paren
id|buf
comma
l_int|10
comma
l_string|&quot;cpu%d&quot;
comma
id|i
)paren
suffix:semicolon
id|cpudir
op_assign
id|oprofilefs_mkdir
c_func
(paren
id|sb
comma
id|dir
comma
id|buf
)paren
suffix:semicolon
multiline_comment|/* Strictly speaking access to these ulongs is racy,&n;&t;&t; * but we can&squot;t simply lock them, and they are&n;&t;&t; * informational only.&n;&t;&t; */
id|oprofilefs_create_ro_ulong
c_func
(paren
id|sb
comma
id|cpudir
comma
l_string|&quot;sample_received&quot;
comma
op_amp
id|cpu_buf-&gt;sample_received
)paren
suffix:semicolon
id|oprofilefs_create_ro_ulong
c_func
(paren
id|sb
comma
id|cpudir
comma
l_string|&quot;sample_lost_overflow&quot;
comma
op_amp
id|cpu_buf-&gt;sample_lost_overflow
)paren
suffix:semicolon
id|oprofilefs_create_ro_ulong
c_func
(paren
id|sb
comma
id|cpudir
comma
l_string|&quot;backtrace_aborted&quot;
comma
op_amp
id|cpu_buf-&gt;backtrace_aborted
)paren
suffix:semicolon
)brace
id|oprofilefs_create_ro_atomic
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;sample_lost_no_mm&quot;
comma
op_amp
id|oprofile_stats.sample_lost_no_mm
)paren
suffix:semicolon
id|oprofilefs_create_ro_atomic
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;sample_lost_no_mapping&quot;
comma
op_amp
id|oprofile_stats.sample_lost_no_mapping
)paren
suffix:semicolon
id|oprofilefs_create_ro_atomic
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;event_lost_overflow&quot;
comma
op_amp
id|oprofile_stats.event_lost_overflow
)paren
suffix:semicolon
id|oprofilefs_create_ro_atomic
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;bt_lost_no_mapping&quot;
comma
op_amp
id|oprofile_stats.bt_lost_no_mapping
)paren
suffix:semicolon
)brace
eof
