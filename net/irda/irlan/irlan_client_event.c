multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlan_client_event.c&n; * Version:       0.9&n; * Description:   IrLAN client state machine&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Aug 31 20:14:37 1997&n; * Modified at:   Sun Dec 26 21:52:24 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/timer.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt;
macro_line|#include &lt;net/irda/iriap.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
macro_line|#include &lt;net/irda/irlan_common.h&gt;
macro_line|#include &lt;net/irda/irlan_client.h&gt;
macro_line|#include &lt;net/irda/irlan_event.h&gt;
r_static
r_int
id|irlan_client_state_idle
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_int
id|irlan_client_state_query
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_int
id|irlan_client_state_conn
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_int
id|irlan_client_state_info
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_int
id|irlan_client_state_media
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_int
id|irlan_client_state_open
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_int
id|irlan_client_state_wait
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_int
id|irlan_client_state_arb
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_int
id|irlan_client_state_data
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_int
id|irlan_client_state_close
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_int
id|irlan_client_state_sync
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|variable|state
r_static
r_int
(paren
op_star
id|state
(braket
)braket
)paren
(paren
r_struct
id|irlan_cb
op_star
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
)paren
op_assign
(brace
id|irlan_client_state_idle
comma
id|irlan_client_state_query
comma
id|irlan_client_state_conn
comma
id|irlan_client_state_info
comma
id|irlan_client_state_media
comma
id|irlan_client_state_open
comma
id|irlan_client_state_wait
comma
id|irlan_client_state_arb
comma
id|irlan_client_state_data
comma
id|irlan_client_state_close
comma
id|irlan_client_state_sync
)brace
suffix:semicolon
DECL|function|irlan_do_client_event
r_void
id|irlan_do_client_event
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
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
id|IRLAN_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
(paren
op_star
id|state
(braket
id|self-&gt;client.state
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
multiline_comment|/*&n; * Function irlan_client_state_idle (event, skb, info)&n; *&n; *    IDLE, We are waiting for an indication that there is a provider&n; *    available.&n; */
DECL|function|irlan_client_state_idle
r_static
r_int
id|irlan_client_state_idle
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLAN_MAGIC
comma
r_return
op_minus
l_int|1
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
id|IRLAN_DISCOVERY_INDICATION
suffix:colon
r_if
c_cond
(paren
id|self-&gt;client.iriap
)paren
(brace
id|IRDA_WARNING
c_func
(paren
l_string|&quot;%s(), busy with a previous query&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|self-&gt;client.iriap
op_assign
id|iriap_open
c_func
(paren
id|LSAP_ANY
comma
id|IAS_CLIENT
comma
id|self
comma
id|irlan_client_get_value_confirm
)paren
suffix:semicolon
multiline_comment|/* Get some values from peer IAS */
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_QUERY
)paren
suffix:semicolon
id|iriap_getvaluebyclass_request
c_func
(paren
id|self-&gt;client.iriap
comma
id|self-&gt;saddr
comma
id|self-&gt;daddr
comma
l_string|&quot;IrLAN&quot;
comma
l_string|&quot;IrDA:TinyTP:LsapSel&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_WATCHDOG_TIMEOUT
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), IRLAN_WATCHDOG_TIMEOUT&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|4
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
r_if
c_cond
(paren
id|skb
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
)brace
multiline_comment|/*&n; * Function irlan_client_state_query (event, skb, info)&n; *&n; *    QUERY, We have queryed the remote IAS and is ready to connect&n; *    to provider, just waiting for the confirm.&n; *&n; */
DECL|function|irlan_client_state_query
r_static
r_int
id|irlan_client_state_query
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLAN_MAGIC
comma
r_return
op_minus
l_int|1
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
id|IRLAN_IAS_PROVIDER_AVAIL
suffix:colon
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;dtsap_sel_ctrl
op_ne
l_int|0
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|self-&gt;client.open_retries
op_assign
l_int|0
suffix:semicolon
id|irttp_connect_request
c_func
(paren
id|self-&gt;client.tsap_ctrl
comma
id|self-&gt;dtsap_sel_ctrl
comma
id|self-&gt;saddr
comma
id|self-&gt;daddr
comma
l_int|NULL
comma
id|IRLAN_MTU
comma
l_int|NULL
)paren
suffix:semicolon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_CONN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_IAS_PROVIDER_NOT_AVAIL
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), IAS_PROVIDER_NOT_AVAIL&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_IDLE
)paren
suffix:semicolon
multiline_comment|/* Give the client a kick! */
r_if
c_cond
(paren
(paren
id|self-&gt;provider.access_type
op_eq
id|ACCESS_PEER
)paren
op_logical_and
(paren
id|self-&gt;provider.state
op_ne
id|IRLAN_IDLE
)paren
)paren
id|irlan_client_wakeup
c_func
(paren
id|self
comma
id|self-&gt;saddr
comma
id|self-&gt;daddr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_LMP_DISCONNECT
suffix:colon
r_case
id|IRLAN_LAP_DISCONNECT
suffix:colon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_IDLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_WATCHDOG_TIMEOUT
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), IRLAN_WATCHDOG_TIMEOUT&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
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
r_if
c_cond
(paren
id|skb
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
)brace
multiline_comment|/*&n; * Function irlan_client_state_conn (event, skb, info)&n; *&n; *    CONN, We have connected to a provider but has not issued any&n; *    commands yet.&n; *&n; */
DECL|function|irlan_client_state_conn
r_static
r_int
id|irlan_client_state_conn
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRLAN_CONNECT_COMPLETE
suffix:colon
multiline_comment|/* Send getinfo cmd */
id|irlan_get_provider_info
c_func
(paren
id|self
)paren
suffix:semicolon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_INFO
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_LMP_DISCONNECT
suffix:colon
r_case
id|IRLAN_LAP_DISCONNECT
suffix:colon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_IDLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_WATCHDOG_TIMEOUT
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), IRLAN_WATCHDOG_TIMEOUT&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
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
r_if
c_cond
(paren
id|skb
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
)brace
multiline_comment|/*&n; * Function irlan_client_state_info (self, event, skb, info)&n; *&n; *    INFO, We have issued a GetInfo command and is awaiting a reply.&n; */
DECL|function|irlan_client_state_info
r_static
r_int
id|irlan_client_state_info
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRLAN_DATA_INDICATION
suffix:colon
id|IRDA_ASSERT
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
id|irlan_client_parse_response
c_func
(paren
id|self
comma
id|skb
)paren
suffix:semicolon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_MEDIA
)paren
suffix:semicolon
id|irlan_get_media_char
c_func
(paren
id|self
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_LMP_DISCONNECT
suffix:colon
r_case
id|IRLAN_LAP_DISCONNECT
suffix:colon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_IDLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_WATCHDOG_TIMEOUT
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), IRLAN_WATCHDOG_TIMEOUT&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
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
r_if
c_cond
(paren
id|skb
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
)brace
multiline_comment|/*&n; * Function irlan_client_state_media (self, event, skb, info)&n; *&n; *    MEDIA, The irlan_client has issued a GetMedia command and is awaiting a&n; *    reply.&n; *&n; */
DECL|function|irlan_client_state_media
r_static
r_int
id|irlan_client_state_media
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRLAN_DATA_INDICATION
suffix:colon
id|irlan_client_parse_response
c_func
(paren
id|self
comma
id|skb
)paren
suffix:semicolon
id|irlan_open_data_channel
c_func
(paren
id|self
)paren
suffix:semicolon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_OPEN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_LMP_DISCONNECT
suffix:colon
r_case
id|IRLAN_LAP_DISCONNECT
suffix:colon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_IDLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_WATCHDOG_TIMEOUT
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), IRLAN_WATCHDOG_TIMEOUT&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
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
r_if
c_cond
(paren
id|skb
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
)brace
multiline_comment|/*&n; * Function irlan_client_state_open (self, event, skb, info)&n; *&n; *    OPEN, The irlan_client has issued a OpenData command and is awaiting a&n; *    reply&n; *&n; */
DECL|function|irlan_client_state_open
r_static
r_int
id|irlan_client_state_open
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|qos_info
id|qos
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
id|IRDA_ASSERT
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRLAN_DATA_INDICATION
suffix:colon
id|irlan_client_parse_response
c_func
(paren
id|self
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  Check if we have got the remote TSAP for data &n;&t;&t; *  communications&n;&t;&t; */
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;dtsap_sel_data
op_ne
l_int|0
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Check which access type we are dealing with */
r_switch
c_cond
(paren
id|self-&gt;client.access_type
)paren
(brace
r_case
id|ACCESS_PEER
suffix:colon
r_if
c_cond
(paren
id|self-&gt;provider.state
op_eq
id|IRLAN_OPEN
)paren
(brace
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_ARB
)paren
suffix:semicolon
id|irlan_do_client_event
c_func
(paren
id|self
comma
id|IRLAN_CHECK_CON_ARB
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_WAIT
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACCESS_DIRECT
suffix:colon
r_case
id|ACCESS_HOSTED
suffix:colon
id|qos.link_disc_time.bits
op_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* 3 secs */
id|irttp_connect_request
c_func
(paren
id|self-&gt;tsap_data
comma
id|self-&gt;dtsap_sel_data
comma
id|self-&gt;saddr
comma
id|self-&gt;daddr
comma
op_amp
id|qos
comma
id|IRLAN_MTU
comma
l_int|NULL
)paren
suffix:semicolon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), unknown access type!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IRLAN_LMP_DISCONNECT
suffix:colon
r_case
id|IRLAN_LAP_DISCONNECT
suffix:colon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_IDLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_WATCHDOG_TIMEOUT
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), IRLAN_WATCHDOG_TIMEOUT&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
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
r_if
c_cond
(paren
id|skb
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
)brace
multiline_comment|/*&n; * Function irlan_client_state_wait (self, event, skb, info)&n; *&n; *    WAIT, The irlan_client is waiting for the local provider to enter the&n; *    provider OPEN state.&n; *&n; */
DECL|function|irlan_client_state_wait
r_static
r_int
id|irlan_client_state_wait
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRLAN_PROVIDER_SIGNAL
suffix:colon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_ARB
)paren
suffix:semicolon
id|irlan_do_client_event
c_func
(paren
id|self
comma
id|IRLAN_CHECK_CON_ARB
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_LMP_DISCONNECT
suffix:colon
r_case
id|IRLAN_LAP_DISCONNECT
suffix:colon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_IDLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_WATCHDOG_TIMEOUT
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), IRLAN_WATCHDOG_TIMEOUT&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
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
r_if
c_cond
(paren
id|skb
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
)brace
DECL|function|irlan_client_state_arb
r_static
r_int
id|irlan_client_state_arb
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|qos_info
id|qos
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
id|IRDA_ASSERT
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRLAN_CHECK_CON_ARB
suffix:colon
r_if
c_cond
(paren
id|self-&gt;client.recv_arb_val
op_eq
id|self-&gt;provider.send_arb_val
)paren
(brace
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_CLOSE
)paren
suffix:semicolon
id|irlan_close_data_channel
c_func
(paren
id|self
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|self-&gt;client.recv_arb_val
OL
id|self-&gt;provider.send_arb_val
)paren
(brace
id|qos.link_disc_time.bits
op_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* 3 secs */
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_DATA
)paren
suffix:semicolon
id|irttp_connect_request
c_func
(paren
id|self-&gt;tsap_data
comma
id|self-&gt;dtsap_sel_data
comma
id|self-&gt;saddr
comma
id|self-&gt;daddr
comma
op_amp
id|qos
comma
id|IRLAN_MTU
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|self-&gt;client.recv_arb_val
OG
id|self-&gt;provider.send_arb_val
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), lost the battle :-(&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IRLAN_DATA_CONNECT_INDICATION
suffix:colon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_LMP_DISCONNECT
suffix:colon
r_case
id|IRLAN_LAP_DISCONNECT
suffix:colon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_IDLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_WATCHDOG_TIMEOUT
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), IRLAN_WATCHDOG_TIMEOUT&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
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
r_if
c_cond
(paren
id|skb
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
)brace
multiline_comment|/*&n; * Function irlan_client_state_data (self, event, skb, info)&n; *&n; *    DATA, The data channel is connected, allowing data transfers between&n; *    the local and remote machines.&n; *&n; */
DECL|function|irlan_client_state_data
r_static
r_int
id|irlan_client_state_data
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
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
id|IRDA_ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRLAN_MAGIC
comma
r_return
op_minus
l_int|1
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
id|IRLAN_DATA_INDICATION
suffix:colon
id|irlan_client_parse_response
c_func
(paren
id|self
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRLAN_LMP_DISCONNECT
suffix:colon
multiline_comment|/* FALLTHROUGH */
r_case
id|IRLAN_LAP_DISCONNECT
suffix:colon
id|irlan_next_client_state
c_func
(paren
id|self
comma
id|IRLAN_IDLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|2
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
r_if
c_cond
(paren
id|skb
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
)brace
multiline_comment|/*&n; * Function irlan_client_state_close (self, event, skb, info)&n; *&n; *    &n; *&n; */
DECL|function|irlan_client_state_close
r_static
r_int
id|irlan_client_state_close
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
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
l_int|2
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
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
)brace
multiline_comment|/*&n; * Function irlan_client_state_sync (self, event, skb, info)&n; *&n; *    &n; *&n; */
DECL|function|irlan_client_state_sync
r_static
r_int
id|irlan_client_state_sync
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|IRLAN_EVENT
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
l_int|2
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
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
)brace
eof
