multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * Copyright Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
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
macro_line|#include &lt;linux/if_ether.h&gt;&t;/* For the statistics structure. */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;net/netrom.h&gt;
macro_line|#ifdef CONFIG_INET
multiline_comment|/*&n; *&t;Only allow IP over NET/ROM frames through if the netrom device is up.&n; */
DECL|function|nr_rx_ip
r_int
id|nr_rx_ip
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
(paren
r_struct
id|net_device_stats
op_star
)paren
id|dev-&gt;priv
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
id|stats-&gt;rx_errors
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|stats-&gt;rx_packets
op_increment
suffix:semicolon
id|stats-&gt;rx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:semicolon
multiline_comment|/* Spoof incoming device */
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|ip_rcv
c_func
(paren
id|skb
comma
id|skb-&gt;dev
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|nr_rebuild_header
r_static
r_int
id|nr_rebuild_header
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
(paren
r_struct
id|net_device_stats
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skbn
suffix:semicolon
r_int
r_char
op_star
id|bp
op_assign
id|skb-&gt;data
suffix:semicolon
r_int
id|len
suffix:semicolon
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
id|bp
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_CBIT
suffix:semicolon
id|bp
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_EBIT
suffix:semicolon
id|bp
(braket
l_int|6
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
id|bp
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|bp
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_CBIT
suffix:semicolon
id|bp
(braket
l_int|6
)braket
op_or_assign
id|AX25_EBIT
suffix:semicolon
id|bp
(braket
l_int|6
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
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
id|len
op_assign
id|skbn-&gt;len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_route_frame
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
)brace
id|stats-&gt;tx_packets
op_increment
suffix:semicolon
id|stats-&gt;tx_bytes
op_add_assign
id|len
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#else
DECL|function|nr_rebuild_header
r_static
r_int
id|nr_rebuild_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
DECL|function|nr_header
r_static
r_int
id|nr_header
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
id|NR_NETWORK_LEN
op_plus
id|NR_TRANSPORT_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buff
comma
(paren
id|saddr
op_ne
l_int|NULL
)paren
ques
c_cond
id|saddr
suffix:colon
id|dev-&gt;dev_addr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
id|buff
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_CBIT
suffix:semicolon
id|buff
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_EBIT
suffix:semicolon
id|buff
(braket
l_int|6
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
id|buff
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
r_if
c_cond
(paren
id|daddr
op_ne
l_int|NULL
)paren
id|memcpy
c_func
(paren
id|buff
comma
id|daddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
id|buff
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_CBIT
suffix:semicolon
id|buff
(braket
l_int|6
)braket
op_or_assign
id|AX25_EBIT
suffix:semicolon
id|buff
(braket
l_int|6
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
id|buff
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
op_star
id|buff
op_increment
op_assign
id|sysctl_netrom_network_ttl_initialiser
suffix:semicolon
op_star
id|buff
op_increment
op_assign
id|NR_PROTO_IP
suffix:semicolon
op_star
id|buff
op_increment
op_assign
id|NR_PROTO_IP
suffix:semicolon
op_star
id|buff
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|buff
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|buff
op_increment
op_assign
id|NR_PROTOEXT
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
DECL|function|nr_set_mac_address
r_static
r_int
id|nr_set_mac_address
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
id|ax25_listen_release
c_func
(paren
(paren
id|ax25_address
op_star
)paren
id|dev-&gt;dev_addr
comma
l_int|NULL
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
id|ax25_listen_register
c_func
(paren
(paren
id|ax25_address
op_star
)paren
id|dev-&gt;dev_addr
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nr_open
r_static
r_int
id|nr_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ax25_listen_register
c_func
(paren
(paren
id|ax25_address
op_star
)paren
id|dev-&gt;dev_addr
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nr_close
r_static
r_int
id|nr_close
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
id|ax25_listen_release
c_func
(paren
(paren
id|ax25_address
op_star
)paren
id|dev-&gt;dev_addr
comma
l_int|NULL
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nr_xmit
r_static
r_int
id|nr_xmit
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
(paren
r_struct
id|net_device_stats
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
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
DECL|function|nr_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|nr_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
(paren
r_struct
id|net_device_stats
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
)brace
DECL|function|nr_init
r_int
id|nr_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|dev-&gt;mtu
op_assign
id|NR_MAX_PACKET_SIZE
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|nr_xmit
suffix:semicolon
id|dev-&gt;open
op_assign
id|nr_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|nr_close
suffix:semicolon
id|dev-&gt;hard_header
op_assign
id|nr_header
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|AX25_BPQ_HEADER_LEN
op_plus
id|AX25_MAX_HEADER_LEN
op_plus
id|NR_NETWORK_LEN
op_plus
id|NR_TRANSPORT_LEN
suffix:semicolon
id|dev-&gt;addr_len
op_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_NETROM
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|nr_rebuild_header
suffix:semicolon
id|dev-&gt;set_mac_address
op_assign
id|nr_set_mac_address
suffix:semicolon
multiline_comment|/* New-style flags. */
id|dev-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|net_device_stats
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|net_device_stats
)paren
)paren
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|nr_get_stats
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
eof
