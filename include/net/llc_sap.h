macro_line|#ifndef LLC_SAP_H
DECL|macro|LLC_SAP_H
mdefine_line|#define LLC_SAP_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology,Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/llc_if.h&gt;
multiline_comment|/**&n; * struct llc_sap - Defines the SAP component&n; *&n; * @station - station this sap belongs to&n; * @state - sap state&n; * @p_bit - only lowest-order bit used&n; * @f_bit - only lowest-order bit used&n; * @laddr - SAP value in this &squot;lsap&squot;&n; * @node - entry in station sap_list&n; * @sk_list - LLC sockets this one manages&n; */
DECL|struct|llc_sap
r_struct
id|llc_sap
(brace
DECL|member|station
r_struct
id|llc_station
op_star
id|station
suffix:semicolon
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|p_bit
id|u8
id|p_bit
suffix:semicolon
DECL|member|f_bit
id|u8
id|f_bit
suffix:semicolon
DECL|member|rcv_func
r_int
(paren
op_star
id|rcv_func
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|packet_type
op_star
id|pt
)paren
suffix:semicolon
DECL|member|laddr
r_struct
id|llc_addr
id|laddr
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
r_struct
(brace
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|list
r_struct
id|hlist_head
id|list
suffix:semicolon
DECL|member|sk_list
)brace
id|sk_list
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|llc_sap_state_process
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|llc_sap_rtn_pdu
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|llc_save_primitive
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|prim
)paren
suffix:semicolon
r_extern
r_struct
id|llc_sap
op_star
id|llc_sap_open
c_func
(paren
id|u8
id|lsap
comma
r_int
(paren
op_star
id|rcv
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|packet_type
op_star
id|pt
)paren
)paren
suffix:semicolon
r_extern
r_void
id|llc_sap_close
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
suffix:semicolon
r_extern
r_void
id|llc_build_and_send_ui_pkt
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|dmac
comma
id|u8
id|dsap
)paren
suffix:semicolon
r_extern
r_void
id|llc_build_and_send_xid_pkt
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|dmac
comma
id|u8
id|dsap
)paren
suffix:semicolon
r_extern
r_void
id|llc_build_and_send_test_pkt
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|dmac
comma
id|u8
id|dsap
)paren
suffix:semicolon
macro_line|#endif /* LLC_SAP_H */
eof
