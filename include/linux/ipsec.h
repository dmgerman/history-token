multiline_comment|/*&n; *&t;Definitions for the SECurity layer&n; *&n; *&t;Author:&n; *&t;&t;Robert Muchsel &lt;muchsel@acm.org&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IPSEC_H
DECL|macro|_LINUX_IPSEC_H
mdefine_line|#define _LINUX_IPSEC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/* Values for the set/getsockopt calls */
multiline_comment|/* These defines are compatible with NRL IPv6, however their semantics&n;   is different */
DECL|macro|IPSEC_LEVEL_NONE
mdefine_line|#define IPSEC_LEVEL_NONE&t;-1&t;/* send plaintext, accept any */
DECL|macro|IPSEC_LEVEL_DEFAULT
mdefine_line|#define IPSEC_LEVEL_DEFAULT&t;0&t;/* encrypt/authenticate if possible */
multiline_comment|/* the default MUST be 0, because a */
multiline_comment|/* socket is initialized with 0&squot;s */
DECL|macro|IPSEC_LEVEL_USE
mdefine_line|#define IPSEC_LEVEL_USE&t;&t;1&t;/* use outbound, don&squot;t require inbound */
DECL|macro|IPSEC_LEVEL_REQUIRE
mdefine_line|#define IPSEC_LEVEL_REQUIRE&t;2&t;/* require both directions */
DECL|macro|IPSEC_LEVEL_UNIQUE
mdefine_line|#define IPSEC_LEVEL_UNIQUE&t;2&t;/* for compatibility only */
macro_line|#ifdef __KERNEL__
multiline_comment|/* skb bit flags set on packet input processing */
DECL|macro|RCV_SEC
mdefine_line|#define RCV_SEC&t;&t;&t;0x0f&t;/* options on receive */
DECL|macro|RCV_AUTH
mdefine_line|#define RCV_AUTH&t;&t;0x01&t;/* was authenticated */
DECL|macro|RCV_CRYPT
mdefine_line|#define RCV_CRYPT&t;&t;0x02&t;/* was encrypted */
DECL|macro|RCV_TUNNEL
mdefine_line|#define RCV_TUNNEL&t;&t;0x04&t;/* was tunneled */
DECL|macro|SND_SEC
mdefine_line|#define SND_SEC&t;&t;&t;0xf0&t;/* options on send, these are */
DECL|macro|SND_AUTH
mdefine_line|#define SND_AUTH&t;&t;0x10&t;/* currently unused */
DECL|macro|SND_CRYPT
mdefine_line|#define SND_CRYPT&t;&t;0x20
DECL|macro|SND_TUNNEL
mdefine_line|#define SND_TUNNEL&t;&t;0x40
multiline_comment|/*&n; *&t;FIXME: ignores network encryption for now..&n; */
macro_line|#ifdef CONFIG_NET_SECURITY
DECL|function|ipsec_sk_policy
r_static
id|__inline__
r_int
id|ipsec_sk_policy
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
(paren
(paren
id|sk-&gt;authentication
OL
id|IPSEC_LEVEL_REQUIRE
)paren
op_logical_or
(paren
id|skb-&gt;security
op_amp
id|RCV_AUTH
)paren
)paren
op_logical_and
(paren
(paren
id|sk-&gt;encryption
OL
id|IPSEC_LEVEL_REQUIRE
)paren
op_logical_or
(paren
id|skb-&gt;security
op_amp
id|RCV_CRYPT
)paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|ipsec_sk_policy
r_static
id|__inline__
r_int
id|ipsec_sk_policy
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* CONFIG */
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_IPSEC_H */
eof
