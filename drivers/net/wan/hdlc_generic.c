multiline_comment|/*&n; * Generic HDLC support routines for Linux&n; *&n; * Copyright (C) 1999 - 2003 Krzysztof Halasa &lt;khc@pm.waw.pl&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License&n; * as published by the Free Software Foundation.&n; *&n; * Currently supported:&n; *&t;* raw IP-in-HDLC&n; *&t;* Cisco HDLC&n; *&t;* Frame Relay with ANSI or CCITT LMI (both user and network side)&n; *&t;* PPP&n; *&t;* X.25&n; *&n; * Use sethdlc utility to set line parameters, protocol and PVCs&n; *&n; * How does it work:&n; * - proto.open(), close(), start(), stop() calls are serialized.&n; *   The order is: open, [ start, stop ... ] close ...&n; * - proto.start() and stop() are called with spin_lock_irq held.&n; */
macro_line|#include &lt;linux/config.h&gt;
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
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;HDLC support module revision 1.17&quot;
suffix:semicolon
DECL|macro|DEBUG_LINK
macro_line|#undef DEBUG_LINK
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
id|hdlc_stats
c_func
(paren
id|dev
)paren
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
id|hdlc-&gt;proto.netif_rx
)paren
r_return
id|hdlc-&gt;proto
dot
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|hdlc-&gt;stats.rx_dropped
op_increment
suffix:semicolon
multiline_comment|/* Shouldn&squot;t happen */
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_RX_DROP
suffix:semicolon
)brace
DECL|function|__hdlc_set_carrier_on
r_static
r_void
id|__hdlc_set_carrier_on
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
r_if
c_cond
(paren
id|hdlc-&gt;proto.start
)paren
r_return
id|hdlc-&gt;proto
dot
id|start
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_LINK
r_if
c_cond
(paren
id|netif_carrier_ok
c_func
(paren
id|dev
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hdlc_set_carrier_on(): already on&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|netif_carrier_on
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|__hdlc_set_carrier_off
r_static
r_void
id|__hdlc_set_carrier_off
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
r_if
c_cond
(paren
id|hdlc-&gt;proto.stop
)paren
r_return
id|hdlc-&gt;proto
dot
id|stop
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_LINK
r_if
c_cond
(paren
op_logical_neg
id|netif_carrier_ok
c_func
(paren
id|dev
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hdlc_set_carrier_off(): already off&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|netif_carrier_off
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|hdlc_set_carrier
r_void
id|hdlc_set_carrier
c_func
(paren
r_int
id|on
comma
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
r_int
r_int
id|flags
suffix:semicolon
id|on
op_assign
id|on
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUG_LINK
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;hdlc_set_carrier %i&bslash;n&quot;
comma
id|on
)paren
suffix:semicolon
macro_line|#endif
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hdlc-&gt;state_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;carrier
op_eq
id|on
)paren
r_goto
id|carrier_exit
suffix:semicolon
multiline_comment|/* no change in DCD line level */
macro_line|#ifdef DEBUG_LINK
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: carrier %s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|on
ques
c_cond
l_string|&quot;ON&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
macro_line|#endif
id|hdlc-&gt;carrier
op_assign
id|on
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdlc-&gt;open
)paren
r_goto
id|carrier_exit
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;carrier
)paren
id|__hdlc_set_carrier_on
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
id|__hdlc_set_carrier_off
c_func
(paren
id|dev
)paren
suffix:semicolon
id|carrier_exit
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hdlc-&gt;state_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Must be called by hardware driver when HDLC device is being opened */
DECL|function|hdlc_open
r_int
id|hdlc_open
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
macro_line|#ifdef DEBUG_LINK
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;hdlc_open() carrier %i open %i&bslash;n&quot;
comma
id|hdlc-&gt;carrier
comma
id|hdlc-&gt;open
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|hdlc-&gt;proto.id
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
multiline_comment|/* no protocol attached */
r_if
c_cond
(paren
id|hdlc-&gt;proto.open
)paren
(brace
r_int
id|result
op_assign
id|hdlc-&gt;proto
dot
id|open
c_func
(paren
id|dev
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
)brace
id|spin_lock_irq
c_func
(paren
op_amp
id|hdlc-&gt;state_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;carrier
)paren
id|__hdlc_set_carrier_on
c_func
(paren
id|dev
)paren
suffix:semicolon
id|hdlc-&gt;open
op_assign
l_int|1
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|hdlc-&gt;state_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Must be called by hardware driver when HDLC device is being closed */
DECL|function|hdlc_close
r_void
id|hdlc_close
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
macro_line|#ifdef DEBUG_LINK
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;hdlc_close() carrier %i open %i&bslash;n&quot;
comma
id|hdlc-&gt;carrier
comma
id|hdlc-&gt;open
)paren
suffix:semicolon
macro_line|#endif
id|spin_lock_irq
c_func
(paren
op_amp
id|hdlc-&gt;state_lock
)paren
suffix:semicolon
id|hdlc-&gt;open
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;carrier
)paren
id|__hdlc_set_carrier_off
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|hdlc-&gt;state_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;proto.close
)paren
id|hdlc-&gt;proto
dot
id|close
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_HDLC_RAW
DECL|macro|hdlc_raw_ioctl
mdefine_line|#define hdlc_raw_ioctl(dev, ifr)&t;-ENOSYS
macro_line|#endif
macro_line|#ifndef CONFIG_HDLC_RAW_ETH
DECL|macro|hdlc_raw_eth_ioctl
mdefine_line|#define hdlc_raw_eth_ioctl(dev, ifr)&t;-ENOSYS
macro_line|#endif
macro_line|#ifndef CONFIG_HDLC_PPP
DECL|macro|hdlc_ppp_ioctl
mdefine_line|#define hdlc_ppp_ioctl(dev, ifr)&t;-ENOSYS
macro_line|#endif
macro_line|#ifndef CONFIG_HDLC_CISCO
DECL|macro|hdlc_cisco_ioctl
mdefine_line|#define hdlc_cisco_ioctl(dev, ifr)&t;-ENOSYS
macro_line|#endif
macro_line|#ifndef CONFIG_HDLC_FR
DECL|macro|hdlc_fr_ioctl
mdefine_line|#define hdlc_fr_ioctl(dev, ifr)&t;&t;-ENOSYS
macro_line|#endif
macro_line|#ifndef CONFIG_HDLC_X25
DECL|macro|hdlc_x25_ioctl
mdefine_line|#define hdlc_x25_ioctl(dev, ifr)&t;-ENOSYS
macro_line|#endif
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
id|ifr-&gt;ifr_settings.type
)paren
(brace
r_case
id|IF_PROTO_HDLC
suffix:colon
r_case
id|IF_PROTO_HDLC_ETH
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
id|ifr-&gt;ifr_settings.type
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|proto
op_assign
id|hdlc-&gt;proto.id
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|proto
)paren
(brace
r_case
id|IF_PROTO_HDLC
suffix:colon
r_return
id|hdlc_raw_ioctl
c_func
(paren
id|dev
comma
id|ifr
)paren
suffix:semicolon
r_case
id|IF_PROTO_HDLC_ETH
suffix:colon
r_return
id|hdlc_raw_eth_ioctl
c_func
(paren
id|dev
comma
id|ifr
)paren
suffix:semicolon
r_case
id|IF_PROTO_PPP
suffix:colon
r_return
id|hdlc_ppp_ioctl
c_func
(paren
id|dev
comma
id|ifr
)paren
suffix:semicolon
r_case
id|IF_PROTO_CISCO
suffix:colon
r_return
id|hdlc_cisco_ioctl
c_func
(paren
id|dev
comma
id|ifr
)paren
suffix:semicolon
r_case
id|IF_PROTO_FR
suffix:colon
r_return
id|hdlc_fr_ioctl
c_func
(paren
id|dev
comma
id|ifr
)paren
suffix:semicolon
r_case
id|IF_PROTO_X25
suffix:colon
r_return
id|hdlc_x25_ioctl
c_func
(paren
id|dev
comma
id|ifr
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|hdlc_setup
r_static
r_void
id|hdlc_setup
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
id|hdlc-&gt;proto.id
op_assign
op_minus
l_int|1
suffix:semicolon
id|hdlc-&gt;proto.detach
op_assign
l_int|NULL
suffix:semicolon
id|hdlc-&gt;carrier
op_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;open
op_assign
l_int|0
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|hdlc-&gt;state_lock
)paren
suffix:semicolon
)brace
DECL|function|alloc_hdlcdev
r_struct
id|net_device
op_star
id|alloc_hdlcdev
c_func
(paren
r_void
op_star
id|priv
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|alloc_netdev
c_func
(paren
r_sizeof
(paren
id|hdlc_device
)paren
comma
l_string|&quot;hdlc%d&quot;
comma
id|hdlc_setup
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|priv
op_assign
id|priv
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
DECL|function|register_hdlc_device
r_int
id|register_hdlc_device
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
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
multiline_comment|/* no carrier until DCD goes up */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_hdlc_device
r_void
id|unregister_hdlc_device
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
id|hdlc_proto_detach
c_func
(paren
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|unregister_netdevice
c_func
(paren
id|dev
)paren
suffix:semicolon
id|rtnl_unlock
c_func
(paren
)paren
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
l_string|&quot;GPL v2&quot;
)paren
suffix:semicolon
DECL|variable|hdlc_open
id|EXPORT_SYMBOL
c_func
(paren
id|hdlc_open
)paren
suffix:semicolon
DECL|variable|hdlc_close
id|EXPORT_SYMBOL
c_func
(paren
id|hdlc_close
)paren
suffix:semicolon
DECL|variable|hdlc_set_carrier
id|EXPORT_SYMBOL
c_func
(paren
id|hdlc_set_carrier
)paren
suffix:semicolon
DECL|variable|hdlc_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|hdlc_ioctl
)paren
suffix:semicolon
DECL|variable|alloc_hdlcdev
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_hdlcdev
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
r_static
r_struct
id|packet_type
id|hdlc_packet_type
op_assign
(brace
dot
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_HDLC
)paren
comma
dot
id|func
op_assign
id|hdlc_rcv
comma
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
