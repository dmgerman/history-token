multiline_comment|/*&n; *  Copyright (c) 2000-2001 LSI Logic Corporation.&n; *&n; *&n; *           Name:  MPI_FC.H&n; *          Title:  MPI Fibre Channel messages and structures&n; *  Creation Date:  June 12, 2000&n; *&n; *    MPI Version:  01.01.05&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  05-08-00  00.10.01  Original release for 0.10 spec dated 4/26/2000.&n; *  06-06-00  01.00.01  Update version number for 1.0 release.&n; *  06-12-00  01.00.02  Added _MSG_FC_ABORT_REPLY structure.&n; *  11-02-00  01.01.01  Original release for post 1.0 work&n; *  12-04-00  01.01.02  Added messages for Common Transport Send and&n; *                      Primitive Send.&n; *  01-09-01  01.01.03  Modifed some of the new flags to have an MPI prefix&n; *                      and modified the FcPrimitiveSend flags.&n; *  01-25-01  01.01.04  Move InitiatorIndex in LinkServiceRsp reply to a larger&n; *                      field.&n; *                      Added FC_ABORT_TYPE_CT_SEND_REQUEST and&n; *                      FC_ABORT_TYPE_EXLINKSEND_REQUEST for FcAbort request.&n; *                      Added MPI_FC_PRIM_SEND_FLAGS_STOP_SEND.&n; *  02-20-01  01.01.05  Started using MPI_POINTER.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_FC_H
DECL|macro|MPI_FC_H
mdefine_line|#define MPI_FC_H
multiline_comment|/*****************************************************************************&n;*&n;*        F C    T a r g e t    M o d e    M e s s a g e s&n;*&n;*****************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/* Link Service Buffer Post messages                                        */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_LINK_SERVICE_BUFFER_POST_REQUEST
r_typedef
r_struct
id|_MSG_LINK_SERVICE_BUFFER_POST_REQUEST
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
DECL|member|Reserved
id|U16
id|Reserved
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
DECL|member|SGL
id|SGE_TRANS_SIMPLE_UNION
id|SGL
suffix:semicolon
DECL|typedef|MSG_LINK_SERVICE_BUFFER_POST_REQUEST
)brace
id|MSG_LINK_SERVICE_BUFFER_POST_REQUEST
comma
DECL|typedef|PTR_MSG_LINK_SERVICE_BUFFER_POST_REQUEST
id|MPI_POINTER
id|PTR_MSG_LINK_SERVICE_BUFFER_POST_REQUEST
comma
DECL|typedef|LinkServiceBufferPostRequest_t
DECL|typedef|pLinkServiceBufferPostRequest_t
id|LinkServiceBufferPostRequest_t
comma
id|MPI_POINTER
id|pLinkServiceBufferPostRequest_t
suffix:semicolon
DECL|macro|LINK_SERVICE_BUFFER_POST_FLAGS_PORT_MASK
mdefine_line|#define LINK_SERVICE_BUFFER_POST_FLAGS_PORT_MASK (0x01)
DECL|struct|_WWNFORMAT
r_typedef
r_struct
id|_WWNFORMAT
(brace
DECL|member|PortNameHigh
id|U32
id|PortNameHigh
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|PortNameLow
id|U32
id|PortNameLow
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|NodeNameHigh
id|U32
id|NodeNameHigh
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|NodeNameLow
id|U32
id|NodeNameLow
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|WWNFORMAT
)brace
id|WWNFORMAT
comma
DECL|typedef|WwnFormat_t
id|WwnFormat_t
suffix:semicolon
multiline_comment|/* Link Service Buffer Post Reply */
DECL|struct|_MSG_LINK_SERVICE_BUFFER_POST_REPLY
r_typedef
r_struct
id|_MSG_LINK_SERVICE_BUFFER_POST_REPLY
(brace
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
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
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|PortNumber
id|U8
id|PortNumber
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
DECL|member|TransferLength
id|U32
id|TransferLength
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|TransactionContext
id|U32
id|TransactionContext
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|Rctl_Did
id|U32
id|Rctl_Did
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|member|Csctl_Sid
id|U32
id|Csctl_Sid
suffix:semicolon
multiline_comment|/* 20h */
DECL|member|Type_Fctl
id|U32
id|Type_Fctl
suffix:semicolon
multiline_comment|/* 24h */
DECL|member|SeqCnt
id|U16
id|SeqCnt
suffix:semicolon
multiline_comment|/* 28h */
DECL|member|Dfctl
id|U8
id|Dfctl
suffix:semicolon
multiline_comment|/* 2Ah */
DECL|member|SeqId
id|U8
id|SeqId
suffix:semicolon
multiline_comment|/* 2Bh */
DECL|member|Rxid
id|U16
id|Rxid
suffix:semicolon
multiline_comment|/* 2Ch */
DECL|member|Oxid
id|U16
id|Oxid
suffix:semicolon
multiline_comment|/* 2Eh */
DECL|member|Parameter
id|U32
id|Parameter
suffix:semicolon
multiline_comment|/* 30h */
DECL|member|Wwn
id|WWNFORMAT
id|Wwn
suffix:semicolon
multiline_comment|/* 34h */
DECL|typedef|MSG_LINK_SERVICE_BUFFER_POST_REPLY
DECL|typedef|PTR_MSG_LINK_SERVICE_BUFFER_POST_REPLY
)brace
id|MSG_LINK_SERVICE_BUFFER_POST_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_LINK_SERVICE_BUFFER_POST_REPLY
comma
DECL|typedef|LinkServiceBufferPostReply_t
DECL|typedef|pLinkServiceBufferPostReply_t
id|LinkServiceBufferPostReply_t
comma
id|MPI_POINTER
id|pLinkServiceBufferPostReply_t
suffix:semicolon
DECL|macro|MPI_LS_BUF_POST_REPLY_FLAG_NO_RSP_NEEDED
mdefine_line|#define MPI_LS_BUF_POST_REPLY_FLAG_NO_RSP_NEEDED    (0x80)
DECL|macro|MPI_FC_DID_MASK
mdefine_line|#define MPI_FC_DID_MASK                             (0x00FFFFFF)
DECL|macro|MPI_FC_DID_SHIFT
mdefine_line|#define MPI_FC_DID_SHIFT                            (0)
DECL|macro|MPI_FC_RCTL_MASK
mdefine_line|#define MPI_FC_RCTL_MASK                            (0xFF000000)
DECL|macro|MPI_FC_RCTL_SHIFT
mdefine_line|#define MPI_FC_RCTL_SHIFT                           (24)
DECL|macro|MPI_FC_SID_MASK
mdefine_line|#define MPI_FC_SID_MASK                             (0x00FFFFFF)
DECL|macro|MPI_FC_SID_SHIFT
mdefine_line|#define MPI_FC_SID_SHIFT                            (0)
DECL|macro|MPI_FC_CSCTL_MASK
mdefine_line|#define MPI_FC_CSCTL_MASK                           (0xFF000000)
DECL|macro|MPI_FC_CSCTL_SHIFT
mdefine_line|#define MPI_FC_CSCTL_SHIFT                          (24)
DECL|macro|MPI_FC_FCTL_MASK
mdefine_line|#define MPI_FC_FCTL_MASK                            (0x00FFFFFF)
DECL|macro|MPI_FC_FCTL_SHIFT
mdefine_line|#define MPI_FC_FCTL_SHIFT                           (0)
DECL|macro|MPI_FC_TYPE_MASK
mdefine_line|#define MPI_FC_TYPE_MASK                            (0xFF000000)
DECL|macro|MPI_FC_TYPE_SHIFT
mdefine_line|#define MPI_FC_TYPE_SHIFT                           (24)
multiline_comment|/* obsolete name for the above */
DECL|macro|FCP_TARGET_DID_MASK
mdefine_line|#define FCP_TARGET_DID_MASK                         (0x00FFFFFF)
DECL|macro|FCP_TARGET_DID_SHIFT
mdefine_line|#define FCP_TARGET_DID_SHIFT                        (0)
DECL|macro|FCP_TARGET_RCTL_MASK
mdefine_line|#define FCP_TARGET_RCTL_MASK                        (0xFF000000)
DECL|macro|FCP_TARGET_RCTL_SHIFT
mdefine_line|#define FCP_TARGET_RCTL_SHIFT                       (24)
DECL|macro|FCP_TARGET_SID_MASK
mdefine_line|#define FCP_TARGET_SID_MASK                         (0x00FFFFFF)
DECL|macro|FCP_TARGET_SID_SHIFT
mdefine_line|#define FCP_TARGET_SID_SHIFT                        (0)
DECL|macro|FCP_TARGET_CSCTL_MASK
mdefine_line|#define FCP_TARGET_CSCTL_MASK                       (0xFF000000)
DECL|macro|FCP_TARGET_CSCTL_SHIFT
mdefine_line|#define FCP_TARGET_CSCTL_SHIFT                      (24)
DECL|macro|FCP_TARGET_FCTL_MASK
mdefine_line|#define FCP_TARGET_FCTL_MASK                        (0x00FFFFFF)
DECL|macro|FCP_TARGET_FCTL_SHIFT
mdefine_line|#define FCP_TARGET_FCTL_SHIFT                       (0)
DECL|macro|FCP_TARGET_TYPE_MASK
mdefine_line|#define FCP_TARGET_TYPE_MASK                        (0xFF000000)
DECL|macro|FCP_TARGET_TYPE_SHIFT
mdefine_line|#define FCP_TARGET_TYPE_SHIFT                       (24)
multiline_comment|/****************************************************************************/
multiline_comment|/* Link Service Response messages                                           */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_LINK_SERVICE_RSP_REQUEST
r_typedef
r_struct
id|_MSG_LINK_SERVICE_RSP_REQUEST
(brace
DECL|member|RspFlags
id|U8
id|RspFlags
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
DECL|member|Rctl_Did
id|U32
id|Rctl_Did
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|Csctl_Sid
id|U32
id|Csctl_Sid
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|Type_Fctl
id|U32
id|Type_Fctl
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|SeqCnt
id|U16
id|SeqCnt
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|Dfctl
id|U8
id|Dfctl
suffix:semicolon
multiline_comment|/* 1Ah */
DECL|member|SeqId
id|U8
id|SeqId
suffix:semicolon
multiline_comment|/* 1Bh */
DECL|member|Rxid
id|U16
id|Rxid
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|member|Oxid
id|U16
id|Oxid
suffix:semicolon
multiline_comment|/* 1Eh */
DECL|member|Parameter
id|U32
id|Parameter
suffix:semicolon
multiline_comment|/* 20h */
DECL|member|SGL
id|SGE_SIMPLE_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 24h */
DECL|typedef|MSG_LINK_SERVICE_RSP_REQUEST
DECL|typedef|PTR_MSG_LINK_SERVICE_RSP_REQUEST
)brace
id|MSG_LINK_SERVICE_RSP_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_LINK_SERVICE_RSP_REQUEST
comma
DECL|typedef|LinkServiceRspRequest_t
DECL|typedef|pLinkServiceRspRequest_t
id|LinkServiceRspRequest_t
comma
id|MPI_POINTER
id|pLinkServiceRspRequest_t
suffix:semicolon
DECL|macro|LINK_SERVICE_RSP_FLAGS_IMMEDIATE
mdefine_line|#define LINK_SERVICE_RSP_FLAGS_IMMEDIATE        (0x80)
DECL|macro|LINK_SERVICE_RSP_FLAGS_PORT_MASK
mdefine_line|#define LINK_SERVICE_RSP_FLAGS_PORT_MASK        (0x01)
multiline_comment|/* Link Service Response Reply  */
DECL|struct|_MSG_LINK_SERVICE_RSP_REPLY
r_typedef
r_struct
id|_MSG_LINK_SERVICE_RSP_REPLY
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
DECL|member|InitiatorIndex
id|U32
id|InitiatorIndex
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_LINK_SERVICE_RSP_REPLY
DECL|typedef|PTR_MSG_LINK_SERVICE_RSP_REPLY
)brace
id|MSG_LINK_SERVICE_RSP_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_LINK_SERVICE_RSP_REPLY
comma
DECL|typedef|LinkServiceRspReply_t
DECL|typedef|pLinkServiceRspReply_t
id|LinkServiceRspReply_t
comma
id|MPI_POINTER
id|pLinkServiceRspReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* Extended Link Service Send messages                                      */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_EXLINK_SERVICE_SEND_REQUEST
r_typedef
r_struct
id|_MSG_EXLINK_SERVICE_SEND_REQUEST
(brace
DECL|member|SendFlags
id|U8
id|SendFlags
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
DECL|member|MsgFlags_Did
id|U32
id|MsgFlags_Did
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|ElsCommandCode
id|U32
id|ElsCommandCode
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|SGL
id|SGE_SIMPLE_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 10h */
DECL|typedef|MSG_EXLINK_SERVICE_SEND_REQUEST
DECL|typedef|PTR_MSG_EXLINK_SERVICE_SEND_REQUEST
)brace
id|MSG_EXLINK_SERVICE_SEND_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_EXLINK_SERVICE_SEND_REQUEST
comma
DECL|typedef|ExLinkServiceSendRequest_t
DECL|typedef|pExLinkServiceSendRequest_t
id|ExLinkServiceSendRequest_t
comma
id|MPI_POINTER
id|pExLinkServiceSendRequest_t
suffix:semicolon
DECL|macro|EX_LINK_SERVICE_SEND_DID_MASK
mdefine_line|#define EX_LINK_SERVICE_SEND_DID_MASK           (0x00FFFFFF)
DECL|macro|EX_LINK_SERVICE_SEND_DID_SHIFT
mdefine_line|#define EX_LINK_SERVICE_SEND_DID_SHIFT          (0)
DECL|macro|EX_LINK_SERVICE_SEND_MSGFLAGS_MASK
mdefine_line|#define EX_LINK_SERVICE_SEND_MSGFLAGS_MASK      (0xFF000000)
DECL|macro|EX_LINK_SERVICE_SEND_MSGFLAGS_SHIFT
mdefine_line|#define EX_LINK_SERVICE_SEND_MSGFLAGS_SHIFT     (24)
multiline_comment|/* Extended Link Service Send Reply */
DECL|struct|_MSG_EXLINK_SERVICE_SEND_REPLY
r_typedef
r_struct
id|_MSG_EXLINK_SERVICE_SEND_REPLY
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
DECL|member|ResponseLength
id|U32
id|ResponseLength
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_EXLINK_SERVICE_SEND_REPLY
DECL|typedef|PTR_MSG_EXLINK_SERVICE_SEND_REPLY
)brace
id|MSG_EXLINK_SERVICE_SEND_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_EXLINK_SERVICE_SEND_REPLY
comma
DECL|typedef|ExLinkServiceSendReply_t
DECL|typedef|pExLinkServiceSendReply_t
id|ExLinkServiceSendReply_t
comma
id|MPI_POINTER
id|pExLinkServiceSendReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* FC Abort messages                                                        */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_FC_ABORT_REQUEST
r_typedef
r_struct
id|_MSG_FC_ABORT_REQUEST
(brace
DECL|member|AbortFlags
id|U8
id|AbortFlags
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|AbortType
id|U8
id|AbortType
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
DECL|member|TransactionContextToAbort
id|U32
id|TransactionContextToAbort
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|MSG_FC_ABORT_REQUEST
DECL|typedef|PTR_MSG_FC_ABORT_REQUEST
)brace
id|MSG_FC_ABORT_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_FC_ABORT_REQUEST
comma
DECL|typedef|FcAbortRequest_t
DECL|typedef|pFcAbortRequest_t
id|FcAbortRequest_t
comma
id|MPI_POINTER
id|pFcAbortRequest_t
suffix:semicolon
DECL|macro|FC_ABORT_FLAG_PORT_MASK
mdefine_line|#define FC_ABORT_FLAG_PORT_MASK                 (0x01)
DECL|macro|FC_ABORT_TYPE_ALL_FC_BUFFERS
mdefine_line|#define FC_ABORT_TYPE_ALL_FC_BUFFERS            (0x00)
DECL|macro|FC_ABORT_TYPE_EXACT_FC_BUFFER
mdefine_line|#define FC_ABORT_TYPE_EXACT_FC_BUFFER           (0x01)
DECL|macro|FC_ABORT_TYPE_CT_SEND_REQUEST
mdefine_line|#define FC_ABORT_TYPE_CT_SEND_REQUEST           (0x02)
DECL|macro|FC_ABORT_TYPE_EXLINKSEND_REQUEST
mdefine_line|#define FC_ABORT_TYPE_EXLINKSEND_REQUEST        (0x03)
multiline_comment|/* FC Abort Reply */
DECL|struct|_MSG_FC_ABORT_REPLY
r_typedef
r_struct
id|_MSG_FC_ABORT_REPLY
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
DECL|typedef|MSG_FC_ABORT_REPLY
DECL|typedef|PTR_MSG_FC_ABORT_REPLY
)brace
id|MSG_FC_ABORT_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_FC_ABORT_REPLY
comma
DECL|typedef|FcAbortReply_t
DECL|typedef|pFcAbortReply_t
id|FcAbortReply_t
comma
id|MPI_POINTER
id|pFcAbortReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* FC Common Transport Send messages                                        */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_FC_COMMON_TRANSPORT_SEND_REQUEST
r_typedef
r_struct
id|_MSG_FC_COMMON_TRANSPORT_SEND_REQUEST
(brace
DECL|member|SendFlags
id|U8
id|SendFlags
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
DECL|member|MsgFlags_Did
id|U32
id|MsgFlags_Did
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|CTCommandCode
id|U16
id|CTCommandCode
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|FsType
id|U8
id|FsType
suffix:semicolon
multiline_comment|/* 0Eh */
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 0Fh */
DECL|member|SGL
id|SGE_SIMPLE_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 10h */
DECL|typedef|MSG_FC_COMMON_TRANSPORT_SEND_REQUEST
)brace
id|MSG_FC_COMMON_TRANSPORT_SEND_REQUEST
comma
DECL|typedef|PTR_MSG_FC_COMMON_TRANSPORT_SEND_REQUEST
id|MPI_POINTER
id|PTR_MSG_FC_COMMON_TRANSPORT_SEND_REQUEST
comma
DECL|typedef|FcCommonTransportSendRequest_t
DECL|typedef|pFcCommonTransportSendRequest_t
id|FcCommonTransportSendRequest_t
comma
id|MPI_POINTER
id|pFcCommonTransportSendRequest_t
suffix:semicolon
DECL|macro|MPI_FC_CT_SEND_DID_MASK
mdefine_line|#define MPI_FC_CT_SEND_DID_MASK                 (0x00FFFFFF)
DECL|macro|MPI_FC_CT_SEND_DID_SHIFT
mdefine_line|#define MPI_FC_CT_SEND_DID_SHIFT                (0)
DECL|macro|MPI_FC_CT_SEND_MSGFLAGS_MASK
mdefine_line|#define MPI_FC_CT_SEND_MSGFLAGS_MASK            (0xFF000000)
DECL|macro|MPI_FC_CT_SEND_MSGFLAGS_SHIFT
mdefine_line|#define MPI_FC_CT_SEND_MSGFLAGS_SHIFT           (24)
multiline_comment|/* FC Common Transport Send Reply */
DECL|struct|_MSG_FC_COMMON_TRANSPORT_SEND_REPLY
r_typedef
r_struct
id|_MSG_FC_COMMON_TRANSPORT_SEND_REPLY
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
DECL|member|ResponseLength
id|U32
id|ResponseLength
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_FC_COMMON_TRANSPORT_SEND_REPLY
DECL|typedef|PTR_MSG_FC_COMMON_TRANSPORT_SEND_REPLY
)brace
id|MSG_FC_COMMON_TRANSPORT_SEND_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_FC_COMMON_TRANSPORT_SEND_REPLY
comma
DECL|typedef|FcCommonTransportSendReply_t
DECL|typedef|pFcCommonTransportSendReply_t
id|FcCommonTransportSendReply_t
comma
id|MPI_POINTER
id|pFcCommonTransportSendReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* FC Primitive Send messages                                               */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_FC_PRIMITIVE_SEND_REQUEST
r_typedef
r_struct
id|_MSG_FC_PRIMITIVE_SEND_REQUEST
(brace
DECL|member|SendFlags
id|U8
id|SendFlags
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
DECL|member|FcPrimitive
id|U8
id|FcPrimitive
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|MSG_FC_PRIMITIVE_SEND_REQUEST
DECL|typedef|PTR_MSG_FC_PRIMITIVE_SEND_REQUEST
)brace
id|MSG_FC_PRIMITIVE_SEND_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_FC_PRIMITIVE_SEND_REQUEST
comma
DECL|typedef|FcPrimitiveSendRequest_t
DECL|typedef|pFcPrimitiveSendRequest_t
id|FcPrimitiveSendRequest_t
comma
id|MPI_POINTER
id|pFcPrimitiveSendRequest_t
suffix:semicolon
DECL|macro|MPI_FC_PRIM_SEND_FLAGS_PORT_MASK
mdefine_line|#define MPI_FC_PRIM_SEND_FLAGS_PORT_MASK       (0x01)
DECL|macro|MPI_FC_PRIM_SEND_FLAGS_STOP_SEND
mdefine_line|#define MPI_FC_PRIM_SEND_FLAGS_STOP_SEND       (0x08)
DECL|macro|MPI_FC_PRIM_SEND_FLAGS_SEND_ONCE
mdefine_line|#define MPI_FC_PRIM_SEND_FLAGS_SEND_ONCE       (0x10)
DECL|macro|MPI_FC_PRIM_SEND_FLAGS_SEND_AROUND
mdefine_line|#define MPI_FC_PRIM_SEND_FLAGS_SEND_AROUND     (0x20)
DECL|macro|MPI_FC_PRIM_SEND_FLAGS_UNTIL_FULL
mdefine_line|#define MPI_FC_PRIM_SEND_FLAGS_UNTIL_FULL      (0x40)
DECL|macro|MPI_FC_PRIM_SEND_FLAGS_FOREVER
mdefine_line|#define MPI_FC_PRIM_SEND_FLAGS_FOREVER         (0x80)
multiline_comment|/* FC Primitive Send Reply */
DECL|struct|_MSG_FC_PRIMITIVE_SEND_REPLY
r_typedef
r_struct
id|_MSG_FC_PRIMITIVE_SEND_REPLY
(brace
DECL|member|SendFlags
id|U8
id|SendFlags
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved
id|U8
id|Reserved
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
DECL|typedef|MSG_FC_PRIMITIVE_SEND_REPLY
DECL|typedef|PTR_MSG_FC_PRIMITIVE_SEND_REPLY
)brace
id|MSG_FC_PRIMITIVE_SEND_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_FC_PRIMITIVE_SEND_REPLY
comma
DECL|typedef|FcPrimitiveSendReply_t
DECL|typedef|pFcPrimitiveSendReply_t
id|FcPrimitiveSendReply_t
comma
id|MPI_POINTER
id|pFcPrimitiveSendReply_t
suffix:semicolon
macro_line|#endif
eof
