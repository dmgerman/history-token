multiline_comment|/*&n; * Generic HDLC support routines for Linux&n; *&n; * Copyright (C) 1999 - 2001 Krzysztof Halasa &lt;khc@pm.waw.pl&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Current status:&n; *    - this is work in progress&n; *    - not heavily tested on SMP&n; *    - currently supported:&n; *&t;* raw IP-in-HDLC&n; *&t;* Cisco HDLC&n; *&t;* Frame Relay with ANSI or CCITT LMI (both user and network side)&n; *&t;* PPP&n; *&t;* X.25&n; *&n; * Use sethdlc utility to set line parameters, protocol and PVCs&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/pkt_sched.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/lapb.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/hdlc.h&gt;
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;HDLC support module revision 1.08&quot;
suffix:semicolon
DECL|function|hdlc_change_mtu
r_static
r_int
id|hdlc_change_mtu
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|new_mtu
)paren
(brace
r_if
c_cond
(paren
(paren
id|new_mtu
OL
l_int|68
)paren
op_logical_or
(paren
id|new_mtu
OG
id|HDLC_MAX_MTU
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev-&gt;mtu
op_assign
id|new_mtu
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hdlc_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|hdlc_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
op_amp
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|stats
suffix:semicolon
)brace
DECL|function|hdlc_rcv
r_static
r_int
id|hdlc_rcv
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
r_struct
id|packet_type
op_star
id|p
)paren
(brace
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hdlc_ioctl
r_int
id|hdlc_ioctl
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
comma
r_int
id|cmd
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
r_int
r_int
id|proto
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|SIOCWANDEV
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|ifr-&gt;ifr_settings-&gt;type
)paren
(brace
r_case
id|IF_PROTO_HDLC
suffix:colon
r_case
id|IF_PROTO_PPP
suffix:colon
r_case
id|IF_PROTO_CISCO
suffix:colon
r_case
id|IF_PROTO_FR
suffix:colon
r_case
id|IF_PROTO_X25
suffix:colon
id|proto
op_assign
id|ifr-&gt;ifr_settings-&gt;type
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|proto
op_assign
id|hdlc-&gt;proto
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|proto
)paren
(brace
macro_line|#ifdef CONFIG_HDLC_RAW
r_case
id|IF_PROTO_HDLC
suffix:colon
r_return
id|hdlc_raw_ioctl
c_func
(paren
id|hdlc
comma
id|ifr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HDLC_PPP
r_case
id|IF_PROTO_PPP
suffix:colon
r_return
id|hdlc_ppp_ioctl
c_func
(paren
id|hdlc
comma
id|ifr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HDLC_CISCO
r_case
id|IF_PROTO_CISCO
suffix:colon
r_return
id|hdlc_cisco_ioctl
c_func
(paren
id|hdlc
comma
id|ifr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HDLC_FR
r_case
id|IF_PROTO_FR
suffix:colon
r_return
id|hdlc_fr_ioctl
c_func
(paren
id|hdlc
comma
id|ifr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HDLC_X25
r_case
id|IF_PROTO_X25
suffix:colon
r_return
id|hdlc_x25_ioctl
c_func
(paren
id|hdlc
comma
id|ifr
)paren
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
)brace
DECL|function|register_hdlc_device
r_int
id|register_hdlc_device
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
(brace
r_int
id|result
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|hdlc_to_dev
c_func
(paren
id|hdlc
)paren
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|hdlc_get_stats
suffix:semicolon
id|dev-&gt;change_mtu
op_assign
id|hdlc_change_mtu
suffix:semicolon
id|dev-&gt;mtu
op_assign
id|HDLC_MAX_MTU
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_RAWHDLC
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
l_int|16
suffix:semicolon
id|dev-&gt;flags
op_assign
id|IFF_POINTOPOINT
op_or
id|IFF_NOARP
suffix:semicolon
id|hdlc-&gt;proto
op_assign
op_minus
l_int|1
suffix:semicolon
id|hdlc-&gt;detach
op_assign
l_int|NULL
suffix:semicolon
id|result
op_assign
id|dev_alloc_name
c_func
(paren
id|dev
comma
l_string|&quot;hdlc%d&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|result
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_hdlc_device
r_void
id|unregister_hdlc_device
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
(brace
id|hdlc_detach
c_func
(paren
id|hdlc
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|hdlc_to_dev
c_func
(paren
id|hdlc
)paren
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Krzysztof Halasa &lt;khc@pm.waw.pl&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;HDLC support module&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|hdlc_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|hdlc_ioctl
)paren
suffix:semicolon
DECL|variable|register_hdlc_device
id|EXPORT_SYMBOL
c_func
(paren
id|register_hdlc_device
)paren
suffix:semicolon
DECL|variable|unregister_hdlc_device
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_hdlc_device
)paren
suffix:semicolon
DECL|variable|hdlc_packet_type
r_struct
id|packet_type
id|hdlc_packet_type
op_assign
(brace
id|__constant_htons
c_func
(paren
id|ETH_P_HDLC
)paren
comma
l_int|NULL
comma
id|hdlc_rcv
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|hdlc_module_init
r_static
r_int
id|__init
id|hdlc_module_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
id|dev_add_pack
c_func
(paren
op_amp
id|hdlc_packet_type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hdlc_module_exit
r_static
r_void
id|__exit
id|hdlc_module_exit
c_func
(paren
r_void
)paren
(brace
id|dev_remove_pack
c_func
(paren
op_amp
id|hdlc_packet_type
)paren
suffix:semicolon
)brace
DECL|variable|hdlc_module_init
id|module_init
c_func
(paren
id|hdlc_module_init
)paren
suffix:semicolon
DECL|variable|hdlc_module_exit
id|module_exit
c_func
(paren
id|hdlc_module_exit
)paren
suffix:semicolon
eof