multiline_comment|/*&n; *  linux/fs/umsdos/emd.c&n; *&n; *  Written 1993 by Jacques Gelinas&n; *&n; *  Extended MS-DOS directory handling functions&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/umsdos_fs.h&gt;
macro_line|#include &lt;linux/dcache.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|function|put_entry
r_void
id|put_entry
(paren
r_struct
id|umsdos_dirent
op_star
id|p
comma
r_struct
id|umsdos_dirent
op_star
id|q
)paren
(brace
id|p-&gt;name_len
op_assign
id|q-&gt;name_len
suffix:semicolon
id|p-&gt;flags
op_assign
id|q-&gt;flags
suffix:semicolon
id|p-&gt;nlink
op_assign
id|cpu_to_le16
c_func
(paren
id|q-&gt;nlink
)paren
suffix:semicolon
id|p-&gt;uid
op_assign
id|cpu_to_le16
c_func
(paren
id|q-&gt;uid
)paren
suffix:semicolon
id|p-&gt;gid
op_assign
id|cpu_to_le16
c_func
(paren
id|q-&gt;gid
)paren
suffix:semicolon
id|p-&gt;atime
op_assign
id|cpu_to_le32
c_func
(paren
id|q-&gt;atime
)paren
suffix:semicolon
id|p-&gt;mtime
op_assign
id|cpu_to_le32
c_func
(paren
id|q-&gt;mtime
)paren
suffix:semicolon
id|p-&gt;ctime
op_assign
id|cpu_to_le32
c_func
(paren
id|q-&gt;ctime
)paren
suffix:semicolon
id|p-&gt;rdev
op_assign
id|cpu_to_le16
c_func
(paren
id|q-&gt;rdev
)paren
suffix:semicolon
id|p-&gt;mode
op_assign
id|cpu_to_le16
c_func
(paren
id|q-&gt;mode
)paren
suffix:semicolon
)brace
DECL|function|get_entry
r_static
r_void
id|get_entry
c_func
(paren
r_struct
id|umsdos_dirent
op_star
id|p
comma
r_struct
id|umsdos_dirent
op_star
id|q
)paren
(brace
id|p-&gt;name_len
op_assign
id|q-&gt;name_len
suffix:semicolon
id|p-&gt;name
(braket
id|p-&gt;name_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|p-&gt;flags
op_assign
id|q-&gt;flags
suffix:semicolon
id|p-&gt;nlink
op_assign
id|le16_to_cpu
(paren
id|q-&gt;nlink
)paren
suffix:semicolon
multiline_comment|/* FIXME -- 32bit UID/GID issues */
id|p-&gt;uid
op_assign
id|le16_to_cpu
(paren
id|q-&gt;uid
)paren
suffix:semicolon
id|p-&gt;gid
op_assign
id|le16_to_cpu
(paren
id|q-&gt;gid
)paren
suffix:semicolon
id|p-&gt;atime
op_assign
id|le32_to_cpu
(paren
id|q-&gt;atime
)paren
suffix:semicolon
id|p-&gt;mtime
op_assign
id|le32_to_cpu
(paren
id|q-&gt;mtime
)paren
suffix:semicolon
id|p-&gt;ctime
op_assign
id|le32_to_cpu
(paren
id|q-&gt;ctime
)paren
suffix:semicolon
id|p-&gt;rdev
op_assign
id|le16_to_cpu
(paren
id|q-&gt;rdev
)paren
suffix:semicolon
id|p-&gt;mode
op_assign
id|le16_to_cpu
(paren
id|q-&gt;mode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Lookup the EMD dentry for a directory.&n; *&n; * Note: the caller must hold a lock on the parent directory.&n; */
DECL|function|umsdos_get_emd_dentry
r_struct
id|dentry
op_star
id|umsdos_get_emd_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|parent
)paren
(brace
r_struct
id|dentry
op_star
id|demd
suffix:semicolon
id|demd
op_assign
id|umsdos_lookup_dentry
c_func
(paren
id|parent
comma
id|UMSDOS_EMD_FILE
comma
id|UMSDOS_EMD_NAMELEN
comma
l_int|1
)paren
suffix:semicolon
r_return
id|demd
suffix:semicolon
)brace
multiline_comment|/*&n; * Check whether a directory has an EMD file.&n; *&n; * Note: the caller must hold a lock on the parent directory.&n; */
DECL|function|umsdos_have_emd
r_int
id|umsdos_have_emd
c_func
(paren
r_struct
id|dentry
op_star
id|dir
)paren
(brace
r_struct
id|dentry
op_star
id|demd
op_assign
id|umsdos_get_emd_dentry
(paren
id|dir
)paren
suffix:semicolon
r_int
id|found
op_assign
l_int|0
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
r_if
c_cond
(paren
id|demd-&gt;d_inode
)paren
id|found
op_assign
l_int|1
suffix:semicolon
id|dput
c_func
(paren
id|demd
)paren
suffix:semicolon
)brace
r_return
id|found
suffix:semicolon
)brace
multiline_comment|/*&n; * Create the EMD file for a directory if it doesn&squot;t&n; * already exist. Returns 0 or an error code.&n; *&n; * Note: the caller must hold a lock on the parent directory.&n; */
DECL|function|umsdos_make_emd
r_int
id|umsdos_make_emd
c_func
(paren
r_struct
id|dentry
op_star
id|parent
)paren
(brace
r_struct
id|dentry
op_star
id|demd
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|parent
)paren
suffix:semicolon
r_int
id|err
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
(brace
id|printk
c_func
(paren
l_string|&quot;umsdos_make_emd: can&squot;t get dentry in %s, err=%d&bslash;n&quot;
comma
id|parent-&gt;d_name.name
comma
id|err
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* already created? */
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|demd-&gt;d_inode
)paren
r_goto
id|out_set
suffix:semicolon
id|Printk
c_func
(paren
(paren
l_string|&quot;umsdos_make_emd: creating EMD %s/%s&bslash;n&quot;
comma
id|parent-&gt;d_name.name
comma
id|demd-&gt;d_name.name
)paren
)paren
suffix:semicolon
id|err
op_assign
id|msdos_create
c_func
(paren
id|parent-&gt;d_inode
comma
id|demd
comma
id|S_IFREG
op_or
l_int|0777
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;umsdos_make_emd: create %s/%s failed, err=%d&bslash;n&quot;
comma
id|parent-&gt;d_name.name
comma
id|demd-&gt;d_name.name
comma
id|err
)paren
suffix:semicolon
)brace
id|out_set
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
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Read an entry from the EMD file.&n; * Support variable length record.&n; * Return -EIO if error, 0 if OK.&n; *&n; * does not change {d,i}_count&n; */
DECL|function|umsdos_emd_dir_readentry
r_int
id|umsdos_emd_dir_readentry
(paren
r_struct
id|dentry
op_star
id|demd
comma
id|loff_t
op_star
id|pos
comma
r_struct
id|umsdos_dirent
op_star
id|entry
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|demd-&gt;d_inode-&gt;i_mapping
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_struct
id|umsdos_dirent
op_star
id|p
suffix:semicolon
r_int
id|offs
op_assign
op_star
id|pos
op_amp
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
r_int
id|recsize
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|page
op_assign
id|read_cache_page
c_func
(paren
id|mapping
comma
op_star
id|pos
op_rshift
id|PAGE_CACHE_SHIFT
comma
(paren
id|filler_t
op_star
)paren
id|mapping-&gt;a_ops-&gt;readpage
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
r_goto
id|sync_fail
suffix:semicolon
id|wait_on_page_locked
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
r_goto
id|async_fail
suffix:semicolon
id|p
op_assign
(paren
r_struct
id|umsdos_dirent
op_star
)paren
(paren
id|kmap
c_func
(paren
id|page
)paren
op_plus
id|offs
)paren
suffix:semicolon
multiline_comment|/* if this is an invalid entry (invalid name length), ignore it */
r_if
c_cond
(paren
id|p-&gt;name_len
OG
id|UMSDOS_MAXNAME
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;Ignoring invalid EMD entry with size %d&bslash;n&quot;
comma
id|entry-&gt;name_len
)paren
suffix:semicolon
id|p-&gt;name_len
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
op_minus
id|ENAMETOOLONG
suffix:semicolon
multiline_comment|/* notify umssync(8) code that something is wrong */
multiline_comment|/* FIXME: does not work if we did &squot;ls -l&squot; before &squot;udosctl uls&squot; ?! */
)brace
id|recsize
op_assign
id|umsdos_evalrecsize
c_func
(paren
id|p-&gt;name_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offs
op_plus
id|recsize
OG
id|PAGE_CACHE_SIZE
)paren
(brace
r_struct
id|page
op_star
id|page2
suffix:semicolon
r_int
id|part
op_assign
(paren
r_char
op_star
)paren
(paren
id|page_address
c_func
(paren
id|page
)paren
op_plus
id|PAGE_CACHE_SIZE
)paren
op_minus
id|p-&gt;spare
suffix:semicolon
id|page2
op_assign
id|read_cache_page
c_func
(paren
id|mapping
comma
l_int|1
op_plus
(paren
op_star
id|pos
op_rshift
id|PAGE_CACHE_SHIFT
)paren
comma
(paren
id|filler_t
op_star
)paren
id|mapping-&gt;a_ops-&gt;readpage
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page2
)paren
)paren
(brace
id|kunmap
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
id|page
op_assign
id|page2
suffix:semicolon
r_goto
id|sync_fail
suffix:semicolon
)brace
id|wait_on_page_locked
c_func
(paren
id|page2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page2
)paren
)paren
(brace
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page2
)paren
suffix:semicolon
r_goto
id|async_fail
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|entry-&gt;spare
comma
id|p-&gt;spare
comma
id|part
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|entry-&gt;spare
op_plus
id|part
comma
id|kmap
c_func
(paren
id|page2
)paren
comma
id|recsize
op_plus
id|offs
op_minus
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page2
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page2
)paren
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
id|entry-&gt;spare
comma
id|p-&gt;spare
comma
(paren
(paren
r_char
op_star
)paren
id|p
op_plus
id|recsize
)paren
op_minus
id|p-&gt;spare
)paren
suffix:semicolon
id|get_entry
c_func
(paren
id|entry
comma
id|p
)paren
suffix:semicolon
id|kunmap
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
op_star
id|pos
op_add_assign
id|recsize
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|async_fail
suffix:colon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|page
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
id|sync_fail
suffix:colon
r_return
id|PTR_ERR
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write an entry in the EMD file.&n; * Return 0 if OK, -EIO if some error.&n; *&n; * Note: the caller must hold a lock on the parent directory.&n; */
DECL|function|umsdos_writeentry
r_int
id|umsdos_writeentry
(paren
r_struct
id|dentry
op_star
id|parent
comma
r_struct
id|umsdos_info
op_star
id|info
comma
r_int
id|free_entry
)paren
(brace
r_struct
id|inode
op_star
id|dir
op_assign
id|parent-&gt;d_inode
suffix:semicolon
r_struct
id|umsdos_dirent
op_star
id|entry
op_assign
op_amp
id|info-&gt;entry
suffix:semicolon
r_struct
id|dentry
op_star
id|emd_dentry
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_struct
id|umsdos_dirent
id|entry0
comma
op_star
id|p
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
comma
op_star
id|page2
op_assign
l_int|NULL
suffix:semicolon
r_int
id|offs
suffix:semicolon
id|emd_dentry
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|parent
)paren
suffix:semicolon
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|emd_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|emd_dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* make sure there&squot;s an EMD file */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|emd_dentry-&gt;d_inode
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;umsdos_writeentry: no EMD file in %s/%s&bslash;n&quot;
comma
id|parent-&gt;d_parent-&gt;d_name.name
comma
id|parent-&gt;d_name.name
)paren
suffix:semicolon
r_goto
id|out_dput
suffix:semicolon
)brace
r_if
c_cond
(paren
id|free_entry
)paren
(brace
multiline_comment|/* #Specification: EMD file / empty entries&n;&t;&t; * Unused entries in the EMD file are identified&n;&t;&t; * by the name_len field equal to 0. However to&n;&t;&t; * help future extension (or bug correction :-( ),&n;&t;&t; * empty entries are filled with 0.&n;&t;&t; */
id|memset
(paren
op_amp
id|entry0
comma
l_int|0
comma
r_sizeof
(paren
id|entry0
)paren
)paren
suffix:semicolon
id|entry
op_assign
op_amp
id|entry0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|entry-&gt;name_len
OG
l_int|0
)paren
(brace
id|memset
(paren
id|entry-&gt;name
op_plus
id|entry-&gt;name_len
comma
l_char|&squot;&bslash;0&squot;
comma
r_sizeof
(paren
id|entry-&gt;name
)paren
op_minus
id|entry-&gt;name_len
)paren
suffix:semicolon
multiline_comment|/* #Specification: EMD file / spare bytes&n;&t;&t; * 10 bytes are unused in each record of the EMD. They&n;&t;&t; * are set to 0 all the time, so it will be possible&n;&t;&t; * to do new stuff and rely on the state of those&n;&t;&t; * bytes in old EMD files.&n;&t;&t; */
id|memset
(paren
id|entry-&gt;spare
comma
l_int|0
comma
r_sizeof
(paren
id|entry-&gt;spare
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* write the entry and update the parent timestamps */
id|mapping
op_assign
id|emd_dentry-&gt;d_inode-&gt;i_mapping
suffix:semicolon
id|offs
op_assign
id|info-&gt;f_pos
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
id|info-&gt;f_pos
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
id|p
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
id|offs
op_plus
id|info-&gt;recsize
OG
id|PAGE_CACHE_SIZE
)paren
(brace
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
id|PAGE_CACHE_SIZE
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
id|page2
op_assign
id|grab_cache_page
c_func
(paren
id|mapping
comma
(paren
id|info-&gt;f_pos
op_rshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page2
)paren
r_goto
id|out_unlock2
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
id|page2
comma
l_int|0
comma
id|offs
op_plus
id|info-&gt;recsize
op_minus
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out_unlock3
suffix:semicolon
id|put_entry
(paren
id|p
comma
id|entry
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p-&gt;spare
comma
id|entry-&gt;spare
comma
(paren
r_char
op_star
)paren
(paren
id|page_address
c_func
(paren
id|page
)paren
op_plus
id|PAGE_CACHE_SIZE
)paren
op_minus
id|p-&gt;spare
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|page_address
c_func
(paren
id|page2
)paren
comma
(paren
(paren
r_char
op_star
)paren
id|entry
)paren
op_plus
id|PAGE_CACHE_SIZE
op_minus
id|offs
comma
id|offs
op_plus
id|info-&gt;recsize
op_minus
id|PAGE_CACHE_SIZE
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
id|page2
comma
l_int|0
comma
id|offs
op_plus
id|info-&gt;recsize
op_minus
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out_unlock3
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
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page2
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page2
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
)brace
r_else
(brace
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
id|info-&gt;recsize
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
id|put_entry
(paren
id|p
comma
id|entry
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p-&gt;spare
comma
id|entry-&gt;spare
comma
(paren
(paren
r_char
op_star
)paren
id|p
op_plus
id|info-&gt;recsize
)paren
op_minus
id|p-&gt;spare
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
id|info-&gt;recsize
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
)brace
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
id|dir-&gt;i_ctime
op_assign
id|dir-&gt;i_mtime
op_assign
id|CURRENT_TIME_SEC
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|out_dput
suffix:colon
id|dput
c_func
(paren
id|emd_dentry
)paren
suffix:semicolon
id|out
suffix:colon
id|Printk
(paren
(paren
l_string|&quot;umsdos_writeentry /mn/: returning %d...&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|out_unlock3
suffix:colon
id|unlock_page
c_func
(paren
id|page2
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page2
)paren
suffix:semicolon
id|out_unlock2
suffix:colon
id|ClearPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
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
id|printk
(paren
l_string|&quot;UMSDOS:  problem with EMD file:  can&squot;t write&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_dput
suffix:semicolon
)brace
multiline_comment|/*&n; * General search, locate a name in the EMD file or an empty slot to&n; * store it. if info-&gt;entry.name_len == 0, search the first empty&n; * slot (of the proper size).&n; * &n; * Return 0 if found, -ENOENT if not found, another error code if&n; * other problem.&n; * &n; * So this routine is used to either find an existing entry or to&n; * create a new one, while making sure it is a new one. After you&n; * get -ENOENT, you make sure the entry is stuffed correctly and&n; * call umsdos_writeentry().&n; * &n; * To delete an entry, you find it, zero out the entry (memset)&n; * and call umsdos_writeentry().&n; * &n; * All this to say that umsdos_writeentry must be called after this&n; * function since it relies on the f_pos field of info.&n; *&n; * Note: the caller must hold a lock on the parent directory.&n; */
multiline_comment|/* #Specification: EMD file structure&n; * The EMD file uses a fairly simple layout.  It is made of records&n; * (UMSDOS_REC_SIZE == 64).  When a name can&squot;t be written in a single&n; * record, multiple contiguous records are allocated.&n; */
DECL|function|umsdos_find
r_static
r_int
id|umsdos_find
(paren
r_struct
id|dentry
op_star
id|demd
comma
r_struct
id|umsdos_info
op_star
id|info
)paren
(brace
r_struct
id|umsdos_dirent
op_star
id|entry
op_assign
op_amp
id|info-&gt;entry
suffix:semicolon
r_int
id|recsize
op_assign
id|info-&gt;recsize
suffix:semicolon
r_struct
id|inode
op_star
id|emd_dir
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_struct
(brace
id|off_t
id|posok
suffix:semicolon
multiline_comment|/* Position available to store the entry */
id|off_t
id|one
suffix:semicolon
multiline_comment|/* One empty position -&gt; maybe &lt;- large enough */
)brace
id|empty
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_int
id|empty_size
op_assign
l_int|0
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
suffix:semicolon
id|filler_t
op_star
id|readpage
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
r_int
id|index
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|offs
op_assign
id|PAGE_CACHE_SIZE
comma
id|max_offs
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
r_char
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
id|loff_t
id|pos
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* make sure there&squot;s an EMD file ... */
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|emd_dir
op_assign
id|demd-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|emd_dir
)paren
r_goto
id|out_dput
suffix:semicolon
id|mapping
op_assign
id|emd_dir-&gt;i_mapping
suffix:semicolon
id|readpage
op_assign
(paren
id|filler_t
op_star
)paren
id|mapping-&gt;a_ops-&gt;readpage
suffix:semicolon
id|empty.posok
op_assign
id|emd_dir-&gt;i_size
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_struct
id|umsdos_dirent
op_star
id|rentry
suffix:semicolon
r_int
id|entry_size
suffix:semicolon
r_if
c_cond
(paren
id|offs
op_ge
id|max_offs
)paren
(brace
r_if
c_cond
(paren
id|page
)paren
(brace
id|kunmap
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
id|page
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
op_ge
id|emd_dir-&gt;i_size
)paren
(brace
id|info-&gt;f_pos
op_assign
id|empty.posok
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|index
op_eq
(paren
id|emd_dir-&gt;i_size
op_rshift
id|PAGE_CACHE_SHIFT
)paren
)paren
id|max_offs
op_assign
id|emd_dir-&gt;i_size
op_amp
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
id|offs
op_sub_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|page
op_assign
id|read_cache_page
c_func
(paren
id|mapping
comma
id|index
comma
id|readpage
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
r_goto
id|sync_fail
suffix:semicolon
id|wait_on_page_locked
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
r_goto
id|async_fail
suffix:semicolon
id|p
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|rentry
op_assign
(paren
r_struct
id|umsdos_dirent
op_star
)paren
(paren
id|p
op_plus
id|offs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rentry-&gt;name_len
op_eq
l_int|0
)paren
(brace
multiline_comment|/* We are looking for an empty section at least */
multiline_comment|/* as large as recsize. */
r_if
c_cond
(paren
id|entry-&gt;name_len
op_eq
l_int|0
)paren
(brace
id|info-&gt;f_pos
op_assign
id|pos
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|offs
op_add_assign
id|UMSDOS_REC_SIZE
suffix:semicolon
id|pos
op_add_assign
id|UMSDOS_REC_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|found
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|empty_size
)paren
id|empty.one
op_assign
id|pos
op_minus
id|UMSDOS_REC_SIZE
suffix:semicolon
id|empty_size
op_add_assign
id|UMSDOS_REC_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|empty_size
op_eq
id|recsize
)paren
(brace
multiline_comment|/* Here is a large enough section. */
id|empty.posok
op_assign
id|empty.one
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
id|entry_size
op_assign
id|umsdos_evalrecsize
c_func
(paren
id|rentry-&gt;name_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry_size
OG
id|PAGE_CACHE_SIZE
)paren
r_goto
id|async_fail
suffix:semicolon
id|empty_size
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;name_len
op_ne
id|rentry-&gt;name_len
)paren
r_goto
id|skip_it
suffix:semicolon
r_if
c_cond
(paren
id|entry_size
op_plus
id|offs
OG
id|PAGE_CACHE_SIZE
)paren
(brace
multiline_comment|/* Sucker spans the page boundary */
r_int
id|len
op_assign
(paren
id|p
op_plus
id|PAGE_CACHE_SIZE
)paren
op_minus
id|rentry-&gt;name
suffix:semicolon
r_struct
id|page
op_star
id|next_page
suffix:semicolon
r_char
op_star
id|q
suffix:semicolon
id|next_page
op_assign
id|read_cache_page
c_func
(paren
id|mapping
comma
id|index
op_plus
l_int|1
comma
id|readpage
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|next_page
)paren
)paren
(brace
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|page
op_assign
id|next_page
suffix:semicolon
r_goto
id|sync_fail
suffix:semicolon
)brace
id|wait_on_page_locked
c_func
(paren
id|next_page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|next_page
)paren
)paren
(brace
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|page
op_assign
id|next_page
suffix:semicolon
r_goto
id|async_fail
suffix:semicolon
)brace
id|q
op_assign
id|kmap
c_func
(paren
id|next_page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|entry-&gt;name
comma
id|rentry-&gt;name
comma
id|len
)paren
op_logical_or
id|memcmp
c_func
(paren
id|entry-&gt;name
op_plus
id|len
comma
id|q
comma
id|entry-&gt;name_len
op_minus
id|len
)paren
)paren
(brace
id|kunmap
c_func
(paren
id|next_page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|next_page
)paren
suffix:semicolon
r_goto
id|skip_it
suffix:semicolon
)brace
id|kunmap
c_func
(paren
id|next_page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|next_page
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|memcmp
(paren
id|entry-&gt;name
comma
id|rentry-&gt;name
comma
id|entry-&gt;name_len
)paren
)paren
r_goto
id|skip_it
suffix:semicolon
id|info-&gt;f_pos
op_assign
id|pos
suffix:semicolon
id|get_entry
c_func
(paren
id|entry
comma
id|rentry
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
id|skip_it
suffix:colon
id|offs
op_add_assign
id|entry_size
suffix:semicolon
id|pos
op_add_assign
id|entry_size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page
)paren
(brace
id|kunmap
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
id|umsdos_manglename
(paren
id|info
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
r_return
id|ret
suffix:semicolon
id|async_fail
suffix:colon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|page
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
id|sync_fail
suffix:colon
r_return
id|PTR_ERR
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a new entry in the EMD file.&n; * Return 0 if OK or a negative error code.&n; * Return -EEXIST if the entry already exists.&n; *&n; * Complete the information missing in info.&n; * &n; * N.B. What if the EMD file doesn&squot;t exist?&n; */
DECL|function|umsdos_newentry
r_int
id|umsdos_newentry
(paren
r_struct
id|dentry
op_star
id|parent
comma
r_struct
id|umsdos_info
op_star
id|info
)paren
(brace
r_int
id|err
comma
id|ret
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_struct
id|dentry
op_star
id|demd
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|parent
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
id|err
op_assign
id|umsdos_find
(paren
id|demd
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_logical_and
id|err
op_eq
op_minus
id|ENOENT
)paren
(brace
id|ret
op_assign
id|umsdos_writeentry
(paren
id|parent
comma
id|info
comma
l_int|0
)paren
suffix:semicolon
id|Printk
(paren
(paren
l_string|&quot;umsdos_writeentry EMD ret = %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a new hidden link.&n; * Return 0 if OK, an error code if not.&n; */
multiline_comment|/* #Specification: hard link / hidden name&n; * When a hard link is created, the original file is renamed&n; * to a hidden name. The name is &quot;..LINKNNN&quot; where NNN is a&n; * number define from the entry offset in the EMD file.&n; */
DECL|function|umsdos_newhidden
r_int
id|umsdos_newhidden
(paren
r_struct
id|dentry
op_star
id|parent
comma
r_struct
id|umsdos_info
op_star
id|info
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|dentry
op_star
id|demd
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|parent
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
id|umsdos_parse
(paren
l_string|&quot;..LINK&quot;
comma
l_int|6
comma
id|info
)paren
suffix:semicolon
id|info-&gt;entry.name_len
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|umsdos_find
(paren
id|demd
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENOENT
op_logical_or
id|ret
op_eq
l_int|0
)paren
(brace
id|info-&gt;entry.name_len
op_assign
id|sprintf
(paren
id|info-&gt;entry.name
comma
l_string|&quot;..LINK%ld&quot;
comma
id|info-&gt;f_pos
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove an entry from the EMD file.&n; * Return 0 if OK, a negative error code otherwise.&n; * &n; * Complete the information missing in info.&n; */
DECL|function|umsdos_delentry
r_int
id|umsdos_delentry
(paren
r_struct
id|dentry
op_star
id|parent
comma
r_struct
id|umsdos_info
op_star
id|info
comma
r_int
id|isdir
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|dentry
op_star
id|demd
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|parent
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
id|umsdos_find
(paren
id|demd
comma
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
r_if
c_cond
(paren
id|info-&gt;entry.name_len
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|isdir
op_ne
l_int|0
)paren
op_ne
(paren
id|S_ISDIR
(paren
id|info-&gt;entry.mode
)paren
op_ne
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
id|S_ISDIR
(paren
id|info-&gt;entry.mode
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EISDIR
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
op_minus
id|ENOTDIR
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|umsdos_writeentry
(paren
id|parent
comma
id|info
comma
l_int|1
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Verify that an EMD directory is empty.&n; * Return: &n; * 0 if not empty,&n; * 1 if empty (except for EMD file),&n; * 2 if empty or no EMD file.&n; */
DECL|function|umsdos_isempty
r_int
id|umsdos_isempty
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|dentry
op_star
id|demd
suffix:semicolon
r_int
id|ret
op_assign
l_int|2
suffix:semicolon
id|loff_t
id|pos
op_assign
l_int|0
suffix:semicolon
id|demd
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|dentry
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
multiline_comment|/* If the EMD file does not exist, it is certainly empty. :-) */
r_if
c_cond
(paren
op_logical_neg
id|demd-&gt;d_inode
)paren
r_goto
id|out_dput
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|pos
OL
id|demd-&gt;d_inode-&gt;i_size
)paren
(brace
r_struct
id|umsdos_dirent
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|umsdos_emd_dir_readentry
(paren
id|demd
comma
op_amp
id|pos
comma
op_amp
id|entry
)paren
op_ne
l_int|0
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|entry.name_len
op_ne
l_int|0
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
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
multiline_comment|/*&n; * Locate an entry in a EMD directory.&n; * Return 0 if OK, error code if not, generally -ENOENT.&n; *&n; * expect argument:&n; * &t;0: anything&n; * &t;1: file&n; * &t;2: directory&n; */
DECL|function|umsdos_findentry
r_int
id|umsdos_findentry
(paren
r_struct
id|dentry
op_star
id|parent
comma
r_struct
id|umsdos_info
op_star
id|info
comma
r_int
id|expect
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|dentry
op_star
id|demd
op_assign
id|umsdos_get_emd_dentry
c_func
(paren
id|parent
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
id|umsdos_find
(paren
id|demd
comma
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
r_switch
c_cond
(paren
id|expect
)paren
(brace
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|S_ISDIR
(paren
id|info-&gt;entry.mode
)paren
)paren
id|ret
op_assign
op_minus
id|EISDIR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
(paren
id|info-&gt;entry.mode
)paren
)paren
id|ret
op_assign
op_minus
id|ENOTDIR
suffix:semicolon
)brace
id|out
suffix:colon
id|Printk
(paren
(paren
l_string|&quot;umsdos_findentry: returning %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
