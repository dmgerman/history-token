macro_line|#ifndef LLC_S_ST_H
DECL|macro|LLC_S_ST_H
mdefine_line|#define LLC_S_ST_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology,Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
multiline_comment|/* Defines SAP component states */
DECL|macro|LLC_SAP_STATE_INACTIVE
mdefine_line|#define LLC_SAP_STATE_INACTIVE&t;1
DECL|macro|LLC_SAP_STATE_ACTIVE
mdefine_line|#define LLC_SAP_STATE_ACTIVE&t;2
DECL|macro|LLC_NBR_SAP_STATES
mdefine_line|#define LLC_NBR_SAP_STATES&t;2       /* size of state table */
multiline_comment|/* structures and types */
multiline_comment|/* SAP state table structure */
DECL|struct|llc_sap_state_trans
r_struct
id|llc_sap_state_trans
(brace
DECL|member|ev
id|llc_sap_ev_t
id|ev
suffix:semicolon
DECL|member|next_state
id|u8
id|next_state
suffix:semicolon
DECL|member|ev_actions
id|llc_sap_action_t
op_star
id|ev_actions
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|llc_sap_state
r_struct
id|llc_sap_state
(brace
DECL|member|curr_state
id|u8
id|curr_state
suffix:semicolon
DECL|member|transitions
r_struct
id|llc_sap_state_trans
op_star
op_star
id|transitions
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* only access to SAP state table */
r_extern
r_struct
id|llc_sap_state
id|llc_sap_state_table
(braket
id|LLC_NBR_SAP_STATES
)braket
suffix:semicolon
macro_line|#endif /* LLC_S_ST_H */
eof
