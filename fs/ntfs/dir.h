multiline_comment|/*&n; * dir.h - Header file for dir.c&n; *&n; * Copyright (C) 1997 R&#xfffd;gis Duchesne&n; */
DECL|macro|ITERATE_SPLIT_DONE
mdefine_line|#define ITERATE_SPLIT_DONE      1
DECL|enum|ntfs_iterate_e
r_enum
id|ntfs_iterate_e
(brace
DECL|enumerator|BY_POSITION
id|BY_POSITION
comma
DECL|enumerator|BY_NAME
id|BY_NAME
comma
DECL|enumerator|DIR_INSERT
id|DIR_INSERT
)brace
suffix:semicolon
multiline_comment|/* not all fields are used for all operations */
DECL|struct|ntfs_iterate_s
r_typedef
r_struct
id|ntfs_iterate_s
(brace
DECL|member|type
r_enum
id|ntfs_iterate_e
id|type
suffix:semicolon
DECL|member|dir
id|ntfs_inode
op_star
id|dir
suffix:semicolon
(def_block
r_union
(brace
DECL|member|pos
id|ntfs_u64
id|pos
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|u
)brace
)def_block
id|u
suffix:semicolon
DECL|member|result
r_char
op_star
id|result
suffix:semicolon
multiline_comment|/* pointer to entry if found */
DECL|member|name
id|ntfs_u16
op_star
id|name
suffix:semicolon
DECL|member|namelen
r_int
id|namelen
suffix:semicolon
DECL|member|block
r_int
id|block
suffix:semicolon
multiline_comment|/* current index record */
DECL|member|newblock
r_int
id|newblock
suffix:semicolon
multiline_comment|/* index record created in a split */
DECL|member|new_entry
r_char
op_star
id|new_entry
suffix:semicolon
DECL|member|new_entry_size
r_int
id|new_entry_size
suffix:semicolon
multiline_comment|/*ntfs_inode* new;*/
DECL|typedef|ntfs_iterate_s
)brace
id|ntfs_iterate_s
suffix:semicolon
r_int
id|ntfs_getdir_unsorted
c_func
(paren
id|ntfs_inode
op_star
id|ino
comma
id|ntfs_u32
op_star
id|p_high
comma
id|ntfs_u32
op_star
id|p_low
comma
r_int
(paren
op_star
id|cb
)paren
(paren
id|ntfs_u8
op_star
comma
r_void
op_star
)paren
comma
r_void
op_star
id|param
)paren
suffix:semicolon
r_int
id|ntfs_getdir_byname
c_func
(paren
id|ntfs_iterate_s
op_star
id|walk
)paren
suffix:semicolon
r_int
id|ntfs_dir_add
c_func
(paren
id|ntfs_inode
op_star
id|dir
comma
id|ntfs_inode
op_star
r_new
comma
id|ntfs_attribute
op_star
id|name
)paren
suffix:semicolon
r_int
id|ntfs_check_index_record
c_func
(paren
id|ntfs_inode
op_star
id|ino
comma
r_char
op_star
id|record
)paren
suffix:semicolon
r_int
id|ntfs_getdir_byposition
c_func
(paren
id|ntfs_iterate_s
op_star
id|walk
)paren
suffix:semicolon
r_int
id|ntfs_mkdir
c_func
(paren
id|ntfs_inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
id|ntfs_inode
op_star
id|ino
)paren
suffix:semicolon
r_int
id|ntfs_split_indexroot
c_func
(paren
id|ntfs_inode
op_star
id|ino
)paren
suffix:semicolon
r_int
id|ntfs_add_index_root
c_func
(paren
id|ntfs_inode
op_star
id|ino
comma
r_int
id|type
)paren
suffix:semicolon
eof
