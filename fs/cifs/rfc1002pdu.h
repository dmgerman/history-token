multiline_comment|/*&n; *   fs/cifs/rfc1002pdu.h&n; *&n; *   Protocol Data Unit definitions for RFC 1001/1002 support&n; *&n; *   Copyright (c) International Business Machines  Corp., 2004&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA &n; */
macro_line|#pragma pack(1)
multiline_comment|/* NB: unlike smb/cifs packets, the RFC1002 structures are big endian */
multiline_comment|/* RFC 1002 session packet types */
DECL|macro|RFC1002_SESSION_MESASAGE
mdefine_line|#define RFC1002_SESSION_MESASAGE 0x00
DECL|macro|RFC1002_SESSION_REQUEST
mdefine_line|#define RFC1002_SESSION_REQUEST  0x81
DECL|macro|RFC1002_POSITIVE_SESSION_RESPONSE
mdefine_line|#define RFC1002_POSITIVE_SESSION_RESPONSE 0x82
DECL|macro|RFC1002_NEGATIVE_SESSION_RESPONSE
mdefine_line|#define RFC1002_NEGATIVE_SESSION_RESPONSE 0x83
DECL|macro|RFC1002_RETARGET_SESSION_RESPONSE
mdefine_line|#define RFC1002_RETARGET_SESSION_RESPONSE 0x83
DECL|macro|RFC1002_SESSION_KEEP_ALIVE
mdefine_line|#define RFC1002_SESSION_KEEP_ALIVE 0x85
multiline_comment|/* RFC 1002 flags (only one defined */
DECL|macro|RFC1002_LENGTH_EXTEND
mdefine_line|#define RFC1002_LENGTH_EXTEND 0x80 /* high order bit of length (ie +64K) */
DECL|struct|rfc1002_session_packet
r_struct
id|rfc1002_session_packet
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|called_len
id|__u8
id|called_len
suffix:semicolon
DECL|member|called_name
id|__u8
id|called_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|scope1
id|__u8
id|scope1
suffix:semicolon
multiline_comment|/* null */
DECL|member|calling_len
id|__u8
id|calling_len
suffix:semicolon
DECL|member|calling_name
id|__u8
id|calling_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|scope2
id|__u8
id|scope2
suffix:semicolon
multiline_comment|/* null */
DECL|member|session_req
)brace
id|session_req
suffix:semicolon
r_struct
(brace
DECL|member|retarget_ip_addr
id|__u32
id|retarget_ip_addr
suffix:semicolon
DECL|member|port
id|__u16
id|port
suffix:semicolon
DECL|member|retarget_resp
)brace
id|retarget_resp
suffix:semicolon
DECL|member|neg_ses_resp_error_code
id|__u8
id|neg_ses_resp_error_code
suffix:semicolon
multiline_comment|/* POSITIVE_SESSION_RESPONSE packet does not include trailer.&n;&t;&t;SESSION_KEEP_ALIVE packet also does not include a trailer.&n;&t;&t;Trailer for the SESSION_MESSAGE packet is SMB/CIFS header */
DECL|member|trailer
)brace
id|trailer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Negative Session Response error codes */
DECL|macro|RFC1002_NOT_LISTENING_CALLED
mdefine_line|#define RFC1002_NOT_LISTENING_CALLED  0x80 /* not listening on called name */
DECL|macro|RFC1002_NOT_LISTENING_CALLING
mdefine_line|#define RFC1002_NOT_LISTENING_CALLING 0x81 /* not listening on calling name */
DECL|macro|RFC1002_NOT_PRESENT
mdefine_line|#define RFC1002_NOT_PRESENT           0x82 /* called name not present */
DECL|macro|RFC1002_INSUFFICIENT_RESOURCE
mdefine_line|#define RFC1002_INSUFFICIENT_RESOURCE 0x83
DECL|macro|RFC1002_UNSPECIFIED_ERROR
mdefine_line|#define RFC1002_UNSPECIFIED_ERROR     0x8F
multiline_comment|/* RFC 1002 Datagram service packets are not defined here as they&n;are not needed for the network filesystem client unless we plan on&n;implementing broadcast resolution of the server ip address (from&n;server netbios name). Currently server names are resolved only via DNS&n;(tcp name) or ip address or an /etc/hosts equivalent mapping to ip address.*/
DECL|macro|DEFAULT_CIFS_CALLED_NAME
mdefine_line|#define DEFAULT_CIFS_CALLED_NAME  &quot;*SMBSERVER      &quot;
macro_line|#pragma pack()&t;&t;/* resume default structure packing */
eof
