multiline_comment|/*&n; *&t;&t;Swansea University Computer Society NET3&n; *&n; *&t;This work is derived from NET2Debugged, which is in turn derived&n; *&t;from NET2D which was written by:&n; * &t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This work was derived from Ross Biro&squot;s inspirational work&n; *&t;&t;for the LINUX operating system.  His version numbers were:&n; *&n; *&t;&t;$Id: Space.c,v     0.8.4.5  1992/12/12 19:25:04 bir7 Exp $&n; *&t;&t;$Id: arp.c,v       0.8.4.6  1993/01/28 22:30:00 bir7 Exp $&n; *&t;&t;$Id: arp.h,v       0.8.4.6  1993/01/28 22:30:00 bir7 Exp $&n; *&t;&t;$Id: dev.c,v       0.8.4.13 1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: dev.h,v       0.8.4.7  1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: eth.c,v       0.8.4.4  1993/01/22 23:21:38 bir7 Exp $&n; *&t;&t;$Id: eth.h,v       0.8.4.1  1992/11/10 00:17:18 bir7 Exp $&n; *&t;&t;$Id: icmp.c,v      0.8.4.9  1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: icmp.h,v      0.8.4.2  1992/11/15 14:55:30 bir7 Exp $&n; * &t;&t;$Id: ip.c,v        0.8.4.8  1992/12/12 19:25:04 bir7 Exp $&n; * &t;&t;$Id: ip.h,v        0.8.4.2  1993/01/23 18:00:11 bir7 Exp $&n; * &t;&t;$Id: loopback.c,v  0.8.4.8  1993/01/23 18:00:11 bir7 Exp $&n; * &t;&t;$Id: packet.c,v    0.8.4.7  1993/01/26 22:04:00 bir7 Exp $&n; *&t;&t;$Id: protocols.c,v 0.8.4.3  1992/11/15 14:55:30 bir7 Exp $&n; *&t;&t;$Id: raw.c,v       0.8.4.12 1993/01/26 22:04:00 bir7 Exp $&n; *&t;&t;$Id: sock.c,v      0.8.4.6  1993/01/28 22:30:00 bir7 Exp $&n; *&t;&t;$Id: sock.h,v      0.8.4.7  1993/01/26 22:04:00 bir7 Exp $&n; *&t;&t;$Id: tcp.c,v       0.8.4.16 1993/01/26 22:04:00 bir7 Exp $&n; *&t;&t;$Id: tcp.h,v       0.8.4.7  1993/01/22 22:58:08 bir7 Exp $&n; *&t;&t;$Id: timer.c,v     0.8.4.8  1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: timer.h,v     0.8.4.2  1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: udp.c,v       0.8.4.12 1993/01/26 22:04:00 bir7 Exp $&n; *&t;&t;$Id: udp.h,v       0.8.4.1  1992/11/10 00:17:18 bir7 Exp $&n; *&t;&t;$Id: we.c,v        0.8.4.10 1993/01/23 18:00:11 bir7 Exp $&n; *&t;&t;$Id: wereg.h,v     0.8.4.1  1992/11/10 00:17:18 bir7 Exp $&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_INET_H
DECL|macro|_LINUX_INET_H
mdefine_line|#define _LINUX_INET_H
macro_line|#ifdef __KERNEL__
r_extern
r_void
id|inet_proto_init
c_func
(paren
r_struct
id|net_proto
op_star
id|pro
)paren
suffix:semicolon
r_extern
r_char
op_star
id|in_ntoa
c_func
(paren
id|__u32
id|in
)paren
suffix:semicolon
r_extern
id|__u32
id|in_aton
c_func
(paren
r_const
r_char
op_star
id|str
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* _LINUX_INET_H */
eof
