multiline_comment|/* &n; * dvb_net.c&n; *&n; * Copyright (C) 2001 Convergence integrated media GmbH&n; *                    Ralph Metzler &lt;ralph@convergence.de&gt;&n; * Copyright (C) 2002 Ralph Metzler &lt;rjkm@metzlerbros.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; * &n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; * Or, point your browser to http://www.gnu.org/copyleft/gpl.html&n; * &n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/dvb/net.h&gt;
macro_line|#include &quot;dvb_demux.h&quot;
macro_line|#include &quot;dvb_net.h&quot;
macro_line|#include &quot;dvb_functions.h&quot;
DECL|macro|DVB_NET_MULTICAST_MAX
mdefine_line|#define DVB_NET_MULTICAST_MAX 10
DECL|struct|dvb_net_priv
r_struct
id|dvb_net_priv
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|pid
id|u16
id|pid
suffix:semicolon
DECL|member|demux
r_struct
id|dmx_demux
op_star
id|demux
suffix:semicolon
DECL|member|secfeed
r_struct
id|dmx_section_feed
op_star
id|secfeed
suffix:semicolon
DECL|member|secfilter
r_struct
id|dmx_section_filter
op_star
id|secfilter
suffix:semicolon
DECL|member|multi_num
r_int
id|multi_num
suffix:semicolon
DECL|member|multi_secfilter
r_struct
id|dmx_section_filter
op_star
id|multi_secfilter
(braket
id|DVB_NET_MULTICAST_MAX
)braket
suffix:semicolon
DECL|member|multi_macs
r_int
r_char
id|multi_macs
(braket
id|DVB_NET_MULTICAST_MAX
)braket
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Determine the packet&squot;s protocol ID. The rule here is that we &n; *&t;assume 802.3 if the type field is short enough to be a length.&n; *&t;This is normal practice and works for any &squot;now in use&squot; protocol.&n; *&n; *  stolen from eth.c out of the linux kernel, hacked for dvb-device&n; *  by Michael Holzt &lt;kju@debian.org&gt;&n; */
DECL|function|my_eth_type_trans
r_int
r_int
id|my_eth_type_trans
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
id|ethhdr
op_star
id|eth
suffix:semicolon
r_int
r_char
op_star
id|rawp
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|dev-&gt;hard_header_len
)paren
suffix:semicolon
id|eth
op_assign
id|skb-&gt;mac.ethernet
suffix:semicolon
r_if
c_cond
(paren
op_star
id|eth-&gt;h_dest
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|eth-&gt;h_dest
comma
id|dev-&gt;broadcast
comma
id|ETH_ALEN
)paren
op_eq
l_int|0
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
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|eth-&gt;h_proto
)paren
op_ge
l_int|1536
)paren
r_return
id|eth-&gt;h_proto
suffix:semicolon
id|rawp
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/*&n;&t; *&t;This is a magic hack to spot IPX packets. Older Novell breaks&n;&t; *&t;the protocol design and runs IPX over 802.3 without an 802.2 LLC&n;&t; *&t;layer. We look for FFFF which isn&squot;t a used 802.2 SSAP/DSAP. This&n;&t; *&t;won&squot;t work for fault tolerant netware but does for the rest.&n;&t; */
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|rawp
op_eq
l_int|0xFFFF
)paren
r_return
id|htons
c_func
(paren
id|ETH_P_802_3
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Real 802.2 LLC&n;&t; */
r_return
id|htons
c_func
(paren
id|ETH_P_802_2
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|dvb_net_sec
id|dvb_net_sec
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_const
id|u8
op_star
id|pkt
comma
r_int
id|pkt_len
)paren
(brace
id|u8
op_star
id|eth
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|pkt_len
OL
l_int|13
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: IP/MPE packet length = %d too small.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|pkt_len
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|pkt_len
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: Memory squeeze, dropping packet.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
(paren
(paren
r_struct
id|dvb_net_priv
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|stats.rx_dropped
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
id|eth
op_assign
(paren
id|u8
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
id|pkt_len
op_plus
l_int|2
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|eth
op_plus
l_int|14
comma
(paren
r_void
op_star
)paren
id|pkt
op_plus
l_int|12
comma
id|pkt_len
op_minus
l_int|12
)paren
suffix:semicolon
id|eth
(braket
l_int|0
)braket
op_assign
id|pkt
(braket
l_int|0x0b
)braket
suffix:semicolon
id|eth
(braket
l_int|1
)braket
op_assign
id|pkt
(braket
l_int|0x0a
)braket
suffix:semicolon
id|eth
(braket
l_int|2
)braket
op_assign
id|pkt
(braket
l_int|0x09
)braket
suffix:semicolon
id|eth
(braket
l_int|3
)braket
op_assign
id|pkt
(braket
l_int|0x08
)braket
suffix:semicolon
id|eth
(braket
l_int|4
)braket
op_assign
id|pkt
(braket
l_int|0x04
)braket
suffix:semicolon
id|eth
(braket
l_int|5
)braket
op_assign
id|pkt
(braket
l_int|0x03
)braket
suffix:semicolon
id|eth
(braket
l_int|6
)braket
op_assign
id|eth
(braket
l_int|7
)braket
op_assign
id|eth
(braket
l_int|8
)braket
op_assign
id|eth
(braket
l_int|9
)braket
op_assign
id|eth
(braket
l_int|10
)braket
op_assign
id|eth
(braket
l_int|11
)braket
op_assign
l_int|0
suffix:semicolon
id|eth
(braket
l_int|12
)braket
op_assign
l_int|0x08
suffix:semicolon
id|eth
(braket
l_int|13
)braket
op_assign
l_int|0x00
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|my_eth_type_trans
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
(paren
(paren
r_struct
id|dvb_net_priv
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|stats.rx_packets
op_increment
suffix:semicolon
(paren
(paren
r_struct
id|dvb_net_priv
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|stats.rx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|dvb_net_callback
id|dvb_net_callback
c_func
(paren
r_const
id|u8
op_star
id|buffer1
comma
r_int
id|buffer1_len
comma
r_const
id|u8
op_star
id|buffer2
comma
r_int
id|buffer2_len
comma
r_struct
id|dmx_section_filter
op_star
id|filter
comma
r_enum
id|dmx_success
id|success
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
id|filter-&gt;priv
suffix:semicolon
multiline_comment|/* FIXME: this only works if exactly one complete section is&n;&t;          delivered in buffer1 only */
id|dvb_net_sec
c_func
(paren
id|dev
comma
id|buffer1
comma
id|buffer1_len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dvb_net_tx
id|dvb_net_tx
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mask_normal
r_static
id|u8
id|mask_normal
(braket
l_int|6
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|mask_allmulti
r_static
id|u8
id|mask_allmulti
(braket
l_int|6
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|mac_allmulti
r_static
id|u8
id|mac_allmulti
(braket
l_int|6
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|mask_promisc
r_static
id|u8
id|mask_promisc
(braket
l_int|6
)braket
op_assign
initialization_block
suffix:semicolon
r_static
r_int
DECL|function|dvb_net_filter_set
id|dvb_net_filter_set
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|dmx_section_filter
op_star
op_star
id|secfilter
comma
id|u8
op_star
id|mac
comma
id|u8
op_star
id|mac_mask
)paren
(brace
r_struct
id|dvb_net_priv
op_star
id|priv
op_assign
(paren
r_struct
id|dvb_net_priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ret
suffix:semicolon
op_star
id|secfilter
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|priv-&gt;secfeed
op_member_access_from_pointer
id|allocate_filter
c_func
(paren
id|priv-&gt;secfeed
comma
id|secfilter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: could not get filter&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|priv
op_assign
(paren
r_void
op_star
)paren
id|dev
suffix:semicolon
id|memset
c_func
(paren
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_value
comma
l_int|0x00
comma
id|DMX_MAX_FILTER_SIZE
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_mask
comma
l_int|0x00
comma
id|DMX_MAX_FILTER_SIZE
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_mode
comma
l_int|0xff
comma
id|DMX_MAX_FILTER_SIZE
)paren
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_value
(braket
l_int|0
)braket
op_assign
l_int|0x3e
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_mask
(braket
l_int|0
)braket
op_assign
l_int|0xff
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_value
(braket
l_int|3
)braket
op_assign
id|mac
(braket
l_int|5
)braket
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_mask
(braket
l_int|3
)braket
op_assign
id|mac_mask
(braket
l_int|5
)braket
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_value
(braket
l_int|4
)braket
op_assign
id|mac
(braket
l_int|4
)braket
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_mask
(braket
l_int|4
)braket
op_assign
id|mac_mask
(braket
l_int|4
)braket
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_value
(braket
l_int|8
)braket
op_assign
id|mac
(braket
l_int|3
)braket
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_mask
(braket
l_int|8
)braket
op_assign
id|mac_mask
(braket
l_int|3
)braket
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_value
(braket
l_int|9
)braket
op_assign
id|mac
(braket
l_int|2
)braket
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_mask
(braket
l_int|9
)braket
op_assign
id|mac_mask
(braket
l_int|2
)braket
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_value
(braket
l_int|10
)braket
op_assign
id|mac
(braket
l_int|1
)braket
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_mask
(braket
l_int|10
)braket
op_assign
id|mac_mask
(braket
l_int|1
)braket
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_value
(braket
l_int|11
)braket
op_assign
id|mac
(braket
l_int|0
)braket
suffix:semicolon
(paren
op_star
id|secfilter
)paren
op_member_access_from_pointer
id|filter_mask
(braket
l_int|11
)braket
op_assign
id|mac_mask
(braket
l_int|0
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: filter mac=%02x %02x %02x %02x %02x %02x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|mac
(braket
l_int|0
)braket
comma
id|mac
(braket
l_int|1
)braket
comma
id|mac
(braket
l_int|2
)braket
comma
id|mac
(braket
l_int|3
)braket
comma
id|mac
(braket
l_int|4
)braket
comma
id|mac
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dvb_net_feed_start
id|dvb_net_feed_start
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|ret
comma
id|i
suffix:semicolon
r_struct
id|dvb_net_priv
op_star
id|priv
op_assign
(paren
r_struct
id|dvb_net_priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|dmx_demux
op_star
id|demux
op_assign
id|priv-&gt;demux
suffix:semicolon
r_int
r_char
op_star
id|mac
op_assign
(paren
r_int
r_char
op_star
)paren
id|dev-&gt;dev_addr
suffix:semicolon
id|priv-&gt;secfeed
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;secfilter
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|demux
op_member_access_from_pointer
id|allocate_section_feed
c_func
(paren
id|demux
comma
op_amp
id|priv-&gt;secfeed
comma
id|dvb_net_callback
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: could not get section feed&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|priv-&gt;secfeed
op_member_access_from_pointer
id|set
c_func
(paren
id|priv-&gt;secfeed
comma
id|priv-&gt;pid
comma
l_int|32768
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: could not set section feed&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|priv-&gt;demux
op_member_access_from_pointer
id|release_section_feed
c_func
(paren
id|priv-&gt;demux
comma
id|priv-&gt;secfeed
)paren
suffix:semicolon
id|priv-&gt;secfeed
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* fixme: is this correct? */
id|try_module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;mode
OL
l_int|3
)paren
id|dvb_net_filter_set
c_func
(paren
id|dev
comma
op_amp
id|priv-&gt;secfilter
comma
id|mac
comma
id|mask_normal
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|priv-&gt;mode
)paren
(brace
r_case
l_int|1
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|priv-&gt;multi_num
suffix:semicolon
id|i
op_increment
)paren
id|dvb_net_filter_set
c_func
(paren
id|dev
comma
op_amp
id|priv-&gt;multi_secfilter
(braket
id|i
)braket
comma
id|priv-&gt;multi_macs
(braket
id|i
)braket
comma
id|mask_normal
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|priv-&gt;multi_num
op_assign
l_int|1
suffix:semicolon
id|dvb_net_filter_set
c_func
(paren
id|dev
comma
op_amp
id|priv-&gt;multi_secfilter
(braket
l_int|0
)braket
comma
id|mac_allmulti
comma
id|mask_allmulti
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|priv-&gt;multi_num
op_assign
l_int|0
suffix:semicolon
id|dvb_net_filter_set
c_func
(paren
id|dev
comma
op_amp
id|priv-&gt;secfilter
comma
id|mac
comma
id|mask_promisc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|priv-&gt;secfeed
op_member_access_from_pointer
id|start_filtering
c_func
(paren
id|priv-&gt;secfeed
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|dvb_net_feed_stop
id|dvb_net_feed_stop
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|dvb_net_priv
op_star
id|priv
op_assign
(paren
r_struct
id|dvb_net_priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;secfeed
)paren
(brace
r_if
c_cond
(paren
id|priv-&gt;secfeed-&gt;is_filtering
)paren
id|priv-&gt;secfeed
op_member_access_from_pointer
id|stop_filtering
c_func
(paren
id|priv-&gt;secfeed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;secfilter
)paren
id|priv-&gt;secfeed
op_member_access_from_pointer
id|release_filter
c_func
(paren
id|priv-&gt;secfeed
comma
id|priv-&gt;secfilter
)paren
suffix:semicolon
id|priv-&gt;secfilter
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
id|priv-&gt;multi_num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|priv-&gt;multi_secfilter
(braket
id|i
)braket
)paren
id|priv-&gt;secfeed
op_member_access_from_pointer
id|release_filter
c_func
(paren
id|priv-&gt;secfeed
comma
id|priv-&gt;multi_secfilter
(braket
id|i
)braket
)paren
suffix:semicolon
id|priv-&gt;multi_secfilter
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|priv-&gt;demux
op_member_access_from_pointer
id|release_section_feed
c_func
(paren
id|priv-&gt;demux
comma
id|priv-&gt;secfeed
)paren
suffix:semicolon
id|priv-&gt;secfeed
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* fixme: is this correct? */
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;%s: no feed to stop&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|dvb_add_mc_filter
id|dvb_add_mc_filter
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|dev_mc_list
op_star
id|mc
)paren
(brace
r_struct
id|dvb_net_priv
op_star
id|priv
op_assign
(paren
r_struct
id|dvb_net_priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;multi_num
op_ge
id|DVB_NET_MULTICAST_MAX
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ret
op_assign
id|memcmp
c_func
(paren
id|priv-&gt;multi_macs
(braket
id|priv-&gt;multi_num
)braket
comma
id|mc-&gt;dmi_addr
comma
l_int|6
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|priv-&gt;multi_macs
(braket
id|priv-&gt;multi_num
)braket
comma
id|mc-&gt;dmi_addr
comma
l_int|6
)paren
suffix:semicolon
id|priv-&gt;multi_num
op_increment
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|dvb_net_set_multi
id|dvb_net_set_multi
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|dvb_net_priv
op_star
id|priv
op_assign
(paren
r_struct
id|dvb_net_priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|dev_mc_list
op_star
id|mc
suffix:semicolon
r_int
id|mci
suffix:semicolon
r_int
id|update
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_PROMISC
)paren
(brace
singleline_comment|//&t;printk(&quot;%s: promiscuous mode&bslash;n&quot;, dev-&gt;name);
r_if
c_cond
(paren
id|priv-&gt;mode
op_ne
l_int|3
)paren
(brace
id|update
op_assign
l_int|1
suffix:semicolon
)brace
id|priv-&gt;mode
op_assign
l_int|3
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_ALLMULTI
)paren
(brace
singleline_comment|//&t;printk(&quot;%s: allmulti mode&bslash;n&quot;, dev-&gt;name);
r_if
c_cond
(paren
id|priv-&gt;mode
op_ne
l_int|2
)paren
(brace
id|update
op_assign
l_int|1
suffix:semicolon
)brace
id|priv-&gt;mode
op_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;mc_count
OG
l_int|0
)paren
(brace
singleline_comment|//&t;printk(&quot;%s: set_mc_list, %d entries&bslash;n&quot;, 
singleline_comment|//&t;       dev-&gt;name, dev-&gt;mc_count);
r_if
c_cond
(paren
id|priv-&gt;mode
op_ne
l_int|1
)paren
(brace
id|update
op_assign
l_int|1
suffix:semicolon
)brace
id|priv-&gt;mode
op_assign
l_int|1
suffix:semicolon
id|priv-&gt;multi_num
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|mci
op_assign
l_int|0
comma
id|mc
op_assign
id|dev-&gt;mc_list
suffix:semicolon
id|mci
OL
id|dev-&gt;mc_count
suffix:semicolon
id|mc
op_assign
id|mc-&gt;next
comma
id|mci
op_increment
)paren
r_if
c_cond
(paren
id|dvb_add_mc_filter
c_func
(paren
id|dev
comma
id|mc
)paren
op_ne
l_int|0
)paren
(brace
id|update
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|priv-&gt;mode
op_ne
l_int|0
)paren
(brace
id|update
op_assign
l_int|1
suffix:semicolon
)brace
id|priv-&gt;mode
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|netif_running
c_func
(paren
id|dev
)paren
op_ne
l_int|0
op_logical_and
id|update
OG
l_int|0
)paren
(brace
id|dvb_net_feed_stop
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dvb_net_feed_start
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|dvb_net_set_config
id|dvb_net_set_config
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifmap
op_star
id|map
)paren
(brace
r_if
c_cond
(paren
id|netif_running
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dvb_net_set_mac
id|dvb_net_set_mac
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|p
)paren
(brace
r_struct
id|sockaddr
op_star
id|addr
op_assign
id|p
suffix:semicolon
r_int
id|update
suffix:semicolon
id|update
op_assign
id|memcmp
c_func
(paren
id|dev-&gt;dev_addr
comma
id|addr-&gt;sa_data
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
id|addr-&gt;sa_data
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|netif_running
c_func
(paren
id|dev
)paren
op_ne
l_int|0
op_logical_and
id|update
OG
l_int|0
)paren
(brace
id|dvb_net_feed_stop
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dvb_net_feed_start
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dvb_net_open
id|dvb_net_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|dvb_net_feed_start
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dvb_net_stop
id|dvb_net_stop
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|dvb_net_feed_stop
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_struct
id|net_device_stats
op_star
DECL|function|dvb_net_get_stats
id|dvb_net_get_stats
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
(paren
(paren
r_struct
id|dvb_net_priv
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|stats
suffix:semicolon
)brace
r_static
r_int
DECL|function|dvb_net_init_dev
id|dvb_net_init_dev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;open
op_assign
id|dvb_net_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|dvb_net_stop
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|dvb_net_tx
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|dvb_net_get_stats
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
id|dvb_net_set_multi
suffix:semicolon
id|dev-&gt;set_config
op_assign
id|dvb_net_set_config
suffix:semicolon
id|dev-&gt;set_mac_address
op_assign
id|dvb_net_set_mac
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|4096
suffix:semicolon
id|dev-&gt;mc_count
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;flags
op_or_assign
id|IFF_NOARP
suffix:semicolon
id|dev-&gt;hard_header_cache
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|//SET_MODULE_OWNER(dev);
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|get_if
id|get_if
c_func
(paren
r_struct
id|dvb_net
op_star
id|dvbnet
)paren
(brace
r_int
id|i
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
id|dvbnet-&gt;dev_num
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|dvbnet-&gt;state
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|dvbnet-&gt;dev_num
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|dvbnet-&gt;state
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
r_int
DECL|function|dvb_net_add_if
id|dvb_net_add_if
c_func
(paren
r_struct
id|dvb_net
op_star
id|dvbnet
comma
id|u16
id|pid
)paren
(brace
r_struct
id|net_device
op_star
id|net
suffix:semicolon
r_struct
id|dmx_demux
op_star
id|demux
suffix:semicolon
r_struct
id|dvb_net_priv
op_star
id|priv
suffix:semicolon
r_int
id|result
suffix:semicolon
r_int
id|if_num
suffix:semicolon
id|if_num
op_assign
id|get_if
c_func
(paren
id|dvbnet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|if_num
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|net
op_assign
op_amp
id|dvbnet-&gt;device
(braket
id|if_num
)braket
suffix:semicolon
id|demux
op_assign
id|dvbnet-&gt;demux
suffix:semicolon
id|net-&gt;base_addr
op_assign
l_int|0
suffix:semicolon
id|net-&gt;irq
op_assign
l_int|0
suffix:semicolon
id|net-&gt;dma
op_assign
l_int|0
suffix:semicolon
id|net-&gt;mem_start
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|net-&gt;name
comma
l_string|&quot;dvb0_0&quot;
comma
l_int|7
)paren
suffix:semicolon
id|net-&gt;name
(braket
l_int|3
)braket
op_assign
id|dvbnet-&gt;card_num
op_plus
l_int|0x30
suffix:semicolon
id|net-&gt;name
(braket
l_int|5
)braket
op_assign
id|if_num
op_plus
l_int|0x30
suffix:semicolon
id|net-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|net-&gt;init
op_assign
id|dvb_net_init_dev
suffix:semicolon
id|net-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dvb_net_priv
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net-&gt;priv
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|priv
op_assign
id|net-&gt;priv
suffix:semicolon
id|memset
c_func
(paren
id|priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dvb_net_priv
)paren
)paren
suffix:semicolon
id|priv-&gt;demux
op_assign
id|demux
suffix:semicolon
id|priv-&gt;pid
op_assign
id|pid
suffix:semicolon
id|priv-&gt;mode
op_assign
l_int|0
suffix:semicolon
id|net-&gt;base_addr
op_assign
id|pid
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|register_netdev
c_func
(paren
id|net
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* fixme: is this correct? */
id|try_module_get
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
r_return
id|if_num
suffix:semicolon
)brace
r_int
DECL|function|dvb_net_remove_if
id|dvb_net_remove_if
c_func
(paren
r_struct
id|dvb_net
op_star
id|dvbnet
comma
r_int
id|num
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dvbnet-&gt;state
(braket
id|num
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dvb_net_stop
c_func
(paren
op_amp
id|dvbnet-&gt;device
(braket
id|num
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dvbnet-&gt;device
(braket
id|num
)braket
dot
id|priv
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
op_amp
id|dvbnet-&gt;device
(braket
id|num
)braket
)paren
suffix:semicolon
id|dvbnet-&gt;state
(braket
id|num
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* fixme: is this correct? */
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_net_do_ioctl
r_int
id|dvb_net_do_ioctl
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
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|parg
)paren
(brace
r_struct
id|dvb_device
op_star
id|dvbdev
op_assign
(paren
r_struct
id|dvb_device
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|dvb_net
op_star
id|dvbnet
op_assign
(paren
r_struct
id|dvb_net
op_star
)paren
id|dvbdev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|file-&gt;f_flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_RDONLY
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|NET_ADD_IF
suffix:colon
(brace
r_struct
id|dvb_net_if
op_star
id|dvbnetif
op_assign
(paren
r_struct
id|dvb_net_if
op_star
)paren
id|parg
suffix:semicolon
r_int
id|result
suffix:semicolon
id|result
op_assign
id|dvb_net_add_if
c_func
(paren
id|dvbnet
comma
id|dvbnetif-&gt;pid
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
id|dvbnetif-&gt;if_num
op_assign
id|result
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|NET_GET_IF
suffix:colon
(brace
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
r_struct
id|dvb_net_priv
op_star
id|priv_data
suffix:semicolon
r_struct
id|dvb_net_if
op_star
id|dvbnetif
op_assign
(paren
r_struct
id|dvb_net_if
op_star
)paren
id|parg
suffix:semicolon
r_if
c_cond
(paren
id|dvbnetif-&gt;if_num
op_ge
id|dvbnet-&gt;dev_num
op_logical_or
op_logical_neg
id|dvbnet-&gt;state
(braket
id|dvbnetif-&gt;if_num
)braket
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|netdev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
op_amp
id|dvbnet-&gt;device
(braket
id|dvbnetif-&gt;if_num
)braket
suffix:semicolon
id|priv_data
op_assign
(paren
r_struct
id|dvb_net_priv
op_star
)paren
id|netdev-&gt;priv
suffix:semicolon
id|dvbnetif-&gt;pid
op_assign
id|priv_data-&gt;pid
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|NET_REMOVE_IF
suffix:colon
r_return
id|dvb_net_remove_if
c_func
(paren
id|dvbnet
comma
(paren
r_int
)paren
id|parg
)paren
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
r_static
r_int
DECL|function|dvb_net_ioctl
id|dvb_net_ioctl
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
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
id|dvb_usercopy
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
comma
id|dvb_net_do_ioctl
)paren
suffix:semicolon
)brace
DECL|variable|dvb_net_fops
r_static
r_struct
id|file_operations
id|dvb_net_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
l_int|0
comma
dot
id|write
op_assign
l_int|0
comma
dot
id|ioctl
op_assign
id|dvb_net_ioctl
comma
dot
id|open
op_assign
id|dvb_generic_open
comma
dot
id|release
op_assign
id|dvb_generic_release
comma
dot
id|poll
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|dvbdev_net
r_static
r_struct
id|dvb_device
id|dvbdev_net
op_assign
(brace
dot
id|priv
op_assign
l_int|0
comma
dot
id|users
op_assign
l_int|1
comma
dot
id|writers
op_assign
l_int|1
comma
dot
id|fops
op_assign
op_amp
id|dvb_net_fops
comma
)brace
suffix:semicolon
r_void
DECL|function|dvb_net_release
id|dvb_net_release
c_func
(paren
r_struct
id|dvb_net
op_star
id|dvbnet
)paren
(brace
r_int
id|i
suffix:semicolon
id|dvb_unregister_device
c_func
(paren
id|dvbnet-&gt;dvbdev
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
id|dvbnet-&gt;dev_num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dvbnet-&gt;state
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|dvb_net_remove_if
c_func
(paren
id|dvbnet
comma
id|i
)paren
suffix:semicolon
)brace
)brace
r_int
DECL|function|dvb_net_init
id|dvb_net_init
c_func
(paren
r_struct
id|dvb_adapter
op_star
id|adap
comma
r_struct
id|dvb_net
op_star
id|dvbnet
comma
r_struct
id|dmx_demux
op_star
id|dmx
)paren
(brace
r_int
id|i
suffix:semicolon
id|dvbnet-&gt;demux
op_assign
id|dmx
suffix:semicolon
id|dvbnet-&gt;dev_num
op_assign
id|DVB_NET_DEVICES_MAX
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
id|dvbnet-&gt;dev_num
suffix:semicolon
id|i
op_increment
)paren
id|dvbnet-&gt;state
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|dvb_register_device
(paren
id|adap
comma
op_amp
id|dvbnet-&gt;dvbdev
comma
op_amp
id|dvbdev_net
comma
id|dvbnet
comma
id|DVB_DEVICE_NET
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
