macro_line|#ifndef _LINUX_NFS_XDR_H
DECL|macro|_LINUX_NFS_XDR_H
mdefine_line|#define _LINUX_NFS_XDR_H
macro_line|#include &lt;linux/sunrpc/xprt.h&gt;
DECL|struct|nfs_fattr
r_struct
id|nfs_fattr
(brace
DECL|member|valid
r_int
r_int
id|valid
suffix:semicolon
multiline_comment|/* which fields are valid */
DECL|member|pre_size
id|__u64
id|pre_size
suffix:semicolon
multiline_comment|/* pre_op_attr.size&t;  */
DECL|member|pre_mtime
r_struct
id|timespec
id|pre_mtime
suffix:semicolon
multiline_comment|/* pre_op_attr.mtime&t;  */
DECL|member|pre_ctime
r_struct
id|timespec
id|pre_ctime
suffix:semicolon
multiline_comment|/* pre_op_attr.ctime&t;  */
DECL|member|type
r_enum
id|nfs_ftype
id|type
suffix:semicolon
multiline_comment|/* always use NFSv2 types */
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
DECL|member|nlink
id|__u32
id|nlink
suffix:semicolon
DECL|member|uid
id|__u32
id|uid
suffix:semicolon
DECL|member|gid
id|__u32
id|gid
suffix:semicolon
DECL|member|size
id|__u64
id|size
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|blocksize
id|__u32
id|blocksize
suffix:semicolon
DECL|member|blocks
id|__u32
id|blocks
suffix:semicolon
DECL|member|nfs2
)brace
id|nfs2
suffix:semicolon
r_struct
(brace
DECL|member|used
id|__u64
id|used
suffix:semicolon
DECL|member|nfs3
)brace
id|nfs3
suffix:semicolon
DECL|member|du
)brace
id|du
suffix:semicolon
DECL|member|rdev
id|__u32
id|rdev
suffix:semicolon
r_union
(brace
DECL|member|nfs3
id|__u64
id|nfs3
suffix:semicolon
multiline_comment|/* also nfs2 */
r_struct
(brace
DECL|member|major
id|__u64
id|major
suffix:semicolon
DECL|member|minor
id|__u64
id|minor
suffix:semicolon
DECL|member|nfs4
)brace
id|nfs4
suffix:semicolon
DECL|member|fsid_u
)brace
id|fsid_u
suffix:semicolon
DECL|member|fileid
id|__u64
id|fileid
suffix:semicolon
DECL|member|atime
r_struct
id|timespec
id|atime
suffix:semicolon
DECL|member|mtime
r_struct
id|timespec
id|mtime
suffix:semicolon
DECL|member|ctime
r_struct
id|timespec
id|ctime
suffix:semicolon
DECL|member|change_attr
id|__u64
id|change_attr
suffix:semicolon
multiline_comment|/* NFSv4 change attribute */
DECL|member|pre_change_attr
id|__u64
id|pre_change_attr
suffix:semicolon
multiline_comment|/* pre-op NFSv4 change attribute */
DECL|member|timestamp
r_int
r_int
id|timestamp
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NFS_ATTR_WCC
mdefine_line|#define NFS_ATTR_WCC&t;&t;0x0001&t;&t;/* pre-op WCC data    */
DECL|macro|NFS_ATTR_FATTR
mdefine_line|#define NFS_ATTR_FATTR&t;&t;0x0002&t;&t;/* post-op attributes */
DECL|macro|NFS_ATTR_FATTR_V3
mdefine_line|#define NFS_ATTR_FATTR_V3&t;0x0004&t;&t;/* NFSv3 attributes */
DECL|macro|NFS_ATTR_FATTR_V4
mdefine_line|#define NFS_ATTR_FATTR_V4&t;0x0008
DECL|macro|NFS_ATTR_PRE_CHANGE
mdefine_line|#define NFS_ATTR_PRE_CHANGE&t;0x0010
multiline_comment|/*&n; * Info on the file system&n; */
DECL|struct|nfs_fsinfo
r_struct
id|nfs_fsinfo
(brace
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
multiline_comment|/* Post-op attributes */
DECL|member|rtmax
id|__u32
id|rtmax
suffix:semicolon
multiline_comment|/* max.  read transfer size */
DECL|member|rtpref
id|__u32
id|rtpref
suffix:semicolon
multiline_comment|/* pref. read transfer size */
DECL|member|rtmult
id|__u32
id|rtmult
suffix:semicolon
multiline_comment|/* reads should be multiple of this */
DECL|member|wtmax
id|__u32
id|wtmax
suffix:semicolon
multiline_comment|/* max.  write transfer size */
DECL|member|wtpref
id|__u32
id|wtpref
suffix:semicolon
multiline_comment|/* pref. write transfer size */
DECL|member|wtmult
id|__u32
id|wtmult
suffix:semicolon
multiline_comment|/* writes should be multiple of this */
DECL|member|dtpref
id|__u32
id|dtpref
suffix:semicolon
multiline_comment|/* pref. readdir transfer size */
DECL|member|maxfilesize
id|__u64
id|maxfilesize
suffix:semicolon
DECL|member|lease_time
id|__u32
id|lease_time
suffix:semicolon
multiline_comment|/* in seconds */
)brace
suffix:semicolon
DECL|struct|nfs_fsstat
r_struct
id|nfs_fsstat
(brace
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
multiline_comment|/* Post-op attributes */
DECL|member|tbytes
id|__u64
id|tbytes
suffix:semicolon
multiline_comment|/* total size in bytes */
DECL|member|fbytes
id|__u64
id|fbytes
suffix:semicolon
multiline_comment|/* # of free bytes */
DECL|member|abytes
id|__u64
id|abytes
suffix:semicolon
multiline_comment|/* # of bytes available to user */
DECL|member|tfiles
id|__u64
id|tfiles
suffix:semicolon
multiline_comment|/* # of files */
DECL|member|ffiles
id|__u64
id|ffiles
suffix:semicolon
multiline_comment|/* # of free files */
DECL|member|afiles
id|__u64
id|afiles
suffix:semicolon
multiline_comment|/* # of files available to user */
)brace
suffix:semicolon
DECL|struct|nfs2_fsstat
r_struct
id|nfs2_fsstat
(brace
DECL|member|tsize
id|__u32
id|tsize
suffix:semicolon
multiline_comment|/* Server transfer size */
DECL|member|bsize
id|__u32
id|bsize
suffix:semicolon
multiline_comment|/* Filesystem block size */
DECL|member|blocks
id|__u32
id|blocks
suffix:semicolon
multiline_comment|/* No. of &quot;bsize&quot; blocks on filesystem */
DECL|member|bfree
id|__u32
id|bfree
suffix:semicolon
multiline_comment|/* No. of free &quot;bsize&quot; blocks */
DECL|member|bavail
id|__u32
id|bavail
suffix:semicolon
multiline_comment|/* No. of available &quot;bsize&quot; blocks */
)brace
suffix:semicolon
DECL|struct|nfs_pathconf
r_struct
id|nfs_pathconf
(brace
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
multiline_comment|/* Post-op attributes */
DECL|member|max_link
id|__u32
id|max_link
suffix:semicolon
multiline_comment|/* max # of hard links */
DECL|member|max_namelen
id|__u32
id|max_namelen
suffix:semicolon
multiline_comment|/* max name length */
)brace
suffix:semicolon
multiline_comment|/*&n; * Arguments to the read call.&n; */
DECL|macro|NFS_READ_MAXIOV
mdefine_line|#define NFS_READ_MAXIOV&t;&t;(9U)
macro_line|#if (NFS_READ_MAXIOV &gt; (MAX_IOVEC -2))
macro_line|#error &quot;NFS_READ_MAXIOV is too large&quot;
macro_line|#endif
DECL|struct|nfs_readargs
r_struct
id|nfs_readargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|offset
id|__u64
id|offset
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
DECL|member|pgbase
r_int
r_int
id|pgbase
suffix:semicolon
DECL|member|pages
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_readres
r_struct
id|nfs_readres
(brace
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
DECL|member|eof
r_int
id|eof
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Arguments to the write call.&n; */
DECL|macro|NFS_WRITE_MAXIOV
mdefine_line|#define NFS_WRITE_MAXIOV&t;(9U)
macro_line|#if (NFS_WRITE_MAXIOV &gt; (MAX_IOVEC -2))
macro_line|#error &quot;NFS_WRITE_MAXIOV is too large&quot;
macro_line|#endif
DECL|struct|nfs_writeargs
r_struct
id|nfs_writeargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|offset
id|__u64
id|offset
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
DECL|member|stable
r_enum
id|nfs3_stable_how
id|stable
suffix:semicolon
DECL|member|pgbase
r_int
r_int
id|pgbase
suffix:semicolon
DECL|member|pages
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_writeverf
r_struct
id|nfs_writeverf
(brace
DECL|member|committed
r_enum
id|nfs3_stable_how
id|committed
suffix:semicolon
DECL|member|verifier
id|__u32
id|verifier
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_writeres
r_struct
id|nfs_writeres
(brace
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
DECL|member|verf
r_struct
id|nfs_writeverf
op_star
id|verf
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Argument struct for decode_entry function&n; */
DECL|struct|nfs_entry
r_struct
id|nfs_entry
(brace
DECL|member|ino
id|__u64
id|ino
suffix:semicolon
DECL|member|cookie
id|__u64
id|cookie
comma
DECL|member|prev_cookie
id|prev_cookie
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|eof
r_int
id|eof
suffix:semicolon
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The following types are for NFSv2 only.&n; */
DECL|struct|nfs_sattrargs
r_struct
id|nfs_sattrargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_diropargs
r_struct
id|nfs_diropargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_createargs
r_struct
id|nfs_createargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_renameargs
r_struct
id|nfs_renameargs
(brace
DECL|member|fromfh
r_struct
id|nfs_fh
op_star
id|fromfh
suffix:semicolon
DECL|member|fromname
r_const
r_char
op_star
id|fromname
suffix:semicolon
DECL|member|fromlen
r_int
r_int
id|fromlen
suffix:semicolon
DECL|member|tofh
r_struct
id|nfs_fh
op_star
id|tofh
suffix:semicolon
DECL|member|toname
r_const
r_char
op_star
id|toname
suffix:semicolon
DECL|member|tolen
r_int
r_int
id|tolen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_linkargs
r_struct
id|nfs_linkargs
(brace
DECL|member|fromfh
r_struct
id|nfs_fh
op_star
id|fromfh
suffix:semicolon
DECL|member|tofh
r_struct
id|nfs_fh
op_star
id|tofh
suffix:semicolon
DECL|member|toname
r_const
r_char
op_star
id|toname
suffix:semicolon
DECL|member|tolen
r_int
r_int
id|tolen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_symlinkargs
r_struct
id|nfs_symlinkargs
(brace
DECL|member|fromfh
r_struct
id|nfs_fh
op_star
id|fromfh
suffix:semicolon
DECL|member|fromname
r_const
r_char
op_star
id|fromname
suffix:semicolon
DECL|member|fromlen
r_int
r_int
id|fromlen
suffix:semicolon
DECL|member|topath
r_const
r_char
op_star
id|topath
suffix:semicolon
DECL|member|tolen
r_int
r_int
id|tolen
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_readdirargs
r_struct
id|nfs_readdirargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|cookie
id|__u32
id|cookie
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|pages
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_diropok
r_struct
id|nfs_diropok
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_readlinkargs
r_struct
id|nfs_readlinkargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|pages
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_sattrargs
r_struct
id|nfs3_sattrargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
suffix:semicolon
DECL|member|guard
r_int
r_int
id|guard
suffix:semicolon
DECL|member|guardtime
r_struct
id|timespec
id|guardtime
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_diropargs
r_struct
id|nfs3_diropargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_accessargs
r_struct
id|nfs3_accessargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|access
id|__u32
id|access
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_createargs
r_struct
id|nfs3_createargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
suffix:semicolon
DECL|member|createmode
r_enum
id|nfs3_createmode
id|createmode
suffix:semicolon
DECL|member|verifier
id|__u32
id|verifier
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_mkdirargs
r_struct
id|nfs3_mkdirargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_symlinkargs
r_struct
id|nfs3_symlinkargs
(brace
DECL|member|fromfh
r_struct
id|nfs_fh
op_star
id|fromfh
suffix:semicolon
DECL|member|fromname
r_const
r_char
op_star
id|fromname
suffix:semicolon
DECL|member|fromlen
r_int
r_int
id|fromlen
suffix:semicolon
DECL|member|topath
r_const
r_char
op_star
id|topath
suffix:semicolon
DECL|member|tolen
r_int
r_int
id|tolen
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_mknodargs
r_struct
id|nfs3_mknodargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|type
r_enum
id|nfs3_ftype
id|type
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
suffix:semicolon
DECL|member|rdev
id|dev_t
id|rdev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_renameargs
r_struct
id|nfs3_renameargs
(brace
DECL|member|fromfh
r_struct
id|nfs_fh
op_star
id|fromfh
suffix:semicolon
DECL|member|fromname
r_const
r_char
op_star
id|fromname
suffix:semicolon
DECL|member|fromlen
r_int
r_int
id|fromlen
suffix:semicolon
DECL|member|tofh
r_struct
id|nfs_fh
op_star
id|tofh
suffix:semicolon
DECL|member|toname
r_const
r_char
op_star
id|toname
suffix:semicolon
DECL|member|tolen
r_int
r_int
id|tolen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_linkargs
r_struct
id|nfs3_linkargs
(brace
DECL|member|fromfh
r_struct
id|nfs_fh
op_star
id|fromfh
suffix:semicolon
DECL|member|tofh
r_struct
id|nfs_fh
op_star
id|tofh
suffix:semicolon
DECL|member|toname
r_const
r_char
op_star
id|toname
suffix:semicolon
DECL|member|tolen
r_int
r_int
id|tolen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_readdirargs
r_struct
id|nfs3_readdirargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|cookie
id|__u64
id|cookie
suffix:semicolon
DECL|member|verf
id|__u32
id|verf
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|plus
r_int
id|plus
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|pages
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_diropres
r_struct
id|nfs3_diropres
(brace
DECL|member|dir_attr
r_struct
id|nfs_fattr
op_star
id|dir_attr
suffix:semicolon
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_accessres
r_struct
id|nfs3_accessres
(brace
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
DECL|member|access
id|__u32
id|access
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_readlinkargs
r_struct
id|nfs3_readlinkargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|pages
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_renameres
r_struct
id|nfs3_renameres
(brace
DECL|member|fromattr
r_struct
id|nfs_fattr
op_star
id|fromattr
suffix:semicolon
DECL|member|toattr
r_struct
id|nfs_fattr
op_star
id|toattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_linkres
r_struct
id|nfs3_linkres
(brace
DECL|member|dir_attr
r_struct
id|nfs_fattr
op_star
id|dir_attr
suffix:semicolon
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_readdirres
r_struct
id|nfs3_readdirres
(brace
DECL|member|dir_attr
r_struct
id|nfs_fattr
op_star
id|dir_attr
suffix:semicolon
DECL|member|verf
id|__u32
op_star
id|verf
suffix:semicolon
DECL|member|plus
r_int
id|plus
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_NFS_V4
DECL|typedef|clientid4
r_typedef
id|u64
id|clientid4
suffix:semicolon
DECL|struct|nfs4_change_info
r_struct
id|nfs4_change_info
(brace
DECL|member|atomic
id|u32
id|atomic
suffix:semicolon
DECL|member|before
id|u64
id|before
suffix:semicolon
DECL|member|after
id|u64
id|after
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs4_access
r_struct
id|nfs4_access
(brace
DECL|member|ac_req_access
id|u32
id|ac_req_access
suffix:semicolon
multiline_comment|/* request */
DECL|member|ac_resp_supported
id|u32
op_star
id|ac_resp_supported
suffix:semicolon
multiline_comment|/* response */
DECL|member|ac_resp_access
id|u32
op_star
id|ac_resp_access
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfs4_close
r_struct
id|nfs4_close
(brace
DECL|member|cl_stateid
r_char
op_star
id|cl_stateid
suffix:semicolon
multiline_comment|/* request */
DECL|member|cl_seqid
id|u32
id|cl_seqid
suffix:semicolon
multiline_comment|/* request */
)brace
suffix:semicolon
DECL|struct|nfs4_commit
r_struct
id|nfs4_commit
(brace
DECL|member|co_start
id|u64
id|co_start
suffix:semicolon
multiline_comment|/* request */
DECL|member|co_len
id|u32
id|co_len
suffix:semicolon
multiline_comment|/* request */
DECL|member|co_verifier
r_struct
id|nfs_writeverf
op_star
id|co_verifier
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfs4_create
r_struct
id|nfs4_create
(brace
DECL|member|cr_ftype
id|u32
id|cr_ftype
suffix:semicolon
multiline_comment|/* request */
r_union
(brace
multiline_comment|/* request */
r_struct
(brace
DECL|member|textlen
id|u32
id|textlen
suffix:semicolon
DECL|member|text
r_const
r_char
op_star
id|text
suffix:semicolon
DECL|member|symlink
)brace
id|symlink
suffix:semicolon
multiline_comment|/* NF4LNK */
r_struct
(brace
DECL|member|specdata1
id|u32
id|specdata1
suffix:semicolon
DECL|member|specdata2
id|u32
id|specdata2
suffix:semicolon
DECL|member|device
)brace
id|device
suffix:semicolon
multiline_comment|/* NF4BLK, NF4CHR */
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|cr_namelen
id|u32
id|cr_namelen
suffix:semicolon
multiline_comment|/* request */
DECL|member|cr_name
r_const
r_char
op_star
id|cr_name
suffix:semicolon
multiline_comment|/* request */
DECL|member|cr_attrs
r_struct
id|iattr
op_star
id|cr_attrs
suffix:semicolon
multiline_comment|/* request */
DECL|member|cr_cinfo
r_struct
id|nfs4_change_info
op_star
id|cr_cinfo
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|macro|cr_textlen
mdefine_line|#define cr_textlen&t;&t;&t;u.symlink.textlen
DECL|macro|cr_text
mdefine_line|#define cr_text&t;&t;&t;&t;u.symlink.text
DECL|macro|cr_specdata1
mdefine_line|#define cr_specdata1&t;&t;&t;u.device.specdata1
DECL|macro|cr_specdata2
mdefine_line|#define cr_specdata2&t;&t;&t;u.device.specdata2
DECL|struct|nfs4_getattr
r_struct
id|nfs4_getattr
(brace
DECL|member|gt_bmval
id|u32
op_star
id|gt_bmval
suffix:semicolon
multiline_comment|/* request */
DECL|member|gt_attrs
r_struct
id|nfs_fattr
op_star
id|gt_attrs
suffix:semicolon
multiline_comment|/* response */
DECL|member|gt_fsstat
r_struct
id|nfs_fsstat
op_star
id|gt_fsstat
suffix:semicolon
multiline_comment|/* response */
DECL|member|gt_fsinfo
r_struct
id|nfs_fsinfo
op_star
id|gt_fsinfo
suffix:semicolon
multiline_comment|/* response */
DECL|member|gt_pathconf
r_struct
id|nfs_pathconf
op_star
id|gt_pathconf
suffix:semicolon
multiline_comment|/* response */
DECL|member|gt_bmres
id|u32
op_star
id|gt_bmres
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfs4_getfh
r_struct
id|nfs4_getfh
(brace
DECL|member|gf_fhandle
r_struct
id|nfs_fh
op_star
id|gf_fhandle
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfs4_link
r_struct
id|nfs4_link
(brace
DECL|member|ln_namelen
id|u32
id|ln_namelen
suffix:semicolon
multiline_comment|/* request */
DECL|member|ln_name
r_const
r_char
op_star
id|ln_name
suffix:semicolon
multiline_comment|/* request */
DECL|member|ln_cinfo
r_struct
id|nfs4_change_info
op_star
id|ln_cinfo
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfs4_lookup
r_struct
id|nfs4_lookup
(brace
DECL|member|lo_name
r_struct
id|qstr
op_star
id|lo_name
suffix:semicolon
multiline_comment|/* request */
)brace
suffix:semicolon
DECL|struct|nfs4_open
r_struct
id|nfs4_open
(brace
DECL|member|op_share_access
id|u32
id|op_share_access
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_opentype
id|u32
id|op_opentype
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_createmode
id|u32
id|op_createmode
suffix:semicolon
multiline_comment|/* request */
r_union
(brace
multiline_comment|/* request */
DECL|member|attrs
r_struct
id|iattr
op_star
id|attrs
suffix:semicolon
multiline_comment|/* UNCHECKED, GUARDED */
DECL|member|verifier
id|nfs4_verifier
id|verifier
suffix:semicolon
multiline_comment|/* EXCLUSIVE */
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|op_name
r_struct
id|qstr
op_star
id|op_name
suffix:semicolon
multiline_comment|/* request */
DECL|member|op_stateid
r_char
op_star
id|op_stateid
suffix:semicolon
multiline_comment|/* response */
DECL|member|op_cinfo
r_struct
id|nfs4_change_info
op_star
id|op_cinfo
suffix:semicolon
multiline_comment|/* response */
DECL|member|op_rflags
id|u32
op_star
id|op_rflags
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|macro|op_attrs
mdefine_line|#define op_attrs     u.attrs
DECL|macro|op_verifier
mdefine_line|#define op_verifier  u.verifier
DECL|struct|nfs4_open_confirm
r_struct
id|nfs4_open_confirm
(brace
DECL|member|oc_stateid
r_char
op_star
id|oc_stateid
suffix:semicolon
multiline_comment|/* request */
)brace
suffix:semicolon
DECL|struct|nfs4_putfh
r_struct
id|nfs4_putfh
(brace
DECL|member|pf_fhandle
r_struct
id|nfs_fh
op_star
id|pf_fhandle
suffix:semicolon
multiline_comment|/* request */
)brace
suffix:semicolon
DECL|struct|nfs4_read
r_struct
id|nfs4_read
(brace
DECL|member|rd_offset
id|u64
id|rd_offset
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_length
id|u32
id|rd_length
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_eof
id|u32
op_star
id|rd_eof
suffix:semicolon
multiline_comment|/* response */
DECL|member|rd_bytes_read
id|u32
op_star
id|rd_bytes_read
suffix:semicolon
multiline_comment|/* response */
DECL|member|rd_pages
r_struct
id|page
op_star
op_star
id|rd_pages
suffix:semicolon
multiline_comment|/* zero-copy data */
DECL|member|rd_pgbase
r_int
r_int
id|rd_pgbase
suffix:semicolon
multiline_comment|/* zero-copy data */
)brace
suffix:semicolon
DECL|struct|nfs4_readdir
r_struct
id|nfs4_readdir
(brace
DECL|member|rd_cookie
id|u64
id|rd_cookie
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_req_verifier
id|nfs4_verifier
id|rd_req_verifier
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_count
id|u32
id|rd_count
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_bmval
id|u32
id|rd_bmval
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* request */
DECL|member|rd_resp_verifier
id|nfs4_verifier
id|rd_resp_verifier
suffix:semicolon
multiline_comment|/* response */
DECL|member|rd_pages
r_struct
id|page
op_star
op_star
id|rd_pages
suffix:semicolon
multiline_comment|/* zero-copy data */
DECL|member|rd_pgbase
r_int
r_int
id|rd_pgbase
suffix:semicolon
multiline_comment|/* zero-copy data */
)brace
suffix:semicolon
DECL|struct|nfs4_readlink
r_struct
id|nfs4_readlink
(brace
DECL|member|rl_count
id|u32
id|rl_count
suffix:semicolon
multiline_comment|/* zero-copy data */
DECL|member|rl_pages
r_struct
id|page
op_star
op_star
id|rl_pages
suffix:semicolon
multiline_comment|/* zero-copy data */
)brace
suffix:semicolon
DECL|struct|nfs4_remove
r_struct
id|nfs4_remove
(brace
DECL|member|rm_namelen
id|u32
id|rm_namelen
suffix:semicolon
multiline_comment|/* request */
DECL|member|rm_name
r_const
r_char
op_star
id|rm_name
suffix:semicolon
multiline_comment|/* request */
DECL|member|rm_cinfo
r_struct
id|nfs4_change_info
op_star
id|rm_cinfo
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfs4_rename
r_struct
id|nfs4_rename
(brace
DECL|member|rn_oldnamelen
id|u32
id|rn_oldnamelen
suffix:semicolon
multiline_comment|/* request */
DECL|member|rn_oldname
r_const
r_char
op_star
id|rn_oldname
suffix:semicolon
multiline_comment|/* request */
DECL|member|rn_newnamelen
id|u32
id|rn_newnamelen
suffix:semicolon
multiline_comment|/* request */
DECL|member|rn_newname
r_const
r_char
op_star
id|rn_newname
suffix:semicolon
multiline_comment|/* request */
DECL|member|rn_src_cinfo
r_struct
id|nfs4_change_info
op_star
id|rn_src_cinfo
suffix:semicolon
multiline_comment|/* response */
DECL|member|rn_dst_cinfo
r_struct
id|nfs4_change_info
op_star
id|rn_dst_cinfo
suffix:semicolon
multiline_comment|/* response */
)brace
suffix:semicolon
DECL|struct|nfs4_setattr
r_struct
id|nfs4_setattr
(brace
DECL|member|st_stateid
r_char
op_star
id|st_stateid
suffix:semicolon
multiline_comment|/* request */
DECL|member|st_iap
r_struct
id|iattr
op_star
id|st_iap
suffix:semicolon
multiline_comment|/* request */
)brace
suffix:semicolon
DECL|struct|nfs4_setclientid
r_struct
id|nfs4_setclientid
(brace
DECL|member|sc_verifier
id|nfs4_verifier
id|sc_verifier
suffix:semicolon
multiline_comment|/* request */
DECL|member|sc_name
r_char
op_star
id|sc_name
suffix:semicolon
multiline_comment|/* request */
DECL|member|sc_prog
id|u32
id|sc_prog
suffix:semicolon
multiline_comment|/* request */
DECL|member|sc_netid
r_char
id|sc_netid
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* request */
DECL|member|sc_uaddr
r_char
id|sc_uaddr
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* request */
DECL|member|sc_cb_ident
id|u32
id|sc_cb_ident
suffix:semicolon
multiline_comment|/* request */
)brace
suffix:semicolon
DECL|struct|nfs4_write
r_struct
id|nfs4_write
(brace
DECL|member|wr_offset
id|u64
id|wr_offset
suffix:semicolon
multiline_comment|/* request */
DECL|member|wr_stable_how
id|u32
id|wr_stable_how
suffix:semicolon
multiline_comment|/* request */
DECL|member|wr_len
id|u32
id|wr_len
suffix:semicolon
multiline_comment|/* request */
DECL|member|wr_bytes_written
id|u32
op_star
id|wr_bytes_written
suffix:semicolon
multiline_comment|/* response */
DECL|member|wr_verf
r_struct
id|nfs_writeverf
op_star
id|wr_verf
suffix:semicolon
multiline_comment|/* response */
DECL|member|wr_pages
r_struct
id|page
op_star
op_star
id|wr_pages
suffix:semicolon
multiline_comment|/* zero-copy data */
DECL|member|wr_pgbase
r_int
r_int
id|wr_pgbase
suffix:semicolon
multiline_comment|/* zero-copy data */
)brace
suffix:semicolon
DECL|struct|nfs4_op
r_struct
id|nfs4_op
(brace
DECL|member|opnum
id|u32
id|opnum
suffix:semicolon
DECL|member|nfserr
id|u32
id|nfserr
suffix:semicolon
r_union
(brace
DECL|member|access
r_struct
id|nfs4_access
id|access
suffix:semicolon
DECL|member|close
r_struct
id|nfs4_close
id|close
suffix:semicolon
DECL|member|commit
r_struct
id|nfs4_commit
id|commit
suffix:semicolon
DECL|member|create
r_struct
id|nfs4_create
id|create
suffix:semicolon
DECL|member|getattr
r_struct
id|nfs4_getattr
id|getattr
suffix:semicolon
DECL|member|getfh
r_struct
id|nfs4_getfh
id|getfh
suffix:semicolon
DECL|member|link
r_struct
id|nfs4_link
id|link
suffix:semicolon
DECL|member|lookup
r_struct
id|nfs4_lookup
id|lookup
suffix:semicolon
DECL|member|open
r_struct
id|nfs4_open
id|open
suffix:semicolon
DECL|member|open_confirm
r_struct
id|nfs4_open_confirm
id|open_confirm
suffix:semicolon
DECL|member|putfh
r_struct
id|nfs4_putfh
id|putfh
suffix:semicolon
DECL|member|read
r_struct
id|nfs4_read
id|read
suffix:semicolon
DECL|member|readdir
r_struct
id|nfs4_readdir
id|readdir
suffix:semicolon
DECL|member|readlink
r_struct
id|nfs4_readlink
id|readlink
suffix:semicolon
DECL|member|remove
r_struct
id|nfs4_remove
id|remove
suffix:semicolon
DECL|member|rename
r_struct
id|nfs4_rename
id|rename
suffix:semicolon
DECL|member|setattr
r_struct
id|nfs4_setattr
id|setattr
suffix:semicolon
DECL|member|setclientid
r_struct
id|nfs4_setclientid
id|setclientid
suffix:semicolon
DECL|member|write
r_struct
id|nfs4_write
id|write
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs4_compound
r_struct
id|nfs4_compound
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* defined below */
DECL|member|server
r_struct
id|nfs_server
op_star
id|server
suffix:semicolon
multiline_comment|/* RENEW information */
DECL|member|renew_index
r_int
id|renew_index
suffix:semicolon
DECL|member|timestamp
r_int
r_int
id|timestamp
suffix:semicolon
multiline_comment|/* scratch variables for XDR encode/decode */
DECL|member|nops
r_int
id|nops
suffix:semicolon
DECL|member|p
id|u32
op_star
id|p
suffix:semicolon
DECL|member|end
id|u32
op_star
id|end
suffix:semicolon
multiline_comment|/* the individual COMPOUND operations */
DECL|member|ops
r_struct
id|nfs4_op
op_star
id|ops
suffix:semicolon
multiline_comment|/* request */
DECL|member|req_nops
r_int
id|req_nops
suffix:semicolon
DECL|member|taglen
id|u32
id|taglen
suffix:semicolon
DECL|member|tag
r_char
op_star
id|tag
suffix:semicolon
multiline_comment|/* response */
DECL|member|resp_nops
r_int
id|resp_nops
suffix:semicolon
DECL|member|toplevel_status
r_int
id|toplevel_status
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_NFS_V4 */
DECL|struct|nfs_read_data
r_struct
id|nfs_read_data
(brace
DECL|member|task
r_struct
id|rpc_task
id|task
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|cred
r_struct
id|rpc_cred
op_star
id|cred
suffix:semicolon
DECL|member|fattr
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
multiline_comment|/* fattr storage */
DECL|member|pages
r_struct
id|list_head
id|pages
suffix:semicolon
multiline_comment|/* Coalesced read requests */
DECL|member|pagevec
r_struct
id|page
op_star
id|pagevec
(braket
id|NFS_READ_MAXIOV
)braket
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|args
r_struct
id|nfs_readargs
id|args
suffix:semicolon
DECL|member|res
r_struct
id|nfs_readres
id|res
suffix:semicolon
DECL|member|v3
)brace
id|v3
suffix:semicolon
multiline_comment|/* also v2 */
macro_line|#ifdef CONFIG_NFS_V4
r_struct
(brace
DECL|member|compound
r_struct
id|nfs4_compound
id|compound
suffix:semicolon
DECL|member|ops
r_struct
id|nfs4_op
id|ops
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|res_count
id|u32
id|res_count
suffix:semicolon
DECL|member|res_eof
id|u32
id|res_eof
suffix:semicolon
DECL|member|v4
)brace
id|v4
suffix:semicolon
macro_line|#endif
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_write_data
r_struct
id|nfs_write_data
(brace
DECL|member|task
r_struct
id|rpc_task
id|task
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|cred
r_struct
id|rpc_cred
op_star
id|cred
suffix:semicolon
DECL|member|fattr
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
DECL|member|verf
r_struct
id|nfs_writeverf
id|verf
suffix:semicolon
DECL|member|pages
r_struct
id|list_head
id|pages
suffix:semicolon
multiline_comment|/* Coalesced requests we wish to flush */
DECL|member|pagevec
r_struct
id|page
op_star
id|pagevec
(braket
id|NFS_WRITE_MAXIOV
)braket
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|args
r_struct
id|nfs_writeargs
id|args
suffix:semicolon
multiline_comment|/* argument struct */
DECL|member|res
r_struct
id|nfs_writeres
id|res
suffix:semicolon
multiline_comment|/* result struct */
DECL|member|v3
)brace
id|v3
suffix:semicolon
macro_line|#ifdef CONFIG_NFS_V4
r_struct
(brace
DECL|member|compound
r_struct
id|nfs4_compound
id|compound
suffix:semicolon
DECL|member|ops
r_struct
id|nfs4_op
id|ops
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|arg_count
id|u32
id|arg_count
suffix:semicolon
DECL|member|arg_stable
id|u32
id|arg_stable
suffix:semicolon
DECL|member|res_count
id|u32
id|res_count
suffix:semicolon
DECL|member|v4
)brace
id|v4
suffix:semicolon
macro_line|#endif
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * RPC procedure vector for NFSv2/NFSv3 demuxing&n; */
DECL|struct|nfs_rpc_ops
r_struct
id|nfs_rpc_ops
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
multiline_comment|/* Protocol version */
DECL|member|getroot
r_int
(paren
op_star
id|getroot
)paren
(paren
r_struct
id|nfs_server
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|getattr
r_int
(paren
op_star
id|getattr
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|setattr
r_int
(paren
op_star
id|setattr
)paren
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|nfs_fattr
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
DECL|member|lookup
r_int
(paren
op_star
id|lookup
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|access
r_int
(paren
op_star
id|access
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|rpc_cred
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|readlink
r_int
(paren
op_star
id|readlink
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|rpc_cred
op_star
comma
r_struct
id|nfs_fattr
op_star
comma
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|page
op_star
comma
r_int
op_star
id|eofp
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|rpc_cred
op_star
comma
r_struct
id|nfs_fattr
op_star
comma
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|page
op_star
comma
r_struct
id|nfs_writeverf
op_star
id|verfp
)paren
suffix:semicolon
DECL|member|commit
r_int
(paren
op_star
id|commit
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|nfs_fattr
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|create
r_int
(paren
op_star
id|create
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|iattr
op_star
comma
r_int
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|remove
r_int
(paren
op_star
id|remove
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|unlink_setup
r_int
(paren
op_star
id|unlink_setup
)paren
(paren
r_struct
id|rpc_message
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|unlink_done
r_int
(paren
op_star
id|unlink_done
)paren
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
DECL|member|rename
r_int
(paren
op_star
id|rename
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|link
r_int
(paren
op_star
id|link
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|symlink
r_int
(paren
op_star
id|symlink
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|iattr
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|mkdir
r_int
(paren
op_star
id|mkdir
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|iattr
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|rmdir
r_int
(paren
op_star
id|rmdir
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|readdir
r_int
(paren
op_star
id|readdir
)paren
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|rpc_cred
op_star
comma
id|u64
comma
r_struct
id|page
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|mknod
r_int
(paren
op_star
id|mknod
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|iattr
op_star
comma
id|dev_t
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|statfs
r_int
(paren
op_star
id|statfs
)paren
(paren
r_struct
id|nfs_server
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fsstat
op_star
)paren
suffix:semicolon
DECL|member|fsinfo
r_int
(paren
op_star
id|fsinfo
)paren
(paren
r_struct
id|nfs_server
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fsinfo
op_star
)paren
suffix:semicolon
DECL|member|pathconf
r_int
(paren
op_star
id|pathconf
)paren
(paren
r_struct
id|nfs_server
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_pathconf
op_star
)paren
suffix:semicolon
DECL|member|decode_dirent
id|u32
op_star
(paren
op_star
id|decode_dirent
)paren
(paren
id|u32
op_star
comma
r_struct
id|nfs_entry
op_star
comma
r_int
id|plus
)paren
suffix:semicolon
DECL|member|read_setup
r_void
(paren
op_star
id|read_setup
)paren
(paren
r_struct
id|nfs_read_data
op_star
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|member|write_setup
r_void
(paren
op_star
id|write_setup
)paren
(paren
r_struct
id|nfs_write_data
op_star
comma
r_int
r_int
id|count
comma
r_int
id|how
)paren
suffix:semicolon
DECL|member|commit_setup
r_void
(paren
op_star
id|commit_setup
)paren
(paren
r_struct
id|nfs_write_data
op_star
comma
id|u64
id|start
comma
id|u32
id|len
comma
r_int
id|how
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * &t;NFS_CALL(getattr, inode, (fattr));&n; * into&n; *&t;NFS_PROTO(inode)-&gt;getattr(fattr);&n; */
DECL|macro|NFS_CALL
mdefine_line|#define NFS_CALL(op, inode, args)&t;NFS_PROTO(inode)-&gt;op args
multiline_comment|/*&n; * Function vectors etc. for the NFS client&n; */
r_extern
r_struct
id|nfs_rpc_ops
id|nfs_v2_clientops
suffix:semicolon
r_extern
r_struct
id|nfs_rpc_ops
id|nfs_v3_clientops
suffix:semicolon
r_extern
r_struct
id|nfs_rpc_ops
id|nfs_v4_clientops
suffix:semicolon
r_extern
r_struct
id|rpc_version
id|nfs_version2
suffix:semicolon
r_extern
r_struct
id|rpc_version
id|nfs_version3
suffix:semicolon
r_extern
r_struct
id|rpc_version
id|nfs_version4
suffix:semicolon
r_extern
r_struct
id|rpc_program
id|nfs_program
suffix:semicolon
r_extern
r_struct
id|rpc_stat
id|nfs_rpcstat
suffix:semicolon
macro_line|#endif
eof
