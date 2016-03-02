multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;PF_INET6 protocol dispatch tables.&n; *&n; * Version:&t;$Id: protocol.c,v 1.10 2001/05/18 02:25:49 davem Exp $&n; *&n; * Authors:&t;Pedro Roque&t;&lt;roque@di.fc.ul.pt&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; *      Changes:&n; *&n; *      Vince Laviano (vince@cs.stanford.edu)       16 May 2001&n; *      - Removed unused variable &squot;inet6_protocol_base&squot;&n; *      - Modified inet6_del_protocol() to correctly maintain copy bit.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/brlock.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
DECL|variable|inet6_protos
r_struct
id|inet6_protocol
op_star
id|inet6_protos
(braket
id|MAX_INET_PROTOS
)braket
suffix:semicolon
DECL|function|inet6_add_protocol
r_int
id|inet6_add_protocol
c_func
(paren
r_struct
id|inet6_protocol
op_star
id|prot
comma
r_int
r_char
id|protocol
)paren
(brace
r_int
id|ret
comma
id|hash
op_assign
id|protocol
op_amp
(paren
id|MAX_INET_PROTOS
op_minus
l_int|1
)paren
suffix:semicolon
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet6_protos
(braket
id|hash
)braket
)paren
(brace
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|inet6_protos
(braket
id|hash
)braket
op_assign
id|prot
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Remove a protocol from the hash tables.&n; */
DECL|function|inet6_del_protocol
r_int
id|inet6_del_protocol
c_func
(paren
r_struct
id|inet6_protocol
op_star
id|prot
comma
r_int
r_char
id|protocol
)paren
(brace
r_int
id|ret
comma
id|hash
op_assign
id|protocol
op_amp
(paren
id|MAX_INET_PROTOS
op_minus
l_int|1
)paren
suffix:semicolon
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet6_protos
(braket
id|hash
)braket
op_ne
id|prot
)paren
(brace
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|inet6_protos
(braket
id|hash
)braket
op_assign
l_int|NULL
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
