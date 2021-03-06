macro_line|#ifndef _NET_RAWV6_H
DECL|macro|_NET_RAWV6_H
mdefine_line|#define _NET_RAWV6_H
macro_line|#ifdef __KERNEL__
DECL|macro|RAWV6_HTABLE_SIZE
mdefine_line|#define RAWV6_HTABLE_SIZE&t;MAX_INET_PROTOS
r_extern
r_struct
id|hlist_head
id|raw_v6_htable
(braket
id|RAWV6_HTABLE_SIZE
)braket
suffix:semicolon
r_extern
id|rwlock_t
id|raw_v6_lock
suffix:semicolon
r_extern
r_void
id|ipv6_raw_deliver
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|nexthdr
)paren
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|__raw_v6_lookup
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
r_struct
id|in6_addr
op_star
id|loc_addr
comma
r_struct
id|in6_addr
op_star
id|rmt_addr
)paren
suffix:semicolon
r_extern
r_int
id|rawv6_rcv
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
suffix:semicolon
r_extern
r_void
id|rawv6_err
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
comma
r_struct
id|inet6_skb_parm
op_star
id|opt
comma
r_int
id|type
comma
r_int
id|code
comma
r_int
id|offset
comma
id|u32
id|info
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
