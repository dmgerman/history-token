multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ircomm_ttp.c&n; * Version:       1.0&n; * Description:   Interface between IrCOMM and IrTTP&n; * Status:        Stable&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Jun  6 20:48:27 1999&n; * Modified at:   Mon Dec 13 11:35:13 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *     Copyright (c) 2000-2003 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/iriap.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
macro_line|#include &lt;net/irda/ircomm_event.h&gt;
macro_line|#include &lt;net/irda/ircomm_ttp.h&gt;
multiline_comment|/*&n; * Function ircomm_open_tsap (self)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_open_tsap
r_int
id|ircomm_open_tsap
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
)paren
(brace
id|notify_t
id|notify
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* Register callbacks */
id|irda_notify_init
c_func
(paren
op_amp
id|notify
)paren
suffix:semicolon
id|notify.data_indication
op_assign
id|ircomm_ttp_data_indication
suffix:semicolon
id|notify.connect_confirm
op_assign
id|ircomm_ttp_connect_confirm
suffix:semicolon
id|notify.connect_indication
op_assign
id|ircomm_ttp_connect_indication
suffix:semicolon
id|notify.flow_indication
op_assign
id|ircomm_ttp_flow_indication
suffix:semicolon
id|notify.disconnect_indication
op_assign
id|ircomm_ttp_disconnect_indication
suffix:semicolon
id|notify.instance
op_assign
id|self
suffix:semicolon
id|strlcpy
c_func
(paren
id|notify.name
comma
l_string|&quot;IrCOMM&quot;
comma
r_sizeof
(paren
id|notify.name
)paren
)paren
suffix:semicolon
id|self-&gt;tsap
op_assign
id|irttp_open_tsap
c_func
(paren
id|LSAP_ANY
comma
id|DEFAULT_INITIAL_CREDIT
comma
op_amp
id|notify
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|self-&gt;tsap
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%sfailed to allocate tsap&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|self-&gt;slsap_sel
op_assign
id|self-&gt;tsap-&gt;stsap_sel
suffix:semicolon
multiline_comment|/*&n;&t; *  Initialize the call-table for issuing commands&n;&t; */
id|self-&gt;issue.data_request
op_assign
id|ircomm_ttp_data_request
suffix:semicolon
id|self-&gt;issue.connect_request
op_assign
id|ircomm_ttp_connect_request
suffix:semicolon
id|self-&gt;issue.connect_response
op_assign
id|ircomm_ttp_connect_response
suffix:semicolon
id|self-&gt;issue.disconnect_request
op_assign
id|ircomm_ttp_disconnect_request
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_ttp_connect_request (self, userdata)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_ttp_connect_request
r_int
id|ircomm_ttp_connect_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|userdata
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t forget to refcount it - should be NULL anyway */
r_if
c_cond
(paren
id|userdata
)paren
(brace
id|skb_get
c_func
(paren
id|userdata
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|irttp_connect_request
c_func
(paren
id|self-&gt;tsap
comma
id|info-&gt;dlsap_sel
comma
id|info-&gt;saddr
comma
id|info-&gt;daddr
comma
l_int|NULL
comma
id|TTP_SAR_DISABLE
comma
id|userdata
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_ttp_connect_response (self, skb)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_ttp_connect_response
r_int
id|ircomm_ttp_connect_response
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
(brace
r_int
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t forget to refcount it - should be NULL anyway */
r_if
c_cond
(paren
id|userdata
)paren
(brace
id|skb_get
c_func
(paren
id|userdata
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|irttp_connect_response
c_func
(paren
id|self-&gt;tsap
comma
id|TTP_SAR_DISABLE
comma
id|userdata
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_ttp_data_request (self, userdata)&n; *&n; *    Send IrCOMM data to IrTTP layer. Currently we do not try to combine &n; *    control data with pure data, so they will be sent as separate frames. &n; *    Should not be a big problem though, since control frames are rare. But&n; *    some of them are sent after connection establishment, so this can &n; *    increase the latency a bit.&n; */
DECL|function|ircomm_ttp_data_request
r_int
id|ircomm_ttp_data_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|clen
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ASSERT
c_func
(paren
id|skb
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), clen=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|clen
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Insert clen field, currently we either send data only, or control&n;&t; * only frames, to make things easier and avoid queueing&n;&t; */
id|ASSERT
c_func
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
op_ge
id|IRCOMM_HEADER_SIZE
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t forget to refcount it - see ircomm_tty_do_softint() */
id|skb_get
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb_push
c_func
(paren
id|skb
comma
id|IRCOMM_HEADER_SIZE
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
id|clen
suffix:semicolon
id|ret
op_assign
id|irttp_data_request
c_func
(paren
id|self-&gt;tsap
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|ERROR
c_func
(paren
l_string|&quot;%s(), failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* irttp_data_request already free the packet */
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_ttp_data_indication (instance, sap, skb)&n; *&n; *    Incoming data&n; *&n; */
DECL|function|ircomm_ttp_data_indication
r_int
id|ircomm_ttp_data_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ircomm_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_cb
op_star
)paren
id|instance
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|skb
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ircomm_do_event
c_func
(paren
id|self
comma
id|IRCOMM_TTP_DATA_INDICATION
comma
id|skb
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Drop reference count - see ircomm_tty_data_indication(). */
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
DECL|function|ircomm_ttp_connect_confirm
r_void
id|ircomm_ttp_connect_confirm
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|qos_info
op_star
id|qos
comma
id|__u32
id|max_sdu_size
comma
id|__u8
id|max_header_size
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ircomm_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_cb
op_star
)paren
id|instance
suffix:semicolon
r_struct
id|ircomm_info
id|info
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|skb
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|qos
op_ne
l_int|NULL
comma
r_goto
id|out
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_sdu_size
op_ne
id|TTP_SAR_DISABLE
)paren
(brace
id|ERROR
c_func
(paren
l_string|&quot;%s(), SAR not allowed for IrCOMM!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|info.max_data_size
op_assign
id|irttp_get_max_seg_size
c_func
(paren
id|self-&gt;tsap
)paren
op_minus
id|IRCOMM_HEADER_SIZE
suffix:semicolon
id|info.max_header_size
op_assign
id|max_header_size
op_plus
id|IRCOMM_HEADER_SIZE
suffix:semicolon
id|info.qos
op_assign
id|qos
suffix:semicolon
id|ircomm_do_event
c_func
(paren
id|self
comma
id|IRCOMM_TTP_CONNECT_CONFIRM
comma
id|skb
comma
op_amp
id|info
)paren
suffix:semicolon
id|out
suffix:colon
multiline_comment|/* Drop reference count - see ircomm_tty_connect_confirm(). */
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_ttp_connect_indication (instance, sap, qos, max_sdu_size,&n; *                                         max_header_size, skb)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_ttp_connect_indication
r_void
id|ircomm_ttp_connect_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|qos_info
op_star
id|qos
comma
id|__u32
id|max_sdu_size
comma
id|__u8
id|max_header_size
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ircomm_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_cb
op_star
)paren
id|instance
suffix:semicolon
r_struct
id|ircomm_info
id|info
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|skb
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|qos
op_ne
l_int|NULL
comma
r_goto
id|out
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_sdu_size
op_ne
id|TTP_SAR_DISABLE
)paren
(brace
id|ERROR
c_func
(paren
l_string|&quot;%s(), SAR not allowed for IrCOMM!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|info.max_data_size
op_assign
id|irttp_get_max_seg_size
c_func
(paren
id|self-&gt;tsap
)paren
op_minus
id|IRCOMM_HEADER_SIZE
suffix:semicolon
id|info.max_header_size
op_assign
id|max_header_size
op_plus
id|IRCOMM_HEADER_SIZE
suffix:semicolon
id|info.qos
op_assign
id|qos
suffix:semicolon
id|ircomm_do_event
c_func
(paren
id|self
comma
id|IRCOMM_TTP_CONNECT_INDICATION
comma
id|skb
comma
op_amp
id|info
)paren
suffix:semicolon
id|out
suffix:colon
multiline_comment|/* Drop reference count - see ircomm_tty_connect_indication(). */
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_ttp_disconnect_request (self, userdata, info)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_ttp_disconnect_request
r_int
id|ircomm_ttp_disconnect_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|userdata
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* Don&squot;t forget to refcount it - should be NULL anyway */
r_if
c_cond
(paren
id|userdata
)paren
(brace
id|skb_get
c_func
(paren
id|userdata
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|irttp_disconnect_request
c_func
(paren
id|self-&gt;tsap
comma
id|userdata
comma
id|P_NORMAL
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_ttp_disconnect_indication (instance, sap, reason, skb)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_ttp_disconnect_indication
r_void
id|ircomm_ttp_disconnect_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
id|LM_REASON
id|reason
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ircomm_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_cb
op_star
)paren
id|instance
suffix:semicolon
r_struct
id|ircomm_info
id|info
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|info.reason
op_assign
id|reason
suffix:semicolon
id|ircomm_do_event
c_func
(paren
id|self
comma
id|IRCOMM_TTP_DISCONNECT_INDICATION
comma
id|skb
comma
op_amp
id|info
)paren
suffix:semicolon
multiline_comment|/* Drop reference count - see ircomm_tty_disconnect_indication(). */
r_if
c_cond
(paren
id|skb
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function ircomm_ttp_flow_indication (instance, sap, cmd)&n; *&n; *    Layer below is telling us to start or stop the flow of data&n; *&n; */
DECL|function|ircomm_ttp_flow_indication
r_void
id|ircomm_ttp_flow_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
id|LOCAL_FLOW
id|cmd
)paren
(brace
r_struct
id|ircomm_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_cb
op_star
)paren
id|instance
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;notify.flow_indication
)paren
id|self-&gt;notify
dot
id|flow_indication
c_func
(paren
id|self-&gt;notify.instance
comma
id|self
comma
id|cmd
)paren
suffix:semicolon
)brace
eof
