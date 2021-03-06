multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright (C) 1996 Mike Shaver (shaver@zeroknowledge.com)&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;net/netrom.h&gt;
multiline_comment|/*&n; *&t;Values taken from NET/ROM documentation.&n; */
DECL|variable|min_quality
DECL|variable|max_quality
r_static
r_int
id|min_quality
(braket
)braket
op_assign
(brace
l_int|0
)brace
comma
id|max_quality
(braket
)braket
op_assign
(brace
l_int|255
)brace
suffix:semicolon
DECL|variable|min_obs
DECL|variable|max_obs
r_static
r_int
id|min_obs
(braket
)braket
op_assign
(brace
l_int|0
)brace
comma
id|max_obs
(braket
)braket
op_assign
(brace
l_int|255
)brace
suffix:semicolon
DECL|variable|min_ttl
DECL|variable|max_ttl
r_static
r_int
id|min_ttl
(braket
)braket
op_assign
(brace
l_int|0
)brace
comma
id|max_ttl
(braket
)braket
op_assign
(brace
l_int|255
)brace
suffix:semicolon
DECL|variable|min_t1
r_static
r_int
id|min_t1
(braket
)braket
op_assign
(brace
l_int|5
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|max_t1
r_static
r_int
id|max_t1
(braket
)braket
op_assign
(brace
l_int|600
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|min_n2
DECL|variable|max_n2
r_static
r_int
id|min_n2
(braket
)braket
op_assign
(brace
l_int|2
)brace
comma
id|max_n2
(braket
)braket
op_assign
(brace
l_int|127
)brace
suffix:semicolon
DECL|variable|min_t2
r_static
r_int
id|min_t2
(braket
)braket
op_assign
(brace
l_int|1
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|max_t2
r_static
r_int
id|max_t2
(braket
)braket
op_assign
(brace
l_int|60
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|min_t4
r_static
r_int
id|min_t4
(braket
)braket
op_assign
(brace
l_int|1
op_star
id|HZ
)brace
suffix:semicolon
DECL|variable|max_t4
r_static
r_int
id|max_t4
(braket
)braket
op_assign
(brace
l_int|1000
op_star
id|HZ
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
l_int|127
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
DECL|variable|min_fails
DECL|variable|max_fails
r_static
r_int
id|min_fails
(braket
)braket
op_assign
(brace
l_int|1
)brace
comma
id|max_fails
(braket
)braket
op_assign
(brace
l_int|10
)brace
suffix:semicolon
DECL|variable|nr_table_header
r_static
r_struct
id|ctl_table_header
op_star
id|nr_table_header
suffix:semicolon
DECL|variable|nr_table
r_static
id|ctl_table
id|nr_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM_DEFAULT_PATH_QUALITY
comma
dot
id|procname
op_assign
l_string|&quot;default_path_quality&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_netrom_default_path_quality
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
id|min_quality
comma
dot
id|extra2
op_assign
op_amp
id|max_quality
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM_OBSOLESCENCE_COUNT_INITIALISER
comma
dot
id|procname
op_assign
l_string|&quot;obsolescence_count_initialiser&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_netrom_obsolescence_count_initialiser
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
id|min_obs
comma
dot
id|extra2
op_assign
op_amp
id|max_obs
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM_NETWORK_TTL_INITIALISER
comma
dot
id|procname
op_assign
l_string|&quot;network_ttl_initialiser&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_netrom_network_ttl_initialiser
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
id|min_ttl
comma
dot
id|extra2
op_assign
op_amp
id|max_ttl
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM_TRANSPORT_TIMEOUT
comma
dot
id|procname
op_assign
l_string|&quot;transport_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_netrom_transport_timeout
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
id|min_t1
comma
dot
id|extra2
op_assign
op_amp
id|max_t1
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM_TRANSPORT_MAXIMUM_TRIES
comma
dot
id|procname
op_assign
l_string|&quot;transport_maximum_tries&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_netrom_transport_maximum_tries
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
id|min_n2
comma
dot
id|extra2
op_assign
op_amp
id|max_n2
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM_TRANSPORT_ACKNOWLEDGE_DELAY
comma
dot
id|procname
op_assign
l_string|&quot;transport_acknowledge_delay&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_netrom_transport_acknowledge_delay
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
id|min_t2
comma
dot
id|extra2
op_assign
op_amp
id|max_t2
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM_TRANSPORT_BUSY_DELAY
comma
dot
id|procname
op_assign
l_string|&quot;transport_busy_delay&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_netrom_transport_busy_delay
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
id|min_t4
comma
dot
id|extra2
op_assign
op_amp
id|max_t4
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM_TRANSPORT_REQUESTED_WINDOW_SIZE
comma
dot
id|procname
op_assign
l_string|&quot;transport_requested_window_size&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_netrom_transport_requested_window_size
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
id|min_window
comma
dot
id|extra2
op_assign
op_amp
id|max_window
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM_TRANSPORT_NO_ACTIVITY_TIMEOUT
comma
dot
id|procname
op_assign
l_string|&quot;transport_no_activity_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_netrom_transport_no_activity_timeout
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
id|min_idle
comma
dot
id|extra2
op_assign
op_amp
id|max_idle
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM_ROUTING_CONTROL
comma
dot
id|procname
op_assign
l_string|&quot;routing_control&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_netrom_routing_control
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
id|min_route
comma
dot
id|extra2
op_assign
op_amp
id|max_route
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM_LINK_FAILS_COUNT
comma
dot
id|procname
op_assign
l_string|&quot;link_fails_count&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_netrom_link_fails_count
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
id|min_fails
comma
dot
id|extra2
op_assign
op_amp
id|max_fails
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|nr_dir_table
r_static
id|ctl_table
id|nr_dir_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_NETROM
comma
dot
id|procname
op_assign
l_string|&quot;netrom&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|nr_table
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|nr_root_table
r_static
id|ctl_table
id|nr_root_table
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
id|nr_dir_table
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|nr_register_sysctl
r_void
id|__init
id|nr_register_sysctl
c_func
(paren
r_void
)paren
(brace
id|nr_table_header
op_assign
id|register_sysctl_table
c_func
(paren
id|nr_root_table
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|nr_unregister_sysctl
r_void
id|nr_unregister_sysctl
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|nr_table_header
)paren
suffix:semicolon
)brace
eof
