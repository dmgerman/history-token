multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;IPv4 Forwarding Information Base: policy rules.&n; *&n; * Version:&t;$Id: fib_rules.c,v 1.17 2001/10/31 21:55:54 davem Exp $&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Fixes:&n; * &t;&t;Rani Assaf&t;:&t;local_rule cannot be deleted&n; *&t;&t;Marc Boucher&t;:&t;routing by fwmark&n; */
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
macro_line|#include &lt;net/ip_fib.h&gt;
DECL|macro|FRprintk
mdefine_line|#define FRprintk(a...)
DECL|struct|fib_rule
r_struct
id|fib_rule
(brace
DECL|member|r_next
r_struct
id|fib_rule
op_star
id|r_next
suffix:semicolon
DECL|member|r_clntref
id|atomic_t
id|r_clntref
suffix:semicolon
DECL|member|r_preference
id|u32
id|r_preference
suffix:semicolon
DECL|member|r_table
r_int
r_char
id|r_table
suffix:semicolon
DECL|member|r_action
r_int
r_char
id|r_action
suffix:semicolon
DECL|member|r_dst_len
r_int
r_char
id|r_dst_len
suffix:semicolon
DECL|member|r_src_len
r_int
r_char
id|r_src_len
suffix:semicolon
DECL|member|r_src
id|u32
id|r_src
suffix:semicolon
DECL|member|r_srcmask
id|u32
id|r_srcmask
suffix:semicolon
DECL|member|r_dst
id|u32
id|r_dst
suffix:semicolon
DECL|member|r_dstmask
id|u32
id|r_dstmask
suffix:semicolon
DECL|member|r_srcmap
id|u32
id|r_srcmap
suffix:semicolon
DECL|member|r_flags
id|u8
id|r_flags
suffix:semicolon
DECL|member|r_tos
id|u8
id|r_tos
suffix:semicolon
macro_line|#ifdef CONFIG_IP_ROUTE_FWMARK
DECL|member|r_fwmark
id|u32
id|r_fwmark
suffix:semicolon
macro_line|#endif
DECL|member|r_ifindex
r_int
id|r_ifindex
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ROUTE
DECL|member|r_tclassid
id|__u32
id|r_tclassid
suffix:semicolon
macro_line|#endif
DECL|member|r_ifname
r_char
id|r_ifname
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|r_dead
r_int
id|r_dead
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|default_rule
r_static
r_struct
id|fib_rule
id|default_rule
op_assign
(brace
dot
id|r_clntref
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|2
)paren
comma
dot
id|r_preference
op_assign
l_int|0x7FFF
comma
dot
id|r_table
op_assign
id|RT_TABLE_DEFAULT
comma
dot
id|r_action
op_assign
id|RTN_UNICAST
comma
)brace
suffix:semicolon
DECL|variable|main_rule
r_static
r_struct
id|fib_rule
id|main_rule
op_assign
(brace
dot
id|r_next
op_assign
op_amp
id|default_rule
comma
dot
id|r_clntref
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|2
)paren
comma
dot
id|r_preference
op_assign
l_int|0x7FFE
comma
dot
id|r_table
op_assign
id|RT_TABLE_MAIN
comma
dot
id|r_action
op_assign
id|RTN_UNICAST
comma
)brace
suffix:semicolon
DECL|variable|local_rule
r_static
r_struct
id|fib_rule
id|local_rule
op_assign
(brace
dot
id|r_next
op_assign
op_amp
id|main_rule
comma
dot
id|r_clntref
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|2
)paren
comma
dot
id|r_table
op_assign
id|RT_TABLE_LOCAL
comma
dot
id|r_action
op_assign
id|RTN_UNICAST
comma
)brace
suffix:semicolon
DECL|variable|fib_rules
r_static
r_struct
id|fib_rule
op_star
id|fib_rules
op_assign
op_amp
id|local_rule
suffix:semicolon
DECL|variable|fib_rules_lock
r_static
id|rwlock_t
id|fib_rules_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|function|inet_rtm_delrule
r_int
id|inet_rtm_delrule
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
id|rtm
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
r_struct
id|fib_rule
op_star
id|r
comma
op_star
op_star
id|rp
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ESRCH
suffix:semicolon
r_for
c_loop
(paren
id|rp
op_assign
op_amp
id|fib_rules
suffix:semicolon
(paren
id|r
op_assign
op_star
id|rp
)paren
op_ne
l_int|NULL
suffix:semicolon
id|rp
op_assign
op_amp
id|r-&gt;r_next
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|rta
(braket
id|RTA_SRC
op_minus
l_int|1
)braket
op_logical_or
id|memcmp
c_func
(paren
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_SRC
op_minus
l_int|1
)braket
)paren
comma
op_amp
id|r-&gt;r_src
comma
l_int|4
)paren
op_eq
l_int|0
)paren
op_logical_and
id|rtm-&gt;rtm_src_len
op_eq
id|r-&gt;r_src_len
op_logical_and
id|rtm-&gt;rtm_dst_len
op_eq
id|r-&gt;r_dst_len
op_logical_and
(paren
op_logical_neg
id|rta
(braket
id|RTA_DST
op_minus
l_int|1
)braket
op_logical_or
id|memcmp
c_func
(paren
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_DST
op_minus
l_int|1
)braket
)paren
comma
op_amp
id|r-&gt;r_dst
comma
l_int|4
)paren
op_eq
l_int|0
)paren
op_logical_and
id|rtm-&gt;rtm_tos
op_eq
id|r-&gt;r_tos
op_logical_and
macro_line|#ifdef CONFIG_IP_ROUTE_FWMARK
(paren
op_logical_neg
id|rta
(braket
id|RTA_PROTOINFO
op_minus
l_int|1
)braket
op_logical_or
id|memcmp
c_func
(paren
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_PROTOINFO
op_minus
l_int|1
)braket
)paren
comma
op_amp
id|r-&gt;r_fwmark
comma
l_int|4
)paren
op_eq
l_int|0
)paren
op_logical_and
macro_line|#endif
(paren
op_logical_neg
id|rtm-&gt;rtm_type
op_logical_or
id|rtm-&gt;rtm_type
op_eq
id|r-&gt;r_action
)paren
op_logical_and
(paren
op_logical_neg
id|rta
(braket
id|RTA_PRIORITY
op_minus
l_int|1
)braket
op_logical_or
id|memcmp
c_func
(paren
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_PRIORITY
op_minus
l_int|1
)braket
)paren
comma
op_amp
id|r-&gt;r_preference
comma
l_int|4
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
op_logical_neg
id|rta
(braket
id|RTA_IIF
op_minus
l_int|1
)braket
op_logical_or
id|strcmp
c_func
(paren
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_IIF
op_minus
l_int|1
)braket
)paren
comma
id|r-&gt;r_ifname
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
op_logical_neg
id|rtm-&gt;rtm_table
op_logical_or
(paren
id|r
op_logical_and
id|rtm-&gt;rtm_table
op_eq
id|r-&gt;r_table
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
op_amp
id|local_rule
)paren
r_break
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
op_star
id|rp
op_assign
id|r-&gt;r_next
suffix:semicolon
id|r-&gt;r_dead
op_assign
l_int|1
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
id|fib_rule_put
c_func
(paren
id|r
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* Allocate new unique table id */
DECL|function|fib_empty_table
r_static
r_struct
id|fib_table
op_star
id|fib_empty_table
c_func
(paren
r_void
)paren
(brace
r_int
id|id
suffix:semicolon
r_for
c_loop
(paren
id|id
op_assign
l_int|1
suffix:semicolon
id|id
op_le
id|RT_TABLE_MAX
suffix:semicolon
id|id
op_increment
)paren
r_if
c_cond
(paren
id|fib_tables
(braket
id|id
)braket
op_eq
l_int|NULL
)paren
r_return
id|__fib_new_table
c_func
(paren
id|id
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|fib_rule_put
r_void
id|fib_rule_put
c_func
(paren
r_struct
id|fib_rule
op_star
id|r
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|r-&gt;r_clntref
)paren
)paren
(brace
r_if
c_cond
(paren
id|r-&gt;r_dead
)paren
id|kfree
c_func
(paren
id|r
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;Freeing alive rule %p&bslash;n&quot;
comma
id|r
)paren
suffix:semicolon
)brace
)brace
DECL|function|inet_rtm_newrule
r_int
id|inet_rtm_newrule
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
id|rtm
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
r_struct
id|fib_rule
op_star
id|r
comma
op_star
id|new_r
comma
op_star
op_star
id|rp
suffix:semicolon
r_int
r_char
id|table_id
suffix:semicolon
r_if
c_cond
(paren
id|rtm-&gt;rtm_src_len
OG
l_int|32
op_logical_or
id|rtm-&gt;rtm_dst_len
OG
l_int|32
op_logical_or
(paren
id|rtm-&gt;rtm_tos
op_amp
op_complement
id|IPTOS_TOS_MASK
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|rta
(braket
id|RTA_IIF
op_minus
l_int|1
)braket
op_logical_and
id|RTA_PAYLOAD
c_func
(paren
id|rta
(braket
id|RTA_IIF
op_minus
l_int|1
)braket
)paren
OG
id|IFNAMSIZ
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|table_id
op_assign
id|rtm-&gt;rtm_table
suffix:semicolon
r_if
c_cond
(paren
id|table_id
op_eq
id|RT_TABLE_UNSPEC
)paren
(brace
r_struct
id|fib_table
op_star
id|table
suffix:semicolon
r_if
c_cond
(paren
id|rtm-&gt;rtm_type
op_eq
id|RTN_UNICAST
op_logical_or
id|rtm-&gt;rtm_type
op_eq
id|RTN_NAT
)paren
(brace
r_if
c_cond
(paren
(paren
id|table
op_assign
id|fib_empty_table
c_func
(paren
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOBUFS
suffix:semicolon
id|table_id
op_assign
id|table-&gt;tb_id
suffix:semicolon
)brace
)brace
id|new_r
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|new_r
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_r
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|new_r
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|new_r
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rta
(braket
id|RTA_SRC
op_minus
l_int|1
)braket
)paren
id|memcpy
c_func
(paren
op_amp
id|new_r-&gt;r_src
comma
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_SRC
op_minus
l_int|1
)braket
)paren
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rta
(braket
id|RTA_DST
op_minus
l_int|1
)braket
)paren
id|memcpy
c_func
(paren
op_amp
id|new_r-&gt;r_dst
comma
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_DST
op_minus
l_int|1
)braket
)paren
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rta
(braket
id|RTA_GATEWAY
op_minus
l_int|1
)braket
)paren
id|memcpy
c_func
(paren
op_amp
id|new_r-&gt;r_srcmap
comma
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_GATEWAY
op_minus
l_int|1
)braket
)paren
comma
l_int|4
)paren
suffix:semicolon
id|new_r-&gt;r_src_len
op_assign
id|rtm-&gt;rtm_src_len
suffix:semicolon
id|new_r-&gt;r_dst_len
op_assign
id|rtm-&gt;rtm_dst_len
suffix:semicolon
id|new_r-&gt;r_srcmask
op_assign
id|inet_make_mask
c_func
(paren
id|rtm-&gt;rtm_src_len
)paren
suffix:semicolon
id|new_r-&gt;r_dstmask
op_assign
id|inet_make_mask
c_func
(paren
id|rtm-&gt;rtm_dst_len
)paren
suffix:semicolon
id|new_r-&gt;r_tos
op_assign
id|rtm-&gt;rtm_tos
suffix:semicolon
macro_line|#ifdef CONFIG_IP_ROUTE_FWMARK
r_if
c_cond
(paren
id|rta
(braket
id|RTA_PROTOINFO
op_minus
l_int|1
)braket
)paren
id|memcpy
c_func
(paren
op_amp
id|new_r-&gt;r_fwmark
comma
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_PROTOINFO
op_minus
l_int|1
)braket
)paren
comma
l_int|4
)paren
suffix:semicolon
macro_line|#endif
id|new_r-&gt;r_action
op_assign
id|rtm-&gt;rtm_type
suffix:semicolon
id|new_r-&gt;r_flags
op_assign
id|rtm-&gt;rtm_flags
suffix:semicolon
r_if
c_cond
(paren
id|rta
(braket
id|RTA_PRIORITY
op_minus
l_int|1
)braket
)paren
id|memcpy
c_func
(paren
op_amp
id|new_r-&gt;r_preference
comma
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_PRIORITY
op_minus
l_int|1
)braket
)paren
comma
l_int|4
)paren
suffix:semicolon
id|new_r-&gt;r_table
op_assign
id|table_id
suffix:semicolon
r_if
c_cond
(paren
id|rta
(braket
id|RTA_IIF
op_minus
l_int|1
)braket
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|memcpy
c_func
(paren
id|new_r-&gt;r_ifname
comma
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_IIF
op_minus
l_int|1
)braket
)paren
comma
id|IFNAMSIZ
)paren
suffix:semicolon
id|new_r-&gt;r_ifname
(braket
id|IFNAMSIZ
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|new_r-&gt;r_ifindex
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev
op_assign
id|__dev_get_by_name
c_func
(paren
id|new_r-&gt;r_ifname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
id|new_r-&gt;r_ifindex
op_assign
id|dev-&gt;ifindex
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_CLS_ROUTE
r_if
c_cond
(paren
id|rta
(braket
id|RTA_FLOW
op_minus
l_int|1
)braket
)paren
id|memcpy
c_func
(paren
op_amp
id|new_r-&gt;r_tclassid
comma
id|RTA_DATA
c_func
(paren
id|rta
(braket
id|RTA_FLOW
op_minus
l_int|1
)braket
)paren
comma
l_int|4
)paren
suffix:semicolon
macro_line|#endif
id|rp
op_assign
op_amp
id|fib_rules
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_r-&gt;r_preference
)paren
(brace
id|r
op_assign
id|fib_rules
suffix:semicolon
r_if
c_cond
(paren
id|r
op_logical_and
(paren
id|r
op_assign
id|r-&gt;r_next
)paren
op_ne
l_int|NULL
)paren
(brace
id|rp
op_assign
op_amp
id|fib_rules-&gt;r_next
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;r_preference
)paren
id|new_r-&gt;r_preference
op_assign
id|r-&gt;r_preference
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
id|r
op_assign
op_star
id|rp
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|r-&gt;r_preference
OG
id|new_r-&gt;r_preference
)paren
r_break
suffix:semicolon
id|rp
op_assign
op_amp
id|r-&gt;r_next
suffix:semicolon
)brace
id|new_r-&gt;r_next
op_assign
id|r
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|new_r-&gt;r_clntref
)paren
suffix:semicolon
id|write_lock_bh
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
op_star
id|rp
op_assign
id|new_r
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fib_rules_map_destination
id|u32
id|fib_rules_map_destination
c_func
(paren
id|u32
id|daddr
comma
r_struct
id|fib_result
op_star
id|res
)paren
(brace
id|u32
id|mask
op_assign
id|inet_make_mask
c_func
(paren
id|res-&gt;prefixlen
)paren
suffix:semicolon
r_return
(paren
id|daddr
op_amp
op_complement
id|mask
)paren
op_or
id|res-&gt;fi-&gt;fib_nh-&gt;nh_gw
suffix:semicolon
)brace
DECL|function|fib_rules_policy
id|u32
id|fib_rules_policy
c_func
(paren
id|u32
id|saddr
comma
r_struct
id|fib_result
op_star
id|res
comma
r_int
op_star
id|flags
)paren
(brace
r_struct
id|fib_rule
op_star
id|r
op_assign
id|res-&gt;r
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;r_action
op_eq
id|RTN_NAT
)paren
(brace
r_int
id|addrtype
op_assign
id|inet_addr_type
c_func
(paren
id|r-&gt;r_srcmap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addrtype
op_eq
id|RTN_NAT
)paren
(brace
multiline_comment|/* Packet is from  translated source; remember it */
id|saddr
op_assign
(paren
id|saddr
op_amp
op_complement
id|r-&gt;r_srcmask
)paren
op_or
id|r-&gt;r_srcmap
suffix:semicolon
op_star
id|flags
op_or_assign
id|RTCF_SNAT
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addrtype
op_eq
id|RTN_LOCAL
op_logical_or
id|r-&gt;r_srcmap
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Packet is from masqueraded source; remember it */
id|saddr
op_assign
id|r-&gt;r_srcmap
suffix:semicolon
op_star
id|flags
op_or_assign
id|RTCF_MASQ
suffix:semicolon
)brace
)brace
r_return
id|saddr
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_CLS_ROUTE
DECL|function|fib_rules_tclass
id|u32
id|fib_rules_tclass
c_func
(paren
r_struct
id|fib_result
op_star
id|res
)paren
(brace
r_if
c_cond
(paren
id|res-&gt;r
)paren
r_return
id|res-&gt;r-&gt;r_tclassid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|fib_rules_detach
r_static
r_void
id|fib_rules_detach
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|fib_rule
op_star
id|r
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
id|fib_rules
suffix:semicolon
id|r
suffix:semicolon
id|r
op_assign
id|r-&gt;r_next
)paren
(brace
r_if
c_cond
(paren
id|r-&gt;r_ifindex
op_eq
id|dev-&gt;ifindex
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
id|r-&gt;r_ifindex
op_assign
op_minus
l_int|1
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|fib_rules_attach
r_static
r_void
id|fib_rules_attach
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|fib_rule
op_star
id|r
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
id|fib_rules
suffix:semicolon
id|r
suffix:semicolon
id|r
op_assign
id|r-&gt;r_next
)paren
(brace
r_if
c_cond
(paren
id|r-&gt;r_ifindex
op_eq
op_minus
l_int|1
op_logical_and
id|strcmp
c_func
(paren
id|dev-&gt;name
comma
id|r-&gt;r_ifname
)paren
op_eq
l_int|0
)paren
(brace
id|write_lock_bh
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
id|r-&gt;r_ifindex
op_assign
id|dev-&gt;ifindex
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|fib_lookup
r_int
id|fib_lookup
c_func
(paren
r_const
r_struct
id|flowi
op_star
id|flp
comma
r_struct
id|fib_result
op_star
id|res
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|fib_rule
op_star
id|r
comma
op_star
id|policy
suffix:semicolon
r_struct
id|fib_table
op_star
id|tb
suffix:semicolon
id|u32
id|daddr
op_assign
id|flp-&gt;fl4_dst
suffix:semicolon
id|u32
id|saddr
op_assign
id|flp-&gt;fl4_src
suffix:semicolon
id|FRprintk
c_func
(paren
l_string|&quot;Lookup: %u.%u.%u.%u &lt;- %u.%u.%u.%u &quot;
comma
id|NIPQUAD
c_func
(paren
id|flp-&gt;fl4_dst
)paren
comma
id|NIPQUAD
c_func
(paren
id|flp-&gt;fl4_src
)paren
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
id|fib_rules
suffix:semicolon
id|r
suffix:semicolon
id|r
op_assign
id|r-&gt;r_next
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|saddr
op_xor
id|r-&gt;r_src
)paren
op_amp
id|r-&gt;r_srcmask
)paren
op_logical_or
(paren
(paren
id|daddr
op_xor
id|r-&gt;r_dst
)paren
op_amp
id|r-&gt;r_dstmask
)paren
op_logical_or
macro_line|#ifdef CONFIG_IP_ROUTE_TOS
(paren
id|r-&gt;r_tos
op_logical_and
id|r-&gt;r_tos
op_ne
id|flp-&gt;fl4_tos
)paren
op_logical_or
macro_line|#endif
macro_line|#ifdef CONFIG_IP_ROUTE_FWMARK
(paren
id|r-&gt;r_fwmark
op_logical_and
id|r-&gt;r_fwmark
op_ne
id|flp-&gt;fl4_fwmark
)paren
op_logical_or
macro_line|#endif
(paren
id|r-&gt;r_ifindex
op_logical_and
id|r-&gt;r_ifindex
op_ne
id|flp-&gt;iif
)paren
)paren
r_continue
suffix:semicolon
id|FRprintk
c_func
(paren
l_string|&quot;tb %d r %d &quot;
comma
id|r-&gt;r_table
comma
id|r-&gt;r_action
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|r-&gt;r_action
)paren
(brace
r_case
id|RTN_UNICAST
suffix:colon
r_case
id|RTN_NAT
suffix:colon
id|policy
op_assign
id|r
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RTN_UNREACHABLE
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENETUNREACH
suffix:semicolon
r_default
suffix:colon
r_case
id|RTN_BLACKHOLE
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|RTN_PROHIBIT
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tb
op_assign
id|fib_get_table
c_func
(paren
id|r-&gt;r_table
)paren
)paren
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|err
op_assign
id|tb
op_member_access_from_pointer
id|tb_lookup
c_func
(paren
id|tb
comma
id|flp
comma
id|res
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
id|res-&gt;r
op_assign
id|policy
suffix:semicolon
r_if
c_cond
(paren
id|policy
)paren
id|atomic_inc
c_func
(paren
op_amp
id|policy-&gt;r_clntref
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
OL
l_int|0
op_logical_and
id|err
op_ne
op_minus
id|EAGAIN
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
id|FRprintk
c_func
(paren
l_string|&quot;FAILURE&bslash;n&quot;
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENETUNREACH
suffix:semicolon
)brace
DECL|function|fib_select_default
r_void
id|fib_select_default
c_func
(paren
r_const
r_struct
id|flowi
op_star
id|flp
comma
r_struct
id|fib_result
op_star
id|res
)paren
(brace
r_if
c_cond
(paren
id|res-&gt;r
op_logical_and
id|res-&gt;r-&gt;r_action
op_eq
id|RTN_UNICAST
op_logical_and
id|FIB_RES_GW
c_func
(paren
op_star
id|res
)paren
op_logical_and
id|FIB_RES_NH
id|res.nh_scope
op_eq
id|RT_SCOPE_LINK
)paren
(brace
r_struct
id|fib_table
op_star
id|tb
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
id|res-&gt;r-&gt;r_table
)paren
)paren
op_ne
l_int|NULL
)paren
id|tb
op_member_access_from_pointer
id|tb_select_default
c_func
(paren
id|tb
comma
id|flp
comma
id|res
)paren
suffix:semicolon
)brace
)brace
DECL|function|fib_rules_event
r_static
r_int
id|fib_rules_event
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
r_if
c_cond
(paren
id|event
op_eq
id|NETDEV_UNREGISTER
)paren
id|fib_rules_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|event
op_eq
id|NETDEV_REGISTER
)paren
id|fib_rules_attach
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|fib_rules_notifier
r_struct
id|notifier_block
id|fib_rules_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|fib_rules_event
comma
)brace
suffix:semicolon
DECL|function|inet_fill_rule
r_static
id|__inline__
r_int
id|inet_fill_rule
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|fib_rule
op_star
id|r
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
(brace
r_struct
id|rtmsg
op_star
id|rtm
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
id|NETLINK_CREDS
c_func
(paren
id|cb-&gt;skb
)paren
op_member_access_from_pointer
id|pid
comma
id|cb-&gt;nlh-&gt;nlmsg_seq
comma
id|RTM_NEWRULE
comma
r_sizeof
(paren
op_star
id|rtm
)paren
)paren
suffix:semicolon
id|rtm
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
id|rtm-&gt;rtm_family
op_assign
id|AF_INET
suffix:semicolon
id|rtm-&gt;rtm_dst_len
op_assign
id|r-&gt;r_dst_len
suffix:semicolon
id|rtm-&gt;rtm_src_len
op_assign
id|r-&gt;r_src_len
suffix:semicolon
id|rtm-&gt;rtm_tos
op_assign
id|r-&gt;r_tos
suffix:semicolon
macro_line|#ifdef CONFIG_IP_ROUTE_FWMARK
r_if
c_cond
(paren
id|r-&gt;r_fwmark
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|RTA_PROTOINFO
comma
l_int|4
comma
op_amp
id|r-&gt;r_fwmark
)paren
suffix:semicolon
macro_line|#endif
id|rtm-&gt;rtm_table
op_assign
id|r-&gt;r_table
suffix:semicolon
id|rtm-&gt;rtm_protocol
op_assign
l_int|0
suffix:semicolon
id|rtm-&gt;rtm_scope
op_assign
l_int|0
suffix:semicolon
id|rtm-&gt;rtm_type
op_assign
id|r-&gt;r_action
suffix:semicolon
id|rtm-&gt;rtm_flags
op_assign
id|r-&gt;r_flags
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;r_dst_len
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|RTA_DST
comma
l_int|4
comma
op_amp
id|r-&gt;r_dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;r_src_len
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|RTA_SRC
comma
l_int|4
comma
op_amp
id|r-&gt;r_src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;r_ifname
(braket
l_int|0
)braket
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|RTA_IIF
comma
id|IFNAMSIZ
comma
op_amp
id|r-&gt;r_ifname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;r_preference
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|RTA_PRIORITY
comma
l_int|4
comma
op_amp
id|r-&gt;r_preference
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;r_srcmap
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|RTA_GATEWAY
comma
l_int|4
comma
op_amp
id|r-&gt;r_srcmap
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ROUTE
r_if
c_cond
(paren
id|r-&gt;r_tclassid
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|RTA_FLOW
comma
l_int|4
comma
op_amp
id|r-&gt;r_tclassid
)paren
suffix:semicolon
macro_line|#endif
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
DECL|function|inet_dump_rules
r_int
id|inet_dump_rules
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
id|fib_rule
op_star
id|r
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|fib_rules_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
id|fib_rules
comma
id|idx
op_assign
l_int|0
suffix:semicolon
id|r
suffix:semicolon
id|r
op_assign
id|r-&gt;r_next
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
id|inet_fill_rule
c_func
(paren
id|skb
comma
id|r
comma
id|cb
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|fib_rules_lock
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
DECL|function|fib_rules_init
r_void
id|__init
id|fib_rules_init
c_func
(paren
r_void
)paren
(brace
id|register_netdevice_notifier
c_func
(paren
op_amp
id|fib_rules_notifier
)paren
suffix:semicolon
)brace
eof
