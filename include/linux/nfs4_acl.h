multiline_comment|/*&n; *  include/linux/nfs4_acl.c&n; *&n; *  Common NFSv4 ACL handling definitions.&n; *&n; *  Copyright (c) 2002 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Marius Aamodt Eriksen &lt;marius@umich.edu&gt;&n; *&n; *  Redistribution and use in source and binary forms, with or without&n; *  modification, are permitted provided that the following conditions&n; *  are met:&n; *&n; *  1. Redistributions of source code must retain the above copyright&n; *     notice, this list of conditions and the following disclaimer.&n; *  2. Redistributions in binary form must reproduce the above copyright&n; *     notice, this list of conditions and the following disclaimer in the&n; *     documentation and/or other materials provided with the distribution.&n; *  3. Neither the name of the University nor the names of its&n; *     contributors may be used to endorse or promote products derived&n; *     from this software without specific prior written permission.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR&n; *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF&n; *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR&n; *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF&n; *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING&n; *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS&n; *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; */
macro_line|#ifndef LINUX_NFS4_ACL_H
DECL|macro|LINUX_NFS4_ACL_H
mdefine_line|#define LINUX_NFS4_ACL_H
macro_line|#include &lt;linux/posix_acl.h&gt;
r_struct
id|nfs4_acl
op_star
id|nfs4_acl_new
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nfs4_acl_free
c_func
(paren
r_struct
id|nfs4_acl
op_star
)paren
suffix:semicolon
r_int
id|nfs4_acl_add_ace
c_func
(paren
r_struct
id|nfs4_acl
op_star
comma
id|u32
comma
id|u32
comma
id|u32
comma
r_int
comma
id|uid_t
)paren
suffix:semicolon
r_int
id|nfs4_acl_get_whotype
c_func
(paren
r_char
op_star
comma
id|u32
)paren
suffix:semicolon
r_int
id|nfs4_acl_write_who
c_func
(paren
r_int
id|who
comma
r_char
op_star
id|p
)paren
suffix:semicolon
r_int
id|nfs4_acl_permission
c_func
(paren
r_struct
id|nfs4_acl
op_star
id|acl
comma
id|uid_t
id|owner
comma
id|gid_t
id|group
comma
id|uid_t
id|who
comma
id|u32
id|mask
)paren
suffix:semicolon
DECL|macro|NFS4_ACL_TYPE_DEFAULT
mdefine_line|#define NFS4_ACL_TYPE_DEFAULT&t;0x01
DECL|macro|NFS4_ACL_DIR
mdefine_line|#define NFS4_ACL_DIR&t;&t;0x02
DECL|macro|NFS4_ACL_OWNER
mdefine_line|#define NFS4_ACL_OWNER&t;&t;0x04
r_struct
id|nfs4_acl
op_star
id|nfs4_acl_posix_to_nfsv4
c_func
(paren
r_struct
id|posix_acl
op_star
comma
r_struct
id|posix_acl
op_star
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_int
id|nfs4_acl_nfsv4_to_posix
c_func
(paren
r_struct
id|nfs4_acl
op_star
comma
r_struct
id|posix_acl
op_star
op_star
comma
r_struct
id|posix_acl
op_star
op_star
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
macro_line|#endif /* LINUX_NFS4_ACL_H */
eof
