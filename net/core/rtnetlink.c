multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Routing netlink socket interface: protocol independent part.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Fixes:&n; *&t;Vitaly E. Lavrov&t;&t;RTA_OK arithmetics was wrong.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/string.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
DECL|variable|rtnl_sem
id|DECLARE_MUTEX
c_func
(paren
id|rtnl_sem
)paren
suffix:semicolon
DECL|function|rtnl_lock
r_void
id|rtnl_lock
c_func
(paren
r_void
)paren
(brace
id|rtnl_shlock
c_func
(paren
)paren
suffix:semicolon
id|rtnl_exlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|rtnl_unlock
r_void
id|rtnl_unlock
c_func
(paren
r_void
)paren
(brace
id|rtnl_exunlock
c_func
(paren
)paren
suffix:semicolon
id|rtnl_shunlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|rtattr_parse
r_int
id|rtattr_parse
c_func
(paren
r_struct
id|rtattr
op_star
id|tb
(braket
)braket
comma
r_int
id|maxattr
comma
r_struct
id|rtattr
op_star
id|rta
comma
r_int
id|len
)paren
(brace
id|memset
c_func
(paren
id|tb
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|rtattr
op_star
)paren
op_star
id|maxattr
)paren
suffix:semicolon
r_while
c_loop
(paren
id|RTA_OK
c_func
(paren
id|rta
comma
id|len
)paren
)paren
(brace
r_int
id|flavor
op_assign
id|rta-&gt;rta_type
suffix:semicolon
r_if
c_cond
(paren
id|flavor
op_logical_and
id|flavor
op_le
id|maxattr
)paren
id|tb
(braket
id|flavor
op_minus
l_int|1
)braket
op_assign
id|rta
suffix:semicolon
id|rta
op_assign
id|RTA_NEXT
c_func
(paren
id|rta
comma
id|len
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|rtnl
r_struct
id|sock
op_star
id|rtnl
suffix:semicolon
DECL|variable|rtnetlink_links
r_struct
id|rtnetlink_link
op_star
id|rtnetlink_links
(braket
id|NPROTO
)braket
suffix:semicolon
DECL|variable|rtm_min
r_static
r_const
r_int
id|rtm_min
(braket
(paren
id|RTM_MAX
op_plus
l_int|1
op_minus
id|RTM_BASE
)paren
op_div
l_int|4
)braket
op_assign
(brace
id|NLMSG_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|ifinfomsg
)paren
)paren
comma
id|NLMSG_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|ifaddrmsg
)paren
)paren
comma
id|NLMSG_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|rtmsg
)paren
)paren
comma
id|NLMSG_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|ndmsg
)paren
)paren
comma
id|NLMSG_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|rtmsg
)paren
)paren
comma
id|NLMSG_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|tcmsg
)paren
)paren
comma
id|NLMSG_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|tcmsg
)paren
)paren
comma
id|NLMSG_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|tcmsg
)paren
)paren
)brace
suffix:semicolon
DECL|variable|rta_max
r_static
r_const
r_int
id|rta_max
(braket
(paren
id|RTM_MAX
op_plus
l_int|1
op_minus
id|RTM_BASE
)paren
op_div
l_int|4
)braket
op_assign
(brace
id|IFLA_MAX
comma
id|IFA_MAX
comma
id|RTA_MAX
comma
id|NDA_MAX
comma
id|RTA_MAX
comma
id|TCA_MAX
comma
id|TCA_MAX
comma
id|TCA_MAX
)brace
suffix:semicolon
DECL|function|__rta_fill
r_void
id|__rta_fill
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|attrtype
comma
r_int
id|attrlen
comma
r_const
r_void
op_star
id|data
)paren
(brace
r_struct
id|rtattr
op_star
id|rta
suffix:semicolon
r_int
id|size
op_assign
id|RTA_LENGTH
c_func
(paren
id|attrlen
)paren
suffix:semicolon
id|rta
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
id|RTA_ALIGN
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
id|rta-&gt;rta_type
op_assign
id|attrtype
suffix:semicolon
id|rta-&gt;rta_len
op_assign
id|size
suffix:semicolon
id|memcpy
c_func
(paren
id|RTA_DATA
c_func
(paren
id|rta
)paren
comma
id|data
comma
id|attrlen
)paren
suffix:semicolon
)brace
DECL|function|rtnetlink_send
r_int
id|rtnetlink_send
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
id|pid
comma
r_int
id|group
comma
r_int
id|echo
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|NETLINK_CB
c_func
(paren
id|skb
)paren
dot
id|dst_groups
op_assign
id|group
suffix:semicolon
r_if
c_cond
(paren
id|echo
)paren
id|atomic_inc
c_func
(paren
op_amp
id|skb-&gt;users
)paren
suffix:semicolon
id|netlink_broadcast
c_func
(paren
id|rtnl
comma
id|skb
comma
id|pid
comma
id|group
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|echo
)paren
id|err
op_assign
id|netlink_unicast
c_func
(paren
id|rtnl
comma
id|skb
comma
id|pid
comma
id|MSG_DONTWAIT
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|rtnetlink_put_metrics
r_int
id|rtnetlink_put_metrics
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
op_star
id|metrics
)paren
(brace
r_struct
id|rtattr
op_star
id|mx
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|skb-&gt;tail
suffix:semicolon
r_int
id|i
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|RTA_METRICS
comma
l_int|0
comma
l_int|NULL
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
id|RTAX_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|metrics
(braket
id|i
)braket
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|i
op_plus
l_int|1
comma
r_sizeof
(paren
id|u32
)paren
comma
id|metrics
op_plus
id|i
)paren
suffix:semicolon
)brace
id|mx-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
(paren
id|u8
op_star
)paren
id|mx
suffix:semicolon
r_if
c_cond
(paren
id|mx-&gt;rta_len
op_eq
id|RTA_LENGTH
c_func
(paren
l_int|0
)paren
)paren
id|skb_trim
c_func
(paren
id|skb
comma
(paren
id|u8
op_star
)paren
id|mx
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|rtattr_failure
suffix:colon
id|skb_trim
c_func
(paren
id|skb
comma
(paren
id|u8
op_star
)paren
id|mx
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|rtnetlink_fill_ifinfo
r_static
r_int
id|rtnetlink_fill_ifinfo
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|type
comma
id|u32
id|pid
comma
id|u32
id|seq
comma
id|u32
id|change
)paren
(brace
r_struct
id|ifinfomsg
op_star
id|r
suffix:semicolon
r_struct
id|nlmsghdr
op_star
id|nlh
suffix:semicolon
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
suffix:semicolon
id|nlh
op_assign
id|NLMSG_PUT
c_func
(paren
id|skb
comma
id|pid
comma
id|seq
comma
id|type
comma
r_sizeof
(paren
op_star
id|r
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
)paren
id|nlh-&gt;nlmsg_flags
op_or_assign
id|NLM_F_MULTI
suffix:semicolon
id|r
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
id|r-&gt;ifi_family
op_assign
id|AF_UNSPEC
suffix:semicolon
id|r-&gt;ifi_type
op_assign
id|dev-&gt;type
suffix:semicolon
id|r-&gt;ifi_index
op_assign
id|dev-&gt;ifindex
suffix:semicolon
id|r-&gt;ifi_flags
op_assign
id|dev-&gt;flags
suffix:semicolon
id|r-&gt;ifi_change
op_assign
id|change
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|netif_running
c_func
(paren
id|dev
)paren
op_logical_or
op_logical_neg
id|netif_carrier_ok
c_func
(paren
id|dev
)paren
)paren
id|r-&gt;ifi_flags
op_and_assign
op_complement
id|IFF_RUNNING
suffix:semicolon
r_else
id|r-&gt;ifi_flags
op_or_assign
id|IFF_RUNNING
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|IFLA_IFNAME
comma
id|strlen
c_func
(paren
id|dev-&gt;name
)paren
op_plus
l_int|1
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;addr_len
)paren
(brace
id|RTA_PUT
c_func
(paren
id|skb
comma
id|IFLA_ADDRESS
comma
id|dev-&gt;addr_len
comma
id|dev-&gt;dev_addr
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|IFLA_BROADCAST
comma
id|dev-&gt;addr_len
comma
id|dev-&gt;broadcast
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|1
)paren
(brace
r_int
id|mtu
op_assign
id|dev-&gt;mtu
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|IFLA_MTU
comma
r_sizeof
(paren
id|mtu
)paren
comma
op_amp
id|mtu
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;ifindex
op_ne
id|dev-&gt;iflink
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|IFLA_LINK
comma
r_sizeof
(paren
r_int
)paren
comma
op_amp
id|dev-&gt;iflink
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;qdisc_sleeping
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|IFLA_QDISC
comma
id|strlen
c_func
(paren
id|dev-&gt;qdisc_sleeping-&gt;ops-&gt;id
)paren
op_plus
l_int|1
comma
id|dev-&gt;qdisc_sleeping-&gt;ops-&gt;id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;master
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|IFLA_MASTER
comma
r_sizeof
(paren
r_int
)paren
comma
op_amp
id|dev-&gt;master-&gt;ifindex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;get_stats
)paren
(brace
r_struct
id|net_device_stats
op_star
id|stats
op_assign
id|dev
op_member_access_from_pointer
id|get_stats
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stats
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|IFLA_STATS
comma
r_sizeof
(paren
op_star
id|stats
)paren
comma
id|stats
)paren
suffix:semicolon
)brace
id|nlh-&gt;nlmsg_len
op_assign
id|skb-&gt;tail
op_minus
id|b
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
id|nlmsg_failure
suffix:colon
id|rtattr_failure
suffix:colon
id|skb_trim
c_func
(paren
id|skb
comma
id|b
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|rtnetlink_dump_ifinfo
r_int
id|rtnetlink_dump_ifinfo
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
id|idx
suffix:semicolon
r_int
id|s_idx
op_assign
id|cb-&gt;args
(braket
l_int|0
)braket
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
comma
id|idx
op_assign
l_int|0
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
comma
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|idx
OL
id|s_idx
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|rtnetlink_fill_ifinfo
c_func
(paren
id|skb
comma
id|dev
comma
id|RTM_NEWLINK
comma
id|NETLINK_CB
c_func
(paren
id|cb-&gt;skb
)paren
dot
id|pid
comma
id|cb-&gt;nlh-&gt;nlmsg_seq
comma
l_int|0
)paren
op_le
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
id|cb-&gt;args
(braket
l_int|0
)braket
op_assign
id|idx
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
)brace
DECL|function|do_setlink
r_static
r_int
id|do_setlink
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
id|ifinfomsg
op_star
id|ifm
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
r_struct
id|rtattr
op_star
op_star
id|ida
op_assign
id|arg
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dev
op_assign
id|dev_get_by_index
c_func
(paren
id|ifm-&gt;ifi_index
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ida
(braket
id|IFLA_ADDRESS
op_minus
l_int|1
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;set_mac_address
)paren
(brace
id|err
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|netif_device_present
c_func
(paren
id|dev
)paren
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
r_if
c_cond
(paren
id|ida
(braket
id|IFLA_ADDRESS
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|rta_len
op_ne
id|RTA_LENGTH
c_func
(paren
id|dev-&gt;addr_len
)paren
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|dev
op_member_access_from_pointer
id|set_mac_address
c_func
(paren
id|dev
comma
id|RTA_DATA
c_func
(paren
id|ida
(braket
id|IFLA_ADDRESS
op_minus
l_int|1
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ida
(braket
id|IFLA_BROADCAST
op_minus
l_int|1
)braket
)paren
(brace
r_if
c_cond
(paren
id|ida
(braket
id|IFLA_BROADCAST
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|rta_len
op_ne
id|RTA_LENGTH
c_func
(paren
id|dev-&gt;addr_len
)paren
)paren
r_goto
id|out
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;broadcast
comma
id|RTA_DATA
c_func
(paren
id|ida
(braket
id|IFLA_BROADCAST
op_minus
l_int|1
)braket
)paren
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|call_netdevice_notifiers
c_func
(paren
id|NETDEV_CHANGEADDR
comma
id|dev
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
DECL|function|rtnetlink_dump_all
r_int
id|rtnetlink_dump_all
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
id|idx
suffix:semicolon
r_int
id|s_idx
op_assign
id|cb-&gt;family
suffix:semicolon
r_if
c_cond
(paren
id|s_idx
op_eq
l_int|0
)paren
id|s_idx
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|1
suffix:semicolon
id|idx
OL
id|NPROTO
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_int
id|type
op_assign
id|cb-&gt;nlh-&gt;nlmsg_type
op_minus
id|RTM_BASE
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
id|s_idx
op_logical_or
id|idx
op_eq
id|PF_PACKET
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|rtnetlink_links
(braket
id|idx
)braket
op_eq
l_int|NULL
op_logical_or
id|rtnetlink_links
(braket
id|idx
)braket
(braket
id|type
)braket
dot
id|dumpit
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|idx
OG
id|s_idx
)paren
id|memset
c_func
(paren
op_amp
id|cb-&gt;args
(braket
l_int|0
)braket
comma
l_int|0
comma
r_sizeof
(paren
id|cb-&gt;args
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtnetlink_links
(braket
id|idx
)braket
(braket
id|type
)braket
dot
id|dumpit
c_func
(paren
id|skb
comma
id|cb
)paren
)paren
r_break
suffix:semicolon
)brace
id|cb-&gt;family
op_assign
id|idx
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
)brace
DECL|function|rtmsg_ifinfo
r_void
id|rtmsg_ifinfo
c_func
(paren
r_int
id|type
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|change
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|size
op_assign
id|NLMSG_GOODSIZE
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|rtnetlink_fill_ifinfo
c_func
(paren
id|skb
comma
id|dev
comma
id|type
comma
l_int|0
comma
l_int|0
comma
id|change
)paren
OL
l_int|0
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|NETLINK_CB
c_func
(paren
id|skb
)paren
dot
id|dst_groups
op_assign
id|RTMGRP_LINK
suffix:semicolon
id|netlink_broadcast
c_func
(paren
id|rtnl
comma
id|skb
comma
l_int|0
comma
id|RTMGRP_LINK
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
DECL|function|rtnetlink_done
r_static
r_int
id|rtnetlink_done
c_func
(paren
r_struct
id|netlink_callback
op_star
id|cb
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Process one rtnetlink message. */
r_static
id|__inline__
r_int
DECL|function|rtnetlink_rcv_msg
id|rtnetlink_rcv_msg
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
r_int
op_star
id|errp
)paren
(brace
r_struct
id|rtnetlink_link
op_star
id|link
suffix:semicolon
r_struct
id|rtnetlink_link
op_star
id|link_tab
suffix:semicolon
r_struct
id|rtattr
op_star
id|rta
(braket
id|RTATTR_MAX
)braket
suffix:semicolon
r_int
id|exclusive
op_assign
l_int|0
suffix:semicolon
r_int
id|sz_idx
comma
id|kind
suffix:semicolon
r_int
id|min_len
suffix:semicolon
r_int
id|family
suffix:semicolon
r_int
id|type
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* Only requests are handled by kernel now */
r_if
c_cond
(paren
op_logical_neg
(paren
id|nlh-&gt;nlmsg_flags
op_amp
id|NLM_F_REQUEST
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|type
op_assign
id|nlh-&gt;nlmsg_type
suffix:semicolon
multiline_comment|/* A control message: ignore them */
r_if
c_cond
(paren
id|type
OL
id|RTM_BASE
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Unknown message: reply with EINVAL */
r_if
c_cond
(paren
id|type
OG
id|RTM_MAX
)paren
r_goto
id|err_inval
suffix:semicolon
id|type
op_sub_assign
id|RTM_BASE
suffix:semicolon
multiline_comment|/* All the messages must have at least 1 byte length */
r_if
c_cond
(paren
id|nlh-&gt;nlmsg_len
OL
id|NLMSG_LENGTH
c_func
(paren
r_sizeof
(paren
r_struct
id|rtgenmsg
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|family
op_assign
(paren
(paren
r_struct
id|rtgenmsg
op_star
)paren
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
)paren
op_member_access_from_pointer
id|rtgen_family
suffix:semicolon
r_if
c_cond
(paren
id|family
OG
id|NPROTO
)paren
(brace
op_star
id|errp
op_assign
op_minus
id|EAFNOSUPPORT
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|link_tab
op_assign
id|rtnetlink_links
(braket
id|family
)braket
suffix:semicolon
r_if
c_cond
(paren
id|link_tab
op_eq
l_int|NULL
)paren
id|link_tab
op_assign
id|rtnetlink_links
(braket
id|PF_UNSPEC
)braket
suffix:semicolon
id|link
op_assign
op_amp
id|link_tab
(braket
id|type
)braket
suffix:semicolon
id|sz_idx
op_assign
id|type
op_rshift
l_int|2
suffix:semicolon
id|kind
op_assign
id|type
op_amp
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|kind
op_ne
l_int|2
op_logical_and
id|security_netlink_recv
c_func
(paren
id|skb
)paren
)paren
(brace
op_star
id|errp
op_assign
op_minus
id|EPERM
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kind
op_eq
l_int|2
op_logical_and
id|nlh-&gt;nlmsg_flags
op_amp
id|NLM_F_DUMP
)paren
(brace
id|u32
id|rlen
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;dumpit
op_eq
l_int|NULL
)paren
id|link
op_assign
op_amp
(paren
id|rtnetlink_links
(braket
id|PF_UNSPEC
)braket
(braket
id|type
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;dumpit
op_eq
l_int|NULL
)paren
r_goto
id|err_inval
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|errp
op_assign
id|netlink_dump_start
c_func
(paren
id|rtnl
comma
id|skb
comma
id|nlh
comma
id|link-&gt;dumpit
comma
id|rtnetlink_done
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rlen
op_assign
id|NLMSG_ALIGN
c_func
(paren
id|nlh-&gt;nlmsg_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rlen
OG
id|skb-&gt;len
)paren
id|rlen
op_assign
id|skb-&gt;len
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|rlen
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kind
op_ne
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|rtnl_exlock_nowait
c_func
(paren
)paren
)paren
(brace
op_star
id|errp
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|exclusive
op_assign
l_int|1
suffix:semicolon
)brace
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
id|min_len
op_assign
id|rtm_min
(braket
id|sz_idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nlh-&gt;nlmsg_len
OL
id|min_len
)paren
r_goto
id|err_inval
suffix:semicolon
r_if
c_cond
(paren
id|nlh-&gt;nlmsg_len
OG
id|min_len
)paren
(brace
r_int
id|attrlen
op_assign
id|nlh-&gt;nlmsg_len
op_minus
id|NLMSG_ALIGN
c_func
(paren
id|min_len
)paren
suffix:semicolon
r_struct
id|rtattr
op_star
id|attr
op_assign
(paren
r_void
op_star
)paren
id|nlh
op_plus
id|NLMSG_ALIGN
c_func
(paren
id|min_len
)paren
suffix:semicolon
r_while
c_loop
(paren
id|RTA_OK
c_func
(paren
id|attr
comma
id|attrlen
)paren
)paren
(brace
r_int
id|flavor
op_assign
id|attr-&gt;rta_type
suffix:semicolon
r_if
c_cond
(paren
id|flavor
)paren
(brace
r_if
c_cond
(paren
id|flavor
OG
id|rta_max
(braket
id|sz_idx
)braket
)paren
r_goto
id|err_inval
suffix:semicolon
id|rta
(braket
id|flavor
op_minus
l_int|1
)braket
op_assign
id|attr
suffix:semicolon
)brace
id|attr
op_assign
id|RTA_NEXT
c_func
(paren
id|attr
comma
id|attrlen
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|link-&gt;doit
op_eq
l_int|NULL
)paren
id|link
op_assign
op_amp
(paren
id|rtnetlink_links
(braket
id|PF_UNSPEC
)braket
(braket
id|type
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;doit
op_eq
l_int|NULL
)paren
r_goto
id|err_inval
suffix:semicolon
id|err
op_assign
id|link
op_member_access_from_pointer
id|doit
c_func
(paren
id|skb
comma
id|nlh
comma
(paren
r_void
op_star
)paren
op_amp
id|rta
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exclusive
)paren
id|rtnl_exunlock
c_func
(paren
)paren
suffix:semicolon
op_star
id|errp
op_assign
id|err
suffix:semicolon
r_return
id|err
suffix:semicolon
id|err_inval
suffix:colon
r_if
c_cond
(paren
id|exclusive
)paren
id|rtnl_exunlock
c_func
(paren
)paren
suffix:semicolon
op_star
id|errp
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* &n; * Process one packet of messages.&n; * Malformed skbs with wrong lengths of messages are discarded silently.&n; */
DECL|function|rtnetlink_rcv_skb
r_extern
id|__inline__
r_int
id|rtnetlink_rcv_skb
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|nlmsghdr
op_star
id|nlh
suffix:semicolon
r_while
c_loop
(paren
id|skb-&gt;len
op_ge
id|NLMSG_SPACE
c_func
(paren
l_int|0
)paren
)paren
(brace
id|u32
id|rlen
suffix:semicolon
id|nlh
op_assign
(paren
r_struct
id|nlmsghdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|nlh-&gt;nlmsg_len
OL
r_sizeof
(paren
op_star
id|nlh
)paren
op_logical_or
id|skb-&gt;len
OL
id|nlh-&gt;nlmsg_len
)paren
r_return
l_int|0
suffix:semicolon
id|rlen
op_assign
id|NLMSG_ALIGN
c_func
(paren
id|nlh-&gt;nlmsg_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rlen
OG
id|skb-&gt;len
)paren
id|rlen
op_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|rtnetlink_rcv_msg
c_func
(paren
id|skb
comma
id|nlh
comma
op_amp
id|err
)paren
)paren
(brace
multiline_comment|/* Not error, but we must interrupt processing here:&n;&t;&t;&t; *   Note, that in this case we do not pull message&n;&t;&t;&t; *   from skb, it will be processed later.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|netlink_ack
c_func
(paren
id|skb
comma
id|nlh
comma
id|err
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nlh-&gt;nlmsg_flags
op_amp
id|NLM_F_ACK
)paren
id|netlink_ack
c_func
(paren
id|skb
comma
id|nlh
comma
l_int|0
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|rlen
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  rtnetlink input queue processing routine:&n; *&t;- try to acquire shared lock. If it is failed, defer processing.&n; *&t;- feed skbs to rtnetlink_rcv_skb, until it refuse a message,&n; *&t;  that will occur, when a dump started and/or acquisition of&n; *&t;  exclusive lock failed.&n; */
DECL|function|rtnetlink_rcv
r_static
r_void
id|rtnetlink_rcv
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|len
)paren
(brace
r_do
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|rtnl_shlock_nowait
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|rtnetlink_rcv_skb
c_func
(paren
id|skb
)paren
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;len
)paren
id|skb_queue_head
c_func
(paren
op_amp
id|sk-&gt;receive_queue
comma
id|skb
)paren
suffix:semicolon
r_else
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|rtnl_sem
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|rtnl
op_logical_and
id|rtnl-&gt;receive_queue.qlen
)paren
suffix:semicolon
)brace
DECL|variable|link_rtnetlink_table
r_static
r_struct
id|rtnetlink_link
id|link_rtnetlink_table
(braket
id|RTM_MAX
op_minus
id|RTM_BASE
op_plus
l_int|1
)braket
op_assign
(brace
(braket
id|RTM_GETLINK
op_minus
id|RTM_BASE
)braket
op_assign
(brace
dot
id|dumpit
op_assign
id|rtnetlink_dump_ifinfo
)brace
comma
(braket
id|RTM_SETLINK
op_minus
id|RTM_BASE
)braket
op_assign
(brace
dot
id|doit
op_assign
id|do_setlink
)brace
comma
(braket
id|RTM_GETADDR
op_minus
id|RTM_BASE
)braket
op_assign
(brace
dot
id|dumpit
op_assign
id|rtnetlink_dump_all
)brace
comma
(braket
id|RTM_GETROUTE
op_minus
id|RTM_BASE
)braket
op_assign
(brace
dot
id|dumpit
op_assign
id|rtnetlink_dump_all
)brace
comma
(braket
id|RTM_NEWNEIGH
op_minus
id|RTM_BASE
)braket
op_assign
(brace
dot
id|doit
op_assign
id|neigh_add
)brace
comma
(braket
id|RTM_DELNEIGH
op_minus
id|RTM_BASE
)braket
op_assign
(brace
dot
id|doit
op_assign
id|neigh_delete
)brace
comma
(braket
id|RTM_GETNEIGH
op_minus
id|RTM_BASE
)braket
op_assign
(brace
dot
id|dumpit
op_assign
id|neigh_dump_info
)brace
)brace
suffix:semicolon
DECL|function|rtnetlink_event
r_static
r_int
id|rtnetlink_event
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|NETDEV_UNREGISTER
suffix:colon
id|rtmsg_ifinfo
c_func
(paren
id|RTM_DELLINK
comma
id|dev
comma
op_complement
l_int|0U
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NETDEV_REGISTER
suffix:colon
id|rtmsg_ifinfo
c_func
(paren
id|RTM_NEWLINK
comma
id|dev
comma
op_complement
l_int|0U
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NETDEV_UP
suffix:colon
r_case
id|NETDEV_DOWN
suffix:colon
id|rtmsg_ifinfo
c_func
(paren
id|RTM_NEWLINK
comma
id|dev
comma
id|IFF_UP
op_or
id|IFF_RUNNING
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NETDEV_CHANGE
suffix:colon
r_case
id|NETDEV_GOING_DOWN
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|rtmsg_ifinfo
c_func
(paren
id|RTM_NEWLINK
comma
id|dev
comma
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
DECL|variable|rtnetlink_dev_notifier
r_struct
id|notifier_block
id|rtnetlink_dev_notifier
op_assign
(brace
id|rtnetlink_event
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
DECL|function|rtnetlink_init
r_void
id|__init
id|rtnetlink_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef RTNL_DEBUG
id|printk
c_func
(paren
l_string|&quot;Initializing RT netlink socket&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|rtnl
op_assign
id|netlink_kernel_create
c_func
(paren
id|NETLINK_ROUTE
comma
id|rtnetlink_rcv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtnl
op_eq
l_int|NULL
)paren
id|panic
c_func
(paren
l_string|&quot;rtnetlink_init: cannot initialize rtnetlink&bslash;n&quot;
)paren
suffix:semicolon
id|netlink_set_nonroot
c_func
(paren
id|NETLINK_ROUTE
comma
id|NL_NONROOT_RECV
)paren
suffix:semicolon
id|register_netdevice_notifier
c_func
(paren
op_amp
id|rtnetlink_dev_notifier
)paren
suffix:semicolon
id|rtnetlink_links
(braket
id|PF_UNSPEC
)braket
op_assign
id|link_rtnetlink_table
suffix:semicolon
id|rtnetlink_links
(braket
id|PF_PACKET
)braket
op_assign
id|link_rtnetlink_table
suffix:semicolon
)brace
eof
