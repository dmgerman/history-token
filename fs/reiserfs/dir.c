multiline_comment|/*&n; * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/reiserfs_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_struct
id|key
id|MIN_KEY
suffix:semicolon
r_static
r_int
id|reiserfs_readdir
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
r_int
id|reiserfs_dir_fsync
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
suffix:semicolon
DECL|variable|reiserfs_dir_operations
r_struct
id|file_operations
id|reiserfs_dir_operations
op_assign
(brace
dot
id|read
op_assign
id|generic_read_dir
comma
dot
id|readdir
op_assign
id|reiserfs_readdir
comma
dot
id|fsync
op_assign
id|reiserfs_dir_fsync
comma
dot
id|ioctl
op_assign
id|reiserfs_ioctl
comma
)brace
suffix:semicolon
DECL|function|reiserfs_dir_fsync
r_int
id|reiserfs_dir_fsync
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|reiserfs_write_lock
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|reiserfs_commit_for_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|reiserfs_write_unlock
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|store_ih
mdefine_line|#define store_ih(where,what) copy_item_head (where, what)
singleline_comment|//
DECL|function|reiserfs_readdir
r_static
r_int
id|reiserfs_readdir
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
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|cpu_key
id|pos_key
suffix:semicolon
multiline_comment|/* key of current position in the directory (key of directory entry) */
id|INITIALIZE_PATH
(paren
id|path_to_entry
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|item_num
comma
id|entry_num
suffix:semicolon
r_const
r_struct
id|key
op_star
id|rkey
suffix:semicolon
r_struct
id|item_head
op_star
id|ih
comma
id|tmp_ih
suffix:semicolon
r_int
id|search_res
suffix:semicolon
r_char
op_star
id|local_buf
suffix:semicolon
id|loff_t
id|next_pos
suffix:semicolon
r_char
id|small_buf
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* avoid kmalloc if we can */
r_struct
id|reiserfs_dir_entry
id|de
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|reiserfs_write_lock
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|reiserfs_check_lock_depth
c_func
(paren
l_string|&quot;readdir&quot;
)paren
suffix:semicolon
multiline_comment|/* form key for search the next directory entry using f_pos field of&n;       file structure */
id|make_cpu_key
(paren
op_amp
id|pos_key
comma
id|inode
comma
(paren
id|filp-&gt;f_pos
)paren
ques
c_cond
(paren
id|filp-&gt;f_pos
)paren
suffix:colon
id|DOT_OFFSET
comma
id|TYPE_DIRENTRY
comma
l_int|3
)paren
suffix:semicolon
id|next_pos
op_assign
id|cpu_key_k_offset
(paren
op_amp
id|pos_key
)paren
suffix:semicolon
multiline_comment|/*  reiserfs_warning (&quot;reiserfs_readdir 1: f_pos = %Ld&bslash;n&quot;, filp-&gt;f_pos);*/
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|research
suffix:colon
multiline_comment|/* search the directory item, containing entry with specified key */
id|search_res
op_assign
id|search_by_entry_key
(paren
id|inode-&gt;i_sb
comma
op_amp
id|pos_key
comma
op_amp
id|path_to_entry
comma
op_amp
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|search_res
op_eq
id|IO_ERROR
)paren
(brace
singleline_comment|// FIXME: we could just skip part of directory which could
singleline_comment|// not be read
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|entry_num
op_assign
id|de.de_entry_num
suffix:semicolon
id|bh
op_assign
id|de.de_bh
suffix:semicolon
id|item_num
op_assign
id|de.de_item_num
suffix:semicolon
id|ih
op_assign
id|de.de_ih
suffix:semicolon
id|store_ih
(paren
op_amp
id|tmp_ih
comma
id|ih
)paren
suffix:semicolon
multiline_comment|/* we must have found item, that is item of this directory, */
id|RFALSE
c_func
(paren
id|COMP_SHORT_KEYS
(paren
op_amp
(paren
id|ih-&gt;ih_key
)paren
comma
op_amp
id|pos_key
)paren
comma
l_string|&quot;vs-9000: found item %h does not match to dir we readdir %K&quot;
comma
id|ih
comma
op_amp
id|pos_key
)paren
suffix:semicolon
id|RFALSE
c_func
(paren
id|item_num
OG
id|B_NR_ITEMS
(paren
id|bh
)paren
op_minus
l_int|1
comma
l_string|&quot;vs-9005 item_num == %d, item amount == %d&quot;
comma
id|item_num
comma
id|B_NR_ITEMS
(paren
id|bh
)paren
)paren
suffix:semicolon
multiline_comment|/* and entry must be not more than number of entries in the item */
id|RFALSE
c_func
(paren
id|I_ENTRY_COUNT
(paren
id|ih
)paren
OL
id|entry_num
comma
l_string|&quot;vs-9010: entry number is too big %d (%d)&quot;
comma
id|entry_num
comma
id|I_ENTRY_COUNT
(paren
id|ih
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|search_res
op_eq
id|POSITION_FOUND
op_logical_or
id|entry_num
OL
id|I_ENTRY_COUNT
(paren
id|ih
)paren
)paren
(brace
multiline_comment|/* go through all entries in the directory item beginning from the entry, that has been found */
r_struct
id|reiserfs_de_head
op_star
id|deh
op_assign
id|B_I_DEH
(paren
id|bh
comma
id|ih
)paren
op_plus
id|entry_num
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|entry_num
OL
id|I_ENTRY_COUNT
(paren
id|ih
)paren
suffix:semicolon
id|entry_num
op_increment
comma
id|deh
op_increment
)paren
(brace
r_int
id|d_reclen
suffix:semicolon
r_char
op_star
id|d_name
suffix:semicolon
id|off_t
id|d_off
suffix:semicolon
id|ino_t
id|d_ino
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de_visible
(paren
id|deh
)paren
)paren
multiline_comment|/* it is hidden entry */
r_continue
suffix:semicolon
id|d_reclen
op_assign
id|entry_length
(paren
id|bh
comma
id|ih
comma
id|entry_num
)paren
suffix:semicolon
id|d_name
op_assign
id|B_I_DEH_ENTRY_FILE_NAME
(paren
id|bh
comma
id|ih
comma
id|deh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d_name
(braket
id|d_reclen
op_minus
l_int|1
)braket
)paren
id|d_reclen
op_assign
id|strlen
(paren
id|d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d_reclen
OG
id|REISERFS_MAX_NAME
c_func
(paren
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
)paren
(brace
multiline_comment|/* too big to send back to VFS */
r_continue
suffix:semicolon
)brace
multiline_comment|/* Ignore the .reiserfs_priv entry */
r_if
c_cond
(paren
id|reiserfs_xattrs
(paren
id|inode-&gt;i_sb
)paren
op_logical_and
op_logical_neg
id|old_format_only
c_func
(paren
id|inode-&gt;i_sb
)paren
op_logical_and
id|filp-&gt;f_dentry
op_eq
id|inode-&gt;i_sb-&gt;s_root
op_logical_and
id|REISERFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|priv_root
op_logical_and
id|REISERFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|priv_root-&gt;d_inode
op_logical_and
id|deh_objectid
c_func
(paren
id|deh
)paren
op_eq
id|le32_to_cpu
(paren
id|INODE_PKEY
c_func
(paren
id|REISERFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|priv_root-&gt;d_inode
)paren
op_member_access_from_pointer
id|k_objectid
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
id|d_off
op_assign
id|deh_offset
(paren
id|deh
)paren
suffix:semicolon
id|filp-&gt;f_pos
op_assign
id|d_off
suffix:semicolon
id|d_ino
op_assign
id|deh_objectid
(paren
id|deh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d_reclen
op_le
l_int|32
)paren
(brace
id|local_buf
op_assign
id|small_buf
suffix:semicolon
)brace
r_else
(brace
id|local_buf
op_assign
id|reiserfs_kmalloc
c_func
(paren
id|d_reclen
comma
id|GFP_NOFS
comma
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|local_buf
)paren
(brace
id|pathrelse
(paren
op_amp
id|path_to_entry
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|item_moved
(paren
op_amp
id|tmp_ih
comma
op_amp
id|path_to_entry
)paren
)paren
(brace
id|reiserfs_kfree
c_func
(paren
id|local_buf
comma
id|d_reclen
comma
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_goto
id|research
suffix:semicolon
)brace
)brace
singleline_comment|// Note, that we copy name to user space via temporary
singleline_comment|// buffer (local_buf) because filldir will block if
singleline_comment|// user space buffer is swapped out. At that time
singleline_comment|// entry can move to somewhere else
id|memcpy
(paren
id|local_buf
comma
id|d_name
comma
id|d_reclen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filldir
(paren
id|dirent
comma
id|local_buf
comma
id|d_reclen
comma
id|d_off
comma
id|d_ino
comma
id|DT_UNKNOWN
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|local_buf
op_ne
id|small_buf
)paren
(brace
id|reiserfs_kfree
c_func
(paren
id|local_buf
comma
id|d_reclen
comma
id|inode-&gt;i_sb
)paren
suffix:semicolon
)brace
r_goto
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|local_buf
op_ne
id|small_buf
)paren
(brace
id|reiserfs_kfree
c_func
(paren
id|local_buf
comma
id|d_reclen
comma
id|inode-&gt;i_sb
)paren
suffix:semicolon
)brace
singleline_comment|// next entry should be looked for with such offset
id|next_pos
op_assign
id|deh_offset
(paren
id|deh
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|item_moved
(paren
op_amp
id|tmp_ih
comma
op_amp
id|path_to_entry
)paren
)paren
(brace
r_goto
id|research
suffix:semicolon
)brace
)brace
multiline_comment|/* for */
)brace
r_if
c_cond
(paren
id|item_num
op_ne
id|B_NR_ITEMS
(paren
id|bh
)paren
op_minus
l_int|1
)paren
singleline_comment|// end of directory has been reached
r_goto
id|end
suffix:semicolon
multiline_comment|/* item we went through is last item of node. Using right&n;&t;   delimiting key check is it directory end */
id|rkey
op_assign
id|get_rkey
(paren
op_amp
id|path_to_entry
comma
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|comp_le_keys
(paren
id|rkey
comma
op_amp
id|MIN_KEY
)paren
)paren
(brace
multiline_comment|/* set pos_key to key, that is the smallest and greater&n;&t;       that key of the last entry in the item */
id|set_cpu_key_k_offset
(paren
op_amp
id|pos_key
comma
id|next_pos
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|COMP_SHORT_KEYS
(paren
id|rkey
comma
op_amp
id|pos_key
)paren
)paren
(brace
singleline_comment|// end of directory has been reached
r_goto
id|end
suffix:semicolon
)brace
multiline_comment|/* directory continues in the right neighboring block */
id|set_cpu_key_k_offset
(paren
op_amp
id|pos_key
comma
id|le_key_k_offset
(paren
id|KEY_FORMAT_3_5
comma
id|rkey
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* while */
id|end
suffix:colon
id|filp-&gt;f_pos
op_assign
id|next_pos
suffix:semicolon
id|pathrelse
(paren
op_amp
id|path_to_entry
)paren
suffix:semicolon
id|reiserfs_check_path
c_func
(paren
op_amp
id|path_to_entry
)paren
suffix:semicolon
id|out
suffix:colon
id|reiserfs_write_unlock
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* compose directory item containing &quot;.&quot; and &quot;..&quot; entries (entries are&n;   not aligned to 4 byte boundary) */
multiline_comment|/* the last four params are LE */
DECL|function|make_empty_dir_item_v1
r_void
id|make_empty_dir_item_v1
(paren
r_char
op_star
id|body
comma
id|__u32
id|dirid
comma
id|__u32
id|objid
comma
id|__u32
id|par_dirid
comma
id|__u32
id|par_objid
)paren
(brace
r_struct
id|reiserfs_de_head
op_star
id|deh
suffix:semicolon
id|memset
(paren
id|body
comma
l_int|0
comma
id|EMPTY_DIR_SIZE_V1
)paren
suffix:semicolon
id|deh
op_assign
(paren
r_struct
id|reiserfs_de_head
op_star
)paren
id|body
suffix:semicolon
multiline_comment|/* direntry header of &quot;.&quot; */
id|put_deh_offset
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|0
)braket
)paren
comma
id|DOT_OFFSET
)paren
suffix:semicolon
multiline_comment|/* these two are from make_le_item_head, and are are LE */
id|deh
(braket
l_int|0
)braket
dot
id|deh_dir_id
op_assign
id|dirid
suffix:semicolon
id|deh
(braket
l_int|0
)braket
dot
id|deh_objectid
op_assign
id|objid
suffix:semicolon
id|deh
(braket
l_int|0
)braket
dot
id|deh_state
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Endian safe if 0 */
id|put_deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|0
)braket
)paren
comma
id|EMPTY_DIR_SIZE_V1
op_minus
id|strlen
c_func
(paren
l_string|&quot;.&quot;
)paren
)paren
suffix:semicolon
id|mark_de_visible
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* direntry header of &quot;..&quot; */
id|put_deh_offset
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|1
)braket
)paren
comma
id|DOT_DOT_OFFSET
)paren
suffix:semicolon
multiline_comment|/* key of &quot;..&quot; for the root directory */
multiline_comment|/* these two are from the inode, and are are LE */
id|deh
(braket
l_int|1
)braket
dot
id|deh_dir_id
op_assign
id|par_dirid
suffix:semicolon
id|deh
(braket
l_int|1
)braket
dot
id|deh_objectid
op_assign
id|par_objid
suffix:semicolon
id|deh
(braket
l_int|1
)braket
dot
id|deh_state
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Endian safe if 0 */
id|put_deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|1
)braket
)paren
comma
id|deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|0
)braket
)paren
)paren
op_minus
id|strlen
c_func
(paren
l_string|&quot;..&quot;
)paren
)paren
suffix:semicolon
id|mark_de_visible
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* copy &quot;..&quot; and &quot;.&quot; */
id|memcpy
(paren
id|body
op_plus
id|deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|0
)braket
)paren
)paren
comma
l_string|&quot;.&quot;
comma
l_int|1
)paren
suffix:semicolon
id|memcpy
(paren
id|body
op_plus
id|deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|1
)braket
)paren
)paren
comma
l_string|&quot;..&quot;
comma
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/* compose directory item containing &quot;.&quot; and &quot;..&quot; entries */
DECL|function|make_empty_dir_item
r_void
id|make_empty_dir_item
(paren
r_char
op_star
id|body
comma
id|__u32
id|dirid
comma
id|__u32
id|objid
comma
id|__u32
id|par_dirid
comma
id|__u32
id|par_objid
)paren
(brace
r_struct
id|reiserfs_de_head
op_star
id|deh
suffix:semicolon
id|memset
(paren
id|body
comma
l_int|0
comma
id|EMPTY_DIR_SIZE
)paren
suffix:semicolon
id|deh
op_assign
(paren
r_struct
id|reiserfs_de_head
op_star
)paren
id|body
suffix:semicolon
multiline_comment|/* direntry header of &quot;.&quot; */
id|put_deh_offset
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|0
)braket
)paren
comma
id|DOT_OFFSET
)paren
suffix:semicolon
multiline_comment|/* these two are from make_le_item_head, and are are LE */
id|deh
(braket
l_int|0
)braket
dot
id|deh_dir_id
op_assign
id|dirid
suffix:semicolon
id|deh
(braket
l_int|0
)braket
dot
id|deh_objectid
op_assign
id|objid
suffix:semicolon
id|deh
(braket
l_int|0
)braket
dot
id|deh_state
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Endian safe if 0 */
id|put_deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|0
)braket
)paren
comma
id|EMPTY_DIR_SIZE
op_minus
id|ROUND_UP
c_func
(paren
id|strlen
c_func
(paren
l_string|&quot;.&quot;
)paren
)paren
)paren
suffix:semicolon
id|mark_de_visible
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* direntry header of &quot;..&quot; */
id|put_deh_offset
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|1
)braket
)paren
comma
id|DOT_DOT_OFFSET
)paren
suffix:semicolon
multiline_comment|/* key of &quot;..&quot; for the root directory */
multiline_comment|/* these two are from the inode, and are are LE */
id|deh
(braket
l_int|1
)braket
dot
id|deh_dir_id
op_assign
id|par_dirid
suffix:semicolon
id|deh
(braket
l_int|1
)braket
dot
id|deh_objectid
op_assign
id|par_objid
suffix:semicolon
id|deh
(braket
l_int|1
)braket
dot
id|deh_state
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Endian safe if 0 */
id|put_deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|1
)braket
)paren
comma
id|deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|0
)braket
)paren
)paren
op_minus
id|ROUND_UP
c_func
(paren
id|strlen
c_func
(paren
l_string|&quot;..&quot;
)paren
)paren
)paren
suffix:semicolon
id|mark_de_visible
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* copy &quot;..&quot; and &quot;.&quot; */
id|memcpy
(paren
id|body
op_plus
id|deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|0
)braket
)paren
)paren
comma
l_string|&quot;.&quot;
comma
l_int|1
)paren
suffix:semicolon
id|memcpy
(paren
id|body
op_plus
id|deh_location
c_func
(paren
op_amp
(paren
id|deh
(braket
l_int|1
)braket
)paren
)paren
comma
l_string|&quot;..&quot;
comma
l_int|2
)paren
suffix:semicolon
)brace
eof
