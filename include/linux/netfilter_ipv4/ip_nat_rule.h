macro_line|#ifndef _IP_NAT_RULE_H
DECL|macro|_IP_NAT_RULE_H
mdefine_line|#define _IP_NAT_RULE_H
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|ip_nat_rule_init
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
r_extern
r_void
id|ip_nat_rule_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ip_nat_rule_find
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
id|hooknum
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_struct
id|ip_nat_info
op_star
id|info
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _IP_NAT_RULE_H */
eof
