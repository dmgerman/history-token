multiline_comment|/*&n; *  Copyright (c) 2000-2001 LSI Logic Corporation.&n; *&n; *&n; *           Name:  MPI_TARG.H&n; *          Title:  MPI Target mode messages and structures&n; *  Creation Date:  June 22, 2000&n; *&n; *    MPI Version:  01.01.04&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  05-08-00  00.10.01  Original release for 0.10 spec dated 4/26/2000.&n; *  06-06-00  01.00.01  Update version number for 1.0 release.&n; *  06-22-00  01.00.02  Added _MSG_TARGET_CMD_BUFFER_POST_REPLY structure.&n; *                      Corrected DECSRIPTOR typo to DESCRIPTOR.&n; *  11-02-00  01.01.01  Original release for post 1.0 work&n; *                      Modified target mode to use IoIndex instead of&n; *                      HostIndex and IocIndex. Added Alias.&n; *  01-09-01  01.01.02  Added defines for TARGET_ASSIST_FLAGS_REPOST_CMD_BUFFER&n; *                      and TARGET_STATUS_SEND_FLAGS_REPOST_CMD_BUFFER.&n; *  02-20-01  01.01.03  Started using MPI_POINTER.&n; *                      Added structures for MPI_TARGET_SCSI_SPI_CMD_BUFFER and&n; *                      MPI_TARGET_FCP_CMD_BUFFER.&n; *  03-27-01  01.01.04  Added structure offset comments.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_TARG_H
DECL|macro|MPI_TARG_H
mdefine_line|#define MPI_TARG_H
multiline_comment|/******************************************************************************&n;*&n;*        S C S I    T a r g e t    M e s s a g e s&n;*&n;*******************************************************************************/
DECL|struct|_CMD_BUFFER_DESCRIPTOR
r_typedef
r_struct
id|_CMD_BUFFER_DESCRIPTOR
(brace
DECL|member|IoIndex
id|U16
id|IoIndex
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
multiline_comment|/* 02h */
r_union
multiline_comment|/* 04h */
(brace
DECL|member|PhysicalAddress32
id|U32
id|PhysicalAddress32
suffix:semicolon
DECL|member|PhysicalAddress64
id|U64
id|PhysicalAddress64
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|CMD_BUFFER_DESCRIPTOR
DECL|typedef|PTR_CMD_BUFFER_DESCRIPTOR
)brace
id|CMD_BUFFER_DESCRIPTOR
comma
id|MPI_POINTER
id|PTR_CMD_BUFFER_DESCRIPTOR
comma
DECL|typedef|CmdBufferDescriptor_t
DECL|typedef|pCmdBufferDescriptor_t
id|CmdBufferDescriptor_t
comma
id|MPI_POINTER
id|pCmdBufferDescriptor_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* Target Command Buffer Post Request                                       */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_TARGET_CMD_BUFFER_POST_REQUEST
r_typedef
r_struct
id|_MSG_TARGET_CMD_BUFFER_POST_REQUEST
(brace
DECL|member|BufferPostFlags
id|U8
id|BufferPostFlags
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|BufferCount
id|U8
id|BufferCount
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
DECL|member|BufferLength
id|U8
id|BufferLength
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 05h */
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
DECL|member|Buffer
id|CMD_BUFFER_DESCRIPTOR
id|Buffer
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|MSG_TARGET_CMD_BUFFER_POST_REQUEST
DECL|typedef|PTR_MSG_TARGET_CMD_BUFFER_POST_REQUEST
)brace
id|MSG_TARGET_CMD_BUFFER_POST_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_TARGET_CMD_BUFFER_POST_REQUEST
comma
DECL|typedef|TargetCmdBufferPostRequest_t
DECL|typedef|pTargetCmdBufferPostRequest_t
id|TargetCmdBufferPostRequest_t
comma
id|MPI_POINTER
id|pTargetCmdBufferPostRequest_t
suffix:semicolon
DECL|macro|CMD_BUFFER_POST_FLAGS_PORT_MASK
mdefine_line|#define CMD_BUFFER_POST_FLAGS_PORT_MASK         (0x01)
DECL|macro|CMD_BUFFER_POST_FLAGS_ADDR_MODE_MASK
mdefine_line|#define CMD_BUFFER_POST_FLAGS_ADDR_MODE_MASK    (0x80)
DECL|macro|CMD_BUFFER_POST_FLAGS_ADDR_MODE_32
mdefine_line|#define CMD_BUFFER_POST_FLAGS_ADDR_MODE_32      (0)
DECL|macro|CMD_BUFFER_POST_FLAGS_ADDR_MODE_64
mdefine_line|#define CMD_BUFFER_POST_FLAGS_ADDR_MODE_64      (1)
DECL|macro|CMD_BUFFER_POST_FLAGS_64_BIT_ADDR
mdefine_line|#define CMD_BUFFER_POST_FLAGS_64_BIT_ADDR       (0x80)
DECL|macro|CMD_BUFFER_POST_IO_INDEX_MASK
mdefine_line|#define CMD_BUFFER_POST_IO_INDEX_MASK           (0x00003FFF)
DECL|struct|_MSG_TARGET_CMD_BUFFER_POST_REPLY
r_typedef
r_struct
id|_MSG_TARGET_CMD_BUFFER_POST_REPLY
(brace
DECL|member|BufferPostFlags
id|U8
id|BufferPostFlags
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|BufferCount
id|U8
id|BufferCount
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
DECL|member|BufferLength
id|U8
id|BufferLength
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 05h */
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
id|U16
id|Reserved2
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
DECL|typedef|MSG_TARGET_CMD_BUFFER_POST_REPLY
DECL|typedef|PTR_MSG_TARGET_CMD_BUFFER_POST_REPLY
)brace
id|MSG_TARGET_CMD_BUFFER_POST_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_TARGET_CMD_BUFFER_POST_REPLY
comma
DECL|typedef|TargetCmdBufferPostReply_t
DECL|typedef|pTargetCmdBufferPostReply_t
id|TargetCmdBufferPostReply_t
comma
id|MPI_POINTER
id|pTargetCmdBufferPostReply_t
suffix:semicolon
DECL|struct|_MSG_PRIORITY_CMD_RECEIVED_REPLY
r_typedef
r_struct
id|_MSG_PRIORITY_CMD_RECEIVED_REPLY
(brace
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
multiline_comment|/* 00h */
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved2
id|U8
id|Reserved2
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
DECL|member|PriorityReason
id|U8
id|PriorityReason
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|Reserved3
id|U8
id|Reserved3
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
DECL|member|ReplyWord
id|U32
id|ReplyWord
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_PRIORITY_CMD_RECEIVED_REPLY
DECL|typedef|PTR_MSG_PRIORITY_CMD_RECEIVED_REPLY
)brace
id|MSG_PRIORITY_CMD_RECEIVED_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_PRIORITY_CMD_RECEIVED_REPLY
comma
DECL|typedef|PriorityCommandReceivedReply_t
DECL|typedef|pPriorityCommandReceivedReply_t
id|PriorityCommandReceivedReply_t
comma
id|MPI_POINTER
id|pPriorityCommandReceivedReply_t
suffix:semicolon
DECL|macro|PRIORITY_REASON_NO_DISCONNECT
mdefine_line|#define PRIORITY_REASON_NO_DISCONNECT           (0x00)
DECL|macro|PRIORITY_REASON_SCSI_TASK_MANAGEMENT
mdefine_line|#define PRIORITY_REASON_SCSI_TASK_MANAGEMENT    (0x01)
DECL|macro|PRIORITY_REASON_UNKNOWN
mdefine_line|#define PRIORITY_REASON_UNKNOWN                 (0xFF)
DECL|struct|_MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY
r_typedef
r_struct
id|_MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY
(brace
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
multiline_comment|/* 00h */
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved2
id|U8
id|Reserved2
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
DECL|member|Reserved3
id|U16
id|Reserved3
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
DECL|member|ReplyWord
id|U32
id|ReplyWord
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY
)brace
id|MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY
comma
DECL|typedef|PTR_MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY
id|MPI_POINTER
id|PTR_MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY
comma
DECL|typedef|TargetCmdBufferPostErrorReply_t
DECL|typedef|pTargetCmdBufferPostErrorReply_t
id|TargetCmdBufferPostErrorReply_t
comma
id|MPI_POINTER
id|pTargetCmdBufferPostErrorReply_t
suffix:semicolon
DECL|struct|_MPI_TARGET_FCP_CMD_BUFFER
r_typedef
r_struct
id|_MPI_TARGET_FCP_CMD_BUFFER
(brace
DECL|member|FcpLun
id|U8
id|FcpLun
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|FcpCntl
id|U8
id|FcpCntl
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|FcpCdb
id|U8
id|FcpCdb
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|FcpDl
id|U32
id|FcpDl
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|typedef|MPI_TARGET_FCP_CMD_BUFFER
DECL|typedef|PTR_MPI_TARGET_FCP_CMD_BUFFER
)brace
id|MPI_TARGET_FCP_CMD_BUFFER
comma
id|MPI_POINTER
id|PTR_MPI_TARGET_FCP_CMD_BUFFER
comma
DECL|typedef|MpiTargetFcpCmdBuffer
DECL|typedef|pMpiTargetFcpCmdBuffer
id|MpiTargetFcpCmdBuffer
comma
id|MPI_POINTER
id|pMpiTargetFcpCmdBuffer
suffix:semicolon
DECL|struct|_MPI_TARGET_SCSI_SPI_CMD_BUFFER
r_typedef
r_struct
id|_MPI_TARGET_SCSI_SPI_CMD_BUFFER
(brace
multiline_comment|/* SPI L_Q information unit */
DECL|member|L_QType
id|U8
id|L_QType
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
multiline_comment|/* 01h */
DECL|member|Tag
id|U16
id|Tag
suffix:semicolon
multiline_comment|/* 02h */
DECL|member|LogicalUnitNumber
id|U8
id|LogicalUnitNumber
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|DataLength
id|U32
id|DataLength
suffix:semicolon
multiline_comment|/* 0Ch */
multiline_comment|/* SPI command information unit */
DECL|member|ReservedFirstByteOfCommandIU
id|U8
id|ReservedFirstByteOfCommandIU
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|TaskAttribute
id|U8
id|TaskAttribute
suffix:semicolon
multiline_comment|/* 11h */
DECL|member|TaskManagementFlags
id|U8
id|TaskManagementFlags
suffix:semicolon
multiline_comment|/* 12h */
DECL|member|AdditionalCDBLength
id|U8
id|AdditionalCDBLength
suffix:semicolon
multiline_comment|/* 13h */
DECL|member|CDB
id|U8
id|CDB
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MPI_TARGET_SCSI_SPI_CMD_BUFFER
)brace
id|MPI_TARGET_SCSI_SPI_CMD_BUFFER
comma
DECL|typedef|PTR_MPI_TARGET_SCSI_SPI_CMD_BUFFER
id|MPI_POINTER
id|PTR_MPI_TARGET_SCSI_SPI_CMD_BUFFER
comma
DECL|typedef|MpiTargetScsiSpiCmdBuffer
DECL|typedef|pMpiTargetScsiSpiCmdBuffer
id|MpiTargetScsiSpiCmdBuffer
comma
id|MPI_POINTER
id|pMpiTargetScsiSpiCmdBuffer
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* Target Assist Request                                                    */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_TARGET_ASSIST_REQUEST
r_typedef
r_struct
id|_MSG_TARGET_ASSIST_REQUEST
(brace
DECL|member|StatusCode
id|U8
id|StatusCode
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|TargetAssistFlags
id|U8
id|TargetAssistFlags
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
DECL|member|QueueTag
id|U16
id|QueueTag
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved
id|U8
id|Reserved
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
DECL|member|ReplyWord
id|U32
id|ReplyWord
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|LUN
id|U8
id|LUN
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|RelativeOffset
id|U32
id|RelativeOffset
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|DataLength
id|U32
id|DataLength
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|member|SGL
id|SGE_IO_UNION
id|SGL
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 20h */
DECL|typedef|MSG_TARGET_ASSIST_REQUEST
DECL|typedef|PTR_MSG_TARGET_ASSIST_REQUEST
)brace
id|MSG_TARGET_ASSIST_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_TARGET_ASSIST_REQUEST
comma
DECL|typedef|TargetAssistRequest_t
DECL|typedef|pTargetAssistRequest_t
id|TargetAssistRequest_t
comma
id|MPI_POINTER
id|pTargetAssistRequest_t
suffix:semicolon
DECL|macro|TARGET_ASSIST_FLAGS_DATA_DIRECTION
mdefine_line|#define TARGET_ASSIST_FLAGS_DATA_DIRECTION          (0x01)
DECL|macro|TARGET_ASSIST_FLAGS_AUTO_STATUS
mdefine_line|#define TARGET_ASSIST_FLAGS_AUTO_STATUS             (0x02)
DECL|macro|TARGET_ASSIST_FLAGS_HIGH_PRIORITY
mdefine_line|#define TARGET_ASSIST_FLAGS_HIGH_PRIORITY           (0x04)
DECL|macro|TARGET_ASSIST_FLAGS_REPOST_CMD_BUFFER
mdefine_line|#define TARGET_ASSIST_FLAGS_REPOST_CMD_BUFFER       (0x80)
DECL|struct|_MSG_TARGET_ERROR_REPLY
r_typedef
r_struct
id|_MSG_TARGET_ERROR_REPLY
(brace
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
multiline_comment|/* 00h */
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved2
id|U8
id|Reserved2
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
DECL|member|Reserved3
id|U16
id|Reserved3
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
DECL|member|ReplyWord
id|U32
id|ReplyWord
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|TransferCount
id|U32
id|TransferCount
suffix:semicolon
multiline_comment|/* 18h */
DECL|typedef|MSG_TARGET_ERROR_REPLY
DECL|typedef|PTR_MSG_TARGET_ERROR_REPLY
)brace
id|MSG_TARGET_ERROR_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_TARGET_ERROR_REPLY
comma
DECL|typedef|TargetErrorReply_t
DECL|typedef|pTargetErrorReply_t
id|TargetErrorReply_t
comma
id|MPI_POINTER
id|pTargetErrorReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* Target Status Send Request                                               */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_TARGET_STATUS_SEND_REQUEST
r_typedef
r_struct
id|_MSG_TARGET_STATUS_SEND_REQUEST
(brace
DECL|member|StatusCode
id|U8
id|StatusCode
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|StatusFlags
id|U8
id|StatusFlags
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
DECL|member|QueueTag
id|U16
id|QueueTag
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved
id|U8
id|Reserved
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
DECL|member|ReplyWord
id|U32
id|ReplyWord
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|LUN
id|U8
id|LUN
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|StatusDataSGE
id|SGE_SIMPLE_UNION
id|StatusDataSGE
suffix:semicolon
multiline_comment|/* 18h */
DECL|typedef|MSG_TARGET_STATUS_SEND_REQUEST
DECL|typedef|PTR_MSG_TARGET_STATUS_SEND_REQUEST
)brace
id|MSG_TARGET_STATUS_SEND_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_TARGET_STATUS_SEND_REQUEST
comma
DECL|typedef|TargetStatusSendRequest_t
DECL|typedef|pTargetStatusSendRequest_t
id|TargetStatusSendRequest_t
comma
id|MPI_POINTER
id|pTargetStatusSendRequest_t
suffix:semicolon
DECL|macro|TARGET_STATUS_SEND_FLAGS_AUTO_GOOD_STATUS
mdefine_line|#define TARGET_STATUS_SEND_FLAGS_AUTO_GOOD_STATUS   (0x01)
DECL|macro|TARGET_STATUS_SEND_FLAGS_REPOST_CMD_BUFFER
mdefine_line|#define TARGET_STATUS_SEND_FLAGS_REPOST_CMD_BUFFER  (0x80)
multiline_comment|/****************************************************************************/
multiline_comment|/* Target Mode Abort Request                                                */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_TARGET_MODE_ABORT_REQUEST
r_typedef
r_struct
id|_MSG_TARGET_MODE_ABORT_REQUEST
(brace
DECL|member|AbortType
id|U8
id|AbortType
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved2
id|U8
id|Reserved2
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
DECL|member|ReplyWord
id|U32
id|ReplyWord
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|MsgContextToAbort
id|U32
id|MsgContextToAbort
suffix:semicolon
multiline_comment|/* 10h */
DECL|typedef|MSG_TARGET_MODE_ABORT
DECL|typedef|PTR_MSG_TARGET_MODE_ABORT
)brace
id|MSG_TARGET_MODE_ABORT
comma
id|MPI_POINTER
id|PTR_MSG_TARGET_MODE_ABORT
comma
DECL|typedef|TargetModeAbort_t
DECL|typedef|pTargetModeAbort_t
id|TargetModeAbort_t
comma
id|MPI_POINTER
id|pTargetModeAbort_t
suffix:semicolon
DECL|macro|TARGET_MODE_ABORT_TYPE_ALL_CMD_BUFFERS
mdefine_line|#define TARGET_MODE_ABORT_TYPE_ALL_CMD_BUFFERS      (0x00)
DECL|macro|TARGET_MODE_ABORT_TYPE_ALL_IO
mdefine_line|#define TARGET_MODE_ABORT_TYPE_ALL_IO               (0x01)
DECL|macro|TARGET_MODE_ABORT_TYPE_EXACT_IO
mdefine_line|#define TARGET_MODE_ABORT_TYPE_EXACT_IO             (0x02)
DECL|macro|TARGET_MODE_ABORT_TYPE_EXACT_IO_REQUEST
mdefine_line|#define TARGET_MODE_ABORT_TYPE_EXACT_IO_REQUEST     (0x03)
multiline_comment|/* Target Mode Abort Reply */
DECL|struct|_MSG_TARGET_MODE_ABORT_REPLY
r_typedef
r_struct
id|_MSG_TARGET_MODE_ABORT_REPLY
(brace
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
multiline_comment|/* 00h */
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|Reserved2
id|U8
id|Reserved2
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
DECL|member|Reserved3
id|U16
id|Reserved3
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
DECL|member|AbortCount
id|U32
id|AbortCount
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_TARGET_MODE_ABORT_REPLY
DECL|typedef|PTR_MSG_TARGET_MODE_ABORT_REPLY
)brace
id|MSG_TARGET_MODE_ABORT_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_TARGET_MODE_ABORT_REPLY
comma
DECL|typedef|TargetModeAbortReply_t
DECL|typedef|pTargetModeAbortReply_t
id|TargetModeAbortReply_t
comma
id|MPI_POINTER
id|pTargetModeAbortReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* Target Mode Context Reply                                                */
multiline_comment|/****************************************************************************/
DECL|macro|TARGET_MODE_REPLY_IO_INDEX_MASK
mdefine_line|#define TARGET_MODE_REPLY_IO_INDEX_MASK         (0x00003FFF)
DECL|macro|TARGET_MODE_REPLY_IO_INDEX_SHIFT
mdefine_line|#define TARGET_MODE_REPLY_IO_INDEX_SHIFT        (0)
DECL|macro|TARGET_MODE_REPLY_INITIATOR_INDEX_MASK
mdefine_line|#define TARGET_MODE_REPLY_INITIATOR_INDEX_MASK  (0x03FFC000)
DECL|macro|TARGET_MODE_REPLY_INITIATOR_INDEX_SHIFT
mdefine_line|#define TARGET_MODE_REPLY_INITIATOR_INDEX_SHIFT (14)
DECL|macro|TARGET_MODE_REPLY_ALIAS_MASK
mdefine_line|#define TARGET_MODE_REPLY_ALIAS_MASK            (0x0C000000)
DECL|macro|TARGET_MODE_REPLY_ALIAS_SHIFT
mdefine_line|#define TARGET_MODE_REPLY_ALIAS_SHIFT           (26)
DECL|macro|TARGET_MODE_REPLY_PORT_MASK
mdefine_line|#define TARGET_MODE_REPLY_PORT_MASK             (0x10000000)
DECL|macro|TARGET_MODE_REPLY_PORT_SHIFT
mdefine_line|#define TARGET_MODE_REPLY_PORT_SHIFT            (28)
DECL|macro|GET_IO_INDEX
mdefine_line|#define GET_IO_INDEX(x)     (((x) &amp; TARGET_MODE_REPLY_IO_INDEX_MASK)           &bslash;&n;                                    &gt;&gt; TARGET_MODE_REPLY_IO_INDEX_SHIFT)
DECL|macro|SET_IO_INDEX
mdefine_line|#define SET_IO_INDEX(t, i)                                                     &bslash;&n;            ((t) = ((t) &amp; ~TARGET_MODE_REPLY_IO_INDEX_MASK) |                  &bslash;&n;                              (((i) &lt;&lt; TARGET_MODE_REPLY_IO_INDEX_SHIFT) &amp;     &bslash;&n;                                             TARGET_MODE_REPLY_IO_INDEX_MASK))
DECL|macro|GET_INITIATOR_INDEX
mdefine_line|#define GET_INITIATOR_INDEX(x) (((x) &amp; TARGET_MODE_REPLY_INITIATOR_INDEX_MASK) &bslash;&n;                                   &gt;&gt; TARGET_MODE_REPLY_INITIATOR_INDEX_SHIFT)
DECL|macro|SET_INITIATOR_INDEX
mdefine_line|#define SET_INITIATOR_INDEX(t, ii)                                             &bslash;&n;        ((t) = ((t) &amp; ~TARGET_MODE_REPLY_INITIATOR_INDEX_MASK) |               &bslash;&n;                        (((ii) &lt;&lt; TARGET_MODE_REPLY_INITIATOR_INDEX_SHIFT) &amp;   &bslash;&n;                                      TARGET_MODE_REPLY_INITIATOR_INDEX_MASK))
DECL|macro|GET_ALIAS
mdefine_line|#define GET_ALIAS(x) (((x) &amp; TARGET_MODE_REPLY_ALIAS_MASK)                     &bslash;&n;                                               &gt;&gt; TARGET_MODE_REPLY_ALIAS_SHIFT)
DECL|macro|SET_ALIAS
mdefine_line|#define SET_ALIAS(t, a)  ((t) = ((t) &amp; ~TARGET_MODE_REPLY_ALIAS_MASK) |        &bslash;&n;                                    (((a) &lt;&lt; TARGET_MODE_REPLY_ALIAS_SHIFT) &amp;  &bslash;&n;                                                 TARGET_MODE_REPLY_ALIAS_MASK))
DECL|macro|GET_PORT
mdefine_line|#define GET_PORT(x) (((x) &amp; TARGET_MODE_REPLY_PORT_MASK)                       &bslash;&n;                                               &gt;&gt; TARGET_MODE_REPLY_PORT_SHIFT)
DECL|macro|SET_PORT
mdefine_line|#define SET_PORT(t, p)  ((t) = ((t) &amp; ~TARGET_MODE_REPLY_PORT_MASK) |          &bslash;&n;                                    (((p) &lt;&lt; TARGET_MODE_REPLY_PORT_SHIFT) &amp;   &bslash;&n;                                                  TARGET_MODE_REPLY_PORT_MASK))
macro_line|#endif
eof
