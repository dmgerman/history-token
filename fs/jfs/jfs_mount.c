multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2003&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
multiline_comment|/*&n; * Module: jfs_mount.c&n; *&n; * note: file system in transition to aggregate/fileset:&n; *&n; * file system mount is interpreted as the mount of aggregate, &n; * if not already mounted, and mount of the single/only fileset in &n; * the aggregate;&n; *&n; * a file system/aggregate is represented by an internal inode&n; * (aka mount inode) initialized with aggregate superblock;&n; * each vfs represents a fileset, and points to its &quot;fileset inode &n; * allocation map inode&quot; (aka fileset inode):&n; * (an aggregate itself is structured recursively as a filset: &n; * an internal vfs is constructed and points to its &quot;fileset inode &n; * allocation map inode&quot; (aka aggregate inode) where each inode &n; * represents a fileset inode) so that inode number is mapped to &n; * on-disk inode in uniform way at both aggregate and fileset level;&n; *&n; * each vnode/inode of a fileset is linked to its vfs (to facilitate&n; * per fileset inode operations, e.g., unmount of a fileset, etc.);&n; * each inode points to the mount inode (to facilitate access to&n; * per aggregate information, e.g., block size, etc.) as well as&n; * its file set inode.&n; *&n; *   aggregate &n; *   ipmnt&n; *   mntvfs -&gt; fileset ipimap+ -&gt; aggregate ipbmap -&gt; aggregate ipaimap;&n; *             fileset vfs     -&gt; vp(1) &lt;-&gt; ... &lt;-&gt; vp(n) &lt;-&gt;vproot;&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &quot;jfs_incore.h&quot;
macro_line|#include &quot;jfs_filsys.h&quot;
macro_line|#include &quot;jfs_superblock.h&quot;
macro_line|#include &quot;jfs_dmap.h&quot;
macro_line|#include &quot;jfs_imap.h&quot;
macro_line|#include &quot;jfs_metapage.h&quot;
macro_line|#include &quot;jfs_debug.h&quot;
multiline_comment|/*&n; * forward references&n; */
r_static
r_int
id|chkSuper
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_static
r_int
id|logMOUNT
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
multiline_comment|/*&n; * NAME:&t;jfs_mount(sb)&n; *&n; * FUNCTION:&t;vfs_mount()&n; *&n; * PARAMETER:&t;sb&t;- super block&n; *&n; * RETURN:&t;-EBUSY&t;- device already mounted or open for write&n; *&t;&t;-EBUSY&t;- cvrdvp already mounted;&n; *&t;&t;-EBUSY&t;- mount table full&n; *&t;&t;-ENOTDIR- cvrdvp not directory on a device mount&n; *&t;&t;-ENXIO&t;- device open failure&n; */
DECL|function|jfs_mount
r_int
id|jfs_mount
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Return code          */
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|ipaimap
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|inode
op_star
id|ipaimap2
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|inode
op_star
id|ipimap
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|inode
op_star
id|ipbmap
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * read/validate superblock &n;&t; * (initialize mount inode from the superblock)&n;&t; */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|chkSuper
c_func
(paren
id|sb
)paren
)paren
)paren
(brace
r_goto
id|errout20
suffix:semicolon
)brace
id|ipaimap
op_assign
id|diReadSpecial
c_func
(paren
id|sb
comma
id|AGGREGATE_I
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipaimap
op_eq
l_int|NULL
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_mount: Faild to read AGGREGATE_I&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|errout20
suffix:semicolon
)brace
id|sbi-&gt;ipaimap
op_assign
id|ipaimap
suffix:semicolon
id|jfs_info
c_func
(paren
l_string|&quot;jfs_mount: ipaimap:0x%p&quot;
comma
id|ipaimap
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * initialize aggregate inode allocation map&n;&t; */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|diMount
c_func
(paren
id|ipaimap
)paren
)paren
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_mount: diMount(ipaimap) failed w/rc = %d&quot;
comma
id|rc
)paren
suffix:semicolon
r_goto
id|errout21
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * open aggregate block allocation map&n;&t; */
id|ipbmap
op_assign
id|diReadSpecial
c_func
(paren
id|sb
comma
id|BMAP_I
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipbmap
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|errout22
suffix:semicolon
)brace
id|jfs_info
c_func
(paren
l_string|&quot;jfs_mount: ipbmap:0x%p&quot;
comma
id|ipbmap
)paren
suffix:semicolon
id|sbi-&gt;ipbmap
op_assign
id|ipbmap
suffix:semicolon
multiline_comment|/*&n;&t; * initialize aggregate block allocation map&n;&t; */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|dbMount
c_func
(paren
id|ipbmap
)paren
)paren
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_mount: dbMount failed w/rc = %d&quot;
comma
id|rc
)paren
suffix:semicolon
r_goto
id|errout22
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * open the secondary aggregate inode allocation map&n;&t; *&n;&t; * This is a duplicate of the aggregate inode allocation map.&n;&t; *&n;&t; * hand craft a vfs in the same fashion as we did to read ipaimap.&n;&t; * By adding INOSPEREXT (32) to the inode number, we are telling&n;&t; * diReadSpecial that we are reading from the secondary aggregate&n;&t; * inode table.  This also creates a unique entry in the inode hash&n;&t; * table.&n;&t; */
r_if
c_cond
(paren
(paren
id|sbi-&gt;mntflag
op_amp
id|JFS_BAD_SAIT
)paren
op_eq
l_int|0
)paren
(brace
id|ipaimap2
op_assign
id|diReadSpecial
c_func
(paren
id|sb
comma
id|AGGREGATE_I
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipaimap2
op_eq
l_int|0
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_mount: Faild to read AGGREGATE_I&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|errout35
suffix:semicolon
)brace
id|sbi-&gt;ipaimap2
op_assign
id|ipaimap2
suffix:semicolon
id|jfs_info
c_func
(paren
l_string|&quot;jfs_mount: ipaimap2:0x%p&quot;
comma
id|ipaimap2
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * initialize secondary aggregate inode allocation map&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|diMount
c_func
(paren
id|ipaimap2
)paren
)paren
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_mount: diMount(ipaimap2) failed, rc = %d&quot;
comma
id|rc
)paren
suffix:semicolon
r_goto
id|errout35
suffix:semicolon
)brace
)brace
r_else
multiline_comment|/* Secondary aggregate inode table is not valid */
id|sbi-&gt;ipaimap2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; *      mount (the only/single) fileset&n;&t; */
multiline_comment|/*&n;&t; * open fileset inode allocation map (aka fileset inode)&n;&t; */
id|ipimap
op_assign
id|diReadSpecial
c_func
(paren
id|sb
comma
id|FILESYSTEM_I
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipimap
op_eq
l_int|NULL
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_mount: Failed to read FILESYSTEM_I&quot;
)paren
suffix:semicolon
multiline_comment|/* open fileset secondary inode allocation map */
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|errout40
suffix:semicolon
)brace
id|jfs_info
c_func
(paren
l_string|&quot;jfs_mount: ipimap:0x%p&quot;
comma
id|ipimap
)paren
suffix:semicolon
multiline_comment|/* map further access of per fileset inodes by the fileset inode */
id|sbi-&gt;ipimap
op_assign
id|ipimap
suffix:semicolon
multiline_comment|/* initialize fileset inode allocation map */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|diMount
c_func
(paren
id|ipimap
)paren
)paren
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_mount: diMount failed w/rc = %d&quot;
comma
id|rc
)paren
suffix:semicolon
r_goto
id|errout41
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; *      unwind on error&n;&t; */
singleline_comment|//errout42: /* close fileset inode allocation map */
id|diUnmount
c_func
(paren
id|ipimap
comma
l_int|1
)paren
suffix:semicolon
id|errout41
suffix:colon
multiline_comment|/* close fileset inode allocation map inode */
id|diFreeSpecial
c_func
(paren
id|ipimap
)paren
suffix:semicolon
id|errout40
suffix:colon
multiline_comment|/* fileset closed */
multiline_comment|/* close secondary aggregate inode allocation map */
r_if
c_cond
(paren
id|ipaimap2
)paren
(brace
id|diUnmount
c_func
(paren
id|ipaimap2
comma
l_int|1
)paren
suffix:semicolon
id|diFreeSpecial
c_func
(paren
id|ipaimap2
)paren
suffix:semicolon
)brace
id|errout35
suffix:colon
multiline_comment|/* close aggregate block allocation map */
id|dbUnmount
c_func
(paren
id|ipbmap
comma
l_int|1
)paren
suffix:semicolon
id|diFreeSpecial
c_func
(paren
id|ipbmap
)paren
suffix:semicolon
id|errout22
suffix:colon
multiline_comment|/* close aggregate inode allocation map */
id|diUnmount
c_func
(paren
id|ipaimap
comma
l_int|1
)paren
suffix:semicolon
id|errout21
suffix:colon
multiline_comment|/* close aggregate inodes */
id|diFreeSpecial
c_func
(paren
id|ipaimap
)paren
suffix:semicolon
id|errout20
suffix:colon
multiline_comment|/* aggregate closed */
id|out
suffix:colon
r_if
c_cond
(paren
id|rc
)paren
id|jfs_err
c_func
(paren
l_string|&quot;Mount JFS Failure: %d&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * NAME:&t;jfs_mount_rw(sb, remount)&n; *&n; * FUNCTION:&t;Completes read-write mount, or remounts read-only volume&n; *&t;&t;as read-write&n; */
DECL|function|jfs_mount_rw
r_int
id|jfs_mount_rw
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|remount
)paren
(brace
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|jfs_log
op_star
id|log
suffix:semicolon
r_int
id|rc
suffix:semicolon
multiline_comment|/*&n;&t; * If we are re-mounting a previously read-only volume, we want to&n;&t; * re-read the inode and block maps, since fsck.jfs may have updated&n;&t; * them.&n;&t; */
r_if
c_cond
(paren
id|remount
)paren
(brace
r_if
c_cond
(paren
id|chkSuper
c_func
(paren
id|sb
)paren
op_logical_or
(paren
id|sbi-&gt;state
op_ne
id|FM_CLEAN
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|truncate_inode_pages
c_func
(paren
id|sbi-&gt;ipimap-&gt;i_mapping
comma
l_int|0
)paren
suffix:semicolon
id|truncate_inode_pages
c_func
(paren
id|sbi-&gt;ipbmap-&gt;i_mapping
comma
l_int|0
)paren
suffix:semicolon
id|diUnmount
c_func
(paren
id|sbi-&gt;ipimap
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|diMount
c_func
(paren
id|sbi-&gt;ipimap
)paren
)paren
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_mount_rw: diMount failed!&quot;
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|dbUnmount
c_func
(paren
id|sbi-&gt;ipbmap
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|dbMount
c_func
(paren
id|sbi-&gt;ipbmap
)paren
)paren
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_mount_rw: dbMount failed!&quot;
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * open/initialize log&n;&t; */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|lmLogOpen
c_func
(paren
id|sb
comma
op_amp
id|log
)paren
)paren
)paren
r_return
id|rc
suffix:semicolon
id|JFS_SBI
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|log
op_assign
id|log
suffix:semicolon
multiline_comment|/*&n;&t; * update file system superblock;&n;&t; */
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|updateSuper
c_func
(paren
id|sb
comma
id|FM_MOUNT
)paren
)paren
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_mount: updateSuper failed w/rc = %d&quot;
comma
id|rc
)paren
suffix:semicolon
id|lmLogClose
c_func
(paren
id|sb
comma
id|log
)paren
suffix:semicolon
id|JFS_SBI
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|log
op_assign
l_int|0
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * write MOUNT log record of the file system&n;&t; */
id|logMOUNT
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;chkSuper()&n; *&n; * validate the superblock of the file system to be mounted and &n; * get the file system parameters.&n; *&n; * returns&n; *&t;0 with fragsize set if check successful&n; *&t;error code if not successful&n; */
DECL|function|chkSuper
r_static
r_int
id|chkSuper
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|jfs_superblock
op_star
id|j_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|AIM_bytesize
comma
id|AIT_bytesize
suffix:semicolon
r_int
id|expected_AIM_bytesize
comma
id|expected_AIT_bytesize
suffix:semicolon
id|s64
id|AIM_byte_addr
comma
id|AIT_byte_addr
comma
id|fsckwsp_addr
suffix:semicolon
id|s64
id|byte_addr_diff0
comma
id|byte_addr_diff1
suffix:semicolon
id|s32
id|bsize
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|readSuper
c_func
(paren
id|sb
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
id|rc
suffix:semicolon
id|j_sb
op_assign
(paren
r_struct
id|jfs_superblock
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
multiline_comment|/*&n;&t; * validate superblock&n;&t; */
multiline_comment|/* validate fs signature */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|j_sb-&gt;s_magic
comma
id|JFS_MAGIC
comma
l_int|4
)paren
op_logical_or
id|j_sb-&gt;s_version
OG
id|cpu_to_le32
c_func
(paren
id|JFS_VERSION
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|bsize
op_assign
id|le32_to_cpu
c_func
(paren
id|j_sb-&gt;s_bsize
)paren
suffix:semicolon
macro_line|#ifdef _JFS_4K
r_if
c_cond
(paren
id|bsize
op_ne
id|PSIZE
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;Currently only 4K block size supported!&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* _JFS_4K */
id|jfs_info
c_func
(paren
l_string|&quot;superblock: flag:0x%08x state:0x%08x size:0x%Lx&quot;
comma
id|le32_to_cpu
c_func
(paren
id|j_sb-&gt;s_flag
)paren
comma
id|le32_to_cpu
c_func
(paren
id|j_sb-&gt;s_state
)paren
comma
(paren
r_int
r_int
r_int
)paren
id|le64_to_cpu
c_func
(paren
id|j_sb-&gt;s_size
)paren
)paren
suffix:semicolon
multiline_comment|/* validate the descriptors for Secondary AIM and AIT */
r_if
c_cond
(paren
(paren
id|j_sb-&gt;s_flag
op_amp
id|cpu_to_le32
c_func
(paren
id|JFS_BAD_SAIT
)paren
)paren
op_ne
id|cpu_to_le32
c_func
(paren
id|JFS_BAD_SAIT
)paren
)paren
(brace
id|expected_AIM_bytesize
op_assign
l_int|2
op_star
id|PSIZE
suffix:semicolon
id|AIM_bytesize
op_assign
id|lengthPXD
c_func
(paren
op_amp
(paren
id|j_sb-&gt;s_aim2
)paren
)paren
op_star
id|bsize
suffix:semicolon
id|expected_AIT_bytesize
op_assign
l_int|4
op_star
id|PSIZE
suffix:semicolon
id|AIT_bytesize
op_assign
id|lengthPXD
c_func
(paren
op_amp
(paren
id|j_sb-&gt;s_ait2
)paren
)paren
op_star
id|bsize
suffix:semicolon
id|AIM_byte_addr
op_assign
id|addressPXD
c_func
(paren
op_amp
(paren
id|j_sb-&gt;s_aim2
)paren
)paren
op_star
id|bsize
suffix:semicolon
id|AIT_byte_addr
op_assign
id|addressPXD
c_func
(paren
op_amp
(paren
id|j_sb-&gt;s_ait2
)paren
)paren
op_star
id|bsize
suffix:semicolon
id|byte_addr_diff0
op_assign
id|AIT_byte_addr
op_minus
id|AIM_byte_addr
suffix:semicolon
id|fsckwsp_addr
op_assign
id|addressPXD
c_func
(paren
op_amp
(paren
id|j_sb-&gt;s_fsckpxd
)paren
)paren
op_star
id|bsize
suffix:semicolon
id|byte_addr_diff1
op_assign
id|fsckwsp_addr
op_minus
id|AIT_byte_addr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|AIM_bytesize
op_ne
id|expected_AIM_bytesize
)paren
op_logical_or
(paren
id|AIT_bytesize
op_ne
id|expected_AIT_bytesize
)paren
op_logical_or
(paren
id|byte_addr_diff0
op_ne
id|AIM_bytesize
)paren
op_logical_or
(paren
id|byte_addr_diff1
op_le
id|AIT_bytesize
)paren
)paren
id|j_sb-&gt;s_flag
op_or_assign
id|cpu_to_le32
c_func
(paren
id|JFS_BAD_SAIT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|j_sb-&gt;s_flag
op_amp
id|cpu_to_le32
c_func
(paren
id|JFS_GROUPCOMMIT
)paren
)paren
op_ne
id|cpu_to_le32
c_func
(paren
id|JFS_GROUPCOMMIT
)paren
)paren
id|j_sb-&gt;s_flag
op_or_assign
id|cpu_to_le32
c_func
(paren
id|JFS_GROUPCOMMIT
)paren
suffix:semicolon
multiline_comment|/* validate fs state */
r_if
c_cond
(paren
id|j_sb-&gt;s_state
op_ne
id|cpu_to_le32
c_func
(paren
id|FM_CLEAN
)paren
op_logical_and
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|jfs_err
c_func
(paren
l_string|&quot;jfs_mount: Mount Failure: File System Dirty.&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|sbi-&gt;state
op_assign
id|le32_to_cpu
c_func
(paren
id|j_sb-&gt;s_state
)paren
suffix:semicolon
id|sbi-&gt;mntflag
op_assign
id|le32_to_cpu
c_func
(paren
id|j_sb-&gt;s_flag
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * JFS always does I/O by 4K pages.  Don&squot;t tell the buffer cache&n;&t; * that we use anything else (leave s_blocksize alone).&n;&t; */
id|sbi-&gt;bsize
op_assign
id|bsize
suffix:semicolon
id|sbi-&gt;l2bsize
op_assign
id|le16_to_cpu
c_func
(paren
id|j_sb-&gt;s_l2bsize
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * For now, ignore s_pbsize, l2bfactor.  All I/O going through buffer&n;&t; * cache.&n;&t; */
id|sbi-&gt;nbperpage
op_assign
id|PSIZE
op_rshift
id|sbi-&gt;l2bsize
suffix:semicolon
id|sbi-&gt;l2nbperpage
op_assign
id|L2PSIZE
op_minus
id|sbi-&gt;l2bsize
suffix:semicolon
id|sbi-&gt;l2niperblk
op_assign
id|sbi-&gt;l2bsize
op_minus
id|L2DISIZE
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;mntflag
op_amp
id|JFS_INLINELOG
)paren
id|sbi-&gt;logpxd
op_assign
id|j_sb-&gt;s_logpxd
suffix:semicolon
r_else
(brace
id|sbi-&gt;logdev
op_assign
id|new_decode_dev
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|j_sb-&gt;s_logdev
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|sbi-&gt;uuid
comma
id|j_sb-&gt;s_uuid
comma
r_sizeof
(paren
id|sbi-&gt;uuid
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|sbi-&gt;loguuid
comma
id|j_sb-&gt;s_loguuid
comma
r_sizeof
(paren
id|sbi-&gt;uuid
)paren
)paren
suffix:semicolon
)brace
id|sbi-&gt;fsckpxd
op_assign
id|j_sb-&gt;s_fsckpxd
suffix:semicolon
id|sbi-&gt;ait2
op_assign
id|j_sb-&gt;s_ait2
suffix:semicolon
id|out
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;updateSuper()&n; *&n; * update synchronously superblock if it is mounted read-write.&n; */
DECL|function|updateSuper
r_int
id|updateSuper
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|uint
id|state
)paren
(brace
r_struct
id|jfs_superblock
op_star
id|j_sb
suffix:semicolon
r_struct
id|jfs_sb_info
op_star
id|sbi
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;flag
op_amp
id|JFS_NOINTEGRITY
)paren
(brace
r_if
c_cond
(paren
id|state
op_eq
id|FM_DIRTY
)paren
(brace
id|sbi-&gt;p_state
op_assign
id|state
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|state
op_eq
id|FM_MOUNT
)paren
(brace
id|sbi-&gt;p_state
op_assign
id|sbi-&gt;state
suffix:semicolon
id|state
op_assign
id|FM_DIRTY
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|state
op_eq
id|FM_CLEAN
)paren
(brace
id|state
op_assign
id|sbi-&gt;p_state
suffix:semicolon
)brace
r_else
id|jfs_err
c_func
(paren
l_string|&quot;updateSuper: bad state&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sbi-&gt;state
op_eq
id|FM_DIRTY
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|readSuper
c_func
(paren
id|sb
comma
op_amp
id|bh
)paren
)paren
)paren
r_return
id|rc
suffix:semicolon
id|j_sb
op_assign
(paren
r_struct
id|jfs_superblock
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|j_sb-&gt;s_state
op_assign
id|cpu_to_le32
c_func
(paren
id|state
)paren
suffix:semicolon
id|sbi-&gt;state
op_assign
id|state
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
id|FM_MOUNT
)paren
(brace
multiline_comment|/* record log&squot;s dev_t and mount serial number */
id|j_sb-&gt;s_logdev
op_assign
id|cpu_to_le32
c_func
(paren
id|new_encode_dev
c_func
(paren
id|sbi-&gt;log-&gt;bdev-&gt;bd_dev
)paren
)paren
suffix:semicolon
id|j_sb-&gt;s_logserial
op_assign
id|cpu_to_le32
c_func
(paren
id|sbi-&gt;log-&gt;serial
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|state
op_eq
id|FM_CLEAN
)paren
(brace
multiline_comment|/*&n;&t;&t; * If this volume is shared with OS/2, OS/2 will need to&n;&t;&t; * recalculate DASD usage, since we don&squot;t deal with it.&n;&t;&t; */
r_if
c_cond
(paren
id|j_sb-&gt;s_flag
op_amp
id|cpu_to_le32
c_func
(paren
id|JFS_DASD_ENABLED
)paren
)paren
id|j_sb-&gt;s_flag
op_or_assign
id|cpu_to_le32
c_func
(paren
id|JFS_DASD_PRIME
)paren
suffix:semicolon
)brace
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|sync_dirty_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;readSuper()&n; *&n; * read superblock by raw sector address&n; */
DECL|function|readSuper
r_int
id|readSuper
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
op_star
id|bpp
)paren
(brace
multiline_comment|/* read in primary superblock */
op_star
id|bpp
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|SUPER1_OFF
op_rshift
id|sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|bpp
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* read in secondary/replicated superblock */
op_star
id|bpp
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|SUPER2_OFF
op_rshift
id|sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|bpp
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;logMOUNT()&n; *&n; * function: write a MOUNT log record for file system.&n; *&n; * MOUNT record keeps logredo() from processing log records&n; * for this file system past this point in log.&n; * it is harmless if mount fails.&n; *&n; * note: MOUNT record is at aggregate level, not at fileset level, &n; * since log records of previous mounts of a fileset&n; * (e.g., AFTER record of extent allocation) have to be processed &n; * to update block allocation map at aggregate level.&n; */
DECL|function|logMOUNT
r_static
r_int
id|logMOUNT
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|jfs_log
op_star
id|log
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|log
suffix:semicolon
r_struct
id|lrd
id|lrd
suffix:semicolon
id|lrd.logtid
op_assign
l_int|0
suffix:semicolon
id|lrd.backchain
op_assign
l_int|0
suffix:semicolon
id|lrd.type
op_assign
id|cpu_to_le16
c_func
(paren
id|LOG_MOUNT
)paren
suffix:semicolon
id|lrd.length
op_assign
l_int|0
suffix:semicolon
id|lrd.aggregate
op_assign
id|cpu_to_le32
c_func
(paren
id|new_encode_dev
c_func
(paren
id|sb-&gt;s_bdev-&gt;bd_dev
)paren
)paren
suffix:semicolon
id|lmLog
c_func
(paren
id|log
comma
l_int|NULL
comma
op_amp
id|lrd
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
