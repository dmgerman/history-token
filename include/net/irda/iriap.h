multiline_comment|/*********************************************************************&n; *                &n; * Filename:      iriap.h&n; * Version:       0.5&n; * Description:   Information Access Protocol (IAP)&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Thu Aug 21 00:02:07 1997&n; * Modified at:   Sat Dec 25 16:42:09 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1997-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRIAP_H
DECL|macro|IRIAP_H
mdefine_line|#define IRIAP_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/irda/iriap_event.h&gt;
macro_line|#include &lt;net/irda/irias_object.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;&t;&t;/* irda_queue_t */
macro_line|#include &lt;net/irda/timer.h&gt;&t;&t;/* struct timer_list */
DECL|macro|IAP_LST
mdefine_line|#define IAP_LST 0x80
DECL|macro|IAP_ACK
mdefine_line|#define IAP_ACK 0x40
DECL|macro|IAS_SERVER
mdefine_line|#define IAS_SERVER 0
DECL|macro|IAS_CLIENT
mdefine_line|#define IAS_CLIENT 1
multiline_comment|/* IrIAP Op-codes */
DECL|macro|GET_INFO_BASE
mdefine_line|#define GET_INFO_BASE      0x01
DECL|macro|GET_OBJECTS
mdefine_line|#define GET_OBJECTS        0x02
DECL|macro|GET_VALUE
mdefine_line|#define GET_VALUE          0x03
DECL|macro|GET_VALUE_BY_CLASS
mdefine_line|#define GET_VALUE_BY_CLASS 0x04
DECL|macro|GET_OBJECT_INFO
mdefine_line|#define GET_OBJECT_INFO    0x05
DECL|macro|GET_ATTRIB_NAMES
mdefine_line|#define GET_ATTRIB_NAMES   0x06
DECL|macro|IAS_SUCCESS
mdefine_line|#define IAS_SUCCESS        0
DECL|macro|IAS_CLASS_UNKNOWN
mdefine_line|#define IAS_CLASS_UNKNOWN  1
DECL|macro|IAS_ATTRIB_UNKNOWN
mdefine_line|#define IAS_ATTRIB_UNKNOWN 2
DECL|macro|IAS_DISCONNECT
mdefine_line|#define IAS_DISCONNECT     10
DECL|typedef|CONFIRM_CALLBACK
r_typedef
r_void
(paren
op_star
id|CONFIRM_CALLBACK
)paren
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
suffix:semicolon
DECL|struct|iriap_cb
r_struct
id|iriap_cb
(brace
DECL|member|q
id|irda_queue_t
id|q
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
multiline_comment|/* Magic cookie */
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/* Client or server */
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
DECL|member|operation
id|__u8
id|operation
suffix:semicolon
DECL|member|request_skb
r_struct
id|sk_buff
op_star
id|request_skb
suffix:semicolon
DECL|member|lsap
r_struct
id|lsap_cb
op_star
id|lsap
suffix:semicolon
DECL|member|slsap_sel
id|__u8
id|slsap_sel
suffix:semicolon
multiline_comment|/* Client states */
DECL|member|client_state
id|IRIAP_STATE
id|client_state
suffix:semicolon
DECL|member|call_state
id|IRIAP_STATE
id|call_state
suffix:semicolon
multiline_comment|/* Server states */
DECL|member|server_state
id|IRIAP_STATE
id|server_state
suffix:semicolon
DECL|member|r_connect_state
id|IRIAP_STATE
id|r_connect_state
suffix:semicolon
DECL|member|confirm
id|CONFIRM_CALLBACK
id|confirm
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* Used to identify client */
DECL|member|max_header_size
id|__u8
id|max_header_size
suffix:semicolon
DECL|member|max_data_size
id|__u32
id|max_data_size
suffix:semicolon
DECL|member|watchdog_timer
r_struct
id|timer_list
id|watchdog_timer
suffix:semicolon
)brace
suffix:semicolon
r_int
id|iriap_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|iriap_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|iriap_cb
op_star
id|iriap_open
c_func
(paren
id|__u8
id|slsap_sel
comma
r_int
id|mode
comma
r_void
op_star
id|priv
comma
id|CONFIRM_CALLBACK
id|callback
)paren
suffix:semicolon
r_void
id|iriap_close
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
)paren
suffix:semicolon
r_int
id|iriap_getvaluebyclass_request
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
id|__u32
id|saddr
comma
id|__u32
id|daddr
comma
r_char
op_star
id|name
comma
r_char
op_star
id|attr
)paren
suffix:semicolon
r_void
id|iriap_connect_request
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|iriap_send_ack
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|iriap_call_indication
c_func
(paren
r_struct
id|iriap_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|iriap_register_server
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
