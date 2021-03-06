multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_x25.c: sysctl interface to net X.25 subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/x25 directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/x25.h&gt;
DECL|variable|min_timer
r_static
r_int
id|min_timer
(braket
)braket
op_assign
(brace
l_int|1
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|max_timer
r_static
r_int
id|max_timer
(braket
)braket
op_assign
(brace
l_int|300
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|x25_table_header
r_static
r_struct
id|ctl_table_header
op_star
id|x25_table_header
suffix:semicolon
DECL|variable|x25_table
r_static
r_struct
id|ctl_table
id|x25_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_X25_RESTART_REQUEST_TIMEOUT
comma
dot
id|procname
op_assign
l_string|&quot;restart_request_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_x25_restart_request_timeout
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
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
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_timer
comma
dot
id|extra2
op_assign
op_amp
id|max_timer
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_X25_CALL_REQUEST_TIMEOUT
comma
dot
id|procname
op_assign
l_string|&quot;call_request_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_x25_call_request_timeout
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
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
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_timer
comma
dot
id|extra2
op_assign
op_amp
id|max_timer
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_X25_RESET_REQUEST_TIMEOUT
comma
dot
id|procname
op_assign
l_string|&quot;reset_request_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_x25_reset_request_timeout
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
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
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_timer
comma
dot
id|extra2
op_assign
op_amp
id|max_timer
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_X25_CLEAR_REQUEST_TIMEOUT
comma
dot
id|procname
op_assign
l_string|&quot;clear_request_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_x25_clear_request_timeout
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
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
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_timer
comma
dot
id|extra2
op_assign
op_amp
id|max_timer
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_X25_ACK_HOLD_BACK_TIMEOUT
comma
dot
id|procname
op_assign
l_string|&quot;acknowledgement_hold_back_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_x25_ack_holdback_timeout
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
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
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
op_amp
id|min_timer
comma
dot
id|extra2
op_assign
op_amp
id|max_timer
comma
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|x25_dir_table
r_static
r_struct
id|ctl_table
id|x25_dir_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_X25
comma
dot
id|procname
op_assign
l_string|&quot;x25&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|x25_table
comma
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|x25_root_table
r_static
r_struct
id|ctl_table
id|x25_root_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|CTL_NET
comma
dot
id|procname
op_assign
l_string|&quot;net&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|x25_dir_table
comma
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|x25_register_sysctl
r_void
id|__init
id|x25_register_sysctl
c_func
(paren
r_void
)paren
(brace
id|x25_table_header
op_assign
id|register_sysctl_table
c_func
(paren
id|x25_root_table
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|x25_unregister_sysctl
r_void
id|x25_unregister_sysctl
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|x25_table_header
)paren
suffix:semicolon
)brace
eof
