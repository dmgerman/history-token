multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;INET protocol dispatch tables.&n; *&n; * Version:&t;$Id: protocol.c,v 1.12 2000/10/03 07:29:00 anton Exp $&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;: Ahah! udp icmp errors don&squot;t work because&n; *&t;&t;&t;&t;  udp_err is never called!&n; *&t;&t;Alan Cox&t;: Added new fields for init and ready for&n; *&t;&t;&t;&t;  proper fragmentation (_NO_ 4K limits!)&n; *&t;&t;Richard Colella&t;: Hang on hash collision&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
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
macro_line|#include &lt;linux/brlock.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/ipip.h&gt;
macro_line|#include &lt;linux/igmp.h&gt;
DECL|macro|IPPROTO_PREVIOUS
mdefine_line|#define IPPROTO_PREVIOUS NULL
macro_line|#ifdef CONFIG_IP_MULTICAST
DECL|variable|igmp_protocol
r_static
r_struct
id|inet_protocol
id|igmp_protocol
op_assign
(brace
id|igmp_rcv
comma
multiline_comment|/* IGMP handler&t;&t;*/
l_int|NULL
comma
multiline_comment|/* IGMP error control&t;*/
id|IPPROTO_PREVIOUS
comma
multiline_comment|/* next&t;&t;&t;*/
id|IPPROTO_IGMP
comma
multiline_comment|/* protocol ID&t;&t;*/
l_int|0
comma
multiline_comment|/* copy&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* data&t;&t;&t;*/
l_string|&quot;IGMP&quot;
multiline_comment|/* name&t;&t;&t;*/
)brace
suffix:semicolon
DECL|macro|IPPROTO_PREVIOUS
macro_line|#undef  IPPROTO_PREVIOUS
DECL|macro|IPPROTO_PREVIOUS
mdefine_line|#define IPPROTO_PREVIOUS &amp;igmp_protocol
macro_line|#endif
DECL|variable|tcp_protocol
r_static
r_struct
id|inet_protocol
id|tcp_protocol
op_assign
(brace
id|tcp_v4_rcv
comma
multiline_comment|/* TCP handler&t;&t;*/
id|tcp_v4_err
comma
multiline_comment|/* TCP error control&t;*/
id|IPPROTO_PREVIOUS
comma
id|IPPROTO_TCP
comma
multiline_comment|/* protocol ID&t;&t;*/
l_int|0
comma
multiline_comment|/* copy&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* data&t;&t;&t;*/
l_string|&quot;TCP&quot;
multiline_comment|/* name&t;&t;&t;*/
)brace
suffix:semicolon
DECL|macro|IPPROTO_PREVIOUS
macro_line|#undef  IPPROTO_PREVIOUS
DECL|macro|IPPROTO_PREVIOUS
mdefine_line|#define IPPROTO_PREVIOUS &amp;tcp_protocol
DECL|variable|udp_protocol
r_static
r_struct
id|inet_protocol
id|udp_protocol
op_assign
(brace
id|udp_rcv
comma
multiline_comment|/* UDP handler&t;&t;*/
id|udp_err
comma
multiline_comment|/* UDP error control&t;*/
id|IPPROTO_PREVIOUS
comma
multiline_comment|/* next&t;&t;&t;*/
id|IPPROTO_UDP
comma
multiline_comment|/* protocol ID&t;&t;*/
l_int|0
comma
multiline_comment|/* copy&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* data&t;&t;&t;*/
l_string|&quot;UDP&quot;
multiline_comment|/* name&t;&t;&t;*/
)brace
suffix:semicolon
DECL|macro|IPPROTO_PREVIOUS
macro_line|#undef  IPPROTO_PREVIOUS
DECL|macro|IPPROTO_PREVIOUS
mdefine_line|#define IPPROTO_PREVIOUS &amp;udp_protocol
DECL|variable|icmp_protocol
r_static
r_struct
id|inet_protocol
id|icmp_protocol
op_assign
(brace
id|icmp_rcv
comma
multiline_comment|/* ICMP handler&t;&t;*/
l_int|NULL
comma
multiline_comment|/* ICMP error control&t;*/
id|IPPROTO_PREVIOUS
comma
multiline_comment|/* next&t;&t;&t;*/
id|IPPROTO_ICMP
comma
multiline_comment|/* protocol ID&t;&t;*/
l_int|0
comma
multiline_comment|/* copy&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* data&t;&t;&t;*/
l_string|&quot;ICMP&quot;
multiline_comment|/* name&t;&t;&t;*/
)brace
suffix:semicolon
DECL|macro|IPPROTO_PREVIOUS
macro_line|#undef  IPPROTO_PREVIOUS
DECL|macro|IPPROTO_PREVIOUS
mdefine_line|#define IPPROTO_PREVIOUS &amp;icmp_protocol
DECL|variable|inet_protocol_base
r_struct
id|inet_protocol
op_star
id|inet_protocol_base
op_assign
id|IPPROTO_PREVIOUS
suffix:semicolon
DECL|variable|inet_protos
r_struct
id|inet_protocol
op_star
id|inet_protos
(braket
id|MAX_INET_PROTOS
)braket
suffix:semicolon
multiline_comment|/*&n; *&t;Add a protocol handler to the hash tables&n; */
DECL|function|inet_add_protocol
r_void
id|inet_add_protocol
c_func
(paren
r_struct
id|inet_protocol
op_star
id|prot
)paren
(brace
r_int
r_char
id|hash
suffix:semicolon
r_struct
id|inet_protocol
op_star
id|p2
suffix:semicolon
id|hash
op_assign
id|prot-&gt;protocol
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
id|prot
op_member_access_from_pointer
id|next
op_assign
id|inet_protos
(braket
id|hash
)braket
suffix:semicolon
id|inet_protos
(braket
id|hash
)braket
op_assign
id|prot
suffix:semicolon
id|prot-&gt;copy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Set the copy bit if we need to. &n;&t; */
id|p2
op_assign
(paren
r_struct
id|inet_protocol
op_star
)paren
id|prot-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|p2
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|p2-&gt;protocol
op_eq
id|prot-&gt;protocol
)paren
(brace
id|prot-&gt;copy
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|p2
op_assign
(paren
r_struct
id|inet_protocol
op_star
)paren
id|p2-&gt;next
suffix:semicolon
)brace
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Remove a protocol from the hash tables.&n; */
DECL|function|inet_del_protocol
r_int
id|inet_del_protocol
c_func
(paren
r_struct
id|inet_protocol
op_star
id|prot
)paren
(brace
r_struct
id|inet_protocol
op_star
id|p
suffix:semicolon
r_struct
id|inet_protocol
op_star
id|lp
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|hash
suffix:semicolon
id|hash
op_assign
id|prot-&gt;protocol
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
id|prot
op_eq
id|inet_protos
(braket
id|hash
)braket
)paren
(brace
id|inet_protos
(braket
id|hash
)braket
op_assign
(paren
r_struct
id|inet_protocol
op_star
)paren
id|inet_protos
(braket
id|hash
)braket
op_member_access_from_pointer
id|next
suffix:semicolon
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|p
op_assign
(paren
r_struct
id|inet_protocol
op_star
)paren
id|inet_protos
(braket
id|hash
)braket
suffix:semicolon
r_while
c_loop
(paren
id|p
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * We have to worry if the protocol being deleted is&n;&t;&t; * the last one on the list, then we may need to reset&n;&t;&t; * someone&squot;s copied bit.&n;&t;&t; */
r_if
c_cond
(paren
id|p-&gt;next
op_ne
l_int|NULL
op_logical_and
id|p-&gt;next
op_eq
id|prot
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * if we are the last one with this protocol and&n;&t;&t;&t; * there is a previous one, reset its copy bit.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|p-&gt;copy
op_eq
l_int|0
op_logical_and
id|lp
op_ne
l_int|NULL
)paren
id|lp-&gt;copy
op_assign
l_int|0
suffix:semicolon
id|p-&gt;next
op_assign
id|prot-&gt;next
suffix:semicolon
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;next
op_ne
l_int|NULL
op_logical_and
id|p-&gt;next-&gt;protocol
op_eq
id|prot-&gt;protocol
)paren
id|lp
op_assign
id|p
suffix:semicolon
id|p
op_assign
(paren
r_struct
id|inet_protocol
op_star
)paren
id|p-&gt;next
suffix:semicolon
)brace
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
eof
