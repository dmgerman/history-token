multiline_comment|/*&n; *&t;Anycast support for IPv6&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;David L Stevens (dlstevens@us.ibm.com)&n; *&n; *&t;based heavily on net/ipv6/mcast.c&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/if_inet6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
multiline_comment|/* Big ac list lock for all the sockets */
DECL|variable|ipv6_sk_ac_lock
r_static
id|rwlock_t
id|ipv6_sk_ac_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* XXX ip6_addr_match() and ip6_onlink() really belong in net/core.c */
r_static
r_int
DECL|function|ip6_addr_match
id|ip6_addr_match
c_func
(paren
r_struct
id|in6_addr
op_star
id|addr1
comma
r_struct
id|in6_addr
op_star
id|addr2
comma
r_int
id|prefix
)paren
(brace
id|__u32
id|mask
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|prefix
OG
l_int|128
op_logical_or
id|prefix
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|prefix
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|prefix
op_ge
l_int|32
)paren
id|mask
op_assign
op_complement
l_int|0
suffix:semicolon
r_else
id|mask
op_assign
id|htonl
c_func
(paren
op_complement
l_int|0
op_lshift
(paren
l_int|32
op_minus
id|prefix
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr1-&gt;s6_addr32
(braket
id|i
)braket
op_xor
id|addr2-&gt;s6_addr32
(braket
id|i
)braket
)paren
op_amp
id|mask
)paren
r_return
l_int|0
suffix:semicolon
id|prefix
op_sub_assign
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|prefix
op_le
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|ip6_onlink
id|ip6_onlink
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
(brace
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
r_struct
id|inet6_ifaddr
op_star
id|ifa
suffix:semicolon
r_int
id|onlink
suffix:semicolon
id|onlink
op_assign
l_int|0
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
id|__in6_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idev
)paren
(brace
id|read_lock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ifa
op_assign
id|idev-&gt;addr_list
suffix:semicolon
id|ifa
suffix:semicolon
id|ifa
op_assign
id|ifa-&gt;if_next
)paren
(brace
id|onlink
op_assign
id|ip6_addr_match
c_func
(paren
id|addr
comma
op_amp
id|ifa-&gt;addr
comma
id|ifa-&gt;prefix_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|onlink
)paren
r_break
suffix:semicolon
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|addrconf_lock
)paren
suffix:semicolon
r_return
id|onlink
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;socket join an anycast group&n; */
DECL|function|ipv6_sock_ac_join
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
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
r_struct
id|ipv6_ac_socklist
op_star
id|pac
suffix:semicolon
r_int
id|ishost
op_assign
op_logical_neg
id|ipv6_devconf.forwarding
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_addr_type
c_func
(paren
id|addr
)paren
op_amp
id|IPV6_ADDR_MULTICAST
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pac
op_assign
id|sock_kmalloc
c_func
(paren
id|sk
comma
r_sizeof
(paren
r_struct
id|ipv6_ac_socklist
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pac
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pac-&gt;acl_next
op_assign
l_int|NULL
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|pac-&gt;acl_addr
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ifindex
op_eq
l_int|0
)paren
(brace
r_struct
id|rt6_info
op_star
id|rt
suffix:semicolon
id|rt
op_assign
id|rt6_lookup
c_func
(paren
id|addr
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rt
)paren
(brace
id|dev
op_assign
id|rt-&gt;rt6i_dev
suffix:semicolon
id|dev_hold
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dst_release
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ishost
)paren
(brace
id|sock_kfree_s
c_func
(paren
id|sk
comma
id|pac
comma
r_sizeof
(paren
op_star
id|pac
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* router, no matching interface: just pick one */
id|dev
op_assign
id|dev_get_by_flags
c_func
(paren
id|IFF_UP
comma
id|IFF_UP
op_or
id|IFF_LOOPBACK
)paren
suffix:semicolon
)brace
)brace
r_else
id|dev
op_assign
id|dev_get_by_index
c_func
(paren
id|ifindex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|sock_kfree_s
c_func
(paren
id|sk
comma
id|pac
comma
r_sizeof
(paren
op_star
id|pac
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|idev
op_assign
id|in6_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idev
)paren
(brace
id|sock_kfree_s
c_func
(paren
id|sk
comma
id|pac
comma
r_sizeof
(paren
op_star
id|pac
)paren
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ifindex
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_else
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
multiline_comment|/* reset ishost, now that we have a specific device */
id|ishost
op_assign
op_logical_neg
id|idev-&gt;cnf.forwarding
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|idev
)paren
suffix:semicolon
id|pac-&gt;acl_ifindex
op_assign
id|dev-&gt;ifindex
suffix:semicolon
multiline_comment|/* XXX&n;&t; * For hosts, allow link-local or matching prefix anycasts.&n;&t; * This obviates the need for propagating anycast routes while&n;&t; * still allowing some non-router anycast participation.&n;&t; *&n;&t; * allow anyone to join anycasts that don&squot;t require a special route&n;&t; * and can&squot;t be spoofs of unicast addresses (reserved anycast only)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ip6_onlink
c_func
(paren
id|addr
comma
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|ishost
)paren
id|err
op_assign
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|sock_kfree_s
c_func
(paren
id|sk
comma
id|pac
comma
r_sizeof
(paren
op_star
id|pac
)paren
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|ipv6_addr_type
c_func
(paren
id|addr
)paren
op_amp
id|IPV6_ADDR_ANYCAST
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|err
op_assign
id|ipv6_dev_ac_inc
c_func
(paren
id|dev
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|sock_kfree_s
c_func
(paren
id|sk
comma
id|pac
comma
r_sizeof
(paren
op_star
id|pac
)paren
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|write_lock_bh
c_func
(paren
op_amp
id|ipv6_sk_ac_lock
)paren
suffix:semicolon
id|pac-&gt;acl_next
op_assign
id|np-&gt;ipv6_ac_list
suffix:semicolon
id|np-&gt;ipv6_ac_list
op_assign
id|pac
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ipv6_sk_ac_lock
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;socket leave an anycast group&n; */
DECL|function|ipv6_sock_ac_drop
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
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|ipv6_ac_socklist
op_star
id|pac
comma
op_star
id|prev_pac
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|ipv6_sk_ac_lock
)paren
suffix:semicolon
id|prev_pac
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|pac
op_assign
id|np-&gt;ipv6_ac_list
suffix:semicolon
id|pac
suffix:semicolon
id|pac
op_assign
id|pac-&gt;acl_next
)paren
(brace
r_if
c_cond
(paren
(paren
id|ifindex
op_eq
l_int|0
op_logical_or
id|pac-&gt;acl_ifindex
op_eq
id|ifindex
)paren
op_logical_and
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|pac-&gt;acl_addr
comma
id|addr
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|prev_pac
op_assign
id|pac
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pac
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|ipv6_sk_ac_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev_pac
)paren
id|prev_pac-&gt;acl_next
op_assign
id|pac-&gt;acl_next
suffix:semicolon
r_else
id|np-&gt;ipv6_ac_list
op_assign
id|pac-&gt;acl_next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ipv6_sk_ac_lock
)paren
suffix:semicolon
id|dev
op_assign
id|dev_get_by_index
c_func
(paren
id|pac-&gt;acl_ifindex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|ipv6_dev_ac_dec
c_func
(paren
id|dev
comma
op_amp
id|pac-&gt;acl_addr
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|sock_kfree_s
c_func
(paren
id|sk
comma
id|pac
comma
r_sizeof
(paren
op_star
id|pac
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipv6_sock_ac_close
r_void
id|ipv6_sock_ac_close
c_func
(paren
r_struct
id|sock
op_star
id|sk
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
id|net_device
op_star
id|dev
op_assign
l_int|0
suffix:semicolon
r_struct
id|ipv6_ac_socklist
op_star
id|pac
suffix:semicolon
r_int
id|prev_index
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|ipv6_sk_ac_lock
)paren
suffix:semicolon
id|pac
op_assign
id|np-&gt;ipv6_ac_list
suffix:semicolon
id|np-&gt;ipv6_ac_list
op_assign
l_int|0
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ipv6_sk_ac_lock
)paren
suffix:semicolon
id|prev_index
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|pac
)paren
(brace
r_struct
id|ipv6_ac_socklist
op_star
id|next
op_assign
id|pac-&gt;acl_next
suffix:semicolon
r_if
c_cond
(paren
id|pac-&gt;acl_ifindex
op_ne
id|prev_index
)paren
(brace
r_if
c_cond
(paren
id|dev
)paren
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev
op_assign
id|dev_get_by_index
c_func
(paren
id|pac-&gt;acl_ifindex
)paren
suffix:semicolon
id|prev_index
op_assign
id|pac-&gt;acl_ifindex
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev
)paren
id|ipv6_dev_ac_dec
c_func
(paren
id|dev
comma
op_amp
id|pac-&gt;acl_addr
)paren
suffix:semicolon
id|sock_kfree_s
c_func
(paren
id|sk
comma
id|pac
comma
r_sizeof
(paren
op_star
id|pac
)paren
)paren
suffix:semicolon
id|pac
op_assign
id|next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev
)paren
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|inet6_ac_check
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
(brace
r_struct
id|ipv6_ac_socklist
op_star
id|pac
suffix:semicolon
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
r_int
id|found
suffix:semicolon
id|found
op_assign
l_int|0
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|ipv6_sk_ac_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pac
op_assign
id|np-&gt;ipv6_ac_list
suffix:semicolon
id|pac
suffix:semicolon
id|pac
op_assign
id|pac-&gt;acl_next
)paren
(brace
r_if
c_cond
(paren
id|ifindex
op_logical_and
id|pac-&gt;acl_ifindex
op_ne
id|ifindex
)paren
r_continue
suffix:semicolon
id|found
op_assign
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|pac-&gt;acl_addr
comma
id|addr
)paren
op_eq
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|found
)paren
r_break
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|ipv6_sk_ac_lock
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
DECL|function|aca_put
r_static
r_void
id|aca_put
c_func
(paren
r_struct
id|ifacaddr6
op_star
id|ac
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|ac-&gt;aca_refcnt
)paren
)paren
(brace
id|in6_dev_put
c_func
(paren
id|ac-&gt;aca_idev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ac
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;device anycast group inc (add if not found)&n; */
DECL|function|ipv6_dev_ac_inc
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
(brace
r_struct
id|ifacaddr6
op_star
id|aca
suffix:semicolon
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
id|idev
op_assign
id|in6_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idev-&gt;dead
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|idev
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_for
c_loop
(paren
id|aca
op_assign
id|idev-&gt;ac_list
suffix:semicolon
id|aca
suffix:semicolon
id|aca
op_assign
id|aca-&gt;aca_next
)paren
(brace
r_if
c_cond
(paren
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|aca-&gt;aca_addr
comma
id|addr
)paren
op_eq
l_int|0
)paren
(brace
id|aca-&gt;aca_users
op_increment
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|idev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *&t;not found: create a new one.&n;&t; */
id|aca
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ifacaddr6
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aca
op_eq
l_int|NULL
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|idev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|aca
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ifacaddr6
)paren
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|aca-&gt;aca_addr
comma
id|addr
)paren
suffix:semicolon
id|aca-&gt;aca_idev
op_assign
id|idev
suffix:semicolon
id|aca-&gt;aca_users
op_assign
l_int|1
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|aca-&gt;aca_refcnt
comma
l_int|2
)paren
suffix:semicolon
id|aca-&gt;aca_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|aca-&gt;aca_next
op_assign
id|idev-&gt;ac_list
suffix:semicolon
id|idev-&gt;ac_list
op_assign
id|aca
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|ip6_rt_addr_add
c_func
(paren
op_amp
id|aca-&gt;aca_addr
comma
id|dev
)paren
suffix:semicolon
id|addrconf_join_solict
c_func
(paren
id|dev
comma
op_amp
id|aca-&gt;aca_addr
)paren
suffix:semicolon
id|aca_put
c_func
(paren
id|aca
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;device anycast group decrement&n; */
DECL|function|ipv6_dev_ac_dec
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
(brace
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
r_struct
id|ifacaddr6
op_star
id|aca
comma
op_star
id|prev_aca
suffix:semicolon
id|idev
op_assign
id|in6_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|prev_aca
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|aca
op_assign
id|idev-&gt;ac_list
suffix:semicolon
id|aca
suffix:semicolon
id|aca
op_assign
id|aca-&gt;aca_next
)paren
(brace
r_if
c_cond
(paren
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|aca-&gt;aca_addr
comma
id|addr
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|prev_aca
op_assign
id|aca
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|aca
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|idev
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_decrement
id|aca-&gt;aca_users
OG
l_int|0
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|idev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev_aca
)paren
id|prev_aca-&gt;aca_next
op_assign
id|aca-&gt;aca_next
suffix:semicolon
r_else
id|idev-&gt;ac_list
op_assign
id|aca-&gt;aca_next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|addrconf_leave_solict
c_func
(paren
id|dev
comma
op_amp
id|aca-&gt;aca_addr
)paren
suffix:semicolon
id|ip6_rt_addr_del
c_func
(paren
op_amp
id|aca-&gt;aca_addr
comma
id|dev
)paren
suffix:semicolon
id|aca_put
c_func
(paren
id|aca
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|idev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;check if the interface has this anycast address&n; */
DECL|function|ipv6_chk_acast_dev
r_static
r_int
id|ipv6_chk_acast_dev
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
(brace
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
r_struct
id|ifacaddr6
op_star
id|aca
suffix:semicolon
id|idev
op_assign
id|in6_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idev
)paren
(brace
id|read_lock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|aca
op_assign
id|idev-&gt;ac_list
suffix:semicolon
id|aca
suffix:semicolon
id|aca
op_assign
id|aca-&gt;aca_next
)paren
r_if
c_cond
(paren
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|aca-&gt;aca_addr
comma
id|addr
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|idev
)paren
suffix:semicolon
r_return
id|aca
op_ne
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;check if given interface (or any, if dev==0) has this anycast address&n; */
DECL|function|ipv6_chk_acast_addr
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
(brace
r_if
c_cond
(paren
id|dev
)paren
r_return
id|ipv6_chk_acast_dev
c_func
(paren
id|dev
comma
id|addr
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|dev_base
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
r_if
c_cond
(paren
id|ipv6_chk_acast_dev
c_func
(paren
id|dev
comma
id|addr
)paren
)paren
r_break
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_return
id|dev
op_ne
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|anycast6_get_info
r_int
id|anycast6_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
id|off_t
id|pos
op_assign
l_int|0
comma
id|begin
op_assign
l_int|0
suffix:semicolon
r_struct
id|ifacaddr6
op_star
id|im
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|dev_base
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
(brace
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|idev
op_assign
id|in6_dev_get
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|im
op_assign
id|idev-&gt;ac_list
suffix:semicolon
id|im
suffix:semicolon
id|im
op_assign
id|im-&gt;aca_next
)paren
(brace
r_int
id|i
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-4d %-15s &quot;
comma
id|dev-&gt;ifindex
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%02x&quot;
comma
id|im-&gt;aca_addr.s6_addr
(braket
id|i
)braket
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot; %5d&bslash;n&quot;
comma
id|im-&gt;aca_users
)paren
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
(brace
id|read_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|idev
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|idev
)paren
suffix:semicolon
)brace
id|done
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
(brace
id|len
op_assign
id|length
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif
eof
