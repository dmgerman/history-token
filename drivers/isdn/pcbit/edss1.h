multiline_comment|/*&n; * DSS.1 module definitions&n; *&n; * Copyright (C) 1996 Universidade de Lisboa&n; * &n; * Written by Pedro Roque Marques (roque@di.fc.ul.pt)&n; *&n; * This software may be used and distributed according to the terms of &n; * the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#ifndef EDSS1_H
DECL|macro|EDSS1_H
mdefine_line|#define EDSS1_H
multiline_comment|/* ISDN states */
DECL|macro|ST_NULL
mdefine_line|#define ST_NULL      0
DECL|macro|ST_CALL_INIT
mdefine_line|#define ST_CALL_INIT 1    /* Call initiated */
DECL|macro|ST_OVER_SEND
mdefine_line|#define ST_OVER_SEND 2    /* Overlap sending - Requests More Info 4 call */
DECL|macro|ST_CALL_PROC
mdefine_line|#define ST_CALL_PROC 3    /* Call Proceeding */
DECL|macro|ST_CALL_DELV
mdefine_line|#define ST_CALL_DELV 4
DECL|macro|ST_CALL_PRES
mdefine_line|#define ST_CALL_PRES 6    /* Call Present - Received CONN.IND */
DECL|macro|ST_CALL_RECV
mdefine_line|#define ST_CALL_RECV 7    /* Alerting sent */
DECL|macro|ST_CONN_REQ
mdefine_line|#define ST_CONN_REQ  8    /* Answered - waiting 4 CONN.CONF */
DECL|macro|ST_INCM_PROC
mdefine_line|#define ST_INCM_PROC 9
DECL|macro|ST_ACTIVE
mdefine_line|#define ST_ACTIVE    10
DECL|macro|ST_DISC_REQ
mdefine_line|#define ST_DISC_REQ  11
DECL|macro|ST_DISC_IND
mdefine_line|#define ST_DISC_IND  12
DECL|macro|ST_SUSP_REQ
mdefine_line|#define ST_SUSP_REQ  15
DECL|macro|ST_RESM_REQ
mdefine_line|#define ST_RESM_REQ  17
DECL|macro|ST_RELS_REQ
mdefine_line|#define ST_RELS_REQ  19
DECL|macro|ST_OVER_RECV
mdefine_line|#define ST_OVER_RECV 25
DECL|macro|ST_ACTIVE_SELP
mdefine_line|#define ST_ACTIVE_SELP 26 /* Select protocol on B-Channel */
DECL|macro|ST_ACTIVE_ACTV
mdefine_line|#define ST_ACTIVE_ACTV 27 /* Activate B-channel protocol  */
DECL|macro|MAX_STATE
mdefine_line|#define MAX_STATE ST_ACTIVE_ACTV
DECL|macro|EV_NULL
mdefine_line|#define EV_NULL               0
DECL|macro|EV_USR_SETUP_REQ
mdefine_line|#define EV_USR_SETUP_REQ      1
DECL|macro|EV_USR_SETUP_RESP
mdefine_line|#define EV_USR_SETUP_RESP     2
DECL|macro|EV_USR_PROCED_REQ
mdefine_line|#define EV_USR_PROCED_REQ     3
DECL|macro|EV_USR_RELEASE_REQ
mdefine_line|#define EV_USR_RELEASE_REQ    4
DECL|macro|EV_USR_REJECT_REQ
mdefine_line|#define EV_USR_REJECT_REQ     4
DECL|macro|EV_NET_SETUP
mdefine_line|#define EV_NET_SETUP          16
DECL|macro|EV_NET_CALL_PROC
mdefine_line|#define EV_NET_CALL_PROC      17
DECL|macro|EV_NET_SETUP_ACK
mdefine_line|#define EV_NET_SETUP_ACK      18
DECL|macro|EV_NET_CONN
mdefine_line|#define EV_NET_CONN           19
DECL|macro|EV_NET_CONN_ACK
mdefine_line|#define EV_NET_CONN_ACK       20
DECL|macro|EV_NET_SELP_RESP
mdefine_line|#define EV_NET_SELP_RESP      21
DECL|macro|EV_NET_ACTV_RESP
mdefine_line|#define EV_NET_ACTV_RESP      22
DECL|macro|EV_NET_DISC
mdefine_line|#define EV_NET_DISC           23
DECL|macro|EV_NET_RELEASE
mdefine_line|#define EV_NET_RELEASE        24
DECL|macro|EV_NET_RELEASE_COMP
mdefine_line|#define EV_NET_RELEASE_COMP   25
DECL|macro|EV_TIMER
mdefine_line|#define EV_TIMER              26
DECL|macro|EV_ERROR
mdefine_line|#define EV_ERROR              32
multiline_comment|/*&n; *  Cause values&n; *  only the ones we use&n; */
DECL|macro|CAUSE_NORMAL
mdefine_line|#define CAUSE_NORMAL          0x10U 
DECL|macro|CAUSE_NOCHAN
mdefine_line|#define CAUSE_NOCHAN          0x22U
DECL|struct|callb_data
r_struct
id|callb_data
(brace
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
r_union
(brace
DECL|struct|ConnInfo
r_struct
id|ConnInfo
(brace
DECL|member|CalledPN
r_char
op_star
id|CalledPN
suffix:semicolon
DECL|member|CallingPN
r_char
op_star
id|CallingPN
suffix:semicolon
DECL|member|setup
)brace
id|setup
suffix:semicolon
DECL|member|cause
r_int
r_int
id|cause
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fsm_entry
r_struct
id|fsm_entry
(brace
DECL|member|init
r_int
r_int
id|init
suffix:semicolon
DECL|member|final
r_int
r_int
id|final
suffix:semicolon
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
DECL|member|callb
r_void
(paren
op_star
id|callb
)paren
(paren
r_struct
id|pcbit_dev
op_star
comma
r_struct
id|pcbit_chan
op_star
comma
r_struct
id|callb_data
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fsm_timer_entry
r_struct
id|fsm_timer_entry
(brace
DECL|member|init
r_int
r_int
id|init
suffix:semicolon
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* in seconds */
)brace
suffix:semicolon
r_extern
r_void
id|pcbit_fsm_event
c_func
(paren
r_struct
id|pcbit_dev
op_star
comma
r_struct
id|pcbit_chan
op_star
comma
r_int
r_int
id|event
comma
r_struct
id|callb_data
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
