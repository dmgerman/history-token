multiline_comment|/*&n; *   fs/cifs/cifsencrypt.c&n; *&n; *   Copyright (C) International Business Machines  Corp., 2003&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;cifsglob.h&quot; 
macro_line|#include &quot;cifs_debug.h&quot;
macro_line|#include &quot;md5.h&quot;
macro_line|#include &quot;cifs_unicode.h&quot;
multiline_comment|/* Calculate and return the CIFS signature based on the mac key and the smb pdu */
multiline_comment|/* the 16 byte signature must be allocated by the caller  */
multiline_comment|/* Note we only use the 1st eight bytes */
multiline_comment|/* Note that the smb header signature field on input contains the  &n;&t;sequence number before this function is called */
r_extern
r_void
id|mdfour
c_func
(paren
r_int
r_char
op_star
id|out
comma
r_int
r_char
op_star
id|in
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
id|E_md4hash
c_func
(paren
r_const
r_int
r_char
op_star
id|passwd
comma
r_int
r_char
op_star
id|p16
)paren
suffix:semicolon
DECL|function|cifs_calculate_signature
r_static
r_int
id|cifs_calculate_signature
c_func
(paren
r_const
r_struct
id|smb_hdr
op_star
id|cifs_pdu
comma
r_const
r_char
op_star
id|key
comma
r_char
op_star
id|signature
)paren
(brace
r_struct
id|MD5Context
id|context
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cifs_pdu
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|signature
op_eq
l_int|NULL
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|MD5Init
c_func
(paren
op_amp
id|context
)paren
suffix:semicolon
id|MD5Update
c_func
(paren
op_amp
id|context
comma
id|key
comma
id|CIFS_SESSION_KEY_SIZE
op_plus
l_int|16
)paren
suffix:semicolon
id|MD5Update
c_func
(paren
op_amp
id|context
comma
id|cifs_pdu-&gt;Protocol
comma
id|cifs_pdu-&gt;smb_buf_length
)paren
suffix:semicolon
id|MD5Final
c_func
(paren
id|signature
comma
op_amp
id|context
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cifs_sign_smb
r_int
id|cifs_sign_smb
c_func
(paren
r_struct
id|smb_hdr
op_star
id|cifs_pdu
comma
r_struct
id|cifsSesInfo
op_star
id|ses
comma
id|__u32
op_star
id|pexpected_response_sequence_number
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_char
id|smb_signature
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* BB remember to initialize sequence number elsewhere and initialize mac_signing key elsewhere BB */
multiline_comment|/* BB remember to add code to save expected sequence number in midQ entry BB */
r_if
c_cond
(paren
(paren
id|cifs_pdu
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|ses
op_eq
l_int|NULL
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|le32_to_cpu
c_func
(paren
id|cifs_pdu-&gt;Flags2
)paren
op_amp
id|SMBFLG2_SECURITY_SIGNATURE
)paren
op_eq
l_int|0
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|cifs_pdu-&gt;Signature.Sequence.SequenceNumber
op_assign
id|cpu_to_le32
c_func
(paren
id|ses-&gt;sequence_number
)paren
suffix:semicolon
id|cifs_pdu-&gt;Signature.Sequence.Reserved
op_assign
l_int|0
suffix:semicolon
op_star
id|pexpected_response_sequence_number
op_assign
id|ses-&gt;sequence_number
op_increment
suffix:semicolon
id|ses-&gt;sequence_number
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|rc
op_assign
id|cifs_calculate_signature
c_func
(paren
id|cifs_pdu
comma
id|ses-&gt;mac_signing_key
comma
id|smb_signature
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|memset
c_func
(paren
id|cifs_pdu-&gt;Signature.SecuritySignature
comma
l_int|0
comma
l_int|8
)paren
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
id|cifs_pdu-&gt;Signature.SecuritySignature
comma
id|smb_signature
comma
l_int|8
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|cifs_verify_signature
r_int
id|cifs_verify_signature
c_func
(paren
r_struct
id|smb_hdr
op_star
id|cifs_pdu
comma
r_const
r_char
op_star
id|mac_key
comma
id|__u32
id|expected_sequence_number
)paren
(brace
r_int
r_int
id|rc
suffix:semicolon
r_char
id|server_response_sig
(braket
l_int|8
)braket
suffix:semicolon
r_char
id|what_we_think_sig_should_be
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cifs_pdu
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|mac_key
op_eq
l_int|NULL
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cifs_pdu-&gt;Command
op_eq
id|SMB_COM_NEGOTIATE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cifs_pdu-&gt;Command
op_eq
id|SMB_COM_LOCKING_ANDX
)paren
(brace
r_struct
id|smb_com_lock_req
op_star
id|pSMB
op_assign
(paren
r_struct
id|smb_com_lock_req
op_star
)paren
id|cifs_pdu
suffix:semicolon
r_if
c_cond
(paren
id|pSMB-&gt;LockType
op_amp
id|LOCKING_ANDX_OPLOCK_RELEASE
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* BB what if signatures are supposed to be on for session but server does not&n;&t;&t;send one? BB */
multiline_comment|/* Do not need to verify session setups with signature &quot;BSRSPYL &quot;  */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|cifs_pdu-&gt;Signature.SecuritySignature
comma
l_string|&quot;BSRSPYL &quot;
comma
l_int|8
)paren
op_eq
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;dummy signature received for smb command 0x%x&quot;
comma
id|cifs_pdu-&gt;Command
)paren
)paren
suffix:semicolon
)brace
id|expected_sequence_number
op_assign
id|cpu_to_le32
c_func
(paren
id|expected_sequence_number
)paren
suffix:semicolon
multiline_comment|/* save off the origiginal signature so we can modify the smb and check&n;&t;&t;its signature against what the server sent */
id|memcpy
c_func
(paren
id|server_response_sig
comma
id|cifs_pdu-&gt;Signature.SecuritySignature
comma
l_int|8
)paren
suffix:semicolon
id|cifs_pdu-&gt;Signature.Sequence.SequenceNumber
op_assign
id|expected_sequence_number
suffix:semicolon
id|cifs_pdu-&gt;Signature.Sequence.Reserved
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|cifs_calculate_signature
c_func
(paren
id|cifs_pdu
comma
id|mac_key
comma
id|what_we_think_sig_should_be
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&t;cifs_dump_mem(&quot;what we think it should be: &quot;,what_we_think_sig_should_be,16); */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|server_response_sig
comma
id|what_we_think_sig_should_be
comma
l_int|8
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We fill in key by putting in 40 byte array which was allocated by caller */
DECL|function|cifs_calculate_mac_key
r_int
id|cifs_calculate_mac_key
c_func
(paren
r_char
op_star
id|key
comma
r_const
r_char
op_star
id|rn
comma
r_const
r_char
op_star
id|password
)paren
(brace
r_char
id|temp_key
(braket
l_int|16
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|key
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|rn
op_eq
l_int|NULL
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|E_md4hash
c_func
(paren
id|password
comma
id|temp_key
)paren
suffix:semicolon
id|mdfour
c_func
(paren
id|key
comma
id|temp_key
comma
l_int|16
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|key
op_plus
l_int|16
comma
id|rn
comma
id|CIFS_SESSION_KEY_SIZE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|CalcNTLMv2_partial_mac_key
r_int
id|CalcNTLMv2_partial_mac_key
c_func
(paren
r_struct
id|cifsSesInfo
op_star
id|ses
comma
r_struct
id|nls_table
op_star
id|nls_info
)paren
(brace
r_char
id|temp_hash
(braket
l_int|16
)braket
suffix:semicolon
r_struct
id|HMACMD5Context
id|ctx
suffix:semicolon
r_char
op_star
id|ucase_buf
suffix:semicolon
m_wchar_t
op_star
id|unicode_buf
suffix:semicolon
r_int
r_int
id|i
comma
id|user_name_len
comma
id|dom_name_len
suffix:semicolon
r_if
c_cond
(paren
id|ses
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|E_md4hash
c_func
(paren
id|ses-&gt;password
comma
id|temp_hash
)paren
suffix:semicolon
id|hmac_md5_init_limK_to_64
c_func
(paren
id|temp_hash
comma
l_int|16
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|user_name_len
op_assign
id|strlen
c_func
(paren
id|ses-&gt;userName
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_name_len
OG
id|MAX_USERNAME_SIZE
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dom_name_len
op_assign
id|strlen
c_func
(paren
id|ses-&gt;domainName
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dom_name_len
OG
id|MAX_USERNAME_SIZE
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ucase_buf
op_assign
id|kmalloc
c_func
(paren
(paren
id|MAX_USERNAME_SIZE
op_plus
l_int|1
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|unicode_buf
op_assign
id|kmalloc
c_func
(paren
(paren
id|MAX_USERNAME_SIZE
op_plus
l_int|1
)paren
op_star
l_int|4
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|user_name_len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ucase_buf
(braket
id|i
)braket
op_assign
id|nls_info-&gt;charset2upper
(braket
(paren
r_int
)paren
id|ses-&gt;userName
(braket
id|i
)braket
)braket
suffix:semicolon
)brace
id|ucase_buf
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|user_name_len
op_assign
id|cifs_strtoUCS
c_func
(paren
id|unicode_buf
comma
id|ucase_buf
comma
id|MAX_USERNAME_SIZE
op_star
l_int|2
comma
id|nls_info
)paren
suffix:semicolon
id|unicode_buf
(braket
id|user_name_len
)braket
op_assign
l_int|0
suffix:semicolon
id|user_name_len
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dom_name_len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ucase_buf
(braket
id|i
)braket
op_assign
id|nls_info-&gt;charset2upper
(braket
(paren
r_int
)paren
id|ses-&gt;domainName
(braket
id|i
)braket
)braket
suffix:semicolon
)brace
id|ucase_buf
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|dom_name_len
op_assign
id|cifs_strtoUCS
c_func
(paren
id|unicode_buf
op_plus
id|user_name_len
comma
id|ucase_buf
comma
id|MAX_USERNAME_SIZE
op_star
l_int|2
comma
id|nls_info
)paren
suffix:semicolon
id|unicode_buf
(braket
id|user_name_len
op_plus
id|dom_name_len
)braket
op_assign
l_int|0
suffix:semicolon
id|hmac_md5_update
c_func
(paren
(paren
r_const
r_int
r_char
op_star
)paren
id|unicode_buf
comma
(paren
id|user_name_len
op_plus
id|dom_name_len
)paren
op_star
l_int|2
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|hmac_md5_final
c_func
(paren
id|ses-&gt;mac_signing_key
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ucase_buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|unicode_buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|CalcNTLMv2_response
r_void
id|CalcNTLMv2_response
c_func
(paren
r_const
r_struct
id|cifsSesInfo
op_star
id|ses
comma
r_char
op_star
id|v2_session_response
)paren
(brace
r_struct
id|HMACMD5Context
id|context
suffix:semicolon
id|memcpy
c_func
(paren
id|v2_session_response
op_plus
l_int|8
comma
id|ses-&gt;server-&gt;cryptKey
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* gen_blob(v2_session_response + 16); */
id|hmac_md5_init_limK_to_64
c_func
(paren
id|ses-&gt;mac_signing_key
comma
l_int|16
comma
op_amp
id|context
)paren
suffix:semicolon
id|hmac_md5_update
c_func
(paren
id|ses-&gt;server-&gt;cryptKey
comma
l_int|8
comma
op_amp
id|context
)paren
suffix:semicolon
multiline_comment|/*&t;hmac_md5_update(v2_session_response+16)client thing,8,&amp;context); */
multiline_comment|/* BB fix */
id|hmac_md5_final
c_func
(paren
id|v2_session_response
comma
op_amp
id|context
)paren
suffix:semicolon
)brace
eof
