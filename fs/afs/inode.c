multiline_comment|/*&n; * Copyright (c) 2002 Red Hat, Inc. All rights reserved.&n; *&n; * This software may be freely redistributed under the terms of the&n; * GNU General Public License.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Authors: David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&n; *          David Howells &lt;dhowells@redhat.com&gt;&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &quot;volume.h&quot;
macro_line|#include &quot;vnode.h&quot;
macro_line|#include &quot;super.h&quot;
macro_line|#include &quot;internal.h&quot;
DECL|struct|afs_iget_data
r_struct
id|afs_iget_data
(brace
DECL|member|fid
r_struct
id|afs_fid
id|fid
suffix:semicolon
DECL|member|volume
r_struct
id|afs_volume
op_star
id|volume
suffix:semicolon
multiline_comment|/* volume on which resides */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * map the AFS file status to the inode member variables&n; */
DECL|function|afs_inode_map_status
r_static
r_int
id|afs_inode_map_status
c_func
(paren
r_struct
id|afs_vnode
op_star
id|vnode
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|AFS_VNODE_TO_I
c_func
(paren
id|vnode
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;FS: ft=%d lk=%d sz=%Zu ver=%Lu mod=%hu&quot;
comma
id|vnode-&gt;status.type
comma
id|vnode-&gt;status.nlink
comma
id|vnode-&gt;status.size
comma
id|vnode-&gt;status.version
comma
id|vnode-&gt;status.mode
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|vnode-&gt;status.type
)paren
(brace
r_case
id|AFS_FTYPE_FILE
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFREG
op_or
id|vnode-&gt;status.mode
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|afs_file_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|afs_file_file_operations
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFS_FTYPE_DIR
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|vnode-&gt;status.mode
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|afs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|afs_dir_file_operations
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFS_FTYPE_SYMLINK
suffix:colon
id|inode-&gt;i_mode
op_assign
id|S_IFLNK
op_or
id|vnode-&gt;status.mode
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;kAFS: AFS vnode with undefined type&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBADMSG
suffix:semicolon
)brace
id|inode-&gt;i_nlink
op_assign
id|vnode-&gt;status.nlink
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|vnode-&gt;status.owner
suffix:semicolon
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|vnode-&gt;status.size
suffix:semicolon
id|inode-&gt;i_ctime.tv_sec
op_assign
id|vnode-&gt;status.mtime_server
suffix:semicolon
id|inode-&gt;i_ctime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_version
op_assign
id|vnode-&gt;fid.unique
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|afs_fs_aops
suffix:semicolon
multiline_comment|/* check to see whether a symbolic link is really a mountpoint */
r_if
c_cond
(paren
id|vnode-&gt;status.type
op_eq
id|AFS_FTYPE_SYMLINK
)paren
(brace
id|afs_mntpt_check_symlink
c_func
(paren
id|vnode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vnode-&gt;flags
op_amp
id|AFS_VNODE_MOUNTPOINT
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|vnode-&gt;status.mode
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|afs_mntpt_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|afs_mntpt_file_operations
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end afs_inode_map_status() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * attempt to fetch the status of an inode, coelescing multiple simultaneous fetches&n; */
DECL|function|afs_inode_fetch_status
r_int
id|afs_inode_fetch_status
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|afs_vnode
op_star
id|vnode
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|vnode
op_assign
id|AFS_FS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ret
op_assign
id|afs_vnode_fetch_status
c_func
(paren
id|vnode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|afs_inode_map_status
c_func
(paren
id|vnode
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_inode_fetch_status() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * iget5() comparator&n; */
DECL|function|afs_iget5_test
r_static
r_int
id|afs_iget5_test
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_void
op_star
id|opaque
)paren
(brace
r_struct
id|afs_iget_data
op_star
id|data
op_assign
id|opaque
suffix:semicolon
r_return
id|inode-&gt;i_ino
op_eq
id|data-&gt;fid.vnode
op_logical_and
id|inode-&gt;i_version
op_eq
id|data-&gt;fid.unique
suffix:semicolon
)brace
multiline_comment|/* end afs_iget5_test() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * iget5() inode initialiser&n; */
DECL|function|afs_iget5_set
r_static
r_int
id|afs_iget5_set
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_void
op_star
id|opaque
)paren
(brace
r_struct
id|afs_iget_data
op_star
id|data
op_assign
id|opaque
suffix:semicolon
r_struct
id|afs_vnode
op_star
id|vnode
op_assign
id|AFS_FS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|data-&gt;fid.vnode
suffix:semicolon
id|inode-&gt;i_version
op_assign
id|data-&gt;fid.unique
suffix:semicolon
id|vnode-&gt;fid
op_assign
id|data-&gt;fid
suffix:semicolon
id|vnode-&gt;volume
op_assign
id|data-&gt;volume
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end afs_iget5_set() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * inode retrieval&n; */
DECL|function|afs_iget
r_inline
r_int
id|afs_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|afs_fid
op_star
id|fid
comma
r_struct
id|inode
op_star
op_star
id|_inode
)paren
(brace
r_struct
id|afs_iget_data
id|data
op_assign
(brace
dot
id|fid
op_assign
op_star
id|fid
)brace
suffix:semicolon
r_struct
id|afs_super_info
op_star
id|as
suffix:semicolon
r_struct
id|afs_vnode
op_star
id|vnode
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;,{%u,%u,%u},,&quot;
comma
id|fid-&gt;vid
comma
id|fid-&gt;vnode
comma
id|fid-&gt;unique
)paren
suffix:semicolon
id|as
op_assign
id|sb-&gt;s_fs_info
suffix:semicolon
id|data.volume
op_assign
id|as-&gt;volume
suffix:semicolon
id|inode
op_assign
id|iget5_locked
c_func
(paren
id|sb
comma
id|fid-&gt;vnode
comma
id|afs_iget5_test
comma
id|afs_iget5_set
comma
op_amp
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = -ENOMEM&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|vnode
op_assign
id|AFS_FS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* deal with an existing inode */
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_state
op_amp
id|I_NEW
)paren
)paren
(brace
id|ret
op_assign
id|afs_vnode_fetch_status
c_func
(paren
id|vnode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
op_star
id|_inode
op_assign
id|inode
suffix:semicolon
r_else
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifdef AFS_CACHING_SUPPORT
multiline_comment|/* set up caching before reading the status, as fetch-status reads the&n;&t; * first page of symlinks to see if they&squot;re really mntpts */
id|cachefs_acquire_cookie
c_func
(paren
id|vnode-&gt;volume-&gt;cache
comma
l_int|NULL
comma
id|vnode
comma
op_amp
id|vnode-&gt;cache
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* okay... it&squot;s a new inode */
id|vnode-&gt;flags
op_or_assign
id|AFS_VNODE_CHANGED
suffix:semicolon
id|ret
op_assign
id|afs_inode_fetch_status
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|bad_inode
suffix:semicolon
multiline_comment|/* success */
id|unlock_new_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
op_star
id|_inode
op_assign
id|inode
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = 0 [CB { v=%u x=%lu t=%u }]&quot;
comma
id|vnode-&gt;cb_version
comma
id|vnode-&gt;cb_timeout.timo_jif
comma
id|vnode-&gt;cb_type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* failure */
id|bad_inode
suffix:colon
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_new_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d [bad]&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_iget() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * read the attributes of an inode&n; */
DECL|function|afs_inode_getattr
r_int
id|afs_inode_getattr
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|kstat
op_star
id|stat
)paren
(brace
r_struct
id|afs_vnode
op_star
id|vnode
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{ ino=%lu v=%lu }&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_version
)paren
suffix:semicolon
id|vnode
op_assign
id|AFS_FS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ret
op_assign
id|afs_inode_fetch_status
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENOENT
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = %d [%d %p]&quot;
comma
id|ret
comma
id|atomic_read
c_func
(paren
op_amp
id|dentry-&gt;d_count
)paren
comma
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* transfer attributes from the inode structure to the stat&n;&t; * structure */
id|generic_fillattr
c_func
(paren
id|inode
comma
id|stat
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = 0 CB { v=%u x=%u t=%u }&quot;
comma
id|vnode-&gt;cb_version
comma
id|vnode-&gt;cb_expiry
comma
id|vnode-&gt;cb_type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end afs_inode_getattr() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clear an AFS inode&n; */
DECL|function|afs_clear_inode
r_void
id|afs_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|afs_vnode
op_star
id|vnode
suffix:semicolon
id|vnode
op_assign
id|AFS_FS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;ino=%lu { vn=%08x v=%u x=%u t=%u }&quot;
comma
id|inode-&gt;i_ino
comma
id|vnode-&gt;fid.vnode
comma
id|vnode-&gt;cb_version
comma
id|vnode-&gt;cb_expiry
comma
id|vnode-&gt;cb_type
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|inode-&gt;i_ino
op_ne
id|vnode-&gt;fid.vnode
)paren
suffix:semicolon
id|afs_vnode_give_up_callback
c_func
(paren
id|vnode
)paren
suffix:semicolon
macro_line|#ifdef AFS_CACHING_SUPPORT
id|cachefs_relinquish_cookie
c_func
(paren
id|vnode-&gt;cache
comma
l_int|0
)paren
suffix:semicolon
id|vnode-&gt;cache
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_clear_inode() */
eof
