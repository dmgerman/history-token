multiline_comment|/*&n; * NFS protocol definitions&n; *&n; * This file contains constants for Version 2 of the protocol.&n; */
macro_line|#ifndef _LINUX_NFS2_H
DECL|macro|_LINUX_NFS2_H
mdefine_line|#define _LINUX_NFS2_H
DECL|macro|NFS2_PORT
mdefine_line|#define NFS2_PORT&t;2049
DECL|macro|NFS2_MAXDATA
mdefine_line|#define NFS2_MAXDATA&t;8192
DECL|macro|NFS2_MAXPATHLEN
mdefine_line|#define NFS2_MAXPATHLEN&t;1024
DECL|macro|NFS2_MAXNAMLEN
mdefine_line|#define NFS2_MAXNAMLEN&t;255
DECL|macro|NFS2_MAXGROUPS
mdefine_line|#define NFS2_MAXGROUPS&t;16
DECL|macro|NFS2_FHSIZE
mdefine_line|#define NFS2_FHSIZE&t;32
DECL|macro|NFS2_COOKIESIZE
mdefine_line|#define NFS2_COOKIESIZE&t;4
DECL|macro|NFS2_FIFO_DEV
mdefine_line|#define NFS2_FIFO_DEV&t;(-1)
DECL|macro|NFS2MODE_FMT
mdefine_line|#define NFS2MODE_FMT&t;0170000
DECL|macro|NFS2MODE_DIR
mdefine_line|#define NFS2MODE_DIR&t;0040000
DECL|macro|NFS2MODE_CHR
mdefine_line|#define NFS2MODE_CHR&t;0020000
DECL|macro|NFS2MODE_BLK
mdefine_line|#define NFS2MODE_BLK&t;0060000
DECL|macro|NFS2MODE_REG
mdefine_line|#define NFS2MODE_REG&t;0100000
DECL|macro|NFS2MODE_LNK
mdefine_line|#define NFS2MODE_LNK&t;0120000
DECL|macro|NFS2MODE_SOCK
mdefine_line|#define NFS2MODE_SOCK&t;0140000
DECL|macro|NFS2MODE_FIFO
mdefine_line|#define NFS2MODE_FIFO&t;0010000
multiline_comment|/* NFSv2 file types - beware, these are not the same in NFSv3 */
DECL|enum|nfs2_ftype
r_enum
id|nfs2_ftype
(brace
DECL|enumerator|NF2NON
id|NF2NON
op_assign
l_int|0
comma
DECL|enumerator|NF2REG
id|NF2REG
op_assign
l_int|1
comma
DECL|enumerator|NF2DIR
id|NF2DIR
op_assign
l_int|2
comma
DECL|enumerator|NF2BLK
id|NF2BLK
op_assign
l_int|3
comma
DECL|enumerator|NF2CHR
id|NF2CHR
op_assign
l_int|4
comma
DECL|enumerator|NF2LNK
id|NF2LNK
op_assign
l_int|5
comma
DECL|enumerator|NF2SOCK
id|NF2SOCK
op_assign
l_int|6
comma
DECL|enumerator|NF2BAD
id|NF2BAD
op_assign
l_int|7
comma
DECL|enumerator|NF2FIFO
id|NF2FIFO
op_assign
l_int|8
)brace
suffix:semicolon
DECL|struct|nfs2_fh
r_struct
id|nfs2_fh
(brace
DECL|member|data
r_char
id|data
(braket
id|NFS2_FHSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Procedure numbers for NFSv2&n; */
DECL|macro|NFS2_VERSION
mdefine_line|#define NFS2_VERSION&t;&t;2
DECL|macro|NFSPROC_NULL
mdefine_line|#define NFSPROC_NULL&t;&t;0
DECL|macro|NFSPROC_GETATTR
mdefine_line|#define NFSPROC_GETATTR&t;&t;1
DECL|macro|NFSPROC_SETATTR
mdefine_line|#define NFSPROC_SETATTR&t;&t;2
DECL|macro|NFSPROC_ROOT
mdefine_line|#define NFSPROC_ROOT&t;&t;3
DECL|macro|NFSPROC_LOOKUP
mdefine_line|#define NFSPROC_LOOKUP&t;&t;4
DECL|macro|NFSPROC_READLINK
mdefine_line|#define NFSPROC_READLINK&t;5
DECL|macro|NFSPROC_READ
mdefine_line|#define NFSPROC_READ&t;&t;6
DECL|macro|NFSPROC_WRITECACHE
mdefine_line|#define NFSPROC_WRITECACHE&t;7
DECL|macro|NFSPROC_WRITE
mdefine_line|#define NFSPROC_WRITE&t;&t;8
DECL|macro|NFSPROC_CREATE
mdefine_line|#define NFSPROC_CREATE&t;&t;9
DECL|macro|NFSPROC_REMOVE
mdefine_line|#define NFSPROC_REMOVE&t;&t;10
DECL|macro|NFSPROC_RENAME
mdefine_line|#define NFSPROC_RENAME&t;&t;11
DECL|macro|NFSPROC_LINK
mdefine_line|#define NFSPROC_LINK&t;&t;12
DECL|macro|NFSPROC_SYMLINK
mdefine_line|#define NFSPROC_SYMLINK&t;&t;13
DECL|macro|NFSPROC_MKDIR
mdefine_line|#define NFSPROC_MKDIR&t;&t;14
DECL|macro|NFSPROC_RMDIR
mdefine_line|#define NFSPROC_RMDIR&t;&t;15
DECL|macro|NFSPROC_READDIR
mdefine_line|#define NFSPROC_READDIR&t;&t;16
DECL|macro|NFSPROC_STATFS
mdefine_line|#define NFSPROC_STATFS&t;&t;17
DECL|macro|NFS_MNT_PROGRAM
mdefine_line|#define NFS_MNT_PROGRAM&t;&t;100005
DECL|macro|NFS_MNT_VERSION
mdefine_line|#define NFS_MNT_VERSION&t;&t;1
DECL|macro|MNTPROC_NULL
mdefine_line|#define MNTPROC_NULL&t;&t;0
DECL|macro|MNTPROC_MNT
mdefine_line|#define MNTPROC_MNT&t;&t;1
DECL|macro|MNTPROC_UMNT
mdefine_line|#define MNTPROC_UMNT&t;&t;3
DECL|macro|MNTPROC_UMNTALL
mdefine_line|#define MNTPROC_UMNTALL&t;&t;4
macro_line|#endif /* _LINUX_NFS2_H */
eof
