multiline_comment|/*&n; * linux/fs/nfsd/nfsfh.c&n; *&n; * NFS server file handle treatment.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; * Portions Copyright (C) 1999 G. Allen Morris III &lt;gam3@acm.org&gt;&n; * Extensive rewrite by Neil Brown &lt;neilb@cse.unsw.edu.au&gt; Southern-Spring 1999&n; * ... and again Southern-Winter 2001 to support export_operations&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/dcache.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY&t;&t;NFSDDBG_FH
DECL|macro|NFSD_PARANOIA
mdefine_line|#define NFSD_PARANOIA 1
multiline_comment|/* #define NFSD_DEBUG_VERBOSE 1 */
DECL|variable|nfsd_nr_verified
r_static
r_int
id|nfsd_nr_verified
suffix:semicolon
DECL|variable|nfsd_nr_put
r_static
r_int
id|nfsd_nr_put
suffix:semicolon
r_extern
r_struct
id|export_operations
id|export_op_default
suffix:semicolon
DECL|macro|CALL
mdefine_line|#define&t;CALL(ops,fun) ((ops-&gt;fun)?(ops-&gt;fun):export_op_default.fun)
multiline_comment|/*&n; * our acceptability function.&n; * if NOSUBTREECHECK, accept anything&n; * if not, require that we can walk up to exp-&gt;ex_dentry&n; * doing some checks on the &squot;x&squot; bits&n; */
DECL|function|nfsd_acceptable
r_int
id|nfsd_acceptable
c_func
(paren
r_void
op_star
id|expv
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|svc_export
op_star
id|exp
op_assign
id|expv
suffix:semicolon
r_int
id|rv
suffix:semicolon
r_struct
id|dentry
op_star
id|tdentry
suffix:semicolon
r_struct
id|dentry
op_star
id|parent
suffix:semicolon
r_if
c_cond
(paren
id|exp-&gt;ex_flags
op_amp
id|NFSEXP_NOSUBTREECHECK
)paren
r_return
l_int|1
suffix:semicolon
id|tdentry
op_assign
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tdentry
op_ne
id|exp-&gt;ex_dentry
op_logical_and
op_logical_neg
id|IS_ROOT
c_func
(paren
id|tdentry
)paren
)paren
(brace
multiline_comment|/* make sure parents give x permission to user */
r_int
id|err
suffix:semicolon
id|parent
op_assign
id|dget_parent
c_func
(paren
id|tdentry
)paren
suffix:semicolon
id|err
op_assign
id|permission
c_func
(paren
id|parent-&gt;d_inode
comma
id|S_IXOTH
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|dput
c_func
(paren
id|parent
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dput
c_func
(paren
id|tdentry
)paren
suffix:semicolon
id|tdentry
op_assign
id|parent
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tdentry
op_ne
id|exp-&gt;ex_dentry
)paren
id|dprintk
c_func
(paren
l_string|&quot;nfsd_acceptable failed at %p %s&bslash;n&quot;
comma
id|tdentry
comma
id|tdentry-&gt;d_name.name
)paren
suffix:semicolon
id|rv
op_assign
(paren
id|tdentry
op_eq
id|exp-&gt;ex_dentry
)paren
suffix:semicolon
id|dput
c_func
(paren
id|tdentry
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform sanity checks on the dentry in a client&squot;s file handle.&n; *&n; * Note that the file handle dentry may need to be freed even after&n; * an error return.&n; *&n; * This is only called at the start of an nfsproc call, so fhp points to&n; * a svc_fh which is all 0 except for the over-the-wire file handle.&n; */
id|u32
DECL|function|fh_verify
id|fh_verify
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|fhp
comma
r_int
id|type
comma
r_int
id|access
)paren
(brace
r_struct
id|knfsd_fh
op_star
id|fh
op_assign
op_amp
id|fhp-&gt;fh_handle
suffix:semicolon
r_struct
id|svc_export
op_star
id|exp
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|u32
id|error
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: fh_verify(%s)&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
id|fhp
)paren
)paren
suffix:semicolon
multiline_comment|/* keep this filehandle for possible reference  when encoding attributes */
id|rqstp-&gt;rq_reffh
op_assign
id|fh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fhp-&gt;fh_dentry
)paren
(brace
id|__u32
op_star
id|datap
op_assign
l_int|NULL
suffix:semicolon
id|__u32
id|tfh
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* filehandle fragment for oldstyle filehandles */
r_int
id|fileid_type
suffix:semicolon
r_int
id|data_left
op_assign
id|fh-&gt;fh_size
op_div
l_int|4
suffix:semicolon
id|error
op_assign
id|nfserr_stale
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_client
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_vers
OG
l_int|2
)paren
id|error
op_assign
id|nfserr_badhandle
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_vers
op_eq
l_int|4
op_logical_and
id|fh-&gt;fh_size
op_eq
l_int|0
)paren
r_return
id|nfserr_nofilehandle
suffix:semicolon
r_if
c_cond
(paren
id|fh-&gt;fh_version
op_eq
l_int|1
)paren
(brace
r_int
id|len
suffix:semicolon
id|datap
op_assign
id|fh-&gt;fh_auth
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|data_left
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_switch
c_cond
(paren
id|fh-&gt;fh_auth_type
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|out
suffix:semicolon
)brace
id|len
op_assign
id|key_len
c_func
(paren
id|fh-&gt;fh_fsid_type
)paren
op_div
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|fh-&gt;fh_fsid_type
op_eq
l_int|2
)paren
(brace
multiline_comment|/* deprecated, convert to type 3 */
id|len
op_assign
l_int|3
suffix:semicolon
id|fh-&gt;fh_fsid_type
op_assign
l_int|3
suffix:semicolon
id|fh-&gt;fh_fsid
(braket
l_int|0
)braket
op_assign
id|new_encode_dev
c_func
(paren
id|MKDEV
c_func
(paren
id|ntohl
c_func
(paren
id|fh-&gt;fh_fsid
(braket
l_int|0
)braket
)paren
comma
id|ntohl
c_func
(paren
id|fh-&gt;fh_fsid
(braket
l_int|1
)braket
)paren
)paren
)paren
suffix:semicolon
id|fh-&gt;fh_fsid
(braket
l_int|1
)braket
op_assign
id|fh-&gt;fh_fsid
(braket
l_int|2
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|data_left
op_sub_assign
id|len
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|exp
op_assign
id|exp_find
c_func
(paren
id|rqstp-&gt;rq_client
comma
id|fh-&gt;fh_fsid_type
comma
id|datap
comma
op_amp
id|rqstp-&gt;rq_chandle
)paren
suffix:semicolon
id|datap
op_add_assign
id|len
suffix:semicolon
)brace
r_else
(brace
id|dev_t
id|xdev
suffix:semicolon
id|ino_t
id|xino
suffix:semicolon
r_if
c_cond
(paren
id|fh-&gt;fh_size
op_ne
id|NFS_FHSIZE
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* assume old filehandle format */
id|xdev
op_assign
id|old_decode_dev
c_func
(paren
id|fh-&gt;ofh_xdev
)paren
suffix:semicolon
id|xino
op_assign
id|u32_to_ino_t
c_func
(paren
id|fh-&gt;ofh_xino
)paren
suffix:semicolon
id|mk_fsid_v0
c_func
(paren
id|tfh
comma
id|xdev
comma
id|xino
)paren
suffix:semicolon
id|exp
op_assign
id|exp_find
c_func
(paren
id|rqstp-&gt;rq_client
comma
l_int|0
comma
id|tfh
comma
op_amp
id|rqstp-&gt;rq_chandle
)paren
suffix:semicolon
)brace
id|error
op_assign
id|nfserr_dropit
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|exp
)paren
op_logical_and
id|PTR_ERR
c_func
(paren
id|exp
)paren
op_eq
op_minus
id|EAGAIN
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|nfserr_stale
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exp
op_logical_or
id|IS_ERR
c_func
(paren
id|exp
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Check if the request originated from a secure port. */
id|error
op_assign
id|nfserr_perm
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rqstp-&gt;rq_secure
op_logical_and
id|EX_SECURE
c_func
(paren
id|exp
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: request from insecure port (%08x:%d)!&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|rqstp-&gt;rq_addr.sin_addr.s_addr
)paren
comma
id|ntohs
c_func
(paren
id|rqstp-&gt;rq_addr.sin_port
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Set user creds for this exportpoint */
id|error
op_assign
id|nfsd_setuser
c_func
(paren
id|rqstp
comma
id|exp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|error
op_assign
id|nfserrno
c_func
(paren
id|error
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Look up the dentry using the NFS file handle.&n;&t;&t; */
id|error
op_assign
id|nfserr_stale
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_vers
OG
l_int|2
)paren
id|error
op_assign
id|nfserr_badhandle
suffix:semicolon
r_if
c_cond
(paren
id|fh-&gt;fh_version
op_ne
l_int|1
)paren
(brace
id|tfh
(braket
l_int|0
)braket
op_assign
id|fh-&gt;ofh_ino
suffix:semicolon
id|tfh
(braket
l_int|1
)braket
op_assign
id|fh-&gt;ofh_generation
suffix:semicolon
id|tfh
(braket
l_int|2
)braket
op_assign
id|fh-&gt;ofh_dirino
suffix:semicolon
id|datap
op_assign
id|tfh
suffix:semicolon
id|data_left
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|fh-&gt;ofh_dirino
op_eq
l_int|0
)paren
id|fileid_type
op_assign
l_int|1
suffix:semicolon
r_else
id|fileid_type
op_assign
l_int|2
suffix:semicolon
)brace
r_else
id|fileid_type
op_assign
id|fh-&gt;fh_fileid_type
suffix:semicolon
r_if
c_cond
(paren
id|fileid_type
op_eq
l_int|0
)paren
id|dentry
op_assign
id|dget
c_func
(paren
id|exp-&gt;ex_dentry
)paren
suffix:semicolon
r_else
(brace
r_struct
id|export_operations
op_star
id|nop
op_assign
id|exp-&gt;ex_mnt-&gt;mnt_sb-&gt;s_export_op
suffix:semicolon
id|dentry
op_assign
id|CALL
c_func
(paren
id|nop
comma
id|decode_fh
)paren
(paren
id|exp-&gt;ex_mnt-&gt;mnt_sb
comma
id|datap
comma
id|data_left
comma
id|fileid_type
comma
id|nfsd_acceptable
comma
id|exp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dentry
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
(brace
r_if
c_cond
(paren
id|PTR_ERR
c_func
(paren
id|dentry
)paren
op_ne
op_minus
id|EINVAL
)paren
id|error
op_assign
id|nfserrno
c_func
(paren
id|PTR_ERR
c_func
(paren
id|dentry
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#ifdef NFSD_PARANOIA
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_mode
)paren
op_logical_and
(paren
id|dentry-&gt;d_flags
op_amp
id|DCACHE_DISCONNECTED
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfsd: find_fh_dentry returned a DISCONNECTED directory: %s/%s&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
)brace
macro_line|#endif
id|fhp-&gt;fh_dentry
op_assign
id|dentry
suffix:semicolon
id|fhp-&gt;fh_export
op_assign
id|exp
suffix:semicolon
id|nfsd_nr_verified
op_increment
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* just rechecking permissions&n;&t;&t; * (e.g. nfsproc_create calls fh_verify, then nfsd_create does as well)&n;&t;&t; */
id|dprintk
c_func
(paren
l_string|&quot;nfsd: fh_verify - just checking&bslash;n&quot;
)paren
suffix:semicolon
id|dentry
op_assign
id|fhp-&gt;fh_dentry
suffix:semicolon
id|exp
op_assign
id|fhp-&gt;fh_export
suffix:semicolon
)brace
id|cache_get
c_func
(paren
op_amp
id|exp-&gt;h
)paren
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
multiline_comment|/* Type check. The correct error return for type mismatches&n;&t; * does not seem to be generally agreed upon. SunOS seems to&n;&t; * use EISDIR if file isn&squot;t S_IFREG; a comment in the NFSv3&n;&t; * spec says this is incorrect (implementation notes for the&n;&t; * write call).&n;&t; */
multiline_comment|/* Type can be negative when creating hardlinks - not to a dir */
r_if
c_cond
(paren
id|type
OG
l_int|0
op_logical_and
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
op_ne
id|type
)paren
(brace
r_if
c_cond
(paren
id|rqstp-&gt;rq_vers
op_eq
l_int|4
op_logical_and
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
op_eq
id|S_IFLNK
)paren
id|error
op_assign
id|nfserr_symlink
suffix:semicolon
r_else
r_if
c_cond
(paren
id|type
op_eq
id|S_IFDIR
)paren
id|error
op_assign
id|nfserr_notdir
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
op_eq
id|S_IFDIR
)paren
id|error
op_assign
id|nfserr_isdir
suffix:semicolon
r_else
id|error
op_assign
id|nfserr_inval
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
OL
l_int|0
op_logical_and
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
op_eq
op_minus
id|type
)paren
(brace
r_if
c_cond
(paren
id|rqstp-&gt;rq_vers
op_eq
l_int|4
op_logical_and
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
op_eq
id|S_IFLNK
)paren
id|error
op_assign
id|nfserr_symlink
suffix:semicolon
r_else
r_if
c_cond
(paren
id|type
op_eq
op_minus
id|S_IFDIR
)paren
id|error
op_assign
id|nfserr_isdir
suffix:semicolon
r_else
id|error
op_assign
id|nfserr_notdir
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Finally, check access permissions. */
id|error
op_assign
id|nfsd_permission
c_func
(paren
id|exp
comma
id|dentry
comma
id|access
)paren
suffix:semicolon
macro_line|#ifdef NFSD_PARANOIA_EXTREME
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fh_verify: %s/%s permission failure, acc=%x, error=%d&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
id|access
comma
(paren
id|error
op_rshift
l_int|24
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|out
suffix:colon
r_if
c_cond
(paren
id|exp
op_logical_and
op_logical_neg
id|IS_ERR
c_func
(paren
id|exp
)paren
)paren
id|exp_put
c_func
(paren
id|exp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
id|nfserr_stale
)paren
id|nfsdstats.fh_stale
op_increment
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Compose a file handle for an NFS reply.&n; *&n; * Note that when first composed, the dentry may not yet have&n; * an inode.  In this case a call to fh_update should be made&n; * before the fh goes out on the wire ...&n; */
DECL|function|_fh_update
r_inline
r_int
id|_fh_update
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|svc_export
op_star
id|exp
comma
id|__u32
op_star
id|datap
comma
r_int
op_star
id|maxsize
)paren
(brace
r_struct
id|export_operations
op_star
id|nop
op_assign
id|exp-&gt;ex_mnt-&gt;mnt_sb-&gt;s_export_op
suffix:semicolon
r_if
c_cond
(paren
id|dentry
op_eq
id|exp-&gt;ex_dentry
)paren
(brace
op_star
id|maxsize
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|CALL
c_func
(paren
id|nop
comma
id|encode_fh
)paren
(paren
id|dentry
comma
id|datap
comma
id|maxsize
comma
op_logical_neg
(paren
id|exp-&gt;ex_flags
op_amp
id|NFSEXP_NOSUBTREECHECK
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * for composing old style file handles&n; */
DECL|function|_fh_update_old
r_inline
r_void
id|_fh_update_old
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|svc_export
op_star
id|exp
comma
r_struct
id|knfsd_fh
op_star
id|fh
)paren
(brace
id|fh-&gt;ofh_ino
op_assign
id|ino_t_to_u32
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|fh-&gt;ofh_generation
op_assign
id|dentry-&gt;d_inode-&gt;i_generation
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_mode
)paren
op_logical_or
(paren
id|exp-&gt;ex_flags
op_amp
id|NFSEXP_NOSUBTREECHECK
)paren
)paren
id|fh-&gt;ofh_dirino
op_assign
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|fh_compose
id|fh_compose
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
comma
r_struct
id|svc_export
op_star
id|exp
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|svc_fh
op_star
id|ref_fh
)paren
(brace
multiline_comment|/* ref_fh is a reference file handle.&n;&t; * if it is non-null, then we should compose a filehandle which is&n;&t; * of the same version, where possible.&n;&t; * Currently, that means that if ref_fh-&gt;fh_handle.fh_version == 0xca&n;&t; * Then create a 32byte filehandle using nfs_fhbase_old&n;&t; *&n;&t; */
id|u8
id|ref_fh_version
op_assign
l_int|0
suffix:semicolon
id|u8
id|ref_fh_fsid_type
op_assign
l_int|0
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|dentry
op_star
id|parent
op_assign
id|dentry-&gt;d_parent
suffix:semicolon
id|__u32
op_star
id|datap
suffix:semicolon
id|dev_t
id|ex_dev
op_assign
id|exp-&gt;ex_dentry-&gt;d_inode-&gt;i_sb-&gt;s_dev
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: fh_compose(exp %02x:%02x/%ld %s/%s, ino=%ld)&bslash;n&quot;
comma
id|MAJOR
c_func
(paren
id|ex_dev
)paren
comma
id|MINOR
c_func
(paren
id|ex_dev
)paren
comma
(paren
r_int
)paren
id|exp-&gt;ex_dentry-&gt;d_inode-&gt;i_ino
comma
id|parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
(paren
id|inode
ques
c_cond
id|inode-&gt;i_ino
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref_fh
)paren
(brace
id|ref_fh_version
op_assign
id|ref_fh-&gt;fh_handle.fh_version
suffix:semicolon
r_if
c_cond
(paren
id|ref_fh_version
op_eq
l_int|0xca
)paren
id|ref_fh_fsid_type
op_assign
l_int|0
suffix:semicolon
r_else
id|ref_fh_fsid_type
op_assign
id|ref_fh-&gt;fh_handle.fh_fsid_type
suffix:semicolon
r_if
c_cond
(paren
id|ref_fh_fsid_type
OG
l_int|3
)paren
id|ref_fh_fsid_type
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* make sure ref_fh type works for given export */
r_if
c_cond
(paren
id|ref_fh_fsid_type
op_eq
l_int|1
op_logical_and
op_logical_neg
(paren
id|exp-&gt;ex_flags
op_amp
id|NFSEXP_FSID
)paren
)paren
(brace
multiline_comment|/* if we don&squot;t have an fsid, we cannot provide one... */
id|ref_fh_fsid_type
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|old_valid_dev
c_func
(paren
id|ex_dev
)paren
op_logical_and
id|ref_fh_fsid_type
op_eq
l_int|0
)paren
(brace
multiline_comment|/* for newer device numbers, we must use a newer fsid format */
id|ref_fh_version
op_assign
l_int|1
suffix:semicolon
id|ref_fh_fsid_type
op_assign
l_int|3
suffix:semicolon
)brace
r_if
c_cond
(paren
id|old_valid_dev
c_func
(paren
id|ex_dev
)paren
op_logical_and
(paren
id|ref_fh_fsid_type
op_eq
l_int|2
op_logical_or
id|ref_fh_fsid_type
op_eq
l_int|3
)paren
)paren
multiline_comment|/* must use type1 for smaller device numbers */
id|ref_fh_fsid_type
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ref_fh
op_eq
id|fhp
)paren
id|fh_put
c_func
(paren
id|ref_fh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fhp-&gt;fh_locked
op_logical_or
id|fhp-&gt;fh_dentry
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_compose: fh %s/%s not initialized!&bslash;n&quot;
comma
id|parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fhp-&gt;fh_maxsize
OL
id|NFS_FHSIZE
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_compose: called with maxsize %d! %s/%s&bslash;n&quot;
comma
id|fhp-&gt;fh_maxsize
comma
id|parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|fhp-&gt;fh_dentry
op_assign
id|dentry
suffix:semicolon
multiline_comment|/* our internal copy */
id|fhp-&gt;fh_export
op_assign
id|exp
suffix:semicolon
id|cache_get
c_func
(paren
op_amp
id|exp-&gt;h
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref_fh_version
op_eq
l_int|0xca
)paren
(brace
multiline_comment|/* old style filehandle please */
id|memset
c_func
(paren
op_amp
id|fhp-&gt;fh_handle.fh_base
comma
l_int|0
comma
id|NFS_FHSIZE
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.fh_size
op_assign
id|NFS_FHSIZE
suffix:semicolon
id|fhp-&gt;fh_handle.ofh_dcookie
op_assign
l_int|0xfeebbaca
suffix:semicolon
id|fhp-&gt;fh_handle.ofh_dev
op_assign
id|old_encode_dev
c_func
(paren
id|ex_dev
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.ofh_xdev
op_assign
id|fhp-&gt;fh_handle.ofh_dev
suffix:semicolon
id|fhp-&gt;fh_handle.ofh_xino
op_assign
id|ino_t_to_u32
c_func
(paren
id|exp-&gt;ex_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.ofh_dirino
op_assign
id|ino_t_to_u32
c_func
(paren
id|parent_ino
c_func
(paren
id|dentry
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
id|_fh_update_old
c_func
(paren
id|dentry
comma
id|exp
comma
op_amp
id|fhp-&gt;fh_handle
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|len
suffix:semicolon
id|fhp-&gt;fh_handle.fh_version
op_assign
l_int|1
suffix:semicolon
id|fhp-&gt;fh_handle.fh_auth_type
op_assign
l_int|0
suffix:semicolon
id|datap
op_assign
id|fhp-&gt;fh_handle.fh_auth
op_plus
l_int|0
suffix:semicolon
id|fhp-&gt;fh_handle.fh_fsid_type
op_assign
id|ref_fh_fsid_type
suffix:semicolon
r_switch
c_cond
(paren
id|ref_fh_fsid_type
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * fsid_type 0:&n;&t;&t;&t;&t; * 2byte major, 2byte minor, 4byte inode&n;&t;&t;&t;&t; */
id|mk_fsid_v0
c_func
(paren
id|datap
comma
id|ex_dev
comma
id|exp-&gt;ex_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* fsid_type 1 == 4 bytes filesystem id */
id|mk_fsid_v1
c_func
(paren
id|datap
comma
id|exp-&gt;ex_fsid
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * fsid_type 2:&n;&t;&t;&t;&t; * 4byte major, 4byte minor, 4byte inode&n;&t;&t;&t;&t; */
id|mk_fsid_v2
c_func
(paren
id|datap
comma
id|ex_dev
comma
id|exp-&gt;ex_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * fsid_type 3:&n;&t;&t;&t;&t; * 4byte devicenumber, 4byte inode&n;&t;&t;&t;&t; */
id|mk_fsid_v3
c_func
(paren
id|datap
comma
id|ex_dev
comma
id|exp-&gt;ex_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|len
op_assign
id|key_len
c_func
(paren
id|ref_fh_fsid_type
)paren
suffix:semicolon
id|datap
op_add_assign
id|len
op_div
l_int|4
suffix:semicolon
id|fhp-&gt;fh_handle.fh_size
op_assign
l_int|4
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
r_int
id|size
op_assign
(paren
id|fhp-&gt;fh_maxsize
op_minus
id|len
op_minus
l_int|4
)paren
op_div
l_int|4
suffix:semicolon
id|fhp-&gt;fh_handle.fh_fileid_type
op_assign
id|_fh_update
c_func
(paren
id|dentry
comma
id|exp
comma
id|datap
comma
op_amp
id|size
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.fh_size
op_add_assign
id|size
op_star
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fhp-&gt;fh_handle.fh_fileid_type
op_eq
l_int|255
)paren
r_return
id|nfserr_opnotsupp
suffix:semicolon
)brace
id|nfsd_nr_verified
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Update file handle information after changing a dentry.&n; * This is only called by nfsd_create, nfsd_create_v3 and nfsd_proc_create&n; */
r_int
DECL|function|fh_update
id|fh_update
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
id|__u32
op_star
id|datap
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fhp-&gt;fh_dentry
)paren
r_goto
id|out_bad
suffix:semicolon
id|dentry
op_assign
id|fhp-&gt;fh_dentry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry-&gt;d_inode
)paren
r_goto
id|out_negative
suffix:semicolon
r_if
c_cond
(paren
id|fhp-&gt;fh_handle.fh_version
op_ne
l_int|1
)paren
(brace
id|_fh_update_old
c_func
(paren
id|dentry
comma
id|fhp-&gt;fh_export
comma
op_amp
id|fhp-&gt;fh_handle
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|fhp-&gt;fh_handle.fh_fileid_type
op_ne
l_int|0
)paren
r_goto
id|out_uptodate
suffix:semicolon
id|datap
op_assign
id|fhp-&gt;fh_handle.fh_auth
op_plus
id|fhp-&gt;fh_handle.fh_size
op_div
l_int|4
op_minus
l_int|1
suffix:semicolon
id|size
op_assign
(paren
id|fhp-&gt;fh_maxsize
op_minus
id|fhp-&gt;fh_handle.fh_size
)paren
op_div
l_int|4
suffix:semicolon
id|fhp-&gt;fh_handle.fh_fileid_type
op_assign
id|_fh_update
c_func
(paren
id|dentry
comma
id|fhp-&gt;fh_export
comma
id|datap
comma
op_amp
id|size
)paren
suffix:semicolon
id|fhp-&gt;fh_handle.fh_size
op_add_assign
id|size
op_star
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|fhp-&gt;fh_handle.fh_fileid_type
op_eq
l_int|255
)paren
r_return
id|nfserr_opnotsupp
suffix:semicolon
)brace
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
id|out_bad
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_update: fh not verified!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_negative
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_update: %s/%s still negative!&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_uptodate
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;fh_update: %s/%s already up-to-date!&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n; * Release a file handle.&n; */
r_void
DECL|function|fh_put
id|fh_put
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|fhp-&gt;fh_dentry
suffix:semicolon
r_struct
id|svc_export
op_star
id|exp
op_assign
id|fhp-&gt;fh_export
suffix:semicolon
r_if
c_cond
(paren
id|dentry
)paren
(brace
id|fh_unlock
c_func
(paren
id|fhp
)paren
suffix:semicolon
id|fhp-&gt;fh_dentry
op_assign
l_int|NULL
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NFSD_V3
id|fhp-&gt;fh_pre_saved
op_assign
l_int|0
suffix:semicolon
id|fhp-&gt;fh_post_saved
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|nfsd_nr_put
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|exp
)paren
(brace
id|svc_export_put
c_func
(paren
op_amp
id|exp-&gt;h
comma
op_amp
id|svc_export_cache
)paren
suffix:semicolon
id|fhp-&gt;fh_export
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Shorthand for dprintk()&squot;s&n; */
DECL|function|SVCFH_fmt
r_char
op_star
id|SVCFH_fmt
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_struct
id|knfsd_fh
op_star
id|fh
op_assign
op_amp
id|fhp-&gt;fh_handle
suffix:semicolon
r_static
r_char
id|buf
(braket
l_int|80
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d: %08x %08x %08x %08x %08x %08x&quot;
comma
id|fh-&gt;fh_size
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|0
)braket
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|1
)braket
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|2
)braket
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|3
)braket
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|4
)braket
comma
id|fh-&gt;fh_base.fh_pad
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
eof
