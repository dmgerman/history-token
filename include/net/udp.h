multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the UDP module.&n; *&n; * Version:&t;@(#)udp.h&t;1.0.2&t;05/07/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;: Turned on udp checksums. I don&squot;t want to&n; *&t;&t;&t;&t;  chase &squot;memory corruption&squot; bugs that aren&squot;t!&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _UDP_H
DECL|macro|_UDP_H
mdefine_line|#define _UDP_H
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;net/sock.h&gt;
DECL|macro|UDP_HTABLE_SIZE
mdefine_line|#define UDP_HTABLE_SIZE&t;&t;128
multiline_comment|/* udp.c: This needs to be shared by v4 and v6 because the lookup&n; *        and hashing code needs to work with different AF&squot;s yet&n; *        the port space is shared.&n; */
r_extern
r_struct
id|sock
op_star
id|udp_hash
(braket
id|UDP_HTABLE_SIZE
)braket
suffix:semicolon
r_extern
id|rwlock_t
id|udp_hash_lock
suffix:semicolon
r_extern
r_int
id|udp_port_rover
suffix:semicolon
DECL|function|udp_lport_inuse
r_static
r_inline
r_int
id|udp_lport_inuse
c_func
(paren
id|u16
id|num
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|udp_hash
(braket
id|num
op_amp
(paren
id|UDP_HTABLE_SIZE
op_minus
l_int|1
)paren
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|sk
op_ne
l_int|NULL
suffix:semicolon
id|sk
op_assign
id|sk-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;num
op_eq
id|num
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Note: this must match &squot;valbool&squot; in sock_setsockopt */
DECL|macro|UDP_CSUM_NOXMIT
mdefine_line|#define UDP_CSUM_NOXMIT&t;&t;1
multiline_comment|/* Used by SunRPC/xprt layer. */
DECL|macro|UDP_CSUM_NORCV
mdefine_line|#define UDP_CSUM_NORCV&t;&t;2
multiline_comment|/* Default, as per the RFC, is to always do csums. */
DECL|macro|UDP_CSUM_DEFAULT
mdefine_line|#define UDP_CSUM_DEFAULT&t;0
r_extern
r_struct
id|proto
id|udp_prot
suffix:semicolon
r_extern
r_void
id|udp_err
c_func
(paren
r_struct
id|sk_buff
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|udp_connect
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sockaddr
op_star
id|usin
comma
r_int
id|addr_len
)paren
suffix:semicolon
r_extern
r_int
id|udp_sendmsg
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|udp_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|udp_ioctl
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|udp_disconnect
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_struct
id|udp_mib
id|udp_statistics
(braket
id|NR_CPUS
op_star
l_int|2
)braket
suffix:semicolon
DECL|macro|UDP_INC_STATS
mdefine_line|#define UDP_INC_STATS(field)&t;&t;SNMP_INC_STATS(udp_statistics, field)
DECL|macro|UDP_INC_STATS_BH
mdefine_line|#define UDP_INC_STATS_BH(field)&t;&t;SNMP_INC_STATS_BH(udp_statistics, field)
DECL|macro|UDP_INC_STATS_USER
mdefine_line|#define UDP_INC_STATS_USER(field) &t;SNMP_INC_STATS_USER(udp_statistics, field)
DECL|macro|udp_sock
mdefine_line|#define udp_sock inet_sock
macro_line|#endif&t;/* _UDP_H */
eof
