multiline_comment|/* $Id: l3_1tr6.h,v 2.2.6.1 2001/02/16 16:43:27 kai Exp $&n; *&n; *  German 1TR6 D-channel protocol defines&n; *&n; * This file is (c) under GNU General Public License&n; *&n; */
macro_line|#ifndef l3_1tr6
DECL|macro|l3_1tr6
mdefine_line|#define l3_1tr6
DECL|macro|PROTO_DIS_N0
mdefine_line|#define PROTO_DIS_N0 0x40
DECL|macro|PROTO_DIS_N1
mdefine_line|#define PROTO_DIS_N1 0x41
multiline_comment|/*&n; * MsgType N0&n; */
DECL|macro|MT_N0_REG_IND
mdefine_line|#define MT_N0_REG_IND 0x61
DECL|macro|MT_N0_CANC_IND
mdefine_line|#define MT_N0_CANC_IND 0x62
DECL|macro|MT_N0_FAC_STA
mdefine_line|#define MT_N0_FAC_STA 0x63
DECL|macro|MT_N0_STA_ACK
mdefine_line|#define MT_N0_STA_ACK 0x64
DECL|macro|MT_N0_STA_REJ
mdefine_line|#define MT_N0_STA_REJ 0x65
DECL|macro|MT_N0_FAC_INF
mdefine_line|#define MT_N0_FAC_INF 0x66
DECL|macro|MT_N0_INF_ACK
mdefine_line|#define MT_N0_INF_ACK 0x67
DECL|macro|MT_N0_INF_REJ
mdefine_line|#define MT_N0_INF_REJ 0x68
DECL|macro|MT_N0_CLOSE
mdefine_line|#define MT_N0_CLOSE   0x75
DECL|macro|MT_N0_CLO_ACK
mdefine_line|#define MT_N0_CLO_ACK 0x77
multiline_comment|/*&n; * MsgType N1&n; */
DECL|macro|MT_N1_ESC
mdefine_line|#define MT_N1_ESC 0x00
DECL|macro|MT_N1_ALERT
mdefine_line|#define MT_N1_ALERT 0x01
DECL|macro|MT_N1_CALL_SENT
mdefine_line|#define MT_N1_CALL_SENT 0x02
DECL|macro|MT_N1_CONN
mdefine_line|#define MT_N1_CONN 0x07
DECL|macro|MT_N1_CONN_ACK
mdefine_line|#define MT_N1_CONN_ACK 0x0F
DECL|macro|MT_N1_SETUP
mdefine_line|#define MT_N1_SETUP 0x05
DECL|macro|MT_N1_SETUP_ACK
mdefine_line|#define MT_N1_SETUP_ACK 0x0D
DECL|macro|MT_N1_RES
mdefine_line|#define MT_N1_RES 0x26
DECL|macro|MT_N1_RES_ACK
mdefine_line|#define MT_N1_RES_ACK 0x2E
DECL|macro|MT_N1_RES_REJ
mdefine_line|#define MT_N1_RES_REJ 0x22
DECL|macro|MT_N1_SUSP
mdefine_line|#define MT_N1_SUSP 0x25
DECL|macro|MT_N1_SUSP_ACK
mdefine_line|#define MT_N1_SUSP_ACK 0x2D
DECL|macro|MT_N1_SUSP_REJ
mdefine_line|#define MT_N1_SUSP_REJ 0x21
DECL|macro|MT_N1_USER_INFO
mdefine_line|#define MT_N1_USER_INFO 0x20
DECL|macro|MT_N1_DET
mdefine_line|#define MT_N1_DET 0x40
DECL|macro|MT_N1_DISC
mdefine_line|#define MT_N1_DISC 0x45
DECL|macro|MT_N1_REL
mdefine_line|#define MT_N1_REL 0x4D
DECL|macro|MT_N1_REL_ACK
mdefine_line|#define MT_N1_REL_ACK 0x5A
DECL|macro|MT_N1_CANC_ACK
mdefine_line|#define MT_N1_CANC_ACK 0x6E
DECL|macro|MT_N1_CANC_REJ
mdefine_line|#define MT_N1_CANC_REJ 0x67
DECL|macro|MT_N1_CON_CON
mdefine_line|#define MT_N1_CON_CON 0x69
DECL|macro|MT_N1_FAC
mdefine_line|#define MT_N1_FAC 0x60
DECL|macro|MT_N1_FAC_ACK
mdefine_line|#define MT_N1_FAC_ACK 0x68
DECL|macro|MT_N1_FAC_CAN
mdefine_line|#define MT_N1_FAC_CAN 0x66
DECL|macro|MT_N1_FAC_REG
mdefine_line|#define MT_N1_FAC_REG 0x64
DECL|macro|MT_N1_FAC_REJ
mdefine_line|#define MT_N1_FAC_REJ 0x65
DECL|macro|MT_N1_INFO
mdefine_line|#define MT_N1_INFO 0x6D
DECL|macro|MT_N1_REG_ACK
mdefine_line|#define MT_N1_REG_ACK 0x6C
DECL|macro|MT_N1_REG_REJ
mdefine_line|#define MT_N1_REG_REJ 0x6F
DECL|macro|MT_N1_STAT
mdefine_line|#define MT_N1_STAT 0x63
DECL|macro|MT_N1_INVALID
mdefine_line|#define MT_N1_INVALID 0
multiline_comment|/*&n; * W Elemente&n; */
DECL|macro|WE_Shift_F0
mdefine_line|#define WE_Shift_F0 0x90
DECL|macro|WE_Shift_F6
mdefine_line|#define WE_Shift_F6 0x96
DECL|macro|WE_Shift_OF0
mdefine_line|#define WE_Shift_OF0 0x98
DECL|macro|WE_Shift_OF6
mdefine_line|#define WE_Shift_OF6 0x9E
DECL|macro|WE0_cause
mdefine_line|#define WE0_cause 0x08
DECL|macro|WE0_connAddr
mdefine_line|#define WE0_connAddr 0x0C
DECL|macro|WE0_callID
mdefine_line|#define WE0_callID 0x10
DECL|macro|WE0_chanID
mdefine_line|#define WE0_chanID 0x18
DECL|macro|WE0_netSpecFac
mdefine_line|#define WE0_netSpecFac 0x20
DECL|macro|WE0_display
mdefine_line|#define WE0_display 0x28
DECL|macro|WE0_keypad
mdefine_line|#define WE0_keypad 0x2C
DECL|macro|WE0_origAddr
mdefine_line|#define WE0_origAddr 0x6C
DECL|macro|WE0_destAddr
mdefine_line|#define WE0_destAddr 0x70
DECL|macro|WE0_userInfo
mdefine_line|#define WE0_userInfo 0x7E
DECL|macro|WE0_moreData
mdefine_line|#define WE0_moreData 0xA0
DECL|macro|WE0_congestLevel
mdefine_line|#define WE0_congestLevel 0xB0
DECL|macro|WE6_serviceInd
mdefine_line|#define WE6_serviceInd 0x01
DECL|macro|WE6_chargingInfo
mdefine_line|#define WE6_chargingInfo 0x02
DECL|macro|WE6_date
mdefine_line|#define WE6_date 0x03
DECL|macro|WE6_facSelect
mdefine_line|#define WE6_facSelect 0x05
DECL|macro|WE6_facStatus
mdefine_line|#define WE6_facStatus 0x06
DECL|macro|WE6_statusCalled
mdefine_line|#define WE6_statusCalled 0x07
DECL|macro|WE6_addTransAttr
mdefine_line|#define WE6_addTransAttr 0x08
multiline_comment|/*&n; * FacCodes&n; */
DECL|macro|FAC_Sperre
mdefine_line|#define FAC_Sperre 0x01
DECL|macro|FAC_Sperre_All
mdefine_line|#define FAC_Sperre_All 0x02
DECL|macro|FAC_Sperre_Fern
mdefine_line|#define FAC_Sperre_Fern 0x03
DECL|macro|FAC_Sperre_Intl
mdefine_line|#define FAC_Sperre_Intl 0x04
DECL|macro|FAC_Sperre_Interk
mdefine_line|#define FAC_Sperre_Interk 0x05
DECL|macro|FAC_Forward1
mdefine_line|#define FAC_Forward1 0x02
DECL|macro|FAC_Forward2
mdefine_line|#define FAC_Forward2 0x03
DECL|macro|FAC_Konferenz
mdefine_line|#define FAC_Konferenz 0x06
DECL|macro|FAC_GrabBchan
mdefine_line|#define FAC_GrabBchan 0x0F
DECL|macro|FAC_Reactivate
mdefine_line|#define FAC_Reactivate 0x10
DECL|macro|FAC_Konferenz3
mdefine_line|#define FAC_Konferenz3 0x11
DECL|macro|FAC_Dienstwechsel1
mdefine_line|#define FAC_Dienstwechsel1 0x12
DECL|macro|FAC_Dienstwechsel2
mdefine_line|#define FAC_Dienstwechsel2 0x13
DECL|macro|FAC_NummernIdent
mdefine_line|#define FAC_NummernIdent 0x14
DECL|macro|FAC_GBG
mdefine_line|#define FAC_GBG 0x15
DECL|macro|FAC_DisplayUebergeben
mdefine_line|#define FAC_DisplayUebergeben 0x17
DECL|macro|FAC_DisplayUmgeleitet
mdefine_line|#define FAC_DisplayUmgeleitet 0x1A
DECL|macro|FAC_Unterdruecke
mdefine_line|#define FAC_Unterdruecke 0x1B
DECL|macro|FAC_Deactivate
mdefine_line|#define FAC_Deactivate 0x1E
DECL|macro|FAC_Activate
mdefine_line|#define FAC_Activate 0x1D
DECL|macro|FAC_SPV
mdefine_line|#define FAC_SPV 0x1F
DECL|macro|FAC_Rueckwechsel
mdefine_line|#define FAC_Rueckwechsel 0x23
DECL|macro|FAC_Umleitung
mdefine_line|#define FAC_Umleitung 0x24
multiline_comment|/*&n; * Cause codes&n; */
DECL|macro|CAUSE_InvCRef
mdefine_line|#define CAUSE_InvCRef 0x01
DECL|macro|CAUSE_BearerNotImpl
mdefine_line|#define CAUSE_BearerNotImpl 0x03
DECL|macro|CAUSE_CIDunknown
mdefine_line|#define CAUSE_CIDunknown 0x07
DECL|macro|CAUSE_CIDinUse
mdefine_line|#define CAUSE_CIDinUse 0x08
DECL|macro|CAUSE_NoChans
mdefine_line|#define CAUSE_NoChans 0x0A
DECL|macro|CAUSE_FacNotImpl
mdefine_line|#define CAUSE_FacNotImpl 0x10
DECL|macro|CAUSE_FacNotSubscr
mdefine_line|#define CAUSE_FacNotSubscr 0x11
DECL|macro|CAUSE_OutgoingBarred
mdefine_line|#define CAUSE_OutgoingBarred 0x20
DECL|macro|CAUSE_UserAccessBusy
mdefine_line|#define CAUSE_UserAccessBusy 0x21
DECL|macro|CAUSE_NegativeGBG
mdefine_line|#define CAUSE_NegativeGBG 0x22
DECL|macro|CAUSE_UnknownGBG
mdefine_line|#define CAUSE_UnknownGBG 0x23
DECL|macro|CAUSE_NoSPVknown
mdefine_line|#define CAUSE_NoSPVknown 0x25
DECL|macro|CAUSE_DestNotObtain
mdefine_line|#define CAUSE_DestNotObtain 0x35
DECL|macro|CAUSE_NumberChanged
mdefine_line|#define CAUSE_NumberChanged 0x38
DECL|macro|CAUSE_OutOfOrder
mdefine_line|#define CAUSE_OutOfOrder 0x39
DECL|macro|CAUSE_NoUserResponse
mdefine_line|#define CAUSE_NoUserResponse 0x3A
DECL|macro|CAUSE_UserBusy
mdefine_line|#define CAUSE_UserBusy 0x3B
DECL|macro|CAUSE_IncomingBarred
mdefine_line|#define CAUSE_IncomingBarred 0x3D
DECL|macro|CAUSE_CallRejected
mdefine_line|#define CAUSE_CallRejected 0x3E
DECL|macro|CAUSE_NetworkCongestion
mdefine_line|#define CAUSE_NetworkCongestion 0x59
DECL|macro|CAUSE_RemoteUser
mdefine_line|#define CAUSE_RemoteUser 0x5A
DECL|macro|CAUSE_LocalProcErr
mdefine_line|#define CAUSE_LocalProcErr 0x70
DECL|macro|CAUSE_RemoteProcErr
mdefine_line|#define CAUSE_RemoteProcErr 0x71
DECL|macro|CAUSE_RemoteUserSuspend
mdefine_line|#define CAUSE_RemoteUserSuspend 0x72
DECL|macro|CAUSE_RemoteUserResumed
mdefine_line|#define CAUSE_RemoteUserResumed 0x73
DECL|macro|CAUSE_UserInfoDiscarded
mdefine_line|#define CAUSE_UserInfoDiscarded 0x7F
DECL|macro|T303
mdefine_line|#define T303&t;4000
DECL|macro|T304
mdefine_line|#define T304&t;20000
DECL|macro|T305
mdefine_line|#define T305&t;4000
DECL|macro|T308
mdefine_line|#define T308&t;4000
DECL|macro|T310
mdefine_line|#define T310&t;120000
DECL|macro|T313
mdefine_line|#define T313&t;4000
DECL|macro|T318
mdefine_line|#define T318&t;4000
DECL|macro|T319
mdefine_line|#define T319&t;4000
macro_line|#endif
eof
