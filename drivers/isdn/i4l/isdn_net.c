multiline_comment|/* Linux ISDN subsystem, network interfaces and related functions (linklevel).&n; *&n; * Copyright 1994-1998  by Fritz Elfert (fritz@isdn4linux.de)&n; *           1995,96    by Thinking Objects Software GmbH Wuerzburg&n; *           1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; *           1999-2002  by Kai Germaschewski &lt;kai@germaschewski.name&gt;&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/isdn.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/dst.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &quot;isdn_common.h&quot;
macro_line|#include &quot;isdn_net.h&quot;
macro_line|#include &quot;isdn_ppp.h&quot;
macro_line|#include &lt;linux/concap.h&gt;
macro_line|#include &quot;isdn_concap.h&quot;
macro_line|#include &quot;isdn_ciscohdlck.h&quot;
singleline_comment|// ISDN_NET_ENCAP_IPTYP
singleline_comment|// ethernet type field
singleline_comment|// ======================================================================
r_static
r_int
DECL|function|isdn_iptyp_header
id|isdn_iptyp_header
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
id|plen
)paren
(brace
id|put_u16
c_func
(paren
id|skb_push
c_func
(paren
id|skb
comma
l_int|2
)paren
comma
id|type
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_static
r_void
DECL|function|isdn_iptyp_receive
id|isdn_iptyp_receive
c_func
(paren
id|isdn_net_local
op_star
id|lp
comma
id|isdn_net_dev
op_star
id|idev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|u16
id|protocol
suffix:semicolon
id|get_u16
c_func
(paren
id|skb-&gt;data
comma
op_amp
id|protocol
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|isdn_netif_rx
c_func
(paren
id|idev
comma
id|skb
comma
id|protocol
)paren
suffix:semicolon
)brace
DECL|variable|iptyp_ops
r_static
r_struct
id|isdn_netif_ops
id|iptyp_ops
op_assign
(brace
dot
id|hard_start_xmit
op_assign
id|isdn_net_start_xmit
comma
dot
id|hard_header
op_assign
id|isdn_iptyp_header
comma
dot
id|flags
op_assign
id|IFF_NOARP
op_or
id|IFF_POINTOPOINT
comma
dot
id|type
op_assign
id|ARPHRD_PPP
comma
dot
id|addr_len
op_assign
l_int|2
comma
dot
id|receive
op_assign
id|isdn_iptyp_receive
comma
)brace
suffix:semicolon
singleline_comment|// ISDN_NET_ENCAP_UIHDLC
singleline_comment|// HDLC with UI-Frames (for ispa with -h1 option) */
singleline_comment|// ======================================================================
r_static
r_int
DECL|function|isdn_uihdlc_header
id|isdn_uihdlc_header
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
id|plen
)paren
(brace
id|put_u16
c_func
(paren
id|skb_push
c_func
(paren
id|skb
comma
l_int|2
)paren
comma
l_int|0x0103
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_static
r_void
DECL|function|isdn_uihdlc_receive
id|isdn_uihdlc_receive
c_func
(paren
id|isdn_net_local
op_star
id|lp
comma
id|isdn_net_dev
op_star
id|idev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|isdn_netif_rx
c_func
(paren
id|idev
comma
id|skb
comma
id|htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
suffix:semicolon
)brace
DECL|variable|uihdlc_ops
r_static
r_struct
id|isdn_netif_ops
id|uihdlc_ops
op_assign
(brace
dot
id|hard_start_xmit
op_assign
id|isdn_net_start_xmit
comma
dot
id|hard_header
op_assign
id|isdn_uihdlc_header
comma
dot
id|flags
op_assign
id|IFF_NOARP
op_or
id|IFF_POINTOPOINT
comma
dot
id|type
op_assign
id|ARPHRD_HDLC
comma
dot
id|addr_len
op_assign
l_int|2
comma
dot
id|receive
op_assign
id|isdn_uihdlc_receive
comma
)brace
suffix:semicolon
singleline_comment|// ISDN_NET_ENCAP_RAWIP
singleline_comment|// RAW-IP without MAC-Header
singleline_comment|// ======================================================================
r_static
r_void
DECL|function|isdn_rawip_receive
id|isdn_rawip_receive
c_func
(paren
id|isdn_net_local
op_star
id|lp
comma
id|isdn_net_dev
op_star
id|idev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|idev-&gt;huptimer
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|variable|rawip_ops
r_static
r_struct
id|isdn_netif_ops
id|rawip_ops
op_assign
(brace
dot
id|hard_start_xmit
op_assign
id|isdn_net_start_xmit
comma
dot
id|flags
op_assign
id|IFF_NOARP
op_or
id|IFF_POINTOPOINT
comma
dot
id|type
op_assign
id|ARPHRD_PPP
comma
dot
id|receive
op_assign
id|isdn_rawip_receive
comma
)brace
suffix:semicolon
singleline_comment|// ISDN_NET_ENCAP_ETHER
singleline_comment|// Ethernet over ISDN
singleline_comment|// ======================================================================
r_static
r_void
DECL|function|isdn_ether_receive
id|isdn_ether_receive
c_func
(paren
id|isdn_net_local
op_star
id|lp
comma
id|isdn_net_dev
op_star
id|idev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|isdn_netif_rx
c_func
(paren
id|idev
comma
id|skb
comma
id|eth_type_trans
c_func
(paren
id|skb
comma
op_amp
id|lp-&gt;dev
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|isdn_ether_open
id|isdn_ether_open
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
op_amp
id|lp-&gt;dev
suffix:semicolon
r_struct
id|in_device
op_star
id|in_dev
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Fill in the MAC-level header ... */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
)paren
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
l_int|0xfc
suffix:semicolon
id|in_dev
op_assign
id|dev-&gt;ip_ptr
suffix:semicolon
r_if
c_cond
(paren
id|in_dev
)paren
(brace
multiline_comment|/* any address will do - we take the first */
r_struct
id|in_ifaddr
op_star
id|ifa
op_assign
id|in_dev-&gt;ifa_list
suffix:semicolon
r_if
c_cond
(paren
id|ifa
)paren
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
op_plus
l_int|2
comma
op_amp
id|ifa-&gt;ifa_local
comma
l_int|4
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|isdn_ether_init
id|isdn_ether_init
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
op_amp
id|lp-&gt;dev
suffix:semicolon
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|10
suffix:semicolon
id|dev-&gt;hard_header_len
op_add_assign
id|isdn_hard_header_len
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ether_ops
r_static
r_struct
id|isdn_netif_ops
id|ether_ops
op_assign
(brace
dot
id|hard_start_xmit
op_assign
id|isdn_net_start_xmit
comma
dot
id|receive
op_assign
id|isdn_ether_receive
comma
dot
id|init
op_assign
id|isdn_ether_init
comma
dot
id|open
op_assign
id|isdn_ether_open
comma
)brace
suffix:semicolon
singleline_comment|// ======================================================================
r_void
DECL|function|isdn_net_init
id|isdn_net_init
c_func
(paren
r_void
)paren
(brace
id|isdn_net_lib_init
c_func
(paren
)paren
suffix:semicolon
id|register_isdn_netif
c_func
(paren
id|ISDN_NET_ENCAP_ETHER
comma
op_amp
id|ether_ops
)paren
suffix:semicolon
id|register_isdn_netif
c_func
(paren
id|ISDN_NET_ENCAP_RAWIP
comma
op_amp
id|rawip_ops
)paren
suffix:semicolon
id|register_isdn_netif
c_func
(paren
id|ISDN_NET_ENCAP_IPTYP
comma
op_amp
id|iptyp_ops
)paren
suffix:semicolon
id|register_isdn_netif
c_func
(paren
id|ISDN_NET_ENCAP_UIHDLC
comma
op_amp
id|uihdlc_ops
)paren
suffix:semicolon
id|register_isdn_netif
c_func
(paren
id|ISDN_NET_ENCAP_CISCOHDLC
comma
op_amp
id|ciscohdlck_ops
)paren
suffix:semicolon
id|register_isdn_netif
c_func
(paren
id|ISDN_NET_ENCAP_CISCOHDLCK
comma
op_amp
id|ciscohdlck_ops
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_X25
id|register_isdn_netif
c_func
(paren
id|ISDN_NET_ENCAP_X25IFACE
comma
op_amp
id|isdn_x25_ops
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_PPP
id|register_isdn_netif
c_func
(paren
id|ISDN_NET_ENCAP_SYNCPPP
comma
op_amp
id|isdn_ppp_ops
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
DECL|function|isdn_net_exit
id|isdn_net_exit
c_func
(paren
r_void
)paren
(brace
id|isdn_net_lib_exit
c_func
(paren
)paren
suffix:semicolon
)brace
eof
