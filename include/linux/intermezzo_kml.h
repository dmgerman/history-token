macro_line|#ifndef __INTERMEZZO_KML_H
DECL|macro|__INTERMEZZO_KML_H
mdefine_line|#define __INTERMEZZO_KML_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/intermezzo_psdev.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/intermezzo_journal.h&gt;
DECL|macro|PRESTO_KML_MAJOR_VERSION
mdefine_line|#define PRESTO_KML_MAJOR_VERSION 0x00010000
DECL|macro|PRESTO_KML_MINOR_VERSION
mdefine_line|#define PRESTO_KML_MINOR_VERSION 0x00002001
DECL|macro|PRESTO_OP_NOOP
mdefine_line|#define PRESTO_OP_NOOP          0
DECL|macro|PRESTO_OP_CREATE
mdefine_line|#define PRESTO_OP_CREATE        1
DECL|macro|PRESTO_OP_MKDIR
mdefine_line|#define PRESTO_OP_MKDIR         2
DECL|macro|PRESTO_OP_UNLINK
mdefine_line|#define PRESTO_OP_UNLINK        3
DECL|macro|PRESTO_OP_RMDIR
mdefine_line|#define PRESTO_OP_RMDIR         4
DECL|macro|PRESTO_OP_CLOSE
mdefine_line|#define PRESTO_OP_CLOSE         5
DECL|macro|PRESTO_OP_SYMLINK
mdefine_line|#define PRESTO_OP_SYMLINK       6
DECL|macro|PRESTO_OP_RENAME
mdefine_line|#define PRESTO_OP_RENAME        7
DECL|macro|PRESTO_OP_SETATTR
mdefine_line|#define PRESTO_OP_SETATTR       8
DECL|macro|PRESTO_OP_LINK
mdefine_line|#define PRESTO_OP_LINK          9
DECL|macro|PRESTO_OP_OPEN
mdefine_line|#define PRESTO_OP_OPEN          10
DECL|macro|PRESTO_OP_MKNOD
mdefine_line|#define PRESTO_OP_MKNOD         11
DECL|macro|PRESTO_OP_WRITE
mdefine_line|#define PRESTO_OP_WRITE         12
DECL|macro|PRESTO_OP_RELEASE
mdefine_line|#define PRESTO_OP_RELEASE       13
DECL|macro|PRESTO_OP_TRUNC
mdefine_line|#define PRESTO_OP_TRUNC         14
DECL|macro|PRESTO_OP_SETEXTATTR
mdefine_line|#define PRESTO_OP_SETEXTATTR    15
DECL|macro|PRESTO_OP_DELEXTATTR
mdefine_line|#define PRESTO_OP_DELEXTATTR    16
DECL|macro|PRESTO_LML_DONE
mdefine_line|#define PRESTO_LML_DONE     &t;1 /* flag to get first write to do LML */
DECL|macro|KML_KOP_MARK
mdefine_line|#define KML_KOP_MARK            0xffff
DECL|struct|presto_lml_data
r_struct
id|presto_lml_data
(brace
DECL|member|rec_offset
id|loff_t
id|rec_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|big_journal_prefix
r_struct
id|big_journal_prefix
(brace
DECL|member|len
id|u32
id|len
suffix:semicolon
DECL|member|version
id|u32
id|version
suffix:semicolon
DECL|member|pid
id|u32
id|pid
suffix:semicolon
DECL|member|uid
id|u32
id|uid
suffix:semicolon
DECL|member|fsuid
id|u32
id|fsuid
suffix:semicolon
DECL|member|fsgid
id|u32
id|fsgid
suffix:semicolon
DECL|member|opcode
id|u32
id|opcode
suffix:semicolon
DECL|member|ngroups
id|u32
id|ngroups
suffix:semicolon
DECL|member|groups
id|u32
id|groups
(braket
id|NGROUPS_MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|kml_opcode
r_enum
id|kml_opcode
(brace
DECL|enumerator|KML_CREATE
id|KML_CREATE
op_assign
l_int|1
comma
DECL|enumerator|KML_MKDIR
id|KML_MKDIR
comma
DECL|enumerator|KML_UNLINK
id|KML_UNLINK
comma
DECL|enumerator|KML_RMDIR
id|KML_RMDIR
comma
DECL|enumerator|KML_CLOSE
id|KML_CLOSE
comma
DECL|enumerator|KML_SYMLINK
id|KML_SYMLINK
comma
DECL|enumerator|KML_RENAME
id|KML_RENAME
comma
DECL|enumerator|KML_SETATTR
id|KML_SETATTR
comma
DECL|enumerator|KML_LINK
id|KML_LINK
comma
DECL|enumerator|KML_OPEN
id|KML_OPEN
comma
DECL|enumerator|KML_MKNOD
id|KML_MKNOD
comma
DECL|enumerator|KML_ENDMARK
id|KML_ENDMARK
op_assign
l_int|0xff
)brace
suffix:semicolon
DECL|struct|kml_create
r_struct
id|kml_create
(brace
DECL|member|path
r_char
op_star
id|path
suffix:semicolon
DECL|member|new_objectv
r_struct
id|presto_version
id|new_objectv
comma
DECL|member|old_parentv
id|old_parentv
comma
DECL|member|new_parentv
id|new_parentv
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|uid
r_int
id|uid
suffix:semicolon
DECL|member|gid
r_int
id|gid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_open
r_struct
id|kml_open
(brace
)brace
suffix:semicolon
DECL|struct|kml_mkdir
r_struct
id|kml_mkdir
(brace
DECL|member|path
r_char
op_star
id|path
suffix:semicolon
DECL|member|new_objectv
r_struct
id|presto_version
id|new_objectv
comma
DECL|member|old_parentv
id|old_parentv
comma
DECL|member|new_parentv
id|new_parentv
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|uid
r_int
id|uid
suffix:semicolon
DECL|member|gid
r_int
id|gid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_unlink
r_struct
id|kml_unlink
(brace
DECL|member|path
r_char
op_star
id|path
comma
DECL|member|name
op_star
id|name
suffix:semicolon
DECL|member|old_tgtv
r_struct
id|presto_version
id|old_tgtv
comma
DECL|member|old_parentv
id|old_parentv
comma
DECL|member|new_parentv
id|new_parentv
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_rmdir
r_struct
id|kml_rmdir
(brace
DECL|member|path
r_char
op_star
id|path
comma
DECL|member|name
op_star
id|name
suffix:semicolon
DECL|member|old_tgtv
r_struct
id|presto_version
id|old_tgtv
comma
DECL|member|old_parentv
id|old_parentv
comma
DECL|member|new_parentv
id|new_parentv
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_close
r_struct
id|kml_close
(brace
DECL|member|open_mode
r_int
id|open_mode
comma
DECL|member|open_uid
id|open_uid
comma
DECL|member|open_gid
id|open_gid
suffix:semicolon
DECL|member|path
r_char
op_star
id|path
suffix:semicolon
DECL|member|new_objectv
r_struct
id|presto_version
id|new_objectv
suffix:semicolon
DECL|member|ino
id|__u64
id|ino
suffix:semicolon
DECL|member|generation
r_int
id|generation
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_symlink
r_struct
id|kml_symlink
(brace
DECL|member|sourcepath
r_char
op_star
id|sourcepath
comma
DECL|member|targetpath
op_star
id|targetpath
suffix:semicolon
DECL|member|new_objectv
r_struct
id|presto_version
id|new_objectv
comma
DECL|member|old_parentv
id|old_parentv
comma
DECL|member|new_parentv
id|new_parentv
suffix:semicolon
DECL|member|uid
r_int
id|uid
suffix:semicolon
DECL|member|gid
r_int
id|gid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_rename
r_struct
id|kml_rename
(brace
DECL|member|sourcepath
r_char
op_star
id|sourcepath
comma
DECL|member|targetpath
op_star
id|targetpath
suffix:semicolon
DECL|member|old_objectv
r_struct
id|presto_version
id|old_objectv
comma
DECL|member|new_objectv
id|new_objectv
comma
DECL|member|old_tgtv
id|old_tgtv
comma
DECL|member|new_tgtv
id|new_tgtv
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_setattr
r_struct
id|kml_setattr
(brace
DECL|member|path
r_char
op_star
id|path
suffix:semicolon
DECL|member|old_objectv
r_struct
id|presto_version
id|old_objectv
suffix:semicolon
DECL|member|iattr
r_struct
id|iattr
id|iattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_link
r_struct
id|kml_link
(brace
DECL|member|sourcepath
r_char
op_star
id|sourcepath
comma
DECL|member|targetpath
op_star
id|targetpath
suffix:semicolon
DECL|member|new_objectv
r_struct
id|presto_version
id|new_objectv
comma
DECL|member|old_parentv
id|old_parentv
comma
DECL|member|new_parentv
id|new_parentv
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_mknod
r_struct
id|kml_mknod
(brace
DECL|member|path
r_char
op_star
id|path
suffix:semicolon
DECL|member|new_objectv
r_struct
id|presto_version
id|new_objectv
comma
DECL|member|old_parentv
id|old_parentv
comma
DECL|member|new_parentv
id|new_parentv
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|uid
r_int
id|uid
suffix:semicolon
DECL|member|gid
r_int
id|gid
suffix:semicolon
DECL|member|major
r_int
id|major
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* kml record items for optimizing */
DECL|struct|kml_kop_node
r_struct
id|kml_kop_node
(brace
DECL|member|kml_recno
id|u32
id|kml_recno
suffix:semicolon
DECL|member|kml_flag
id|u32
id|kml_flag
suffix:semicolon
DECL|member|kml_op
id|u32
id|kml_op
suffix:semicolon
DECL|member|i_nlink
id|nlink_t
id|i_nlink
suffix:semicolon
DECL|member|i_ino
id|u32
id|i_ino
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_kop_lnode
r_struct
id|kml_kop_lnode
(brace
DECL|member|chains
r_struct
id|list_head
id|chains
suffix:semicolon
DECL|member|node
r_struct
id|kml_kop_node
id|node
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_endmark
r_struct
id|kml_endmark
(brace
DECL|member|total
id|u32
id|total
suffix:semicolon
DECL|member|kop
r_struct
id|kml_kop_node
op_star
id|kop
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* kml_flag */
DECL|macro|KML_REC_DELETE
mdefine_line|#define  KML_REC_DELETE               1
DECL|macro|KML_REC_EXIST
mdefine_line|#define  KML_REC_EXIST                0
DECL|struct|kml_optimize
r_struct
id|kml_optimize
(brace
DECL|member|kml_chains
r_struct
id|list_head
id|kml_chains
suffix:semicolon
DECL|member|kml_flag
id|u32
id|kml_flag
suffix:semicolon
DECL|member|kml_op
id|u32
id|kml_op
suffix:semicolon
DECL|member|i_nlink
id|nlink_t
id|i_nlink
suffix:semicolon
DECL|member|i_ino
id|u32
id|i_ino
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_rec
r_struct
id|kml_rec
(brace
multiline_comment|/* attribute of this record */
DECL|member|rec_size
r_int
id|rec_size
suffix:semicolon
DECL|member|rec_kml_offset
r_int
id|rec_kml_offset
suffix:semicolon
DECL|member|rec_head
r_struct
id|big_journal_prefix
id|rec_head
suffix:semicolon
r_union
(brace
DECL|member|create
r_struct
id|kml_create
id|create
suffix:semicolon
DECL|member|open
r_struct
id|kml_open
id|open
suffix:semicolon
DECL|member|mkdir
r_struct
id|kml_mkdir
id|mkdir
suffix:semicolon
DECL|member|unlink
r_struct
id|kml_unlink
id|unlink
suffix:semicolon
DECL|member|rmdir
r_struct
id|kml_rmdir
id|rmdir
suffix:semicolon
DECL|member|close
r_struct
id|kml_close
id|close
suffix:semicolon
DECL|member|symlink
r_struct
id|kml_symlink
id|symlink
suffix:semicolon
DECL|member|rename
r_struct
id|kml_rename
id|rename
suffix:semicolon
DECL|member|setattr
r_struct
id|kml_setattr
id|setattr
suffix:semicolon
DECL|member|mknod
r_struct
id|kml_mknod
id|mknod
suffix:semicolon
DECL|member|link
r_struct
id|kml_link
id|link
suffix:semicolon
DECL|member|endmark
r_struct
id|kml_endmark
id|endmark
suffix:semicolon
DECL|member|rec_kml
)brace
id|rec_kml
suffix:semicolon
DECL|member|rec_tail
r_struct
id|journal_suffix
id|rec_tail
suffix:semicolon
multiline_comment|/* for kml optimize only */
DECL|member|kml_optimize
r_struct
id|kml_optimize
id|kml_optimize
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* kml record items for optimizing */
r_extern
r_void
id|kml_kop_init
(paren
r_struct
id|presto_file_set
op_star
id|fset
)paren
suffix:semicolon
r_extern
r_void
id|kml_kop_addrec
(paren
r_struct
id|presto_file_set
op_star
id|fset
comma
r_struct
id|inode
op_star
id|ino
comma
id|u32
id|op
comma
id|u32
id|flag
)paren
suffix:semicolon
r_extern
r_int
id|kml_kop_flush
(paren
r_struct
id|presto_file_set
op_star
id|fset
)paren
suffix:semicolon
multiline_comment|/* defined in kml_setup.c */
r_extern
r_int
id|kml_init
(paren
r_struct
id|presto_file_set
op_star
id|fset
)paren
suffix:semicolon
r_extern
r_int
id|kml_cleanup
(paren
r_struct
id|presto_file_set
op_star
id|fset
)paren
suffix:semicolon
multiline_comment|/* defined in kml.c */
r_extern
r_int
id|begin_kml_reint
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|do_kml_reint
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|end_kml_reint
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* kml_utils.c */
r_extern
r_char
op_star
id|dlogit
(paren
r_void
op_star
id|tbuf
comma
r_const
r_void
op_star
id|sbuf
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_char
op_star
id|bdup_printf
(paren
r_char
op_star
id|format
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/* defined in kml_decode.c */
multiline_comment|/* printop */
DECL|macro|PRINT_KML_PREFIX
mdefine_line|#define  PRINT_KML_PREFIX             0x1
DECL|macro|PRINT_KML_SUFFIX
mdefine_line|#define  PRINT_KML_SUFFIX             0x2
DECL|macro|PRINT_KML_REC
mdefine_line|#define  PRINT_KML_REC                0x4
DECL|macro|PRINT_KML_OPTIMIZE
mdefine_line|#define  PRINT_KML_OPTIMIZE           0x8
DECL|macro|PRINT_KML_EXIST
mdefine_line|#define  PRINT_KML_EXIST              0x10
DECL|macro|PRINT_KML_DELETE
mdefine_line|#define  PRINT_KML_DELETE             0x20
r_extern
r_void
id|kml_printrec
(paren
r_struct
id|kml_rec
op_star
id|rec
comma
r_int
id|printop
)paren
suffix:semicolon
r_extern
r_int
id|print_allkmlrec
(paren
r_struct
id|list_head
op_star
id|head
comma
r_int
id|printop
)paren
suffix:semicolon
r_extern
r_int
id|delete_kmlrec
(paren
r_struct
id|list_head
op_star
id|head
)paren
suffix:semicolon
r_extern
r_int
id|kml_decoderec
(paren
r_char
op_star
id|buf
comma
r_int
id|pos
comma
r_int
id|buflen
comma
r_int
op_star
id|size
comma
r_struct
id|kml_rec
op_star
op_star
id|newrec
)paren
suffix:semicolon
r_extern
r_int
id|decode_kmlrec
(paren
r_struct
id|list_head
op_star
id|head
comma
r_char
op_star
id|kml_buf
comma
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_void
id|kml_freerec
(paren
r_struct
id|kml_rec
op_star
id|rec
)paren
suffix:semicolon
multiline_comment|/* defined in kml_reint.c */
DECL|macro|KML_CLOSE_BACKFETCH
mdefine_line|#define KML_CLOSE_BACKFETCH            1
r_extern
r_int
id|kml_reintbuf
(paren
r_struct
id|kml_fsdata
op_star
id|kml_fsdata
comma
r_char
op_star
id|mtpt
comma
r_struct
id|kml_rec
op_star
op_star
id|rec
)paren
suffix:semicolon
multiline_comment|/* defined in kml_setup.c */
r_extern
r_int
id|kml_init
(paren
r_struct
id|presto_file_set
op_star
id|fset
)paren
suffix:semicolon
r_extern
r_int
id|kml_cleanup
(paren
r_struct
id|presto_file_set
op_star
id|fset
)paren
suffix:semicolon
macro_line|#endif
eof
