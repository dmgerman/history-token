multiline_comment|/*&n; *  Copyright (c) 2003 LSI Logic Corporation.&n; *&n; *&n; *           Name:  mpi_sas.h&n; *          Title:  MPI Serial Attached SCSI structures and definitions&n; *  Creation Date:  April 23, 2003&n; *&n; *    mpi_sas.h Version:  01.05.xx&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  xx-yy-zz  01.05.01  Original release.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_SAS_H
DECL|macro|MPI_SAS_H
mdefine_line|#define MPI_SAS_H
multiline_comment|/*****************************************************************************&n;*&n;*        S e r i a l    A t t a c h e d    S C S I     M e s s a g e s&n;*&n;*****************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/* Serial Management Protocol Passthrough Request                           */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_SMP_PASSTHROUGH_REQUEST
r_typedef
r_struct
id|_MSG_SMP_PASSTHROUGH_REQUEST
(brace
DECL|member|PassthroughFlags
id|U8
id|PassthroughFlags
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|PhysicalPort
id|U8
id|PhysicalPort
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|ChainOffset
id|U8
id|ChainOffset
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Function
id|U8
id|Function
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|RequestDataLength
id|U16
id|RequestDataLength
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|ConnectionRate
id|U8
id|ConnectionRate
suffix:semicolon
multiline_comment|/* 06h */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
multiline_comment|/* 07h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|Reserved1
id|U32
id|Reserved1
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|SASAddress
id|U64
id|SASAddress
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|Reserved2
id|U32
id|Reserved2
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|Reserved3
id|U32
id|Reserved3
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|member|SGL
id|SGE_SIMPLE_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 20h */
DECL|typedef|MSG_SMP_PASSTHROUGH_REQUEST
DECL|typedef|PTR_MSG_SMP_PASSTHROUGH_REQUEST
)brace
id|MSG_SMP_PASSTHROUGH_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_SMP_PASSTHROUGH_REQUEST
comma
DECL|typedef|SmpPassthroughRequest_t
DECL|typedef|pSmpPassthroughRequest_t
id|SmpPassthroughRequest_t
comma
id|MPI_POINTER
id|pSmpPassthroughRequest_t
suffix:semicolon
DECL|macro|MPI_SMP_PT_REQ_PT_FLAGS_IMMEDIATE
mdefine_line|#define MPI_SMP_PT_REQ_PT_FLAGS_IMMEDIATE       (0x80)
DECL|macro|MPI_SMP_PT_REQ_CONNECT_RATE_NEGOTIATED
mdefine_line|#define MPI_SMP_PT_REQ_CONNECT_RATE_NEGOTIATED  (0x00)
DECL|macro|MPI_SMP_PT_REQ_CONNECT_RATE_1_5
mdefine_line|#define MPI_SMP_PT_REQ_CONNECT_RATE_1_5         (0x08)
DECL|macro|MPI_SMP_PT_REQ_CONNECT_RATE_3_0
mdefine_line|#define MPI_SMP_PT_REQ_CONNECT_RATE_3_0         (0x09)
multiline_comment|/* Serial Management Protocol Passthrough Reply */
DECL|struct|_MSG_SMP_PASSTHROUGH_REPLY
r_typedef
r_struct
id|_MSG_SMP_PASSTHROUGH_REPLY
(brace
DECL|member|PassthroughFlags
id|U8
id|PassthroughFlags
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|PhysicalPort
id|U8
id|PhysicalPort
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|MsgLength
id|U8
id|MsgLength
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Function
id|U8
id|Function
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|ResponseDataLength
id|U16
id|ResponseDataLength
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 06h */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
multiline_comment|/* 07h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|Reserved2
id|U8
id|Reserved2
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|SASStatus
id|U8
id|SASStatus
suffix:semicolon
multiline_comment|/* 0Dh */
DECL|member|IOCStatus
id|U16
id|IOCStatus
suffix:semicolon
multiline_comment|/* 0Eh */
DECL|member|IOCLogInfo
id|U32
id|IOCLogInfo
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|Reserved3
id|U32
id|Reserved3
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|ResponseData
id|U8
id|ResponseData
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 18h */
DECL|typedef|MSG_SMP_PASSTHROUGH_REPLY
DECL|typedef|PTR_MSG_SMP_PASSTHROUGH_REPLY
)brace
id|MSG_SMP_PASSTHROUGH_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_SMP_PASSTHROUGH_REPLY
comma
DECL|typedef|SmpPassthroughReply_t
DECL|typedef|pSmpPassthroughReply_t
id|SmpPassthroughReply_t
comma
id|MPI_POINTER
id|pSmpPassthroughReply_t
suffix:semicolon
DECL|macro|MPI_SMP_PT_REPLY_PT_FLAGS_IMMEDIATE
mdefine_line|#define MPI_SMP_PT_REPLY_PT_FLAGS_IMMEDIATE     (0x80)
multiline_comment|/* values for the SASStatus field */
DECL|macro|MPI_SASSTATUS_SUCCESS
mdefine_line|#define MPI_SASSTATUS_SUCCESS                           (0x00)
DECL|macro|MPI_SASSTATUS_UNKNOWN_ERROR
mdefine_line|#define MPI_SASSTATUS_UNKNOWN_ERROR                     (0x01)
DECL|macro|MPI_SASSTATUS_INVALID_FRAME
mdefine_line|#define MPI_SASSTATUS_INVALID_FRAME                     (0x02)
DECL|macro|MPI_SASSTATUS_UTC_BAD_DEST
mdefine_line|#define MPI_SASSTATUS_UTC_BAD_DEST                      (0x03)
DECL|macro|MPI_SASSTATUS_UTC_BREAK_RECEIVED
mdefine_line|#define MPI_SASSTATUS_UTC_BREAK_RECEIVED                (0x04)
DECL|macro|MPI_SASSTATUS_UTC_CONNECT_RATE_NOT_SUPPORTED
mdefine_line|#define MPI_SASSTATUS_UTC_CONNECT_RATE_NOT_SUPPORTED    (0x05)
DECL|macro|MPI_SASSTATUS_UTC_PORT_LAYER_REQUEST
mdefine_line|#define MPI_SASSTATUS_UTC_PORT_LAYER_REQUEST            (0x06)
DECL|macro|MPI_SASSTATUS_UTC_PROTOCOL_NOT_SUPPORTED
mdefine_line|#define MPI_SASSTATUS_UTC_PROTOCOL_NOT_SUPPORTED        (0x07)
DECL|macro|MPI_SASSTATUS_UTC_STP_RESOURCES_BUSY
mdefine_line|#define MPI_SASSTATUS_UTC_STP_RESOURCES_BUSY            (0x08)
DECL|macro|MPI_SASSTATUS_UTC_WRONG_DESTINATION
mdefine_line|#define MPI_SASSTATUS_UTC_WRONG_DESTINATION             (0x09)
DECL|macro|MPI_SASSTATUS_SHORT_INFORMATION_UNIT
mdefine_line|#define MPI_SASSTATUS_SHORT_INFORMATION_UNIT            (0x0A)
DECL|macro|MPI_SASSTATUS_LONG_INFORMATION_UNIT
mdefine_line|#define MPI_SASSTATUS_LONG_INFORMATION_UNIT             (0x0B)
DECL|macro|MPI_SASSTATUS_XFER_RDY_INCORRECT_WRITE_DATA
mdefine_line|#define MPI_SASSTATUS_XFER_RDY_INCORRECT_WRITE_DATA     (0x0C)
DECL|macro|MPI_SASSTATUS_XFER_RDY_REQUEST_OFFSET_ERROR
mdefine_line|#define MPI_SASSTATUS_XFER_RDY_REQUEST_OFFSET_ERROR     (0x0D)
DECL|macro|MPI_SASSTATUS_XFER_RDY_NOT_EXPECTED
mdefine_line|#define MPI_SASSTATUS_XFER_RDY_NOT_EXPECTED             (0x0E)
DECL|macro|MPI_SASSTATUS_DATA_INCORRECT_DATA_LENGTH
mdefine_line|#define MPI_SASSTATUS_DATA_INCORRECT_DATA_LENGTH        (0x0F)
DECL|macro|MPI_SASSTATUS_DATA_TOO_MUCH_READ_DATA
mdefine_line|#define MPI_SASSTATUS_DATA_TOO_MUCH_READ_DATA           (0x10)
DECL|macro|MPI_SASSTATUS_DATA_OFFSET_ERROR
mdefine_line|#define MPI_SASSTATUS_DATA_OFFSET_ERROR                 (0x11)
DECL|macro|MPI_SASSTATUS_SDSF_NAK_RECEIVED
mdefine_line|#define MPI_SASSTATUS_SDSF_NAK_RECEIVED                 (0x12)
DECL|macro|MPI_SASSTATUS_SDSF_CONNECTION_FAILED
mdefine_line|#define MPI_SASSTATUS_SDSF_CONNECTION_FAILED            (0x13)
DECL|macro|MPI_SASSTATUS_INITIATOR_RESPONSE_TIMEOUT
mdefine_line|#define MPI_SASSTATUS_INITIATOR_RESPONSE_TIMEOUT        (0x14)
multiline_comment|/*&n; * Values for the SAS DeviceInfo field used in SAS Device Status Change Event&n; * data and SAS IO Unit Configuration pages.&n; */
DECL|macro|MPI_SAS_DEVICE_INFO_ATAPI_DEVICE
mdefine_line|#define MPI_SAS_DEVICE_INFO_ATAPI_DEVICE        (0x00002000)
DECL|macro|MPI_SAS_DEVICE_INFO_LSI_DEVICE
mdefine_line|#define MPI_SAS_DEVICE_INFO_LSI_DEVICE          (0x00001000)
DECL|macro|MPI_SAS_DEVICE_INFO_DIRECT_ATTACH
mdefine_line|#define MPI_SAS_DEVICE_INFO_DIRECT_ATTACH       (0x00000800)
DECL|macro|MPI_SAS_DEVICE_INFO_SSP_TARGET
mdefine_line|#define MPI_SAS_DEVICE_INFO_SSP_TARGET          (0x00000400)
DECL|macro|MPI_SAS_DEVICE_INFO_STP_TARGET
mdefine_line|#define MPI_SAS_DEVICE_INFO_STP_TARGET          (0x00000200)
DECL|macro|MPI_SAS_DEVICE_INFO_SMP_TARGET
mdefine_line|#define MPI_SAS_DEVICE_INFO_SMP_TARGET          (0x00000100)
DECL|macro|MPI_SAS_DEVICE_INFO_SATA_DEVICE
mdefine_line|#define MPI_SAS_DEVICE_INFO_SATA_DEVICE         (0x00000080)
DECL|macro|MPI_SAS_DEVICE_INFO_SSP_INITIATOR
mdefine_line|#define MPI_SAS_DEVICE_INFO_SSP_INITIATOR       (0x00000040)
DECL|macro|MPI_SAS_DEVICE_INFO_STP_INITIATOR
mdefine_line|#define MPI_SAS_DEVICE_INFO_STP_INITIATOR       (0x00000020)
DECL|macro|MPI_SAS_DEVICE_INFO_SMP_INITIATOR
mdefine_line|#define MPI_SAS_DEVICE_INFO_SMP_INITIATOR       (0x00000010)
DECL|macro|MPI_SAS_DEVICE_INFO_SATA_HOST
mdefine_line|#define MPI_SAS_DEVICE_INFO_SATA_HOST           (0x00000008)
DECL|macro|MPI_SAS_DEVICE_INFO_MASK_DEVICE_TYPE
mdefine_line|#define MPI_SAS_DEVICE_INFO_MASK_DEVICE_TYPE    (0x00000007)
DECL|macro|MPI_SAS_DEVICE_INFO_NO_DEVICE
mdefine_line|#define MPI_SAS_DEVICE_INFO_NO_DEVICE           (0x00000000)
DECL|macro|MPI_SAS_DEVICE_INFO_END_DEVICE
mdefine_line|#define MPI_SAS_DEVICE_INFO_END_DEVICE          (0x00000001)
DECL|macro|MPI_SAS_DEVICE_INFO_EDGE_EXPANDER
mdefine_line|#define MPI_SAS_DEVICE_INFO_EDGE_EXPANDER       (0x00000002)
DECL|macro|MPI_SAS_DEVICE_INFO_FANOUT_EXPANDER
mdefine_line|#define MPI_SAS_DEVICE_INFO_FANOUT_EXPANDER     (0x00000003)
multiline_comment|/****************************************************************************/
multiline_comment|/* SAS IO Unit Control Request                                              */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_SAS_IOUNIT_CONTROL_REQUEST
r_typedef
r_struct
id|_MSG_SAS_IOUNIT_CONTROL_REQUEST
(brace
DECL|member|Operation
id|U8
id|Operation
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|ChainOffset
id|U8
id|ChainOffset
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Function
id|U8
id|Function
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|Reserved2
id|U16
id|Reserved2
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved3
id|U8
id|Reserved3
suffix:semicolon
multiline_comment|/* 06h */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
multiline_comment|/* 07h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|TargetID
id|U8
id|TargetID
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|Bus
id|U8
id|Bus
suffix:semicolon
multiline_comment|/* 0Dh */
DECL|member|PhyNum
id|U8
id|PhyNum
suffix:semicolon
multiline_comment|/* 0Eh */
DECL|member|Reserved4
id|U8
id|Reserved4
suffix:semicolon
multiline_comment|/* 0Fh */
DECL|member|Reserved5
id|U32
id|Reserved5
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|SASAddress
id|U64
id|SASAddress
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|Reserved6
id|U32
id|Reserved6
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|typedef|MSG_SAS_IOUNIT_CONTROL_REQUEST
DECL|typedef|PTR_MSG_SAS_IOUNIT_CONTROL_REQUEST
)brace
id|MSG_SAS_IOUNIT_CONTROL_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_SAS_IOUNIT_CONTROL_REQUEST
comma
DECL|typedef|SasIoUnitControlRequest_t
DECL|typedef|pSasIoUnitControlRequest_t
id|SasIoUnitControlRequest_t
comma
id|MPI_POINTER
id|pSasIoUnitControlRequest_t
suffix:semicolon
multiline_comment|/* values for the ... field */
DECL|macro|MPI_SAS_OP_CLEAR_NOT_PRESENT
mdefine_line|#define MPI_SAS_OP_CLEAR_NOT_PRESENT             (0x01)
DECL|macro|MPI_SAS_OP_CLEAR_ALL
mdefine_line|#define MPI_SAS_OP_CLEAR_ALL                     (0x02)
DECL|macro|MPI_SAS_OP_MAP
mdefine_line|#define MPI_SAS_OP_MAP                           (0x03)
DECL|macro|MPI_SAS_OP_MOVE
mdefine_line|#define MPI_SAS_OP_MOVE                          (0x04)
DECL|macro|MPI_SAS_OP_CLEAR
mdefine_line|#define MPI_SAS_OP_CLEAR                         (0x05)
DECL|macro|MPI_SAS_OP_PHY_LINK_RESET
mdefine_line|#define MPI_SAS_OP_PHY_LINK_RESET                (0x06)
DECL|macro|MPI_SAS_OP_PHY_HARD_RESET
mdefine_line|#define MPI_SAS_OP_PHY_HARD_RESET                (0x07)
DECL|macro|MPI_SAS_OP_PHY_CLEAR_ERROR_LOG
mdefine_line|#define MPI_SAS_OP_PHY_CLEAR_ERROR_LOG           (0x08)
multiline_comment|/* SAS IO Unit Control Reply */
DECL|struct|_MSG_SAS_IOUNIT_CONTROL_REPLY
r_typedef
r_struct
id|_MSG_SAS_IOUNIT_CONTROL_REPLY
(brace
DECL|member|Operation
id|U8
id|Operation
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|MsgLength
id|U8
id|MsgLength
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|Function
id|U8
id|Function
suffix:semicolon
multiline_comment|/* 03h */
DECL|member|Reserved2
id|U16
id|Reserved2
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved3
id|U8
id|Reserved3
suffix:semicolon
multiline_comment|/* 06h */
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
multiline_comment|/* 07h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|Reserved4
id|U16
id|Reserved4
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|IOCStatus
id|U16
id|IOCStatus
suffix:semicolon
multiline_comment|/* 0Eh */
DECL|member|IOCLogInfo
id|U32
id|IOCLogInfo
suffix:semicolon
multiline_comment|/* 10h */
DECL|typedef|MSG_SAS_IOUNIT_CONTROL_REPLY
DECL|typedef|PTR_MSG_SAS_IOUNIT_CONTROL_REPLY
)brace
id|MSG_SAS_IOUNIT_CONTROL_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_SAS_IOUNIT_CONTROL_REPLY
comma
DECL|typedef|SasIoUnitControlReply_t
DECL|typedef|pSasIoUnitControlReply_t
id|SasIoUnitControlReply_t
comma
id|MPI_POINTER
id|pSasIoUnitControlReply_t
suffix:semicolon
macro_line|#endif
eof
