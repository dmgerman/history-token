multiline_comment|/* IRC extension for IP connection tracking.&n; * (C) 2000 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; * based on RR&squot;s ip_conntrack_ftp.h&n; *&n; * ip_conntrack_irc.h,v 1.6 2000/11/07 18:26:42 laforge Exp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *&n; */
macro_line|#ifndef _IP_CONNTRACK_IRC_H
DECL|macro|_IP_CONNTRACK_IRC_H
mdefine_line|#define _IP_CONNTRACK_IRC_H
macro_line|#ifndef __KERNEL__
macro_line|#error Only in kernel.
macro_line|#endif
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
DECL|macro|IRC_PORT
mdefine_line|#define IRC_PORT&t;6667
DECL|struct|dccproto
r_struct
id|dccproto
(brace
DECL|member|match
r_char
op_star
id|match
suffix:semicolon
DECL|member|matchlen
r_int
id|matchlen
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Protects irc part of conntracks */
DECL|variable|ip_irc_lock
id|DECLARE_LOCK_EXTERN
c_func
(paren
id|ip_irc_lock
)paren
suffix:semicolon
multiline_comment|/* We record seq number and length of irc ip/port text here: all in&n;   host order. */
multiline_comment|/* This structure is per expected connection */
DECL|struct|ip_ct_irc_expect
r_struct
id|ip_ct_irc_expect
(brace
multiline_comment|/* length of IP address */
DECL|member|len
id|u_int32_t
id|len
suffix:semicolon
multiline_comment|/* Port that was to be used */
DECL|member|port
id|u_int16_t
id|port
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This structure exists only once per master */
DECL|struct|ip_ct_irc_master
r_struct
id|ip_ct_irc_master
(brace
)brace
suffix:semicolon
macro_line|#endif /* _IP_CONNTRACK_IRC_H */
eof
