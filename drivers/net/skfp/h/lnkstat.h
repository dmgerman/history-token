multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Definition of the Error Log Structure&n; * This structure will be copied into the Error Log buffer&n; * during the NDIS General Request ReadErrorLog by the MAC Driver&n; */
DECL|struct|s_error_log
r_struct
id|s_error_log
(brace
multiline_comment|/*&n;&t; * place holder for token ring adapter error log (zeros)&n;&t; */
DECL|member|reserved_0
id|u_char
id|reserved_0
suffix:semicolon
multiline_comment|/* byte 0 inside Error Log */
DECL|member|reserved_1
id|u_char
id|reserved_1
suffix:semicolon
multiline_comment|/* byte 1 */
DECL|member|reserved_2
id|u_char
id|reserved_2
suffix:semicolon
multiline_comment|/* byte 2 */
DECL|member|reserved_3
id|u_char
id|reserved_3
suffix:semicolon
multiline_comment|/* byte 3 */
DECL|member|reserved_4
id|u_char
id|reserved_4
suffix:semicolon
multiline_comment|/* byte 4 */
DECL|member|reserved_5
id|u_char
id|reserved_5
suffix:semicolon
multiline_comment|/* byte 5 */
DECL|member|reserved_6
id|u_char
id|reserved_6
suffix:semicolon
multiline_comment|/* byte 6 */
DECL|member|reserved_7
id|u_char
id|reserved_7
suffix:semicolon
multiline_comment|/* byte 7 */
DECL|member|reserved_8
id|u_char
id|reserved_8
suffix:semicolon
multiline_comment|/* byte 8 */
DECL|member|reserved_9
id|u_char
id|reserved_9
suffix:semicolon
multiline_comment|/* byte 9 */
DECL|member|reserved_10
id|u_char
id|reserved_10
suffix:semicolon
multiline_comment|/* byte 10 */
DECL|member|reserved_11
id|u_char
id|reserved_11
suffix:semicolon
multiline_comment|/* byte 11 */
DECL|member|reserved_12
id|u_char
id|reserved_12
suffix:semicolon
multiline_comment|/* byte 12 */
DECL|member|reserved_13
id|u_char
id|reserved_13
suffix:semicolon
multiline_comment|/* byte 13 */
multiline_comment|/*&n;&t; * FDDI link statistics &n;&t; */
multiline_comment|/*&n; * smt error low&n; */
DECL|macro|SMT_ERL_AEB
mdefine_line|#define SMT_ERL_AEB&t;(1&lt;&lt;15)&t;&t;&t;/* A elast. buffer */
DECL|macro|SMT_ERL_BLC
mdefine_line|#define SMT_ERL_BLC&t;(1&lt;&lt;14)&t;&t;&t;/* B link error condition */
DECL|macro|SMT_ERL_ALC
mdefine_line|#define SMT_ERL_ALC&t;(1&lt;&lt;13)&t;&t;&t;/* A link error condition */
DECL|macro|SMT_ERL_NCC
mdefine_line|#define SMT_ERL_NCC&t;(1&lt;&lt;12)&t;&t;&t;/* not copied condition */
DECL|macro|SMT_ERL_FEC
mdefine_line|#define SMT_ERL_FEC&t;(1&lt;&lt;11)&t;&t;&t;/* frame error condition */
multiline_comment|/*&n; * smt event low&n; */
DECL|macro|SMT_EVL_NCE
mdefine_line|#define SMT_EVL_NCE&t;(1&lt;&lt;5)
DECL|member|smt_error_low
id|u_short
id|smt_error_low
suffix:semicolon
multiline_comment|/* byte 14/15 */
DECL|member|smt_error_high
id|u_short
id|smt_error_high
suffix:semicolon
multiline_comment|/* byte 16/17 */
DECL|member|smt_event_low
id|u_short
id|smt_event_low
suffix:semicolon
multiline_comment|/* byte 18/19 */
DECL|member|smt_event_high
id|u_short
id|smt_event_high
suffix:semicolon
multiline_comment|/* byte 20/21 */
DECL|member|connection_policy_violation
id|u_short
id|connection_policy_violation
suffix:semicolon
multiline_comment|/* byte 22/23 */
DECL|member|port_event
id|u_short
id|port_event
suffix:semicolon
multiline_comment|/* byte 24/25 */
DECL|member|set_count_low
id|u_short
id|set_count_low
suffix:semicolon
multiline_comment|/* byte 26/27 */
DECL|member|set_count_high
id|u_short
id|set_count_high
suffix:semicolon
multiline_comment|/* byte 28/29 */
DECL|member|aci_id_code
id|u_short
id|aci_id_code
suffix:semicolon
multiline_comment|/* byte 30/31 */
DECL|member|purge_frame_counter
id|u_short
id|purge_frame_counter
suffix:semicolon
multiline_comment|/* byte 32/33 */
multiline_comment|/*&n;&t; * CMT and RMT state machines&n;&t; */
DECL|member|ecm_state
id|u_short
id|ecm_state
suffix:semicolon
multiline_comment|/* byte 34/35 */
DECL|member|pcm_a_state
id|u_short
id|pcm_a_state
suffix:semicolon
multiline_comment|/* byte 36/37 */
DECL|member|pcm_b_state
id|u_short
id|pcm_b_state
suffix:semicolon
multiline_comment|/* byte 38/39 */
DECL|member|cfm_state
id|u_short
id|cfm_state
suffix:semicolon
multiline_comment|/* byte 40/41 */
DECL|member|rmt_state
id|u_short
id|rmt_state
suffix:semicolon
multiline_comment|/* byte 42/43 */
DECL|member|not_used
id|u_short
id|not_used
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* byte 44-103 */
DECL|member|ucode_version_level
id|u_short
id|ucode_version_level
suffix:semicolon
multiline_comment|/* byte 104/105 */
DECL|member|not_used_1
id|u_short
id|not_used_1
suffix:semicolon
multiline_comment|/* byte 106/107 */
DECL|member|not_used_2
id|u_short
id|not_used_2
suffix:semicolon
multiline_comment|/* byte 108/109 */
)brace
suffix:semicolon
eof
