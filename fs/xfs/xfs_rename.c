multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_macros.h&quot;
macro_line|#include &quot;xfs_types.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
macro_line|#include &quot;xfs_dir.h&quot;
macro_line|#include &quot;xfs_dir2.h&quot;
macro_line|#include &quot;xfs_dmapi.h&quot;
macro_line|#include &quot;xfs_mount.h&quot;
macro_line|#include &quot;xfs_bmap_btree.h&quot;
macro_line|#include &quot;xfs_attr_sf.h&quot;
macro_line|#include &quot;xfs_dir_sf.h&quot;
macro_line|#include &quot;xfs_dir2_sf.h&quot;
macro_line|#include &quot;xfs_dinode.h&quot;
macro_line|#include &quot;xfs_inode_item.h&quot;
macro_line|#include &quot;xfs_inode.h&quot;
macro_line|#include &quot;xfs_bmap.h&quot;
macro_line|#include &quot;xfs_error.h&quot;
macro_line|#include &quot;xfs_quota.h&quot;
macro_line|#include &quot;xfs_refcache.h&quot;
macro_line|#include &quot;xfs_utils.h&quot;
macro_line|#include &quot;xfs_trans_space.h&quot;
macro_line|#include &quot;xfs_da_btree.h&quot;
macro_line|#include &quot;xfs_dir_leaf.h&quot;
multiline_comment|/*&n; * Given an array of up to 4 inode pointers, unlock the pointed to inodes.&n; * If there are fewer than 4 entries in the array, the empty entries will&n; * be at the end and will have NULL pointers in them.&n; */
id|STATIC
r_void
DECL|function|xfs_rename_unlock4
id|xfs_rename_unlock4
c_func
(paren
id|xfs_inode_t
op_star
op_star
id|i_tab
comma
id|uint
id|lock_mode
)paren
(brace
r_int
id|i
suffix:semicolon
id|xfs_iunlock
c_func
(paren
id|i_tab
(braket
l_int|0
)braket
comma
id|lock_mode
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i_tab
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Watch out for duplicate entries in the table.&n;&t;&t; */
r_if
c_cond
(paren
id|i_tab
(braket
id|i
)braket
op_ne
id|i_tab
(braket
id|i
op_minus
l_int|1
)braket
)paren
(brace
id|xfs_iunlock
c_func
(paren
id|i_tab
(braket
id|i
)braket
comma
id|lock_mode
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#ifdef DEBUG
DECL|variable|xfs_rename_skip
DECL|variable|xfs_rename_nskip
r_int
id|xfs_rename_skip
comma
id|xfs_rename_nskip
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * The following routine will acquire the locks required for a rename&n; * operation. The code understands the semantics of renames and will&n; * validate that name1 exists under dp1 &amp; that name2 may or may not&n; * exist under dp2.&n; *&n; * We are renaming dp1/name1 to dp2/name2.&n; *&n; * Return ENOENT if dp1 does not exist, other lookup errors, or 0 for success.&n; */
id|STATIC
r_int
DECL|function|xfs_lock_for_rename
id|xfs_lock_for_rename
c_func
(paren
id|xfs_inode_t
op_star
id|dp1
comma
multiline_comment|/* old (source) directory inode */
id|xfs_inode_t
op_star
id|dp2
comma
multiline_comment|/* new (target) directory inode */
id|vname_t
op_star
id|vname1
comma
multiline_comment|/* old entry name */
id|vname_t
op_star
id|vname2
comma
multiline_comment|/* new entry name */
id|xfs_inode_t
op_star
op_star
id|ipp1
comma
multiline_comment|/* inode of old entry */
id|xfs_inode_t
op_star
op_star
id|ipp2
comma
multiline_comment|/* inode of new entry, if it&n;&t;&t;&t;&t;   already exists, NULL otherwise. */
id|xfs_inode_t
op_star
op_star
id|i_tab
comma
multiline_comment|/* array of inode returned, sorted */
r_int
op_star
id|num_inodes
)paren
multiline_comment|/* number of inodes in array */
(brace
id|xfs_inode_t
op_star
id|ip1
comma
op_star
id|ip2
comma
op_star
id|temp
suffix:semicolon
id|xfs_ino_t
id|inum1
comma
id|inum2
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|uint
id|lock_mode
suffix:semicolon
r_int
id|diff_dirs
op_assign
(paren
id|dp1
op_ne
id|dp2
)paren
suffix:semicolon
id|ip2
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * First, find out the current inums of the entries so that we&n;&t; * can determine the initial locking order.  We&squot;ll have to&n;&t; * sanity check stuff after all the locks have been acquired&n;&t; * to see if we still have the right inodes, directories, etc.&n;&t; */
id|lock_mode
op_assign
id|xfs_ilock_map_shared
c_func
(paren
id|dp1
)paren
suffix:semicolon
id|error
op_assign
id|xfs_get_dir_entry
c_func
(paren
id|vname1
comma
op_amp
id|ip1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|xfs_iunlock_map_shared
c_func
(paren
id|dp1
comma
id|lock_mode
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|inum1
op_assign
id|ip1-&gt;i_ino
suffix:semicolon
id|ASSERT
c_func
(paren
id|ip1
)paren
suffix:semicolon
id|ITRACE
c_func
(paren
id|ip1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Unlock dp1 and lock dp2 if they are different.&n;&t; */
r_if
c_cond
(paren
id|diff_dirs
)paren
(brace
id|xfs_iunlock_map_shared
c_func
(paren
id|dp1
comma
id|lock_mode
)paren
suffix:semicolon
id|lock_mode
op_assign
id|xfs_ilock_map_shared
c_func
(paren
id|dp2
)paren
suffix:semicolon
)brace
id|error
op_assign
id|xfs_dir_lookup_int
c_func
(paren
id|XFS_ITOBHV
c_func
(paren
id|dp2
)paren
comma
id|lock_mode
comma
id|vname2
comma
op_amp
id|inum2
comma
op_amp
id|ip2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
id|ENOENT
)paren
(brace
multiline_comment|/* target does not need to exist. */
id|inum2
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|error
)paren
(brace
multiline_comment|/*&n;&t;&t; * If dp2 and dp1 are the same, the next line unlocks dp1.&n;&t;&t; * Got it?&n;&t;&t; */
id|xfs_iunlock_map_shared
c_func
(paren
id|dp2
comma
id|lock_mode
)paren
suffix:semicolon
id|IRELE
(paren
id|ip1
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_else
(brace
id|ITRACE
c_func
(paren
id|ip2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * i_tab contains a list of pointers to inodes.  We initialize&n;&t; * the table here &amp; we&squot;ll sort it.  We will then use it to&n;&t; * order the acquisition of the inode locks.&n;&t; *&n;&t; * Note that the table may contain duplicates.  e.g., dp1 == dp2.&n;&t; */
id|i_tab
(braket
l_int|0
)braket
op_assign
id|dp1
suffix:semicolon
id|i_tab
(braket
l_int|1
)braket
op_assign
id|dp2
suffix:semicolon
id|i_tab
(braket
l_int|2
)braket
op_assign
id|ip1
suffix:semicolon
r_if
c_cond
(paren
id|inum2
op_eq
l_int|0
)paren
(brace
op_star
id|num_inodes
op_assign
l_int|3
suffix:semicolon
id|i_tab
(braket
l_int|3
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
op_star
id|num_inodes
op_assign
l_int|4
suffix:semicolon
id|i_tab
(braket
l_int|3
)braket
op_assign
id|ip2
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Sort the elements via bubble sort.  (Remember, there are at&n;&t; * most 4 elements to sort, so this is adequate.)&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
op_star
id|num_inodes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
op_star
id|num_inodes
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i_tab
(braket
id|j
)braket
op_member_access_from_pointer
id|i_ino
OL
id|i_tab
(braket
id|j
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|i_ino
)paren
(brace
id|temp
op_assign
id|i_tab
(braket
id|j
)braket
suffix:semicolon
id|i_tab
(braket
id|j
)braket
op_assign
id|i_tab
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|i_tab
(braket
id|j
op_minus
l_int|1
)braket
op_assign
id|temp
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t; * We have dp2 locked. If it isn&squot;t first, unlock it.&n;&t; * If it is first, tell xfs_lock_inodes so it can skip it&n;&t; * when locking. if dp1 == dp2, xfs_lock_inodes will skip both&n;&t; * since they are equal. xfs_lock_inodes needs all these inodes&n;&t; * so that it can unlock and retry if there might be a dead-lock&n;&t; * potential with the log.&n;&t; */
r_if
c_cond
(paren
id|i_tab
(braket
l_int|0
)braket
op_eq
id|dp2
op_logical_and
id|lock_mode
op_eq
id|XFS_ILOCK_SHARED
)paren
(brace
macro_line|#ifdef DEBUG
id|xfs_rename_skip
op_increment
suffix:semicolon
macro_line|#endif
id|xfs_lock_inodes
c_func
(paren
id|i_tab
comma
op_star
id|num_inodes
comma
l_int|1
comma
id|XFS_ILOCK_SHARED
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef DEBUG
id|xfs_rename_nskip
op_increment
suffix:semicolon
macro_line|#endif
id|xfs_iunlock_map_shared
c_func
(paren
id|dp2
comma
id|lock_mode
)paren
suffix:semicolon
id|xfs_lock_inodes
c_func
(paren
id|i_tab
comma
op_star
id|num_inodes
comma
l_int|0
comma
id|XFS_ILOCK_SHARED
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set the return value. Null out any unused entries in i_tab.&n;&t; */
op_star
id|ipp1
op_assign
op_star
id|ipp2
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
op_star
id|num_inodes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i_tab
(braket
id|i
)braket
op_member_access_from_pointer
id|i_ino
op_eq
id|inum1
)paren
(brace
op_star
id|ipp1
op_assign
id|i_tab
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i_tab
(braket
id|i
)braket
op_member_access_from_pointer
id|i_ino
op_eq
id|inum2
)paren
(brace
op_star
id|ipp2
op_assign
id|i_tab
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|i_tab
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|rename_which_error_return
r_int
id|rename_which_error_return
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * xfs_rename&n; */
r_int
DECL|function|xfs_rename
id|xfs_rename
c_func
(paren
id|bhv_desc_t
op_star
id|src_dir_bdp
comma
id|vname_t
op_star
id|src_vname
comma
id|vnode_t
op_star
id|target_dir_vp
comma
id|vname_t
op_star
id|target_vname
comma
id|cred_t
op_star
id|credp
)paren
(brace
id|xfs_trans_t
op_star
id|tp
suffix:semicolon
id|xfs_inode_t
op_star
id|src_dp
comma
op_star
id|target_dp
comma
op_star
id|src_ip
comma
op_star
id|target_ip
suffix:semicolon
id|xfs_mount_t
op_star
id|mp
suffix:semicolon
r_int
id|new_parent
suffix:semicolon
multiline_comment|/* moving to a new dir */
r_int
id|src_is_directory
suffix:semicolon
multiline_comment|/* src_name is a directory */
r_int
id|error
suffix:semicolon
id|xfs_bmap_free_t
id|free_list
suffix:semicolon
id|xfs_fsblock_t
id|first_block
suffix:semicolon
r_int
id|cancel_flags
suffix:semicolon
r_int
id|committed
suffix:semicolon
id|xfs_inode_t
op_star
id|inodes
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|target_ip_dropped
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* dropped target_ip link? */
id|vnode_t
op_star
id|src_dir_vp
suffix:semicolon
id|bhv_desc_t
op_star
id|target_dir_bdp
suffix:semicolon
r_int
id|spaceres
suffix:semicolon
r_int
id|target_link_zero
op_assign
l_int|0
suffix:semicolon
r_int
id|num_inodes
suffix:semicolon
r_char
op_star
id|src_name
op_assign
id|VNAME
c_func
(paren
id|src_vname
)paren
suffix:semicolon
r_char
op_star
id|target_name
op_assign
id|VNAME
c_func
(paren
id|target_vname
)paren
suffix:semicolon
r_int
id|src_namelen
op_assign
id|VNAMELEN
c_func
(paren
id|src_vname
)paren
suffix:semicolon
r_int
id|target_namelen
op_assign
id|VNAMELEN
c_func
(paren
id|target_vname
)paren
suffix:semicolon
id|src_dir_vp
op_assign
id|BHV_TO_VNODE
c_func
(paren
id|src_dir_bdp
)paren
suffix:semicolon
id|vn_trace_entry
c_func
(paren
id|src_dir_vp
comma
l_string|&quot;xfs_rename&quot;
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
id|vn_trace_entry
c_func
(paren
id|target_dir_vp
comma
l_string|&quot;xfs_rename&quot;
comma
(paren
id|inst_t
op_star
)paren
id|__return_address
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Find the XFS behavior descriptor for the target directory&n;&t; * vnode since it was not handed to us.&n;&t; */
id|target_dir_bdp
op_assign
id|vn_bhv_lookup_unlocked
c_func
(paren
id|VN_BHV_HEAD
c_func
(paren
id|target_dir_vp
)paren
comma
op_amp
id|xfs_vnodeops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_dir_bdp
op_eq
l_int|NULL
)paren
(brace
r_return
id|XFS_ERROR
c_func
(paren
id|EXDEV
)paren
suffix:semicolon
)brace
id|src_dp
op_assign
id|XFS_BHVTOI
c_func
(paren
id|src_dir_bdp
)paren
suffix:semicolon
id|target_dp
op_assign
id|XFS_BHVTOI
c_func
(paren
id|target_dir_bdp
)paren
suffix:semicolon
id|mp
op_assign
id|src_dp-&gt;i_mount
suffix:semicolon
r_if
c_cond
(paren
id|DM_EVENT_ENABLED
c_func
(paren
id|src_dir_vp-&gt;v_vfsp
comma
id|src_dp
comma
id|DM_EVENT_RENAME
)paren
op_logical_or
id|DM_EVENT_ENABLED
c_func
(paren
id|target_dir_vp-&gt;v_vfsp
comma
id|target_dp
comma
id|DM_EVENT_RENAME
)paren
)paren
(brace
id|error
op_assign
id|XFS_SEND_NAMESP
c_func
(paren
id|mp
comma
id|DM_EVENT_RENAME
comma
id|src_dir_vp
comma
id|DM_RIGHT_NULL
comma
id|target_dir_vp
comma
id|DM_RIGHT_NULL
comma
id|src_name
comma
id|target_name
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_return
id|error
suffix:semicolon
)brace
)brace
multiline_comment|/* Return through std_return after this point. */
multiline_comment|/*&n;&t; * Lock all the participating inodes. Depending upon whether&n;&t; * the target_name exists in the target directory, and&n;&t; * whether the target directory is the same as the source&n;&t; * directory, we can lock from 2 to 4 inodes.&n;&t; * xfs_lock_for_rename() will return ENOENT if src_name&n;&t; * does not exist in the source directory.&n;&t; */
id|tp
op_assign
l_int|NULL
suffix:semicolon
id|error
op_assign
id|xfs_lock_for_rename
c_func
(paren
id|src_dp
comma
id|target_dp
comma
id|src_vname
comma
id|target_vname
comma
op_amp
id|src_ip
comma
op_amp
id|target_ip
comma
id|inodes
comma
op_amp
id|num_inodes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We have nothing locked, no inode references, and&n;&t;&t; * no transaction, so just get out.&n;&t;&t; */
r_goto
id|std_return
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|src_ip
op_ne
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|src_ip-&gt;i_d.di_mode
op_amp
id|S_IFMT
)paren
op_eq
id|S_IFDIR
)paren
(brace
multiline_comment|/*&n;&t;&t; * Check for link count overflow on target_dp&n;&t;&t; */
r_if
c_cond
(paren
id|target_ip
op_eq
l_int|NULL
op_logical_and
(paren
id|src_dp
op_ne
id|target_dp
)paren
op_logical_and
id|target_dp-&gt;i_d.di_nlink
op_ge
id|XFS_MAXLINK
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
id|error
op_assign
id|XFS_ERROR
c_func
(paren
id|EMLINK
)paren
suffix:semicolon
id|xfs_rename_unlock4
c_func
(paren
id|inodes
comma
id|XFS_ILOCK_SHARED
)paren
suffix:semicolon
r_goto
id|rele_return
suffix:semicolon
)brace
)brace
id|new_parent
op_assign
(paren
id|src_dp
op_ne
id|target_dp
)paren
suffix:semicolon
id|src_is_directory
op_assign
(paren
(paren
id|src_ip-&gt;i_d.di_mode
op_amp
id|S_IFMT
)paren
op_eq
id|S_IFDIR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Drop the locks on our inodes so that we can start the transaction.&n;&t; */
id|xfs_rename_unlock4
c_func
(paren
id|inodes
comma
id|XFS_ILOCK_SHARED
)paren
suffix:semicolon
id|XFS_BMAP_INIT
c_func
(paren
op_amp
id|free_list
comma
op_amp
id|first_block
)paren
suffix:semicolon
id|tp
op_assign
id|xfs_trans_alloc
c_func
(paren
id|mp
comma
id|XFS_TRANS_RENAME
)paren
suffix:semicolon
id|cancel_flags
op_assign
id|XFS_TRANS_RELEASE_LOG_RES
suffix:semicolon
id|spaceres
op_assign
id|XFS_RENAME_SPACE_RES
c_func
(paren
id|mp
comma
id|target_namelen
)paren
suffix:semicolon
id|error
op_assign
id|xfs_trans_reserve
c_func
(paren
id|tp
comma
id|spaceres
comma
id|XFS_RENAME_LOG_RES
c_func
(paren
id|mp
)paren
comma
l_int|0
comma
id|XFS_TRANS_PERM_LOG_RES
comma
id|XFS_RENAME_LOG_COUNT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
id|ENOSPC
)paren
(brace
id|spaceres
op_assign
l_int|0
suffix:semicolon
id|error
op_assign
id|xfs_trans_reserve
c_func
(paren
id|tp
comma
l_int|0
comma
id|XFS_RENAME_LOG_RES
c_func
(paren
id|mp
)paren
comma
l_int|0
comma
id|XFS_TRANS_PERM_LOG_RES
comma
id|XFS_RENAME_LOG_COUNT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|rele_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Attach the dquots to the inodes&n;&t; */
r_if
c_cond
(paren
(paren
id|error
op_assign
id|XFS_QM_DQVOPRENAME
c_func
(paren
id|mp
comma
id|inodes
)paren
)paren
)paren
(brace
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
id|cancel_flags
)paren
suffix:semicolon
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|rele_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Reacquire the inode locks we dropped above.&n;&t; */
id|xfs_lock_inodes
c_func
(paren
id|inodes
comma
id|num_inodes
comma
l_int|0
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Join all the inodes to the transaction. From this point on,&n;&t; * we can rely on either trans_commit or trans_cancel to unlock&n;&t; * them.  Note that we need to add a vnode reference to the&n;&t; * directories since trans_commit &amp; trans_cancel will decrement&n;&t; * them when they unlock the inodes.  Also, we need to be careful&n;&t; * not to add an inode to the transaction more than once.&n;&t; */
id|VN_HOLD
c_func
(paren
id|src_dir_vp
)paren
suffix:semicolon
id|xfs_trans_ijoin
c_func
(paren
id|tp
comma
id|src_dp
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_parent
)paren
(brace
id|VN_HOLD
c_func
(paren
id|target_dir_vp
)paren
suffix:semicolon
id|xfs_trans_ijoin
c_func
(paren
id|tp
comma
id|target_dp
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|src_ip
op_ne
id|src_dp
)paren
op_logical_and
(paren
id|src_ip
op_ne
id|target_dp
)paren
)paren
(brace
id|xfs_trans_ijoin
c_func
(paren
id|tp
comma
id|src_ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|target_ip
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|target_ip
op_ne
id|src_ip
)paren
op_logical_and
(paren
id|target_ip
op_ne
id|src_dp
)paren
op_logical_and
(paren
id|target_ip
op_ne
id|target_dp
)paren
)paren
(brace
id|xfs_trans_ijoin
c_func
(paren
id|tp
comma
id|target_ip
comma
id|XFS_ILOCK_EXCL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set up the target.&n;&t; */
r_if
c_cond
(paren
id|target_ip
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * If there&squot;s no space reservation, check the entry will&n;&t;&t; * fit before actually inserting it.&n;&t;&t; */
r_if
c_cond
(paren
id|spaceres
op_eq
l_int|0
op_logical_and
(paren
id|error
op_assign
id|XFS_DIR_CANENTER
c_func
(paren
id|mp
comma
id|tp
comma
id|target_dp
comma
id|target_name
comma
id|target_namelen
)paren
)paren
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|error_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If target does not exist and the rename crosses&n;&t;&t; * directories, adjust the target directory link count&n;&t;&t; * to account for the &quot;..&quot; reference from the new entry.&n;&t;&t; */
id|error
op_assign
id|XFS_DIR_CREATENAME
c_func
(paren
id|mp
comma
id|tp
comma
id|target_dp
comma
id|target_name
comma
id|target_namelen
comma
id|src_ip-&gt;i_ino
comma
op_amp
id|first_block
comma
op_amp
id|free_list
comma
id|spaceres
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
id|ENOSPC
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|error_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|abort_return
suffix:semicolon
)brace
id|xfs_ichgtime
c_func
(paren
id|target_dp
comma
id|XFS_ICHGTIME_MOD
op_or
id|XFS_ICHGTIME_CHG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_parent
op_logical_and
id|src_is_directory
)paren
(brace
id|error
op_assign
id|xfs_bumplink
c_func
(paren
id|tp
comma
id|target_dp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|abort_return
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/* target_ip != NULL */
multiline_comment|/*&n;&t;&t; * If target exists and it&squot;s a directory, check that both&n;&t;&t; * target and source are directories and that target can be&n;&t;&t; * destroyed, or that neither is a directory.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|target_ip-&gt;i_d.di_mode
op_amp
id|S_IFMT
)paren
op_eq
id|S_IFDIR
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Make sure target dir is empty.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|XFS_DIR_ISEMPTY
c_func
(paren
id|target_ip-&gt;i_mount
comma
id|target_ip
)paren
)paren
op_logical_or
(paren
id|target_ip-&gt;i_d.di_nlink
OG
l_int|2
)paren
)paren
(brace
id|error
op_assign
id|XFS_ERROR
c_func
(paren
id|EEXIST
)paren
suffix:semicolon
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|error_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Link the source inode under the target name.&n;&t;&t; * If the source inode is a directory and we are moving&n;&t;&t; * it across directories, its &quot;..&quot; entry will be&n;&t;&t; * inconsistent until we replace that down below.&n;&t;&t; *&n;&t;&t; * In case there is already an entry with the same&n;&t;&t; * name at the destination directory, remove it first.&n;&t;&t; */
id|error
op_assign
id|XFS_DIR_REPLACE
c_func
(paren
id|mp
comma
id|tp
comma
id|target_dp
comma
id|target_name
comma
id|target_namelen
comma
id|src_ip-&gt;i_ino
comma
op_amp
id|first_block
comma
op_amp
id|free_list
comma
id|spaceres
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|abort_return
suffix:semicolon
)brace
id|xfs_ichgtime
c_func
(paren
id|target_dp
comma
id|XFS_ICHGTIME_MOD
op_or
id|XFS_ICHGTIME_CHG
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Decrement the link count on the target since the target&n;&t;&t; * dir no longer points to it.&n;&t;&t; */
id|error
op_assign
id|xfs_droplink
c_func
(paren
id|tp
comma
id|target_ip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|abort_return
suffix:semicolon
)brace
id|target_ip_dropped
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|src_is_directory
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Drop the link from the old &quot;.&quot; entry.&n;&t;&t;&t; */
id|error
op_assign
id|xfs_droplink
c_func
(paren
id|tp
comma
id|target_ip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|abort_return
suffix:semicolon
)brace
)brace
multiline_comment|/* Do this test while we still hold the locks */
id|target_link_zero
op_assign
(paren
id|target_ip
)paren
op_member_access_from_pointer
id|i_d.di_nlink
op_eq
l_int|0
suffix:semicolon
)brace
multiline_comment|/* target_ip != NULL */
multiline_comment|/*&n;&t; * Remove the source.&n;&t; */
r_if
c_cond
(paren
id|new_parent
op_logical_and
id|src_is_directory
)paren
(brace
multiline_comment|/*&n;&t;&t; * Rewrite the &quot;..&quot; entry to point to the new&n;&t;&t; * directory.&n;&t;&t; */
id|error
op_assign
id|XFS_DIR_REPLACE
c_func
(paren
id|mp
comma
id|tp
comma
id|src_ip
comma
l_string|&quot;..&quot;
comma
l_int|2
comma
id|target_dp-&gt;i_ino
comma
op_amp
id|first_block
comma
op_amp
id|free_list
comma
id|spaceres
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|error
op_ne
id|EEXIST
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|abort_return
suffix:semicolon
)brace
id|xfs_ichgtime
c_func
(paren
id|src_ip
comma
id|XFS_ICHGTIME_MOD
op_or
id|XFS_ICHGTIME_CHG
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * We always want to hit the ctime on the source inode.&n;&t;&t; * We do it in the if clause above for the &squot;new_parent &amp;&amp;&n;&t;&t; * src_is_directory&squot; case, and here we get all the other&n;&t;&t; * cases.  This isn&squot;t strictly required by the standards&n;&t;&t; * since the source inode isn&squot;t really being changed,&n;&t;&t; * but old unix file systems did it and some incremental&n;&t;&t; * backup programs won&squot;t work without it.&n;&t;&t; */
id|xfs_ichgtime
c_func
(paren
id|src_ip
comma
id|XFS_ICHGTIME_CHG
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Adjust the link count on src_dp.  This is necessary when&n;&t; * renaming a directory, either within one parent when&n;&t; * the target existed, or across two parent directories.&n;&t; */
r_if
c_cond
(paren
id|src_is_directory
op_logical_and
(paren
id|new_parent
op_logical_or
id|target_ip
op_ne
l_int|NULL
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Decrement link count on src_directory since the&n;&t;&t; * entry that&squot;s moved no longer points to it.&n;&t;&t; */
id|error
op_assign
id|xfs_droplink
c_func
(paren
id|tp
comma
id|src_dp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|abort_return
suffix:semicolon
)brace
)brace
id|error
op_assign
id|XFS_DIR_REMOVENAME
c_func
(paren
id|mp
comma
id|tp
comma
id|src_dp
comma
id|src_name
comma
id|src_namelen
comma
id|src_ip-&gt;i_ino
comma
op_amp
id|first_block
comma
op_amp
id|free_list
comma
id|spaceres
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|rename_which_error_return
op_assign
id|__LINE__
suffix:semicolon
r_goto
id|abort_return
suffix:semicolon
)brace
id|xfs_ichgtime
c_func
(paren
id|src_dp
comma
id|XFS_ICHGTIME_MOD
op_or
id|XFS_ICHGTIME_CHG
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Update the generation counts on all the directory inodes&n;&t; * that we&squot;re modifying.&n;&t; */
id|src_dp-&gt;i_gen
op_increment
suffix:semicolon
id|xfs_trans_log_inode
c_func
(paren
id|tp
comma
id|src_dp
comma
id|XFS_ILOG_CORE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_parent
)paren
(brace
id|target_dp-&gt;i_gen
op_increment
suffix:semicolon
id|xfs_trans_log_inode
c_func
(paren
id|tp
comma
id|target_dp
comma
id|XFS_ILOG_CORE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If there was a target inode, take an extra reference on&n;&t; * it here so that it doesn&squot;t go to xfs_inactive() from&n;&t; * within the commit.&n;&t; */
r_if
c_cond
(paren
id|target_ip
op_ne
l_int|NULL
)paren
(brace
id|IHOLD
c_func
(paren
id|target_ip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If this is a synchronous mount, make sure that the&n;&t; * rename transaction goes to disk before returning to&n;&t; * the user.&n;&t; */
r_if
c_cond
(paren
id|mp-&gt;m_flags
op_amp
(paren
id|XFS_MOUNT_WSYNC
op_or
id|XFS_MOUNT_DIRSYNC
)paren
)paren
(brace
id|xfs_trans_set_sync
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Take refs. for vop_link_removed calls below.  No need to worry&n;&t; * about directory refs. because the caller holds them.&n;&t; *&n;&t; * Do holds before the xfs_bmap_finish since it might rele them down&n;&t; * to zero.&n;&t; */
r_if
c_cond
(paren
id|target_ip_dropped
)paren
id|IHOLD
c_func
(paren
id|target_ip
)paren
suffix:semicolon
id|IHOLD
c_func
(paren
id|src_ip
)paren
suffix:semicolon
id|error
op_assign
id|xfs_bmap_finish
c_func
(paren
op_amp
id|tp
comma
op_amp
id|free_list
comma
id|first_block
comma
op_amp
id|committed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|xfs_bmap_cancel
c_func
(paren
op_amp
id|free_list
)paren
suffix:semicolon
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
(paren
id|XFS_TRANS_RELEASE_LOG_RES
op_or
id|XFS_TRANS_ABORT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_ip
op_ne
l_int|NULL
)paren
(brace
id|IRELE
c_func
(paren
id|target_ip
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|target_ip_dropped
)paren
(brace
id|IRELE
c_func
(paren
id|target_ip
)paren
suffix:semicolon
)brace
id|IRELE
c_func
(paren
id|src_ip
)paren
suffix:semicolon
r_goto
id|std_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * trans_commit will unlock src_ip, target_ip &amp; decrement&n;&t; * the vnode references.&n;&t; */
id|error
op_assign
id|xfs_trans_commit
c_func
(paren
id|tp
comma
id|XFS_TRANS_RELEASE_LOG_RES
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_ip
op_ne
l_int|NULL
)paren
(brace
id|xfs_refcache_purge_ip
c_func
(paren
id|target_ip
)paren
suffix:semicolon
id|IRELE
c_func
(paren
id|target_ip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Let interposed file systems know about removed links.&n;&t; */
r_if
c_cond
(paren
id|target_ip_dropped
)paren
(brace
id|VOP_LINK_REMOVED
c_func
(paren
id|XFS_ITOV
c_func
(paren
id|target_ip
)paren
comma
id|target_dir_vp
comma
id|target_link_zero
)paren
suffix:semicolon
id|IRELE
c_func
(paren
id|target_ip
)paren
suffix:semicolon
)brace
id|FSC_NOTIFY_NAME_CHANGED
c_func
(paren
id|XFS_ITOV
c_func
(paren
id|src_ip
)paren
)paren
suffix:semicolon
id|IRELE
c_func
(paren
id|src_ip
)paren
suffix:semicolon
multiline_comment|/* Fall through to std_return with error = 0 or errno from&n;&t; * xfs_trans_commit&t; */
id|std_return
suffix:colon
r_if
c_cond
(paren
id|DM_EVENT_ENABLED
c_func
(paren
id|src_dir_vp-&gt;v_vfsp
comma
id|src_dp
comma
id|DM_EVENT_POSTRENAME
)paren
op_logical_or
id|DM_EVENT_ENABLED
c_func
(paren
id|target_dir_vp-&gt;v_vfsp
comma
id|target_dp
comma
id|DM_EVENT_POSTRENAME
)paren
)paren
(brace
(paren
r_void
)paren
id|XFS_SEND_NAMESP
(paren
id|mp
comma
id|DM_EVENT_POSTRENAME
comma
id|src_dir_vp
comma
id|DM_RIGHT_NULL
comma
id|target_dir_vp
comma
id|DM_RIGHT_NULL
comma
id|src_name
comma
id|target_name
comma
l_int|0
comma
id|error
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
id|abort_return
suffix:colon
id|cancel_flags
op_or_assign
id|XFS_TRANS_ABORT
suffix:semicolon
multiline_comment|/* FALLTHROUGH */
id|error_return
suffix:colon
id|xfs_bmap_cancel
c_func
(paren
op_amp
id|free_list
)paren
suffix:semicolon
id|xfs_trans_cancel
c_func
(paren
id|tp
comma
id|cancel_flags
)paren
suffix:semicolon
r_goto
id|std_return
suffix:semicolon
id|rele_return
suffix:colon
id|IRELE
c_func
(paren
id|src_ip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_ip
op_ne
l_int|NULL
)paren
(brace
id|IRELE
c_func
(paren
id|target_ip
)paren
suffix:semicolon
)brace
r_goto
id|std_return
suffix:semicolon
)brace
eof
