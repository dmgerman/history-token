multiline_comment|/*&n; * macros.h&n; *&n; * Copyright (C) 1995 Martin von L&#xfffd;wis&n; * Copyright (C) 1996 R&#xfffd;gis Duchesne&n; * Copyright (c) 2001 Anton Altaparmakov&n; */
macro_line|#include &lt;linux/ntfs_fs_i.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|NTFS_FD
mdefine_line|#define NTFS_FD(vol)&t;&t;((vol)-&gt;u.fd)
DECL|macro|NTFS_SB
mdefine_line|#define NTFS_SB(vol)&t;&t;((struct super_block*)(vol)-&gt;sb)
DECL|macro|NTFS_SB2VOL
mdefine_line|#define NTFS_SB2VOL(sb)         (&amp;(sb)-&gt;u.ntfs_sb)
DECL|macro|NTFS_INO2VOL
mdefine_line|#define NTFS_INO2VOL(ino)&t;(&amp;((ino)-&gt;i_sb-&gt;u.ntfs_sb))
DECL|function|ntfs_i
r_static
r_inline
r_struct
id|ntfs_i
op_star
id|ntfs_i
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|inode
comma
r_struct
id|ntfs_i
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|macro|NTFS_I
mdefine_line|#define NTFS_I(ino)     (&amp;ntfs_i(ino)-&gt;n)
DECL|function|VFS_I
r_static
r_inline
r_struct
id|inode
op_star
id|VFS_I
c_func
(paren
r_struct
id|ntfs_inode_info
op_star
id|ntfs_ino
)paren
(brace
r_return
op_amp
id|list_entry
c_func
(paren
id|ntfs_ino
comma
r_struct
id|ntfs_i
comma
id|n
)paren
op_member_access_from_pointer
id|vfs_inode
suffix:semicolon
)brace
DECL|macro|IS_MAGIC
mdefine_line|#define IS_MAGIC(a,b)&t;&t;(*(int*)(a) == *(int*)(b))
DECL|macro|IS_MFT_RECORD
mdefine_line|#define IS_MFT_RECORD(a)&t;IS_MAGIC((a),&quot;FILE&quot;)
DECL|macro|IS_INDEX_RECORD
mdefine_line|#define IS_INDEX_RECORD(a)&t;IS_MAGIC((a),&quot;INDX&quot;)
multiline_comment|/* &squot;NTFS&squot; in little endian */
DECL|macro|NTFS_SUPER_MAGIC
mdefine_line|#define NTFS_SUPER_MAGIC&t;0x5346544E
DECL|macro|NTFS_AFLAG_RO
mdefine_line|#define NTFS_AFLAG_RO           1
DECL|macro|NTFS_AFLAG_HIDDEN
mdefine_line|#define NTFS_AFLAG_HIDDEN       2
DECL|macro|NTFS_AFLAG_SYSTEM
mdefine_line|#define NTFS_AFLAG_SYSTEM       4
DECL|macro|NTFS_AFLAG_ARCHIVE
mdefine_line|#define NTFS_AFLAG_ARCHIVE      20
DECL|macro|NTFS_AFLAG_COMPRESSED
mdefine_line|#define NTFS_AFLAG_COMPRESSED   0x800
DECL|macro|NTFS_AFLAG_DIR
mdefine_line|#define NTFS_AFLAG_DIR          0x10000000
eof
