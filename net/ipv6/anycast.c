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
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/if_inet6.h&gt;
macro_line|#include &lt;net/ndisc.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
r_static
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
multiline_comment|/* Big ac list lock for all the sockets */
r_static
id|DEFINE_RWLOCK
c_func
(paren
id|ipv6_sk_ac_lock
)paren
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
r_if
c_cond
(paren
id|ipv6_addr_is_multicast
c_func
(paren
id|addr
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_chk_addr
c_func
(paren
id|addr
comma
l_int|NULL
comma
l_int|0
)paren
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
id|err
op_assign
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_goto
id|out_free_pac
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
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out_free_pac
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
r_if
c_cond
(paren
id|ifindex
)paren
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_else
id|err
op_assign
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
r_goto
id|out_dev_put
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
multiline_comment|/* XXX&n;&t; * For hosts, allow link-local or matching prefix anycasts.&n;&t; * This obviates the need for propagating anycast routes while&n;&t; * still allowing some non-router anycast participation.&n;&t; */
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
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_dev_put
suffix:semicolon
)brace
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
r_goto
id|out_dev_put
suffix:semicolon
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
id|out_dev_put
suffix:colon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out_free_pac
suffix:colon
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
id|err
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
l_int|NULL
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
id|ipv6_addr_equal
c_func
(paren
op_amp
id|pac-&gt;acl_addr
comma
id|addr
)paren
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
l_int|NULL
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
l_int|NULL
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
macro_line|#if 0
multiline_comment|/* The function is not used, which is funny. Apparently, author&n; * supposed to use it to filter out datagrams inside udp/raw but forgot.&n; *&n; * It is OK, anycasts are not special comparing to delivery to unicasts.&n; */
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
id|ipv6_addr_equal
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
macro_line|#endif
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
id|dst_release
c_func
(paren
op_amp
id|ac-&gt;aca_rt-&gt;u.dst
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
r_struct
id|rt6_info
op_star
id|rt
suffix:semicolon
r_int
id|err
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
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
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
id|ipv6_addr_equal
c_func
(paren
op_amp
id|aca-&gt;aca_addr
comma
id|addr
)paren
)paren
(brace
id|aca-&gt;aca_users
op_increment
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
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
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|rt
op_assign
id|addrconf_dst_alloc
c_func
(paren
id|idev
comma
id|addr
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|rt
)paren
)paren
(brace
id|kfree
c_func
(paren
id|aca
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|rt
)paren
suffix:semicolon
r_goto
id|out
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
id|aca-&gt;aca_rt
op_assign
id|rt
suffix:semicolon
id|aca-&gt;aca_users
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* aca_tstamp should be updated upon changes */
id|aca-&gt;aca_cstamp
op_assign
id|aca-&gt;aca_tstamp
op_assign
id|jiffies
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
id|spin_lock_init
c_func
(paren
op_amp
id|aca-&gt;aca_lock
)paren
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
id|dst_hold
c_func
(paren
op_amp
id|rt-&gt;u.dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip6_ins_rt
c_func
(paren
id|rt
comma
l_int|NULL
comma
l_int|NULL
)paren
)paren
id|dst_release
c_func
(paren
op_amp
id|rt-&gt;u.dst
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
id|out
suffix:colon
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
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;device anycast group decrement&n; */
DECL|function|__ipv6_dev_ac_dec
r_int
id|__ipv6_dev_ac_dec
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
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
comma
op_star
id|prev_aca
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
l_int|NULL
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
id|ipv6_addr_equal
c_func
(paren
op_amp
id|aca-&gt;aca_addr
comma
id|addr
)paren
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
id|idev
comma
op_amp
id|aca-&gt;aca_addr
)paren
suffix:semicolon
id|dst_hold
c_func
(paren
op_amp
id|aca-&gt;aca_rt-&gt;u.dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip6_del_rt
c_func
(paren
id|aca-&gt;aca_rt
comma
l_int|NULL
comma
l_int|NULL
)paren
)paren
id|dst_free
c_func
(paren
op_amp
id|aca-&gt;aca_rt-&gt;u.dst
)paren
suffix:semicolon
r_else
id|dst_release
c_func
(paren
op_amp
id|aca-&gt;aca_rt-&gt;u.dst
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
DECL|function|ipv6_dev_ac_dec
r_static
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
r_int
id|ret
suffix:semicolon
r_struct
id|inet6_dev
op_star
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
id|ret
op_assign
id|__ipv6_dev_ac_dec
c_func
(paren
id|idev
comma
id|addr
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|idev
)paren
suffix:semicolon
r_return
id|ret
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
id|ipv6_addr_equal
c_func
(paren
op_amp
id|aca-&gt;aca_addr
comma
id|addr
)paren
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
DECL|struct|ac6_iter_state
r_struct
id|ac6_iter_state
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|idev
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ac6_seq_private
mdefine_line|#define ac6_seq_private(seq)&t;((struct ac6_iter_state *)(seq)-&gt;private)
DECL|function|ac6_get_first
r_static
r_inline
r_struct
id|ifacaddr6
op_star
id|ac6_get_first
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
)paren
(brace
r_struct
id|ifacaddr6
op_star
id|im
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ac6_iter_state
op_star
id|state
op_assign
id|ac6_seq_private
c_func
(paren
id|seq
)paren
suffix:semicolon
r_for
c_loop
(paren
id|state-&gt;dev
op_assign
id|dev_base
comma
id|state-&gt;idev
op_assign
l_int|NULL
suffix:semicolon
id|state-&gt;dev
suffix:semicolon
id|state-&gt;dev
op_assign
id|state-&gt;dev-&gt;next
)paren
(brace
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
id|state-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idev
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
id|im
op_assign
id|idev-&gt;ac_list
suffix:semicolon
r_if
c_cond
(paren
id|im
)paren
(brace
id|state-&gt;idev
op_assign
id|idev
suffix:semicolon
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
r_return
id|im
suffix:semicolon
)brace
DECL|function|ac6_get_next
r_static
r_struct
id|ifacaddr6
op_star
id|ac6_get_next
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_struct
id|ifacaddr6
op_star
id|im
)paren
(brace
r_struct
id|ac6_iter_state
op_star
id|state
op_assign
id|ac6_seq_private
c_func
(paren
id|seq
)paren
suffix:semicolon
id|im
op_assign
id|im-&gt;aca_next
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|im
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|state-&gt;idev
op_ne
l_int|NULL
)paren
)paren
(brace
id|read_unlock_bh
c_func
(paren
op_amp
id|state-&gt;idev-&gt;lock
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|state-&gt;idev
)paren
suffix:semicolon
)brace
id|state-&gt;dev
op_assign
id|state-&gt;dev-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;dev
)paren
(brace
id|state-&gt;idev
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|state-&gt;idev
op_assign
id|in6_dev_get
c_func
(paren
id|state-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;idev
)paren
r_continue
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|state-&gt;idev-&gt;lock
)paren
suffix:semicolon
id|im
op_assign
id|state-&gt;idev-&gt;ac_list
suffix:semicolon
)brace
r_return
id|im
suffix:semicolon
)brace
DECL|function|ac6_get_idx
r_static
r_struct
id|ifacaddr6
op_star
id|ac6_get_idx
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|loff_t
id|pos
)paren
(brace
r_struct
id|ifacaddr6
op_star
id|im
op_assign
id|ac6_get_first
c_func
(paren
id|seq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|im
)paren
r_while
c_loop
(paren
id|pos
op_logical_and
(paren
id|im
op_assign
id|ac6_get_next
c_func
(paren
id|seq
comma
id|im
)paren
)paren
op_ne
l_int|NULL
)paren
op_decrement
id|pos
suffix:semicolon
r_return
id|pos
ques
c_cond
l_int|NULL
suffix:colon
id|im
suffix:semicolon
)brace
DECL|function|ac6_seq_start
r_static
r_void
op_star
id|ac6_seq_start
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|loff_t
op_star
id|pos
)paren
(brace
id|read_lock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_return
id|ac6_get_idx
c_func
(paren
id|seq
comma
op_star
id|pos
)paren
suffix:semicolon
)brace
DECL|function|ac6_seq_next
r_static
r_void
op_star
id|ac6_seq_next
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|ifacaddr6
op_star
id|im
suffix:semicolon
id|im
op_assign
id|ac6_get_next
c_func
(paren
id|seq
comma
id|v
)paren
suffix:semicolon
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|im
suffix:semicolon
)brace
DECL|function|ac6_seq_stop
r_static
r_void
id|ac6_seq_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|ac6_iter_state
op_star
id|state
op_assign
id|ac6_seq_private
c_func
(paren
id|seq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|state-&gt;idev
op_ne
l_int|NULL
)paren
)paren
(brace
id|read_unlock_bh
c_func
(paren
op_amp
id|state-&gt;idev-&gt;lock
)paren
suffix:semicolon
id|in6_dev_put
c_func
(paren
id|state-&gt;idev
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
)brace
DECL|function|ac6_seq_show
r_static
r_int
id|ac6_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|ifacaddr6
op_star
id|im
op_assign
(paren
r_struct
id|ifacaddr6
op_star
)paren
id|v
suffix:semicolon
r_struct
id|ac6_iter_state
op_star
id|state
op_assign
id|ac6_seq_private
c_func
(paren
id|seq
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-4d %-15s &quot;
l_string|&quot;%04x%04x%04x%04x%04x%04x%04x%04x &quot;
l_string|&quot;%5d&bslash;n&quot;
comma
id|state-&gt;dev-&gt;ifindex
comma
id|state-&gt;dev-&gt;name
comma
id|NIP6
c_func
(paren
id|im-&gt;aca_addr
)paren
comma
id|im-&gt;aca_users
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ac6_seq_ops
r_static
r_struct
id|seq_operations
id|ac6_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|ac6_seq_start
comma
dot
id|next
op_assign
id|ac6_seq_next
comma
dot
id|stop
op_assign
id|ac6_seq_stop
comma
dot
id|show
op_assign
id|ac6_seq_show
comma
)brace
suffix:semicolon
DECL|function|ac6_seq_open
r_static
r_int
id|ac6_seq_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|seq_file
op_star
id|seq
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_struct
id|ac6_iter_state
op_star
id|s
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|s
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_goto
id|out
suffix:semicolon
id|rc
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|ac6_seq_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|out_kfree
suffix:semicolon
id|seq
op_assign
id|file-&gt;private_data
suffix:semicolon
id|seq
op_member_access_from_pointer
r_private
op_assign
id|s
suffix:semicolon
id|memset
c_func
(paren
id|s
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|s
)paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|out_kfree
suffix:colon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|variable|ac6_seq_fops
r_static
r_struct
id|file_operations
id|ac6_seq_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|ac6_seq_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release_private
comma
)brace
suffix:semicolon
DECL|function|ac6_proc_init
r_int
id|__init
id|ac6_proc_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|proc_net_fops_create
c_func
(paren
l_string|&quot;anycast6&quot;
comma
id|S_IRUGO
comma
op_amp
id|ac6_seq_fops
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ac6_proc_exit
r_void
id|ac6_proc_exit
c_func
(paren
r_void
)paren
(brace
id|proc_net_remove
c_func
(paren
l_string|&quot;anycast6&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
