multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;INET protocol dispatch tables.&n; *&n; * Version:&t;$Id: protocol.c,v 1.14 2001/05/18 02:25:49 davem Exp $&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;: Ahah! udp icmp errors don&squot;t work because&n; *&t;&t;&t;&t;  udp_err is never called!&n; *&t;&t;Alan Cox&t;: Added new fields for init and ready for&n; *&t;&t;&t;&t;  proper fragmentation (_NO_ 4K limits!)&n; *&t;&t;Richard Colella&t;: Hang on hash collision&n; *&t;&t;Vince Laviano&t;: Modified inet_del_protocol() to correctly&n; *&t;&t;&t;&t;  maintain copy bit.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/ipip.h&gt;
macro_line|#include &lt;linux/igmp.h&gt;
DECL|variable|inet_protos
r_struct
id|net_protocol
op_star
id|inet_protos
(braket
id|MAX_INET_PROTOS
)braket
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|inet_proto_lock
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Add a protocol handler to the hash tables&n; */
DECL|function|inet_add_protocol
r_int
id|inet_add_protocol
c_func
(paren
r_struct
id|net_protocol
op_star
id|prot
comma
r_int
r_char
id|protocol
)paren
(brace
r_int
id|hash
comma
id|ret
suffix:semicolon
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
id|spin_lock_bh
c_func
(paren
op_amp
id|inet_proto_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet_protos
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
id|inet_protos
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
id|spin_unlock_bh
c_func
(paren
op_amp
id|inet_proto_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Remove a protocol from the hash tables.&n; */
DECL|function|inet_del_protocol
r_int
id|inet_del_protocol
c_func
(paren
r_struct
id|net_protocol
op_star
id|prot
comma
r_int
r_char
id|protocol
)paren
(brace
r_int
id|hash
comma
id|ret
suffix:semicolon
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
id|spin_lock_bh
c_func
(paren
op_amp
id|inet_proto_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet_protos
(braket
id|hash
)braket
op_eq
id|prot
)paren
(brace
id|inet_protos
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
r_else
(brace
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|inet_proto_lock
)paren
suffix:semicolon
id|synchronize_net
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|inet_add_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|inet_add_protocol
)paren
suffix:semicolon
DECL|variable|inet_del_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|inet_del_protocol
)paren
suffix:semicolon
eof
