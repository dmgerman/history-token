multiline_comment|/*&n; * Generic HDLC support routines for Linux&n; * Point-to-point protocol support&n; *&n; * Copyright (C) 1999 - 2001 Krzysztof Halasa &lt;khc@pm.waw.pl&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
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
DECL|function|ppp_open
r_static
r_int
id|ppp_open
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|hdlc_to_dev
c_func
(paren
id|hdlc
)paren
suffix:semicolon
r_void
op_star
id|old_ioctl
suffix:semicolon
r_int
id|result
suffix:semicolon
id|dev-&gt;priv
op_assign
op_amp
id|hdlc-&gt;state.ppp.syncppp_ptr
suffix:semicolon
id|hdlc-&gt;state.ppp.syncppp_ptr
op_assign
op_amp
id|hdlc-&gt;state.ppp.pppdev
suffix:semicolon
id|hdlc-&gt;state.ppp.pppdev.dev
op_assign
id|dev
suffix:semicolon
id|old_ioctl
op_assign
id|dev-&gt;do_ioctl
suffix:semicolon
id|hdlc-&gt;state.ppp.old_change_mtu
op_assign
id|dev-&gt;change_mtu
suffix:semicolon
id|sppp_attach
c_func
(paren
op_amp
id|hdlc-&gt;state.ppp.pppdev
)paren
suffix:semicolon
multiline_comment|/* sppp_attach nukes them. We don&squot;t need syncppp&squot;s ioctl */
id|dev-&gt;do_ioctl
op_assign
id|old_ioctl
suffix:semicolon
id|hdlc-&gt;state.ppp.pppdev.sppp.pp_flags
op_and_assign
op_complement
id|PP_CISCO
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_PPP
suffix:semicolon
id|result
op_assign
id|sppp_open
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
(brace
id|sppp_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ppp_close
r_static
r_void
id|ppp_close
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|hdlc_to_dev
c_func
(paren
id|hdlc
)paren
suffix:semicolon
id|sppp_close
c_func
(paren
id|dev
)paren
suffix:semicolon
id|sppp_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;rebuild_header
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;change_mtu
op_assign
id|hdlc-&gt;state.ppp.old_change_mtu
suffix:semicolon
id|dev-&gt;mtu
op_assign
id|HDLC_MAX_MTU
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
l_int|16
suffix:semicolon
)brace
DECL|function|ppp_rx
r_static
r_void
id|ppp_rx
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_WAN_PPP
)paren
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|hdlc_ppp_ioctl
r_int
id|hdlc_ppp_ioctl
c_func
(paren
id|hdlc_device
op_star
id|hdlc
comma
r_struct
id|ifreq
op_star
id|ifr
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|hdlc_to_dev
c_func
(paren
id|hdlc
)paren
suffix:semicolon
r_int
id|result
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
id|IF_PROTO_PPP
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* return protocol only, no settable parameters */
r_case
id|IF_PROTO_PPP
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
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* no settable parameters */
id|result
op_assign
id|hdlc
op_member_access_from_pointer
id|attach
c_func
(paren
id|hdlc
comma
id|ENCODING_NRZ
comma
id|PARITY_CRC16_PR1_CCITT
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
id|hdlc-&gt;open
op_assign
id|ppp_open
suffix:semicolon
id|hdlc-&gt;stop
op_assign
id|ppp_close
suffix:semicolon
id|hdlc-&gt;netif_rx
op_assign
id|ppp_rx
suffix:semicolon
id|hdlc-&gt;proto
op_assign
id|IF_PROTO_PPP
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|hdlc-&gt;xmit
suffix:semicolon
id|dev-&gt;hard_header
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_PPP
suffix:semicolon
id|dev-&gt;addr_len
op_assign
l_int|0
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
