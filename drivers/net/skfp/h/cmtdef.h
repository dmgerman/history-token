multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
macro_line|#ifndef&t;_CMTDEF_
DECL|macro|_CMTDEF_
mdefine_line|#define _CMTDEF_
multiline_comment|/* **************************************************************** */
multiline_comment|/*&n; * implementation specific constants&n; * MODIIFY THE FOLLWOING THREE DEFINES&n; */
DECL|macro|AMDPLC
mdefine_line|#define AMDPLC&t;&t;&t;/* if Amd PLC chip used */
macro_line|#ifdef&t;CONC
DECL|macro|NUMPHYS
mdefine_line|#define NUMPHYS&t;&t;12&t;/* 2 for SAS or DAS, more for Concentrator */
macro_line|#else
macro_line|#ifdef&t;CONC_II
DECL|macro|NUMPHYS
mdefine_line|#define NUMPHYS&t;&t;24&t;/* 2 for SAS or DAS, more for Concentrator */
macro_line|#else
DECL|macro|NUMPHYS
mdefine_line|#define NUMPHYS&t;&t;2&t;/* 2 for SAS or DAS, more for Concentrator */
macro_line|#endif
macro_line|#endif
DECL|macro|NUMMACS
mdefine_line|#define NUMMACS&t;&t;1&t;/* only 1 supported at the moment */
DECL|macro|NUMPATHS
mdefine_line|#define NUMPATHS&t;2&t;/* primary and secondary path supported */
multiline_comment|/*&n; * DO NOT MODIFY BEYOND THIS POINT&n; */
multiline_comment|/* **************************************************************** */
macro_line|#if&t;NUMPHYS &gt; 2
DECL|macro|CONCENTRATOR
mdefine_line|#define CONCENTRATOR
macro_line|#endif
multiline_comment|/*&n; * Definitions for comfortable LINT usage&n; */
macro_line|#ifdef&t;lint
DECL|macro|LINT_USE
mdefine_line|#define LINT_USE(x)&t;(x)=(x)
macro_line|#else
DECL|macro|LINT_USE
mdefine_line|#define LINT_USE(x)
macro_line|#endif
macro_line|#ifdef&t;DEBUG
DECL|macro|DB_PR
mdefine_line|#define&t;DB_PR(flag,a,b,c)&t;{ if (flag) printf(a,b,c) ; }
macro_line|#else
DECL|macro|DB_PR
mdefine_line|#define&t;DB_PR(flag,a,b,c)
macro_line|#endif
macro_line|#ifdef DEBUG_BRD
DECL|macro|DB_ECM
mdefine_line|#define DB_ECM(a,b,c)&t;&t;DB_PR((smc-&gt;debug.d_smt&amp;1),a,b,c)
DECL|macro|DB_ECMN
mdefine_line|#define DB_ECMN(n,a,b,c)&t;DB_PR((smc-&gt;debug.d_ecm &gt;=(n)),a,b,c)
DECL|macro|DB_RMT
mdefine_line|#define DB_RMT(a,b,c)&t;&t;DB_PR((smc-&gt;debug.d_smt&amp;2),a,b,c)
DECL|macro|DB_RMTN
mdefine_line|#define DB_RMTN(n,a,b,c)&t;DB_PR((smc-&gt;debug.d_rmt &gt;=(n)),a,b,c)
DECL|macro|DB_CFM
mdefine_line|#define DB_CFM(a,b,c)&t;&t;DB_PR((smc-&gt;debug.d_smt&amp;4),a,b,c)
DECL|macro|DB_CFMN
mdefine_line|#define DB_CFMN(n,a,b,c)&t;DB_PR((smc-&gt;debug.d_cfm &gt;=(n)),a,b,c)
DECL|macro|DB_PCM
mdefine_line|#define DB_PCM(a,b,c)&t;&t;DB_PR((smc-&gt;debug.d_smt&amp;8),a,b,c)
DECL|macro|DB_PCMN
mdefine_line|#define DB_PCMN(n,a,b,c)&t;DB_PR((smc-&gt;debug.d_pcm &gt;=(n)),a,b,c)
DECL|macro|DB_SMT
mdefine_line|#define DB_SMT(a,b,c)&t;&t;DB_PR((smc-&gt;debug.d_smtf),a,b,c)
DECL|macro|DB_SMTN
mdefine_line|#define DB_SMTN(n,a,b,c)&t;DB_PR((smc-&gt;debug.d_smtf &gt;=(n)),a,b,c)
DECL|macro|DB_SBA
mdefine_line|#define DB_SBA(a,b,c)&t;&t;DB_PR((smc-&gt;debug.d_sba),a,b,c)
DECL|macro|DB_SBAN
mdefine_line|#define DB_SBAN(n,a,b,c)&t;DB_PR((smc-&gt;debug.d_sba &gt;=(n)),a,b,c)
DECL|macro|DB_ESS
mdefine_line|#define DB_ESS(a,b,c)&t;&t;DB_PR((smc-&gt;debug.d_ess),a,b,c)
DECL|macro|DB_ESSN
mdefine_line|#define DB_ESSN(n,a,b,c)&t;DB_PR((smc-&gt;debug.d_ess &gt;=(n)),a,b,c)
macro_line|#else
DECL|macro|DB_ECM
mdefine_line|#define DB_ECM(a,b,c)&t;&t;DB_PR((debug.d_smt&amp;1),a,b,c)
DECL|macro|DB_ECMN
mdefine_line|#define DB_ECMN(n,a,b,c)&t;DB_PR((debug.d_ecm &gt;=(n)),a,b,c)
DECL|macro|DB_RMT
mdefine_line|#define DB_RMT(a,b,c)&t;&t;DB_PR((debug.d_smt&amp;2),a,b,c)
DECL|macro|DB_RMTN
mdefine_line|#define DB_RMTN(n,a,b,c)&t;DB_PR((debug.d_rmt &gt;=(n)),a,b,c)
DECL|macro|DB_CFM
mdefine_line|#define DB_CFM(a,b,c)&t;&t;DB_PR((debug.d_smt&amp;4),a,b,c)
DECL|macro|DB_CFMN
mdefine_line|#define DB_CFMN(n,a,b,c)&t;DB_PR((debug.d_cfm &gt;=(n)),a,b,c)
DECL|macro|DB_PCM
mdefine_line|#define DB_PCM(a,b,c)&t;&t;DB_PR((debug.d_smt&amp;8),a,b,c)
DECL|macro|DB_PCMN
mdefine_line|#define DB_PCMN(n,a,b,c)&t;DB_PR((debug.d_pcm &gt;=(n)),a,b,c)
DECL|macro|DB_SMT
mdefine_line|#define DB_SMT(a,b,c)&t;&t;DB_PR((debug.d_smtf),a,b,c)
DECL|macro|DB_SMTN
mdefine_line|#define DB_SMTN(n,a,b,c)&t;DB_PR((debug.d_smtf &gt;=(n)),a,b,c)
DECL|macro|DB_SBA
mdefine_line|#define DB_SBA(a,b,c)&t;&t;DB_PR((debug.d_sba),a,b,c)
DECL|macro|DB_SBAN
mdefine_line|#define DB_SBAN(n,a,b,c)&t;DB_PR((debug.d_sba &gt;=(n)),a,b,c)
DECL|macro|DB_ESS
mdefine_line|#define DB_ESS(a,b,c)&t;&t;DB_PR((debug.d_ess),a,b,c)
DECL|macro|DB_ESSN
mdefine_line|#define DB_ESSN(n,a,b,c)&t;DB_PR((debug.d_ess &gt;=(n)),a,b,c)
macro_line|#endif
macro_line|#ifndef&t;SS_NOT_DS
DECL|macro|SK_LOC_DECL
mdefine_line|#define&t;SK_LOC_DECL(type,var)&t;type var
macro_line|#else
DECL|macro|SK_LOC_DECL
mdefine_line|#define&t;SK_LOC_DECL(type,var)&t;static type var
macro_line|#endif
multiline_comment|/*&n; * PHYs and PORTS&n; * Note: Don&squot;t touch the definition of PA and PB. Those might be used&n; *&t;by some &quot;for&quot; loops.&n; */
DECL|macro|PA
mdefine_line|#define PA&t;&t;0
DECL|macro|PB
mdefine_line|#define PB&t;&t;1
macro_line|#if&t;defined(SUPERNET_3) || defined(CONC_II)
multiline_comment|/*&n; * The port indices have to be different,&n; * because the MAC output goes through the 2. PLC&n; * Conc II: It has to be the first port in the row.&n; */
DECL|macro|PS
mdefine_line|#define PS&t;&t;0&t;/* Internal PLC which is the same as PA */
macro_line|#else
DECL|macro|PS
mdefine_line|#define PS&t;&t;1
macro_line|#endif
DECL|macro|PM
mdefine_line|#define PM&t;&t;2&t;&t;/* PM .. PA+NUM_PHYS-1 */
multiline_comment|/*&n; * PHY types - as in path descriptor &squot;fddiPHYType&squot;&n; */
DECL|macro|TA
mdefine_line|#define TA&t;&t;&t;0&t;/* A port */
DECL|macro|TB
mdefine_line|#define TB&t;&t;&t;1&t;/* B port */
DECL|macro|TS
mdefine_line|#define TS&t;&t;&t;2&t;/* S port */
DECL|macro|TM
mdefine_line|#define TM&t;&t;&t;3&t;/* M port */
DECL|macro|TNONE
mdefine_line|#define TNONE&t;&t;&t;4
multiline_comment|/*&n; * indexes in MIB&n; */
DECL|macro|INDEX_MAC
mdefine_line|#define INDEX_MAC&t;1
DECL|macro|INDEX_PATH
mdefine_line|#define INDEX_PATH&t;1
DECL|macro|INDEX_PORT
mdefine_line|#define INDEX_PORT&t;1
multiline_comment|/*&n; * policies&n; */
DECL|macro|POLICY_AA
mdefine_line|#define POLICY_AA&t;(1&lt;&lt;0)&t;&t;/* reject AA */
DECL|macro|POLICY_AB
mdefine_line|#define POLICY_AB&t;(1&lt;&lt;1)&t;&t;/* reject AB */
DECL|macro|POLICY_AS
mdefine_line|#define POLICY_AS&t;(1&lt;&lt;2)&t;&t;/* reject AS */
DECL|macro|POLICY_AM
mdefine_line|#define POLICY_AM&t;(1&lt;&lt;3)&t;&t;/* reject AM */
DECL|macro|POLICY_BA
mdefine_line|#define POLICY_BA&t;(1&lt;&lt;4)&t;&t;/* reject BA */
DECL|macro|POLICY_BB
mdefine_line|#define POLICY_BB&t;(1&lt;&lt;5)&t;&t;/* reject BB */
DECL|macro|POLICY_BS
mdefine_line|#define POLICY_BS&t;(1&lt;&lt;6)&t;&t;/* reject BS */
DECL|macro|POLICY_BM
mdefine_line|#define POLICY_BM&t;(1&lt;&lt;7)&t;&t;/* reject BM */
DECL|macro|POLICY_SA
mdefine_line|#define POLICY_SA&t;(1&lt;&lt;8)&t;&t;/* reject SA */
DECL|macro|POLICY_SB
mdefine_line|#define POLICY_SB&t;(1&lt;&lt;9)&t;&t;/* reject SB */
DECL|macro|POLICY_SS
mdefine_line|#define POLICY_SS&t;(1&lt;&lt;10)&t;&t;/* reject SS */
DECL|macro|POLICY_SM
mdefine_line|#define POLICY_SM&t;(1&lt;&lt;11)&t;&t;/* reject SM */
DECL|macro|POLICY_MA
mdefine_line|#define POLICY_MA&t;(1&lt;&lt;12)&t;&t;/* reject MA */
DECL|macro|POLICY_MB
mdefine_line|#define POLICY_MB&t;(1&lt;&lt;13)&t;&t;/* reject MB */
DECL|macro|POLICY_MS
mdefine_line|#define POLICY_MS&t;(1&lt;&lt;14)&t;&t;/* reject MS */
DECL|macro|POLICY_MM
mdefine_line|#define POLICY_MM&t;(1&lt;&lt;15)&t;&t;/* reject MM */
multiline_comment|/*&n; * commands&n; */
multiline_comment|/*&n; * EVENTS&n; * event classes&n; */
DECL|macro|EVENT_ECM
mdefine_line|#define EVENT_ECM&t;1&t;&t;/* event class ECM */
DECL|macro|EVENT_CFM
mdefine_line|#define EVENT_CFM&t;2&t;&t;/* event class CFM */
DECL|macro|EVENT_RMT
mdefine_line|#define EVENT_RMT&t;3&t;&t;/* event class RMT */
DECL|macro|EVENT_SMT
mdefine_line|#define EVENT_SMT&t;4&t;&t;/* event class SMT */
DECL|macro|EVENT_PCM
mdefine_line|#define EVENT_PCM&t;5&t;&t;/* event class PCM */
DECL|macro|EVENT_PCMA
mdefine_line|#define EVENT_PCMA&t;5&t;&t;/* event class PCMA */
DECL|macro|EVENT_PCMB
mdefine_line|#define EVENT_PCMB&t;6&t;&t;/* event class PCMB */
multiline_comment|/* WARNING :&n; * EVENT_PCM* must be last in the above list&n; * if more than two ports are used, EVENT_PCM .. EVENT_PCMA+NUM_PHYS-1&n; * are used !&n; */
DECL|macro|EV_TOKEN
mdefine_line|#define EV_TOKEN(class,event)&t;(((u_long)(class)&lt;&lt;16L)|((u_long)(event)))
DECL|macro|EV_T_CLASS
mdefine_line|#define EV_T_CLASS(token)&t;((int)((token)&gt;&gt;16)&amp;0xffff)
DECL|macro|EV_T_EVENT
mdefine_line|#define EV_T_EVENT(token)&t;((int)(token)&amp;0xffff)
multiline_comment|/*&n; * ECM events&n; */
DECL|macro|EC_CONNECT
mdefine_line|#define EC_CONNECT&t;1&t;&t;/* connect request */
DECL|macro|EC_DISCONNECT
mdefine_line|#define EC_DISCONNECT&t;2&t;&t;/* disconnect request */
DECL|macro|EC_TRACE_PROP
mdefine_line|#define EC_TRACE_PROP&t;3&t;&t;/* trace propagation */
DECL|macro|EC_PATH_TEST
mdefine_line|#define EC_PATH_TEST&t;4&t;&t;/* path test */
DECL|macro|EC_TIMEOUT_TD
mdefine_line|#define EC_TIMEOUT_TD&t;5&t;&t;/* timer TD_min */
DECL|macro|EC_TIMEOUT_TMAX
mdefine_line|#define EC_TIMEOUT_TMAX&t;6&t;&t;/* timer trace_max */
DECL|macro|EC_TIMEOUT_IMAX
mdefine_line|#define EC_TIMEOUT_IMAX&t;7&t;&t;/* timer I_max */
DECL|macro|EC_TIMEOUT_INMAX
mdefine_line|#define EC_TIMEOUT_INMAX 8&t;&t;/* timer IN_max */
DECL|macro|EC_TEST_DONE
mdefine_line|#define EC_TEST_DONE&t;9&t;&t;/* path test done */
multiline_comment|/*&n; * CFM events&n; */
DECL|macro|CF_LOOP
mdefine_line|#define CF_LOOP&t;&t;1&t;&t;/* cf_loop flag from PCM */
DECL|macro|CF_LOOP_A
mdefine_line|#define CF_LOOP_A&t;1&t;&t;/* cf_loop flag from PCM */
DECL|macro|CF_LOOP_B
mdefine_line|#define CF_LOOP_B&t;2&t;&t;/* cf_loop flag from PCM */
DECL|macro|CF_JOIN
mdefine_line|#define CF_JOIN&t;&t;3&t;&t;/* cf_join flag from PCM */
DECL|macro|CF_JOIN_A
mdefine_line|#define CF_JOIN_A&t;3&t;&t;/* cf_join flag from PCM */
DECL|macro|CF_JOIN_B
mdefine_line|#define CF_JOIN_B&t;4&t;&t;/* cf_join flag from PCM */
multiline_comment|/*&n; * PCM events&n; */
DECL|macro|PC_START
mdefine_line|#define PC_START&t;&t;1
DECL|macro|PC_STOP
mdefine_line|#define PC_STOP&t;&t;&t;2
DECL|macro|PC_LOOP
mdefine_line|#define PC_LOOP&t;&t;&t;3
DECL|macro|PC_JOIN
mdefine_line|#define PC_JOIN&t;&t;&t;4
DECL|macro|PC_SIGNAL
mdefine_line|#define PC_SIGNAL&t;&t;5
DECL|macro|PC_REJECT
mdefine_line|#define PC_REJECT&t;&t;6
DECL|macro|PC_MAINT
mdefine_line|#define PC_MAINT    &t;&t;7
DECL|macro|PC_TRACE
mdefine_line|#define PC_TRACE&t;&t;8
DECL|macro|PC_PDR
mdefine_line|#define PC_PDR&t;&t;&t;9
DECL|macro|PC_ENABLE
mdefine_line|#define PC_ENABLE&t;&t;10
DECL|macro|PC_DISABLE
mdefine_line|#define PC_DISABLE&t;&t;11
multiline_comment|/*&n; * must be ordered as in LineStateType&n; */
DECL|macro|PC_QLS
mdefine_line|#define PC_QLS&t;&t;&t;12
DECL|macro|PC_ILS
mdefine_line|#define PC_ILS&t;&t;&t;13
DECL|macro|PC_MLS
mdefine_line|#define PC_MLS&t;&t;&t;14
DECL|macro|PC_HLS
mdefine_line|#define PC_HLS&t;&t;&t;15
DECL|macro|PC_LS_PDR
mdefine_line|#define PC_LS_PDR&t;&t;16
DECL|macro|PC_LS_NONE
mdefine_line|#define PC_LS_NONE&t;&t;17
DECL|macro|LS2MIB
mdefine_line|#define LS2MIB(x)&t;((x)-PC_QLS)
DECL|macro|MIB2LS
mdefine_line|#define MIB2LS(x)&t;((x)+PC_QLS)
DECL|macro|PC_TIMEOUT_TB_MAX
mdefine_line|#define PC_TIMEOUT_TB_MAX&t;18&t;/* timer TB_max */
DECL|macro|PC_TIMEOUT_TB_MIN
mdefine_line|#define PC_TIMEOUT_TB_MIN&t;19&t;/* timer TB_min */
DECL|macro|PC_TIMEOUT_C_MIN
mdefine_line|#define PC_TIMEOUT_C_MIN&t;20&t;/* timer C_Min */
DECL|macro|PC_TIMEOUT_T_OUT
mdefine_line|#define PC_TIMEOUT_T_OUT&t;21&t;/* timer T_Out */
DECL|macro|PC_TIMEOUT_TL_MIN
mdefine_line|#define PC_TIMEOUT_TL_MIN&t;22&t;/* timer TL_Min */
DECL|macro|PC_TIMEOUT_T_NEXT
mdefine_line|#define PC_TIMEOUT_T_NEXT&t;23&t;/* timer t_next[] */
DECL|macro|PC_TIMEOUT_LCT
mdefine_line|#define PC_TIMEOUT_LCT&t;&t;24
DECL|macro|PC_NSE
mdefine_line|#define PC_NSE&t;&t;&t;25&t;/* NOISE hardware timer */
DECL|macro|PC_LEM
mdefine_line|#define PC_LEM&t;&t;&t;26&t;/* LEM done */
multiline_comment|/*&n; * RMT events&t;&t;&t;&t;  meaning&t;&t;from&n; */
DECL|macro|RM_RING_OP
mdefine_line|#define RM_RING_OP&t;1&t;&t;/* ring operational&t;MAC&t;*/
DECL|macro|RM_RING_NON_OP
mdefine_line|#define RM_RING_NON_OP&t;2&t;&t;/* ring not operational&t;MAC&t;*/
DECL|macro|RM_MY_BEACON
mdefine_line|#define RM_MY_BEACON&t;3&t;&t;/* recvd my beacon&t;MAC&t;*/
DECL|macro|RM_OTHER_BEACON
mdefine_line|#define RM_OTHER_BEACON&t;4&t;&t;/* recvd other beacon&t;MAC&t;*/
DECL|macro|RM_MY_CLAIM
mdefine_line|#define RM_MY_CLAIM&t;5&t;&t;/* recvd my claim&t;MAC&t;*/
DECL|macro|RM_TRT_EXP
mdefine_line|#define RM_TRT_EXP&t;6&t;&t;/* TRT exp&t;&t;MAC&t;*/
DECL|macro|RM_VALID_CLAIM
mdefine_line|#define RM_VALID_CLAIM&t;7&t;&t;/* claim from dup addr&t;MAC&t;*/
DECL|macro|RM_JOIN
mdefine_line|#define RM_JOIN&t;&t;8&t;&t;/* signal rm_join&t;CFM&t;*/
DECL|macro|RM_LOOP
mdefine_line|#define RM_LOOP&t;&t;9&t;&t;/* signal rm_loop&t;CFM&t;*/
DECL|macro|RM_DUP_ADDR
mdefine_line|#define RM_DUP_ADDR&t;10&t;&t;/* dup_addr_test hange&t;SMT-NIF&t;*/
DECL|macro|RM_ENABLE_FLAG
mdefine_line|#define RM_ENABLE_FLAG&t;11&t;&t;/* enable flag */
DECL|macro|RM_TIMEOUT_NON_OP
mdefine_line|#define RM_TIMEOUT_NON_OP&t;12&t;/* timeout T_Non_OP&t;*/
DECL|macro|RM_TIMEOUT_T_STUCK
mdefine_line|#define RM_TIMEOUT_T_STUCK&t;13&t;/* timeout T_Stuck&t;*/
DECL|macro|RM_TIMEOUT_ANNOUNCE
mdefine_line|#define RM_TIMEOUT_ANNOUNCE&t;14&t;/* timeout T_Announce&t;*/
DECL|macro|RM_TIMEOUT_T_DIRECT
mdefine_line|#define RM_TIMEOUT_T_DIRECT&t;15&t;/* timeout T_Direct&t;*/
DECL|macro|RM_TIMEOUT_D_MAX
mdefine_line|#define RM_TIMEOUT_D_MAX&t;16&t;/* timeout D_Max&t;*/
DECL|macro|RM_TIMEOUT_POLL
mdefine_line|#define RM_TIMEOUT_POLL&t;&t;17&t;/* claim/beacon poller&t;*/
DECL|macro|RM_TX_STATE_CHANGE
mdefine_line|#define RM_TX_STATE_CHANGE&t;18&t;/* To restart timer for D_Max */
multiline_comment|/*&n; * SMT events&n; */
DECL|macro|SM_TIMER
mdefine_line|#define SM_TIMER&t;1&t;&t;/* timer */
DECL|macro|SM_FAST
mdefine_line|#define SM_FAST&t;&t;2&t;&t;/* smt_force_irq */
multiline_comment|/* PC modes */
DECL|macro|PM_NONE
mdefine_line|#define PM_NONE&t;&t;0
DECL|macro|PM_PEER
mdefine_line|#define PM_PEER&t;&t;1
DECL|macro|PM_TREE
mdefine_line|#define PM_TREE&t;&t;2
multiline_comment|/*&n; * PCM withhold codes&n; * MIB PC-WithholdType ENUM&n; */
DECL|macro|PC_WH_NONE
mdefine_line|#define PC_WH_NONE&t;0&t;&t;/* ok */
DECL|macro|PC_WH_M_M
mdefine_line|#define PC_WH_M_M&t;1&t;&t;/* M to M */
DECL|macro|PC_WH_OTHER
mdefine_line|#define PC_WH_OTHER&t;2&t;&t;/* other incompatible phys */
DECL|macro|PC_WH_PATH
mdefine_line|#define PC_WH_PATH&t;3&t;&t;/* path not available */
multiline_comment|/*&n; * LCT duration&n; */
DECL|macro|LC_SHORT
mdefine_line|#define LC_SHORT&t;1&t;&t;/* short LCT */
DECL|macro|LC_MEDIUM
mdefine_line|#define LC_MEDIUM&t;2&t;&t;/* medium LCT */
DECL|macro|LC_LONG
mdefine_line|#define LC_LONG&t;&t;3&t;&t;/* long LCT */
DECL|macro|LC_EXTENDED
mdefine_line|#define LC_EXTENDED&t;4&t;&t;/* extended LCT */
multiline_comment|/*&n; * path_test values&n; */
DECL|macro|PT_NONE
mdefine_line|#define PT_NONE&t;&t;0
DECL|macro|PT_TESTING
mdefine_line|#define PT_TESTING&t;1&t;&t;/* test is running */
DECL|macro|PT_PASSED
mdefine_line|#define PT_PASSED&t;2&t;&t;/* test passed */
DECL|macro|PT_FAILED
mdefine_line|#define PT_FAILED&t;3&t;&t;/* test failed */
DECL|macro|PT_PENDING
mdefine_line|#define PT_PENDING&t;4&t;&t;/* path test follows */
DECL|macro|PT_EXITING
mdefine_line|#define PT_EXITING&t;5&t;&t;/* disconnected while in trace/leave */
multiline_comment|/*&n; * duplicate address test&n; * MIB DupAddressTest ENUM&n; */
DECL|macro|DA_NONE
mdefine_line|#define DA_NONE&t;&t;0&t;&t;/* &t;&t;*/
DECL|macro|DA_PASSED
mdefine_line|#define DA_PASSED&t;1&t;&t;/* test passed */
DECL|macro|DA_FAILED
mdefine_line|#define DA_FAILED&t;2&t;&t;/* test failed */
multiline_comment|/*&n; * optical bypass&n; */
DECL|macro|BP_DEINSERT
mdefine_line|#define BP_DEINSERT&t;0&t;&t;/* disable bypass */
DECL|macro|BP_INSERT
mdefine_line|#define BP_INSERT&t;1&t;&t;/* enable bypass */
multiline_comment|/*&n; * ODL enable/disable&n; */
DECL|macro|PM_TRANSMIT_DISABLE
mdefine_line|#define PM_TRANSMIT_DISABLE&t;0&t;/* disable xmit */
DECL|macro|PM_TRANSMIT_ENABLE
mdefine_line|#define PM_TRANSMIT_ENABLE&t;1&t;/* enable xmit */
multiline_comment|/*&n; * parameter for config_mux&n; * note : number is index in config_endec table !&n; */
DECL|macro|MUX_THRUA
mdefine_line|#define MUX_THRUA&t;0&t;&t;/* through A */
DECL|macro|MUX_THRUB
mdefine_line|#define MUX_THRUB&t;1&t;&t;/* through B */
DECL|macro|MUX_WRAPA
mdefine_line|#define MUX_WRAPA&t;2&t;&t;/* wrap A */
DECL|macro|MUX_WRAPB
mdefine_line|#define MUX_WRAPB&t;3&t;&t;/* wrap B */
DECL|macro|MUX_ISOLATE
mdefine_line|#define MUX_ISOLATE&t;4&t;&t;/* isolated */
DECL|macro|MUX_WRAPS
mdefine_line|#define MUX_WRAPS&t;5&t;&t;/* SAS */
multiline_comment|/*&n; * MAC control&n; */
DECL|macro|MA_RESET
mdefine_line|#define MA_RESET&t;0
DECL|macro|MA_BEACON
mdefine_line|#define MA_BEACON&t;1
DECL|macro|MA_CLAIM
mdefine_line|#define MA_CLAIM&t;2
DECL|macro|MA_DIRECTED
mdefine_line|#define MA_DIRECTED&t;3&t;&t;/* directed beacon */
DECL|macro|MA_TREQ
mdefine_line|#define MA_TREQ&t;&t;4&t;&t;/* change T_Req */
DECL|macro|MA_OFFLINE
mdefine_line|#define MA_OFFLINE&t;5&t;&t;/* switch MAC to offline */
multiline_comment|/*&n; * trace prop&n; * bit map for trace propagation&n; */
DECL|macro|ENTITY_MAC
mdefine_line|#define ENTITY_MAC&t;(NUMPHYS)
DECL|macro|ENTITY_PHY
mdefine_line|#define ENTITY_PHY(p)&t;(p)
DECL|macro|ENTITY_BIT
mdefine_line|#define ENTITY_BIT(m)&t;(1&lt;&lt;(m))
multiline_comment|/*&n; * Resource Tag Types&n; */
DECL|macro|PATH_ISO
mdefine_line|#define PATH_ISO&t;0&t;/* isolated */
DECL|macro|PATH_PRIM
mdefine_line|#define PATH_PRIM&t;3&t;/* primary path */
DECL|macro|PATH_THRU
mdefine_line|#define PATH_THRU&t;5&t;/* through path */
DECL|macro|RES_MAC
mdefine_line|#define RES_MAC&t;&t;2&t;/* resource type MAC */
DECL|macro|RES_PORT
mdefine_line|#define RES_PORT&t;4&t;/* resource type PORT */
multiline_comment|/*&n; * CFM state&n; * oops: MUST MATCH CF-StateType in SMT7.2 !&n; */
DECL|macro|SC0_ISOLATED
mdefine_line|#define SC0_ISOLATED&t;0&t;&t;/* isolated */
DECL|macro|SC1_WRAP_A
mdefine_line|#define SC1_WRAP_A&t;5&t;&t;/* wrap A (not used) */
DECL|macro|SC2_WRAP_B
mdefine_line|#define SC2_WRAP_B&t;6&t;&t;/* wrap B (not used) */
DECL|macro|SC4_THRU_A
mdefine_line|#define SC4_THRU_A&t;12&t;&t;/* through A */
DECL|macro|SC5_THRU_B
mdefine_line|#define SC5_THRU_B&t;7&t;&t;/* through B (used in SMT 6.2) */
DECL|macro|SC7_WRAP_S
mdefine_line|#define SC7_WRAP_S&t;8&t;&t;/* SAS (not used) */
DECL|macro|SC9_C_WRAP_A
mdefine_line|#define SC9_C_WRAP_A&t;9&t;&t;/* c wrap A */
DECL|macro|SC10_C_WRAP_B
mdefine_line|#define SC10_C_WRAP_B&t;10&t;&t;/* c wrap B */
DECL|macro|SC11_C_WRAP_S
mdefine_line|#define SC11_C_WRAP_S&t;11&t;&t;/* c wrap S */
multiline_comment|/*&n; * convert MIB time in units of 80nS to uS&n; */
DECL|macro|MIB2US
mdefine_line|#define MIB2US(t)&t;&t;((t)/12)
DECL|macro|SEC2MIB
mdefine_line|#define SEC2MIB(s)&t;((s)*12500000L)
multiline_comment|/*&n; * SMT timer&n; */
DECL|struct|smt_timer
r_struct
id|smt_timer
(brace
DECL|member|tm_next
r_struct
id|smt_timer
op_star
id|tm_next
suffix:semicolon
multiline_comment|/* linked list */
DECL|member|tm_smc
r_struct
id|s_smc
op_star
id|tm_smc
suffix:semicolon
multiline_comment|/* pointer to context */
DECL|member|tm_delta
id|u_long
id|tm_delta
suffix:semicolon
multiline_comment|/* delta time */
DECL|member|tm_token
id|u_long
id|tm_token
suffix:semicolon
multiline_comment|/* token value */
DECL|member|tm_active
id|u_short
id|tm_active
suffix:semicolon
multiline_comment|/* flag : active/inactive */
DECL|member|tm_pad
id|u_short
id|tm_pad
suffix:semicolon
multiline_comment|/* pad field */
)brace
suffix:semicolon
multiline_comment|/*&n; * communication structures&n; */
DECL|struct|mac_parameter
r_struct
id|mac_parameter
(brace
DECL|member|t_neg
id|u_long
id|t_neg
suffix:semicolon
multiline_comment|/* T_Neg parameter */
DECL|member|t_pri
id|u_long
id|t_pri
suffix:semicolon
multiline_comment|/* T_Pri register in MAC */
)brace
suffix:semicolon
multiline_comment|/*&n; * MAC counters&n; */
DECL|struct|mac_counter
r_struct
id|mac_counter
(brace
DECL|member|mac_nobuf_counter
id|u_long
id|mac_nobuf_counter
suffix:semicolon
multiline_comment|/* MAC SW counter: no buffer */
DECL|member|mac_r_restart_counter
id|u_long
id|mac_r_restart_counter
suffix:semicolon
multiline_comment|/* MAC SW counter: rx restarted */
)brace
suffix:semicolon
multiline_comment|/*&n; * para struct context for SMT parameters&n; */
DECL|struct|s_pcon
r_struct
id|s_pcon
(brace
DECL|member|pc_len
r_int
id|pc_len
suffix:semicolon
DECL|member|pc_err
r_int
id|pc_err
suffix:semicolon
DECL|member|pc_badset
r_int
id|pc_badset
suffix:semicolon
DECL|member|pc_p
r_void
op_star
id|pc_p
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * link error monitor&n; */
DECL|macro|LEM_AVG
mdefine_line|#define LEM_AVG&t;5
DECL|struct|lem_counter
r_struct
id|lem_counter
(brace
macro_line|#ifdef&t;AM29K
DECL|member|lem_on
r_int
id|lem_on
suffix:semicolon
DECL|member|lem_errors
id|u_long
id|lem_errors
suffix:semicolon
DECL|member|lem_symbols
id|u_long
id|lem_symbols
suffix:semicolon
DECL|member|lem_tsymbols
id|u_long
id|lem_tsymbols
suffix:semicolon
DECL|member|lem_s_count
r_int
id|lem_s_count
suffix:semicolon
DECL|member|lem_n_s
r_int
id|lem_n_s
suffix:semicolon
DECL|member|lem_values
r_int
id|lem_values
suffix:semicolon
DECL|member|lem_index
r_int
id|lem_index
suffix:semicolon
DECL|member|lem_avg_ber
r_int
id|lem_avg_ber
(braket
id|LEM_AVG
)braket
suffix:semicolon
DECL|member|lem_sum
r_int
id|lem_sum
suffix:semicolon
macro_line|#else
id|u_short
id|lem_float_ber
suffix:semicolon
multiline_comment|/* 10E-nn bit error rate */
id|u_long
id|lem_errors
suffix:semicolon
multiline_comment|/* accumulated error count */
id|u_short
id|lem_on
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|NUMBITS
mdefine_line|#define NUMBITS&t;10
macro_line|#ifdef&t;AMDPLC
multiline_comment|/*&n; * PLC state table&n; */
DECL|struct|s_plc
r_struct
id|s_plc
(brace
DECL|member|p_state
id|u_short
id|p_state
suffix:semicolon
multiline_comment|/* current state */
DECL|member|p_bits
id|u_short
id|p_bits
suffix:semicolon
multiline_comment|/* number of bits to send */
DECL|member|p_start
id|u_short
id|p_start
suffix:semicolon
multiline_comment|/* first bit pos */
DECL|member|p_pad
id|u_short
id|p_pad
suffix:semicolon
multiline_comment|/* padding for alignment */
DECL|member|soft_err
id|u_long
id|soft_err
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|parity_err
id|u_long
id|parity_err
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|ebuf_err
id|u_long
id|ebuf_err
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|ebuf_cont
id|u_long
id|ebuf_cont
suffix:semicolon
multiline_comment|/* continous error counter */
DECL|member|phyinv
id|u_long
id|phyinv
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|vsym_ctr
id|u_long
id|vsym_ctr
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|mini_ctr
id|u_long
id|mini_ctr
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|tpc_exp
id|u_long
id|tpc_exp
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|np_err
id|u_long
id|np_err
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|b_pcs
id|u_long
id|b_pcs
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|b_tpc
id|u_long
id|b_tpc
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|b_tne
id|u_long
id|b_tne
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|b_qls
id|u_long
id|b_qls
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|b_ils
id|u_long
id|b_ils
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|b_hls
id|u_long
id|b_hls
suffix:semicolon
multiline_comment|/* error counter */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;PROTOTYP_INC
macro_line|#include &quot;fddi/driver.pro&quot;
macro_line|#else&t;/* PROTOTYP_INC */
multiline_comment|/*&n; * function prototypes&n; */
macro_line|#include &quot;h/mbuf.h&quot;&t;/* Type definitions for MBUFs */
r_void
id|hwt_restart
c_func
(paren
multiline_comment|/* hwt.c */
macro_line|#ifdef ANSIC
r_struct
id|s_smc
op_star
id|smc
macro_line|#endif
)paren
suffix:semicolon
id|SMbuf
op_star
id|smt_build_frame
c_func
(paren
multiline_comment|/* smt.c */
macro_line|#ifdef ANSIC
r_struct
id|s_smc
op_star
id|smc
comma
r_int
r_class
comma
r_int
id|type
comma
r_int
id|length
macro_line|#endif
)paren
suffix:semicolon
id|SMbuf
op_star
id|smt_get_mbuf
c_func
(paren
multiline_comment|/* drvsr.c */
macro_line|#ifdef ANSIC
r_struct
id|s_smc
op_star
id|smc
macro_line|#endif
)paren
suffix:semicolon
r_void
op_star
id|sm_to_para
c_func
(paren
multiline_comment|/* smt.c */
macro_line|#ifdef ANSIC
r_struct
id|s_smc
op_star
id|smc
comma
r_struct
id|smt_header
op_star
id|sm
comma
r_int
id|para
macro_line|#endif
)paren
suffix:semicolon
macro_line|#ifndef SK_UNUSED
DECL|macro|SK_UNUSED
mdefine_line|#define SK_UNUSED(var)&t;&t;(void)(var)
macro_line|#endif
r_void
id|queue_event
c_func
(paren
)paren
suffix:semicolon
r_void
id|ecm
c_func
(paren
)paren
suffix:semicolon
r_void
id|ecm_init
c_func
(paren
)paren
suffix:semicolon
r_void
id|rmt
c_func
(paren
)paren
suffix:semicolon
r_void
id|rmt_init
c_func
(paren
)paren
suffix:semicolon
r_void
id|pcm
c_func
(paren
)paren
suffix:semicolon
r_void
id|pcm_init
c_func
(paren
)paren
suffix:semicolon
r_void
id|cfm
c_func
(paren
)paren
suffix:semicolon
r_void
id|cfm_init
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_timer_start
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_timer_stop
c_func
(paren
)paren
suffix:semicolon
r_void
id|pcm_status_state
c_func
(paren
)paren
suffix:semicolon
r_void
id|plc_config_mux
c_func
(paren
)paren
suffix:semicolon
r_void
id|sm_lem_evaluate
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_clear_una_dna
c_func
(paren
)paren
suffix:semicolon
r_void
id|mac_status_para
c_func
(paren
)paren
suffix:semicolon
r_void
id|mac_update_counter
c_func
(paren
)paren
suffix:semicolon
r_void
id|sm_pm_ls_latch
c_func
(paren
)paren
suffix:semicolon
r_void
id|sm_ma_control
c_func
(paren
)paren
suffix:semicolon
r_void
id|sm_mac_check_beacon_claim
c_func
(paren
)paren
suffix:semicolon
r_void
id|config_mux
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_agent_init
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_timer_init
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_received_pack
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_add_para
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_swap_para
c_func
(paren
)paren
suffix:semicolon
r_void
id|ev_init
c_func
(paren
)paren
suffix:semicolon
r_void
id|hwt_init
c_func
(paren
)paren
suffix:semicolon
id|u_long
id|hwt_read
c_func
(paren
)paren
suffix:semicolon
r_void
id|hwt_stop
c_func
(paren
)paren
suffix:semicolon
r_void
id|hwt_start
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_send_mbuf
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_free_mbuf
c_func
(paren
)paren
suffix:semicolon
r_void
id|sm_pm_bypass_req
c_func
(paren
)paren
suffix:semicolon
r_void
id|rmt_indication
c_func
(paren
)paren
suffix:semicolon
r_void
id|cfm_state_change
c_func
(paren
)paren
suffix:semicolon
r_void
id|rx_indication
c_func
(paren
)paren
suffix:semicolon
r_void
id|tx_indication
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef NO_SMT_PANIC
r_void
id|smt_panic
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
macro_line|#ifdef&t;DEBUG
r_void
id|smt_panic
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
DECL|macro|smt_panic
mdefine_line|#define&t;smt_panic(smc,text)
macro_line|#endif&t;/* DEBUG */
macro_line|#endif&t;/* NO_SMT_PANIC */
r_void
id|smt_stat_counter
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_timer_poll
c_func
(paren
)paren
suffix:semicolon
id|u_long
id|smt_get_time
c_func
(paren
)paren
suffix:semicolon
id|u_long
id|smt_get_tid
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_timer_done
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_set_defaults
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_fixup_mib
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_reset_defaults
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_agent_task
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_please_reconnect
c_func
(paren
)paren
suffix:semicolon
r_int
id|smt_check_para
c_func
(paren
)paren
suffix:semicolon
r_void
id|driver_get_bia
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef&t;SUPERNET_3
r_void
id|drv_reset_indication
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;/* SUPERNET_3 */
r_void
id|smt_start_watchdog
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_event
c_func
(paren
)paren
suffix:semicolon
r_void
id|pcm_event
c_func
(paren
)paren
suffix:semicolon
r_void
id|rmt_event
c_func
(paren
)paren
suffix:semicolon
r_void
id|cfm_event
c_func
(paren
)paren
suffix:semicolon
r_void
id|timer_event
c_func
(paren
)paren
suffix:semicolon
r_void
id|ev_dispatcher
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_get_state
c_func
(paren
)paren
suffix:semicolon
r_void
id|ecm_get_state
c_func
(paren
)paren
suffix:semicolon
r_void
id|pcm_get_state
c_func
(paren
)paren
suffix:semicolon
r_void
id|rmt_get_state
c_func
(paren
)paren
suffix:semicolon
r_void
id|ecm_state_change
c_func
(paren
)paren
suffix:semicolon
r_int
id|sm_pm_bypass_present
c_func
(paren
)paren
suffix:semicolon
r_void
id|pcm_state_change
c_func
(paren
)paren
suffix:semicolon
r_void
id|rmt_state_change
c_func
(paren
)paren
suffix:semicolon
r_int
id|sm_pm_get_ls
c_func
(paren
)paren
suffix:semicolon
r_int
id|pcm_get_s_port
c_func
(paren
)paren
suffix:semicolon
r_int
id|pcm_rooted_station
c_func
(paren
)paren
suffix:semicolon
r_int
id|cfm_get_mac_input
c_func
(paren
)paren
suffix:semicolon
r_int
id|cfm_get_mac_output
c_func
(paren
)paren
suffix:semicolon
r_int
id|port_to_mib
c_func
(paren
)paren
suffix:semicolon
r_int
id|cem_build_path
c_func
(paren
)paren
suffix:semicolon
r_int
id|sm_mac_get_tx_state
c_func
(paren
)paren
suffix:semicolon
r_int
id|is_individual
c_func
(paren
)paren
suffix:semicolon
r_int
id|is_my_addr
c_func
(paren
)paren
suffix:semicolon
r_int
id|is_broadcast
c_func
(paren
)paren
suffix:semicolon
r_int
id|is_equal
c_func
(paren
)paren
suffix:semicolon
r_char
op_star
id|get_pcmstate
c_func
(paren
)paren
suffix:semicolon
r_int
id|smt_action
c_func
(paren
)paren
suffix:semicolon
id|u_short
id|smt_online
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_force_irq
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_pmf_received_pack
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_send_frame
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_set_timestamp
c_func
(paren
)paren
suffix:semicolon
r_void
id|mac_set_rx_mode
c_func
(paren
)paren
suffix:semicolon
r_int
id|mac_add_multicast
c_func
(paren
)paren
suffix:semicolon
r_int
id|mac_set_func_addr
c_func
(paren
)paren
suffix:semicolon
r_void
id|mac_del_multicast
c_func
(paren
)paren
suffix:semicolon
r_void
id|mac_update_multicast
c_func
(paren
)paren
suffix:semicolon
r_void
id|mac_clear_multicast
c_func
(paren
)paren
suffix:semicolon
r_void
id|mac_rx_directed_beacon
c_func
(paren
)paren
suffix:semicolon
r_void
id|set_formac_tsync
c_func
(paren
)paren
suffix:semicolon
r_void
id|formac_reinit_tx
c_func
(paren
)paren
suffix:semicolon
r_void
id|formac_tx_restart
c_func
(paren
)paren
suffix:semicolon
r_void
id|process_receive
c_func
(paren
)paren
suffix:semicolon
r_void
id|init_driver_fplus
c_func
(paren
)paren
suffix:semicolon
r_void
id|rtm_irq
c_func
(paren
)paren
suffix:semicolon
r_void
id|rtm_set_timer
c_func
(paren
)paren
suffix:semicolon
r_void
id|ring_status_indication
c_func
(paren
)paren
suffix:semicolon
r_void
id|llc_recover_tx
c_func
(paren
)paren
suffix:semicolon
r_void
id|llc_restart_tx
c_func
(paren
)paren
suffix:semicolon
r_void
id|plc_clear_irq
c_func
(paren
)paren
suffix:semicolon
r_void
id|plc_irq
c_func
(paren
)paren
suffix:semicolon
r_int
id|smt_set_mac_opvalues
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef&t;TAG_MODE
r_void
id|mac_drv_pci_fix
c_func
(paren
)paren
suffix:semicolon
r_void
id|mac_do_pci_fix
c_func
(paren
)paren
suffix:semicolon
r_void
id|mac_drv_clear_tx_queue
c_func
(paren
)paren
suffix:semicolon
r_void
id|mac_drv_repair_descr
c_func
(paren
)paren
suffix:semicolon
id|u_long
id|hwt_quick_read
c_func
(paren
)paren
suffix:semicolon
r_void
id|hwt_wait_time
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef SMT_PNMI
macro_line|#ifdef ANSIC
r_int
id|pnmi_init
(paren
r_struct
id|s_smc
op_star
id|smc
)paren
suffix:semicolon
r_int
id|pnmi_process_ndis_id
(paren
r_struct
id|s_smc
op_star
id|smc
comma
id|u_long
id|ndis_oid
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
op_star
id|BytesAccessed
comma
r_int
op_star
id|BytesNeeded
comma
id|u_char
id|action
)paren
suffix:semicolon
macro_line|#else
r_int
id|pnmi_init
(paren
)paren
suffix:semicolon
r_int
id|pnmi_process_ndis_id
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifdef&t;SBA
macro_line|#ifndef _H2INC
r_void
id|sba
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_void
id|sba_raf_received_pack
c_func
(paren
)paren
suffix:semicolon
r_void
id|sba_timer_poll
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_init_sba
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;ESS
r_int
id|ess_raf_received_pack
c_func
(paren
)paren
suffix:semicolon
r_void
id|ess_timer_poll
c_func
(paren
)paren
suffix:semicolon
r_void
id|ess_para_change
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;BOOT
DECL|macro|smt_srf_event
mdefine_line|#define smt_srf_event(a,b,c,d)
DECL|macro|smt_init_evc
mdefine_line|#define smt_init_evc(a)
macro_line|#else
r_void
id|smt_init_evc
c_func
(paren
)paren
suffix:semicolon
r_void
id|smt_srf_event
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef SMT_REAL_TOKEN_CT
r_void
id|smt_emulate_token_ct
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(DEBUG) &amp;&amp; !defined(BOOT)
r_void
id|dump_smt
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
DECL|macro|dump_smt
mdefine_line|#define&t;dump_smt(smc,sm,text)
macro_line|#endif
macro_line|#ifdef&t;DEBUG
r_char
op_star
id|addr_to_string
c_func
(paren
)paren
suffix:semicolon
r_void
id|dump_hex
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* PROTOTYP_INC */
multiline_comment|/* PNMI default defines */
macro_line|#ifndef PNMI_INIT
DECL|macro|PNMI_INIT
mdefine_line|#define&t;PNMI_INIT(smc)&t;/* Nothing */
macro_line|#endif
macro_line|#ifndef PNMI_GET_ID
DECL|macro|PNMI_GET_ID
mdefine_line|#define PNMI_GET_ID( smc, ndis_oid, buf, len, BytesWritten, BytesNeeded ) &bslash;&n;&t;&t;( 1 ? (-1) : (-1) )
macro_line|#endif
macro_line|#ifndef PNMI_SET_ID
DECL|macro|PNMI_SET_ID
mdefine_line|#define PNMI_SET_ID( smc, ndis_oid, buf, len, BytesRead, BytesNeeded, &bslash;&n;&t;&t;set_type) ( 1 ? (-1) : (-1) )
macro_line|#endif
multiline_comment|/*&n; * SMT_PANIC defines&n; */
macro_line|#ifndef&t;SMT_PANIC
DECL|macro|SMT_PANIC
mdefine_line|#define&t;SMT_PANIC(smc,nr,msg)&t;smt_panic (smc, msg)
macro_line|#endif
macro_line|#ifndef&t;SMT_ERR_LOG
DECL|macro|SMT_ERR_LOG
mdefine_line|#define&t;SMT_ERR_LOG(smc,nr,msg)&t;SMT_PANIC (smc, nr, msg)
macro_line|#endif
macro_line|#ifndef&t;SMT_EBASE
DECL|macro|SMT_EBASE
mdefine_line|#define&t;SMT_EBASE&t;100
macro_line|#endif
DECL|macro|SMT_E0100
mdefine_line|#define&t;SMT_E0100&t;SMT_EBASE + 0
DECL|macro|SMT_E0100_MSG
mdefine_line|#define&t;SMT_E0100_MSG&t;&quot;cfm FSM: illegal ce_type&quot;
DECL|macro|SMT_E0101
mdefine_line|#define&t;SMT_E0101&t;SMT_EBASE + 1
DECL|macro|SMT_E0101_MSG
mdefine_line|#define&t;SMT_E0101_MSG&t;&quot;CEM: case ???&quot;
DECL|macro|SMT_E0102
mdefine_line|#define&t;SMT_E0102&t;SMT_EBASE + 2
DECL|macro|SMT_E0102_MSG
mdefine_line|#define&t;SMT_E0102_MSG&t;&quot;CEM A: illegal state&quot;
DECL|macro|SMT_E0103
mdefine_line|#define&t;SMT_E0103&t;SMT_EBASE + 3
DECL|macro|SMT_E0103_MSG
mdefine_line|#define&t;SMT_E0103_MSG&t;&quot;CEM B: illegal state&quot;
DECL|macro|SMT_E0104
mdefine_line|#define&t;SMT_E0104&t;SMT_EBASE + 4
DECL|macro|SMT_E0104_MSG
mdefine_line|#define&t;SMT_E0104_MSG&t;&quot;CEM M: illegal state&quot;
DECL|macro|SMT_E0105
mdefine_line|#define&t;SMT_E0105&t;SMT_EBASE + 5
DECL|macro|SMT_E0105_MSG
mdefine_line|#define&t;SMT_E0105_MSG&t;&quot;CEM S: illegal state&quot;
DECL|macro|SMT_E0106
mdefine_line|#define&t;SMT_E0106&t;SMT_EBASE + 6
DECL|macro|SMT_E0106_MSG
mdefine_line|#define&t;SMT_E0106_MSG&t;&quot;CFM : illegal state&quot;
DECL|macro|SMT_E0107
mdefine_line|#define&t;SMT_E0107&t;SMT_EBASE + 7
DECL|macro|SMT_E0107_MSG
mdefine_line|#define&t;SMT_E0107_MSG&t;&quot;ECM : illegal state&quot;
DECL|macro|SMT_E0108
mdefine_line|#define&t;SMT_E0108&t;SMT_EBASE + 8
DECL|macro|SMT_E0108_MSG
mdefine_line|#define&t;SMT_E0108_MSG&t;&quot;prop_actions : NAC in DAS CFM&quot;
DECL|macro|SMT_E0109
mdefine_line|#define&t;SMT_E0109&t;SMT_EBASE + 9
DECL|macro|SMT_E0109_MSG
mdefine_line|#define&t;SMT_E0109_MSG&t;&quot;ST2U.FM_SERRSF error in special frame&quot;
DECL|macro|SMT_E0110
mdefine_line|#define&t;SMT_E0110&t;SMT_EBASE + 10
DECL|macro|SMT_E0110_MSG
mdefine_line|#define&t;SMT_E0110_MSG&t;&quot;ST2U.FM_SRFRCTOV recv. count. overflow&quot;
DECL|macro|SMT_E0111
mdefine_line|#define&t;SMT_E0111&t;SMT_EBASE + 11
DECL|macro|SMT_E0111_MSG
mdefine_line|#define&t;SMT_E0111_MSG&t;&quot;ST2U.FM_SNFSLD NP &amp; FORMAC simult. load&quot;
DECL|macro|SMT_E0112
mdefine_line|#define&t;SMT_E0112&t;SMT_EBASE + 12
DECL|macro|SMT_E0112_MSG
mdefine_line|#define&t;SMT_E0112_MSG&t;&quot;ST2U.FM_SRCVFRM single-frame recv.-mode&quot;
DECL|macro|SMT_E0113
mdefine_line|#define&t;SMT_E0113&t;SMT_EBASE + 13
DECL|macro|SMT_E0113_MSG
mdefine_line|#define&t;SMT_E0113_MSG&t;&quot;FPLUS: Buffer Memory Error&quot;
DECL|macro|SMT_E0114
mdefine_line|#define&t;SMT_E0114&t;SMT_EBASE + 14
DECL|macro|SMT_E0114_MSG
mdefine_line|#define&t;SMT_E0114_MSG&t;&quot;ST2U.FM_SERRSF error in special frame&quot;
DECL|macro|SMT_E0115
mdefine_line|#define&t;SMT_E0115&t;SMT_EBASE + 15
DECL|macro|SMT_E0115_MSG
mdefine_line|#define&t;SMT_E0115_MSG&t;&quot;ST3L: parity error in receive queue 2&quot;
DECL|macro|SMT_E0116
mdefine_line|#define&t;SMT_E0116&t;SMT_EBASE + 16
DECL|macro|SMT_E0116_MSG
mdefine_line|#define&t;SMT_E0116_MSG&t;&quot;ST3L: parity error in receive queue 1&quot;
DECL|macro|SMT_E0117
mdefine_line|#define&t;SMT_E0117&t;SMT_EBASE + 17
DECL|macro|SMT_E0117_MSG
mdefine_line|#define&t;SMT_E0117_MSG&t;&quot;E_SMT_001: RxD count for receive queue 1 = 0&quot;
DECL|macro|SMT_E0118
mdefine_line|#define&t;SMT_E0118&t;SMT_EBASE + 18
DECL|macro|SMT_E0118_MSG
mdefine_line|#define&t;SMT_E0118_MSG&t;&quot;PCM : illegal state&quot;
DECL|macro|SMT_E0119
mdefine_line|#define&t;SMT_E0119&t;SMT_EBASE + 19
DECL|macro|SMT_E0119_MSG
mdefine_line|#define&t;SMT_E0119_MSG&t;&quot;smt_add_para&quot;
DECL|macro|SMT_E0120
mdefine_line|#define&t;SMT_E0120&t;SMT_EBASE + 20
DECL|macro|SMT_E0120_MSG
mdefine_line|#define&t;SMT_E0120_MSG&t;&quot;smt_set_para&quot;
DECL|macro|SMT_E0121
mdefine_line|#define&t;SMT_E0121&t;SMT_EBASE + 21
DECL|macro|SMT_E0121_MSG
mdefine_line|#define&t;SMT_E0121_MSG&t;&quot;illegal event in dispatcher&quot;
DECL|macro|SMT_E0122
mdefine_line|#define&t;SMT_E0122&t;SMT_EBASE + 22
DECL|macro|SMT_E0122_MSG
mdefine_line|#define&t;SMT_E0122_MSG&t;&quot;RMT : illegal state&quot;
DECL|macro|SMT_E0123
mdefine_line|#define&t;SMT_E0123&t;SMT_EBASE + 23
DECL|macro|SMT_E0123_MSG
mdefine_line|#define&t;SMT_E0123_MSG&t;&quot;SBA: state machine has illegal state&quot;
DECL|macro|SMT_E0124
mdefine_line|#define&t;SMT_E0124&t;SMT_EBASE + 24
DECL|macro|SMT_E0124_MSG
mdefine_line|#define&t;SMT_E0124_MSG&t;&quot;sba_free_session() called with NULL pointer&quot;
DECL|macro|SMT_E0125
mdefine_line|#define&t;SMT_E0125&t;SMT_EBASE + 25
DECL|macro|SMT_E0125_MSG
mdefine_line|#define&t;SMT_E0125_MSG&t;&quot;SBA : illegal session pointer&quot;
DECL|macro|SMT_E0126
mdefine_line|#define&t;SMT_E0126&t;SMT_EBASE + 26
DECL|macro|SMT_E0126_MSG
mdefine_line|#define&t;SMT_E0126_MSG&t;&quot;smt_free_mbuf() called with NULL pointer&bslash;n&quot;
DECL|macro|SMT_E0127
mdefine_line|#define&t;SMT_E0127&t;SMT_EBASE + 27
DECL|macro|SMT_E0127_MSG
mdefine_line|#define&t;SMT_E0127_MSG&t;&quot;sizeof evcs&quot;
DECL|macro|SMT_E0128
mdefine_line|#define&t;SMT_E0128&t;SMT_EBASE + 28
DECL|macro|SMT_E0128_MSG
mdefine_line|#define&t;SMT_E0128_MSG&t;&quot;evc-&gt;evc_cond_state = 0&quot;
DECL|macro|SMT_E0129
mdefine_line|#define&t;SMT_E0129&t;SMT_EBASE + 29
DECL|macro|SMT_E0129_MSG
mdefine_line|#define&t;SMT_E0129_MSG&t;&quot;evc-&gt;evc_multiple = 0&quot;
DECL|macro|SMT_E0130
mdefine_line|#define&t;SMT_E0130&t;SMT_EBASE + 30
DECL|macro|SMT_E0130_MSG
mdefine_line|#define&t;SMT_E0130_MSG&t;write_mdr_warning
DECL|macro|SMT_E0131
mdefine_line|#define&t;SMT_E0131&t;SMT_EBASE + 31
DECL|macro|SMT_E0131_MSG
mdefine_line|#define&t;SMT_E0131_MSG&t;cam_warning
DECL|macro|SMT_E0132
mdefine_line|#define SMT_E0132&t;SMT_EBASE + 32
DECL|macro|SMT_E0132_MSG
mdefine_line|#define SMT_E0132_MSG&t;&quot;ST1L.FM_SPCEPDx parity/coding error&quot;
DECL|macro|SMT_E0133
mdefine_line|#define SMT_E0133&t;SMT_EBASE + 33
DECL|macro|SMT_E0133_MSG
mdefine_line|#define SMT_E0133_MSG&t;&quot;ST1L.FM_STBURx tx buffer underrun&quot;
DECL|macro|SMT_E0134
mdefine_line|#define SMT_E0134&t;SMT_EBASE + 34
DECL|macro|SMT_E0134_MSG
mdefine_line|#define SMT_E0134_MSG&t;&quot;ST1L.FM_SPCEPDx parity error&quot;
DECL|macro|SMT_E0135
mdefine_line|#define SMT_E0135&t;SMT_EBASE + 35
DECL|macro|SMT_E0135_MSG
mdefine_line|#define SMT_E0135_MSG&t;&quot;RMT: duplicate MAC address detected. Ring left!&quot;
DECL|macro|SMT_E0136
mdefine_line|#define SMT_E0136&t;SMT_EBASE + 36
DECL|macro|SMT_E0136_MSG
mdefine_line|#define SMT_E0136_MSG&t;&quot;Elasticity Buffer hang-up&quot;
DECL|macro|SMT_E0137
mdefine_line|#define SMT_E0137&t;SMT_EBASE + 37
DECL|macro|SMT_E0137_MSG
mdefine_line|#define SMT_E0137_MSG&t;&quot;SMT: queue overrun&quot;
DECL|macro|SMT_E0138
mdefine_line|#define SMT_E0138&t;SMT_EBASE + 38
DECL|macro|SMT_E0138_MSG
mdefine_line|#define SMT_E0138_MSG&t;&quot;RMT: duplicate MAC address detected. Ring NOT left!&quot;
macro_line|#endif&t;/* _CMTDEF_ */
eof
