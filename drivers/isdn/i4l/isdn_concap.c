multiline_comment|/* $Id: isdn_concap.c,v 1.8.6.1 2001/09/23 22:24:31 kai Exp $&n; * &n; * Linux ISDN subsystem, protocol encapsulation&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
multiline_comment|/* Stuff to support the concap_proto by isdn4linux. isdn4linux - specific&n; * stuff goes here. Stuff that depends only on the concap protocol goes to&n; * another -- protocol specific -- source file.&n; *&n; */
macro_line|#include &lt;linux/isdn.h&gt;
macro_line|#include &quot;isdn_x25iface.h&quot;
macro_line|#include &quot;isdn_net.h&quot;
macro_line|#include &lt;linux/concap.h&gt;
macro_line|#include &quot;isdn_concap.h&quot;
multiline_comment|/* The following set of device service operations are for encapsulation&n;   protocols that require for reliable datalink semantics. That means:&n;&n;   - before any data is to be submitted the connection must explicitly&n;     be set up.&n;   - after the successful set up of the connection is signalled the&n;     connection is considered to be reliably up.&n;&n;   Auto-dialing ist not compatible with this requirements. Thus, auto-dialing &n;   is completely bypassed.&n;&n;   It might be possible to implement a (non standardized) datalink protocol&n;   that provides a reliable data link service while using some auto dialing&n;   mechanism. Such a protocol would need an auxiliary channel (i.e. user-user-&n;   signaling on the D-channel) while the B-channel is down.&n;   */
DECL|function|isdn_concap_dl_data_req
r_int
id|isdn_concap_dl_data_req
c_func
(paren
r_struct
id|concap_proto
op_star
id|concap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|net_device
op_star
id|ndev
op_assign
id|concap
op_member_access_from_pointer
id|net_dev
suffix:semicolon
id|isdn_net_dev
op_star
id|nd
op_assign
(paren
(paren
id|isdn_net_local
op_star
)paren
id|ndev-&gt;priv
)paren
op_member_access_from_pointer
id|netdev
suffix:semicolon
id|isdn_net_local
op_star
id|lp
op_assign
id|isdn_net_get_locked_lp
c_func
(paren
id|nd
)paren
suffix:semicolon
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_concap_dl_data_req: %s &bslash;n&quot;
comma
id|concap-&gt;net_dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lp
)paren
(brace
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_concap_dl_data_req: %s : isdn_net_send_skb returned %d&bslash;n&quot;
comma
id|concap
op_member_access_from_pointer
id|net_dev
op_member_access_from_pointer
id|name
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|lp-&gt;huptimer
op_assign
l_int|0
suffix:semicolon
id|isdn_net_writebuf_skb
c_func
(paren
id|lp
comma
id|skb
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|lp-&gt;xmit_lock
)paren
suffix:semicolon
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_concap_dl_data_req: %s : isdn_net_send_skb returned %d&bslash;n&quot;
comma
id|concap
op_member_access_from_pointer
id|net_dev
op_member_access_from_pointer
id|name
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|isdn_concap_dl_connect_req
r_int
id|isdn_concap_dl_connect_req
c_func
(paren
r_struct
id|concap_proto
op_star
id|concap
)paren
(brace
r_struct
id|net_device
op_star
id|ndev
op_assign
id|concap
op_member_access_from_pointer
id|net_dev
suffix:semicolon
id|isdn_net_local
op_star
id|lp
op_assign
(paren
id|isdn_net_local
op_star
)paren
id|ndev-&gt;priv
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_concap_dl_connect_req: %s &bslash;n&quot;
comma
id|ndev
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
multiline_comment|/* dial ... */
id|ret
op_assign
id|isdn_net_dial_req
c_func
(paren
id|lp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|IX25DEBUG
c_func
(paren
l_string|&quot;dialing failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|isdn_concap_dl_disconn_req
r_int
id|isdn_concap_dl_disconn_req
c_func
(paren
r_struct
id|concap_proto
op_star
id|concap
)paren
(brace
id|IX25DEBUG
c_func
(paren
l_string|&quot;isdn_concap_dl_disconn_req: %s &bslash;n&quot;
comma
id|concap
op_member_access_from_pointer
id|net_dev
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|isdn_net_hangup
c_func
(paren
id|concap
op_member_access_from_pointer
id|net_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|isdn_concap_reliable_dl_dops
r_struct
id|concap_device_ops
id|isdn_concap_reliable_dl_dops
op_assign
(brace
op_amp
id|isdn_concap_dl_data_req
comma
op_amp
id|isdn_concap_dl_connect_req
comma
op_amp
id|isdn_concap_dl_disconn_req
)brace
suffix:semicolon
DECL|variable|isdn_concap_demand_dial_dops
r_struct
id|concap_device_ops
id|isdn_concap_demand_dial_dops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* set this first entry to something like &amp;isdn_net_start_xmit,&n;&t;&t; but the entry part of the current isdn_net_start_xmit must be&n;&t;&t; separated first. */
multiline_comment|/* no connection control for demand dial semantics */
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
multiline_comment|/* The following should better go into a dedicated source file such that&n;   this sourcefile does not need to include any protocol specific header&n;   files. For now:&n;   */
DECL|function|isdn_concap_new
r_struct
id|concap_proto
op_star
id|isdn_concap_new
c_func
(paren
r_int
id|encap
)paren
(brace
r_switch
c_cond
(paren
id|encap
)paren
(brace
r_case
id|ISDN_NET_ENCAP_X25IFACE
suffix:colon
r_return
id|isdn_x25iface_proto_new
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|isdn_x25_cleanup
r_void
id|isdn_x25_cleanup
c_func
(paren
id|isdn_net_dev
op_star
id|p
)paren
(brace
id|isdn_net_local
op_star
id|lp
op_assign
op_amp
id|p-&gt;local
suffix:semicolon
r_struct
id|concap_proto
op_star
id|cprot
op_assign
id|p
op_member_access_from_pointer
id|cprot
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* delete old encapsulation protocol if present ... */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* avoid races with incoming events trying to&n;&t;&t;  call cprot-&gt;pops methods */
r_if
c_cond
(paren
id|cprot
op_logical_and
id|cprot
op_member_access_from_pointer
id|pops
)paren
(brace
id|cprot
op_member_access_from_pointer
id|pops
op_member_access_from_pointer
id|proto_del
(paren
id|cprot
)paren
suffix:semicolon
)brace
id|p
op_member_access_from_pointer
id|cprot
op_assign
l_int|NULL
suffix:semicolon
id|lp
op_member_access_from_pointer
id|dops
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|isdn_x25_open
r_void
id|isdn_x25_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|isdn_net_local
op_star
id|lp
op_assign
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/* ... ,  prepare for configuration of new one ... */
r_switch
c_cond
(paren
id|lp-&gt;p_encap
)paren
(brace
r_case
id|ISDN_NET_ENCAP_X25IFACE
suffix:colon
id|lp
op_member_access_from_pointer
id|dops
op_assign
op_amp
id|isdn_concap_reliable_dl_dops
suffix:semicolon
)brace
multiline_comment|/* ... and allocate new one ... */
id|p
op_member_access_from_pointer
id|cprot
op_assign
id|isdn_concap_new
c_func
(paren
id|cfg
op_member_access_from_pointer
id|p_encap
)paren
suffix:semicolon
multiline_comment|/* p -&gt; cprot == NULL now if p_encap is not supported&n;&t;   by means of the concap_proto mechanism */
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;cprot
)paren
r_return
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Avoid glitch on writes to CMD regs */
r_if
c_cond
(paren
id|p
op_member_access_from_pointer
id|cprot
op_member_access_from_pointer
id|pops
op_logical_and
id|lp
op_member_access_from_pointer
id|dops
)paren
(brace
id|p
op_member_access_from_pointer
id|cprot
op_member_access_from_pointer
id|pops
op_member_access_from_pointer
id|restart
(paren
id|p
op_member_access_from_pointer
id|cprot
comma
id|dev
comma
id|lp
op_member_access_from_pointer
id|dops
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|isdn_x25_close
r_void
id|isdn_x25_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|concap_proto
op_star
id|cprot
op_assign
(paren
(paren
id|isdn_net_local
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|netdev
op_member_access_from_pointer
id|cprot
suffix:semicolon
r_if
c_cond
(paren
id|cprot
op_logical_and
id|cprot
op_member_access_from_pointer
id|pops
)paren
(brace
id|cprot
op_member_access_from_pointer
id|pops
op_member_access_from_pointer
id|close
c_func
(paren
id|cprot
)paren
suffix:semicolon
)brace
)brace
DECL|function|isdn_x25_connected
r_static
r_void
id|isdn_x25_connected
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
r_struct
id|concap_proto
op_star
id|cprot
op_assign
id|lp
op_member_access_from_pointer
id|netdev
op_member_access_from_pointer
id|cprot
suffix:semicolon
r_struct
id|concap_proto_ops
op_star
id|pops
op_assign
id|cprot
ques
c_cond
id|cprot
op_member_access_from_pointer
id|pops
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* try if there are generic concap receiver routines */
r_if
c_cond
(paren
id|pops
)paren
r_if
c_cond
(paren
id|pops-&gt;connect_ind
)paren
(brace
id|pops
op_member_access_from_pointer
id|connect_ind
c_func
(paren
id|cprot
)paren
suffix:semicolon
)brace
id|isdn_net_device_wake_queue
c_func
(paren
id|lp
)paren
suffix:semicolon
)brace
DECL|function|isdn_x25_disconnected
r_static
r_void
id|isdn_x25_disconnected
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
r_struct
id|concap_proto
op_star
id|cprot
op_assign
id|lp
op_member_access_from_pointer
id|netdev
op_member_access_from_pointer
id|cprot
suffix:semicolon
r_struct
id|concap_proto_ops
op_star
id|pops
op_assign
id|cprot
ques
c_cond
id|cprot
op_member_access_from_pointer
id|pops
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* try if there are generic encap protocol&n;&t;   receiver routines and signal the closure of&n;&t;   the link */
r_if
c_cond
(paren
id|pops
op_logical_and
id|pops
op_member_access_from_pointer
id|disconn_ind
)paren
(brace
id|pops
op_member_access_from_pointer
id|disconn_ind
c_func
(paren
id|cprot
)paren
suffix:semicolon
)brace
)brace
DECL|function|isdn_x25_start_xmit
r_int
id|isdn_x25_start_xmit
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
multiline_comment|/* At this point hard_start_xmit() passes control to the encapsulation&n;   protocol (if present).&n;   For X.25 auto-dialing is completly bypassed because:&n;   - It does not conform with the semantics of a reliable datalink&n;     service as needed by X.25 PLP.&n;   - I don&squot;t want that the interface starts dialing when the network layer&n;     sends a message which requests to disconnect the lapb link (or if it&n;     sends any other message not resulting in data transmission).&n;   Instead, dialing will be initiated by the encapsulation protocol entity&n;   when a dl_establish request is received from the upper layer.&n;*/
id|isdn_net_local
op_star
id|lp
op_assign
(paren
id|isdn_net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|concap_proto
op_star
id|cprot
op_assign
id|lp
op_member_access_from_pointer
id|netdev
op_member_access_from_pointer
id|cprot
suffix:semicolon
r_int
id|ret
op_assign
id|cprot
op_member_access_from_pointer
id|pops
op_member_access_from_pointer
id|encap_and_xmit
(paren
id|cprot
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|isdn_x25_receive
id|isdn_x25_receive
c_func
(paren
id|isdn_net_dev
op_star
id|p
comma
id|isdn_net_local
op_star
id|olp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|isdn_net_local
op_star
id|lp
op_assign
op_amp
id|p-&gt;local
suffix:semicolon
r_struct
id|concap_proto
op_star
id|cprot
op_assign
id|lp
op_member_access_from_pointer
id|netdev
op_member_access_from_pointer
id|cprot
suffix:semicolon
multiline_comment|/* try if there are generic sync_device receiver routines */
r_if
c_cond
(paren
id|cprot
)paren
r_if
c_cond
(paren
id|cprot
op_member_access_from_pointer
id|pops
)paren
r_if
c_cond
(paren
id|cprot
op_member_access_from_pointer
id|pops
op_member_access_from_pointer
id|data_ind
)paren
(brace
id|cprot
op_member_access_from_pointer
id|pops
op_member_access_from_pointer
id|data_ind
c_func
(paren
id|cprot
comma
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|isdn_x25_realrm
r_void
id|isdn_x25_realrm
c_func
(paren
id|isdn_net_dev
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p
op_member_access_from_pointer
id|cprot
op_logical_and
id|p
op_member_access_from_pointer
id|cprot
op_member_access_from_pointer
id|pops
)paren
(brace
id|p
op_member_access_from_pointer
id|cprot
op_member_access_from_pointer
id|pops
op_member_access_from_pointer
id|proto_del
(paren
id|p
op_member_access_from_pointer
id|cprot
)paren
suffix:semicolon
)brace
)brace
DECL|variable|isdn_x25_ops
r_struct
id|isdn_netif_ops
id|isdn_x25_ops
op_assign
(brace
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
id|ARPHRD_X25
comma
dot
id|receive
op_assign
id|isdn_x25_receive
comma
dot
id|connected
op_assign
id|isdn_x25_connected
comma
dot
id|disconnected
op_assign
id|isdn_x25_disconnected
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_ISDN_X25 */
eof
