multiline_comment|/*&n; *&t;Multicast support for IPv6&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;$Id: mcast.c,v 1.40 2002/02/08 03:57:19 davem Exp $&n; *&n; *&t;Based on linux/ipv4/igmp.c and linux/ipv4/ip_sockglue.c &n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* Changes:&n; *&n; *&t;yoshfuji&t;: fix format of router-alert option&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
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
multiline_comment|/* Set to 3 to get tracing... */
DECL|macro|MCAST_DEBUG
mdefine_line|#define MCAST_DEBUG 2
macro_line|#if MCAST_DEBUG &gt;= 3
DECL|macro|MDBG
mdefine_line|#define MDBG(x) printk x
macro_line|#else
DECL|macro|MDBG
mdefine_line|#define MDBG(x)
macro_line|#endif
multiline_comment|/* Big mc list lock for all the sockets */
DECL|variable|ipv6_sk_mc_lock
r_static
id|rwlock_t
id|ipv6_sk_mc_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|igmp6_socket
r_static
r_struct
id|socket
op_star
id|igmp6_socket
suffix:semicolon
r_static
r_void
id|igmp6_join_group
c_func
(paren
r_struct
id|ifmcaddr6
op_star
id|ma
)paren
suffix:semicolon
r_static
r_void
id|igmp6_leave_group
c_func
(paren
r_struct
id|ifmcaddr6
op_star
id|ma
)paren
suffix:semicolon
r_static
r_void
id|igmp6_timer_handler
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|macro|IGMP6_UNSOLICITED_IVAL
mdefine_line|#define IGMP6_UNSOLICITED_IVAL&t;(10*HZ)
multiline_comment|/*&n; *&t;socket join on multicast group&n; */
DECL|function|ipv6_sock_mc_join
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
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ipv6_mc_socklist
op_star
id|mc_lst
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
id|err
suffix:semicolon
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
id|IPV6_ADDR_MULTICAST
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|mc_lst
op_assign
id|sock_kmalloc
c_func
(paren
id|sk
comma
r_sizeof
(paren
r_struct
id|ipv6_mc_socklist
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mc_lst
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|mc_lst-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|mc_lst-&gt;addr
comma
id|addr
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
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
id|mc_lst
comma
r_sizeof
(paren
op_star
id|mc_lst
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|mc_lst-&gt;ifindex
op_assign
id|dev-&gt;ifindex
suffix:semicolon
multiline_comment|/*&n;&t; *&t;now add/increase the group membership on the device&n;&t; */
id|err
op_assign
id|ipv6_dev_mc_inc
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
id|mc_lst
comma
r_sizeof
(paren
op_star
id|mc_lst
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
id|ipv6_sk_mc_lock
)paren
suffix:semicolon
id|mc_lst-&gt;next
op_assign
id|np-&gt;ipv6_mc_list
suffix:semicolon
id|np-&gt;ipv6_mc_list
op_assign
id|mc_lst
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ipv6_sk_mc_lock
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
multiline_comment|/*&n; *&t;socket leave on multicast group&n; */
DECL|function|ipv6_sock_mc_drop
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
id|ipv6_mc_socklist
op_star
id|mc_lst
comma
op_star
op_star
id|lnk
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|ipv6_sk_mc_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|lnk
op_assign
op_amp
id|np-&gt;ipv6_mc_list
suffix:semicolon
(paren
id|mc_lst
op_assign
op_star
id|lnk
)paren
op_ne
l_int|NULL
suffix:semicolon
id|lnk
op_assign
op_amp
id|mc_lst-&gt;next
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
id|mc_lst-&gt;ifindex
op_eq
id|ifindex
)paren
op_logical_and
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|mc_lst-&gt;addr
comma
id|addr
)paren
op_eq
l_int|0
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
op_star
id|lnk
op_assign
id|mc_lst-&gt;next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ipv6_sk_mc_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|dev_get_by_index
c_func
(paren
id|mc_lst-&gt;ifindex
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|ipv6_dev_mc_dec
c_func
(paren
id|dev
comma
op_amp
id|mc_lst-&gt;addr
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
id|mc_lst
comma
r_sizeof
(paren
op_star
id|mc_lst
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|ipv6_sk_mc_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
DECL|function|ipv6_sock_mc_close
r_void
id|ipv6_sock_mc_close
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
id|ipv6_mc_socklist
op_star
id|mc_lst
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|ipv6_sk_mc_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|mc_lst
op_assign
id|np-&gt;ipv6_mc_list
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|np-&gt;ipv6_mc_list
op_assign
id|mc_lst-&gt;next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|ipv6_sk_mc_lock
)paren
suffix:semicolon
id|dev
op_assign
id|dev_get_by_index
c_func
(paren
id|mc_lst-&gt;ifindex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|ipv6_dev_mc_dec
c_func
(paren
id|dev
comma
op_amp
id|mc_lst-&gt;addr
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
id|mc_lst
comma
r_sizeof
(paren
op_star
id|mc_lst
)paren
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|ipv6_sk_mc_lock
)paren
suffix:semicolon
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|ipv6_sk_mc_lock
)paren
suffix:semicolon
)brace
DECL|function|inet6_mc_check
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
id|ipv6_mc_socklist
op_star
id|mc
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|ipv6_sk_mc_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|mc
op_assign
id|np-&gt;ipv6_mc_list
suffix:semicolon
id|mc
suffix:semicolon
id|mc
op_assign
id|mc-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|mc-&gt;addr
comma
id|addr
)paren
op_eq
l_int|0
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|ipv6_sk_mc_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|ipv6_sk_mc_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ma_put
r_static
r_void
id|ma_put
c_func
(paren
r_struct
id|ifmcaddr6
op_star
id|mc
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|mc-&gt;mca_refcnt
)paren
)paren
(brace
id|in6_dev_put
c_func
(paren
id|mc-&gt;idev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mc
)paren
suffix:semicolon
)brace
)brace
DECL|function|igmp6_group_added
r_static
r_int
id|igmp6_group_added
c_func
(paren
r_struct
id|ifmcaddr6
op_star
id|mc
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|mc-&gt;idev-&gt;dev
suffix:semicolon
r_char
id|buf
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|mc-&gt;mca_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mc-&gt;mca_flags
op_amp
id|MAF_LOADED
)paren
)paren
(brace
id|mc-&gt;mca_flags
op_or_assign
id|MAF_LOADED
suffix:semicolon
r_if
c_cond
(paren
id|ndisc_mc_map
c_func
(paren
op_amp
id|mc-&gt;mca_addr
comma
id|buf
comma
id|dev
comma
l_int|0
)paren
op_eq
l_int|0
)paren
id|dev_mc_add
c_func
(paren
id|dev
comma
id|buf
comma
id|dev-&gt;addr_len
comma
l_int|0
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|mc-&gt;mca_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
id|igmp6_join_group
c_func
(paren
id|mc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|igmp6_group_dropped
r_static
r_int
id|igmp6_group_dropped
c_func
(paren
r_struct
id|ifmcaddr6
op_star
id|mc
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|mc-&gt;idev-&gt;dev
suffix:semicolon
r_char
id|buf
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|mc-&gt;mca_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mc-&gt;mca_flags
op_amp
id|MAF_LOADED
)paren
(brace
id|mc-&gt;mca_flags
op_and_assign
op_complement
id|MAF_LOADED
suffix:semicolon
r_if
c_cond
(paren
id|ndisc_mc_map
c_func
(paren
op_amp
id|mc-&gt;mca_addr
comma
id|buf
comma
id|dev
comma
l_int|0
)paren
op_eq
l_int|0
)paren
id|dev_mc_delete
c_func
(paren
id|dev
comma
id|buf
comma
id|dev-&gt;addr_len
comma
l_int|0
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|mc-&gt;mca_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
id|igmp6_leave_group
c_func
(paren
id|mc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;device multicast group inc (add if not found)&n; */
DECL|function|ipv6_dev_mc_inc
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
(brace
r_struct
id|ifmcaddr6
op_star
id|mc
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
id|mc
op_assign
id|idev-&gt;mc_list
suffix:semicolon
id|mc
suffix:semicolon
id|mc
op_assign
id|mc-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|mc-&gt;mca_addr
comma
id|addr
)paren
op_eq
l_int|0
)paren
(brace
id|mc-&gt;mca_users
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
id|mc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ifmcaddr6
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mc
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
id|mc
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ifmcaddr6
)paren
)paren
suffix:semicolon
id|mc-&gt;mca_timer.function
op_assign
id|igmp6_timer_handler
suffix:semicolon
id|mc-&gt;mca_timer.data
op_assign
(paren
r_int
r_int
)paren
id|mc
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|mc-&gt;mca_addr
comma
id|addr
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|mc-&gt;idev
op_assign
id|idev
suffix:semicolon
id|mc-&gt;mca_users
op_assign
l_int|1
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|mc-&gt;mca_refcnt
comma
l_int|2
)paren
suffix:semicolon
id|mc-&gt;mca_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|mc-&gt;next
op_assign
id|idev-&gt;mc_list
suffix:semicolon
id|idev-&gt;mc_list
op_assign
id|mc
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|igmp6_group_added
c_func
(paren
id|mc
)paren
suffix:semicolon
id|ma_put
c_func
(paren
id|mc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;device multicast group del&n; */
DECL|function|ipv6_dev_mc_dec
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
(brace
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
r_struct
id|ifmcaddr6
op_star
id|ma
comma
op_star
op_star
id|map
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
r_for
c_loop
(paren
id|map
op_assign
op_amp
id|idev-&gt;mc_list
suffix:semicolon
(paren
id|ma
op_assign
op_star
id|map
)paren
op_ne
l_int|NULL
suffix:semicolon
id|map
op_assign
op_amp
id|ma-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|ma-&gt;mca_addr
comma
id|addr
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|ma-&gt;mca_users
op_eq
l_int|0
)paren
(brace
op_star
id|map
op_assign
id|ma-&gt;next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|igmp6_group_dropped
c_func
(paren
id|ma
)paren
suffix:semicolon
id|ma_put
c_func
(paren
id|ma
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
multiline_comment|/*&n; *&t;check if the interface/address pair is valid&n; */
DECL|function|ipv6_chk_mcast_addr
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
id|addr
)paren
(brace
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
r_struct
id|ifmcaddr6
op_star
id|mc
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
id|mc
op_assign
id|idev-&gt;mc_list
suffix:semicolon
id|mc
suffix:semicolon
id|mc
op_assign
id|mc-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|mc-&gt;mca_addr
comma
id|addr
)paren
op_eq
l_int|0
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
r_return
l_int|1
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;IGMP handling (alias multicast ICMPv6 messages)&n; */
DECL|function|igmp6_group_queried
r_static
r_void
id|igmp6_group_queried
c_func
(paren
r_struct
id|ifmcaddr6
op_star
id|ma
comma
r_int
r_int
id|resptime
)paren
(brace
r_int
r_int
id|delay
op_assign
id|resptime
suffix:semicolon
multiline_comment|/* Do not start timer for addresses with link/host scope */
r_if
c_cond
(paren
id|ipv6_addr_type
c_func
(paren
op_amp
id|ma-&gt;mca_addr
)paren
op_amp
(paren
id|IPV6_ADDR_LINKLOCAL
op_or
id|IPV6_ADDR_LOOPBACK
)paren
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ma-&gt;mca_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|del_timer
c_func
(paren
op_amp
id|ma-&gt;mca_timer
)paren
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|ma-&gt;mca_refcnt
)paren
suffix:semicolon
id|delay
op_assign
id|ma-&gt;mca_timer.expires
op_minus
id|jiffies
suffix:semicolon
)brace
r_if
c_cond
(paren
id|delay
op_ge
id|resptime
)paren
(brace
r_if
c_cond
(paren
id|resptime
)paren
id|delay
op_assign
id|net_random
c_func
(paren
)paren
op_mod
id|resptime
suffix:semicolon
r_else
id|delay
op_assign
l_int|1
suffix:semicolon
)brace
id|ma-&gt;mca_timer.expires
op_assign
id|jiffies
op_plus
id|delay
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|ma-&gt;mca_timer
comma
id|jiffies
op_plus
id|delay
)paren
)paren
id|atomic_inc
c_func
(paren
op_amp
id|ma-&gt;mca_refcnt
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ma-&gt;mca_lock
)paren
suffix:semicolon
)brace
DECL|function|igmp6_event_query
r_int
id|igmp6_event_query
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ifmcaddr6
op_star
id|ma
suffix:semicolon
r_struct
id|in6_addr
op_star
id|addrp
suffix:semicolon
r_int
r_int
id|resptime
suffix:semicolon
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
r_struct
id|icmp6hdr
op_star
id|hdr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|hdr
op_assign
(paren
r_struct
id|icmp6hdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
multiline_comment|/* Drop queries with not link local source */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ipv6_addr_type
c_func
(paren
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
)paren
op_amp
id|IPV6_ADDR_LINKLOCAL
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|resptime
op_assign
id|ntohs
c_func
(paren
id|hdr-&gt;icmp6_maxdelay
)paren
suffix:semicolon
multiline_comment|/* Translate milliseconds to jiffies */
id|resptime
op_assign
(paren
id|resptime
op_lshift
l_int|10
)paren
op_div
(paren
l_int|1024000
op_div
id|HZ
)paren
suffix:semicolon
id|addrp
op_assign
(paren
r_struct
id|in6_addr
op_star
)paren
(paren
id|hdr
op_plus
l_int|1
)paren
suffix:semicolon
id|idev
op_assign
id|in6_dev_get
c_func
(paren
id|skb-&gt;dev
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
l_int|0
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipv6_addr_any
c_func
(paren
id|addrp
)paren
)paren
(brace
r_for
c_loop
(paren
id|ma
op_assign
id|idev-&gt;mc_list
suffix:semicolon
id|ma
suffix:semicolon
id|ma
op_assign
id|ma-&gt;next
)paren
id|igmp6_group_queried
c_func
(paren
id|ma
comma
id|resptime
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|ma
op_assign
id|idev-&gt;mc_list
suffix:semicolon
id|ma
suffix:semicolon
id|ma
op_assign
id|ma-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ipv6_addr_cmp
c_func
(paren
id|addrp
comma
op_amp
id|ma-&gt;mca_addr
)paren
op_eq
l_int|0
)paren
(brace
id|igmp6_group_queried
c_func
(paren
id|ma
comma
id|resptime
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|read_unlock
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
DECL|function|igmp6_event_report
r_int
id|igmp6_event_report
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ifmcaddr6
op_star
id|ma
suffix:semicolon
r_struct
id|in6_addr
op_star
id|addrp
suffix:semicolon
r_struct
id|inet6_dev
op_star
id|idev
suffix:semicolon
r_struct
id|icmp6hdr
op_star
id|hdr
suffix:semicolon
multiline_comment|/* Our own report looped back. Ignore it. */
r_if
c_cond
(paren
id|skb-&gt;pkt_type
op_eq
id|PACKET_LOOPBACK
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|hdr
op_assign
(paren
r_struct
id|icmp6hdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
multiline_comment|/* Drop reports with not link local source */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ipv6_addr_type
c_func
(paren
op_amp
id|skb-&gt;nh.ipv6h-&gt;saddr
)paren
op_amp
id|IPV6_ADDR_LINKLOCAL
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|addrp
op_assign
(paren
r_struct
id|in6_addr
op_star
)paren
(paren
id|hdr
op_plus
l_int|1
)paren
suffix:semicolon
id|idev
op_assign
id|in6_dev_get
c_func
(paren
id|skb-&gt;dev
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
multiline_comment|/*&n;&t; *&t;Cancel the timer for this group&n;&t; */
id|read_lock
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ma
op_assign
id|idev-&gt;mc_list
suffix:semicolon
id|ma
suffix:semicolon
id|ma
op_assign
id|ma-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ipv6_addr_cmp
c_func
(paren
op_amp
id|ma-&gt;mca_addr
comma
id|addrp
)paren
op_eq
l_int|0
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|ma-&gt;mca_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|del_timer
c_func
(paren
op_amp
id|ma-&gt;mca_timer
)paren
)paren
id|atomic_dec
c_func
(paren
op_amp
id|ma-&gt;mca_refcnt
)paren
suffix:semicolon
id|ma-&gt;mca_flags
op_and_assign
op_complement
(paren
id|MAF_LAST_REPORTER
op_or
id|MAF_TIMER_RUNNING
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ma-&gt;mca_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|read_unlock
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
DECL|function|igmp6_send
r_static
r_void
id|igmp6_send
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
id|type
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|igmp6_socket-&gt;sk
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|icmp6hdr
op_star
id|hdr
suffix:semicolon
r_struct
id|in6_addr
op_star
id|snd_addr
suffix:semicolon
r_struct
id|in6_addr
op_star
id|addrp
suffix:semicolon
r_struct
id|in6_addr
id|addr_buf
suffix:semicolon
r_struct
id|in6_addr
id|all_routers
suffix:semicolon
r_int
id|err
comma
id|len
comma
id|payload_len
comma
id|full_len
suffix:semicolon
id|u8
id|ra
(braket
l_int|8
)braket
op_assign
(brace
id|IPPROTO_ICMPV6
comma
l_int|0
comma
id|IPV6_TLV_ROUTERALERT
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
id|IPV6_TLV_PADN
comma
l_int|0
)brace
suffix:semicolon
id|snd_addr
op_assign
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|ICMPV6_MGM_REDUCTION
)paren
(brace
id|snd_addr
op_assign
op_amp
id|all_routers
suffix:semicolon
id|ipv6_addr_all_routers
c_func
(paren
op_amp
id|all_routers
)paren
suffix:semicolon
)brace
id|len
op_assign
r_sizeof
(paren
r_struct
id|icmp6hdr
)paren
op_plus
r_sizeof
(paren
r_struct
id|in6_addr
)paren
suffix:semicolon
id|payload_len
op_assign
id|len
op_plus
r_sizeof
(paren
id|ra
)paren
suffix:semicolon
id|full_len
op_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
op_plus
id|payload_len
suffix:semicolon
id|skb
op_assign
id|sock_alloc_send_skb
c_func
(paren
id|sk
comma
id|dev-&gt;hard_header_len
op_plus
id|full_len
op_plus
l_int|15
comma
l_int|0
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
(paren
id|dev-&gt;hard_header_len
op_plus
l_int|15
)paren
op_amp
op_complement
l_int|15
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;hard_header
)paren
(brace
r_int
r_char
id|ha
(braket
id|MAX_ADDR_LEN
)braket
suffix:semicolon
id|ndisc_mc_map
c_func
(paren
id|snd_addr
comma
id|ha
comma
id|dev
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|skb
comma
id|dev
comma
id|ETH_P_IPV6
comma
id|ha
comma
l_int|NULL
comma
id|full_len
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipv6_get_lladdr
c_func
(paren
id|dev
comma
op_amp
id|addr_buf
)paren
)paren
(brace
macro_line|#if MCAST_DEBUG &gt;= 1
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;igmp6: %s no linklocal address&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|out
suffix:semicolon
)brace
id|ip6_nd_hdr
c_func
(paren
id|sk
comma
id|skb
comma
id|dev
comma
op_amp
id|addr_buf
comma
id|snd_addr
comma
id|NEXTHDR_HOP
comma
id|payload_len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
id|ra
)paren
)paren
comma
id|ra
comma
r_sizeof
(paren
id|ra
)paren
)paren
suffix:semicolon
id|hdr
op_assign
(paren
r_struct
id|icmp6hdr
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|icmp6hdr
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|hdr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|icmp6hdr
)paren
)paren
suffix:semicolon
id|hdr-&gt;icmp6_type
op_assign
id|type
suffix:semicolon
id|addrp
op_assign
(paren
r_struct
id|in6_addr
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
id|addrp
comma
id|addr
)paren
suffix:semicolon
id|hdr-&gt;icmp6_cksum
op_assign
id|csum_ipv6_magic
c_func
(paren
op_amp
id|addr_buf
comma
id|snd_addr
comma
id|len
comma
id|IPPROTO_ICMPV6
comma
id|csum_partial
c_func
(paren
(paren
id|__u8
op_star
)paren
id|hdr
comma
id|len
comma
l_int|0
)paren
)paren
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|ICMPV6_MGM_REDUCTION
)paren
id|ICMP6_INC_STATS
c_func
(paren
id|Icmp6OutGroupMembReductions
)paren
suffix:semicolon
r_else
id|ICMP6_INC_STATS
c_func
(paren
id|Icmp6OutGroupMembResponses
)paren
suffix:semicolon
id|ICMP6_INC_STATS
c_func
(paren
id|Icmp6OutMsgs
)paren
suffix:semicolon
r_return
suffix:semicolon
id|out
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|igmp6_join_group
r_static
r_void
id|igmp6_join_group
c_func
(paren
r_struct
id|ifmcaddr6
op_star
id|ma
)paren
(brace
r_int
r_int
id|delay
suffix:semicolon
r_int
id|addr_type
suffix:semicolon
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
op_amp
id|ma-&gt;mca_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr_type
op_amp
(paren
id|IPV6_ADDR_LINKLOCAL
op_or
id|IPV6_ADDR_LOOPBACK
)paren
)paren
)paren
r_return
suffix:semicolon
id|igmp6_send
c_func
(paren
op_amp
id|ma-&gt;mca_addr
comma
id|ma-&gt;idev-&gt;dev
comma
id|ICMPV6_MGM_REPORT
)paren
suffix:semicolon
id|delay
op_assign
id|net_random
c_func
(paren
)paren
op_mod
id|IGMP6_UNSOLICITED_IVAL
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|ma-&gt;mca_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|del_timer
c_func
(paren
op_amp
id|ma-&gt;mca_timer
)paren
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|ma-&gt;mca_refcnt
)paren
suffix:semicolon
id|delay
op_assign
id|ma-&gt;mca_timer.expires
op_minus
id|jiffies
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mod_timer
c_func
(paren
op_amp
id|ma-&gt;mca_timer
comma
id|jiffies
op_plus
id|delay
)paren
)paren
id|atomic_inc
c_func
(paren
op_amp
id|ma-&gt;mca_refcnt
)paren
suffix:semicolon
id|ma-&gt;mca_flags
op_or_assign
id|MAF_TIMER_RUNNING
op_or
id|MAF_LAST_REPORTER
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|ma-&gt;mca_lock
)paren
suffix:semicolon
)brace
DECL|function|igmp6_leave_group
r_static
r_void
id|igmp6_leave_group
c_func
(paren
r_struct
id|ifmcaddr6
op_star
id|ma
)paren
(brace
r_int
id|addr_type
suffix:semicolon
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
op_amp
id|ma-&gt;mca_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr_type
op_amp
id|IPV6_ADDR_LINKLOCAL
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ma-&gt;mca_flags
op_amp
id|MAF_LAST_REPORTER
)paren
id|igmp6_send
c_func
(paren
op_amp
id|ma-&gt;mca_addr
comma
id|ma-&gt;idev-&gt;dev
comma
id|ICMPV6_MGM_REDUCTION
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|ma-&gt;mca_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|del_timer
c_func
(paren
op_amp
id|ma-&gt;mca_timer
)paren
)paren
id|atomic_dec
c_func
(paren
op_amp
id|ma-&gt;mca_refcnt
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|ma-&gt;mca_lock
)paren
suffix:semicolon
)brace
DECL|function|igmp6_timer_handler
r_static
r_void
id|igmp6_timer_handler
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|ifmcaddr6
op_star
id|ma
op_assign
(paren
r_struct
id|ifmcaddr6
op_star
)paren
id|data
suffix:semicolon
id|igmp6_send
c_func
(paren
op_amp
id|ma-&gt;mca_addr
comma
id|ma-&gt;idev-&gt;dev
comma
id|ICMPV6_MGM_REPORT
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ma-&gt;mca_lock
)paren
suffix:semicolon
id|ma-&gt;mca_flags
op_or_assign
id|MAF_LAST_REPORTER
suffix:semicolon
id|ma-&gt;mca_flags
op_and_assign
op_complement
id|MAF_TIMER_RUNNING
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ma-&gt;mca_lock
)paren
suffix:semicolon
id|ma_put
c_func
(paren
id|ma
)paren
suffix:semicolon
)brace
multiline_comment|/* Device going down */
DECL|function|ipv6_mc_down
r_void
id|ipv6_mc_down
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
(brace
r_struct
id|ifmcaddr6
op_star
id|i
suffix:semicolon
multiline_comment|/* Withdraw multicast list */
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
id|i
op_assign
id|idev-&gt;mc_list
suffix:semicolon
id|i
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
id|igmp6_group_dropped
c_func
(paren
id|i
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Device going up */
DECL|function|ipv6_mc_up
r_void
id|ipv6_mc_up
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
(brace
r_struct
id|ifmcaddr6
op_star
id|i
suffix:semicolon
multiline_comment|/* Install multicast list, except for all-nodes (already installed) */
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
id|i
op_assign
id|idev-&gt;mc_list
suffix:semicolon
id|i
suffix:semicolon
id|i
op_assign
id|i-&gt;next
)paren
id|igmp6_group_added
c_func
(paren
id|i
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* IPv6 device initialization. */
DECL|function|ipv6_mc_init_dev
r_void
id|ipv6_mc_init_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
(brace
r_struct
id|in6_addr
id|maddr
suffix:semicolon
multiline_comment|/* Add all-nodes address. */
id|ipv6_addr_all_nodes
c_func
(paren
op_amp
id|maddr
)paren
suffix:semicolon
id|ipv6_dev_mc_inc
c_func
(paren
id|idev-&gt;dev
comma
op_amp
id|maddr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Device is about to be destroyed: clean up.&n; */
DECL|function|ipv6_mc_destroy_dev
r_void
id|ipv6_mc_destroy_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
(brace
r_struct
id|ifmcaddr6
op_star
id|i
suffix:semicolon
r_struct
id|in6_addr
id|maddr
suffix:semicolon
multiline_comment|/* Delete all-nodes address. */
id|ipv6_addr_all_nodes
c_func
(paren
op_amp
id|maddr
)paren
suffix:semicolon
id|ipv6_dev_mc_dec
c_func
(paren
id|idev-&gt;dev
comma
op_amp
id|maddr
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i
op_assign
id|idev-&gt;mc_list
)paren
op_ne
l_int|NULL
)paren
(brace
id|idev-&gt;mc_list
op_assign
id|i-&gt;next
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
id|igmp6_group_dropped
c_func
(paren
id|i
)paren
suffix:semicolon
id|ma_put
c_func
(paren
id|i
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
)brace
id|write_unlock_bh
c_func
(paren
op_amp
id|idev-&gt;lock
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|igmp6_read_proc
r_static
r_int
id|igmp6_read_proc
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
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
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
id|ifmcaddr6
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
id|idev-&gt;mc_list
suffix:semicolon
id|im
suffix:semicolon
id|im
op_assign
id|im-&gt;next
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
id|im-&gt;mca_addr.s6_addr
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
l_string|&quot; %5d %08X %ld&bslash;n&quot;
comma
id|im-&gt;mca_users
comma
id|im-&gt;mca_flags
comma
(paren
id|im-&gt;mca_flags
op_amp
id|MAF_TIMER_RUNNING
)paren
ques
c_cond
id|im-&gt;mca_timer.expires
op_minus
id|jiffies
suffix:colon
l_int|0
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
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
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
DECL|function|igmp6_init
r_int
id|__init
id|igmp6_init
c_func
(paren
r_struct
id|net_proto_family
op_star
id|ops
)paren
(brace
r_struct
id|ipv6_pinfo
op_star
id|np
suffix:semicolon
r_struct
id|sock
op_star
id|sk
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|sock_create
c_func
(paren
id|PF_INET6
comma
id|SOCK_RAW
comma
id|IPPROTO_ICMPV6
comma
op_amp
id|igmp6_socket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to initialize the IGMP6 control socket (err %d).&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
id|igmp6_socket
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* For safety. */
r_return
id|err
suffix:semicolon
)brace
id|sk
op_assign
id|igmp6_socket-&gt;sk
suffix:semicolon
id|sk-&gt;allocation
op_assign
id|GFP_ATOMIC
suffix:semicolon
id|sk-&gt;prot
op_member_access_from_pointer
id|unhash
c_func
(paren
id|sk
)paren
suffix:semicolon
id|np
op_assign
id|inet6_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
id|np-&gt;hop_limit
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|create_proc_read_entry
c_func
(paren
l_string|&quot;net/igmp6&quot;
comma
l_int|0
comma
l_int|0
comma
id|igmp6_read_proc
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|igmp6_cleanup
r_void
id|igmp6_cleanup
c_func
(paren
r_void
)paren
(brace
id|sock_release
c_func
(paren
id|igmp6_socket
)paren
suffix:semicolon
id|igmp6_socket
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* for safety */
macro_line|#ifdef CONFIG_PROC_FS
id|remove_proc_entry
c_func
(paren
l_string|&quot;net/igmp6&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
