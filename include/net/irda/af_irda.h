multiline_comment|/*********************************************************************&n; *                &n; * Filename:      af_irda.h&n; * Version:       1.0&n; * Description:   IrDA sockets declarations&n; * Status:        Stable&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Dec  9 21:13:12 1997&n; * Modified at:   Fri Jan 28 13:16:32 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-2000 Dag Brattli, All Rights Reserved.&n; *     Copyright (c) 2000-2002 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef AF_IRDA_H
DECL|macro|AF_IRDA_H
mdefine_line|#define AF_IRDA_H
macro_line|#include &lt;linux/irda.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/iriap.h&gt;&t;&t;/* struct iriap_cb */
macro_line|#include &lt;net/irda/irias_object.h&gt;&t;/* struct ias_value */
macro_line|#include &lt;net/irda/irlmp.h&gt;&t;&t;/* struct lsap_cb */
macro_line|#include &lt;net/irda/irttp.h&gt;&t;&t;/* struct tsap_cb */
macro_line|#include &lt;net/irda/discovery.h&gt;&t;&t;/* struct discovery_t */
multiline_comment|/* IrDA Socket */
DECL|struct|irda_sock
r_struct
id|irda_sock
(brace
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* my local address */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* peer address */
DECL|member|lsap
r_struct
id|lsap_cb
op_star
id|lsap
suffix:semicolon
multiline_comment|/* LSAP used by Ultra */
DECL|member|pid
id|__u8
id|pid
suffix:semicolon
multiline_comment|/* Protocol IP (PID) used by Ultra */
DECL|member|tsap
r_struct
id|tsap_cb
op_star
id|tsap
suffix:semicolon
multiline_comment|/* TSAP used by this connection */
DECL|member|dtsap_sel
id|__u8
id|dtsap_sel
suffix:semicolon
multiline_comment|/* remote TSAP address */
DECL|member|stsap_sel
id|__u8
id|stsap_sel
suffix:semicolon
multiline_comment|/* local TSAP address */
DECL|member|max_sdu_size_rx
id|__u32
id|max_sdu_size_rx
suffix:semicolon
DECL|member|max_sdu_size_tx
id|__u32
id|max_sdu_size_tx
suffix:semicolon
DECL|member|max_data_size
id|__u32
id|max_data_size
suffix:semicolon
DECL|member|max_header_size
id|__u8
id|max_header_size
suffix:semicolon
DECL|member|qos_tx
r_struct
id|qos_info
id|qos_tx
suffix:semicolon
DECL|member|mask
id|__u16
id|mask
suffix:semicolon
multiline_comment|/* Hint bits mask */
DECL|member|hints
id|__u16
id|hints
suffix:semicolon
multiline_comment|/* Hint bits */
DECL|member|ckey
id|__u32
id|ckey
suffix:semicolon
multiline_comment|/* IrLMP client handle */
DECL|member|skey
id|__u32
id|skey
suffix:semicolon
multiline_comment|/* IrLMP service handle */
DECL|member|ias_obj
r_struct
id|ias_object
op_star
id|ias_obj
suffix:semicolon
multiline_comment|/* Our service name + lsap in IAS */
DECL|member|iriap
r_struct
id|iriap_cb
op_star
id|iriap
suffix:semicolon
multiline_comment|/* Used to query remote IAS */
DECL|member|ias_result
r_struct
id|ias_value
op_star
id|ias_result
suffix:semicolon
multiline_comment|/* Result of remote IAS query */
DECL|member|cachelog
id|hashbin_t
op_star
id|cachelog
suffix:semicolon
multiline_comment|/* Result of discovery query */
DECL|member|cachediscovery
r_struct
id|discovery_t
op_star
id|cachediscovery
suffix:semicolon
multiline_comment|/* Result of selective discovery query */
DECL|member|nslots
r_int
id|nslots
suffix:semicolon
multiline_comment|/* Number of slots to use for discovery */
DECL|member|errno
r_int
id|errno
suffix:semicolon
multiline_comment|/* status of the IAS query */
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|query_wait
id|wait_queue_head_t
id|query_wait
suffix:semicolon
multiline_comment|/* Wait for the answer to a query */
DECL|member|watchdog
r_struct
id|timer_list
id|watchdog
suffix:semicolon
multiline_comment|/* Timeout for discovery */
DECL|member|tx_flow
id|LOCAL_FLOW
id|tx_flow
suffix:semicolon
DECL|member|rx_flow
id|LOCAL_FLOW
id|rx_flow
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|irda_sk
mdefine_line|#define irda_sk(__sk) ((struct irda_sock *)(__sk)-&gt;protinfo)
macro_line|#endif /* AF_IRDA_H */
eof
