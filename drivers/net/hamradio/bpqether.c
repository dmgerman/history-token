multiline_comment|/*&n; *&t;G8BPQ compatible &quot;AX.25 via ethernet&quot; driver release 004&n; *&n; *&t;This code REQUIRES 2.0.0 or higher/ NET3.029&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;This is a &quot;pseudo&quot; network driver to allow AX.25 over Ethernet&n; *&t;using G8BPQ encapsulation. It has been extracted from the protocol&n; *&t;implementation because&n; *&n; *&t;&t;- things got unreadable within the protocol stack&n; *&t;&t;- to cure the protocol stack from &quot;feature-ism&quot;&n; *&t;&t;- a protocol implementation shouldn&squot;t need to know on&n; *&t;&t;  which hardware it is running&n; *&t;&t;- user-level programs like the AX.25 utilities shouldn&squot;t&n; *&t;&t;  need to know about the hardware.&n; *&t;&t;- IP over ethernet encapsulated AX.25 was impossible&n; *&t;&t;- rxecho.c did not work&n; *&t;&t;- to have room for extensions&n; *&t;&t;- it just deserves to &quot;live&quot; as an own driver&n; *&n; *&t;This driver can use any ethernet destination address, and can be&n; *&t;limited to accept frames from one dedicated ethernet card only.&n; *&n; *&t;Note that the driver sets up the BPQ devices automagically on&n; *&t;startup or (if started before the &quot;insmod&quot; of an ethernet device)&n; *&t;on &quot;ifconfig up&quot;. It hopefully will remove the BPQ on &quot;rmmod&quot;ing&n; *&t;the ethernet device (in fact: as soon as another ethernet or bpq&n; *&t;device gets &quot;ifconfig&quot;ured).&n; *&n; *&t;I have heard that several people are thinking of experiments&n; *&t;with highspeed packet radio using existing ethernet cards.&n; *&t;Well, this driver is prepared for this purpose, just add&n; *&t;your tx key control and a txdelay / tailtime algorithm,&n; *&t;probably some buffering, and /voila/...&n; *&n; *&t;History&n; *&t;BPQ   001&t;Joerg(DL1BKE)&t;&t;Extracted BPQ code from AX.25&n; *&t;&t;&t;&t;&t;&t;protocol stack and added my own&n; *&t;&t;&t;&t;&t;&t;yet existing patches&n; *&t;BPQ   002&t;Joerg(DL1BKE)&t;&t;Scan network device list on&n; *&t;&t;&t;&t;&t;&t;startup.&n; *&t;BPQ   003&t;Joerg(DL1BKE)&t;&t;Ethernet destination address&n; *&t;&t;&t;&t;&t;&t;and accepted source address&n; *&t;&t;&t;&t;&t;&t;can be configured by an ioctl()&n; *&t;&t;&t;&t;&t;&t;call.&n; *&t;&t;&t;&t;&t;&t;Fixed to match Linux networking&n; *&t;&t;&t;&t;&t;&t;changes - 2.1.15.&n; *&t;BPQ   004&t;Joerg(DL1BKE)&t;&t;Fixed to not lock up on ifconfig.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;linux/bpqether.h&gt;
DECL|variable|__initdata
r_static
r_char
id|banner
(braket
)braket
id|__initdata
op_assign
id|KERN_INFO
l_string|&quot;AX.25: bpqether driver version 004&bslash;n&quot;
suffix:semicolon
DECL|variable|ax25_bcast
r_static
r_int
r_char
id|ax25_bcast
(braket
id|AX25_ADDR_LEN
)braket
op_assign
(brace
l_char|&squot;Q&squot;
op_lshift
l_int|1
comma
l_char|&squot;S&squot;
op_lshift
l_int|1
comma
l_char|&squot;T&squot;
op_lshift
l_int|1
comma
l_char|&squot; &squot;
op_lshift
l_int|1
comma
l_char|&squot; &squot;
op_lshift
l_int|1
comma
l_char|&squot; &squot;
op_lshift
l_int|1
comma
l_char|&squot;0&squot;
op_lshift
l_int|1
)brace
suffix:semicolon
DECL|variable|ax25_defaddr
r_static
r_int
r_char
id|ax25_defaddr
(braket
id|AX25_ADDR_LEN
)braket
op_assign
(brace
l_char|&squot;L&squot;
op_lshift
l_int|1
comma
l_char|&squot;I&squot;
op_lshift
l_int|1
comma
l_char|&squot;N&squot;
op_lshift
l_int|1
comma
l_char|&squot;U&squot;
op_lshift
l_int|1
comma
l_char|&squot;X&squot;
op_lshift
l_int|1
comma
l_char|&squot; &squot;
op_lshift
l_int|1
comma
l_char|&squot;1&squot;
op_lshift
l_int|1
)brace
suffix:semicolon
DECL|variable|bcast_addr
r_static
r_char
id|bcast_addr
(braket
l_int|6
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|bpq_eth_addr
r_static
r_char
id|bpq_eth_addr
(braket
l_int|6
)braket
suffix:semicolon
r_static
r_int
id|bpq_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
comma
r_struct
id|packet_type
op_star
)paren
suffix:semicolon
r_static
r_int
id|bpq_device_event
c_func
(paren
r_struct
id|notifier_block
op_star
comma
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_const
r_char
op_star
id|bpq_print_ethaddr
c_func
(paren
r_const
r_int
r_char
op_star
)paren
suffix:semicolon
DECL|variable|bpq_packet_type
r_static
r_struct
id|packet_type
id|bpq_packet_type
op_assign
(brace
dot
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_BPQ
)paren
comma
dot
id|func
op_assign
id|bpq_rcv
comma
dot
id|data
op_assign
id|PKT_CAN_SHARE_SKB
comma
)brace
suffix:semicolon
DECL|variable|bpq_dev_notifier
r_static
r_struct
id|notifier_block
id|bpq_dev_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|bpq_device_event
comma
)brace
suffix:semicolon
DECL|macro|MAXBPQDEV
mdefine_line|#define MAXBPQDEV 100
DECL|struct|bpqdev
r_struct
id|bpqdev
(brace
DECL|member|bpq_list
r_struct
id|list_head
id|bpq_list
suffix:semicolon
multiline_comment|/* list of bpq devices chain */
DECL|member|ethdev
r_struct
id|net_device
op_star
id|ethdev
suffix:semicolon
multiline_comment|/* link to ethernet device */
DECL|member|axdev
r_struct
id|net_device
op_star
id|axdev
suffix:semicolon
multiline_comment|/* bpq device (bpq#) */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* some statistics */
DECL|member|dest_addr
r_char
id|dest_addr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* ether destination address */
DECL|member|acpt_addr
r_char
id|acpt_addr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* accept ether frames from this address only */
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|bpq_devices
)paren
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------------------ */
multiline_comment|/*&n; *&t;Get the ethernet device for a BPQ device&n; */
DECL|function|bpq_get_ether_dev
r_static
r_inline
r_struct
id|net_device
op_star
id|bpq_get_ether_dev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|bpqdev
op_star
id|bpq
op_assign
(paren
r_struct
id|bpqdev
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_return
id|bpq
ques
c_cond
id|bpq-&gt;ethdev
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Get the BPQ device for the ethernet device&n; */
DECL|function|bpq_get_ax25_dev
r_static
r_inline
r_struct
id|net_device
op_star
id|bpq_get_ax25_dev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|bpqdev
op_star
id|bpq
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|bpq
comma
op_amp
id|bpq_devices
comma
id|bpq_list
)paren
(brace
r_if
c_cond
(paren
id|bpq-&gt;ethdev
op_eq
id|dev
)paren
r_return
id|bpq-&gt;axdev
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|dev_is_ethdev
r_static
r_inline
r_int
id|dev_is_ethdev
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
id|dev-&gt;type
op_eq
id|ARPHRD_ETHER
op_logical_and
id|strncmp
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;dummy&quot;
comma
l_int|5
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------------------ */
multiline_comment|/*&n; *&t;Receive an AX.25 frame via an ethernet interface.&n; */
DECL|function|bpq_rcv
r_static
r_int
id|bpq_rcv
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
id|ptype
)paren
(brace
r_int
id|len
suffix:semicolon
r_char
op_star
id|ptr
suffix:semicolon
r_struct
id|ethhdr
op_star
id|eth
suffix:semicolon
r_struct
id|bpqdev
op_star
id|bpq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|skb_share_check
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
r_return
id|NET_RX_DROP
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
id|ethhdr
)paren
)paren
)paren
r_goto
id|drop
suffix:semicolon
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
id|dev
op_assign
id|bpq_get_ax25_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
op_logical_or
op_logical_neg
id|netif_running
c_func
(paren
id|dev
)paren
)paren
r_goto
id|drop_unlock
suffix:semicolon
multiline_comment|/*&n;&t; * if we want to accept frames from just one ethernet device&n;&t; * we check the source address of the sender.&n;&t; */
id|bpq
op_assign
(paren
r_struct
id|bpqdev
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|eth
op_assign
(paren
r_struct
id|ethhdr
op_star
)paren
id|skb-&gt;mac.raw
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bpq-&gt;acpt_addr
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
op_logical_and
id|memcmp
c_func
(paren
id|eth-&gt;h_source
comma
id|bpq-&gt;acpt_addr
comma
id|ETH_ALEN
)paren
)paren
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;bpqether: wrong dest %s&bslash;n&quot;
comma
id|bpq_print_ethaddr
c_func
(paren
id|eth-&gt;h_source
)paren
)paren
suffix:semicolon
r_goto
id|drop_unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb_cow
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|ethhdr
)paren
)paren
)paren
r_goto
id|drop_unlock
suffix:semicolon
id|len
op_assign
id|skb-&gt;data
(braket
l_int|0
)braket
op_plus
id|skb-&gt;data
(braket
l_int|1
)braket
op_star
l_int|256
op_minus
l_int|5
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Remove the length bytes */
id|skb_trim
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* Set the length of the data */
id|bpq-&gt;stats.rx_packets
op_increment
suffix:semicolon
id|bpq-&gt;stats.rx_bytes
op_add_assign
id|len
suffix:semicolon
id|ptr
op_assign
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
op_star
id|ptr
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_AX25
)paren
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
id|unlock
suffix:colon
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|drop_unlock
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_goto
id|unlock
suffix:semicolon
id|drop
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * &t;Send an AX.25 frame via an ethernet interface&n; */
DECL|function|bpq_xmit
r_static
r_int
id|bpq_xmit
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
id|sk_buff
op_star
id|newskb
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_struct
id|bpqdev
op_star
id|bpq
suffix:semicolon
r_int
id|size
suffix:semicolon
multiline_comment|/*&n;&t; * Just to be *really* sure not to send anything if the interface&n;&t; * is down, the ethernet device may have gone.&n;&t; */
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
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
id|size
op_assign
id|skb-&gt;len
suffix:semicolon
multiline_comment|/*&n;&t; * The AX.25 code leaves enough room for the ethernet header, but&n;&t; * sendto() does not.&n;&t; */
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|AX25_BPQ_HEADER_LEN
)paren
(brace
multiline_comment|/* Ough! */
r_if
c_cond
(paren
(paren
id|newskb
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
id|AX25_BPQ_HEADER_LEN
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;bpqether: out of memory&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
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
id|newskb
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
id|skb
op_assign
id|newskb
suffix:semicolon
)brace
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_AX25
)paren
suffix:semicolon
id|ptr
op_assign
id|skb_push
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
(paren
id|size
op_plus
l_int|5
)paren
op_mod
l_int|256
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
(paren
id|size
op_plus
l_int|5
)paren
op_div
l_int|256
suffix:semicolon
id|bpq
op_assign
(paren
r_struct
id|bpqdev
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|bpq_get_ether_dev
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|bpq-&gt;stats.tx_dropped
op_increment
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|dev
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|skb
comma
id|dev
comma
id|ETH_P_BPQ
comma
id|bpq-&gt;dest_addr
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|bpq-&gt;stats.tx_packets
op_increment
suffix:semicolon
id|bpq-&gt;stats.tx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Statistics&n; */
DECL|function|bpq_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|bpq_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|bpqdev
op_star
id|bpq
op_assign
(paren
r_struct
id|bpqdev
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|bpq-&gt;stats
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Set AX.25 callsign&n; */
DECL|function|bpq_set_mac_address
r_static
r_int
id|bpq_set_mac_address
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
(paren
r_struct
id|sockaddr
op_star
)paren
id|addr
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&t;Ioctl commands&n; *&n; *&t;&t;SIOCSBPQETHOPT&t;&t;reserved for enhancements&n; *&t;&t;SIOCSBPQETHADDR&t;&t;set the destination and accepted&n; *&t;&t;&t;&t;&t;source ethernet address (broadcast&n; *&t;&t;&t;&t;&t;or multicast: accept all)&n; */
DECL|function|bpq_ioctl
r_static
r_int
id|bpq_ioctl
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
r_struct
id|bpq_ethaddr
op_star
id|ethaddr
op_assign
(paren
r_struct
id|bpq_ethaddr
op_star
)paren
id|ifr-&gt;ifr_data
suffix:semicolon
r_struct
id|bpqdev
op_star
id|bpq
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|bpq_req
id|req
suffix:semicolon
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
id|bpq
op_eq
l_int|NULL
)paren
multiline_comment|/* woops! */
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCSBPQETHOPT
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|req
comma
id|ifr-&gt;ifr_data
comma
r_sizeof
(paren
r_struct
id|bpq_req
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|req.cmd
)paren
(brace
r_case
id|SIOCGBPQETHPARAM
suffix:colon
r_case
id|SIOCSBPQETHPARAM
suffix:colon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SIOCSBPQETHADDR
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|bpq-&gt;dest_addr
comma
id|ethaddr-&gt;destination
comma
id|ETH_ALEN
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|bpq-&gt;acpt_addr
comma
id|ethaddr-&gt;accept
comma
id|ETH_ALEN
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * open/close a device&n; */
DECL|function|bpq_open
r_static
r_int
id|bpq_open
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bpq_close
r_static
r_int
id|bpq_close
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------------------ */
multiline_comment|/*&n; *&t;Proc filesystem&n; */
DECL|function|bpq_print_ethaddr
r_static
r_const
r_char
op_star
id|bpq_print_ethaddr
c_func
(paren
r_const
r_int
r_char
op_star
id|e
)paren
(brace
r_static
r_char
id|buf
(braket
l_int|18
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X&quot;
comma
id|e
(braket
l_int|0
)braket
comma
id|e
(braket
l_int|1
)braket
comma
id|e
(braket
l_int|2
)braket
comma
id|e
(braket
l_int|3
)braket
comma
id|e
(braket
l_int|4
)braket
comma
id|e
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
DECL|function|bpq_seq_start
r_static
r_void
op_star
id|bpq_seq_start
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_int
id|i
op_assign
l_int|1
suffix:semicolon
r_struct
id|bpqdev
op_star
id|bpqdev
suffix:semicolon
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pos
op_eq
l_int|0
)paren
r_return
id|SEQ_START_TOKEN
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|bpqdev
comma
op_amp
id|bpq_devices
comma
id|bpq_list
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
op_star
id|pos
)paren
r_return
id|bpqdev
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|bpq_seq_next
r_static
r_void
op_star
id|bpq_seq_next
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
op_increment
op_star
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
id|SEQ_START_TOKEN
)paren
id|p
op_assign
id|bpq_devices.next
suffix:semicolon
r_else
id|p
op_assign
(paren
(paren
r_struct
id|bpqdev
op_star
)paren
id|v
)paren
op_member_access_from_pointer
id|bpq_list.next
suffix:semicolon
r_return
(paren
id|p
op_eq
op_amp
id|bpq_devices
)paren
ques
c_cond
l_int|NULL
suffix:colon
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|bpqdev
comma
id|bpq_list
)paren
suffix:semicolon
)brace
DECL|function|bpq_seq_stop
r_static
r_void
id|bpq_seq_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|bpq_seq_show
r_static
r_int
id|bpq_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_if
c_cond
(paren
id|v
op_eq
id|SEQ_START_TOKEN
)paren
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;dev   ether      destination        accept from&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
r_const
r_struct
id|bpqdev
op_star
id|bpqdev
op_assign
id|v
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-5s %-10s %s  &quot;
comma
id|bpqdev-&gt;axdev-&gt;name
comma
id|bpqdev-&gt;ethdev-&gt;name
comma
id|bpq_print_ethaddr
c_func
(paren
id|bpqdev-&gt;dest_addr
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%s&bslash;n&quot;
comma
(paren
id|bpqdev-&gt;acpt_addr
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
ques
c_cond
l_string|&quot;*&quot;
suffix:colon
id|bpq_print_ethaddr
c_func
(paren
id|bpqdev-&gt;acpt_addr
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|bpq_seqops
r_static
r_struct
id|seq_operations
id|bpq_seqops
op_assign
(brace
dot
id|start
op_assign
id|bpq_seq_start
comma
dot
id|next
op_assign
id|bpq_seq_next
comma
dot
id|stop
op_assign
id|bpq_seq_stop
comma
dot
id|show
op_assign
id|bpq_seq_show
comma
)brace
suffix:semicolon
DECL|function|bpq_info_open
r_static
r_int
id|bpq_info_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|bpq_seqops
)paren
suffix:semicolon
)brace
DECL|variable|bpq_info_fops
r_static
r_struct
id|file_operations
id|bpq_info_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|bpq_info_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release
comma
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------------------ */
DECL|function|bpq_setup
r_static
r_void
id|bpq_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|dev-&gt;hard_start_xmit
op_assign
id|bpq_xmit
suffix:semicolon
id|dev-&gt;open
op_assign
id|bpq_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|bpq_close
suffix:semicolon
id|dev-&gt;set_mac_address
op_assign
id|bpq_set_mac_address
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|bpq_get_stats
suffix:semicolon
id|dev-&gt;do_ioctl
op_assign
id|bpq_ioctl
suffix:semicolon
id|dev-&gt;destructor
op_assign
id|free_netdev
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;broadcast
comma
id|ax25_bcast
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
id|ax25_defaddr
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|dev-&gt;flags
op_assign
l_int|0
suffix:semicolon
macro_line|#if defined(CONFIG_AX25) || defined(CONFIG_AX25_MODULE)
id|dev-&gt;hard_header
op_assign
id|ax25_encapsulate
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|ax25_rebuild_header
suffix:semicolon
macro_line|#endif
id|dev-&gt;type
op_assign
id|ARPHRD_AX25
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|AX25_MAX_HEADER_LEN
op_plus
id|AX25_BPQ_HEADER_LEN
suffix:semicolon
id|dev-&gt;mtu
op_assign
id|AX25_DEF_PACLEN
suffix:semicolon
id|dev-&gt;addr_len
op_assign
id|AX25_ADDR_LEN
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Setup a new device.&n; */
DECL|function|bpq_new_device
r_static
r_int
id|bpq_new_device
c_func
(paren
r_struct
id|net_device
op_star
id|edev
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|net_device
op_star
id|ndev
suffix:semicolon
r_struct
id|bpqdev
op_star
id|bpq
suffix:semicolon
id|ndev
op_assign
id|alloc_netdev
c_func
(paren
r_sizeof
(paren
r_struct
id|bpqdev
)paren
comma
l_string|&quot;bpq%d&quot;
comma
id|bpq_setup
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ndev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|bpq
op_assign
id|ndev-&gt;priv
suffix:semicolon
id|dev_hold
c_func
(paren
id|edev
)paren
suffix:semicolon
id|bpq-&gt;ethdev
op_assign
id|edev
suffix:semicolon
id|bpq-&gt;axdev
op_assign
id|ndev
suffix:semicolon
id|memcpy
c_func
(paren
id|bpq-&gt;dest_addr
comma
id|bcast_addr
comma
r_sizeof
(paren
id|bpq_eth_addr
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|bpq-&gt;acpt_addr
comma
id|bcast_addr
comma
r_sizeof
(paren
id|bpq_eth_addr
)paren
)paren
suffix:semicolon
id|err
op_assign
id|dev_alloc_name
c_func
(paren
id|ndev
comma
id|ndev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
id|err
op_assign
id|register_netdevice
c_func
(paren
id|ndev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error
suffix:semicolon
multiline_comment|/* List protected by RTNL */
id|list_add_rcu
c_func
(paren
op_amp
id|bpq-&gt;bpq_list
comma
op_amp
id|bpq_devices
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|dev_put
c_func
(paren
id|edev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ndev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bpq_free_device
r_static
r_void
id|bpq_free_device
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
)paren
(brace
r_struct
id|bpqdev
op_star
id|bpq
op_assign
id|ndev-&gt;priv
suffix:semicolon
id|dev_put
c_func
(paren
id|bpq-&gt;ethdev
)paren
suffix:semicolon
id|list_del_rcu
c_func
(paren
op_amp
id|bpq-&gt;bpq_list
)paren
suffix:semicolon
id|unregister_netdevice
c_func
(paren
id|ndev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Handle device status changes.&n; */
DECL|function|bpq_device_event
r_static
r_int
id|bpq_device_event
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
(paren
r_struct
id|net_device
op_star
)paren
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_is_ethdev
c_func
(paren
id|dev
)paren
)paren
r_return
id|NOTIFY_DONE
suffix:semicolon
id|rcu_read_lock
c_func
(paren
)paren
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
multiline_comment|/* new ethernet device -&gt; new BPQ interface */
r_if
c_cond
(paren
id|bpq_get_ax25_dev
c_func
(paren
id|dev
)paren
op_eq
l_int|NULL
)paren
id|bpq_new_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NETDEV_DOWN
suffix:colon
multiline_comment|/* ethernet device closed -&gt; close BPQ interface */
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|bpq_get_ax25_dev
c_func
(paren
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
id|dev_close
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NETDEV_UNREGISTER
suffix:colon
multiline_comment|/* ethernet device removed -&gt; free BPQ interface */
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|bpq_get_ax25_dev
c_func
(paren
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
id|bpq_free_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------------------ */
multiline_comment|/*&n; * Initialize driver. To be called from af_ax25 if not compiled as a&n; * module&n; */
DECL|function|bpq_init_driver
r_static
r_int
id|__init
id|bpq_init_driver
c_func
(paren
r_void
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|dev_add_pack
c_func
(paren
op_amp
id|bpq_packet_type
)paren
suffix:semicolon
id|register_netdevice_notifier
c_func
(paren
op_amp
id|bpq_dev_notifier
)paren
suffix:semicolon
id|printk
c_func
(paren
id|banner
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_if
c_cond
(paren
op_logical_neg
id|proc_net_fops_create
c_func
(paren
l_string|&quot;bpqether&quot;
comma
id|S_IRUGO
comma
op_amp
id|bpq_info_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bpq: cannot create /proc/net/bpqether entry.&bslash;n&quot;
)paren
suffix:semicolon
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|bpq_dev_notifier
)paren
suffix:semicolon
id|dev_remove_pack
c_func
(paren
op_amp
id|bpq_packet_type
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
macro_line|#endif  /* CONFIG_PROC_FS */
id|rtnl_lock
c_func
(paren
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
op_ne
l_int|NULL
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|dev_is_ethdev
c_func
(paren
id|dev
)paren
op_logical_and
id|bpq_new_device
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
l_string|&quot;bpq: cannot setup dev for &squot;%s&squot;&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
)brace
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bpq_cleanup_driver
r_static
r_void
id|__exit
id|bpq_cleanup_driver
c_func
(paren
r_void
)paren
(brace
r_struct
id|bpqdev
op_star
id|bpq
suffix:semicolon
id|dev_remove_pack
c_func
(paren
op_amp
id|bpq_packet_type
)paren
suffix:semicolon
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|bpq_dev_notifier
)paren
suffix:semicolon
id|proc_net_remove
c_func
(paren
l_string|&quot;bpqether&quot;
)paren
suffix:semicolon
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|bpq_devices
)paren
)paren
(brace
id|bpq
op_assign
id|list_entry
c_func
(paren
id|bpq_devices.next
comma
r_struct
id|bpqdev
comma
id|bpq_list
)paren
suffix:semicolon
id|bpq_free_device
c_func
(paren
id|bpq-&gt;axdev
)paren
suffix:semicolon
)brace
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Joerg Reuter DL1BKE &lt;jreuter@yaina.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Transmit and receive AX.25 packets over Ethernet&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|bpq_init_driver
id|module_init
c_func
(paren
id|bpq_init_driver
)paren
suffix:semicolon
DECL|variable|bpq_cleanup_driver
id|module_exit
c_func
(paren
id|bpq_cleanup_driver
)paren
suffix:semicolon
eof
