multiline_comment|/*&n; * ialloc.c&n; *&n; * PURPOSE&n; *&t;Inode allocation handling routines for the OSTA-UDF(tm) filesystem.&n; *&n; * CONTACTS&n; *&t;E-mail regarding any portion of the Linux UDF file system should be&n; *&t;directed to the development team mailing list (run by majordomo):&n; *&t;&t;linux_udf@hpesjro.fc.hp.com&n; *&n; * COPYRIGHT&n; *&t;This file is distributed under the terms of the GNU General Public&n; *&t;License (GPL). Copies of the GPL can be obtained from:&n; *&t;&t;ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *&t;Each contributing author retains all rights to their own work.&n; *&n; *  (C) 1998-2000 Ben Fennema&n; *&n; * HISTORY&n; *&n; *  02/24/99 blf  Created.&n; *&n; */
macro_line|#include &quot;udfdecl.h&quot;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/quotaops.h&gt;
macro_line|#include &lt;linux/udf_fs.h&gt;
macro_line|#include &quot;udf_i.h&quot;
macro_line|#include &quot;udf_sb.h&quot;
DECL|function|udf_free_inode
r_void
id|udf_free_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
id|is_directory
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
multiline_comment|/*&n;&t; * Note: we must free any quota before locking the superblock,&n;&t; * as writing the quota to disk may need the lock as well.&n;&t; */
id|DQUOT_FREE_INODE
c_func
(paren
id|inode
)paren
suffix:semicolon
id|DQUOT_DROP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|is_directory
op_assign
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UDF_SB_LVIDBH
c_func
(paren
id|sb
)paren
)paren
(brace
r_if
c_cond
(paren
id|is_directory
)paren
id|UDF_SB_LVIDIU
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|numDirs
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|UDF_SB_LVIDIU
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|numDirs
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_else
id|UDF_SB_LVIDIU
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|numFiles
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|UDF_SB_LVIDIU
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|numFiles
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|UDF_SB_LVIDBH
c_func
(paren
id|sb
)paren
)paren
suffix:semicolon
)brace
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|udf_free_blocks
c_func
(paren
id|sb
comma
l_int|NULL
comma
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|udf_new_inode
r_struct
id|inode
op_star
id|udf_new_inode
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
id|mode
comma
r_int
op_star
id|err
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|block
suffix:semicolon
id|Uint32
id|start
op_assign
id|UDF_I_LOCATION
c_func
(paren
id|dir
)paren
dot
id|logicalBlockNum
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
op_star
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|err
op_assign
op_minus
id|ENOSPC
suffix:semicolon
id|block
op_assign
id|udf_new_block
c_func
(paren
id|dir-&gt;i_sb
comma
l_int|NULL
comma
id|UDF_I_LOCATION
c_func
(paren
id|dir
)paren
dot
id|partitionReferenceNum
comma
id|start
comma
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|err
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UDF_SB_LVIDBH
c_func
(paren
id|sb
)paren
)paren
(brace
r_struct
id|LogicalVolHeaderDesc
op_star
id|lvhd
suffix:semicolon
id|Uint64
id|uniqueID
suffix:semicolon
id|lvhd
op_assign
(paren
r_struct
id|LogicalVolHeaderDesc
op_star
)paren
(paren
id|UDF_SB_LVID
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|logicalVolContentsUse
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|UDF_SB_LVIDIU
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|numDirs
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|UDF_SB_LVIDIU
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|numDirs
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_else
id|UDF_SB_LVIDIU
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|numFiles
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|UDF_SB_LVIDIU
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|numFiles
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|UDF_I_UNIQUE
c_func
(paren
id|inode
)paren
op_assign
id|uniqueID
op_assign
id|le64_to_cpu
c_func
(paren
id|lvhd-&gt;uniqueID
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_increment
id|uniqueID
op_amp
l_int|0x00000000FFFFFFFFUL
)paren
)paren
id|uniqueID
op_add_assign
l_int|16
suffix:semicolon
id|lvhd-&gt;uniqueID
op_assign
id|cpu_to_le64
c_func
(paren
id|uniqueID
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|UDF_SB_LVIDBH
c_func
(paren
id|sb
)paren
)paren
suffix:semicolon
)brace
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_mode
op_amp
id|S_ISGID
)paren
(brace
id|inode-&gt;i_gid
op_assign
id|dir-&gt;i_gid
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|mode
op_or_assign
id|S_ISGID
suffix:semicolon
)brace
r_else
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
dot
id|logicalBlockNum
op_assign
id|block
suffix:semicolon
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
dot
id|partitionReferenceNum
op_assign
id|UDF_I_LOCATION
c_func
(paren
id|dir
)paren
dot
id|partitionReferenceNum
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|udf_get_lb_pblock
c_func
(paren
id|sb
comma
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
comma
l_int|0
)paren
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
id|UDF_I_LENALLOC
c_func
(paren
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|UDF_QUERY_FLAG
c_func
(paren
id|inode-&gt;i_sb
comma
id|UDF_FLAG_USE_EXTENDED_FE
)paren
)paren
(brace
id|UDF_I_EXTENDED_FE
c_func
(paren
id|inode
)paren
op_assign
l_int|1
suffix:semicolon
id|UDF_UPDATE_UDFREV
c_func
(paren
id|inode-&gt;i_sb
comma
id|UDF_VERS_USE_EXTENDED_FE
)paren
suffix:semicolon
)brace
r_else
id|UDF_I_EXTENDED_FE
c_func
(paren
id|inode
)paren
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|UDF_QUERY_FLAG
c_func
(paren
id|inode-&gt;i_sb
comma
id|UDF_FLAG_USE_AD_IN_ICB
)paren
)paren
id|UDF_I_ALLOCTYPE
c_func
(paren
id|inode
)paren
op_assign
id|ICB_FLAG_AD_IN_ICB
suffix:semicolon
r_else
r_if
c_cond
(paren
id|UDF_QUERY_FLAG
c_func
(paren
id|inode-&gt;i_sb
comma
id|UDF_FLAG_USE_SHORT_AD
)paren
)paren
id|UDF_I_ALLOCTYPE
c_func
(paren
id|inode
)paren
op_assign
id|ICB_FLAG_AD_SHORT
suffix:semicolon
r_else
id|UDF_I_ALLOCTYPE
c_func
(paren
id|inode
)paren
op_assign
id|ICB_FLAG_AD_LONG
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|UDF_I_CRTIME
c_func
(paren
id|inode
)paren
op_assign
id|CURRENT_TIME
suffix:semicolon
id|UDF_I_UMTIME
c_func
(paren
id|inode
)paren
op_assign
id|UDF_I_UCTIME
c_func
(paren
id|inode
)paren
op_assign
id|UDF_I_UCRTIME
c_func
(paren
id|inode
)paren
op_assign
id|CURRENT_UTIME
suffix:semicolon
id|UDF_I_NEW_INODE
c_func
(paren
id|inode
)paren
op_assign
l_int|1
suffix:semicolon
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DQUOT_ALLOC_INODE
c_func
(paren
id|inode
)paren
)paren
(brace
id|DQUOT_DROP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_flags
op_or_assign
id|S_NOQUOTA
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
op_star
id|err
op_assign
op_minus
id|EDQUOT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|err
op_assign
l_int|0
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
eof
