multiline_comment|/*&n; *   fs/cifs/cifsencrypt.c&n; *&n; *   Copyright (c) International Business Machines  Corp., 2003&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;cifsglob.h&quot; 
macro_line|#include &quot;cifs_debug.h&quot;
macro_line|#include &quot;md5.h&quot;
multiline_comment|/* Calculate and return the CIFS signature based on the mac key and the smb pdu */
multiline_comment|/* the 16 byte signature must be allocated by the caller  */
multiline_comment|/* Note we only use the 1st eight bytes */
multiline_comment|/* Note that the smb header signature field on input contains the  &n;&t;sequence number before this function is called */
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
id|cifs_dump_mem
c_func
(paren
l_string|&quot;signature: &quot;
comma
id|signature
comma
l_int|16
)paren
suffix:semicolon
multiline_comment|/* BB remove BB */
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
id|write_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|cifs_pdu-&gt;Signature.Sequence.SequenceNumber
op_assign
id|ses-&gt;sequence_number
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
id|write_unlock
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
r_const
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
op_assign
l_int|0
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
multiline_comment|/* BB no need to verify negprot or if flag is not on for session (or for frame?? */
multiline_comment|/* BB what if signatures are supposed to be on for session but server does not&n;&t;&t;send one? BB */
multiline_comment|/* BB also do not verify oplock breaks for signature */
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
r_return
id|rc
suffix:semicolon
)brace
eof
