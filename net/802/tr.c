multiline_comment|/*&n; * NET3:&t;Token ring device handling subroutines&n; * &n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Fixes:       3 Feb 97 Paul Norton &lt;pnorton@cts.com&gt; Minor routing fixes.&n; *              Added rif table to /proc/net/tr_rif and rif timeout to&n; *              /proc/sys/net/token-ring/rif_timeout.&n; *              22 Jun 98 Paul Norton &lt;p.norton@computer.org&gt; Rearranged&n; *              tr_header and tr_type_trans to handle passing IPX SNAP and&n; *              802.2 through the correct layers. Eliminated tr_reformat.&n; *        &n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/arp.h&gt;
r_static
r_void
id|tr_add_rif_info
c_func
(paren
r_struct
id|trh_hdr
op_star
id|trh
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|rif_check_expire
c_func
(paren
r_int
r_int
id|dummy
)paren
suffix:semicolon
DECL|macro|TR_SR_DEBUG
mdefine_line|#define TR_SR_DEBUG 0
multiline_comment|/*&n; *&t;Each RIF entry we learn is kept this way&n; */
DECL|struct|rif_cache_s
r_struct
id|rif_cache_s
(brace
DECL|member|addr
r_int
r_char
id|addr
(braket
id|TR_ALEN
)braket
suffix:semicolon
DECL|member|iface
r_int
id|iface
suffix:semicolon
DECL|member|rcf
id|__u16
id|rcf
suffix:semicolon
DECL|member|rseg
id|__u16
id|rseg
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|next
r_struct
id|rif_cache_s
op_star
id|next
suffix:semicolon
DECL|member|last_used
r_int
r_int
id|last_used
suffix:semicolon
DECL|member|local_ring
r_int
r_char
id|local_ring
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RIF_TABLE_SIZE
mdefine_line|#define RIF_TABLE_SIZE 32
multiline_comment|/*&n; *&t;We hash the RIF cache 32 ways. We do after all have to look it&n; *&t;up a lot.&n; */
DECL|variable|rif_table
r_static
r_struct
id|rif_cache_s
op_star
id|rif_table
(braket
id|RIF_TABLE_SIZE
)braket
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|rif_lock
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Garbage disposal timer.&n; */
DECL|variable|rif_timer
r_static
r_struct
id|timer_list
id|rif_timer
suffix:semicolon
DECL|variable|sysctl_tr_rif_timeout
r_int
id|sysctl_tr_rif_timeout
op_assign
l_int|60
op_star
l_int|10
op_star
id|HZ
suffix:semicolon
DECL|function|rif_hash
r_static
r_inline
r_int
r_int
id|rif_hash
c_func
(paren
r_const
r_int
r_char
op_star
id|addr
)paren
(brace
r_int
r_int
id|x
suffix:semicolon
id|x
op_assign
id|addr
(braket
l_int|0
)braket
suffix:semicolon
id|x
op_assign
(paren
id|x
op_lshift
l_int|2
)paren
op_xor
id|addr
(braket
l_int|1
)braket
suffix:semicolon
id|x
op_assign
(paren
id|x
op_lshift
l_int|2
)paren
op_xor
id|addr
(braket
l_int|2
)braket
suffix:semicolon
id|x
op_assign
(paren
id|x
op_lshift
l_int|2
)paren
op_xor
id|addr
(braket
l_int|3
)braket
suffix:semicolon
id|x
op_assign
(paren
id|x
op_lshift
l_int|2
)paren
op_xor
id|addr
(braket
l_int|4
)braket
suffix:semicolon
id|x
op_assign
(paren
id|x
op_lshift
l_int|2
)paren
op_xor
id|addr
(braket
l_int|5
)braket
suffix:semicolon
id|x
op_xor_assign
id|x
op_rshift
l_int|8
suffix:semicolon
r_return
id|x
op_amp
(paren
id|RIF_TABLE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Put the headers on a token ring packet. Token ring source routing&n; *&t;makes this a little more exciting than on ethernet.&n; */
DECL|function|tr_header
r_static
r_int
id|tr_header
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
id|trh_hdr
op_star
id|trh
suffix:semicolon
r_int
id|hdr_len
suffix:semicolon
multiline_comment|/* &n;&t; * Add the 802.2 SNAP header if IP as the IPv4/IPv6 code calls  &n;&t; * dev-&gt;hard_header directly.&n;&t; */
r_if
c_cond
(paren
id|type
op_eq
id|ETH_P_IP
op_logical_or
id|type
op_eq
id|ETH_P_IPV6
op_logical_or
id|type
op_eq
id|ETH_P_ARP
)paren
(brace
r_struct
id|trllc
op_star
id|trllc
suffix:semicolon
id|hdr_len
op_assign
r_sizeof
(paren
r_struct
id|trh_hdr
)paren
op_plus
r_sizeof
(paren
r_struct
id|trllc
)paren
suffix:semicolon
id|trh
op_assign
(paren
r_struct
id|trh_hdr
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
id|trllc
op_assign
(paren
r_struct
id|trllc
op_star
)paren
(paren
id|trh
op_plus
l_int|1
)paren
suffix:semicolon
id|trllc-&gt;dsap
op_assign
id|trllc-&gt;ssap
op_assign
id|EXTENDED_SAP
suffix:semicolon
id|trllc-&gt;llc
op_assign
id|UI_CMD
suffix:semicolon
id|trllc-&gt;protid
(braket
l_int|0
)braket
op_assign
id|trllc-&gt;protid
(braket
l_int|1
)braket
op_assign
id|trllc-&gt;protid
(braket
l_int|2
)braket
op_assign
l_int|0x00
suffix:semicolon
id|trllc-&gt;ethertype
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
id|trh_hdr
)paren
suffix:semicolon
id|trh
op_assign
(paren
r_struct
id|trh_hdr
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
id|trh-&gt;ac
op_assign
id|AC
suffix:semicolon
id|trh-&gt;fc
op_assign
id|LLC_FRAME
suffix:semicolon
r_if
c_cond
(paren
id|saddr
)paren
(brace
id|memcpy
c_func
(paren
id|trh-&gt;saddr
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
id|trh-&gt;saddr
comma
id|dev-&gt;dev_addr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Build the destination and then source route the frame&n;&t; */
r_if
c_cond
(paren
id|daddr
)paren
(brace
id|memcpy
c_func
(paren
id|trh-&gt;daddr
comma
id|daddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
id|tr_source_route
c_func
(paren
id|skb
comma
id|trh
comma
id|dev
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
DECL|function|tr_rebuild_header
r_static
r_int
id|tr_rebuild_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|trh_hdr
op_star
id|trh
op_assign
(paren
r_struct
id|trh_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|trllc
op_star
id|trllc
op_assign
(paren
r_struct
id|trllc
op_star
)paren
(paren
id|skb-&gt;data
op_plus
r_sizeof
(paren
r_struct
id|trh_hdr
)paren
)paren
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|skb-&gt;dev
suffix:semicolon
multiline_comment|/*&n;&t; *&t;FIXME: We don&squot;t yet support IPv6 over token rings&n;&t; */
r_if
c_cond
(paren
id|trllc-&gt;ethertype
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
l_string|&quot;tr_rebuild_header: Don&squot;t know how to resolve type %04X addresses ?&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|htons
c_func
(paren
id|trllc-&gt;ethertype
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_INET
r_if
c_cond
(paren
id|arp_find
c_func
(paren
id|trh-&gt;daddr
comma
id|skb
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
macro_line|#endif&t;
(brace
id|tr_source_route
c_func
(paren
id|skb
comma
id|trh
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Some of this is a bit hackish. We intercept RIF information&n; *&t;used for source routing. We also grab IP directly and don&squot;t feed&n; *&t;it via SNAP.&n; */
DECL|function|tr_type_trans
r_int
r_int
id|tr_type_trans
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
id|trh_hdr
op_star
id|trh
op_assign
(paren
r_struct
id|trh_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|trllc
op_star
id|trllc
suffix:semicolon
r_int
id|riflen
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_amp
id|TR_RII
)paren
(brace
id|riflen
op_assign
(paren
id|ntohs
c_func
(paren
id|trh-&gt;rcf
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_rshift
l_int|8
suffix:semicolon
)brace
id|trllc
op_assign
(paren
r_struct
id|trllc
op_star
)paren
(paren
id|skb-&gt;data
op_plus
r_sizeof
(paren
r_struct
id|trh_hdr
)paren
op_minus
id|TR_MAXRIFLEN
op_plus
id|riflen
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
id|trh_hdr
)paren
op_minus
id|TR_MAXRIFLEN
op_plus
id|riflen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|trh-&gt;daddr
op_amp
l_int|0x80
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|trh-&gt;daddr
comma
id|dev-&gt;broadcast
comma
id|TR_ALEN
)paren
)paren
(brace
id|skb-&gt;pkt_type
op_assign
id|PACKET_BROADCAST
suffix:semicolon
)brace
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
(paren
id|trh-&gt;daddr
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
op_logical_and
(paren
id|trh-&gt;daddr
(braket
l_int|1
)braket
op_amp
l_int|0x00
)paren
op_logical_and
(paren
id|trh-&gt;daddr
(braket
l_int|2
)braket
op_amp
l_int|0x5E
)paren
)paren
(brace
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
id|trh-&gt;daddr
comma
id|dev-&gt;dev_addr
comma
id|TR_ALEN
)paren
)paren
(brace
id|skb-&gt;pkt_type
op_assign
id|PACKET_OTHERHOST
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|skb-&gt;pkt_type
op_ne
id|PACKET_BROADCAST
)paren
op_logical_and
(paren
id|skb-&gt;pkt_type
op_ne
id|PACKET_MULTICAST
)paren
)paren
id|tr_add_rif_info
c_func
(paren
id|trh
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Strip the SNAP header from ARP packets since we don&squot;t &n;&t; * pass them through to the 802.2/SNAP layers.&n;&t; */
r_if
c_cond
(paren
id|trllc-&gt;dsap
op_eq
id|EXTENDED_SAP
op_logical_and
(paren
id|trllc-&gt;ethertype
op_eq
id|ntohs
c_func
(paren
id|ETH_P_IP
)paren
op_logical_or
id|trllc-&gt;ethertype
op_eq
id|ntohs
c_func
(paren
id|ETH_P_IPV6
)paren
op_logical_or
id|trllc-&gt;ethertype
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
id|trllc
)paren
)paren
suffix:semicolon
r_return
id|trllc-&gt;ethertype
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
multiline_comment|/*&n; *&t;We try to do source routing... &n; */
DECL|function|tr_source_route
r_void
id|tr_source_route
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|trh_hdr
op_star
id|trh
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|slack
suffix:semicolon
r_int
r_int
id|hash
suffix:semicolon
r_struct
id|rif_cache_s
op_star
id|entry
suffix:semicolon
r_int
r_char
op_star
id|olddata
suffix:semicolon
r_static
r_const
r_int
r_char
id|mcast_func_addr
(braket
)braket
op_assign
(brace
l_int|0xC0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|rif_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Broadcasts are single route as stated in RFC 1042 &n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|memcmp
c_func
(paren
op_amp
(paren
id|trh-&gt;daddr
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|dev-&gt;broadcast
(braket
l_int|0
)braket
)paren
comma
id|TR_ALEN
)paren
)paren
op_logical_or
(paren
op_logical_neg
id|memcmp
c_func
(paren
op_amp
(paren
id|trh-&gt;daddr
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|mcast_func_addr
(braket
l_int|0
)braket
)paren
comma
id|TR_ALEN
)paren
)paren
)paren
(brace
id|trh-&gt;rcf
op_assign
id|htons
c_func
(paren
(paren
(paren
(paren
r_sizeof
(paren
id|trh-&gt;rcf
)paren
)paren
op_lshift
l_int|8
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_or
id|TR_RCF_FRAME2K
op_or
id|TR_RCF_LIMITED_BROADCAST
)paren
suffix:semicolon
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_or_assign
id|TR_RII
suffix:semicolon
)brace
r_else
(brace
id|hash
op_assign
id|rif_hash
c_func
(paren
id|trh-&gt;daddr
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Walk the hash table and look for an entry&n;&t;&t; */
r_for
c_loop
(paren
id|entry
op_assign
id|rif_table
(braket
id|hash
)braket
suffix:semicolon
id|entry
op_logical_and
id|memcmp
c_func
(paren
op_amp
(paren
id|entry-&gt;addr
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|trh-&gt;daddr
(braket
l_int|0
)braket
)paren
comma
id|TR_ALEN
)paren
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;If we found an entry we can route the frame.&n;&t;&t; */
r_if
c_cond
(paren
id|entry
)paren
(brace
macro_line|#if TR_SR_DEBUG
id|printk
c_func
(paren
l_string|&quot;source routing for %02X:%02X:%02X:%02X:%02X:%02X&bslash;n&quot;
comma
id|trh-&gt;daddr
(braket
l_int|0
)braket
comma
id|trh-&gt;daddr
(braket
l_int|1
)braket
comma
id|trh-&gt;daddr
(braket
l_int|2
)braket
comma
id|trh-&gt;daddr
(braket
l_int|3
)braket
comma
id|trh-&gt;daddr
(braket
l_int|4
)braket
comma
id|trh-&gt;daddr
(braket
l_int|5
)braket
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;local_ring
op_logical_and
(paren
id|ntohs
c_func
(paren
id|entry-&gt;rcf
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_rshift
l_int|8
)paren
(brace
id|trh-&gt;rcf
op_assign
id|entry-&gt;rcf
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|trh-&gt;rseg
(braket
l_int|0
)braket
comma
op_amp
id|entry-&gt;rseg
(braket
l_int|0
)braket
comma
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
id|trh-&gt;rcf
op_xor_assign
id|htons
c_func
(paren
id|TR_RCF_DIR_BIT
)paren
suffix:semicolon
id|trh-&gt;rcf
op_and_assign
id|htons
c_func
(paren
l_int|0x1fff
)paren
suffix:semicolon
multiline_comment|/* Issam Chehab &lt;ichehab@madge1.demon.co.uk&gt; */
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_or_assign
id|TR_RII
suffix:semicolon
macro_line|#if TR_SR_DEBUG
id|printk
c_func
(paren
l_string|&quot;entry found with rcf %04x&bslash;n&quot;
comma
id|entry-&gt;rcf
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;entry found but without rcf length, local=%02x&bslash;n&quot;
comma
id|entry-&gt;local_ring
)paren
suffix:semicolon
macro_line|#endif
)brace
id|entry-&gt;last_used
op_assign
id|jiffies
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;Without the information we simply have to shout&n;&t;&t;&t; *&t;on the wire. The replies should rapidly clean this&n;&t;&t;&t; *&t;situation up.&n;&t;&t;&t; */
id|trh-&gt;rcf
op_assign
id|htons
c_func
(paren
(paren
(paren
(paren
r_sizeof
(paren
id|trh-&gt;rcf
)paren
)paren
op_lshift
l_int|8
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_or
id|TR_RCF_FRAME2K
op_or
id|TR_RCF_LIMITED_BROADCAST
)paren
suffix:semicolon
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_or_assign
id|TR_RII
suffix:semicolon
macro_line|#if TR_SR_DEBUG
id|printk
c_func
(paren
l_string|&quot;no entry in rif table found - broadcasting frame&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
multiline_comment|/* Compress the RIF here so we don&squot;t have to do it in the driver(s) */
r_if
c_cond
(paren
op_logical_neg
(paren
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_amp
l_int|0x80
)paren
)paren
id|slack
op_assign
l_int|18
suffix:semicolon
r_else
id|slack
op_assign
l_int|18
op_minus
(paren
(paren
id|ntohs
c_func
(paren
id|trh-&gt;rcf
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|olddata
op_assign
id|skb-&gt;data
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|rif_lock
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|slack
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|skb-&gt;data
comma
id|olddata
comma
r_sizeof
(paren
r_struct
id|trh_hdr
)paren
op_minus
id|slack
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;We have learned some new RIF information for our source&n; *&t;routing.&n; */
DECL|function|tr_add_rif_info
r_static
r_void
id|tr_add_rif_info
c_func
(paren
r_struct
id|trh_hdr
op_star
id|trh
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|hash
comma
id|rii_p
op_assign
l_int|0
suffix:semicolon
r_struct
id|rif_cache_s
op_star
id|entry
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|rif_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Firstly see if the entry exists&n;&t; */
r_if
c_cond
(paren
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_amp
id|TR_RII
)paren
(brace
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_and_assign
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|ntohs
c_func
(paren
id|trh-&gt;rcf
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_rshift
l_int|8
)paren
OG
l_int|2
)paren
(brace
id|rii_p
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|hash
op_assign
id|rif_hash
c_func
(paren
id|trh-&gt;saddr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|rif_table
(braket
id|hash
)braket
suffix:semicolon
id|entry
op_logical_and
id|memcmp
c_func
(paren
op_amp
(paren
id|entry-&gt;addr
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|trh-&gt;saddr
(braket
l_int|0
)braket
)paren
comma
id|TR_ALEN
)paren
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
(brace
macro_line|#if TR_SR_DEBUG
id|printk
c_func
(paren
l_string|&quot;adding rif_entry: addr:%02X:%02X:%02X:%02X:%02X:%02X rcf:%04X&bslash;n&quot;
comma
id|trh-&gt;saddr
(braket
l_int|0
)braket
comma
id|trh-&gt;saddr
(braket
l_int|1
)braket
comma
id|trh-&gt;saddr
(braket
l_int|2
)braket
comma
id|trh-&gt;saddr
(braket
l_int|3
)braket
comma
id|trh-&gt;saddr
(braket
l_int|4
)braket
comma
id|trh-&gt;saddr
(braket
l_int|5
)braket
comma
id|ntohs
c_func
(paren
id|trh-&gt;rcf
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t; *&t;Allocate our new entry. A failure to allocate loses&n;&t;&t; *&t;use the information. This is harmless.&n;&t;&t; *&n;&t;&t; *&t;FIXME: We ought to keep some kind of cache size&n;&t;&t; *&t;limiting and adjust the timers to suit.&n;&t;&t; */
id|entry
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|rif_cache_s
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;tr.c: Couldn&squot;t malloc rif cache entry !&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|rif_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
(paren
id|entry-&gt;addr
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|trh-&gt;saddr
(braket
l_int|0
)braket
)paren
comma
id|TR_ALEN
)paren
suffix:semicolon
id|entry-&gt;iface
op_assign
id|dev-&gt;ifindex
suffix:semicolon
id|entry-&gt;next
op_assign
id|rif_table
(braket
id|hash
)braket
suffix:semicolon
id|entry-&gt;last_used
op_assign
id|jiffies
suffix:semicolon
id|rif_table
(braket
id|hash
)braket
op_assign
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|rii_p
)paren
(brace
id|entry-&gt;rcf
op_assign
id|trh-&gt;rcf
op_amp
id|htons
c_func
(paren
(paren
r_int
r_int
)paren
op_complement
id|TR_RCF_BROADCAST_MASK
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
(paren
id|entry-&gt;rseg
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|trh-&gt;rseg
(braket
l_int|0
)braket
)paren
comma
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
id|entry-&gt;local_ring
op_assign
l_int|0
suffix:semicolon
id|trh-&gt;saddr
(braket
l_int|0
)braket
op_or_assign
id|TR_RII
suffix:semicolon
multiline_comment|/* put the routing indicator back for tcpdump */
)brace
r_else
(brace
id|entry-&gt;local_ring
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
multiline_comment|/* Y. Tahara added */
(brace
multiline_comment|/*&n;&t;&t; *&t;Update existing entries&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;local_ring
)paren
r_if
c_cond
(paren
id|entry-&gt;rcf
op_ne
(paren
id|trh-&gt;rcf
op_amp
id|htons
c_func
(paren
(paren
r_int
r_int
)paren
op_complement
id|TR_RCF_BROADCAST_MASK
)paren
)paren
op_logical_and
op_logical_neg
(paren
id|trh-&gt;rcf
op_amp
id|htons
c_func
(paren
id|TR_RCF_BROADCAST_MASK
)paren
)paren
)paren
(brace
macro_line|#if TR_SR_DEBUG
id|printk
c_func
(paren
l_string|&quot;updating rif_entry: addr:%02X:%02X:%02X:%02X:%02X:%02X rcf:%04X&bslash;n&quot;
comma
id|trh-&gt;saddr
(braket
l_int|0
)braket
comma
id|trh-&gt;saddr
(braket
l_int|1
)braket
comma
id|trh-&gt;saddr
(braket
l_int|2
)braket
comma
id|trh-&gt;saddr
(braket
l_int|3
)braket
comma
id|trh-&gt;saddr
(braket
l_int|4
)braket
comma
id|trh-&gt;saddr
(braket
l_int|5
)braket
comma
id|ntohs
c_func
(paren
id|trh-&gt;rcf
)paren
)paren
suffix:semicolon
macro_line|#endif
id|entry-&gt;rcf
op_assign
id|trh-&gt;rcf
op_amp
id|htons
c_func
(paren
(paren
r_int
r_int
)paren
op_complement
id|TR_RCF_BROADCAST_MASK
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
(paren
id|entry-&gt;rseg
(braket
l_int|0
)braket
)paren
comma
op_amp
(paren
id|trh-&gt;rseg
(braket
l_int|0
)braket
)paren
comma
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
)brace
id|entry-&gt;last_used
op_assign
id|jiffies
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|rif_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Scan the cache with a timer and see what we need to throw out.&n; */
DECL|function|rif_check_expire
r_static
r_void
id|rif_check_expire
c_func
(paren
r_int
r_int
id|dummy
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|next_interval
op_assign
id|jiffies
op_plus
id|sysctl_tr_rif_timeout
op_div
l_int|2
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|rif_lock
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
id|RIF_TABLE_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|rif_cache_s
op_star
id|entry
comma
op_star
op_star
id|pentry
suffix:semicolon
id|pentry
op_assign
id|rif_table
op_plus
id|i
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
op_star
id|pentry
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_int
id|expires
op_assign
id|entry-&gt;last_used
op_plus
id|sysctl_tr_rif_timeout
suffix:semicolon
r_if
c_cond
(paren
id|time_before_eq
c_func
(paren
id|expires
comma
id|jiffies
)paren
)paren
(brace
op_star
id|pentry
op_assign
id|entry-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
r_else
(brace
id|pentry
op_assign
op_amp
id|entry-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|expires
comma
id|next_interval
)paren
)paren
id|next_interval
op_assign
id|expires
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|rif_lock
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|rif_timer
comma
id|next_interval
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Generate the /proc/net information for the token ring RIF&n; *&t;routing.&n; */
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|rif_get_idx
r_static
r_struct
id|rif_cache_s
op_star
id|rif_get_idx
c_func
(paren
id|loff_t
id|pos
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|rif_cache_s
op_star
id|entry
suffix:semicolon
id|loff_t
id|off
op_assign
l_int|0
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
id|RIF_TABLE_SIZE
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|entry
op_assign
id|rif_table
(braket
id|i
)braket
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|off
op_eq
id|pos
)paren
r_return
id|entry
suffix:semicolon
op_increment
id|off
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|rif_seq_start
r_static
r_void
op_star
id|rif_seq_start
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
id|spin_lock_bh
c_func
(paren
op_amp
id|rif_lock
)paren
suffix:semicolon
r_return
op_star
id|pos
ques
c_cond
id|rif_get_idx
c_func
(paren
op_star
id|pos
op_minus
l_int|1
)paren
suffix:colon
id|SEQ_START_TOKEN
suffix:semicolon
)brace
DECL|function|rif_seq_next
r_static
r_void
op_star
id|rif_seq_next
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
r_int
id|i
suffix:semicolon
r_struct
id|rif_cache_s
op_star
id|ent
op_assign
id|v
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
(brace
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|scan
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ent-&gt;next
)paren
r_return
id|ent-&gt;next
suffix:semicolon
id|i
op_assign
id|rif_hash
c_func
(paren
id|ent-&gt;addr
)paren
suffix:semicolon
id|scan
suffix:colon
r_while
c_loop
(paren
op_increment
id|i
OL
id|RIF_TABLE_SIZE
)paren
(brace
r_if
c_cond
(paren
(paren
id|ent
op_assign
id|rif_table
(braket
id|i
)braket
)paren
op_ne
l_int|NULL
)paren
r_return
id|ent
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|rif_seq_stop
r_static
r_void
id|rif_seq_stop
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
id|spin_unlock_bh
c_func
(paren
op_amp
id|rif_lock
)paren
suffix:semicolon
)brace
DECL|function|rif_seq_show
r_static
r_int
id|rif_seq_show
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
r_int
id|j
comma
id|rcf_len
comma
id|segment
comma
id|brdgnmb
suffix:semicolon
r_struct
id|rif_cache_s
op_star
id|entry
op_assign
id|v
suffix:semicolon
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
l_string|&quot;if     TR address       TTL   rcf   routing segments&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|dev_get_by_index
c_func
(paren
id|entry-&gt;iface
)paren
suffix:semicolon
r_int
id|ttl
op_assign
(paren
r_int
)paren
(paren
id|entry-&gt;last_used
op_plus
id|sysctl_tr_rif_timeout
)paren
op_minus
(paren
r_int
)paren
id|jiffies
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%s %02X:%02X:%02X:%02X:%02X:%02X %7li &quot;
comma
id|dev
ques
c_cond
id|dev-&gt;name
suffix:colon
l_string|&quot;?&quot;
comma
id|entry-&gt;addr
(braket
l_int|0
)braket
comma
id|entry-&gt;addr
(braket
l_int|1
)braket
comma
id|entry-&gt;addr
(braket
l_int|2
)braket
comma
id|entry-&gt;addr
(braket
l_int|3
)braket
comma
id|entry-&gt;addr
(braket
l_int|4
)braket
comma
id|entry-&gt;addr
(braket
l_int|5
)braket
comma
id|ttl
op_div
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;local_ring
)paren
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;local&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%04X&quot;
comma
id|ntohs
c_func
(paren
id|entry-&gt;rcf
)paren
)paren
suffix:semicolon
id|rcf_len
op_assign
(paren
(paren
id|ntohs
c_func
(paren
id|entry-&gt;rcf
)paren
op_amp
id|TR_RCF_LEN_MASK
)paren
op_rshift
l_int|8
)paren
op_minus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|rcf_len
)paren
id|rcf_len
op_rshift_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|rcf_len
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|j
op_eq
l_int|1
)paren
(brace
id|segment
op_assign
id|ntohs
c_func
(paren
id|entry-&gt;rseg
(braket
id|j
op_minus
l_int|1
)braket
)paren
op_rshift
l_int|4
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;  %03X&quot;
comma
id|segment
)paren
suffix:semicolon
)brace
suffix:semicolon
id|segment
op_assign
id|ntohs
c_func
(paren
id|entry-&gt;rseg
(braket
id|j
)braket
)paren
op_rshift
l_int|4
suffix:semicolon
id|brdgnmb
op_assign
id|ntohs
c_func
(paren
id|entry-&gt;rseg
(braket
id|j
op_minus
l_int|1
)braket
)paren
op_amp
l_int|0x00f
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;-%01X-%03X&quot;
comma
id|brdgnmb
comma
id|segment
)paren
suffix:semicolon
)brace
id|seq_putc
c_func
(paren
id|seq
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|rif_seq_ops
r_static
r_struct
id|seq_operations
id|rif_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|rif_seq_start
comma
dot
id|next
op_assign
id|rif_seq_next
comma
dot
id|stop
op_assign
id|rif_seq_stop
comma
dot
id|show
op_assign
id|rif_seq_show
comma
)brace
suffix:semicolon
DECL|function|rif_seq_open
r_static
r_int
id|rif_seq_open
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
id|rif_seq_ops
)paren
suffix:semicolon
)brace
DECL|variable|rif_seq_fops
r_static
r_struct
id|file_operations
id|rif_seq_fops
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
id|rif_seq_open
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
macro_line|#endif
DECL|function|tr_setup
r_static
r_void
id|tr_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/*&n;&t; *&t;Configure and register&n;&t; */
id|dev-&gt;hard_header
op_assign
id|tr_header
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
id|tr_rebuild_header
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_IEEE802_TR
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
id|TR_HLEN
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|2000
suffix:semicolon
id|dev-&gt;addr_len
op_assign
id|TR_ALEN
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* Long queues on tr */
id|memset
c_func
(paren
id|dev-&gt;broadcast
comma
l_int|0xFF
comma
id|TR_ALEN
)paren
suffix:semicolon
multiline_comment|/* New-style flags. */
id|dev-&gt;flags
op_assign
id|IFF_BROADCAST
op_or
id|IFF_MULTICAST
suffix:semicolon
)brace
multiline_comment|/**&n; * alloc_trdev - Register token ring device&n; * @sizeof_priv: Size of additional driver-private structure to be allocated&n; *&t;for this token ring device&n; *&n; * Fill in the fields of the device structure with token ring-generic values.&n; *&n; * Constructs a new net device, complete with a private data area of&n; * size @sizeof_priv.  A 32-byte (not bit) alignment is enforced for&n; * this private data area.&n; */
DECL|function|alloc_trdev
r_struct
id|net_device
op_star
id|alloc_trdev
c_func
(paren
r_int
id|sizeof_priv
)paren
(brace
r_return
id|alloc_netdev
c_func
(paren
id|sizeof_priv
comma
l_string|&quot;tr%d&quot;
comma
id|tr_setup
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Called during bootup.  We don&squot;t actually have to initialise&n; *&t;too much for this.&n; */
DECL|function|rif_init
r_static
r_int
id|__init
id|rif_init
c_func
(paren
r_void
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|rif_timer
)paren
suffix:semicolon
id|rif_timer.expires
op_assign
id|sysctl_tr_rif_timeout
suffix:semicolon
id|rif_timer.data
op_assign
l_int|0L
suffix:semicolon
id|rif_timer.function
op_assign
id|rif_check_expire
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|rif_timer
)paren
suffix:semicolon
id|proc_net_fops_create
c_func
(paren
l_string|&quot;tr_rif&quot;
comma
id|S_IRUGO
comma
op_amp
id|rif_seq_fops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|rif_init
id|module_init
c_func
(paren
id|rif_init
)paren
suffix:semicolon
DECL|variable|tr_source_route
id|EXPORT_SYMBOL
c_func
(paren
id|tr_source_route
)paren
suffix:semicolon
DECL|variable|tr_type_trans
id|EXPORT_SYMBOL
c_func
(paren
id|tr_type_trans
)paren
suffix:semicolon
DECL|variable|alloc_trdev
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_trdev
)paren
suffix:semicolon
eof
