multiline_comment|/* $Id: message.h,v 1.1.10.1 2001/09/23 22:24:59 kai Exp $&n; *&n; * Copyright (C) 1996  SpellCaster Telecommunications Inc.&n; *&n; * structures, macros and defines useful for sending&n; * messages to the adapter&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For more information, please contact gpl-info@spellcast.com or write:&n; *&n; *     SpellCaster Telecommunications Inc.&n; *     5621 Finch Avenue East, Unit #3&n; *     Scarborough, Ontario  Canada&n; *     M1B 2T9&n; *     +1 (416) 297-8565&n; *     +1 (416) 297-6433 Facsimile&n; */
multiline_comment|/*&n; * Board message macros, defines and structures&n; */
macro_line|#ifndef MESSAGE_H
DECL|macro|MESSAGE_H
mdefine_line|#define MESSAGE_H
DECL|macro|MAX_MESSAGES
mdefine_line|#define MAX_MESSAGES&t;&t;32&t;/* Maximum messages that can be&n;&t;&t;&t;&t;&t;   queued */
DECL|macro|MSG_DATA_LEN
mdefine_line|#define MSG_DATA_LEN&t;&t;48&t;/* Maximum size of message payload */
DECL|macro|MSG_LEN
mdefine_line|#define MSG_LEN&t;&t;&t;64&t;/* Size of a message */
DECL|macro|CMPID
mdefine_line|#define CMPID&t;&t;&t;0&t;/* Loader message process ID */
DECL|macro|CEPID
mdefine_line|#define CEPID&t;&t;&t;64&t;/* Firmware message process ID */
multiline_comment|/*&n; * Macro to determine if a message is a loader message&n; */
DECL|macro|IS_CM_MESSAGE
mdefine_line|#define IS_CM_MESSAGE(mesg, tx, cx, dx)&t;&t;&bslash;&n;&t;&t;((mesg.type == cmRspType##tx)&t;&t;&bslash;&n;&t;&t;&amp;&amp;(mesg.class == cmRspClass##cx)&t;&bslash;&n;&t;&t;&amp;&amp;(mesg.code == cmRsp##dx))
multiline_comment|/*&n; * Macro to determine if a message is a firmware message&n; */
DECL|macro|IS_CE_MESSAGE
mdefine_line|#define IS_CE_MESSAGE(mesg, tx, cx, dx)&t;&t;&bslash;&n;&t;&t;((mesg.type == ceRspType##tx)&t;&t;&bslash;&n;&t;&t;&amp;&amp;(mesg.class == ceRspClass##cx)&t;&bslash;&n;&t;&t;&amp;&amp;(mesg.code == ceRsp##tx##dx))
multiline_comment|/* &n; * Loader Request and Response Messages&n; */
multiline_comment|/* message types */
DECL|macro|cmReqType1
mdefine_line|#define cmReqType1&t;&t;&t;1
DECL|macro|cmReqType2
mdefine_line|#define cmReqType2&t;&t;&t;2
DECL|macro|cmRspType0
mdefine_line|#define cmRspType0&t;&t;&t;0
DECL|macro|cmRspType1
mdefine_line|#define cmRspType1&t;&t;&t;1
DECL|macro|cmRspType2
mdefine_line|#define cmRspType2&t;&t;&t;2
DECL|macro|cmRspType5
mdefine_line|#define cmRspType5&t;&t;&t;5
multiline_comment|/* message classes */
DECL|macro|cmReqClass0
mdefine_line|#define cmReqClass0&t;&t;&t;0
DECL|macro|cmRspClass0
mdefine_line|#define cmRspClass0&t;&t;&t;0
multiline_comment|/* message codes */
DECL|macro|cmReqHWConfig
mdefine_line|#define cmReqHWConfig&t;&t;1&t;&t;&t;/* 1,0,1 */
DECL|macro|cmReqMsgLpbk
mdefine_line|#define cmReqMsgLpbk&t;&t;2&t;&t;&t;/* 1,0,2 */
DECL|macro|cmReqVersion
mdefine_line|#define cmReqVersion&t;&t;3&t;&t;&t;/* 1,0,3 */
DECL|macro|cmReqLoadProc
mdefine_line|#define cmReqLoadProc&t;&t;1&t;&t;&t;/* 2,0,1 */
DECL|macro|cmReqStartProc
mdefine_line|#define cmReqStartProc&t;&t;2&t;&t;&t;/* 2,0,2 */
DECL|macro|cmReqReadMem
mdefine_line|#define cmReqReadMem&t;&t;6&t;&t;&t;/* 2,0,6 */
DECL|macro|cmRspHWConfig
mdefine_line|#define cmRspHWConfig&t;&t;cmReqHWConfig
DECL|macro|cmRspMsgLpbk
mdefine_line|#define&t;cmRspMsgLpbk&t;&t;cmReqMsgLpbk
DECL|macro|cmRspVersion
mdefine_line|#define cmRspVersion&t;&t;cmReqVersion
DECL|macro|cmRspLoadProc
mdefine_line|#define cmRspLoadProc&t;&t;cmReqLoadProc
DECL|macro|cmRspStartProc
mdefine_line|#define cmRspStartProc&t;&t;cmReqStartProc
DECL|macro|cmRspReadMem
mdefine_line|#define&t;cmRspReadMem&t;&t;cmReqReadMem
DECL|macro|cmRspMiscEngineUp
mdefine_line|#define cmRspMiscEngineUp&t;1&t;&t;&t;/* 5,0,1 */
DECL|macro|cmRspInvalid
mdefine_line|#define cmRspInvalid&t;&t;0&t;&t;&t;/* 0,0,0 */
multiline_comment|/*&n; * Firmware Request and Response Messages&n; */
multiline_comment|/* message types */
DECL|macro|ceReqTypePhy
mdefine_line|#define ceReqTypePhy&t;&t;1
DECL|macro|ceReqTypeLnk
mdefine_line|#define ceReqTypeLnk&t;&t;2
DECL|macro|ceReqTypeCall
mdefine_line|#define ceReqTypeCall&t;&t;3
DECL|macro|ceReqTypeStat
mdefine_line|#define ceReqTypeStat&t;&t;1
DECL|macro|ceRspTypeErr
mdefine_line|#define ceRspTypeErr&t;&t;0
DECL|macro|ceRspTypePhy
mdefine_line|#define&t;ceRspTypePhy&t;&t;ceReqTypePhy
DECL|macro|ceRspTypeLnk
mdefine_line|#define ceRspTypeLnk&t;&t;ceReqTypeLnk
DECL|macro|ceRspTypeCall
mdefine_line|#define ceRspTypeCall&t;&t;ceReqTypeCall
DECL|macro|ceRspTypeStat
mdefine_line|#define ceRspTypeStat&t;&t;ceReqTypeStat
multiline_comment|/* message classes */
DECL|macro|ceReqClass0
mdefine_line|#define ceReqClass0&t;&t;0
DECL|macro|ceReqClass1
mdefine_line|#define ceReqClass1&t;&t;1
DECL|macro|ceReqClass2
mdefine_line|#define ceReqClass2&t;&t;2
DECL|macro|ceReqClass3
mdefine_line|#define ceReqClass3&t;&t;3
DECL|macro|ceRspClass0
mdefine_line|#define ceRspClass0&t;&t;ceReqClass0
DECL|macro|ceRspClass1
mdefine_line|#define ceRspClass1&t;&t;ceReqClass1
DECL|macro|ceRspClass2
mdefine_line|#define ceRspClass2&t;&t;ceReqClass2
DECL|macro|ceRspClass3
mdefine_line|#define ceRspClass3&t;&t;ceReqClass3
multiline_comment|/* message codes  (B) = BRI only, (P) = PRI only, (V) = POTS only */
DECL|macro|ceReqPhyProcInfo
mdefine_line|#define ceReqPhyProcInfo&t;1&t;&t;&t;/* 1,0,1 */
DECL|macro|ceReqPhyConnect
mdefine_line|#define ceReqPhyConnect&t;&t;1&t;&t;&t;/* 1,1,1 */
DECL|macro|ceReqPhyDisconnect
mdefine_line|#define ceReqPhyDisconnect&t;2&t;&t;&t;/* 1,1,2 */
DECL|macro|ceReqPhySetParams
mdefine_line|#define ceReqPhySetParams&t;3&t;&t;&t;/* 1,1,3 (P) */
DECL|macro|ceReqPhyGetParams
mdefine_line|#define ceReqPhyGetParams&t;4&t;&t;&t;/* 1,1,4 (P) */
DECL|macro|ceReqPhyStatus
mdefine_line|#define ceReqPhyStatus&t;&t;1&t;&t;&t;/* 1,2,1 */
DECL|macro|ceReqPhyAcfaStatus
mdefine_line|#define ceReqPhyAcfaStatus&t;2&t;&t;&t;/* 1,2,2 (P) */
DECL|macro|ceReqPhyChCallState
mdefine_line|#define ceReqPhyChCallState&t;3&t;&t;&t;/* 1,2,3 (P) */
DECL|macro|ceReqPhyChServState
mdefine_line|#define ceReqPhyChServState&t;4&t;&t;&t;/* 1,2,4 (P) */
DECL|macro|ceReqPhyRLoopBack
mdefine_line|#define ceReqPhyRLoopBack&t;1&t;&t;&t;/* 1,3,1 */
DECL|macro|ceRspPhyProcInfo
mdefine_line|#define ceRspPhyProcInfo&t;ceReqPhyProcInfo
DECL|macro|ceRspPhyConnect
mdefine_line|#define&t;ceRspPhyConnect&t;&t;ceReqPhyConnect
DECL|macro|ceRspPhyDisconnect
mdefine_line|#define ceRspPhyDisconnect&t;ceReqPhyDisconnect
DECL|macro|ceRspPhySetParams
mdefine_line|#define ceRspPhySetParams&t;ceReqPhySetParams
DECL|macro|ceRspPhyGetParams
mdefine_line|#define ceRspPhyGetParams&t;ceReqPhyGetParams
DECL|macro|ceRspPhyStatus
mdefine_line|#define ceRspPhyStatus&t;&t;ceReqPhyStatus
DECL|macro|ceRspPhyAcfaStatus
mdefine_line|#define ceRspPhyAcfaStatus&t;ceReqPhyAcfaStatus
DECL|macro|ceRspPhyChCallState
mdefine_line|#define ceRspPhyChCallState&t;ceReqPhyChCallState
DECL|macro|ceRspPhyChServState
mdefine_line|#define ceRspPhyChServState&t;ceReqPhyChServState
DECL|macro|ceRspPhyRLoopBack
mdefine_line|#define ceRspPhyRLoopBack&t;ceReqphyRLoopBack
DECL|macro|ceReqLnkSetParam
mdefine_line|#define ceReqLnkSetParam&t;1&t;&t;&t;/* 2,0,1 */
DECL|macro|ceReqLnkGetParam
mdefine_line|#define ceReqLnkGetParam&t;2&t;&t;&t;/* 2,0,2 */
DECL|macro|ceReqLnkGetStats
mdefine_line|#define ceReqLnkGetStats&t;3&t;&t;&t;/* 2,0,3 */
DECL|macro|ceReqLnkWrite
mdefine_line|#define ceReqLnkWrite&t;&t;1&t;&t;&t;/* 2,1,1 */
DECL|macro|ceReqLnkRead
mdefine_line|#define ceReqLnkRead&t;&t;2&t;&t;&t;/* 2,1,2 */
DECL|macro|ceReqLnkFlush
mdefine_line|#define ceReqLnkFlush&t;&t;3&t;&t;&t;/* 2,1,3 */
DECL|macro|ceReqLnkWrBufTrc
mdefine_line|#define ceReqLnkWrBufTrc&t;4&t;&t;&t;/* 2,1,4 */
DECL|macro|ceReqLnkRdBufTrc
mdefine_line|#define ceReqLnkRdBufTrc&t;5&t;&t;&t;/* 2,1,5 */
DECL|macro|ceRspLnkSetParam
mdefine_line|#define ceRspLnkSetParam&t;ceReqLnkSetParam
DECL|macro|ceRspLnkGetParam
mdefine_line|#define ceRspLnkGetParam&t;ceReqLnkGetParam
DECL|macro|ceRspLnkGetStats
mdefine_line|#define ceRspLnkGetStats&t;ceReqLnkGetStats
DECL|macro|ceRspLnkWrite
mdefine_line|#define ceRspLnkWrite&t;&t;ceReqLnkWrite
DECL|macro|ceRspLnkRead
mdefine_line|#define ceRspLnkRead&t;&t;ceReqLnkRead
DECL|macro|ceRspLnkFlush
mdefine_line|#define ceRspLnkFlush&t;&t;ceReqLnkFlush
DECL|macro|ceRspLnkWrBufTrc
mdefine_line|#define ceRspLnkWrBufTrc&t;ceReqLnkWrBufTrc
DECL|macro|ceRspLnkRdBufTrc
mdefine_line|#define ceRspLnkRdBufTrc&t;ceReqLnkRdBufTrc
DECL|macro|ceReqCallSetSwitchType
mdefine_line|#define ceReqCallSetSwitchType&t;1&t;&t;&t;/* 3,0,1 */
DECL|macro|ceReqCallGetSwitchType
mdefine_line|#define ceReqCallGetSwitchType&t;2&t;&t;&t;/* 3,0,2 */
DECL|macro|ceReqCallSetFrameFormat
mdefine_line|#define ceReqCallSetFrameFormat&t;3&t;&t;&t;/* 3,0,3 */
DECL|macro|ceReqCallGetFrameFormat
mdefine_line|#define ceReqCallGetFrameFormat&t;4&t;&t;&t;/* 3,0,4 */
DECL|macro|ceReqCallSetCallType
mdefine_line|#define ceReqCallSetCallType&t;5&t;&t;&t;/* 3,0,5 */
DECL|macro|ceReqCallGetCallType
mdefine_line|#define ceReqCallGetCallType&t;6&t;&t;&t;/* 3,0,6 */
DECL|macro|ceReqCallSetSPID
mdefine_line|#define ceReqCallSetSPID&t;7&t;&t;&t;/* 3,0,7 (!P) */
DECL|macro|ceReqCallGetSPID
mdefine_line|#define ceReqCallGetSPID&t;8&t;&t;&t;/* 3,0,8 (!P) */
DECL|macro|ceReqCallSetMyNumber
mdefine_line|#define ceReqCallSetMyNumber&t;9&t;&t;&t;/* 3,0,9 (!P) */
DECL|macro|ceReqCallGetMyNumber
mdefine_line|#define ceReqCallGetMyNumber&t;10&t;&t;&t;/* 3,0,10 (!P) */
DECL|macro|ceRspCallSetSwitchType
mdefine_line|#define&t;ceRspCallSetSwitchType&t;ceReqCallSetSwitchType
DECL|macro|ceRspCallGetSwitchType
mdefine_line|#define ceRspCallGetSwitchType&t;ceReqCallSetSwitchType
DECL|macro|ceRspCallSetFrameFormat
mdefine_line|#define ceRspCallSetFrameFormat&t;ceReqCallSetFrameFormat
DECL|macro|ceRspCallGetFrameFormat
mdefine_line|#define ceRspCallGetFrameFormat&t;ceReqCallGetFrameFormat
DECL|macro|ceRspCallSetCallType
mdefine_line|#define ceRspCallSetCallType&t;ceReqCallSetCallType
DECL|macro|ceRspCallGetCallType
mdefine_line|#define ceRspCallGetCallType&t;ceReqCallGetCallType
DECL|macro|ceRspCallSetSPID
mdefine_line|#define ceRspCallSetSPID&t;ceReqCallSetSPID
DECL|macro|ceRspCallGetSPID
mdefine_line|#define ceRspCallGetSPID&t;ceReqCallGetSPID
DECL|macro|ceRspCallSetMyNumber
mdefine_line|#define ceRspCallSetMyNumber&t;ceReqCallSetMyNumber
DECL|macro|ceRspCallGetMyNumber
mdefine_line|#define ceRspCallGetMyNumber&t;ceReqCallGetMyNumber
DECL|macro|ceRspStatAcfaStatus
mdefine_line|#define ceRspStatAcfaStatus&t;2
DECL|macro|ceRspStat
mdefine_line|#define ceRspStat
DECL|macro|ceRspErrError
mdefine_line|#define ceRspErrError&t;&t;0&t;&t;&t;/* 0,0,0 */
multiline_comment|/*&n; * Call Types&n; */
DECL|macro|CALLTYPE_64K
mdefine_line|#define CALLTYPE_64K&t;&t;0
DECL|macro|CALLTYPE_56K
mdefine_line|#define CALLTYPE_56K&t;&t;1
DECL|macro|CALLTYPE_SPEECH
mdefine_line|#define CALLTYPE_SPEECH&t;&t;2
DECL|macro|CALLTYPE_31KHZ
mdefine_line|#define CALLTYPE_31KHZ&t;&t;3
multiline_comment|/*&n; * Link Level data contains a pointer to and the length of&n; * a buffer in shared RAM. Used by LnkRead and LnkWrite message&n; * types. Part of RspMsgStruct and ReqMsgStruct.&n; */
r_typedef
r_struct
(brace
DECL|member|buff_offset
r_int
r_int
id|buff_offset
suffix:semicolon
DECL|member|msg_len
r_int
r_int
id|msg_len
suffix:semicolon
DECL|typedef|LLData
)brace
id|LLData
suffix:semicolon
multiline_comment|/* &n; * Message payload template for an HWConfig message&n; */
r_typedef
r_struct
(brace
DECL|member|st_u_sense
r_char
id|st_u_sense
suffix:semicolon
DECL|member|powr_sense
r_char
id|powr_sense
suffix:semicolon
DECL|member|sply_sense
r_char
id|sply_sense
suffix:semicolon
DECL|member|asic_id
r_int
r_char
id|asic_id
suffix:semicolon
DECL|member|ram_size
r_int
id|ram_size
suffix:semicolon
DECL|member|serial_no
r_char
id|serial_no
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|part_no
r_char
id|part_no
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|rev_no
r_char
id|rev_no
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|HWConfig_pl
)brace
id|HWConfig_pl
suffix:semicolon
multiline_comment|/*&n; * A Message&n; */
DECL|struct|message
r_struct
id|message
(brace
DECL|member|sequence_no
r_int
r_char
id|sequence_no
suffix:semicolon
DECL|member|process_id
r_int
r_char
id|process_id
suffix:semicolon
DECL|member|time_stamp
r_int
r_char
id|time_stamp
suffix:semicolon
DECL|member|cmd_sequence_no
r_int
r_char
id|cmd_sequence_no
suffix:semicolon
multiline_comment|/* Rsp messages only */
DECL|member|reserved1
r_int
r_char
id|reserved1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|msg_byte_cnt
r_int
r_char
id|msg_byte_cnt
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|class
r_int
r_char
r_class
suffix:semicolon
DECL|member|code
r_int
r_char
id|code
suffix:semicolon
DECL|member|phy_link_no
r_int
r_char
id|phy_link_no
suffix:semicolon
DECL|member|rsp_status
r_int
r_char
id|rsp_status
suffix:semicolon
multiline_comment|/* Rsp messages only */
DECL|member|reseved2
r_int
r_char
id|reseved2
(braket
l_int|3
)braket
suffix:semicolon
r_union
(brace
DECL|member|byte_array
r_int
r_char
id|byte_array
(braket
id|MSG_DATA_LEN
)braket
suffix:semicolon
DECL|member|response
id|LLData
id|response
suffix:semicolon
DECL|member|HWCresponse
id|HWConfig_pl
id|HWCresponse
suffix:semicolon
DECL|member|msg_data
)brace
id|msg_data
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|ReqMessage
r_typedef
r_struct
id|message
id|ReqMessage
suffix:semicolon
multiline_comment|/* Request message */
DECL|typedef|RspMessage
r_typedef
r_struct
id|message
id|RspMessage
suffix:semicolon
multiline_comment|/* Response message */
multiline_comment|/*&n; * The first 5010 bytes of shared memory contain the message queues,&n; * indexes and other data. This structure is its template&n; */
r_typedef
r_struct
(brace
DECL|member|req_queue
r_volatile
id|ReqMessage
id|req_queue
(braket
id|MAX_MESSAGES
)braket
suffix:semicolon
DECL|member|rsp_queue
r_volatile
id|RspMessage
id|rsp_queue
(braket
id|MAX_MESSAGES
)braket
suffix:semicolon
DECL|member|req_head
r_volatile
r_int
r_char
id|req_head
suffix:semicolon
DECL|member|req_tail
r_volatile
r_int
r_char
id|req_tail
suffix:semicolon
DECL|member|rsp_head
r_volatile
r_int
r_char
id|rsp_head
suffix:semicolon
DECL|member|rsp_tail
r_volatile
r_int
r_char
id|rsp_tail
suffix:semicolon
DECL|member|signature
r_volatile
r_int
r_int
id|signature
suffix:semicolon
DECL|member|trace_enable
r_volatile
r_int
r_int
id|trace_enable
suffix:semicolon
DECL|member|reserved
r_volatile
r_int
r_char
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|DualPortMemory
)brace
id|DualPortMemory
suffix:semicolon
macro_line|#endif
eof
