multiline_comment|/*&n; * NFS protocol definitions&n; *&n; * This file contains constants mostly for Version 2 of the protocol,&n; * but also has a couple of NFSv3 bits in (notably the error codes).&n; */
macro_line|#ifndef _LINUX_NFS_H
DECL|macro|_LINUX_NFS_H
mdefine_line|#define _LINUX_NFS_H
macro_line|#include &lt;linux/sunrpc/msg_prot.h&gt;
DECL|macro|NFS_PROGRAM
mdefine_line|#define NFS_PROGRAM&t;100003
DECL|macro|NFS_PORT
mdefine_line|#define NFS_PORT&t;2049
DECL|macro|NFS_MAXDATA
mdefine_line|#define NFS_MAXDATA&t;8192
DECL|macro|NFS_MAXPATHLEN
mdefine_line|#define NFS_MAXPATHLEN&t;1024
DECL|macro|NFS_MAXNAMLEN
mdefine_line|#define NFS_MAXNAMLEN&t;255
DECL|macro|NFS_MAXGROUPS
mdefine_line|#define NFS_MAXGROUPS&t;16
DECL|macro|NFS_FHSIZE
mdefine_line|#define NFS_FHSIZE&t;32
DECL|macro|NFS_COOKIESIZE
mdefine_line|#define NFS_COOKIESIZE&t;4
DECL|macro|NFS_FIFO_DEV
mdefine_line|#define NFS_FIFO_DEV&t;(-1)
DECL|macro|NFSMODE_FMT
mdefine_line|#define NFSMODE_FMT&t;0170000
DECL|macro|NFSMODE_DIR
mdefine_line|#define NFSMODE_DIR&t;0040000
DECL|macro|NFSMODE_CHR
mdefine_line|#define NFSMODE_CHR&t;0020000
DECL|macro|NFSMODE_BLK
mdefine_line|#define NFSMODE_BLK&t;0060000
DECL|macro|NFSMODE_REG
mdefine_line|#define NFSMODE_REG&t;0100000
DECL|macro|NFSMODE_LNK
mdefine_line|#define NFSMODE_LNK&t;0120000
DECL|macro|NFSMODE_SOCK
mdefine_line|#define NFSMODE_SOCK&t;0140000
DECL|macro|NFSMODE_FIFO
mdefine_line|#define NFSMODE_FIFO&t;0010000
DECL|macro|NFS_MNT_PROGRAM
mdefine_line|#define NFS_MNT_PROGRAM&t;100005
DECL|macro|NFS_MNT_PORT
mdefine_line|#define NFS_MNT_PORT&t;627
multiline_comment|/*&n; * NFS stats. The good thing with these values is that NFSv3 errors are&n; * a superset of NFSv2 errors (with the exception of NFSERR_WFLUSH which&n; * no-one uses anyway), so we can happily mix code as long as we make sure&n; * no NFSv3 errors are returned to NFSv2 clients.&n; * Error codes that have a `--&squot; in the v2 column are not part of the&n; * standard, but seem to be widely used nevertheless.&n; */
DECL|enum|nfs_stat
r_enum
id|nfs_stat
(brace
DECL|enumerator|NFS_OK
id|NFS_OK
op_assign
l_int|0
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_PERM
id|NFSERR_PERM
op_assign
l_int|1
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_NOENT
id|NFSERR_NOENT
op_assign
l_int|2
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_IO
id|NFSERR_IO
op_assign
l_int|5
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_NXIO
id|NFSERR_NXIO
op_assign
l_int|6
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_EAGAIN
id|NFSERR_EAGAIN
op_assign
l_int|11
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_ACCES
id|NFSERR_ACCES
op_assign
l_int|13
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_EXIST
id|NFSERR_EXIST
op_assign
l_int|17
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_XDEV
id|NFSERR_XDEV
op_assign
l_int|18
comma
multiline_comment|/*    v3 */
DECL|enumerator|NFSERR_NODEV
id|NFSERR_NODEV
op_assign
l_int|19
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_NOTDIR
id|NFSERR_NOTDIR
op_assign
l_int|20
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_ISDIR
id|NFSERR_ISDIR
op_assign
l_int|21
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_INVAL
id|NFSERR_INVAL
op_assign
l_int|22
comma
multiline_comment|/* v2 v3 that Sun forgot */
DECL|enumerator|NFSERR_FBIG
id|NFSERR_FBIG
op_assign
l_int|27
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_NOSPC
id|NFSERR_NOSPC
op_assign
l_int|28
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_ROFS
id|NFSERR_ROFS
op_assign
l_int|30
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_MLINK
id|NFSERR_MLINK
op_assign
l_int|31
comma
multiline_comment|/*    v3 */
DECL|enumerator|NFSERR_OPNOTSUPP
id|NFSERR_OPNOTSUPP
op_assign
l_int|45
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_NAMETOOLONG
id|NFSERR_NAMETOOLONG
op_assign
l_int|63
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_NOTEMPTY
id|NFSERR_NOTEMPTY
op_assign
l_int|66
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_DQUOT
id|NFSERR_DQUOT
op_assign
l_int|69
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_STALE
id|NFSERR_STALE
op_assign
l_int|70
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_REMOTE
id|NFSERR_REMOTE
op_assign
l_int|71
comma
multiline_comment|/* v2 v3 */
DECL|enumerator|NFSERR_WFLUSH
id|NFSERR_WFLUSH
op_assign
l_int|99
comma
multiline_comment|/* v2    */
DECL|enumerator|NFSERR_BADHANDLE
id|NFSERR_BADHANDLE
op_assign
l_int|10001
comma
multiline_comment|/*    v3 */
DECL|enumerator|NFSERR_NOT_SYNC
id|NFSERR_NOT_SYNC
op_assign
l_int|10002
comma
multiline_comment|/*    v3 */
DECL|enumerator|NFSERR_BAD_COOKIE
id|NFSERR_BAD_COOKIE
op_assign
l_int|10003
comma
multiline_comment|/*    v3 */
DECL|enumerator|NFSERR_NOTSUPP
id|NFSERR_NOTSUPP
op_assign
l_int|10004
comma
multiline_comment|/*    v3 */
DECL|enumerator|NFSERR_TOOSMALL
id|NFSERR_TOOSMALL
op_assign
l_int|10005
comma
multiline_comment|/*    v3 */
DECL|enumerator|NFSERR_SERVERFAULT
id|NFSERR_SERVERFAULT
op_assign
l_int|10006
comma
multiline_comment|/*    v3 */
DECL|enumerator|NFSERR_BADTYPE
id|NFSERR_BADTYPE
op_assign
l_int|10007
comma
multiline_comment|/*    v3 */
DECL|enumerator|NFSERR_JUKEBOX
id|NFSERR_JUKEBOX
op_assign
l_int|10008
multiline_comment|/*    v3 */
)brace
suffix:semicolon
multiline_comment|/* NFSv2 file types - beware, these are not the same in NFSv3 */
DECL|enum|nfs_ftype
r_enum
id|nfs_ftype
(brace
DECL|enumerator|NFNON
id|NFNON
op_assign
l_int|0
comma
DECL|enumerator|NFREG
id|NFREG
op_assign
l_int|1
comma
DECL|enumerator|NFDIR
id|NFDIR
op_assign
l_int|2
comma
DECL|enumerator|NFBLK
id|NFBLK
op_assign
l_int|3
comma
DECL|enumerator|NFCHR
id|NFCHR
op_assign
l_int|4
comma
DECL|enumerator|NFLNK
id|NFLNK
op_assign
l_int|5
comma
DECL|enumerator|NFSOCK
id|NFSOCK
op_assign
l_int|6
comma
DECL|enumerator|NFBAD
id|NFBAD
op_assign
l_int|7
comma
DECL|enumerator|NFFIFO
id|NFFIFO
op_assign
l_int|8
)brace
suffix:semicolon
macro_line|#if defined(__KERNEL__)
multiline_comment|/*&n; * This is the kernel NFS client file handle representation&n; */
DECL|macro|NFS_MAXFHSIZE
mdefine_line|#define NFS_MAXFHSIZE&t;&t;64
DECL|struct|nfs_fh
r_struct
id|nfs_fh
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
id|NFS_MAXFHSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is really a general kernel constant, but since nothing like&n; * this is defined in the kernel headers, I have to do it here.&n; */
DECL|macro|NFS_OFFSET_MAX
mdefine_line|#define NFS_OFFSET_MAX&t;&t;((__s64)((~(__u64)0) &gt;&gt; 1))
DECL|enum|nfs3_stable_how
r_enum
id|nfs3_stable_how
(brace
DECL|enumerator|NFS_UNSTABLE
id|NFS_UNSTABLE
op_assign
l_int|0
comma
DECL|enumerator|NFS_DATA_SYNC
id|NFS_DATA_SYNC
op_assign
l_int|1
comma
DECL|enumerator|NFS_FILE_SYNC
id|NFS_FILE_SYNC
op_assign
l_int|2
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_NFS_H */
eof
