multiline_comment|/*&n; *  linux/fs/nfs/proc.c&n; *&n; *  Copyright (C) 1992, 1993, 1994  Rick Sladkey&n; *&n; *  OS-independent nfs remote procedure call functions&n; *&n; *  Tuned by Alan Cox &lt;A.Cox@swansea.ac.uk&gt; for &gt;3K buffers&n; *  so at last we can have decent(ish) throughput off a &n; *  Sun server.&n; *&n; *  Coding optimized and cleaned up by Florian La Roche.&n; *  Note: Error returns are optimized for NFS_OK, which isn&squot;t translated via&n; *  nfs_stat_to_errno(), but happens to be already the right return code.&n; *&n; *  Also, the code currently doesn&squot;t check the size of the packet, when&n; *  it decodes the packet.&n; *&n; *  Feel free to fix it and mail me the diffs if it worries you.&n; *&n; *  Completely rewritten to support the new RPC call interface;&n; *  rewrote and moved the entire XDR stuff to xdr.c&n; *  --Olaf Kirch June 1996&n; *&n; *  The code below initializes all auto variables explicitly, otherwise&n; *  it will fail to work as a module (gcc generates a memset call for an&n; *  incomplete struct).&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/nfs2.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;NFSDBG_PROC
multiline_comment|/*&n; * Bare-bones access to getattr: this is for nfs_read_super.&n; */
r_static
r_int
DECL|function|nfs_proc_get_root
id|nfs_proc_get_root
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  getroot&bslash;n&quot;
)paren
suffix:semicolon
id|fattr-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_GETATTR
comma
id|fhandle
comma
id|fattr
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply getroot&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * One function for each procedure in the NFS protocol.&n; */
r_static
r_int
DECL|function|nfs_proc_getattr
id|nfs_proc_getattr
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  getattr&bslash;n&quot;
)paren
suffix:semicolon
id|fattr-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|inode
)paren
comma
id|NFSPROC_GETATTR
comma
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
id|fattr
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply getattr&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_setattr
id|nfs_proc_setattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|nfs_fattr
op_star
id|fattr
comma
r_struct
id|iattr
op_star
id|sattr
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|nfs_sattrargs
id|arg
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
dot
id|sattr
op_assign
id|sattr
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  setattr&bslash;n&quot;
)paren
suffix:semicolon
id|fattr-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|inode
)paren
comma
id|NFSPROC_SETATTR
comma
op_amp
id|arg
comma
id|fattr
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply setattr&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_lookup
id|nfs_proc_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|name
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_struct
id|nfs_diropargs
id|arg
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|dir
)paren
comma
dot
id|name
op_assign
id|name-&gt;name
comma
dot
id|len
op_assign
id|name-&gt;len
)brace
suffix:semicolon
r_struct
id|nfs_diropok
id|res
op_assign
(brace
dot
id|fh
op_assign
id|fhandle
comma
dot
id|fattr
op_assign
id|fattr
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  lookup %s&bslash;n&quot;
comma
id|name-&gt;name
)paren
suffix:semicolon
id|fattr-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|dir
)paren
comma
id|NFSPROC_LOOKUP
comma
op_amp
id|arg
comma
op_amp
id|res
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply lookup: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_readlink
id|nfs_proc_readlink
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|nfs_readlinkargs
id|args
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
dot
id|count
op_assign
id|PAGE_CACHE_SIZE
comma
dot
id|pages
op_assign
op_amp
id|page
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  readlink&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|inode
)paren
comma
id|NFSPROC_READLINK
comma
op_amp
id|args
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply readlink: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_read
id|nfs_proc_read
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|rpc_cred
op_star
id|cred
comma
r_struct
id|nfs_fattr
op_star
id|fattr
comma
r_int
id|flags
comma
r_int
r_int
id|base
comma
r_int
r_int
id|count
comma
r_struct
id|page
op_star
id|page
comma
r_int
op_star
id|eofp
)paren
(brace
id|u64
id|offset
op_assign
id|page_offset
c_func
(paren
id|page
)paren
op_plus
id|base
suffix:semicolon
r_struct
id|nfs_readargs
id|arg
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
dot
id|offset
op_assign
id|offset
comma
dot
id|count
op_assign
id|count
comma
dot
id|pgbase
op_assign
id|base
comma
dot
id|pages
op_assign
op_amp
id|page
)brace
suffix:semicolon
r_struct
id|nfs_readres
id|res
op_assign
(brace
dot
id|fattr
op_assign
id|fattr
comma
dot
id|count
op_assign
id|count
)brace
suffix:semicolon
r_struct
id|rpc_message
id|msg
op_assign
(brace
dot
id|rpc_proc
op_assign
id|NFSPROC_READ
comma
dot
id|rpc_argp
op_assign
op_amp
id|arg
comma
dot
id|rpc_resp
op_assign
op_amp
id|res
comma
dot
id|rpc_cred
op_assign
id|cred
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  read %d @ %Ld&bslash;n&quot;
comma
id|count
comma
(paren
r_int
r_int
)paren
id|offset
)paren
suffix:semicolon
id|fattr-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|rpc_call_sync
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|inode
)paren
comma
op_amp
id|msg
comma
id|flags
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply read: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
op_star
id|eofp
op_assign
id|res.eof
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_write
id|nfs_proc_write
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|rpc_cred
op_star
id|cred
comma
r_struct
id|nfs_fattr
op_star
id|fattr
comma
r_int
id|how
comma
r_int
r_int
id|base
comma
r_int
r_int
id|count
comma
r_struct
id|page
op_star
id|page
comma
r_struct
id|nfs_writeverf
op_star
id|verf
)paren
(brace
id|u64
id|offset
op_assign
id|page_offset
c_func
(paren
id|page
)paren
op_plus
id|base
suffix:semicolon
r_struct
id|nfs_writeargs
id|arg
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
dot
id|offset
op_assign
id|offset
comma
dot
id|count
op_assign
id|count
comma
dot
id|stable
op_assign
id|NFS_FILE_SYNC
comma
dot
id|pgbase
op_assign
id|base
comma
dot
id|pages
op_assign
op_amp
id|page
)brace
suffix:semicolon
r_struct
id|nfs_writeres
id|res
op_assign
(brace
dot
id|fattr
op_assign
id|fattr
comma
dot
id|verf
op_assign
id|verf
comma
dot
id|count
op_assign
id|count
)brace
suffix:semicolon
r_struct
id|rpc_message
id|msg
op_assign
(brace
dot
id|rpc_proc
op_assign
id|NFSPROC_WRITE
comma
dot
id|rpc_argp
op_assign
op_amp
id|arg
comma
dot
id|rpc_resp
op_assign
op_amp
id|res
comma
dot
id|rpc_cred
op_assign
id|cred
)brace
suffix:semicolon
r_int
id|status
comma
id|flags
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  write %d @ %Ld&bslash;n&quot;
comma
id|count
comma
(paren
r_int
r_int
)paren
id|offset
)paren
suffix:semicolon
id|fattr-&gt;valid
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|how
op_amp
id|NFS_RW_SWAP
)paren
id|flags
op_or_assign
id|NFS_RPC_SWAPFLAGS
suffix:semicolon
id|status
op_assign
id|rpc_call_sync
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|inode
)paren
comma
op_amp
id|msg
comma
id|flags
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply write: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|verf-&gt;committed
op_assign
id|NFS_FILE_SYNC
suffix:semicolon
multiline_comment|/* NFSv2 always syncs data */
r_return
id|status
OL
l_int|0
ques
c_cond
id|status
suffix:colon
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_create
id|nfs_proc_create
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|name
comma
r_struct
id|iattr
op_star
id|sattr
comma
r_int
id|flags
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_struct
id|nfs_createargs
id|arg
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|dir
)paren
comma
dot
id|name
op_assign
id|name-&gt;name
comma
dot
id|len
op_assign
id|name-&gt;len
comma
dot
id|sattr
op_assign
id|sattr
)brace
suffix:semicolon
r_struct
id|nfs_diropok
id|res
op_assign
(brace
dot
id|fh
op_assign
id|fhandle
comma
dot
id|fattr
op_assign
id|fattr
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|fattr-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  create %s&bslash;n&quot;
comma
id|name-&gt;name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|dir
)paren
comma
id|NFSPROC_CREATE
comma
op_amp
id|arg
comma
op_amp
id|res
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply create: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * In NFSv2, mknod is grafted onto the create call.&n; */
r_static
r_int
DECL|function|nfs_proc_mknod
id|nfs_proc_mknod
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|name
comma
r_struct
id|iattr
op_star
id|sattr
comma
id|dev_t
id|rdev
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_struct
id|nfs_createargs
id|arg
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|dir
)paren
comma
dot
id|name
op_assign
id|name-&gt;name
comma
dot
id|len
op_assign
id|name-&gt;len
comma
dot
id|sattr
op_assign
id|sattr
)brace
suffix:semicolon
r_struct
id|nfs_diropok
id|res
op_assign
(brace
dot
id|fh
op_assign
id|fhandle
comma
dot
id|fattr
op_assign
id|fattr
)brace
suffix:semicolon
r_int
id|status
comma
id|mode
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  mknod %s&bslash;n&quot;
comma
id|name-&gt;name
)paren
suffix:semicolon
id|mode
op_assign
id|sattr-&gt;ia_mode
suffix:semicolon
r_if
c_cond
(paren
id|S_ISFIFO
c_func
(paren
id|mode
)paren
)paren
(brace
id|sattr-&gt;ia_mode
op_assign
(paren
id|mode
op_amp
op_complement
id|S_IFMT
)paren
op_or
id|S_IFCHR
suffix:semicolon
id|sattr-&gt;ia_valid
op_and_assign
op_complement
id|ATTR_SIZE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISBLK
c_func
(paren
id|mode
)paren
)paren
(brace
id|sattr-&gt;ia_valid
op_or_assign
id|ATTR_SIZE
suffix:semicolon
id|sattr-&gt;ia_size
op_assign
id|rdev
suffix:semicolon
multiline_comment|/* get out your barf bag */
)brace
id|fattr-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|dir
)paren
comma
id|NFSPROC_CREATE
comma
op_amp
id|arg
comma
op_amp
id|res
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
op_minus
id|EINVAL
op_logical_and
id|S_ISFIFO
c_func
(paren
id|mode
)paren
)paren
(brace
id|sattr-&gt;ia_mode
op_assign
id|mode
suffix:semicolon
id|fattr-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|dir
)paren
comma
id|NFSPROC_CREATE
comma
op_amp
id|arg
comma
op_amp
id|res
comma
l_int|0
)paren
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;NFS reply mknod: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_remove
id|nfs_proc_remove
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|name
)paren
(brace
r_struct
id|nfs_diropargs
id|arg
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|dir
)paren
comma
dot
id|name
op_assign
id|name-&gt;name
comma
dot
id|len
op_assign
id|name-&gt;len
)brace
suffix:semicolon
r_struct
id|rpc_message
id|msg
op_assign
(brace
dot
id|rpc_proc
op_assign
id|NFSPROC_REMOVE
comma
dot
id|rpc_argp
op_assign
op_amp
id|arg
comma
dot
id|rpc_resp
op_assign
l_int|NULL
comma
dot
id|rpc_cred
op_assign
l_int|NULL
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  remove %s&bslash;n&quot;
comma
id|name-&gt;name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call_sync
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|dir
)paren
comma
op_amp
id|msg
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply remove: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_unlink_setup
id|nfs_proc_unlink_setup
c_func
(paren
r_struct
id|rpc_message
op_star
id|msg
comma
r_struct
id|dentry
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|name
)paren
(brace
r_struct
id|nfs_diropargs
op_star
id|arg
suffix:semicolon
id|arg
op_assign
(paren
r_struct
id|nfs_diropargs
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|arg
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|arg-&gt;fh
op_assign
id|NFS_FH
c_func
(paren
id|dir-&gt;d_inode
)paren
suffix:semicolon
id|arg-&gt;name
op_assign
id|name-&gt;name
suffix:semicolon
id|arg-&gt;len
op_assign
id|name-&gt;len
suffix:semicolon
id|msg-&gt;rpc_proc
op_assign
id|NFSPROC_REMOVE
suffix:semicolon
id|msg-&gt;rpc_argp
op_assign
id|arg
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|nfs_proc_unlink_done
id|nfs_proc_unlink_done
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_struct
id|rpc_message
op_star
id|msg
)paren
(brace
r_if
c_cond
(paren
id|msg-&gt;rpc_argp
)paren
(brace
id|NFS_CACHEINV
c_func
(paren
id|dir-&gt;d_inode
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|msg-&gt;rpc_argp
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|nfs_proc_rename
id|nfs_proc_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_struct
id|qstr
op_star
id|old_name
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_struct
id|qstr
op_star
id|new_name
)paren
(brace
r_struct
id|nfs_renameargs
id|arg
op_assign
(brace
dot
id|fromfh
op_assign
id|NFS_FH
c_func
(paren
id|old_dir
)paren
comma
dot
id|fromname
op_assign
id|old_name-&gt;name
comma
dot
id|fromlen
op_assign
id|old_name-&gt;len
comma
dot
id|tofh
op_assign
id|NFS_FH
c_func
(paren
id|new_dir
)paren
comma
dot
id|toname
op_assign
id|new_name-&gt;name
comma
dot
id|tolen
op_assign
id|new_name-&gt;len
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  rename %s -&gt; %s&bslash;n&quot;
comma
id|old_name-&gt;name
comma
id|new_name-&gt;name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|old_dir
)paren
comma
id|NFSPROC_RENAME
comma
op_amp
id|arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply rename: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_link
id|nfs_proc_link
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|name
)paren
(brace
r_struct
id|nfs_linkargs
id|arg
op_assign
(brace
dot
id|fromfh
op_assign
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
dot
id|tofh
op_assign
id|NFS_FH
c_func
(paren
id|dir
)paren
comma
dot
id|toname
op_assign
id|name-&gt;name
comma
dot
id|tolen
op_assign
id|name-&gt;len
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  link %s&bslash;n&quot;
comma
id|name-&gt;name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|inode
)paren
comma
id|NFSPROC_LINK
comma
op_amp
id|arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply link: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_symlink
id|nfs_proc_symlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|name
comma
r_struct
id|qstr
op_star
id|path
comma
r_struct
id|iattr
op_star
id|sattr
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_struct
id|nfs_symlinkargs
id|arg
op_assign
(brace
dot
id|fromfh
op_assign
id|NFS_FH
c_func
(paren
id|dir
)paren
comma
dot
id|fromname
op_assign
id|name-&gt;name
comma
dot
id|fromlen
op_assign
id|name-&gt;len
comma
dot
id|topath
op_assign
id|path-&gt;name
comma
dot
id|tolen
op_assign
id|path-&gt;len
comma
dot
id|sattr
op_assign
id|sattr
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  symlink %s -&gt; %s&bslash;n&quot;
comma
id|name-&gt;name
comma
id|path-&gt;name
)paren
suffix:semicolon
id|fattr-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|dir
)paren
comma
id|NFSPROC_SYMLINK
comma
op_amp
id|arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply symlink: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_mkdir
id|nfs_proc_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|name
comma
r_struct
id|iattr
op_star
id|sattr
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_struct
id|nfs_createargs
id|arg
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|dir
)paren
comma
dot
id|name
op_assign
id|name-&gt;name
comma
dot
id|len
op_assign
id|name-&gt;len
comma
dot
id|sattr
op_assign
id|sattr
)brace
suffix:semicolon
r_struct
id|nfs_diropok
id|res
op_assign
(brace
dot
id|fh
op_assign
id|fhandle
comma
dot
id|fattr
op_assign
id|fattr
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  mkdir %s&bslash;n&quot;
comma
id|name-&gt;name
)paren
suffix:semicolon
id|fattr-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|dir
)paren
comma
id|NFSPROC_MKDIR
comma
op_amp
id|arg
comma
op_amp
id|res
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply mkdir: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_rmdir
id|nfs_proc_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|qstr
op_star
id|name
)paren
(brace
r_struct
id|nfs_diropargs
id|arg
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|dir
)paren
comma
dot
id|name
op_assign
id|name-&gt;name
comma
dot
id|len
op_assign
id|name-&gt;len
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  rmdir %s&bslash;n&quot;
comma
id|name-&gt;name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|dir
)paren
comma
id|NFSPROC_RMDIR
comma
op_amp
id|arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply rmdir: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * The READDIR implementation is somewhat hackish - we pass a temporary&n; * buffer to the encode function, which installs it in the receive&n; * the receive iovec. The decode function just parses the reply to make&n; * sure it is syntactically correct; the entries itself are decoded&n; * from nfs_readdir by calling the decode_entry function directly.&n; */
r_static
r_int
DECL|function|nfs_proc_readdir
id|nfs_proc_readdir
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|rpc_cred
op_star
id|cred
comma
id|u64
id|cookie
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|count
comma
r_int
id|plus
)paren
(brace
r_struct
id|inode
op_star
id|dir
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|nfs_readdirargs
id|arg
op_assign
(brace
dot
id|fh
op_assign
id|NFS_FH
c_func
(paren
id|dir
)paren
comma
dot
id|cookie
op_assign
id|cookie
comma
dot
id|count
op_assign
id|count
comma
dot
id|pages
op_assign
op_amp
id|page
)brace
suffix:semicolon
r_struct
id|rpc_message
id|msg
op_assign
(brace
dot
id|rpc_proc
op_assign
id|NFSPROC_READDIR
comma
dot
id|rpc_argp
op_assign
op_amp
id|arg
comma
dot
id|rpc_resp
op_assign
l_int|NULL
comma
dot
id|rpc_cred
op_assign
id|cred
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  readdir %d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|cookie
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call_sync
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|dir
)paren
comma
op_amp
id|msg
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply readdir: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_proc_statfs
id|nfs_proc_statfs
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fsinfo
op_star
id|info
)paren
(brace
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  statfs&bslash;n&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_STATFS
comma
id|fhandle
comma
id|info
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply statfs: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_extern
id|u32
op_star
id|nfs_decode_dirent
c_func
(paren
id|u32
op_star
comma
r_struct
id|nfs_entry
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|nfs_v2_clientops
r_struct
id|nfs_rpc_ops
id|nfs_v2_clientops
op_assign
(brace
dot
id|version
op_assign
l_int|2
comma
multiline_comment|/* protocol version */
dot
id|getroot
op_assign
id|nfs_proc_get_root
comma
dot
id|getattr
op_assign
id|nfs_proc_getattr
comma
dot
id|setattr
op_assign
id|nfs_proc_setattr
comma
dot
id|lookup
op_assign
id|nfs_proc_lookup
comma
dot
id|access
op_assign
l_int|NULL
comma
multiline_comment|/* access */
dot
id|readlink
op_assign
id|nfs_proc_readlink
comma
dot
id|read
op_assign
id|nfs_proc_read
comma
dot
id|write
op_assign
id|nfs_proc_write
comma
dot
id|commit
op_assign
l_int|NULL
comma
multiline_comment|/* commit */
dot
id|create
op_assign
id|nfs_proc_create
comma
dot
id|remove
op_assign
id|nfs_proc_remove
comma
dot
id|unlink_setup
op_assign
id|nfs_proc_unlink_setup
comma
dot
id|unlink_done
op_assign
id|nfs_proc_unlink_done
comma
dot
id|rename
op_assign
id|nfs_proc_rename
comma
dot
id|link
op_assign
id|nfs_proc_link
comma
dot
id|symlink
op_assign
id|nfs_proc_symlink
comma
dot
id|mkdir
op_assign
id|nfs_proc_mkdir
comma
dot
id|rmdir
op_assign
id|nfs_proc_rmdir
comma
dot
id|readdir
op_assign
id|nfs_proc_readdir
comma
dot
id|mknod
op_assign
id|nfs_proc_mknod
comma
dot
id|statfs
op_assign
id|nfs_proc_statfs
comma
dot
id|decode_dirent
op_assign
id|nfs_decode_dirent
comma
)brace
suffix:semicolon
eof
