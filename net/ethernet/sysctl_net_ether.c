multiline_comment|/* -*- linux-c -*-&n; * sysctl_net_ether.c: sysctl interface to net Ethernet subsystem.&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/ether directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
DECL|variable|ether_table
id|ctl_table
id|ether_table
(braket
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
eof
