multiline_comment|/*&n; * Generic HDLC support routines for Linux&n; * X.25 support&n; *&n; * Copyright (C) 1999 - 2003 Krzysztof Halasa &lt;khc@pm.waw.pl&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License&n; * as published by the Free Software Foundation.&n; */
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
multiline_comment|/* These functions are callbacks called by LAPB layer */
DECL|function|x25_connect_disconnect
r_static
r_void
id|x25_connect_disconnect
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|reason
comma
r_int
id|code
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
l_int|1
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: out of memory&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ptr
op_assign
id|skb_put
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
id|code
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
id|ETH_P_X25
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
)brace
DECL|function|x25_connected
r_static
r_void
id|x25_connected
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|reason
)paren
(brace
id|x25_connect_disconnect
c_func
(paren
id|dev
comma
id|reason
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|x25_disconnected
r_static
r_void
id|x25_disconnected
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|reason
)paren
(brace
id|x25_connect_disconnect
c_func
(paren
id|dev
comma
id|reason
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|x25_data_indication
r_static
r_int
id|x25_data_indication
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_cow
c_func
(paren
id|skb
comma
l_int|1
)paren
)paren
r_return
id|NET_RX_DROP
suffix:semicolon
id|ptr
op_assign
id|skb-&gt;data
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
id|ETH_P_X25
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
r_return
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|x25_data_transmit
r_static
r_void
id|x25_data_transmit
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
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
id|hdlc
op_member_access_from_pointer
id|xmit
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* Ignore return value :-( */
)brace
DECL|function|x25_xmit
r_static
r_int
id|x25_xmit
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
multiline_comment|/* X.25 to LAPB */
r_switch
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Data to be transmitted */
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|lapb_data_request
c_func
(paren
id|dev
comma
id|skb
)paren
)paren
op_ne
id|LAPB_OK
)paren
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|lapb_connect_request
c_func
(paren
id|dev
)paren
)paren
op_ne
id|LAPB_OK
)paren
(brace
r_if
c_cond
(paren
id|result
op_eq
id|LAPB_CONNECTED
)paren
multiline_comment|/* Send connect confirm. msg to level 3 */
id|x25_connected
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: LAPB connect request &quot;
l_string|&quot;failed, error code = %i&bslash;n&quot;
comma
id|hdlc_to_name
c_func
(paren
id|hdlc
)paren
comma
id|result
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|lapb_disconnect_request
c_func
(paren
id|dev
)paren
)paren
op_ne
id|LAPB_OK
)paren
(brace
r_if
c_cond
(paren
id|result
op_eq
id|LAPB_NOTCONNECTED
)paren
multiline_comment|/* Send disconnect confirm. msg to level 3 */
id|x25_disconnected
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: LAPB disconnect request &quot;
l_string|&quot;failed, error code = %i&bslash;n&quot;
comma
id|hdlc_to_name
c_func
(paren
id|hdlc
)paren
comma
id|result
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* to be defined */
r_break
suffix:semicolon
)brace
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
DECL|function|x25_open
r_static
r_int
id|x25_open
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
(brace
r_struct
id|lapb_register_struct
id|cb
suffix:semicolon
r_int
id|result
suffix:semicolon
id|cb.connect_confirmation
op_assign
id|x25_connected
suffix:semicolon
id|cb.connect_indication
op_assign
id|x25_connected
suffix:semicolon
id|cb.disconnect_confirmation
op_assign
id|x25_disconnected
suffix:semicolon
id|cb.disconnect_indication
op_assign
id|x25_disconnected
suffix:semicolon
id|cb.data_indication
op_assign
id|x25_data_indication
suffix:semicolon
id|cb.data_transmit
op_assign
id|x25_data_transmit
suffix:semicolon
id|result
op_assign
id|lapb_register
c_func
(paren
id|hdlc_to_dev
c_func
(paren
id|hdlc
)paren
comma
op_amp
id|cb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|LAPB_OK
)paren
r_return
id|result
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|x25_close
r_static
r_void
id|x25_close
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
(brace
id|lapb_unregister
c_func
(paren
id|hdlc_to_dev
c_func
(paren
id|hdlc
)paren
)paren
suffix:semicolon
)brace
DECL|function|x25_rx
r_static
r_int
id|x25_rx
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|hdlc_device
op_star
id|hdlc
op_assign
id|dev_to_hdlc
c_func
(paren
id|skb-&gt;dev
)paren
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
(brace
id|hdlc-&gt;stats.rx_dropped
op_increment
suffix:semicolon
r_return
id|NET_RX_DROP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lapb_data_received
c_func
(paren
id|skb-&gt;dev
comma
id|skb
)paren
op_eq
id|LAPB_OK
)paren
r_return
id|NET_RX_SUCCESS
suffix:semicolon
id|hdlc-&gt;stats.rx_errors
op_increment
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_RX_DROP
suffix:semicolon
)brace
DECL|function|hdlc_x25_ioctl
r_int
id|hdlc_x25_ioctl
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
id|IF_PROTO_X25
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* return protocol only, no settable parameters */
r_case
id|IF_PROTO_X25
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
id|hdlc-&gt;proto.open
op_assign
id|x25_open
suffix:semicolon
id|hdlc-&gt;proto.close
op_assign
id|x25_close
suffix:semicolon
id|hdlc-&gt;proto.netif_rx
op_assign
id|x25_rx
suffix:semicolon
id|hdlc-&gt;proto.type_trans
op_assign
l_int|NULL
suffix:semicolon
id|hdlc-&gt;proto.id
op_assign
id|IF_PROTO_X25
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|x25_xmit
suffix:semicolon
id|dev-&gt;hard_header
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_X25
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
