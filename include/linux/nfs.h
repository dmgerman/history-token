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
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_PERM
id|NFSERR_PERM
op_assign
l_int|1
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_NOENT
id|NFSERR_NOENT
op_assign
l_int|2
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_IO
id|NFSERR_IO
op_assign
l_int|5
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_NXIO
id|NFSERR_NXIO
op_assign
l_int|6
comma
multiline_comment|/* v2 v3 v4 */
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
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_EXIST
id|NFSERR_EXIST
op_assign
l_int|17
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_XDEV
id|NFSERR_XDEV
op_assign
l_int|18
comma
multiline_comment|/*    v3 v4 */
DECL|enumerator|NFSERR_NODEV
id|NFSERR_NODEV
op_assign
l_int|19
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_NOTDIR
id|NFSERR_NOTDIR
op_assign
l_int|20
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_ISDIR
id|NFSERR_ISDIR
op_assign
l_int|21
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_INVAL
id|NFSERR_INVAL
op_assign
l_int|22
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_FBIG
id|NFSERR_FBIG
op_assign
l_int|27
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_NOSPC
id|NFSERR_NOSPC
op_assign
l_int|28
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_ROFS
id|NFSERR_ROFS
op_assign
l_int|30
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_MLINK
id|NFSERR_MLINK
op_assign
l_int|31
comma
multiline_comment|/*    v3 v4 */
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
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_NOTEMPTY
id|NFSERR_NOTEMPTY
op_assign
l_int|66
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_DQUOT
id|NFSERR_DQUOT
op_assign
l_int|69
comma
multiline_comment|/* v2 v3 v4 */
DECL|enumerator|NFSERR_STALE
id|NFSERR_STALE
op_assign
l_int|70
comma
multiline_comment|/* v2 v3 v4 */
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
multiline_comment|/*    v3 v4 */
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
multiline_comment|/*    v3 v4 */
DECL|enumerator|NFSERR_NOTSUPP
id|NFSERR_NOTSUPP
op_assign
l_int|10004
comma
multiline_comment|/*    v3 v4 */
DECL|enumerator|NFSERR_TOOSMALL
id|NFSERR_TOOSMALL
op_assign
l_int|10005
comma
multiline_comment|/*    v3 v4 */
DECL|enumerator|NFSERR_SERVERFAULT
id|NFSERR_SERVERFAULT
op_assign
l_int|10006
comma
multiline_comment|/*    v3 v4 */
DECL|enumerator|NFSERR_BADTYPE
id|NFSERR_BADTYPE
op_assign
l_int|10007
comma
multiline_comment|/*    v3 v4 */
DECL|enumerator|NFSERR_JUKEBOX
id|NFSERR_JUKEBOX
op_assign
l_int|10008
comma
multiline_comment|/*    v3 v4 */
DECL|enumerator|NFSERR_SAME
id|NFSERR_SAME
op_assign
l_int|10009
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_DENIED
id|NFSERR_DENIED
op_assign
l_int|10010
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_EXPIRED
id|NFSERR_EXPIRED
op_assign
l_int|10011
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_LOCKED
id|NFSERR_LOCKED
op_assign
l_int|10012
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_GRACE
id|NFSERR_GRACE
op_assign
l_int|10013
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_FHEXPIRED
id|NFSERR_FHEXPIRED
op_assign
l_int|10014
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_SHARE_DENIED
id|NFSERR_SHARE_DENIED
op_assign
l_int|10015
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_WRONGSEC
id|NFSERR_WRONGSEC
op_assign
l_int|10016
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_CLID_INUSE
id|NFSERR_CLID_INUSE
op_assign
l_int|10017
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_RESOURCE
id|NFSERR_RESOURCE
op_assign
l_int|10018
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_MOVED
id|NFSERR_MOVED
op_assign
l_int|10019
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_NOFILEHANDLE
id|NFSERR_NOFILEHANDLE
op_assign
l_int|10020
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_MINOR_VERS_MISMATCH
id|NFSERR_MINOR_VERS_MISMATCH
op_assign
l_int|10021
comma
multiline_comment|/* v4 */
DECL|enumerator|NFSERR_STALE_CLIENTID
id|NFSERR_STALE_CLIENTID
op_assign
l_int|10022
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_STALE_STATEID
id|NFSERR_STALE_STATEID
op_assign
l_int|10023
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_OLD_STATEID
id|NFSERR_OLD_STATEID
op_assign
l_int|10024
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_BAD_STATEID
id|NFSERR_BAD_STATEID
op_assign
l_int|10025
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_BAD_SEQID
id|NFSERR_BAD_SEQID
op_assign
l_int|10026
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_NOT_SAME
id|NFSERR_NOT_SAME
op_assign
l_int|10027
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_LOCK_RANGE
id|NFSERR_LOCK_RANGE
op_assign
l_int|10028
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_SYMLINK
id|NFSERR_SYMLINK
op_assign
l_int|10029
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_READDIR_NOSPC
id|NFSERR_READDIR_NOSPC
op_assign
l_int|10030
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_LEASE_MOVED
id|NFSERR_LEASE_MOVED
op_assign
l_int|10031
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_ATTRNOTSUPP
id|NFSERR_ATTRNOTSUPP
op_assign
l_int|10032
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_NO_GRACE
id|NFSERR_NO_GRACE
op_assign
l_int|10033
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_RECLAIM_BAD
id|NFSERR_RECLAIM_BAD
op_assign
l_int|10034
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_RECLAIM_CONFLICT
id|NFSERR_RECLAIM_CONFLICT
op_assign
l_int|10035
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_BAD_XDR
id|NFSERR_BAD_XDR
op_assign
l_int|10036
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_LOCKS_HELD
id|NFSERR_LOCKS_HELD
op_assign
l_int|10037
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_OPENMODE
id|NFSERR_OPENMODE
op_assign
l_int|10038
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_BADOWNER
id|NFSERR_BADOWNER
op_assign
l_int|10039
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_BADCHAR
id|NFSERR_BADCHAR
op_assign
l_int|10040
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_BADNAME
id|NFSERR_BADNAME
op_assign
l_int|10041
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_BAD_RANGE
id|NFSERR_BAD_RANGE
op_assign
l_int|10042
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_LOCK_NOTSUPP
id|NFSERR_LOCK_NOTSUPP
op_assign
l_int|10043
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_OP_ILLEGAL
id|NFSERR_OP_ILLEGAL
op_assign
l_int|10044
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_DEADLOCK
id|NFSERR_DEADLOCK
op_assign
l_int|10045
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_FILE_OPEN
id|NFSERR_FILE_OPEN
op_assign
l_int|10046
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_ADMIN_REVOKED
id|NFSERR_ADMIN_REVOKED
op_assign
l_int|10047
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_CB_PATH_DOWN
id|NFSERR_CB_PATH_DOWN
op_assign
l_int|10048
comma
multiline_comment|/*       v4 */
DECL|enumerator|NFSERR_REPLAY_ME
id|NFSERR_REPLAY_ME
op_assign
l_int|10049
multiline_comment|/*       v4 */
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
mdefine_line|#define NFS_MAXFHSIZE&t;&t;128
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
