multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;net/rose.h&gt;
DECL|function|rose_header
r_static
r_int
id|rose_header
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
r_int
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
id|len
)paren
(brace
r_int
r_char
op_star
id|buff
op_assign
id|skb_push
c_func
(paren
id|skb
comma
id|ROSE_MIN_LEN
op_plus
l_int|2
)paren
suffix:semicolon
op_star
id|buff
op_increment
op_assign
id|ROSE_GFI
op_or
id|ROSE_Q_BIT
suffix:semicolon
op_star
id|buff
op_increment
op_assign
l_int|0x00
suffix:semicolon
op_star
id|buff
op_increment
op_assign
id|ROSE_DATA
suffix:semicolon
op_star
id|buff
op_increment
op_assign
l_int|0x7F
suffix:semicolon
op_star
id|buff
op_increment
op_assign
id|AX25_P_IP
suffix:semicolon
r_if
c_cond
(paren
id|daddr
op_ne
l_int|NULL
)paren
r_return
l_int|37
suffix:semicolon
r_return
op_minus
l_int|37
suffix:semicolon
)brace
DECL|function|rose_rebuild_header
r_static
r_int
id|rose_rebuild_header
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
r_struct
id|net_device_stats
op_star
id|stats
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_char
op_star
id|bp
op_assign
(paren
r_int
r_char
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skbn
suffix:semicolon
macro_line|#ifdef CONFIG_INET
r_if
c_cond
(paren
id|arp_find
c_func
(paren
id|bp
op_plus
l_int|7
comma
id|skb
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|skbn
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;sk
op_ne
l_int|NULL
)paren
id|skb_set_owner_w
c_func
(paren
id|skbn
comma
id|skb-&gt;sk
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rose_route_frame
c_func
(paren
id|skbn
comma
l_int|NULL
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skbn
)paren
suffix:semicolon
id|stats-&gt;tx_errors
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|stats-&gt;tx_packets
op_increment
suffix:semicolon
id|stats-&gt;tx_bytes
op_add_assign
id|skbn-&gt;len
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|rose_set_mac_address
r_static
r_int
id|rose_set_mac_address
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|addr
)paren
(brace
r_struct
id|sockaddr
op_star
id|sa
op_assign
id|addr
suffix:semicolon
id|rose_del_loopback_node
c_func
(paren
(paren
id|rose_address
op_star
)paren
id|dev-&gt;dev_addr
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
id|sa-&gt;sa_data
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
id|rose_add_loopback_node
c_func
(paren
(paren
id|rose_address
op_star
)paren
id|dev-&gt;dev_addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rose_open
r_static
r_int
id|rose_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|rose_add_loopback_node
c_func
(paren
(paren
id|rose_address
op_star
)paren
id|dev-&gt;dev_addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rose_close
r_static
r_int
id|rose_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|rose_del_loopback_node
c_func
(paren
(paren
id|rose_address
op_star
)paren
id|dev-&gt;dev_addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rose_xmit
r_static
r_int
id|rose_xmit
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
r_struct
id|net_device_stats
op_star
id|stats
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
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
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ROSE: rose_xmit - called when iface is down&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|stats-&gt;tx_errors
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rose_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|rose_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|rose_setup
r_void
id|rose_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;mtu
op_assign
id|ROSE_MAX_PACKET_SIZE
op_minus
l_int|2
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|rose_xmit
suffix:semicolon
id|dev-&gt;open
op_assign
id|rose_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|rose_close
suffix:semicolon
id|dev-&gt;hard_header
op_assign
id|rose_header
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
op_plus
id|ROSE_MIN_LEN
suffix:semicolon
id|dev-&gt;addr_len
op_assign
id|ROSE_ADDR_LEN
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_ROSE
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|rose_rebuild_header
suffix:semicolon
id|dev-&gt;set_mac_address
op_assign
id|rose_set_mac_address
suffix:semicolon
multiline_comment|/* New-style flags. */
id|dev-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|rose_get_stats
suffix:semicolon
)brace
eof
