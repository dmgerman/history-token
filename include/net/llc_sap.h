macro_line|#ifndef LLC_SAP_H
DECL|macro|LLC_SAP_H
mdefine_line|#define LLC_SAP_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology,Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/**&n; * struct llc_sap - Defines the SAP component&n; *&n; * @p_bit - only lowest-order bit used&n; * @f_bit - only lowest-order bit used&n; * @ind - provided by network layer&n; * @conf - provided by network layer&n; * @laddr - SAP value in this &squot;lsap&squot;&n; * @node - entry in station sap_list&n; * @sk_list - LLC sockets this one manages&n; * @mac_pdu_q - PDUs ready to send to MAC&n; */
DECL|struct|llc_sap
r_struct
id|llc_sap
(brace
DECL|member|parent_station
r_struct
id|llc_station
op_star
id|parent_station
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
DECL|member|ind
id|llc_prim_call_t
id|ind
suffix:semicolon
DECL|member|conf
id|llc_prim_call_t
id|conf
suffix:semicolon
DECL|member|llc_ind_prim
DECL|member|llc_cfm_prim
r_struct
id|llc_prim_if_block
id|llc_ind_prim
comma
id|llc_cfm_prim
suffix:semicolon
DECL|member|llc_ind_data_prim
DECL|member|llc_cfm_data_prim
r_union
id|llc_u_prim_data
id|llc_ind_data_prim
comma
id|llc_cfm_data_prim
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
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|sk_list
)brace
id|sk_list
suffix:semicolon
DECL|member|mac_pdu_q
r_struct
id|sk_buff_head
id|mac_pdu_q
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|llc_sap_state_ev
suffix:semicolon
r_extern
r_void
id|llc_sap_assign_sock
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_void
id|llc_sap_unassign_sock
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sock
op_star
id|sk
)paren
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
id|llc_sap_send_pdu
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
macro_line|#endif /* LLC_SAP_H */
eof
