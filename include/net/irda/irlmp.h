multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlmp.h&n; * Version:       0.9&n; * Description:   IrDA Link Management Protocol (LMP) layer&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Aug 17 20:54:32 1997&n; * Modified at:   Fri Dec 10 13:23:01 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     Copyright (c) 2000-2002 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRLMP_H
DECL|macro|IRLMP_H
mdefine_line|#define IRLMP_H
macro_line|#include &lt;asm/param.h&gt;  /* for HZ */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/qos.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;&t;&t;/* LAP_MAX_HEADER, ... */
macro_line|#include &lt;net/irda/irlmp_event.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
macro_line|#include &lt;net/irda/discovery.h&gt;
multiline_comment|/* LSAP-SEL&squot;s */
DECL|macro|LSAP_MASK
mdefine_line|#define LSAP_MASK     0x7f
DECL|macro|LSAP_IAS
mdefine_line|#define LSAP_IAS      0x00
DECL|macro|LSAP_ANY
mdefine_line|#define LSAP_ANY      0xff
DECL|macro|LSAP_MAX
mdefine_line|#define LSAP_MAX      0x6f /* 0x70-0x7f are reserved */
DECL|macro|LSAP_CONNLESS
mdefine_line|#define LSAP_CONNLESS 0x70 /* Connectionless LSAP, mostly used for Ultra */
DECL|macro|DEV_ADDR_ANY
mdefine_line|#define DEV_ADDR_ANY  0xffffffff
DECL|macro|LMP_HEADER
mdefine_line|#define LMP_HEADER          2    /* Dest LSAP + Source LSAP */
DECL|macro|LMP_CONTROL_HEADER
mdefine_line|#define LMP_CONTROL_HEADER  4
DECL|macro|LMP_PID_HEADER
mdefine_line|#define LMP_PID_HEADER      1    /* Used by Ultra */
DECL|macro|LMP_MAX_HEADER
mdefine_line|#define LMP_MAX_HEADER      (LMP_CONTROL_HEADER+LAP_MAX_HEADER)
DECL|macro|LM_MAX_CONNECTIONS
mdefine_line|#define LM_MAX_CONNECTIONS  10
DECL|macro|LM_IDLE_TIMEOUT
mdefine_line|#define LM_IDLE_TIMEOUT     2*HZ /* 2 seconds for now */
r_typedef
r_enum
(brace
DECL|enumerator|S_PNP
id|S_PNP
op_assign
l_int|0
comma
DECL|enumerator|S_PDA
id|S_PDA
comma
DECL|enumerator|S_COMPUTER
id|S_COMPUTER
comma
DECL|enumerator|S_PRINTER
id|S_PRINTER
comma
DECL|enumerator|S_MODEM
id|S_MODEM
comma
DECL|enumerator|S_FAX
id|S_FAX
comma
DECL|enumerator|S_LAN
id|S_LAN
comma
DECL|enumerator|S_TELEPHONY
id|S_TELEPHONY
comma
DECL|enumerator|S_COMM
id|S_COMM
comma
DECL|enumerator|S_OBEX
id|S_OBEX
comma
DECL|enumerator|S_ANY
id|S_ANY
comma
DECL|enumerator|S_END
id|S_END
comma
DECL|typedef|SERVICE
)brace
id|SERVICE
suffix:semicolon
multiline_comment|/* For selective discovery */
DECL|typedef|DISCOVERY_CALLBACK1
r_typedef
r_void
(paren
op_star
id|DISCOVERY_CALLBACK1
)paren
(paren
id|discinfo_t
op_star
comma
id|DISCOVERY_MODE
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* For expiry (the same) */
DECL|typedef|DISCOVERY_CALLBACK2
r_typedef
r_void
(paren
op_star
id|DISCOVERY_CALLBACK2
)paren
(paren
id|discinfo_t
op_star
comma
id|DISCOVERY_MODE
comma
r_void
op_star
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|queue
id|irda_queue_t
id|queue
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|hints
id|__u16_host_order
id|hints
suffix:semicolon
multiline_comment|/* Hint bits */
DECL|typedef|irlmp_service_t
)brace
id|irlmp_service_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|queue
id|irda_queue_t
id|queue
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|hint_mask
id|__u16_host_order
id|hint_mask
suffix:semicolon
DECL|member|disco_callback
id|DISCOVERY_CALLBACK1
id|disco_callback
suffix:semicolon
multiline_comment|/* Selective discovery */
DECL|member|expir_callback
id|DISCOVERY_CALLBACK2
id|expir_callback
suffix:semicolon
multiline_comment|/* Selective expiration */
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* Used to identify client */
DECL|typedef|irlmp_client_t
)brace
id|irlmp_client_t
suffix:semicolon
multiline_comment|/*&n; *  Information about each logical LSAP connection&n; */
DECL|struct|lsap_cb
r_struct
id|lsap_cb
(brace
DECL|member|queue
id|irda_queue_t
id|queue
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
DECL|member|connected
r_int
r_int
id|connected
suffix:semicolon
multiline_comment|/* set_bit used on this */
DECL|member|persistent
r_int
id|persistent
suffix:semicolon
DECL|member|slsap_sel
id|__u8
id|slsap_sel
suffix:semicolon
multiline_comment|/* Source (this) LSAP address */
DECL|member|dlsap_sel
id|__u8
id|dlsap_sel
suffix:semicolon
multiline_comment|/* Destination LSAP address (if connected) */
macro_line|#ifdef CONFIG_IRDA_ULTRA
DECL|member|pid
id|__u8
id|pid
suffix:semicolon
multiline_comment|/* Used by connectionless LSAP */
macro_line|#endif /* CONFIG_IRDA_ULTRA */
DECL|member|conn_skb
r_struct
id|sk_buff
op_star
id|conn_skb
suffix:semicolon
multiline_comment|/* Store skb here while connecting */
DECL|member|watchdog_timer
r_struct
id|timer_list
id|watchdog_timer
suffix:semicolon
DECL|member|lsap_state
id|IRLMP_STATE
id|lsap_state
suffix:semicolon
multiline_comment|/* Connection state */
DECL|member|notify
id|notify_t
id|notify
suffix:semicolon
multiline_comment|/* Indication/Confirm entry points */
DECL|member|qos
r_struct
id|qos_info
id|qos
suffix:semicolon
multiline_comment|/* QoS for this connection */
DECL|member|lap
r_struct
id|lap_cb
op_star
id|lap
suffix:semicolon
multiline_comment|/* Pointer to LAP connection structure */
)brace
suffix:semicolon
multiline_comment|/*&n; *  Used for caching the last slsap-&gt;dlsap-&gt;handle mapping&n; *&n; * We don&squot;t need to keep/match the remote address in the cache because&n; * we are associated with a specific LAP (which implies it).&n; * Jean II&n; */
r_typedef
r_struct
(brace
DECL|member|valid
r_int
id|valid
suffix:semicolon
DECL|member|slsap_sel
id|__u8
id|slsap_sel
suffix:semicolon
DECL|member|dlsap_sel
id|__u8
id|dlsap_sel
suffix:semicolon
DECL|member|lsap
r_struct
id|lsap_cb
op_star
id|lsap
suffix:semicolon
DECL|typedef|CACHE_ENTRY
)brace
id|CACHE_ENTRY
suffix:semicolon
multiline_comment|/*&n; *  Information about each registred IrLAP layer&n; */
DECL|struct|lap_cb
r_struct
id|lap_cb
(brace
DECL|member|queue
id|irda_queue_t
id|queue
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
DECL|member|reason
r_int
id|reason
suffix:semicolon
multiline_comment|/* LAP disconnect reason */
DECL|member|lap_state
id|IRLMP_STATE
id|lap_state
suffix:semicolon
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
multiline_comment|/* Instance of IrLAP layer */
DECL|member|lsaps
id|hashbin_t
op_star
id|lsaps
suffix:semicolon
multiline_comment|/* LSAP associated with this link */
DECL|member|flow_next
r_struct
id|lsap_cb
op_star
id|flow_next
suffix:semicolon
multiline_comment|/* Next lsap to be polled for Tx */
DECL|member|caddr
id|__u8
id|caddr
suffix:semicolon
multiline_comment|/* Connection address */
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* Source device address */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Destination device address */
DECL|member|qos
r_struct
id|qos_info
op_star
id|qos
suffix:semicolon
multiline_comment|/* LAP QoS for this session */
DECL|member|idle_timer
r_struct
id|timer_list
id|idle_timer
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_CACHE_LAST_LSAP
multiline_comment|/* The lsap cache was moved from struct irlmp_cb to here because&n;&t; * it must be associated with the specific LAP. Also, this&n;&t; * improves performance. - Jean II */
DECL|member|cache
id|CACHE_ENTRY
id|cache
suffix:semicolon
multiline_comment|/* Caching last slsap-&gt;dlsap-&gt;handle mapping */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; *  Main structure for IrLMP&n; */
DECL|struct|irlmp_cb
r_struct
id|irlmp_cb
(brace
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
DECL|member|conflict_flag
id|__u8
id|conflict_flag
suffix:semicolon
DECL|member|discovery_cmd
id|discovery_t
id|discovery_cmd
suffix:semicolon
multiline_comment|/* Discovery command to use by IrLAP */
DECL|member|discovery_rsp
id|discovery_t
id|discovery_rsp
suffix:semicolon
multiline_comment|/* Discovery response to use by IrLAP */
multiline_comment|/* Last lsap picked automatically by irlmp_find_free_slsap() */
DECL|member|last_lsap_sel
r_int
id|last_lsap_sel
suffix:semicolon
DECL|member|discovery_timer
r_struct
id|timer_list
id|discovery_timer
suffix:semicolon
DECL|member|links
id|hashbin_t
op_star
id|links
suffix:semicolon
multiline_comment|/* IrLAP connection table */
DECL|member|unconnected_lsaps
id|hashbin_t
op_star
id|unconnected_lsaps
suffix:semicolon
DECL|member|clients
id|hashbin_t
op_star
id|clients
suffix:semicolon
DECL|member|services
id|hashbin_t
op_star
id|services
suffix:semicolon
DECL|member|cachelog
id|hashbin_t
op_star
id|cachelog
suffix:semicolon
multiline_comment|/* Current discovery log */
DECL|member|running
r_int
id|running
suffix:semicolon
DECL|member|hints
id|__u16_host_order
id|hints
suffix:semicolon
multiline_comment|/* Hint bits */
)brace
suffix:semicolon
multiline_comment|/* Prototype declarations */
r_int
id|irlmp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irlmp_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|lsap_cb
op_star
id|irlmp_open_lsap
c_func
(paren
id|__u8
id|slsap
comma
id|notify_t
op_star
id|notify
comma
id|__u8
id|pid
)paren
suffix:semicolon
r_void
id|irlmp_close_lsap
c_func
(paren
r_struct
id|lsap_cb
op_star
id|self
)paren
suffix:semicolon
id|__u16
id|irlmp_service_to_hint
c_func
(paren
r_int
id|service
)paren
suffix:semicolon
r_void
op_star
id|irlmp_register_service
c_func
(paren
id|__u16
id|hints
)paren
suffix:semicolon
r_int
id|irlmp_unregister_service
c_func
(paren
r_void
op_star
id|handle
)paren
suffix:semicolon
r_void
op_star
id|irlmp_register_client
c_func
(paren
id|__u16
id|hint_mask
comma
id|DISCOVERY_CALLBACK1
id|disco_clb
comma
id|DISCOVERY_CALLBACK2
id|expir_clb
comma
r_void
op_star
id|priv
)paren
suffix:semicolon
r_int
id|irlmp_unregister_client
c_func
(paren
r_void
op_star
id|handle
)paren
suffix:semicolon
r_int
id|irlmp_update_client
c_func
(paren
r_void
op_star
id|handle
comma
id|__u16
id|hint_mask
comma
id|DISCOVERY_CALLBACK1
id|disco_clb
comma
id|DISCOVERY_CALLBACK2
id|expir_clb
comma
r_void
op_star
id|priv
)paren
suffix:semicolon
r_void
id|irlmp_register_link
c_func
(paren
r_struct
id|irlap_cb
op_star
comma
id|__u32
id|saddr
comma
id|notify_t
op_star
)paren
suffix:semicolon
r_void
id|irlmp_unregister_link
c_func
(paren
id|__u32
id|saddr
)paren
suffix:semicolon
r_int
id|irlmp_connect_request
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
id|__u8
id|dlsap_sel
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
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlmp_connect_indication
c_func
(paren
r_struct
id|lsap_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|irlmp_connect_response
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlmp_connect_confirm
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_struct
id|lsap_cb
op_star
id|irlmp_dup
c_func
(paren
r_struct
id|lsap_cb
op_star
id|self
comma
r_void
op_star
id|instance
)paren
suffix:semicolon
r_void
id|irlmp_disconnect_indication
c_func
(paren
r_struct
id|lsap_cb
op_star
id|self
comma
id|LM_REASON
id|reason
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
suffix:semicolon
r_int
id|irlmp_disconnect_request
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
suffix:semicolon
r_void
id|irlmp_discovery_confirm
c_func
(paren
id|hashbin_t
op_star
id|discovery_log
comma
id|DISCOVERY_MODE
id|mode
)paren
suffix:semicolon
r_void
id|irlmp_discovery_request
c_func
(paren
r_int
id|nslots
)paren
suffix:semicolon
id|discinfo_t
op_star
id|irlmp_get_discoveries
c_func
(paren
r_int
op_star
id|pn
comma
id|__u16
id|mask
comma
r_int
id|nslots
)paren
suffix:semicolon
r_void
id|irlmp_do_expiry
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irlmp_do_discovery
c_func
(paren
r_int
id|nslots
)paren
suffix:semicolon
id|discovery_t
op_star
id|irlmp_get_discovery_response
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irlmp_discovery_expiry
c_func
(paren
id|discinfo_t
op_star
id|expiry
comma
r_int
id|number
)paren
suffix:semicolon
r_int
id|irlmp_data_request
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlmp_data_indication
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_int
id|irlmp_udata_request
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_void
id|irlmp_udata_indication
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_ULTRA
r_int
id|irlmp_connless_data_request
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
comma
id|__u8
)paren
suffix:semicolon
r_void
id|irlmp_connless_data_indication
c_func
(paren
r_struct
id|lsap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IRDA_ULTRA */
r_void
id|irlmp_status_request
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irlmp_status_indication
c_func
(paren
r_struct
id|lap_cb
op_star
comma
id|LINK_STATUS
id|link
comma
id|LOCK_STATUS
id|lock
)paren
suffix:semicolon
r_void
id|irlmp_flow_indication
c_func
(paren
r_struct
id|lap_cb
op_star
id|self
comma
id|LOCAL_FLOW
id|flow
)paren
suffix:semicolon
r_int
id|irlmp_slsap_inuse
c_func
(paren
id|__u8
id|slsap
)paren
suffix:semicolon
id|__u8
id|irlmp_find_free_slsap
c_func
(paren
r_void
)paren
suffix:semicolon
id|LM_REASON
id|irlmp_convert_lap_reason
c_func
(paren
id|LAP_REASON
)paren
suffix:semicolon
DECL|function|irlmp_get_saddr
r_static
r_inline
id|__u32
id|irlmp_get_saddr
c_func
(paren
r_const
r_struct
id|lsap_cb
op_star
id|self
)paren
(brace
r_return
(paren
id|self
op_logical_and
id|self-&gt;lap
)paren
ques
c_cond
id|self-&gt;lap-&gt;saddr
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|irlmp_get_daddr
r_static
r_inline
id|__u32
id|irlmp_get_daddr
c_func
(paren
r_const
r_struct
id|lsap_cb
op_star
id|self
)paren
(brace
r_return
(paren
id|self
op_logical_and
id|self-&gt;lap
)paren
ques
c_cond
id|self-&gt;lap-&gt;daddr
suffix:colon
l_int|0
suffix:semicolon
)brace
r_extern
r_const
r_char
op_star
id|irlmp_reasons
(braket
)braket
suffix:semicolon
r_extern
r_int
id|sysctl_discovery_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_discovery_slots
suffix:semicolon
r_extern
r_int
id|sysctl_discovery
suffix:semicolon
r_extern
r_int
id|sysctl_lap_keepalive_time
suffix:semicolon
multiline_comment|/* in ms, default is LM_IDLE_TIMEOUT */
r_extern
r_struct
id|irlmp_cb
op_star
id|irlmp
suffix:semicolon
multiline_comment|/* Check if LAP queue is full.&n; * Used by IrTTP for low control, see comments in irlap.h - Jean II */
DECL|function|irlmp_lap_tx_queue_full
r_static
r_inline
r_int
id|irlmp_lap_tx_queue_full
c_func
(paren
r_struct
id|lsap_cb
op_star
id|self
)paren
(brace
r_if
c_cond
(paren
id|self
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;lap
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;lap-&gt;irlap
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|IRLAP_GET_TX_QUEUE_LEN
c_func
(paren
id|self-&gt;lap-&gt;irlap
)paren
op_ge
id|LAP_HIGH_THRESHOLD
suffix:semicolon
)brace
multiline_comment|/* After doing a irlmp_dup(), this get one of the two socket back into&n; * a state where it&squot;s waiting incomming connections.&n; * Note : this can be used *only* if the socket is not yet connected&n; * (i.e. NO irlmp_connect_response() done on this socket).&n; * - Jean II */
DECL|function|irlmp_listen
r_static
r_inline
r_void
id|irlmp_listen
c_func
(paren
r_struct
id|lsap_cb
op_star
id|self
)paren
(brace
id|self-&gt;dlsap_sel
op_assign
id|LSAP_ANY
suffix:semicolon
id|self-&gt;lap
op_assign
l_int|NULL
suffix:semicolon
id|self-&gt;lsap_state
op_assign
id|LSAP_DISCONNECTED
suffix:semicolon
multiline_comment|/* Started when we received the LM_CONNECT_INDICATION */
id|del_timer
c_func
(paren
op_amp
id|self-&gt;watchdog_timer
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
