multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Pseudo-driver for the loopback interface.&n; *&n; * Version:&t;@(#)loopback.c&t;1.0.4b&t;08/16/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald Becker, &lt;becker@scyld.com&gt;&n; *&n; *&t;&t;Alan Cox&t;:&t;Fixed oddments for NET3.014&n; *&t;&t;Alan Cox&t;:&t;Rejig for NET3.029 snap #3&n; *&t;&t;Alan Cox&t;: &t;Fixed NET3.029 bugs and sped up&n; *&t;&t;Larry McVoy&t;:&t;Tiny tweak to double performance&n; *&t;&t;Alan Cox&t;:&t;Backed out LMV&squot;s tweak - the linux mm&n; *&t;&t;&t;&t;&t;can&squot;t take it...&n; *              Michael Griffith:       Don&squot;t bother computing the checksums&n; *                                      on packets received on the loopback&n; *                                      interface.&n; *&t;&t;Alexey Kuznetsov:&t;Potential hang under some extreme&n; *&t;&t;&t;&t;&t;cases removed.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;&t;/* For the statistics structure. */
macro_line|#include &lt;linux/if_arp.h&gt;&t;/* For ARPHRD_ETHER */
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
DECL|variable|loopback_stats
r_static
r_struct
id|net_device_stats
op_star
id|loopback_stats
suffix:semicolon
DECL|macro|LOOPBACK_OVERHEAD
mdefine_line|#define LOOPBACK_OVERHEAD (128 + MAX_HEADER + 16 + 16)
multiline_comment|/* KISS: just allocate small chunks and copy bits.&n; *&n; * So, in fact, this is documentation, explaining what we expect&n; * of largesending device modulo TCP checksum, which is ignored for loopback.&n; */
DECL|function|emulate_large_send_offload
r_static
r_void
id|emulate_large_send_offload
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|th
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
id|skb-&gt;nh.raw
op_plus
(paren
id|iph-&gt;ihl
op_star
l_int|4
)paren
)paren
suffix:semicolon
r_int
r_int
id|doffset
op_assign
(paren
id|iph-&gt;ihl
op_plus
id|th-&gt;doff
)paren
op_star
l_int|4
suffix:semicolon
r_int
r_int
id|mtu
op_assign
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|tso_size
op_plus
id|doffset
suffix:semicolon
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
id|u32
id|seq
op_assign
id|ntohl
c_func
(paren
id|th-&gt;seq
)paren
suffix:semicolon
id|u16
id|id
op_assign
id|ntohs
c_func
(paren
id|iph-&gt;id
)paren
suffix:semicolon
r_while
c_loop
(paren
id|offset
op_plus
id|doffset
OL
id|skb-&gt;len
)paren
(brace
r_int
r_int
id|frag_size
op_assign
id|min
c_func
(paren
id|mtu
comma
id|skb-&gt;len
op_minus
id|offset
)paren
op_minus
id|doffset
suffix:semicolon
r_struct
id|sk_buff
op_star
id|nskb
op_assign
id|alloc_skb
c_func
(paren
id|mtu
op_plus
l_int|32
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nskb
)paren
r_break
suffix:semicolon
id|skb_reserve
c_func
(paren
id|nskb
comma
l_int|32
)paren
suffix:semicolon
id|nskb-&gt;mac.raw
op_assign
id|nskb-&gt;data
op_minus
l_int|14
suffix:semicolon
id|nskb-&gt;nh.raw
op_assign
id|nskb-&gt;data
suffix:semicolon
id|iph
op_assign
id|nskb-&gt;nh.iph
suffix:semicolon
id|memcpy
c_func
(paren
id|nskb-&gt;data
comma
id|skb-&gt;nh.raw
comma
id|doffset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|doffset
op_plus
id|offset
comma
id|nskb-&gt;data
op_plus
id|doffset
comma
id|frag_size
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|skb_put
c_func
(paren
id|nskb
comma
id|doffset
op_plus
id|frag_size
)paren
suffix:semicolon
id|nskb-&gt;ip_summed
op_assign
id|CHECKSUM_UNNECESSARY
suffix:semicolon
id|nskb-&gt;dev
op_assign
id|skb-&gt;dev
suffix:semicolon
id|nskb-&gt;priority
op_assign
id|skb-&gt;priority
suffix:semicolon
id|nskb-&gt;protocol
op_assign
id|skb-&gt;protocol
suffix:semicolon
id|nskb-&gt;dst
op_assign
id|dst_clone
c_func
(paren
id|skb-&gt;dst
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|nskb-&gt;cb
comma
id|skb-&gt;cb
comma
r_sizeof
(paren
id|skb-&gt;cb
)paren
)paren
suffix:semicolon
id|nskb-&gt;pkt_type
op_assign
id|skb-&gt;pkt_type
suffix:semicolon
id|th
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
id|nskb-&gt;nh.raw
op_plus
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|frag_size
op_plus
id|doffset
)paren
suffix:semicolon
id|iph-&gt;id
op_assign
id|htons
c_func
(paren
id|id
)paren
suffix:semicolon
id|iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;check
op_assign
id|ip_fast_csum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|iph
comma
id|iph-&gt;ihl
)paren
suffix:semicolon
id|th-&gt;seq
op_assign
id|htonl
c_func
(paren
id|seq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_plus
id|doffset
op_plus
id|frag_size
OL
id|skb-&gt;len
)paren
id|th-&gt;fin
op_assign
id|th-&gt;psh
op_assign
l_int|0
suffix:semicolon
id|netif_rx
c_func
(paren
id|nskb
)paren
suffix:semicolon
id|offset
op_add_assign
id|frag_size
suffix:semicolon
id|seq
op_add_assign
id|frag_size
suffix:semicolon
id|id
op_increment
suffix:semicolon
)brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The higher levels take care of making this non-reentrant (it&squot;s&n; * called with bh&squot;s disabled).&n; */
DECL|function|loopback_xmit
r_static
r_int
id|loopback_xmit
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
id|skb_orphan
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
macro_line|#ifndef LOOPBACK_MUST_CHECKSUM
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_UNNECESSARY
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|tso_size
)paren
(brace
id|BUG_ON
c_func
(paren
id|skb-&gt;protocol
op_ne
id|htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|skb-&gt;nh.iph-&gt;protocol
op_ne
id|IPPROTO_TCP
)paren
suffix:semicolon
id|emulate_large_send_offload
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|loopback_stats
)paren
)paren
(brace
id|get_cpu_ptr
c_func
(paren
id|loopback_stats
)paren
op_member_access_from_pointer
id|rx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|get_cpu_ptr
c_func
(paren
id|loopback_stats
)paren
op_member_access_from_pointer
id|tx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|get_cpu_ptr
c_func
(paren
id|loopback_stats
)paren
op_member_access_from_pointer
id|rx_packets
op_increment
suffix:semicolon
id|get_cpu_ptr
c_func
(paren
id|loopback_stats
)paren
op_member_access_from_pointer
id|tx_packets
op_increment
suffix:semicolon
id|put_cpu_ptr
c_func
(paren
id|loopback_stats
)paren
suffix:semicolon
)brace
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
DECL|function|get_stats
r_static
r_struct
id|net_device_stats
op_star
id|get_stats
c_func
(paren
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
id|dev-&gt;priv
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stats
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|stats
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
r_if
c_cond
(paren
op_logical_neg
id|loopback_stats
)paren
(brace
r_return
id|stats
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|stats-&gt;rx_bytes
op_add_assign
id|per_cpu_ptr
c_func
(paren
id|loopback_stats
comma
id|i
)paren
op_member_access_from_pointer
id|rx_bytes
suffix:semicolon
id|stats-&gt;tx_bytes
op_add_assign
id|per_cpu_ptr
c_func
(paren
id|loopback_stats
comma
id|i
)paren
op_member_access_from_pointer
id|tx_bytes
suffix:semicolon
id|stats-&gt;rx_packets
op_add_assign
id|per_cpu_ptr
c_func
(paren
id|loopback_stats
comma
id|i
)paren
op_member_access_from_pointer
id|rx_packets
suffix:semicolon
id|stats-&gt;tx_packets
op_add_assign
id|per_cpu_ptr
c_func
(paren
id|loopback_stats
comma
id|i
)paren
op_member_access_from_pointer
id|tx_packets
suffix:semicolon
)brace
r_return
id|stats
suffix:semicolon
)brace
DECL|variable|loopback_dev
r_struct
id|net_device
id|loopback_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;lo&quot;
comma
dot
id|mtu
op_assign
(paren
l_int|16
op_star
l_int|1024
)paren
op_plus
l_int|20
op_plus
l_int|20
op_plus
l_int|12
comma
dot
id|hard_start_xmit
op_assign
id|loopback_xmit
comma
dot
id|hard_header
op_assign
id|eth_header
comma
dot
id|hard_header_cache
op_assign
id|eth_header_cache
comma
dot
id|header_cache_update
op_assign
id|eth_header_cache_update
comma
dot
id|hard_header_len
op_assign
id|ETH_HLEN
comma
multiline_comment|/* 14&t;*/
dot
id|addr_len
op_assign
id|ETH_ALEN
comma
multiline_comment|/* 6&t;*/
dot
id|tx_queue_len
op_assign
l_int|0
comma
dot
id|type
op_assign
id|ARPHRD_LOOPBACK
comma
multiline_comment|/* 0x0001*/
dot
id|rebuild_header
op_assign
id|eth_rebuild_header
comma
dot
id|flags
op_assign
id|IFF_LOOPBACK
comma
dot
id|features
op_assign
id|NETIF_F_SG
op_or
id|NETIF_F_FRAGLIST
op_or
id|NETIF_F_NO_CSUM
op_or
id|NETIF_F_HIGHDMA
op_or
id|NETIF_F_LLTX
comma
)brace
suffix:semicolon
multiline_comment|/* Setup and register the of the LOOPBACK device. */
DECL|function|loopback_init
r_int
id|__init
id|loopback_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|net_device_stats
op_star
id|stats
suffix:semicolon
multiline_comment|/* Can survive without statistics */
id|stats
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
suffix:semicolon
r_if
c_cond
(paren
id|stats
)paren
(brace
id|memset
c_func
(paren
id|stats
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
id|loopback_dev.priv
op_assign
id|stats
suffix:semicolon
id|loopback_dev.get_stats
op_assign
op_amp
id|get_stats
suffix:semicolon
)brace
id|loopback_stats
op_assign
id|alloc_percpu
c_func
(paren
r_struct
id|net_device_stats
)paren
suffix:semicolon
r_return
id|register_netdev
c_func
(paren
op_amp
id|loopback_dev
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|loopback_dev
id|EXPORT_SYMBOL
c_func
(paren
id|loopback_dev
)paren
suffix:semicolon
eof
