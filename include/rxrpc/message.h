multiline_comment|/* message.h: Rx message caching&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_RXRPC_MESSAGE_H
DECL|macro|_LINUX_RXRPC_MESSAGE_H
mdefine_line|#define _LINUX_RXRPC_MESSAGE_H
macro_line|#include &lt;rxrpc/packet.h&gt;
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Rx message record&n; */
DECL|struct|rxrpc_message
r_struct
id|rxrpc_message
(brace
DECL|member|usage
id|atomic_t
id|usage
suffix:semicolon
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* list link */
DECL|member|stamp
r_struct
id|timeval
id|stamp
suffix:semicolon
multiline_comment|/* time received or last sent */
DECL|member|seq
id|rxrpc_seq_t
id|seq
suffix:semicolon
multiline_comment|/* message sequence number */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* the state the message is currently in */
DECL|macro|RXRPC_MSG_PREPARED
mdefine_line|#define RXRPC_MSG_PREPARED&t;0
DECL|macro|RXRPC_MSG_SENT
mdefine_line|#define RXRPC_MSG_SENT&t;&t;1
DECL|macro|RXRPC_MSG_ACKED
mdefine_line|#define RXRPC_MSG_ACKED&t;&t;2&t;&t;/* provisionally ACK&squot;d */
DECL|macro|RXRPC_MSG_DONE
mdefine_line|#define RXRPC_MSG_DONE&t;&t;3&t;&t;/* definitively ACK&squot;d (msg-&gt;seq&lt;ack.firstPacket) */
DECL|macro|RXRPC_MSG_RECEIVED
mdefine_line|#define RXRPC_MSG_RECEIVED&t;4
DECL|macro|RXRPC_MSG_ERROR
mdefine_line|#define RXRPC_MSG_ERROR&t;&t;-1
DECL|member|rttdone
r_char
id|rttdone
suffix:semicolon
multiline_comment|/* used for RTT */
DECL|member|trans
r_struct
id|rxrpc_transport
op_star
id|trans
suffix:semicolon
multiline_comment|/* transport received through */
DECL|member|conn
r_struct
id|rxrpc_connection
op_star
id|conn
suffix:semicolon
multiline_comment|/* connection received over */
DECL|member|pkt
r_struct
id|sk_buff
op_star
id|pkt
suffix:semicolon
multiline_comment|/* received packet */
DECL|member|offset
id|off_t
id|offset
suffix:semicolon
multiline_comment|/* offset into pkt of next byte of data */
DECL|member|hdr
r_struct
id|rxrpc_header
id|hdr
suffix:semicolon
multiline_comment|/* message header */
DECL|member|dcount
r_int
id|dcount
suffix:semicolon
multiline_comment|/* data part count */
DECL|member|dsize
r_int
id|dsize
suffix:semicolon
multiline_comment|/* data size */
DECL|macro|RXRPC_MSG_MAX_IOCS
mdefine_line|#define RXRPC_MSG_MAX_IOCS 8
DECL|member|data
r_struct
id|iovec
id|data
(braket
id|RXRPC_MSG_MAX_IOCS
)braket
suffix:semicolon
multiline_comment|/* message data */
DECL|member|dfree
r_int
r_int
id|dfree
suffix:semicolon
multiline_comment|/* bit mask indicating kfree(data[x]) if T */
)brace
suffix:semicolon
DECL|macro|rxrpc_get_message
mdefine_line|#define rxrpc_get_message(M) do { atomic_inc(&amp;(M)-&gt;usage); } while(0)
r_extern
r_void
id|__rxrpc_put_message
c_func
(paren
r_struct
id|rxrpc_message
op_star
id|msg
)paren
suffix:semicolon
DECL|function|rxrpc_put_message
r_static
r_inline
r_void
id|rxrpc_put_message
c_func
(paren
r_struct
id|rxrpc_message
op_star
id|msg
)paren
(brace
id|BUG_ON
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|msg-&gt;usage
)paren
op_le
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|msg-&gt;usage
)paren
)paren
id|__rxrpc_put_message
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
r_extern
r_int
id|rxrpc_conn_newmsg
c_func
(paren
r_struct
id|rxrpc_connection
op_star
id|conn
comma
r_struct
id|rxrpc_call
op_star
id|call
comma
r_uint8
id|type
comma
r_int
id|count
comma
r_struct
id|iovec
id|diov
(braket
)braket
comma
r_int
id|alloc_flags
comma
r_struct
id|rxrpc_message
op_star
op_star
id|_msg
)paren
suffix:semicolon
r_extern
r_int
id|rxrpc_conn_sendmsg
c_func
(paren
r_struct
id|rxrpc_connection
op_star
id|conn
comma
r_struct
id|rxrpc_message
op_star
id|msg
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_RXRPC_MESSAGE_H */
eof
