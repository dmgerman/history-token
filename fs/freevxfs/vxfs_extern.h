multiline_comment|/*&n; * Copyright (c) 2000-2001 Christoph Hellwig.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
macro_line|#ifndef _VXFS_EXTERN_H_
DECL|macro|_VXFS_EXTERN_H_
mdefine_line|#define _VXFS_EXTERN_H_
macro_line|#ident &quot;$Id: vxfs_extern.h,v 1.22 2001/12/28 20:50:47 hch Exp hch $&quot;
multiline_comment|/*&n; * Veritas filesystem driver - external prototypes.&n; *&n; * This file contains prototypes for all vxfs functions used&n; * outside their respective source files.&n; */
r_struct
id|kmem_cache_s
suffix:semicolon
r_struct
id|super_block
suffix:semicolon
r_struct
id|vxfs_inode_info
suffix:semicolon
r_struct
id|inode
suffix:semicolon
multiline_comment|/* vxfs_bmap.c */
r_extern
id|daddr_t
id|vxfs_bmap1
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* vxfs_fshead.c */
r_extern
r_int
id|vxfs_read_fshead
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
multiline_comment|/* vxfs_inode.c */
r_extern
r_struct
id|kmem_cache_s
op_star
id|vxfs_inode_cachep
suffix:semicolon
r_extern
r_void
id|vxfs_dumpi
c_func
(paren
r_struct
id|vxfs_inode_info
op_star
comma
id|ino_t
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|vxfs_get_fake_inode
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|vxfs_inode_info
op_star
)paren
suffix:semicolon
r_extern
r_void
id|vxfs_put_fake_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|vxfs_inode_info
op_star
id|vxfs_blkiget
c_func
(paren
r_struct
id|super_block
op_star
comma
id|u_long
comma
id|ino_t
)paren
suffix:semicolon
r_extern
r_struct
id|vxfs_inode_info
op_star
id|vxfs_stiget
c_func
(paren
r_struct
id|super_block
op_star
comma
id|ino_t
)paren
suffix:semicolon
r_extern
r_void
id|vxfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|vxfs_put_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* vxfs_lookup.c */
r_extern
r_struct
id|inode_operations
id|vxfs_dir_inode_ops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|vxfs_dir_operations
suffix:semicolon
multiline_comment|/* vxfs_olt.c */
r_extern
r_int
id|vxfs_read_olt
c_func
(paren
r_struct
id|super_block
op_star
comma
id|u_long
)paren
suffix:semicolon
multiline_comment|/* vxfs_subr.c */
r_extern
r_struct
id|page
op_star
id|vxfs_get_page
c_func
(paren
r_struct
id|address_space
op_star
comma
id|u_long
)paren
suffix:semicolon
r_extern
id|__inline__
r_void
id|vxfs_put_page
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|vxfs_bread
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* _VXFS_EXTERN_H_ */
eof
