multiline_comment|/* -*- linux-c -*-&n; *&t;&t;sysctl_net_802.c: sysctl interface to net 802 subsystem.&n; *&n; *&t;&t;Begun April 1, 1996, Mike Shaver.&n; *&t;&t;Added /proc/sys/net/802 directory entry (empty =) ). [MS]&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/config.h&gt;
DECL|variable|e802_table
id|ctl_table
id|e802_table
(braket
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_TR
r_extern
r_int
id|sysctl_tr_rif_timeout
suffix:semicolon
DECL|variable|tr_table
id|ctl_table
id|tr_table
(braket
)braket
op_assign
(brace
(brace
id|NET_TR_RIF_TIMEOUT
comma
l_string|&quot;rif_timeout&quot;
comma
op_amp
id|sysctl_tr_rif_timeout
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
id|proc_dointvec
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#endif
eof
