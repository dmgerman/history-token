multiline_comment|/*&n; *  Copyright (c) 2000-2001 LSI Logic Corporation.&n; *&n; *&n; *           Name:  MPI_LAN.H&n; *          Title:  MPI LAN messages and structures&n; *  Creation Date:  June 30, 2000&n; *&n; *    MPI Version:  01.02.01&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  05-08-00  00.10.01  Original release for 0.10 spec dated 4/26/2000.&n; *  05-24-00  00.10.02  Added LANStatus field to _MSG_LAN_SEND_REPLY.&n; *                      Added LANStatus field to _MSG_LAN_RECEIVE_POST_REPLY.&n; *                      Moved ListCount field in _MSG_LAN_RECEIVE_POST_REPLY.&n; *  06-06-00  01.00.01  Update version number for 1.0 release.&n; *  06-12-00  01.00.02  Added MPI_ to BUCKETSTATUS_ definitions.&n; *  06-22-00  01.00.03  Major changes to match new LAN definition in 1.0 spec.&n; *  06-30-00  01.00.04  Added Context Reply definitions per revised proposal.&n; *                      Changed transaction context usage to bucket/buffer.&n; *  07-05-00  01.00.05  Removed LAN_RECEIVE_POST_BUCKET_CONTEXT_MASK definition&n; *                      to lan private header file&n; *  11-02-00  01.01.01  Original release for post 1.0 work&n; *  02-20-01  01.01.02  Started using MPI_POINTER.&n; *  03-27-01  01.01.03  Added structure offset comments.&n; *  08-08-01  01.02.01  Original release for v1.2 work.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_LAN_H
DECL|macro|MPI_LAN_H
mdefine_line|#define MPI_LAN_H
multiline_comment|/******************************************************************************&n;*&n;*               L A N    M e s s a g e s&n;*&n;*******************************************************************************/
multiline_comment|/* LANSend messages */
DECL|struct|_MSG_LAN_SEND_REQUEST
r_typedef
r_struct
id|_MSG_LAN_SEND_REQUEST
(brace
DECL|member|Reserved
id|U16
id|Reserved
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
DECL|member|SG_List
id|SGE_MPI_UNION
id|SG_List
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|typedef|MSG_LAN_SEND_REQUEST
DECL|typedef|PTR_MSG_LAN_SEND_REQUEST
)brace
id|MSG_LAN_SEND_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_LAN_SEND_REQUEST
comma
DECL|typedef|LANSendRequest_t
DECL|typedef|pLANSendRequest_t
id|LANSendRequest_t
comma
id|MPI_POINTER
id|pLANSendRequest_t
suffix:semicolon
DECL|struct|_MSG_LAN_SEND_REPLY
r_typedef
r_struct
id|_MSG_LAN_SEND_REPLY
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
DECL|member|Reserved2
id|U8
id|Reserved2
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|NumberOfContexts
id|U8
id|NumberOfContexts
suffix:semicolon
multiline_comment|/* 05h */
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
DECL|member|BufferContext
id|U32
id|BufferContext
suffix:semicolon
multiline_comment|/* 14h */
DECL|typedef|MSG_LAN_SEND_REPLY
DECL|typedef|PTR_MSG_LAN_SEND_REPLY
)brace
id|MSG_LAN_SEND_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_LAN_SEND_REPLY
comma
DECL|typedef|LANSendReply_t
DECL|typedef|pLANSendReply_t
id|LANSendReply_t
comma
id|MPI_POINTER
id|pLANSendReply_t
suffix:semicolon
multiline_comment|/* LANReceivePost */
DECL|struct|_MSG_LAN_RECEIVE_POST_REQUEST
r_typedef
r_struct
id|_MSG_LAN_RECEIVE_POST_REQUEST
(brace
DECL|member|Reserved
id|U16
id|Reserved
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
DECL|member|BucketCount
id|U32
id|BucketCount
suffix:semicolon
multiline_comment|/* 0Ch */
DECL|member|SG_List
id|SGE_MPI_UNION
id|SG_List
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 10h */
DECL|typedef|MSG_LAN_RECEIVE_POST_REQUEST
DECL|typedef|PTR_MSG_LAN_RECEIVE_POST_REQUEST
)brace
id|MSG_LAN_RECEIVE_POST_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_LAN_RECEIVE_POST_REQUEST
comma
DECL|typedef|LANReceivePostRequest_t
DECL|typedef|pLANReceivePostRequest_t
id|LANReceivePostRequest_t
comma
id|MPI_POINTER
id|pLANReceivePostRequest_t
suffix:semicolon
DECL|struct|_MSG_LAN_RECEIVE_POST_REPLY
r_typedef
r_struct
id|_MSG_LAN_RECEIVE_POST_REPLY
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
DECL|member|Reserved2
id|U8
id|Reserved2
suffix:semicolon
multiline_comment|/* 04h */
DECL|member|NumberOfContexts
id|U8
id|NumberOfContexts
suffix:semicolon
multiline_comment|/* 05h */
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
DECL|member|BucketsRemaining
id|U32
id|BucketsRemaining
suffix:semicolon
multiline_comment|/* 14h */
DECL|member|PacketOffset
id|U32
id|PacketOffset
suffix:semicolon
multiline_comment|/* 18h */
DECL|member|PacketLength
id|U32
id|PacketLength
suffix:semicolon
multiline_comment|/* 1Ch */
DECL|member|BucketContext
id|U32
id|BucketContext
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 20h */
DECL|typedef|MSG_LAN_RECEIVE_POST_REPLY
DECL|typedef|PTR_MSG_LAN_RECEIVE_POST_REPLY
)brace
id|MSG_LAN_RECEIVE_POST_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_LAN_RECEIVE_POST_REPLY
comma
DECL|typedef|LANReceivePostReply_t
DECL|typedef|pLANReceivePostReply_t
id|LANReceivePostReply_t
comma
id|MPI_POINTER
id|pLANReceivePostReply_t
suffix:semicolon
multiline_comment|/* LANReset */
DECL|struct|_MSG_LAN_RESET_REQUEST
r_typedef
r_struct
id|_MSG_LAN_RESET_REQUEST
(brace
DECL|member|Reserved
id|U16
id|Reserved
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
DECL|member|PortNumber
id|U8
id|PortNumber
suffix:semicolon
multiline_comment|/* 05h */
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
DECL|typedef|MSG_LAN_RESET_REQUEST
DECL|typedef|PTR_MSG_LAN_RESET_REQUEST
)brace
id|MSG_LAN_RESET_REQUEST
comma
id|MPI_POINTER
id|PTR_MSG_LAN_RESET_REQUEST
comma
DECL|typedef|LANResetRequest_t
DECL|typedef|pLANResetRequest_t
id|LANResetRequest_t
comma
id|MPI_POINTER
id|pLANResetRequest_t
suffix:semicolon
DECL|struct|_MSG_LAN_RESET_REPLY
r_typedef
r_struct
id|_MSG_LAN_RESET_REPLY
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
DECL|member|Reserved2
id|U16
id|Reserved2
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
DECL|typedef|MSG_LAN_RESET_REPLY
DECL|typedef|PTR_MSG_LAN_RESET_REPLY
)brace
id|MSG_LAN_RESET_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_LAN_RESET_REPLY
comma
DECL|typedef|LANResetReply_t
DECL|typedef|pLANResetReply_t
id|LANResetReply_t
comma
id|MPI_POINTER
id|pLANResetReply_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/* LAN Context Reply defines and macros                                     */
multiline_comment|/****************************************************************************/
DECL|macro|LAN_REPLY_PACKET_LENGTH_MASK
mdefine_line|#define LAN_REPLY_PACKET_LENGTH_MASK            (0x0000FFFF)
DECL|macro|LAN_REPLY_PACKET_LENGTH_SHIFT
mdefine_line|#define LAN_REPLY_PACKET_LENGTH_SHIFT           (0)
DECL|macro|LAN_REPLY_BUCKET_CONTEXT_MASK
mdefine_line|#define LAN_REPLY_BUCKET_CONTEXT_MASK           (0x07FF0000)
DECL|macro|LAN_REPLY_BUCKET_CONTEXT_SHIFT
mdefine_line|#define LAN_REPLY_BUCKET_CONTEXT_SHIFT          (16)
DECL|macro|LAN_REPLY_BUFFER_CONTEXT_MASK
mdefine_line|#define LAN_REPLY_BUFFER_CONTEXT_MASK           (0x07FFFFFF)
DECL|macro|LAN_REPLY_BUFFER_CONTEXT_SHIFT
mdefine_line|#define LAN_REPLY_BUFFER_CONTEXT_SHIFT          (0)
DECL|macro|LAN_REPLY_FORM_MASK
mdefine_line|#define LAN_REPLY_FORM_MASK                     (0x18000000)
DECL|macro|LAN_REPLY_FORM_RECEIVE_SINGLE
mdefine_line|#define LAN_REPLY_FORM_RECEIVE_SINGLE           (0x00)
DECL|macro|LAN_REPLY_FORM_RECEIVE_MULTIPLE
mdefine_line|#define LAN_REPLY_FORM_RECEIVE_MULTIPLE         (0x01)
DECL|macro|LAN_REPLY_FORM_SEND_SINGLE
mdefine_line|#define LAN_REPLY_FORM_SEND_SINGLE              (0x02)
DECL|macro|LAN_REPLY_FORM_MESSAGE_CONTEXT
mdefine_line|#define LAN_REPLY_FORM_MESSAGE_CONTEXT          (0x03)
DECL|macro|LAN_REPLY_FORM_SHIFT
mdefine_line|#define LAN_REPLY_FORM_SHIFT                    (27)
DECL|macro|GET_LAN_PACKET_LENGTH
mdefine_line|#define GET_LAN_PACKET_LENGTH(x)    (((x) &amp; LAN_REPLY_PACKET_LENGTH_MASK)   &bslash;&n;                                        &gt;&gt; LAN_REPLY_PACKET_LENGTH_SHIFT)
DECL|macro|SET_LAN_PACKET_LENGTH
mdefine_line|#define SET_LAN_PACKET_LENGTH(x, lth)                                       &bslash;&n;            ((x) = ((x) &amp; ~LAN_REPLY_PACKET_LENGTH_MASK) |                  &bslash;&n;                            (((lth) &lt;&lt; LAN_REPLY_PACKET_LENGTH_SHIFT) &amp;     &bslash;&n;                                        LAN_REPLY_PACKET_LENGTH_MASK))
DECL|macro|GET_LAN_BUCKET_CONTEXT
mdefine_line|#define GET_LAN_BUCKET_CONTEXT(x)   (((x) &amp; LAN_REPLY_BUCKET_CONTEXT_MASK)  &bslash;&n;                                        &gt;&gt; LAN_REPLY_BUCKET_CONTEXT_SHIFT)
DECL|macro|SET_LAN_BUCKET_CONTEXT
mdefine_line|#define SET_LAN_BUCKET_CONTEXT(x, ctx)                                      &bslash;&n;            ((x) = ((x) &amp; ~LAN_REPLY_BUCKET_CONTEXT_MASK) |                 &bslash;&n;                            (((ctx) &lt;&lt; LAN_REPLY_BUCKET_CONTEXT_SHIFT) &amp;    &bslash;&n;                                        LAN_REPLY_BUCKET_CONTEXT_MASK))
DECL|macro|GET_LAN_BUFFER_CONTEXT
mdefine_line|#define GET_LAN_BUFFER_CONTEXT(x)   (((x) &amp; LAN_REPLY_BUFFER_CONTEXT_MASK)  &bslash;&n;                                        &gt;&gt; LAN_REPLY_BUFFER_CONTEXT_SHIFT)
DECL|macro|SET_LAN_BUFFER_CONTEXT
mdefine_line|#define SET_LAN_BUFFER_CONTEXT(x, ctx)                                      &bslash;&n;            ((x) = ((x) &amp; ~LAN_REPLY_BUFFER_CONTEXT_MASK) |                 &bslash;&n;                            (((ctx) &lt;&lt; LAN_REPLY_BUFFER_CONTEXT_SHIFT) &amp;    &bslash;&n;                                        LAN_REPLY_BUFFER_CONTEXT_MASK))
DECL|macro|GET_LAN_FORM
mdefine_line|#define GET_LAN_FORM(x)             (((x) &amp; LAN_REPLY_FORM_MASK)            &bslash;&n;                                        &gt;&gt; LAN_REPLY_FORM_SHIFT)
DECL|macro|SET_LAN_FORM
mdefine_line|#define SET_LAN_FORM(x, frm)                                                &bslash;&n;            ((x) = ((x) &amp; ~LAN_REPLY_FORM_MASK) |                           &bslash;&n;                            (((frm) &lt;&lt; LAN_REPLY_FORM_SHIFT) &amp;              &bslash;&n;                                        LAN_REPLY_FORM_MASK))
multiline_comment|/****************************************************************************/
multiline_comment|/* LAN Current Device State defines                                         */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_LAN_DEVICE_STATE_RESET
mdefine_line|#define MPI_LAN_DEVICE_STATE_RESET                     (0x00)
DECL|macro|MPI_LAN_DEVICE_STATE_OPERATIONAL
mdefine_line|#define MPI_LAN_DEVICE_STATE_OPERATIONAL               (0x01)
multiline_comment|/****************************************************************************/
multiline_comment|/* LAN Loopback defines                                                     */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_LAN_TX_MODES_ENABLE_LOOPBACK_SUPPRESSION
mdefine_line|#define MPI_LAN_TX_MODES_ENABLE_LOOPBACK_SUPPRESSION   (0x01)
macro_line|#endif
eof
