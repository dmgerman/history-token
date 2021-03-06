multiline_comment|/*&n; * llc_output.c - LLC minimal output path&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001-2003 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License version 2 as published by the Free Software&n; * Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License version 2 for more details.&n; */
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/if_tr.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/llc.h&gt;
macro_line|#include &lt;net/llc_pdu.h&gt;
multiline_comment|/**&n; *&t;llc_mac_hdr_init - fills MAC header fields&n; *&t;@skb: Address of the frame to initialize its MAC header&n; *&t;@sa: The MAC source address&n; *&t;@da: The MAC destination address&n; *&n; *&t;Fills MAC header fields, depending on MAC type. Returns 0, If MAC type&n; *&t;is a valid type and initialization completes correctly 1, otherwise.&n; */
DECL|function|llc_mac_hdr_init
r_int
id|llc_mac_hdr_init
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_char
op_star
id|sa
comma
r_int
r_char
op_star
id|da
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;dev-&gt;type
)paren
(brace
macro_line|#ifdef CONFIG_TR
r_case
id|ARPHRD_IEEE802_TR
suffix:colon
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|skb-&gt;dev
suffix:semicolon
r_struct
id|trh_hdr
op_star
id|trh
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
op_star
id|trh
)paren
)paren
suffix:semicolon
id|trh
op_assign
id|tr_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
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
id|sa
)paren
id|memcpy
c_func
(paren
id|trh-&gt;saddr
comma
id|sa
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_else
id|memset
c_func
(paren
id|trh-&gt;saddr
comma
l_int|0
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|da
)paren
(brace
id|memcpy
c_func
(paren
id|trh-&gt;daddr
comma
id|da
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
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
macro_line|#endif
r_case
id|ARPHRD_ETHER
suffix:colon
r_case
id|ARPHRD_LOOPBACK
suffix:colon
(brace
r_int
r_int
id|len
op_assign
id|skb-&gt;len
suffix:semicolon
r_struct
id|ethhdr
op_star
id|eth
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
op_star
id|eth
)paren
)paren
suffix:semicolon
id|eth
op_assign
id|eth_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|eth-&gt;h_proto
op_assign
id|htons
c_func
(paren
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|eth-&gt;h_dest
comma
id|da
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|eth-&gt;h_source
comma
id|sa
comma
id|ETH_ALEN
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;device type not supported: %d&bslash;n&quot;
comma
id|skb-&gt;dev-&gt;type
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_build_and_send_ui_pkt - unitdata request interface for upper layers&n; *&t;@sap: sap to use&n; *&t;@skb: packet to send&n; *&t;@dmac: destination mac address&n; *&t;@dsap: destination sap&n; *&n; *&t;Upper layers calls this function when upper layer wants to send data&n; *&t;using connection-less mode communication (UI pdu).&n; *&n; *&t;Accept data frame from network layer to be sent using connection-&n; *&t;less mode communication; timeout/retries handled by network layer;&n; *&t;package primitive as an event and send to SAP event handler&n; */
DECL|function|llc_build_and_send_ui_pkt
r_int
id|llc_build_and_send_ui_pkt
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_char
op_star
id|dmac
comma
r_int
r_char
id|dsap
)paren
(brace
r_int
id|rc
suffix:semicolon
id|llc_pdu_header_init
c_func
(paren
id|skb
comma
id|LLC_PDU_TYPE_U
comma
id|sap-&gt;laddr.lsap
comma
id|dsap
comma
id|LLC_PDU_CMD
)paren
suffix:semicolon
id|llc_pdu_init_as_ui_cmd
c_func
(paren
id|skb
)paren
suffix:semicolon
id|rc
op_assign
id|llc_mac_hdr_init
c_func
(paren
id|skb
comma
id|skb-&gt;dev-&gt;dev_addr
comma
id|dmac
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|rc
op_assign
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|variable|llc_mac_hdr_init
id|EXPORT_SYMBOL
c_func
(paren
id|llc_mac_hdr_init
)paren
suffix:semicolon
DECL|variable|llc_build_and_send_ui_pkt
id|EXPORT_SYMBOL
c_func
(paren
id|llc_build_and_send_ui_pkt
)paren
suffix:semicolon
eof
