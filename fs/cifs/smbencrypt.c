multiline_comment|/* &n;   Unix SMB/Netbios implementation.&n;   Version 1.9.&n;   SMB parameters and setup&n;   Copyright (C) Andrew Tridgell 1992-2000&n;   Copyright (C) Luke Kenneth Casson Leighton 1996-2000&n;   Modified by Jeremy Allison 1995.&n;   Copyright (C) Andrew Bartlett &lt;abartlet@samba.org&gt; 2002-2003&n;   Modified by Steve French (sfrench@us.ibm.com) 2002-2003&n;   &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;   &n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;   &n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &quot;cifs_unicode.h&quot;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;md5.h&quot;
macro_line|#include &quot;cifs_debug.h&quot;
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
multiline_comment|/* following came from the other byteorder.h to avoid include conflicts */
DECL|macro|CVAL
mdefine_line|#define CVAL(buf,pos) (((unsigned char *)(buf))[pos])
DECL|macro|SSVALX
mdefine_line|#define SSVALX(buf,pos,val) (CVAL(buf,pos)=(val)&amp;0xFF,CVAL(buf,pos+1)=(val)&gt;&gt;8)
DECL|macro|SIVALX
mdefine_line|#define SIVALX(buf,pos,val) (SSVALX(buf,pos,val&amp;0xFFFF),SSVALX(buf,pos+2,val&gt;&gt;16))
DECL|macro|SSVAL
mdefine_line|#define SSVAL(buf,pos,val) SSVALX((buf),(pos),((__u16)(val)))
DECL|macro|SIVAL
mdefine_line|#define SIVAL(buf,pos,val) SIVALX((buf),(pos),((__u32)(val)))
multiline_comment|/*The following definitions come from  lib/md4.c  */
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
multiline_comment|/*The following definitions come from  libsmb/smbdes.c  */
r_void
id|E_P16
c_func
(paren
r_int
r_char
op_star
id|p14
comma
r_int
r_char
op_star
id|p16
)paren
suffix:semicolon
r_void
id|E_P24
c_func
(paren
r_int
r_char
op_star
id|p21
comma
r_int
r_char
op_star
id|c8
comma
r_int
r_char
op_star
id|p24
)paren
suffix:semicolon
r_void
id|D_P16
c_func
(paren
r_int
r_char
op_star
id|p14
comma
r_int
r_char
op_star
id|in
comma
r_int
r_char
op_star
id|out
)paren
suffix:semicolon
r_void
id|E_old_pw_hash
c_func
(paren
r_int
r_char
op_star
id|p14
comma
r_int
r_char
op_star
id|in
comma
r_int
r_char
op_star
id|out
)paren
suffix:semicolon
r_void
id|cred_hash1
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
r_char
op_star
id|key
)paren
suffix:semicolon
r_void
id|cred_hash2
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
r_char
op_star
id|key
)paren
suffix:semicolon
r_void
id|cred_hash3
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
r_char
op_star
id|key
comma
r_int
id|forw
)paren
suffix:semicolon
multiline_comment|/*The following definitions come from  libsmb/smbencrypt.c  */
r_void
id|SMBencrypt
c_func
(paren
r_int
r_char
op_star
id|passwd
comma
r_int
r_char
op_star
id|c8
comma
r_int
r_char
op_star
id|p24
)paren
suffix:semicolon
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
r_void
id|nt_lm_owf_gen
c_func
(paren
r_char
op_star
id|pwd
comma
r_int
r_char
id|nt_p16
(braket
l_int|16
)braket
comma
r_int
r_char
id|p16
(braket
l_int|16
)braket
)paren
suffix:semicolon
r_void
id|SMBOWFencrypt
c_func
(paren
r_int
r_char
id|passwd
(braket
l_int|16
)braket
comma
r_int
r_char
op_star
id|c8
comma
r_int
r_char
id|p24
(braket
l_int|24
)braket
)paren
suffix:semicolon
r_void
id|NTLMSSPOWFencrypt
c_func
(paren
r_int
r_char
id|passwd
(braket
l_int|8
)braket
comma
r_int
r_char
op_star
id|ntlmchalresp
comma
r_int
r_char
id|p24
(braket
l_int|24
)braket
)paren
suffix:semicolon
r_void
id|SMBNTencrypt
c_func
(paren
r_int
r_char
op_star
id|passwd
comma
r_int
r_char
op_star
id|c8
comma
r_int
r_char
op_star
id|p24
)paren
suffix:semicolon
r_int
id|decode_pw_buffer
c_func
(paren
r_char
id|in_buffer
(braket
l_int|516
)braket
comma
r_char
op_star
id|new_pwrd
comma
r_int
id|new_pwrd_size
comma
id|__u32
op_star
id|new_pw_len
)paren
suffix:semicolon
multiline_comment|/*&n;   This implements the X/Open SMB password encryption&n;   It takes a password, a 8 byte &quot;crypt key&quot; and puts 24 bytes of &n;   encrypted password into p24 */
multiline_comment|/* Note that password must be uppercased and null terminated */
r_void
DECL|function|SMBencrypt
id|SMBencrypt
c_func
(paren
r_int
r_char
op_star
id|passwd
comma
r_int
r_char
op_star
id|c8
comma
r_int
r_char
op_star
id|p24
)paren
(brace
r_int
r_char
id|p14
(braket
l_int|15
)braket
comma
id|p21
(braket
l_int|21
)braket
suffix:semicolon
id|memset
c_func
(paren
id|p21
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|21
)paren
suffix:semicolon
id|memset
c_func
(paren
id|p14
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|14
)paren
suffix:semicolon
id|strncpy
c_func
(paren
(paren
r_char
op_star
)paren
id|p14
comma
(paren
r_char
op_star
)paren
id|passwd
comma
l_int|14
)paren
suffix:semicolon
multiline_comment|/*&t;strupper((char *)p14); */
multiline_comment|/* BB at least uppercase the easy range */
id|E_P16
c_func
(paren
id|p14
comma
id|p21
)paren
suffix:semicolon
id|SMBOWFencrypt
c_func
(paren
id|p21
comma
id|c8
comma
id|p24
)paren
suffix:semicolon
id|memset
c_func
(paren
id|p14
comma
l_int|0
comma
l_int|15
)paren
suffix:semicolon
id|memset
c_func
(paren
id|p21
comma
l_int|0
comma
l_int|21
)paren
suffix:semicolon
)brace
multiline_comment|/* Routines for Windows NT MD4 Hash functions. */
r_static
r_int
DECL|function|_my_wcslen
id|_my_wcslen
c_func
(paren
id|__u16
op_star
id|str
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|str
op_increment
op_ne
l_int|0
)paren
id|len
op_increment
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert a string into an NT UNICODE string.&n; * Note that regardless of processor type &n; * this must be in intel (little-endian)&n; * format.&n; */
r_static
r_int
DECL|function|_my_mbstowcs
id|_my_mbstowcs
c_func
(paren
id|__u16
op_star
id|dst
comma
r_const
r_int
r_char
op_star
id|src
comma
r_int
id|len
)paren
(brace
multiline_comment|/* not a very good conversion routine - change/fix */
r_int
id|i
suffix:semicolon
id|__u16
id|val
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|val
op_assign
op_star
id|src
suffix:semicolon
id|SSVAL
c_func
(paren
id|dst
comma
l_int|0
comma
id|val
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|src
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|val
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/* &n; * Creates the MD4 Hash of the users password in NT UNICODE.&n; */
r_void
DECL|function|E_md4hash
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
(brace
r_int
id|len
suffix:semicolon
id|__u16
id|wpwd
(braket
l_int|129
)braket
suffix:semicolon
multiline_comment|/* Password cannot be longer than 128 characters */
id|len
op_assign
id|strlen
c_func
(paren
(paren
r_char
op_star
)paren
id|passwd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|128
)paren
id|len
op_assign
l_int|128
suffix:semicolon
multiline_comment|/* Password must be converted to NT unicode */
id|_my_mbstowcs
c_func
(paren
id|wpwd
comma
id|passwd
comma
id|len
)paren
suffix:semicolon
id|wpwd
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Ensure string is null terminated */
multiline_comment|/* Calculate length in bytes */
id|len
op_assign
id|_my_wcslen
c_func
(paren
id|wpwd
)paren
op_star
r_sizeof
(paren
id|__u16
)paren
suffix:semicolon
id|mdfour
c_func
(paren
id|p16
comma
(paren
r_int
r_char
op_star
)paren
id|wpwd
comma
id|len
)paren
suffix:semicolon
id|memset
c_func
(paren
id|wpwd
comma
l_int|0
comma
l_int|129
op_star
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/* Does both the NT and LM owfs of a user&squot;s password */
r_void
DECL|function|nt_lm_owf_gen
id|nt_lm_owf_gen
c_func
(paren
r_char
op_star
id|pwd
comma
r_int
r_char
id|nt_p16
(braket
l_int|16
)braket
comma
r_int
r_char
id|p16
(braket
l_int|16
)braket
)paren
(brace
r_char
id|passwd
(braket
l_int|514
)braket
suffix:semicolon
id|memset
c_func
(paren
id|passwd
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|514
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|pwd
)paren
OL
l_int|513
)paren
id|strcpy
c_func
(paren
id|passwd
comma
id|pwd
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|passwd
comma
id|pwd
comma
l_int|512
)paren
suffix:semicolon
multiline_comment|/* Calculate the MD4 hash (NT compatible) of the password */
id|memset
c_func
(paren
id|nt_p16
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|16
)paren
suffix:semicolon
id|E_md4hash
c_func
(paren
id|passwd
comma
id|nt_p16
)paren
suffix:semicolon
multiline_comment|/* Mangle the passwords into Lanman format */
id|passwd
(braket
l_int|14
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/*&t;strupper(passwd); */
multiline_comment|/* Calculate the SMB (lanman) hash functions of the password */
id|memset
c_func
(paren
id|p16
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|16
)paren
suffix:semicolon
id|E_P16
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|passwd
comma
(paren
r_int
r_char
op_star
)paren
id|p16
)paren
suffix:semicolon
multiline_comment|/* clear out local copy of user&squot;s password (just being paranoid). */
id|memset
c_func
(paren
id|passwd
comma
l_char|&squot;&bslash;0&squot;
comma
r_sizeof
(paren
id|passwd
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Does the NTLMv2 owfs of a user&squot;s password */
r_void
DECL|function|ntv2_owf_gen
id|ntv2_owf_gen
c_func
(paren
r_const
r_int
r_char
id|owf
(braket
l_int|16
)braket
comma
r_const
r_char
op_star
id|user_n
comma
r_const
r_char
op_star
id|domain_n
comma
r_int
r_char
id|kr_buf
(braket
l_int|16
)braket
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
(brace
m_wchar_t
op_star
id|user_u
suffix:semicolon
m_wchar_t
op_star
id|dom_u
suffix:semicolon
r_int
id|user_l
comma
id|domain_l
suffix:semicolon
r_struct
id|HMACMD5Context
id|ctx
suffix:semicolon
multiline_comment|/* might as well do one alloc to hold both (user_u and dom_u) */
id|user_u
op_assign
id|kmalloc
c_func
(paren
l_int|2048
op_star
r_sizeof
(paren
m_wchar_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_u
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
id|dom_u
op_assign
id|user_u
op_plus
l_int|1024
suffix:semicolon
multiline_comment|/* push_ucs2(NULL, user_u, user_n, (user_l+1)*2, STR_UNICODE|STR_NOALIGN|STR_TERMINATE|STR_UPPER);&n;&t;   push_ucs2(NULL, dom_u, domain_n, (domain_l+1)*2, STR_UNICODE|STR_NOALIGN|STR_TERMINATE|STR_UPPER); */
multiline_comment|/* BB user and domain may need to be uppercased */
id|user_l
op_assign
id|cifs_strtoUCS
c_func
(paren
id|user_u
comma
id|user_n
comma
l_int|511
comma
id|nls_codepage
)paren
suffix:semicolon
id|domain_l
op_assign
id|cifs_strtoUCS
c_func
(paren
id|dom_u
comma
id|domain_n
comma
l_int|511
comma
id|nls_codepage
)paren
suffix:semicolon
id|user_l
op_increment
suffix:semicolon
multiline_comment|/* trailing null */
id|domain_l
op_increment
suffix:semicolon
id|hmac_md5_init_limK_to_64
c_func
(paren
id|owf
comma
l_int|16
comma
op_amp
id|ctx
)paren
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
id|user_u
comma
id|user_l
op_star
l_int|2
comma
op_amp
id|ctx
)paren
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
id|dom_u
comma
id|domain_l
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
id|kr_buf
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|user_u
)paren
suffix:semicolon
)brace
multiline_comment|/* Does the des encryption from the NT or LM MD4 hash. */
r_void
DECL|function|SMBOWFencrypt
id|SMBOWFencrypt
c_func
(paren
r_int
r_char
id|passwd
(braket
l_int|16
)braket
comma
r_int
r_char
op_star
id|c8
comma
r_int
r_char
id|p24
(braket
l_int|24
)braket
)paren
(brace
r_int
r_char
id|p21
(braket
l_int|21
)braket
suffix:semicolon
id|memset
c_func
(paren
id|p21
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|21
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p21
comma
id|passwd
comma
l_int|16
)paren
suffix:semicolon
id|E_P24
c_func
(paren
id|p21
comma
id|c8
comma
id|p24
)paren
suffix:semicolon
)brace
multiline_comment|/* Does the des encryption from the FIRST 8 BYTES of the NT or LM MD4 hash. */
r_void
DECL|function|NTLMSSPOWFencrypt
id|NTLMSSPOWFencrypt
c_func
(paren
r_int
r_char
id|passwd
(braket
l_int|8
)braket
comma
r_int
r_char
op_star
id|ntlmchalresp
comma
r_int
r_char
id|p24
(braket
l_int|24
)braket
)paren
(brace
r_int
r_char
id|p21
(braket
l_int|21
)braket
suffix:semicolon
id|memset
c_func
(paren
id|p21
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|21
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p21
comma
id|passwd
comma
l_int|8
)paren
suffix:semicolon
id|memset
c_func
(paren
id|p21
op_plus
l_int|8
comma
l_int|0xbd
comma
l_int|8
)paren
suffix:semicolon
id|E_P24
c_func
(paren
id|p21
comma
id|ntlmchalresp
comma
id|p24
)paren
suffix:semicolon
)brace
multiline_comment|/* Does the NT MD4 hash then des encryption. */
r_void
DECL|function|SMBNTencrypt
id|SMBNTencrypt
c_func
(paren
r_int
r_char
op_star
id|passwd
comma
r_int
r_char
op_star
id|c8
comma
r_int
r_char
op_star
id|p24
)paren
(brace
r_int
r_char
id|p21
(braket
l_int|21
)braket
suffix:semicolon
id|memset
c_func
(paren
id|p21
comma
l_char|&squot;&bslash;0&squot;
comma
l_int|21
)paren
suffix:semicolon
id|E_md4hash
c_func
(paren
id|passwd
comma
id|p21
)paren
suffix:semicolon
id|SMBOWFencrypt
c_func
(paren
id|p21
comma
id|c8
comma
id|p24
)paren
suffix:semicolon
)brace
multiline_comment|/* Does the md5 encryption from the NT hash for NTLMv2. */
r_void
DECL|function|SMBOWFencrypt_ntv2
id|SMBOWFencrypt_ntv2
c_func
(paren
r_const
r_int
r_char
id|kr
(braket
l_int|16
)braket
comma
r_const
r_struct
id|data_blob
op_star
id|srv_chal
comma
r_const
r_struct
id|data_blob
op_star
id|cli_chal
comma
r_int
r_char
id|resp_buf
(braket
l_int|16
)braket
)paren
(brace
r_struct
id|HMACMD5Context
id|ctx
suffix:semicolon
id|hmac_md5_init_limK_to_64
c_func
(paren
id|kr
comma
l_int|16
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|hmac_md5_update
c_func
(paren
id|srv_chal-&gt;data
comma
id|srv_chal-&gt;length
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|hmac_md5_update
c_func
(paren
id|cli_chal-&gt;data
comma
id|cli_chal-&gt;length
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|hmac_md5_final
c_func
(paren
id|resp_buf
comma
op_amp
id|ctx
)paren
suffix:semicolon
)brace
r_void
DECL|function|SMBsesskeygen_ntv2
id|SMBsesskeygen_ntv2
c_func
(paren
r_const
r_int
r_char
id|kr
(braket
l_int|16
)braket
comma
r_const
r_int
r_char
op_star
id|nt_resp
comma
id|__u8
id|sess_key
(braket
l_int|16
)braket
)paren
(brace
r_struct
id|HMACMD5Context
id|ctx
suffix:semicolon
id|hmac_md5_init_limK_to_64
c_func
(paren
id|kr
comma
l_int|16
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|hmac_md5_update
c_func
(paren
id|nt_resp
comma
l_int|16
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|hmac_md5_final
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|sess_key
comma
op_amp
id|ctx
)paren
suffix:semicolon
)brace
r_void
DECL|function|SMBsesskeygen_ntv1
id|SMBsesskeygen_ntv1
c_func
(paren
r_const
r_int
r_char
id|kr
(braket
l_int|16
)braket
comma
r_const
r_int
r_char
op_star
id|nt_resp
comma
id|__u8
id|sess_key
(braket
l_int|16
)braket
)paren
(brace
id|mdfour
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|sess_key
comma
(paren
r_int
r_char
op_star
)paren
id|kr
comma
l_int|16
)paren
suffix:semicolon
)brace
multiline_comment|/***********************************************************&n; encode a password buffer.  The caller gets to figure out &n; what to put in it.&n;************************************************************/
r_int
DECL|function|encode_pw_buffer
id|encode_pw_buffer
c_func
(paren
r_char
id|buffer
(braket
l_int|516
)braket
comma
r_char
op_star
id|new_pw
comma
r_int
id|new_pw_length
)paren
(brace
id|get_random_bytes
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|buffer
(braket
l_int|512
op_minus
id|new_pw_length
)braket
comma
id|new_pw
comma
id|new_pw_length
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * The length of the new password is in the last 4 bytes of&n;&t; * the data buffer.&n;&t; */
id|SIVAL
c_func
(paren
id|buffer
comma
l_int|512
comma
id|new_pw_length
)paren
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
eof
