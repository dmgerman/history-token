multiline_comment|/*&n; *  linux/fs/umsdos/inode.c&n; *&n; *      Written 1993 by Jacques Gelinas&n; *      Inspired from linux/fs/msdos/... by Werner Almesberger&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/umsdos_fs.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
r_extern
r_struct
id|dentry_operations
id|umsdos_dentry_operations
suffix:semicolon
DECL|variable|saved_root
r_struct
id|dentry
op_star
id|saved_root
suffix:semicolon
multiline_comment|/* Original root if changed */
DECL|variable|pseudo_root
r_struct
id|inode
op_star
id|pseudo_root
suffix:semicolon
multiline_comment|/* Useful to simulate the pseudo DOS */
multiline_comment|/* directory. See UMSDOS_readdir_x() */
r_static
r_struct
id|dentry
op_star
id|check_pseudo_root
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
DECL|function|UMSDOS_put_inode
r_void
id|UMSDOS_put_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|PRINTK
(paren
(paren
id|KERN_DEBUG
l_string|&quot;put inode %p (%lu) pos %lu count=%d&bslash;n&quot;
comma
id|inode
comma
id|inode-&gt;i_ino
comma
id|UMSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|pos
comma
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
id|pseudo_root
)paren
(brace
id|Printk
(paren
(paren
id|KERN_ERR
l_string|&quot;Umsdos: debug: releasing pseudo_root - ino=%lu count=%d&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
op_eq
l_int|1
)paren
id|UMSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_patched
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|UMSDOS_put_super
r_void
id|UMSDOS_put_super
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|Printk
(paren
(paren
id|KERN_DEBUG
l_string|&quot;UMSDOS_put_super: entering&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved_root
op_logical_and
id|pseudo_root
op_logical_and
id|kdev_same
c_func
(paren
id|sb-&gt;s_dev
comma
id|ROOT_DEV
)paren
)paren
(brace
id|shrink_dcache_parent
c_func
(paren
id|saved_root
)paren
suffix:semicolon
id|dput
c_func
(paren
id|saved_root
)paren
suffix:semicolon
id|saved_root
op_assign
l_int|NULL
suffix:semicolon
id|pseudo_root
op_assign
l_int|NULL
suffix:semicolon
)brace
id|fat_put_super
(paren
id|sb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Complete the setup of a directory dentry based on its&n; * EMD/non-EMD status.  If it has an EMD, then plug the&n; * umsdos function table. If not, use the msdos one.&n; */
DECL|function|umsdos_setup_dir
r_void
id|umsdos_setup_dir
c_func
(paren
r_struct
id|dentry
op_star
id|dir
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dir-&gt;d_inode
suffix:semicolon
r_struct
id|umsdos_inode_info
op_star
id|ui
op_assign
id|UMSDOS_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;umsdos_setup_dir: %s/%s not a dir!&bslash;n&quot;
comma
id|dir-&gt;d_parent-&gt;d_name.name
comma
id|dir-&gt;d_name.name
)paren
suffix:semicolon
id|init_waitqueue_head
(paren
op_amp
id|ui-&gt;dir_info.p
)paren
suffix:semicolon
id|ui-&gt;dir_info.looking
op_assign
l_int|0
suffix:semicolon
id|ui-&gt;dir_info.creating
op_assign
l_int|0
suffix:semicolon
id|ui-&gt;dir_info.pid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|umsdos_rdir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|umsdos_rdir_operations
suffix:semicolon
r_if
c_cond
(paren
id|umsdos_have_emd
c_func
(paren
id|dir
)paren
)paren
(brace
id|Printk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;umsdos_setup_dir: %s/%s using EMD&bslash;n&quot;
comma
id|dir-&gt;d_parent-&gt;d_name.name
comma
id|dir-&gt;d_name.name
)paren
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|umsdos_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|umsdos_dir_operations
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Add some info into an inode so it can find its owner quickly&n; */
DECL|function|umsdos_set_dirinfo_new
r_void
id|umsdos_set_dirinfo_new
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|off_t
id|f_pos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|dentry
op_star
id|demd
suffix:semicolon
id|UMSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|pos
op_assign
id|f_pos
suffix:semicolon
multiline_comment|/* now check the EMD file */
id|demd
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|dentry-&gt;d_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|demd
)paren
)paren
(brace
id|dput
c_func
(paren
id|demd
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|variable|umsdos_file_inode_operations
r_static
r_struct
id|inode_operations
id|umsdos_file_inode_operations
op_assign
(brace
id|truncate
suffix:colon
id|fat_truncate
comma
id|setattr
suffix:colon
id|UMSDOS_notify_change
comma
)brace
suffix:semicolon
DECL|variable|umsdos_symlink_inode_operations
r_static
r_struct
id|inode_operations
id|umsdos_symlink_inode_operations
op_assign
(brace
id|readlink
suffix:colon
id|page_readlink
comma
id|follow_link
suffix:colon
id|page_follow_link
comma
id|setattr
suffix:colon
id|UMSDOS_notify_change
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Connect the proper tables in the inode and add some info.&n; */
multiline_comment|/* #Specification: inode / umsdos info&n; * The first time an inode is seen (inode-&gt;i_count == 1),&n; * the inode number of the EMD file which controls this inode&n; * is tagged to this inode. It allows operations such as&n; * notify_change to be handled.&n; */
DECL|function|umsdos_patch_dentry_inode
r_void
id|umsdos_patch_dentry_inode
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|off_t
id|f_pos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|PRINTK
(paren
(paren
l_string|&quot;umsdos_patch_dentry_inode: inode=%lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Classify the inode based on EMD/non-EMD status.&n;&t; */
id|PRINTK
(paren
(paren
l_string|&quot;umsdos_patch_inode: call umsdos_set_dirinfo_new(%p,%lu)&bslash;n&quot;
comma
id|dentry
comma
id|f_pos
)paren
)paren
suffix:semicolon
id|umsdos_set_dirinfo_new
c_func
(paren
id|dentry
comma
id|f_pos
)paren
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|umsdos_file_inode_operations
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
multiline_comment|/* address_space operations already set */
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|umsdos_setup_dir
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
multiline_comment|/* address_space operations already set */
id|inode-&gt;i_op
op_assign
op_amp
id|umsdos_symlink_inode_operations
suffix:semicolon
)brace
r_else
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * lock the parent dir before starting ...&n; * also handles hardlink converting&n; */
DECL|function|UMSDOS_notify_change
r_int
id|UMSDOS_notify_change
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_struct
id|inode
op_star
id|dir
comma
op_star
id|inode
suffix:semicolon
r_struct
id|umsdos_info
id|info
suffix:semicolon
r_struct
id|dentry
op_star
id|temp
comma
op_star
id|old_dentry
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|umsdos_parse
(paren
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
comma
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|umsdos_findentry
(paren
id|dentry-&gt;d_parent
comma
op_amp
id|info
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;UMSDOS_notify_change: %s/%s not in EMD, ret=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info.entry.flags
op_amp
id|UMSDOS_HLINK
)paren
(brace
multiline_comment|/*&n;&t;&t; * In order to get the correct (real) inode, we just drop&n;&t;&t; * the original dentry.&n;&t;&t; */
id|d_drop
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|Printk
c_func
(paren
(paren
l_string|&quot;UMSDOS_notify_change: hard link %s/%s, fake=%s&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|info.fake.fname
)paren
)paren
suffix:semicolon
multiline_comment|/* Do a real lookup to get the short name dentry */
id|temp
op_assign
id|umsdos_covered
c_func
(paren
id|dentry-&gt;d_parent
comma
id|info.fake.fname
comma
id|info.fake.len
)paren
suffix:semicolon
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|temp
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* now resolve the link ... */
id|temp
op_assign
id|umsdos_solve_hlink
c_func
(paren
id|temp
)paren
suffix:semicolon
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|temp
)paren
)paren
r_goto
id|out
suffix:semicolon
id|old_dentry
op_assign
id|dentry
suffix:semicolon
id|dentry
op_assign
id|temp
suffix:semicolon
multiline_comment|/* so umsdos_notify_change_locked will operate on that */
)brace
id|dir
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|ret
op_assign
id|inode_change_ok
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|umsdos_notify_change_locked
c_func
(paren
id|dentry
comma
id|attr
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
id|inode_setattr
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|old_dentry
)paren
id|dput
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/* if we had to use fake dentry for hardlinks, dput() it now */
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Must be called with the parent lock held.&n; */
DECL|function|umsdos_notify_change_locked
r_int
id|umsdos_notify_change_locked
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|dentry
op_star
id|demd
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|umsdos_dirent
op_star
id|entry
suffix:semicolon
r_int
id|offs
suffix:semicolon
id|Printk
c_func
(paren
(paren
l_string|&quot;UMSDOS_notify_change: entering for %s/%s (%d)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|UMSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_patched
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_nlink
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|UMSDOS_ROOT_INO
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* get the EMD file dentry */
id|demd
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|dentry-&gt;d_parent
)paren
suffix:semicolon
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|demd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|demd
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* don&squot;t do anything if directory is not promoted to umsdos yet */
r_if
c_cond
(paren
op_logical_neg
id|demd-&gt;d_inode
)paren
(brace
id|Printk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;UMSDOS_notify_change: no EMD file %s/%s&bslash;n&quot;
comma
id|demd-&gt;d_parent-&gt;d_name.name
comma
id|demd-&gt;d_name.name
)paren
)paren
suffix:semicolon
r_goto
id|out_dput
suffix:semicolon
)brace
multiline_comment|/* don&squot;t do anything if this is the EMD itself */
r_if
c_cond
(paren
id|inode
op_eq
id|demd-&gt;d_inode
)paren
r_goto
id|out_dput
suffix:semicolon
multiline_comment|/* This inode is not a EMD file nor an inode used internally&n;&t; * by MSDOS, so we can update its status.&n;&t; * See emd.c&n;&t; */
multiline_comment|/* Read only the start of the entry since we don&squot;t touch the name */
id|mapping
op_assign
id|demd-&gt;d_inode-&gt;i_mapping
suffix:semicolon
id|offs
op_assign
id|UMSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|pos
op_amp
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|page
op_assign
id|grab_cache_page
c_func
(paren
id|mapping
comma
id|UMSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|pos
op_rshift
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_goto
id|out_dput
suffix:semicolon
id|ret
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|offs
comma
id|offs
op_plus
id|UMSDOS_REC_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out_unlock
suffix:semicolon
id|entry
op_assign
(paren
r_struct
id|umsdos_dirent
op_star
)paren
(paren
id|page_address
c_func
(paren
id|page
)paren
op_plus
id|offs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_UID
)paren
id|entry-&gt;uid
op_assign
id|cpu_to_le16
c_func
(paren
id|attr-&gt;ia_uid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_GID
)paren
id|entry-&gt;gid
op_assign
id|cpu_to_le16
c_func
(paren
id|attr-&gt;ia_gid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
id|entry-&gt;mode
op_assign
id|cpu_to_le16
c_func
(paren
id|attr-&gt;ia_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_ATIME
)paren
id|entry-&gt;atime
op_assign
id|cpu_to_le32
c_func
(paren
id|attr-&gt;ia_atime
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MTIME
)paren
id|entry-&gt;mtime
op_assign
id|cpu_to_le32
c_func
(paren
id|attr-&gt;ia_mtime
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_CTIME
)paren
id|entry-&gt;ctime
op_assign
id|cpu_to_le32
c_func
(paren
id|attr-&gt;ia_ctime
)paren
suffix:semicolon
id|entry-&gt;nlink
op_assign
id|cpu_to_le16
c_func
(paren
id|inode-&gt;i_nlink
)paren
suffix:semicolon
id|ret
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|commit_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|offs
comma
id|offs
op_plus
id|UMSDOS_REC_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;umsdos_notify_change: %s/%s EMD write error, ret=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* #Specification: notify_change / msdos fs&n;&t; * notify_change operation are done only on the&n;&t; * EMD file. The msdos fs is not even called.&n;&t; */
id|out_unlock
suffix:colon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|out_dput
suffix:colon
id|dput
c_func
(paren
id|demd
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Update the disk with the inode content&n; */
DECL|function|UMSDOS_write_inode
r_void
id|UMSDOS_write_inode
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|wait
)paren
(brace
r_struct
id|iattr
id|newattrs
suffix:semicolon
id|fat_write_inode
(paren
id|inode
comma
id|wait
)paren
suffix:semicolon
id|newattrs.ia_mtime
op_assign
id|inode-&gt;i_mtime
suffix:semicolon
id|newattrs.ia_atime
op_assign
id|inode-&gt;i_atime
suffix:semicolon
id|newattrs.ia_ctime
op_assign
id|inode-&gt;i_ctime
suffix:semicolon
id|newattrs.ia_valid
op_assign
id|ATTR_MTIME
op_or
id|ATTR_ATIME
op_or
id|ATTR_CTIME
suffix:semicolon
multiline_comment|/*&n;&t; * UMSDOS_notify_change is convenient to call here&n;&t; * to update the EMD entry associated with this inode.&n;&t; * But it has the side effect to re&quot;dirt&quot; the inode.&n;&t; */
multiline_comment|/*      &n; * UMSDOS_notify_change (inode, &amp;newattrs);&n;&n; * inode-&gt;i_state &amp;= ~I_DIRTY; / * FIXME: this doesn&squot;t work.  We need to remove ourselves from list on dirty inodes. /mn/ */
)brace
DECL|variable|umsdos_sops
r_static
r_struct
id|super_operations
id|umsdos_sops
op_assign
(brace
id|write_inode
suffix:colon
id|UMSDOS_write_inode
comma
id|put_inode
suffix:colon
id|UMSDOS_put_inode
comma
id|delete_inode
suffix:colon
id|fat_delete_inode
comma
id|put_super
suffix:colon
id|UMSDOS_put_super
comma
id|statfs
suffix:colon
id|UMSDOS_statfs
comma
id|clear_inode
suffix:colon
id|fat_clear_inode
comma
)brace
suffix:semicolon
DECL|function|UMSDOS_statfs
r_int
id|UMSDOS_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|fat_statfs
(paren
id|sb
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|buf-&gt;f_namelen
op_assign
id|UMSDOS_MAXNAME
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the super block of an Extended MS-DOS FS.&n; */
DECL|function|UMSDOS_read_super
r_struct
id|super_block
op_star
id|UMSDOS_read_super
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|super_block
op_star
id|res
suffix:semicolon
r_struct
id|dentry
op_star
id|new_root
suffix:semicolon
multiline_comment|/*&n;&t; * Call msdos-fs to mount the disk.&n;&t; * Note: this returns res == sb or NULL&n;&t; */
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|options.isvfat
op_assign
l_int|0
suffix:semicolon
id|res
op_assign
id|fat_read_super
c_func
(paren
id|sb
comma
id|data
comma
id|silent
comma
op_amp
id|umsdos_rdir_inode_operations
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|res
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;VFS: Can&squot;t find a valid &quot;
l_string|&quot;UMSDOS filesystem on dev %s.&bslash;n&quot;
comma
id|sb-&gt;s_id
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;UMSDOS 0.86k &quot;
l_string|&quot;(compatibility level %d.%d, fast msdos)&bslash;n&quot;
comma
id|UMSDOS_VERSION
comma
id|UMSDOS_RELEASE
)paren
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|umsdos_sops
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|options.dotsOK
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disable hidden==dotfile */
multiline_comment|/* install our dentry operations ... */
id|sb-&gt;s_root-&gt;d_op
op_assign
op_amp
id|umsdos_dentry_operations
suffix:semicolon
id|umsdos_patch_dentry_inode
c_func
(paren
id|sb-&gt;s_root
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Check whether to change to the /linux root */
id|new_root
op_assign
id|check_pseudo_root
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_root
)paren
(brace
multiline_comment|/* sanity check */
r_if
c_cond
(paren
id|new_root-&gt;d_op
op_ne
op_amp
id|umsdos_dentry_operations
)paren
id|printk
c_func
(paren
l_string|&quot;umsdos_read_super: pseudo-root wrong ops!&bslash;n&quot;
)paren
suffix:semicolon
id|pseudo_root
op_assign
id|new_root-&gt;d_inode
suffix:semicolon
id|saved_root
op_assign
id|sb-&gt;s_root
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;UMSDOS: changed to alternate root&bslash;n&quot;
)paren
suffix:semicolon
id|dget
(paren
id|sb-&gt;s_root
)paren
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|dget
c_func
(paren
id|new_root
)paren
suffix:semicolon
)brace
r_return
id|sb
suffix:semicolon
)brace
multiline_comment|/*&n; * Check for an alternate root if we&squot;re the root device.&n; */
r_extern
id|kdev_t
id|ROOT_DEV
suffix:semicolon
DECL|function|check_pseudo_root
r_static
r_struct
id|dentry
op_star
id|check_pseudo_root
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|dentry
op_star
id|root
comma
op_star
id|sbin
comma
op_star
id|init
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether we&squot;re mounted as the root device.&n;&t; * must check like this, because we can be used with initrd&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|kdev_same
c_func
(paren
id|sb-&gt;s_dev
comma
id|ROOT_DEV
)paren
)paren
r_goto
id|out_noroot
suffix:semicolon
multiline_comment|/* &n;&t; * lookup_dentry needs a (so far non-existent) root. &n;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;check_pseudo_root: mounted as root&bslash;n&quot;
)paren
suffix:semicolon
id|root
op_assign
id|lookup_one_len
c_func
(paren
id|UMSDOS_PSDROOT_NAME
comma
id|sb-&gt;s_root
comma
id|UMSDOS_PSDROOT_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|root
)paren
)paren
r_goto
id|out_noroot
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root-&gt;d_inode
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|root-&gt;d_inode-&gt;i_mode
)paren
)paren
r_goto
id|out_dput
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;check_pseudo_root: found %s/%s&bslash;n&quot;
comma
id|root-&gt;d_parent-&gt;d_name.name
comma
id|root-&gt;d_name.name
)paren
suffix:semicolon
multiline_comment|/* look for /sbin/init */
id|sbin
op_assign
id|lookup_one_len
c_func
(paren
l_string|&quot;sbin&quot;
comma
id|root
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|sbin
)paren
)paren
r_goto
id|out_dput
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbin-&gt;d_inode
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|sbin-&gt;d_inode-&gt;i_mode
)paren
)paren
r_goto
id|out_dput_sbin
suffix:semicolon
id|init
op_assign
id|lookup_one_len
c_func
(paren
l_string|&quot;init&quot;
comma
id|sbin
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|init
)paren
)paren
r_goto
id|out_dput_sbin
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|init-&gt;d_inode
)paren
r_goto
id|out_dput_init
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;check_pseudo_root: found %s/%s, enabling pseudo-root&bslash;n&quot;
comma
id|init-&gt;d_parent-&gt;d_name.name
comma
id|init-&gt;d_name.name
)paren
suffix:semicolon
id|dput
c_func
(paren
id|sbin
)paren
suffix:semicolon
id|dput
c_func
(paren
id|init
)paren
suffix:semicolon
r_return
id|root
suffix:semicolon
multiline_comment|/* Alternate root not found ... */
id|out_dput_init
suffix:colon
id|dput
c_func
(paren
id|init
)paren
suffix:semicolon
id|out_dput_sbin
suffix:colon
id|dput
c_func
(paren
id|sbin
)paren
suffix:semicolon
id|out_dput
suffix:colon
id|dput
c_func
(paren
id|root
)paren
suffix:semicolon
id|out_noroot
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
id|DECLARE_FSTYPE_DEV
c_func
(paren
id|umsdos_fs_type
comma
l_string|&quot;umsdos&quot;
comma
id|UMSDOS_read_super
)paren
suffix:semicolon
DECL|function|init_umsdos_fs
r_static
r_int
id|__init
id|init_umsdos_fs
(paren
r_void
)paren
(brace
r_return
id|register_filesystem
(paren
op_amp
id|umsdos_fs_type
)paren
suffix:semicolon
)brace
DECL|function|exit_umsdos_fs
r_static
r_void
id|__exit
id|exit_umsdos_fs
(paren
r_void
)paren
(brace
id|unregister_filesystem
(paren
op_amp
id|umsdos_fs_type
)paren
suffix:semicolon
)brace
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|module_init
c_func
(paren
id|init_umsdos_fs
)paren
id|module_exit
c_func
(paren
id|exit_umsdos_fs
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
