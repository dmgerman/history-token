macro_line|#ifndef LLC_STAT_H
DECL|macro|LLC_STAT_H
mdefine_line|#define LLC_STAT_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology,Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
multiline_comment|/* Station component state table */
multiline_comment|/* Station component states */
DECL|macro|LLC_STATION_STATE_DOWN
mdefine_line|#define LLC_STATION_STATE_DOWN&t;&t;1&t;/* initial state */
DECL|macro|LLC_STATION_STATE_DUP_ADDR_CHK
mdefine_line|#define LLC_STATION_STATE_DUP_ADDR_CHK&t;2
DECL|macro|LLC_STATION_STATE_UP
mdefine_line|#define LLC_STATION_STATE_UP&t;&t;3
DECL|macro|LLC_NBR_STATION_STATES
mdefine_line|#define LLC_NBR_STATION_STATES&t;&t;3&t;/* size of state table */
multiline_comment|/* Station component state table structure */
DECL|struct|llc_station_state_trans
r_struct
id|llc_station_state_trans
(brace
DECL|member|ev
id|llc_station_ev_t
id|ev
suffix:semicolon
DECL|member|next_state
id|u8
id|next_state
suffix:semicolon
DECL|member|ev_actions
id|llc_station_action_t
op_star
id|ev_actions
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|llc_station_state
r_struct
id|llc_station_state
(brace
DECL|member|curr_state
id|u8
id|curr_state
suffix:semicolon
DECL|member|transitions
r_struct
id|llc_station_state_trans
op_star
op_star
id|transitions
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|llc_station_state
id|llc_station_state_table
(braket
id|LLC_NBR_STATION_STATES
)braket
suffix:semicolon
macro_line|#endif /* LLC_STAT_H */
eof
