multiline_comment|/*&n; *   fs/cifs/ntlmssp.h&n; *&n; *   Copyright (c) International Business Machines  Corp., 2002&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA &n; */
macro_line|#pragma pack(1)
DECL|macro|NTLMSSP_SIGNATURE
mdefine_line|#define NTLMSSP_SIGNATURE &quot;NTLMSSP&quot;
multiline_comment|/* Message Types */
DECL|macro|NtLmNegotiate
mdefine_line|#define NtLmNegotiate     1
DECL|macro|NtLmChallenge
mdefine_line|#define NtLmChallenge     2
DECL|macro|NtLmAuthenticate
mdefine_line|#define NtLmAuthenticate  3
DECL|macro|UnknownMessage
mdefine_line|#define UnknownMessage    8
multiline_comment|/* Negotiate Flags */
DECL|macro|NTLMSSP_NEGOTIATE_UNICODE
mdefine_line|#define NTLMSSP_NEGOTIATE_UNICODE       0x01&t;
singleline_comment|// Text strings are in unicode
DECL|macro|NTLMSSP_NEGOTIATE_OEM
mdefine_line|#define NTLMSSP_NEGOTIATE_OEM           0x02&t;
singleline_comment|// Text strings are in OEM
DECL|macro|NTLMSSP_REQUEST_TARGET
mdefine_line|#define NTLMSSP_REQUEST_TARGET          0x04&t;
singleline_comment|// Server return its auth realm
DECL|macro|NTLMSSP_NEGOTIATE_SIGN
mdefine_line|#define NTLMSSP_NEGOTIATE_SIGN        0x0010&t;
singleline_comment|// Request signature capability
DECL|macro|NTLMSSP_NEGOTIATE_SEAL
mdefine_line|#define NTLMSSP_NEGOTIATE_SEAL        0x0020&t;
singleline_comment|// Request confidentiality
DECL|macro|NTLMSSP_NEGOTIATE_DGRAM
mdefine_line|#define NTLMSSP_NEGOTIATE_DGRAM       0x0040
DECL|macro|NTLMSSP_NEGOTIATE_LM_KEY
mdefine_line|#define NTLMSSP_NEGOTIATE_LM_KEY      0x0080&t;
singleline_comment|// Use LM session key for sign/seal
DECL|macro|NTLMSSP_NEGOTIATE_NTLM
mdefine_line|#define NTLMSSP_NEGOTIATE_NTLM        0x0200&t;
singleline_comment|// NTLM authentication
DECL|macro|NTLMSSP_NEGOTIATE_DOMAIN_SUPPLIED
mdefine_line|#define NTLMSSP_NEGOTIATE_DOMAIN_SUPPLIED 0x1000
DECL|macro|NTLMSSP_NEGOTIATE_WORKSTATION_SUPPLIED
mdefine_line|#define NTLMSSP_NEGOTIATE_WORKSTATION_SUPPLIED 0x2000
DECL|macro|NTLMSSP_NEGOTIATE_LOCAL_CALL
mdefine_line|#define NTLMSSP_NEGOTIATE_LOCAL_CALL  0x4000&t;
singleline_comment|// client/server on same machine
DECL|macro|NTLMSSP_NEGOTIATE_ALWAYS_SIGN
mdefine_line|#define NTLMSSP_NEGOTIATE_ALWAYS_SIGN 0x8000&t;
singleline_comment|// Sign for all security levels
DECL|macro|NTLMSSP_TARGET_TYPE_DOMAIN
mdefine_line|#define NTLMSSP_TARGET_TYPE_DOMAIN   0x10000
DECL|macro|NTLMSSP_TARGET_TYPE_SERVER
mdefine_line|#define NTLMSSP_TARGET_TYPE_SERVER   0x20000
DECL|macro|NTLMSSP_TARGET_TYPE_SHARE
mdefine_line|#define NTLMSSP_TARGET_TYPE_SHARE    0x40000
DECL|macro|NTLMSSP_NEGOTIATE_NTLMV2
mdefine_line|#define NTLMSSP_NEGOTIATE_NTLMV2     0x80000
DECL|macro|NTLMSSP_REQUEST_INIT_RESP
mdefine_line|#define NTLMSSP_REQUEST_INIT_RESP   0x100000
DECL|macro|NTLMSSP_REQUEST_ACCEPT_RESP
mdefine_line|#define NTLMSSP_REQUEST_ACCEPT_RESP 0x200000
DECL|macro|NTLMSSP_REQUEST_NOT_NT_KEY
mdefine_line|#define NTLMSSP_REQUEST_NOT_NT_KEY  0x400000
DECL|macro|NTLMSSP_NEGOTIATE_TARGET_INFO
mdefine_line|#define NTLMSSP_NEGOTIATE_TARGET_INFO 0x800000
DECL|macro|NTLMSSP_NEGOTIATE_128
mdefine_line|#define NTLMSSP_NEGOTIATE_128     0x20000000
DECL|macro|NTLMSSP_NEGOTIATE_KEY_XCH
mdefine_line|#define NTLMSSP_NEGOTIATE_KEY_XCH 0x40000000
DECL|macro|NTLMSSP_NEGOTIATE_56
mdefine_line|#define NTLMSSP_NEGOTIATE_56      0x80000000
multiline_comment|/* Although typedefs are not commonly used for structure definitions */
multiline_comment|/* in the Linux kernel, in this particular case they are useful      */
multiline_comment|/* to more closely match the standards document for NTLMSSP from     */
multiline_comment|/* OpenGroup and to make the code more closely match the standard in */
multiline_comment|/* appearance */
DECL|struct|_SECURITY_BUFFER
r_typedef
r_struct
id|_SECURITY_BUFFER
(brace
DECL|member|Length
id|__u16
id|Length
suffix:semicolon
DECL|member|MaximumLength
id|__u16
id|MaximumLength
suffix:semicolon
DECL|member|Buffer
id|__u32
id|Buffer
suffix:semicolon
multiline_comment|/* offset to buffer */
DECL|typedef|SECURITY_BUFFER
)brace
id|SECURITY_BUFFER
suffix:semicolon
DECL|struct|_NEGOTIATE_MESSAGE
r_typedef
r_struct
id|_NEGOTIATE_MESSAGE
(brace
DECL|member|Signature
id|__u8
id|Signature
(braket
r_sizeof
(paren
id|NTLMSSP_SIGNATURE
)paren
)braket
suffix:semicolon
DECL|member|MessageType
id|__u32
id|MessageType
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|NegotiateFlags
id|__u32
id|NegotiateFlags
suffix:semicolon
DECL|member|DomainName
id|SECURITY_BUFFER
id|DomainName
suffix:semicolon
multiline_comment|/* RFC 1001 style and ASCII */
DECL|member|WorkstationName
id|SECURITY_BUFFER
id|WorkstationName
suffix:semicolon
multiline_comment|/* RFC 1001 and ASCII */
DECL|member|DomainString
r_char
id|DomainString
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* followed by WorkstationString */
DECL|typedef|NEGOTIATE_MESSAGE
DECL|typedef|PNEGOTIATE_MESSAGE
)brace
id|NEGOTIATE_MESSAGE
comma
op_star
id|PNEGOTIATE_MESSAGE
suffix:semicolon
DECL|struct|_CHALLENGE_MESSAGE
r_typedef
r_struct
id|_CHALLENGE_MESSAGE
(brace
DECL|member|Signature
id|__u8
id|Signature
(braket
r_sizeof
(paren
id|NTLMSSP_SIGNATURE
)paren
)braket
suffix:semicolon
DECL|member|MessageType
id|__u32
id|MessageType
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|TargetName
id|SECURITY_BUFFER
id|TargetName
suffix:semicolon
DECL|member|NegotiateFlags
id|__u32
id|NegotiateFlags
suffix:semicolon
DECL|member|Challenge
id|__u8
id|Challenge
(braket
id|CIFS_CRYPTO_KEY_SIZE
)braket
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|TargetInfoArray
id|SECURITY_BUFFER
id|TargetInfoArray
suffix:semicolon
DECL|typedef|CHALLENGE_MESSAGE
DECL|typedef|PCHALLENGE_MESSAGE
)brace
id|CHALLENGE_MESSAGE
comma
op_star
id|PCHALLENGE_MESSAGE
suffix:semicolon
DECL|struct|_AUTHENTICATE_MESSAGE
r_typedef
r_struct
id|_AUTHENTICATE_MESSAGE
(brace
DECL|member|Signature
id|__u8
id|Signature
(braket
r_sizeof
(paren
id|NTLMSSP_SIGNATURE
)paren
)braket
suffix:semicolon
DECL|member|MessageType
id|__u32
id|MessageType
suffix:semicolon
multiline_comment|/* 3 */
DECL|member|LmChallengeResponse
id|SECURITY_BUFFER
id|LmChallengeResponse
suffix:semicolon
DECL|member|NtChallengeResponse
id|SECURITY_BUFFER
id|NtChallengeResponse
suffix:semicolon
DECL|member|DomainName
id|SECURITY_BUFFER
id|DomainName
suffix:semicolon
DECL|member|UserName
id|SECURITY_BUFFER
id|UserName
suffix:semicolon
DECL|member|WorkstationName
id|SECURITY_BUFFER
id|WorkstationName
suffix:semicolon
DECL|member|SessionKey
id|SECURITY_BUFFER
id|SessionKey
suffix:semicolon
DECL|member|NegotiateFlags
id|__u32
id|NegotiateFlags
suffix:semicolon
DECL|member|UserString
r_char
id|UserString
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|AUTHENTICATE_MESSAGE
DECL|typedef|PAUTHENTICATE_MESSAGE
)brace
id|AUTHENTICATE_MESSAGE
comma
op_star
id|PAUTHENTICATE_MESSAGE
suffix:semicolon
macro_line|#pragma pack()&t;&t;&t;/* resume default structure packing */
eof
