multiline_comment|/*&n; *&t;PF_INET6 socket protocol family&n; *&t;Linux INET6 implementation &n; *&n; *&t;Authors:&n; *&t;Pedro Roque&t;&t;&lt;roque@di.fc.ul.pt&gt;&t;&n; *&n; *&t;Adapted from linux/net/ipv4/af_inet.c&n; *&n; *&t;$Id: af_inet6.c,v 1.66 2002/02/01 22:01:04 davem Exp $&n; *&n; * &t;Fixes:&n; *&t;piggy, Karl Knutson&t;:&t;Socket protocol table&n; * &t;Hideaki YOSHIFUJI&t;:&t;sin6_scope_id support&n; * &t;Arnaldo Melo&t;&t;: &t;check proc_net_create return, cleanups&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
macro_line|#include &lt;linux/brlock.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/ipip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/inet_common.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef MODULE
DECL|variable|unloadable
r_static
r_int
id|unloadable
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XX: Turn to one when all is ok within the&n;&t;&t;&t;      module for allowing unload */
macro_line|#endif
macro_line|#if defined(MODULE) &amp;&amp; LINUX_VERSION_CODE &gt; 0x20115
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Cast of dozens&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IPv6 protocol stack for Linux&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|unloadable
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* IPv6 procfs goodies... */
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_int
id|raw6_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tcp6_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|udp6_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|afinet6_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|afinet6_get_snmp
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SYSCTL
r_extern
r_void
id|ipv6_sysctl_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_sysctl_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef INET_REFCNT_DEBUG
DECL|variable|inet6_sock_nr
id|atomic_t
id|inet6_sock_nr
suffix:semicolon
macro_line|#endif
multiline_comment|/* Per protocol sock slabcache */
DECL|variable|tcp6_sk_cachep
id|kmem_cache_t
op_star
id|tcp6_sk_cachep
suffix:semicolon
DECL|variable|udp6_sk_cachep
id|kmem_cache_t
op_star
id|udp6_sk_cachep
suffix:semicolon
DECL|variable|raw6_sk_cachep
id|kmem_cache_t
op_star
id|raw6_sk_cachep
suffix:semicolon
multiline_comment|/* The inetsw table contains everything that inet_create needs to&n; * build a new socket.&n; */
DECL|variable|inetsw6
r_struct
id|list_head
id|inetsw6
(braket
id|SOCK_MAX
)braket
suffix:semicolon
DECL|function|inet6_sock_destruct
r_static
r_void
id|inet6_sock_destruct
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
id|inet_sock_destruct
c_func
(paren
id|sk
)paren
suffix:semicolon
macro_line|#ifdef INET_REFCNT_DEBUG
id|atomic_dec
c_func
(paren
op_amp
id|inet6_sock_nr
)paren
suffix:semicolon
macro_line|#endif
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|inet6_sk_slab
r_static
id|__inline__
id|kmem_cache_t
op_star
id|inet6_sk_slab
c_func
(paren
r_int
id|protocol
)paren
(brace
id|kmem_cache_t
op_star
id|rc
op_assign
id|tcp6_sk_cachep
suffix:semicolon
r_if
c_cond
(paren
id|protocol
op_eq
id|IPPROTO_UDP
)paren
id|rc
op_assign
id|udp6_sk_cachep
suffix:semicolon
r_else
r_if
c_cond
(paren
id|protocol
op_eq
id|IPPROTO_RAW
)paren
id|rc
op_assign
id|raw6_sk_cachep
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|inet6_sk_size
r_static
id|__inline__
r_int
id|inet6_sk_size
c_func
(paren
r_int
id|protocol
)paren
(brace
r_int
id|rc
op_assign
r_sizeof
(paren
r_struct
id|tcp6_sock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|protocol
op_eq
id|IPPROTO_UDP
)paren
id|rc
op_assign
r_sizeof
(paren
r_struct
id|udp6_sock
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|protocol
op_eq
id|IPPROTO_RAW
)paren
id|rc
op_assign
r_sizeof
(paren
r_struct
id|raw6_sock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|inet6_sk_generic
r_static
id|__inline__
r_struct
id|ipv6_pinfo
op_star
id|inet6_sk_generic
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
id|rc
op_assign
(paren
op_amp
(paren
(paren
r_struct
id|tcp6_sock
op_star
)paren
id|sk
)paren
op_member_access_from_pointer
id|inet6
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;protocol
op_eq
id|IPPROTO_UDP
)paren
id|rc
op_assign
(paren
op_amp
(paren
(paren
r_struct
id|udp6_sock
op_star
)paren
id|sk
)paren
op_member_access_from_pointer
id|inet6
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sk-&gt;protocol
op_eq
id|IPPROTO_RAW
)paren
id|rc
op_assign
(paren
op_amp
(paren
(paren
r_struct
id|raw6_sock
op_star
)paren
id|sk
)paren
op_member_access_from_pointer
id|inet6
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|inet6_create
r_static
r_int
id|inet6_create
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|protocol
)paren
(brace
r_struct
id|inet_opt
op_star
id|inet
suffix:semicolon
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
r_struct
id|tcp6_sock
op_star
id|tcp6sk
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|inet_protosw
op_star
id|answer
suffix:semicolon
id|sk
op_assign
id|sk_alloc
c_func
(paren
id|PF_INET6
comma
id|GFP_KERNEL
comma
id|inet6_sk_size
c_func
(paren
id|protocol
)paren
comma
id|inet6_sk_slab
c_func
(paren
id|protocol
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
r_goto
id|do_oom
suffix:semicolon
multiline_comment|/* Look for the requested type/protocol pair. */
id|answer
op_assign
l_int|NULL
suffix:semicolon
id|br_read_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|inetsw6
(braket
id|sock-&gt;type
)braket
)paren
(brace
id|answer
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|inet_protosw
comma
id|list
)paren
suffix:semicolon
multiline_comment|/* Check the non-wild match. */
r_if
c_cond
(paren
id|protocol
op_eq
id|answer-&gt;protocol
)paren
(brace
r_if
c_cond
(paren
id|protocol
op_ne
id|IPPROTO_IP
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Check for the two wild cases. */
r_if
c_cond
(paren
id|IPPROTO_IP
op_eq
id|protocol
)paren
(brace
id|protocol
op_assign
id|answer-&gt;protocol
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|IPPROTO_IP
op_eq
id|answer-&gt;protocol
)paren
r_break
suffix:semicolon
)brace
id|answer
op_assign
l_int|NULL
suffix:semicolon
)brace
id|br_read_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|answer
)paren
r_goto
id|free_and_badtype
suffix:semicolon
r_if
c_cond
(paren
id|answer-&gt;capability
OG
l_int|0
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|answer-&gt;capability
)paren
)paren
r_goto
id|free_and_badperm
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|protocol
)paren
r_goto
id|free_and_noproto
suffix:semicolon
id|sock-&gt;ops
op_assign
id|answer-&gt;ops
suffix:semicolon
id|sock_init_data
c_func
(paren
id|sock
comma
id|sk
)paren
suffix:semicolon
id|sk-&gt;prot
op_assign
id|answer-&gt;prot
suffix:semicolon
id|sk-&gt;no_check
op_assign
id|answer-&gt;no_check
suffix:semicolon
r_if
c_cond
(paren
id|INET_PROTOSW_REUSE
op_amp
id|answer-&gt;flags
)paren
id|sk-&gt;reuse
op_assign
l_int|1
suffix:semicolon
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SOCK_RAW
op_eq
id|sock-&gt;type
)paren
(brace
id|inet-&gt;num
op_assign
id|protocol
suffix:semicolon
r_if
c_cond
(paren
id|IPPROTO_RAW
op_eq
id|protocol
)paren
id|inet-&gt;hdrincl
op_assign
l_int|1
suffix:semicolon
)brace
id|sk-&gt;destruct
op_assign
id|inet6_sock_destruct
suffix:semicolon
id|sk-&gt;zapped
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;family
op_assign
id|PF_INET6
suffix:semicolon
id|sk-&gt;protocol
op_assign
id|protocol
suffix:semicolon
id|sk-&gt;backlog_rcv
op_assign
id|answer-&gt;prot-&gt;backlog_rcv
suffix:semicolon
id|tcp6sk
op_assign
(paren
r_struct
id|tcp6_sock
op_star
)paren
id|sk
suffix:semicolon
id|tcp6sk-&gt;pinet6
op_assign
id|np
op_assign
id|inet6_sk_generic
c_func
(paren
id|sk
)paren
suffix:semicolon
id|np-&gt;hop_limit
op_assign
op_minus
l_int|1
suffix:semicolon
id|np-&gt;mcast_hops
op_assign
op_minus
l_int|1
suffix:semicolon
id|np-&gt;mc_loop
op_assign
l_int|1
suffix:semicolon
id|np-&gt;pmtudisc
op_assign
id|IPV6_PMTUDISC_WANT
suffix:semicolon
multiline_comment|/* Init the ipv4 part of the socket since we can have sockets&n;&t; * using v6 API for ipv4.&n;&t; */
id|inet-&gt;ttl
op_assign
l_int|64
suffix:semicolon
id|inet-&gt;mc_loop
op_assign
l_int|1
suffix:semicolon
id|inet-&gt;mc_ttl
op_assign
l_int|1
suffix:semicolon
id|inet-&gt;mc_index
op_assign
l_int|0
suffix:semicolon
id|inet-&gt;mc_list
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ipv4_config.no_pmtu_disc
)paren
id|inet-&gt;pmtudisc
op_assign
id|IP_PMTUDISC_DONT
suffix:semicolon
r_else
id|inet-&gt;pmtudisc
op_assign
id|IP_PMTUDISC_WANT
suffix:semicolon
macro_line|#ifdef INET_REFCNT_DEBUG
id|atomic_inc
c_func
(paren
op_amp
id|inet6_sock_nr
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|inet_sock_nr
)paren
suffix:semicolon
macro_line|#endif
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|inet-&gt;num
)paren
(brace
multiline_comment|/* It assumes that any protocol which allows&n;&t;&t; * the user to assign a number at socket&n;&t;&t; * creation time automatically shares.&n;&t;&t; */
id|inet-&gt;sport
op_assign
id|ntohs
c_func
(paren
id|inet-&gt;num
)paren
suffix:semicolon
id|sk-&gt;prot
op_member_access_from_pointer
id|hash
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;prot-&gt;init
)paren
(brace
r_int
id|err
op_assign
id|sk-&gt;prot
op_member_access_from_pointer
id|init
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|inet_sock_release
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
id|free_and_badtype
suffix:colon
id|sk_free
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
op_minus
id|ESOCKTNOSUPPORT
suffix:semicolon
id|free_and_badperm
suffix:colon
id|sk_free
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
id|free_and_noproto
suffix:colon
id|sk_free
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
op_minus
id|EPROTONOSUPPORT
suffix:semicolon
id|do_oom
suffix:colon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
multiline_comment|/* bind for INET6 API */
DECL|function|inet6_bind
r_int
id|inet6_bind
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|uaddr
comma
r_int
id|addr_len
)paren
(brace
r_struct
id|sockaddr_in6
op_star
id|addr
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|uaddr
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
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
id|__u32
id|v4addr
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|snum
suffix:semicolon
r_int
id|addr_type
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* If the socket has its own bind function then use it. */
r_if
c_cond
(paren
id|sk-&gt;prot-&gt;bind
)paren
(brace
r_return
id|sk-&gt;prot
op_member_access_from_pointer
id|bind
c_func
(paren
id|sk
comma
id|uaddr
comma
id|addr_len
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr_len
OL
id|SIN6_LEN_RFC2133
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|addr_type
op_assign
id|ipv6_addr_type
c_func
(paren
op_amp
id|addr-&gt;sin6_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr_type
op_amp
id|IPV6_ADDR_MULTICAST
)paren
op_logical_and
id|sock-&gt;type
op_eq
id|SOCK_STREAM
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Check if the address belongs to the host. */
r_if
c_cond
(paren
id|addr_type
op_eq
id|IPV6_ADDR_MAPPED
)paren
(brace
id|v4addr
op_assign
id|addr-&gt;sin6_addr.s6_addr32
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|inet_addr_type
c_func
(paren
id|v4addr
)paren
op_ne
id|RTN_LOCAL
)paren
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|addr_type
op_ne
id|IPV6_ADDR_ANY
)paren
(brace
multiline_comment|/* ipv4 addr of the socket is invalid.  Only the&n;&t;&t;&t; * unpecified and mapped address have a v4 equivalent.&n;&t;&t;&t; */
id|v4addr
op_assign
id|LOOPBACK4_IPV6
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|addr_type
op_amp
id|IPV6_ADDR_MULTICAST
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ipv6_chk_addr
c_func
(paren
op_amp
id|addr-&gt;sin6_addr
comma
l_int|NULL
)paren
)paren
r_return
op_minus
id|EADDRNOTAVAIL
suffix:semicolon
)brace
)brace
)brace
id|snum
op_assign
id|ntohs
c_func
(paren
id|addr-&gt;sin6_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snum
op_logical_and
id|snum
OL
id|PROT_SOCK
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_BIND_SERVICE
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
multiline_comment|/* Check these errors (active socket, double bind). */
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|TCP_CLOSE
op_logical_or
id|inet-&gt;num
)paren
(brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr_type
op_amp
id|IPV6_ADDR_LINKLOCAL
)paren
(brace
r_if
c_cond
(paren
id|addr_len
op_ge
r_sizeof
(paren
r_struct
id|sockaddr_in6
)paren
op_logical_and
id|addr-&gt;sin6_scope_id
)paren
(brace
multiline_comment|/* Override any existing binding, if another one&n;&t;&t;&t; * is supplied by user.&n;&t;&t;&t; */
id|sk-&gt;bound_dev_if
op_assign
id|addr-&gt;sin6_scope_id
suffix:semicolon
)brace
multiline_comment|/* Binding to link-local address requires an interface */
r_if
c_cond
(paren
id|sk-&gt;bound_dev_if
op_eq
l_int|0
)paren
(brace
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
id|inet-&gt;rcv_saddr
op_assign
id|v4addr
suffix:semicolon
id|inet-&gt;saddr
op_assign
id|v4addr
suffix:semicolon
id|ipv6_addr_copy
c_func
(paren
op_amp
id|np-&gt;rcv_saddr
comma
op_amp
id|addr-&gt;sin6_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|addr_type
op_amp
id|IPV6_ADDR_MULTICAST
)paren
)paren
id|ipv6_addr_copy
c_func
(paren
op_amp
id|np-&gt;saddr
comma
op_amp
id|addr-&gt;sin6_addr
)paren
suffix:semicolon
multiline_comment|/* Make sure we are allowed to bind here. */
r_if
c_cond
(paren
id|sk-&gt;prot
op_member_access_from_pointer
id|get_port
c_func
(paren
id|sk
comma
id|snum
)paren
op_ne
l_int|0
)paren
(brace
id|inet-&gt;rcv_saddr
op_assign
id|inet-&gt;saddr
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|np-&gt;rcv_saddr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|np-&gt;saddr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
op_minus
id|EADDRINUSE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr_type
op_ne
id|IPV6_ADDR_ANY
)paren
id|sk-&gt;userlocks
op_or_assign
id|SOCK_BINDADDR_LOCK
suffix:semicolon
r_if
c_cond
(paren
id|snum
)paren
id|sk-&gt;userlocks
op_or_assign
id|SOCK_BINDPORT_LOCK
suffix:semicolon
id|inet-&gt;sport
op_assign
id|ntohs
c_func
(paren
id|inet-&gt;num
)paren
suffix:semicolon
id|inet-&gt;dport
op_assign
l_int|0
suffix:semicolon
id|inet-&gt;daddr
op_assign
l_int|0
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inet6_release
r_int
id|inet6_release
c_func
(paren
r_struct
id|socket
op_star
id|sock
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Free mc lists */
id|ipv6_sock_mc_close
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|inet_release
c_func
(paren
id|sock
)paren
suffix:semicolon
)brace
DECL|function|inet6_destroy_sock
r_int
id|inet6_destroy_sock
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
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|ipv6_txoptions
op_star
id|opt
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Release destination entry&n;&t; */
id|sk_dst_reset
c_func
(paren
id|sk
)paren
suffix:semicolon
multiline_comment|/* Release rx options */
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|xchg
c_func
(paren
op_amp
id|np-&gt;pktoptions
comma
l_int|NULL
)paren
)paren
op_ne
l_int|NULL
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* Free flowlabels */
id|fl6_free_socklist
c_func
(paren
id|sk
)paren
suffix:semicolon
multiline_comment|/* Free tx options */
r_if
c_cond
(paren
(paren
id|opt
op_assign
id|xchg
c_func
(paren
op_amp
id|np-&gt;opt
comma
l_int|NULL
)paren
)paren
op_ne
l_int|NULL
)paren
id|sock_kfree_s
c_func
(paren
id|sk
comma
id|opt
comma
id|opt-&gt;tot_len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This does both peername and sockname.&n; */
DECL|function|inet6_getname
r_int
id|inet6_getname
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|uaddr
comma
r_int
op_star
id|uaddr_len
comma
r_int
id|peer
)paren
(brace
r_struct
id|sockaddr_in6
op_star
id|sin
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|uaddr
suffix:semicolon
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_struct
id|inet_opt
op_star
id|inet
op_assign
id|inet_sk
c_func
(paren
id|sk
)paren
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
id|sin-&gt;sin6_family
op_assign
id|AF_INET6
suffix:semicolon
id|sin-&gt;sin6_flowinfo
op_assign
l_int|0
suffix:semicolon
id|sin-&gt;sin6_scope_id
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|peer
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|inet-&gt;dport
)paren
r_return
op_minus
id|ENOTCONN
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
l_int|1
op_lshift
id|sk-&gt;state
)paren
op_amp
(paren
id|TCPF_CLOSE
op_or
id|TCPF_SYN_SENT
)paren
)paren
op_logical_and
id|peer
op_eq
l_int|1
)paren
r_return
op_minus
id|ENOTCONN
suffix:semicolon
id|sin-&gt;sin6_port
op_assign
id|inet-&gt;dport
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|sin-&gt;sin6_addr
comma
op_amp
id|np-&gt;daddr
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
id|np-&gt;sndflow
)paren
id|sin-&gt;sin6_flowinfo
op_assign
id|np-&gt;flow_label
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ipv6_addr_type
c_func
(paren
op_amp
id|np-&gt;rcv_saddr
)paren
op_eq
id|IPV6_ADDR_ANY
)paren
id|memcpy
c_func
(paren
op_amp
id|sin-&gt;sin6_addr
comma
op_amp
id|np-&gt;saddr
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
op_amp
id|sin-&gt;sin6_addr
comma
op_amp
id|np-&gt;rcv_saddr
comma
r_sizeof
(paren
r_struct
id|in6_addr
)paren
)paren
suffix:semicolon
id|sin-&gt;sin6_port
op_assign
id|inet-&gt;sport
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipv6_addr_type
c_func
(paren
op_amp
id|sin-&gt;sin6_addr
)paren
op_amp
id|IPV6_ADDR_LINKLOCAL
)paren
id|sin-&gt;sin6_scope_id
op_assign
id|sk-&gt;bound_dev_if
suffix:semicolon
op_star
id|uaddr_len
op_assign
r_sizeof
(paren
op_star
id|sin
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inet6_ioctl
r_int
id|inet6_ioctl
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_int
id|pid
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FIOSETOWN
suffix:colon
r_case
id|SIOCSPGRP
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|pid
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* see sock_no_fcntl */
r_if
c_cond
(paren
id|current-&gt;pid
op_ne
id|pid
op_logical_and
id|current-&gt;pgrp
op_ne
op_minus
id|pid
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
id|sk-&gt;proc
op_assign
id|pid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|FIOGETOWN
suffix:colon
r_case
id|SIOCGPGRP
suffix:colon
r_return
id|put_user
c_func
(paren
id|sk-&gt;proc
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SIOCGSTAMP
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;stamp.tv_sec
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|err
op_assign
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|sk-&gt;stamp
comma
r_sizeof
(paren
r_struct
id|timeval
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SIOCADDRT
suffix:colon
r_case
id|SIOCDELRT
suffix:colon
r_return
id|ipv6_route_ioctl
c_func
(paren
id|cmd
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SIOCSIFADDR
suffix:colon
r_return
id|addrconf_add_ifaddr
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SIOCDIFADDR
suffix:colon
r_return
id|addrconf_del_ifaddr
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SIOCSIFDSTADDR
suffix:colon
r_return
id|addrconf_set_dstaddr
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
(paren
id|cmd
op_ge
id|SIOCDEVPRIVATE
)paren
op_logical_and
(paren
id|cmd
op_le
(paren
id|SIOCDEVPRIVATE
op_plus
l_int|15
)paren
)paren
)paren
r_return
id|dev_ioctl
c_func
(paren
id|cmd
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;prot-&gt;ioctl
op_eq
l_int|0
op_logical_or
(paren
id|err
op_assign
id|sk-&gt;prot
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|sk
comma
id|cmd
comma
id|arg
)paren
)paren
op_eq
op_minus
id|ENOIOCTLCMD
)paren
(brace
r_return
id|dev_ioctl
c_func
(paren
id|cmd
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*NOTREACHED*/
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|inet6_stream_ops
r_struct
id|proto_ops
id|inet6_stream_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_INET6
comma
dot
id|release
op_assign
id|inet6_release
comma
dot
id|bind
op_assign
id|inet6_bind
comma
dot
id|connect
op_assign
id|inet_stream_connect
comma
multiline_comment|/* ok&t;&t;*/
dot
id|socketpair
op_assign
id|sock_no_socketpair
comma
multiline_comment|/* a do nothing&t;*/
dot
id|accept
op_assign
id|inet_accept
comma
multiline_comment|/* ok&t;&t;*/
dot
id|getname
op_assign
id|inet6_getname
comma
dot
id|poll
op_assign
id|tcp_poll
comma
multiline_comment|/* ok&t;&t;*/
dot
id|ioctl
op_assign
id|inet6_ioctl
comma
multiline_comment|/* must change  */
dot
id|listen
op_assign
id|inet_listen
comma
multiline_comment|/* ok&t;&t;*/
dot
id|shutdown
op_assign
id|inet_shutdown
comma
multiline_comment|/* ok&t;&t;*/
dot
id|setsockopt
op_assign
id|inet_setsockopt
comma
multiline_comment|/* ok&t;&t;*/
dot
id|getsockopt
op_assign
id|inet_getsockopt
comma
multiline_comment|/* ok&t;&t;*/
dot
id|sendmsg
op_assign
id|inet_sendmsg
comma
multiline_comment|/* ok&t;&t;*/
dot
id|recvmsg
op_assign
id|inet_recvmsg
comma
multiline_comment|/* ok&t;&t;*/
dot
id|mmap
op_assign
id|sock_no_mmap
comma
dot
id|sendpage
op_assign
id|tcp_sendpage
)brace
suffix:semicolon
DECL|variable|inet6_dgram_ops
r_struct
id|proto_ops
id|inet6_dgram_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_INET6
comma
dot
id|release
op_assign
id|inet6_release
comma
dot
id|bind
op_assign
id|inet6_bind
comma
dot
id|connect
op_assign
id|inet_dgram_connect
comma
multiline_comment|/* ok&t;&t;*/
dot
id|socketpair
op_assign
id|sock_no_socketpair
comma
multiline_comment|/* a do nothing&t;*/
dot
id|accept
op_assign
id|sock_no_accept
comma
multiline_comment|/* a do nothing&t;*/
dot
id|getname
op_assign
id|inet6_getname
comma
dot
id|poll
op_assign
id|datagram_poll
comma
multiline_comment|/* ok&t;&t;*/
dot
id|ioctl
op_assign
id|inet6_ioctl
comma
multiline_comment|/* must change  */
dot
id|listen
op_assign
id|sock_no_listen
comma
multiline_comment|/* ok&t;&t;*/
dot
id|shutdown
op_assign
id|inet_shutdown
comma
multiline_comment|/* ok&t;&t;*/
dot
id|setsockopt
op_assign
id|inet_setsockopt
comma
multiline_comment|/* ok&t;&t;*/
dot
id|getsockopt
op_assign
id|inet_getsockopt
comma
multiline_comment|/* ok&t;&t;*/
dot
id|sendmsg
op_assign
id|inet_sendmsg
comma
multiline_comment|/* ok&t;&t;*/
dot
id|recvmsg
op_assign
id|inet_recvmsg
comma
multiline_comment|/* ok&t;&t;*/
dot
id|mmap
op_assign
id|sock_no_mmap
comma
dot
id|sendpage
op_assign
id|sock_no_sendpage
comma
)brace
suffix:semicolon
DECL|variable|inet6_family_ops
r_struct
id|net_proto_family
id|inet6_family_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_INET6
comma
dot
id|create
op_assign
id|inet6_create
comma
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|ipv6_unload
r_int
id|ipv6_unload
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|unloadable
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* We keep internally 3 raw sockets */
r_return
id|atomic_read
c_func
(paren
op_amp
(paren
id|__this_module.uc.usecount
)paren
)paren
op_minus
l_int|3
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(MODULE) &amp;&amp; defined(CONFIG_SYSCTL)
r_extern
r_void
id|ipv6_sysctl_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ipv6_sysctl_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|rawv6_protosw
r_static
r_struct
id|inet_protosw
id|rawv6_protosw
op_assign
(brace
dot
id|type
op_assign
id|SOCK_RAW
comma
dot
id|protocol
op_assign
id|IPPROTO_IP
comma
multiline_comment|/* wild card */
dot
id|prot
op_assign
op_amp
id|rawv6_prot
comma
dot
id|ops
op_assign
op_amp
id|inet6_dgram_ops
comma
dot
id|capability
op_assign
id|CAP_NET_RAW
comma
dot
id|no_check
op_assign
id|UDP_CSUM_DEFAULT
comma
dot
id|flags
op_assign
id|INET_PROTOSW_REUSE
comma
)brace
suffix:semicolon
DECL|macro|INETSW6_ARRAY_LEN
mdefine_line|#define INETSW6_ARRAY_LEN (sizeof(inetsw6_array) / sizeof(struct inet_protosw))
r_void
DECL|function|inet6_register_protosw
id|inet6_register_protosw
c_func
(paren
r_struct
id|inet_protosw
op_star
id|p
)paren
(brace
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|inet_protosw
op_star
id|answer
suffix:semicolon
r_int
id|protocol
op_assign
id|p-&gt;protocol
suffix:semicolon
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;type
OG
id|SOCK_MAX
)paren
r_goto
id|out_illegal
suffix:semicolon
multiline_comment|/* If we are trying to override a permanent protocol, bail. */
id|answer
op_assign
l_int|NULL
suffix:semicolon
id|list_for_each
c_func
(paren
id|lh
comma
op_amp
id|inetsw6
(braket
id|p-&gt;type
)braket
)paren
(brace
id|answer
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|inet_protosw
comma
id|list
)paren
suffix:semicolon
multiline_comment|/* Check only the non-wild match. */
r_if
c_cond
(paren
id|protocol
op_eq
id|answer-&gt;protocol
op_logical_and
(paren
id|INET_PROTOSW_PERMANENT
op_amp
id|answer-&gt;flags
)paren
)paren
r_break
suffix:semicolon
id|answer
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|answer
)paren
r_goto
id|out_permanent
suffix:semicolon
multiline_comment|/* Add to the BEGINNING so that we override any existing&n;&t; * entry.  This means that when we remove this entry, the&n;&t; * system automatically returns to the old behavior.&n;&t; */
id|list_add
c_func
(paren
op_amp
id|p-&gt;list
comma
op_amp
id|inetsw6
(braket
id|p-&gt;type
)braket
)paren
suffix:semicolon
id|out
suffix:colon
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
suffix:semicolon
id|out_permanent
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Attempt to override permanent protocol %d.&bslash;n&quot;
comma
id|protocol
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_illegal
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Ignoring attempt to register illegal socket type %d.&bslash;n&quot;
comma
id|p-&gt;type
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_void
DECL|function|inet6_unregister_protosw
id|inet6_unregister_protosw
c_func
(paren
r_struct
id|inet_protosw
op_star
id|p
)paren
(brace
id|inet_unregister_protosw
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|inet6_init
r_static
r_int
id|__init
id|inet6_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|sk_buff
op_star
id|dummy_skb
suffix:semicolon
r_struct
id|list_head
op_star
id|r
suffix:semicolon
r_int
id|err
suffix:semicolon
macro_line|#ifdef MODULE
r_if
c_cond
(paren
op_logical_neg
id|mod_member_present
c_func
(paren
op_amp
id|__this_module
comma
id|can_unload
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|__this_module.can_unload
op_assign
op_amp
id|ipv6_unload
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;IPv6 v0.8 for NET4.0&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|inet6_skb_parm
)paren
OG
r_sizeof
(paren
id|dummy_skb-&gt;cb
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;inet6_proto_init: size fault&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* allocate our sock slab caches */
id|tcp6_sk_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;tcp6_sock&quot;
comma
r_sizeof
(paren
r_struct
id|tcp6_sock
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|udp6_sk_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;udp6_sock&quot;
comma
r_sizeof
(paren
r_struct
id|udp6_sock
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|raw6_sk_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;raw6_sock&quot;
comma
r_sizeof
(paren
r_struct
id|raw6_sock
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tcp6_sk_cachep
op_logical_or
op_logical_neg
id|udp6_sk_cachep
op_logical_or
op_logical_neg
id|raw6_sk_cachep
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;%s: Can&squot;t create protocol sock SLAB &quot;
l_string|&quot;caches!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* Register the socket-side information for inet6_create.  */
r_for
c_loop
(paren
id|r
op_assign
op_amp
id|inetsw6
(braket
l_int|0
)braket
suffix:semicolon
id|r
OL
op_amp
id|inetsw6
(braket
id|SOCK_MAX
)braket
suffix:semicolon
op_increment
id|r
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
id|r
)paren
suffix:semicolon
)brace
multiline_comment|/* We MUST register RAW sockets before we create the ICMP6,&n;&t; * IGMP6, or NDISC control sockets.&n;&t; */
id|inet6_register_protosw
c_func
(paren
op_amp
id|rawv6_protosw
)paren
suffix:semicolon
multiline_comment|/* Register the family here so that the init calls below will&n;&t; * be able to create sockets. (?? is this dangerous ??)&n;&t; */
(paren
r_void
)paren
id|sock_register
c_func
(paren
op_amp
id|inet6_family_ops
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;ipngwg API draft makes clear that the correct semantics&n;&t; *&t;for TCP and UDP is to consider one TCP and UDP instance&n;&t; *&t;in a host availiable by both INET and INET6 APIs and&n;&t; *&t;able to communicate via both network protocols.&n;&t; */
macro_line|#if defined(MODULE) &amp;&amp; defined(CONFIG_SYSCTL)
id|ipv6_sysctl_register
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|err
op_assign
id|icmpv6_init
c_func
(paren
op_amp
id|inet6_family_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|icmp_fail
suffix:semicolon
id|err
op_assign
id|ndisc_init
c_func
(paren
op_amp
id|inet6_family_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|ndisc_fail
suffix:semicolon
id|err
op_assign
id|igmp6_init
c_func
(paren
op_amp
id|inet6_family_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|igmp_fail
suffix:semicolon
multiline_comment|/* Create /proc/foo6 entries. */
macro_line|#ifdef CONFIG_PROC_FS
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_create
c_func
(paren
l_string|&quot;raw6&quot;
comma
l_int|0
comma
id|raw6_get_info
)paren
)paren
r_goto
id|proc_raw6_fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_create
c_func
(paren
l_string|&quot;tcp6&quot;
comma
l_int|0
comma
id|tcp6_get_info
)paren
)paren
r_goto
id|proc_tcp6_fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_create
c_func
(paren
l_string|&quot;udp6&quot;
comma
l_int|0
comma
id|udp6_get_info
)paren
)paren
r_goto
id|proc_udp6_fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_create
c_func
(paren
l_string|&quot;sockstat6&quot;
comma
l_int|0
comma
id|afinet6_get_info
)paren
)paren
r_goto
id|proc_sockstat6_fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_create
c_func
(paren
l_string|&quot;snmp6&quot;
comma
l_int|0
comma
id|afinet6_get_snmp
)paren
)paren
r_goto
id|proc_snmp6_fail
suffix:semicolon
macro_line|#endif
id|ipv6_netdev_notif_init
c_func
(paren
)paren
suffix:semicolon
id|ipv6_packet_init
c_func
(paren
)paren
suffix:semicolon
id|ip6_route_init
c_func
(paren
)paren
suffix:semicolon
id|ip6_flowlabel_init
c_func
(paren
)paren
suffix:semicolon
id|addrconf_init
c_func
(paren
)paren
suffix:semicolon
id|sit_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Init v6 transport protocols. */
id|udpv6_init
c_func
(paren
)paren
suffix:semicolon
id|tcpv6_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|proc_snmp6_fail
suffix:colon
id|proc_net_remove
c_func
(paren
l_string|&quot;sockstat6&quot;
)paren
suffix:semicolon
id|proc_sockstat6_fail
suffix:colon
id|proc_net_remove
c_func
(paren
l_string|&quot;udp6&quot;
)paren
suffix:semicolon
id|proc_udp6_fail
suffix:colon
id|proc_net_remove
c_func
(paren
l_string|&quot;tcp6&quot;
)paren
suffix:semicolon
id|proc_tcp6_fail
suffix:colon
id|proc_net_remove
c_func
(paren
l_string|&quot;raw6&quot;
)paren
suffix:semicolon
id|proc_raw6_fail
suffix:colon
id|igmp6_cleanup
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|igmp_fail
suffix:colon
id|ndisc_cleanup
c_func
(paren
)paren
suffix:semicolon
id|ndisc_fail
suffix:colon
id|icmpv6_cleanup
c_func
(paren
)paren
suffix:semicolon
id|icmp_fail
suffix:colon
macro_line|#if defined(MODULE) &amp;&amp; defined(CONFIG_SYSCTL)
id|ipv6_sysctl_unregister
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|err
suffix:semicolon
)brace
DECL|variable|inet6_init
id|module_init
c_func
(paren
id|inet6_init
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|inet6_exit
r_static
r_void
id|inet6_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* First of all disallow new sockets creation. */
id|sock_unregister
c_func
(paren
id|PF_INET6
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|proc_net_remove
c_func
(paren
l_string|&quot;raw6&quot;
)paren
suffix:semicolon
id|proc_net_remove
c_func
(paren
l_string|&quot;tcp6&quot;
)paren
suffix:semicolon
id|proc_net_remove
c_func
(paren
l_string|&quot;udp6&quot;
)paren
suffix:semicolon
id|proc_net_remove
c_func
(paren
l_string|&quot;sockstat6&quot;
)paren
suffix:semicolon
id|proc_net_remove
c_func
(paren
l_string|&quot;snmp6&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Cleanup code parts. */
id|sit_cleanup
c_func
(paren
)paren
suffix:semicolon
id|ipv6_netdev_notif_cleanup
c_func
(paren
)paren
suffix:semicolon
id|ip6_flowlabel_cleanup
c_func
(paren
)paren
suffix:semicolon
id|addrconf_cleanup
c_func
(paren
)paren
suffix:semicolon
id|ip6_route_cleanup
c_func
(paren
)paren
suffix:semicolon
id|ipv6_packet_cleanup
c_func
(paren
)paren
suffix:semicolon
id|igmp6_cleanup
c_func
(paren
)paren
suffix:semicolon
id|ndisc_cleanup
c_func
(paren
)paren
suffix:semicolon
id|icmpv6_cleanup
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
id|ipv6_sysctl_unregister
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|inet6_exit
id|module_exit
c_func
(paren
id|inet6_exit
)paren
suffix:semicolon
macro_line|#endif /* MODULE */
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
