multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlmp_frame.c&n; * Version:       0.9&n; * Description:   IrLMP frame implementation&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Aug 19 02:09:59 1997&n; * Modified at:   Mon Dec 13 13:41:12 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *     All Rights Reserved.&n; *     Copyright (c) 2000-2001 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#include &lt;net/irda/timer.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/irlmp_frame.h&gt;
macro_line|#include &lt;net/irda/discovery.h&gt;
r_static
r_struct
id|lsap_cb
op_star
id|irlmp_find_lsap
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
comma
id|__u8
id|dlsap
comma
id|__u8
id|slsap
comma
r_int
id|status
comma
id|hashbin_t
op_star
)paren
suffix:semicolon
DECL|function|irlmp_send_data_pdu
r_inline
r_void
id|irlmp_send_data_pdu
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
comma
id|__u8
id|dlsap
comma
id|__u8
id|slsap
comma
r_int
id|expedited
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
id|dlsap
suffix:semicolon
id|skb-&gt;data
(braket
l_int|1
)braket
op_assign
id|slsap
suffix:semicolon
r_if
c_cond
(paren
id|expedited
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s(), sending expedited data&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|irlap_data_request
c_func
(paren
id|self-&gt;irlap
comma
id|skb
comma
id|TRUE
)paren
suffix:semicolon
)brace
r_else
id|irlap_data_request
c_func
(paren
id|self-&gt;irlap
comma
id|skb
comma
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlmp_send_lcf_pdu (dlsap, slsap, opcode,skb)&n; *&n; *    Send Link Control Frame to IrLAP&n; */
DECL|function|irlmp_send_lcf_pdu
r_void
id|irlmp_send_lcf_pdu
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
comma
id|__u8
id|dlsap
comma
id|__u8
id|slsap
comma
id|__u8
id|opcode
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|__u8
op_star
id|frame
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
id|LMP_LAP_MAGIC
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
id|frame
op_assign
id|skb-&gt;data
suffix:semicolon
id|frame
(braket
l_int|0
)braket
op_assign
id|dlsap
op_or
id|CONTROL_BIT
suffix:semicolon
id|frame
(braket
l_int|1
)braket
op_assign
id|slsap
suffix:semicolon
id|frame
(braket
l_int|2
)braket
op_assign
id|opcode
suffix:semicolon
r_if
c_cond
(paren
id|opcode
op_eq
id|DISCONNECT
)paren
id|frame
(braket
l_int|3
)braket
op_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* Service user request */
r_else
id|frame
(braket
l_int|3
)braket
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* rsvd */
id|irlap_data_request
c_func
(paren
id|self-&gt;irlap
comma
id|skb
comma
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlmp_input (skb)&n; *&n; *    Used by IrLAP to pass received data frames to IrLMP layer&n; *&n; */
DECL|function|irlmp_link_data_indication
r_void
id|irlmp_link_data_indication
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|unreliable
)paren
(brace
r_struct
id|lsap_cb
op_star
id|lsap
suffix:semicolon
id|__u8
id|slsap_sel
suffix:semicolon
multiline_comment|/* Source (this) LSAP address */
id|__u8
id|dlsap_sel
suffix:semicolon
multiline_comment|/* Destination LSAP address */
id|__u8
op_star
id|fp
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
id|LMP_LAP_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|skb-&gt;len
OG
l_int|2
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|fp
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/*&n;&t; *  The next statements may be confusing, but we do this so that &n;&t; *  destination LSAP of received frame is source LSAP in our view&n;&t; */
id|slsap_sel
op_assign
id|fp
(braket
l_int|0
)braket
op_amp
id|LSAP_MASK
suffix:semicolon
id|dlsap_sel
op_assign
id|fp
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*&n;&t; *  Check if this is an incoming connection, since we must deal with&n;&t; *  it in a different way than other established connections.&n;&t; */
r_if
c_cond
(paren
(paren
id|fp
(braket
l_int|0
)braket
op_amp
id|CONTROL_BIT
)paren
op_logical_and
(paren
id|fp
(braket
l_int|2
)braket
op_eq
id|CONNECT_CMD
)paren
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|3
comma
l_string|&quot;%s(), incoming connection, &quot;
l_string|&quot;source LSAP=%d, dest LSAP=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slsap_sel
comma
id|dlsap_sel
)paren
suffix:semicolon
multiline_comment|/* Try to find LSAP among the unconnected LSAPs */
id|lsap
op_assign
id|irlmp_find_lsap
c_func
(paren
id|self
comma
id|dlsap_sel
comma
id|slsap_sel
comma
id|CONNECT_CMD
comma
id|irlmp-&gt;unconnected_lsaps
)paren
suffix:semicolon
multiline_comment|/* Maybe LSAP was already connected, so try one more time */
r_if
c_cond
(paren
op_logical_neg
id|lsap
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;%s(), incoming connection for LSAP already connected&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|lsap
op_assign
id|irlmp_find_lsap
c_func
(paren
id|self
comma
id|dlsap_sel
comma
id|slsap_sel
comma
l_int|0
comma
id|self-&gt;lsaps
)paren
suffix:semicolon
)brace
)brace
r_else
id|lsap
op_assign
id|irlmp_find_lsap
c_func
(paren
id|self
comma
id|dlsap_sel
comma
id|slsap_sel
comma
l_int|0
comma
id|self-&gt;lsaps
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lsap
op_eq
l_int|NULL
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;IrLMP, Sorry, no LSAP for received frame!&bslash;n&quot;
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), slsap_sel = %02x, dlsap_sel = %02x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slsap_sel
comma
id|dlsap_sel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fp
(braket
l_int|0
)braket
op_amp
id|CONTROL_BIT
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), received control frame %02x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|fp
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), received data frame&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* &n;&t; *  Check if we received a control frame? &n;&t; */
r_if
c_cond
(paren
id|fp
(braket
l_int|0
)braket
op_amp
id|CONTROL_BIT
)paren
(brace
r_switch
c_cond
(paren
id|fp
(braket
l_int|2
)braket
)paren
(brace
r_case
id|CONNECT_CMD
suffix:colon
id|lsap-&gt;lap
op_assign
id|self
suffix:semicolon
id|irlmp_do_lsap_event
c_func
(paren
id|lsap
comma
id|LM_CONNECT_INDICATION
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CONNECT_CNF
suffix:colon
id|irlmp_do_lsap_event
c_func
(paren
id|lsap
comma
id|LM_CONNECT_CONFIRM
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DISCONNECT
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s(), Disconnect indication!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|irlmp_do_lsap_event
c_func
(paren
id|lsap
comma
id|LM_DISCONNECT_INDICATION
comma
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACCESSMODE_CMD
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Access mode cmd not implemented!&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACCESSMODE_CNF
suffix:colon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;Access mode cnf not implemented!&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
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
l_string|&quot;%s(), Unknown control frame %02x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|fp
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|unreliable
)paren
(brace
multiline_comment|/* Optimize and bypass the state machine if possible */
r_if
c_cond
(paren
id|lsap-&gt;lsap_state
op_eq
id|LSAP_DATA_TRANSFER_READY
)paren
id|irlmp_udata_indication
c_func
(paren
id|lsap
comma
id|skb
)paren
suffix:semicolon
r_else
id|irlmp_do_lsap_event
c_func
(paren
id|lsap
comma
id|LM_UDATA_INDICATION
comma
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Optimize and bypass the state machine if possible */
r_if
c_cond
(paren
id|lsap-&gt;lsap_state
op_eq
id|LSAP_DATA_TRANSFER_READY
)paren
id|irlmp_data_indication
c_func
(paren
id|lsap
comma
id|skb
)paren
suffix:semicolon
r_else
id|irlmp_do_lsap_event
c_func
(paren
id|lsap
comma
id|LM_DATA_INDICATION
comma
id|skb
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function irlmp_link_unitdata_indication (self, skb)&n; *&n; *    &n; *&n; */
macro_line|#ifdef CONFIG_IRDA_ULTRA
DECL|function|irlmp_link_unitdata_indication
r_void
id|irlmp_link_unitdata_indication
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|lsap_cb
op_star
id|lsap
suffix:semicolon
id|__u8
id|slsap_sel
suffix:semicolon
multiline_comment|/* Source (this) LSAP address */
id|__u8
id|dlsap_sel
suffix:semicolon
multiline_comment|/* Destination LSAP address */
id|__u8
id|pid
suffix:semicolon
multiline_comment|/* Protocol identifier */
id|__u8
op_star
id|fp
suffix:semicolon
r_int
r_int
id|flags
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
id|LMP_LAP_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|skb-&gt;len
OG
l_int|2
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|fp
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/*&n;&t; *  The next statements may be confusing, but we do this so that &n;&t; *  destination LSAP of received frame is source LSAP in our view&n;&t; */
id|slsap_sel
op_assign
id|fp
(braket
l_int|0
)braket
op_amp
id|LSAP_MASK
suffix:semicolon
id|dlsap_sel
op_assign
id|fp
(braket
l_int|1
)braket
suffix:semicolon
id|pid
op_assign
id|fp
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_amp
l_int|0x80
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), extension in PID not supp!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Check if frame is addressed to the connectionless LSAP */
r_if
c_cond
(paren
(paren
id|slsap_sel
op_ne
id|LSAP_CONNLESS
)paren
op_logical_or
(paren
id|dlsap_sel
op_ne
id|LSAP_CONNLESS
)paren
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), dropping frame!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Search the connectionless LSAP */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irlmp-&gt;unconnected_lsaps-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
id|lsap
op_assign
(paren
r_struct
id|lsap_cb
op_star
)paren
id|hashbin_get_first
c_func
(paren
id|irlmp-&gt;unconnected_lsaps
)paren
suffix:semicolon
r_while
c_loop
(paren
id|lsap
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; *  Check if source LSAP and dest LSAP selectors and PID match.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|lsap-&gt;slsap_sel
op_eq
id|slsap_sel
)paren
op_logical_and
(paren
id|lsap-&gt;dlsap_sel
op_eq
id|dlsap_sel
)paren
op_logical_and
(paren
id|lsap-&gt;pid
op_eq
id|pid
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
id|lsap
op_assign
(paren
r_struct
id|lsap_cb
op_star
)paren
id|hashbin_get_next
c_func
(paren
id|irlmp-&gt;unconnected_lsaps
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irlmp-&gt;unconnected_lsaps-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lsap
)paren
id|irlmp_connless_data_indication
c_func
(paren
id|lsap
comma
id|skb
)paren
suffix:semicolon
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), found no matching LSAP!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_IRDA_ULTRA */
multiline_comment|/*&n; * Function irlmp_link_disconnect_indication (reason, userdata)&n; *&n; *    IrLAP has disconnected &n; *&n; */
DECL|function|irlmp_link_disconnect_indication
r_void
id|irlmp_link_disconnect_indication
c_func
(paren
r_struct
id|lap_cb
op_star
id|lap
comma
r_struct
id|irlap_cb
op_star
id|irlap
comma
id|LAP_REASON
id|reason
comma
r_struct
id|sk_buff
op_star
id|userdata
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
id|ASSERT
c_func
(paren
id|lap
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
id|lap-&gt;magic
op_eq
id|LMP_LAP_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|lap-&gt;reason
op_assign
id|reason
suffix:semicolon
id|lap-&gt;daddr
op_assign
id|DEV_ADDR_ANY
suffix:semicolon
multiline_comment|/* FIXME: must do something with the userdata if any */
r_if
c_cond
(paren
id|userdata
)paren
id|dev_kfree_skb
c_func
(paren
id|userdata
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  Inform station state machine&n;&t; */
id|irlmp_do_lap_event
c_func
(paren
id|lap
comma
id|LM_LAP_DISCONNECT_INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlmp_link_connect_indication (qos)&n; *&n; *    Incoming LAP connection!&n; *&n; */
DECL|function|irlmp_link_connect_indication
r_void
id|irlmp_link_connect_indication
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
comma
id|__u32
id|saddr
comma
id|__u32
id|daddr
comma
r_struct
id|qos_info
op_star
id|qos
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
multiline_comment|/* Copy QoS settings for this session */
id|self-&gt;qos
op_assign
id|qos
suffix:semicolon
multiline_comment|/* Update destination device address */
id|self-&gt;daddr
op_assign
id|daddr
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;saddr
op_eq
id|saddr
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|irlmp_do_lap_event
c_func
(paren
id|self
comma
id|LM_LAP_CONNECT_INDICATION
comma
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlmp_link_connect_confirm (qos)&n; *&n; *    LAP connection confirmed!&n; *&n; */
DECL|function|irlmp_link_connect_confirm
r_void
id|irlmp_link_connect_confirm
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
comma
r_struct
id|qos_info
op_star
id|qos
comma
r_struct
id|sk_buff
op_star
id|userdata
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
id|LMP_LAP_MAGIC
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
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t need use the userdata for now */
r_if
c_cond
(paren
id|userdata
)paren
id|dev_kfree_skb
c_func
(paren
id|userdata
)paren
suffix:semicolon
multiline_comment|/* Copy QoS settings for this session */
id|self-&gt;qos
op_assign
id|qos
suffix:semicolon
id|irlmp_do_lap_event
c_func
(paren
id|self
comma
id|LM_LAP_CONNECT_CONFIRM
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlmp_link_discovery_indication (self, log)&n; *&n; *    Device is discovering us&n; *&n; * It&squot;s not an answer to our own discoveries, just another device trying&n; * to perform discovery, but we don&squot;t want to miss the opportunity&n; * to exploit this information, because :&n; *&t;o We may not actively perform discovery (just passive discovery)&n; *&t;o This type of discovery is much more reliable. In some cases, it&n; *&t;  seem that less than 50% of our discoveries get an answer, while&n; *&t;  we always get ~100% of these.&n; *&t;o Make faster discovery, statistically divide time of discovery&n; *&t;  events by 2 (important for the latency aspect and user feel)&n; *&t;o Even is we do active discovery, the other node might not&n; *&t;  answer our discoveries (ex: Palm). The Palm will just perform&n; *&t;  one active discovery and connect directly to us.&n; *&n; * However, when both devices discover each other, they might attempt to&n; * connect to each other following the discovery event, and it would create&n; * collisions on the medium (SNRM battle).&n; * The &quot;fix&quot; for that is to disable all connection requests in IrLAP&n; * for 100ms after a discovery indication by setting the media_busy flag.&n; * Previously, we used to postpone the event which was quite ugly. Now&n; * that IrLAP takes care of this problem, just pass the event up...&n; *&n; * Jean II&n; */
DECL|function|irlmp_link_discovery_indication
r_void
id|irlmp_link_discovery_indication
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
comma
id|discovery_t
op_star
id|discovery
)paren
(brace
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
id|LMP_LAP_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Add to main log, cleanup */
id|irlmp_add_discovery
c_func
(paren
id|irlmp-&gt;cachelog
comma
id|discovery
)paren
suffix:semicolon
multiline_comment|/* Just handle it the same way as a discovery confirm,&n;&t; * bypass the LM_LAP state machine (see below) */
id|irlmp_discovery_confirm
c_func
(paren
id|irlmp-&gt;cachelog
comma
id|DISCOVERY_PASSIVE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlmp_link_discovery_confirm (self, log)&n; *&n; *    Called by IrLAP with a list of discoveries after the discovery&n; *    request has been carried out. A NULL log is received if IrLAP&n; *    was unable to carry out the discovery request&n; *&n; */
DECL|function|irlmp_link_discovery_confirm
r_void
id|irlmp_link_discovery_confirm
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
comma
id|hashbin_t
op_star
id|log
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
id|LMP_LAP_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Add to main log, cleanup */
id|irlmp_add_discovery_log
c_func
(paren
id|irlmp-&gt;cachelog
comma
id|log
)paren
suffix:semicolon
multiline_comment|/* Propagate event to various LSAPs registered for it.&n;&t; * We bypass the LM_LAP state machine because&n;&t; *&t;1) We do it regardless of the LM_LAP state&n;&t; *&t;2) It doesn&squot;t affect the LM_LAP state&n;&t; *&t;3) Faster, slimer, simpler, ...&n;&t; * Jean II */
id|irlmp_discovery_confirm
c_func
(paren
id|irlmp-&gt;cachelog
comma
id|DISCOVERY_ACTIVE
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IRDA_CACHE_LAST_LSAP
DECL|function|irlmp_update_cache
r_static
r_inline
r_void
id|irlmp_update_cache
c_func
(paren
r_struct
id|lap_cb
op_star
id|lap
comma
r_struct
id|lsap_cb
op_star
id|lsap
)paren
(brace
multiline_comment|/* Prevent concurrent read to get garbage */
id|lap-&gt;cache.valid
op_assign
id|FALSE
suffix:semicolon
multiline_comment|/* Update cache entry */
id|lap-&gt;cache.dlsap_sel
op_assign
id|lsap-&gt;dlsap_sel
suffix:semicolon
id|lap-&gt;cache.slsap_sel
op_assign
id|lsap-&gt;slsap_sel
suffix:semicolon
id|lap-&gt;cache.lsap
op_assign
id|lsap
suffix:semicolon
id|lap-&gt;cache.valid
op_assign
id|TRUE
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Function irlmp_find_handle (self, dlsap_sel, slsap_sel, status, queue)&n; *&n; *    Find handle associated with destination and source LSAP&n; *&n; * Any IrDA connection (LSAP/TSAP) is uniquely identified by&n; * 3 parameters, the local lsap, the remote lsap and the remote address. &n; * We may initiate multiple connections to the same remote service&n; * (they will have different local lsap), a remote device may initiate&n; * multiple connections to the same local service (they will have&n; * different remote lsap), or multiple devices may connect to the same&n; * service and may use the same remote lsap (and they will have&n; * different remote address).&n; * So, where is the remote address ? Each LAP connection is made with&n; * a single remote device, so imply a specific remote address.&n; * Jean II&n; */
DECL|function|irlmp_find_lsap
r_static
r_struct
id|lsap_cb
op_star
id|irlmp_find_lsap
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
comma
id|__u8
id|dlsap_sel
comma
id|__u8
id|slsap_sel
comma
r_int
id|status
comma
id|hashbin_t
op_star
id|queue
)paren
(brace
r_struct
id|lsap_cb
op_star
id|lsap
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* &n;&t; *  Optimize for the common case. We assume that the last frame&n;&t; *  received is in the same connection as the last one, so check in&n;&t; *  cache first to avoid the linear search&n;&t; */
macro_line|#ifdef CONFIG_IRDA_CACHE_LAST_LSAP
r_if
c_cond
(paren
(paren
id|self-&gt;cache.valid
)paren
op_logical_and
(paren
id|self-&gt;cache.slsap_sel
op_eq
id|slsap_sel
)paren
op_logical_and
(paren
id|self-&gt;cache.dlsap_sel
op_eq
id|dlsap_sel
)paren
)paren
(brace
r_return
(paren
id|self-&gt;cache.lsap
)paren
suffix:semicolon
)brace
macro_line|#endif
id|spin_lock_irqsave
c_func
(paren
op_amp
id|queue-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
id|lsap
op_assign
(paren
r_struct
id|lsap_cb
op_star
)paren
id|hashbin_get_first
c_func
(paren
id|queue
)paren
suffix:semicolon
r_while
c_loop
(paren
id|lsap
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* &n;&t;&t; *  If this is an incoming connection, then the destination &n;&t;&t; *  LSAP selector may have been specified as LM_ANY so that &n;&t;&t; *  any client can connect. In that case we only need to check&n;&t;&t; *  if the source LSAP (in our view!) match!&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|status
op_eq
id|CONNECT_CMD
)paren
op_logical_and
(paren
id|lsap-&gt;slsap_sel
op_eq
id|slsap_sel
)paren
op_logical_and
(paren
id|lsap-&gt;dlsap_sel
op_eq
id|LSAP_ANY
)paren
)paren
(brace
multiline_comment|/* This is where the dest lsap sel is set on incoming&n;&t;&t;&t; * lsaps */
id|lsap-&gt;dlsap_sel
op_assign
id|dlsap_sel
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *  Check if source LSAP and dest LSAP selectors match.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|lsap-&gt;slsap_sel
op_eq
id|slsap_sel
)paren
op_logical_and
(paren
id|lsap-&gt;dlsap_sel
op_eq
id|dlsap_sel
)paren
)paren
r_break
suffix:semicolon
id|lsap
op_assign
(paren
r_struct
id|lsap_cb
op_star
)paren
id|hashbin_get_next
c_func
(paren
id|queue
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IRDA_CACHE_LAST_LSAP
r_if
c_cond
(paren
id|lsap
)paren
(brace
id|irlmp_update_cache
c_func
(paren
id|self
comma
id|lsap
)paren
suffix:semicolon
)brace
macro_line|#endif
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|queue-&gt;hb_spinlock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Return what we&squot;ve found or NULL */
r_return
id|lsap
suffix:semicolon
)brace
eof
