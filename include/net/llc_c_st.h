macro_line|#ifndef LLC_C_ST_H
DECL|macro|LLC_C_ST_H
mdefine_line|#define LLC_C_ST_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology,Inc.&n; *&t;&t;2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
multiline_comment|/* Connection component state management */
multiline_comment|/* connection states */
DECL|macro|LLC_CONN_OUT_OF_SVC
mdefine_line|#define LLC_CONN_OUT_OF_SVC&t;&t; 0&t;/* prior to allocation */
DECL|macro|LLC_CONN_STATE_ADM
mdefine_line|#define LLC_CONN_STATE_ADM&t;&t; 1&t;/* disc, initial state */
DECL|macro|LLC_CONN_STATE_SETUP
mdefine_line|#define LLC_CONN_STATE_SETUP&t;&t; 2&t;/* disconnected state */
DECL|macro|LLC_CONN_STATE_NORMAL
mdefine_line|#define LLC_CONN_STATE_NORMAL&t;&t; 3&t;/* connected state */
DECL|macro|LLC_CONN_STATE_BUSY
mdefine_line|#define LLC_CONN_STATE_BUSY&t;&t; 4&t;/* connected state */
DECL|macro|LLC_CONN_STATE_REJ
mdefine_line|#define LLC_CONN_STATE_REJ&t;&t; 5&t;/* connected state */
DECL|macro|LLC_CONN_STATE_AWAIT
mdefine_line|#define LLC_CONN_STATE_AWAIT&t;&t; 6&t;/* connected state */
DECL|macro|LLC_CONN_STATE_AWAIT_BUSY
mdefine_line|#define LLC_CONN_STATE_AWAIT_BUSY&t; 7&t;/* connected state */
DECL|macro|LLC_CONN_STATE_AWAIT_REJ
mdefine_line|#define LLC_CONN_STATE_AWAIT_REJ&t; 8&t;/* connected state */
DECL|macro|LLC_CONN_STATE_D_CONN
mdefine_line|#define LLC_CONN_STATE_D_CONN&t;&t; 9&t;/* disconnected state */
DECL|macro|LLC_CONN_STATE_RESET
mdefine_line|#define LLC_CONN_STATE_RESET&t;&t;10&t;/* disconnected state */
DECL|macro|LLC_CONN_STATE_ERROR
mdefine_line|#define LLC_CONN_STATE_ERROR&t;&t;11&t;/* disconnected state */
DECL|macro|LLC_CONN_STATE_TEMP
mdefine_line|#define LLC_CONN_STATE_TEMP&t;&t;12&t;/* disconnected state */
DECL|macro|NBR_CONN_STATES
mdefine_line|#define NBR_CONN_STATES&t;&t;&t;12&t;/* size of state table */
DECL|macro|NO_STATE_CHANGE
mdefine_line|#define NO_STATE_CHANGE&t;&t;&t;100
multiline_comment|/* Connection state table structure */
DECL|struct|llc_conn_state_trans
r_struct
id|llc_conn_state_trans
(brace
DECL|member|ev
id|llc_conn_ev_t
id|ev
suffix:semicolon
DECL|member|next_state
id|u8
id|next_state
suffix:semicolon
DECL|member|ev_qualifiers
id|llc_conn_ev_qfyr_t
op_star
id|ev_qualifiers
suffix:semicolon
DECL|member|ev_actions
id|llc_conn_action_t
op_star
id|ev_actions
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|llc_conn_state
r_struct
id|llc_conn_state
(brace
DECL|member|current_state
id|u8
id|current_state
suffix:semicolon
DECL|member|transitions
r_struct
id|llc_conn_state_trans
op_star
op_star
id|transitions
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|llc_conn_state
id|llc_conn_state_table
(braket
)braket
suffix:semicolon
macro_line|#endif /* LLC_C_ST_H */
eof
