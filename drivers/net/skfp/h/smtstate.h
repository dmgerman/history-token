multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *&t;SMT state definitions&n; */
macro_line|#ifndef&t;KERNEL
multiline_comment|/*&n; * PCM states&n; */
DECL|macro|PC0_OFF
mdefine_line|#define PC0_OFF&t;&t;&t;0
DECL|macro|PC1_BREAK
mdefine_line|#define PC1_BREAK&t;&t;1
DECL|macro|PC2_TRACE
mdefine_line|#define PC2_TRACE&t;&t;2
DECL|macro|PC3_CONNECT
mdefine_line|#define PC3_CONNECT&t;&t;3
DECL|macro|PC4_NEXT
mdefine_line|#define PC4_NEXT&t;&t;4
DECL|macro|PC5_SIGNAL
mdefine_line|#define PC5_SIGNAL&t;&t;5
DECL|macro|PC6_JOIN
mdefine_line|#define PC6_JOIN&t;&t;6
DECL|macro|PC7_VERIFY
mdefine_line|#define PC7_VERIFY&t;&t;7
DECL|macro|PC8_ACTIVE
mdefine_line|#define PC8_ACTIVE&t;&t;8
DECL|macro|PC9_MAINT
mdefine_line|#define PC9_MAINT&t;&t;9
multiline_comment|/*&n; * PCM modes&n; */
DECL|macro|PM_NONE
mdefine_line|#define PM_NONE&t;&t;&t;0
DECL|macro|PM_PEER
mdefine_line|#define PM_PEER&t;&t;&t;1
DECL|macro|PM_TREE
mdefine_line|#define PM_TREE&t;&t;&t;2
multiline_comment|/*&n; * PCM type&n; */
DECL|macro|TA
mdefine_line|#define TA&t;&t;&t;0
DECL|macro|TB
mdefine_line|#define TB&t;&t;&t;1
DECL|macro|TS
mdefine_line|#define TS&t;&t;&t;2
DECL|macro|TM
mdefine_line|#define TM&t;&t;&t;3
DECL|macro|TNONE
mdefine_line|#define TNONE&t;&t;&t;4
multiline_comment|/*&n; * CFM states&n; */
DECL|macro|SC0_ISOLATED
mdefine_line|#define SC0_ISOLATED&t;0&t;&t;/* isolated */
DECL|macro|SC1_WRAP_A
mdefine_line|#define SC1_WRAP_A&t;5&t;&t;/* wrap A */
DECL|macro|SC2_WRAP_B
mdefine_line|#define SC2_WRAP_B&t;6&t;&t;/* wrap B */
DECL|macro|SC4_THRU_A
mdefine_line|#define SC4_THRU_A&t;12&t;&t;/* through A */
DECL|macro|SC5_THRU_B
mdefine_line|#define SC5_THRU_B&t;7&t;&t;/* through B (SMt 6.2) */
DECL|macro|SC7_WRAP_S
mdefine_line|#define SC7_WRAP_S&t;8&t;&t;/* SAS */
multiline_comment|/*&n; * ECM states&n; */
DECL|macro|EC0_OUT
mdefine_line|#define EC0_OUT&t;&t;0
DECL|macro|EC1_IN
mdefine_line|#define EC1_IN&t;&t;1
DECL|macro|EC2_TRACE
mdefine_line|#define EC2_TRACE&t;2
DECL|macro|EC3_LEAVE
mdefine_line|#define EC3_LEAVE&t;3
DECL|macro|EC4_PATH_TEST
mdefine_line|#define EC4_PATH_TEST&t;4
DECL|macro|EC5_INSERT
mdefine_line|#define EC5_INSERT&t;5
DECL|macro|EC6_CHECK
mdefine_line|#define EC6_CHECK&t;6
DECL|macro|EC7_DEINSERT
mdefine_line|#define EC7_DEINSERT&t;7
multiline_comment|/*&n; * RMT states&n; */
DECL|macro|RM0_ISOLATED
mdefine_line|#define RM0_ISOLATED&t;0
DECL|macro|RM1_NON_OP
mdefine_line|#define RM1_NON_OP&t;1&t;&t;/* not operational */
DECL|macro|RM2_RING_OP
mdefine_line|#define RM2_RING_OP&t;2&t;&t;/* ring operational */
DECL|macro|RM3_DETECT
mdefine_line|#define RM3_DETECT&t;3&t;&t;/* detect dupl addresses */
DECL|macro|RM4_NON_OP_DUP
mdefine_line|#define RM4_NON_OP_DUP&t;4&t;&t;/* dupl. addr detected */
DECL|macro|RM5_RING_OP_DUP
mdefine_line|#define RM5_RING_OP_DUP&t;5&t;&t;/* ring oper. with dupl. addr */
DECL|macro|RM6_DIRECTED
mdefine_line|#define RM6_DIRECTED&t;6&t;&t;/* sending directed beacons */
DECL|macro|RM7_TRACE
mdefine_line|#define RM7_TRACE&t;7&t;&t;/* trace initiated */
macro_line|#endif
DECL|struct|pcm_state
r_struct
id|pcm_state
(brace
DECL|member|pcm_type
r_int
r_char
id|pcm_type
suffix:semicolon
multiline_comment|/* TA TB TS TM */
DECL|member|pcm_state
r_int
r_char
id|pcm_state
suffix:semicolon
multiline_comment|/* state PC[0-9]_* */
DECL|member|pcm_mode
r_int
r_char
id|pcm_mode
suffix:semicolon
multiline_comment|/* PM_{NONE,PEER,TREE} */
DECL|member|pcm_neighbor
r_int
r_char
id|pcm_neighbor
suffix:semicolon
multiline_comment|/* TA TB TS TM */
DECL|member|pcm_bsf
r_int
r_char
id|pcm_bsf
suffix:semicolon
multiline_comment|/* flag bs : TRUE/FALSE */
DECL|member|pcm_lsf
r_int
r_char
id|pcm_lsf
suffix:semicolon
multiline_comment|/* flag ls : TRUE/FALSE */
DECL|member|pcm_lct_fail
r_int
r_char
id|pcm_lct_fail
suffix:semicolon
multiline_comment|/* counter lct_fail */
DECL|member|pcm_ls_rx
r_int
r_char
id|pcm_ls_rx
suffix:semicolon
multiline_comment|/* rx line state */
DECL|member|pcm_r_val
r_int
id|pcm_r_val
suffix:semicolon
multiline_comment|/* signaling bits */
DECL|member|pcm_t_val
r_int
id|pcm_t_val
suffix:semicolon
multiline_comment|/* signaling bits */
)brace
suffix:semicolon
DECL|struct|smt_state
r_struct
id|smt_state
(brace
DECL|member|pcm_state
r_struct
id|pcm_state
id|pcm_state
(braket
id|NUMPHYS
)braket
suffix:semicolon
multiline_comment|/* port A &amp; port B */
)brace
suffix:semicolon
eof
