multiline_comment|/*&n; * Copyright (c) 2000-2001 Christoph Hellwig.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
macro_line|#ifndef _VXFS_INODE_H_
DECL|macro|_VXFS_INODE_H_
mdefine_line|#define _VXFS_INODE_H_
macro_line|#ident &quot;$Id: vxfs_inode.h,v 1.13 2001/04/24 19:28:36 hch Exp hch $&quot;
multiline_comment|/*&n; * Veritas filesystem driver - inode structure.&n; *&n; * This file contains the definition of the disk and core&n; * inodes of the Veritas Filesystem.&n; */
DECL|macro|VXFS_ISIZE
mdefine_line|#define VXFS_ISIZE&t;&t;0x100&t;&t;/* Inode size */
DECL|macro|VXFS_NDADDR
mdefine_line|#define VXFS_NDADDR&t;&t;10&t;&t;/* Number of direct addrs in inode */
DECL|macro|VXFS_NIADDR
mdefine_line|#define VXFS_NIADDR&t;&t;2&t;&t;/* Number of indirect addrs in inode */
DECL|macro|VXFS_NIMMED
mdefine_line|#define VXFS_NIMMED&t;&t;96&t;&t;/* Size of immediate data in inode */
DECL|macro|VXFS_NTYPED
mdefine_line|#define VXFS_NTYPED&t;&t;6&t;&t;/* Num of typed extents */
DECL|macro|VXFS_TYPED_OFFSETMASK
mdefine_line|#define VXFS_TYPED_OFFSETMASK&t;(0x00FFFFFFFFFFFFFFULL)
DECL|macro|VXFS_TYPED_TYPEMASK
mdefine_line|#define VXFS_TYPED_TYPEMASK&t;(0xFF00000000000000ULL)
DECL|macro|VXFS_TYPED_TYPESHIFT
mdefine_line|#define VXFS_TYPED_TYPESHIFT&t;56
DECL|macro|VXFS_TYPED_PER_BLOCK
mdefine_line|#define VXFS_TYPED_PER_BLOCK(sbp) &bslash;&n;&t;((sbp)-&gt;s_blocksize / sizeof(struct vxfs_typed))
multiline_comment|/*&n; * Possible extent descriptor types for %VXFS_ORG_TYPED extents.&n; */
r_enum
(brace
DECL|enumerator|VXFS_TYPED_INDIRECT
id|VXFS_TYPED_INDIRECT
op_assign
l_int|1
comma
DECL|enumerator|VXFS_TYPED_DATA
id|VXFS_TYPED_DATA
op_assign
l_int|2
comma
DECL|enumerator|VXFS_TYPED_INDIRECT_DEV4
id|VXFS_TYPED_INDIRECT_DEV4
op_assign
l_int|3
comma
DECL|enumerator|VXFS_TYPED_DATA_DEV4
id|VXFS_TYPED_DATA_DEV4
op_assign
l_int|4
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Data stored immediately in the inode.&n; */
DECL|struct|vxfs_immed
r_struct
id|vxfs_immed
(brace
DECL|member|vi_immed
id|u_int8_t
id|vi_immed
(braket
id|VXFS_NIMMED
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vxfs_ext4
r_struct
id|vxfs_ext4
(brace
DECL|member|ve4_spare
id|u_int32_t
id|ve4_spare
suffix:semicolon
multiline_comment|/* ?? */
DECL|member|ve4_indsize
id|u_int32_t
id|ve4_indsize
suffix:semicolon
multiline_comment|/* Indirect extent size */
DECL|member|ve4_indir
id|vx_daddr_t
id|ve4_indir
(braket
id|VXFS_NIADDR
)braket
suffix:semicolon
multiline_comment|/* Indirect extents */
DECL|struct|direct
r_struct
id|direct
(brace
multiline_comment|/* Direct extents */
DECL|member|extent
id|vx_daddr_t
id|extent
suffix:semicolon
multiline_comment|/* Extent number */
DECL|member|size
id|u_int32_t
id|size
suffix:semicolon
multiline_comment|/* Size of extent */
DECL|member|ve4_direct
)brace
id|ve4_direct
(braket
id|VXFS_NDADDR
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vxfs_typed
r_struct
id|vxfs_typed
(brace
DECL|member|vt_hdr
id|u_int64_t
id|vt_hdr
suffix:semicolon
multiline_comment|/* Header, 0xTTOOOOOOOOOOOOOO; T=type,O=offs */
DECL|member|vt_block
id|vx_daddr_t
id|vt_block
suffix:semicolon
multiline_comment|/* Extent block */
DECL|member|vt_size
r_int32
id|vt_size
suffix:semicolon
multiline_comment|/* Size in blocks */
)brace
suffix:semicolon
DECL|struct|vxfs_typed_dev4
r_struct
id|vxfs_typed_dev4
(brace
DECL|member|vd4_hdr
id|u_int64_t
id|vd4_hdr
suffix:semicolon
multiline_comment|/* Header, 0xTTOOOOOOOOOOOOOO; T=type,O=offs */
DECL|member|vd4_block
id|u_int64_t
id|vd4_block
suffix:semicolon
multiline_comment|/* Extent block */
DECL|member|vd4_size
id|u_int64_t
id|vd4_size
suffix:semicolon
multiline_comment|/* Size in blocks */
DECL|member|vd4_dev
r_int32
id|vd4_dev
suffix:semicolon
multiline_comment|/* Device ID */
DECL|member|__pad1
id|u_int32_t
id|__pad1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The inode as contained on the physical device.&n; */
DECL|struct|vxfs_dinode
r_struct
id|vxfs_dinode
(brace
DECL|member|vdi_mode
r_int32
id|vdi_mode
suffix:semicolon
DECL|member|vdi_nlink
id|u_int32_t
id|vdi_nlink
suffix:semicolon
multiline_comment|/* Link count */
DECL|member|vdi_uid
id|u_int32_t
id|vdi_uid
suffix:semicolon
multiline_comment|/* UID */
DECL|member|vdi_gid
id|u_int32_t
id|vdi_gid
suffix:semicolon
multiline_comment|/* GID */
DECL|member|vdi_size
id|u_int64_t
id|vdi_size
suffix:semicolon
multiline_comment|/* Inode size in bytes */
DECL|member|vdi_atime
id|u_int32_t
id|vdi_atime
suffix:semicolon
multiline_comment|/* Last time accessed - sec */
DECL|member|vdi_autime
id|u_int32_t
id|vdi_autime
suffix:semicolon
multiline_comment|/* Last time accessed - usec */
DECL|member|vdi_mtime
id|u_int32_t
id|vdi_mtime
suffix:semicolon
multiline_comment|/* Last modify time - sec */
DECL|member|vdi_mutime
id|u_int32_t
id|vdi_mutime
suffix:semicolon
multiline_comment|/* Last modify time - usec */
DECL|member|vdi_ctime
id|u_int32_t
id|vdi_ctime
suffix:semicolon
multiline_comment|/* Create time - sec */
DECL|member|vdi_cutime
id|u_int32_t
id|vdi_cutime
suffix:semicolon
multiline_comment|/* Create time - usec */
DECL|member|vdi_aflags
id|u_int8_t
id|vdi_aflags
suffix:semicolon
multiline_comment|/* Allocation flags */
DECL|member|vdi_orgtype
id|u_int8_t
id|vdi_orgtype
suffix:semicolon
multiline_comment|/* Organisation type */
DECL|member|vdi_eopflags
id|u_int16_t
id|vdi_eopflags
suffix:semicolon
DECL|member|vdi_eopdata
id|u_int32_t
id|vdi_eopdata
suffix:semicolon
r_union
(brace
DECL|member|rdev
id|u_int32_t
id|rdev
suffix:semicolon
DECL|member|dotdot
id|u_int32_t
id|dotdot
suffix:semicolon
r_struct
(brace
DECL|member|reserved
id|u_int32_t
id|reserved
suffix:semicolon
DECL|member|fixextsize
id|u_int32_t
id|fixextsize
suffix:semicolon
DECL|member|i_regular
)brace
id|i_regular
suffix:semicolon
r_struct
(brace
DECL|member|matchino
id|u_int32_t
id|matchino
suffix:semicolon
DECL|member|fsetindex
id|u_int32_t
id|fsetindex
suffix:semicolon
DECL|member|i_vxspec
)brace
id|i_vxspec
suffix:semicolon
DECL|member|align
id|u_int64_t
id|align
suffix:semicolon
DECL|member|vdi_ftarea
)brace
id|vdi_ftarea
suffix:semicolon
DECL|member|vdi_blocks
id|u_int32_t
id|vdi_blocks
suffix:semicolon
multiline_comment|/* How much blocks does inode occupy */
DECL|member|vdi_gen
id|u_int32_t
id|vdi_gen
suffix:semicolon
multiline_comment|/* Inode generation */
DECL|member|vdi_version
id|u_int64_t
id|vdi_version
suffix:semicolon
multiline_comment|/* Version */
r_union
(brace
DECL|member|immed
r_struct
id|vxfs_immed
id|immed
suffix:semicolon
DECL|member|ext4
r_struct
id|vxfs_ext4
id|ext4
suffix:semicolon
DECL|member|typed
r_struct
id|vxfs_typed
id|typed
(braket
id|VXFS_NTYPED
)braket
suffix:semicolon
DECL|member|vdi_org
)brace
id|vdi_org
suffix:semicolon
DECL|member|vdi_iattrino
id|u_int32_t
id|vdi_iattrino
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|vdi_rdev
mdefine_line|#define vdi_rdev&t;vdi_ftarea.rdev
DECL|macro|vdi_dotdot
mdefine_line|#define vdi_dotdot&t;vdi_ftarea.dotdot
DECL|macro|vdi_fixextsize
mdefine_line|#define vdi_fixextsize&t;vdi_ftarea.regular.fixextsize
DECL|macro|vdi_matchino
mdefine_line|#define vdi_matchino&t;vdi_ftarea.vxspec.matchino
DECL|macro|vdi_fsetindex
mdefine_line|#define vdi_fsetindex&t;vdi_ftarea.vxspec.fsetindex
DECL|macro|vdi_immed
mdefine_line|#define vdi_immed&t;vdi_org.immed
DECL|macro|vdi_ext4
mdefine_line|#define vdi_ext4&t;vdi_org.ext4
DECL|macro|vdi_typed
mdefine_line|#define vdi_typed&t;vdi_org.typed
multiline_comment|/*&n; * The inode as represented in the main memory.&n; *&n; * TBD: This should become a separate structure...&n; */
DECL|macro|vxfs_inode_info
mdefine_line|#define vxfs_inode_info&t;vxfs_dinode
DECL|macro|vii_mode
mdefine_line|#define vii_mode&t;vdi_mode
DECL|macro|vii_uid
mdefine_line|#define vii_uid&t;&t;vdi_uid
DECL|macro|vii_gid
mdefine_line|#define vii_gid&t;&t;vdi_gid
DECL|macro|vii_nlink
mdefine_line|#define vii_nlink&t;vdi_nlink
DECL|macro|vii_size
mdefine_line|#define vii_size&t;vdi_size
DECL|macro|vii_atime
mdefine_line|#define vii_atime&t;vdi_atime
DECL|macro|vii_ctime
mdefine_line|#define vii_ctime&t;vdi_ctime
DECL|macro|vii_mtime
mdefine_line|#define vii_mtime&t;vdi_mtime
DECL|macro|vii_blocks
mdefine_line|#define vii_blocks&t;vdi_blocks
DECL|macro|vii_org
mdefine_line|#define vii_org&t;&t;vdi_org
DECL|macro|vii_orgtype
mdefine_line|#define vii_orgtype&t;vdi_orgtype
DECL|macro|vii_gen
mdefine_line|#define vii_gen&t;&t;vdi_gen
DECL|macro|vii_rdev
mdefine_line|#define vii_rdev&t;vdi_ftarea.rdev
DECL|macro|vii_dotdot
mdefine_line|#define vii_dotdot&t;vdi_ftarea.dotdot
DECL|macro|vii_fixextsize
mdefine_line|#define vii_fixextsize&t;vdi_ftarea.regular.fixextsize
DECL|macro|vii_matchino
mdefine_line|#define vii_matchino&t;vdi_ftarea.vxspec.matchino
DECL|macro|vii_fsetindex
mdefine_line|#define vii_fsetindex&t;vdi_ftarea.vxspec.fsetindex
DECL|macro|vii_immed
mdefine_line|#define vii_immed&t;vdi_org.immed
DECL|macro|vii_ext4
mdefine_line|#define vii_ext4&t;vdi_org.ext4
DECL|macro|vii_typed
mdefine_line|#define vii_typed&t;vdi_org.typed
macro_line|#endif /* _VXFS_INODE_H_ */
eof
