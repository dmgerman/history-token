macro_line|#ifndef _IP_CONNTRACK_AMANDA_H
DECL|macro|_IP_CONNTRACK_AMANDA_H
mdefine_line|#define _IP_CONNTRACK_AMANDA_H
multiline_comment|/* AMANDA tracking. */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
multiline_comment|/* Protects amanda part of conntracks */
DECL|variable|ip_amanda_lock
id|DECLARE_LOCK_EXTERN
c_func
(paren
id|ip_amanda_lock
)paren
suffix:semicolon
macro_line|#endif
DECL|struct|ip_ct_amanda_expect
r_struct
id|ip_ct_amanda_expect
(brace
DECL|member|port
id|u_int16_t
id|port
suffix:semicolon
multiline_comment|/* port number of this expectation */
DECL|member|offset
id|u_int16_t
id|offset
suffix:semicolon
multiline_comment|/* offset of the port specification in ctrl packet */
DECL|member|len
id|u_int16_t
id|len
suffix:semicolon
multiline_comment|/* the length of the port number specification */
)brace
suffix:semicolon
macro_line|#endif /* _IP_CONNTRACK_AMANDA_H */
eof
