macro_line|#ifndef _IP_CONNTRACK_ICMP_H
DECL|macro|_IP_CONNTRACK_ICMP_H
mdefine_line|#define _IP_CONNTRACK_ICMP_H
multiline_comment|/* ICMP tracking. */
macro_line|#include &lt;asm/atomic.h&gt;
DECL|struct|ip_ct_icmp
r_struct
id|ip_ct_icmp
(brace
multiline_comment|/* Optimization: when number in == number out, forget immediately. */
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _IP_CONNTRACK_ICMP_H */
eof
