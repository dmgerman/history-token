multiline_comment|/*&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _IP6_FIB_H
DECL|macro|_IP6_FIB_H
mdefine_line|#define _IP6_FIB_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/ipv6_route.h&gt;
macro_line|#include &lt;net/dst.h&gt;
macro_line|#include &lt;net/flow.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
r_struct
id|rt6_info
suffix:semicolon
DECL|struct|fib6_node
r_struct
id|fib6_node
(brace
DECL|member|parent
r_struct
id|fib6_node
op_star
id|parent
suffix:semicolon
DECL|member|left
r_struct
id|fib6_node
op_star
id|left
suffix:semicolon
DECL|member|right
r_struct
id|fib6_node
op_star
id|right
suffix:semicolon
DECL|member|subtree
r_struct
id|fib6_node
op_star
id|subtree
suffix:semicolon
DECL|member|leaf
r_struct
id|rt6_info
op_star
id|leaf
suffix:semicolon
DECL|member|fn_bit
id|__u16
id|fn_bit
suffix:semicolon
multiline_comment|/* bit key */
DECL|member|fn_flags
id|__u16
id|fn_flags
suffix:semicolon
DECL|member|fn_sernum
id|__u32
id|fn_sernum
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;routing information&n; *&n; */
DECL|struct|rt6key
r_struct
id|rt6key
(brace
DECL|member|addr
r_struct
id|in6_addr
id|addr
suffix:semicolon
DECL|member|plen
r_int
id|plen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rt6_info
r_struct
id|rt6_info
(brace
r_union
(brace
DECL|member|dst
r_struct
id|dst_entry
id|dst
suffix:semicolon
DECL|member|next
r_struct
id|rt6_info
op_star
id|next
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|rt6i_idev
r_struct
id|inet6_dev
op_star
id|rt6i_idev
suffix:semicolon
DECL|macro|rt6i_dev
mdefine_line|#define rt6i_dev&t;&t;&t;u.dst.dev
DECL|macro|rt6i_nexthop
mdefine_line|#define rt6i_nexthop&t;&t;&t;u.dst.neighbour
DECL|macro|rt6i_expires
mdefine_line|#define rt6i_expires&t;&t;&t;u.dst.expires
DECL|member|rt6i_node
r_struct
id|fib6_node
op_star
id|rt6i_node
suffix:semicolon
DECL|member|rt6i_gateway
r_struct
id|in6_addr
id|rt6i_gateway
suffix:semicolon
DECL|member|rt6i_flags
id|u32
id|rt6i_flags
suffix:semicolon
DECL|member|rt6i_metric
id|u32
id|rt6i_metric
suffix:semicolon
DECL|member|rt6i_ref
id|atomic_t
id|rt6i_ref
suffix:semicolon
DECL|member|rt6i_dst
r_struct
id|rt6key
id|rt6i_dst
suffix:semicolon
DECL|member|rt6i_src
r_struct
id|rt6key
id|rt6i_src
suffix:semicolon
DECL|member|rt6i_protocol
id|u8
id|rt6i_protocol
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fib6_walker_t
r_struct
id|fib6_walker_t
(brace
DECL|member|prev
DECL|member|next
r_struct
id|fib6_walker_t
op_star
id|prev
comma
op_star
id|next
suffix:semicolon
DECL|member|root
DECL|member|node
r_struct
id|fib6_node
op_star
id|root
comma
op_star
id|node
suffix:semicolon
DECL|member|leaf
r_struct
id|rt6_info
op_star
id|leaf
suffix:semicolon
DECL|member|state
r_int
r_char
id|state
suffix:semicolon
DECL|member|prune
r_int
r_char
id|prune
suffix:semicolon
DECL|member|func
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|fib6_walker_t
op_star
)paren
suffix:semicolon
DECL|member|args
r_void
op_star
id|args
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|fib6_walker_t
id|fib6_walker_list
suffix:semicolon
r_extern
id|rwlock_t
id|fib6_walker_lock
suffix:semicolon
DECL|function|fib6_walker_link
r_static
r_inline
r_void
id|fib6_walker_link
c_func
(paren
r_struct
id|fib6_walker_t
op_star
id|w
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|fib6_walker_lock
)paren
suffix:semicolon
id|w-&gt;next
op_assign
id|fib6_walker_list.next
suffix:semicolon
id|w-&gt;prev
op_assign
op_amp
id|fib6_walker_list
suffix:semicolon
id|w-&gt;next-&gt;prev
op_assign
id|w
suffix:semicolon
id|w-&gt;prev-&gt;next
op_assign
id|w
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|fib6_walker_lock
)paren
suffix:semicolon
)brace
DECL|function|fib6_walker_unlink
r_static
r_inline
r_void
id|fib6_walker_unlink
c_func
(paren
r_struct
id|fib6_walker_t
op_star
id|w
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|fib6_walker_lock
)paren
suffix:semicolon
id|w-&gt;next-&gt;prev
op_assign
id|w-&gt;prev
suffix:semicolon
id|w-&gt;prev-&gt;next
op_assign
id|w-&gt;next
suffix:semicolon
id|w-&gt;prev
op_assign
id|w-&gt;next
op_assign
id|w
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|fib6_walker_lock
)paren
suffix:semicolon
)brace
DECL|struct|rt6_statistics
r_struct
id|rt6_statistics
(brace
DECL|member|fib_nodes
id|__u32
id|fib_nodes
suffix:semicolon
DECL|member|fib_route_nodes
id|__u32
id|fib_route_nodes
suffix:semicolon
DECL|member|fib_rt_alloc
id|__u32
id|fib_rt_alloc
suffix:semicolon
multiline_comment|/* permanent routes&t;*/
DECL|member|fib_rt_entries
id|__u32
id|fib_rt_entries
suffix:semicolon
multiline_comment|/* rt entries in table&t;*/
DECL|member|fib_rt_cache
id|__u32
id|fib_rt_cache
suffix:semicolon
multiline_comment|/* cache routes&t;&t;*/
DECL|member|fib_discarded_routes
id|__u32
id|fib_discarded_routes
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RTN_TL_ROOT
mdefine_line|#define RTN_TL_ROOT&t;0x0001
DECL|macro|RTN_ROOT
mdefine_line|#define RTN_ROOT&t;0x0002&t;&t;/* tree root node&t;&t;*/
DECL|macro|RTN_RTINFO
mdefine_line|#define RTN_RTINFO&t;0x0004&t;&t;/* node with valid routing info&t;*/
multiline_comment|/*&n; *&t;priority levels (or metrics)&n; *&n; */
DECL|macro|RTPRI_FIREWALL
mdefine_line|#define RTPRI_FIREWALL&t;8&t;&t;/* Firewall control information&t;*/
DECL|macro|RTPRI_FLOW
mdefine_line|#define RTPRI_FLOW&t;16&t;&t;/* Flow based forwarding rules&t;*/
DECL|macro|RTPRI_KERN_CTL
mdefine_line|#define RTPRI_KERN_CTL&t;32&t;&t;/* Kernel control routes&t;*/
DECL|macro|RTPRI_USER_MIN
mdefine_line|#define RTPRI_USER_MIN&t;256&t;&t;/* Mimimum user priority&t;*/
DECL|macro|RTPRI_USER_MAX
mdefine_line|#define RTPRI_USER_MAX&t;1024&t;&t;/* Maximum user priority&t;*/
DECL|macro|RTPRI_KERN_DFLT
mdefine_line|#define RTPRI_KERN_DFLT&t;4096&t;&t;/* Kernel default routes&t;*/
DECL|macro|MAX_FLOW_BACKTRACE
mdefine_line|#define&t;MAX_FLOW_BACKTRACE&t;32
DECL|typedef|f_pnode
r_typedef
r_void
(paren
op_star
id|f_pnode
)paren
(paren
r_struct
id|fib6_node
op_star
id|fn
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|fib6_node
id|ip6_routing_table
suffix:semicolon
multiline_comment|/*&n; *&t;exported functions&n; */
r_extern
r_struct
id|fib6_node
op_star
id|fib6_lookup
c_func
(paren
r_struct
id|fib6_node
op_star
id|root
comma
r_struct
id|in6_addr
op_star
id|daddr
comma
r_struct
id|in6_addr
op_star
id|saddr
)paren
suffix:semicolon
r_struct
id|fib6_node
op_star
id|fib6_locate
c_func
(paren
r_struct
id|fib6_node
op_star
id|root
comma
r_struct
id|in6_addr
op_star
id|daddr
comma
r_int
id|dst_len
comma
r_struct
id|in6_addr
op_star
id|saddr
comma
r_int
id|src_len
)paren
suffix:semicolon
r_extern
r_void
id|fib6_clean_tree
c_func
(paren
r_struct
id|fib6_node
op_star
id|root
comma
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|rt6_info
op_star
comma
r_void
op_star
id|arg
)paren
comma
r_int
id|prune
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|fib6_walk
c_func
(paren
r_struct
id|fib6_walker_t
op_star
id|w
)paren
suffix:semicolon
r_extern
r_int
id|fib6_walk_continue
c_func
(paren
r_struct
id|fib6_walker_t
op_star
id|w
)paren
suffix:semicolon
r_extern
r_int
id|fib6_add
c_func
(paren
r_struct
id|fib6_node
op_star
id|root
comma
r_struct
id|rt6_info
op_star
id|rt
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|rtattr
)paren
suffix:semicolon
r_extern
r_int
id|fib6_del
c_func
(paren
r_struct
id|rt6_info
op_star
id|rt
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_void
op_star
id|rtattr
)paren
suffix:semicolon
r_extern
r_void
id|inet6_rt_notify
c_func
(paren
r_int
id|event
comma
r_struct
id|rt6_info
op_star
id|rt
comma
r_struct
id|nlmsghdr
op_star
id|nlh
)paren
suffix:semicolon
r_extern
r_void
id|fib6_run_gc
c_func
(paren
r_int
r_int
id|dummy
)paren
suffix:semicolon
r_extern
r_void
id|fib6_gc_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fib6_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
