multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the RAW-IP module.&n; *&n; * Version:&t;@(#)raw.h&t;1.0.2&t;05/07/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _RAW_H
DECL|macro|_RAW_H
mdefine_line|#define _RAW_H
r_extern
r_struct
id|proto
id|raw_prot
suffix:semicolon
r_extern
r_void
id|raw_err
c_func
(paren
r_struct
id|sock
op_star
comma
r_struct
id|sk_buff
op_star
comma
id|u32
id|info
)paren
suffix:semicolon
r_extern
r_int
id|raw_rcv
c_func
(paren
r_struct
id|sock
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* Note: v4 ICMP wants to get at this stuff, if you change the&n; *       hashing mechanism, make sure you update icmp.c as well.&n; */
DECL|macro|RAWV4_HTABLE_SIZE
mdefine_line|#define RAWV4_HTABLE_SIZE&t;MAX_INET_PROTOS
r_extern
r_struct
id|sock
op_star
id|raw_v4_htable
(braket
id|RAWV4_HTABLE_SIZE
)braket
suffix:semicolon
r_extern
id|rwlock_t
id|raw_v4_lock
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|__raw_v4_lookup
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_int
id|num
comma
r_int
r_int
id|raddr
comma
r_int
r_int
id|laddr
comma
r_int
id|dif
)paren
suffix:semicolon
r_extern
r_void
id|raw_v4_input
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|iphdr
op_star
id|iph
comma
r_int
id|hash
)paren
suffix:semicolon
macro_line|#endif&t;/* _RAW_H */
eof
