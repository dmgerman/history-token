multiline_comment|/*&n; * Copyright (c) 2000-2001 Christoph Hellwig.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
macro_line|#ifndef _VXFS_OLT_H_
DECL|macro|_VXFS_OLT_H_
mdefine_line|#define _VXFS_OLT_H_
macro_line|#ident &quot;$Id: vxfs_olt.h,v 1.5 2001/04/25 18:11:23 hch Exp hch $&quot;
multiline_comment|/*&n; * Veritas filesystem driver - Object Location Table data structures.&n; *&n; * This file contains definitions for the Object Location Table used&n; * by the Veritas Filesystem version 2 and newer.&n; */
multiline_comment|/*&n; * OLT magic number (vxfs_olt-&gt;olt_magic).&n; */
DECL|macro|VXFS_OLT_MAGIC
mdefine_line|#define VXFS_OLT_MAGIC&t;&t;0xa504FCF5
multiline_comment|/*&n; * VxFS OLT entry types.&n; */
r_enum
(brace
DECL|enumerator|VXFS_OLT_FREE
id|VXFS_OLT_FREE
op_assign
l_int|1
comma
DECL|enumerator|VXFS_OLT_FSHEAD
id|VXFS_OLT_FSHEAD
op_assign
l_int|2
comma
DECL|enumerator|VXFS_OLT_CUT
id|VXFS_OLT_CUT
op_assign
l_int|3
comma
DECL|enumerator|VXFS_OLT_ILIST
id|VXFS_OLT_ILIST
op_assign
l_int|4
comma
DECL|enumerator|VXFS_OLT_DEV
id|VXFS_OLT_DEV
op_assign
l_int|5
comma
DECL|enumerator|VXFS_OLT_SB
id|VXFS_OLT_SB
op_assign
l_int|6
)brace
suffix:semicolon
multiline_comment|/*&n; * VxFS OLT header.&n; *&n; * The Object Location Table header is placed at the beginning of each&n; * OLT extent.  It is used to fing certain filesystem-wide metadata, e.g.&n; * the inital inode list, the fileset header or the device configuration.&n; */
DECL|struct|vxfs_olt
r_struct
id|vxfs_olt
(brace
DECL|member|olt_magic
id|u_int32_t
id|olt_magic
suffix:semicolon
multiline_comment|/* magic number&t;&t;&t;*/
DECL|member|olt_size
id|u_int32_t
id|olt_size
suffix:semicolon
multiline_comment|/* size of this entry&t;&t;*/
DECL|member|olt_checksum
id|u_int32_t
id|olt_checksum
suffix:semicolon
multiline_comment|/* checksum of extent&t;&t;*/
DECL|member|__unused1
id|u_int32_t
id|__unused1
suffix:semicolon
multiline_comment|/* ???&t;&t;&t;&t;*/
DECL|member|olt_mtime
id|u_int32_t
id|olt_mtime
suffix:semicolon
multiline_comment|/* time of last mod. (sec)&t;*/
DECL|member|olt_mutime
id|u_int32_t
id|olt_mutime
suffix:semicolon
multiline_comment|/* time of last mod. (usec)&t;*/
DECL|member|olt_totfree
id|u_int32_t
id|olt_totfree
suffix:semicolon
multiline_comment|/* free space in OLT extent&t;*/
DECL|member|olt_extents
id|vx_daddr_t
id|olt_extents
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* addr of this extent, replica&t;*/
DECL|member|olt_esize
id|u_int32_t
id|olt_esize
suffix:semicolon
multiline_comment|/* size of this extent&t;&t;*/
DECL|member|olt_next
id|vx_daddr_t
id|olt_next
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* addr of next extent, replica&t;*/
DECL|member|olt_nsize
id|u_int32_t
id|olt_nsize
suffix:semicolon
multiline_comment|/* size of next extent&t;&t;*/
DECL|member|__unused2
id|u_int32_t
id|__unused2
suffix:semicolon
multiline_comment|/* align to 8 byte boundary&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * VxFS common OLT entry (on disk).&n; */
DECL|struct|vxfs_oltcommon
r_struct
id|vxfs_oltcommon
(brace
DECL|member|olt_type
id|u_int32_t
id|olt_type
suffix:semicolon
multiline_comment|/* type of this record&t;&t;*/
DECL|member|olt_size
id|u_int32_t
id|olt_size
suffix:semicolon
multiline_comment|/* size of this record&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * VxFS free OLT entry (on disk).&n; */
DECL|struct|vxfs_oltfree
r_struct
id|vxfs_oltfree
(brace
DECL|member|olt_type
id|u_int32_t
id|olt_type
suffix:semicolon
multiline_comment|/* type of this record&t;&t;*/
DECL|member|olt_fsize
id|u_int32_t
id|olt_fsize
suffix:semicolon
multiline_comment|/* size of this free record&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * VxFS initial-inode list (on disk).&n; */
DECL|struct|vxfs_oltilist
r_struct
id|vxfs_oltilist
(brace
DECL|member|olt_type
id|u_int32_t
id|olt_type
suffix:semicolon
multiline_comment|/* type of this record&t;&t;*/
DECL|member|olt_size
id|u_int32_t
id|olt_size
suffix:semicolon
multiline_comment|/* size of this record&t;&t;*/
DECL|member|olt_iext
id|vx_ino_t
id|olt_iext
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* initial inode list, replica&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * Current Usage Table &n; */
DECL|struct|vxfs_oltcut
r_struct
id|vxfs_oltcut
(brace
DECL|member|olt_type
id|u_int32_t
id|olt_type
suffix:semicolon
multiline_comment|/* type of this record&t;&t;*/
DECL|member|olt_size
id|u_int32_t
id|olt_size
suffix:semicolon
multiline_comment|/* size of this record&t;&t;*/
DECL|member|olt_cutino
id|vx_ino_t
id|olt_cutino
suffix:semicolon
multiline_comment|/* inode of current usage table&t;*/
DECL|member|__pad
id|u_int32_t
id|__pad
suffix:semicolon
multiline_comment|/* unused, 8 byte align&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * Inodes containing Superblock, Intent log and OLTs &n; */
DECL|struct|vxfs_oltsb
r_struct
id|vxfs_oltsb
(brace
DECL|member|olt_type
id|u_int32_t
id|olt_type
suffix:semicolon
multiline_comment|/* type of this record&t;&t;*/
DECL|member|olt_size
id|u_int32_t
id|olt_size
suffix:semicolon
multiline_comment|/* size of this record&t;&t;*/
DECL|member|olt_sbino
id|vx_ino_t
id|olt_sbino
suffix:semicolon
multiline_comment|/* inode of superblock file&t;*/
DECL|member|__unused1
id|u_int32_t
id|__unused1
suffix:semicolon
multiline_comment|/* ???&t;&t;&t;&t;*/
DECL|member|olt_logino
id|vx_ino_t
id|olt_logino
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* inode of log file,replica&t;*/
DECL|member|olt_oltino
id|vx_ino_t
id|olt_oltino
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* inode of OLT, replica&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * Inode containing device configuration + it&squot;s replica &n; */
DECL|struct|vxfs_oltdev
r_struct
id|vxfs_oltdev
(brace
DECL|member|olt_type
id|u_int32_t
id|olt_type
suffix:semicolon
multiline_comment|/* type of this record&t;&t;*/
DECL|member|olt_size
id|u_int32_t
id|olt_size
suffix:semicolon
multiline_comment|/* size of this record&t;&t;*/
DECL|member|olt_devino
id|vx_ino_t
id|olt_devino
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* inode of device config files&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * Fileset header &n; */
DECL|struct|vxfs_oltfshead
r_struct
id|vxfs_oltfshead
(brace
DECL|member|olt_type
id|u_int32_t
id|olt_type
suffix:semicolon
multiline_comment|/* type number&t;&t;&t;*/
DECL|member|olt_size
id|u_int32_t
id|olt_size
suffix:semicolon
multiline_comment|/* size of this record&t;&t;*/
DECL|member|olt_fsino
id|vx_ino_t
id|olt_fsino
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* inodes of fileset header&t;*/
)brace
suffix:semicolon
macro_line|#endif /* _VXFS_OLT_H_ */
eof
