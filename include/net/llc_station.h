macro_line|#ifndef LLC_STATION_H
DECL|macro|LLC_STATION_H
mdefine_line|#define LLC_STATION_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001-2003 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/skbuff.h&gt;
DECL|macro|LLC_EVENT
mdefine_line|#define LLC_EVENT&t;&t; 1
DECL|macro|LLC_PACKET
mdefine_line|#define LLC_PACKET&t;&t; 2
DECL|macro|LLC_TYPE_1
mdefine_line|#define LLC_TYPE_1&t;&t; 1
DECL|macro|LLC_TYPE_2
mdefine_line|#define LLC_TYPE_2&t;&t; 2
DECL|macro|LLC_P_TIME
mdefine_line|#define LLC_P_TIME&t;&t; 2
DECL|macro|LLC_ACK_TIME
mdefine_line|#define LLC_ACK_TIME&t;&t; 1
DECL|macro|LLC_REJ_TIME
mdefine_line|#define LLC_REJ_TIME&t;&t; 3
DECL|macro|LLC_BUSY_TIME
mdefine_line|#define LLC_BUSY_TIME&t;&t; 3
multiline_comment|/**&n; * struct llc_station - LLC station component&n; *&n; * SAP and connection resource manager, one per adapter.&n; *&n; * @state - state of station&n; * @xid_r_count - XID response PDU counter&n; * @mac_sa - MAC source address&n; * @sap_list - list of related SAPs&n; * @ev_q - events entering state mach.&n; * @mac_pdu_q - PDUs ready to send to MAC&n; */
DECL|struct|llc_station
r_struct
id|llc_station
(brace
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|xid_r_count
id|u8
id|xid_r_count
suffix:semicolon
DECL|member|ack_timer
r_struct
id|timer_list
id|ack_timer
suffix:semicolon
DECL|member|retry_count
id|u8
id|retry_count
suffix:semicolon
DECL|member|maximum_retry
id|u8
id|maximum_retry
suffix:semicolon
r_struct
(brace
DECL|member|list
r_struct
id|sk_buff_head
id|list
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ev_q
)brace
id|ev_q
suffix:semicolon
DECL|member|mac_pdu_q
r_struct
id|sk_buff_head
id|mac_pdu_q
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|__init
id|llc_station_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__exit
id|llc_station_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* LLC_STATION_H */
eof
