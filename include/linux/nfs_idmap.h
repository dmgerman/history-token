multiline_comment|/*&n; * include/linux/nfs_idmap.h&n; *&n; *  UID and GID to name mapping for clients.&n; *&n; *  Copyright (c) 2002 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Marius Aamodt Eriksen &lt;marius@umich.edu&gt;&n; *&n; *  Redistribution and use in source and binary forms, with or without&n; *  modification, are permitted provided that the following conditions&n; *  are met:&n; *&n; *  1. Redistributions of source code must retain the above copyright&n; *     notice, this list of conditions and the following disclaimer.&n; *  2. Redistributions in binary form must reproduce the above copyright&n; *     notice, this list of conditions and the following disclaimer in the&n; *     documentation and/or other materials provided with the distribution.&n; *  3. Neither the name of the University nor the names of its&n; *     contributors may be used to endorse or promote products derived&n; *     from this software without specific prior written permission.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR&n; *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF&n; *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR&n; *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF&n; *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING&n; *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS&n; *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; */
macro_line|#ifndef NFS_IDMAP_H
DECL|macro|NFS_IDMAP_H
mdefine_line|#define NFS_IDMAP_H
multiline_comment|/* XXX from bits/utmp.h  */
DECL|macro|IDMAP_NAMESZ
mdefine_line|#define IDMAP_NAMESZ  128
DECL|macro|IDMAP_TYPE_USER
mdefine_line|#define IDMAP_TYPE_USER  0
DECL|macro|IDMAP_TYPE_GROUP
mdefine_line|#define IDMAP_TYPE_GROUP 1
DECL|macro|IDMAP_CONV_IDTONAME
mdefine_line|#define IDMAP_CONV_IDTONAME 0
DECL|macro|IDMAP_CONV_NAMETOID
mdefine_line|#define IDMAP_CONV_NAMETOID 1
DECL|macro|IDMAP_STATUS_INVALIDMSG
mdefine_line|#define IDMAP_STATUS_INVALIDMSG 0x01
DECL|macro|IDMAP_STATUS_AGAIN
mdefine_line|#define IDMAP_STATUS_AGAIN      0x02
DECL|macro|IDMAP_STATUS_LOOKUPFAIL
mdefine_line|#define IDMAP_STATUS_LOOKUPFAIL 0x04
DECL|macro|IDMAP_STATUS_SUCCESS
mdefine_line|#define IDMAP_STATUS_SUCCESS    0x08
DECL|struct|idmap_msg
r_struct
id|idmap_msg
(brace
DECL|member|im_type
id|u_int8_t
id|im_type
suffix:semicolon
DECL|member|im_conv
id|u_int8_t
id|im_conv
suffix:semicolon
DECL|member|im_name
r_char
id|im_name
(braket
id|IDMAP_NAMESZ
)braket
suffix:semicolon
DECL|member|im_id
id|u_int32_t
id|im_id
suffix:semicolon
DECL|member|im_status
id|u_int8_t
id|im_status
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_void
op_star
id|nfs_idmap_new
c_func
(paren
r_struct
id|nfs_server
op_star
)paren
suffix:semicolon
r_void
id|nfs_idmap_delete
c_func
(paren
r_struct
id|nfs_server
op_star
)paren
suffix:semicolon
r_int
id|nfs_idmap_id
c_func
(paren
r_struct
id|nfs_server
op_star
comma
id|u_int8_t
comma
r_char
op_star
comma
id|u_int
comma
id|uid_t
op_star
)paren
suffix:semicolon
r_int
id|nfs_idmap_name
c_func
(paren
r_struct
id|nfs_server
op_star
comma
id|u_int8_t
comma
id|uid_t
comma
r_char
op_star
comma
id|u_int
op_star
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* NFS_IDMAP_H */
eof
