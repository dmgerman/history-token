multiline_comment|/*&n; *   Copyright (c) International Business Machines  Corp., 2000&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; */
macro_line|#ifndef&t;_H_JFS_SUPERBLOCK
DECL|macro|_H_JFS_SUPERBLOCK
mdefine_line|#define _H_JFS_SUPERBLOCK
multiline_comment|/*&n; *&t;jfs_superblock.h&n; */
multiline_comment|/*&n; * make the magic number something a human could read&n; */
DECL|macro|JFS_MAGIC
mdefine_line|#define JFS_MAGIC &t;&quot;JFS1&quot;&t;/* Magic word: Version 1 */
DECL|macro|JFS_VERSION
mdefine_line|#define JFS_VERSION&t;1&t;/* Version number: Version 1 */
DECL|macro|LV_NAME_SIZE
mdefine_line|#define LV_NAME_SIZE&t;11&t;/* MUST BE 11 for OS/2 boot sector */
multiline_comment|/* &n; *&t;aggregate superblock &n; *&n; * The name superblock is too close to super_block, so the name has been&n; * changed to jfs_superblock.  The utilities are still using the old name.&n; */
DECL|struct|jfs_superblock
r_struct
id|jfs_superblock
(brace
DECL|member|s_magic
r_char
id|s_magic
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 4: magic number */
DECL|member|s_version
id|u32
id|s_version
suffix:semicolon
multiline_comment|/* 4: version number */
DECL|member|s_size
id|s64
id|s_size
suffix:semicolon
multiline_comment|/* 8: aggregate size in hardware/LVM blocks;&n;&t;&t;&t;&t; * VFS: number of blocks&n;&t;&t;&t;&t; */
DECL|member|s_bsize
id|s32
id|s_bsize
suffix:semicolon
multiline_comment|/* 4: aggregate block size in bytes; &n;&t;&t;&t;&t; * VFS: fragment size&n;&t;&t;&t;&t; */
DECL|member|s_l2bsize
id|s16
id|s_l2bsize
suffix:semicolon
multiline_comment|/* 2: log2 of s_bsize */
DECL|member|s_l2bfactor
id|s16
id|s_l2bfactor
suffix:semicolon
multiline_comment|/* 2: log2(s_bsize/hardware block size) */
DECL|member|s_pbsize
id|s32
id|s_pbsize
suffix:semicolon
multiline_comment|/* 4: hardware/LVM block size in bytes */
DECL|member|s_l2pbsize
id|s16
id|s_l2pbsize
suffix:semicolon
multiline_comment|/* 2: log2 of s_pbsize */
DECL|member|pad
id|s16
id|pad
suffix:semicolon
multiline_comment|/* 2: padding necessary for alignment */
DECL|member|s_agsize
id|u32
id|s_agsize
suffix:semicolon
multiline_comment|/* 4: allocation group size in aggr. blocks */
DECL|member|s_flag
id|u32
id|s_flag
suffix:semicolon
multiline_comment|/* 4: aggregate attributes:&n;&t;&t;&t;&t; *    see jfs_filsys.h&n;&t;&t;&t;&t; */
DECL|member|s_state
id|u32
id|s_state
suffix:semicolon
multiline_comment|/* 4: mount/unmount/recovery state: &n;&t;&t;&t;&t; *    see jfs_filsys.h&n;&t;&t;&t;&t; */
DECL|member|s_compress
id|s32
id|s_compress
suffix:semicolon
multiline_comment|/* 4: &gt; 0 if data compression */
DECL|member|s_ait2
id|pxd_t
id|s_ait2
suffix:semicolon
multiline_comment|/* 8: first extent of secondary&n;&t;&t;&t;&t; *    aggregate inode table&n;&t;&t;&t;&t; */
DECL|member|s_aim2
id|pxd_t
id|s_aim2
suffix:semicolon
multiline_comment|/* 8: first extent of secondary&n;&t;&t;&t;&t; *    aggregate inode map&n;&t;&t;&t;&t; */
DECL|member|s_logdev
id|u32
id|s_logdev
suffix:semicolon
multiline_comment|/* 4: device address of log */
DECL|member|s_logserial
id|s32
id|s_logserial
suffix:semicolon
multiline_comment|/* 4: log serial number at aggregate mount */
DECL|member|s_logpxd
id|pxd_t
id|s_logpxd
suffix:semicolon
multiline_comment|/* 8: inline log extent */
DECL|member|s_fsckpxd
id|pxd_t
id|s_fsckpxd
suffix:semicolon
multiline_comment|/* 8: inline fsck work space extent */
DECL|member|s_time
r_struct
id|timestruc_t
id|s_time
suffix:semicolon
multiline_comment|/* 8: time last updated */
DECL|member|s_fsckloglen
id|s32
id|s_fsckloglen
suffix:semicolon
multiline_comment|/* 4: Number of filesystem blocks reserved for&n;&t;&t;&t;&t; *    the fsck service log.  &n;&t;&t;&t;&t; *    N.B. These blocks are divided among the&n;&t;&t;&t;&t; *         versions kept.  This is not a per&n;&t;&t;&t;&t; *         version size.&n;&t;&t;&t;&t; *    N.B. These blocks are included in the &n;&t;&t;&t;&t; *         length field of s_fsckpxd.&n;&t;&t;&t;&t; */
DECL|member|s_fscklog
id|s8
id|s_fscklog
suffix:semicolon
multiline_comment|/* 1: which fsck service log is most recent&n;&t;&t;&t;&t; *    0 =&gt; no service log data yet&n;&t;&t;&t;&t; *    1 =&gt; the first one&n;&t;&t;&t;&t; *    2 =&gt; the 2nd one&n;&t;&t;&t;&t; */
DECL|member|s_fpack
r_char
id|s_fpack
(braket
l_int|11
)braket
suffix:semicolon
multiline_comment|/* 11: file system volume name &n;&t;&t;&t;&t; *     N.B. This must be 11 bytes to&n;&t;&t;&t;&t; *          conform with the OS/2 BootSector&n;&t;&t;&t;&t; *          requirements&n;&t;&t;&t;&t; */
multiline_comment|/* extendfs() parameter under s_state &amp; FM_EXTENDFS */
DECL|member|s_xsize
id|s64
id|s_xsize
suffix:semicolon
multiline_comment|/* 8: extendfs s_size */
DECL|member|s_xfsckpxd
id|pxd_t
id|s_xfsckpxd
suffix:semicolon
multiline_comment|/* 8: extendfs fsckpxd */
DECL|member|s_xlogpxd
id|pxd_t
id|s_xlogpxd
suffix:semicolon
multiline_comment|/* 8: extendfs logpxd */
multiline_comment|/* - 128 byte boundary - */
multiline_comment|/*&n;&t; *      DFS VFS support (preliminary) &n;&t; */
DECL|member|s_attach
r_char
id|s_attach
suffix:semicolon
multiline_comment|/* 1: VFS: flag: set when aggregate is attached&n;&t;&t;&t;&t; */
DECL|member|rsrvd4
id|u8
id|rsrvd4
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* 7: reserved - set to 0 */
DECL|member|totalUsable
id|u64
id|totalUsable
suffix:semicolon
multiline_comment|/* 8: VFS: total of 1K blocks which are&n;&t;&t;&t;&t; * available to &quot;normal&quot; (non-root) users.&n;&t;&t;&t;&t; */
DECL|member|minFree
id|u64
id|minFree
suffix:semicolon
multiline_comment|/* 8: VFS: # of 1K blocks held in reserve for &n;&t;&t;&t;&t; * exclusive use of root.  This value can be 0,&n;&t;&t;&t;&t; * and if it is then totalUsable will be equal &n;&t;&t;&t;&t; * to # of blocks in aggregate.  I believe this&n;&t;&t;&t;&t; * means that minFree + totalUsable = # blocks.&n;&t;&t;&t;&t; * In that case, we don&squot;t need to store both &n;&t;&t;&t;&t; * totalUsable and minFree since we can compute&n;&t;&t;&t;&t; * one from the other.  I would guess minFree &n;&t;&t;&t;&t; * would be the one we should store, and &n;&t;&t;&t;&t; * totalUsable would be the one we should &n;&t;&t;&t;&t; * compute.  (Just a guess...)&n;&t;&t;&t;&t; */
DECL|member|realFree
id|u64
id|realFree
suffix:semicolon
multiline_comment|/* 8: VFS: # of free 1K blocks can be used by &n;&t;&t;&t;&t; * &quot;normal&quot; users.  It may be this is something&n;&t;&t;&t;&t; * we should compute when asked for instead of &n;&t;&t;&t;&t; * storing in the superblock.  I don&squot;t know how&n;&t;&t;&t;&t; * often this information is needed.&n;&t;&t;&t;&t; */
multiline_comment|/*&n;&t; *      graffiti area&n;&t; */
)brace
suffix:semicolon
r_extern
r_int
id|readSuper
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|metapage
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|updateSuper
c_func
(paren
r_struct
id|super_block
op_star
comma
id|uint
)paren
suffix:semicolon
macro_line|#endif /*_H_JFS_SUPERBLOCK */
eof