macro_line|#ifndef _ADDRCONF_H
DECL|macro|_ADDRCONF_H
mdefine_line|#define _ADDRCONF_H
DECL|macro|RETRANS_TIMER
mdefine_line|#define RETRANS_TIMER&t;HZ
DECL|macro|MAX_RTR_SOLICITATIONS
mdefine_line|#define MAX_RTR_SOLICITATIONS&t;&t;3
DECL|macro|RTR_SOLICITATION_INTERVAL
mdefine_line|#define RTR_SOLICITATION_INTERVAL&t;(4*HZ)
DECL|macro|MIN_VALID_LIFETIME
mdefine_line|#define MIN_VALID_LIFETIME&t;&t;(2*3600)&t;/* 2 hours */
DECL|macro|TEMP_VALID_LIFETIME
mdefine_line|#define TEMP_VALID_LIFETIME&t;&t;(7*86400)
DECL|macro|TEMP_PREFERRED_LIFETIME
mdefine_line|#define TEMP_PREFERRED_LIFETIME&t;&t;(86400)
DECL|macro|REGEN_MAX_RETRY
mdefine_line|#define REGEN_MAX_RETRY&t;&t;&t;(5)
DECL|macro|MAX_DESYNC_FACTOR
mdefine_line|#define MAX_DESYNC_FACTOR&t;&t;(600)
DECL|macro|ADDR_CHECK_FREQUENCY
mdefine_line|#define ADDR_CHECK_FREQUENCY&t;&t;(120*HZ)
DECL|macro|IPV6_MAX_ADDRESSES
mdefine_line|#define IPV6_MAX_ADDRESSES&t;&t;16
DECL|struct|prefix_info
r_struct
id|prefix_info
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|length
id|__u8
id|length
suffix:semicolon
DECL|member|prefix_len
id|__u8
id|prefix_len
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|onlink
id|__u8
id|onlink
suffix:colon
l_int|1
comma
DECL|member|autoconf
id|autoconf
suffix:colon
l_int|1
comma
DECL|member|reserved
id|reserved
suffix:colon
l_int|6
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved
id|__u8
id|reserved
suffix:colon
l_int|6
comma
DECL|member|autoconf
id|autoconf
suffix:colon
l_int|1
comma
DECL|member|onlink
id|onlink
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|valid
id|__u32
id|valid
suffix:semicolon
DECL|member|prefered
id|__u32
id|prefered
suffix:semicolon
DECL|member|reserved2
id|__u32
id|reserved2
suffix:semicolon
DECL|member|prefix
r_struct
id|in6_addr
id|prefix
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/if_inet6.h&gt;
DECL|macro|IN6_ADDR_HSIZE
mdefine_line|#define IN6_ADDR_HSIZE&t;&t;16
r_extern
r_void
id|addrconf_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|addrconf_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|addrconf_add_ifaddr
c_func
(paren
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|addrconf_del_ifaddr
c_func
(paren
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|addrconf_set_dstaddr
c_func
(paren
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_chk_addr
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
comma
r_int
id|strict
)paren
suffix:semicolon
r_extern
r_struct
id|inet6_ifaddr
op_star
id|ipv6_get_ifaddr
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
comma
r_int
id|strict
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_get_saddr
c_func
(paren
r_struct
id|dst_entry
op_star
id|dst
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
r_extern
r_int
id|ipv6_dev_get_saddr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
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
comma
r_int
id|onlink
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_get_lladdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_rcv_saddr_equal
c_func
(paren
r_const
r_struct
id|sock
op_star
id|sk
comma
r_const
r_struct
id|sock
op_star
id|sk2
)paren
suffix:semicolon
r_extern
r_void
id|addrconf_join_solict
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|addrconf_leave_solict
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;multicast prototypes (mcast.c)&n; */
r_extern
r_int
id|ipv6_sock_mc_join
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|ifindex
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_sock_mc_drop
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|ifindex
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_sock_mc_close
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|inet6_mc_check
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|in6_addr
op_star
id|mc_addr
comma
r_struct
id|in6_addr
op_star
id|src_addr
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_dev_mc_inc
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_dev_mc_dec
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_mc_up
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_mc_down
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_mc_init_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_mc_destroy_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
suffix:semicolon
r_extern
r_void
id|addrconf_dad_failure
c_func
(paren
r_struct
id|inet6_ifaddr
op_star
id|ifp
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_chk_mcast_addr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|group
comma
r_struct
id|in6_addr
op_star
id|src_addr
)paren
suffix:semicolon
r_extern
r_void
id|addrconf_prefix_rcv
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u8
op_star
id|opt
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;anycast prototypes (anycast.c)&n; */
r_extern
r_int
id|ipv6_sock_ac_join
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|ifindex
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_sock_ac_drop
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|ifindex
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_sock_ac_close
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|inet6_ac_check
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|in6_addr
op_star
id|addr
comma
r_int
id|ifindex
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_dev_ac_inc
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_dev_ac_dec
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|ipv6_chk_acast_addr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|in6_addr
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/* Device notifier */
r_extern
r_int
id|register_inet6addr_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_extern
r_int
id|unregister_inet6addr_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_static
r_inline
r_struct
id|inet6_dev
op_star
DECL|function|__in6_dev_get
id|__in6_dev_get
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
(paren
r_struct
id|inet6_dev
op_star
)paren
id|dev-&gt;ip6_ptr
suffix:semicolon
)brace
r_extern
id|rwlock_t
id|addrconf_lock
suffix:semicolon
r_static
r_inline
r_struct
id|inet6_dev
op_star
DECL|function|in6_dev_get
id|in6_dev_get
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|inet6_dev
op_star
id|idev
op_assign
l_int|NULL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|addrconf_lock
)paren
suffix:semicolon
id|idev
op_assign
id|dev-&gt;ip6_ptr
suffix:semicolon
r_if
c_cond
(paren
id|idev
)paren
id|atomic_inc
c_func
(paren
op_amp
id|idev-&gt;refcnt
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|addrconf_lock
)paren
suffix:semicolon
r_return
id|idev
suffix:semicolon
)brace
r_extern
r_void
id|in6_dev_finish_destroy
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|in6_dev_put
id|in6_dev_put
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|idev-&gt;refcnt
)paren
)paren
id|in6_dev_finish_destroy
c_func
(paren
id|idev
)paren
suffix:semicolon
)brace
DECL|macro|__in6_dev_put
mdefine_line|#define __in6_dev_put(idev)  atomic_dec(&amp;(idev)-&gt;refcnt)
DECL|macro|in6_dev_hold
mdefine_line|#define in6_dev_hold(idev)   atomic_inc(&amp;(idev)-&gt;refcnt)
r_extern
r_void
id|inet6_ifa_finish_destroy
c_func
(paren
r_struct
id|inet6_ifaddr
op_star
id|ifp
)paren
suffix:semicolon
DECL|function|in6_ifa_put
r_static
r_inline
r_void
id|in6_ifa_put
c_func
(paren
r_struct
id|inet6_ifaddr
op_star
id|ifp
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|ifp-&gt;refcnt
)paren
)paren
id|inet6_ifa_finish_destroy
c_func
(paren
id|ifp
)paren
suffix:semicolon
)brace
DECL|macro|__in6_ifa_put
mdefine_line|#define __in6_ifa_put(idev)  atomic_dec(&amp;(idev)-&gt;refcnt)
DECL|macro|in6_ifa_hold
mdefine_line|#define in6_ifa_hold(idev)   atomic_inc(&amp;(idev)-&gt;refcnt)
r_extern
r_void
id|addrconf_forwarding_on
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Hash function taken from net_alias.c&n; */
DECL|function|ipv6_addr_hash
r_static
id|__inline__
id|u8
id|ipv6_addr_hash
c_func
(paren
r_const
r_struct
id|in6_addr
op_star
id|addr
)paren
(brace
id|__u32
id|word
suffix:semicolon
multiline_comment|/* &n;&t; * We perform the hash function over the last 64 bits of the address&n;&t; * This will include the IEEE address token on links that support it.&n;&t; */
id|word
op_assign
id|addr-&gt;s6_addr
(braket
l_int|2
)braket
op_xor
id|addr-&gt;s6_addr32
(braket
l_int|3
)braket
suffix:semicolon
id|word
op_xor_assign
(paren
id|word
op_rshift
l_int|16
)paren
suffix:semicolon
id|word
op_xor_assign
(paren
id|word
op_rshift
l_int|8
)paren
suffix:semicolon
r_return
(paren
(paren
id|word
op_xor
(paren
id|word
op_rshift
l_int|4
)paren
)paren
op_amp
l_int|0x0f
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;compute link-local solicited-node multicast address&n; */
DECL|function|addrconf_addr_solict_mult
r_static
r_inline
r_void
id|addrconf_addr_solict_mult
c_func
(paren
r_const
r_struct
id|in6_addr
op_star
id|addr
comma
r_struct
id|in6_addr
op_star
id|solicited
)paren
(brace
id|ipv6_addr_set
c_func
(paren
id|solicited
comma
id|__constant_htonl
c_func
(paren
l_int|0xFF020000
)paren
comma
l_int|0
comma
id|__constant_htonl
c_func
(paren
l_int|0x1
)paren
comma
id|__constant_htonl
c_func
(paren
l_int|0xFF000000
)paren
op_or
id|addr-&gt;s6_addr32
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
DECL|function|ipv6_addr_all_nodes
r_static
r_inline
r_void
id|ipv6_addr_all_nodes
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr
)paren
(brace
id|ipv6_addr_set
c_func
(paren
id|addr
comma
id|__constant_htonl
c_func
(paren
l_int|0xFF020000
)paren
comma
l_int|0
comma
l_int|0
comma
id|__constant_htonl
c_func
(paren
l_int|0x1
)paren
)paren
suffix:semicolon
)brace
DECL|function|ipv6_addr_all_routers
r_static
r_inline
r_void
id|ipv6_addr_all_routers
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr
)paren
(brace
id|ipv6_addr_set
c_func
(paren
id|addr
comma
id|__constant_htonl
c_func
(paren
l_int|0xFF020000
)paren
comma
l_int|0
comma
l_int|0
comma
id|__constant_htonl
c_func
(paren
l_int|0x2
)paren
)paren
suffix:semicolon
)brace
DECL|function|ipv6_addr_is_multicast
r_static
r_inline
r_int
id|ipv6_addr_is_multicast
c_func
(paren
r_const
r_struct
id|in6_addr
op_star
id|addr
)paren
(brace
r_return
(paren
id|addr-&gt;s6_addr32
(braket
l_int|0
)braket
op_amp
id|__constant_htonl
c_func
(paren
l_int|0xFF000000
)paren
)paren
op_eq
id|__constant_htonl
c_func
(paren
l_int|0xFF000000
)paren
suffix:semicolon
)brace
DECL|function|ipv6_addr_is_ll_all_nodes
r_static
r_inline
r_int
id|ipv6_addr_is_ll_all_nodes
c_func
(paren
r_const
r_struct
id|in6_addr
op_star
id|addr
)paren
(brace
r_return
(paren
id|addr-&gt;s6_addr32
(braket
l_int|0
)braket
op_eq
id|htonl
c_func
(paren
l_int|0xff020000
)paren
op_logical_and
id|addr-&gt;s6_addr32
(braket
l_int|1
)braket
op_eq
l_int|0
op_logical_and
id|addr-&gt;s6_addr32
(braket
l_int|2
)braket
op_eq
l_int|0
op_logical_and
id|addr-&gt;s6_addr32
(braket
l_int|3
)braket
op_eq
id|htonl
c_func
(paren
l_int|0x00000001
)paren
)paren
suffix:semicolon
)brace
DECL|function|ipv6_addr_is_ll_all_routers
r_static
r_inline
r_int
id|ipv6_addr_is_ll_all_routers
c_func
(paren
r_const
r_struct
id|in6_addr
op_star
id|addr
)paren
(brace
r_return
(paren
id|addr-&gt;s6_addr32
(braket
l_int|0
)braket
op_eq
id|htonl
c_func
(paren
l_int|0xff020000
)paren
op_logical_and
id|addr-&gt;s6_addr32
(braket
l_int|1
)braket
op_eq
l_int|0
op_logical_and
id|addr-&gt;s6_addr32
(braket
l_int|2
)braket
op_eq
l_int|0
op_logical_and
id|addr-&gt;s6_addr32
(braket
l_int|3
)braket
op_eq
id|htonl
c_func
(paren
l_int|0x00000002
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
