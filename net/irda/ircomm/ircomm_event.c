multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ircomm_event.c&n; * Version:       1.0&n; * Description:   IrCOMM layer state machine&n; * Status:        Stable&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Jun  6 20:33:11 1999&n; * Modified at:   Sun Dec 12 13:44:32 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/iriap.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
macro_line|#include &lt;net/irda/irias_object.h&gt;
macro_line|#include &lt;net/irda/ircomm_core.h&gt;
macro_line|#include &lt;net/irda/ircomm_event.h&gt;
r_static
r_int
id|ircomm_state_idle
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|ircomm_state_waiti
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|ircomm_state_waitr
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|ircomm_state_conn
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
suffix:semicolon
DECL|variable|ircomm_state
r_char
op_star
id|ircomm_state
(braket
)braket
op_assign
(brace
l_string|&quot;IRCOMM_IDLE&quot;
comma
l_string|&quot;IRCOMM_WAITI&quot;
comma
l_string|&quot;IRCOMM_WAITR&quot;
comma
l_string|&quot;IRCOMM_CONN&quot;
comma
)brace
suffix:semicolon
DECL|variable|ircomm_event
r_static
r_char
op_star
id|ircomm_event
(braket
)braket
op_assign
(brace
l_string|&quot;IRCOMM_CONNECT_REQUEST&quot;
comma
l_string|&quot;IRCOMM_CONNECT_RESPONSE&quot;
comma
l_string|&quot;IRCOMM_TTP_CONNECT_INDICATION&quot;
comma
l_string|&quot;IRCOMM_LMP_CONNECT_INDICATION&quot;
comma
l_string|&quot;IRCOMM_TTP_CONNECT_CONFIRM&quot;
comma
l_string|&quot;IRCOMM_LMP_CONNECT_CONFIRM&quot;
comma
l_string|&quot;IRCOMM_LMP_DISCONNECT_INDICATION&quot;
comma
l_string|&quot;IRCOMM_TTP_DISCONNECT_INDICATION&quot;
comma
l_string|&quot;IRCOMM_DISCONNECT_REQUEST&quot;
comma
l_string|&quot;IRCOMM_TTP_DATA_INDICATION&quot;
comma
l_string|&quot;IRCOMM_LMP_DATA_INDICATION&quot;
comma
l_string|&quot;IRCOMM_DATA_REQUEST&quot;
comma
l_string|&quot;IRCOMM_CONTROL_REQUEST&quot;
comma
l_string|&quot;IRCOMM_CONTROL_INDICATION&quot;
comma
)brace
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
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
op_assign
(brace
id|ircomm_state_idle
comma
id|ircomm_state_waiti
comma
id|ircomm_state_waitr
comma
id|ircomm_state_conn
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Function ircomm_state_idle (self, event, skb)&n; *&n; *    IrCOMM is currently idle&n; *&n; */
DECL|function|ircomm_state_idle
r_static
r_int
id|ircomm_state_idle
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRCOMM_CONNECT_REQUEST
suffix:colon
id|ircomm_next_state
c_func
(paren
id|self
comma
id|IRCOMM_WAITI
)paren
suffix:semicolon
id|ret
op_assign
id|self-&gt;issue
dot
id|connect_request
c_func
(paren
id|self
comma
id|skb
comma
id|info
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRCOMM_TTP_CONNECT_INDICATION
suffix:colon
r_case
id|IRCOMM_LMP_CONNECT_INDICATION
suffix:colon
id|ircomm_next_state
c_func
(paren
id|self
comma
id|IRCOMM_WAITR
)paren
suffix:semicolon
id|ircomm_connect_indication
c_func
(paren
id|self
comma
id|skb
comma
id|info
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
l_string|&quot;%s(), unknown event: %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ircomm_event
(braket
id|event
)braket
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_state_waiti (self, event, skb)&n; *&n; *    The IrCOMM user has requested an IrCOMM connection to the remote &n; *    device and is awaiting confirmation&n; */
DECL|function|ircomm_state_waiti
r_static
r_int
id|ircomm_state_waiti
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRCOMM_TTP_CONNECT_CONFIRM
suffix:colon
r_case
id|IRCOMM_LMP_CONNECT_CONFIRM
suffix:colon
id|ircomm_next_state
c_func
(paren
id|self
comma
id|IRCOMM_CONN
)paren
suffix:semicolon
id|ircomm_connect_confirm
c_func
(paren
id|self
comma
id|skb
comma
id|info
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRCOMM_TTP_DISCONNECT_INDICATION
suffix:colon
r_case
id|IRCOMM_LMP_DISCONNECT_INDICATION
suffix:colon
id|ircomm_next_state
c_func
(paren
id|self
comma
id|IRCOMM_IDLE
)paren
suffix:semicolon
id|ircomm_disconnect_indication
c_func
(paren
id|self
comma
id|skb
comma
id|info
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
l_string|&quot;%s(), unknown event: %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ircomm_event
(braket
id|event
)braket
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_state_waitr (self, event, skb)&n; *&n; *    IrCOMM has received an incoming connection request and is awaiting&n; *    response from the user&n; */
DECL|function|ircomm_state_waitr
r_static
r_int
id|ircomm_state_waitr
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRCOMM_CONNECT_RESPONSE
suffix:colon
id|ircomm_next_state
c_func
(paren
id|self
comma
id|IRCOMM_CONN
)paren
suffix:semicolon
id|ret
op_assign
id|self-&gt;issue
dot
id|connect_response
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
id|IRCOMM_DISCONNECT_REQUEST
suffix:colon
id|ircomm_next_state
c_func
(paren
id|self
comma
id|IRCOMM_IDLE
)paren
suffix:semicolon
id|ret
op_assign
id|self-&gt;issue
dot
id|disconnect_request
c_func
(paren
id|self
comma
id|skb
comma
id|info
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRCOMM_TTP_DISCONNECT_INDICATION
suffix:colon
r_case
id|IRCOMM_LMP_DISCONNECT_INDICATION
suffix:colon
id|ircomm_next_state
c_func
(paren
id|self
comma
id|IRCOMM_IDLE
)paren
suffix:semicolon
id|ircomm_disconnect_indication
c_func
(paren
id|self
comma
id|skb
comma
id|info
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
l_string|&quot;%s(), unknown event = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ircomm_event
(braket
id|event
)braket
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_state_conn (self, event, skb)&n; *&n; *    IrCOMM is connected to the peer IrCOMM device&n; *&n; */
DECL|function|ircomm_state_conn
r_static
r_int
id|ircomm_state_conn
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
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
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|IRCOMM_DATA_REQUEST
suffix:colon
id|ret
op_assign
id|self-&gt;issue
dot
id|data_request
c_func
(paren
id|self
comma
id|skb
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRCOMM_TTP_DATA_INDICATION
suffix:colon
id|ircomm_process_data
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
id|IRCOMM_LMP_DATA_INDICATION
suffix:colon
id|ircomm_data_indication
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
id|IRCOMM_CONTROL_REQUEST
suffix:colon
multiline_comment|/* Just send a separate frame for now */
id|ret
op_assign
id|self-&gt;issue
dot
id|data_request
c_func
(paren
id|self
comma
id|skb
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRCOMM_TTP_DISCONNECT_INDICATION
suffix:colon
r_case
id|IRCOMM_LMP_DISCONNECT_INDICATION
suffix:colon
id|ircomm_next_state
c_func
(paren
id|self
comma
id|IRCOMM_IDLE
)paren
suffix:semicolon
id|ircomm_disconnect_indication
c_func
(paren
id|self
comma
id|skb
comma
id|info
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRCOMM_DISCONNECT_REQUEST
suffix:colon
id|ircomm_next_state
c_func
(paren
id|self
comma
id|IRCOMM_IDLE
)paren
suffix:semicolon
id|ret
op_assign
id|self-&gt;issue
dot
id|disconnect_request
c_func
(paren
id|self
comma
id|skb
comma
id|info
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
l_string|&quot;%s(), unknown event = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ircomm_event
(braket
id|event
)braket
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_do_event (self, event, skb)&n; *&n; *    Process event&n; *&n; */
DECL|function|ircomm_do_event
r_int
id|ircomm_do_event
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_EVENT
id|event
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s: state=%s, event=%s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ircomm_state
(braket
id|self-&gt;state
)braket
comma
id|ircomm_event
(braket
id|event
)braket
)paren
suffix:semicolon
r_return
(paren
op_star
id|state
(braket
id|self-&gt;state
)braket
)paren
(paren
id|self
comma
id|event
comma
id|skb
comma
id|info
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_next_state (self, state)&n; *&n; *    Switch state&n; *&n; */
DECL|function|ircomm_next_state
r_void
id|ircomm_next_state
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_STATE
id|state
)paren
(brace
id|self-&gt;state
op_assign
id|state
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s: next state=%s, service type=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ircomm_state
(braket
id|self-&gt;state
)braket
comma
id|self-&gt;service_type
)paren
suffix:semicolon
)brace
eof
