multiline_comment|/*&n; * Copyright (c) 2000-2001 Christoph Hellwig.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
macro_line|#ifndef _VXFS_DIR_H_
DECL|macro|_VXFS_DIR_H_
mdefine_line|#define _VXFS_DIR_H_
macro_line|#ident &quot;$Id: vxfs_dir.h,v 1.4 2001/04/24 19:28:36 hch Exp hch $&quot;
multiline_comment|/*&n; * Veritas filesystem driver - directory structure.&n; *&n; * This file contains the definition of the vxfs directory format.&n; */
multiline_comment|/*&n; * VxFS directory block header.&n; */
DECL|struct|vxfs_dirblk
r_struct
id|vxfs_dirblk
(brace
DECL|member|d_free
id|u_int16_t
id|d_free
suffix:semicolon
DECL|member|d_nhash
id|u_int16_t
id|d_nhash
suffix:semicolon
DECL|member|d_hash
id|u_int16_t
id|d_hash
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Special dirblk for immed inodes:  no hash.&n; */
DECL|struct|vxfs_immed_dirblk
r_struct
id|vxfs_immed_dirblk
(brace
DECL|member|d_free
id|u_int16_t
id|d_free
suffix:semicolon
DECL|member|d_nhash
id|u_int16_t
id|d_nhash
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * VxFS directory entry.&n; */
DECL|macro|VXFS_NAME_LEN
mdefine_line|#define VXFS_NAME_LEN&t;256
DECL|struct|vxfs_direct
r_struct
id|vxfs_direct
(brace
DECL|member|d_ino
id|vx_ino_t
id|d_ino
suffix:semicolon
DECL|member|d_reclen
id|u_int16_t
id|d_reclen
suffix:semicolon
DECL|member|d_namelen
id|u_int16_t
id|d_namelen
suffix:semicolon
DECL|member|d_hashnext
id|u_int16_t
id|d_hashnext
suffix:semicolon
DECL|member|d_name
r_char
id|d_name
(braket
id|VXFS_NAME_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _VXFS_DIR_H_ */
eof
