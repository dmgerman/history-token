multiline_comment|/*&n; * Copyright (c) 2000-2001 Christoph Hellwig.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
macro_line|#ifndef _VXFS_SUPER_H_
DECL|macro|_VXFS_SUPER_H_
mdefine_line|#define _VXFS_SUPER_H_
macro_line|#ident &quot;$Id: vxfs.h 1.12 2001/12/28 19:48:03 hch Exp $&quot;
multiline_comment|/*&n; * Veritas filesystem driver - superblock structure.&n; *&n; * This file contains the definition of the disk and core&n; * superblocks of the Veritas Filesystem.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &quot;vxfs_kcompat.h&quot;
multiline_comment|/*&n; * Data types for use with the VxFS ondisk format.&n; */
DECL|typedef|vx_daddr_t
r_typedef
r_int32
id|vx_daddr_t
suffix:semicolon
DECL|typedef|vx_ino_t
r_typedef
r_int32
id|vx_ino_t
suffix:semicolon
multiline_comment|/*&n; * Superblock magic number (vxfs_super-&gt;vs_magic).&n; */
DECL|macro|VXFS_SUPER_MAGIC
mdefine_line|#define VXFS_SUPER_MAGIC&t;0xa501FCF5
multiline_comment|/*&n; * The root inode.&n; */
DECL|macro|VXFS_ROOT_INO
mdefine_line|#define VXFS_ROOT_INO&t;&t;2
multiline_comment|/*&n; * Num of entries in free extent array&n; */
DECL|macro|VXFS_NEFREE
mdefine_line|#define VXFS_NEFREE&t;&t;32
multiline_comment|/*&n; * VxFS superblock (disk).&n; */
DECL|struct|vxfs_sb
r_struct
id|vxfs_sb
(brace
multiline_comment|/*&n;&t; * Readonly fields for the version 1 superblock.&n;&t; *&n;&t; * Lots of this fields are no more used by version 2&n;&t; * and never filesystems.&n;&t; */
DECL|member|vs_magic
id|u_int32_t
id|vs_magic
suffix:semicolon
multiline_comment|/* Magic number */
DECL|member|vs_version
r_int32
id|vs_version
suffix:semicolon
multiline_comment|/* VxFS version */
DECL|member|vs_ctime
id|u_int32_t
id|vs_ctime
suffix:semicolon
multiline_comment|/* create time - secs */
DECL|member|vs_cutime
id|u_int32_t
id|vs_cutime
suffix:semicolon
multiline_comment|/* create time - usecs */
DECL|member|__unused1
r_int32
id|__unused1
suffix:semicolon
multiline_comment|/* unused */
DECL|member|__unused2
r_int32
id|__unused2
suffix:semicolon
multiline_comment|/* unused */
DECL|member|vs_old_logstart
id|vx_daddr_t
id|vs_old_logstart
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|vs_old_logend
id|vx_daddr_t
id|vs_old_logend
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|vs_bsize
r_int32
id|vs_bsize
suffix:semicolon
multiline_comment|/* block size */
DECL|member|vs_size
r_int32
id|vs_size
suffix:semicolon
multiline_comment|/* number of blocks */
DECL|member|vs_dsize
r_int32
id|vs_dsize
suffix:semicolon
multiline_comment|/* number of data blocks */
DECL|member|vs_old_ninode
id|u_int32_t
id|vs_old_ninode
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|vs_old_nau
r_int32
id|vs_old_nau
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|__unused3
r_int32
id|__unused3
suffix:semicolon
multiline_comment|/* unused */
DECL|member|vs_old_defiextsize
r_int32
id|vs_old_defiextsize
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|vs_old_ilbsize
r_int32
id|vs_old_ilbsize
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|vs_immedlen
r_int32
id|vs_immedlen
suffix:semicolon
multiline_comment|/* size of immediate data area */
DECL|member|vs_ndaddr
r_int32
id|vs_ndaddr
suffix:semicolon
multiline_comment|/* number of direct extentes */
DECL|member|vs_firstau
id|vx_daddr_t
id|vs_firstau
suffix:semicolon
multiline_comment|/* address of first AU */
DECL|member|vs_emap
id|vx_daddr_t
id|vs_emap
suffix:semicolon
multiline_comment|/* offset of extent map in AU */
DECL|member|vs_imap
id|vx_daddr_t
id|vs_imap
suffix:semicolon
multiline_comment|/* offset of inode map in AU */
DECL|member|vs_iextop
id|vx_daddr_t
id|vs_iextop
suffix:semicolon
multiline_comment|/* offset of ExtOp. map in AU */
DECL|member|vs_istart
id|vx_daddr_t
id|vs_istart
suffix:semicolon
multiline_comment|/* offset of inode list in AU */
DECL|member|vs_bstart
id|vx_daddr_t
id|vs_bstart
suffix:semicolon
multiline_comment|/* offset of fdblock in AU */
DECL|member|vs_femap
id|vx_daddr_t
id|vs_femap
suffix:semicolon
multiline_comment|/* aufirst + emap */
DECL|member|vs_fimap
id|vx_daddr_t
id|vs_fimap
suffix:semicolon
multiline_comment|/* aufirst + imap */
DECL|member|vs_fiextop
id|vx_daddr_t
id|vs_fiextop
suffix:semicolon
multiline_comment|/* aufirst + iextop */
DECL|member|vs_fistart
id|vx_daddr_t
id|vs_fistart
suffix:semicolon
multiline_comment|/* aufirst + istart */
DECL|member|vs_fbstart
id|vx_daddr_t
id|vs_fbstart
suffix:semicolon
multiline_comment|/* aufirst + bstart */
DECL|member|vs_nindir
r_int32
id|vs_nindir
suffix:semicolon
multiline_comment|/* number of entries in indir */
DECL|member|vs_aulen
r_int32
id|vs_aulen
suffix:semicolon
multiline_comment|/* length of AU in blocks */
DECL|member|vs_auimlen
r_int32
id|vs_auimlen
suffix:semicolon
multiline_comment|/* length of imap in blocks */
DECL|member|vs_auemlen
r_int32
id|vs_auemlen
suffix:semicolon
multiline_comment|/* length of emap in blocks */
DECL|member|vs_auilen
r_int32
id|vs_auilen
suffix:semicolon
multiline_comment|/* length of ilist in blocks */
DECL|member|vs_aupad
r_int32
id|vs_aupad
suffix:semicolon
multiline_comment|/* length of pad in blocks */
DECL|member|vs_aublocks
r_int32
id|vs_aublocks
suffix:semicolon
multiline_comment|/* data blocks in AU */
DECL|member|vs_maxtier
r_int32
id|vs_maxtier
suffix:semicolon
multiline_comment|/* log base 2 of aublocks */
DECL|member|vs_inopb
r_int32
id|vs_inopb
suffix:semicolon
multiline_comment|/* number of inodes per blk */
DECL|member|vs_old_inopau
r_int32
id|vs_old_inopau
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|vs_old_inopilb
r_int32
id|vs_old_inopilb
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|vs_old_ndiripau
r_int32
id|vs_old_ndiripau
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|vs_iaddrlen
r_int32
id|vs_iaddrlen
suffix:semicolon
multiline_comment|/* size of indirect addr ext. */
DECL|member|vs_bshift
r_int32
id|vs_bshift
suffix:semicolon
multiline_comment|/* log base 2 of bsize */
DECL|member|vs_inoshift
r_int32
id|vs_inoshift
suffix:semicolon
multiline_comment|/* log base 2 of inobp */
DECL|member|vs_bmask
r_int32
id|vs_bmask
suffix:semicolon
multiline_comment|/* ~( bsize - 1 ) */
DECL|member|vs_boffmask
r_int32
id|vs_boffmask
suffix:semicolon
multiline_comment|/* bsize - 1 */
DECL|member|vs_old_inomask
r_int32
id|vs_old_inomask
suffix:semicolon
multiline_comment|/* old_inopilb - 1 */
DECL|member|vs_checksum
r_int32
id|vs_checksum
suffix:semicolon
multiline_comment|/* checksum of V1 data */
multiline_comment|/*&n;&t; * Version 1, writable&n;&t; */
DECL|member|vs_free
r_int32
id|vs_free
suffix:semicolon
multiline_comment|/* number of free blocks */
DECL|member|vs_ifree
r_int32
id|vs_ifree
suffix:semicolon
multiline_comment|/* number of free inodes */
DECL|member|vs_efree
r_int32
id|vs_efree
(braket
id|VXFS_NEFREE
)braket
suffix:semicolon
multiline_comment|/* number of free extents by size */
DECL|member|vs_flags
r_int32
id|vs_flags
suffix:semicolon
multiline_comment|/* flags ?!? */
DECL|member|vs_mod
id|u_int8_t
id|vs_mod
suffix:semicolon
multiline_comment|/* filesystem has been changed */
DECL|member|vs_clean
id|u_int8_t
id|vs_clean
suffix:semicolon
multiline_comment|/* clean FS */
DECL|member|__unused4
id|u_int16_t
id|__unused4
suffix:semicolon
multiline_comment|/* unused */
DECL|member|vs_firstlogid
id|u_int32_t
id|vs_firstlogid
suffix:semicolon
multiline_comment|/* mount time log ID */
DECL|member|vs_wtime
id|u_int32_t
id|vs_wtime
suffix:semicolon
multiline_comment|/* last time written - sec */
DECL|member|vs_wutime
id|u_int32_t
id|vs_wutime
suffix:semicolon
multiline_comment|/* last time written - usec */
DECL|member|vs_fname
id|u_int8_t
id|vs_fname
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* FS name */
DECL|member|vs_fpack
id|u_int8_t
id|vs_fpack
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* FS pack name */
DECL|member|vs_logversion
r_int32
id|vs_logversion
suffix:semicolon
multiline_comment|/* log format version */
DECL|member|__unused5
r_int32
id|__unused5
suffix:semicolon
multiline_comment|/* unused */
multiline_comment|/*&n;&t; * Version 2, Read-only&n;&t; */
DECL|member|vs_oltext
id|vx_daddr_t
id|vs_oltext
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* OLT extent and replica */
DECL|member|vs_oltsize
r_int32
id|vs_oltsize
suffix:semicolon
multiline_comment|/* OLT extent size */
DECL|member|vs_iauimlen
r_int32
id|vs_iauimlen
suffix:semicolon
multiline_comment|/* size of inode map */
DECL|member|vs_iausize
r_int32
id|vs_iausize
suffix:semicolon
multiline_comment|/* size of IAU in blocks */
DECL|member|vs_dinosize
r_int32
id|vs_dinosize
suffix:semicolon
multiline_comment|/* size of inode in bytes */
DECL|member|vs_old_dniaddr
r_int32
id|vs_old_dniaddr
suffix:semicolon
multiline_comment|/* indir levels per inode */
DECL|member|vs_checksum2
r_int32
id|vs_checksum2
suffix:semicolon
multiline_comment|/* checksum of V2 RO */
multiline_comment|/*&n;&t; * Actually much more...&n;&t; */
)brace
suffix:semicolon
multiline_comment|/*&n; * In core superblock filesystem private data for VxFS.&n; */
DECL|struct|vxfs_sb_info
r_struct
id|vxfs_sb_info
(brace
DECL|member|vsi_raw
r_struct
id|vxfs_sb
op_star
id|vsi_raw
suffix:semicolon
multiline_comment|/* raw (on disk) supeblock */
DECL|member|vsi_bp
r_struct
id|buffer_head
op_star
id|vsi_bp
suffix:semicolon
multiline_comment|/* buffer for raw superblock*/
DECL|member|vsi_fship
r_struct
id|inode
op_star
id|vsi_fship
suffix:semicolon
multiline_comment|/* fileset header inode */
DECL|member|vsi_ilist
r_struct
id|inode
op_star
id|vsi_ilist
suffix:semicolon
multiline_comment|/* inode list inode */
DECL|member|vsi_stilist
r_struct
id|inode
op_star
id|vsi_stilist
suffix:semicolon
multiline_comment|/* structual inode list inode */
DECL|member|vsi_iext
id|u_long
id|vsi_iext
suffix:semicolon
multiline_comment|/* initial inode list */
DECL|member|vsi_fshino
id|ino_t
id|vsi_fshino
suffix:semicolon
multiline_comment|/* fileset header inode */
DECL|member|vsi_oltext
id|daddr_t
id|vsi_oltext
suffix:semicolon
multiline_comment|/* OLT extent */
DECL|member|vsi_oltsize
id|daddr_t
id|vsi_oltsize
suffix:semicolon
multiline_comment|/* OLT size */
)brace
suffix:semicolon
multiline_comment|/*&n; * File modes.  File types above 0xf000 are vxfs internal only, they should&n; * not be passed back to higher levels of the system.  vxfs file types must&n; * never have one of the regular file type bits set.&n; */
DECL|enum|vxfs_mode
r_enum
id|vxfs_mode
(brace
DECL|enumerator|VXFS_ISUID
id|VXFS_ISUID
op_assign
l_int|0x00000800
comma
multiline_comment|/* setuid */
DECL|enumerator|VXFS_ISGID
id|VXFS_ISGID
op_assign
l_int|0x00000400
comma
multiline_comment|/* setgid */
DECL|enumerator|VXFS_ISVTX
id|VXFS_ISVTX
op_assign
l_int|0x00000200
comma
multiline_comment|/* sticky bit */
DECL|enumerator|VXFS_IREAD
id|VXFS_IREAD
op_assign
l_int|0x00000100
comma
multiline_comment|/* read */
DECL|enumerator|VXFS_IWRITE
id|VXFS_IWRITE
op_assign
l_int|0x00000080
comma
multiline_comment|/* write */
DECL|enumerator|VXFS_IEXEC
id|VXFS_IEXEC
op_assign
l_int|0x00000040
comma
multiline_comment|/* exec */
DECL|enumerator|VXFS_IFIFO
id|VXFS_IFIFO
op_assign
l_int|0x00001000
comma
multiline_comment|/* Named pipe */
DECL|enumerator|VXFS_IFCHR
id|VXFS_IFCHR
op_assign
l_int|0x00002000
comma
multiline_comment|/* Character device */
DECL|enumerator|VXFS_IFDIR
id|VXFS_IFDIR
op_assign
l_int|0x00004000
comma
multiline_comment|/* Directory */
DECL|enumerator|VXFS_IFNAM
id|VXFS_IFNAM
op_assign
l_int|0x00005000
comma
multiline_comment|/* Xenix device ?? */
DECL|enumerator|VXFS_IFBLK
id|VXFS_IFBLK
op_assign
l_int|0x00006000
comma
multiline_comment|/* Block device */
DECL|enumerator|VXFS_IFREG
id|VXFS_IFREG
op_assign
l_int|0x00008000
comma
multiline_comment|/* Regular file */
DECL|enumerator|VXFS_IFCMP
id|VXFS_IFCMP
op_assign
l_int|0x00009000
comma
multiline_comment|/* Compressed file ?!? */
DECL|enumerator|VXFS_IFLNK
id|VXFS_IFLNK
op_assign
l_int|0x0000a000
comma
multiline_comment|/* Symlink */
DECL|enumerator|VXFS_IFSOC
id|VXFS_IFSOC
op_assign
l_int|0x0000c000
comma
multiline_comment|/* Socket */
multiline_comment|/* VxFS internal */
DECL|enumerator|VXFS_IFFSH
id|VXFS_IFFSH
op_assign
l_int|0x10000000
comma
multiline_comment|/* Fileset header */
DECL|enumerator|VXFS_IFILT
id|VXFS_IFILT
op_assign
l_int|0x20000000
comma
multiline_comment|/* Inode list */
DECL|enumerator|VXFS_IFIAU
id|VXFS_IFIAU
op_assign
l_int|0x30000000
comma
multiline_comment|/* Inode allocation unit */
DECL|enumerator|VXFS_IFCUT
id|VXFS_IFCUT
op_assign
l_int|0x40000000
comma
multiline_comment|/* Current usage table */
DECL|enumerator|VXFS_IFATT
id|VXFS_IFATT
op_assign
l_int|0x50000000
comma
multiline_comment|/* Attr. inode */
DECL|enumerator|VXFS_IFLCT
id|VXFS_IFLCT
op_assign
l_int|0x60000000
comma
multiline_comment|/* Link count table */
DECL|enumerator|VXFS_IFIAT
id|VXFS_IFIAT
op_assign
l_int|0x70000000
comma
multiline_comment|/* Indirect attribute file */
DECL|enumerator|VXFS_IFEMR
id|VXFS_IFEMR
op_assign
l_int|0x80000000
comma
multiline_comment|/* Extent map reorg file */
DECL|enumerator|VXFS_IFQUO
id|VXFS_IFQUO
op_assign
l_int|0x90000000
comma
multiline_comment|/* BSD quota file */
DECL|enumerator|VXFS_IFPTI
id|VXFS_IFPTI
op_assign
l_int|0xa0000000
comma
multiline_comment|/* &quot;Pass through&quot; inode */
DECL|enumerator|VXFS_IFLAB
id|VXFS_IFLAB
op_assign
l_int|0x11000000
comma
multiline_comment|/* Device label file */
DECL|enumerator|VXFS_IFOLT
id|VXFS_IFOLT
op_assign
l_int|0x12000000
comma
multiline_comment|/* OLT file */
DECL|enumerator|VXFS_IFLOG
id|VXFS_IFLOG
op_assign
l_int|0x13000000
comma
multiline_comment|/* Log file */
DECL|enumerator|VXFS_IFEMP
id|VXFS_IFEMP
op_assign
l_int|0x14000000
comma
multiline_comment|/* Extent map file */
DECL|enumerator|VXFS_IFEAU
id|VXFS_IFEAU
op_assign
l_int|0x15000000
comma
multiline_comment|/* Extent AU file */
DECL|enumerator|VXFS_IFAUS
id|VXFS_IFAUS
op_assign
l_int|0x16000000
comma
multiline_comment|/* Extent AU summary file */
DECL|enumerator|VXFS_IFDEV
id|VXFS_IFDEV
op_assign
l_int|0x17000000
comma
multiline_comment|/* Device config file */
)brace
suffix:semicolon
DECL|macro|VXFS_TYPE_MASK
mdefine_line|#define&t;VXFS_TYPE_MASK&t;&t;0xfffff000
DECL|macro|VXFS_IS_TYPE
mdefine_line|#define VXFS_IS_TYPE(ip,type)&t;(((ip)-&gt;vii_mode &amp; VXFS_TYPE_MASK) == (type))
DECL|macro|VXFS_ISFIFO
mdefine_line|#define VXFS_ISFIFO(x)&t;&t;VXFS_IS_TYPE((x),VXFS_IFIFO)
DECL|macro|VXFS_ISCHR
mdefine_line|#define VXFS_ISCHR(x)&t;&t;VXFS_IS_TYPE((x),VXFS_IFCHR)
DECL|macro|VXFS_ISDIR
mdefine_line|#define VXFS_ISDIR(x)&t;&t;VXFS_IS_TYPE((x),VXFS_IFDIR)
DECL|macro|VXFS_ISNAM
mdefine_line|#define VXFS_ISNAM(x)&t;&t;VXFS_IS_TYPE((x),VXFS_IFNAM)
DECL|macro|VXFS_ISBLK
mdefine_line|#define VXFS_ISBLK(x)&t;&t;VXFS_IS_TYPE((x),VXFS_IFBLK)
DECL|macro|VXFS_ISLNK
mdefine_line|#define VXFS_ISLNK(x)&t;&t;VXFS_IS_TYPE((x),VXFS_IFLNK)
DECL|macro|VXFS_ISREG
mdefine_line|#define VXFS_ISREG(x)&t;&t;VXFS_IS_TYPE((x),VXFS_IFREG)
DECL|macro|VXFS_ISCMP
mdefine_line|#define VXFS_ISCMP(x)&t;&t;VXFS_IS_TYPE((x),VXFS_IFCMP)
DECL|macro|VXFS_ISSOC
mdefine_line|#define VXFS_ISSOC(x)&t;&t;VXFS_IS_TYPE((x),VXFS_IFSOC)
DECL|macro|VXFS_ISFSH
mdefine_line|#define VXFS_ISFSH(x)&t;&t;VXFS_IS_TYPE((x),VXFS_IFFSH)
DECL|macro|VXFS_ISILT
mdefine_line|#define VXFS_ISILT(x)&t;&t;VXFS_IS_TYPE((x),VXFS_IFILT)
multiline_comment|/*&n; * Inmode organisation types.&n; */
r_enum
(brace
DECL|enumerator|VXFS_ORG_NONE
id|VXFS_ORG_NONE
op_assign
l_int|0
comma
multiline_comment|/* Inode has *no* format ?!? */
DECL|enumerator|VXFS_ORG_EXT4
id|VXFS_ORG_EXT4
op_assign
l_int|1
comma
multiline_comment|/* Ext4 */
DECL|enumerator|VXFS_ORG_IMMED
id|VXFS_ORG_IMMED
op_assign
l_int|2
comma
multiline_comment|/* All data stored in inode */
DECL|enumerator|VXFS_ORG_TYPED
id|VXFS_ORG_TYPED
op_assign
l_int|3
comma
multiline_comment|/* Typed extents */
)brace
suffix:semicolon
DECL|macro|VXFS_IS_ORG
mdefine_line|#define VXFS_IS_ORG(ip,org)&t;((ip)-&gt;vii_orgtype == (org))
DECL|macro|VXFS_ISNONE
mdefine_line|#define VXFS_ISNONE(ip)&t;&t;VXFS_IS_ORG((ip), VXFS_ORG_NONE)
DECL|macro|VXFS_ISEXT4
mdefine_line|#define VXFS_ISEXT4(ip)&t;&t;VXFS_IS_ORG((ip), VXFS_ORG_EXT4)
DECL|macro|VXFS_ISIMMED
mdefine_line|#define VXFS_ISIMMED(ip)&t;VXFS_IS_ORG((ip), VXFS_ORG_IMMED)
DECL|macro|VXFS_ISTYPED
mdefine_line|#define VXFS_ISTYPED(ip)&t;VXFS_IS_ORG((ip), VXFS_ORG_TYPED)
multiline_comment|/*&n; * Get filesystem private data from VFS inode.&n; */
DECL|macro|VXFS_INO
mdefine_line|#define VXFS_INO(ip) &bslash;&n;&t;((struct vxfs_inode_info *)(ip)-&gt;u.generic_ip)
multiline_comment|/*&n; * Get filesystem private data from VFS superblock.&n; */
DECL|macro|VXFS_SBI
mdefine_line|#define VXFS_SBI(sbp) &bslash;&n;&t;((struct vxfs_sb_info *)(sbp)-&gt;u.generic_sbp)
macro_line|#endif /* _VXFS_SUPER_H_ */
eof
