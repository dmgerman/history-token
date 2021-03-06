multiline_comment|/*&n; * nfsproc2.c&t;Process version 2 NFS requests.&n; * linux/fs/nfsd/nfs2proc.c&n; * &n; * Process version 2 NFS requests.&n; *&n; * Copyright (C) 1995-1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/cache.h&gt;
macro_line|#include &lt;linux/nfsd/xdr.h&gt;
DECL|typedef|svc_rqst
r_typedef
r_struct
id|svc_rqst
id|svc_rqst
suffix:semicolon
DECL|typedef|svc_buf
r_typedef
r_struct
id|svc_buf
id|svc_buf
suffix:semicolon
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY&t;&t;NFSDDBG_PROC
r_static
r_int
DECL|function|nfsd_proc_null
id|nfsd_proc_null
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_void
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_return
id|nfs_ok
suffix:semicolon
)brace
multiline_comment|/*&n; * Get a file&squot;s attributes&n; * N.B. After this call resp-&gt;fh needs an fh_put&n; */
r_static
r_int
DECL|function|nfsd_proc_getattr
id|nfsd_proc_getattr
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_fhandle
op_star
id|argp
comma
r_struct
id|nfsd_attrstat
op_star
id|resp
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;nfsd: GETATTR  %s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
r_return
id|fh_verify
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
l_int|0
comma
id|MAY_NOP
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set a file&squot;s attributes&n; * N.B. After this call resp-&gt;fh needs an fh_put&n; */
r_static
r_int
DECL|function|nfsd_proc_setattr
id|nfsd_proc_setattr
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_sattrargs
op_star
id|argp
comma
r_struct
id|nfsd_attrstat
op_star
id|resp
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;nfsd: SETATTR  %s, valid=%x, size=%ld&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;attrs.ia_valid
comma
(paren
r_int
)paren
id|argp-&gt;attrs.ia_size
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
r_return
id|nfsd_setattr
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;attrs
comma
l_int|0
comma
(paren
id|time_t
)paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Look up a path name component&n; * Note: the dentry in the resp-&gt;fh may be negative if the file&n; * doesn&squot;t exist yet.&n; * N.B. After this call resp-&gt;fh needs an fh_put&n; */
r_static
r_int
DECL|function|nfsd_proc_lookup
id|nfsd_proc_lookup
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_diropargs
op_star
id|argp
comma
r_struct
id|nfsd_diropres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: LOOKUP   %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|fh_init
c_func
(paren
op_amp
id|resp-&gt;fh
comma
id|NFS_FHSIZE
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_lookup
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
id|argp-&gt;name
comma
id|argp-&gt;len
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a symlink.&n; */
r_static
r_int
DECL|function|nfsd_proc_readlink
id|nfsd_proc_readlink
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_readlinkargs
op_star
id|argp
comma
r_struct
id|nfsd_readlinkres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: READLINK %s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
multiline_comment|/* Read the symlink. */
id|resp-&gt;len
op_assign
id|NFS_MAXPATHLEN
suffix:semicolon
id|nfserr
op_assign
id|nfsd_readlink
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
id|argp-&gt;buffer
comma
op_amp
id|resp-&gt;len
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a portion of a file.&n; * N.B. After this call resp-&gt;fh needs an fh_put&n; */
r_static
r_int
DECL|function|nfsd_proc_read
id|nfsd_proc_read
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_readargs
op_star
id|argp
comma
r_struct
id|nfsd_readres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: READ    %s %d bytes at %d&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;count
comma
id|argp-&gt;offset
)paren
suffix:semicolon
multiline_comment|/* Obtain buffer pointer for payload. 19 is 1 word for&n;&t; * status, 17 words for fattr, and 1 word for the byte count.&n;&t; */
r_if
c_cond
(paren
id|NFSSVC_MAXBLKSIZE
OL
id|argp-&gt;count
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;oversized read request from %u.%u.%u.%u:%d (%d bytes)&bslash;n&quot;
comma
id|NIPQUAD
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
comma
id|argp-&gt;count
)paren
suffix:semicolon
id|argp-&gt;count
op_assign
id|NFSSVC_MAXBLKSIZE
suffix:semicolon
)brace
id|svc_reserve
c_func
(paren
id|rqstp
comma
(paren
l_int|19
op_lshift
l_int|2
)paren
op_plus
id|argp-&gt;count
op_plus
l_int|4
)paren
suffix:semicolon
id|resp-&gt;count
op_assign
id|argp-&gt;count
suffix:semicolon
id|nfserr
op_assign
id|nfsd_read
c_func
(paren
id|rqstp
comma
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
comma
l_int|NULL
comma
id|argp-&gt;offset
comma
id|argp-&gt;vec
comma
id|argp-&gt;vlen
comma
op_amp
id|resp-&gt;count
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
multiline_comment|/*&n; * Write data to a file&n; * N.B. After this call resp-&gt;fh needs an fh_put&n; */
r_static
r_int
DECL|function|nfsd_proc_write
id|nfsd_proc_write
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_writeargs
op_star
id|argp
comma
r_struct
id|nfsd_attrstat
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
r_int
id|stable
op_assign
l_int|1
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: WRITE    %s %d bytes at %d&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;offset
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_write
c_func
(paren
id|rqstp
comma
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
comma
l_int|NULL
comma
id|argp-&gt;offset
comma
id|argp-&gt;vec
comma
id|argp-&gt;vlen
comma
id|argp-&gt;len
comma
op_amp
id|stable
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
multiline_comment|/*&n; * CREATE processing is complicated. The keyword here is `overloaded.&squot;&n; * The parent directory is kept locked between the check for existence&n; * and the actual create() call in compliance with VFS protocols.&n; * N.B. After this call _both_ argp-&gt;fh and resp-&gt;fh need an fh_put&n; */
r_static
r_int
DECL|function|nfsd_proc_create
id|nfsd_proc_create
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_createargs
op_star
id|argp
comma
r_struct
id|nfsd_diropres
op_star
id|resp
)paren
(brace
id|svc_fh
op_star
id|dirfhp
op_assign
op_amp
id|argp-&gt;fh
suffix:semicolon
id|svc_fh
op_star
id|newfhp
op_assign
op_amp
id|resp-&gt;fh
suffix:semicolon
r_struct
id|iattr
op_star
id|attr
op_assign
op_amp
id|argp-&gt;attrs
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|dchild
suffix:semicolon
r_int
id|nfserr
comma
id|type
comma
id|mode
suffix:semicolon
id|dev_t
id|rdev
op_assign
l_int|0
comma
id|wanted
op_assign
id|new_decode_dev
c_func
(paren
id|attr-&gt;ia_size
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: CREATE   %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
id|dirfhp
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;name
)paren
suffix:semicolon
multiline_comment|/* First verify the parent file handle */
id|nfserr
op_assign
id|fh_verify
c_func
(paren
id|rqstp
comma
id|dirfhp
comma
id|S_IFDIR
comma
id|MAY_EXEC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfserr
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* must fh_put dirfhp even on error */
multiline_comment|/* Check for MAY_WRITE in nfsd_create if necessary */
id|nfserr
op_assign
id|nfserr_acces
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|argp-&gt;len
)paren
r_goto
id|done
suffix:semicolon
id|nfserr
op_assign
id|nfserr_exist
suffix:semicolon
r_if
c_cond
(paren
id|isdotent
c_func
(paren
id|argp-&gt;name
comma
id|argp-&gt;len
)paren
)paren
r_goto
id|done
suffix:semicolon
id|fh_lock
c_func
(paren
id|dirfhp
)paren
suffix:semicolon
id|dchild
op_assign
id|lookup_one_len
c_func
(paren
id|argp-&gt;name
comma
id|dirfhp-&gt;fh_dentry
comma
id|argp-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dchild
)paren
)paren
(brace
id|nfserr
op_assign
id|nfserrno
c_func
(paren
id|PTR_ERR
c_func
(paren
id|dchild
)paren
)paren
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
id|fh_init
c_func
(paren
id|newfhp
comma
id|NFS_FHSIZE
)paren
suffix:semicolon
id|nfserr
op_assign
id|fh_compose
c_func
(paren
id|newfhp
comma
id|dirfhp-&gt;fh_export
comma
id|dchild
comma
id|dirfhp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nfserr
op_logical_and
op_logical_neg
id|dchild-&gt;d_inode
)paren
id|nfserr
op_assign
id|nfserr_noent
suffix:semicolon
id|dput
c_func
(paren
id|dchild
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfserr
)paren
(brace
r_if
c_cond
(paren
id|nfserr
op_ne
id|nfserr_noent
)paren
r_goto
id|out_unlock
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the new file handle wasn&squot;t verified, we can&squot;t tell&n;&t;&t; * whether the file exists or not. Time to bail ...&n;&t;&t; */
id|nfserr
op_assign
id|nfserr_acces
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newfhp-&gt;fh_dentry
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd_proc_create: file handle not verified&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
)brace
id|inode
op_assign
id|newfhp-&gt;fh_dentry-&gt;d_inode
suffix:semicolon
multiline_comment|/* Unfudge the mode bits */
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
(brace
id|type
op_assign
id|attr-&gt;ia_mode
op_amp
id|S_IFMT
suffix:semicolon
id|mode
op_assign
id|attr-&gt;ia_mode
op_amp
op_complement
id|S_IFMT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|type
)paren
(brace
multiline_comment|/* no type, so if target exists, assume same as that,&n;&t;&t;&t; * else assume a file */
r_if
c_cond
(paren
id|inode
)paren
(brace
id|type
op_assign
id|inode-&gt;i_mode
op_amp
id|S_IFMT
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|S_IFCHR
suffix:colon
r_case
id|S_IFBLK
suffix:colon
multiline_comment|/* reserve rdev for later checking */
id|rdev
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
id|attr-&gt;ia_valid
op_or_assign
id|ATTR_SIZE
suffix:semicolon
multiline_comment|/* FALLTHROUGH */
r_case
id|S_IFIFO
suffix:colon
multiline_comment|/* this is probably a permission check..&n;&t;&t;&t;&t;&t; * at least IRIX implements perm checking on&n;&t;&t;&t;&t;&t; *   echo thing &gt; device-special-file-or-pipe&n;&t;&t;&t;&t;&t; * by doing a CREATE with type==0&n;&t;&t;&t;&t;&t; */
id|nfserr
op_assign
id|nfsd_permission
c_func
(paren
id|newfhp-&gt;fh_export
comma
id|newfhp-&gt;fh_dentry
comma
id|MAY_WRITE
op_or
id|MAY_LOCAL_ACCESS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfserr
op_logical_and
id|nfserr
op_ne
id|nfserr_rofs
)paren
r_goto
id|out_unlock
suffix:semicolon
)brace
)brace
r_else
id|type
op_assign
id|S_IFREG
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|inode
)paren
(brace
id|type
op_assign
id|inode-&gt;i_mode
op_amp
id|S_IFMT
suffix:semicolon
id|mode
op_assign
id|inode-&gt;i_mode
op_amp
op_complement
id|S_IFMT
suffix:semicolon
)brace
r_else
(brace
id|type
op_assign
id|S_IFREG
suffix:semicolon
id|mode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ??? */
)brace
id|attr-&gt;ia_valid
op_or_assign
id|ATTR_MODE
suffix:semicolon
id|attr-&gt;ia_mode
op_assign
id|mode
suffix:semicolon
multiline_comment|/* Special treatment for non-regular files according to the&n;&t; * gospel of sun micro&n;&t; */
r_if
c_cond
(paren
id|type
op_ne
id|S_IFREG
)paren
(brace
r_int
id|is_borc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|S_IFBLK
op_logical_and
id|type
op_ne
id|S_IFCHR
)paren
(brace
id|rdev
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|S_IFCHR
op_logical_and
op_logical_neg
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_SIZE
)paren
)paren
(brace
multiline_comment|/* If you think you&squot;ve seen the worst, grok this. */
id|type
op_assign
id|S_IFIFO
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Okay, char or block special */
id|is_borc
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rdev
)paren
id|rdev
op_assign
id|wanted
suffix:semicolon
)brace
multiline_comment|/* we&squot;ve used the SIZE information, so discard it */
id|attr-&gt;ia_valid
op_and_assign
op_complement
id|ATTR_SIZE
suffix:semicolon
multiline_comment|/* Make sure the type and device matches */
id|nfserr
op_assign
id|nfserr_exist
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_logical_and
id|type
op_ne
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
)brace
id|nfserr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
multiline_comment|/* File doesn&squot;t exist. Create it and set attrs */
id|nfserr
op_assign
id|nfsd_create
c_func
(paren
id|rqstp
comma
id|dirfhp
comma
id|argp-&gt;name
comma
id|argp-&gt;len
comma
id|attr
comma
id|type
comma
id|rdev
comma
id|newfhp
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|S_IFREG
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;nfsd:   existing %s, valid=%x, size=%ld&bslash;n&quot;
comma
id|argp-&gt;name
comma
id|attr-&gt;ia_valid
comma
(paren
r_int
)paren
id|attr-&gt;ia_size
)paren
suffix:semicolon
multiline_comment|/* File already exists. We ignore all attributes except&n;&t;&t; * size, so that creat() behaves exactly like&n;&t;&t; * open(..., O_CREAT|O_TRUNC|O_WRONLY).&n;&t;&t; */
id|attr-&gt;ia_valid
op_and_assign
id|ATTR_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
)paren
id|nfserr
op_assign
id|nfsd_setattr
c_func
(paren
id|rqstp
comma
id|newfhp
comma
id|attr
comma
l_int|0
comma
(paren
id|time_t
)paren
l_int|0
)paren
suffix:semicolon
)brace
id|out_unlock
suffix:colon
multiline_comment|/* We don&squot;t really need to unlock, as fh_put does it. */
id|fh_unlock
c_func
(paren
id|dirfhp
)paren
suffix:semicolon
id|done
suffix:colon
id|fh_put
c_func
(paren
id|dirfhp
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd_proc_remove
id|nfsd_proc_remove
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_diropargs
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: REMOVE   %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;name
)paren
suffix:semicolon
multiline_comment|/* Unlink. -SIFDIR means file must not be a directory */
id|nfserr
op_assign
id|nfsd_unlink
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
op_minus
id|S_IFDIR
comma
id|argp-&gt;name
comma
id|argp-&gt;len
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd_proc_rename
id|nfsd_proc_rename
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_renameargs
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: RENAME   %s %.*s -&gt; &bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
comma
id|argp-&gt;flen
comma
id|argp-&gt;fname
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd:        -&gt;  %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
comma
id|argp-&gt;tlen
comma
id|argp-&gt;tname
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_rename
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;ffh
comma
id|argp-&gt;fname
comma
id|argp-&gt;flen
comma
op_amp
id|argp-&gt;tfh
comma
id|argp-&gt;tname
comma
id|argp-&gt;tlen
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd_proc_link
id|nfsd_proc_link
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_linkargs
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: LINK     %s -&gt;&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd:    %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
comma
id|argp-&gt;tlen
comma
id|argp-&gt;tname
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_link
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;tfh
comma
id|argp-&gt;tname
comma
id|argp-&gt;tlen
comma
op_amp
id|argp-&gt;ffh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd_proc_symlink
id|nfsd_proc_symlink
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_symlinkargs
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_struct
id|svc_fh
id|newfh
suffix:semicolon
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: SYMLINK  %s %.*s -&gt; %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
comma
id|argp-&gt;flen
comma
id|argp-&gt;fname
comma
id|argp-&gt;tlen
comma
id|argp-&gt;tname
)paren
suffix:semicolon
id|fh_init
c_func
(paren
op_amp
id|newfh
comma
id|NFS_FHSIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create the link, look up new file and set attrs.&n;&t; */
id|nfserr
op_assign
id|nfsd_symlink
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;ffh
comma
id|argp-&gt;fname
comma
id|argp-&gt;flen
comma
id|argp-&gt;tname
comma
id|argp-&gt;tlen
comma
op_amp
id|newfh
comma
op_amp
id|argp-&gt;attrs
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|newfh
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
multiline_comment|/*&n; * Make directory. This operation is not idempotent.&n; * N.B. After this call resp-&gt;fh needs an fh_put&n; */
r_static
r_int
DECL|function|nfsd_proc_mkdir
id|nfsd_proc_mkdir
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_createargs
op_star
id|argp
comma
r_struct
id|nfsd_diropres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: MKDIR    %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resp-&gt;fh.fh_dentry
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd_proc_mkdir: response already verified??&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|argp-&gt;attrs.ia_valid
op_and_assign
op_complement
id|ATTR_SIZE
suffix:semicolon
id|fh_init
c_func
(paren
op_amp
id|resp-&gt;fh
comma
id|NFS_FHSIZE
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_create
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
id|argp-&gt;name
comma
id|argp-&gt;len
comma
op_amp
id|argp-&gt;attrs
comma
id|S_IFDIR
comma
l_int|0
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove a directory&n; */
r_static
r_int
DECL|function|nfsd_proc_rmdir
id|nfsd_proc_rmdir
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_diropargs
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: RMDIR    %s %.*s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_unlink
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
id|S_IFDIR
comma
id|argp-&gt;name
comma
id|argp-&gt;len
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a portion of a directory.&n; */
r_static
r_int
DECL|function|nfsd_proc_readdir
id|nfsd_proc_readdir
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_readdirargs
op_star
id|argp
comma
r_struct
id|nfsd_readdirres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
comma
id|count
suffix:semicolon
id|loff_t
id|offset
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: READDIR  %s %d bytes at %d&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;count
comma
id|argp-&gt;cookie
)paren
suffix:semicolon
multiline_comment|/* Shrink to the client read size */
id|count
op_assign
(paren
id|argp-&gt;count
op_rshift
l_int|2
)paren
op_minus
l_int|2
suffix:semicolon
multiline_comment|/* Make sure we&squot;ve room for the NULL ptr &amp; eof flag */
id|count
op_sub_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
id|count
op_assign
l_int|0
suffix:semicolon
id|resp-&gt;buffer
op_assign
id|argp-&gt;buffer
suffix:semicolon
id|resp-&gt;offset
op_assign
l_int|NULL
suffix:semicolon
id|resp-&gt;buflen
op_assign
id|count
suffix:semicolon
id|resp-&gt;common.err
op_assign
id|nfs_ok
suffix:semicolon
multiline_comment|/* Read directory and encode entries on the fly */
id|offset
op_assign
id|argp-&gt;cookie
suffix:semicolon
id|nfserr
op_assign
id|nfsd_readdir
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
op_amp
id|offset
comma
op_amp
id|resp-&gt;common
comma
id|nfssvc_encode_entry
)paren
suffix:semicolon
id|resp-&gt;count
op_assign
id|resp-&gt;buffer
op_minus
id|argp-&gt;buffer
suffix:semicolon
r_if
c_cond
(paren
id|resp-&gt;offset
)paren
op_star
id|resp-&gt;offset
op_assign
id|htonl
c_func
(paren
id|offset
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
multiline_comment|/*&n; * Get file system info&n; */
r_static
r_int
DECL|function|nfsd_proc_statfs
id|nfsd_proc_statfs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_fhandle
op_star
id|argp
comma
r_struct
id|nfsd_statfsres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: STATFS   %s&bslash;n&quot;
comma
id|SVCFH_fmt
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_statfs
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
op_amp
id|resp-&gt;stats
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
)brace
multiline_comment|/*&n; * NFSv2 Server procedures.&n; * Only the results of non-idempotent operations are cached.&n; */
DECL|macro|nfsd_proc_none
mdefine_line|#define nfsd_proc_none&t;&t;NULL
DECL|macro|nfssvc_release_none
mdefine_line|#define nfssvc_release_none&t;NULL
DECL|struct|nfsd_void
DECL|member|dummy
r_struct
id|nfsd_void
(brace
r_int
id|dummy
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PROC
mdefine_line|#define PROC(name, argt, rest, relt, cache, respsize)&t;&bslash;&n; { (svc_procfunc) nfsd_proc_##name,&t;&t;&bslash;&n;   (kxdrproc_t) nfssvc_decode_##argt,&t;&t;&bslash;&n;   (kxdrproc_t) nfssvc_encode_##rest,&t;&t;&bslash;&n;   (kxdrproc_t) nfssvc_release_##relt,&t;&t;&bslash;&n;   sizeof(struct nfsd_##argt),&t;&t;&t;&bslash;&n;   sizeof(struct nfsd_##rest),&t;&t;&t;&bslash;&n;   0,&t;&t;&t;&t;&t;&t;&bslash;&n;   cache,&t;&t;&t;&t;&t;&bslash;&n;   respsize,&t;&t;&t;&t;       &t;&bslash;&n; }
DECL|macro|ST
mdefine_line|#define ST 1&t;&t;/* status */
DECL|macro|FH
mdefine_line|#define FH 8&t;&t;/* filehandle */
DECL|macro|AT
mdefine_line|#define&t;AT 18&t;&t;/* attributes */
DECL|variable|nfsd_procedures2
r_static
r_struct
id|svc_procedure
id|nfsd_procedures2
(braket
l_int|18
)braket
op_assign
(brace
id|PROC
c_func
(paren
id|null
comma
r_void
comma
r_void
comma
id|none
comma
id|RC_NOCACHE
comma
id|ST
)paren
comma
id|PROC
c_func
(paren
id|getattr
comma
id|fhandle
comma
id|attrstat
comma
id|fhandle
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|AT
)paren
comma
id|PROC
c_func
(paren
id|setattr
comma
id|sattrargs
comma
id|attrstat
comma
id|fhandle
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
id|AT
)paren
comma
id|PROC
c_func
(paren
id|none
comma
r_void
comma
r_void
comma
id|none
comma
id|RC_NOCACHE
comma
id|ST
)paren
comma
id|PROC
c_func
(paren
id|lookup
comma
id|diropargs
comma
id|diropres
comma
id|fhandle
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|FH
op_plus
id|AT
)paren
comma
id|PROC
c_func
(paren
id|readlink
comma
id|readlinkargs
comma
id|readlinkres
comma
id|none
comma
id|RC_NOCACHE
comma
id|ST
op_plus
l_int|1
op_plus
id|NFS_MAXPATHLEN
op_div
l_int|4
)paren
comma
id|PROC
c_func
(paren
id|read
comma
id|readargs
comma
id|readres
comma
id|fhandle
comma
id|RC_NOCACHE
comma
id|ST
op_plus
id|AT
op_plus
l_int|1
op_plus
id|NFSSVC_MAXBLKSIZE
)paren
comma
id|PROC
c_func
(paren
id|none
comma
r_void
comma
r_void
comma
id|none
comma
id|RC_NOCACHE
comma
id|ST
)paren
comma
id|PROC
c_func
(paren
id|write
comma
id|writeargs
comma
id|attrstat
comma
id|fhandle
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
id|AT
)paren
comma
id|PROC
c_func
(paren
id|create
comma
id|createargs
comma
id|diropres
comma
id|fhandle
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
id|FH
op_plus
id|AT
)paren
comma
id|PROC
c_func
(paren
id|remove
comma
id|diropargs
comma
r_void
comma
id|none
comma
id|RC_REPLSTAT
comma
id|ST
)paren
comma
id|PROC
c_func
(paren
id|rename
comma
id|renameargs
comma
r_void
comma
id|none
comma
id|RC_REPLSTAT
comma
id|ST
)paren
comma
id|PROC
c_func
(paren
id|link
comma
id|linkargs
comma
r_void
comma
id|none
comma
id|RC_REPLSTAT
comma
id|ST
)paren
comma
id|PROC
c_func
(paren
id|symlink
comma
id|symlinkargs
comma
r_void
comma
id|none
comma
id|RC_REPLSTAT
comma
id|ST
)paren
comma
id|PROC
c_func
(paren
id|mkdir
comma
id|createargs
comma
id|diropres
comma
id|fhandle
comma
id|RC_REPLBUFF
comma
id|ST
op_plus
id|FH
op_plus
id|AT
)paren
comma
id|PROC
c_func
(paren
id|rmdir
comma
id|diropargs
comma
r_void
comma
id|none
comma
id|RC_REPLSTAT
comma
id|ST
)paren
comma
id|PROC
c_func
(paren
id|readdir
comma
id|readdirargs
comma
id|readdirres
comma
id|none
comma
id|RC_NOCACHE
comma
l_int|0
)paren
comma
id|PROC
c_func
(paren
id|statfs
comma
id|fhandle
comma
id|statfsres
comma
id|none
comma
id|RC_NOCACHE
comma
id|ST
op_plus
l_int|5
)paren
comma
)brace
suffix:semicolon
DECL|variable|nfsd_version2
r_struct
id|svc_version
id|nfsd_version2
op_assign
(brace
dot
id|vs_vers
op_assign
l_int|2
comma
dot
id|vs_nproc
op_assign
l_int|18
comma
dot
id|vs_proc
op_assign
id|nfsd_procedures2
comma
dot
id|vs_dispatch
op_assign
id|nfsd_dispatch
comma
dot
id|vs_xdrsize
op_assign
id|NFS2_SVC_XDRSIZE
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Map errnos to NFS errnos.&n; */
r_int
DECL|function|nfserrno
id|nfserrno
(paren
r_int
id|errno
)paren
(brace
r_static
r_struct
(brace
r_int
id|nfserr
suffix:semicolon
r_int
id|syserr
suffix:semicolon
)brace
id|nfs_errtbl
(braket
)braket
op_assign
(brace
(brace
id|nfs_ok
comma
l_int|0
)brace
comma
(brace
id|nfserr_perm
comma
op_minus
id|EPERM
)brace
comma
(brace
id|nfserr_noent
comma
op_minus
id|ENOENT
)brace
comma
(brace
id|nfserr_io
comma
op_minus
id|EIO
)brace
comma
(brace
id|nfserr_nxio
comma
op_minus
id|ENXIO
)brace
comma
(brace
id|nfserr_acces
comma
op_minus
id|EACCES
)brace
comma
(brace
id|nfserr_exist
comma
op_minus
id|EEXIST
)brace
comma
(brace
id|nfserr_xdev
comma
op_minus
id|EXDEV
)brace
comma
(brace
id|nfserr_mlink
comma
op_minus
id|EMLINK
)brace
comma
(brace
id|nfserr_nodev
comma
op_minus
id|ENODEV
)brace
comma
(brace
id|nfserr_notdir
comma
op_minus
id|ENOTDIR
)brace
comma
(brace
id|nfserr_isdir
comma
op_minus
id|EISDIR
)brace
comma
(brace
id|nfserr_inval
comma
op_minus
id|EINVAL
)brace
comma
(brace
id|nfserr_fbig
comma
op_minus
id|EFBIG
)brace
comma
(brace
id|nfserr_nospc
comma
op_minus
id|ENOSPC
)brace
comma
(brace
id|nfserr_rofs
comma
op_minus
id|EROFS
)brace
comma
(brace
id|nfserr_mlink
comma
op_minus
id|EMLINK
)brace
comma
(brace
id|nfserr_nametoolong
comma
op_minus
id|ENAMETOOLONG
)brace
comma
(brace
id|nfserr_notempty
comma
op_minus
id|ENOTEMPTY
)brace
comma
macro_line|#ifdef EDQUOT
(brace
id|nfserr_dquot
comma
op_minus
id|EDQUOT
)brace
comma
macro_line|#endif
(brace
id|nfserr_stale
comma
op_minus
id|ESTALE
)brace
comma
(brace
id|nfserr_jukebox
comma
op_minus
id|ETIMEDOUT
)brace
comma
(brace
id|nfserr_dropit
comma
op_minus
id|EAGAIN
)brace
comma
(brace
id|nfserr_dropit
comma
op_minus
id|ENOMEM
)brace
comma
(brace
id|nfserr_badname
comma
op_minus
id|ESRCH
)brace
comma
(brace
id|nfserr_io
comma
op_minus
id|ETXTBSY
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
id|EIO
)brace
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|nfs_errtbl
(braket
id|i
)braket
dot
id|nfserr
op_ne
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|nfs_errtbl
(braket
id|i
)braket
dot
id|syserr
op_eq
id|errno
)paren
r_return
id|nfs_errtbl
(braket
id|i
)braket
dot
id|nfserr
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;nfsd: non-standard errno: %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
id|nfserr_io
suffix:semicolon
)brace
eof
