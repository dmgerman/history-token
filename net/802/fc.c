multiline_comment|/*&n; * NET3:&t;Fibre Channel device handling subroutines&n; * &n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;&t;Vineet Abraham &lt;vma@iol.unh.edu&gt;&n; *&t;&t;v 1.0 03/22/99&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/fcdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/arp.h&gt;
multiline_comment|/*&n; *&t;Put the headers on a Fibre Channel packet. &n; */
DECL|function|fc_header
r_int
id|fc_header
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
r_struct
id|fch_hdr
op_star
id|fch
suffix:semicolon
r_int
id|hdr_len
suffix:semicolon
multiline_comment|/* &n;&t; * Add the 802.2 SNAP header if IP as the IPv4 code calls  &n;&t; * dev-&gt;hard_header directly.&n;&t; */
r_if
c_cond
(paren
id|type
op_eq
id|ETH_P_IP
op_logical_or
id|type
op_eq
id|ETH_P_ARP
)paren
(brace
r_struct
id|fcllc
op_star
id|fcllc
op_assign
(paren
r_struct
id|fcllc
op_star
)paren
(paren
id|fch
op_plus
l_int|1
)paren
suffix:semicolon
id|hdr_len
op_assign
r_sizeof
(paren
r_struct
id|fch_hdr
)paren
op_plus
r_sizeof
(paren
r_struct
id|fcllc
)paren
suffix:semicolon
id|fch
op_assign
(paren
r_struct
id|fch_hdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|hdr_len
)paren
suffix:semicolon
id|fcllc
op_assign
(paren
r_struct
id|fcllc
op_star
)paren
(paren
id|fch
op_plus
l_int|1
)paren
suffix:semicolon
id|fcllc-&gt;dsap
op_assign
id|fcllc-&gt;ssap
op_assign
id|EXTENDED_SAP
suffix:semicolon
id|fcllc-&gt;llc
op_assign
id|UI_CMD
suffix:semicolon
id|fcllc-&gt;protid
(braket
l_int|0
)braket
op_assign
id|fcllc-&gt;protid
(braket
l_int|1
)braket
op_assign
id|fcllc-&gt;protid
(braket
l_int|2
)braket
op_assign
l_int|0x00
suffix:semicolon
id|fcllc-&gt;ethertype
op_assign
id|htons
c_func
(paren
id|type
)paren
suffix:semicolon
)brace
r_else
(brace
id|hdr_len
op_assign
r_sizeof
(paren
r_struct
id|fch_hdr
)paren
suffix:semicolon
id|fch
op_assign
(paren
r_struct
id|fch_hdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|hdr_len
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|saddr
)paren
(brace
id|memcpy
c_func
(paren
id|fch-&gt;saddr
comma
id|saddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
id|fch-&gt;saddr
comma
id|dev-&gt;dev_addr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|daddr
)paren
(brace
id|memcpy
c_func
(paren
id|fch-&gt;daddr
comma
id|daddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_return
id|hdr_len
suffix:semicolon
)brace
r_return
op_minus
id|hdr_len
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;A neighbour discovery of some species (eg arp) has completed. We&n; *&t;can now send the packet.&n; */
DECL|function|fc_rebuild_header
r_int
id|fc_rebuild_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|fch_hdr
op_star
id|fch
op_assign
(paren
r_struct
id|fch_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|fcllc
op_star
id|fcllc
op_assign
(paren
r_struct
id|fcllc
op_star
)paren
(paren
id|skb-&gt;data
op_plus
r_sizeof
(paren
r_struct
id|fch_hdr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fcllc-&gt;ethertype
op_ne
id|htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fc_rebuild_header: Don&squot;t know how to resolve type %04X addresses ?&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|htons
c_func
(paren
id|fcllc-&gt;ethertype
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_INET
r_return
id|arp_find
c_func
(paren
id|fch-&gt;daddr
comma
id|skb
)paren
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
r_int
r_int
DECL|function|fc_type_trans
id|fc_type_trans
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
id|fch_hdr
op_star
id|fch
op_assign
(paren
r_struct
id|fch_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|fcllc
op_star
id|fcllc
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|fcllc
op_assign
(paren
r_struct
id|fcllc
op_star
)paren
(paren
id|skb-&gt;data
op_plus
r_sizeof
(paren
r_struct
id|fch_hdr
)paren
op_plus
l_int|2
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|fch_hdr
)paren
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|fch-&gt;daddr
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|fch-&gt;daddr
comma
id|dev-&gt;broadcast
comma
id|FC_ALEN
)paren
)paren
id|skb-&gt;pkt_type
op_assign
id|PACKET_BROADCAST
suffix:semicolon
r_else
id|skb-&gt;pkt_type
op_assign
id|PACKET_MULTICAST
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_PROMISC
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|fch-&gt;daddr
comma
id|dev-&gt;dev_addr
comma
id|FC_ALEN
)paren
)paren
id|skb-&gt;pkt_type
op_assign
id|PACKET_OTHERHOST
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Strip the SNAP header from ARP packets since we don&squot;t pass&n;&t; * them through to the 802.2/SNAP layers.&n;&t; */
r_if
c_cond
(paren
id|fcllc-&gt;dsap
op_eq
id|EXTENDED_SAP
op_logical_and
(paren
id|fcllc-&gt;ethertype
op_eq
id|ntohs
c_func
(paren
id|ETH_P_IP
)paren
op_logical_or
id|fcllc-&gt;ethertype
op_eq
id|ntohs
c_func
(paren
id|ETH_P_ARP
)paren
)paren
)paren
(brace
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|fcllc
)paren
)paren
suffix:semicolon
r_return
id|fcllc-&gt;ethertype
suffix:semicolon
)brace
r_return
id|ntohs
c_func
(paren
id|ETH_P_802_2
)paren
suffix:semicolon
)brace
eof
