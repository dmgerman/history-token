multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;IPv4 Forwarding Information Base: FIB frontend.&n; *&n; * Version:&t;$Id: fib_frontend.c,v 1.26 2001/10/31 21:55:54 davem Exp $&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/ip_fib.h&gt;
DECL|macro|FFprint
mdefine_line|#define FFprint(a...) printk(KERN_DEBUG a)
macro_line|#ifndef CONFIG_IP_MULTIPLE_TABLES
DECL|macro|RT_TABLE_MIN
mdefine_line|#define RT_TABLE_MIN RT_TABLE_MAIN
DECL|variable|local_table
r_struct
id|fib_table
op_star
id|local_table
suffix:semicolon
DECL|variable|main_table
r_struct
id|fib_table
op_star
id|main_table
suffix:semicolon
macro_line|#else
DECL|macro|RT_TABLE_MIN
mdefine_line|#define RT_TABLE_MIN 1
DECL|variable|fib_tables
r_struct
id|fib_table
op_star
id|fib_tables
(braket
id|RT_TABLE_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|function|__fib_new_table
r_struct
id|fib_table
op_star
id|__fib_new_table
c_func
(paren
r_int
id|id
)paren
(brace
r_struct
id|fib_table
op_star
id|tb
suffix:semicolon
id|tb
op_assign
id|fib_hash_init
c_func
(paren
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tb
)paren
r_return
l_int|NULL
suffix:semicolon
id|fib_tables
(braket
id|id
)braket
op_assign
id|tb
suffix:semicolon
r_return
id|tb
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_IP_MULTIPLE_TABLES */
DECL|function|fib_flush
r_void
id|fib_flush
c_func
(paren
r_void
)paren
(brace
r_int
id|flushed
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MULTIPLE_TABLES
r_struct
id|fib_table
op_star
id|tb
suffix:semicolon
r_int
id|id
suffix:semicolon
r_for
c_loop
(paren
id|id
op_assign
id|RT_TABLE_MAX
suffix:semicolon
id|id
OG
l_int|0
suffix:semicolon
id|id
op_decrement
)paren
(brace
r_if
c_cond
(paren
(paren
id|tb
op_assign
id|fib_get_table
c_func
(paren
id|id
)paren
)paren
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|flushed
op_add_assign
id|tb
op_member_access_from_pointer
id|tb_flush
c_func
(paren
id|tb
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_IP_MULTIPLE_TABLES */
id|flushed
op_add_assign
id|main_table
op_member_access_from_pointer
id|tb_flush
c_func
(paren
id|main_table
)paren
suffix:semicolon
id|flushed
op_add_assign
id|local_table
op_member_access_from_pointer
id|tb_flush
c_func
(paren
id|local_table
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IP_MULTIPLE_TABLES */
r_if
c_cond
(paren
id|flushed
)paren
id|rt_cache_flush
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/* &n; *&t;Called from the PROCfs module. This outputs /proc/net/route.&n; *&n; *&t;It always works in backward compatibility mode.&n; *&t;The format of the file is not supposed to be changed.&n; */
r_static
r_int
DECL|function|fib_get_procinfo
id|fib_get_procinfo
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
r_int
id|first
op_assign
id|offset
op_div
l_int|128
suffix:semicolon
r_char
op_star
id|ptr
op_assign
id|buffer
suffix:semicolon
r_int
id|count
op_assign
(paren
id|length
op_plus
l_int|127
)paren
op_div
l_int|128
suffix:semicolon
r_int
id|len
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
op_mod
l_int|128
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|first
OL
l_int|0
)paren
(brace
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%-127s&bslash;n&quot;
comma
l_string|&quot;Iface&bslash;tDestination&bslash;tGateway &bslash;tFlags&bslash;tRefCnt&bslash;tUse&bslash;tMetric&bslash;tMask&bslash;t&bslash;tMTU&bslash;tWindow&bslash;tIRTT&quot;
)paren
suffix:semicolon
op_decrement
id|count
suffix:semicolon
id|ptr
op_add_assign
l_int|128
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|main_table
op_logical_and
id|count
OG
l_int|0
)paren
(brace
r_int
id|n
op_assign
id|main_table
op_member_access_from_pointer
id|tb_get_info
c_func
(paren
id|main_table
comma
id|ptr
comma
id|first
comma
id|count
)paren
suffix:semicolon
id|count
op_sub_assign
id|n
suffix:semicolon
id|ptr
op_add_assign
id|n
op_star
l_int|128
suffix:semicolon
)brace
id|len
op_assign
id|ptr
op_minus
op_star
id|start
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|length
)paren
r_return
id|length
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
l_int|0
)paren
r_return
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
multiline_comment|/*&n; *&t;Find the first device with a given source address.&n; */
DECL|function|ip_dev_find
r_struct
id|net_device
op_star
id|ip_dev_find
c_func
(paren
id|u32
id|addr
)paren
(brace
r_struct
id|flowi
id|fl
op_assign
(brace
dot
id|nl_u
op_assign
(brace
dot
id|ip4_u
op_assign
(brace
dot
id|daddr
op_assign
id|addr
)brace
)brace
)brace
suffix:semicolon
r_struct
id|fib_result
id|res
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MULTIPLE_TABLES
id|res.r
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|local_table
op_logical_or
id|local_table
op_member_access_from_pointer
id|tb_lookup
c_func
(paren
id|local_table
comma
op_amp
id|fl
comma
op_amp
id|res
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res.type
op_ne
id|RTN_LOCAL
)paren
r_goto
id|out
suffix:semicolon
id|dev
op_assign
id|FIB_RES_DEV
c_func
(paren
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;refcnt
)paren
suffix:semicolon
id|out
suffix:colon
id|fib_res_put
c_func
(paren
op_amp
id|res
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
DECL|function|inet_addr_type
r_int
id|inet_addr_type
c_func
(paren
id|u32
id|addr
)paren
(brace
r_struct
id|flowi
id|fl
op_assign
(brace
dot
id|nl_u
op_assign
(brace
dot
id|ip4_u
op_assign
(brace
dot
id|daddr
op_assign
id|addr
)brace
)brace
)brace
suffix:semicolon
r_struct
id|fib_result
id|res
suffix:semicolon
r_int
id|ret
op_assign
id|RTN_BROADCAST
suffix:semicolon
r_if
c_cond
(paren
id|ZERONET
c_func
(paren
id|addr
)paren
op_logical_or
id|BADCLASS
c_func
(paren
id|addr
)paren
)paren
r_return
id|RTN_BROADCAST
suffix:semicolon
r_if
c_cond
(paren
id|MULTICAST
c_func
(paren
id|addr
)paren
)paren
r_return
id|RTN_MULTICAST
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MULTIPLE_TABLES
id|res.r
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|local_table
)paren
(brace
id|ret
op_assign
id|RTN_UNICAST
suffix:semicolon
r_if
c_cond
(paren
id|local_table
op_member_access_from_pointer
id|tb_lookup
c_func
(paren
id|local_table
comma
op_amp
id|fl
comma
op_amp
id|res
)paren
op_eq
l_int|0
)paren
(brace
id|ret
op_assign
id|res.type
suffix:semicolon
id|fib_res_put
c_func
(paren
op_amp
id|res
)paren
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Given (packet source, input interface) and optional (dst, oif, tos):&n;   - (main) check, that source is valid i.e. not broadcast or our local&n;     address.&n;   - figure out what &quot;logical&quot; interface this packet arrived&n;     and calculate &quot;specific destination&quot; address.&n;   - check, that packet arrived from expected physical interface.&n; */
DECL|function|fib_validate_source
r_int
id|fib_validate_source
c_func
(paren
id|u32
id|src
comma
id|u32
id|dst
comma
id|u8
id|tos
comma
r_int
id|oif
comma
r_struct
id|net_device
op_star
id|dev
comma
id|u32
op_star
id|spec_dst
comma
id|u32
op_star
id|itag
)paren
(brace
r_struct
id|in_device
op_star
id|in_dev
suffix:semicolon
r_struct
id|flowi
id|fl
op_assign
(brace
dot
id|nl_u
op_assign
(brace
dot
id|ip4_u
op_assign
(brace
dot
id|daddr
op_assign
id|src
comma
dot
id|saddr
op_assign
id|dst
comma
dot
id|tos
op_assign
id|tos
)brace
)brace
comma
dot
id|iif
op_assign
id|oif
)brace
suffix:semicolon
r_struct
id|fib_result
id|res
suffix:semicolon
r_int
id|no_addr
comma
id|rpf
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|no_addr
op_assign
id|rpf
op_assign
l_int|0
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|inetdev_lock
)paren
suffix:semicolon
id|in_dev
op_assign
id|__in_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_dev
)paren
(brace
id|no_addr
op_assign
id|in_dev-&gt;ifa_list
op_eq
l_int|NULL
suffix:semicolon
id|rpf
op_assign
id|IN_DEV_RPFILTER
c_func
(paren
id|in_dev
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|inetdev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_dev
op_eq
l_int|NULL
)paren
r_goto
id|e_inval
suffix:semicolon
r_if
c_cond
(paren
id|fib_lookup
c_func
(paren
op_amp
id|fl
comma
op_amp
id|res
)paren
)paren
r_goto
id|last_resort
suffix:semicolon
r_if
c_cond
(paren
id|res.type
op_ne
id|RTN_UNICAST
)paren
r_goto
id|e_inval_res
suffix:semicolon
op_star
id|spec_dst
op_assign
id|FIB_RES_PREFSRC
c_func
(paren
id|res
)paren
suffix:semicolon
id|fib_combine_itag
c_func
(paren
id|itag
comma
op_amp
id|res
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IP_ROUTE_MULTIPATH
r_if
c_cond
(paren
id|FIB_RES_DEV
c_func
(paren
id|res
)paren
op_eq
id|dev
op_logical_or
id|res.fi-&gt;fib_nhs
OG
l_int|1
)paren
macro_line|#else
r_if
c_cond
(paren
id|FIB_RES_DEV
c_func
(paren
id|res
)paren
op_eq
id|dev
)paren
macro_line|#endif
(brace
id|ret
op_assign
id|FIB_RES_NH
c_func
(paren
id|res
)paren
dot
id|nh_scope
op_ge
id|RT_SCOPE_HOST
suffix:semicolon
id|fib_res_put
c_func
(paren
op_amp
id|res
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|fib_res_put
c_func
(paren
op_amp
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|no_addr
)paren
r_goto
id|last_resort
suffix:semicolon
r_if
c_cond
(paren
id|rpf
)paren
r_goto
id|e_inval
suffix:semicolon
id|fl.oif
op_assign
id|dev-&gt;ifindex
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fib_lookup
c_func
(paren
op_amp
id|fl
comma
op_amp
id|res
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|res.type
op_eq
id|RTN_UNICAST
)paren
(brace
op_star
id|spec_dst
op_assign
id|FIB_RES_PREFSRC
c_func
(paren
id|res
)paren
suffix:semicolon
id|ret
op_assign
id|FIB_RES_NH
c_func
(paren
id|res
)paren
dot
id|nh_scope
op_ge
id|RT_SCOPE_HOST
suffix:semicolon
)brace
id|fib_res_put
c_func
(paren
op_amp
id|res
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
id|last_resort
suffix:colon
r_if
c_cond
(paren
id|rpf
)paren
r_goto
id|e_inval
suffix:semicolon
op_star
id|spec_dst
op_assign
id|inet_select_addr
c_func
(paren
id|dev
comma
l_int|0
comma
id|RT_SCOPE_UNIVERSE
)paren
suffix:semicolon
op_star
id|itag
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|e_inval_res
suffix:colon
id|fib_res_put
c_func
(paren
op_amp
id|res
)paren
suffix:semicolon
id|e_inval
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_IP_NOSIOCRT
multiline_comment|/*&n; *&t;Handle IP routing ioctl calls. These are used to manipulate the routing tables&n; */
DECL|function|ip_rt_ioctl
r_int
id|ip_rt_ioctl
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
(brace
r_int
id|err
suffix:semicolon
r_struct
id|kern_rta
id|rta
suffix:semicolon
r_struct
id|rtentry
id|r
suffix:semicolon
r_struct
(brace
r_struct
id|nlmsghdr
id|nlh
suffix:semicolon
r_struct
id|rtmsg
id|rtm
suffix:semicolon
)brace
id|req
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCADDRT
suffix:colon
multiline_comment|/* Add a route */
r_case
id|SIOCDELRT
suffix:colon
multiline_comment|/* Delete a route */
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
id|copy_from_user
c_func
(paren
op_amp
id|r
comma
id|arg
comma
r_sizeof
(paren
r_struct
id|rtentry
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|fib_convert_rtentry
c_func
(paren
id|cmd
comma
op_amp
id|req.nlh
comma
op_amp
id|req.rtm
comma
op_amp
id|rta
comma
op_amp
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|cmd
op_eq
id|SIOCDELRT
)paren
(brace
r_struct
id|fib_table
op_star
id|tb
op_assign
id|fib_get_table
c_func
(paren
id|req.rtm.rtm_table
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ESRCH
suffix:semicolon
r_if
c_cond
(paren
id|tb
)paren
id|err
op_assign
id|tb
op_member_access_from_pointer
id|tb_delete
c_func
(paren
id|tb
comma
op_amp
id|req.rtm
comma
op_amp
id|rta
comma
op_amp
id|req.nlh
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|fib_table
op_star
id|tb
op_assign
id|fib_new_table
c_func
(paren
id|req.rtm.rtm_table
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOBUFS
suffix:semicolon
r_if
c_cond
(paren
id|tb
)paren
id|err
op_assign
id|tb
op_member_access_from_pointer
id|tb_insert
c_func
(paren
id|tb
comma
op_amp
id|req.rtm
comma
op_amp
id|rta
comma
op_amp
id|req.nlh
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rta.rta_mx
)paren
id|kfree
c_func
(paren
id|rta.rta_mx
)paren
suffix:semicolon
)brace
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#else
DECL|function|ip_rt_ioctl
r_int
id|ip_rt_ioctl
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
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
DECL|function|inet_check_attr
r_static
r_int
id|inet_check_attr
c_func
(paren
r_struct
id|rtmsg
op_star
id|r
comma
r_struct
id|rtattr
op_star
op_star
id|rta
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|RTA_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|rtattr
op_star
id|attr
op_assign
id|rta
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|attr
)paren
(brace
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|attr
)paren
OL
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|RTA_MULTIPATH
op_logical_and
id|i
op_ne
id|RTA_METRICS
)paren
id|rta
(braket
id|i
op_minus
l_int|1
)braket
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|RTA_DATA
c_func
(paren
id|attr
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inet_rtm_delroute
r_int
id|inet_rtm_delroute
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
(brace
r_struct
id|fib_table
op_star
id|tb
suffix:semicolon
r_struct
id|rtattr
op_star
op_star
id|rta
op_assign
id|arg
suffix:semicolon
r_struct
id|rtmsg
op_star
id|r
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet_check_attr
c_func
(paren
id|r
comma
id|rta
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tb
op_assign
id|fib_get_table
c_func
(paren
id|r-&gt;rtm_table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tb
)paren
r_return
id|tb
op_member_access_from_pointer
id|tb_delete
c_func
(paren
id|tb
comma
id|r
comma
(paren
r_struct
id|kern_rta
op_star
)paren
id|rta
comma
id|nlh
comma
op_amp
id|NETLINK_CB
c_func
(paren
id|skb
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
DECL|function|inet_rtm_newroute
r_int
id|inet_rtm_newroute
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
(brace
r_struct
id|fib_table
op_star
id|tb
suffix:semicolon
r_struct
id|rtattr
op_star
op_star
id|rta
op_assign
id|arg
suffix:semicolon
r_struct
id|rtmsg
op_star
id|r
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inet_check_attr
c_func
(paren
id|r
comma
id|rta
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tb
op_assign
id|fib_new_table
c_func
(paren
id|r-&gt;rtm_table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tb
)paren
r_return
id|tb
op_member_access_from_pointer
id|tb_insert
c_func
(paren
id|tb
comma
id|r
comma
(paren
r_struct
id|kern_rta
op_star
)paren
id|rta
comma
id|nlh
comma
op_amp
id|NETLINK_CB
c_func
(paren
id|skb
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
DECL|function|inet_dump_fib
r_int
id|inet_dump_fib
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
(brace
r_int
id|t
suffix:semicolon
r_int
id|s_t
suffix:semicolon
r_struct
id|fib_table
op_star
id|tb
suffix:semicolon
r_if
c_cond
(paren
id|NLMSG_PAYLOAD
c_func
(paren
id|cb-&gt;nlh
comma
l_int|0
)paren
op_ge
r_sizeof
(paren
r_struct
id|rtmsg
)paren
op_logical_and
(paren
(paren
r_struct
id|rtmsg
op_star
)paren
id|NLMSG_DATA
c_func
(paren
id|cb-&gt;nlh
)paren
)paren
op_member_access_from_pointer
id|rtm_flags
op_amp
id|RTM_F_CLONED
)paren
r_return
id|ip_rt_dump
c_func
(paren
id|skb
comma
id|cb
)paren
suffix:semicolon
id|s_t
op_assign
id|cb-&gt;args
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|s_t
op_eq
l_int|0
)paren
id|s_t
op_assign
id|cb-&gt;args
(braket
l_int|0
)braket
op_assign
id|RT_TABLE_MIN
suffix:semicolon
r_for
c_loop
(paren
id|t
op_assign
id|s_t
suffix:semicolon
id|t
op_le
id|RT_TABLE_MAX
suffix:semicolon
id|t
op_increment
)paren
(brace
r_if
c_cond
(paren
id|t
OL
id|s_t
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|t
OG
id|s_t
)paren
id|memset
c_func
(paren
op_amp
id|cb-&gt;args
(braket
l_int|1
)braket
comma
l_int|0
comma
r_sizeof
(paren
id|cb-&gt;args
)paren
op_minus
r_sizeof
(paren
id|cb-&gt;args
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tb
op_assign
id|fib_get_table
c_func
(paren
id|t
)paren
)paren
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|tb
op_member_access_from_pointer
id|tb_dump
c_func
(paren
id|tb
comma
id|skb
comma
id|cb
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|cb-&gt;args
(braket
l_int|0
)braket
op_assign
id|t
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
)brace
multiline_comment|/* Prepare and feed intra-kernel routing request.&n;   Really, it should be netlink message, but :-( netlink&n;   can be not configured, so that we feed it directly&n;   to fib engine. It is legal, because all events occur&n;   only when netlink is already locked.&n; */
DECL|function|fib_magic
r_static
r_void
id|fib_magic
c_func
(paren
r_int
id|cmd
comma
r_int
id|type
comma
id|u32
id|dst
comma
r_int
id|dst_len
comma
r_struct
id|in_ifaddr
op_star
id|ifa
)paren
(brace
r_struct
id|fib_table
op_star
id|tb
suffix:semicolon
r_struct
(brace
r_struct
id|nlmsghdr
id|nlh
suffix:semicolon
r_struct
id|rtmsg
id|rtm
suffix:semicolon
)brace
id|req
suffix:semicolon
r_struct
id|kern_rta
id|rta
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|req.rtm
comma
l_int|0
comma
r_sizeof
(paren
id|req.rtm
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|rta
comma
l_int|0
comma
r_sizeof
(paren
id|rta
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|RTN_UNICAST
)paren
id|tb
op_assign
id|fib_new_table
c_func
(paren
id|RT_TABLE_MAIN
)paren
suffix:semicolon
r_else
id|tb
op_assign
id|fib_new_table
c_func
(paren
id|RT_TABLE_LOCAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tb
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|req.nlh.nlmsg_len
op_assign
r_sizeof
(paren
id|req
)paren
suffix:semicolon
id|req.nlh.nlmsg_type
op_assign
id|cmd
suffix:semicolon
id|req.nlh.nlmsg_flags
op_assign
id|NLM_F_REQUEST
op_or
id|NLM_F_CREATE
op_or
id|NLM_F_APPEND
suffix:semicolon
id|req.nlh.nlmsg_pid
op_assign
l_int|0
suffix:semicolon
id|req.nlh.nlmsg_seq
op_assign
l_int|0
suffix:semicolon
id|req.rtm.rtm_dst_len
op_assign
id|dst_len
suffix:semicolon
id|req.rtm.rtm_table
op_assign
id|tb-&gt;tb_id
suffix:semicolon
id|req.rtm.rtm_protocol
op_assign
id|RTPROT_KERNEL
suffix:semicolon
id|req.rtm.rtm_scope
op_assign
(paren
id|type
op_ne
id|RTN_LOCAL
ques
c_cond
id|RT_SCOPE_LINK
suffix:colon
id|RT_SCOPE_HOST
)paren
suffix:semicolon
id|req.rtm.rtm_type
op_assign
id|type
suffix:semicolon
id|rta.rta_dst
op_assign
op_amp
id|dst
suffix:semicolon
id|rta.rta_prefsrc
op_assign
op_amp
id|ifa-&gt;ifa_local
suffix:semicolon
id|rta.rta_oif
op_assign
op_amp
id|ifa-&gt;ifa_dev-&gt;dev-&gt;ifindex
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|RTM_NEWROUTE
)paren
id|tb
op_member_access_from_pointer
id|tb_insert
c_func
(paren
id|tb
comma
op_amp
id|req.rtm
comma
op_amp
id|rta
comma
op_amp
id|req.nlh
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|tb
op_member_access_from_pointer
id|tb_delete
c_func
(paren
id|tb
comma
op_amp
id|req.rtm
comma
op_amp
id|rta
comma
op_amp
id|req.nlh
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|fib_add_ifaddr
r_static
r_void
id|fib_add_ifaddr
c_func
(paren
r_struct
id|in_ifaddr
op_star
id|ifa
)paren
(brace
r_struct
id|in_device
op_star
id|in_dev
op_assign
id|ifa-&gt;ifa_dev
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|in_dev-&gt;dev
suffix:semicolon
r_struct
id|in_ifaddr
op_star
id|prim
op_assign
id|ifa
suffix:semicolon
id|u32
id|mask
op_assign
id|ifa-&gt;ifa_mask
suffix:semicolon
id|u32
id|addr
op_assign
id|ifa-&gt;ifa_local
suffix:semicolon
id|u32
id|prefix
op_assign
id|ifa-&gt;ifa_address
op_amp
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|ifa-&gt;ifa_flags
op_amp
id|IFA_F_SECONDARY
)paren
(brace
id|prim
op_assign
id|inet_ifa_byprefix
c_func
(paren
id|in_dev
comma
id|prefix
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prim
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;fib_add_ifaddr: bug: prim == NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|fib_magic
c_func
(paren
id|RTM_NEWROUTE
comma
id|RTN_LOCAL
comma
id|addr
comma
l_int|32
comma
id|prim
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Add broadcast address, if it is explicitly assigned. */
r_if
c_cond
(paren
id|ifa-&gt;ifa_broadcast
op_logical_and
id|ifa-&gt;ifa_broadcast
op_ne
l_int|0xFFFFFFFF
)paren
id|fib_magic
c_func
(paren
id|RTM_NEWROUTE
comma
id|RTN_BROADCAST
comma
id|ifa-&gt;ifa_broadcast
comma
l_int|32
comma
id|prim
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ZERONET
c_func
(paren
id|prefix
)paren
op_logical_and
op_logical_neg
(paren
id|ifa-&gt;ifa_flags
op_amp
id|IFA_F_SECONDARY
)paren
op_logical_and
(paren
id|prefix
op_ne
id|addr
op_logical_or
id|ifa-&gt;ifa_prefixlen
OL
l_int|32
)paren
)paren
(brace
id|fib_magic
c_func
(paren
id|RTM_NEWROUTE
comma
id|dev-&gt;flags
op_amp
id|IFF_LOOPBACK
ques
c_cond
id|RTN_LOCAL
suffix:colon
id|RTN_UNICAST
comma
id|prefix
comma
id|ifa-&gt;ifa_prefixlen
comma
id|prim
)paren
suffix:semicolon
multiline_comment|/* Add network specific broadcasts, when it takes a sense */
r_if
c_cond
(paren
id|ifa-&gt;ifa_prefixlen
OL
l_int|31
)paren
(brace
id|fib_magic
c_func
(paren
id|RTM_NEWROUTE
comma
id|RTN_BROADCAST
comma
id|prefix
comma
l_int|32
comma
id|prim
)paren
suffix:semicolon
id|fib_magic
c_func
(paren
id|RTM_NEWROUTE
comma
id|RTN_BROADCAST
comma
id|prefix
op_or
op_complement
id|mask
comma
l_int|32
comma
id|prim
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|fib_del_ifaddr
r_static
r_void
id|fib_del_ifaddr
c_func
(paren
r_struct
id|in_ifaddr
op_star
id|ifa
)paren
(brace
r_struct
id|in_device
op_star
id|in_dev
op_assign
id|ifa-&gt;ifa_dev
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|in_dev-&gt;dev
suffix:semicolon
r_struct
id|in_ifaddr
op_star
id|ifa1
suffix:semicolon
r_struct
id|in_ifaddr
op_star
id|prim
op_assign
id|ifa
suffix:semicolon
id|u32
id|brd
op_assign
id|ifa-&gt;ifa_address
op_or
op_complement
id|ifa-&gt;ifa_mask
suffix:semicolon
id|u32
id|any
op_assign
id|ifa-&gt;ifa_address
op_amp
id|ifa-&gt;ifa_mask
suffix:semicolon
DECL|macro|LOCAL_OK
mdefine_line|#define LOCAL_OK&t;1
DECL|macro|BRD_OK
mdefine_line|#define BRD_OK&t;&t;2
DECL|macro|BRD0_OK
mdefine_line|#define BRD0_OK&t;&t;4
DECL|macro|BRD1_OK
mdefine_line|#define BRD1_OK&t;&t;8
r_int
id|ok
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ifa-&gt;ifa_flags
op_amp
id|IFA_F_SECONDARY
)paren
)paren
id|fib_magic
c_func
(paren
id|RTM_DELROUTE
comma
id|dev-&gt;flags
op_amp
id|IFF_LOOPBACK
ques
c_cond
id|RTN_LOCAL
suffix:colon
id|RTN_UNICAST
comma
id|any
comma
id|ifa-&gt;ifa_prefixlen
comma
id|prim
)paren
suffix:semicolon
r_else
(brace
id|prim
op_assign
id|inet_ifa_byprefix
c_func
(paren
id|in_dev
comma
id|any
comma
id|ifa-&gt;ifa_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prim
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;fib_del_ifaddr: bug: prim == NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* Deletion is more complicated than add.&n;&t;   We should take care of not to delete too much :-)&n;&n;&t;   Scan address list to be sure that addresses are really gone.&n;&t; */
r_for
c_loop
(paren
id|ifa1
op_assign
id|in_dev-&gt;ifa_list
suffix:semicolon
id|ifa1
suffix:semicolon
id|ifa1
op_assign
id|ifa1-&gt;ifa_next
)paren
(brace
r_if
c_cond
(paren
id|ifa-&gt;ifa_local
op_eq
id|ifa1-&gt;ifa_local
)paren
id|ok
op_or_assign
id|LOCAL_OK
suffix:semicolon
r_if
c_cond
(paren
id|ifa-&gt;ifa_broadcast
op_eq
id|ifa1-&gt;ifa_broadcast
)paren
id|ok
op_or_assign
id|BRD_OK
suffix:semicolon
r_if
c_cond
(paren
id|brd
op_eq
id|ifa1-&gt;ifa_broadcast
)paren
id|ok
op_or_assign
id|BRD1_OK
suffix:semicolon
r_if
c_cond
(paren
id|any
op_eq
id|ifa1-&gt;ifa_broadcast
)paren
id|ok
op_or_assign
id|BRD0_OK
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ok
op_amp
id|BRD_OK
)paren
)paren
id|fib_magic
c_func
(paren
id|RTM_DELROUTE
comma
id|RTN_BROADCAST
comma
id|ifa-&gt;ifa_broadcast
comma
l_int|32
comma
id|prim
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ok
op_amp
id|BRD1_OK
)paren
)paren
id|fib_magic
c_func
(paren
id|RTM_DELROUTE
comma
id|RTN_BROADCAST
comma
id|brd
comma
l_int|32
comma
id|prim
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ok
op_amp
id|BRD0_OK
)paren
)paren
id|fib_magic
c_func
(paren
id|RTM_DELROUTE
comma
id|RTN_BROADCAST
comma
id|any
comma
l_int|32
comma
id|prim
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ok
op_amp
id|LOCAL_OK
)paren
)paren
(brace
id|fib_magic
c_func
(paren
id|RTM_DELROUTE
comma
id|RTN_LOCAL
comma
id|ifa-&gt;ifa_local
comma
l_int|32
comma
id|prim
)paren
suffix:semicolon
multiline_comment|/* Check, that this local address finally disappeared. */
r_if
c_cond
(paren
id|inet_addr_type
c_func
(paren
id|ifa-&gt;ifa_local
)paren
op_ne
id|RTN_LOCAL
)paren
(brace
multiline_comment|/* And the last, but not the least thing.&n;&t;&t;&t;   We must flush stray FIB entries.&n;&n;&t;&t;&t;   First of all, we scan fib_info list searching&n;&t;&t;&t;   for stray nexthop entries, then ignite fib_flush.&n;&t;&t;&t;*/
r_if
c_cond
(paren
id|fib_sync_down
c_func
(paren
id|ifa-&gt;ifa_local
comma
l_int|NULL
comma
l_int|0
)paren
)paren
id|fib_flush
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|macro|LOCAL_OK
macro_line|#undef LOCAL_OK
DECL|macro|BRD_OK
macro_line|#undef BRD_OK
DECL|macro|BRD0_OK
macro_line|#undef BRD0_OK
DECL|macro|BRD1_OK
macro_line|#undef BRD1_OK
)brace
DECL|function|fib_disable_ip
r_static
r_void
id|fib_disable_ip
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|force
)paren
(brace
r_if
c_cond
(paren
id|fib_sync_down
c_func
(paren
l_int|0
comma
id|dev
comma
id|force
)paren
)paren
id|fib_flush
c_func
(paren
)paren
suffix:semicolon
id|rt_cache_flush
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|arp_ifdown
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|fib_inetaddr_event
r_static
r_int
id|fib_inetaddr_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|in_ifaddr
op_star
id|ifa
op_assign
(paren
r_struct
id|in_ifaddr
op_star
)paren
id|ptr
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|NETDEV_UP
suffix:colon
id|fib_add_ifaddr
c_func
(paren
id|ifa
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IP_ROUTE_MULTIPATH
id|fib_sync_up
c_func
(paren
id|ifa-&gt;ifa_dev-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
id|rt_cache_flush
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NETDEV_DOWN
suffix:colon
id|fib_del_ifaddr
c_func
(paren
id|ifa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ifa-&gt;ifa_dev
op_logical_and
id|ifa-&gt;ifa_dev-&gt;ifa_list
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* Last address was deleted from this interface.&n;&t;&t;&t;   Disable IP.&n;&t;&t;&t; */
id|fib_disable_ip
c_func
(paren
id|ifa-&gt;ifa_dev-&gt;dev
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|rt_cache_flush
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|function|fib_netdev_event
r_static
r_int
id|fib_netdev_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|ptr
suffix:semicolon
r_struct
id|in_device
op_star
id|in_dev
op_assign
id|__in_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|event
op_eq
id|NETDEV_UNREGISTER
)paren
(brace
id|fib_disable_ip
c_func
(paren
id|dev
comma
l_int|2
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|in_dev
)paren
r_return
id|NOTIFY_DONE
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|NETDEV_UP
suffix:colon
id|for_ifa
c_func
(paren
id|in_dev
)paren
(brace
id|fib_add_ifaddr
c_func
(paren
id|ifa
)paren
suffix:semicolon
)brace
id|endfor_ifa
c_func
(paren
id|in_dev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IP_ROUTE_MULTIPATH
id|fib_sync_up
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#endif
id|rt_cache_flush
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NETDEV_DOWN
suffix:colon
id|fib_disable_ip
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NETDEV_CHANGEMTU
suffix:colon
r_case
id|NETDEV_CHANGE
suffix:colon
id|rt_cache_flush
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|fib_inetaddr_notifier
r_struct
id|notifier_block
id|fib_inetaddr_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|fib_inetaddr_event
comma
)brace
suffix:semicolon
DECL|variable|fib_netdev_notifier
r_struct
id|notifier_block
id|fib_netdev_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|fib_netdev_event
comma
)brace
suffix:semicolon
DECL|function|ip_fib_init
r_void
id|__init
id|ip_fib_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
id|proc_net_create
c_func
(paren
l_string|&quot;route&quot;
comma
l_int|0
comma
id|fib_get_procinfo
)paren
suffix:semicolon
macro_line|#endif&t;&t;/* CONFIG_PROC_FS */
macro_line|#ifndef CONFIG_IP_MULTIPLE_TABLES
id|local_table
op_assign
id|fib_hash_init
c_func
(paren
id|RT_TABLE_LOCAL
)paren
suffix:semicolon
id|main_table
op_assign
id|fib_hash_init
c_func
(paren
id|RT_TABLE_MAIN
)paren
suffix:semicolon
macro_line|#else
id|fib_rules_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|register_netdevice_notifier
c_func
(paren
op_amp
id|fib_netdev_notifier
)paren
suffix:semicolon
id|register_inetaddr_notifier
c_func
(paren
op_amp
id|fib_inetaddr_notifier
)paren
suffix:semicolon
)brace
eof
