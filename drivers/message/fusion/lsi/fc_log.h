multiline_comment|/*&n; *  Copyright (c) 2000-2001 LSI Logic Corporation. All rights reserved.&n; *&n; *  NAME:           fc_log.h&n; *  SUMMARY:        MPI IocLogInfo definitions for the SYMFC9xx chips&n; *  DESCRIPTION:    Contains the enumerated list of values that may be returned&n; *                  in the IOCLogInfo field of a MPI Default Reply Message.&n; *&n; *  CREATION DATE:  6/02/2000&n; *  ID:             $Id: fc_log.h,v 4.5 2001/06/07 19:18:00 sschremm Exp $&n; */
multiline_comment|/*&n; * MpiIocLogInfo_t enum&n; *&n; * These 32 bit values are used in the IOCLogInfo field of the MPI reply&n; * messages.&n; * The value is 0xabcccccc where&n; *          a = The type of log info as per the MPI spec. Since these codes are&n; *              all for Fibre Channel this value will always be 2.&n; *          b = Specifies a subclass of the firmware where&n; *                  0 = FCP Initiator&n; *                  1 = FCP Target&n; *                  2 = LAN&n; *                  3 = MPI Message Layer&n; *                  4 = FC Link&n; *                  5 = Context Manager&n; *                  6 = Invalid Field Offset&n; *                  7 = State Change Info&n; *                  all others are reserved for future use&n; *          c = A specific value within the subclass.&n; *&n; * NOTE: Any new values should be added to the end of each subclass so that the&n; *       codes remain consistent across firmware releases.&n; */
DECL|enum|_MpiIocLogInfoFc
r_typedef
r_enum
id|_MpiIocLogInfoFc
(brace
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_BASE
id|MPI_IOCLOGINFO_FC_INIT_BASE
op_assign
l_int|0x20000000
comma
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_ERROR_OUT_OF_ORDER_FRAME
id|MPI_IOCLOGINFO_FC_INIT_ERROR_OUT_OF_ORDER_FRAME
op_assign
l_int|0x20000001
comma
multiline_comment|/* received an out of order frame - unsupported */
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_ERROR_BAD_START_OF_FRAME
id|MPI_IOCLOGINFO_FC_INIT_ERROR_BAD_START_OF_FRAME
op_assign
l_int|0x20000002
comma
multiline_comment|/* Bad Rx Frame, bad start of frame primative */
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_ERROR_BAD_END_OF_FRAME
id|MPI_IOCLOGINFO_FC_INIT_ERROR_BAD_END_OF_FRAME
op_assign
l_int|0x20000003
comma
multiline_comment|/* Bad Rx Frame, bad end of frame primative */
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_ERROR_OVER_RUN
id|MPI_IOCLOGINFO_FC_INIT_ERROR_OVER_RUN
op_assign
l_int|0x20000004
comma
multiline_comment|/* Bad Rx Frame, overrun */
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_ERROR_RX_OTHER
id|MPI_IOCLOGINFO_FC_INIT_ERROR_RX_OTHER
op_assign
l_int|0x20000005
comma
multiline_comment|/* Other errors caught by IOC which require retries */
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_ERROR_SUBPROC_DEAD
id|MPI_IOCLOGINFO_FC_INIT_ERROR_SUBPROC_DEAD
op_assign
l_int|0x20000006
comma
multiline_comment|/* Main processor could not initialize sub-processor */
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_ERROR_RX_OVERRUN
id|MPI_IOCLOGINFO_FC_INIT_ERROR_RX_OVERRUN
op_assign
l_int|0x20000007
comma
multiline_comment|/* Scatter Gather overrun  */
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_ERROR_RX_BAD_STATUS
id|MPI_IOCLOGINFO_FC_INIT_ERROR_RX_BAD_STATUS
op_assign
l_int|0x20000008
comma
multiline_comment|/* Receiver detected context mismatch via invalid header */
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_ERROR_RX_UNEXPECTED_FRAME
id|MPI_IOCLOGINFO_FC_INIT_ERROR_RX_UNEXPECTED_FRAME
op_assign
l_int|0x20000009
comma
multiline_comment|/* CtxMgr detected unsupported frame type  */
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_ERROR_LINK_FAILURE
id|MPI_IOCLOGINFO_FC_INIT_ERROR_LINK_FAILURE
op_assign
l_int|0x2000000A
comma
multiline_comment|/* Link failure occurred  */
DECL|enumerator|MPI_IOCLOGINFO_FC_INIT_ERROR_TX_TIMEOUT
id|MPI_IOCLOGINFO_FC_INIT_ERROR_TX_TIMEOUT
op_assign
l_int|0x2000000B
comma
multiline_comment|/* Transmitter timeout error */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_BASE
id|MPI_IOCLOGINFO_FC_TARGET_BASE
op_assign
l_int|0x21000000
comma
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_NO_PDISC
id|MPI_IOCLOGINFO_FC_TARGET_NO_PDISC
op_assign
l_int|0x21000001
comma
multiline_comment|/* not sent because we are waiting for a PDISC from the initiator */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_NO_LOGIN
id|MPI_IOCLOGINFO_FC_TARGET_NO_LOGIN
op_assign
l_int|0x21000002
comma
multiline_comment|/* not sent because we are not logged in to the remote node */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_DOAR_KILLED_BY_LIP
id|MPI_IOCLOGINFO_FC_TARGET_DOAR_KILLED_BY_LIP
op_assign
l_int|0x21000003
comma
multiline_comment|/* Data Out, Auto Response, not sent due to a LIP */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_DIAR_KILLED_BY_LIP
id|MPI_IOCLOGINFO_FC_TARGET_DIAR_KILLED_BY_LIP
op_assign
l_int|0x21000004
comma
multiline_comment|/* Data In, Auto Response, not sent due to a LIP */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_DIAR_MISSING_DATA
id|MPI_IOCLOGINFO_FC_TARGET_DIAR_MISSING_DATA
op_assign
l_int|0x21000005
comma
multiline_comment|/* Data In, Auto Response, missing data frames */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_DONR_KILLED_BY_LIP
id|MPI_IOCLOGINFO_FC_TARGET_DONR_KILLED_BY_LIP
op_assign
l_int|0x21000006
comma
multiline_comment|/* Data Out, No Response, not sent due to a LIP */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_WRSP_KILLED_BY_LIP
id|MPI_IOCLOGINFO_FC_TARGET_WRSP_KILLED_BY_LIP
op_assign
l_int|0x21000007
comma
multiline_comment|/* Auto-response after a write not sent due to a LIP */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_DINR_KILLED_BY_LIP
id|MPI_IOCLOGINFO_FC_TARGET_DINR_KILLED_BY_LIP
op_assign
l_int|0x21000008
comma
multiline_comment|/* Data In, No Response, not completed due to a LIP */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_DINR_MISSING_DATA
id|MPI_IOCLOGINFO_FC_TARGET_DINR_MISSING_DATA
op_assign
l_int|0x21000009
comma
multiline_comment|/* Data In, No Response, missing data frames */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_MRSP_KILLED_BY_LIP
id|MPI_IOCLOGINFO_FC_TARGET_MRSP_KILLED_BY_LIP
op_assign
l_int|0x2100000a
comma
multiline_comment|/* Manual Response not sent due to a LIP */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_NO_CLASS_3
id|MPI_IOCLOGINFO_FC_TARGET_NO_CLASS_3
op_assign
l_int|0x2100000b
comma
multiline_comment|/* not sent because remote node does not support Class 3 */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_LOGIN_NOT_VALID
id|MPI_IOCLOGINFO_FC_TARGET_LOGIN_NOT_VALID
op_assign
l_int|0x2100000c
comma
multiline_comment|/* not sent because login to remote node not validated */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_FROM_OUTBOUND
id|MPI_IOCLOGINFO_FC_TARGET_FROM_OUTBOUND
op_assign
l_int|0x2100000e
comma
multiline_comment|/* cleared from the outbound after a logout */
DECL|enumerator|MPI_IOCLOGINFO_FC_TARGET_WAITING_FOR_DATA_IN
id|MPI_IOCLOGINFO_FC_TARGET_WAITING_FOR_DATA_IN
op_assign
l_int|0x2100000f
comma
multiline_comment|/* cleared waiting for data after a logout */
DECL|enumerator|MPI_IOCLOGINFO_FC_LAN_BASE
id|MPI_IOCLOGINFO_FC_LAN_BASE
op_assign
l_int|0x22000000
comma
DECL|enumerator|MPI_IOCLOGINFO_FC_LAN_TRANS_SGL_MISSING
id|MPI_IOCLOGINFO_FC_LAN_TRANS_SGL_MISSING
op_assign
l_int|0x22000001
comma
multiline_comment|/* Transaction Context Sgl Missing */
DECL|enumerator|MPI_IOCLOGINFO_FC_LAN_TRANS_WRONG_PLACE
id|MPI_IOCLOGINFO_FC_LAN_TRANS_WRONG_PLACE
op_assign
l_int|0x22000002
comma
multiline_comment|/* Transaction Context found before an EOB */
DECL|enumerator|MPI_IOCLOGINFO_FC_LAN_TRANS_RES_BITS_SET
id|MPI_IOCLOGINFO_FC_LAN_TRANS_RES_BITS_SET
op_assign
l_int|0x22000003
comma
multiline_comment|/* Transaction Context value has reserved bits set */
DECL|enumerator|MPI_IOCLOGINFO_FC_LAN_WRONG_SGL_FLAG
id|MPI_IOCLOGINFO_FC_LAN_WRONG_SGL_FLAG
op_assign
l_int|0x22000004
comma
multiline_comment|/* Invalid SGL Flags */
DECL|enumerator|MPI_IOCLOGINFO_FC_MSG_BASE
id|MPI_IOCLOGINFO_FC_MSG_BASE
op_assign
l_int|0x23000000
comma
DECL|enumerator|MPI_IOCLOGINFO_FC_LINK_BASE
id|MPI_IOCLOGINFO_FC_LINK_BASE
op_assign
l_int|0x24000000
comma
DECL|enumerator|MPI_IOCLOGINFO_FC_LINK_LOOP_INIT_TIMEOUT
id|MPI_IOCLOGINFO_FC_LINK_LOOP_INIT_TIMEOUT
op_assign
l_int|0x24000001
comma
multiline_comment|/* Loop initialization timed out */
DECL|enumerator|MPI_IOCLOGINFO_FC_LINK_ALREADY_INITIALIZED
id|MPI_IOCLOGINFO_FC_LINK_ALREADY_INITIALIZED
op_assign
l_int|0x24000002
comma
multiline_comment|/* Another system controller already initialized the loop */
DECL|enumerator|MPI_IOCLOGINFO_FC_LINK_LINK_NOT_ESTABLISHED
id|MPI_IOCLOGINFO_FC_LINK_LINK_NOT_ESTABLISHED
op_assign
l_int|0x24000003
comma
multiline_comment|/* Not synchronized to signal or still negotiating (possible cable problem) */
DECL|enumerator|MPI_IOCLOGINFO_FC_LINK_CRC_ERROR
id|MPI_IOCLOGINFO_FC_LINK_CRC_ERROR
op_assign
l_int|0x24000004
comma
multiline_comment|/* CRC check detected error on received frame */
DECL|enumerator|MPI_IOCLOGINFO_FC_CTX_BASE
id|MPI_IOCLOGINFO_FC_CTX_BASE
op_assign
l_int|0x25000000
comma
DECL|enumerator|MPI_IOCLOGINFO_FC_INVALID_FIELD_BYTE_OFFSET
id|MPI_IOCLOGINFO_FC_INVALID_FIELD_BYTE_OFFSET
op_assign
l_int|0x26000000
comma
multiline_comment|/* The lower 24 bits give the byte offset of the field in the request message that is invalid */
DECL|enumerator|MPI_IOCLOGINFO_FC_INVALID_FIELD_MAX_OFFSET
id|MPI_IOCLOGINFO_FC_INVALID_FIELD_MAX_OFFSET
op_assign
l_int|0x26ffffff
comma
DECL|enumerator|MPI_IOCLOGINFO_FC_STATE_CHANGE
id|MPI_IOCLOGINFO_FC_STATE_CHANGE
op_assign
l_int|0x27000000
multiline_comment|/* The lower 24 bits give additional information concerning state change */
DECL|typedef|MpiIocLogInfoFc_t
)brace
id|MpiIocLogInfoFc_t
suffix:semicolon
eof
