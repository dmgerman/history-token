multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the ICMP module.&n; *&n; * Version:&t;@(#)icmp.h&t;1.0.4&t;05/13/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ICMP_H
DECL|macro|_ICMP_H
mdefine_line|#define&t;_ICMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
DECL|struct|icmp_err
r_struct
id|icmp_err
(brace
DECL|member|errno
r_int
id|errno
suffix:semicolon
DECL|member|fatal
r_int
id|fatal
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|icmp_err
id|icmp_err_convert
(braket
)braket
suffix:semicolon
id|DECLARE_SNMP_STAT
c_func
(paren
r_struct
id|icmp_mib
comma
id|icmp_statistics
)paren
suffix:semicolon
DECL|macro|ICMP_INC_STATS
mdefine_line|#define ICMP_INC_STATS(field)&t;&t;SNMP_INC_STATS(icmp_statistics, field)
DECL|macro|ICMP_INC_STATS_BH
mdefine_line|#define ICMP_INC_STATS_BH(field)&t;SNMP_INC_STATS_BH(icmp_statistics, field)
DECL|macro|ICMP_INC_STATS_USER
mdefine_line|#define ICMP_INC_STATS_USER(field) &t;SNMP_INC_STATS_USER(icmp_statistics, field)
r_extern
r_void
id|icmp_send
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb_in
comma
r_int
id|type
comma
r_int
id|code
comma
id|u32
id|info
)paren
suffix:semicolon
r_extern
r_int
id|icmp_rcv
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
id|icmp_ioctl
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
r_void
id|icmp_init
c_func
(paren
r_struct
id|net_proto_family
op_star
id|ops
)paren
suffix:semicolon
multiline_comment|/* Move into dst.h ? */
r_extern
r_int
id|xrlim_allow
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
comma
r_int
id|timeout
)paren
suffix:semicolon
DECL|struct|raw_sock
r_struct
id|raw_sock
(brace
multiline_comment|/* inet_sock has to be the first member */
DECL|member|inet
r_struct
id|inet_sock
id|inet
suffix:semicolon
DECL|member|filter
r_struct
id|icmp_filter
id|filter
suffix:semicolon
)brace
suffix:semicolon
DECL|function|raw_sk
r_static
r_inline
r_struct
id|raw_sock
op_star
id|raw_sk
c_func
(paren
r_const
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_return
(paren
r_struct
id|raw_sock
op_star
)paren
id|sk
suffix:semicolon
)brace
macro_line|#endif&t;/* _ICMP_H */
eof
