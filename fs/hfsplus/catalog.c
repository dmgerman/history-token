multiline_comment|/*&n; *  linux/fs/hfsplus/catalog.c&n; *&n; * Copyright (C) 2001&n; * Brad Boyer (flar@allandria.com)&n; * (C) 2003 Ardis Technologies &lt;roman@ardistech.com&gt;&n; *&n; * Handling of catalog records&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &quot;hfsplus_fs.h&quot;
macro_line|#include &quot;hfsplus_raw.h&quot;
DECL|function|hfsplus_cat_cmp_key
r_int
id|hfsplus_cat_cmp_key
c_func
(paren
id|hfsplus_btree_key
op_star
id|k1
comma
id|hfsplus_btree_key
op_star
id|k2
)paren
(brace
id|__be32
id|k1p
comma
id|k2p
suffix:semicolon
id|k1p
op_assign
id|k1-&gt;cat.parent
suffix:semicolon
id|k2p
op_assign
id|k2-&gt;cat.parent
suffix:semicolon
r_if
c_cond
(paren
id|k1p
op_ne
id|k2p
)paren
r_return
id|be32_to_cpu
c_func
(paren
id|k1p
)paren
OL
id|be32_to_cpu
c_func
(paren
id|k2p
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|1
suffix:semicolon
r_return
id|hfsplus_unistrcmp
c_func
(paren
op_amp
id|k1-&gt;cat.name
comma
op_amp
id|k2-&gt;cat.name
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_cat_build_key
r_void
id|hfsplus_cat_build_key
c_func
(paren
id|hfsplus_btree_key
op_star
id|key
comma
id|u32
id|parent
comma
r_struct
id|qstr
op_star
id|str
)paren
(brace
r_int
id|len
suffix:semicolon
id|key-&gt;cat.parent
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
id|str
)paren
(brace
id|hfsplus_asc2uni
c_func
(paren
op_amp
id|key-&gt;cat.name
comma
id|str-&gt;name
comma
id|str-&gt;len
)paren
suffix:semicolon
id|len
op_assign
id|be16_to_cpu
c_func
(paren
id|key-&gt;cat.name.length
)paren
suffix:semicolon
)brace
r_else
(brace
id|key-&gt;cat.name.length
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
)brace
id|key-&gt;key_len
op_assign
id|cpu_to_be16
c_func
(paren
l_int|6
op_plus
l_int|2
op_star
id|len
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_cat_build_key_uni
r_static
r_void
id|hfsplus_cat_build_key_uni
c_func
(paren
id|hfsplus_btree_key
op_star
id|key
comma
id|u32
id|parent
comma
r_struct
id|hfsplus_unistr
op_star
id|name
)paren
(brace
r_int
id|ustrlen
suffix:semicolon
id|ustrlen
op_assign
id|be16_to_cpu
c_func
(paren
id|name-&gt;length
)paren
suffix:semicolon
id|key-&gt;cat.parent
op_assign
id|cpu_to_be32
c_func
(paren
id|parent
)paren
suffix:semicolon
id|key-&gt;cat.name.length
op_assign
id|cpu_to_be16
c_func
(paren
id|ustrlen
)paren
suffix:semicolon
id|ustrlen
op_mul_assign
l_int|2
suffix:semicolon
id|memcpy
c_func
(paren
id|key-&gt;cat.name.unicode
comma
id|name-&gt;unicode
comma
id|ustrlen
)paren
suffix:semicolon
id|key-&gt;key_len
op_assign
id|cpu_to_be16
c_func
(paren
l_int|6
op_plus
id|ustrlen
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_set_perms
r_static
r_void
id|hfsplus_set_perms
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|hfsplus_perm
op_star
id|perms
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_flags
op_amp
id|S_IMMUTABLE
)paren
id|perms-&gt;rootflags
op_or_assign
id|HFSPLUS_FLG_IMMUTABLE
suffix:semicolon
r_else
id|perms-&gt;rootflags
op_and_assign
op_complement
id|HFSPLUS_FLG_IMMUTABLE
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_flags
op_amp
id|S_APPEND
)paren
id|perms-&gt;rootflags
op_or_assign
id|HFSPLUS_FLG_APPEND
suffix:semicolon
r_else
id|perms-&gt;rootflags
op_and_assign
op_complement
id|HFSPLUS_FLG_APPEND
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|rootflags
op_assign
id|perms-&gt;rootflags
suffix:semicolon
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|userflags
op_assign
id|perms-&gt;userflags
suffix:semicolon
id|perms-&gt;mode
op_assign
id|cpu_to_be16
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
id|perms-&gt;owner
op_assign
id|cpu_to_be32
c_func
(paren
id|inode-&gt;i_uid
)paren
suffix:semicolon
id|perms-&gt;group
op_assign
id|cpu_to_be32
c_func
(paren
id|inode-&gt;i_gid
)paren
suffix:semicolon
)brace
DECL|function|hfsplus_cat_build_record
r_static
r_int
id|hfsplus_cat_build_record
c_func
(paren
id|hfsplus_cat_entry
op_star
id|entry
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
r_struct
id|hfsplus_cat_folder
op_star
id|folder
suffix:semicolon
id|folder
op_assign
op_amp
id|entry-&gt;folder
suffix:semicolon
id|memset
c_func
(paren
id|folder
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|folder
)paren
)paren
suffix:semicolon
id|folder-&gt;type
op_assign
id|cpu_to_be16
c_func
(paren
id|HFSPLUS_FOLDER
)paren
suffix:semicolon
id|folder-&gt;id
op_assign
id|cpu_to_be32
c_func
(paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|folder-&gt;create_date
op_assign
id|folder-&gt;content_mod_date
op_assign
id|folder-&gt;attribute_mod_date
op_assign
id|folder-&gt;access_date
op_assign
id|hfsp_now2mt
c_func
(paren
)paren
suffix:semicolon
id|hfsplus_set_perms
c_func
(paren
id|inode
comma
op_amp
id|folder-&gt;permissions
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_eq
id|HFSPLUS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
dot
id|hidden_dir
)paren
multiline_comment|/* invisible and namelocked */
id|folder-&gt;user_info.frFlags
op_assign
id|cpu_to_be16
c_func
(paren
l_int|0x5000
)paren
suffix:semicolon
r_return
r_sizeof
(paren
op_star
id|folder
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|hfsplus_cat_file
op_star
id|file
suffix:semicolon
id|file
op_assign
op_amp
id|entry-&gt;file
suffix:semicolon
id|memset
c_func
(paren
id|file
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|file
)paren
)paren
suffix:semicolon
id|file-&gt;type
op_assign
id|cpu_to_be16
c_func
(paren
id|HFSPLUS_FILE
)paren
suffix:semicolon
id|file-&gt;flags
op_assign
id|cpu_to_be16
c_func
(paren
id|HFSPLUS_FILE_THREAD_EXISTS
)paren
suffix:semicolon
id|file-&gt;id
op_assign
id|cpu_to_be32
c_func
(paren
id|cnid
)paren
suffix:semicolon
id|file-&gt;create_date
op_assign
id|file-&gt;content_mod_date
op_assign
id|file-&gt;attribute_mod_date
op_assign
id|file-&gt;access_date
op_assign
id|hfsp_now2mt
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cnid
op_eq
id|inode-&gt;i_ino
)paren
(brace
id|hfsplus_set_perms
c_func
(paren
id|inode
comma
op_amp
id|file-&gt;permissions
)paren
suffix:semicolon
id|file-&gt;user_info.fdType
op_assign
id|cpu_to_be32
c_func
(paren
id|HFSPLUS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
dot
id|type
)paren
suffix:semicolon
id|file-&gt;user_info.fdCreator
op_assign
id|cpu_to_be32
c_func
(paren
id|HFSPLUS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
dot
id|creator
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|file-&gt;permissions.rootflags
op_or
id|file-&gt;permissions.userflags
)paren
op_amp
id|HFSPLUS_FLG_IMMUTABLE
)paren
id|file-&gt;flags
op_or_assign
id|cpu_to_be16
c_func
(paren
id|HFSPLUS_FILE_LOCKED
)paren
suffix:semicolon
)brace
r_else
(brace
id|file-&gt;user_info.fdType
op_assign
id|cpu_to_be32
c_func
(paren
id|HFSP_HARDLINK_TYPE
)paren
suffix:semicolon
id|file-&gt;user_info.fdCreator
op_assign
id|cpu_to_be32
c_func
(paren
id|HFSP_HFSPLUS_CREATOR
)paren
suffix:semicolon
id|file-&gt;user_info.fdFlags
op_assign
id|cpu_to_be16
c_func
(paren
l_int|0x100
)paren
suffix:semicolon
id|file-&gt;permissions.dev
op_assign
id|cpu_to_be32
c_func
(paren
id|HFSPLUS_I
c_func
(paren
id|inode
)paren
dot
id|dev
)paren
suffix:semicolon
)brace
r_return
r_sizeof
(paren
op_star
id|file
)paren
suffix:semicolon
)brace
)brace
DECL|function|hfsplus_fill_cat_thread
r_static
r_int
id|hfsplus_fill_cat_thread
c_func
(paren
id|hfsplus_cat_entry
op_star
id|entry
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
id|str
)paren
(brace
id|entry-&gt;type
op_assign
id|cpu_to_be16
c_func
(paren
id|type
)paren
suffix:semicolon
id|entry-&gt;thread.reserved
op_assign
l_int|0
suffix:semicolon
id|entry-&gt;thread.parentID
op_assign
id|cpu_to_be32
c_func
(paren
id|parentid
)paren
suffix:semicolon
id|hfsplus_asc2uni
c_func
(paren
op_amp
id|entry-&gt;thread.nodeName
comma
id|str-&gt;name
comma
id|str-&gt;len
)paren
suffix:semicolon
r_return
l_int|10
op_plus
id|be16_to_cpu
c_func
(paren
id|entry-&gt;thread.nodeName.length
)paren
op_star
l_int|2
suffix:semicolon
)brace
multiline_comment|/* Try to get a catalog entry for given catalog id */
DECL|function|hfsplus_find_cat
r_int
id|hfsplus_find_cat
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
id|hfsplus_cat_entry
id|tmp
suffix:semicolon
r_int
id|err
suffix:semicolon
id|u16
id|type
suffix:semicolon
id|hfsplus_cat_build_key
c_func
(paren
id|fd-&gt;search_key
comma
id|cnid
comma
l_int|NULL
)paren
suffix:semicolon
id|err
op_assign
id|hfs_brec_read
c_func
(paren
id|fd
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|hfsplus_cat_entry
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|type
op_assign
id|be16_to_cpu
c_func
(paren
id|tmp.type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|HFSPLUS_FOLDER_THREAD
op_logical_and
id|type
op_ne
id|HFSPLUS_FILE_THREAD
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HFS+-fs: Found bad thread record in catalog&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|hfsplus_cat_build_key_uni
c_func
(paren
id|fd-&gt;search_key
comma
id|be32_to_cpu
c_func
(paren
id|tmp.thread.parentID
)paren
comma
op_amp
id|tmp.thread.nodeName
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
DECL|function|hfsplus_create_cat
r_int
id|hfsplus_create_cat
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
id|hfsplus_cat_entry
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
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
id|hfs_find_init
c_func
(paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|cat_tree
comma
op_amp
id|fd
)paren
suffix:semicolon
id|hfsplus_cat_build_key
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
id|hfsplus_fill_cat_thread
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
id|HFSPLUS_FOLDER_THREAD
suffix:colon
id|HFSPLUS_FILE_THREAD
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
id|err2
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
id|err2
suffix:semicolon
id|hfsplus_cat_build_key
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
id|hfsplus_cat_build_record
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
id|err1
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
id|err1
suffix:semicolon
id|dir-&gt;i_size
op_increment
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|hfs_find_exit
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err1
suffix:colon
id|hfsplus_cat_build_key
c_func
(paren
id|fd.search_key
comma
id|cnid
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hfs_brec_find
c_func
(paren
op_amp
id|fd
)paren
)paren
id|hfs_brec_remove
c_func
(paren
op_amp
id|fd
)paren
suffix:semicolon
id|err2
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
DECL|function|hfsplus_delete_cat
r_int
id|hfsplus_delete_cat
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
id|hfsplus_fork_raw
id|fork
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_int
id|err
comma
id|off
suffix:semicolon
id|u16
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
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|cat_tree
comma
op_amp
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|str
)paren
(brace
r_int
id|len
suffix:semicolon
id|hfsplus_cat_build_key
c_func
(paren
id|fd.search_key
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
id|fd
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
id|off
op_assign
id|fd.entryoffset
op_plus
m_offsetof
(paren
r_struct
id|hfsplus_cat_thread
comma
id|nodeName
)paren
suffix:semicolon
id|fd.search_key-&gt;cat.parent
op_assign
id|cpu_to_be32
c_func
(paren
id|dir-&gt;i_ino
)paren
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|fd.bnode
comma
op_amp
id|fd.search_key-&gt;cat.name.length
comma
id|off
comma
l_int|2
)paren
suffix:semicolon
id|len
op_assign
id|be16_to_cpu
c_func
(paren
id|fd.search_key-&gt;cat.name.length
)paren
op_star
l_int|2
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|fd.bnode
comma
op_amp
id|fd.search_key-&gt;cat.name.unicode
comma
id|off
op_plus
l_int|2
comma
id|len
)paren
suffix:semicolon
id|fd.search_key-&gt;key_len
op_assign
id|cpu_to_be16
c_func
(paren
l_int|6
op_plus
id|len
)paren
suffix:semicolon
)brace
r_else
id|hfsplus_cat_build_key
c_func
(paren
id|fd.search_key
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
)paren
r_goto
id|out
suffix:semicolon
id|type
op_assign
id|hfs_bnode_read_u16
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
id|HFSPLUS_FILE
)paren
(brace
macro_line|#if 0
id|off
op_assign
id|fd.entryoffset
op_plus
m_offsetof
(paren
id|hfsplus_cat_file
comma
id|data_fork
)paren
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|fd.bnode
comma
op_amp
id|fork
comma
id|off
comma
r_sizeof
(paren
id|fork
)paren
)paren
suffix:semicolon
id|hfsplus_free_fork
c_func
(paren
id|sb
comma
id|cnid
comma
op_amp
id|fork
comma
id|HFSPLUS_TYPE_DATA
)paren
suffix:semicolon
macro_line|#endif
id|off
op_assign
id|fd.entryoffset
op_plus
m_offsetof
(paren
r_struct
id|hfsplus_cat_file
comma
id|rsrc_fork
)paren
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
id|fd.bnode
comma
op_amp
id|fork
comma
id|off
comma
r_sizeof
(paren
id|fork
)paren
)paren
suffix:semicolon
id|hfsplus_free_fork
c_func
(paren
id|sb
comma
id|cnid
comma
op_amp
id|fork
comma
id|HFSPLUS_TYPE_RSRC
)paren
suffix:semicolon
)brace
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|HFSPLUS_I
c_func
(paren
id|dir
)paren
dot
id|open_dir_list
)paren
(brace
r_struct
id|hfsplus_readdir_data
op_star
id|rd
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|hfsplus_readdir_data
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
id|err
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
id|err
)paren
r_goto
id|out
suffix:semicolon
id|hfsplus_cat_build_key
c_func
(paren
id|fd.search_key
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
id|fd
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
id|fd
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
id|dir-&gt;i_size
op_decrement
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
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
id|err
suffix:semicolon
)brace
DECL|function|hfsplus_rename_cat
r_int
id|hfsplus_rename_cat
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
id|hfsplus_cat_entry
id|entry
suffix:semicolon
r_int
id|entry_size
comma
id|type
suffix:semicolon
r_int
id|err
op_assign
l_int|0
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
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
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
id|hfsplus_cat_build_key
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
id|hfsplus_cat_build_key
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
id|dst_dir-&gt;i_mtime
op_assign
id|dst_dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dst_dir
)paren
suffix:semicolon
multiline_comment|/* finally remove the old entry */
id|hfsplus_cat_build_key
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
id|src_dir-&gt;i_mtime
op_assign
id|src_dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|src_dir
)paren
suffix:semicolon
multiline_comment|/* remove old thread entry */
id|hfsplus_cat_build_key
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
id|type
op_assign
id|hfs_bnode_read_u16
c_func
(paren
id|src_fd.bnode
comma
id|src_fd.entryoffset
)paren
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
id|hfsplus_cat_build_key
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
id|hfsplus_fill_cat_thread
c_func
(paren
op_amp
id|entry
comma
id|type
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
