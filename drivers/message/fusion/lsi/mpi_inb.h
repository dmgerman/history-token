multiline_comment|/*&n; *  Copyright (c) 2003 LSI Logic Corporation.&n; *&n; *&n; *           Name:  mpi_inb.h&n; *          Title:  MPI Inband structures and definitions&n; *  Creation Date:  September 30, 2003&n; *&n; *    mpi_inb.h Version:  01.03.xx&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  ??-??-??  01.03.01  Original release.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_INB_H
DECL|macro|MPI_INB_H
mdefine_line|#define MPI_INB_H
multiline_comment|/******************************************************************************&n;*&n;*        I n b a n d    M e s s a g e s&n;*&n;*******************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/* Inband Buffer Post Request                                               */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_INBAND_BUFFER_POST_REQUEST
r_typedef
r_struct
id|_MSG_INBAND_BUFFER_POST_REQUEST
(brace
DECL|member|Reserved1
id|U8
id|Reserved1
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
id|U32
id|Reserved4
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|SGL
id|SGE_TRANS_SIMPLE_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 10h */
DECL|typedef|MSG_INBAND_BUFFER_POST_REQUEST
DECL|typedef|PTR_MSG_INBAND_BUFFER_POST_REQUEST
)brace
id|MSG_INBAND_BUFFER_POST_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_INBAND_BUFFER_POST_REQUEST
comma
DECL|typedef|MpiInbandBufferPostRequest_t
DECL|typedef|pMpiInbandBufferPostRequest_t
id|MpiInbandBufferPostRequest_t
comma
id|MPI_POINTER
id|pMpiInbandBufferPostRequest_t
suffix:semicolon
DECL|struct|_WWN_FC_FORMAT
r_typedef
r_struct
id|_WWN_FC_FORMAT
(brace
DECL|member|NodeName
id|U64
id|NodeName
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|PortName
id|U64
id|PortName
suffix:semicolon
multiline_comment|/* 08h */
DECL|typedef|WWN_FC_FORMAT
DECL|typedef|PTR_WWN_FC_FORMAT
)brace
id|WWN_FC_FORMAT
comma
id|MPI_POINTER
id|PTR_WWN_FC_FORMAT
comma
DECL|typedef|WwnFcFormat_t
DECL|typedef|pWwnFcFormat_t
id|WwnFcFormat_t
comma
id|MPI_POINTER
id|pWwnFcFormat_t
suffix:semicolon
DECL|struct|_WWN_SAS_FORMAT
r_typedef
r_struct
id|_WWN_SAS_FORMAT
(brace
DECL|member|WorldWideID
id|U64
id|WorldWideID
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|Reserved1
id|U32
id|Reserved1
suffix:semicolon
multiline_comment|/* 08h */
DECL|member|Reserved2
id|U32
id|Reserved2
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|WWN_SAS_FORMAT
DECL|typedef|PTR_WWN_SAS_FORMAT
)brace
id|WWN_SAS_FORMAT
comma
id|MPI_POINTER
id|PTR_WWN_SAS_FORMAT
comma
DECL|typedef|WwnSasFormat_t
DECL|typedef|pWwnSasFormat_t
id|WwnSasFormat_t
comma
id|MPI_POINTER
id|pWwnSasFormat_t
suffix:semicolon
DECL|union|_WWN_INBAND_FORMAT
r_typedef
r_union
id|_WWN_INBAND_FORMAT
(brace
DECL|member|Fc
id|WWN_FC_FORMAT
id|Fc
suffix:semicolon
DECL|member|Sas
id|WWN_SAS_FORMAT
id|Sas
suffix:semicolon
DECL|typedef|WWN_INBAND_FORMAT
DECL|typedef|PTR_WWN_INBAND_FORMAT
)brace
id|WWN_INBAND_FORMAT
comma
id|MPI_POINTER
id|PTR_WWN_INBAND_FORMAT
comma
DECL|typedef|WwnInbandFormat
DECL|typedef|pWwnInbandFormat
id|WwnInbandFormat
comma
id|MPI_POINTER
id|pWwnInbandFormat
suffix:semicolon
multiline_comment|/* Inband Buffer Post reply message */
DECL|struct|_MSG_INBAND_BUFFER_POST_REPLY
r_typedef
r_struct
id|_MSG_INBAND_BUFFER_POST_REPLY
(brace
DECL|member|Reserved1
id|U16
id|Reserved1
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
DECL|member|Wwn
id|WWN_INBAND_FORMAT
id|Wwn
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|member|IOCIdentifier
id|U32
id|IOCIdentifier
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 2Ch */
DECL|typedef|MSG_INBAND_BUFFER_POST_REPLY
DECL|typedef|PTR_MSG_INBAND_BUFFER_POST_REPLY
)brace
id|MSG_INBAND_BUFFER_POST_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_INBAND_BUFFER_POST_REPLY
comma
DECL|typedef|MpiInbandBufferPostReply_t
DECL|typedef|pMpiInbandBufferPostReply_t
id|MpiInbandBufferPostReply_t
comma
id|MPI_POINTER
id|pMpiInbandBufferPostReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* Inband Send Request                                                      */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_INBAND_SEND_REQUEST
r_typedef
r_struct
id|_MSG_INBAND_SEND_REQUEST
(brace
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 00h */
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
DECL|member|Reserved4
id|U32
id|Reserved4
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|Wwn
id|WWN_INBAND_FORMAT
id|Wwn
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|Reserved5
id|U32
id|Reserved5
suffix:semicolon
multiline_comment|/* 20h */
DECL|member|SGL
id|SGE_IO_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 24h */
DECL|typedef|MSG_INBAND_SEND_REQUEST
DECL|typedef|PTR_MSG_INBAND_SEND_REQUEST
)brace
id|MSG_INBAND_SEND_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_INBAND_SEND_REQUEST
comma
DECL|typedef|MpiInbandSendRequest_t
DECL|typedef|pMpiInbandSendRequest_t
id|MpiInbandSendRequest_t
comma
id|MPI_POINTER
id|pMpiInbandSendRequest_t
suffix:semicolon
multiline_comment|/* Inband Send reply message */
DECL|struct|_MSG_INBAND_SEND_REPLY
r_typedef
r_struct
id|_MSG_INBAND_SEND_REPLY
(brace
DECL|member|Reserved1
id|U16
id|Reserved1
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
DECL|member|ResponseLength
id|U32
id|ResponseLength
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_INBAND_SEND_REPLY
DECL|typedef|PTR_MSG_INBAND_SEND_REPLY
)brace
id|MSG_INBAND_SEND_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_INBAND_SEND_REPLY
comma
DECL|typedef|MpiInbandSendReply_t
DECL|typedef|pMpiInbandSendReply_t
id|MpiInbandSendReply_t
comma
id|MPI_POINTER
id|pMpiInbandSendReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* Inband Response Request                                                  */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_INBAND_RSP_REQUEST
r_typedef
r_struct
id|_MSG_INBAND_RSP_REQUEST
(brace
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
multiline_comment|/* 00h */
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
DECL|member|Reserved4
id|U32
id|Reserved4
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|Wwn
id|WWN_INBAND_FORMAT
id|Wwn
suffix:semicolon
multiline_comment|/* 10h */
DECL|member|IOCIdentifier
id|U32
id|IOCIdentifier
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 20h */
DECL|member|ResponseLength
id|U32
id|ResponseLength
suffix:semicolon
multiline_comment|/* 30h */
DECL|member|SGL
id|SGE_IO_UNION
id|SGL
suffix:semicolon
multiline_comment|/* 34h */
DECL|typedef|MSG_INBAND_RSP_REQUEST
DECL|typedef|PTR_MSG_INBAND_RSP_REQUEST
)brace
id|MSG_INBAND_RSP_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_INBAND_RSP_REQUEST
comma
DECL|typedef|MpiInbandRspRequest_t
DECL|typedef|pMpiInbandRspRequest_t
id|MpiInbandRspRequest_t
comma
id|MPI_POINTER
id|pMpiInbandRspRequest_t
suffix:semicolon
multiline_comment|/* Inband Response reply message */
DECL|struct|_MSG_INBAND_RSP_REPLY
r_typedef
r_struct
id|_MSG_INBAND_RSP_REPLY
(brace
DECL|member|Reserved1
id|U16
id|Reserved1
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
DECL|typedef|MSG_INBAND_RSP_REPLY
DECL|typedef|PTR_MSG_INBAND_RSP_REPLY
)brace
id|MSG_INBAND_RSP_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_INBAND_RSP_REPLY
comma
DECL|typedef|MpiInbandRspReply_t
DECL|typedef|pMpiInbandRspReply_t
id|MpiInbandRspReply_t
comma
id|MPI_POINTER
id|pMpiInbandRspReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* Inband Abort Request                                                     */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_INBAND_ABORT_REQUEST
r_typedef
r_struct
id|_MSG_INBAND_ABORT_REQUEST
(brace
DECL|member|Reserved1
id|U8
id|Reserved1
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
id|U32
id|Reserved4
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|ContextToAbort
id|U32
id|ContextToAbort
suffix:semicolon
multiline_comment|/* 10h */
DECL|typedef|MSG_INBAND_ABORT_REQUEST
DECL|typedef|PTR_MSG_INBAND_ABORT_REQUEST
)brace
id|MSG_INBAND_ABORT_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_INBAND_ABORT_REQUEST
comma
DECL|typedef|MpiInbandAbortRequest_t
DECL|typedef|pMpiInbandAbortRequest_t
id|MpiInbandAbortRequest_t
comma
id|MPI_POINTER
id|pMpiInbandAbortRequest_t
suffix:semicolon
DECL|macro|MPI_INBAND_ABORT_TYPE_ALL_BUFFERS
mdefine_line|#define MPI_INBAND_ABORT_TYPE_ALL_BUFFERS       (0x00)
DECL|macro|MPI_INBAND_ABORT_TYPE_EXACT_BUFFER
mdefine_line|#define MPI_INBAND_ABORT_TYPE_EXACT_BUFFER      (0x01)
DECL|macro|MPI_INBAND_ABORT_TYPE_SEND_REQUEST
mdefine_line|#define MPI_INBAND_ABORT_TYPE_SEND_REQUEST      (0x02)
DECL|macro|MPI_INBAND_ABORT_TYPE_RESPONSE_REQUEST
mdefine_line|#define MPI_INBAND_ABORT_TYPE_RESPONSE_REQUEST  (0x03)
multiline_comment|/* Inband Abort reply message */
DECL|struct|_MSG_INBAND_ABORT_REPLY
r_typedef
r_struct
id|_MSG_INBAND_ABORT_REPLY
(brace
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
multiline_comment|/* 00h */
DECL|member|AbortType
id|U8
id|AbortType
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
DECL|typedef|MSG_INBAND_ABORT_REPLY
DECL|typedef|PTR_MSG_INBAND_ABORT_REPLY
)brace
id|MSG_INBAND_ABORT_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_INBAND_ABORT_REPLY
comma
DECL|typedef|MpiInbandAbortReply_t
DECL|typedef|pMpiInbandAbortReply_t
id|MpiInbandAbortReply_t
comma
id|MPI_POINTER
id|pMpiInbandAbortReply_t
suffix:semicolon
macro_line|#endif
eof
