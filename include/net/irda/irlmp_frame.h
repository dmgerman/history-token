multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlmp_frame.h&n; * Version:       0.9&n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Aug 19 02:09:59 1997&n; * Modified at:   Fri Dec 10 13:21:53 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1997, 1999 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRMLP_FRAME_H
DECL|macro|IRMLP_FRAME_H
mdefine_line|#define IRMLP_FRAME_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/irda/discovery.h&gt;
multiline_comment|/* IrLMP frame opcodes */
DECL|macro|CONNECT_CMD
mdefine_line|#define CONNECT_CMD    0x01
DECL|macro|CONNECT_CNF
mdefine_line|#define CONNECT_CNF    0x81
DECL|macro|DISCONNECT
mdefine_line|#define DISCONNECT     0x02
DECL|macro|ACCESSMODE_CMD
mdefine_line|#define ACCESSMODE_CMD 0x03
DECL|macro|ACCESSMODE_CNF
mdefine_line|#define ACCESSMODE_CNF 0x83
DECL|macro|CONTROL_BIT
mdefine_line|#define CONTROL_BIT    0x80
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
suffix:semicolon
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
suffix:semicolon
r_void
id|irlmp_link_data_indication
c_func
(paren
r_struct
id|lap_cb
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_int
id|unreliable
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_ULTRA
r_void
id|irlmp_link_unitdata_indication
c_func
(paren
r_struct
id|lap_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IRDA_ULTRA */
r_void
id|irlmp_link_connect_indication
c_func
(paren
r_struct
id|lap_cb
op_star
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
suffix:semicolon
r_void
id|irlmp_link_connect_request
c_func
(paren
id|__u32
id|daddr
)paren
suffix:semicolon
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
id|skb
)paren
suffix:semicolon
r_void
id|irlmp_link_disconnect_indication
c_func
(paren
r_struct
id|lap_cb
op_star
comma
r_struct
id|irlap_cb
op_star
comma
id|LAP_REASON
id|reason
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
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
suffix:semicolon
r_void
id|irlmp_link_discovery_indication
c_func
(paren
r_struct
id|lap_cb
op_star
comma
id|discovery_t
op_star
id|discovery
)paren
suffix:semicolon
macro_line|#endif
eof
