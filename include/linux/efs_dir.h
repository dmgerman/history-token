multiline_comment|/*&n; * efs_dir.h&n; *&n; * Copyright (c) 1999 Al Smith&n; */
macro_line|#ifndef __EFS_DIR_H__
DECL|macro|__EFS_DIR_H__
mdefine_line|#define __EFS_DIR_H__
DECL|macro|EFS_DIRBSIZE_BITS
mdefine_line|#define EFS_DIRBSIZE_BITS&t;EFS_BLOCKSIZE_BITS
DECL|macro|EFS_DIRBSIZE
mdefine_line|#define EFS_DIRBSIZE&t;&t;(1 &lt;&lt; EFS_DIRBSIZE_BITS)
DECL|struct|efs_dentry
r_struct
id|efs_dentry
(brace
DECL|member|inode
r_int
r_int
id|inode
suffix:semicolon
DECL|member|namelen
r_int
r_char
id|namelen
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EFS_DENTSIZE
mdefine_line|#define EFS_DENTSIZE&t;(sizeof(struct efs_dentry) - 3 + 1)
DECL|macro|EFS_MAXNAMELEN
mdefine_line|#define EFS_MAXNAMELEN  ((1 &lt;&lt; (sizeof(char) * 8)) - 1)
DECL|macro|EFS_DIRBLK_HEADERSIZE
mdefine_line|#define EFS_DIRBLK_HEADERSIZE&t;4
DECL|macro|EFS_DIRBLK_MAGIC
mdefine_line|#define EFS_DIRBLK_MAGIC&t;0xbeef&t;/* moo */
DECL|struct|efs_dir
r_struct
id|efs_dir
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|firstused
r_int
r_char
id|firstused
suffix:semicolon
DECL|member|slots
r_int
r_char
id|slots
suffix:semicolon
DECL|member|space
r_int
r_char
id|space
(braket
id|EFS_DIRBSIZE
op_minus
id|EFS_DIRBLK_HEADERSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EFS_MAXENTS
mdefine_line|#define EFS_MAXENTS &bslash;&n;&t;((EFS_DIRBSIZE - EFS_DIRBLK_HEADERSIZE) / &bslash;&n;&t; (EFS_DENTSIZE + sizeof(char)))
DECL|macro|EFS_SLOTAT
mdefine_line|#define EFS_SLOTAT(dir, slot) EFS_REALOFF((dir)-&gt;space[slot])
DECL|macro|EFS_REALOFF
mdefine_line|#define EFS_REALOFF(offset) ((offset &lt;&lt; 1))
macro_line|#endif /* __EFS_DIR_H__ */
eof
