multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlan_client.c&n; * Version:       0.9&n; * Description:   IrDA LAN Access Protocol (IrLAN) Client&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Aug 31 20:14:37 1997&n; * Modified at:   Tue Dec 14 15:47:02 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Sources:       skeleton.c by Donald Becker &lt;becker@CESDIS.gsfc.nasa.gov&gt;&n; *                slip.c by Laurence Culhane, &lt;loz@holmes.demon.co.uk&gt;&n; *                          Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/irias_object.h&gt;
macro_line|#include &lt;net/irda/iriap.h&gt;
macro_line|#include &lt;net/irda/timer.h&gt;
macro_line|#include &lt;net/irda/irlan_common.h&gt;
macro_line|#include &lt;net/irda/irlan_event.h&gt;
macro_line|#include &lt;net/irda/irlan_eth.h&gt;
macro_line|#include &lt;net/irda/irlan_provider.h&gt;
macro_line|#include &lt;net/irda/irlan_client.h&gt;
DECL|macro|CONFIG_IRLAN_GRATUITOUS_ARP
macro_line|#undef CONFIG_IRLAN_GRATUITOUS_ARP
r_static
r_void
id|irlan_client_ctrl_disconnect_indication
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
)paren
suffix:semicolon
r_static
r_int
id|irlan_client_ctrl_data_indication
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
suffix:semicolon
r_static
r_void
id|irlan_client_ctrl_connect_confirm
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
)paren
suffix:semicolon
r_static
r_void
id|irlan_check_response_param
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_char
op_star
id|param
comma
r_char
op_star
id|value
comma
r_int
id|val_len
)paren
suffix:semicolon
DECL|function|irlan_client_kick_timer_expired
r_static
r_void
id|irlan_client_kick_timer_expired
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|irlan_cb
op_star
id|self
op_assign
(paren
r_struct
id|irlan_cb
op_star
)paren
id|data
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
id|IRLAN_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/*  &n;&t; * If we are in peer mode, the client may not have got the discovery&n;&t; * indication it needs to make progress. If the client is still in &n;&t; * IDLE state, we must kick it to, but only if the provider is not IDLE&n; &t; */
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
id|self-&gt;client.state
op_eq
id|IRLAN_IDLE
)paren
op_logical_and
(paren
id|self-&gt;provider.state
op_ne
id|IRLAN_IDLE
)paren
)paren
(brace
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
)brace
)brace
DECL|function|irlan_client_start_kick_timer
r_void
id|irlan_client_start_kick_timer
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_int
id|timeout
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
id|irda_start_timer
c_func
(paren
op_amp
id|self-&gt;client.kick_timer
comma
id|timeout
comma
(paren
r_void
op_star
)paren
id|self
comma
id|irlan_client_kick_timer_expired
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlan_client_wakeup (self, saddr, daddr)&n; *&n; *    Wake up client&n; *&n; */
DECL|function|irlan_client_wakeup
r_void
id|irlan_client_wakeup
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
id|__u32
id|saddr
comma
id|__u32
id|daddr
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|1
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
id|IRLAN_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Check if we are already awake, or if we are a provider in direct&n;&t; * mode (in that case we must leave the client idle&n;&t; */
r_if
c_cond
(paren
(paren
id|self-&gt;client.state
op_ne
id|IRLAN_IDLE
)paren
op_logical_or
(paren
id|self-&gt;provider.access_type
op_eq
id|ACCESS_DIRECT
)paren
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), already awake!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Addresses may have changed! */
id|self-&gt;saddr
op_assign
id|saddr
suffix:semicolon
id|self-&gt;daddr
op_assign
id|daddr
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;disconnect_reason
op_eq
id|LM_USER_REQUEST
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s(), still stopped by user&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Open TSAPs */
id|irlan_client_open_ctrl_tsap
c_func
(paren
id|self
)paren
suffix:semicolon
id|irlan_open_data_tsap
c_func
(paren
id|self
)paren
suffix:semicolon
id|irlan_do_client_event
c_func
(paren
id|self
comma
id|IRLAN_DISCOVERY_INDICATION
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Start kick timer */
id|irlan_client_start_kick_timer
c_func
(paren
id|self
comma
l_int|2
op_star
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlan_discovery_indication (daddr)&n; *&n; *    Remote device with IrLAN server support discovered&n; *&n; */
DECL|function|irlan_client_discovery_indication
r_void
id|irlan_client_discovery_indication
c_func
(paren
id|discinfo_t
op_star
id|discovery
comma
id|DISCOVERY_MODE
id|mode
comma
r_void
op_star
id|priv
)paren
(brace
r_struct
id|irlan_cb
op_star
id|self
suffix:semicolon
id|__u32
id|saddr
comma
id|daddr
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|discovery
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * I didn&squot;t check it, but I bet that IrLAN suffer from the same&n;&t; * deficiency as IrComm and doesn&squot;t handle two instances&n;&t; * simultaneously connecting to each other.&n;&t; * Same workaround, drop passive discoveries.&n;&t; * Jean II */
r_if
c_cond
(paren
id|mode
op_eq
id|DISCOVERY_PASSIVE
)paren
(brace
r_return
suffix:semicolon
)brace
id|saddr
op_assign
id|discovery-&gt;saddr
suffix:semicolon
id|daddr
op_assign
id|discovery-&gt;daddr
suffix:semicolon
multiline_comment|/* Find instance */
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
id|self
op_assign
id|irlan_get_any
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self
)paren
(brace
id|ASSERT
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
id|IRDA_DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;%s(), Found instance (%08x)!&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|daddr
)paren
suffix:semicolon
id|irlan_client_wakeup
c_func
(paren
id|self
comma
id|saddr
comma
id|daddr
)paren
suffix:semicolon
)brace
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlan_client_data_indication (handle, skb)&n; *&n; *    This function gets the data that is received on the control channel&n; *&n; */
DECL|function|irlan_client_ctrl_data_indication
r_static
r_int
id|irlan_client_ctrl_data_indication
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
id|irlan_cb
op_star
id|self
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
id|self
op_assign
(paren
r_struct
id|irlan_cb
op_star
)paren
id|instance
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
id|IRLAN_MAGIC
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
id|irlan_do_client_event
c_func
(paren
id|self
comma
id|IRLAN_DATA_INDICATION
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/* Ready for a new command */
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), clearing tx_busy&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|self-&gt;client.tx_busy
op_assign
id|FALSE
suffix:semicolon
multiline_comment|/* Check if we have some queued commands waiting to be sent */
id|irlan_run_ctrl_tx_queue
c_func
(paren
id|self
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irlan_client_ctrl_disconnect_indication
r_static
r_void
id|irlan_client_ctrl_disconnect_indication
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
id|userdata
)paren
(brace
r_struct
id|irlan_cb
op_star
id|self
suffix:semicolon
r_struct
id|tsap_cb
op_star
id|tsap
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s(), reason=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|reason
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irlan_cb
op_star
)paren
id|instance
suffix:semicolon
id|tsap
op_assign
(paren
r_struct
id|tsap_cb
op_star
)paren
id|sap
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
id|IRLAN_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|tsap
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
id|tsap-&gt;magic
op_eq
id|TTP_TSAP_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|tsap
op_eq
id|self-&gt;client.tsap_ctrl
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Remove frames queued on the control channel */
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|self-&gt;client.txq
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|self-&gt;client.tx_busy
op_assign
id|FALSE
suffix:semicolon
id|irlan_do_client_event
c_func
(paren
id|self
comma
id|IRLAN_LMP_DISCONNECT
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlan_client_open_tsaps (self)&n; *&n; *    Initialize callbacks and open IrTTP TSAPs&n; *&n; */
DECL|function|irlan_client_open_ctrl_tsap
r_void
id|irlan_client_open_ctrl_tsap
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
(brace
r_struct
id|tsap_cb
op_star
id|tsap
suffix:semicolon
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
id|IRLAN_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Check if already open */
r_if
c_cond
(paren
id|self-&gt;client.tsap_ctrl
)paren
r_return
suffix:semicolon
id|irda_notify_init
c_func
(paren
op_amp
id|notify
)paren
suffix:semicolon
multiline_comment|/* Set up callbacks */
id|notify.data_indication
op_assign
id|irlan_client_ctrl_data_indication
suffix:semicolon
id|notify.connect_confirm
op_assign
id|irlan_client_ctrl_connect_confirm
suffix:semicolon
id|notify.disconnect_indication
op_assign
id|irlan_client_ctrl_disconnect_indication
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
l_string|&quot;IrLAN ctrl (c)&quot;
comma
r_sizeof
(paren
id|notify.name
)paren
)paren
suffix:semicolon
id|tsap
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
id|tsap
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), Got no tsap!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|self-&gt;client.tsap_ctrl
op_assign
id|tsap
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlan_client_connect_confirm (handle, skb)&n; *&n; *    Connection to peer IrLAN laye confirmed&n; *&n; */
DECL|function|irlan_client_ctrl_connect_confirm
r_static
r_void
id|irlan_client_ctrl_connect_confirm
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
id|irlan_cb
op_star
id|self
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
id|self
op_assign
(paren
r_struct
id|irlan_cb
op_star
)paren
id|instance
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
id|IRLAN_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|self-&gt;client.max_sdu_size
op_assign
id|max_sdu_size
suffix:semicolon
id|self-&gt;client.max_header_size
op_assign
id|max_header_size
suffix:semicolon
multiline_comment|/* TODO: we could set the MTU depending on the max_sdu_size */
id|irlan_do_client_event
c_func
(paren
id|self
comma
id|IRLAN_CONNECT_COMPLETE
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlan_client_reconnect_data_channel (self)&n; *&n; *    Try to reconnect data channel (currently not used)&n; *&n; */
DECL|function|irlan_client_reconnect_data_channel
r_void
id|irlan_client_reconnect_data_channel
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|__u8
op_star
id|frame
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
id|IRLAN_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
l_int|128
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
suffix:semicolon
multiline_comment|/* Reserve space for TTP, LMP, and LAP header */
id|skb_reserve
c_func
(paren
id|skb
comma
id|self-&gt;max_header_size
)paren
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
l_int|2
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
id|CMD_RECONNECT_DATA_CHAN
suffix:semicolon
id|frame
(braket
l_int|1
)braket
op_assign
l_int|0x01
suffix:semicolon
id|irlan_insert_array_param
c_func
(paren
id|skb
comma
l_string|&quot;RECONNECT_KEY&quot;
comma
id|self-&gt;client.reconnect_key
comma
id|self-&gt;client.key_len
)paren
suffix:semicolon
id|irttp_data_request
c_func
(paren
id|self-&gt;client.tsap_ctrl
comma
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function print_ret_code (code)&n; *&n; *    Print return code of request to peer IrLAN layer.&n; *&n; */
DECL|function|print_ret_code
r_static
r_void
id|print_ret_code
c_func
(paren
id|__u8
id|code
)paren
(brace
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Success&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|WARNING
c_func
(paren
l_string|&quot;IrLAN: Insufficient resources&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|WARNING
c_func
(paren
l_string|&quot;IrLAN: Invalid command format&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|WARNING
c_func
(paren
l_string|&quot;IrLAN: Command not supported&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|WARNING
c_func
(paren
l_string|&quot;IrLAN: Parameter not supported&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|WARNING
c_func
(paren
l_string|&quot;IrLAN: Value not supported&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|WARNING
c_func
(paren
l_string|&quot;IrLAN: Not open&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|WARNING
c_func
(paren
l_string|&quot;IrLAN: Authentication required&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|WARNING
c_func
(paren
l_string|&quot;IrLAN: Invalid password&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
id|WARNING
c_func
(paren
l_string|&quot;IrLAN: Protocol error&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|255
suffix:colon
id|WARNING
c_func
(paren
l_string|&quot;IrLAN: Asynchronous status&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function irlan_client_parse_response (self, skb)&n; *&n; *    Extract all parameters from received buffer, then feed them to &n; *    check_params for parsing&n; */
DECL|function|irlan_client_parse_response
r_void
id|irlan_client_parse_response
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
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
id|__u8
op_star
id|ptr
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|__u16
id|val_len
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_char
op_star
id|value
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
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s() skb-&gt;len=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
(paren
r_int
)paren
id|skb-&gt;len
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
id|IRLAN_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|ERROR
c_func
(paren
l_string|&quot;%s(), Got NULL skb!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|frame
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* &n;&t; *  Check return code and print it if not success &n;&t; */
r_if
c_cond
(paren
id|frame
(braket
l_int|0
)braket
)paren
(brace
id|print_ret_code
c_func
(paren
id|frame
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|name
op_assign
id|kmalloc
c_func
(paren
l_int|255
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
suffix:semicolon
id|value
op_assign
id|kmalloc
c_func
(paren
l_int|1016
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
(brace
id|kfree
c_func
(paren
id|name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* How many parameters? */
id|count
op_assign
id|frame
(braket
l_int|1
)braket
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s(), got %d parameters&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|count
)paren
suffix:semicolon
id|ptr
op_assign
id|frame
op_plus
l_int|2
suffix:semicolon
multiline_comment|/* For all parameters */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ret
op_assign
id|irlan_extract_param
c_func
(paren
id|ptr
comma
id|name
comma
id|value
comma
op_amp
id|val_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), IrLAN, Error!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ptr
op_add_assign
id|ret
suffix:semicolon
id|irlan_check_response_param
c_func
(paren
id|self
comma
id|name
comma
id|value
comma
id|val_len
)paren
suffix:semicolon
)brace
multiline_comment|/* Cleanup */
id|kfree
c_func
(paren
id|name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlan_check_response_param (self, param, value, val_len)&n; *&n; *     Check which parameter is received and update local variables&n; *&n; */
DECL|function|irlan_check_response_param
r_static
r_void
id|irlan_check_response_param
c_func
(paren
r_struct
id|irlan_cb
op_star
id|self
comma
r_char
op_star
id|param
comma
r_char
op_star
id|value
comma
r_int
id|val_len
)paren
(brace
id|__u16
id|tmp_cpu
suffix:semicolon
multiline_comment|/* Temporary value in host order */
id|__u8
op_star
id|bytes
suffix:semicolon
r_int
id|i
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s(), parm=%s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|param
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
id|IRLAN_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Media type */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;MEDIA&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;802.3&quot;
)paren
op_eq
l_int|0
)paren
id|self-&gt;media
op_assign
id|MEDIA_802_3
suffix:semicolon
r_else
id|self-&gt;media
op_assign
id|MEDIA_802_5
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;FILTER_TYPE&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;DIRECTED&quot;
)paren
op_eq
l_int|0
)paren
id|self-&gt;client.filter_type
op_or_assign
id|IRLAN_DIRECTED
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;FUNCTIONAL&quot;
)paren
op_eq
l_int|0
)paren
id|self-&gt;client.filter_type
op_or_assign
id|IRLAN_FUNCTIONAL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;GROUP&quot;
)paren
op_eq
l_int|0
)paren
id|self-&gt;client.filter_type
op_or_assign
id|IRLAN_GROUP
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;MAC_FRAME&quot;
)paren
op_eq
l_int|0
)paren
id|self-&gt;client.filter_type
op_or_assign
id|IRLAN_MAC_FRAME
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;MULTICAST&quot;
)paren
op_eq
l_int|0
)paren
id|self-&gt;client.filter_type
op_or_assign
id|IRLAN_MULTICAST
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;BROADCAST&quot;
)paren
op_eq
l_int|0
)paren
id|self-&gt;client.filter_type
op_or_assign
id|IRLAN_BROADCAST
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;IPX_SOCKET&quot;
)paren
op_eq
l_int|0
)paren
id|self-&gt;client.filter_type
op_or_assign
id|IRLAN_IPX_SOCKET
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;ACCESS_TYPE&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;DIRECT&quot;
)paren
op_eq
l_int|0
)paren
id|self-&gt;client.access_type
op_assign
id|ACCESS_DIRECT
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;PEER&quot;
)paren
op_eq
l_int|0
)paren
id|self-&gt;client.access_type
op_assign
id|ACCESS_PEER
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;HOSTED&quot;
)paren
op_eq
l_int|0
)paren
id|self-&gt;client.access_type
op_assign
id|ACCESS_HOSTED
suffix:semicolon
r_else
(brace
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
)brace
)brace
multiline_comment|/* IRLAN version */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;IRLAN_VER&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;IrLAN version %d.%d&bslash;n&quot;
comma
(paren
id|__u8
)paren
id|value
(braket
l_int|0
)braket
comma
(paren
id|__u8
)paren
id|value
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|self-&gt;version
(braket
l_int|0
)braket
op_assign
id|value
(braket
l_int|0
)braket
suffix:semicolon
id|self-&gt;version
(braket
l_int|1
)braket
op_assign
id|value
(braket
l_int|1
)braket
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Which remote TSAP to use for data channel */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;DATA_CHAN&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|self-&gt;dtsap_sel_data
op_assign
id|value
(braket
l_int|0
)braket
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;Data TSAP = %02x&bslash;n&quot;
comma
id|self-&gt;dtsap_sel_data
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;CON_ARB&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|tmp_cpu
comma
id|value
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Align value */
id|le16_to_cpus
c_func
(paren
op_amp
id|tmp_cpu
)paren
suffix:semicolon
multiline_comment|/* Convert to host order */
id|self-&gt;client.recv_arb_val
op_assign
id|tmp_cpu
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), receive arb val=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|self-&gt;client.recv_arb_val
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;MAX_FRAME&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|tmp_cpu
comma
id|value
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Align value */
id|le16_to_cpus
c_func
(paren
op_amp
id|tmp_cpu
)paren
suffix:semicolon
multiline_comment|/* Convert to host order */
id|self-&gt;client.max_frame
op_assign
id|tmp_cpu
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;%s(), max frame=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|self-&gt;client.max_frame
)paren
suffix:semicolon
)brace
multiline_comment|/* RECONNECT_KEY, in case the link goes down! */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;RECONNECT_KEY&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;Got reconnect key: &quot;
)paren
suffix:semicolon
multiline_comment|/* for (i = 0; i &lt; val_len; i++) */
multiline_comment|/* &t;&t;&t;printk(&quot;%02x&quot;, value[i]); */
id|memcpy
c_func
(paren
id|self-&gt;client.reconnect_key
comma
id|value
comma
id|val_len
)paren
suffix:semicolon
id|self-&gt;client.key_len
op_assign
id|val_len
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* FILTER_ENTRY, have we got an ethernet address? */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|param
comma
l_string|&quot;FILTER_ENTRY&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|bytes
op_assign
id|value
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;Ethernet address = %02x:%02x:%02x:%02x:%02x:%02x&bslash;n&quot;
comma
id|bytes
(braket
l_int|0
)braket
comma
id|bytes
(braket
l_int|1
)braket
comma
id|bytes
(braket
l_int|2
)braket
comma
id|bytes
(braket
l_int|3
)braket
comma
id|bytes
(braket
l_int|4
)braket
comma
id|bytes
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|self-&gt;dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|bytes
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function irlan_client_get_value_confirm (obj_id, value)&n; *&n; *    Got results from remote LM-IAS&n; *&n; */
DECL|function|irlan_client_get_value_confirm
r_void
id|irlan_client_get_value_confirm
c_func
(paren
r_int
id|result
comma
id|__u16
id|obj_id
comma
r_struct
id|ias_value
op_star
id|value
comma
r_void
op_star
id|priv
)paren
(brace
r_struct
id|irlan_cb
op_star
id|self
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
id|priv
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irlan_cb
op_star
)paren
id|priv
suffix:semicolon
id|ASSERT
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
multiline_comment|/* We probably don&squot;t need to make any more queries */
id|iriap_close
c_func
(paren
id|self-&gt;client.iriap
)paren
suffix:semicolon
id|self-&gt;client.iriap
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Check if request succeeded */
r_if
c_cond
(paren
id|result
op_ne
id|IAS_SUCCESS
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s(), got NULL value!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|irlan_do_client_event
c_func
(paren
id|self
comma
id|IRLAN_IAS_PROVIDER_NOT_AVAIL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|value-&gt;type
)paren
(brace
r_case
id|IAS_INTEGER
suffix:colon
id|self-&gt;dtsap_sel_ctrl
op_assign
id|value-&gt;t.integer
suffix:semicolon
r_if
c_cond
(paren
id|value-&gt;t.integer
op_ne
op_minus
l_int|1
)paren
(brace
id|irlan_do_client_event
c_func
(paren
id|self
comma
id|IRLAN_IAS_PROVIDER_AVAIL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|irias_delete_value
c_func
(paren
id|value
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
l_string|&quot;%s(), unknown type!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|irlan_do_client_event
c_func
(paren
id|self
comma
id|IRLAN_IAS_PROVIDER_NOT_AVAIL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
