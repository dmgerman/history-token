multiline_comment|/*&n; * Copyright (c) 2000-2001 Christoph Hellwig.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
macro_line|#ifndef _VXFS_DIR_H_
DECL|macro|_VXFS_DIR_H_
mdefine_line|#define _VXFS_DIR_H_
macro_line|#ident &quot;$Id: vxfs_dir.h,v 1.7 2001/05/21 15:48:26 hch Exp hch $&quot;
multiline_comment|/*&n; * Veritas filesystem driver - directory structure.&n; *&n; * This file contains the definition of the vxfs directory format.&n; */
multiline_comment|/*&n; * VxFS directory block header.&n; *&n; * This entry is the head of every filesystem block in a directory.&n; * It is used for free space managment and additionally includes&n; * a hash for speeding up directory search (lookup).&n; *&n; * The hash may be empty and in fact we do not use it all in the&n; * Linux driver for now.&n; */
DECL|struct|vxfs_dirblk
r_struct
id|vxfs_dirblk
(brace
DECL|member|d_free
id|u_int16_t
id|d_free
suffix:semicolon
multiline_comment|/* free space in dirblock */
DECL|member|d_nhash
id|u_int16_t
id|d_nhash
suffix:semicolon
multiline_comment|/* no of hash chains */
DECL|member|d_hash
id|u_int16_t
id|d_hash
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* hash chain */
)brace
suffix:semicolon
multiline_comment|/*&n; * VXFS_NAMELEN is the maximum length of the d_name field&n; *&t;of an VxFS directory entry.&n; */
DECL|macro|VXFS_NAMELEN
mdefine_line|#define VXFS_NAMELEN&t;256
multiline_comment|/*&n; * VxFS directory entry.&n; */
DECL|struct|vxfs_direct
r_struct
id|vxfs_direct
(brace
DECL|member|d_ino
id|vx_ino_t
id|d_ino
suffix:semicolon
multiline_comment|/* inode number */
DECL|member|d_reclen
id|u_int16_t
id|d_reclen
suffix:semicolon
multiline_comment|/* record length */
DECL|member|d_namelen
id|u_int16_t
id|d_namelen
suffix:semicolon
multiline_comment|/* d_name length */
DECL|member|d_hashnext
id|u_int16_t
id|d_hashnext
suffix:semicolon
multiline_comment|/* next hash entry */
DECL|member|d_name
r_char
id|d_name
(braket
id|VXFS_NAMELEN
)braket
suffix:semicolon
multiline_comment|/* name */
)brace
suffix:semicolon
multiline_comment|/*&n; * VXFS_DIRPAD defines the directory entry boundaries, is _must_ be&n; *&t;a multiple of four.&n; * VXFS_NAMEMIN is the length of a directory entry with a NULL d_name.&n; * VXFS_DIRROUND is an internal macros that rounds a length to a value&n; *&t;usable for directory sizes.&n; * VXFS_DIRLEN calculates the directory entry size for an entry with&n; *&t;a d_name with size len.&n; */
DECL|macro|VXFS_DIRPAD
mdefine_line|#define VXFS_DIRPAD&t;&t;4
DECL|macro|VXFS_NAMEMIN
mdefine_line|#define VXFS_NAMEMIN&t;&t;((int)((struct vxfs_direct *)0)-&gt;d_name)
DECL|macro|VXFS_DIRROUND
mdefine_line|#define VXFS_DIRROUND(len)&t;((VXFS_DIRPAD + (len) - 1) &amp; ~(VXFS_DIRPAD -1))
DECL|macro|VXFS_DIRLEN
mdefine_line|#define VXFS_DIRLEN(len)&t;(VXFS_DIRROUND(VXFS_NAMEMIN + (len)))
multiline_comment|/*&n; * VXFS_DIRBLKOV is the overhead of a specific dirblock.&n; */
DECL|macro|VXFS_DIRBLKOV
mdefine_line|#define VXFS_DIRBLKOV(dbp)&t;((sizeof(short) * dbp-&gt;d_nhash) + 4)
macro_line|#endif /* _VXFS_DIR_H_ */
eof
