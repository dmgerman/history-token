multiline_comment|/* -*- linux-c -*-&n; *&t;&t;sysctl_net_802.c: sysctl interface to net 802 subsystem.&n; *&n; *&t;&t;Begun April 1, 1996, Mike Shaver.&n; *&t;&t;Added /proc/sys/net/802 directory entry (empty =) ). [MS]&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_TR
r_extern
r_int
id|sysctl_tr_rif_timeout
suffix:semicolon
macro_line|#endif
DECL|variable|tr_table
r_struct
id|ctl_table
id|tr_table
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_TR
(brace
dot
id|ctl_name
op_assign
id|NET_TR_RIF_TIMEOUT
comma
dot
id|procname
op_assign
l_string|&quot;rif_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tr_rif_timeout
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
id|proc_dointvec
)brace
comma
macro_line|#endif /* CONFIG_TR */
(brace
l_int|0
)brace
comma
)brace
suffix:semicolon
eof
