multiline_comment|/*&n; *  linux/fs/hfs/catalog.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * (C) 2003 Ardis Technologies &lt;roman@ardistech.com&gt;&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * This file contains the functions related to the catalog B-tree.&n; *&n; * Cache code shamelessly stolen from&n; *     linux/fs/inode.c Copyright (C) 1991, 1992  Linus Torvalds&n; *     re-shamelessly stolen Copyright (C) 1997 Linus Torvalds&n; */
macro_line|#include &quot;hfs_fs.h&quot;
macro_line|#include &quot;btree.h&quot;
multiline_comment|/*&n; * hfs_cat_build_key()&n; *&n; * Given the ID of the parent and the name build a search key.&n; */
DECL|function|hfs_cat_build_key
r_void
id|hfs_cat_build_key
c_func
(paren
id|btree_key
op_star
id|key
comma
id|u32
id|parent
comma
r_struct
id|qstr
op_star
id|name
)paren
(brace
id|key-&gt;cat.reserved
op_assign
l_int|0
suffix:semicolon
id|key-&gt;cat.ParID
op_assign
id|cpu_to_be32
c_func
(paren
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
(brace
id|hfs_triv2mac
c_func
(paren
op_amp
id|key-&gt;cat.CName
comma
id|name
)paren
suffix:semicolon
id|key-&gt;key_len
op_assign
l_int|6
op_plus
id|key-&gt;cat.CName.len
suffix:semicolon
)brace
r_else
(brace
id|memset
c_func
(paren
op_amp
id|key-&gt;cat.CName
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hfs_name
)paren
)paren
suffix:semicolon
id|key-&gt;key_len
op_assign
l_int|6
suffix:semicolon
)brace
)brace
DECL|function|hfs_cat_build_record
r_int
id|hfs_cat_build_record
c_func
(paren
id|hfs_cat_rec
op_star
id|rec
comma
id|u32
id|cnid
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|u32
id|mtime
op_assign
id|hfs_mtime
c_func
(paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|rec
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|rec
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|rec-&gt;type
op_assign
id|HFS_CDR_DIR
suffix:semicolon
id|rec-&gt;dir.DirID
op_assign
id|cpu_to_be32
c_func
(paren
id|cnid
)paren
suffix:semicolon
id|rec-&gt;dir.CrDat
op_assign
id|mtime
suffix:semicolon
id|rec-&gt;dir.MdDat
op_assign
id|mtime
suffix:semicolon
id|rec-&gt;dir.BkDat
op_assign
l_int|0
suffix:semicolon
id|rec-&gt;dir.UsrInfo.frView
op_assign
id|cpu_to_be16
c_func
(paren
l_int|0xff
)paren
suffix:semicolon
r_return
r_sizeof
(paren
r_struct
id|hfs_cat_dir
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* init some fields for the file record */
id|rec-&gt;type
op_assign
id|HFS_CDR_FIL
suffix:semicolon
id|rec-&gt;file.Flags
op_assign
id|HFS_FIL_USED
op_or
id|HFS_FIL_THD
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_mode
op_amp
id|S_IWUSR
)paren
)paren
id|rec-&gt;file.Flags
op_or_assign
id|HFS_FIL_LOCK
suffix:semicolon
id|rec-&gt;file.FlNum
op_assign
id|cpu_to_be32
c_func
(paren
id|cnid
)paren
suffix:semicolon
id|rec-&gt;file.CrDat
op_assign
id|mtime
suffix:semicolon
id|rec-&gt;file.MdDat
op_assign
id|mtime
suffix:semicolon
id|rec-&gt;file.BkDat
op_assign
l_int|0
suffix:semicolon
id|rec-&gt;file.UsrWds.fdType
op_assign
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_type
suffix:semicolon
id|rec-&gt;file.UsrWds.fdCreator
op_assign
id|HFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_creator
suffix:semicolon
r_return
r_sizeof
(paren
r_struct
id|hfs_cat_file
)paren
suffix:semicolon
)brace
)brace
DECL|function|hfs_cat_build_thread
r_static
r_int
id|hfs_cat_build_thread
c_func
(paren
id|hfs_cat_rec
op_star
id|rec
comma
r_int
id|type
comma
id|u32
id|parentid
comma
r_struct
id|qstr
op_star
id|name
)paren
(brace
id|rec-&gt;type
op_assign
id|type
suffix:semicolon
id|memset
c_func
(paren
id|rec-&gt;thread.reserved
comma
l_int|0
comma
r_sizeof
(paren
id|rec-&gt;thread.reserved
)paren
)paren
suffix:semicolon
id|rec-&gt;thread.ParID
op_assign
id|cpu_to_be32
c_func
(paren
id|parentid
)paren
suffix:semicolon
id|hfs_triv2mac
c_func
(paren
op_amp
id|rec-&gt;thread.CName
comma
id|name
)paren
suffix:semicolon
r_return
r_sizeof
(paren
r_struct
id|hfs_cat_thread
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * create_entry()&n; *&n; * Add a new file or directory to the catalog B-tree and&n; * return a (struct hfs_cat_entry) for it in &squot;*result&squot;.&n; */
DECL|function|hfs_cat_create
r_int
id|hfs_cat_create
c_func
(paren
id|u32
id|cnid
comma
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|str
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|hfs_find_data
id|fd
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_union
id|hfs_cat_rec
id|entry
suffix:semicolon
r_int
id|entry_size
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_CAT_MOD
comma
l_string|&quot;create_cat: %s,%u(%d)&bslash;n&quot;
comma
id|str-&gt;name
comma
id|cnid
comma
id|inode-&gt;i_nlink
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_size
op_ge
id|HFS_MAX_VALENCE
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
id|hfs_find_init
c_func
(paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cat_tree
comma
op_amp
id|fd
)paren
suffix:semicolon
id|hfs_cat_build_key
c_func
(paren
id|fd.search_key
comma
id|cnid
comma
l_int|NULL
)paren
suffix:semicolon
id|entry_size
op_assign
id|hfs_cat_build_thread
c_func
(paren
op_amp
id|entry
comma
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
ques
c_cond
id|HFS_CDR_THD
suffix:colon
id|HFS_CDR_FTH
comma
id|dir-&gt;i_ino
comma
id|str
)paren
suffix:semicolon
id|err
op_assign
id|hfs_brec_find
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
op_minus
id|ENOENT
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|hfs_brec_insert
c_func
(paren
op_amp
id|fd
comma
op_amp
id|entry
comma
id|entry_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|hfs_cat_build_key
c_func
(paren
id|fd.search_key
comma
id|dir-&gt;i_ino
comma
id|str
)paren
suffix:semicolon
id|entry_size
op_assign
id|hfs_cat_build_record
c_func
(paren
op_amp
id|entry
comma
id|cnid
comma
id|inode
)paren
suffix:semicolon
id|err
op_assign
id|hfs_brec_find
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
op_minus
id|ENOENT
)paren
(brace
multiline_comment|/* panic? */
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|hfs_brec_insert
c_func
(paren
op_amp
id|fd
comma
op_amp
id|entry
comma
id|entry_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|dir-&gt;i_size
op_increment
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|hfs_find_exit
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_cat_compare()&n; *&n; * Description:&n; *   This is the comparison function used for the catalog B-tree.  In&n; *   comparing catalog B-tree entries, the parent id is the most&n; *   significant field (compared as unsigned ints).  The name field is&n; *   the least significant (compared in &quot;Macintosh lexical order&quot;,&n; *   see hfs_strcmp() in string.c)&n; * Input Variable(s):&n; *   struct hfs_cat_key *key1: pointer to the first key to compare&n; *   struct hfs_cat_key *key2: pointer to the second key to compare&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   int: negative if key1&lt;key2, positive if key1&gt;key2, and 0 if key1==key2&n; * Preconditions:&n; *   key1 and key2 point to &quot;valid&quot; (struct hfs_cat_key)s.&n; * Postconditions:&n; *   This function has no side-effects&n; */
DECL|function|hfs_cat_keycmp
r_int
id|hfs_cat_keycmp
c_func
(paren
r_const
id|btree_key
op_star
id|key1
comma
r_const
id|btree_key
op_star
id|key2
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|be32_to_cpu
c_func
(paren
id|key1-&gt;cat.ParID
)paren
op_minus
id|be32_to_cpu
c_func
(paren
id|key2-&gt;cat.ParID
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
id|retval
op_assign
id|hfs_strcmp
c_func
(paren
id|key1-&gt;cat.CName.name
comma
id|key1-&gt;cat.CName.len
comma
id|key2-&gt;cat.CName.name
comma
id|key2-&gt;cat.CName.len
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Try to get a catalog entry for given catalog id */
singleline_comment|// move to read_super???
DECL|function|hfs_cat_find_brec
r_int
id|hfs_cat_find_brec
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u32
id|cnid
comma
r_struct
id|hfs_find_data
op_star
id|fd
)paren
(brace
id|hfs_cat_rec
id|rec
suffix:semicolon
r_int
id|res
comma
id|len
comma
id|type
suffix:semicolon
id|hfs_cat_build_key
c_func
(paren
id|fd-&gt;search_key
comma
id|cnid
comma
l_int|NULL
)paren
suffix:semicolon
id|res
op_assign
id|hfs_brec_read
c_func
(paren
id|fd
comma
op_amp
id|rec
comma
r_sizeof
(paren
id|rec
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_return
id|res
suffix:semicolon
id|type
op_assign
id|rec.type
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|HFS_CDR_THD
op_logical_and
id|type
op_ne
id|HFS_CDR_FTH
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HFS-fs: Found bad thread record in catalog&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|fd-&gt;search_key-&gt;cat.ParID
op_assign
id|rec.thread.ParID
suffix:semicolon
id|len
op_assign
id|fd-&gt;search_key-&gt;cat.CName.len
op_assign
id|rec.thread.CName.len
suffix:semicolon
id|memcpy
c_func
(paren
id|fd-&gt;search_key-&gt;cat.CName.name
comma
id|rec.thread.CName.name
comma
id|len
)paren
suffix:semicolon
r_return
id|hfs_brec_find
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_cat_delete()&n; *&n; * Delete the indicated file or directory.&n; * The associated thread is also removed unless (&squot;with_thread&squot;==0).&n; */
DECL|function|hfs_cat_delete
r_int
id|hfs_cat_delete
c_func
(paren
id|u32
id|cnid
comma
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|str
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|hfs_find_data
id|fd
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_int
id|res
comma
id|type
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_CAT_MOD
comma
l_string|&quot;delete_cat: %s,%u&bslash;n&quot;
comma
id|str
ques
c_cond
id|str-&gt;name
suffix:colon
l_int|NULL
comma
id|cnid
)paren
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
id|hfs_find_init
c_func
(paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cat_tree
comma
op_amp
id|fd
)paren
suffix:semicolon
id|hfs_cat_build_key
c_func
(paren
id|fd.search_key
comma
id|dir-&gt;i_ino
comma
id|str
)paren
suffix:semicolon
id|res
op_assign
id|hfs_brec_find
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|out
suffix:semicolon
id|type
op_assign
id|hfs_bnode_read_u8
c_func
(paren
id|fd.bnode
comma
id|fd.entryoffset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|HFS_CDR_FIL
)paren
(brace
r_struct
id|hfs_cat_file
id|file
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|fd.bnode
comma
op_amp
id|file
comma
id|fd.entryoffset
comma
r_sizeof
(paren
id|file
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|be32_to_cpu
c_func
(paren
id|file.FlNum
)paren
op_eq
id|cnid
)paren
(brace
macro_line|#if 0
id|hfs_free_fork
c_func
(paren
id|sb
comma
op_amp
id|file
comma
id|HFS_FK_DATA
)paren
suffix:semicolon
macro_line|#endif
id|hfs_free_fork
c_func
(paren
id|sb
comma
op_amp
id|file
comma
id|HFS_FK_RSRC
)paren
suffix:semicolon
)brace
)brace
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|HFS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|open_dir_list
)paren
(brace
r_struct
id|hfs_readdir_data
op_star
id|rd
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|hfs_readdir_data
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd.tree
op_member_access_from_pointer
id|keycmp
c_func
(paren
id|fd.search_key
comma
(paren
r_void
op_star
)paren
op_amp
id|rd-&gt;key
)paren
OL
l_int|0
)paren
id|rd-&gt;file-&gt;f_pos
op_decrement
suffix:semicolon
)brace
id|res
op_assign
id|hfs_brec_remove
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|out
suffix:semicolon
id|hfs_cat_build_key
c_func
(paren
id|fd.search_key
comma
id|cnid
comma
l_int|NULL
)paren
suffix:semicolon
id|res
op_assign
id|hfs_brec_find
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|res
op_assign
id|hfs_brec_remove
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|out
suffix:semicolon
)brace
id|dir-&gt;i_size
op_decrement
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|hfs_find_exit
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_cat_move()&n; *&n; * Rename a file or directory, possibly to a new directory.&n; * If the destination exists it is removed and a&n; * (struct hfs_cat_entry) for it is returned in &squot;*result&squot;.&n; */
DECL|function|hfs_cat_move
r_int
id|hfs_cat_move
c_func
(paren
id|u32
id|cnid
comma
r_struct
id|inode
op_star
id|src_dir
comma
r_struct
id|qstr
op_star
id|src_name
comma
r_struct
id|inode
op_star
id|dst_dir
comma
r_struct
id|qstr
op_star
id|dst_name
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|hfs_find_data
id|src_fd
comma
id|dst_fd
suffix:semicolon
r_union
id|hfs_cat_rec
id|entry
suffix:semicolon
r_int
id|entry_size
comma
id|type
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dprint
c_func
(paren
id|DBG_CAT_MOD
comma
l_string|&quot;rename_cat: %u - %lu,%s - %lu,%s&bslash;n&quot;
comma
id|cnid
comma
id|src_dir-&gt;i_ino
comma
id|src_name-&gt;name
comma
id|dst_dir-&gt;i_ino
comma
id|dst_name-&gt;name
)paren
suffix:semicolon
id|sb
op_assign
id|src_dir-&gt;i_sb
suffix:semicolon
id|hfs_find_init
c_func
(paren
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cat_tree
comma
op_amp
id|src_fd
)paren
suffix:semicolon
id|dst_fd
op_assign
id|src_fd
suffix:semicolon
multiline_comment|/* find the old dir entry and read the data */
id|hfs_cat_build_key
c_func
(paren
id|src_fd.search_key
comma
id|src_dir-&gt;i_ino
comma
id|src_name
)paren
suffix:semicolon
id|err
op_assign
id|hfs_brec_find
c_func
(paren
op_amp
id|src_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|src_fd.bnode
comma
op_amp
id|entry
comma
id|src_fd.entryoffset
comma
id|src_fd.entrylength
)paren
suffix:semicolon
multiline_comment|/* create new dir entry with the data from the old entry */
id|hfs_cat_build_key
c_func
(paren
id|dst_fd.search_key
comma
id|dst_dir-&gt;i_ino
comma
id|dst_name
)paren
suffix:semicolon
id|err
op_assign
id|hfs_brec_find
c_func
(paren
op_amp
id|dst_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
op_minus
id|ENOENT
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|hfs_brec_insert
c_func
(paren
op_amp
id|dst_fd
comma
op_amp
id|entry
comma
id|src_fd.entrylength
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|dst_dir-&gt;i_size
op_increment
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dst_dir
)paren
suffix:semicolon
multiline_comment|/* finally remove the old entry */
id|hfs_cat_build_key
c_func
(paren
id|src_fd.search_key
comma
id|src_dir-&gt;i_ino
comma
id|src_name
)paren
suffix:semicolon
id|err
op_assign
id|hfs_brec_find
c_func
(paren
op_amp
id|src_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|hfs_brec_remove
c_func
(paren
op_amp
id|src_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|src_dir-&gt;i_size
op_decrement
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|src_dir
)paren
suffix:semicolon
id|type
op_assign
id|entry.type
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|HFS_CDR_FIL
op_logical_and
op_logical_neg
(paren
id|entry.file.Flags
op_amp
id|HFS_FIL_THD
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* remove old thread entry */
id|hfs_cat_build_key
c_func
(paren
id|src_fd.search_key
comma
id|cnid
comma
l_int|NULL
)paren
suffix:semicolon
id|err
op_assign
id|hfs_brec_find
c_func
(paren
op_amp
id|src_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|hfs_brec_remove
c_func
(paren
op_amp
id|src_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* create new thread entry */
id|hfs_cat_build_key
c_func
(paren
id|dst_fd.search_key
comma
id|cnid
comma
l_int|NULL
)paren
suffix:semicolon
id|entry_size
op_assign
id|hfs_cat_build_thread
c_func
(paren
op_amp
id|entry
comma
id|type
op_eq
id|HFS_CDR_FIL
ques
c_cond
id|HFS_CDR_FTH
suffix:colon
id|HFS_CDR_THD
comma
id|dst_dir-&gt;i_ino
comma
id|dst_name
)paren
suffix:semicolon
id|err
op_assign
id|hfs_brec_find
c_func
(paren
op_amp
id|dst_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
op_minus
id|ENOENT
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|hfs_brec_insert
c_func
(paren
op_amp
id|dst_fd
comma
op_amp
id|entry
comma
id|entry_size
)paren
suffix:semicolon
id|out
suffix:colon
id|hfs_bnode_put
c_func
(paren
id|dst_fd.bnode
)paren
suffix:semicolon
id|hfs_find_exit
c_func
(paren
op_amp
id|src_fd
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
