multiline_comment|/*&n; * Generic HDLC support routines for Linux&n; * HDLC Ethernet emulation support&n; *&n; * Copyright (C) 2002-2003 Krzysztof Halasa &lt;khc@pm.waw.pl&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License&n; * as published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/pkt_sched.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/lapb.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/hdlc.h&gt;
DECL|function|eth_tx
r_static
r_int
id|eth_tx
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
r_int
id|pad
op_assign
id|ETH_ZLEN
op_minus
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|pad
OG
l_int|0
)paren
(brace
multiline_comment|/* Pad the frame with zeros */
r_int
id|len
op_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|skb_tailroom
c_func
(paren
id|skb
)paren
OL
id|pad
)paren
r_if
c_cond
(paren
id|pskb_expand_head
c_func
(paren
id|skb
comma
l_int|0
comma
id|pad
comma
id|GFP_ATOMIC
)paren
)paren
(brace
id|hdlc_stats
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|tx_dropped
op_increment
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|skb_put
c_func
(paren
id|skb
comma
id|pad
)paren
suffix:semicolon
id|memset
c_func
(paren
id|skb-&gt;data
op_plus
id|len
comma
l_int|0
comma
id|pad
)paren
suffix:semicolon
)brace
r_return
id|dev_to_hdlc
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|xmit
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
)brace
DECL|function|hdlc_raw_eth_ioctl
r_int
id|hdlc_raw_eth_ioctl
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
)paren
(brace
id|raw_hdlc_proto
id|__user
op_star
id|raw_s
op_assign
id|ifr-&gt;ifr_settings.ifs_ifsu.raw_hdlc
suffix:semicolon
r_const
r_int
id|size
op_assign
r_sizeof
(paren
id|raw_hdlc_proto
)paren
suffix:semicolon
id|raw_hdlc_proto
id|new_settings
suffix:semicolon
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
id|result
suffix:semicolon
r_void
op_star
id|old_ch_mtu
suffix:semicolon
r_int
id|old_qlen
suffix:semicolon
r_switch
c_cond
(paren
id|ifr-&gt;ifr_settings.type
)paren
(brace
r_case
id|IF_GET_PROTO
suffix:colon
id|ifr-&gt;ifr_settings.type
op_assign
id|IF_PROTO_HDLC_ETH
suffix:semicolon
r_if
c_cond
(paren
id|ifr-&gt;ifr_settings.size
OL
id|size
)paren
(brace
id|ifr-&gt;ifr_settings.size
op_assign
id|size
suffix:semicolon
multiline_comment|/* data size wanted */
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|raw_s
comma
op_amp
id|hdlc-&gt;state.raw_hdlc.settings
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|IF_PROTO_HDLC_ETH
suffix:colon
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
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|new_settings
comma
id|raw_s
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|new_settings.encoding
op_eq
id|ENCODING_DEFAULT
)paren
id|new_settings.encoding
op_assign
id|ENCODING_NRZ
suffix:semicolon
r_if
c_cond
(paren
id|new_settings.parity
op_eq
id|PARITY_DEFAULT
)paren
id|new_settings.parity
op_assign
id|PARITY_CRC16_PR1_CCITT
suffix:semicolon
id|result
op_assign
id|hdlc
op_member_access_from_pointer
id|attach
c_func
(paren
id|dev
comma
id|new_settings.encoding
comma
id|new_settings.parity
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
id|hdlc_proto_detach
c_func
(paren
id|hdlc
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|hdlc-&gt;state.raw_hdlc.settings
comma
op_amp
id|new_settings
comma
id|size
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|hdlc-&gt;proto
comma
l_int|0
comma
r_sizeof
(paren
id|hdlc-&gt;proto
)paren
)paren
suffix:semicolon
id|hdlc-&gt;proto.type_trans
op_assign
id|eth_type_trans
suffix:semicolon
id|hdlc-&gt;proto.id
op_assign
id|IF_PROTO_HDLC_ETH
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|eth_tx
suffix:semicolon
id|old_ch_mtu
op_assign
id|dev-&gt;change_mtu
suffix:semicolon
id|old_qlen
op_assign
id|dev-&gt;tx_queue_len
suffix:semicolon
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;change_mtu
op_assign
id|old_ch_mtu
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
id|old_qlen
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
l_string|&quot;&bslash;x00&bslash;x01&quot;
comma
l_int|2
)paren
suffix:semicolon
id|get_random_bytes
c_func
(paren
id|dev-&gt;dev_addr
op_plus
l_int|2
comma
id|ETH_ALEN
op_minus
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
