multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the UDP protocol.&n; *&n; * Version:&t;@(#)udp.h&t;1.0.2&t;04/28/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_UDP_H
DECL|macro|_LINUX_UDP_H
mdefine_line|#define _LINUX_UDP_H
macro_line|#include &lt;linux/types.h&gt;
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
multiline_comment|/* UDP socket options */
DECL|macro|UDP_CORK
mdefine_line|#define UDP_CORK&t;1&t;/* Never send partially complete segments */
DECL|macro|UDP_ENCAP
mdefine_line|#define UDP_ENCAP&t;100&t;/* Set the socket to accept encapsulated packets */
multiline_comment|/* UDP encapsulation types */
DECL|macro|UDP_ENCAP_ESPINUDP_NON_IKE
mdefine_line|#define UDP_ENCAP_ESPINUDP_NON_IKE&t;1 /* draft-ietf-ipsec-nat-t-ike-00/01 */
DECL|macro|UDP_ENCAP_ESPINUDP
mdefine_line|#define UDP_ENCAP_ESPINUDP&t;2 /* draft-ietf-ipsec-udp-encaps-06 */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
DECL|struct|udp_sock
r_struct
id|udp_sock
(brace
multiline_comment|/* inet_sock has to be the first member */
DECL|member|inet
r_struct
id|inet_sock
id|inet
suffix:semicolon
DECL|member|pending
r_int
id|pending
suffix:semicolon
multiline_comment|/* Any pending frames ? */
DECL|member|corkflag
r_int
r_int
id|corkflag
suffix:semicolon
multiline_comment|/* Cork is required */
DECL|member|encap_type
id|__u16
id|encap_type
suffix:semicolon
multiline_comment|/* Is this an Encapsulation socket? */
multiline_comment|/*&n;&t; * Following member retains the infomation to create a UDP header&n;&t; * when the socket is uncorked.&n;&t; */
DECL|member|len
id|__u16
id|len
suffix:semicolon
multiline_comment|/* total length of pending frames */
)brace
suffix:semicolon
DECL|function|udp_sk
r_static
r_inline
r_struct
id|udp_sock
op_star
id|udp_sk
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
id|udp_sock
op_star
)paren
id|sk
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif&t;/* _LINUX_UDP_H */
eof
