multiline_comment|/*&n; * Generic HDLC support routines for Linux&n; * Cisco HDLC support&n; *&n; * Copyright (C) 2000 - 2003 Krzysztof Halasa &lt;khc@pm.waw.pl&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License&n; * as published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/pkt_sched.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/lapb.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/hdlc.h&gt;
DECL|macro|DEBUG_HARD_HEADER
macro_line|#undef DEBUG_HARD_HEADER
DECL|macro|CISCO_MULTICAST
mdefine_line|#define CISCO_MULTICAST&t;&t;0x8F&t;/* Cisco multicast address */
DECL|macro|CISCO_UNICAST
mdefine_line|#define CISCO_UNICAST&t;&t;0x0F&t;/* Cisco unicast address */
DECL|macro|CISCO_KEEPALIVE
mdefine_line|#define CISCO_KEEPALIVE&t;&t;0x8035&t;/* Cisco keepalive protocol */
DECL|macro|CISCO_SYS_INFO
mdefine_line|#define CISCO_SYS_INFO&t;&t;0x2000&t;/* Cisco interface/system info */
DECL|macro|CISCO_ADDR_REQ
mdefine_line|#define CISCO_ADDR_REQ&t;&t;0&t;/* Cisco address request */
DECL|macro|CISCO_ADDR_REPLY
mdefine_line|#define CISCO_ADDR_REPLY&t;1&t;/* Cisco address reply */
DECL|macro|CISCO_KEEPALIVE_REQ
mdefine_line|#define CISCO_KEEPALIVE_REQ&t;2&t;/* Cisco keepalive request */
DECL|function|cisco_hard_header
r_static
r_int
id|cisco_hard_header
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
id|u16
id|type
comma
r_void
op_star
id|daddr
comma
r_void
op_star
id|saddr
comma
r_int
r_int
id|len
)paren
(brace
id|hdlc_header
op_star
id|data
suffix:semicolon
macro_line|#ifdef DEBUG_HARD_HEADER
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: cisco_hard_header called&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
macro_line|#endif
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
id|hdlc_header
)paren
)paren
suffix:semicolon
id|data
op_assign
(paren
id|hdlc_header
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|CISCO_KEEPALIVE
)paren
id|data-&gt;address
op_assign
id|CISCO_MULTICAST
suffix:semicolon
r_else
id|data-&gt;address
op_assign
id|CISCO_UNICAST
suffix:semicolon
id|data-&gt;control
op_assign
l_int|0
suffix:semicolon
id|data-&gt;protocol
op_assign
id|htons
c_func
(paren
id|type
)paren
suffix:semicolon
r_return
r_sizeof
(paren
id|hdlc_header
)paren
suffix:semicolon
)brace
DECL|function|cisco_keepalive_send
r_static
r_void
id|cisco_keepalive_send
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u32
id|type
comma
id|u32
id|par1
comma
id|u32
id|par2
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|cisco_packet
op_star
id|data
suffix:semicolon
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
r_sizeof
(paren
id|hdlc_header
)paren
op_plus
r_sizeof
(paren
id|cisco_packet
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Memory squeeze on cisco_keepalive_send()&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
id|cisco_hard_header
c_func
(paren
id|skb
comma
id|dev
comma
id|CISCO_KEEPALIVE
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|data
op_assign
(paren
id|cisco_packet
op_star
)paren
id|skb-&gt;tail
suffix:semicolon
id|data-&gt;type
op_assign
id|htonl
c_func
(paren
id|type
)paren
suffix:semicolon
id|data-&gt;par1
op_assign
id|htonl
c_func
(paren
id|par1
)paren
suffix:semicolon
id|data-&gt;par2
op_assign
id|htonl
c_func
(paren
id|par2
)paren
suffix:semicolon
id|data-&gt;rel
op_assign
l_int|0xFFFF
suffix:semicolon
multiline_comment|/* we will need do_div here if 1000 % HZ != 0 */
id|data-&gt;time
op_assign
id|htonl
c_func
(paren
(paren
id|jiffies
op_minus
id|INITIAL_JIFFIES
)paren
op_star
(paren
l_int|1000
op_div
id|HZ
)paren
)paren
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
id|cisco_packet
)paren
)paren
suffix:semicolon
id|skb-&gt;priority
op_assign
id|TC_PRIO_CONTROL
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|cisco_type_trans
r_static
r_int
r_int
id|cisco_type_trans
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
)paren
(brace
id|hdlc_header
op_star
id|data
op_assign
(paren
id|hdlc_header
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OL
r_sizeof
(paren
id|hdlc_header
)paren
)paren
r_return
id|__constant_htons
c_func
(paren
id|ETH_P_HDLC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;address
op_ne
id|CISCO_MULTICAST
op_logical_and
id|data-&gt;address
op_ne
id|CISCO_UNICAST
)paren
r_return
id|__constant_htons
c_func
(paren
id|ETH_P_HDLC
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|data-&gt;protocol
)paren
(brace
r_case
id|__constant_htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:colon
r_case
id|__constant_htons
c_func
(paren
id|ETH_P_IPX
)paren
suffix:colon
r_case
id|__constant_htons
c_func
(paren
id|ETH_P_IPV6
)paren
suffix:colon
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
id|hdlc_header
)paren
)paren
suffix:semicolon
r_return
id|data-&gt;protocol
suffix:semicolon
r_default
suffix:colon
r_return
id|__constant_htons
c_func
(paren
id|ETH_P_HDLC
)paren
suffix:semicolon
)brace
)brace
DECL|function|cisco_rx
r_static
r_int
id|cisco_rx
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|skb-&gt;dev
suffix:semicolon
id|hdlc_device
op_star
id|hdlc
op_assign
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
suffix:semicolon
id|hdlc_header
op_star
id|data
op_assign
(paren
id|hdlc_header
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|cisco_packet
op_star
id|cisco_data
suffix:semicolon
r_struct
id|in_device
op_star
id|in_dev
suffix:semicolon
id|u32
id|addr
comma
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OL
r_sizeof
(paren
id|hdlc_header
)paren
)paren
r_goto
id|rx_error
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;address
op_ne
id|CISCO_MULTICAST
op_logical_and
id|data-&gt;address
op_ne
id|CISCO_UNICAST
)paren
r_goto
id|rx_error
suffix:semicolon
r_switch
c_cond
(paren
id|ntohs
c_func
(paren
id|data-&gt;protocol
)paren
)paren
(brace
r_case
id|CISCO_SYS_INFO
suffix:colon
multiline_comment|/* Packet is not needed, drop it. */
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_RX_SUCCESS
suffix:semicolon
r_case
id|CISCO_KEEPALIVE
suffix:colon
r_if
c_cond
(paren
id|skb-&gt;len
op_ne
r_sizeof
(paren
id|hdlc_header
)paren
op_plus
id|CISCO_PACKET_LEN
op_logical_and
id|skb-&gt;len
op_ne
r_sizeof
(paren
id|hdlc_header
)paren
op_plus
id|CISCO_BIG_PACKET_LEN
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Invalid length of Cisco &quot;
l_string|&quot;control packet (%d bytes)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_goto
id|rx_error
suffix:semicolon
)brace
id|cisco_data
op_assign
(paren
id|cisco_packet
op_star
)paren
(paren
id|skb-&gt;data
op_plus
r_sizeof
(paren
id|hdlc_header
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ntohl
(paren
id|cisco_data-&gt;type
)paren
)paren
(brace
r_case
id|CISCO_ADDR_REQ
suffix:colon
multiline_comment|/* Stolen from syncppp.c :-) */
id|in_dev
op_assign
id|dev-&gt;ip_ptr
suffix:semicolon
id|addr
op_assign
l_int|0
suffix:semicolon
id|mask
op_assign
op_complement
l_int|0
suffix:semicolon
multiline_comment|/* is the mask correct? */
r_if
c_cond
(paren
id|in_dev
op_ne
l_int|NULL
)paren
(brace
r_struct
id|in_ifaddr
op_star
op_star
id|ifap
op_assign
op_amp
id|in_dev-&gt;ifa_list
suffix:semicolon
r_while
c_loop
(paren
op_star
id|ifap
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|dev-&gt;name
comma
(paren
op_star
id|ifap
)paren
op_member_access_from_pointer
id|ifa_label
)paren
op_eq
l_int|0
)paren
(brace
id|addr
op_assign
(paren
op_star
id|ifap
)paren
op_member_access_from_pointer
id|ifa_local
suffix:semicolon
id|mask
op_assign
(paren
op_star
id|ifap
)paren
op_member_access_from_pointer
id|ifa_mask
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ifap
op_assign
op_amp
(paren
op_star
id|ifap
)paren
op_member_access_from_pointer
id|ifa_next
suffix:semicolon
)brace
id|cisco_keepalive_send
c_func
(paren
id|dev
comma
id|CISCO_ADDR_REPLY
comma
id|addr
comma
id|mask
)paren
suffix:semicolon
)brace
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_RX_SUCCESS
suffix:semicolon
r_case
id|CISCO_ADDR_REPLY
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Unexpected Cisco IP address &quot;
l_string|&quot;reply&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_goto
id|rx_error
suffix:semicolon
r_case
id|CISCO_KEEPALIVE_REQ
suffix:colon
id|hdlc-&gt;state.cisco.rxseq
op_assign
id|ntohl
c_func
(paren
id|cisco_data-&gt;par1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;state.cisco.request_sent
op_logical_and
id|ntohl
c_func
(paren
id|cisco_data-&gt;par2
)paren
op_eq
id|hdlc-&gt;state.cisco.txseq
)paren
(brace
id|hdlc-&gt;state.cisco.last_poll
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdlc-&gt;state.cisco.up
)paren
(brace
id|u32
id|sec
comma
id|min
comma
id|hrs
comma
id|days
suffix:semicolon
id|sec
op_assign
id|ntohl
c_func
(paren
id|cisco_data-&gt;time
)paren
op_div
l_int|1000
suffix:semicolon
id|min
op_assign
id|sec
op_div
l_int|60
suffix:semicolon
id|sec
op_sub_assign
id|min
op_star
l_int|60
suffix:semicolon
id|hrs
op_assign
id|min
op_div
l_int|60
suffix:semicolon
id|min
op_sub_assign
id|hrs
op_star
l_int|60
suffix:semicolon
id|days
op_assign
id|hrs
op_div
l_int|24
suffix:semicolon
id|hrs
op_sub_assign
id|days
op_star
l_int|24
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Link up (peer &quot;
l_string|&quot;uptime %ud%uh%um%us)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|days
comma
id|hrs
comma
id|min
comma
id|sec
)paren
suffix:semicolon
id|netif_carrier_on
c_func
(paren
id|dev
)paren
suffix:semicolon
id|hdlc-&gt;state.cisco.up
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_RX_SUCCESS
suffix:semicolon
)brace
multiline_comment|/* switch(keepalive type) */
)brace
multiline_comment|/* switch(protocol) */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Unsupported protocol %x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|data-&gt;protocol
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_RX_DROP
suffix:semicolon
id|rx_error
suffix:colon
id|hdlc-&gt;stats.rx_errors
op_increment
suffix:semicolon
multiline_comment|/* Mark error */
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_RX_DROP
suffix:semicolon
)brace
DECL|function|cisco_timer
r_static
r_void
id|cisco_timer
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|arg
suffix:semicolon
id|hdlc_device
op_star
id|hdlc
op_assign
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;state.cisco.up
op_logical_and
id|time_after
c_func
(paren
id|jiffies
comma
id|hdlc-&gt;state.cisco.last_poll
op_plus
id|hdlc-&gt;state.cisco.settings.timeout
op_star
id|HZ
)paren
)paren
(brace
id|hdlc-&gt;state.cisco.up
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Link down&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|netif_carrier_off
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|cisco_keepalive_send
c_func
(paren
id|dev
comma
id|CISCO_KEEPALIVE_REQ
comma
op_increment
id|hdlc-&gt;state.cisco.txseq
comma
id|hdlc-&gt;state.cisco.rxseq
)paren
suffix:semicolon
id|hdlc-&gt;state.cisco.request_sent
op_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;state.cisco.timer.expires
op_assign
id|jiffies
op_plus
id|hdlc-&gt;state.cisco.settings.interval
op_star
id|HZ
suffix:semicolon
id|hdlc-&gt;state.cisco.timer.function
op_assign
id|cisco_timer
suffix:semicolon
id|hdlc-&gt;state.cisco.timer.data
op_assign
id|arg
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|hdlc-&gt;state.cisco.timer
)paren
suffix:semicolon
)brace
DECL|function|cisco_start
r_static
r_void
id|cisco_start
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|hdlc_device
op_star
id|hdlc
op_assign
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
suffix:semicolon
id|hdlc-&gt;state.cisco.up
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;state.cisco.request_sent
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;state.cisco.txseq
op_assign
id|hdlc-&gt;state.cisco.rxseq
op_assign
l_int|0
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|hdlc-&gt;state.cisco.timer
)paren
suffix:semicolon
id|hdlc-&gt;state.cisco.timer.expires
op_assign
id|jiffies
op_plus
id|HZ
suffix:semicolon
multiline_comment|/*First poll after 1s*/
id|hdlc-&gt;state.cisco.timer.function
op_assign
id|cisco_timer
suffix:semicolon
id|hdlc-&gt;state.cisco.timer.data
op_assign
(paren
r_int
r_int
)paren
id|dev
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|hdlc-&gt;state.cisco.timer
)paren
suffix:semicolon
)brace
DECL|function|cisco_stop
r_static
r_void
id|cisco_stop
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|hdlc_device
op_star
id|hdlc
op_assign
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|hdlc-&gt;state.cisco.timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|netif_carrier_ok
c_func
(paren
id|dev
)paren
)paren
id|netif_carrier_off
c_func
(paren
id|dev
)paren
suffix:semicolon
id|hdlc-&gt;state.cisco.up
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;state.cisco.request_sent
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|hdlc_cisco_ioctl
r_int
id|hdlc_cisco_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
)paren
(brace
id|cisco_proto
id|__user
op_star
id|cisco_s
op_assign
id|ifr-&gt;ifr_settings.ifs_ifsu.cisco
suffix:semicolon
r_const
r_int
id|size
op_assign
r_sizeof
(paren
id|cisco_proto
)paren
suffix:semicolon
id|cisco_proto
id|new_settings
suffix:semicolon
id|hdlc_device
op_star
id|hdlc
op_assign
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|result
suffix:semicolon
r_switch
c_cond
(paren
id|ifr-&gt;ifr_settings.type
)paren
(brace
r_case
id|IF_GET_PROTO
suffix:colon
id|ifr-&gt;ifr_settings.type
op_assign
id|IF_PROTO_CISCO
suffix:semicolon
r_if
c_cond
(paren
id|ifr-&gt;ifr_settings.size
OL
id|size
)paren
(brace
id|ifr-&gt;ifr_settings.size
op_assign
id|size
suffix:semicolon
multiline_comment|/* data size wanted */
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|cisco_s
comma
op_amp
id|hdlc-&gt;state.cisco.settings
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|IF_PROTO_CISCO
suffix:colon
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
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|new_settings
comma
id|cisco_s
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|new_settings.interval
OL
l_int|1
op_logical_or
id|new_settings.timeout
OL
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|result
op_assign
id|hdlc
op_member_access_from_pointer
id|attach
c_func
(paren
id|dev
comma
id|ENCODING_NRZ
comma
id|PARITY_CRC16_PR1_CCITT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
id|hdlc_proto_detach
c_func
(paren
id|hdlc
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|hdlc-&gt;state.cisco.settings
comma
op_amp
id|new_settings
comma
id|size
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|hdlc-&gt;proto
comma
l_int|0
comma
r_sizeof
(paren
id|hdlc-&gt;proto
)paren
)paren
suffix:semicolon
id|hdlc-&gt;proto.start
op_assign
id|cisco_start
suffix:semicolon
id|hdlc-&gt;proto.stop
op_assign
id|cisco_stop
suffix:semicolon
id|hdlc-&gt;proto.netif_rx
op_assign
id|cisco_rx
suffix:semicolon
id|hdlc-&gt;proto.type_trans
op_assign
id|cisco_type_trans
suffix:semicolon
id|hdlc-&gt;proto.id
op_assign
id|IF_PROTO_CISCO
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|hdlc-&gt;xmit
suffix:semicolon
id|dev-&gt;hard_header
op_assign
id|cisco_hard_header
suffix:semicolon
id|dev-&gt;hard_header_cache
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_CISCO
suffix:semicolon
id|dev-&gt;flags
op_assign
id|IFF_POINTOPOINT
op_or
id|IFF_NOARP
suffix:semicolon
id|dev-&gt;addr_len
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
