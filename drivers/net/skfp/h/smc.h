multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
macro_line|#ifndef&t;_SCMECM_
DECL|macro|_SCMECM_
mdefine_line|#define _SCMECM_
macro_line|#if&t;defined(PCI) &amp;&amp; !defined(OSDEF)
multiline_comment|/*&n; * In the case of the PCI bus the file osdef1st.h must be present&n; */
DECL|macro|OSDEF
mdefine_line|#define&t;OSDEF
macro_line|#endif
macro_line|#ifdef&t;PCI
macro_line|#ifndef&t;SUPERNET_3
DECL|macro|SUPERNET_3
mdefine_line|#define&t;SUPERNET_3
macro_line|#endif
macro_line|#ifndef&t;TAG_MODE
DECL|macro|TAG_MODE
mdefine_line|#define&t;TAG_MODE
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * include all other files in required order&n; * the following files must have been included before:&n; *&t;types.h&n; *&t;fddi.h&n; */
macro_line|#ifdef&t;OSDEF
macro_line|#include &quot;h/osdef1st.h&quot;
macro_line|#endif&t;/* OSDEF */
macro_line|#ifdef&t;OEM_CONCEPT
macro_line|#include &quot;oemdef.h&quot;
macro_line|#endif&t;/* OEM_CONCEPT */
macro_line|#include &quot;h/smt.h&quot;
macro_line|#include &quot;h/cmtdef.h&quot;
macro_line|#include &quot;h/fddimib.h&quot;
macro_line|#include &quot;h/targethw.h&quot;&t;&t;/* all target hw dependencies */
macro_line|#include &quot;h/targetos.h&quot;&t;&t;/* all target os dependencies */
macro_line|#ifdef&t;ESS
macro_line|#include &quot;h/sba.h&quot;
macro_line|#endif
multiline_comment|/*&n; * Event Queue&n; *&t;queue.c&n; * events are class/value pairs&n; *&t;class&t;is addressee, e.g. RMT, PCM etc.&n; *&t;value&t;is command, e.g. line state change, ring op change etc.&n; */
DECL|struct|event_queue
r_struct
id|event_queue
(brace
DECL|member|class
id|u_short
r_class
suffix:semicolon
multiline_comment|/* event class */
DECL|member|event
id|u_short
id|event
suffix:semicolon
multiline_comment|/* event value */
)brace
suffix:semicolon
multiline_comment|/*&n; * define event queue as circular buffer&n; */
macro_line|#ifdef&t;CONCENTRATOR
DECL|macro|MAX_EVENT
mdefine_line|#define MAX_EVENT&t;128
macro_line|#else&t;/* nCONCENTRATOR */
DECL|macro|MAX_EVENT
mdefine_line|#define MAX_EVENT&t;64
macro_line|#endif&t;/* nCONCENTRATOR */
DECL|struct|s_queue
r_struct
id|s_queue
(brace
DECL|member|ev_queue
r_struct
id|event_queue
id|ev_queue
(braket
id|MAX_EVENT
)braket
suffix:semicolon
DECL|member|ev_put
r_struct
id|event_queue
op_star
id|ev_put
suffix:semicolon
DECL|member|ev_get
r_struct
id|event_queue
op_star
id|ev_get
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ECM - Entity Coordination Management&n; * ecm.c&n; */
DECL|struct|s_ecm
r_struct
id|s_ecm
(brace
DECL|member|path_test
id|u_char
id|path_test
suffix:semicolon
multiline_comment|/* ECM path test variable */
DECL|member|sb_flag
id|u_char
id|sb_flag
suffix:semicolon
multiline_comment|/* ECM stuck bypass */
DECL|member|DisconnectFlag
id|u_char
id|DisconnectFlag
suffix:semicolon
multiline_comment|/* jd 05-Aug-1999 Bug #10419 &n;&t;&t;&t;&t;&t; * ECM disconnected */
DECL|member|ecm_line_state
id|u_char
id|ecm_line_state
suffix:semicolon
multiline_comment|/* flag to dispatcher : line states */
DECL|member|trace_prop
id|u_long
id|trace_prop
suffix:semicolon
multiline_comment|/* ECM Trace_Prop flag &gt;= 16 bits !! */
multiline_comment|/* NUMPHYS note:&n;&t; * this variable must have enough bits to hold all entiies in&n;&t; * the station. So NUMPHYS may not be greater than 31.&n;&t; */
DECL|member|ec_pad
r_char
id|ec_pad
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ecm_timer
r_struct
id|smt_timer
id|ecm_timer
suffix:semicolon
multiline_comment|/* timer */
)brace
suffix:semicolon
multiline_comment|/*&n; * RMT - Ring Management&n; * rmt.c&n; */
DECL|struct|s_rmt
r_struct
id|s_rmt
(brace
DECL|member|dup_addr_test
id|u_char
id|dup_addr_test
suffix:semicolon
multiline_comment|/* state of dupl. addr. test */
DECL|member|da_flag
id|u_char
id|da_flag
suffix:semicolon
multiline_comment|/* flag : duplicate address det. */
DECL|member|loop_avail
id|u_char
id|loop_avail
suffix:semicolon
multiline_comment|/* flag : MAC available for loopback */
DECL|member|sm_ma_avail
id|u_char
id|sm_ma_avail
suffix:semicolon
multiline_comment|/* flag : MAC available for SMT */
DECL|member|no_flag
id|u_char
id|no_flag
suffix:semicolon
multiline_comment|/* flag : ring not operational */
DECL|member|bn_flag
id|u_char
id|bn_flag
suffix:semicolon
multiline_comment|/* flag : MAC reached beacon state */
DECL|member|jm_flag
id|u_char
id|jm_flag
suffix:semicolon
multiline_comment|/* flag : jamming in NON_OP_DUP */
DECL|member|rm_join
id|u_char
id|rm_join
suffix:semicolon
multiline_comment|/* CFM flag RM_Join */
DECL|member|rm_loop
id|u_char
id|rm_loop
suffix:semicolon
multiline_comment|/* CFM flag RM_Loop */
DECL|member|fast_rm_join
r_int
id|fast_rm_join
suffix:semicolon
multiline_comment|/* bit mask of active ports */
multiline_comment|/*&n;&t; * timer and flags&n;&t; */
DECL|member|rmt_timer0
r_struct
id|smt_timer
id|rmt_timer0
suffix:semicolon
multiline_comment|/* timer 0 */
DECL|member|rmt_timer1
r_struct
id|smt_timer
id|rmt_timer1
suffix:semicolon
multiline_comment|/* timer 1 */
DECL|member|rmt_timer2
r_struct
id|smt_timer
id|rmt_timer2
suffix:semicolon
multiline_comment|/* timer 2 */
DECL|member|timer0_exp
id|u_char
id|timer0_exp
suffix:semicolon
multiline_comment|/* flag : timer 0 expired */
DECL|member|timer1_exp
id|u_char
id|timer1_exp
suffix:semicolon
multiline_comment|/* flag : timer 1 expired */
DECL|member|timer2_exp
id|u_char
id|timer2_exp
suffix:semicolon
multiline_comment|/* flag : timer 2 expired */
DECL|member|rm_pad1
id|u_char
id|rm_pad1
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * CFM - Configuration Management&n; * cfm.c&n; * used for SAS and DAS&n; */
DECL|struct|s_cfm
r_struct
id|s_cfm
(brace
DECL|member|cf_state
id|u_char
id|cf_state
suffix:semicolon
multiline_comment|/* CFM state machine current state */
DECL|member|cf_pad
id|u_char
id|cf_pad
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * CEM - Configuration Element Management&n; * cem.c&n; * used for Concentrator&n; */
macro_line|#ifdef&t;CONCENTRATOR
DECL|struct|s_cem
r_struct
id|s_cem
(brace
DECL|member|ce_state
r_int
id|ce_state
suffix:semicolon
multiline_comment|/* CEM state */
DECL|member|ce_port
r_int
id|ce_port
suffix:semicolon
multiline_comment|/* PA PB PM PM+1 .. */
DECL|member|ce_type
r_int
id|ce_type
suffix:semicolon
multiline_comment|/* TA TB TS TM */
)brace
suffix:semicolon
multiline_comment|/*&n; * linked list of CCEs in current token path&n; */
DECL|struct|s_c_ring
r_struct
id|s_c_ring
(brace
DECL|member|c_next
r_struct
id|s_c_ring
op_star
id|c_next
suffix:semicolon
DECL|member|c_entity
r_char
id|c_entity
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mib_path_config
r_struct
id|mib_path_config
(brace
DECL|member|fddimibPATHConfigSMTIndex
id|u_long
id|fddimibPATHConfigSMTIndex
suffix:semicolon
DECL|member|fddimibPATHConfigPATHIndex
id|u_long
id|fddimibPATHConfigPATHIndex
suffix:semicolon
DECL|member|fddimibPATHConfigTokenOrder
id|u_long
id|fddimibPATHConfigTokenOrder
suffix:semicolon
DECL|member|fddimibPATHConfigResourceType
id|u_long
id|fddimibPATHConfigResourceType
suffix:semicolon
DECL|macro|SNMP_RES_TYPE_MAC
mdefine_line|#define SNMP_RES_TYPE_MAC&t;2&t;/* Resource is a MAC */
DECL|macro|SNMP_RES_TYPE_PORT
mdefine_line|#define SNMP_RES_TYPE_PORT&t;4&t;/* Resource is a PORT */
DECL|member|fddimibPATHConfigResourceIndex
id|u_long
id|fddimibPATHConfigResourceIndex
suffix:semicolon
DECL|member|fddimibPATHConfigCurrentPath
id|u_long
id|fddimibPATHConfigCurrentPath
suffix:semicolon
DECL|macro|SNMP_PATH_ISOLATED
mdefine_line|#define SNMP_PATH_ISOLATED&t;1&t;/* Current path is isolated */
DECL|macro|SNMP_PATH_LOCAL
mdefine_line|#define SNMP_PATH_LOCAL&t;&t;2&t;/* Current path is local */
DECL|macro|SNMP_PATH_SECONDARY
mdefine_line|#define SNMP_PATH_SECONDARY&t;3&t;/* Current path is secondary */
DECL|macro|SNMP_PATH_PRIMARY
mdefine_line|#define SNMP_PATH_PRIMARY&t;4&t;/* Current path is primary */
DECL|macro|SNMP_PATH_CONCATENATED
mdefine_line|#define SNMP_PATH_CONCATENATED&t;5&t;/* Current path is concatenated */
DECL|macro|SNMP_PATH_THRU
mdefine_line|#define SNMP_PATH_THRU&t;&t;6&t;/* Current path is thru */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * PCM connect states&n; */
DECL|macro|PCM_DISABLED
mdefine_line|#define PCM_DISABLED&t;0
DECL|macro|PCM_CONNECTING
mdefine_line|#define PCM_CONNECTING&t;1
DECL|macro|PCM_STANDBY
mdefine_line|#define PCM_STANDBY&t;2
DECL|macro|PCM_ACTIVE
mdefine_line|#define PCM_ACTIVE&t;3
DECL|struct|s_pcm
r_struct
id|s_pcm
(brace
DECL|member|pcm_pad
id|u_char
id|pcm_pad
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * PHY struct&n; * one per physical port&n; */
DECL|struct|s_phy
r_struct
id|s_phy
(brace
multiline_comment|/* Inter Module Globals */
DECL|member|mib
r_struct
id|fddi_mib_p
op_star
id|mib
suffix:semicolon
DECL|member|np
id|u_char
id|np
suffix:semicolon
multiline_comment|/* index 0 .. NUMPHYS */
DECL|member|cf_join
id|u_char
id|cf_join
suffix:semicolon
DECL|member|cf_loop
id|u_char
id|cf_loop
suffix:semicolon
DECL|member|wc_flag
id|u_char
id|wc_flag
suffix:semicolon
multiline_comment|/* withhold connection flag */
DECL|member|pc_mode
id|u_char
id|pc_mode
suffix:semicolon
multiline_comment|/* Holds the negotiated mode of the PCM */
DECL|member|pc_lem_fail
id|u_char
id|pc_lem_fail
suffix:semicolon
multiline_comment|/* flag : LCT failed */
DECL|member|lc_test
id|u_char
id|lc_test
suffix:semicolon
DECL|member|scrub
id|u_char
id|scrub
suffix:semicolon
multiline_comment|/* CFM flag Scrub -&gt; PCM */
DECL|member|phy_name
r_char
id|phy_name
suffix:semicolon
DECL|member|pmd_type
id|u_char
id|pmd_type
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* SK connector/transceiver type codes */
DECL|macro|PMD_SK_CONN
mdefine_line|#define PMD_SK_CONN&t;0&t;/* pmd_type[PMD_SK_CONN] = Connector */
DECL|macro|PMD_SK_PMD
mdefine_line|#define PMD_SK_PMD&t;1&t;/* pmd_type[PMD_SK_PMD] = Xver */
DECL|member|pmd_scramble
id|u_char
id|pmd_scramble
suffix:semicolon
multiline_comment|/* scrambler on/off */
multiline_comment|/* inner Module Globals */
DECL|member|curr_ls
id|u_char
id|curr_ls
suffix:semicolon
multiline_comment|/* current line state */
DECL|member|ls_flag
id|u_char
id|ls_flag
suffix:semicolon
DECL|member|rc_flag
id|u_char
id|rc_flag
suffix:semicolon
DECL|member|tc_flag
id|u_char
id|tc_flag
suffix:semicolon
DECL|member|td_flag
id|u_char
id|td_flag
suffix:semicolon
DECL|member|bitn
id|u_char
id|bitn
suffix:semicolon
DECL|member|tr_flag
id|u_char
id|tr_flag
suffix:semicolon
multiline_comment|/* trace recvd while in active */
DECL|member|twisted
id|u_char
id|twisted
suffix:semicolon
multiline_comment|/* flag to indicate an A-A or B-B connection */
DECL|member|t_val
id|u_char
id|t_val
(braket
id|NUMBITS
)braket
suffix:semicolon
multiline_comment|/* transmit bits for signaling */
DECL|member|r_val
id|u_char
id|r_val
(braket
id|NUMBITS
)braket
suffix:semicolon
multiline_comment|/* receive bits for signaling */
DECL|member|t_next
id|u_long
id|t_next
(braket
id|NUMBITS
)braket
suffix:semicolon
DECL|member|pcm_timer0
r_struct
id|smt_timer
id|pcm_timer0
suffix:semicolon
DECL|member|pcm_timer1
r_struct
id|smt_timer
id|pcm_timer1
suffix:semicolon
DECL|member|pcm_timer2
r_struct
id|smt_timer
id|pcm_timer2
suffix:semicolon
DECL|member|timer0_exp
id|u_char
id|timer0_exp
suffix:semicolon
DECL|member|timer1_exp
id|u_char
id|timer1_exp
suffix:semicolon
DECL|member|timer2_exp
id|u_char
id|timer2_exp
suffix:semicolon
DECL|member|pcm_pad1
id|u_char
id|pcm_pad1
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|cem_pst
r_int
id|cem_pst
suffix:semicolon
multiline_comment|/* CEM privae state; used for dual homing */
DECL|member|lem
r_struct
id|lem_counter
id|lem
suffix:semicolon
macro_line|#ifdef&t;AMDPLC
DECL|member|plc
r_struct
id|s_plc
id|plc
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * timer package&n; * smttimer.c&n; */
DECL|struct|s_timer
r_struct
id|s_timer
(brace
DECL|member|st_queue
r_struct
id|smt_timer
op_star
id|st_queue
suffix:semicolon
DECL|member|st_fast
r_struct
id|smt_timer
id|st_fast
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * SRF types and data&n; */
DECL|macro|SMT_EVENT_BASE
mdefine_line|#define SMT_EVENT_BASE&t;&t;&t;1
DECL|macro|SMT_EVENT_MAC_PATH_CHANGE
mdefine_line|#define SMT_EVENT_MAC_PATH_CHANGE&t;(SMT_EVENT_BASE+0)
DECL|macro|SMT_EVENT_MAC_NEIGHBOR_CHANGE
mdefine_line|#define SMT_EVENT_MAC_NEIGHBOR_CHANGE&t;(SMT_EVENT_BASE+1)
DECL|macro|SMT_EVENT_PORT_PATH_CHANGE
mdefine_line|#define SMT_EVENT_PORT_PATH_CHANGE&t;(SMT_EVENT_BASE+2)
DECL|macro|SMT_EVENT_PORT_CONNECTION
mdefine_line|#define SMT_EVENT_PORT_CONNECTION&t;(SMT_EVENT_BASE+3)
DECL|macro|SMT_IS_CONDITION
mdefine_line|#define SMT_IS_CONDITION(x)&t;&t;&t;((x)&gt;=SMT_COND_BASE)
DECL|macro|SMT_COND_BASE
mdefine_line|#define SMT_COND_BASE&t;&t;(SMT_EVENT_PORT_CONNECTION+1)
DECL|macro|SMT_COND_SMT_PEER_WRAP
mdefine_line|#define SMT_COND_SMT_PEER_WRAP&t;&t;(SMT_COND_BASE+0)
DECL|macro|SMT_COND_SMT_HOLD
mdefine_line|#define SMT_COND_SMT_HOLD&t;&t;(SMT_COND_BASE+1)
DECL|macro|SMT_COND_MAC_FRAME_ERROR
mdefine_line|#define SMT_COND_MAC_FRAME_ERROR&t;(SMT_COND_BASE+2)
DECL|macro|SMT_COND_MAC_DUP_ADDR
mdefine_line|#define SMT_COND_MAC_DUP_ADDR&t;&t;(SMT_COND_BASE+3)
DECL|macro|SMT_COND_MAC_NOT_COPIED
mdefine_line|#define SMT_COND_MAC_NOT_COPIED&t;&t;(SMT_COND_BASE+4)
DECL|macro|SMT_COND_PORT_EB_ERROR
mdefine_line|#define SMT_COND_PORT_EB_ERROR&t;&t;(SMT_COND_BASE+5)
DECL|macro|SMT_COND_PORT_LER
mdefine_line|#define SMT_COND_PORT_LER&t;&t;(SMT_COND_BASE+6)
DECL|macro|SR0_WAIT
mdefine_line|#define SR0_WAIT&t;0
DECL|macro|SR1_HOLDOFF
mdefine_line|#define SR1_HOLDOFF&t;1
DECL|macro|SR2_DISABLED
mdefine_line|#define SR2_DISABLED&t;2
DECL|struct|s_srf
r_struct
id|s_srf
(brace
DECL|member|SRThreshold
id|u_long
id|SRThreshold
suffix:semicolon
multiline_comment|/* threshold value */
DECL|member|RT_Flag
id|u_char
id|RT_Flag
suffix:semicolon
multiline_comment|/* report transmitted flag */
DECL|member|sr_state
id|u_char
id|sr_state
suffix:semicolon
multiline_comment|/* state-machine */
DECL|member|any_report
id|u_char
id|any_report
suffix:semicolon
multiline_comment|/* any report required */
DECL|member|TSR
id|u_long
id|TSR
suffix:semicolon
multiline_comment|/* timer */
DECL|member|ring_status
id|u_short
id|ring_status
suffix:semicolon
multiline_comment|/* IBM ring status */
)brace
suffix:semicolon
multiline_comment|/*&n; * IBM token ring status&n; */
DECL|macro|RS_RES15
mdefine_line|#define RS_RES15&t;(1&lt;&lt;15)&t;&t;&t;/* reserved */
DECL|macro|RS_HARDERROR
mdefine_line|#define RS_HARDERROR&t;(1&lt;&lt;14)&t;&t;&t;/* ring down */
DECL|macro|RS_SOFTERROR
mdefine_line|#define RS_SOFTERROR&t;(1&lt;&lt;13)&t;&t;&t;/* sent SRF */
DECL|macro|RS_BEACON
mdefine_line|#define RS_BEACON&t;(1&lt;&lt;12)&t;&t;&t;/* transmitted beacon */
DECL|macro|RS_PATHTEST
mdefine_line|#define RS_PATHTEST&t;(1&lt;&lt;11)&t;&t;&t;/* path test failed */
DECL|macro|RS_SELFTEST
mdefine_line|#define RS_SELFTEST&t;(1&lt;&lt;10)&t;&t;&t;/* selftest required */
DECL|macro|RS_RES9
mdefine_line|#define RS_RES9&t;&t;(1&lt;&lt; 9)&t;&t;&t;/* reserved */
DECL|macro|RS_DISCONNECT
mdefine_line|#define RS_DISCONNECT&t;(1&lt;&lt; 8)&t;&t;&t;/* remote disconnect */
DECL|macro|RS_RES7
mdefine_line|#define RS_RES7&t;&t;(1&lt;&lt; 7)&t;&t;&t;/* reserved */
DECL|macro|RS_DUPADDR
mdefine_line|#define RS_DUPADDR&t;(1&lt;&lt; 6)&t;&t;&t;/* duplicate address */
DECL|macro|RS_NORINGOP
mdefine_line|#define RS_NORINGOP&t;(1&lt;&lt; 5)&t;&t;&t;/* no ring op */
DECL|macro|RS_VERSION
mdefine_line|#define RS_VERSION&t;(1&lt;&lt; 4)&t;&t;&t;/* SMT version mismatch */
DECL|macro|RS_STUCKBYPASSS
mdefine_line|#define RS_STUCKBYPASSS&t;(1&lt;&lt; 3)&t;&t;&t;/* stuck bypass */
DECL|macro|RS_EVENT
mdefine_line|#define RS_EVENT&t;(1&lt;&lt; 2)&t;&t;&t;/* FDDI event occurred */
DECL|macro|RS_RINGOPCHANGE
mdefine_line|#define RS_RINGOPCHANGE&t;(1&lt;&lt; 1)&t;&t;&t;/* ring op changed */
DECL|macro|RS_RES0
mdefine_line|#define RS_RES0&t;&t;(1&lt;&lt; 0)&t;&t;&t;/* reserved */
DECL|macro|RS_SET
mdefine_line|#define RS_SET(smc,bit) &bslash;&n;&t;ring_status_indication(smc,smc-&gt;srf.ring_status |= bit)
DECL|macro|RS_CLEAR
mdefine_line|#define RS_CLEAR(smc,bit)&t;&bslash;&n;&t;ring_status_indication(smc,smc-&gt;srf.ring_status &amp;= ~bit)
DECL|macro|RS_CLEAR_EVENT
mdefine_line|#define RS_CLEAR_EVENT&t;(0xffff &amp; ~(RS_NORINGOP))
multiline_comment|/* Define the AIX-event-Notification as null function if it isn&squot;t defined */
multiline_comment|/* in the targetos.h file */
macro_line|#ifndef AIX_EVENT
DECL|macro|AIX_EVENT
mdefine_line|#define AIX_EVENT(smc,opt0,opt1,opt2,opt3)&t;/* nothing */
macro_line|#endif
DECL|struct|s_srf_evc
r_struct
id|s_srf_evc
(brace
DECL|member|evc_code
id|u_char
id|evc_code
suffix:semicolon
multiline_comment|/* event code type */
DECL|member|evc_index
id|u_char
id|evc_index
suffix:semicolon
multiline_comment|/* index for mult. instances */
DECL|member|evc_rep_required
id|u_char
id|evc_rep_required
suffix:semicolon
multiline_comment|/* report required */
DECL|member|evc_para
id|u_short
id|evc_para
suffix:semicolon
multiline_comment|/* SMT Para Number */
DECL|member|evc_cond_state
id|u_char
op_star
id|evc_cond_state
suffix:semicolon
multiline_comment|/* condition state */
DECL|member|evc_multiple
id|u_char
op_star
id|evc_multiple
suffix:semicolon
multiline_comment|/* multiple occurence */
)brace
suffix:semicolon
multiline_comment|/*&n; * Values used by frame based services&n; * smt.c&n; */
DECL|macro|SMT_MAX_TEST
mdefine_line|#define SMT_MAX_TEST&t;&t;5
DECL|macro|SMT_TID_NIF
mdefine_line|#define SMT_TID_NIF&t;&t;0&t;&t;/* pending NIF request */
DECL|macro|SMT_TID_NIF_TEST
mdefine_line|#define SMT_TID_NIF_TEST&t;1&t;&t;/* pending NIF test */
DECL|macro|SMT_TID_ECF_UNA
mdefine_line|#define SMT_TID_ECF_UNA&t;&t;2&t;&t;/* pending ECF UNA test */
DECL|macro|SMT_TID_ECF_DNA
mdefine_line|#define SMT_TID_ECF_DNA&t;&t;3&t;&t;/* pending ECF DNA test */
DECL|macro|SMT_TID_ECF
mdefine_line|#define SMT_TID_ECF&t;&t;4&t;&t;/* pending ECF test */
DECL|struct|smt_values
r_struct
id|smt_values
(brace
DECL|member|smt_tvu
id|u_long
id|smt_tvu
suffix:semicolon
multiline_comment|/* timer valid una */
DECL|member|smt_tvd
id|u_long
id|smt_tvd
suffix:semicolon
multiline_comment|/* timer valid dna */
DECL|member|smt_tid
id|u_long
id|smt_tid
suffix:semicolon
multiline_comment|/* transaction id */
DECL|member|pend
id|u_long
id|pend
(braket
id|SMT_MAX_TEST
)braket
suffix:semicolon
multiline_comment|/* TID of requests */
DECL|member|uniq_time
id|u_long
id|uniq_time
suffix:semicolon
multiline_comment|/* unique time stamp */
DECL|member|uniq_ticks
id|u_short
id|uniq_ticks
suffix:semicolon
multiline_comment|/* unique time stamp */
DECL|member|please_reconnect
id|u_short
id|please_reconnect
suffix:semicolon
multiline_comment|/* flag : reconnect */
DECL|member|smt_last_lem
id|u_long
id|smt_last_lem
suffix:semicolon
DECL|member|smt_last_notify
id|u_long
id|smt_last_notify
suffix:semicolon
DECL|member|smt_timer
r_struct
id|smt_timer
id|smt_timer
suffix:semicolon
multiline_comment|/* SMT NIF timer */
DECL|member|last_tok_time
id|u_long
id|last_tok_time
(braket
id|NUMMACS
)braket
suffix:semicolon
multiline_comment|/* token cnt emulation */
)brace
suffix:semicolon
multiline_comment|/*&n; * SMT/CMT configurable parameters&n; */
DECL|macro|SMT_DAS
mdefine_line|#define SMT_DAS&t;0&t;&t;&t;/* dual attach */
DECL|macro|SMT_SAS
mdefine_line|#define SMT_SAS&t;1&t;&t;&t;/* single attach */
DECL|macro|SMT_NAC
mdefine_line|#define SMT_NAC&t;2&t;&t;&t;/* null attach concentrator */
DECL|struct|smt_config
r_struct
id|smt_config
(brace
DECL|member|attach_s
id|u_char
id|attach_s
suffix:semicolon
multiline_comment|/* CFM attach to secondary path */
DECL|member|sas
id|u_char
id|sas
suffix:semicolon
multiline_comment|/* SMT_DAS/SAS/NAC */
DECL|member|build_ring_map
id|u_char
id|build_ring_map
suffix:semicolon
multiline_comment|/* build ringmap if TRUE */
DECL|member|numphys
id|u_char
id|numphys
suffix:semicolon
multiline_comment|/* number of active phys */
DECL|member|sc_pad
id|u_char
id|sc_pad
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|pcm_tb_min
id|u_long
id|pcm_tb_min
suffix:semicolon
multiline_comment|/* PCM : TB_Min timer value */
DECL|member|pcm_tb_max
id|u_long
id|pcm_tb_max
suffix:semicolon
multiline_comment|/* PCM : TB_Max timer value */
DECL|member|pcm_c_min
id|u_long
id|pcm_c_min
suffix:semicolon
multiline_comment|/* PCM : C_Min timer value */
DECL|member|pcm_t_out
id|u_long
id|pcm_t_out
suffix:semicolon
multiline_comment|/* PCM : T_Out timer value */
DECL|member|pcm_tl_min
id|u_long
id|pcm_tl_min
suffix:semicolon
multiline_comment|/* PCM : TL_min timer value */
DECL|member|pcm_lc_short
id|u_long
id|pcm_lc_short
suffix:semicolon
multiline_comment|/* PCM : LC_Short timer value */
DECL|member|pcm_lc_medium
id|u_long
id|pcm_lc_medium
suffix:semicolon
multiline_comment|/* PCM : LC_Medium timer value */
DECL|member|pcm_lc_long
id|u_long
id|pcm_lc_long
suffix:semicolon
multiline_comment|/* PCM : LC_Long timer value */
DECL|member|pcm_lc_extended
id|u_long
id|pcm_lc_extended
suffix:semicolon
multiline_comment|/* PCM : LC_Extended timer value */
DECL|member|pcm_t_next_9
id|u_long
id|pcm_t_next_9
suffix:semicolon
multiline_comment|/* PCM : T_Next[9] timer value */
DECL|member|pcm_ns_max
id|u_long
id|pcm_ns_max
suffix:semicolon
multiline_comment|/* PCM : NS_Max timer value */
DECL|member|ecm_i_max
id|u_long
id|ecm_i_max
suffix:semicolon
multiline_comment|/* ECM : I_Max timer value */
DECL|member|ecm_in_max
id|u_long
id|ecm_in_max
suffix:semicolon
multiline_comment|/* ECM : IN_Max timer value */
DECL|member|ecm_td_min
id|u_long
id|ecm_td_min
suffix:semicolon
multiline_comment|/* ECM : TD_Min timer */
DECL|member|ecm_test_done
id|u_long
id|ecm_test_done
suffix:semicolon
multiline_comment|/* ECM : path test done timer */
DECL|member|ecm_check_poll
id|u_long
id|ecm_check_poll
suffix:semicolon
multiline_comment|/* ECM : check bypass poller */
DECL|member|rmt_t_non_op
id|u_long
id|rmt_t_non_op
suffix:semicolon
multiline_comment|/* RMT : T_Non_OP timer value */
DECL|member|rmt_t_stuck
id|u_long
id|rmt_t_stuck
suffix:semicolon
multiline_comment|/* RMT : T_Stuck timer value */
DECL|member|rmt_t_direct
id|u_long
id|rmt_t_direct
suffix:semicolon
multiline_comment|/* RMT : T_Direct timer value */
DECL|member|rmt_t_jam
id|u_long
id|rmt_t_jam
suffix:semicolon
multiline_comment|/* RMT : T_Jam timer value */
DECL|member|rmt_t_announce
id|u_long
id|rmt_t_announce
suffix:semicolon
multiline_comment|/* RMT : T_Announce timer value */
DECL|member|rmt_t_poll
id|u_long
id|rmt_t_poll
suffix:semicolon
multiline_comment|/* RMT : claim/beacon poller */
DECL|member|rmt_dup_mac_behavior
id|u_long
id|rmt_dup_mac_behavior
suffix:semicolon
multiline_comment|/* Flag for the beavior of SMT if&n;&t;&t;&t;&t;&t; * a Duplicate MAC Address was detected.&n;&t;&t;&t;&t;&t; * FALSE: SMT will leave finaly the ring&n;&t;&t;&t;&t;&t; * TRUE:  SMT will reinstert into the ring&n;&t;&t;&t;&t;&t; */
DECL|member|mac_d_max
id|u_long
id|mac_d_max
suffix:semicolon
multiline_comment|/* MAC : D_Max timer value */
DECL|member|lct_short
id|u_long
id|lct_short
suffix:semicolon
multiline_comment|/* LCT : error threshhold */
DECL|member|lct_medium
id|u_long
id|lct_medium
suffix:semicolon
multiline_comment|/* LCT : error threshhold */
DECL|member|lct_long
id|u_long
id|lct_long
suffix:semicolon
multiline_comment|/* LCT : error threshhold */
DECL|member|lct_extended
id|u_long
id|lct_extended
suffix:semicolon
multiline_comment|/* LCT : error threshhold */
)brace
suffix:semicolon
macro_line|#ifdef&t;DEBUG
multiline_comment|/*&n; * Debugging struct sometimes used in smc&n; */
DECL|struct|smt_debug
r_struct
id|smt_debug
(brace
DECL|member|d_smtf
r_int
id|d_smtf
suffix:semicolon
DECL|member|d_smt
r_int
id|d_smt
suffix:semicolon
DECL|member|d_ecm
r_int
id|d_ecm
suffix:semicolon
DECL|member|d_rmt
r_int
id|d_rmt
suffix:semicolon
DECL|member|d_cfm
r_int
id|d_cfm
suffix:semicolon
DECL|member|d_pcm
r_int
id|d_pcm
suffix:semicolon
DECL|member|d_plc
r_int
id|d_plc
suffix:semicolon
macro_line|#ifdef&t;ESS
DECL|member|d_ess
r_int
id|d_ess
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;SBA
DECL|member|d_sba
r_int
id|d_sba
suffix:semicolon
macro_line|#endif
DECL|member|d_os
r_struct
id|os_debug
id|d_os
suffix:semicolon
multiline_comment|/* Include specific OS DEBUG struct */
)brace
suffix:semicolon
macro_line|#ifndef&t;DEBUG_BRD
multiline_comment|/* all boards shall be debugged with one debug struct */
r_extern
r_struct
id|smt_debug
id|debug
suffix:semicolon
multiline_comment|/* Declaration of debug struct */
macro_line|#endif&t;/* DEBUG_BRD */
macro_line|#endif&t;/* DEBUG */
multiline_comment|/*&n; * the SMT Context Struct SMC&n; * this struct contains ALL global variables of SMT&n; */
DECL|struct|s_smc
r_struct
id|s_smc
(brace
DECL|member|os
r_struct
id|s_smt_os
id|os
suffix:semicolon
multiline_comment|/* os specific */
DECL|member|hw
r_struct
id|s_smt_hw
id|hw
suffix:semicolon
multiline_comment|/* hardware */
multiline_comment|/*&n; * NOTE: os and hw MUST BE the first two structs&n; * anything beyond hw WILL BE SET TO ZERO in smt_set_defaults()&n; */
DECL|member|s
r_struct
id|smt_config
id|s
suffix:semicolon
multiline_comment|/* smt constants */
DECL|member|sm
r_struct
id|smt_values
id|sm
suffix:semicolon
multiline_comment|/* smt variables */
DECL|member|e
r_struct
id|s_ecm
id|e
suffix:semicolon
multiline_comment|/* ecm */
DECL|member|r
r_struct
id|s_rmt
id|r
suffix:semicolon
multiline_comment|/* rmt */
DECL|member|cf
r_struct
id|s_cfm
id|cf
suffix:semicolon
multiline_comment|/* cfm/cem */
macro_line|#ifdef&t;CONCENTRATOR
DECL|member|ce
r_struct
id|s_cem
id|ce
(braket
id|NUMPHYS
)braket
suffix:semicolon
multiline_comment|/* cem */
DECL|member|cr
r_struct
id|s_c_ring
id|cr
(braket
id|NUMPHYS
op_plus
id|NUMMACS
)braket
suffix:semicolon
macro_line|#endif
DECL|member|p
r_struct
id|s_pcm
id|p
suffix:semicolon
multiline_comment|/* pcm */
DECL|member|y
r_struct
id|s_phy
id|y
(braket
id|NUMPHYS
)braket
suffix:semicolon
multiline_comment|/* phy */
DECL|member|q
r_struct
id|s_queue
id|q
suffix:semicolon
multiline_comment|/* queue */
DECL|member|t
r_struct
id|s_timer
id|t
suffix:semicolon
multiline_comment|/* timer */
DECL|member|srf
r_struct
id|s_srf
id|srf
suffix:semicolon
multiline_comment|/* SRF */
DECL|member|evcs
r_struct
id|s_srf_evc
id|evcs
(braket
l_int|6
op_plus
id|NUMPHYS
op_star
l_int|4
)braket
suffix:semicolon
DECL|member|mib
r_struct
id|fddi_mib
id|mib
suffix:semicolon
multiline_comment|/* __THE_MIB__ */
macro_line|#ifdef&t;SBA
DECL|member|sba
r_struct
id|s_sba
id|sba
suffix:semicolon
multiline_comment|/* SBA variables */
macro_line|#endif
macro_line|#ifdef&t;ESS
DECL|member|ess
r_struct
id|s_ess
id|ess
suffix:semicolon
multiline_comment|/* Ess variables */
macro_line|#endif
macro_line|#if&t;defined(DEBUG) &amp;&amp; defined(DEBUG_BRD)
multiline_comment|/* If you want all single board to be debugged separately */
DECL|member|debug
r_struct
id|smt_debug
id|debug
suffix:semicolon
multiline_comment|/* Declaration of debug struct */
macro_line|#endif&t;/* DEBUG_BRD &amp;&amp; DEBUG */
)brace
suffix:semicolon
macro_line|#endif&t;/* _SCMECM_ */
eof
