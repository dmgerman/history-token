macro_line|#ifndef _IP_CONNTRACK_CORE_H
DECL|macro|_IP_CONNTRACK_CORE_H
mdefine_line|#define _IP_CONNTRACK_CORE_H
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
multiline_comment|/* This header is used to share core functionality between the&n;   standalone connection tracking module, and the compatibility layer&squot;s use&n;   of connection tracking. */
r_extern
r_int
r_int
id|ip_conntrack_in
c_func
(paren
r_int
r_int
id|hooknum
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
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
r_int
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|ip_conntrack_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ip_conntrack_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|ip_conntrack_protocol
suffix:semicolon
r_extern
r_struct
id|ip_conntrack_protocol
op_star
id|ip_ct_find_proto
c_func
(paren
id|u_int8_t
id|protocol
)paren
suffix:semicolon
multiline_comment|/* Like above, but you already have conntrack read lock. */
r_extern
r_struct
id|ip_conntrack_protocol
op_star
id|__ip_ct_find_proto
c_func
(paren
id|u_int8_t
id|protocol
)paren
suffix:semicolon
r_extern
r_struct
id|list_head
id|protocol_list
suffix:semicolon
multiline_comment|/* Returns conntrack if it dealt with ICMP, and filled in skb-&gt;nfct */
r_extern
r_struct
id|ip_conntrack
op_star
id|icmp_error_track
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_enum
id|ip_conntrack_info
op_star
id|ctinfo
comma
r_int
r_int
id|hooknum
)paren
suffix:semicolon
r_extern
r_int
id|get_tuple
c_func
(paren
r_const
r_struct
id|iphdr
op_star
id|iph
comma
r_int
id|len
comma
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_struct
id|ip_conntrack_protocol
op_star
id|protocol
)paren
suffix:semicolon
multiline_comment|/* Find a connection corresponding to a tuple. */
r_struct
id|ip_conntrack_tuple_hash
op_star
id|ip_conntrack_find_get
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_const
r_struct
id|ip_conntrack
op_star
id|ignored_conntrack
)paren
suffix:semicolon
r_extern
r_int
id|__ip_conntrack_confirm
c_func
(paren
r_struct
id|nf_ct_info
op_star
id|nfct
)paren
suffix:semicolon
multiline_comment|/* Confirm a connection: returns NF_DROP if packet must be dropped. */
DECL|function|ip_conntrack_confirm
r_static
r_inline
r_int
id|ip_conntrack_confirm
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nfct
op_logical_and
op_logical_neg
id|is_confirmed
c_func
(paren
(paren
r_struct
id|ip_conntrack
op_star
)paren
id|skb-&gt;nfct-&gt;master
)paren
)paren
r_return
id|__ip_conntrack_confirm
c_func
(paren
id|skb-&gt;nfct
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
r_extern
r_struct
id|list_head
op_star
id|ip_conntrack_hash
suffix:semicolon
r_extern
r_struct
id|list_head
id|ip_conntrack_expect_list
suffix:semicolon
DECL|variable|ip_conntrack_lock
id|DECLARE_RWLOCK_EXTERN
c_func
(paren
id|ip_conntrack_lock
)paren
suffix:semicolon
macro_line|#endif /* _IP_CONNTRACK_CORE_H */
eof
