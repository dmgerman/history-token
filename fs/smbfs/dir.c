multiline_comment|/*&n; *  dir.c&n; *&n; *  Copyright (C) 1995, 1996 by Paal-Kr. Engstad and Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; *  Please add a note about your changes to smbfs in the ChangeLog file.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/smb_fs.h&gt;
macro_line|#include &lt;linux/smb_mount.h&gt;
macro_line|#include &lt;linux/smbno.h&gt;
macro_line|#include &quot;smb_debug.h&quot;
macro_line|#include &quot;proto.h&quot;
r_static
r_int
id|smb_readdir
c_func
(paren
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
r_static
r_int
id|smb_dir_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_struct
id|dentry
op_star
id|smb_lookup
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_static
r_int
id|smb_create
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|smb_mkdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|smb_rmdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_static
r_int
id|smb_unlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_static
r_int
id|smb_rename
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
DECL|variable|smb_dir_operations
r_struct
id|file_operations
id|smb_dir_operations
op_assign
(brace
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|smb_readdir
comma
id|ioctl
suffix:colon
id|smb_ioctl
comma
id|open
suffix:colon
id|smb_dir_open
comma
)brace
suffix:semicolon
DECL|variable|smb_dir_inode_operations
r_struct
id|inode_operations
id|smb_dir_inode_operations
op_assign
(brace
id|create
suffix:colon
id|smb_create
comma
id|lookup
suffix:colon
id|smb_lookup
comma
id|unlink
suffix:colon
id|smb_unlink
comma
id|mkdir
suffix:colon
id|smb_mkdir
comma
id|rmdir
suffix:colon
id|smb_rmdir
comma
id|rename
suffix:colon
id|smb_rename
comma
id|revalidate
suffix:colon
id|smb_revalidate_inode
comma
id|setattr
suffix:colon
id|smb_notify_change
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Read a directory, using filldir to fill the dirent memory.&n; * smb_proc_readdir does the actual reading from the smb server.&n; *&n; * The cache code is almost directly taken from ncpfs&n; */
r_static
r_int
DECL|function|smb_readdir
id|smb_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|filp-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|dir
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|smb_sb_info
op_star
id|server
op_assign
id|server_from_dentry
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_union
id|smb_dir_cache
op_star
id|cache
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|smb_cache_control
id|ctl
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
r_int
id|result
suffix:semicolon
id|ctl.page
op_assign
l_int|NULL
suffix:semicolon
id|ctl.cache
op_assign
l_int|NULL
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;reading %s/%s, f_pos=%d&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
(paren
r_int
)paren
id|filp-&gt;f_pos
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
(paren
r_int
r_int
)paren
id|filp-&gt;f_pos
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;.&quot;
comma
l_int|1
comma
l_int|0
comma
id|dir-&gt;i_ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|filp-&gt;f_pos
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* fallthrough */
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;..&quot;
comma
l_int|2
comma
l_int|1
comma
id|dentry-&gt;d_parent-&gt;d_inode-&gt;i_ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|filp-&gt;f_pos
op_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Make sure our inode is up-to-date.&n;&t; */
id|result
op_assign
id|smb_revalidate_inode
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|out
suffix:semicolon
id|page
op_assign
id|grab_cache_page
c_func
(paren
op_amp
id|dir-&gt;i_data
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_goto
id|read_really
suffix:semicolon
id|ctl.cache
op_assign
id|cache
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|ctl.head
op_assign
id|cache-&gt;head
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|Page_Uptodate
c_func
(paren
id|page
)paren
op_logical_or
op_logical_neg
id|ctl.head.eof
)paren
(brace
id|VERBOSE
c_func
(paren
l_string|&quot;%s/%s, page uptodate=%d, eof=%d&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|Page_Uptodate
c_func
(paren
id|page
)paren
comma
id|ctl.head.eof
)paren
suffix:semicolon
r_goto
id|init_cache
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|jiffies
op_minus
id|ctl.head.time
op_ge
id|SMB_MAX_AGE
c_func
(paren
id|server
)paren
)paren
r_goto
id|init_cache
suffix:semicolon
multiline_comment|/*&n;&t;&t; * N.B. ncpfs checks mtime of dentry too here, we don&squot;t.&n;&t;&t; *   1. common smb servers do not update mtime on dir changes&n;&t;&t; *   2. it requires an extra smb request&n;&t;&t; *      (revalidate has the same timeout as ctl.head.time)&n;&t;&t; *&n;&t;&t; * Instead smbfs invalidates its own cache on local changes&n;&t;&t; * and remote changes are not seen until timeout.&n;&t;&t; */
)brace
r_if
c_cond
(paren
id|filp-&gt;f_pos
OG
id|ctl.head.end
)paren
r_goto
id|finished
suffix:semicolon
id|ctl.fpos
op_assign
id|filp-&gt;f_pos
op_plus
(paren
id|SMB_DIRCACHE_START
op_minus
l_int|2
)paren
suffix:semicolon
id|ctl.ofs
op_assign
id|ctl.fpos
op_div
id|SMB_DIRCACHE_SIZE
suffix:semicolon
id|ctl.idx
op_assign
id|ctl.fpos
op_mod
id|SMB_DIRCACHE_SIZE
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|ctl.ofs
op_ne
l_int|0
)paren
(brace
id|ctl.page
op_assign
id|find_lock_page
c_func
(paren
op_amp
id|dir-&gt;i_data
comma
id|ctl.ofs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ctl.page
)paren
r_goto
id|invalid_cache
suffix:semicolon
id|ctl.cache
op_assign
id|kmap
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|Page_Uptodate
c_func
(paren
id|ctl.page
)paren
)paren
r_goto
id|invalid_cache
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ctl.idx
OL
id|SMB_DIRCACHE_SIZE
)paren
(brace
r_struct
id|dentry
op_star
id|dent
suffix:semicolon
r_int
id|res
suffix:semicolon
id|dent
op_assign
id|smb_dget_fpos
c_func
(paren
id|ctl.cache-&gt;dentry
(braket
id|ctl.idx
)braket
comma
id|dentry
comma
id|filp-&gt;f_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dent
)paren
r_goto
id|invalid_cache
suffix:semicolon
id|res
op_assign
id|filldir
c_func
(paren
id|dirent
comma
id|dent-&gt;d_name.name
comma
id|dent-&gt;d_name.len
comma
id|filp-&gt;f_pos
comma
id|dent-&gt;d_inode-&gt;i_ino
comma
id|DT_UNKNOWN
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|finished
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
l_int|1
suffix:semicolon
id|ctl.idx
op_add_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
OG
id|ctl.head.end
)paren
r_goto
id|finished
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctl.page
)paren
(brace
id|kunmap
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
id|ctl.page
op_assign
l_int|NULL
suffix:semicolon
)brace
id|ctl.idx
op_assign
l_int|0
suffix:semicolon
id|ctl.ofs
op_add_assign
l_int|1
suffix:semicolon
)brace
id|invalid_cache
suffix:colon
r_if
c_cond
(paren
id|ctl.page
)paren
(brace
id|kunmap
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
id|ctl.page
op_assign
l_int|NULL
suffix:semicolon
)brace
id|ctl.cache
op_assign
id|cache
suffix:semicolon
id|init_cache
suffix:colon
id|smb_invalidate_dircache_entries
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|ctl.head.time
op_assign
id|jiffies
suffix:semicolon
id|ctl.head.eof
op_assign
l_int|0
suffix:semicolon
id|ctl.fpos
op_assign
l_int|2
suffix:semicolon
id|ctl.ofs
op_assign
l_int|0
suffix:semicolon
id|ctl.idx
op_assign
id|SMB_DIRCACHE_START
suffix:semicolon
id|ctl.filled
op_assign
l_int|0
suffix:semicolon
id|ctl.valid
op_assign
l_int|1
suffix:semicolon
id|read_really
suffix:colon
id|result
op_assign
id|smb_proc_readdir
c_func
(paren
id|filp
comma
id|dirent
comma
id|filldir
comma
op_amp
id|ctl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctl.idx
op_eq
op_minus
l_int|1
)paren
r_goto
id|invalid_cache
suffix:semicolon
multiline_comment|/* retry */
id|ctl.head.end
op_assign
id|ctl.fpos
op_minus
l_int|1
suffix:semicolon
id|ctl.head.eof
op_assign
id|ctl.valid
suffix:semicolon
id|finished
suffix:colon
r_if
c_cond
(paren
id|page
)paren
(brace
id|cache-&gt;head
op_assign
id|ctl.head
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
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
)brace
r_if
c_cond
(paren
id|ctl.page
)paren
(brace
id|kunmap
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|ctl.page
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_dir_open
id|smb_dir_open
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|file-&gt;f_dentry
suffix:semicolon
r_struct
id|smb_sb_info
op_star
id|server
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;(%s/%s)&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|file-&gt;f_dentry-&gt;d_name.name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Directory timestamps in the core protocol aren&squot;t updated&n;&t; * when a file is added, so we give them a very short TTL.&n;&t; */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|server
op_assign
id|server_from_dentry
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;opt.protocol
OL
id|SMB_PROTOCOL_LANMAN2
)paren
(brace
r_int
r_int
id|age
op_assign
id|jiffies
op_minus
id|SMB_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|oldmtime
suffix:semicolon
r_if
c_cond
(paren
id|age
OG
l_int|2
op_star
id|HZ
)paren
id|smb_invalid_dir_cache
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Note: in order to allow the smbmount process to open the&n;&t; * mount point, we only revalidate if the connection is valid or&n;&t; * if the process is trying to access something other than the root.&n;&t; */
r_if
c_cond
(paren
id|server-&gt;state
op_eq
id|CONN_VALID
op_logical_or
op_logical_neg
id|IS_ROOT
c_func
(paren
id|dentry
)paren
)paren
id|error
op_assign
id|smb_revalidate_inode
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Dentry operations routines&n; */
r_static
r_int
id|smb_lookup_validate
c_func
(paren
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|smb_hash_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
r_static
r_int
id|smb_compare_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
r_static
r_int
id|smb_delete_dentry
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
DECL|variable|smbfs_dentry_operations
r_static
r_struct
id|dentry_operations
id|smbfs_dentry_operations
op_assign
(brace
id|d_revalidate
suffix:colon
id|smb_lookup_validate
comma
id|d_hash
suffix:colon
id|smb_hash_dentry
comma
id|d_compare
suffix:colon
id|smb_compare_dentry
comma
id|d_delete
suffix:colon
id|smb_delete_dentry
comma
)brace
suffix:semicolon
DECL|variable|smbfs_dentry_operations_case
r_static
r_struct
id|dentry_operations
id|smbfs_dentry_operations_case
op_assign
(brace
id|d_revalidate
suffix:colon
id|smb_lookup_validate
comma
id|d_delete
suffix:colon
id|smb_delete_dentry
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the callback when the dcache has a lookup hit.&n; */
r_static
r_int
DECL|function|smb_lookup_validate
id|smb_lookup_validate
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|flags
)paren
(brace
r_struct
id|smb_sb_info
op_star
id|server
op_assign
id|server_from_dentry
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
r_int
id|age
op_assign
id|jiffies
op_minus
id|dentry-&gt;d_time
suffix:semicolon
r_int
id|valid
suffix:semicolon
multiline_comment|/*&n;&t; * The default validation is based on dentry age:&n;&t; * we believe in dentries for a few seconds.  (But each&n;&t; * successful server lookup renews the timestamp.)&n;&t; */
id|valid
op_assign
(paren
id|age
op_le
id|SMB_MAX_AGE
c_func
(paren
id|server
)paren
)paren
suffix:semicolon
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
r_if
c_cond
(paren
op_logical_neg
id|valid
)paren
id|VERBOSE
c_func
(paren
l_string|&quot;%s/%s not valid, age=%lu&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|age
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|inode
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bad_inode
c_func
(paren
id|inode
)paren
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;%s/%s has dud inode&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
)paren
suffix:semicolon
id|valid
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|valid
)paren
id|valid
op_assign
(paren
id|smb_revalidate_inode
c_func
(paren
id|dentry
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * What should we do for negative dentries?&n;&t;&t; */
)brace
r_return
id|valid
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_hash_dentry
id|smb_hash_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|this
)paren
(brace
r_int
r_int
id|hash
suffix:semicolon
r_int
id|i
suffix:semicolon
id|hash
op_assign
id|init_name_hash
c_func
(paren
)paren
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
id|this-&gt;len
suffix:semicolon
id|i
op_increment
)paren
id|hash
op_assign
id|partial_name_hash
c_func
(paren
id|tolower
c_func
(paren
id|this-&gt;name
(braket
id|i
)braket
)paren
comma
id|hash
)paren
suffix:semicolon
id|this-&gt;hash
op_assign
id|end_name_hash
c_func
(paren
id|hash
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_compare_dentry
id|smb_compare_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|a
comma
r_struct
id|qstr
op_star
id|b
)paren
(brace
r_int
id|i
comma
id|result
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;len
op_ne
id|b-&gt;len
)paren
r_goto
id|out
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
id|a-&gt;len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|tolower
c_func
(paren
id|a-&gt;name
(braket
id|i
)braket
)paren
op_ne
id|tolower
c_func
(paren
id|b-&gt;name
(braket
id|i
)braket
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
id|result
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the callback from dput() when d_count is going to 0.&n; * We use this to unhash dentries with bad inodes.&n; */
r_static
r_int
DECL|function|smb_delete_dentry
id|smb_delete_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
(brace
r_if
c_cond
(paren
id|is_bad_inode
c_func
(paren
id|dentry-&gt;d_inode
)paren
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;bad inode, unhashing %s/%s&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* N.B. Unhash negative dentries? */
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize a new dentry&n; */
r_void
DECL|function|smb_new_dentry
id|smb_new_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|smb_sb_info
op_star
id|server
op_assign
id|server_from_dentry
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;mnt-&gt;flags
op_amp
id|SMB_MOUNT_CASE
)paren
id|dentry-&gt;d_op
op_assign
op_amp
id|smbfs_dentry_operations_case
suffix:semicolon
r_else
id|dentry-&gt;d_op
op_assign
op_amp
id|smbfs_dentry_operations
suffix:semicolon
id|dentry-&gt;d_time
op_assign
id|jiffies
suffix:semicolon
)brace
multiline_comment|/*&n; * Whenever a lookup succeeds, we know the parent directories&n; * are all valid, so we want to update the dentry timestamps.&n; * N.B. Move this to dcache?&n; */
r_void
DECL|function|smb_renew_times
id|smb_renew_times
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|dentry-&gt;d_time
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|IS_ROOT
c_func
(paren
id|dentry
)paren
)paren
r_break
suffix:semicolon
id|dentry
op_assign
id|dentry-&gt;d_parent
suffix:semicolon
)brace
)brace
r_static
r_struct
id|dentry
op_star
DECL|function|smb_lookup
id|smb_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|smb_fattr
id|finfo
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|smb_sb_info
op_star
id|server
suffix:semicolon
id|error
op_assign
op_minus
id|ENAMETOOLONG
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_name.len
OG
id|SMB_MAXNAMELEN
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|smb_proc_getattr
c_func
(paren
id|dentry
comma
op_amp
id|finfo
)paren
suffix:semicolon
macro_line|#ifdef SMBFS_PARANOIA
r_if
c_cond
(paren
id|error
op_logical_and
id|error
op_ne
op_minus
id|ENOENT
)paren
id|PARANOIA
c_func
(paren
l_string|&quot;find %s/%s failed, error=%d&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|error
)paren
suffix:semicolon
macro_line|#endif
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
op_minus
id|ENOENT
)paren
r_goto
id|add_entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
id|finfo.f_ino
op_assign
id|iunique
c_func
(paren
id|dentry-&gt;d_sb
comma
l_int|2
)paren
suffix:semicolon
id|inode
op_assign
id|smb_iget
c_func
(paren
id|dir-&gt;i_sb
comma
op_amp
id|finfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|add_entry
suffix:colon
id|server
op_assign
id|server_from_dentry
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;mnt-&gt;flags
op_amp
id|SMB_MOUNT_CASE
)paren
id|dentry-&gt;d_op
op_assign
op_amp
id|smbfs_dentry_operations_case
suffix:semicolon
r_else
id|dentry-&gt;d_op
op_assign
op_amp
id|smbfs_dentry_operations
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|smb_renew_times
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|out
suffix:colon
r_return
id|ERR_PTR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This code is common to all routines creating a new inode.&n; */
r_static
r_int
DECL|function|smb_instantiate
id|smb_instantiate
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|__u16
id|fileid
comma
r_int
id|have_id
)paren
(brace
r_struct
id|smb_sb_info
op_star
id|server
op_assign
id|server_from_dentry
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|smb_fattr
id|fattr
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;file %s/%s, fileid=%u&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|fileid
)paren
suffix:semicolon
id|error
op_assign
id|smb_proc_getattr
c_func
(paren
id|dentry
comma
op_amp
id|fattr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_close
suffix:semicolon
id|smb_renew_times
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|fattr.f_ino
op_assign
id|iunique
c_func
(paren
id|dentry-&gt;d_sb
comma
l_int|2
)paren
suffix:semicolon
id|inode
op_assign
id|smb_iget
c_func
(paren
id|dentry-&gt;d_sb
comma
op_amp
id|fattr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out_no_inode
suffix:semicolon
r_if
c_cond
(paren
id|have_id
)paren
(brace
r_struct
id|smb_inode_info
op_star
id|ei
op_assign
id|SMB_I
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ei-&gt;fileid
op_assign
id|fileid
suffix:semicolon
id|ei-&gt;access
op_assign
id|SMB_O_RDWR
suffix:semicolon
id|ei-&gt;open
op_assign
id|server-&gt;generation
suffix:semicolon
)brace
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
id|out_no_inode
suffix:colon
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
id|out_close
suffix:colon
r_if
c_cond
(paren
id|have_id
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;%s/%s failed, error=%d, closing %u&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|error
comma
id|fileid
)paren
suffix:semicolon
id|smb_close_fileid
c_func
(paren
id|dentry
comma
id|fileid
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* N.B. How should the mode argument be used? */
r_static
r_int
DECL|function|smb_create
id|smb_create
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
(brace
id|__u16
id|fileid
suffix:semicolon
r_int
id|error
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;creating %s/%s, mode=%d&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|mode
)paren
suffix:semicolon
id|smb_invalid_dir_cache
c_func
(paren
id|dir
)paren
suffix:semicolon
id|error
op_assign
id|smb_proc_create
c_func
(paren
id|dentry
comma
l_int|0
comma
id|CURRENT_TIME
comma
op_amp
id|fileid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|error
op_assign
id|smb_instantiate
c_func
(paren
id|dentry
comma
id|fileid
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;%s/%s failed, error=%d&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|dentry
)paren
comma
id|error
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* N.B. How should the mode argument be used? */
r_static
r_int
DECL|function|smb_mkdir
id|smb_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
(brace
r_int
id|error
suffix:semicolon
id|smb_invalid_dir_cache
c_func
(paren
id|dir
)paren
suffix:semicolon
id|error
op_assign
id|smb_proc_mkdir
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|error
op_assign
id|smb_instantiate
c_func
(paren
id|dentry
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_rmdir
id|smb_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * Close the directory if it&squot;s open.&n;&t; */
id|smb_close
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check that nobody else is using the directory..&n;&t; */
id|error
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d_unhashed
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|smb_invalid_dir_cache
c_func
(paren
id|dir
)paren
suffix:semicolon
id|error
op_assign
id|smb_proc_rmdir
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_unlink
id|smb_unlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * Close the file if it&squot;s open.&n;&t; */
id|smb_close
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
id|smb_invalid_dir_cache
c_func
(paren
id|dir
)paren
suffix:semicolon
id|error
op_assign
id|smb_proc_unlink
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|smb_renew_times
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_static
r_int
DECL|function|smb_rename
id|smb_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
(brace
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * Close any open files, and check whether to delete the&n;&t; * target before attempting the rename.&n;&t; */
r_if
c_cond
(paren
id|old_dentry-&gt;d_inode
)paren
id|smb_close
c_func
(paren
id|old_dentry-&gt;d_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_dentry-&gt;d_inode
)paren
(brace
id|smb_close
c_func
(paren
id|new_dentry-&gt;d_inode
)paren
suffix:semicolon
id|error
op_assign
id|smb_proc_unlink
c_func
(paren
id|new_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|VERBOSE
c_func
(paren
l_string|&quot;unlink %s/%s, error=%d&bslash;n&quot;
comma
id|DENTRY_PATH
c_func
(paren
id|new_dentry
)paren
comma
id|error
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* FIXME */
id|d_delete
c_func
(paren
id|new_dentry
)paren
suffix:semicolon
)brace
id|smb_invalid_dir_cache
c_func
(paren
id|old_dir
)paren
suffix:semicolon
id|smb_invalid_dir_cache
c_func
(paren
id|new_dir
)paren
suffix:semicolon
id|error
op_assign
id|smb_proc_mv
c_func
(paren
id|old_dentry
comma
id|new_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|smb_renew_times
c_func
(paren
id|old_dentry
)paren
suffix:semicolon
id|smb_renew_times
c_func
(paren
id|new_dentry
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
eof
