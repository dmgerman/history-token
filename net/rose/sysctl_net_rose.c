multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright (C) 1996 Mike Shaver (shaver@zeroknowledge.com)&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;net/rose.h&gt;
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
DECL|variable|min_idle
r_static
r_int
id|min_idle
(braket
)braket
op_assign
(brace
l_int|0
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|max_idle
r_static
r_int
id|max_idle
(braket
)braket
op_assign
(brace
l_int|65535
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|min_route
DECL|variable|max_route
r_static
r_int
id|min_route
(braket
)braket
op_assign
(brace
l_int|0
)brace
comma
id|max_route
(braket
)braket
op_assign
(brace
l_int|1
)brace
suffix:semicolon
DECL|variable|min_ftimer
r_static
r_int
id|min_ftimer
(braket
)braket
op_assign
(brace
l_int|60
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|max_ftimer
r_static
r_int
id|max_ftimer
(braket
)braket
op_assign
(brace
l_int|600
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|min_maxvcs
DECL|variable|max_maxvcs
r_static
r_int
id|min_maxvcs
(braket
)braket
op_assign
(brace
l_int|1
)brace
comma
id|max_maxvcs
(braket
)braket
op_assign
(brace
l_int|254
)brace
suffix:semicolon
DECL|variable|min_window
DECL|variable|max_window
r_static
r_int
id|min_window
(braket
)braket
op_assign
(brace
l_int|1
)brace
comma
id|max_window
(braket
)braket
op_assign
(brace
l_int|7
)brace
suffix:semicolon
DECL|variable|rose_table_header
r_static
r_struct
id|ctl_table_header
op_star
id|rose_table_header
suffix:semicolon
DECL|variable|rose_table
r_static
id|ctl_table
id|rose_table
(braket
)braket
op_assign
(brace
(brace
id|NET_ROSE_RESTART_REQUEST_TIMEOUT
comma
l_string|&quot;restart_request_timeout&quot;
comma
op_amp
id|sysctl_rose_restart_request_timeout
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_timer
comma
op_amp
id|max_timer
)brace
comma
(brace
id|NET_ROSE_CALL_REQUEST_TIMEOUT
comma
l_string|&quot;call_request_timeout&quot;
comma
op_amp
id|sysctl_rose_call_request_timeout
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_timer
comma
op_amp
id|max_timer
)brace
comma
(brace
id|NET_ROSE_RESET_REQUEST_TIMEOUT
comma
l_string|&quot;reset_request_timeout&quot;
comma
op_amp
id|sysctl_rose_reset_request_timeout
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_timer
comma
op_amp
id|max_timer
)brace
comma
(brace
id|NET_ROSE_CLEAR_REQUEST_TIMEOUT
comma
l_string|&quot;clear_request_timeout&quot;
comma
op_amp
id|sysctl_rose_clear_request_timeout
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_timer
comma
op_amp
id|max_timer
)brace
comma
(brace
id|NET_ROSE_NO_ACTIVITY_TIMEOUT
comma
l_string|&quot;no_activity_timeout&quot;
comma
op_amp
id|sysctl_rose_no_activity_timeout
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_idle
comma
op_amp
id|max_idle
)brace
comma
(brace
id|NET_ROSE_ACK_HOLD_BACK_TIMEOUT
comma
l_string|&quot;acknowledge_hold_back_timeout&quot;
comma
op_amp
id|sysctl_rose_ack_hold_back_timeout
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_timer
comma
op_amp
id|max_timer
)brace
comma
(brace
id|NET_ROSE_ROUTING_CONTROL
comma
l_string|&quot;routing_control&quot;
comma
op_amp
id|sysctl_rose_routing_control
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_route
comma
op_amp
id|max_route
)brace
comma
(brace
id|NET_ROSE_LINK_FAIL_TIMEOUT
comma
l_string|&quot;link_fail_timeout&quot;
comma
op_amp
id|sysctl_rose_link_fail_timeout
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_ftimer
comma
op_amp
id|max_ftimer
)brace
comma
(brace
id|NET_ROSE_MAX_VCS
comma
l_string|&quot;maximum_virtual_circuits&quot;
comma
op_amp
id|sysctl_rose_maximum_vcs
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_maxvcs
comma
op_amp
id|max_maxvcs
)brace
comma
(brace
id|NET_ROSE_WINDOW_SIZE
comma
l_string|&quot;window_size&quot;
comma
op_amp
id|sysctl_rose_window_size
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|proc_dointvec_minmax
comma
op_amp
id|sysctl_intvec
comma
l_int|NULL
comma
op_amp
id|min_window
comma
op_amp
id|max_window
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|rose_dir_table
r_static
id|ctl_table
id|rose_dir_table
(braket
)braket
op_assign
(brace
(brace
id|NET_ROSE
comma
l_string|&quot;rose&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|rose_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|rose_root_table
r_static
id|ctl_table
id|rose_root_table
(braket
)braket
op_assign
(brace
(brace
id|CTL_NET
comma
l_string|&quot;net&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|rose_dir_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|rose_register_sysctl
r_void
id|__init
id|rose_register_sysctl
c_func
(paren
r_void
)paren
(brace
id|rose_table_header
op_assign
id|register_sysctl_table
c_func
(paren
id|rose_root_table
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|rose_unregister_sysctl
r_void
id|rose_unregister_sysctl
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|rose_table_header
)paren
suffix:semicolon
)brace
eof
