multiline_comment|/* IRC extension for IP connection tracking.&n; * (C) 2000 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; * based on RR&squot;s ip_conntrack_ftp.h&n; *&n; * ip_conntrack_irc.h,v 1.6 2000/11/07 18:26:42 laforge Exp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *&n; */
macro_line|#ifndef _IP_CONNTRACK_IRC_H
DECL|macro|_IP_CONNTRACK_IRC_H
mdefine_line|#define _IP_CONNTRACK_IRC_H
multiline_comment|/* This structure exists only once per master */
DECL|struct|ip_ct_irc_master
r_struct
id|ip_ct_irc_master
(brace
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_int
r_int
(paren
op_star
id|ip_nat_irc_hook
)paren
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_int
r_int
id|matchoff
comma
r_int
r_int
id|matchlen
comma
r_struct
id|ip_conntrack_expect
op_star
id|exp
)paren
suffix:semicolon
DECL|macro|IRC_PORT
mdefine_line|#define IRC_PORT&t;6667
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _IP_CONNTRACK_IRC_H */
eof
