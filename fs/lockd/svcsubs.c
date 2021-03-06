multiline_comment|/*&n; * linux/fs/lockd/svcsubs.c&n; *&n; * Various support routines for the NLM server.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfsd/nfsfh.h&gt;
macro_line|#include &lt;linux/nfsd/export.h&gt;
macro_line|#include &lt;linux/lockd/lockd.h&gt;
macro_line|#include &lt;linux/lockd/share.h&gt;
macro_line|#include &lt;linux/lockd/sm_inter.h&gt;
DECL|macro|NLMDBG_FACILITY
mdefine_line|#define NLMDBG_FACILITY&t;&t;NLMDBG_SVCSUBS
multiline_comment|/*&n; * Global file hash table&n; */
DECL|macro|FILE_HASH_BITS
mdefine_line|#define FILE_HASH_BITS&t;&t;5
DECL|macro|FILE_NRHASH
mdefine_line|#define FILE_NRHASH&t;&t;(1&lt;&lt;FILE_HASH_BITS)
DECL|variable|nlm_files
r_static
r_struct
id|nlm_file
op_star
id|nlm_files
(braket
id|FILE_NRHASH
)braket
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|nlm_file_sema
)paren
suffix:semicolon
DECL|function|file_hash
r_static
r_inline
r_int
r_int
id|file_hash
c_func
(paren
r_struct
id|nfs_fh
op_star
id|f
)paren
(brace
r_int
r_int
id|tmp
op_assign
l_int|0
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
id|i
OL
id|NFS2_FHSIZE
suffix:semicolon
id|i
op_increment
)paren
id|tmp
op_add_assign
id|f-&gt;data
(braket
id|i
)braket
suffix:semicolon
r_return
id|tmp
op_amp
(paren
id|FILE_NRHASH
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Lookup file info. If it doesn&squot;t exist, create a file info struct&n; * and open a (VFS) file for the given inode.&n; *&n; * FIXME:&n; * Note that we open the file O_RDONLY even when creating write locks.&n; * This is not quite right, but for now, we assume the client performs&n; * the proper R/W checking.&n; */
id|u32
DECL|function|nlm_lookup_file
id|nlm_lookup_file
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_file
op_star
op_star
id|result
comma
r_struct
id|nfs_fh
op_star
id|f
)paren
(brace
r_struct
id|nlm_file
op_star
id|file
suffix:semicolon
r_int
r_int
id|hash
suffix:semicolon
id|u32
id|nfserr
suffix:semicolon
id|u32
op_star
id|fhp
op_assign
(paren
id|u32
op_star
)paren
id|f-&gt;data
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: nlm_file_lookup(%08x %08x %08x %08x %08x %08x)&bslash;n&quot;
comma
id|fhp
(braket
l_int|0
)braket
comma
id|fhp
(braket
l_int|1
)braket
comma
id|fhp
(braket
l_int|2
)braket
comma
id|fhp
(braket
l_int|3
)braket
comma
id|fhp
(braket
l_int|4
)braket
comma
id|fhp
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|hash
op_assign
id|file_hash
c_func
(paren
id|f
)paren
suffix:semicolon
multiline_comment|/* Lock file table */
id|down
c_func
(paren
op_amp
id|nlm_file_sema
)paren
suffix:semicolon
r_for
c_loop
(paren
id|file
op_assign
id|nlm_files
(braket
id|hash
)braket
suffix:semicolon
id|file
suffix:semicolon
id|file
op_assign
id|file-&gt;f_next
)paren
r_if
c_cond
(paren
op_logical_neg
id|nfs_compare_fh
c_func
(paren
op_amp
id|file-&gt;f_handle
comma
id|f
)paren
)paren
r_goto
id|found
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: creating file for (%08x %08x %08x %08x %08x %08x)&bslash;n&quot;
comma
id|fhp
(braket
l_int|0
)braket
comma
id|fhp
(braket
l_int|1
)braket
comma
id|fhp
(braket
l_int|2
)braket
comma
id|fhp
(braket
l_int|3
)braket
comma
id|fhp
(braket
l_int|4
)braket
comma
id|fhp
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|nfserr
op_assign
id|nlm_lck_denied_nolocks
suffix:semicolon
id|file
op_assign
(paren
r_struct
id|nlm_file
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|file
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|out_unlock
suffix:semicolon
id|memset
c_func
(paren
id|file
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|file
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|file-&gt;f_handle
comma
id|f
comma
r_sizeof
(paren
r_struct
id|nfs_fh
)paren
)paren
suffix:semicolon
id|file-&gt;f_hash
op_assign
id|hash
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
multiline_comment|/* Open the file. Note that this must not sleep for too long, else&n;&t; * we would lock up lockd:-) So no NFS re-exports, folks.&n;&t; *&n;&t; * We have to make sure we have the right credential to open&n;&t; * the file.&n;&t; */
r_if
c_cond
(paren
(paren
id|nfserr
op_assign
id|nlmsvc_ops
op_member_access_from_pointer
id|fopen
c_func
(paren
id|rqstp
comma
id|f
comma
op_amp
id|file-&gt;f_file
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: open failed (nfserr %d)&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|nfserr
)paren
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|file-&gt;f_next
op_assign
id|nlm_files
(braket
id|hash
)braket
suffix:semicolon
id|nlm_files
(braket
id|hash
)braket
op_assign
id|file
suffix:semicolon
id|found
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;lockd: found file %p (count %d)&bslash;n&quot;
comma
id|file
comma
id|file-&gt;f_count
)paren
suffix:semicolon
op_star
id|result
op_assign
id|file
suffix:semicolon
id|file-&gt;f_count
op_increment
suffix:semicolon
id|nfserr
op_assign
l_int|0
suffix:semicolon
id|out_unlock
suffix:colon
id|up
c_func
(paren
op_amp
id|nlm_file_sema
)paren
suffix:semicolon
r_return
id|nfserr
suffix:semicolon
id|out_free
suffix:colon
id|kfree
c_func
(paren
id|file
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_LOCKD_V4
r_if
c_cond
(paren
id|nfserr
op_eq
l_int|1
)paren
id|nfserr
op_assign
id|nlm4_stale_fh
suffix:semicolon
r_else
macro_line|#endif
id|nfserr
op_assign
id|nlm_lck_denied
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
multiline_comment|/*&n; * Delete a file after having released all locks, blocks and shares&n; */
r_static
r_inline
r_void
DECL|function|nlm_delete_file
id|nlm_delete_file
c_func
(paren
r_struct
id|nlm_file
op_star
id|file
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|nlm_file
op_star
op_star
id|fp
comma
op_star
id|f
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: closing file %s/%ld&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|fp
op_assign
id|nlm_files
op_plus
id|file-&gt;f_hash
suffix:semicolon
r_while
c_loop
(paren
(paren
id|f
op_assign
op_star
id|fp
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|f
op_eq
id|file
)paren
(brace
op_star
id|fp
op_assign
id|file-&gt;f_next
suffix:semicolon
id|nlmsvc_ops
op_member_access_from_pointer
id|fclose
c_func
(paren
id|file-&gt;f_file
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fp
op_assign
op_amp
id|f-&gt;f_next
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd: attempt to release unknown file!&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Loop over all locks on the given file and perform the specified&n; * action.&n; */
r_static
r_int
DECL|function|nlm_traverse_locks
id|nlm_traverse_locks
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
comma
r_struct
id|nlm_file
op_star
id|file
comma
r_int
id|action
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|nlmsvc_file_inode
c_func
(paren
id|file
)paren
suffix:semicolon
r_struct
id|file_lock
op_star
id|fl
suffix:semicolon
r_struct
id|nlm_host
op_star
id|lockhost
suffix:semicolon
id|again
suffix:colon
id|file-&gt;f_locks
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|fl
op_assign
id|inode-&gt;i_flock
suffix:semicolon
id|fl
suffix:semicolon
id|fl
op_assign
id|fl-&gt;fl_next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|fl-&gt;fl_flags
op_amp
id|FL_LOCKD
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* update current lock count */
id|file-&gt;f_locks
op_increment
suffix:semicolon
id|lockhost
op_assign
(paren
r_struct
id|nlm_host
op_star
)paren
id|fl-&gt;fl_owner
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|NLM_ACT_MARK
)paren
id|lockhost-&gt;h_inuse
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|action
op_eq
id|NLM_ACT_CHECK
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|action
op_eq
id|NLM_ACT_UNLOCK
)paren
(brace
r_struct
id|file_lock
id|lock
op_assign
op_star
id|fl
suffix:semicolon
r_if
c_cond
(paren
id|host
op_logical_and
id|lockhost
op_ne
id|host
)paren
r_continue
suffix:semicolon
id|lock.fl_type
op_assign
id|F_UNLCK
suffix:semicolon
id|lock.fl_start
op_assign
l_int|0
suffix:semicolon
id|lock.fl_end
op_assign
id|OFFSET_MAX
suffix:semicolon
r_if
c_cond
(paren
id|posix_lock_file
c_func
(paren
id|file-&gt;f_file
comma
op_amp
id|lock
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lockd: unlock failure in %s:%d&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_goto
id|again
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Operate on a single file&n; */
r_static
r_inline
r_int
DECL|function|nlm_inspect_file
id|nlm_inspect_file
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
comma
r_struct
id|nlm_file
op_star
id|file
comma
r_int
id|action
)paren
(brace
r_if
c_cond
(paren
id|action
op_eq
id|NLM_ACT_CHECK
)paren
(brace
multiline_comment|/* Fast path for mark and sweep garbage collection */
r_if
c_cond
(paren
id|file-&gt;f_count
op_logical_or
id|file-&gt;f_blocks
op_logical_or
id|file-&gt;f_shares
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|nlmsvc_traverse_blocks
c_func
(paren
id|host
comma
id|file
comma
id|action
)paren
op_logical_or
id|nlmsvc_traverse_shares
c_func
(paren
id|host
comma
id|file
comma
id|action
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|nlm_traverse_locks
c_func
(paren
id|host
comma
id|file
comma
id|action
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Loop over all files in the file table.&n; */
r_static
r_int
DECL|function|nlm_traverse_files
id|nlm_traverse_files
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
comma
r_int
id|action
)paren
(brace
r_struct
id|nlm_file
op_star
id|file
comma
op_star
op_star
id|fp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|nlm_file_sema
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|FILE_NRHASH
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fp
op_assign
id|nlm_files
op_plus
id|i
suffix:semicolon
r_while
c_loop
(paren
(paren
id|file
op_assign
op_star
id|fp
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Traverse locks, blocks and shares of this file&n;&t;&t;&t; * and update file-&gt;f_locks count */
r_if
c_cond
(paren
id|nlm_inspect_file
c_func
(paren
id|host
comma
id|file
comma
id|action
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|nlm_file_sema
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* No more references to this file. Let go of it. */
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_blocks
op_logical_and
op_logical_neg
id|file-&gt;f_locks
op_logical_and
op_logical_neg
id|file-&gt;f_shares
op_logical_and
op_logical_neg
id|file-&gt;f_count
)paren
(brace
op_star
id|fp
op_assign
id|file-&gt;f_next
suffix:semicolon
id|nlmsvc_ops
op_member_access_from_pointer
id|fclose
c_func
(paren
id|file-&gt;f_file
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
r_else
(brace
id|fp
op_assign
op_amp
id|file-&gt;f_next
suffix:semicolon
)brace
)brace
)brace
id|up
c_func
(paren
op_amp
id|nlm_file_sema
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Release file. If there are no more remote locks on this file,&n; * close it and free the handle.&n; *&n; * Note that we can&squot;t do proper reference counting without major&n; * contortions because the code in fs/locks.c creates, deletes and&n; * splits locks without notification. Our only way is to walk the&n; * entire lock list each time we remove a lock.&n; */
r_void
DECL|function|nlm_release_file
id|nlm_release_file
c_func
(paren
r_struct
id|nlm_file
op_star
id|file
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: nlm_release_file(%p, ct = %d)&bslash;n&quot;
comma
id|file
comma
id|file-&gt;f_count
)paren
suffix:semicolon
multiline_comment|/* Lock file table */
id|down
c_func
(paren
op_amp
id|nlm_file_sema
)paren
suffix:semicolon
multiline_comment|/* If there are no more locks etc, delete the file */
r_if
c_cond
(paren
op_decrement
id|file-&gt;f_count
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nlm_inspect_file
c_func
(paren
l_int|NULL
comma
id|file
comma
id|NLM_ACT_CHECK
)paren
)paren
(brace
id|nlm_delete_file
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|nlm_file_sema
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Mark all hosts that still hold resources&n; */
r_void
DECL|function|nlmsvc_mark_resources
id|nlmsvc_mark_resources
c_func
(paren
r_void
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: nlmsvc_mark_resources&bslash;n&quot;
)paren
suffix:semicolon
id|nlm_traverse_files
c_func
(paren
l_int|NULL
comma
id|NLM_ACT_MARK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Release all resources held by the given client&n; */
r_void
DECL|function|nlmsvc_free_host_resources
id|nlmsvc_free_host_resources
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: nlmsvc_free_host_resources&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nlm_traverse_files
c_func
(paren
id|host
comma
id|NLM_ACT_UNLOCK
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd: couldn&squot;t remove all locks held by %s&quot;
comma
id|host-&gt;h_name
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * delete all hosts structs for clients&n; */
r_void
DECL|function|nlmsvc_invalidate_all
id|nlmsvc_invalidate_all
c_func
(paren
r_void
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
r_while
c_loop
(paren
(paren
id|host
op_assign
id|nlm_find_client
c_func
(paren
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|nlmsvc_free_host_resources
c_func
(paren
id|host
)paren
suffix:semicolon
id|host-&gt;h_expires
op_assign
l_int|0
suffix:semicolon
id|host-&gt;h_killed
op_assign
l_int|1
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
)brace
)brace
eof
