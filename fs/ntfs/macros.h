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
DECL|macro|NTFS_LINO2NINO
mdefine_line|#define NTFS_LINO2NINO(ino)     ((struct ntfs_inode_info*)(&amp;((ino)-&gt;u.ntfs_i)))
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
r_struct
id|inode
op_star
id|i
op_assign
(paren
r_struct
id|inode
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|ntfs_ino
op_minus
(paren
(paren
r_char
op_star
)paren
op_amp
(paren
(paren
(paren
r_struct
id|inode
op_star
)paren
l_int|NULL
)paren
op_member_access_from_pointer
id|u.ntfs_i
)paren
op_minus
(paren
r_char
op_star
)paren
l_int|NULL
)paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|NTFS_LINO2NINO
c_func
(paren
id|i
)paren
op_ne
(paren
r_char
op_star
)paren
id|ntfs_ino
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|i
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
