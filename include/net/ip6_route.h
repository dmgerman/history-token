macro_line|#ifndef _NET_IP6_ROUTE_H
DECL|macro|_NET_IP6_ROUTE_H
mdefine_line|#define _NET_IP6_ROUTE_H
DECL|macro|IP6_RT_PRIO_FW
mdefine_line|#define IP6_RT_PRIO_FW&t;&t;16
DECL|macro|IP6_RT_PRIO_USER
mdefine_line|#define IP6_RT_PRIO_USER&t;1024
DECL|macro|IP6_RT_PRIO_ADDRCONF
mdefine_line|#define IP6_RT_PRIO_ADDRCONF&t;256
DECL|macro|IP6_RT_PRIO_KERN
mdefine_line|#define IP6_RT_PRIO_KERN&t;512
DECL|macro|IP6_RT_FLOW_MASK
mdefine_line|#define IP6_RT_FLOW_MASK&t;0x00ff
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;net/flow.h&gt;
macro_line|#include &lt;net/ip6_fib.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
DECL|struct|pol_chain
r_struct
id|pol_chain
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|priority
r_int
id|priority
suffix:semicolon
DECL|member|rules
r_struct
id|fib6_node
op_star
id|rules
suffix:semicolon
DECL|member|next
r_struct
id|pol_chain
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|rt6_info
id|ip6_null_entry
suffix:semicolon
r_extern
r_int
id|ip6_rt_max_size
suffix:semicolon
r_extern
r_int
id|ip6_rt_gc_min
suffix:semicolon
r_extern
r_int
id|ip6_rt_gc_timeout
suffix:semicolon
r_extern
r_int
id|ip6_rt_gc_interval
suffix:semicolon
r_extern
r_void
id|ip6_route_input
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_struct
id|dst_entry
op_star
id|ip6_route_output
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|flowi
op_star
id|fl
)paren
suffix:semicolon
r_extern
r_void
id|ip6_route_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ip6_route_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_route_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|ip6_route_add
c_func
(paren
r_struct
id|in6_rtmsg
op_star
id|rtmsg
)paren
suffix:semicolon
r_extern
r_int
id|ip6_del_rt
c_func
(paren
r_struct
id|rt6_info
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ip6_rt_addr_add
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ip6_rt_addr_del
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|rt6_sndmsg
c_func
(paren
r_int
id|type
comma
r_struct
id|in6_addr
op_star
id|dst
comma
r_struct
id|in6_addr
op_star
id|src
comma
r_struct
id|in6_addr
op_star
id|gw
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|dstlen
comma
r_int
id|srclen
comma
r_int
id|metric
comma
id|__u32
id|flags
)paren
suffix:semicolon
r_extern
r_struct
id|rt6_info
op_star
id|rt6_lookup
c_func
(paren
r_struct
id|in6_addr
op_star
id|daddr
comma
r_struct
id|in6_addr
op_star
id|saddr
comma
r_int
id|oif
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;support functions for ND&n; *&n; */
r_extern
r_struct
id|rt6_info
op_star
id|rt6_get_dflt_router
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_struct
id|rt6_info
op_star
id|rt6_add_dflt_router
c_func
(paren
r_struct
id|in6_addr
op_star
id|gwaddr
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|rt6_purge_dflt_routers
c_func
(paren
r_int
id|lst_resort
)paren
suffix:semicolon
r_extern
r_void
id|rt6_redirect
c_func
(paren
r_struct
id|in6_addr
op_star
id|dest
comma
r_struct
id|in6_addr
op_star
id|saddr
comma
r_struct
id|neighbour
op_star
id|neigh
comma
r_int
id|on_link
)paren
suffix:semicolon
r_extern
r_void
id|rt6_pmtu_discovery
c_func
(paren
r_struct
id|in6_addr
op_star
id|daddr
comma
r_struct
id|in6_addr
op_star
id|saddr
comma
r_struct
id|net_device
op_star
id|dev
comma
id|u32
id|pmtu
)paren
suffix:semicolon
r_struct
id|nlmsghdr
suffix:semicolon
r_struct
id|netlink_callback
suffix:semicolon
r_extern
r_int
id|inet6_dump_fib
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
r_extern
r_int
id|inet6_rtm_newroute
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|inet6_rtm_delroute
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|inet6_rtm_getroute
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|rt6_ifdown
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|rt6_mtu_change
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mtu
)paren
suffix:semicolon
r_extern
id|rwlock_t
id|rt6_lock
suffix:semicolon
multiline_comment|/*&n; *&t;Store a destination cache entry in a socket&n; *&t;For UDP/RAW sockets this is done on udp_connect.&n; */
DECL|function|ip6_dst_store
r_static
r_inline
r_void
id|ip6_dst_store
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|dst_entry
op_star
id|dst
comma
r_struct
id|in6_addr
op_star
id|daddr
)paren
(brace
r_struct
id|ipv6_pinfo
op_star
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_struct
id|rt6_info
op_star
id|rt
op_assign
(paren
r_struct
id|rt6_info
op_star
)paren
id|dst
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|sk-&gt;dst_lock
)paren
suffix:semicolon
id|__sk_dst_set
c_func
(paren
id|sk
comma
id|dst
)paren
suffix:semicolon
id|np-&gt;daddr_cache
op_assign
id|daddr
suffix:semicolon
id|np-&gt;dst_cookie
op_assign
id|rt-&gt;rt6i_node
ques
c_cond
id|rt-&gt;rt6i_node-&gt;fn_sernum
suffix:colon
l_int|0
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|sk-&gt;dst_lock
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
