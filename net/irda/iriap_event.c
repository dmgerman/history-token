multiline_comment|/*********************************************************************&n; *&n; * Filename:      iriap_event.c&n; * Version:       0.1&n; * Description:   IAP Finite State Machine&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Thu Aug 21 00:02:07 1997&n; * Modified at:   Wed Mar  1 11:28:34 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *&n; *     Copyright (c) 1997, 1999-2000 Dag Brattli &lt;dagb@cs.uit.no&gt;,&n; *     All Rights Reserved.&n; *     Copyright (c) 2000-2003 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is&n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/iriap.h&gt;
macro_line|#include &lt;net/irda/iriap_event.h&gt;
r_static
r_void
id|state_s_disconnect
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_s_connecting
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_s_call
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_s_make_call
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_s_calling
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_s_outstanding
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_s_replying
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_s_wait_for_call
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_s_wait_active
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_r_disconnect
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_r_call
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_r_waiting
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_r_wait_active
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_r_receiving
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_r_execute
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_void
id|state_r_returning
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|variable|iriap_state
r_static
r_void
(paren
op_star
id|iriap_state
(braket
)braket
)paren
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
op_assign
(brace
multiline_comment|/* Client FSM */
id|state_s_disconnect
comma
id|state_s_connecting
comma
id|state_s_call
comma
multiline_comment|/* S-Call FSM */
id|state_s_make_call
comma
id|state_s_calling
comma
id|state_s_outstanding
comma
id|state_s_replying
comma
id|state_s_wait_for_call
comma
id|state_s_wait_active
comma
multiline_comment|/* Server FSM */
id|state_r_disconnect
comma
id|state_r_call
comma
multiline_comment|/* R-Connect FSM */
id|state_r_waiting
comma
id|state_r_wait_active
comma
id|state_r_receiving
comma
id|state_r_execute
comma
id|state_r_returning
comma
)brace
suffix:semicolon
DECL|function|iriap_next_client_state
r_void
id|iriap_next_client_state
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_STATE
id|state
)paren
(brace
id|IRDA_ASSERT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IAS_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|self-&gt;client_state
op_assign
id|state
suffix:semicolon
)brace
DECL|function|iriap_next_call_state
r_void
id|iriap_next_call_state
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_STATE
id|state
)paren
(brace
id|IRDA_ASSERT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IAS_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|self-&gt;call_state
op_assign
id|state
suffix:semicolon
)brace
DECL|function|iriap_next_server_state
r_void
id|iriap_next_server_state
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_STATE
id|state
)paren
(brace
id|IRDA_ASSERT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IAS_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|self-&gt;server_state
op_assign
id|state
suffix:semicolon
)brace
DECL|function|iriap_next_r_connect_state
r_void
id|iriap_next_r_connect_state
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_STATE
id|state
)paren
(brace
id|IRDA_ASSERT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IAS_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|self-&gt;r_connect_state
op_assign
id|state
suffix:semicolon
)brace
DECL|function|iriap_do_client_event
r_void
id|iriap_do_client_event
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_ASSERT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IAS_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
(paren
op_star
id|iriap_state
(braket
id|self-&gt;client_state
)braket
)paren
(paren
id|self
comma
id|event
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|iriap_do_call_event
r_void
id|iriap_do_call_event
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_ASSERT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IAS_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
(paren
op_star
id|iriap_state
(braket
id|self-&gt;call_state
)braket
)paren
(paren
id|self
comma
id|event
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|iriap_do_server_event
r_void
id|iriap_do_server_event
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_ASSERT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IAS_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
(paren
op_star
id|iriap_state
(braket
id|self-&gt;server_state
)braket
)paren
(paren
id|self
comma
id|event
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|iriap_do_r_connect_event
r_void
id|iriap_do_r_connect_event
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_ASSERT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IAS_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
(paren
op_star
id|iriap_state
(braket
id|self-&gt;r_connect_state
)braket
)paren
(paren
id|self
comma
id|event
comma
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function state_s_disconnect (event, skb)&n; *&n; *    S-Disconnect, The device has no LSAP connection to a particular&n; *    remote device.&n; */
DECL|function|state_s_disconnect
r_static
r_void
id|state_s_disconnect
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_ASSERT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IAS_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IAP_CALL_REQUEST_GVBC
suffix:colon
id|iriap_next_client_state
c_func
(paren
id|self
comma
id|S_CONNECTING
)paren
suffix:semicolon
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;request_skb
op_eq
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t forget to refcount it -&n;&t;&t; * see iriap_getvaluebyclass_request(). */
id|skb_get
c_func
(paren
id|skb
)paren
suffix:semicolon
id|self-&gt;request_skb
op_assign
id|skb
suffix:semicolon
id|iriap_connect_request
c_func
(paren
id|self
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IAP_LM_DISCONNECT_INDICATION
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), Unknown event %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|event
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function state_s_connecting (self, event, skb)&n; *&n; *    S-Connecting&n; *&n; */
DECL|function|state_s_connecting
r_static
r_void
id|state_s_connecting
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_ASSERT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IAS_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IAP_LM_CONNECT_CONFIRM
suffix:colon
multiline_comment|/*&n;&t;&t; *  Jump to S-Call FSM&n;&t;&t; */
id|iriap_do_call_event
c_func
(paren
id|self
comma
id|IAP_CALL_REQUEST
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* iriap_call_request(self, 0,0,0); */
id|iriap_next_client_state
c_func
(paren
id|self
comma
id|S_CALL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IAP_LM_DISCONNECT_INDICATION
suffix:colon
multiline_comment|/* Abort calls */
id|iriap_next_call_state
c_func
(paren
id|self
comma
id|S_MAKE_CALL
)paren
suffix:semicolon
id|iriap_next_client_state
c_func
(paren
id|self
comma
id|S_DISCONNECT
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), Unknown event %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|event
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function state_s_call (self, event, skb)&n; *&n; *    S-Call, The device can process calls to a specific remote&n; *    device. Whenever the LSAP connection is disconnected, this state&n; *    catches that event and clears up&n; */
DECL|function|state_s_call
r_static
r_void
id|state_s_call
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_ASSERT
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IAP_LM_DISCONNECT_INDICATION
suffix:colon
multiline_comment|/* Abort calls */
id|iriap_next_call_state
c_func
(paren
id|self
comma
id|S_MAKE_CALL
)paren
suffix:semicolon
id|iriap_next_client_state
c_func
(paren
id|self
comma
id|S_DISCONNECT
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;state_s_call: Unknown event %d&bslash;n&quot;
comma
id|event
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function state_s_make_call (event, skb)&n; *&n; *    S-Make-Call&n; *&n; */
DECL|function|state_s_make_call
r_static
r_void
id|state_s_make_call
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
id|IRDA_ASSERT
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IAP_CALL_REQUEST
suffix:colon
multiline_comment|/* Already refcounted - see state_s_disconnect() */
id|tx_skb
op_assign
id|self-&gt;request_skb
suffix:semicolon
id|self-&gt;request_skb
op_assign
l_int|NULL
suffix:semicolon
id|irlmp_data_request
c_func
(paren
id|self-&gt;lsap
comma
id|tx_skb
)paren
suffix:semicolon
id|iriap_next_call_state
c_func
(paren
id|self
comma
id|S_OUTSTANDING
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), Unknown event %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|event
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function state_s_calling (event, skb)&n; *&n; *    S-Calling&n; *&n; */
DECL|function|state_s_calling
r_static
r_void
id|state_s_calling
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), Not implemented&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function state_s_outstanding (event, skb)&n; *&n; *    S-Outstanding, The device is waiting for a response to a command&n; *&n; */
DECL|function|state_s_outstanding
r_static
r_void
id|state_s_outstanding
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_ASSERT
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IAP_RECV_F_LST
suffix:colon
multiline_comment|/*iriap_send_ack(self);*/
multiline_comment|/*LM_Idle_request(idle); */
id|iriap_next_call_state
c_func
(paren
id|self
comma
id|S_WAIT_FOR_CALL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), Unknown event %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|event
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function state_s_replying (event, skb)&n; *&n; *    S-Replying, The device is collecting a multiple part response&n; */
DECL|function|state_s_replying
r_static
r_void
id|state_s_replying
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), Not implemented&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function state_s_wait_for_call (event, skb)&n; *&n; *    S-Wait-for-Call&n; *&n; */
DECL|function|state_s_wait_for_call
r_static
r_void
id|state_s_wait_for_call
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), Not implemented&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function state_s_wait_active (event, skb)&n; *&n; *    S-Wait-Active&n; *&n; */
DECL|function|state_s_wait_active
r_static
r_void
id|state_s_wait_active
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), Not implemented&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/**************************************************************************&n; *&n; *  Server FSM&n; *&n; **************************************************************************/
multiline_comment|/*&n; * Function state_r_disconnect (self, event, skb)&n; *&n; *    LM-IAS server is disconnected (not processing any requests!)&n; *&n; */
DECL|function|state_r_disconnect
r_static
r_void
id|state_r_disconnect
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IAP_LM_CONNECT_INDICATION
suffix:colon
id|tx_skb
op_assign
id|dev_alloc_skb
c_func
(paren
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tx_skb
op_eq
l_int|NULL
)paren
(brace
id|IRDA_WARNING
c_func
(paren
l_string|&quot;%s: unable to malloc!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Reserve space for MUX_CONTROL and LAP header */
id|skb_reserve
c_func
(paren
id|tx_skb
comma
id|LMP_MAX_HEADER
)paren
suffix:semicolon
id|irlmp_connect_response
c_func
(paren
id|self-&gt;lsap
comma
id|tx_skb
)paren
suffix:semicolon
multiline_comment|/*LM_Idle_request(idle); */
id|iriap_next_server_state
c_func
(paren
id|self
comma
id|R_CALL
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  Jump to R-Connect FSM, we skip R-Waiting since we do not&n;&t;&t; *  care about LM_Idle_request()!&n;&t;&t; */
id|iriap_next_r_connect_state
c_func
(paren
id|self
comma
id|R_RECEIVING
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), unknown event %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|event
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function state_r_call (self, event, skb)&n; */
DECL|function|state_r_call
r_static
r_void
id|state_r_call
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IAP_LM_DISCONNECT_INDICATION
suffix:colon
multiline_comment|/* Abort call */
id|iriap_next_server_state
c_func
(paren
id|self
comma
id|R_DISCONNECT
)paren
suffix:semicolon
id|iriap_next_r_connect_state
c_func
(paren
id|self
comma
id|R_WAITING
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), unknown event!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  R-Connect FSM&n; */
multiline_comment|/*&n; * Function state_r_waiting (self, event, skb)&n; */
DECL|function|state_r_waiting
r_static
r_void
id|state_r_waiting
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), Not implemented&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
DECL|function|state_r_wait_active
r_static
r_void
id|state_r_wait_active
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), Not implemented&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function state_r_receiving (self, event, skb)&n; *&n; *    We are receiving a command&n; *&n; */
DECL|function|state_r_receiving
r_static
r_void
id|state_r_receiving
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IAP_RECV_F_LST
suffix:colon
id|iriap_next_r_connect_state
c_func
(paren
id|self
comma
id|R_EXECUTE
)paren
suffix:semicolon
id|iriap_call_indication
c_func
(paren
id|self
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), unknown event!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function state_r_execute (self, event, skb)&n; *&n; *    The server is processing the request&n; *&n; */
DECL|function|state_r_execute
r_static
r_void
id|state_r_execute
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
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
id|IRDA_ASSERT
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
id|IRDA_ASSERT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IAS_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IAP_CALL_RESPONSE
suffix:colon
multiline_comment|/*&n;&t;&t; *  Since we don&squot;t implement the Waiting state, we return&n;&t;&t; *  to state Receiving instead, DB.&n;&t;&t; */
id|iriap_next_r_connect_state
c_func
(paren
id|self
comma
id|R_RECEIVING
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t forget to refcount it - see&n;&t;&t; * iriap_getvaluebyclass_response(). */
id|skb_get
c_func
(paren
id|skb
)paren
suffix:semicolon
id|irlmp_data_request
c_func
(paren
id|self-&gt;lsap
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), unknown event!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|state_r_returning
r_static
r_void
id|state_r_returning
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|IRIAP_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), event=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|event
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IAP_RECV_F_LST
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
eof
