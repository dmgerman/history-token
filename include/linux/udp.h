multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the UDP protocol.&n; *&n; * Version:&t;@(#)udp.h&t;1.0.2&t;04/28/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_UDP_H
DECL|macro|_LINUX_UDP_H
mdefine_line|#define _LINUX_UDP_H
DECL|struct|udphdr
r_struct
id|udphdr
(brace
DECL|member|source
id|__u16
id|source
suffix:semicolon
DECL|member|dest
id|__u16
id|dest
suffix:semicolon
DECL|member|len
id|__u16
id|len
suffix:semicolon
DECL|member|check
id|__u16
id|check
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_UDP_H */
eof
