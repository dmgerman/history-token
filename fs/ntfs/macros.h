multiline_comment|/*&n; *  macros.h&n; *&n; *  Copyright (C) 1995 Martin von L&#xfffd;wis&n; *  Copyright (C) 1996 R&#xfffd;gis Duchesne&n; */
DECL|macro|NTFS_FD
mdefine_line|#define NTFS_FD(vol)&t;&t;((vol)-&gt;u.fd)
multiline_comment|/* Linux */
macro_line|#ifdef NTFS_IN_LINUX_KERNEL
DECL|macro|NTFS_SB
mdefine_line|#define NTFS_SB(vol)&t;&t;((struct super_block*)(vol)-&gt;sb)
DECL|macro|NTFS_SB2VOL
mdefine_line|#define NTFS_SB2VOL(sb)         (&amp;(sb)-&gt;u.ntfs_sb)
DECL|macro|NTFS_INO2VOL
mdefine_line|#define NTFS_INO2VOL(ino)&t;(&amp;((ino)-&gt;i_sb-&gt;u.ntfs_sb))
DECL|macro|NTFS_LINO2NINO
mdefine_line|#define NTFS_LINO2NINO(ino)     (&amp;((ino)-&gt;u.ntfs_i))
macro_line|#else
DECL|macro|NTFS_SB
mdefine_line|#define NTFS_SB(vol)&t;&t;((struct super_block*)(vol)-&gt;u.sb)
DECL|macro|NTFS_SB2VOL
mdefine_line|#define NTFS_SB2VOL(sb)&t;&t;((ntfs_volume*)(sb)-&gt;u.generic_sbp)
DECL|macro|NTFS_INO2VOL
mdefine_line|#define NTFS_INO2VOL(ino)&t;((ntfs_volume*)((ino)-&gt;i_sb-&gt;u.generic_sbp))
DECL|macro|NTFS_LINO2NINO
mdefine_line|#define NTFS_LINO2NINO(ino)     ((ntfs_inode*)((ino)-&gt;u.generic_ip))
macro_line|#endif
multiline_comment|/* BSD */
DECL|macro|NTFS_MNT
mdefine_line|#define NTFS_MNT(vol)&t;&t;((struct mount*)(vol)-&gt;u.sb)
DECL|macro|NTFS_MNT2VOL
mdefine_line|#define NTFS_MNT2VOL(sb)&t;((ntfs_volume*)(sb)-&gt;mnt_data)
DECL|macro|NTFS_V2INO
mdefine_line|#define NTFS_V2INO(ino)&t;&t;((ntfs_inode*)((ino)-&gt;v_data))
multiline_comment|/* Classical min and max macros still missing in standard headers... */
macro_line|#ifndef min
DECL|macro|min
mdefine_line|#define min(a,b)&t;((a) &lt;= (b) ? (a) : (b))
DECL|macro|max
mdefine_line|#define max(a,b)&t;((a) &gt;= (b) ? (a) : (b))
macro_line|#endif
DECL|macro|IS_MAGIC
mdefine_line|#define IS_MAGIC(a,b)&t;&t;(*(int*)(a)==*(int*)(b))
DECL|macro|IS_MFT_RECORD
mdefine_line|#define IS_MFT_RECORD(a)&t;IS_MAGIC((a),&quot;FILE&quot;)
DECL|macro|IS_NTFS_VOLUME
mdefine_line|#define IS_NTFS_VOLUME(a)&t;IS_MAGIC((a)+3,&quot;NTFS&quot;)
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
multiline_comment|/*&n; * Local variables:&n; *  c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
